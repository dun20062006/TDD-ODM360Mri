#include "includes.h"
#include <iom128v.h>
#include <macros.h>
#include <eeprom.h>
const unsigned char filename[]={"LOGO.BMP\0"};
const unsigned char filename1[]={"L.BMP\0"};
const unsigned char usbtext[]={"USB ERROR\0"};
const unsigned char ERR_USR_COUNNECT[]={"The USB device has disconnected,or not connected.\0"};
const unsigned char ERR_DISK_DISCON[]={"The USB device has disconnected,or not connected.\0"};
const unsigned char ERR_SUCCESS[]={"success\0"};
const unsigned char ERR_STATUS_ERR[]={"Disk status error, may be connecting or disconnect.\0"};
const unsigned char ERR_FAT_ERROR[]={"Disk file system does not support.\0"};
const unsigned char ERR_DISK_FULL[]={"Disk file is too full, the remaining space is too little.\0"};
const unsigned char ERR_MISS_DIR[]={"The home DIR you specified does not exist\0"};
const unsigned char ERR_FILE_CLOSE[]={"File has already closed, if need to use,please open again.\0"};
const unsigned char ERR_OPEN_DIR[]={"The specified path is opened.\0"};
const unsigned char ERR_MISS_FILE[]={"The home DIR you specified does not exist, maybe the wrong file name.\0"};
const unsigned char ERR_USB_DISK_ERR[]={"the USB memory operation failed.\0"};
unsigned char RTX=0;

unsigned char DwinCmd = 0;
unsigned int DwinAddr = 0;
unsigned int DwinData = 0;
unsigned int Dwindata2 = 0;
unsigned char DIWEN_RECEICEDATA_STATE=0;//���յ�������״̬
unsigned char SAVE_FAT_FLAME;//��֬�����ȼ�

#pragma interrupt_handler uart0_rx_isr:19
void uart0_rx_isr(void)
{
   unsigned char i;
   unsigned char len;
   i=UDR0; 
   if(RTX==1) return;
   if(R_full==1)return;//���ջ���������   
   if ((R_count==0)&&(i==0x5A))//�ж�ͷ��5a
    {
      R_buf[0]=i;
	    R_count+=1;
    }
   else if(R_count>0)
    {
      R_buf[R_count]=i;
	    R_count+=1; 
    }
   else
    {
      R_count=0;
	    R_full=0;
    }
   if(R_count>40)//���Ȳ��ܳ���30
   {
    R_count=0;
   }
   if(R_count>5)//�������ݳ���
   {
      len=R_buf[4];
   }
   if(R_count==(len+9))
    {
	   R_full=1;
	   R_count=0;
     len=0;
	  }
   if(R_full==1)//��������
   {
    for(i=0;i<30;i++)
    {RX1Data[RX1Counterhead][i]=R_buf[i];}
   // memcpy(&RX1Data[RX1Counter][0], R_buf, len+3);
    RX1Counterhead++;
    if(RX1Counterhead>20){RX1Counterhead=0;}
    R_full=0;


    /*
    if(DisPage==MVPAGE)
	  {
	  R_full=0;
	  MC=1;
	  return;
	  }
	  MV=0;
    if(R_buf[1]==0x72)
	  {
	  Touch_Buf=TOUCH_UP;
	  Touch_X=R_buf[2];
	  Touch_X<<=8;
	  Touch_X+=R_buf[3];
	  Touch_Y=R_buf[4];
	  Touch_Y<<=8;
	  Touch_Y+=R_buf[5];
	  }
	else if(R_buf[1]==0x73)
	  {
	  Touch_Buf=TOUCH_DOWN;
	  Touch_X=R_buf[2];
	  Touch_X<<=8;
	  Touch_X+=R_buf[3];
	  Touch_Y=R_buf[4];
	  Touch_Y<<=8;
	  Touch_Y+=R_buf[5];
	  }
    else if(R_buf[1]==0x78)
	  {
	  Touch_Buf=TOUCH_UP;
	  Touch_ID=R_buf[2];
	  Touch_ID<<=8;
	  Touch_ID+=R_buf[3];
	  }
	else if(R_buf[1]==0x79)
	  {
	  Touch_Buf=TOUCH_DOWN;
	  Touch_ID=R_buf[2];
	  Touch_ID<<=8;
	  Touch_ID+=R_buf[3];
	  }
	else if((R_buf[1]==0x9B)&&(R_buf[2]==0x5A))//ʱ��
	  {
	  for(i=0;i<7;i++)
	  {
	    datetime[i]=R_buf[i+3];
	  }
	  }
	  R_full=0;
    */
    }
}
#pragma interrupt_handler uart1_rx_isr:31
void uart1_rx_isr(void)
{
  unsigned char i;
  i=UDR1; 
  if(R_full1==1)return;                            //���ջ���������    
  if(R_count1==0)
  {
    if(i==0xaa)
	{
      R_buf1[0]=i;
      R_count1+=1;
	}
  }
  else if(R_count1==1)
  {
    R_buf1[1]=i;
    R_count1+=1; 
  }
  else if(R_count1<R_buf1[1])
  {
    R_buf1[R_count1]=i;
	R_count1+=1; 
  }
  else
  {
    R_full1=0;
	R_count1=0;
  }
  if(R_count1==R_buf1[1])
  {
	R_full1=1;
	R_count1=0;
  }

  if (R_full1==1)
  {
    for(i=0;i<30;i++)
    {RX2Data[RX2Counterhead][i]=R_buf1[i];}
   // memcpy(&RX1Data[RX1Counter][0], R_buf, len+3);
    RX2Counterhead++;
    if(RX2Counterhead>10){RX2Counterhead=0;}
    R_full1=0;
  }

}

//���ڷ����жϳ���
#pragma interrupt_handler uart0_tx_isr:21
void uart0_tx_isr(void)
{
  if(T_ptr<T_count)
   {
     UDR0=T_buf[T_ptr];
     T_ptr++;
   }
  else
  {
    T_count=0;
	T_ptr=0;
  }
}
#pragma interrupt_handler uart1_tx_isr:33
void uart1_tx_isr(void)
{
  if(T_ptr<T_count)
   {
     TXD;
     UDR1=T_buf[T_ptr];
     T_ptr++;
   }
  else
  {
    T_count=0;
	T_ptr=0;
	RXD;
  }
}
void WaitTX(unsigned long time)
{
  DelayMs=time;
  DelayMs=time;
  while((R_full==0)&&(DelayMs>0));
}
void WaitRX(unsigned long time)
{
  DelayMs=time;
  while(((R_full==0)&&(DelayMs>0)));
}
/*void Wait(unsigned long time)
{
  unsigned long x=0;
  while(T_count>0)
  {
   x++;
   if(x>time)
   {
     T_count=0;
   }
  }
}*/

/*HAO***************************************************/
DATE_STRUCT DwinDate;//������ RTC��ֵ
Treatment_information HNDLE_INFORMATION;//��������ʹ�õ�ǰ�Ĳ���
Treatment_state MACHINE_STATE;

Set_information SettingDdata;//��̨���Ʋ���

static const unsigned char CRCHigh[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40};

static const unsigned char CRCLow[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
	0x41, 0x81, 0x80, 0x40};
/**
 * @brief  �ֱ�Ĭ������
 * @note   
 * @param 
 * @retval ��
 */
