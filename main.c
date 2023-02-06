#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include "main.h"

static int ok;

int main(void) {
	time_t t = 0;
	ok = sizeof(time_t) == timesize();
	printf("\e[%sm%zubit time_t program using a %zubit time_t library\e[m\n", ok?"32":"31", sizeof(time_t)<<3, timesize()<<3);
#ifdef __i386__
	__asm__ __volatile__ ("movl $0xC0DEBAD, %edx");
#endif
	t = now();
	printf("ret: %" PRIt "\n", t);
	nowp(&t);
	printf("ptr: %" PRIt "\n", t);
	uset(0,
#ifdef __USE_TIME_BITS64
	0x6464646432323232,
#else
	0x32323232,
#endif
	0);

	return 0;
}
