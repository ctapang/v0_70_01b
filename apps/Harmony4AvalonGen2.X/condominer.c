#include "GenericTypeDefs.h"
#include <xc.h>
#include "condominer.h"

#define USBGEN_EP_SIZE 1024
//#define IN_DATA_BUFFER_ADDRESS 0x2140
//#define OUT_DATA_BUFFER_ADDRESS 0x2190
//#define IN_DATA_BUFFER_ADDRESS_TAG @IN_DATA_BUFFER_ADDRESS
//#define OUT_DATA_BUFFER_ADDRESS_TAG @OUT_DATA_BUFFER_ADDRESS

unsigned char INPacket[USBGEN_EP_SIZE];      //User application buffer for sending IN packets to the host
unsigned char OUTPacket[USBGEN_EP_SIZE];    //User application buffer for receiving and holding OUT packets sent from the host

//USB_DEVICE_HANDLE USBGenericOutHandle;  //USB handle.  Must be initialized to 0 at startup.
//USB_DEVICE_HANDLE USBGenericInHandle;   //USB handle.  Must be initialized to 0 at startup.

unsigned char SlaveAddress = 0;

BYTE WQI, WQX;

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
volatile WORKSTATUS Status = {'I',0,0,0,0,0,0,0,0, WORK_TICKS, 0 };
WORKCFG Cfg = { 1500, 0, 0, 0, 0 };
WORKTASK WorkQue[MAX_WORK_COUNT];
volatile BYTE ResultQue[6];
//DWORD ClockCfg[2] = { (((DWORD)DEFAULT_HASHCLOCK) << 18) | CLOCK_LOW_CHG, CLOCK_HIGH_CFG };
INT16 Step, Error, LastError;

DWORD NonceRanges[10];

const IDENTITY ID = { 1, "Swauk1", 0xA51C };

DWORD PrecalcHashes[6];

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
    BYTE n;

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

        PrecalcHashes[2-n] = m[7-n];
        PrecalcHashes[5-n] = m[3-n];
    }
}

//#define R(a, b, c, d, e, f, g, h, w, k) \
//    h = h + (rotate(e, 26) ^ rotate(e, 21) ^ rotate(e, 7)) + (g ^ (e & (f ^ g))) + k + w; \
//    d = d + h; \
//    h = h + (rotate(a, 30) ^ rotate(a, 19) ^ rotate(a, 10)) + ((a & b) | (c & (a | b)))

/* this version uses too much stack and causes overflow
 * re-written above to be more flat and as first step to
 * assembly optimization
 *
DWORD rotate(DWORD x, BYTE y)
{
    return ((x<<y) | (x>>(32-y)));
}

void R1(DWORD *m, DWORD w, DWORD k)
{
    m[7] = m[7] + (rotate(m[4], 26) ^ rotate(m[4], 21) ^ rotate(m[4], 7)) + (m[6] ^ (m[4] & (m[5] ^ m[6]))) + k + w;
    m[3] = m[3] + m[7];
    m[7] = m[7] + (rotate(m[0], 30) ^ rotate(m[0], 19) ^ rotate(m[0], 10)) + ((m[0] & m[1]) | (m[2] & (m[0] | m[1])));
}

void R2(DWORD *m)
{
    DWORD hold = m[7];
    for(BYTE x=7; x > 0; x--)
        m[x] = m[x-1];
    m[0] = hold;
}

extern BYTE WorkNow;
extern WORKTASK WorkQue[MAX_WORK_COUNT];

DWORD precalc_hash[6];

void HasherPreCalc(void)
{
    const DWORD K[3] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf };
    DWORD m[8];
    BYTE n;
    for(n = 0; n < 8; n++)
        m[n] = WorkQue[WorkNow].MidState[n];

    R1(m, WorkQue[WorkNow].Merkle[0], K[0]);
    precalc_hash[0] = m[7];
    precalc_hash[3] = m[3];
    R2(m);
    R1(m, WorkQue[WorkNow].Merkle[1], K[1]);
    precalc_hash[1] = m[7];
    precalc_hash[4] = m[3];
    R2(m);
    R1(m, WorkQue[WorkNow].Merkle[2], K[2]);
    precalc_hash[2] = m[7];
    precalc_hash[5] = m[3];
}
*/

void SendCmdReply(char *cmd, BYTE *data, BYTE count)
{
    if(WQI*USB_RECORD_SIZE + count + 2 < USBGEN_EP_SIZE) {
        INPacket[WQI*USB_RECORD_SIZE] = cmd[0];
        INPacket[WQI*USB_RECORD_SIZE + 1] = SlaveAddress;
        BYTE n;
        for(n = 0; n < count; n++)
            INPacket[WQI*USB_RECORD_SIZE + n + 2] = data[n];
        WQI = (WQI+1) & 3;
    }
}

