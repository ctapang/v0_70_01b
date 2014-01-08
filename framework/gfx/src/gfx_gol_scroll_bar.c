/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_scroll_bar.c

  Summary:
    This implements the scroll bar object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Slider Object.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#include <stdlib.h>
#include <stdint.h>
#include "gfx/gfx_gol_scroll_bar.h"
#include "gfx/gfx_gol_scan_codes.h"

typedef union
{
    struct
    {
        uint8_t uint328BitValue[4];
    };

    struct
    {
        uint16_t uint3216BitValue[2];
    };

    uint32_t uint32Value;
}SLIDER_UINT32_UNION;

/* Internal Functions */
short SldSetThumbSize(GFX_GOL_SCROLLBAR *pSld, short high, short low);
void SldGetMinMaxPos(GFX_GOL_SCROLLBAR *pSld, uint16_t *minPos, uint16_t *maxPos);
uint16_t SldGetWidth(GFX_GOL_SCROLLBAR *pSld);
uint16_t SldGetHeight(GFX_GOL_SCROLLBAR *pSld);

/*********************************************************************
 * Function: GFX_GOL_SCROLLBAR *GFX_GOL_Slider_Create(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *							  uint16_t bottom, uint16_t state, uint16_t range,
 *							  uint16_t page, uint16_t pos, GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Notes: Creates a SLIDER object and adds it to the current active list.
 *        If the creation is successful, the pointer to the created Object
 *        is returned. If not successful, NULL is returned.
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
        )
{
    GFX_GOL_SCROLLBAR *pSld = NULL;

    pSld = (GFX_GOL_SCROLLBAR *) GFX_malloc(sizeof (GFX_GOL_SCROLLBAR));
    if (pSld == NULL)
        return (pSld);

    //pSld->hdr.instance = instance; //Device Instance set
    pSld->hdr.ID = ID; // unique id assigned for referencing
    pSld->hdr.pNxtObj = NULL;
    pSld->hdr.type = GFX_GOL_SCROLLBAR_TYPE; // set object type
    pSld->hdr.left = left; // left and right should be equal when oriented vertically
    pSld->hdr.top = top; // top and bottom should be equal when oriented horizontally
    pSld->hdr.right = right;
    pSld->hdr.bottom = bottom;
    pSld->hdr.state = state;
    pSld->hdr.DrawObj = GFX_GOL_ScrollBarDraw; // draw function
    pSld->hdr.actionGet = GFX_GOL_ScrollBarActionGet; // message function
    pSld->hdr.actionSet = GFX_GOL_ScrollBarActionSet; // default message function
    pSld->hdr.FreeObj = NULL; // default free function

    // Parameters in the user defined range system (pos, page and range)
    pSld->range = range; // range of the slider movement (always measured from 0 to range)

    // 0 refers to pSld->minPos and
    // range refers to pSld->maxpos where: minPos and maxPos are
    // the coordinate equivalent of 0 and range value
    pSld->page = page; // set the resolution
    pSld->pos = pos; // set the initial position

    // calculate the thumb width and height
    pSld->thWidth = SldGetWidth(pSld);
    pSld->thHeight = SldGetHeight(pSld);

    // Set the color scheme to be used
    pSld->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme; // user defined scheme

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pSld); // add the new object to the current list
    return (pSld);
}

/*********************************************************************
 * Function: short SldSetThumbSize(GFX_GOL_SCROLLBAR *pSld, short high, short low)
 *
 * Notes: An INTERNAL function used to compute for the width or
 *        height of the thumb. This function is created to save
 *        code size. This function is called only to dynamically
 *        compute for the thumb size. Used only when slider is
 * 		 type Scrollbar. Parameter are defined as:
 *		 pSld - pointer to the object
 *        high - higher value to be used
 *        low  - lower value to be used
 *
 ********************************************************************/
