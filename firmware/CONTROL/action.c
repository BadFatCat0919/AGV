//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "action.h"

/********************************************************************************
    ���ܣ�	���ⱨ��
    ������  ��
    ���أ�	��
    ��ע��	ʹ��ʱ�ᵼ�³�����ʱ150ms
*********************************************************************************/
void Audible_and_Visual_Alarm(void)
{
    LED_WAR = LED_ON;
    BUZZER  = BUZZER_ON;

    Delay_n5ms(10);

    LED_WAR = LED_OFF;
    BUZZER  = BUZZER_OFF;
	
    Delay_n5ms(5);
	
    LED_WAR = LED_ON;
    BUZZER  = BUZZER_ON;

    Delay_n5ms(15);

    LED_WAR = LED_OFF;
    BUZZER  = BUZZER_OFF;
}
/********************************************************************************
    ���ܣ�	ɲ��
    ������  ��
    ���أ�	��
    ��ע��	�����ٶ�PI���������ٶ����㣬Ȼ���ͷŵ��
*********************************************************************************/
void CAR_Breaking(void)
{
    CAR_Velocity = 0;
    Yaw_PID_Flag = RESET;
    CCD_PID_Flag = RESET;
    CAR_Run_Flag = SET;
    while( Velocity_L || Velocity_R );

    CAR_Run_Flag = RESET;
    MOTOR_Release();
}
/********************************************************************************
    ���ܣ�	����ֱ���˶�������
    ������  velocity    �����ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
*********************************************************************************/
void CAR_Move(int velocity)
{
    if(velocity == 0) {CAR_Breaking();return;}

    CAR_Velocity = velocity;
    Yaw_PID_Flag = RESET;
    CCD_PID_Flag = RESET;
    CAR_Run_Flag = SET;
    Divide_Ctrl_Flag = RESET;
}
/********************************************************************************
    ���ܣ�	���ҵ���ֿ�����
    ������  
            velocity_left    �����ٶ�
            velocity_left    �ҵ���ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
*********************************************************************************/
void CAR_Divide_Ctrl(int velocity_left,int velocity_right)
{
    Divide_Ctrl_Flag = SET;

    MOTOR_L_Velocity = velocity_left;
    MOTOR_R_Velocity = velocity_right;
}
/********************************************************************************
    ���ܣ�	����ת�򣬿���
    ������  velocity    ת���ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
*********************************************************************************/
void CAR_Turn_OpenLoop(int velocity)
{
    CAR_Run_Flag = SET;
    Yaw_PID_Flag = RESET;
    CCD_PID_Flag = RESET;
		CAR_Velocity = 0;
    CAR_Divide_Ctrl(-velocity,velocity);
}
/********************************************************************************
    ���ܣ�	����ֱ���˶�������ƫ���ǻ��ջ�
    ������  velocity    �����ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
*********************************************************************************/
void CAR_Move_YawCorrect(int velocity)
{
    if(velocity == 0) {CAR_Breaking();return;}

		Yaw_Reset_Flag = SET;
    CAR_Yaw        = 0;
    CAR_Velocity   = velocity;
    Yaw_PID_Flag   = SET;
    CCD_PID_Flag   = RESET;
    CAR_Run_Flag   = SET;
    Divide_Ctrl_Flag = RESET;
}
/********************************************************************************
    ���ܣ�	����ֱ���˶�������CCD���ջ�
    ������  velocity    �����ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
*********************************************************************************/
void CAR_Move_CCDCorrect(int velocity)
{
    if(velocity == 0) {CAR_Breaking();return;}

    CAR_Velocity = velocity;
    Yaw_PID_Flag = RESET;
    CCD_PID_Flag = SET;
    CAR_Run_Flag = SET;
    Divide_Ctrl_Flag = RESET;
}
/********************************************************************************
    ���ܣ�	����ת��
    ������  yaw    	����Ŀ��ƫ����
    ���أ�	��
    ��ע��	ת��ֱ���Ƕȵִ�
*********************************************************************************/
void CAR_Turn(int yaw)
{
    CAR_Velocity    = 0;
    Yaw_Reset_Flag  = SET;
    CAR_Yaw         = yaw;
    Yaw_PID_Flag    = SET;
    CCD_PID_Flag    = RESET;
    CAR_Run_Flag    = SET;
    Yaw_Arrive_Flag = RESET;
    Divide_Ctrl_Flag = RESET;
	
    while(Yaw_Arrive_Flag == RESET);
    
    Yaw_PID_Flag    = RESET;
    CCD_PID_Flag    = RESET;
    CAR_Run_Flag    = RESET;
    MOTOR_Release();
}
/********************************************************************************
    ���ܣ� ǰ����ͣ����һ���ڵ�
    ������ velocity    �����ٶ�
    ���أ� ��
    ��ע�� ��
*********************************************************************************/
void Move_NextPoint(int velocity)
{
		CCD_JudgePoint = 0;
		CAR_Move_CCDCorrect(velocity);
		while(!CCD_JudgePoint);
    CAR_Velocity = 80;
    while(Gray_Line_Flag == RESET);
		CAR_Breaking();
}
/********************************************************************************
    ���ܣ� ǰ��,������һ���ڵ�
    ������ velocity    �����ٶ�
    ���أ� ��
    ��ע�� ��
*********************************************************************************/
void Move_NextPoint_Pass(int velocity)
{
		CAR_Move_CCDCorrect(velocity);
		CCD_JudgePoint = 0;
		while(!CCD_JudgePoint);
    while(Gray_Line_Flag == RESET);
}
/********************************************************************************
    ���ܣ� ǰ��������һ���ڵ�������Ѱ������ʱͣ��
    ������
					 search_velocity    ��Ѱʱ�ĳ����ٶ�
					 find_velocity      ����Ŀ������ٶ�
    ���أ� �Ƿ���Ѱ��
    ��ע�� ��
*********************************************************************************/
FlagStatus Move_NextPoint_IRSearch(int search_velocity,int find_velocity)
{
		FlagStatus Find_Flag = RESET;
		CCD_JudgePoint = 0;
	  IR_Use_Flag = SET;
		CAR_Move_CCDCorrect(search_velocity);
		
		while(!CCD_JudgePoint)
			if(IR_Find_Flag == SET)
			{
				CAR_Velocity = find_velocity;
				Find_Flag = SET;
			}
    CAR_Velocity = 80;
    while(Gray_Line_Flag == RESET);
		CAR_Breaking();
		IR_Use_Flag = RESET;
		return Find_Flag;
}
/********************************************************************************
    ���ܣ� ǰ��,�ں�����Ѱ������ʱͣ��,����ͨ����һ��
    ������
					 search_velocity    ��Ѱʱ�ĳ����ٶ�
					 find_velocity      ����Ŀ������ٶ�
    ���أ� �Ƿ���Ѱ��
    ��ע�� ��
*********************************************************************************/
FlagStatus Move_NextPoint_Pass_IRSearch(int search_velocity,int find_velocity)
{
		FlagStatus Find_Flag = RESET;
		CCD_JudgePoint = 0;
	  IR_Use_Flag = SET;
		CAR_Move_CCDCorrect(search_velocity);
	
		while(!CCD_JudgePoint)
			if(IR_Find_Flag == SET)
			{
				CAR_Velocity = find_velocity;
				Find_Flag = SET;
			}
			
		if(Find_Flag == SET)
		{
			CAR_Velocity = 80;
			while(Gray_Line_Flag == RESET);
			CAR_Breaking();
		  IR_Use_Flag = RESET;
			return Find_Flag;
		}
		
    while(Gray_Line_Flag == RESET);
		IR_Use_Flag = RESET;
		return Find_Flag;
}
/********************************************************************************
    ���ܣ� ǰ��������һ���ڵ��OpenMV��Ѱ������ʱͣ��
    ������
					 search_velocity    ��Ѱʱ�ĳ����ٶ�
					 find_velocity      ����Ŀ������ٶ�
    ���أ� �Ƿ���Ѱ��
    ��ע�� ��
*********************************************************************************/
FlagStatus Move_NextPoint_OpenMVSearch(int search_velocity,int find_velocity)
{
		FlagStatus Find_Flag = RESET;
    OpenMV_Use_Flag = SET;
		CAR_Move_CCDCorrect(search_velocity);
		
		while(!CCD_JudgePoint)
			if(OpenMV_Find_Flag == SET)
			{
				CAR_Velocity = find_velocity;
				Find_Flag = SET;
			}
    CAR_Velocity = 80;
    while(Gray_Line_Flag == RESET);
		CAR_Breaking();
    OpenMV_Use_Flag = RESET;
		return Find_Flag;
}
/********************************************************************************
    ���ܣ� ǰ��,��OpenMV��Ѱ������ʱͣ��,����ͨ����һ��
    ������
					 search_velocity    ��Ѱʱ�ĳ����ٶ�
					 find_velocity      ����Ŀ������ٶ�
    ���أ� �Ƿ���Ѱ��
    ��ע�� ��
*********************************************************************************/
FlagStatus Move_NextPoint_Pass_OpenMVSearch(int search_velocity,int find_velocity)
{
		FlagStatus Find_Flag = RESET;
    OpenMV_Use_Flag = SET;
		CAR_Move_CCDCorrect(search_velocity);
	
		while(!CCD_JudgePoint)
			if(OpenMV_Find_Flag == SET)
			{
				CAR_Velocity = find_velocity;
				Find_Flag = SET;
			}
			
		if(Find_Flag == SET)
		{
			CAR_Velocity = 80;
			while(Gray_Line_Flag == RESET);
			CAR_Breaking();
      OpenMV_Use_Flag = RESET;
			return Find_Flag;
		}
		
    while(Gray_Line_Flag == RESET);
    OpenMV_Use_Flag = RESET;
		return Find_Flag;
}
/********************************************************************************
    ���ܣ� ��ת����
    ������
					 velocity    ��Ѱ�ٶ�
    ���أ� �Ƿ���Ѱ��
    ��ע�� ����90�㣬��������Ŀ������ٻص���ʼ�Ƕ�
*********************************************************************************/
FlagStatus Rotate_Search(int velocity)
{
		FlagStatus Find_Flag = RESET;
		IR_Use_Flag     = SET;
    Yaw_Reset_Flag  = SET;
	
		while(Yaw>10);
	
		CAR_Turn_OpenLoop(velocity);
	
		while(Yaw <= 90)
			if(IR_Find_Flag == SET)
			{
				CAR_Yaw      = 0;
				Find_Flag    = SET;
				break;
			}
			else
				CAR_Yaw      = 90;
				
		CAR_Velocity     = 0;
		Yaw_Arrive_Flag  = RESET;
		Yaw_PID_Flag     = SET;
		Divide_Ctrl_Flag = RESET;

		while(Yaw_Arrive_Flag == RESET);
		
		Yaw_PID_Flag    = RESET;
		IR_Use_Flag     = RESET;
			
		return Find_Flag;
}
/********************************************************************************
    ���ܣ� ��ת
    ������ ��
    ���أ� ��
    ��ע�� ������ת
*********************************************************************************/
void Turn_Left(void)
{
		CAR_Turn(90);
    Divide_Ctrl_Flag=RESET;
		CAR_Run_Flag=SET;
		Yaw_PID_Flag=RESET;
		CAR_Run_Flag=RESET;
		MOTOR_Release();
}
/********************************************************************************
    ���ܣ� ��ת
    ������ ��
    ���أ� ��
    ��ע�� ������ת
*********************************************************************************/
void Turn_Right(void)
{
		CAR_Turn(-90);
    Divide_Ctrl_Flag=RESET;
		CAR_Run_Flag=SET;
		Yaw_PID_Flag=RESET;
		CAR_Run_Flag=RESET;
		MOTOR_Release();
}
/********************************************************************************
    ���ܣ� ��ͷ
    ������ ��
    ���أ� ��
    ��ע�� ��
*********************************************************************************/
void Turn_Back(void)
{
		CAR_Turn(180);
    Divide_Ctrl_Flag=RESET;
		CAR_Run_Flag=SET;
		Yaw_PID_Flag=RESET;
		CCD_PID_Flag=SET;
		CCD_Arrive_Flag=RESET;
		while(CCD_Arrive_Flag==RESET);
		CAR_Run_Flag=RESET;
		CCD_PID_Flag=RESET;
		MOTOR_Release();
}
/********************************************************************************
    ���ܣ� ��������ϵ
    ������ velocity    �����ٶ�
    ���أ� ��
    ��ע�� ��
*********************************************************************************/
void Enter_CoordinateSystem(void)
{
  CAR_Turn(-37);
	
	CAR_Move_YawCorrect(500);
	Delay_n5ms(240);
	CAR_Move_YawCorrect(100);
	while(Gray_Line_Flag == RESET);
	
  CAR_Turn(37);
	
	CAR_Run_Flag=RESET;
	Yaw_PID_Flag=RESET;
	MOTOR_Release();
}
/********************************************************************************
    ���ܣ� �ȴ�����ָ��
    ������ ��
    ���أ� ��
    ��ע�� ��
*********************************************************************************/
void Wait_StartCMD(void)
{
	IR_Use_Flag = SET;
	while(IR_Find_Flag == SET);
	while(IR_Find_Flag == RESET);
	while(IR_Find_Flag == SET);
	IR_Use_Flag = RESET;
}
