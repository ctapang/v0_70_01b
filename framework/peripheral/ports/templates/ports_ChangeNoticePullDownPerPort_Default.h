/*******************************************************************************
  PORTS Peripheral Library Template Implementation

  File Name:
    ports_ChangeNoticePullDownPerPort_Default.h

  Summary:
    PORTS PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChangeNoticePullDownPerPort
    and its Variant : Default
    For following APIs :
        PLIB_PORTS_ChangeNoticePullDownPerPortEnable
        PLIB_PORTS_ChangeNoticePullDownPerPortDisable
        PLIB_PORTS_ExistsChangeNoticePullDownPerPort

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

#ifndef _PORTS_CHANGENOTICEPULLDOWNPERPORT_DEFAULT_H
#define _PORTS_CHANGENOTICEPULLDOWNPERPORT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PORTS_CHANGE_NOTICE_PULL_DOWN_B_VREG(index)

  MASKs: 
    _PORTS_CHANGE_NOTICE_PULL_DOWN_B_MASK(index)

  POSs: 
    _PORTS_CHANGE_NOTICE_PULL_DOWN_B_POS(index)

  LENs: 
    _PORTS_CHANGE_NOTICE_PULL_DOWN_B_LEN(index)

*/


//******************************************************************************
/* Function :  PORTS_ChangeNoticePullDownPerPortEnable_Default

  Summary:
    Implements Default variant of PLIB_PORTS_ChangeNoticePullDownPerPortEnable 

  Description:
    This template implements the Default variant of the PLIB_PORTS_ChangeNoticePullDownPerPortEnable function.
*/

PLIB_TEMPLATE void PORTS_ChangeNoticePullDownPerPortEnable_Default( PORTS_MODULE_ID  index , PORTS_CHANNEL channel , PORTS_BIT_POS  bitPos )
{
    _SFR_BIT_SET(_PORTS_CHANGE_NOTICE_PULL_DOWN_B_VREG(index) + ((channel-1) * 0x40),
						   bitPos );
}


//******************************************************************************
/* Function :  PORTS_ChangeNoticePullDownPerPortDisable_Default

  Summary:
    Implements Default variant of PLIB_PORTS_ChangeNoticePullDownPerPortDisable 

  Description:
    This template implements the Default variant of the PLIB_PORTS_ChangeNoticePullDownPerPortDisable function.
*/

PLIB_TEMPLATE void PORTS_ChangeNoticePullDownPerPortDisable_Default( PORTS_MODULE_ID  index , PORTS_CHANNEL channel , PORTS_BIT_POS  bitPos )
{
    _SFR_BIT_CLEAR(_PORTS_CHANGE_NOTICE_PULL_DOWN_B_VREG(index) + ((channel-1) * 0x40),
						   bitPos );
}


//******************************************************************************
/* Function :  PORTS_ExistsChangeNoticePullDownPerPort_Default

  Summary:
    Implements Default variant of PLIB_PORTS_ExistsChangeNoticePullDownPerPort

  Description:
    This template implements the Default variant of the PLIB_PORTS_ExistsChangeNoticePullDownPerPort function.
*/

PLIB_TEMPLATE bool PORTS_ExistsChangeNoticePullDownPerPort_Default( PORTS_MODULE_ID index )
{
    return true;
}


#endif /*_PORTS_CHANGENOTICEPULLDOWNPERPORT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

