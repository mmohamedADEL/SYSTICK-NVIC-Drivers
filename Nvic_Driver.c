/*
 * Nvic_Driver.c
 *
 *  Created on: Jul 31, 2024
 *      Author: i9
 */

#include <NVIC.h>

/*Description: Function to enable Interrupt request for this specific IRQ.*/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    //IRQ_Num -=16 ;
    if(IRQ_Num <= 31){
        NVIC_EN0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 32 && IRQ_Num <= 63){
        IRQ_Num -=32 ;
        NVIC_EN1_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 64 && IRQ_Num <= 95){
        IRQ_Num -=64 ;
        NVIC_EN2_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 96 && IRQ_Num <= 122){
        IRQ_Num -=96 ;
        NVIC_EN3_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 128 && IRQ_Num <= 138){
        IRQ_Num -=128 ;
        NVIC_EN4_REG |= (1<<IRQ_Num);
    }
    else {
       /*Nothing*/
    }
}
/*Description: Function to disable Interrupt request for this specific IRQ*/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    //IRQ_Num -=16 ;
    if(IRQ_Num <= 31){
       NVIC_DIS0_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 32 && IRQ_Num <= 63){
       IRQ_Num -=32 ;
       NVIC_DIS1_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 64 && IRQ_Num <= 95){
       IRQ_Num -=64 ;
       NVIC_DIS2_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 96 && IRQ_Num <= 122){
        IRQ_Num -=96 ;
       NVIC_DIS3_REG |= (1<<IRQ_Num);
    }
    else if(IRQ_Num >= 123 && IRQ_Num <= 138){
        IRQ_Num -=128 ;
       NVIC_DIS4_REG |= (1<<IRQ_Num);
    }
    else {
      /*Nothing*/
    }
}
/*Description: Function to set the priority value for specific IRQ.*/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
    //IRQ_Num -=16 ;
    uint8 dev = IRQ_Num/4 ;
    uint8 per_postion = IRQ_Num%4 ;
    switch (per_postion){
    case (0) :
        *(NVIC_PRI0_PTR + dev) |=   (PRI_FRIST_POS_MASK & IRQ_Priority << 5);
        break ;
    case (1) :
        *(NVIC_PRI0_PTR + dev) |=   (PRI_SEC_POS_MASK & IRQ_Priority << 13);
       break ;
    case (2) :
        *(NVIC_PRI0_PTR + dev) |=  (PRI_THIRD_POS_MASK & IRQ_Priority << 21);
       break ;
    case (3) :
        *(NVIC_PRI0_PTR + dev) |=  (PRI_FORTH_POS_MASK & IRQ_Priority << 29);
       break ;
    default :
        /*nothing*/
        break ;
    }
}
/*Description: Function to enable specific ARM system or fault exceptions.*/
 void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
     switch (Exception_Num){
     case EXCEPTION_RESET_TYPE :
         /*NOTHING*/
         break ;
     case EXCEPTION_NMI_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_HARD_FAULT_TYPE :
         Enable_Faults();
         break;
      case EXCEPTION_MEM_FAULT_TYPE :
          NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK ;
          break;
      case EXCEPTION_BUS_FAULT_TYPE :
          NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK ;
          break;
     case EXCEPTION_USAGE_FAULT_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL  |= USAGE_FAULT_ENABLE_MASK ;
          break;
      case EXCEPTION_SVC_TYPE :
          NVIC_SYSTEM_SYSHNDCTRL  |= PENDSV_FAULT_ENABLE_MASK ;
         break;
     case EXCEPTION_DEBUG_MONITOR_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_PEND_SV_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL  |= SVC_FAULT_ENABLE_MASK ;
          break;
     case EXCEPTION_SYSTICK_TYPE :
         SYSTICK_CTRL_REG |= SYSTRL_INTEN_ENABLE_BIT_MASK ;
          break;
     default :
         /*NOTHING*/
         break ;
     }
 }
/*Description: Function to disable specific ARM system or fault exceptions.*/
 void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
     switch (Exception_Num){
     case EXCEPTION_RESET_TYPE :
         /*NOTHING*/
         break ;
     case EXCEPTION_NMI_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_HARD_FAULT_TYPE :
         Disable_Faults();
         break;
     case EXCEPTION_MEM_FAULT_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK ;
         break;
     case EXCEPTION_BUS_FAULT_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK ;
         break;
     case EXCEPTION_USAGE_FAULT_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL  &= ~USAGE_FAULT_ENABLE_MASK ;
         break;
     case EXCEPTION_SVC_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL   &= ~SVC_FAULT_ENABLE_MASK ;
         break;
     case EXCEPTION_DEBUG_MONITOR_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_PEND_SV_TYPE :
         NVIC_SYSTEM_SYSHNDCTRL   &= ~PENDSV_FAULT_ENABLE_MASK ;
          break;
     case EXCEPTION_SYSTICK_TYPE :
         SYSTICK_CTRL_REG &= ~SYSTRL_INTEN_ENABLE_BIT_MASK ;
          break;
     default :
          /*NOTHING*/
          break ;
     }
 }
/*Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
Description: Function to set the priority value for specific ARM system or fault exceptions*/
 void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num ,
                                NVIC_ExceptionPriorityType Exception_Priority){
     switch (Exception_Num){
     case EXCEPTION_RESET_TYPE :
         /*NOTHING*/
         break ;
     case EXCEPTION_NMI_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_HARD_FAULT_TYPE :
         /*NOTHING*/
         break;
     case EXCEPTION_MEM_FAULT_TYPE :
         NVIC_SYSTEM_PRI1_REG |= MEM_FAULT_PRIORITY_MASK & (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
         break;
     case EXCEPTION_BUS_FAULT_TYPE :
         NVIC_SYSTEM_PRI1_REG |= BUS_FAULT_PRIORITY_MASK & (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
         break;
     case EXCEPTION_USAGE_FAULT_TYPE :
         NVIC_SYSTEM_PRI1_REG |= USAGE_FAULT_PRIORITY_MASK &(Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
         break;
     case EXCEPTION_SVC_TYPE :
         NVIC_SYSTEM_PRI2_REG |= SVC_PRIORITY_MASK & (Exception_Priority << SVC_PRIORITY_BITS_POS );
         break;
     case EXCEPTION_DEBUG_MONITOR_TYPE :
         NVIC_SYSTEM_PRI3_REG |= DEBUG_MONITOR_PRIORITY_MASK & (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
         break;
     case EXCEPTION_PEND_SV_TYPE :
         NVIC_SYSTEM_PRI3_REG |= PENDSV_PRIORITY_MASK & (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
          break;
     case EXCEPTION_SYSTICK_TYPE :
         NVIC_SYSTEM_PRI3_REG |= SYSTICK_PRIORITY_MASK & (Exception_Priority << SYSTICK_PRIORITY_BITS_POS) ;
          break;
     default :
         /*NOTHING*/
         break ;
     }
 }