void ProcessCmd(char *cmd)
{
    // cmd is one char, dest address 1 byte, data follows
    // we already know address is ours here
    switch(cmd[0]) {
        case 'W': // queue new work
            if( Status.WorkQC < MAX_WORK_COUNT-1 ) {
                WorkQue[ (WorkNow + Status.WorkQC++) & WORKMASK ] = *(WORKTASK *)(cmd+2);
                if(Status.State == 'R') {
                    AssembleWorkForAsics();
                }
            }
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'A': // abort work, reply status has hash completed count
            Status.WorkQC = WorkNow = 0;
            Status.State = 'R';
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'I': // return identity 
            SendCmdReply(cmd, (char *)&ID, sizeof(ID));
            break;
        case 'S': // return status 
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
            Status.Noise = Status.ErrorCount = 0;
            break;
        case 'C': // set config values 
            if( *(WORD *)&cmd[2] != 0 )
                Cfg = *(WORKCFG *)(cmd+2);
            SendCmdReply(cmd, (char *)&Cfg, sizeof(Cfg));
            break;
        case 'E': // enable/disable work
            //HASH_CLK_EN = (cmd[2] == '1');
            Status.State = (cmd[2] == '1') ? 'R' : 'D';
            SendCmdReply(cmd, (char *)&Status, sizeof(Status));
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

WORKTASK *AssembleWorkForAsics(void)
{
    AsicPreCalc(&WorkQue[WorkNow]);
    Status.WorkID = WorkQue[WorkNow].WorkID;
    //SendAsicData(&WorkQue[WorkNow]);
    WORKTASK *retVal = &WorkQue[WorkNow];
    WorkNow = (WorkNow+1) & WORKMASK;
    Status.HashCount = 0;
    //TMR0 = HashTime;
    Status.State = 'W';
    Status.WorkQC--;
    return retVal;
}

void PrepareWorkStatus(void)
{
    Status.ChipCount = 10;

    // pre-calc nonce range values
    BankSize = 10;
    Status.MaxCount = WORK_TICKS / BankSize / 2;

    NonceRanges[0] = 0;
    BYTE x;
    for(x = 1; x < BankSize; x++)
        NonceRanges[x] = NonceRanges[x-1] + DivisionOfLabor[1];

    Status.State = 'R';
    Status.HashCount = 0;
}


void ResultRx(BYTE *nonce)
{
    if(Status.State == 'W') {
        ResultQue[0] = '=';
        ResultQue[1] = Status.WorkID;

        // FIXME: deal with endianness
        memcpy(&ResultQue + 2, nonce, sizeof(DWORD));
        SendCmdReply((char *)ResultQue, (BYTE *)(ResultQue+1), sizeof(ResultQue)-1);
    }
}


void InitResultRx(void)
{
    ResultQC = 0;
    //TXSTAbits.SYNC = 1;
    //RCSTAbits.SPEN = 1;
    //TXSTAbits.CSRC = 0;
    //BAUDCONbits.SCKP = 0;
    //BAUDCONbits.BRG16 = 1;
    //ANSELBbits.ANSB5 = 0;
    //IOCBPbits.IOCBP7 = 1;
    //INTCONbits.IOCIE = 1;
    //IOCBF = 0;
    //INTCONbits.GIE = 1;
    //RCSTAbits.CREN = 1;
    //RCREG = 0xFF;
}

void ProcessIO();


int mainProgram(void)
{   
    InitializeWorkSystem();

    while(1)
    {
        #if defined(USB_INTERRUPT)
            //if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
            //{
                USBDeviceAttach();              
            //}
        #endif

        /*if(USBDeviceState < CONFIGURED_STATE) {
            if(!I2CState.Slave)
                InitI2CSlave();
            }
        else if(!I2CState.Master)
            InitI2CMaster();*/

        #if defined(USB_POLLING)
    // Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
                          // this function periodically.  This function will take care
                          // of processing and responding to SETUP transactions 
                          // (such as during the enumeration process when you first
                          // plug in).  USB hosts require that USB devices should accept
                          // and process SETUP packets in a timely fashion.  Therefore,
                          // when using polling, this function should be called 
                          // regularly (such as once every 1.8ms or faster** [see 
                          // inline code comments in usb_device.c for explanation when
                          // "or faster" applies])  In most cases, the USBDeviceTasks() 
                          // function does not take very long to execute (ex: <100 
                          // instruction cycles) before it returns.
        #endif
        
        //if(TMR0IF)
        //    WorkTick();

        if(Status.State == 'P'){
            AssembleWorkForAsics();
        }
                      
        ProcessIO();
              
    }//end while
}//end main

void InitializeWorkSystem(void)
{
    // all pins digital mode, except RC2, which has a Thermistor on it
    ANSELA = 0x00;
    ANSELB = 0x00;
    //ANSELC = 0x04;

    //USBGenericOutHandle = 0;
    //USBGenericInHandle = 0;
    WQI = WQX = 0;
    
    //replaced UserInit() call with the following two lines:
    InitResultRx();
    PrepareWorkStatus();

    //USBDeviceInit();    //usb_device.c.  Initializes USB module SFRs and firmware
                        //variables to known states.
}//end InitializeSystem


void ProcessIO(void)
{   
  
    //if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    /*if(USBGetDeviceState() == DETACHED_STATE) {
        if(I2CCount > 0) {
            ProcessCmd(OUTPacket);
            I2CCount = 0;
            }
    }
    else
    if(!USBHandleBusy(USBGenericOutHandle)) {
        //if( OUTPacket[1] != MASTER_ADDRESS )
        //    I2CRelay(OUTPacket, USBGEN_EP_SIZE);
        //else
        ProcessCmd(OUTPacket);
        USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM, (BYTE*)&OUTPacket, USBGEN_EP_SIZE);
    }

    if(WQI != WQX && !USBHandleBusy(USBGenericInHandle)) {
        //USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM, (BYTE*)&INPacket[WQX*USB_RECORD_SIZE], USB_RECORD_SIZE);
        WQX = (WQX+1) & 3;
    } */
} //end ProcessIO
