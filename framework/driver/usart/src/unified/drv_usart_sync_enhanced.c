/*******************************************************************************
  USART Driver Feature Variant Implementations

  Summary:
    USART Driver Feature Variant Implementations

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature. The functions are the
    additional functions available on EUSARTs from AUSARTS
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_eusart .c
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
    _DRV_USART_WakeOnStartEnable ( USART_MODULE_ID index )

   Summary:
    Sets up the stop in idle enable

   Description:
    Sets up the stop in idle enable

   Remarks:
    None
 */

void _DRV_USART_WakeOnStartEnable( USART_MODULE_ID index , const DRV_USART_INIT_CONFIG *usartInit )
{
    if (usartInit->initFlags & DRV_USART_INIT_FLAG_WAKE_ON_START_ENABLE)
    {
        PLIB_USART_WakeOnStartEnable ( DRV_USART_MODULE_ID( index ) );
    }
}


// *****************************************************************************
/*  void
    _DRV_USART_SetupAutoBaud ( USART_MODULE_ID index , DRV_USART_INIT_CONFIG *usartInit )

   Summary:
    Sets up the auto baud

   Description:
    Sets up the auto baud

   Remarks:
    None
 */

void _DRV_USART_SetupAutoBaud(USART_MODULE_ID index , const DRV_USART_INIT_CONFIG *usartInit )
{
    if (usartInit->initFlags & DRV_USART_INIT_FLAG_AUTO_BAUD_ENABLE)
    {
        PLIB_USART_BaudRateAutoDetectEnable( DRV_USART_MODULE_ID( index ) );
    }
}

/*******************************************************************************
 End of File
*/
