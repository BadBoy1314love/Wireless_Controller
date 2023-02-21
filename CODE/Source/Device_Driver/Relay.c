#include "Config.h"
#include "Relay.h"

extern u16 NowTime;  //引用时间

/*需要在设置菜单设置的变量*/

/*用于记录端口是否被触发*/
//Pin12输出响应标志,任务响应后清除
bit Pin12 = 0; 
bit Pin13 = 0; 
bit Pin14 = 0;
bit Pin15 = 0;
bit Pin16 = 0;
bit Pin17 = 0;

bit Pin20 = 0;
bit Pin21 = 0;
bit Pin22 = 0;
bit Pin23 = 0;
bit Pin24 = 0;

bit Pin35 = 0;
bit Pin36 = 0;
bit Pin37 = 0;

/*端口的触发模式*/
/*触发模式（0为自锁模式）（1为立即模式）*/
//自锁模式：按键按下，释放才会更新任务状态
//立即模式：按键按下，立刻更新任务状态，按键释放才可重新更新
bdata u16 Pin_Trigger_Mode;

sbit Pin10_Trigger_Mode = Pin_Trigger_Mode^0;
sbit Pin11_Trigger_Mode = Pin_Trigger_Mode^1;

sbit Pin12_Trigger_Mode = Pin_Trigger_Mode^2;
sbit Pin13_Trigger_Mode = Pin_Trigger_Mode^3;
sbit Pin14_Trigger_Mode = Pin_Trigger_Mode^4;
sbit Pin15_Trigger_Mode = Pin_Trigger_Mode^5;
sbit Pin16_Trigger_Mode = Pin_Trigger_Mode^6;
sbit Pin17_Trigger_Mode = Pin_Trigger_Mode^7;

sbit Pin20_Trigger_Mode = Pin_Trigger_Mode^8;
sbit Pin21_Trigger_Mode = Pin_Trigger_Mode^9;
sbit Pin22_Trigger_Mode = Pin_Trigger_Mode^10;
sbit Pin23_Trigger_Mode = Pin_Trigger_Mode^11;
sbit Pin24_Trigger_Mode = Pin_Trigger_Mode^12;

sbit Pin35_Trigger_Mode = Pin_Trigger_Mode^13;
sbit Pin36_Trigger_Mode = Pin_Trigger_Mode^14;
sbit Pin37_Trigger_Mode = Pin_Trigger_Mode^15;

/*
bit Pin10_Trigger_Mode = 0;
bit Pin11_Trigger_Mode = 0;

bit Pin12_Trigger_Mode = 1;
bit Pin13_Trigger_Mode = 1;
bit Pin14_Trigger_Mode = 0;
bit Pin15_Trigger_Mode = 0;
bit Pin16_Trigger_Mode = 0;
bit Pin17_Trigger_Mode = 0;

bit Pin20_Trigger_Mode = 1;
bit Pin21_Trigger_Mode = 1;
bit Pin22_Trigger_Mode = 1;
bit Pin23_Trigger_Mode = 1;
bit Pin24_Trigger_Mode = 1;

bit Pin35_Trigger_Mode = 0;
bit Pin36_Trigger_Mode = 0;
bit Pin37_Trigger_Mode = 0;
*/

/*端口外部的模拟按键*/
/*0代表按键状态还没有按下，1代表按键处于按下的状态*/
bit Pin10_Key = 0;
bit Pin11_Key = 0;

bit Pin12_Key = 0;
bit Pin13_Key = 0;
bit Pin14_Key = 0;
bit Pin15_Key = 0;
bit Pin16_Key = 0;
bit Pin17_Key = 0;

bit Pin20_Key = 0;
bit Pin21_Key = 0;
bit Pin22_Key = 0;
bit Pin23_Key = 0;
bit Pin24_Key = 0;

bit Pin35_Key = 0;
bit Pin36_Key = 0;
bit Pin37_Key = 0;

/*输入模式时作为端口触发更新任务号*/ 
/*输出模式时选择关联任务号*/
/*端口模式（0为输入模式）（1为输出模式）*/
bdata u16 Pin_Mode;  //可位寻址变量

sbit Pin10_Mode = Pin_Mode^0;
sbit Pin11_Mode = Pin_Mode^1;

sbit Pin12_Mode = Pin_Mode^2;
sbit Pin13_Mode = Pin_Mode^3;
sbit Pin14_Mode = Pin_Mode^4;
sbit Pin15_Mode = Pin_Mode^5;
sbit Pin16_Mode = Pin_Mode^6;
sbit Pin17_Mode = Pin_Mode^7;

sbit Pin20_Mode = Pin_Mode^8;
sbit Pin21_Mode = Pin_Mode^9;
sbit Pin22_Mode = Pin_Mode^10;
sbit Pin23_Mode = Pin_Mode^11;
sbit Pin24_Mode = Pin_Mode^12;

