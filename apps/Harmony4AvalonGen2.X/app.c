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
#include "sha256.h"
#include "GenericTypeDefs.h"
#include "condominer.h"

extern DWORD DivisionOfLabor[10];
extern WORKSTATUS Status;

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
    .appState = Initializing,
    .spiReportModule = NULL,
    .spiReportDrvHandle = NULL,
    .spiConfigModule = NULL,
    .spiConfigDrvHandle = NULL,
    .TimerObjectHandle = NULL,
    .usbDevHandle = USB_DEVICE_HANDLE_INVALID,
    .configValue = 0,
    .deviceIsConfigured = false,
    .testMode = false
};

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObject =
{
    .receiveBufHandle = {NULL, NULL, NULL, NULL},
    .transmitBufHandle = NULL,
    .usbDevObject = SYS_MODULE_OBJ_INVALID,

};

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

// golden nonces received from Asics
uint8_t state1[sizeof(DWORD)];
uint8_t state2[sizeof(DWORD)];
uint8_t state3[sizeof(DWORD)];
uint8_t state4[sizeof(DWORD)];

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

// An Report has arrived from the Asics.
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
    InitializeWorkSystem();

    appObject.epDataReadPending = false ;
    appObject.epDataWritePending = false;
}

// private methods

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

// we have one outputdata for every buffer object in the SPI transmit driver
SPI_DATA_TYPE _outdata[DRV_SPI_BUFFER_OBJ_SIZE][(ARRANGED_SIZE_IN_BYTES / 4) + 1];
int outDataIndex = 0;


SPI_DATA_TYPE * massage_for_send( const uint8_t * rawBuf, int size, int *count)
{
    uint8_t temp1[ARRANGED_SIZE_IN_BYTES];
    uint8_t temp2[ARRANGED_SIZE_IN_BYTES];

    memcpy(temp1, rawBuf, size);
    memcpy(temp1, coded_clock_rate, 8); // overwrite first 2 DWORDs
    memcpy(temp1 + size, (uint8_t *)DivisionOfLabor, 4 * ASIC_COUNT);
    flip4SPI(temp2, temp1, ARRANGED_SIZE_IN_BYTES);

    // very simple outdata allocation because we have one outdata for every buffer obj
    SPI_DATA_TYPE *outdata = _outdata[outDataIndex];
    outDataIndex = (outDataIndex < (DRV_SPI_BUFFER_OBJ_SIZE - 1)) ? outDataIndex + 1 : 0;
    
    // FIXME: remove call to invert_logic once hashing unit PCB is finalized
    invert_logic(outdata, (SPI_DATA_TYPE *)temp2, ARRANGED_SIZE_IN_BYTES);
    if (count != NULL)
        *count = ARRANGED_SIZE_IN_BYTES;

    // save work ID in LAST word in outdata
    outdata[ARRANGED_SIZE_IN_BYTES / 4] = *(SPI_DATA_TYPE *)rawBuf;

    return outdata;
}

BYTE Nonce[4][sizeof(DWORD)];
int nonceCount = 0;
int nonceSent = 0;

void massage_asic_report( const uint8_t * state, int size )
{
    SYS_ASSERT((nonceCount < 4), "Ran out of nonce buffer");
    BYTE * aNonce = Nonce[nonceCount];
    flip4SPI( aNonce, state, size );
    nonceCount++;
}

SYS_TMR_HANDLE timer_handle = NULL;
SPI_DATA_TYPE *dataToSend;
int asicBadOutputCount = 0;
int tc = 0, to = 0, cc = 0;
int j = 0;

