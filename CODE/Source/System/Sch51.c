/*------------------------------------------------------------------*-

   SCH51.C (v1.00) 

  ------------------------------------------------------------------

   *** 这些是核心调度器函数 ***
   --- 这些功能可用于所有8051设备 ---

   *** SCH_MAX_TASKS *必须*由用户设置 ***
   --- 参见“Sch51.H” ---

   *** 包括(可选)节能模式 ***
   --- 您必须确保已适应掉电模式 ---
   --- 匹配您选择的设备(或完全禁用) ---

-*------------------------------------------------------------------*/

#include "Config.h"
#include "Sch51.h"

// ------ 公共变量定义 ------------------------------

sTask SCH_tasks_G[SCH_MAX_TASKS];   // 任务数组


// ------ 私有函数原型 ------------------------------

static void SCH_Manual_Timer0_Reload(void);


// ------ 私有变量 ----------------------------------------


/*------------------------------------------------------------------*-

  SCH_Manual_Timer0_Reload()

  这个调度器使用一个(手动重新加载的)16位计时器。
  手动重新加载意味着所有的时间都是近似的。 
  此调度器不适用于以下应用程序
  准确的时间是必需的!!
  在此函数中执行计时器重新加载. 
 
-*------------------------------------------------------------------*/
void SCH_Manual_Timer0_Reload()
{	
	TR0 = 0;		//定时器0停止计时
	TL0 = 0x66;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TR0 = 1;		//定时器0开始计时
}

/*------------------------------------------------------------------*-

  SCH_Start()

  通过启用中断启动调度程序。

  注意:通常在添加所有常规任务后调用，
       以保持任务同步。

  注意:只有调度器中断应该被启用!!
 
-*------------------------------------------------------------------*/
void SCH_Start(void) 
   {
   EA = 1;
   }


/*------------------------------------------------------------------*-

  SCH_Init_T0()

  调度程序初始化函数。
	准备调度程序数据结构，并按要求的速率设置计时器中断。
	必须在使用调度器之前调用此函数。

-*------------------------------------------------------------------*/
void SCH_Init_T0(void) 
   {
   tByte i;

   for (i = 0; i < SCH_MAX_TASKS; i++) 
      {
      SCH_Delete_Task(i);
      }


   // 使用定时器0,16位手动重装
   TMOD &= 0xF0; // 清除所有T0位(T1保持不变)
   TMOD |= 0x01; // 设置所需T0位(T1保持不变)

   // 设置定时器重装值
   SCH_Manual_Timer0_Reload();

   //  启用定时器0中断
   ET0  = 1;
   }

/*------------------------------------------------------------------*-

  SCH_Update

  这是调度程序ISR。
	它的调用速率由SCH_Init_T0()中的计时器设置决定。
	此版本由0定时器中断触发。
 
-*------------------------------------------------------------------*/
void SCH_Update(void)
   {
   tByte Index;
   SCH_Manual_Timer0_Reload();  //定时器0重装

   // 注:计算单位为*TICKS*(不是毫秒)
   for (Index = 0; Index < SCH_MAX_TASKS; Index++)
      {
      if (SCH_tasks_G[Index].pTask) // 检查这个位置是否有任务
         {
         if (SCH_tasks_G[Index].Delay == 0)
            {
            // 任务即将运行
            SCH_tasks_G[Index].RunMe += 1;  // Inc. the 'Run Me' flag

            if (SCH_tasks_G[Index].Period)
               {
               // 安排周期性任务再次运行
               SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
               }
            }
         else
            {
            // 还没有准备好运行:只需减少延迟
            SCH_tasks_G[Index].Delay -= 1;
            }
         }         
      }
   } 
	 
