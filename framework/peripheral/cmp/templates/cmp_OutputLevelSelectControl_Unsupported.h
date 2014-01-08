/*******************************************************************************
  CMP Peripheral Library Template Implementation

  File Name:
    cmp_OutputLevelSelectControl_Unsupported.h

  Summary:
    CMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : OutputLevelSelectControl
    and its Variant : Unsupported
    For following APIs :
        PLIB_CMP_ExistsOutputLevelControl
        PLIB_CMP_OutputHighSelect
        PLIB_CMP_OutputLowSelect
        PLIB_CMP_Cmp1OutputHighSelect
        PLIB_CMP_Cmp1OutputLowSelect
        PLIB_CMP_Cmp2OutputHighSelect
        PLIB_CMP_Cmp2OutputLowSelect

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

#ifndef _CMP_OUTPUTLEVELSELECTCONTROL_UNSUPPORTED_H
#define _CMP_OUTPUTLEVELSELECTCONTROL_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  CMP_ExistsOutputLevelControl_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_ExistsOutputLevelControl

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_ExistsOutputLevelControl function.
*/

PLIB_TEMPLATE bool CMP_ExistsOutputLevelControl_Unsupported( CMP_MODULE_ID index )
{
    return false;
}


//******************************************************************************
/* Function :  CMP_OutputHighSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_OutputHighSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_OutputHighSelect function.
*/

PLIB_TEMPLATE void CMP_OutputHighSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_OutputHighSelect");
}


//******************************************************************************
/* Function :  CMP_OutputLowSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_OutputLowSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_OutputLowSelect function.
*/

PLIB_TEMPLATE void CMP_OutputLowSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_OutputLowSelect");
}


//******************************************************************************
/* Function :  CMP_Cmp1OutputHighSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_Cmp1OutputHighSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_Cmp1OutputHighSelect function.
*/

PLIB_TEMPLATE void CMP_Cmp1OutputHighSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_Cmp1OutputHighSelect");
}


//******************************************************************************
/* Function :  CMP_Cmp1OutputLowSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_Cmp1OutputLowSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_Cmp1OutputLowSelect function.
*/

PLIB_TEMPLATE void CMP_Cmp1OutputLowSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_Cmp1OutputLowSelect");
}


//******************************************************************************
/* Function :  CMP_Cmp2OutputHighSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_Cmp2OutputHighSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_Cmp2OutputHighSelect function.
*/

PLIB_TEMPLATE void CMP_Cmp2OutputHighSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_Cmp2OutputHighSelect");
}


//******************************************************************************
/* Function :  CMP_Cmp2OutputLowSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_CMP_Cmp2OutputLowSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_CMP_Cmp2OutputLowSelect function.
*/

PLIB_TEMPLATE void CMP_Cmp2OutputLowSelect_Unsupported( CMP_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_CMP_Cmp2OutputLowSelect");
}


#endif /*_CMP_OUTPUTLEVELSELECTCONTROL_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

