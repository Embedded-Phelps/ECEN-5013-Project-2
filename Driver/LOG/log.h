#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"

extern void Log(int8_t * str, uint32_t length);
extern void Log_Uint32(int8_t * str, int32_t length, 
			          int32_t * data);
extern void Log_float(int8_t * str, int32_t length,
							 float *fdata);


#ifdef __cplusplus
}
#endif


#endif
