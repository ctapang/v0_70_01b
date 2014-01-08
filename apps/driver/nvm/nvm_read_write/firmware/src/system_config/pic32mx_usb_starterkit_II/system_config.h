/*******************************************************************************
    NVM FAT Single Disk Demo Configuration File
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for NVM FAT Single Disk
    application for the PIC32 USB starter kit.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
// Section: Constants
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: NVM Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* NVM Driver setup for interrupt mode */
#define DRV_NVM_INTERRUPT_MODE true

/* NVM Driver will support one instance */
#define DRV_NVM_INSTANCES_NUMBER 1

/* NVM Driver will have only one client */
#define DRV_NVM_CLIENTS_NUMBER 1

/* NVM Driver can support upto five data
 * requests */
#define DRV_NVM_BUFFER_OBJECT_NUMBER 5

/* NVM Driver Flash Memory row size
 * in bytes */
#define DRV_NVM_ROW_SIZE 512

/* NVM Driver Flash Memory page size
 * in bytes */
#define DRV_NVM_PAGE_SIZE 4096

/*NVM Base Address*/
#define     NVM_BASE_ADDRESS                0x9D004000

/* NVM Driver Flash Memory programming
 * key 1*/

#define DRV_NVM_PROGRAM_UNLOCK_KEY1 0xAA996655

/* NVM Driver Flash Memory programming
 * key 1*/

#define DRV_NVM_PROGRAM_UNLOCK_KEY2 0x556699AA

#define BSP_SwitchONSuccessLED()            BSP_SwitchONLED(LED_2)

#define BSP_SwitchONFailureLED()            BSP_SwitchONLED(LED_1)

#endif

/*******************************************************************************
 End of File
*/

