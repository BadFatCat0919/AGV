//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "key.h"
#include "buzzer.h"
/********************************************************************************
	���ܣ�	������ʼ��
	������	��
	���أ�	��
	��ע��	��
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
	���ܣ�	ɨ����������
	������	��
	���أ�	��ֵ
	��ע��	��
*********************************************************************************/
u8 KEY_Scan(void)
{
	u8 value=0;
	if ( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
				KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS )
	{
		delay_ms(3);
		BUZZER = BUZZER_ON;												  //����������
		if (KEY_UP 		== PRESS)value = __KEY_UP;		//�ϼ�
		if (KEY_DOWN 	== PRESS)value = __KEY_DOWN;	//�¼�
		if (KEY_LEFT 	== PRESS)value = __KEY_LEFT;	//���
		if (KEY_RIGHT	== PRESS)value = __KEY_RIGHT;	//�Ҽ�
		if (KEY_OK 		== PRESS)value = __KEY_OK;		//ȷ��
		if (KEY_BACK	== PRESS)value = __KEY_BACK;	//����
	}
	while( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
					KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS );
	delay_ms(3);
	while( KEY_OK == PRESS || KEY_BACK == PRESS || KEY_UP == PRESS ||\
					KEY_LEFT == PRESS || KEY_DOWN == PRESS || KEY_RIGHT == PRESS );
	BUZZER = BUZZER_OFF;												  //����������
	return value;
}
/********************************************************************************
	���ܣ�	ɨ����ذ���
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��OK��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��BACK��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��UP��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��RIGHT��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��DOWN��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
	���ܣ�	ɨ��LEFT��
	������	��
	���أ�	1	������
			0	δ����
	��ע��	��
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
