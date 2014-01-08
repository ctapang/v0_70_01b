/*******************************************************************************
  ADCP Peripheral Library Template Implementation

  File Name:
    adcp_ChannelScan_Default.h

  Summary:
    ADCP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChannelScan
    and its Variant : Default
    For following APIs :
        PLIB_ADCP_ChannelScanConfigure
        PLIB_ADCP_ExistsChannelScan

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

#ifndef _ADCP_CHANNELSCAN_DEFAULT_H
#define _ADCP_CHANNELSCAN_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADCP_CHANNEL_SCAN_ENABLE_0_VREG(index)

  MASKs: 
    _ADCP_CHANNEL_SCAN_ENABLE_0_MASK(index)

  POSs: 
    _ADCP_CHANNEL_SCAN_ENABLE_0_POS(index)

  LENs: 
    _ADCP_CHANNEL_SCAN_ENABLE_0_LEN(index)

*/


//******************************************************************************
/* Function :  ADCP_ChannelScanConfigure_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ChannelScanConfigure 

  Description:
    This template implements the Default variant of the PLIB_ADCP_ChannelScanConfigure function.
*/

PLIB_TEMPLATE void ADCP_ChannelScanConfigure_Default( ADCP_MODULE_ID index , uint32_t lowEnable , uint32_t highEnable , ADCP_SCAN_TRG_SRC triggerSource )
{
    uint32_t input;
    /* set the channel scan enable bits */
    _SFR_WRITE(_ADCP_CHANNEL_SCAN_ENABLE_0_VREG(index), lowEnable);
    _SFR_WRITE(_ADCP_CHANNEL_SCAN_ENABLE_44_VREG(index), highEnable);

    /* Set the trigger source for all Class 1 and Class 2 inputs to ADCP_TRG_SRC_SCAN_TRG */
    for (input = 0; input < 12; input++ ) {
        if (lowEnable & 1) {
            _SFR_FIELD_WRITE(_ADCP_TRIGGER_SOURCE0_VREG(index)+ (input / 4),
                    _ADCP_TRIGGER_SOURCE0_MASK(index) << ((input % 4) * _ADCP_TRIGGER_SOURCE1_POS(index)),
                    _ADCP_TRIGGER_SOURCE1_POS(index) * (input % 4),
                    ADCP_TRG_SRC_SCAN_TRG);
        }
        lowEnable >>= 1;
    }

    /* Set the Scan Trigger source*/
    _SFR_FIELD_WRITE(_ADCP_SCAN_TRIG_SRC_VREG(index),
            _ADCP_SCAN_TRIG_SRC_MASK(index),
            _ADCP_SCAN_TRIG_SRC_POS(index),
            triggerSource);

}


//******************************************************************************
/* Function :  ADCP_ExistsChannelScan_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ExistsChannelScan

  Description:
    This template implements the Default variant of the PLIB_ADCP_ExistsChannelScan function.
*/

PLIB_TEMPLATE bool ADCP_ExistsChannelScan_Default( ADCP_MODULE_ID index )
{
    return true;
}


#endif /*_ADCP_CHANNELSCAN_DEFAULT_H*/

/******************************************************************************
 End of File
*/

