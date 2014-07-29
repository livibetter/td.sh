AM_CFLAGS = -std=c99 -Wall -Wextra
AM_CPPFLAGS = -I$(srcdir)/../lib

bin_PROGRAMS = td
dist_bin_SCRIPTS = td.sh

td_SOURCES = main.c
td_LDADD = $(top_builddir)/lib/libtd.la

CLEANFILES = $(dist_bin_SCRIPTS)
