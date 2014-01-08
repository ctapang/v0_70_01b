/********************************************************************
 File Name:     ak4953a.c
 Dependencies:  See INCLUDES section
 Processor:	PIC32 USB Microcontrollers
 Hardware:	This demo is natively intended to be used on Microchip USB demo
 		boards supported by the MCHPFSUSB stack.  See release notes for
 		support matrix.  This demo can be modified for use on other hardware
 		platforms.
 Complier:  	Microchip C32 (for PIC32)
 Company:	Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
********************************************************************/

#include "ak4953a.h"
#include <sys/attribs.h>
INT AK4953AControl(AK4953AState* pCodecHandle, AK4953A_REGISTER controlRegister, INT command);
INT AK4953ATuneSampleRate(AK4953AState* pCodecHandle, TUNE_STEP tune_step);

volatile INT 	data_index_tx=0;
volatile INT 	data_index_value_tx=0;
volatile INT 	data_index_rx=0;
volatile INT 	data_index_value_rx=0;
volatile INT	pllkUpdate=0;
volatile INT 	data_available_count=0;
volatile INT 	data_available_count_rx=0;

AK4953AState* pCodecHandlePriv = NULL;
uint32_t i2cErrors;


uint8_t             AK4953A_Control_Registers[]={
                        /* Power Management 1 */0x54,
                        /* Power Management 1 */0x33,
                        /*   Signal Select 1  */0xBB,
                        /*   Signal Select 2  */0x45,
                        /*   Signal Select 3  */0x10,
                        /*   Mode Control 1   */0x23,
                        /*   Mode Control 2   */0x09,
                        /*   Mode Control 3   */0xB8,
                        /*   Digital MIC0     */0x00,
                        /*   Timer Select     */0x00,
                        /*   ALC Timer Select */0x00,
                        /*   ALC Mode Control 1*/0x00,
                        /*   ALC Mode Control 2*/0xE1,
                       /*    ALC Mode Control 3*/0x28,
                       /*    ALC Volume */        0x30,
                       /*    Lch Input Volume Control */  0x31,
                       /*    Rch Input Volume Control */0x31,
                       /*    Lch Output Volume Control*/ 0xF0,
                       /*    Rch Output Volume Control*/  0xF0,
                       /*    Lch Digital Volume Control*/ 0x1A,
                       /*    Rch Digital Volume Control*/ 0x1A,

                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        0x00, 0x00
                                      };
#define NUM_CODECREG                        0x1d           //16 CODEC Registers

void AK4953AInit(void)
{
    /* I2S module uses REFCLKO1 as the base clock source*/
   /* REFLCKO1 setup */
   /* Configure reference clock output to 12.288MHz */
   /* Setup REFCLKO1 trim bits*/
   //REFO1TRIM = I2S_MCLK_ROTRIM(I2S_MCLK_SOURCE, I2S_SAMPLERATE_INIT, I2S_MCLK_RATIO);

   /* Select input clock source for REFCLKO1 - SPLL */
   REFO1CONbits.ROSEL = OSC_REFOCON_SYSPLL;
   /* Enable REFCLKO1 to be output on a Pin */
   REFO1CONbits.OE = 1;
   /* Select the Clock Divider */
   REFO1CON |= I2S_MCLK_RODIV(I2S_MCLK_SOURCE, I2S_SAMPLERATE_INIT, I2S_MCLK_RATIO);
   /* Turn on the REFLCKO1 module */
   REFO1CONbits.ON = 1;
   /* Turn on the division logic*/
   REFO1CONbits.DIVSWEN = 1;

   /* Wait for division to finish*/
   while (REFO1CONbits.DIVSWEN);

           
         /* I2S pin setup*/
   /***************************************/
   /* I2S pin               PIC32MZ pin   */
   /***************************************/
   /***************Power*******************/
   /* PDN                   RH3           */
   /***************Data********************/
   /* MCKI                  RPD15/REFCLKO1*/
   /* BICK                  SCK1          */
   /* LRCK                  RPF12/SS1#    */
   /* SDTI                  RPB10/SDO1    */
   /* SDTO                  RPD14/SDI1    */
   /***************Control*****************/
   /* SCL                   RA2/SCL2      */
   /* SDA                   RA3/SDA2      */
   /***************************************/
   /* Disable analog functions on I2S pins*/
   /* Disable analog function on MCKI */
   ANSELDbits.ANSD15 = 0;
   /* Disable analog function on SS1# */
   ANSELFbits.ANSF12 = 0;
   /* Disable analog function on SDO1 */
   ANSELBbits.ANSB10 = 0;
   /* Disable analog function on SDI1 */
   ANSELDbits.ANSD14 = 0;

   /* Set the pin direction - PDN, REFCLKO1, SCK1, SS1#, SDO1- output, SDI1 - input*/
   TRISHbits.TRISH3 = 0;
   TRISDbits.TRISD15 = 0;
   TRISDbits.TRISD1 = 0;
   TRISFbits.TRISF12 = 0;
   TRISBbits.TRISB10 = 0;
   TRISDbits.TRISD14 = 1;

   /* Configure PPS pins */
   RPD15Rbits.RPD15R = 0xF;
   RPF12Rbits.RPF12R = 0x5;
   RPB10Rbits.RPB10R = 0x5;
   SDI1Rbits.SDI1R = 0xB;      //SDI1

      /* Disable the SPI1/I2S1 module before configuration */
   SPI1CONCLR = 0xFFFFFFFF;
   SPI1CON2CLR = 0xFFFFFFFF;

   /* Setup the baud rate */
   SPI1BRG = ((I2S_MCLK_RATIO/I2S_FRAME_RATIO) >> 1) - 1;

   //Clear the receive overflow flag
   SPI1STATCLR = 0x00000040;

   /* Configure SPI in I2S audio protocol mode */
   /* Enable audio protocol*/
   SPI1CON2bits.AUDEN = 1;
   /* Ignore transmit underrun (not critical) */
   SPI1CON2bits.IGNTUR = 1;
   /* Ignore receive overrun (not critical) */
   SPI1CON2bits.IGNROV = 1;

   /* Enable master mode */
   SPI1CONbits.MSTEN = 1;
   /* Set clock polarity as active low */
   SPI1CONbits.CKP = 1;
   /* Enable enhanced buffer mode */
   SPI1CONbits.ENHBUF = 1;
   /* Select base clock for baud rate generator*/
   SPI1CONbits.MCLKSEL = 1;
   /* Setup frame sync pulse as one character wide*/
   //SPI1CONbits.FRMSYPW = 1;
   SPI1CONbits.STXISEL = 3; 
   /* Turn on SPI1/I2S1 module*/
   /* LRCK and BICK are free running after this step */
   SPI1CONSET =  0x00008000;


    /* I2C module uses PBCLK2 as the base clock source */
    /* Setup PBCLK2 */
    /* Oscillator SFR unlock sequence*/
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    /* 2nd level unlock */
    if (OSCCONbits.CLKLOCK)
        OSCCONbits.CLKLOCK=0;
    PB2DIV = 0x00008003;
    PB2DIVbits.PBDIV = PBCLK_DIV_4;
    /* Wait for PBCLK2 to be stable*/
    while (!PB2DIVbits.PBDIVRDY);
    SYSKEY = 0x33333333;

    /* As I2C2 lines are primary functions on port pins, no mapping necessary */

    /* Power-up Codec */
    PORTHbits.RH3 = 1;
}

