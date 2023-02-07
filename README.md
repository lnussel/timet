Small test program and library for time_t on 32bit platforms. Both program and
library are compiled with 32bit as well as 64bit time_t and then
combined. The ABI changes but the linker will happily load even
invalid combinations. The program calls three library functions, one
that returns a value, one that puts the value in a pointer and one that gets a
time_t as parameter. A mismatch mix may lead to garbage passed around or crash.

    $ uname -m
    x86_64
    $ make test
    cc -o 32/libnow.so.1 now.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 32/libnow.so
    cc -o main main.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -L32 -lnow
    cc -o 64/libnow.so.1 now.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 64/libnow.so
    cc -o main64 main.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -L64 -lnow
    LD_LIBRARY_PATH=$PWD/32 ./main
    32bit time_t program using a 32bit time_t library
    ret: 32323232
    ptr: 32323232
    prm: 0 32323232 0
    LD_LIBRARY_PATH=$PWD/64 ./main64
    64bit time_t program using a 64bit time_t library
    ret: 6464646432323232
    ptr: 6464646432323232
    prm: 0 6464646432323232 0
    ### this one gets garbage
    LD_LIBRARY_PATH=$PWD/32 ./main64
    64bit time_t program using a 32bit time_t library
    ret: 0c0debad32323232
    ptr: 0c0debad32323232
    prm: 0 32323232 64646464
    ### the following should crash
    LD_LIBRARY_PATH=$PWD/64 ./main
    32bit time_t program using a 64bit time_t library
    ret: 32323232
    ptr: 32323232
    prm: 0 0000000032323232 8049102
    make: *** [Makefile:12: test] Segmentation fault (core dumped)


    $ uname -m
    armv7l
    $ make test
    LD_LIBRARY_PATH=$PWD/32 ./main
    32bit time_t program using a 32bit time_t library
    ret: 32323232
    ptr: 32323232
    prm: 0 32323232 0
    LD_LIBRARY_PATH=$PWD/64 ./main64
    64bit time_t program using a 64bit time_t library
    ret: 6464646432323232
    ptr: 6464646432323232
    prm: 0 6464646432323232 0
    ### this one gets garbage
    LD_LIBRARY_PATH=$PWD/32 ./main64
    64bit time_t program using a 32bit time_t library
    ret: 0000000032323232
    ptr: 0000000032323232
    prm: 0 00000000 32323232
    ### the following should crash
    LD_LIBRARY_PATH=$PWD/64 ./main
    32bit time_t program using a 64bit time_t library
    ret: 32323232
    ptr: 32323232
    prm: 0 0000000000000000 40
