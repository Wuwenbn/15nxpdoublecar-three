#ifndef _PIT0_IRQHandler_h
#define _PIT0_IRQHandler_h

#include  "common.h"
#include "headfile.h"

//�ⲿʹ�ñ��ļ���ȫ�ֱ����ڴ�����
/**************ȫ�ֱ����ⲿ����*****************/
extern int8 Flag_Stop;			
extern int8 Flag_Speed;			
extern int8 Flag_Direction;
/**********************************************/

void RIT_DriverIRQHandler(void);

#endif