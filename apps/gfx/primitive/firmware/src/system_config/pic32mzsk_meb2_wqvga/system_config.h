/*******************************************************************************
  GFX Primitive Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the GFX Primitive Application.

  Description:
    This file is the top-level configuration header for the Primitive demo
    application which runs on the PIC32 MEB2 board.
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

//PICTail
#define MEB_2_BOARD
#define GFX_PICTAIL_LCC

//PIC Interface
#define PIC_SK

//Graphics Controller
#define GFX_USE_DISPLAY_CONTROLLER_LCC

//Display
#define GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q

//LCC Specific
#define LCC_INTERNAL_MEMORY


//GFX
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

#define GFX_CONFIG_COLOR_DEPTH              (16)
#define GFX_CONFIG_FONT_CHAR_SIZE           (8)
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_GOL_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE

// CLOCK
#define SYS_CLK_CONFIG_USBPLL_ENABLE              true
#define SYS_CLK_PRIMARY_CLOCK                     80000000L
#define SYS_CLK_SECONDARY_CLOCK                   80000000
#define SYS_CLK_CLOCK_CONFIG_ERROR                10
#define SYS_CLK_CONFIG_USBPLL_DIVISOR             2
#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR         2
#define SYS_CLK_CONFIG_SYSCLK_OP_DIVISOR          1
#define SYS_CLK_ON_WAIT_IDLE	              1
#define SYS_CLK_ON_WAIT_SLEEP                     0
#define SYS_CLK_EXTERNAL_CLOCK	              4000000

// Timer
#define DRV_TMR_COUNT_WIDTH 32
#define SYS_TMR_MAX_PERIODIC_EVENTS 4
#define DRV_TMR_INDEX 0
#define DRV_TMR_INTERRUPT_MODE 0
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "bsp/sk_pic32_mz/bsp_config.h"
#include "bsp/gfx/meb/meb2/bsp_config.h"
#include "bsp/gfx/meb/meb2/display/wqvga/bsp_config.h"

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

