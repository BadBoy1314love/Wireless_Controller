/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "config.h"
#include "LCD1602.h"
#include "LCD1602_Menu.h"
#include "ESP8266.h"
#include "EEPROM_Application.h"

/******************************************************************************/
// 变量初始化
/******************************************************************************/
u8 Menu_Index = 0;   //菜单索引号
u8 Menu_Flag = 0;    //菜单标志位
                     //0:EC11旋转切换条目，按键按下菜单级别转移
										 //1:EC11旋转切换条目，按键按下为返回执行返回操作，即退出菜单(第一级RETURN)
										 //2:EC11旋转切换条目，按键按下更新任务状态
										 //3:EC11旋转切换条目，按键按下进入第一个编辑位
										 //4:EC11旋转修改值，按键按下切换编辑位
u8 Menu_Edit_Tips = 0; //编辑提示控制变量，计数函数进入的次数，
											 //改变编辑提示控制位
bit Menu_Edit_Show = 0;  //编辑提示控制位，判断此位，显示或者不显示
u8 Menu_Edit = 0;  //编辑显示位,通过此变量来确定当前页面的显示位
                   //0:为菜单条目，不闪烁编辑位
									 //1:为编辑位1号，闪烁此编辑位
									 //2:为编辑为2号，闪烁此编辑位
									 //3:...
s8 Menu_Edit_Value = 0;  //菜单编辑位当前值

bit isReset = 0;  //系统复位控制位  0：此时为非复位 1：此时为复位

/*显示用指针*/
u8 *LCD1602_First_Line;  //1602第一行的显示，填充第一行
u8 *LCD1602_Second_Line;  //1602第二行的显示，填充第二行
u8 *LCD1602_First_Line_16; //1602第一行第16位的显示
u8 *LCD1602_First_Line_6; //1602第一行第6位的显示


//菜单字符指针
/*第一级菜单*/
u8 code Menu_TASKS_CTRL_Select[] =">> TASKS CTRL <<";
u8 code Menu_TASKS_SET_Select[]  =">> TASKS SET  <<";
u8 code Menu_PORT_SET_Select[]   =">>  PORT SET  <<";
u8 code Menu_TIME_SET_Select[]   =">>  TIME SET  <<";
u8 code Menu_WIFI_SET_Select[]   =">>  WIFI SET  <<";
u8 code RETURN_Select[]          =">>   RETURN   <<";

u8 code Menu_TASKS_CTRL[] ="   TASKS CTRL   ";
u8 code Menu_TASKS_SET[]  ="   TASKS SET    ";
u8 code Menu_PORT_SET[]   ="    PORT SET    ";
u8 code Menu_TIME_SET[]   ="    TIME SET    ";
u8 code Menu_WIFI_SET[]   ="    WIFI SET    ";
u8 code RETURN[]          ="     RETURN     ";
//补充菜单条目
u8 code SYSTEM_RESET_Select[]=">> SYS RESET  <<";
u8 code SYSTEM_RESET[]       ="   SYS RESET    ";
u8 code SYSTEM_RESET_ASK[]   ="SYSTEM RESET ???";
u8 code SYSTEM_RESET_YES[]   =">> YES <<  NO   ";
u8 code SYSTEM_RESET_NO[]    ="   YES  >> NO <<";
/*第二级菜单*/
//TASKS_CTRL_1_0下项目

//TASK1_CTRL
u8 code Menu_TASK1_CTRL_Run_Select[]  =">>  RUN TASK1 <<";
u8 code Menu_TASK1_CTRL_Run[]         ="    RUN TASK1   ";
u8 code Menu_TASK1_CTRL_Stop_Select[] =">> STOP TASK1 <<";
u8 code Menu_TASK1_CTRL_Stop[]        ="   STOP TASK1   ";

//TASK2_CTRL
u8 code Menu_TASK2_CTRL_Run_Select[]  =">>  RUN TASK2 <<";
u8 code Menu_TASK2_CTRL_Run[]         ="    RUN TASK2   ";
u8 code Menu_TASK2_CTRL_Stop_Select[] =">> STOP TASK2 <<";
u8 code Menu_TASK2_CTRL_Stop[]        ="   STOP TASK2   ";

//TASK3_CTRL
u8 code Menu_TASK3_CTRL_Run_Select[]  =">>  RUN TASK3 <<";
u8 code Menu_TASK3_CTRL_Run[]         ="    RUN TASK3   ";
u8 code Menu_TASK3_CTRL_Stop_Select[] =">> STOP TASK3 <<";
u8 code Menu_TASK3_CTRL_Stop[]        ="   STOP TASK3   ";

//TASK4_CTRL
u8 code Menu_TASK4_CTRL_Run_Select[]  =">>  RUN TASK4 <<";
u8 code Menu_TASK4_CTRL_Run[]         ="    RUN TASK4   ";
u8 code Menu_TASK4_CTRL_Stop_Select[] =">> STOP TASK4 <<";
u8 code Menu_TASK4_CTRL_Stop[]        ="   STOP TASK4   ";

//TASK5_CTRL
u8 code Menu_TASK5_CTRL_Run_Select[]  =">>  RUN TASK5 <<";
u8 code Menu_TASK5_CTRL_Run[]         ="    RUN TASK5   ";
u8 code Menu_TASK5_CTRL_Stop_Select[] =">> STOP TASK5 <<";
u8 code Menu_TASK5_CTRL_Stop[]        ="   STOP TASK5   ";

//TASK6_CTRL
u8 code Menu_TASK6_CTRL_Run_Select[]  =">>  RUN TASK6 <<";
u8 code Menu_TASK6_CTRL_Run[]         ="    RUN TASK6   ";
u8 code Menu_TASK6_CTRL_Stop_Select[] =">> STOP TASK6 <<";
u8 code Menu_TASK6_CTRL_Stop[]        ="   STOP TASK6   ";

u8 code Menu_Empty_Line[]             ="                ";

/*第二级菜单*/
//TASKS_SET_1_1下项目

u8 code Menu_TASK1_SET_Select[]   =">> TASK1 SET  <<";
u8 code Menu_TASK2_SET_Select[]   =">> TASK2 SET  <<";
u8 code Menu_TASK3_SET_Select[]   =">> TASK3 SET  <<";
u8 code Menu_TASK4_SET_Select[]   =">> TASK4 SET  <<";
u8 code Menu_TASK5_SET_Select[]   =">> TASK5 SET  <<";
u8 code Menu_TASK6_SET_Select[]   =">> TASK6 SET  <<";

u8 code Menu_TASK1_SET[]   ="   TASK1 SET    ";
u8 code Menu_TASK2_SET[]   ="   TASK2 SET    ";
u8 code Menu_TASK3_SET[]   ="   TASK3 SET    ";
u8 code Menu_TASK4_SET[]   ="   TASK4 SET    ";
u8 code Menu_TASK5_SET[]   ="   TASK5 SET    ";
u8 code Menu_TASK6_SET[]   ="   TASK6 SET    ";

//PORT_SET_1_2下项目

//对所有端口
u8 code Trigger_Mode_0[]="  TRIGGER MODE:0"; 
u8 code Trigger_Mode_1[]="  TRIGGER MODE:1";
u8 code Trigger_Mode_Empty[]="  TRIGGER MODE: ";
u8 code Empty_Number[] = " ";

//PIN(10-17,20-24,35-37) SET
u8 xdata PIN_SET_Input[]  =">>PIN  -->TASK:";
u8 xdata PIN_SET_Output[] =">>PIN  <--TASK:";
u8 xdata PIN_SET_Empty[]  =">>PIN     TASK:";

//TIME_SET_1_3下项目
u8 xdata SET_DATE[]  ="DATE:2022/07/17 ";
u8 xdata SET_TIME[]  ="TIME: 00:00:00  ";

u8 code SET_TIME_MANUAL[]        ="   MANUAL SET   ";
u8 code SET_TIME_MANUAL_Select[] =">> MANUAL SET <<";

u8 code SET_TIME_AUTO[]        ="    AUTO SET    ";
u8 code SET_TIME_AUTO_Select[] =">>  AUTO SET  <<";

