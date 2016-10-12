/****************************************************
* memory.c
*
* author: ShuTing Guo
*
* date: 9/18/2016
*
* Description: provided memory-manupulation functions 
*              including memory memory zero out, and
*              memory reverse.
*
*****************************************************/

#include <stdio.h>
#include <stdint.h>
#include "memory.h"

/****************************************************
* @name: my_memmove
*
* @description: copy data from one memory to the other 
*               
* @param: src -- pointer to the source address
*         dst -- pointer to the destination address
*         length -- lenth of memory bytes to copy
*
* @return:SUCCESS/ERROR 
*/

int8_t my_memmove(uint8_t * src, uint8_t * dst, int32_t length){
    uint32_t i;
    uint8_t * psrc = (uint8_t *) src; 	
    uint8_t * pdst = (uint8_t *) dst;
	if (length == 0)
        return ERROR;
    if((NULL==src)||(NULL==dst))
	return ERROR;
    
    if ((pdst <= psrc) || (pdst > (psrc+length))){ //forward copy
	for (i=0;i<length;i++){
	    *pdst = *psrc;
	    pdst++;
	    psrc++;
	}
    }
    else{				//backward copy
        psrc += length-1;
	pdst += length-1;
	for (i=0;i<length;i++){
	    *pdst = *psrc;
            pdst--;
	    psrc--;
	}
    }
    return SUCCESS;
}

/****************************************************
* @name: my_memzero
*
* @description: zero out memory 
*               
* @param: src -- pointer to the memory address
*         length -- lenth of memory bytes to zero out
*
* @return:SUCCESS/ERROR 
*/

int8_t my_memzero(uint8_t * src, uint32_t length){
    uint32_t i;
	if(src == NULL)
        return ERROR;
    
    for(i = 0;i < length;i ++)
        *(src + i) = 0;
    return SUCCESS;
}

/****************************************************
* @name: my_reverse
*
* @description: reverse the order of certain bytes 
*               starting from a memory location 
*               
* @param: src -- pointer to the starting memory address
*         length -- lenth of memory bytes to reverse
*
* @return:SUCCESS/ERROR 
*/

int8_t my_reverse(uint8_t * str, uint32_t length){
    uint8_t temp;
    uint32_t i=0;
    if (str == NULL)
        return ERROR;
    while((i) < (length-1-i)){
        temp = *(str+i);
        *(str+i) = *(str+length-1-i);
        *(str+length-1-i) = temp;
        i++;
    }
    return SUCCESS;
}
