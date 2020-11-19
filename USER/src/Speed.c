
#include "headfile.h"

/**********ȫ�ֱ�������********/
int32 LeftDead = 400;
int32 RighDead = 430;               //���ҵ��������320
float Ratio_Encoder_Left = 50/(1175*0.02);//  ԭ50 8.8 �����ٶ�=counter*�����ܳ�(mm)/(����תһȦ��Ӧ��������*��������)
float Ratio_Encoder_Righ = 50/(1175*0.02);// �����ٶ�=counter*�����ܳ�(mm)/(����תһȦ��Ӧ��������*��������)
float g_fRealSpeed = 0;				//��ʵ�ٶ�
float g_fLeftRealSpeed;
float g_fRighRealSpeed;
float g_fSpeedFilter = 0;                //�����˲��ٶ�
float g_fExpectSpeed;              //�����ٶ�,δת������ʵ�ٶȣ����������	
float g_fSpeedError;		        //�ٶ�ƫ��
float g_fSpeedErrorTemp[5] = {0};
float fSpeedErrorInteg = 0;
int32 g_nLeftpulse = 0,g_nRighpulse = 0;
float g_PWMOut;
int32 g_nLeftPWM, g_nRighPWM;
int8 fast_flag=0;

float g_FastSpeed = 1400;//ֱ�����٣������У����1400

//�ٶȿ���
float g_speedControl_P = 160;		//�ٶ�P160
float g_speedControl_I = 120;		//�ٶ�I120
float g_fSpeedControlOut = 0;		//�ٶ����
int   g_fmaxspeed = 9000;               //�ٶ��޷�


  int32 nLeftPWM = 0, nRighPWM = 0;//���ҵ��pwm���
  
void PWMOut(void)
{
   
    if(Flag_Speed == OFF)      g_fSpeedControlOut = 0;	//���Flag_Speed == OFF     ������ٶ�
    if(Flag_Direction == OFF)  g_fDirectionControlOut = 0;//���Flag_Direction == OFF ���������
  
  if(flag_go!=1)
    {
      g_nLeftPWM = (int32)(g_fSpeedControlOut - g_fDirectionControlOut);
      g_nRighPWM = (int32)(g_fSpeedControlOut + g_fDirectionControlOut); 
    } 
	//g_nLeftPWM = g_nLeftPWM;//������첹��
	//g_nRighPWM = g_nRighPWM*1.05;
  
  if(Flag_Stop == OFF) 				//���Flag_Stop == OFF������0
    {
  	g_nLeftPWM = 0;g_nRighPWM = 0;
     }

    	if(g_nLeftPWM < 0)
	{
		nLeftPWM = LeftDead - g_nLeftPWM;
		nLeftPWM = (nLeftPWM > g_fmaxspeed? g_fmaxspeed: nLeftPWM);
                
		ctimer_pwm_duty(TIMER2_PWMCH0_B5, 0);        //����
		ctimer_pwm_duty(TIMER2_PWMCH1_B4, nLeftPWM);//��
	}
	else
	{
		nLeftPWM = LeftDead + g_nLeftPWM;
		nLeftPWM = (nLeftPWM > g_fmaxspeed? g_fmaxspeed: nLeftPWM);
		ctimer_pwm_duty(TIMER2_PWMCH0_B5, nLeftPWM); //����
		ctimer_pwm_duty(TIMER2_PWMCH1_B4, 0);         //��
	}

	if(g_nRighPWM < 0)
	{
		nRighPWM = RighDead - g_nRighPWM;
		nRighPWM = (nRighPWM > g_fmaxspeed? g_fmaxspeed: nRighPWM);
		ctimer_pwm_duty(TIMER1_PWMCH0_A18, 0);       //����
		ctimer_pwm_duty(TIMER1_PWMCH1_A20, nRighPWM); //�ҷ�
	}        
	else
	{
		nRighPWM = RighDead + g_nRighPWM;
		nRighPWM = (nRighPWM > g_fmaxspeed? g_fmaxspeed: nRighPWM);
		ctimer_pwm_duty(TIMER1_PWMCH0_A18, nRighPWM);//����
		ctimer_pwm_duty(TIMER1_PWMCH1_A20, 0);       //�ҷ�
	}
}
/************************************************
 * @file	     �����ٶ�ƫ��
 * @note      	����ȫ�ֱ���g_fSpeedError
 * @date		2020
 ************************************************/
