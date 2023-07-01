/*===========================================================================================
 * Filename   : External_Interrupts.c
 * Author     : Ahmad Ragab Mohamed
 * Description: Source file the Externa_Interrupts Driver
 * Created on : Jun 12, 2023
 *
 *==========================================================================================*/

#include "External_Interrupts.h"

void INT0_init(EDGE_TYPE EDGE)
{
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT); /* set PD2 input pin */
	if(EDGE == FALLING)
	{
		SET_BIT(MCUCR,ISC01);  /* Make INT0 happen with Falling Edge */

	}
	else if(EDGE == RAISING)
	{
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);  /* Make INT0 happen with Raising Edge */
	}
	SET_BIT(GICR,INT0);    /* Enable INT0 */
	SET_BIT(SREG,7); /* Enable Global Interrupt Enable */
}


void INT1_init(EDGE_TYPE EDGE)
{
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT); /* set PD2 input pin */
	if(EDGE == FALLING)
	{
		SET_BIT(MCUCR,ISC11);  /* Make INT1 happen with Falling Edge */

	}
	else if(EDGE == RAISING)
	{
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);  /* Make INT0 happen with Raising Edge */
	}
	SET_BIT(GICR,INT1);        /* Enable INT1 */
	SET_BIT(SREG,7);           /* Enable Global Interrupt Enable */
}

void INT2_init(EDGE_TYPE EDGE)
{
	GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT); /* set PD2 input pin */
	if(EDGE == FALLING)
	{
		CLEAR_BIT(MCUCSR,ISC2);
	}
	else if(EDGE == RAISING)
	{
		SET_BIT(MCUCSR,ISC2);    /* Make INT2 happen with Raising Edge */
	}
	SET_BIT(GICR,INT2);          /* Make INT1 happen with Raising Edge */
	SREG   |= (1<<7);           // Enable interrupts by setting I-bit
}

/* INTERRUPT HANDLER FOR INT0 */
ISR(INT0_vect)
{
	(*funcArray[0])();   /* Call the Function that is required to be Executed when INT0 happens */
}

/* INTERRUPT HANDLER FOR INT1 */
ISR(INT1_vect)
{
	(*funcArray[1])();   /* Call the Function that is required to be Executed when INT1 happens */
}

/* INTERRUPT HANDLER FOR INT2 */
ISR(INT2_vect)
{
	(*funcArray[2])();   /* Call the Function that is required to be Executed when INT2 happens */
}


void External_Interrupt_set_CallBack(void(*ptr_2_fun)(void),uint8 index)
{
	funcArray[index] = ptr_2_fun;
}
