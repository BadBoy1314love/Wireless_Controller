
/******************************************************************************/
// 串口通信函数声明
/******************************************************************************/
void UartInit(void);	               //串口初始化
void Uart_Send_Char(uint8 uartData);   //串口发送一个字符
void Uart_Send_String(uint8 *str);	   //串口发送字符串