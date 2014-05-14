#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

void InitAtmel(void);
volatile unsigned char flag=0; //

//INT2 til 'flag'
ISR(INT2_vect)
{
	flag = 0x01;
}


void InitAtmel(void)
{
	DDRB = 0x00;//Input for INT2 on PB2
	DDRC = 0xff;//Output for LEDs
}

//---------------------------------------------------------------
int main(void)
{
	flag  = 0x00;
	cli();
	
	InitAtmel();
	MCUCSR = 0b01000000;		// INT2:Rising edge
	GICR |= 0b00100000;		// Enable extern interrupts INT2
	sei();

	while(1)
	{
		if(flag == 0x01)
		{
			PORTC = 0b10111111;
			_delay_ms(50);
			flag = 0x00;
		}
		if(flag1 == 0x01)
		{
			PORTC = 0b11011111;
			_delay_ms(50);
			flag1 = 0x00;
		}
		else
		{
			PORTC =  0b11111111; //0x66;
			_delay_ms(50);
		}
	}
}
