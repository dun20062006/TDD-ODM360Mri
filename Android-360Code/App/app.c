#include "includes.h"
const unsigned int Color[2]={0x8410,0};
const unsigned int Color1[2]={0xf800,0};
unsigned char UL_workdate=0;//?????????????
unsigned char POWER_LEVEL=0;//

extern void TASK_SendToDwin(void);
extern void TASK_PROCESSING(void);
const unsigned int pxy[8][4]=
{
  { 76,150,124,174},
  {138,280,174,304},
  {187,150,235,174},
  {247,280,283,304},
  {296,150,344,174},
  {115,352,163,376},
  {260,352,308,376},
  {370,352,418,376}
};
const unsigned char temp_text[2][4]={"OFF\0","ON \0"};
const unsigned char user_type[4][6]={"NULL \0","Guest\0","User \0","Super\0"};
void delay_ms(unsigned int i)
{
  unsigned int x,y;
  for(x=0;x<i;x++)
  {
    for(y=0;y<1141;y++); 
  }
}
void DataSynchronization(void)
{
  unsigned char foot_buf;
  static unsigned char count1=0;
  static unsigned char count2=0;
  static unsigned char count3=0;
  

  TASK_SendToDwin(); //迪文屏串口通讯
  TASK_PROCESSING();//参数处理函数
  if (MACHINE_STATE.HANDLE_ID==1)
  {
    dispose_data();//1号手柄数据同步
  }
  if (MACHINE_STATE.WORK_STATE==1)//启动
  {
    if(MACHINE_STATE.HANDLE_ID==5)//5号爆脂手柄
    {        
     switch (SAVE_FAT_FLAME)
     {
      case 0:POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
      case 1:POWER1_ON;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
      case 2:POWER1_OFF;POWER2_ON;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
      case 3:POWER1_OFF;POWER2_OFF;POWER3_ON;POWER4_OFF;POWER5_OFF;  break;   
      case 4:POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_ON;POWER5_OFF;  break;
      case 5:POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_ON;  break;
      default:
      break;
     }
    }
    else
    {
      DisWork();
    }
  }
  if (MACHINE_STATE.WORK_STATE==0)//停止
  {
    if(MACHINE_STATE.HANDLE_ID==5)//5号爆脂手柄
    {        
    POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF;
    }

  }

}


void ItoA(unsigned int x,unsigned char *Text)
{
  unsigned int i=10000;
  while(i>0)
  {
   *Text=x/i+'0';
   x%=i;
   i=i/10;
   Text++; 
  }
   *Text='\0';
}
void LtoA(unsigned long x,unsigned char *Text)
{
  unsigned long i=1000000;
  x%=10000000;
  while(i>0)
  {
   *Text=x/i+'0';
   x%=i;
   i=i/10;
   Text++; 
  }
   *Text='\0';
}


void Dis_pressure(void)
{
 /* unsigned char pressure;//???
  unsigned int temperature; //????
  READ_P_T(&pressure,&temperature);
  Text1[0]=pressure/100+'0';
  Text1[1]=(pressure%100)/10+'0';
  Text1[2]=pressure%10+'0';
  Text1[3]='\0';
  print_texts(610,12,0,0xC1,2,0,0xDEDB,Text1);
  
  Text1[0]=water/10+'0';
  Text1[1]=water%10+'0';
  Text1[2]='K';
  Text1[3]='P';
  Text1[4]='a';
  Text1[5]='\0';*/
 // if(PressureSet == 1)
 // print_texts(610,12,0,0xC1,2,0,0xDEDB,Text1);
}



