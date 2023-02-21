
#include "Config.h"
#include "intrins.h"
#include "EEPROM.h"

/******************************************************************************/
// �������ƣ�IapIdle
// �����������
// ����������� 
// �������ܣ����ã��رգ� ISP/IAP/EEPROM , ʹ��Ƭ�����ڰ�ȫ״̬
/******************************************************************************/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //Clear command to standby
    IAP_TRIG = 0;                   //����������Ĵ���
    IAP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    IAP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}

/******************************************************************************/
// �������ƣ�IapReadByte
// ���������addr-������Ԫ��ַ
// ���������dat-����������
// �������ܣ��� ISP/IAP/EEPROM ����һ�ֽ�
/******************************************************************************/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //Data buffer

    IAP_CONTR = ENABLE_IAP;         //��IAP���ܣ����õȴ�ʱ��
    IAP_CMD = CMD_READ;             //����ISP/IAP/EEPROM ������
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //��Ƭ�������������ֱ��ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ȡ ISP/IAP/EEPROM ����
    IapIdle();                      //�ر�ISP/IAP/EEPROM����

    return dat;                     //����Flash����
}

/******************************************************************************/
// �������ƣ�IapProgramByte
// ���������addr-������Ԫ��ַ��dat-��д�������
// �����������
// �������ܣ�д��һ�ֽڵ� ISP/IAP/EEPROM 
/******************************************************************************/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //��IAP���ܣ����õȴ�ʱ��
    IAP_CMD = CMD_PROGRAM;          //����ISP/IAP/EEPROM �������
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_DATA = dat;                 //д ISP/IAP/EEPROM ����
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //��Ƭ�������������ֱ��ISP/IAP/EEPROM�������
    IapIdle();											//�ر�ISP/IAP/EEPROM����
}


/******************************************************************************/
// �������ƣ�IapEraseSector
// ���������addr-ĳһ�����׵�ַ
// �����������
// �������ܣ�����ĳһ������ÿ������512�ֽڣ�
/******************************************************************************/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //��IAP���ܣ����õȴ�ʱ��
    IAP_CMD = CMD_ERASE;            //���� ISP/IAP/EEPROM ��������
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //��Ƭ�������������ֱ��ISP/IAP/EEPROM�������
    IapIdle();
}