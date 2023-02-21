/******************************************************************************/
// 包含头文件
/******************************************************************************/
#include "Config.h"
#include "ESP8266.h"
#include "UART.h"
#include "LCD1602.h"
#include "Delay.h"
#include "EEPROM_Application.h"

/*单片机软件复位下载*/
uint8 xdata UART_0x7F_Count=0;  //串口0x7F计数变量

/*STA模式与AP模式的设置信息*/
u8 xdata STA_MODE_Table[150]={"AT+CWJAP_CUR=\"TP-LINK_847A\",\"asdfghjkl\"\r\n             "};
u8 xdata AP_MODE_Table[150]={"AT+CWSAP_CUR=\"Wireless_Controller\",\"asdfghjkl\",3,4\r\n        "};

/*设置TCP服务器信息*/
u8 xdata ATCIPSERVER[22]="AT+CIPSERVER=1,00001\r\n";

s32 xdata TcpServerPort = 1;

u8 xdata RESET_COUNTER = 0;
u8 xdata STA_MODE_COUNTER = 0;
u8 xdata URL_COUNTER = 0;

/*从网页获取的日期和时间数据*/
u8 xdata DateTable[]={"2022/01/01"};
u8 xdata TimeTable[]={"00:00:00"};

/*时间存储变量*/
extern s8 hour,minute,second;
s16 Year=2022;
s8 Month=1;
s8 Day=1;

//从网页获取时间数据超时计数器
u8 xdata GET_TIME_COUNTER = 0;  //GET_TIME计数器

//IP数据接收数组
u8 xdata STAIPTable[16]="                "; 
u8 xdata APIPTable[16]="                "; 

/*串口数据接收数组*/
uint8 xdata rcvTable[200];

//判断8266的返回信息的标志位(判断命令执行是否完成)
uint8 xdata ESP8266_Return_Value = 0;

//任务控制
extern bit Task1;
extern bit Task2;
extern bit Task3;
extern bit Task4;
extern bit Task5;
extern bit Task6;

extern u8 code STA_IP_ADDRESS[];
extern u8 code AP_IP_ADDRESS[];

extern u8 code TCP_SERVER_PORT[];  // ="TCP SERVER PORT:";
extern u8 xdata TCP_PORT_Number[]; //  ="-->  65535   <--";

/******************************************************************************/
// 函数名称：Esp8266_Send_String 
// 输入参数：str-发送的命令
// 输出参数：无 
// 函数功能：向ESP8266模块发送命令
/******************************************************************************/
void Esp8266_Send_String(uint8 *str){
	Uart_Send_String(str);
	Uart_Send_String("\r\n");
}


