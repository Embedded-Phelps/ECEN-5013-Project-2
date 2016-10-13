#include "includes.h"

#define SET_LED_GREEN(x)   TPM2_C1V = (x)
#define SET_LED_RED(x)     TPM2_C0V = (x)
#define SET_LED_BLUE(x)    TPM0_C1V = (x)

extern uint8_t serial_flag;
extern uint8_t rx_in[5];
static uint8_t led;
static int32_t redbrightness,greenbrightness,bluebrightness;

int main(){   	
  int32_t test1=200, test2=4096, test3=123456;
	float test4=1543.321;
	
	enum ledcolor{RED,GREEN,BLUE};
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
	//uart0_SendString("For this part, you will have to take the Circular buffer code you have written\n\r in the previous assignments and this lab and connect it into our UART interface.\n\r");
	/* Initialize LED GPIO */
	led_Gpio_Init();
	
	/* Initialize TPM */
	tpm_Init();
	
	/* Initialize PIT */
	pit_Init();

	//time_Profiler();
	/*
	Log("Testing123, Serial Print Test, no params\r\n", 42);
	Log_Uint32("This is an integer: ", 20, &test1);
	Log("\r\n",2);
	Log_Uint32("This is an integer: ", 20, &test2);
	Log("\r\n",2);
	Log_Uint32("This is an integer: ", 20, &test3);
	Log("\r\n",2);
	Log_float("This is an integer: ", 20, &test4);
	Log("\r\n",2);*/
	
	
	//Log("Please set LED brightness", 25);
	while(1){
		if(serial_flag){
			
			switch (rx_in[0]){
				case 'r':
					led=RED;
					redbrightness = my_atoi(&rx_in[1]);
					SET_LED_RED(redbrightness);
					break;
				case 'g':
					led=GREEN;
					greenbrightness = my_atoi(&rx_in[1]);
					SET_LED_GREEN(greenbrightness);
					break;
				case 'b':
					led=BLUE;
					bluebrightness = my_atoi(&rx_in[1]);
					SET_LED_BLUE(bluebrightness);
					break;
				case 'w':
					if (led==RED)
						SET_LED_RED(redbrightness+100);
					if (led==GREEN)
						SET_LED_GREEN(greenbrightness+100);
					if(led==BLUE)
						SET_LED_BLUE(bluebrightness+100);
					break;
				case 's':
					if (led==RED)
						SET_LED_RED(redbrightness-100);
					if (led==GREEN)
						SET_LED_GREEN(greenbrightness-100);
					if(led==BLUE)
						SET_LED_BLUE(bluebrightness-100);
					break;
				case 'e':
					Log("\r\nechoing...\r\n", 14);
					uart0_SendString(&rx_in[1]);
					Log("\r\n",2);
				default:;
			}
			my_memzero(rx_in,6);
			serial_flag=0;
			Log("\r\n", 2);
		}
	}
}