void DefaultSetting(void)
{
  unsigned char buff[16]; //���� 

  HNDLE_INFORMATION.SAVE_PRESS=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_RF=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_PRESS_IN=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_PRESS_OUT=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_LED=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_INFRARED=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_MOTO_SPEED=DEFAULTDATA;
  HNDLE_INFORMATION.SAVE_MOTO_TOWARD=DEFAULTDATA;
  MACHINE_STATE.WORK_SAVE_STATE=3;//Ĭ��ģʽ
  memset(buff, 0, 6);
  //DwinWriteLongWords(ADDR_BOOTINGSAVE_ADATA, buff, 3); //�������ABC������ʾ
  //ͬ������
  
  buff[0]= MACHINE_STATE.HANDLE_ID;
  buff[1]=HNDLE_INFORMATION.SAVE_PRESS;
  buff[2]=HNDLE_INFORMATION.SAVE_RF;
  buff[3]=HNDLE_INFORMATION.SAVE_PRESS_IN;
  buff[4]=HNDLE_INFORMATION.SAVE_PRESS_OUT;
  buff[5]=HNDLE_INFORMATION.SAVE_LED;
  buff[6]=HNDLE_INFORMATION.SAVE_INFRARED;
  buff[7]=HNDLE_INFORMATION.SAVE_MOTO_SPEED;
  buff[8]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
          
  //DwinWriteLongWords(ADDR_BOOTINGPRESSLINE, buff, 4); //������ͨ��
  //DwinWriteLongWords(ADDR_BOOTINGPRESSDATA, buff, 4);//������ͨ�ź���
  //DwinWriteLongWords(ADDR_BOOTINGPRESSKEY, buff, 4);//������ͨ�ź���

  //DwinWriteLongWords(ADDR_BOOTINGLEDLINE, &buff[8], 3); //������ͨ��
  //DwinWriteLongWords(ADDR_BOOTINGLEDDATA, &buff[8], 4);//������ͨ�ź���
  //DwinWriteLongWords(ADDR_BOOTINGLEDKEY, &buff[8], 4);//������ͨ�ź���
  Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
  ModeSet();//���ת������
  DwinWriteLongWords(ADDR_HANDPARAMETER, buff, 9); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
}
  
/**
 * @brief  ����CRCУ��
 * @note
 * @param  *buff: У�������ַָ��
 * @param  length: ��ҪУ������ݳ���
 * @retval 2�ֽ�У����
 */
unsigned int CheckCRC16(unsigned char *buff, unsigned char length)
{
	unsigned int result = 0;
	unsigned int index = 0;
	unsigned char highByte = 0xff;
	unsigned char lowByte = 0xff;
	while (length--)
	{
		index = lowByte ^ *(buff++);
		lowByte = (unsigned char)(highByte ^ CRCHigh[index]);
		highByte = CRCLow[index];
	}
	result = (unsigned int)highByte << 8 | (unsigned int)lowByte;
	return result;
}
/**
 * @brief  ��������ת����
 * @note   This function can be used for all STM32F10x devices.
 * @param  pageIndex: ��Ҫ��ת��ҳ��id
 * @retval ��
 */
void DwinToPage(unsigned char pageIndex)
{
	unsigned char i = 0;
	unsigned int check = 0;
  while(T_count>0);
  memset(T_buf, 0, sizeof(T_buf));
  T_buf[0]=0x5A;//2�ֽ�֡ͷ
  T_buf[1]=0xA5;//2�ֽ�֡ͷ
  T_buf[2]=0xA0;//Ŀ���ַ
  T_buf[3]=0xA4;//Դ��ַ 
  T_buf[4]=0x04;//����  ָ��+���ݳ���
  T_buf[5]=0x4000 >> 8;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ  ��תҳ��ָ��0x4000
  T_buf[6]=0x4000 & 0xff;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ  ��תҳ��ָ��0x4000
  T_buf[7]=pageIndex >> 8;;//����
  T_buf[8]=pageIndex & 0xff;//����
  T_buf[9]=0x00;//״̬ ����Ĭ��FF �ӻ��޹���00���߹�����

  for ( i = 0; i < (T_buf[4]+6); i++)//У���
  {
      T_buf[T_buf[4]+6]+=T_buf[i];
  }

  T_buf[11]=0x0D;//2�ֽ�֡β
  T_buf[12]=0x0A;//2�ֽ�֡β

  T_count=T_buf[4]+9;//����
  T_ptr=1;
  UDR0=T_buf[0];
}
/**
 * @brief  �����������д�Ĵ���ָ��
 * @note   �Ƿ����CRC16У�飬Ӱ�췢��ָ��ĳ���
 * @param  addr: �Ĵ�����ַ ������Ϊ��ָ��
 * @param  data: д�������
 * @param  ifCheck: �Ƿ����CRC16У�� true:У��  false:��У��
 * @retval None
 */
void DwinWriteWord(unsigned int addr, unsigned int data) //�������д��1��word����
{
	unsigned char i = 0;
	unsigned int check = 0;
  while(T_count>0);
  memset(T_buf, 0, sizeof(T_buf));
  T_buf[0]=0x5A;//2�ֽ�֡ͷ
  T_buf[1]=0xA5;//2�ֽ�֡ͷ
  T_buf[2]=0xA0;//Ŀ���ַ
  T_buf[3]=0xA4;//Դ��ַ 
  T_buf[4]=0x03;//����  ָ��+���ݳ���
  T_buf[5]=addr >> 8;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ
  T_buf[6]=addr & 0xff;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ
  T_buf[7]=data;//����
  T_buf[8]=0x00;//״̬ ����Ĭ��FF �ӻ��޹���00���߹�����

  for ( i = 0; i < (T_buf[4]+6); i++)//У���
  {
      T_buf[T_buf[4]+6]+=T_buf[i];
  }

  T_buf[10]=0x0D;//2�ֽ�֡β
  T_buf[11]=0x0A;//2�ֽ�֡β

  T_count=T_buf[4]+9;//����
  T_ptr=1;
  UDR0=T_buf[0];
}

/**
 * @brief  ���������������д�Ĵ���ָ��
 * @note
 * @param  addr: ��Ҫд��Ĵ������׵�ַ
 * @param  *p: ��д�����ݵ��׵�ַ
 * @param  length: д�����ݵĳ��� ��λ��word��2���ֽڣ�
 * @param  isCRC: �Ƿ����CRC16У�� true:У��  false:��У��
 * @retval None
 */
void DwinWriteLongWords(unsigned int addr, unsigned char *p, unsigned char length)
{
	//���ַaddr����дlength����word����
	// 1��word����ռ2���ֽ�

	unsigned int check;
	unsigned char i = 0;
  while(T_count>0);
	memset(T_buf, 0, sizeof(T_buf));
  T_buf[0]=0x5A;//2�ֽ�֡ͷ
  T_buf[1]=0xA5;//2�ֽ�֡ͷ
  T_buf[2]=0xA0;//Ŀ���ַ
  T_buf[3]=0xA4;//Դ��ַ 
  T_buf[4]=length+2;//����  ָ��+���ݳ���
  T_buf[5]=addr >> 8;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ
  T_buf[6]=addr & 0xff;;//2�ֽ�ָ�� ������Ϊ�ǵ��ĵĵ�ַ

  for (i = 0; i < length; i++)//��ֵ����
	{
      T_buf[i + 7] = p[i];
  }
  T_buf[length+7]=0x00;//״̬ ����Ĭ��FF �ӻ��޹���00���߹�����

  for ( i = 0; i < (length+8); i++)//У���
  {
      T_buf[length+8]+=T_buf[i];
  }
  T_buf[length+9]=0x0D;//2�ֽ�֡β
  T_buf[length+10]=0x0A;//2�ֽ�֡β
	
  T_count=length+11;//����
  T_ptr=1;
  UDR0=T_buf[0];
}

/**
 * @brief  �������
 * @note
 * @param  key: 1��̨���� 2sn����
 * @retval None
 */
