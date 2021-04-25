//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#ifndef __ACTION_H
#define __ACTION_H

#include "main.h"
#include "control.h"

void Audible_and_Visual_Alarm(void);
void CAR_Breaking(void);
void CAR_Move(int velocity);
void CAR_Turn_OpenLoop(int velocity);
void CAR_Divide_Ctrl(int velocity_left,int velocity_right);
void CAR_Move_YawCorrect(int velocity);
void CAR_Move_CCDCorrect(int velocity);
void CAR_Turn(int yaw);
void Move_NextPoint(int velocity);
void Move_NextPoint_Pass(int velocity);
FlagStatus Move_NextPoint_IRSearch(int search_velocity,int find_velocity);
FlagStatus Move_NextPoint_Pass_IRSearch(int search_velocity,int find_velocity);
FlagStatus Move_NextPoint_OpenMVSearch(int search_velocity,int find_velocity);
FlagStatus Move_NextPoint_Pass_OpenMVSearch(int search_velocity,int find_velocity);
FlagStatus Rotate_Search(int velocity);
void Turn_Left(void);
void Turn_Right(void);
void Turn_Back(void);
void Enter_CoordinateSystem(void);
void Wait_StartCMD(void);

#endif
//////////////////////////////////////////////////////////////////////////////////
