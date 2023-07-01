/******************************************************************************
 * File Name: timer1.h
 *
 * Description: Header File for TIMER1 Driver
 *
 * Author: Ahmad Ragab Mohamed
 *
 * Date : July 1 2023


 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "gpio.h"
#include <avr/interrupt.h>



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NORMAL_PORT,
	TOGGLE_OC1A,
	CLEAR_OC1A,
	SET_OC1A,
}CTC_Output_Mode;

typedef enum
{
	Normal_Port,
	Toggle_OC1A ,
	NON_INVERTING,
	INVERTING,
}PWM_Output_Mode;

typedef enum
{
	NO_CLOCK,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING,
}Clock_Pescaler;

typedef enum
{
	DISABLE_INTERRUPT,
	ENABLE_INTERRUPT,
}INTERRUPT_SELECT;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description:
 * Initialize TIMER1 in Clear timer on compare match(CTC) mode
 * returns: void
 */
void TIMER1_Init_CTC_Mode(uint16 Compare_Value,CTC_Output_Mode OutPutPin_Mode
		                 ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);

/*
 * Description:
 * Initialize TIMER0 in pulse width modulation generation(PWM)mode
 * returns: void
 */
void TIMER1_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);


/*
 * Description:
 * Initialize TIMER0 in Normal or Overflow mode
 * returns: void
 */
void TIMER1_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);


/*
 * Description:
 * Initialize TIMER1 in ICU mode
 * returns: void
 */
void TIMER1_Init_ICU_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);

#endif /* TIMER1_H_ */
