/*******************************************************************************
  Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    GFX_GOL_SLIDER_.h

  Summary:
    This is the header file for the slider object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Slider Object.

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


#ifndef _SLIDER_H
#define _SLIDER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <gfx/gfx_gol.h>


/*********************************************************************
 * Object States Definition:
 *********************************************************************/
#define GFX_GOL_SLIDER_FOCUSED     0x0001  // Bit for focus state
#define GFX_GOL_SLIDER_DISABLED    0x0002  // Bit for disabled state
#define GFX_GOL_SLIDER_VERTICAL    0x0004  // Bit for orientation  (0 - horizontal, 1 - vertical)
#define GFX_GOL_SLIDER_SCROLLBAR   0x0010  // Bit for type usage (0 - Slider, 1 - ScrollBar)
#define GFX_GOL_SLIDER_DRAW_THUMB  0x1000  // Bit to indicate that only thumb area must be redrawn
#define GFX_GOL_SLIDER_DRAW_FOCUS  0x2000  // Bit to indicate that only the focus will be redrawn
#define GFX_GOL_SLIDER_DRAW        0x4000  // Bit to indicate whole slider must be redrawn
#define GFX_GOL_SLIDER_HIDE        0x8000  // Bit to remove object from screen

// *****************************************************************************
/*

  Summary:
     Defines the parameters required for a slider/scrollbar Object.

  Description:
    Depending on the GFX_GOL_SLIDER_SCROLLBAR state bit slider or scrollbar mode
    is set. If GFX_GOL_SLIDER_SCROLLBAR is set, mode is scrollbar; if not set
    mode is slider. For scrollbar mode, focus rectangle is not drawn.

  Remarks:

*/

typedef struct {
    GFX_GOL_OBJ_HEADER hdr; // Generic header for all Objects (see GFX_GOL_OBJ_HEADER).
    uint16_t currPos; // Position of the slider relative to minimum.
    uint16_t prevPos; // Previous position of the slider relative to minimum.
    uint16_t range; // User defined range of the slider. Minimum value at 0 and maximum at 0x7FFF.
    uint16_t pos; // Position of the slider in range domain.
    uint16_t page; // User specified resolution to incrementally change the position

    // in range domain.
    uint16_t thWidth; // Thumb width. This is computed internally.

    // User must not change this value.
    uint16_t thHeight; // Thumb width. This is computed internally.
    // User must not change this value.
} GFX_GOL_SCROLLBAR;

// *****************************************************************************
// *****************************************************************************
// Section: Graphics Module Initialization Routines
// *****************************************************************************
// *****************************************************************************

/*********************************************************************
 * Function: GFX_GOL_SLIDER_RangeSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newRange)
 *
 * Summary: This sets the range of the thumb. If this field is changed
 *	    Object must be completely redrawn to reflect the change.
 *
 * Description:
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *        newRange - Value of the new range used.
 *
 * Returns: none
 *
 * Example:
 *   <CODE>
 *	GFX_GOL_SCROLLBAR *pSld;
 *
 *		GFX_GOL_SLIDER_RangeSet(pSld, 100);
 *		// to completely redraw the object when GFX_OBJ_Draw() is executed.
 *		GFX_OBJ_StateSet(pSld, GFX_GOL_SLIDER_DRAW);
 *
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/
void GFX_GOL_ScrollBarRangeSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newRange);

/*********************************************************************
 * Macros:  GFX_GOL_SLIDER_PageGet(pSld)
 *
 * Summary: Returns the current range of the thumb.
 *
 * Description:
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *
 * Returns: Returns the current range of the slider thumb.
 *
 * Example:
 *   <CODE>
 *	uint16_t range;
 *	GFX_GOL_SCROLLBAR *pSld;
 *
 *		range = GFX_GOL_SLIDER_PageGet(pSld);
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/
#define GFX_GOL_ScrollBarRangeGet(pSld)   (((GFX_GOL_SCROLLBAR*)pSld)->range)

/*********************************************************************
 * Function: GFX_GOL_SLIDER_PageSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPage);
 *
 * Summary: This sets the page size of the object.
 *
 * Description: Page size defines the delta change of the thumb position when incremented
 *      	via SldIncPos() or decremented via SldDecPos(). Page size
 *		minimum value is 1. Maximum value is range/2.
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *        newPage - Value of the new page used.
 *
 * Returns: none
 *
 * Example:
 *       See SldIncPos() example.
 *
 * Notes: none
 *
 ********************************************************************/

void GFX_GOL_ScrollBarPageSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPage);