short SldSetThumbSize(GFX_GOL_SCROLLBAR *pSld, short high, short low)
{
    uint16_t temp;

    temp = (pSld->range / pSld->page);
    temp = (high - low) / temp;

    // when size is less than half of emboss size, set the
    // size to half the emboss size. This is to make sure
    // thumb will always have a size.
    if (temp < (GFX_GOL_EMBOSS_SIZE << 1))
        temp = (GFX_GOL_EMBOSS_SIZE << 1);

    return (short) temp;
}

/*********************************************************************
 * Function: uint16_t SldGetWidth(GFX_GOL_SCROLLBAR *pSld)
 *
 * Notes: An INTERNAL function that computes for the width
 *        of the thumb. This function is created to save
 *        code size. This function is called only to dynamically
 *        compute for the thumb size.
 *
 ********************************************************************/
uint16_t SldGetWidth(GFX_GOL_SCROLLBAR *pSld)
{
    uint16_t temp;

    /*
                Calculating the width is dependent on the mode type.
                If type Scrollbar, width is dependent on the ratio of the
                page/range = width/max-min (see SetThumbSize())
                if type is Slider, width is dependent on height*3/8
		
                When horizontal width is dynamic, height is contant.
	
     */
    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
    {
        temp = pSld->hdr.right - pSld->hdr.left;
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
        {
            temp = temp - (GFX_GOL_EMBOSS_SIZE << 1);
        }
        else
        {
            temp = temp - (GFX_GOL_EMBOSS_SIZE << 1) - 2;
        }
    }
    else
    {
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
        {
            temp = SldSetThumbSize(pSld, pSld->hdr.right, pSld->hdr.left);
        }
        else
        {
            temp = (((pSld->hdr.bottom - pSld->hdr.top) - (GFX_GOL_EMBOSS_SIZE << 1) - 2) * 3) >> 3;
        }
    }

    // to avoid calculations of dividing by two, we store half the width value
    return (temp >> 1);
}

/*********************************************************************
 * Function: uint16_t SldGetHeight(GFX_GOL_SCROLLBAR *pSld)
 *
 * Notes: An INTERNAL function that computes for the height
 *        of the thumb. This function is created to save
 *        code size. This function is called only to dynamically
 *        compute for the thumb size.
 *
 ********************************************************************/
uint16_t SldGetHeight(GFX_GOL_SCROLLBAR *pSld)
{
    uint16_t temp;

    /*
                Calculating the height is dependent on the mode type.
                If type Scrollbar, width is dependent on the ratio of the
                page/range = width/max-min (see SetThumbSize())
                if type is Slider, width is dependent on width*3/8
	
                When vertical height is dynamic, width is contant.
     */
    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
    {
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
        {
            temp = SldSetThumbSize(pSld, pSld->hdr.bottom, pSld->hdr.top);
        }
        else
        {
            temp = (((pSld->hdr.right - pSld->hdr.left) - (GFX_GOL_EMBOSS_SIZE << 1) - 2) * 3) >> 3;
        }
    }
    else
    {
        temp = pSld->hdr.bottom - pSld->hdr.top;
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
        {
            temp = temp - (GFX_GOL_EMBOSS_SIZE << 1);
        }
        else
        {
            temp = temp - (GFX_GOL_EMBOSS_SIZE << 1) - 2;
        }
    }

    // to avoid calculations of dividing by two, we store half the height value
    return (temp >> 1);
}

/*********************************************************************
 * Function: void SldGetMinMaxPos(GFX_GOL_SCROLLBAR *pSld, uint16_t *min, uint16_t *max)
 *
 * Notes:  An INTERNAL function that computes for the minimum
 *         and maximum pixel position in the screen. This function is
 *         created to save code size. Used to define the minimum
 *         & maximum position of the thumb when sliding. Parameters
 *		  used are defined as:
 *		  pSld - pointer to the object
 *         min  - pointer to the minimum variable
 *         max  - pointer to the maximum variable
 *
 ********************************************************************/
