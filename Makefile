CFLAGS=-m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector
CFLAGS64=$(CFLAGS) -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64

all: main main64

test: all
	LD_LIBRARY_PATH=$$PWD/32 ./main
	LD_LIBRARY_PATH=$$PWD/64 ./main64
	@echo -e "\e[34m### this one gets garbage\e[m"
	LD_LIBRARY_PATH=$$PWD/32 ./main64
	@echo -e "\e[34m### the following should crash\e[m"
	LD_LIBRARY_PATH=$$PWD/64 ./main

clean:
	rm -rf 32 64 main main64

32/libnow.so.1: now.c
	@mkdir -p 32
	$(CC) -o $@ now.c $(CFLAGS) -shared -Wl,-soname,libnow.so.1

32/libnow.so: 32/libnow.so.1
	ln -sf libnow.so.1 32/libnow.so

64/libnow.so.1: now.c
	@mkdir -p 64
	$(CC) -o $@ now.c $(CFLAGS64) -shared -Wl,-soname,libnow.so.1

64/libnow.so: 64/libnow.so.1
	ln -sf libnow.so.1 64/libnow.so

main: main.c 32/libnow.so
	$(CC) -o $@ main.c $(CFLAGS) -L32 -lnow

main64: main.c 64/libnow.so
	$(CC) -o $@ main.c $(CFLAGS64) -L64 -lnow

.PHONY: all test clean
