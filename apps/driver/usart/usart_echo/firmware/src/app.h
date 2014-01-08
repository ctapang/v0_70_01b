/*******************************************************************************
  Sample Application Header

  File Name:
    app.h

  Summary:
    Sample application definitions and prototypes

  Description:
    This file contains the sample application's definitions and prototypes.
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

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "bsp_config.h"
#include "system_definitions.h"
#include "system/system.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum
{
    /* In this state, the application opens the driver. */
    APP_INIT,

    /* The application waits in this state for the driver to be ready
       before sending the "hello world" message. */
    APP_WAIT_FOR_READY,

    /* The application waits in this state for the driver to finish
       sending/receiving the mesage. */
    APP_WAIT_FOR_DONE,

    /* The application does nothing in the idle state. */
    APP_IDLE,

    /* This state indicates an error has occured. */
    APP_ERROR,

} APP_STATES;

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states will
    update the APP_STATES state machine and configure the driver in appropriate
    mode.
*/

typedef enum
{
    /* This state will load the buffer with APP_MSG_1 message. */
    APP_DISP_MSG_1,

    /* This state will load the buffer with APP_MSG_2 message. */
    APP_DISP_MSG_2,

    /* This state will load the buffer with APP_MSG_3 message. */
    APP_DISP_MSG_3,

    /* This state will load the buffer with APP_MSG_4 message. */
    APP_DISP_MSG_4,

    /* This state will load the buffer with APP_MSG_5 message. */
    APP_DISP_MSG_5,

    /* This state will configure the driver in read mode */
    APP_RX_DATA,

    /* This state will configure the driver in write mode */
    APP_TX_DATA,

    /* The application does nothing in the idle state. */
    APP_DEMO_COMPLETE

} APP_DEMO_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* Application current state */
    APP_STATES state;

    /* USART buffer for display */
    char buffer[APP_BUFFER_SIZE];

    /* Structure used to transfer buffer via USART driver. */
    DRV_USART_IO_BUFFER bufferObject;

    /* USART driver handle */
    DRV_HANDLE usartHandle;

    /* Handle returned by USART for buffer submitted */
    DRV_HANDLE usartBufferHandle;

    /*States to control the application state machine and configuring the driver*/
    APP_DEMO_STATES demoState;

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     Sample application's initialization routine

  Description:
    This routine initializes sample application's state machine.
    
  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    Demo application tasks function

  Description:
    This routine is the demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks ( void );

/*******************************************************************************
  Function:
    void UpdateTaskState ( void )

  Summary:
    Updates the application's state

  Description:
    This routine updates the application's state. It also loads appropriate
    message into the buffer. This routine is also used to swtch the driver
    between read and write modes.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>
    UpdateTaskState();

  Remarks:
    This routine must be called after every successful data transfer to update
    the application's state machine.
 */

void UpdateTaskState ( void );

#endif /* _APP_HEADER_H */
/*******************************************************************************
 End of File
*/

