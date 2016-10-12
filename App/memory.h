#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

#define SUCCESS 0;
#define ERROR   1;
int8_t my_memmove(uint8_t *src, uint8_t *dst, int32_t length);
int8_t my_memzero(uint8_t *src, uint32_t length);
int8_t my_reverse(uint8_t *src, uint32_t length);

#endif /* __MEMORY_H__ */