/*第二级菜单*/
//WIFI_SET_1_4下项目
u8 code TCP_PORT_SET_Select[]=">>  TCP PORT  <<";
u8 code TCP_PORT_SET[]       ="    TCP PORT    ";
u8 code TCP_SERVER_PORT[]   ="TCP SERVER PORT:";
u8 xdata TCP_PORT_Number[]   ="-->  65535   <--";

u8 code STA_IP_Select[] =">>   STA IP   <<";
u8 code STA_IP[]        ="     STA IP     ";
u8 code STA_IP_ADDRESS[]="STA IP ADDRESS: ";

u8 code AP_IP_Select[] =">>    AP IP   <<";
u8 code AP_IP[]        ="      AP IP     ";
u8 code AP_IP_ADDRESS[]="AP IP ADDRESS:  ";

/*第三级菜单*/
//TASK_SET下项目（TASK1-TASK1复用）
u8 xdata TASK_StartTime[]="TASK  StartTime:"; 
u8 xdata TASK_EndTime[]  ="TASK    EndTime:";
u8 xdata TASK_OverTime[] ="TASK   OverTime:";
u8 code TASK_OverTime_AutoReset_ON[]  ="AutoReset--->ON ";
u8 code TASK_OverTime_AutoReset_OFF[] ="AutoReset--->OFF";
u8 code TASK_OverTime_AutoReset_Empty[] ="AutoReset--->   ";
u8 xdata TASK_OnTime[]   ="TASK     OnTime:";
u8 xdata TASK_OffTime[]  ="TASK    OffTime:";
u8 xdata Time_Minute[]   ="   00:00        ";
u8 xdata Time_100MS[]    =" 0000:00:00:00  ";

u8 xdata TASK_SET_Number =0;


/*任务号的显示数据*/
u8 idata Pin10_Number[1] = {0};
u8 idata Pin11_Number[1] = {0};
u8 idata Pin12_Number[1] = {0};
u8 idata Pin13_Number[1] = {0};
u8 idata Pin14_Number[1] = {0};
u8 idata Pin15_Number[1] = {0};
u8 idata Pin16_Number[1] = {0};
u8 idata Pin17_Number[1] = {0};

u8 idata Pin20_Number[1] = {0};
u8 idata Pin21_Number[1] = {0};
u8 idata Pin22_Number[1] = {0};
u8 idata Pin23_Number[1] = {0};
u8 idata Pin24_Number[1] = {0};

u8 idata Pin35_Number[1] = {0};
u8 idata Pin36_Number[1] = {0};
u8 idata Pin37_Number[1] = {0};

extern u8 EC11_State;   //引用EC11的状态
extern s8 EC11_Value;   //引用EC11的表示值

extern u8 LCD1602_Show_State;

/*引用任务控制位*/
extern bit Task1;
extern bit Task2;
extern bit Task3;
extern bit Task4;
extern bit Task5;
extern bit Task6;

/*输入模式时作为端口触发更新任务号*/ 
/*输出模式时选择关联任务号*/
/*端口模式（0为输入模式）（1为输出模式）*/
extern s8 xdata Pin10_Task_Number;	extern bit Pin10_Mode;
extern s8 xdata Pin11_Task_Number;	extern bit Pin11_Mode;

extern s8 xdata Pin12_Task_Number;  extern bit Pin12_Mode; 
extern s8 xdata Pin13_Task_Number;	extern bit Pin13_Mode;
extern s8 xdata Pin14_Task_Number;	extern bit Pin14_Mode;
extern s8 xdata Pin15_Task_Number;	extern bit Pin15_Mode;
extern s8 xdata Pin16_Task_Number;	extern bit Pin16_Mode;
extern s8 xdata Pin17_Task_Number;	extern bit Pin17_Mode;

extern s8 xdata Pin20_Task_Number;	extern bit Pin20_Mode;
extern s8 xdata Pin21_Task_Number;	extern bit Pin21_Mode;
extern s8 xdata Pin22_Task_Number;  extern bit Pin22_Mode;
extern s8 xdata Pin23_Task_Number;	extern bit Pin23_Mode;
extern s8 xdata Pin24_Task_Number;  extern bit Pin24_Mode;

extern s8 xdata Pin35_Task_Number;  extern bit Pin35_Mode;
extern s8 xdata Pin36_Task_Number;	extern bit Pin36_Mode;
extern s8 xdata Pin37_Task_Number;	extern bit Pin37_Mode;

/*端口的触发模式*/
/*触发模式（0为自锁模式）（1为立即模式）*/
//自锁模式：按键按下，释放才会更新任务状态
//立即模式：按键按下，立刻更新任务状态，按键释放才可重新更新
extern bit Pin10_Trigger_Mode;
extern bit Pin11_Trigger_Mode;

extern bit Pin12_Trigger_Mode;
extern bit Pin13_Trigger_Mode;
extern bit Pin14_Trigger_Mode;
extern bit Pin15_Trigger_Mode;
extern bit Pin16_Trigger_Mode;
extern bit Pin17_Trigger_Mode;

extern bit Pin20_Trigger_Mode;
extern bit Pin21_Trigger_Mode;
extern bit Pin22_Trigger_Mode;
extern bit Pin23_Trigger_Mode;
extern bit Pin24_Trigger_Mode;

extern bit Pin35_Trigger_Mode;
extern bit Pin36_Trigger_Mode;
extern bit Pin37_Trigger_Mode;

extern s8 hour,minute,second;
extern s16 Year;
extern s8 Month;
extern s8 Day;
extern u8 xdata Max_Month_Days[];

extern u8 xdata ESP8266_Return_Value;

//TCP服务器端口
extern s32 xdata TcpServerPort;
/*设置TCP服务器信息*/
extern u8 xdata ATCIPSERVER[]; //="AT+CIPSERVER=1,65535";

extern u8 xdata STAIPTable[];
extern u8 xdata APIPTable[];

/*时间区间间歇模式*/

/*任务一*/
extern s16 xdata Task1_StartTime;//任务1起始运行时间
extern s16 xdata Task1_EndTime;//任务1结束运行时间
extern s32 xdata Task1_OverTime; //任务1运行超时时间
extern bit Task1_OverTime_Reset; //任务1运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task1_OnTime;  //表示Task1输出ON状态的时间
extern s32 xdata Task1_OffTime; //表示Task1输出OFF状态的时间

/*任务二*/
extern s16 xdata Task2_StartTime;//任务2起始运行时间
extern s16 xdata Task2_EndTime;//任务2结束运行时间
extern s32 xdata Task2_OverTime; //任务2运行超时时间
extern bit Task2_OverTime_Reset; //任务2运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task2_OnTime;  //表示Task2输出ON状态的时间
extern s32 xdata Task2_OffTime; //表示Task2输出OFF状态的时间


/*任务三*/
extern s16 xdata Task3_StartTime;//任务3起始运行时间
extern s16 xdata Task3_EndTime;//任务3结束运行时间
extern s32 xdata Task3_OverTime; //任务3运行超时时间
extern bit Task3_OverTime_Reset; //任务3运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task3_OnTime;  //表示Task3输出ON状态的时间
extern s32 xdata Task3_OffTime; //表示Task3输出OFF状态的时间


/*任务四*/
extern s16 xdata Task4_StartTime;//任务4起始运行时间
extern s16 xdata Task4_EndTime;//任务4结束运行时间
extern s32 xdata Task4_OverTime; //任务4运行超时时间
extern bit Task4_OverTime_Reset; //任务4运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task4_OnTime;  //表示Task4输出ON状态的时间
extern s32 xdata Task4_OffTime; //表示Task4输出OFF状态的时间

/*任务五*/
extern s16 xdata Task5_StartTime;//任务5起始运行时间
extern s16 xdata Task5_EndTime;//任务5结束运行时间
extern s32 xdata Task5_OverTime; //任务5运行超时时间
extern bit Task5_OverTime_Reset; //任务5运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task5_OnTime;  //表示Task5输出ON状态的时间
extern s32 xdata Task5_OffTime; //表示Task5输出OFF状态的时间

