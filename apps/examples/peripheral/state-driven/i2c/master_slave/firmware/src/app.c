/*******************************************************************************
  MPLAB Harmony I2C Master Slave Example

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    MPLAB Harmony master_slave application logic

  Description:
    This file contains the MPLAB Harmony master_slave application logic.
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
#include "i2c.h"


// *****************************************************************************
// *****************************************************************************
// Section: Application Variables
// *****************************************************************************
// *****************************************************************************

bool startTransfer;
char *someString = "Microchip I2C";
char *strPtr;


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
    appObject.state = I2C_STATE_IDLE;

    strPtr = someString;
    startTransfer = true;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{
    LEDIndicateWorking();

    if (masterTransferIsComplete() && masterIsIdle())
    {
        switch (appObject.state)
        {
            case I2C_STATE_IDLE:
                if (startTransfer) {
                    appObject.state = I2C_STATE_SEND_START_CONDITION;
                }
                break;

            case I2C_STATE_SEND_START_CONDITION:
                PLIB_I2C_MasterStart(I2C_ID_1);
                appObject.state = I2C_STATE_SEND_ADDRESS_BYTE;
                break;

            case I2C_STATE_SEND_ADDRESS_BYTE:
                PLIB_I2C_TransmitterByteSend(I2C_ID_1, (slaveAddress << 1));
                appObject.state = I2C_STATE_SEND_DATA;
                break;

            case I2C_STATE_SEND_DATA:
                if (PLIB_I2C_TransmitterByteWasAcknowledged(I2C_ID_1)) {
                    if (*strPtr) {
                        PLIB_I2C_TransmitterByteSend(I2C_ID_1, *strPtr++);
                    }
                    else
                        appObject.state = I2C_STATE_SEND_STOP_CONDITION;
                }
                break;

            case I2C_STATE_SEND_STOP_CONDITION:
                PLIB_I2C_MasterStop(I2C_ID_1);
                startTransfer = false;
                appObject.state = I2C_STATE_IDLE;
                break;

            default:
                DBPRINTF("ERROR! Invalid state %d\n", testState);
                while (1);
        }
    }
}


/*******************************************************************************
 End of File
 */
