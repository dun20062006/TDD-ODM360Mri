unsigned char water=0;
unsigned char Menu=0;
unsigned char MC=0;
unsigned char MV=0;
unsigned char Clk=0;
unsigned char Work=0;
unsigned char HandID=255;//按键键值
unsigned char Hand_Event=0;
unsigned char Foot_Event=0;
unsigned char PasswordTab[6];
unsigned char DisPage=0;
unsigned char KeyID=255;
unsigned char BackSet=0;
unsigned char VerSet=0;
unsigned char WorktimeSet=0;
unsigned char PressureSet=0;
unsigned char Function_Tab[9];
unsigned char Function_Buf[9];
unsigned char Function_Count=0;
unsigned char Function_Ptr=0;
unsigned int  DelayMs=0;
unsigned char Page_ptr=0;
unsigned char SoundSet=0;
unsigned char Sound_Count=0;
unsigned long Total_counter;
unsigned int  Work_counter;
unsigned char ClockSet=0;
unsigned char Language=0;
unsigned char RfPer;

/***HAO*****************************************************/



unsigned char RX1Data[20][30];
unsigned char RX1Counterhead;//
unsigned char RX1Countertail;

unsigned char RX2Data[10][30];
unsigned char RX2Counterhead;//
unsigned char RX2Countertail;

unsigned char passwordInput[8];//输入密码
unsigned char password[8] = {0x31,0x32,0x31,0x33,0x31,0x34,0x31,0x39};//预设密码
unsigned char SNpassword[8] = {0x31,0x32,0x31,0x33,0x31,0x34,0x31,0x39};//SN预设密码
unsigned char SNInput[16];//输入SN
/***HAO****************************************************/

unsigned char Text[50];
unsigned char Text1[20];
unsigned char R_buf[250]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char R_buf1[100]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char T_buf[250]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char R_count=0;
unsigned char R_count1=0;
unsigned char R_Check=0;
unsigned char R_full=0;
unsigned char R_full1=0;
unsigned char T_ptr=0;
unsigned char T_count=0;
unsigned char Event_count=0;
unsigned char CardSet=0;
unsigned char Card_Event=0;
unsigned char Card_Info=0;
unsigned char Card_Command=0;
unsigned char Card_ID=0;
unsigned char User_ID=0;
unsigned char Card_Type=0;
unsigned char User_Type=0;
unsigned int  Card_Counter=0;
unsigned int  User_Counter=0;
unsigned char Card_Data[4]={0,0,0,0};
unsigned char Touch_Event=0;
unsigned char Touch_Buf=0;
unsigned int  Touch_ID=65535;
unsigned int  Touch_X;
unsigned int  Touch_Y;
unsigned int w_buf=0;
//the is Set Page data define
unsigned int SetID=0xffff;
unsigned char text_ptr=0;
unsigned char datetime[7]={0,0,0,0,0,0,0};

unsigned char Intensity[9]={0,0,0,0,0,0,0,0,0};//Intensity[0] LED等级  Intensity[2] RF等级  Intensity[3] 电机转速等级  Intensity[8] 手柄ID Intensity[1] 红外等级？
                                               //Intensity[4] 负压等级  Intensity[5] 吸气时间  Intensity[6] 放气时间  Intensity[7] 电机转向
unsigned char Handpiece=0;
unsigned char Mode=0;

