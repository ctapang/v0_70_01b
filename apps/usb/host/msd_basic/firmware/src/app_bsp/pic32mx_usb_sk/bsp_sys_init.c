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

void BSP_Initialize(void )
{

    /* Set the switch pins as input
     * and the LED pins as output. Switch 
     * the LEDs off. Enable the Change Notice
     * Pull up resitors. */

    TRISDSET = 0x20C0;
    TRISDCLR = 0x7;
    LATDCLR =  0x7;
    CNPUESET = 0x98000;
}

void BSP_SwitchONLED(BSP_LED led)
{

    /* switch ON the LED */
    LATDSET = (1 << led);

}

void BSP_SwitchOFFLED(BSP_LED led)
{
    
    /* switch OFF the LED */
     LATDCLR = (1 << led);
}

void BSP_ToggleLED(BSP_LED led)
{

    LATDINV = (1 << led);
}

BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch )
{
    return ( ((PORTD & (1 << bspSwitch)) == 0) ? BSP_SWITCH_STATE_PRESSED :
        BSP_SWITCH_STATE_RELEASED );
}

uint32_t BSP_ReadCoreTimer()
{
    uint32_t timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}


/******************************************************************************/
/******************************************************************************/

#endif //__32MX795F512L__

/*******************************************************************************
 End of File
*/
