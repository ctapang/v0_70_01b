/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_UsbClockSource_Default.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : UsbClockSource
    and its Variant : Default
    For following APIs :
        PLIB_OSC_ExistsUsbClockSource
        PLIB_OSC_UsbClockSourceSelect
        PLIB_OSC_UsbClockSourceGet

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

#ifndef _OSC_USBCLOCKSOURCE_DEFAULT_H
#define _OSC_USBCLOCKSOURCE_DEFAULT_H


// *****************************************************************************
// *****************************************************************************
// Section: SYS Clock Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Clock USB clock fixed divisor

  Summary:
    Sets up Clock module USB clock fixed divisor.

  Description:
    Macro holds the value of the fixed USB clock divisor.

  Remarks:
	None.
*/

#define SYS_CLK_USB_FIXED_DIVISOR					2


// *****************************************************************************
/* Clock USB clock fixed multipler

  Summary:
    Sets up Clock module USB clock fixed multipler.

  Description:
    Macro holds the value of the fixed USB clock multipler.

  Remarks:
	None.
*/

#define SYS_CLK_USB_FIXED_PLL_MULTIPLIER			24


//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_OSC_USB_CLOCK_SOURCE_VREG(index)
    _OSC_OSC_REGISTER_LOCK_VREG(index)

  MASKs: 
    _OSC_OSC_USB_CLOCK_SOURCE_MASK(index)
    _OSC_OSC_REGISTER_LOCK_MASK(index)

  POSs: 
    _OSC_OSC_USB_CLOCK_SOURCE_POS(index)
    _OSC_OSC_REGISTER_LOCK_POS(index)

  LENs: 
    _OSC_OSC_USB_CLOCK_SOURCE_LEN(index)
    _OSC_OSC_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsUsbClockSource_Default

  Summary:
    Implements Default variant of PLIB_OSC_ExistsUsbClockSource

  Description:
    This template implements the Default variant of the PLIB_OSC_ExistsUsbClockSource function.
*/

PLIB_TEMPLATE bool OSC_ExistsUsbClockSource_Default( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_UsbClockSourceSelect_Default

  Summary:
    Implements Default variant of PLIB_OSC_UsbClockSourceSelect 

  Description:
    This template implements the Default variant of the PLIB_OSC_UsbClockSourceSelect function.
*/

PLIB_TEMPLATE void OSC_UsbClockSourceSelect_Default( OSC_MODULE_ID index , OSC_USBCLOCK_SOURCE usbClock )
{
    _SFR_BIT_WRITE(_OSC_OSC_USB_CLOCK_SOURCE_VREG(index),
                       _OSC_OSC_USB_CLOCK_SOURCE_POS(index) ,
                       usbClock );
}


//******************************************************************************
/* Function :  OSC_UsbClockSourceGet_Default

  Summary:
    Implements Default variant of PLIB_OSC_UsbClockSourceGet 

  Description:
    This template implements the Default variant of the PLIB_OSC_UsbClockSourceGet function.
*/

PLIB_TEMPLATE OSC_USBCLOCK_SOURCE OSC_UsbClockSourceGet_Default( OSC_MODULE_ID index )
{
    return _SFR_BIT_READ(_OSC_OSC_USB_CLOCK_SOURCE_VREG(index),
                            _OSC_OSC_USB_CLOCK_SOURCE_POS(index) );
}


#endif /*_OSC_USBCLOCKSOURCE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

