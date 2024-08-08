
#include "includes.h"
//const unsigned char Ver[]={"MCU Ver:MED360.1.6.150616\0"};
//const unsigned char Ver[]={"MCU Ver:MED360.1.8.180329\0"};
//const unsigned char Ver[]={"MCU Ver:MED360.1.9.180510\0"};//增加后台射频百分比调节
  const unsigned char Ver[]={"DIWEN 1.0"};//迪文软件版本
  const unsigned char HARDVer[]={"FUYA MAN-1"};//硬件版本
  const unsigned char HEXVer[]={"MED360.2.1"};//软件版本

//1.后台增加工作累计时间清零功能
//2.后台增加取消所有工作模式，延时自动进入界面功能
//3.后台增加paras display功能，开启关闭压力、时间和累计工作时间显示
//4.后台增加version显示功能
//5.后台增加出厂复位功能
// by hanjingyang 20170920
//const unsigned char Ver[]={"System version v2.2.10.111001_beta\0"};

char lcd_ver[4]={0};

void uart0_init(void)
{
 UCSR0B = 0x00; 	 	   		 	  		 				//disable while setting baud rate
 UCSR0A = 0x00;
 UCSR0C = 0x06;
 UBRR0L = 0x19;  //0x19; //set baud rate lo 38400 (0.2%)
 UBRR0H = 0x00; //set baud rate hi
 UCSR0B = 0xD8;
 //UBRR0L = 0x10; //set baud rate lo 57600(2.1%)
 //UBRR0H = 0x00; //set baud rate hi
 //UCSR0B = 0xD8;
 //UBRR0L = 0x0C; //set baud rate lo 76800 (0.2%)
 //UBRR0H = 0x00; //set baud rate hi
 //UCSR0B = 0x18;
 //UBRR0L = 0x8;  //0x19; //set baud rate lo  115200(3.7%)
 //UBRR0H = 0x00; 				//set baud rate hi
 //UCSR0B = 0xD8;
}
void uart1_init(void)
{
 UCSR1B = 0x00; //disable while setting baud rate
 UCSR1A = 0x00;
 UCSR1C = 0x06;
 UBRR1L = 0x67; //set baud rate lo 9600
 UBRR1H = 0x00; //set baud rate hi
 UCSR1B = 0xD8;
 //UBRR1L = 0x19;  //0x19; //set baud rate lo  38400 (0.2%)
 //UBRR1H = 0x00; //set baud rate hi
 //UCSR1B = 0xD8;
 //UBRR1L = 0x10; //set baud rate lo 57600(2.1%)
 //UBRR1H = 0x00; //set baud rate hi
 //UCSR1B = 0xD8;
 //UBRR1L = 0x0C; //set baud rate lo 76800(0.2%)
 //UBRR1H = 0x00; //set baud rate hi
 //UCSR1B = 0x18;
 //UBRR1L = 0x08; //set baud rate lo 115200(3.7%)
 //UBRR1H = 0x00; //set baud rate hi
 //UCSR1B = 0xD8;
}
void timer0_init(void)
{
  TCCR0 = 0x00; //stop
  ASSR  = 0x00; //set async mode
  TCNT0 = 0x00; //set count
  OCR0  = 0x9C;
  TCCR0 = 0x07; //start timer
}
void timer1_init(void)
{
  TCCR1B = 0x00; //stop
  TCNT1H = 0xFB; //setup
  TCNT1L = 0x1E;
  OCR1AH = 0x04;
  OCR1AL = 0xE2;
  OCR1BH = 0x04;
  OCR1BL = 0xE2;
  OCR1CH = 0x04;
  OCR1CL = 0xE2;
  ICR1H  = 0x04;
  ICR1L  = 0xE2;
  TCCR1A = 0x00;
  TCCR1B = 0x03; //start Timer
}
void adc_init(void)
{
 ADCSRA = 0x00;   //disable adc
 ADMUX=0xe0;
 ACSR   = 0x80;
 ADCSRA = 0x87;
}
//TIMER2 initialize - prescale:64
// WGM: PWM Fast
// desired value: 500Hz
// actual value: 488.281Hz (2.4%)
void timer2_init(void)
{
 TCCR2 = 0x00;     //stop
 TCNT2 = 0x01;       //setup01
 OCR2  = 0xFF;

 //TCCR2 = 0x79; 
}
//TIMER3 initialize - prescale:64
// WGM: 1) PWM 8bit Phz correct, TOP=0x00FF
// desired value: 245Hz
// actual value: 245.098Hz (0.0%)
void timer3_init(void)
{
 TCCR3B = 0x00; //stop
 TCNT3H = 0xFF; //setup
 TCNT3L = 0x01;
 OCR3AH = 0x00;
 OCR3AL = 0xFF;
 OCR3BH = 0x00;
 OCR3BL = 0xFF;
 OCR3CH = 0x00;
 OCR3CL = 0xFF;
 ICR3H  = 0x00;
 ICR3L  = 0xFF;
 TCCR3A = 0x01;
 TCCR3B = 0x0D; //start Timer
}
void port_init(void)
{
 PORTA = 0xFF;
 DDRA  = 0xFF;
 PORTB = 0xFF;
 DDRB  = 0xFF;
 PORTC = 0xFF;   
 DDRC  = 0xFF;
 PORTD = 0xFF;
 DDRD  = 0x0F;
 PORTE = 0xFF;
 DDRE  = 0xFF;
 PORTF = 0xFF;
 DDRF  = 0xF0;
 PORTG = 0xFF;
 DDRG  = 0xFE;
 RXD;
}
//call this routine to initialize all peripherals
void init_devices(void)
{   
 CLI(); 
 XDIV  = 0x00;                              		  //xtal divider
 XMCRA = 0x00;                                  	  //external memory
 XMCRB = 0x00;
 port_init();       
 adc_init();                               			  //uart0_init();
 uart0_init();
 uart1_init();
 timer0_init();
 timer1_init();
 timer2_init();
 timer3_init();
 MCUCR = 0x00;
 EICRA = 0x00;                                  	  //extended ext ints
 EICRB = 0x00;                                  	  //extended ext ints
 EIMSK = 0x00;
 TIMSK = 0xc2;                                        //timer interrupt sources
// cool_time =25;
 ETIMSK = 0x06;   
 start_pwm();                                    //extended timer interrupt sources       
 SEI();          									  //re-enable interrupts
}
void cartoon(void)
{
  static unsigned char x=0;
  x=(x+1)%32;
  //cut_pic(0,x,300,170,500,530,300,170);
  dis_pic(x);
  Sound_Count=5;
}
void DisVer(void)
{
	Text[0]='L';
	Text[1]='C';
	Text[2]='D';
	Text[3]=' ';
	Text[4]='V';
	Text[5]='e';
	Text[6]='r';
	Text[7]=':';
	Text[8]=lcd_ver[0];
  Text[9]=lcd_ver[1];
	Text[10]=lcd_ver[2];
	Text[11]=lcd_ver[3];
	Text[12]='\0';
  print_texts(0,550,0,0x81,2,0xf800,0xffff,Text);
  print_consttexts(0,570,0,0x81,2,0xf800,0xffff,Ver); 
}
void init_system(void)
{
  unsigned long t;
  unsigned char i;

  CLI();//关闭中断？
  init_devices();//用到的外设初始化
  SEI(); //使能中断
  DwinWriteWord(ADDR_BOOTINGBAR, 1);//迪文屏通信函数
  POWER5_OFF;
  POWER1_OFF;POWER2_OFF;POWER3_OFF;POWER4_OFF;
  EEPROMReadBytes(SoundSetAddr,&SoundSet,1);
  if(SoundSet>10) 
  {
    SoundSet=10;
	EEPROMWriteBytes(SoundSetAddr,&SoundSet,1);
  }
  for (i = 0; i < sizeof(Ver); i++){SettingDdata.softwareVersion[i] = Ver[i];}
  EEPROMWriteBytes(softwareVersionAddr,&SettingDdata.softwareVersion,16);//迪文软件版本
  for (i = 0; i < sizeof(HARDVer); i++){SettingDdata.hardwareVersion[i] = HARDVer[i];}
  EEPROMWriteBytes(hardwareVersionAddr,&SettingDdata.hardwareVersion,16);//主板硬件版本
  for (i = 0; i < sizeof(HEXVer); i++){SettingDdata.hexVersion[i] = HEXVer[i];}
  EEPROMWriteBytes(hexVersionAddr,&SettingDdata.hexVersion,16);//主板软件版本

  EEPROMReadBytes(snNumberAddr,&SettingDdata.snNumber,16);//SN号

  EEPROMReadBytes(SET_HANDLEFIVEAddr,&SettingDdata.SET_HANDLEFIVE,1);//5号爆脂手柄选择
  if(SettingDdata.SET_HANDLEFIVE>1||SettingDdata.SET_HANDLEFIVE<0)
  {SettingDdata.SET_HANDLEFIVE=0;EEPROMWriteBytes(SET_HANDLEFIVEAddr,&SettingDdata.SET_HANDLEFIVE,1);}
  EEPROMReadBytes(SET_WORKTIMEAddr,&SettingDdata.SET_WORKTIME,1);//治疗时间读取
  EEPROMReadBytes(SET_WORKPOWERAddr,&SettingDdata.SET_WORKPOWER,1);//治疗能量百分比读取
  RfPer=SettingDdata.SET_WORKPOWER;
  if(RfPer>100){RfPer=100;EEPROMWriteBytes(SET_WORKPOWERAddr,&SettingDdata.SET_WORKPOWER,1);}
  if(RfPer<0){RfPer=100;EEPROMWriteBytes(SET_WORKPOWERAddr,&SettingDdata.SET_WORKPOWER,1);}
  
  MACHINE_STATE.WORK_STATE=0;
  MACHINE_STATE.HANDLE_ID=0;
  delay_ms(2200);
  EEPROMReadBytes(SET_HANDLEONEAddr,&SettingDdata.SET_HANDLEONE,1);//1号手柄选择
  if(SettingDdata.SET_HANDLEONE>=1)
  {SettingDdata.SET_HANDLEONE=1;DwinToPage(PAGE_HANDLECHOOSE1); MACHINE_STATE.WORK_PAGE=PAGE_HANDLECHOOSE1;EEPROMWriteBytes(SET_HANDLEONEAddr,&SettingDdata.SET_HANDLEONE,1);}//有一号手柄跳转到0页
  if(SettingDdata.SET_HANDLEONE<0)
  {SettingDdata.SET_HANDLEONE=1;DwinToPage(PAGE_HANDLECHOOSE1); MACHINE_STATE.WORK_PAGE=PAGE_HANDLECHOOSE1;EEPROMWriteBytes(SET_HANDLEONEAddr,&SettingDdata.SET_HANDLEONE,1);}//有一号手柄跳转到0页
  if(SettingDdata.SET_HANDLEONE==0)
  {DwinToPage(PAGE_HANDLECHOOSE4); MACHINE_STATE.WORK_PAGE=PAGE_HANDLECHOOSE4;}//无一号手柄跳转到23页

  start_pwm(); 
  //Init_Task(); 
  //Add_Task(DataSynchronization,1,10,1);//迪文通讯数据同步 485数据同步
  //Add_Task(HandpieceKey,2,1,1); //手柄按键处理
}