/******************************************************************************/
// 函数名称：Esp8266_Sta_Mode 
// 输入参数：无
// 输出参数：无 
// 函数功能：ESP8266模块设置为STA模式
// 注意：忙信号检查
// 每发送一条命令一定要等待ESP8266完成操作后，再发送下一条命令
/******************************************************************************/
void Esp8266_STA_AP_Mode(void){

	/*第一页的显示内容*/
	Lcd1602_Show_String(1,1,"WIFI_RST        ");
	Lcd1602_Show_String(2,1,"WIFT_MODE=     ");
	
	/*AT+RST指令的进行*/
	ESP8266_Return_Value=0;   //复位返回标志位
	while((ESP8266_Return_Value!=0x02)&&(P32==1))
	{
		//20次复位不成功后结束8266初始化
		if(++RESET_COUNTER==20){RESET_COUNTER=0; goto END;}
		Esp8266_Send_String("AT+RST");//返回ready
		Lcd1602_Show_String(1,1,"WIFI_RST        ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST>       ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST->      ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST-->     ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST--->    ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST---->   ");Delay100ms();
		Lcd1602_Show_String(1,1,"WIFI_RST----->  ");Delay100ms();
	}
	if(P32==1){
		RESET_COUNTER=0;
		Lcd1602_Show_String(1,1,"WIFI_RST----->OK");
	}else{
		RESET_COUNTER=0;
		Lcd1602_Show_String(1,1,"WIFI_RST--->FAIL");
		Delay1000ms();
		while(!P32);   //按键未释放则停止在此处
		goto END;
	}
	
	
	/*AT+CWMODE_CUR=3指令的执行*/
	ESP8266_Return_Value=0;  //复位返回标志位
	while(ESP8266_Return_Value!=0x01)
	{
		Esp8266_Send_String("AT+CWMODE_CUR=3");//返回OK
		Lcd1602_Show_String(2,1,"WIFT_MODE=     ");Delay50ms();
		Lcd1602_Show_String(2,1,"WIFT_MODE=>    ");Delay50ms();
		Lcd1602_Show_String(2,1,"WIFT_MODE=->   ");Delay50ms();
		Lcd1602_Show_String(2,1,"WIFT_MODE=-->  ");Delay50ms();
		Lcd1602_Show_String(2,1,"WIFT_MODE=---> ");Delay50ms();
		Lcd1602_Show_String(2,1,"WIFT_MODE=---->");Delay50ms();
	}
	Lcd1602_Show_String(2,1,"WIFT_MODE=STA+AP");Delay1000ms();

	/*第二页的显示内容*/
	Lcd1602_Show_String(1,1,"STA_MODE        ");
	Lcd1602_Show_String(2,1,"AT+CIPMUX       ");
	
	/*STA模式连接WIFI指令*/
	ESP8266_Return_Value = 0;  //复位返回标志位
	while(ESP8266_Return_Value!=0x01&&P32==1)
	{
		if(++STA_MODE_COUNTER==20){STA_MODE_COUNTER=0; goto STA_MODE_FAIL;}
		Esp8266_Send_String(STA_MODE_Table);//返回OK	
		Lcd1602_Show_String(1,1,"STA_MODE        ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE>       ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE->      ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE-->     ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE--->    ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE---->   ");Delay50ms();
		Lcd1602_Show_String(1,1,"STA_MODE----->  ");Delay50ms();
	}
	if(P32==1){
		STA_MODE_COUNTER=0;
		Lcd1602_Show_String(1,1,"STA_MODE----->OK");
	}else{
		STA_MODE_FAIL:
		Lcd1602_Show_String(1,1,"STA_MODE--->FAIL");
	}
	
	
	/*设置单路连接*/
	ESP8266_Return_Value = 0;    //复位返回标志位
	while(ESP8266_Return_Value!=0x01)
	{
		Esp8266_Send_String("AT+CIPMUX=0");
		Lcd1602_Show_String(2,1,"AT+CIPMUX       ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX>      ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX->     ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX-->    ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX--->   ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX---->  ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPMUX-----> ");Delay50ms();
	}
	Lcd1602_Show_String(2,1,"AT+CIPMUX----->0");Delay1000ms();
	

	/*第三页的显示内容*/
	GET_TIME:
	if(++GET_TIME_COUNTER==20){GET_TIME_COUNTER=0; goto GET_TIME_FAIL;}
	Lcd1602_Show_String(1,1,"LINK_URL        ");
	Lcd1602_Show_String(2,1,"AT+CIPSEND      ");

	/*设置TCP连接*/
	ESP8266_Return_Value = 0;
	while((ESP8266_Return_Value!=0x01) && (P32 == 1))
	{
		if(++URL_COUNTER==20){URL_COUNTER=0; goto GET_TIME_FAIL;}
		Esp8266_Send_String("AT+CIPSTART=\"TCP\",\"www.shijian.cc\",80");
		Lcd1602_Show_String(1,1,"LINK_URL        ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL>       ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL->      ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL-->     ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL--->    ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL---->   ");Delay50ms();
		Lcd1602_Show_String(1,1,"LINK_URL----->  ");Delay50ms();
	}
	
	if(P32==1){
		Lcd1602_Show_String(1,1,"LINK_URL----->OK");
	}else{
		Lcd1602_Show_String(1,1,"LINK_URL--->FAIL");
	}
	
	while(!P32);   //按键未释放则停止在此处
	
	/*发送数据指令*/
	ESP8266_Return_Value = 0;
	while((ESP8266_Return_Value!=0x01) && (P32 == 1))
	{
		Esp8266_Send_String("AT+CIPSEND=42");
		Lcd1602_Show_String(2,1,"AT+CIPSEND      ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPSEND>     ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPSEND->    ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPSEND-->   ");Delay50ms();
		Lcd1602_Show_String(2,1,"AT+CIPSEND--->  ");Delay50ms();
	}
	if(P32==1){
		Lcd1602_Show_String(2,1,"AT+CIPSEND--->OK");
	}else{
		Lcd1602_Show_String(2,1,"AT+CIPSEND->FAIL");
	}
	Delay1000ms();
	while(!P32);   //按键未释放则停止在此处
	
	
	/*第四页的显示内容*/
	Lcd1602_Show_String(1,1,"SEND_DATA       ");
	Lcd1602_Show_String(2,1,"GET_TIME        ");
	
	/*发送数据内容*/
	ESP8266_Return_Value = 0;
	Esp8266_Send_String("GET http://www.shijian.cc/000/clock.asp\r\n\r\n");
	while((ESP8266_Return_Value!=0x01) && (P32 == 1))   //接收到SEND OK
	{
		if(++GET_TIME_COUNTER==5){GET_TIME_COUNTER=0; goto GET_TIME;}
		Lcd1602_Show_String(1,1,"SEND_DATA       ");Delay50ms();
		Lcd1602_Show_String(1,1,"SEND_DATA>      ");Delay50ms();
		Lcd1602_Show_String(1,1,"SEND_DATA->     ");Delay50ms();
		Lcd1602_Show_String(1,1,"SEND_DATA-->    ");Delay50ms();
		Lcd1602_Show_String(1,1,"SEND_DATA--->   ");Delay50ms();
		Lcd1602_Show_String(1,1,"SEND_DATA---->  ");Delay50ms();
	}
	if(P32==1){
		Lcd1602_Show_String(1,1,"SEND_DATA---->OK");
	}else{
		Lcd1602_Show_String(1,1,"SEND_DATA-->FAIL");
	}
	
	while(!P32);   //按键未释放则停止在此处
	
	
	
	while((ESP8266_Return_Value!=0x01) && (P32 == 1))
	{
		if(++GET_TIME_COUNTER==5){GET_TIME_COUNTER=0; goto GET_TIME;}
		Lcd1602_Show_String(2,1,"GET_TIME        ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME>       ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME->      ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME-->     ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME--->    ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME---->   ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_TIME----->  ");Delay50ms();
	}
	if(P32==1){
		GET_TIME_COUNTER=0;
		Lcd1602_Show_String(2,1,"GET_TIME----->OK");
	}else{
		GET_TIME_FAIL:
		Lcd1602_Show_String(2,1,"GET_TIME--->FAIL");
	}
	while(!P32);   //按键未释放则停止在此处
	Delay1000ms();
	
	
	/*第五页的显示内容*/
	Lcd1602_Write_Cmd(0x01);//显示清屏	
	Lcd1602_Show_String(1,4,DateTable);
	Lcd1602_Show_String(2,5,TimeTable);
	Delay1000ms();
	
	/*第六页的显示内容*/
	Lcd1602_Show_String(1,1,"AT+CIPMUX       ");
	Lcd1602_Show_String(2,1,"SET_PORT        ");
	
	/*设置多路连接*/
	ESP8266_Return_Value = 0;    //复位返回标志位
	while(ESP8266_Return_Value!=0x01)
	{
		Esp8266_Send_String("AT+CIPMUX=1");
		Lcd1602_Show_String(1,1,"AT+CIPMUX       ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX>      ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX->     ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX-->    ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX--->   ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX---->  ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT+CIPMUX-----> ");Delay50ms();
	}
	Lcd1602_Show_String(1,1,"AT+CIPMUX----->1");
	
	/*设置多路连接端口*/
	ESP8266_Return_Value = 0;
	while((ESP8266_Return_Value!=0x01)&& (P32 == 1))
	{
		Esp8266_Send_String(ATCIPSERVER);//返回OK
		Lcd1602_Show_String(2,1,"SET_PORT        ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT>       ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT->      ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT-->     ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT--->    ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT---->   ");Delay50ms();
		Lcd1602_Show_String(2,1,"SET_PORT----->  ");Delay50ms();
	}
	if(P32==1){
		Lcd1602_Show_String(2,1,"SET_PORT----->OK");
	}else{
		Lcd1602_Show_String(2,1,"SET_PORT--->FAIL");
	}
	while(!P32);Delay1000ms();
	
	/*第七页显示内容*/
	Lcd1602_Show_String(1,1,"AT_MODE         ");
	Lcd1602_Show_String(2,1,"GET_IP          ");

	/*AP模式设置指令*/
	ESP8266_Return_Value = 0;  //复位返回标志位
	while(ESP8266_Return_Value!=0x01&& (P32 == 1))
	{
		Esp8266_Send_String(AP_MODE_Table);//返回OK	
		Lcd1602_Show_String(1,1,"AT_MODE         ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE>        ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE->       ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE-->      ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE--->     ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE---->    ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE----->   ");Delay50ms();
		Lcd1602_Show_String(1,1,"AT_MODE------>  ");Delay50ms();
	}
	if(P32==1){
		Lcd1602_Show_String(1,1,"AT_MODE------>OK");
	}else{
		Lcd1602_Show_String(1,1,"AT_MODE---->FAIL");
	}
	while(!P32);
	
	/*查询IP地址*/
	ESP8266_Return_Value = 0; 
	Esp8266_Send_String("AT+CIFSR");//查询路由器分配的IP地址.返回OK
	while(ESP8266_Return_Value!=0x01)
	{
		Lcd1602_Show_String(2,1,"GET_IP          ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP>         ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP->        ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP-->       ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP--->      ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP---->     ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP----->    ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP------>   ");Delay50ms();
		Lcd1602_Show_String(2,1,"GET_IP------->  ");Delay50ms();
	}
	Lcd1602_Show_String(2,1,"GET_IP------->OK");Delay1000ms();
	
	/*第八页显示内容*/
	ESP8266_Return_Value = 0;
	Lcd1602_Write_Cmd(0x01);//显示清屏
	Lcd1602_Show_String(1,1,AP_IP_ADDRESS);
	Lcd1602_Show_String(2,1,APIPTable);
	Delay1000ms();Delay1000ms();Delay1000ms();
	
	/*第九页显示内容*/
	ESP8266_Return_Value = 0;
	Lcd1602_Write_Cmd(0x01);//显示清屏
	Lcd1602_Show_String(1,1,STA_IP_ADDRESS);
	Lcd1602_Show_String(2,1,STAIPTable);
	Delay1000ms();Delay1000ms();Delay1000ms();
	
	END:;
	
}


