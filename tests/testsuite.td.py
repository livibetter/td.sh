import sys

import td


if '--' in sys.argv:
  durations = sys.argv[sys.argv.index('--') + 1:]
else:
  durations = filter(lambda n: '-' not in n, sys.argv[1:])
print_all_numbers = '-a' in sys.argv
pad_units = '-P' in sys.argv
pad_char = ' ' if '-p' in sys.argv else ('0' if '-p0' in sys.argv else '\000')


for d in durations:
  if '-s' in sys.argv:
    print(td.sprint_td(int(d), print_all_numbers, pad_units, pad_char))
  else:
    td.print_td(int(d), print_all_numbers, pad_units, pad_char)
