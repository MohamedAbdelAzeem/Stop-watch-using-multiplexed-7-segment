/*
 * Ex_Int.c
 *
 *  Created on: Oct 19, 2020
 *      Author: ZAMALA
 */

#include <avr/io.h>

#include "Int_init.h"
#include "operations.h"

void INT0_init(void)
{
	SET_BIT(GICR, INT0);
	SET_BIT(MCUCR, ISC01);
	CLEAR_BIT(MCUCR, ISC00);
}
void INT1_init(void)
{
	SET_BIT(GICR, INT1);
	SET_BIT(MCUCR, ISC11);
	SET_BIT(MCUCR, ISC10);

}

void INT2_init(void)
{
	SET_BIT(GICR, INT2);
	CLEAR_BIT(MCUCSR, ISC2);
}


void Timer1_init(void)
{
	//timer interrupts
	TIMSK = (1<< OCIE1A); //timer module interrupt Enable
	//F_cpu = 1Mhz
	TCCR1A = (1 << FOC1A) ;
	TCCR1B = (1<<CS10) |(1<<CS12)|(1<<WGM12) ; //CLK/1024
	TCNT1 = 0x00; //initial value 0
	//T_timer = 1 u_sec
	OCR1A = SECOND; //compare match every one second
}




