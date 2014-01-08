/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       info_screen.c
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
#define GFX_BlockUntilFinished(function)   while(function == GFX_STATUS_FAILURE)

/*****************************************************************************
 * void CreateInfo(void)
 *****************************************************************************/
void CreateInfo()
{
    static uint8_t timeThrough = 0;
    static uint8_t currentPage;
    GFX_GOL_OBJ_SCHEME *defaultScheme;

    defaultScheme = GFX_SchemeGetDefaultScheme();

     GFX_ColorSet(GFX_SchemeGetCurrentScheme()->Color0);

    if(timeThrough == 0)
    {

        currentPage = GFX_ActivePageGet();

        while (GFX_PageSet(ACTIVE_PAGE, PIP_PAGE_BUFFER) == GFX_STATUS_FAILURE); //Draw Image to be shown fading in

        GFX_AlphaParamsSet(BACKGROUND_BUFFER,0,0,BACKGROUND_BUFFER,0,0,PIP_PAGE_BUFFER,0,0);

        while(CopyPageWindow(&GFX_Primitive_instance.alphaArea,
                        GFX_MaxXGet(), GFX_MaxYGet()) == GFX_STATUS_FAILURE);


	while(GFX_RectangleRoundFillDraw((GFX_MaxXGet() >> 2)+20,10 ,(GFX_MaxXGet() - 10), 60,5) == GFX_STATUS_FAILURE);
	while(GFX_ImageDraw((GFX_MaxXGet() >> 2)+20, 10, (void *) &help_faq) == GFX_STATUS_FAILURE);
	while(GFX_RectangleRoundFillDraw((GFX_MaxXGet() >> 2) + 20,90 ,GFX_MaxXGet() - 10, GFX_MaxYGet()-10,5) == GFX_STATUS_FAILURE);
  
	GFX_AlphaParamsSet(PIP_PAGE_BUFFER, (GFX_MaxXGet() >> 2) + 15, 5,
                            BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2) + 15, 5,
                            PIP_PAGE_BUFFER, (GFX_MaxXGet() >> 2) + 15, 5);

	while(GFX_AlphaBlendWindow(&GFX_Primitive_instance.alphaArea,
				     (GFX_MaxXGet())-((GFX_MaxXGet() >> 2) + 15),
				     60,  	
				     GFX_SchemeGetDefaultScheme()->AlphaValue) == GFX_STATUS_FAILURE);
    	
	GFX_AlphaParamsSet(PIP_PAGE_BUFFER, (GFX_MaxXGet() >> 2) + 15, 85,
                            BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2) + 15, 85,
                            PIP_PAGE_BUFFER, (GFX_MaxXGet() >> 2) + 15, 85);

	while(GFX_AlphaBlendWindow(&GFX_Primitive_instance.alphaArea,
				     (GFX_MaxXGet())-((GFX_MaxXGet() >> 2) + 15),
				     GFX_MaxYGet() - 90,
				     GFX_SchemeGetDefaultScheme()->AlphaValue) == GFX_STATUS_FAILURE);
				     		     				     
	GFX_ColorSet(GFX_RGBConvert(255, 102, 0));
        GFX_FontSet((void *) &GOLSmallFont);

        GFX_BlockUntilFinished(GFX_TextStringDraw((GFX_MaxXGet() >> 2)+100,20,(GFX_XCHAR *)InfoStr,0));
        GFX_BlockUntilFinished(GFX_TextStringDraw((GFX_MaxXGet() >> 2) + 90, 90, (GFX_XCHAR *)InformationStr,0));

        while (GFX_PageSet(ACTIVE_PAGE, currentPage) == GFX_STATUS_FAILURE); //Draw Image to be shown fading in
        timeThrough = 1;
}	

	GFX_GOL_ObjectStateSet(GFX_GOL_ObjectFind(MAIN_SCREEN_ID_INFO_BUT),GFX_GOL_BUTTON_DRAW_STATE|GFX_GOL_BUTTON_DISABLED_STATE);
      	
}
