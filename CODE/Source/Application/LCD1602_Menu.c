/******************************************************************************/
// ����ͷ�ļ�
/******************************************************************************/
#include "config.h"
#include "LCD1602.h"
#include "LCD1602_Menu.h"
#include "ESP8266.h"
#include "EEPROM_Application.h"

/******************************************************************************/
// ������ʼ��
/******************************************************************************/
u8 Menu_Index = 0;   //�˵�������
u8 Menu_Flag = 0;    //�˵���־λ
                     //0:EC11��ת�л���Ŀ���������²˵�����ת��
										 //1:EC11��ת�л���Ŀ����������Ϊ����ִ�з��ز��������˳��˵�(��һ��RETURN)
										 //2:EC11��ת�л���Ŀ���������¸�������״̬
										 //3:EC11��ת�л���Ŀ���������½����һ���༭λ
										 //4:EC11��ת�޸�ֵ�����������л��༭λ
u8 Menu_Edit_Tips = 0; //�༭��ʾ���Ʊ�����������������Ĵ�����
											 //�ı�༭��ʾ����λ
bit Menu_Edit_Show = 0;  //�༭��ʾ����λ���жϴ�λ����ʾ���߲���ʾ
u8 Menu_Edit = 0;  //�༭��ʾλ,ͨ���˱�����ȷ����ǰҳ�����ʾλ
                   //0:Ϊ�˵���Ŀ������˸�༭λ
									 //1:Ϊ�༭λ1�ţ���˸�˱༭λ
									 //2:Ϊ�༭Ϊ2�ţ���˸�˱༭λ
									 //3:...
s8 Menu_Edit_Value = 0;  //�˵��༭λ��ǰֵ

bit isReset = 0;  //ϵͳ��λ����λ  0����ʱΪ�Ǹ�λ 1����ʱΪ��λ

/*��ʾ��ָ��*/
u8 *LCD1602_First_Line;  //1602��һ�е���ʾ������һ��
u8 *LCD1602_Second_Line;  //1602�ڶ��е���ʾ�����ڶ���
u8 *LCD1602_First_Line_16; //1602��һ�е�16λ����ʾ
u8 *LCD1602_First_Line_6; //1602��һ�е�6λ����ʾ


//�˵��ַ�ָ��
/*��һ���˵�*/
u8 code Menu_TASKS_CTRL_Select[] =">> TASKS CTRL <<";
u8 code Menu_TASKS_SET_Select[]  =">> TASKS SET  <<";
u8 code Menu_PORT_SET_Select[]   =">>  PORT SET  <<";
u8 code Menu_TIME_SET_Select[]   =">>  TIME SET  <<";
u8 code Menu_WIFI_SET_Select[]   =">>  WIFI SET  <<";
u8 code RETURN_Select[]          =">>   RETURN   <<";

u8 code Menu_TASKS_CTRL[] ="   TASKS CTRL   ";
u8 code Menu_TASKS_SET[]  ="   TASKS SET    ";
u8 code Menu_PORT_SET[]   ="    PORT SET    ";
u8 code Menu_TIME_SET[]   ="    TIME SET    ";
u8 code Menu_WIFI_SET[]   ="    WIFI SET    ";
u8 code RETURN[]          ="     RETURN     ";
//����˵���Ŀ
u8 code SYSTEM_RESET_Select[]=">> SYS RESET  <<";
u8 code SYSTEM_RESET[]       ="   SYS RESET    ";
u8 code SYSTEM_RESET_ASK[]   ="SYSTEM RESET ???";
u8 code SYSTEM_RESET_YES[]   =">> YES <<  NO   ";
u8 code SYSTEM_RESET_NO[]    ="   YES  >> NO <<";
/*�ڶ����˵�*/
//TASKS_CTRL_1_0����Ŀ

//TASK1_CTRL
u8 code Menu_TASK1_CTRL_Run_Select[]  =">>  RUN TASK1 <<";
u8 code Menu_TASK1_CTRL_Run[]         ="    RUN TASK1   ";
u8 code Menu_TASK1_CTRL_Stop_Select[] =">> STOP TASK1 <<";
u8 code Menu_TASK1_CTRL_Stop[]        ="   STOP TASK1   ";

//TASK2_CTRL
u8 code Menu_TASK2_CTRL_Run_Select[]  =">>  RUN TASK2 <<";
u8 code Menu_TASK2_CTRL_Run[]         ="    RUN TASK2   ";
u8 code Menu_TASK2_CTRL_Stop_Select[] =">> STOP TASK2 <<";
u8 code Menu_TASK2_CTRL_Stop[]        ="   STOP TASK2   ";

//TASK3_CTRL
u8 code Menu_TASK3_CTRL_Run_Select[]  =">>  RUN TASK3 <<";
u8 code Menu_TASK3_CTRL_Run[]         ="    RUN TASK3   ";
u8 code Menu_TASK3_CTRL_Stop_Select[] =">> STOP TASK3 <<";
u8 code Menu_TASK3_CTRL_Stop[]        ="   STOP TASK3   ";

//TASK4_CTRL
u8 code Menu_TASK4_CTRL_Run_Select[]  =">>  RUN TASK4 <<";
u8 code Menu_TASK4_CTRL_Run[]         ="    RUN TASK4   ";
u8 code Menu_TASK4_CTRL_Stop_Select[] =">> STOP TASK4 <<";
u8 code Menu_TASK4_CTRL_Stop[]        ="   STOP TASK4   ";

//TASK5_CTRL
u8 code Menu_TASK5_CTRL_Run_Select[]  =">>  RUN TASK5 <<";
u8 code Menu_TASK5_CTRL_Run[]         ="    RUN TASK5   ";
u8 code Menu_TASK5_CTRL_Stop_Select[] =">> STOP TASK5 <<";
u8 code Menu_TASK5_CTRL_Stop[]        ="   STOP TASK5   ";

//TASK6_CTRL
u8 code Menu_TASK6_CTRL_Run_Select[]  =">>  RUN TASK6 <<";
u8 code Menu_TASK6_CTRL_Run[]         ="    RUN TASK6   ";
u8 code Menu_TASK6_CTRL_Stop_Select[] =">> STOP TASK6 <<";
u8 code Menu_TASK6_CTRL_Stop[]        ="   STOP TASK6   ";

u8 code Menu_Empty_Line[]             ="                ";

/*�ڶ����˵�*/
//TASKS_SET_1_1����Ŀ

u8 code Menu_TASK1_SET_Select[]   =">> TASK1 SET  <<";
u8 code Menu_TASK2_SET_Select[]   =">> TASK2 SET  <<";
u8 code Menu_TASK3_SET_Select[]   =">> TASK3 SET  <<";
u8 code Menu_TASK4_SET_Select[]   =">> TASK4 SET  <<";
u8 code Menu_TASK5_SET_Select[]   =">> TASK5 SET  <<";
u8 code Menu_TASK6_SET_Select[]   =">> TASK6 SET  <<";

u8 code Menu_TASK1_SET[]   ="   TASK1 SET    ";
u8 code Menu_TASK2_SET[]   ="   TASK2 SET    ";
u8 code Menu_TASK3_SET[]   ="   TASK3 SET    ";
u8 code Menu_TASK4_SET[]   ="   TASK4 SET    ";
u8 code Menu_TASK5_SET[]   ="   TASK5 SET    ";
u8 code Menu_TASK6_SET[]   ="   TASK6 SET    ";

//PORT_SET_1_2����Ŀ

//�����ж˿�
u8 code Trigger_Mode_0[]="  TRIGGER MODE:0"; 
u8 code Trigger_Mode_1[]="  TRIGGER MODE:1";
u8 code Trigger_Mode_Empty[]="  TRIGGER MODE: ";
u8 code Empty_Number[] = " ";

//PIN(10-17,20-24,35-37) SET
u8 xdata PIN_SET_Input[]  =">>PIN  -->TASK:";
u8 xdata PIN_SET_Output[] =">>PIN  <--TASK:";
u8 xdata PIN_SET_Empty[]  =">>PIN     TASK:";

//TIME_SET_1_3����Ŀ
u8 xdata SET_DATE[]  ="DATE:2022/07/17 ";
u8 xdata SET_TIME[]  ="TIME: 00:00:00  ";

u8 code SET_TIME_MANUAL[]        ="   MANUAL SET   ";
u8 code SET_TIME_MANUAL_Select[] =">> MANUAL SET <<";

u8 code SET_TIME_AUTO[]        ="    AUTO SET    ";
u8 code SET_TIME_AUTO_Select[] =">>  AUTO SET  <<";

/*�ڶ����˵�*/
//WIFI_SET_1_4����Ŀ
u8 code TCP_PORT_SET_Select[]=">>  TCP PORT  <<";
u8 code TCP_PORT_SET[]       ="    TCP PORT    ";
u8 code TCP_SERVER_PORT[]   ="TCP SERVER PORT:";
u8 xdata TCP_PORT_Number[]   ="-->  65535   <--";

