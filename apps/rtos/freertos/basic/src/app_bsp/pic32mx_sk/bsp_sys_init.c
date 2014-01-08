/*******************************************************************************
 Board initialization file for PIC32 USB starter kit

 Company:
    Microchip Technology Inc.

 File Name:
    bsp_sys_init.c

 Summary:
    Board initialization file for PIC32 USB starter kit

 Description:
    This file contains the initialization of board specific I/O.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#if defined(__32MX795F512L__)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "bsp_config.h"
#include "peripheral/ports/plib_ports.h"
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board

*/

void BSP_Initialize(void )
{

    /* Set LED pins as output. Switch 
     * the LEDs off.  */
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_0);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);

    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_0);
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_1);
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2);
}


/*******************************************************************************
  Function: void BSP_ToggleLED(void)

  Summary:
    Toggles the specified LED

  Description:
    Toggles the specified LED

*/

void BSP_ToggleLED(BSP_LED led)
{

    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, led);
}



/******************************************************************************/
/******************************************************************************/

#endif //__32MX795F512L__

/*******************************************************************************
 End of File
*/
