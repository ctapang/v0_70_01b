/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_round_dial.c

  Summary:
    This implements the round dial object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    RoundDial Object.
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
#include "gfx/gfx_gol_round_dial.h"

#define ROUNDDIAL_VALUE_GAP    2   // minimum pixel gap between values
#define ROUNDDIAL_RESOLUTION   8   // sub value interval

uint8_t tickStr[2] = {3,6};

/*********************************************************************
* Function: GFX_GOL_ROUNDDIAL  *GFX_GOL_RoundDialCreate(uint16_t ID, uint16_t x, uint16_t y, uint16_t radius,
*						uint16_t state, uint16_t res, uint16_t value, uint16_t max,
*						GFX_GOL_SCHEME *pScheme)
*
*
* Notes: Creates a ROUNDDIAL object and adds it to the current active list.
*        If the creation is successful, the pointer to the created Object 
*        is returned. If not successful, NULL is returned.
*
********************************************************************/
GFX_GOL_ROUNDDIAL *GFX_GOL_RoundDialCreate
(
    uint16_t ID, int16_t left, int16_t top, int16_t right, int16_t bottom, uint8_t rad, uint16_t state,
    const ROUNDDIALITEM* pItems, uint16_t nItems, uint16_t startPos, GFX_ALIGNMENT alignment,
    GFX_GOL_OBJ_SCHEME  *pScheme
)
{

    int16_t txtHeight, txtWidth;

    GFX_GOL_ROUNDDIAL *pDia = NULL;

    // sanity check
    if ((pItems == NULL) || (nItems == 0))
        return NULL;

    // allocate memory for the control
    pDia = (GFX_GOL_ROUNDDIAL*) GFX_malloc(sizeof (GFX_GOL_ROUNDDIAL));
    if (pDia == NULL)
        return (pDia);

    pDia->hdr.imageStored = false;
    
    if (startPos >= nItems)
        startPos = nItems - 1;

    pDia->hdr.ID = ID;
    pDia->hdr.pNxtObj = NULL;
    pDia->hdr.type = GFX_GOL_ROUNDDIAL_TYPE;
    pDia->hdr.state = state; // set state

    pDia->hdr.left = left;
    pDia->hdr.top = top;
    pDia->hdr.right = right;
    pDia->hdr.bottom = bottom;

    pDia->hdr.DrawObj = GFX_GOL_RoundDialDraw;		        // draw function
    pDia->hdr.actionGet = GFX_GOL_RoundDailActionGet;		// message function
    pDia->hdr.actionSet = GFX_GOL_RoundDailActionSet;	       // default message function
    pDia->alignment = alignment;

    pDia->radius = rad;

    // record the data items
    pDia->pItems = pItems;
    pDia->nItems = nItems;

    // current position bit shifted to allow rotational steps
    pDia->pos = startPos;
    pDia->posOffset = startPos;

    // Set the style scheme to be used
     pDia->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    // calculate the range of values either side of the current one that will be visible
    if (pDia->alignment == GFX_ALIGN_VCENTER) {
        txtHeight = GFX_TextStringHeightGet(pDia->hdr.pGolScheme->pFont) + ROUNDDIAL_VALUE_GAP;
        pDia->bandHeight = txtHeight;
        pDia->numericRange = (bottom - top) / txtHeight;

        pDia->center = (top + bottom) >> 1;
    } else {
        // this is a guess on width since it will vary according to the values (we 'guess' at 2 digit values)
        txtWidth = GFX_TextStringWidthGet("00", pDia->hdr.pGolScheme->pFont) + ROUNDDIAL_VALUE_GAP;
        pDia->bandHeight = txtWidth;
        pDia->numericRange = (right - left) / (txtWidth);

        pDia->center = (left + right) >> 1;
    }

    // since we are displaying either side of a value div by 2
    pDia->numericRange >>= 1;

    // bounds check it against  the min and max values to prevent wraparound
    if (pDia->numericRange > pDia->nItems) {
        pDia->numericRange = pDia->nItems >> 1;
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pDia);
    return (pDia);
}

/*********************************************************************
* Function: GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
*
*
* Notes: This the default operation to change the state of the dial.
*		 Called inside GFX_GOL_Message() when GFX_GOL_MessageCallback() returns a 1.
*
********************************************************************/
void GFX_GOL_RoundDailActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_ROUNDDIAL *pDia;
    int16_t newPos;

    pDia = (GFX_GOL_ROUNDDIAL *)pObj;

#ifdef USE_FOCUS
    if (pMsg->type == TYPE_TOUCHSCREEN) {
        if (!GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_FOCUSED)) {
            GFX_GOL_ObjectFocusSet((GFX_GOL_OBJ_HEADER*) pDia);
        }
    }
