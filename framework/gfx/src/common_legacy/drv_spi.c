/*****************************************************************************
 *
 * Basic SPI Driver 
 *
 *****************************************************************************
 * File Name:       spi_drv.c
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30, MPLAB C32
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
 * Date        	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 02/10/11	   	...
 *****************************************************************************/
#include "peripheral/spi/plib_spi.h"
#include "drv_spi.h"

static int spiMutex[SPI_NUMBER_OF_MODULES] = { 0, 0, 0, 0 };

/*****************************************************************************
 * void DRV_SPI_Initialize(const unsigned int channel, DRV_SPI_INIT_DATA *pData)
 *****************************************************************************/
void DRV_SPI_Init(uint16_t index, DRV_SPI_INIT *init)
{        
        PLIB_SPI_Disable(index);
        PLIB_SPI_MasterEnable( index );
        PLIB_SPI_CommunicationWidthSelect( index, init->commWidth );
        PLIB_SPI_ClockPolaritySelect( index, 0 );
        PLIB_SPI_OutputDataPhaseSelect( index, 1 );
        PLIB_SPI_InputSamplePhaseSelect( index, 1/*pData->inputSamplePhase*/);
        PLIB_SPI_BaudRateSet(index, 80000000, init->baudRate);
        PLIB_SPI_Enable(index);
}

/*****************************************************************************
 * BYTE SPIGet (unsigned int channel)
 *****************************************************************************/
uint8_t SPIGet (uint16_t channel)
{
    uint8_t spiData = 0;

        spiData = PLIB_SPI_BufferRead(channel);
        return spiData;
          
    return spiData;   
}
/*****************************************************************************
 * int SPILock(unsigned int channel)
 *****************************************************************************/
int SPILock(uint16_t channel)
{

        if(!spiMutex[channel])
        {
            spiMutex[channel] = 1;
            return (1);
        }

        return 0; 
          
}
/*****************************************************************************
 * int SPIUnLock(unsigned int channel)
 *****************************************************************************/
void SPIUnLock(uint16_t channel)
{    
        spiMutex[channel] = 0;
}
