/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_button.c

  Summary:
    This implements the button object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Button Object.
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

#include "gfx/gfx_gol_button.h"

/******************************************************************************
  Function:
   GFX_GOL_BUTTON *GFX_GOL_ButtonCreate(uint16_t ID, uint16_t left, uint16_t top,
                               uint16_t right, uint16_t bottom, uint16_t radius,
                               void *pBitmap, GFX_XCHAR *pText, GFX_GOL_OBJ_SCHEME *pScheme)

  Summary:
    Creates a BUTTON object and adds it to the current active list.

  Description:
    If the creation is successful, the pointer to the created Object
    is returned. If not successful, NULL is returned.

  Remarks:
    None.
*/
GFX_GOL_BUTTON *GFX_GOL_ButtonCreate
(
    uint16_t            ID,
    uint16_t            left,
    uint16_t            top,
    uint16_t            right,
    uint16_t            bottom,
    uint16_t            radius,
    uint16_t            state,
    GFX_RESOURCE_HDR    *pPressImage,
    GFX_RESOURCE_HDR    *pReleaseImage,
    GFX_XCHAR           *pText,
    GFX_ALIGNMENT       alignment,
    GFX_GOL_OBJ_SCHEME  *pScheme
 )
{
    GFX_GOL_BUTTON *button = NULL;
    button = (GFX_GOL_BUTTON *) GFX_malloc(sizeof (GFX_GOL_BUTTON));

    if (button == NULL)
        return (NULL);

    //button->hdr.instance = instance; //Device Instance set
    button->hdr.ID = ID; // unique id assigned for referencing
    button->hdr.pNxtObj = NULL; // initialize pointer to NULL
    button->hdr.type = GFX_GOL_BUTTON_TYPE; // set object type
    button->hdr.left = left; // left position
    button->hdr.top = top; // top position
    button->hdr.right = right; // right position
    button->hdr.bottom = bottom; // bottom position
    button->radius = radius; // radius
    button->pPressImage = pPressImage; // location of bitmap
    button->pReleaseImage = pReleaseImage;
    button->pText = pText; // location of the text
    button->hdr.state = state; // state
    button->hdr.DrawObj = GFX_GOL_ButtonDraw; // draw function
    button->hdr.actionGet = GFX_GOL_ButtonActionGet; // message function
    button->hdr.actionSet = GFX_GOL_ButtonActionSet; // default message function
    button->hdr.FreeObj = NULL; // free function
    button->alignment = alignment;
    button->hdr.imageStored = false;

    // Set the color scheme to be used
    button->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    #ifdef USE_ALPHABLEND_LITE
    button->previousAlphaColor = 0;
    #endif

    button->textWidth = 0;
    button->textHeight = 0;
    if (button->pText != NULL)
    {
        GFX_GOL_ButtonTextSet(button, pText);
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) button);

#ifdef USE_FOCUS
    // focus and alpha blend cannot be used together
    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_FOCUSED))
        GFX_OBJ_FocusSet((GFX_OBJ_HEADER *) button);
#endif
    return (button);
}

/*********************************************************************
 * Function: GFX_GOL_ButtonTextSet(GFX_GOL_BUTTON *button, GFX_XCHAR *pText)
 *
 *
 * Notes: Sets the text used in the button.
 *
 ********************************************************************/
void GFX_GOL_ButtonTextSet(GFX_GOL_BUTTON *button, GFX_XCHAR *pText)
{
    button->pText = pText;
    button->textWidth = GFX_TextStringWidthGet(pText, button->hdr.pGolScheme->pFont);
    button->textHeight = GFX_TextStringHeightGet(button->hdr.pGolScheme->pFont);
}

void GFX_GOL_ButtonTextAlignmentSet(
                                GFX_GOL_BUTTON *pObject,
                                GFX_ALIGNMENT align)
{

    pObject->alignment = align;

}

