/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_MemoryTimingConfig_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemoryTimingConfig
    and its Variant : Default
    For following APIs :
        PLIB_EBI_MemoryTimingConfigSet
        PLIB_EBI_ExistsMemoryTimingConfig

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

#ifndef _EBI_MEMORYTIMINGCONFIG_DEFAULT_H
#define _EBI_MEMORYTIMINGCONFIG_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_TPRC0_VREG(index)
    _EBI_TBTA0_VREG(index)
    _EBI_TWP0_VREG(index)
    _EBI_TWR0_VREG(index)
    _EBI_TAS0_VREG(index)
    _EBI_TRC0_VREG(index)
    _EBI_TPRC1_VREG(index)
    _EBI_TBTA1_VREG(index)
    _EBI_TWP1_VREG(index)
    _EBI_TWR1_VREG(index)
    _EBI_TAS1_VREG(index)
    _EBI_TRC1_VREG(index)
    _EBI_TPRC2_VREG(index)
    _EBI_TBTA2_VREG(index)
    _EBI_TWP2_VREG(index)
    _EBI_TWR2_VREG(index)
    _EBI_TAS2_VREG(index)
    _EBI_TRC2_VREG(index)

  MASKs: 
    _EBI_TPRC0_MASK(index)
    _EBI_TBTA0_MASK(index)
    _EBI_TWP0_MASK(index)
    _EBI_TWR0_MASK(index)
    _EBI_TAS0_MASK(index)
    _EBI_TRC0_MASK(index)
    _EBI_TPRC1_MASK(index)
    _EBI_TBTA1_MASK(index)
    _EBI_TWP1_MASK(index)
    _EBI_TWR1_MASK(index)
    _EBI_TAS1_MASK(index)
    _EBI_TRC1_MASK(index)
    _EBI_TPRC2_MASK(index)
    _EBI_TBTA2_MASK(index)
    _EBI_TWP2_MASK(index)
    _EBI_TWR2_MASK(index)
    _EBI_TAS2_MASK(index)
    _EBI_TRC2_MASK(index)

  POSs: 
    _EBI_TPRC0_POS(index)
    _EBI_TBTA0_POS(index)
    _EBI_TWP0_POS(index)
    _EBI_TWR0_POS(index)
    _EBI_TAS0_POS(index)
    _EBI_TRC0_POS(index)
    _EBI_TPRC1_POS(index)
    _EBI_TBTA1_POS(index)
    _EBI_TWP1_POS(index)
    _EBI_TWR1_POS(index)
    _EBI_TAS1_POS(index)
    _EBI_TRC1_POS(index)
    _EBI_TPRC2_POS(index)
    _EBI_TBTA2_POS(index)
    _EBI_TWP2_POS(index)
    _EBI_TWR2_POS(index)
    _EBI_TAS2_POS(index)
    _EBI_TRC2_POS(index)

  LENs: 
    _EBI_TPRC0_LEN(index)
    _EBI_TBTA0_LEN(index)
    _EBI_TWP0_LEN(index)
    _EBI_TWR0_LEN(index)
    _EBI_TAS0_LEN(index)
    _EBI_TRC0_LEN(index)
    _EBI_TPRC1_LEN(index)
    _EBI_TBTA1_LEN(index)
    _EBI_TWP1_LEN(index)
    _EBI_TWR1_LEN(index)
    _EBI_TAS1_LEN(index)
    _EBI_TRC1_LEN(index)
    _EBI_TPRC2_LEN(index)
    _EBI_TBTA2_LEN(index)
    _EBI_TWP2_LEN(index)
    _EBI_TWR2_LEN(index)
    _EBI_TAS2_LEN(index)
    _EBI_TRC2_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_MemoryTimingConfigSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemoryTimingConfigSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemoryTimingConfigSet function.
*/

