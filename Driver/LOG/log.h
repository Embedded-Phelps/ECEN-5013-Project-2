#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"

extern void Log(int8_t * str, uint32_t length);
extern void Log_Uint8(int8_t * str, uint32_t length, 
			          int32_t * data);


#ifdef __cplusplus
}
#endif


#endif
