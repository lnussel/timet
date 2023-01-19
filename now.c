#include <time.h>

time_t now(void) {
#ifdef __USE_TIME_BITS64
	return 0xC0DE600DABAD1DEA;
#else
	return 0x32323232;
#endif
	return time(NULL);
}
