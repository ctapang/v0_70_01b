/*******************************************************************************
  MPLAB Harmony Application 
  
  File Name:
    app.c

  Summary:
    Application Template

  Description:
    This file contains the application logic.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
<#if harmony_gfx_appC_include?has_content>
<#list harmony_gfx_appC_include as func>
${func}
</#list>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************


/*****************************************************
 * Initialize the application data structure. All
 * application related variables are stored in this
 * data structure.
 *****************************************************/

APP_DATA appData = 
{
    //TODO - Initialize appData structure. 

};
// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/


APP_DRV_OBJECTS appDrvObject;

<#if usb_code_app_c?has_content>
        <#list usb_code_app_c as func>
            ${func}
        </#list>
 </#if>
 
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */

    /* Place the App state machine in it's initial state. */
    appData.state = APP_STATE_INIT;
<#if usb_init_code_app_c?has_content>
	<#list usb_init_code_app_c as func>
    ${func}
	</#list>
</#if>

<#if harmony_gfx_Initialize?has_content>
	<#list harmony_gfx_Initialize as func>
    ${func}
	</#list>
</#if>
	
}

/********************************************************
 * Application switch press routine
 ********************************************************/



/**********************************************************
 * Application tasks routine. This function implements the
 * application state machine.
 ***********************************************************/
void APP_Tasks ( void )
{
    /* check the application state*/
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
            break;

        // TODO implement your application statemachine
<#if fs_switch_case_app_c?has_content>
 	<#list fs_switch_case_app_c as func>
 		${func}
 	</#list>       
</#if>
        /* The default state should never be executed. */
        default:
            /* TODO: Handle error in application's state machine. */
            break;

    }


   
} 

/*******************************************************************************
 End of File
 */

