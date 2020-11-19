#include "headfile.h"

void car_init()
{
  //初始化led
  gpio_init(LED1,GPO,0,NOPULL); //上电指示灯
  gpio_init(LED2,GPO,1,NOPULL);
  gpio_init(LED3,GPO,1,NOPULL);
  gpio_init(LED4,GPO,1,NOPULL);
  
  //初始化蜂鸣器
  gpio_init(BEEP,GPO,1,NOPULL);
  gpio_set(BEEP,0);
  
  //初始化拨码开关上拉
  gpio_init(KEY1,GPI,1,PULLUP);
  gpio_init(KEY2,GPI,1,PULLUP);
  gpio_init(KEY3,GPI,1,PULLUP);
  gpio_init(KEY4,GPI,1,PULLUP);
  
  //初始化按键
  gpio_init(Key_U,GPI,1,PULLUP);
  gpio_init(Key_D,GPI,1,PULLUP);
  gpio_init(Key_L,GPI,1,PULLUP);
  gpio_init(Key_R,GPI,1,PULLUP);
  gpio_init(Key_O,GPI,1,PULLUP);
  
  //ADC初始化
  adc_init(ADC1); //左1
  adc_init(ADC2);//右1
  adc_init(ADC3);//左2
  adc_init(ADC4);//右2
  adc_init(ADC5);//红外
  
  //显示屏初始化
  lcd_init();
  lcd_display_chinese(15,10,16,chinese_test[0],2,YELLOW);
  lcd_display_chinese(15,30,16,chinese_test[4],6,YELLOW);
  lcd_display_chinese(15,60,16,chinese_test[16],6,GREEN);
  lcd_display_chinese(15,90,16,chinese_test[28],4,RED);//等待界面
  
  //初始化编码器
  ctimer_count_init(TIMER0_COUNT1_A2);//计数左
  gpio_init(Coder_dir_left,GPI,0,NOPULL);//方向左
  ctimer_count_init(TIMER3_COUNT0_A4);//计数右
  gpio_init(Coder_dir_right,GPI,0,NOPULL);//方向右
  
  //初始化电机
   ctimer_pwm_init(TIMER1_PWMCH0_A18,18000,0);//右正
   ctimer_pwm_init(TIMER1_PWMCH1_A20,18000,0);//右反
   ctimer_pwm_init(TIMER2_PWMCH1_B4,18000,0);//左反
   ctimer_pwm_init(TIMER2_PWMCH0_B5,18000,0);//左正
   
   //初始化传球DJ
   ctimer_pwm_init(TIMER4_PWMCH0_A6,50,495);//舵机上电夹紧PWM470夹紧
   
   //初始化寄存器
   eeprom_init();
    
   //串口初始化
   uart_init(USART_0,115200,UART0_TX_A25,UART0_RX_A24); //超声波测距
   uart_rx_irq(USART_0,1); //打开串口0接收中断  
   
   uart_init(USART_2,4800,UART2_TX_A27,UART2_RX_A26);//无线透传通信
  // uart_rx_irq(USART_2,1);//打开串口2接收中断
   
   //延时2s后进入中断 
   systick_delay_ms(2000);
   dsp_single_colour(BLACK);
   //中断初始化
   pit_init_us(5000);//定时中断时间5ms
   enable_irq(RIT_IRQn);  
   set_irq_priority(RIT_IRQn,0);//设置优先级
}