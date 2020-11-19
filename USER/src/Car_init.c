#include "headfile.h"

void car_init()
{
  //��ʼ��led
  gpio_init(LED1,GPO,0,NOPULL); //�ϵ�ָʾ��
  gpio_init(LED2,GPO,1,NOPULL);
  gpio_init(LED3,GPO,1,NOPULL);
  gpio_init(LED4,GPO,1,NOPULL);
  
  //��ʼ��������
  gpio_init(BEEP,GPO,1,NOPULL);
  gpio_set(BEEP,0);
  
  //��ʼ�����뿪������
  gpio_init(KEY1,GPI,1,PULLUP);
  gpio_init(KEY2,GPI,1,PULLUP);
  gpio_init(KEY3,GPI,1,PULLUP);
  gpio_init(KEY4,GPI,1,PULLUP);
  
  //��ʼ������
  gpio_init(Key_U,GPI,1,PULLUP);
  gpio_init(Key_D,GPI,1,PULLUP);
  gpio_init(Key_L,GPI,1,PULLUP);
  gpio_init(Key_R,GPI,1,PULLUP);
  gpio_init(Key_O,GPI,1,PULLUP);
  
  //ADC��ʼ��
  adc_init(ADC1); //��1
  adc_init(ADC2);//��1
  adc_init(ADC3);//��2
  adc_init(ADC4);//��2
  adc_init(ADC5);//����
  
  //��ʾ����ʼ��
  lcd_init();
  lcd_display_chinese(15,10,16,chinese_test[0],2,YELLOW);
  lcd_display_chinese(15,30,16,chinese_test[4],6,YELLOW);
  lcd_display_chinese(15,60,16,chinese_test[16],6,GREEN);
  lcd_display_chinese(15,90,16,chinese_test[28],4,RED);//�ȴ�����
  
  //��ʼ��������
  ctimer_count_init(TIMER0_COUNT1_A2);//������
  gpio_init(Coder_dir_left,GPI,0,NOPULL);//������
  ctimer_count_init(TIMER3_COUNT0_A4);//������
  gpio_init(Coder_dir_right,GPI,0,NOPULL);//������
  
  //��ʼ�����
   ctimer_pwm_init(TIMER1_PWMCH0_A18,18000,0);//����
   ctimer_pwm_init(TIMER1_PWMCH1_A20,18000,0);//�ҷ�
   ctimer_pwm_init(TIMER2_PWMCH1_B4,18000,0);//��
   ctimer_pwm_init(TIMER2_PWMCH0_B5,18000,0);//����
   
   //��ʼ������DJ
   ctimer_pwm_init(TIMER4_PWMCH0_A6,50,495);//����ϵ�н�PWM470�н�
   
   //��ʼ���Ĵ���
   eeprom_init();
    
   //���ڳ�ʼ��
   uart_init(USART_0,115200,UART0_TX_A25,UART0_RX_A24); //���������
   uart_rx_irq(USART_0,1); //�򿪴���0�����ж�  
   
   uart_init(USART_2,4800,UART2_TX_A27,UART2_RX_A26);//����͸��ͨ��
  // uart_rx_irq(USART_2,1);//�򿪴���2�����ж�
   
   //��ʱ2s������ж� 
   systick_delay_ms(2000);
   dsp_single_colour(BLACK);
   //�жϳ�ʼ��
   pit_init_us(5000);//��ʱ�ж�ʱ��5ms
   enable_irq(RIT_IRQn);  
   set_irq_priority(RIT_IRQn,0);//�������ȼ�
}