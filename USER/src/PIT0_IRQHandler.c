#include "headfile.h"
#include "PIT0_IRQHandler.h"

/****************ȫ�ֱ�������******************/
int8 Flag_Stop = ON;		 //=OFFͣ��
int8 Flag_Speed = ON;		//=ON�����ٶȿ���
int8 Flag_Direction = ON;       //=ON���ӷ������

void RIT_DriverIRQHandler(void)
{
  PIT_FLAG_CLEAR;    //���ж�
    
  //��־��������
  static uint16 i = 0;
  static uint16 j = 0;
  
 //0.5sLED��˸����ʱ���ж��ڱ�־��
   i++;
   if(i >= 100)  
   {    
     i = 0;
     gpio_toggle(LED2);
    }
   
  //20msһ���ٶȿ���
  j++;
  if(j >= 4)
  {    
    j = 0;
    SpeedControl();//�ٶȿ���
  }	
    DirectionControl();  
    //������� 
    PWMOut();
   //����PWM���    
             
          /*
  //ͣ�����
  if(stop_time>1)    
  {
    stop_time--;
    k[4] = 1;
  }
  if(stop_time<=1)
  {
    gpio_init(stop,GPI,1);
     k[4] = gpio_get(stop);  
    stop_time=1;
  }
  if(k[4]==0 && stop_time==1) 
  {
    Flag_Stop=OFF;
   // gpio_set(beep,1);
  }*/
}