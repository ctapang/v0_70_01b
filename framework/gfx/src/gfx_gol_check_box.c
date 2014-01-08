/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_check_box.c

  Summary:
    This implements the check box object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    CheckBox Object.
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
#include "gfx/gfx_gol_check_box.h"

// This is indent from outside borders
    #define GFX_GOL_CHECKBOX_INDENT   2

/*********************************************************************
 * Function: GFX_GOL_CHECKBOX  *GFX_GOL_Checkbox_Create(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *                              uint16_t bottom, uint16_t state, GFX_XCHAR *pText,
 *                              GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Overview: Creates the check box.
 *
 ********************************************************************/
GFX_GOL_CHECKBOX *GFX_GOL_CheckboxCreate
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
    GFX_GOL_CHECKBOX *pCb = NULL;

    pCb = (GFX_GOL_CHECKBOX *) GFX_malloc(sizeof (GFX_GOL_CHECKBOX));
    if (pCb == NULL)
        return (pCb);

    pCb->hdr.ID = ID;
    pCb->hdr.pNxtObj = NULL;
    pCb->hdr.type = GFX_GOL_CHECKBOX_TYPE;
    pCb->hdr.left = left;
    pCb->hdr.top = top;
    pCb->hdr.right = right;
    pCb->hdr.bottom = bottom;
    pCb->pText = pText;
    //pCb->hdr.instance = instance; //Device Instance set
    pCb->hdr.state = state;
    pCb->hdr.DrawObj = GFX_GOL_CheckBoxDraw; // draw function
    pCb->hdr.actionGet = GFX_GOL_CheckBoxActionGet; // message function
    pCb->hdr.actionSet = GFX_GOL_CheckBoxActionSet; // default message function
    pCb->hdr.FreeObj = NULL; // free function
    pCb->alignment = alignment;

    // Set the style scheme
    pCb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    // Set the text height
    pCb->textHeight = 0;
    if (pText != NULL)
    {
        pCb->textHeight = GFX_TextStringHeightGet(pCb->hdr.pGolScheme->pFont);
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pCb);

    return (pCb);
}

/*********************************************************************
 * Function: GFX_GOL_CheckboxTextSet(GFX_GOL_CHECKBOX *pCb, char *pText)
 *
 * Overview: Sets the text.
 *
 ********************************************************************/
void GFX_GOL_CheckboxTextSet(GFX_GOL_CHECKBOX *pCb, GFX_XCHAR *pText)
{
    pCb->pText = pText;
    pCb->textHeight = GFX_TextStringHeightGet(pCb->hdr.pGolScheme->pFont);
}

/*********************************************************************
 * Function: GFX_GOL_CheckboxActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 * Overview: Changes the state of the check box by default.
 *
 ********************************************************************/
void GFX_GOL_CheckBoxActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg,void *pObject,GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_CHECKBOX *pCb;

    pCb = (GFX_GOL_CHECKBOX *) pObject;

#ifdef USE_FOCUS
#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
        if (!GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_FOCUSED))
        {
            GFX_GOL_FocusSet((GFX_GOL_HEADER *) pCb);
        }
    }

#endif
#endif
    switch (translatedMsg)
    {
        case GFX_GOL_CHECKBOX_ACTION_CHECKED:
            GFX_GOL_ObjectStateSet(pCb, GFX_GOL_CHECKBOX_CHECKED_STATE | GFX_GOL_CHECKBOX_DRAW_CHECK_STATE); // Set checked and redraw
            break;

        case GFX_GOL_CHECKBOX_ACTION_UNCHECKED:
            GFX_GOL_ObjectStateClear(pCb, GFX_GOL_CHECKBOX_CHECKED_STATE); // Reset check
            GFX_GOL_ObjectStateSet(pCb, GFX_GOL_CHECKBOX_DRAW_CHECK_STATE); // Redraw
            break;
    }
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_CheckboxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Overview: Checks if the check box will be affected by the message
 *           and returns translated message.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_CheckBoxActionGet(void *pObject, GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_CHECKBOX *pCb;

    pCb = (GFX_GOL_CHECKBOX *) pObject;

    // Evaluate if the message is for the check box
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in the check box borders
        if
            (
                (pCb->hdr.left < pMessage->param1) &&
                (pCb->hdr.right > pMessage->param1) &&
                (pCb->hdr.top < pMessage->param2) &&
                (pCb->hdr.bottom > pMessage->param2)
                )
        {
            if (pMessage->uiEvent == EVENT_PRESS)
            {
                if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_CHECKED_STATE))
                    return (GFX_GOL_CHECKBOX_ACTION_UNCHECKED);
                else
                    return (GFX_GOL_CHECKBOX_ACTION_CHECKED);
            }
        }

        return (GFX_GOL_OBJECT_ACTION_INVALID);
    }