AK4953AState* AK4953AOpen(OPEN_MODE mode)
{
    pCodecHandlePriv = (AK4953AState*)malloc(sizeof(AK4953AState));
    if(pCodecHandlePriv == NULL)
        return(NULL);

    if((mode == O_RD) || (mode == O_RDWR))
    {
        pCodecHandlePriv->rxBuffer = (AudioStereo*)__pic32_alloc_coherent(AK4953A_RX_BUFFER_SIZE_BYTES);
        if(pCodecHandlePriv->rxBuffer == NULL)
        return(NULL);
        memset(pCodecHandlePriv->rxBuffer, 0, AK4953A_RX_BUFFER_SIZE_BYTES);

        //Set DMA Channel Priority
        PLIB_DMA_ChannelXPrioritySelect
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            DMA_CHANNEL_PRIORITY_0
        );

        // Set Auto Enable
        PLIB_DMA_ChannelXAutoEnable( DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);

        //Set start IRQ
        PLIB_DMA_ChannelXStartIRQSet
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            DMA_TRIGGER_SPI_1_RECEIVE
        );

        PLIB_DMA_ChannelXTriggerEnable
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           DMA_CHANNEL_TRIGGER_TRANSFER_START
       );
       
       PLIB_DMA_ChannelXSourceStartAddressSet
       (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            (uint32_t)&AK4953A_SPI_MODULE_BUFFER
       );

       PLIB_DMA_ChannelXSourceSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           sizeof(UINT16)
       );
       PLIB_DMA_ChannelXDestinationStartAddressSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           (uint32_t)pCodecHandlePriv->rxBuffer
       );
       PLIB_DMA_ChannelXDestinationSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           AK4953A_RX_BUFFER_SIZE_BYTES>>1
        );

        PLIB_DMA_ChannelXCellSizeSet
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            sizeof(UINT16)
        );

        PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);

        PLIB_DMA_ChannelXINTSourceEnable
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            DMA_INT_BLOCK_TRANSFER_COMPLETE
        );

        PLIB_INT_VectorPrioritySet(INT_ID_0, AK4953A_SPI_RX_DMA_VECTOR, AK4953A_SPI_RX_DMA_INT_PRI_LEVEL);
        PLIB_INT_VectorSubPrioritySet(INT_ID_0, AK4953A_SPI_RX_DMA_VECTOR, AK4953A_SPI_RX_DMA_INT_SPRI_LEVEL);

        PLIB_INT_SourceFlagClear(INT_ID_0, AK4953A_SPI_RX_DMA_INTERRUPT);
    }

    if((mode == O_WR) ||(mode == O_RDWR))
    {
        pCodecHandlePriv->txBuffer = (AudioStereo*)__pic32_alloc_coherent(AK4953A_TX_BUFFER_SIZE_BYTES);

        if(pCodecHandlePriv->txBuffer == NULL)
        return(NULL);
        memset(pCodecHandlePriv->txBuffer, 0, AK4953A_TX_BUFFER_SIZE_BYTES);


        PLIB_DMA_ChannelXPrioritySelect(DMA_ID_0,
                                        AK4953A_SPI_TX_DMA_CHANNEL,
                                        DMA_CHANNEL_PRIORITY_0);
        PLIB_DMA_ChannelXAutoEnable( DMA_ID_0, AK4953A_SPI_TX_DMA_CHANNEL);
        PLIB_DMA_ChannelXStartIRQSet
        (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            DMA_TRIGGER_SPI_1_TRANSMIT
        );
        PLIB_DMA_ChannelXTriggerEnable
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           DMA_CHANNEL_TRIGGER_TRANSFER_START
       );

       PLIB_DMA_ChannelXSourceStartAddressSet
       (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            (uint32_t)pCodecHandlePriv->txBuffer
       );

       PLIB_DMA_ChannelXSourceSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           AK4953A_TX_BUFFER_SIZE_BYTES>>1
       );
       PLIB_DMA_ChannelXDestinationStartAddressSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           (uint32_t)&AK4953A_SPI_MODULE_BUFFER
       );
       PLIB_DMA_ChannelXDestinationSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           sizeof(UINT16)
        );

        PLIB_DMA_ChannelXCellSizeSet
        (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            sizeof(UINT16)
        );
        PLIB_DMA_ChannelXINTSourceEnable
        (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            DMA_INT_BLOCK_TRANSFER_COMPLETE
        );

        PLIB_INT_VectorPrioritySet(INT_ID_0, AK4953A_SPI_TX_DMA_VECTOR, AK4953A_SPI_TX_DMA_INT_PRI_LEVEL);
        PLIB_INT_VectorSubPrioritySet(INT_ID_0, AK4953A_SPI_TX_DMA_VECTOR, AK4953A_SPI_TX_DMA_INT_SPRI_LEVEL);

        PLIB_INT_SourceFlagClear(INT_ID_0, AK4953A_SPI_TX_DMA_INTERRUPT);
    }
    return(pCodecHandlePriv);
}

