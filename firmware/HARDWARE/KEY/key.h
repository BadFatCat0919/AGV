//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "delay.h"

#define KEY_BOARD	PBin(14)	//板载按键
#define KEY_OK 		PAin(8)		//OK键
#define KEY_UP 		PCin(1)		//UP键
#define KEY_DOWN 	PCin(2)		//DOWN键
#define KEY_LEFT 	PCin(3)		//LEFT键
extern FlagStatus KEY_RIGHT_USE_FLAG;
#define KEY_RIGHT	(KEY_RIGHT_USE_FLAG == SET? (GraySensor2>20):1)//RIGHT键
#define KEY_BACK 	PCin(5)		//BACK键

#define __KEY_OK 	  1
#define __KEY_BACK 	2
#define __KEY_UP 	  3
#define __KEY_DOWN 	4
#define __KEY_LEFT 	5
#define __KEY_RIGHT 6

#define PRESS     0
#define RELEASE   !PRESS

void KEY_Init(void);
u8	 KEY_Scan(void);
u8   KEY_OK_Scan(void);
u8   KEY_BACK_Scan(void);
u8   KEY_UP_Scan(void);
u8   KEY_DOWN_Scan(void);
u8   KEY_LEFT_Scan(void);
u8   KEY_RIGHT_Scan(void);

#endif
//////////////////////////////////////////////////////////////////////////////////
