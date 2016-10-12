#include "includes.h"

#define DEFAULT_BUS_CLOCK         24000000u
uint32_t SystemBusClock = DEFAULT_BUS_CLOCK;

void uart0_Init( uint32_t ulBaudRate,
				 uint8_t  ucParityEnable,
				 uint8_t  ucParityType,
				 uint8_t  ucDataLength,
				 uint8_t  ucStopBit)
{
	UART0_MemMapPtr uartPtr			= UART0_BASE_PTR;
	register uint16_t usBaudRate 	= 0;
	
	/* Configure clock for UART0*/
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; 
  SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);                      
  SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; 
	
	//maybe add param check
	
	/* Disable UART0 before changing any register */
	uart0_TranCtl(UART_TX_DISABLE, UART_RX_DISABLE);
	
	/* Configure pin for UART0 */
	PORTA_PCR1 = PORT_PCR_MUX(0x2);		//maybe integrate this into gpio.h
	PORTA_PCR2 = PORT_PCR_MUX(0x2);
	
	/* Configure parity and data length */
	UART0_C1_REG(uartPtr) &= ~(UART0_C1_M_MASK |            
                              UART0_C1_PT_MASK |                                
                              UART0_C1_PE_MASK);                                
    UART0_C4_REG(uartPtr) &= ~UART0_C4_M10_MASK; 
    if (ucDataLength == 10) {  
        UART0_C1_REG(uartPtr) |= (ucParityEnable << UART0_C1_PE_SHIFT)|
                                 (ucParityType << UART0_C1_PT_SHIFT);
		UART0_C4_REG(uartPtr) |= UART0_C4_M10_MASK;   
    } 
	else {
        UART0_C1_REG(uartPtr) |= ((ucDataLength - 8UL) << UART0_C1_M_SHIFT)|
                                 (ucParityEnable << UART0_C1_PE_SHIFT)|
                                 (ucParityType << UART0_C1_PT_SHIFT); 
	}
	
	/* Configure BaudRate */
	usBaudRate = SystemBusClock/(ulBaudRate * 16);
	UART0_BDH_REG(uartPtr) = (usBaudRate & 0x1F00) >> 8;
	UART0_BDL_REG(uartPtr) = (uint8_t)(usBaudRate & UART0_BDL_SBR_MASK);
	
	/* Configure stop bit */
	UART0_BDH_REG(uartPtr) &= ~UART0_BDH_SBNS_MASK;                            
    UART0_BDH_REG(uartPtr) |= (ucStopBit - 1) << UART0_BDH_SBNS_SHIFT;
	
	/* Clear interrupt settings */
	UART0_C2_REG(uartPtr)  &= ~(UART0_C2_TIE_MASK | UART0_C2_TCIE_MASK |      
                              UART0_C2_RIE_MASK | UART0_C2_ILIE_MASK);
	
	/* Clear receive buffer */
	while((UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) &&
          (UART0_D_REG(uartPtr))); 
	
	#if UART0_DEFAULT_OPEN
		uart0_TranCtl(UART_TX_ENABLE, UART_RX_ENABLE);
	#endif
	
	#if UART0_IRQ_ENABLE
		#if UART0_SEND_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_TCIE_MASK;
        #endif
        #if UART0_RECEIVE_IRQ
        UART0_C2_REG(uartPtr) |= UART0_C2_RIE_MASK;
        #endif                
		NVIC_EnableIRQ(UART0_IRQn);
		NVIC_SetPriority(UART0_IRQn,3); 
	#endif
	
}

void uart0_TranCtl(uint8_t ucTxEnable, 
                   uint8_t ucRxEnable)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    UART0_C2_REG(uartPtr) &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
    UART0_C2_REG(uartPtr) |= (ucTxEnable << UART0_C2_TE_SHIFT)|
                             (ucRxEnable << UART0_C2_RE_SHIFT);
}

uint8_t uart0_GetChar(void)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    while (!(UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK));                      /* 等待接收缓冲区可用   */
    return UART0_D_REG(uartPtr);                                                /* 返回接收字节         */
}

void uart0_SendChar(int8_t ucCh)
{
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;

    while(!((UART0_S1_REG(uartPtr) & UART0_S1_TDRE_MASK)));                     /* 等待FIFO可用         */
    UART0_D_REG(uartPtr) = ucCh;                                              /* 填充数据寄存器       */
}

void uart0_SendString(int8_t *pData)
{
    while (*pData != '\0') { 
        uart0_SendChar(*pData++);
    }    
}

void UART0_IRQHandler(void)
{     
   UART0_MemMapPtr uartPtr = UART0_BASE_PTR;  
   #if UART0_SEND_IRQ
                                                                               /* 发送中断处理程序     */
                                                                               /* 用户定义             */    
   #endif
   #if UART0_RECEIVE_IRQ
   while(UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK){                          /* 清除中断标志         */
   uart0_SendChar(UART0_D_REG(uartPtr));                                    /* 返回接收数据         */
   //while(!UART0_D_REG(uartPtr));                                           /* 清接收缓冲区         */
   }   
   #endif
}
