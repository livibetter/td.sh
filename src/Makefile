all: td

td: main.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f td main.o

.PHONY: clean