/******************************************************************************/
// 函数名称：arryClear 
// 输入参数：dataArry
// 输出参数：无 
// 函数功能：数组元素清零
/******************************************************************************/
void arryClear(uint8 *dataArry){
	uint8 i;
	for(i=0;i<200;i++){
		*(dataArry+i)=' ';
	}
}


/******************************************************************************/
// 函数名称：Uart_Int 
// 输入参数：无
// 输出参数：无 
// 函数功能：串口中断服务程序
// 主要两个功能：
// 1. 忙信号判断 - 单片机发送指令后，根据ESP8266反馈的信息判断指令是否完成
// 2. 任务判断   - 单片机根据从ESP8266模块收到的信息，执行相应的动作
/******************************************************************************/
void Uart_Interrupt(void) interrupt INTERRUPT_UART_Rx_Tx {
	
	static u8 ip = 0;   //ip地址数组元素标号
	static uint8 i = 0;   //接收数组元素标号
	static u8 t = 0;    //TimeTable数组元素标号
	static u8 sta = 0;  //sta数组元素标号
	static u8 ap = 0;   //ap数组元素标号
	
	if(TI){   //如果发送中断引起
		
		TI = 0;  //发送中断请求标志位置0
	}
	
	else{    //否则接收中断引起
		
		RI = 0;  //接收中断请求标志位置0
		
		/*单片机软件自动下载*/
		if(SBUF==0x7f){   //STC下载指令0X7F 
			
			UART_0x7F_Count++;   //串口0x7F计数变量+1
			
			if(UART_0x7F_Count==10) //如果收到10次0X7F
			{
					UART_0x7F_Count=0;   //串口0x7F计数变量置0
					IAP_CONTR=0x60;//复位命令  
			}
		}else{
			UART_0x7F_Count=0;	//串口0x7F计数变量置0
		}
		
		rcvTable[i]=SBUF;  //每次接受中断都放入接受数组一字节数据
		if(i==200){i=0;}  //如果接受数组已满，则从头放起
		i++;  //数组元素号+1

		//接收到换行符意味着指令已经接收完整
		/*对忙信号的判断，判断模块的返回内容修改标志位*/
		if(rcvTable[i-1]=='\n'){  //如果在本次接收之前是一个换行符
															//接收到换行符意味着接收数组已经接收到当前行的末尾
															//如果判断的任务控制达到了末尾
			
			i = 0;  //接收数组指向了第0个元素,判断当前指令到达了结尾
			
			//如果接收到ok,返回OK标志位
			if((rcvTable[0]=='O')&&(rcvTable[1]=='K')){  
				ESP8266_Return_Value = 0x01;
			}
			
			//如果接收到SEND OK，返回SEND OK标志位
			else if((rcvTable[0]=='S')&&(rcvTable[1]=='E')&&(rcvTable[2]=='N')
				&&(rcvTable[3]=='D')&&(rcvTable[5]=='O')&&(rcvTable[6]=='K')){
					ESP8266_Return_Value = 0x03;
				}
			
			//否则如果接收到ready,返回ready标志位
			else if((rcvTable[0]=='r')&&(rcvTable[1]=='e')&&(rcvTable[4]=='y')){
				ESP8266_Return_Value = 0x02;			
			}
			
		//	AT+CIFSR      //8266模块接收到当前指令之后接收到换行符
		//	+CIFSR:APIP,"192.168.4.1"
		//	+CIFSR:APMAC,"36:94:54:64:c3:b7"
		//	+CIFSR:STAIP,"192.168.0.103"
		//	+CIFSR:STAMAC,"34:94:54:64:c3:b7"
			
			//否则如果接收到 +CIFSR:APIP,"192.168.4.1"
			else if((rcvTable[0]=='+')&&(rcvTable[9]=='I')&&(rcvTable[10]=='P')){
				
				/*获取IP地址写入到IP数组中,判断到 " 则退出不写入*/
				for(ip=0;ip<16;ip++){
					if(rcvTable[ip+13]=='"'){break;}
					APIPTable[ip]=rcvTable[ip+13];
				}
				
				ESP8266_Return_Value = 0x01;		
			}
			
			
			//否则如果接收到 +CIFSR:STAIP,"192.168.0.103"
			else if((rcvTable[0]=='+')&&(rcvTable[10]=='I')&&(rcvTable[11]=='P')){
				
				/*获取IP地址写入到IP数组中,判断到 " 则退出不写入*/
				for(ip=0;ip<16;ip++){
					if(rcvTable[ip+14]=='"'){break;}
					STAIPTable[ip]=rcvTable[ip+14];
				}
				
				ESP8266_Return_Value = 0x01;		
			}
			
			// +IPD,0,33:STA=AT+CWJAP_CUR="TP-LINK_847A","asdfghjkl"
			//STA_MODE_Table[150]={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\""};
      //AP_MODE_Table[150]={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4"};
			else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
						&&(rcvTable[3]=='D')&&(rcvTable[10]=='S')&&(rcvTable[11]=='T')
						&&(rcvTable[12]=='A')&&(rcvTable[13]=='=')){
							
							//清空STA信息
							for(sta=0;sta<150;sta++){
								STA_MODE_Table[sta] = ' ';
							}	
						
							//将获取到的STA数据写入STA数组
							for(sta=0;sta<150;sta++){
								if(rcvTable[sta-1]=='\n'){
									break;
								}
								STA_MODE_Table[sta] = rcvTable[sta+14];
							}
							
							EA = 0;
							EEPROM_Program_Sector_1();
							EA = 1;
										
							arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
							i = 0;   //接收数组指向了第0个元素
				}
				
			// +IPD,0,103:STA=AT+CWJAP_CUR="TP-LINK_847A","asdfghjkl"
			//STA_MODE_Table[150]={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\""};
      //AP_MODE_Table[150]={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4"};
			else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
						&&(rcvTable[3]=='D')&&(rcvTable[11]=='S')&&(rcvTable[12]=='T')
						&&(rcvTable[13]=='A')&&(rcvTable[14]=='=')){
							
							//清空STA信息
							for(sta=0;sta<150;sta++){
								STA_MODE_Table[sta] = ' ';
							}	
						
							//将获取到的STA数据写入STA数组
							for(sta=0;sta<150;sta++){
								if(rcvTable[sta-1]=='\n'){
									break;
								}
								STA_MODE_Table[sta] = rcvTable[sta+14];
							}
							
							EA = 0;
							EEPROM_Program_Sector_1();
							EA = 1;
										
							arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
							i = 0;   //接收数组指向了第0个元素
				}


			// +IPD,0,61:AP=AT+CWSAP_CUR="Wireless_Controller_Test","asdfghjkl",3,4
			//STA_MODE_Table[150]={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\""};
      //AP_MODE_Table[150]={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4"};
			 else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
						&&(rcvTable[3]=='D')&&(rcvTable[10]=='A')&&(rcvTable[11]=='P')
						&&(rcvTable[12]=='=')){
							
							//清空AP信息
							for(ap=0;ap<150;ap++){
								AP_MODE_Table[ap] = ' ';
							}	
							
							//将获取到的AP数据写入AP数组
							for(ap=0;ap<150;ap++){
								if(rcvTable[ap-1]=='\n'){
									break;
								}
								AP_MODE_Table[ap] = rcvTable[ap+13];
							}
							
							EA = 0;
							EEPROM_Program_Sector_1();
							EA = 1;
										
							arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
							i = 0;   //接收数组指向了第0个元素
				}

			// +IPD,0,101:AP=AT+CWSAP_CUR="Wireless_Controller_Test","asdfghjkl",3,4
			//STA_MODE_Table[150]={"AT+CWJAP_CUR=\"TP-LINK_888F\",\"asdfghjkl\""};
      //AP_MODE_Table[150]={"AT+CWSAP_CUR=\"Wireless_Controller_Test\",\"asdfghjkl\",3,4"};
			 else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
						&&(rcvTable[3]=='D')&&(rcvTable[11]=='A')&&(rcvTable[12]=='P')
						&&(rcvTable[13]=='=')){
							
							//清空AP信息
							for(ap=0;ap<150;ap++){
								AP_MODE_Table[ap] = ' ';
							}	
							
							//将获取到的AP数据写入AP数组
							for(ap=0;ap<150;ap++){
								if(rcvTable[ap-1]=='\n'){
									break;
								}
								AP_MODE_Table[ap] = rcvTable[ap+14];
							}
							
							EA = 0;
							EEPROM_Program_Sector_1();
							EA = 1;
										
							arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
							i = 0;   //接收数组指向了第0个元素
				}	

		}else{  //否则没有接收到末尾的换行符，则判断任务控制
			
			//接收到OK
			//返回OK返回值
			if((rcvTable[0]=='O')&&(rcvTable[1]=='K')){
				ESP8266_Return_Value = 0x01;		
				
				arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				i = 0;   //接收数组指向了第0个元素
			 }
			
			
			//接收到时间数据
			//+IPD,19:2022/06/14 19:03:24CLOSED
			if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[5]=='1')
			&&(rcvTable[6]=='9')&&(rcvTable[7]==':')&&(rcvTable[27]=='C')
			 &&(rcvTable[29]=='O')&&(rcvTable[32]=='D')){
				 
				 /*有用时间数据一共19位为：2022/06/14 19:03:24*/
				 //首先遍历接收数组，将时间数据取出
				 //同时将时间字符串转换成数字并存入变量
				
				 //接受日期时间数据之前复位日期时间
				Year=0;Month=0;Day=0;
				hour=0;minute=0;second=0;
			
				for(t=0;t<19;t++){
					
					if((t>=0)&&(t<=3)){
						Year=Year*10+(rcvTable[t+8]-'0');
						
					}else if((t>=5)&&(t<=6)){
						Month=Month*10+(rcvTable[t+8]-'0');
						
					}else if((t>=8)&&(t<=9)){
						Day=Day*10+(rcvTable[t+8]-'0');
						
					}else if((t>=11)&&(t<=12)){
						hour=hour*10+(rcvTable[t+8]-'0');
						
					}else if((t>=14)&&(t<=15)){
						minute=minute*10+(rcvTable[t+8]-'0');
						
					}else if((t>=17)&&(t<=18)){
						second=second*10+(rcvTable[t+8]-'0');
					}
					
					if((t>=0)&&(t<=9)){
						DateTable[t]=rcvTable[t+8];
					}else if((t>=11)&&(t<=18)){
						TimeTable[t-11]=rcvTable[t+8];
					}
					
				}
				ESP8266_Return_Value = 0x01;		
				
				arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				i = 0;   //接收数组指向了第0个元素

			 }
			 
		
			//+IPD,0,11,StartTask>1
			if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='1')){
				 
				 Task1 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
						
				 //+IPD,0,11,StartTask>2
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='2')){
				 
				 Task2 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
				 
			   //+IPD,0,11,StartTask>3
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='3')){
				 
				 Task3 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
				 
				 //+IPD,0,11,StartTask>4
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='4')){
				 
				 Task4 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
				 
				 //+IPD,0,11,StartTask>5
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='5')){
				 
				 Task5 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
				 
				 //+IPD,0,11,StartTask>6
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[12]=='a')&&(rcvTable[15]=='T')&&(rcvTable[18]=='k')
			 &&(rcvTable[19]=='>')&&(rcvTable[20]=='6')){
				 
				 Task6 = 1;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
				 i = 0;   //接收数组指向了第0个元素
			
				 //+IPD,0,10,StopTask>1
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='1')){
				 
				 Task1 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素

				 //+IPD,0,10,StopTask>2
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='2')){
				 
				 Task2 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素		 

				 //+IPD,0,10,StopTask>3
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='3')){
				 
				 Task3 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素		 
				 
				 //+IPD,0,10,StopTask>4
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='4')){
				 
				 Task4 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素		 
				 
				 //+IPD,0,10,StopTask>5
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='5')){
				 
				 Task5 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素		 
				 
				 //+IPD,0,10,StopTask>6
			 }else if((rcvTable[0]=='+')&&(rcvTable[1]=='I')&&(rcvTable[2]=='P')
			 &&(rcvTable[3]=='D')&&(rcvTable[4]==',')&&(rcvTable[10]=='S')
			 &&(rcvTable[13]=='p')&&(rcvTable[14]=='T')&&(rcvTable[17]=='k')
			 &&(rcvTable[18]=='>')&&(rcvTable[19]=='6')){
				 
				 Task6 = 0;
				 arryClear(rcvTable);  //清除接收数组中全部内容，全部置0
			   i = 0;			//接收数组指向了第0个元素		 
			 }
			 
			 
		}		
		
		}
}