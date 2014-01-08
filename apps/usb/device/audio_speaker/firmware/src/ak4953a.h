
#include <xc.h>
#include <stdlib.h>
#include <GenericTypeDefs.h>
#include "peripheral/dma/plib_dma.h"
#include "peripheral/spi/plib_spi.h"
#include "peripheral/int/plib_int.h"

#ifndef GetPeripheralClock
#define GetPeripheralClock() 					40000000
#endif

#define BUFFER_DEPTH                        1
#define PINGPONG_DEPTH                      (BUFFER_DEPTH<<1)
#define AK4953A_TX_BUFFER_SIZE_STEREO_WORD  (48*PINGPONG_DEPTH)
#define AK4953A_RX_BUFFER_SIZE_STEREO_WORD  (48*PINGPONG_DEPTH)
#define AK4953A_TX_BUFFER_SIZE_BYTES        (AK4953A_TX_BUFFER_SIZE_STEREO_WORD * sizeof(UINT32))
#define AK4953A_RX_BUFFER_SIZE_BYTES        (AK4953A_RX_BUFFER_SIZE_STEREO_WORD * sizeof(UINT32))
#define DMA_PP_BUFFER_SIZE                  (AK4953A_TX_BUFFER_SIZE_STEREO_WORD>>1)

#define AK4953A_I2C_ADDRESS                 0x24
#define CODEC_SUB_ADDRESS                   0x00
#define DUMMY_BYTE                          0x00
#define AK4953A_I2C_MODULE                  I2C_ID_2
#define AK4953A_I2C_BAUD                    100000

#define AK4953A_SPI_MODULE                  SPI_ID_1	//SPI_CHANNEL1
#define AK4953A_SPI_MODULE_BUFFER     	    SPI1BUF
#define AK4953A_SPI_MODULE_TX_IRQ     	    _SPI1_TX_IRQ
#define AK4953A_SPI_MODULE_RX_IRQ     	    _SPI1_RX_IRQ
                                                
#define AK4953A_SPI_TX_DMA_CHANNEL          DMA_CHANNEL_0
#define AK4953A_SPI_TX_DMA_VECTOR           INT_VECTOR_DMA0
#define AK4953A_SPI_TX_DMA_INTERRUPT        INT_SOURCE_DMA_0
#define AK4953A_SPI_TX_DMA_INT_PRI_LEVEL    INT_PRIORITY_LEVEL5
#define AK4953A_SPI_TX_DMA_INT_SPRI_LEVEL   INT_SUBPRIORITY_LEVEL1
                                                
#define AK4953A_SPI_RX_DMA_CHANNEL    	    DMA_CHANNEL_1
#define AK4953A_SPI_RX_DMA_VECTOR           INT_VECTOR_DMA1
#define AK4953A_SPI_RX_DMA_INTERRUPT        INT_SOURCE_DMA_1
#define AK4953A_SPI_RX_DMA_INT_PRI_LEVEL    INT_PRIORITY_LEVEL5
#define AK4953A_SPI_RX_DMA_INT_SPRI_LEVEL   INT_SUBPRIORITY_LEVEL1

#define I2S_SAMPLERATE_INIT                 48000
#define I2S_MCLK_SOURCE                     (200000000ul)
#define I2C_PBCLK_SOURCE                    (I2S_MCLK_SOURCE/2)
#define I2S_MCLK_RATIO                      256
#define I2S_FRAME_RATIO                     32

#define I2S_MCLK_RODIV(source, rate, ratio) ((source / rate / (ratio << 1)) << 16)
#define I2S_MCLK_ROTRIM(source, rate, ratio)(((source / rate) & ((ratio << 1)-1)) << 23);

// Reference Oscillator Source Select bits - values are mutually exclusive
#define OSC_REFOCON_SYSPLL                  (7)
#define OSC_REFOCON_SOSC                    (5)
#define OSC_REFOCON_LPRC                    (4)
#define OSC_REFOCON_FRC                     (3)
#define OSC_REFOCON_POSC                    (2)
#define OSC_REFOCON_PBCLK                   (1)
#define OSC_REFOCON_SYSCLK                  (0)

#define PBCLK_DIV_4                         (3 << _PB2DIV_PBDIV_POSITION)
#define I2C_BAUD_SET(baudRate)              (((1/2*(uint32_t)baudRate)*I2C_PBCLK_SOURCE)-2)

typedef enum{
    O_RD,   
    O_WR,   
    O_RDWR,      
}OPEN_MODE;

typedef enum{
	PP_BUFF0,
	PP_BUFF1,
	PP_BUFFN
}PINGPONG_BUFFN;

