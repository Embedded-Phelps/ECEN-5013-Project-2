#include "includes.h"


void Log(int8_t * str, uint32_t length){
	while (length>0){
		uart0_SendChar(*str);
		str++;
		length--;
	}
}


void Log_Uint8(int8_t * str, uint32_t length, 
			   int32_t * data){
		int8_t temp[12];
		while (length>0){
			uart0_SendChar(*str);
			str++;
			length--;
		}
		my_itoa(temp, *data, 10);
		uart0_SendString(temp);
}

