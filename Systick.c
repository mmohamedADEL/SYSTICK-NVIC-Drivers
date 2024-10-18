/*
 * Systick.c
 *
 *  @Created on: Jul 29, 2024
 *  @Author: Mohamed Adel
 */

#include "Systick.h"

volatile static void(*Ptr_Fun)(void);
static uint16 count ;

/*********************************************************************
* Service Name: Initialize the SysTick timer
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Reload value
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Initialize the SysTick timer with the specified time in milliseconds
  using interrupts. This function is used to setup the timer to generate periodic
  interrupts every specified time in milliseconds.
**********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG = 0 ;
    SYSTICK_RELOAD_REG = 16000 - 1 ;
    SYSTICK_CURRENT_REG = 0 ;
    SYSTICK_CTRL_REG |= (SYSTRL_CLK_SRC_BIT_MASK | SYSTIRL_ENABLE_BIT_MASK |SYSTRL_INTEN_ENABLE_BIT_MASK) ;
    NVIC_SYSTEM_PRI3_REG  = 0xE0000000 & 2 ;
    count = a_TimeInMilliSeconds ;
}

/*********************************************************************
* Service Name:  Initialize the SysTick timer
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): a_TimeInMilliSeconds - Reload value
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Initialize the SysTick timer with the specified time in milliseconds
using polling or busy-wait technique. The function should exit when the time is
elapsed and stops the timer at the end
**********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
   SYSTICK_CTRL_REG = 0 ;
   SYSTICK_RELOAD_REG = MILLI_SECOND_PERIOD ;
   SYSTICK_CURRENT_REG = 0 ;
   SYSTICK_CTRL_REG |= (SYSTRL_CLK_SRC_BIT_MASK | SYSTIRL_ENABLE_BIT_MASK) ;
   while(a_TimeInMilliSeconds --){
       while(!(SYSTICK_CTRL_REG & SYSTRL_COUNT_BIT_MASK));
   }
   SYSTICK_CTRL_REG = 0 ;
   SYSTICK_RELOAD_REG = 0 ;
   SYSTICK_CURRENT_REG = 0 ;
}

/*********************************************************************
* Service Name: De-initialize the SysTick Timer.
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to De-initialize the SysTick Timer.
**********************************************************************/
 void SysTick_DeInit(void){
     SYSTICK_CTRL_REG = 0 ;
     SYSTICK_RELOAD_REG = 0 ;
     SYSTICK_CURRENT_REG = 0 ;

 }

 /*********************************************************************
 * Service Name:Handler for SysTick interrupt.
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Handler for SysTick interrupt use to call the call-back function.
 **********************************************************************/
 void SysTick_Handler(void){
     static uint16 L_Count = 0 ;
     if (L_Count == count){
         Ptr_Fun();
         L_Count = 0 ;
     }
     else{
         L_Count++ ;
     }
 }

 /*********************************************************************
 * Service Name:Call back Handler for SysTick interrupt.
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Ptr2Func - pointer to function of Systick ISR.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to setup the SysTick Timer call back to be executed in.
 **********************************************************************/
 void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
     if (Ptr2Func){
         Ptr_Fun = Ptr2Func ;
     }
 }
 /*********************************************************************
 * Service Name:Stop the SysTick timer.
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to Stop the SysTick timer.
 **********************************************************************/
 void SysTick_Stop(void){
     SYSTICK_CTRL_REG &= ~(SYSTIRL_ENABLE_BIT_MASK) ;
 }
 /*********************************************************************
 * Service Name:Start/Resume the SysTick timer.
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description:  Function to Start/Resume the SysTick timer.
 **********************************************************************/
  void SysTick_Start(void){
      SYSTICK_CTRL_REG |= (SYSTIRL_ENABLE_BIT_MASK) ;
  }

