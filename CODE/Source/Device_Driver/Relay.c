#include "Config.h"
#include "Relay.h"

extern u16 NowTime;  //����ʱ��

/*��Ҫ�����ò˵����õı���*/

/*���ڼ�¼�˿��Ƿ񱻴���*/
//Pin12�����Ӧ��־,������Ӧ�����
bit Pin12 = 0; 
bit Pin13 = 0; 
bit Pin14 = 0;
bit Pin15 = 0;
bit Pin16 = 0;
bit Pin17 = 0;

bit Pin20 = 0;
bit Pin21 = 0;
bit Pin22 = 0;
bit Pin23 = 0;
bit Pin24 = 0;

bit Pin35 = 0;
bit Pin36 = 0;
bit Pin37 = 0;

/*�˿ڵĴ���ģʽ*/
/*����ģʽ��0Ϊ����ģʽ����1Ϊ����ģʽ��*/
//����ģʽ���������£��ͷŲŻ��������״̬
//����ģʽ���������£����̸�������״̬�������ͷŲſ����¸���
bdata u16 Pin_Trigger_Mode;

sbit Pin10_Trigger_Mode = Pin_Trigger_Mode^0;
sbit Pin11_Trigger_Mode = Pin_Trigger_Mode^1;

sbit Pin12_Trigger_Mode = Pin_Trigger_Mode^2;
sbit Pin13_Trigger_Mode = Pin_Trigger_Mode^3;
sbit Pin14_Trigger_Mode = Pin_Trigger_Mode^4;
sbit Pin15_Trigger_Mode = Pin_Trigger_Mode^5;
sbit Pin16_Trigger_Mode = Pin_Trigger_Mode^6;
sbit Pin17_Trigger_Mode = Pin_Trigger_Mode^7;

sbit Pin20_Trigger_Mode = Pin_Trigger_Mode^8;
sbit Pin21_Trigger_Mode = Pin_Trigger_Mode^9;
sbit Pin22_Trigger_Mode = Pin_Trigger_Mode^10;
sbit Pin23_Trigger_Mode = Pin_Trigger_Mode^11;
sbit Pin24_Trigger_Mode = Pin_Trigger_Mode^12;

sbit Pin35_Trigger_Mode = Pin_Trigger_Mode^13;
sbit Pin36_Trigger_Mode = Pin_Trigger_Mode^14;
sbit Pin37_Trigger_Mode = Pin_Trigger_Mode^15;

/*
bit Pin10_Trigger_Mode = 0;
bit Pin11_Trigger_Mode = 0;

bit Pin12_Trigger_Mode = 1;
bit Pin13_Trigger_Mode = 1;
bit Pin14_Trigger_Mode = 0;
bit Pin15_Trigger_Mode = 0;
bit Pin16_Trigger_Mode = 0;
bit Pin17_Trigger_Mode = 0;

bit Pin20_Trigger_Mode = 1;
bit Pin21_Trigger_Mode = 1;
bit Pin22_Trigger_Mode = 1;
bit Pin23_Trigger_Mode = 1;
bit Pin24_Trigger_Mode = 1;

bit Pin35_Trigger_Mode = 0;
bit Pin36_Trigger_Mode = 0;
bit Pin37_Trigger_Mode = 0;
*/

/*�˿��ⲿ��ģ�ⰴ��*/
/*0������״̬��û�а��£�1���������ڰ��µ�״̬*/
bit Pin10_Key = 0;
bit Pin11_Key = 0;

bit Pin12_Key = 0;
bit Pin13_Key = 0;
bit Pin14_Key = 0;
bit Pin15_Key = 0;
bit Pin16_Key = 0;
bit Pin17_Key = 0;

bit Pin20_Key = 0;
bit Pin21_Key = 0;
bit Pin22_Key = 0;
bit Pin23_Key = 0;
bit Pin24_Key = 0;

bit Pin35_Key = 0;
bit Pin36_Key = 0;
bit Pin37_Key = 0;

/*����ģʽʱ��Ϊ�˿ڴ������������*/ 
/*���ģʽʱѡ����������*/
/*�˿�ģʽ��0Ϊ����ģʽ����1Ϊ���ģʽ��*/
bdata u16 Pin_Mode;  //��λѰַ����

sbit Pin10_Mode = Pin_Mode^0;
sbit Pin11_Mode = Pin_Mode^1;

sbit Pin12_Mode = Pin_Mode^2;
sbit Pin13_Mode = Pin_Mode^3;
sbit Pin14_Mode = Pin_Mode^4;
sbit Pin15_Mode = Pin_Mode^5;
sbit Pin16_Mode = Pin_Mode^6;
sbit Pin17_Mode = Pin_Mode^7;

sbit Pin20_Mode = Pin_Mode^8;
sbit Pin21_Mode = Pin_Mode^9;
sbit Pin22_Mode = Pin_Mode^10;
sbit Pin23_Mode = Pin_Mode^11;
sbit Pin24_Mode = Pin_Mode^12;

sbit Pin35_Mode = Pin_Mode^13;
sbit Pin36_Mode = Pin_Mode^14;
sbit Pin37_Mode = Pin_Mode^15;