/*任务六*/
extern s16 xdata Task6_StartTime;//任务6起始运行时间
extern s16 xdata Task6_EndTime;//任务6结束运行时间
extern s32 xdata Task6_OverTime; //任务6运行超时时间
extern bit Task6_OverTime_Reset; //任务6运行超时自动复位控制位
                              //用于控制任务是否永久运行
															//1:自动复位 ，任务超时将复位超时计数，任务永久运行
															//0:不自动复位 任务超时将关闭

extern s32 xdata Task6_OnTime;  //表示Task6输出ON状态的时间
extern s32 xdata Task6_OffTime; //表示Task6输出OFF状态的时间


extern u8 xdata STA_MODE_Table[150]; //={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\"\r\n        "};
extern u8 xdata AP_MODE_Table[150]; //={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4\r\n      "};
extern uint8 xdata rcvTable[200];
extern u8 xdata apTable[16];

/*执行当前菜单索引号下的具体操作函数*/
void (*current_operation_index)();   //设定显示状态以及对参数进行操作

/******************************************************************************/
// LCD1602菜单索引表
/******************************************************************************/
Menu_table code table[52]=
{
	/*第一级菜单*/
	{0,5,1,6,(*TASKS_CTRL_1_0)},
	{1,0,2,13, (*TASKS_SET_1_1)},
	{2,1,3,20,  (*PORT_SET_1_2)},
	{3,2,4,37,  (*TIME_SET_1_3)},
	{4,3,51,40,  (*WIFI_SET_1_4)},
	{5,51,0,5,    (*RETURN_1_5)},
	
	/*第二级菜单*/
	//TASKS_CTRL_1_0下项目
	{6,12,7,6,   (*TASK1_CTRL_2_6)},
	{7,6,8,7,    (*TASK2_CTRL_2_7)},
	{8,7,9,8,    (*TASK3_CTRL_2_8)},
	{9,8,10,9,   (*TASK4_CTRL_2_9)},
	{10,9,11,10, (*TASK5_CTRL_2_10)},
	{11,10,12,11,(*TASK6_CTRL_2_11)},
	{12,11,6,0,      (*RETURN_2_12)},
	
	/*第二级菜单*/
	//TASKS_SET_1_1下项目
	{13,19,14,44, (*TASK1_SET_2_13)},
	{14,13,15,44, (*TASK2_SET_2_14)},
	{15,14,16,44, (*TASK3_SET_2_15)},
	{16,15,17,44, (*TASK4_SET_2_16)},
	{17,16,18,44, (*TASK5_SET_2_17)},
	{18,17,19,44, (*TASK6_SET_2_18)},
	{19,18,13,1,  (*RETURN_2_19)},
	
	/*第二级菜单*/
  //PORT_SET_1_2下项目
	{20,36,21,20, (*PIN10_SET_2_20)},
	{21,20,22,21, (*PIN11_SET_2_21)},
	{22,21,23,22, (*PIN12_SET_2_22)},
	{23,22,24,23, (*PIN13_SET_2_23)},
	{24,23,25,24, (*PIN14_SET_2_24)},
	{25,24,26,25, (*PIN15_SET_2_25)},
	{26,25,27,26, (*PIN16_SET_2_26)},
	{27,26,28,27, (*PIN17_SET_2_27)},
	
	{28,27,29,28, (*PIN20_SET_2_28)},
	{29,28,30,29, (*PIN21_SET_2_29)},
	{30,29,31,30, (*PIN22_SET_2_30)},
	{31,30,32,31, (*PIN23_SET_2_31)},
	{32,31,33,32, (*PIN24_SET_2_32)},
	
	{33,32,34,33, (*PIN35_SET_2_33)},
	{34,33,35,34, (*PIN36_SET_2_34)},
	{35,34,36,35, (*PIN37_SET_2_35)},
	
	{36,35,20,2, (*RETURN_2_36)},
	
	/*第二级菜单*/
  //TIME_SET_1_3下项目
	{37,39,38,37,(*TIME_SET_Manual_Set_2_37)},
	{38,37,39,38,(*TIME_SET_Auto_Set_2_38)},
	{39,38,37,3,(*RETURN_2_39)},

	/*第二级菜单*/
  //WIFI_SET_1_4下项目
	{40,43,41,40,(*TCP_PORT_SET_2_40)},
	{41,40,42,41,(*STA_IP_2_41)},
	{42,41,43,42,(*AP_IP_2_42)},
	{43,42,40,4,(*RETURN_2_43)},

	/*第三级菜单*/
  //TASK_SET下项目（TASK1-TASK1复用）
	{44,50,45,44,(*TASK_StartTime_SET_3_44)},
	{45,44,46,45,(*TASK_EndTime_SET_3_45)},
	{46,45,47,46,(*TASK_OverTime_SET_3_46)},
	{47,46,48,47,(*TASK_OverTime_MODE_SET_3_47)},
	{48,47,49,48,(*TASK_OnTime_SET_3_48)},
	{49,48,50,49,(*TASK_OffTime_SET_3_49)},
	{50,49,44,50,(*RETURN_3_50)},
	
	//补充菜单条目
	{51,4,5,51,(*SYSTEM_RESET_1_51)},
	
};

/******************************************************************************/
// LCD1602菜单显示函数
// 函数名称：Lcd1602_Menu
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602显示菜单
/******************************************************************************/
void LCD1602_Menu_Update()
{
	
	//编辑位的闪烁
	if(++Menu_Edit_Tips==4)
	{
		Menu_Edit_Tips=0;  //复位显示控制变量
	  Menu_Edit_Show=~Menu_Edit_Show;  //切换显示状态
	}
	
	/*响应EC11状态并复位EC11状态*/
	/*并更新菜单索引号*/
	switch(EC11_State)  
	{
		case 1:  //EC11为逆时针旋转状态
			switch(Menu_Flag)
			{
				case 0:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 1:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 2:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 3:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 4:
					
					break;
				case 5:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
			}
		  
		  EC11_State = 0; //复位EC11状态
		  break;
		case 2:  //EC11为顺时针旋转状态
			switch(Menu_Flag)
			{
				case 0:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 1:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 2:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 3:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 4:
					
					break;
				case 5:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
			}
	
			
		  EC11_State = 0; //复位EC11状态
		  break;
		case 3:  //EC11为按键按下的状态
			
			//Menu_Flag确定当前的EC11的操作行为
			switch(Menu_Flag)
			{
				case 0:  //处于菜单条目切换状态，单击进入下一级菜单
					
					if(Menu_Index==19||Menu_Index==36||Menu_Index==43){
						EA=0;  //编程前关闭总中断
						EEPROM_Program_Sector_1();
						EA=1;  //编程后开启总中断
					}
				
					Menu_Index = table[Menu_Index].Enter_Index;
					break;
				case 1:  //处于返回状态，单击退出菜单
					//通过索引号执行指定内容
					switch(Menu_Index)
					{
						case 5:	LCD1602_Show_State = 0;break;
					}
					break;
				
				case 2:  //处于TASK_CTRL状态，单击控制任务
					switch(Menu_Index)
					{
						case 6:Task1=~Task1;break;
						case 7:Task2=~Task2;break;
						case 8:Task3=~Task3;break;
						case 9:Task4=~Task4;break;
						case 10:Task5=~Task5;break;
						case 11:Task6=~Task6;break;
					}
					break;
				
				case 3:  //处于条目状态，单击进入编辑位
					Menu_Edit++; //切换编辑显示位
					break;
				case 4: //处于编辑状态，单击切换编辑位
					Menu_Edit++; //切换编辑显示位
					break;
				case 5:
					if(Menu_Index==50){EEPROM_Program_Sector_1();}
					switch(TASK_SET_Number)
					{
						case 1:
							Menu_Index = 13;
							break;
						case 2:
							Menu_Index = 14;
							break;
						case 3:
							Menu_Index = 15;
							break;
						case 4:
							Menu_Index = 16;
							break;
						case 5:
							Menu_Index = 17;
							break;
						case 6:
							Menu_Index = 18;
							break;
					}
				
					break;
			}
			
		  EC11_State = 0; //复位EC11状态
		  break;
	}
	
	/*更新对应索引号下的函数指针*/
  current_operation_index = table[Menu_Index].current_operation;
	(*current_operation_index)();////设定显示状态以及对参数进行操作
	
	/*显示当前菜单页面*/
	LCD1602_Show_Current_Page();
}