void DisFunctionKey(unsigned char K,unsigned char CMD)
{
  unsigned int x,y,xs,ys,i;
  xs=CMD*100;
  ys=Function_Tab[K]*100;
  x=(K/3)*145+30;
  y=(K%3)*175+65;
  cut_pic(1,10,xs,ys,xs+99,ys+99,x,y);
  xs=(Function_Tab[K]%5)*130;
  ys=Language*37;
  x=(K/3)*145+15;
  y=(K%3)*175+175;
  cut_pic(1,11,xs,ys,xs+130,ys+36,x,y);
}
void DisWelcome(void)
{
  unsigned int x,y,i;
  dis_pic(BackSet);//背景图片设置
  for(i=0;i<Function_Count;i++)
  {
    DisFunctionKey(i,0);
  }
  cut_pic(1,10,0,400,0+99,400+99,175,240);// ???????汛????完??
  if(ClockSet==TRUE)
  clock_on(ClockSet,3,0,700,10);
}
void DisIntensity(unsigned char ID)
{
  unsigned int x,xs,xe;
  //xs=Intensity[ID];
  xs=xs*50;
  xe=xs+49;
  x=ID;
  x=x*112;
  x=x+44;
  cut_pic(0,32,xs,0,xe,289,x,50);
  //cut_pic(0,32,Intensity[ID]*50,0,49+Intensity[ID]*50,289,44+ID*112,50);
}
void HandpieceSet(void)//射频选通  负压选通 H
{
  //cut_pic(0,28+Intensity[8],0,390,260,599,0,390);
  PORTB|=0x3C; 
  PORTB&=~(0x04<<Intensity[8]);
  PORTC|=0xF0; 
  PORTC&=~(0x10<<Intensity[8]);
}
void ModeSet(void)//电机转向 H
{
  unsigned char buff[9];
  unsigned char i;
  PORTE|=0x7C;
  if(Intensity[7]==0) {PORTE&=0xCB;for(i = 0; i < 8; i++){buff[i]=0;}buff[1]=1;}
  else if(Intensity[7]==1) {PORTE&=0x97;for(i = 0; i < 8; i++){buff[i]=0;}buff[3]=1;}
  else if(Intensity[7]==2) {PORTE&=0x9B;for(i = 0; i < 8; i++){buff[i]=0;}buff[5]=1;}
  else if(Intensity[7]==3) {PORTE&=0xC7;for(i = 0; i < 8; i++){buff[i]=0;}buff[7]=1;}

 // DwinWriteWord(ADDR_BOOTINGMOTO_TOWARD_LEFTDATA, buff[0]);//迪文屏通信函数
 // DwinWriteWord(ADDR_BOOTINGMOTO_TOWARD_RIGHTDATA, buff[1]);//迪文屏通信函数
  //DwinWriteWord(ADDR_BOOTINGMOTO_TOWARD_INDATA, buff[2]);//迪文屏通信函数
 // DwinWriteWord(ADDR_BOOTINGMOTO_TOWARD_OUTDATA, buff[3]);//迪文屏通信函数
}
void IntensitySet(void)//负压等级 H
{
  PORTC|=0x0F;
  //PORTC&=~(10-Intensity[4]);
  switch(Intensity[4])
  {
   case 0:  PORTC&=~15; break;
   case 1:  PORTC&=~12; break;
   case 2:  PORTC&=~9; break;
   case 3:  PORTC&=~7;  break;
   case 4:  PORTC&=~6;  break;
   case 5:  PORTC&=~5;  break;
   case 6:  PORTC&=~4;  break;
   case 7:  PORTC&=~3;  break;
   case 8:  PORTC&=~2;  break;
   case 9:  PORTC&=~1;  break;
   case 10: PORTC&=~0;  break;
   default: break;
  }
}
/*void DisMode(void)
{
  static unsigned int i=0;
  unsigned int xs,ys,xe,ye;
  if(DisPage!=WORKPAGE) return;
  if(Intensity[8]>1) return;
  if(Intensity[7]==0)
  {
   if(i>0) i-=1;
   else i=5;
   xs=i%3;
   xs=xs*240;
   ys=i/3;
   ys=ys*180;
   xe=i%3;
   xe=xe*240;
   xe=xe+239; 
   ye=i/3;
   ye=ye*180;
   ye=ye+179;
   cut_pic(0,33,xs,ys,xe,ye,280,395);
   //cut_pic(0,33,(i%3)*240,i/3*180,239+(i%3)*240,179+i/3*180,280,395);
  }
  else if(Intensity[7]==1)
  {
   if(i<5) i+=1;
   else i=0;
   xs=i%3;
   xs=xs*240;
   ys=i/3;
   ys=ys*180;
   xe=i%3;
   xe=xe*240;
   xe=xe+239; 
   ye=i/3;
   ye=ye*180;
   ye=ye+179;
   cut_pic(0,33,xs,ys,xe,ye,280,395);
   //cut_pic(0,33,(i%3)*240,i/3*180,239+(i%3)*240,179+i/3*180,280,395);
  }
  else if(Intensity[7]==2)
  {
   if(i>0) i-=1;
   else i=5;
   xs=i%3;
   xs=xs*240;
   ys=i/3;
   ys=ys*180;
   xe=i%3;
   xe=xe*240;
   xe=xe+239; 
   ye=i/3;
   ye=ye*180;
   ye=ye+179;
   cut_pic(0,34,xs,ys,xe,ye,280,395);
   //cut_pic(0,34,(i%3)*240,i/3*180,239+(i%3)*240,179+i/3*180,280,395);
  }
  else if(Intensity[7]==3)
  {
   if(i<5) i+=1;
   else i=0;
   xs=i%3;
   xs=xs*240;
   ys=i/3;
   ys=ys*180;
   xe=i%3;
   xe=xe*240;
   xe=xe+239; 
   ye=i/3;
   ye=ye*180;
   ye=ye+179;
   cut_pic(0,34,xs,ys,xe,ye,280,395);
   //cut_pic(0,34,(i%3)*240,i/3*180,239+(i%3)*240,179+i/3*180,280,395);
  }
}*/
void DisMode(void)//电机转向动画H
{
  /*
  static unsigned char i=0;
  if(DisPage!=WORKPAGE) return;
  if(Intensity[8]>1) return;
  if(Intensity[7]==0)
  {
   if(i==0)
   {
     cut_pic(0,33,0,0,239,179,280,395);
     i=5;
   }
   else if(i==1)
   {
     cut_pic(0,33,240,0,479,179,280,395);
     i=0;
   }
   else if(i==2)
   {
     cut_pic(0,33,480,0,719,179,280,395);
     i=1;
   }
   else if(i==3)
   {
     cut_pic(0,33,0,180,239,359,280,395);
     i=2;
   }
   else if(i==4)
   {
     cut_pic(0,33,240,180,479,359,280,395);
     i=3;
   }
   else if(i==5)
   {
     cut_pic(0,33,480,180,719,359,280,395);
     i=4;
   }
  }
  else if(Intensity[7]==1)
  {
   if(i==0)
   {
     cut_pic(0,33,0,0,239,179,280,395);
     i=1;
   }
   else if(i==1)
   {
     cut_pic(0,33,240,0,479,179,280,395);
     i=2;
   }
   else if(i==2)
   {
     cut_pic(0,33,480,0,719,179,280,395);
     i=3;
   }
   else if(i==3)
   {
     cut_pic(0,33,0,180,239,359,280,395);
     i=4;
   }
   else if(i==4)
   {
     cut_pic(0,33,240,180,479,359,280,395);
     i=5;
   }
   else if(i==5)
   {
     cut_pic(0,33,480,180,719,359,280,395);
     i=0;
   }
  }
  else if(Intensity[7]==2)
  {
   if(i==0)
   {
     cut_pic(0,34,0,0,239,179,280,395);
     i=5;
   }
   else if(i==1)
   {
     cut_pic(0,34,240,0,479,179,280,395);
     i=0;
   }
   else if(i==2)
   {
     cut_pic(0,34,480,0,719,179,280,395);
     i=1;
   }
   else if(i==3)
   {
     cut_pic(0,34,0,180,239,359,280,395);
     i=2;
   }
   else if(i==4)
   {
     cut_pic(0,34,240,180,479,359,280,395);
     i=3;
   }
   else if(i==5)
   {
     cut_pic(0,34,480,180,719,359,280,395);
     i=4;
   }
  }
  else if(Intensity[7]==3)
  {
   if(i==0)
   {
     cut_pic(0,34,0,0,239,179,280,395);
     i=1;
   }
   else if(i==1)
   {
     cut_pic(0,34,240,0,479,179,280,395);
     i=2;
   }
   else if(i==2)
   {
     cut_pic(0,34,480,0,719,179,280,395);
     i=3;
   }
   else if(i==3)
   {
     cut_pic(0,34,0,180,239,359,280,395);
     i=4;
   }
   else if(i==4)
   {
     cut_pic(0,34,240,180,479,359,280,395);
     i=5;
   }
   else if(i==5)
   {
     cut_pic(0,34,480,180,719,359,280,395);
     i=0;
   }
  }
  */
}
void DisWork(void)
{
   unsigned char i;
   //EEPROMReadBytes(IntensityAddr+Function_Tab[Function_Ptr]*9,Intensity,9);
   //dis_pic(28);
   //cut_pic(0,107,0,Language*30,761,29+Language*30,22,344);
   /*
   for(i=0;i<9;i++)//显示参数等级
   {
     if(Intensity[i]>Intensity_Max[i]) Intensity[i]=Intensity_Tab[Function_Tab[Function_Ptr]][i];
     if(i<7) DisIntensity(i);
   }*/
   //EEPROMReadBytes(CounterAddr+hand[Intensity[8]]*4,&Total_counter,4);
   HandpieceSet();//射频选通 负压选通
   IntensitySet();//负压等级
   //ModeSet();//电机转向设置
   //DisCount();//显示计时
   //Dis_pressure();
   //cut_pic(0,28+Intensity[7],523,388,588,788,523,388);
}
void DisMV(void)
{
  /*
  static unsigned char pic=35;
  if(DisPage==WELCOMEPAGE)
  {
    if(MV<50) MV++;
	else 
	{
	  DisPage=MVPAGE;
	}
  }
  if(MC==1)
	{
	  DisWelcome();
      DisPage=WELCOMEPAGE;
	  MV=0;
	  MC=0;
	  return;
  }
  if(DisPage!=MVPAGE) return;
  if(pic<106) pic++;
  else pic=36;
  dis_pic(pic);
  */
}










unsigned char GetKeyID(const struct KEY *P,unsigned char Len)
{
  unsigned char ID;
  for(ID=0;ID<Len;ID++)
  {
   if((Touch_X>P->XS)&&(Touch_X<P->XE))
   {
     if((Touch_Y>P->YS)&&(Touch_Y<P->YE))
	 {
	   return ID;
	 }
   }
   P++;
  }
  return 255;
}
void MainKeyDown(void)
{
  if(DisPage!=WELCOMEPAGE) return;
  KeyID=GetKeyID(Main_Key,6);
  if(KeyID<Function_Count)//????踩?????完??
  {
    DisFunctionKey(KeyID,1);
	Function_Ptr=KeyID;
  }
  else if(KeyID==4)//??????
  {
	cut_pic(0,13,0,0,199,319,0,50); 
	get_time();
  }
  else if(KeyID==5)//???????
  {
	 cut_pic(1,10,100,400,100+99,400+99,175,240);//????????????完??   x=(K/3)*145+30;  y=(K%3)*175+65;
  // Function_Ptr=KeyID;
  }
  /////////////////////////////
  else if(Function_Count == 0)
  {
    KeyID = 0;
	Function_Ptr=KeyID;  
  }
  /////////////////////////////add function by hanjingyang 20170920
}

