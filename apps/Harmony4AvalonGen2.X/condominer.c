#include "GenericTypeDefs.h"
#include <xc.h>
#include "app.h"
#include "condominer.h"


DWORD DivisionOfLabor[10] = {
    0x00000000,
    0x19999999,
    0x33333332,
    0x4ccccccb,
    0x66666664,
    0x7ffffffd,
    0x99999996,
    0xb333332f,
    0xccccccc8,
    0xe6666661
};
BYTE WorkNow, BankSize, ResultQC, SlowTick, TimeOut, TempTarget;
//BYTE HashTime = 256 - ((WORD)TICK_TOTAL/DEFAULT_HASHCLOCK);
volatile WORKSTATUS Status = {USB_ID_1,'I',0,1,0,0,0,0,0, (WORD)0, WORK_TICKS, 0 };
volatile WORKRESULT WResult = {USB_ID_1, 0, 0L};
WORKCFG Cfg = { USB_ID_1, 1500, 0, 0, 0, 0 };
WORKTASK *pWork;
WORKTASK alternatePreCalcCopy;
WORKTASK WorkQue[MAX_WORK_COUNT];
volatile BYTE ResultQue[RESULT_SIZE];
//DWORD ClockCfg[2] = { (((DWORD)DEFAULT_HASHCLOCK) << 18) | CLOCK_LOW_CHG, CLOCK_HIGH_CFG };
INT16 Step, Error, LastError;

DWORD NonceRanges[10];

const IDENTITY ID = {USB_ID_1, 2, "Swauk1", 0xA51C };

#define r(x) ((x-n)&7)


DWORD rotate(DWORD x, BYTE y)
{
    return ((x<<y) | (x>>(32-y)));
}

void AsicPreCalc(WORKTASK *work)
{
    DWORD K[3] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf };
    DWORD x, y, z;
    DWORD m[8];
    int n;

    for(n = 0; n < 8; n++)
        m[n] = work->MidState[n];

    for(n = 0; n < 3; n++) {

        x = m[5-n] ^ m[6-n];
        x = x & m[4-n];
        x = m[6-n] ^ x;
        x += K[n];
        x += work->Merkle[n];
        x += m[7-n];
        y = rotate(m[4-n], 26);
        z = rotate(m[4-n], 21);
        z = y^z;
        y = rotate(m[4-n], 7);
        z = y^z;
        m[7-n] = z+x;
        m[3-n] = m[3-n] + m[7-n];
        x = rotate(m[r(0)], 30);
        y = rotate(m[r(0)], 19);
        y = y^x;
        x = rotate(m[r(0)], 10);
        y = x^y;
        x = m[r(0)] | m[r(1)];
        x = m[r(2)] & x;
        z = m[r(0)] & m[r(1)];
        x = x | z;
        m[7-n] += y + x;

        work->PrecalcHashes[2-n] = m[7-n];
        work->PrecalcHashes[5-n] = m[3-n];
    }
}

USB_ERROR usbResult;
int disposedCount = 0;

// This executes in the context of a USB interrupt (called from ProcessCmd()),
// and also in the context of the main program loop (called from ResultTx()).
void SendCmdReply(char *cmd, BYTE *data, BYTE count)
{
    int bufIndex;
    bool intEnabled;

    if(appObject.transmitBufArea < USB_DEVICE_MSGBUF_COUNT)
    {
        intEnabled = USBMutexOpen();

        bufIndex = (appObject.transmitBufArea + appObject.pullPoint) % USB_DEVICE_MSGBUF_COUNT;
        bufIndex = bufIndex * (appObject.txBufSize + 1);

        SYS_ASSERT(((count + 1) <= appObject.txBufSize), "size to transmit too large");

        appObject.transmitDataBuffer[bufIndex] = cmd[0];
        //appObject.transmitDataBuffer[bufIndex + 1] = data[0]; // USB_ID_1
        memcpy(appObject.transmitDataBuffer + bufIndex + 1, data, count);
        if (count < appObject.txBufSize)
            memset(appObject.transmitDataBuffer + bufIndex + count + 1, (BYTE)0, appObject.txBufSize - count);

        appObject.transmitBufArea++;

        USBMutexClose(intEnabled);
    }
    else
    {
        disposedCount++; // debug point
    }
}