typedef enum{
DEC_TUNE=0,INC_TUNE,
} TUNE_STEP;

typedef union{
    struct{
        INT16 rightChannel;
        INT16 leftChannel;
    };
    UINT32 audioWord;
}AudioStereo;

typedef struct __AK4953A_state{
    AudioStereo		*txBuffer;
    AudioStereo		*rxBuffer;
    volatile PINGPONG_BUFFN	activeRxBuffer;
    volatile BOOL		statusRxBuffer[PP_BUFFN];
    volatile UINT		countRxBuffer[PP_BUFFN];
    volatile PINGPONG_BUFFN	activeTxBuffer;
    volatile BOOL		statusTxBuffer[PP_BUFFN];
    volatile UINT		countTxBuffer[PP_BUFFN];

    volatile UINT/*float*/ 	frameSize;    
    volatile UINT 		bufferSize;
    volatile UINT 		underrunCount;
    volatile UINT 		overrunCount;
    volatile UINT 		underrunLimit;
    volatile UINT 		overrunLimit;
    volatile INT 		pllkValue;
    volatile INT 		pllkTune;
    volatile INT		pllkTuneLimit;
    volatile UINT32 		masterClk;
    volatile UINT32		samplingFreq;

} AK4953AState;

typedef enum{
								
	AK4953A_REG_PWR_MGMT1=0,	//0		<--
	AK4953A_REG_PWR_MGMT2,		//1
	AK4953A_REG_SIG_SLCT1,		//2
	AK4953A_REG_SIG_SLCT2,		//3
        AK4953A_REG_SIG_SLCT3,		//4
	AK4953A_REG_MODE_CTRL1,		//5
	AK4953A_REG_MODE_CTRL2,		//6
        AK4953A_REG_MODE_CTRL3,		//7
        AK4953A_REG_DIG_MIC,            //8
	AK4953A_REG_TMR_SLCT,		//9
        AK4953A_REG_ALC_TMR_SLCT,       //A
        AK4953A_REG_ALC_MODE_CTRL1,     //B
	AK4953A_REG_ALC_MODE_CTRL2,	//C
        AK4953A_REG_ALC_MODE_CTRL3,	//D
        AK4953A_REG_ALC_VLM,            //E
	AK4953A_REG_LIN_VOL_CTRL,       //F
        AK4953A_REG_RIN_VOL_CTRL,       //10
        AK4953A_REG_LOP_VOL_CTRL,       //11
        AK4953A_REG_ROP_VOL_CTRL,       //12
        AK4953A_REG_LDIG_VOL_CTRL,       //13
        AK4953A_REG_RDIG_VOL_CTRL,       //14
	AK4953A_REG_BEEP_FREQ,          //15
	AK4953A_REG_BEEP_ON_TIME,       //16
	AK4953A_REG_BEEP_OFF_TIME,      //17
	AK4953A_REG_BEEP_RPT_CNT,       //18
	AK4953A_REG_BEEP_VLM_CTRL,	//19
	AK4953A_REG_DFLTR_SLCT_1,       //1C
	AK4953A_REG_DFLTR_MODE,         //1D
	AK4953A_REG_HPF2_0_SET,         //1E
        AK4953A_REG_HPF2_1_SET,   	//1F
        AK4953A_REG_HPF2_2_SET,   	//20
        AK4953A_REG_HPF2_3_SET,   	//21
        AK4953A_REG_LPF_0_SET,   	//22
        AK4953A_REG_LPF_1_SET,   	//23
        AK4953A_REG_LPF_2_SET,   	//24
        AK4953A_REG_LPF_3_SET,   	//25
        AK4953A_REG_DFLTR_SLCT_2,       //30
        AK4953A_REG_E1_0_SET,            //32
        AK4953A_REG_E1_1_SET,            //33
        AK4953A_REG_E1_2_SET,            //34
        AK4953A_REG_E1_3_SET,            //35
        AK4953A_REG_E1_4_SET,            //36
        AK4953A_REG_E1_5_SET,            //37
        AK4953A_REG_E2_0_SET,            //38
        AK4953A_REG_E2_1_SET,            //39
        AK4953A_REG_E2_2_SET,            //3A
        AK4953A_REG_E2_3_SET,            //3B
        AK4953A_REG_E2_4_SET,            //3C
        AK4953A_REG_E2_5_SET,            //3D
        AK4953A_REG_E3_0_SET,            //3E
        AK4953A_REG_E3_1_SET,            //3F
        AK4953A_REG_E3_2_SET,            //40
        AK4953A_REG_E3_3_SET,            //41
        AK4953A_REG_E3_4_SET,            //42
        AK4953A_REG_E3_5_SET,            //43
        AK4953A_REG_E4_0_SET,            //44
        AK4953A_REG_E4_1_SET,            //45
        AK4953A_REG_E4_2_SET,            //46
        AK4953A_REG_E4_3_SET,            //47
        AK4953A_REG_E4_4_SET,            //48
        AK4953A_REG_E4_5_SET,            //49
        AK4953A_REG_E5_0_SET,            //4A
        AK4953A_REG_E5_1_SET,            //4B
        AK4953A_REG_E5_2_SET,            //4C
        AK4953A_REG_E5_3_SET,            //4D
        AK4953A_REG_E5_4_SET,            //4E
        AK4953A_REG_E5_5_SET,            //4F
	
}AK4953A_REGISTER;

