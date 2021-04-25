//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "control.h"

FlagStatus  CAR_Run_Flag=RESET;							            //�����˶�ʹ�ܱ�־λ
FlagStatus  Divide_Ctrl_Flag=RESET;                     //���ҵ���ֿ����Ʊ�־λ
FlagStatus  Yaw_PID_Flag=RESET;						              //ƫ���ǻ�PID������ʹ�ܱ�־λ
FlagStatus  CCD_PID_Flag=RESET;                         //CCD��PID������ʹ�ܱ�־λ
FlagStatus  Yaw_Reset_Flag=RESET;						            //Yaw����ʹ�ܱ�־λ
FlagStatus  Yaw_Arrive_Flag=SET;						            //ƫ���ǻ�PIDλ�õ����־λ
FlagStatus  CCD_Arrive_Flag=SET;						            //CCD��PIDλ�õ����־λ
FlagStatus  Gray_Line_Flag=RESET;						            //�ҶȺ���ʶ���־λ
FlagStatus  IR_Use_Flag=RESET;						              //����ʹ�ñ�־λ
FlagStatus  OpenMV_Use_Flag=RESET;						          //OpenMVʹ�ñ�־λ
FlagStatus  OpenMV_Find_Flag=RESET;						          //OpenMV����ʶ���־λ
FlagStatus  IR_Find_Flag=RESET;						              //��������ʶ���־λ
u16   			Delay_n5ms_CNT=0;							              //5ms��ʱʹ�ܼ���
int  			  CAR_Velocity=0,CAR_Yaw=0;				            //����Ŀ���ٶȺ�ƫ����
int  			  MOTOR_L_Velocity=0,MOTOR_R_Velocity=0;			//����Ŀ���ٶȺ�ƫ����
float       yaw_correct=0;                              //ƫ���������ֱ���
float 			Velocity_KP_L=50,Velocity_KI_L=10;          //�ٶȻ�����PIֵ
float 			Velocity_KP_R=50,Velocity_KI_R=10;          //�ٶȻ��ҵ��PIֵ
float 			Angle_KP_Yaw=110,
						Angle_KI_Yaw=0,
						Angle_KD_Yaw=40;												    //ƫ���ǻ�PIDֵ
float 			Angle_KP_CCD=150,
						Angle_KI_CCD=7,
						Angle_KD_CCD=40;											  	  //CCD��PIDֵ
int   			TargetVelocity_L=0,TargetVelocity_R=0;      //���Ŀ���ٶ�
int   			TargetVelocity_A=0;                         //���Ŀ����ٶ�
int   			Velocity_L=0,Velocity_R=0;                  //�����ǰ�ٶ�
int   			PWM_L=0,PWM_R=0;                            //���PWMֵ
int         GraySensor=0,GraySensor2=0,
						GraySensor_Threshold=4000;     							//�Ҷȴ�������������ֵ
int         IRSensor=0,
						IRSensor_Threshold=550;     								//���⴫������������ֵ
/********************************************************************************
    ���ܣ�	MPU6050INT�жϷ�����
    ������	��
    ���أ�	��
    ��ע��	�������п����㷨
*********************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	static FlagStatus WIRELESS_FLAG = RESET;
	static u8 IR_FIND_CNT = 0,OpenMV_FIND_CNT = 0;
	
/*====================����жϱ�־λ====================*/
  EXTI->PR = 1<<15;
/*====================������ʱ��־λ====================*/
  if(Delay_n5ms_CNT > 0)
      Delay_n5ms_CNT--;
/*===================��ȡң��ɲ��ָ��===================*/
	if(WIRELESS_A == 1)																		//�������ɲ��������
	{
		FlagStatus_Reversal(&WIRELESS_FLAG);								//��תɲ����־λ
		
		if(WIRELESS_FLAG == SET)
			LED_WAR = LED_ON;													  			//LED��ʾ�Ƴ�����ʾ
		else
			LED_WAR = LED_OFF;													  		//�ر�LED��ʾ����ʾ
	}	
