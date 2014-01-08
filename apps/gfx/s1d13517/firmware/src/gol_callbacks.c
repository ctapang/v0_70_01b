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
#include "gfx_strings.h"
#include "gfx_screens.h"
#include "gfx_schemes.h"
#include "gol_ids.h"
#include "timer_tick.h"

/*****************************************************************************
 * SECTION: Defines
 *****************************************************************************/
#define GFX_BlockUntilFinished(function)   while(function == GFX_STATUS_FAILURE)

/*****************************************************************************
 * SECTION: Externs
 *****************************************************************************/
extern uint8_t backgroundScheme;
/*****************************************************************************
 * SECTION: Variables
 *****************************************************************************/

/************************************************************************
 Function: WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)

 Overview: This function must be implemented by user. GOLMsg() function 
 		   calls it each time the valid message for the object received.
           
 Input: objMsg - translated message for the object,
        pObj - pointer to the object,
        pMsg - pointer to the non-translated, raw GOL message 

 Output: If the function returns non-zero the message will 
 		 be processed by the object directly affected by the message.
 		 Default action on the object based on the message will be 
 		 performed.
************************************************************************/
bool GFX_GOL_MessageCallback(GFX_GOL_TRANSLATED_ACTION objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{

    // Process messages for demo screens. Each of the
    // demo screens will have its own corresponding message callback
    // functions.
    switch(screenState)
    {

       	case DISPLAY_MAIN:
        case DISPLAY_INFO:
        case DISPLAY_ALPHABLEND:
        case DISPLAY_GRADIENT:
        case DISPLAY_SPEED:
            return (MsgMainScreen(objMsg, pObj));
    
        case DISPLAY_COMFORT:
            return (MsgComfortScreen(objMsg, pObj));

        default:
            return (1); // process message by default
    }
}

/************************************************************************
 Function: WORD GOLDrawCallback()

 Overview: This function must be implemented by user. GOLDraw() function 
 		   calls it each time when GOL objects drawing is completed. User 
 		   drawing should be done here. GOL will not change color, line 
 		   type and clipping region settings while  this function 
 		   returns zero.

 Input: none

 Output: If the function returns non-zero the draw control will be passed 
		to GOL. GOLDraw() can proceed and re-draw objects that needs 
		to be redrawn.
************************************************************************/
bool GFX_GOL_DrawCallback(void)
{
    static uint32_t timeClock = 0;
//    GFX_GOL_ANALOGCLOCK     *pAc;

    switch(screenState)
    {

        case CREATE_BACKGROUND:
            screenState = DISPLAY_BACKGROUND;     // switch to next state
            return (1);

        case DISPLAY_BACKGROUND: 
            CreatePreLoadScreen();
            screenState = CREATE_MAIN;
            return(1);

        case CREATE_MAIN:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);

            CreateMainScreen(1);
            screenState = DISPLAY_MAIN;                                 // switch to next state
            timeClock =0;
            return (1);                                                 // draw objects created

        case DISPLAY_MAIN:
            if((TimerTick_GetTick() - timeClock) >= 5000)
            {
                 timeClock = TimerTick_GetTick();
//                 pAc = (GFX_GOL_ANALOGCLOCK *)GFX_GOL_ObjectFind(MAIN_SCREEN_ID_ANALOG_CLOCK);
//                 GFX_GOL_ObjectStateSet(pAc, GFX_GOL_ANALOGCLOCK_TICK);
            }
            return (1);
                        
        case CREATE_INFO:                     //Use PIP for this screen

            CreateInfo();

            while(GFX_Layer(PIP1, SET_PAGE_START, 164,0) == GFX_STATUS_FAILURE);
            while(GFX_Layer(PIP1, SET_SIZE, GFX_MaxXGet()-164,GFX_MaxYGet()) == GFX_STATUS_FAILURE);
            while(GFX_Layer(PIP1, SET_PAGE, PIP_PAGE_BUFFER, 0) == GFX_STATUS_FAILURE);
            while(GFX_Layer(PIP1, SET_LAYER_START, 160,0) == GFX_STATUS_FAILURE);
            while(GFX_Layer(PIP1, ENABLE, 0, 0) == GFX_STATUS_FAILURE);

            screenState = DISPLAY_INFO;     // switch to next state
            return (0);

	case CREATE_SPEED:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
	    CreateSpeed();
            screenState = CREATE_MAIN;                       // switch to next state
            return (1);                                                 // draw objects created

        case CREATE_COMFORT:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
            CreateComfortScreen();                     // create window and sliders
            screenState = DISPLAY_COMFORT;   // switch to next state
            return (1);                         // draw objects created

        case CREATE_SCROLLING:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);

            GFX_TransitionParametersSet(0,0,PUSH, GFX_ActivePageGet(), BACKGROUND_BUFFER,
                       1,16,LEFT_TO_RIGHT);

            while(GFX_Transition(&GFX_Primitive_instance.transitionParams,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);


            GFX_TransitionParametersSet(0,0,PUSH,BACKGROUND_BUFFER,GFX_ActivePageGet(),
                       1,10,TOP_TO_BOTTOM);

            while(GFX_Transition(&GFX_Primitive_instance.transitionParams,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);

            GFX_TransitionParametersSet(0,0,PUSH,GFX_ActivePageGet(),BACKGROUND_BUFFER,
                       1,8,RIGHT_TO_LEFT);

            while(GFX_Transition(&GFX_Primitive_instance.transitionParams,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);

            GFX_TransitionParametersSet(0,0,PUSH,BACKGROUND_BUFFER,GFX_ActivePageGet(),
                       1,5,BOTTOM_TO_TOP);

            while(GFX_Transition(&GFX_Primitive_instance.transitionParams,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);

            screenState = CREATE_MAIN;
            return(1);                         // draw objects created

        case CREATE_GRADIENT:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
            CreateGradientScreen();                  // create window
            screenState = DISPLAY_GRADIENT;   // switch to next state
            return (1);                         // draw objects created

        case DISPLAY_SCROLLING:
        case DISPLAY_GRADIENT:
        case DISPLAY_COMFORT:
        case DISPLAY_SPEED:
        case DISPLAY_INFO:
            return (1);                         // redraw objects if needed

        case CREATE_ALPHABLEND:
            while(GFX_Layer(PIP1, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
            CreateAlphaBlendScreen();
            screenState = DISPLAY_ALPHABLEND;
            return(1);

        case DISPLAY_ALPHABLEND:

            if((TimerTick_GetTick() - timeClock) >= 500)
            {
        	if(DisplayAlphaBlendScreen() == true)
                    screenState = CREATE_MAIN;
            }
            return (1);                         // redraw objects if needed

        default:
            break;
    }

    return (1); // release drawing control to GOL
}
