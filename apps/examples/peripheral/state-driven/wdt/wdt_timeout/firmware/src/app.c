/*******************************************************************************
  MPLAB Harmony WDT Timeout Example

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    MPLAB Harmony wdt_timeout application logic

  Description:
    This file contains the MPLAB Harmony wdt_timeout application logic.
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"


// *****************************************************************************
/* Application Data

  Summary:
    Contains application data

  Description:
    This structure contains application data.
*/

APP_DATA appObject;


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Initialize ( void )
{
    /* Clear the core timer. */
    BSP_WriteCoreTimer(0);

    /* Put the application into its initial state */
    appObject.state = APP_STATE_IDLE;
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Take appropriate action, depending on the current state. */
    switch (appObject.state)
    {

        case APP_STATE_WDT_TIMEOUT_HANDLER:
        {
            /* Disable the WDT to keep it from resetting the system again */
            PLIB_WDT_Disable(WDT_ID_0);

            /* Clear the WDT timer */
            PLIB_WDT_TimerClear(WDT_ID_0);

            /* User code to handle a WDT timeout event would be here */
            /* Setting the 3rd LED to indicate a WDT timeout occured */
            BSP_SwitchONLED(LED_3);

            /* Return to IDLE state after WDT timeout event has been processed */
            appObject.state = APP_STATE_IDLE;

            /* Clear the WDT timeout flag, so a subsequent event can set the bit */
            RCONbits.WDTO = 0;

            /* Re-enable the WDT */
            PLIB_WDT_Enable(WDT_ID_0);

            break;
        }

         /* Application is stuck in an idle loop. */
        case APP_STATE_IDLE:
        {
            /* If a WDT timeout has occured, change state to handle the WDT */
            if (RCONbits.WDTO) 
            {
                appObject.state = APP_STATE_WDT_TIMEOUT_HANDLER;

                break;
            }

            /* If the core time counts to one second, change state to BLINK_LED */
            if (BSP_ReadCoreTimer() >= APP_LED_BLINK_DELAY_1s)
            {
               appObject.state = APP_STATE_BLINK;
            }

            /* Service the WDT */
            PLIB_WDT_TimerClear(WDT_ID_0);

            break;
        }

        /* Continuously blinking the LED. */
        case APP_STATE_BLINK:
        {
            /* Toggle LED */
            BSP_ToggleLED(LED_1);
            
            /* Put the application back to the idle state*/
            appObject.state = APP_STATE_IDLE;

            /* Clear the core timer to restart count. */
            BSP_WriteCoreTimer(0);

            break;
        }

        /* Should not come here during normal operation */
        default:
        {
            PLIB_ASSERT(false , "unknown application state");

            break;
        }

    }
}


/*******************************************************************************
 End of File
 */