/******************************************************************************/
// LCD1602菜单页面显示函数
// 函数名称：LCD1602_Show_Current_Page()
// 输入参数：无
// 输出参数：无 
// 函数功能：显示LCD1602菜单当前页面
/******************************************************************************/
void LCD1602_Show_Current_Page()
{
	if(((Menu_Index>=0)&&(Menu_Index<=19))||((Menu_Index>=36)&&Menu_Index<=51)){
		Lcd1602_Show_String(1,1,LCD1602_First_Line);
	  Lcd1602_Show_String(2,1,LCD1602_Second_Line);
	}else if((Menu_Index>=20)&&(Menu_Index<=35)){
		Lcd1602_Show_String(1,1,LCD1602_First_Line);
		Lcd1602_Show_String(1,16,LCD1602_First_Line_16);
	  Lcd1602_Show_String(2,1,LCD1602_Second_Line);
	}
	
}





/******************************************************************************/
// LCD1602菜单操作函数
// 函数名称：
// 输入参数：无
// 输出参数：无 
// 函数功能：执行LCD1602菜单操作函数
/******************************************************************************/
/*第一级菜单*/
void TASKS_CTRL_1_0()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_TASKS_CTRL_Select;
	LCD1602_Second_Line = Menu_TASKS_SET;
}
void TASKS_SET_1_1()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_TASKS_CTRL;
	LCD1602_Second_Line = Menu_TASKS_SET_Select;
}
void PORT_SET_1_2()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_PORT_SET_Select;
	LCD1602_Second_Line = Menu_TIME_SET;
}
void TIME_SET_1_3()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_PORT_SET;
	LCD1602_Second_Line = Menu_TIME_SET_Select;
}
void WIFI_SET_1_4()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_WIFI_SET_Select;
	LCD1602_Second_Line = SYSTEM_RESET;
}

void SYSTEM_RESET_1_51()
{
	//显示位超出复位0，切换为条目
	if((Menu_Edit==3)||(Menu_Edit==2)&&(isReset==0)){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = Menu_WIFI_SET;
	    LCD1602_Second_Line = SYSTEM_RESET_Select;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//通过菜单编辑值来设定是否复位
			if(Menu_Edit_Value < 0){
				isReset = 1;
			}else if(Menu_Edit_Value > 0){
				isReset = 0;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
	
			//显示当前页的所有项目
			LCD1602_First_Line = SYSTEM_RESET_ASK;
			
			if(isReset==1){
				LCD1602_Second_Line = SYSTEM_RESET_YES;		
			}else{
				LCD1602_Second_Line = SYSTEM_RESET_NO;
			}
	    
			break;
			
		case 2:
			Menu_Flag = 4;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
	
			if(isReset==1){
				EA = 0;  //关闭总中断
				SYSTEM_DATA_RESET();
				EEPROM_Program_Sector_1();
				IAP_CONTR=0x60;//复位命令 
				EA = 1;
			}else{
				Menu_Edit = 0;  //切换回条目
			}
			
	}
	
}

void RETURN_1_5()
{
	Menu_Flag = 1;
	
	LCD1602_First_Line  = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*第二级菜单*/
//TASKS_CTRL_1_0下项目


void TASK1_CTRL_2_6()
{
	Menu_Flag = 2;
	
	if(Task1==1){
		LCD1602_First_Line = Menu_TASK1_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK1_CTRL_Run_Select;
	}
	
	if(Task2==1){
		LCD1602_Second_Line = Menu_TASK2_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK2_CTRL_Run;
	}
}
void TASK2_CTRL_2_7()
{
	Menu_Flag = 2;
	if(Task1==1){
		LCD1602_First_Line = Menu_TASK1_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK1_CTRL_Run;
	}
	
	if(Task2==1){
		LCD1602_Second_Line = Menu_TASK2_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK2_CTRL_Run_Select;
	}
}
void TASK3_CTRL_2_8()
{
	Menu_Flag = 2;
	if(Task3==1){
		LCD1602_First_Line = Menu_TASK3_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK3_CTRL_Run_Select;
	}
	
	if(Task4==1){
		LCD1602_Second_Line = Menu_TASK4_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK4_CTRL_Run;
	}
}
void TASK4_CTRL_2_9()
{
	Menu_Flag = 2;
	if(Task3==1){
		LCD1602_First_Line = Menu_TASK3_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK3_CTRL_Run;
	}
	
	if(Task4==1){
		LCD1602_Second_Line = Menu_TASK4_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK4_CTRL_Run_Select;
	}
}
void TASK5_CTRL_2_10()
{
	Menu_Flag = 2;
	if(Task5==1){
		LCD1602_First_Line = Menu_TASK5_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK5_CTRL_Run_Select;
	}
	
	if(Task6==1){
		LCD1602_Second_Line = Menu_TASK6_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK6_CTRL_Run;
	}
}
void TASK6_CTRL_2_11()
{
	Menu_Flag = 2;
	if(Task5==1){
		LCD1602_First_Line = Menu_TASK5_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK5_CTRL_Run;
	}
	
	if(Task6==1){
		LCD1602_Second_Line = Menu_TASK6_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK6_CTRL_Run_Select;
	}
}
void RETURN_2_12()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*第二级菜单*/
//TASKS_SET_1_1下项目

void TASK1_SET_2_13()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=1;
	
	LCD1602_First_Line = Menu_TASK1_SET_Select;
	LCD1602_Second_Line = Menu_TASK2_SET;
}
void TASK2_SET_2_14()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=2;
	
	LCD1602_First_Line = Menu_TASK1_SET;
	LCD1602_Second_Line = Menu_TASK2_SET_Select;
}
void TASK3_SET_2_15()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=3;
	
	LCD1602_First_Line = Menu_TASK3_SET_Select;
	LCD1602_Second_Line = Menu_TASK4_SET;
}
void TASK4_SET_2_16()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=4;
	
	LCD1602_First_Line = Menu_TASK3_SET;
	LCD1602_Second_Line = Menu_TASK4_SET_Select;
}
void TASK5_SET_2_17()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=5;
	
	LCD1602_First_Line = Menu_TASK5_SET_Select;
	LCD1602_Second_Line = Menu_TASK6_SET;
}
void TASK6_SET_2_18()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=6;
	
	LCD1602_First_Line = Menu_TASK5_SET;
	LCD1602_Second_Line = Menu_TASK6_SET_Select;
}
void RETURN_2_19()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=0;
	
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}

/*第二级菜单*/
//PORT_SET_1_2下项目

void PIN10_SET_2_20()
{
	//设置任务号显示数据
	Pin10_Number[0]=Pin10_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin10_Number;

			//显示第二行端口触发模式
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin10_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin10_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin10_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin10_Number;
			
			//显示第二行端口触发模式
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin10_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin10_Task_Number<1){Pin10_Task_Number = 1;}
			else if(Pin10_Task_Number>6){Pin10_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin10_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin10_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin10_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin10_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin10_Number;
			
			
			break;
			
	}
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '0';
}

void PIN11_SET_2_21()
{
	//设置任务号显示数据
	Pin11_Number[0]=Pin11_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin11_Number;

			//显示第二行端口触发模式
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin11_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin11_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin11_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin11_Number;
			
			//显示第二行端口触发模式
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin11_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin11_Task_Number<1){Pin11_Task_Number = 1;}
			else if(Pin11_Task_Number>6){Pin11_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin11_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin11_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin11_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin11_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin11_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '1';
	
}

