/*******************************************************************************
  Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_round_dial.h

  Summary:
    This is the header file for the round dial object of the GOL.

  Description:
   Refer to Microchip Graphics Library for complete documentation of the
   Round dial Object.
*******************************************************************************/

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


#ifndef _ROUNDDIAL_H
    #define _ROUNDDIAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
    #include <gfx/gfx_gol.h>

/*********************************************************************
* Object States Definition: 
*********************************************************************/
    #define GFX_GOL_ROUNDDIAL_FOCUSED      0x0001
    #define GFX_GOL_ROUNDDIAL_DISABLED     0x0002  // Bit for disabled state.
    #define GFX_GOL_ROUNDDIAL_WRAPAROUND   0x0008  // is the control allowed to wrap around
    #define GFX_GOL_ROUNDDIAL_ANIMATE      0x0040  /*control is animated (moves to next position in small steps)*/
    #define GFX_GOL_ROUNDDIAL_ROTATING     0x1000  // currently moving to a new target
    #define GFX_GOL_ROUNDDIAL_DRAW_BAR     0x2000  // control bar should be redrawn
    #define GFX_GOL_ROUNDDIAL_DRAW         0x4000  // Bit to indicate object must be redrawn.
    #define GFX_GOL_ROUNDDIAL_HIDE         0x8000  // Bit to indicate object must be removed from screen.

#if !defined(ROUNDDIALITEM_SIZE)
#define ROUNDDIALITEM_SIZE  4
#endif

// the structure containing data for each item in the list
typedef struct
{
    GFX_XCHAR   text[ROUNDDIALITEM_SIZE];       // the text
    int16_t   iData;                          // a number to associate with the text
} ROUNDDIALITEM;

uint16_t GFX_GOL_RoundDialWrap(int16_t kX, const int16_t kLowerBound, const int16_t kUpperBound);

// *****************************************************************************
/*

  Summary:
     Defines the parameters required for a dial Object.

  Description:
    The curr_xPos, curr_yPos, new_xPos and new_yPos parameters
    are internally generated to aid in the redrawing of the
    dial. User must avoid modifying these values.

  Remarks:

*/
typedef struct
{
    GFX_GOL_OBJ_HEADER      hdr;        // Generic header for all Objects (see GFX_OBJ_HEADER).
    
    // an array of items to display in the listwheel
    const ROUNDDIALITEM*  pItems;
    uint16_t          nItems;
    uint16_t          pos;            // current target position in integer final units
    int16_t           posOffset;        // position offset from final position
    int16_t           velocity;       // direction and speed of movement
    short             bandHeight;     // size of the central band where the selected text is drawn
    short             numericRange;   // how many text values either side of selected are visible on wheel
    short             center;         // central position (depending on vertical or horizontal alignment)
    uint8_t           radius;
    GFX_ALIGNMENT     alignment;
} GFX_GOL_ROUNDDIAL;

GFX_STATUS DrawBand(GFX_GOL_ROUNDDIAL* pDia, int16_t left, int16_t top, int16_t right, int16_t bottom);

/*********************************************************************
* Function: GFX_GOL_ROUNDDIAL  *GFX_GOL_RoundDialCreate(uint16_t ID, uint16_t x, uint16_t y, uint16_t radius,
*						uint16_t state, uint16_t res, uint16_t value, uint16_t max,
*						GFX_GOL_OBJ_SCHEME *pScheme);
*
* Summary: This function creates a ROUNDDIAL object with the parameters given.
*
*
* Description: It automatically attaches the new object into a global linked list of
*			objects and returns the address of the object.
*
* PreCondition: none
*
* Input: ID - Unique user defined ID for the object instance.
*        x - Location of the center of the dial in the x coordinate.
*        y - Location of the center of the dial in the y coordinate.
* 		 radius - Defines the radius of the dial. 
*        state - Sets the initial state of the object.
*        res - Sets the resolution of the dial when rotating clockwise or
*			   counter clockwise.
*        value - Sets the initial value of the dial.
*        max - Sets the maximum value of the dial.
*        pScheme - Pointer to the style scheme used.
*
* Returns: Returns the pointer to the object created.
*
* Example:
*   <CODE> 
*	GFX_GOL_OBJ_SCHEME *pScheme;
*	GFX_GOL_ROUNDDIAL *pDial;
*	uint16_t state;
*	
*		pScheme = GFX_GOL_SchemeCreate();
*		state = GFX_GOL_ROUNDDIAL_DRAW;
*
*		// creates a dial at (50,50) x,y location, with an initial value
*		// of 50, a resolution of 2 and maximum value of 100.
*		pDial = GFX_GOL_RoundDial_Create(1,50,50,25,118,0, state, 2, 50, 100, pScheme);
*		// check if dial was created
*		if (pDial == NULL)		
*		   return 0;
*
*		return 1;
*	</CODE> 
*
* Notes: none
*
********************************************************************/
GFX_GOL_ROUNDDIAL *GFX_GOL_RoundDialCreate
(
    uint16_t ID,
    int16_t left,
    int16_t top,
    int16_t right,
    int16_t bottom,
    uint8_t rad,
    uint16_t state,
    const ROUNDDIALITEM* pItems,
    uint16_t nItems,
    uint16_t startPos,
    GFX_ALIGNMENT alignment,
    GFX_GOL_OBJ_SCHEME  *pScheme
);

