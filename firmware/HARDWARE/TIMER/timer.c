//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ���������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "timer.h"
/********************************************************************************
	���ܣ�	TIM2��ʼ��
	������	��
	���أ�	��
	��ע��	������ģʽ
*********************************************************************************/
void TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef		TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_Period			=	ENCODER_TIM_PERIOD-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler		=	0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision	=	TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);              
                 
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);	 
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
		
	TIM2->CNT = 0;

	TIM_Cmd(TIM2, ENABLE);
}
/********************************************************************************
	���ܣ�	TIM3��ʼ��
	������	��
	���أ�	��
	��ע��	������ģʽ
*********************************************************************************/
void TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef		TIM_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_Period			=	ENCODER_TIM_PERIOD-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler		=	0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision	=	TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);              
                 
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);	 
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
		
	TIM3->CNT = 0;

	TIM_Cmd(TIM3, ENABLE);
}
/********************************************************************************
	���ܣ�	TIM5��ʼ��
	������	��
	���أ�	��
	��ע��	PWM���ģʽ
			PWMƵ��=72000000/(0+1)/(7199+1)=10KHz
*********************************************************************************/
void TIM5_Init(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef 		TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_Period 			  =	7199;
	TIM_TimeBaseInitStruct.TIM_Prescaler 		  =	0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision	=	0;
	TIM_TimeBaseInitStruct.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode 				  = 	TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState 		= 	TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity 			= 	TIM_OCPolarity_Low;
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

	TIM_Cmd(TIM5, ENABLE);
}
/********************************************************************************
	���ܣ�	TIM6��ʼ��
	������	��
	���أ�	��
	��ע��	����50ms��ʱ
*********************************************************************************/
void TIM6_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_Period        = 499;
	TIM_TimeBaseInitStruct.TIM_Prescaler     = 7199;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStruct.TIM_CounterMode   = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM6, ENABLE);			 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