sbit Pin35_Mode = Pin_Mode^13;
sbit Pin36_Mode = Pin_Mode^14;
sbit Pin37_Mode = Pin_Mode^15;

s8 xdata Pin10_Task_Number = 1; //	bit Pin10_Mode = 1;
s8 xdata Pin11_Task_Number = 2;	//  bit Pin11_Mode = 1;

s8 xdata Pin12_Task_Number = 1; //  bit Pin12_Mode = 0;
s8 xdata Pin13_Task_Number = 2;	//  bit Pin13_Mode = 0;
s8 xdata Pin14_Task_Number = 3;	//  bit Pin14_Mode = 0;
s8 xdata Pin15_Task_Number = 4;	//  bit Pin15_Mode = 0;
s8 xdata Pin16_Task_Number = 5;	//  bit Pin16_Mode = 0;
s8 xdata Pin17_Task_Number = 6;	//  bit Pin17_Mode = 0;

s8 xdata Pin20_Task_Number = 4;	//  bit Pin20_Mode = 0;
s8 xdata Pin21_Task_Number = 4;	//  bit Pin21_Mode = 0;
s8 xdata Pin22_Task_Number = 4; //  bit Pin22_Mode = 0;
s8 xdata Pin23_Task_Number = 4;	//  bit Pin23_Mode = 0;
s8 xdata Pin24_Task_Number = 4; //  bit Pin24_Mode = 0;

s8 xdata Pin35_Task_Number = 1; //  bit Pin35_Mode = 1;
s8 xdata Pin36_Task_Number = 2;	//  bit Pin36_Mode = 1;
s8 xdata Pin37_Task_Number = 3;	//  bit Pin37_Mode = 1;



/*将要更新的任务号*/
u8 Task_Number = 0;  //正常触发任务号（自锁触发）
u8 Task_Number_Immediate = 0;  //立即触发任务号 （立即触发）

/*任务运行控制位*/
bit Task1 = 0;  //任务1 运行(1)/暂停(0)
bit Task2 = 0;
bit Task3 = 0;
bit Task4 = 0;
bit Task5 = 0;
bit Task6 = 0;

/*任务运行模式*/
u8 xdata Task1_Mode = 1;  //任务1运行时的模式
u8 xdata Task2_Mode = 1;
u8 xdata Task3_Mode = 1;
u8 xdata Task4_Mode = 1;
u8 xdata Task5_Mode = 1;
u8 xdata Task6_Mode = 1;

/*任务输出位*/
bit Task1_Output = 0;
bit Task2_Output = 0;
bit Task3_Output = 0;
bit Task4_Output = 0;
bit Task5_Output = 0;
bit Task6_Output = 0;

/*时间区间间歇模式*/

//对所有任务
bdata u8 Task_OverTime_Reset;  //设置可位寻址变量
sbit Task1_OverTime_Reset = Task_OverTime_Reset^1;
sbit Task2_OverTime_Reset = Task_OverTime_Reset^2;
sbit Task3_OverTime_Reset = Task_OverTime_Reset^3;
sbit Task4_OverTime_Reset = Task_OverTime_Reset^4;
sbit Task5_OverTime_Reset = Task_OverTime_Reset^5;
sbit Task6_OverTime_Reset = Task_OverTime_Reset^6;

/*任务一*/
s16 xdata Task1_StartTime = 0;//任务1起始运行时间
s16 xdata Task1_EndTime = 1439;//任务1结束运行时间
s32 xdata Task1_OverTime = 2*3000; //任务1运行超时时间
u32 xdata Task1_OverTime_Count=0; //任务1运行超时时间计数器
//bit Task1_OverTime_Reset = 0; //任务1运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task1_OnState = 1; //表示Task1输出ON状态 1：有输出 0；无输出
s32 xdata Task1_OnTime = 2*1;  //表示Task1输出ON状态的时间
s32 xdata Task1_OffTime = 2*1; //表示Task1输出OFF状态的时间

u32 xdata Task1_CountTime = 1;  //任务1 ON/OFF状态时间计数器

/*任务二*/
s16 xdata Task2_StartTime = 0;//任务2起始运行时间
s16 xdata Task2_EndTime = 1439;//任务2结束运行时间
s32 xdata Task2_OverTime = 2*3000; //任务2运行超时时间
u32 xdata Task2_OverTime_Count=0; //任务2运行超时时间计数器
//bit Task2_OverTime_Reset = 0; //任务2运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task2_OnState = 1; //表示Task2输出ON状态 1：有输出 0；无输出
s32 xdata Task2_OnTime = 2*1;  //表示Task2输出ON状态的时间
s32 xdata Task2_OffTime = 2*1; //表示Task2输出OFF状态的时间

u32 xdata Task2_CountTime = 1;  //任务2 ON/OFF状态时间计数器