void AK4953AStartAudio(AK4953AState *pCodecHandle, BOOL enable)
{
    if(enable == TRUE)
    {
        pllkUpdate=0;
        data_available_count=0;

        data_index_tx=0;
        data_index_value_tx=0;
        data_index_rx=0;
        data_index_value_rx=0;

        pCodecHandle->activeTxBuffer 	= PP_BUFF0;
        pCodecHandle->statusTxBuffer[0] = TRUE;
        pCodecHandle->statusTxBuffer[1] = FALSE;
        pCodecHandle->countTxBuffer[0] 	= DMA_PP_BUFFER_SIZE;
        pCodecHandle->countTxBuffer[1] 	= DMA_PP_BUFFER_SIZE;
        
        PLIB_DMA_ChannelXINTSourceFlagClear
        (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            DMA_INT_BLOCK_TRANSFER_COMPLETE
        );
        
       
        PLIB_INT_SourceEnable(INT_ID_0, AK4953A_SPI_TX_DMA_INTERRUPT);


        pCodecHandle->activeRxBuffer 	= PP_BUFF0;
        pCodecHandle->statusRxBuffer[0] = TRUE;
        pCodecHandle->statusRxBuffer[1] = FALSE;
        pCodecHandle->countRxBuffer[0] 	= DMA_PP_BUFFER_SIZE;
        pCodecHandle->countRxBuffer[1] 	= DMA_PP_BUFFER_SIZE;
        
        PLIB_DMA_ChannelXINTSourceFlagClear
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            DMA_INT_BLOCK_TRANSFER_COMPLETE
        );
       
        PLIB_INT_SourceEnable(INT_ID_0, AK4953A_SPI_RX_DMA_INTERRUPT);

        
        PLIB_SPI_Enable(AK4953A_SPI_MODULE);
        
        
        PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_TX_DMA_CHANNEL);
//        while(!DCH0CONbits.CHEN)
//            DCH0CONbits.CHEN=1;

        PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);
        while(!DCH1CONbits.CHEN)
            DCH1CONbits.CHEN=1;

         PLIB_DMA_Enable(DMA_ID_0);

    }
    else if(enable == FALSE)
    {
        PLIB_DMA_Disable(DMA_ID_0);
        
        PLIB_DMA_ChannelXDisable(DMA_ID_0, AK4953A_SPI_TX_DMA_CHANNEL);
       
        PLIB_DMA_ChannelXDisable(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);
        
        PLIB_SPI_Disable(AK4953A_SPI_MODULE);
    }
}

