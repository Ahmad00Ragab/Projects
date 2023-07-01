/******************************************************************************
 * File Name: gpio.c
 *
 * Description: source file for the GPIO Driver
 *
 * Author: Ahmad Ragab Mohamed
 *
 * Date :  July 1 2023
 *******************************************************************************/


#include "gpio.h"   /* include the header file for the GPIO Driver */
#include "common_macros.h"


/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction)
{
	if((port_num >= Max_NUM_Of_PORTS) || (pin_num >=  MAX_NUM_Of_PINS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}

	}
}

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if((port_num >= Max_NUM_Of_PORTS))
		{
			/* Do Nothing */
		}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRA = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value)
{
	if((port_num >= Max_NUM_Of_PORTS) || (pin_num >=  MAX_NUM_Of_PINS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}

	}
}

void GPIO_writePort(uint8 port_num,uint8 value)
{
	if((port_num >= Max_NUM_Of_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

uint8 GPIO_readPin(uint8 port_num,uint8 pin_num)
{
	uint8 READ_PIN = LOGIC_LOW ;
	if((port_num >= Max_NUM_Of_PORTS) || (pin_num >=  MAX_NUM_Of_PINS))
		{
			/* Do Nothing */
		}
		else
		{
			switch(port_num)
			{
			case PORTA_ID:
				if(BIT_IS_SET(PINA,pin_num))
				{
					READ_PIN = LOGIC_HIGH;
				}
				else
				{
					READ_PIN = LOGIC_LOW;
				}
				break;
			case PORTB_ID:
				if(BIT_IS_SET(PINB,pin_num))
				{
					READ_PIN = LOGIC_HIGH;
				}
				else
				{
					READ_PIN = LOGIC_LOW;
				}
				break;
			case PORTC_ID:
				if(BIT_IS_SET(PINC,pin_num))
				{
					READ_PIN = LOGIC_HIGH;
				}
				else
				{
					READ_PIN = LOGIC_LOW;
				}
				break;
			case PORTD_ID:
				if(BIT_IS_SET(PIND,pin_num))
				{
					READ_PIN = LOGIC_HIGH;
				}
				else
				{
					READ_PIN = LOGIC_LOW;
				}
				break;
			}
		}
	return READ_PIN;
}

uint8 GPIO_readPort(uint8 port_num)
{
	uint8 READ_PORT = LOGIC_LOW ;
	if((port_num >= Max_NUM_Of_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			READ_PORT = PINA;
			break;
		case PORTB_ID:
			READ_PORT = PINB;
			break;
		case PORTC_ID:
			READ_PORT = PINC;
			break;
		case PORTD_ID:
			READ_PORT = PIND;
			break;
		}

	}
	return READ_PORT;
}
