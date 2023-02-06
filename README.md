Small test program and library for time_t on 32bit platforms. Both program and
library are compiled with 32bit as well as 64bit time_t and then
combined. The ABI changes but the linker will happily load even
invalid combinations. The program call two library functions, one
that returns a value and one that puts the value in a pointer. A
mismatch mix may lead to garbage returned or crash.

    $ cc -o 32/libnow.so.1 now.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 32/libnow.so
    cc -o main main.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -L32 -lnow
    cc -o 64/libnow.so.1 now.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 64/libnow.so
    cc -o main64 main.c -m32 -fPIC -Wall -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -L64 -lnow
    LD_LIBRARY_PATH=$PWD/32 ./main
    32bit program using a 32bit library
    ret: 32323232
    ptr: 32323232
    LD_LIBRARY_PATH=$PWD/64 ./main64
    64bit program using a 64bit library
    ret: 6464646432323232
    ptr: 6464646432323232
    LD_LIBRARY_PATH=$PWD/32 ./main64
    64bit program using a 32bit library
    ret: 0c0debad32323232
    ptr: 0c0debad32323232
    ### the following will crash
    LD_LIBRARY_PATH=$PWD/64 ./main
    32bit program using a 64bit library
    ret: 32323232
    ptr: 32323232
    make: *** [Makefile:11: test] Segmentation fault (core dumped)
