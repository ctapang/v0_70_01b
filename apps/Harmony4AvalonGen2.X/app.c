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
#include "GenericTypeDefs.h"

extern DWORD DivisionOfLabor[10];


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

// "Config" message link to the A3255 chips
// Note that although the link has queuing capability, we are not using
// that capability because we have to wait for the "Report" signal from
// the chips (on the other SPI channel) before we can issue the next
// "Config" message.
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
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE,

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

// bit 0*1 2 3 4*5 6 7 ... 15 16*17 18 19 20*21 22 23 24*25 26 27 28*29 30 .. 63
//     | | | | | | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  |  | reserved
//     | | | | | | | | rsvd |  |----- R ---|  |------ F --------|  OD OD
//     | | | | | | +- output clock to pin if set
//     | | | | | +- use external clock XCLKIN for clock if set
//     | | | | +- divide by 2 if set
//     | | | +- clock gating if set
//     | | +- make clock divider settings (R, F, and OD) effective if set
//     | +- make all clock configuration settings effective if set
//     +- must always be set
//
//const uint8_t set_clock_low[] = {0x27, 0x00, 0x02, 0x33, 0, 0, 0, 0};
const uint8_t set_clock_lowest[] = {0x27, 0x00, 0x03, 0x0F, 0, 0, 0, 0};  // chips cool to the touch, 355mSecs
const uint8_t set_clock_low[] = {0x07, 0x00, 0x20, 0x07, 0, 0, 0, 0};//
const uint8_t set_clock_medium_low[] = {0x07, 0x00, 0x10, 0x07, 0, 0, 0, 0};// 106mSecs          (3.5 x 50)
const uint8_t set_clock_medium[] = {0x07, 0x00, 0x08, 0x07, 0, 0, 0, 0};    //                   (07 x 50)
const uint8_t set_clock_medium_high[] = {0x07, 0x00, 0x04, 0x07, 0, 0, 0, 0}; //warm, 31.5mSecs  (14 x 50)
const uint8_t set_clock_high[] = {0x07, 0x00, 0x06, 0x0F, 0, 0, 0, 0}; // not too hot, 21mSecs   (20 x 50)
const uint8_t set_clock_highest[] = {0x07, 0x00, 0x04, 0x0F, 0, 0, 0, 0}; // 15.1mSecs           (30 x 50)
const uint8_t set_clock_unchanged[] = {0x01, 0x00, 0x00, 0x00, 0, 0, 0, 0};

DWORD asic_clock_rate_in_MHz = 1500; // in MHz
const uint8_t *coded_clock_rate = set_clock_highest;
DWORD timeout_in_msec = 4294967 / (1500 * ASIC_COUNT);


const uint32_t testChips[] = {
    //0x07C10067,
    0x05010067,
    //0x00000001,
    0x00000000,

    0x4ac1d001,
    0x88517050,
    0x087e051a,

    0x05b168ae,
    0x62a5f25c,
    0x81677107,
    0x12cdfd7b,
    0xfa77fe7d,

    0x9cb18a17,
    0x65c90d1e,
    0x8f41371d,
    0x974bf4bb,
    0x7145fd6d,
    0xc44192c0,
    0x12146495,
    0xd8f8ef67,

    0x220f1dbd
};


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************
void Set_Clock_Rate(DWORD freqInMHz)
{
    SYS_ASSERT((freqInMHz <= 1500), "cannot set clock: too high");
    if (freqInMHz > 1100)
    {
        coded_clock_rate = set_clock_highest;
        asic_clock_rate_in_MHz = 30 * 50;
    }
    else if (freqInMHz > 800)
    {
        coded_clock_rate = set_clock_high;
        asic_clock_rate_in_MHz = 20 * 50;
    }
    else if (freqInMHz > 400)
    {
        coded_clock_rate = set_clock_medium_high;
        asic_clock_rate_in_MHz = 14 * 50;
    }
    else if (freqInMHz > 200)
    {
        coded_clock_rate = set_clock_medium;
        asic_clock_rate_in_MHz = 7 * 50;
    }
    else if (freqInMHz > 150)
    {
        coded_clock_rate = set_clock_medium_low;
        asic_clock_rate_in_MHz = 3 * 50 + 25;
    }
    else if (freqInMHz > 80)
    {
        coded_clock_rate = set_clock_low;
        asic_clock_rate_in_MHz = 50 + 38;
    }
    else
    {
        coded_clock_rate = set_clock_lowest;
        asic_clock_rate_in_MHz = 50;
    }
    timeout_in_msec = 4294967 / (asic_clock_rate_in_MHz * ASIC_COUNT);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
void ASIC_wait_callback()
{
    appObject.appState = ReadReport;
}


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
    uint32_t *outData = (uint32_t *)malloc(ARRANGED_SIZE_IN_BYTES);
    uint32_t *divlabor = (uint32_t *)DivisionOfLabor;

    memcpy((uint8_t*)outData, set_clock_highest, 8);

    // put data tail in reverse order
    int i, j;
    for (i = 2, j = 0; j < 3; i++, j++)
        outData[i] = data[j];

    outData[5] = a[1];
    outData[6] = a[0];
    outData[7] = e[2];
    outData[8] = e[1];
    outData[9] = e[0];

    for (i = 10, j = 3; i < 18; i++, j++ )
        outData[i] = data[j];

    outData[i] = a[2];

    // initial nonces, 10 words
    for (i = 19, j = 0; i < 29; i++, j++)
    {
        outData[i] = divlabor[j];
    }

    // 29 words total = 116 bytes = 928 bits

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
    flip4SPI(temp, (uint8_t *)arranged, ARRANGED_SIZE_IN_BYTES);
    free(arranged);
    // FIXME: remove call to invert_logic once hashing unit PCB is finalized
    invert_logic((SPI_DATA_TYPE *)data, (SPI_DATA_TYPE *)temp, ARRANGED_SIZE_IN_BYTES);
    if (count != NULL)
        *count = ARRANGED_SIZE_IN_BYTES;
    return (SPI_DATA_TYPE *)data;
}

