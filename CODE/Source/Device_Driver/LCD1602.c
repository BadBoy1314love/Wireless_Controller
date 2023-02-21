/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "config.h"
#include "LCD1602.h"
#include "delay.h"
/******************************************************************************/
// 函数名称：Lcd1602_Custom_Char 
// 输入参数：row-行 col-列 pos-CGRAM位置 *customValueTable-自定义字符数据
// 输出参数：无 
// 函数功能：显示自定义字符
/******************************************************************************/
void Lcd1602_Custom_Char(uint8 row, uint8 col, uint8 pos, uint8 *customValueTable){
	uint8 i = 0;
	for(i=0;i<8;i++){
		Lcd1602_Write_Cmd(0x40+pos*8+i);
		Lcd1602_Write_Data(*(customValueTable+i));
	}
	if(row==1){
		Lcd1602_Write_Cmd(0x00+0x80+col-1);
		Lcd1602_Write_Data(0x00+pos);
	}else{
		Lcd1602_Write_Cmd(0x40+0x80+col-1);
		Lcd1602_Write_Data(0x00+pos);	
	}
}
/******************************************************************************/
// 函数名称：Lcd1602_Show_String 
// 输入参数：row-行 col-列 *str-字符
// 输出参数：无 
// 函数功能：LCD1602显示字符
/******************************************************************************/
void Lcd1602_Show_String(uint8 row, uint8 col,uint8 *str){
	uint8 *defaultValue = "parameter error" ;
	switch(row){
		case 1:
				Lcd1602_Write_Cmd(0x00+0x80+col-1);//第一行第y个空格
				while(*str!='\0'){
					Lcd1602_Write_Data(*str);
					str++;
				}
				break;	
		case 2:
				Lcd1602_Write_Cmd(0x40+0x80+col-1);//第二行第y个空格
				while(*str!='\0'){
					Lcd1602_Write_Data(*str);
					str++;
				}
				break;

	   default:
	   			Lcd1602_Write_Cmd(0x00+0x80);//parameter error
				while(*defaultValue!='\0'){
					Lcd1602_Write_Data(*defaultValue);
					defaultValue++;
				}					
	}	
}


/******************************************************************************/
// 函数名称：Lcd1602_Busy_Check 
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602忙信号检查 
/******************************************************************************/
void Lcd1602_Busy_Check(void){
	uint8 tmp;
	lcdPort = 0xff;//一开始的时候，lcdPort设置成输入状态

	do{
		RS = 0;
		RW = 1;
		EN = 0;
		EN = 1;
		_nop_();
		_nop_();
		tmp = lcdPort;
		_nop_();
		EN = 0;
		_nop_();
	}while(tmp&0x80);	
}
/******************************************************************************/
// 函数名称：Lcd1602_Init 
// 输入参数：无
// 输出参数：无 
// 函数功能：LCD1602初始化
/******************************************************************************/
void Lcd1602_Init(void){
	Delay15ms();
	Lcd1602_Write_Cmd(0x38);//写指令38H
	Delay5ms();	
	Lcd1602_Write_Cmd(0x38);//显示模式设置	
	Lcd1602_Write_Cmd(0x08);//显示关闭	
	Lcd1602_Write_Cmd(0x01);//显示清屏	
	Lcd1602_Write_Cmd(0x06);//显示光标移动设置	
	Lcd1602_Write_Cmd(0x0c);//显示开及光标设置
}
/******************************************************************************/
// 函数名称：Lcd1602_Write_Cmd 
// 输入参数：cmd-指令
// 输出参数：无 
// 函数功能：LCD1602写指令
/******************************************************************************/
void Lcd1602_Write_Cmd(uint8 cmd){
	Lcd1602_Busy_Check();
	RS = 0;
	RW = 0;
	EN = 0;
	lcdPort = cmd;
	_nop_();
	EN = 1;
	_nop_();
	EN = 0;
	_nop_();
	_nop_();
}


/******************************************************************************/
// 函数名称：Lcd1602_Write_Data 
// 输入参数：Data-数据
// 输出参数：无 
// 函数功能：LCD1602写数据
/******************************************************************************/
void Lcd1602_Write_Data(uint8 Data){
	Lcd1602_Busy_Check();
	RS = 1;
	RW = 0;
	EN = 0;
	lcdPort = Data;
	_nop_();
	EN = 1;
	_nop_();
	EN = 0;
	_nop_();
	_nop_();
}