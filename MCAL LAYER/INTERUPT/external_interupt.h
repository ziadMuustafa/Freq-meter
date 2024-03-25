/* 
 * File:   external_interupt.h
 * Author: el msria
 *
 * Created on December 19, 2023, 4:36 PM
 */

//GENERAL DEFINITION
/*
 * HERE WE HAVE 2 NESTED #IF STATMENT FOR THE 2 TYPES OF EXTERNAL INTERUPTS (INTX , ON CHANG(RBX))
 * 
 * //////////////////
 * FIRST TYPE (INTX)
 * 
 * #IF IF WE (SET EXTERNAL_INTERUPT_INTX_ENABLE) TO (FEATURE_ENABLE) FROM (INTERUPTT_GEN_FEATURES.H) T
 * THEN WE HAVE ACCESS TO THE FUNCTIONS WHICH MAKE ME CONTROL INT0 ,INT1, INT2
 * (ENABLE INT0 OR DISABLE IT)(CLEAR INT0 FLAG)(USING INT0 ON FALLING EDGE)(USING INT0 ON RISING EDGE)
 * (ENABLE INT1 OR DISABLE IT)(CLEAR INT1 FLAG)(USING INT1 ON FALLING EDGE)(USING INT1 ON RISING EDGE)
 * (ENABLE INT2 OR DISABLE IT)(CLEAR INT2 FLAG)(USING INT2 ON FALLING EDGE)(USING INT2 ON RISING EDGE)
 * HERE WE HAVE ANOTHER IF INSIDE THIS IF (NESTED IF) TO CHECK IF WE USING PIRIORITY FEATURE OR NOT(FROM INTERUPTT_GEN_FEATURES.H )
 * 
 * #IF ////(NESTED)/// IF WE (PIRIORITY_FEATURE_ENABLE) TO (FEATURE_ENABLE) FROM (INTERUPTT_GEN_FEATURES.H) T
 * THEN IF WE USED IT ACCESS HIGH OR LOW PIRIORITY FEATURE FUNCTIONS AND IF NOT , WILL NOT ACCESS THEM
 * #ENDIF ///(NESTED)///
 * 
 * #ENDID // (EXTERNAL FOR THE FIRST #IF)

 */
//AND SAME CONCEPT FOR THE SECOND TYPE (ON CHANGE))
//////////////////////////////////////////////////////////////////////////////
#ifndef EXTERNAL_INTERUPT_H
#define	EXTERNAL_INTERUPT_H

//INCLUDES////////////////////////////////////////////////////////////////// 
#include "interupt_config.h"
#include "C:\Program Files\Microchip\xc8\v2.45\pic\include\c99\stdio.h"





//MACRO FUNCTIONS////////////////////////////////////////////////////////////

//FIRST TYPE (INTX)
#if EXTERNAL_INTERUPT_INTX_ENABLE==FEATURE_ENABLE


#define EXTERNAL_INT0_INTERUPT_ENABLE()   (INTCONbits.INT0IE = 1)

#define EXTERNAL_INT0_INTERUPT_DIASABLE() (INTCONbits.INT0IE = 0)

#define EXTERNAL_INT0_INTERUPT_CLRAR_FLAG()     (INTCONbits.INT0IF = 0)

#define EXTERNAL_INT0_INTERUPT_FALLING_EDGE()   (INTCON2bits.INTEDG0 = 0)

#define EXTERNAL_INT0_INTERUPT_RISING_EDGE()    (INTCON2bits.INTEDG0 = 1)
////////////////////////
#define EXTERNAL_INT1_INTERUPT_ENABLE()          (INTCON3bits.INT1IE = 1)

#define EXTERNAL_INT1_INTERUPT_DISABLE()         (INTCON3bits.INT1IE = 0)

#define EXTERNAL_INT1_INTERUPT_CLRAR_FLAG()       (INTCON3bits.INT1IF = 0)

#define EXTERNAL_INT1_INTERUPT_FALLING_EDGE()      (INTCON2bits.INTEDG1 = 0)

#define EXTERNAL_INT1_INTERUPT_RISING_EDGE()       (INTCON2bits.INTEDG1 = 1)

//////////////////////////
#define EXTERNAL_INT2_INTERUPT_ENABLE()          (INTCON3bits.INT2IE = 1)

#define EXTERNAL_INT2_INTERUPT_DISABLE()         (INTCON3bits.INT2IE = 0)

#define EXTERNAL_INT2_INTERUPT_CLRAR_FLAG()       (INTCON3bits.INT2IF = 0)

#define EXTERNAL_INT2_INTERUPT_FALLING_EDGE()      (INTCON2bits.INTEDG2 = 0)

#define EXTERNAL_INT2_INTERUPT_RISING_EDGE()       (INTCON2bits.INTEDG2 = 1)


//SAME FOR INT1 ,INT2, ... AND ALL EXTERNAL INTERUPTS

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE //NESTED #IF

#define INT1_USING_HIGH_PIRIORITY() (INTCON3bits.INT1IP = 1)

#define INT1_USING_LOW_PIRIORITY()  (INTCON3bits.INT1IP = 0)

#define INT2_USING_HIGH_PIRIORITY() (INTCON3bits.INT2IP = 1)

#define INT2_USING_LOW_PIRIORITY()  (INTCON3bits.INT2IP = 0)

