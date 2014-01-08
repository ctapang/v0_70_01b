/*******************************************************************************
  MRF24W Driver SPI interface routines

  File Name: 
    drv_wifi_spi_init_spi.c  
  
  Summary:
    SUMMARY
    
  Description:
    Module for Microchip TCP/IP Stack
*******************************************************************************/

//DOM-IGNORE-BEGIN
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


/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/
#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_IF_MRF24W)
//#include "tcpip/src/system/drivers/drv_spi.h"
#include "drv_wifi_spi.h"


/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

//============================================================================
//                          SPI Definitions
//============================================================================

#if defined(__C30__)
    #define ClearSPIDoneFlag()
    static inline __attribute__((__always_inline__)) void WaitForDataByte( void )
    {
        while ((WF_SPISTATbits.SPITBF == 1) || (WF_SPISTATbits.SPIRBF == 0));
    }

    #define SPI_ON_BIT          (WF_SPISTATbits.SPIEN)
#endif

/*
*********************************************************************************************************
*                                           LOCAL FUNCTION PROTOTYPES                               
*********************************************************************************************************
*/

static bool ConfigureSpiMRF24W(void);

#define TEST_SPI_SPEED 0
#if TEST_SPI_SPEED
static void test_SPI_Speed(void);
#endif
/*****************************************************************************
  Function:
    bool WF_SpiInit(void)

  Summary:
    Initializes the SPI interface to the MRF24W device.

  Description:
    Configures the SPI interface for communications with the MRF24W.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None
      
  Remarks:
    This function is called by WFHardwareInit.
*****************************************************************************/
bool WF_SpiInit(void)
{
    bool res;
    
    /* disable the spi interrupt if necessary */
    // No need because SPI interrupt is not used

    // Initialize IO for WF chip select    
    WF_CS_Init();     
    WF_SpiDisableChipSelect();  // Disable chip select before initialization

    res = ConfigureSpiMRF24W();  

    /* clear the completion flag */
    #if (!defined( __PIC32MX__ )) && (!defined( __PIC32MZ__ ))
    ClearSPIDoneFlag();
    #endif
#if TEST_SPI_SPEED   //test speed
	test_SPI_Speed();
#endif
    return res;
}


/*
  PIC32 SPI clock speed:
  ---------------------
    Fsck =        Fpb
           ------------------
           2 * (SPIxBRG + 1)
           
Note that the maximum possible baud rate is
Fpb/2 (SPIXBRG = 0) and the minimum possible baud
rate is Fpb /1024.           
*/


/*****************************************************************************
  Function:
    void ConfigureSpiMRF24W(void)

  Summary:
    Configures the SPI interface to the MRF24W.

  Description:
    Configures the SPI interface for communications with the MRF24W.

  Precondition:
    None

  Parameters:
    None

  Returns:
    true if success
    false otherwise
      
  Remarks:
    1) If the SPI bus is shared with other peripherals this function is called
       each time an SPI transaction occurs by WF_SpiEnableChipSelect.  Otherwise it 
       is called once during initialization by WF_SpiInit. 
       
    2) Maximum SPI clock rate for the MRF24W is 25MHz.
*****************************************************************************/
static bool ConfigureSpiMRF24W(void)
{
    /*----------------------------------------------------------------*/
    /* After we save context, configure SPI for MRF24W communications */
    /*----------------------------------------------------------------*/
    /* enable the SPI clocks            */
    /* set as master                    */
    /* clock idles high                 */
    /* ms bit first                     */
    /* 8 bit tranfer length             */
    /* data changes on falling edge     */
    /* data is sampled on rising edge   */
    /* set the clock divider            */

            ISP_SPI_init();
            return true;

}    

/*****************************************************************************
  Function:
    void WF_SpiEnableChipSelect(void)

  Summary:
    Enables the MRF24W SPI chip select.

  Description:
    Enables the MRF24W SPI chip select as part of the sequence of SPI 
    communications.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None
      
  Remarks:
    If the SPI bus is shared with other peripherals then the current SPI context
    is saved.
*****************************************************************************/
void WF_SpiEnableChipSelect(void)
{
    /* set Slave Select low (enable SPI chip select on MRF24W) */
    WF_CS_Assert(); 
}    

