/*******************************************************************************
  Timer System Service Configuration Definitions for the Template Version

  Company:
    Microchip Technology Inc.

  File Name:
    sys_tmr_config.h

  Summary:
    Contains configuration definitions that are common to timer system services
    and aggregrates the configuration files for the system services.

  Description:
    This file contains configuration definitions that are common to timer drivers
    and aggregrates the configuration files for the system services.

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


#ifndef _SYS_TMR_CONFIG_TEMPLATE_H
#define _SYS_TMR_CONFIG_TEMPLATE_H


#error "This is a configuration template file.  Do not include it directly."


// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Maximum periodic events configuration

  Summary:
    Sets the maximum periodic multi-event callbacks supported.

  Description:
    This macro sets the maximum periodic multi-event callbacks.

  Remarks:
    This requires multiple periodic events enabled through the switch
    SYS_TMR_SINGLE_PERIODIC_EVENT.
*/

#define SYS_TMR_MAX_PERIODIC_EVENTS                                 5


// *****************************************************************************
/* Periodic event type configuration

  Summary:
    Sets the type of the periodic event.

  Description:
    This macro sets the type of the periodic event, which can accept the following
    values:
        - true  - Single periodic event
        - false - Multiple periodic events

  Remarks:
    If multiple periodic events are enabled, the switch SYS_TMR_MAX_PERIODIC_EVENTS
    has to be configured to support the maximum permitted events.
*/

#define SYS_TMR_SINGLE_PERIODIC_EVENT                               true


// *****************************************************************************
/* Error Tolerance configuration

  Summary:
    Sets the error tolerance in milliseconds.

  Description:
    This macro sets the error tolerance in milliseconds with reference to the configured
    alarm period of the timer driver.

  Remarks:
    None.
*/

#define SYS_TMR_ERROR_TOLERANCE                                     0


// *****************************************************************************
/* Interrupt Mode configuration

  Summary:
    Activates the Interrupt mode.

  Description:
    This macro sets up the interrupt mode, which can accept the following values:
        - true  - Interrupt mode
        - false - No Interrupt mode

  Remarks:
    The delay feature works only if the Interrupt mode is set to 'true' and the 
    respective Timer has been configured for Interrupt mode. This feature has 
    been designed to provide a non-blocking delay.
*/

#define SYS_TMR_INTERRUPT_MODE                                      false


#endif // _SYS_TMR_CONFIG_TEMPLATE_H

/*******************************************************************************
 End of File
*/