void SldGetMinMaxPos(GFX_GOL_SCROLLBAR *pSld, uint16_t *min, uint16_t *max)
{
    uint16_t temp;

    // calculate maximum and minimum position	
    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
    {
        temp = pSld->thHeight + GFX_GOL_EMBOSS_SIZE;
        *min = pSld->hdr.top + temp;
        *max = pSld->hdr.bottom - temp;
    }
    else
    {
        temp = pSld->thWidth + GFX_GOL_EMBOSS_SIZE;
        *min = pSld->hdr.left + temp;
        *max = pSld->hdr.right - temp;
    }

    // for aestetics.
    if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
    {
        *min = *min + 2;
        *max = *max - 2;
    }
}

/*********************************************************************
 * Function: void GFX_Slider_SetRange(GFX_GOL_SCROLLBAR *pSld, uint16_t newRange)
 *
 * Notes:  Sets the new range value of the slider or scrollbar.
 *         Object must be redrawn after this function is called to
 *         reflect the changes to the object.
 *
 ********************************************************************/
void GFX_GOL_ScrollBarRangeSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newRange)
{
    uint16_t newPos;
    uint32_t dTemp;

    // this checks for limits of the range (minimum is 2)
    if (newRange <= 2)
        newRange = 2;

    if ((uint16_t) newRange > (uint16_t) 0x7FFF)
        newRange = 0x7FFF;

    dTemp = newRange * pSld->pos;
    dTemp = dTemp / pSld->range;

    // get new range
    newPos = (uint16_t)dTemp;

    // set the new range
    pSld->range = newRange;

    // now check the page, adjust when necessary
    // page maximum limit is range/2, minimum is 1
    if (pSld->page > ((pSld->range) >> 1))
    {
        if (!((pSld->range) >> 1))
            pSld->page = 1;
        else
            pSld->page = (pSld->range) >> 1;
    }

    // calculate new thumb width and height
    pSld->thWidth = SldGetWidth(pSld);
    pSld->thHeight = SldGetHeight(pSld);
    GFX_GOL_ScrollBarPositionSet(pSld, newPos);
}

/*********************************************************************
 * Function: void GFX_Slider_SetPage(GFX_GOL_SCROLLBAR *pSld, uint16_t newPage)
 *
 * Notes: Sets the new page value of the slider or scrollbar.
 *        The page maximum limit is range/2, minimum is 1
 *
 ********************************************************************/
void GFX_GOL_ScrollBarPageSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPage)
{
    if (newPage < 1)
        newPage = 1;
    else if (newPage > ((pSld->range) >> 1))
        newPage = (pSld->range) >> 1;
    pSld->page = newPage;

    // calculate new thumb width and height
    pSld->thWidth = SldGetWidth(pSld);
    pSld->thHeight = SldGetHeight(pSld);
}

/*********************************************************************
 * Function: GFX_GOL_ScrollBarPositionSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPos)
 *
 * Notes: Sets the thumb to the new position. Checking is first
 *        preformed if the new position is within the range (0 to range)
 *        of the slider. Object must be redrawn after this function is called to
 *        reflect the changes to the object.
 *
 ********************************************************************/