void MainKeyUp(void)
{
  static char Cnt=0;
  if(DisPage!=WELCOMEPAGE) return;
  if(KeyID<Function_Count)
  {
   DisPage=WORKPAGE;
   DisWork();
   Send_Data8();
  }
  else if(KeyID==4)
  {
    DisPage=STARTPAGE;
  }
  else if(KeyID==5)//???????
  {
    DisPage=ultrasonicpage;
    dis_pic(108);
    cut_pic(1,109,0,510,60,599,420,170);
  }
  else if(Function_Count==0)
  {
   DisPage=WORKPAGE;
   DisWork();
   Send_Data8();
  } 
  Cnt=KeyID==255?++Cnt:0;
  if(Cnt>=10) 
  {
    Cnt=0;
    Chack_screen(); 
  }
}
void StartKeyDown(void)
{
  if(DisPage!=STARTPAGE) return;
  KeyID=GetKeyID(Start_Key,9); 
  if(KeyID<8)
  {
    cut_pic(0,13,201,KeyID*40,400,KeyID*40+40,0,50+KeyID*40);
  }
  if(KeyID==0)
  {
    DisPage=TIMEPAGE;
    cut_pic(0,14,0,0,269,330,300,100);
	  text_ptr=0;
	  Text[0]=(datetime[0]>>4)+'0';
    Text[1]=(datetime[0]&0x0f)+'0';
    Text[2]='-';
    Text[3]=(datetime[1]>>4)+'0';
    Text[4]=(datetime[1]&0x0f)+'0';
    Text[5]='-';
    Text[6]=(datetime[2]>>4)+'0';
    Text[7]=(datetime[2]&0x0f)+'0';
    Text[8]=' ';
	  Text[9]=(datetime[4]>>4)+'0';
    Text[10]=(datetime[4]&0x0f)+'0';
    Text[11]=':';
    Text[12]=(datetime[5]>>4)+'0';
    Text[13]=(datetime[5]&0x0f)+'0';
    Text[14]=':';
    Text[15]=(datetime[6]>>4)+'0';
    Text[16]=(datetime[6]&0x0f)+'0';
    Text[17]='\0';
    Text[18]=Text[text_ptr];
    Text[19]='\0';
	  print_texts(335,156,0,0xD1,2,0x04bb,0xffff,Text);
    print_texts(335+text_ptr*12,156,0,0xD1,2,0xffff,0x04bb,&Text[18]);
  }
  else if(KeyID==2)
  {
    DisPage=SOUNDPAGE;
    cut_pic(0,14,181,331,360,531,300,200);
	  cut_pic(0,14,1,371,170,371+(10-SoundSet)*15,301,240);
  }
  else if(KeyID==3)
  {
    DisPage=LANGUAGEPAGE; 
    cut_pic(0,15,0,0,374,400,300,100);
	  cut_pic(0,15,Language_Key[Language].XS+75,Language_Key[Language].YS-100,Language_Key[Language].XE+75,Language_Key[Language].YE-100,Language_Key[Language].XS,Language_Key[Language].YS);
  }
  else if(KeyID==4)
  {
    DisPage=BACKPAGE; 
    cut_pic(0,16+BackSet/6,(BackSet%3)*241,(BackSet%6/3)*270,(BackSet%3)*241+239,(BackSet%6/3)*270+269,300,200);
  }
  else if(KeyID==5)
  {
    DisPage=USBPAGE;
    cut_pic(0,26,0,282,269,422,300,200);
  }
  else if(KeyID==6)
  {
    if(Card_Type>1)
	{
     DisPage=CARDPAGE;
	 text_ptr=255;
     cut_pic(0,18,0,0,269,369,300,100);
	 Text[0]=User_ID/100+'0';
     Text[1]=(User_ID%100)/10+'0';
	 Text[2]=User_ID%10+'0';
     Text[3]='\0';
	 print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
	 User_Type=0;
	 print_consttexts(406,152,0,0x81,2,0x04bb,0xffff,&user_type[User_Type][0]);
	 User_Counter=10000;
     Text[4]=User_Counter/10000+'0';
     Text[5]=User_Counter%10000/1000+'0';
	 Text[6]=User_Counter%1000/100+'0';
	 Text[7]=User_Counter%100/10+'0';
	 Text[8]=User_Counter%10+'0';
	 Text[9]='\0';
     Text[10]=0;
     Text[11]='\0';
	 print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
	}
	else cut_pic(0,13,0,0,199,319,0,50); 
  }
  else if(KeyID==7)
  {
    DisPage=PASSWORDPAGE;
	//EEPROMReadBytes(PasswordAddr,&PasswordTab,6);
    if((PasswordTab[0]>9)||(PasswordTab[1]>9)||(PasswordTab[2]>9)||(PasswordTab[3]>9)||(PasswordTab[4]>9)||(PasswordTab[5]>9))
    {
      PasswordTab[0]=6;
	  PasswordTab[1]=6;
	  PasswordTab[2]=6;
	  PasswordTab[3]=6;
	  PasswordTab[4]=6;
	  PasswordTab[5]=6;
	  //EEPROMWriteBytes(PasswordAddr,&PasswordTab,6);
    }
	cut_pic(0,27,0,0,269,325,300,100);
	text_ptr=0;
	Text[0]=' ';
	Text[1]=' ';
	Text[2]=' ';
	Text[3]=' ';
	Text[4]=' ';
	Text[5]=' ';
	Text[6]='\0';
	Text[7]='*';
    Text[8]='\0';
	Text[9]=' ';
    Text[10]='\0';
  }
  else if(KeyID==8)
  {
    DisWelcome();
  }
}
void StartKeyUp(void)
{
  if(DisPage!=STARTPAGE) return;
  if(KeyID==1)
  {
    Chack_screen();
    while((R_buf[1]!=0xE4)||(R_buf[2]!=0x4F)||(R_buf[3]!=0x4B));
	Delay_MS(100);
	DisWelcome();
	DisPage=WELCOMEPAGE;
  }
   else if(KeyID==8)
  {
	DisPage=WELCOMEPAGE;
  }
}

