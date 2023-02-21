/*------------------------------------------------------------------*-
  
   hSCH51.h (v1.00)

-*------------------------------------------------------------------*/

#ifndef _hSCH51_H
#define _hSCH51_H


// ------ 公共数据类型声明 ----------------------------

//如果可能，存储在DATA区，以便快速访问
//每个任务的总内存为8字节
typedef idata struct 
   {
		 
   void (code * pTask)(void);   //指向任务的指针（必须是“void（void）”函数）

   tWord Delay;     //延迟（滴答声）直到函数（下一个）运行

   tWord Period;    //每次运行的间隔   

   tByte RunMe;     //当任务即将执行时递增(由调度程序)  

   tByte Co_op;     //合作式任务设置（1），抢占式任务设置（0）
		 
   } sTaskH; 

// ------ 公共函数原型 -------------------------------

//核心调度器函数

void hSCH_Init_T0(void);
void hSCH_Start(void);
void hSCH_Update(void);
void  hSCH_Dispatch_Tasks(void);
tByte hSCH_Add_Task(void (code *)(void), tWord, tWord, bit);  
bit   hSCH_Delete_Task(tByte);
void hSCH_Run(void);
void hSCH_Pause(void);

// ------ 公共常数 -----------------------------------------


#define hSCH_MAX_TASKS   (11)   //一次所需的最大任务数
															 //在程序执行期间
															 //必须针对每个新项目进行调整
 
#endif
                              

