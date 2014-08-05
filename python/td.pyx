cimport ctd


def sprint_td(t, print_all_numbers=False, pad_units=False, pad_char=' '):

  py_str = '\000' * 64
  py_str_bytes = py_str.encode('utf-8')
  cdef char *c_str = py_str_bytes

  ctd.sprint_td(c_str, t, print_all_numbers, pad_units, ord(pad_char[0]))

  return c_str.decode('utf-8')


def print_td(t, print_all_numbers=False, pad_units=False, pad_char=' '):

  ctd.print_td(t, print_all_numbers, pad_units, ord(pad_char[0]))
