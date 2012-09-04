/*
 * Dallas/Maxim 1-Wire library
 * d1w.c
 * https://github.com/hberg539/avr-gcc-libs
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define D1W_DDR		DDRC
#define D1W_PORT	PORTC
#define D1W_PIN		PINC
#define D1W_DQ		PINC3

void d1w_init() {
	
	// set DDR to output
	D1W_DDR |= (1 << D1W_DQ);
	
	// put signal low
	D1W_PORT &= (1 << D1W_DQ);
	
	// wait at least 480us
	_delay_us(500);
	
	// release by DDR to input
	D1W_DDR &= ~(1 << D1W_DQ);
	
	// wait at least 60+240us
	_delay_us(310);
}

void d1w_write(uint8_t data) {
	
	for (uint8_t i = 0; i < 8; i++) {
		
		// set DDR to output
		D1W_DDR |= (1 << D1W_DQ);
		
		// write 1
		if (data & (1 << i)) {
			
			// put signal low
			D1W_PORT &= ~(1 << D1W_DQ);
			
			// relase within 15us
			_delay_us(5);
			
			// release by DDR to input
			D1W_DDR &= ~(1 << D1W_DQ);
			
			// wait at least 60us
			_delay_us(60);
			
		// write 0
		} else {
			
			// put signal low
			D1W_PORT &= ~(1 << D1W_DQ);
			
			// hold down for at least 60us
			_delay_us(65);
			
			// release by DDR to input
			D1W_DDR &= ~(1 << D1W_DQ);
		}
		
		// wait at least 1us (recovery time)
		_delay_us(1);
	}
}

uint8_t d1w_read() {
	
	uint8_t data = 0x00;
	
	for (uint8_t i = 0; i < 8; i++) {
		
		// set DDR to output
		D1W_DDR |= (1 << D1W_DQ);
	
		// put signal low
		D1W_PORT &= ~(1 << D1W_DQ);
	
		// hold down for at least 1us
		_delay_us(1);
	
		// release by DDR to input
		D1W_DDR &= ~(1 << D1W_DQ);
	
		// wait
		_delay_us(10);
	
		// read 1 (high)
		if (D1W_PIN & (1 << D1W_DQ)) {
			data |= (1 << i);
			
		//  read 0 (low)
		} else {
			
			data &= ~(1 << i);
			
			// wait until high
			//while (D1W_PIN & (1 << D1W_DQ));
		}
		
		// total slot at least 60us
		_delay_us(55);
	}
	
	return data;
}