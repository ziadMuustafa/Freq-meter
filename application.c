/* 
 * File:   application.c
 * Author: el msria
 *
 * Created on March 19, 2024, 9:30 PM
 */

//INCLUDES///////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "application.h"

/*
 * 
 */

#define _XTAL_FREQ 4000000UL 

 volatile uint16 timer_count = 0 ; volatile uint16 INTERUPT_COUNTER = 0 ; volatile uint16 NUMS_OF_OVER_FLOW ;volatile uint32 RESED_TMR_VAL ;
 volatile uint32 final_val = 0 ; volatile uint32 final = 0 ; volatile uint32 final_edit = 0 ;
 volatile int freq_hunds ;
 volatile int freq_tens  ;
 volatile int freq_ones  ;  volatile int key =0 ; const volatile uint32 res ;

///DECLERATIONS/////////////////////////////////////////////////////////////////
interupt_INTx intx1 ={
.edge = RISING_EDGE ,
.interupt_num = INTT0 ,
.interupt_pin.pin_direction = INPUT , .interupt_pin.pin_num = PIN0 , .interupt_pin.pin_port =PORTB_INDEX ,
.ext_interupt = isr_0 ,
.interupt_piriority = HIGH_PRIORITY ,
}  ;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIMER0_t TMR0_1 ={
.timer0_clc_sorce = TIMER_MODE ,
.timer0_rg_bits = USING_16BIT ,
.timer0_pre_scaler_value = Prescale_value_1_dev_2 ,
.timer0_pre_load = 0 ,
.interupt_callback = TMR0_ISR_1 ,        
}; 

///////////////////////////////////////////////
TIMER2_t t2= {
.interupt_callback = TMR2_ISR_1 ,
.timer2_post_scaler_value = 0 ,
.timer2_pre_scaler_value  = 0 ,  
.timer2_pre_load  = 0 ,
} ;
////////////////////////////////////////////////////////////////////////////////
lcd_8bit_t lcd1 ={
.data_pins[0].pin_direction = OUTPUT , .data_pins[0].pin_num =0 ,
.data_pins[0].pin_port =PORTD_INDEX  , .data_pins[0].pin_state =HIGH ,

.data_pins[1].pin_direction = OUTPUT , .data_pins[1].pin_num =1 ,
.data_pins[1].pin_port =PORTD_INDEX  , .data_pins[1].pin_state =HIGH ,

.data_pins[2].pin_direction = OUTPUT , .data_pins[2].pin_num =2 ,
.data_pins[2].pin_port =PORTD_INDEX  , .data_pins[2].pin_state =HIGH ,

.data_pins[3].pin_direction = OUTPUT , .data_pins[3].pin_num =3 ,
.data_pins[3].pin_port =PORTD_INDEX  , .data_pins[3].pin_state =HIGH ,

.data_pins[4].pin_direction = OUTPUT , .data_pins[4].pin_num =4 ,
.data_pins[4].pin_port =PORTD_INDEX  , .data_pins[4].pin_state =HIGH ,

.data_pins[5].pin_direction = OUTPUT , .data_pins[5].pin_num =5 ,
.data_pins[5].pin_port =PORTD_INDEX  , .data_pins[5].pin_state =HIGH ,

.data_pins[6].pin_direction = OUTPUT , .data_pins[6].pin_num =6 ,
.data_pins[6].pin_port =PORTD_INDEX  , .data_pins[6].pin_state =HIGH ,

.data_pins[7].pin_direction = OUTPUT , .data_pins[7].pin_num =7 ,
.data_pins[7].pin_port =PORTD_INDEX  , .data_pins[7].pin_state =HIGH ,

.rs_pin.pin_direction = OUTPUT , .rs_pin.pin_num = 6 ,
.rs_pin.pin_port = PORTC_INDEX , .rs_pin.pin_state = HIGH ,

.enable_pin.pin_direction = OUTPUT , .enable_pin.pin_num =7 ,
.enable_pin.pin_port = PORTC_INDEX , .enable_pin.pin_state =HIGH ,
};
////////////////////////////////////////////////////////////////////////////////


int main(){

 if(key==0){
 lcd_8bit_init(&lcd1); key ++ ; 
 }   
 TIMER0_INIT(&TMR0_1) ;   ADCON1bits.PCFG = 0B1111 ; interupt_intx_init(&intx1)  ;
 
while(1){
 
  
  key ++ ;    
    
 
 // lcd_8bit_send_char_data( &lcd1 , (final/100) + '0' ) ;
  if(key == 3) {while(1){} ;} 

}
 
    return (EXIT_SUCCESS);
}




/***********************************OPERATION FUNCTIONS***************************************************/
/*********************************************************************************************************/
void WELCOMING(void) {
    
lcd_8bit_send_string_pos( &lcd1 , "******* WELCOME *******" ,  2 , 5)  ;
__delay_ms(400) ;
lcd_8bit_send_command( &lcd1 ,  LCD_CLEAR)  ;
lcd_8bit_send_string(&lcd1 ,"The Frequency   is nrearly " );
};
/********************************************************************************************************/
void SEPARATE_NUM(uint32 freq ,int *freq_hunds , int *freq_tens , int *freq_ones  ){
    
     *freq_hunds =  freq / 100;
     *freq_tens  = (freq / 10) % 10;
     *freq_ones  =  freq % 10;

    
};

/***************************************************************************************/
void DISPLAY_FREQ(int *freq_hunds , int *freq_tens , int *freq_ones  ){
    WELCOMING();
    char hunds  = *freq_hunds  + '0'   ; lcd_8bit_send_char_data( &lcd1 , hunds )  ;
    char tens   = *freq_tens   + '0'   ; lcd_8bit_send_char_data( &lcd1 , tens ) ;
    char ones   = *freq_ones   + '0'   ; lcd_8bit_send_char_data( &lcd1 , ones ) ;
    
};
/*****************************************************************************************/







/*************************************ISR FUNCTIONS***********************************************************************/
/***********************************************************************************************************************/
void isr_0(void){
    
    INTERUPT_COUNTER ++ ; 
 
    if(INTERUPT_COUNTER == 1){ TMR0 = 0 ;};
    if(INTERUPT_COUNTER == 2){NUMS_OF_OVER_FLOW = timer_count ; RESED_TMR_VAL = TMR0 ;  
    final_val = ((NUMS_OF_OVER_FLOW * 258.00 ) + RESED_TMR_VAL) / 1.00 ; 
 
    final = (1.00000000/(double)final_val) *1000000.000000 ;
    if(final<75){ final_edit = final + (.05)*final ;}
    if(final>75){ final_edit = final - final*(.003) + 2;}

  //  final_edit = final + (0.04)*final ;
    SEPARATE_NUM(final_edit ,&freq_hunds , &freq_tens, &freq_ones ) ;
    DISPLAY_FREQ(&freq_hunds , &freq_tens, &freq_ones ) ;
     
    };
}
/***********************************************************************************************/

void TMR2_ISR_1(void){
timer_count ++ ;

}
/************************************************************************************************/
void TMR0_ISR_1(void){
timer_count ++ ;

}

/**************************************************************************************************/