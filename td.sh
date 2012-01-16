#!/bin/bash
# Converting seconds to human readable time duration.
# Copyright (c) 2010, 2012 Yu-Jie Lin
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
