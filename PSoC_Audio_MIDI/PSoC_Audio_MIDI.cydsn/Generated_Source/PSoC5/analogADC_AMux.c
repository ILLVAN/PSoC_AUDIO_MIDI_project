/*******************************************************************************
* File Name: analogADC_AMux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "analogADC_AMux.h"

static uint8 analogADC_AMux_lastChannel = analogADC_AMux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: analogADC_AMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < analogADC_AMux_CHANNELS ; chan++)
    {
#if (analogADC_AMux_MUXTYPE == analogADC_AMux_MUX_SINGLE)
        analogADC_AMux_Unset(chan);
#else
        analogADC_AMux_CYAMUXSIDE_A_Unset(chan);
        analogADC_AMux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    analogADC_AMux_lastChannel = analogADC_AMux_NULL_CHANNEL;
}


#if (!analogADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: analogADC_AMux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_Select(uint8 channel) 
{
    analogADC_AMux_DisconnectAll();        /* Disconnect all previous connections */
    analogADC_AMux_Connect(channel);       /* Make the given selection */
    analogADC_AMux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: analogADC_AMux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( analogADC_AMux_lastChannel != analogADC_AMux_NULL_CHANNEL)
    {
        analogADC_AMux_Disconnect(analogADC_AMux_lastChannel);
    }

    /* Make the new channel connection */
#if (analogADC_AMux_MUXTYPE == analogADC_AMux_MUX_SINGLE)
    analogADC_AMux_Set(channel);
#else
    analogADC_AMux_CYAMUXSIDE_A_Set(channel);
    analogADC_AMux_CYAMUXSIDE_B_Set(channel);
#endif


    analogADC_AMux_lastChannel = channel;   /* Update last channel */
}


#if (analogADC_AMux_MUXTYPE == analogADC_AMux_MUX_DIFF)
#if (!analogADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: analogADC_AMux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_Connect(uint8 channel) 
{
    analogADC_AMux_CYAMUXSIDE_A_Set(channel);
    analogADC_AMux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: analogADC_AMux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_Disconnect(uint8 channel) 
{
    analogADC_AMux_CYAMUXSIDE_A_Unset(channel);
    analogADC_AMux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (analogADC_AMux_ATMOSTONE)
/*******************************************************************************
* Function Name: analogADC_AMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void analogADC_AMux_DisconnectAll(void) 
{
    if(analogADC_AMux_lastChannel != analogADC_AMux_NULL_CHANNEL) 
    {
        analogADC_AMux_Disconnect(analogADC_AMux_lastChannel);
        analogADC_AMux_lastChannel = analogADC_AMux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
