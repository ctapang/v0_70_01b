/*******************************************************************************
 System Interrupt Source File

  File Name:
    sys_int.c

  Summary:
    Raw ISR definitions

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

#include "app.h"


/*******************************************************************************
  Function:
    void _InterruptHandler_TMR_1_stub(void)

  Summary:
    Raw ISR routine for the timer 1 interrupt

  Description:
    This is the raw Interrupt Service Routine (ISR) for the Timer 1 interrupt.
    This routine calls the timer driver's tasks routine to service the
    interrupt.

  Precondition:
    The timer driver must have been initialized for Timer 1.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must not be "called" as a C-language function is called.  It
    is "vectored" to by the processor when the interrupt occurs.
*/

void __ISR ( _TIMER_1_VECTOR ) _InterruptHandler_TMR_1_stub ( void )
{
    /* Call the timer driver's "Tasks" routine */
    DRV_TMR_Tasks ( appDrvObject.tmrObject );
}


/*******************************************************************************
  Function:
    void _InterruptHandler_USART_2_stub(void)

  Summary:
    Raw ISR routine for the USART 2 TX interrupt

  Description:
    This is the raw Interrupt Service Routine (ISR) for the USART 2 TX
    interrupt.  This routine calls the timer driver's tasks routine to service
    the interrupt.

  Precondition:
    The USART driver must have been initialized for USART 2.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must not be "called" as a C-language function is called.  It
    is "vectored" to by the processor when the interrupt occurs.
 */

void __ISR ( _UART_2_VECTOR ) _InterruptHandler_USART_2_stub ( void )
{
    if ( SYS_INT_SourceStatusGet ( APP_USART_INT_SOURCE_TX ) )
    {
        /* Call the USART driver's "Tasks" routine */
        DRV_USART_TasksTX ( appDrvObject.usartObject );
    }
}


/*******************************************************************************
  Function:
    void _InterruptHandler_ADC_stub(void)

  Summary:
    Raw ISR routine for the ADC 1 Interrupt

  Description:
    This is the raw Interrupt Service Routine (ISR) for the ADC 1 interrupt.
    This routine calls the timer driver's tasks routine to service the
    interrupt.

  Precondition:
    The ADC driver must have been initialized for ADC 1.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must not be "called" as a C-language function is called.  It
    is "vectored" to by the processor when the interrupt occurs.
*/

void __ISR ( _ADC_VECTOR ) _InterruptHandler_ADC_stub ( void )
{
    /* Call the ADC driver's "Tasks" routine */
    DRV_ADC_Tasks ( appDrvObject.adcObject );
}


/*******************************************************************************
 End of File
 */

