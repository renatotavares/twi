#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// teste
#include "twi.h"

uint8_t twi_scanner(uint8_t address);

int main(void)
{
	
	sei();
	
	twi_init();
	twi_start();
	twi_write_address( (0x8<<1) | TW_WRITE);
	twi_write_data('R');
	twi_write_data('E');
	twi_write_data(24);
	twi_stop();
	
	_delay_ms(100);
	
	twi_init();
	twi_start();
	twi_read_address((0x8<<1) | TW_READ);
	twi_read_data();
	twi_read_data();
	twi_read_data();
	twi_read_data();
	twi_read_data();
	
	twi_stop();
	
	while(1);
	
}

