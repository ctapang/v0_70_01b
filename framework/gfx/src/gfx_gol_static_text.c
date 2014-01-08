/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
  gfx_gol_static_text.c

  Summary:
    This implements the static text of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    StaticText Object.
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
#include "gfx/gfx_gol_static_text.h"

/*********************************************************************
 * Function: GFX_GOL_STATICTEXT  *GFX_GOL_StaticTextCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom,
 *								  uint16_t state , GFX_XCHAR *pText, GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * Notes: Creates a GFX_GOL_STATICTEXT object and adds it to the current active list.
 *        If the creation is successful, the pointer to the created Object
 *        is returned. If not successful, NULL is returned.
 *
 ********************************************************************/
GFX_GOL_STATICTEXT *GFX_GOL_StaticTextCreate
(
        uint16_t ID,
        uint16_t left,
        uint16_t top,
        uint16_t right,
        uint16_t bottom,
        uint16_t state,
        GFX_XCHAR *pText,
        GFX_ALIGNMENT alignment,
        GFX_GOL_OBJ_SCHEME *pScheme
)
{
    GFX_GOL_STATICTEXT *pSt = NULL;

    pSt = (GFX_GOL_STATICTEXT *) GFX_malloc(sizeof (GFX_GOL_STATICTEXT));
    if (pSt == NULL)
        return (pSt);

    //pSt->hdr.instance = instance; //Device Instance set
    pSt->hdr.ID = ID; // unique id assigned for referencing
    pSt->hdr.pNxtObj = NULL; // initialize pointer to NULL
    pSt->hdr.type = GFX_GOL_STATICTEXT_TYPE; // set object type
    pSt->hdr.left = left; // left,top corner
    pSt->hdr.top = top;
    pSt->hdr.right = right; // right buttom corner
    pSt->hdr.bottom = bottom;
    pSt->pText = pText; // location of the text
    pSt->hdr.state = state;
    pSt->hdr.DrawObj = GFX_GOL_StaticTextDraw; // draw function
    pSt->hdr.actionGet = GFX_GOL_StaticTextActionGet; // message function
    pSt->hdr.actionSet = NULL; // default message function
    pSt->hdr.FreeObj = NULL; // free function
    pSt->alignment = alignment;

    // Set the color scheme to be used
    pSt->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pSt);
    return (pSt);
}

/*********************************************************************
 * Function: GFX_GOL_StaticText_SetText(GFX_GOL_STATICTEXT *pSt, GFX_XCHAR *pText)
 *
 * Notes: Sets the string that will be used.
 *
 ********************************************************************/
void GFX_GOL_StaticTextTextSet(GFX_GOL_STATICTEXT *pSt, GFX_XCHAR *pText)
{
    pSt->pText = pText;
}

