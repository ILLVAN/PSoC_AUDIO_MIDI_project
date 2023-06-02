/*******************************************************************************
* File Name: analogADC_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "analogADC.h"

static analogADC_BACKUP_STRUCT analogADC_backup =
{
    analogADC_DISABLED,
    analogADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: analogADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  analogADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void analogADC_SaveConfig(void) 
{
    analogADC_backup.deccr = analogADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: analogADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  analogADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void analogADC_RestoreConfig(void) 
{
    analogADC_DEC_CR_REG = analogADC_backup.deccr;
}


/*******************************************************************************
* Function Name: analogADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  analogADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void analogADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((analogADC_ACT_PWR_DEC_EN == (analogADC_PWRMGR_DEC_REG & analogADC_ACT_PWR_DEC_EN)) &&
       (analogADC_ACT_PWR_DSM_EN == (analogADC_PWRMGR_DSM_REG & analogADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        analogADC_backup.enableState = analogADC_ENABLED;
        if((analogADC_DEC_CR_REG & analogADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            analogADC_backup.enableState |= analogADC_STARTED;
        }
		
        /* Stop the configuration */
        analogADC_Stop();
    }
    else
    {
        /* Component is disabled */
        analogADC_backup.enableState = analogADC_DISABLED;
    }

    /* Save the user configuration */
    analogADC_SaveConfig();
}


/*******************************************************************************
* Function Name: analogADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  analogADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void analogADC_Wakeup(void) 
{
    /* Restore the configuration */
    analogADC_RestoreConfig();

    /* Enables the component operation */
    if(analogADC_backup.enableState != analogADC_DISABLED)
    {
        analogADC_Enable();
        if((analogADC_backup.enableState & analogADC_STARTED) != 0u)
        {
            analogADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
