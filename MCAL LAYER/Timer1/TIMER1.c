#include "TIMER1.h"

uint8 ret =E_OK ; 
static uint16 preloud_val ;

///POINTER TO FUNCTIONS/////////////////////////////////////////////////////////
static void (*interupt_tmr1_callvack)(void) = NULL ; // pointer to function to save the callback func(which is comming from app layer)




///HELPER FUNCTIONS/////////////////////////////////////////////////////////////
/**
 * this func is a handler function which just assign the pointer to function we created to the callbak func (which is comming from app layer)
 * @param interupt_callback
 * @return 
 */
Std_ReturnType TMR1_INTERUPT_HANDELER(void (*interupt_callback)(void) ){
TMR1_interupt_CLEAR_FLAG() ;
if(interupt_callback == NULL){ret = E_NOT_OK ;}
else{
interupt_tmr1_callvack = interupt_callback ;
}
return ret  ;
}
////////////////////////////////////////////////////////////////////////////////



///MAIN FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TIMER1_INIT(const TIMER1_t *TMR1_1){
   //WE HAVE SOME STEPS TO FOLLOW 
   
    //STEP1 ---> DISABLE IT 
    TMR1_DISABLE() ;
  
    //STEP2 ---> SET THE MODE_TYPE (TIMER OR COUNTER)
    if(TMR1_1->timer1_mode == COUNTER_MODE){USING_EXTERNAL_CLC_SOURCE__COUNTER_MODE();}
    else if(TMR1_1->timer1_mode == TIMER_MODE){USING_INTERNAL_CLC_SOURCE__TIMER_MODE();}
    
    
    //STEP3 ---> SET THE EDGE 
    /// no need for edge configration as it just rising edge counter
    
   
    //STEP4 ---> SET THE REG SIZE TYPE (AT 8 BIT 2 TIMES OR 16BIT ONE TIME )---> ITS JUST 16 BIT RECALL  
    if(TMR1_1->timer1_rg_bits_type == 0){TMR1_REG_8BIT_AT_2_TIMES() ;}
    else if(TMR1_1->timer1_rg_bits_type == 1){TMR1_REG_16BIT_AT_1_TIME();} 
    
    
    //timer1_osc_cfg
    //STEP5 ---> SET THE SYNCH TYPE  
    if(TMR1_1->timer1_synch == SYNCH_COUNTER){TMR1_SYNCH_COUNTER_MODE() ;}
    else if(TMR1_1->timer1_synch == ASYNCH_COUNTER){TMR1_ASYNCH_COUNTER_MODE();} 
  
    
    //STEP6 ---> SET THE SYNCH TYPE  
    if(TMR1_1->timer1_osc_cfg == 1){TIMER1_OSC_ENABLE() ;}
    else if(TMR1_1->timer1_osc_cfg == 0){TIMER1_OSC_DISABLE();} 
    
    
    //STEP7 ---> SET THE PRE_SCALLER VALUE 
      #if PRE_SCALLER_STATE==PRE_SCALER_IS_ON
 
    
    if(1){
        switch(TMR1_1->timer1_pre_scaler_value){
            case Prescale_TMR1_value_1_dev_1   : TMR1_PRE_SCALER_SET(Prescale_TMR1_value_1_dev_1) ;break ;
            case Prescale_TMR1_value_1_dev_2   : TMR1_PRE_SCALER_SET(Prescale_TMR1_value_1_dev_2) ;break ;
            case Prescale_TMR1_value_1_dev_4   : TMR1_PRE_SCALER_SET(Prescale_TMR1_value_1_dev_4) ;break ;
            case Prescale_TMR1_value_1_dev_8   : TMR1_PRE_SCALER_SET(Prescale_TMR1_value_1_dev_8) ;break ;
         
        }
    }
    #endif
    
    
    //STEP8 ---> CONFIGURE THE INTERUPT
        #if TMR1_INTERUPT==FEATURE_ENABLE 
        GENERAL_INTERUPT_ENABLE();
        PREPHERAL_INTERUPT_ENABLE() ; 
        TMR1_interupt_ENABLE();
        TMR1_interupt_CLEAR_FLAG() ;
        
        #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
        gfgdgdfg
        #endif
        
        TMR1_INTERUPT_HANDELER(TMR1_1->interupt_callback) ;
        
        #endif

    
    //STEP9 ---> SET THE TIMER PRELOAD
        TMR1H = (uint8)(TMR1_1->timer1_pre_load >> 8) ;
        TMR1L = (uint8)(TMR1_1->timer1_pre_load)  ;    
        preloud_val =  TMR1_1->timer1_pre_load ;
           
    
    //STEP10 ---> FINALLY ENABLE IT 
        TMR1_ENABLE() ;
        
        
} ;



////////////////////////////////////////////////////////////////////////////////
//THE ISR TO BE EXCUTED //////
/**
 * THIS FUNC IS THE ISR FUNCTION WHICH WILL BE EXCUTED WHEN THE INTERUPT HAPPENS
 */
void TMRR1_ISR(void){
    TMR1_interupt_CLEAR_FLAG() ;
        TMR1H = (uint8)(preloud_val >> 8) ;
        TMR1L = (uint8)(preloud_val)  ;    
       
    if(interupt_tmr1_callvack){interupt_tmr1_callvack() ; };
}
////////////////////////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST READS THE VALUE AT TMR1 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER1_READ_VALUE(const TIMER1_t *TMR1 , uint16 *value){
    if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
        uint8 val_high = TMR1H ;  uint8 val_low = TMR1L ;
       *value = val_low ;
       *value = value  + (val_high >> 8) ;
    }
    return ret ;
};

////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST WRITES A VALUE AT TMR1 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER1_WRITE_VALUE(const TIMER1_t *TMR1 , uint16 value){
 if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
       TMR1H = (uint8)(value >> 8) ;
       TMR1L = (uint8)value ; 
    }
    return ret ;
};
////////////////////////////////////////////////////////////////////////////////