void PIN12_SET_2_22()
{
	//设置任务号显示数据
	Pin12_Number[0]=Pin12_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin12_Number;

			//显示第二行端口触发模式
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin12_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin12_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin12_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin12_Number;
			
			//显示第二行端口触发模式
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin12_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin12_Task_Number<1){Pin12_Task_Number = 1;}
			else if(Pin12_Task_Number>6){Pin12_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin12_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin12_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin12_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin12_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin12_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '2';
	
}

void PIN13_SET_2_23()
{
	//设置任务号显示数据
	Pin13_Number[0]=Pin13_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin13_Number;

			//显示第二行端口触发模式
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin13_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin13_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin13_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin13_Number;
			
			//显示第二行端口触发模式
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin13_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin13_Task_Number<1){Pin13_Task_Number = 1;}
			else if(Pin13_Task_Number>6){Pin13_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin13_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin13_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin13_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin13_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin13_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '3';
	
}

void PIN14_SET_2_24()
{
	//设置任务号显示数据
	Pin14_Number[0]=Pin14_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin14_Number;

			//显示第二行端口触发模式
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin14_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin14_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin14_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin14_Number;
			
			//显示第二行端口触发模式
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin14_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin14_Task_Number<1){Pin14_Task_Number = 1;}
			else if(Pin14_Task_Number>6){Pin14_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin14_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin14_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin14_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin14_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin14_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '4';
	
}

void PIN15_SET_2_25()
{
	//设置任务号显示数据
	Pin15_Number[0]=Pin15_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin15_Number;

			//显示第二行端口触发模式
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin15_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin15_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin15_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin15_Number;
			
			//显示第二行端口触发模式
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin15_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin15_Task_Number<1){Pin15_Task_Number = 1;}
			else if(Pin15_Task_Number>6){Pin15_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin15_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin15_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin15_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin15_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin15_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '5';
	
}

void PIN16_SET_2_26()
{
	//设置任务号显示数据
	Pin16_Number[0]=Pin16_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin16_Number;

			//显示第二行端口触发模式
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin16_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin16_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin16_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin16_Number;
			
			//显示第二行端口触发模式
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin16_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin16_Task_Number<1){Pin16_Task_Number = 1;}
			else if(Pin16_Task_Number>6){Pin16_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin16_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin16_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin16_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin16_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin16_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '6';
	
}

void PIN17_SET_2_27()
{
	//设置任务号显示数据
	Pin17_Number[0]=Pin17_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin17_Number;

			//显示第二行端口触发模式
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin17_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin17_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin17_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin17_Number;
			
			//显示第二行端口触发模式
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin17_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin17_Task_Number<1){Pin17_Task_Number = 1;}
			else if(Pin17_Task_Number>6){Pin17_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin17_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin17_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin17_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin17_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin17_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '7';
	
}

void PIN20_SET_2_28()
{
	//设置任务号显示数据
	Pin20_Number[0]=Pin20_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin20_Number;

			//显示第二行端口触发模式
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin20_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin20_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin20_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin20_Number;
			
			//显示第二行端口触发模式
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin20_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin20_Task_Number<1){Pin20_Task_Number = 1;}
			else if(Pin20_Task_Number>6){Pin20_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin20_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin20_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin20_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin20_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin20_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '0';
	
}

void PIN21_SET_2_29()
{
	//设置任务号显示数据
	Pin21_Number[0]=Pin21_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin21_Number;

			//显示第二行端口触发模式
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin21_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin21_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin21_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin21_Number;
			
			//显示第二行端口触发模式
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin21_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin21_Task_Number<1){Pin21_Task_Number = 1;}
			else if(Pin21_Task_Number>6){Pin21_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin21_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin21_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin21_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin21_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin21_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '1';
	
}

void PIN22_SET_2_30()
{
	//设置任务号显示数据
	Pin22_Number[0]=Pin22_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin22_Number;

			//显示第二行端口触发模式
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin22_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin22_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin22_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin22_Number;
			
			//显示第二行端口触发模式
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin22_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin22_Task_Number<1){Pin22_Task_Number = 1;}
			else if(Pin22_Task_Number>6){Pin22_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin22_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin22_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin22_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin22_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin22_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '2';
	
}

void PIN23_SET_2_31()
{
	//设置任务号显示数据
	Pin23_Number[0]=Pin23_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin23_Number;

			//显示第二行端口触发模式
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin23_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin23_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin23_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin23_Number;
			
			//显示第二行端口触发模式
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin23_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin23_Task_Number<1){Pin23_Task_Number = 1;}
			else if(Pin23_Task_Number>6){Pin23_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin23_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin23_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin23_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin23_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin23_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '3';
	
}

void PIN24_SET_2_32()
{
	//设置任务号显示数据
	Pin24_Number[0]=Pin24_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin24_Number;

			//显示第二行端口触发模式
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin24_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin24_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin24_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin24_Number;
			
			//显示第二行端口触发模式
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin24_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin24_Task_Number<1){Pin24_Task_Number = 1;}
			else if(Pin24_Task_Number>6){Pin24_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin24_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin24_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin24_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin24_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin24_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '4';
	
}

void PIN35_SET_2_33()
{
	//设置任务号显示数据
	Pin35_Number[0]=Pin35_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin35_Number;

			//显示第二行端口触发模式
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin35_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin35_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin35_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin35_Number;
			
			//显示第二行端口触发模式
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin35_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin35_Task_Number<1){Pin35_Task_Number = 1;}
			else if(Pin35_Task_Number>6){Pin35_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin35_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin35_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin35_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin35_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin35_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '5';
	
}


void PIN36_SET_2_34()
{
	//设置任务号显示数据
	Pin36_Number[0]=Pin36_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin36_Number;

			//显示第二行端口触发模式
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin36_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin36_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin36_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin36_Number;
			
			//显示第二行端口触发模式
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin36_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin36_Task_Number<1){Pin36_Task_Number = 1;}
			else if(Pin36_Task_Number>6){Pin36_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin36_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin36_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin36_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin36_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin36_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '6';
	
}

