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

#ifndef QVGA_BSP_CONFIG_H
#define QVGA_BSP_CONFIG_H


/*********************************************************************
* DISPLAY PARAMETERS
*********************************************************************/
/*
    The following are the parameters required for the
    different display drivers that is supported.
    When adding support to a new display controller or display panel,
    follow the parameterization of the driver for reusability of the
    driver.

    Display Parameter Macros Descriptions:

    1. DISP_ORIENTATION - defines the display rotation with
            respect to its native orientation. For example, if the display
            has a resolution specifications that says 240x320 (QVGA), the
            display is natively in portrait mode. If the application
            uses the display in landscape mode (320x240), then the
            orientation musts be defined as 90 or 180 degree rotation.
            The Graphics Library will calculate the actual pixel location
            to rotate the contents of the screen. So when users view the
            display, the image on the screen will come out in the correct
            orientation.

            Valid values: 0, 90, 180 and 270
            Example: #define DISP_ORIENTATION 90

    2. DISP_HOR_RESOLUTION - defines the horizontal dimension in pixels. This
            is the native horizontal dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_HOR_RESOLUTION
            of 320.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_HOR_RESOLUTION 320

    3. DISP_VER_RESOLUTION - defines the vertical dimension in pixels. This
            is the native vertical dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_VER_RESOLUTION
            of 240.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_VER_RESOLUTION 240

    4. COLOR_DEPTH - (NOTE: Define this macro in the GraphicsConfig.h
             This defines the vertical dimension in pixels.

            Valid Values: 1, 4, 8, 16, 24 (note 24 bpp is only used if you are
                          using a Display Driver that supports 24 bpp color depth.
            Example: #define COLOR_DEPTH 16

    5. DISP_DATA_WIDTH - this defines the display controller physical interface
            to the display panel.

            Valid Values: 1, 4, 8, 16, 18, 24
                          1, 4, 8 are usually used in MSTN and CSTN displays
                          16, 18 and 24 are usually used in TFT displays.
            Example: #define DISP_DATA_WIDTH 18

    6. DISP_INV_LSHIFT - this indicates that the color data is sampled in the
            falling edge of the pixel clock.

            Example: #define DISP_INV_LSHIFT - define this to sample the
                          color data in the falling edge of the pixel clock.

    7. DISP_HOR_PULSE_WIDTH - this defines the horizontal sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_PULSE_WIDTH 25

    8. DISP_VER_PULSE_WIDTH - this defines the vertical sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_PULSE_WIDTH 4

    9. DISP_HOR_BACK_PORCH - this defines the horizontal back porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_BACK_PORCH 5

    10. DISP_HOR_FRONT_PORCH - this defines the horizontal front porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_FRONT_PORCH 10

    11. DISP_VER_BACK_PORCH - this defines the vertical back porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_BACK_PORCH 0

    12. DISP_VER_FRONT_PORCH - this defines the horizontal front porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_FRONT_PORCH 2

    13. GFX_LCD_TYPE - this defines the type of display glass used.

            Valid Values: Dependent on the display controller supported LCD types.
                          GFX_LCD_TFT  // Type TFT Display
                          GFX_LCD_CSTN // Type Color STN Display
                          GFX_LCD_MSTN // Type Mono STN Display
                          GFX_LCD_OLED // Type OLED Display

            Example: #define GFX_LCD_TYPE GFX_LCD_TFT

    14. GFX_DISPLAYENABLE_ENABLE - this enables the use of the Display Enable Port
            (GEN) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports DATA ENABLE Mode. DATA ENABLE Mode
            is used when the display panel do not have sync (HSYNC and VSYNC) signals.

            Example: #define GFX_DISPLAYENABLE_ENABLE

    15. GFX_DISPLAYENABLE_POLARITY - this sets the polarity of the Display Enable Port
            (GEN) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYENABLE_POLARITY GFX_ACTIVE_HIGH

    16. GFX_HSYNC_ENABLE - this enables the use of the Display Horizontal Synchronization
            Port (HSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_HSYNC_ENABLE

    17. GFX_HSYNC_POLARITY - this sets the polarity of the Display Horizontal Synchronization
            Port (HSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_HSYNC_POLARITY GFX_ACTIVE_LOW

    18. GFX_VSYNC_ENABLE - this enables the use of the Display Vertical Synchronization
            Port (VSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_VSYNC_ENABLE

    19. GFX_VSYNC_POLARITY - this sets the polarity of the Display Vertical Synchronization
            Port (VSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_VSYNC_POLARITY GFX_ACTIVE_LOW

    20. GFX_DISPLAYPOWER_ENABLE - this enables the use of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module. The signal
            can be used to control the display power circuitry. The Graphics Module
            can manage the powering up and powering down of the display since
            power up and power down sequence in display panels is essential to
            extend display life cycle.

            Example: #define GFX_DISPLAYPOWER_ENABLE

    21. GFX_DISPLAYPOWER_POLARITY - this sets the polarity of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYPOWER_POLARITY GFX_ACTIVE_HIGH

    22. GFX_CLOCK_POLARITY - this sets the polarity of the Display Glass Clock Port (GCLK)
            when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_CLOCK_POLARITY GFX_ACTIVE_HIGH


    There are two major types of controllers enumerated here:
    1. Controllers in Smart Displays - these are display modules that have
       built in display controller. Interface to the PIC device(s)
       are usually through parallel interface or serial interface.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION

    2. Controller that drives the RGB Glass directly - these are display
       controllers that comes in a separate package or built into the
       microcontrollers.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION
       #define DISP_DATA_WIDTH
       #define DISP_HOR_PULSE_WIDTH
       #define DISP_HOR_BACK_PORCH
       #define DISP_HOR_FRONT_PORCH
       #define DISP_VER_PULSE_WIDTH
       #define DISP_VER_BACK_PORCH
       #define DISP_VER_FRONT_PORCH

       Optional parameters:
       #define DISP_INV_LSHIFT

       When using Microchip Graphics Module (mchpGfxDrv) required parameters:
       #define GFX_DISPLAYENABLE_ENABLE
       #define GFX_DISPLAYENABLE_POLARITY

       or

       #define GFX_HSYNC_ENABLE
       #define GFX_VSYNC_ENABLE
       #define GFX_HSYNC_POLARITY
       #define GFX_VSYNC_POLARITY

       #define GFX_CLOCK_POLARITY

       When using Microchip Graphics Module (mchpGfxDrv) Optional parameters:
       #define GFX_DISPLAYPOWER_ENABLE
       #define GFX_DISPLAYPOWER_POLARITY


*/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Graphics Display Parameters Constants

  Summary:
    Defines the constants which identifies Graphic Display Parameters

  Description:
    These constants identifies Graphic Display Parameters
*/
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


#endif //QVGA_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
