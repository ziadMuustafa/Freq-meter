# include "TIMER0.h"
uint8 ret =E_OK ; 
static uint16 preloud_val ;

///POINTER TO FUNCTIONS/////////////////////////////////////////////////////////
static void (*interupt_callvack)(void) = NULL ;  // pointer to function to save the callback func(which is comming from app layer)

///HELPER FUNCTIONS/////////////////////////////////////////////////////////////

/**
 * this func is a handler function which just assign the pointer to function we created to the callbak func (which is comming from app layer)
 * @param interupt_callback
 * @return 
 */
Std_ReturnType TMR_INTERUPT_HANDELER(void (*interupt_callback)(void) ){
TMR0_interupt_CLEAR_FLAG() ;
if(interupt_callback == NULL){ret = E_NOT_OK ;}
else{
interupt_callvack = interupt_callback ;
}
return ret  ;
}
/////////////////////////////////////////////////////////////////////////////////




///MAIN FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TIMER0_INIT(const TIMER0_t *TMR0_1){
   //WE HAVE SOME STEPS TO FOLLOW 
   //STEP1 ---> DISABLE IT 
    TMR0_DISABLE() ;
  
     
    //STEP2 ---> SET THE MODE_TYPE (TIMER OR COUNTER)
    if(TMR0_1->timer0_clc_sorce == COUNTER_MODE){USING_EXTERNAL_CLC_SOURCE();}
    else if(TMR0_1->timer0_clc_sorce == TIMER_MODE){USING_INTERNAL_CLC_SOURCE();}
    
    
    //STEP3 ---> SET THE EDGE 
    if(T0CONbits.T0CS == COUNTER_MODE){
    if(TMR0_1->timer0_edge == HIGH_TO_LOW){USING_HIGH_TO_LOW();}
    else if(TMR0_1->timer0_edge == LOW_TO_HIGH){USING_LOW_TO_HIGH();} 
    }
   
   
    //STEP4 ---> SET THE REG SIZE  --> 8bit or 16bit   
    if(TMR0_1->timer0_rg_bits == USING_8BIT){TMR0_REG_8BIT() ;}
    else if(TMR0_1->timer0_rg_bits == USING_16BIT){TMR0_REG_16BIT();} 
  
    
    
    //STEP5 ---> SET THE PRE_SCALLER VALUE 
    #if PRE_SCALLER_STATE==PRE_SCALER_IS_ON
      PRE_SCALER_ON() ;
    
     if( T0CONbits.PSA == 0){
        switch(TMR0_1->timer0_pre_scaler_value){
            case Prescale_value_1_dev_2   : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_2) ;break ;
            case Prescale_value_1_dev_4   : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_4) ;break ;
            case Prescale_value_1_dev_8   : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_8) ;break ;
            case Prescale_value_1_dev_16  : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_16) ;break ;
            case Prescale_value_1_dev_32  : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_32) ;break ;
            case Prescale_value_1_dev_64  : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_64) ;break ;
            case Prescale_value_1_dev_128 : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_128) ;break ;
            case Prescale_value_1_dev_256 : TMR0_PRE_SCALER_SET(Prescale_value_1_dev_256) ;break ;
        }
    }
    #endif
    
    
    //STEP6 ---> CONFIGURE THE INTERUPT
    #if TMR0_INTERUPT==FEATURE_ENABLE 
        GENERAL_INTERUPT_ENABLE();
        PREPHERAL_INTERUPT_ENABLE() ; 
        TMR0_interupt_ENABLE();
        TMR0_interupt_CLEAR_FLAG() ;
        
        #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
        gfgdgdfg
        #endif
        
        TMR_INTERUPT_HANDELER(TMR0_1->interupt_callback) ;   // here we call the interupt handler func to assign the callbak func to
                                                            //  the pointer to function we created to save it  
    #endif

    
    
    //STEP7 ---> SET THE TIMER PRELOAD
        TMR0H = (uint8)(TMR0_1->timer0_pre_load >> 8) ;     // here we set the preload at TMR0 REG so will not start from 0(RECALL)
        TMR0L = (uint8)(TMR0_1->timer0_pre_load)  ;    
        preloud_val =  TMR0_1->timer0_pre_load ;
           
   
    
    //STEP8 ---> FINALLY ENABLE IT 
        TMR0_ENABLE() ;
        
        
} ;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//THE ISR TO BE EXCUTED //////
////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNC IS THE ISR FUNCTION WHICH WILL BE EXCUTED WHEN THE INTERUPT HAPPENS
 */void TMRR0_ISR(void){

    TMR0_interupt_CLEAR_FLAG() ;
        TMR0H = (uint8)(preloud_val >> 8) ;
        TMR0L = (uint8)(preloud_val)  ;    
       
    if(interupt_callvack){interupt_callvack() ; };
}
////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST READS THE VALUE AT TMR0 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER0_READ_VALUE(const TIMER0_t *TMR1 , uint16 *value){
    if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
        uint8 val_high = TMR0H ;  uint8 val_low = TMR0L ;
       *value = val_low ;
       *value = value  + (val_high >> 8) ;
    }
    return ret ;
};


////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST WRITES A VALUE AT TMR0 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER0_WRITE_VALUE(const TIMER0_t *TMR1 , uint16 value){
 if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
       TMR0H = (uint8)(value >> 8) ;
       TMR0L = (uint8)value ; 
    }
    return ret ;
};
////////////////////////////////////////////////////////////////////////////////
