#include "Timer.h"
#include "config.h"

void Timer1Init(void)		//20微秒@11.0592MHz
{
  AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x66;		//设置定时初始值
	TH1 = 0xEA;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	//	ET1 = 1;    //开定时器1中断
	ET1 = 0;    //关闭定时器1中断
}

void Timer1_Reload()  //定时器1重装
{
	TF1 = 0;		//清除TF1标志
	TR1 = 0;		//定时器0停止计时
	TL1 = 0x66;		//设置定时初始值
	TH1 = 0xEA;		//设置定时初始值
	TR1 = 1;		//定时器0开始计时
}