INT AK4953AControlReset(AK4953AState* pCodecHandle)
{
    i2cErrors = 0; 
     // Setup I2C2 baud rate
    I2C2BRG = I2C_BAUD_SET(100000);

      /* Turn-on the I2C2 module */
    I2C2CONbits.ON = 1;
    /************************/
    /* CODEC RESET SEQUENCE */
    /************************/
    /* Enable the start condition (transaction starts) */
    I2C2CONbits.SEN = 1;
    /* Wait for start sequence to finish  (hardware clear) */
    while(I2C2CONbits.SEN);
    /* Wait for start indication */
    while(!I2C2STATbits.S);
    /* Check for collisions */
    if(I2C2STATbits.BCL)
    {
        /* Clear collision */
        I2C2STATbits.BCL = 0;
        /* Increment error flag */
        i2cErrors++;
    }
    /* Send audio codec reset release sequence */
    /* Send codec address (0x24) */
    I2C2TRN = AK4953A_I2C_ADDRESS;
    /* Wait for transmit buffer to be empty */
    while(I2C2STATbits.TBF);
    /* Wait for transmit complete */
    while(I2C2STATbits.TRSTAT);
    /* Wait for NACK (should get nack according to AK4953A data sheet page 31) */
    if(!I2C2STATbits.ACKSTAT)
    {
        /* Increment error flag*/
        i2cErrors++;
    }

    /* Send codec sub address (0x00)*/
    I2C2TRN = CODEC_SUB_ADDRESS;
    /* Wait for transmit buffer to be empty */
    while(I2C2STATbits.TBF);
    /* Wait for transmit complete */
    while(I2C2STATbits.TRSTAT);
    /* Wait for NACK (should get nack according to AK4953A data sheet page 31) */
    if(!I2C2STATbits.ACKSTAT)
    {
        /* Increment error flag*/
        i2cErrors++;
    }

    /* Send dummy data (0x00)*/
    I2C2TRN = DUMMY_BYTE;
    /* Wait for transmit buffer to be empty */
    while(I2C2STATbits.TBF);
    /* Wait for transmit complete */
    while(I2C2STATbits.TRSTAT);
    /* Wait for NACK (should get nack according to AK4953A data sheet page 31) */
    if(!I2C2STATbits.ACKSTAT)
    {
        /* Increment error flag*/
        i2cErrors++;
    }

    /* Initiate the stop condition */
    /* Clear the enable bits (SEN, RSEN, PEN, RCEN and ACKEN) */
    I2C2CONCLR = 0x0000001F;
    /* Set repeated start condition bit */
    I2C2CONbits.PEN = 1;
    /* Wait for stop sequence to finish  (hardware clear) */
    while(I2C2CONbits.PEN);

    while((I2C2CON & 0x00000004) == 0x00000004);

    I2C2CONCLR = 0x00008000;
    return 0; 
}

INT AK4953AControl(AK4953AState* pCodecHandle, AK4953A_REGISTER controlRegister, INT command)
{

    BYTE byte1  = (BYTE) (controlRegister & 0xFF);
    BYTE byte2  = (BYTE) (command & 0xFF); 

    int i = 0;
   
    /**************************/
    /* CODEC CONTROL SEQUENCE */
    /**************************/
    I2C2BRG = 0x1E7; 
     /* Turn-on the I2C2 module */
    I2C2CONbits.ON = 1;
    for(i=1l; i<1000; i++);
    /* Enable the start condition (transaction starts) */
    I2C2CONbits.SEN = 1;
    /* Wait for start sequence to finish  (hardware clear) */
    while(I2C2CONbits.SEN);
    /* Wait for start indication */
    while(!I2C2STATbits.S);
    /* Check for collisions */
    if(I2C2STATbits.BCL)
    {
        /* Clear collision */
        I2C2STATbits.BCL = 0;
        /* Increment error flag */
        i2cErrors++;
    }

    /* Send codec address (0x24) */
    I2C2TRN =  AK4953A_I2C_ADDRESS;
    
    /* Wait for transmit buffer to be empty */
    while(I2C2STATbits.TBF);
    /* Wait for transmit complete */
    while(I2C2STATbits.TRSTAT);
    /* Wait for ACK */
    if(I2C2STATbits.ACKSTAT)
    {
        /* Increment error flag*/
        i2cErrors++;
    }
    //Write control data from the array
     I2C2TRN = byte1;
     /* Wait for transmit buffer to be empty */
        while(I2C2STATbits.TBF);
        /* Wait for transmit complete */
        while(I2C2STATbits.TRSTAT);
        /* Wait for NACK (should get nack according to AK4953A data sheet page 31) */
        if(I2C2STATbits.ACKSTAT)
        {
            /* Increment error flag*/
            i2cErrors++;
        }

     //Write control data from the array
     I2C2TRN = byte2;
     /* Wait for transmit buffer to be empty */
        while(I2C2STATbits.TBF);
        /* Wait for transmit complete */
        while(I2C2STATbits.TRSTAT);
        /* Wait for NACK (should get nack according to AK4953A data sheet page 31) */
        if(I2C2STATbits.ACKSTAT)
        {
            /* Increment error flag*/
            i2cErrors++;
        }

      /* Initiate the stop condition */
    /* Clear the enable bits (SEN, RSEN, PEN, RCEN and ACKEN) */
    I2C2CONCLR = 0x0000001F;
    /* Set repeated start condition bit */
    I2C2CONbits.PEN = 1;
    /* Wait for stop sequence to finish  (hardware clear) */
    while(I2C2CONbits.PEN);

    while((I2C2CON & 0x00000004) == 0x00000004);

    I2C2CONCLR = 0x00008000;
 
    return(1);    
}

