#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"
/*********************************************************************************************************
  Macro
*********************************************************************************************************/

#define UART0_DEFAULT_OPEN      1                                                                              
#define UART0_IRQ_ENABLE        1                                              
#define UART_TX_ENABLE          1
#define UART_TX_DISABLE         0
#define UART_RX_ENABLE          1
#define UART_RX_DISABLE         0

#define DEFAULT_BUS_CLOCK       24000000u

/*********************************************************************************************************
  Functions Declaration 
*********************************************************************************************************/  
extern void uart0_Init( uint32_t ulBaudRate,
					   uint8_t  ucParityEnable,
					   uint8_t  ucParityType,
					   uint8_t  ucDataLength,
					   uint8_t  ucStopBit);
					   
extern void uart0_TranCtl( uint8_t ucTxEnable, uint8_t ucRxEnable);
						   
extern void UART0_IRQHandler(void);	

/*
extern uint8_t uart0_GetChar(void);

extern void uart0_SendChar(int8_t ucCh);

extern void uart0_SendString(int8_t *pData);
*/						   
#ifdef __cplusplus
}
#endif


#endif

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  


