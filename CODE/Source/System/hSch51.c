/*------------------------------------------------------------------*-

   hSCH51.C (v1.00) 

-*------------------------------------------------------------------*/

#include "Config.h"
#include "hSch51.h"

// ------ 公共变量定义 ------------------------------

sTaskH idata hSCH_tasks_G[hSCH_MAX_TASKS];  //任务数组


/******************************************************************************/
// 混合式调度器初始化函数
// 函数名称：hSCH_Init_T0
// 输入参数：无
// 输出参数：无 
// 函数功能：初始化调度器数据结构，并按要求的速率设置计时器中断
//           在使用调度程序之前，必须调用此函数。
/******************************************************************************/
void hSCH_Init_T0(void) 
{
	tByte i;
	
  for (i = 0; i < hSCH_MAX_TASKS; i++) 
  {
     hSCH_Delete_Task(i);
  }
	
	 //现在设置定时器0，为16位手动重装模式
   // 当前使用11.0592M晶振
   // 所需的定时器0溢出时间为0.001秒（1毫秒）
	
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值 
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时

}


/******************************************************************************/
// 混合式调度器启动函数
// 函数名称：hSCH_Start()
// 输入参数：无
// 输出参数：无 
// 函数功能：通过启用中断来启动计划程序
// 注意：通常在添加所有常规任务后调用，使任务保持同步。
// 注意：只应启用调度程序中断！！！
/******************************************************************************/
void hSCH_Start(void) 
   {
   EA = 1;
   }

/******************************************************************************/
// 混合式调度器刷新函数
// 函数名称：hSCH_Update()
// 输入参数：无
// 输出参数：无 
// 函数功能：
// 说明：这是调度器的中断服务程序。hSCH_Init_T0()中的定时器设置决定了
//       调用频率，这个版本是由定时器0中断出发的，定时器0为手动重装模式	 
/******************************************************************************/	 
void hSCH_Update(void) interrupt INTERRUPT_Timer_0_Overflow
{
  tByte Index;

  TF0 = 0;     // 需要手动清除定时器0溢出标志位
	TR0 = 0;
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TR0 = 1;
	
   //注：计算单位为*时标*（非毫秒）
  for (Index = 0; Index < hSCH_MAX_TASKS; Index++)
  {
     if (hSCH_tasks_G[Index].pTask) //检查这里是否有任务
      {
        if (hSCH_tasks_G[Index].Delay == 0)  //任务需要运行
          {
            if (hSCH_tasks_G[Index].Co_op)  //如果是一个合作式任务
             {
               hSCH_tasks_G[Index].RunMe += 1;  //RunMe标志+1
             }
						 else   //否则如果为抢占式任务，立即运行任务
             {
               (*hSCH_tasks_G[Index].pTask)();  // 运行任务
               hSCH_tasks_G[Index].RunMe -= 1;   // RunMe标志复位/-1
							 
               if (hSCH_tasks_G[Index].Period == 0)    // 周期性任务将再次运行
                { 																		 // 如果是一个单次任务，将它从数组中删除
                  hSCH_tasks_G[Index].pTask  = 0;
                }
             }
            if (hSCH_tasks_G[Index].Period)  // 调度定期任务再次运行
             {
               hSCH_tasks_G[Index].Delay = hSCH_tasks_G[Index].Period;
             }
            }
         else    // 任务还没有准备好运行，Delay-1
            {
            hSCH_tasks_G[Index].Delay -= 1;
            }
         }         
      }
   }   

/******************************************************************************/
// 混合式调度器调度函数
// 函数名称：hSCH_Dispatch_Tasks()
// 输入参数：无
// 输出参数：无 
// 函数功能：
// 说明：这是“调度”函数。当一个任务函数需要运行时，hSCH_Dispatch_Tasks()将运行它
	 //       这个函数需要被主循环重复调用
/******************************************************************************/	 
void hSCH_Dispatch_Tasks(void) 
{
  tByte Index;
	
  for (Index = 0; Index < hSCH_MAX_TASKS; Index++)  // 调度运行下一个任务（如果有）
     {
     //只调度合作式任务
     if ((hSCH_tasks_G[Index].Co_op) && (hSCH_tasks_G[Index].RunMe > 0)) 
       {
        (*hSCH_tasks_G[Index].pTask)();  //运行任务
         hSCH_tasks_G[Index].RunMe -= 1;   //复位/-1RunMe标志

         //周期性任务将自动重新运行
				 // -如果这是一个“单次”任务，从数组中删除它
         if (hSCH_tasks_G[Index].Period == 0)
            {
            //比通过调用来删除任务更快
            hSCH_tasks_G[Index].pTask = 0;
            }
        }
      }
 }

