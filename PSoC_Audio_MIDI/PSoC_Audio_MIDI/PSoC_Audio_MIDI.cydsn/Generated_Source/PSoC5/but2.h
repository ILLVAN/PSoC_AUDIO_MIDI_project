/*******************************************************************************
* File Name: but2.h  
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

#if !defined(CY_PINS_but2_H) /* Pins but2_H */
#define CY_PINS_but2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "but2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 but2__PORT == 15 && ((but2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    but2_Write(uint8 value);
void    but2_SetDriveMode(uint8 mode);
uint8   but2_ReadDataReg(void);
uint8   but2_Read(void);
void    but2_SetInterruptMode(uint16 position, uint16 mode);
uint8   but2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the but2_SetDriveMode() function.
     *  @{
     */
        #define but2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define but2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define but2_DM_RES_UP          PIN_DM_RES_UP
        #define but2_DM_RES_DWN         PIN_DM_RES_DWN
        #define but2_DM_OD_LO           PIN_DM_OD_LO
        #define but2_DM_OD_HI           PIN_DM_OD_HI
        #define but2_DM_STRONG          PIN_DM_STRONG
        #define but2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define but2_MASK               but2__MASK
#define but2_SHIFT              but2__SHIFT
#define but2_WIDTH              1u

/* Interrupt constants */
#if defined(but2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in but2_SetInterruptMode() function.
     *  @{
     */
        #define but2_INTR_NONE      (uint16)(0x0000u)
        #define but2_INTR_RISING    (uint16)(0x0001u)
        #define but2_INTR_FALLING   (uint16)(0x0002u)
        #define but2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define but2_INTR_MASK      (0x01u) 
#endif /* (but2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define but2_PS                     (* (reg8 *) but2__PS)
/* Data Register */
#define but2_DR                     (* (reg8 *) but2__DR)
/* Port Number */
#define but2_PRT_NUM                (* (reg8 *) but2__PRT) 
/* Connect to Analog Globals */                                                  
#define but2_AG                     (* (reg8 *) but2__AG)                       
/* Analog MUX bux enable */
#define but2_AMUX                   (* (reg8 *) but2__AMUX) 
/* Bidirectional Enable */                                                        
#define but2_BIE                    (* (reg8 *) but2__BIE)
/* Bit-mask for Aliased Register Access */
#define but2_BIT_MASK               (* (reg8 *) but2__BIT_MASK)
/* Bypass Enable */
#define but2_BYP                    (* (reg8 *) but2__BYP)
/* Port wide control signals */                                                   
#define but2_CTL                    (* (reg8 *) but2__CTL)
/* Drive Modes */
#define but2_DM0                    (* (reg8 *) but2__DM0) 
#define but2_DM1                    (* (reg8 *) but2__DM1)
#define but2_DM2                    (* (reg8 *) but2__DM2) 
/* Input Buffer Disable Override */
#define but2_INP_DIS                (* (reg8 *) but2__INP_DIS)
/* LCD Common or Segment Drive */
#define but2_LCD_COM_SEG            (* (reg8 *) but2__LCD_COM_SEG)
/* Enable Segment LCD */
#define but2_LCD_EN                 (* (reg8 *) but2__LCD_EN)
/* Slew Rate Control */
#define but2_SLW                    (* (reg8 *) but2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define but2_PRTDSI__CAPS_SEL       (* (reg8 *) but2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define but2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) but2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define but2_PRTDSI__OE_SEL0        (* (reg8 *) but2__PRTDSI__OE_SEL0) 
#define but2_PRTDSI__OE_SEL1        (* (reg8 *) but2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define but2_PRTDSI__OUT_SEL0       (* (reg8 *) but2__PRTDSI__OUT_SEL0) 
#define but2_PRTDSI__OUT_SEL1       (* (reg8 *) but2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define but2_PRTDSI__SYNC_OUT       (* (reg8 *) but2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(but2__SIO_CFG)
    #define but2_SIO_HYST_EN        (* (reg8 *) but2__SIO_HYST_EN)
    #define but2_SIO_REG_HIFREQ     (* (reg8 *) but2__SIO_REG_HIFREQ)
    #define but2_SIO_CFG            (* (reg8 *) but2__SIO_CFG)
    #define but2_SIO_DIFF           (* (reg8 *) but2__SIO_DIFF)
#endif /* (but2__SIO_CFG) */

/* Interrupt Registers */
#if defined(but2__INTSTAT)
    #define but2_INTSTAT            (* (reg8 *) but2__INTSTAT)
    #define but2_SNAP               (* (reg8 *) but2__SNAP)
    
	#define but2_0_INTTYPE_REG 		(* (reg8 *) but2__0__INTTYPE)
#endif /* (but2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_but2_H */


/* [] END OF FILE */
