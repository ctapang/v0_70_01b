/***********************************************************************************/
/*  Copyright (c) 2002-2009, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
#include "string.h"
#include "framework/peripheral/i2c/plib_i2c.h"
#include <sys/attribs.h>
#include <sys/kmem.h>

uint8_t I2C_ReadBlock(uint8_t deviceID, uint8_t offset, uint8_t *buffer, uint16_t length);
bool I2CByteWasAcknowledged ( void );
bool I2CReceivedDataIsAvailable ( void );
bool I2CReceiverEnable ( bool enable );
bool I2CSendByte ( uint8_t data );
bool I2CStart( void );
void I2CStop ( void );
bool I2CTransmissionHasCompleted ( void );
bool I2CTransmitterIsReady ( void );

#define OVM7690_I2C_BUS              I2C1

void I2C_Init(void)
{
    TRISEbits.TRISE8 = 1; // Input for INT pin for PCAP

    IEC0bits.INT1IE = 0; // disable INT1
    INTCONbits.INT1EP = 1; // rising edge trigger
    IPC2bits.INT1IP = 5;
    IFS0bits.INT1IF = 0; // clear the interrupt flag
    IEC0bits.INT1IE = 1; // enable INT0

    I2C1CONbits.ON =0;

    I2C1BRG = 50; // 50 kHz Baudrate

    I2C1CONbits.ON =1;

    SYS_TMR_DelayMS(500);
}

/*******************************************************************************
  Function:
    BOOL StartTransfer( BOOL restart )

  Summary:
    Starts (or restarts) a transfer to/from the EEPROM.

  Description:
    This routine starts (or restarts) a transfer to/from the EEPROM, waiting (in
    a blocking loop) until the start (or re-start) condition has completed.

  Precondition:
    The I2C module must have been initialized.

  Parameters:
    restart - If FALSE, send a "Start" condition
            - If TRUE, send a "Restart" condition

  Returns:
    TRUE    - If successful
    FALSE   - If a collision occured during Start signaling

  Example:
    <code>
    StartTransfer(FALSE);
    </code>

  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    (or Restart) signal to complete.
  *****************************************************************************/

bool StartTransfer( bool restart )
{

    // Wait for the bus to be idle, then start the transfer
    while(PLIB_I2C_BusIsIdle(0) == false);

    PLIB_I2C_MasterStart(0);

    while(PLIB_I2C_StartWasDetected(0) == false);
    
    return true;
}

/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data )

  Summary:
    This transmits one byte to the EEPROM.

  Description:
    This transmits one byte to the EEPROM, and reports errors for any bus
    collisions.

  Precondition:
    The transfer must have been previously started.

  Parameters:
    data    - Data byte to transmit

  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured

  Example:
    <code>
    TransmitOneByte(0xAA);
    </code>

  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/

bool TransmitOneByte( uint8_t data )
{
 
    // Wait for the transmitter to be ready
    if(PLIB_I2C_TransmitterIsReady(0) == true)
    {

    // Transmit the byte
    if(I2CSendByte(data) == false)
    {
        return(false);
    }

    // Wait for the transmission to finish
    while(PLIB_I2C_TransmitterByteHasCompleted(0) == false);

    return true;
    }
    return false;
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the EEPROM.

  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    StopTransfer();
    </code>

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
***************************************************************************/

void StopTransfer( void )
{

    PLIB_I2C_MasterStop(0);

    I2C1CONCLR = 0x8000; //Reset Status Registers
    I2C1CONSET = 0x8000;

}

//------------------------------------------------------------------------------
// Function: I2C_ReadByte
// Description: Read one byte from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The read data is returned.  There is no indication in case of error.
//------------------------------------------------------------------------------
uint8_t I2C_ReadByte(uint8_t deviceID, uint8_t offset)
{
    static uint8_t returnData = 0;

    I2C_ReadBlock( deviceID, offset, &returnData, 1 );

    return( returnData );
}

//------------------------------------------------------------------------------
// Function: I2C_ReadBlock
// Description: Read a block of bytes from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The return code is always 0.  There is no indication in case of error.
//------------------------------------------------------------------------------
uint8_t I2C_ReadBlock(uint8_t deviceID, uint8_t offset, uint8_t *buffer, uint16_t length)
{
    static uint8_t count =0;

    I2C1CONCLR = 0x20; //I2C1CONbits.ACKDT = 0;

    // Start the transfer to write data to the EEPROM
    while(!StartTransfer(false));

   TransmitOneByte(deviceID|0x01);
   
    // Verify that the byte was acknowledged
    while(!I2CByteWasAcknowledged());

    for(count=0;count<length;count++)
    {
        PLIB_I2C_MasterReceiverClock1Byte(0);
        
        while(PLIB_I2C_ReceivedByteIsAvailable(0) == false);

        *buffer  = PLIB_I2C_ReceivedByteGet(0);
        buffer++;

        if(count == (length-1))
        {
            PLIB_I2C_ReceivedByteAcknowledge(0, false);
        }

        I2C1CONSET = 0x10; //I2C1CONbits.ACKEN = 1;

        while(I2C1CONbits.ACKEN == 1);

    }

    // End the transfer (stop here if an error occured)
    StopTransfer();

    return(0);
}

bool I2CByteWasAcknowledged (void)
{
	return(!I2C1STATbits.ACKSTAT);
}

bool I2CReceivedDataIsAvailable (void)
{
	return(I2C1STATbits.RBF);
}

bool I2CSendByte (uint8_t data )
{
    // Send the byte
    PLIB_I2C_TransmitterByteSend(0,data);
        
    // Check for collisions
    if((I2C1STATbits.BCL == 1) || (I2C1STATbits.IWCOL == 1))
    {
		return(false);
    }
	else
    {
		return(true);
    }
}

bool I2CTransmissionHasCompleted (void)
{
	return(!I2C1STATbits.TRSTAT);
}

bool I2CTransmitterIsReady (void)
{
	return(!I2C1STATbits.TBF);
}

//#endif //Used only when debug command handler is enabled
