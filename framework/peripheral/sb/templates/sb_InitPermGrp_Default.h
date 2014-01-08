/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_InitPermGrp_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : InitPermGrp
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsInitPermGrp
        PLIB_SB_InitPermGrpSet

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

#ifndef _SB_INITPERMGRP_DEFAULT_H
#define _SB_INITPERMGRP_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_CFGPG_CPU_VREG(index)
    _SB_CFGPG_DMA_VREG(index)
    _SB_CFGPG_USB_VREG(index)
    _SB_CFGPG_CAN1_VREG(index)
    _SB_CFGPG_CAN2_VREG(index)
    _SB_CFGPG_ETH_VREG(index)
    _SB_CFGPG_SQI1_VREG(index)
    _SB_CFGPG_FC_VREG(index)

  MASKs: 
    _SB_CFGPG_CPU_MASK(index)
    _SB_CFGPG_DMA_MASK(index)
    _SB_CFGPG_USB_MASK(index)
    _SB_CFGPG_CAN1_MASK(index)
    _SB_CFGPG_CAN2_MASK(index)
    _SB_CFGPG_ETH_MASK(index)
    _SB_CFGPG_SQI1_MASK(index)
    _SB_CFGPG_FC_MASK(index)

  POSs: 
    _SB_CFGPG_CPU_POS(index)
    _SB_CFGPG_DMA_POS(index)
    _SB_CFGPG_USB_POS(index)
    _SB_CFGPG_CAN1_POS(index)
    _SB_CFGPG_CAN2_POS(index)
    _SB_CFGPG_ETH_POS(index)
    _SB_CFGPG_SQI1_POS(index)
    _SB_CFGPG_FC_POS(index)

  LENs: 
    _SB_CFGPG_CPU_LEN(index)
    _SB_CFGPG_DMA_LEN(index)
    _SB_CFGPG_USB_LEN(index)
    _SB_CFGPG_CAN1_LEN(index)
    _SB_CFGPG_CAN2_LEN(index)
    _SB_CFGPG_ETH_LEN(index)
    _SB_CFGPG_SQI1_LEN(index)
    _SB_CFGPG_FC_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsInitPermGrp_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsInitPermGrp

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsInitPermGrp function.
*/

PLIB_TEMPLATE bool SB_ExistsInitPermGrp_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_InitPermGrpSet_Default

  Summary:
    Implements Default variant of PLIB_SB_InitPermGrpSet 

  Description:
    This template implements the Default variant of the PLIB_SB_InitPermGrpSet function.
*/

PLIB_TEMPLATE void SB_InitPermGrpSet_Default( SB_MODULE_ID index , PLIB_SB_PG_INITIATOR initiator , PLIB_SB_INIT_PG pg )
{
    switch (initiator) {
        case PLIB_SB_PG_INITIATOR_CPU:
            _SFR_FIELD_WRITE(_SB_CFGPG_CPU_VREG(index), _SB_CFGPG_CPU_MASK(index), _SB_CFGPG_CPU_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_DMA1:
            _SFR_FIELD_WRITE(_SB_CFGPG_DMA_VREG(index), _SB_CFGPG_DMA_MASK(index), _SB_CFGPG_DMA_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_USB1:
            _SFR_FIELD_WRITE(_SB_CFGPG_USB_VREG(index), _SB_CFGPG_USB_MASK(index), _SB_CFGPG_USB_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_CAN1:
            _SFR_FIELD_WRITE(_SB_CFGPG_CAN1_VREG(index), _SB_CFGPG_CAN1_MASK(index), _SB_CFGPG_CAN1_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_CAN2:
            _SFR_FIELD_WRITE(_SB_CFGPG_CAN2_VREG(index), _SB_CFGPG_CAN2_MASK(index), _SB_CFGPG_CAN2_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_ETH1:
            _SFR_FIELD_WRITE(_SB_CFGPG_ETH_VREG(index), _SB_CFGPG_ETH_MASK(index), _SB_CFGPG_ETH_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_SQI1:
            _SFR_FIELD_WRITE(_SB_CFGPG_SQI1_VREG(index), _SB_CFGPG_SQI1_MASK(index), _SB_CFGPG_SQI1_POS(index), pg);
            break;
        case PLIB_SB_PG_INITIATOR_FLASH_CTL:
            _SFR_FIELD_WRITE(_SB_CFGPG_FC_VREG(index), _SB_CFGPG_FC_MASK(index), _SB_CFGPG_FC_POS(index), pg);
            break;
        default:
            break;
    }
    
}


#endif /*_SB_INITPERMGRP_DEFAULT_H*/

/******************************************************************************
 End of File
*/