int tenMSecTimer = 0;

void TraceTimer()
{
    tenMSecTimer++;
}

int recycleCount = 0;
int pendingCountTrace[1000];
int traceIndex = 0;

void PutTraceEntry(int *pindex, int time, int pendCount)
{
    if (*pindex >= 1000)
        return;

    pendingCountTrace[(*pindex)++] = (time << 8) | (pendCount & 0xFF);
}

// This executes in the context of the main thread
void AsyncSendUSB()
{
    int bufIndex;
    bool intEnabled;

    if(USBConfigured())
    {
        while(appObject.transmitBufArea > 0) // while there is something to pull
        {
            PutTraceEntry( &traceIndex, tenMSecTimer, appObject.transmitBufArea);

            intEnabled = USBMutexOpen();

            bufIndex = appObject.pullPoint * (appObject.txBufSize + 1);

            // check for invalid cmd
            SYS_ASSERT((appObject.transmitDataBuffer[bufIndex] > '!'), "bad command");

            /* Send the data to the host */

            if (appObject.testMode)
                test_reply(&appObject.transmitDataBuffer[bufIndex]);
            else
            {
                usbResult = USB_DEVICE_GENERIC_EndpointWrite( USB_DEVICE_GENERIC_INDEX_0,
                        ( USB_DEVICE_GENERIC_TRANSFER_HANDLE *)&appObject.writeTranferHandle,
                        appObject.endpointTx, &appObject.transmitDataBuffer[bufIndex],
                        appObject.txBufSize,
                        USB_DEVICE_GENERIC_TRANSFER_FLAG_NONE );

                SYS_ASSERT((usbResult == USB_DEVICE_GENERIC_RESULT_OK), "bad result");
            }

            appObject.pullPoint = (appObject.pullPoint + 1) % USB_DEVICE_MSGBUF_COUNT;
            appObject.transmitBufArea--;

            USBMutexClose(intEnabled);
        }
    }
    else
        PutTraceEntry( &traceIndex, 0, appObject.transmitBufArea);
}

char commandTrace[100];
int cmdIndex = 0;
int i;

extern void Reset_All_Avalon_Chips();

// swap bytes of a full word
// Note: PIC32MX is little endian
DWORD SwapBytesIfNecessary(BYTE *psrc, bool necessary)
{
    DWORD word;
    BYTE *pdst = (BYTE *)&word;
    if (necessary)
    {
        pdst[0] = psrc[3];
        pdst[1] = psrc[2];
        pdst[2] = psrc[1];
        pdst[3] = psrc[0];
    }
    else
    {
        pdst[0] = psrc[0];
        pdst[1] = psrc[1];
        pdst[2] = psrc[2];
        pdst[3] = psrc[3];
    }
    return word;
}

WORKCFG tempCfg;