/*********************************************************************
 * Macros:  GFX_GOL_SLIDER_PageGet(pSld)
 *
 * Summary: Returns the current page size of the object.
 *
 * Description: Page size defines the delta change of the thumb position when incremented
 *      	via SldIncPos() or decremented via SldDecPos(). Page size minimum value
 *              is 1. Maximum value is range/2.
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *
 * Returns: Returns the current value of the slider page.
 *
 * Example:
 *   <CODE>
 *	uint16_t page;
 *	GFX_GOL_SCROLLBAR *pSld;
 *
 *		page = GFX_GOL_SLIDER_PageGet(pSld);
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/

#define GFX_GOL_ScrollBarPageGet(pSld)    (((GFX_GOL_SCROLLBAR*)pSld)->page)

/*********************************************************************
 * Macros:  GFX_GOL_SLIDER_PosGet(pSld)
 *
 * Summary: Returns returns the current position of the slider thumb.
 *
 * Description:
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *
 * Returns: Returns the current position of the slider's thumb.
 *
 *<CODE>
 *	#define MAXVALUE 100;
 *
 *	GFX_GOL_SCROLLBAR *pSlider;
 *	DWORD ctr = 0;
 *
 *		// create slider here and initialize parameters
 *		GFX_OBJ_StateSet(pSlider, GFX_GOL_SLIDER_DRAW);
 *		SldDraw(pSlider);
 *
 *		while("some condition") {
 *			GFX_GOL_SLIDER_PosGet(pSlider, ctr);
 *			GFX_OBJ_StateSet(pSlider, GFX_GOL_SLIDER_DRAW_THUMB);
 *			SldDraw(pSlider);
 *			// update ctr here
 *			ctr = "some source of value";
 *		}
 *
 *		if (GFX_GOL_SLIDER_PosGet(pSlider) > (MAXVALUE – 1))
 *		   return 0;
 *		else
 *			"do something else"
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/

#define GFX_GOL_ScrollBarPositionGet(pSld) (((GFX_GOL_SCROLLBAR*)pSld)->pos)

/*********************************************************************
 * Function: GFX_GOL_SLIDER_PosSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPos);
 *
 * Summary: This function sets the position of the slider thumb.
 *
 * Description: Value should be in the set range inclusive. Object must
 *		be redrawn to reflect the change.
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *	  newPos - The new position of the slider's thumb.
 *
 * Returns: none
 *
 * Example:
 *      <CODE>
 *	GFX_GOL_SCROLLBAR *pSlider;
 *	DWORD ctr = 0;
 *
 *		// create slider here and initialize parameters
 *		GFX_OBJ_StateSet(pSlider, GFX_GOL_SLIDER_DRAW);
 *		SldDraw(pSlider);
 *
 *		while("some condition") {
 *			GFX_GOL_SLIDER_PosSet(pSlider, ctr);
 *			GFX_OBJ_StateSet(pSlider, GFX_GOL_SLIDER_DRAW_THUMB);
 *			SldDraw(pSlider);
 *			// update ctr here
 *			ctr = "some source of value";
 *		}
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/

void GFX_GOL_ScrollBarPositionSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPos);

/*********************************************************************
 * Macros:  GFX_GOL_SLIDER_PosInc(pSld)
 *
 * Summary: This macro increment the slider position by the delta
 *	    change (page) value set. Object must be redrawn after
 *	    this function is called to reflect the changes to the object.
 *
 * Description:
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *
 * Returns: none
 *
 *Example:
 *   <CODE>
 *	void ControlSpeed(GFX_GOL_SCROLLBAR* pSld, int setSpeed, int curSpeed)
 *	{
 *		GFX_GOL_SLIDER_PageSet(pSld, 1);					// set page size to 1
 *		if (setSpeed < curSpeed) {
 *       	while(GFX_GOL_SLIDER_PosGet(pSld) < SetSpeed)
 *				GFX_GOL_SLIDER_PosInc(pSld);              	// increment by 1
 *	   	}
 *	   	else if (setSpeed > curSpeed) {
 *	   		while(GFX_GOL_SLIDER_PosGet(pSld) > SetSpeed)
 *				GFX_GOL_SLIDER_PosDec(pSld);              	// decrement by 1
 *  		}
 *	}
 *	</CODE>
 *
 * Notes: none
 *
 ********************************************************************/
#define GFX_GOL_ScrollBarPositionIncrement(pSld)

