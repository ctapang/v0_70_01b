#define MAX_WORK_COUNT      4   // must be binary multiple and match driver
#define WORKMASK            MAX_WORK_COUNT-1
#define USB_RECORD_SIZE     15

// set values for ASIC PLL, we use R=16 N=Freq in MHz
#define WORK_TICKS          16384   // 2^32 total / 2^18 hashes per tick
#define TICK_TOTAL          12284   // 2^18 / 21.33uS TMR0 period (adjusted down for push time)
#define CLOCK_R_VALUE       16
#define DEFAULT_HASHCLOCK   333
#define CLOCK_NOCHG_MASK    0x00000002
#define CLOCK_LOW_CHG       0x00030007
#define CLOCK_HALF_CHG      0x00030017
#define CLOCK_HIGH_CFG      0x00000172
#define MIN_HASH_CLOCK      128
#define HALF_HASH_CLOCK     250
#define MAX_HASH_CLOCK      450

// default temp values
#define DEFAULT_TEMP_TARGET     143 // default temperature to hold by adjusting fan speed
#define DEFAULT_TEMP_CRITICAL   80  // critical temp (not decided what to do in this case - probably disable clock, disable usb enable cmd and wait for cooldown)

#define DATA_SPLIT  0x50

typedef struct _id {
    BYTE version;
    char product[7];    
    DWORD serial;
} IDENTITY;

const IDENTITY ID = { 1, "Swauk1", 0xA51C };

typedef struct _workstatus {
    BYTE State;
    BYTE ChipCount;
    BYTE SlaveCount;
    BYTE WorkQC;
    BYTE WorkID;
    BYTE Temp;
    BYTE FanSpeed;
    BYTE ErrorCount;
    WORD HashCount, MaxCount;
    BYTE Noise;
} WORKSTATUS;

typedef struct _workcfg {
    WORD HashClock;
    BYTE TempTarget, Future1;
    BYTE Future2, Future3;
} WORKCFG;

typedef struct _worktask {
    BYTE WorkID;
    DWORD MidState[8];
    DWORD Merkle[3];
} WORKTASK;


void ProcessCmd(char *cmd);
void AsicPushWork(void);

void DetectAsics(void);

void ResultRx(void);
void WorkTick(void);

void InitTempSensor(void);
void InitWorkTick(void);
void InitResultRx(void);

void SendAsicData(WORKTASK *work);
void Send32(void);
void AsicPreCalc(WORKTASK *work);

void SendCmdReply(char *cmd, BYTE *ReplyBuf, BYTE count);