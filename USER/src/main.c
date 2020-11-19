/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   	成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 8.32.1
 * @Target core		LPC54606J512BD100
 * @date       		20200701
 * @user                @吴文彬
 ********************************************************************************************************************/

#include "headfile.h"

int main(void)
{   
    DisableInterrupts;//关闭中断
  
    get_clk();//获取时钟频率（必须运行）

    car_init();//整车初始化
    
    Eeprom_read();//读取eeprom内的值
     
    EnableInterrupts;//中断启用标志
    
    //电位器调节：水平1500 垂直3400
    
    while(1)
    {    
      if(gpio_get(KEY1) == 0)//拨码1向上显示电感值
      {  
        UIHMI1();
        Eeprom_write();
        
        lcd_showuint16(5,0,g_ValueOfAD[0]);//左1
        lcd_showuint16(75,0,g_ValueOfAD[1]);//右1
        lcd_showuint16(15,1,g_ValueOfAD[2]);//左2
        lcd_showuint16(65,1,g_ValueOfAD[3]);//右2
        
        lcd_showstr(10,3,"L_real");
        lcd_showint32(75,3,g_fLeftRealSpeed,5);//左轮速度
        lcd_showstr(10,4,"R_real");
        lcd_showint32(75,4,g_fRighRealSpeed,5);//右轮速度
        lcd_showstr(10,5,"distance");
        lcd_showuint16(75,5,g_rellaydistance);//超声波测距
        lcd_showstr(10,6,"Red_OUT");
        lcd_showuint16(75,6,g_ValueOfAD[4]); //红外测距
        lcd_showstr(10,9,"g_stop");
        lcd_showuint16(75,9,g_stopFlag);
        //lcd_display_chinese(0,30,16,chinese_test[0],7,YELLOW);
        //showimage(gImage_hz1);
        
        // data_conversion(g_ValueOfAD[0],g_ValueOfAD[1],g_ValueOfAD[2] ,g_ValueOfAD[3], virtual_scope_data); 
           
         }
      
      if(gpio_get(KEY4) == 0)//拨码4向上打开调参界面
      {
        UIHMI();
        Eeprom_write();  

        lcd_showstr(10,8,"L_pwm");
        lcd_showint32(75,8,nLeftPWM,5);//左轮PWM输出        
        lcd_showstr(10,9,"R_pwm");
        lcd_showint32(75,9,nRighPWM,5);//右轮PWM输出 
        //data_conversion(g_ValueOfAD[0],g_ValueOfAD[1],g_ValueOfAD[2] ,g_ValueOfAD[3], virtual_scope_data); 
       //data_conversion(g_FastSpeed,g_fRealSpeed,g_nLeftPWM ,g_nRighPWM, virtual_scope_data);
        
      }
    }
}