void DoneWaiting4Asics()
{
    tc++;
    timer_handle = SYS_TMR_HANDLE_INVALID;
    // Reset bufering mechanism. We have direct access to the actual buffers,
    // and so we don't access the actual buffers through the buffering mechanism.
    DRV_SPI_AbortCurrentReadAndResetBuffers(appObject.spiReportDrvHandle);

    if (Status.State == 'W')
    {
        to++;
        
        // at least the first buffer should have data
        if (state1[0] == 0 && state1[1] == 0 && state1[2] == 0 && state1[3] == 0)
            asicBadOutputCount++;

        if(Status.WorkQC > 0)
            Status.State = 'P';
        else
            Status.State = 'R';
    }
}

// Only one work item can be processed by the Asics at one time.
// The currentWorkID indicates the work item being processed.
DWORD currentWorkID = -1L;

// Event Processing Technique. Event is received when
// the buffer is processed.

void APP_SPITransmitEventHandler( DRV_SPI_BUFFER_EVENT event,
        DRV_SPI_BUFFER_HANDLE handle, uintptr_t context )
{
    if(event == DRV_SPI_BUFFER_EVENT_COMPLETE && Status.State == 'W')
    {
        SPI_DATA_TYPE *buf = _DRV_SPI_GetTransmitBuffer(handle);
        currentWorkID = (DWORD)buf[0]; // pointer has moved past end
        nonceCount = 0;
    }
}

void APP_SPIReceiveEventHandler( DRV_SPI_BUFFER_EVENT event,
        DRV_SPI_BUFFER_HANDLE handle, uintptr_t context )
{
    cc++;
    if(timer_handle == SYS_TMR_HANDLE_INVALID || nonceCount > 3)
    {
        // debug/test
        //massage_data_in(state1, 4);
        //massage_asic_report( state1, sizeof(DWORD)); // puts report in Nonce
        //appObject.appState = ReadReport;
        //APP_Tasks();
        return; // timeout timer invalid during buffer completion event entry
    }

    // We are only interested in the completion event.
    // We use only four buffers. If we run out, just re-use the same buffers, one after another, in a circular buf manner.
    if(event == DRV_SPI_BUFFER_EVENT_COMPLETE)
    {
        if (handle == appDrvObject.receiveBufHandle[0])
        {
            // Process this report
            if (state1[0] != 0 || state1[1] != 0 || state1[2] != 0 || state1[3] != 0)
                massage_asic_report( state1, sizeof(DWORD)); // puts report in Nonce
            else if (Status.State == 'W')
                Status.ErrorCount++;

            // now prepare the next receive buf
            state2[0] = 0; state2[1] = 0; state2[2] = 0; state2[3] = 0;
            appDrvObject.receiveBufHandle[1] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state2, sizeof(DWORD));
        }
        else if (handle == appDrvObject.receiveBufHandle[1])
        {
            // Process this report
            if (state2[0] != 0 || state2[1] != 0 || state2[2] != 0 || state2[3] != 0)
                massage_asic_report( state2, sizeof(DWORD)); // puts report in Nonce
            else if (Status.State == 'W')
                Status.ErrorCount++;

            // now prepare the next receive buf
            state3[0] = 0; state3[1] = 0; state3[2] = 0; state3[3] = 0;
            appDrvObject.receiveBufHandle[2] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state3, sizeof(DWORD));
        }
        else if (handle == appDrvObject.receiveBufHandle[2])
        {
            // Process this report
            if (state3[0] != 0 || state3[1] != 0 || state3[2] != 0 || state3[3] != 0)
                massage_asic_report( state3, sizeof(DWORD)); // puts report in Nonce
            else if (Status.State == 'W')
                Status.ErrorCount++;

            // now prepare the next receive buf
            state4[0] = 0; state4[1] = 0; state4[2] = 0; state4[3] = 0;
            appDrvObject.receiveBufHandle[3] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state4, sizeof(DWORD));
        }
        else if (handle == appDrvObject.receiveBufHandle[3])
        {
            // Process this report
            if (state4[0] != 0 || state4[1] != 0 || state4[2] != 0 || state4[3] != 0)
                massage_asic_report( state4, sizeof(DWORD)); // puts report in Nonce
            else if (Status.State == 'W')
                Status.ErrorCount++;

            // now prepare the next receive buf
            state1[0] = 0; state1[1] = 0; state1[2] = 0; state1[3] = 0;
            appDrvObject.receiveBufHandle[0] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state1, sizeof(DWORD));
        }
        // Don't free this buffer here. Free them all at the same instant in DoneWaiting4Asics above.
        //DRV_SPI_FreeBuffer(appObject.spiReportDrvHandle, handle);

        if (appObject.appState == WaitingForReport)
            appObject.appState = ReadReport;
    }
    SYS_ASSERT((timer_handle != SYS_TMR_HANDLE_INVALID), "timeout timer invalid during buffer completion event (exit)");
}

