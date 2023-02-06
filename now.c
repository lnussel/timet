#include <time.h>

size_t timesize() {
	return sizeof(time_t);
}

time_t now(void) {
#ifdef __USE_TIME_BITS64
	return 0x6464646432323232;
#else
	return 0x32323232;
#endif
	return time(NULL);
}

void nowp(time_t* t) {
	*t = now();
}
