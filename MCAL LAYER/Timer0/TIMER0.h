/* 
 * File:   TIMER0.h
 * Author: el msria
 *
 * Created on February 19, 2024, 3:17 AM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif

///GEN CONFIG///////////////////////////////////////////////////////////////////
    
    
///INCLUDES/////////////////////////////////////////////////////////////////////
#include "../STD_TYPES.h"
#include "pic18f4620.h"    
#include "../interupt/internal_inerupt.h"
#include "../interupt/interupt_manager.h"
#include "../interupt/interupt_gen_features.h"    
    
///DEFINES//////////////////////////////////////////////////////////////////////
#define HIGH_TO_LOW 1
#define LOW_TO_HIGH 0
    
#define COUNTER_MODE 1
#define TIMER_MODE 0

#define USING_8BIT  0
#define USING_16BIT 1

#define PRE_SCALER_IS_ON   0
#define PRE_SCALER_IS_OFF  1

///GEN CONFIG///////////////////////////////////////////////////////////////////
#define PRE_SCALLER_STATE PRE_SCALER_IS_OFF     
    
    
///MACRO FUNCTIONS//////////////////////////////////////////////////////////////
        
#define PRE_SCALER_ON()  (T0CONbits.PSA = 0)
#define PRE_SCALER_OFF() (T0CONbits.PSA = 1)

#define USING_HIGH_TO_LOW()(T0CONbits.T0SE = 1) 
#define USING_LOW_TO_HIGH()(T0CONbits.T0SE = 0) 
    
#define USING_EXTERNAL_CLC_SOURCE() (T0CONbits.T0CS = 1)    // COUNTER MODE 
#define USING_INTERNAL_CLC_SOURCE() (T0CONbits.T0CS = 0)   // TIMER MODE

#define TMR0_REG_8BIT()  (T0CONbits.T08BIT = 1)
#define TMR0_REG_16BIT() (T0CONbits.T08BIT = 0)
    
#define TMR0_ENABLE()  (T0CONbits.TMR0ON = 1)
#define TMR0_DISABLE() (T0CONbits.TMR0ON = 0)
    
#define TMR0_PRE_SCALER_SET(DEV)  (T0CONbits.T0PS = DEV)
    
 

///USER DEFINED DATA TYPES//////////////////////////////////////////////////////
typedef enum {
    Prescale_value_1_dev_2,
    Prescale_value_1_dev_4,
    Prescale_value_1_dev_8,
    Prescale_value_1_dev_16,
    Prescale_value_1_dev_32,
    Prescale_value_1_dev_64,
    Prescale_value_1_dev_128,
    Prescale_value_1_dev_256,        
     
};    
    
typedef struct {
    uint8 timer0_rg_bits : 1 ;
    uint8 timer0_edge : 1   ;
    uint8 timer0_clc_sorce :1 ;
    uint8 timer0_pre_scaler_value : 3 ;
    uint16 timer0_pre_load ;
    void (*interupt_callback)(void) ;
}TIMER0_t;


///FUNCTINS DECLERATIONS////////////////////////////////////////////////////////

//HELPER FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TMR_INTERUPT_HANDELER(void (*interupt_callback)(void)) ;
void TMRR0_ISR(void) ;



Std_ReturnType TIMER0_INIT(const TIMER0_t *TMR1);
Std_ReturnType TIMER0_READ_VALUE(const TIMER0_t *TMR1 , uint16 *value);
Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0_t *TMR1 , uint16 value);




#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

