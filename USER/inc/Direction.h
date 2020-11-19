#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include  "common.h"
#include  "headfile.h"

/**********全局变量外部申明********/

extern int16 g_dirControl_P;
extern int16 g_dirControl_D;
extern int16 g_roundControl_P;
extern int16 g_roundControl_D;
extern float g_fDirectionError[2];
extern float g_fDirectionError_dot[2];
extern float g_fDirectionControlOut;
extern int16 g_ValueOfAD[5];
extern int16 g_ValueOfADFilter[5];
extern int16 flag_go;      //出库标志
extern int16 angle_round;
extern int16 direction_round;
extern int16 flag_timeintoround;
extern int16 g_distance[5];
extern int16 g_Infrared[5];
extern uint16 g_rellaydistance;
extern uint16 g_rinfrared;
extern uint16 set_distance;
extern int16 g_ValueOfADError;
extern uint16 ui_ValueOfADError;
extern uint16 stop_time;//刹车时间
extern uint16 stop_flag;//停车标志
extern int8 dire_garage;//出库方向
extern uint16 set_redout;
extern int8 slow_flag;
extern uint8 g_stopFlag;
extern int16 g_rolControl_P;             //弯道P
extern int16 g_rolControl_D;             //弯道D
extern int16 g_fastControl_P;             //直道P
extern int16 g_fastControl_D;             //直道D
/***********函数声明*************/
void Read_ADC(void);
void DirectionControl(void);
void distance_filter(void);
void infrared_filter(void);
#endif