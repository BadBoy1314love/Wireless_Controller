/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "config.h"
#include "Download.h"

//uint8 xdata uart_ser_n=0;//计数变量

/*void uart_ser()   // interrupt INTERRUPT_UART_Rx_Tx
{ 
		if(RI)
		{
				RI=0;        //清空接收标志位
				if(SBUF==0x7f)  //STC下载指令0X7F
				{ 
						uart_ser_n++;   //判断位自加
						if(uart_ser_n==10) //如果收到10次0X7F
						{
								uart_ser_n=0;   //判断位清0
								ISP_CONTR=0x60;//复位命令  
						}
				}
				else
				{
						uart_ser_n=0;	
				}
	  }
		if(TI)
		{
				TI=0;
		}
} 
*/
/*
void UartInit(void)		//9600bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//定时器1开始计时
	ES = 1;    //启用串口中断
}
*/

/*
void UartInit(void)		//115200bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFF;		//设置定时初始值
	TH1 = 0xFF;		//设置定时重载值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//定时器1开始计时
	ES = 1;    //启用串口中断
}
*/
