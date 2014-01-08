/*******************************************************************************
  PORTS Peripheral Library Template Implementation

  File Name:
    ports_ChangeNoticePullup_PIC24.h

  Summary:
    PORTS PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChangeNoticePullup
    and its Variant : PIC24
    For following APIs :
        PLIB_PORTS_ChangeNoticePullUpEnable
        PLIB_PORTS_ChangeNoticePullUpDisable
        PLIB_PORTS_ExistsChangeNoticePullUp

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

#ifndef _PORTS_CHANGENOTICEPULLUP_PIC24_H
#define _PORTS_CHANGENOTICEPULLUP_PIC24_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PORTS_CHANGE_NOTICE_PULL_UP_1_VREG(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_2_VREG(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_3_VREG(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_4_VREG(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_5_VREG(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_6_VREG(index)

  MASKs: 
    _PORTS_CHANGE_NOTICE_PULL_UP_1_MASK(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_2_MASK(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_3_MASK(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_4_MASK(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_5_MASK(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_6_MASK(index)

  POSs: 
    _PORTS_CHANGE_NOTICE_PULL_UP_1_POS(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_2_POS(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_3_POS(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_4_POS(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_5_POS(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_6_POS(index)

  LENs: 
    _PORTS_CHANGE_NOTICE_PULL_UP_1_LEN(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_2_LEN(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_3_LEN(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_4_LEN(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_5_LEN(index)
    _PORTS_CHANGE_NOTICE_PULL_UP_6_LEN(index)

*/


//******************************************************************************
/* Function :  PORTS_ChangeNoticePullUpEnable_PIC24

  Summary:
    Implements PIC24 variant of PLIB_PORTS_ChangeNoticePullUpEnable 

  Description:
    This template implements the PIC24 variant of the PLIB_PORTS_ChangeNoticePullUpEnable function.
*/

PLIB_TEMPLATE void PORTS_ChangeNoticePullUpEnable_PIC24( PORTS_MODULE_ID         index , PORTS_CHANGE_NOTICE_PIN pinNum )
{
    if( ( pinNum >= 0 ) && ( pinNum <= 15 ) )
    {
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_1_VREG(index), pinNum );
    }
    else if( ( pinNum >= 16 ) && ( pinNum <= 31 ) )
    {
        pinNum = pinNum - 16;
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_2_VREG(index), pinNum );
    }
    else if( ( pinNum >= 32 ) && ( pinNum <= 47 ) )
    {
        pinNum = pinNum - 32;
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_3_VREG(index), pinNum );
    }
    else if( ( pinNum >= 48 ) && ( pinNum <= 63 ) )
    {
        pinNum = pinNum - 48;
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_4_VREG(index), pinNum );
    }
    else if( ( pinNum >= 64 ) && ( pinNum <= 79 ) )
    {
        pinNum = pinNum - 64;
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_5_VREG(index), pinNum );
    }
    else if( ( pinNum >= 80 ) && ( pinNum <= 84 ) )
    {
        pinNum = pinNum - 80;
        _SFR_BIT_SET( _PORTS_CHANGE_NOTICE_PULL_UP_6_VREG(index), pinNum );
    }
}


//******************************************************************************
/* Function :  PORTS_ChangeNoticePullUpDisable_PIC24

  Summary:
    Implements PIC24 variant of PLIB_PORTS_ChangeNoticePullUpDisable 

  Description:
    This template implements the PIC24 variant of the PLIB_PORTS_ChangeNoticePullUpDisable function.
*/

PLIB_TEMPLATE void PORTS_ChangeNoticePullUpDisable_PIC24( PORTS_MODULE_ID         index , PORTS_CHANGE_NOTICE_PIN pinNum )
{
    if( ( pinNum >= 0 ) && ( pinNum <= 15 ) )
    {
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_1_VREG(index), pinNum );
    }
    else if( ( pinNum >= 16 ) && ( pinNum <= 31 ) )
    {
        pinNum = pinNum - 16;
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_2_VREG(index), pinNum );
    }
    else if( ( pinNum >= 32 ) && ( pinNum <= 47 ) )
    {
        pinNum = pinNum - 32;
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_3_VREG(index), pinNum );
    }
    else if( ( pinNum >= 48 ) && ( pinNum <= 63 ) )
    {
        pinNum = pinNum - 48;
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_4_VREG(index), pinNum );
    }
    else if( ( pinNum >= 64 ) && ( pinNum <= 79 ) )
    {
        pinNum = pinNum - 64;
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_5_VREG(index), pinNum );
    }
    else if( ( pinNum >= 80 ) && ( pinNum <= 84 ) )
    {
        pinNum = pinNum - 80;
        _SFR_BIT_CLEAR( _PORTS_CHANGE_NOTICE_PULL_UP_6_VREG(index), pinNum );
    }
}


//******************************************************************************
/* Function :  PORTS_ExistsChangeNoticePullUp_PIC24

  Summary:
    Implements PIC24 variant of PLIB_PORTS_ExistsChangeNoticePullUp

  Description:
    This template implements the PIC24 variant of the PLIB_PORTS_ExistsChangeNoticePullUp function.
*/

PLIB_TEMPLATE bool PORTS_ExistsChangeNoticePullUp_PIC24( PORTS_MODULE_ID index )
{
    return true;
}


#endif /*_PORTS_CHANGENOTICEPULLUP_PIC24_H*/

/******************************************************************************
 End of File
*/

