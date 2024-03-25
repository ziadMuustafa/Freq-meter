/* 
 * File:   interupt_manager.h
 * Author: el msria
 *
 * Created on December 19, 2023, 4:37 PM
 */

#ifndef INTERUPT_MANAGER_H
#define	INTERUPT_MANAGER_H

// INCLUDES 
#include "interupt_config.h"

  void INT0_ISR(void);
  void INT1_ISR(void);
  void INT2_ISR(void);
  void ADC_ISR(void) ;
  void TMR0_ISR(void);
  void TMRR1_ISR(void) ;
  void TMRR2_ISR(void) ;
  void TMRR3_ISR(void) ;
  void CCP1_ISR(void) ;
  void CCP2_ISR(void) ;

  
  
  void RB4_ISR(uint8 RX) ;
  void RB5_ISR(uint8 RX) ;
  void RB6_ISR(uint8 RX) ;
  void RB7_ISR(uint8 RX) ;



#endif	/* INTERUPT_MANAGER_H */

