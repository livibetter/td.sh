#!/bin/bash

TD="src/td"

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
