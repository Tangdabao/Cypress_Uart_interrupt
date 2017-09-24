/*******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:
*  This is the source code for the Interrupts example project of the Interrupt
*  and cy_boot components.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

#define HIGHE_H_PRIORITY                    (0u)
#define NESTED_ISR                          (1u)
#define HIGHER_PRIORITY                     (2u)
#define Uartset_ISR                         (3u)
#define DEFAULT_PRIORITY                    (4u)


#if(CY_PSOC4)
    #define LIGHT_OFF                       (1u)
    #define LIGHT_ON                        (0u)
#else
    #define LIGHT_OFF                       (0u)
    #define LIGHT_ON                        (1u)
#endif /* (CY_PSOC4) */

/* Interrupt prototypes */
CY_ISR_PROTO(GPIOIsrHandler);
CY_ISR_PROTO(NestedIsrHandler);
CY_ISR_PROTO(UART_1_SCB_IRQ_Interrupt);

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  At the beginning of the main function, the GPIO interrupt is set up and
*  enabled. After that, initial priority for the GPIO interrupt is changed from
*  1 to 3 (DEFAULT_PRIORITY). The custom interrupt (nested) is configured
*  (sets up, sets priority) and enabled. In GPIOIsrHandler, the isr_GPIO
*  pending interrupt clears, the green LED turns on, the nested software
*  interrupt causes after approximately 1 second delay, green LED turns off.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    uint32 ch=0;
    ///UART////
    UART_1_Start();
    UART_1_SCB_IRQ_Start();
    UART_1_UartPutString("Test");
    
    /* Set initial state (off) for LED */
    LED_Isr_Write(LIGHT_OFF);
    LED_Nested_Write(LIGHT_OFF);

    /* Sets up the GPIO interrupt and enables it */
    ISRGPIO_StartEx(GPIOIsrHandler);

    /* Changes initial priority for the GPIO interrupt */
    ISRGPIO_SetPriority(DEFAULT_PRIORITY);

    /* Sets up the nested interrupt, sets priority and enables it */
    CyIntSetVector(NESTED_ISR,NestedIsrHandler);
    CyIntSetPriority(NESTED_ISR,HIGHER_PRIORITY);
    CyIntEnable(NESTED_ISR);

    //CyIntSetVector(Uartset_ISR,UART_1_SCB_IRQ_Interrupt);
    //CyIntSetPriority(Uartset_ISR,HIGHE_H_PRIORITY);
   // CyIntEnable(Uartset_ISR);

    
    
    
    /* Enable global interrupts */
    CyGlobalIntEnable;

    for(;;)
    {
       //  ch = UART_1_UartGetChar();
        //    if (0u != ch)
       // {
         //   UART_1_UartPutChar(ch);
       // } 
    }
}


/*******************************************************************************
* Function Name: GPIOIsrHandler
********************************************************************************
* Summary:
*  The interrupt handler for GPIO interrupts.
*  Clears a pending Interrupt.
*  Clears a pin Interrupt.
*  Blinks the LED with the LED_Isr pin.
*  Calls nested interrupt.

*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(GPIOIsrHandler)
{
    /* Clear pending Interrupt */
    ISRGPIO_ClearPending();
    
    /* Clear pin Interrupt */
    Pin_Sw_ClearInterrupt();
    
    /* Turn On the LED */
    LED_Isr_Write(LIGHT_ON);

    /* Cause nested software interrupt after 1000 ms */
    CyDelay(1000u);
    CyIntSetPending(NESTED_ISR);

    /* Turn Off the LED */
    LED_Isr_Write(LIGHT_OFF);
}


/*******************************************************************************
* Function Name: NestedIsrHandler
********************************************************************************
* Summary:
*  The interrupt handler for nested interrupt.
*  Blinks the LED with the LED_Nested pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(NestedIsrHandler)
{
    /* Clear pending Interrupt */
    CyIntClearPending(NESTED_ISR);

    /* Turn On the LED for 1000 ms */
    LED_Nested_Write(LIGHT_ON);
    CyDelay(1000u);

    /* Turn Off the LED and wait for 1000 ms */
    LED_Nested_Write(LIGHT_OFF);
    CyDelay(1000u);
}


/*******************************************************************************
* Function Name: NestedIsrHandler
********************************************************************************
* Summary:
*  The interrupt handler for nested interrupt.
*  Blinks the LED with the LED_Nested pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(UART_1_SCB_IRQ_Interrupt)
{
   #ifdef UART_1_SCB_IRQ_INTERRUPT_INTERRUPT_CALLBACK
        UART_1_SCB_IRQ_Interrupt_InterruptCallback();
    #endif /* UART_1_SCB_IRQ_INTERRUPT_INTERRUPT_CALLBACK */  
    
    UART_1_ClearRxInterruptSource(UART_1_INTR_RX_NOT_EMPTY);

    if(UART_1_GetRxInterruptSourceMasked()&UART_1_INTR_RX_NOT_EMPTY)
    {
        uint32 ReceviceData=0;
        ReceviceData=UART_1_SpiUartReadRxData();
        UART_1_UartPutChar((uint8_t)ReceviceData);
    }
    UART_1_SpiUartClearRxBuffer();
}





