//==== RS232 =================================================================
#include "neco.h"

//pro jistotu, v hlavnim souboru to bylo 
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>


volatile unsigned char serial_bytes;

void serial_baudrate (unsigned long int new_baudrate)
{
	unsigned int ubrr = 0;
	// předpoklad U2X = 0

	switch (new_baudrate)
	{
		case 9600:
			ubrr = 51;
			break;
		default:
		case 115200:
			ubrr = 3;
			break;
	}

		// zápis do 16 bit registru
		UBRRH = (unsigned char) (ubrr >> 8);
		UBRRL = (unsigned char) (ubrr);
}

int serial_init()
{
	unsigned char i;

	serial_baudrate (9600); //115200

	// set registers
	UCSRA = 0x20;	// 0010 0010 (RXC, TXC, UDRE, FE, DOR, PE, U2X, MPCM)
	UCSRB = (1 << RXEN) | (1 << TXEN);	// enable receiver, enable transmitter
	UCSRC = (1 << UMSEL) | (0 << USBS) | (3 << UCSZ0);	// 8 data, 2 stop bits
	
	// vyprázdnění bufferu připojeného PC
	// while (UCSRA & (1 << RXC)) i = UDR;
}

void serial_putc (unsigned char c)
{
	// čekej dokud není volný registr k odeslání znaku
	while(!(UCSRA & (1 << UDRE)));
	
	// zápisem do registru UDR odešli znak
	UDR = c;
}

void serial_puts (char *s)
{
	//  opakuj dokud není *s != NULL
	while (*s)
	{
		serial_putc(*s);
		s++;
	}
}