PLIB_TEMPLATE void EBI_MemoryTimingConfigSet_Default( EBI_MODULE_ID index , int CS_Timing_Reg , int PageReadTime , int  DataTurnAroundTime , int WritePulseWidth , int AddressHoldTime , int AddressSetupTime , int ReadCycleTime )
{
        switch (CS_Timing_Reg)
	{
	case 0:
	_SFR_FIELD_WRITE(_EBI_TPRC0_VREG(index), _EBI_TPRC0_MASK(index), _EBI_TPRC0_POS(index), PageReadTime);
	_SFR_FIELD_WRITE(_EBI_TBTA0_VREG(index), _EBI_TBTA0_MASK(index), _EBI_TBTA0_POS(index), DataTurnAroundTime);
	_SFR_FIELD_WRITE(_EBI_TWP0_VREG(index), _EBI_TWP0_MASK(index), _EBI_TWP0_POS(index), WritePulseWidth);
	_SFR_FIELD_WRITE(_EBI_TWR0_VREG(index), _EBI_TWR0_MASK(index), _EBI_TWR0_POS(index), AddressHoldTime);
	_SFR_FIELD_WRITE(_EBI_TAS0_VREG(index), _EBI_TAS0_MASK(index), _EBI_TAS0_POS(index), AddressSetupTime);
	_SFR_FIELD_WRITE(_EBI_TRC0_VREG(index), _EBI_TRC0_MASK(index), _EBI_TRC0_POS(index), ReadCycleTime);
	break;

	case 1:
	_SFR_FIELD_WRITE(_EBI_TPRC1_VREG(index), _EBI_TPRC1_MASK(index), _EBI_TPRC1_POS(index), PageReadTime);
	_SFR_FIELD_WRITE(_EBI_TBTA1_VREG(index), _EBI_TBTA1_MASK(index), _EBI_TBTA1_POS(index), DataTurnAroundTime);
	_SFR_FIELD_WRITE(_EBI_TWP1_VREG(index), _EBI_TWP1_MASK(index), _EBI_TWP1_POS(index), WritePulseWidth);
	_SFR_FIELD_WRITE(_EBI_TWR1_VREG(index), _EBI_TWR1_MASK(index), _EBI_TWR1_POS(index), AddressHoldTime);
	_SFR_FIELD_WRITE(_EBI_TAS1_VREG(index), _EBI_TAS1_MASK(index), _EBI_TAS1_POS(index), AddressSetupTime);
	_SFR_FIELD_WRITE(_EBI_TRC1_VREG(index), _EBI_TRC1_MASK(index), _EBI_TRC1_POS(index), ReadCycleTime);
	break;

	case 2:
	_SFR_FIELD_WRITE(_EBI_TPRC2_VREG(index), _EBI_TPRC2_MASK(index), _EBI_TPRC2_POS(index), PageReadTime);
	_SFR_FIELD_WRITE(_EBI_TBTA2_VREG(index), _EBI_TBTA2_MASK(index), _EBI_TBTA2_POS(index), DataTurnAroundTime);
	_SFR_FIELD_WRITE(_EBI_TWP2_VREG(index), _EBI_TWP2_MASK(index), _EBI_TWP2_POS(index), WritePulseWidth);
	_SFR_FIELD_WRITE(_EBI_TWR2_VREG(index), _EBI_TWR2_MASK(index), _EBI_TWR2_POS(index), AddressHoldTime);
	_SFR_FIELD_WRITE(_EBI_TAS2_VREG(index), _EBI_TAS2_MASK(index), _EBI_TAS2_POS(index), AddressSetupTime);
	_SFR_FIELD_WRITE(_EBI_TRC2_VREG(index), _EBI_TRC2_MASK(index), _EBI_TRC2_POS(index), ReadCycleTime);
	break;
	
	default:
        PLIB_ASSERT(false,"Chip Select Number is Invalid, Check input arguments");
	break;
	}

}


//******************************************************************************
/* Function :  EBI_ExistsMemoryTimingConfig_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsMemoryTimingConfig

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsMemoryTimingConfig function.
*/

PLIB_TEMPLATE bool EBI_ExistsMemoryTimingConfig_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_MEMORYTIMINGCONFIG_DEFAULT_H*/

/******************************************************************************
 End of File
*/

