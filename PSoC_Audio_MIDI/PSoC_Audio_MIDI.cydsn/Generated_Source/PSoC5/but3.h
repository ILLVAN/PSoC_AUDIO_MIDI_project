/*******************************************************************************
* File Name: but3.h  
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

#if !defined(CY_PINS_but3_H) /* Pins but3_H */
#define CY_PINS_but3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "but3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 but3__PORT == 15 && ((but3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    but3_Write(uint8 value);
void    but3_SetDriveMode(uint8 mode);
uint8   but3_ReadDataReg(void);
uint8   but3_Read(void);
void    but3_SetInterruptMode(uint16 position, uint16 mode);
uint8   but3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the but3_SetDriveMode() function.
     *  @{
     */
        #define but3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define but3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define but3_DM_RES_UP          PIN_DM_RES_UP
        #define but3_DM_RES_DWN         PIN_DM_RES_DWN
        #define but3_DM_OD_LO           PIN_DM_OD_LO
        #define but3_DM_OD_HI           PIN_DM_OD_HI
        #define but3_DM_STRONG          PIN_DM_STRONG
        #define but3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define but3_MASK               but3__MASK
#define but3_SHIFT              but3__SHIFT
#define but3_WIDTH              1u

/* Interrupt constants */
#if defined(but3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in but3_SetInterruptMode() function.
     *  @{
     */
        #define but3_INTR_NONE      (uint16)(0x0000u)
        #define but3_INTR_RISING    (uint16)(0x0001u)
        #define but3_INTR_FALLING   (uint16)(0x0002u)
        #define but3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define but3_INTR_MASK      (0x01u) 
#endif /* (but3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define but3_PS                     (* (reg8 *) but3__PS)
/* Data Register */
#define but3_DR                     (* (reg8 *) but3__DR)
/* Port Number */
#define but3_PRT_NUM                (* (reg8 *) but3__PRT) 
/* Connect to Analog Globals */                                                  
#define but3_AG                     (* (reg8 *) but3__AG)                       
/* Analog MUX bux enable */
#define but3_AMUX                   (* (reg8 *) but3__AMUX) 
/* Bidirectional Enable */                                                        
#define but3_BIE                    (* (reg8 *) but3__BIE)
/* Bit-mask for Aliased Register Access */
#define but3_BIT_MASK               (* (reg8 *) but3__BIT_MASK)
/* Bypass Enable */
#define but3_BYP                    (* (reg8 *) but3__BYP)
/* Port wide control signals */                                                   
#define but3_CTL                    (* (reg8 *) but3__CTL)
/* Drive Modes */
#define but3_DM0                    (* (reg8 *) but3__DM0) 
#define but3_DM1                    (* (reg8 *) but3__DM1)
#define but3_DM2                    (* (reg8 *) but3__DM2) 
/* Input Buffer Disable Override */
#define but3_INP_DIS                (* (reg8 *) but3__INP_DIS)
/* LCD Common or Segment Drive */
#define but3_LCD_COM_SEG            (* (reg8 *) but3__LCD_COM_SEG)
/* Enable Segment LCD */
#define but3_LCD_EN                 (* (reg8 *) but3__LCD_EN)
/* Slew Rate Control */
#define but3_SLW                    (* (reg8 *) but3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define but3_PRTDSI__CAPS_SEL       (* (reg8 *) but3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define but3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) but3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define but3_PRTDSI__OE_SEL0        (* (reg8 *) but3__PRTDSI__OE_SEL0) 
#define but3_PRTDSI__OE_SEL1        (* (reg8 *) but3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define but3_PRTDSI__OUT_SEL0       (* (reg8 *) but3__PRTDSI__OUT_SEL0) 
#define but3_PRTDSI__OUT_SEL1       (* (reg8 *) but3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define but3_PRTDSI__SYNC_OUT       (* (reg8 *) but3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(but3__SIO_CFG)
    #define but3_SIO_HYST_EN        (* (reg8 *) but3__SIO_HYST_EN)
    #define but3_SIO_REG_HIFREQ     (* (reg8 *) but3__SIO_REG_HIFREQ)
    #define but3_SIO_CFG            (* (reg8 *) but3__SIO_CFG)
    #define but3_SIO_DIFF           (* (reg8 *) but3__SIO_DIFF)
#endif /* (but3__SIO_CFG) */

/* Interrupt Registers */
#if defined(but3__INTSTAT)
    #define but3_INTSTAT            (* (reg8 *) but3__INTSTAT)
    #define but3_SNAP               (* (reg8 *) but3__SNAP)
    
	#define but3_0_INTTYPE_REG 		(* (reg8 *) but3__0__INTTYPE)
#endif /* (but3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_but3_H */


/* [] END OF FILE */
