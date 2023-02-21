/******************************************************************************/
// ����ͷ�ļ�
/******************************************************************************/
#include "Config.h"
#include "Delay.h"

/******************************************************************************/
// �������ƣ�Delay5ms 
// �����������
// ����������� 
// �������ܣ�5ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 54;
	j = 198;
	do
	{
		while (--j);
	} while (--i);
}
/******************************************************************************/
// �������ƣ�Delay15ms 
// �����������
// ����������� 
// �������ܣ�15ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
void Delay15ms()	
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 162;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}

/******************************************************************************/
// �������ƣ�Delay50ms 
// �����������
// ����������� 
// �������ܣ�50ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
void Delay50ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 3;
	j = 26;
	k = 223;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/******************************************************************************/
// �������ƣ�Delay100ms 
// �����������
// ����������� 
// �������ܣ�100ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/******************************************************************************/
// �������ƣ�Delay200ms 
// �����������
// ����������� 
// �������ܣ�200ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
/*
void Delay200ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
*/

/******************************************************************************/
// �������ƣ�Delay400ms 
// �����������
// ����������� 
// �������ܣ�400ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
/*
void Delay400ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
*/
/******************************************************************************/
// �������ƣ�Delay1000ms 
// �����������
// ����������� 
// �������ܣ�1000ms
// ����Ƶ�ʣ�11.0592M
/******************************************************************************/
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
