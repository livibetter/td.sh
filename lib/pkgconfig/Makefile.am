# ensure all output files will be cleaned despite the used options changeing
# in invoking ./configure

pkgconfig_DATA__ = libtd.pc

if ENABLE_C
  pkgconfig_DATA = $(pkgconfig_DATA__)
endif

CLEANFILES = $(pkgconfig_DATA__)
