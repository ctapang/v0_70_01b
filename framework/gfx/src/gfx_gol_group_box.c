/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
  gfx_gol_group_box.c

  Summary:
    This implements the group box object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    EditBox Object.
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

#include "gfx/gfx_gol_group_box.h"

/*********************************************************************
 * Function: GFX_GOL_GROUPBOX *GFX_GOL_GroupboxCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *							   uint16_t bottom, uint16_t state, GFX_XCHAR *pText,
 *							   GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Notes: Creates a GROUPBOX object and adds it to the current active list.
 *        If the creation is successful, the pointer to the created Object
 *        is returned. If not successful, NULL is returned.
 *
 ********************************************************************/
GFX_GOL_GROUPBOX *GFX_GOL_GroupboxCreate
(
        uint16_t ID,
        uint16_t left,
        uint16_t top,
        uint16_t right,
        uint16_t bottom,
        uint16_t state,
        GFX_XCHAR *pText,
        GFX_ALIGNMENT       alignment,
        GFX_GOL_OBJ_SCHEME *pScheme
        )
{
    GFX_GOL_GROUPBOX *pGb = NULL;

    pGb = (GFX_GOL_GROUPBOX *) GFX_malloc(sizeof (GFX_GOL_GROUPBOX));
    if (pGb == NULL)
        return (pGb);

    //pGb->hdr.instance = instance; //Device Instance set
    pGb->hdr.ID = ID; // unique id assigned for referencing
    pGb->hdr.pNxtObj = NULL;
    pGb->hdr.type = GFX_GOL_GROUPBOX_TYPE; // set object type
    pGb->hdr.left = left; // left position
    pGb->hdr.top = top; // top position
    pGb->hdr.right = right; // right position
    pGb->hdr.bottom = bottom; // bottom position
    pGb->hdr.state = state; // initial state
    pGb->hdr.DrawObj = GFX_GOL_GroupboxDraw; // draw function
    pGb->hdr.actionGet = GFX_GOL_GroupboxActionGet; // message function
    pGb->hdr.actionSet = NULL; // default message function
    pGb->hdr.FreeObj = NULL; // free function
    pGb->alignment = alignment;

    // Set the color scheme and font to be used
    pGb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    if (pText != NULL)
    {
        // Set the text width & height
        GFX_GOL_GroupboxTextSet(pGb, pText);
    }
    else
    {
        pGb->pText = NULL;
        pGb->textWidth = 0;
        pGb->textHeight = 0;
    }
    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pGb);
    return (pGb);
}

/*********************************************************************
 * Function: GFX_GOL_GroupboxTextSet(GFX_GOL_GROUPBOX *pGb, char *pText)
 *
 * Overview: Sets the text.
 *
 ********************************************************************/
void GFX_GOL_GroupboxTextSet(GFX_GOL_GROUPBOX *pGb, GFX_XCHAR *pText)
{
    pGb->pText = pText;
    // Set the text width & height
    pGb->textWidth = GFX_TextStringWidthGet(pText, pGb->hdr.pGolScheme->pFont);
    pGb->textHeight = GFX_TextStringHeightGet(pGb->hdr.pGolScheme->pFont);

}

/*********************************************************************
 * Function: uint16_t GFX_GOL_GroupboxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_GroupboxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{

    GFX_GOL_GROUPBOX *pGb;

    pGb = (GFX_GOL_GROUPBOX *) pObj;

    // Evaluate if the message is for the button
    // Check if disabled first
    if (!GFX_GOL_ObjectStateGet(pGb, GFX_GOL_GROUPBOX_DISABLED_STATE))
    {
#ifdef USE_TOUCHSCREEN
        if (pMsg->type == TYPE_TOUCHSCREEN)
        {

            // Check if it falls to the left or right of the center of the thumb's face
            if
                (
                    (pGb->hdr.left < pMsg->param1) &&
                    (pGb->hdr.right > pMsg->param1) &&
                    (pGb->hdr.top < pMsg->param2) &&
                    (pGb->hdr.bottom > pMsg->param2)
                    )
            {
                if ((pMsg->uiEvent == EVENT_PRESS) || (pMsg->uiEvent == EVENT_RELEASE))
                    return (GFX_GOL_GROUPBOX_ACTION_SELECTED);
            }
        }

#endif
    }

    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_GroupboxTextDraw(void *pObj)
 *
 * Notes: This is the state machine to draw the button.
 *
 ********************************************************************/
#if (GFX_CONFIG_COLOR_DEPTH == 1)
#define THREE_D_EFFECT  0
#else
#define THREE_D_EFFECT  1
#endif

