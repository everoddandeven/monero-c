#!/usr/bin/env bash
# Compares the versions of the brew formulae that the macOS build links with the ones in brew-versions.txt, after brew install. A formula that
# has another version, or is not installed, is a warning of the run, and is in its summary. It fails only with BREW_VERSIONS_STRICT=1.
#
#   check-brew-versions.sh [brew-versions.txt]
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
list="${1:-$here/brew-versions.txt}"
architecture=$(uname -m)
changed=0
rows=""

while read -r listed_architecture formula expected; do
  [ "$listed_architecture" = "$architecture" ] || continue
  # brew lists every installed version of a formula after its name, the newest last
  installed=$(brew list --versions "$formula" 2> /dev/null | awk '{ print $NF }' || true)
  status="same"
  if [ -z "$installed" ]; then
    status="not installed"
  elif [ "$installed" != "$expected" ]; then
    status="changed"
  fi
  printf '%-20s installed %-12s listed %-12s %s\n' "$formula" "${installed:--}" "$expected" "$status"
  rows="$rows| $formula | ${installed:--} | $expected | $status |"$'\n'
  if [ "$status" != "same" ]; then
    changed=1
    echo "::warning title=brew formula of the macOS build ($architecture)::$formula is ${installed:-not installed} on this runner and brew-versions.txt has $expected"
  fi
done < <(grep -Ev '^[[:space:]]*(#|$)' "$list")

if [ -n "${GITHUB_STEP_SUMMARY:-}" ]; then
  {
    echo "### Brew formulae of the macOS build ($architecture)"
    echo
    echo "| formula | installed | listed | |"
    echo "| --- | --- | --- | --- |"
    printf '%s' "$rows"
  } >> "$GITHUB_STEP_SUMMARY"
fi

if [ "$changed" -ne 0 ]; then
  echo "some formulae are not the ones of $list: see the notes of the file"
  [ "${BREW_VERSIONS_STRICT:-0}" = "1" ] && exit 1
fi
exit 0