//void SendAsicData(WORKTASK *work)
//{
//
//}

SPI_DATA_TYPE * massage_for_send( const uint8_t * rawBuf, int size, int *count)
{
    uint8_t temp1[ARRANGED_SIZE_IN_BYTES];
    uint8_t temp2[ARRANGED_SIZE_IN_BYTES];
    uint8_t *data = malloc(ARRANGED_SIZE_IN_BYTES); // this is freed in drv_spi_dynamic.c

    memcpy(temp1, rawBuf, size);
    memcpy(temp1, coded_clock_rate, 8);
    memcpy(temp1 + size, (uint8_t *)DivisionOfLabor, 4 * ASIC_COUNT);
    flip4SPI(temp2, temp1, ARRANGED_SIZE_IN_BYTES);
    // FIXME: remove call to invert_logic once hashing unit PCB is finalized
    invert_logic((SPI_DATA_TYPE *)data, (SPI_DATA_TYPE *)temp2, ARRANGED_SIZE_IN_BYTES);
    if (count != NULL)
        *count = ARRANGED_SIZE_IN_BYTES;
    return (SPI_DATA_TYPE *)data;
}

SPI_DATA_TYPE * massage_data_in( const uint8_t * state, int size )
{
    flip4SPI( indata, state, size );
    return indata;
}

void Wait4AsicsDone()
{
    if (appObject.appState == WaitingForReport)
        appObject.appState = ReadReport;
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
    SYS_TMR_HANDLE timer_handle = NULL;
    
    /* check the application state*/
    switch (appObject.appState)
    {
        case Initializing:
            SYS_ASSERT((sha256_test() == 0), "sha256 failed, cannot start");

            Set_Clock_Rate(500);
            
            appObject.spiConfigDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_1, DRV_IO_INTENT_WRITE);
            SYS_ASSERT(appObject.spiConfigDrvHandle != DRV_HANDLE_INVALID, "Invalid handle from Open");

            // Setup SPI clients
            DRV_SPI_ClientSetup(appObject.spiConfigDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientCONFIGSetup);
            // This SPI module has only one client, so we can set it up here permanently.
            _DRV_SPI_ClientHardwareSetup(appObject.spiConfigDrvHandle);

            appObject.spiReportDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READ);
            SYS_ASSERT(appObject.spiReportDrvHandle != DRV_HANDLE_INVALID, "Invalid handle from Open");

            DRV_SPI_ClientSetup(appObject.spiReportDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientREPORTSetup);
            // This SPI module has only one client, so we can set it up here permanently.
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
            dataToSend = massage_for_send( (uint8_t *)testChips, 4 * GEN2_INPUT_WORD_COUNT, &count );
            appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
            appDrvObject.receiveBufHandle = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state1, 4 /*SHA256_DIGEST_SIZE */);

            timer_handle = SYS_TMR_CallbackSingle (timeout_in_msec, Wait4AsicsDone);
            appObject.appState = WaitingForReport;
            break;

        case WaitingForReport:
            // SPI interrupt came in? If so, process it here and then read report
            if (DRV_SPI_BufferStatus (appDrvObject.receiveBufHandle) == DRV_SPI_BUFFER_EVENT_COMPLETE)
            {
                free(dataToSend);
                appObject.appState = ReadReport;
            }
            break;

        case ReadReport:
            massage_data_in( state1, RCV_BUF_SIZE_IN_BYTES );

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

