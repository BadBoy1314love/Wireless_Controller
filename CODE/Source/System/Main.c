/******************************************************************************/
// ����ͷ�ļ�
/******************************************************************************/
#include "Config.h"
#include "LCD1602.h"
#include "LCD1602_Clock.h"
#include "LCD1602_Menu.h"
#include "LCD1602_Show.h"
#include "Timer.h"
#include "hSch51.h"
#include "Download.h"
#include "Relay.h"
#include "EEPROM.h"
#include "EEPROM_Application.h"
#include "EC11.h"
#include "Buzzer.h"
#include "UART.h"
#include "ESP8266.h"

/******************************************************************************/
// �������
/******************************************************************************/


/******************************************************************************/
// main����
/******************************************************************************/
int main(void)
{	
	/*��ʼ������*/	
	
	P4SW = 0x20;   // 0010 0000
	P4M1=0xDF;  // 1101 1111
	P4M0=0x20;  // 0010 0000
	
	EEPROM_Read_Sector_1();
	Lcd1602_Init();
	EC11_Init();
	Timer1Init();
	Buzzer_Init();
	UartInit();  //��ʼ��ѡ����������ʷ�����,���ô����ж�
	
	hSCH_Start(); // �������ȳ��򣨿������жϣ�
	
	Esp8266_STA_AP_Mode();  
	
	Lcd1602_Write_Cmd(0x01);//��ʾ����
	
	hSCH_Init_T0(); //���õ��ȳ���,��ʼ�������������ö�ʱ��0
									//Ϊ16λ�ֶ���װģʽ����ʱ1ms��Ϊ������ʱ��
	
	hSCH_Pause();  //��������Ϊ������ʱ����T2�ж�
	
	
	/*��ӵ���������*/
	hSCH_Add_Task(EC11_Scan,  0, 5 ,0);
	
	hSCH_Add_Task(LCD1602_Show_Update,  5, 100 ,1);
	hSCH_Add_Task(LCD1602_Time_Update, 40, 991 ,0);

  hSCH_Add_Task(Task_Input_Update,   51, 49 ,0);
	hSCH_Add_Task(Task1_Output_Update, 52, 49 ,0);
	hSCH_Add_Task(Task2_Output_Update, 53, 49 ,0);
	hSCH_Add_Task(Task3_Output_Update, 54, 49 ,0);
	
	hSCH_Add_Task(Task4_Output_Update, 55, 49 ,0);
	hSCH_Add_Task(Task5_Output_Update, 56, 49 ,0);
	hSCH_Add_Task(Task6_Output_Update, 57, 49 ,0);

//	hSCH_Add_Task(Buzzer_Open,  55, 500 ,1);
	
  hSCH_Run();  //������Ϊ������ʱ����T2�ж�
	
	
	
	/*��ѭ��*/
	while(1)
	{
		hSCH_Dispatch_Tasks();
  }
}
