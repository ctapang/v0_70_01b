/*******************************************************************************
  ISP Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the Explorer-16 board with PIC32MX795F512L.

  Description:
    This file is the top-level configuration header for the ISP Demo
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
// Section: General System Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Services Configuration
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_CONFIG_USBPLL_ENABLE              true

#define SYS_CLK_PRIMARY_CLOCK                     80000000L

#define SYS_CLK_SECONDARY_CLOCK                   80000000

#define SYS_CLK_CLOCK_CONFIG_ERROR                10

#define SYS_CLK_CONFIG_USBPLL_DIVISOR             2

#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR         2

#define SYS_CLK_CONFIG_SYSCLK_OP_DIVISOR          1

#define SYS_CLK_ON_WAIT_IDLE                      1

#define SYS_CLK_ON_WAIT_SLEEP                     0

#define SYS_CLK_EXTERNAL_CLOCK                    4000000

// *****************************************************************************
// *****************************************************************************
// Section: SPI Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_SPI_INSTANCES_NUMBER                    1

#define DRV_SPI_CLIENTS_NUMBER                      1

#define DRV_SPI_INTERRUPT_MODE                      true

#define DRV_SPI_PORTS_REMAP_USAGE                   false

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

