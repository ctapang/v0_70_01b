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
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
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
#define MAIN_SCREEN_BUTTON_HEIGHT       (GFX_MaxYGet() / 10)
#define MAIN_SCREEN_BUTTON_RADIUS       7

#define GFX_BlockUntilFinished(function)   while(function == GFX_STATUS_FAILURE)

/*****************************************************************************
 * SECTION: Constants
 *****************************************************************************/
const GFX_XCHAR mainScreenStr[] = { 'H', 'o', 'm', 'e', '\0' };
/*****************************************************************************
 * void CreateMainScreen(void)
 *****************************************************************************/
void CreateMainScreen(uint8_t clock)
{

      GFX_AlphaParamsSet(BACKGROUND_BUFFER,0,0,BACKGROUND_BUFFER,0,0,GFX_ActivePageGet(),0,0);

      while(CopyPageWindow(&GFX_Primitive_instance.alphaArea,
                        GFX_MaxXGet(), GFX_MaxYGet()) == GFX_STATUS_FAILURE);
    
    GFX_GOL_OBJ_SCHEME *currentScheme;

    currentScheme = GFX_SchemeGetCurrentScheme();
    currentScheme->AlphaValue = 70;

    GFX_AlphaParamsSet(BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2), 0,
                           BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2), 0,
                            GFX_ActivePageGet(),(GFX_MaxXGet() >> 2), 0);

    while(GFX_AlphaBlendWindow(&GFX_Primitive_instance.alphaArea,
				     GFX_MaxXGet()-(GFX_MaxXGet() >> 2),
	    	                     GFX_MaxYGet(),
				     50) == GFX_STATUS_FAILURE);

    GFX_ColorSet(ORANGE);                       // Orange

    while(GFX_RectangleFillDraw((GFX_MaxXGet() >> 2)-2, 0 , (GFX_MaxXGet() >> 2) + 2, GFX_MaxYGet()) == GFX_STATUS_FAILURE);
 
    GFX_GOL_ObjectListFree();                              // free memory for the objects in the previous linked list and start new list
 
    GFX_AlphaParamsSet(BACKGROUND_BUFFER,0,0,BACKGROUND_BUFFER,0,0,GFX_ActivePageGet(),0,0);

    while(CopyPageWindow(&GFX_Primitive_instance.alphaArea,
                        (GFX_MaxXGet() >> 2) - 5, GFX_MaxYGet()) == GFX_STATUS_FAILURE);

    GFX_GOL_ButtonCreate
    (   
        MAIN_SCREEN_ID_COMFORT_BUT,                         // button ID
        5,
        MAIN_SCREEN_BUTTON_HEIGHT << 1,
        (GFX_MaxXGet() >> 2) - 5,
        MAIN_SCREEN_BUTTON_HEIGHT *3,                                // dimension
        MAIN_SCREEN_BUTTON_RADIUS,                                 // set radius
        GFX_GOL_BUTTON_DRAW_STATE,                           // draw a beveled button
        NULL,                               // no bitmap
        NULL,
        (GFX_XCHAR *)ComfortStr,                 // "Button",     	// text
        GFX_ALIGN_HCENTER,
        currentScheme
    );

    GFX_GOL_ButtonCreate
    (      
        MAIN_SCREEN_ID_SLIDE_SHOW_BUT,                         // button ID
        5,
        (MAIN_SCREEN_BUTTON_HEIGHT *3) + 10,
        (GFX_MaxXGet() >> 2) - 5,
        (MAIN_SCREEN_BUTTON_HEIGHT << 2) + 10,                 // dimension
        MAIN_SCREEN_BUTTON_RADIUS,
        GFX_GOL_BUTTON_DRAW_STATE,                           // will be dislayed after creation
        NULL,           // use bitmap
        NULL,
        (GFX_XCHAR *)SlideShowStr,                   // "HOME", 	    // text
        GFX_ALIGN_HCENTER,
        currentScheme
    );                                      // alternative GOL scheme

    GFX_GOL_ButtonCreate
    (        
        MAIN_SCREEN_ID_SPEED_BUT,                         // button ID
        5,
        (MAIN_SCREEN_BUTTON_HEIGHT << 2) + 20,
        (GFX_MaxXGet() >> 2) - 5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 5) + 20,                 // dimension
        MAIN_SCREEN_BUTTON_RADIUS,                                 // set radius
        GFX_GOL_BUTTON_DRAW_STATE,              // draw a vertical capsule button
        NULL,
        NULL, // no bitmap
        (GFX_XCHAR *)SpeedStr,                    // "LO",       	// text
        GFX_ALIGN_HCENTER,
        currentScheme
    );                          // use alternate scheme

    GFX_GOL_ButtonCreate
    (      
        MAIN_SCREEN_ID_GRADIENT_BUT,             // button ID
        5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 5) + 30,
        (GFX_MaxXGet() >> 2) - 5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 6) +  30,      // dimension
        MAIN_SCREEN_BUTTON_RADIUS,                // set radius
        GFX_GOL_BUTTON_DRAW_STATE,                     // draw a vertical capsule button
        NULL,                         // no bitmap
        NULL,
        (GFX_XCHAR *)GradientStr,           // "ON",		// text
        GFX_ALIGN_HCENTER,
        currentScheme
    );                          // use alternate scheme

    GFX_GOL_ButtonCreate
    (        
        MAIN_SCREEN_ID_ALPHA_BUT,             // button ID
        5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 6) +  40,
        (GFX_MaxXGet() >> 2) - 5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 7) +  40,     // dimension
        MAIN_SCREEN_BUTTON_RADIUS,                     // set radius
        GFX_GOL_BUTTON_DRAW_STATE, // draw a vertical capsule button
        NULL,  // no bitmap
        NULL,
        (GFX_XCHAR *)BlendingStr,                    // "OFF",      	// text
        GFX_ALIGN_HCENTER,
        currentScheme
    );                      // use alternate scheme

    GFX_GOL_ButtonCreate
    (    
        MAIN_SCREEN_ID_INFO_BUT,             // button ID
        5,
        (MAIN_SCREEN_BUTTON_HEIGHT * 7) +  50,
        (GFX_MaxXGet() >> 2) - 5,
        (MAIN_SCREEN_BUTTON_HEIGHT << 3) +  50,     // dimension
        MAIN_SCREEN_BUTTON_RADIUS,                     // set radius
        GFX_GOL_BUTTON_DRAW_STATE, // draw a vertical capsule button
        NULL,  // no bitmap
        NULL,
        (GFX_XCHAR *)InfoStr,                    // "OFF",      	// text
        GFX_ALIGN_HCENTER,
        currentScheme
    );                      // use alternate scheme 

