//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "match.h"

int Match_Velocity=500;
int Match_Velocity_Search=500;
int Match_Velocity_OpenMVSearch=400;

void Around_Block(void);
/********************************************************************************
    ���ܣ�	����һ����A
    ������	��
    ���أ�	��
    ��ע��	˳����Ȧ����3#��4#����
*********************************************************************************/
void Task_I_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Move_NextPoint_Pass(600);	            //����2#��

	Move_NextPoint(Match_Velocity);	      //����3#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Turn_Right();                         //��ת
	
	Move_NextPoint(Match_Velocity);	      //����6#��

	Turn_Right();                         //��ת
	Move_NextPoint_Pass(600);							//����5#��

	Move_NextPoint(Match_Velocity);	      //����4#��
	Audible_and_Visual_Alarm();           //���ⱨ��
}
/********************************************************************************
    ���ܣ�	����һ����B
    ������	��
    ���أ�	��
    ��ע��	ֱ�ߵ���3#�㣬��ת��ֱ�ߵ���1#��4#����ߣ�
					��תCCD���������ϣ�ֱ�ߵ���4#��
*********************************************************************************/
int Task_I_SchemeB_Angle = -151;
void Task_I_SchemeB(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Move_NextPoint_Pass(600);	            //����2#��

	Move_NextPoint(Match_Velocity);	      //����3#��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	CAR_Turn(Task_I_SchemeB_Angle);	    //��ת����1#��4#�����
	CAR_Breaking();												//ɲ��
	CAR_Move_YawCorrect(500);	            //����ƫ���ǻ��ջ�ֱ��
	Delay_n5ms(80);										  	//����������ĺڵ�
  while(Gray_Line_Flag == RESET);				//Խ��2#��5#�����
	Delay_n5ms(160);											//���ֵ�ǰ�ٶ�����
	CAR_Velocity = 100;										//��������Ŀ�꣬����
  while(Gray_Line_Flag == RESET);				//����1#��4#�����
	CAR_Turn(80);													//��ת����ڵ�
	Move_NextPoint(Match_Velocity);				//��CCD�����µ���4#��
	Audible_and_Visual_Alarm();           //���ⱨ��
}
int Task_I_SchemeC_Angle = -158;
/********************************************************************************
    ���ܣ�	����һ����C
    ������	��
    ���أ�	��
    ��ע��	ֱ�ߵ���3�㣬��ת151�㣬ֱ�ߵ���4#��
*********************************************************************************/
void Task_I_SchemeC(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Move_NextPoint_Pass(600);	            //����2#��
	Move_NextPoint(Match_Velocity);	      //����3#��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	CAR_Turn(Task_I_SchemeC_Angle);	    //��ת����4#�����
	CAR_Breaking();												//ɲ��
	CAR_Move_YawCorrect(1000);	          //����ƫ���ǻ��ջ�ֱ��
	Delay_n5ms(120);											//����������ĺ���
  while(Gray_Line_Flag == RESET);				//Խ��2#��5#�����
	Delay_n5ms(23);	  										//���ֵ�ǰ�ٶ�����
	
  CAR_Velocity = 200;										//����
  
	while(Gray_Line_Flag == RESET);				//����4#��
	CAR_Breaking();												//ɲ��
	
	CAR_Turn(-35);												//��ת����ڵ�
	if(CCD_LineCenter>-63)
	Move_NextPoint(Match_Velocity);				//��CCD�����µ���4#��
	Audible_and_Visual_Alarm();           //���ⱨ��
}
/********************************************************************************
    ���ܣ�	���������A
    ������	��
    ���أ�	��
    ��ע��	˳�򵽴�1#��2#��3#��6#�ĵ�
*********************************************************************************/
void Task_II_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();							//��������ϵ������1#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Move_NextPoint_Pass(Match_Velocity);	//����2#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Move_NextPoint(Match_Velocity);	      //����3#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Turn_Right();                         //��ת
	
	Move_NextPoint(Match_Velocity);	      //����6#��
	Audible_and_Visual_Alarm();           //���ⱨ��
}
/********************************************************************************
    ���ܣ�	����������A
    ������	��
    ���أ�	��
    ��ע��	˳�򵽴�1#��2#��3#��6#�ĵ�
*********************************************************************************/
void Task_III_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();							//��������ϵ������1#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Move_NextPoint_Pass(Match_Velocity);	//����2#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Move_NextPoint(Match_Velocity);	      //����3#��
	Audible_and_Visual_Alarm();           //���ⱨ��

	Turn_Right();                         //��ת
	
	Move_NextPoint(Match_Velocity);	      //����6#��
	Audible_and_Visual_Alarm();           //���ⱨ��
}
/********************************************************************************
    ���ܣ�	�����ķ���A
    ������	��
    ���أ�	��
    ��ע��	��������
*********************************************************************************/
void Task_IV_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();							//��������ϵ������1#��

	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��2#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������3#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��6#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������9#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��8#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������7#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������4#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��5#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������6#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Back();													//��ͷ
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��5#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������4#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������1#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
}
/********************************************************************************
    ���ܣ�	�����ķ���B
    ������	��
    ���أ�	��
    ��ע��	����ɨ��
*********************************************************************************/
void Task_IV_SchemeB(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();							//��������ϵ������1#��
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������2#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������5#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//���������飬���������Χ�ĸ���
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//���������飬���������Χ�ĸ���
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//���������飬���������Χ�ĸ���
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������2#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������3#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��6#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������9#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ����ͨ��8#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������7#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//����ǰ��������4#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
}
/********************************************************************************
    ���ܣ�	�����巽��A
    ������	��
    ���أ�	��
    ��ע��	��������
*********************************************************************************/
void Task_V_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Wait_StartCMD();											//�ȴ���������ָ��
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();							//��������ϵ������1#��

	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ����ͨ��2#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������3#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ����ͨ��6#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������9#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ����ͨ��8#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������7#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������4#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ����ͨ��5#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������6#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Back();													//��ͷ
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ����ͨ��5#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������4#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
	
	Turn_Right();													//��ת
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//����ǰ��������1#��
	{
		Audible_and_Visual_Alarm();         //���ⱨ��
		Turn_Right();                       //��ת
		Around_Block();											//���������飬���������Χ����������
		return;
	}
}
/********************************************************************************
    ���ܣ�	������飬���������Χ�ĸ���
    ������	��
    ���أ�	��
    ��ע��	�ӵ�һ�������˳ʱ�뵽��Ŀ�귽����Χ��������
*********************************************************************************/
void Around_Block(void)
{
		Move_NextPoint(Match_Velocity);	    //����5#��
		Audible_and_Visual_Alarm();         //���ⱨ��
		
		Turn_Right();                       //��ת
		Move_NextPoint(Match_Velocity);	    //����4#��
		Audible_and_Visual_Alarm();         //���ⱨ��
		
		Turn_Right();                       //��ת
		Move_NextPoint(Match_Velocity);	    //����1#��
		Audible_and_Visual_Alarm();         //���ⱨ��
}
