/*******************************************************************************
  ADC Driver build variant implementation for single client 

  Company:    
    Microchip Technology Inc.

  File Name:  
    drv_adc_client_static.h

  Summary:
    ADC Driver build variant implementation for single client.

  Description:
    This file defines the build variant implementations for the single client.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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


#ifndef _DRV_ADC_CLIENT_SINGLE_H
#define _DRV_ADC_CLIENT_SINGLE_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "../drv_adc_local.h"


// *****************************************************************************
/* Macro: _DRV_ADC_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member.

  Description:
    This macro either returns the static object or the indexed dynamic object.
    This macro has variations for dynamic or static drivers.

*/

#define _DRV_ADC_CLIENT_OBJ(obj,mem)                        _DRV_ADC_OBJ_MAKE_NAME(gDrvADCClientObj).mem


// *****************************************************************************
/* Macro: _DRV_ADC_MC( statement )

  Summary:
    Allows removal of code statements only needed for multi-client configurations.

  Description:
    This macro allows removal of code statements that are only needed for
    multi-client configurations.

  Remarks:
    Do not put multiple statements or compound statements within this macro.
    The statement must not include a comma (,).
*/

#define _DRV_ADC_MC(statement)


// *****************************************************************************
/* Macro: _DRV_ADC_MC_ARG( arg )

  Summary:
    Allows removal of function arguments only needed for multi-client configurations.

  Description:
    This macro allows removal of function arguments that are only needed for
    multi-client configurations.

  Remarks:
    This macro is only for single or Right-most arguments in a function's formal
    parameter list.
*/

#define _DRV_ADC_MC_ARG(arg)


// *****************************************************************************
/* Macro: _DRV_ADC_MC_ARG_COMMA(arg)

  Summary:
    Allows removal of multiple function arguments only needed for multi-client
    configurations.

  Description:
    This macro allows removal of multiple function arguments that are only
    needed for multi-client configurations.

  Remarks:
    This macro is only for use on arguments that preceed (or are to the Left of)
    other arguments in a function's formal parameter list because it embeds a
    comma (,) at the end of the argument declaration.
*/

#define _DRV_ADC_MC_ARG_COMMA(arg)


// *****************************************************************************
/* Macro: _DRV_ADC_MC_RETURN_TYPE(type)

  Summary:
    Multi client return type.

  Description:
    Multi-client interface return type, single client voids out and multi-client
    returns the client handle

*/

#define _DRV_ADC_MC_RETURN_TYPE(type)           void


// *****************************************************************************
/* Macro: _DRV_ADC_MC_RETURN(handle)

  Summary:
    Switches "return(handle)" statements needed in multi-client builds to just
    "return" in single client builds.

  Description:
    This macro switches "return(handle)" statements needed in multi-client builds
    to  just "return" in single client builds.

*/

#define _DRV_ADC_MC_RETURN(handle)       return


// *****************************************************************************
/* Macro: _DRV_ADC_MC_Test(c)

  Summary:
    Macro to check for exclusive access.

  Description:
    This macro checks for exclusive access.

*/

#define  _DRV_ADC_MC_Test(c)    true


#endif // _DRV_ADC_CLIENT_SINGLE_H

/*******************************************************************************
 End of File
*/
