/*******************************************************************************
* File Name: UART_TOESP_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_TOESP.h"


/***************************************
* Local data allocation
***************************************/

static UART_TOESP_BACKUP_STRUCT  UART_TOESP_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: UART_TOESP_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the UART_TOESP_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_TOESP_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_TOESP_SaveConfig(void)
{
    #if(UART_TOESP_CONTROL_REG_REMOVED == 0u)
        UART_TOESP_backup.cr = UART_TOESP_CONTROL_REG;
    #endif /* End UART_TOESP_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_TOESP_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_TOESP_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling UART_TOESP_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void UART_TOESP_RestoreConfig(void)
{
    #if(UART_TOESP_CONTROL_REG_REMOVED == 0u)
        UART_TOESP_CONTROL_REG = UART_TOESP_backup.cr;
    #endif /* End UART_TOESP_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: UART_TOESP_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The UART_TOESP_Sleep() API saves the current component state. Then it
*  calls the UART_TOESP_Stop() function and calls 
*  UART_TOESP_SaveConfig() to save the hardware configuration.
*  Call the UART_TOESP_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_TOESP_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_TOESP_Sleep(void)
{
    #if(UART_TOESP_RX_ENABLED || UART_TOESP_HD_ENABLED)
        if((UART_TOESP_RXSTATUS_ACTL_REG  & UART_TOESP_INT_ENABLE) != 0u)
        {
            UART_TOESP_backup.enableState = 1u;
        }
        else
        {
            UART_TOESP_backup.enableState = 0u;
        }
    #else
        if((UART_TOESP_TXSTATUS_ACTL_REG  & UART_TOESP_INT_ENABLE) !=0u)
        {
            UART_TOESP_backup.enableState = 1u;
        }
        else
        {
            UART_TOESP_backup.enableState = 0u;
        }
    #endif /* End UART_TOESP_RX_ENABLED || UART_TOESP_HD_ENABLED*/

    UART_TOESP_Stop();
    UART_TOESP_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_TOESP_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  UART_TOESP_Sleep() was called. The UART_TOESP_Wakeup() function
*  calls the UART_TOESP_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  UART_TOESP_Sleep() function was called, the UART_TOESP_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  UART_TOESP_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void UART_TOESP_Wakeup(void)
{
    UART_TOESP_RestoreConfig();
    #if( (UART_TOESP_RX_ENABLED) || (UART_TOESP_HD_ENABLED) )
        UART_TOESP_ClearRxBuffer();
    #endif /* End (UART_TOESP_RX_ENABLED) || (UART_TOESP_HD_ENABLED) */
    #if(UART_TOESP_TX_ENABLED || UART_TOESP_HD_ENABLED)
        UART_TOESP_ClearTxBuffer();
    #endif /* End UART_TOESP_TX_ENABLED || UART_TOESP_HD_ENABLED */

    if(UART_TOESP_backup.enableState != 0u)
    {
        UART_TOESP_Enable();
    }
}


/* [] END OF FILE */
