#include "headfile.h"

/**********全局变量定义********/ 
int16 g_dirControl_P = 650;            //方向控制P
int16 g_dirControl_D = 1200;	       //方向控制D

int16 g_rolControl_P=900;             //弯道P
int16 g_rolControl_D=940;             //弯道D

int16 g_fastControl_P=760;
int16 g_fastControl_D=660;  //直道PD

int16 g_roundControl_P = 800;        //垂直电感P
int16 g_roundControl_D = 860;        //垂直电感D

float g_fDirectionError[2];	     //方向偏差（g_fDirectionError[0]为一对水平电感的差比和偏差）
			           //（g_fDirectionError[1]为一对垂直电感的差比和偏差）
float g_fDirectionError_dot[2];  //方向偏差微分（g_fDirectionError_dot[0]为一对水平电感的差比和偏差微分）
				//（g_fDirectionError_dot[1]为一对垂直电感的差比和偏差微分）
float g_fDirectionControlOut;//方向控制输出

int16 g_ValueOfAD[5] = {0};       //获取的电感值
int16 g_ValueOfADFilter[5] = {0};//阶梯滤波的电感值（未使用）

uint16 flag_timego = 0 ;  //出库打角时间
int16 flag_go = 0 ;      //出库标志
int16 flag_go2=0;
int16 a_Angleout;            //出库打角角度
int16 flag_timeintoround = 0;//入环强打角时间
int16 flag_timeoutround = 0;
int16 flag_timeinround;      //环内时间
int16 flag_Round = OFF;      //环内标志
int16 angle_round=0;         //入环打角大小
//int16 direction_round;         //环岛方向0为左，1为右 

int16 Infrared;             //获取的红外测距值
int16 g_distance[5] = {0};
//int16 g_Infrared[5] = {0}; 
uint16 g_rellaydistance;
uint16 g_rinfrared;
uint16 set_distance=600;//超声波距离
uint16 stop_time=0;//刹车时间
uint16 stop_flag=0;//停车标志
uint16 stop_sever=0;
uint16 time=0;
uint16 set_redout;//  红外距离
int16 g_ValueOfADError;//直道偏差标志
uint16 ui_ValueOfADError;
uint8 ruhuan=0;
int8 dire_garage = 0; //出库方向
int8 slow_flag=0;
//uint8 sever=470;
uint8 g_stopFlag=0;

/************************************************************************
 * file *		            方向控制
 *		一般情况下：用两水平电感的差比和作为偏差
 *             在环岛时中：用量垂直电感的差比和作为偏差
 *
 *		        电感值对应变量
 *
 *   g_ValueOfAD[0]：1500		          g_ValueOfAD[1]：1500
 *      (水平左电感)		                    （水平右电感）
 *          g_ValueOfAD[2]：3400	    g_ValueOfAD[3]：3400
 *	       （垂直左电感）	              （垂直右电感）
 * date *		     2020
 *************************************************************************/

