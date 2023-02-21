
/******************************************************************************/
// 字符构造表声明
/******************************************************************************/
extern uint8 code lcd1602Table0[8]; //0点阵__上
extern uint8 code lcd1602Table1[8]; //1点阵__下
extern uint8 code lcd1602Table2[8]; //2点阵__上下
extern uint8 code lcd1602Table3[8]; //3点阵__上中下
extern uint8 code lcd1602Table4[8]; //4点阵__点点左
extern uint8 code lcd1602Table5[8]; //5点阵__点点右
extern uint8 code lcd1602Table6[8]; //6点阵__写空

/******************************************************************************/
// LCD1602_Clock函数声明
/******************************************************************************/
void LCD1602_Number(uint8 column_change,uint8 number);
void LCD1602_Clock_Update();
void LCD1602_Time_Update();
void LCD1602_DateTime_Update();
