#include "includes.h"
struct Task Tasks[MAX_TASKS];
unsigned char Error_code;
unsigned int  Error_tick_const;
unsigned char Last_error_code;  
void Init_Task(void) 
{
   unsigned char Index;
   for(Index = 0; Index <MAX_TASKS; Index++)
     {
       Tasks[Index].pTask  = 0;
       Tasks[Index].Delay  = 0;
       Tasks[Index].Period = 0;
       Tasks[Index].RunMe  = 0;
       Tasks[Index].Co_op  = 0;

	 }
}		
unsigned char Add_Task(void(*pFunction)(void),
                       unsigned int DELAY,
					   unsigned int PERIOD,
					   unsigned int Co_op)
{
   unsigned char Index = 0;
   while((Tasks[Index].pTask != 0)&&(Index<MAX_TASKS))
    {
       Index++;
    }
   if(Index == MAX_TASKS)
    {  	       
       Error_code = ERROR_TOO_MANY_RASKS;
	   return MAX_TASKS; 
    }
   Tasks[Index].pTask = pFunction;
   Tasks[Index].Delay  = DELAY;
   Tasks[Index].Period = PERIOD;
   Tasks[Index].Co_op=Co_op;
   return Index;
}
unsigned char Delete_Task(unsigned char TASK_INDEX)
{
   if(Tasks[TASK_INDEX].pTask == 0)
    {
	  Error_code = ERROR_CANNONT_DELETE_TASK;
	  return Return_ERROR; 
	}
   Tasks[TASK_INDEX].pTask  = 0;
   Tasks[TASK_INDEX].Delay  = 0;
   Tasks[TASK_INDEX].Period = 0;
   Tasks[TASK_INDEX].RunMe  = 0;
   Tasks[TASK_INDEX].Co_op  = 0;
   return Return_NORMAR;
}  
void Report_Status(void)
 {
 ;    //加入空闲任务代码
 }
   
//轮询
void Updata(void)
{
   unsigned char Index;
   for (Index = 0;Index < MAX_TASKS;Index++)
    {
	  if(Tasks[Index].pTask)                  
	   {
	     if(Tasks[Index].Delay == 0)         
		   {
	         if(Tasks[Index].Co_op)           
              {
		         Tasks[Index].RunMe =1;     
			  }
			 else
			  {
			 	(*Tasks[Index].pTask)();
                Tasks[Index].RunMe=0; 
	 		    if(Tasks[Index].Period==0)
				 {
				   Tasks[Index].pTask =0;
				 }
			  }	   
			 if(Tasks[Index].Period)
			   {
			     Tasks[Index].Delay = Tasks[Index].Period;
			   }	
		   }
		  else 
		   {
		     Tasks[Index].Delay -=1;
		   }
	   }
	}
}	
//调度
void Dispartch_Task(void)
 {
    unsigned char Index;
	for(Index = 0; Index < MAX_TASKS;Index++)
	  {
	    if(Tasks[Index].RunMe>0)
		  {
		    (*Tasks[Index].pTask)();
		    Tasks[Index].RunMe-=1;
			if(Tasks[Index].Period == 0)
			  {
			   Delete_Task(Index);
		      }
	      }
	  }
	//Report_Status();   加入空闲任务代码
}	