/*任务三*/
s16 xdata Task3_StartTime = 0;//任务3起始运行时间
s16 xdata Task3_EndTime = 1439;//任务3结束运行时间
s32 xdata Task3_OverTime = 2*3000; //任务3运行超时时间
u32 xdata Task3_OverTime_Count=0; //任务3运行超时时间计数器
//bit Task3_OverTime_Reset = 0; //任务3运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task3_OnState = 1; //表示Task3输出ON状态 1：有输出 0；无输出
s32 xdata Task3_OnTime = 2*1;  //表示Task3输出ON状态的时间
s32 xdata Task3_OffTime = 2*1; //表示Task3输出OFF状态的时间

u32 xdata Task3_CountTime = 1;  //任务3 ON/OFF状态时间计数器

/*任务四*/
s16 xdata Task4_StartTime = 0;//任务4起始运行时间
s16 xdata Task4_EndTime = 1439;//任务4结束运行时间
s32 xdata Task4_OverTime = 2*3000; //任务4运行超时时间
u32 xdata Task4_OverTime_Count=0; //任务4运行超时时间计数器
//bit Task4_OverTime_Reset = 0; //任务4运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task4_OnState = 1; //表示Task4输出ON状态 1：有输出 0；无输出
s32 xdata Task4_OnTime = 2*1;  //表示Task4输出ON状态的时间
s32 xdata Task4_OffTime = 2*1; //表示Task4输出OFF状态的时间

u32 xdata Task4_CountTime = 1;  //任务4 ON/OFF状态时间计数器

/*任务五*/
s16 xdata Task5_StartTime = 0;//任务5起始运行时间
s16 xdata Task5_EndTime = 1439;//任务5结束运行时间
s32 xdata Task5_OverTime = 2*3000; //任务5运行超时时间
u32 xdata Task5_OverTime_Count=0; //任务5运行超时时间计数器
//bit Task5_OverTime_Reset = 0; //任务5运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task5_OnState = 1; //表示Task5输出ON状态 1：有输出 0；无输出
s32 xdata Task5_OnTime = 2*1;  //表示Task5输出ON状态的时间
s32 xdata Task5_OffTime = 2*1; //表示Task5输出OFF状态的时间

u32 xdata Task5_CountTime = 1;  //任务5 ON/OFF状态时间计数器

/*任务六*/
s16 xdata Task6_StartTime = 0;//任务6起始运行时间
s16 xdata Task6_EndTime = 1439;//任务6结束运行时间
s32 xdata Task6_OverTime = 2*3000; //任务6运行超时时间
u32 xdata Task6_OverTime_Count=0; //任务6运行超时时间计数器
//bit Task6_OverTime_Reset = 0; //任务6运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

bit Task6_OnState = 1; //表示Task6输出ON状态 1：有输出 0；无输出
s32 xdata Task6_OnTime = 2*1;  //表示Task6输出ON状态的时间
s32 xdata Task6_OffTime = 2*1; //表示Task6输出OFF状态的时间

u32 xdata Task6_CountTime = 1;  //任务6 ON/OFF状态时间计数器

