//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
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
/*###################################【主页】###################################*/
__M_PAGE(Homepage,"HOMEPAGE",PAGE_NULL,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_GotoPage(0,	&Match);
	SOLGUI_Widget_GotoPage(1,	&Debug);
});
/*##################################【比赛页】##################################*/
__M_PAGE(Match,"MATCH",&Homepage,
{
	SOLGUI_Cursor_Set(5);

	SOLGUI_Widget_GotoPage(0,	&TASK_1);
	SOLGUI_Widget_GotoPage(1,	&TASK_2);
	SOLGUI_Widget_GotoPage(2,	&TASK_3);
	SOLGUI_Widget_GotoPage(3,	&TASK_4);
	SOLGUI_Widget_GotoPage(4,	&TASK_5);
});
/*##################################【任务一】##################################*/
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
/*##################################【任务二】##################################*/
__M_PAGE(TASK_2,"TASK 2",&Match,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_Button(0,"TASK 2 SCHEME A",&Task_II_SchemeA);
	SOLGUI_Widget_Spin	(1,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################【任务三】##################################*/
__M_PAGE(TASK_3,"TASK 3",&Match,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_Button(0,"TASK 3 SCHEME A",&Task_III_SchemeA);
	SOLGUI_Widget_Spin	(1,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################【任务四】##################################*/
__M_PAGE(TASK_4,"TASK 4",&Match,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Button(0,"TASK 4 SCHEME A",&Task_IV_SchemeA);
	SOLGUI_Widget_Button(1,"TASK 4 SCHEME B",&Task_IV_SchemeB);
	SOLGUI_Widget_Spin	(2,"IR THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_Spin	(3,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################【任务五】##################################*/
__M_PAGE(TASK_5,"TASK 5",&Match,
{
	SOLGUI_Cursor_Set(3);

	SOLGUI_Widget_Button(0,"TASK 5 SCHEME A",&Task_V_SchemeA);
	SOLGUI_Widget_Spin	(1,"IR THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_Spin	(2,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*##################################【调试页】##################################*/
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
/*###############################【速度PI调试页】###############################*/
__M_PAGE(Velocity_PI_SET,"VELOCITY",&Debug,
{
	SOLGUI_Cursor_Set(5);

	SOLGUI_Widget_Spin	(0,"VL-KP",FLT16	,5000	,0	,&Velocity_KP_L	  );
	SOLGUI_Widget_Spin	(1,"VL-KI",FLT16	,5000	,0	,&Velocity_KI_L	  );
	SOLGUI_Widget_Spin	(2,"VR-KP",FLT16	,5000	,0	,&Velocity_KP_R	  );
	SOLGUI_Widget_Spin	(3,"VR-KI",FLT16	,5000	,0	,&Velocity_KI_R	  );
	SOLGUI_Widget_Spin	(4,"VELOCITY",INT32,3000,0,&Match_Velocity);
});
/*#################################【角度调试页】###############################*/
__M_PAGE(Angle_Debug,"ANGLE",&Debug,
{
	SOLGUI_Cursor_Set(2);

	SOLGUI_Widget_GotoPage(0,	&Angle_PID_Static    );
	SOLGUI_Widget_GotoPage(1,	&Angle_PID_Dynamic   );
});
/*##############################【角度PID静态调试页】###########################*/
__M_PAGE(Angle_PID_Static,"YAW PID STATIC",&Angle_Debug,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Spin	(0,"ANGLE",INT32,360,-360,&Test_Yaw           );
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_Yaw	     );
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_Yaw	     );
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_Yaw	     );
});
/*##############################【角度PID动态调试页】###########################*/
__M_PAGE(Angle_PID_Dynamic,"YAW PID DYNAMIC",&Angle_Debug,
{
	SOLGUI_Cursor_Set(4);

	SOLGUI_Widget_Spin	(0,"VELOCITY",INT32,3000,0,&Match_Velocity);
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_Yaw	     );
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_Yaw	     );
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_Yaw	     );
});
/*################################【CCD 调试页】################################*/
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
/*############################【CCD PID静态调试页】#############################*/
__M_PAGE(CCD_PID_Static,"CCD PID STATIC",&CCD_Debug,
{
	SOLGUI_Cursor(4,2,3);

	SOLGUI_Widget_Spin	(0,"KP"	,FLT16	,5000	,0	,&Angle_KP_CCD);
	SOLGUI_Widget_Spin	(1,"KD"	,FLT16	,5000	,0	,&Angle_KD_CCD);
	SOLGUI_Widget_Spin	(2,"KI"	,FLT16	,5000	,0	,&Angle_KI_CCD);

	Menu_ShowCCD();
});
/*############################【CCD PID动态调试页】#############################*/
__M_PAGE(CCD_PID_Dynamic,"CCD PID DYNAMIC",&CCD_Debug,
{
	SOLGUI_Cursor(4,2,4);

	SOLGUI_Widget_Spin	(0,"VELOCITY",INT32,3000,0,&Match_Velocity);
	SOLGUI_Widget_Spin	(1,"KP"	,FLT16	,5000	,0	,&Angle_KP_CCD);
	SOLGUI_Widget_Spin	(2,"KD"	,FLT16	,5000	,0	,&Angle_KD_CCD);
	SOLGUI_Widget_Spin	(3,"KI"	,FLT16	,5000	,0	,&Angle_KI_CCD);

	Menu_ShowCCD();
});
/*################################【灰度调试页】################################*/
__M_PAGE(Gray_Debug,"GRAY",&Debug,
{
	SOLGUI_Cursor_Set(4);
	
	SOLGUI_Widget_OptionText(0,"GRAY VALUE L: %d",GraySensor);
	SOLGUI_Widget_OptionText(1,"GRAY VALUE R: %d",GraySensor2);
	SOLGUI_Widget_Spin	    (2,"THRESHOLD:",INT32,4095,0,&GraySensor_Threshold);
	SOLGUI_Widget_OptionText(3,Gray_Line_Flag==SET?(const u8*)"POINT JUDGE:  YES":(const u8*)"POINT JUDGE:  NO");
});
/*################################【红外调试页】################################*/
__M_PAGE(IR_Debug,"IR",&Debug,
{
	SOLGUI_Cursor_Set(3);
	
	SOLGUI_Widget_OptionText(0,"IR VALUE:   %d",IRSensor);
	SOLGUI_Widget_Spin	    (1,"THRESHOLD:",INT32,4095,0,&IRSensor_Threshold);
	SOLGUI_Widget_OptionText(2,IR_Find_Flag==SET?(const u8*)"BLOCK JUDGE:  YES":(const u8*)"BLOCK JUDGE:  NO");
});
/*##############################【OpenMV调试页】################################*/
__M_PAGE(OpenMV_Debug,"OpenMV",&Debug,
{
	SOLGUI_Cursor_Set(1);
	
	SOLGUI_Widget_OptionText(0,(const u8*)(OpenMV_Find_Flag == SET?"OpenMV Not Find":"OpenMV Find"));
});
/*###############################【动作测试页】#################################*/
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
    功能：	在菜单下方放置仪表盘
    参数：	无
    返回：	无
    备注：	无
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
    功能：	在菜单上方放置CCD图像显示页
    参数：	无
    返回：	无
    备注：	无
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
    功能：	配合菜单执行相应程序
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Menu_Support(void)
{
	static FlagStatus CCD_Static_Flag = RESET;
	static FlagStatus Yaw_Static_Flag = RESET;
	static FlagStatus Yaw_Dynamic_Flag = RESET;
/*======================速度调节页面======================*/
  if(current_page == &Velocity_PI_SET)								  	//如果位于速度PI调节页面
		{
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					FlagStatus_Reversal(&CAR_Run_Flag);				      //翻转车辆运动标志位

					Yaw_PID_Flag=RESET;											  	    //关闭角度PID控制器
					CCD_PID_Flag=RESET;											  	  	//关闭CCD_PID控制器

					if(CAR_Run_Flag)																//如果车辆运动使能
						CAR_Velocity = Match_Velocity;									//将测试速度赋给车辆目标速度
					else
						CAR_Velocity = 0;

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
			send_date_u16(Velocity_L,Velocity_R,CAR_Velocity);	//发送速度数据给上位机
		}
/*======================角度调节页面======================*/
		else if(current_page == &Angle_Debug)						      //如果位于角度调节页面
		{			
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					Yaw_Reset_Flag=SET;													  	//陀螺仪清零

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
		}
/*=================角度 PID静态调节页面===================*/
		else if(current_page == &Angle_PID_Static)						//如果位于偏航角PID静态调节页面
		{
			CAR_Yaw = Test_Yaw;													        //将测试角度赋给车辆目标角度
			CAR_Velocity = 0;						    			              //车辆目标速度清零
			
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					FlagStatus_Reversal(&Yaw_Static_Flag);			    //翻转偏航角PID静态调试标志位

					if(Yaw_Static_Flag == SET)											//如果角度调试标志位使能
					{
							Yaw_Reset_Flag=SET;											  	//偏航角清零
							Yaw_Arrive_Flag=RESET;
					}

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
			if(Yaw_Static_Flag == SET)											  	//如果使能角度调试
			{
					CAR_Run_Flag=SET;																//使能车辆运动
					Yaw_PID_Flag=SET;											  		    //使能偏航角环PID控制器
					if(Yaw_Arrive_Flag == SET)
						Yaw_Static_Flag=RESET;
			}
			else if(Yaw_Static_Flag == RESET)										//如果关闭角度调试
			{
					CAR_Run_Flag=RESET;															//停车
					Yaw_PID_Flag=RESET;												    	//关闭偏航角环PID控制器
					MOTOR_Release();																//释放电机
			}
			Send_date_float(Yaw,CAR_Yaw,0);											//发送角度数据给上位机
		}
/*=================角度 PID动态调节页面===================*/
		else if(current_page == &Angle_PID_Dynamic)						//如果位于偏航角PID动态调节页面
		{
			CAR_Yaw = 0;													              //偏航角清零
			
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					FlagStatus_Reversal(&Yaw_Dynamic_Flag);			    //翻转偏航角PID动态调试标志位

					Yaw_Reset_Flag=SET;											      	//偏航角清零

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
			if(Yaw_Dynamic_Flag == SET)											  	//如果使能角度调试
			{
					CAR_Velocity = Match_Velocity;									  //将测试速度赋给车辆目标速度
					CAR_Run_Flag=SET;																//使能车辆运动
					Yaw_PID_Flag=SET;											  		    //使能偏航角环PID控制器
			}
			else if(Yaw_Dynamic_Flag == RESET)									//如果关闭角度调试
			{
					CAR_Velocity = 0;									              //车辆目标速度清零
					CAR_Run_Flag=RESET;															//停车
					Yaw_PID_Flag=RESET;												    	//关闭偏航角环PID控制器
					MOTOR_Release();																//释放电机
			}
			Send_date_float(Yaw,CAR_Yaw,0);											//发送角度数据给上位机
		}
/*===================CCD PID静态调节页面===================*/
		else if(current_page == &CCD_PID_Static)				  		//如果位于CCD PID静态态调节页面
		{
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					FlagStatus_Reversal(&CCD_Static_Flag);					//翻转CCD静态调试标志位

					CAR_Velocity = 0;							            			//车辆目标速度清零

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
			if(CCD_Static_Flag == SET)	                  		  //如果使能CCD静态调试标志位
			{
					CAR_Run_Flag=SET;																//使能车辆运动
					CCD_PID_Flag=SET;											  		    //使能CCD环PID控制器
					if(CCD_LineCenter <-62)													//如果丢失黑线
							CCD_Static_Flag = RESET;										//关闭车辆运动
			}
			else if(CCD_Static_Flag == RESET)	                  //如果CCD环位置到达
			{
					CAR_Run_Flag=RESET;															//停车
					CCD_PID_Flag=RESET;												    	//关闭CCD环PID控制器
					MOTOR_Release();																//释放电机
			}
			send_date_u16(CCD_LineCenter,0,0);									//发送CCD中心位置数据给上位机
		}
/*===================CCD PID动态调节页面===================*/
		else if(current_page == &CCD_PID_Dynamic)							//如果位于CCD PID动态调节页面
		{
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					CAR_Run_Flag=SET;																//使能车辆运动
					CCD_PID_Flag=SET;											  		    //使能CCD环PID控制器

					CAR_Velocity = Match_Velocity;										//将测试速度赋给车辆目标速度

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
			else if(CCD_JudgePoint == 1||CCD_LineCenter <-62)		//如果到达黑点或丢失黑线
			{
					CAR_Run_Flag=RESET;															//停车
					CCD_PID_Flag=RESET;												    	//关闭CCD环PID控制器
					MOTOR_Release();																//释放电机
			}
			send_date_u16(CCD_LineCenter,0,0);									//发送CCD中心位置数据给上位机
		}
/*========================灰度调试页======================*/
		else if(current_page == &Gray_Debug)					    		//如果位于灰度调试页页面
		{
			CAR_Run_Flag=RESET;																	//关闭车辆运动标志位

			MOTOR_Release();					    											//释放电机
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					GraySensor_Threshold=(int)((4096+GraySensor)/2);//将阈值取为当前值与空白值的中值

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
		}
/*======================OpenMV调试页======================*/
		else if(current_page == &OpenMV_Debug)					    	//如果位于灰度调试页页面
		{
			CAR_Run_Flag=RESET;																	//关闭车辆运动标志位

			MOTOR_Release();					    											//释放电机
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					FlagStatus_Reversal(&OpenMV_Use_Flag);					//OpenMV标志位取反

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
		}
/*======================动作测试页面======================*/
		else if(current_page == &Action_Test)							    //如果位于动作测试页面
		{
			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声
					
					CAR_Run_Flag = RESET;												  	//关闭车辆运动
					MOTOR_Release();																//释放电机
					Yaw_PID_Flag = RESET;														//关闭偏航角环PID控制器
					CCD_PID_Flag = RESET;														//关闭CCD环PID控制器

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
		}
/*========================其他页面========================*/
		else																									//如果位于其他页面
		{
			CAR_Run_Flag=RESET;																	//关闭车辆运动标志位
			OpenMV_Use_Flag=RESET;															//关闭OpenMV使用标志位

			MOTOR_Release();					    											//释放电机

			if(KEY_BOARD == PRESS)															//如果板载按键被按下
			{
					BUZZER = BUZZER_ON;															//蜂鸣器发声

					Yaw_Reset_Flag=SET;													  	//陀螺仪清零

					while(KEY_BOARD == PRESS);											//等待按键释放
					BUZZER = BUZZER_OFF;														//松开按键，关闭蜂鸣器
			}
		}
}
/********************************************************************************
    功能：	测试声光报警
    参数：	无
    返回：	无
    备注：	延时500ms后声光报警
*********************************************************************************/
void Test_Alarm(void)
{
	Delay_n5ms(100);
	Audible_and_Visual_Alarm();
}
/********************************************************************************
    功能：	测试刹车
    参数：	无
    返回：	无
    备注：	开环跑500ms后刹车
*********************************************************************************/
void Test_Breaking(void)
{
	CAR_Move(Match_Velocity);
	Delay_n5ms(100);
	CAR_Breaking();
}
/********************************************************************************
    功能：	测试开环直行
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_Move(void)
{
	CAR_Move(Match_Velocity);
}
/********************************************************************************
    功能：	测试偏航角环闭环直行
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_Move_YawCorrect(void)
{
	CAR_Move_YawCorrect(Match_Velocity);
}
/********************************************************************************
    功能：	测试CCD环闭环直行
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_Move_CCDCorrect(void)
{
	CAR_Move_CCDCorrect(Match_Velocity);
}
/********************************************************************************
    功能：	测试左转直角
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_RATurn_L(void)
{
	Turn_Left();
}
/********************************************************************************
    功能：	测试右转直角
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_RATurn_R(void)
{
	Turn_Right();
}
/********************************************************************************
    功能：	测试调头
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_TurnBack(void)
{
	Turn_Back();
}
/********************************************************************************
    功能：	测试到达下一黑点
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_NextPoint(void)
{
	Move_NextPoint(Match_Velocity);
}
/********************************************************************************
    功能：	测试进入坐标系
    参数：	无
    返回：	无
    备注：	无
*********************************************************************************/
void Test_Enter_CoordinateSystem(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Delay_sec(1);
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();
}
//////////////////////////////////////////////////////////////////////////////////
