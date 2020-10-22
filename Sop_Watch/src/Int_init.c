/*
 * Ex_Int.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Mohamed AbdelAzeem
 *
 *
 */

#define SECOND 1000

#include <avr/io.h>
#include "Int_init.h"
#include "operations.h"

/* External INT0 Interrupt Initialization:
 * Trigger INT0 with the raising edge
 */
void INT0_init(void)
{
	SET_BIT(GICR, INT0);     // Enable external interrupt pin INT0
	SET_BIT(MCUCR, ISC01);
	CLEAR_BIT(MCUCR, ISC00);
}
/* External INT1 Interrupt Initialization:
 * Trigger INT1 with the Falling edge
 */
void INT1_init(void)
{
	SET_BIT(GICR, INT1);	// Enable external interrupt pin INT1
	SET_BIT(MCUCR, ISC11);
	SET_BIT(MCUCR, ISC10);

}

/* External INT2 Interrupt Initialization:
 * Trigger INT0 with the Falling edge
 */
void INT2_init(void)
{
	SET_BIT(GICR, INT2);    // Enable external interrupt pin INT2
	CLEAR_BIT(MCUCSR, ISC2);
}

/* Timer1  Interrupt Initialization :
 *  F_cpu = 1Mhz
 *  Prescaler = 1024
 *  initial value = 0
 *  Compare value = 1000
 */
void Timer1_init(void)
{
	CLEAR_BIT(SREG,7); 			// Disable interrupts by clearing I-bit
	SET_BIT(TIMSK, OCIE1A); 	 //timer module interrupt Enable
	TCCR1A = (1 << FOC1A) ;  	//Force output compare bit = 1
	TCCR1B = (1<<CS10) |(1<<CS12)|(1<<WGM12) ; //CLK/1024
	TCNT1 = 0x00; 				//initial value 0
	OCR1A = SECOND; 			//compare match every one second
	SET_BIT(SREG, 7 );			// Enable interrupts by setting I-bit
}