u8 code STA_IP_Select[] =">>   STA IP   <<";
u8 code STA_IP[]        ="     STA IP     ";
u8 code STA_IP_ADDRESS[]="STA IP ADDRESS: ";

u8 code AP_IP_Select[] =">>    AP IP   <<";
u8 code AP_IP[]        ="      AP IP     ";
u8 code AP_IP_ADDRESS[]="AP IP ADDRESS:  ";

/*�������˵�*/
//TASK_SET����Ŀ��TASK1-TASK1���ã�
u8 xdata TASK_StartTime[]="TASK  StartTime:"; 
u8 xdata TASK_EndTime[]  ="TASK    EndTime:";
u8 xdata TASK_OverTime[] ="TASK   OverTime:";
u8 code TASK_OverTime_AutoReset_ON[]  ="AutoReset--->ON ";
u8 code TASK_OverTime_AutoReset_OFF[] ="AutoReset--->OFF";
u8 code TASK_OverTime_AutoReset_Empty[] ="AutoReset--->   ";
u8 xdata TASK_OnTime[]   ="TASK     OnTime:";
u8 xdata TASK_OffTime[]  ="TASK    OffTime:";
u8 xdata Time_Minute[]   ="   00:00        ";
u8 xdata Time_100MS[]    =" 0000:00:00:00  ";

u8 xdata TASK_SET_Number =0;


/*����ŵ���ʾ����*/
u8 idata Pin10_Number[1] = {0};
u8 idata Pin11_Number[1] = {0};
u8 idata Pin12_Number[1] = {0};
u8 idata Pin13_Number[1] = {0};
u8 idata Pin14_Number[1] = {0};
u8 idata Pin15_Number[1] = {0};
u8 idata Pin16_Number[1] = {0};
u8 idata Pin17_Number[1] = {0};

u8 idata Pin20_Number[1] = {0};
u8 idata Pin21_Number[1] = {0};
u8 idata Pin22_Number[1] = {0};
u8 idata Pin23_Number[1] = {0};
u8 idata Pin24_Number[1] = {0};

u8 idata Pin35_Number[1] = {0};
u8 idata Pin36_Number[1] = {0};
u8 idata Pin37_Number[1] = {0};

extern u8 EC11_State;   //����EC11��״̬
extern s8 EC11_Value;   //����EC11�ı�ʾֵ

extern u8 LCD1602_Show_State;

/*�����������λ*/
extern bit Task1;
extern bit Task2;
extern bit Task3;
extern bit Task4;
extern bit Task5;
extern bit Task6;

/*����ģʽʱ��Ϊ�˿ڴ������������*/ 
/*���ģʽʱѡ����������*/
/*�˿�ģʽ��0Ϊ����ģʽ����1Ϊ���ģʽ��*/
extern s8 xdata Pin10_Task_Number;	extern bit Pin10_Mode;
extern s8 xdata Pin11_Task_Number;	extern bit Pin11_Mode;

extern s8 xdata Pin12_Task_Number;  extern bit Pin12_Mode; 
extern s8 xdata Pin13_Task_Number;	extern bit Pin13_Mode;
extern s8 xdata Pin14_Task_Number;	extern bit Pin14_Mode;
extern s8 xdata Pin15_Task_Number;	extern bit Pin15_Mode;
extern s8 xdata Pin16_Task_Number;	extern bit Pin16_Mode;
extern s8 xdata Pin17_Task_Number;	extern bit Pin17_Mode;

extern s8 xdata Pin20_Task_Number;	extern bit Pin20_Mode;
extern s8 xdata Pin21_Task_Number;	extern bit Pin21_Mode;
extern s8 xdata Pin22_Task_Number;  extern bit Pin22_Mode;
extern s8 xdata Pin23_Task_Number;	extern bit Pin23_Mode;
extern s8 xdata Pin24_Task_Number;  extern bit Pin24_Mode;

extern s8 xdata Pin35_Task_Number;  extern bit Pin35_Mode;
extern s8 xdata Pin36_Task_Number;	extern bit Pin36_Mode;
extern s8 xdata Pin37_Task_Number;	extern bit Pin37_Mode;

/*�˿ڵĴ���ģʽ*/
/*����ģʽ��0Ϊ����ģʽ����1Ϊ����ģʽ��*/
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

extern s8 hour,minute,second;
extern s16 Year;
extern s8 Month;
extern s8 Day;
extern u8 xdata Max_Month_Days[];

extern u8 xdata ESP8266_Return_Value;

//TCP�������˿�
extern s32 xdata TcpServerPort;
/*����TCP��������Ϣ*/
extern u8 xdata ATCIPSERVER[]; //="AT+CIPSERVER=1,65535";

extern u8 xdata STAIPTable[];
extern u8 xdata APIPTable[];

/*ʱ�������Ъģʽ*/

/*����һ*/
extern s16 xdata Task1_StartTime;//����1��ʼ����ʱ��
extern s16 xdata Task1_EndTime;//����1��������ʱ��
extern s32 xdata Task1_OverTime; //����1���г�ʱʱ��
extern bit Task1_OverTime_Reset; //����1���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task1_OnTime;  //��ʾTask1���ON״̬��ʱ��
extern s32 xdata Task1_OffTime; //��ʾTask1���OFF״̬��ʱ��

/*�����*/
extern s16 xdata Task2_StartTime;//����2��ʼ����ʱ��
extern s16 xdata Task2_EndTime;//����2��������ʱ��
extern s32 xdata Task2_OverTime; //����2���г�ʱʱ��
extern bit Task2_OverTime_Reset; //����2���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task2_OnTime;  //��ʾTask2���ON״̬��ʱ��
extern s32 xdata Task2_OffTime; //��ʾTask2���OFF״̬��ʱ��


/*������*/
extern s16 xdata Task3_StartTime;//����3��ʼ����ʱ��
extern s16 xdata Task3_EndTime;//����3��������ʱ��
extern s32 xdata Task3_OverTime; //����3���г�ʱʱ��
extern bit Task3_OverTime_Reset; //����3���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task3_OnTime;  //��ʾTask3���ON״̬��ʱ��
extern s32 xdata Task3_OffTime; //��ʾTask3���OFF״̬��ʱ��


/*������*/
extern s16 xdata Task4_StartTime;//����4��ʼ����ʱ��
extern s16 xdata Task4_EndTime;//����4��������ʱ��
extern s32 xdata Task4_OverTime; //����4���г�ʱʱ��
extern bit Task4_OverTime_Reset; //����4���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task4_OnTime;  //��ʾTask4���ON״̬��ʱ��
extern s32 xdata Task4_OffTime; //��ʾTask4���OFF״̬��ʱ��

/*������*/
extern s16 xdata Task5_StartTime;//����5��ʼ����ʱ��
extern s16 xdata Task5_EndTime;//����5��������ʱ��
extern s32 xdata Task5_OverTime; //����5���г�ʱʱ��
extern bit Task5_OverTime_Reset; //����5���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task5_OnTime;  //��ʾTask5���ON״̬��ʱ��
extern s32 xdata Task5_OffTime; //��ʾTask5���OFF״̬��ʱ��

/*������*/
extern s16 xdata Task6_StartTime;//����6��ʼ����ʱ��
extern s16 xdata Task6_EndTime;//����6��������ʱ��
extern s32 xdata Task6_OverTime; //����6���г�ʱʱ��
extern bit Task6_OverTime_Reset; //����6���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

extern s32 xdata Task6_OnTime;  //��ʾTask6���ON״̬��ʱ��
extern s32 xdata Task6_OffTime; //��ʾTask6���OFF״̬��ʱ��


extern u8 xdata STA_MODE_Table[150]; //={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\"\r\n        "};
extern u8 xdata AP_MODE_Table[150]; //={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4\r\n      "};
extern uint8 xdata rcvTable[200];
extern u8 xdata apTable[16];

/*ִ�е�ǰ�˵��������µľ����������*/
void (*current_operation_index)();   //�趨��ʾ״̬�Լ��Բ������в���

