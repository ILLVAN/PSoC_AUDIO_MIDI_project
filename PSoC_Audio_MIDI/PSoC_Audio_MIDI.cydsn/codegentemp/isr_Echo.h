/*******************************************************************************
* File Name: isr_Echo.h
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
#if !defined(CY_ISR_isr_Echo_H)
#define CY_ISR_isr_Echo_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Echo_Start(void);
void isr_Echo_StartEx(cyisraddress address);
void isr_Echo_Stop(void);

CY_ISR_PROTO(isr_Echo_Interrupt);

void isr_Echo_SetVector(cyisraddress address);
cyisraddress isr_Echo_GetVector(void);

void isr_Echo_SetPriority(uint8 priority);
uint8 isr_Echo_GetPriority(void);

void isr_Echo_Enable(void);
uint8 isr_Echo_GetState(void);
void isr_Echo_Disable(void);

void isr_Echo_SetPending(void);
void isr_Echo_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Echo ISR. */
#define isr_Echo_INTC_VECTOR            ((reg32 *) isr_Echo__INTC_VECT)

/* Address of the isr_Echo ISR priority. */
#define isr_Echo_INTC_PRIOR             ((reg8 *) isr_Echo__INTC_PRIOR_REG)

/* Priority of the isr_Echo interrupt. */
#define isr_Echo_INTC_PRIOR_NUMBER      isr_Echo__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Echo interrupt. */
#define isr_Echo_INTC_SET_EN            ((reg32 *) isr_Echo__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Echo interrupt. */
#define isr_Echo_INTC_CLR_EN            ((reg32 *) isr_Echo__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Echo interrupt state to pending. */
#define isr_Echo_INTC_SET_PD            ((reg32 *) isr_Echo__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Echo interrupt. */
#define isr_Echo_INTC_CLR_PD            ((reg32 *) isr_Echo__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Echo_H */


/* [] END OF FILE */
