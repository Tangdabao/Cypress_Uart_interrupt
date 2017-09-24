/*******************************************************************************
* File Name: ISRGPIO.h
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
#if !defined(CY_ISR_ISRGPIO_H)
#define CY_ISR_ISRGPIO_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISRGPIO_Start(void);
void ISRGPIO_StartEx(cyisraddress address);
void ISRGPIO_Stop(void);

CY_ISR_PROTO(ISRGPIO_Interrupt);

void ISRGPIO_SetVector(cyisraddress address);
cyisraddress ISRGPIO_GetVector(void);

void ISRGPIO_SetPriority(uint8 priority);
uint8 ISRGPIO_GetPriority(void);

void ISRGPIO_Enable(void);
uint8 ISRGPIO_GetState(void);
void ISRGPIO_Disable(void);

void ISRGPIO_SetPending(void);
void ISRGPIO_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISRGPIO ISR. */
#define ISRGPIO_INTC_VECTOR            ((reg32 *) ISRGPIO__INTC_VECT)

/* Address of the ISRGPIO ISR priority. */
#define ISRGPIO_INTC_PRIOR             ((reg32 *) ISRGPIO__INTC_PRIOR_REG)

/* Priority of the ISRGPIO interrupt. */
#define ISRGPIO_INTC_PRIOR_NUMBER      ISRGPIO__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISRGPIO interrupt. */
#define ISRGPIO_INTC_SET_EN            ((reg32 *) ISRGPIO__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISRGPIO interrupt. */
#define ISRGPIO_INTC_CLR_EN            ((reg32 *) ISRGPIO__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISRGPIO interrupt state to pending. */
#define ISRGPIO_INTC_SET_PD            ((reg32 *) ISRGPIO__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISRGPIO interrupt. */
#define ISRGPIO_INTC_CLR_PD            ((reg32 *) ISRGPIO__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISRGPIO_H */


/* [] END OF FILE */
