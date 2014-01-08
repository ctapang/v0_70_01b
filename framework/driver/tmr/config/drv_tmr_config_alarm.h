/*******************************************************************************
  TMR Driver Configuration Definitions for Alarm feature

  Company:
    Microchip Technology Inc.

  File Name:
    drv_tmr_config_alarm.h

  Summary:
    Timer driver configuration definitions for the alarm feature.

  Description:
     These definitions set up the driver for the alarm feature.
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

#ifndef _DRV_TMR_CONFIG_ALARM_H
#define _DRV_TMR_CONFIG_ALARM_H

// *****************************************************************************
/* Selecting the alarm functionality

  Summary:
    Enables alarm functionality.

  Description:
    This feature enables the alarm functionality inside the Timer driver.

  Remarks:
    This is an additional feature. If the user wants to be called after a time
    elapse, alarm callback registration is mandatory.
*/

#define DRV_TMR_ALARM_ENABLE


// *****************************************************************************
/* Alarm type configuration option

  Summary:
    Sets the alarm type configuration.

  Description:
    This macro set the alram type to alarm periodic.

  Remarks:
    To make the alarm as one-shot set the following macro as false.
*/

#define DRV_TMR_ALARM_PERIODIC               true


#endif // #ifndef _DRV_TMR_CONFIG_ALARM_H

/*******************************************************************************
 End of File
*/
