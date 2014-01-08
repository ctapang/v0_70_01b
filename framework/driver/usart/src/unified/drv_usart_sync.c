/*******************************************************************************
  USART Driver Feature Variant Implementations

  Summary:
    USART Driver Feature Variant Implementations

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature and available on AUSARTs and
    USARTS and the functions common to EUSARTS
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_usart .c
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

#include "usart/src/drv_usart_local.h"

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


void _DRV_USART_SetupLineControlModes_V2(USART_MODULE_ID index, DRV_USART_LINE_CONTROL_MODES lineControlMode)
{                                                                       
    if (lineControlMode == DRV_USART_LINE_CONTROL_MODE_9NONE1)
    {
        PLIB_USART_Receiver9BitModeEnable ( DRV_USART_MODULE_ID( index ) );
        PLIB_USART_Transmitter9BitModeEnable ( DRV_USART_MODULE_ID( index ) );
    }
}

// *****************************************************************************
/*  void
    _DRV_USART_SetupSyncMasterMode ( USART_MODULE_ID index )

   Summary:
    Sets up the synchronous master mode

   Description:
    Sets up the synchronous master mode

   Remarks:
    None
 */

void _DRV_USART_SetupSyncMaster(USART_MODULE_ID index, DRV_USART_OPERATION_MODES operationMode)
{                                                                       
    if (operationMode == DRV_USART_OPERATION_MODE_SYNCHRONOUS_MASTER)
    {
        PLIB_USART_SyncModeSelect ( DRV_USART_MODULE_ID( index ) );
        PLIB_USART_SyncClockSourceMasterSelect ( DRV_USART_MODULE_ID( index ) );
    }
}


// *****************************************************************************
/*  void
    _DRV_USART_SetupSyncSlaveMode ( USART_MODULE_ID index )

   Summary:
    Sets up the synchronous slave mode

   Description:
    Sets up the synchronous slave mode

   Remarks:
    None
 */

void _DRV_USART_SetupSyncSlave(USART_MODULE_ID index, DRV_USART_OPERATION_MODES operationMode)
{                                                                       
    if (operationMode == DRV_USART_OPERATION_MODE_SYNCHRONOUS_SLAVE)
    {
        PLIB_USART_SyncModeSelect ( DRV_USART_MODULE_ID( index ) );
        PLIB_USART_SyncClockSourceSlaveSelect ( DRV_USART_MODULE_ID( index ) );
    }
}


/*******************************************************************************
 End of File
*/