// WE DIDNT SET INT0 PIRIORITY AS IT HAS NO PIRIORITY SO WE JUST SET INT1 AND INT2
#endif // NESTED
#endif


/////////////////////////////////////////////////////////////////////////////////////


//SECOND TYPE(ON CHANGE)
#if EXTERNAL_INTERUPT_ON_CHANGE_ENABLE==FEATURE_ENABLE 

#define EXT_RBX_INTERUPT_ENABLE() (INTCONbits.RBIE = 1)

#define EXT_RBX_INTERUPT_DISABLE() (INTCONbits.RBIE = 0)

#define EXT_RBX_CLEAR_FLAG() (INTCONbits.RBIF = 0) 

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE   //NESTED

#define EXT_RBX_INTERUPT_USING_HIGH_PIRIORITY() (INTCON2bits.RBIP = 1)

#define EXT_RBX_INTERUPT_USING_LOW_PIRIORITY() (INTCON2bits.RBIP = 0)


#define USING_
#endif  // NESTED
#endif 
////////////////////////////////////////////////////////////////////////////////


//USER DEFINED DATA TYPES////////////////////////////////////////////////
typedef enum {
    INTT0,
    INTT1,
    INTT2,

}INTX;
typedef enum {
    RBB0,
    RBB1,        
}RBx;
typedef struct{
     void (*ext_interupt)(void) ;  // NEED TO UNDERSTAND // THIS IS FUNCTION POINTER
     pin_config interupt_pin ;    // NEED TO UNDERSTAND // THE INTERUPT IN WHICH PIN
     int interupt_num  ;
     int interupt_piriority ;
     int edge ;

}interupt_INTx ;

typedef struct{
     void (*ext_interupt_HIGH)(void) ; // NEED TO UNDERSTAND
     void (*ext_interupt_LOW)(void) ; // NEED TO UNDERSTAND
     pin_config interupt_pin ;   // NEED TO UNDERSTAND // THE INTERUPT IN WHICH PIN
     int interupt_num  ; 
     int interupt_piriority ;

}interupt_RBx ; 

//HELPER FUNCTIONS//////////////////////////////////////////////////////////
  
  //INTx HELPER FUNCTIONS
  static Std_ReturnType INTERUPT_INTx_ENABLE(const interupt_INTx *intx1) ;
  static Std_ReturnType INTERUPT_INTx_DISABLE(const interupt_INTx *intx1) ;
  static Std_ReturnType INTERUPT_INTx_EDGE_CONFIG(const interupt_INTx *intx1) ;
  static Std_ReturnType INTERUPT_INTx_PRIORITY_CONFIG(const interupt_INTx *intx1) ;
  static Std_ReturnType INTERUPT_INTx_PIN_INIT(const interupt_INTx *intx1) ;
  static Std_ReturnType INTERUPT_INTx_CLEAR_FLAG(const interupt_INTx *intx1) ;

  //CALLBACK HELPER FUNCTIONS HANDELING
  static Std_ReturnType INTERUPT_INT0_CALLBACK_HANDLER(void(*interupt_handaler)(void)) ;  //GET A POINTER TO FUNCTION AS A PARAMETER
  static Std_ReturnType INTERUPT_INT1_CALLBACK_HANDLER(void(*interupt_handaler)(void)) ;  //GET A POINTER TO FUNCTION AS A PARAMETER
  static Std_ReturnType INTERUPT_INT2_CALLBACK_HANDLER(void(*interupt_handaler)(void)) ;  //GET A POINTER TO FUNCTION AS A PARAMETER
  static Std_ReturnType INTERUPT_INTx_SET_CALLBACK_ISR(const interupt_INTx *intx1) ;

  //RBx HELPER FUNCTIONS
  //NO NEEEEEEEEEEEEED

  //RBx OR ON CHANGE EXTERNEL INTERUPTS HAVE NO EDGE SETTING 
////////////////////////////////////////////////////////////////////////////////

//FUNCTIONS DECLERATIONS
  /**
   * 
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_intx_init(const interupt_INTx* inturupt1);
 ///////////////////////////////////////////////////////////////////////////////
  
  //THIS FUNCTIONS ARE THE FUNCTIONS WHICH WILL IMPLIMENT THE ISR CODE(WILL EXCUTE THE CALL BACK FUNCTION)
  void INT0_ISR(void);
  void INT1_ISR(void);
  void INT2_ISR(void);
  
  
  void RB4_ISR(uint8 RX) ;
  void RB5_ISR(uint8 RX) ;
  void RB6_ISR(uint8 RX) ;
  void RB7_ISR(uint8 RX) ;

 /////////////////////////////////////////////////////////////////////////////// 
  
  /**
   * 
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_intx_Deinit(const interupt_INTx* inturupt1);
  //////////////////////////////////////////////////////////////////////////////
  /**
   * 
   * @param inturupt1
   * @return 
   */
  
  Std_ReturnType interupt_rbx_init(const interupt_RBx* inturupt1);
  ////////////////////////////////////////////////////////////////////////////
  /**
   * 
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_rbx_Deinit(const interupt_RBx* inturupt1);
  ////////////////////////////////////////////////////////////////////////////

  

#endif	/* EXTERNAL_INTERUPT_H */



