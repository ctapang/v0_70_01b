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

#ifndef PICTAILLCC_BSP_CONFIG_H
#define PICTAILLCC_BSP_CONFIG_H

#include <xc.h>
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* LCD Display Pin Constants

  Summary:
    Defines the constants which identifies LCD Display pins

  Description:
    These constants identifies LCD Display pins
*/

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

// Definitions for FLASH CS pin
#define DisplayFlashConfig()
#define DisplayFlashEnable()
#define DisplayFlashDisable()

// Definitions for POWER ON pin
#define DisplayPowerConfig()
#define DisplayPowerOn()
#define DisplayPowerOff()

// ADC channel constants
// resistive touch X and Y voltage sensing
#define ADC_XPOS		 (0x0 << _AD1CHS_CH0SA_POSITION)
#define ADC_YPOS		 (0x1 << _AD1CHS_CH0SA_POSITION)

#if defined(_AD1PCFG_PCFG_POSITION)
#define ADPCFG_XPOS AD1PCFGbits.PCFG0
#define ADPCFG_YPOS AD1PCFGbits.PCFG1
#define RESISTIVETOUCH_ANALOG  0
#define RESISTIVETOUCH_DIGITAL 1
#else //ANSEL
#define ADPCFG_XPOS ANSELBbits.ANSB0
#define ADPCFG_YPOS ANSELBbits.ANSB1
#define RESISTIVETOUCH_ANALOG  1
#define RESISTIVETOUCH_DIGITAL 0
#endif




// X port definitions
#define ResistiveTouchScreen_XPlus_Drive_High()             LATBbits.LATB0   = 1
#define ResistiveTouchScreen_XPlus_Drive_Low()              LATBbits.LATB0   = 0
#define ResistiveTouchScreen_XPlus_Config_As_Input()        TRISBbits.TRISB0 = 1
#define ResistiveTouchScreen_XPlus_Config_As_Output()       TRISBbits.TRISB0 = 0

#define ResistiveTouchScreen_XMinus_Drive_High()         LATDbits.LATD9    = 1
#define ResistiveTouchScreen_XMinus_Drive_Low()          LATDbits.LATD9    = 0
#define ResistiveTouchScreen_XMinus_Config_As_Input()    TRISDbits.TRISD9  = 1
#define ResistiveTouchScreen_XMinus_Config_As_Output()   TRISDbits.TRISD9  = 0

// Y port definitions
#define ResistiveTouchScreen_YPlus_Drive_High()             LATBbits.LATB1   = 1
#define ResistiveTouchScreen_YPlus_Drive_Low()              LATBbits.LATB1   = 0
#define ResistiveTouchScreen_YPlus_Config_As_Input()        TRISBbits.TRISB1 = 1
#define ResistiveTouchScreen_YPlus_Config_As_Output()       TRISBbits.TRISB1 = 0

#define ResistiveTouchScreen_YMinus_Drive_High()            LATBbits.LATB9   = 1
#define ResistiveTouchScreen_YMinus_Drive_Low()             LATBbits.LATB9   = 0
#define ResistiveTouchScreen_YMinus_Config_As_Input()       TRISBbits.TRISB9 = 1
#define ResistiveTouchScreen_YMinus_Config_As_Output()      TRISBbits.TRISB9 = 0


// Potentiometer and Temperature sensor
#define ADC_TEMP		 ADC_CH0_POS_SAMPLEA_AN4
#define TOUCH_ADC_INPUT_SEL   AD1CHS

// ADC Sample Start
#define TOUCH_ADC_START   AD1CON1bits.SAMP

// ADC Status
#define TOUCH_ADC_DONE   AD1CON1bits.DONE

#define ADDRESS_RESISTIVE_TOUCH_VERSION	(unsigned long)0xFFFFFFFE
#define ADDRESS_RESISTIVE_TOUCH_ULX   (unsigned long)0xFFFFFFFC
#define ADDRESS_RESISTIVE_TOUCH_ULY   (unsigned long)0xFFFFFFFA
#define ADDRESS_RESISTIVE_TOUCH_URX   (unsigned long)0xFFFFFFF8
#define ADDRESS_RESISTIVE_TOUCH_URY   (unsigned long)0xFFFFFFF6

#define ADDRESS_RESISTIVE_TOUCH_LLX   (unsigned long)0xFFFFFFF4
#define ADDRESS_RESISTIVE_TOUCH_LLY   (unsigned long)0xFFFFFFF2
#define ADDRESS_RESISTIVE_TOUCH_LRX   (unsigned long)0xFFFFFFF0
#define ADDRESS_RESISTIVE_TOUCH_LRY   (unsigned long)0xFFFFFFEE

#define SST25_CS_TRIS   TRISDbits.TRISD1
#define SST25_CS_LAT    LATDbits.LATD1

#define SST25_SCK_TRIS  TRISGbits.TRISG6
#define SST25_SDO_TRIS  TRISGbits.TRISG8
#define SST25_SDI_TRIS  TRISGbits.TRISG7

#define PMP_DATA_SETUP_TIME                (18)
#define PMP_DATA_WAIT_TIME                 (82)  // based on the minimum pulse width requirement of CS signal of SSD1926
#define PMP_DATA_HOLD_TIME                 (0)

#define SST25_SPI_CHANNEL SPI_ID_1

#define USE_TCON_MODULE 0
#define GFX_USE_TCON_CUSTOM

/*Macros for timing signals*/
#define DATA_ENABLE      LATDbits.LATD2
#define DATA_ENABLE_TRIS TRISDbits.TRISD2
#define HSYNC            LATBbits.LATB8
#define HSYNC_TRIS       TRISBbits.TRISB8
#define VSYNC            LATCbits.LATC3
#define VSYNC_TRIS       TRISCbits.TRISC3

/*Macros for LCD IO*/
#define BACKLIGHT      LATDbits.LATD3
#define BACKLIGHT_TRIS TRISDbits.TRISD3
#define LCD_RESET      LATCbits.LATC1
#define LCD_RESET_TRIS TRISCbits.TRISC1
#define LCD_CS         LATCbits.LATC2
#define LCD_CS_TRIS    TRISCbits.TRISC2
#define LCD_DC         LATBbits.LATB3
#define LCD_DC_TRIS    TRISBbits.TRISB3

/*Macros for External SRAM*/
#define SRAM_CS       LATFbits.LATF13
#define SRAM_TRIS     TRISFbits.TRISF13

#define ADDR15        LATAbits.LATA15
#define ADDR15_TRIS   TRISAbits.TRISA15
#define ADDR16        LATDbits.LATD8
#define ADDR16_TRIS   TRISDbits.TRISD8
#define ADDR17        LATEbits.LATE9
#define ADDR17_TRIS   TRISEbits.TRISE9
#define ADDR18        LATFbits.LATF12
#define ADDR18_TRIS   TRISFbits.TRISF12

#define PIXELCLOCK        LATDbits.LATD4
#define PIXELCLOCK_TRIS   TRISDbits.TRISD4

#define PMP_INTERRUPT IEC1bits.PMPIE
#define  PMADDR_OVERFLOW               32768


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


#endif //PICTAILLCC_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
