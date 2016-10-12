#include "includes.h"
#define TPM_MODULE    1999
#define TPM_INIT_VAL   20
#define TPM_Cn_MODE  (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK)

/*********************************************************************************************************
** Function name:           tpmInit
** Descriptions:            ptmµÄ³õÊ¼»¯ 
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              JiaoLong Liu
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void tpm_Init(void) 
{
    //SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;          
    SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;              /* Enable clock gate for TPM0 & TPM2                */
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK | SIM_SOPT2_TPMSRC(1);         /* Select PLL clock and select TPM clock                 */

    PORTB_PCR18 = ( 0 | PORT_PCR_MUX(3));                                /* TPM2_CH0 enable on PTB18    */
    PORTB_PCR19 = ( 0 | PORT_PCR_MUX(3));                                /* TPM2_CH1 enable on PTB19    */
    PORTD_PCR1  = ( 0 | PORT_PCR_MUX(4));                                /* TPM0_CH1 enable on PTD1     */

    TPM0_MOD  = TPM_MODULE;                                              /* 1999 / 50MHz = 40uS PWM     */
    TPM0_C1SC = TPM_Cn_MODE;                                             /* No Interrupts; High True 
                                                                             pulses on Edge Aligned PWM */
    TPM0_C1V  = TPM_INIT_VAL;                                            /* 90% pulse width             */
    TPM2_MOD  = TPM_MODULE;                                              /* 1999 / 50MHz = 40uS PWM     */
    TPM2_C0SC = TPM_Cn_MODE;                                             /* No Interrupts; Low True 
                                                                            pulses on Edge Aligned PWM  */
    TPM2_C0V  = TPM_INIT_VAL;                                            /* 90% pulse width             */
    TPM2_C1SC = TPM_Cn_MODE;                                             /* No Interrupts; Low True 
                                                                            pulses on Edge Aligned PWM  */
    TPM2_C1V  = TPM_INIT_VAL;                                            /* 90% pulse width             */

    TPM2_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);                          /* Edge Aligned PWM running from 
                                                                           BUSCLK / 1                   */
    TPM0_SC   = TPM_SC_CMOD(1) | TPM_SC_PS(0);                          /* Edge Aligned PWM running from 
																		   BUSCLK / 1                   */
}
