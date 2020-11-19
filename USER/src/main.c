/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   	�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴LPC546XX_config.h�ļ��ڰ汾�궨��
 * @Software 		IAR 8.32.1
 * @Target core		LPC54606J512BD100
 * @date       		20200701
 * @user                @���ı�
 ********************************************************************************************************************/

#include "headfile.h"

int main(void)
{   
    DisableInterrupts;//�ر��ж�
  
    get_clk();//��ȡʱ��Ƶ�ʣ��������У�

    car_init();//������ʼ��
    
    Eeprom_read();//��ȡeeprom�ڵ�ֵ
     
    EnableInterrupts;//�ж����ñ�־
    
    //��λ�����ڣ�ˮƽ1500 ��ֱ3400
    
    while(1)
    {    
      if(gpio_get(KEY1) == 0)//����1������ʾ���ֵ
      {  
        UIHMI1();
        Eeprom_write();
        
        lcd_showuint16(5,0,g_ValueOfAD[0]);//��1
        lcd_showuint16(75,0,g_ValueOfAD[1]);//��1
        lcd_showuint16(15,1,g_ValueOfAD[2]);//��2
        lcd_showuint16(65,1,g_ValueOfAD[3]);//��2
        
        lcd_showstr(10,3,"L_real");
        lcd_showint32(75,3,g_fLeftRealSpeed,5);//�����ٶ�
        lcd_showstr(10,4,"R_real");
        lcd_showint32(75,4,g_fRighRealSpeed,5);//�����ٶ�
        lcd_showstr(10,5,"distance");
        lcd_showuint16(75,5,g_rellaydistance);//���������
        lcd_showstr(10,6,"Red_OUT");
        lcd_showuint16(75,6,g_ValueOfAD[4]); //������
        lcd_showstr(10,9,"g_stop");
        lcd_showuint16(75,9,g_stopFlag);
        //lcd_display_chinese(0,30,16,chinese_test[0],7,YELLOW);
        //showimage(gImage_hz1);
        
        // data_conversion(g_ValueOfAD[0],g_ValueOfAD[1],g_ValueOfAD[2] ,g_ValueOfAD[3], virtual_scope_data); 
           
         }
      
      if(gpio_get(KEY4) == 0)//����4���ϴ򿪵��ν���
      {
        UIHMI();
        Eeprom_write();  

        lcd_showstr(10,8,"L_pwm");
        lcd_showint32(75,8,nLeftPWM,5);//����PWM���        
        lcd_showstr(10,9,"R_pwm");
        lcd_showint32(75,9,nRighPWM,5);//����PWM��� 
        //data_conversion(g_ValueOfAD[0],g_ValueOfAD[1],g_ValueOfAD[2] ,g_ValueOfAD[3], virtual_scope_data); 
       //data_conversion(g_FastSpeed,g_fRealSpeed,g_nLeftPWM ,g_nRighPWM, virtual_scope_data);
        
      }
    }
}


