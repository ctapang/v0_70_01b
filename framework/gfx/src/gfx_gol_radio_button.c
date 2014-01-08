/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_radio_button.c

  Summary:
    This implements the radio object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    RadioButton Object.
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


#include "gfx/gfx_gol_radio_button.h"

#define GFX_GOL_RADIOBUTTON_INDENT   2           // Indent for the text from title bar border

// This pointer is used to create linked list of radio buttons for the group
GFX_GOL_RADIOBUTTON *_pListButtons = NULL;

/*********************************************************************
 * Function: RADIOBUTTON  *RbCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *                              uint16_t bottom, uint16_t state, GFX_XCHAR *pText, GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Overview: creates the radio button
 *
 ********************************************************************/
GFX_GOL_RADIOBUTTON *GFX_GOL_RadioButtonCreate
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
    GFX_GOL_RADIOBUTTON *pRb = NULL;
    GFX_GOL_RADIOBUTTON *pointer;

    pRb = (GFX_GOL_RADIOBUTTON *) GFX_malloc(sizeof (GFX_GOL_RADIOBUTTON));
    if (pRb == NULL)
        return (pRb);

    //pRb->hdr.instance = instance; //Device Instance set
    pRb->hdr.ID = ID;
    pRb->hdr.pNxtObj = NULL;
    pRb->hdr.type = GFX_GOL_RADIOBUTTON_TYPE;
    pRb->hdr.left = left;
    pRb->hdr.top = top;
    pRb->hdr.right = right;
    pRb->hdr.bottom = bottom;
    pRb->pText = pText;
    pRb->pNext = NULL; // last radio button in the list
    pRb->hdr.state = state;
    pRb->hdr.DrawObj = GFX_GOL_RadioButtonDraw; // draw function
    pRb->hdr.actionGet = GFX_GOL_RadioButtonActionGet; // message function
    pRb->hdr.actionSet = GFX_GOL_RadioButtonActionSet; // default message function
    pRb->hdr.FreeObj = NULL; // free function
    pRb->alignment = alignment;

    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_GROUP_STATE))
    {
        // If it's first button in the group start new button's list
        _pListButtons = pRb;

        // Attach the button to the list
        pRb->pHead = (GFX_GOL_OBJ_HEADER *) _pListButtons;
    }
    else
    {

        // Attach the button to the list
        pRb->pHead = (GFX_GOL_OBJ_HEADER *) _pListButtons;
        pointer = _pListButtons;
        while (pointer->pNext != NULL)
        {
            pointer = (GFX_GOL_RADIOBUTTON *) pointer->pNext;
        }

        pointer->pNext = (GFX_GOL_OBJ_HEADER *) pRb;
    }

    // Set the style scheme to be used
    pRb->hdr.pGolScheme = pScheme;

    // Set the text height
    pRb->textHeight = 0;
    if (pText != NULL)
    {
        pRb->textHeight = GFX_TextStringHeightGet(pRb->hdr.pGolScheme->pFont);
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pRb);

    return (pRb);
}

/*********************************************************************
 * Function: void GFX_GOL_RadioButton_CheckSet(RADIOBUTTON *pRb, uint16_t ID)
 *
 * Input: pRb - the pointer to any radio button in the group
 *        ID - ID of button to be checked
 *
 * Output: none
 *
 * Overview: sets radio button to checked state, and marks states of group
 *           radio buttons to be redrawn
 *
 ********************************************************************/
void GFX_GOL_RadioButtonCheckSet(GFX_GOL_RADIOBUTTON *pRb, uint16_t ID)
{
    GFX_GOL_RADIOBUTTON *pointer;

    pointer = (GFX_GOL_RADIOBUTTON *) pRb->pHead;

    while (pointer != NULL)
    {
        if (pointer->hdr.ID == ID)
        {
            GFX_GOL_ObjectStateSet(pointer, GFX_GOL_RADIOBUTTON_CHECKED_STATE | GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE); // set check and redraw
        }
        else
        {
            GFX_GOL_ObjectStateClear(pointer, GFX_GOL_RADIOBUTTON_CHECKED_STATE); // reset checked
            GFX_GOL_ObjectStateSet(pointer, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE); // redraw
        }

        pointer = (GFX_GOL_RADIOBUTTON *) pointer->pNext;
    }
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_RadioButton_CheckGet(RADIOBUTTON *pRb)
 *
 * Input: pRb - the pointer to any radio button in the group
 *
 * Output: ID of checked button, -1 if there are no checked buttons
 *
 * Overview: gets ID of checked radio button
 *
 ********************************************************************/
uint16_t GFX_GOL_RadioButtonCheckGet(GFX_GOL_RADIOBUTTON *pRb)
{
    GFX_GOL_RADIOBUTTON *pointer;

    pointer = (GFX_GOL_RADIOBUTTON *) pRb->pHead;

    while (pointer != NULL)
    {
        if (GFX_GOL_ObjectStateGet(pointer, GFX_GOL_RADIOBUTTON_CHECKED_STATE))
        {
            return (pointer->hdr.ID);
        }

        pointer = (GFX_GOL_RADIOBUTTON *) pointer->pNext;
    }

    return (-1);
}

/*********************************************************************
 * Function: GFX_GOL_RadioButtonTextSet(GFX_GOL_RADIOBUTTON *pRb, GFX_XCHAR *pText)
 *
 * Input: pRb - the pointer to the radio button
 *        pText - pointer to the text
 *
 * Output: none
 *
 * Overview: sets text
 *
 ********************************************************************/
void GFX_GOL_RadioButtonTextSet(GFX_GOL_RADIOBUTTON *pRb, GFX_XCHAR *pText)
{
    pRb->pText = pText;
    pRb->textHeight = GFX_TextStringHeightGet((GFX_RESOURCE_HDR *) pRb->hdr.pGolScheme->pFont);
}

/*********************************************************************
 * Function: GFX_GOL_RadioButtonActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 * Overview: changes the state of the radio button by default
 *
 ********************************************************************/
void GFX_GOL_RadioButtonActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg, void *pObject, GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_RADIOBUTTON *pointer;
    GFX_GOL_RADIOBUTTON *pRb;

    pRb = (GFX_GOL_RADIOBUTTON *) pObject;

#ifdef USE_FOCUS
#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
        if (!GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_FOCUSED_STATE))
        {
            GFX_GOL_FocusSet((GFX_GOL_HEADER *) pRb);
        }
    }