s8 xdata Pin10_Task_Number = 1; //	bit Pin10_Mode = 1;
s8 xdata Pin11_Task_Number = 2;	//  bit Pin11_Mode = 1;

s8 xdata Pin12_Task_Number = 1; //  bit Pin12_Mode = 0;
s8 xdata Pin13_Task_Number = 2;	//  bit Pin13_Mode = 0;
s8 xdata Pin14_Task_Number = 3;	//  bit Pin14_Mode = 0;
s8 xdata Pin15_Task_Number = 4;	//  bit Pin15_Mode = 0;
s8 xdata Pin16_Task_Number = 5;	//  bit Pin16_Mode = 0;
s8 xdata Pin17_Task_Number = 6;	//  bit Pin17_Mode = 0;

s8 xdata Pin20_Task_Number = 4;	//  bit Pin20_Mode = 0;
s8 xdata Pin21_Task_Number = 4;	//  bit Pin21_Mode = 0;
s8 xdata Pin22_Task_Number = 4; //  bit Pin22_Mode = 0;
s8 xdata Pin23_Task_Number = 4;	//  bit Pin23_Mode = 0;
s8 xdata Pin24_Task_Number = 4; //  bit Pin24_Mode = 0;

s8 xdata Pin35_Task_Number = 1; //  bit Pin35_Mode = 1;
s8 xdata Pin36_Task_Number = 2;	//  bit Pin36_Mode = 1;
s8 xdata Pin37_Task_Number = 3;	//  bit Pin37_Mode = 1;



/*��Ҫ���µ������*/
u8 Task_Number = 0;  //������������ţ�����������
u8 Task_Number_Immediate = 0;  //������������� ������������

/*�������п���λ*/
bit Task1 = 0;  //����1 ����(1)/��ͣ(0)
bit Task2 = 0;
bit Task3 = 0;
bit Task4 = 0;
bit Task5 = 0;
bit Task6 = 0;

/*��������ģʽ*/
u8 xdata Task1_Mode = 1;  //����1����ʱ��ģʽ
u8 xdata Task2_Mode = 1;
u8 xdata Task3_Mode = 1;
u8 xdata Task4_Mode = 1;
u8 xdata Task5_Mode = 1;
u8 xdata Task6_Mode = 1;

/*�������λ*/
bit Task1_Output = 0;
bit Task2_Output = 0;
bit Task3_Output = 0;
bit Task4_Output = 0;
bit Task5_Output = 0;
bit Task6_Output = 0;

/*ʱ�������Ъģʽ*/

//����������
bdata u8 Task_OverTime_Reset;  //���ÿ�λѰַ����
sbit Task1_OverTime_Reset = Task_OverTime_Reset^1;
sbit Task2_OverTime_Reset = Task_OverTime_Reset^2;
sbit Task3_OverTime_Reset = Task_OverTime_Reset^3;
sbit Task4_OverTime_Reset = Task_OverTime_Reset^4;
sbit Task5_OverTime_Reset = Task_OverTime_Reset^5;
sbit Task6_OverTime_Reset = Task_OverTime_Reset^6;

/*����һ*/
s16 xdata Task1_StartTime = 0;//����1��ʼ����ʱ��
s16 xdata Task1_EndTime = 1439;//����1��������ʱ��
s32 xdata Task1_OverTime = 2*3000; //����1���г�ʱʱ��
u32 xdata Task1_OverTime_Count=0; //����1���г�ʱʱ�������
//bit Task1_OverTime_Reset = 0; //����1���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task1_OnState = 1; //��ʾTask1���ON״̬ 1������� 0�������
s32 xdata Task1_OnTime = 2*1;  //��ʾTask1���ON״̬��ʱ��
s32 xdata Task1_OffTime = 2*1; //��ʾTask1���OFF״̬��ʱ��

u32 xdata Task1_CountTime = 1;  //����1 ON/OFF״̬ʱ�������

/*�����*/
s16 xdata Task2_StartTime = 0;//����2��ʼ����ʱ��
s16 xdata Task2_EndTime = 1439;//����2��������ʱ��
s32 xdata Task2_OverTime = 2*3000; //����2���г�ʱʱ��
u32 xdata Task2_OverTime_Count=0; //����2���г�ʱʱ�������
//bit Task2_OverTime_Reset = 0; //����2���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task2_OnState = 1; //��ʾTask2���ON״̬ 1������� 0�������
s32 xdata Task2_OnTime = 2*1;  //��ʾTask2���ON״̬��ʱ��
s32 xdata Task2_OffTime = 2*1; //��ʾTask2���OFF״̬��ʱ��

u32 xdata Task2_CountTime = 1;  //����2 ON/OFF״̬ʱ�������

/*������*/
s16 xdata Task3_StartTime = 0;//����3��ʼ����ʱ��
s16 xdata Task3_EndTime = 1439;//����3��������ʱ��
s32 xdata Task3_OverTime = 2*3000; //����3���г�ʱʱ��
u32 xdata Task3_OverTime_Count=0; //����3���г�ʱʱ�������
//bit Task3_OverTime_Reset = 0; //����3���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task3_OnState = 1; //��ʾTask3���ON״̬ 1������� 0�������
s32 xdata Task3_OnTime = 2*1;  //��ʾTask3���ON״̬��ʱ��
s32 xdata Task3_OffTime = 2*1; //��ʾTask3���OFF״̬��ʱ��

u32 xdata Task3_CountTime = 1;  //����3 ON/OFF״̬ʱ�������

/*������*/
s16 xdata Task4_StartTime = 0;//����4��ʼ����ʱ��
s16 xdata Task4_EndTime = 1439;//����4��������ʱ��
s32 xdata Task4_OverTime = 2*3000; //����4���г�ʱʱ��
u32 xdata Task4_OverTime_Count=0; //����4���г�ʱʱ�������
//bit Task4_OverTime_Reset = 0; //����4���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task4_OnState = 1; //��ʾTask4���ON״̬ 1������� 0�������
s32 xdata Task4_OnTime = 2*1;  //��ʾTask4���ON״̬��ʱ��
s32 xdata Task4_OffTime = 2*1; //��ʾTask4���OFF״̬��ʱ��

u32 xdata Task4_CountTime = 1;  //����4 ON/OFF״̬ʱ�������

/*������*/
s16 xdata Task5_StartTime = 0;//����5��ʼ����ʱ��
s16 xdata Task5_EndTime = 1439;//����5��������ʱ��
s32 xdata Task5_OverTime = 2*3000; //����5���г�ʱʱ��
u32 xdata Task5_OverTime_Count=0; //����5���г�ʱʱ�������
//bit Task5_OverTime_Reset = 0; //����5���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task5_OnState = 1; //��ʾTask5���ON״̬ 1������� 0�������
s32 xdata Task5_OnTime = 2*1;  //��ʾTask5���ON״̬��ʱ��
s32 xdata Task5_OffTime = 2*1; //��ʾTask5���OFF״̬��ʱ��

u32 xdata Task5_CountTime = 1;  //����5 ON/OFF״̬ʱ�������

/*������*/
s16 xdata Task6_StartTime = 0;//����6��ʼ����ʱ��
s16 xdata Task6_EndTime = 1439;//����6��������ʱ��
s32 xdata Task6_OverTime = 2*3000; //����6���г�ʱʱ��
u32 xdata Task6_OverTime_Count=0; //����6���г�ʱʱ�������
//bit Task6_OverTime_Reset = 0; //����6���г�ʱ�Զ���λ����λ
                              //���ڿ��������Ƿ���������
															//1:�Զ���λ ������ʱ����λ��ʱ������������������
															//0:���Զ���λ ����ʱ���ر�

bit Task6_OnState = 1; //��ʾTask6���ON״̬ 1������� 0�������
s32 xdata Task6_OnTime = 2*1;  //��ʾTask6���ON״̬��ʱ��
s32 xdata Task6_OffTime = 2*1; //��ʾTask6���OFF״̬��ʱ��

u32 xdata Task6_CountTime = 1;  //����6 ON/OFF״̬ʱ�������

