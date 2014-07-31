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
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

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
  src/td.sh
  tests/Makefile
  tests/atlocal
  tests/benchmark.sh
],[
  chmod +x src/td.sh
  chmod +x tests/benchmark.sh
])

AC_OUTPUT
