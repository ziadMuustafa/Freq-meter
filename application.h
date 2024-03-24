/* 
 * File:   application.h
 * Author: el msria
 *
 * Created on March 19, 2024, 9:19 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

//INCLUDES//////////////////////////////////////////////////////////////////////
 #include "pic18f4620.h"
 #include "MCAL_LAYER/COMPILER.h"
 #include "ECU_LAYER/K_PAD/K_PAD.h"
 #include "ECU_LAYER/LCD/LCD.h"
 #include "MCAL_LAYER/STD_TYPES.h"
 #include "MCAL_LAYER/GPIO/HAL_GPIO.h"
 #include "MCAL_LAYER/TIMER0/TIMER0.h"
 #include "MCAL_LAYER/TIMER2/TIMER2.h"
 #include "MCAL_LAYER/interupt/external_interupt.h"
 #include "MCAL_LAYER/interupt/interupt_config.h"
 #include "MCAL_LAYER/interupt/interupt_manager.h"
 #include "MCAL_LAYER/interupt/interupt_gen_features.h"
 #include "DECLERATIONS.h"
        
    
///FUNCTIONS DECLERATIONS///////////////////////////////////////////////////////
void isr_0(void) ;
void TMR0_ISR_1(void) ;
void TMR2_ISR_1(void) ;
void WELCOMING(void) ;
void SEPARATE_NUM(uint32 freq ,int *freq_hunds , int *freq_tens , int *freq_ones  );
void DISPLAY_FREQ(int *freq_hunds , int *freq_tens , int *freq_ones  ) ;


#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