void GFX_GOL_ScrollBarPositionSet(GFX_GOL_SCROLLBAR *pSld, uint16_t newPos)
{
    uint16_t minPos, maxPos, relPos;
    uint32_t dTemp;

    // get minimum and maximum positions
    SldGetMinMaxPos(pSld, &minPos, &maxPos);
    dTemp = 0;

#ifndef GFX_GOL_SLIDER_INVERT_VERTICAL

    // check if the new value is still in range
    if (newPos <= 0)
    {
        pSld->pos = 0; // set to zero in range domain
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
        { // min and max in vertical is inverted
            pSld->currPos = maxPos; // minimum position is the bottom position in
        } // coordinate domain
        else
            pSld->currPos = minPos; // minimum is left most position in coordinate domain
    }
    else if (newPos >= pSld->range)
    {
        pSld->pos = pSld->range; // set to maximum value in range domain
        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
        { // min and max in vertical is inverted
            pSld->currPos = minPos; // maximum position is the top position in
        } // coordinate domain
        else
            pSld->currPos = maxPos; // maximum is right most position in coordinate domain
    }
    else
    {
        pSld->pos = newPos; // get new position in range domain
        dTemp |= (uint32_t)(newPos<<16);
        dTemp = dTemp / pSld->range;
        dTemp = (maxPos - minPos) * dTemp;

        // set current position in coordinate domain
        relPos = (dTemp>>16) + minPos;

        if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
        { // test if we need to transform min and max position
            pSld->currPos = maxPos - (relPos - minPos); // min and max position is swapped in coordinate domain
        }
        else
            pSld->currPos = relPos; // use position
    }

#else

    // check if the new value is still in range
    if (newPos <= 0)
    {
        pSld->pos = 0; // set to zero in range domain
        pSld->currPos = minPos; // set to minimum in coordinate domain
    }
    else if (newPos >= pSld->range)
    {
        pSld->pos = pSld->range; // set to maximum value in range domain
        pSld->currPos = maxPos; // set to minimum in coordinate domain
    }
    else
    {
        pSld->pos = newPos; // get new position in range domain
        dTemp.w[1] = newPos;
        dTemp.Val = dTemp.Val / pSld->range;
        dTemp.Val = (maxPos - minPos) * dTemp.Val;

        // set current position in coordinate domain
        pSld->currPos = dTemp.w[1] + minPos;
    }

#endif // ifndef GFX_GOL_SLIDER_INVERT_VERTICAL
}

/*********************************************************************
 * Function: void GFX_GOL_ScrollBarMsgDefault(uint16_t translatedMsg, void *pObj,
 *							   GFX_GOL_MESSAGE* pMsg)
 *
 * Notes: This the default operation to change the state of the button.
 *		 Called inside GFX_GOL_Message() when GFX_GOL_MessageCallback() returns a 1.
 *
 ********************************************************************/
void GFX_GOL_ScrollBarActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_SCROLLBAR *pSld;

    pSld = (GFX_GOL_SCROLLBAR *) pObject;

#ifdef USE_TOUCHSCREEN

    uint16_t newPos, minPos, maxPos;
    uint32_t dTemp;

#ifdef USE_FOCUS
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {
        if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DRAW_FOCUS_STATE))
        {
            GFX_GOL_FocusSet((GFX_GOL_HEADER *) pSld);
        }
    }

#endif // USE_FOCUS

    // if message was passive do not do anything
    if (translatedMsg == GFX_GOL_OBJECT_ACTION_PASSIVE)
        return;

    // get the min and max positions
    SldGetMinMaxPos(pSld, &minPos, &maxPos);

    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
        if ((translatedMsg == GFX_GOL_SCROLLBAR_ACTION_DEC) || (translatedMsg == GFX_GOL_SCROLLBAR_ACTION_INC))
        {

            // newPos in this context is used in the coordinate domain
            if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
            { // check if Horizontal or Vertical orientation
                if (pMessage->param1 <= minPos)
                { // Horizontal orientation: test x position
                    newPos = minPos; // beyond minimum, use min position
                }
                else if (pMessage->param1 >= maxPos)
                {
                    newPos = maxPos; // beyond maximum, use max position
                }
                else
                {
                    newPos = pMessage->param1; // within range: use x position given
                }
            }
            else
            {
                if (pMessage->param2 <= minPos)
                { // Vertical orientation: test y position
                    newPos = minPos; // beyond minimum, use min position
                }
                else if (pMessage->param2 >= maxPos)
                {
                    newPos = maxPos; // beyond maximum, use max position
                }
                else
                {
                    newPos = pMessage->param2; // within range: use y position given
                }
            }

            if (newPos != pSld->currPos)
            { // check if we need to redraw thumb
                // yes redraw is needed, translate newPos into range domain
                // first get new position in range domain
                dTemp = (uint32_t) (newPos - minPos) * (uint32_t) pSld->range;
                dTemp = dTemp / (maxPos - minPos);
                newPos = (uint16_t)dTemp;

#ifndef GFX_GOL_SLIDER_INVERT_VERTICAL
                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                { // check if we need to swap min and max in vertical
                    newPos = pSld->range - newPos; // min and max is swapped in vertical orientation
                }

#endif
                GFX_GOL_ScrollBarPositionSet(pSld, newPos); // set to new position
                GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_STATE); // redraw the thumb only
            }
            else
                return;
        }
        else
            return;
    }

