#include "includes.h"

#define SET_LED_GREEN(x)   TPM2_C1V = (x)
#define SET_LED_RED(x)     TPM2_C0V = (x)
#define SET_LED_BLUE(x)    TPM0_C1V = (x)

int main(){
	/* Configure system clockSystem */
	int32_t test=123;
	//int i = 19, j=0xfff;
	//SystemCoreClockUpdate();    	
	
	/* Enable the clock gate to ALL the Port module */
	PORT_ENABLE_CLK(A);		
	PORT_ENABLE_CLK(B);
	PORT_ENABLE_CLK(C);
	PORT_ENABLE_CLK(D);
	PORT_ENABLE_CLK(E);
	
	/* Initialize uart0 */
	uart0_Init(9600,0,0,8,1);
	
	/* Initialize LED GPIO */
	//led_Gpio_Init();
	
	/* Initialize TPM */
	//tpm_Init();
	
	while(1){
		Log("Come on", 7);
		Log_Uint8("...",3,&test);
		/*while(i < 1800) {
            while(j--) {};
            j = 0xfff;
            SET_LED_GREEN(i);
            SET_LED_RED(i);
            SET_LED_BLUE(i);
            i++;
        }
        while(i > 19) {
            while(j--) {};
            j = 0xfff;
            SET_LED_GREEN(i);
            SET_LED_RED(i);
            SET_LED_BLUE(i);
            i--;
        }*/
	};
}