#endif

    // if message was passive do nothing
    if (translatedMsg == GFX_GOL_OBJECT_ACTION_PASSIVE)
        return;

    if (pMsg->type == TYPE_TOUCHSCREEN) {
        if (translatedMsg == GFX_GOL_ROUNDDIAL_ACTION_DEC) {
            // find the new final target position
            newPos = (int16_t) pDia->pos - 1;
            pDia->velocity = +1;
            pDia->posOffset = -pDia->bandHeight;

            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_WRAPAROUND)) {
                newPos = GFX_GOL_RoundDialWrap(newPos, 0, pDia->nItems);
            } else {
                if (newPos < 0)
                    newPos = 0;
            }
        } else if (translatedMsg == GFX_GOL_ROUNDDIAL_ACTION_INC) {
            newPos = (int16_t) pDia->pos + 1;
            pDia->velocity = -1;
            pDia->posOffset = pDia->bandHeight;

            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_WRAPAROUND)) {
                newPos = GFX_GOL_RoundDialWrap(newPos, 0, pDia->nItems);
            } else {
                if (newPos >= pDia->nItems)
                    newPos = pDia->nItems - 1;
            }
        } else {
            return;
        }

        if (newPos != pDia->pos) {
            pDia->pos = (uint16_t) newPos;

            // if animating then mark as such, if not zero the offset and velocity
            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_ANIMATE)) {
                GFX_GOL_ObjectStateSet(pDia, GFX_GOL_ROUNDDIAL_ROTATING);
            } else {
                pDia->posOffset = 0;
                pDia->velocity = 0;
            }

            GFX_GOL_ObjectStateSet(pDia, GFX_GOL_ROUNDDIAL_DRAW_BAR); // redraw the numeric scale area
        }
    }


}

/*********************************************************************
* Function: uint16_t RdiaTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
*
* Notes: Evaluates the message if the object will be affected by the 
*		 message or not.
*
********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{

      GFX_GOL_ROUNDDIAL *pDia;

    pDia = (GFX_GOL_ROUNDDIAL *) pObj;

    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DISABLED))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN) {
        // Check if it falls in the control area
        if ((pMsg->uiEvent == EVENT_PRESS)) {
            if ((pDia->hdr.left + GFX_GOL_EMBOSS_SIZE < pMsg->param1) &&
                    (pDia->hdr.right - GFX_GOL_EMBOSS_SIZE > pMsg->param1) &&
                    (pDia->hdr.top + GFX_GOL_EMBOSS_SIZE < pMsg->param2) &&
                    (pDia->hdr.bottom - GFX_GOL_EMBOSS_SIZE > pMsg->param2)) {

                // depending on the vertical or horizontal alignment see if this is an increment or decrement
                if (pDia->alignment == GFX_ALIGN_VCENTER) {
                    if (pDia->center < pMsg->param2)
                        return (GFX_GOL_ROUNDDIAL_ACTION_DEC );
                    else
                        return (GFX_GOL_ROUNDDIAL_ACTION_INC);
                } else {
                    if (pDia->center < pMsg->param1)
                        return (GFX_GOL_ROUNDDIAL_ACTION_DEC);
                    else
                        return (GFX_GOL_ROUNDDIAL_ACTION_INC);
                }
            }
        }

        if (pMsg->uiEvent == EVENT_RELEASE) {
            return GFX_GOL_OBJECT_ACTION_PASSIVE;
        }
    }

#endif

    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_RoundDialWrap(int16_t kX, const int16_t kLowerBound, const int16_t kUpperBound)
 *
 * Overview: generate a wrapped integer result
 *
 ********************************************************************/
uint16_t GFX_GOL_RoundDialWrap(int16_t kX, const int16_t kLowerBound, const int16_t kUpperBound)
{
    if (kX < kLowerBound)
        return (kUpperBound) - (kLowerBound - kX);

    if (kX >= kUpperBound)
        return (kX - kUpperBound) + (kLowerBound);

    return kX;
}

/*********************************************************************
 * Function: void DrawBand(void *pObj)
 *
 * Overview: Draw just the band of the control
 *
 ********************************************************************/
