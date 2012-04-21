PREFIX=/usr/local
DESTDIR=

INSTDIR=$(DESTDIR)$(PREFIX)
INSTBIN=$(INSTDIR)/bin

all:
	@echo do nothing. try targets: install, uninstall, or test.

install:
	test -d $(INSTDIR) || mkdir -p $(INSTDIR)
	test -d $(INSTBIN) || mkdir -p $(INSTBIN)

	install -m 0755 td.sh $(INSTBIN)

uninstall:
	rm -f $(INSTBIN)/td.sh

test:
	./td-test.sh

.PHONY: all install uninstall test
