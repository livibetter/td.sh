#!/bin/bash

TD="src/td"

test_counts=0
test_failures=0

test_eq() {
  ((test_counts++))
  test_val="$1"
  test_ans="$2"
  shift 2
  result="$("$TD" "$@" -- $test_val)"
  if [[ "$result" == "$test_ans" ]]; then
    printf "Passed: %10s %-10s => %q\n" "$test_val" "$*" "$result"
    return 0
  else
    ((test_failures++))
    printf "Failed: %10s %-10s => %q != %q\n" "$test_val" "$*" "$result" "$test_ans" >&2
    return 1
  fi
  }

test_eq "1 60" $'1 second \n1 minute ' -P

echo "$test_failures failures of $test_counts tests."

# Performance test

trap 'kill $tmpcount_pid ; rm "$tmpcount" ; exit 130' INT

echo -n "Please wait for 5 seconds..."
tmpcount="$(mktemp)"
( trap exit TERM; while :; do $TD 180122; echo >> "$tmpcount"; done ) &>/dev/null &
tmpcount_pid=$!
sleep 5
kill $tmpcount_pid
echo -ne "\e[2K\e[0G$(bc <<< "$(wc -l < "$tmpcount") / 5") conversions per second.\n"
rm "$tmpcount"