// This is always called in the context of USB interrupt
void ProcessCmd(char * ourPtr)
{
    // cmd is one char, dest address 1 byte, data follows
    // we already know address is ours here
    if (cmdIndex < 100)
        commandTrace[cmdIndex++] = ourPtr[0];
    switch(ourPtr[0]) {
        case 'W': // queue new work
            if( Status.WorkQC < MAX_WORK_COUNT && Status.State != 'D' ) {
                WORKTASK *work = &WorkQue[ (WorkNow + Status.WorkQC) & WORKMASK ];
                work->Device = ourPtr[1];
                work->WorkID = ourPtr[2];
                // cmd input is little-endian, and we are also little-endian
                for (i = 0; i < 8; i++)
                    work->MidState[i] = SwapBytesIfNecessary(ourPtr + 4*i + 3, true);
                for (i = 0; i < 3; i++)
                    work->Merkle[i] = SwapBytesIfNecessary(ourPtr + 4*i + 35, true);
                if(Status.State == 'R') {
                    Status.State = 'P'; // AssembleWorkForAsics(out);
                }
                Status.WorkQC++;
            }
            else if (cmdIndex < 100)
            {
                commandTrace[cmdIndex++] = 'X';
            }
            SendCmdReply(ourPtr, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'A': // abort work, reply status has hash completed count
            Status.WorkQC = 0;
            Status.State = 'R';
            SendCmdReply(ourPtr, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            Reset_All_Avalon_Chips();
            break;
        case 'I': // return identity 
            SendCmdReply(ourPtr, (char *)&ID, 13);
            break;
        case 'S': // return status 
            SendCmdReply(ourPtr, (char *)&Status, 14); // sizeof(WORKSTATUS));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'C': // set config values 
            if( *(WORD *)&ourPtr[2] != 0 )
            {
                //Cfg = *(WORKCFG *)(cmd+2);
                Cfg.Device = ourPtr[1];
                Cfg.HashClock = ourPtr[2];
                Cfg.HashClock += ((WORD)ourPtr[3]) << 8;
                Cfg.TempTarget = ourPtr[4];
                Cfg.Future1 = ourPtr[5];
                Cfg.Future2 = ourPtr[6];
                Cfg.Future3 = ourPtr[7];
            }
            memcpy(&tempCfg, &Cfg, sizeof(WORKCFG));
            tempCfg.HashClock = Cfg.HashClock >> 8;
            tempCfg.HashClock += (Cfg.HashClock & 0xFF) << 8;
            SendCmdReply(ourPtr, (char *)&tempCfg, sizeof(WORKCFG));
            break;
        case 'E': // enable/disable work
            Status.State = (ourPtr[2] == '1') ? ((Status.WorkQC > 0) ? 'P' : 'R') : 'D';
            SendCmdReply(ourPtr, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        default:
            break;
    }
}

void ArrangeWords4TxSequence(WORKTASK * work, DWORD * buf)
{
    buf[0] = (DWORD)work->WorkID; // for clock, to be set later
    buf[1] = 0L; // for clock, to be set later
    // Merkle, PrecalHashes, and MidState are all big-endian, so we swap bytes
    buf[2] = SwapBytesIfNecessary((BYTE*)&work->Merkle[0], true);
    buf[3] = SwapBytesIfNecessary((BYTE*)&work->Merkle[1], true);
    buf[4] = SwapBytesIfNecessary((BYTE*)&work->Merkle[2], true);
    buf[5] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[1], true);
    buf[6] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[2], true);
    buf[7] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[3], true);
    buf[8] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[4], true);
    buf[9] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[5], true);
    buf[10] = SwapBytesIfNecessary((BYTE*)&work->MidState[0], true);
    buf[11] = SwapBytesIfNecessary((BYTE*)&work->MidState[1], true);
    buf[12] = SwapBytesIfNecessary((BYTE*)&work->MidState[2], true);
    buf[13] = SwapBytesIfNecessary((BYTE*)&work->MidState[3], true);
    buf[14] = SwapBytesIfNecessary((BYTE*)&work->MidState[4], true);
    buf[15] = SwapBytesIfNecessary((BYTE*)&work->MidState[5], true);
    buf[16] = SwapBytesIfNecessary((BYTE*)&work->MidState[6], true);
    buf[17] = SwapBytesIfNecessary((BYTE*)&work->MidState[7], true);
    buf[18] = SwapBytesIfNecessary((BYTE*)&work->PrecalcHashes[0], true);

}

WORKTASK taskCopy;

void AsicPrecalc_sha256_Compare(WORKTASK * pWork)
{
    int i;
    DWORD swapped;
    taskCopy.Device = pWork->Device;
    taskCopy.WorkID = pWork->WorkID;
    for(i = 0; i < 8; i++)
        taskCopy.MidState[i] = SwapBytesIfNecessary((BYTE*)&pWork->MidState[i], false);
    for(i = 0; i < 3; i++)
        taskCopy.Merkle[i] = SwapBytesIfNecessary((BYTE*)&pWork->Merkle[i], true);
    sha256_precalc(taskCopy.MidState, (BYTE*)taskCopy.Merkle, 12, taskCopy.PrecalcHashes);
    // swap bytes in precalc hashes
    for(i = 0; i < 6; i++)
    {
        swapped = SwapBytesIfNecessary((BYTE*)&taskCopy.PrecalcHashes[i], true);
        SYS_ASSERT((swapped == pWork->PrecalcHashes[i]), "OOPS outputs don't match");
    }
}

