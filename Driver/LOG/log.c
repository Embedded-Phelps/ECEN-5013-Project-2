#include "includes.h"


void Log(int8_t * str, uint32_t length){
	while (length>0){

#ifdef _BBB
		printf("%c",*str);
#else
		uart0_SendChar(*str);
#endif
		str++;
		length--;
	}
}


void Log_Uint32(int8_t * str, int32_t length,	
			   int32_t * data){
		int8_t temp[12];
		while (length>0){
#ifdef _BBB
		printf("%c",*str);
#else
		uart0_SendChar(*str);
#endif
			str++;
			length--;
		}
		
#ifdef _BBB
		printf("%d",*data);
#else
		my_itoa(temp, *data, 10);
		uart0_SendString(temp);
#endif		
		//uart0_SendString(temp);
}

void Log_float(int8_t * str, int32_t length,
							 float *fdata){
	int8_t temp[32];
	while (length>0){
#ifdef _BBB
	printf("%c",*str);
#else
	uart0_SendChar(*str);
#endif
			str++;
			length--;
	}
#ifdef _BBB
	printf("%f",*fdata);
#else
	my_ftoa(temp, *fdata);
	uart0_SendString(temp);
#endif
	
}