/* */
GFX_STATUS GFX_GOL_GroupboxDraw(void *pObj)
{

    typedef enum
    {
        GFX_GOL_GROUPBOX_STATE_IDLE,
        GFX_GOL_GROUPBOX_STATE_HIDETEXT,
        GFX_GOL_GROUPBOX_STATE_SETDIMENSION,
        GFX_GOL_GROUPBOX_STATE_DRAWTEXT,
        GFX_GOL_GROUPBOX_STATE_DRAWTOPRIGHT,
        GFX_GOL_GROUPBOX_STATE_DRAWTOPLEFT,
        GFX_GOL_GROUPBOX_STATE_DRAWSIDELEFT,
        GFX_GOL_GROUPBOX_STATE_DRAWSIDERIGHT,
        GFX_GOL_GROUPBOX_STATE_DRAWBOTTOM,
        WAIT,
#if (GFX_CONFIG_COLOR_DEPTH != 1)
        GFX_GOL_GROUPBOX_STATE_2DRAWTOPRIGHT,
        GFX_GOL_GROUPBOX_STATE_2DRAWTOPLEFT,
        GFX_GOL_GROUPBOX_STATE_2DRAWSIDELEFT,
        GFX_GOL_GROUPBOX_STATE_2DRAWSIDERIGHT,
        GFX_GOL_GROUPBOX_STATE_2DRAWBOTTOM,
#endif
    } GFX_GOL_GROUPBOX_DRAW_STATES;

    static GFX_GOL_GROUPBOX_DRAW_STATES state = GFX_GOL_GROUPBOX_STATE_IDLE;
    static short textLeft, textRight, top; // used to draw lines that start/stops at text.
    static GFX_STATUS index = NULL;
    static GFX_ALIGNMENT align;
    GFX_GOL_GROUPBOX *pGb;

    pGb = (GFX_GOL_GROUPBOX *) pObj;

    while (1)
    {
        switch (state)
        {
            case GFX_GOL_GROUPBOX_STATE_IDLE:

                if (GFX_GOL_ObjectStateGet(pGb, GFX_GOL_GROUPBOX_HIDE_STATE))
                { // Hide the Group Box (remove from screen)
                    GFX_ColorSet(pGb->hdr.pGolScheme->CommonBkColor);
                    index = GFX_RectangleDraw(pGb->hdr.left, pGb->hdr.top, pGb->hdr.right, pGb->hdr.bottom);
                    if(index==GFX_STATUS_FAILURE)
                    {
                        return(GFX_STATUS_FAILURE);
                    }
                    state = WAIT;
                    return(GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_GROUPBOX_STATE_HIDETEXT;

            case GFX_GOL_GROUPBOX_STATE_HIDETEXT: // hide the text first
                if (pGb->pText != NULL)
                { // needed when dynamically changing
                    GFX_ColorSet(pGb->hdr.pGolScheme->CommonBkColor); // the alignement of text
                    if (GFX_RectangleDraw(pGb->hdr.left, pGb->hdr.top, pGb->hdr.right, pGb->hdr.top + pGb->textHeight) == GFX_STATUS_FAILURE)
                        return GFX_STATUS_FAILURE;
                }

                state = GFX_GOL_GROUPBOX_STATE_SETDIMENSION;
                break;

            case GFX_GOL_GROUPBOX_STATE_SETDIMENSION:

                if (GFX_GOL_ObjectStateGet(pGb, GFX_GOL_GROUPBOX_DISABLED_STATE))
                { // set color to inactive color
                    GFX_ColorSet(pGb->hdr.pGolScheme->TextColorDisabled);
                }
                else
                {
                    GFX_ColorSet(pGb->hdr.pGolScheme->TextColor0); // active color
                }

                if (pGb->pText == NULL)
                { // there is no text, use full dimensions
                    top = pGb->hdr.top;
                    textLeft = pGb->hdr.left + 1;
                    textRight = textLeft;
                    state = GFX_GOL_GROUPBOX_STATE_DRAWTOPRIGHT; // go to drawing of right top line
                    break;
                }
                else
                { // text is present, set up dimensions with text
                    GFX_FontSet(pGb->hdr.pGolScheme->pFont);
                    top = pGb->hdr.top + (pGb->textHeight >> 1); // adjust lines on top

                    if (pGb->alignment & GFX_ALIGN_RIGHT)
                    {
                        // do right aligned
                        align = GFX_ALIGN_RIGHT;
                        textLeft = pGb->hdr.right - pGb->textWidth - 2;
                        textRight = pGb->hdr.right - 2;
                    }
                    else if (pGb->alignment & GFX_ALIGN_CENTER)
                    {

                        // do center aligned
                        align = GFX_ALIGN_HCENTER;
                        textLeft = (pGb->hdr.left + pGb->hdr.right - pGb->textWidth) >> 1;
                        textRight = textLeft + pGb->textWidth;
                    }
                    else
                    {
                        // do left aligned
                        align = GFX_ALIGN_LEFT;
                        textLeft = pGb->hdr.left + 2;
                        textRight = pGb->hdr.left + 2 + pGb->textWidth;
                    }

                    GFX_LinePositionSet(textLeft, pGb->hdr.top); // move cursor to start of text
                    state = GFX_GOL_GROUPBOX_STATE_DRAWTEXT;
                }

            case GFX_GOL_GROUPBOX_STATE_DRAWTEXT:
                if (GFX_TextStringBoxDraw(pGb->hdr.left, pGb->hdr.top, pGb->hdr.right - pGb->hdr.left, 
                                          0, pGb->pText, 0, align) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
#if (GFX_CONFIG_COLOR_DEPTH == 1)
                GFX_ColorSet(WHITE);
#else
                GFX_ColorSet(pGb->hdr.pGolScheme->EmbossDkColor);
#endif
                state = GFX_GOL_GROUPBOX_STATE_DRAWTOPRIGHT;
                break;

            case GFX_GOL_GROUPBOX_STATE_DRAWTOPRIGHT:
                if (GFX_LineDraw(textRight, top + THREE_D_EFFECT, pGb->hdr.right, top + THREE_D_EFFECT) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // top line at right
                state = GFX_GOL_GROUPBOX_STATE_DRAWTOPLEFT;
                break;

            case GFX_GOL_GROUPBOX_STATE_DRAWTOPLEFT:
                if (GFX_LineDraw(pGb->hdr.left + THREE_D_EFFECT, top + THREE_D_EFFECT, textLeft, top + THREE_D_EFFECT) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // top line at left
                state = GFX_GOL_GROUPBOX_STATE_DRAWSIDELEFT;
                break;

            case GFX_GOL_GROUPBOX_STATE_DRAWSIDELEFT:
                if (GFX_LineDraw(pGb->hdr.left + THREE_D_EFFECT, top + THREE_D_EFFECT, pGb->hdr.left + THREE_D_EFFECT, pGb->hdr.bottom) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // side line at left
                state = GFX_GOL_GROUPBOX_STATE_DRAWSIDERIGHT;
                break;

            case GFX_GOL_GROUPBOX_STATE_DRAWSIDERIGHT:
                if (GFX_LineDraw(pGb->hdr.right, top + THREE_D_EFFECT, pGb->hdr.right, pGb->hdr.bottom) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // side line at right
                state = GFX_GOL_GROUPBOX_STATE_DRAWBOTTOM;
                break;

            case GFX_GOL_GROUPBOX_STATE_DRAWBOTTOM:
                index = GFX_LineDraw(pGb->hdr.left + THREE_D_EFFECT, pGb->hdr.bottom, pGb->hdr.right, pGb->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                    return GFX_STATUS_FAILURE; // bottom line
                }
#if (GFX_CONFIG_COLOR_DEPTH == 1)
                state = WAIT;
                return(0);
#else
                state = GFX_GOL_GROUPBOX_STATE_2DRAWTOPLEFT;
#endif
#if (GFX_CONFIG_COLOR_DEPTH != 1)

            case GFX_GOL_GROUPBOX_STATE_2DRAWTOPLEFT:
                GFX_ColorSet(pGb->hdr.pGolScheme->EmbossLtColor); // 2nd line top line at left
                if (GFX_LineDraw(pGb->hdr.left, top, textLeft, top) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE;
                state = GFX_GOL_GROUPBOX_STATE_2DRAWTOPRIGHT;
                break;

            case GFX_GOL_GROUPBOX_STATE_2DRAWTOPRIGHT:
                if (GFX_LineDraw(textRight, top, pGb->hdr.right, top) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // 2nd line top line at right
                state = GFX_GOL_GROUPBOX_STATE_2DRAWSIDELEFT;
                break;

            case GFX_GOL_GROUPBOX_STATE_2DRAWSIDELEFT:
                if (GFX_LineDraw(pGb->hdr.left, top, pGb->hdr.left, pGb->hdr.bottom - 1) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // 2nd line left
                state = GFX_GOL_GROUPBOX_STATE_2DRAWSIDERIGHT;
                break;

            case GFX_GOL_GROUPBOX_STATE_2DRAWSIDERIGHT:
                if (GFX_LineDraw(pGb->hdr.right - 1, top + 2, pGb->hdr.right - 1, pGb->hdr.bottom - 1) == GFX_STATUS_FAILURE)
                    return GFX_STATUS_FAILURE; // 2nd line right
                state = GFX_GOL_GROUPBOX_STATE_2DRAWBOTTOM;
                break;

            case GFX_GOL_GROUPBOX_STATE_2DRAWBOTTOM:
                index = GFX_LineDraw(pGb->hdr.left + 2, pGb->hdr.bottom - 1, pGb->hdr.right - 1, pGb->hdr.bottom - 1);
                if(index == GFX_STATUS_FAILURE)
                {
                    return GFX_STATUS_FAILURE; // 2nd line bottom
                }
                state = WAIT;
            case WAIT:
//                if(index->type != DONE) // Wait until renderring is complete
//                {
//                    return(0);
//                }
                state = GFX_GOL_GROUPBOX_STATE_IDLE;
                return(GFX_STATUS_SUCCESS);
#endif // end of #if (GFX_CONFIG_COLOR_DEPTH != 1)

        } // end of switch()
    } // end of while(1)
}