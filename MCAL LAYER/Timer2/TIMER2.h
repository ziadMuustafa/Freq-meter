/* 
 * File:   TIMER2.h
 * Author: el msria
 *
 * Created on February 25, 2024, 12:29 AM
 */

#ifndef TIMER2_H
#define	TIMER2_H

#ifdef	__cplusplus
extern "C" {
#endif

/////////////RECALL ---> TMR2 IS 8BIT TIMER ONLY AND WOORK AS ATIMER ONLY NOT COUNTER    
    
///INCLUDES/////////////////////////////////////////////////////////////////////
#include "../STD_TYPES.h"
#include "pic18f4620.h"    
#include "../interupt/internal_inerupt.h"
#include "../interupt/interupt_manager.h"
#include "../interupt/interupt_gen_features.h"    
    
///DEFINES//////////////////////////////////////////////////////////////////////

#define TIMER2_ON  1
#define TIMER2_OFF 0    
    
#define COUNTER_MODE 1  // --------------> TIMER2 DOES NOT WORK ON COUNTER MODE ---> JUST TIMER MODE 
#define TIMER_MODE 0

#define SYNCH_COUNTER  0 /// AS BELLOW IT DOES NOT HAVE SYNCH OR ASYNCH FEATURE AS IT DOES NOT WORK ON COUNTER MODE ASLAN BA33A
#define ASYNCH_COUNTER 1 /// AS BELLOW IT DOES NOT HAVE SYNCH OR ASYNCH FEATURE AS IT DOES NOT WORK ON COUNTER MODE ASLAN BA33A    
    
#define PRE_SCALER_IS_ON    1
#define PRE_SCALER_IS_OFF   0
    
#define POST_SCALER_IS_ON   1
#define POST_SCALER_IS_OFF  0    

///GEN CONFIG///////////////////////////////////////////////////////////////////
#define PRE_SCALLER_STATE  PRE_SCALER_IS_ON
#define POST_SCALLER_STATE POST_SCALER_IS_ON
    
    
///MACRO FUNCTIONS//////////////////////////////////////////////////////////////
        
    
#define TMR2_ENABLE()  (T2CONbits.TMR2ON = 1)
#define TMR2_DISABLE() (T2CONbits.TMR2ON = 0)
   
    
#define TMR2_PRE_SCALER_SET(DEV)   (T2CONbits.T2CKPS = DEV)
#define TMR2_POST_SCALER_SET(DEV)  (T2CONbits.TOUTPS = DEV)
    
 

///USER DEFINED DATA TYPES//////////////////////////////////////////////////////
typedef enum {
    postcale_TMR2_value_1_dev_1,   ///postscale msh postcale
    postcale_TMR2_value_1_dev_2,
    postcale_TMR2_value_1_dev_3,
    postcale_TMR2_value_1_dev_4,        
    postcale_TMR2_value_1_dev_5,
    postcale_TMR2_value_1_dev_6,        
    postcale_TMR2_value_1_dev_7,  
    postcale_TMR2_value_1_dev_8,        
    postcale_TMR2_value_1_dev_9,  
    postcale_TMR2_value_1_dev_10,      
    postcale_TMR2_value_1_dev_11,
    postcale_TMR2_value_1_dev_12,   
    postcale_TMR2_value_1_dev_13,
    postcale_TMR2_value_1_dev_14,
    postcale_TMR2_value_1_dev_15,
    postcale_TMR2_value_1_dev_16,        
};    //NO NEED TO GIVE NAME TO THE ENUM

typedef enum {
    precale_TMR2_value_1_dev_1,   ///prescale msh precale
    precale_TMR2_value_1_dev_4,
    precale_TMR2_value_1_dev_16,
    
};    //NO NEED TO GIVE NAME TO THE ENUM
    
typedef struct {
    uint8 timer2_pre_scaler_value : 2 ;
    uint8 timer2_post_scaler_value : 4 ;
    uint8 timer2_pre_load ;
    void (*interupt_callback)(void) ;
}TIMER2_t;


///FUNCTINS DECLERATIONS////////////////////////////////////////////////////////

//HELPER FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TMR2_INTERUPT_HANDELER(void (*interupt_callback)(void)) ;
void TMRR2_ISR(void) ;



Std_ReturnType TIMER2_INIT(const TIMER2_t *TMRR2);
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_t *TMRR2 , uint8 *value);
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_t *TMRR2 , uint8 value);




#ifdef	__cplusplus
}
#endif

#endif	/* TIMER2_H */

