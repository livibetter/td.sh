#!/bin/bash

TD="./td.sh"

test_counts=0
test_failures=0

test_eq() {
  ((test_counts++))
  result="$("$TD" "$1")"
  if [[ "$result" == "$2" ]]; then
    echo "Passed: $1 => \"$result\""
    return 0
  else
    ((test_failures++))
    echo "Failed: $1 => \"$result\" != \"$2\"" >&2
    return 1
  fi
  }

test_eq 0 "0 seconds"
test_eq 1 "1 second"
test_eq -1 "1 second"
test_eq 2 "2 seconds"
test_eq 60 "1 minute"
test_eq 61 "1 minute 1 second"
test_eq 3599 "59 minutes 59 seconds"
test_eq 3600 "1 hour"
test_eq 3601 "1 hour 1 second"
test_eq 3660 "1 hour 1 minute"
test_eq 3661 "1 hour 1 minute 1 second"
test_eq 86400 "1 day"
test_eq "$((86400 + 86400 - 1))" "1 day 23 hours 59 minutes 59 seconds"
test_eq "$((2 * 86400 + 86400 - 1))" "2 days 23 hours 59 minutes 59 seconds"
test_eq "$((366 * 86400 + 1))" "366 days 1 second"

echo "$test_failures failures of $test_counts tests."

# Performance test

trap 'kill $tmpcount_pid ; rm "$tmpcount" ; exit 130' INT

echo -n "Please wait for 5 seconds..."
tmpcount="$(mktemp)"
( trap exit TERM; source td.sh -s; while :; do print_td 180122; echo >> "$tmpcount"; done ) &>/dev/null &
tmpcount_pid=$!
sleep 5
kill $tmpcount_pid
echo -ne "\e[2K\e[0G$(bc <<< "$(wc -l < "$tmpcount") / 5") conversions per second via function calls.\n"
rm "$tmpcount"

echo -n "Please wait for 5 seconds..."
tmpcount="$(mktemp)"
( trap exit TERM; while :; do ./td.sh 180122; echo >> "$tmpcount"; done ) &>/dev/null &
tmpcount_pid=$!
sleep 5
kill $tmpcount_pid
echo -ne "\e[2K\e[0G$(bc <<< "$(wc -l < "$tmpcount") / 5") conversions per second via script executions.\n"
rm "$tmpcount"
