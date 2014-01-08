/*******************************************************************************
  USART Driver Feature Variant Implementations

  Summary:
    USART Driver Feature Variant Implementations

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature. The features are available
    on UARTS
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_async.c
Copyright © 2009-2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS�? WITHOUT WARRANTY OF ANY KIND,
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
//DOM-IGNORE-END
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "drv.h"
#include "usart/src/drv_usart_variant_mapping.h"


// *****************************************************************************
/*  void
    _DRV_USART_SetupLineControlModes ( USART_MODULE_ID index , lineControlMode, flowControl)

   Summary:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

   Description:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

   Remarks:
    None
 */

void _DRV_USART_SetupLineControlModes_V1(USART_MODULE_ID index,
                                            DRV_USART_LINE_CONTROL_MODES lineControlMode,
                                            DRV_USART_HANDSHAKE_MODES  handShakeMode)
{
    PLIB_USART_LINECONTROL_MODE     flowControl;

    if (handShakeMode == DRV_USART_HANDSHAKE_MODE_SIMPLEX)
    {
        flowControl = PLIB_USART_RTS_MODE_SIMPLEX;
    } else
    {
        flowControl = PLIB_USART_RTS_MODE_FLOWCONTROL;
    }

    /* Supporting 8NONE1 */
    //if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_8NONE1)
    {
            PLIB_USART_LineControlModeSelect (DRV_USART_MODULE_ID( index ), PLIB_USART_ONE_STOPBIT   |PLIB_USART_8_DATABITS_NO_PARITY |PLIB_USART_RTS_MODE_FLOWCONTROL );
    }
/*
    if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_9NONE1)
    {
            PLIB_USART_LineControlModeSelect (
                                   DRV_USART_MODULE_ID( index ), PLIB_USART_ONE_STOPBIT |
                                   PLIB_USART_9_DATABITS         |
                                   flowControl );
    }
    if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_8EVEN1)
    {
            PLIB_USART_LineControlModeSelect (
                                   DRV_USART_MODULE_ID( index ), PLIB_USART_ONE_STOPBIT     |
                                   PLIB_USART_8_DATABITS_EVEN_PARITY |
                                   flowControl );
    }
    if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_8EVEN2)
    {
            PLIB_USART_LineControlModeSelect (
                                   DRV_USART_MODULE_ID( index ), PLIB_USART_TWO_STOPBIT     |
                                   PLIB_USART_8_DATABITS_EVEN_PARITY |
                                   flowControl );
    }
    if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_8ODD1)
    {
            PLIB_USART_LineControlModeSelect (
                                   DRV_USART_MODULE_ID( index ), PLIB_USART_ONE_STOPBIT    |
                                   PLIB_USART_8_DATABITS_ODD_PARITY |
                                   flowControl );
    }
    if(lineControlMode & DRV_USART_LINE_CONTROL_MODE_8ODD2)
    {
            PLIB_USART_LineControlModeSelect (
                                   DRV_USART_MODULE_ID( index ), PLIB_USART_TWO_STOPBIT    |
                                   PLIB_USART_8_DATABITS_ODD_PARITY |
                                   flowControl );
    }
*/
}


/*******************************************************************************
 End of File
*/
