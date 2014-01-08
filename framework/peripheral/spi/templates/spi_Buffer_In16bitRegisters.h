/*******************************************************************************
  SPI Peripheral Library Template Implementation

  File Name:
    spi_Buffer_In16bitRegisters.h

  Summary:
    SPI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Buffer
    and its Variant : In16bitRegisters
    For following APIs :
        PLIB_SPI_BufferClear
        PLIB_SPI_BufferRead
        PLIB_SPI_BufferWrite
        PLIB_SPI_ExistsBuffer

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

#ifndef _SPI_BUFFER_IN16BITREGISTERS_H
#define _SPI_BUFFER_IN16BITREGISTERS_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SPI_BUFFER_16BIT_LOW_VREG(index)
    _SPI_BUFFER_16BIT_HIGH_VREG(index)

  MASKs: 
    _SPI_BUFFER_16BIT_LOW_MASK(index)
    _SPI_BUFFER_16BIT_HIGH_MASK(index)

  POSs: 
    _SPI_BUFFER_16BIT_LOW_POS(index)
    _SPI_BUFFER_16BIT_HIGH_POS(index)

  LENs: 
    _SPI_BUFFER_16BIT_LOW_LEN(index)
    _SPI_BUFFER_16BIT_HIGH_LEN(index)

*/


//******************************************************************************
/* Function :  SPI_BufferClear_In16bitRegisters

  Summary:
    Implements In16bitRegisters variant of PLIB_SPI_BufferClear 

  Description:
    This template implements the In16bitRegisters variant of the PLIB_SPI_BufferClear function.
*/

PLIB_TEMPLATE void SPI_BufferClear_In16bitRegisters( SPI_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  SPI_BufferRead_In16bitRegisters

  Summary:
    Implements In16bitRegisters variant of PLIB_SPI_BufferRead 

  Description:
    This template implements the In16bitRegisters variant of the PLIB_SPI_BufferRead function.
*/

PLIB_TEMPLATE SPI_DATA_TYPE SPI_BufferRead_In16bitRegisters( SPI_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  SPI_BufferWrite_In16bitRegisters

  Summary:
    Implements In16bitRegisters variant of PLIB_SPI_BufferWrite 

  Description:
    This template implements the In16bitRegisters variant of the PLIB_SPI_BufferWrite function.
*/

PLIB_TEMPLATE void SPI_BufferWrite_In16bitRegisters( SPI_MODULE_ID index , SPI_DATA_TYPE data )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  SPI_ExistsBuffer_In16bitRegisters

  Summary:
    Implements In16bitRegisters variant of PLIB_SPI_ExistsBuffer

  Description:
    This template implements the In16bitRegisters variant of the PLIB_SPI_ExistsBuffer function.
*/

PLIB_TEMPLATE bool SPI_ExistsBuffer_In16bitRegisters( SPI_MODULE_ID index )
{
    return true;
}


#endif /*_SPI_BUFFER_IN16BITREGISTERS_H*/

/******************************************************************************
 End of File
*/