/******************************************************************************/
// LCD1602�˵�������
/******************************************************************************/
Menu_table code table[52]=
{
	/*��һ���˵�*/
	{0,5,1,6,(*TASKS_CTRL_1_0)},
	{1,0,2,13, (*TASKS_SET_1_1)},
	{2,1,3,20,  (*PORT_SET_1_2)},
	{3,2,4,37,  (*TIME_SET_1_3)},
	{4,3,51,40,  (*WIFI_SET_1_4)},
	{5,51,0,5,    (*RETURN_1_5)},
	
	/*�ڶ����˵�*/
	//TASKS_CTRL_1_0����Ŀ
	{6,12,7,6,   (*TASK1_CTRL_2_6)},
	{7,6,8,7,    (*TASK2_CTRL_2_7)},
	{8,7,9,8,    (*TASK3_CTRL_2_8)},
	{9,8,10,9,   (*TASK4_CTRL_2_9)},
	{10,9,11,10, (*TASK5_CTRL_2_10)},
	{11,10,12,11,(*TASK6_CTRL_2_11)},
	{12,11,6,0,      (*RETURN_2_12)},
	
	/*�ڶ����˵�*/
	//TASKS_SET_1_1����Ŀ
	{13,19,14,44, (*TASK1_SET_2_13)},
	{14,13,15,44, (*TASK2_SET_2_14)},
	{15,14,16,44, (*TASK3_SET_2_15)},
	{16,15,17,44, (*TASK4_SET_2_16)},
	{17,16,18,44, (*TASK5_SET_2_17)},
	{18,17,19,44, (*TASK6_SET_2_18)},
	{19,18,13,1,  (*RETURN_2_19)},
	
	/*�ڶ����˵�*/
  //PORT_SET_1_2����Ŀ
	{20,36,21,20, (*PIN10_SET_2_20)},
	{21,20,22,21, (*PIN11_SET_2_21)},
	{22,21,23,22, (*PIN12_SET_2_22)},
	{23,22,24,23, (*PIN13_SET_2_23)},
	{24,23,25,24, (*PIN14_SET_2_24)},
	{25,24,26,25, (*PIN15_SET_2_25)},
	{26,25,27,26, (*PIN16_SET_2_26)},
	{27,26,28,27, (*PIN17_SET_2_27)},
	
	{28,27,29,28, (*PIN20_SET_2_28)},
	{29,28,30,29, (*PIN21_SET_2_29)},
	{30,29,31,30, (*PIN22_SET_2_30)},
	{31,30,32,31, (*PIN23_SET_2_31)},
	{32,31,33,32, (*PIN24_SET_2_32)},
	
	{33,32,34,33, (*PIN35_SET_2_33)},
	{34,33,35,34, (*PIN36_SET_2_34)},
	{35,34,36,35, (*PIN37_SET_2_35)},
	
	{36,35,20,2, (*RETURN_2_36)},
	
	/*�ڶ����˵�*/
  //TIME_SET_1_3����Ŀ
	{37,39,38,37,(*TIME_SET_Manual_Set_2_37)},
	{38,37,39,38,(*TIME_SET_Auto_Set_2_38)},
	{39,38,37,3,(*RETURN_2_39)},

	/*�ڶ����˵�*/
  //WIFI_SET_1_4����Ŀ
	{40,43,41,40,(*TCP_PORT_SET_2_40)},
	{41,40,42,41,(*STA_IP_2_41)},
	{42,41,43,42,(*AP_IP_2_42)},
	{43,42,40,4,(*RETURN_2_43)},

	/*�������˵�*/
  //TASK_SET����Ŀ��TASK1-TASK1���ã�
	{44,50,45,44,(*TASK_StartTime_SET_3_44)},
	{45,44,46,45,(*TASK_EndTime_SET_3_45)},
	{46,45,47,46,(*TASK_OverTime_SET_3_46)},
	{47,46,48,47,(*TASK_OverTime_MODE_SET_3_47)},
	{48,47,49,48,(*TASK_OnTime_SET_3_48)},
	{49,48,50,49,(*TASK_OffTime_SET_3_49)},
	{50,49,44,50,(*RETURN_3_50)},
	
	//����˵���Ŀ
	{51,4,5,51,(*SYSTEM_RESET_1_51)},
	
};

/******************************************************************************/
// LCD1602�˵���ʾ����
// �������ƣ�Lcd1602_Menu
// �����������
// ����������� 
// �������ܣ�LCD1602��ʾ�˵�
/******************************************************************************/
void LCD1602_Menu_Update()
{
	
	//�༭λ����˸
	if(++Menu_Edit_Tips==4)
	{
		Menu_Edit_Tips=0;  //��λ��ʾ���Ʊ���
	  Menu_Edit_Show=~Menu_Edit_Show;  //�л���ʾ״̬
	}
	
	/*��ӦEC11״̬����λEC11״̬*/
	/*�����²˵�������*/
	switch(EC11_State)  
	{
		case 1:  //EC11Ϊ��ʱ����ת״̬
			switch(Menu_Flag)
			{
				case 0:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 1:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 2:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 3:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
				case 4:
					
					break;
				case 5:
					Menu_Index = table[Menu_Index].Left_Index;
					break;
			}
		  
		  EC11_State = 0; //��λEC11״̬
		  break;
		case 2:  //EC11Ϊ˳ʱ����ת״̬
			switch(Menu_Flag)
			{
				case 0:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 1:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 2:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 3:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
				case 4:
					
					break;
				case 5:
					Menu_Index = table[Menu_Index].Right_Index;
					break;
			}
	
			
		  EC11_State = 0; //��λEC11״̬
		  break;
		case 3:  //EC11Ϊ�������µ�״̬
			
			//Menu_Flagȷ����ǰ��EC11�Ĳ�����Ϊ
			switch(Menu_Flag)
			{
				case 0:  //���ڲ˵���Ŀ�л�״̬������������һ���˵�
					
					if(Menu_Index==19||Menu_Index==36||Menu_Index==43){
						EA=0;  //���ǰ�ر����ж�
						EEPROM_Program_Sector_1();
						EA=1;  //��̺������ж�
					}
				
					Menu_Index = table[Menu_Index].Enter_Index;
					break;
				case 1:  //���ڷ���״̬�������˳��˵�
					//ͨ��������ִ��ָ������
					switch(Menu_Index)
					{
						case 5:	LCD1602_Show_State = 0;break;
					}
					break;
				
				case 2:  //����TASK_CTRL״̬��������������
					switch(Menu_Index)
					{
						case 6:Task1=~Task1;break;
						case 7:Task2=~Task2;break;
						case 8:Task3=~Task3;break;
						case 9:Task4=~Task4;break;
						case 10:Task5=~Task5;break;
						case 11:Task6=~Task6;break;
					}
					break;
				
				case 3:  //������Ŀ״̬����������༭λ
					Menu_Edit++; //�л��༭��ʾλ
					break;
				case 4: //���ڱ༭״̬�������л��༭λ
					Menu_Edit++; //�л��༭��ʾλ
					break;
				case 5:
					if(Menu_Index==50){EEPROM_Program_Sector_1();}
					switch(TASK_SET_Number)
					{
						case 1:
							Menu_Index = 13;
							break;
						case 2:
							Menu_Index = 14;
							break;
						case 3:
							Menu_Index = 15;
							break;
						case 4:
							Menu_Index = 16;
							break;
						case 5:
							Menu_Index = 17;
							break;
						case 6:
							Menu_Index = 18;
							break;
					}
				
					break;
			}
			
		  EC11_State = 0; //��λEC11״̬
		  break;
	}
	
	/*���¶�Ӧ�������µĺ���ָ��*/
  current_operation_index = table[Menu_Index].current_operation;
	(*current_operation_index)();////�趨��ʾ״̬�Լ��Բ������в���
	
	/*��ʾ��ǰ�˵�ҳ��*/
	LCD1602_Show_Current_Page();
}

/******************************************************************************/
// LCD1602�˵�ҳ����ʾ����
// �������ƣ�LCD1602_Show_Current_Page()
// �����������
// ����������� 
// �������ܣ���ʾLCD1602�˵���ǰҳ��
/******************************************************************************/
void LCD1602_Show_Current_Page()
{
	if(((Menu_Index>=0)&&(Menu_Index<=19))||((Menu_Index>=36)&&Menu_Index<=51)){
		Lcd1602_Show_String(1,1,LCD1602_First_Line);
	  Lcd1602_Show_String(2,1,LCD1602_Second_Line);
	}else if((Menu_Index>=20)&&(Menu_Index<=35)){
		Lcd1602_Show_String(1,1,LCD1602_First_Line);
		Lcd1602_Show_String(1,16,LCD1602_First_Line_16);
	  Lcd1602_Show_String(2,1,LCD1602_Second_Line);
	}
	
}





/******************************************************************************/
// LCD1602�˵���������
// �������ƣ�
// �����������
// ����������� 
// �������ܣ�ִ��LCD1602�˵���������
/******************************************************************************/
/*��һ���˵�*/
void TASKS_CTRL_1_0()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_TASKS_CTRL_Select;
	LCD1602_Second_Line = Menu_TASKS_SET;
}
void TASKS_SET_1_1()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_TASKS_CTRL;
	LCD1602_Second_Line = Menu_TASKS_SET_Select;
}
void PORT_SET_1_2()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_PORT_SET_Select;
	LCD1602_Second_Line = Menu_TIME_SET;
}
void TIME_SET_1_3()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_PORT_SET;
	LCD1602_Second_Line = Menu_TIME_SET_Select;
}
void WIFI_SET_1_4()
{
	Menu_Flag = 0;
	LCD1602_First_Line  = Menu_WIFI_SET_Select;
	LCD1602_Second_Line = SYSTEM_RESET;
}

