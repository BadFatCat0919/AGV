//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "action.h"

/********************************************************************************
    功能：	声光报警
    参数：  无
    返回：	无
    备注：	使用时会导致程序延时150ms
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
    功能：	刹车
    参数：  无
    返回：	无
    备注：	利用速度PI控制器将速度置零，然后释放电机
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
    功能：	车辆直线运动，开环
    参数：  velocity    车辆速度
    返回：	无
    备注：	如果速度为0，刹车
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
    功能：	左右电机分开控制
    参数：  
            velocity_left    左电机速度
            velocity_left    右电机速度
    返回：	无
    备注：	如果速度为0，刹车
*********************************************************************************/
void CAR_Divide_Ctrl(int velocity_left,int velocity_right)
{
    Divide_Ctrl_Flag = SET;

    MOTOR_L_Velocity = velocity_left;
    MOTOR_R_Velocity = velocity_right;
}
/********************************************************************************
    功能：	车辆转向，开环
    参数：  velocity    转向速度
    返回：	无
    备注：	如果速度为0，刹车
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
    功能：	车辆直线运动，利用偏航角环闭环
    参数：  velocity    车辆速度
    返回：	无
    备注：	如果速度为0，刹车
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
    功能：	车辆直线运动，利用CCD环闭环
    参数：  velocity    车辆速度
    返回：	无
    备注：	如果速度为0，刹车
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
    功能：	车辆转向
    参数：  yaw    	车辆目标偏航角
    返回：	无
    备注：	转向直到角度抵达
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
    功能： 前进，停在下一个节点
    参数： velocity    车辆速度
    返回： 无
    备注： 无
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
    功能： 前进,经过下一个节点
    参数： velocity    车辆速度
    返回： 无
    备注： 无
*********************************************************************************/
void Move_NextPoint_Pass(int velocity)
{
		CAR_Move_CCDCorrect(velocity);
		CCD_JudgePoint = 0;
		while(!CCD_JudgePoint);
    while(Gray_Line_Flag == RESET);
}
/********************************************************************************
    功能： 前进，在下一个节点或红外搜寻到物体时停下
    参数：
					 search_velocity    搜寻时的车辆速度
					 find_velocity      发现目标后车辆速度
    返回： 是否搜寻到
    备注： 无
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
    功能： 前进,在红外搜寻到物体时停下,否则通过下一点
    参数：
					 search_velocity    搜寻时的车辆速度
					 find_velocity      发现目标后车辆速度
    返回： 是否搜寻到
    备注： 无
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
    功能： 前进，在下一个节点或OpenMV搜寻到物体时停下
    参数：
					 search_velocity    搜寻时的车辆速度
					 find_velocity      发现目标后车辆速度
    返回： 是否搜寻到
    备注： 无
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
    功能： 前进,在OpenMV搜寻到物体时停下,否则通过下一点
    参数：
					 search_velocity    搜寻时的车辆速度
					 find_velocity      发现目标后车辆速度
    返回： 是否搜寻到
    备注： 无
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
    功能： 旋转搜索
    参数：
					 velocity    搜寻速度
    返回： 是否搜寻到
    备注： 搜索90°，若搜索到目标则快速回到初始角度
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
    功能： 左转
    参数： 无
    返回： 无
    备注： 线上左转
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
    功能： 右转
    参数： 无
    返回： 无
    备注： 线上右转
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
    功能： 调头
    参数： 无
    返回： 无
    备注： 无
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
    功能： 进入坐标系
    参数： velocity    车辆速度
    返回： 无
    备注： 无
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
    功能： 等待手势指令
    参数： 无
    返回： 无
    备注： 无
*********************************************************************************/
void Wait_StartCMD(void)
{
	IR_Use_Flag = SET;
	while(IR_Find_Flag == SET);
	while(IR_Find_Flag == RESET);
	while(IR_Find_Flag == SET);
	IR_Use_Flag = RESET;
}
