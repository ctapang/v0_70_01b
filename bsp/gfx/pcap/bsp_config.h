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

#ifndef PCAP_BSP_CONFIG_H
#define PCAP_BSP_CONFIG_H


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
#define DisplayResetConfig()        TRISCCLR = _TRISC_TRISC14_MASK
#define DisplayResetEnable()        LATCCLR = _LATC_LATC14_MASK
#define DisplayResetDisable()       LATCSET = _LATC_LATC14_MASK

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

#define SST25_SPI_CHANNEL SPI_ID_1

#define USE_TCON_MODULE 0
#define GFX_USE_TCON_CUSTOM

/*Macros for timing signals*/
#define DATA_ENABLE      LATAbits.LATA6         //PCAP
#define DATA_ENABLE_TRIS TRISAbits.TRISA6       //PCAP
#define HSYNC            LATDbits.LATD2         //PCAP
#define HSYNC_TRIS       TRISDbits.TRISD2       //PCAP
#define VSYNC            LATDbits.LATD3         //PCAP
#define VSYNC_TRIS       TRISDbits.TRISD3       //PCAP

/*Macros for LCD IO*/ 
#define BACKLIGHT      LATDbits.LATD1         //PCAP
#define BACKLIGHT_TRIS TRISDbits.TRISD1       //PCAP
#define LCD_RESET      LATCbits.LATC14        //PCAP
#define LCD_RESET_TRIS TRISCbits.TRISC14      //PCAP
#define LCD_CS         LATAbits.LATA7         //PCAP       
#define LCD_CS_TRIS    TRISAbits.TRISA7       //PCAP

/*Macros for External SRAM*/
#define SRAM_CS       LATGbits.LATG15        //PCAP     
#define SRAM_TRIS     TRISGbits.TRISG15      //PCAP

#define ADDR16        LATGbits.LATG13        //PCAP
#define ADDR16_TRIS   TRISGbits.TRISG13      //PCAP
#define ADDR17        LATGbits.LATG12        //PCAP
#define ADDR17_TRIS   TRISGbits.TRISG12      //PCAP
#define ADDR18        LATGbits.LATG14        //PCAP
#define ADDR18_TRIS   TRISGbits.TRISG14      //PCAP

#define PIXELCLOCK        LATDbits.LATD5
#define PIXELCLOCK_TRIS   TRISDbits.TRISD5

#define  PMADDR_OVERFLOW               65536

#define TCON_MODULE NULL
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