/******************************************************************************/
// 函数名称：Task_Input_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：对端口进行扫描，用于触发继电器任务
//		 说明：首先记录下所有被触发的输入型端口，当该端口
//					 被释放，则更新该端口所匹配的任务，同时清除
//					 端口记录
/******************************************************************************/
void Task_Input_Update(void)
{
	/*记录下所有被触发的端口*/
	/*如果端口模式是 1.输入模式
						并且为 2.自锁模式
									 3.端口被触发
			则记录*/
	if((Pin12_Mode==0)&&(Pin12_Trigger_Mode==0)&&(P12==0)){Pin12=1;}
	if((Pin13_Mode==0)&&(Pin13_Trigger_Mode==0)&&(P13==0)){Pin13=1;}
	if((Pin14_Mode==0)&&(Pin14_Trigger_Mode==0)&&(P14==0)){Pin14=1;}
	if((Pin15_Mode==0)&&(Pin15_Trigger_Mode==0)&&(P15==0)){Pin15=1;}
	if((Pin16_Mode==0)&&(Pin16_Trigger_Mode==0)&&(P16==0)){Pin16=1;}
	if((Pin17_Mode==0)&&(Pin17_Trigger_Mode==0)&&(P17==0)){Pin17=1;}
	
	if((Pin20_Mode==0)&&(Pin20_Trigger_Mode==0)&&(P20==0)){Pin20=1;}
	if((Pin21_Mode==0)&&(Pin21_Trigger_Mode==0)&&(P21==0)){Pin21=1;}
	if((Pin22_Mode==0)&&(Pin22_Trigger_Mode==0)&&(P22==0)){Pin22=1;}
	if((Pin23_Mode==0)&&(Pin23_Trigger_Mode==0)&&(P23==0)){Pin23=1;}
	if((Pin24_Mode==0)&&(Pin24_Trigger_Mode==0)&&(P24==0)){Pin24=1;}
	
	if((Pin35_Mode==0)&&(Pin35_Trigger_Mode==0)&&(P35==0)){Pin35=1;}
	if((Pin36_Mode==0)&&(Pin36_Trigger_Mode==0)&&(P36==0)){Pin36=1;}
	if((Pin37_Mode==0)&&(Pin37_Trigger_Mode==0)&&(P37==0)){Pin37=1;}
	
	
	/*自锁模式的更新*/
	/*每次只更新一个任务状态*/
  //对每一个记录的端口进行扫描执行任务号设置
	//假定现在有多个任务被记录
	//单个扫描周期只处理一个记录信号,并且此时端口被释放
	if((Pin12==1)&&(P12==1)){		
		/*更新任务号设置为Pin12触发任务号*/
		Task_Number = Pin12_Task_Number;  
		Pin12=0;   //复位端口触发状态
	}
  else if((Pin13==1)&&(P13==1)){   //松手检测
		Task_Number = Pin13_Task_Number;
		Pin13=0;   
	}
	else if((Pin14==1)&&(P14==1)){   //松手检测
		Task_Number = Pin14_Task_Number;
		Pin14=0;   
	}
	else if((Pin15==1)&&(P15==1)){   //松手检测
		Task_Number = Pin15_Task_Number;
		Pin15=0;   
	}
	else if((Pin16==1)&&(P16==1)){   //松手检测
		Task_Number = Pin16_Task_Number;
		Pin16=0;   
	}
	else if((Pin17==1)&&(P17==1)){  //松手检测
		Task_Number = Pin17_Task_Number;
		Pin17=0;   
	}
	else if((Pin20==1)&&(P20==1)){  //松手检测
		Task_Number = Pin20_Task_Number;
		Pin20=0;   
	}
	else if((Pin21==1)&&(P21==1)){   //松手检测
		Task_Number = Pin21_Task_Number;
		Pin21=0;   
	}
	else if((Pin22==1)&&(P22==1)){   //松手检测
		Task_Number = Pin22_Task_Number;
		Pin22=0;   
	}
	else if((Pin23==1)&&(P23==1)){   //松手检测
		Task_Number = Pin23_Task_Number;
		Pin23=0;   
	}
	else if((Pin24==1)&&(P24==1)){   //松手检测
		Task_Number = Pin24_Task_Number;
		Pin24=0;   
	}
	else if((Pin35==1)&&(P35==1)){   //松手检测
		Task_Number = Pin35_Task_Number;
		Pin35=0;   
	}
	else if((Pin36==1)&&(P36==1)){   //松手检测
		Task_Number = Pin36_Task_Number;
		Pin36=0;   
	}
	else if((Pin37==1)&&(P37==1)){   //松手检测
		Task_Number = Pin37_Task_Number;
		Pin37=0;   
	}
	
		
	/*如果端口模式是 1.输入模式
	            并且 2.立即触发模式
						  并且 3.外部模拟按键状态为未按下
						  并且 4.端口处于触发状态
						则更新任务号*/
	
	if((Pin12_Mode==0)&&(Pin12_Trigger_Mode==1)&&(Pin12_Key==0)&&(P12==0)){
		Task_Number_Immediate = Pin12_Task_Number; //立即更新任务号
		Pin12_Key = 1;   //外部虚拟按键状态变为按下		
	}
	else if((Pin13_Mode==0)&&(Pin13_Trigger_Mode==1)&&(Pin13_Key==0)&&(P13==0)){
		Task_Number_Immediate = Pin13_Task_Number;
		Pin13_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin14_Mode==0)&&(Pin14_Trigger_Mode==1)&&(Pin14_Key==0)&&(P14==0)){
		Task_Number_Immediate = Pin14_Task_Number;
		Pin14_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin15_Mode==0)&&(Pin15_Trigger_Mode==1)&&(Pin15_Key==0)&&(P15==0)){
		Task_Number_Immediate = Pin15_Task_Number;
		Pin15_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin16_Mode==0)&&(Pin16_Trigger_Mode==1)&&(Pin16_Key==0)&&(P16==0)){
		Task_Number_Immediate = Pin16_Task_Number;
		Pin16_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin17_Mode==0)&&(Pin17_Trigger_Mode==1)&&(Pin17_Key==0)&&(P17==0)){
		Task_Number_Immediate = Pin17_Task_Number;
		Pin17_Key = 1;   //外部虚拟按键状态变为按下
	}
	
	else if((Pin20_Mode==0)&&(Pin20_Trigger_Mode==1)&&(Pin20_Key==0)&&(P20==0)){
		Task_Number_Immediate = Pin20_Task_Number;
		Pin20_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin21_Mode==0)&&(Pin21_Trigger_Mode==1)&&(Pin21_Key==0)&&(P21==0)){
		Task_Number_Immediate = Pin21_Task_Number;
		Pin21_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin22_Mode==0)&&(Pin22_Trigger_Mode==1)&&(Pin22_Key==0)&&(P22==0)){
		Task_Number_Immediate = Pin22_Task_Number;
		Pin22_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin23_Mode==0)&&(Pin23_Trigger_Mode==1)&&(Pin23_Key==0)&&(P23==0)){
		Task_Number_Immediate = Pin23_Task_Number;
		Pin23_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin24_Mode==0)&&(Pin24_Trigger_Mode==1)&&(Pin24_Key==0)&&(P24==0)){
		Task_Number_Immediate = Pin24_Task_Number;
		Pin24_Key = 1;   //外部虚拟按键状态变为按下
	}
	
	else if((Pin35_Mode==0)&&(Pin35_Trigger_Mode==1)&&(Pin35_Key==0)&&(P35==0)){
		Task_Number_Immediate = Pin35_Task_Number;
		Pin35_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin36_Mode==0)&&(Pin36_Trigger_Mode==1)&&(Pin36_Key==0)&&(P36==0)){
		Task_Number_Immediate = Pin36_Task_Number;
		Pin36_Key = 1;   //外部虚拟按键状态变为按下
	}
	else if((Pin37_Mode==0)&&(Pin37_Trigger_Mode==1)&&(Pin37_Key==0)&&(P37==0)){
		Task_Number_Immediate = Pin37_Task_Number;
		Pin37_Key = 1;   //外部虚拟按键状态变为按下
	}
	
	
	//如果端口被释放，外部虚拟按键变为未按下，允许重新设置
	if((Pin12_Key==1)&&(P12==1)){Pin12_Key = 0;}
  if((Pin13_Key==1)&&(P13==1)){Pin13_Key = 0;}
  if((Pin14_Key==1)&&(P14==1)){Pin14_Key = 0;}
  if((Pin15_Key==1)&&(P15==1)){Pin15_Key = 0;}
  if((Pin16_Key==1)&&(P16==1)){Pin16_Key = 0;}
  if((Pin17_Key==1)&&(P17==1)){Pin17_Key = 0;} 

  if((Pin20_Key==1)&&(P20==1)){Pin20_Key = 0;}
  if((Pin21_Key==1)&&(P21==1)){Pin21_Key = 0;}
  if((Pin22_Key==1)&&(P22==1)){Pin22_Key = 0;}	
	if((Pin23_Key==1)&&(P23==1)){Pin23_Key = 0;}
	if((Pin24_Key==1)&&(P24==1)){Pin24_Key = 0;}
	
	if((Pin35_Key==1)&&(P35==1)){Pin35_Key = 0;}
	if((Pin36_Key==1)&&(P36==1)){Pin36_Key = 0;}
	if((Pin37_Key==1)&&(P37==1)){Pin37_Key = 0;}
	
	/*自锁模式更新新的触发任务*/
	switch(Task_Number)
	{
		case 1:   //任务1
			Task1=~Task1;  //开启或关闭任务1
			Task_Number = 0; //复位要更新的任务号
			break;
		case 2:   //任务2
			Task2=~Task2;  //开启或关闭任务2
			Task_Number = 0;
			break;
		case 3:   //任务3
			Task3=~Task3;  //开启或关闭任务3
			Task_Number = 0;
			break;
		case 4:   //任务4
			Task4=~Task4;  //开启或关闭任务4
			Task_Number = 0;
			break;
		case 5:   //任务5
			Task5=~Task5;  //开启或关闭任务5
			Task_Number = 0;
			break;
		case 6:   //任务6
			Task6=~Task6;  //开启或关闭任务6
			Task_Number = 0;
			break;
	}
	
	/*立即模式控制任务状态*/
	switch(Task_Number_Immediate)
	{
		case 1:   //任务1
			Task1=1;  //开启任务1
			Task_Number_Immediate = 0; //复位要更新的任务号
			break;
		case 2:   //任务2
			Task2=1;  //开启任务2
			Task_Number_Immediate = 0;
			break;
		case 3:   //任务3
			Task3=1;  //开启任务3
			Task_Number_Immediate = 0;
			break;
		case 4:   //任务4
			Task4=1;  //开启任务4
			Task_Number_Immediate = 0;
			break;
		case 5:   //任务5
			Task5=1;  //开启任务5
			Task_Number_Immediate = 0;
			break;
		case 6:   //任务6
			Task6=1;  //开启任务6
			Task_Number_Immediate = 0;
			break;
	
	}
}
/******************************************************************************/
// 函数名称：(Task1~Task6)_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：执行任务函数
/******************************************************************************/

