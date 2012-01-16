#!/bin/bash

TD="./td.sh"

test_counts=0
test_failures=0

test_eq() {
  ((test_counts++))
  test_val="$1"
  test_ans="$2"
  shift 2
  result="$("$TD" "$@" "$test_val")"
  if [[ "$result" == "$test_ans" ]]; then
    echo "Passed: "$test_val" => \"$result\""
    return 0
  else
    ((test_failures++))
    echo "Failed: "$test_val" => \"$result\" != \"$test_ans\"" >&2
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
# Paddings
test_eq 1 "1 second " -P
test_eq 60 "1 minute " -P
test_eq 60 " 1 minute " -P -p
test_eq 60 "01 minute " -P -p0
test_eq 60 " 0 days  0 hours  1 minute  0 seconds" -p -a
test_eq 60 "0 days 0 hours 1 minute  0 seconds" -P -a
test_eq 60 " 0 days  0 hours  1 minute   0 seconds" -P -p -a

echo "$test_failures failures of $test_counts tests."

# Performance test

trap 'kill $tmpcount_pid ; rm "$tmpcount" ; exit 130' INT

echo -n "Please wait for 5 seconds..."
tmpcount="$(mktemp)"
( trap exit TERM; source td.sh; while :; do print_td 180122; echo >> "$tmpcount"; done ) &>/dev/null &
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
