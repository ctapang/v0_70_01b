/***********************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    gfx_transitions.h

  Summary:

  Description:

***********************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END


#ifndef _TRANSITIONS_H
    #define _TRANSITIONS_H

    #include "gfx_primitive.h"

/*********************************************************************
* Overview: Transition type enumeration to determine the type of 
*           the transition. Each type will require specific parameters when
*           setting up the transition operation (GFXSetupTransition() or
*           GFXTransition()).
*
*	<TABLE>
*    	GFX_TRANSITION_TYPE         param1              param2 (sets the direction of transition)
*     	########################    ################    ###################################################
*		PLAIN                       pixel block size    not used
*		EXPANDING_RECTANGLE         pixel block size    not used
*		CONTRACTING_RECTANGLE       pixel block size    not used
*		SLIDE                       pixel block size    LEFT_TO_RIGHT, RIGHT_TO_LEFT, TOP_TO_BOTTOM, BOTTOM_TO_TOP
*		PUSH                        pixel block size    LEFT_TO_RIGHT, RIGHT_TO_LEFT, TOP_TO_BOTTOM, BOTTOM_TO_TOP
*		EXPANDING_LINE              pixel block size    HORIZONTAL, VERTICAL
*		CONTRACTING_LINE            pixel block size    HORIZONTAL, VERTICAL  				
*	</TABLE>

*********************************************************************/
typedef enum 
{
    EXPANDING_RECTANGLE = 0, // param1 -> Pixel-block size
    CONTRACTING_RECTANGLE,   // param1 -> Pixel-block size 
    SLIDE,                   // param1 -> Pixel-block size, param2 -> Sliding direction  LEFT_TO_RIGHT/RIGHT_TO_LEFT/TOP_TO_BOTTOM/BOTTOM_TO_TOP 
    PUSH,                    // param1 -> Pixel-block size, param2 -> Sliding direction  LEFT_TO_RIGHT/RIGHT_TO_LEFT/TOP_TO_BOTTOM/BOTTOM_TO_TOP        
    EXPANDING_LINE,          // param1 -> Pixel-block size, param2 -> direction  HORIZONTAL/VERTICAL 
    CONTRACTING_LINE         // param1 -> Pixel-block size, param2 -> direction  HORIZONTAL/VERTICAL  
} GFX_TRANSITION_TYPE;

/*********************************************************************
* Overview: Direction enumeration to determine the direction of the 
*           selected GFX_TRANSITION_TYPE. 
*********************************************************************/
typedef enum 
{
    LEFT_TO_RIGHT = 0,		      // option used in SLIDE, PUSH transition type (GFX_TRANSITION_TYPE)
    RIGHT_TO_LEFT,			// option used in SLIDE, PUSH transition type (GFX_TRANSITION_TYPE)
    TOP_TO_BOTTOM,			// option used in SLIDE, PUSH transition type (GFX_TRANSITION_TYPE)
    BOTTOM_TO_TOP,			// option used in SLIDE, PUSH transition type (GFX_TRANSITION_TYPE)
    HORIZONTAL,				// option used in EXPANDING_LINE and CONTRACTING_LINE transition type (GFX_TRANSITION_TYPE) 
    VERTICAL				// option used in EXPANDING_LINE and CONTRACTING_LINE transition type (GFX_TRANSITION_TYPE)
} GFX_TRANSITION_DIRECTION;

/************************************************************************
* Function: uint8_t GFX_PRIM_SetTransitionParameters(short left, short top, short width, 
*                                   short height, GFX_TRANSITION_TYPE type, 
*                                   uint16_t delay_ms, uint16_t param1, uint16_t param2)
*
* Overview: This sets up the transition effect using the GFX_TRANSITION_TYPE 
*           and the given parameters. The actual transition execution will  
*           occur when GFXExecutePendingTransition() is called. When 
*           DOUBLE_BUFFERING is enabled, GFXExecutePendingTransition() is 
*           executed after the current screen is fully rendered.
*                                                                       
* Input:    left - left x coordinate
*           top - top y coordinate
*           right - right x coordinate
*           bottom - bottom y coordinate
*           type - Transition type
*           delay_ms - Delay in milli seconds between redraws in the 
*                      screen while executing the transition
*           param1 - Transition-type specific parameter
*           param2 - Transition-type specific parameter
*                                                                       
* Output:   Returns success of the setup 
*           - 0 : Parameters successfully saved for the new transition
*           - -1 : Parameters not saved, there is a pending transition 
*                                                                       
************************************************************************/
uint8_t GFX_SetTransitionParameters(short left, short top, GFX_TRANSITION_TYPE type, uint8_t sourcePage, 
                                         uint8_t destinationPage, uint16_t delay_ms, uint16_t param1, 
                                         uint16_t param2);

/************************************************************************
* Function: BYTE GFX_PRIMITIVE_Transition(short left, short top, short right,
*                              short bottom, GFX_TRANSITION_TYPE type, 
*                              DWORD srcpageaddr, DWORD destpageaddr,
*                              uint16_t delay_ms, uint16_t param1, uint16_t param2)
*                                                                       
* Overview: This immediately executes the transition effect using the
*           GFX_TRANSITION_TYPE and the given parameters. 
*                                                                       
* Input:    transitionParams    
*                                                                       
* Output:   Returns status of transition
*           - 0  : Transition executed successfully
*           - -1 : Transition not executed
*                                                                       
************************************************************************/
GFX_STATUS GFX_Transition(GFX_TRANSITION_PARAMS* transitionParams, short width, short height);

#endif
