/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    ADC data logger demo application definitions (advanced driver-based version)

  Description:
    This file contains the ADC data logger demo application definitions for the 
    driver-based version that uses some advanced driver features.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"
#include <xc.h>
#include <sys/attribs.h>

/*****************************************************************************
 * SECTION: MainDemo.h Includes
 *****************************************************************************/
#include "gfx/gfx.h"
#include "gfx/src/common_legacy/SST25VF016.h"
#include "internal_resource.h"
#include "gfx/src/common_legacy/TouchScreen.h"
#include "driver/pmp/drv_pmp.h"



extern uint8_t handle;
extern volatile uint32_t tick; // tick counter

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
	
	/* The application is waiting for the button to be pressed */
    APP_WAIT_FOR_BUTTON_PRESS = 0,
	
	/* button is pressed */
    APP_BUTTON_PRESSED,
	
	/* Button is pressed, print the message */
    APP_PRINT_MESSAGE_BEGIN,

    /* print is initiated */
    APP_WAIT_FOR_PRINT,
	
	/* a charecter is received from host */
    APP_RX_CHAR,

    /* echo the same charecter that is rceived from the host */
    APP_TX_CHAR

} APP_STATES;


// *****************************************************************************
/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

typedef struct
{
    /* device layer object returned by device layer init function */
    SYS_MODULE_OBJ              usbDevObject;

    /* Controller driver object returned by controller driver init function */
    SYS_MODULE_OBJ              usbCDObject;

} APP_DRV_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

/*******************************************************************************
  Function:
    void APP_UsbSetUpFuncDriver(void)

  Summary:
    Opens an instance of CDC.

  Description:
    This routine opens an instance of CDC function driver and registers the
    application callback with the CDC.

  Precondition:
    Device should be in configured state.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void APP_UsbSetUpFuncDriver(void);


/*******************************************************************************
  Function:
    void APP_ProcessSwitchState(void)

  Summary:
    Checks the switch status.

  Description:
    This routine returns the switch(button) status.

  Precondition:
    The button should be configured as digital inputs.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void APP_ProcessSwitchState(void);

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     ADC data logger application initialization routine

  Description:
    This routine initializes ADC data logger application.  This function opens
    the necessary drivers, initializes the timer and registers the application
    callback with the USART driver.

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
    ADC Data Logger application tasks function

  Description:
    This routine is the ADC Data Logger application's tasks function.  It
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

void SYS_Initialize ( void* data );

void SYS_Tasks ( void );


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************
extern APP_DRV_OBJECTS appDrvObject;

extern SYS_MODULE_OBJ object;

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