/*------------------------------------------------------------------*-

  SCH_Dispatch_Tasks()

  这是'dispatcher'函数。当一个任务(函数)
， SCH_Dispatch_Tasks()将运行它。
这个函数必须从主循环中(重复地)调用。

-*------------------------------------------------------------------*/
void SCH_Dispatch_Tasks(void) 
   {
   tByte Index;
   for (Index = 0; Index < SCH_MAX_TASKS; Index++) // 调度(运行)下一个任务(如果准备好了)
      {
      if (SCH_tasks_G[Index].RunMe > 0) 
         {
         (*SCH_tasks_G[Index].pTask)();  // 运行的任务
         SCH_tasks_G[Index].RunMe -= 1;   // 重置 / 减少 RunMe 标志

         //定时任务将自动重新运行
         // -如果这是一个'单次'任务，从数组中删除它
         if (SCH_tasks_G[Index].Period == 0)
            {
            SCH_Delete_Task(Index);
            }
         }
      }   
   }

/*------------------------------------------------------------------*-

  SCH_Add_Task()

  使任务(函数)定期执行
  或者在用户定义的延迟之后

  Fn_P   - 要调度的函数的名称。
           注意:所有计划函数必须是'void, void' -
           也就是说，它们必须不带参数，并且有
           一个void返回类型。
                   
  DELAY  - 任务第一次执行前的间隔(TICKS)

  PERIOD - 如果'PERIOD'为0，函数只被调用一次，
					 时间由'DELAY'决定。如果PERIOD不为零，
					 然后以一定的间隔重复调用该函数
					 由PERIOD的值决定(参见下面的示例
				   这应该有助于澄清这一点)。


  返回值:  

  返回在任务数组中添加任务的位置。
	如果返回值是SCH_MAX_TASKS，那么任务不能添加到数组中(因为空间不足)。
	如果返回值是< SCH_MAX_TASKS，则任务被成功添加。

  注意:这个返回值可能是必需的，如果一个任务随后要被删除-参见SCH_Delete_Task()。

  例子:

  Task_ID = SCH_Add_Task(Do_X,1000,0);
  函数Do_X()将在1000次 sch ticks 后执行一次。           

  Task_ID = SCH_Add_Task(Do_X,0,1000);
  定期执行的函数Do_X()，每1000个 sch ticks 。            

  Task_ID = SCH_Add_Task(Do_X,300,1000);
  使函数Do_X()定期执行，每1000次 ticks。
  任务将首先在T = 300 ticks时执行，然后是1300,2300，等等。            
 
-*------------------------------------------------------------------*/
tByte SCH_Add_Task(void (code * pFunction)(), 
                   const tWord DELAY, 
                   const tWord PERIOD)    
   {
   tByte Index = 0;
   
	 // 首先在数中找到一个缺口(如果有的话)
   while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
      {
      Index++;
      } 
   
   // 我们到达名单的末尾了吗?		
   if (Index == SCH_MAX_TASKS)  // 如果任务列表已满
      {
      return SCH_MAX_TASKS;  
      }
      
   // 如果能运行到这里，说明任务队列中有空间
   SCH_tasks_G[Index].pTask  = pFunction;
     
   SCH_tasks_G[Index].Delay  = DELAY;
   SCH_tasks_G[Index].Period = PERIOD;

   SCH_tasks_G[Index].RunMe  = 0;

   return Index; // 返回任务的位置(允许稍后删除)
   }

/*------------------------------------------------------------------*-

  SCH_Delete_Task()

  从调度程序中删除任务。注意这是
  *不*从内存中删除相关函数:
  它只是意味着它不再被调度器调用。
 
  TASK_INDEX - The task index.  由SCH_Add_Task()提供。

  返回值 : ETURN_ERROR 1 或 RETURN_NORMAL 0

-*------------------------------------------------------------------*/
bit SCH_Delete_Task(const tByte TASK_INDEX) 
   {
   bit Return_code;

   if (SCH_tasks_G[TASK_INDEX].pTask == 0)  // 这个位置没有任务…
      {
      Return_code = 1;        
      }
   else
      {
      Return_code = 0;
      }      
   
   SCH_tasks_G[TASK_INDEX].pTask   = 0x0000;
   SCH_tasks_G[TASK_INDEX].Delay   = 0;
   SCH_tasks_G[TASK_INDEX].Period  = 0;

   SCH_tasks_G[TASK_INDEX].RunMe   = 0;

   return Return_code;       // 返回状态
   }