void PIN37_SET_2_35()
{
	//设置任务号显示数据
	Pin37_Number[0]=Pin37_Task_Number+'0'; 
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
		
			//显示第一行端口输入输出状态
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin37_Number;

			//显示第二行端口触发模式
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //第一个编辑位，箭头
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定箭头,(输入输出模式)
			if(Menu_Edit_Value < 0){
				Pin37_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin37_Mode = 0;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//当前选中条目的闪烁
			//箭头的闪烁
			if(Menu_Edit_Show){  //如果显示箭头
				
				if(Pin37_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //否则不显示箭头
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//显示其他项目
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin37_Number;
			
			//显示第二行端口触发模式
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //第二个编辑位，任务号
			
			Menu_Flag = 4;
		
			//修改任务号
			Pin37_Task_Number += Menu_Edit_Value;
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//设定任务号可以设置的范围
			if(Pin37_Task_Number<1){Pin37_Task_Number = 1;}
			else if(Pin37_Task_Number>6){Pin37_Task_Number = 6;}
		
			//当前选中条目的闪烁
			//任务号的闪烁
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin37_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第二行端口触发模式
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //第三个编辑位，端口的触发模式
			
			Menu_Flag = 4;
		
		
			//通过菜单编辑值来设定触发模式,立即触发或者自锁触发
			if(Menu_Edit_Value < 0){
				Pin37_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin37_Trigger_Mode = 1;
			}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//触发模式的闪烁
			if(Menu_Edit_Show){
			  if(Pin37_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//显示其他项目
			//显示第一行端口输入输出状态
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//显示第一行16位端口匹配任务号
			LCD1602_First_Line_16 = Pin37_Number;
			
			break;
			
	}
	
	//设置端口号显示数据
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '7';
	
}

void RETURN_2_36()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*第二级菜单*/
//TIME_SET_1_3下项目
void TIME_SET_Manual_Set_2_37()
{
	
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==7){Menu_Edit=0;};
	
	//SET_DATE[]  ="DATE:2022/07/17 ";
  //SET_TIME[]  ="TIME: 00:00:00  ";
  //如果在1-6编辑位时，设定日期时间显示内容
	if(Menu_Edit>=1){
		//设置日期
		SET_DATE[5]=Year/1000%10+'0';
		SET_DATE[6]=Year/100%10+'0';
		SET_DATE[7]=Year/10%10+'0';
		SET_DATE[8]=Year%10+'0';
		
		SET_DATE[10]=Month/10%10+'0';
		SET_DATE[11]=Month%10+'0';
		
		SET_DATE[13]=Day/10%10+'0';
		SET_DATE[14]=Day%10+'0';
		
		//设置时间
		SET_TIME[6]=hour/10%10+'0';
		SET_TIME[7]=hour%10+'0';
		
		SET_TIME[9]=minute/10%10+'0';
		SET_TIME[10]=minute%10+'0';
		
		SET_TIME[12]=second/10%10+'0';
		SET_TIME[13]=second%10+'0';
		
		LCD1602_First_Line = SET_DATE;
	  LCD1602_Second_Line = SET_TIME;
	}
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
			LCD1602_First_Line = SET_TIME_MANUAL_Select;
	    LCD1602_Second_Line = SET_TIME_AUTO;
			
			break;
			
		case 1:
			Menu_Flag = 4;
		  
			//更新Year
			Year += Menu_Edit_Value;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//年的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[5] = ' ';
				LCD1602_First_Line[6] = ' ';
				LCD1602_First_Line[7] = ' ';
				LCD1602_First_Line[8] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		  
			//更新Month
			Month += Menu_Edit_Value;
		
			//限制Month的设置范围
			if(Month<1){Month=1;}
			else if(Month>12){Month=12;}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//年的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[10] = ' ';
				LCD1602_First_Line[11] = ' ';
			}
			break;
			
		case 3:
			Menu_Flag = 4;
		  
			//更新Day
			Day += Menu_Edit_Value;
		
			//限制Day
			if(Day<1){Day=1;}
			else if(Day>Max_Month_Days[Month]){Day=Max_Month_Days[Month];}
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//年的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[13] = ' ';
				LCD1602_First_Line[14] = ' ';
			}
			break;	
			
		case 4:
			Menu_Flag = 4;
		  
			//更新小时
			hour += Menu_Edit_Value;
		
			//限制小时的设置范围
			if(hour<0){hour=0;}
			else if(hour>23){hour=23;}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;	
			
		case 5:
			Menu_Flag = 4;
		  
			//更新分钟
			minute += Menu_Edit_Value;
		
			//限制分钟的设置范围
			if(minute<0){minute=0;}
			else if(minute>59){minute=59;}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;	
			
		case 6:
			Menu_Flag = 4;
		  
			//更新秒
			second += Menu_Edit_Value;
		
			//限制秒的设置范围
			if(second<0){second=0;}
			else if(second>59){second=59;}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		  
			//当前选中条目的闪烁
			//秒的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;	
	}
}

void TIME_SET_Auto_Set_2_38()
{
	
		//显示位超出复位0，切换为条目
	if(Menu_Edit==1){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
		  //显示当前页的所有项目
			LCD1602_First_Line = SET_TIME_MANUAL;
	    LCD1602_Second_Line = SET_TIME_AUTO_Select;
			
			break;
		
	 }
}

void RETURN_2_39()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}

/*第二级菜单*/
//WIFI_SET_1_4下项目
void TCP_PORT_SET_2_40()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//设定显示内容
	if(Menu_Edit>=1){
		//根据当前TCP端口设定菜单显示端口
		TCP_PORT_Number[5] = TcpServerPort/10000%10+'0';
		TCP_PORT_Number[6] = TcpServerPort/1000%10+'0';
		TCP_PORT_Number[7] = TcpServerPort/100%10+'0';
		TCP_PORT_Number[8] = TcpServerPort/10%10+'0';
		TCP_PORT_Number[9] = TcpServerPort/1%10+'0';
		
		//设定TCP服务器的端口
		ATCIPSERVER[15] = TcpServerPort/10000%10+'0';
		ATCIPSERVER[16] = TcpServerPort/1000%10+'0';
		ATCIPSERVER[17] = TcpServerPort/100%10+'0';
		ATCIPSERVER[18] = TcpServerPort/10%10+'0';
		ATCIPSERVER[19] = TcpServerPort/1%10+'0';
		
	  //显示当前页的所有项目
		LCD1602_First_Line = TCP_SERVER_PORT;
		LCD1602_Second_Line = TCP_PORT_Number;
	}
	
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = TCP_PORT_SET_Select;
	    LCD1602_Second_Line = STA_IP;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
	
			break;
		
		case 2:
			Menu_Flag = 4;
			
			TcpServerPort += Menu_Edit_Value*100;
			if(TcpServerPort<1){
				TcpServerPort=1;
			}else if(TcpServerPort>65535){
				TcpServerPort=65535;
			}
			
			
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//前三位的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[5] = ' ';
				LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}

			break;
			
		case 3:
			Menu_Flag = 4;
		
			TcpServerPort += Menu_Edit_Value;
			
			if(TcpServerPort<1){
				TcpServerPort=1;
			}else if(TcpServerPort>65535){
				TcpServerPort=65535;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//后两位的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[8] = ' ';
				LCD1602_Second_Line[9] = ' ';
			}

			break;
		
	}
}

void STA_IP_2_41()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = TCP_PORT_SET;
	    LCD1602_Second_Line = STA_IP_Select;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = STA_IP_ADDRESS;
	    LCD1602_Second_Line = STAIPTable;
				
			break;
	}
	
}

void AP_IP_2_42()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = AP_IP_Select;
	    LCD1602_Second_Line = RETURN;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
		
			//显示当前页的所有项目
			LCD1602_First_Line = AP_IP_ADDRESS;
	    LCD1602_Second_Line = APIPTable;
				
			break;
	}
	
}

void RETURN_2_43()
{
	Menu_Flag = 0;
	LCD1602_First_Line = AP_IP;
	LCD1602_Second_Line = RETURN_Select;
}



