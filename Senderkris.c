#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h> //itoa 


#define FREQ 3686400 // ATmega32 Frequency
#define F_OUT 120000 // desired Output frequency
#define OCR0_VALUE ((((FREQ/2)/1)/F_OUT)-1)// 0x1e set the ocr0 register value to mimic 120khz cycel (118916.1310 Hz) actual frequence
 
void InitAtmel(void);
volatile unsigned char flag=0; //the value stored in this variable might change without my code doing anything


ISR(INT2_vect)	//INT2 til 'flag'
{
	flag = 0x01;
	// kan måske laves til en "tunnel" fra interruptet uden om main. 
}

ISR(TIMER0_COMP_vect)
{
	OCR0 = (uint8_t)OCR0_VALUE;// sets OCR value from above formula in usingned int 8bit value.
}

void InitAtmel(void)
{
	DDRB |= (0<<PB2) | (0<<PB0);// Input for INT2 on PB2 & CTC PB0
	DDRC = 0xff;				// Output for LEDs
	MCUCSR = 0b01000000;		// INT2:Rising edge
	GICR |= 0b00100000;			// Enable extern interrupts INT2
	TCCR0 = 0b01101001;			// CTC - Mode 2 - No prescale
	TCNT0 = 0;					// CTC - couter initial value
	TIMSK |=(1<<OCIE0);			// CTC - counter compare interrupt
	flag  = 0x00;				// interrupt flag set to  initial value. 
	sei();						// enable global interrupts
}
void CTCBurst(void)
{
	PORTC ^= (1 << 0);			// XOR toggle portC 
}

void switchSetCTC(void)
{
	DDRB |=(1<<PB3);
	_delay_ms(1);
	PORTC = 0b01111111;
	_delay_ms(500);
	DDRB |=(0<<PB3);
}

char CovertToBinary(char *Buffer)
{
	char Binary [9]; // 8bit +1 
	itoa(*Buffer, Binary, 2); // convert buffer char til 8bit binær char array
	return Binary;
}

//---------------------------------------------------------------
int main(void)
{
	InitAtmel();
	switchSetCTC();
	
	
	while(1)
	{

		if(TCNT0 >= OCR0_VALUE)
		{
			CTCBurst();
		}
		
		
	// CHECK OM DET VIRKER!		
	
	switch(OI)
		case '1': // 10 = 1
			if (flag == 0x01) 
			{
			// burst 1 code.
			flag = 0x00;
			}
		break;
		
		case '0':
			if (flag == 0x01)
			{
				// burst 0 code	
			}
		break;
	}			
}