void Key_Password(unsigned char key)
{
  unsigned char check = 1;
	unsigned char i = 0;

	unsigned char buff[20];
	switch (key)
	{
	case 1: //��̨�������
		for (i = 0; i < 8; i++)
		{
			if (passwordInput[i] != password[i])
			{
				check = 0; //�����������
				break;
			}
		}
		if (check) //������ȷ
		{
			memset(passwordInput, 0x20, sizeof(passwordInput));
			DwinWriteLongWords(ADDR_BOOTING_PASSWORDDISPLAY, passwordInput, 4); //���������ʾ
			DwinToPage(PAGE_SETTING);								  //��ת��̨����ҳ��

      EEPROMReadBytes(softwareVersionAddr,&SettingDdata.softwareVersion,16);//��������汾
      //for (i = 0; i < 16; i++){SettingDdata.softwareVersion[i]=buff[i];}
      DwinWriteLongWords(ADDR_BOOTING_softwareVersion,SettingDdata.softwareVersion, 8); //����ͨ��

      EEPROMReadBytes(hardwareVersionAddr,&SettingDdata.hardwareVersion,16);//����Ӳ���汾
      DwinWriteLongWords(ADDR_BOOTING_hardwareVersion, SettingDdata.hardwareVersion, 8); //����ͨ��

      EEPROMReadBytes(hexVersionAddr,&SettingDdata.hexVersion,16);//��������汾
      DwinWriteLongWords(ADDR_BOOTING_hexVersion, SettingDdata.hexVersion, 8); //����ͨ��

      EEPROMReadBytes(snNumberAddr,&SettingDdata.snNumber,16);//SN��
      DwinWriteLongWords(ADDR_BOOTING_snNumber, SettingDdata.snNumber, 8); //����ͨ��

      EEPROMReadBytes(SET_HANDLEONEAddr,&SettingDdata.SET_HANDLEONE,1);//1���ֱ�ѡ��
      DwinWriteWord(ADDR_KEY_SET_HANDLEONEDATA, SettingDdata.SET_HANDLEONE);//������ͨ�ź���

      EEPROMReadBytes(SET_HANDLEFIVEAddr,&SettingDdata.SET_HANDLEFIVE,1);//5�ű�֬�ֱ�ѡ��
      DwinWriteWord(ADDR_KEY_SET_HANDLEFIVEDATA, SettingDdata.SET_HANDLEFIVE);//������ͨ�ź���

      EEPROMReadBytes(SET_WORKTIMEAddr,&SettingDdata.SET_WORKTIME,1);//����ʱ��
      DwinWriteWord(ADDR_KEY_SET_WORKTIMEDATA,SettingDdata.SET_WORKTIME);//������ͨ�ź���

      EEPROMReadBytes(SET_WORKPOWERAddr,&SettingDdata.SET_WORKPOWER,1);//���������ٷֱ�
      DwinWriteWord(ADDR_KEY_SET_WORKPOWERDATA, SettingDdata.SET_WORKPOWER);//������ͨ�ź���

		}
		else //�������
		{
			//memset(buff, 0x20, sizeof(buff));
			//DwinWriteLongWords(ADDR_BOOTING_PASSWORDDISPLAY, buff, 4); //���������ʾ
			//delay_ms(20);
			strcpy((char *)buff, "Password Erro!");
			DwinWriteLongWords(ADDR_BOOTING_PASSWORDERR, buff, 7); //��ʾ�������
      delay_ms(600);
      memset(buff, 0x20, sizeof(buff));
			DwinWriteLongWords(ADDR_BOOTING_PASSWORDERR, buff, 7); //������������ʾ
      memset(passwordInput, 0x20, sizeof(passwordInput));
			DwinWriteLongWords(ADDR_BOOTING_PASSWORDDISPLAY, passwordInput, 4); //���������ʾ
		}
		break;
	case 2: //sn�������
		for (i = 0; i < 8; i++)
		{
			if (passwordInput[i] != SNpassword[i])
			{
				check = 0; //�����������
				break;
			}
		}
		if (check) //������ȷ
		{
			memset(passwordInput, 0x20, sizeof(passwordInput));
			DwinWriteLongWords(ADDR_BOOTING_SNPASSWORDDISPLAY, passwordInput, 4); //���������ʾ
      DwinToPage(SNPAGE_SETTING);	//��תSN����ҳ��
      memset(passwordInput, 0x20, sizeof(passwordInput));
		 DwinWriteLongWords(ADDR_BOOTING_SNDISPLAY, passwordInput, 4); //���SN
		}
		else //�������
		{
			//memset(buff, 0x20, sizeof(buff));
			//DwinWriteLongWords(ADDR_BOOTING_PASSWORDDISPLAY, buff, 4); //���������ʾ
			//delay_ms(20);
			strcpy((char *)buff, "Password Erro!");
			DwinWriteLongWords(ADDR_BOOTING_SNPASSWORDERR, buff, 7); //��ʾ�������
      delay_ms(600);
      memset(buff, 0x20, sizeof(buff));
			DwinWriteLongWords(ADDR_BOOTING_SNPASSWORDERR, buff, 7); //������������ʾ
      memset(passwordInput, 0x20, sizeof(passwordInput));
			DwinWriteLongWords(ADDR_BOOTING_SNPASSWORDDISPLAY, passwordInput, 4); //���������ʾ
		}
		break;
	}
}

/**
 * @brief  ���������ڴ������
 * @note   
 * @retval None
 */