GFX_ALIGNMENT GFX_GOL_ButtonTextAlignmentGet(GFX_GOL_BUTTON *pObject)
{
    return(pObject->alignment);
}

/*********************************************************************
 * Function: GFX_GOL_ButtonActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 *
 * Notes: This the default operation to change the state of the button.
 *		 Called inside GFX_GOL_MESSAGE() when GFX_GOL_MESSAGECallback() returns a 1.
 *
 ********************************************************************/
void GFX_GOL_ButtonActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg,void *pObject,GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_BUTTON *button;

    button = (GFX_GOL_BUTTON *) pObject;

#ifdef USE_FOCUS  
#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
        if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_FOCUSED))
        {
            GFX_OBJ_FocusSet((GFX_OBJ_HEADER *) button);
        }
    }
#endif
#endif
    switch (translatedMsg)
    {
        case GFX_GOL_BUTTON_ACTION_PRESSED:
            GFX_GOL_ObjectStateSet(button, GFX_GOL_BUTTON_PRESSED_STATE | GFX_GOL_BUTTON_DRAW_STATE); // set pressed and redraw
            break;

        case GFX_GOL_BUTTON_ACTION_RELEASED:
        case GFX_GOL_BUTTON_ACTION_CANCELPRESS:
            GFX_GOL_ObjectStateClear(button, GFX_GOL_BUTTON_PRESSED_STATE); // reset pressed
            GFX_GOL_ObjectStateSet(button, GFX_GOL_BUTTON_DRAW_STATE); // redraw
            break;

        default:

            // catch all for button messages added by users and
            // behavior defined by users in message callback
            break;
    }
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_ButtonActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_ButtonActionGet(void *pObject,GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_BUTTON *button;

    button = (GFX_GOL_BUTTON *) pObject;

    // Evaluate if the message is for the button
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in the button's face
        if ((button->hdr.left < pMessage->param1) &&
            (button->hdr.right > pMessage->param1) &&
            (button->hdr.top < pMessage->param2) &&
            (button->hdr.bottom > pMessage->param2))
        {
            if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_TOGGLE_STATE))
            {
                if (pMessage->uiEvent == EVENT_RELEASE)
                {
                    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                        return (GFX_GOL_BUTTON_ACTION_RELEASED);
                    else
                        return (GFX_GOL_BUTTON_ACTION_PRESSED);
                }
            }
            else
            {
                if (pMessage->uiEvent == EVENT_RELEASE)
                    return (GFX_GOL_BUTTON_ACTION_RELEASED);
                if (pMessage->uiEvent == EVENT_STILLPRESS)
                {
                    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                        return (GFX_GOL_BUTTON_ACTION_STILLPRESSED);
                }

                if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                    return (GFX_GOL_BUTTON_ACTION_PRESSED);
            }
        }
        else
        {
            if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_TOGGLE_STATE))
            {
                if ((pMessage->uiEvent == EVENT_MOVE) && (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE)))
                    return (GFX_GOL_BUTTON_ACTION_CANCELPRESS);
            }
        }

        return (GFX_GOL_OBJECT_ACTION_INVALID);
    }

#endif
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
    {
        if ((uint16_t) pMessage->param1 == button->hdr.ID)
        {
            if (pMessage->uiEvent == EVENT_KEYSCAN)
            {
                if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_TOGGLE_STATE))
                {
                    if ((pMessage->param2 == SCAN_SPACE_RELEASED) || (pMessage->param2 == SCAN_CR_RELEASED))
                    {
                        if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                            return (GFX_GOL_BUTTON_ACTION_RELEASED);
                        else
                            return (GFX_GOL_BUTTON_ACTION_PRESSED);
                    }
                }
                else
                {
                    if ((pMessage->param2 == SCAN_SPACE_PRESSED) || (pMessage->param2 == SCAN_CR_PRESSED))
                    {
                        return (GFX_GOL_BUTTON_ACTION_PRESSED);
                    }

                    if ((pMessage->param2 == SCAN_SPACE_RELEASED) || (pMessage->param2 == SCAN_CR_RELEASED))
                    {
                        return (GFX_GOL_BUTTON_ACTION_RELEASED);
                    }
                }

                if ((pMessage->param2 == SCAN_SPACE_PRESSED) || (pMessage->param2 == SCAN_CRA_PRESSED))
                {
                    return (GFX_GOL_BUTTON_ACTION_PRESSED);
                }

                if ((pMessage->param2 == SCAN_SPACE_RELEASED) || (pMessage->param2 == SCAN_CRA_RELEASED))
                {
                    return (GFX_GOL_BUTTON_ACTION_RELEASED);
                }
            }
        }

    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Button draw states
 ********************************************************************/
