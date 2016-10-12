#include "includes.h"
void led_Gpio_Init(void) 
{
    //SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK ;

    PORTB_PCR18 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* Red LED: GPIO, digital output */
    PORTB_PCR19 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* GREENLED: GPIO, digital output*/
    PORTD_PCR1  |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* BLUE LED: GPIO, digital output*/

    FGPIOB_PSOR |= 1<<18;                                               /* Port output set to logic 1   */
    FGPIOB_PDDR |= 1<<18;                                               /* Pin set for GPIO function    */
    FGPIOB_PSOR |= 1<<19;                                               
    FGPIOB_PDDR |= 1<<19;                                               
    FGPIOD_PSOR |= 1<<1;                                            
    FGPIOD_PDDR |= 1<<1;                                              
}