extern WORKCFG Cfg;

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

bool done = false;
BYTE id = 0;
int usbWaitCount = 0;
DWORD sequencedBuffer[GEN2_INPUT_WORD_COUNT];

void APP_Tasks ( void )
{
    DRV_SPI_BUFFER_OBJECT *buf;
    DWORD nonce;
    int count;
    
    /* check the application state*/
    switch (appObject.appState)
    {
        case Initializing:
            SYS_ASSERT((sha256_test() == 0), "sha256 failed, cannot start");

            Set_Clock_Rate(300); // set clock rate data, not the chips clock itself
            
            appObject.spiConfigDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_1, DRV_IO_INTENT_WRITE);
            SYS_ASSERT(appObject.spiConfigDrvHandle != DRV_HANDLE_INVALID, "Invalid handle from Open");

            // Setup SPI clients
            DRV_SPI_ClientSetup(appObject.spiConfigDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientCONFIGSetup);
            // This SPI module has only one client, so we can set it up here permanently.
            _DRV_SPI_ClientHardwareSetup(appObject.spiConfigDrvHandle);

            DRV_SPI_BufferEventHandlerSet (appObject.spiConfigDrvHandle, APP_SPITransmitEventHandler, NULL );

            appObject.spiReportDrvHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_READ);
            SYS_ASSERT(appObject.spiReportDrvHandle != DRV_HANDLE_INVALID, "Invalid handle from Open");

            DRV_SPI_ClientSetup(appObject.spiReportDrvHandle, (DRV_SPI_CLIENT_SETUP *)&drvSPIClientREPORTSetup);
            // This SPI module has only one client, so we can set it up here permanently.
            _DRV_SPI_ClientHardwareSetup(appObject.spiReportDrvHandle);

            DRV_SPI_BufferEventHandlerSet (appObject.spiReportDrvHandle, APP_SPIReceiveEventHandler, NULL );
            
            Status.State = 'D'; // initially condominer should be dead

            appObject.appState = ResetAvalon;

        case ResetAvalon:
            Reset_All_Avalon_Chips();

            // send message to chips just to set clock
            dataToSend = massage_for_send( (uint8_t *)testChips, 4 * GEN2_INPUT_WORD_COUNT, &count );
            appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
            state1[0] = 0; state1[1] = 0; state1[2] = 0; state1[3] = 0;
            appDrvObject.receiveBufHandle[0] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state1, sizeof(DWORD));

            timer_handle = SYS_TMR_HANDLE_INVALID;

            // We should now be ready to accept commands from cgminer
            //Status.State = 'R';

            appObject.appState = WaitingForUSBConfig;

            break;

        case WaitingForUSBConfig:
            appObject.endpointRx = 0x01;
            appObject.endpointTx = 0x81;

            if (appObject.testMode)
                appObject.appState = WaitingForCommand; // wait for test commands
            else if (appObject.deviceIsConfigured && appObject.configValue == 1)
            {
                usbWaitCount = 0;
                
                appObject.epDataReadPending = true ;
                appObject.bReceivedBufArea = false;
                appObject.bTransmitBufArea = false;
                appObject.rxBufSize = USB_DEVICE_EP1_BUF_SIZE;
                appObject.txBufSize = USB_DEVICE_SEND_HOST_SIZE;
                int bufIndex = appObject.bReceivedBufArea ? appObject.rxBufSize : 0;

                /* Place a new read request. */
                USB_DEVICE_GENERIC_EndpointRead ( USB_DEVICE_GENERIC_INDEX_0,
                                                   &appObject.readTranferHandle,
                                                    appObject.endpointRx,
                                                    &appObject.receivedDataBuffer[bufIndex],
                                                    1 ); // ask for the very minimum

                appObject.epDataWritePending = false ;

                // After initializing we set the state to "WaitingForCommand" and enable USB interrupts
                appObject.appState = WaitingForCommand; // wait for interrupt from USB
            }
            else
            {
                usbWaitCount++;
                if (usbWaitCount > 20000)
                {
                    usbWaitCount = 0;
                    //ReInitializeUSB();

                    appObject.appState = ResetAvalon;
                }
            }
            break;

        case WaitingForCommand:
            // If USB has been reset, restart all Avalon chips and USB.
            if (!appObject.deviceIsConfigured)
            {
                //ReInitializeUSB();
                
                appObject.appState = ResetAvalon;
            }

            // Pick up next work, and
            // set appState to "SendWorkToAsics" if state switches from 'W' to 'P'
            // (If a packet came in from cgminer for the Asic chips, we get out of this state.)
            if (Status.State == 'P')
            {
                DeQueueNextWork(sequencedBuffer);
                Set_Clock_Rate(Cfg.HashClock);
                
                appObject.appState = SendWorkToAsics;
                nonceCount = nonceSent = 0;

                // kill un-triggered timer
                if (timer_handle != SYS_TMR_HANDLE_INVALID)
                    SYS_TMR_CallbackStop(timer_handle);
                timer_handle = SYS_TMR_HANDLE_INVALID;
            }
            
            break;

        case SendWorkToAsics:
            dataToSend = massage_for_send( (uint8_t *)sequencedBuffer, 4 * GEN2_INPUT_WORD_COUNT, &count );
            //dataToSend = massage_for_send( (uint8_t *)testChips, 4 * GEN2_INPUT_WORD_COUNT, &count );
            
            appDrvObject.transmitBufHandle = DRV_SPI_BufferAddWrite(appObject.spiConfigDrvHandle, dataToSend, count);
            state1[0] = 0; state1[1] = 0; state1[2] = 0; state1[3] = 0;
            appDrvObject.receiveBufHandle[0] = DRV_SPI_BufferAddRead(appObject.spiReportDrvHandle, state1, sizeof(DWORD));

            SYS_ASSERT((timer_handle == SYS_TMR_HANDLE_INVALID), "Previous timeout was not triggered");
            timer_handle = SYS_TMR_CallbackSingle (timeout_in_msec, DoneWaiting4Asics);
            SYS_ASSERT((timer_handle != SYS_TMR_HANDLE_INVALID), "Cannot setup Asic wait timeout");
            appObject.appState = WaitingForReport;
            break;

        case WaitingForReport:
            // When work is DONE (timeout occurred), get next work item.
            if (timer_handle == SYS_TMR_HANDLE_INVALID)
            {
                appObject.appState = WaitingForCommand;
                nonceSent = 0;
            }
            break;
        case ReadReport:
            // send this result back to cgminer
            SYS_ASSERT((nonceSent < 4), "Too many nonces");
            SYS_ASSERT((nonceCount > 0), "No report");
            if (nonceCount > nonceSent)
            {
                BYTE *noncePtr = Nonce[nonceSent++];
                int32_t *wordPtr = (int32_t *)noncePtr;
                *wordPtr = *wordPtr - 0xC0;  // Klondike cgminer Gen1 driver takes away 0xC0 also

                SYS_ASSERT((sequencedBuffer[0] == currentWorkID), "work ID incorrect");
                
                ResultRx(noncePtr, currentWorkID, sequencedBuffer);

                appObject.appState = WaitingForReport;
            }
            break;

        case Idle:
            SYS_ASSERT(false, "Invalid app state");
            break;

        default:
            break;

    }

}


