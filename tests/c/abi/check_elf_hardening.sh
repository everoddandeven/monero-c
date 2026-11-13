#!/usr/bin/env bash
# Checks the hardening of a Linux library of monero-c: the segments and the dynamic section, and how many of its functions the compiler protected.
#
#   check_elf_hardening.sh path/to/libmonero_c.so
#
# It needs the symbol table of the library, so it checks the one that the build makes and not the stripped one of the archives.
#
# Why the counts: a library that has a stack canary in one function and nothing in the rest passes a check that looks for __stack_chk_fail and
# the _chk functions of FORTIFY, and the release of 0.3.0, where monero-c, monero-cpp, OpenSSL and unbound were built with no flags (the gcc of
# debian:12 doesn't turn them on, and the one of Ubuntu does), has both. So the functions are counted, by kind (see function_hardening.awk).
#
# The minimums are about half of what the build of 0.4.0 has (percent of the functions that call __stack_chk_fail, and, on x86_64, that start with
# endbr64), and far from what a build with no flags has (C: 1.3%, ABI: under 1%, endbr64: under 3%):
#   measured on x86_64 : stack protector: abi 75.8%, c++ 20.4%, c 15.5%;  endbr64: abi 100%, c++ 59.2%, c 89.0%
# A kind that falls under its minimum is a flag that no longer reaches a library, or a library that was built without them.
set -euo pipefail
export LC_ALL=C

library="${1:?usage: check_elf_hardening.sh library.so}"
here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

MIN_PROTECTED_ABI=40
MIN_PROTECTED_CPP=10
MIN_PROTECTED_C=8
MIN_FORTIFY_IMPORTS=8
# x86_64 only: arm has no flag for the branch protection in the build
MIN_LANDING_ABI=60
MIN_LANDING_CPP=30
MIN_LANDING_C=60
# fewer functions than this in a kind means that the output was not read, and not that the library is hardened
MIN_FUNCTIONS_ABI=250
MIN_FUNCTIONS_CPP=1000
MIN_FUNCTIONS_C=1000

failed=0
fail() {
  echo "FAIL: $*"
  failed=1
}

for tool in readelf objdump awk; do
  command -v "$tool" > /dev/null || { echo "$tool is needed"; exit 2; }
done

machine=$(readelf -h "$library" | awk -F: '/Machine:/ {gsub(/^[ \t]+/, "", $2); print $2}')
echo "$library: $machine"

# the output of a tool is kept in a variable and read with here-strings: grep -q that stops at the first match makes the tool before it in a pipe
# fail with SIGPIPE, which pipefail turns into a failure
dynamic_symbols=$(readelf --dyn-syms --wide "$library")
grep -Eq 'UND[[:space:]]+__stack_chk_fail(@|$)' <<< "$dynamic_symbols" || fail "__stack_chk_fail is not imported, so there are no stack canaries"
fortify_imports=$(awk '$7 == "UND" && $8 ~ /^__[A-Za-z0-9_]+_chk(@|$)/ { n++ } END { print n + 0 }' <<< "$dynamic_symbols")
echo "FORTIFY functions imported: $fortify_imports (minimum $MIN_FORTIFY_IMPORTS)"
[ "$fortify_imports" -ge "$MIN_FORTIFY_IMPORTS" ] || fail "only $fortify_imports _chk functions are imported, FORTIFY_SOURCE is not on in most of the code"

program_headers=$(readelf -lW "$library")
grep -q 'GNU_RELRO' <<< "$program_headers" || fail "RELRO segment is missing"
awk '$1 == "GNU_STACK" { found = 1; if ($7 ~ /E/) executable = 1 } END { exit !(found && !executable) }' <<< "$program_headers" || fail "GNU_STACK is executable or missing"
dynamic_section=$(readelf -dW "$library")
grep -Eq '\(BIND_NOW\)|\(FLAGS_1\).*NOW' <<< "$dynamic_section" || fail "full RELRO (BIND_NOW) is missing"
section_headers=$(readelf -SW "$library")
grep -q '\.symtab' <<< "$section_headers" || fail "the library has no symbol table, so its functions can't be counted: check the library of the build, not a stripped one"

# the functions that the compiler protected, by kind
counts=$(objdump -d --no-show-raw-insn "$library" | awk -f "$here/function_hardening.awk")
echo "kind  functions  stack protector  landing pad"
check_kind() {
  local kind="$1" min_functions="$2" min_protected="$3" min_landing="$4" line total guarded pads
  line=$(awk -v k="$kind" '$1 == k' <<< "$counts")
  [ -n "$line" ] || { fail "no function of the kind $kind was found"; return; }
  read -r _ total guarded pads <<< "$line"
  local protected_percent=$((guarded * 1000 / total))
  local landing_percent=$((pads * 1000 / total))
  printf '%-5s %9d  %6d (%2d.%d%%)  %6d (%2d.%d%%)\n' "$kind" "$total" "$guarded" $((protected_percent / 10)) $((protected_percent % 10)) "$pads" $((landing_percent / 10)) $((landing_percent % 10))
  [ "$total" -ge "$min_functions" ] || fail "only $total functions of the kind $kind were found, the output of objdump was not read"
  [ "$protected_percent" -ge $((min_protected * 10)) ] || fail "the kind $kind has $((protected_percent / 10)).$((protected_percent % 10))% of its functions with a stack protector, the minimum is $min_protected%"
  if [ "$machine" = "Advanced Micro Devices X86-64" ] && [ "$min_landing" -gt 0 ]; then
    [ "$landing_percent" -ge $((min_landing * 10)) ] || fail "the kind $kind has $((landing_percent / 10)).$((landing_percent % 10))% of its functions with endbr64, the minimum is $min_landing%"
  fi
}
check_kind abi "$MIN_FUNCTIONS_ABI" "$MIN_PROTECTED_ABI" "$MIN_LANDING_ABI"
check_kind c++ "$MIN_FUNCTIONS_CPP" "$MIN_PROTECTED_CPP" "$MIN_LANDING_CPP"
check_kind c "$MIN_FUNCTIONS_C" "$MIN_PROTECTED_C" "$MIN_LANDING_C"

if [ "$failed" -ne 0 ]; then
  exit 1
fi
echo "hardening of $library: ok"