typedef struct KEY
{
  unsigned int  XS;
  unsigned int  YS;
  unsigned int  XE;
  unsigned int  YE;
};
const struct KEY Main_Key[6]=
{
  { 30, 65,130,185},  //HR
  { 30,240,130,360},  //SR
  { 30,415,130,535},  //PR
  {175, 65,275,185},  //VR
  {  0,  0, 60, 50},   //start
  {175,240,275, 360}   //爆脂触摸
};
const struct KEY Start_Key[9]=
{
  {  0, 50,200, 90},  //time
  {  0, 90,200,130},  //touch
  {  0,130,200,170},  //sound
  {  0,170,200,210},  //language
  {  0,210,200,250},  //back set
  {  0,250,200,290},  //usb
  {  0,290,200,330},  //write
  {  0,330,200,370},   //system set
  {  0,  0, 60, 50}  //start
};
const struct KEY Time_Key[13]=
{
  {319,349,394,399},//0
  {319,196,394,246},//1
  {395,196,470,246},//2
  {471,196,546,246},//3 
  {319,247,393,297},//4
  {395,247,470,297},//5
  {471,247,546,297},//6
  {319,298,394,348},//7
  {395,298,470,348},//8
  {471,298,546,348},//9
  {395,349,470,399},//SET
  {471,349,546,399},//OK
  {530,100,570,135} //BLACK
};
const struct KEY Sound_Key[3]=
{
 {440,200,475,235},
 {405,330,460,390},
 {305,240,405,390}
};
const struct KEY Language_Key[17]=
{
  {306,140,396,226},
  {396,140,486,226},
  {486,140,576,226},
  {576,140,666,226},
  
  {306,226,396,312},
  {396,226,486,312},
  {486,226,576,312},
  {576,226,666,312},
  
  {306,312,396,398},
  {396,312,486,398},
  {486,312,576,398},
  {576,312,666,398},
  
  {306,398,396,484},
  {396,398,486,484},
  {486,398,576,484},
  {576,398,666,484},
  
  {630,100,670,135}
};
const struct KEY Back_Key[4]=
{
  {320,408,375,460},
  {390,408,445,460},
  {460,408,515,460},
  {500,200,540,235},
};
const struct KEY USB_Key[3]=
{
  {325,255,435,315},
  {455,255,565,315},
  {520,200,570,235}
};
const struct KEY Card_Key[16]=
{
  {320,400,395,450},//0
  
  {320,247,395,297},//1
  {396,247,471,297},//2
  {472,247,547,297},//3
  
  {320,298,395,348},//4
  {396,298,471,348},//5
  {472,298,547,348},//6
  
  {320,349,395,399},//7
  {396,349,471,399},//8
  {472,349,547,399},//9
  
  
  {395,400,471,450},//*  10
  {472,400,547,450},//OK 11
  
  {320,190,395,240},//CardID   12
  {396,190,471,240},//Type     13
  {472,190,547,240},//Count    14
  
  {530,100,570,135} //BLACK    15
};
const struct KEY System_Key[10]=
{
  {  8, 52,138, 98},//0
  {  8, 98,138,144},//1
  {  8,144,138,190},//2
  {  8,190,138,236},//3
  {  8,236,138,282},//4
  {  8,282,138,328},//5
  {  8,328,138,374},//6
  {  8,374,138,420},//7
  {  8,420,138,466},//8
  {740,  0,799, 45}//9 EXIT
};
const struct KEY Count_Key[2]=
{
  {475,240,550,295},
  {530,100,570,135}
};
const struct KEY Option_Key[5]=
{
  {364,175,474,285},
  {526,175,636,285},
  {364,331,474,441},
  {526,331,636,441},
  {640, 80,700,120} 
};
const struct KEY Handpiece_Key[22]=
{
  {314,166,377,209},
  {378,166,440,209},
  {442,166,504,209},
  {506,166,568,209},
  {570,166,632,209},
  {632,166,696,209},
  {696,166,760,209},
  
  {314,249,377,292},
  {378,249,440,292},
  {442,249,504,292},
  {506,249,568,292},
  {570,249,632,292}, 
  {632,249,696,292},
  {696,249,760,292},
  
  {314,332,377,375},
  {378,332,440,375},
  {442,332,504,375},
  {506,332,568,375},
  {570,332,632,375},
  {632,332,696,375},
  {696,332,760,375},
  
  {730,100,770,135}
};
const struct KEY CardSet_Key[3]=
{
  {325,255,410,315},
  {455,255,540,315},
  {520,200,570,235}
};
const struct KEY VerSet_Key[3]=
{
  {325,255,410,315},
  {455,255,540,315},
  {520,200,570,235}//exit
};
const struct KEY Reset_Key[3]=
{
  {325,255,410,315},
  {455,255,540,315},
  {520,200,570,235}//exit
};
const struct KEY Paras_Key[4]=
{
  {318,272,395,323},
  {396,272,472,323},
  {473,272,549,323},
  {520,200,570,235}//exit
};
const struct KEY Work_Key[19]=
{
  { 40,96,100,315},
  {150,96,210,315},
  {260,96,320,315},
  {370,96,430,315},
  {480,96,540,315},
  {590,96,650,315},
  {700,96,760,315},
  
  {190,394,255,444},
  {190,444,255,494},
  {190,494,255,544},
  {190,544,255,594},
  
  {523,394,588,444},
  {523,444,588,494},
  {523,494,588,544},
  {523,544,588,594},
  
  {592,389,692,489},
  {692,389,792,489},
  {592,489,692,589},
  {692,489,792,589}
};
//?????????
const struct KEY UL_Key[4]=
{
  { 420,110,480,170},
  {420,260,480,320},
  {720,560,780,600},
  {420,400,480,460}
};

const unsigned char Intensity_Tab[4][9]=
{
  //LED LD RF 转速 强度 吸气，放气
  { 2, 2, 2, 2, 2, 2, 2, 0, 0},
  { 2, 0, 2, 2, 2, 2, 2, 0, 1},
  { 2, 0, 2, 0, 2, 2, 2, 0, 2},
  { 0, 0, 2, 0, 2, 2, 2, 0, 3}
};
const unsigned char Intensity_Max[9]={10,10,10,10,10,10,10, 3, 3};
const unsigned char hand[4]={0,1,2,2};