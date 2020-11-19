#ifndef _Ui_hmi_h
#define _Ui_hmi_h

#include  "common.h"
#include "headfile.h"

/*************全局变量声明***************/
extern float eeprom_exspeed;
extern uint16 eeprom_intotime;

/***************函数声明***************/
void UIHMI(void);
void UIHMI1(void);
void Eeprom_write(void);
void Eeprom_read(void);

#endif