/*******************************************************************************
* File Name: analogMUX.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_analogMUX_H)
#define CY_AMUX_analogMUX_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void analogMUX_Start(void) ;
#define analogMUX_Init() analogMUX_Start()
void analogMUX_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void analogMUX_Stop(void); */
/* void analogMUX_Select(uint8 channel); */
/* void analogMUX_Connect(uint8 channel); */
/* void analogMUX_Disconnect(uint8 channel); */
/* void analogMUX_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define analogMUX_CHANNELS  2u
#define analogMUX_MUXTYPE   1
#define analogMUX_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define analogMUX_NULL_CHANNEL 0xFFu
#define analogMUX_MUX_SINGLE   1
#define analogMUX_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if analogMUX_MUXTYPE == analogMUX_MUX_SINGLE
# if !analogMUX_ATMOSTONE
#  define analogMUX_Connect(channel) analogMUX_Set(channel)
# endif
# define analogMUX_Disconnect(channel) analogMUX_Unset(channel)
#else
# if !analogMUX_ATMOSTONE
void analogMUX_Connect(uint8 channel) ;
# endif
void analogMUX_Disconnect(uint8 channel) ;
#endif

#if analogMUX_ATMOSTONE
# define analogMUX_Stop() analogMUX_DisconnectAll()
# define analogMUX_Select(channel) analogMUX_FastSelect(channel)
void analogMUX_DisconnectAll(void) ;
#else
# define analogMUX_Stop() analogMUX_Start()
void analogMUX_Select(uint8 channel) ;
# define analogMUX_DisconnectAll() analogMUX_Start()
#endif

#endif /* CY_AMUX_analogMUX_H */


/* [] END OF FILE */