/*********************************************************************
 * Macros:  #define GFX_GOL_SLIDER_PosDec(pSld)
 *
 * Summary: This macro decrement the slider position by the delta
 *	    change (page) value set. Object must be redrawn after
 *	    this function is called to reflect the changes to the object
 *
 * Description:
 *
 * PreCondition: none
 *
 * Input: pSld - Pointer to the object.
 *
 * Returns: none
 *
 * Example:
 *   See GFX_GOL_SLIDER_PosInc() example.
 *
 * Notes: none
 *
 ********************************************************************/

#define GFX_GOL_ScrollBarPositionDecrement(pSld)
 
/*********************************************************************
 * Function: GFX_GOL_SCROLLBAR *GFX_GOL_SLIDER_Create(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *			       uint16_t bottom, uint16_t state, uint16_t range,
 *			       uint16_t page, uint16_t pos, GFX_GOL_OBJ_SCHEME *pScheme);
 *
 * Overview: This function creates a SLIDER object with the parameters given.
 *
 * Description: Depending on the GFX_GOL_SLIDER_SCROLLBAR state bit slider or scrollbar mode
 *		is set. If GFX_GOL_SLIDER_SCROLLBAR is set, mode is scrollbar; if not set
 *		mode is slider. It automatically attaches the new object into a
 *		global linked list of objects and returns the address of the object.
 *
 * PreCondition: none
 *
 * Input: instance - device instance
 *        ID - Unique user defined ID for the object instance.
 *        left - Left most position of the Object.
 * 	  top - Top most position of the Object.
 *	  right - Right most position of the Object.
 *	  bottom - Bottom most position of the Object.
 *	  state - This defines the initial state of the Object.
 *	  range - This specifies the maximum value of the slider when the
 *		  thumb is on the rightmost position for a horizontal orientation
 *		  and bottom most position for the vertical orientation. Minimum
 *		  value is always at zero.
 *	  page - This is the incremental change of the slider when user action
 *	         requests to move the slider thumb. This value is added or
 *		 subtracted to the current position of the thumb.
 *	  pos - This defines the initial position of the thumb.
 *	  pScheme - The pointer to the style scheme used for the Object.
 *	            Set to NULL if default style scheme is used.
 *
 * Returns: Returns the pointer to the object created.
 *
 * Example:
 *   <CODE>
 *	GFX_GOL_OBJ_SCHEME *pScheme;
 *	GFX_GOL_SCROLLBAR *slider[3];
 *	uint16_t state;
 *
 *		pScheme = GFX_GOL_SCHEMECreate();
 *
 *		// create a slider with
 *		//       range = [0 – 50000]
 *		//       delta = 500
 *		//       initial position = 25000
 *		state = GFX_GOL_SLIDER_DRAW;
 *		slider[0] =GFX_GOL_SLIDER__Create(  5,
 *								150, 145, 285, 181,
 *								state,
 *								50000, 500, 25000,
 *								pScheme);
 *		if (slider[0] == NULL)
 *			return 0;
 *
 *	 	// create a scrollbar with
 *		//       range = [0 – 100]
 *		//       delta = 20
 *		//       initial position = 0
 *
 *		state = GFX_GOL_SLIDER_DRAW|GFX_GOL_SLIDER_SCROLLBAR;
 *	 	slider[1] = GFX_GOL_SLIDER__Create(  6,
 *								150, 190, 285, 220,
 *								state,
 *								100, 20, 0,
 *								pScheme);
 *		if (slider[1] == NULL)
 *			return 0;
 *
 *		// create a vertical slider with
 *		//       range = [0 – 30]
 *		//       delta = 2
 *		//       initial position = 20
 *
 *	 	state = GFX_GOL_SLIDER_DRAW|GFX_GOL_SLIDER_VERTICAL;
 *		slider[2] = GFX_GOL_SLIDER__Create(  7,
 *								120, 145, 140, 220,
 *								state,
 *								30, 2, 20,
 *								pScheme);
 *		if (slider[2] == NULL)
 *			return 0;
 *
 *	// draw the sliders
 *		while(!sldDraw(slider[0]);		// draw the horizontal slider
 *		while(!sldDraw(slider[1]);		// draw the horizontal scroll bar
 *		while(!sldDraw(slider[2]);		// draw the vertical slider
 *		return 1;
 *	</CODE>
 *
 * Side Effects: none
 *
 ********************************************************************/
GFX_GOL_SCROLLBAR *GFX_GOL_ScrollBarCreate
        (
        uint16_t ID,
        uint16_t left,
        uint16_t top,
        uint16_t right,
        uint16_t bottom,
        uint16_t state,
        uint16_t range,
        uint16_t page,
        uint16_t pos,
        GFX_GOL_OBJ_SCHEME *pScheme
        );

