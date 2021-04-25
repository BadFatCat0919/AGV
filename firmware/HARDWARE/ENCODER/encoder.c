//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "encoder.h"
/********************************************************************************
	功能：	编码器初始化
	参数：	无
	返回：	无
	备注：	
            TIM2 
			CH1		A15
			CH2		B3
            TIM3
			CH1		C6
			CH2		C7
*********************************************************************************/
void ENCODER_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2|GPIO_FullRemap_TIM3,ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin					=	GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode				= 	GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed 				=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin					=	GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin					=	GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    TIM2_Init();
    TIM3_Init();
}
/********************************************************************************
	功能：	读编码器值
	参数：	无
	返回：	无
	备注：	无
*********************************************************************************/
int Read_Encoder(u8 EncoderX)
{
	int Encoder;
	switch (EncoderX)
	{
		case 1:
			Encoder = -(short)TIM2->CNT,TIM2->CNT=0;
			break;
		case 2:
			Encoder =  (short)TIM3->CNT,TIM3->CNT=0;
			break;
	
		default:
			Encoder = 0;
			break;
	}
	return Encoder;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
