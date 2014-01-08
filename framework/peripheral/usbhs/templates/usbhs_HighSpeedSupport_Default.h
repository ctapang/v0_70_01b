/*******************************************************************************
  USBHS Peripheral Library Template Implementation

  File Name:
    usbhs_HighSpeedSupport_Default.h

  Summary:
    USBHS PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : HighSpeedSupport
    and its Variant : Default
    For following APIs :
        PLIB_USBHS_HighSpeedEnable
        PLIB_USBHS_HighSpeedDisable
        PLIB_USBHS_HighSpeedIsConnected
        PLIB_USBHS_FullOrHighSpeedIsConnected
        PLIB_USBHS_ExistsHighSpeedSupport

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _USBHS_HIGHSPEEDSUPPORT_DEFAULT_H
#define _USBHS_HIGHSPEEDSUPPORT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USBHS_BASE_ADDRESS_VREG(index)

  MASKs: 
    _USBHS_BASE_ADDRESS_MASK(index)

  POSs: 
    _USBHS_BASE_ADDRESS_POS(index)

  LENs: 
    _USBHS_BASE_ADDRESS_LEN(index)

*/


//******************************************************************************
/* Function :  USBHS_HighSpeedEnable_Default

  Summary:
    Implements Default variant of PLIB_USBHS_HighSpeedEnable 

  Description:
    This template implements the Default variant of the PLIB_USBHS_HighSpeedEnable function.
*/

PLIB_TEMPLATE void USBHS_HighSpeedEnable_Default( USBHS_MODULE_ID index )
{
    /* This function enables high speed support */

    volatile uint8_t * usbBaseAddress = (uint8_t *)_USBHS_BASE_ADDRESS_VREG(index);

    *(usbBaseAddress + 0x01) |= 0x20;
}


//******************************************************************************
/* Function :  USBHS_HighSpeedDisable_Default

  Summary:
    Implements Default variant of PLIB_USBHS_HighSpeedDisable 

  Description:
    This template implements the Default variant of the PLIB_USBHS_HighSpeedDisable function.
*/

PLIB_TEMPLATE void USBHS_HighSpeedDisable_Default( USBHS_MODULE_ID index )
{
    /* This function disables high speed support */

    volatile uint8_t * usbBaseAddress = (uint8_t *)_USBHS_BASE_ADDRESS_VREG(index);

    *(usbBaseAddress + 0x01) &= 0xDF;
}


//******************************************************************************
/* Function :  USBHS_HighSpeedIsConnected_Default

  Summary:
    Implements Default variant of PLIB_USBHS_HighSpeedIsConnected 

  Description:
    This template implements the Default variant of the PLIB_USBHS_HighSpeedIsConnected function.
*/

PLIB_TEMPLATE bool USBHS_HighSpeedIsConnected_Default( USBHS_MODULE_ID index )
{
    /* Returns true if the connected device is high speed
     * else returns false. */

    volatile uint8_t * usbBaseAddress = (uint8_t *)_USBHS_BASE_ADDRESS_VREG(index);

    if((*(usbBaseAddress + 0x1)) & 0x10)
    {
        return true;
    }
    
    return false;
}


//******************************************************************************
/* Function :  USBHS_FullOrHighSpeedIsConnected_Default

  Summary:
    Implements Default variant of PLIB_USBHS_FullOrHighSpeedIsConnected 

  Description:
    This template implements the Default variant of the PLIB_USBHS_FullOrHighSpeedIsConnected function.
*/

PLIB_TEMPLATE bool USBHS_FullOrHighSpeedIsConnected_Default( USBHS_MODULE_ID index )
{
    /* Function returns true is high or full speed device is connected.
     * Return false if low speed or no device is connected */

    volatile uint8_t * usbBaseAddress = (uint8_t *)_USBHS_BASE_ADDRESS_VREG(index);

    if((*(usbBaseAddress + 0x60)) & 0x40)
    {
        /* Connected device is either full or high speed */
        return true;
    }

    if((*(usbBaseAddress + 0x60)) & 0x20)
    {
        /* Connected device is low speed */
        return false;
    }

    /* Nothing is connected ? */

    return false;
}


//******************************************************************************
/* Function :  USBHS_ExistsHighSpeedSupport_Default

  Summary:
    Implements Default variant of PLIB_USBHS_ExistsHighSpeedSupport

  Description:
    This template implements the Default variant of the PLIB_USBHS_ExistsHighSpeedSupport function.
*/

PLIB_TEMPLATE bool USBHS_ExistsHighSpeedSupport_Default( USBHS_MODULE_ID index )
{
    return true;
}


#endif /*_USBHS_HIGHSPEEDSUPPORT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

