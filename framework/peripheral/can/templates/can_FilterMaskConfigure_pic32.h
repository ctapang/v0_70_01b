/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_FilterMaskConfigure_pic32.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : FilterMaskConfigure
    and its Variant : pic32
    For following APIs :
        PLIB_CAN_FilterMaskConfigure
        PLIB_CAN_ExistsFilterMaskConfigure

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

#ifndef _CAN_FILTERMASKCONFIGURE_PIC32_H
#define _CAN_FILTERMASKCONFIGURE_PIC32_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_FILTER_MASK0_SID_VREG(index)
    _CAN_FILTER_MASK0_MIDE_VREG(index)
    _CAN_FILTER_MASK0_EID_VREG(index)
    _CAN_FILTER_MASK1_SID_VREG(index)
    _CAN_FILTER_MASK1_MIDE_VREG(index)
    _CAN_FILTER_MASK1_EID_VREG(index)
    _CAN_FILTER_MASK2_SID_VREG(index)
    _CAN_FILTER_MASK2_MIDE_VREG(index)
    _CAN_FILTER_MASK2_EID_VREG(index)
    _CAN_FILTER_MASK3_SID_VREG(index)
    _CAN_FILTER_MASK3_MIDE_VREG(index)
    _CAN_FILTER_MASK3_EID_VREG(index)

  MASKs: 
    _CAN_FILTER_MASK0_SID_MASK(index)
    _CAN_FILTER_MASK0_MIDE_MASK(index)
    _CAN_FILTER_MASK0_EID_MASK(index)
    _CAN_FILTER_MASK1_SID_MASK(index)
    _CAN_FILTER_MASK1_MIDE_MASK(index)
    _CAN_FILTER_MASK1_EID_MASK(index)
    _CAN_FILTER_MASK2_SID_MASK(index)
    _CAN_FILTER_MASK2_MIDE_MASK(index)
    _CAN_FILTER_MASK2_EID_MASK(index)
    _CAN_FILTER_MASK3_SID_MASK(index)
    _CAN_FILTER_MASK3_MIDE_MASK(index)
    _CAN_FILTER_MASK3_EID_MASK(index)

  POSs: 
    _CAN_FILTER_MASK0_SID_POS(index)
    _CAN_FILTER_MASK0_MIDE_POS(index)
    _CAN_FILTER_MASK0_EID_POS(index)
    _CAN_FILTER_MASK1_SID_POS(index)
    _CAN_FILTER_MASK1_MIDE_POS(index)
    _CAN_FILTER_MASK1_EID_POS(index)
    _CAN_FILTER_MASK2_SID_POS(index)
    _CAN_FILTER_MASK2_MIDE_POS(index)
    _CAN_FILTER_MASK2_EID_POS(index)
    _CAN_FILTER_MASK3_SID_POS(index)
    _CAN_FILTER_MASK3_MIDE_POS(index)
    _CAN_FILTER_MASK3_EID_POS(index)

  LENs: 
    _CAN_FILTER_MASK0_SID_LEN(index)
    _CAN_FILTER_MASK0_MIDE_LEN(index)
    _CAN_FILTER_MASK0_EID_LEN(index)
    _CAN_FILTER_MASK1_SID_LEN(index)
    _CAN_FILTER_MASK1_MIDE_LEN(index)
    _CAN_FILTER_MASK1_EID_LEN(index)
    _CAN_FILTER_MASK2_SID_LEN(index)
    _CAN_FILTER_MASK2_MIDE_LEN(index)
    _CAN_FILTER_MASK2_EID_LEN(index)
    _CAN_FILTER_MASK3_SID_LEN(index)
    _CAN_FILTER_MASK3_MIDE_LEN(index)
    _CAN_FILTER_MASK3_EID_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_FilterMaskConfigure_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_FilterMaskConfigure 

  Description:
    This template implements the pic32 variant of the PLIB_CAN_FilterMaskConfigure function.
*/

PLIB_TEMPLATE void CAN_FilterMaskConfigure_pic32( CAN_MODULE_ID index , CAN_FILTER_MASK mask , uint32_t maskbits , CAN_ID_TYPE idType , CAN_FILTER_MASK_TYPE mide )
{
    /* This function will configure the specified mask. */
    SFR_TYPE *maskControlReg;
    unsigned int sid;
    unsigned int eid;

    // Get the address of the first register. We will can calculate other using filter number.
    maskControlReg = (SFR_TYPE *)_CAN_FILTER_MASK0_SID_VREG(index);

    if(idType == CAN_EID)
    {
            /* Extract the sid and eid from the specified id and assign these to
         the register fields. */
        maskbits &= 0x1FFFFFFF;
        sid = (maskbits & 0x1FFC0000) >> 18;
        eid = maskbits & 0x3FFFF;

        _SFR_FIELD_WRITE(&maskControlReg[4 * mask],
                            _CAN_FILTER_MASK0_EID_MASK(index),
                            _CAN_FILTER_MASK0_EID_POS(index) ,
                            eid );
        _SFR_FIELD_WRITE(&maskControlReg[4 * mask],
                            _CAN_FILTER_MASK0_SID_MASK(index),
                            _CAN_FILTER_MASK0_SID_POS(index) ,
                            sid );
    }
    else if(idType == CAN_SID)
    {
        maskbits &= 0x7FF;
        _SFR_FIELD_WRITE(&maskControlReg[4 * mask],
                                _CAN_FILTER_MASK0_SID_MASK(index),
                                _CAN_FILTER_MASK0_SID_POS(index) ,
                                maskbits );
    }
    if(mide == CAN_FILTER_MASK_IDE_TYPE)
    {
        /* This means masking will also compare the message type */
        _SFR_BIT_SET(&maskControlReg[4 * mask], _CAN_FILTER_MASK1_MIDE_POS(index));
    }
    else if(mide == CAN_FILTER_MASK_ANY_TYPE)
    {
        /* This means any message is masked */
        _SFR_BIT_CLEAR(&maskControlReg[4 * mask], _CAN_FILTER_MASK1_MIDE_POS(index));
    }
}


//******************************************************************************
/* Function :  CAN_ExistsFilterMaskConfigure_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ExistsFilterMaskConfigure

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ExistsFilterMaskConfigure function.
*/

PLIB_TEMPLATE bool CAN_ExistsFilterMaskConfigure_pic32( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_FILTERMASKCONFIGURE_PIC32_H*/

/******************************************************************************
 End of File
*/

