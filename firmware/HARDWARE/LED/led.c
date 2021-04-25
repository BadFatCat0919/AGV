//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "led.h"
/********************************************************************************
	功能：	LED初始化
	参数：	无
	返回：	无
	备注：	无
*********************************************************************************/
void LED_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
}
/********************************************************************************
	功能：	LED_MCU闪烁
	参数：	time	闪烁频率
	返回：	无
	备注：	无
*********************************************************************************/
void LED_MCU_Flash(u16 time)
{
	  static int temp;
	  if(time==0)
	  	LED_MCU=LED_OFF;
	  else
	  	if(++temp==time)
				LED_MCU=!LED_MCU,temp=0;
}
//////////////////////////////////////////////////////////////////////////////////
/********************************************************************************
	功能：	LED_WAR闪烁
	参数：	time	闪烁频率
	返回：	无
	备注：	无
*********************************************************************************/
void LED_WAR_Flash(u16 time)
{
	  static int temp;
	  if(time==0)
	  	LED_WAR=LED_OFF;
	  else
	  	if(++temp==time)
		  LED_WAR=!LED_WAR,temp=0;
}
//////////////////////////////////////////////////////////////////////////////////
