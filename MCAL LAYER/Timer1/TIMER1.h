/* 
 * File:   TIMER1.h
 * Author: el msria
 *
 * Created on February 22, 2024, 2:55 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif

///FEN CONFIG///////////////////////////////////////////////////////////////////
    
    
///INCLUDES/////////////////////////////////////////////////////////////////////
#include "../STD_TYPES.h"
#include "pic18f4620.h"    
#include "../interupt/internal_inerupt.h"
#include "../interupt/interupt_manager.h"
#include "../interupt/interupt_gen_features.h"    
    
///DEFINES//////////////////////////////////////////////////////////////////////
#define HIGH_TO_LOW 1
#define LOW_TO_HIGH 0

#define TIMER1_ON  1
#define TIMER1_OFF 0    
    
#define COUNTER_MODE 1
#define TIMER_MODE 0

#define SYNCH_COUNTER  0
#define ASYNCH_COUNTER 1    
    
#define PRE_SCALER_IS_ON   0
#define PRE_SCALER_IS_OFF  1

///GEN CONFIG///////////////////////////////////////////////////////////////////
#define PRE_SCALLER_STATE PRE_SCALER_IS_ON     
    
    
///MACRO FUNCTIONS//////////////////////////////////////////////////////////////
        
#define TIMER1_OSC_ENABLE() (T1CONbits.T1OSCEN = 1) 
#define TIMER1_OSC_DISABLE()(T1CONbits.T1OSCEN = 0) 
    
#define USING_EXTERNAL_CLC_SOURCE__COUNTER_MODE() (T1CONbits.TMR1CS = 1)    // COUNTER MODE  //RC0 MUST BE INPUT CONFIG FROM GPIO
#define USING_INTERNAL_CLC_SOURCE__TIMER_MODE()   (T1CONbits.TMR1CS = 0)   // TIMER MODE

#define TMR1_READ_RUN_BIT()  (T1CONbits.T1RUN) 
    
#define TMR1_REG_8BIT_AT_2_TIMES()  (T1CONbits.RD16 = 0)
#define TMR1_REG_16BIT_AT_1_TIME()  (T1CONbits.RD16 = 1)
    
#define TMR1_SYNCH_COUNTER_MODE()  (T1CONbits.T1SYNC = SYNCH_COUNTER)
#define TMR1_ASYNCH_COUNTER_MODE()  (T1CONbits.T1SYNC = ASYNCH_COUNTER)    
    
#define TMR1_ENABLE()  (T1CONbits.TMR1ON = 1)
#define TMR1_DISABLE() (T1CONbits.TMR1ON = 0)
    
#define TMR1_OSC_ENABLE()  (T1CONbits.T1OSCEN = 1)
#define TMR1_OSC_DISABLE() (T1CONbits.T1OSCEN = 0)    
    
#define TMR1_PRE_SCALER_SET(DEV)  (T1CONbits.T1CKPS = DEV)
    
 

///USER DEFINED DATA TYPES//////////////////////////////////////////////////////
typedef enum {
    Prescale_TMR1_value_1_dev_1,
    Prescale_TMR1_value_1_dev_2,
    Prescale_TMR1_value_1_dev_4,
    Prescale_TMR1_value_1_dev_8,
     
     
};    //NO NEED TO GIVE NAME TO THE ENUM
    
typedef struct {
    uint8 timer1_rg_bits_type : 1 ;
    uint8 timer1_mode :1 ;
    uint8 timer1_pre_scaler_value : 2 ;
    uint16 timer1_pre_load ;
    void (*interupt_callback)(void) ;
    uint8 timer1_synch :1 ;
    uint8 timer1_osc_cfg :1 ;
}TIMER1_t;


///FUNCTINS DECLERATIONS////////////////////////////////////////////////////////

//HELPER FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TMR1_INTERUPT_HANDELER(void (*interupt_callback)(void)) ;
void TMRR1_ISR(void) ;



Std_ReturnType TIMER1_INIT(const TIMER1_t *TMR1);
Std_ReturnType TIMER1_READ_VALUE(const TIMER1_t *TMR1 , uint16 *value);
Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1_t *TMR1 , uint16 value);


    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

