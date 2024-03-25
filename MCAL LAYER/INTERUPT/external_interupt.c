#include "external_interupt.h"
#include "C:\Program Files\Microchip\xc8\v2.45\pic\include\c99\stdio.h"

uint8 ret = E_OK;
int rb4_flag  = 0 ;int rb5_flag  = 0 ;int rb6_flag  = 0 ;int rb7_flag  = 0 ;

////////////////////////////////////////////////////////////////////////////
//POINTER TO FUNCTIONS//////////////////////////////////////////////////////
static void(*int0_interupt_handler)(void) = NULL ;  // THIS IS A POINTER TO FUCTION JUST WILL BE ASSIGNED TO THE ISR POINTER TO FUNCTION 
static void(*int1_interupt_handler)(void) = NULL ; //WHICH WILL COME FROM THE MAIN FUNCTION(APP LAYER) TO USE IT IN THE MCAL LAYER
static void(*int2_interupt_handler)(void) = NULL ;//THIS IS CALLED CALLBACK NO DIRECT CALL 
///////////////////////////////////////////////////////////////////////////


static void(*RBx4_LOW_interupt_handler)(void) = NULL ;  // THIS IS A POINTER TO FUCTION JUST WILL BE ASSIGNED TO THE ISR POINTER TO FUNCTION 
static void(*RBx4_HIGH_interupt_handler)(void) = NULL ; //WHICH WILL COME FROM THE MAIN FUNCTION(APP LAYER) TO USE IT IN THE MCAL LAYER
static void(*RBx5_HIGH_interupt_handler)(void) = NULL ;//THIS IS CALLED CALLBACK NO DIRECT CALL 
static void(*RBx5_LOW_interupt_handler)(void) = NULL ;  // THIS IS A POINTER TO FUCTION JUST WILL BE ASSIGNED TO THE ISR POINTER TO FUNCTION 
static void(*RBx6_HIGH_interupt_handler)(void) = NULL ; //WHICH WILL COME FROM THE MAIN FUNCTION(APP LAYER) TO USE IT IN THE MCAL LAYER
static void(*RBx6_LOW_interupt_handler)(void) = NULL ;//THIS IS CALLED CALLBACK NO DIRECT CALL 
static void(*RBx7_LOW_interupt_handler)(void) = NULL ;  // THIS IS A POINTER TO FUCTION JUST WILL BE ASSIGNED TO THE ISR POINTER TO FUNCTION 
static void(*RBx7_HIGH_interupt_handler)(void) = NULL ; //WHICH WILL COME FROM THE MAIN FUNCTION(APP LAYER) TO USE IT IN THE MCAL LAYER
////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////
//HELPER FUNCTIONS//////////////////////////////////////////////////////////
//WE ARE USING HELPER FUNCTION TO MAKE IT EASIER TO SWITCH FOR ANOTHER MCU THEM WILL NOT CHANGE ALOT IN THE MAIN FUNCTIONS 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION RES FOR SET THE ENABLE OF THE INTERYPT NEEDED IN THE STRUCT INT0 , INT1 , INT2 ...
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INTx_ENABLE(const interupt_INTx *intx1){
      if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          switch(intx1->interupt_num){
              case INTT0 :
                  #if PIRIORITY_LEVELS_ENABLE==FEATURE_DIASABLE
                   GENERAL_INTERUPT_ENABLE() ;
                   PREPHERAL_INTERUPT_ENABLE() ;
                  #else
                   INTERUPT_PRIORITY_ENABLE() ;
                   if(intx1->interupt_piriority == HIGH_PRIORITY){
                   GLOBAL_INTERUPT_HIGH_PRIORITY_ENABLE() ;
                   }
                   else{
                   GLOBAL_INTERUPT_LOW_PRIORITY_ENABLE() ;
                   }
                   #endif
                   EXTERNAL_INT0_INTERUPT_ENABLE() ;break;   //USINR INTT0 , INTT1 ,, WIT DOUBLE TO TO PREVENT CRASHING WITH THE PRE DEFINED  
              
              case INTT1 :
                   #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
                    INTERUPT_PRIORITY_ENABLE() ;
                   if(intx1->interupt_piriority == LOW_PRIORITY){
                   GLOBAL_INTERUPT_LOW_PRIORITY_ENABLE() ;
                   
                   }
                   else if(intx1->interupt_piriority == HIGH_PRIORITY){
                   GLOBAL_INTERUPT_HIGH_PRIORITY_ENABLE() ;
                   }
                  
                  #else
                   GENERAL_INTERUPT_ENABLE() ;
                   PREPHERAL_INTERUPT_ENABLE() ;
                  #endif
                  
                   EXTERNAL_INT1_INTERUPT_ENABLE() ;break;   //USINR INTT0 , INTT1 ,, WIT DOUBLE TO TO PREVENT CRASHING WITH THE PRE DEFINED 
                   
              
              case INTT2 :
                  #if PIRIORITY_LEVELS_ENABLE==FEATURE_DIASABLE
                   GENERAL_INTERUPT_ENABLE() ;
                   PREPHERAL_INTERUPT_ENABLE() ;
                  #else
                   INTERUPT_PRIORITY_ENABLE() ;
                   if(intx1->interupt_piriority == HIGH_PRIORITY){
                   GLOBAL_INTERUPT_HIGH_PRIORITY_ENABLE() ;
                   }
                   else{
                   GLOBAL_INTERUPT_LOW_PRIORITY_ENABLE() ;
                   }
                  #endif 
                   EXTERNAL_INT2_INTERUPT_ENABLE() ;break;   //USINR INTT0 , INTT1 ,, WIT DOUBLE TO TO PREVENT CRASHING WITH THE PRE DEFINED 
          }
      }
    return ret  ;  
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION RES FOR CLEAR THE ENABLE(DISABLE) OF THE INTERYPT NEEDED IN THE STRUCT INT0 , INT1 , INT2 ...
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INTx_DISABLE(const interupt_INTx *intx1){
    if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          switch(intx1->interupt_num){
              case INTT0 :
                   EXTERNAL_INT0_INTERUPT_DIASABLE() ;break;
              case INTT1 :
                   EXTERNAL_INT1_INTERUPT_DISABLE() ;break;
              case INTT2 :
                   EXTERNAL_INT2_INTERUPT_DISABLE() ;break;
          }
      }
    return ret  ;  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION RES FOR SET THE EDGE OF THE INTERYPT NEEDED IN THE STRUCT (FALLING OR RISING)
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INTx_EDGE_CONFIG(const interupt_INTx *intx1){
    if(intx1 == NULL){ret = E_NOT_OK ;}
       else{
          switch(intx1->edge){
              case RISING_EDGE :
                  switch(intx1->interupt_num){ // NESTED SWITCH CASE TO CHECH WHICH INTERUPT SOURCE MUST SET THE EDGE FOR
                      case INTT0 :
                          EXTERNAL_INT0_INTERUPT_RISING_EDGE(); break ;
                      case INTT1 :
                          EXTERNAL_INT1_INTERUPT_RISING_EDGE(); break ;
                      case INTT2 :
                          EXTERNAL_INT2_INTERUPT_RISING_EDGE(); break ;
                  }                                             break ;
              case FALLING_EDGE :
                    switch(intx1->interupt_num){ // NESTED SWITCH CASE TO CHECH WHICH INTERUPT SOURCE MUST SET THE EDGE FOR
                      case INTT0 :
                          EXTERNAL_INT0_INTERUPT_FALLING_EDGE(); break ;
                      case INTT1 :
                          EXTERNAL_INT1_INTERUPT_FALLING_EDGE(); break ;
                      case INTT2 :
                          EXTERNAL_INT2_INTERUPT_FALLING_EDGE(); break ;
                                                                break ;
                  }                          
          }
      }
    return ret ;
  } ;
  //////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION RES FOR SET THE PRIRITY OF THE INTERYPT NEEDED IN THE STRUCT (LOW OR HIGH PRIRITY)
   * @param intx1
   * @return 
   */
 #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE      //USING THIS #IF TO CHECK IF WE ARE USING THE PRIORITY FEATURE OR NOT
  static Std_ReturnType INTERUPT_INTx_PRIORITY_CONFIG(const interupt_INTx *intx1){
      if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          switch(intx1->interupt_piriority){
              case HIGH_PRIORITY :
                  switch(intx1->interupt_num){ // NESTED SWITCH CASE TO CHECH WHICH INTERUPT SOURCE MUST SET THE EDGE FOR
                      case INTT0 :
                          break ; // INT0 HAS NO PRIORITY OPTIONS , ITS HIGH PRIORITY BY DEFAULT
                      case INTT1 :
                          INT1_USING_HIGH_PIRIORITY(); break ;
                      case INTT2 :
                          INT2_USING_HIGH_PIRIORITY(); break ;
                  }                                    break ;
              
              case LOW_PRIORITY :
                    switch(intx1->interupt_num){ // NESTED SWITCH CASE TO CHECH WHICH INTERUPT SOURCE MUST SET THE EDGE FOR
                      case INTT0 :
                          break ; // INT0 HAS NO PRIORITY OPTIONS , ITS HIGH PRIORITY BY DEFAULT
                      case INTT1 :
                          INT1_USING_LOW_PIRIORITY(); break ;
                      case INTT2 :
                          INT2_USING_LOW_PIRIORITY(); break ;
                                                      break ;
                  }                          
          }
      }
      return ret ;
  } ;
  #endif
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION RES FOR INIT THE PIN OF THE INTERYPT NEEDED IN THE STRUCT (PIN2 , PORTC OR PIN1 PORTC OR......  )
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INTx_PIN_INIT(const interupt_INTx *intx1){
      if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          gpio_pin_init(&(intx1->interupt_pin)) ;
      }
  } ;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION IS RES FOR CLEARING THE FLAG OF THE INTERUPT WHICH MUST BE MADE IN SOFTWARE TO PREVENT RECURSIVE INTERUPT 
   * @param intx1
   * @return 
   */  
  static Std_ReturnType INTERUPT_INTx_CLEAR_FLAG(const interupt_INTx *intx1){
    if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          switch(intx1->interupt_num){
              case INTT0 :
                   EXTERNAL_INT0_INTERUPT_CLRAR_FLAG() ;break;
              case INTT1 :
                   EXTERNAL_INT1_INTERUPT_CLRAR_FLAG() ;break;
              case INTT2 :
                   EXTERNAL_INT2_INTERUPT_CLRAR_FLAG() ;break;
          }
      }
    } ;
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
    
    
    
    
    
  //////////////////////////////////////////////////////////////////////////////  
 //HELPER FUNCTONS FOR RBx(ON CHANGE EXTERNAL INTERUPTS)////////////////////////  
