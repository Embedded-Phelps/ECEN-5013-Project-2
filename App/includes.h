/*********************************************Copyright (c)***********************************************
**                                Guangzhou ZLG MCU Technology Co., Ltd.
**
**                                        http://www.zlgmcu.com
**
**      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
**  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
**  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
**  承担任何责任。
**                                                                        ——广州周立功单片机科技有限公司
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               includes.h
** Last modified date:      2012-12-14
** Last version:            V1.0
** Description:             包含所有头文件文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Li Xiang
** Created date:            2012-12-14
** Version:                 V1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __INCLUDES_H
#define  __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  Standard header files 标准头文件
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

/*********************************************************************************************************
  Common's header files  公共头文件 
*********************************************************************************************************/
#ifndef _BBB
#include "MKL25Z4.h"
#include "system_MKL25Z4.h"

#include "uart.h"
#include "gpio.h"
#include "timer.h"
#endif
/*********************************************************************************************************
  Driver's header files  驱动头文件 
*********************************************************************************************************/

#include "log.h"

/*********************************************************************************************************
  User's header files 用户头文件
*********************************************************************************************************/
//#include "..\App\main.h"
#include "data.h"
#include "memory.h"
#include "profiler.h"


#define TIME_PER_CYCLE		41.6666666

#ifdef __cplusplus
}
#endif

#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
