/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       main_screen.c
 * Dependencies:    See Includes Section
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/
#include "app.h"
#include "gfx_schemes.h"
#include "gfx_strings.h"
#include "gfx_screens.h"
#include "gol_ids.h"

/*****************************************************************************
 * SECTION: Defines
 *****************************************************************************/
#define PERFORMANCE_BUTTON_HEIGHT    (GFX_MaxYGet() / 9)
#define PERFORMANCE_BUTTON_RADIUS    7

#define GFX_BlockUntilFinished(function)   while(function == GFX_STATUS_FAILURE)
/*****************************************************************************
 * SECTION: Local Function Prototypes
 *****************************************************************************/
float FPS_PPS(void);
void CharStringToXCharString(GFX_XCHAR *xstring, char *string);
/*****************************************************************************
 * void CreatePerformanceScreen(BYTE drawFlag)
 *****************************************************************************/

/*****************************************************************************
 * void CreateSpeed(void)
 *****************************************************************************/
void CreateSpeed(void)
{

uint16_t counter =0;
float    randl,randt,randr,randb,temp;

while (GFX_PageSet(ACTIVE_PAGE, GFX_VisualPageGet()) == GFX_STATUS_FAILURE); //Draw Image to be shown fading in

while(counter++ < 100)
{
	// draw random bars in the middle of the screen
        GFX_ColorSet((rand() % 65536));

        randl = rand() % GFX_MaxXGet();
        randr = rand() % GFX_MaxXGet();

        if(randl > randr)
        {
           temp = randl;
           randl = randr;
           randr = temp;
        }

        randt = rand() % GFX_MaxYGet();
        randb = rand() % GFX_MaxYGet();

        if(randt > randb)
        {
           temp = randt;
           randt = randb;
           randb = temp;
        }

         while(GFX_RectangleFillDraw(randl,randt,randr,randb) == GFX_STATUS_FAILURE);
}

while (GFX_PageSet(ACTIVE_PAGE, GFX_ActivePageGet()) == GFX_STATUS_FAILURE); //Draw Image to be shown fading in

}

/*****************************************************************************
 * void CharStringToXCharString(XCHAR *wtext, char *text)
 *****************************************************************************/
void CharStringToXCharString(GFX_XCHAR *xstring, char *string)
{
    while(*string != '\0')
    {
        *xstring = (GFX_XCHAR)*string;
        xstring++;
        string++;
    }

    *xstring = (GFX_XCHAR)*string;
}
