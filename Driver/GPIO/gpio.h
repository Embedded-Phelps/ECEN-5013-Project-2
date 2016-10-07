#ifndef __GPIO__H
#define __GPIO__H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************************
  PORT Configuration
********************************************************************************************************/
#define PTA               A
#define PTB               B
#define PTC               C
#define PTD               D
#define PTE               E

/*
 * Clock configuration for Port module
 */ 
#define PORT_ENABLE_CLK(PTx)    SIM_SCGC5 |=  SIM_SCGC5_PORT##PTx##_MASK  
#define PORT_DISABLE_CLK(PTx)   SIM_SCGC5 &= ~SIM_SCGC5_PORT##PTx##_MASK




#ifdef __cplusplus
}
#endif


#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  

