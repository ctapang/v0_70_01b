/*****************************************************************************
 *
 * Basic access to SPI Flash SST25VF016 and M25P80
 *
 *****************************************************************************
 * File Name:       SST25VF016.c
 * Dependencies:    SST25VF016.h
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 01/07/09	   ...
 * 03/08/11    - Modified header file dependencies
 *             - Abstracted out SPI component 
 * 05/11/11    - Updated this file to support both SST25VF016 and M25P80 families
 *             - Although the file name is still specific for SST25VF016
 * 02/29/12    - Updated this file for specific M25P80 families usage.
 *****************************************************************************/
#include "system_config.h"

#if defined (USE_SST25VF016) || defined(USE_M25P80)

#include "SST25VF016.h"

/************************************************************************
* SST25 Commands                                                       
************************************************************************/
    #define SST25_CMD_READ  (unsigned)0x03
    #define SST25_CMD_WRITE (unsigned)0x02
    #define SST25_CMD_WREN  (unsigned)0x06
    #define SST25_CMD_RDSR  (unsigned)0x05

    #if defined(USE_M25P80)
      #define SST25_CMD_EWSR  (unsigned)0x06
      #define SST25_CMD_SER   (unsigned)0xD8
      #define SST25_CMD_READ_HIGH_SPEED  (unsigned) 0x0B
      #define SST25_CMD_ERASE (unsigned) 0xC7  // in M25P80 data sheet this is BULK ERASE
	  
      #define SST25_WIP_STATUS (unsigned) 0x01
      #define SST25_WEL_STATUS (unsigned) 0x02
	  #define SST25_STATUS_MASK (unsigned) 0x60
    #elif defined(USE_SST25VF016)
      #define SST25_CMD_EWSR  (unsigned)0x50
      #define SST25_CMD_SER   (unsigned)0x20
      #define SST25_CMD_ERASE (unsigned)0x60
	#else
	  #error "EWSR and SER commands not defined for the selected Serial flash."
    #endif	
     
    #define SST25_CMD_WRSR  (unsigned)0x01  // Write Status Register

void SPIPut(uint16_t channel, unsigned char data)
{
        // Wait for free buffer
        while(!PLIB_SPI_TransmitBufferIsEmpty(channel));

        PLIB_SPI_BufferWrite(channel, data);

        // Wait for data byte
        while(!PLIB_SPI_ReceiverBufferIsFull(channel));

        return;

}

static DRV_SPI_INIT spiInitData;

/************************************************************************
* Function: SST25Init                                                  
*                                                                       
* Overview: this function setup SPI and IOs connected to SST25
*                                                                       
* Input: none                                                          
*                                                                       
* Output: none
*                                                                       
************************************************************************/
void SST25Init( DRV_SPI_INIT *pInitData )
{
    // initialize the SPI channel to be used
    // SPI_CHANNEL_USED is defined in the hardware profile
    //Set IOs directions for SST25 SPI

    SST25_CS_LAT = 1;
    SST25_CS_TRIS = 0;

    memcpy(&spiInitData, pInitData, sizeof(DRV_SPI_INIT));

    SST25ResetWriteProtection();
}

/************************************************************************
* Function: void SST25WriteByte(BYTE data, DWORD address)                                           
*                                                                       
* Overview: this function writes a byte to the address specified
*                                                                       
* Input: data to be written and address
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void SST25WriteByte(uint8_t data, uint32_t address)
{
    SST25WriteEnable();

    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_WRITE);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>16);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>8);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, data);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SST25CSHigh();

    // Wait for write end
    while(SST25IsWriteBusy());
}

/************************************************************************
* Function: BYTE SST25ReadByte(DWORD address)             
*                                                                       
* Overview: this function reads a byte from the address specified         
*                                                                       
* Input: address                                                     
*                                                                       
* Output: data read
*                                                                       
************************************************************************/
uint8_t SST25ReadByte(uint32_t address)
{
    uint8_t    temp;
    
    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_READ);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>16);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>8);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, 0);
    temp = PLIB_SPI_BufferRead(spiInitData.spiId);

    SST25CSHigh();

    return (temp);
}