/*==================��ȡ�Ҷȴ�������ֵ==================*/
  GraySensor = Get_Adc(ADC_Channel_8);                  //��ȡ�Ҷ�ֵ
  GraySensor2 = Get_Adc(ADC_Channel_14);                //��ȡ�Ҷ�ֵ2
	if(GraySensor <= GraySensor_Threshold||GraySensor2 <= GraySensor_Threshold)                
																												//�����һ���ҶȵĶ���С����ֵ
		Gray_Line_Flag = SET;              								  //���ֺڵ�
	else
		Gray_Line_Flag = RESET;
/*==================��ȡ���⴫������ֵ==================*/
	IRSensor = Get_Adc(ADC_Channel_9);                  	//��ȡ����ֵ
	if(IR_Use_Flag == SET)																//���ʹ���˺���
	{
		if(IRSensor >= IRSensor_Threshold)                  //�������������ֵ
			IR_FIND_CNT++;														  			//��־λ�Լ�
		else
			IR_FIND_CNT=0;
		if(IR_FIND_CNT>=5)
		{
			IR_Find_Flag = SET;              				  		    //��������
			BUZZER = BUZZER_ON;																//��������ʾ
		}
		else
		{
			IR_Find_Flag = RESET;
			BUZZER = BUZZER_OFF;
		}
	}
/*=================��ȡOpenMVͨ�����ŵ�ƽ===============*/
	if(OpenMV_Use_Flag == SET)                            //���������OpenMVʹ�ñ�־λ
	{
		OpenMV_CMD = OpenMV_ENABLE;                         //ʹ��OpenMV
		
		if(OpenMV_RES)                                      //���OpenMV����Ŀ��
		{
			//BUZZER = BUZZER_ON;																//��������ʾ
			OpenMV_FIND_CNT++;                                //���������Լ�
		}
		else
		{
			//BUZZER = BUZZER_OFF;
		}
		
		if(OpenMV_RES >= 3)                                 //�������ֵ�����趨ֵ
			OpenMV_Find_Flag = SET;                           //ʶ�����壬����Ŀ�귢�ֱ�־λ
	}
	else
	{
		OpenMV_CMD       = OpenMV_DISABLE;
		OpenMV_FIND_CNT  = 0;
		OpenMV_Find_Flag = RESET;
	}
/*==================��ȡMPU6050ƫ������ֵ===============*/
  if(Yaw_Reset_Flag == SET)                             //���ƫ�������㱻ʹ��
  {
    Yaw_Reset_Flag = RESET;						                  //��־λ����
    yaw_correct += Yaw;							                    //ƫ����������
  }
	
  Read_DMP();                                           //MPU6050DMP����
  Branch_Out_Yaw();											                //��Yaw��+-180������ʵ����float����Χ�ڣ�
  Yaw -= yaw_correct;                                   //ƫ����������
/*======================��ȡ��������ֵ==================*/
  Velocity_L = Read_Encoder(ENCODER_L);                 //������������ֵ
  Velocity_R = Read_Encoder(ENCODER_R);                 //���ҵ��������ֵ