void Task1_Output_Update(void)
{
		if(Task1 == 1)
		{
			switch(Task1_Mode)
			{
				case 1:
					if((Task1_StartTime<=NowTime)&&(NowTime<=Task1_EndTime)
						&&(Task1_OverTime_Count<Task1_OverTime)){ 
							Task1_OverTime_Count++;
						
							if(Task1_OnState==1) //首先如果处于On状态
								{
									
								if(Task1_CountTime<Task1_OnTime){
									Task1_CountTime++;
									Task1_Output = 1;
								}else{
									Task1_CountTime = 1;  //复位时间计数器
									Task1_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task1_CountTime<Task1_OffTime){
									Task1_CountTime++;
									Task1_Output = 0;
								}else{
									Task1_CountTime = 1;  //复位时间计数器
									Task1_OnState = 1; //切换到ON状态
								}
							}	
							
				  }else{  //不满足时间运行条件则不输出
								
								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时
						
						//如果任务一不在时间区间但还没有超时
						//重新回到时间区间将重新开始
						//默认输出ON
						if(Task1_OverTime_Count<Task1_OverTime){
							
							Task1_Output = 0;   //禁止任务1输出
							Task1_OverTime_Count=0;  //复位超时计数器
							Task1_CountTime = 1;  //复位时间计数器
							Task1_OnState = 1; //切换到ON状态
							
							//否则如果任务一已经超时
						}else if(Task1_OverTime_Count==Task1_OverTime){
							
							//使能超时任务自动复位,为了持续运行
							if(Task1_OverTime_Reset){
								
								Task1_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task1=0; //关闭Task
								Task1_OverTime_Count=0;  //复位超时计数器
								Task1_CountTime = 1;  //复位时间计数器
								Task1_OnState = 1; //切换到ON状态
								Task1_Output = 0;   //禁止任务1输出
								
							}
							
						}
						
					}
					break;
			}
		}else{  //任务如果不运行则不输出
			Task1_OverTime_Count=0;  //复位超时计数器
			Task1_CountTime = 1;  //复位时间计数器
			Task1_OnState = 1; //切换到ON状态
			Task1_Output = 0;   //禁止任务1输出
			
		}
		
/******************************************************************************/
// 任务一输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task1_Output==1){
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=1;}
	}
}