void DeQueueNextWork(DWORD *out)
{
    SYS_ASSERT((Status.WorkQC > 0), "No work queued");

    AsicPreCalc(&WorkQue[WorkNow]);

    if(appObject.testMode)
        AsicPrecalc_sha256_Compare(&WorkQue[WorkNow]);

    Status.WorkID = WorkQue[WorkNow].WorkID;

    //ArrangeWords4TxSequence(&taskCopy, out);
    ArrangeWords4TxSequence(&WorkQue[WorkNow], out);
    WorkNow = (WorkNow+1) & WORKMASK;
    Status.HashCount = 0;
    //TMR0 = HashTime;
    Status.State = 'W';
    Status.WorkQC--;
}

void PrepareWorkStatus(void)
{
    Status.ChipCount = ASIC_COUNT;
    Status.SlaveCount = 0; // no slave

    // pre-calc nonce range values
    BankSize = ASIC_COUNT;
    Status.MaxCount = WORK_TICKS / BankSize;

    NonceRanges[0] = 0;
    BYTE x;
    for(x = 1; x < BankSize; x++)
        NonceRanges[x] = NonceRanges[x-1] + DivisionOfLabor[1];

    Status.State = 'R';
    Status.HashCount = 0;
}

// we only remembrer the last four unique nonces
int cacheIndex = 0;
DWORD nonceCache[6];

bool IsNew(DWORD nonce)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        if (nonce == nonceCache[i])
            return false;
    }
    nonceCache[cacheIndex] = nonce;
    cacheIndex = (cacheIndex + 1) % 6;
}

int resultCount = 0;
DWORD firstNonce = 0;
DWORD resultArray[30];
DWORD resultWorkID[30];

int unfilteredCount = 0;
DWORD unfilteredNonces[40];
DWORD unfilteredWrkIDs[40];

// Note: third param unused (needed only for debugging)
void ResultRx(BYTE *indata, DWORD wrkID, DWORD *workDone)
{
    DWORD nonce = SwapBytesIfNecessary(indata, false);

    if (unfilteredCount < 40)
    {
        unfilteredNonces[unfilteredCount] = nonce;
        unfilteredWrkIDs[unfilteredCount] = wrkID;
    }
    unfilteredCount++;

    // filter out noise
    if (firstNonce == 0)
    {
        firstNonce = nonce;
        return; // reject very first nonce
    }
    if (!IsNew(nonce))
    {
        return;
    }
    
    if (resultCount < 30)
    {
        resultArray[resultCount] = nonce;
        resultWorkID[resultCount] = wrkID;
    }
    resultCount++;

    nonce -= 0xC0; // driver-klondike.c in cgminer also takes away 0xC0
    BYTE *noncePtr = (BYTE *)&nonce;

    Status.HashCount++;

    ResultQue[0] = '=';
    ResultQue[1] = USB_ID_1;
    ResultQue[2] = (BYTE)wrkID;
    ResultQue[3] = noncePtr[0];
    ResultQue[4] = noncePtr[1];
    ResultQue[5] = noncePtr[2];
    ResultQue[6] = noncePtr[3];

    SendCmdReply((char *)ResultQue, (BYTE *)(ResultQue+1), RESULT_SIZE-1);
}


void InitResultRx(void)
{
    ResultQC = 0;
    WorkNow = 0;
    appObject.transmitBufArea = 0;
    appObject.pullPoint = 0;
}



void InitializeCondominer(void)
{
    //replaced UserInit() call with the following two lines:
    InitResultRx();
    PrepareWorkStatus();

    SYS_TMR_CallbackPeriodic(10, &TraceTimer);

}//end InitializeSystem


