if ENABLE_BASH_LOADABLE
  ALL_DEPS = td
endif

all: $(ALL_DEPS)

install-exec-hook: $(ALL_DEPS)
if ENABLE_BASH_LOADABLE
	$(INSTALL) -m755 td $(DESTDIR)$(bindir)/td.bash
endif

uninstall-local:
if ENABLE_BASH_LOADABLE
	$(RM) $(DESTDIR)$(bindir)/td.bash
endif

td: libtd.o td.o
	gcc -shared -Wl,-soname,$@ -o $@ $^

libtd.o: $(srcdir)/../lib/td.c
	gcc -std=c99 -g -O2 -fPIC -I$(srcdir)/../lib -c -o $@ $<

td.o: $(srcdir)/../src/main.c
	gcc -std=gnu99 -g -O2 -fPIC -DBASH_LOADABLE -I@BASH_INC@ -I$(srcdir)/../lib -c -o $@ $<

CLEANFILES = td libtd.o td.o