void DirectionControl(void)
{
	static float g_fDirectionErrorTemp[2][5];
	
	Read_ADC();		//获取电感值
	
	if((g_ValueOfAD[0]<20 || g_ValueOfAD[1]<20) && flag_timego>400)	
	Flag_Stop = OFF;//冲出赛道停车保护
        
	g_ValueOfAD[0] = (g_ValueOfAD[0] < 10? 10:g_ValueOfAD[0]);//四个电感值限幅
	g_ValueOfAD[1] = (g_ValueOfAD[1] < 10? 10:g_ValueOfAD[1]);
	g_ValueOfAD[2] = (g_ValueOfAD[2] < 10? 10:g_ValueOfAD[2]);
	g_ValueOfAD[3] = (g_ValueOfAD[3] < 10? 10:g_ValueOfAD[3]);
        
        g_ValueOfAD[4] = (g_ValueOfAD[4] < 10? 10:g_ValueOfAD[4]);//红外测距限幅
		
	
	g_fDirectionError[0] = (float)(g_ValueOfAD[0] - g_ValueOfAD[1])/(g_ValueOfAD[0] + g_ValueOfAD[1]);//水平电感的差比和作为偏差
	g_fDirectionError[0] = (g_fDirectionError[0]>= 1? 1:g_fDirectionError[0]);
	g_fDirectionError[0] = (g_fDirectionError[0]<=-1?-1:g_fDirectionError[0]);//偏差限幅
	
        
	g_fDirectionError[1] = (float)(g_ValueOfAD[2] - g_ValueOfAD[3])/(g_ValueOfAD[2] + g_ValueOfAD[3]);//垂直电感的差比和作为偏差   
	g_fDirectionError[1] = (g_fDirectionError[1]>= 1? 1:g_fDirectionError[1]);	
	g_fDirectionError[1] = (g_fDirectionError[1]<=-1?-1:g_fDirectionError[1]);//偏差限幅	
	  
        
	g_fDirectionErrorTemp[0][4] = g_fDirectionErrorTemp[0][3];
	g_fDirectionErrorTemp[0][3] = g_fDirectionErrorTemp[0][2];
	g_fDirectionErrorTemp[0][2] = g_fDirectionErrorTemp[0][1];
	g_fDirectionErrorTemp[0][1] = g_fDirectionErrorTemp[0][0];
	g_fDirectionErrorTemp[0][0] = g_fDirectionError[0];
	g_fDirectionError_dot[0] = 5*(g_fDirectionErrorTemp[0][0]-g_fDirectionErrorTemp[0][3]);//水平电感的偏差微分
         
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]> 0.7? 0.7:g_fDirectionError_dot[0]);
	g_fDirectionError_dot[0] = (g_fDirectionError_dot[0]<-0.7?-0.7:g_fDirectionError_dot[0]);//偏差微分限幅
        

	g_fDirectionErrorTemp[1][4] = g_fDirectionErrorTemp[1][3];
	g_fDirectionErrorTemp[1][3] = g_fDirectionErrorTemp[1][2];
	g_fDirectionErrorTemp[1][2] = g_fDirectionErrorTemp[1][1];
	g_fDirectionErrorTemp[1][1] = g_fDirectionErrorTemp[1][0];
	g_fDirectionErrorTemp[1][0] = g_fDirectionError[1];
	g_fDirectionError_dot[1] = 5*(g_fDirectionErrorTemp[1][0]-g_fDirectionErrorTemp[1][3]);//垂直电感的偏差微分
        
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]> 0.7? 0.7:g_fDirectionError_dot[1]);
	g_fDirectionError_dot[1] = (g_fDirectionError_dot[1]<-0.7?-0.7:g_fDirectionError_dot[1]);//偏差微分限幅

        g_ValueOfADError=g_ValueOfAD[0]-g_ValueOfAD[1];//水平两个电感的差值
        g_ValueOfADError=(g_ValueOfADError>0?g_ValueOfADError:-g_ValueOfADError);
        
        //if(slow_flag==0)
        FLEXCOMM0_DriverIRQHandler();  //获取distanc超声波的值
        
        g_distance[4]=g_distance[3];
        g_distance[3]=g_distance[2];
        g_distance[2]=g_distance[1];
        g_distance[1]=g_distance[0];
        g_distance[0]=distance;
        distance_filter();  //滤除超声波跳变的最小值
 /*       
        g_Infrared[4]=g_Infrared[3];
        g_Infrared[3]=g_Infrared[2];
        g_Infrared[2]=g_Infrared[1];
        g_Infrared[1]=g_Infrared[0];
        g_Infrared[0]=Infrared;
        infrared_filter();  //滤除红外跳变的最大值

*/
        