/*******************************************************************************
  Function:
    void APP_GenUSB_CallBack ( SYS_MODULE_INDEX funcDriverIndex,
		USB_DEVICE_GEN_DRIVER_CALLBACK_TYPE callback,
		USB_DEVICE_GEN_DRIVER_CALLBACK_EVENT event)


  Summary:
    Application Callback.


  Description:
    This function gets called by the Generic USB function driver if any event of type
    USB_DEVICE_GEN_DRIVER_CALLBACK_EVENT occurs.

  Parameters:
    callback        - Callback type that indicates the why this callback was
                      called.
    event           - Indicates what event triggered this callback.

  Returns:
    None.
 */

int x = 0, y = 0, z = 0;
BYTE buf[100];

extern int countAfter;
int readCompletionTime = -1;

void APP_USBDeviceGenericEventHandler ( USB_DEVICE_GENERIC_INDEX iGEN,
                           USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                           USB_DEVICE_GENERIC_EVENT event,
                           USB_DEVICE_GENERIC_EVENT_DATA * eventData,
                           uintptr_t userData )
{
    // Check type of callback
    switch (event)
    {
        case USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE:
            appObject.epDataWritePending = false;
            z++;
            break;

        case USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE:
            
            appObject.epDataReadPending = false;
            appObject.bReceivedBufArea = !appObject.bReceivedBufArea;
            int bufIndex = appObject.bReceivedBufArea ? appObject.rxBufSize : 0;

            /* Place a new read request. */
            USB_DEVICE_GENERIC_EndpointRead ( USB_DEVICE_GENERIC_INDEX_0,
                                               &appObject.readTranferHandle,
                                                appObject.endpointRx,
                                                &appObject.receivedDataBuffer[bufIndex],
                                                appObject.rxBufSize );

            // be ready to receive next command
            appObject.epDataReadPending = true ;

            if (x < 100)
                buf[x++] = eventData->endpointReadComplete.data[0];
            y++;
            
            // execute the command from cgminer
            ProcessCmd(eventData->endpointReadComplete.data);
            break;

        case USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_ABORTED:
            break;

        default:
            break;
    }

}

