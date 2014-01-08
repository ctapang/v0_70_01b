/*******************************************************************************
  GFX Primitive Demo Application
  
  File Name:
    app.c

  Summary:
    GFX Primitive Demo application

  Description:
    This file contains the GFX Primitive Demo application logic.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012-2013 released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "app.h"
#include "internal_resource.h"

// *****************************************************************************
// *****************************************************************************
// Section: Fonts
// *****************************************************************************
// *****************************************************************************
////extern const FONT_FLASH     Font25;
//extern const GFX_RESOURCE_HDR Font25;
//
//// *****************************************************************************
//// *****************************************************************************
//// Section: Pictures
//// *****************************************************************************
//// *****************************************************************************
//extern const IMAGE_FLASH        flower16bit;
//extern const IMAGE_FLASH        flower8bit;
//extern const IMAGE_FLASH        flower4bit;
//extern const IMAGE_FLASH        flower1bit;
//extern const IMAGE_FLASH        splash;
//
//extern const GFX_IMAGE_HEADER   Gaming4bit_RLE;
//extern const GFX_IMAGE_HEADER   Sun8bit_RLE;

// *****************************************************************************
// *****************************************************************************
// Section: MACROS
// *****************************************************************************
// *****************************************************************************
#define MIN(x,y)                ((x > y)? y: x)

uint32_t timeCount = 0;
short  renderCount = 0;
#define DEMODELAY 400000

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************
    short          width, height;
    short          counter;

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObject;

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Initialize ( void )
{

    DisplayResetEnable();               // hold in reset by default

    DisplayResetConfig();               // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                    // enable chip select line

    DisplayBacklightOff();              // initially set the backlight to off

    DisplayBacklightConfig();           // set the backlight control pin

    T4CONbits.ON = 1;

    PR4 = 160;

    IEC0bits.T4IE = 1;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Tasks ( void )
{
    if(timeCount++ > DEMODELAY)
    {

    switch(renderCount)
    {
        case 0:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);
        break;

        case 1:
        GFX_ColorSet(BRIGHTRED);
        while(GFX_LineDraw(0,0,GFX_MaxXGet(),0) == GFX_STATUS_FAILURE);

        GFX_ColorSet(YELLOW);
        while(GFX_LineDraw(0,0,0,GFX_MaxYGet()) == GFX_STATUS_FAILURE);

        GFX_ColorSet(GREEN);
        while(GFX_LineDraw(0,GFX_MaxYGet(),GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BLUE);
        while(GFX_LineDraw(GFX_MaxXGet(),0,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);
        counter = 0;
        GFX_ColorSet(WHITE);
        break;

         case 4:
       // renderCount = 3;
        break;

        case 3:
 
        while(counter < GFX_MaxXGet())
        {
            while(GFX_LineDraw(counter, 0, GFX_MaxXGet() - 1 - counter, GFX_MaxYGet() - 1) == GFX_STATUS_FAILURE);
            counter += 20;
            return;
        }
        while(GFX_LineDraw(counter, 0, GFX_MaxXGet() - 1 - counter, GFX_MaxYGet() - 1) == GFX_STATUS_FAILURE);

        counter = 10;
        GFX_ColorSet(BRIGHTRED);
        break;
        
        case 6:

        while(counter < MIN(GFX_MaxXGet(), GFX_MaxYGet()) >> 1)
        {
            while(GFX_CircleDraw(GFX_MaxXGet() >> 1, GFX_MaxYGet() >> 1, counter) == GFX_STATUS_FAILURE);
            counter += 10;
            return;
        }
        break;
        case 7:
        GFX_ColorSet(BLUE);
        while(GFX_CircleFillDraw(GFX_MaxXGet() >> 1, GFX_MaxYGet() >> 1, 60) == GFX_STATUS_FAILURE);

        GFX_ColorSet(GREEN);
        while(GFX_CircleFillDraw(GFX_MaxXGet() >> 1, GFX_MaxYGet() >> 1, 40) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BRIGHTRED);
        while(GFX_CircleFillDraw(GFX_MaxXGet() >> 1, GFX_MaxYGet() >> 1, 20) == GFX_STATUS_FAILURE);
        break;

        case 8:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

		// draw concentric beveled objects in the middle of the screen
        GFX_ColorSet(BLUE);
        while(GFX_RectangleRoundDraw((GFX_MaxXGet() >> 1) - 60, (GFX_MaxYGet() >> 1) - 60, (GFX_MaxXGet() >> 1) + 60, (GFX_MaxYGet() >> 1) + 60, 30) == GFX_STATUS_FAILURE);
        GFX_ColorSet(GREEN);
        while(GFX_RectangleRoundDraw((GFX_MaxXGet() >> 1) - 40, (GFX_MaxYGet() >> 1) - 40, (GFX_MaxXGet() >> 1) + 40, (GFX_MaxYGet() >> 1) + 40, 30) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BRIGHTRED);
        while(GFX_RectangleRoundDraw((GFX_MaxXGet() >> 1) - 20, (GFX_MaxYGet() >> 1) - 20, (GFX_MaxXGet() >> 1) + 20, (GFX_MaxYGet() >> 1) + 20, 30) == GFX_STATUS_FAILURE);
        break;
        case 9:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

        GFX_ColorSet(BLUE);

        while(GFX_ArcDraw
                (
                    (GFX_MaxXGet() >> 1) - 60,
                    (GFX_MaxYGet() >> 1) - 60,
                    (GFX_MaxXGet() >> 1) + 60,
                    (GFX_MaxYGet() >> 1) + 60,
                    20,
                    30,
                    0xFF
                ) == GFX_STATUS_FAILURE);


        GFX_ColorSet(GREEN);

        while(GFX_ArcDraw
                (
                    (GFX_MaxXGet() >> 1) - 40,
                    (GFX_MaxYGet() >> 1) - 40,
                    (GFX_MaxXGet() >> 1) + 40,
                    (GFX_MaxYGet() >> 1) + 40,
                    20,
                    30,
                    0xFF
                ) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BRIGHTRED);

        while(GFX_ArcDraw
                (
                    (GFX_MaxXGet() >> 1) - 20,
                    (GFX_MaxYGet() >> 1) - 20,
                    (GFX_MaxXGet() >> 1) + 20,
                    (GFX_MaxYGet() >> 1) + 20,
                    20,
                    30,
                    0xFF
                ) == GFX_STATUS_FAILURE);

        break;
        case 10:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);
		// draw concentric filled beveled objects in the middle of the screen
       GFX_ColorSet(BLUE);

            while(GFX_RectangleRoundFillDraw
                (
                    (GFX_MaxXGet() >> 1) - 60,
                    (GFX_MaxYGet() >> 1) - 60,
                    (GFX_MaxXGet() >> 1) + 60,
                    (GFX_MaxYGet() >> 1) + 60,
                    30
                ) == GFX_STATUS_FAILURE);


        GFX_ColorSet(GREEN);

            while(GFX_RectangleRoundFillDraw
                (
                    (GFX_MaxXGet() >> 1) - 40,
                    (GFX_MaxYGet() >> 1) - 40,
                    (GFX_MaxXGet() >> 1) + 40,
                    (GFX_MaxYGet() >> 1) + 40,
                    30
                ) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BRIGHTRED);
 
            while(GFX_RectangleRoundFillDraw
                (
                    (GFX_MaxXGet() >> 1) - 20,
                    (GFX_MaxYGet() >> 1) - 20,
                    (GFX_MaxXGet() >> 1) + 20,
                    (GFX_MaxYGet() >> 1) + 20,
                    30
                ) == GFX_STATUS_FAILURE);
        break;
        case 11:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

		// draw concentric thick beveled objects in the middle of the screen
        GFX_ColorSet(BLUE);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 50, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 50, 50, 60, 0x11) == GFX_STATUS_FAILURE);

        GFX_ColorSet(GREEN);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 50, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 50, 50, 60, 0x22) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BRIGHTRED);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 50, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 50, 50, 60, 0x44) == GFX_STATUS_FAILURE);
        GFX_ColorSet(YELLOW);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 50, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 50, 50, 60, 0x88) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BLUE);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 30, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 30, 35, 45, 0x11) == GFX_STATUS_FAILURE);

        GFX_ColorSet(GREEN);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 30, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 30, 35, 45, 0x22) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BRIGHTRED);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 30, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 30, 35, 45, 0x44) == GFX_STATUS_FAILURE);
        GFX_ColorSet(YELLOW);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) - 30, (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1) + 30, 35, 45, 0x88) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BLUE);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), 20, 30, 0x11) == GFX_STATUS_FAILURE);
        GFX_ColorSet(GREEN);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), 20, 30, 0x22) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BRIGHTRED);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), 20, 30, 0x44) == GFX_STATUS_FAILURE);
        GFX_ColorSet(YELLOW);
        while(GFX_ArcDraw((GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), (GFX_MaxXGet() >> 1), (GFX_MaxYGet() >> 1), 20, 30, 0x88) == GFX_STATUS_FAILURE);
        counter = 0;
        break;
        case 12:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

		// draw rectangles in the middle of the screen
         GFX_ColorSet(BLUE);
        while(counter < MIN(GFX_MaxXGet(), GFX_MaxYGet()) >> 1)
        {

                while(GFX_RectangleDraw
                    (
                        GFX_MaxXGet() / 2 - counter,
                        GFX_MaxYGet() / 2 - counter,
                        GFX_MaxXGet() / 2 + counter,
                        GFX_MaxYGet() / 2 + counter
                    ) == GFX_STATUS_FAILURE);
                counter += 20;
                return;
        }

        GFX_ColorSet(BLUE);
        while(GFX_RectangleFillDraw(GFX_MaxXGet() / 2 - 80, GFX_MaxYGet() / 2 - 80, GFX_MaxXGet() / 2 + 80, GFX_MaxYGet() / 2 + 80) == GFX_STATUS_FAILURE);
        GFX_ColorSet(GREEN);
        while(GFX_RectangleFillDraw(GFX_MaxXGet() / 2 - 60, GFX_MaxYGet() / 2 - 60, GFX_MaxXGet() / 2 + 60, GFX_MaxYGet() / 2 + 60) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BRIGHTRED);
        while(GFX_RectangleFillDraw(GFX_MaxXGet() / 2 - 40, GFX_MaxYGet() / 2 - 40, GFX_MaxXGet() / 2 + 40, GFX_MaxYGet() / 2 + 40) == GFX_STATUS_FAILURE);
        break;

        case 13:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

                short polyPoints[] = {
        (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)/4,
        (GFX_MaxXGet()+1)*3/4,  (GFX_MaxYGet()+1)/2,
        (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)*3/4,
        (GFX_MaxXGet()+1)/4,    (GFX_MaxYGet()+1)/2,
        (GFX_MaxXGet()+1)/2,    (GFX_MaxYGet()+1)/4,
                                    };
	    // draw ploygon shape in the middle of the screen
        GFX_ColorSet(WHITE);
        while(GFX_PolygonDraw(5, (short *)polyPoints) == GFX_STATUS_FAILURE);
        break;
        case 14:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

		// draw fonts in the screen
        GFX_FontSet((GFX_RESOURCE_HDR *) &Font25);
        GFX_ColorSet(GREEN);
        width = GFX_TextStringWidthGet((GFX_XCHAR*)"Microchip Technology Inc.", (GFX_RESOURCE_HDR *) &Font25);
        height = GFX_TextStringHeightGet((GFX_RESOURCE_HDR *) &Font25);
        while(GFX_TextStringBoxDraw(0, 0 ,0,0, (GFX_XCHAR*)"Microchip Technology Inc. \nRocks",0, 0) == GFX_STATUS_FAILURE);
        break;
        case 15:
        GFX_ImageStretchSet(IMAGE_X2);
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

		// draw pictures in the screen with different bits per pixel
        while(GFX_ImageDraw(0, 0, (GFX_RESOURCE_HDR *) &flower1bit) == GFX_STATUS_FAILURE);
        GFX_ColorSet(WHITE);
        while(GFX_TextStringBoxDraw(200, 0,0,0, (GFX_XCHAR*)"1BPP",0, 0)== GFX_STATUS_FAILURE);
        break;
        case 16:
        GFX_ColorSet(BLACK);
        GFX_ScreenClear();

        while(GFX_ImageDraw(0, 0, (GFX_RESOURCE_HDR *) &flower4bit) == GFX_STATUS_FAILURE);
        GFX_ColorSet(WHITE);
        while(GFX_TextStringBoxDraw(200, 0,0,0, (GFX_XCHAR*)"4BPP",0, 0)== GFX_STATUS_FAILURE);
        break;
        case 17:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

        while(GFX_ImageDraw(0, 0, (GFX_RESOURCE_HDR *) &flower8bit) == GFX_STATUS_FAILURE);
        GFX_ColorSet(WHITE);

        while(GFX_TextStringBoxDraw(200, 0,0,0, (GFX_XCHAR*)"8BPP",0, 0) == GFX_STATUS_FAILURE);
        break;
        case 18:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

//        GFX_ImageDraw(0, 0, (void *) &splash, 1);
        while(GFX_ImageDraw(0, 0, (GFX_RESOURCE_HDR *) &flower16bit) == GFX_STATUS_FAILURE);
        GFX_ColorSet(WHITE);
        while(GFX_TextStringBoxDraw(200, 0,0,0, (GFX_XCHAR*)"16BPP",0, 0) == GFX_STATUS_FAILURE);
        break;

        case 19:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

        width = GFX_ImageWidthGet((GFX_RESOURCE_HDR *) &flower1bit);
        height = GFX_ImageHeightGet((GFX_RESOURCE_HDR *) &flower1bit);
        GFX_ImageStretchSet(IMAGE_NORMAL);
        while(GFX_ImageDraw((GFX_MaxXGet() + 1) / 2 - width  , (GFX_MaxYGet() + 1) / 2 - height  , (void *) &flower1bit) == GFX_STATUS_FAILURE);
        while(GFX_ImageDraw((GFX_MaxXGet() + 1) / 2          , (GFX_MaxYGet() + 1) / 2 - height  , (void *) &flower4bit)== GFX_STATUS_FAILURE);
        while(GFX_ImageDraw((GFX_MaxXGet() + 1) / 2 - width  , (GFX_MaxYGet() + 1) / 2           , (void *) &flower8bit) == GFX_STATUS_FAILURE);
        while(GFX_ImageDraw((GFX_MaxXGet() + 1) / 2          , (GFX_MaxYGet() + 1) / 2           , (void *) &flower16bit) == GFX_STATUS_FAILURE);
        break;

        case 20:
        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

//        /* RLE Demonstration starts here */
        width = GFX_ImageWidthGet((GFX_RESOURCE_HDR *) &Sun8bit_RLE);
        height = GFX_ImageHeightGet((GFX_RESOURCE_HDR *) &Sun8bit_RLE);

        GFX_ColorSet(WHITE);
        GFX_FontSet((GFX_RESOURCE_HDR *) &Font25);

        while(GFX_ImageDraw(width + 90, 40, (GFX_RESOURCE_HDR *) &Sun8bit_RLE) == GFX_STATUS_FAILURE);
        while(GFX_TextStringBoxDraw(width + 90, height + 60,0,0, (GFX_XCHAR*)"RLE 8bit",0, 0) == GFX_STATUS_FAILURE);
        while(GFX_TextStringBoxDraw(width + 90, height + 90,0,0, (GFX_XCHAR*)"(3997 Bytes)",0, 0) == GFX_STATUS_FAILURE);
        while(GFX_ImageDraw(0, 40, (GFX_RESOURCE_HDR *) &Gaming4bit_RLE) == GFX_STATUS_FAILURE);
        while(GFX_TextStringBoxDraw(0, height + 60,0,0, (GFX_XCHAR*)"RLE 4bit",0, 0) == GFX_STATUS_FAILURE);
        while(GFX_TextStringBoxDraw(0, height + 90,0,0, (GFX_XCHAR*)"(1378 Bytes)",0, 0) == GFX_STATUS_FAILURE);
        renderCount = -1; //Startover
        break;
    }

    renderCount++;
    timeCount = 0;
    }
} //End of APP_Tasks



/*******************************************************************************
 End of File
 */

