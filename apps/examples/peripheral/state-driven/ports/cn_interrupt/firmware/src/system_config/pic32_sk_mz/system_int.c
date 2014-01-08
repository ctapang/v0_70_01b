/*******************************************************************************
  MPLAB Harmony Change Notice Example

  Company:
    Microchip Technology Inc.

  File Name:
    system_init.c

  Summary:
    MPLAB Harmony cn_interrupt interrupt service routine.

  Description:
    This file contains the MPLAB Harmony cn_interrupt ISR, which toggles the
   state from IDLE to BLINKING on button press.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#if defined(cfg_pic32_sk_mz)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "peripheral/peripheral.h"
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

bool buttonWasPressed = false;


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_CHANGE_NOTICE_B_VECTOR)))
ChangeNoticeHandler(void)
{  
    if (!buttonWasPressed) // if button was not already pushed down
    {
        buttonWasPressed = true;

        if (appObject.state == APP_STATE_BLINKING)
        {
            BSP_SwitchOFFLED(LED_1);

            appObject.state = APP_STATE_IDLE;
        }

        else
            appObject.state = APP_STATE_BLINKING;
    }

    else // if button is already pushed down, ignore
        buttonWasPressed = false;
    

    unsigned int temp;

    /* Read port to clear mismatch on change notice pins */
    temp = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B);

    /* Clear the interrupt flag */
    //PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    IFS3bits.CNBIF = 0;
}


#endif //__32MZ2048ECH144__


/*******************************************************************************
 End of File
*/
