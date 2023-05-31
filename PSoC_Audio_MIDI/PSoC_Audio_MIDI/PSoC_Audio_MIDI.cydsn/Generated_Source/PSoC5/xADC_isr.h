/*******************************************************************************
* File Name: xADC_isr.h
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
#if !defined(CY_ISR_xADC_isr_H)
#define CY_ISR_xADC_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void xADC_isr_Start(void);
void xADC_isr_StartEx(cyisraddress address);
void xADC_isr_Stop(void);

CY_ISR_PROTO(xADC_isr_Interrupt);

void xADC_isr_SetVector(cyisraddress address);
cyisraddress xADC_isr_GetVector(void);

void xADC_isr_SetPriority(uint8 priority);
uint8 xADC_isr_GetPriority(void);

void xADC_isr_Enable(void);
uint8 xADC_isr_GetState(void);
void xADC_isr_Disable(void);

void xADC_isr_SetPending(void);
void xADC_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the xADC_isr ISR. */
#define xADC_isr_INTC_VECTOR            ((reg32 *) xADC_isr__INTC_VECT)

/* Address of the xADC_isr ISR priority. */
#define xADC_isr_INTC_PRIOR             ((reg8 *) xADC_isr__INTC_PRIOR_REG)

/* Priority of the xADC_isr interrupt. */
#define xADC_isr_INTC_PRIOR_NUMBER      xADC_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable xADC_isr interrupt. */
#define xADC_isr_INTC_SET_EN            ((reg32 *) xADC_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the xADC_isr interrupt. */
#define xADC_isr_INTC_CLR_EN            ((reg32 *) xADC_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the xADC_isr interrupt state to pending. */
#define xADC_isr_INTC_SET_PD            ((reg32 *) xADC_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the xADC_isr interrupt. */
#define xADC_isr_INTC_CLR_PD            ((reg32 *) xADC_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_xADC_isr_H */


/* [] END OF FILE */
