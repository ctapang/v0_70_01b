/*******************************************************************************
 System Tasks File

  File Name:
    system_tasks.c

  Summary:
    System tasks File.

  Description:
    This file will contain any source code necessary to maintain various tasks
    in the system.
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


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Summary:
    Calls all module-specific "tasks" routines to maintain module state

  Description:
    This routine calls all module-specific "tasks" routines to maintain module
    state.

  Precondition:
    SYS_Initialize has been called

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    int main ( void )
    {
        SYS_Initialize(&initData);

        while (true)
        {
            SYS_Tasks();
        }
    }
    </code>

  Remarks:
    When not using the dynamic system "Tasks" service, this routine must be
    implemented by the application's system configuration (in the application's
    configuration-specific "sys_tasks.c" file).
 */
void SYS_Tasks ( void )
{
    // TODO call task routines for the Harmony drivers and middleware
	/* TODO For Graphics Stack. In the future releases, the tool would add required task API's appropriately.

		  GFX_OBJ_Tasks(); // Draw GOL objects
		  GFX_PRIM_Tasks();
		  GFX_DRV_lcc_Tasks();
		  GFX_DRV_SSD1926_Tasks();
		  GFX_DRV_S1D13517_Tasks();
	*/
	
	/* TODO For USB Stack. In the future releases, the tool would add required task API's appropriately.

		USB_DEVICE_Tasks( );

		USB_HOST_HUB_task();

		USB_HOST_CDC_Tasks();
	*/

<#if fs_sys_tasks_sys_task?has_content>
    <#list fs_sys_tasks_sys_task as func>
        ${func}
    </#list>
</#if>

	/* TODO For TCPIP Stack. In the future releases, the tool would add required task API's appropriately.

			TCPIP_STACK_Task();

			//If the macro TCPIP_STACK_USE_DHCP_CLIENT is defined
			TCPIP_DHCP_Task( );

			//If the macro TCPIP_STACK_USE_UDP is defined
			TCPIP_UDP_Task( );
	*/
 <#if harmony_sys_tasks?has_content>
    <#list harmony_sys_tasks as func>
        ${func}
    </#list>
 </#if>

    /* Call the application's tasks routine */
    APP_Tasks ( );
}


/*******************************************************************************
 End of File
 */
