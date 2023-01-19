#include <stdio.h>
#include <inttypes.h>
#include <time.h>

time_t now(void);

#ifdef __USE_TIME_BITS64
#define PRIt "016llx"
#else
#define PRIt "08lx"
#endif

int main(void) {
	printf("sizeof(time_t): %u\n", sizeof(time_t));
	printf("now: %" PRIt "\n", now());
	return 0;
}
