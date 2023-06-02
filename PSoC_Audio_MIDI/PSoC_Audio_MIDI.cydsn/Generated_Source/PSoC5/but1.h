/*******************************************************************************
* File Name: but1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_but1_H) /* Pins but1_H */
#define CY_PINS_but1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "but1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 but1__PORT == 15 && ((but1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    but1_Write(uint8 value);
void    but1_SetDriveMode(uint8 mode);
uint8   but1_ReadDataReg(void);
uint8   but1_Read(void);
void    but1_SetInterruptMode(uint16 position, uint16 mode);
uint8   but1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the but1_SetDriveMode() function.
     *  @{
     */
        #define but1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define but1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define but1_DM_RES_UP          PIN_DM_RES_UP
        #define but1_DM_RES_DWN         PIN_DM_RES_DWN
        #define but1_DM_OD_LO           PIN_DM_OD_LO
        #define but1_DM_OD_HI           PIN_DM_OD_HI
        #define but1_DM_STRONG          PIN_DM_STRONG
        #define but1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define but1_MASK               but1__MASK
#define but1_SHIFT              but1__SHIFT
#define but1_WIDTH              1u

/* Interrupt constants */
#if defined(but1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in but1_SetInterruptMode() function.
     *  @{
     */
        #define but1_INTR_NONE      (uint16)(0x0000u)
        #define but1_INTR_RISING    (uint16)(0x0001u)
        #define but1_INTR_FALLING   (uint16)(0x0002u)
        #define but1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define but1_INTR_MASK      (0x01u) 
#endif /* (but1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define but1_PS                     (* (reg8 *) but1__PS)
/* Data Register */
#define but1_DR                     (* (reg8 *) but1__DR)
/* Port Number */
#define but1_PRT_NUM                (* (reg8 *) but1__PRT) 
/* Connect to Analog Globals */                                                  
#define but1_AG                     (* (reg8 *) but1__AG)                       
/* Analog MUX bux enable */
#define but1_AMUX                   (* (reg8 *) but1__AMUX) 
/* Bidirectional Enable */                                                        
#define but1_BIE                    (* (reg8 *) but1__BIE)
/* Bit-mask for Aliased Register Access */
#define but1_BIT_MASK               (* (reg8 *) but1__BIT_MASK)
/* Bypass Enable */
#define but1_BYP                    (* (reg8 *) but1__BYP)
/* Port wide control signals */                                                   
#define but1_CTL                    (* (reg8 *) but1__CTL)
/* Drive Modes */
#define but1_DM0                    (* (reg8 *) but1__DM0) 
#define but1_DM1                    (* (reg8 *) but1__DM1)
#define but1_DM2                    (* (reg8 *) but1__DM2) 
/* Input Buffer Disable Override */
#define but1_INP_DIS                (* (reg8 *) but1__INP_DIS)
/* LCD Common or Segment Drive */
#define but1_LCD_COM_SEG            (* (reg8 *) but1__LCD_COM_SEG)
/* Enable Segment LCD */
#define but1_LCD_EN                 (* (reg8 *) but1__LCD_EN)
/* Slew Rate Control */
#define but1_SLW                    (* (reg8 *) but1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define but1_PRTDSI__CAPS_SEL       (* (reg8 *) but1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define but1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) but1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define but1_PRTDSI__OE_SEL0        (* (reg8 *) but1__PRTDSI__OE_SEL0) 
#define but1_PRTDSI__OE_SEL1        (* (reg8 *) but1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define but1_PRTDSI__OUT_SEL0       (* (reg8 *) but1__PRTDSI__OUT_SEL0) 
#define but1_PRTDSI__OUT_SEL1       (* (reg8 *) but1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define but1_PRTDSI__SYNC_OUT       (* (reg8 *) but1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(but1__SIO_CFG)
    #define but1_SIO_HYST_EN        (* (reg8 *) but1__SIO_HYST_EN)
    #define but1_SIO_REG_HIFREQ     (* (reg8 *) but1__SIO_REG_HIFREQ)
    #define but1_SIO_CFG            (* (reg8 *) but1__SIO_CFG)
    #define but1_SIO_DIFF           (* (reg8 *) but1__SIO_DIFF)
#endif /* (but1__SIO_CFG) */

/* Interrupt Registers */
#if defined(but1__INTSTAT)
    #define but1_INTSTAT            (* (reg8 *) but1__INTSTAT)
    #define but1_SNAP               (* (reg8 *) but1__SNAP)
    
	#define but1_0_INTTYPE_REG 		(* (reg8 *) but1__0__INTTYPE)
#endif /* (but1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_but1_H */


/* [] END OF FILE */
