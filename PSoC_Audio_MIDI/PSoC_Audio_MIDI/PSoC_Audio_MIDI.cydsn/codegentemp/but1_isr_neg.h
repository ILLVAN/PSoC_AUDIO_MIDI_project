/*******************************************************************************
* File Name: but1_isr_neg.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_but1_isr_neg_H)
#define CY_ISR_but1_isr_neg_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void but1_isr_neg_Start(void);
void but1_isr_neg_StartEx(cyisraddress address);
void but1_isr_neg_Stop(void);

CY_ISR_PROTO(but1_isr_neg_Interrupt);

void but1_isr_neg_SetVector(cyisraddress address);
cyisraddress but1_isr_neg_GetVector(void);

void but1_isr_neg_SetPriority(uint8 priority);
uint8 but1_isr_neg_GetPriority(void);

void but1_isr_neg_Enable(void);
uint8 but1_isr_neg_GetState(void);
void but1_isr_neg_Disable(void);

void but1_isr_neg_SetPending(void);
void but1_isr_neg_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the but1_isr_neg ISR. */
#define but1_isr_neg_INTC_VECTOR            ((reg32 *) but1_isr_neg__INTC_VECT)

/* Address of the but1_isr_neg ISR priority. */
#define but1_isr_neg_INTC_PRIOR             ((reg8 *) but1_isr_neg__INTC_PRIOR_REG)

/* Priority of the but1_isr_neg interrupt. */
#define but1_isr_neg_INTC_PRIOR_NUMBER      but1_isr_neg__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable but1_isr_neg interrupt. */
#define but1_isr_neg_INTC_SET_EN            ((reg32 *) but1_isr_neg__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the but1_isr_neg interrupt. */
#define but1_isr_neg_INTC_CLR_EN            ((reg32 *) but1_isr_neg__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the but1_isr_neg interrupt state to pending. */
#define but1_isr_neg_INTC_SET_PD            ((reg32 *) but1_isr_neg__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the but1_isr_neg interrupt. */
#define but1_isr_neg_INTC_CLR_PD            ((reg32 *) but1_isr_neg__INTC_CLR_PD_REG)


#endif /* CY_ISR_but1_isr_neg_H */


/* [] END OF FILE */
