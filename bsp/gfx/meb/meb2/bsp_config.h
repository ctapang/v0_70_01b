/*******************************************************************************
 Board support configuration file.

 Company:
    Microchip Technology Inc.

 File Name:
    bsp_config.h

 Summary:
    Board support configuration file.

 Description:
    This contains all the configuration that is required to be done for the
    application running on this combination of explorer 16 board with the
    PIC24FJ256GA110 PIM.
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

#ifndef MEB2_BSP_CONFIG_H
#define MEB2_BSP_CONFIG_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Graphics Display Timing Pin Constants

  Summary:
    Defines the constants which identifies Graphic Display timing pins

  Description:
    These constants identifies Graphic Display timing pins
*/

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
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board
*/

void BSP_Initialize(void);


#endif //MEB2_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
