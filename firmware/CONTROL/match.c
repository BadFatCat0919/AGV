//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#include "match.h"

int Match_Velocity=500;
int Match_Velocity_Search=500;
int Match_Velocity_OpenMVSearch=400;

void Around_Block(void);
/********************************************************************************
    功能：	任务一方案A
    参数：	无
    返回：	无
    备注：	顺序绕圈到达3#、4#两点
*********************************************************************************/
void Task_I_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Move_NextPoint_Pass(600);	            //到达2#点

	Move_NextPoint(Match_Velocity);	      //到达3#点
	Audible_and_Visual_Alarm();           //声光报警

	Turn_Right();                         //右转
	
	Move_NextPoint(Match_Velocity);	      //到达6#点

	Turn_Right();                         //右转
	Move_NextPoint_Pass(600);							//到达5#点

	Move_NextPoint(Match_Velocity);	      //到达4#点
	Audible_and_Visual_Alarm();           //声光报警
}
/********************************************************************************
    功能：	任务一方案B
    参数：	无
    返回：	无
    备注：	直线到达3#点，右转，直线到达1#、4#间黑线，
					右转CCD修正至线上，直线到达4#点
*********************************************************************************/
int Task_I_SchemeB_Angle = -151;
void Task_I_SchemeB(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Move_NextPoint_Pass(600);	            //到达2#点

	Move_NextPoint(Match_Velocity);	      //到达3#点
	Audible_and_Visual_Alarm();           //声光报警
	
	CAR_Turn(Task_I_SchemeB_Angle);	    //右转朝向1#、4#间黑线
	CAR_Breaking();												//刹车
	CAR_Move_YawCorrect(500);	            //利用偏航角环闭环直行
	Delay_n5ms(80);										  	//经过出发点的黑点
  while(Gray_Line_Flag == RESET);				//越过2#、5#间黑线
	Delay_n5ms(160);											//保持当前速度运行
	CAR_Velocity = 100;										//即将到达目标，减速
  while(Gray_Line_Flag == RESET);				//到达1#、4#间黑线
	CAR_Turn(80);													//左转朝向黑点
	Move_NextPoint(Match_Velocity);				//在CCD修正下到达4#点
	Audible_and_Visual_Alarm();           //声光报警
}
int Task_I_SchemeC_Angle = -158;
/********************************************************************************
    功能：	任务一方案C
    参数：	无
    返回：	无
    备注：	直线到达3点，右转151°，直线到达4#点
*********************************************************************************/
void Task_I_SchemeC(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Move_NextPoint_Pass(600);	            //到达2#点
	Move_NextPoint(Match_Velocity);	      //到达3#点
	Audible_and_Visual_Alarm();           //声光报警
	
	CAR_Turn(Task_I_SchemeC_Angle);	    //右转朝向4#间黑线
	CAR_Breaking();												//刹车
	CAR_Move_YawCorrect(1000);	          //利用偏航角环闭环直行
	Delay_n5ms(120);											//经过出发点的黑线
  while(Gray_Line_Flag == RESET);				//越过2#、5#间黑线
	Delay_n5ms(23);	  										//保持当前速度运行
	
  CAR_Velocity = 200;										//减速
  
	while(Gray_Line_Flag == RESET);				//到达4#点
	CAR_Breaking();												//刹车
	
	CAR_Turn(-35);												//左转朝向黑点
	if(CCD_LineCenter>-63)
	Move_NextPoint(Match_Velocity);				//在CCD修正下到达4#点
	Audible_and_Visual_Alarm();           //声光报警
}
/********************************************************************************
    功能：	任务二方案A
    参数：	无
    返回：	无
    备注：	顺序到达1#、2#、3#、6#四点
*********************************************************************************/
void Task_II_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();							//进入坐标系，到达1#点
	Audible_and_Visual_Alarm();           //声光报警

	Move_NextPoint_Pass(Match_Velocity);	//到达2#点
	Audible_and_Visual_Alarm();           //声光报警

	Move_NextPoint(Match_Velocity);	      //到达3#点
	Audible_and_Visual_Alarm();           //声光报警

	Turn_Right();                         //右转
	
	Move_NextPoint(Match_Velocity);	      //到达6#点
	Audible_and_Visual_Alarm();           //声光报警
}
/********************************************************************************
    功能：	任务三方案A
    参数：	无
    返回：	无
    备注：	顺序到达1#、2#、3#、6#四点
*********************************************************************************/
void Task_III_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();							//进入坐标系，到达1#点
	Audible_and_Visual_Alarm();           //声光报警

	Move_NextPoint_Pass(Match_Velocity);	//到达2#点
	Audible_and_Visual_Alarm();           //声光报警

	Move_NextPoint(Match_Velocity);	      //到达3#点
	Audible_and_Visual_Alarm();           //声光报警

	Turn_Right();                         //右转
	
	Move_NextPoint(Match_Velocity);	      //到达6#点
	Audible_and_Visual_Alarm();           //声光报警
}
/********************************************************************************
    功能：	任务四方案A
    参数：	无
    返回：	无
    备注：	蛇形搜索
*********************************************************************************/
void Task_IV_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();							//进入坐标系，到达1#点

	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过2#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达3#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过6#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达9#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过8#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达7#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达4#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过5#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达6#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Back();													//调头
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过5#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达4#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达1#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
}
/********************************************************************************
    功能：	任务四方案B
    参数：	无
    返回：	无
    备注：	中心扫描
*********************************************************************************/
void Task_IV_SchemeB(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();							//进入坐标系，到达1#点
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达2#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达5#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//如果发现物块，环绕物块周围四个点
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//如果发现物块，环绕物块周围四个点
		return;
	}
	
	if(Rotate_Search(50))
	{
		Around_Block();											//如果发现物块，环绕物块周围四个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达2#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达3#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过6#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达9#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，通过8#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达7#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_IRSearch(Match_Velocity_Search,Match_Velocity))
																				//搜索前进，到达4#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
}
/********************************************************************************
    功能：	任务五方案A
    参数：	无
    返回：	无
    备注：	蛇形搜索
*********************************************************************************/
void Task_V_SchemeA(void)
{
	Audible_and_Visual_Alarm();           //声光报警
	Wait_StartCMD();											//等待手势启动指令
	Audible_and_Visual_Alarm();           //声光报警
	
	Enter_CoordinateSystem();							//进入坐标系，到达1#点

	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，通过2#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达3#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，通过6#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达9#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，通过8#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达7#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达4#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，通过5#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达6#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Back();													//调头
	
	if(Move_NextPoint_Pass_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，通过5#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达4#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
	
	Turn_Right();													//右转
	
	if(Move_NextPoint_OpenMVSearch(Match_Velocity_OpenMVSearch,Match_Velocity))
																				//搜索前进，到达1#点
	{
		Audible_and_Visual_Alarm();         //声光报警
		Turn_Right();                       //右转
		Around_Block();											//如果发现物块，环绕物块周围其它三个点
		return;
	}
}
/********************************************************************************
    功能：	发现物块，环绕物块周围四个点
    参数：	无
    返回：	无
    备注：	从第一点出发，顺时针到达目标方块周围其它三点
*********************************************************************************/
void Around_Block(void)
{
		Move_NextPoint(Match_Velocity);	    //到达5#点
		Audible_and_Visual_Alarm();         //声光报警
		
		Turn_Right();                       //右转
		Move_NextPoint(Match_Velocity);	    //到达4#点
		Audible_and_Visual_Alarm();         //声光报警
		
		Turn_Right();                       //右转
		Move_NextPoint(Match_Velocity);	    //到达1#点
		Audible_and_Visual_Alarm();         //声光报警
}
