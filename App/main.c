/***************************************************************************
 *
 *	Filename: 		main.c
 *  Description:  	main file for the project
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/

#include "includes.h"

uint8_t value;
uint32_t brightness;

/* LED color and brightness setting function */
void led_Ctl(uint8_t color){
	uint8_t temp=1;
	uint8_t a[10];
	uint8_t i=0;
	
	while(temp!='\0'){
		cb_Dequeue(rx_buf, &temp);
		a[i]=temp;
		i++;
	}
	i=0;
	a[i]='\0';
	brightness=my_itoa(a);
	if(brightness>100)
		brightness=100;
	brightness=(uint32_t)2000*(brightness/100)
	switch(color){
		case 'r':	SET_LED_RED(brightness);
					break;
		case 'g':	SET_LED_GREEN(brightness);
					break;
		case 'b':	SET_LED_BLUE(brightness);
					break;
		default:;
	}
}

/* Echo mode function */
void echo(){
	uint8_t temp=1;
	uint8_t str[100];
	uint8_t i=0;
	while(temp!='\0'){
		cb_Dequeue(rx_buf, &temp);
		a[i]=temp;
		i++;
	}
	i=0;
	a[i]='\0';
	log_Str(str);
}

int main(){   	
	
	/* Enable system interrupt */                                     
	__enable_irq();
	
	/* Enable the clock gate to ALL the Port module */
	PORT_ENABLE_CLK(A);		
	PORT_ENABLE_CLK(B);
	PORT_ENABLE_CLK(C);
	PORT_ENABLE_CLK(D);
	PORT_ENABLE_CLK(E);
	
	/* Initialize uart0 */
	uart0_Init(9600,0,0,8,1);
	
	/* Initialize LED GPIO */
	led_Gpio_Init();
	
	/* Initialize TPM */
	tpm_Init();
	
	/* Initialize PIT */
	pit_Init();
	
#if LOG_TEST
	int8_t test1=200; 
	uint16_t test2=4096; 
	uint32_t test3=123456;
	float test4=1543.321;
	log_Str("Testing123, Serial Print Test, no params\n");
	log_Int("This is an integer number: ", test1);
	log_Int("\nThis is an integer number: ", test2);
	log_Int("\nThis is an integer number: ", test3);
	log_Float("\nThis is a floating point number: ", test4);
#endif
	
#if CIRCBUF_UNITTEST
	circBuf_UnitTest();
#endif

#if TIME_PROFILE
	time_Profiler();
#endif
	
	while(1){
	/* checking for signals from terminal */
		if(cb_IsEmpty(rx_buf)!=EMPTY){
			cb_Dequeue(rx_buf, &value);
	/* command to set led color and brightness */
			if((value=='r')&&(value=='g')&&(value=='b'))
				led_Ctl(value);
	/* command to strengthen led brightness */
			else if (value=='w'){
				if(brightness>95)
					brightness=100;
				else
					brightness += 5;
				brightness = (uint32_t)2000*(brightness/100);
				SET_LED_RED(brightness);
				SET_LED_GREEN(brightness);
				SET_LED_BLUE(brightness);
				cb_Dequeue(rx_buf, &value);  //get rid of the '\0' at the end of the command
			}
	/* command to weaken led brightness */
			else if (value=='s'){
				if(brightness<5)
					brightness=0;
				else
					brightness -= 5;
				brightness = (uint32_t)2000*(brightness/100);
				SET_LED_RED(brightness);
				SET_LED_GREEN(brightness);
				SET_LED_BLUE(brightness);
				cb_Dequeue(rx_buf, &value);  //get rid of the '\0' at the end of the command
			}
	/* command to enter echo mode */
			else if (value=='e')
				echo();
	/* unrecogonized commands */
			else
				log_Str("Command error\n");
		}
	}
}