////////////////////////////////////////////////////////////////////////////////
  // NO NEEEEEEEEEEEEEEED ///
    
 
    
 ////////////////////////////////////////////////////////////////////////////////////  
//INTx CALLBACK HANDELING HELPER FUNCTIONS///////////////////////////////////////////    
/////////////////////////////////////////////////////////////////////////////////////    
//CALLBACK HELPER FUNCTIONS
    /**
     * //THIS FUNCTION IS RES FOR ASSIGN THE P.TO.FUNCTION HERE TO THE P.T.FUNCTION WHICH COMMING FROM THE APP LAYER JUST TO STORE IT HERE 
     * @param intx1
     * @return 
     */
  static Std_ReturnType INTERUPT_INT0_CALLBACK_HANDLER(void(*interupt_handaler)(void)){
      if(NULL == interupt_handaler){ret = E_NOT_OK ; }
      else{
      int0_interupt_handler = interupt_handaler ;
      }
      return ret ;
  };
  ///////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION IS RES FOR ASSIGN THE P.TO.FUNCTION HERE TO THE P.T.FUNCTION WHICH COMMING FROM THE APP LAYER JUST TO STORE IT HERE  
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INT1_CALLBACK_HANDLER(void(*interupt_handaler)(void)){
      if(interupt_handaler == NULL){ret = E_NOT_OK ;}
      else{
      int1_interupt_handler = interupt_handaler ;
      }
      return ret ;
  } ;
  //////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNCTION IS RES FOR ASSIGN THE P.TO.FUNCTION HERE TO THE P.T.FUNCTION WHICH COMMING FROM THE APP LAYER JUST TO STORE IT HERE 
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INT2_CALLBACK_HANDLER(void(*interupt_handaler)(void)){
      if(interupt_handaler == NULL){ret = E_NOT_OK ;}
      else{
      int2_interupt_handler = interupt_handaler ; 
      }
  } ;
  ///////////////////////////////////////////////////////////////////////////////
  /**
   * //THIS FUNC CHECK WHICH INTx YOU WANT TO SET THE CALLBACK FOR INT0, INT1 OR INT2
   * @param intx1
   * @return 
   */
  static Std_ReturnType INTERUPT_INTx_SET_CALLBACK_ISR(const interupt_INTx *intx1){
  if(intx1 == NULL){ret = E_NOT_OK ;}
      else{
          switch(intx1->interupt_num){
              case INTT0 :
                INTERUPT_INT0_CALLBACK_HANDLER(intx1->ext_interupt) ;break;
              case INTT1 :
                INTERUPT_INT1_CALLBACK_HANDLER(intx1->ext_interupt) ;break;
              case INTT2 :
                INTERUPT_INT2_CALLBACK_HANDLER(intx1->ext_interupt) ;break;
          }
      }
    return ret  ;
  };
