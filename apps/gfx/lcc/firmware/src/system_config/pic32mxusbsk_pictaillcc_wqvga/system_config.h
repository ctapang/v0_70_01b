/*******************************************************************************
  GFX Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the GFX LCC Driver Application.

  Description:
    This file is the top-level configuration header for the LCC Driver demo
    application which runs on the PIC32 LCC board.
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
#define GFX_PICTAIL_LCC

//PIC Interface
#define PIC_SK

//Graphics Controller
#define GFX_USE_DISPLAY_CONTROLLER_LCC

//Graphics Library
#define USE_TOUCHSCREEN
#define USE_MULTIBYTECHAR
#define USE_FONT_FLASH
#define USE_BITMAP_FLASH
#define USE_GRADIENT
#define USE_COMP_RLE
#define GFX_CONFIG_COLOR_DEPTH              (16)
#define GFX_CONFIG_FONT_CHAR_SIZE           (8)
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_FOCUS_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_ALPHABLEND_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
	#define GFX_malloc(size)    	malloc(size)
	#define GFX_free(pObj)    	    free(pObj)		// <COPY GFX_malloc>
#define GFX_GOL_FOCUS_LINE  2
#define GFX_GOL_EMBOSS_SIZE 3
#define GOLFontDefault Gentium_16

//Display
#define GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q
#define USE_TOUCHSCREEN_RESISTIVE

//LCC Specific
#define LCC_EXTERNAL_MEMORY

#define IMG_SUPPORT_JPEG
#define USE_DOUBLE_BUFFERING
#define USE_ALPHABLEND_LITE

// INTERRUPT
#define INT_IRQ_MAX  5

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
#define SYS_CLK_USB_FIXED_DIVISOR		2
#define SYS_CLK_USB_FIXED_PLL_MULTIPLIER	24

// SPI
#define DRV_SPI_INSTANCES_NUMBER                    		2
#define DRV_SPI_CLIENTS_NUMBER                      		2
#define DRV_SPI_INTERRUPT_MODE                      true
#define DRV_SPI_PORTS_REMAP_USAGE                   false
#define DRV_SPI_BUFFER_SIZE                         64
#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT
#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH
#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

// SPI FLASH
#define USE_SST25VF016

// Timer
#define DRV_TMR_COUNT_WIDTH 32
#define SYS_TMR_MAX_PERIODIC_EVENTS 4
#define DRV_TMR_INDEX 0
#define DRV_TMR_INTERRUPT_MODE 0
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4

#include "bsp/sk_pic32_mx_usb/bsp_config.h"
#include "bsp/gfx/pictail/pictaillcc/bsp_config.h"
#include "bsp/gfx/pictail/display/wqvga/bsp_config.h"

#endif // _SYS_CONFIG_H
