CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega128  -l -g -Wa-IC:\icc -MLongJump -MHasMul -MEnhanced -Wf-use_elpm -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -LC:\icc\lib -g -e:0x20000 -ucrtatmega.o -bfunc_lit:0x8c.0x20000 -dram_end:0x10ff -bdata:0x100.0x10ff -dhwstk_size:128 -beeprom:0.4096 -fihx_coff -S2
FILES = app.o def.o Init.o isr.o main.o task.o uart.o 

ANDROID360:	$(FILES)
	$(CC) -o ANDROID360 $(LFLAGS) @ANDROID360.lk   -lcatm128
app.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
app.o:	App\app.c
	$(CC) -c $(CFLAGS) App\app.c
def.o:
def.o:	App\def.c
	$(CC) -c $(CFLAGS) App\def.c
Init.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
Init.o:	App\Init.c
	$(CC) -c $(CFLAGS) App\Init.c
isr.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
isr.o:	App\isr.c
	$(CC) -c $(CFLAGS) App\isr.c
main.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
main.o:	App\main.c
	$(CC) -c $(CFLAGS) App\main.c
task.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
task.o:	App\task.c
	$(CC) -c $(CFLAGS) App\task.c
uart.o: .\App\includes.h C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h C:\iccv7avr\include\eeprom.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\APP\APP.H .\APP\INIT.H .\APP\UART.H .\APP\TASK.H .\APP\ISR.H .\APP\DEF.H .\APP\EEPROMADDR.H
uart.o:	App\uart.c
	$(CC) -c $(CFLAGS) App\uart.c