#endif
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
    {
        if ((uint16_t) pMessage->param1 == pCb->hdr.ID)
        {
            if (pMessage->uiEvent == EVENT_KEYSCAN)
            {
                if ((pMessage->param2 == SCAN_SPACE_PRESSED) || (pMessage->param2 == SCAN_CR_PRESSED))
                {
                    if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_CHECKED))
                        return (GFX_GOL_CHECKBOX_ACTION_UNCHECKED);
                    else
                        return (GFX_GOL_CHECKBOX_ACTION_CHECKED);
                }
            }
        }
    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_CheckboxDraw(void *pObj)
 *
 * Output: returns the status of the drawing
 *		  0 - not complete
 *         1 - done
 *
 * Overview: Draws check box.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_CheckBoxDraw(void *pObject)
{

    typedef enum
    {
        GFX_GOL_CHECKBOX_STATE_REMOVE,
        GFX_GOL_CHECKBOX_STATE_BOX_DRAW,
        GFX_GOL_CHECKBOX_STATE_RUN_DRAW,
        GFX_GOL_CHECKBOX_STATE_TEXT_DRAW,
        GFX_GOL_CHECKBOX_STATE_TEXT_DRAW_RUN,
        GFX_GOL_CHECKBOX_STATE_SET_CHECK_DRAW,
        GFX_GOL_CHECKBOX_STATE_CHECK_DRAW,
        GFX_GOL_CHECKBOX_STATE_FOCUS_DRAW,
    } GFX_GOL_CHECKBOX_DRAW_STATES;

    static GFX_COLOR tempColor;
    static GFX_GOL_CHECKBOX_DRAW_STATES state = GFX_GOL_CHECKBOX_STATE_REMOVE;
    static GFX_STATUS index = GFX_STATUS_FAILURE;
    static short checkIndent;

    GFX_GOL_CHECKBOX *pCb;

    pCb = (GFX_GOL_CHECKBOX *) pObject;

    while (1)
    {
        switch (state)
        {
            case GFX_GOL_CHECKBOX_STATE_RUN_DRAW:
                if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                state = GFX_GOL_CHECKBOX_STATE_TEXT_DRAW;

            case GFX_GOL_CHECKBOX_STATE_TEXT_DRAW:
                if (pCb->pText != NULL)
                {
                    GFX_FontSet(pCb->hdr.pGolScheme->pFont);

                    if (!GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DISABLED_STATE))
                    {
                        GFX_ColorSet(pCb->hdr.pGolScheme->TextColor0);
                    }
                    else
                    {
                        GFX_ColorSet(pCb->hdr.pGolScheme->TextColorDisabled);
                    }

                    GFX_LinePositionSet
                            (
                            
                            pCb->hdr.left + pCb->hdr.bottom - pCb->hdr.top + GFX_GOL_CHECKBOX_INDENT,
                            (pCb->hdr.bottom + pCb->hdr.top - pCb->textHeight) >> 1
                            );

                    state = GFX_GOL_CHECKBOX_STATE_TEXT_DRAW_RUN;
                }
                else
                {
                    state = GFX_GOL_CHECKBOX_STATE_SET_CHECK_DRAW;
                    break;
                }

            case GFX_GOL_CHECKBOX_STATE_TEXT_DRAW_RUN:

                index = GFX_TextStringDraw(GFX_LinePositionXGet(),GFX_LinePositionYGet(),pCb->pText, 0);
                if(index==GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_CHECKBOX_STATE_SET_CHECK_DRAW;
                break;

            case GFX_GOL_CHECKBOX_STATE_REMOVE:

                if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_HIDE_STATE))
                {
                    GFX_ColorSet(pCb->hdr.pGolScheme->CommonBkColor);
                    index = GFX_RectangleFillDraw(pCb->hdr.left, pCb->hdr.top, pCb->hdr.right, pCb->hdr.bottom);
 
                    if(index == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                    
                        return (GFX_STATUS_SUCCESS);
                }

                state = GFX_GOL_CHECKBOX_STATE_BOX_DRAW;

            case GFX_GOL_CHECKBOX_STATE_BOX_DRAW:
                if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DRAW_STATE))
                {
                    if (!GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DISABLED_STATE))
                    {
                        tempColor = pCb->hdr.pGolScheme->Color0;
                    }
                    else
                    {
                        tempColor = pCb->hdr.pGolScheme->ColorDisabled; 
                    }
                        GFX_GOL_PanelParameterSet
                                (
                                
                                pCb->hdr.left + GFX_GOL_CHECKBOX_INDENT,
                                pCb->hdr.top + GFX_GOL_CHECKBOX_INDENT,
                                pCb->hdr.left + (pCb->hdr.bottom - pCb->hdr.top) - GFX_GOL_CHECKBOX_INDENT,
                                pCb->hdr.bottom - GFX_GOL_CHECKBOX_INDENT,
                                0,
                                tempColor,
                                pCb->hdr.pGolScheme->EmbossDkColor,
                                pCb->hdr.pGolScheme->EmbossLtColor,
                                NULL,
                                GFX_FILL_STYLE_COLOR,
                                GFX_GOL_EMBOSS_SIZE
                                );

                    state = GFX_GOL_CHECKBOX_STATE_RUN_DRAW;
                    break;
                }
                else
                {
                    state = GFX_GOL_CHECKBOX_STATE_SET_CHECK_DRAW;
                }

            case GFX_GOL_CHECKBOX_STATE_SET_CHECK_DRAW:
                if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DRAW_STATE | GFX_GOL_CHECKBOX_DRAW_CHECK_STATE))
                {
                    if (!GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DISABLED_STATE))
                    {
                        if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_CHECKED_STATE))
                        {
                            GFX_ColorSet(pCb->hdr.pGolScheme->TextColor0);
                        }
                        else
                        {
                            GFX_ColorSet(pCb->hdr.pGolScheme->Color0);
                        }
                    }
                    else
                    {
                        if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_CHECKED_STATE))
                        {
                            GFX_ColorSet(pCb->hdr.pGolScheme->TextColorDisabled);
                        }
                        else
                        {
                            GFX_ColorSet(pCb->hdr.pGolScheme->ColorDisabled);
                        }
                    }

                    checkIndent = (pCb->hdr.bottom - pCb->hdr.top) >> 2;
                    state = GFX_GOL_CHECKBOX_STATE_CHECK_DRAW;
                }
                else
                {
                    state = GFX_GOL_CHECKBOX_STATE_FOCUS_DRAW;
                    break;
                }

            case GFX_GOL_CHECKBOX_STATE_CHECK_DRAW:

                        index = GFX_RectangleFillDraw
                        (
                        
                        pCb->hdr.left + checkIndent + GFX_GOL_EMBOSS_SIZE,
                        pCb->hdr.top + checkIndent + GFX_GOL_EMBOSS_SIZE,
                        pCb->hdr.left + (pCb->hdr.bottom - pCb->hdr.top) - checkIndent - GFX_GOL_EMBOSS_SIZE,
                        pCb->hdr.bottom - checkIndent - GFX_GOL_EMBOSS_SIZE
                        );
                       
                if(index==GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_CHECKBOX_STATE_FOCUS_DRAW;

            case GFX_GOL_CHECKBOX_STATE_FOCUS_DRAW:
                if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_DRAW_STATE | GFX_GOL_CHECKBOX_DRAW_FOCUS_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(pCb, GFX_GOL_CHECKBOX_FOCUSED_STATE))
                    {
                        GFX_ColorSet(pCb->hdr.pGolScheme->TextColor0);
                    }
                    else
                    {
                       GFX_ColorSet(pCb->hdr.pGolScheme->CommonBkColor);
                    }

                    GFX_LineStyleSet(GFX_GOL_FOCUS_LINE);
                    index = GFX_RectangleDraw(pCb->hdr.left, pCb->hdr.top, pCb->hdr.right, pCb->hdr.bottom);
                    if(index == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }

                    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
                }
                state = GFX_GOL_CHECKBOX_STATE_REMOVE;
                return (GFX_STATUS_SUCCESS);
        } // end of switch()   
    } // end of while(1)
}
