/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "Config.h"
#include "LCD1602.h"
#include "LCD1602_Clock.h"
#include "LCD1602_Menu.h"
#include "LCD1602_Show.h"
#include "Timer.h"
#include "hSch51.h"
#include "Download.h"
#include "Relay.h"
#include "EEPROM.h"
#include "EEPROM_Application.h"
#include "EC11.h"
#include "Buzzer.h"
#include "UART.h"
#include "ESP8266.h"

/******************************************************************************/
// 定义变量
/******************************************************************************/


/******************************************************************************/
// main函数
/******************************************************************************/
int main(void)
{	
	/*初始化函数*/	
	
	P4SW = 0x20;   // 0010 0000
	P4M1=0xDF;  // 1101 1111
	P4M0=0x20;  // 0010 0000
	
	EEPROM_Read_Sector_1();
	Lcd1602_Init();
	EC11_Init();
	Timer1Init();
	Buzzer_Init();
	UartInit();  //初始化选择独立波特率发生器,启用串口中断
	
	hSCH_Start(); // 启动调度程序（开启总中断）
	
	Esp8266_STA_AP_Mode();  
	
	Lcd1602_Write_Cmd(0x01);//显示清屏
	
	hSCH_Init_T0(); //设置调度程序,初始化调度器，设置定时器0
									//为16位手动重装模式，定时1ms作为调度器时标
	
	hSCH_Pause();  //禁用用作为调度器时基的T2中断
	
	
	/*添加调度器任务*/
	hSCH_Add_Task(EC11_Scan,  0, 5 ,0);
	
	hSCH_Add_Task(LCD1602_Show_Update,  5, 100 ,1);
	hSCH_Add_Task(LCD1602_Time_Update, 40, 991 ,0);

  hSCH_Add_Task(Task_Input_Update,   51, 49 ,0);
	hSCH_Add_Task(Task1_Output_Update, 52, 49 ,0);
	hSCH_Add_Task(Task2_Output_Update, 53, 49 ,0);
	hSCH_Add_Task(Task3_Output_Update, 54, 49 ,0);
	
	hSCH_Add_Task(Task4_Output_Update, 55, 49 ,0);
	hSCH_Add_Task(Task5_Output_Update, 56, 49 ,0);
	hSCH_Add_Task(Task6_Output_Update, 57, 49 ,0);

//	hSCH_Add_Task(Buzzer_Open,  55, 500 ,1);
	
  hSCH_Run();  //启用作为调度器时基的T2中断
	
	
	
	/*主循环*/
	while(1)
	{
		hSCH_Dispatch_Tasks();
  }
}