void TASK_SendToDwin(void)
{
	unsigned char i = 0;
	unsigned char buff[16]; //����  ���ڵ��������ֽ�д��ָ��
  
	if (RX1Countertail!=RX1Counterhead) //�����������ݽ����뷢��
	{
		/*
		д�Ĵ���������82ָ��
		00 01 02 03 04 05
		5A A5 05 82 4F 4B

		�����ϴ���83ָ��
		00 01 02 03 04 05 06 07   08   09   0a
		5A A5 06 83 66 66 01 ���� ��ֵ У��1 У��2

		���ݶ�ȡ��83ָ��
		00 01 02 03 04 05 06 07   08   09   0a
		5A A5 06 83 66 66 01 ���� ��ֵ У��1 У��2
		*/
		DwinCmd = RX1Data[RX1Countertail][3];//��������
		DwinAddr = RX1Data[RX1Countertail][5] << 8 | RX1Data[RX1Countertail][6]; //��ַ  �൱��ָ��
		DwinData = RX1Data[RX1Countertail][7]; //����
    Dwindata2 = RX1Data[RX1Countertail][8]; //״̬���
 
		//DwinTouchPage = RX1Data[RX1FinishIndex][7];													 //����ҳ��
		//DwinTouchKey = RX1Data[RX1FinishIndex][8];													 //���ؼ�ֵ                                                                                                                                                                 

		switch (DwinCmd) //������������
		{
     
		 case 0x82: DIWEN_RECEICEDATA_STATE=1; //д�Ĵ�������
			break;
		 case 0xA0: //�ж���������

      DIWEN_RECEICEDATA_STATE=1; 
			switch (DwinAddr)
			{
        case ADDR_HANDCHOOSE://�ֱ�ѡ��ָ��
        if(DwinData==ADDR_KEY_BACK_HANDLEONE)//�ֱ�1��ѡ��
        {
        MACHINE_STATE.HANDLE_ID=1;   
        Intensity[8]=MACHINE_STATE.HANDLE_ID-1;
        //DefaultSetting();   
        DwinWriteWord(DwinAddr, DwinData);//ָ���
        }

        if(DwinData==ADDR_KEY_BACK_HANDLETWO)//�ֱ�2��ѡ��
        {
        MACHINE_STATE.HANDLE_ID=2;
        Intensity[8]=MACHINE_STATE.HANDLE_ID-1;
        //DefaultSetting();
        DwinWriteWord(DwinAddr, DwinData);//ָ���      
        }

        if(DwinData==ADDR_KEY_BACK_HANDLETHREE)//�ֱ�3��ѡ��
        {
        MACHINE_STATE.HANDLE_ID=3;  
        Intensity[8]=MACHINE_STATE.HANDLE_ID-1;
        //DefaultSetting();
        DwinWriteWord(DwinAddr, DwinData);//ָ���         
        }

        if(DwinData==ADDR_KEY_BACK_HANDLEFOUR)//�ֱ�4��ѡ��
        {
        MACHINE_STATE.HANDLE_ID=4; 
        Intensity[8]=MACHINE_STATE.HANDLE_ID-1;
       // DefaultSetting();
        DwinWriteWord(DwinAddr, DwinData);//ָ���   
        }

        if(DwinData==ADDR_KEY_BACK_HANDLEFIVE)//�ֱ�5��ѡ��
        {
        MACHINE_STATE.HANDLE_ID=5;  
        Intensity[8]=MACHINE_STATE.HANDLE_ID-1;
        //SAVE_FAT_FLAME=DEFAULTDATA;//Ĭ�������ȼ�   
        //DwinWriteWord(ADDR_BOOTING_FAT_UP_DOWNDATA, SAVE_FAT_FLAME);//������ͨ�ź��� 
        DwinWriteWord(DwinAddr, DwinData);//ָ���
        }

        if(DwinData==0xFF)//δѡ�ֱ��˳����ƽ���
        {
        MACHINE_STATE.HANDLE_ID=0xFF;  
        Intensity[8]=MACHINE_STATE.HANDLE_ID;
        //SAVE_FAT_FLAME=DEFAULTDATA;//Ĭ�������ȼ�   
        //DwinWriteWord(ADDR_BOOTING_FAT_UP_DOWNDATA, SAVE_FAT_FLAME);//������ͨ�ź��� 
        DwinWriteWord(DwinAddr, DwinData);//ָ���
        }

        break;

        case ADDR_HANDPARAMETER: //�ֱ���������

        switch (DwinData)
        {
        case 0://1���ֱ���������

        //��ѹ�ȼ�
        HNDLE_INFORMATION.SAVE_PRESS=RX1Data[RX1Countertail][8];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_IN=RX1Data[RX1Countertail][9];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_OUT=RX1Data[RX1Countertail][10];//ͬ����������
        //��Ƶ�ȼ�
        HNDLE_INFORMATION.SAVE_RF=RX1Data[RX1Countertail][11];//ͬ����������
        //LED�ȼ�
        HNDLE_INFORMATION.SAVE_LED=RX1Data[RX1Countertail][12];//ͬ����������
        //����ȼ�
        HNDLE_INFORMATION.SAVE_INFRARED=RX1Data[RX1Countertail][13];//ͬ����������
        //���ת�ٵȼ�
        HNDLE_INFORMATION.SAVE_MOTO_SPEED=RX1Data[RX1Countertail][14];//ͬ����������
        //���ת�򰴼���ֵ����
        HNDLE_INFORMATION.SAVE_MOTO_TOWARD=RX1Data[RX1Countertail][15];//���ת��״̬
        Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
        ModeSet();//���ת������
        memcpy(buff,&RX1Data[RX1Countertail][7],9);
        DwinWriteLongWords(ADDR_HANDPARAMETER, buff, 9); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        delay_ms(10);
          
          break;

        case 1://2���ֱ���������
        //��ѹ�ȼ�
        HNDLE_INFORMATION.SAVE_PRESS=RX1Data[RX1Countertail][8];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_IN=RX1Data[RX1Countertail][9];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_OUT=RX1Data[RX1Countertail][10];//ͬ����������
        //��Ƶ�ȼ�
        HNDLE_INFORMATION.SAVE_RF=RX1Data[RX1Countertail][11];//ͬ����������
        //LED�ȼ�
        HNDLE_INFORMATION.SAVE_LED=RX1Data[RX1Countertail][12];//ͬ����������
        //����ȼ�
        HNDLE_INFORMATION.SAVE_INFRARED=RX1Data[RX1Countertail][13];//ͬ����������
        //���ת�ٵȼ�
        HNDLE_INFORMATION.SAVE_MOTO_SPEED=RX1Data[RX1Countertail][14];//ͬ����������
        //���ת�򰴼���ֵ����
        HNDLE_INFORMATION.SAVE_MOTO_TOWARD=RX1Data[RX1Countertail][15];//���ת��״̬
        Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
        ModeSet();//���ת������
        memcpy(buff,&RX1Data[RX1Countertail][7],9);
        DwinWriteLongWords(ADDR_HANDPARAMETER, buff, 9); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        delay_ms(10);
          break;
        case 2://3���ֱ���������
        //��ѹ�ȼ�
        HNDLE_INFORMATION.SAVE_PRESS=RX1Data[RX1Countertail][8];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_IN=RX1Data[RX1Countertail][9];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_OUT=RX1Data[RX1Countertail][10];//ͬ����������
        //��Ƶ�ȼ�
        HNDLE_INFORMATION.SAVE_RF=RX1Data[RX1Countertail][11];//ͬ����������
        //LED�ȼ�
        HNDLE_INFORMATION.SAVE_LED=RX1Data[RX1Countertail][12];//ͬ����������
        //����ȼ�
        HNDLE_INFORMATION.SAVE_INFRARED=RX1Data[RX1Countertail][13];//ͬ����������
        //���ת�ٵȼ�
        HNDLE_INFORMATION.SAVE_MOTO_SPEED=RX1Data[RX1Countertail][14];//ͬ����������
        //���ת�򰴼���ֵ����
        HNDLE_INFORMATION.SAVE_MOTO_TOWARD=RX1Data[RX1Countertail][15];//���ת��״̬
        Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
        ModeSet();//���ת������
        memcpy(buff,&RX1Data[RX1Countertail][7],9);
        DwinWriteLongWords(ADDR_HANDPARAMETER, buff, 9); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        delay_ms(10);
          
        break;
        case 3://4���ֱ���������
        //��ѹ�ȼ�
        HNDLE_INFORMATION.SAVE_PRESS=RX1Data[RX1Countertail][8];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_IN=RX1Data[RX1Countertail][9];//ͬ����������
        //�����ȼ�
        HNDLE_INFORMATION.SAVE_PRESS_OUT=RX1Data[RX1Countertail][10];//ͬ����������
        //��Ƶ�ȼ�
        HNDLE_INFORMATION.SAVE_RF=RX1Data[RX1Countertail][11];//ͬ����������
        //LED�ȼ�
        HNDLE_INFORMATION.SAVE_LED=RX1Data[RX1Countertail][12];//ͬ����������
        //����ȼ�
        HNDLE_INFORMATION.SAVE_INFRARED=RX1Data[RX1Countertail][13];//ͬ����������
        //���ת�ٵȼ�
        HNDLE_INFORMATION.SAVE_MOTO_SPEED=RX1Data[RX1Countertail][14];//ͬ����������
        //���ת�򰴼���ֵ����
        HNDLE_INFORMATION.SAVE_MOTO_TOWARD=RX1Data[RX1Countertail][15];//���ת��״̬
        Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;
        ModeSet();//���ת������
        memcpy(buff,&RX1Data[RX1Countertail][7],9);
        DwinWriteLongWords(ADDR_HANDPARAMETER, buff, 9); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        delay_ms(10);
          
        break;
        
        default:
          break;
        }

        break;


	      case ADDR_HANDWORK://�ֱ�������ָͣ��

        switch (DwinData)
        {
        case 0://1���ֱ���ͣ����
  
        MACHINE_STATE.WORK_STATE=RX1Data[RX1Countertail][8];//��ֵ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HANDWORK, buff, 2); //��������׿��
       // delay_ms(10);
        if(MACHINE_STATE.HANDLE_ID==1)//1��485ͨѶ�ֱ�
        {Send_command();delay_ms(10);}//1���ֱ���ͣ
          
          break;

        case 1://2���ֱ���ͣ����
        MACHINE_STATE.WORK_STATE=RX1Data[RX1Countertail][8];//��ֵ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HANDWORK, buff, 2); //��������׿��
        
        if(MACHINE_STATE.WORK_STATE==1)
        {
          if(Intensity[8]==2)  BitClr(PORTG,4);//�ֱ�����ָʾ��
          if(Intensity[8]==3)  BitClr(PORTG,3);//�ֱ�����ָʾ��
        }
        else
        {
          BitSet(PORTG,4);
          BitSet(PORTG,3);
        }
          
          break;

        case 2://3���ֱ���ͣ����
        MACHINE_STATE.WORK_STATE=RX1Data[RX1Countertail][8];//��ֵ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HANDWORK, buff, 2); //��������׿��
        
        if(MACHINE_STATE.WORK_STATE==1)
        {
          if(Intensity[8]==2)  BitClr(PORTG,4);//�ֱ�����ָʾ��
          if(Intensity[8]==3)  BitClr(PORTG,3);//�ֱ�����ָʾ��
        }
        else
        {
          BitSet(PORTG,4);
          BitSet(PORTG,3);
        }
          
          break;

        case 3://4���ֱ���ͣ����
        MACHINE_STATE.WORK_STATE=RX1Data[RX1Countertail][8];//��ֵ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HANDWORK, buff, 2); //��������׿��
        
        if(MACHINE_STATE.WORK_STATE==1)
        {
          if(Intensity[8]==2)  BitClr(PORTG,4);//�ֱ�����ָʾ��
          if(Intensity[8]==3)  BitClr(PORTG,3);//�ֱ�����ָʾ��
        }
        else
        {
          BitSet(PORTG,4);
          BitSet(PORTG,3);
        }
          
          break;
        
        default:
          break;
        }

        break;
		

        case ADDR_HAND40KWORK://��֬�ֱ�������ָͣ��
        MACHINE_STATE.WORK_STATE=RX1Data[RX1Countertail][8];//��ֵ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HAND40KWORK, buff, 2); //��������׿��
        
        if(MACHINE_STATE.WORK_STATE==1)
        {
          if(Intensity[8]==2)  BitClr(PORTG,4);//�ֱ�����ָʾ��
          if(Intensity[8]==3)  BitClr(PORTG,3);//�ֱ�����ָʾ��
        }
        else
        {
          BitSet(PORTG,4);
          BitSet(PORTG,3);
        }
        break;

        case ADDR_HAND40KPARAMETER: //��֬�ֱ���������
        SAVE_FAT_FLAME=RX1Data[RX1Countertail][8];//ͬ����������
        //DwinWriteLongWords(ADDR_BOOTINGINFRAREDLINE, buff, 1); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        memcpy(buff,&RX1Data[RX1Countertail][7],2);
        DwinWriteLongWords(ADDR_HAND40KPARAMETER, buff, 2); //��������׿��
        delay_ms(10);
				break;

        
        case ADDR_HANDPARAMETER_SAVE: //��̨��������
        SettingDdata.SET_WORKPOWER=RX1Data[RX1Countertail][9];//ͬ����������
        RfPer=SettingDdata.SET_WORKPOWER;
        //DwinWriteLongWords(ADDR_BOOTINGINFRAREDLINE, buff, 1); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
        memcpy(buff,&RX1Data[RX1Countertail][7],3);
        DwinWriteLongWords(ADDR_HANDPARAMETER_SAVE, buff, 3); //��������׿��
        delay_ms(10);
				break;

        case ADDR_HANDPARAMETER_READ: //��̨������ȡ
        RfPer=SettingDdata.SET_WORKPOWER;
        buff[0]=RfPer;
        DwinWriteLongWords(ADDR_HANDPARAMETER_READ, buff, 1); //��������׿��
        delay_ms(10);
				break;





        default:  break;  
			}
      break;
			default:  break;  
		}
		//������һ��ָ�� �ƶ�ָ�� ѭ������  ֱ�������ָ����ͬΪֹ
		//if (isLongPress == false)
		//MoveFinishIndex();
    for(i=0;i<30;i++)
    {RX1Data[RX1Countertail][i]=0;}
    RX1Countertail++;
    if(RX1Countertail>20){RX1Countertail=0;}
  }
}