#endif // USE_TOUCHSCREEN
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
    { // for keyboard
        if (translatedMsg == GFX_GOL_SCROLLBAR_ACTION_INC)
        {
            SldIncPos(pSld); // increment is requested
        }
        else
        {
            SldDecPos(pSld); // decrement is requested
        }

        GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE); // redraw the thumb only
    }

#endif // USE_KEYBOARD
}

// *****************************************************************************
/*  Function:
    uint16_t GFX_GOL_ScrollBarPositionGet(
                                GFX_GOL_SCROLLBAR *pObject)

    Summary:
        This function returns the current position of the scroll bar
        thumb.

    Description:
        This function returns the current position of the scroll bar
        thumb. The thumb is the rectangular area that slides left or
        right (for horizontal orientation) or slides up or down (for
        vertical orientation).

*/
// *****************************************************************************
uint16_t __attribute__ ((always_inline)) GFX_GOL_ScrollBarPositionGet(
                                GFX_GOL_SCROLLBAR *pObject)
{
    return (pObject->pos);
}

/*********************************************************************
 * Function: uint16_t SldTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_ScrollBarActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{

    GFX_GOL_SCROLLBAR *pSld;

    pSld = (GFX_GOL_SCROLLBAR *) pObj;

    // Evaluate if the message is for the slider
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls to the left or right of the center of the thumb's face
        if ((pMsg->uiEvent == EVENT_PRESS) || (pMsg->uiEvent == EVENT_MOVE))
        {
            if
                (
                    (pSld->hdr.left < pMsg->param1) &&
                    (pSld->hdr.right > pMsg->param1) &&
                    (pSld->hdr.top < pMsg->param2) &&
                    (pSld->hdr.bottom > pMsg->param2)
                    )
            {
                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                    if (pSld->currPos < pMsg->param2)
                        return (GFX_GOL_SCROLLBAR_ACTION_INC);
                    else
                        return (GFX_GOL_SCROLLBAR_ACTION_DEC);
                }
                else
                {
                    if (pSld->currPos < pMsg->param1)
                        return (GFX_GOL_SCROLLBAR_ACTION_INC);
                    else
                        return (GFX_GOL_SCROLLBAR_ACTION_DEC);
                }
            }
        } // end of if((pMsg->uiEvent == EVENT_PRESS) || (pMsg->uiEvent == EVENT_MOVE))

        // when the event is release emit OBJ_MSG_PASSIVE this can be used to
        // detect that the release event happened on the slider.
        if (pMsg->uiEvent == EVENT_RELEASE)
            return GFX_GOL_OBJECT_ACTION_PASSIVE;

        return (GFX_GOL_OBJECT_ACTION_INVALID);
    } // end of if(pMsg->type == TYPE_TOUCHSCREEN
#endif
#ifdef USE_KEYBOARD
    if (pMsg->type == TYPE_KEYBOARD)
    {
        if ((uint16_t) pMsg->param1 == pSld->hdr.ID)
        {
            if (pMsg->uiEvent == EVENT_KEYSCAN)
            {
                if ((pMsg->param2 == SCAN_RIGHT_PRESSED) || (pMsg->param2 == SCAN_UP_PRESSED))
                {
                    return (GFX_GOL_SCROLLBAR_ACTION_INC);
                }

                if ((pMsg->param2 == SCAN_LEFT_PRESSED) || (pMsg->param2 == SCAN_DOWN_PRESSED))
                {
                    return (GFX_GOL_SCROLLBAR_ACTION_DEC);
                }
            }
        }
    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_ScrollBarDraw(void *pObj)
 *
 * Notes: This is the state machine to draw the slider or scrollbar.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_ScrollBarDraw(void *pObj)
{

    typedef enum
    {
        GFX_GOL_SLIDER_STATE_IDLE,
        GFX_GOL_SLIDER_STATE_HIDE,
        GFX_GOL_SLIDER_STATE_PANEL,
        GFX_GOL_SLIDER_STATE_THUMBPATH1,
        GFX_GOL_SLIDER_STATE_THUMBPATH2,
        GFX_GOL_SLIDER_STATE_CLEARTHUMB,
        GFX_GOL_SLIDER_STATE_REDRAWPATH1,
        GFX_GOL_SLIDER_STATE_REDRAWPATH2,
        GFX_GOL_SLIDER_STATE_THUMB,
        GFX_GOL_SLIDER_STATE_THUMBPANEL,
        GFX_GOL_SLIDER_STATE_FOCUS,
    } GFX_GOL_SCROLLBAR_DRAW_STATE_STATES;

    static GFX_COLOR colorTemp = 0;

    static GFX_GOL_SCROLLBAR_DRAW_STATE_STATES state = GFX_GOL_SLIDER_STATE_IDLE;
    static uint16_t left, top, right, bottom;
    static uint16_t midPoint, thWidth, thHeight;
    static uint16_t minPos, maxPos;
    static uint8_t index = 1;
    GFX_GOL_SCROLLBAR *pSld;

    pSld = (GFX_GOL_SCROLLBAR *) pObj;

    while (1)
    {
        switch (state)
        {
            case GFX_GOL_SLIDER_STATE_IDLE:
                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_HIDE_STATE))
                {
                    GFX_ColorSet(pSld->hdr.pGolScheme->CommonBkColor); // set to common BK Color
                    state = GFX_GOL_SLIDER_STATE_HIDE;
                    // no break here so it falls through to GFX_GOL_SLIDER_STATE_HIDE
                }
                else
                {
                    if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DISABLED_STATE))
                    {
                        colorTemp = pSld->hdr.pGolScheme->Color0; // select enabled color
                    }
                    else
                    {
                        colorTemp = pSld->hdr.pGolScheme->ColorDisabled; // select disabled color
                    }

                    SldGetMinMaxPos(pSld, &minPos, &maxPos);

                    midPoint = GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE) ? (pSld->hdr.left + pSld->hdr.right) >> 1 : (pSld->hdr.top + pSld->hdr.bottom) >> 1;

                    // calculate the thumb width and height Actually gets the half value
                    // (see calculation of width and height) SldGetWidth() and SldGetHeight()
                    thWidth = pSld->thWidth; // gets half the width
                    thHeight = pSld->thHeight; // gets half the height

                    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

                    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DRAW_STATE))
                    { // draw the panel for the slider
                        // modify the color setting if scroll bar mode or slider mode
                        GFX_GOL_PanelParameterSet
                                (
                                
                                pSld->hdr.left,
                                pSld->hdr.top,
                                pSld->hdr.right,
                                pSld->hdr.bottom,
                                0,
                                colorTemp,
                                (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE)) ? pSld->hdr.pGolScheme->EmbossDkColor : pSld->hdr.pGolScheme->EmbossLtColor,
                                (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE)) ? pSld->hdr.pGolScheme->EmbossLtColor : pSld->hdr.pGolScheme->EmbossDkColor,
                                NULL,
                                GFX_FILL_STYLE_COLOR,
                                GFX_GOL_EMBOSS_SIZE
                                );

                        // initialize current and previous position
                        GFX_GOL_ScrollBarPositionSet(pSld, pSld->pos);
                        pSld->prevPos = pSld->currPos;

                        state = GFX_GOL_SLIDER_STATE_PANEL;
                    }
                    else
                    { // we do not need to draw the whole object
                        state = GFX_GOL_SLIDER_STATE_CLEARTHUMB; // go to thumb drawing
                    }
                    break;
                }

            case GFX_GOL_SLIDER_STATE_HIDE:
                if(GFX_RectangleFillDraw(pSld->hdr.left, pSld->hdr.top, pSld->hdr.right, pSld->hdr.bottom) == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = GFX_GOL_SLIDER_STATE_IDLE;
                return (GFX_STATUS_SUCCESS);

            case GFX_GOL_SLIDER_STATE_PANEL:
                if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE) // draw the panel of the slider
                    return (GFX_STATUS_FAILURE);
                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
                { // check if slider or scroll bar
                    state = GFX_GOL_SLIDER_STATE_THUMB; // scrollbar: go directly to thumb drawing
                    break; // thumb path is not drawn in scrollbar
                }
                else
                {
                    state = GFX_GOL_SLIDER_STATE_THUMBPATH1; // slider: draw thumb path next
                }

            case GFX_GOL_SLIDER_STATE_THUMBPATH1:
                GFX_ColorSet(pSld->hdr.pGolScheme->EmbossDkColor);
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                    if (GFX_LineDraw(minPos, midPoint, maxPos, midPoint) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                }
                else
                {
                    if (GFX_LineDraw(midPoint, minPos, midPoint, maxPos) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_SLIDER_STATE_THUMBPATH2;

            case GFX_GOL_SLIDER_STATE_THUMBPATH2:
                GFX_ColorSet(pSld->hdr.pGolScheme->EmbossLtColor);
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                         index = GFX_LineDraw(minPos, midPoint + 1, maxPos, midPoint + 1);
                }
                else
                {
                         index = GFX_LineDraw(midPoint + 1, minPos, midPoint + 1, maxPos);
                }

               if(index == GFX_STATUS_FAILURE)
                {
                    return(GFX_STATUS_FAILURE);
                }

                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DRAW_STATE))
                { // if drawing the whole slider
                    state = GFX_GOL_SLIDER_STATE_THUMB; // go straight to drawing the thumb
                    break;
                }
                else
                    // if just drawing the thumb
                    state = GFX_GOL_SLIDER_STATE_CLEARTHUMB; // go to state to remove current position

            case GFX_GOL_SLIDER_STATE_CLEARTHUMB: // this removes the current thumb

                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE))
                { // GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE is only set when
                    state = GFX_GOL_SLIDER_STATE_FOCUS; // object type is SLIDER
                    break;
                }

                GFX_ColorSet(colorTemp);

                // Remove the current thumb by drawing a bar with background color
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                    index = GFX_RectangleFillDraw(pSld->prevPos - thWidth, midPoint - thHeight, pSld->prevPos + thWidth, midPoint + thHeight);
                }
                else
                {
                    index = GFX_RectangleFillDraw(midPoint - thWidth, pSld->prevPos - thHeight, midPoint + thWidth, pSld->prevPos + thHeight);
                }

                if(index == GFX_STATUS_FAILURE)
                {
                    return(GFX_STATUS_FAILURE);
                }

                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
                { // check if slider or scroll bar
                    state = GFX_GOL_SLIDER_STATE_REDRAWPATH1;
                }
                else
                {
                    state = GFX_GOL_SLIDER_STATE_THUMB; // go directly to thumb drawing
                    break; // thumb path is not drawn in scrollbar
                }

            case GFX_GOL_SLIDER_STATE_REDRAWPATH1: // redraws the lines that it covered
                GFX_ColorSet(pSld->hdr.pGolScheme->EmbossDkColor);

                // Check if the redraw area exceeds the actual dimension. This will
                // adjust the redrawing area to just within the parameters
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                    if (minPos + thWidth > pSld->prevPos)
                        left = minPos;
                    else
                        left = pSld->prevPos - thWidth;

                    if (maxPos - thWidth < pSld->prevPos)
                        right = maxPos;
                    else
                        right = pSld->prevPos + thWidth;

                    if (GFX_LineDraw(left, midPoint, right, midPoint) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                }
                else
                {
                    if (minPos + thHeight > pSld->prevPos)
                        top = minPos;
                    else
                        top = pSld->prevPos - thHeight;

                    if (maxPos - thHeight < pSld->prevPos)
                        bottom = maxPos;
                    else
                        bottom = pSld->prevPos + thHeight;

                    if (GFX_LineDraw(midPoint, top, midPoint, bottom) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_SLIDER_STATE_REDRAWPATH2;

            case GFX_GOL_SLIDER_STATE_REDRAWPATH2:
                GFX_ColorSet(pSld->hdr.pGolScheme->EmbossLtColor);
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                {
                    index = GFX_LineDraw(left, midPoint + 1, right, midPoint + 1);
                }
                else
                {
                    index = GFX_LineDraw(midPoint + 1, top, midPoint + 1, bottom);
                }

                if(index == GFX_STATUS_FAILURE)
                {
                    return(GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_SLIDER_STATE_THUMB;

            case GFX_GOL_SLIDER_STATE_THUMB:
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_VERTICAL_STATE))
                { // Draw the slider thumb based on the
                    // current position
                    left = pSld->currPos - thWidth;
                    top = midPoint - thHeight;
                    right = pSld->currPos + thWidth;
                    bottom = midPoint + thHeight;
                }
                else
                {
                    left = midPoint - thWidth;
                    top = pSld->currPos - thHeight;
                    right = midPoint + thWidth;
                    bottom = pSld->currPos + thHeight;
                }

                GFX_GOL_PanelParameterSet
                        (
                        
                        left,
                        top,
                        right,
                        bottom,
                        0, // set the parameters of the thumb
                        colorTemp,
                        pSld->hdr.pGolScheme->EmbossLtColor,
                        pSld->hdr.pGolScheme->EmbossDkColor,
                        NULL,
                        GFX_FILL_STYLE_COLOR,
                        (GFX_GOL_EMBOSS_SIZE - 1) ? GFX_GOL_EMBOSS_SIZE - 1 : 1
                        );

                state = GFX_GOL_SLIDER_STATE_THUMBPANEL;

            case GFX_GOL_SLIDER_STATE_THUMBPANEL:
                if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE) // draw the panel of the thumb
                    return (GFX_STATUS_FAILURE);

                pSld->prevPos = pSld->currPos; // record the current position as previous
                if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE) || !GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_FOCUSED_STATE))
                { // check if scroll bar focus is not used
                    state = GFX_GOL_SLIDER_STATE_IDLE; // go back to idle state
                    return (GFX_STATUS_SUCCESS);
                }

                state = GFX_GOL_SLIDER_STATE_FOCUS;

            case GFX_GOL_SLIDER_STATE_FOCUS:
                if (!GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE))
                { // do not draw focus when in scroll bar mode
                    GFX_LineStyleSet(GFX_GOL_FOCUS_LINE);
                    if (GFX_GOL_ObjectStateGet(pSld, GFX_GOL_SCROLLBAR_DRAW_FOCUS_STATE))
                    {
                        GFX_ColorSet(pSld->hdr.pGolScheme->TextColor0); // draw the focus box
                    }
                    else
                    {
                        GFX_ColorSet(colorTemp); // remove the focus box, colorTemp
                    }

                    if(GFX_RectangleDraw(

                            pSld->hdr.left + GFX_GOL_EMBOSS_SIZE,
                            pSld->hdr.top + GFX_GOL_EMBOSS_SIZE,
                            pSld->hdr.right - GFX_GOL_EMBOSS_SIZE,
                            pSld->hdr.bottom - GFX_GOL_EMBOSS_SIZE) == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }

                    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID); // reset line type
                }

                state = GFX_GOL_SLIDER_STATE_IDLE; // set state to idle
                return (GFX_STATUS_SUCCESS); // return as done
        }
    } // end of while(1)
}
