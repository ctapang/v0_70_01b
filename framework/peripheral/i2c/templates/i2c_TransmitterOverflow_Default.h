/*******************************************************************************
  I2C Peripheral Library Template Implementation

  File Name:
    i2c_TransmitterOverflow_Default.h

  Summary:
    I2C PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TransmitterOverflow
    and its Variant : Default
    For following APIs :
        PLIB_I2C_TransmitterOverflowHasOccurred
        PLIB_I2C_TransmitterOverflowClear
        PLIB_I2C_ExistsTransmitterOverflow

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

#ifndef _I2C_TRANSMITTEROVERFLOW_DEFAULT_H
#define _I2C_TRANSMITTEROVERFLOW_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _I2C_TRANS_OVERFLOW_VREG(index)

  MASKs: 
    _I2C_TRANS_OVERFLOW_MASK(index)

  POSs: 
    _I2C_TRANS_OVERFLOW_POS(index)

  LENs: 
    _I2C_TRANS_OVERFLOW_LEN(index)

*/


//******************************************************************************
/* Function :  I2C_TransmitterOverflowHasOccurred_Default

  Summary:
    Implements Default variant of PLIB_I2C_TransmitterOverflowHasOccurred 

  Description:
    This template implements the Default variant of the PLIB_I2C_TransmitterOverflowHasOccurred function.
*/

PLIB_TEMPLATE bool I2C_TransmitterOverflowHasOccurred_Default( I2C_MODULE_ID index )
{
    return _SFR_BIT_READ(_I2C_TRANS_OVERFLOW_VREG(index),
                             _I2C_TRANS_OVERFLOW_POS(index));
}


//******************************************************************************
/* Function :  I2C_TransmitterOverflowClear_Default

  Summary:
    Implements Default variant of PLIB_I2C_TransmitterOverflowClear 

  Description:
    This template implements the Default variant of the PLIB_I2C_TransmitterOverflowClear function.
*/

PLIB_TEMPLATE void I2C_TransmitterOverflowClear_Default( I2C_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_I2C_TRANS_OVERFLOW_VREG(index),
                             _I2C_TRANS_OVERFLOW_POS(index));
}


//******************************************************************************
/* Function :  I2C_ExistsTransmitterOverflow_Default

  Summary:
    Implements Default variant of PLIB_I2C_ExistsTransmitterOverflow

  Description:
    This template implements the Default variant of the PLIB_I2C_ExistsTransmitterOverflow function.
*/

PLIB_TEMPLATE bool I2C_ExistsTransmitterOverflow_Default( I2C_MODULE_ID index )
{
    return true;
}


#endif /*_I2C_TRANSMITTEROVERFLOW_DEFAULT_H*/

/******************************************************************************
 End of File
*/

