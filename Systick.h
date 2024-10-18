/*
 * Systick.h
 *
 *  @Created on: Jul 29, 2024
 *  @Author: Mohamed Adel
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"

#define SYSTRL_CLK_SRC_BIT_MASK       0x04
#define SYSTRL_INTEN_ENABLE_BIT_MASK  0x02
#define SYSTIRL_ENABLE_BIT_MASK       0x01
#define MILLI_SECOND_PERIOD           15999
#define SYSTRL_COUNT_BIT_MASK         0x10000

/*
 *Description: Initialize the SysTick timer with the specified time in milliseconds
  using interrupts. This function is used to setup the timer to generate periodic
  interrupts every specified time in milliseconds.
 *
 */
void SysTick_Init(uint16 a_TimeInMilliSeconds);

/*Description: Initialize the SysTick timer with the specified time in milliseconds
using polling or busy-wait technique. The function should exit when the time is
elapsed and stops the timer at the end.*/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);

/*Description: Function to De-initialize the SysTick Timer.*/
 void SysTick_DeInit(void);

 /* Description: Handler for SysTick interrupt use to call the call-back function. */
 void SysTick_Handler(void);

 /*Description: Function to setup the SysTick Timer call back to be executed in */
 void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
 /* Description: Stop the SysTick timer.*/
 void SysTick_Stop(void);
/* Description: Start/Resume the SysTick timer.*/
  void SysTick_Start(void);


#endif /* SYSTICK_H_ */
