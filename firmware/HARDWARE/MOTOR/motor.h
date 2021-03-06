//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "timer.h"

#define MOTOR_LF  TIM5->CCR4
#define MOTOR_LB  TIM5->CCR2
#define MOTOR_RF  TIM5->CCR1
#define MOTOR_RB  TIM5->CCR3

void MOTOR_Init(void);
void MOTOR_Release(void);

#endif
