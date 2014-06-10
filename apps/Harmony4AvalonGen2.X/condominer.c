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
WORKTASK WorkQue[MAX_WORK_COUNT];
volatile BYTE ResultQue[8];
//DWORD ClockCfg[2] = { (((DWORD)DEFAULT_HASHCLOCK) << 18) | CLOCK_LOW_CHG, CLOCK_HIGH_CFG };
INT16 Step, Error, LastError;

DWORD NonceRanges[10];

const IDENTITY ID = {USB_ID_1, 2, "Swauk1", 0xA51C };

/*bank2*/ DWORD send32_data; // place in same bank as latc registers!
/*bank2*/ BYTE send32_count; // count DWORDS
/*bank2*/ BYTE last_bit0, last_bit1;

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

void ProcessCmd(char *cmd)
{
    // cmd is one char, dest address 1 byte, data follows
    // we already know address is ours here
    if (cmdIndex < 10)
        commandTrace[cmdIndex++] = cmd[0];
    switch(cmd[0]) {
        case 'W': // queue new work
            if( Status.WorkQC < MAX_WORK_COUNT ) {
                WORKTASK *work = &WorkQue[ (WorkNow + Status.WorkQC) & WORKMASK ];
                memcpy((BYTE *)work, cmd + 1, 4 * GEN2_INPUT_WORD_COUNT + 2);
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
            //HASH_CLK_EN = (cmd[2] == '1');
            Status.State = (cmd[2] == '1') ? 'R' : 'D';
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
    buf[0] = 0L; // for clock, to be set later
    buf[1] = 0L; // for clock, to be set later
    buf[2] = work->Merkle[0];
    buf[3] = work->Merkle[1];
    buf[4] = work->Merkle[2];
    buf[5] = work->PrecalcHashes[1];
    buf[6] = work->PrecalcHashes[2];
    buf[7] = work->PrecalcHashes[3];
    buf[8] = work->PrecalcHashes[4];
    buf[9] = work->PrecalcHashes[5];
    buf[10] = work->MidState[0];
    buf[11] = work->MidState[1];
    buf[12] = work->MidState[2];
    buf[13] = work->MidState[3];
    buf[14] = work->MidState[4];
    buf[15] = work->MidState[5];
    buf[16] = work->MidState[6];
    buf[17] = work->MidState[7];
    buf[18] = work->PrecalcHashes[0];

}

void DeQueueNextWork(DWORD *out)
{
    SYS_ASSERT((Status.WorkQC > 0), "No work queued");
    
    AsicPreCalc(&WorkQue[WorkNow]);
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

void ResultRx(DWORD nonce)
{
    if (resultCount < 10)
        resultArray[resultCount] = nonce;
    resultCount++;

    Status.HashCount++;

    if(Status.State == 'W') {
        ResultQue[0] = '=';
        ResultQue[1] = USB_ID_1;
        ResultQue[2] = Status.WorkID;
        // FIXME: deal with endianness
        ResultQue[3] = (BYTE)nonce;
        ResultQue[4] = (BYTE)(nonce >> 8);
        ResultQue[5] = (BYTE)(nonce >> 16);
        ResultQue[6] = (BYTE)(nonce >> 24);

        SendCmdReply((char *)ResultQue, (BYTE *)(ResultQue+1), sizeof(ResultQue)-1);
    }
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


