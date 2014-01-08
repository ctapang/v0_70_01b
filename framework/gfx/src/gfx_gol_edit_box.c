/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
  gfx_gol_edit_box.c

  Summary:
    This implements the edit box object of the GOL.

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
#include "gfx/gfx_gol_edit_box.h"

#define GFX_GOL_EDITBOX_INDENT       0x02    // Indent for the text from the frame.
#define GFX_GOL_EDITBOX_CARET_WIDTH  0x02    // Caret line width.

/*********************************************************************
 * Function: GFX_GOL_EDITBOX  *GFX_Editbox_Create(uint16_t ID, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom,
 *							   uint16_t state , GFX_XCHAR *pText, uint16_t charMax, GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Notes: Create the GFX_GOL_EDITBOX Object.
 *
 ********************************************************************/
GFX_GOL_EDITBOX *GFX_GOL_EditBoxCreate
(
 uint16_t ID,
 uint16_t left,
 uint16_t top,
 uint16_t right,
 uint16_t bottom,
 uint16_t state,
 GFX_XCHAR *pText,
 uint16_t charMax,
 GFX_ALIGNMENT       alignment,
 GFX_GOL_OBJ_SCHEME *pScheme
 )
{
    GFX_GOL_EDITBOX *pEb = NULL;

    pEb = (GFX_GOL_EDITBOX*) GFX_malloc(sizeof (GFX_GOL_EDITBOX)+ (charMax + 1) * sizeof (GFX_XCHAR)); // ending zero is not included into charMax
    if (pEb == NULL)
        return pEb;

    pEb->pText = (GFX_XCHAR*) ((uint8_t*) pEb + sizeof (GFX_GOL_EDITBOX));
    *pEb->pText = 0;
    pEb->length = 0;
    pEb->charMax = charMax;

    if (pText != NULL)
        GFX_GOL_EditBoxTextSet(pEb, pText);

    //pEb->hdr.instance = instance;
    pEb->hdr.ID = ID;
    pEb->hdr.pNxtObj = NULL;
    pEb->hdr.type = GFX_GOL_EDITBOX_TYPE;
    pEb->hdr.left = left;
    pEb->hdr.top = top;
    pEb->hdr.right = right;
    pEb->hdr.bottom = bottom;
    pEb->hdr.state = state;
    pEb->hdr.DrawObj = GFX_GOL_EditBoxDraw; // draw function
    pEb->hdr.actionGet = GFX_GOL_EditBoxActionGet; // message function
    pEb->hdr.actionSet = GFX_GOL_EditBoxActionSet; // default message function
    pEb->hdr.FreeObj = NULL; // free function
    pEb->alignment = alignment;

    // Set the style scheme to be used
    pEb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    pEb->textHeight = GFX_TextStringHeightGet(pEb->hdr.pGolScheme->pFont);

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER*) pEb);
    return pEb;
}

/*********************************************************************
 * Function: GFX_GOL_Editbox_TextSet(GFX_GOL_EDITBOX *pEb, GFX_XCHAR *pText)
 *
 * Notes: Sets a new text.
 *
 ********************************************************************/
void GFX_GOL_EditBoxTextSet(GFX_GOL_EDITBOX *pEb, GFX_XCHAR *pText)
{
    uint16_t ch;
    uint16_t length;
    GFX_XCHAR* pointerFrom;
    GFX_XCHAR* pointerTo;

    // Copy and count length
    pointerFrom = pText;
    pointerTo = pEb->pText;
    length = 0;

    do
    {
        ch = *pointerFrom++;
        *pointerTo++ = ch;
        length++;
        if (length >= pEb->charMax)
        {
            *pointerTo = 0;
            break;
        }
        if (ch == 0)
        {
            break;
        }
    } while (ch);


    pEb->length = length - 1;
}