typedef enum{
    SAMPLERATE_48000HZ,
    SAMPLERATE_44100HZ,
    SAMPLERATE_32000HZ,
    SAMPLERATE_24000HZ,
    SAMPLERATE_16000HZ,
    SAMPLERATE_8000HZ,
    SAMPLERATE_PERSIST    
}AK4953A_SAMPLERATE;


/* Register bit fields. */
//Register Name: Power Management 1
#define PWRMGMT1_PMADL_UP    	(1 << 0)
#define PWRMGMT1_PMADR_UP	(1 << 1)
#define PWRMGMT1_PMDAC_UP	(1 << 2)
#define PWRMGMT1_LSV_UP         (1 << 3)
#define PWRMGMT1_PMSPK_UP	(1 << 4)
#define PWRMGMT1_PMBP_UP	(1 << 5)
#define PWRMGMT1_PMVCM_UP	(1 << 6)
#define PWRMGMT1_PMPFIL_UP	(1 << 7)

//Register Name: Power Management 2
#define PWRMGMT2_PMPLL	    (1 << 0)
#define PWRMGMT2_MCKO	    (1 << 1)
#define PWRMGMT2_MS_MASTER  (1 << 3)
#define PWRMGMT2_PMHPR_UP   (1 << 4)
#define PWRMGMT2_PMHPL_UP   (1 << 5)

//Register Name: Signal Select 1
#define SIGSLCT1_MGAIN0_SET		(1 << 0)
#define SIGSLCT1_MGAIN1_SET		(1 << 1)
#define SIGSLCT1_MGAIN2_SET		(1 << 2)
#define SIGSLCT1_PMMP_UP		(1 << 3)
#define SIGSLCT1_MPSEL_UP		(1 << 4)
#define SIGSLCT1_DACS_ON		(1 << 5)
#define SIGSLCT1_SPPSN_UP		(1 << 7)

//Register Name: Signal Select 2
#define SIGSLCT2_INL0_ON		(1 << 0)
#define SIGSLCT2_INR0_ON		(1 << 1)
#define SIGSLCT2_INL1_ON		(1 << 2)
#define SIGSLCT2_INR1_ON		(1 << 3)
#define SIGSLCT2_SPKG0_ON               (1 << 6)
#define SIGSLCT2_SPKG1_ON               (1 << 7)


//Register Name: Signal Select 3
#define SIGSLCT3_HPM_UP		(1 << 2)
#define SIGSLCT3_MOFF_UP        (1 << 3)
#define SIGSLCT3_PTS0_UP        (1 << 4)
#define SIGSLCT3_PTS1_UP	(1 << 5)

//Register Name: Mode Control 1
#define MODECTRL1_DIF0_UP       (1 << 0)
#define MODECTRL1_DIF1_UP       (1 << 1)
#define MODECTRL1_HPZ_UP        (1 << 2)
#define MODECTRL1_BCK0_UP       (1 << 3)
#define MODECTRL1_PLL0_UP       (1 << 4)
#define MODECTRL1_PLL1_UP       (1 << 5)
#define MODECTRL1_PLL2_UP       (1 << 6)
#define MODECTRL1_PLL3_UP       (1 << 7)

//Register Name: Mode Control 2
#define MODECTRL2_FS0_UP       (1 << 0)
#define MODECTRL2_FS1_UP       (1 << 1)
#define MODECTRL2_FS2_UP        (1 << 2)
#define MODECTRL2_FS3_UP       (1 << 3)
#define MODECTRL2_DS_UP       (1 << 4)
#define MODECTRL2_CPCK_UP       (1 << 5)
#define MODECTRL2_PS0_UP       (1 << 6)
#define MODECTRL2_PS1_UP       (1 << 7)

