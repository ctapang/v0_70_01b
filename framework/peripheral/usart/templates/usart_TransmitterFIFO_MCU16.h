/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_TransmitterFIFO_Default.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TransmitterFIFO
    and its Variant : Default
    For following APIs :
        PLIB_USART_TransmitterFIFOLevelSelect
        PLIB_USART_ExistsTransmitterFIFO

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

#ifndef _USART_TRANSMITTERFIFO_MCU16_H
#define _USART_TRANSMITTERFIFO_MCU16_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_VREG(index)
	_USART_TRANSMITTER_FIFO_LEVEL_SELECT_2_VREG(index)

  MASKs: 
    _USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_MASK(index)
    _USART_TRANSMITTER_FIFO_LEVEL_SELECT_2_MASK(index)
	
  POSs: 
    _USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_POS(index)
	_USART_TRANSMITTER_FIFO_LEVEL_SELECT_2_POS(index)

  LENs: 
    _USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_LEN(index)
	_USART_TRANSMITTER_FIFO_LEVEL_SELECT_2_LEN(index)

*/


//******************************************************************************
/* Function :  USART_TransmitterFIFOLevelSelect_MCU16

  Summary:
    Implements MCU16 variant of PLIB_USART_TransmitterFIFOLevelSelect 

  Description:
    This template implements the MCU16 variant of the PLIB_USART_TransmitterFIFOLevelSelect function.
*/

PLIB_TEMPLATE void USART_TransmitterFIFOLevelSelect_MCU16( USART_MODULE_ID index , USART_TRANSMIT_FIFO_LEVEL fifolevel )
{
    _SFR_FIELD_SET(_USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_VREG(index),
                   (_USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_MASK(index) | _USART_TRANSMITTER_FIFO_LEVEL_SELECT_2_MASK(index)),
                   _USART_TRANSMITTER_FIFO_LEVEL_SELECT_1_POS(index) ,
                   fifolevel );
}


//******************************************************************************
/* Function :  USART_ExistsTransmitterFIFO_MCU16

  Summary:
    Implements MCU16 variant of PLIB_USART_ExistsTransmitterFIFO

  Description:
    This template implements the MCU16 variant of the PLIB_USART_ExistsTransmitterFIFO function.
*/

PLIB_TEMPLATE bool USART_ExistsTransmitterFIFO_MCU16( USART_MODULE_ID index )
{
    return true;
}


#endif /*_USART_TRANSMITTERFIFO_DEFAULT_H*/

/******************************************************************************
 End of File
*/

