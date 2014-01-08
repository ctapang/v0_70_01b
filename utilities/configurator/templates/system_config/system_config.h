/*******************************************************************************
  MPLAB Harmony Demo Configuration Header

  Company:
    Microchip Technology Incorporated

  File Name:
    system_config.h

  Summary:
    Top-level configuration header file.

  Description:
    This file is the top-level configuration header for the Harmony Demo
    application for the Explorer-16 board with PIC32MX795F512L.
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

#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H

<#if harmony_gfx_SYS_Config_Macros?has_content>
	<#list harmony_gfx_SYS_Config_Macros as func>
		${func}
	</#list>
</#if>

<#if usb_host_system_config_h?has_content>
<#list usb_host_system_config_h as func>
${func}
</#list>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

<#if fs_macros_sys_conf?has_content>
<#list fs_macros_sys_conf as func>
${func}
</#list>
</#if>


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

<#if harmony_usb_hid_device_config?has_content>
<#list harmony_usb_hid_device_config as func>
${func}
</#list>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: System Clock Service Configuration
// *****************************************************************************
// *****************************************************************************

<#if fs_clock_macros_sys_conf?has_content>
<#list fs_clock_macros_sys_conf as func>
${func}
</#list>
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: System Timer Service Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: OSAL Configuration
// *****************************************************************************
// *****************************************************************************
<#if osal_use_rtos_none_sysconf_h?has_content>
<#list osal_use_rtos_none_sysconf_h as func>
${func}
</#list>
</#if>

<#if osal_use_rtos_basic_sysconf_h?has_content>
<#list osal_use_rtos_basic_sysconf_h as func>
${func}
</#list>
</#if>

<#if osal_use_rtos_sysconf_h?has_content>
<#list osal_use_rtos_sysconf_h as func>
${func}
</#list>
</#if>

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

