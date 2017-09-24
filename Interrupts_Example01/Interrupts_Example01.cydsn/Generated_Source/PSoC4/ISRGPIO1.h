/*******************************************************************************
* File Name: ISRGPIO1.h
* Version 1.70
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
#if !defined(CY_ISR_ISRGPIO1_H)
#define CY_ISR_ISRGPIO1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISRGPIO1_Start(void);
void ISRGPIO1_StartEx(cyisraddress address);
void ISRGPIO1_Stop(void);

CY_ISR_PROTO(ISRGPIO1_Interrupt);

void ISRGPIO1_SetVector(cyisraddress address);
cyisraddress ISRGPIO1_GetVector(void);

void ISRGPIO1_SetPriority(uint8 priority);
uint8 ISRGPIO1_GetPriority(void);

void ISRGPIO1_Enable(void);
uint8 ISRGPIO1_GetState(void);
void ISRGPIO1_Disable(void);

void ISRGPIO1_SetPending(void);
void ISRGPIO1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISRGPIO1 ISR. */
#define ISRGPIO1_INTC_VECTOR            ((reg32 *) ISRGPIO1__INTC_VECT)

/* Address of the ISRGPIO1 ISR priority. */
#define ISRGPIO1_INTC_PRIOR             ((reg32 *) ISRGPIO1__INTC_PRIOR_REG)

/* Priority of the ISRGPIO1 interrupt. */
#define ISRGPIO1_INTC_PRIOR_NUMBER      ISRGPIO1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISRGPIO1 interrupt. */
#define ISRGPIO1_INTC_SET_EN            ((reg32 *) ISRGPIO1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISRGPIO1 interrupt. */
#define ISRGPIO1_INTC_CLR_EN            ((reg32 *) ISRGPIO1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISRGPIO1 interrupt state to pending. */
#define ISRGPIO1_INTC_SET_PD            ((reg32 *) ISRGPIO1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISRGPIO1 interrupt. */
#define ISRGPIO1_INTC_CLR_PD            ((reg32 *) ISRGPIO1__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISRGPIO1_H */


/* [] END OF FILE */