void SYSTEM_RESET_1_51()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if((Menu_Edit==3)||(Menu_Edit==2)&&(isReset==0)){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = Menu_WIFI_SET;
	    LCD1602_Second_Line = SYSTEM_RESET_Select;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//ͨ���˵��༭ֵ���趨�Ƿ�λ
			if(Menu_Edit_Value < 0){
				isReset = 1;
			}else if(Menu_Edit_Value > 0){
				isReset = 0;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
	
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = SYSTEM_RESET_ASK;
			
			if(isReset==1){
				LCD1602_Second_Line = SYSTEM_RESET_YES;		
			}else{
				LCD1602_Second_Line = SYSTEM_RESET_NO;
			}
	    
			break;
			
		case 2:
			Menu_Flag = 4;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
	
			if(isReset==1){
				EA = 0;  //�ر����ж�
				SYSTEM_DATA_RESET();
				EEPROM_Program_Sector_1();
				IAP_CONTR=0x60;//��λ���� 
				EA = 1;
			}else{
				Menu_Edit = 0;  //�л�����Ŀ
			}
			
	}
	
}

void RETURN_1_5()
{
	Menu_Flag = 1;
	
	LCD1602_First_Line  = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*�ڶ����˵�*/
//TASKS_CTRL_1_0����Ŀ


void TASK1_CTRL_2_6()
{
	Menu_Flag = 2;
	
	if(Task1==1){
		LCD1602_First_Line = Menu_TASK1_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK1_CTRL_Run_Select;
	}
	
	if(Task2==1){
		LCD1602_Second_Line = Menu_TASK2_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK2_CTRL_Run;
	}
}
void TASK2_CTRL_2_7()
{
	Menu_Flag = 2;
	if(Task1==1){
		LCD1602_First_Line = Menu_TASK1_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK1_CTRL_Run;
	}
	
	if(Task2==1){
		LCD1602_Second_Line = Menu_TASK2_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK2_CTRL_Run_Select;
	}
}
void TASK3_CTRL_2_8()
{
	Menu_Flag = 2;
	if(Task3==1){
		LCD1602_First_Line = Menu_TASK3_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK3_CTRL_Run_Select;
	}
	
	if(Task4==1){
		LCD1602_Second_Line = Menu_TASK4_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK4_CTRL_Run;
	}
}
void TASK4_CTRL_2_9()
{
	Menu_Flag = 2;
	if(Task3==1){
		LCD1602_First_Line = Menu_TASK3_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK3_CTRL_Run;
	}
	
	if(Task4==1){
		LCD1602_Second_Line = Menu_TASK4_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK4_CTRL_Run_Select;
	}
}
void TASK5_CTRL_2_10()
{
	Menu_Flag = 2;
	if(Task5==1){
		LCD1602_First_Line = Menu_TASK5_CTRL_Stop_Select;
	}else{
		LCD1602_First_Line = Menu_TASK5_CTRL_Run_Select;
	}
	
	if(Task6==1){
		LCD1602_Second_Line = Menu_TASK6_CTRL_Stop;
	}else{
		LCD1602_Second_Line = Menu_TASK6_CTRL_Run;
	}
}
void TASK6_CTRL_2_11()
{
	Menu_Flag = 2;
	if(Task5==1){
		LCD1602_First_Line = Menu_TASK5_CTRL_Stop;
	}else{
		LCD1602_First_Line = Menu_TASK5_CTRL_Run;
	}
	
	if(Task6==1){
		LCD1602_Second_Line = Menu_TASK6_CTRL_Stop_Select;
	}else{
		LCD1602_Second_Line = Menu_TASK6_CTRL_Run_Select;
	}
}
void RETURN_2_12()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*�ڶ����˵�*/
//TASKS_SET_1_1����Ŀ

void TASK1_SET_2_13()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=1;
	
	LCD1602_First_Line = Menu_TASK1_SET_Select;
	LCD1602_Second_Line = Menu_TASK2_SET;
}
void TASK2_SET_2_14()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=2;
	
	LCD1602_First_Line = Menu_TASK1_SET;
	LCD1602_Second_Line = Menu_TASK2_SET_Select;
}
void TASK3_SET_2_15()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=3;
	
	LCD1602_First_Line = Menu_TASK3_SET_Select;
	LCD1602_Second_Line = Menu_TASK4_SET;
}
void TASK4_SET_2_16()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=4;
	
	LCD1602_First_Line = Menu_TASK3_SET;
	LCD1602_Second_Line = Menu_TASK4_SET_Select;
}
void TASK5_SET_2_17()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=5;
	
	LCD1602_First_Line = Menu_TASK5_SET_Select;
	LCD1602_Second_Line = Menu_TASK6_SET;
}
void TASK6_SET_2_18()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=6;
	
	LCD1602_First_Line = Menu_TASK5_SET;
	LCD1602_Second_Line = Menu_TASK6_SET_Select;
}
void RETURN_2_19()
{
	Menu_Flag = 0;
	
	TASK_SET_Number=0;
	
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}

/*�ڶ����˵�*/
//PORT_SET_1_2����Ŀ

void PIN10_SET_2_20()
{
	//�����������ʾ����
	Pin10_Number[0]=Pin10_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin10_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin10_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin10_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin10_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin10_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin10_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin10_Task_Number<1){Pin10_Task_Number = 1;}
			else if(Pin10_Task_Number>6){Pin10_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin10_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin10_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin10_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin10_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin10_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin10_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin10_Number;
			
			
			break;
			
	}
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '0';
}

void PIN11_SET_2_21()
{
	//�����������ʾ����
	Pin11_Number[0]=Pin11_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin11_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin11_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin11_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin11_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin11_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin11_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin11_Task_Number<1){Pin11_Task_Number = 1;}
			else if(Pin11_Task_Number>6){Pin11_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin11_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin11_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin11_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin11_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin11_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin11_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin11_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '1';
	
}

void PIN12_SET_2_22()
{
	//�����������ʾ����
	Pin12_Number[0]=Pin12_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin12_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin12_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin12_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin12_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin12_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin12_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin12_Task_Number<1){Pin12_Task_Number = 1;}
			else if(Pin12_Task_Number>6){Pin12_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin12_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin12_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin12_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin12_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin12_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin12_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin12_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '2';
	
}

void PIN13_SET_2_23()
{
	//�����������ʾ����
	Pin13_Number[0]=Pin13_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin13_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin13_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin13_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin13_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin13_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin13_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin13_Task_Number<1){Pin13_Task_Number = 1;}
			else if(Pin13_Task_Number>6){Pin13_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin13_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin13_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin13_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin13_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin13_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin13_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin13_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '3';
	
}

void PIN14_SET_2_24()
{
	//�����������ʾ����
	Pin14_Number[0]=Pin14_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin14_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin14_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin14_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin14_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin14_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin14_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin14_Task_Number<1){Pin14_Task_Number = 1;}
			else if(Pin14_Task_Number>6){Pin14_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin14_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin14_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin14_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin14_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin14_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin14_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin14_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '4';
	
}

void PIN15_SET_2_25()
{
	//�����������ʾ����
	Pin15_Number[0]=Pin15_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin15_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin15_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin15_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin15_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin15_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin15_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin15_Task_Number<1){Pin15_Task_Number = 1;}
			else if(Pin15_Task_Number>6){Pin15_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin15_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin15_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin15_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin15_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin15_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin15_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin15_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '5';
	
}

void PIN16_SET_2_26()
{
	//�����������ʾ����
	Pin16_Number[0]=Pin16_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin16_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin16_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin16_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin16_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin16_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin16_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin16_Task_Number<1){Pin16_Task_Number = 1;}
			else if(Pin16_Task_Number>6){Pin16_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin16_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin16_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin16_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin16_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin16_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin16_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin16_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '6';
	
}

void PIN17_SET_2_27()
{
	//�����������ʾ����
	Pin17_Number[0]=Pin17_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin17_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin17_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin17_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin17_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin17_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin17_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin17_Task_Number<1){Pin17_Task_Number = 1;}
			else if(Pin17_Task_Number>6){Pin17_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin17_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin17_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin17_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin17_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin17_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin17_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin17_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '1';
	LCD1602_First_Line[6]= '7';
	
}

void PIN20_SET_2_28()
{
	//�����������ʾ����
	Pin20_Number[0]=Pin20_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin20_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin20_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin20_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin20_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin20_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin20_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin20_Task_Number<1){Pin20_Task_Number = 1;}
			else if(Pin20_Task_Number>6){Pin20_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin20_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin20_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin20_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin20_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin20_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin20_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin20_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '0';
	
}

void PIN21_SET_2_29()
{
	//�����������ʾ����
	Pin21_Number[0]=Pin21_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin21_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin21_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin21_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin21_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin21_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin21_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin21_Task_Number<1){Pin21_Task_Number = 1;}
			else if(Pin21_Task_Number>6){Pin21_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin21_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin21_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin21_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin21_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin21_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin21_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin21_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '1';
	
}

void PIN22_SET_2_30()
{
	//�����������ʾ����
	Pin22_Number[0]=Pin22_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin22_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin22_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin22_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin22_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin22_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin22_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin22_Task_Number<1){Pin22_Task_Number = 1;}
			else if(Pin22_Task_Number>6){Pin22_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin22_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin22_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin22_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin22_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin22_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin22_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin22_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '2';
	
}

