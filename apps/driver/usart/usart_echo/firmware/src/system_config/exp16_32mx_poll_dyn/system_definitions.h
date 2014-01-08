/*******************************************************************************
  System Definitions

  File Name:
    sys_definitions.h

  Summary:
    Sample application system definitions

  Description:
    This file contains the sample application's system protoypes and definitions.
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

#ifndef _SYS_DEFINITIONS_H
#define _SYS_DEFINITIONS_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/system.h"
#include "driver/usart/drv_usart.h"


// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Sample Application's System Objects

  Summary:
    Structure holding the sample application's system object handles

  Description:
    This structure contains the object handles for all objects in the sample 
    application's system configurtion.

  Remarks:
    These values are returned from the "Initialize" functions for each module.
*/

typedef struct
{
    /* USART driver object handle. */
    SYS_MODULE_OBJ drvUSARTObject;

} APP_DRV_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization and Tasks Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System Initialization Function

  Function:
    void SYS_Initialize( void *data )

  Summary:
    Function that initializes all modules in the system.
    
  Description:
    This function initializes all modules in the system, including any drivers, 
    services, middleware, and applications.

  Precondition:
    None.

  Parameters:
    dat             - Pointer to the data structure containing any data
                      necessary to initialize the module. This pointer may
                      be null if no data is required and default initialization
                      is to be used.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

  Remarks:
    This function will only be called once, after system reset.
*/

void SYS_Initialize( void *data );


// *****************************************************************************
/* System Tasks Function

  Function:
    void SYS_Tasks ( void );

  Summary:
    Function that performs all polled system tasks.

  Description:
    This function performs all polled system tasks by calling the state machine 
    "tasks" functions for all polled modules in the system, including drivers, 
    services, middleware and applications.

  Precondition:
    The SYS_Initialize function must have been called and completed.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize ( NULL );

    while ( true )
    {
        SYS_Tasks ( );
    }
    </code>

  Remarks:
    If the module is interrupt driven, the system will call this routine from
    an interrupt context.
*/

void SYS_Tasks ( void );


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

extern APP_DRV_OBJECTS appDrvObjects;


#endif /* _SYS_DEFINITIONS_H */
/*******************************************************************************
 End of File
*/