/*********************************************************************
 * Function: uint16_t StTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_StaticTextActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{

    GFX_GOL_STATICTEXT *pSt;

    pSt = (GFX_GOL_STATICTEXT *) pObj;


    // Evaluate if the message is for the static text
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMsg->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in static text control borders
        if
            (
                (pSt->hdr.left < pMsg->param1) &&
                (pSt->hdr.right > pMsg->param1) &&
                (pSt->hdr.top < pMsg->param2) &&
                (pSt->hdr.bottom > pMsg->param2)
                )
        {
            return (GFX_GOL_STATICTEXT_ACTION_SELECTED);
        }
    }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

void GFX_GOL_StaticTextAlignmentSet(GFX_GOL_STATICTEXT *pObject, GFX_ALIGNMENT align)
{
    pObject->alignment = align;
    return;
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_StaticTextDraw(void *pObj)
 *
 * Notes: This is the state machine to draw the static text.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_StaticTextDraw(void *pObject)
{

    typedef enum
    {
        GFX_GOL_STATICTEXT_STATE_IDLE,
        GFX_GOL_STATICTEXT_STATE_CLEANAREA,
        GFX_GOL_STATICTEXT_STATE_INIT,
        WAIT
    } GFX_GOL_STATICTEXT_DRAW_STATES;

    static GFX_GOL_STATICTEXT_DRAW_STATES state = GFX_GOL_STATICTEXT_STATE_IDLE;
    static GFX_STATUS index;
    GFX_GOL_STATICTEXT *pSt;

    pSt = (GFX_GOL_STATICTEXT *) pObject;

    while (1)
    {
        switch (state)
        {
            case GFX_GOL_STATICTEXT_STATE_IDLE:
                if (GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_HIDE_STATE))
                {
                    GFX_ColorSet(pSt->hdr.pGolScheme->CommonBkColor);
                    if (GFX_RectangleFillDraw(pSt->hdr.left, pSt->hdr.top, pSt->hdr.right, pSt->hdr.bottom) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);

                    // State is still IDLE STATE so no need to set state
                    return (GFX_STATUS_SUCCESS);
                }

                if (GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_DRAW_STATE))
                {

                    if (GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_FRAME_STATE))
                    {

                    // show frame if specified to be shown
                    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

                    if (!GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_DISABLED_STATE))
                    {
                        // show enabled color
                        GFX_ColorSet(pSt->hdr.pGolScheme->Color1);
                    }
                    else
                    {
                        // show disabled color
                        GFX_ColorSet(pSt->hdr.pGolScheme->ColorDisabled);
                    }
                    
                   if (GFX_RectangleDraw(pSt->hdr.left, pSt->hdr.top, pSt->hdr.right, pSt->hdr.bottom) == GFX_STATUS_FAILURE)
                            return (GFX_STATUS_FAILURE);
                    }
                }

                state = GFX_GOL_STATICTEXT_STATE_CLEANAREA;

            case GFX_GOL_STATICTEXT_STATE_CLEANAREA:

            #ifdef USE_ALPHABLEND                //Draw the background image
            if (pSt->hdr.pGolScheme->AlphaValue != 100)
            {

                GFX_AlphaParamsSet(GFX_Primitive_instance.backgroundPage,pSt->hdr.left, pSt->hdr.top,
                                 GFX_Primitive_instance.backgroundPage,pSt->hdr.left, pSt->hdr.top,
                                 GFX_Primitive_instance.activePage,pSt->hdr.left, pSt->hdr.top);

                if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        pSt->hdr.right - pSt->hdr.left, pSt->hdr.bottom - pSt->hdr.top) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
            }
            else
            #endif
            {
                // clean area where text will be placed.
                GFX_ColorSet(pSt->hdr.pGolScheme->CommonBkColor);
                if (GFX_RectangleFillDraw(pSt->hdr.left, pSt->hdr.top, pSt->hdr.right, pSt->hdr.bottom) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
            }
            state = GFX_GOL_STATICTEXT_STATE_INIT;

            case GFX_GOL_STATICTEXT_STATE_INIT:
                // set the text color
                if (!GFX_GOL_ObjectStateGet(pSt, GFX_GOL_STATICTEXT_DISABLED_STATE))
                {
                    GFX_ColorSet(pSt->hdr.pGolScheme->TextColor0);
                }
                else
                {
                    GFX_ColorSet(pSt->hdr.pGolScheme->TextColorDisabled);
                }

                // use the font specified in the object
                GFX_FontSet(pSt->hdr.pGolScheme->pFont);

                index = GFX_TextStringBoxDraw(
                        
                        pSt->hdr.left,
                        pSt->hdr.top,
                        pSt->hdr.right - pSt->hdr.left,
                        pSt->hdr.bottom - pSt->hdr.top,
                        pSt->pText, 0, pSt->alignment);

                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
		state = WAIT;
            case WAIT:
                state = GFX_GOL_STATICTEXT_STATE_IDLE; // go back to IDLE state
                return (GFX_STATUS_SUCCESS);
        }
    } // end of switch()
} // end of while(1)    

