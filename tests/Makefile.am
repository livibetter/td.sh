# ensure all output files will be cleaned despite the used options changeing
# in invoking ./configure

check_PROGRAMS__ = check_libtd

if ENABLE_C
if WITH_CHECK
  AM_CFLAGS = -std=c99 -Wall -Wextra

  check_PROGRAMS = $(check_PROGRAMS__)

  check_libtd_SOURCES = check_libtd.c $(top_srcdir)/lib/td.h
  check_libtd_CFLAGS  = $(AM_CFLAGS) @CHECK_CFLAGS@
  check_libtd_LDADD   = $(top_builddir)/lib/libtd.la @CHECK_LIBS@
endif
endif

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
  $(TESTSUITE) \
  testsuite.td.py \
  benchmark.sh.in
TESTSUITE = $(srcdir)/testsuite
TESTSUITE_ATS = \
  $(srcdir)/testsuite.at \
  $(srcdir)/testsuite.td.at

check-local: $(TESTSUITE_ATS) atconfig atlocal $(TESTSUITE) run-check-programs
	$(SHELL) '$(TESTSUITE)' \
	  --enable-bash=$(enable_bash) \
	  --enable-c=$(enable_c) \
	  --enable-bash-loadable=$(enable_bash_loadable) \
	  --enable-python2=$(enable_python2) \
	  --enable-python3=$(enable_python3) \
	  $(TESTSUITEFLAGS)

run-check-programs: $(check_PROGRAMS)
if ENABLE_C
if WITH_CHECK
	for check_program in $^; do \
	  $(SHELL) "$$check_program" || exit 1; \
	done
endif
endif

installcheck-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' \
	  $(TESTSUITEFLAGS)

DISTCLEANFILES = atconfig
CLEANFILES = $(check_PROGRAMS__)

clean-local:
	test ! -f '$(TESTSUITE)' || \
	  $(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(TESTSUITE_ATS) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@

benchmark-local:
	$(SHELL) $(srcdir)/benchmark.sh

.PHONY: run-check-programs
