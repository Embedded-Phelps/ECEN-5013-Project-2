#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"

extern void log_Str(uint8_t *str);
extern void log_Mem(int8_t * source, uint32_t num);
extern void log_Int(uint8_t * str, int32_t data);
extern void log_Float(int8_t * str, float fdata);


#ifdef __cplusplus
}
#endif


#endif