/************************************************************************
* Function: void SST25WriteWord(WODR data, DWORD address)                                           
*                                                                       
* Overview: this function writes a 16-bit word to the address specified
*                                                                       
* Input: data to be written and address
*                                                                       
* Output: none                                                         
*                                                                       
************************************************************************/
void SST25WriteWord(uint16_t data, uint32_t address)
{
    SST25WriteByte(data, address);
    SST25WriteByte(data>>8, address + 1);
}

/************************************************************************
* Function: uint16_t SST25ReadWord(DWORD address)             
*                                                                       
* Overview: this function reads a 16-bit word from the address specified         
*                                                                       
* Input: address                                                     
*                                                                       
* Output: data read
*                                                                       
************************************************************************/
uint16_t SST25ReadWord(uint32_t address)
{
    uint16_t    temp;

    temp = SST25ReadByte(address);
    temp |= (uint16_t)(SST25ReadByte(address + 1) << 8 );

    return (temp);
}

/************************************************************************
* Function: SST25WriteEnable()                                         
*                                                                       
* Overview: this function allows write/erase SST25. Must be called  
* before every write/erase command.                                         
*                                                                       
* Input: none                                                          
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void SST25WriteEnable(void)
{

    SST25CSLow();
    SPIPut(spiInitData.spiId, SST25_CMD_WREN);
    PLIB_SPI_BufferRead(spiInitData.spiId);
    SST25CSHigh();

}

/************************************************************************
* Function: BYTE SST25IsWriteBusy(void)  
*                                                                       
* Overview: this function reads status register and chek BUSY bit for write operation
*                                                                       
* Input: none                                                          
*                                                                       
* Output: non zero if busy
*                                                                       
************************************************************************/
uint8_t SST25IsWriteBusy(void)
{
    uint8_t    temp;

    SST25CSLow();
    SPIPut(spiInitData.spiId, SST25_CMD_RDSR);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, 0);
    temp = PLIB_SPI_BufferRead(spiInitData.spiId);
    SST25CSHigh();

    return (temp & 0x01);
}

/************************************************************************
* Function: BYTE SST25WriteArray(DWORD address, BYTE* pData, nCount)
*                                                                       
* Overview: this function writes a data array at the address specified
*                                                                       
* Input: flash memory address, pointer to the data array, data number
*                                                                       
* Output: return 1 if the operation was successfull
*                                                                     
************************************************************************/
uint8_t SST25WriteArray(uint32_t address, uint8_t *pData, uint16_t nCount)
{
    uint32_t   addr;
    uint8_t    *pD;
    uint16_t    counter;
#if defined(USE_M25P80)    
    uint8_t status;
#endif

    addr = address;
    pD = pData;

    // WRITE
    for(counter = 0; counter < nCount; counter++)
    {
        SST25WriteByte(*pD++, addr++);
    }

#if defined(USE_M25P80)

    // check status of Write in Progress
    // wait for BULK ERASE to be done
    SST25CSLow();
    SPIPut(spiInitData.spiId, SST25_CMD_RDSR);
    SPIGet(spiInitData.spiId);
    while(1)
    {
        SPIPut(spiInitData.spiId, 0);
        status = (SPIGet(spiInitData.spiId)& SST25_WIP_STATUS);
        if ((status & SST25_WIP_STATUS) == 0)
            break;
    }

    SST25CSHigh();
	
#endif

    // VERIFY
    for(counter = 0; counter < nCount; counter++)
    {
        if(*pData != SST25ReadByte(address))
            return (0);
        pData++;
        address++;
    }

    return (1);
}

/************************************************************************
* Function: void SST25ReadArray(DWORD address, BYTE* pData, nCount)
*                                                                       
* Overview: this function reads data into buffer specified
*                                                                       
* Input: flash memory address, pointer to the data buffer, data number
*                                                                       
************************************************************************/
void SST25ReadArray(uint32_t address, uint8_t *pData, uint16_t nCount)
{

    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_READ);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>16);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>8);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    while(nCount--)
    {
        SPIPut(spiInitData.spiId, 0);
        *pData++ = PLIB_SPI_BufferRead(spiInitData.spiId);
    }

    SST25CSHigh();

}

