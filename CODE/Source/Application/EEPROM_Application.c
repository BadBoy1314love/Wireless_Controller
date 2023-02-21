#include "Config.h"
#include "EEPROM.h"
#include "EEPROM_Application.h"
#include "ESP8266.h"


u16 xdata EepromSta = 0;
u16 xdata EepromAp = 0;

//Ĭ��������Ϣ
u8 code ATCIPSERVER_Default[]="AT+CIPSERVER=1,00001\r\n";
u8 code STA_MODE_Table_Default[]="AT+CWJAP_CUR=\"TP-LINK_847A\",\"asdfghjkl\"\r\n        ";
u8 code AP_MODE_Table_Default[]="AT+CWSAP_CUR=\"Wireless_Controller\",\"asdfghjkl\",3,4\r\n       ";

/*ʱ�������Ъģʽ*/

//����������
extern bdata u8 Task_OverTime_Reset;

/*����һ*/
extern s16 xdata Task1_StartTime;//����1��ʼ����ʱ��
extern s16 xdata Task1_EndTime;//����1��������ʱ��
extern s32 xdata Task1_OverTime; //����1���г�ʱʱ��
//extern bit Task1_OverTime_Reset; //����1���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task1_OnTime;  //��ʾTask1���ON״̬��ʱ��
extern s32 xdata Task1_OffTime; //��ʾTask1���OFF״̬��ʱ��

/*�����*/
extern s16 xdata Task2_StartTime;//����2��ʼ����ʱ��
extern s16 xdata Task2_EndTime;//����2��������ʱ��
extern s32 xdata Task2_OverTime; //����2���г�ʱʱ��
//extern bit Task2_OverTime_Reset; //����2���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task2_OnTime;  //��ʾTask2���ON״̬��ʱ��
extern s32 xdata Task2_OffTime; //��ʾTask2���OFF״̬��ʱ��


/*������*/
extern s16 xdata Task3_StartTime;//����3��ʼ����ʱ��
extern s16 xdata Task3_EndTime;//����3��������ʱ��
extern s32 xdata Task3_OverTime; //����3���г�ʱʱ��
//extern bit Task3_OverTime_Reset; //����3���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task3_OnTime;  //��ʾTask3���ON״̬��ʱ��
extern s32 xdata Task3_OffTime; //��ʾTask3���OFF״̬��ʱ��


/*������*/
extern s16 xdata Task4_StartTime;//����4��ʼ����ʱ��
extern s16 xdata Task4_EndTime;//����4��������ʱ��
extern s32 xdata Task4_OverTime; //����4���г�ʱʱ��
//extern bit Task4_OverTime_Reset; //����4���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task4_OnTime;  //��ʾTask4���ON״̬��ʱ��
extern s32 xdata Task4_OffTime; //��ʾTask4���OFF״̬��ʱ��

/*������*/
extern s16 xdata Task5_StartTime;//����5��ʼ����ʱ��
extern s16 xdata Task5_EndTime;//����5��������ʱ��
extern s32 xdata Task5_OverTime; //����5���г�ʱʱ��
//extern bit Task5_OverTime_Reset; //����5���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task5_OnTime;  //��ʾTask5���ON״̬��ʱ��
extern s32 xdata Task5_OffTime; //��ʾTask5���OFF״̬��ʱ��

/*������*/
extern s16 xdata Task6_StartTime;//����6��ʼ����ʱ��
extern s16 xdata Task6_EndTime;//����6��������ʱ��
extern s32 xdata Task6_OverTime; //����6���г�ʱʱ��
//extern bit Task6_OverTime_Reset; //����6���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task6_OnTime;  //��ʾTask6���ON״̬��ʱ��
extern s32 xdata Task6_OffTime; //��ʾTask6���OFF״̬��ʱ��

/*�˿ڵĴ���ģʽ*/
extern bdata u16 Pin_Trigger_Mode;

/*�˿ڵ��������ģʽ*/
extern bdata u16 Pin_Mode;

/*�˿ڹ��������*/
extern s8 xdata Pin10_Task_Number;
extern s8 xdata Pin11_Task_Number;

extern s8 xdata Pin12_Task_Number; 
extern s8 xdata Pin13_Task_Number;
extern s8 xdata Pin14_Task_Number;
extern s8 xdata Pin15_Task_Number;
extern s8 xdata Pin16_Task_Number;
extern s8 xdata Pin17_Task_Number;

