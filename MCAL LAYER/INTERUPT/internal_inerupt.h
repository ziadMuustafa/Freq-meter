/* 
 * File:   internal_inerupt.h
 * Author: el msria
 *
 * Created on December 19, 2023, 4:35 PM
 */

#ifndef INTERNAL_INERUPT_H
#define	INTERNAL_INERUPT_H

///INCLUDES/////////////////////////////////////////////////////////////////////
#include "interupt_config.h"
#include "interupt_gen_features.h"
#include "pic18f4620.h"


///MACRO FUNCTION///////////////////////////////////////////////////////////////
#if ADC_INTERUPT==FEATURE_ENABLE

#define ADC_INTERUPT_ENABLE()       (PIE1bits.ADIE = 1)
#define ADC_INTERUPT_DISABLE()      (PIE1bits.ADIE = 0)
#define ADC_INTERUPT_CLEAR_FLAG()   (PIR1bits.ADIF = 0)

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
#define ADC_USING_HIGH_PRIORITY() (IPR1bits.ADIP = 1)
#define ADC_USING_LOW_PRIORITY()  (IPR1bits.ADIP = 0)
#endif
#endif
 

#if TMR0_INTERUPT==FEATURE_ENABLE   

#define TMR0_interupt_ENABLE()      (INTCONbits.TMR0IE = 1)    
#define TMR0_interupt_DISABLE()     (INTCONbits.TMR0IE = 0)    
#define TMR0_interupt_CLEAR_FLAG()  (INTCONbits.TMR0IF = 0)    
    
#endif      
/*
#if TMR1_INTERUPT==FEATURE_ENABLE   

#define TMR1_interupt_ENABLE()      (PIE1bits.TMR1IE = 1)    
#define TMR1_interupt_DISABLE()     (PIE1bits.TMR1IE = 0)    
#define TMR1_interupt_CLEAR_FLAG()  (PIR1bits.TMR1IF = 0)    
    
#endif      
*/
#if TMR2_INTERUPT==FEATURE_ENABLE   

#define TMR2_interupt_ENABLE()      (PIE1bits.TMR2IE = 1)    
#define TMR2_interupt_DISABLE()     (PIE1bits.TMR1IE = 0)    
#define TMR2_interupt_CLEAR_FLAG()  (PIR1bits.TMR1IF = 0)    
    
#endif      
/*
#if TMR3_INTERUPT==FEATURE_ENABLE   

#define TMR3_interupt_ENABLE()      (PIE2bits.TMR3IE = 1)    
#define TMR3_interupt_DISABLE()     (PIE2bits.TMR3IE = 0)    
#define TMR3_interupt_CLEAR_FLAG()  (PIR2bits.TMR3IF = 0)    
    
#endif      
*/
/*
#if CCP1_INTERUPT==FEATURE_ENABLE

#define  CCP1_INTERUPT_ENABLE()      (PIE1bits.CCP1IE = 1)
#define CCP1_INTERUPT_DISABLE()      (PIE1bits.CCP1IE = 0)
#define CCP1_INTERUPT_CLEAR_FLAG()   (PIR1bits.CCP1IF = 0)

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
#define CCP1_USING_HIGH_PRIORITY() (IPR1bits.CCP1IP = 1)
#define CCP1_USING_LOW_PRIORITY()  (IPR1bits.CCP1IP = 0)
#endif

#endif
*/ /*
#if CCP2_INTERUPT==FEATURE_ENABLE

#define  CCP2_INTERUPT_ENABLE()      (PIE2bits.CCP2IE = 1)
#define CCP2_INTERUPT_DISABLE()      (PIE2bits.CCP2IE = 0)
#define CCP2_INTERUPT_CLEAR_FLAG()   (PIR2bits.CCP2IF = 0)

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
#define CCP2_USING_HIGH_PRIORITY() (IPR2bits.CCP2IP = 1)
#define CCP2_USING_LOW_PRIORITY()  (IPR2bits.CCP2IP = 0)
#endif


#endif

*/

///FUNCTIONS DECLERATIONS///////////////////////////////////////////////////////
//Std_ReturnType ADC_ISR_FUNCTION(void (*ADC_INTERUPT_CALLBACK)(void)) ;



#endif	/* INTERNAL_INERUPT_H */

