/*******************************************************************************
  I2C Peripheral Library Template Implementation

  File Name:
    i2c_SlaveClockStretching_Default.h

  Summary:
    I2C PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SlaveClockStretching
    and its Variant : Default
    For following APIs :
        PLIB_I2C_SlaveClockStretchingEnable
        PLIB_I2C_SlaveClockStretchingDisable
        PLIB_I2C_ExistsSlaveClockStretching

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

#ifndef _I2C_SLAVECLOCKSTRETCHING_DEFAULT_H
#define _I2C_SLAVECLOCKSTRETCHING_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _I2C_CLOCK_STRETCHING_VREG(index)

  MASKs: 
    _I2C_CLOCK_STRETCHING_MASK(index)

  POSs: 
    _I2C_CLOCK_STRETCHING_POS(index)

  LENs: 
    _I2C_CLOCK_STRETCHING_LEN(index)

*/


//******************************************************************************
/* Function :  I2C_SlaveClockStretchingEnable_Default

  Summary:
    Implements Default variant of PLIB_I2C_SlaveClockStretchingEnable 

  Description:
    This template implements the Default variant of the PLIB_I2C_SlaveClockStretchingEnable function.
*/

PLIB_TEMPLATE void I2C_SlaveClockStretchingEnable_Default( I2C_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  I2C_SlaveClockStretchingDisable_Default

  Summary:
    Implements Default variant of PLIB_I2C_SlaveClockStretchingDisable 

  Description:
    This template implements the Default variant of the PLIB_I2C_SlaveClockStretchingDisable function.
*/

PLIB_TEMPLATE void I2C_SlaveClockStretchingDisable_Default( I2C_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  I2C_ExistsSlaveClockStretching_Default

  Summary:
    Implements Default variant of PLIB_I2C_ExistsSlaveClockStretching

  Description:
    This template implements the Default variant of the PLIB_I2C_ExistsSlaveClockStretching function.
*/

PLIB_TEMPLATE bool I2C_ExistsSlaveClockStretching_Default( I2C_MODULE_ID index )
{
    return true;
}


#endif /*_I2C_SLAVECLOCKSTRETCHING_DEFAULT_H*/

/******************************************************************************
 End of File
*/

