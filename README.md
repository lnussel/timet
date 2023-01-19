    $ make
    cc -o 32/libnow.so.1 now.c -m32 -fPIC -Wall -g -O0 -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 32/libnow.so 
    cc -o main main.c -m32 -fPIC -Wall -g -O0 -L32 -lnow
    cc -o 64/libnow.so.1 now.c -m32 -fPIC -Wall -g -O0 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -shared -Wl,-soname,libnow.so.1
    ln -sf libnow.so.1 64/libnow.so 
    cc -o main64 main.c -m32 -fPIC -Wall -g -O0 -D_TIME_BITS=64 -D_FILE_OFFSET_BITS=64 -L64 -lnow
    $ make test
    LD_LIBRARY_PATH=$PWD/32 ./main
    sizeof(time_t): 4
    now: deadbeef
    LD_LIBRARY_PATH=$PWD/64 ./main
    sizeof(time_t): 4
    now: abad1dea
    LD_LIBRARY_PATH=$PWD/32 ./main64
    sizeof(time_t): 8
    now: f7ef4880deadbeef
    LD_LIBRARY_PATH=$PWD/64 ./main64
    sizeof(time_t): 8
    now: c001d00dabad1dea