/******************************************************************************/
// 混合式调度器任务添加函数
// 函数名称：hSCH_Add_Task()
// 输入参数：void (code* Fn_p)(),tWord Del,tWord Per,bit Co_op
// 输出参数：无 
// 函数功能：使任务(函数)以定期间隔或在用户定义的延迟之后执行
// 说明：这是“调度”函数。当一个任务函数需要运行时，hSCH_Dispatch_Tasks()将运行它
//       这个函数需要被主循环重复调用
/******************************************************************************/	 
/*------------------------------------------------------------------*-
  Fn_P  - 要调度的函数的名称。
          注意:所有计划函数必须是'void, void' 
          也就是说，它们必须不带参数，并且有
          一个void返回类型。
                   
  Del   - 任务第一次执行前的间隔(TICKS)

  Per   - 如果'PERIOD'为0，函数只被调用一次，
					时间由'DELAY'决定。如果PERIOD不为零，
					然后以一定的间隔重复调用该函数
					由PERIOD的值决定(参见下面的示例
				  这应该有助于澄清这一点)。

  Co-op - 如果是合作式任务则设置（1）; 如果是抢占式任务则设置（0）

  返回值:  

  返回在任务数组中添加任务的位置。
	如果返回值是SCH_MAX_TASKS，那么任务不能添加到数组中(因为空间不足)。
	如果返回值是< SCH_MAX_TASKS，则任务被成功添加。

  注意:这个返回值可能是必需的，如果一个任务随后要被删除-参见SCH_Delete_Task()。


  EXAMPLES:

  Task_ID = hSCH_Add_Task(Do_X,1000,0,0);
  Causes the function Do_X() to be executed once after 1000 ticks.
  (Pre-emptive task)          

  Task_ID = hSCH_Add_Task(Do_X,0,1000,1);
  Causes the function Do_X() to be executed regularly, every 1000 ticks.            
  (co-operative task)          

  Task_ID = hSCH_Add_Task(Do_X,300,1000,0);
  Causes the function Do_X() to be executed regularly, every 1000 ticks.
  Task will be first executed at T = 300 ticks, then 1300, 2300, etc.            
  (Pre-emptive task)          
 
-*------------------------------------------------------------------*/
tByte hSCH_Add_Task(void (code* Fn_p)(), // 任务函数指针
                   tWord   Del,    // 直到任务第一次运行时的时标数 
                   tWord   Per,    // 重复运行之间的时标数
                   bit     Co_op)  // 合作式任务（1） / 抢占式任务（0）
   {
   tByte Index = 0;
   
   // First find a gap in the array (if there is one)
   while ((hSCH_tasks_G[Index].pTask != 0) && (Index < hSCH_MAX_TASKS))
      {
      Index++;
      } 
   
   // Have we reached the end of the list?   
   if (Index == hSCH_MAX_TASKS)
      {
      return hSCH_MAX_TASKS;  
      }
      
   // 如果能运行到这里，说明任务队列里有空间
   hSCH_tasks_G[Index].pTask = Fn_p;
   hSCH_tasks_G[Index].Delay  = Del;
   hSCH_tasks_G[Index].Period = Per;
   hSCH_tasks_G[Index].Co_op = Co_op;
   hSCH_tasks_G[Index].RunMe  = 0;

   return Index; //返回任务的位置(以便以后删除)
   }

/******************************************************************************/
// 混合式调度器任务删除函数
// 函数名称：hSCH_Delete_Task()
// 输入参数：tByte Task_index
// 输出参数：无 
// 函数功能：从调度程序中删除任务
// 说明：从调度程序中删除任务。注意，这将从内存中删除相关函数:
//       它只是意味着它不再被调度器调用。
/******************************************************************************/	 
/*------------------------------------------------------------------*-

  参数:   Task_index - 任务索引.  由 hSCH_Add_Task(). 提供

  返回值:  RETURN_ERROR 或 RETURN_NORMAL

-*------------------------------------------------------------------*/
bit hSCH_Delete_Task(tByte Task_index) 
   {
   bit Return_code;

   if (hSCH_tasks_G[Task_index].pTask == 0)  //这里没有任务
      {
      Return_code = 1; //RETURN_ERROR
      }
   else
      {
      Return_code = 0; //RETURN_NORMAL
      }      
   
   hSCH_tasks_G[Task_index].pTask   = 0;
   hSCH_tasks_G[Task_index].Delay   = 0;
   hSCH_tasks_G[Task_index].Period  = 0;
   hSCH_tasks_G[Task_index].RunMe   = 0;

   return Return_code;       // 返回状态
   }
	 
	 

/******************************************************************************/
// 函数名称：hSCH_Run
// 输入参数：无
// 输出参数：无 
// 函数功能：启用作为调度器时基的T0中断
/******************************************************************************/	 	 
void hSCH_Run(void)
{
	ET0   = 1;  // 开启定时器0中断
}
/******************************************************************************/
// 函数名称：hSCH_Pause
// 输入参数：无
// 输出参数：无 
// 函数功能：禁用用作为调度器时基的T0中断
/******************************************************************************/
void hSCH_Pause(void)
{
	ET0   = 0;  // 禁用定时器0中断
}