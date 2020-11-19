#include "headfile.h"

/**********ȫ�ֱ�������********/ 
int16 g_dirControl_P = 650;            //�������P
int16 g_dirControl_D = 1200;	       //�������D

int16 g_rolControl_P=900;             //���P
int16 g_rolControl_D=940;             //���D

int16 g_fastControl_P=760;
int16 g_fastControl_D=660;  //ֱ��PD

int16 g_roundControl_P = 800;        //��ֱ���P
int16 g_roundControl_D = 860;        //��ֱ���D

float g_fDirectionError[2];	     //����ƫ�g_fDirectionError[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ�
			           //��g_fDirectionError[1]Ϊһ�Դ�ֱ��еĲ�Ⱥ�ƫ�
float g_fDirectionError_dot[2];  //����ƫ��΢�֣�g_fDirectionError_dot[0]Ϊһ��ˮƽ��еĲ�Ⱥ�ƫ��΢�֣�
				//��g_fDirectionError_dot[1]Ϊһ�Դ�ֱ��еĲ�Ⱥ�ƫ��΢�֣�
float g_fDirectionControlOut;//����������

int16 g_ValueOfAD[5] = {0};       //��ȡ�ĵ��ֵ
int16 g_ValueOfADFilter[5] = {0};//�����˲��ĵ��ֵ��δʹ�ã�

uint16 flag_timego = 0 ;  //������ʱ��
int16 flag_go = 0 ;      //�����־
int16 flag_go2=0;
int16 a_Angleout;            //�����ǽǶ�
int16 flag_timeintoround = 0;//�뻷ǿ���ʱ��
int16 flag_timeoutround = 0;
int16 flag_timeinround;      //����ʱ��
int16 flag_Round = OFF;      //���ڱ�־
int16 angle_round=0;         //�뻷��Ǵ�С
//int16 direction_round;         //��������0Ϊ��1Ϊ�� 

int16 Infrared;             //��ȡ�ĺ�����ֵ
int16 g_distance[5] = {0};
//int16 g_Infrared[5] = {0}; 
uint16 g_rellaydistance;
uint16 g_rinfrared;
uint16 set_distance=600;//����������
uint16 stop_time=0;//ɲ��ʱ��
uint16 stop_flag=0;//ͣ����־
uint16 stop_sever=0;
uint16 time=0;
uint16 set_redout;//  �������
int16 g_ValueOfADError;//ֱ��ƫ���־
uint16 ui_ValueOfADError;
uint8 ruhuan=0;
int8 dire_garage = 0; //���ⷽ��
int8 slow_flag=0;
//uint8 sever=470;
uint8 g_stopFlag=0;

/************************************************************************
 * file *		            �������
 *		һ������£�����ˮƽ��еĲ�Ⱥ���Ϊƫ��
 *             �ڻ���ʱ�У�������ֱ��еĲ�Ⱥ���Ϊƫ��
 *
 *		        ���ֵ��Ӧ����
 *
 *   g_ValueOfAD[0]��1500		          g_ValueOfAD[1]��1500
 *      (ˮƽ����)		                    ��ˮƽ�ҵ�У�
 *          g_ValueOfAD[2]��3400	    g_ValueOfAD[3]��3400
 *	       ����ֱ���У�	              ����ֱ�ҵ�У�
 * date *		     2020
 *************************************************************************/

