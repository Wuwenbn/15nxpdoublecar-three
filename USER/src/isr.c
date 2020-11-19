/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   	成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		IAR 8.32.1
 * @Target core		LPC54606J512BD100
 * @date       		2020
 * @user                abn
 ********************************************************************************************************************/

#include "headfile.h"
#include "isr.h"


uint32 test_num;

void GINT0_DriverIRQHandler(void)
{
    if(1 == GINT0_FLAG)
    {
        if(1 == gpio_get(A0)) //上升沿或者高电平
        {
            test_num++;
        }
        else//下降沿或者低电平
        {
            test_num++;
        }
        CLEAR_GINT0_FLAG;
    }
}

//uint8 ddf[500];
//uint32 fg;
uint16 distance = 0;	
uint8 dat[3];
uint8 num;

void FLEXCOMM0_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART0_FIFO_FLAG;
    
    
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
      uart_getchar(USART_0,&dat[num]);
      if(dat[0] != 0xa5)num = 0;	//检查头帧是否正确，不正确就重新接收
      else num++;
		
	if(num==3)					//接收完成，开始处理数据
	{
		num = 0;
		distance = dat[1]<<8 | dat[2];	//得到超声波模块测出的距离
	}
      //  uart_query(USART_0,&ddf[fg]);
       // fg++;
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//发送FIFO达到设定水平（库默认设定水平 当发送FIFO为空的时候触发中断）
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        USART0->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART0->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
    }

}
/*
uint16 pit_test;
void RIT_DriverIRQHandler(void)
{
    PIT_FLAG_CLEAR;
    pit_test++;

    
}*/

//uint16 pint_test;
long high_time;
uint8 flag_mux;

void PIN_INT2_DriverIRQHandler(void)
{

    
    //pint_test++;
}



uint16  dma_test;
void DMA0_DriverIRQHandler(void)
{
    dma_test++;
    //CLEAR_DMA_FLAG(MT9V032_DMA_CH);
    //ov7725_dma();       //小钻风dma中断代码，当使用小钻风的时候执行该代码
    mt9v032_dma();      //总钻风dma中断代码，当使用总钻风的时候执行该代码
}

uint16  sct_test;
void SCT0_DriverIRQHandler(void)
{
    uint32_t flag;
    flag = READ_SCT_FLAG;   //读取中断标志位
    CLEAR_SCT_FLAG;         //清除标志位
    

    if(flag & (1<<0))         //场中断
    {
        sct_test++;
        //ov7725_vsync(); //小钻风场中断代码，当使用小钻风的时候执行该代码
        VSYNC();        //总钻风场中断代码，当使用总钻风的时候执行该代码
    }

}

void FLEXCOMM5_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART5_FIFO_FLAG;
    
    
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//接收FIFO达到设定水平（库默认设定水平 当接收FIFO有一个数据的时候触发中断）
    {
        mt9v032_cof_uart_interrupt();
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//接收FIFO错误
    {
        
        USART5->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//清空RX FIFO
        USART5->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
    }

}

/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器 通道0得中断
void PIT_CH0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位

WDT_BOD_DriverIRQHandler
DMA0_DriverIRQHandler
GINT0_DriverIRQHandler
GINT1_DriverIRQHandler
PIN_INT0_DriverIRQHandler
PIN_INT1_DriverIRQHandler
PIN_INT2_DriverIRQHandler
PIN_INT3_DriverIRQHandler
UTICK0_DriverIRQHandler
MRT0_DriverIRQHandler
CTIMER0_DriverIRQHandler
CTIMER1_DriverIRQHandler
SCT0_DriverIRQHandler
CTIMER3_DriverIRQHandler
FLEXCOMM0_DriverIRQHandler
FLEXCOMM1_DriverIRQHandler
FLEXCOMM2_DriverIRQHandler
FLEXCOMM3_DriverIRQHandler
FLEXCOMM4_DriverIRQHandler
FLEXCOMM5_DriverIRQHandler
FLEXCOMM6_DriverIRQHandler
FLEXCOMM7_DriverIRQHandler
ADC0_SEQA_DriverIRQHandler
ADC0_SEQB_DriverIRQHandler
ADC0_THCMP_DriverIRQHandler
DMIC0_DriverIRQHandler
HWVAD0_DriverIRQHandler
USB0_NEEDCLK_DriverIRQHandler
USB0_DriverIRQHandler
RTC_DriverIRQHandler
Reserved46_DriverIRQHandler
Reserved47_DriverIRQHandler
PIN_INT4_DriverIRQHandler
PIN_INT5_DriverIRQHandler
PIN_INT6_DriverIRQHandler
PIN_INT7_DriverIRQHandler
CTIMER2_DriverIRQHandler
CTIMER4_DriverIRQHandler
RIT_DriverIRQHandler
SPIFI0_DriverIRQHandler
FLEXCOMM8_DriverIRQHandler
FLEXCOMM9_DriverIRQHandler
SDIO_DriverIRQHandler
CAN0_IRQ0_DriverIRQHandler
CAN0_IRQ1_DriverIRQHandler
CAN1_IRQ0_DriverIRQHandler
CAN1_IRQ1_DriverIRQHandler
USB1_DriverIRQHandler
USB1_NEEDCLK_DriverIRQHandler
ETHERNET_DriverIRQHandler
ETHERNET_PMT_DriverIRQHandler
ETHERNET_MACLP_DriverIRQHandler
EEPROM_DriverIRQHandler
LCD_DriverIRQHandler
SHA_DriverIRQHandler
SMARTCARD0_DriverIRQHandler
SMARTCARD1_DriverIRQHandler
*/