if(clock == 1)
{
//    GFX_AnalogClockCreate
//    (
//
//        MAIN_SCREEN_ID_ANALOG_CLOCK,                         // button ID
//        (GFX_MaxXGet() >> 2) + 20,
//        90,
//        GFX_MaxXGet() - 10,
//        GFX_MaxYGet()-10,
//        5,  //Set Hour
//        30, //Set Minute
//        150,
//        true,
//        (GFX_GOL_ANALOGCLOCK_DRAW),                           // draw a beveled button
//        NULL,
//        NULL
//    );
}
	GFX_ColorSet(currentScheme->Color0);
   
	while(GFX_RectangleRoundFillDraw((GFX_MaxXGet() >> 2)+20,10 ,(GFX_MaxXGet() - 10), 60,5)==GFX_STATUS_FAILURE);
	while(GFX_ImageDraw((GFX_MaxXGet() >> 2)+20, 10, (void *) &file_browser)==GFX_STATUS_FAILURE);

       GFX_AlphaParamsSet(GFX_ActivePageGet(), (GFX_MaxXGet() >> 2)+15, 5,
                                   BACKGROUND_BUFFER, (GFX_MaxXGet() >> 2)+15, 5,
                                   GFX_ActivePageGet(), (GFX_MaxXGet() >> 2)+15, 5);
     
	while(GFX_AlphaBlendWindow(
                     &GFX_Primitive_instance.alphaArea,
				     (GFX_MaxXGet()) - ((GFX_MaxXGet() >> 2)+20),
				     60,  	
				     GFX_SchemeGetDefaultScheme()->AlphaValue) == GFX_STATUS_FAILURE);
				     		     				  
	GFX_ColorSet(GFX_RGBConvert(255, 102, 0));

    GFX_FontSet((void *) &GOLSmallFont);
    while(GFX_TextStringBoxDraw((GFX_MaxXGet() >> 2) + 80,20,0,0,(GFX_XCHAR *)mainScreenStr,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

}
/*****************************************************************************
 * WORD MsgMainScreen(WORD objMsg, OBJ_HEADER *pObj)
 *****************************************************************************/
uint16_t MsgMainScreen(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{

    switch(GFX_GOL_ObjectIDGet(pObj))
    {   
        case MAIN_SCREEN_ID_COMFORT_BUT:
            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                 screenState = CREATE_COMFORT;   // switch to next state
            }
            return (1);                 // process by default

         case MAIN_SCREEN_ID_SLIDE_SHOW_BUT:

            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {     
                screenState = CREATE_SCROLLING;
            }
            return (1);                 // process by default

        case MAIN_SCREEN_ID_ALPHA_BUT:
            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_ALPHABLEND;
            }

            return (1);                 // Do not process by default

        case MAIN_SCREEN_ID_INFO_BUT:    //Info
            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
		screenState = CREATE_INFO;  
            }
            return (1);                 // Do not process by default

        case MAIN_SCREEN_ID_GRADIENT_BUT:    //Upload

            if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
		screenState = CREATE_GRADIENT;
            }
            return (1);                 // Do not process by default

        case MAIN_SCREEN_ID_SPEED_BUT:   //Performance Screen
            if((objMsg == GFX_GOL_BUTTON_ACTION_RELEASED))
            {

            screenState = CREATE_SPEED;

            }
            return (1);                 // process by default

        default:
            return (1);                 // process by default
    }
}
