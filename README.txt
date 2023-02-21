/*******************************************/
/         以下为程序思路整理
/*******************************************/

继电器任务应该由多个输入信号对应单个任务
继电器任务输出应该由单个任务输出一个或多个IO
而不是多个任务共同占用一个IO

一个任务：
输入触发信号（一个或者多个信号）--->启动指定的任务
--->输出一个或者多个信号（应该由一个任务占用这些输出信号）
（不能由其他任务占用这些输出信号）

设置项
首先设置触发信号
设置不同的IO触发任务号（每个IO有其对应的任务）

继电器任务模式：
1.点动模式：
	有触发信号（无松手检测），则有输出，否则没有
2.自锁模式：
	有带松手检测触发信号，则启动任务输出，
	再次触发，则关闭输出
3.时间区间间歇：
	有带松手检测触发信号，则启动任务输出，
	再次触发，则关闭输出
	可以设置时间区间
	可以设置输出ON的时间，可按百分比设置
	可以设置输出OFF的时间，可按百分比设置
	可以设置周期时间
	可以设置OVERTIME，任务运行超过此时间则关闭
	
	“间歇”：应该有三个要素（以秒（S）作为时间单位）
	运行的时间，停止的时间，总的时间（周期时间Cycle Time）
	_______________
	               |_______________
	|<--On Time -->|<--Off Time-->|
	|<--------Cycle Time--------->|
	
	应该确认什么时候开始运行也就是起始运行时间，
	得确认两个起始时间，一个是On状态的起始时间，还有一个是Off状态的起始时间
	一共有两个状态，一个是On状态，一个是Off状态
	在指定的时间区间内将状态设置为On或者Off
	也就是做时间区间内判断
	
继电器的任务输出：
	首先当前任务TASK1是启动的状态，并且有了一个输出
	通过这个输出结果TASK1_Out,值为1则输出已经为当前任务分配的IO
	值为0则不输出
	
为什么外部输入信号触发的是任务，而不是任务内的具体信号？
如果没有外部输入设备，则可以使用ec11内部的Start Task

任务的触发
1.自锁触发，按下按键，并且释放才触发，端口匹配的任务

自锁触发的过程
1.确认端口为输入模式并且为自锁模式且端口被拉低，则记录下端口
2.判断有哪些端口被记录，再次判断端口有没有被释放，被释放则用端口任务号赋给自锁任务号
3.匹配到自锁任务号则开启或者关闭匹配的任务


2.点动触发，按下按键，直接触发端口匹配的任务

按键为松开状态此时按下则记录

点动触发的过程
1.确认端口为输入模式并且按键为松开状态，端口被拉低，则直接记录下端口，按键状态变为按下
2.判断有哪些端口被记录，再次判断端口是不是点动触发型，
  是则立即将端口任务号赋给点动任务号，然后如果端口被释放，
  则将按键设置为松开状态，允许重新设置

自锁还是点动输入实际模拟外部输入
自锁：按下按键，记录下按下的按键，进入记录的按键，直到按键释放，才设置任务
立即：按下按键，直接设置任务，并且直到按键释放才可重新设置




任务的时间控制:
首先是判断当前时间在时间区间内
再判断超时计数器有没有大于超时时间

否则任务的运行不满足时间条件
1,当前时间不在时间区间内，没有超时
//当前关闭输出
//直到在时间区间，继续运行

2.当前时间不在时间区间内，已经超时
//如果开启超时自动复位，将复位计数,否则关闭task，复位时间计数器，关闭输出

3.当前时间在时间区间内，已经超时
//如果开启超时自动复位，将复位计数，否则关闭task，复位时间计数器，关闭输出

如果要实现无限时间运行（意味着超时自动复位）



/******************************************************************************/
// STA模式操作步骤
/******************************************************************************/

AT+CWMODE_DEF=3        //设置当前wifi模式并保存到flash /1:STA/2:AP/3.STA+AP
AT+CWMODE_CUR=3  //设置当前wifi模式不保存到flash


AT+CWJAP_DEF="wifiname","password"   //连接AP并保存到FLASH
AT+CWJAP_CUR="wifiname","password"   //连接AP不保存到FLASH

AT+CIFSR                    //查看路由器分配的IP

AT+CIPMUX=1         //设置多连接 

AT+CIPSERVER=1,9527   //设置TCP服务器 


/*STA+AP模式设置*/
AT+CWMODE_CUR=3
AT+CWJAP_CUR="TP-LINK_847A","asdfghjkl"
AT+CWSAP_CUR="Wireless_Controller_Test","asdfghjkl",11,4
AT+CIFSR
AT+CIPMUX=1
AT+CIPSERVER=1,9527


/*GET 苏宁时间网址*/（get网址之后一定要加、/r/n）
AT+CIPMUX=0
AT+CIPSTART="TCP","quan.suning.com",80
AT+CIPSTART="TCP","223.111.230.101",80
AT+CIPSEND=50
GET http://quan.suning.com/getSysTime.do

/*GET www.shijian.cc 网址的GMT+8标准时间 */（get网址之后一定要加、/r/n）
AT+CIPMUX=0
AT+CIPSTART="TCP","www.shijian.cc",80
AT+CIPSTART="TCP","118.112.250.193",80
AT+CIPSEND=50
GET http://www.shijian.cc/000/clock.asp

/*GET www.beijing-time.org 网址上的GMT+8标准时间*/（get网址之后一定要加、/r/n）
AT+CIPMUX=0
AT+CIPSTART="TCP","beijing-time.org",80
AT+CIPSEND=50
GET http://www.beijing-time.org/t/time.asp
GET http://beijing-time.org/t/time.asp

GET /t/time.asp

/*http://api.k780.com/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json
*/




/*ESP8266的其他指令*/

AT+CIPSEND

AT+RESTORE   //重置

/*设置 UART 配置，保存到 Flash*/
AT+UART_DEF(_CUR)=9600,8,1,0,0





/*8266的初始化过程*/

AT+RST    //复位8266模块
AT+CWMODE_CUR=3   //设置当前wifi模式  
AT+CWJAP_CUR="TP-LINK_847A","asdfghjkl"   //连接AP

/*获取网络时间*/
AT+CIPSTART="TCP","www.shijian.cc",80
AT+CIPSEND=42
GET http://www.shijian.cc/000/clock.asp\r\n\r\n
显示时间

AT+CIPMUX=1   //使能多连接
AT+CIPSERVER=1,9527  //开启TCP服务器，只能在多连接的情况下开启
AT+CWSAP_CUR=\"Wireless_Controller\",\"asdfghjkl\",3,4  //设置8266 SOFTAP
AT+CIFSR

