#include "headfile.h"
#include "PIT0_IRQHandler.h"

/****************全局变量定义******************/
int8 Flag_Stop = ON;		 //=OFF停车
int8 Flag_Speed = ON;		//=ON增加速度控制
int8 Flag_Direction = ON;       //=ON增加方向控制

void RIT_DriverIRQHandler(void)
{
  PIT_FLAG_CLEAR;    //清中断
    
  //标志变量定义
  static uint16 i = 0;
  static uint16 j = 0;
  
 //0.5sLED闪烁（定时器中断内标志）
   i++;
   if(i >= 100)  
   {    
     i = 0;
     gpio_toggle(LED2);
    }
   
  //20ms一次速度控制
  j++;
  if(j >= 4)
  {    
    j = 0;
    SpeedControl();//速度控制
  }	
    DirectionControl();  
    //方向控制 
    PWMOut();
   //最终PWM输出    
             
          /*
  //停车检测
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