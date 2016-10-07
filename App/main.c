#include "include.h"

int main(){
	/* Configure system clockSystem */
	CoreClockUpdate();	
	
	/* Enable the clock gate to ALL the Port module */
	PORT_ENABLE_CLK(PTA);		
	PORT_ENABLE_CLK(PTB);
	PORT_ENABLE_CLK(PTC);
	PORT_ENABLE_CLK(PTD);
	PORT_ENABLE_CLK(PTE);
	
	/* Initialize uart0 */
	uart0_Init(9600,0,0,8,1);
	
	while(1){
		
	};
}