/*======================����PID�˶�����=================*/
  if(CAR_Run_Flag == RESET||WIRELESS_FLAG == SET)				//��������˶���־λ�رջ�ɲ����ʹ�ܣ�ֹͣ�˶����ƣ�ɲ��
	{
    MOTOR_Release();                                    //�ͷŵ��
		LED_MCU_Flash(100);                                 //LED��˸��ʾ�ж�ִ����ϣ�������������
		return;
	}
	
	if(Yaw_PID_Flag == SET)										            //���ƫ���ǻ�PID������ʹ��
	{
		TargetVelocity_A = Angle_PID_Yaw(Yaw,CAR_Yaw,&Yaw_Arrive_Flag);
																										  	//ƫ���ǻ�PID����������Ŀ����ٶ�
		Amplitude_Limiting(&TargetVelocity_A,1000);          //���ٶ��޷�
	}
	else if(CCD_PID_Flag == SET)										      //���CCD��PID������ʹ��
	{
		TargetVelocity_A = Angle_PID_CCD(CCD_LineCenter<-62?0:CCD_LineCenter,0,&CCD_Arrive_Flag);
																										  	//CCD��PID����������Ŀ����ٶ�
		Amplitude_Limiting(&TargetVelocity_A,500);          //���ٶ��޷�
	}
	else
	{
		TargetVelocity_A = 0;        											  //���ٶ�����
	}
	
  if(Divide_Ctrl_Flag == RESET)                         //���û��ʹ�����ҵ���ֿ����ƣ����ҵ���ٶȶ�Ϊ����Ŀ���ٶ�
  {
    MOTOR_L_Velocity=CAR_Velocity;
    MOTOR_R_Velocity=CAR_Velocity;
  }

	TargetVelocity_L = MOTOR_L_Velocity-TargetVelocity_A; //�����ٶȷֽ⵽��ಢ�������ٶ�
	TargetVelocity_R = MOTOR_R_Velocity+TargetVelocity_A;	//�����ٶȷֽ⵽�Ҳಢ�������ٶ�

	PWM_L = Velocity_PI_L(Velocity_L,TargetVelocity_L);   //�ٶ�PI��������������PWM���
	Amplitude_Limiting(&PWM_L,7000);                      //PWM�޷�

	PWM_R = Velocity_PI_R(Velocity_R,TargetVelocity_R);   //�ٶ�PI�����������ҵ��PWM���
	Amplitude_Limiting(&PWM_R,7000);                      //PWM�޷�

	Set_PWM(PWM_L,PWM_R);                                 //��PWMֵ�������
