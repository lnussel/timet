#pragma once

size_t timesize();
time_t now(void);
void nowp(time_t* t);
void uset(long a, time_t t, long b);

#ifdef __USE_TIME_BITS64
#define PRIt "016llx"
#else
#define PRIt "08lx"
#endif
