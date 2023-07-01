/*===========================================================================================
 * Filename   : External_Interrupts.h
 * Author     : Ahmad Ragab Mohamed
 * Description: header file the Externa_Interrupts Driver
 * Created on : Jun 12, 2023
 *
 *==========================================================================================*/

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "gpio.h"
#include <avr/interrupt.h>



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	FALLING,
	RAISING,
}EDGE_TYPE;



/*******************************************************************************
 *                               Global_Variables Declaration                             *
 *******************************************************************************/
static volatile void (*funcArray[3])(void);


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void INT0_init(EDGE_TYPE EDGE);
void INT1_init(EDGE_TYPE EDGE);
void INT2_init(EDGE_TYPE EDGE);
void External_Interrupt_set_CallBack(void(*ptr_2_fun)(void),uint8 index);


#endif /* EXTERNAL_INTERRUPTS_H_ */
