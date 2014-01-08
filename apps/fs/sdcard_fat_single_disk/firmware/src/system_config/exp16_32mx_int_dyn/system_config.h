/*******************************************************************************
    SDCARD FAT Single Disk Demo Configuration File
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for SDCARD FAT Single Disk
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
// Section: SPI Driver Configuration
// *****************************************************************************
// *****************************************************************************


/* Number of driver instances */
#define DRV_SPI_INSTANCES_NUMBER                    		1

/* Number of client to be supported */
#define DRV_SPI_CLIENTS_NUMBER                      		1

/* Driver will work in polling mode */
#define DRV_SPI_INTERRUPT_MODE                      true

#define DRV_SPI_PORTS_REMAP_USAGE                   false

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

#define DRV_SPI_PERIPHERAL_ID                       SPI_ID_1

// *****************************************************************************
// *****************************************************************************
// Section: SDCARD Driver Configuration
// *****************************************************************************
// *****************************************************************************
#define DRV_SDCARD_INSTANCES_NUMBER                             1
#define DRV_SDCARD_CLIENTS_NUMBER                               1
#define DRV_SDCARD_INDEX_MAX                                    1
#define DRV_SDCARD_INDEX                                        DRV_SDCARD_INDEX_0
#define DRV_SDCARD_QUEUE_POOL_SIZE                              10
/* Defines if the card detect logic as designed in hardware */
#define DRV_SDCARD_CD_LOGIC_ACTIVE_LOW

// *****************************************************************************
// *****************************************************************************
// Section: Media Manager Configuration
// *****************************************************************************
// *****************************************************************************
/* Max Number of media used in the demo */
#define SYS_FS_MEDIA_NUMBER 1
/* Max Number of volumes to be allocated  */
#define SYS_FS_VOLUME_NUMBER    1


// *****************************************************************************
// *****************************************************************************
// Section: Clock Configuration
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL )     80000000


// *****************************************************************************
// *****************************************************************************
// Section: SYS FS Configuration
// *****************************************************************************
// *****************************************************************************

/* Max Number of file system to be supported for the demo */
#define SYS_FS_MAX_FILE_SYSTEM_TYPE     1

/* Max Number of files that will be opened at a time */
#define SYS_FS_MAX_FILES    2

// *****************************************************************************
// *****************************************************************************
// Section: LED Configuration for success and failure
// *****************************************************************************
// *****************************************************************************

#define BSP_SwitchONSuccessLED()            BSP_SwitchONLED(LED_5)

#define BSP_SwitchONFailureLED()            BSP_SwitchONLED(LED_6)


#endif

/*******************************************************************************
 End of File
*/

