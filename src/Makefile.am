# ensure all output files will be cleaned despite the used options changeing
# in invoking ./configure

bin_PROGRAMS__     = td
dist_bin_SCRIPTS__ = td.sh

if ENABLE_C
  AM_CFLAGS   = -std=c99 -Wall -Wextra
  AM_CPPFLAGS = -I$(srcdir)/../lib

  bin_PROGRAMS = $(bin_PROGRAMS__)

  td_SOURCES = main.c
  td_LDADD   = $(top_builddir)/lib/libtd.la
endif

if ENABLE_BASH
  dist_bin_SCRIPTS = $(dist_bin_SCRIPTS__)
endif

CLEANFILES = $(bin_PROGRAMS__) $(dist_bin_SCRIPTS__)
