#ifndef _PIT0_IRQHandler_h
#define _PIT0_IRQHandler_h

#include  "common.h"
#include "headfile.h"

//外部使用本文件的全局变量在此申明
/**************全局变量外部申明*****************/
extern int8 Flag_Stop;			
extern int8 Flag_Speed;			
extern int8 Flag_Direction;
/**********************************************/

void RIT_DriverIRQHandler(void);

#endif