/**
 * @brief  �����ǲ���������
 * @note   //֮ǰ���� Intensity[0] LED�ȼ�  Intensity[2] RF�ȼ�  Intensity[3] ���ת�ٵȼ�  Intensity[8] �ֱ�ID
 * @note   //֮ǰ���� Intensity[4] ��ѹ�ȼ�  Intensity[5] ����ʱ��  Intensity[6] ����ʱ��  Intensity[7] ���ת��
 * @retval None
 */
void TASK_PROCESSING(void)
{
 
  if (DIWEN_RECEICEDATA_STATE==1)
  {
    DIWEN_RECEICEDATA_STATE=0;
    if(MACHINE_STATE.HANDLE_ID==1)//1���ֱ�����
    {
      Intensity[0]=HNDLE_INFORMATION.SAVE_LED;//LED�ȼ�
      Intensity[1]=HNDLE_INFORMATION.SAVE_INFRARED;//����ȼ�
      Intensity[2]=HNDLE_INFORMATION.SAVE_RF;//��Ƶ�ȼ�
      Intensity[3]=HNDLE_INFORMATION.SAVE_MOTO_SPEED;//���ת�ٵȼ�
      Intensity[4]=HNDLE_INFORMATION.SAVE_PRESS;//��ѹ�ȼ�
      Intensity[5]=HNDLE_INFORMATION.SAVE_PRESS_IN;//����ʱ��
      Intensity[6]=HNDLE_INFORMATION.SAVE_PRESS_OUT;//����ʱ��
      Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;//���ת��
      Intensity[8]=MACHINE_STATE.HANDLE_ID-1;//�ֱ�ID
      Send_Data8();//1���ֱ�����ͬ��
    }

    if(MACHINE_STATE.HANDLE_ID==2)//2���ֱ�����
    {
      Intensity[0]=HNDLE_INFORMATION.SAVE_LED;//LED�ȼ�
      Intensity[2]=HNDLE_INFORMATION.SAVE_RF;//��Ƶ�ȼ�
      Intensity[3]=HNDLE_INFORMATION.SAVE_MOTO_SPEED;//���ת�ٵȼ�
      Intensity[4]=HNDLE_INFORMATION.SAVE_PRESS;//��ѹ�ȼ�
      Intensity[5]=HNDLE_INFORMATION.SAVE_PRESS_IN;//����ʱ��
      Intensity[6]=HNDLE_INFORMATION.SAVE_PRESS_OUT;//����ʱ��
      Intensity[7]=HNDLE_INFORMATION.SAVE_MOTO_TOWARD;//���ת��
      Intensity[8]=MACHINE_STATE.HANDLE_ID-1;//�ֱ�ID
    }

    if(MACHINE_STATE.HANDLE_ID==3)//3���ֱ�����
    {
      Intensity[0]=HNDLE_INFORMATION.SAVE_LED;//LED�ȼ�
      Intensity[2]=HNDLE_INFORMATION.SAVE_RF;//��Ƶ�ȼ�
      Intensity[4]=HNDLE_INFORMATION.SAVE_PRESS;//��ѹ�ȼ�
      Intensity[5]=HNDLE_INFORMATION.SAVE_PRESS_IN;//����ʱ��
      Intensity[6]=HNDLE_INFORMATION.SAVE_PRESS_OUT;//����ʱ��
      Intensity[8]=MACHINE_STATE.HANDLE_ID-1;//�ֱ�ID
    }


    if(MACHINE_STATE.HANDLE_ID==4)//4���ֱ�����
    {
      Intensity[2]=HNDLE_INFORMATION.SAVE_RF;//��Ƶ�ȼ�
      Intensity[4]=HNDLE_INFORMATION.SAVE_PRESS;//��ѹ�ȼ�
      Intensity[5]=HNDLE_INFORMATION.SAVE_PRESS_IN;//����ʱ��
      Intensity[6]=HNDLE_INFORMATION.SAVE_PRESS_OUT;//����ʱ��
      Intensity[8]=MACHINE_STATE.HANDLE_ID-1;//�ֱ�ID
    }

  }
  
}


/*HAO****************************************************/

unsigned char  GetChecking(void)
{
  unsigned int Or=0;
  unsigned int Len;
  Len=R_count-6;
  R_count=1;
  while(R_count<Len) Or+=R_buf[R_count++];
  if((R_buf[R_count]==(Or>>8))&&(R_buf[R_count+1]==(Or&0x00ff))) return 1;
  else return 0;
}
void GetCheckingOr(void)
{
  unsigned int Or=0;
  unsigned int Len;
  Len=T_count-4;
  T_count=1;
  while(T_count<Len) Or+=T_buf[T_count++];
  T_buf[T_count++]=Or>>8;
  T_buf[T_count++]=Or;
  T_buf[T_count++]=0xcc;
  T_buf[T_count++]=0x33;
  T_buf[T_count++]=0xc3;
  T_buf[T_count++]=0x3c;
}
void ShakeHands(void)
{
 while(T_count>0);
 T_buf[0]=0x5a;
 T_buf[1]=0xa5;
 T_buf[2]=0x05;
 T_buf[3]=0x82;
 T_buf[4]=0x10;
 T_buf[5]=0x00;
 T_buf[6]=0x00;
 T_buf[7]=0x03;
 T_count=8;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 UDR0=T_buf[0];
}
void set_color(unsigned int ForegColor,unsigned int BackColor)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x40;
 T_buf[2]=ForegColor>>8;
 T_buf[3]=ForegColor;
 T_buf[4]=BackColor>>8;
 T_buf[5]=BackColor;
 T_buf[6]=0xcc;
 T_buf[7]=0x33;
 T_buf[8]=0xc3;
 T_buf[9]=0x3c;
 T_count=10;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void set_text_xy(unsigned char dx,unsigned char dy)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x41;
 T_buf[2]=dx;
 T_buf[3]=dy;
 T_buf[4]=0xcc;
 T_buf[5]=0x33;
 T_buf[6]=0xc3;
 T_buf[7]=0x3c;
 T_count=8;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void get_color(unsigned char FB,unsigned int x,unsigned int y)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x42+FB;
 T_buf[2]=x>>8;
 T_buf[3]=x;
 T_buf[4]=y>>8;
 T_buf[5]=y;
 T_buf[6]=0xcc;
 T_buf[7]=0x33;
 T_buf[8]=0xc3;
 T_buf[9]=0x3c;
 T_count=10;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}

