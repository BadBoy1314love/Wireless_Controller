/*------------------------------------------------------------------*-
  
   hSCH51.h (v1.00)

-*------------------------------------------------------------------*/

#ifndef _hSCH51_H
#define _hSCH51_H


// ------ ���������������� ----------------------------

//������ܣ��洢��DATA�����Ա���ٷ���
//ÿ����������ڴ�Ϊ8�ֽ�
typedef idata struct 
   {
		 
   void (code * pTask)(void);   //ָ�������ָ�루�����ǡ�void��void����������

   tWord Delay;     //�ӳ٣��δ�����ֱ����������һ��������

   tWord Period;    //ÿ�����еļ��   

   tByte RunMe;     //�����񼴽�ִ��ʱ����(�ɵ��ȳ���)  

   tByte Co_op;     //����ʽ�������ã�1������ռʽ�������ã�0��
		 
   } sTaskH; 

// ------ ��������ԭ�� -------------------------------

//���ĵ���������

void hSCH_Init_T0(void);
void hSCH_Start(void);
void hSCH_Update(void);
void  hSCH_Dispatch_Tasks(void);
tByte hSCH_Add_Task(void (code *)(void), tWord, tWord, bit);  
bit   hSCH_Delete_Task(tByte);
void hSCH_Run(void);
void hSCH_Pause(void);

// ------ �������� -----------------------------------------


#define hSCH_MAX_TASKS   (11)   //һ����������������
															 //�ڳ���ִ���ڼ�
															 //�������ÿ������Ŀ���е���
 
#endif
                              

