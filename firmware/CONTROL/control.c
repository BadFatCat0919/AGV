//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "control.h"

FlagStatus  CAR_Run_Flag=RESET;							            //车辆运动使能标志位
FlagStatus  Divide_Ctrl_Flag=RESET;                     //左右电机分开控制标志位
FlagStatus  Yaw_PID_Flag=RESET;						              //偏航角环PID控制器使能标志位
FlagStatus  CCD_PID_Flag=RESET;                         //CCD环PID控制器使能标志位
FlagStatus  Yaw_Reset_Flag=RESET;						            //Yaw清零使能标志位
FlagStatus  Yaw_Arrive_Flag=SET;						            //偏航角环PID位置到达标志位
FlagStatus  CCD_Arrive_Flag=SET;						            //CCD环PID位置到达标志位
FlagStatus  Gray_Line_Flag=RESET;						            //灰度黑线识别标志位
FlagStatus  IR_Use_Flag=RESET;						              //红外使用标志位
FlagStatus  OpenMV_Use_Flag=RESET;						          //OpenMV使用标志位
FlagStatus  OpenMV_Find_Flag=RESET;						          //OpenMV物体识别标志位
FlagStatus  IR_Find_Flag=RESET;						              //红外物体识别标志位
u16   			Delay_n5ms_CNT=0;							              //5ms延时使能计数
int  			  CAR_Velocity=0,CAR_Yaw=0;				            //车辆目标速度和偏航角
int  			  MOTOR_L_Velocity=0,MOTOR_R_Velocity=0;			//车辆目标速度和偏航角
float       yaw_correct=0;                              //偏航角误差积分变量
float 			Velocity_KP_L=50,Velocity_KI_L=10;          //速度环左电机PI值
float 			Velocity_KP_R=50,Velocity_KI_R=10;          //速度环右电机PI值
float 			Angle_KP_Yaw=110,
						Angle_KI_Yaw=0,
						Angle_KD_Yaw=40;												    //偏航角环PID值
float 			Angle_KP_CCD=150,
						Angle_KI_CCD=7,
						Angle_KD_CCD=40;											  	  //CCD环PID值
int   			TargetVelocity_L=0,TargetVelocity_R=0;      //电机目标速度
int   			TargetVelocity_A=0;                         //电机目标角速度
int   			Velocity_L=0,Velocity_R=0;                  //电机当前速度
int   			PWM_L=0,PWM_R=0;                            //电机PWM值
int         GraySensor=0,GraySensor2=0,
						GraySensor_Threshold=4000;     							//灰度传感器读数及阈值
int         IRSensor=0,
						IRSensor_Threshold=550;     								//红外传感器读数及阈值
/********************************************************************************
    功能：	MPU6050INT中断服务函数
    参数：	无
    返回：	无
    备注：	包含所有控制算法
*********************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	static FlagStatus WIRELESS_FLAG = RESET;
	static u8 IR_FIND_CNT = 0,OpenMV_FIND_CNT = 0;
	
/*====================清除中断标志位====================*/
  EXTI->PR = 1<<15;
/*====================处理延时标志位====================*/
  if(Delay_n5ms_CNT > 0)
      Delay_n5ms_CNT--;
/*===================获取遥控刹车指令===================*/
	if(WIRELESS_A == 1)																		//如果无线刹车键按下
	{
		FlagStatus_Reversal(&WIRELESS_FLAG);								//翻转刹车标志位
		
		if(WIRELESS_FLAG == SET)
			LED_WAR = LED_ON;													  			//LED警示灯常亮提示
		else
			LED_WAR = LED_OFF;													  		//关闭LED警示灯提示
	}	
/*==================读取灰度传感器数值==================*/
  GraySensor = Get_Adc(ADC_Channel_8);                  //读取灰度值
  GraySensor2 = Get_Adc(ADC_Channel_14);                //读取灰度值2
	if(GraySensor <= GraySensor_Threshold||GraySensor2 <= GraySensor_Threshold)                
																												//如果有一个灰度的读数小于阈值
		Gray_Line_Flag = SET;              								  //发现黑点
	else
		Gray_Line_Flag = RESET;
