/*******************************************************************************
 System Interrupt Source File

  File Name:
    sys_int.c

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

void __ISR ( _USB_1_VECTOR ) _InterruptHandler_USB_stub ( void )
{
    DRV_USB_Tasks_ISR((SYS_MODULE_OBJ)0);
}

void __ISR ( _CHANGE_NOTICE_VECTOR ) _InterruptHandler_CN_stub ( void )
{

    uint32_t portD;

    volatile static uint8_t count;

    if(!PORTDbits.RD6)
    {
        pushButton = 0x31;
    }

    else if(!PORTDbits.RD7)
    {
        pushButton = 0x32;
    }
    else if(!PORTDbits.RD13)
    {
        pushButton = 0x33;
    }
    
    portD = PORTD;
    
    count++;

    if(count == 2)
    {
        /* check if the app is waiting for the button press */
        if ( appData.state == APP_WAIT_FOR_BUTTON_PRESS )
        {

            /* update the state to button pressed */
            appData.state = APP_BUTTON_PRESSED;
        }

        count = 0;
    }    

    IFS1bits.CNIF = 0;
}

/*******************************************************************************
 End of File
 */