/*********************************************************************
 * Function: void SldMsgDefault(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 * Overview: This function performs the actual state change
 *			based on the translated message given. The following state changes
 *			are supported:
 *	<TABLE>
 *    	Translated Message   Input Source	  Set/Clear State Bit	Description
 *     	##################   ############	  ######     			###########
 *     	GFX_GOL_SLIDER_MSG_INC       	 Touch Screen,	  Set GFX_GOL_SLIDER_DRAW_THUMB  	Slider will be redrawn with thumb in the incremented position.
 *     					      Keyboard
 *		GFX_GOL_SLIDER_MSG_DEC	 		 Touch Screen, 	  Set GFX_GOL_SLIDER_DRAW_THUMB	Slider will be redrawn with thumb in the decremented position.
 *							  Keyboard
 *	</TABLE>
 *
 * PreCondition: none
 *
 * Input: translatedMsg - The translated message.
 *        pSld          - The pointer to the object whose state will be modified.
 *        pMsg          - The pointer to the GOL message.
 *
 * Output: none
 *
 * Example:
 *	Usage is similar to BtnTranslateMsg() example.
 *
 * Side Effects: none
 *
 ********************************************************************/
void GFX_GOL_ScrollBarMsgDefault(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
 * Function: uint16_t SldTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Overview: This function evaluates the message from a user if the
 *			message will affect the object or not. The table below
 *			enumerates the translated messages for each event of the
 *			touch screen and keyboard inputs.
 *
 *	<TABLE>
 *    	Translated Message   Input Source  Events         				Description
 *     	##################   ############  ######         				###########
 *		GFX_GOL_SLIDER_MSG_INC			 Touch Screen  EVENT_PRESS, EVENT_MOVE		If events occurs and the x,y position falls in the area of the slider and the slider position is to the LEFT of the x,y position for a horizontal slider or BELOW the x,y position for a vertical slider.
 *							 Keyboard 	   EVENT_KEYSCAN				If event occurs and parameter1 passed matches the object’s ID and parameter 2 passed matches SCAN_UP_PRESSED or SCAN_LEFT_PRESSED.
 *		GFX_GOL_SLIDER_MSG_DEC			 Touch Screen  EVENT_PRESS, EVENT_MOVE		If events occurs and the x,y position falls in the area of the slider and the slider position is to the RIGHT of the x,y position for a horizontal slider or ABOVE the x,y position for a vertical slider.
 *							 Keyboard	   EVENT_KEYSCAN				If event occurs and parameter1 passed matches the object’s ID and parameter 2 passed matches SCAN_DOWN_PRESSED or SCAN_RIGHT_PRESSED.
 *		OBJ_MSG_PASSIVE		 Touch Screen  EVENT_RELEASE				If events occurs and the x,y position falls in the area of the slider.
 *		OBJ_MSG_INVALID		 Any		   Any							If the message did not affect the object.
 *	</TABLE>
 *
 * PreCondition: none
 *
 * Input: pSld  - The pointer to the object where the message will be
 *				 evaluated to check if the message will affect the object.
 *        pMsg  - Pointer to the message struct containing the message from
 *        		 the user interface.
 *
 * Output: Returns the translated message depending on the received GOL message:
 *		  - GFX_GOL_SLIDER_MSG_INC – Increment slider position
 *         - GFX_GOL_SLIDER_MSG_DEC – Decrement slider position
 *     	  - OBJ_MSG_PASSIVE – Slider is not affected
 *     	  - OBJ_MSG_INVALID – Slider is not affected
 *
 * Example:
 *	Usage is similar to BtnTranslateMsg() example.
 *
 * Side Effects: none
 *
 ********************************************************************/
uint16_t SldTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
 * Function: uint16_t SldDraw(void *pObj)
 *
 * Overview: This function renders the object on the screen using
 * 			the current parameter settings. Location of the object is
 *			determined by the left, top, right and bottom parameters.
 *			The colors used are dependent on the state of the object.
 *
 *			When rendering objects of the same type, each object
 *			must be rendered completely before the rendering of the
 *			next object is started. This is to avoid incomplete
 *			object rendering.
 *
 * PreCondition: Object must be created before this function is called.
 *
 * Input: pSld - Pointer to the object to be rendered.
 *
 * Output: Returns the status of the drawing
 *		  - 1 - If the rendering was completed and
 *		  - 0 - If the rendering is not yet finished.
 *		  Next call to the function will resume the
 *		  rendering on the pending drawing state.
 *
 * Example:
 *   See SldCreate() example.
 *
 * Side Effects: none
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_ScrollBarDraw(void *pObj);
#endif //_SLIDER_H
