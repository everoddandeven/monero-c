#!/usr/bin/env bash
# Checks the hardening of the macOS library of monero-c. Run it on macOS, which has nm and otool.
#
#   check_macho_hardening.sh path/to/libmonero_c.dylib
#
# Apple clang turns the stack protector on (-fstack-protector-strong), so what is checked is that the library imports the guard and the handler of
# the canary, and that many functions call the handler. The count is the number of calls to ___stack_chk_fail in the code, a call for each function
# that has a canary. The library of 0.4.0 for Linux x86_64 has about 6200 of them, and the minimum is a sixth of that: a library built with no stack
# protector, or whose libraries were, has a handful. The minimum was not measured on the library of macOS, since the one of the build is not read
# anywhere else: if the first run of the check is under it, count the calls by hand (otool -tV library | grep -c ___stack_chk_fail) and set it.
set -euo pipefail
export LC_ALL=C

library="${1:?usage: check_macho_hardening.sh library.dylib}"
MIN_CANARY_CALLS=1000

failed=0
fail() {
  echo "FAIL: $*"
  failed=1
}

for tool in nm otool awk; do
  command -v "$tool" > /dev/null || { echo "$tool is needed"; exit 2; }
done

echo "$library"
undefined=$(nm -u "$library")
for symbol in ___stack_chk_fail ___stack_chk_guard; do
  # nm of Apple prints the name alone for -u, and some print the type before it
  grep -Eq "(^|[[:space:]])${symbol}\$" <<< "$undefined" || fail "$symbol is not imported, so there are no stack canaries"
done

# a call is a line of the code that names the handler. The stub of the dynamic linker is named in each of them
calls=$(otool -tV "$library" | awk '/___stack_chk_fail/ { n++ } END { print n + 0 }')
echo "calls to ___stack_chk_fail: $calls (minimum $MIN_CANARY_CALLS)"
[ "$calls" -ge "$MIN_CANARY_CALLS" ] || fail "only $calls calls to ___stack_chk_fail, so most of the code has no stack protector"

if [ "$failed" -ne 0 ]; then
  exit 1
fi
echo "hardening of $library: ok"