/*==================读取红外传感器数值==================*/
	IRSensor = Get_Adc(ADC_Channel_9);                  	//读取红外值
	if(IR_Use_Flag == SET)																//如果使用了红外
	{
		if(IRSensor >= IRSensor_Threshold)                  //如果读数大于阈值
			IR_FIND_CNT++;														  			//标志位自加
		else
			IR_FIND_CNT=0;
		if(IR_FIND_CNT>=5)
		{
			IR_Find_Flag = SET;              				  		    //发现物体
			BUZZER = BUZZER_ON;																//蜂鸣器提示
		}
		else
		{
			IR_Find_Flag = RESET;
			BUZZER = BUZZER_OFF;
		}
	}
/*=================读取OpenMV通信引脚电平===============*/
	if(OpenMV_Use_Flag == SET)                            //如果设置了OpenMV使用标志位
	{
		OpenMV_CMD = OpenMV_ENABLE;                         //使能OpenMV
		
		if(OpenMV_RES)                                      //如果OpenMV发现目标
		{
			//BUZZER = BUZZER_ON;																//蜂鸣器提示
			OpenMV_FIND_CNT++;                                //计数变量自加
		}
		else
		{
			//BUZZER = BUZZER_OFF;
		}
		
		if(OpenMV_RES >= 3)                                 //如果计数值超过设定值
			OpenMV_Find_Flag = SET;                           //识别到物体，设置目标发现标志位
	}
	else
	{
		OpenMV_CMD       = OpenMV_DISABLE;
		OpenMV_FIND_CNT  = 0;
		OpenMV_Find_Flag = RESET;
	}
/*==================读取MPU6050偏航角数值===============*/
  if(Yaw_Reset_Flag == SET)                             //如果偏航角清零被使能
  {
    Yaw_Reset_Flag = RESET;						                  //标志位清零
    yaw_correct += Yaw;							                    //偏航角误差积分
  }
	
  Read_DMP();                                           //MPU6050DMP读数
  Branch_Out_Yaw();											                //将Yaw由+-180扩充至实数域（float允许范围内）
  Yaw -= yaw_correct;                                   //偏航角误差抵消
/*======================读取编码器数值==================*/
  Velocity_L = Read_Encoder(ENCODER_L);                 //读左电机编码器值
  Velocity_R = Read_Encoder(ENCODER_R);                 //读右电机编码器值
/*======================串级PID运动控制=================*/
  if(CAR_Run_Flag == RESET||WIRELESS_FLAG == SET)				//如果车辆运动标志位关闭或刹车被使能，停止运动控制，刹车
	{
    MOTOR_Release();                                    //释放电机
		LED_MCU_Flash(100);                                 //LED闪烁提示中断执行完毕，程序运行正常
		return;
	}
	
	if(Yaw_PID_Flag == SET)										            //如果偏航角环PID控制器使能
	{
		TargetVelocity_A = Angle_PID_Yaw(Yaw,CAR_Yaw,&Yaw_Arrive_Flag);
																										  	//偏航角环PID控制器计算目标角速度
		Amplitude_Limiting(&TargetVelocity_A,1000);          //角速度限幅
	}
	else if(CCD_PID_Flag == SET)										      //如果CCD环PID控制器使能
	{
		TargetVelocity_A = Angle_PID_CCD(CCD_LineCenter<-62?0:CCD_LineCenter,0,&CCD_Arrive_Flag);
																										  	//CCD环PID控制器计算目标角速度
		Amplitude_Limiting(&TargetVelocity_A,500);          //角速度限幅
	}
	else
	{
		TargetVelocity_A = 0;        											  //角速度清零
	}
	
  if(Divide_Ctrl_Flag == RESET)                         //如果没有使能左右电机分开控制，左右电机速度都为车辆目标速度
  {
    MOTOR_L_Velocity=CAR_Velocity;
    MOTOR_R_Velocity=CAR_Velocity;
  }

	TargetVelocity_L = MOTOR_L_Velocity-TargetVelocity_A; //将角速度分解到左侧并叠加线速度
	TargetVelocity_R = MOTOR_R_Velocity+TargetVelocity_A;	//将角速度分解到右侧并叠加线速度

	PWM_L = Velocity_PI_L(Velocity_L,TargetVelocity_L);   //速度PI控制器计算左电机PWM输出
	Amplitude_Limiting(&PWM_L,7000);                      //PWM限幅

	PWM_R = Velocity_PI_R(Velocity_R,TargetVelocity_R);   //速度PI控制器计算右电机PWM输出
	Amplitude_Limiting(&PWM_R,7000);                      //PWM限幅

	Set_PWM(PWM_L,PWM_R);                                 //将PWM值赋给电机
