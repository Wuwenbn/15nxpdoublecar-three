#include "headfile.h"

#define key_o   gpio_get(Key_O)
#define key_u   gpio_get(Key_U)
#define key_d   gpio_get(Key_D)
#define key_l   gpio_get(Key_L)
#define key_r   gpio_get(Key_R)

float eeprom_exspeed = 1000;
uint16 eeprom_intotime = 100;

//uint32 data0[32] = {0};
//uint32 data1[32] = {0};

int Flag_key=0;

void UIHMI1(void)
{  
      if(key_d==0)   
    {
      dsp_single_colour(BLACK);
      systick_delay_ms(10);
      if(key_d==0) Flag_key++;//按键值
    }
    if(key_u==0)   
    {
      dsp_single_colour(BLACK);
      systick_delay_ms(10);
      if(key_u==0) Flag_key--;//按键值
    }
    
    if(Flag_key>1) Flag_key=0;
    if(Flag_key<0) Flag_key=1;
    
    //参数4  红外距离  set_redout
    lcd_showstr(10,7,"set_red");
    lcd_showuint16(75,7,set_redout);
    
    //参数5  超声波距离 set_distance 
    lcd_showstr(10,8,"set_ult");
    lcd_showuint16(75,8,set_distance);
    
    //参数4   set_redout  800
    if(Flag_key==0) 
    {
      lcd_showstr(0,7,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) set_redout=set_redout+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) set_redout=set_redout-5;
      }
    }
    //参数5  set_distance
    if(Flag_key==1)
    {
      lcd_showstr(0,8,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) set_distance=set_distance+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) set_distance=set_distance-5;
      }
    }
}

void UIHMI(void)
  {    
    if(key_d==0)   
    {
      dsp_single_colour(BLACK);
      systick_delay_ms(10);
      if(key_d==0) Flag_key++;//按键值
    }
    if(key_u==0)   
    {
      dsp_single_colour(BLACK);
      systick_delay_ms(10);
      if(key_u==0) Flag_key--;//按键值
    } 
    if(Flag_key>7) Flag_key=0;
    if(Flag_key<0) Flag_key=7;
 //   if(dire_garage>1) dire_garage=0;
 //   if(dire_garage<0) dire_garage=1;
    /***********************/
    
    //参数1  期望速度   eeprom_exspeed
    lcd_showstr(10,0,"ExSpeed");
    lcd_showuint16(75,0,eeprom_exspeed);;
      
    //参数2  方向控制P   g_dirControl_P
    lcd_showstr(10,1,"DrCol_P");
    lcd_showuint16(75,1,g_dirControl_P);
    
    //参数3  方向控制D   g_dirControl_D
    lcd_showstr(10,2,"DrCol_D");
    lcd_showuint16(75,2,g_dirControl_D);

   //参数4  红外距离  set_redout
    lcd_showstr(10,3,"set_red");
    lcd_showuint16(75,3,set_redout);
    
   //参数5  超声波距离 set_distance 
    lcd_showstr(10,4,"set_ult");
    lcd_showuint16(75,4,set_distance);
    
    //参数6 直道加速  g_FastSpeed  
    lcd_showstr(10,5,"Fastspd");
    lcd_showuint16(75,5,g_FastSpeed);
    
    //参数7 圆环P
    lcd_showstr(10,6,"Round_P");
    lcd_showuint16(75,6,g_roundControl_P); 
    
    //参数8  圆环D
    lcd_showstr(10,7,"Round_D");
    lcd_showuint16(75,7,g_roundControl_D); 
    
    //参数9  圆环D
//    lcd_showstr(10,8,"Round_D");
//    lcd_showuint16(75,8,g_roundControl_D);
    
    //参数10 直道速度  g_FastSpeed
//    lcd_showstr(10,9,"Fastspd");
 //   lcd_showuint16(75,9,g_FastSpeed);
    
    
    //参数1   eeprom_exspeed
    if(Flag_key==0)
    {
      lcd_showstr(0,0,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) eeprom_exspeed=eeprom_exspeed+5;//
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) eeprom_exspeed=eeprom_exspeed-5;
      }
    }
    //参数2   g_dirControl_P
    if(Flag_key==1)
    {
      lcd_showstr(0,1,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_dirControl_P=g_dirControl_P+10;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_dirControl_P=g_dirControl_P-10;
      }
    }
    //参数3   g_dirControl_D
    if(Flag_key==2)
    {
      lcd_showstr(0,2,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_dirControl_D=g_dirControl_D+10;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_dirControl_D=g_dirControl_D-10;
      }
    }
    //参数4   set_redout  800
    if(Flag_key==3) 
    {
      lcd_showstr(0,3,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) set_redout=set_redout+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) set_redout=set_redout-5;
      }
    }
    //参数5  set_distance
    if(Flag_key==4)
    {
      lcd_showstr(0,4,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) set_distance=set_distance+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) set_distance=set_distance-5;
      }
    }
    //参数6    g_FastSpeed
    if(Flag_key==5)
    {
      lcd_showstr(0,5,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_FastSpeed=g_FastSpeed+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);  
        if(key_l==0) g_FastSpeed=g_FastSpeed-5;
      }
    }
    //参数7   g_roundControl_P
    if(Flag_key==6)
    {
      lcd_showstr(0,6,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_roundControl_P=g_roundControl_P+10;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_roundControl_P=g_roundControl_P-10;
      }
    }
    
    //参数8       //g_roundControl_D
    if(Flag_key==7)
    {
      lcd_showstr(0,7,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_roundControl_D=g_roundControl_D+10;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_roundControl_D=g_roundControl_D-10;
      }
    }
    
        //参数9       //g_roundControl_D
 /*   if(Flag_key==8)
    {
      lcd_showstr(0,8,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_roundControl_D=g_roundControl_D+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_roundControl_D=g_roundControl_D-5;
      }
    }*/
    
        //参数10       //g_FastSpeed
 /*   if(Flag_key==9)
    {
      lcd_showstr(0,9,">");
      if(key_r==0)   
      {
        systick_delay_ms(50);
        if(key_r==0) g_FastSpeed=g_FastSpeed+5;
      }
      if(key_l==0)   
      {
        systick_delay_ms(50);
        if(key_l==0) g_FastSpeed=g_FastSpeed-5;
      }
    }*/
  }
