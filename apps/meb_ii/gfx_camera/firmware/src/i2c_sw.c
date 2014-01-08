/***********************************************************************************/
/*  Copyright (c) 2002-2009, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
#include "app.h"
#include "string.h"
#include "i2c.h"
#include "I2CPrivate.h"

#include <sys/attribs.h>
#include <sys/kmem.h>


BYTE I2C_ReadBlock(BYTE deviceID, BYTE offset, BYTE *buffer, WORD length);
BYTE I2C_WriteBlock(BYTE deviceID, BYTE offset, BYTE buffer, WORD length);

extern volatile GFX_COLOR GraphicsFrame[1][(DISP_VER_RESOLUTION)][(DISP_HOR_RESOLUTION)];

#define OVM7690_I2C_BUS              I2C3

void Camera_Init(void)
{

    LATJbits.LATJ7 = 0;

   CNENAbits.CNIEA1 = 1;
   TRISAbits.TRISA1 = 1; //HSYNC IO Pin

   CNENJbits.CNIEJ2 = 1; //VSYNC
   TRISJbits.TRISJ2 = 1; //VSYNC IO Pin
   CNCONJbits.ON = 1;
   CNCONAbits.ON = 1;
   
   IFS3bits.CNJIF = 0; //Clear intterupt flag

   IPC31bits.CNJIP = 5;
   IPC29bits.CNAIP = 7;

   IEC3bits.CNJIE = 1;
   IEC3bits.CNAIE = 1;

   // set the transfer event control: what event is to start the DMA transfer
   INTCONbits.INT2EP = 1; // rising edge trigger
   IEC0bits.INT2IE = 1;
   TRISFbits.TRISF5 = 1; //Input for CLK

   TRISK = 0xff; //Input for portk

   DCH0CONbits.CHPRI = 0b11;  //Camera DMA channel has highest priority
   DCH0ECONbits.CHSIRQ = _EXTERNAL_2_VECTOR;
   DCH0ECONbits.SIRQEN = 1;
   DCH0DSA = KVA_TO_PA(&GraphicsFrame[0][0][0]);
   DCH0SSA = KVA_TO_PA((void*)&PORTK);
   DCH0SSIZ = 1;
   DCH0DSIZ = (480<<1);
   DCH0CSIZ = 1;

}

void I2C_Init(void)
{

    TRISJbits.TRISJ7 = 0;
    LATJbits.LATJ7 = 0;

    SYS_TMR_DelayMS(1000);

    I2C3CONCLR = 0x8000;  //Reset Status Registers
    I2C3BRG = 175; // 300 kHz Baudrate

    I2C3CONSET = 0x8000;  //Reset Status Registers
    
    SYS_TMR_DelayMS(1000);
    
    I2C_WriteBlock(0x42, 0x11, 0x06, 2); //Slow the clock rate by half and change to RGB format

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

BOOL StartTransfer( BOOL restart )
{
    I2C_STATUS  status;

    // Wait for the bus to be idle, then start the transfer
    while( !I2CBusIsIdle(OVM7690_I2C_BUS) );

    if(I2CStart(OVM7690_I2C_BUS) != I2C_SUCCESS)
    {
         return FALSE;
    }

    // Wait for the signal to complete
    while(I2C3STATbits.S == 0);
    
    return TRUE;
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

BOOL TransmitOneByte( UINT8 data )
{
 
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(OVM7690_I2C_BUS));

    // Transmit the byte
    if(I2CSendByte(OVM7690_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION)
    {
        return FALSE;
    }

   // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(OVM7690_I2C_BUS));
 
    return TRUE;
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
    I2C_STATUS status;

    // Send the Stop signal
    I2CStop(OVM7690_I2C_BUS);

    while(I2C3STATbits.P == 0)
    {
        I2C3CONbits.PEN = 1;
    }

}

//------------------------------------------------------------------------------
// Function: I2C_WriteByte
// Description: Write one byte to the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              No error information is returned.
//------------------------------------------------------------------------------
void I2C_WriteByte(BYTE deviceID, BYTE offset, BYTE value)
{
    I2C_WriteBlock( deviceID, offset, value, 1 );
}


//------------------------------------------------------------------------------
// Function: I2C_ReadByte
// Description: Read one byte from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The read data is returned.  There is no indication in case of error.
//------------------------------------------------------------------------------
BYTE I2C_ReadByte(BYTE deviceID, BYTE offset)
{
    BYTE returnData = 0;

    I2C_ReadBlock( deviceID, offset, &returnData, 1 );

    return( returnData );
}




//#ifdef USE_DEBUG_CMD_HANDLER   //Uused only when debug command handler is enabled

//------------------------------------------------------------------------------
// Function: I2C_WriteBlock
// Description: Write a block of bytes to the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The return code is always 0.  There is no indication in case of error.
//------------------------------------------------------------------------------
BYTE I2C_WriteBlock(BYTE deviceID, BYTE offset, BYTE buffer, WORD length)
{
	BYTE write_buffer[256];
    //    memset(write_buffer, 0, sizeof(write_buffer));
	WORD count;
        BOOL Success = TRUE;

    write_buffer[0] = deviceID;
    write_buffer[1] = offset;
    write_buffer[2] = buffer;
    write_buffer[3] = 0x06;

    // Start the transfer to write data to the EEPROM
    if( !StartTransfer(FALSE) )
    {
        while(1);
    }

    // Transmit all data
    count = 0;

    while( Success && (count < (length + 2)) )
    {

             // Transmit a byte
            TransmitOneByte(write_buffer[count]);
        
            // Advance to the next byte
            count++;

            // Verify that the byte was acknowledged
            if(!I2CByteWasAcknowledged(OVM7690_I2C_BUS))
            {
                Success = FALSE;
            }

    }

    // End the transfer (hang here if an error occured)
    StopTransfer();

    if(!Success)
    {
        while(1);
    }

    return(0);
}


//------------------------------------------------------------------------------
// Function: I2C_ReadBlock
// Description: Read a block of bytes from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The return code is always 0.  There is no indication in case of error.
//------------------------------------------------------------------------------
BYTE I2C_ReadBlock(BYTE deviceID, BYTE offset, BYTE *buffer, WORD length)
{
    BYTE write_buffer[2] = {0x00};
    BYTE count =0;
    BOOL                Success = TRUE;

    write_buffer[0] = deviceID;
    write_buffer[1] = offset;

    // Start the transfer to write data to the EEPROM
    if(!StartTransfer(FALSE) )
    {
        while(1);
    }

    // Transmit all data
    count = 0;

    while( Success && (count < (2)) )
    {
        // Transmit a byte
        TransmitOneByte(write_buffer[count]);

            // Advance to the next byte
            count++;

            // Verify that the byte was acknowledged
            if(!I2CByteWasAcknowledged(OVM7690_I2C_BUS))
            {
                Success = FALSE;
            }
    }

    // Start the transfer to read data
    StartTransfer(TRUE);

   // Transmit the address with the READ bit set
   deviceID |= 0x01;

   TransmitOneByte(deviceID);

    // Verify that the byte was acknowledged
    if(!I2CByteWasAcknowledged(OVM7690_I2C_BUS))
    {
        Success = FALSE;
    }

    for(count=0;count<length;count++)
    {

    // Read the data from the desired address
    if(Success)
    {
        if(I2CReceiverEnable(OVM7690_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
        {
            Success = FALSE;
        }
        else
        {
//            while(!I2CReceivedDataIsAvailable(OVM7690_I2C_BUS));
            *buffer++ = I2CGetByte(OVM7690_I2C_BUS);
        }

    }
    }
    // End the transfer (stop here if an error occured)
    StopTransfer();

    return(0);
}

BOOL I2CBusIsIdle( I2C_MODULE id )
{
    // Check the status of the Start & Stop bits to determine if the bus is idle.
    return ( (I2C3STATbits.S == 0 && I2C3STATbits.P == 0 ) ||
             (I2C3STATbits.S == 0 && I2C3STATbits.P == 1 )   );
}

BOOL I2CByteWasAcknowledged ( I2C_MODULE id )
{
	return(!I2C3STATbits.ACKSTAT);
}

BYTE I2CGetByte ( I2C_MODULE id )
{
	return(I2C3RCV);
}

I2C_STATUS I2CGetStatus ( I2C_MODULE id )
{
    I2C_STATUS              status;
    UINT32                  control;

    // Read the status and control registers
    status  = I2C3STAT;
    control = I2C3CON;

    // Condition the "Start" flag so it does not get set until
    // the "Start" (or "Repeated Start") signal is complete.
    if( control & (_I2CCON_SEN_MASK | _I2CCON_RSEN_MASK) )
    {
        status &= ~_I2CSTAT_S_MASK;
    }

    // Condition the "Stop" flag so it does not get set until
    // the "Stop" signal is complete.
    if( control & _I2CCON_PEN_MASK )
    {
        status &= ~_I2CSTAT_P_MASK;
    }

	return(status);
}

I2C_RESULT I2CReceiverEnable ( I2C_MODULE id, BOOL enable )
{
    // Enable the receiver
	I2C3CONbits.RCEN = enable;

    // Check for an overflow condition
    if(I2C3STATbits.I2COV)
    {
		return(I2C_RECEIVE_OVERFLOW);
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

I2C_RESULT I2CRepeatStart ( I2C_MODULE id )
{
    // Send the repeated Start
	I2C3CONbits.RSEN = 1;

    // Check for collisions
	if( I2C3STAT & (_I2CSTAT_BCL_MASK | _I2CSTAT_IWCOL_MASK) )
    {
		return(I2C_MASTER_BUS_COLLISION);
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

I2C_RESULT I2CSendByte ( I2C_MODULE id, BYTE data )
{

    // Send the byte
    I2C3TRN = data;

    // Check for collisions
    if((I2C3STATbits.BCL == 1) || (I2C3STATbits.IWCOL == 1))
    {
		return(I2C_MASTER_BUS_COLLISION);
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

I2C_RESULT I2CStart( I2C_MODULE id )
{
    // Enable the Start condition
   I2C3CONSET = 0x00000001;//I2C1CONbits.SEN = 1;

    // Check for collisions
    if(I2C3STATbits.BCL)
    {
		return(I2C_MASTER_BUS_COLLISION);
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

void I2CStop ( I2C_MODULE id )
{
    // Enable the Stop condition
    I2C3CONSET = 0x00000004;// I2C1CONbits.PEN = 1;

}

BOOL I2CTransmissionHasCompleted ( I2C_MODULE id )
{
	return(!I2C3STATbits.TRSTAT);
}

BOOL I2CTransmitterIsReady ( I2C_MODULE id )
{
	return(!I2C3STATbits.TBF);
}
