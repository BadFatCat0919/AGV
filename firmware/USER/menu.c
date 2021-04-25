//////////////////////////////////////////////////////////////////////////////////
//2019���й��񺽴�ѧ������ƾ���E��
//////////////////////////////////////////////////////////////////////////////////
//���������Ӿ���
//��Ա����  ��  �ι���  ������
//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//////////////////////////////////////////////////////////////////////////////////
#include "menu.h"
#include "main.h"
#include "action.h"
#include "match.h"

extern MENU_PAGE *current_page;
MENU_PAGE Homepage;
MENU_PAGE	Debug,Match;
MENU_PAGE	TASK_1,TASK_2,TASK_3,TASK_4,TASK_5;
MENU_PAGE	Velocity_PI_SET,Angle_Debug,CCD_Debug,Gray_Debug,Action_Test,IR_Debug,OpenMV_Debug;
MENU_PAGE	CCD_PID_Static,CCD_PID_Dynamic,Angle_PID_Static,Angle_PID_Dynamic;
int  Test_Yaw=90;

extern int Task_I_SchemeB_Angle,Task_I_SchemeC_Angle;

void Test_Alarm(void);
void Test_Breaking(void);
void Test_Move(void);
void Test_Move_YawCorrect(void);
void Test_Move_CCDCorrect(void);
void Test_RATurn_L(void);
void Test_RATurn_R(void);
void Test_TurnBack(void);
void Test_NextPoint(void);
void Test_Enter_CoordinateSystem(void);
void Menu_SetWatch(void);
void Menu_ShowCCD(void);
/*###################################����ҳ��###################################*/
__M_PAGE(Homepage,"HOMEPAGE",PAGE_NULL,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_GotoPage(0,	&Match);
	SOLGUI_Widget_GotoPage(1,	&Debug);
});
/*##################################������ҳ��##################################*/
__M_PAGE(Match,"MATCH",&Homepage,
{
	SOLGUI_Cursor_Set(5);

	SOLGUI_Widget_GotoPage(0,	&TASK_1);
	SOLGUI_Widget_GotoPage(1,	&TASK_2);
	SOLGUI_Widget_GotoPage(2,	&TASK_3);
	SOLGUI_Widget_GotoPage(3,	&TASK_4);
	SOLGUI_Widget_GotoPage(4,	&TASK_5);
});
/*##################################������һ��##################################*/
__M_PAGE(TASK_1,"TASK 1",&Match,
{
	SOLGUI_Cursor(4,2,6);

	SOLGUI_Widget_Button(0,"TASK 1 SCHEME A",&Task_I_SchemeA);
	SOLGUI_Widget_Button(1,"TASK 1 SCHEME B",&Task_I_SchemeB);
	SOLGUI_Widget_Spin	(2,"SCHEME B ANGLE",INT32,3000,-3000,&Task_I_SchemeB_Angle);
	SOLGUI_Widget_Button(3,"TASK 1 SCHEME C",&Task_I_SchemeC);
	SOLGUI_Widget_Spin	(4,"SCHEME C ANGLE",INT32,3000,-3000,&Task_I_SchemeC_Angle);
	SOLGUI_Widget_Spin	(5,"VELOCITY",INT32,3000,0,&Match_Velocity);
	
	Menu_ShowCCD();
});
/*##################################���������##################################*/
__M_PAGE(TASK_2,"TASK 2",&Match,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_Button(0,"TASK 2 SCHEME A",&Task_II_SchemeA);
	SOLGUI_Widget_Spin	(1,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################����������##################################*/
__M_PAGE(TASK_3,"TASK 3",&Match,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_Button(0,"TASK 3 SCHEME A",&Task_III_SchemeA);
	SOLGUI_Widget_Spin	(1,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################�������ġ�##################################*/
__M_PAGE(TASK_4,"TASK 4",&Match,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Button(0,"TASK 4 SCHEME A",&Task_IV_SchemeA);
	SOLGUI_Widget_Button(1,"TASK 4 SCHEME B",&Task_IV_SchemeB);
	SOLGUI_Widget_Spin	(2,"IR THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_Spin	(3,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################�������塿##################################*/
__M_PAGE(TASK_5,"TASK 5",&Match,
{
	SOLGUI_Cursor_Set(3);

	SOLGUI_Widget_Button(0,"TASK 5 SCHEME A",&Task_V_SchemeA);
	SOLGUI_Widget_Spin	(1,"IR THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_Spin	(2,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################������ҳ��##################################*/
__M_PAGE(Debug,"DEBUG",&Homepage,
{
	SOLGUI_Cursor_Set(7);

	SOLGUI_Widget_GotoPage(0,	&CCD_Debug      );
	SOLGUI_Widget_GotoPage(1,	&IR_Debug       );
	SOLGUI_Widget_GotoPage(2,	&OpenMV_Debug   );
	SOLGUI_Widget_GotoPage(3,	&Gray_Debug     );
	SOLGUI_Widget_GotoPage(4,	&Action_Test    );
	SOLGUI_Widget_GotoPage(5,	&Angle_Debug    );
	SOLGUI_Widget_GotoPage(6,	&Velocity_PI_SET);
});
/*###############################���ٶ�PI����ҳ��###############################*/
__M_PAGE(Velocity_PI_SET,"VELOCITY",&Debug,
{
	SOLGUI_Cursor_Set(5);

	SOLGUI_Widget_Spin	(0,"VL-KP",FLT16	,5000	,0	,&Velocity_KP_L	  );
	SOLGUI_Widget_Spin	(1,"VL-KI",FLT16	,5000	,0	,&Velocity_KI_L	  );
	SOLGUI_Widget_Spin	(2,"VR-KP",FLT16	,5000	,0	,&Velocity_KP_R	  );
	SOLGUI_Widget_Spin	(3,"VR-KI",FLT16	,5000	,0	,&Velocity_KI_R	  );
	SOLGUI_Widget_Spin	(4,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*#################################���Ƕȵ���ҳ��###############################*/
__M_PAGE(Angle_Debug,"ANGLE",&Debug,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_GotoPage(0,	&Angle_PID_Static    );
	SOLGUI_Widget_GotoPage(1,	&Angle_PID_Dynamic   );
});
/*##############################���Ƕ�PID��̬����ҳ��###########################*/
__M_PAGE(Angle_PID_Static,"YAW PID STATIC",&Angle_Debug,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Spin	(0,"ANGLE",INT32,360,-360,&Test_Yaw           );
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_Yaw	     );
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_Yaw	     );
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_Yaw	     );
});
/*##############################���Ƕ�PID��̬����ҳ��###########################*/
__M_PAGE(Angle_PID_Dynamic,"YAW PID DYNAMIC",&Angle_Debug,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Spin	(0,"VELOCITY",INT32,3000,0,&Match_Velocity);
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_Yaw	     );
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_Yaw	     );
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_Yaw	     );
});
/*################################��CCD ����ҳ��################################*/
__M_PAGE(CCD_Debug,"CCD",&Debug,
{
	SOLGUI_Cursor(4,2,5);

	SOLGUI_Widget_GotoPage(0,	&CCD_PID_Static);
	SOLGUI_Widget_GotoPage(1,	&CCD_PID_Dynamic);
	SOLGUI_Widget_OptionText(2,"LinesNumber:  %d",CCD_LinesNumber);
	SOLGUI_Widget_OptionText(3,"LinePoints:   %d",CCD_LinePoints);
	SOLGUI_Widget_OptionText(4,"AutoThreshold:%d",CCD_AutoThreshold);

	Menu_ShowCCD();
});
/*############################��CCD PID��̬����ҳ��#############################*/
__M_PAGE(CCD_PID_Static,"CCD PID STATIC",&CCD_Debug,
{
	SOLGUI_Cursor(4,2,3);

	SOLGUI_Widget_Spin	(0,"KP"	,FLT16	,5000	,0	,&Angle_KP_CCD);
	SOLGUI_Widget_Spin	(1,"KD"	,FLT16	,5000	,0	,&Angle_KD_CCD);
	SOLGUI_Widget_Spin	(2,"KI"	,FLT16	,5000	,0	,&Angle_KI_CCD);

	Menu_ShowCCD();
});
/*############################��CCD PID��̬����ҳ��#############################*/
__M_PAGE(CCD_PID_Dynamic,"CCD PID DYNAMIC",&CCD_Debug,
{
	SOLGUI_Cursor(4,2,4);

	SOLGUI_Widget_Spin	(0,"VELOCITY",INT32,3000,0,&Match_Velocity);
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_CCD);
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_CCD);
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_CCD);

	Menu_ShowCCD();
});
/*################################���Ҷȵ���ҳ��################################*/
__M_PAGE(Gray_Debug,"GRAY",&Debug,
{
	SOLGUI_Cursor_Set(4);
	
	SOLGUI_Widget_OptionText(0,"GRAY VALUE L: %d",GraySensor);
	SOLGUI_Widget_OptionText(1,"GRAY VALUE R: %d",GraySensor2);
	SOLGUI_Widget_Spin	    (2,"THRESHOLD:",INT32,4095,0,&GraySensor_Threshold);
	SOLGUI_Widget_OptionText(3,Gray_Line_Flag==SET?(const u8*)"POINT JUDGE:  YES":(const u8*)"POINT JUDGE:  NO");
});
/*################################���������ҳ��################################*/
__M_PAGE(IR_Debug,"IR",&Debug,
{
	SOLGUI_Cursor_Set(3);
	
	SOLGUI_Widget_OptionText(0,"IR VALUE:   %d",IRSensor);
	SOLGUI_Widget_Spin	    (1,"THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_OptionText(2,IR_Find_Flag==SET?(const u8*)"BLOCK JUDGE:  YES":(const u8*)"BLOCK JUDGE:  NO");
});
/*##############################��OpenMV����ҳ��################################*/
__M_PAGE(OpenMV_Debug,"OpenMV",&Debug,
{
	SOLGUI_Cursor_Set(1);
	
	SOLGUI_Widget_OptionText(0,(const u8*)(OpenMV_Find_Flag == SET?"OpenMV Not Find":"OpenMV Find"));
});
/*###############################����������ҳ��#################################*/
__M_PAGE(Action_Test,"ACTION",&Debug,
{
	SOLGUI_Cursor(4,2,11);
	SOLGUI_Widget_Spin	(0,"VELOCITY" ,INT32,3000,0,&Match_Velocity);
	SOLGUI_Widget_Button(1,"READY"	       ,&Test_Enter_CoordinateSystem);
	SOLGUI_Widget_Button(2,"NEXT POINT"	   ,&Test_NextPoint);
	SOLGUI_Widget_Button(3,"RA TURN LEFT"	 ,&Test_RATurn_L);
	SOLGUI_Widget_Button(4,"RA TURN RIGHT" ,&Test_RATurn_R);
	SOLGUI_Widget_Button(5,"U-TURN"        ,&Test_TurnBack);
	SOLGUI_Widget_Button(6,"MOVE IN LINE"	 ,&Test_Move_CCDCorrect);
	SOLGUI_Widget_Button(7,"MOVE IN YAW"	 ,&Test_Move_YawCorrect);
	SOLGUI_Widget_Button(8,"MOVE OPEN LOOP",&Test_Move);
	SOLGUI_Widget_Button(9,"BREAKING"		   ,&Test_Breaking);
	SOLGUI_Widget_Button(10,"ALARM"	     	 ,&Test_Alarm);
	Menu_ShowCCD();
	
});
/********************************************************************************
    ���ܣ�	�ڲ˵��·������Ǳ���
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Menu_SetWatch(void)
{
	SOLGUI_Widget_Text(0 ,6,OpenMV_RES==1?R4X6:F4X6,(const u8*)(OpenMV_RES==1?"POINT":"BLANK"));
	SOLGUI_Widget_Text(0 ,0,GraySensor<=GraySensor_Threshold?R4X6:F4X6,"%4d",GraySensor);
	SOLGUI_Widget_Text(28,3,F4X6,"VL:%-5d" ,Velocity_L);
	SOLGUI_Widget_Text(50,3,F4X6,"YAW:%.1f",Yaw);
	SOLGUI_Widget_Text(87,3,F4X6,"VR:%-5d" ,Velocity_R);
	SOLGUI_Widget_Text(112 ,0,GraySensor2<=GraySensor_Threshold?R4X6:F4X6,"%4d",GraySensor2);
	SOLGUI_Widget_Text(112 ,6,IR_Find_Flag==SET?R4X6:F4X6,"%4d",IRSensor);
}
/********************************************************************************
    ���ܣ�	�ڲ˵��Ϸ�����CCDͼ����ʾҳ
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Menu_ShowCCD(void)
{
	u8 i,j;

	SOLGUI_DrawPoint(61,55,1);
	SOLGUI_DrawPoint(62,55,1);
	SOLGUI_DrawPoint(63,55,1);
	SOLGUI_DrawPoint(64,55,1);
	SOLGUI_DrawPoint(65,55,1);
	SOLGUI_DrawPoint(66,55,1);
	SOLGUI_DrawPoint(67,55,1);
	SOLGUI_DrawPoint(68,55,1);

	SOLGUI_DrawPoint(61,54,1);
	SOLGUI_DrawPoint(62,54,1);
	SOLGUI_DrawPoint(63,54,1);
	SOLGUI_DrawPoint(64,54,1);
	SOLGUI_DrawPoint(65,54,1);
	SOLGUI_DrawPoint(66,54,1);
	SOLGUI_DrawPoint(67,54,1);
	SOLGUI_DrawPoint(68,54,1);

	SOLGUI_DrawPoint(62,53,1);
	SOLGUI_DrawPoint(63,53,1);
	SOLGUI_DrawPoint(64,53,1);
	SOLGUI_DrawPoint(65,53,1);
	SOLGUI_DrawPoint(66,53,1);
	SOLGUI_DrawPoint(67,53,1);

	SOLGUI_DrawPoint(63,52,1);
	SOLGUI_DrawPoint(64,52,1);
	SOLGUI_DrawPoint(65,52,1);
	SOLGUI_DrawPoint(66,52,1);

	SOLGUI_DrawPoint(64,51,1);
	SOLGUI_DrawPoint(65,51,1);

	for(i=3;i<125;i++)
		for(j=41;j<=50;j++)
			SOLGUI_DrawPoint(i,j,ccd_picture[i]);

	if(CCD_JudgePoint)
		SOLGUI_Widget_Text(41,42,F6X8," CIRCLE ");
	else if(CCD_LineCenter<-62)
		SOLGUI_Widget_Text(38,42,F6X8," MISSING ");
	else
		SOLGUI_Widget_Text(CCD_LineCenter>=0?60:56,43,F4X6," %d",CCD_LineCenter);
}
/********************************************************************************
    ���ܣ�	��ϲ˵�ִ����Ӧ����
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Menu_Support(void)
{
	static FlagStatus CCD_Static_Flag = RESET;
	static FlagStatus Yaw_Static_Flag = RESET;
	static FlagStatus Yaw_Dynamic_Flag = RESET;
/*======================�ٶȵ���ҳ��======================*/
  if(current_page == &Velocity_PI_SET)								  	//���λ���ٶ�PI����ҳ��
		{
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					FlagStatus_Reversal(&CAR_Run_Flag);				      //��ת�����˶���־λ

					Yaw_PID_Flag=RESET;											  	    //�رսǶ�PID������
					CCD_PID_Flag=RESET;											  	  	//�ر�CCD_PID������

					if(CAR_Run_Flag)																//��������˶�ʹ��
						CAR_Velocity = Match_Velocity;									//�������ٶȸ�������Ŀ���ٶ�
					else
						CAR_Velocity = 0;

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
			send_date_u16(Velocity_L,Velocity_R,CAR_Velocity);	//�����ٶ����ݸ���λ��
		}
/*======================�Ƕȵ���ҳ��======================*/
		else if(current_page == &Angle_Debug)						      //���λ�ڽǶȵ���ҳ��
		{			
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					Yaw_Reset_Flag=SET;													  	//����������

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
		}
/*=================�Ƕ� PID��̬����ҳ��===================*/
		else if(current_page == &Angle_PID_Static)						//���λ��ƫ����PID��̬����ҳ��
		{
			CAR_Yaw = Test_Yaw;													        //�����ԽǶȸ�������Ŀ��Ƕ�
			CAR_Velocity = 0;						    			              //����Ŀ���ٶ�����
			
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					FlagStatus_Reversal(&Yaw_Static_Flag);			    //��תƫ����PID��̬���Ա�־λ

					if(Yaw_Static_Flag == SET)											//����Ƕȵ��Ա�־λʹ��
					{
							Yaw_Reset_Flag=SET;											  	//ƫ��������
							Yaw_Arrive_Flag=RESET;
					}

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
			if(Yaw_Static_Flag == SET)											  	//���ʹ�ܽǶȵ���
			{
					CAR_Run_Flag=SET;																//ʹ�ܳ����˶�
					Yaw_PID_Flag=SET;											  		    //ʹ��ƫ���ǻ�PID������
					if(Yaw_Arrive_Flag == SET)
						Yaw_Static_Flag=RESET;
			}
			else if(Yaw_Static_Flag == RESET)										//����رսǶȵ���
			{
					CAR_Run_Flag=RESET;															//ͣ��
					Yaw_PID_Flag=RESET;												    	//�ر�ƫ���ǻ�PID������
					MOTOR_Release();																//�ͷŵ��
			}
			Send_date_float(Yaw,CAR_Yaw,0);											//���ͽǶ����ݸ���λ��
		}
/*=================�Ƕ� PID��̬����ҳ��===================*/
		else if(current_page == &Angle_PID_Dynamic)						//���λ��ƫ����PID��̬����ҳ��
		{
			CAR_Yaw = 0;													              //ƫ��������
			
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					FlagStatus_Reversal(&Yaw_Dynamic_Flag);			    //��תƫ����PID��̬���Ա�־λ

					Yaw_Reset_Flag=SET;											      	//ƫ��������

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
			if(Yaw_Dynamic_Flag == SET)											  	//���ʹ�ܽǶȵ���
			{
					CAR_Velocity = Match_Velocity;									  //�������ٶȸ�������Ŀ���ٶ�
					CAR_Run_Flag=SET;																//ʹ�ܳ����˶�
					Yaw_PID_Flag=SET;											  		    //ʹ��ƫ���ǻ�PID������
			}
			else if(Yaw_Dynamic_Flag == RESET)									//����رսǶȵ���
			{
					CAR_Velocity = 0;									              //����Ŀ���ٶ�����
					CAR_Run_Flag=RESET;															//ͣ��
					Yaw_PID_Flag=RESET;												    	//�ر�ƫ���ǻ�PID������
					MOTOR_Release();																//�ͷŵ��
			}
			Send_date_float(Yaw,CAR_Yaw,0);											//���ͽǶ����ݸ���λ��
		}
/*===================CCD PID��̬����ҳ��===================*/
		else if(current_page == &CCD_PID_Static)				  		//���λ��CCD PID��̬̬����ҳ��
		{
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					FlagStatus_Reversal(&CCD_Static_Flag);					//��תCCD��̬���Ա�־λ

					CAR_Velocity = 0;							            			//����Ŀ���ٶ�����

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
			if(CCD_Static_Flag == SET)	                  		  //���ʹ��CCD��̬���Ա�־λ
			{
					CAR_Run_Flag=SET;																//ʹ�ܳ����˶�
					CCD_PID_Flag=SET;											  		    //ʹ��CCD��PID������
					if(CCD_LineCenter <-62)													//�����ʧ����
							CCD_Static_Flag = RESET;										//�رճ����˶�
			}
			else if(CCD_Static_Flag == RESET)	                  //���CCD��λ�õ���
			{
					CAR_Run_Flag=RESET;															//ͣ��
					CCD_PID_Flag=RESET;												    	//�ر�CCD��PID������
					MOTOR_Release();																//�ͷŵ��
			}
			send_date_u16(CCD_LineCenter,0,0);									//����CCD����λ�����ݸ���λ��
		}
/*===================CCD PID��̬����ҳ��===================*/
		else if(current_page == &CCD_PID_Dynamic)							//���λ��CCD PID��̬����ҳ��
		{
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					CAR_Run_Flag=SET;																//ʹ�ܳ����˶�
					CCD_PID_Flag=SET;											  		    //ʹ��CCD��PID������

					CAR_Velocity = Match_Velocity;										//�������ٶȸ�������Ŀ���ٶ�

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
			else if(CCD_JudgePoint == 1||CCD_LineCenter <-62)		//�������ڵ��ʧ����
			{
					CAR_Run_Flag=RESET;															//ͣ��
					CCD_PID_Flag=RESET;												    	//�ر�CCD��PID������
					MOTOR_Release();																//�ͷŵ��
			}
			send_date_u16(CCD_LineCenter,0,0);									//����CCD����λ�����ݸ���λ��
		}
/*========================�Ҷȵ���ҳ======================*/
		else if(current_page == &Gray_Debug)					    		//���λ�ڻҶȵ���ҳҳ��
		{
			CAR_Run_Flag=RESET;																	//�رճ����˶���־λ

			MOTOR_Release();					    											//�ͷŵ��
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					GraySensor_Threshold=(int)((4096+GraySensor)/2);//����ֵȡΪ��ǰֵ��հ�ֵ����ֵ

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
		}
/*======================OpenMV����ҳ======================*/
		else if(current_page == &OpenMV_Debug)					    	//���λ�ڻҶȵ���ҳҳ��
		{
			CAR_Run_Flag=RESET;																	//�رճ����˶���־λ

			MOTOR_Release();					    											//�ͷŵ��
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					FlagStatus_Reversal(&OpenMV_Use_Flag);					//OpenMV��־λȡ��

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
		}
/*======================��������ҳ��======================*/
		else if(current_page == &Action_Test)							    //���λ�ڶ�������ҳ��
		{
			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������
					
					CAR_Run_Flag = RESET;												  	//�رճ����˶�
					MOTOR_Release();																//�ͷŵ��
					Yaw_PID_Flag = RESET;														//�ر�ƫ���ǻ�PID������
					CCD_PID_Flag = RESET;														//�ر�CCD��PID������

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
		}
/*========================����ҳ��========================*/
		else																									//���λ������ҳ��
		{
			CAR_Run_Flag=RESET;																	//�رճ����˶���־λ
			OpenMV_Use_Flag=RESET;															//�ر�OpenMVʹ�ñ�־λ

			MOTOR_Release();					    											//�ͷŵ��

			if(KEY_BOARD == PRESS)															//������ذ���������
			{
					BUZZER = BUZZER_ON;															//����������

					Yaw_Reset_Flag=SET;													  	//����������

					while(KEY_BOARD == PRESS);											//�ȴ������ͷ�
					BUZZER = BUZZER_OFF;														//�ɿ��������رշ�����
			}
		}
}
/********************************************************************************
    ���ܣ�	�������ⱨ��
    ������	��
    ���أ�	��
    ��ע��	��ʱ500ms�����ⱨ��
*********************************************************************************/
void Test_Alarm(void)
{
	Delay_n5ms(100);
	Audible_and_Visual_Alarm();
}
/********************************************************************************
    ���ܣ�	����ɲ��
    ������	��
    ���أ�	��
    ��ע��	������500ms��ɲ��
*********************************************************************************/
void Test_Breaking(void)
{
	CAR_Move(Match_Velocity);
	Delay_n5ms(100);
	CAR_Breaking();
}
/********************************************************************************
    ���ܣ�	���Կ���ֱ��
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_Move(void)
{
	CAR_Move(Match_Velocity);
}
/********************************************************************************
    ���ܣ�	����ƫ���ǻ��ջ�ֱ��
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_Move_YawCorrect(void)
{
	CAR_Move_YawCorrect(Match_Velocity);
}
/********************************************************************************
    ���ܣ�	����CCD���ջ�ֱ��
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_Move_CCDCorrect(void)
{
	CAR_Move_CCDCorrect(Match_Velocity);
}
/********************************************************************************
    ���ܣ�	������תֱ��
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_RATurn_L(void)
{
	Turn_Left();
}
/********************************************************************************
    ���ܣ�	������תֱ��
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_RATurn_R(void)
{
	Turn_Right();
}
/********************************************************************************
    ���ܣ�	���Ե�ͷ
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_TurnBack(void)
{
	Turn_Back();
}
/********************************************************************************
    ���ܣ�	���Ե�����һ�ڵ�
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_NextPoint(void)
{
	Move_NextPoint(Match_Velocity);
}
/********************************************************************************
    ���ܣ�	���Խ�������ϵ
    ������	��
    ���أ�	��
    ��ע��	��
*********************************************************************************/
void Test_Enter_CoordinateSystem(void)
{
	Audible_and_Visual_Alarm();           //���ⱨ��
	Delay_sec(1);
	Audible_and_Visual_Alarm();           //���ⱨ��
	
	Enter_CoordinateSystem();
}
//////////////////////////////////////////////////////////////////////////////////
