/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "config.h"
#include "LCD1602_Clock.h"
#include "LCD1602.h"

/******************************************************************************/
// 变量初始化
/******************************************************************************/
uint8 hour_ten_pos=0;   //小时十位(用于充当LCD1602点阵数字显示函数的列变化量)
uint8 hour_bit_pos=4;   //小时个位(用于充当LCD1602点阵数字显示函数的列变化量)
uint8 minute_ten_pos=9;   //分钟十位(用于充当LCD1602点阵数字显示函数的列变化量)
uint8 minute_bit_pos=13;  //分钟个位(用于充当LCD1602点阵数字显示函数的列变化量)

/*时间存储变量*/
s8 hour=0,minute=0,second=0;

/*当前时间转换成分钟的变量*/
u16 NowTime = 0;

/*判断时间界面“点”更新的变量*/
bit point=0;

//时间补偿控制位
bit isFixTime = 1;

u8 xdata Max_Month_Days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

extern u8 xdata DateTable[13];
extern u8 xdata TimeTable[12];

extern s16 Year;
extern s8 Month;
extern s8 Day;

/******************************************************************************/
// 字符构造表
/******************************************************************************/
uint8 code lcd1602Table0[8]={0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00}; //0点阵__上
uint8 code lcd1602Table1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F}; //1点阵__下
uint8 code lcd1602Table2[8]={0x1F,0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F}; //2点阵__上下
uint8 code lcd1602Table3[8]={0x1F,0x1F,0x00,0x1F,0x1F,0x00,0x1F,0x1F}; //3点阵__上中下
uint8 code lcd1602Table4[8]={0x00,0x00,0x07,0x07,0x07,0x07,0x00,0x00}; //4点阵__点点左
uint8 code lcd1602Table5[8]={0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x00,0x00}; //5点阵__点点右
uint8 code lcd1602Table6[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //6点阵__写空

/******************************************************************************/
// LCD1602点阵数字显示函数
// 函数名称：Lcd1602_Number
// 输入参数：column_change-列变化量(用于确定显示位置)，number-想要显示的数字
// 输出参数：无 
// 函数功能：LCD1602在指定位置显示点阵数字
/******************************************************************************/
void LCD1602_Number(uint8 column_change,uint8 number)
{
	switch(number){
		case 0:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
		  break;
		case 1:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+3,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+1,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+2,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+3,1,lcd1602Table1);
			break;
		case 2:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,2,lcd1602Table2);
			break;
		case 3:
			Lcd1602_Custom_Char(1,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 4:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,6,lcd1602Table6);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(2,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 5:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+1,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 6:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 7:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+2,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 8:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 9:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
		  break;
	}
}

/******************************************************************************/
// LCD1602点阵数字时钟时间更新函数
// 函数名称：Lcd1602_Time_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602点阵数字时钟时间更新
/******************************************************************************/
void LCD1602_Time_Update()
{

	//判断是否为闰年，是则将二月修改为29天，不是则为28天
	if(Year%400==0||(Year%4==0&&Year%100!=0))
	{
		Max_Month_Days[2]=29;  //闰年
	}else{
		Max_Month_Days[2]=28;  //平年
	}
	
	/*
	//时间补偿，每两个小时(奇数个小时做补偿)
	if((isFixTime==1)&&(hour%2!=0)&&(minute==59)&&(second==59))
	{
		second--;
		isFixTime = 0; //关闭时间补偿
	}
	*/
	
	//时间补偿
	if((isFixTime==1)&&(hour%2!=0)&&(minute==59)&&(second==59))
	{
		second--;
		isFixTime = 0; //关闭时间补偿
	}
	//时间补偿
	else if((isFixTime==1)&&(hour%2==0)&&(minute==59)&&(second==59))
	{
		second--;
		second--;
		isFixTime = 0; //关闭时间补偿
	}
	
	point=~point;
	second++;
	if(second==60){
		isFixTime = 1; //开启时间补偿
		second=0;
		minute++;
		if(minute==60){
			minute=0;
			hour++;
			if(hour==24){
				hour=0;
				Day++;
				if(Day>Max_Month_Days[Month]){
					Day=1;
					Month++;
					if(Month==13){
						Month=1;
						Year++;
					}
				}
			}
		}
	}
	
	NowTime = hour*60+minute;  //当前时间的转换值单位为分钟（0-1439） 
	
	//更新日期时间数组
	//遍历时间数组写入时间信息
	//有用时间数据一共19位为：2022/06/14 19:03:24
	
//	更新日期数据
	DateTable[0]=Year/1000%10+'0';
	DateTable[1]=Year/100%10+'0';
	DateTable[2]=Year/10%10+'0';
	DateTable[3]=Year%10+'0';
	
	DateTable[5]=Month/10%10+'0';
	DateTable[6]=Month%10+'0';
	
	DateTable[8]=Day/10%10+'0';
	DateTable[9]=Day/1%10+'0';
	
  //	更新时间数据
	TimeTable[0]=hour/10%10+'0';
	TimeTable[1]=hour/1%10+'0';

	TimeTable[3]=minute/10%10+'0';
	TimeTable[4]=minute/1%10+'0';
	
	TimeTable[6]=second/10%10+'0';			
	TimeTable[7]=second/1%10+'0';

	
}


/******************************************************************************/
// LCD1602点阵数字时钟（数字+点）显示函数
// 函数名称：Lcd1602_Clock_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602刷新点阵数字时钟
/******************************************************************************/
void LCD1602_Clock_Update()
{
	LCD1602_Number(minute_ten_pos,minute/10);
	LCD1602_Number(minute_bit_pos,minute%10);
	LCD1602_Number(hour_ten_pos,hour/10);
	LCD1602_Number(hour_bit_pos,hour%10);
	
	Lcd1602_Custom_Char(1,4,6,lcd1602Table6);
	Lcd1602_Custom_Char(1,13,6,lcd1602Table6);
	Lcd1602_Custom_Char(2,4,6,lcd1602Table6);
	Lcd1602_Custom_Char(2,13,6,lcd1602Table6);
	
	if(point){
		Lcd1602_Custom_Char(1,8,4,lcd1602Table4);
	  Lcd1602_Custom_Char(2,9,5,lcd1602Table5);
	  Lcd1602_Custom_Char(1,9,6,lcd1602Table6);
	  Lcd1602_Custom_Char(2,8,6,lcd1602Table6);
	}else{
		Lcd1602_Custom_Char(1,8,6,lcd1602Table6);
		Lcd1602_Custom_Char(2,9,6,lcd1602Table6);
		Lcd1602_Custom_Char(1,9,5,lcd1602Table5);
		Lcd1602_Custom_Char(2,8,4,lcd1602Table4);
	}
}

/******************************************************************************/
// LCD1602日期/时间显示函数
// 函数名称：LCD1602_DateTime_Update
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602显示日期和时间
/******************************************************************************/
void LCD1602_DateTime_Update(void)
{	
	Lcd1602_Show_String(1,1,"   ");
	Lcd1602_Show_String(2,1,"    ");
	Lcd1602_Show_String(1,14,"   ");
	Lcd1602_Show_String(2,13,"    ");
	Lcd1602_Show_String(1,4,DateTable);
	Lcd1602_Show_String(2,5,TimeTable);
}
