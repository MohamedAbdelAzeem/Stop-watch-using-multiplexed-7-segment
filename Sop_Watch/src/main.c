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

void Pins_init(void);
void print_num();



/*********************main***********************/
int main(void)
{
	SET_BIT(SREG,7);
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

ISR(INT0_vect)
{
	int i = 0;
	for(; i< 6 ;i++)
	{
		digits[i] = 0 ;
	}
}

ISR(INT1_vect)
{
	//stop clk
	TCCR1B = 0;
	CLEAR_BIT(TCCR1A, FOC1A);
}

ISR(INT2_vect)
{
	TCCR1A = (1 << FOC1A) ;
	TCCR1B = (1<<CS10) |(1<<CS12)|(1<<WGM12) ; //CLK/1024
}

ISR(TIMER1_COMPA_vect)
{
	digits[0]++;
	if(digits[0] == 10)
	{
		digits[0] = 0 ;
		digits[1]++;
	}
	if(digits[1] == 6)
	{
		digits[1] =0 ;
		digits[2]++;
	}
	if(digits[2] == 10)
	{
		digits[2] = 0 ;
		digits[3]++;
	}
	if(digits[3] == 6)
	{
		digits[3] =0 ;
		digits[4]++;
	}
	if(digits[4] == 10)
	{
		digits[4] =0 ;
		digits[5]++;
	}
	if(digits[5] == 6)
	{
		digits[5] =0 ;
	}
}
/******************************************************/

/*****************a Pins initialization *****************/
void Pins_init(void)
{
	//initializing output pins
	int i = PC0;
	int j = PA0;
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
	int k = 0 ;
	int i = PA0;
	PORTA = 0x00;
	for(; i<=PA5 ;i++)
	{
		SET_BIT(PORTA,i);
		PORTC = digits[k];
		k++;
		_delay_ms(2);
		CLEAR_BIT(PORTA,i);
	}
}