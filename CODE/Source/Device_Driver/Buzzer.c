#include "Config.h"
#include "Buzzer.h"
#include "Timer.h"

u8 Number;

void Buzzer_Init()
{
	Number = 70;
	Buzzer = 1;
	ET1 = 0;    //关闭定时器1中断
}

void Buzzer_Open()
{
	ET1 = 1;    //开启定时器1中断
}

/*
void Buzzer_Close()
{
	ET1 = 0;    //关闭定时器1中断
}
*/

void Buzzer_Key_Beep() interrupt INTERRUPT_Timer_1_Overflow
{
	Timer1_Reload();                                                                                      
	if(--Number > 0){
		Buzzer = ~Buzzer;
	}else{
		Buzzer_Init();
	}	
}
