//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"

int  __abs(int number);
int  Velocity_PI_L(int Now,int Target);
int  Velocity_PI_R(int Now,int Target);
int  Angle_PID_Yaw(float Now,float Target,FlagStatus* Arrive_Flag);
int  Angle_PID_CCD(int Now,int Target,FlagStatus* Arrive_Flag);
void EXTI15_10_IRQHandler(void);
void Branch_Out_Yaw(void);
void Set_PWM(int motor_l,int motor_r);
void Amplitude_Limiting(int* Variable,int Range);
void Yaw_Reset(void);
void Delay_n5ms(u16 n5ms);
void Delay_sec(u8 sec);

#endif
//////////////////////////////////////////////////////////////////////////////////