void Task2_Output_Update(void)
{
		if(Task2 == 1)
		{
			switch(Task2_Mode)
			{
				case 1:
					if((Task2_StartTime<=NowTime)&&(NowTime<=Task2_EndTime)
						&&(Task2_OverTime_Count<Task2_OverTime)){
							Task2_OverTime_Count++;
						
							if(Task2_OnState==1) //首先如果处于On状态
								{
									
								if(Task2_CountTime<Task2_OnTime){
									Task2_CountTime++;
									Task2_Output = 1;
								}else{
									Task2_CountTime = 1;  //复位时间计数器
									Task2_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task2_CountTime<Task2_OffTime){
									Task2_CountTime++;
									Task2_Output = 0;
								}else{
									Task2_CountTime = 1;  //复位时间计数器
									Task2_OnState = 1; //切换到ON状态
								}
							}	
							
			   }else{  //不满足时间运行条件则不输出

								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时					 
					 
					 //如果任务二不在时间区间但还没有超时
						if(Task2_OverTime_Count<Task2_OverTime){
							
							Task2_OverTime_Count=0;  //复位超时计数器
							Task2_CountTime = 1;  //复位时间计数器
							Task2_Output = 0;   //禁止任务2输出
							Task2_OnState = 1; //切换到ON状态
							
							//否则如果任务一已经超时
						}else if(Task2_OverTime_Count==Task2_OverTime){
							
							//使能超时任务自动复位
							if(Task2_OverTime_Reset){
								
								Task2_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task2=0; //关闭Task
								Task2_OverTime_Count=0;  //复位超时计数器
								Task2_CountTime = 1;  //复位时间计数器
								Task2_Output = 0;   //禁止任务2输出
								Task2_OnState = 1; //切换到ON状态
							}
							
						}
				 }
				 break;
		  }
		}else{
			Task2_OverTime_Count=0;  //复位超时计数器
			Task2_CountTime = 1;  //复位时间计数器
			Task2_Output = 0;   //禁止任务2输出
			Task2_OnState = 1; //切换到ON状态
		}
		
/******************************************************************************/
// 任务二输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task2_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=1;}
	}		
}


