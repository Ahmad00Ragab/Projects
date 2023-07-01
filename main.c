/******************************************************************************
 * File Name: main.c
 *
 * Description: A Program to Design A STOP WATCH
 *
 * Author: Ahmad Ragab Mohamed
 *
 * Date :  JULY 1 2023
 *******************************************************************************/

#include "timer1.h"
#include "External_Interrupts.h"
#include <util/delay.h>

extern volatile uint8 SECOND;
extern volatile uint8 MINUTE;
extern volatile uint8 HOUR;

/* a function to increment the seconds every compare match or every second */
void Increment_Watch(void)
{
	SECOND++;
		if(SECOND == 60)
		{
			SECOND = 0;
			MINUTE++;
			if(MINUTE == 60)
			{
				MINUTE = 0;
				HOUR++;
				if(HOUR == 24)
				{
					SECOND = 0;
					MINUTE = 0;
					HOUR = 0;
				}
			}
		}
}

/* a function to pause the time on the 7-segment display */
void Pause_Watch(void)
{
	TCCR1B = (TCCR1B & 0xF8) | (NO_CLOCK);
}

/* a function to resume the time on the 7-segment display after pause */
void Resume_Watch(void)
{
	TCCR1B = (TCCR1B & 0xF8) | (PRESCALER_1024);
}
/* a function to reset the stop watch and make it count from 0 */
void Reset_Watch(void)
{
	SECOND = 0;
	MINUTE = 0;
	HOUR = 0;
}

int main(void)
{

	/* configure the common anode pins controllers as output pins */
	GPIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN3_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN4_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID, PIN5_ID, PIN_OUTPUT);
	/*configure the pins that we send the number on as output pins */
	GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID, PIN3_ID, PIN_OUTPUT);
    PORTC = PORTC |(0xF0);
    Set_CallBack(Increment_Watch);
    External_Interrupt_set_CallBack(Reset_Watch,0);
    External_Interrupt_set_CallBack(Pause_Watch,1);
    External_Interrupt_set_CallBack(Resume_Watch,2);
    INT0_init(FALLING);
    INT1_init(RAISING);
    INT2_init(FALLING);
    PORTB |= (1 <<PB2);                 /* activate internal pull_up resistor for PB2 */
    PORTD |= (1 <<PD2);                 /* activate internal pull_up resistor for PB2 */
	TIMER1_Init_CTC_Mode(977,NORMAL_PORT,PRESCALER_1024,ENABLE_INTERRUPT);
	while(1)
	{
		PORTA = (1<<0);                             /* Turn on the First 7-segment by setting its common pin and Turn off rest */
		PORTC = SECOND % 10 ;                       /* display the first digit of the value of the Seconds */
		_delay_us(10);
		PORTA = (1<<1);                             /* Turn on the Second 7-segment by setting its common pin and Turn off rest */
		PORTC = SECOND / 10;                        /* display the Second digit of the value of the Seconds */
		_delay_us(10);
		PORTA = (1<<2);                             /* Turn on the Third 7-segment by setting its common pin and Turn off rest */
		PORTC = MINUTE % 10;                        /* display the First digit of the value of the Minutes */
		_delay_us(10);
		PORTA = (1<<3);                             /* Turn on the Fourth 7-segment by setting its common pin and Turn off rest */
		PORTC = MINUTE / 10;                        /* display the Second digit of the value of the Minutes */
		_delay_us(10);
		PORTA = (1<<4);                             /* Turn on the Fifth 7-segment by setting its common pin and Turn off rest */
		PORTC = HOUR % 10;                          /* display the First digit of the value of the Hours */
		_delay_us(10);
		PORTA = (1<<5);                             /* Turn on the sixth 7-segment by setting its common pin and Turn off rest */
		PORTC = HOUR / 10;                          /* display the Second digit of the value of the Hours */
		_delay_us(10);
	}

}
