/*******************************************************************************
* File Name: analogBut.h  
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

#if !defined(CY_PINS_analogBut_H) /* Pins analogBut_H */
#define CY_PINS_analogBut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "analogBut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 analogBut__PORT == 15 && ((analogBut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    analogBut_Write(uint8 value);
void    analogBut_SetDriveMode(uint8 mode);
uint8   analogBut_ReadDataReg(void);
uint8   analogBut_Read(void);
void    analogBut_SetInterruptMode(uint16 position, uint16 mode);
uint8   analogBut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the analogBut_SetDriveMode() function.
     *  @{
     */
        #define analogBut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define analogBut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define analogBut_DM_RES_UP          PIN_DM_RES_UP
        #define analogBut_DM_RES_DWN         PIN_DM_RES_DWN
        #define analogBut_DM_OD_LO           PIN_DM_OD_LO
        #define analogBut_DM_OD_HI           PIN_DM_OD_HI
        #define analogBut_DM_STRONG          PIN_DM_STRONG
        #define analogBut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define analogBut_MASK               analogBut__MASK
#define analogBut_SHIFT              analogBut__SHIFT
#define analogBut_WIDTH              1u

/* Interrupt constants */
#if defined(analogBut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in analogBut_SetInterruptMode() function.
     *  @{
     */
        #define analogBut_INTR_NONE      (uint16)(0x0000u)
        #define analogBut_INTR_RISING    (uint16)(0x0001u)
        #define analogBut_INTR_FALLING   (uint16)(0x0002u)
        #define analogBut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define analogBut_INTR_MASK      (0x01u) 
#endif /* (analogBut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define analogBut_PS                     (* (reg8 *) analogBut__PS)
/* Data Register */
#define analogBut_DR                     (* (reg8 *) analogBut__DR)
/* Port Number */
#define analogBut_PRT_NUM                (* (reg8 *) analogBut__PRT) 
/* Connect to Analog Globals */                                                  
#define analogBut_AG                     (* (reg8 *) analogBut__AG)                       
/* Analog MUX bux enable */
#define analogBut_AMUX                   (* (reg8 *) analogBut__AMUX) 
/* Bidirectional Enable */                                                        
#define analogBut_BIE                    (* (reg8 *) analogBut__BIE)
/* Bit-mask for Aliased Register Access */
#define analogBut_BIT_MASK               (* (reg8 *) analogBut__BIT_MASK)
/* Bypass Enable */
#define analogBut_BYP                    (* (reg8 *) analogBut__BYP)
/* Port wide control signals */                                                   
#define analogBut_CTL                    (* (reg8 *) analogBut__CTL)
/* Drive Modes */
#define analogBut_DM0                    (* (reg8 *) analogBut__DM0) 
#define analogBut_DM1                    (* (reg8 *) analogBut__DM1)
#define analogBut_DM2                    (* (reg8 *) analogBut__DM2) 
/* Input Buffer Disable Override */
#define analogBut_INP_DIS                (* (reg8 *) analogBut__INP_DIS)
/* LCD Common or Segment Drive */
#define analogBut_LCD_COM_SEG            (* (reg8 *) analogBut__LCD_COM_SEG)
/* Enable Segment LCD */
#define analogBut_LCD_EN                 (* (reg8 *) analogBut__LCD_EN)
/* Slew Rate Control */
#define analogBut_SLW                    (* (reg8 *) analogBut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define analogBut_PRTDSI__CAPS_SEL       (* (reg8 *) analogBut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define analogBut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) analogBut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define analogBut_PRTDSI__OE_SEL0        (* (reg8 *) analogBut__PRTDSI__OE_SEL0) 
#define analogBut_PRTDSI__OE_SEL1        (* (reg8 *) analogBut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define analogBut_PRTDSI__OUT_SEL0       (* (reg8 *) analogBut__PRTDSI__OUT_SEL0) 
#define analogBut_PRTDSI__OUT_SEL1       (* (reg8 *) analogBut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define analogBut_PRTDSI__SYNC_OUT       (* (reg8 *) analogBut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(analogBut__SIO_CFG)
    #define analogBut_SIO_HYST_EN        (* (reg8 *) analogBut__SIO_HYST_EN)
    #define analogBut_SIO_REG_HIFREQ     (* (reg8 *) analogBut__SIO_REG_HIFREQ)
    #define analogBut_SIO_CFG            (* (reg8 *) analogBut__SIO_CFG)
    #define analogBut_SIO_DIFF           (* (reg8 *) analogBut__SIO_DIFF)
#endif /* (analogBut__SIO_CFG) */

/* Interrupt Registers */
#if defined(analogBut__INTSTAT)
    #define analogBut_INTSTAT            (* (reg8 *) analogBut__INTSTAT)
    #define analogBut_SNAP               (* (reg8 *) analogBut__SNAP)
    
	#define analogBut_0_INTTYPE_REG 		(* (reg8 *) analogBut__0__INTTYPE)
#endif /* (analogBut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_analogBut_H */


/* [] END OF FILE */