extern s8 xdata Pin20_Task_Number;
extern s8 xdata Pin21_Task_Number;
extern s8 xdata Pin22_Task_Number;
extern s8 xdata Pin23_Task_Number;
extern s8 xdata Pin24_Task_Number;

extern s8 xdata Pin35_Task_Number;
extern s8 xdata Pin36_Task_Number;
extern s8 xdata Pin37_Task_Number;

/*����TCP��������Ϣ*/
extern u8 xdata ATCIPSERVER[]; //="AT+CIPSERVER=1,65535";
/*TCP�������˿�*/
extern s32 xdata TcpServerPort;// = 65535;

/*STA AP��Ϣ*/
extern u8 xdata STA_MODE_Table[]; //={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\""};
extern u8 xdata AP_MODE_Table[];  //={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4"};

//extern bdata�Ͳ���
//Task_OverTime_Reset
extern bit Task1_OverTime_Reset;
extern bit Task2_OverTime_Reset;
extern bit Task3_OverTime_Reset;
extern bit Task4_OverTime_Reset;
extern bit Task5_OverTime_Reset;
extern bit Task6_OverTime_Reset;

//����ģʽ��0Ϊ����ģʽ����1Ϊ����ģʽ��
//����ģʽ���������£��ͷŲŻ��������״̬
//����ģʽ���������£����̸�������״̬�������ͷŲſ����¸���
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


//����ģʽʱ��Ϊ�˿ڴ������������ 
//���ģʽʱѡ����������
//�˿�ģʽ��0Ϊ����ģʽ����1Ϊ���ģʽ��
extern bit Pin10_Mode;
extern bit Pin11_Mode;

extern bit Pin12_Mode;
extern bit Pin13_Mode;
extern bit Pin14_Mode;
extern bit Pin15_Mode;
extern bit Pin16_Mode;
extern bit Pin17_Mode;

extern bit Pin20_Mode;
extern bit Pin21_Mode;
extern bit Pin22_Mode;
extern bit Pin23_Mode;
extern bit Pin24_Mode;

extern bit Pin35_Mode;
extern bit Pin36_Mode;
extern bit Pin37_Mode;


