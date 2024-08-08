
#include "includes.h"

void main(void)
{
  unsigned x=0;
  init_system();
  Sound_Count=20;
  while(1)
  {  
    //Dispartch_Task();
    DataSynchronization();
    HandpieceKey();
  }
}





