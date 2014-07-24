AM_CFLAGS = -std=c99 -Wall -Wextra

check_PROGRAMS = check_libtd

check_libtd_SOURCES = check_libtd.c $(top_srcdir)/lib/td.h
check_libtd_CFLAGS  = $(AM_CFLAGS) @CHECK_CFLAGS@
check_libtd_LDADD   = $(top_builddir)/lib/libtd.la @CHECK_LIBS@

DISTCLEANFILES = atconfig

check-local: run-check-programs

run-check-programs: $(check_PROGRAMS)
	for check_program in $^; do \
	  $(SHELL) "$$check_program" || exit 1; \
	done

.PHONY: run-check-programs
