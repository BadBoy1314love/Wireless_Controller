/******************************************************************************/
// lcd1602函数声明
/******************************************************************************/
void Lcd1602_Init(void);
void Lcd1602_Busy_Check(void);
void Lcd1602_Write_Cmd(uint8 cmd);
void Lcd1602_Write_Data(uint8 Data);
void Lcd1602_Show_String(uint8 row, uint8 col,uint8 *str);
void Lcd1602_Custom_Char(uint8 row, uint8 col, uint8 pos, uint8 *customValueTable);