void TimeKeyDown(void)
{
  if(DisPage!=TIMEPAGE) return;
  KeyID=GetKeyID(Time_Key,13); 
  if(KeyID<10)
  {
    if((text_ptr==3)&&(KeyID>1));
	else if((text_ptr==4)&&(Text[3]=='1')&&(KeyID>2));
	else if((text_ptr==6)&&(KeyID>3));
	else if((text_ptr==7)&&(Text[6]=='3')&&(KeyID>1)); 
    else if((text_ptr==9)&&(KeyID>2));
	else if((text_ptr==10)&&(Text[9]=='2')&&(KeyID>3)); 
	else if((text_ptr==12)&&(KeyID>5));
	else if((text_ptr==15)&&(KeyID>5));
	else
	{
	  cut_pic(0,14,Time_Key[KeyID].XS-28,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-28,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	  Text[text_ptr]=KeyID+'0';
	  Text[18]=Text[text_ptr];
      print_texts(335+text_ptr*12,156,0,0xD1,2,0xffff,0x04bb,&Text[18]);
	}
	
  }
  else if(KeyID==10)
  {
    cut_pic(0,14,Time_Key[KeyID].XS-28,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-28,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
    if(text_ptr<16) text_ptr++;
	else text_ptr=0;
	if((text_ptr==2)||(text_ptr==5)||(text_ptr==8)||(text_ptr==11)||(text_ptr==14)) text_ptr++;
	Text[18]=Text[text_ptr];
	print_texts(335,156,0,0xD1,2,0x04bb,0xffff,Text);
    print_texts(335+text_ptr*12,156,0,0xD1,2,0xffff,0x04bb,&Text[18]);
  }
  else if(KeyID==11)
  {
    cut_pic(0,14,Time_Key[KeyID].XS-28,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-28,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	datetime[0]=((Text[0]-'0')<<4)|(Text[1]-'0');
	datetime[1]=((Text[3]-'0')<<4)|(Text[4]-'0');
	datetime[2]=((Text[6]-'0')<<4)|(Text[7]-'0');
  datetime[4]=((Text[9]-'0')<<4)|(Text[10]-'0');
	datetime[5]=((Text[12]-'0')<<4)|(Text[13]-'0');
	datetime[6]=((Text[15]-'0')<<4)|(Text[16]-'0');
	clock_set(datetime[0],datetime[1],datetime[2],datetime[4],datetime[5],datetime[6]);
  }
}
void TimeKeyUp(void)
{
  if(DisPage!=TIMEPAGE) return;
  if(KeyID<12)
  {
   cut_pic(0,14,0,90,269,330,300,190);
  }
  if(KeyID<10)
  {
    if((text_ptr==3)&&(KeyID>1));
	else if((text_ptr==4)&&(Text[3]=='1')&&(KeyID>2));
	else if((text_ptr==6)&&(KeyID>3));
	else if((text_ptr==7)&&(Text[6]=='3')&&(KeyID>1)); 
    else if((text_ptr==9)&&(KeyID>2));
	else if((text_ptr==10)&&(Text[9]=='2')&&(KeyID>3)); 
	else if((text_ptr==12)&&(KeyID>5));
	else if((text_ptr==15)&&(KeyID>5));
	else
	{
	  if((Text[3]=='1')&&(Text[4]>'2')) Text[4]='0';
	  if((Text[6]=='3')&&(Text[7]>'1')) Text[7]='0';
	  if((Text[9]=='2')&&(Text[10]>'3')) Text[10]='0';
	  if(text_ptr<16) text_ptr++;
	  else text_ptr=0;
	  if((text_ptr==2)||(text_ptr==5)||(text_ptr==8)||(text_ptr==11)||(text_ptr==14)) text_ptr++;
	  Text[18]=Text[text_ptr];
	  print_texts(335,156,0,0xD1,2,0x04bb,0xffff,Text);
      print_texts(335+text_ptr*12,156,0,0xD1,2,0xffff,0x04bb,&Text[18]);
	}
  }
  else if(KeyID==11)
  {
    DisWelcome();
	DisPage=0;
  }
  else if(KeyID==12)
  {
    DisWelcome();
	DisPage=WELCOMEPAGE;
  }
}
void SoundKeyDown(void)
{
  if(DisPage!=SOUNDPAGE) return;
  KeyID=GetKeyID(Sound_Key,3); 
  if(KeyID==0)
  {
    
  }
  else if(KeyID==1)
  {
    SoundSet=0;
    //EEPROMWriteBytes(SoundSetAddr,&SoundSet,1);
    cut_pic(0,14,0,331,179,531,300,200);
	//cut_pic(0,13,669,402+(SoundSet>0)*50,699,450+(SoundSet>0)*50,669,552);
  }
  else if(KeyID==2)
  {
    cut_pic(0,14,181,331,360,531,300,200);
	cut_pic(0,14,1,371,170,371+(Touch_Y-240)/15*15,301,240);
	//cut_pic(0,13,669,402+(SoundSet>0)*50,699,450+(SoundSet>0)*50,669,552);
	SoundSet=10-(Touch_Y-240)/15;
    //EEPROMWriteBytes(SoundSetAddr,&SoundSet,1);
  }
}
void SoundKeyUP(void)
{
 if(DisPage!=SOUNDPAGE) return; 
 if(KeyID==0)
  {
    DisWelcome();
	DisPage=WELCOMEPAGE;
  }
}
void LanguageKeyDown(void)
{
 if(DisPage!=LANGUAGEPAGE) return;
 KeyID=GetKeyID(Language_Key,17); 
 if(KeyID<16)
 {
   Language=KeyID;
   cut_pic(0,15,0,0,374,400,300,100);
   cut_pic(0,15,Language_Key[KeyID].XS+75,Language_Key[KeyID].YS-100,Language_Key[KeyID].XE+75,Language_Key[KeyID].YE-100,Language_Key[KeyID].XS,Language_Key[KeyID].YS);
 }
 else if(KeyID==16)
 {

 }
}
void LanguageKeyUp(void)
{
 if(DisPage!=LANGUAGEPAGE) return;
 if(KeyID==16)
 {
   //EEPROMWriteBytes(LanguageAddr,&Language,1);
  // DisWelcome();
   DisPage=WELCOMEPAGE;
 }
}
void BackKeyDown(void)
{
 if(DisPage!=BACKPAGE) return;
 KeyID=GetKeyID(Back_Key,4); 
 if((KeyID==0)&&(BackSet>0)) 
 {
   BackSet--;
   cut_pic(0,16+BackSet/6,(BackSet%3)*241,(BackSet%6/3)*270,(BackSet%3)*241+239,(BackSet%6/3)*270+269,300,200);
 } 
 else if((KeyID==1)&&(BackSet<9)) 
 {
   BackSet++;
   cut_pic(0,16+BackSet/6,(BackSet%3)*241,(BackSet%6/3)*270,(BackSet%3)*241+239,(BackSet%6/3)*270+269,300,200);
 } 
}
void BackKeyUp(void)
{
 if(DisPage!=BACKPAGE) return;
 if(KeyID==2)
 {
   //EEPROMWriteBytes(BackSetAddr,&BackSet,1);
   DisWelcome();
   DisPage=WELCOMEPAGE;
 } 
 else if(KeyID==3)
 {
   //EEPROMReadBytes(BackSetAddr,&BackSet,1);
   DisWelcome();
   DisPage=WELCOMEPAGE;
 }  
}
void USBKeyDown(void)
{
 if(DisPage!=USBPAGE) return;
 KeyID=GetKeyID(USB_Key,3); 
 if(KeyID==0)
 {
   cut_pic(0,26,USB_Key[0].XS-300,USB_Key[0].YS+223,USB_Key[0].XE-300,USB_Key[0].YE+223,USB_Key[0].XS,USB_Key[0].YS);
 }
}
void USBKeyUp(void)
{
 if(DisPage!=USBPAGE) return;
 if(KeyID==0)
 {
   cut_pic(0,26,USB_Key[0].XS-300,USB_Key[0].YS+82,USB_Key[0].XE-300,USB_Key[0].YE+82,USB_Key[0].XS,USB_Key[0].YS);
   Up_Pic();
   Delay_MS(1000);
   DisWelcome();
   DisPage=WELCOMEPAGE;
 }
 else if(KeyID==2)
 {
   DisWelcome();
   DisPage=WELCOMEPAGE;
 } 
}
void CardKeyDown(void)
{
 if(DisPage!=CARDPAGE) return;
 KeyID=GetKeyID(Card_Key,16);
 if(KeyID<15)
 {
   cut_pic(0,18,Card_Key[KeyID].XS-29,Card_Key[KeyID].YS-100,Card_Key[KeyID].XE-29,Card_Key[KeyID].YE-100,Card_Key[KeyID].XS,Card_Key[KeyID].YS);
 }
 if((KeyID<10)&&(text_ptr<9))
 {
   Text[text_ptr]=KeyID+'0';
   Text[10]=Text[text_ptr];
   if(text_ptr<3) print_texts(343+text_ptr*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
   else print_texts(482+(text_ptr-4)*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
 }
 else if((KeyID==10)&&(text_ptr<9))
 {
   print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
   print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
   if(text_ptr<3)
   {
    if(text_ptr>0) text_ptr--;
	Text[10]=Text[text_ptr];
	print_texts(343+text_ptr*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
   }
   else
   {
    if(text_ptr>4) text_ptr--;
	Text[10]=Text[text_ptr];
	print_texts(482+(text_ptr-4)*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
   }
 }
 else if(KeyID==11)
 {
   if(text_ptr<3)
   {
     User_ID=(int)(Text[0]-'0')*100+(int)(Text[1]-'0')*10+(int)(Text[2]-'0');
	 //EEPROMWriteBytes(UserIDAddr,&User_ID,1);
	 Card_Data[1]=User_ID;
   }
   else
   {
     User_Counter=(int)(Text[4]-'0')*10000+(int)(Text[5]-'0')*1000+(int)(Text[6]-'0')*100+(int)(Text[7]-'0')*10+(int)(Text[8]-'0');
	 if(User_Type>0)//忱???
     {
       if((User_Type<Card_Type)&&(Card_Type<4)) return;
       Card_Data[0]=User_Type;
       Card_Data[1]=User_ID;
       Card_Data[2]=User_Counter;
       Card_Data[3]=User_Counter>>8;
       Card_Command=2;
     }
     else if((Card_Type>1)&&(Card_Type<4))//忱???
     {
       Card_Data[0]=Card_Type;
       Card_Data[1]=User_ID;
       Card_Data[2]=User_Counter;
       Card_Data[3]=User_Counter>>8;
       Card_Command=1;
     }
   }
   text_ptr=255;
   print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
   print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
 }
 else if(KeyID==12)
 {
   if(Card_Type==3)
   {
     if(text_ptr<2) text_ptr++;
     else text_ptr=0;
     Text[10]=Text[text_ptr];
     print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
     print_texts(343+text_ptr*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
     print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
   }
 }
 else if(KeyID==13)
 {
   if(Card_Type==3)
   {
    if(User_Type<3) User_Type++;
    else User_Type=0;
   }
   else if(Card_Type==2)
   {
    if(User_Type<1) User_Type++;
    else User_Type=0;
   }
   print_consttexts(406,152,0,0xC1,2,0x04bb,0xffff,&user_type[User_Type][0]);
 }
 else if(KeyID==14)
 {
   if(text_ptr<8) text_ptr++;
   else text_ptr=4;
   if(text_ptr<4) text_ptr=4;
   Text[10]=Text[text_ptr];
   print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
   print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
   print_texts(482+(text_ptr-4)*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
 }
}
void CardKeyUp(void)
{
 if(DisPage!=CARDPAGE) return;
 if(KeyID<15)
 {
   cut_pic(0,18,Card_Key[KeyID].XS-300,Card_Key[KeyID].YS-100,Card_Key[KeyID].XE-300,Card_Key[KeyID].YE-100,Card_Key[KeyID].XS,Card_Key[KeyID].YS);
 }
 if((KeyID<10)&&(text_ptr<9))
 {
   print_texts(343,152,0,0xD1,2,0x04bb,0xffff,Text);
   print_texts(482,152,0,0xD1,2,0x04bb,0xffff,&Text[4]);
   if(text_ptr<3)
   {
    if(text_ptr<2) text_ptr++;
    else text_ptr=0;
	Text[10]=Text[text_ptr];
	print_texts(343+text_ptr*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
   }
   else
   {
    if(text_ptr<8) text_ptr++;
    else text_ptr=4;
	Text[10]=Text[text_ptr];
	print_texts(482+(text_ptr-4)*12,152,0,0xD1,2,0xffff,0x04bb,&Text[10]);
   }
 }
 else if(KeyID==15)
 {
   DisWelcome();
   DisPage=WELCOMEPAGE;
 }
}
void PasswordKeyDown(void)
{
  if(DisPage!=PASSWORDPAGE) return;
  KeyID=GetKeyID(Time_Key,13); 
  if((KeyID<10)&&(text_ptr<6))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,&Text[7]);
    Text[text_ptr]=KeyID;
	text_ptr++;
  }
  else if((KeyID==10)&&(text_ptr>0))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
    text_ptr--;
	Text[text_ptr]=0;
	print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,&Text[9]);
  }
  else if((KeyID==11)&&(text_ptr==6))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	if((Text[0]==PasswordTab[0])&&(Text[1]==PasswordTab[1])&&(Text[2]==PasswordTab[2])&&(Text[3]==PasswordTab[3])&&(Text[4]==PasswordTab[4])&&(Text[5]==PasswordTab[5]))
	{
	  text_ptr=8;
	}
	else if((Text[0]==1)&&(Text[1]==1)&&(Text[2]==1)&&(Text[3]==0)&&(Text[4]==0)&&(Text[5]==1))
	{
	  PasswordTab[0]=1;
	  PasswordTab[1]=2;
	  PasswordTab[2]=0;
	  PasswordTab[3]=1;
	  PasswordTab[4]=0;
	  PasswordTab[5]=1;
	  text_ptr=0;
	  Text[0]=' ';
	  Text[1]=' ';
	  Text[2]=' ';
	  Text[3]=' ';
	  Text[4]=' ';
	  Text[5]=' ';
	  print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,Text);
	}
	else
    {
	  text_ptr=0;
	  Text[0]=' ';
	  Text[1]=' ';
	  Text[2]=' ';
	  Text[3]=' ';
	  Text[4]=' ';
	  Text[5]=' ';
	  print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,Text);
	}
  }
  else if(KeyID==12)
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS); 
  }
} 
void PasswordKeyUp(void)
{
  if(DisPage!=PASSWORDPAGE) return;
  if(KeyID<12)
  {
    cut_pic(0,27,0,90,269,325,300,190);
  }
  if((KeyID==11)&&(text_ptr==8))
  {
    clock_off();
	dis_pic(19);
	DisVer();
	DisPage=SYSTEMPAGE;
  }
  else if(KeyID==12)
  {
    DisWelcome();
    DisPage=WELCOMEPAGE;
  } 
}   
void SystemKeyDown(void)
{
 unsigned char i;
 if(DisPage!=SYSTEMPAGE) return;
 KeyID=GetKeyID(System_Key,10);
 if(KeyID==0)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,21,0,0,269,299,300,100);
//   EEPROMReadBytes(CounterAddr+0,&Total_counter,4);
//   LtoA(Total_counter,Text);
//   print_texts(340,180,0,0xD1,2,0x04bb,0xffff,Text);

	//EEPROMReadBytes(CounterAddr+hand[Intensity[8]]*4,&Total_counter,4);
    LtoA(Total_counter,Text);
    print_texts(340,260,0,0xD1,2,0x04bb,0xffff,Text);
	
//   EEPROMReadBytes(CounterAddr+8,&Total_counter,4);
//   LtoA(Total_counter,Text);
//   print_texts(340,340,0,0xD1,2,0x04bb,0xffff,Text);
   DisPage=WORKTIMEPAGE;
 }
 else if(KeyID==1)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,22,0,0,399,449,300,80);
   for(i=0;i<4;i++)
   {
    cut_pic(0,22,Option_Key[i].XS+Function_Buf[i]*400-300,Option_Key[i].YS-80,Option_Key[i].XE+Function_Buf[i]*400-300,Option_Key[i].YE-80,Option_Key[i].XS,Option_Key[i].YS);
   }
   DisPage=OPTIONPAGE;
 }
 else if(KeyID==2)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,21,0,300,269,460,300,200);

    cut_pic(0,21,18+(WorktimeSet*272),372,95+(WorktimeSet*271),423,318,272);
    cut_pic(0,21,96+(PressureSet*272),372,172+(PressureSet*271),423,396,272);	
    cut_pic(0,21,173+(ClockSet*272),372,249+(ClockSet*271),423,473,272);			  
   DisPage=PARASPAGE;
 }
 else if(KeyID==4)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,24,0,0,269,139,300,200);
   if(VerSet == TRUE)
   cut_pic(0,24,290,40,539,139,320,240);
   else
   cut_pic(0,24,20,40,269,139,320,240);
   DisPage=VERSIONPAGE;
 }
 else if(KeyID==5)
 {
   DisPage=PARMPAGE;
 }
 else if(KeyID==6)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,18,0,372,269,512,300,200);
   cut_pic(0,18,CardSet*271,422,269+CardSet*271,512,300,250);
   DisPage=ICCARDPAGE;
 }
 else if(KeyID==7)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,26,0,0,269,139,300,200);
   DisPage=RESETPAGE;
 }
 else if(KeyID==8)
 {
   cut_pic(0,20,System_Key[KeyID].XS,System_Key[KeyID].YS,System_Key[KeyID].XE,System_Key[KeyID].YE,System_Key[KeyID].XS,System_Key[KeyID].YS);
   cut_pic(0,27,0,0,269,325,300,100);
   text_ptr=0;
   Text[0]=' ';
   Text[1]=' ';
   Text[2]=' ';
   Text[3]=' ';
   Text[4]=' ';
   Text[5]=' ';
   Text[6]='\0';
   Text[7]='*';
   Text[8]='\0';
   Text[9]=' ';
   Text[10]='\0';
   Text[11]=0;
   DisPage=PASSSETPAGE;
 }
}
void SystemKeyUp(void)
{
 if(DisPage!=SYSTEMPAGE) return;
 if(KeyID==9)
 {
   DisWelcome();
   DisPage=WELCOMEPAGE;
 }
}
void ClearCountKeyDown(void)
{
  if(DisPage!=WORKTIMEPAGE) return;
  KeyID=GetKeyID(Count_Key,2); 
  if(KeyID<1)
  {   
	cut_pic(0,21,Count_Key[KeyID].XS-28,Count_Key[KeyID].YS-100,Count_Key[KeyID].XE-28,Count_Key[KeyID].YE-100,Count_Key[KeyID].XS,Count_Key[KeyID].YS);
    Total_counter=0;
    if(CardSet==0) Work_counter=0;
	//EEPROMWriteBytes(CounterAddr+hand[Intensity[8]]*4,&Total_counter,4);
    LtoA(Total_counter,Text);
    print_texts(340,180+KeyID*80+80,0,0xD1,2,0x04bb,0xffff,Text);
  }
}
void ClearCountKeyUp(void)
{
  if(DisPage!=WORKTIMEPAGE) return; 
  if(KeyID<1)
  {
    cut_pic(0,21,Count_Key[KeyID].XS-300,Count_Key[KeyID].YS-100,Count_Key[KeyID].XE-300,Count_Key[KeyID].YE-100,Count_Key[KeyID].XS,Count_Key[KeyID].YS);
  }
  else if(KeyID==1)
  {
    dis_pic(19);
	DisPage=SYSTEMPAGE;
  }
}
void ParmKeyDown(void)
{

}
void ParmKeyUp(void)
{
 if(DisPage!=PARMPAGE) return;
 if(KeyID<13)//????完??
 {
   cut_pic(0,25,Card_Key[KeyID].XS-300,Card_Key[KeyID].YS-100,Card_Key[KeyID].XE-300,Card_Key[KeyID].YE-100,Card_Key[KeyID].XS,Card_Key[KeyID].YS);
 }
 else if((KeyID<10)&&(text_ptr<3))
 {
   print_texts(333,154,0,0xD1,2,0x04bb,0xffff,Text);
   if(text_ptr<2) text_ptr++;
   else text_ptr=0;
   Text[4]=Text[text_ptr];
   print_texts(333+text_ptr*12,154,0,0xD1,2,0xffff,0x04bb,&Text[4]);
 }
 else if(KeyID==15)
 {
   dis_pic(19);
   DisPage=SYSTEMPAGE;
 }
}
void OptionKeyDown(void)
{
  if(DisPage!=OPTIONPAGE) return;
  KeyID=GetKeyID(Option_Key,5); 
  if(KeyID<4)
  {
    Function_Buf[KeyID]=1-Function_Buf[KeyID];
	cut_pic(0,22,Option_Key[KeyID].XS+Function_Buf[KeyID]*400-300,Option_Key[KeyID].YS-80,Option_Key[KeyID].XE+Function_Buf[KeyID]*400-300,Option_Key[KeyID].YE-80,Option_Key[KeyID].XS,Option_Key[KeyID].YS);
  }
}
void OptionKeyUp(void)
{
  unsigned char i;
  if(DisPage!=OPTIONPAGE) return;
  if(KeyID==4)
  {
    //EEPROMWriteBytes(FunctionAddr,Function_Buf,9);
	Function_Count=0;
	for(i=0;i<4;i++)
    {
     if(Function_Buf[i]==TRUE)
     {
       Function_Tab[Function_Count]=i;
	   Function_Count++;
     }
    }
	dis_pic(19);
	DisPage=SYSTEMPAGE;
  }
}
void CardSetKeyDown(void)
{
  if(DisPage!=ICCARDPAGE) return;
  KeyID=GetKeyID(CardSet_Key,3); 
  if(KeyID<2)
  {
    CardSet=KeyID;
	cut_pic(0,18,CardSet*271,422,269+CardSet*271,512,300,250);
  }
}
void CardSetKeyUp(void)
{
  if(DisPage!=ICCARDPAGE) return;
  if(KeyID==2)
  {
    //EEPROMWriteBytes(CardSetAddr,&CardSet,1);
    dis_pic(19);
    DisPage=SYSTEMPAGE;
  }
}
void PassSetKeyDown(void)
{
  if(DisPage!=PASSSETPAGE) return;
  KeyID=GetKeyID(Time_Key,13); 
  if((KeyID<10)&&(text_ptr<6))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,&Text[7]);
    Text[text_ptr]=KeyID;
	text_ptr++;
  }
  else if((KeyID==10)&&(text_ptr>0))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
    text_ptr--;
	Text[text_ptr]=0;
	print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,&Text[9]);
  }
  else if((KeyID==11)&&(text_ptr==6))
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS);
	if(Text[11]==0)
	{
	  PasswordTab[0]=Text[0];
	  PasswordTab[1]=Text[1];
	  PasswordTab[2]=Text[2];
	  PasswordTab[3]=Text[3];
	  PasswordTab[4]=Text[4];
	  PasswordTab[5]=Text[5];
	  text_ptr=0;
	  Text[0]=' ';
	  Text[1]=' ';
	  Text[2]=' ';
	  Text[3]=' ';
	  Text[4]=' ';
	  Text[5]=' ';
	  Text[11]=1;
	  print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,Text);
	}
	else
	{
	  if((Text[0]==PasswordTab[0])&&(Text[1]==PasswordTab[1])&&(Text[2]==PasswordTab[2])&&(Text[3]==PasswordTab[3])&&(Text[4]==PasswordTab[4])&&(Text[5]==PasswordTab[5]))
	  {
	    //EEPROMWriteBytes(PasswordAddr,&PasswordTab,6);
		  text_ptr=0;
	    Text[0]='O';
	    Text[1]='K';
	    Text[2]='.';
	    Text[3]='.';
	    Text[4]='.';
	    Text[5]='.';   
	    print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,Text);
	  }
	  else
	  {
	    //EEPROMReadBytes(PasswordAddr,&PasswordTab,6);
		text_ptr=0;
	    Text[0]='E';
	    Text[1]='r';
	    Text[2]='r';
	    Text[3]='o';
	    Text[4]='r';
	    Text[5]='!';
	    print_texts(335+text_ptr*12,150,0,0xD1,2,0x04bb,0xffff,Text);
	  }
	  Text[11]=2;
	}
  }
  else if(KeyID==12)
  {
    cut_pic(0,27,Time_Key[KeyID].XS-29,Time_Key[KeyID].YS-100,Time_Key[KeyID].XE-29,Time_Key[KeyID].YE-100,Time_Key[KeyID].XS,Time_Key[KeyID].YS); 
  }
} 
void PassSetKeyUp(void)
{
  if(DisPage!=PASSSETPAGE) return;
  if(KeyID<12)
  {
    cut_pic(0,27,0,90,269,325,300,190);
  }
  if((KeyID==11)&&(Text[11]==2))
  {
    dis_pic(19);
	DisPage=SYSTEMPAGE;
  }
  else if(KeyID==12)
  {
    dis_pic(19);
	DisPage=SYSTEMPAGE;
  } 
} 
void HandpieceKey(void)//2号手柄键值处理 H
{
  unsigned char buff[16];
  static unsigned ID=255;
  static unsigned count=0;
 // if(DisPage!=WORKPAGE) return;
  if (MACHINE_STATE.HANDLE_ID==1) return;
  if (MACHINE_STATE.HANDLE_ID==0) return;
  if (MACHINE_STATE.HANDLE_ID>4)  return;
  
  if(Hand_Event==KEY_NULL)
  {
    if((PIND&0x10)==0) HandID=1;
    else if((PIND&0x20)==0)  HandID=3;
    else if((PIND&0x40)==0)  HandID=4;
    else if((PIND&0x80)==0)  HandID=2;
    else if((PING&0x01)==0)  HandID=0;
    else HandID=255;
	if(ID!=HandID)
	{
	  ID=HandID;
	  count=0;
	  return;
	}
  if(HandID<5) count++;
	else count=0;
	if(count>=5)
	{
	  count=0;
	  Hand_Event=KEY_DOWN;
	}
  }
  else if(Hand_Event==KEY_DOWN)
  {
	if(HandID<4)
    {
      Intensity[7]=HandID;
      ModeSet();
    if(MACHINE_STATE.WORK_STATE==1)
	  {
	    if(Intensity[8]==2)  BitClr(PORTG,4);//手柄工作指示灯
	    if(Intensity[8]==3)  BitClr(PORTG,3);//手柄工作指示灯
	  }
	  else
	  {
	    BitSet(PORTG,4);
	    BitSet(PORTG,3);
	  }
      buff[0] = MACHINE_STATE.HANDLE_ID-1;
      buff[1] = Intensity[4];//负压等级
      buff[2] = Intensity[5];//吸气等级
      buff[3] = Intensity[6];//放气等级
      buff[4] = Intensity[2] ;//RF等级
      buff[5] = Intensity[0];//LED等级
      buff[6] = Intensity[1];//红外等级
      buff[7] = Intensity[3];//电机转速等级
      buff[8] = Intensity[7];//电机转向

      DwinWriteLongWords(ADDR_HANDPARAMETER_TO_ANDROID,buff,9);//迪文屏通信函数
	    //cut_pic(0,28+Intensity[7],523,388,588,788,523,388);
    }
	else if(HandID==4)
	{
      MACHINE_STATE.WORK_STATE=1-MACHINE_STATE.WORK_STATE;
      buff[0] = MACHINE_STATE.HANDLE_ID-1;
      buff[1] = MACHINE_STATE.WORK_STATE;
      DwinWriteLongWords(ADDR_HANDWORK_TO_ANDROID, buff, 2); //反馈给安卓端
	  if(MACHINE_STATE.WORK_STATE==1)
	  {
	    if(Intensity[8]==2)  BitClr(PORTG,4);//手柄工作指示灯
	    if(Intensity[8]==3)  BitClr(PORTG,3);//手柄工作指示灯
	  }
	  else
	  {
	    BitSet(PORTG,4);
	    BitSet(PORTG,3);
	  }
	  //cut_pic(0,28+Work,Work_Key[18].XS,Work_Key[18].YS,Work_Key[18].XE,Work_Key[18].YE,Work_Key[18].XS,Work_Key[18].YS);
  }
	if((PIND&0x10)==0) HandID=1;
    else if((PIND&0x20)==0)  HandID=3;
    else if((PIND&0x40)==0)  HandID=4;
    else if((PIND&0x80)==0)  HandID=2;
    else if((PING&0x01)==0)  HandID=0;
    else HandID=255;
    if(HandID>5) 
	{
	  Hand_Event=KEY_NULL;
	  return;
	}
    Hand_Event=KEY_KEEP;
  }
  else if(Hand_Event==KEY_KEEP)
  {
    if((PIND&0x10)==0) HandID=1;
    else if((PIND&0x20)==0)  HandID=3;
    else if((PIND&0x40)==0)  HandID=4;
    else if((PIND&0x80)==0)  HandID=2;
    else if((PING&0x01)==0)  HandID=0;
    else HandID=255;
    if(HandID>5) Hand_Event=KEY_UP;
  }
  else if(Hand_Event==KEY_UP)
  {
    if((PIND&0x10)==0) HandID=1;
    else if((PIND&0x20)==0)  HandID=3;
    else if((PIND&0x40)==0)  HandID=4;
    else if((PIND&0x80)==0)  HandID=2;
    else if((PING&0x01)==0)  HandID=0;
    else HandID=255;
    if(HandID<5) 
	{
	  Hand_Event=KEY_KEEP;
	  return;
	}
    Hand_Event=KEY_NULL;
	HandID=255;
  }
}
void WorkKeyDown(void)
{
  /*
  unsigned int i;
  if(DisPage!=WORKPAGE) return;
  KeyID=GetKeyID(Work_Key,19); 
  if(KeyID<7)
  {
    if((KeyID==0)&&(Intensity[8]==3));
	else if((KeyID==1)&&(Intensity[8]>0));
	else if((KeyID==3)&&(Intensity[8]>1));
	else
	{
     i=Touch_Y;
     Intensity[KeyID]=(315-i)/20;
	 DisIntensity(KeyID);
     IntensitySet();
	 Touch_Event=TOUCH_UP;
	}
  }
  else if((KeyID>=7)&&(KeyID<=10)&&(Work==0))
  {
    Intensity[8]=KeyID-7;
	for(i=0;i<7;i++)
    {
      Intensity[i]=Intensity_Tab[Intensity[8]][i];
      DisIntensity(i);
    }
	  //EEPROMReadBytes(CounterAddr+hand[Intensity[8]]*4,&Total_counter,4);
    HandpieceSet();
	  IntensitySet();
    ModeSet();
  }
  else if((KeyID>=11)&&(KeyID<=14))
  {
    Intensity[7]=KeyID-11;
    ModeSet();
	cut_pic(0,28+Intensity[7],523,388,588,788,523,388);
  }
  else if((KeyID==15)&&(Work==0))
  {
	cut_pic(0,29,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
	//EEPROMWriteBytes(IntensityAddr+Function_Tab[Function_Ptr]*9,Intensity,9);
  }
  else if((KeyID==16)&&(Work==0))
  {
	cut_pic(0,29,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
    for(i=0;i<9;i++)
    {
      Intensity[i]=Intensity_Tab[Function_Tab[Function_Ptr]][i];
      if(i<7) DisIntensity(i);
    }
    HandpieceSet();
    cut_pic(0,28+Intensity[7],523,388,588,788,523,388);
    //EEPROMWriteBytes(IntensityAddr+Function_Tab[Function_Ptr]*9,Intensity,9);
  }
  else if((KeyID==17)&&(Work==0))
  {
	cut_pic(0,29,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
	for(i=0;i<9;i++) Intensity[i]=0;
  }
  else if(KeyID==18)
  {
   // Work=1-Work;
	if(Work==1)
	  {
	    if(Intensity[8]==2)  BitClr(PORTG,4);
	    if(Intensity[8]==3)  BitClr(PORTG,3);
	  }
	  else
	  {
	    BitSet(PORTG,4);
	    BitSet(PORTG,3);
	  }
	cut_pic(0,28+Work,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
  }*/
}
void WorkKeyUp(void)
{
  if(DisPage!=WORKPAGE) return;
  if((KeyID==15)&&(Work==0)) cut_pic(0,28,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
  else if((KeyID==16)&&(Work==0)) cut_pic(0,28,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
  else if((KeyID==17)&&(Work==0))
  {
	cut_pic(0,28,Work_Key[KeyID].XS,Work_Key[KeyID].YS,Work_Key[KeyID].XE,Work_Key[KeyID].YE,Work_Key[KeyID].XS,Work_Key[KeyID].YS);
	DisWelcome();
    DisPage=WELCOMEPAGE;
	Send_Data8();
  }
  if(KeyID<7)
  {
    Menu=KeyID;
    Send_Data();
  }
  else if((KeyID>=7)&&(KeyID<=10)&&(Work==0))
  {
   Send_Data8();
  }
  else if((KeyID>=11)&&(KeyID<=14))
  {
   Menu=7;
   Send_Data();
  }
  else if((KeyID==16)&&(Work==0))
  {
   Send_Data8();
  }
  else if(KeyID==18)
  {
   Send_command();
  }

}

void ULKeyDown(void)
{
  if(DisPage!=ultrasonicpage) return;
  KeyID=GetKeyID(UL_Key,4); 
  if((KeyID==0)&&(UL_workdate==0))
  {
    cut_pic(1,109,420,110,480,168,420,110);if(POWER_LEVEL<5){POWER_LEVEL++;}
    switch(POWER_LEVEL)//??????????
     {
     case 0:  cut_pic(1,109,0,510,60,599,420,170); break;
     case 1:  cut_pic(1,109,60,510,120,599,420,170); break;
     case 2:  cut_pic(1,109,120,510,180,599,420,170); break;
     case 3:  cut_pic(1,109,180,510,240,599,420,170);  break;
     case 4:  cut_pic(1,109,240,510,300,599,420,170);  break;
     case 5:  cut_pic(1,109,300,510,358,599,420,170);  break;
     default: break;
     }
  }
  else if((KeyID==1)&&(UL_workdate==0))
  {
    cut_pic(1,109,420,260,480,320,420,260);if(POWER_LEVEL>0){POWER_LEVEL--;}
    switch(POWER_LEVEL)
     {
     case 0:  cut_pic(1,109,0,510,60,599,420,170); break;
     case 1:  cut_pic(1,109,60,510,120,599,420,170); break;
     case 2:  cut_pic(1,109,120,510,180,599,420,170); break;
     case 3:  cut_pic(1,109,180,510,240,599,420,170);  break;
     case 4:  cut_pic(1,109,240,510,300,599,420,170);  break;
     case 5:  cut_pic(1,109,300,510,358,599,420,170);  break;
     default: break;
     }
  } 
  else if(KeyID==2){cut_pic(1,109,720,560,780,600,720,560);} //?????????完??
  else if(KeyID==3)//??????
  {
    UL_workdate=1-UL_workdate;
    if(UL_workdate==1){cut_pic(1,109,420,400,480,460,420,400);}
    else{cut_pic(1,108,420,400,480,460,420,400);}
  }

}

void ULKeyUP(void)
{
  if(DisPage!=ultrasonicpage) return;
  if(KeyID==0){cut_pic(1,108,420,110,480,168,420,110);}
  else if(KeyID==1){cut_pic(1,108,420,260,480,320,420,260);} 
  else if((KeyID==2)&&(UL_workdate==0))//???????
  {
	cut_pic(1,108,720,560,780,600,720,560);
	DisWelcome();
  DisPage=WELCOMEPAGE;
	Send_Data8();
  }
  else if(KeyID==3)//??????
  {   
	 if(UL_workdate==1)
	  {
     switch(POWER_LEVEL)
     {
     case 0:  POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
     case 1:  POWER1_ON;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
     case 2:  POWER1_OFF;POWER2_ON;POWER3_OFF;POWER4_OFF;POWER5_OFF; break;
     case 3:  POWER1_OFF;POWER2_OFF;POWER3_ON;POWER4_OFF;POWER5_OFF;  break;
     case 4:  POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_ON;POWER5_OFF;  break;
     case 5:  POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_ON;  break;
     default: break;
     }
	  }
	  else
	  {
     POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;POWER5_OFF;
	  }
  }
}

void ParasKeyDown(void)
{
  if(DisPage!=PARASPAGE) return;
  KeyID=GetKeyID(Paras_Key,4); 
  switch(KeyID)
  {
   case 0:
    WorktimeSet = 1-WorktimeSet;
    cut_pic(0,21,18+(WorktimeSet*272),372,95+(WorktimeSet*272),423,318,272);
   break;
   case 1:
    PressureSet = 1-PressureSet;
    cut_pic(0,21,96+(PressureSet*272),372,172+(PressureSet*272),423,396,272);	  
   break;
   case 2:
    ClockSet = 1-ClockSet;
    cut_pic(0,21,173+(ClockSet*272),372,249+(ClockSet*272),423,473,272);	
   break;
   default :break;
  }
}
void ParasKeyUp(void)
{
  if(DisPage!=PARASPAGE) return;
  if(KeyID==3)
  {
    //EEPROMWriteBytes(PressureAddr,&PressureSet,1);
	  //EEPROMWriteBytes(ClockSetAddr,&ClockSet,1);
	  //EEPROMWriteBytes(WorktimeAddr,&WorktimeSet,1);
    dis_pic(19);
    DisPage=SYSTEMPAGE;
  }
}
void VersionKeyDown(void)
{
  if(DisPage!=VERSIONPAGE) return;
  KeyID=GetKeyID(VerSet_Key,3); 
  if(KeyID<2)
  {
    VerSet=KeyID;
   if(VerSet == TRUE)
   cut_pic(0,24,290,40,539,139,320,240);
   else
   cut_pic(0,24,20,40,269,139,320,240);
  }
}
void VersionKeyUp(void)
{
  if(DisPage!=VERSIONPAGE) return;
  if(KeyID==2)
  {
    //EEPROMWriteBytes(VerDisAddr,&VerSet,1);
    dis_pic(19);
    DisPage=SYSTEMPAGE;
  }
}
void ResetKeyDown(void)
{
  if(DisPage!=RESETPAGE) return;
  KeyID=GetKeyID(Reset_Key,3); 
  switch(KeyID)
  {
   case 0:   cut_pic(0,26,25,196,118,257,325,255);
   break;
   case 1:   cut_pic(0,26,155,196,248,257,455,255);
   break;   
   default: break;
  }
}
void ResetKeyUp(void)
{
  unsigned char i;
  if(DisPage!=RESETPAGE) return;
  if(KeyID==1)
  {
    VerSet = TRUE;
	//EEPROMWriteBytes(VerDisAddr,&VerSet,1); 
	
	WorktimeSet = TRUE;
	//EEPROMWriteBytes(WorktimeAddr,&WorktimeSet,1);
	
    PressureSet = TRUE;
	//EEPROMWriteBytes(PressureAddr,&PressureSet,1);

    BackSet=0;
	//EEPROMWriteBytes(BackSetAddr,&BackSet,1);

    SoundSet=10;
	//EEPROMWriteBytes(SoundSetAddr,&SoundSet,1);

    ClockSet=TRUE;
	//EEPROMWriteBytes(ClockSetAddr,&ClockSet,1);

    Language=0;
	//EEPROMWriteBytes(LanguageAddr,&Language,1);

    CardSet=FALSE;
	//EEPROMWriteBytes(CardSetAddr,&CardSet,1);
	for(i=0;i<4;i++)
	{
		Function_Buf[i] = 1;
	}
   // EEPROMWriteBytes(FunctionAddr,Function_Buf,9);
  }
  if(KeyID<3)
  {
    dis_pic(19);
    DisPage=SYSTEMPAGE;
  }
}
void Key(void)
{
  static unsigned int enter_mode_num;
  if((DisPage==WELCOMEPAGE)&&(Function_Count == 0))
  {
	if(enter_mode_num<50)
	{
	  delay_ms(1);
	  enter_mode_num++;	
	}  
	else if(enter_mode_num==50)
	{
	    Function_Ptr=0;
   	  DisPage=WORKPAGE;
   	  DisWork();
      Send_Data8();
	  enter_mode_num = 51;  
	}
  }
  
  if(Touch_Event==TOUCH_NULL)
  {
    if(Touch_Buf==TOUCH_DOWN) 
	{
	  Touch_Event=TOUCH_DOWN;
	}
  }
  if(Touch_Event==TOUCH_DOWN)
  {
    Sound_Count=SoundSet;
    Touch_Event=TOUCH_KEEP;	
	switch(DisPage)
	{
	  case WELCOMEPAGE: MainKeyDown();break;//主界面功能选择
	  case STARTPAGE:   StartKeyDown();break;//主界面设置选项
	  case TIMEPAGE:    TimeKeyDown();break;//时间设置
	  case TOUCHPAGE:   break;
	  case SOUNDPAGE:   SoundKeyDown();break;//声音设置
	  case LANGUAGEPAGE:LanguageKeyDown();break;//语言设置界面
	  case BACKPAGE:    BackKeyDown();break;//背景设置
	  case USBPAGE:     USBKeyDown();break;//
	  case CARDPAGE:    CardKeyDown();break;
	  case PARASPAGE:	ParasKeyDown();break;//气压时间等显示
	  case VERSIONPAGE: VersionKeyDown();break;//脉冲
	  case RESETPAGE:	ResetKeyDown();break;//复位？
	  case PASSWORDPAGE:PasswordKeyDown();break;//密码设置
	  case SYSTEMPAGE:  SystemKeyDown();break;//系统设置
	  case WORKTIMEPAGE:ClearCountKeyDown();break;//清零计数
	  case OPTIONPAGE:  OptionKeyDown();break;//功能选择
	  case PARMPAGE:    ParmKeyDown();break;//能量设置
	  case ICCARDPAGE:  CardSetKeyDown();break;
	  case PASSSETPAGE: PassSetKeyDown();break;//密码设置
	  case WORKPAGE:    WorkKeyDown();break;
    case ultrasonicpage: ULKeyDown();break;//爆脂页
	  default:WorkKeyDown(); break;
	}
  }
  else if(Touch_Event==TOUCH_KEEP)
  {
    if(Touch_Buf==TOUCH_UP) 
	{
	 Touch_Event=TOUCH_UP;
	}
  }
  else if(Touch_Event==TOUCH_UP)
  {
	Touch_Event=TOUCH_NULL;
	switch(DisPage)
	{
	  case WELCOMEPAGE:  MainKeyUp();break;
	  case STARTPAGE:    StartKeyUp();break;
	  case TIMEPAGE:     TimeKeyUp();break;
	  case TOUCHPAGE:    break;
	  case SOUNDPAGE:    SoundKeyUP();break;
	  case LANGUAGEPAGE: LanguageKeyUp();break;
	  case BACKPAGE:     BackKeyUp();break;
	  case USBPAGE:      USBKeyUp();break;
	  case CARDPAGE:     CardKeyUp();break;
	  case OPTIONPAGE:   OptionKeyUp();break;
	  case PARASPAGE:	 ParasKeyUp();break;
	  case VERSIONPAGE:  VersionKeyUp();break;
	  case RESETPAGE:	 ResetKeyUp();break;
	  case PASSWORDPAGE: PasswordKeyUp();break;
	  case SYSTEMPAGE:   SystemKeyUp();break;
	  case WORKTIMEPAGE: ClearCountKeyUp();break;
	  case PARMPAGE:     ParmKeyUp();break;
	  case ICCARDPAGE:   CardSetKeyUp();break;
	  case PASSSETPAGE:  PassSetKeyUp();break;
	  case WORKPAGE:     WorkKeyUp();break;  
    case ultrasonicpage: ULKeyUP();break;               
	  default:WorkKeyUp(); break;
	}
  }
  else Touch_Event=TOUCH_NULL;
  dispose_data();
  //Dis_pressure();
}  
