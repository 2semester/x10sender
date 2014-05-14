#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

void InitAtmel(void);
volatile unsigned char flag=0; // 
volatile unsigned char flag1=0; //

//INT0 til 'flag'
ISR(INT0_vect)
{
	flag = 0x01;
}

//INT1 til 'flag1'
ISR(INT1_vect)
{
	flag1 = 0x01;	
}

void InitAtmel(void)
{
	DDRD = 0x00;//Input for INT0 on PD2 & INT1 on PD3
	DDRC = 0xff;//Output for LEDs
}

//---------------------------------------------------------------
int main(void)
{
	flag  = 0x00;
	flag1 = 0x00;
	cli();
	
	InitAtmel();
	MCUCR = 0b00001011;		// INT0:Rising edge, INT1:Falling edge
	GICR |= 0b11000000;		// Enable extern interrupts INT0 og INT1
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