/******************************************************************************/
// �������ƣ�Task_Input_Update
// �����������
// ����������� 
// �������ܣ��Զ˿ڽ���ɨ�裬���ڴ����̵�������
//		 ˵�������ȼ�¼�����б������������Ͷ˿ڣ����ö˿�
//					 ���ͷţ�����¸ö˿���ƥ�������ͬʱ���
//					 �˿ڼ�¼
/******************************************************************************/
void Task_Input_Update(void)
{
	/*��¼�����б������Ķ˿�*/
	/*����˿�ģʽ�� 1.����ģʽ
						����Ϊ 2.����ģʽ
									 3.�˿ڱ�����
			���¼*/
	if((Pin12_Mode==0)&&(Pin12_Trigger_Mode==0)&&(P12==0)){Pin12=1;}
	if((Pin13_Mode==0)&&(Pin13_Trigger_Mode==0)&&(P13==0)){Pin13=1;}
	if((Pin14_Mode==0)&&(Pin14_Trigger_Mode==0)&&(P14==0)){Pin14=1;}
	if((Pin15_Mode==0)&&(Pin15_Trigger_Mode==0)&&(P15==0)){Pin15=1;}
	if((Pin16_Mode==0)&&(Pin16_Trigger_Mode==0)&&(P16==0)){Pin16=1;}
	if((Pin17_Mode==0)&&(Pin17_Trigger_Mode==0)&&(P17==0)){Pin17=1;}
	
	if((Pin20_Mode==0)&&(Pin20_Trigger_Mode==0)&&(P20==0)){Pin20=1;}
	if((Pin21_Mode==0)&&(Pin21_Trigger_Mode==0)&&(P21==0)){Pin21=1;}
	if((Pin22_Mode==0)&&(Pin22_Trigger_Mode==0)&&(P22==0)){Pin22=1;}
	if((Pin23_Mode==0)&&(Pin23_Trigger_Mode==0)&&(P23==0)){Pin23=1;}
	if((Pin24_Mode==0)&&(Pin24_Trigger_Mode==0)&&(P24==0)){Pin24=1;}
	
	if((Pin35_Mode==0)&&(Pin35_Trigger_Mode==0)&&(P35==0)){Pin35=1;}
	if((Pin36_Mode==0)&&(Pin36_Trigger_Mode==0)&&(P36==0)){Pin36=1;}
	if((Pin37_Mode==0)&&(Pin37_Trigger_Mode==0)&&(P37==0)){Pin37=1;}
	
	
	/*����ģʽ�ĸ���*/
	/*ÿ��ֻ����һ������״̬*/
  //��ÿһ����¼�Ķ˿ڽ���ɨ��ִ�����������
	//�ٶ������ж�����񱻼�¼
	//����ɨ������ֻ����һ����¼�ź�,���Ҵ�ʱ�˿ڱ��ͷ�
	if((Pin12==1)&&(P12==1)){		
		/*�������������ΪPin12���������*/
		Task_Number = Pin12_Task_Number;  
		Pin12=0;   //��λ�˿ڴ���״̬
	}
  else if((Pin13==1)&&(P13==1)){   //���ּ��
		Task_Number = Pin13_Task_Number;
		Pin13=0;   
	}
	else if((Pin14==1)&&(P14==1)){   //���ּ��
		Task_Number = Pin14_Task_Number;
		Pin14=0;   
	}
	else if((Pin15==1)&&(P15==1)){   //���ּ��
		Task_Number = Pin15_Task_Number;
		Pin15=0;   
	}
	else if((Pin16==1)&&(P16==1)){   //���ּ��
		Task_Number = Pin16_Task_Number;
		Pin16=0;   
	}
	else if((Pin17==1)&&(P17==1)){  //���ּ��
		Task_Number = Pin17_Task_Number;
		Pin17=0;   
	}
	else if((Pin20==1)&&(P20==1)){  //���ּ��
		Task_Number = Pin20_Task_Number;
		Pin20=0;   
	}
	else if((Pin21==1)&&(P21==1)){   //���ּ��
		Task_Number = Pin21_Task_Number;
		Pin21=0;   
	}
	else if((Pin22==1)&&(P22==1)){   //���ּ��
		Task_Number = Pin22_Task_Number;
		Pin22=0;   
	}
	else if((Pin23==1)&&(P23==1)){   //���ּ��
		Task_Number = Pin23_Task_Number;
		Pin23=0;   
	}
	else if((Pin24==1)&&(P24==1)){   //���ּ��
		Task_Number = Pin24_Task_Number;
		Pin24=0;   
	}
	else if((Pin35==1)&&(P35==1)){   //���ּ��
		Task_Number = Pin35_Task_Number;
		Pin35=0;   
	}
	else if((Pin36==1)&&(P36==1)){   //���ּ��
		Task_Number = Pin36_Task_Number;
		Pin36=0;   
	}
	else if((Pin37==1)&&(P37==1)){   //���ּ��
		Task_Number = Pin37_Task_Number;
		Pin37=0;   
	}
	
		
	/*����˿�ģʽ�� 1.����ģʽ
	            ���� 2.��������ģʽ
						  ���� 3.�ⲿģ�ⰴ��״̬Ϊδ����
						  ���� 4.�˿ڴ��ڴ���״̬
						����������*/
	
	if((Pin12_Mode==0)&&(Pin12_Trigger_Mode==1)&&(Pin12_Key==0)&&(P12==0)){
		Task_Number_Immediate = Pin12_Task_Number; //�������������
		Pin12_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����		
	}
	else if((Pin13_Mode==0)&&(Pin13_Trigger_Mode==1)&&(Pin13_Key==0)&&(P13==0)){
		Task_Number_Immediate = Pin13_Task_Number;
		Pin13_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin14_Mode==0)&&(Pin14_Trigger_Mode==1)&&(Pin14_Key==0)&&(P14==0)){
		Task_Number_Immediate = Pin14_Task_Number;
		Pin14_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin15_Mode==0)&&(Pin15_Trigger_Mode==1)&&(Pin15_Key==0)&&(P15==0)){
		Task_Number_Immediate = Pin15_Task_Number;
		Pin15_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin16_Mode==0)&&(Pin16_Trigger_Mode==1)&&(Pin16_Key==0)&&(P16==0)){
		Task_Number_Immediate = Pin16_Task_Number;
		Pin16_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin17_Mode==0)&&(Pin17_Trigger_Mode==1)&&(Pin17_Key==0)&&(P17==0)){
		Task_Number_Immediate = Pin17_Task_Number;
		Pin17_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	
	else if((Pin20_Mode==0)&&(Pin20_Trigger_Mode==1)&&(Pin20_Key==0)&&(P20==0)){
		Task_Number_Immediate = Pin20_Task_Number;
		Pin20_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin21_Mode==0)&&(Pin21_Trigger_Mode==1)&&(Pin21_Key==0)&&(P21==0)){
		Task_Number_Immediate = Pin21_Task_Number;
		Pin21_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin22_Mode==0)&&(Pin22_Trigger_Mode==1)&&(Pin22_Key==0)&&(P22==0)){
		Task_Number_Immediate = Pin22_Task_Number;
		Pin22_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin23_Mode==0)&&(Pin23_Trigger_Mode==1)&&(Pin23_Key==0)&&(P23==0)){
		Task_Number_Immediate = Pin23_Task_Number;
		Pin23_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin24_Mode==0)&&(Pin24_Trigger_Mode==1)&&(Pin24_Key==0)&&(P24==0)){
		Task_Number_Immediate = Pin24_Task_Number;
		Pin24_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	
	else if((Pin35_Mode==0)&&(Pin35_Trigger_Mode==1)&&(Pin35_Key==0)&&(P35==0)){
		Task_Number_Immediate = Pin35_Task_Number;
		Pin35_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin36_Mode==0)&&(Pin36_Trigger_Mode==1)&&(Pin36_Key==0)&&(P36==0)){
		Task_Number_Immediate = Pin36_Task_Number;
		Pin36_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	else if((Pin37_Mode==0)&&(Pin37_Trigger_Mode==1)&&(Pin37_Key==0)&&(P37==0)){
		Task_Number_Immediate = Pin37_Task_Number;
		Pin37_Key = 1;   //�ⲿ���ⰴ��״̬��Ϊ����
	}
	
	
	//����˿ڱ��ͷţ��ⲿ���ⰴ����Ϊδ���£�������������
	if((Pin12_Key==1)&&(P12==1)){Pin12_Key = 0;}
  if((Pin13_Key==1)&&(P13==1)){Pin13_Key = 0;}
  if((Pin14_Key==1)&&(P14==1)){Pin14_Key = 0;}
  if((Pin15_Key==1)&&(P15==1)){Pin15_Key = 0;}
  if((Pin16_Key==1)&&(P16==1)){Pin16_Key = 0;}
  if((Pin17_Key==1)&&(P17==1)){Pin17_Key = 0;} 

  if((Pin20_Key==1)&&(P20==1)){Pin20_Key = 0;}
  if((Pin21_Key==1)&&(P21==1)){Pin21_Key = 0;}
  if((Pin22_Key==1)&&(P22==1)){Pin22_Key = 0;}	
	if((Pin23_Key==1)&&(P23==1)){Pin23_Key = 0;}
	if((Pin24_Key==1)&&(P24==1)){Pin24_Key = 0;}
	
	if((Pin35_Key==1)&&(P35==1)){Pin35_Key = 0;}
	if((Pin36_Key==1)&&(P36==1)){Pin36_Key = 0;}
	if((Pin37_Key==1)&&(P37==1)){Pin37_Key = 0;}
	
	/*����ģʽ�����µĴ�������*/
	switch(Task_Number)
	{
		case 1:   //����1
			Task1=~Task1;  //������ر�����1
			Task_Number = 0; //��λҪ���µ������
			break;
		case 2:   //����2
			Task2=~Task2;  //������ر�����2
			Task_Number = 0;
			break;
		case 3:   //����3
			Task3=~Task3;  //������ر�����3
			Task_Number = 0;
			break;
		case 4:   //����4
			Task4=~Task4;  //������ر�����4
			Task_Number = 0;
			break;
		case 5:   //����5
			Task5=~Task5;  //������ر�����5
			Task_Number = 0;
			break;
		case 6:   //����6
			Task6=~Task6;  //������ر�����6
			Task_Number = 0;
			break;
	}
	
	/*����ģʽ��������״̬*/
	switch(Task_Number_Immediate)
	{
		case 1:   //����1
			Task1=1;  //��������1
			Task_Number_Immediate = 0; //��λҪ���µ������
			break;
		case 2:   //����2
			Task2=1;  //��������2
			Task_Number_Immediate = 0;
			break;
		case 3:   //����3
			Task3=1;  //��������3
			Task_Number_Immediate = 0;
			break;
		case 4:   //����4
			Task4=1;  //��������4
			Task_Number_Immediate = 0;
			break;
		case 5:   //����5
			Task5=1;  //��������5
			Task_Number_Immediate = 0;
			break;
		case 6:   //����6
			Task6=1;  //��������6
			Task_Number_Immediate = 0;
			break;
	
	}
}
/******************************************************************************/
// �������ƣ�(Task1~Task6)_Update
// �����������
// ����������� 
// �������ܣ�ִ��������
/******************************************************************************/

