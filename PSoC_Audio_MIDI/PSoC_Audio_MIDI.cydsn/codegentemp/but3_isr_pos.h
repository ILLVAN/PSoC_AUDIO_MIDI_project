/*******************************************************************************
* File Name: but3_isr_pos.h
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
#if !defined(CY_ISR_but3_isr_pos_H)
#define CY_ISR_but3_isr_pos_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void but3_isr_pos_Start(void);
void but3_isr_pos_StartEx(cyisraddress address);
void but3_isr_pos_Stop(void);

CY_ISR_PROTO(but3_isr_pos_Interrupt);

void but3_isr_pos_SetVector(cyisraddress address);
cyisraddress but3_isr_pos_GetVector(void);

void but3_isr_pos_SetPriority(uint8 priority);
uint8 but3_isr_pos_GetPriority(void);

void but3_isr_pos_Enable(void);
uint8 but3_isr_pos_GetState(void);
void but3_isr_pos_Disable(void);

void but3_isr_pos_SetPending(void);
void but3_isr_pos_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the but3_isr_pos ISR. */
#define but3_isr_pos_INTC_VECTOR            ((reg32 *) but3_isr_pos__INTC_VECT)

/* Address of the but3_isr_pos ISR priority. */
#define but3_isr_pos_INTC_PRIOR             ((reg8 *) but3_isr_pos__INTC_PRIOR_REG)

/* Priority of the but3_isr_pos interrupt. */
#define but3_isr_pos_INTC_PRIOR_NUMBER      but3_isr_pos__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable but3_isr_pos interrupt. */
#define but3_isr_pos_INTC_SET_EN            ((reg32 *) but3_isr_pos__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the but3_isr_pos interrupt. */
#define but3_isr_pos_INTC_CLR_EN            ((reg32 *) but3_isr_pos__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the but3_isr_pos interrupt state to pending. */
#define but3_isr_pos_INTC_SET_PD            ((reg32 *) but3_isr_pos__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the but3_isr_pos interrupt. */
#define but3_isr_pos_INTC_CLR_PD            ((reg32 *) but3_isr_pos__INTC_CLR_PD_REG)


#endif /* CY_ISR_but3_isr_pos_H */


/* [] END OF FILE */
