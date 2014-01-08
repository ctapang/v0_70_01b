/*******************************************************************************
 System Interrupt Source File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

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

#include <xc.h>
#include <sys/attribs.h>
#include "app.h"

void __ISR ( _USB_1_VECTOR,ipl4 ) _InterruptHandler_USB ( void )
{
    DRV_USB_Tasks_ISR((SYS_MODULE_OBJ)0);
}

void __ISR(_UART_2_VECTOR, ipl3) _InterruptHandler_UART2(void)
{
    uint8_t * data;

    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_TRANSMIT)
            && SYS_INT_SourceIsEnabled(INT_SOURCE_USART_2_TRANSMIT))
    {
        appData.uartTxCount ++;
        if(appData.uartTxCount >= appData.uartTransmitDataLength)
        {
            /* This means we dont have any more data to send */
            SYS_INT_SourceDisable(INT_SOURCE_USART_2_TRANSMIT);
            appData.isUARTTransmitBusy = false;
        }
        else
        {
            data = (uint8_t*)(appData.uartTransmitData);
            U2TXREG = data[appData.uartTxCount];
          
        }
    }

    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_2_RECEIVE))
    {
        /* This means we have received a character */
        appData.uartReceivedData = U2RXREG;
        appData.isUARTReceivedData = true;
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_2_RECEIVE);
    }
}
/*******************************************************************************
 End of File
 */

