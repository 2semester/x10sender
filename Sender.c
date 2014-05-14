#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FREQ 3686400 // ATmega32 Frequency
#define PRESCALER 1 
#define F_OUT 120000 // Output frequency
#define OCR0_VALUE 14 // 

void InitAtmel(void);
volatile unsigned char flag=0; 

//INT2 til 'flag'
ISR(INT2_vect)
{
	flag = 0x01;
}

ISR(TIMER0_COMP_vect)
{
	OCR0 = (uint8_t)OCR0_VALUE; 
}

void InitAtmel(void)
{
	DDRB |= (0<<PB2) | (0<<PB0); //Input for INT2 on PB2 & CTC PB0
	DDRC = 0xff;//Output for LEDs
}

void switchSetCTC(void)
{
	DDRB |=(1<<PB3);
	_delay_ms(1);
	PORTC = 0b01111111;
	_delay_ms(500);
	DDRB |=(0<<PB3);
}

//---------------------------------------------------------------
int main(void)
{
	flag  = 0x00;
	cli();
	
	InitAtmel();
	MCUCSR = 0b01000000;		// INT2:Rising edge
	GICR |= 0b00100000;		// Enable extern interrupts INT2
	TCCR0 = 0b01101001; // CTC - Mode 2 - No prescale
	DDRB |=(0<<PB3);
	TIMSK |=(1<<OCIE0);
	switchSetCTC();
	sei();
	
	while(1)
	{
		if(flag == 0x01)
		{
			PORTC = 0b11111101;
			_delay_ms(50);
			flag = 0x00;
		}
		else
		{
			PORTC =  0b11111111; //0x66;
			_delay_ms(50);
		}
		
		if((PINA & 0b10000000)==0)
		{
			switchSetCTC();
		}
		switch(OI)
			case 1: // 01
			
			break;
			
			case 2:
	}
}
