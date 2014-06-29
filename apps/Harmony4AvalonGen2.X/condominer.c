#include "GenericTypeDefs.h"
#include <xc.h>
#include "condominer.h"
#include "app.h"


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
volatile WORKSTATUS Status = {USB_ID_1,'I',0,0,0,0,0,0,0, (WORD)0, WORK_TICKS, 0 };
volatile WORKRESULT WResult = {USB_ID_1, 0, 0L};
WORKCFG Cfg = { USB_ID_1, 1500, 0, 0, 0, 0 };
WORKTASK *pWork;
WORKTASK alternatePreCalcCopy;
WORKTASK WorkQue[MAX_WORK_COUNT];
volatile BYTE ResultQue[8];
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


void SendCmdReply(char *cmd, BYTE *data, BYTE count)
{
    appObject.bTransmitBufArea = !appObject.bTransmitBufArea;
    int bufIndex = appObject.bTransmitBufArea ? appObject.txBufSize : 0;

    SYS_ASSERT(((count + 1) <= appObject.txBufSize), "size to transmit too large");

    appObject.transmitDataBuffer[bufIndex] = cmd[0];
    //appObject.transmitDataBuffer[bufIndex + 1] = data[0]; // USB_ID_1
    memcpy(appObject.transmitDataBuffer + bufIndex + 1, data, count);

    /* Send the data to the host */

    appObject.epDataWritePending = true;

    USB_DEVICE_GENERIC_EndpointWrite
            ( USB_DEVICE_GENERIC_INDEX_0,
            ( USB_DEVICE_GENERIC_TRANSFER_HANDLE *)&appObject.writeTranferHandle,
            appObject.endpointTx, &appObject.transmitDataBuffer[bufIndex],
            appObject.txBufSize,
            USB_DEVICE_GENERIC_TRANSFER_FLAG_NONE );
}

char commandTrace[10];
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

void ProcessCmd(char *cmd)
{
    // cmd is one char, dest address 1 byte, data follows
    // we already know address is ours here
    if (cmdIndex < 10)
        commandTrace[cmdIndex++] = cmd[0];
    switch(cmd[0]) {
        case 'W': // queue new work
            if( Status.WorkQC < MAX_WORK_COUNT && Status.State != 'D' ) {
                WORKTASK *work = &WorkQue[ (WorkNow + Status.WorkQC) & WORKMASK ];
                work->Device = cmd[1];
                work->WorkID = cmd[2];
                // cmd input is little-endian, and we are also little-endian
                for (i = 0; i < 8; i++)
                    work->MidState[i] = SwapBytesIfNecessary(cmd + 4*i + 3, false);
                for (i = 0; i < 3; i++)
                    work->Merkle[i] = SwapBytesIfNecessary(cmd + 4*i + 35, false);
                if(Status.State == 'R') {
                    Status.State = 'P'; // AssembleWorkForAsics(out);
                }
                Status.WorkQC++;
            }
            SendCmdReply(cmd, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'A': // abort work, reply status has hash completed count
            Status.WorkQC = 0;
            Status.State = 'R';
            SendCmdReply(cmd, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            Reset_All_Avalon_Chips();
            break;
        case 'I': // return identity 
            SendCmdReply(cmd, (char *)&ID, 13); // sizeof(ID));
            break;
        case 'S': // return status 
            SendCmdReply(cmd, (char *)&Status, 14); // sizeof(WORKSTATUS));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'C': // set config values 
            if( *(WORD *)&cmd[2] != 0 )
            {
                //Cfg = *(WORKCFG *)(cmd+2);
                Cfg.Device = cmd[1];
                Cfg.HashClock = cmd[2];
                Cfg.HashClock += ((WORD)cmd[3]) << 8;
                Cfg.TempTarget = cmd[4];
                Cfg.Future1 = cmd[5];
                Cfg.Future2 = cmd[6];
                Cfg.Future3 = cmd[7];
            }
            SendCmdReply(cmd, (char *)&Cfg, sizeof(Cfg));
            break;
        case 'E': // enable/disable work
            Status.State = (cmd[2] == '1') ? ((Status.WorkQC > 0) ? 'P' : 'R') : 'D';
            SendCmdReply(cmd, (char *)&Status, 14); // sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        //case 'F': // enter firmware update mode
        //    for(BYTE n = 0; n < sizeof(FwPwd); n++)
	//	if(FwPwd[n] != cmd[2+n])
        //            return;
        //    UpdateFirmware();
        //    break;
        default:
            break;
        }
    //LED_On();
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

void DeQueueNextWork(DWORD *out)
{
    SYS_ASSERT((Status.WorkQC > 0), "No work queued");

#ifdef USE_SHA256
    pWork = &WorkQue[WorkNow];
    sha256_precalc((uint8_t *)pWork->MidState, (uint8_t *)pWork->Merkle, 3, pWork->PrecalcHashes);
#else
    AsicPreCalc(&WorkQue[WorkNow]);
#endif
    Status.WorkID = WorkQue[WorkNow].WorkID;
    //SendAsicData(&WorkQue[WorkNow]);
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

int resultCount = 0;
DWORD resultArray[10];
DWORD resultWorkID[10];

void ResultRx(BYTE *indata, DWORD wrkID)
{
    DWORD nonce = SwapBytesIfNecessary(indata, false);
    if (resultCount < 10)
    {
        resultArray[resultCount] = nonce;
        resultWorkID[resultCount] = wrkID;
    }
    resultCount++;

    Status.HashCount++;

    ResultQue[0] = '=';
    ResultQue[1] = USB_ID_1;
    ResultQue[2] = (BYTE)wrkID;
    ResultQue[3] = indata[0];
    ResultQue[4] = indata[1];
    ResultQue[5] = indata[2];
    ResultQue[6] = indata[3];

    SendCmdReply((char *)ResultQue, (BYTE *)(ResultQue+1), sizeof(ResultQue)-1);
}


void InitResultRx(void)
{
    ResultQC = 0;
}



void InitializeWorkSystem(void)
{
    // all pins digital mode, except RC2, which has a Thermistor on it
    ANSELA = 0x00;
    ANSELB = 0x00;
    //ANSELC = 0x04;

    
    //replaced UserInit() call with the following two lines:
    InitResultRx();
    PrepareWorkStatus();

}//end InitializeSystem