//Register Name: Mode Control 3
#define MODECTRL2_DEM0_UP       (1 << 0)
#define MODECTRL2_DEM1_UP       (1 << 1)
#define MODECTRL2_IVOLC_UP        (1 << 2)
#define MODECTRL2_OVOLC_UP       (1 << 3)
#define MODECTRL2_DVOLC_UP       (1 << 4)
#define MODECTRL2_SMUTE_UP       (1 << 5)
#define MODECTRL2_THDET_UP       (1 << 6)
#define MODECTRL2_READ_UP       (1 << 7)

//Register Name: Timer Select
#define TMRSLCT_DVTM0_UP	(1 << 0)
#define TMRSLCT_DVTM1_UP	(1 << 01
#define TMRSLCT_ADRST0		(2 << 0)
#define TMRSLCT_AFRST1		(0 << 2)
#define TMRSLCT_WTM_256FS		(1 << 2)
#define TMRSLCT_WTM_512FS		(2 << 2)
#define TMRSLCT_WTM_1024FS		(3 << 2)
#define TMRSLCT_WTM_2048FS		(16 << 2)
#define TMRSLCT_WTM_4096FS		(17 << 2)
#define TMRSLCT_WTM_8192FS		(18 << 2)
#define TMRSLCT_WTM_16384FS		(19 << 2)
#define TMRSLCT_ZTM_128FS		(0 << 4)
#define TMRSLCT_ZTM_256FS		(1 << 4)
#define TMRSLCT_ZTM_512FS		(2 << 4)
#define TMRSLCT_ZTM_1024FS		(3 << 4)
#define TMRSLCT_DVTM_256FS		(1 << 7)

#define ALCCTRL1_LMTH0_SET		(1 << 0)
#define ALCCTRL1_RGAIN0_SET		(1 << 1)
#define ALCCTRL1_LMAT_0P375		(0 << 2)
#define ALCCTRL1_LMAT_0P750		(1 << 2)
#define ALCCTRL1_LMAT_1P125		(2 << 2)
#define ALCCTRL1_LMAT_1P500		(3 << 2)
#define ALCCTRL1_ZELMN_DISABLE	(1 << 4)
#define ALCCTRL1_ALC_ENABLE		(1 << 5)

#define ALCCTRL2_REF(n)			(n)

#define LINPGAGAIN_IVL(n)		(n)
#define RINPGAGAIN_IVL(n)		(n)

#define LDACVOL_DVL(n)			(n)
#define RDACVOL_DVL(n)			(n)

#define ALCCTRL3_VBAT_0P64AVDD	(1 << 1)
#define ALCCTRL3_LMTH1_SET		(1 << 6)
#define ALCCTRL3_RGAIN1_SET		(1 << 7)

#define MODECTRL3_DEM_44K1HZ	(0 << 0)
#define MODECTRL3_DEM_OFF		(1 << 0)
#define MODECTRL3_DEM_48KHZ		(2 << 0)
#define MODECTRL3_DEM_32KHZ		(3 << 0)
#define MODECTRL3_BST_OFF		(0 << 2)
#define MODECTRL3_BST_MIN		(1 << 2)
#define MODECTRL3_BST_MID		(2 << 2)
#define MODECTRL3_BST_MAX		(3 << 2)
#define MODECTRL3_DVOLC_DEP		(1 << 4)
#define MODECTRL3_SMUTE_ENABLE	(1 << 5)
#define MODECTRL3_LOOP_ENABLE	(1 << 6)

#define MODECTRL4_DAC_ON		(1 << 0)
#define MODECTRL4_MINH_ON		(1 << 1)
#define MODECTRL4_HPM_MONO		(1 << 2)
#define MODECTRL4_IVOLC_DEP		(1 << 3)

#define PWRMGMT3_PMADR_UP	    (1 << 0)
#define PWRMGMT3_INL0_SET	    (1 << 1)
#define PWRMGMT3_INR0_SET	    (1 << 2)
#define PWRMGMT3_MDIF1_DIFFIN   (1 << 3)
#define PWRMGMT3_MDIF2_DIFFIN   (1 << 4)
#define PWRMGMT3_HPG_3P6DB	    (1 << 5)
#define PWRMGMT3_INL1_SET	    (1 << 6)
#define PWRMGMT3_INR1_SET	    (1 << 7)

