/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_digital_meter.c

  Summary:
    This implements the digital meter object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    DigitalMeter Object.
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

#include "gfx/gfx_gol_digital_meter.h"

/************************************************************************************
 * Function: NumberToString(uint32_t Value,GFX_XCHAR *pText, uint8_t NoOfDigits, uint8_t DotPos )
 *
 * Notes: convert the number to string
 *
 *************************************************************************************/
static void NumberToString(uint32_t Value, GFX_XCHAR *pText, uint8_t NoOfDigits, uint8_t DotPos)
{
    uint8_t i;
    uint8_t bIndex;

    for (bIndex = 0; bIndex < NoOfDigits; bIndex++)
    {
        pText[NoOfDigits - bIndex - 1] = '0' + (Value % 10);
        Value /= 10;
    }

    if (DotPos != 0 && DotPos <= NoOfDigits)
    {
        for (i = 0; i < DotPos; i++)
        {
            pText[NoOfDigits - i] = pText[NoOfDigits - 1 - i];
        }

        pText[NoOfDigits - DotPos] = '.';
        pText[NoOfDigits + 1] = '\0';
    }

        //If dot position is 0 or greater than number of digits, then don't put dot in the display
    else
    {
        pText[NoOfDigits] = '\0';
    }
}

/*********************************************************************************************************
 * Function: GFX_GOL_DIGITALMETER  *GFX_DigitalMeterCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t state,
 *                               uint32_t Value, uint8_t NoOfDigits, uint8_t DotPos, GFX_OBJ_SCHEME *pScheme)
 *
 * Notes: Creates a DIGITALMETER object and adds it to the current active list.
 *        If the creation is successful, the pointer to the created Object
 *        is returned. If not successful, NULL is returned.
 *
 **********************************************************************************************************/
GFX_GOL_DIGITALMETER *GFX_GOL_DigitalMeterCreate
(
 uint16_t ID,
 uint16_t left,
 uint16_t top,
 uint16_t right,
 uint16_t bottom,
 uint16_t state,
 uint32_t Value,
 uint8_t NoOfDigits,
 uint8_t DotPos,
 GFX_ALIGNMENT       alignment,
 GFX_GOL_OBJ_SCHEME *pScheme
 )
{
    GFX_GOL_DIGITALMETER *pDm = NULL;
    pDm = GFX_malloc(sizeof (GFX_GOL_DIGITALMETER));
    if (pDm == NULL)
        return (pDm);

    //pDm->hdr.instance = instance;
    pDm->hdr.ID = ID; // unique id assigned for referencing
    pDm->hdr.pNxtObj = NULL; // initialize pointer to NULL
    pDm->hdr.type = GFX_GOL_DIGITALMETER_TYPE; // set object type
    pDm->hdr.left = left; // left,top corner
    pDm->hdr.top = top;
    pDm->hdr.right = right; // right buttom corner
    pDm->hdr.bottom = bottom;
    pDm->Cvalue = Value; // initial value to be displayed
    pDm->hdr.state = state;
    pDm->NoOfDigits = NoOfDigits; // number of digits to be displayed
    pDm->DotPos = DotPos; // position of decimal point
    pDm->hdr.DrawObj = GFX_GOL_DigitalMeterDraw; // draw function
    pDm->hdr.actionGet = GFX_GOL_DigitalMeterActionGet; // message function
    pDm->hdr.actionSet = NULL; // default message function
    pDm->hdr.FreeObj = NULL; // free function
    pDm->alignment = alignment;

    // Set the color scheme to be used
    pDm->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    pDm->textHeight = 0;
    if (pDm->Cvalue != 0)
    {

        // Set the text height
        pDm->textHeight = GFX_TextStringHeightGet(pDm->hdr.pGolScheme->pFont);
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pDm);

    return (pDm);
}

/*********************************************************************
 * Function: GFX_GOL_DigitalMeterValueSet(GFX_GOL_DIGITALMETER *pDm, uint32_t Value)
 *
 * Notes: Sets the value to be displayed.
 *
 ********************************************************************/
void GFX_GOL_DigitalMeterValueSet(GFX_GOL_DIGITALMETER *pDm, int16_t Value)
{

    // store the previous and current value to be displayed
    pDm->Pvalue = pDm->Cvalue;
    pDm->Cvalue = Value;

    pDm->textHeight = GFX_TextStringHeightGet(pDm->hdr.pGolScheme->pFont);
}