void DirectionControl(void)
{
	static float g_fDirectionErrorTemp[2][5];
	
	Read_ADC();		//��ȡ���ֵ
	
	if((g_ValueOfAD[0]<20 || g_ValueOfAD[1]<20) && flag_timego>400)	
	Flag_Stop = OFF;//�������ͣ������
        
	g_ValueOfAD[0] = (g_ValueOfAD[0] < 10? 10:g_ValueOfAD[0]);//�ĸ����ֵ�޷�
	g_ValueOfAD[1] = (g_ValueOfAD[1] < 10? 10:g_ValueOfAD[1]);
	g_ValueOfAD[2] = (g_ValueOfAD[2] < 10? 10:g_ValueOfAD[2]);
	g_ValueOfAD[3] = (g_ValueOfAD[3] < 10? 10:g_ValueOfAD[3]);
        
        g_ValueOfAD[4] = (g_ValueOfAD[4] < 10? 10:g_ValueOfAD[4]);//�������޷�
		
	
	g_fDirectionError[0] = (float)(g_ValueOfAD[0] - g_ValueOfAD[1])/(g_ValueOfAD[0] + g_ValueOfAD[1]);//ˮƽ��еĲ�Ⱥ���Ϊƫ��
	g_fDirectionError[0] = (g_fDirectionError[0]>= 1? 1:g_fDirectionError[0]);
	g_fDirectionError[0] = (g_fDirectionError[0]<=-1?-1:g_fDirectionError[0]);//ƫ���޷�
	
        
	g_fDirectionError[1] = (float)(g_ValueOfAD[2] - g_ValueOfAD[3])/(g_ValueOfAD[2] + g_ValueOfAD[3]);//��ֱ��еĲ�Ⱥ���Ϊƫ��   
	g_fDirectionError[1] = (g_fDirectionError[1]>= 1? 1:g_fDirectionError[1]);	
	g_fDirectionError[1] = (g_fDirectionError[1]<=-1?-1:g_fDirectionError[1]);//ƫ���޷�	
	  
        
	g_fDirectionErrorTemp[0][4] = g_fDirectionErrorTemp[0][3];
	g_fDirectionErrorTemp[0][3] = g_fDirectionErrorTemp[0][2];
	g_fDirectionErrorTemp[0][2] = g_fDirectionErrorTemp[0][1];
	g_fDirectionErrorTemp[0][1] = g_fDirectionErrorTemp[0][0];
	g_fDirectionErrorTemp[0][0] = g_fDirectionError[0];
	g_fDirectionError_dot[0] = 5*(g_fDirectionErrorTemp[0][0]-g_fDirectionErrorTemp[0][3]);//ˮƽ��е�ƫ��΢��
         
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]> 0.7? 0.7:g_fDirectionError_dot[0]);
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]<-0.7?-0.7:g_fDirectionError_dot[0]);//ƫ��΢���޷�
        

	g_fDirectionErrorTemp[1][4] = g_fDirectionErrorTemp[1][3];
	g_fDirectionErrorTemp[1][3] = g_fDirectionErrorTemp[1][2];
	g_fDirectionErrorTemp[1][2] = g_fDirectionErrorTemp[1][1];
	g_fDirectionErrorTemp[1][1] = g_fDirectionErrorTemp[1][0];
	g_fDirectionErrorTemp[1][0] = g_fDirectionError[1];
	g_fDirectionError_dot[1] = 5*(g_fDirectionErrorTemp[1][0]-g_fDirectionErrorTemp[1][3]);//��ֱ��е�ƫ��΢��
        
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]> 0.7? 0.7:g_fDirectionError_dot[1]);
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]<-0.7?-0.7:g_fDirectionError_dot[1]);//ƫ��΢���޷�

        g_ValueOfADError=g_ValueOfAD[0]-g_ValueOfAD[1];//ˮƽ������еĲ�ֵ
        g_ValueOfADError=(g_ValueOfADError>0?g_ValueOfADError:-g_ValueOfADError);
        
        //if(slow_flag==0)
        FLEXCOMM0_DriverIRQHandler();  //��ȡdistanc��������ֵ
        
        g_distance[4]=g_distance[3];
        g_distance[3]=g_distance[2];
        g_distance[2]=g_distance[1];
        g_distance[1]=g_distance[0];
        g_distance[0]=distance;
        distance_filter();  //�˳��������������Сֵ
 /*       
        g_Infrared[4]=g_Infrared[3];
        g_Infrared[3]=g_Infrared[2];
        g_Infrared[2]=g_Infrared[1];
        g_Infrared[1]=g_Infrared[0];
        g_Infrared[0]=Infrared;
        infrared_filter();  //�˳�������������ֵ

*/
        
