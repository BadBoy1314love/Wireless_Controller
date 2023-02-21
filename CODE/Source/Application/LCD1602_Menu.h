
typedef struct
{
	u8 Index;  //��ǰ�˵�������
	u8 Left_Index;  //��ת��������ʱ����תת���������
	u8 Right_Index;  //��ת������˳ʱ����תת���������
	u8 Enter_Index;  //��������������ת�����һ��������
	void (*current_operation)(); //ָ��ǰ�˵��������µľ����������
} Menu_table;  

void LCD1602_Menu_Update();

void LCD1602_Show_Current_Page(); //1602��ʾ��ǰҳ��

/******************************************************************************/
// LCD1602�˵���������
/******************************************************************************/
/*��һ���˵�*/
void TASKS_CTRL_1_0();
void TASKS_SET_1_1();
void PORT_SET_1_2();
void TIME_SET_1_3();
void WIFI_SET_1_4();
void RETURN_1_5();
//��һ���˵�����
void SYSTEM_RESET_1_51();

/*�ڶ����˵�*/
//TASKS_CTRL_1_0����Ŀ
void TASK1_CTRL_2_6();
void TASK2_CTRL_2_7();
void TASK3_CTRL_2_8();
void TASK4_CTRL_2_9();
void TASK5_CTRL_2_10();
void TASK6_CTRL_2_11();
void RETURN_2_12();

/*�ڶ����˵�*/
//TASKS_SET_1_1����Ŀ
void TASK1_SET_2_13();
void TASK2_SET_2_14();
void TASK3_SET_2_15();
void TASK4_SET_2_16();
void TASK5_SET_2_17();
void TASK6_SET_2_18();
void RETURN_2_19();

/*�ڶ����˵�*/
//PORT_SET_1_2����Ŀ
void PIN10_SET_2_20();
void PIN11_SET_2_21();
void PIN12_SET_2_22();
void PIN13_SET_2_23();
void PIN14_SET_2_24();
void PIN15_SET_2_25();
void PIN16_SET_2_26();
void PIN17_SET_2_27();

void PIN20_SET_2_28();
void PIN21_SET_2_29();
void PIN22_SET_2_30();
void PIN23_SET_2_31();
void PIN24_SET_2_32();

void PIN35_SET_2_33();
void PIN36_SET_2_34();
void PIN37_SET_2_35();
void RETURN_2_36();

/*�ڶ����˵�*/
//TIME_SET_1_3����Ŀ
void TIME_SET_Manual_Set_2_37();
void TIME_SET_Auto_Set_2_38();
void RETURN_2_39();

/*�ڶ����˵�*/
//WIFI_SET_1_4����Ŀ
void TCP_PORT_SET_2_40();
void STA_IP_2_41();
void AP_IP_2_42();
void RETURN_2_43();

/*�������˵�*/
//TASK_SET����Ŀ��TASK1-TASK1���ã�
void TASK_StartTime_SET_3_44();
void TASK_EndTime_SET_3_45();
void TASK_OverTime_SET_3_46();
void TASK_OverTime_MODE_SET_3_47();
void TASK_OnTime_SET_3_48();
void TASK_OffTime_SET_3_49();
void RETURN_3_50();