void cursor(unsigned char EN,unsigned int x,unsigned int y,unsigned char w,unsigned char h)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x44;
 T_buf[2]=EN;
 T_buf[3]=x>>8;
 T_buf[4]=x;
 T_buf[5]=y>>8;
 T_buf[6]=y;
 T_buf[7]=w;
 T_buf[8]=h;
 T_buf[9]=0xcc;
 T_buf[10]=0x33;
 T_buf[11]=0xc3;
 T_buf[12]=0x3c;
 T_count=13;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void print_text(unsigned char lib,unsigned int x,unsigned int y,unsigned char *text)
{
  /*
 unsigned char len=6;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x53+lib;//lib=0-2
 T_buf[2]=x>>8;
 T_buf[3]=x;
 T_buf[4]=y>>8;
 T_buf[5]=y;
 while (*text !='\0')
 {
  T_buf[len]=*text;
  text++;
  len++;
 }
 T_buf[len++]=0xcc;
 T_buf[len++]=0x33;
 T_buf[len++]=0xc3;
 T_buf[len++]=0x3c;
 T_count=len;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void print_texts(unsigned int x,unsigned int y,unsigned char lib,unsigned char mode,unsigned char dots,unsigned int Fcolor,unsigned int Bcolor,unsigned char *text)
{
  /*
 unsigned char len=13;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x98;  
 T_buf[2]=x>>8;
 T_buf[3]=x;
 T_buf[4]=y>>8;
 T_buf[5]=y;
 T_buf[6]=lib;  //0x00-0x3b
 T_buf[7]=mode; //.7ǰ��,.6����,.5����,.4�Զ���࣬.3-.1=1-4
 T_buf[8]=dots; //0x00-0x1E
 T_buf[9]=Fcolor>>8;
 T_buf[10]=Fcolor;
 T_buf[11]=Bcolor>>8;
 T_buf[12]=Bcolor;
 while (*text !='\0')
 {
  T_buf[len]=*text;
  text++;
  len++;
 }
 T_buf[len++]=0xcc;
 T_buf[len++]=0x33;
 T_buf[len++]=0xc3;
 T_buf[len++]=0x3c;
 T_count=len;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void print_consttexts(unsigned int x,unsigned int y,unsigned char lib,unsigned char mode,unsigned char dots,unsigned int Fcolor,unsigned int Bcolor,const unsigned char *text)
{
  /*
 unsigned char len=13;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x98;  
 T_buf[2]=x>>8;
 T_buf[3]=x;
 T_buf[4]=y>>8;
 T_buf[5]=y;
 T_buf[6]=lib;  //0x00-0x3b
 T_buf[7]=mode; //.7ǰ��,.6����,.5����,.4�Զ���࣬.3-.1=1-4
 T_buf[8]=dots; //0x00-0x1E
 T_buf[9]=Fcolor>>8;
 T_buf[10]=Fcolor;
 T_buf[11]=Bcolor>>8;
 T_buf[12]=Bcolor;
 while (*text !='\0')
 {
  T_buf[len]=*text;
  text++;
  len++;
 }
 T_buf[len++]=0xcc;
 T_buf[len++]=0x33;
 T_buf[len++]=0xc3;
 T_buf[len++]=0x3c;
 T_count=len;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void textsize_enable(unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x45;
 T_buf[2]=Xs>>8;
 T_buf[3]=Xs;
 T_buf[4]=Ys>>8;
 T_buf[5]=Ys;
 T_buf[6]=Xe>>8;
 T_buf[7]=Xe;
 T_buf[8]=Ye>>8;
 T_buf[9]=Ye;
 T_buf[10]=0xcc;
 T_buf[11]=0x33;
 T_buf[12]=0xc3;
 T_buf[13]=0x3c;
 T_count=14;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void textsize_disable(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x45;
 T_buf[2]=0;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void Painting_dot(unsigned char CMD,unsigned int x,unsigned int y)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x50+CMD;
 T_buf[2]=x>>8;
 T_buf[3]=x;
 T_buf[4]=y>>8;
 T_buf[5]=y;
 T_buf[6]=0xcc;
 T_buf[7]=0x33;
 T_buf[8]=0xc3;
 T_buf[9]=0x3c;
 T_count=10;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void Painting_dots(unsigned char CMD,unsigned char argc,unsigned int *argv,unsigned int x,unsigned int y)
{
  /*
 unsigned char i,j=2;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x50+CMD;
 for(i=0;i<argc;i++)
 {
  T_buf[j++]=*argv>>8;
  T_buf[j++]=*argv;
  argv++;
  T_buf[j++]=*argv>>8;
  T_buf[j++]=*argv;
  argv++;
 }
 T_buf[j++]=x>>8;
 T_buf[j++]=x;
 T_buf[j++]=y>>8;
 T_buf[j++]=y;
 T_buf[j++]=0xcc;
 T_buf[j++]=0x33;
 T_buf[j++]=0xc3;
 T_buf[j++]=0x3c;
 T_count=j;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void Painting_line(unsigned char CMD,unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x5D-CMD*7;
 T_buf[2]=Xs>>8;
 T_buf[3]=Xs;
 T_buf[4]=Ys>>8;
 T_buf[5]=Ys;
 T_buf[6]=Xe>>8;
 T_buf[7]=Xe;
 T_buf[8]=Ye>>8;
 T_buf[9]=Ye;
 T_buf[10]=0xcc;
 T_buf[11]=0x33;
 T_buf[12]=0xc3;
 T_buf[13]=0x3c;
 T_count=14;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void Set_screen(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0xe3;
 T_buf[2]=0x55;
 T_buf[3]=0xaa;
 T_buf[4]=0x5a;
 T_buf[5]=0xa5;
 T_buf[6]=0x03;
 T_buf[7]=0x05;
 T_buf[8]=0x08;
 T_buf[9]=0xff;
 T_buf[10]=0xcc;
 T_buf[11]=0x33;
 T_buf[12]=0xc3;
 T_buf[13]=0x3c;
 T_count=14;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void clear_screen(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x52;
 T_buf[2]=0xcc;
 T_buf[3]=0x33;
 T_buf[4]=0xc3;
 T_buf[5]=0x3c;
 T_count=6;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void Chack_screen(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0xe4;
 T_buf[2]=0x55;
 T_buf[3]=0xaa;
 T_buf[4]=0x5a;
 T_buf[5]=0xa5;
 T_buf[6]=0xcc;
 T_buf[7]=0x33;
 T_buf[8]=0xc3;
 T_buf[9]=0x3c;
 T_count=10;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void PicRam(unsigned char CMD,unsigned char RAM_POS)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x73+CMD*0x75; //CMD=0 read ram,1 write ram
 T_buf[2]=RAM_POS; //0-1
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void dis_pic(unsigned char pic_ID)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x70;
 T_buf[2]=pic_ID;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while(0==(PIND&0x10));
 UDR0=T_buf[0];
 */
}
void cut_pic(unsigned char CMD,unsigned char pic_ID,unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye,unsigned int X,unsigned int Y)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x71+CMD*0x2b;
 T_buf[2]=pic_ID;
 T_buf[3]=Xs>>8;
 T_buf[4]=Xs;
 T_buf[5]=Ys>>8;
 T_buf[6]=Ys;
 T_buf[7]=Xe>>8;
 T_buf[8]=Xe;
 T_buf[9]=Ye>>8;
 T_buf[10]=Ye;
 T_buf[11]=X>>8;
 T_buf[12]=X;
 T_buf[13]=Y>>8;
 T_buf[14]=Y;
 T_buf[15]=0xcc;
 T_buf[16]=0x33;
 T_buf[17]=0xc3;
 T_buf[18]=0x3c;
 T_count=19;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
