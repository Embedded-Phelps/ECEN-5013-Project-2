#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <stdint.h>

extern void time_Profiler(void);
void time_Profiler_Memmove(int32_t bytes);
void time_Profiler_Memset(int32_t byte);
void time_Profiler_Reverse(int32_t byte);

#endif /* __PROFILER_H__ */
