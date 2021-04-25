//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
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