/*====================中断函数正确结束指示==============*/
  LED_MCU_Flash(100);                                   //LED闪烁提示中断执行完毕，程序运行正常
}
/********************************************************************************
    功能：	TIM6中断服务函数
    参数：	无
    返回：	无
    备注：	包含所有控制算法
*********************************************************************************/
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)     //检查TIM6更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);         //清除TIMx更新中断标志
		
		CCD_Find_Line(CCD);										    				  //读取摄像头数据
	}
}
/********************************************************************************
    功能：	扩充Yaw范围
    参数：	无
    返回：	扩充后的Yaw值
    备注：	利用Yaw不会突变的特点，将Yaw扩充至实数域
*********************************************************************************/
void Branch_Out_Yaw(void)
{
    static float Last_Yaw=0;
	
    while(Yaw - Last_Yaw + 10 >  360.0)
      Yaw -= 360.0;
    while(Yaw - Last_Yaw - 10 < -360.0)
      Yaw += 360.0;
		
    Last_Yaw = Yaw;
}
/********************************************************************************
    功能：	限幅
    参数：
            Variable    需要限幅的变量
            Range	      限制幅度
    返回：	无
    备注：	无
*********************************************************************************/
void Amplitude_Limiting(int* Variable,int Range)
{
    if(*Variable >  Range)*Variable =  Range;
    if(*Variable < -Range)*Variable = -Range;
}
/********************************************************************************
    功能：	增量式速度PI控制器
    参数：
            Now 	  当前速度
            Target	目标速度
    返回：	PWM输出值
    备注：	由于增量式PI控制器上次输出对本次输出有影响，故限幅应在控制器内部
*********************************************************************************/
int Velocity_PI_L(int Now,int Target)
{
    static int Bias=0,Last_bias=0,PWM=0;
    Bias = Target-Now;                			    		            //计算本次偏差
    PWM += Velocity_KP_L*(Bias-Last_bias)+Velocity_KI_L*Bias;   //增量式PI控制器
    Last_bias = Bias;	                   				          	    //保存上一次偏差

    Amplitude_Limiting(&PWM,7000);                              //PWM限幅
    return PWM;                        					                //输出PWM控制量
}
int Velocity_PI_R(int Now,int Target)
{
    static int Bias=0,Last_bias=0,PWM=0;
    Bias = Target-Now;                  					              //计算本次偏差
    PWM += Velocity_KP_R*(Bias-Last_bias)+Velocity_KI_R*Bias;   //增量式PI控制器
    Last_bias = Bias;	                   					              //保存上一次偏差

    Amplitude_Limiting(&PWM,7000);                              //PWM限幅
    return PWM;                        					                //输出PWM控制量
}
/********************************************************************************
    功能：	位置式角度PID控制器
    参数：
            Now 	  当前角度
            Target	目标角度
						Arrive_Flag    到达目标角度标志位地址
    返回：	车辆角速度变化值
    备注：	由于位置式PID控制器上次输出对本次输出无影响，
           故将限幅置于外部，从而提升多级串联时运行速度。
					到达目标位置后，将Arrive_Flag置为SET
*********************************************************************************/
int Angle_PID_Yaw(float Now,float Target,FlagStatus* Arrive_Flag)
{
    static float Bias,Last_Bias,Integral_bias,velocity;
		static float Integral_bias_Range=500;
    Bias = Target-Now;                                          //计算本次偏差
    if(Angle_KI_Yaw>0.0)                                        //如果使用了KI
    {
      Integral_bias+=Bias;	                                    //求出偏差的积分
			
      if(Integral_bias >  Integral_bias_Range)                  //积分限幅
				Integral_bias = Integral_bias_Range;
			if(Integral_bias < -Integral_bias_Range)
				Integral_bias = Integral_bias_Range;
    }
    velocity = Angle_KP_Yaw/10*Bias
             + Angle_KI_Yaw/10000*Integral_bias
             + Angle_KD_Yaw*(Bias-Last_Bias);                   //位置式PID控制器
    Last_Bias = Bias;                                           //保存上一次偏差
		if(__abs(Bias) <= 0.01 && __abs(Last_Bias) <= 0.01 && __abs(velocity)<10)                 			//如果到达目标位置
			*Arrive_Flag = SET;																				//将到达FLAG置为SET
    return velocity;                                            //输出速度控制量
}
int Angle_PID_CCD(int Now,int Target,FlagStatus* Arrive_Flag)
{
    static float Bias,Last_Bias,Integral_bias,velocity;
		static float Integral_bias_Range=500;
    Bias = Target-Now;                                          //计算本次偏差
    if(Angle_KI_CCD>0.0)                                        //如果使用了KI
    {
      Integral_bias+=Bias;	                                    //求出偏差的积分
			
      if(Integral_bias >  Integral_bias_Range)                  //积分限幅
				Integral_bias = Integral_bias_Range;
			if(Integral_bias < -Integral_bias_Range)
				Integral_bias = Integral_bias_Range;
    }
    velocity = Angle_KP_CCD/100*Bias
             + Angle_KI_CCD/10000*Integral_bias
             + Angle_KD_CCD*(Last_Bias-Bias);                   //位置式PID控制器
    Last_Bias = Bias;                                           //保存上一次偏差
		if(Bias == 0 && Last_Bias == 0)                             //如果到达目标位置
			*Arrive_Flag = SET;																				//将到达FLAG置为SET
    return velocity;                                            //输出速度控制量
} 
/********************************************************************************
    功能：	取绝对值
    参数：	number 取绝对值的数
    返回：	绝对值
    备注：	无
*********************************************************************************/
int __abs(int number)
{
    return number>0?number:-number;
}
/********************************************************************************
    功能：	把PWM值赋给寄存器
    参数：
            motor_l	左电机PWM值
            motor_r	右电机PWM值
    返回：	无
    备注：	无
*********************************************************************************/
void Set_PWM(int motor_l,int motor_r)
{
    if(motor_l>0)
        MOTOR_LF =  motor_l, MOTOR_LB=0;
    else
        MOTOR_LB = -motor_l, MOTOR_LF=0;

    if(motor_r>0)
        MOTOR_RF =  motor_r, MOTOR_RB=0;
    else
        MOTOR_RB = -motor_r, MOTOR_RF=0;
}
/********************************************************************************
    功能：	偏航角清零
    参数：	无
    返回：	无
    备注：	将标志位置1，在中断中触发相应程序
*********************************************************************************/
void Yaw_Reset(void)
{
    Yaw_Reset_Flag = SET;
}
/********************************************************************************
    功能：	延时数个5ms
    参数：	n5ms 延时的5毫秒倍数
    返回：	无
    备注：	设置标志位，利用中断延时
*********************************************************************************/
void Delay_n5ms(u16 n5ms)
{
    Delay_n5ms_CNT = n5ms;
        while(Delay_n5ms_CNT);
}
/********************************************************************************
    功能：	秒延时
    参数：	time 延时秒数
    返回：	无
    备注：	设置标志位，利用中断延时
*********************************************************************************/
void Delay_sec(u8 sec)
{
    while(sec--)
        Delay_n5ms(200);
}
//////////////////////////////////////////////////////////////////////////////////