/******************************************************************************/
// �������ƣ�EEPROM_Program_Sector_1 
// �����������
// ����������� 
// �������ܣ�EEPROM��̵�һ��������д�������ֵ
/******************************************************************************/
void EEPROM_Program_Sector_1()
{
	IapEraseSector(IAP_ADDRESS_SECTOR_1); //������һ����
	
	//��������1
	IapProgramByte(0x0000,Task1_StartTime>>8);
	IapProgramByte(0x0001,Task1_StartTime);
	
	IapProgramByte(0x0002,Task1_EndTime>>8);
	IapProgramByte(0x0003,Task1_EndTime);
	
	IapProgramByte(0x0004,Task1_OverTime>>24);
	IapProgramByte(0x0005,Task1_OverTime>>16);
	IapProgramByte(0x0006,Task1_OverTime>>8);
	IapProgramByte(0x0007,Task1_OverTime);
	
	IapProgramByte(0x0008,Task1_OnTime>>24);
	IapProgramByte(0x0009,Task1_OnTime>>16);
	IapProgramByte(0x000A,Task1_OnTime>>8);
	IapProgramByte(0x000B,Task1_OnTime);
	
	IapProgramByte(0x000C,Task1_OffTime>>24);
	IapProgramByte(0x000D,Task1_OffTime>>16);
	IapProgramByte(0x000E,Task1_OffTime>>8);
	IapProgramByte(0x000F,Task1_OffTime);
	
	//��������2
	IapProgramByte(0x0010,Task2_StartTime>>8);
	IapProgramByte(0x0011,Task2_StartTime);
	
	IapProgramByte(0x0012,Task2_EndTime>>8);
	IapProgramByte(0x0013,Task2_EndTime);
	
	IapProgramByte(0x0014,Task2_OverTime>>24);
	IapProgramByte(0x0015,Task2_OverTime>>16);
	IapProgramByte(0x0016,Task2_OverTime>>8);
	IapProgramByte(0x0017,Task2_OverTime);
	
	IapProgramByte(0x0018,Task2_OnTime>>24);
	IapProgramByte(0x0019,Task2_OnTime>>16);
	IapProgramByte(0x001A,Task2_OnTime>>8);
	IapProgramByte(0x001B,Task2_OnTime);
	
	IapProgramByte(0x001C,Task2_OffTime>>24);
	IapProgramByte(0x001D,Task2_OffTime>>16);
	IapProgramByte(0x001E,Task2_OffTime>>8);
	IapProgramByte(0x001F,Task2_OffTime);
	
	//��������3
	IapProgramByte(0x0020,Task3_StartTime>>8);
	IapProgramByte(0x0021,Task3_StartTime);
	
	IapProgramByte(0x0022,Task3_EndTime>>8);
	IapProgramByte(0x0023,Task3_EndTime);
	
	IapProgramByte(0x0024,Task3_OverTime>>24);
	IapProgramByte(0x0025,Task3_OverTime>>16);
	IapProgramByte(0x0026,Task3_OverTime>>8);
	IapProgramByte(0x0027,Task3_OverTime);
	
	IapProgramByte(0x0028,Task3_OnTime>>24);
	IapProgramByte(0x0029,Task3_OnTime>>16);
	IapProgramByte(0x002A,Task3_OnTime>>8);
	IapProgramByte(0x002B,Task3_OnTime);
	
	IapProgramByte(0x002C,Task3_OffTime>>24);
	IapProgramByte(0x002D,Task3_OffTime>>16);
	IapProgramByte(0x002E,Task3_OffTime>>8);
	IapProgramByte(0x002F,Task3_OffTime);
	
	//��������4
	IapProgramByte(0x0030,Task4_StartTime>>8);
	IapProgramByte(0x0031,Task4_StartTime);
	
	IapProgramByte(0x0032,Task4_EndTime>>8);
	IapProgramByte(0x0033,Task4_EndTime);
	
	IapProgramByte(0x0034,Task4_OverTime>>24);
	IapProgramByte(0x0035,Task4_OverTime>>16);
	IapProgramByte(0x0036,Task4_OverTime>>8);
	IapProgramByte(0x0037,Task4_OverTime);
	
	IapProgramByte(0x0038,Task4_OnTime>>24);
	IapProgramByte(0x0039,Task4_OnTime>>16);
	IapProgramByte(0x003A,Task4_OnTime>>8);
	IapProgramByte(0x003B,Task4_OnTime);
	
	IapProgramByte(0x003C,Task4_OffTime>>24);
	IapProgramByte(0x003D,Task4_OffTime>>16);
	IapProgramByte(0x003E,Task4_OffTime>>8);
	IapProgramByte(0x003F,Task4_OffTime);
	
	//��������5
	IapProgramByte(0x0040,Task5_StartTime>>8);
	IapProgramByte(0x0041,Task5_StartTime);
	
	IapProgramByte(0x0042,Task5_EndTime>>8);
	IapProgramByte(0x0043,Task5_EndTime);
	
	IapProgramByte(0x0044,Task5_OverTime>>24);
	IapProgramByte(0x0045,Task5_OverTime>>16);
	IapProgramByte(0x0046,Task5_OverTime>>8);
	IapProgramByte(0x0047,Task5_OverTime);
	
	IapProgramByte(0x0048,Task5_OnTime>>24);
	IapProgramByte(0x0049,Task5_OnTime>>16);
	IapProgramByte(0x004A,Task5_OnTime>>8);
	IapProgramByte(0x004B,Task5_OnTime);
	
	IapProgramByte(0x004C,Task5_OffTime>>24);
	IapProgramByte(0x004D,Task5_OffTime>>16);
	IapProgramByte(0x004E,Task5_OffTime>>8);
	IapProgramByte(0x004F,Task5_OffTime);
	
	//��������6
	IapProgramByte(0x0050,Task6_StartTime>>8);
	IapProgramByte(0x0051,Task6_StartTime);
	
	IapProgramByte(0x0052,Task6_EndTime>>8);
	IapProgramByte(0x0053,Task6_EndTime);
	
	IapProgramByte(0x0054,Task6_OverTime>>24);
	IapProgramByte(0x0055,Task6_OverTime>>16);
	IapProgramByte(0x0056,Task6_OverTime>>8);
	IapProgramByte(0x0057,Task6_OverTime);
	
	IapProgramByte(0x0058,Task6_OnTime>>24);
	IapProgramByte(0x0059,Task6_OnTime>>16);
	IapProgramByte(0x005A,Task6_OnTime>>8);
	IapProgramByte(0x005B,Task6_OnTime);
	
	IapProgramByte(0x005C,Task6_OffTime>>24);
	IapProgramByte(0x005D,Task6_OffTime>>16);
	IapProgramByte(0x005E,Task6_OffTime>>8);
	IapProgramByte(0x005F,Task6_OffTime);
	
	//���ó�ʱ��λģʽ
	IapProgramByte(0x0060,Task_OverTime_Reset);
	
	//���ö˿ڵĴ���ģʽ
	IapProgramByte(0x0061,Pin_Trigger_Mode>>8);
	IapProgramByte(0x0062,Pin_Trigger_Mode);
		
	//���ö˿ڵ��������ģʽ
	IapProgramByte(0x0063,Pin_Mode>>8);
	IapProgramByte(0x0064,Pin_Mode);
	
	//���ö˿ڹ��������
	IapProgramByte(0x0065,Pin10_Task_Number);
	IapProgramByte(0x0066,Pin11_Task_Number);
	
	IapProgramByte(0x0067,Pin12_Task_Number);
	IapProgramByte(0x0068,Pin13_Task_Number);
	IapProgramByte(0x0069,Pin14_Task_Number);
	IapProgramByte(0x006A,Pin15_Task_Number);
	IapProgramByte(0x006B,Pin16_Task_Number);
	IapProgramByte(0x006C,Pin17_Task_Number);
	
	IapProgramByte(0x006D,Pin20_Task_Number);
	IapProgramByte(0x006E,Pin21_Task_Number);
	IapProgramByte(0x006F,Pin22_Task_Number);
	IapProgramByte(0x0070,Pin23_Task_Number);
	IapProgramByte(0x0071,Pin24_Task_Number);
	
	IapProgramByte(0x0072,Pin35_Task_Number);
	IapProgramByte(0x0073,Pin36_Task_Number);
	IapProgramByte(0x0074,Pin37_Task_Number);
	
	//����TCP�������˿�
	IapProgramByte(0x0075,TcpServerPort>>8);
	IapProgramByte(0x0076,TcpServerPort);
	//����ATָ��TCP�������˿�
	IapProgramByte(0x0077,ATCIPSERVER[15]);
	IapProgramByte(0x0078,ATCIPSERVER[16]);
	IapProgramByte(0x0079,ATCIPSERVER[17]);
	IapProgramByte(0x007A,ATCIPSERVER[18]);
	IapProgramByte(0x007B,ATCIPSERVER[19]);
	
	//д��STA��Ϣ
	//124-0x007C  274-0x0112
	for(EepromSta=124;EepromSta<274;EepromSta++){
		 IapProgramByte(EepromSta,STA_MODE_Table[EepromSta-124]);
	}
	
	//д��AP��Ϣ
	//274-0x0112 424-0x01A8
	for(EepromAp=274;EepromAp<424;EepromAp++){
		 IapProgramByte(EepromAp,AP_MODE_Table[EepromAp-274]);
	}
	
}
/******************************************************************************/
// �������ƣ�EEPROM_Program_Sector_2 
// �����������
// ����������� 
// �������ܣ�EEPROM��̵ڶ���������д�������ֵ
/******************************************************************************/
/*
void EEPROM_Program_Sector_2()
{
	
}
*/
/******************************************************************************/
// �������ƣ�EEPROM_Read_Sector_1 
// �����������
// ����������� 
// �������ܣ�EEPROM��ȡ��һ�����������ز�����ֵ
/******************************************************************************/
void EEPROM_Read_Sector_1()
{

	//��ȡ����һ
	Task1_StartTime = IapReadByte(0x0000);
	Task1_StartTime = (Task1_StartTime<<8)|IapReadByte(0x0001);
	
	Task1_EndTime = IapReadByte(0x0002);
	Task1_EndTime = (Task1_EndTime<<8)|IapReadByte(0x0003);

	Task1_OverTime = IapReadByte(0x0004);
	Task1_OverTime = (Task1_OverTime<<8)|IapReadByte(0x0005);
	Task1_OverTime = (Task1_OverTime<<8)|IapReadByte(0x0006);
	Task1_OverTime = (Task1_OverTime<<8)|IapReadByte(0x0007);
	
	Task1_OnTime = IapReadByte(0x0008);
	Task1_OnTime = (Task1_OnTime<<8)|IapReadByte(0x0009);
	Task1_OnTime = (Task1_OnTime<<8)|IapReadByte(0x000A);
	Task1_OnTime = (Task1_OnTime<<8)|IapReadByte(0x000B);
	
	Task1_OffTime = IapReadByte(0x000C);
	Task1_OffTime = (Task1_OffTime<<8)|IapReadByte(0x000D);
	Task1_OffTime = (Task1_OffTime<<8)|IapReadByte(0x000E);
	Task1_OffTime = (Task1_OffTime<<8)|IapReadByte(0x000F);
	
	//��ȡ�����
	Task2_StartTime = IapReadByte(0x0010);
	Task2_StartTime = (Task2_StartTime<<8)|IapReadByte(0x0011);
	
	Task2_EndTime = IapReadByte(0x0012);
	Task2_EndTime = (Task2_EndTime<<8)|IapReadByte(0x0013);

	Task2_OverTime = IapReadByte(0x0014);
	Task2_OverTime = (Task2_OverTime<<8)|IapReadByte(0x0015);
	Task2_OverTime = (Task2_OverTime<<8)|IapReadByte(0x0016);
	Task2_OverTime = (Task2_OverTime<<8)|IapReadByte(0x0017);
	
	Task2_OnTime = IapReadByte(0x0018);
	Task2_OnTime = (Task2_OnTime<<8)|IapReadByte(0x0019);
	Task2_OnTime = (Task2_OnTime<<8)|IapReadByte(0x001A);
	Task2_OnTime = (Task2_OnTime<<8)|IapReadByte(0x001B);
	
	Task2_OffTime = IapReadByte(0x001C);
	Task2_OffTime = (Task2_OffTime<<8)|IapReadByte(0x001D);
	Task2_OffTime = (Task2_OffTime<<8)|IapReadByte(0x001E);
	Task2_OffTime = (Task2_OffTime<<8)|IapReadByte(0x001F);
	
	//��ȡ������
	Task3_StartTime = IapReadByte(0x0020);
	Task3_StartTime = (Task3_StartTime<<8)|IapReadByte(0x0021);
	
	Task3_EndTime = IapReadByte(0x0022);
	Task3_EndTime = (Task3_EndTime<<8)|IapReadByte(0x0023);

	Task3_OverTime = IapReadByte(0x0024);
	Task3_OverTime = (Task3_OverTime<<8)|IapReadByte(0x0025);
	Task3_OverTime = (Task3_OverTime<<8)|IapReadByte(0x0026);
	Task3_OverTime = (Task3_OverTime<<8)|IapReadByte(0x0027);
	
	Task3_OnTime = IapReadByte(0x0028);
	Task3_OnTime = (Task3_OnTime<<8)|IapReadByte(0x0029);
	Task3_OnTime = (Task3_OnTime<<8)|IapReadByte(0x002A);
	Task3_OnTime = (Task3_OnTime<<8)|IapReadByte(0x002B);
	
	Task3_OffTime = IapReadByte(0x002C);
	Task3_OffTime = (Task3_OffTime<<8)|IapReadByte(0x002D);
	Task3_OffTime = (Task3_OffTime<<8)|IapReadByte(0x002E);
	Task3_OffTime = (Task3_OffTime<<8)|IapReadByte(0x002F);
	
	//��ȡ������
	Task4_StartTime = IapReadByte(0x0030);
	Task4_StartTime = (Task4_StartTime<<8)|IapReadByte(0x0031);
	
	Task4_EndTime = IapReadByte(0x0032);
	Task4_EndTime = (Task4_EndTime<<8)|IapReadByte(0x0033);

	Task4_OverTime = IapReadByte(0x0034);
	Task4_OverTime = (Task4_OverTime<<8)|IapReadByte(0x0035);
	Task4_OverTime = (Task4_OverTime<<8)|IapReadByte(0x0036);
	Task4_OverTime = (Task4_OverTime<<8)|IapReadByte(0x0037);
	
	Task4_OnTime = IapReadByte(0x0038);
	Task4_OnTime = (Task4_OnTime<<8)|IapReadByte(0x0039);
	Task4_OnTime = (Task4_OnTime<<8)|IapReadByte(0x003A);
	Task4_OnTime = (Task4_OnTime<<8)|IapReadByte(0x003B);
	
	Task4_OffTime = IapReadByte(0x003C);
	Task4_OffTime = (Task4_OffTime<<8)|IapReadByte(0x003D);
	Task4_OffTime = (Task4_OffTime<<8)|IapReadByte(0x003E);
	Task4_OffTime = (Task4_OffTime<<8)|IapReadByte(0x003F);
	
	//��ȡ������
	Task5_StartTime = IapReadByte(0x0040);
	Task5_StartTime = (Task5_StartTime<<8)|IapReadByte(0x0041);
	
	Task5_EndTime = IapReadByte(0x0042);
	Task5_EndTime = (Task5_EndTime<<8)|IapReadByte(0x0043);

	Task5_OverTime = IapReadByte(0x0044);
	Task5_OverTime = (Task5_OverTime<<8)|IapReadByte(0x0045);
	Task5_OverTime = (Task5_OverTime<<8)|IapReadByte(0x0046);
	Task5_OverTime = (Task5_OverTime<<8)|IapReadByte(0x0047);
	
	Task5_OnTime = IapReadByte(0x0048);
	Task5_OnTime = (Task5_OnTime<<8)|IapReadByte(0x0049);
	Task5_OnTime = (Task5_OnTime<<8)|IapReadByte(0x004A);
	Task5_OnTime = (Task5_OnTime<<8)|IapReadByte(0x004B);
	
	Task5_OffTime = IapReadByte(0x004C);
	Task5_OffTime = (Task5_OffTime<<8)|IapReadByte(0x004D);
	Task5_OffTime = (Task5_OffTime<<8)|IapReadByte(0x004E);
	Task5_OffTime = (Task5_OffTime<<8)|IapReadByte(0x004F);
	
	//��ȡ������
	Task6_StartTime = IapReadByte(0x0050);
	Task6_StartTime = (Task6_StartTime<<8)|IapReadByte(0x0051);
	
	Task6_EndTime = IapReadByte(0x0052);
	Task6_EndTime = (Task6_EndTime<<8)|IapReadByte(0x0053);

	Task6_OverTime = IapReadByte(0x0054);
	Task6_OverTime = (Task6_OverTime<<8)|IapReadByte(0x0055);
	Task6_OverTime = (Task6_OverTime<<8)|IapReadByte(0x0056);
	Task6_OverTime = (Task6_OverTime<<8)|IapReadByte(0x0057);
	
	Task6_OnTime = IapReadByte(0x0058);
	Task6_OnTime = (Task6_OnTime<<8)|IapReadByte(0x0059);
	Task6_OnTime = (Task6_OnTime<<8)|IapReadByte(0x005A);
	Task6_OnTime = (Task6_OnTime<<8)|IapReadByte(0x005B);
	
	Task6_OffTime = IapReadByte(0x005C);
	Task6_OffTime = (Task6_OffTime<<8)|IapReadByte(0x005D);
	Task6_OffTime = (Task6_OffTime<<8)|IapReadByte(0x005E);
	Task6_OffTime = (Task6_OffTime<<8)|IapReadByte(0x005F);
	
	//���������񣬶�ȡ��ʱ��λģʽ
	Task_OverTime_Reset = IapReadByte(0x0060);
	
	//��ȡ�˿ڵĴ���ģʽ
	Pin_Trigger_Mode = IapReadByte(0x0061);
	Pin_Trigger_Mode = (Pin_Trigger_Mode<<8)|IapReadByte(0x0062);
	
	//��ȡ�˿��������ģʽ
	Pin_Mode = IapReadByte(0x0063);
	Pin_Mode = (Pin_Mode<<8)|IapReadByte(0x0064);
	
	//���ö˿ڹ��������
	Pin10_Task_Number = IapReadByte(0x0065);
	Pin11_Task_Number = IapReadByte(0x0066);
	
	Pin12_Task_Number = IapReadByte(0x0067);
	Pin13_Task_Number = IapReadByte(0x0068);
	Pin14_Task_Number = IapReadByte(0x0069);
	Pin15_Task_Number = IapReadByte(0x006A);
	Pin16_Task_Number = IapReadByte(0x006B);
	Pin17_Task_Number = IapReadByte(0x006C);
	
	Pin20_Task_Number = IapReadByte(0x006D);
	Pin21_Task_Number = IapReadByte(0x006E);
	Pin22_Task_Number = IapReadByte(0x006F);
	Pin23_Task_Number = IapReadByte(0x0070);
	Pin24_Task_Number = IapReadByte(0x0071);
	
	Pin35_Task_Number = IapReadByte(0x0072);
	Pin36_Task_Number = IapReadByte(0x0073);
	Pin37_Task_Number = IapReadByte(0x0074);
	
	//��ȡTCP�������˿�
	TcpServerPort = IapReadByte(0x0075);
	TcpServerPort = (TcpServerPort<<8)|IapReadByte(0x0076);
	//��ȡָ��TCP�������˿�
	ATCIPSERVER[15] = IapReadByte(0x0077);
	ATCIPSERVER[16] = IapReadByte(0x0078);
	ATCIPSERVER[17] = IapReadByte(0x0079);
	ATCIPSERVER[18] = IapReadByte(0x007A);
	ATCIPSERVER[19] = IapReadByte(0x007B);
	
	
	//��ȡSTA��Ϣ
	//124-0x007C 274-0x0112
	for(EepromSta=124;EepromSta<274;EepromSta++){
		 STA_MODE_Table[EepromSta-124] = IapReadByte(EepromSta);
	}
	
	//��ȡAP��Ϣ
	//274-0x0112 424-0x01A8
	for(EepromAp=274;EepromAp<424;EepromAp++){
		 AP_MODE_Table[EepromAp-274] = IapReadByte(EepromAp);
	}
	
}
/******************************************************************************/
// �������ƣ�EEPROM_Read_Sector_2 
// �����������
// ����������� 
// �������ܣ�EEPROM��ȡ�ڶ������������ز�����ֵ
/******************************************************************************/
/*
void EEPROM_Read_Sector_2()
{
	
}
*/