/*====================�жϺ�����ȷ����ָʾ==============*/
  LED_MCU_Flash(100);                                   //LED��˸��ʾ�ж�ִ����ϣ�������������
}
/********************************************************************************
    ���ܣ�	TIM6�жϷ�����
    ������	��
    ���أ�	��
    ��ע��	�������п����㷨
*********************************************************************************/
void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)     //���TIM6�����жϷ������
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);         //���TIMx�����жϱ�־
		
		CCD_Find_Line(CCD);										    				  //��ȡ����ͷ����
	}
}
/********************************************************************************
    ���ܣ�	����Yaw��Χ
    ������	��
    ���أ�	������Yawֵ
    ��ע��	����Yaw����ͻ����ص㣬��Yaw������ʵ����
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
    ���ܣ�	�޷�
    ������
            Variable    ��Ҫ�޷��ı���
            Range	      ���Ʒ���
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Amplitude_Limiting(int* Variable,int Range)
{
    if(*Variable >  Range)*Variable =  Range;
    if(*Variable < -Range)*Variable = -Range;
}
/********************************************************************************
    ���ܣ�	����ʽ�ٶ�PI������
    ������
            Now 	  ��ǰ�ٶ�
            Target	Ŀ���ٶ�
    ���أ�	PWM���ֵ
    ��ע��	��������ʽPI�������ϴ�����Ա��������Ӱ�죬���޷�Ӧ�ڿ������ڲ�
*********************************************************************************/
int Velocity_PI_L(int Now,int Target)
{
    static int Bias=0,Last_bias=0,PWM=0;
    Bias = Target-Now;                			    		            //���㱾��ƫ��
    PWM += Velocity_KP_L*(Bias-Last_bias)+Velocity_KI_L*Bias;   //����ʽPI������
    Last_bias = Bias;	                   				          	    //������һ��ƫ��

    Amplitude_Limiting(&PWM,7000);                              //PWM�޷�
    return PWM;                        					                //���PWM������
}
int Velocity_PI_R(int Now,int Target)
{
    static int Bias=0,Last_bias=0,PWM=0;
    Bias = Target-Now;                  					              //���㱾��ƫ��
    PWM += Velocity_KP_R*(Bias-Last_bias)+Velocity_KI_R*Bias;   //����ʽPI������
    Last_bias = Bias;	                   					              //������һ��ƫ��

    Amplitude_Limiting(&PWM,7000);                              //PWM�޷�
    return PWM;                        					                //���PWM������
}
/********************************************************************************
    ���ܣ�	λ��ʽ�Ƕ�PID������
    ������
            Now 	  ��ǰ�Ƕ�
            Target	Ŀ��Ƕ�
						Arrive_Flag    ����Ŀ��Ƕȱ�־λ��ַ
    ���أ�	�������ٶȱ仯ֵ
    ��ע��	����λ��ʽPID�������ϴ�����Ա��������Ӱ�죬
           �ʽ��޷������ⲿ���Ӷ������༶����ʱ�����ٶȡ�
					����Ŀ��λ�ú󣬽�Arrive_Flag��ΪSET
*********************************************************************************/
int Angle_PID_Yaw(float Now,float Target,FlagStatus* Arrive_Flag)
{
    static float Bias,Last_Bias,Integral_bias,velocity;
		static float Integral_bias_Range=500;
    Bias = Target-Now;                                          //���㱾��ƫ��
    if(Angle_KI_Yaw>0.0)                                        //���ʹ����KI
    {
      Integral_bias+=Bias;	                                    //���ƫ��Ļ���
			
      if(Integral_bias >  Integral_bias_Range)                  //�����޷�
				Integral_bias = Integral_bias_Range;
			if(Integral_bias < -Integral_bias_Range)
				Integral_bias = Integral_bias_Range;
    }
    velocity = Angle_KP_Yaw/10*Bias
             + Angle_KI_Yaw/10000*Integral_bias
             + Angle_KD_Yaw*(Bias-Last_Bias);                   //λ��ʽPID������
    Last_Bias = Bias;                                           //������һ��ƫ��
		if(__abs(Bias) <= 0.01 && __abs(Last_Bias) <= 0.01 && __abs(velocity)<10)                 			//�������Ŀ��λ��
			*Arrive_Flag = SET;																				//������FLAG��ΪSET
    return velocity;                                            //����ٶȿ�����
}
int Angle_PID_CCD(int Now,int Target,FlagStatus* Arrive_Flag)
{
    static float Bias,Last_Bias,Integral_bias,velocity;
		static float Integral_bias_Range=500;
    Bias = Target-Now;                                          //���㱾��ƫ��
    if(Angle_KI_CCD>0.0)                                        //���ʹ����KI
    {
      Integral_bias+=Bias;	                                    //���ƫ��Ļ���
			
      if(Integral_bias >  Integral_bias_Range)                  //�����޷�
				Integral_bias = Integral_bias_Range;
			if(Integral_bias < -Integral_bias_Range)
				Integral_bias = Integral_bias_Range;
    }
    velocity = Angle_KP_CCD/100*Bias
             + Angle_KI_CCD/10000*Integral_bias
             + Angle_KD_CCD*(Last_Bias-Bias);                   //λ��ʽPID������
    Last_Bias = Bias;                                           //������һ��ƫ��
		if(Bias == 0 && Last_Bias == 0)                             //�������Ŀ��λ��
			*Arrive_Flag = SET;																				//������FLAG��ΪSET
    return velocity;                                            //����ٶȿ�����
} 
/********************************************************************************
    ���ܣ�	ȡ����ֵ
    ������	number ȡ����ֵ����
    ���أ�	����ֵ
    ��ע��	��
*********************************************************************************/
int __abs(int number)
{
    return number>0?number:-number;
}
/********************************************************************************
    ���ܣ�	��PWMֵ�����Ĵ���
    ������
            motor_l	����PWMֵ
            motor_r	�ҵ��PWMֵ
    ���أ�	��
    ��ע��	��
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
    ���ܣ�	ƫ��������
    ������	��
    ���أ�	��
    ��ע��	����־λ��1�����ж��д�����Ӧ����
*********************************************************************************/
void Yaw_Reset(void)
{
    Yaw_Reset_Flag = SET;
}
/********************************************************************************
    ���ܣ�	��ʱ����5ms
    ������	n5ms ��ʱ��5���뱶��
    ���أ�	��
    ��ע��	���ñ�־λ�������ж���ʱ
*********************************************************************************/
void Delay_n5ms(u16 n5ms)
{
    Delay_n5ms_CNT = n5ms;
        while(Delay_n5ms_CNT);
}
/********************************************************************************
    ���ܣ�	����ʱ
    ������	time ��ʱ����
    ���أ�	��
    ��ע��	���ñ�־λ�������ж���ʱ
*********************************************************************************/
void Delay_sec(u8 sec)
{
    while(sec--)
        Delay_n5ms(200);
}
//////////////////////////////////////////////////////////////////////////////////
