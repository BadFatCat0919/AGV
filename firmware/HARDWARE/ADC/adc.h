#ifndef __ADC_H
#define __ADC_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
void  Adc_Init(void);
void  ADC2_Init(void);
u16 Get_Adc_Average(u8 ch,u8 times);
u16 Get_Adc1_Average(u8 ch,u8 times);
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch);
u16 Get_Adc2(u8 ch);

		 				    
#endif