/******************************************************************************/
// �������ƣ�SYSTEM_DATA_RESET 
// �����������
// ����������� 
// �������ܣ�������ϵͳ��������Ϊȷ��������
/******************************************************************************/
void SYSTEM_DATA_RESET()
{
	static u8 i = 0; 
	//��������趨
	//����һ
	Task1_StartTime = 0;//����1��ʼ����ʱ��
	Task1_EndTime = 1439;//����1��������ʱ��
	Task1_OverTime = 2*3000; //����1���г�ʱʱ��
	Task1_OverTime_Reset = 0; //����1���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task1_OnTime = 2*1;  //��ʾTask1���ON״̬��ʱ��
	Task1_OffTime = 2*1; //��ʾTask1���OFF״̬��ʱ��

	//�����
	Task2_StartTime = 0;//����2��ʼ����ʱ��
	Task2_EndTime = 1439;//����2��������ʱ��
	Task2_OverTime =2*3000; //����2���г�ʱʱ��
	Task2_OverTime_Reset = 0; //����2���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task2_OnTime = 2*1;  //��ʾTask2���ON״̬��ʱ��
	Task2_OffTime = 2*1; //��ʾTask2���OFF״̬��ʱ��


	//������
	Task3_StartTime = 0;//����3��ʼ����ʱ��
	Task3_EndTime = 1439;//����3��������ʱ��
	Task3_OverTime = 2*3000; //����3���г�ʱʱ��
	Task3_OverTime_Reset = 0; //����3���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task3_OnTime = 2*1;  //��ʾTask3���ON״̬��ʱ��
	Task3_OffTime = 2*1; //��ʾTask3���OFF״̬��ʱ��


	//������
	Task4_StartTime = 0;//����4��ʼ����ʱ��
	Task4_EndTime = 1439;//����4��������ʱ��
	Task4_OverTime = 2*3000; //����4���г�ʱʱ��
	Task4_OverTime_Reset = 0; //����4���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task4_OnTime = 2*1;  //��ʾTask4���ON״̬��ʱ��
	Task4_OffTime = 2*1; //��ʾTask4���OFF״̬��ʱ��

	//������
	Task5_StartTime = 0;//����5��ʼ����ʱ��
	Task5_EndTime = 1439;//����5��������ʱ��
	Task5_OverTime = 2*3000; //����5���г�ʱʱ��
	Task5_OverTime_Reset = 0; //����5���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task5_OnTime = 2*1;  //��ʾTask5���ON״̬��ʱ��
	Task5_OffTime = 2*1; //��ʾTask5���OFF״̬��ʱ��

	//������
	Task6_StartTime = 0;//����6��ʼ����ʱ��
	Task6_EndTime = 1439;//����6��������ʱ��
	Task6_OverTime = 2*3000; //����6���г�ʱʱ��
	Task6_OverTime_Reset = 0; //����6���г�ʱ�Զ���λ����λ
																//���ڿ��������Ƿ���������
																//1:�Զ���λ ������ʱ����λ��ʱ������������������
																//0:���Զ���λ ����ʱ���ر�

	Task6_OnTime = 2*1;  //��ʾTask6���ON״̬��ʱ��
	Task6_OffTime = 2*1; //��ʾTask6���OFF״̬��ʱ��

	//�˿ڵĴ���ģʽ
	//����ģʽ��0Ϊ����ģʽ����1Ϊ����ģʽ��
	//����ģʽ���������£��ͷŲŻ��������״̬
	//����ģʽ���������£����̸�������״̬�������ͷŲſ����¸���
	Pin10_Trigger_Mode = 0;
	Pin11_Trigger_Mode = 0;

	Pin12_Trigger_Mode = 0;
	Pin13_Trigger_Mode = 0;
	Pin14_Trigger_Mode = 0;
	Pin15_Trigger_Mode = 0;
	Pin16_Trigger_Mode = 0;
	Pin17_Trigger_Mode = 0;

	Pin20_Trigger_Mode = 0;
	Pin21_Trigger_Mode = 0;
	Pin22_Trigger_Mode = 0;
	Pin23_Trigger_Mode = 0;
	Pin24_Trigger_Mode = 0;

	Pin35_Trigger_Mode = 0;
	Pin36_Trigger_Mode = 0;
	Pin37_Trigger_Mode = 0;

	//�˿ڵ��������ģʽ
	//����ģʽʱ��Ϊ�˿ڴ������������ 
	//���ģʽʱѡ����������
	//�˿�ģʽ��0Ϊ����ģʽ����1Ϊ���ģʽ��
	Pin10_Mode = 1;
	Pin11_Mode = 1;

	Pin12_Mode = 0;
	Pin13_Mode = 0;
	Pin14_Mode = 0;
	Pin15_Mode = 0;
	Pin16_Mode = 0;
	Pin17_Mode = 0;

	Pin20_Mode = 0;
	Pin21_Mode = 0;
	Pin22_Mode = 0;
	Pin23_Mode = 0;
	Pin24_Mode = 0;

	Pin35_Mode = 0;
	Pin36_Mode = 0;
	Pin37_Mode = 0;

	//�˿ڹ��������
	Pin10_Task_Number = 1;
	Pin11_Task_Number = 2;

	Pin12_Task_Number = 1; 
	Pin13_Task_Number = 1;
	Pin14_Task_Number = 2;
	Pin15_Task_Number = 2;
	Pin16_Task_Number = 3;
	Pin17_Task_Number = 3;

	Pin20_Task_Number = 4;
	Pin21_Task_Number = 4;
	Pin22_Task_Number = 5;
	Pin23_Task_Number = 5;
	Pin24_Task_Number = 6;

	Pin35_Task_Number = 6;
	Pin36_Task_Number = 6;
	Pin37_Task_Number = 6;

	//����TCP��������Ϣ
	for(i=0;i<22;i++){
		ATCIPSERVER[i]=ATCIPSERVER_Default[i];
	}
		
	//TCP�������˿�
	TcpServerPort = 1;

	//STA AP��Ϣ
	for(i=1;1<151;i++){
		if(STA_MODE_Table_Default[i-2]=='\n'){break;}
		STA_MODE_Table[i-1]=STA_MODE_Table_Default[i-1];
	}
	
	for(i=1;i<151;i++){
		if(AP_MODE_Table_Default[i-2]=='\n'){break;}
		AP_MODE_Table[i-1]=AP_MODE_Table_Default[i-1];
	}
	
	

	
}