UINT AK4953AWritePPBuffer(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples)
{
    UINT i, nWrittenSamples = 0;
    PINGPONG_BUFFN usePPBuffer;
    AudioStereo* dest;

    if(nStereoSamples == 0) return(0);
	
    if(data_index_value_tx < pCodecHandle->bufferSize)
        data_index_value_tx += nStereoSamples;
    else
        data_index_value_tx = 0;
	
    usePPBuffer = (pCodecHandle->activeTxBuffer == PP_BUFF0) ? PP_BUFF1 : PP_BUFF0;
    if(pCodecHandle->statusTxBuffer[usePPBuffer] == TRUE)
        return(0);
    nWrittenSamples = (nStereoSamples > DMA_PP_BUFFER_SIZE) ? DMA_PP_BUFFER_SIZE : nStereoSamples;
    dest = (usePPBuffer == PP_BUFF0) ? 	&pCodecHandle->txBuffer[0] : &pCodecHandle->txBuffer[DMA_PP_BUFFER_SIZE];

    for(i = 0; i < nWrittenSamples; i++)
    {
        dest[data_index_tx].audioWord = data[i].audioWord;
		data_index_tx++;
    }

    if(data_index_tx >= pCodecHandle->bufferSize)
    {
	    data_index_value_tx=data_index_tx;
	    data_index_tx=0;
		pCodecHandle->countTxBuffer[usePPBuffer] = pCodecHandle->bufferSize;      
    	pCodecHandle->statusTxBuffer[usePPBuffer] = TRUE;
    }
    return(nWrittenSamples);    
}

UINT AK4953AWrite(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples)
{
    UINT writtenSamples = 0;
	writtenSamples = AK4953AWritePPBuffer(pCodecHandle, &data[0], nStereoSamples);
    return(writtenSamples);
}


UINT AK4953AReadPPBuffer(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples)
{
    UINT i, nReadSamples = 0;
    PINGPONG_BUFFN usePPBuffer;
    AudioStereo* src;

	if(nStereoSamples == 0) return(0);

	if(data_index_value_rx>pCodecHandle->frameSize)
		data_index_value_rx -= nStereoSamples;
	else
		data_index_value_rx = 0;
			
    usePPBuffer = (pCodecHandle->activeRxBuffer == PP_BUFF0) ? PP_BUFF1 : PP_BUFF0;
    if(pCodecHandle->statusRxBuffer[usePPBuffer] == TRUE)
        return(0);
    nReadSamples = (nStereoSamples > DMA_PP_BUFFER_SIZE) ? DMA_PP_BUFFER_SIZE : nStereoSamples;
    src = (usePPBuffer == PP_BUFF0) ? 	&pCodecHandle->rxBuffer[0]
									 :	&pCodecHandle->rxBuffer[DMA_PP_BUFFER_SIZE];

	for(i = 0; i < nReadSamples; i++){	
        data[i].audioWord = src[pCodecHandle->bufferSize-data_index_rx].audioWord;
		data_index_rx--;
    }

    
    if(data_index_rx <= 0){
	    data_index_value_rx = data_index_rx;
	    data_index_rx = pCodecHandle->bufferSize>>1;
		pCodecHandle->countRxBuffer[usePPBuffer] = pCodecHandle->bufferSize;      
    	pCodecHandle->statusRxBuffer[usePPBuffer] = TRUE;
    }

    return(nReadSamples);    
}

UINT AK4953ARead(AK4953AState* pCodecHandle, AudioStereo* data, UINT nStereoSamples)
{
    UINT readSamples = 0;
	readSamples = AK4953AReadPPBuffer(pCodecHandle, &data[0], nStereoSamples);
    return(readSamples);
}

