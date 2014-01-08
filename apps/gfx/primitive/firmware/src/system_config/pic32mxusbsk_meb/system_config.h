/*******************************************************************************
  GFX Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the GFX Primitive Application.

  Description:
    This file is the top-level configuration header for the Primitive demo
    application which runs on the PIC32 MEB board.
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
#define GFX_PICTAIL_V3
#define MEB_BOARD

//PMP Data Size
#define USE_16BIT_PMP
//#define USE_8BIT_PMP

//PIC Interface
#define PIC_SK

//Graphics Controller
#define GFX_USE_DISPLAY_CONTROLLER_SSD1926
#define USE_GFX_PMP
#define PMP_DATA_SETUP_TIME                (18)
#define PMP_DATA_WAIT_TIME                 (82)  // based on the minimum pulse width requirement of CS signal of SSD1926
#define PMP_DATA_HOLD_TIME                 (0)

//GFX
#define USE_BITMAP_FLASH
#define USE_COMP_RLE
#define USE_MULTIBYTECHAR
#define USE_FONT_FLASH
#define GFX_CONFIG_COLOR_DEPTH              (16)
#define GFX_CONFIG_FONT_CHAR_SIZE           (8)
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_GOL_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

//Display
#define GFX_USE_DISPLAY_PANEL_TFT_G240320LTSW_118W_E

#undef USE_MULTIBYTECHAR

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

#include "bsp/gfx/meb/meb/bsp_config.h"

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