/*********************************************************************
 * Function: GFX_GOL_TRANSLATED_ACTION GFX_GOL_DigitalMeterActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 **********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_DigitalMeterActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{

    GFX_GOL_DIGITALMETER *pDm;

    pDm = (GFX_GOL_DIGITALMETER *) pObj;

    // Evaluate if the message is for the static text
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in static text control borders
        if
            (
             (pDm->hdr.left < pMsg->param1) &&
             (pDm->hdr.right > pMsg->param1) &&
             (pDm->hdr.top < pMsg->param2) &&
             (pDm->hdr.bottom > pMsg->param2)
             )
        {
            return (GFX_GOL_DIGITALMETER_ACTION_SELECTED);
        }
    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_DigitalMeterDraw(void *pObj)
 *
 * Notes: This is the state machine to display the changing numbers.
 *
 **********************************************************************/
GFX_STATUS GFX_GOL_DigitalMeterDraw(void *pObj)
{

    typedef enum
    {
        GFX_GOL_DIGITALMETER_STATE_IDLE,
        GFX_GOL_DIGITALMETER_STATE_FRAME,
        GFX_GOL_DIGITALMETER_STATE_DRAW_FRAME,
        GFX_GOL_DIGITALMETER_STATE_INIT,
        GFX_GOL_DIGITALMETER_STATE_SETALIGN,
        GFX_GOL_DIGITALMETER_STATE_SETTEXT,
        GFX_GOL_DIGITALMETER_STATE_ERASETEXT,
        GFX_GOL_DIGITALMETER_STATE_DRAWTEXT,
        GFX_GOL_DIGITALMETER_STATE_WRAPUP,
        WAIT
    } GFX_GOL_DIGITALMETER_DRAW_STATES;

    static GFX_STATUS index = NULL;
    GFX_GOL_DIGITALMETER *pDm;
    static GFX_GOL_DIGITALMETER_DRAW_STATES state = GFX_GOL_DIGITALMETER_STATE_IDLE;
    static short charCtr = 0;
    static GFX_XCHAR CurValue[GFX_GOL_DIGITALMETER_WIDTH], PreValue[GFX_GOL_DIGITALMETER_WIDTH];
    static short textWidth = 0;
    static GFX_XCHAR ch = 0, pch = 0;

    pDm = (GFX_GOL_DIGITALMETER *) pObj;

    while (1)
    {
        switch (state)
        {
            case GFX_GOL_DIGITALMETER_STATE_DRAW_FRAME:
                index = GFX_RectangleDraw(pDm->hdr.left, pDm->hdr.top, pDm->hdr.right, pDm->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = GFX_GOL_DIGITALMETER_STATE_INIT;
                break;

            case GFX_GOL_DIGITALMETER_STATE_IDLE:

                if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_HIDE_STATE) || GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DRAW_STATE))
                {
                    GFX_ColorSet(pDm->hdr.pGolScheme->CommonBkColor);
                    index = GFX_RectangleFillDraw(pDm->hdr.left, pDm->hdr.top, pDm->hdr.right, pDm->hdr.bottom);
                    if(index == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                }
                // if the draw state was to hide then state is still IDLE STATE so no need to change state
                if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_HIDE_STATE))
                {
                    state = WAIT;
                    return (GFX_STATUS_FAILURE);
                }
                state = GFX_GOL_DIGITALMETER_STATE_FRAME;

            case GFX_GOL_DIGITALMETER_STATE_FRAME:

                if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DRAW_STATE | GFX_GOL_DIGITALMETER_FRAME_STATE) == (GFX_GOL_DIGITALMETER_DRAW_STATE | GFX_GOL_DIGITALMETER_FRAME_STATE))
                {
                    // show frame if specified to be shown
                    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

                    if (!GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DISABLED_STATE))
                    {
                        // show enabled color
                        GFX_ColorSet(pDm->hdr.pGolScheme->Color1);
                    }
                    else
                    {
                        // show disabled color
                        GFX_ColorSet(pDm->hdr.pGolScheme->ColorDisabled);
                    }
                    state = GFX_GOL_DIGITALMETER_STATE_DRAW_FRAME;
                    break;
                }
                else
                {
                    state = GFX_GOL_DIGITALMETER_STATE_INIT;
                }

            case GFX_GOL_DIGITALMETER_STATE_INIT:
                // set the text color
                if (!GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DISABLED_STATE))
                {
                    GFX_ColorSet(pDm->hdr.pGolScheme->TextColor0);
                }
                else
                {
                    GFX_ColorSet(pDm->hdr.pGolScheme->TextColorDisabled);
                }

                // convert the values to be displayed in string format
                NumberToString(pDm->Pvalue, PreValue, pDm->NoOfDigits, pDm->DotPos);
                NumberToString(pDm->Cvalue, CurValue, pDm->NoOfDigits, pDm->DotPos);

                // use the font specified in the object
                GFX_FontSet(pDm->hdr.pGolScheme->pFont);

                state = GFX_GOL_DIGITALMETER_STATE_SETALIGN; // go to drawing of text

            case GFX_GOL_DIGITALMETER_STATE_SETALIGN:
                if (!charCtr)
                {
                    // set position of the next character (based on alignment and next character)
                    textWidth = GFX_TextStringWidthGet(CurValue, pDm->hdr.pGolScheme->pFont);

                    // Display text with center alignment
                    if ( pDm->alignment & GFX_ALIGN_CENTER )
                    {
                        GFX_LinePositionSet((pDm->hdr.left + pDm->hdr.right - textWidth) >> 1, pDm->hdr.top);
                    }

                        // Display text with right alignment
                    else if ( pDm->alignment & GFX_ALIGN_RIGHT )
                    {
                        GFX_LinePositionSet((pDm->hdr.right - textWidth - GFX_GOL_DIGITALMETER_INDENT), pDm->hdr.top);
                    }

                        // Display text with left alignment
                    else
                    {
                        GFX_LinePositionSet(pDm->hdr.left + GFX_GOL_DIGITALMETER_INDENT, pDm->hdr.top);
                    }
                }
                pch = *(PreValue + charCtr);
                ch = *(CurValue + charCtr);
                state = GFX_GOL_DIGITALMETER_STATE_SETTEXT;

            case GFX_GOL_DIGITALMETER_STATE_SETTEXT:

                if (0x0000 != ch)
                {
                    if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_DRAW_STATE))
                    {
                        GFX_ColorSet(pDm->hdr.pGolScheme->CommonBkColor);
                    }
                    else if (GFX_GOL_ObjectStateGet(pDm, GFX_GOL_DIGITALMETER_UPDATE_STATE))
                    {
                        if (pch != ch)
                        {
                            GFX_ColorSet(pDm->hdr.pGolScheme->CommonBkColor);
                        }
                        else
                        {
                            state = GFX_GOL_DIGITALMETER_STATE_DRAWTEXT;
                            break;
                        }
                    }
                    state = GFX_GOL_DIGITALMETER_STATE_ERASETEXT;
                   break;
                }
                else
                {
                    state = GFX_GOL_DIGITALMETER_STATE_WRAPUP;
                    break;
                }

            case GFX_GOL_DIGITALMETER_STATE_ERASETEXT:
               index = GFX_RectangleFillDraw(GFX_LinePositionXGet(), pDm->hdr.top + 1, GFX_LinePositionXGet() + GFX_TextStringWidthGet(&ch, pDm->hdr.pGolScheme->pFont), pDm->hdr.bottom - 1);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = GFX_GOL_DIGITALMETER_STATE_DRAWTEXT;

            case GFX_GOL_DIGITALMETER_STATE_DRAWTEXT:
                GFX_ColorSet(pDm->hdr.pGolScheme->TextColor0);

                // render the character
                if(GFX_TextCharDraw(ch) != 0)
                     return(GFX_STATUS_FAILURE);

                // move cursor
                GFX_LinePositionRelativeSet(GFX_TextStringWidthGet(&ch, pDm->hdr.pGolScheme->pFont)>>1,0);

                charCtr++; // update to next character
                ch = *(CurValue + charCtr);
                pch = *(PreValue + charCtr);
                state = GFX_GOL_DIGITALMETER_STATE_SETTEXT;
                break;

            case GFX_GOL_DIGITALMETER_STATE_WRAPUP:
                // end of text string is reached no more lines to display
                charCtr = 0;
                state = WAIT;
            case WAIT:
                state = GFX_GOL_DIGITALMETER_STATE_IDLE;
                return (GFX_STATUS_SUCCESS);

        } // end of switch()
    } // end of while(1)
}