INT AK4953ASetADCDACOptions(AK4953AState* pCodecHandle, BOOL enable)
{
    AK4953AControlReset(pCodecHandle);
    
     AK4953AControl(pCodecHandle, AK4953A_REG_PWR_MGMT1, 0x54);
     AK4953AControl(pCodecHandle, AK4953A_REG_PWR_MGMT2, 0x33);
     AK4953AControl(pCodecHandle, AK4953A_REG_SIG_SLCT1, 0x9B);
     AK4953AControl(pCodecHandle, AK4953A_REG_SIG_SLCT2, 0x45);
     AK4953AControl(pCodecHandle, AK4953A_REG_SIG_SLCT3, 0x10);
     AK4953AControl(pCodecHandle, AK4953A_REG_MODE_CTRL1, 0x63);
     AK4953AControl(pCodecHandle, AK4953A_REG_MODE_CTRL2, 0x09);
     AK4953AControl(pCodecHandle, AK4953A_REG_MODE_CTRL3, 0x98);
     AK4953AControl(pCodecHandle, AK4953A_REG_DIG_MIC, 0x00);
     AK4953AControl(pCodecHandle, AK4953A_REG_TMR_SLCT, 0x00);
     AK4953AControl(pCodecHandle, AK4953A_REG_ALC_TMR_SLCT, 0x00);
     AK4953AControl(pCodecHandle, AK4953A_REG_ALC_MODE_CTRL1, 0x00);
     AK4953AControl(pCodecHandle, AK4953A_REG_ALC_MODE_CTRL2, 0xE1);
     AK4953AControl(pCodecHandle, AK4953A_REG_ALC_MODE_CTRL3, 0x28);
     AK4953AControl(pCodecHandle, AK4953A_REG_ALC_VLM, 0x91);
     AK4953AControl(pCodecHandle, AK4953A_REG_LIN_VOL_CTRL, 0xF1);
     AK4953AControl(pCodecHandle, AK4953A_REG_RIN_VOL_CTRL, 0xF1);
     AK4953AControl(pCodecHandle, AK4953A_REG_LOP_VOL_CTRL, 0x90);
     AK4953AControl(pCodecHandle, AK4953A_REG_ROP_VOL_CTRL, 0x90);
     AK4953AControl(pCodecHandle, AK4953A_REG_LDIG_VOL_CTRL, 0x1A);
     AK4953AControl(pCodecHandle, AK4953A_REG_RDIG_VOL_CTRL, 0x1A);

     return 1;
}

INT AK4953ASetInput(AK4953AState* pCodecHandle, BOOL enable)
{
#if 0
	if(enable){
    	if(AK4953AControl(pCodecHandle, AK4953A_REG_PWR_MGMT3, PWRMGMT3_PMADR_UP | PWRMGMT3_MDIF1_DIFFIN | PWRMGMT3_MDIF2_DIFFIN/*PWRMGMT3_HPG_3P6DB*/) < 0)
    		return(-1);
 	}   	
    else{	
    	if(AK4953AControl(pCodecHandle, AK4953A_REG_PWR_MGMT3, PWRMGMT3_PMADR_UP | PWRMGMT3_INL0_SET | PWRMGMT3_INR0_SET | PWRMGMT3_INL1_SET | PWRMGMT3_INR1_SET) < 0)
			return(-1);		
	}
        return 0;
#endif
        return 0;
}

INT AK4953ABufferClear(AK4953AState* pCodecHandle){
	if(pCodecHandlePriv->rxBuffer != NULL)	
    	memset(pCodecHandlePriv->rxBuffer, 0, AK4953A_RX_BUFFER_SIZE_BYTES);
    if(pCodecHandlePriv->txBuffer != NULL)		
    	memset(pCodecHandlePriv->txBuffer, 0, AK4953A_TX_BUFFER_SIZE_BYTES);

	return(1);
}

INT AK4953ASetDACVolume(AK4953AState* pCodecHandle, BYTE volumeDAC)
{
	INT volCtrl = 0x15 + ((UINT32)((100-volumeDAC)*(0x80-0x15)))/100;
	
	if(volumeDAC<3)
		volCtrl = 0xF1;
/*
	if(AK4953AControl(pCodecHandle, AK4953A_REG_LDAC_VOL, LDACVOL_DVL(volCtrl)) < 0)
		return(-1);

	if(AK4953AControl(pCodecHandle, AK4953A_REG_RDAC_VOL, RDACVOL_DVL(volCtrl)) < 0)
		return(-1);*/ 
			
								
	return(1);
}

INT AK4953ADACMute(AK4953AState* pCodecHandle, BOOL enable)
{
    if (enable)
       AK4953A_Control_Registers[AK4953A_REG_MODE_CTRL3] |=  MODECTRL3_SMUTE_ENABLE;
    else
       AK4953A_Control_Registers[AK4953A_REG_MODE_CTRL3] &=  ~MODECTRL3_SMUTE_ENABLE;
    if(AK4953AControl(pCodecHandle, AK4953A_REG_MODE_CTRL3, AK4953A_Control_Registers[AK4953A_REG_MODE_CTRL3]) < 0)
		return(-1);
		
	return(1);
}

