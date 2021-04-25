//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "delay.h"

#define KEY_BOARD	PBin(14)	//���ذ���
#define KEY_OK 		PAin(8)		//OK��
#define KEY_UP 		PCin(1)		//UP��
#define KEY_DOWN 	PCin(2)		//DOWN��
#define KEY_LEFT 	PCin(3)		//LEFT��
extern FlagStatus KEY_RIGHT_USE_FLAG;
#define KEY_RIGHT	(KEY_RIGHT_USE_FLAG == SET? (GraySensor2>20):1)//RIGHT��
#define KEY_BACK 	PCin(5)		//BACK��

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
