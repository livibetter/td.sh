if ENABLE_BASH_LOADABLE
  ALL_DEPS = td
endif

all: $(ALL_DEPS)

td: libtd.o td.o
	gcc -shared -Wl,-soname,$@ -o $@ $^

libtd.o: $(srcdir)/../lib/td.c
	gcc -std=c99 -g -O2 -fPIC -I$(srcdir)/../lib -c -o $@ $<

td.o: $(srcdir)/../src/main.c
	gcc -std=gnu99 -g -O2 -fPIC -DBASH_LOADABLE -I@BASH_INC@ -I$(srcdir)/../lib -c -o $@ $<

CLEANFILES = td libtd.o td.o
