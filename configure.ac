#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([td], [0.0.0], [livibetter@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_EXTRA_RECURSIVE_TARGETS([benchmark])
AM_PROG_AR
LT_INIT

AC_ARG_ENABLE(
  [bash],
  [AS_HELP_STRING([--disable-bash], [do not build Bash implementation])],
  [AS_IF([test "x$enable_bash" != xno], [enable_bash=yes])],
  [enable_bash=yes]
)

AC_ARG_ENABLE(
  [c],
  [AS_HELP_STRING([--disable-c], [do not build C implementation])],
  [AS_IF([test "x$enable_c" != xno], [enable_c=yes])],
  [enable_c=yes]
)

AC_ARG_WITH(
  [check],
  [AS_HELP_STRING([--without-check], [do not run Check unittest])],
  [AS_IF(
    [test "x$with_check" != xno],
    [with_check=check],
    [with_check=no; has_check=skipped]
  )],
  [with_check=check]
)

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_TESTDIR([tests])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CC_C99
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for libraries.
AS_IF(
  [test "x$with_check" == xcheck],
  [PKG_CHECK_MODULES(
    [CHECK],
    [check >= 0.9.4],
    [has_check=yes; with_check=yes],
    [has_check=no;  with_check=no]
  )],
)

# Checks for header files.
AC_CHECK_HEADERS([ \
  stdlib.h \
  string.h \
  unistd.h \
])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([
  Makefile
  lib/Makefile
  src/Makefile
  tests/Makefile
  tests/atlocal
  tests/benchmark.sh
],[
  chmod +x tests/benchmark.sh
])

AS_IF([test "x$enable_bash" != xno], [
  AC_CONFIG_FILES([
    src/td.sh
  ], [
    chmod +x src/td.sh
  ])
])

AC_SUBST([enable_bash])
AC_SUBST([enable_c])

AM_CONDITIONAL([ENABLE_BASH], [test "x$enable_bash" != xno])
AM_CONDITIONAL([ENABLE_C],    [test "x$enable_c"    != xno])

AM_CONDITIONAL([WITH_CHECK],  [test "x$with_check"  != xno])

AC_OUTPUT

AC_MSG_RESULT([
  package             = ${PACKAGE}
  version             = ${VERSION}

  prefix              = ${prefix}
  exec_prefix         = ${exec_prefix}

  bindir              = ${bindir}
  libdir              = ${libdir}
  includedir          = ${includedir}

  CC                  = ${CC}
  CFLAGS              = ${CFLAGS}
  LDFLAGS             = ${LDFLAGS}

  has Check           = ${has_check}

  build Bash          = ${enable_bash}
  build C             = ${enable_c}

  with Check          = ${with_check}
])
