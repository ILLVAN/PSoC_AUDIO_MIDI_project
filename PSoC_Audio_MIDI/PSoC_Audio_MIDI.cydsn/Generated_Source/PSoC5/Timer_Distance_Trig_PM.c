/*******************************************************************************
* File Name: Timer_Distance_Trig_PM.c
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

#include "Timer_Distance_Trig.h"

static Timer_Distance_Trig_backupStruct Timer_Distance_Trig_backup;


/*******************************************************************************
* Function Name: Timer_Distance_Trig_SaveConfig
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
*  Timer_Distance_Trig_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Distance_Trig_SaveConfig(void) 
{
    #if (!Timer_Distance_Trig_UsingFixedFunction)
        Timer_Distance_Trig_backup.TimerUdb = Timer_Distance_Trig_ReadCounter();
        Timer_Distance_Trig_backup.InterruptMaskValue = Timer_Distance_Trig_STATUS_MASK;
        #if (Timer_Distance_Trig_UsingHWCaptureCounter)
            Timer_Distance_Trig_backup.TimerCaptureCounter = Timer_Distance_Trig_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Distance_Trig_UDB_CONTROL_REG_REMOVED)
            Timer_Distance_Trig_backup.TimerControlRegister = Timer_Distance_Trig_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Distance_Trig_RestoreConfig
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
*  Timer_Distance_Trig_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Distance_Trig_RestoreConfig(void) 
{   
    #if (!Timer_Distance_Trig_UsingFixedFunction)

        Timer_Distance_Trig_WriteCounter(Timer_Distance_Trig_backup.TimerUdb);
        Timer_Distance_Trig_STATUS_MASK =Timer_Distance_Trig_backup.InterruptMaskValue;
        #if (Timer_Distance_Trig_UsingHWCaptureCounter)
            Timer_Distance_Trig_SetCaptureCount(Timer_Distance_Trig_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Distance_Trig_UDB_CONTROL_REG_REMOVED)
            Timer_Distance_Trig_WriteControlRegister(Timer_Distance_Trig_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Distance_Trig_Sleep
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
*  Timer_Distance_Trig_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Distance_Trig_Sleep(void) 
{
    #if(!Timer_Distance_Trig_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Distance_Trig_CTRL_ENABLE == (Timer_Distance_Trig_CONTROL & Timer_Distance_Trig_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Distance_Trig_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Distance_Trig_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Distance_Trig_Stop();
    Timer_Distance_Trig_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Distance_Trig_Wakeup
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
*  Timer_Distance_Trig_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Distance_Trig_Wakeup(void) 
{
    Timer_Distance_Trig_RestoreConfig();
    #if(!Timer_Distance_Trig_UDB_CONTROL_REG_REMOVED)
        if(Timer_Distance_Trig_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Distance_Trig_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