void AK4953AAdjustSampleRateRx(AK4953AState* pCodecHandle)
{

	data_available_count_rx=(volatile INT)(PLIB_DMA_ChannelXSourceStartAddressGet(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL)>>2)-data_index_value_rx;

	if(data_available_count_rx>pCodecHandle->underrunLimit && data_available_count<pCodecHandle->overrunLimit){
			
		if(data_available_count_rx<pCodecHandle->underrunCount)
			AK4953ATuneSampleRate(pCodecHandle, DEC_TUNE);
		else if(data_available_count_rx>pCodecHandle->overrunCount)
			AK4953ATuneSampleRate(pCodecHandle, INC_TUNE);
	}
		
}
UINT32 Test = 0;
void AK4953AAdjustSampleRateTx(AK4953AState* pCodecHandle)
{
    INT DMASourceStartAddress;
    DMASourceStartAddress = (volatile INT)(PLIB_DMA_ChannelXSourcePointerGet(DMA_ID_0,AK4953A_SPI_TX_DMA_CHANNEL));
    DMASourceStartAddress = KVA_TO_PA(DMASourceStartAddress);
    data_available_count=(pCodecHandle->bufferSize-DMASourceStartAddress)+data_index_value_tx;
    Test++; 
    if(data_available_count>pCodecHandle->underrunLimit && data_available_count<pCodecHandle->overrunLimit)
    {

            if(data_available_count<pCodecHandle->underrunCount)
                    AK4953ATuneSampleRate(pCodecHandle, DEC_TUNE);
            else if(data_available_count>pCodecHandle->overrunCount)
                    AK4953ATuneSampleRate(pCodecHandle, INC_TUNE);
    }
}


INT AK4953ATuneSampleRate(AK4953AState* pCodecHandle, TUNE_STEP tune_step)
{    
    if((pllkUpdate-pCodecHandle->pllkValue)<(-1*pCodecHandle->pllkTuneLimit))
            pllkUpdate=pCodecHandle->pllkValue-pCodecHandle->pllkTuneLimit+pCodecHandle->pllkTune;
    else if((pllkUpdate-pCodecHandle->pllkValue)>pCodecHandle->pllkTuneLimit)
            pllkUpdate=pCodecHandle->pllkValue+pCodecHandle->pllkTuneLimit-pCodecHandle->pllkTune;

    pllkUpdate=(tune_step==INC_TUNE)?(pllkUpdate-pCodecHandle->pllkTune):(pllkUpdate+pCodecHandle->pllkTune);
    
    REFO1TRIM=(pllkUpdate<<23);
    REFO1CONSET=0x00000200;
    return(1);
}

INT AK4953ASetSampleRate(AK4953AState* pCodecHandle, AK4953A_SAMPLERATE sampleRate)
{
	AK4953AStartAudio(pCodecHandle, FALSE);
	pllkUpdate=0;
	data_available_count=0;	    
	
	data_index_tx=0;
	data_index_value_tx=0;
	data_index_rx=0;
	data_index_value_rx=0;	
		
		
	switch (sampleRate)
        {
        case SAMPLERATE_32000HZ:

            pCodecHandle->samplingFreq = 32000;
            pCodecHandle->frameSize = 32;
            pCodecHandle->bufferSize = pCodecHandle->frameSize*BUFFER_DEPTH;
            pCodecHandle->bufferSize = pCodecHandle->frameSize*BUFFER_DEPTH;
            pCodecHandle->underrunCount = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) - pCodecHandle->frameSize / 4;
            pCodecHandle->overrunCount = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) + pCodecHandle->frameSize / 4;
            pCodecHandle->underrunLimit = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) - pCodecHandle->frameSize / 2;
            pCodecHandle->overrunLimit = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) + pCodecHandle->frameSize / 2;

            REFO1CONbits.OE = 0;
            REFO1CONbits.ON = 0;
            REFO1CONbits.RODIV = 5;
            REFO1TRIM = (440 << 23);
            REFO1CONSET = 0x00000200;
            REFO1CONbits.OE = 1;
            REFO1CONbits.ON = 1;
            pCodecHandle->pllkTune = 1;
            pCodecHandle->pllkTuneLimit = 8;
            pCodecHandle->pllkValue = 440;
            pllkUpdate = 440;

            break;

        case SAMPLERATE_48000HZ:
            pCodecHandle->samplingFreq = 48000;
            pCodecHandle->frameSize = 48;
            pCodecHandle->bufferSize = pCodecHandle->frameSize*BUFFER_DEPTH;
            pCodecHandle->underrunCount = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) - pCodecHandle->frameSize / 4;
            pCodecHandle->overrunCount = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) + pCodecHandle->frameSize / 4;
            pCodecHandle->underrunLimit = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) - pCodecHandle->frameSize / 2;
            pCodecHandle->overrunLimit = pCodecHandle->bufferSize + ((int) pCodecHandle->frameSize >> 1) + pCodecHandle->frameSize / 2;

            /* I2S module uses REFCLKO1 as the base clock source*/
           /* REFLCKO1 setup */
           /* Configure reference clock output to 12.288MHz */
           /* Setup REFCLKO1 trim bits*/
           REFO1TRIM = I2S_MCLK_ROTRIM(I2S_MCLK_SOURCE, I2S_SAMPLERATE_INIT, I2S_MCLK_RATIO);
           //REFO1TRIM = (0x1D0 << 23);
           /* Select input clock source for REFCLKO1 - SPLL */
           REFO1CONbits.ROSEL = OSC_REFOCON_SYSPLL;
           /* Enable REFCLKO1 to be output on a Pin */
           REFO1CONbits.OE = 1;
           /* Select the Clock Divider */
           REFO1CON |= I2S_MCLK_RODIV(I2S_MCLK_SOURCE, I2S_SAMPLERATE_INIT, I2S_MCLK_RATIO);
           /* Turn on the REFLCKO1 module */
           REFO1CONbits.ON = 1;
           /* Turn on the division logic*/
           REFO1CONbits.DIVSWEN = 1;

           /* Wait for division to finish*/
           while (REFO1CONbits.DIVSWEN);
            pCodecHandle->pllkTune = 1;
            pCodecHandle->pllkTuneLimit = 4;
            pCodecHandle->pllkValue = 0x46;
            pllkUpdate = 0x46;
        break;

        default:
            break;
	}
	

	AK4953AStartAudio(pCodecHandle, TRUE);
	
	return(1);
}
UINT32 counterDelete;
void __ISR (  _DMA0_VECTOR ,ipl5 ) __DMA0Interrupt ( void )
{

    AudioStereo * dest = pCodecHandlePriv->txBuffer;

    INT size;
    data_index_tx=data_index_value_tx=0;
    counterDelete++; 
    
    PLIB_INT_SourceFlagClear(INT_ID_0, AK4953A_SPI_TX_DMA_INTERRUPT);
    
    DCH0INTbits.CHBCIF = 0;
    while(DCH0INTbits.CHBCIF == 1);

    
    PINGPONG_BUFFN ppFlag = pCodecHandlePriv->activeTxBuffer;
    pCodecHandlePriv->statusTxBuffer[ppFlag] = FALSE;
	
    ppFlag = (ppFlag == PP_BUFF0) ? PP_BUFF1 : PP_BUFF0;
    pCodecHandlePriv->statusTxBuffer[ppFlag] = TRUE;
    dest = (ppFlag == PP_BUFF0) ? dest : &dest[DMA_PP_BUFFER_SIZE];
    size = pCodecHandlePriv->countTxBuffer[ppFlag] * sizeof(AudioStereo);

    PLIB_DMA_ChannelXSourceStartAddressSet
       (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            (uint32_t)dest
       );

       PLIB_DMA_ChannelXSourceSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           size
       );
       PLIB_DMA_ChannelXDestinationStartAddressSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           (uint32_t)&AK4953A_SPI_MODULE_BUFFER
       );
       PLIB_DMA_ChannelXDestinationSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_TX_DMA_CHANNEL,
           sizeof(UINT16)
        );

        PLIB_DMA_ChannelXCellSizeSet
        (
            DMA_ID_0,
            AK4953A_SPI_TX_DMA_CHANNEL,
            sizeof(UINT16)
        );       


    pCodecHandlePriv->activeTxBuffer = ppFlag;
    PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_TX_DMA_CHANNEL);
}

