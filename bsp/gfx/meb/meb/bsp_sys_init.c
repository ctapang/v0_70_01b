/*******************************************************************************
 Board initialization file for pic18 explorer using the PIM PIC18F47J53

 Company:
    Microchip Technology Inc

 File Name:
    bsp_sys_init.c

 Summary:
    Board initialization file for pic18 explorer using the PIM PIC18F47J53

 Description:
    This file contains the initialization of board specific I/O.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "bsp_config.h"

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

  Remarks:
    This routine performs direct register accesses, when the PORTS PLIB and
    system service become available, these register accesses will be be replaced
    by the PLIB\system service interfaces.

*/

void BSP_Initialize(void)
{


}


void BSP_SwitchONLED(BSP_LED led)
{
    /* switch ON the LED */
    // PLIB_PORTS_PinWrite ( PORTS_ID_0, PORT_CHANNEL_D, led, 1 );
    switch( led )
    {
        case LED_0:
            PORTDbits.RD0 = 1;
            break;

        case LED_1:
            PORTDbits.RD1 = 1;
            break;

        case LED_2:
            PORTDbits.RD2 = 1;
            break;

        default:
            break;
    }
}

void BSP_SwitchOFFLED(BSP_LED led)
{
    /* switch OFF the LED */
    // PLIB_PORTS_PinWrite ( PORTS_ID_0, PORT_CHANNEL_D, led, 0 );
    switch( led )
    {
        case LED_0:
            PORTDbits.RD0 = 0;
            break;

        case LED_1:
            PORTDbits.RD1 = 0;
            break;

        case LED_2:
            PORTDbits.RD2 = 0;
            break;

        default:
            break;
    }
}


/*******************************************************************************
 End of File
*/
