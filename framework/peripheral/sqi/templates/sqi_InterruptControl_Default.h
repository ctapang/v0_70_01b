/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_InterruptControl_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : InterruptControl
    and its Variant : Default
    For following APIs :
        PLIB_SQI_InterruptEnable
        PLIB_SQI_InterruptDisable
        PLIB_SQI_InterruptIsEnabled
        PLIB_SQI_ExistsInterruptControl

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

#ifndef _SQI_INTERRUPTCONTROL_DEFAULT_H
#define _SQI_INTERRUPTCONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_INTERRUPT_ENABLE_VAL_VREG(index)

  MASKs:
    _SQI_INTERRUPT_ENABLE_VAL_MASK(index)

  POSs:
    _SQI_INTERRUPT_ENABLE_VAL_POS(index)

  LENs:
    _SQI_INTERRUPT_ENABLE_VAL_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_InterruptEnable_Default

  Summary:
    Implements Default variant of PLIB_SQI_InterruptEnable

  Description:
    This template implements the Default variant of the PLIB_SQI_InterruptEnable function.
*/

PLIB_TEMPLATE void SQI_InterruptEnable_Default( SQI_MODULE_ID index , SQI_INTERRUPTS interruptFlag )
{
	switch (interruptFlag)
	{
		case SQI_PKTCOMP:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 10);
		break;
		case SQI_BDDONE:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 9);
		break;
		case SQI_CONTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 8);
		break;
		case SQI_CONEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 7);
		break;
		case SQI_CONFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 6);
		break;
		case SQI_RXTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 5);
		break;
		case SQI_RXEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 4);
		break;
		case SQI_RXFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 3);
		break;
		case SQI_TXTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 2);
		break;
		case SQI_TXEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 1);
		break;
		case SQI_TXFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							1 << 0);
		break;
		case SQI_ALL_INT:
			_SFR_FIELD_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							  _SQI_INTERRUPT_ENABLE_VAL_MASK(index),
							  _SQI_INTERRUPT_ENABLE_VAL_POS(index),
							  0x7FF);
		break;
		default:
			_SFR_FIELD_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							  _SQI_INTERRUPT_ENABLE_VAL_MASK(index),
							  _SQI_INTERRUPT_ENABLE_VAL_POS(index),
							  0x7FF);
	}
}


//******************************************************************************
/* Function :  SQI_InterruptDisable_Default

  Summary:
    Implements Default variant of PLIB_SQI_InterruptDisable

  Description:
    This template implements the Default variant of the PLIB_SQI_InterruptDisable function.
*/

PLIB_TEMPLATE void SQI_InterruptDisable_Default( SQI_MODULE_ID index , SQI_INTERRUPTS interruptFlag )
{
	switch (interruptFlag)
	{
		case SQI_PKTCOMP:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 10);
		break;
		case SQI_BDDONE:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 9);
		break;
		case SQI_CONTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 8);
		break;
		case SQI_CONEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 7);
		break;
		case SQI_CONFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 6);
		break;
		case SQI_RXTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 5);
		break;
		case SQI_RXEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 4);
		break;
		case SQI_RXFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 3);
		break;
		case SQI_TXTHR:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 2);
		break;
		case SQI_TXEMPTY:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 1);
		break;
		case SQI_TXFULL:
			_SFR_BIT_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							_SQI_INTERRUPT_ENABLE_VAL_POS(index),
							0 << 0);
		break;
		case SQI_ALL_INT:
			_SFR_FIELD_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							  _SQI_INTERRUPT_ENABLE_VAL_MASK(index),
							  _SQI_INTERRUPT_ENABLE_VAL_POS(index),
							  0);
		break;
		default:
			_SFR_FIELD_WRITE (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
							  _SQI_INTERRUPT_ENABLE_VAL_MASK(index),
							  _SQI_INTERRUPT_ENABLE_VAL_POS(index),
							  0);
	}
}


//******************************************************************************
/* Function :  SQI_InterruptIsEnabled_Default

  Summary:
    Implements Default variant of PLIB_SQI_InterruptIsEnabled

  Description:
    This template implements the Default variant of the PLIB_SQI_InterruptIsEnabled function.
*/

PLIB_TEMPLATE bool SQI_InterruptIsEnabled_Default( SQI_MODULE_ID index , SQI_INTERRUPTS interruptFlag )
{
    return (bool) _SFR_BIT_READ (_SQI_INTERRUPT_ENABLE_VAL_VREG(index),
								 _SQI_INTERRUPT_ENABLE_VAL_POS(index)<<interruptFlag);
}


//******************************************************************************
/* Function :  SQI_ExistsInterruptControl_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsInterruptControl

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsInterruptControl function.
*/

PLIB_TEMPLATE bool SQI_ExistsInterruptControl_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_INTERRUPTCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

