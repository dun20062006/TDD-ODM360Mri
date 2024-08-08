#ifndef    _TASK_H
#define    _TASK_H


#define MAX_TASKS                     11
#define ERROR_TOO_MANY_RASKS          0 
#define ERROR_CANNONT_DELETE_TASK     1
#define Return_ERROR                  2
#define Return_NORMAR                 3
typedef struct Task
 {
   void (* pTask)(void);
   unsigned int  Delay;
   unsigned int Period;
   unsigned char RunMe;
   unsigned char Co_op;
 };	
unsigned char Add_Task(void(*pFunction)(void),unsigned int DELAY,unsigned int PERIOD,unsigned int Co_op);
unsigned char Delete_Task(unsigned char TASK_INDEX);
void Init_Task(void);
void Updata(void);
void Dispartch_Task(void);
#endif