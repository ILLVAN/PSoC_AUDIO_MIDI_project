/*******************************************************************************
* File Name: debouncerClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_debouncerClock_H)
#define CY_CLOCK_debouncerClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void debouncerClock_Start(void) ;
void debouncerClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void debouncerClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void debouncerClock_StandbyPower(uint8 state) ;
void debouncerClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 debouncerClock_GetDividerRegister(void) ;
void debouncerClock_SetModeRegister(uint8 modeBitMask) ;
void debouncerClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 debouncerClock_GetModeRegister(void) ;
void debouncerClock_SetSourceRegister(uint8 clkSource) ;
uint8 debouncerClock_GetSourceRegister(void) ;
#if defined(debouncerClock__CFG3)
void debouncerClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 debouncerClock_GetPhaseRegister(void) ;
#endif /* defined(debouncerClock__CFG3) */

#define debouncerClock_Enable()                       debouncerClock_Start()
#define debouncerClock_Disable()                      debouncerClock_Stop()
#define debouncerClock_SetDivider(clkDivider)         debouncerClock_SetDividerRegister(clkDivider, 1u)
#define debouncerClock_SetDividerValue(clkDivider)    debouncerClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define debouncerClock_SetMode(clkMode)               debouncerClock_SetModeRegister(clkMode)
#define debouncerClock_SetSource(clkSource)           debouncerClock_SetSourceRegister(clkSource)
#if defined(debouncerClock__CFG3)
#define debouncerClock_SetPhase(clkPhase)             debouncerClock_SetPhaseRegister(clkPhase)
#define debouncerClock_SetPhaseValue(clkPhase)        debouncerClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(debouncerClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define debouncerClock_CLKEN              (* (reg8 *) debouncerClock__PM_ACT_CFG)
#define debouncerClock_CLKEN_PTR          ((reg8 *) debouncerClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define debouncerClock_CLKSTBY            (* (reg8 *) debouncerClock__PM_STBY_CFG)
#define debouncerClock_CLKSTBY_PTR        ((reg8 *) debouncerClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define debouncerClock_DIV_LSB            (* (reg8 *) debouncerClock__CFG0)
#define debouncerClock_DIV_LSB_PTR        ((reg8 *) debouncerClock__CFG0)
#define debouncerClock_DIV_PTR            ((reg16 *) debouncerClock__CFG0)

/* Clock MSB divider configuration register. */
#define debouncerClock_DIV_MSB            (* (reg8 *) debouncerClock__CFG1)
#define debouncerClock_DIV_MSB_PTR        ((reg8 *) debouncerClock__CFG1)

/* Mode and source configuration register */
#define debouncerClock_MOD_SRC            (* (reg8 *) debouncerClock__CFG2)
#define debouncerClock_MOD_SRC_PTR        ((reg8 *) debouncerClock__CFG2)

#if defined(debouncerClock__CFG3)
/* Analog clock phase configuration register */
#define debouncerClock_PHASE              (* (reg8 *) debouncerClock__CFG3)
#define debouncerClock_PHASE_PTR          ((reg8 *) debouncerClock__CFG3)
#endif /* defined(debouncerClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define debouncerClock_CLKEN_MASK         debouncerClock__PM_ACT_MSK
#define debouncerClock_CLKSTBY_MASK       debouncerClock__PM_STBY_MSK

/* CFG2 field masks */
#define debouncerClock_SRC_SEL_MSK        debouncerClock__CFG2_SRC_SEL_MASK
#define debouncerClock_MODE_MASK          (~(debouncerClock_SRC_SEL_MSK))

#if defined(debouncerClock__CFG3)
/* CFG3 phase mask */
#define debouncerClock_PHASE_MASK         debouncerClock__CFG3_PHASE_DLY_MASK
#endif /* defined(debouncerClock__CFG3) */

#endif /* CY_CLOCK_debouncerClock_H */


/* [] END OF FILE */
