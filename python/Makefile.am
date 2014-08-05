EXTRA_DIST = \
  ctd.pxd \
  setup.py \
  td.pyx

all-local:
if ENABLE_PYTHON2
	cd $(abs_top_builddir)/python; \
	CFLAGS="-I$(abs_top_builddir)/lib" \
	LDFLAGS="-L$(abs_top_builddir)/lib/.libs" \
	@PYTHON2@ setup.py build_ext --inplace
endif
if ENABLE_PYTHON3
	cd $(abs_top_builddir)/python; \
	CFLAGS="-I$(abs_top_builddir)/lib" \
	LDFLAGS="-L$(abs_top_builddir)/lib/.libs" \
	@PYTHON3@ setup.py build_ext --inplace
endif

clean-local:
	rm -rf *.so

distclean-local:
	rm -rf build

DISTCLEANFILES = td.c