/**************************传球方案******************************/  
 
  /*****方案1*******  
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
       //  ctimer_pwm_duty(TIMER4_PWMCH0_A6,600);//停车打开DJ
          uart_putchar(USART_2,0x0e);//无线透传发送数据(起跑信号)
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
          ctimer_pwm_duty(TIMER4_PWMCH0_A6,580);//停车打开DJ
         // if(sever>=580) stop_sever=0;
          uart_putchar(USART_2,0x0e);//无线透传发送数据(起跑信号)
        }
        else uart_putchar(USART_2,0x01);
 */
   
      /*****方案2******/ 
      if(set_distance >= g_rellaydistance && set_redout <= g_ValueOfAD[4] && g_ValueOfADError<=800 && slow_flag==0) 
      {
        slow_flag=1;
      } 
      if(slow_flag==1)      
      {
        ctimer_pwm_duty(TIMER4_PWMCH0_A6,530);//打开DJ
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
/***********************************出库处理***************************/
        
        if(gpio_get(KEY2) == 0)
        {
          dire_garage=0;
          gpio_set(LED3,0);
        }
        else dire_garage=1;
        
        flag_timego++;
        if(flag_timego<=75)   //慢速起步
        {
          flag_go=1;
         // gpio_set(BEEP,1);
          if(dire_garage == 0)   //左出库
          {
            g_nLeftPWM=3500;
            g_nRighPWM=5600;
          }
          if(dire_garage == 1)  //右出库
          {
            g_nLeftPWM=5600;
            g_nRighPWM=3500;
          }
        }
        
        if(flag_timego>75)   //出库打角
        {
          // gpio_set(BEEP,0);
           flag_go=0; 
        }       

        
        
        
/***************************环岛处理****************************/
   
if((g_ValueOfAD[0]>2700)&&(g_ValueOfAD[1]>2700)&&(g_ValueOfAD[2]<700)&&(g_ValueOfAD[3]<700)&&(flag_timeintoround==0)&&(flag_go==0))
{
  flag_timeintoround=120; //入环打角时间
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

        //方向算法（位置式PD)
        if(flag_Round != ON && slow_flag!=1)
	g_fDirectionControlOut = g_fDirectionError[0]*g_dirControl_P*10 + g_fDirectionError_dot[0]*g_dirControl_D*10; //P10000,D10000
        
        //入环岛    
        if(flag_Round == ON)
          g_fDirectionControlOut = g_fDirectionError[1]*g_roundControl_P*10 + g_fDirectionError_dot[1]*g_roundControl_D*10;                    
                                                          //800                //840
        if(slow_flag==1)
          g_fDirectionControlOut = g_fDirectionError[0]*g_dirControl_P + g_fDirectionError_dot[0]*g_dirControl_D;
        
}

/***************************************
*file*       电感信号采集处理
*date*           2020 
***************************************/
void Read_ADC(void)
{
     int16  i,j,k,temp;
     int16  ad_valu[5][5],ad_valu1[5],ad_sum[5];
     int16  ValueOfADOld[5],ValueOfADNew[5];
        
//**********************************红外处理************************************//
     
    // Infrared=adc_convert(ADC5,ADC_12BIT);
     
//*******************************电感值滤波处理*******************************//    
   for(i=0;i<5;i++)
     {
         ad_valu[0][i]=adc_convert(ADC1,ADC_12BIT);  	// AD1水平左
         ad_valu[1][i]=adc_convert(ADC2,ADC_12BIT);     // AD2水平右
         ad_valu[2][i]=adc_convert(ADC3,ADC_12BIT);  	// AD3垂直左
         ad_valu[3][i]=adc_convert(ADC4,ADC_12BIT);     // AD4垂直右
         ad_valu[4][i]=adc_convert(ADC5,ADC_12BIT);     // 红外测距
     }
     
/*=========================冒泡排序升序==========================*///舍弃最大值和最小值
     for(i=0;i<5;i++)
     {
        for(j=0;j<4;j++)
        {
           for(k=0;k<4-j;k++)
           {
              if(ad_valu[i][k] > ad_valu[i][k+1])        //前面的比后面的大  则进行交换
              {
                 temp = ad_valu[i][k+1];
                 ad_valu[i][k+1] = ad_valu[i][k];
                 ad_valu[i][k] = temp;
              }
           }
        }
     }
     
/*===========================中值滤波=================================*/
    for(i=0;i<5;i++)    //求中间三项的和
     {
        ad_sum[i] = ad_valu[i][1] + ad_valu[i][2] + ad_valu[i][3];
        ad_valu1[i] = ad_sum[i] / 3;
     }

	
	 for(i=0;i<5;i++)            //将数值中个位数除掉
	 {
	 	g_ValueOfAD[i] = (int16)(ad_valu1[i]/10*10);

		//采集梯度平滑，每次采集最大变化40
		ValueOfADOld[i] = g_ValueOfADFilter[i];
		ValueOfADNew[i] = g_ValueOfAD[i];
		
		if(ValueOfADNew[i]>=ValueOfADOld[i])
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])>50?(ValueOfADOld[i]+50):ValueOfADNew[i]);
		else
			g_ValueOfADFilter[i] = ((ValueOfADNew[i]-ValueOfADOld[i])<-60?(ValueOfADOld[i]-60):ValueOfADNew[i]);
	 }
	 
}

void distance_filter(void)     //超声波测距滤波(取平均值,滤去跳变值)
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
void infrared_filter(void)    //红外滤波
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