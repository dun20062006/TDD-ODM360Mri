#ifndef   __UART_H__
#define   __UART_H__
#define CHECKING BitTst(PINF,3)
void uart0_rx_isr(void);
void uart1_rx_isr(void);
void uart0_tx_isr(void);
void uart1_tx_isr(void);
void dispose_data(void);
void GetCheckingOr(void);
unsigned char  GetChecking(void);
void ShakeHands(void);
void set_color(unsigned int ForegColor,unsigned int BackColor);
void set_text_xy(unsigned char dx,unsigned char dy);
void get_color(unsigned char FB,unsigned int x,unsigned int y);
void cursor(unsigned char EN,unsigned int x,unsigned int y,unsigned char w,unsigned char h);
void print_text(unsigned char lib,unsigned int x,unsigned int y,unsigned char *text);
void print_texts(unsigned int x,unsigned int y,unsigned char lib,unsigned char mode,unsigned char dots,unsigned int Fcolor,unsigned int Bcolor,unsigned char *text);
void print_consttexts(unsigned int x,unsigned int y,unsigned char lib,unsigned char mode,unsigned char dots,unsigned int Fcolor,unsigned int Bcolor,const unsigned char *text);
void textsize_enable(unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye);
void textsize_disable(void);
void Painting_dot(unsigned char CMD,unsigned int x,unsigned int y);
void Painting_dots(unsigned char CMD,unsigned char argc,unsigned int *argv,unsigned int x,unsigned int y);
void Painting_line(unsigned char CMD,unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye);
void Set_screen(void);
void clear_screen(void);
void Chack_screen(void);
void PicRam(unsigned char CMD,unsigned char RAM_POS);
void dis_pic(unsigned char pic_ID);
void cut_pic(unsigned char CMD,unsigned char pic_ID,unsigned int Xs,unsigned int Ys,unsigned int Xe,unsigned int Ye,unsigned int X,unsigned int Y);
void buzzer(unsigned char time);
void clock_off(void);
void get_time(void);
void clock_on(unsigned char RTC_mode,unsigned char Text_mode,unsigned int Color,unsigned int X,unsigned int Y);
void clock_set(unsigned char YY,unsigned char MO,unsigned char DD,unsigned char HH,unsigned char MM,unsigned char SS);
void GetUSB(void);
void Up_Pic(void);
void dispose_data(void);
void Send_Data(void);
void Send_Data8(void);
void Send_command(void);
void Send_EN(void);
/*HAO****************************************************/
//#define true 1
//#define false 0
void DwinToPage(unsigned char pageIndex);
void DwinWriteWord(unsigned int addr, unsigned int data);
void DwinWriteLongWords(unsigned int addr, unsigned char *p, unsigned char length);
unsigned int CheckCRC16(unsigned char *buff, unsigned char length);
void DefaultSetting(void);
/*HAO****************************************************/

#endif