void Eeprom_write(void)
{
  if(key_o==0)
  {
    systick_delay_ms(10);
    if(key_o==0)
    {
      dsp_single_colour(BLACK);
      gpio_toggle(LED4);
      
    //  eeprom_write_page(0,data0);
  //    eeprom_write_page(1,data1);
      
      eeprom_write_word(0,eeprom_exspeed);  //eeprom_exspeed
      eeprom_write_word(4,g_dirControl_P);  //g_dirControl_P
      eeprom_write_word(8,g_dirControl_D);  //g_dirControl_D
      eeprom_write_word(12,set_redout);  //set_redout
      eeprom_write_word(16,set_distance);   //set_distance
      eeprom_write_word(20,g_FastSpeed);   //g_FastSpeed
      eeprom_write_word(24,g_roundControl_P);   //g_roundControl_P
      eeprom_write_word(28,g_roundControl_D);//g_roundControl_D
     
      //eeprom_write_word(32,g_roundControl_D);//g_roundControl_D
     // eeprom_write_word(36,g_FastSpeed);  //g_FastSpeed
      systick_delay_ms(100);
      gpio_toggle(LED4);  
    }
  }
} 
void Eeprom_read(void)
{ 
  eeprom_exspeed   =  EEPROM_READ_WORD(0);  //eeprom_exspeed
  g_dirControl_P   =  EEPROM_READ_WORD(4);  //g_dirControl_P
  g_dirControl_D   =  EEPROM_READ_WORD(8);  //g_dirControl_D
  set_redout       =  EEPROM_READ_WORD(12);  //set_redout
  set_distance  =  EEPROM_READ_WORD(16);   //set_distance
  g_FastSpeed     =  EEPROM_READ_WORD(20);  //g_FastSpeed
  g_roundControl_P      =  EEPROM_READ_WORD(24);  //g_roundControl_P
  g_roundControl_D =  EEPROM_READ_WORD(28);//g_roundControl_D
  //g_roundControl_D =  EEPROM_READ_WORD(32);//g_roundControl_D 1000
 // g_FastSpeed      =  EEPROM_READ_WORD(36);//g_FastSpeed
}