void CalSpeedError(void)
{
	static float fSpeedOld = 0, fSpeedNew = 0;
	
	g_nLeftpulse = (gpio_get(Coder_dir_left) == 1? ctimer_count_read(TIMER0_COUNT1_A2):-ctimer_count_read(TIMER0_COUNT1_A2));//��ȡ��������
	ctimer_count_clean(TIMER0_COUNT1_A2);
	g_nRighpulse = (gpio_get(Coder_dir_right) == 0? ctimer_count_read(TIMER3_COUNT0_A4):-ctimer_count_read(TIMER3_COUNT0_A4));//��ȡ��������
	ctimer_count_clean(TIMER3_COUNT0_A4);	
	
	g_fLeftRealSpeed = g_nLeftpulse*Ratio_Encoder_Left;
	g_fLeftRealSpeed = (g_fLeftRealSpeed>3400?3400:g_fLeftRealSpeed);//���������������
	g_fRighRealSpeed = g_nRighpulse*Ratio_Encoder_Righ;
	g_fRighRealSpeed = (g_fRighRealSpeed>3400?3400:g_fRighRealSpeed);//���ұ�����������
	
	g_fRealSpeed = (g_fLeftRealSpeed + g_fRighRealSpeed) * 0.5;//��ʵ�ٶ�
	
	//�ٶȲɼ��ݶ�ƽ����ÿ�βɼ����仯200
	fSpeedOld = g_fSpeedFilter;
	fSpeedNew = g_fRealSpeed;
	
	if(fSpeedNew>=fSpeedOld)
		g_fSpeedFilter = ((fSpeedNew-fSpeedOld)>300?(fSpeedOld+300):fSpeedNew);
	else
		g_fSpeedFilter = ((fSpeedNew-fSpeedOld)<-300?(fSpeedOld-300):fSpeedNew);
        
        //�ٶȱ仯
        
        if(g_ValueOfADError <= 170 && stop_flag == 0 && slow_flag==0)
        {
              g_fExpectSpeed = g_FastSpeed;     //ֱ���ٶ�
              fast_flag=1;
        }
        else if(g_ValueOfADError > 170 && g_ValueOfADError<=400 && stop_flag==0 && slow_flag==0)
        {
              g_fExpectSpeed = (g_FastSpeed+eeprom_exspeed)*0.5;         
        }
        else if(slow_flag==1)
        { 
              g_fExpectSpeed = 280;
              fast_flag=0;
        }
        else if(slow_flag==1 && g_stopFlag==14)
        
              g_fExpectSpeed = 0;
       /*   
        else if(stop_time>1 && stop_flag==1) //����ͣ������
        {
              g_fExpectSpeed = 0;
        }
       */
        else
        {
              g_fExpectSpeed = eeprom_exspeed;
              fast_flag=0;
        }
        
	g_fSpeedError =  g_fExpectSpeed - g_fRealSpeed;
	g_fSpeedErrorTemp[4] = g_fSpeedErrorTemp[3];
	g_fSpeedErrorTemp[3] = g_fSpeedErrorTemp[2];
	g_fSpeedErrorTemp[2] = g_fSpeedErrorTemp[1];
	g_fSpeedErrorTemp[1] = g_fSpeedErrorTemp[0];
	g_fSpeedErrorTemp[0] = g_fSpeedError;
	
}

/**
 * @file	  �ٶȿ���
 * @note      	�ٶ��ݶ�ƽ��
 * @date	   2020
 */
void SpeedControl(void)
{
	int8 index=1;

	CalSpeedError();	//�����ٶ�ƫ��
        
	g_fSpeedError = (g_fSpeedError>800?800:g_fSpeedError);//�ٶ�ƫ���޷�
        
	//EEPROM�в���
	//g_speedControl_P = EEPROM_READ_WORD(12);	//320
	//g_speedControl_I = EEPROM_READ_WORD(16);	//100
	
	//���ַ���
	if((g_fSpeedError<=300)&&(g_fSpeedError>=-300))
	index=1;
	else
	index=0;	
	fSpeedErrorInteg = index * g_speedControl_I * g_fSpeedError * 0.00001;
         /*	
	if(Flag_Stop==OFF|Flag_Speed==OFF)
	{
		fSpeedErrorInteg = 0;	//ͣ����������
	}
         */	
	//fSpeedErrorInteg = (fSpeedErrorInteg < 0.0? 0.0: fSpeedErrorInteg);//��������
	//fSpeedErrorInteg = (fSpeedErrorInteg > 400.0? 400.0: fSpeedErrorInteg);//��������
	//�ٶȿ����㷨������ʽPI��
	g_fSpeedControlOut += g_speedControl_P*0.04*(g_fSpeedErrorTemp[0]-g_fSpeedErrorTemp[1]) + fSpeedErrorInteg;
	g_fSpeedControlOut = (g_fSpeedControlOut>=9000?9000:g_fSpeedControlOut);
	
}