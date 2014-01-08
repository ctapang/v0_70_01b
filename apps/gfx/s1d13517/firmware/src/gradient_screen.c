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
#include "gfx_screens.h"
#include "gol_ids.h"
/*****************************************************************************
 * SECTION: Defines
 *****************************************************************************/
#define GRADIENT_SCREEN_SIZE_X  (GFX_MaxXGet() - (GFX_MaxXGet() >> 2) - 100)
#define GRADIENT_SCREEN_SIZE_Y  (GFX_MaxYGet()  - 120)
#define GRADIENT_SIZE_V         (GRADIENT_SCREEN_SIZE_X / 3 )
#define GRADIENT_SIZE_H         (GRADIENT_SCREEN_SIZE_Y >> 1)

/*****************************************************************************
 * void CreateGradientScreen(void)
 *****************************************************************************/
void CreateGradientScreen(void)
{

     GFX_GradientColorSet(BRIGHTRED,BLACK);

 	GFX_ColorSet(GFX_SchemeGetCurrentScheme()->Color0);
	while(GFX_RectangleRoundFillDraw((GFX_MaxXGet() >> 2) + 20,90 ,GFX_MaxXGet() - 10, GFX_MaxYGet()-10,5)== GFX_STATUS_FAILURE);

	GFX_AlphaParamsSet(GFX_ActivePageGet(), (GFX_MaxXGet() >> 2) + 15, 85,
                            BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2) + 15, 85,
                            GFX_ActivePageGet(),(GFX_MaxXGet() >> 2) + 15, 85);

	while(GFX_AlphaBlendWindow(&GFX_Primitive_instance.alphaArea,
				     (GFX_MaxXGet())-((GFX_MaxXGet() >> 2) + 15),
				     GFX_MaxYGet() - 90,
				     GFX_SchemeGetDefaultScheme()->AlphaValue) == GFX_STATUS_FAILURE);

        GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_UP);

        while(GFX_BevelGradientDraw((GFX_MaxXGet() >> 2) +40,
   				     120,  
   				     (GFX_MaxXGet() >> 2) +40 + (GRADIENT_SCREEN_SIZE_X /3),
   				     90+(GRADIENT_SCREEN_SIZE_Y >>1),
   				     10) == GFX_STATUS_FAILURE);

   GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOWN);

   while(GFX_BevelGradientDraw(  (GFX_MaxXGet() >> 2) +65 + (GRADIENT_SCREEN_SIZE_X /3),
                    120, 
                    (GFX_MaxXGet() >> 2) +65 + ((GRADIENT_SCREEN_SIZE_X <<1)/3),
                    90+(GRADIENT_SCREEN_SIZE_Y >>1),
                    10) == GFX_STATUS_FAILURE);

   GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);

   while(GFX_BevelGradientDraw((GFX_MaxXGet() >> 2) +90 + ((GRADIENT_SCREEN_SIZE_X <<1)/3),
                    120+(GRADIENT_SCREEN_SIZE_Y >>1),
                    GFX_MaxXGet() - 20,
                    GFX_MaxYGet()-40,
                    10) == GFX_STATUS_FAILURE);

    GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_LEFT);

    while(GFX_BevelGradientDraw((GFX_MaxXGet() >> 2) +90 + ((GRADIENT_SCREEN_SIZE_X <<1)/3),
                    120, 
                    GFX_MaxXGet() - 20,
                    90+(GRADIENT_SCREEN_SIZE_Y >>1),
                    10) == GFX_STATUS_FAILURE);

   GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_VER);

   while(GFX_BevelGradientDraw(  (GFX_MaxXGet() >> 2) +65 + (GRADIENT_SCREEN_SIZE_X /3),
                    120+(GRADIENT_SCREEN_SIZE_Y >>1),
                    (GFX_MaxXGet() >> 2) +65 + ((GRADIENT_SCREEN_SIZE_X <<1)/3),
                    GFX_MaxYGet()-40,
                    10) == GFX_STATUS_FAILURE);

    GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_RIGHT);

    while(GFX_BevelGradientDraw( (GFX_MaxXGet() >> 2)+ 40,
                    120+(GRADIENT_SCREEN_SIZE_Y >>1), 
                    (GFX_MaxXGet() >> 2) +40 + (GRADIENT_SCREEN_SIZE_X /3),
                    GFX_MaxYGet()-40,
                    10) == GFX_STATUS_FAILURE);

   GFX_DoubleBufferAreaMark(0, 0, GFX_MaxXGet(), GFX_MaxYGet());
}