#endif
#endif
    if (translatedMsg == GFX_GOL_RADIOBUTTON_ACTION_CHECKED)
    {

        // Uncheck radio buttons in the group
        pointer = (GFX_GOL_RADIOBUTTON *) pRb->pHead;

        while (pointer != NULL)
        {
            if (GFX_GOL_ObjectStateGet(pointer, GFX_GOL_RADIOBUTTON_CHECKED_STATE))
            {
                GFX_GOL_ObjectStateClear(pointer, GFX_GOL_RADIOBUTTON_CHECKED_STATE); // reset check
                GFX_GOL_ObjectStateSet(pointer, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE); // redraw
            }

            pointer = (GFX_GOL_RADIOBUTTON *) pointer->pNext;
        }

        GFX_GOL_ObjectStateSet(pRb, GFX_GOL_RADIOBUTTON_CHECKED_STATE | GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE); // set check and redraw
    }
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_RadioButtonActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Overview: translates the GOL message for the radio button
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_RadioButtonActionGet(void *pObject, GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_RADIOBUTTON *pRb;

    pRb = (GFX_GOL_RADIOBUTTON *) pObject;

    // Evaluate if the message is for the radio button
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
        if (pMessage->uiEvent == EVENT_PRESS)
        {

            // Check if it falls in the radio button borders
            if
                (
                    (pRb->hdr.left < pMessage->param1) &&
                    (pRb->hdr.right > pMessage->param1) &&
                    (pRb->hdr.top < pMessage->param2) &&
                    (pRb->hdr.bottom > pMessage->param2)
                    )
            {
                if (!GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_CHECKED_STATE))
                    return (GFX_GOL_RADIOBUTTON_ACTION_CHECKED);
            }
        }

        return (GFX_GOL_OBJECT_ACTION_INVALID);
    }