/*********************************************************************
 * Function: void  GFX_GOL_Editbox_CharAdd(GFX_GOL_EDITBOX* pEb, GFX_XCHAR ch)
 *
 * Notes: Adds character at the end.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_EditBoxCharAdd(GFX_GOL_EDITBOX* pEb, GFX_XCHAR ch)
{

    if (pEb->length >= pEb->charMax)
        return;

    // Add character
    pEb->pText[pEb->length] = ch;
    pEb->length++;
    pEb->pText[pEb->length] = 0;
}

/*********************************************************************
 * Function: void  GFX_GOL_EditBoxCharRemove(GFX_GOL_EDITBOX* pEb)
 *
 * Notes: Deletes character at the end.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_EditBoxCharRemove(GFX_GOL_EDITBOX* pEb)
{

    if (pEb->length == 0)
        return;

    // Delete charachter
    pEb->length--;
    pEb->pText[pEb->length] = 0;

}

/*********************************************************************
 * Function: uint16_t GFX_GOL_EditboxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Translates GOL message for the edit box
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_EditBoxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_EDITBOX *pEb;

    pEb = (GFX_GOL_EDITBOX *) pObj;

    // Evaluate if the message is for the edit box
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DISABLED_STATE))
        return GFX_GOL_OBJECT_ACTION_INVALID;

#ifdef  USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {
        // Check if it falls in edit box borders
        if ((pEb->hdr.left < pMsg->param1) &&
            (pEb->hdr.right > pMsg->param1) &&
            (pEb->hdr.top < pMsg->param2) &&
            (pEb->hdr.bottom > pMsg->param2))
            return GFX_GOL_EDITBOX_ACTION_TOUCHSCREEN;

        return GFX_GOL_OBJECT_ACTION_INVALID;
    }
#endif

#ifdef  USE_KEYBOARD
    if (pMsg->type == TYPE_KEYBOARD)
    {

        if (pMsg->uiEvent == EVENT_CHARCODE)
            return GFX_GOL_EDITBOX_ACTION_CHAR;

        if (pMsg->uiEvent == EVENT_KEYSCAN)
            if (pMsg->param2 == SCAN_BS_PRESSED)
                return GFX_GOL_EDITBOX_ACTION_DEL;

        return OBJ_MSG_INVALID;
    }
#endif


    return GFX_GOL_OBJECT_ACTION_INVALID;
}

/*********************************************************************
 * Function: void GFX_GOL_EditboxActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Changes the state of the edit box by default.
 *
 ********************************************************************/
void GFX_GOL_EditBoxActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg)
{

    GFX_GOL_EDITBOX *pEb;

    pEb = (GFX_GOL_EDITBOX *) pObj;

#ifdef  USE_FOCUS
#ifdef  USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {
        if (!GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DRAW_FOCUS_STATE))
        {
            GFX_OBJ_FocusSet((GFX_OBJ_HEADER*) pEb);
        }
    }
#endif
#endif

    switch (translatedMsg)
    {

        case GFX_GOL_EDITBOX_ACTION_ADD_CHAR:
            GFX_GOL_EditBoxCharAdd(pEb, (GFX_XCHAR) pMsg->param2);
            GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
            break;

        case GFX_GOL_EDITBOX_ACTION_DEL_CHAR:
            GFX_GOL_EditBoxCharRemove(pEb);
            GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
            break;

    }
}

