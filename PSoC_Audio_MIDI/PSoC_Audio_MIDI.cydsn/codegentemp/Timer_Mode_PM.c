/*******************************************************************************
* File Name: Timer_Mode_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Mode.h"

static Timer_Mode_backupStruct Timer_Mode_backup;


/*******************************************************************************
* Function Name: Timer_Mode_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Mode_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Mode_SaveConfig(void) 
{
    #if (!Timer_Mode_UsingFixedFunction)
        Timer_Mode_backup.TimerUdb = Timer_Mode_ReadCounter();
        Timer_Mode_backup.InterruptMaskValue = Timer_Mode_STATUS_MASK;
        #if (Timer_Mode_UsingHWCaptureCounter)
            Timer_Mode_backup.TimerCaptureCounter = Timer_Mode_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Mode_UDB_CONTROL_REG_REMOVED)
            Timer_Mode_backup.TimerControlRegister = Timer_Mode_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Mode_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Mode_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Mode_RestoreConfig(void) 
{   
    #if (!Timer_Mode_UsingFixedFunction)

        Timer_Mode_WriteCounter(Timer_Mode_backup.TimerUdb);
        Timer_Mode_STATUS_MASK =Timer_Mode_backup.InterruptMaskValue;
        #if (Timer_Mode_UsingHWCaptureCounter)
            Timer_Mode_SetCaptureCount(Timer_Mode_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Mode_UDB_CONTROL_REG_REMOVED)
            Timer_Mode_WriteControlRegister(Timer_Mode_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Mode_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Mode_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Mode_Sleep(void) 
{
    #if(!Timer_Mode_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Mode_CTRL_ENABLE == (Timer_Mode_CONTROL & Timer_Mode_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Mode_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Mode_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Mode_Stop();
    Timer_Mode_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Mode_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Mode_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Mode_Wakeup(void) 
{
    Timer_Mode_RestoreConfig();
    #if(!Timer_Mode_UDB_CONTROL_REG_REMOVED)
        if(Timer_Mode_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Mode_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
