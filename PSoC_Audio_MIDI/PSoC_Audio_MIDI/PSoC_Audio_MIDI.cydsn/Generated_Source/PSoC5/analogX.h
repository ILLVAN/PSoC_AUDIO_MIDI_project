/*******************************************************************************
* File Name: analogX.h  
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

#if !defined(CY_PINS_analogX_H) /* Pins analogX_H */
#define CY_PINS_analogX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "analogX_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 analogX__PORT == 15 && ((analogX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    analogX_Write(uint8 value);
void    analogX_SetDriveMode(uint8 mode);
uint8   analogX_ReadDataReg(void);
uint8   analogX_Read(void);
void    analogX_SetInterruptMode(uint16 position, uint16 mode);
uint8   analogX_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the analogX_SetDriveMode() function.
     *  @{
     */
        #define analogX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define analogX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define analogX_DM_RES_UP          PIN_DM_RES_UP
        #define analogX_DM_RES_DWN         PIN_DM_RES_DWN
        #define analogX_DM_OD_LO           PIN_DM_OD_LO
        #define analogX_DM_OD_HI           PIN_DM_OD_HI
        #define analogX_DM_STRONG          PIN_DM_STRONG
        #define analogX_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define analogX_MASK               analogX__MASK
#define analogX_SHIFT              analogX__SHIFT
#define analogX_WIDTH              1u

/* Interrupt constants */
#if defined(analogX__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in analogX_SetInterruptMode() function.
     *  @{
     */
        #define analogX_INTR_NONE      (uint16)(0x0000u)
        #define analogX_INTR_RISING    (uint16)(0x0001u)
        #define analogX_INTR_FALLING   (uint16)(0x0002u)
        #define analogX_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define analogX_INTR_MASK      (0x01u) 
#endif /* (analogX__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define analogX_PS                     (* (reg8 *) analogX__PS)
/* Data Register */
#define analogX_DR                     (* (reg8 *) analogX__DR)
/* Port Number */
#define analogX_PRT_NUM                (* (reg8 *) analogX__PRT) 
/* Connect to Analog Globals */                                                  
#define analogX_AG                     (* (reg8 *) analogX__AG)                       
/* Analog MUX bux enable */
#define analogX_AMUX                   (* (reg8 *) analogX__AMUX) 
/* Bidirectional Enable */                                                        
#define analogX_BIE                    (* (reg8 *) analogX__BIE)
/* Bit-mask for Aliased Register Access */
#define analogX_BIT_MASK               (* (reg8 *) analogX__BIT_MASK)
/* Bypass Enable */
#define analogX_BYP                    (* (reg8 *) analogX__BYP)
/* Port wide control signals */                                                   
#define analogX_CTL                    (* (reg8 *) analogX__CTL)
/* Drive Modes */
#define analogX_DM0                    (* (reg8 *) analogX__DM0) 
#define analogX_DM1                    (* (reg8 *) analogX__DM1)
#define analogX_DM2                    (* (reg8 *) analogX__DM2) 
/* Input Buffer Disable Override */
#define analogX_INP_DIS                (* (reg8 *) analogX__INP_DIS)
/* LCD Common or Segment Drive */
#define analogX_LCD_COM_SEG            (* (reg8 *) analogX__LCD_COM_SEG)
/* Enable Segment LCD */
#define analogX_LCD_EN                 (* (reg8 *) analogX__LCD_EN)
/* Slew Rate Control */
#define analogX_SLW                    (* (reg8 *) analogX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define analogX_PRTDSI__CAPS_SEL       (* (reg8 *) analogX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define analogX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) analogX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define analogX_PRTDSI__OE_SEL0        (* (reg8 *) analogX__PRTDSI__OE_SEL0) 
#define analogX_PRTDSI__OE_SEL1        (* (reg8 *) analogX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define analogX_PRTDSI__OUT_SEL0       (* (reg8 *) analogX__PRTDSI__OUT_SEL0) 
#define analogX_PRTDSI__OUT_SEL1       (* (reg8 *) analogX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define analogX_PRTDSI__SYNC_OUT       (* (reg8 *) analogX__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(analogX__SIO_CFG)
    #define analogX_SIO_HYST_EN        (* (reg8 *) analogX__SIO_HYST_EN)
    #define analogX_SIO_REG_HIFREQ     (* (reg8 *) analogX__SIO_REG_HIFREQ)
    #define analogX_SIO_CFG            (* (reg8 *) analogX__SIO_CFG)
    #define analogX_SIO_DIFF           (* (reg8 *) analogX__SIO_DIFF)
#endif /* (analogX__SIO_CFG) */

/* Interrupt Registers */
#if defined(analogX__INTSTAT)
    #define analogX_INTSTAT            (* (reg8 *) analogX__INTSTAT)
    #define analogX_SNAP               (* (reg8 *) analogX__SNAP)
    
	#define analogX_0_INTTYPE_REG 		(* (reg8 *) analogX__0__INTTYPE)
#endif /* (analogX__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_analogX_H */


/* [] END OF FILE */
