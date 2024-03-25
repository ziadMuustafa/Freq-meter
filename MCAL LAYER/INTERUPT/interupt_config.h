/* 
 * File:   interupt_config.h
 * Author: el msria
 *
 * Created on December 19, 2023, 4:34 PM
 */
// GENERAL DEFINATION
/*
HERE WE HAVE 2 IF STATMENTS TO DEFINE IF WE WILL USE PRIORITY LEVELS FEATURE OR USING GENERAL INETERUPT WITHOUT PIRIRITY
IF WE SET (PIRIORITY_LEVELS_ENABLE) TO (FEATURE_ENABLE) FROM (INTERUPTT_GEN_FEATURES.H) THE WE WILL HAVE ACCEESS TO THE SET OF 
FUNCTIONS WHICH WILL MAKE ME USE THE HIGH PIRIORITY OR LOW PIRIORITY AND IF WE SET (PIRIORITY_LEVELS_ENABLE) TO (FEATURE_DISABLE) WE WILL
 * ACCESS just the general interupt and prepheral interupt enable and disable without interupt
*/


#ifndef INTERUPT_CONFIG_H
#define	INTERUPT_CONFIG_H

// INCLUDES//////////////////////////////////////////////////////////////
#include "pic18f4620.h"
#include "../GPIO/HAL_GPIO.h"
#include "../STD_TYPES.h"
#include "interupt_gen_features.h"
#include "external_interupt.h"




//MACROS///////////////////////////////////////////////////////////////////
#define INTERUPT_ENABLE 1
#define INTERUPT_DISABLE 0
#define LOW_PRIORITY 0
#define HIGH_PRIORITY 1
#define INTERUPT_OCCUR 1
#define INTERUPT_NOT_OCUUR 0
#define RISING_EDGE 1
#define FALLING_EDGE 0


//MACRO FUNCTIONS///////////////////////////////////////////////////////////

#if PIRIORITY_LEVELS_ENABLE==FEATURE_ENABLE

#define INTERUPT_PRIORITY_ENABLE()       (RCONbits.IPEN = INTERUPT_ENABLE) ///* This macro will enable priority levels on interrupts. */

#define INTERUPT_PRIORITY_DISABLE()      (RCONbits.IPEN = INTERUPT_DISABLE) ///* This macro will disable  priority levels on interrupts. */

#define GLOBAL_INTERUPT_HIGH_PRIORITY_ENABLE()  (INTCONbits.GIEH = INTERUPT_ENABLE) ///* This macro will enable high priority global interrupts. */

#define GLOBAL_INTERUPT_HIGH_PRIORITY_DISABLE() (INTCONbits.GIEH = INTERUPT_DISABLE) ///* This macro will disable high priority global interrupts. */

#define GLOBAL_INTERUPT_LOW_PRIORITY_DISABLE()  (INTCONbits.GIEL = INTERUPT_DISABLE) ///* This macro will enable low priority global interrupts. */

#define GLOBAL_INTERUPT_LOW_PRIORITY_ENABLE()   (INTCONbits.GIEL = INTERUPT_ENABLE) ///* This macro will disable low priority global interrupts. */


#else

#define GENERAL_INTERUPT_ENABLE()    (INTCONbits.GIE = INTERUPT_ENABLE) ///* This macro will enable global interrupts. */

#define GENERAL_INTERUPT_DISABLE()   (INTCONbits.GIE = INTERUPT_DISABLE) ///* This macro will disable global interrupts. */

#define PREPHERAL_INTERUPT_ENABLE()  (INTCONbits.PEIE= INTERUPT_ENABLE) ///* This macro will enable peripheral interrupts. */

#define PREPHERAL_INTERUPT_DISABLE() (INTCONbits.PEIE= INTERUPT_DISABLE) ///* This macro will disable peripheral interrupts. */

#endif




#endif	/* INTERUPT_CONFIG_H */