/*第三级菜单*/
//TASK_SET下项目（TASK1-TASK1复用）
void TASK_StartTime_SET_3_44()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==3){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_StartTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			//1234分钟
			//取出小时
			//1234/60  =  20小时   20x60=1200  余数34
			//1299/60  =  21小时   21x60=1260  余数39
			
			Time_Minute[3]=Task1_StartTime/60/10%10+'0';
			Time_Minute[4]=Task1_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task1_StartTime-(Task1_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task1_StartTime-(Task1_StartTime/60)*60)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
			Time_Minute[3]=Task2_StartTime/60/10%10+'0';
			Time_Minute[4]=Task2_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task2_StartTime-(Task2_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task2_StartTime-(Task2_StartTime/60)*60)/1%10+'0';
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			Time_Minute[3]=Task3_StartTime/60/10%10+'0';
			Time_Minute[4]=Task3_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task3_StartTime-(Task3_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task3_StartTime-(Task3_StartTime/60)*60)/1%10+'0';
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
		  Time_Minute[3]=Task4_StartTime/60/10%10+'0';
			Time_Minute[4]=Task4_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task4_StartTime-(Task4_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task4_StartTime-(Task4_StartTime/60)*60)/1%10+'0';
			break;
		case 5: 
			LCD1602_First_Line[4]='5';
			Time_Minute[3]=Task5_StartTime/60/10%10+'0';
			Time_Minute[4]=Task5_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task5_StartTime-(Task5_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task5_StartTime-(Task5_StartTime/60)*60)/1%10+'0';
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			Time_Minute[3]=Task6_StartTime/60/10%10+'0';
			Time_Minute[4]=Task6_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task6_StartTime-(Task6_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task6_StartTime-(Task6_StartTime/60)*60)/1%10+'0';
			break;
	}
	LCD1602_Second_Line = Time_Minute;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_StartTime+=Menu_Edit_Value*60;
					if(Task1_StartTime<0){Task1_StartTime=0;}
					else if(Task1_StartTime>1439){Task1_StartTime=1439;}
					break;
				
				case 2:
					Task2_StartTime+=Menu_Edit_Value*60;
					if(Task2_StartTime<0){Task2_StartTime=0;}
					else if(Task2_StartTime>1439){Task2_StartTime=1439;}
					break;
					
				case 3:
					Task3_StartTime+=Menu_Edit_Value*60;
					if(Task3_StartTime<0){Task3_StartTime=0;}
					else if(Task3_StartTime>1439){Task3_StartTime=1439;}
					break;
					
				case 4:
					Task4_StartTime+=Menu_Edit_Value*60;
					if(Task4_StartTime<0){Task4_StartTime=0;}
					else if(Task4_StartTime>1439){Task4_StartTime=1439;}
					break;
					
				case 5:
					Task5_StartTime+=Menu_Edit_Value*60;
					if(Task5_StartTime<0){Task5_StartTime=0;}
					else if(Task5_StartTime>1439){Task5_StartTime=1439;}
					break;
					
				case 6:
					Task6_StartTime+=Menu_Edit_Value*60;
					if(Task6_StartTime<0){Task6_StartTime=0;}
					else if(Task6_StartTime>1439){Task6_StartTime=1439;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_StartTime+=Menu_Edit_Value;
					if(Task1_StartTime<0){Task1_StartTime=0;}
					else if(Task1_StartTime>1439){Task1_StartTime=1439;}
					break;
				
				case 2:
					Task2_StartTime+=Menu_Edit_Value;
					if(Task2_StartTime<0){Task2_StartTime=0;}
					else if(Task2_StartTime>1439){Task2_StartTime=1439;}
					break;
				
				case 3:
					Task3_StartTime+=Menu_Edit_Value;
					if(Task3_StartTime<0){Task3_StartTime=0;}
					else if(Task3_StartTime>1439){Task3_StartTime=1439;}
					break;
					
				case 4:
					Task4_StartTime+=Menu_Edit_Value;
					if(Task4_StartTime<0){Task4_StartTime=0;}
					else if(Task4_StartTime>1439){Task4_StartTime=1439;}
					break;
				
				case 5:
					Task5_StartTime+=Menu_Edit_Value;
					if(Task5_StartTime<0){Task5_StartTime=0;}
					else if(Task5_StartTime>1439){Task5_StartTime=1439;}
					break;
				
				case 6:
					Task6_StartTime+=Menu_Edit_Value;
					if(Task6_StartTime<0){Task6_StartTime=0;}
					else if(Task6_StartTime>1439){Task6_StartTime=1439;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
	}
	
}

void TASK_EndTime_SET_3_45()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==3){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_EndTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			Time_Minute[3]=Task1_EndTime/60/10%10+'0';
			Time_Minute[4]=Task1_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task1_EndTime-(Task1_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task1_EndTime-(Task1_EndTime/60)*60)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
			Time_Minute[3]=Task2_EndTime/60/10%10+'0';
			Time_Minute[4]=Task2_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task2_EndTime-(Task2_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task2_EndTime-(Task2_EndTime/60)*60)/1%10+'0';
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			Time_Minute[3]=Task3_EndTime/60/10%10+'0';
			Time_Minute[4]=Task3_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task3_EndTime-(Task3_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task3_EndTime-(Task3_EndTime/60)*60)/1%10+'0';
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
		  Time_Minute[3]=Task4_EndTime/60/10%10+'0';
			Time_Minute[4]=Task4_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task4_EndTime-(Task4_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task4_EndTime-(Task4_EndTime/60)*60)/1%10+'0';
			break;
		case 5: 
			LCD1602_First_Line[4]='5';
			Time_Minute[3]=Task5_EndTime/60/10%10+'0';
			Time_Minute[4]=Task5_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task5_EndTime-(Task5_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task5_EndTime-(Task5_EndTime/60)*60)/1%10+'0';
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			Time_Minute[3]=Task6_EndTime/60/10%10+'0';
			Time_Minute[4]=Task6_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task6_EndTime-(Task6_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task6_EndTime-(Task6_EndTime/60)*60)/1%10+'0';
			break;
	}
	LCD1602_Second_Line = Time_Minute;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_EndTime+=Menu_Edit_Value*60;
					if(Task1_EndTime<0){Task1_EndTime=0;}
					else if(Task1_EndTime>1439){Task1_EndTime=1439;}
					break;
				
				case 2:
					Task2_EndTime+=Menu_Edit_Value*60;
					if(Task2_EndTime<0){Task2_EndTime=0;}
					else if(Task2_EndTime>1439){Task2_EndTime=1439;}
					break;
					
				case 3:
					Task3_EndTime+=Menu_Edit_Value*60;
					if(Task3_EndTime<0){Task3_EndTime=0;}
					else if(Task3_EndTime>1439){Task3_EndTime=1439;}
					break;
					
				case 4:
					Task4_EndTime+=Menu_Edit_Value*60;
					if(Task4_EndTime<0){Task4_EndTime=0;}
					else if(Task4_EndTime>1439){Task4_EndTime=1439;}
					break;
					
				case 5:
					Task5_EndTime+=Menu_Edit_Value*60;
					if(Task5_EndTime<0){Task5_EndTime=0;}
					else if(Task5_EndTime>1439){Task5_EndTime=1439;}
					break;
					
				case 6:
					Task6_EndTime+=Menu_Edit_Value*60;
					if(Task6_EndTime<0){Task6_EndTime=0;}
					else if(Task6_EndTime>1439){Task6_EndTime=1439;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_EndTime+=Menu_Edit_Value;
					if(Task1_EndTime<0){Task1_EndTime=0;}
					else if(Task1_EndTime>1439){Task1_EndTime=1439;}
					break;
				
				case 2:
					Task2_EndTime+=Menu_Edit_Value;
					if(Task2_EndTime<0){Task2_EndTime=0;}
					else if(Task2_EndTime>1439){Task2_EndTime=1439;}
					break;
				
				case 3:
					Task3_EndTime+=Menu_Edit_Value;
					if(Task3_EndTime<0){Task3_EndTime=0;}
					else if(Task3_EndTime>1439){Task3_EndTime=1439;}
					break;
					
				case 4:
					Task4_EndTime+=Menu_Edit_Value;
					if(Task4_EndTime<0){Task4_EndTime=0;}
					else if(Task4_EndTime>1439){Task4_EndTime=1439;}
					break;
				
				case 5:
					Task5_EndTime+=Menu_Edit_Value;
					if(Task5_EndTime<0){Task5_EndTime=0;}
					else if(Task5_EndTime>1439){Task5_EndTime=1439;}
					break;
				
				case 6:
					Task6_EndTime+=Menu_Edit_Value;
					if(Task6_EndTime<0){Task6_EndTime=0;}
					else if(Task6_EndTime>1439){Task6_EndTime=1439;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
	}
}