/*********************************************************************
* Function: GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
* Overview: This function evaluates the message from a user if the 
*			message will affect the object or not. The table below enumerates the translated 
*			messages for each event of the touch screen inputs.
*
*	<TABLE>
*    	Translated Message      Input Source  Events        Description
*     	#####################   ############  ######        ###########
*     	RD_MSG_CLOCKWISE        Touch Screen  EVENT_MOVE	If events occurs and the x,y position falls in the face of the Dial and moving in the clockwise rotation.
*		RD_MSG_CTR_CLOCKWISE    Touch Screen  EVENT_MOVE	If events occurs and the x,y position falls in the face of the Dial and moving in the counter clockwise rotation.     					      			   
*		OBJ_MSG_INVALID		    Any		      Any			If the message did not affect the object.							 
*	</TABLE>
*
* PreCondition: none
*
* Input: pDia  - The pointer to the object where the message will be
*				 evaluated to check if the message will affect the object.
*        pMsg  - Pointer to the message struct containing the message from 
*        		 the user interface.
*
* Output: Returns the translated message depending on the received GOL message:
*		  - RD_MSG_CLOCKWISE – Dial is moved in a clockwise direction.
*         - RD_MSG_CTR_CLOCKWISE – Dial is moved in a counter clockwise direction.
*         - GFX_GOL_MSG_INVALID – Dial is not affected
*
* Example:
*   <CODE> 
*	void MyGOLMsg(GFX_GOL_MESSAGE *pMsg){
*
*		GFX_OBJ_HEADER *pCurrentObj;
*		uint16_t objMsg;
*			
*		if(pMsg->event == EVENT_INVALID)
*			return;
*		pCurrentObj = GFX_OBJ_ListGet();
*		
*		while(pCurrentObj != NULL){
*			// Process only ROUNDDIAL
*			if(!GFX_OBJ_IsUpdatePending(pCurrentObj)){
*				switch(pCurrentObj->type){
*					case OBJ_ROUNDIAL:
*						objMsg = RdiaTranslateMsg((ROUNDDIAL*)pCurrentObj, pMsg);
*						if(objMsg == OBJ_MSG_INVALID)
*							break;
*						if(GFX_GOL_MESSAGECallback(objMsg,pCurrentObj,pMsg))
*							RdiaMsgDefault(objMsg,(ROUNDDIAL*)pCurrentObj);
*						break;
*					default: break;	
*				}
*			}
*		}
*		pCurrentObj = pCurrentObj->pNxtObj;
*	}
*	</CODE> 
*
* Side Effects: none
*
********************************************************************/
GFX_GOL_TRANSLATED_ACTION        GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg);

/*****************************************************************************************
  Function:
     GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
    
  Description:
    This function performs the actual state change based on the translated
    message given. The following state changes are supported:
    <table>
    Translated             \Input   Set/Clear State Bit Description
     Message                Source   
    \                               
    RD_MSG_CLOCKWISE       Touch    Set GFX_GOL_ROUNDDIAL_ROT_CW, Dial will be
                            Screen   redrawn with clockwise update. Set
                                     GFX_GOL_ROUNDDIAL_DRAW
    RD_MSG_CTR_CLOCKWISE   Touch    Set GFX_GOL_ROUNDDIAL_ROT_CCW, Dial will be
                            Screen   redrawn with counter clockwise update. Set
                                     GFX_GOL_ROUNDDIAL_DRAW
    </table>
  Conditions:
    none
  Input:
    translatedMsg -  The translated message
    pDia -           The pointer to the object whose state will be modified
    pMsg -           The pointer to the GOL message
  Return:
    none
  Example:
    See RdiaTranslateMsg() example.
  Side Effects:
    none                                                                                  
  *****************************************************************************************/
void        GFX_GOL_RoundDailActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg);

/**************************************************************************
  Function:
     uint16_t GFX_GOL_RoundDialDraw(void *pObj)
    
  Description:
    This function renders the object on the screen using the current
    parameter settings. Location of the object is determined by the center
    (x,y) position and the radius parameters. The colors used are dependent
    on the state of the object.
    
    When rendering objects of the same type, each object must be rendered
    completely before the rendering of the next object is started. This is
    to avoid incomplete object rendering.
  Conditions:
    Object must be created before this function is called.
  Input:
    pDia -  Pointer to the object
  Return:
    \Returns the status of the drawing
      * 1 &#45; If the rendering was completed and
      * 0 &#45; If the rendering is not yet finished.
  Side Effects:
    none                                                                   
  **************************************************************************/
GFX_STATUS GFX_GOL_RoundDialDraw(void *pObject);
#endif // _ROUNDDIAL_H
