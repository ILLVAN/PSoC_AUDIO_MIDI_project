/*******************************************************************************
* File Name: analogMUX.c
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

#include "analogMUX.h"

static uint8 analogMUX_lastChannel = analogMUX_NULL_CHANNEL;


/*******************************************************************************
* Function Name: analogMUX_Start
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
void analogMUX_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < analogMUX_CHANNELS ; chan++)
    {
#if (analogMUX_MUXTYPE == analogMUX_MUX_SINGLE)
        analogMUX_Unset(chan);
#else
        analogMUX_CYAMUXSIDE_A_Unset(chan);
        analogMUX_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    analogMUX_lastChannel = analogMUX_NULL_CHANNEL;
}


#if (!analogMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: analogMUX_Select
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
void analogMUX_Select(uint8 channel) 
{
    analogMUX_DisconnectAll();        /* Disconnect all previous connections */
    analogMUX_Connect(channel);       /* Make the given selection */
    analogMUX_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: analogMUX_FastSelect
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
void analogMUX_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( analogMUX_lastChannel != analogMUX_NULL_CHANNEL)
    {
        analogMUX_Disconnect(analogMUX_lastChannel);
    }

    /* Make the new channel connection */
#if (analogMUX_MUXTYPE == analogMUX_MUX_SINGLE)
    analogMUX_Set(channel);
#else
    analogMUX_CYAMUXSIDE_A_Set(channel);
    analogMUX_CYAMUXSIDE_B_Set(channel);
#endif


    analogMUX_lastChannel = channel;   /* Update last channel */
}


#if (analogMUX_MUXTYPE == analogMUX_MUX_DIFF)
#if (!analogMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: analogMUX_Connect
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
void analogMUX_Connect(uint8 channel) 
{
    analogMUX_CYAMUXSIDE_A_Set(channel);
    analogMUX_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: analogMUX_Disconnect
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
void analogMUX_Disconnect(uint8 channel) 
{
    analogMUX_CYAMUXSIDE_A_Unset(channel);
    analogMUX_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (analogMUX_ATMOSTONE)
/*******************************************************************************
* Function Name: analogMUX_DisconnectAll
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
void analogMUX_DisconnectAll(void) 
{
    if(analogMUX_lastChannel != analogMUX_NULL_CHANNEL) 
    {
        analogMUX_Disconnect(analogMUX_lastChannel);
        analogMUX_lastChannel = analogMUX_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
