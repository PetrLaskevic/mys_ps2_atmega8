#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <inttypes.h>
#include "ioconfig.h"
#include "ps2.h"
#include "mouse.h"
#include </home/petr/Documents/zkompilujeSeTo/neco.h> //kdyz tam nedam absolute path, tak to avr-gcc nevidi: 
//takto:
//petr@petr-Lenovo-V320-15IAP-Desktop:~/Documents/zkompilujeSeTo$ make
//avr-gcc -g -O0 -mmcu=atmega8 -c mainMujMod.c -o mainMujMod.o
//mainMujMod.c:8:18: fatal error: neco.h: No such file or directory
// #include <neco.h>
//                  ^
//compilation terminated.
//make: *** [Makefile:12: mainMujMod.o] Error 1
//petr@petr-Lenovo-V320-15IAP-Desktop:~/Documents/zkompilujeSeTo$ ls
//mainMujMod.c    mainMujMod.hex  mainMujMod.map  Makefile     neco.c
//mainMujMod.elf  mainMujMod.lst  mainMujMod.o    nasserial.o  neco.h

/// Fresh movement packet, raw
MouseMovt   movt_packet;

/// Decoded movement packet
DecodedMovt movt;

int main(){
    uint8_t byte;
    uint8_t i;
    serial_init();
    serial_init ();
    serial_baudrate (9600); //115200
    serial_puts("jo\n");
    io_init();
    serial_puts("mame io\n");
    ps2_init();
    serial_puts("2\n");
    sei(); // enable interruptsk
    serial_puts("3\n");
    byte = mouse_boot();
    serial_puts("4\n");
    for(i = 0;;){
       if (ps2_avail()) {
            serial_puts("in ps2 avail\n");
            byte = ps2_getbyte();
        } 
    }

    return 0;
}