void __ISR (  _DMA1_VECTOR ,ipl5 ) __DMA1Interrupt ( void )
{

    AudioStereo * src = pCodecHandlePriv->rxBuffer;

    INT size;
    data_index_rx=data_index_value_rx=pCodecHandlePriv->bufferSize;
    
    PLIB_INT_SourceFlagClear(INT_ID_0, AK4953A_SPI_RX_DMA_INTERRUPT);
    
    PLIB_DMA_ChannelXINTSourceFlagClear
    (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            DMA_INT_BLOCK_TRANSFER_COMPLETE
    );
    PINGPONG_BUFFN ppFlag = pCodecHandlePriv->activeRxBuffer;
    pCodecHandlePriv->statusRxBuffer[ppFlag] = FALSE;
	
    ppFlag = (ppFlag == PP_BUFF0) ? PP_BUFF1 : PP_BUFF0;
    pCodecHandlePriv->statusRxBuffer[ppFlag] = TRUE;
    src = (ppFlag == PP_BUFF0) ? src : &src[DMA_PP_BUFFER_SIZE];
    size = pCodecHandlePriv->countRxBuffer[ppFlag] * sizeof(AudioStereo);

     PLIB_DMA_ChannelXSourceStartAddressSet
     (
         DMA_ID_0,
         AK4953A_SPI_RX_DMA_CHANNEL,
         (uint32_t)&AK4953A_SPI_MODULE_BUFFER
     );

       PLIB_DMA_ChannelXSourceSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           sizeof(UINT16)
       );
       PLIB_DMA_ChannelXDestinationStartAddressSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           (uint32_t)src
       );
       PLIB_DMA_ChannelXDestinationSizeSet
       (
           DMA_ID_0,
           AK4953A_SPI_RX_DMA_CHANNEL,
           size
        );

        PLIB_DMA_ChannelXCellSizeSet
        (
            DMA_ID_0,
            AK4953A_SPI_RX_DMA_CHANNEL,
            sizeof(UINT16)
        );

        PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);

    pCodecHandlePriv->activeRxBuffer = ppFlag;
    PLIB_DMA_ChannelXEnable(DMA_ID_0, AK4953A_SPI_RX_DMA_CHANNEL);
}
