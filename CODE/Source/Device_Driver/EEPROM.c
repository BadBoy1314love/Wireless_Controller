
#include "Config.h"
#include "intrins.h"
#include "EEPROM.h"

/******************************************************************************/
// 函数名称：IapIdle
// 输入参数：无
// 输出参数：无 
// 函数功能：禁用（关闭） ISP/IAP/EEPROM , 使单片机处于安全状态
/******************************************************************************/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //Clear command to standby
    IAP_TRIG = 0;                   //清除触发器寄存器
    IAP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    IAP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}

/******************************************************************************/
// 函数名称：IapReadByte
// 输入参数：addr-扇区单元地址
// 输出参数：dat-读出的数据
// 函数功能：从 ISP/IAP/EEPROM 读出一字节
/******************************************************************************/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //Data buffer

    IAP_CONTR = ENABLE_IAP;         //打开IAP功能，设置等待时间
    IAP_CMD = CMD_READ;             //设置ISP/IAP/EEPROM 读命令
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //单片机将保持在这里，直到ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读取 ISP/IAP/EEPROM 数据
    IapIdle();                      //关闭ISP/IAP/EEPROM功能

    return dat;                     //返回Flash数据
}

/******************************************************************************/
// 函数名称：IapProgramByte
// 输入参数：addr-扇区单元地址，dat-待写入的数据
// 输出参数：无
// 函数功能：写入一字节到 ISP/IAP/EEPROM 
/******************************************************************************/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //打开IAP功能，设置等待时间
    IAP_CMD = CMD_PROGRAM;          //设置ISP/IAP/EEPROM 编程命令
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_DATA = dat;                 //写 ISP/IAP/EEPROM 数据
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //单片机将保持在这里，直到ISP/IAP/EEPROM操作完成
    IapIdle();											//关闭ISP/IAP/EEPROM功能
}


/******************************************************************************/
// 函数名称：IapEraseSector
// 输入参数：addr-某一扇区首地址
// 输出参数：无
// 函数功能：擦除某一扇区（每个扇区512字节）
/******************************************************************************/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //打开IAP功能，设置等待时间
    IAP_CMD = CMD_ERASE;            //设置 ISP/IAP/EEPROM 擦除命令
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //单片机将保持在这里，直到ISP/IAP/EEPROM操作完成
    IapIdle();
}