/******************************************************************************/
// ����ͷ�ļ�
/******************************************************************************/
#include "config.h"
#include "LCD1602_Clock.h"
#include "LCD1602.h"

/******************************************************************************/
// ������ʼ��
/******************************************************************************/
uint8 hour_ten_pos=0;   //Сʱʮλ(���ڳ䵱LCD1602����������ʾ�������б仯��)
uint8 hour_bit_pos=4;   //Сʱ��λ(���ڳ䵱LCD1602����������ʾ�������б仯��)
uint8 minute_ten_pos=9;   //����ʮλ(���ڳ䵱LCD1602����������ʾ�������б仯��)
uint8 minute_bit_pos=13;  //���Ӹ�λ(���ڳ䵱LCD1602����������ʾ�������б仯��)

/*ʱ��洢����*/
s8 hour=0,minute=0,second=0;

/*��ǰʱ��ת���ɷ��ӵı���*/
u16 NowTime = 0;

/*�ж�ʱ����桰�㡱���µı���*/
bit point=0;

//ʱ�䲹������λ
bit isFixTime = 1;

u8 xdata Max_Month_Days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

extern u8 xdata DateTable[13];
extern u8 xdata TimeTable[12];

extern s16 Year;
extern s8 Month;
extern s8 Day;

/******************************************************************************/
// �ַ������
/******************************************************************************/
uint8 code lcd1602Table0[8]={0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00}; //0����__��
uint8 code lcd1602Table1[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F}; //1����__��
uint8 code lcd1602Table2[8]={0x1F,0x1F,0x00,0x00,0x00,0x00,0x1F,0x1F}; //2����__����
uint8 code lcd1602Table3[8]={0x1F,0x1F,0x00,0x1F,0x1F,0x00,0x1F,0x1F}; //3����__������
uint8 code lcd1602Table4[8]={0x00,0x00,0x07,0x07,0x07,0x07,0x00,0x00}; //4����__�����
uint8 code lcd1602Table5[8]={0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x00,0x00}; //5����__�����
uint8 code lcd1602Table6[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //6����__д��

/******************************************************************************/
// LCD1602����������ʾ����
// �������ƣ�Lcd1602_Number
// ���������column_change-�б仯��(����ȷ����ʾλ��)��number-��Ҫ��ʾ������
// ����������� 
// �������ܣ�LCD1602��ָ��λ����ʾ��������
/******************************************************************************/
void LCD1602_Number(uint8 column_change,uint8 number)
{
	switch(number){
		case 0:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
		  break;
		case 1:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+3,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+1,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+2,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+3,1,lcd1602Table1);
			break;
		case 2:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,2,lcd1602Table2);
			break;
		case 3:
			Lcd1602_Custom_Char(1,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 4:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,6,lcd1602Table6);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(2,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 5:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+1,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 6:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,1,lcd1602Table1);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 7:
			Lcd1602_Custom_Char(1,column_change+1,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+2,6,lcd1602Table6);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 8:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
			break;
		case 9:
			Lcd1602_Custom_Char(1,column_change+1,3,lcd1602Table3);
	    Lcd1602_Custom_Char(1,column_change+2,0,lcd1602Table0);
	    Lcd1602_Custom_Char(1,column_change+3,3,lcd1602Table3);
	    Lcd1602_Custom_Char(2,column_change+1,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+2,2,lcd1602Table2);
	    Lcd1602_Custom_Char(2,column_change+3,3,lcd1602Table3);
		  break;
	}
}

