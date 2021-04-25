//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "wireless.h"
/********************************************************************************
	功能：	无线遥控初始化
	参数：	无
	返回：	无
	备注：	无
*********************************************************************************/
void WIRELESS_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6;	 
 	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPD;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
