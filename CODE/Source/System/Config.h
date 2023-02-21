/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "STC12C5A60S2.H"
#include "intrins.h"

/******************************************************************************/
// 类型定义
/******************************************************************************/
typedef unsigned char u8; //0 to 255
typedef unsigned int  u16;  //0 — 65535
typedef unsigned long u32;   //0 — 4294967295

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;
typedef signed char   int8;
typedef signed int    int16;
typedef signed long   int32;

typedef unsigned char tByte;
typedef unsigned int  tWord;
typedef unsigned long tLong;

typedef unsigned char BYTE;
typedef unsigned int  WORD;

typedef signed char		s8;  //–128 to 127
typedef signed int		s16;  //-32768 — 32767
typedef signed long		s32;  //-2147483648 — 2147483647


#define INTERRUPT_Timer_0_Overflow 1
#define INTERRUPT_Timer_1_Overflow 3
#define INTERRUPT_Timer_2_Overflow 5

#define INTERRUPT_EXTERNAL_0 0
#define INTERRUPT_EXTERNAL_1 2
#define INTERRUPT_UART_Rx_Tx 4

#define  ENABLE   1
#define  DISABLE  0

/******************************************************************************/
// LCD1602引脚配置
/******************************************************************************/
sbit RS = P2^5;
sbit RW = P2^6;
sbit EN = P2^7;
#define lcdPort P0 //LCD1602双向数据端口

/******************************************************************************/
// 继电器引脚配置
/******************************************************************************/
sbit RelayA = P1^0;
sbit RelayB = P1^1;

/******************************************************************************/
// EC11编码器引脚配置
/******************************************************************************/
sbit EC11_Key = P3^2;
sbit EC11_A = P3^3;
sbit EC11_B = P3^4;

/******************************************************************************/
// 无源蜂鸣器引脚配置
/******************************************************************************/
sbit Buzzer = P4^5;