#endif
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
    {
        if ((uint16_t) pMessage->param1 == pRb->hdr.ID)
        {
            if (pMessage->uiEvent == EVENT_KEYSCAN)
            {
                if ((pMessage->param2 == SCAN_SPACE_PRESSED) || (pMsg->param2 == SCAN_CR_PRESSED))
                {
                    if (!GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_CHECKED_STATE))
                        return (GFX_GOL_RADIOBUTTON_ACTION_CHECKED);
                }
            }
        }
    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_RadioButtonDraw(void *pObj)
 *
 * Output: returns the status of the drawing
 *		  0 - not completed
 *         1 - done
 *
 * Overview: draws radio button
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_RadioButtonDraw(void *pObj)
{

    typedef enum
    {
        REMOVE,
        DRAW_BUTTON0,
        DRAW_BUTTON1,
        DRAW_TEXT,
        DRAW_TEXT_RUN,
        DRAW_CHECK,
        DRAW_CHECK_RUN,
        DRAW_FOC,
        DRAW_FOC_ACTUAL,
    } GFX_GOL_RADIOBUTTON_DRAW_STATES;

#define SIN45   46341

    static GFX_GOL_RADIOBUTTON_DRAW_STATES state = REMOVE;
    static uint16_t checkIndent;
    static uint16_t radius;
    static uint16_t x, y;
    static uint32_t temp;
    static GFX_STATUS index = GFX_STATUS_FAILURE;
    static GFX_COLOR faceClr;
    GFX_GOL_RADIOBUTTON *pRb;

    pRb = (GFX_GOL_RADIOBUTTON *) pObj;

    while (1)
    {
        switch (state)
        {
            case REMOVE:

                if (GFX_GOL_ObjectStateGet(pRb, (GFX_GOL_RADIOBUTTON_HIDE_STATE | GFX_GOL_RADIOBUTTON_DRAW_STATE)))
                {
                    GFX_ColorSet(pRb->hdr.pGolScheme->CommonBkColor);
                    index = GFX_RectangleDraw(pRb->hdr.left, pRb->hdr.top, pRb->hdr.right, pRb->hdr.bottom);
                    if(index == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                }

                if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_HIDE_STATE))
                {
                    return (GFX_STATUS_SUCCESS);
                }
                radius = ((pRb->hdr.bottom - pRb->hdr.top) >> 1) - GFX_GOL_RADIOBUTTON_INDENT;
                x = pRb->hdr.left + ((pRb->hdr.bottom - pRb->hdr.top) >> 1) + GFX_GOL_RADIOBUTTON_INDENT;
                y = (pRb->hdr.bottom + pRb->hdr.top) >> 1;
                temp = SIN45;

                if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DRAW_STATE))
                {
                    state = DRAW_BUTTON0;
                }
                else if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE))
                {
                    state = DRAW_CHECK;
                    break;
                }
                else if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DRAW_FOCUS_STATE))
                {
                    state = DRAW_FOC;
                    break;
                }
                else
                {
                    return (GFX_STATUS_SUCCESS);
                }

            case DRAW_BUTTON0:
                if (!GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DISABLED_STATE))
                {
                    faceClr = pRb->hdr.pGolScheme->Color0;
                }
                else
                {
                    faceClr = pRb->hdr.pGolScheme->ColorDisabled;
                }

                GFX_GOL_PanelParameterSet
                        (
                        
                        x,
                        y,
                        x,
                        y,
                        radius,
                        faceClr,
                        pRb->hdr.pGolScheme->EmbossDkColor,
                        pRb->hdr.pGolScheme->EmbossLtColor,
                        NULL,
                        GFX_FILL_STYLE_COLOR,
                        GFX_GOL_EMBOSS_SIZE
                        );
                state = DRAW_BUTTON1;

            case DRAW_BUTTON1:
                if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }

                state = DRAW_TEXT;

            case DRAW_TEXT:
                if (pRb->pText != NULL)
                {
                    GFX_FontSet(pRb->hdr.pGolScheme->pFont);

                    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DISABLED_STATE))
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->TextColorDisabled);
                    }
                    else
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->TextColor0);
                    }

                    GFX_LinePositionSet
                            (
                            
                            pRb->hdr.left + pRb->hdr.bottom - pRb->hdr.top + GFX_GOL_RADIOBUTTON_INDENT,
                            (pRb->hdr.bottom + pRb->hdr.top - pRb->textHeight) >> 1
                            );

                    state = DRAW_TEXT_RUN;
                }
                else
                {
                    state = DRAW_CHECK;
                    break;
                }

            case DRAW_TEXT_RUN:

                if (GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), pRb->pText, 0) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);

                state = DRAW_CHECK;
                break;

            case DRAW_CHECK:
                if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_CHECKED_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DISABLED_STATE))
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->TextColorDisabled);
                    }
                    else
                    {
#if (GFX_CONFIG_COLOR_DEPTH == 1)
                        GFX_ColorSet(BLACK);
#else
                        GFX_ColorSet(pRb->hdr.pGolScheme->TextColor0);
#endif
                    }
                }
                else
                {
                    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DISABLED_STATE))
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->ColorDisabled);
                    }
                    else
                    {
#if (GFX_CONFIG_COLOR_DEPTH == 1)
                        GFX_ColorSet(WHITE);
#else
                        GFX_ColorSet(pRb->hdr.pGolScheme->Color0);
#endif
                    }
                }

                state = DRAW_CHECK_RUN;

            case DRAW_CHECK_RUN:
                checkIndent = (pRb->hdr.bottom - pRb->hdr.top) >> 2;
                index = GFX_CircleFillDraw(x, y, radius - checkIndent);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = DRAW_FOC;
                break;

            case DRAW_FOC:
                if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_DRAW_FOCUS_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(pRb, GFX_GOL_RADIOBUTTON_FOCUSED_STATE))
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->TextColor0);
                    }
                    else
                    {
                        GFX_ColorSet(pRb->hdr.pGolScheme->CommonBkColor);
                    }

                    GFX_LineStyleSet(GFX_GOL_FOCUS_LINE);
                    state = DRAW_FOC_ACTUAL;
                    break;
                }
                state = REMOVE;
                return(GFX_STATUS_SUCCESS);

            case DRAW_FOC_ACTUAL:
                if(GFX_RectangleDraw(pRb->hdr.left, pRb->hdr.top, pRb->hdr.right, pRb->hdr.bottom) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);

                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
                state = REMOVE;
                return(GFX_STATUS_SUCCESS);
        } // end of switch()
    } // end of while(1)

}
