/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		isr
 * @company	   	�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴LPC546XX_config.h�ļ��ڰ汾�궨��
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
        if(1 == gpio_get(A0)) //�����ػ��߸ߵ�ƽ
        {
            test_num++;
        }
        else//�½��ػ��ߵ͵�ƽ
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
    
    
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//����FIFO�ﵽ�趨ˮƽ����Ĭ���趨ˮƽ ������FIFO��һ�����ݵ�ʱ�򴥷��жϣ�
    {
      uart_getchar(USART_0,&dat[num]);
      if(dat[0] != 0xa5)num = 0;	//���ͷ֡�Ƿ���ȷ������ȷ�����½���
      else num++;
		
	if(num==3)					//������ɣ���ʼ��������
	{
		num = 0;
		distance = dat[1]<<8 | dat[2];	//�õ�������ģ�����ľ���
	}
      //  uart_query(USART_0,&ddf[fg]);
       // fg++;
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//����FIFO�ﵽ�趨ˮƽ����Ĭ���趨ˮƽ ������FIFOΪ�յ�ʱ�򴥷��жϣ�
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//����FIFO����
    {
        USART0->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART0->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//���RX FIFO
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
    //ov7725_dma();       //С���dma�жϴ��룬��ʹ��С����ʱ��ִ�иô���
    mt9v032_dma();      //�����dma�жϴ��룬��ʹ��������ʱ��ִ�иô���
}

uint16  sct_test;
void SCT0_DriverIRQHandler(void)
{
    uint32_t flag;
    flag = READ_SCT_FLAG;   //��ȡ�жϱ�־λ
    CLEAR_SCT_FLAG;         //�����־λ
    

    if(flag & (1<<0))         //���ж�
    {
        sct_test++;
        //ov7725_vsync(); //С��糡�жϴ��룬��ʹ��С����ʱ��ִ�иô���
        VSYNC();        //����糡�жϴ��룬��ʹ��������ʱ��ִ�иô���
    }

}

void FLEXCOMM5_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART5_FIFO_FLAG;
    
    
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//����FIFO�ﵽ�趨ˮƽ����Ĭ���趨ˮƽ ������FIFO��һ�����ݵ�ʱ�򴥷��жϣ�
    {
        mt9v032_cof_uart_interrupt();
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//����FIFO����
    {
        
        USART5->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//���RX FIFO
        USART5->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
    }

}

/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

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



