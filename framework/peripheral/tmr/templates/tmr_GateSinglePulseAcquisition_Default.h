/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_GateSinglePulseAcquisition_Default.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : GateSinglePulseAcquisition
    and its Variant : Default
    For following APIs :
        PLIB_TMR_GateSinglePulseAcquisitionStart
        PLIB_TMR_GateSinglePulseAcquisitionHasCompleted
        PLIB_TMR_ExistsGateSinglePulseAcqusition

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

#ifndef _TMR_GATESINGLEPULSEACQUISITION_DEFAULT_H
#define _TMR_GATESINGLEPULSEACQUISITION_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_GATE_SINGLE_PULSE_ACQUISITION_VREG(index)

  MASKs: 
    _TMR_GATE_SINGLE_PULSE_ACQUISITION_MASK(index)

  POSs: 
    _TMR_GATE_SINGLE_PULSE_ACQUISITION_POS(index)

  LENs: 
    _TMR_GATE_SINGLE_PULSE_ACQUISITION_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_GateSinglePulseAcquisitionStart_Default

  Summary:
    Implements Default variant of PLIB_TMR_GateSinglePulseAcquisitionStart 

  Description:
    This template implements the Default variant of the PLIB_TMR_GateSinglePulseAcquisitionStart function.
*/

PLIB_TEMPLATE void TMR_GateSinglePulseAcquisitionStart_Default( TMR_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_GateSinglePulseAcquisitionHasCompleted_Default

  Summary:
    Implements Default variant of PLIB_TMR_GateSinglePulseAcquisitionHasCompleted 

  Description:
    This template implements the Default variant of the PLIB_TMR_GateSinglePulseAcquisitionHasCompleted function.
*/

PLIB_TEMPLATE bool TMR_GateSinglePulseAcquisitionHasCompleted_Default( TMR_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_ExistsGateSinglePulseAcqusition_Default

  Summary:
    Implements Default variant of PLIB_TMR_ExistsGateSinglePulseAcqusition

  Description:
    This template implements the Default variant of the PLIB_TMR_ExistsGateSinglePulseAcqusition function.
*/

PLIB_TEMPLATE bool TMR_ExistsGateSinglePulseAcqusition_Default( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_GATESINGLEPULSEACQUISITION_DEFAULT_H*/

/******************************************************************************
 End of File
*/