/*********************************************************************
 * Function: uint16_t EditboxDraw(void *pObj)
 *
 * Notes: This is the state machine to draw the button.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_EditBoxDraw(void *pObj)
{

    typedef enum
    {
        GFX_GOL_EDITBOX_STATE_START,
        GFX_GOL_EDITBOX_STATE_DRAW_PANEL,
        GFX_GOL_EDITBOX_STATE_PREPARE_FOR_TEXT,
        GFX_GOL_EDITBOX_STATE_POSITION_TEXT,
        GFX_GOL_EDITBOX_STATE_TEXT,
        GFX_GOL_EDITBOX_STATE_CARET,
        WAIT
    } GFX_GOL_EDITBOX_DRAW_STATES;

    static GFX_GOL_EDITBOX_DRAW_STATES state = GFX_GOL_EDITBOX_STATE_START;
    static GFX_XCHAR* pText;
    static GFX_COLOR tempColor;
    static short temp;
    static short width = 0;
    static GFX_STATUS index = NULL;
    GFX_GOL_EDITBOX *pEb;

    pEb = (GFX_GOL_EDITBOX *) pObj;

    switch (state)
    {

        case GFX_GOL_EDITBOX_STATE_START:

            if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_HIDE_STATE))
            {
                GFX_ColorSet(pEb->hdr.pGolScheme->CommonBkColor);
                index = GFX_RectangleFillDraw(pEb->hdr.left, pEb->hdr.top, pEb->hdr.right, pEb->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                    return(GFX_STATUS_FAILURE);
                }
                state = WAIT;
                return(GFX_STATUS_FAILURE);
            }

            if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DISABLED_STATE))
            {
                tempColor = pEb->hdr.pGolScheme->ColorDisabled;
            }
            else
            {
                tempColor = pEb->hdr.pGolScheme->Color0;
            }

            if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DRAW_STATE))
            {

                GFX_GOL_PanelParameterSet(pEb->hdr.left, pEb->hdr.top, pEb->hdr.right, pEb->hdr.bottom, 0,
                                  tempColor,
                                  pEb->hdr.pGolScheme->EmbossDkColor,
                                  pEb->hdr.pGolScheme->EmbossLtColor,
                                  NULL,
                                  GFX_FILL_STYLE_COLOR,
                                  GFX_GOL_EMBOSS_SIZE);

                state = GFX_GOL_EDITBOX_STATE_DRAW_PANEL;
            }
            else
            {
                state = GFX_GOL_EDITBOX_STATE_PREPARE_FOR_TEXT;
                break;
            }

        case GFX_GOL_EDITBOX_STATE_DRAW_PANEL:
            if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
                return GFX_STATUS_FAILURE;
            state = GFX_GOL_EDITBOX_STATE_PREPARE_FOR_TEXT;

        case GFX_GOL_EDITBOX_STATE_PREPARE_FOR_TEXT:

            GFX_FontSet(pEb->hdr.pGolScheme->pFont);

            if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DISABLED_STATE))
            {
                GFX_ColorSet(pEb->hdr.pGolScheme->TextColorDisabled);
            }
            else
            {
                GFX_ColorSet(pEb->hdr.pGolScheme->TextColor0);
            }

            // get the string buffer
            pText = pEb->pText;
            temp = 1;

            // calculate how many lines are expected so we know where to
            // place the starting point
            while ((GFX_XCHAR) * pText != (GFX_XCHAR) 0)
            {
                if ((GFX_XCHAR) * pText == (GFX_XCHAR) '\n')
                    temp++;
                pText++;
            }

            // go back to the start of the buffer
            pText = pEb->pText;
            // position the cursor
            GFX_LinePositionSet(GFX_LinePositionXGet(), (pEb->hdr.top + pEb->hdr.bottom - temp * pEb->textHeight) >> 1);

            // set state to actual string rendering loop
            state = GFX_GOL_EDITBOX_STATE_POSITION_TEXT;

        case GFX_GOL_EDITBOX_STATE_POSITION_TEXT:

            // get width of the string to render
            width = GFX_TextStringWidthGet(pText, pEb->hdr.pGolScheme->pFont);

            // place the starting point based on text alignment
            if (!GFX_GOL_ObjectStateGet(pEb, GFX_ALIGN_CENTER | GFX_ALIGN_RIGHT))
            {
                GFX_LinePositionSet(pEb->hdr.left + GFX_GOL_EDITBOX_INDENT + GFX_GOL_EMBOSS_SIZE, GFX_LinePositionYGet());
            }
            else
            {
                if (GFX_GOL_ObjectStateGet(pEb, GFX_ALIGN_RIGHT))
                {
                   GFX_LinePositionSet(pEb->hdr.right-width-GFX_GOL_EDITBOX_INDENT-GFX_GOL_EMBOSS_SIZE, GFX_LinePositionYGet());
                }
                else
                {
                    GFX_LinePositionSet((pEb->hdr.left+pEb->hdr.right-width)>>1,GFX_LinePositionYGet());
                }
            }

            state = GFX_GOL_EDITBOX_STATE_TEXT;

        case GFX_GOL_EDITBOX_STATE_TEXT:

            // this is the actual string rendering
            if (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DRAW_STATE))
            {
                index = GFX_TextStringDraw(GFX_LinePositionXGet(),GFX_LinePositionYGet(), pText, 0);
                if(index == GFX_STATUS_FAILURE)
                {
                    return GFX_STATUS_FAILURE;
                }
            }
            else
            {
                GFX_LinePositionRelativeSet(width, 0);
            }
            while ((GFX_XCHAR) * pText > (GFX_XCHAR) 15)
                pText++;

            if ((GFX_XCHAR) * pText == (GFX_XCHAR) '\n')
            {
                GFX_LinePositionRelativeSet(0, pEb->textHeight);
            }

            // check if end of string
            if (*pText != 0)
            {
                state = GFX_GOL_EDITBOX_STATE_POSITION_TEXT;
                pText++;
                break;
            }

            // draw the caret if required
            if (!GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DISABLED_STATE))
            {

                if ((GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DRAW_FOCUS_STATE) && GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_DRAW_CARET_STATE)) || (GFX_GOL_ObjectStateGet(pEb, GFX_GOL_EDITBOX_ENABLE_CARET_STATE)))
                {
                    GFX_ColorSet(pEb->hdr.pGolScheme->TextColor0);
                    state = GFX_GOL_EDITBOX_STATE_CARET;
                }
                else
                {
                    GFX_ColorSet(pEb->hdr.pGolScheme->Color0);
                    state = WAIT;
                    return(GFX_STATUS_FAILURE);
                }
            }
            else
            {
                state = WAIT;
                return(GFX_STATUS_FAILURE);
            }

        case GFX_GOL_EDITBOX_STATE_CARET:

            // draw the caret if required
            index = GFX_RectangleFillDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), GFX_LinePositionXGet() + GFX_GOL_EDITBOX_CARET_WIDTH, GFX_LinePositionYGet() + pEb->textHeight);
            if(index == GFX_STATUS_FAILURE)
            {
                return(GFX_STATUS_FAILURE);
            }

            state = WAIT;
        case WAIT:
            state = GFX_GOL_EDITBOX_STATE_START;
            return(GFX_STATUS_SUCCESS);

    } // switch()

    return GFX_STATUS_SUCCESS;
}
