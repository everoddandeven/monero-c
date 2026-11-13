# Reads the output of `objdump -d --no-show-raw-insn` of a library and says, for the functions of each kind, how many call __stack_chk_fail, which is
# what a function that the compiler protects with a canary does, and how many start with a landing pad of the branch protection (endbr64 on x86,
# bti on arm). The functions are the ones that the symbol table names, so the library has to have it.
#
# The kinds are told by the name of the function: the C ABI (monero_*), C++ (a mangled name, _Z...), where monero-c, monero-cpp, monero-project and
# Boost are, and C, where OpenSSL, unbound and libsodium are. A compiler that is not given the flags of the build protects almost none of the C ones,
# and that is what the checks of check_elf_hardening.sh and check_pe_hardening.sh look for. The output is a line per kind:
#   <kind> <number of functions> <number that call __stack_chk_fail> <number that start with a landing pad>

function kind_of(name) {
  if (name ~ /^monero_/) return "abi"
  if (name ~ /^_Z/) return "c++"
  return "c"
}

function skip(name) {
  # the stubs of the dynamic linker, and the parts that the compiler splits out of a function, which have no canary of their own
  return name ~ /@plt$/ || name ~ /^\.plt/ || name == "_init" || name == "_fini" || name ~ /\.cold$/ || name ~ /\.part\.[0-9]+$/
}

function flush() {
  if (name == "" || skip(name)) return
  k = kind_of(name)
  total[k]++
  if (protected) guarded[k]++
  if (landing) pads[k]++
}

/^[0-9a-f]+ <.*>:$/ {
  flush()
  name = $2
  gsub(/[<>:]/, "", name)
  protected = 0
  landing = 0
  first = 1
  next
}

/__stack_chk_fail/ { protected = 1 }

# the first instruction of the function
first && /^[ \t]+[0-9a-f]+:/ {
  if ($0 ~ /endbr64|bti/) landing = 1
  first = 0
}

END {
  flush()
  for (k in total) printf "%s %d %d %d\n", k, total[k], guarded[k] + 0, pads[k] + 0
}