void PIN23_SET_2_31()
{
	//�����������ʾ����
	Pin23_Number[0]=Pin23_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin23_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin23_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin23_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin23_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin23_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin23_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin23_Task_Number<1){Pin23_Task_Number = 1;}
			else if(Pin23_Task_Number>6){Pin23_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin23_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin23_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin23_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin23_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin23_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin23_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin23_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '3';
	
}

void PIN24_SET_2_32()
{
	//�����������ʾ����
	Pin24_Number[0]=Pin24_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin24_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin24_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin24_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin24_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin24_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin24_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin24_Task_Number<1){Pin24_Task_Number = 1;}
			else if(Pin24_Task_Number>6){Pin24_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin24_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin24_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin24_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin24_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin24_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin24_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin24_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '2';
	LCD1602_First_Line[6]= '4';
	
}

void PIN35_SET_2_33()
{
	//�����������ʾ����
	Pin35_Number[0]=Pin35_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin35_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin35_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin35_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin35_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin35_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin35_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin35_Task_Number<1){Pin35_Task_Number = 1;}
			else if(Pin35_Task_Number>6){Pin35_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin35_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin35_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin35_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin35_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin35_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin35_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin35_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '5';
	
}


void PIN36_SET_2_34()
{
	//�����������ʾ����
	Pin36_Number[0]=Pin36_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin36_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin36_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin36_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin36_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin36_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin36_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin36_Task_Number<1){Pin36_Task_Number = 1;}
			else if(Pin36_Task_Number>6){Pin36_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin36_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin36_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin36_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin36_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin36_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin36_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin36_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '6';
	
}

void PIN37_SET_2_35()
{
	//�����������ʾ����
	Pin37_Number[0]=Pin37_Task_Number+'0'; 
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
		
			//��ʾ��һ�ж˿��������״̬
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin37_Number;

			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			
			break;
			
		case 1:  //��һ���༭λ����ͷ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨��ͷ,(�������ģʽ)
			if(Menu_Edit_Value < 0){
				Pin37_Mode = 1;
			}else if(Menu_Edit_Value > 0){
				Pin37_Mode = 0;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ǰѡ����Ŀ����˸
			//��ͷ����˸
			if(Menu_Edit_Show){  //�����ʾ��ͷ
				
				if(Pin37_Mode==0){
					LCD1602_First_Line = PIN_SET_Input;
				}else{
					LCD1602_First_Line = PIN_SET_Output;
				}
				
			}else{   //������ʾ��ͷ
				
					LCD1602_First_Line = PIN_SET_Empty;

			}
			
			//��ʾ������Ŀ
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin37_Number;
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
			break;
			
		case 2:  //�ڶ����༭λ�������
			
			Menu_Flag = 4;
		
			//�޸������
			Pin37_Task_Number += Menu_Edit_Value;
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//�趨����ſ������õķ�Χ
			if(Pin37_Task_Number<1){Pin37_Task_Number = 1;}
			else if(Pin37_Task_Number>6){Pin37_Task_Number = 6;}
		
			//��ǰѡ����Ŀ����˸
			//����ŵ���˸
			if(Menu_Edit_Show){
			  LCD1602_First_Line_16 = Pin37_Number;
			}else{
				LCD1602_First_Line_16 = Empty_Number;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ�ڶ��ж˿ڴ���ģʽ
			if(Pin37_Trigger_Mode == 0){
				LCD1602_Second_Line = Trigger_Mode_0;
			}else{
				LCD1602_Second_Line = Trigger_Mode_1;
			}
						
			break;
			
		case 3:   //�������༭λ���˿ڵĴ���ģʽ
			
			Menu_Flag = 4;
		
		
			//ͨ���˵��༭ֵ���趨����ģʽ,��������������������
			if(Menu_Edit_Value < 0){
				Pin37_Trigger_Mode = 0;
			}else if(Menu_Edit_Value > 0){
				Pin37_Trigger_Mode = 1;
			}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//����ģʽ����˸
			if(Menu_Edit_Show){
			  if(Pin37_Trigger_Mode == 0){
					LCD1602_Second_Line = Trigger_Mode_0;
				}else{
					LCD1602_Second_Line = Trigger_Mode_1;
				}
			}else{
				LCD1602_Second_Line = Trigger_Mode_Empty;
			}
			
			//��ʾ������Ŀ
			//��ʾ��һ�ж˿��������״̬
			if(Pin37_Mode==0){
				LCD1602_First_Line = PIN_SET_Input;
			}else{
				LCD1602_First_Line = PIN_SET_Output;
			}
			
			//��ʾ��һ��16λ�˿�ƥ�������
			LCD1602_First_Line_16 = Pin37_Number;
			
			break;
			
	}
	
	//���ö˿ں���ʾ����
	LCD1602_First_Line[5]= '3';
	LCD1602_First_Line[6]= '7';
	
}

void RETURN_2_36()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}


/*�ڶ����˵�*/
//TIME_SET_1_3����Ŀ
void TIME_SET_Manual_Set_2_37()
{
	
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==7){Menu_Edit=0;};
	
	//SET_DATE[]  ="DATE:2022/07/17 ";
  //SET_TIME[]  ="TIME: 00:00:00  ";
  //�����1-6�༭λʱ���趨����ʱ����ʾ����
	if(Menu_Edit>=1){
		//��������
		SET_DATE[5]=Year/1000%10+'0';
		SET_DATE[6]=Year/100%10+'0';
		SET_DATE[7]=Year/10%10+'0';
		SET_DATE[8]=Year%10+'0';
		
		SET_DATE[10]=Month/10%10+'0';
		SET_DATE[11]=Month%10+'0';
		
		SET_DATE[13]=Day/10%10+'0';
		SET_DATE[14]=Day%10+'0';
		
		//����ʱ��
		SET_TIME[6]=hour/10%10+'0';
		SET_TIME[7]=hour%10+'0';
		
		SET_TIME[9]=minute/10%10+'0';
		SET_TIME[10]=minute%10+'0';
		
		SET_TIME[12]=second/10%10+'0';
		SET_TIME[13]=second%10+'0';
		
		LCD1602_First_Line = SET_DATE;
	  LCD1602_Second_Line = SET_TIME;
	}
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = SET_TIME_MANUAL_Select;
	    LCD1602_Second_Line = SET_TIME_AUTO;
			
			break;
			
		case 1:
			Menu_Flag = 4;
		  
			//����Year
			Year += Menu_Edit_Value;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//�����˸
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[5] = ' ';
				LCD1602_First_Line[6] = ' ';
				LCD1602_First_Line[7] = ' ';
				LCD1602_First_Line[8] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		  
			//����Month
			Month += Menu_Edit_Value;
		
			//����Month�����÷�Χ
			if(Month<1){Month=1;}
			else if(Month>12){Month=12;}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//�����˸
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[10] = ' ';
				LCD1602_First_Line[11] = ' ';
			}
			break;
			
		case 3:
			Menu_Flag = 4;
		  
			//����Day
			Day += Menu_Edit_Value;
		
			//����Day
			if(Day<1){Day=1;}
			else if(Day>Max_Month_Days[Month]){Day=Max_Month_Days[Month];}
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//�����˸
			if(Menu_Edit_Show==0){
			  LCD1602_First_Line[13] = ' ';
				LCD1602_First_Line[14] = ' ';
			}
			break;	
			
		case 4:
			Menu_Flag = 4;
		  
			//����Сʱ
			hour += Menu_Edit_Value;
		
			//����Сʱ�����÷�Χ
			if(hour<0){hour=0;}
			else if(hour>23){hour=23;}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;	
			
		case 5:
			Menu_Flag = 4;
		  
			//���·���
			minute += Menu_Edit_Value;
		
			//���Ʒ��ӵ����÷�Χ
			if(minute<0){minute=0;}
			else if(minute>59){minute=59;}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;	
			
		case 6:
			Menu_Flag = 4;
		  
			//������
			second += Menu_Edit_Value;
		
			//����������÷�Χ
			if(second<0){second=0;}
			else if(second>59){second=59;}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		  
			//��ǰѡ����Ŀ����˸
			//�����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;	
	}
}

void TIME_SET_Auto_Set_2_38()
{
	
		//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==1){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
		  //��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = SET_TIME_MANUAL;
	    LCD1602_Second_Line = SET_TIME_AUTO_Select;
			
			break;
		
	 }
}

void RETURN_2_39()
{
	Menu_Flag = 0;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}

