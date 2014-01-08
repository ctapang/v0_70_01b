/*******************************************************************************
  SPI Peripheral Library Template Implementation

  File Name:
    spi_ReceiverFIFOInterruptMode_Default.h

  Summary:
    SPI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReceiverFIFOInterruptMode
    and its Variant : Default
    For following APIs :
        PLIB_SPI_ReceiverFIFOInterruptModeSelect
        PLIB_SPI_ExistsReceiverFIFOInterruptMode

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

//DOM-IGNORE-END

#ifndef _SPI_RECEIVERFIFOINTERRUPTMODE_DEFAULT_H
#define _SPI_RECEIVERFIFOINTERRUPTMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SPI_RECEIVER_FIFO_INTERRUPT_MODE_VREG(index)

  MASKs: 
    _SPI_RECEIVER_FIFO_INTERRUPT_MODE_MASK(index)

  POSs: 
    _SPI_RECEIVER_FIFO_INTERRUPT_MODE_POS(index)

  LENs: 
    _SPI_RECEIVER_FIFO_INTERRUPT_MODE_LEN(index)

*/


//******************************************************************************
/* Function :  SPI_ReceiverFIFOInterruptModeSelect_Default

  Summary:
    Implements Default variant of PLIB_SPI_ReceiverFIFOInterruptModeSelect 

  Description:
    This template implements the Default variant of the PLIB_SPI_ReceiverFIFOInterruptModeSelect function.
*/

PLIB_TEMPLATE void SPI_ReceiverFIFOInterruptModeSelect_Default( SPI_MODULE_ID index , SPI_FIFO_RX_INTERRUPT mode )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  SPI_ExistsReceiverFIFOInterruptMode_Default

  Summary:
    Implements Default variant of PLIB_SPI_ExistsReceiverFIFOInterruptMode

  Description:
    This template implements the Default variant of the PLIB_SPI_ExistsReceiverFIFOInterruptMode function.
*/

PLIB_TEMPLATE bool SPI_ExistsReceiverFIFOInterruptMode_Default( SPI_MODULE_ID index )
{
    return true;
}


#endif /*_SPI_RECEIVERFIFOINTERRUPTMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

