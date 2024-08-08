#ifndef  __APP_H
#define  __APP_H


typedef struct KEY
{
  unsigned int  XS;
  unsigned int  YS;
  unsigned int  XE;
  unsigned int  YE;
};
void delay_ms(unsigned int i);
void DataSynchronization(void);
void DisCount(void); 
void Dis_pressure(void);

void DisFunctionKey(unsigned char K,unsigned char CMD);
void DisWelcome(void);
void DisWork(void);
void DisHandpiece(void);
void DisMode(void);
unsigned char GetKeyID(const struct KEY *P,unsigned char Len);
void Key(void);
void DisMV(void);
void HandpieceKey(void);
void IntensitySet(void);
void HandpieceSet(void);
void DisIntensity(unsigned char ID);
void ModeSet(void);
#endif