/**************************���򷽰�******************************/  
 
  /*****����1*******  
  if(set_distance >= g_rellaydistance && set_redout <= g_ValueOfAD[4] && g_ValueOfADError<=800 && stop_flag==0) 
  {    
          stop_time=80;
          stop_flag=1;
  }           
        if(stop_time>1 && stop_flag==1)
        {
          //g_fExpectSpeed=0;
          stop_time--;
          gpio_set(BEEP,1);
       //  ctimer_pwm_duty(TIMER4_PWMCH0_A6,600);//ͣ����DJ
          uart_putchar(USART_2,0x0e);//����͸����������(�����ź�)
        }
        if(stop_time==1 && stop_flag==1)
        {
          Flag_Stop = OFF;
          stop_time=0;
          stop_flag=1;
          gpio_set(BEEP,0);
          stop_sever=1;
        }
        
        if(stop_sever==1) 
        {
        //  sever++;
          ctimer_pwm_duty(TIMER4_PWMCH0_A6,580);//ͣ����DJ
         // if(sever>=580) stop_sever=0;
          uart_putchar(USART_2,0x0e);//����͸����������(�����ź�)
        }
        else uart_putchar(USART_2,0x01);
 */
   
      /*****����2******/ 
      if(set_distance >= g_rellaydistance && set_redout <= g_ValueOfAD[4] && g_ValueOfADError<=800 && slow_flag==0) 
      {
        slow_flag=1;
      } 
      if(slow_flag==1)      
      {
        ctimer_pwm_duty(TIMER4_PWMCH0_A6,530);//��DJ
        gpio_set(BEEP,1);
      } 
     if(uart_query(USART_2,&g_stopFlag))     
      //uart_getchar(USART_2,&g_stopFlag);
     {
      if(g_stopFlag == 14 && stop_time == 0)
      {
        stop_time = 80;
        g_fExpectSpeed = 0;
      }
     }
      if(stop_time > 1)stop_time--;
      if(stop_time == 1)
      {
        Flag_Stop = OFF;
        gpio_set(BEEP,0);
      }
/***********************************���⴦��***************************/
        
        if(gpio_get(KEY2) == 0)
        {
          dire_garage=0;
          gpio_set(LED3,0);
        }
        else dire_garage=1;
        
        flag_timego++;
        if(flag_timego<=75)   //������
        {
          flag_go=1;
         // gpio_set(BEEP,1);
          if(dire_garage == 0)   //�����
          {
            g_nLeftPWM=3500;
            g_nRighPWM=5600;
          }
          if(dire_garage == 1)  //�ҳ���
          {
            g_nLeftPWM=5600;
            g_nRighPWM=3500;
          }
        }
        
        if(flag_timego>75)   //������
        {
          // gpio_set(BEEP,0);
           flag_go=0; 
        }       

        
        
        
/***************************��������****************************/
   
if((g_ValueOfAD[0]>2700)&&(g_ValueOfAD[1]>2700)&&(g_ValueOfAD[2]<700)&&(g_ValueOfAD[3]<700)&&(flag_timeintoround==0)&&(flag_go==0))
{
  flag_timeintoround=120; //�뻷���ʱ��
}  
  if(flag_timeintoround>1)
  {
    flag_timeintoround--;
    flag_Round=ON;
    gpio_set(BEEP,1);
    flag_timeoutround=1;
    flag_timeinround=800;
  }
  if((flag_timeoutround==1)&&(flag_timeintoround==1))
  {
    flag_Round = OFF;
    gpio_set(BEEP,0);
    flag_timeintoround = 1;
    if(flag_timeinround>1)
    {
      flag_timeinround--;
     }
     if(flag_timeinround<=1)
     {
      flag_timeintoround = 0;
      flag_timeoutround = 0;
      ruhuan = 0;
     }
  }    