/*******************************************************************************
  Function:
    void APP_UsbDeviceEventCallBack ( void )

  Summary:
    Event callback generated by USB device layer.

  Description:
   It is very important that when device is configured, application initializes
   handles to correct function driver. If device is deconfigured, application
   has to close peviously opened handles to function drivers.

  Parameters:
    None.

  Returns:
    None.
 */
static int p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0;

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData)
{

    switch( event )
    {
        case USB_DEVICE_EVENT_RESET:
            p++;

            appObject.deviceIsConfigured = false;
            break;
        case USB_DEVICE_EVENT_DECONFIGURED:
            // Turn OFF then ON the green LED to indicate reset/deconfigured state.
            //Reset_All_Avalon_Chips();
            q++;
            break;

        case USB_DEVICE_EVENT_CONFIGURED:
            /* check the configuration */
            if( eventData->eventConfigured.configurationValue == 1 )
            {
                /* Reset endpoint data send & receive flag  */
                appObject.deviceIsConfigured = true;
                appObject.configValue = 1;

                //APP_Initialize();
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            r++;
            break;

        case USB_DEVICE_EVENT_RESUMED:
            s++;
            break;
        case USB_DEVICE_EVENT_ATTACHED:
            t++;
            break;
        case USB_DEVICE_EVENT_DETACHED:
            u++;
            break;
        case USB_DEVICE_EVENT_ERROR:
            v++;
            break;
        default:
            w++;
            break;

    }
}

/*******************************************************************************
 End of File
 */

