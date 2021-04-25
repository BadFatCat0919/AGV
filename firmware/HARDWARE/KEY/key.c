//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "key.h"
#include "buzzer.h"
/********************************************************************************
	功能：	按键初始化
	参数：	无
	返回：	无
	备注：	无
*********************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8;	 
 	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_14;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/********************************************************************************
	功能：	扫描六个按键
	参数：	无
	返回：	键值
	备注：	无
*********************************************************************************/
u8 KEY_Scan(void)
{
	u8 value=0;
	if ( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
				KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS )
	{
		delay_ms(3);
		BUZZER = BUZZER_ON;												  //蜂鸣器发声
		if (KEY_UP 		== PRESS)value = __KEY_UP;		//上键
		if (KEY_DOWN 	== PRESS)value = __KEY_DOWN;	//下键
		if (KEY_LEFT 	== PRESS)value = __KEY_LEFT;	//左键
		if (KEY_RIGHT	== PRESS)value = __KEY_RIGHT;	//右键
		if (KEY_OK 		== PRESS)value = __KEY_OK;		//确认
		if (KEY_BACK	== PRESS)value = __KEY_BACK;	//返回
	}
	while( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
					KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS );
	delay_ms(3);
	while( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
					KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS );
	BUZZER = BUZZER_OFF;												  //蜂鸣器发声
	return value;
}
/********************************************************************************
	功能：	扫描板载按键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_BOARD_Scan(void)
{
	if(KEY_BOARD == PRESS)
	{
		delay_ms(10);
		if(KEY_BOARD == PRESS)
		{
			while(KEY_BOARD == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描OK键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_OK_Scan(void)
{
	if(KEY_OK == PRESS)
	{
		delay_ms(10);
		if(KEY_OK == PRESS)
		{
			while(KEY_OK == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描BACK键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_BACK_Scan(void)
{
	if(KEY_BACK == PRESS)
	{
		delay_ms(10);
		if(KEY_BACK == PRESS)
		{
			while(KEY_BACK == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描UP键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_UP_Scan(void)
{
	if(KEY_UP == PRESS)
	{
		delay_ms(10);
		if(KEY_UP == PRESS)
		{
			while(KEY_UP == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描RIGHT键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_RIGHT_Scan(void)
{
	if(KEY_RIGHT == PRESS)
	{
		delay_ms(10);
		if(KEY_RIGHT == PRESS)
		{
			while(KEY_RIGHT == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描DOWN键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_DOWN_Scan(void)
{
	if(KEY_DOWN == PRESS)
	{
		delay_ms(10);
		if(KEY_DOWN == PRESS)
		{
			while(KEY_DOWN == PRESS);
			return 1;
		}
	}
	return 0;
}
/********************************************************************************
	功能：	扫描LEFT键
	参数：	无
	返回：	1	被按下
			0	未按下
	备注：	无
*********************************************************************************/
u8 KEY_LEFT_Scan(void)
{
	if(KEY_LEFT == PRESS)
	{
		delay_ms(10);
		if(KEY_LEFT == PRESS)
		{
			while(KEY_LEFT == PRESS);
			return 1;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