void Task1_Output_Update(void)
{
		if(Task1 == 1)
		{
			switch(Task1_Mode)
			{
				case 1:
					if((Task1_StartTime<=NowTime)&&(NowTime<=Task1_EndTime)
						&&(Task1_OverTime_Count<Task1_OverTime)){ 
							Task1_OverTime_Count++;
						
							if(Task1_OnState==1) //�����������On״̬
								{
									
								if(Task1_CountTime<Task1_OnTime){
									Task1_CountTime++;
									Task1_Output = 1;
								}else{
									Task1_CountTime = 1;  //��λʱ�������
									Task1_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task1_CountTime<Task1_OffTime){
									Task1_CountTime++;
									Task1_Output = 0;
								}else{
									Task1_CountTime = 1;  //��λʱ�������
									Task1_OnState = 1; //�л���ON״̬
								}
							}	
							
				  }else{  //������ʱ���������������
								
								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ
						
						//�������һ����ʱ�����䵫��û�г�ʱ
						//���»ص�ʱ�����佫���¿�ʼ
						//Ĭ�����ON
						if(Task1_OverTime_Count<Task1_OverTime){
							
							Task1_Output = 0;   //��ֹ����1���
							Task1_OverTime_Count=0;  //��λ��ʱ������
							Task1_CountTime = 1;  //��λʱ�������
							Task1_OnState = 1; //�л���ON״̬
							
							//�����������һ�Ѿ���ʱ
						}else if(Task1_OverTime_Count==Task1_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ,Ϊ�˳�������
							if(Task1_OverTime_Reset){
								
								Task1_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task1=0; //�ر�Task
								Task1_OverTime_Count=0;  //��λ��ʱ������
								Task1_CountTime = 1;  //��λʱ�������
								Task1_OnState = 1; //�л���ON״̬
								Task1_Output = 0;   //��ֹ����1���
								
							}
							
						}
						
					}
					break;
			}
		}else{  //������������������
			Task1_OverTime_Count=0;  //��λ��ʱ������
			Task1_CountTime = 1;  //��λʱ�������
			Task1_OnState = 1; //�л���ON״̬
			Task1_Output = 0;   //��ֹ����1���
			
		}
		
/******************************************************************************/
// ����һ��������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task1_Output==1){
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=1;}
	}
}

