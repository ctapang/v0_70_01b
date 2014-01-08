/*******************************************************************************
  CDC Basic Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the CDC Basic demo
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

//PICTail
#define MEB_2_BOARD
#define GFX_PICTAIL_LCC

//PMP Data Size
//#define USE_16BIT_PMP
//#define USE_8BIT_PMP


#define LCC_INTERNAL_MEMORY_EBI

#define MEB_2_BOARD
#define GFX_PICTAIL_LCC

//PMP Data Size
//#define USE_16BIT_PMP
//#define USE_8BIT_PMP

//PIC Interface
#define PIC_SK

//Graphics Controller
#define GFX_USE_DISPLAY_CONTROLLER_LCC

//GFX
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

#define GFX_CONFIG_COLOR_DEPTH              (16)
#define GFX_CONFIG_FONT_CHAR_SIZE           (8)
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_GOL_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE

//Display
#define GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q

//LCC Specific
//#define LCC_EXTERNAL_MEMORY
#define LCC_INTERNAL_MEMORY

#undef USE_MULTIBYTECHAR

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

// Timer
#define DRV_TMR_COUNT_WIDTH 32
#define SYS_TMR_MAX_PERIODIC_EVENTS 4
#define DRV_TMR_INDEX 0
#define DRV_TMR_INTERRUPT_MODE 0
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4

#define PIXELCLOCK        LATDbits.LATD5
#define PIXELCLOCK_TRIS   TRISDbits.TRISD5
//#include "sk_pic32_mz/bsp_config.h"

//#include "gfx/meb/meb2/bsp_config.h"
#define DATA_ENABLE      LATBbits.LATB4
#define DATA_ENABLE_TRIS TRISBbits.TRISB4
#define HSYNC            LATBbits.LATB1
#define HSYNC_TRIS       TRISBbits.TRISB1
#define VSYNC            LATAbits.LATA9
#define VSYNC_TRIS       TRISAbits.TRISA9

// *****************************************************************************
/* LCD Display Pin Constants

  Summary:
    Defines the constants which identifies LCD Display pins

  Description:
    These constants identifies LCD Display pins
*/
#define BACKLIGHT      LATFbits.LATF13
#define BACKLIGHT_TRIS TRISFbits.TRISF13
#define LCD_RESET      LATJbits.LATJ3
#define LCD_RESET_TRIS TRISJbits.TRISJ3
#define LCD_CS         LATJbits.LATJ6
#define LCD_CS_TRIS    TRISJbits.TRISJ6

#define BACKLIGHT_ENABLE_LEVEL      1
#define BACKLIGHT_DISABLE_LEVEL     0

// Definitions for reset pin
#define DisplayResetConfig()        TRISCCLR = _TRISC_TRISC1_MASK
#define DisplayResetEnable()        LATCCLR = _LATC_LATC1_MASK
#define DisplayResetDisable()       LATCSET = _LATC_LATC1_MASK

// Definitions for RS pin
#define DisplayCmdDataConfig()      TRISCCLR = _TRISC_TRISC2_MASK
#define DisplaySetCommand()         LATCCLR = _LATC_LATC2_MASK
#define DisplaySetData()            LATCSET = _LATC_LATC2_MASK

// Definitions for CS pin
#define DisplayConfig()             TRISDCLR = _TRISD_TRISD10_MASK
#define DisplayEnable()             LATDCLR = _LATD_LATD10_MASK
#define DisplayDisable()            LATDSET = _LATD_LATD10_MASK

// Definitions for backlight control pin
#define DisplayBacklightConfig()    (TRISDbits.TRISD0 = 0)
#define DisplayBacklightOn()        (LATDbits.LATD0 = BACKLIGHT_ENABLE_LEVEL)
#define DisplayBacklightOff()       (LATDbits.LATD0 = BACKLIGHT_DISABLE_LEVEL)


#define ADDR16        LATKbits.LATK0
#define ADDR16_TRIS   TRISKbits.TRISK0
#define ADDR17        LATKbits.LATK3
#define ADDR17_TRIS   TRISKbits.TRISK3
#define ADDR18        LATKbits.LATK4
#define ADDR18_TRIS   TRISKbits.TRISK4
#define ADDR19        LATKbits.LATK5
#define ADDR19_TRIS   TRISKbits.TRISK5
/*Macros for External SRAM*/
#define SRAM_CS       LATJbits.LATJ4
#define SRAM_TRIS     TRISJbits.TRISJ4

#define PMP_INTERRUPT IEC4bits.PMPIE
#define  PMADDR_OVERFLOW               65536


#define USE_TCON_MODULE 0
#define GFX_USE_TCON_CUSTOM

//#include "gfx/meb/meb2/display/wqvga/bsp_config.h"
#define DISP_ORIENTATION		0
#define DISP_HOR_RESOLUTION		480
#define DISP_VER_RESOLUTION		272
#define DISP_DATA_WIDTH			24
#define DISP_HOR_PULSE_WIDTH    41
#define DISP_HOR_BACK_PORCH     2
#define DISP_HOR_FRONT_PORCH    2
#define DISP_VER_PULSE_WIDTH    10
#define DISP_VER_BACK_PORCH     2
#define DISP_VER_FRONT_PORCH    2
#define DISP_INV_LSHIFT         0
#define GFX_LCD_TYPE            GFX_LCD_TFT
#define TCON_MODULE             NULL


/*
*********************************************************************************************************
*                                            SYSTEM TASK PRIORITIES
*********************************************************************************************************
*/
#define  DISPLAYDRIVER_TASK_PRIO                         6u

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/
#define  DISPLAYDRIVER_TASK_STK_SIZE                     400u

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void  DisplayDriverTask         (void *p_arg);

#endif // _SYS_CONFIG_H



