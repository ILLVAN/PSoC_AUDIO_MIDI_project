/*******************************************************************************
* File Name: analogADC_X_PM.c
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

#include "analogADC_X.h"

static analogADC_X_BACKUP_STRUCT analogADC_X_backup =
{
    analogADC_X_DISABLED,
    analogADC_X_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: analogADC_X_SaveConfig
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
*  analogADC_X_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void analogADC_X_SaveConfig(void) 
{
    analogADC_X_backup.deccr = analogADC_X_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: analogADC_X_RestoreConfig
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
*  analogADC_X_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void analogADC_X_RestoreConfig(void) 
{
    analogADC_X_DEC_CR_REG = analogADC_X_backup.deccr;
}


/*******************************************************************************
* Function Name: analogADC_X_Sleep
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
*  analogADC_X_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void analogADC_X_Sleep(void) 
{
    /* Save ADC enable state */
    if((analogADC_X_ACT_PWR_DEC_EN == (analogADC_X_PWRMGR_DEC_REG & analogADC_X_ACT_PWR_DEC_EN)) &&
       (analogADC_X_ACT_PWR_DSM_EN == (analogADC_X_PWRMGR_DSM_REG & analogADC_X_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        analogADC_X_backup.enableState = analogADC_X_ENABLED;
        if((analogADC_X_DEC_CR_REG & analogADC_X_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            analogADC_X_backup.enableState |= analogADC_X_STARTED;
        }
		
        /* Stop the configuration */
        analogADC_X_Stop();
    }
    else
    {
        /* Component is disabled */
        analogADC_X_backup.enableState = analogADC_X_DISABLED;
    }

    /* Save the user configuration */
    analogADC_X_SaveConfig();
}


/*******************************************************************************
* Function Name: analogADC_X_Wakeup
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
*  analogADC_X_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void analogADC_X_Wakeup(void) 
{
    /* Restore the configuration */
    analogADC_X_RestoreConfig();

    /* Enables the component operation */
    if(analogADC_X_backup.enableState != analogADC_X_DISABLED)
    {
        analogADC_X_Enable();
        if((analogADC_X_backup.enableState & analogADC_X_STARTED) != 0u)
        {
            analogADC_X_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
