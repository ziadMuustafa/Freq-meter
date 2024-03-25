#include "interupt_manager.h"
#include "external_interupt.h"
#include "internal_inerupt.h"
#include "../TIMER0/TIMER0.h"
//#include "../ADC/ADC.h"
//#include "../../MCAL_LAYER/TIMER0/TIMER0.h"
 extern rb4_flag   ;
 extern rb5_flag   ;
  extern rb6_flag   ;
   extern rb7_flag   ;

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE //NESTED #IF

void __interrupt() InterruptManagerHigh(void){
   
    
    if((INTERUPT_ENABLE == INTCONbits.INT0IE) && (INTERUPT_ENABLE == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{ /* Nothing */ }
 
    if((INTERUPT_ENABLE == INTCON3bits.INT2IE) && (INTERUPT_ENABLE == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{ /* Nothing */ }
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERUPT_ENABLE == INTCON3bits.INT1E) && (INTERUPT_ENABLE == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else{ /* Nothing */ }
}



 // NESTED
#else

void __interrupt()  interupt_manager(void){
    if((INTCONbits.INT0IF == INTERUPT_ENABLE) && (INTCONbits.INT0IE == INTERUPT_ENABLE)){
            INT0_ISR() ; 
    
    }
     if((INTCON3bits.INT1IF == INTERUPT_ENABLE) && (INTCON3bits.INT1IE == INTERUPT_ENABLE)) {
            INT1_ISR() ; 
    }  
    
    if((INTCON3bits.INT2IF == INTERUPT_ENABLE) && (INTCON3bits.INT2IE == INTERUPT_ENABLE)) {
            INT2_ISR() ; 
    }  
    
    
    
    
  /*  if((PIR1bits.ADIF == INTERUPT_ENABLE) && (PIE1bits.ADIE  == INTERUPT_ENABLE)) {
           ADC_ISR() ; 
    }   */
    
    if((INTCONbits.TMR0IE == INTERUPT_ENABLE) && (INTCONbits.T0IF == INTERUPT_ENABLE) ) {
       TMRR0_ISR() ;
    }   
    
 /*   if((PIR1bits.TMR1IF == INTERUPT_ENABLE) && (PIE1bits.TMR1IE == INTERUPT_ENABLE) ) {
        TMRR1_ISR() ;
    }   */
    
    if((PIR1bits.TMR2IF == INTERUPT_ENABLE) && (PIE1bits.TMR2IE == INTERUPT_ENABLE) ) {
        TMRR2_ISR() ;
    }  
    
  /*  if((PIR2bits.TMR3IF == INTERUPT_ENABLE) && (PIE2bits.TMR3IE == INTERUPT_ENABLE) ) {
        TMRR3_ISR() ;
    }  
    
    if((PIR1bits.CCP1IF == INTERUPT_ENABLE) && (PIE1bits.CCP1IE == INTERUPT_ENABLE) ) {
         CCP1_ISR();
    }  
    
    if((PIR2bits.CCP2IF == INTERUPT_ENABLE) && (PIE1bits.CCP1IE == INTERUPT_ENABLE) ) {
         CCP2_ISR();
    }   */
    /*
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB4 == HIGH) ) {
        RB4_ISR(HIGH) ; rb4_flag  = 0 ;
    }  
     if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB4 == LOW) ) {
        RB4_ISR(LOW) ; rb4_flag  = 1 ;
    } 
    */
  
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB5 == HIGH)) {
        RB5_ISR(HIGH) ; rb5_flag = 0 ;
    }  
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB5 == LOW)) {
        RB5_ISR(LOW) ; rb5_flag = 1 ;
    } 
    
    
    
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB6 == HIGH)) {
        RB6_ISR(HIGH) ;  rb6_flag = 0  ;
    }  
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB6 == LOW)) {
        RB6_ISR(LOW) ; rb6_flag = 1;
    }  
    
    
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB7 == HIGH)) {
        RB7_ISR(HIGH) ; rb7_flag = 0 ;
    }  
    if((INTCONbits.RBIE == INTERUPT_ENABLE) && (INTCONbits.RBIF == INTERUPT_ENABLE) && (PORTBbits.RB7 == LOW) ) {
        RB7_ISR(LOW) ;  rb7_flag  =  1 ;
    }  
    

    
    

} 
   
    
  
#endif
