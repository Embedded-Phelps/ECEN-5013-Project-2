#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>

uint8_t * my_itoa(uint8_t *str, int32_t data, int32_t base);
int8_t * my_ftoa(int8_t *str, float fdata);
int32_t  my_atoi(int8_t *str);
void dump_memory(uint8_t * start, uint32_t length);
uint32_t big_to_little(uint32_t data);
uint32_t little_to_big(uint32_t data);

#endif /* __DATA_H__ */