#define DFLTRSLCT_FIL3_ENABLE	(1 << 2)
#define DFLTRSLCT_EQ_ENABLE		(1 << 3)
#define DFLTRSLCT_FIL1_ENABLE	(1 << 4)
#define DFLTRSLCT_GN_0DB		(0 << 6)
#define DFLTRSLCT_GN_12DB		(1 << 6)
#define DFLTRSLCT_GN_24DB		(2 << 6)


#define FLTR30SET_F3A(nA)		(0xFF & nA)
#define FLTR31SET_F3A(nA)		((0x3F00 & nA) >> 8)
#define FLTR31SET_F3AS_LPF		(1 << 7)
#define FLTR32SET_F3B(nB)		(0xFF & nB)
#define FLTR33SET_F3B(nB)		((0x3F00 & nB) >> 8)
#define EQ0SET_EQA(nA)			(0xFF & nA)	
#define EQ1SET_EQA(nA)			((0xFF00 & nA) >> 8)
#define EQ2SET_EQB(nB)			(0xFF & nB)
#define EQ3SET_EQB(nB)			((0x3F00 & nB) >> 8)
#define EQ4SET_EQC(nC)			(0xFF & nC)	
#define EQ5SET_EQC(nC)			((0xFF00 & nC) >> 8)
#define FLTR10SET_F1A(nA)		(0xFF & nA)
#define FLTR11SET_F1A(nA)		((0x3F00 & nA) >> 8)
#define FLTR11SET_F1AS_LPF		(1 << 7)
#define FLTR12SET_F1B(nB)		(0xFF & nB)
#define FLTR13SET_F1B(nB)		((0x3F00 & nB) >> 8)


#define PWRMGMT4_PMMICL_UP	    (1 << 0)
#define PWRMGMT4_PMMICR_UP	    (1 << 1)
#define PWRMGMT4_PMAINL2_UP	    (1 << 2)
#define PWRMGMT4_PMAINR2_UP	    (1 << 3)
#define PWRMGMT4_PMAINL3_UP	    (1 << 4)
#define PWRMGMT4_PMAINR3_UP	    (1 << 5)
#define PWRMGMT4_PMAINL4_UP	    (1 << 6)
#define PWRMGMT4_PMAINR4_UP	    (1 << 7)

#define MODECTRL5_LODIF_DIFFOUT	(1 << 0)
#define MODECTRL5_AIN3_STEREOIN	(1 << 1)
#define MODECTRL5_MIX_MONO		(1 << 2)
#define MODECTRL5_L4DIF_DIFFIN	(1 << 3)
#define MODECTRL5_MICL3_MICAMP	(1 << 4)
#define MODECTRL5_MICR3_MICAMP	(1 << 5)

#define OUTMIXERCTRL_LINL2_ON	(1 << 0)
#define OUTMIXERCTRL_RINL2_ON	(1 << 1)
#define OUTMIXERCTRL_LINL3_ON	(1 << 2)
#define OUTMIXERCTRL_RINL3_ON	(1 << 3)
#define OUTMIXERCTRL_LINL4_ON	(1 << 4)
#define OUTMIXERCTRL_RINL4_ON	(1 << 5)
#define OUTMIXERCTRL_LOM3_MONO	(1 << 6)
#define OUTMIXERCTRL_LOM_MONO	(1 << 7)

#define HPMIXERCTRL_LINH2_ON	(1 << 0)		
#define HPMIXERCTRL_RINH2_ON	(1 << 1)
#define HPMIXERCTRL_LINH3_ON	(1 << 2)		
#define HPMIXERCTRL_RINH3_ON	(1 << 3)
#define HPMIXERCTRL_LINH4_ON	(1 << 4)		
#define HPMIXERCTRL_RINH4_ON	(1 << 5)
#define HPMIXERCTRL_HPM3_MONO	(1 << 6)		

extern AK4953AState* pCodecHandle;

void AK4953AInit(void);
UINT AK4953AWrite(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples);
UINT AK4953ARead(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples);
AK4953AState* AK4953AOpen(OPEN_MODE mode);
INT AK4953ASetDACVolume(AK4953AState* pCodecHandle, BYTE volumeDAC);
void AK4953AAdjustSampleRateTx(AK4953AState* pCodecHandle);
INT AK4953ASetSampleRate(AK4953AState* pCodecHandle, AK4953A_SAMPLERATE sampleRate);
void AK4953AStartAudio(AK4953AState *pCodecHandle, BOOL enable);
INT AK4953ASetADCDACOptions(AK4953AState* pCodecHandle, BOOL enable);
INT AK4953ADACMute(AK4953AState* pCodecHandle, BOOL enable);
INT AK4953ABufferClear(AK4953AState* pCodecHandle);