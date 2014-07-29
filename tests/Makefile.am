AM_CFLAGS = -std=c99 -Wall -Wextra

check_PROGRAMS = check_libtd

check_libtd_SOURCES = check_libtd.c $(top_srcdir)/lib/td.h
check_libtd_CFLAGS  = $(AM_CFLAGS) @CHECK_CFLAGS@
check_libtd_LDADD   = $(top_builddir)/lib/libtd.la @CHECK_LIBS@

# Modified from Autoconf manual
# The `:;' works around a Bash 3.2 bug when the output is not writable.
$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:;{ \
	  echo '# Signature of the current package.' && \
	  echo 'm4_define([AT_PACKAGE_NAME],' && \
	  echo '  [$(PACKAGE_NAME)])' && \
	  echo 'm4_define([AT_PACKAGE_TARNAME],' && \
	  echo '  [$(PACKAGE_TARNAME)])' && \
	  echo 'm4_define([AT_PACKAGE_VERSION],' && \
	  echo '  [$(PACKAGE_VERSION)])' && \
	  echo 'm4_define([AT_PACKAGE_STRING],' && \
	  echo '  [$(PACKAGE_STRING)])' && \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
	  echo '  [$(PACKAGE_BUGREPORT)])'; \
	  echo 'm4_define([AT_PACKAGE_URL],' && \
	  echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

EXTRA_DIST = \
  $(srcdir)/package.m4 \
  atlocal.in \
  $(TESTSUITE_ATS) \
  $(TESTSUITES) \
  benchmark.sh.in
TESTSUITES = \
  $(srcdir)/testsuite.td \
  $(srcdir)/testsuite.td.sh
TESTSUITE_ATS = \
  $(srcdir)/testsuite.td.at \
  $(srcdir)/testsuite.td.sh.at

check-local: atconfig atlocal run-check-programs $(TESTSUITES)
	for testsuite in $(TESTSUITES); do \
	  $(SHELL) "$$testsuite" $(TESTSUITEFLAGS); \
	done

run-check-programs: $(check_PROGRAMS)
	for check_program in $^; do \
	  $(SHELL) "$$check_program" || exit 1; \
	done

installcheck-local: atconfig atlocal $(TESTSUITES)
	for testsuite in $(TESTSUITES); do \
	  $(SHELL) "$$testsuite" AUTOTEST_PATH='$(bindir)' \
	    $(TESTSUITEFLAGS); \
	done

DISTCLEANFILES = atconfig

clean-local:
	for testsuite in $(TESTSUITES); do \
	  test ! -f "$$testsuite" || \
	    $(SHELL) "$$testsuite" --clean; \
	done

AUTOM4TE = $(SHELL) $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITES): $(TESTSUITE_ATS) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@

benchmark-local:
	$(SHELL) $(srcdir)/benchmark.sh

.PHONY: run-check-programs
