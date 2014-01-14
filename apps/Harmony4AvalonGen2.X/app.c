/*******************************************************************************
  MPLAB Harmony Application 
  
  File Name:
    app.c

  Summary:
    Application Template

  Description:
	This file contains the application logic.
    
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

#include "app.h"
#include "byte_manipulation.h"
#include "sha256.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appObject = 
{
    NULL,
    Initializing,
    NULL,
    NULL,
    NULL,
    NULL
};

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObject;

DRV_SPI_CLIENT_SETUP drvSPIClientCONFIGSetup =
{
    /* Variable specifying the baud.  */
    .baudRate = 4000000L,

    /* SPI Input Sample Phase Selection */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE,

    /* Set this bit if it has to be logic high to
    assert the chip select */
    .chipSelectLogicLevel = 0,

    /* PORT which the chip select pin belongs to */
    .chipSelectPort = PORT_CHANNEL_B,

    /* Bit position in the port */
    .chipSelectBitPos = PORTS_BIT_POS_13
};

// test data

uint8_t state[32];
uint8_t sendData[128];

const uint8_t sha256_in[] = {0x61, 0x62, 0x63};

/* The correct result is: */
/* ba 78 16 bf 8f 01 cf ea  41 41 40 de 5d ae 22 23 */
/* b0 03 61 a3 96 17 7a 9c  b4 10 ff 61 f2 00 15 ad */

const uint8_t sha256_in2[] = {
	0x61, 0x62, 0x63, 0x64, 0x62, 0x63, 0x64, 0x65,
	0x63, 0x64, 0x65, 0x66, 0x64, 0x65, 0x66, 0x67,
	0x65, 0x66, 0x67, 0x68, 0x66, 0x67, 0x68, 0x69,
	0x67, 0x68, 0x69, 0x6A, 0x68, 0x69, 0x6A, 0x6B,
	0x69, 0x6A, 0x6B, 0x6C, 0x6A, 0x6B, 0x6C, 0x6D,
	0x6B, 0x6C, 0x6D, 0x6E, 0x6C, 0x6D, 0x6E, 0x6F,
	0x6D, 0x6E, 0x6F, 0x70, 0x6E, 0x6F, 0x70, 0x71};

/* The correct result is: */
/* 24 8d 6a 61 d2 06 38 b8  e5 c0 26 93 0c 3e 60 39 */
/* a3 3c e4 59 64 ff 21 67  f6 ec ed d4 19 db 06 c1 */

const uint8_t sha256_in3[] = {
	0x00, 0x00, 0x00, 0x02, 0xd5, 0xa0, 0xf8, 0xa5,
	0xb8, 0x2b, 0x43, 0xd5, 0x80, 0x90, 0xd4, 0x8d,
	0x41, 0xa0, 0x83, 0xe5, 0x71, 0x52, 0x80, 0x62,
	0xe8, 0xe3, 0xae, 0x5a, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x36, 0x9d, 0xab, 0x3f,
	0xbc, 0xe8, 0xd5, 0x4b, 0x23, 0xbf, 0xa1, 0xe4,
	0xdd, 0xd4, 0x3f, 0x5a, 0x92, 0x6e, 0x8a, 0x7a,
	0xcd, 0x1c, 0xc2, 0xa5, 0x35, 0x07, 0x30, 0xd2};

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************



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
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

static int q = 0, r = 0, s = 0;

void APP_Tasks ( void )
{
    uint8_t temp[2 * SHA256_BLOCK_SIZE];
    
    /* check the application state*/
    switch (appObject.appState)
    {
        case Initializing:
            appObject.spiConfigDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_1, DRV_IO_INTENT_WRITE);

            // Setup SPI clients
            DRV_SPI_ClientSetup(appObject.spiConfigDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientCONFIGSetup);
            _DRV_SPI_ClientHardwareSetup(appObject.spiConfigDrvHandle);

            appObject.spiReportDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READ);

            // After initializing we set the state to "WaitingForCommand" and enable USB interrupts
            appObject.appState = WaitingForCommand; // wait for interrupt from USB
            break;

        case WaitingForCommand:
            q++;
            // USB interrupt should be enabled;
            // If a packet came in, process the command here
            // set appState to "PreCalculating" when done analyzing command
            appObject.appState = PreCalculating;
            SYS_ASSERT((appObject.appState == PreCalculating), "");
            break;

        case PreCalculating:
            // do precalc, then wait for report
            sha256_padding( sha256_in, temp, 3);
            flip64bytes(sendData, temp);

            _DRV_SPI_CHIP_SELECT_CLEAR(PORT_CHANNEL_B, PORTS_BIT_POS_13);
            size_t sent = DRV_SPI_Write ( appObject.spiConfigDrvHandle, sendData, 64 );
            while (!PLIB_SPI_TransmitBufferIsEmpty(DRV_SPI_INDEX_1))
                r++;
            //SpinDelay((uint8_t)900);
            _DRV_SPI_CHIP_SELECT_SET(PORT_CHANNEL_B, PORTS_BIT_POS_13);
            SYS_ASSERT((sent = 64), "Not all config bytes sent");
            //appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, sendData, 64);

            appDrvObject.receiveBufHandle = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state, 32);
            appObject.appState = WaitingForReport;
            SYS_ASSERT((appObject.appState == WaitingForReport), "");
            break;

        case WaitingForReport:
            s++;
            // SPI interrupt came in? If so, process it here and then wait for next command
            break;

        case ReadReport:

            appObject.appState = WaitingForCommand;
            break;

        case Idle:
            break;

        default:
            break;

    }

}


/*******************************************************************************
 End of File
 */

