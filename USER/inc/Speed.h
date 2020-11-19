#ifndef __SPEED_H__
#define __SPEED_H__

#include  "common.h"
#include  "headfile.h"

/**********ȫ�ֱ����ⲿ����********/
extern int32 g_nLeftpulse;
extern int32 g_nRighpulse;
extern float g_fSpeedError;
extern float g_fRealSpeed;
extern float g_fLeftRealSpeed;
extern float g_fRighRealSpeed;
extern float g_fSpeedFilter;
extern float fSpeedErrorInteg;
extern float g_fSpeedControlOut;
extern float g_PWMOut;
extern int32 g_nLeftPWM, g_nRighPWM;
extern float g_speedControl_P;		//���ٱ���
extern float g_speedControl_I;		//λ�Ʊ���
extern float g_fExpectSpeed;
extern float g_FastSpeed; 
extern int8 fast_flag;
extern int32 nLeftPWM;
extern int32 nRighPWM;

/***********��������*************/
void PWMOut(void);
void CalSpeedError(void);
void SpeedControl(void);
#endif