/*******************************************************************************/

        //�����㷨��λ��ʽPD)
        if(flag_Round != ON && slow_flag!=1)
	g_fDirectionControlOut = g_fDirectionError[0]*g_dirControl_P*10 + g_fDirectionError_dot[0]*g_dirControl_D*10; //P10000,D10000
        
        //�뻷��    
        if(flag_Round == ON)
          g_fDirectionControlOut = g_fDirectionError[1]*g_roundControl_P*10 + g_fDirectionError_dot[1]*g_roundControl_D*10;                    
                                                          //800                //840
        if(slow_flag==1)
          g_fDirectionControlOut = g_fDirectionError[0]*g_dirControl_P + g_fDirectionError_dot[0]*g_dirControl_D;
        
}

/***************************************
*file*       ����źŲɼ�����
*date*           2020 
***************************************/
void Read_ADC(void)
{
     int16  i,j,k,temp;
     int16  ad_valu[5][5],ad_valu1[5],ad_sum[5];
     int16  ValueOfADOld[5],ValueOfADNew[5];
        
//**********************************���⴦��************************************//
     
    // Infrared=adc_convert(ADC5,ADC_12BIT);
     
//*******************************���ֵ�˲�����*******************************//    
   for(i=0;i<5;i++)
     {
         ad_valu[0][i]=adc_convert(ADC1,ADC_12BIT);  	// AD1ˮƽ��
         ad_valu[1][i]=adc_convert(ADC2,ADC_12BIT);     // AD2ˮƽ��
         ad_valu[2][i]=adc_convert(ADC3,ADC_12BIT);  	// AD3��ֱ��
         ad_valu[3][i]=adc_convert(ADC4,ADC_12BIT);     // AD4��ֱ��
         ad_valu[4][i]=adc_convert(ADC5,ADC_12BIT);     // ������
     }
     
/*=========================ð����������==========================*///�������ֵ����Сֵ
     for(i=0;i<5;i++)
     {
        for(j=0;j<4;j++)
        {
           for(k=0;k<4-j;k++)
           {
              if(ad_valu[i][k] > ad_valu[i][k+1])        //ǰ��ıȺ���Ĵ�  ����н���
              {
                 temp = ad_valu[i][k+1];
                 ad_valu[i][k+1] = ad_valu[i][k];
                 ad_valu[i][k] = temp;
              }
           }
        }
     }
     
/*===========================��ֵ�˲�=================================*/
    for(i=0;i<5;i++)    //���м�����ĺ�
     {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
     }

	
	 for(i=0;i<5;i++)            //����ֵ�и�λ������
	 {
	 	g_ValueOfAD[i] = (int16)(ad_valu1[i]/10*10);

		//�ɼ��ݶ�ƽ����ÿ�βɼ����仯40
		ValueOfADOld[i] = g_ValueOfADFilter[i];
		ValueOfADNew[i] = g_ValueOfAD[i];
		
		if(ValueOfADNew[i]>=ValueOfADOld[i])
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])>50?(ValueOfADOld[i]+50):ValueOfADNew[i]);
		else
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])<-60?(ValueOfADOld[i]-60):ValueOfADNew[i]);
	 }
	 
}

void distance_filter(void)     //����������˲�(ȡƽ��ֵ,��ȥ����ֵ)
{
  int min=10000,i,j,sum=0,average;
  for(i=0;i<5;i++)
  {
    //if(g_distance[i]>max) max=g_distance[i];
    if(g_distance[i]<min) min=g_distance[i];
    sum+=g_distance[i];
  }
  j = sum-min;
  average=(int)j/4;
  g_rellaydistance=average;
}
/*
void infrared_filter(void)    //�����˲�
{
  int max=0,i,j,sum=0,average;
  for(i=0;i<5;i++)
  {
    if(g_Infrared[i]>max) max=g_Infrared[i];
   // if(g_distance[i]<min) min=g_distance[i];
    sum+=g_Infrared[i];
  }
  j = sum-max;
  average=(int)j/4;
  g_rinfrared=average;
}
*/