void Task3_Output_Update(void)
{
		if(Task3 == 1)
		{
			switch(Task3_Mode)
			{
				case 1:
					if((Task3_StartTime<=NowTime)&&(NowTime<=Task3_EndTime)
						&&(Task3_OverTime_Count<Task3_OverTime)){ 
							Task3_OverTime_Count++;
						
							if(Task3_OnState==1) //首先如果处于On状态
								{
									
								if(Task3_CountTime<Task3_OnTime){
									Task3_CountTime++;
									Task3_Output = 1;
								}else{
									Task3_CountTime = 1;  //复位时间计数器
									Task3_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task3_CountTime<Task3_OffTime){
									Task3_CountTime++;
									Task3_Output = 0;
								}else{
									Task3_CountTime = 1;  //复位时间计数器
									Task3_OnState = 1; //切换到ON状态
								}
							}	
							
				  }else{  //不满足时间运行条件则不输出
								
								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时
						
						//如果任务三不在时间区间但还没有超时
						if(Task3_OverTime_Count<Task3_OverTime){
							
							Task3_OverTime_Count=0;  //复位超时计数器
							Task3_CountTime = 1;  //复位时间计数器
							Task3_Output = 0;   //禁止任务3输出
							Task3_OnState = 1; //切换到ON状态
							
							//否则如果任务三已经超时
						}else if(Task3_OverTime_Count==Task3_OverTime){
							
							//使能超时任务自动复位
							if(Task3_OverTime_Reset){
								
								Task3_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task3=0; //关闭Task
								Task3_OverTime_Count=0;  //复位超时计数器
								Task3_CountTime = 1;  //复位时间计数器
								Task3_Output = 0;   //禁止任务3输出
								Task3_OnState = 1; //切换到ON状态
							}
							
						}  
					}
					break;
			}
		}else{  //任务如果不运行则不输出
			Task3_OverTime_Count=0;  //复位超时计数器
			Task3_CountTime = 1;  //复位时间计数器
			Task3_Output = 0;   //禁止任务3输出
			Task3_OnState = 1; //切换到ON状态
		}
		
/******************************************************************************/
// 任务三输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task3_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=1;}
	}	
}

void Task4_Output_Update(void)
{
		if(Task4 == 1)
		{
			switch(Task4_Mode)
			{
				case 1:
					if((Task4_StartTime<=NowTime)&&(NowTime<=Task4_EndTime)
						&&(Task4_OverTime_Count<Task4_OverTime)){ 
							Task4_OverTime_Count++;
						
							if(Task4_OnState==1) //首先如果处于On状态
								{
									
								if(Task4_CountTime<Task4_OnTime){
									Task4_CountTime++;
									Task4_Output = 1;
								}else{
									Task4_CountTime = 1;  //复位时间计数器
									Task4_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task4_CountTime<Task4_OffTime){
									Task4_CountTime++;
									Task4_Output = 0;
								}else{
									Task4_CountTime = 1;  //复位时间计数器
									Task4_OnState = 1; //切换到ON状态
								}
							}	
							
				  }else{  //不满足时间运行条件则不输出
								
								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时
						
						//如果任务四不在时间区间但还没有超时
						if(Task4_OverTime_Count<Task4_OverTime){
							
							Task4_OverTime_Count=0;  //复位超时计数器
							Task4_CountTime = 1;  //复位时间计数器
							Task4_Output = 0;   //禁止任务4输出
							Task4_OnState = 1; //切换到ON状态
							
							//否则如果任务四已经超时
						}else if(Task4_OverTime_Count==Task4_OverTime){
							
							//使能超时任务自动复位
							if(Task4_OverTime_Reset){
								
								Task4_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task4=0; //关闭Task
								Task4_OverTime_Count=0;  //复位超时计数器
								Task4_CountTime = 1;  //复位时间计数器
								Task4_Output = 0;   //禁止任务4输出
								Task4_OnState = 1; //切换到ON状态
							}
							
						}
	
					}
					break;
			}
		}else{  //任务如果不运行则不输出
			Task4_OverTime_Count=0;  //复位超时计数器
			Task4_CountTime = 1;  //复位时间计数器
			Task4_Output = 0;   //禁止任务4输出
			Task4_OnState = 1; //切换到ON状态
		}
		
/******************************************************************************/
// 任务四输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task4_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=1;}
	}	
}