//while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void buzzer(unsigned char time)
{
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x79;
 T_buf[2]=time;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
}
void clock_off(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x9b;
 T_buf[2]=0x00;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void get_time(void)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x9b;
 T_buf[2]=0x5a;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void clock_on(unsigned char RTC_mode,unsigned char Text_mode,unsigned int Color,unsigned int X,unsigned int Y)
{
  /*
 while(T_count>0);
 if(RTC_mode==0) return;
 T_buf[0]=0xaa;
 T_buf[1]=0x9b;
 T_buf[2]=0xff;
 T_buf[3]=RTC_mode-1;  //0-1
 T_buf[4]=Text_mode; //0-7
 T_buf[5]=Color>>8;
 T_buf[6]=Color;
 T_buf[7]=X>>8;
 T_buf[8]=X;
 T_buf[9]=Y>>8;
 T_buf[10]=Y;
 T_buf[11]=0xcc;
 T_buf[12]=0x33;
 T_buf[13]=0xc3;
 T_buf[14]=0x3c;
 T_count=15;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void clock_set(unsigned char YY,unsigned char MO,unsigned char DD,unsigned char HH,unsigned char MM,unsigned char SS)
{
  /*
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0xE7;
 T_buf[2]=0x55;
 T_buf[3]=0xAA;
 T_buf[4]=0x5A;
 T_buf[5]=0xA5;
 T_buf[6]=YY;
 T_buf[7]=MO;
 T_buf[8]=DD;
 T_buf[9]=HH;
 T_buf[10]=MM;
 T_buf[11]=SS;
 T_buf[12]=0xcc;
 T_buf[13]=0x33;
 T_buf[14]=0xc3;
 T_buf[15]=0x3c;
 T_count=16;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 //while((PIND&0x10)==0);
 UDR0=T_buf[0];
 */
}
void send_pic(unsigned long add,unsigned char len)
{
  /*
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0x72;
 T_buf[2]=(char)(add/65536);
 T_buf[3]=(char)(add%65536/256);
 T_buf[4]=(char)(add%256);
 for(i=0;i<len/3;i++)
 {
  T_buf[i*3+5]=R_buf[i*3+5]; 
  T_buf[i*3+6]=R_buf[i*3+4]; 
  T_buf[i*3+7]=R_buf[i*3+3]; 
 }
 T_buf[len+5]=0xcc;
 T_buf[len+6]=0x33;
 T_buf[len+7]=0xc3;
 T_buf[len+8]=0x3c;
 T_count=len+9;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 UDR0=T_buf[0];
 */
}
void save_pic(unsigned char page)
{
  /*
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0xaa;
 T_buf[1]=0xE2;
 T_buf[2]=page;
 T_buf[3]=0xcc;
 T_buf[4]=0x33;
 T_buf[5]=0xc3;
 T_buf[6]=0x3c;
 T_count=7;
 if(R_Check==1) GetCheckingOr();
 T_ptr=1;
 UDR0=T_buf[0];
 */
}

void USB_info(void)
{
  /*
  if(R_buf[0]==0x82) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_DISK_DISCON);
  else if(R_buf[0]==0x00) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_SUCCESS);
  else if(R_buf[0]==0x83) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_STATUS_ERR);
  else if(R_buf[0]==0xA3) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_FAT_ERROR);
  else if(R_buf[0]==0xB1) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_DISK_FULL);
  else if(R_buf[0]==0xB3) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_MISS_DIR);
  else if(R_buf[0]==0xB4) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_FILE_CLOSE);
  else if(R_buf[0]==0x41) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_OPEN_DIR);
  else if(R_buf[0]==0x42) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_MISS_FILE);
  else if(R_buf[0]==0x1F) print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_USB_DISK_ERR);
  else print_consttexts(0,0,0,0xc1,2,0xf800,0xffff,ERR_USB_DISK_ERR);
  */
}
//COM1����
void CMD_GetVer(void)//��ȡ�汾��
{
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x0a;
 T_buf[2]=0;
 T_count=3;
 T_ptr=1;
 UDR1=T_buf[0];
}
void CMD_DiskReady(void)//��ѯӲ��
{
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x71;
 T_buf[2]=0;
 T_count=3;
 T_ptr=1;
 UDR1=T_buf[0];
}
void CMD_File(unsigned char cmd,const unsigned char *FileName)//cmd=0���ļ���cmd=1�����ļ���cmd=2ɾ���ļ���cmd=3�ر��ļ�,�ļ�����"filemame.bmp\0"
{
 unsigned long i=0;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x64+cmd;
 T_buf[3]='/';  //92
 while(*FileName !='\0')
 {
  T_buf[i+4]=*FileName; 
  FileName++;
  i++;
 }
 T_buf[2]=i+1;
 T_count=i+4;
 T_ptr=1; 
 UDR1=T_buf[0];
}
void CMD_ByteLocate(unsigned long Locate)//�ֽ�ƫ��
{
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x7A;
 T_buf[2]=4;
 T_buf[3]=(char)(Locate/0x1000000);
 T_buf[4]=(char)(Locate%0x1000000/0x10000);
 T_buf[5]=(char)(Locate%0x10000/0x100);
 T_buf[6]=(char)(Locate%0x100);
 T_count=7;
 T_ptr=1;
 UDR1=T_buf[0];
}
void CMD_ByteRead(unsigned char Len)//��ȡ�����ֽ�
{
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x7b;
 T_buf[2]=1;
 T_buf[3]=Len;
 T_count=4;
 T_ptr=1;
 UDR1=T_buf[0];
}
void CMD_ByteWrite(const unsigned char *Text)//д�������ֽ�
{
 unsigned long i=0;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x7c;
 while(*Text !='\0')
 {
  T_buf[i+3]=*Text; 
  Text++;
  i++;
 }
 T_buf[2]=i;
 T_count=i+3;
 T_ptr=1;
 UDR1=T_buf[0];
}
void CMD_RESET(void)//��λ
{
 unsigned long i;
 while(T_count>0);
 T_buf[0]=0x3a;
 T_buf[1]=0x7d;
 T_buf[2]=0;
 T_count=3;
 T_ptr=1;
 UDR1=T_buf[0];
}
void GetUSB(void)
{
  RTX=1;
  R_full=0;
  R_buf[0]=255;
  CMD_DiskReady();//���USB�豸
  WaitRX(500);
  if(R_buf[0]==0)
  {
   
  }
  RTX=0;
}
void Up_Pic(void)
{
  unsigned long w,h,len;
  clock_off();
  clear_screen();
  RTX=1;
  R_full=0;
  CMD_GetVer();//��ȡ�汾��
  WaitRX(500);
  Sound_Count=2;
  if(R_buf[0]!=0)
  {
    USB_info();
	RTX=0;
	return;
  }
  Delay_MS(2);
  R_full=0;
  CMD_DiskReady();//���USB�豸
  WaitRX(500);
  if(R_buf[0]!=0)
  {
    USB_info();
	RTX=0;
	return;
  }
  Delay_MS(2);
  R_full=0;
  CMD_File(0,filename);//���ļ�
  WaitRX(500);
  Sound_Count=2;
  if(R_buf[0]!=0)
  {
    USB_info();
	RTX=0;
	return;
  }
  R_full=0;
  for(h=0;h<600;h++)
  {
    for(w=0;w<10;w++)
	{
	 Delay_MS(2);
	 len=(479-h)*2400+w*240+54;
     CMD_ByteLocate(len);
	 WaitRX(500);
	 if(R_full==0) continue;  /* �����ȴ�ģ����ɲ��� */
	 R_full=0;
	 Delay_MS(2);
     CMD_ByteRead(240);
	 WaitRX(500);
	 if(R_full==0) continue;  /* �����ȴ�ģ����ɲ��� */
	 R_full=0;
	 
     send_pic(800*h+w*80,240);
	 Sound_Count=2;
	}
  }
  save_pic(0);
  CMD_File(3,filename);
  Sound_Count=20;
  RTX=0;
}

void dispose_data(void)//��ѹ1���ֱ����ݴ���
{
  unsigned char i;
  unsigned char buff[16];
  if (RX2Countertail!=RX2Counterhead)
  {

  if(RX2Data[RX2Countertail][2]<7)//buf2��Ӧ�������� buf3��Ӧ�����ȼ�
  {
    Intensity[RX2Data[RX2Countertail][2]]=RX2Data[RX2Countertail][3];
	 // DisIntensity(R_buf1[2]);
   // IntensitySet();
	 Sound_Count=10;
  /*
  if (RX2Data[RX2Countertail][2]==0)
  {
    HNDLE_INFORMATION.SAVE_LED=Intensity[0];//LED�ȼ�
    DwinWriteWord(ADDR_BOOTINGLEDDATA,HNDLE_INFORMATION.SAVE_LED);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGLEDLINE,HNDLE_INFORMATION.SAVE_LED); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGLEDKEY,HNDLE_INFORMATION.SAVE_LED);//������ͨ�ź���
  }

    if (RX2Data[RX2Countertail][2]==2)
  {
    HNDLE_INFORMATION.SAVE_RF=Intensity[2];//��Ƶ�ȼ�
    DwinWriteWord(ADDR_BOOTINGRF,HNDLE_INFORMATION.SAVE_RF);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGRFLINE,HNDLE_INFORMATION.SAVE_RF); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGRFKEY,HNDLE_INFORMATION.SAVE_RF);//������ͨ�ź���
  }
  

    if (R_buf1[2]==3)
  {
     HNDLE_INFORMATION.SAVE_MOTO_SPEED=Intensity[3];//���ת�ٵȼ�
    DwinWriteWord(ADDR_BOOTINGMOTO_SPEEDDATA,HNDLE_INFORMATION.SAVE_MOTO_SPEED);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGMOTO_SPEEDLINE,HNDLE_INFORMATION.SAVE_MOTO_SPEED); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGMOTO_SPEEDKEY,HNDLE_INFORMATION.SAVE_MOTO_SPEED);//������ͨ�ź���
  }
  

    if (R_buf1[2]==4)
  {
    HNDLE_INFORMATION.SAVE_PRESS=Intensity[4];//��ѹ�ȼ�
    DwinWriteWord(ADDR_BOOTINGPRESSDATA,HNDLE_INFORMATION.SAVE_PRESS);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGPRESSLINE,HNDLE_INFORMATION.SAVE_PRESS); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGPRESSKEY,HNDLE_INFORMATION.SAVE_PRESS);//������ͨ�ź���
  }
  

    if (R_buf1[2]==5)
  {
    HNDLE_INFORMATION.SAVE_PRESS_IN=Intensity[5];//�����ȼ�
    DwinWriteWord(ADDR_BOOTINGPRESS_INDATA,HNDLE_INFORMATION.SAVE_PRESS_IN);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGPRESS_INLINE,HNDLE_INFORMATION.SAVE_PRESS_IN); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGPRESS_INKEY,HNDLE_INFORMATION.SAVE_PRESS_IN);//������ͨ�ź���
  }
  

    if (R_buf1[2]==6)
  {
    HNDLE_INFORMATION.SAVE_PRESS_OUT=Intensity[6];//�����ȼ�
    DwinWriteWord(ADDR_BOOTINGPRESS_OUTDATA,HNDLE_INFORMATION.SAVE_PRESS_OUT);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGPRESS_OUTLINE,HNDLE_INFORMATION.SAVE_PRESS_OUT); //��Ӧ��ַ ����д�����ֽ� д��������������ʾ
    DwinWriteWord(ADDR_BOOTINGPRESS_OUTKEY,HNDLE_INFORMATION.SAVE_PRESS_OUT);//������ͨ�ź���
  }
  

    if (R_buf1[2]==7)
  {
    HNDLE_INFORMATION.SAVE_MOTO_TOWARD=Intensity[7];//���ת��
    DwinWriteWord(ADDR_BOOTINGMOTO_TOWARDDATA,HNDLE_INFORMATION.SAVE_MOTO_TOWARD);//������ͨ�ź���
    DwinWriteWord(ADDR_BOOTINGMOTO_TOWARDKEY,HNDLE_INFORMATION.SAVE_MOTO_TOWARD);//������ͨ�ź���
  }
  delay_ms(10);
  */
  }
  else if(RX2Data[RX2Countertail][2]==7)//���ת�� 
  {
    Intensity[(RX2Data[RX2Countertail][2])]=RX2Data[RX2Countertail][3];
	//ModeSet();
	//cut_pic(0,28+Intensity[7],523,388,588,788,523,388);
	Sound_Count=10;
  }


  else if(RX2Data[RX2Countertail][2]==10)//��������
  {
    MACHINE_STATE.WORK_STATE=RX2Data[RX2Countertail][3];
	  Sound_Count=10;
    buff[0] = 0;//1���ֱ�
    buff[1] = MACHINE_STATE.WORK_STATE;
    DwinWriteLongWords(ADDR_HANDWORK_TO_ANDROID, buff, 2); //��������׿��
    delay_ms(10);
  }

  HNDLE_INFORMATION.SAVE_LED=Intensity[0];//LED�ȼ�
  HNDLE_INFORMATION.SAVE_INFRARED=Intensity[1];//����ȼ�
  HNDLE_INFORMATION.SAVE_RF=Intensity[2];//��Ƶ�ȼ�
  HNDLE_INFORMATION.SAVE_MOTO_SPEED=Intensity[3];//���ת�ٵȼ�
  HNDLE_INFORMATION.SAVE_PRESS=Intensity[4];//��ѹ�ȼ�
  HNDLE_INFORMATION.SAVE_PRESS_IN=Intensity[5];//����ʱ��
  HNDLE_INFORMATION.SAVE_PRESS_OUT=Intensity[6];//����ʱ��
  HNDLE_INFORMATION.SAVE_MOTO_TOWARD=Intensity[7];//���ת��
  //MACHINE_STATE.HANDLE_ID=Intensity[8]+1;//�ֱ�ID
  buff[0] = 0;//1���ֱ�
  buff[1] = Intensity[4];//��ѹ�ȼ�
  buff[2] = Intensity[5];//�����ȼ�
  buff[3] = Intensity[6];//�����ȼ�
  buff[4] =  Intensity[2] ;//RF�ȼ�
  buff[5] = Intensity[0];//LED�ȼ�
  buff[6] = Intensity[1];//����ȼ�
  buff[7] = Intensity[3];//���ת�ٵȼ�
  buff[8] = Intensity[7];//���ת��

  DwinWriteLongWords(ADDR_HANDPARAMETER_TO_ANDROID,buff,9);//������ͨ�ź���

          
  ModeSet();
  delay_ms(10);
  
  for(i=0;i<30;i++)
  {RX2Data[RX2Countertail][i]=0;}
  RX2Countertail++;
  if(RX2Countertail>10){RX2Countertail=0;}

  }
  
}
void Send_Data(void)
{
  while(T_count>0);
  T_buf[0]=0xaa;
  T_buf[1]=4;
  //T_buf[2]=Menu;
  //T_buf[3]=Intensity[Menu];
    T_buf[2]=0;
  T_buf[3]=Intensity[0];
  while(R_count1>0);
  TXD;
  T_ptr=1;
  T_count=T_buf[1];
  UDR1=T_buf[0];
}
void Send_Data8(void)
{
  while(T_count>0);
  T_buf[0]=0xaa;
  T_buf[1]=13;
  T_buf[2]=9;
  T_buf[3]=Intensity[0];
  T_buf[4]=Intensity[1];
  T_buf[5]=Intensity[2];
  T_buf[6]=Intensity[3];
  T_buf[7]=Intensity[4];
  T_buf[8]=Intensity[5];
  T_buf[9]=Intensity[6];
  T_buf[10]=Intensity[7];
  T_buf[11]=Intensity[8];
  T_buf[12]=WORKPAGE;
  while(R_count1>0);
  TXD;
  T_ptr=1;
  T_count=T_buf[1];
  UDR1=T_buf[0];
}
void Send_command(void)
{
  while(T_count>0);
  T_buf[0]=0xaa;
  T_buf[1]=4;
  T_buf[2]=10;
  T_buf[3]=MACHINE_STATE.WORK_STATE;
  while(R_count1>0);
  TXD;
  T_ptr=1;
  T_count=T_buf[1];
  UDR1=T_buf[0];
}
void Send_EN(void)
{
  while(T_count>0);
  T_buf[0]=0xaa;
  T_buf[1]=4;
  T_buf[2]=11;
  T_buf[3]=DisPage;
  while(R_count>0);
  TXD;
  T_ptr=1;
  T_count=T_buf[1];
  UDR1=T_buf[0];
}