void Task2_Output_Update(void)
{
		if(Task2 == 1)
		{
			switch(Task2_Mode)
			{
				case 1:
					if((Task2_StartTime<=NowTime)&&(NowTime<=Task2_EndTime)
						&&(Task2_OverTime_Count<Task2_OverTime)){
							Task2_OverTime_Count++;
						
							if(Task2_OnState==1) //�����������On״̬
								{
									
								if(Task2_CountTime<Task2_OnTime){
									Task2_CountTime++;
									Task2_Output = 1;
								}else{
									Task2_CountTime = 1;  //��λʱ�������
									Task2_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task2_CountTime<Task2_OffTime){
									Task2_CountTime++;
									Task2_Output = 0;
								}else{
									Task2_CountTime = 1;  //��λʱ�������
									Task2_OnState = 1; //�л���ON״̬
								}
							}	
							
			   }else{  //������ʱ���������������

								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ					 
					 
					 //������������ʱ�����䵫��û�г�ʱ
						if(Task2_OverTime_Count<Task2_OverTime){
							
							Task2_OverTime_Count=0;  //��λ��ʱ������
							Task2_CountTime = 1;  //��λʱ�������
							Task2_Output = 0;   //��ֹ����2���
							Task2_OnState = 1; //�л���ON״̬
							
							//�����������һ�Ѿ���ʱ
						}else if(Task2_OverTime_Count==Task2_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ
							if(Task2_OverTime_Reset){
								
								Task2_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task2=0; //�ر�Task
								Task2_OverTime_Count=0;  //��λ��ʱ������
								Task2_CountTime = 1;  //��λʱ�������
								Task2_Output = 0;   //��ֹ����2���
								Task2_OnState = 1; //�л���ON״̬
							}
							
						}
				 }
				 break;
		  }
		}else{
			Task2_OverTime_Count=0;  //��λ��ʱ������
			Task2_CountTime = 1;  //��λʱ�������
			Task2_Output = 0;   //��ֹ����2���
			Task2_OnState = 1; //�л���ON״̬
		}
		
/******************************************************************************/
// �������������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task2_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=1;}
	}		
}


void Task3_Output_Update(void)
{
		if(Task3 == 1)
		{
			switch(Task3_Mode)
			{
				case 1:
					if((Task3_StartTime<=NowTime)&&(NowTime<=Task3_EndTime)
						&&(Task3_OverTime_Count<Task3_OverTime)){ 
							Task3_OverTime_Count++;
						
							if(Task3_OnState==1) //�����������On״̬
								{
									
								if(Task3_CountTime<Task3_OnTime){
									Task3_CountTime++;
									Task3_Output = 1;
								}else{
									Task3_CountTime = 1;  //��λʱ�������
									Task3_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task3_CountTime<Task3_OffTime){
									Task3_CountTime++;
									Task3_Output = 0;
								}else{
									Task3_CountTime = 1;  //��λʱ�������
									Task3_OnState = 1; //�л���ON״̬
								}
							}	
							
				  }else{  //������ʱ���������������
								
								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ
						
						//�������������ʱ�����䵫��û�г�ʱ
						if(Task3_OverTime_Count<Task3_OverTime){
							
							Task3_OverTime_Count=0;  //��λ��ʱ������
							Task3_CountTime = 1;  //��λʱ�������
							Task3_Output = 0;   //��ֹ����3���
							Task3_OnState = 1; //�л���ON״̬
							
							//��������������Ѿ���ʱ
						}else if(Task3_OverTime_Count==Task3_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ
							if(Task3_OverTime_Reset){
								
								Task3_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task3=0; //�ر�Task
								Task3_OverTime_Count=0;  //��λ��ʱ������
								Task3_CountTime = 1;  //��λʱ�������
								Task3_Output = 0;   //��ֹ����3���
								Task3_OnState = 1; //�л���ON״̬
							}
							
						}  
					}
					break;
			}
		}else{  //������������������
			Task3_OverTime_Count=0;  //��λ��ʱ������
			Task3_CountTime = 1;  //��λʱ�������
			Task3_Output = 0;   //��ֹ����3���
			Task3_OnState = 1; //�л���ON״̬
		}
		
/******************************************************************************/
// ��������������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task3_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=1;}
	}	
}