/*�ڶ����˵�*/
//WIFI_SET_1_4����Ŀ
void TCP_PORT_SET_2_40()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==4){Menu_Edit=0;};
	
	//�趨��ʾ����
	if(Menu_Edit>=1){
		//���ݵ�ǰTCP�˿��趨�˵���ʾ�˿�
		TCP_PORT_Number[5] = TcpServerPort/10000%10+'0';
		TCP_PORT_Number[6] = TcpServerPort/1000%10+'0';
		TCP_PORT_Number[7] = TcpServerPort/100%10+'0';
		TCP_PORT_Number[8] = TcpServerPort/10%10+'0';
		TCP_PORT_Number[9] = TcpServerPort/1%10+'0';
		
		//�趨TCP�������Ķ˿�
		ATCIPSERVER[15] = TcpServerPort/10000%10+'0';
		ATCIPSERVER[16] = TcpServerPort/1000%10+'0';
		ATCIPSERVER[17] = TcpServerPort/100%10+'0';
		ATCIPSERVER[18] = TcpServerPort/10%10+'0';
		ATCIPSERVER[19] = TcpServerPort/1%10+'0';
		
	  //��ʾ��ǰҳ��������Ŀ
		LCD1602_First_Line = TCP_SERVER_PORT;
		LCD1602_Second_Line = TCP_PORT_Number;
	}
	
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = TCP_PORT_SET_Select;
	    LCD1602_Second_Line = STA_IP;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
	
			break;
		
		case 2:
			Menu_Flag = 4;
			
			TcpServerPort += Menu_Edit_Value*100;
			if(TcpServerPort<1){
				TcpServerPort=1;
			}else if(TcpServerPort>65535){
				TcpServerPort=65535;
			}
			
			
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//ǰ��λ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[5] = ' ';
				LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}

			break;
			
		case 3:
			Menu_Flag = 4;
		
			TcpServerPort += Menu_Edit_Value;
			
			if(TcpServerPort<1){
				TcpServerPort=1;
			}else if(TcpServerPort>65535){
				TcpServerPort=65535;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//����λ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[8] = ' ';
				LCD1602_Second_Line[9] = ' ';
			}

			break;
		
	}
}

void STA_IP_2_41()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = TCP_PORT_SET;
	    LCD1602_Second_Line = STA_IP_Select;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = STA_IP_ADDRESS;
	    LCD1602_Second_Line = STAIPTable;
				
			break;
	}
	
}

void AP_IP_2_42()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = AP_IP_Select;
	    LCD1602_Second_Line = RETURN;
			
			break;
			
		case 1:
			Menu_Flag = 4;
					
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
		
			//��ʾ��ǰҳ��������Ŀ
			LCD1602_First_Line = AP_IP_ADDRESS;
	    LCD1602_Second_Line = APIPTable;
				
			break;
	}
	
}

void RETURN_2_43()
{
	Menu_Flag = 0;
	LCD1602_First_Line = AP_IP;
	LCD1602_Second_Line = RETURN_Select;
}



/*�������˵�*/
//TASK_SET����Ŀ��TASK1-TASK1���ã�
void TASK_StartTime_SET_3_44()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==3){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_StartTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			//1234����
			//ȡ��Сʱ
			//1234/60  =  20Сʱ   20x60=1200  ����34
			//1299/60  =  21Сʱ   21x60=1260  ����39
			
			Time_Minute[3]=Task1_StartTime/60/10%10+'0';
			Time_Minute[4]=Task1_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task1_StartTime-(Task1_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task1_StartTime-(Task1_StartTime/60)*60)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
			Time_Minute[3]=Task2_StartTime/60/10%10+'0';
			Time_Minute[4]=Task2_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task2_StartTime-(Task2_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task2_StartTime-(Task2_StartTime/60)*60)/1%10+'0';
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			Time_Minute[3]=Task3_StartTime/60/10%10+'0';
			Time_Minute[4]=Task3_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task3_StartTime-(Task3_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task3_StartTime-(Task3_StartTime/60)*60)/1%10+'0';
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
		  Time_Minute[3]=Task4_StartTime/60/10%10+'0';
			Time_Minute[4]=Task4_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task4_StartTime-(Task4_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task4_StartTime-(Task4_StartTime/60)*60)/1%10+'0';
			break;
		case 5: 
			LCD1602_First_Line[4]='5';
			Time_Minute[3]=Task5_StartTime/60/10%10+'0';
			Time_Minute[4]=Task5_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task5_StartTime-(Task5_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task5_StartTime-(Task5_StartTime/60)*60)/1%10+'0';
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			Time_Minute[3]=Task6_StartTime/60/10%10+'0';
			Time_Minute[4]=Task6_StartTime/60/1%10+'0';
			Time_Minute[6]=(Task6_StartTime-(Task6_StartTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task6_StartTime-(Task6_StartTime/60)*60)/1%10+'0';
			break;
	}
	LCD1602_Second_Line = Time_Minute;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_StartTime+=Menu_Edit_Value*60;
					if(Task1_StartTime<0){Task1_StartTime=0;}
					else if(Task1_StartTime>1439){Task1_StartTime=1439;}
					break;
				
				case 2:
					Task2_StartTime+=Menu_Edit_Value*60;
					if(Task2_StartTime<0){Task2_StartTime=0;}
					else if(Task2_StartTime>1439){Task2_StartTime=1439;}
					break;
					
				case 3:
					Task3_StartTime+=Menu_Edit_Value*60;
					if(Task3_StartTime<0){Task3_StartTime=0;}
					else if(Task3_StartTime>1439){Task3_StartTime=1439;}
					break;
					
				case 4:
					Task4_StartTime+=Menu_Edit_Value*60;
					if(Task4_StartTime<0){Task4_StartTime=0;}
					else if(Task4_StartTime>1439){Task4_StartTime=1439;}
					break;
					
				case 5:
					Task5_StartTime+=Menu_Edit_Value*60;
					if(Task5_StartTime<0){Task5_StartTime=0;}
					else if(Task5_StartTime>1439){Task5_StartTime=1439;}
					break;
					
				case 6:
					Task6_StartTime+=Menu_Edit_Value*60;
					if(Task6_StartTime<0){Task6_StartTime=0;}
					else if(Task6_StartTime>1439){Task6_StartTime=1439;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_StartTime+=Menu_Edit_Value;
					if(Task1_StartTime<0){Task1_StartTime=0;}
					else if(Task1_StartTime>1439){Task1_StartTime=1439;}
					break;
				
				case 2:
					Task2_StartTime+=Menu_Edit_Value;
					if(Task2_StartTime<0){Task2_StartTime=0;}
					else if(Task2_StartTime>1439){Task2_StartTime=1439;}
					break;
				
				case 3:
					Task3_StartTime+=Menu_Edit_Value;
					if(Task3_StartTime<0){Task3_StartTime=0;}
					else if(Task3_StartTime>1439){Task3_StartTime=1439;}
					break;
					
				case 4:
					Task4_StartTime+=Menu_Edit_Value;
					if(Task4_StartTime<0){Task4_StartTime=0;}
					else if(Task4_StartTime>1439){Task4_StartTime=1439;}
					break;
				
				case 5:
					Task5_StartTime+=Menu_Edit_Value;
					if(Task5_StartTime<0){Task5_StartTime=0;}
					else if(Task5_StartTime>1439){Task5_StartTime=1439;}
					break;
				
				case 6:
					Task6_StartTime+=Menu_Edit_Value;
					if(Task6_StartTime<0){Task6_StartTime=0;}
					else if(Task6_StartTime>1439){Task6_StartTime=1439;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
	}
	
}

void TASK_EndTime_SET_3_45()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==3){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_EndTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			Time_Minute[3]=Task1_EndTime/60/10%10+'0';
			Time_Minute[4]=Task1_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task1_EndTime-(Task1_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task1_EndTime-(Task1_EndTime/60)*60)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
			Time_Minute[3]=Task2_EndTime/60/10%10+'0';
			Time_Minute[4]=Task2_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task2_EndTime-(Task2_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task2_EndTime-(Task2_EndTime/60)*60)/1%10+'0';
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			Time_Minute[3]=Task3_EndTime/60/10%10+'0';
			Time_Minute[4]=Task3_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task3_EndTime-(Task3_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task3_EndTime-(Task3_EndTime/60)*60)/1%10+'0';
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
		  Time_Minute[3]=Task4_EndTime/60/10%10+'0';
			Time_Minute[4]=Task4_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task4_EndTime-(Task4_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task4_EndTime-(Task4_EndTime/60)*60)/1%10+'0';
			break;
		case 5: 
			LCD1602_First_Line[4]='5';
			Time_Minute[3]=Task5_EndTime/60/10%10+'0';
			Time_Minute[4]=Task5_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task5_EndTime-(Task5_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task5_EndTime-(Task5_EndTime/60)*60)/1%10+'0';
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			Time_Minute[3]=Task6_EndTime/60/10%10+'0';
			Time_Minute[4]=Task6_EndTime/60/1%10+'0';
			Time_Minute[6]=(Task6_EndTime-(Task6_EndTime/60)*60)/10%10+'0';
			Time_Minute[7]=(Task6_EndTime-(Task6_EndTime/60)*60)/1%10+'0';
			break;
	}
	LCD1602_Second_Line = Time_Minute;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_EndTime+=Menu_Edit_Value*60;
					if(Task1_EndTime<0){Task1_EndTime=0;}
					else if(Task1_EndTime>1439){Task1_EndTime=1439;}
					break;
				
				case 2:
					Task2_EndTime+=Menu_Edit_Value*60;
					if(Task2_EndTime<0){Task2_EndTime=0;}
					else if(Task2_EndTime>1439){Task2_EndTime=1439;}
					break;
					
				case 3:
					Task3_EndTime+=Menu_Edit_Value*60;
					if(Task3_EndTime<0){Task3_EndTime=0;}
					else if(Task3_EndTime>1439){Task3_EndTime=1439;}
					break;
					
				case 4:
					Task4_EndTime+=Menu_Edit_Value*60;
					if(Task4_EndTime<0){Task4_EndTime=0;}
					else if(Task4_EndTime>1439){Task4_EndTime=1439;}
					break;
					
				case 5:
					Task5_EndTime+=Menu_Edit_Value*60;
					if(Task5_EndTime<0){Task5_EndTime=0;}
					else if(Task5_EndTime>1439){Task5_EndTime=1439;}
					break;
					
				case 6:
					Task6_EndTime+=Menu_Edit_Value*60;
					if(Task6_EndTime<0){Task6_EndTime=0;}
					else if(Task6_EndTime>1439){Task6_EndTime=1439;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_EndTime+=Menu_Edit_Value;
					if(Task1_EndTime<0){Task1_EndTime=0;}
					else if(Task1_EndTime>1439){Task1_EndTime=1439;}
					break;
				
				case 2:
					Task2_EndTime+=Menu_Edit_Value;
					if(Task2_EndTime<0){Task2_EndTime=0;}
					else if(Task2_EndTime>1439){Task2_EndTime=1439;}
					break;
				
				case 3:
					Task3_EndTime+=Menu_Edit_Value;
					if(Task3_EndTime<0){Task3_EndTime=0;}
					else if(Task3_EndTime>1439){Task3_EndTime=1439;}
					break;
					
				case 4:
					Task4_EndTime+=Menu_Edit_Value;
					if(Task4_EndTime<0){Task4_EndTime=0;}
					else if(Task4_EndTime>1439){Task4_EndTime=1439;}
					break;
				
				case 5:
					Task5_EndTime+=Menu_Edit_Value;
					if(Task5_EndTime<0){Task5_EndTime=0;}
					else if(Task5_EndTime>1439){Task5_EndTime=1439;}
					break;
				
				case 6:
					Task6_EndTime+=Menu_Edit_Value;
					if(Task6_EndTime<0){Task6_EndTime=0;}
					else if(Task6_EndTime>1439){Task6_EndTime=1439;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
	}
}

