#include "includes.h"

void log_Str(uint8_t *str){
#ifdef _BBB
	printf("%s", str);
#else
	UART0_MemMapPtr uartPtr = UART0_BASE_PTR;
	while(*str != '\0')
			cb_Enqueue(tx_buf, *str++);
	if((cb_IsEmpty(tx_buf)!=EMPTY)&&(UART0_C2_REG(uartPtr) & UART0_C2_TIE_MASK))
		UART0_C2_REG(uartPtr) |= UART0_C2_TIE_MASK;
#endif
}

void log_Mem(int8_t * source, uint32_t num){

#ifdef _BBB
	while (num>0){
		printf("%c",*str++);
		num--;
	}
#else
	UART0_MemMapPtr uartPtr = UART0_BASE_PTR;
	while(num>0){
		cb_Enqueue(tx_buf, *source++);
		num--;
	}
	if((cb_IsEmpty(tx_buf)!=EMPTY)&&(UART0_C2_REG(uartPtr) & UART0_C2_TIE_MASK))
		UART0_C2_REG(uartPtr) |= UART0_C2_TIE_MASK;
#endif
		
}


void log_Int(uint8_t * str, int32_t data){
		
#ifdef _BBB
	printf("%s%d", str, data);
#else
	int8_t temp[12];
	int8_t temp[12];
	my_itoa(temp, data, 10);
	log_Str(str);
	log_Str(temp);
#endif		
	
}

void log_Float(int8_t * str, float fdata){

#ifdef _BBB
	printf("%s%f",str, fdata);
#else
	int8_t temp[32];	
	my_ftoa(temp, fdata);
	log_Str(str);
	log_Str(temp);
#endif
}