void Task4_Output_Update(void)
{
		if(Task4 == 1)
		{
			switch(Task4_Mode)
			{
				case 1:
					if((Task4_StartTime<=NowTime)&&(NowTime<=Task4_EndTime)
						&&(Task4_OverTime_Count<Task4_OverTime)){ 
							Task4_OverTime_Count++;
						
							if(Task4_OnState==1) //�����������On״̬
								{
									
								if(Task4_CountTime<Task4_OnTime){
									Task4_CountTime++;
									Task4_Output = 1;
								}else{
									Task4_CountTime = 1;  //��λʱ�������
									Task4_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task4_CountTime<Task4_OffTime){
									Task4_CountTime++;
									Task4_Output = 0;
								}else{
									Task4_CountTime = 1;  //��λʱ�������
									Task4_OnState = 1; //�л���ON״̬
								}
							}	
							
				  }else{  //������ʱ���������������
								
								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ
						
						//��������Ĳ���ʱ�����䵫��û�г�ʱ
						if(Task4_OverTime_Count<Task4_OverTime){
							
							Task4_OverTime_Count=0;  //��λ��ʱ������
							Task4_CountTime = 1;  //��λʱ�������
							Task4_Output = 0;   //��ֹ����4���
							Task4_OnState = 1; //�л���ON״̬
							
							//��������������Ѿ���ʱ
						}else if(Task4_OverTime_Count==Task4_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ
							if(Task4_OverTime_Reset){
								
								Task4_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task4=0; //�ر�Task
								Task4_OverTime_Count=0;  //��λ��ʱ������
								Task4_CountTime = 1;  //��λʱ�������
								Task4_Output = 0;   //��ֹ����4���
								Task4_OnState = 1; //�л���ON״̬
							}
							
						}
	
					}
					break;
			}
		}else{  //������������������
			Task4_OverTime_Count=0;  //��λ��ʱ������
			Task4_CountTime = 1;  //��λʱ�������
			Task4_Output = 0;   //��ֹ����4���
			Task4_OnState = 1; //�л���ON״̬
		}
		
/******************************************************************************/
// ��������������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task4_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=1;}
	}	
}


void Task5_Output_Update(void)
{
		if(Task5 == 1)
		{
			switch(Task5_Mode)
			{
				case 1:
					if((Task5_StartTime<=NowTime)&&(NowTime<=Task5_EndTime)
						&&(Task5_OverTime_Count<Task5_OverTime)){
							Task5_OverTime_Count++;
						
							if(Task5_OnState==1) //�����������On״̬
								{
									
								if(Task5_CountTime<Task5_OnTime){
									Task5_CountTime++;
									Task5_Output = 1;
								}else{
									Task5_CountTime = 1;  //��λʱ�������
									Task5_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task5_CountTime<Task5_OffTime){
									Task5_CountTime++;
									Task5_Output = 0;
								}else{
									Task5_CountTime = 1;  //��λʱ�������
									Task5_OnState = 1; //�л���ON״̬
								}
							}	
							
			   }else{   //������ʱ���������������
								
								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ
					 
					 //��������岻��ʱ�����䵫��û�г�ʱ
						if(Task5_OverTime_Count<Task5_OverTime){
							
							Task5_OverTime_Count=0;  //��λ��ʱ������
							Task5_CountTime = 1;  //��λʱ�������
							Task5_Output = 0;   //��ֹ����5���
							Task5_OnState = 1; //�л���ON״̬
							
							//��������������Ѿ���ʱ
						}else if(Task5_OverTime_Count==Task5_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ
							if(Task5_OverTime_Reset){
								
								Task5_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task5=0; //�ر�Task
								Task5_OverTime_Count=0;  //��λ��ʱ������
								Task5_CountTime = 1;  //��λʱ�������
								Task5_Output = 0;   //��ֹ����5���
								Task5_OnState = 1; //�л���ON״̬
							}
							
						}
				 }
				 break;
		  }
		}else{   //������������������
			Task5_OverTime_Count=0;  //��λ��ʱ������
			Task5_CountTime = 1;  //��λʱ�������
			Task5_Output = 0;   //��ֹ����5���
			Task5_OnState = 1; //�л���ON״̬
		}
		
/******************************************************************************/
// ��������������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task5_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==5)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==5)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==5)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==5)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==5)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==5)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==5)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==5)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==5)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==5)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==5)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==5)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==5)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==5)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==5)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==5)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==5)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==5)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==5)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==5)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==5)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==5)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==5)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==5)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==5)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==5)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==5)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==5)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==5)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==5)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==5)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==5)){P37=1;}
	}		
}

