from libcpp cimport bool


cdef extern from 'td.h':

  int sprint_td(char *, long long, bool, bool, char)
  void print_td(long long, bool, bool, char)
