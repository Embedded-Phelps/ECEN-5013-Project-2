#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
  Macro
*********************************************************************************************************/
#define MKL_UART0               0
#define MKL_UART1               1
#define MKL_UART2               2
  
#define UART_PARITY_EN          1
#define UART_PARITY_DIS         0
  
#define UART_PARITY_EVEN        0
#define UART_PARITY_ODD         1

#define UART_10BIT_LENGTH       10
#define UART_9BIT_LENGTH        9
#define UART_8BIT_LENGTH        8

#define UART_1BIT_STOP          1
#define UART_2BIT_STOP          2
  
#define UART_POLLED             0
#define UART_INTERRUPT          1
#define UART_DMA                2

#define UART_TX_ENABLE          1
#define UART_TX_DISABLE         0

#define UART_RX_ENABLE          1
#define UART_RX_DISABLE         0

// <h> UART Configuration(config the status after uart inited.)
//   <h> UART0 Default Configuration 
//     <o0>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e1>  	UART0 IRQ Enable
//         <o6.0>   Send IRQ Enable    
//         <O7.0>   Receive IRQ Enable   
//     </e1>
//   </h>  
//   <h> UART1 Default Configuration 
//     <o2>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e3>  	UART1_IRQ_ENABLE:
//         <o8.0>   Send IRQ Enable    
//         <O9.0>   Receive IRQ Enable       
//     </e3>
//   </h>  
//   <h> UART2 Default Configuration 
//     <o4>  	Transport Enable:
//                     <0=> Disable
//                     <1=> Enable
//     <e5>  	UART2_IRQ_ENABLE:
//         <o10.0>   Send IRQ Enable    
//         <O11.0>   Receive IRQ Enable           
//     </e5>
//   </h>  
// </h>
#define UART0_DEFAULT_OPEN      1                                               /* 是否允许传输          */                                
#define UART0_IRQ_ENABLE        1                                               /* 串口中断允许          */    

#define UART1_DEFAULT_OPEN      0                                               /* 是否允许传输          */                               
#define UART1_IRQ_ENABLE        1                                               /* 串口中断允许          */

#define UART2_DEFAULT_OPEN      0                                               /* 是否允许传输          */                              
#define UART2_IRQ_ENABLE        1                                               /* 串口中断允许          */

#define UART0_SEND_IRQ          0                                               
#define UART0_RECEIVE_IRQ       1

#define UART1_SEND_IRQ          0
#define UART1_RECEIVE_IRQ       0

#define UART2_SEND_IRQ          0
#define UART2_RECEIVE_IRQ       0    

#define UART_PARAM_DEBUG        0                                               /* 是否进行参数检查     */
  
#define UART_PARAM_PORTNUM(x)   (x > 3? 1 : 0)                                  /* 端口号检查           */
#define UART_PARAM_MODE(x)      (x > 3? 1 : 0)                                  /* 模式检查             */
#define UART_PARAM_LENGTH(x)    ((x == 8)||(x == 9)||(x == 9) ? 1 : 0)          /* 数据长度检查         */
#define UART_PARAM_STOP(x)      ((x == 1)||(x == 2)? 1 : 0)                     /* 停止位检查           */
#define UART_PARAM_PARITY(x)    ((x == 0)||(x == 1)? 1 : 0)                     /* 校验位检查           */
#define UART_PARAM_LOGIC(x)     ((x == 0)||(x == 1)? 1 : 0)                     /* 逻辑位检查           */
#define UART_CHECK_PARAM(x)     (x? (while (1)):)                               /* 错误处理             */

/*********************************************************************************************************
  Functions Declaration 
*********************************************************************************************************/  
extern void uart0Init( uint32_t ulBaudRate,
					   uint8_t  ucParityEnable,
					   uint8_t  ucParityType,
					   uint8_t  ucDataLength,
					   uint8_t  ucStopBit);
					   
extern void uart0_TranCtl( uint8_t ucTxEnable, 
						   uint8_t ucRxEnable);
						   
extern uint8_t uart0_GetChar(void);

extern void uart0_SendChar(uint8_t ucCh);

extern void uart0_SendString(uint8_t *pData);

extern void UART0_IRQHandler(void);	//called where?

						   
#ifdef __cplusplus
}
#endif


#endif

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  


