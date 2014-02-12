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
    .baudRate = 2000000L,

    /* SPI Input Sample Phase Selection */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE,

    /* Set this bit if it has to be logic high to
    assert the chip select */
    .chipSelectLogicLevel = 0,

    /* PORT which the chip select pin belongs to */
    .chipSelectPort = PORT_CHANNEL_B,

    /* Bit position in the port */
    .chipSelectBitPos = PORTS_BIT_POS_13
};

DRV_SPI_CLIENT_SETUP drvSPIClientREPORTSetup =
{
    /* Variable specifying the baud.  */
    .baudRate = 2000000L,

    /* SPI Input Sample Phase Selection */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL,

    /* Set this bit if it has to be logic high to
    assert the chip select */
    .chipSelectLogicLevel = 0, // no slave select

    /* PORT which the chip select pin belongs to */
    .chipSelectPort = 2, // invalid port, not used for slave receive

    /* Bit position in the port */
    .chipSelectBitPos = 16 // invalid pin, not used for slave receive
};

// test data
uint8_t state1[SHA256_DIGEST_SIZE];
uint8_t state2[SHA256_DIGEST_SIZE];
uint8_t state3[SHA256_DIGEST_SIZE];

const uint8_t set_clock_low[] = {0x47, 0x00, 0x02, 0x33, 0, 0, 0, 0};
const uint8_t set_clock_high[] = {0xC7, 0x00, 0x02, 0x03, 0, 0, 0, 0};

const uint8_t division_of_labor[] = {
        0x00, 0x00, 0x00, 0x00,
        0x99, 0x99, 0x99, 0x19,
        0x32, 0x33, 0x33, 0x33,
        0xcb, 0xcc, 0xcc, 0x4c,
        0x64, 0x66, 0x66, 0x66,
        0xfd, 0xff, 0xff, 0x7f,
        0x96, 0x99, 0x99, 0x99,
        0x2f, 0x33, 0x33, 0xb3,
        0xc8, 0xcc, 0xcc, 0xcc,
        0x61, 0x66, 0x66, 0xe6 };

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

int test = 0;

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

// private methods

SPI_DATA_TYPE indata[SHA256_DIGEST_SIZE];

// remove this method for the next revision of the PCB card
void invert_logic(SPI_DATA_TYPE *output, SPI_DATA_TYPE *input, int size)
{
    SPI_DATA_TYPE allOnes = (SPI_DATA_TYPE)0xFFFFFFFF; // should work whatever SPI_DATA_TYPE is
    int count = size / sizeof(SPI_DATA_TYPE);
    int i;
    for (i = 0; i < count; i++)
    {
        output[i] = allOnes ^ input[i];
    }
}

uint32_t * re_arrange_words(uint32_t *data, uint32_t *a, uint32_t *e, int byteCount)
{
    int wordCount = byteCount / sizeof(SPI_DATA_TYPE);
    uint32_t *outData = (uint32_t *)malloc(4 * GEN2_INPUT_WORD_COUNT);

    memcpy((uint8_t*)outData, set_clock_high, 8);

    // put data tail in reverse order
    int i;
    for (i = 0; i < 3; i++)
        outData[i + 2] = data[i + 8];

    outData[5] = a[1];
    outData[6] = a[0];
    outData[7] = e[2];
    outData[8] = e[1];
    outData[9] = e[0];

    for (i = 10; i < 18; i++ )
        outData[i] = data[i -10];

    outData[i] = a[2];

    return outData;
}

SPI_DATA_TYPE * massage_data_out( const uint8_t * rawBuf, int size, int *count)
{
    int byteCount = 4 * GEN2_INPUT_WORD_COUNT;
    int dataSize = 2 * SHA256_BLOCK_SIZE;
    uint32_t a[3], e[3];
    uint8_t temp[2 * SHA256_BLOCK_SIZE];

    uint8_t *data = malloc(dataSize); // this is freed in drv_spi_dynamic.c
    memset(data, 0x00, dataSize);
    SYS_ASSERT((size < dataSize), "input data size too large");
    memcpy(data, rawBuf, size);
    
    sha256_precalc(data, a, e, byteCount);
    uint32_t *arranged = re_arrange_words((uint32_t *)data, a, e, byteCount);
    flip4SPI(temp, (uint8_t *)arranged, sizeof(arranged));
    free(arranged);
    // FIXME: remove call to invert_logic once hashing unit PCB is finalized
    invert_logic((SPI_DATA_TYPE *)data, (SPI_DATA_TYPE *)temp, byteCount);
    if (count != NULL)
        *count = byteCount;
    return (SPI_DATA_TYPE *)data;
}

SPI_DATA_TYPE * massage_data_in( const uint8_t * state, int size )
{
    flip4SPI( indata, state, size );
    return indata;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

static int q = 0, r = 0, s = 0, t = 0;
int i = 0;
SPI_DATA_TYPE *dataToSend;
bool done = false;

void APP_Tasks ( void )
{
    DRV_SPI_BUFFER_OBJECT *buf;
    int count;
    
    /* check the application state*/
    switch (appObject.appState)
    {
        case Initializing:
            appObject.spiConfigDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_1, DRV_IO_INTENT_WRITE);

            // Setup SPI clients
            DRV_SPI_ClientSetup(appObject.spiConfigDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientCONFIGSetup);
            _DRV_SPI_ClientHardwareSetup(appObject.spiConfigDrvHandle);

            appObject.spiReportDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READ);
            DRV_SPI_ClientSetup(appObject.spiReportDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientREPORTSetup);
            _DRV_SPI_ClientHardwareSetup(appObject.spiReportDrvHandle);

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
            switch(test)
            {
                case 0:
                    dataToSend = massage_data_out( sha256_in, 3, &count );
                    appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
                    appDrvObject.receiveBufHandle = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state1, SHA256_DIGEST_SIZE);
                    break;
                case 1:
                    dataToSend = massage_data_out( sha256_in2, ARRAY_SIZE(sha256_in2), &count );
                    appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
                    appDrvObject.receiveBufHandle = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state2, SHA256_DIGEST_SIZE);
                    break;
                case 2:
                    dataToSend = massage_data_out( sha256_in3,  ARRAY_SIZE(sha256_in3 ), &count );
                    appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
                    appDrvObject.receiveBufHandle = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state3, SHA256_DIGEST_SIZE);
                    break;
                default:
                    break;
            }


            appObject.appState = WaitingForReport;
            break;

        case WaitingForReport:
            // SPI interrupt came in? If so, process it here and then wait for next command
            if (DRV_SPI_BufferStatus (appDrvObject.receiveBufHandle) == DRV_SPI_BUFFER_EVENT_COMPLETE)
            {
                _DRV_SPI_QueueCleanup( (DRV_SPI_OBJ *)appObject.spiConfigDrvHandle );
                appObject.appState = ReadReport;
            }
            break;

        case ReadReport:
            //buf = (DRV_SPI_BUFFER_OBJECT *)appDrvObject.receiveBufHandle;
            switch (test)
            {
                case 0:
                    massage_data_in( state1, RCV_BUF_SIZE_IN_BYTES );
                    break;
                case 1:
                    massage_data_in( state2, RCV_BUF_SIZE_IN_BYTES );
                    break;
                case 2:
                    massage_data_in( state3, RCV_BUF_SIZE_IN_BYTES );
                    break;
                default:
                    break;
            }
            appObject.appState = WaitingForCommand;
            test++;
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

