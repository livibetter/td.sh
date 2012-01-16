#!/bin/bash
# Converting seconds to human readable time duration.
# Author: Yu-Jie Lin
# BSD license

if (($# != 1)); then
	echo "Usage: $(basename "$0") <seconds|-s>
  -s: for sourcing, e.g. \`source $(basename "$0") -s\`
      then you can use \`print_td <seconds>\` in your script.
" >&2
	exit 1
fi

units=(second minute hour day)

print_td() {
	t=${1#-}
	nums=($(($t % 60)) $(($t / 60 % 60)) $(($t / 3600 % 24)) $(($t / 86400)))

	result=""
	for ((idx=${#units[@]}-1;idx>=0;idx--)) {
		((nums[idx] == 0)) && continue;
		result="$result ${nums[idx]} ${units[idx]}"
		((nums[idx] != 1)) && result="${result}s"
		}
	[[ -z "$result" ]] && result="0 seconds"
	echo "${result# }"
	}

if [[ "$1" != "-s" ]]; then
	print_td $1
fi
