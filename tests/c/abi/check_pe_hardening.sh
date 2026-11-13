#!/usr/bin/env bash
# Checks the hardening and the exports of the Windows DLL of monero-c. Run it in MSYS2 MINGW64 (it needs objdump and c++filt of binutils, and awk).
#
#   check_pe_hardening.sh path/to/libmonero_c.dll [path/to/monero_c.symbols]
#
# 1. The flags of the image: ASLR with a high entropy address space (DYNAMIC_BASE, HIGH_ENTROPY_VA) and DEP (NX_COMPAT). mingw-w64 sets them.
# 2. How many functions of each kind (the C ABI, C++, C) call __stack_chk_fail, see function_hardening.awk and check_elf_hardening.sh. The gcc of
#    MSYS2 doesn't turn the stack protector on, so the functions of monero-c had none until the build asked for it in CMakeLists.txt, while the
#    libraries of monero-project, Boost and MSYS2 had it:
#      measured before it, from the build of 0.4.0: abi 0% (304 functions), c++ 21.9%, c 13.7%
#      measured with it, on the build of this check: abi 76.3%, c++ 22.5%, c 13.7%
# 3. The exports: every function of the C ABI, and nothing that isn't Boost.Serialization or Boost.Archive. Those are the 1099 symbols that the
#    headers of Boost mark with BOOST_SYMBOL_EXPORT and that a .def file doesn't remove (see TODO.md). Any other export, such as a symbol of OpenSSL
#    or libsodium, fails the check.
set -euo pipefail
export LC_ALL=C

library="${1:?usage: check_pe_hardening.sh library.dll [monero_c.symbols]}"
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
expected="${2:-$here/monero_c.symbols}"

MIN_PROTECTED_ABI=40
MIN_PROTECTED_CPP=10
MIN_PROTECTED_C=8
# fewer functions than this in a kind means that the output was not read
MIN_FUNCTIONS_ABI=250
MIN_FUNCTIONS_CPP=1000
MIN_FUNCTIONS_C=1000

failed=0
fail() {
  echo "FAIL: $*"
  failed=1
}

for tool in objdump c++filt awk sort comm; do
  command -v "$tool" > /dev/null || { echo "$tool is needed"; exit 2; }
done

# the output of a tool is kept in a variable and read with here-strings: grep -q that stops at the first match makes the tool before it in a pipe
# fail with SIGPIPE, which pipefail turns into a failure
headers=$(objdump -p "$library")
echo "$library"
for flag in DYNAMIC_BASE HIGH_ENTROPY_VA NX_COMPAT; do
  grep -q "$flag" <<< "$headers" || fail "the image has no $flag in its DllCharacteristics"
done

# the names in the export table
exports=$(sed -n '/Ordinal\/Name Pointer/,$p' <<< "$headers" | awk '/^[ \t]*\[ *[0-9]+\]/ { print $NF }' | sort -u)
echo "exports: $(wc -l <<< "$exports")"
exported_abi=$(grep '^monero_' <<< "$exports" || true)
# a checkout on Windows can turn the line ends of the list into CRLF, which make every name of it different from the ones of the DLL
expected_names=$(tr -d '\r' < "$expected" | sort -u)
missing=$(comm -13 <(sort -u <<< "$exported_abi") <(cat <<< "$expected_names"))
extra=$(comm -23 <(sort -u <<< "$exported_abi") <(cat <<< "$expected_names"))
[ -z "$missing" ] || fail "missing from the DLL: $(tr '\n' ' ' <<< "$missing")"
[ -z "$extra" ] || fail "not in $expected: $(tr '\n' ' ' <<< "$extra")"
foreign=$(grep -v '^monero_' <<< "$exports" | c++filt | grep -Ev '^((vtable|typeinfo|typeinfo name|guard variable|VTT|construction vtable) for )?((non-virtual |virtual )?thunk to )?boost::(serialization|archive)::' || true)
if [ -n "$foreign" ]; then
  fail "the DLL exports $(wc -l <<< "$foreign") symbols that are not of the C ABI or of Boost.Serialization and Boost.Archive, such as:"
  head -n 20 <<< "$foreign"
fi

counts=$(objdump -d --no-show-raw-insn "$library" | awk -f "$here/function_hardening.awk")
echo "kind  functions  stack protector"
check_kind() {
  local kind="$1" min_functions="$2" min_protected="$3" line total guarded pads
  line=$(awk -v k="$kind" '$1 == k' <<< "$counts")
  [ -n "$line" ] || { fail "no function of the kind $kind was found"; return; }
  read -r _ total guarded pads <<< "$line"
  local protected_percent=$((guarded * 1000 / total))
  printf '%-5s %9d  %6d (%2d.%d%%)\n' "$kind" "$total" "$guarded" $((protected_percent / 10)) $((protected_percent % 10))
  [ "$total" -ge "$min_functions" ] || fail "only $total functions of the kind $kind were found, the output of objdump was not read"
  [ "$protected_percent" -ge $((min_protected * 10)) ] || fail "the kind $kind has $((protected_percent / 10)).$((protected_percent % 10))% of its functions with a stack protector, the minimum is $min_protected%"
}
check_kind abi "$MIN_FUNCTIONS_ABI" "$MIN_PROTECTED_ABI"
check_kind c++ "$MIN_FUNCTIONS_CPP" "$MIN_PROTECTED_CPP"
check_kind c "$MIN_FUNCTIONS_C" "$MIN_PROTECTED_C"

if [ "$failed" -ne 0 ]; then
  exit 1
fi
echo "hardening of $library: ok"