typedef enum
{
    REMOVE,
    RNDBUTTON_DRAW,
    TEXT_DRAW,
    TEXT_DRAW_RUN,
    FOCUS_DRAW,
    ALPHA
} BUTTON_DRAW_STATES;

/*********************************************************************
 * Function: inline uint16_t __attribute__((always_inline)) DrawButtonFocus(BUTTON *button, uint16_t radius, GFX_GOL_BUTTON_DRAW_STATES *current_state)
 ********************************************************************/
inline uint16_t __attribute__((always_inline)) DrawButtonFocus(GFX_GOL_BUTTON *button, uint16_t radius, BUTTON_DRAW_STATES *current_state)
{

        GFX_LineStyleSet(GFX_GOL_FOCUS_LINE);

        if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
        {
            GFX_ColorSet(button->hdr.pGolScheme->TextColor1);
        }
        else
        {
            GFX_ColorSet(button->hdr.pGolScheme->TextColor0);
        }

        // check if the object has rounded corners or not
        if (!button->radius)
        {
            if
                (
                 GFX_RectangleDraw
                 (
                  
                  button->hdr.left + GFX_GOL_EMBOSS_SIZE + 2,
                  button->hdr.top + GFX_GOL_EMBOSS_SIZE + 2,
                  button->hdr.right - GFX_GOL_EMBOSS_SIZE - 2,
                  button->hdr.bottom - GFX_GOL_EMBOSS_SIZE - 2
                  ) == GFX_STATUS_FAILURE
                 )
            {
                return (GFX_STATUS_FAILURE);
            }
        }
        else
        {

            // original center is still the same, but radius is reduced
            if
                (
                 GFX_RectangleRoundDraw
                 (
                  
                  button->hdr.left + radius,
                  button->hdr.top + radius,
                  button->hdr.right - radius,
                  button->hdr.bottom - radius,
                  radius - 2 - GFX_GOL_EMBOSS_SIZE
                  ) == GFX_STATUS_FAILURE
                 )
            {
                return (GFX_STATUS_FAILURE);
            }
        }

        GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

    return(GFX_STATUS_SUCCESS);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_ButtonDraw(void *pObj)
 *
 *
 * Notes: This is the state machine to draw the button.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_ButtonDraw(void *pObject)
{
    static BUTTON_DRAW_STATES state = REMOVE;
    static uint16_t width, height, radius;
    static uint16_t xText, yText;
    static GFX_ALIGNMENT align;
    GFX_RESOURCE_HDR *pBitmap = NULL;
    GFX_COLOR embossLtClr, embossDkClr;
    static GFX_COLOR faceClr;
    GFX_GOL_BUTTON *button;
    static GFX_STATUS index = GFX_STATUS_FAILURE;
    static GFX_XCHAR *ch;
    static uint8_t lineCount = 1;

    button = (GFX_GOL_BUTTON *) pObject;

    switch (state)
    {
        case REMOVE:

            if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_HIDE_STATE))
            { // Hide the button (remove from screen)

                #ifndef GFX_CONFIG_ALPHABLEND_DISABLE
                if (button->hdr.pGolScheme->AlphaValue != 100)
                {

                     GFX_AlphaParamsSet(GFX_Primitive_instance.backgroundPage,button->hdr.left, button->hdr.top,
                                 GFX_Primitive_instance.backgroundPage,button->hdr.left, button->hdr.top,
                                 GFX_Primitive_instance.activePage,button->hdr.left, button->hdr.top);

                      if(CopyPageWindow(
                            &GFX_Primitive_instance.alphaArea,
                            button->hdr.right - button->hdr.left, button->hdr.bottom - button->hdr.top) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
   
                }
                else
                #endif
                {
                    GFX_ColorSet(button->hdr.pGolScheme->CommonBkColor);

                index = GFX_RectangleFillDraw(button->hdr.left, button->hdr.top, button->hdr.right, button->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                }

                return (GFX_STATUS_SUCCESS);
            }

            /* Note: that width and height adjustment considers the following assumptions:
                                        1. if circular width = height = radius*2
                                        2. if vertical capsule width = radius*2
                                        3. if horizontal capsule height = radius*2
                                        4. radius must be less than or equal to width if height is greater than width
                                        5. radius must be less than or equal to height if width is greater than height
                                        6. if button is cornered, radius must be zero
             */
            radius = button->radius; // get radius
            width = (button->hdr.right - button->hdr.left) - (radius * 2); // get width
            height = (button->hdr.bottom - button->hdr.top) - (radius * 2); // get height

            if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_NOPANEL_STATE))
            {
                if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_DISABLED_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                    {
                        embossDkClr = button->hdr.pGolScheme->EmbossLtColor;
                        embossLtClr = button->hdr.pGolScheme->EmbossDkColor;
                        faceClr = button->hdr.pGolScheme->Color1;
                        pBitmap = button->pPressImage;
                    }
                    else
                    {
                        embossLtClr = button->hdr.pGolScheme->EmbossLtColor;
                        embossDkClr = button->hdr.pGolScheme->EmbossDkColor;
                        faceClr = button->hdr.pGolScheme->Color0;
                        pBitmap = button->pReleaseImage;
                    }
                }
                else
                {
                    embossLtClr = button->hdr.pGolScheme->EmbossLtColor;
                    embossDkClr = button->hdr.pGolScheme->EmbossDkColor;
                    faceClr = button->hdr.pGolScheme->ColorDisabled;
                }

                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

#ifdef USE_ALPHABLEND_LITE
                GFX_PrevAlphaColorSet(button->previousAlphaColor);
                GfxPanel.panelAlpha = button->hdr.pGolScheme->AlphaValue;
                button->previousAlphaColor = faceClr;
#endif

                GFX_GOL_PanelParameterSet
                        (
                         
                         button->hdr.left + radius,
                         button->hdr.top + radius,
                         button->hdr.right - radius,
                         button->hdr.bottom - radius,
                         radius,
                         faceClr,
                         embossLtClr,
                         embossDkClr,
                         pBitmap,
                         GFX_FILL_STYLE_COLOR,
                         GFX_GOL_EMBOSS_SIZE
                         );

                #ifndef GFX_CONFIG_GRADIENT_DISABLE
                GFX_GOL_PanelGradientParameterSet(button->hdr.pGolScheme->gradientStartColor,button->hdr.pGolScheme->gradientEndColor);
                GfxPanel.panelFillStyle = button->hdr.pGolScheme->fillStyle;
                #endif
            }
            state = RNDBUTTON_DRAW;

        case RNDBUTTON_DRAW:
            if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_NOPANEL_STATE))
            {
                // check if there is an image to be drawn
                if (button->pReleaseImage != NULL)
                {

                    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                    {
                        pBitmap = button->pPressImage;
                    }
                    else
                    {
                        pBitmap = button->pReleaseImage;
                    }


                    if(GFX_ImageDraw
                                          (
                                          
                                          ((button->hdr.right + button->hdr.left - GFX_ImageWidthGet((void *) pBitmap)) >> 1) + 1,
                                          ((button->hdr.top + button->hdr.bottom - GFX_ImageHeightGet((void *) pBitmap)) >> 1) + 1,
                                          pBitmap
                                          )  == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }

                }
            }
            else
            {
                if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_TWOTONE_STATE))
                {
                    if (GFX_GOL_TwoTonePanelDraw() == GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                }
                else
                {

                    if (GFX_GOL_PanelDraw()==GFX_STATUS_FAILURE)
                    {
                        return (GFX_STATUS_FAILURE);
                    }
                }

            }

            if (button->pText != NULL)
            {

            state = TEXT_DRAW;

        case TEXT_DRAW:

                if (!GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_DISABLED_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_PRESSED_STATE))
                    {
                        GFX_ColorSet(button->hdr.pGolScheme->TextColor1);
                    }
                    else
                    {
                        GFX_ColorSet(button->hdr.pGolScheme->TextColor0);
                    }
                }
                else
                {
                    GFX_ColorSet(button->hdr.pGolScheme->TextColorDisabled);
                }

                GFX_FontSet(button->hdr.pGolScheme->pFont);

                // check text alignment
                if((button->alignment&GFX_ALIGN_RIGHT) == GFX_ALIGN_RIGHT)
                {
                    align = GFX_ALIGN_RIGHT;
                }
                else if((button->alignment&GFX_ALIGN_LEFT) == GFX_ALIGN_LEFT)
                {
                    align = GFX_ALIGN_LEFT;
                }
                else
                {
                    align = GFX_ALIGN_HCENTER;
                }

                if ((GFX_ALIGN_TOP&button->alignment) == GFX_ALIGN_TOP)
                {
                    yText = button->hdr.top + GFX_GOL_EMBOSS_SIZE;

                }
                else if ((GFX_ALIGN_BOTTOM&button->alignment) == GFX_ALIGN_BOTTOM)
                {
                    ch = button->pText;
                    while(*ch != '\0')
                    {
                        if(*ch++ == '\n')
                            lineCount++;
                    }
                    yText = button->hdr.bottom - (button->textHeight*lineCount) - GFX_GOL_EMBOSS_SIZE;

                }
                else
                {
                    ch = button->pText;
                    while(*ch != '\0')
                    {
                        if(*ch++ == '\n')
                            lineCount++;
                    }
                    // centered	text in y direction
                    yText = button->hdr.top + ((button->hdr.bottom-button->hdr.top - (button->textHeight*lineCount) - GFX_GOL_EMBOSS_SIZE) >> 1);

                }
                lineCount = 1;
                state = TEXT_DRAW_RUN;
            }
            else 
            {
                state = FOCUS_DRAW;
case FOCUS_DRAW:
                if(GFX_GOL_ObjectStateGet(button, GFX_GOL_BUTTON_FOCUSED_STATE))
                {
                
                if(DrawButtonFocus(button, radius, &state)== GFX_STATUS_FAILURE)
                {
                    return(GFX_STATUS_FAILURE);
                }
                }
                state = REMOVE;
                return GFX_STATUS_SUCCESS;
            }

        case TEXT_DRAW_RUN:
            index = GFX_TextStringBoxDraw(
                                         button->hdr.left + GFX_GOL_EMBOSS_SIZE + 2,
                                         yText,
                                         button->hdr.right - button->hdr.left - ((GFX_GOL_EMBOSS_SIZE + 2)<<1),
                                         button->hdr.bottom - button->hdr.top - ((GFX_GOL_EMBOSS_SIZE + 2)<<1),
                                         button->pText, 0, align);
            if(index == GFX_STATUS_FAILURE)
            {
                return (GFX_STATUS_FAILURE);
            }
            state = FOCUS_DRAW;
            return(GFX_STATUS_FAILURE);

    }

    return (GFX_STATUS_SUCCESS);
}