void TASK_OverTime_SET_3_46()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_OverTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//864000 (100MS)
			//���Ƚ�864000��100MSת����Сʱ
			//   /10ת����S  /60ת���ɷ��� ��/60ת����Сʱ 
		//	Time_100MS[2]=Task1_OverTime/2/10/60/60/10%10+'0';
		//	Time_100MS[3]=Task1_OverTime/2/10/60/60/1%10+'0';
		
			//345643(100ms)
		  //345643-9*36000=345643-324000=21643(100MS)
		  //ת����Сʱ
		  //345643/10/60/60=9.60119444Сʱ
			//ת���ɷ���
			//345643/10/60=576.071667����
		
			//691286
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task1_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OverTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task1_OverTime/10/60/2)-(Task1_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OverTime/10/60/2)-(Task1_OverTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task1_OverTime/10/2)-(Task1_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OverTime/10/2)-(Task1_OverTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task1_OverTime/2)-(Task1_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OverTime/2)-(Task1_OverTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  
			Time_100MS[1]=Task2_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task2_OverTime/10/60/2)-(Task2_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OverTime/10/60/2)-(Task2_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task2_OverTime/10/2)-(Task2_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OverTime/10/2)-(Task2_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task2_OverTime/2)-(Task2_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OverTime/2)-(Task2_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			
			Time_100MS[1]=Task3_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task3_OverTime/10/60/2)-(Task3_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OverTime/10/60/2)-(Task3_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task3_OverTime/10/2)-(Task3_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OverTime/10/2)-(Task3_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task3_OverTime/2)-(Task3_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OverTime/2)-(Task3_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			
			Time_100MS[1]=Task4_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task4_OverTime/10/60/2)-(Task4_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OverTime/10/60/2)-(Task4_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task4_OverTime/10/2)-(Task4_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OverTime/10/2)-(Task4_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task4_OverTime/2)-(Task4_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OverTime/2)-(Task4_OverTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			
			Time_100MS[1]=Task5_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task5_OverTime/10/60/2)-(Task5_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OverTime/10/60/2)-(Task5_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task5_OverTime/10/2)-(Task5_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OverTime/10/2)-(Task5_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task5_OverTime/2)-(Task5_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OverTime/2)-(Task5_OverTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			
			Time_100MS[1]=Task6_OverTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OverTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OverTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OverTime/10/60/60/2/1%10+'0';
		
			Time_100MS[6]=((Task6_OverTime/10/60/2)-(Task6_OverTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OverTime/10/60/2)-(Task6_OverTime/10/60/60/2)*60)/1%10+'0';
			
			Time_100MS[9]=((Task6_OverTime/10/2)-(Task6_OverTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OverTime/10/2)-(Task6_OverTime/10/60/2)*60)/1%10+'0';
			
			Time_100MS[12]=((Task6_OverTime/2)-(Task6_OverTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OverTime/2)-(Task6_OverTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
		
			break;
			
		case 1:  //��һ���༭λ���޸�Сʱ
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*36000*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*36000*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
					
				case 3:
					Task3_OverTime+=Menu_Edit_Value*36000*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*36000*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
					
				case 5:
					Task5_OverTime+=Menu_Edit_Value*36000*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
					
				case 6:
					Task6_OverTime+=Menu_Edit_Value*36000*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*600*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*600*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*600*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*600*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*600*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*600*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //�������༭λ������趨
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*10*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*10*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*10*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*10*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*10*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*10*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //���ĸ��༭λ��100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OverTime+=Menu_Edit_Value*2;
					if(Task1_OverTime<0){Task1_OverTime=0;}
					break;
				
				case 2:
					Task2_OverTime+=Menu_Edit_Value*2;
					if(Task2_OverTime<0){Task2_OverTime=0;}
					break;
				
				case 3:
					Task3_OverTime+=Menu_Edit_Value*2;
					if(Task3_OverTime<0){Task3_OverTime=0;}
					break;
					
				case 4:
					Task4_OverTime+=Menu_Edit_Value*2;
					if(Task4_OverTime<0){Task4_OverTime=0;}
					break;
				
				case 5:
					Task5_OverTime+=Menu_Edit_Value*2;
					if(Task5_OverTime<0){Task5_OverTime=0;}
					break;
				
				case 6:
					Task6_OverTime+=Menu_Edit_Value*2;
					if(Task6_OverTime<0){Task6_OverTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}
}

void TASK_OverTime_MODE_SET_3_47()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==2){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_OverTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			if(Task1_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  if(Task2_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			if(Task3_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			if(Task4_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			if(Task5_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			if(Task6_OverTime_Reset==1){
				LCD1602_Second_Line = TASK_OverTime_AutoReset_ON;
			}else{
				LCD1602_Second_Line = TASK_OverTime_AutoReset_OFF;
			}
			break;
	}
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
				
			break;
			
		case 1:  //��һ���༭λ���������߹ر��Զ���λ
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task1_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task1_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
				case 2:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task2_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task2_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
				case 3:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task3_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task3_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
				case 4:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task4_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task4_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
				case 5:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task5_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task5_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
				case 6:
					//ͨ���˵��༭ֵ���趨����ʱ��λ
					if(Menu_Edit_Value < 0){
						Task6_OverTime_Reset = 1;
					}else if(Menu_Edit_Value > 0){
						Task6_OverTime_Reset = 0;
					}
			
					//��λ�˵���ǰ�༭ֵ
					Menu_Edit_Value = 0;
					break;
			}
			
				//��ǰѡ����Ŀ����˸
			if(Menu_Edit_Show){  
				LCD1602_Second_Line = TASK_OverTime_AutoReset_Empty;
			}
			
			break;
		}
}

void TASK_OnTime_SET_3_48()
{
	
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_OnTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task1_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task1_OnTime/10/60/2)-(Task1_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OnTime/10/60/2)-(Task1_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task1_OnTime/10/2)-(Task1_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OnTime/10/2)-(Task1_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task1_OnTime/2)-(Task1_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OnTime/2)-(Task1_OnTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //��ȡСʱ��Ϣ
			Time_100MS[1]=Task2_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task2_OnTime/10/60/2)-(Task2_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OnTime/10/60/2)-(Task2_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task2_OnTime/10/2)-(Task2_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OnTime/10/2)-(Task2_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task2_OnTime/2)-(Task2_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OnTime/2)-(Task2_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task3_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task3_OnTime/10/60/2)-(Task3_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OnTime/10/60/2)-(Task3_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task3_OnTime/10/2)-(Task3_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OnTime/10/2)-(Task3_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task3_OnTime/2)-(Task3_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OnTime/2)-(Task3_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task4_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task4_OnTime/10/60/2)-(Task4_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OnTime/10/60/2)-(Task4_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task4_OnTime/10/2)-(Task4_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OnTime/10/2)-(Task4_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task4_OnTime/2)-(Task4_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OnTime/2)-(Task4_OnTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task5_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task5_OnTime/10/60/2)-(Task5_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OnTime/10/60/2)-(Task5_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task5_OnTime/10/2)-(Task5_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OnTime/10/2)-(Task5_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task5_OnTime/2)-(Task5_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OnTime/2)-(Task5_OnTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task6_OnTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OnTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OnTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OnTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task6_OnTime/10/60/2)-(Task6_OnTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OnTime/10/60/2)-(Task6_OnTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task6_OnTime/10/2)-(Task6_OnTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OnTime/10/2)-(Task6_OnTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task6_OnTime/2)-(Task6_OnTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OnTime/2)-(Task6_OnTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //��һ���༭λ���޸�Сʱ
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*36000*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*36000*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
					
				case 3:
					Task3_OnTime+=Menu_Edit_Value*36000*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*36000*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
					
				case 5:
					Task5_OnTime+=Menu_Edit_Value*36000*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
					
				case 6:
					Task6_OnTime+=Menu_Edit_Value*36000*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*600*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*600*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*600*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*600*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*600*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*600*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //�������༭λ������趨
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*10*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*10*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*10*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*10*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*10*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*10*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //���ĸ��༭λ��100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OnTime+=Menu_Edit_Value*2;
					if(Task1_OnTime<0){Task1_OnTime=0;}
					break;
				
				case 2:
					Task2_OnTime+=Menu_Edit_Value*2;
					if(Task2_OnTime<0){Task2_OnTime=0;}
					break;
				
				case 3:
					Task3_OnTime+=Menu_Edit_Value*2;
					if(Task3_OnTime<0){Task3_OnTime=0;}
					break;
					
				case 4:
					Task4_OnTime+=Menu_Edit_Value*2;
					if(Task4_OnTime<0){Task4_OnTime=0;}
					break;
				
				case 5:
					Task5_OnTime+=Menu_Edit_Value*2;
					if(Task5_OnTime<0){Task5_OnTime=0;}
					break;
				
				case 6:
					Task6_OnTime+=Menu_Edit_Value*2;
					if(Task6_OnTime<0){Task6_OnTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//100MS����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}
}

void TASK_OffTime_SET_3_49()
{
	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_OffTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task1_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //��ȡСʱ��Ϣ
			Time_100MS[1]=Task2_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task3_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task4_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task5_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task6_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //��һ���༭λ���޸�Сʱ
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*36000*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*36000*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
					
				case 3:
					Task3_OffTime+=Menu_Edit_Value*36000*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*36000*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
					
				case 5:
					Task5_OffTime+=Menu_Edit_Value*36000*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
					
				case 6:
					Task6_OffTime+=Menu_Edit_Value*36000*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*600*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*600*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*600*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*600*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*600*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*600*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //�������༭λ������趨
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*10*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*10*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*10*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*10*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*10*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*10*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //���ĸ��༭λ��100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//100MS����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}

	//��ʾλ������λ0���л�Ϊ��Ŀ
	if(Menu_Edit==5){Menu_Edit=0;};
	
	//��ʾ��ǰҳ��������Ŀ
	LCD1602_First_Line = TASK_OffTime;
	switch(TASK_SET_Number)
	{
		case 1: 
			LCD1602_First_Line[4]='1';
			
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task1_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task1_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task1_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task1_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task1_OffTime/10/60/2)-(Task1_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task1_OffTime/10/2)-(Task1_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task1_OffTime/2)-(Task1_OffTime/10/2)*10)/1%10+'0';
			break;
		case 2: 
			LCD1602_First_Line[4]='2';
		  //��ȡСʱ��Ϣ
			Time_100MS[1]=Task2_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task2_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task2_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task2_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task2_OffTime/10/60/2)-(Task2_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task2_OffTime/10/2)-(Task2_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task2_OffTime/2)-(Task2_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 3: 
			LCD1602_First_Line[4]='3';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task3_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task3_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task3_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task3_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task3_OffTime/10/60/2)-(Task3_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task3_OffTime/10/2)-(Task3_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task3_OffTime/2)-(Task3_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 4: 
			LCD1602_First_Line[4]='4';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task4_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task4_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task4_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task4_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task4_OffTime/10/60/2)-(Task4_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task4_OffTime/10/2)-(Task4_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task4_OffTime/2)-(Task4_OffTime/10/2)*10)/1%10+'0';
			
		  break;
		case 5: 
			LCD1602_First_Line[4]='5';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task5_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task5_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task5_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task5_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task5_OffTime/10/60/2)-(Task5_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task5_OffTime/10/2)-(Task5_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task5_OffTime/2)-(Task5_OffTime/10/2)*10)/1%10+'0';
			
			break;
		case 6: 
			LCD1602_First_Line[4]='6';
			//��ȡСʱ��Ϣ
			Time_100MS[1]=Task6_OffTime/10/60/60/2/1000%10+'0';
			Time_100MS[2]=Task6_OffTime/10/60/60/2/100%10+'0';
			Time_100MS[3]=Task6_OffTime/10/60/60/2/10%10+'0';
			Time_100MS[4]=Task6_OffTime/10/60/60/2/1%10+'0';
		
			//��ȡ������Ϣ
			//��ʱ���ȥСʱ���֣�ʣ�·��Ӳ���
			//��ʱ��ת���ɷ���
			Time_100MS[6]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/10%10+'0';
			Time_100MS[7]=((Task6_OffTime/10/60/2)-(Task6_OffTime/10/60/60/2)*60)/1%10+'0';
			
			//��ȡ����Ϣ
			Time_100MS[9]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/10%10+'0';
			Time_100MS[10]=((Task6_OffTime/10/2)-(Task6_OffTime/10/60/2)*60)/1%10+'0';
		
			//��ȡ100MS��Ϣ		
			Time_100MS[12]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/10%10+'0';
			Time_100MS[13]=((Task6_OffTime/2)-(Task6_OffTime/10/2)*10)/1%10+'0';
			
			break;
	}
	LCD1602_Second_Line = Time_100MS;
	
	//��ʾ��ͬ��ʾλʱ��״̬
	switch(Menu_Edit)
	{
		case 0:   //��Ŀ״̬
			
			Menu_Flag = 3;
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			break;
			
		case 1:  //��һ���༭λ���޸�Сʱ
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*36000*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*36000*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
					
				case 3:
					Task3_OffTime+=Menu_Edit_Value*36000*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*36000*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
					
				case 5:
					Task5_OffTime+=Menu_Edit_Value*36000*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
					
				case 6:
					Task6_OffTime+=Menu_Edit_Value*36000*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//Сʱ����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[1] = ' ';
				LCD1602_Second_Line[2] = ' ';
				LCD1602_Second_Line[3] = ' ';
				LCD1602_Second_Line[4] = ' ';
			}
			break;
			
		case 2:
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*600*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*600*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*600*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*600*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*600*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*600*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[6] = ' ';
				LCD1602_Second_Line[7] = ' ';
			}
			break;
			
		case 3:  //�������༭λ������趨
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*10*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*10*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*10*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*10*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*10*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*10*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//���ӵ���˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[9] = ' ';
				LCD1602_Second_Line[10] = ' ';
			}
			break;
		
		case 4:  //���ĸ��༭λ��100MS
			Menu_Flag = 4;
		
			switch(TASK_SET_Number)
			{
				case 1:
					Task1_OffTime+=Menu_Edit_Value*2;
					if(Task1_OffTime<0){Task1_OffTime=0;}
					break;
				
				case 2:
					Task2_OffTime+=Menu_Edit_Value*2;
					if(Task2_OffTime<0){Task2_OffTime=0;}
					break;
				
				case 3:
					Task3_OffTime+=Menu_Edit_Value*2;
					if(Task3_OffTime<0){Task3_OffTime=0;}
					break;
					
				case 4:
					Task4_OffTime+=Menu_Edit_Value*2;
					if(Task4_OffTime<0){Task4_OffTime=0;}
					break;
				
				case 5:
					Task5_OffTime+=Menu_Edit_Value*2;
					if(Task5_OffTime<0){Task5_OffTime=0;}
					break;
				
				case 6:
					Task6_OffTime+=Menu_Edit_Value*2;
					if(Task6_OffTime<0){Task6_OffTime=0;}
					break;
			}
		
			//��λ�˵���ǰ�༭ֵ
			Menu_Edit_Value = 0;
			
			//��ǰѡ����Ŀ����˸
			//100MS����˸
			if(Menu_Edit_Show==0){
			  LCD1602_Second_Line[12] = ' ';
				LCD1602_Second_Line[13] = ' ';
			}
			break;
		
	}

	
}

void RETURN_3_50()
{
	Menu_Flag = 5;
	LCD1602_First_Line = RETURN_Select;
	LCD1602_Second_Line = Menu_Empty_Line;
}



