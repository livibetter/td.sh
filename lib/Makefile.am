# ensure all output files will be cleaned despite the used options changeing
# in invoking ./configure

lib_LTLIBRARIES__ = libtd.la

if ENABLE_C
  AM_CFLAGS = -std=c99 -Wall -Wextra

  lib_LTLIBRARIES = $(lib_LTLIBRARIES__)

  libtd_la_SOURCES = td.c td.h
endif

CLEANFILES = $(lib_LTLIBRARIES__)
