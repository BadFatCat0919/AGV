//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "motor.h"
/********************************************************************************
	功能：	电机初始化
	参数：	无
	返回：	无
	备注：	TIM5
			CH1		A0
			CH2		A1
			CH3		A2
			CH4		A3
*********************************************************************************/
void MOTOR_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin					=	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode				= 	GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed 				=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM5_Init();
}
/********************************************************************************
	功能：	电机释放
	参数：	无
	返回：	无
	备注：	无
*********************************************************************************/
void MOTOR_Release(void)
{
	MOTOR_LF = 0;
	MOTOR_LB = 0;
	MOTOR_RF = 0;
	MOTOR_RB = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
