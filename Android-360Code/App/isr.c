#include "includes.h"
void Delay_MS(unsigned int t)
{
  DelayMs=t;
  while(DelayMs>0);
}
void Delay_10MS(unsigned int t)
{
  Clk=0;
  while(Clk<t);
}
void start_pwm(void)
 {
    timer2_init();
    TCCR2 = 0x72; 
 }	
void stop_pwm(void)
 {
   timer2_init();
   PORTB &=0x7f;
 } 
void out_pulse(void)
{
  TCNT1H = 0x00; 
  TCNT1L = 0x01;
  OCR1C  = 1250; 
  ETIMSK |=0X01;
} 
void sound(void)//???
{
  if(Sound_Count>0)
  {
    Sound_Count--;
	SPK_ON;
  }
  else SPK_OFF;
}
void water_count(void)
{
  static unsigned int w_cnt=0;
  static unsigned int w_bit=0;
  w_cnt++; 
  if(w_cnt>80)
  {
	water=w_buf;
	w_buf=0;
	w_cnt=0;
  }
  if(w_bit!=(PINF&0x04))
  {
    w_bit=PINF&0x04;
	if(w_buf<255) 
	w_buf++;
  }
}
#pragma interrupt_handler timer0_comp_isr:16

void timer0_comp_isr(void)
{
  static unsigned int count=0;
  static unsigned int xf=0;
  TCNT0=0;
  OCR0 = 0x97;
  Clk++;
  sound();
  if(DelayMs>0) DelayMs--;
  //Updata(); 
  if(MACHINE_STATE.WORK_STATE==0) return;
  if(MACHINE_STATE.HANDLE_ID==5)return;

  if((Intensity[5]==0)||(Intensity[6]==0)) XF_OFF; //吸放气 H
  else if(xf==0)
  {
    if(count<Intensity[5]*20) count++;
	else 
	{
	  count=0;
	  xf=1;
	  if((Intensity[5]>0)&&(Intensity[6]>0)) XF_ON; 
	}
  }
  else
  {
    //if(count<Intensity[6]*20) count++;
	if(count<Intensity[6]*10) count++;//20190410改
	else 
	{
	  count=0;
	  xf=0;
	  XF_OFF; 
	}
  }
}


#pragma interrupt_handler timer1_compc_isr:25

void timer1_compc_isr(void)
{

}

//TIMER2 initialize - prescale:64
// WGM: PWM Fast
// desired value: 500Hz
// actual value: 488.281Hz (2.4%)


#pragma interrupt_handler timer2_comp_isr:10
void timer2_comp_isr(void)
{
  /*
  if((Intensity[8]==0)&&(Intensity[2]>0)&&(Work>0))
  {
   OCR2=Intensity[2]*25; 
  }
  else OCR2=0;*/
 OCR2=0;
}
#pragma interrupt_handler timer2_ovf_isr:11
void timer2_ovf_isr(void)
{
  static unsigned char count=0;
  TCNT2 = 0x01;
  //water_count();

  
  if(MACHINE_STATE.WORK_STATE==0)
  {
   BitSet(PORTA,6);
   BitSet(PORTA,7);
   LED2_OFF;
   LD2_OFF;
   RFE_OFF;
   MD_OFF;
   LED3_OFF;
   return;
  }
  if(MACHINE_STATE.HANDLE_ID==5)return;
  BitClr(PORTA,6); //负压真空泵打开 H
  if(Intensity[8]<2) BitClr(PORTA,7);// 没用到 H
  count=(count+1)%50;
  RfPer=SettingDdata.SET_WORKPOWER;
  if(Intensity[8]==0)//1号手柄 射频等级 H
  {
    if((Intensity[2]*5*RfPer/100)>count) RFE_ON;
    else RFE_OFF;
  }
  else if(Intensity[8]==1)//2号手柄 LED 射频  电机转速等级  H
  {
    if(Intensity[0]*5>count) LED2_ON;
    else LED2_OFF;
    if((Intensity[2]*4*RfPer/100)>count) RFE_ON;
    else RFE_OFF;
    if(Intensity[3]*5>count) MD_ON;
    else MD_OFF;
  }
  else if(Intensity[8]==2)//3号手柄  LED 射频等级 H
  {
    if(Intensity[0]*5>count) LED3_ON;
    else LED3_OFF;
    if((Intensity[2]*2*RfPer/100)>count) RFE_ON;
    else RFE_OFF;
  }
  else if(Intensity[8]==3)//4号手柄射频等级  H
  {
    if((Intensity[2]*RfPer/100)>count) RFE_ON;
    else RFE_OFF;
  }
  
}
//TIMER3 initialize - prescale:64
// WGM: 1) PWM 8bit Phz correct, TOP=0x00FF
// desired value: 245Hz
// actual value: 245.098Hz (0.0%)


#pragma interrupt_handler timer3_compc_isr:29
void timer3_compc_isr(void)
{
 //compare occured TCNT3
 OCR3CH = 0xff;
 OCR3CL =255;
 //PORTE &= 0x7F;
}
#pragma interrupt_handler timer3_ovf_isr:30
void timer3_ovf_isr(void)
{
 TCNT3H = 0xFF; //reload counter high value
 TCNT3L = 0x01; //reload counter low value
 //PORTE |=0x80;
}

#pragma interrupt_handler adc_isr:22
void adc_isr(void)
{
   //conversion complete, read value (int) using...
   //i=ADCL;
   //adc_value=i;            //Read 8 low bits first (important)
   //j=ADCH;
   //adc_value|=(int)j << 8; //read 2 high bits and shift into top byte
   //adc_value&=0x3fFF;
   //x=j;
}