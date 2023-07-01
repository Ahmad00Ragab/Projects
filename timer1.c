/******************************************************************************
 * File Name: timer1.c
 *
 * Description: Source File for TIMER1 Driver
 *
 * Author: Ahmad Ragab Mohamed
 *
 * Date :  JULY 1 2023
 *******************************************************************************/

#include "timer1.h"

/*******************************************************************************
 *                               Global_Variables Declaration                             *
 *******************************************************************************/
volatile uint8 Counter_Compare_Mode = 0;
volatile uint8 Counter_Normal_Mode = 0;
volatile uint8 Counter_PWM_Mode = 0;

volatile uint8 SECOND  = 0;
volatile uint8 MINUTE  = 0;
volatile uint8 HOUR    = 0;

static volatile void(* CallBack_Ptr)(void) = NULL_PTR;
/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{


}



ISR(TIMER1_COMPB_vect)
{


}

ISR(TIMER1_CAPT_vect)
{


}

ISR(TIMER1_COMPA_vect)
{
	(* CallBack_Ptr)();
}


/*
 * Description:
 * Initialize TIMER0 in Clear timer on compare match(CTC) mode
 * returns: void
 */
void TIMER1_Init_CTC_Mode(uint16 Compare_Value,CTC_Output_Mode OutPutPin_Mode
		                 ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT1 = 0;
	OCR1A  = Compare_Value;
	TCCR1A |=(1 << FOC1A) ;
	TCCR1B |= (1 << WGM12);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	TCCR1A = (TCCR0 & 0x3F) | (OutPutPin_Mode << 6);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE1A);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE1A);
		SREG |= (1 << 7);
	}
	else
	{

	}

}
/*
 * Description:
 * Initialize TIMER0 in pulse width modulation generation(PWM)mode
 * returns: void
 */
void TIMER1_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{

	TCNT1 = 0;
	OCR1A  = Compare_Value;
	TCCR1A |= (1<<WGM00)|(1 <<WGM01);
	TCCR1B |= (1<<WGM12)|(1 <<WGM13);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	TCCR1A = (TCCR1B & 0x3F) | (OutPutPin_Mode << 6);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE1A);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE1A);
		SREG |= (1 << 7);
	}
	else
	{

	}
}

/*
 * Description:
 * Initialize TIMER0 in Normal or Overflow mode
 * returns: void
 */
void TIMER1_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT1 = 0;
	TCCR1A |= (1 << FOC1A);
	TCCR1B = (TCCR1B & 0xF8) | (Prescaler);
	if(Interrupt_Choice == DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,TOIE1);
	}
	else if(Interrupt_Choice == ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,TOIE1);
		SREG |= (1 << 7);
	}
	else
	{

	}
}

/* SET CallBack For a Function in the Application Layer
 * takes the address of the requied function to be
 * executed in ISR or Timer1_CTC_COMPA Mode
 * */
void Set_CallBack(void(* ptr_2_fun)(void))
{
	CallBack_Ptr = ptr_2_fun;
}

void TIMER1_Init_ICU_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{

}