void Task6_Output_Update(void)
{
		if(Task6 == 1)
		{
			switch(Task6_Mode)
			{
				case 1:
					if((Task6_StartTime<=NowTime)&&(NowTime<=Task6_EndTime)
						&&(Task5_OverTime_Count<Task5_OverTime)){
							Task5_OverTime_Count++;
						
							if(Task6_OnState==1) //�����������On״̬
								{
									
								if(Task6_CountTime<Task6_OnTime){
									Task6_CountTime++;
									Task6_Output = 1;
								}else{
									Task6_CountTime = 1;  //��λʱ�������
									Task6_OnState = 0; //�л���OFF״̬
								}
								
							}else{  //������Off״̬
								
								if(Task6_CountTime<Task6_OffTime){
									Task6_CountTime++;
									Task6_Output = 0;
								}else{
									Task6_CountTime = 1;  //��λʱ�������
									Task6_OnState = 1; //�л���ON״̬
								}
							}	
							
			   }else{    //������ʱ���������������
								
								  //��ʱ�����䵫������ʱ 
						      //����ʱ�����䣬����δ��ʱ
									//����ʱ�����䣬�����Ѿ���ʱ
					 
					 //�������������ʱ�����䵫��û�г�ʱ
						if(Task6_OverTime_Count<Task6_OverTime){
							
							Task6_OverTime_Count=0;  //��λ��ʱ������
							Task6_CountTime = 1;  //��λʱ�������
							Task6_Output = 0;   //��ֹ����6���
							Task6_OnState = 1; //�л���ON״̬
							
							//��������������Ѿ���ʱ
						}else if(Task6_OverTime_Count==Task6_OverTime){
							
							//ʹ�ܳ�ʱ�����Զ���λ
							if(Task6_OverTime_Reset){
								
								Task6_OverTime_Count=0;  //��λ��ʱ������
																				 //�������ʱ�������ڽ���������
																				 //�������ʱ�������ڽ��ȴ���������
							}else{  
								
								Task6=0; //�ر�Task
								Task6_OverTime_Count=0;  //��λ��ʱ������
								Task6_CountTime = 1;  //��λʱ�������
								Task6_Output = 0;   //��ֹ����6���
								Task6_OnState = 1; //�л���ON״̬
							}
							
						}
				 }
				 break;
		  }
		}else{    //������������������
			Task6_OverTime_Count=0;  //��λ��ʱ������
			Task6_CountTime = 1;  //��λʱ�������
			Task6_Output = 0;   //��ֹ����6���
			Task6_OnState = 1; //�л���ON״̬
		}
		
/******************************************************************************/
// ��������������֣��Դ�ע�����£�
/******************************************************************************/
	if(Task6_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==6)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==6)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==6)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==6)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==6)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==6)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==6)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==6)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==6)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==6)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==6)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==6)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==6)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==6)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==6)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==6)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==6)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==6)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==6)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==6)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==6)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==6)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==6)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==6)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==6)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==6)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==6)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==6)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==6)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==6)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==6)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==6)){P37=1;}
	}		
}

/******************************************************************************/
// �������ƣ�Task_Output_Update
// �����������
// ����������� 
// �������ܣ��������������ɨ�裬���ڴ����̵�������
/******************************************************************************/
/*
void Task1_Output_Update(void)
{
	if(Task1_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==1)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==1)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==1)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==1)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==1)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==1)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==1)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==1)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==1)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==1)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==1)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==1)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==1)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==1)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==1)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==1)){P37=1;}
	}
	
	
}

*/

/*
void Task2_Output_Update(void)
{
	if(Task2_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==2)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==2)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==2)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==2)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==2)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==2)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==2)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==2)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==2)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==2)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==2)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==2)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==2)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==2)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==2)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==2)){P37=1;}
	}

}	

*/

/*
void Task3_Output_Update(void)
{
	if(Task3_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==3)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==3)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==3)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==3)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==3)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==3)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==3)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==3)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==3)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==3)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==3)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==3)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==3)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==3)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==3)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==3)){P37=1;}
	}

}

*/

/*
void Task4_Output_Update(void)
{
	if(Task4_Output==1){
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=0;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=0;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=0;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=0;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=0;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=0;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=0;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=0;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=0;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=0;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=0;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=0;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=0;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=0;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=0;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=0;}
		
	}else{
		
		if((Pin10_Mode==1)&&(Pin10_Task_Number==4)){P10=1;}
		if((Pin11_Mode==1)&&(Pin11_Task_Number==4)){P11=1;}
		if((Pin12_Mode==1)&&(Pin12_Task_Number==4)){P12=1;}
		if((Pin13_Mode==1)&&(Pin13_Task_Number==4)){P13=1;}
		if((Pin14_Mode==1)&&(Pin14_Task_Number==4)){P14=1;}
		if((Pin15_Mode==1)&&(Pin15_Task_Number==4)){P15=1;}
		if((Pin16_Mode==1)&&(Pin16_Task_Number==4)){P16=1;}
		if((Pin17_Mode==1)&&(Pin17_Task_Number==4)){P17=1;}
		
		if((Pin20_Mode==1)&&(Pin20_Task_Number==4)){P20=1;}
		if((Pin21_Mode==1)&&(Pin21_Task_Number==4)){P21=1;}
		if((Pin22_Mode==1)&&(Pin22_Task_Number==4)){P22=1;}
		if((Pin23_Mode==1)&&(Pin23_Task_Number==4)){P23=1;}
		if((Pin24_Mode==1)&&(Pin24_Task_Number==4)){P24=1;}
		
		if((Pin35_Mode==1)&&(Pin35_Task_Number==4)){P35=1;}
		if((Pin36_Mode==1)&&(Pin36_Task_Number==4)){P36=1;}
		if((Pin37_Mode==1)&&(Pin37_Task_Number==4)){P37=1;}
	}

}
*/






