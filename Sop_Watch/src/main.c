/*
 * main.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Mohamed AbdelAzeem
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "operations.h"
#include "Int_init.h"


unsigned char digits[6] = {0};
/*
 * digits[0] => seconds ones
 * digits[1] => seconds tens
 * digits[2] => minutes ones
 * digits[3] => minutes tens
 * digits[4] => hours   ones
 * digits[5] => hours   tens
 */

void Pins_init(void);
void print_num();

/*********************main***********************/
int main(void)
{
	SET_BIT(SREG,7); 	// Enable interrupts by setting I-bit
	Pins_init();
	INT0_init();
	INT1_init();
	INT2_init();
	Timer1_init();
	while(1)
	{
		print_num();
	}
	return 0;
}

/**********************ISR*******************/
/* External INT0 Interrupt Service Routine */
ISR(INT0_vect)
{
	int i = 0;
	for(; i< 6 ;i++)
	{
		digits[i] = 0 ;
	}
}

/* External INT1 Interrupt Service Routine */
ISR(INT1_vect)
{
	//Turn OFF the Clock
	TCCR1B = 0;
	CLEAR_BIT(TCCR1A, FOC1A);
}
/* External INT2 Interrupt Service Routine */
ISR(INT2_vect)
{
	//Turn ON the Clock
	TCCR1A = (1 << FOC1A) ;
	TCCR1B = (1<<CS10) |(1<<CS12)|(1<<WGM12) ; //CLK/1024
}

/* Timer1 Interrupt Service Routine */
ISR(TIMER1_COMPA_vect)
{
	digits[0]++;
	if(digits[0] >= 10)
	{
		digits[0] = 0 ;
		digits[1]++;
	}
	if(digits[1] >= 6)
	{
		digits[1] =0 ;
		digits[2]++;
	}
	if(digits[2] >= 10)
	{
		digits[2] = 0 ;
		digits[3]++;
	}
	if(digits[3] >= 6)
	{
		digits[3] =0 ;
		digits[4]++;
	}
	if(digits[4] >= 10)
	{
		digits[4] =0 ;
		digits[5]++;
	}
	if(digits[5] > 9 )
	{
		digits[5] = 0;
	}
}
/******************************************************/

/***************** Pins initialization *****************/
void Pins_init(void)
{
	//initializing output pins
	unsigned char i = PC0;
	unsigned char j = PA0;
	for(; i <= PC3;i++)
	{
		SET_BIT(DDRC, i);
	}
	for(; j<= PA5;j++)
	{
		SET_BIT(DDRA, j);
	}
	//initializing input pins
	CLEAR_BIT(DDRD, PD2);
	SET_BIT(PORTD, PD2); //INTERNAL PULL UP

	CLEAR_BIT(DDRD, PD3);

	CLEAR_BIT(DDRB, PB2);
	SET_BIT(PORTB, PB2); //INTERNAL PULL UP

}

/************ Print number ************************/
void print_num()
{
	unsigned char digit_index = 0 ;
	unsigned char pin_index = PA0;
	PORTA = 0x00;    //Disable all pins
	for(; pin_index <=PA5 ; pin_index++)
	{
		SET_BIT(PORTA, pin_index); //Enable one pin at a time
		PORTC = digits[digit_index]; //print digit
		digit_index++;
		_delay_ms(2);
		CLEAR_BIT(PORTA, pin_index);//disable pin
	}
}