/*****************************************************************************
  Function:
    void WF_SpiDisableChipSelect(void)

  Summary:
    Disables the MRF24W SPI chip select.

  Description:
    Disables the MRF24W SPI chip select as part of the sequence of SPI 
    communications.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None
      
  Remarks:
    If the SPI bus is shared with other peripherals then the current SPI context
    is restored.
*****************************************************************************/
void WF_SpiDisableChipSelect(void)
{
    /* set Slave Select high ((disable SPI chip select on MRF24W)   */
    WF_CS_Deassert();
}    


#if defined(WF_SPI_DMA_ENABLE)
void WF_DMA_Transmit(uint8_t *pbuf,uint16_t length)
{
    uint8_t  rxTrash[WF_SPI_DMA_BUF_SIZE];
    BOOL intDisabled;

    if(length > WF_SPI_DMA_BUF_SIZE)
    {
        SYS_ASSERT(false, ""); 
    }
    // pbuf points to uint8_t array of data to be transmitted to MRF
    // length indicates number of bytes to send
//    TRISAbits.TRISA7 = 0;
//    LATAbits.LATA7 = 1;
    //printf("T %d\r\n",length);
    // save state of external interrupt here
    intDisabled = WF_EintIsDisabled();
    WF_EintDisable();


    IEC1CLR=0x00030000; // disable DMA channel 0&1 interrupts
    IFS1CLR=0x00030000; // clear existing DMA channel 0&1 interrupt flag

    DMACONSET=0x00008000; // enable the DMA controller

    DCH0CONSET = 0x3; // channel off, pri 3, no chaining
    DCH1CONSET = 0x62;
    DCH0ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match
    DCH1ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match

    // program the transfer
    DCH0SSA=((UINT32)pbuf) & 0x1FFFFFFFL; // transfer source physical address
    DCH1DSA=((UINT32)rxTrash) & 0x1FFFFFFFL; // transfer source physical address
    //    DCH0DSA=(UINT32)pbuf+length;
    if( MRF24W_SPI_CHN == 1)
    {
        DCH0DSA=((UINT32)&SPI1BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer destination physical address
        DCH1SSA=((UINT32)&SPI1BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer source physical address
    }
    else if(MRF24W_SPI_CHN == 2)
    {
        DCH0DSA=((UINT32)&SPI2BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer destination physical address
        DCH1SSA=((UINT32)&SPI2BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer source physical address
    }
    DCH0SSIZ=length; // source size 200 bytes
    DCH0DSIZ=1; // destination size 200 bytes
    DCH0CSIZ=1; // 200 bytes transferred per event

    DCH1SSIZ=1; // source size 200 bytes
    DCH1DSIZ=length; // destination size 200 bytes
    DCH1CSIZ=1; // 200 bytes transferred per event

    DCH0INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH1INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH0CONSET=0x80; // turn channel on
    DCH1CONSET=0x80; // turn channel on
    // initiate a transfer
    DCH0ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_TX_IRQ);
    DCH1ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_RX_IRQ);
//    DCH0ECONSET=0x00000080; // set CFORCE to 1
    // do something else
    // poll to see that the transfer was done
    while(TRUE)
    {
        register int pollCnt; // use a poll counter.
        // continuously polling the DMA controller in a tight
        // loop would affect the performance of the DMA transfer
        int dma0Flags=DCH0INT;
        int dma1Flags = DCH1INT;
        if((dma0Flags&0xb)&&(dma1Flags&0xb))
        {           // one of CHERIF (DCHxINT<0>), CHTAIF (DCHxINT<1>)
                    // or CHBCIF (DCHxINT<3>) flags set
            break;  // transfer completed
        }
        pollCnt=length; // use an adjusted value here
        while(pollCnt--); // wait before reading again the DMA controller
    }


    DMACONCLR=0x00008000; // disable the DMA controller
    if(!intDisabled)
    {
        WF_EintEnable();
    }
//    LATAbits.LATA7 = 0;

}
void WF_DMA_Receive(uint8_t *pbuf,uint16_t length)
{
    BOOL intDisabled;
    uint8_t  txTrash[WF_SPI_DMA_BUF_SIZE];

    if(length > WF_SPI_DMA_BUF_SIZE)
    {
        SYS_ASSERT(false, ""); 
    }

//    printf("R %d\r\n",length);
    // pbuf points to uint8_t array of data to be received from MRF
    // length indicates number of bytes to read
    intDisabled = WF_EintIsDisabled();
    WF_EintDisable();

//    TRISAbits.TRISA7 = 0;
//    LATAbits.LATA7 = 1;

    IEC1CLR=0x00030000; // disable DMA channel 0&1 interrupts
    IFS1CLR=0x00030000; // clear existing DMA channel 0&1 interrupt flag

    DMACONSET=0x00008000; // enable the DMA controller

    DCH0CONSET = 0x3; // channel off, pri 3, no chaining
    DCH1CONSET = 0x62;
    DCH0ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match
    DCH1ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match

    // program the transfer
    DCH0SSA=((UINT32)txTrash) & 0x1FFFFFFFL; // transfer source physical address
    DCH1DSA=((UINT32)pbuf) & 0x1FFFFFFFL; // transfer source physical address
//    DCH0DSA=(UINT32)pbuf+length;
    if( MRF24W_SPI_CHN == 1)
    {
        DCH0DSA=((UINT32)&SPI1BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer destination physical address
        DCH1SSA=((UINT32)&SPI1BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer source physical address
    }
    else if( MRF24W_SPI_CHN == 2)
    {
        DCH0DSA=((UINT32)&SPI2BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer destination physical address
        DCH1SSA=((UINT32)&SPI2BUF /*WF_SSPBUF*/) & 0x1FFFFFFFL; // transfer source physical address
    }
    DCH0SSIZ=length; // source size 200 bytes
    DCH0DSIZ=1; // destination size 200 bytes
    DCH0CSIZ=1; // 200 bytes transferred per event

    DCH1SSIZ=1; // source size 200 bytes
    DCH1DSIZ=length; // destination size 200 bytes
    DCH1CSIZ=1; // 200 bytes transferred per event

    DCH0INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH1INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH0CONSET=0x80; // turn channel on
    DCH1CONSET=0x80; // turn channel on
    // initiate a transfer
    DCH0ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_TX_IRQ);
    DCH1ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_RX_IRQ);
//    DCH0ECONSET=0x00000080; // set CFORCE to 1
    // do something else
    // poll to see that the transfer was done
    while(TRUE)
    {
        register int pollCnt; // use a poll counter.
        // continuously polling the DMA controller in a tight
        // loop would affect the performance of the DMA transfer
        int dma0Flags=DCH0INT;
        int dma1Flags = DCH1INT;
        if((dma0Flags&0xb)&&(dma1Flags&0xb))
        {           // one of CHERIF (DCHxINT<0>), CHTAIF (DCHxINT<1>)
                    // or CHBCIF (DCHxINT<3>) flags set
            break;  // transfer completed
        }
        pollCnt=length<<1; // use an adjusted value here
        while(pollCnt--); // wait before reading again the DMA controller
    }


    DMACONCLR=0x00008000; // disable the DMA controller
    if(!intDisabled)
    {
        WF_EintEnable();
    }
//    LATAbits.LATA7 = 0;

}

#endif

#if TEST_SPI_SPEED   //test code for compare SPI speed between DMA and No-DMA
static void test_SPI_Speed(void)
{
    int bufsize_speed = 100;
	int i;
	uint8_t buf[1000];
    SYS_TICK tick_begin, tick_end;
	printf("This is a test for spi speed for write\r\n");

	tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 1);
	tick_end = SYS_TICK_Get();
	printf("1 the ticks = %d\r\n",tick_end - tick_begin);

	tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 2);
	tick_end = SYS_TICK_Get();
	printf("2 the ticks = %d\r\n",tick_end - tick_begin);

	tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 4);
	tick_end = SYS_TICK_Get();
	printf("4 the ticks = %d\r\n",tick_end - tick_begin);

	tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 10);
	tick_end = SYS_TICK_Get();
	printf("10 the ticks = %d\r\n",tick_end - tick_begin);

	tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 100);
	tick_end = SYS_TICK_Get();
	printf("100 the ticks = %d\r\n",tick_end - tick_begin);

    tick_begin = SYS_TICK_Get();
	for(i=0;i<1000;i++) WriteWFArray(0,buf, 1000);
	tick_end = SYS_TICK_Get();
	printf("1000 the ticks = %d\r\n",tick_end - tick_begin);	

	while(1);
}
#endif
#else
// dummy func to keep compiler happy when module has no executeable code
void MCHP_Spi_EmptyFunc(void)
{
}
#endif /* TCPIP_IF_MRF24W */


//DOM-IGNORE-END
