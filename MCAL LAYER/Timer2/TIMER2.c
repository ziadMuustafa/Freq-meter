#include "TIMER2.h"
uint8 ret =E_OK ; 
static uint16 preloud_val ;

///POINTER TO FUNCTIONS/////////////////////////////////////////////////////////
static void (*interupt_tmr2_callvack)(void) = NULL ; // pointer to function to save the callback func(which is comming from app layer)



///HELPER FUNCTIONS/////////////////////////////////////////////////////////////
/**
 * this func is a handler function which just assign the pointer to function we created to the callbak func (which is comming from app layer)
 * @param interupt_callback
 * @return 
 */
Std_ReturnType TMR2_INTERUPT_HANDELER(void (*interupt_callback)(void) ){
TMR2_interupt_CLEAR_FLAG() ;
if(interupt_callback == NULL){ret = E_NOT_OK ;}
else{
interupt_tmr2_callvack = interupt_callback ;
}
return ret  ;
}
///////////////////////////////////////////////////////////////////////////////



///MAIN FUNCTIONS//////////////////////////////////////////////////////////////
Std_ReturnType TIMER2_INIT(const TIMER2_t *TMR2_1){
   //WE HAVE SOME STEPS TO FOLLOW 
   
    //STEP1 ---> DISABLE IT 
    TMR2_DISABLE() ;
    
    
    //STEP2 ---> SET THE EDGE 
    /// no need for edge configration as it just rising edge counter
    
   
   
    //STEP3 ---> SET THE REG SIZE TYPE (AT 8 BIT 2 TIMES OR 16BIT ONE TIME )---> ITS JUST 16 BIT RECALL  
    //no need too as iys just 8 bit only ---> any way ba3aa
    
    
    
    //STEP4 ---> SET THE POST_SCALLER VALUE 
    #if POST_SCALLER_STATE==PRE_SCALER_IS_ON
    if(1){
        switch(TMR2_1->timer2_post_scaler_value){
            case postcale_TMR2_value_1_dev_1   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_1) ;break ;
            case postcale_TMR2_value_1_dev_2  : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_2) ;break ;
            case postcale_TMR2_value_1_dev_3   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_3) ;break ;
            case postcale_TMR2_value_1_dev_4   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_4) ;break ;
            case postcale_TMR2_value_1_dev_5   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_5) ;break ;
            case postcale_TMR2_value_1_dev_6   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_6) ;break ;
            case postcale_TMR2_value_1_dev_7   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_7) ;break ;
            case postcale_TMR2_value_1_dev_8   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_8) ;break ;
            case postcale_TMR2_value_1_dev_9   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_9) ;break ;
            case postcale_TMR2_value_1_dev_10   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_10) ;break ;
            case postcale_TMR2_value_1_dev_11   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_11) ;break ;
            case postcale_TMR2_value_1_dev_12   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_12) ;break ;
            case postcale_TMR2_value_1_dev_13   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_13) ;break ;
            case postcale_TMR2_value_1_dev_14   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_14) ;break ;
            case postcale_TMR2_value_1_dev_15   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_15) ;break ;
            case postcale_TMR2_value_1_dev_16   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_16) ;break ;
            
        }
    }
    #endif
    
    
    //STEP5 ---> SET THE PRE_SCALLER VALUE
    #if PRE_SCALLER_STATE==PRE_SCALER_IS_ON
    if(1){
        switch(TMR2_1->timer2_pre_scaler_value){
            case precale_TMR2_value_1_dev_1   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_1) ;break ;
            case precale_TMR2_value_1_dev_4  : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_2) ;break ;
            case precale_TMR2_value_1_dev_16   : TMR2_POST_SCALER_SET(postcale_TMR2_value_1_dev_3) ;break ;
            
            
        }
    }
    #endif
    
    
    
    //STEP6 ---> CONFIGURE THE INTERUPT
        #if TMR1_INTERUPT==FEATURE_ENABLE 
        GENERAL_INTERUPT_ENABLE();
        PREPHERAL_INTERUPT_ENABLE() ; 
        TMR2_interupt_ENABLE();
        TMR2_interupt_CLEAR_FLAG() ;
        
        #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
        gfgdgdfg
        #endif
        
        TMR2_INTERUPT_HANDELER(TMR2_1->interupt_callback) ;
        
        #endif

    
        
    //STEP7 ---> SET THE TIMER PRELOAD
       
        TMR2 = (uint8)(TMR2_1->timer2_pre_load)  ;    
        preloud_val =  TMR2_1->timer2_pre_load ; 
           
    
    
    //STEP8 ---> FINALLY ENABLE IT 
        TMR2_ENABLE() ;
        
        
} ;




//THE ISR TO BE EXCUTED //////
////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNC IS THE ISR FUNCTION WHICH WILL BE EXCUTED WHEN THE INTERUPT HAPPENS
 */
void TMRR2_ISR(void){
    TMR2_interupt_CLEAR_FLAG() ;
      //  TMR2H = (uint8)(preloud_val >> 8) ;
        TMR2 = (uint8)(preloud_val)  ;    
       
    if(interupt_tmr2_callvack){interupt_tmr2_callvack() ; };
}
////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST READS THE VALUE AT TMR2 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER2_READ_VALUE(const TIMER2_t *TMRR2 , uint8 *value){
    if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
    
       *value = TMR2 ;
       
    }
    return ret ;
};

////////////////////////////////////////////////////////////////////////////////
/**
 * THIS FUNCTION JUST WRITES A VALUE AT TMR2 REG 
 * @param TMR1
 * @param value
 * @return 
 */
Std_ReturnType TIMER2_WRITE_VALUE(const TIMER2_t *TMRR2 , uint8 value){
 if(TMR1 == NULL || value == NULL ){ret = E_NOT_OK ;}
    else{
     
       TMR2 = (uint8)value ;  
    }
    return ret ;
};
////////////////////////////////////////////////////////////////////////////////

    

