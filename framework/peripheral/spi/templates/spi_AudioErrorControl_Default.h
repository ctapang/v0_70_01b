/*******************************************************************************
  SPI Peripheral Library Template Implementation

  File Name:
    spi_AudioErrorControl_Default.h

  Summary:
    SPI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : AudioErrorControl
    and its Variant : Default
    For following APIs :
        PLIB_SPI_AudioErrorEnable
        PLIB_SPI_AudioErrorDisable
        PLIB_SPI_ExistsAudioErrorControl

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

#ifndef _SPI_AUDIOERRORCONTROL_DEFAULT_H
#define _SPI_AUDIOERRORCONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_VREG(index)
    _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_VREG(index)

  MASKs: 
    _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_MASK(index)
    _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_MASK(index)

  POSs: 
    _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_POS(index)
    _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_POS(index)

  LENs: 
    _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_LEN(index)
    _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  SPI_AudioErrorEnable_Default

  Summary:
    Implements Default variant of PLIB_SPI_AudioErrorEnable 

  Description:
    This template implements the Default variant of the PLIB_SPI_AudioErrorEnable function.
*/

PLIB_TEMPLATE void SPI_AudioErrorEnable_Default( SPI_MODULE_ID index , SPI_AUDIO_ERROR error )
{
   switch( error )
    {
        case SPI_AUDIO_ERROR_RECEIVE_OVERFLOW:
                _SFR_BIT_CLEAR( _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_VREG( index ),
                              _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_POS( index ) );
            break;
        case SPI_AUDIO_ERROR_TRANSMIT_UNDERRUN:
                _SFR_BIT_CLEAR( _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_VREG( index ),
                              _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_POS( index ) );
            break;
        default:
            break;
    }
}


//******************************************************************************
/* Function :  SPI_AudioErrorDisable_Default

  Summary:
    Implements Default variant of PLIB_SPI_AudioErrorDisable 

  Description:
    This template implements the Default variant of the PLIB_SPI_AudioErrorDisable function.
*/

PLIB_TEMPLATE void SPI_AudioErrorDisable_Default( SPI_MODULE_ID index , SPI_AUDIO_ERROR error )
{
   switch( error )
    {
        case SPI_AUDIO_ERROR_RECEIVE_OVERFLOW:
                _SFR_BIT_SET( _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_VREG( index ),
                              _SPI_RX_OVERFLOW_AUDIO_ERROR_CONTROL_POS( index ) );
            break;
        case SPI_AUDIO_ERROR_TRANSMIT_UNDERRUN:
                _SFR_BIT_SET( _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_VREG( index ),
                              _SPI_TX_UNDERRUN_AUDIO_ERROR_CONTROL_POS( index ) );
            break;
        default:
            break;
    }
}


//******************************************************************************
/* Function :  SPI_ExistsAudioErrorControl_Default

  Summary:
    Implements Default variant of PLIB_SPI_ExistsAudioErrorControl

  Description:
    This template implements the Default variant of the PLIB_SPI_ExistsAudioErrorControl function.
*/

PLIB_TEMPLATE bool SPI_ExistsAudioErrorControl_Default( SPI_MODULE_ID index )
{
    return true;
}


#endif /*_SPI_AUDIOERRORCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

