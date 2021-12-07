# makfile configuration
COMMON_OBJECTS 		= wakedemo.o led.o switches.o p2_interrupt_handler.o buzzer.o 
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS			= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *.h~ *.c~ *~

wakedemo.o: led.h switches.h buzzer.h
led.o: led.h
switches.o: switches.h led.h
p2_interrupt_handler.o: switches.h
buzzer.o: buzzer.h
#stateMachines.o: stateMachines.h led.h switches.h buzzer.h
#wdInterruptHandler.o: led.h stateMachines.h