/******************************************************************************/
// LCD1602��������ʱ��ʱ����º���
// �������ƣ�Lcd1602_Time_Update
// �����������
// ����������� 
// �������ܣ�LCD1602��������ʱ��ʱ�����
/******************************************************************************/
void LCD1602_Time_Update()
{

	//�ж��Ƿ�Ϊ���꣬���򽫶����޸�Ϊ29�죬������Ϊ28��
	if(Year%400==0||(Year%4==0&&Year%100!=0))
	{
		Max_Month_Days[2]=29;  //����
	}else{
		Max_Month_Days[2]=28;  //ƽ��
	}
	
	/*
	//ʱ�䲹����ÿ����Сʱ(������Сʱ������)
	if((isFixTime==1)&&(hour%2!=0)&&(minute==59)&&(second==59))
	{
		second--;
		isFixTime = 0; //�ر�ʱ�䲹��
	}
	*/
	
	//ʱ�䲹��
	if((isFixTime==1)&&(hour%2!=0)&&(minute==59)&&(second==59))
	{
		second--;
		isFixTime = 0; //�ر�ʱ�䲹��
	}
	//ʱ�䲹��
	else if((isFixTime==1)&&(hour%2==0)&&(minute==59)&&(second==59))
	{
		second--;
		second--;
		isFixTime = 0; //�ر�ʱ�䲹��
	}
	
	point=~point;
	second++;
	if(second==60){
		isFixTime = 1; //����ʱ�䲹��
		second=0;
		minute++;
		if(minute==60){
			minute=0;
			hour++;
			if(hour==24){
				hour=0;
				Day++;
				if(Day>Max_Month_Days[Month]){
					Day=1;
					Month++;
					if(Month==13){
						Month=1;
						Year++;
					}
				}
			}
		}
	}
	
	NowTime = hour*60+minute;  //��ǰʱ���ת��ֵ��λΪ���ӣ�0-1439�� 
	
	//��������ʱ������
	//����ʱ������д��ʱ����Ϣ
	//����ʱ������һ��19λΪ��2022/06/14 19:03:24
	
//	������������
	DateTable[0]=Year/1000%10+'0';
	DateTable[1]=Year/100%10+'0';
	DateTable[2]=Year/10%10+'0';
	DateTable[3]=Year%10+'0';
	
	DateTable[5]=Month/10%10+'0';
	DateTable[6]=Month%10+'0';
	
	DateTable[8]=Day/10%10+'0';
	DateTable[9]=Day/1%10+'0';
	
  //	����ʱ������
	TimeTable[0]=hour/10%10+'0';
	TimeTable[1]=hour/1%10+'0';

	TimeTable[3]=minute/10%10+'0';
	TimeTable[4]=minute/1%10+'0';
	
	TimeTable[6]=second/10%10+'0';			
	TimeTable[7]=second/1%10+'0';

	
}


/******************************************************************************/
// LCD1602��������ʱ�ӣ�����+�㣩��ʾ����
// �������ƣ�Lcd1602_Clock_Update
// �����������
// ����������� 
// �������ܣ�LCD1602ˢ�µ�������ʱ��
/******************************************************************************/
void LCD1602_Clock_Update()
{
	LCD1602_Number(minute_ten_pos,minute/10);
	LCD1602_Number(minute_bit_pos,minute%10);
	LCD1602_Number(hour_ten_pos,hour/10);
	LCD1602_Number(hour_bit_pos,hour%10);
	
	Lcd1602_Custom_Char(1,4,6,lcd1602Table6);
	Lcd1602_Custom_Char(1,13,6,lcd1602Table6);
	Lcd1602_Custom_Char(2,4,6,lcd1602Table6);
	Lcd1602_Custom_Char(2,13,6,lcd1602Table6);
	
	if(point){
		Lcd1602_Custom_Char(1,8,4,lcd1602Table4);
	  Lcd1602_Custom_Char(2,9,5,lcd1602Table5);
	  Lcd1602_Custom_Char(1,9,6,lcd1602Table6);
	  Lcd1602_Custom_Char(2,8,6,lcd1602Table6);
	}else{
		Lcd1602_Custom_Char(1,8,6,lcd1602Table6);
		Lcd1602_Custom_Char(2,9,6,lcd1602Table6);
		Lcd1602_Custom_Char(1,9,5,lcd1602Table5);
		Lcd1602_Custom_Char(2,8,4,lcd1602Table4);
	}
}

/******************************************************************************/
// LCD1602����/ʱ����ʾ����
// �������ƣ�LCD1602_DateTime_Update
// �����������
// ����������� 
// �������ܣ�LCD1602��ʾ���ں�ʱ��
/******************************************************************************/
void LCD1602_DateTime_Update(void)
{	
	Lcd1602_Show_String(1,1,"   ");
	Lcd1602_Show_String(2,1,"    ");
	Lcd1602_Show_String(1,14,"   ");
	Lcd1602_Show_String(2,13,"    ");
	Lcd1602_Show_String(1,4,DateTable);
	Lcd1602_Show_String(2,5,TimeTable);
}
