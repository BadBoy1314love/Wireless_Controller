
typedef struct
{
	u8 Index;  //当前菜单索引号
	u8 Left_Index;  //旋转编码器逆时针旋转转向的索引号
	u8 Right_Index;  //旋转编码器顺时针旋转转向的索引号
	u8 Enter_Index;  //编码器按键按下转向的下一级索引号
	void (*current_operation)(); //指向当前菜单索引号下的具体操作函数
} Menu_table;  

void LCD1602_Menu_Update();

void LCD1602_Show_Current_Page(); //1602显示当前页面

/******************************************************************************/
// LCD1602菜单操作函数
/******************************************************************************/
/*第一级菜单*/
void TASKS_CTRL_1_0();
void TASKS_SET_1_1();
void PORT_SET_1_2();
void TIME_SET_1_3();
void WIFI_SET_1_4();
void RETURN_1_5();
//第一级菜单补充
void SYSTEM_RESET_1_51();

/*第二级菜单*/
//TASKS_CTRL_1_0下项目
void TASK1_CTRL_2_6();
void TASK2_CTRL_2_7();
void TASK3_CTRL_2_8();
void TASK4_CTRL_2_9();
void TASK5_CTRL_2_10();
void TASK6_CTRL_2_11();
void RETURN_2_12();

/*第二级菜单*/
//TASKS_SET_1_1下项目
void TASK1_SET_2_13();
void TASK2_SET_2_14();
void TASK3_SET_2_15();
void TASK4_SET_2_16();
void TASK5_SET_2_17();
void TASK6_SET_2_18();
void RETURN_2_19();

/*第二级菜单*/
//PORT_SET_1_2下项目
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

/*第二级菜单*/
//TIME_SET_1_3下项目
void TIME_SET_Manual_Set_2_37();
void TIME_SET_Auto_Set_2_38();
void RETURN_2_39();

/*第二级菜单*/
//WIFI_SET_1_4下项目
void TCP_PORT_SET_2_40();
void STA_IP_2_41();
void AP_IP_2_42();
void RETURN_2_43();

/*第三级菜单*/
//TASK_SET下项目（TASK1-TASK1复用）
void TASK_StartTime_SET_3_44();
void TASK_EndTime_SET_3_45();
void TASK_OverTime_SET_3_46();
void TASK_OverTime_MODE_SET_3_47();
void TASK_OnTime_SET_3_48();
void TASK_OffTime_SET_3_49();
void RETURN_3_50();

