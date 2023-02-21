#include "Config.h"
#include "LCD1602_Show.h"
#include "LCD1602_Menu.h"
#include "LCD1602_Clock.h"

u8 LCD1602_Show_State = 0; //LCD1602µ±Ç°ÏÔÊ¾×´Ì¬

void LCD1602_Show_Update(void)
{
	switch(LCD1602_Show_State)
	{
		case 0:
			LCD1602_Clock_Update();
		  break;
		case 1:
			LCD1602_DateTime_Update();
			break;
		case 2:
	    LCD1602_Menu_Update();
			break;
	}
}

