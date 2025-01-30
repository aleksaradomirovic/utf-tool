CFLAGS += -O3 -std=gnu23 -Wall

.PHONY: all clean

all: strtest

clean:
	rm -rf libutf.so strtest *.o

libutf.so: utf.c utf.h
	$(CC) $(CFLAGS) -shared -fpic utf.c -o $(@)

strtest: strtest.c libutf.so
	$(CC) $(CFLAGS) strtest.c $(shell realpath libutf.so) -o $(@)