/************************************************************************
* Function: void SST25ChipErase(void)
*                                                                       
* Overview: chip erase
*                                                                       
* Input: none
*                                                                       
************************************************************************/
void SST25ChipErase(void)
{
#if defined(USE_M25P80)    
    uint8_t status;
#endif

#if defined(USE_SST25VF016)
    SST25WriteEnable();
#endif

 //   while(!SPILock(spiInitData.spiId));

    SST25CSLow();

#if defined(USE_M25P80)    
    // send write enable command
    SPIPut(spiInitData.spiId, SST25_CMD_EWSR);
    SPIGet(spiInitData.spiId);

    SST25CSHigh();
    Nop();
    SST25CSLow();

    // verify if the WEL bit is set high
    while(1)
    {
        SPIPut(spiInitData.spiId, SST25_CMD_RDSR);
        SPIGet(spiInitData.spiId);
        status = 0xFF;
        while((status & SST25_STATUS_MASK) > 0)
        {
            SPIPut(spiInitData.spiId, 0);
            status = SPIGet(spiInitData.spiId);
        }
        if ((status & SST25_WEL_STATUS) == SST25_WEL_STATUS)
            break;
    }
    SST25CSHigh();
#endif

    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_ERASE);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SST25CSHigh();

#if defined (USE_M25P80)
    // wait for BULK ERASE to be done
    SST25CSLow();
    SPIPut(spiInitData.spiId, SST25_CMD_RDSR);
    SPIGet(spiInitData.spiId);
    while(1)
    {
        SPIPut(spiInitData.spiId, 0);
        status = (SPIGet(spiInitData.spiId)& SST25_WIP_STATUS);
        if ((status & SST25_WIP_STATUS) == 0)
            break;
    }

    SST25CSHigh();
#endif
 //   SPIUnLock(spiInitData.spiId);
    
    // Wait for write end
    while(SST25IsWriteBusy());
}

/************************************************************************
* Function: void SST25ResetWriteProtection()
*                                                                       
* Overview: this function reset write protection bits
*                                                                       
* Input: none                                                     
*                                                                       
* Output: none
*                                                                       
************************************************************************/
void SST25ResetWriteProtection(void)
{
#if defined(USE_M25P80)    
    uint8_t status;
#endif

 //   while(!SPILock(spiInitData.spiId));
   
    SST25CSLow();
    
    // send write enable command
    SPIPut(spiInitData.spiId, SST25_CMD_EWSR);
    PLIB_SPI_BufferRead(spiInitData.spiId);
	
    SST25CSHigh();
	
#if defined(USE_M25P80)    
    SST25CSLow();
    // verify if the WEL bit is set high
    while(1)
    {
        SPIPut(spiInitData.spiId, SST25_CMD_RDSR);
        SPIGet(spiInitData.spiId);

        status = 0xFF;
        while((status & SST25_STATUS_MASK) > 0)
        {
            SPIPut(spiInitData.spiId, 0);
            status = SPIGet(spiInitData.spiId);
        }
        if ((status & SST25_WEL_STATUS) == SST25_WEL_STATUS)
            break;
    }
    SST25CSHigh();
#endif


    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_WRSR);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, 0);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SST25CSHigh();
 //   SPIUnLock(spiInitData.spiId);

    // Wait for write end
    while(SST25IsWriteBusy());
}

/************************************************************************
* Function: void SST25SectorErase(DWORD address)                                           
*                                                                       
* Overview: this function erases a 4Kb sector
*                                                                       
* Input: address within sector to be erased
*                                                                       
* Output: none                                 
*                                                                       
************************************************************************/
void SST25SectorErase(uint32_t address)
{
    SST25WriteEnable();
    
 //   while(!SPILock(spiInitData.spiId));

    SST25CSLow();

    SPIPut(spiInitData.spiId, SST25_CMD_SER);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>16);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address>>8);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SPIPut(spiInitData.spiId, address);
    PLIB_SPI_BufferRead(spiInitData.spiId);

    SST25CSHigh();
 //   SPIUnLock(spiInitData.spiId);

    // Wait for write end
    while(SST25IsWriteBusy());
}

#endif // #if defined (USE_SST25VF016) || defined(USE_M25P80)

