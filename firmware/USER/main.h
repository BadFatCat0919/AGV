//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#ifndef __MAIN_H
#define __MAIN_H

#include "sys.h"
#include "key.h"
#include "led.h"
#include "buzzer.h"
#include "oled.h"
#include "ioi2c.h"
#include "mpu6050.h"					   
#include "exti.h"
#include "wireless.h"
#include "encoder.h"
#include "motor.h"
#include "OpenMV.h"
#include "usart.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "adc.h"
#include "ccd.h"
#include "UNO.h"
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int        CAR_Velocity,CAR_Yaw,MOTOR_L_Velocity,MOTOR_R_Velocity;
extern int        Velocity_L,Velocity_R;
extern int        GraySensor,GraySensor2,GraySensor_Threshold,IRSensor,IRSensor_Threshold;
extern int        Match_Velocity;
extern float      Velocity_KP_L,Velocity_KI_L,Velocity_KP_R,Velocity_KI_R;
extern float      Angle_KP_Yaw,Angle_KI_Yaw,Angle_KD_Yaw;
extern float      Angle_KP_CCD,Angle_KI_CCD,Angle_KD_CCD;
extern float      Pitch,Roll,Yaw,yaw_correct;
extern FlagStatus Yaw_Reset_Flag,CAR_Run_Flag,Divide_Ctrl_Flag;
extern FlagStatus Yaw_PID_Flag,CCD_PID_Flag;
extern FlagStatus Yaw_Arrive_Flag,CCD_Arrive_Flag;
extern FlagStatus Gray_Line_Flag,IR_Find_Flag,OpenMV_Find_Flag,IR_Use_Flag,OpenMV_Use_Flag;

void FlagStatus_Reversal(FlagStatus* flag);

#endif
//////////////////////////////////////////////////////////////////////////////////