void Task5_Output_Update(void)
{
		if(Task5 == 1)
		{
			switch(Task5_Mode)
			{
				case 1:
					if((Task5_StartTime<=NowTime)&&(NowTime<=Task5_EndTime)
						&&(Task5_OverTime_Count<Task5_OverTime)){
							Task5_OverTime_Count++;
						
							if(Task5_OnState==1) //首先如果处于On状态
								{
									
								if(Task5_CountTime<Task5_OnTime){
									Task5_CountTime++;
									Task5_Output = 1;
								}else{
									Task5_CountTime = 1;  //复位时间计数器
									Task5_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task5_CountTime<Task5_OffTime){
									Task5_CountTime++;
									Task5_Output = 0;
								}else{
									Task5_CountTime = 1;  //复位时间计数器
									Task5_OnState = 1; //切换到ON状态
								}
							}	
							
			   }else{   //不满足时间运行条件则不输出
								
								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时
					 
					 //如果任务五不在时间区间但还没有超时
						if(Task5_OverTime_Count<Task5_OverTime){
							
							Task5_OverTime_Count=0;  //复位超时计数器
							Task5_CountTime = 1;  //复位时间计数器
							Task5_Output = 0;   //禁止任务5输出
							Task5_OnState = 1; //切换到ON状态
							
							//否则如果任务五已经超时
						}else if(Task5_OverTime_Count==Task5_OverTime){
							
							//使能超时任务自动复位
							if(Task5_OverTime_Reset){
								
								Task5_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task5=0; //关闭Task
								Task5_OverTime_Count=0;  //复位超时计数器
								Task5_CountTime = 1;  //复位时间计数器
								Task5_Output = 0;   //禁止任务5输出
								Task5_OnState = 1; //切换到ON状态
							}
							
						}
				 }
				 break;
		  }
		}else{   //任务如果不运行则不输出
			Task5_OverTime_Count=0;  //复位超时计数器
			Task5_CountTime = 1;  //复位时间计数器
			Task5_Output = 0;   //禁止任务5输出
			Task5_OnState = 1; //切换到ON状态
		}
		
/******************************************************************************/
// 任务五输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task5_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==5)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==5)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==5)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==5)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==5)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==5)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==5)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==5)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==5)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==5)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==5)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==5)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==5)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==5)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==5)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==5)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==5)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==5)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==5)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==5)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==5)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==5)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==5)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==5)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==5)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==5)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==5)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==5)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==5)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==5)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==5)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==5)){P37=1;}
	}		
}

void Task6_Output_Update(void)
{
		if(Task6 == 1)
		{
			switch(Task6_Mode)
			{
				case 1:
					if((Task6_StartTime<=NowTime)&&(NowTime<=Task6_EndTime)
						&&(Task5_OverTime_Count<Task5_OverTime)){
							Task5_OverTime_Count++;
						
							if(Task6_OnState==1) //首先如果处于On状态
								{
									
								if(Task6_CountTime<Task6_OnTime){
									Task6_CountTime++;
									Task6_Output = 1;
								}else{
									Task6_CountTime = 1;  //复位时间计数器
									Task6_OnState = 0; //切换到OFF状态
								}
								
							}else{  //否则处于Off状态
								
								if(Task6_CountTime<Task6_OffTime){
									Task6_CountTime++;
									Task6_Output = 0;
								}else{
									Task6_CountTime = 1;  //复位时间计数器
									Task6_OnState = 1; //切换到ON状态
								}
							}	
							
			   }else{    //不满足时间运行条件则不输出
								
								  //在时间区间但是任务超时 
						      //不在时间区间，任务还未超时
									//不在时间区间，任务已经超时
					 
					 //如果任务六不在时间区间但还没有超时
						if(Task6_OverTime_Count<Task6_OverTime){
							
							Task6_OverTime_Count=0;  //复位超时计数器
							Task6_CountTime = 1;  //复位时间计数器
							Task6_Output = 0;   //禁止任务6输出
							Task6_OnState = 1; //切换到ON状态
							
							//否则如果任务六已经超时
						}else if(Task6_OverTime_Count==Task6_OverTime){
							
							//使能超时任务自动复位
							if(Task6_OverTime_Reset){
								
								Task6_OverTime_Count=0;  //复位超时计数器
																				 //如果还在时间区间内将继续运行
																				 //如果不在时间区间内将等待继续运行
							}else{  
								
								Task6=0; //关闭Task
								Task6_OverTime_Count=0;  //复位超时计数器
								Task6_CountTime = 1;  //复位时间计数器
								Task6_Output = 0;   //禁止任务6输出
								Task6_OnState = 1; //切换到ON状态
							}
							
						}
				 }
				 break;
		  }
		}else{    //任务如果不运行则不输出
			Task6_OverTime_Count=0;  //复位超时计数器
			Task6_CountTime = 1;  //复位时间计数器
			Task6_Output = 0;   //禁止任务6输出
			Task6_OnState = 1; //切换到ON状态
		}
		
/******************************************************************************/
// 任务六输出处理部分（以此注释向下）
/******************************************************************************/
	if(Task6_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==6)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==6)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==6)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==6)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==6)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==6)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==6)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==6)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==6)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==6)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==6)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==6)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==6)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==6)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==6)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==6)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==6)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==6)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==6)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==6)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==6)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==6)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==6)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==6)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==6)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==6)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==6)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==6)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==6)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==6)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==6)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==6)){P37=1;}
	}		
}

/******************************************************************************/
// 函数名称：Task_Output_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：对任务输出进行扫描，用于触发继电器任务
/******************************************************************************/
/*
void Task1_Output_Update(void)
{
	if(Task1_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=1;}
	}
	
	
}

*/

/*
void Task2_Output_Update(void)
{
	if(Task2_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=1;}
	}

}	

*/

/*
void Task3_Output_Update(void)
{
	if(Task3_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=1;}
	}

}

*/

/*
void Task4_Output_Update(void)
{
	if(Task4_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=1;}
	}

}
*/






