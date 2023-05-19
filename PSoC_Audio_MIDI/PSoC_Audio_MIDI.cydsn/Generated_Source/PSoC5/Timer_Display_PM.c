/*******************************************************************************
* File Name: Timer_Display_PM.c
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

#include "Timer_Display.h"

static Timer_Display_backupStruct Timer_Display_backup;


/*******************************************************************************
* Function Name: Timer_Display_SaveConfig
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
*  Timer_Display_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Display_SaveConfig(void) 
{
    #if (!Timer_Display_UsingFixedFunction)
        Timer_Display_backup.TimerUdb = Timer_Display_ReadCounter();
        Timer_Display_backup.InterruptMaskValue = Timer_Display_STATUS_MASK;
        #if (Timer_Display_UsingHWCaptureCounter)
            Timer_Display_backup.TimerCaptureCounter = Timer_Display_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Display_UDB_CONTROL_REG_REMOVED)
            Timer_Display_backup.TimerControlRegister = Timer_Display_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Display_RestoreConfig
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
*  Timer_Display_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Display_RestoreConfig(void) 
{   
    #if (!Timer_Display_UsingFixedFunction)

        Timer_Display_WriteCounter(Timer_Display_backup.TimerUdb);
        Timer_Display_STATUS_MASK =Timer_Display_backup.InterruptMaskValue;
        #if (Timer_Display_UsingHWCaptureCounter)
            Timer_Display_SetCaptureCount(Timer_Display_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Display_UDB_CONTROL_REG_REMOVED)
            Timer_Display_WriteControlRegister(Timer_Display_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Display_Sleep
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
*  Timer_Display_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Display_Sleep(void) 
{
    #if(!Timer_Display_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Display_CTRL_ENABLE == (Timer_Display_CONTROL & Timer_Display_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Display_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Display_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Display_Stop();
    Timer_Display_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Display_Wakeup
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
*  Timer_Display_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Display_Wakeup(void) 
{
    Timer_Display_RestoreConfig();
    #if(!Timer_Display_UDB_CONTROL_REG_REMOVED)
        if(Timer_Display_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Display_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