void TASK_OverTime_SET_3_46()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_OverTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//864000 (100MS)
			//首先将864000个100MS转化成小时
			//   /10转换成S  /60转换成分钟 再/60转换成小时 
		//	Time_100MS[2]=Task1_OverTime/2/10/60/60/10%10+'0';
		//	Time_100MS[3]=Task1_OverTime/2/10/60/60/1%10+'0';
		
			//345643(100ms)
		  //345643-9*36000=345643-324000=21643(100MS)
		  //转换成小时
		  //345643/10/60/60=9.60119444小时
			//转换成分钟
			//345643/10/60=576.071667分钟
		
			//691286
			//获取小时信息
			Time_100MS[1]=Task1_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OverTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task1_OverTime/10/60/2)-(Task1_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OverTime/10/60/2)-(Task1_OverTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task1_OverTime/10/2)-(Task1_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OverTime/10/2)-(Task1_OverTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task1_OverTime/2)-(Task1_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OverTime/2)-(Task1_OverTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  
			Time_100MS[1]=Task2_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task2_OverTime/10/60/2)-(Task2_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OverTime/10/60/2)-(Task2_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task2_OverTime/10/2)-(Task2_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OverTime/10/2)-(Task2_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task2_OverTime/2)-(Task2_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OverTime/2)-(Task2_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			
			Time_100MS[1]=Task3_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task3_OverTime/10/60/2)-(Task3_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OverTime/10/60/2)-(Task3_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task3_OverTime/10/2)-(Task3_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OverTime/10/2)-(Task3_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task3_OverTime/2)-(Task3_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OverTime/2)-(Task3_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			
			Time_100MS[1]=Task4_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task4_OverTime/10/60/2)-(Task4_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OverTime/10/60/2)-(Task4_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task4_OverTime/10/2)-(Task4_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OverTime/10/2)-(Task4_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task4_OverTime/2)-(Task4_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OverTime/2)-(Task4_OverTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			
			Time_100MS[1]=Task5_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task5_OverTime/10/60/2)-(Task5_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OverTime/10/60/2)-(Task5_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task5_OverTime/10/2)-(Task5_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OverTime/10/2)-(Task5_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task5_OverTime/2)-(Task5_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OverTime/2)-(Task5_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			
			Time_100MS[1]=Task6_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task6_OverTime/10/60/2)-(Task6_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OverTime/10/60/2)-(Task6_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task6_OverTime/10/2)-(Task6_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OverTime/10/2)-(Task6_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task6_OverTime/2)-(Task6_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OverTime/2)-(Task6_OverTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:  //第一个编辑位，修改小时
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*36000*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*36000*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
					
				case 3:
					Task3_OverTime+=Menu_Edit_Value*36000*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*36000*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
					
				case 5:
					Task5_OverTime+=Menu_Edit_Value*36000*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
					
				case 6:
					Task6_OverTime+=Menu_Edit_Value*36000*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*600*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*600*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*600*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*600*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*600*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*600*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //第三个编辑位，秒的设定
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*10*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*10*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*10*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*10*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*10*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*10*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //第四个编辑位，100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}
}

void TASK_OverTime_MODE_SET_3_47()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_OverTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			if(Task1_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  if(Task2_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			if(Task3_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			if(Task4_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			if(Task5_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			if(Task6_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
	}
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
				
			break;
			
		case 1:  //第一个编辑位，开启或者关闭自动复位
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task1_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task1_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
				case 2:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task2_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task2_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
				case 3:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task3_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task3_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
				case 4:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task4_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task4_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
				case 5:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task5_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task5_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
				case 6:
					//通过菜单编辑值来设定任务超时复位
					if(Menu_Edit_Value < 0){
						Task6_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task6_OverTime_Reset = 0;
					}
			
					//复位菜单当前编辑值
					Menu_Edit_Value = 0;
					break;
			}
			
				//当前选中条目的闪烁
			if(Menu_Edit_Show){  
				LCD1602_Second_Line = TASK_OverTime_AutoReset_Empty;
			}
			
			break;
		}
}

void TASK_OnTime_SET_3_48()
{
	
	//显示位超出复位0，切换为条目
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_OnTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//获取小时信息
			Time_100MS[1]=Task1_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task1_OnTime/10/60/2)-(Task1_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OnTime/10/60/2)-(Task1_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task1_OnTime/10/2)-(Task1_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OnTime/10/2)-(Task1_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task1_OnTime/2)-(Task1_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OnTime/2)-(Task1_OnTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //获取小时信息
			Time_100MS[1]=Task2_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task2_OnTime/10/60/2)-(Task2_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OnTime/10/60/2)-(Task2_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task2_OnTime/10/2)-(Task2_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OnTime/10/2)-(Task2_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task2_OnTime/2)-(Task2_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OnTime/2)-(Task2_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//获取小时信息
			Time_100MS[1]=Task3_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task3_OnTime/10/60/2)-(Task3_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OnTime/10/60/2)-(Task3_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task3_OnTime/10/2)-(Task3_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OnTime/10/2)-(Task3_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task3_OnTime/2)-(Task3_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OnTime/2)-(Task3_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//获取小时信息
			Time_100MS[1]=Task4_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task4_OnTime/10/60/2)-(Task4_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OnTime/10/60/2)-(Task4_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task4_OnTime/10/2)-(Task4_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OnTime/10/2)-(Task4_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task4_OnTime/2)-(Task4_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OnTime/2)-(Task4_OnTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//获取小时信息
			Time_100MS[1]=Task5_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task5_OnTime/10/60/2)-(Task5_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OnTime/10/60/2)-(Task5_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task5_OnTime/10/2)-(Task5_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OnTime/10/2)-(Task5_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task5_OnTime/2)-(Task5_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OnTime/2)-(Task5_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//获取小时信息
			Time_100MS[1]=Task6_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OnTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task6_OnTime/10/60/2)-(Task6_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OnTime/10/60/2)-(Task6_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task6_OnTime/10/2)-(Task6_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OnTime/10/2)-(Task6_OnTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task6_OnTime/2)-(Task6_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OnTime/2)-(Task6_OnTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //第一个编辑位，修改小时
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*36000*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*36000*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
					
				case 3:
					Task3_OnTime+=Menu_Edit_Value*36000*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*36000*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
					
				case 5:
					Task5_OnTime+=Menu_Edit_Value*36000*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
					
				case 6:
					Task6_OnTime+=Menu_Edit_Value*36000*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*600*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*600*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*600*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*600*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*600*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*600*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //第三个编辑位，秒的设定
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*10*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*10*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*10*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*10*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*10*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*10*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //第四个编辑位，100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//100MS的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}
}

void TASK_OffTime_SET_3_49()
{
	//显示位超出复位0，切换为条目
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_OffTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//获取小时信息
			Time_100MS[1]=Task1_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //获取小时信息
			Time_100MS[1]=Task2_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//获取小时信息
			Time_100MS[1]=Task3_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//获取小时信息
			Time_100MS[1]=Task4_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//获取小时信息
			Time_100MS[1]=Task5_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//获取小时信息
			Time_100MS[1]=Task6_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //第一个编辑位，修改小时
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*36000*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*36000*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
					
				case 3:
					Task3_OffTime+=Menu_Edit_Value*36000*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*36000*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
					
				case 5:
					Task5_OffTime+=Menu_Edit_Value*36000*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
					
				case 6:
					Task6_OffTime+=Menu_Edit_Value*36000*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*600*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*600*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*600*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*600*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*600*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*600*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //第三个编辑位，秒的设定
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*10*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*10*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*10*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*10*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*10*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*10*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //第四个编辑位，100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//100MS的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}

	//显示位超出复位0，切换为条目
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//显示当前页的所有项目
	LCD1602_First_Line = TASK_OffTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//获取小时信息
			Time_100MS[1]=Task1_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //获取小时信息
			Time_100MS[1]=Task2_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//获取小时信息
			Time_100MS[1]=Task3_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//获取小时信息
			Time_100MS[1]=Task4_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//获取小时信息
			Time_100MS[1]=Task5_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//获取小时信息
			Time_100MS[1]=Task6_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OffTime/10/60/60/2/1%10+'0';
		
			//获取分钟信息
			//总时间减去小时部分，剩下分钟部分
			//总时间转换成分钟
			Time_100MS[6]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//获取秒信息
			Time_100MS[9]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/1%10+'0';
		
			//获取100MS信息		
			Time_100MS[12]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//显示不同显示位时的状态
	switch(Menu_Edit)
	{
		case 0:   //条目状态
			
			Menu_Flag = 3;
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //第一个编辑位，修改小时
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*36000*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*36000*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
					
				case 3:
					Task3_OffTime+=Menu_Edit_Value*36000*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*36000*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
					
				case 5:
					Task5_OffTime+=Menu_Edit_Value*36000*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
					
				case 6:
					Task6_OffTime+=Menu_Edit_Value*36000*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//小时的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*600*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*600*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*600*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*600*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*600*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*600*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //第三个编辑位，秒的设定
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*10*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*10*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*10*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*10*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*10*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*10*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//分钟的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //第四个编辑位，100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//复位菜单当前编辑值
			Menu_Edit_Value = 0;
			
			//当前选中条目的闪烁
			//100MS的闪烁
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}

	
}

void RETURN_3_50()
{
	Menu_Flag = 5;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}



