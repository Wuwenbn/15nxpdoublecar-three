#ifndef _Ui_hmi_h
#define _Ui_hmi_h

#include  "common.h"
#include "headfile.h"

/*************ȫ�ֱ�������***************/
extern float eeprom_exspeed;
extern uint16 eeprom_intotime;

/***************��������***************/
void UIHMI(void);
void UIHMI1(void);
void Eeprom_write(void);
void Eeprom_read(void);

#endif