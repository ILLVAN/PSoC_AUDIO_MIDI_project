/*******************************************************************************
* File Name: analogBut_isr.h
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
#if !defined(CY_ISR_analogBut_isr_H)
#define CY_ISR_analogBut_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void analogBut_isr_Start(void);
void analogBut_isr_StartEx(cyisraddress address);
void analogBut_isr_Stop(void);

CY_ISR_PROTO(analogBut_isr_Interrupt);

void analogBut_isr_SetVector(cyisraddress address);
cyisraddress analogBut_isr_GetVector(void);

void analogBut_isr_SetPriority(uint8 priority);
uint8 analogBut_isr_GetPriority(void);

void analogBut_isr_Enable(void);
uint8 analogBut_isr_GetState(void);
void analogBut_isr_Disable(void);

void analogBut_isr_SetPending(void);
void analogBut_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the analogBut_isr ISR. */
#define analogBut_isr_INTC_VECTOR            ((reg32 *) analogBut_isr__INTC_VECT)

/* Address of the analogBut_isr ISR priority. */
#define analogBut_isr_INTC_PRIOR             ((reg8 *) analogBut_isr__INTC_PRIOR_REG)

/* Priority of the analogBut_isr interrupt. */
#define analogBut_isr_INTC_PRIOR_NUMBER      analogBut_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable analogBut_isr interrupt. */
#define analogBut_isr_INTC_SET_EN            ((reg32 *) analogBut_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the analogBut_isr interrupt. */
#define analogBut_isr_INTC_CLR_EN            ((reg32 *) analogBut_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the analogBut_isr interrupt state to pending. */
#define analogBut_isr_INTC_SET_PD            ((reg32 *) analogBut_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the analogBut_isr interrupt. */
#define analogBut_isr_INTC_CLR_PD            ((reg32 *) analogBut_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_analogBut_isr_H */


/* [] END OF FILE */