////////////////////////////////////////////////////////////////////////////////  
  
  
  
////////////////////////////////////////////////////////////////////////////////
//MAIN FUNCTIONS ///////////////////////////////////////////////////////////////
  /**
   * //THIS IS THE MAIN FUNCTION WHICH FINNALY INIT THE INTERUPT STRUCT OR OBJECT
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_intx_init(const interupt_INTx* inturupt1){
      if(inturupt1 == NULL){ret = E_NOT_OK ;}
      else{
      //WE HAVE STEPS MUST BE FOLLWED TO INIT THE INTERUPT
      //STEP1 ---> DISABLE THE INTERUPT (MUST BE DISABLED BEFORE INIT TO MAKE SURE IT DOESNT WORK DURING INITIALIZING IT)
       INTERUPT_INTx_DISABLE(inturupt1) ;
      //STEP2 ---> CLEAR THE INTERUPT FLAG
       INTERUPT_INTx_CLEAR_FLAG(inturupt1) ;
      //STEP3 ---> SET THE EDGE 
       INTERUPT_INTx_EDGE_CONFIG(inturupt1) ;
      
       //STEP4 ---> SET OR CHECK THE PRIORITY
       #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE 
       INTERUPT_INTx_PRIORITY_CONFIG(inturupt1) ;
       #endif
      
       //STEP5 ---> CONFIGURE OR INIT THE INTERUPT PIN 
       INTERUPT_INTx_PIN_INIT(inturupt1) ;
      //STEP6 ---> CONFIGURE THE INTERUPT CallBack FUNCTION
       INTERUPT_INTx_SET_CALLBACK_ISR(inturupt1) ;
      //STEP7 ---> FINNALY NOW ENABLE THE INTERUPT USING THE ENABLE HELPER FUNCTION(WHICH USE THE FUNCTION LIKE MACRO TO DO THE MISSION DIRECT) 
      INTERUPT_INTx_ENABLE(inturupt1) ;
      }
      return ret ;
  };
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///ISR FUNCTIONS --> WHICH WILL BE EXCUTED WHEN CALLING THE INTERUPT////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //THIS FUNCTIONS ARE THE FUNCTIONS WHICH WILL IMPLIMENT THE ISR CODE(WILL EXCUTE THE CALL BACK FUNCTION)
  void INT0_ISR(void){
  //MUST CLEAR THE FLAG
      EXTERNAL_INT0_INTERUPT_CLRAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      if(int0_interupt_handler){int0_interupt_handler() ;} //JUST CHECK IF THE int0_interupt_handler == NULL OR NOT
  }                                                       //IF NOT THAT MEANS IT STORES A P.T.FUNCTION WHICH CAOME FROM THE APP LAYER
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void INT1_ISR(void){
      //MUST CLEAR THE FLAG
      EXTERNAL_INT1_INTERUPT_CLRAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      if(int1_interupt_handler){int1_interupt_handler() ;} //JUST CHECK IF THE int1_interupt_handler == NULL OR NOT
  }                           
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void INT2_ISR(void){
      //MUST CLEAR THE FLAG
      EXTERNAL_INT2_INTERUPT_CLRAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      if(int2_interupt_handler){int2_interupt_handler() ;} //JUST CHECK IF THE int2_interupt_handler == NULL OR NOT
  }                           
  
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  
  
  
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////
 //RBX IS FUNCTIONS //////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////////////////////////////
   void RB4_ISR(uint8 RX){
      //MUST CLEAR THE FLAG
      EXT_RBX_CLEAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      switch(RX){
          case HIGH :
              if(RBx4_HIGH_interupt_handler){RBx4_HIGH_interupt_handler();break;}  
          case LOW :    
              if(RBx4_LOW_interupt_handler){RBx4_LOW_interupt_handler() ;break;} 
    
    
      } }
 ///////////////////////////////////////////////////////////////////////////////////////////
   void RB5_ISR(uint8 RX){
      //MUST CLEAR THE FLAG
      EXT_RBX_CLEAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      switch(RX){
          case HIGH :
              if(RBx5_HIGH_interupt_handler){RBx5_HIGH_interupt_handler() ;break;} 
          case LOW :    
              if(RBx5_LOW_interupt_handler) {RBx5_LOW_interupt_handler() ;break;}  
    
    
      } }
  ///////////////////////////////////////////////////////////////////////////////////////////
   void RB6_ISR(uint8 RX){
      //MUST CLEAR THE FLAG
      EXT_RBX_CLEAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      switch(RX){
          case HIGH :
              if(RBx6_HIGH_interupt_handler){RBx6_HIGH_interupt_handler() ;break;} 
          case LOW :    
              if(RBx6_LOW_interupt_handler){RBx6_LOW_interupt_handler() ;break;}   
    
    
      } }
 ///////////////////////////////////////////////////////////////////////////////////////////
   void RB7_ISR(uint8 RX){
      //MUST CLEAR THE FLAG
      EXT_RBX_CLEAR_FLAG()  ;
  //WE CAN WRITE CODE HERE TO EXCUTE
   
  //HERE THE CALL BACK FUNCTION WHICH WILL COME FROM THE APP LAYER (MADE BY THE USER)
      switch(RX){
          case HIGH :
              if(RBx7_HIGH_interupt_handler){RBx7_HIGH_interupt_handler() ;break ;} 
          case LOW :    
              if(RBx7_LOW_interupt_handler){RBx7_LOW_interupt_handler() ; break ;}   
    
    
      } }
  ///////////////////////////////////////////////////////////////////////////////////////////
  
  
 
   
   
   
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /**
   * //THIS IS A MAIN FUNCTION USED TO DEINIT THE INTx INTERUPT OR DISABLE IT(INTERNALLU USED THE DISABLE HELPER FUNCTION)
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_intx_Deinit(const interupt_INTx* inturupt1){
      if(inturupt1 == NULL){ret = E_NOT_OK ;}
      else{
      INTERUPT_INTx_DISABLE(inturupt1) ;
      }
  };
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * 
   * @param inturupt1
   * @return 
   */
  
  Std_ReturnType interupt_rbx_init(const interupt_RBx* inturupt1){
  
      if(inturupt1 == NULL){ret = E_NOT_OK ;}
      else{
      //WE HAVE STEPS MUST BE FOLLWED TO INIT THE INTERUPT
      //STEP1 ---> DISABLE THE INTERUPT (MUST BE DISABLED BEFORE INIT TO MAKE SURE IT DOESNT WORK DURING INITIALIZING IT)
       EXT_RBX_INTERUPT_DISABLE() ;
      //STEP2 ---> CLEAR THE INTERUPT FLAG
       EXT_RBX_CLEAR_FLAG() ;
      //STEP3 ---> SET THE EDGE 
      //HAS NO EDGE CONFIGRATION
      
       //STEP4 ---> SET OR CHECK THE PRIORITY
       #if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE
                  INTERUPT_PRIORITY_ENABLE() ;
                   if(inturupt1->interupt_piriority == HIGH_PRIORITY){
                   GLOBAL_INTERUPT_HIGH_PRIORITY_ENABLE() ;
                   EXT_RBX_INTERUPT_USING_HIGH_PIRIORITY() ;
                   }
                   else{
                   GLOBAL_INTERUPT_LOW_PRIORITY_ENABLE() ;
                   EXT_RBX_INTERUPT_USING_LOW_PIRIORITY() ;
                   }
                  #else
                   GENERAL_INTERUPT_ENABLE() ;
                   PREPHERAL_INTERUPT_ENABLE() ;
                  
                   #endif
            
      
       
      //STEP5 ---> CONFIGURE OR INIT THE INTERUPT PIN 
                   gpio_pin_init(&(inturupt1->interupt_pin)) ;
      
      
       //STEP6 ---> CONFIGURE THE INTERUPT CallBack FUNCTION
                   switch(inturupt1->interupt_num){
                       case PIN4 :
                           RBx4_HIGH_interupt_handler =  inturupt1->ext_interupt_HIGH ;
                           RBx4_LOW_interupt_handler =  inturupt1->ext_interupt_LOW ;int rb4_flag  = 1 ;  break ;
                       case PIN5 :
                           RBx5_HIGH_interupt_handler =  inturupt1->ext_interupt_HIGH ;
                           RBx5_LOW_interupt_handler =  inturupt1->ext_interupt_LOW ; int rb5_flag  = 1 ;break ;
                       case PIN6 :
                           RBx6_HIGH_interupt_handler =  inturupt1->ext_interupt_HIGH ;
                           RBx6_LOW_interupt_handler =  inturupt1->ext_interupt_LOW ;int rb6_flag  = 1 ; break ;
                       case PIN7 :
                           RBx7_HIGH_interupt_handler =  inturupt1->ext_interupt_HIGH ;
                           RBx7_LOW_interupt_handler =  inturupt1->ext_interupt_LOW ;int rb7_flag  = 1 ; break ;
                           
                           
                           
                   }
                           
                           
      //STEP7 ---> FINNALY NOW ENABLE THE INTERUPT USING THE ENABLE HELPER FUNCTION(WHICH USE THE FUNCTION LIKE MACRO TO DO THE MISSION DIRECT) 
      EXT_RBX_INTERUPT_ENABLE() ;
      }
      return ret ;
      
  };
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**
   * 
   * @param inturupt1
   * @return 
   */
  Std_ReturnType interupt_rbx_Deinit(const interupt_RBx* inturupt1){};
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
