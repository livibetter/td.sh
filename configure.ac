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

AC_ARG_ENABLE(
  [bash-loadable],
  [AS_HELP_STRING([--enable-bash-loadable=BASH_HEADER_PATH], [build Bash loadable])],
  [
    AS_IF(
      [test "x$enable_bash_loadable" != xno],
      [
        AS_IF(
          [test "x$enable_bash_loadable" == xyes],
          [AC_MSG_ERROR([please supply the path to Bash header files using --enable-bash-loadable=PATH])]
        )
        AC_MSG_CHECKING([whether Bash headers at $enable_bash_loadable])
        AS_IF(
          [test -f "$enable_bash_loadable/builtins.h"],
          [
            AC_MSG_RESULT([yes])
            BASH_INC="$enable_bash_loadable"
            enable_bash_loadable=yes
          ],
          [
            AC_MSG_RESULT([no])
            AC_MSG_ERROR([cannot find Bash header files at $enable_bash_loadable])
          ]
        )
      ]
    )
  ],
  [enable_bash_loadable=no]
)

AC_ARG_ENABLE(
  [python],
  [AS_HELP_STRING([--disable-python], [do not build Python bindings])],
  [AS_IF([test "x$enable_python" != xno], [enable_python=check])],
  [enable_python=check]
)

AC_ARG_ENABLE(
  [python2],
  [AS_HELP_STRING([--disable-python2], [do not build Python 2 binding])],
  [AS_IF([test "x$enable_python2" != xno], [enable_python2=check])],
  [enable_python2=check]
)

AC_ARG_ENABLE(
  [python3],
  [AS_HELP_STRING([--disable-python3], [do not build Python 3 binding])],
  [AS_IF([test "x$enable_python3" != xno], [enable_python3=check])],
  [enable_python3=check]
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

AS_IF(
  [test "x$enable_python" == xcheck],
  [
    AC_PATH_PROG([PYTHON2], [python2], [])
    AC_PATH_PROG([PYTHON3], [python3], [])
    AS_IF(
      [test ! -z "$PYTHON2" -a "x$enable_python2" == xcheck],
      [enable_python2=yes],
      [enable_python2=no]
    )
    AS_IF(
      [test ! -z "$PYTHON3" -a "x$enable_python3" == xcheck],
      [enable_python3=yes],
      [enable_python3=no]
    )
    AS_IF(
      [test "x$enable_python2" == xyes -o "x$enable_python3" == xyes],
      [enable_python=yes],
      [enable_python=no]
    )
  ]
)

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
  bash/Makefile
  lib/Makefile
  lib/pkgconfig/Makefile
  python/Makefile
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

AS_IF([test "x$enable_c" == xyes], [
  dnl force ${pkgconfigdir} to be set
  AS_IF([test "x$pkgconfigdir" == x], [PKG_INSTALLDIR])
  AC_CONFIG_FILES([
    lib/pkgconfig/libtd.pc
  ])
  AC_CONFIG_LINKS([
    lib/td.h:lib/td.h
  ])
], [
  enable_python=no
  with_check=no
])

AS_IF([test "x$enable_python" == xyes], [
  AC_CONFIG_LINKS([
    python/ctd.pxd:python/ctd.pxd
    python/setup.py:python/setup.py
    python/td.pyx:python/td.pyx
    tests/testsuite.td.py:tests/testsuite.td.py
  ])
], [
  enable_python2=no
  enable_python3=no
])

AC_SUBST([enable_bash])
AC_SUBST([enable_c])
AC_SUBST([enable_bash_loadable])
AC_SUBST([BASH_INC])
AC_SUBST([enable_python2])
AC_SUBST([enable_python3])

AM_CONDITIONAL([ENABLE_BASH], [test "x$enable_bash" != xno])
AM_CONDITIONAL([ENABLE_C],    [test "x$enable_c"    != xno])

AM_CONDITIONAL([ENABLE_BASH_LOADABLE], [test "x$enable_bash_loadable" != xno])

AM_CONDITIONAL([ENABLE_PYTHON2], [test "x$enable_python2" != xno])
AM_CONDITIONAL([ENABLE_PYTHON3], [test "x$enable_python3" != xno])

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
  pkgconfigdir        = ${pkgconfigdir}

  Bash headers        = ${BASH_INC}

  CC                  = ${CC}
  CFLAGS              = ${CFLAGS}
  LDFLAGS             = ${LDFLAGS}

  PYTHON2             = ${PYTHON2}
  PYTHON3             = ${PYTHON3}

  has Check           = ${has_check}

  build Bash          = ${enable_bash}
  build C             = ${enable_c}
  build Bash Loadable = ${enable_bash_loadable}
  build Python 2      = ${enable_python2}
  build Python 3      = ${enable_python3}

  with Check          = ${with_check}
])
