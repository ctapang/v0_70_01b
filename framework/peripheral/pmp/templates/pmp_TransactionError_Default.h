/*******************************************************************************
  PMP Peripheral Library Template Implementation

  File Name:
    pmp_TransactionError_Default.h

  Summary:
    PMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TransactionError
    and its Variant : Default
    For following APIs :
        PLIB_PMP_ExistsTransactionError
        PLIB_PMP_TransactionErrorHasOccurred
        PLIB_PMP_TransactionErrorClear

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

#ifndef _PMP_TRANSACTIONERROR_DEFAULT_H
#define _PMP_TRANSACTIONERROR_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PMP_TRANSACTION_ERROR_VREG(index)

  MASKs: 
    _PMP_TRANSACTION_ERROR_MASK(index)

  POSs: 
    _PMP_TRANSACTION_ERROR_POS(index)

  LENs: 
    _PMP_TRANSACTION_ERROR_LEN(index)

*/


//******************************************************************************
/* Function :  PMP_ExistsTransactionError_Default

  Summary:
    Implements Default variant of PLIB_PMP_ExistsTransactionError

  Description:
    This template implements the Default variant of the PLIB_PMP_ExistsTransactionError function.
*/

PLIB_TEMPLATE bool PMP_ExistsTransactionError_Default( PMP_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PMP_TransactionErrorHasOccurred_Default

  Summary:
    Implements Default variant of PLIB_PMP_TransactionErrorHasOccurred 

  Description:
    This template implements the Default variant of the PLIB_PMP_TransactionErrorHasOccurred function.
*/

PLIB_TEMPLATE bool PMP_TransactionErrorHasOccurred_Default( PMP_MODULE_ID index )
{
    return (_SFR_BIT_READ(
        _PMP_TRANSACTION_ERROR_VREG(index),
        _PMP_TRANSACTION_ERROR_POS(index)
    ));
}


//******************************************************************************
/* Function :  PMP_TransactionErrorClear_Default

  Summary:
    Implements Default variant of PLIB_PMP_TransactionErrorClear 

  Description:
    This template implements the Default variant of the PLIB_PMP_TransactionErrorClear function.
*/

PLIB_TEMPLATE void PMP_TransactionErrorClear_Default( PMP_MODULE_ID index )
{
    _SFR_BIT_CLEAR(
        _PMP_TRANSACTION_ERROR_VREG(index),
        _PMP_TRANSACTION_ERROR_POS(index)
    );
}


#endif /*_PMP_TRANSACTIONERROR_DEFAULT_H*/

/******************************************************************************
 End of File
*/

