/*******************************************************************************
* File Name: analogADC_AMux.h
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

#if !defined(CY_AMUX_analogADC_AMux_H)
#define CY_AMUX_analogADC_AMux_H

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

void analogADC_AMux_Start(void) ;
#define analogADC_AMux_Init() analogADC_AMux_Start()
void analogADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void analogADC_AMux_Stop(void); */
/* void analogADC_AMux_Select(uint8 channel); */
/* void analogADC_AMux_Connect(uint8 channel); */
/* void analogADC_AMux_Disconnect(uint8 channel); */
/* void analogADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define analogADC_AMux_CHANNELS  2u
#define analogADC_AMux_MUXTYPE   1
#define analogADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define analogADC_AMux_NULL_CHANNEL 0xFFu
#define analogADC_AMux_MUX_SINGLE   1
#define analogADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if analogADC_AMux_MUXTYPE == analogADC_AMux_MUX_SINGLE
# if !analogADC_AMux_ATMOSTONE
#  define analogADC_AMux_Connect(channel) analogADC_AMux_Set(channel)
# endif
# define analogADC_AMux_Disconnect(channel) analogADC_AMux_Unset(channel)
#else
# if !analogADC_AMux_ATMOSTONE
void analogADC_AMux_Connect(uint8 channel) ;
# endif
void analogADC_AMux_Disconnect(uint8 channel) ;
#endif

#if analogADC_AMux_ATMOSTONE
# define analogADC_AMux_Stop() analogADC_AMux_DisconnectAll()
# define analogADC_AMux_Select(channel) analogADC_AMux_FastSelect(channel)
void analogADC_AMux_DisconnectAll(void) ;
#else
# define analogADC_AMux_Stop() analogADC_AMux_Start()
void analogADC_AMux_Select(uint8 channel) ;
# define analogADC_AMux_DisconnectAll() analogADC_AMux_Start()
#endif

#endif /* CY_AMUX_analogADC_AMux_H */


/* [] END OF FILE */