GFX_STATUS DrawBand(GFX_GOL_ROUNDDIAL* pDia, int16_t left, int16_t top, int16_t right, int16_t bottom)
{
    static int16_t calcValue;
    static int16_t nextState;
    static uint8_t state = 0;

    switch(state)
    {
       case 0:     // draw the band
       GFX_GradientColorSet(pDia->hdr.pGolScheme->Color0,pDia->hdr.pGolScheme->Color1);
       calcValue = pDia->center - (pDia->bandHeight >> 1);

       if (pDia->alignment == GFX_ALIGN_VCENTER)
       {
           GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
           nextState = 1;
       }
       else
       {
           GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_VER);
           nextState = 4;
       }
       if(GFX_BevelGradientDraw(left, top, right, bottom , pDia->radius) == GFX_STATUS_FAILURE)
           return(GFX_STATUS_FAILURE);
       state = nextState;
        case 1:   // draw the raised central vertical portion
            GFX_ColorSet(pDia->hdr.pGolScheme->Color1);
            if(GFX_RectangleFillDraw(left, calcValue, right, calcValue + pDia->bandHeight) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            state++;
        case 2:
            GFX_ColorSet(pDia->hdr.pGolScheme->EmbossLtColor);
            if(GFX_RectangleFillDraw(left, calcValue - GFX_GOL_EMBOSS_SIZE, right, calcValue) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            state++;
        case 3:
            GFX_ColorSet(pDia->hdr.pGolScheme->EmbossLtColor);
            if(GFX_RectangleFillDraw(left, calcValue + pDia->bandHeight, right, calcValue + pDia->bandHeight + GFX_GOL_EMBOSS_SIZE) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            break;
        case 4: // draw the raised central horizontal portion
            GFX_ColorSet(pDia->hdr.pGolScheme->Color1);
            if(GFX_RectangleFillDraw(calcValue, top, calcValue + pDia->bandHeight, bottom) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            state++;
        case 5:
            GFX_ColorSet(pDia->hdr.pGolScheme->EmbossLtColor);
            if(GFX_RectangleFillDraw(calcValue - GFX_GOL_EMBOSS_SIZE, top, calcValue, bottom) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            state++;
        case 6:
            GFX_ColorSet(pDia->hdr.pGolScheme->EmbossLtColor);
            if(GFX_RectangleFillDraw(calcValue + pDia->bandHeight, top, calcValue + pDia->bandHeight + GFX_GOL_EMBOSS_SIZE, bottom) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            break;
    }
    state = 0;
    return(GFX_STATUS_SUCCESS);
}

/*********************************************************************
* Function: uint16_t RoundDialDraw(void *pObj)
*
*
* Notes: This is the state machine to draw the dial.
*
********************************************************************/
GFX_STATUS GFX_GOL_RoundDialDraw(void *pObject)
{
    typedef enum {
        IDLE,
        DRAW_PANEL_TOP,
        DRAW_PANEL_BOTTOM,
        DIAL_BAND_INIT,
        DRAW_DIAL_BAND,
        CLEAN_TEXT_1,
        DRAW_TEXT_1,
        DRAW_TEXT_2,
        DRAW_TEXT_3,
        CLEAN_TEXT_2,
        FOCUS,
        INDEX,
        ROLLING
    } ROUNDDIAL_DRAW_STATES;

    static int16_t left, top, right, bottom;
    static ROUNDDIAL_DRAW_STATES state = IDLE;
    static int16_t textX, textY, textWidth;
    static int16_t itemValue, absValue;
    GFX_GOL_ROUNDDIAL *pDia;
    static ROUNDDIALITEM* pLwItem;
    static uint8_t tickStart,tickLength = 0;

    pDia = (GFX_GOL_ROUNDDIAL*) pObject;

    switch (state) {
        case IDLE:
            
            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_HIDE)) {
                GFX_ColorSet(pDia->hdr.pGolScheme->CommonBkColor);
                return(GFX_RectangleFillDraw(pDia->hdr.left, pDia->hdr.top, pDia->hdr.right, pDia->hdr.bottom));
            }

            // check if the whole control needs redrawing
            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DRAW)) {
                state = DRAW_PANEL_TOP;
            } else if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DRAW_BAR)) {
                state = DIAL_BAND_INIT;
                return (GFX_STATUS_FAILURE);
            }

        case DRAW_PANEL_TOP:
            GFX_GradientColorSet(pDia->hdr.pGolScheme->EmbossDkColor, pDia->hdr.pGolScheme->EmbossLtColor);

            if (pDia->alignment == GFX_ALIGN_VCENTER) {
                GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR);
                // draw the left hand bevel
                if(GFX_BarGradientDraw(pDia->hdr.left, pDia->hdr.top, pDia->hdr.left + GFX_GOL_EMBOSS_SIZE, pDia->hdr.bottom)== GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                // draw the right hand bevel
                left = pDia->hdr.right - GFX_GOL_EMBOSS_SIZE;
                top = pDia->hdr.top;
                right = pDia->hdr.right;
                bottom = pDia->hdr.bottom;
             } else {
                 GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOUBLE_VER);
                // draw the top bevel
                if(GFX_BarGradientDraw(pDia->hdr.left, pDia->hdr.top, pDia->hdr.right, pDia->hdr.top + GFX_GOL_EMBOSS_SIZE) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                // draw the bottom bevel
                left = pDia->hdr.left;
                top = pDia->hdr.bottom - GFX_GOL_EMBOSS_SIZE;
                right = pDia->hdr.right;
                bottom = pDia->hdr.bottom;
                   }
            state = DRAW_PANEL_BOTTOM;
        case DRAW_PANEL_BOTTOM:
            if(GFX_BarGradientDraw(left,top,right,bottom) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);
            state = DIAL_BAND_INIT;

        case DIAL_BAND_INIT:
            left = pDia->hdr.left;
            top = pDia->hdr.top;
            right = pDia->hdr.right;
            bottom = pDia->hdr.bottom;

            if (pDia->alignment == GFX_ALIGN_VCENTER) {
                left += GFX_GOL_EMBOSS_SIZE;
                right -= GFX_GOL_EMBOSS_SIZE;
            } else {
                top += GFX_GOL_EMBOSS_SIZE;
                bottom -= GFX_GOL_EMBOSS_SIZE;
            }
            state = DRAW_DIAL_BAND;

        case DRAW_DIAL_BAND:
            if(DrawBand(pDia, left, top, right, bottom) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);

            // draw the text
            GFX_FontSet(pDia->hdr.pGolScheme->pFont);
            GFX_ColorSet(pDia->hdr.pGolScheme->TextColorDisabled);

            // calculate the position offset for the y values
            textY = pDia->center - (pDia->bandHeight >> 1);
            textY -= pDia->numericRange * pDia->bandHeight;
            if (GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_ROTATING)) {
            //    textY += pDia->posOffset;
                pDia->posOffset += pDia->velocity;
                if (pDia->posOffset == 0)
                    GFX_GOL_ObjectStateClear(pDia, GFX_GOL_ROUNDDIAL_ROTATING);
            }
            
            tickStart  ^= 1;
            tickLength = tickStart;

            // calculate the range of absolute values (not including wraparound) and print them
            for (absValue = (pDia->pos - pDia->numericRange); absValue != (pDia->pos + 1 + pDia->numericRange); absValue++)
            {
                itemValue = GFX_GOL_RoundDialWrap(absValue, 0, pDia->nItems);
                pLwItem = (ROUNDDIALITEM*) &pDia->pItems[itemValue];
                textWidth = GFX_TextStringWidthGet(pLwItem->text, pDia->hdr.pGolScheme->pFont);
                textX = ((left + right) >> 1) - (textWidth >> 1);
                // set the color according to the button state and scheme
                if (absValue == pDia->pos) {
                      GFX_ColorSet(pDia->hdr.pGolScheme->TextColor1);
                }
                else {
                      GFX_ColorSet(pDia->hdr.pGolScheme->TextColor0);
                }
                    tickLength ^= 1;
                    state = DRAW_TEXT_1;
        case DRAW_TEXT_1:
                if(GFX_LineDraw(left, textY + (pDia->bandHeight>>1), left+tickStr[tickLength], textY + (pDia->bandHeight>>1))== GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                 state = DRAW_TEXT_2;
        case DRAW_TEXT_2:
                if(GFX_TextStringDraw(textX, textY, pLwItem->text) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                 state = DRAW_TEXT_3;
        case DRAW_TEXT_3:
                if(GFX_LineDraw(right-tickStr[tickLength], textY + (pDia->bandHeight>>1), right-1, textY + (pDia->bandHeight>>1)) == GFX_STATUS_FAILURE)
                     return(GFX_STATUS_FAILURE);
                state = CLEAN_TEXT_1;
                GFX_ColorSet(pDia->hdr.pGolScheme->CommonBkColor);
        case CLEAN_TEXT_1:
                if(GFX_RectangleFillDraw(pDia->hdr.left, pDia->hdr.top-pDia->bandHeight, pDia->hdr.right, pDia->hdr.top-pDia->radius) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                 state = CLEAN_TEXT_2;
        case CLEAN_TEXT_2:
                if(GFX_RectangleFillDraw(pDia->hdr.left, pDia->hdr.bottom+pDia->radius, pDia->hdr.right, pDia->hdr.bottom+pDia->bandHeight) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
                // move Y position to next location
                textY += pDia->bandHeight;
            }

            state = IDLE;

        case FOCUS:
        case INDEX:
        case ROLLING:
            break;
    }

    return (GFX_STATUS_SUCCESS);
}
