#include "SOLGUI_Type.h"
#include "SOLGUI_Config.h"
#include "SOLGUI_Hardware.h"

//*******************【屏幕驱动头文件】*******************
#include "oled.h"
#include "delay.h"

//##########################【需要用户实现的部分】############################

void SOLGUI_Hardware_Init(void)
{
//=========【用户硬件初始化移植处】=======

//========================================
}

void SOLGUI_Hardware_FillScreen(u8 GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE])
{
//=========【用户硬件屏幕填充函数移植处】=======
	int i=0,n=0;
	for(i=0;i<SCREEN_Y_PAGE;i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD);
		OLED_WR_Byte(0x00,OLED_CMD);
		OLED_WR_Byte(0x10,OLED_CMD);
		for(n=0;n<SCREEN_X_WIDTH;n++)
		{
			OLED_WR_Byte(GRAM[n][i],OLED_DATA);
		}
	}	  
//========================================
}

void SOLGUI_Hardware_ClearScreen(void)
{
//=========【用户硬件清屏函数移植处】=======
	u8 i,n;  
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	}  
//========================================	
}



