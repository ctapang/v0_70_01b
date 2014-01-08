/*******************************************************************************
  MPLAB Harmony I2C Master Slave Example

  Company:
    Microchip Technology Inc.

  File Name:
    system_init.c

  Summary:
    MPLAB Harmony master_slave interrupt service routine.

  Description:
    This file contains the MPLAB Harmony wdt_timeout ISR, which implements
    a blocking loop when one of the buttons are pressed. This blocking loop
    causes a WDT timeout event to occur.
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

#if defined(cfg_ex16_pic32mx795f512l)

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

char dataBuff[32];
unsigned int buffIndex = 0;


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_I2C_2_VECTOR)))
i2cSlaveHandler(void)
{
    char temp;

    /* Last byte received was address with write indication */
    if ((!PLIB_I2C_SlaveReadIsRequested(I2C_ID_2)) && (PLIB_I2C_SlaveAddressIsDetected(I2C_ID_2)))
    {
        /* Dummy read to clear receive buffer */
        temp = SlaveRead();

        /* Instruct slave to release the clock */
        PLIB_I2C_SlaveClockRelease(I2C_ID_2);
    }

    /* Last byte received was data with write indication */
    else if ((!PLIB_I2C_SlaveReadIsRequested(I2C_ID_2)) && (PLIB_I2C_SlaveDataIsDetected(I2C_ID_2)))
    {
        /* Store the received data into dataBuff[] array */
        dataBuff[buffIndex] = SlaveRead();

        /* Increment the index */
        buffIndex++;

        /* Instruct slave to release the clock */
        PLIB_I2C_SlaveClockRelease(I2C_ID_2);
    }

    /* Clear the interrupt flag */
    IFS1 = (0 << 12);
}


#endif //__32MX795F512L__


/*******************************************************************************
 End of File
*/
