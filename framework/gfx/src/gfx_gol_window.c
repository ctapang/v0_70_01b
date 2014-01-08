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
    Window Object.
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
#include "gfx/gfx_gol_window.h"

// Indent for the title bar text from the left side of bitmap or title bar emboss
#define GFX_GOL_WINDOW_INDENT  2

// Height of the title bar
#define GFX_GOL_WINDOW_TITLE_HEIGHT    35

/*********************************************************************
* Function: GFX_GOL_WINDOW  *GFX_GOL_Window_Create(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
*                              uint16_t bottom, uint16_t state, GFX_XCHAR *pText, void* pBitmap,
*                              GFX_GOL_OBJ_SCHEME *pScheme)
*
* Overview: creates the window
*
********************************************************************/
GFX_GOL_WINDOW *GFX_GOL_WindowCreate
(
    uint16_t    ID,
    uint16_t       left,
    uint16_t       top,
    uint16_t       right,
    uint16_t       bottom,
    uint16_t    state,
    void        *pBitmap,
    GFX_XCHAR       *pText,
    GFX_ALIGNMENT       alignment,
    GFX_GOL_OBJ_SCHEME  *pScheme
)
{
    GFX_GOL_WINDOW  *pW;

    pW = (GFX_GOL_WINDOW *)GFX_malloc(sizeof(GFX_GOL_WINDOW));
    if(pW == NULL)
        return (pW);

    //pW->hdr.instance = instance; //Device Instance set
    pW->hdr.ID = ID;
    pW->hdr.pNxtObj = NULL;
    pW->hdr.type = GFX_GOL_WINDOW_TYPE;
    pW->hdr.left = left;
    pW->hdr.top = top;
    pW->hdr.right = right;
    pW->hdr.bottom = bottom;
    pW->pBitmap = pBitmap;
    pW->pText = pText;
    pW->hdr.state = state;
    pW->hdr.DrawObj = GFX_GOL_WindowDraw;			// draw function
    pW->hdr.actionGet = GFX_GOL_WindowActionGet;   // message function
    pW->hdr.actionSet = NULL;		// default message function
    pW->hdr.FreeObj = NULL;				// free function
    pW->alignment = alignment;

    // Set the style scheme to be used
    pW->hdr.pGolScheme = pScheme;

    pW->textHeight = 0;
    if(pText != NULL)
    {
        pW->textHeight = GFX_TextStringHeightGet(pW->hdr.pGolScheme->pFont);
    }

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *)pW);

    return (pW);
}

/*********************************************************************
* Function: GFX_GOL_Window_TextSet(GFX_GOL_WINDOW *pW, GFX_XCHAR *pText)
*
* Overview: sets text
*
********************************************************************/
void GFX_GOL_WindowTextSet(GFX_GOL_WINDOW *pW, GFX_XCHAR *pText)
{
    pW->pText = pText;
    pW->textHeight = GFX_TextStringHeightGet(pW->hdr.pGolScheme->pFont);
}

/*********************************************************************
* Function: uint16_t WndTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
* Overview: translates the GOL message for the window
*
********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_WindowActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_WINDOW *pW;

    pW = (GFX_GOL_WINDOW *)pObj;

    // Evaluate if the message is for the window
    // Check if disabled first
    if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

        #ifdef USE_TOUCHSCREEN
    if(pMsg->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in the title bar area
        if
        (
            (pW->hdr.left < pMsg->param1) &&
            (pW->hdr.right > pMsg->param1) &&
            (pW->hdr.top < pMsg->param2) &&
            (pW->hdr.top + GFX_GOL_WINDOW_TITLE_HEIGHT + GFX_GOL_EMBOSS_SIZE > pMsg->param2)
        )
        {
            return (GFX_GOL_WINDOW_ACTION_TITLE);
        }

        // Check if it falls in the client area
        if
        (
            (pW->hdr.left + GFX_GOL_EMBOSS_SIZE < pMsg->param1) &&
            (pW->hdr.right - GFX_GOL_EMBOSS_SIZE > pMsg->param1) &&
            (pW->hdr.top + GFX_GOL_WINDOW_TITLE_HEIGHT + GFX_GOL_EMBOSS_SIZE < pMsg->param2) &&
            (pW->hdr.bottom - GFX_GOL_EMBOSS_SIZE > pMsg->param2)
        )
        {
            return (GFX_GOL_WINDOW_ACTION_CLIENT);
        }
    }

        #endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
* Function: uint16_t WindowDraw(void *pObj)
*
* Overview: draws window
*
********************************************************************/
GFX_STATUS GFX_GOL_WindowDraw(void *pObj)
{
    typedef enum
    {
        GFX_GOL_WINDOW_DRAW_IDLE,
        GFX_GOL_WINDOW_DRAW_HIDE,
        GFX_GOL_WINDOW_DRAW_TITLE_BAR,
        GFX_GOL_WINDOW_DRAW_TITLE_BAR_BITMAP,
        GFX_GOL_WINDOW_DRAW_SET_TITLE_BAR_TEXT,
        GFX_GOL_WINDOW_DRAW_TITLE_BAR_TEXT,
        GFX_GOL_WINDOW_DRAW_SET_CLIENT_AREA,
        GFX_GOL_WINDOW_DRAW_CLIENT_AREA,
    } GFX_GOL_WINDOW_DRAW_STATES;

    short temp;
    static GFX_STATUS index;
    GFX_GOL_WINDOW *pW;
    static GFX_GOL_WINDOW_DRAW_STATES state = GFX_GOL_WINDOW_DRAW_IDLE;

    pW = (GFX_GOL_WINDOW *)pObj;

    while(1)
    {
        switch(state)
        {

                case GFX_GOL_WINDOW_DRAW_IDLE:

                if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_HIDE_STATE))
                {
                    GFX_ColorSet(pW->hdr.pGolScheme->CommonBkColor);
					state = GFX_GOL_WINDOW_DRAW_HIDE;
					// no break; here so it falls through to GFX_GOL_WINDOW_DRAW_HIDE
                }
else
{
                if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DRAW_CLIENT_STATE))
                {
                    state = GFX_GOL_WINDOW_DRAW_SET_CLIENT_AREA;
                    break;
				} 
				else if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DRAW_TITLE_STATE))
				{
					state = GFX_GOL_WINDOW_DRAW_TITLE_BAR;
					break;
				}
                else
				{

                    return (GFX_STATUS_SUCCESS);
				}

}
            case GFX_GOL_WINDOW_DRAW_HIDE:
                index = GFX_RectangleFillDraw(pW->hdr.left, pW->hdr.top, pW->hdr.right, pW->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
		state = GFX_GOL_WINDOW_DRAW_IDLE;
                return (GFX_STATUS_SUCCESS);
				
			case GFX_GOL_WINDOW_DRAW_SET_CLIENT_AREA:
				GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
				GFX_GOL_PanelParameterSet
				(
                    
					pW->hdr.left,
					pW->hdr.top,
					pW->hdr.right,
					pW->hdr.bottom,
					0,
					pW->hdr.pGolScheme->CommonBkColor,
					pW->hdr.pGolScheme->EmbossLtColor,
					pW->hdr.pGolScheme->EmbossDkColor,
					NULL,
                                        GFX_FILL_STYLE_COLOR,
					GFX_GOL_EMBOSS_SIZE
				);

				state = GFX_GOL_WINDOW_DRAW_CLIENT_AREA;

			case GFX_GOL_WINDOW_DRAW_CLIENT_AREA:
				if(GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
					return (GFX_STATUS_FAILURE);

                if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DRAW_TITLE_STATE))
                {
					state = GFX_GOL_WINDOW_DRAW_TITLE_BAR;
					break;
				} else
				{
					state = GFX_GOL_WINDOW_DRAW_IDLE;
					return (GFX_STATUS_SUCCESS);
				}

            case GFX_GOL_WINDOW_DRAW_TITLE_BAR:
                if(!GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DISABLED_STATE))
                {
                    if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_FOCUSED_STATE))
                    {
                        GFX_ColorSet(pW->hdr.pGolScheme->Color1);
                    }
                    else
                    {
                        GFX_ColorSet(pW->hdr.pGolScheme->Color0);
                    }
                }
                else
                {
                    GFX_ColorSet(pW->hdr.pGolScheme->ColorDisabled);
                }

                index = GFX_RectangleFillDraw
                        (
                            
                            pW->hdr.left + GFX_GOL_EMBOSS_SIZE,
                            pW->hdr.top + GFX_GOL_EMBOSS_SIZE,
                            pW->hdr.right - GFX_GOL_EMBOSS_SIZE,
                            pW->hdr.top + GFX_GOL_EMBOSS_SIZE + GFX_GOL_WINDOW_TITLE_HEIGHT
                        );
                
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }

                state = GFX_GOL_WINDOW_DRAW_TITLE_BAR_BITMAP;

            case GFX_GOL_WINDOW_DRAW_TITLE_BAR_BITMAP:
                if(pW->pBitmap != NULL)
                {
                    index = GFX_ImageDraw
                            (
                                
                                pW->hdr.left + GFX_GOL_EMBOSS_SIZE,
                                pW->hdr.top + GFX_GOL_EMBOSS_SIZE + ((GFX_GOL_WINDOW_TITLE_HEIGHT - GFX_ImageHeightGet(pW->pBitmap)) >> 1),
                                pW->pBitmap
                                
                            );
                   
                    if(index == GFX_STATUS_FAILURE)
                    {
                         return (GFX_STATUS_FAILURE);
                    }
                }

                if(pW->pText != NULL)
                {
                    state = GFX_GOL_WINDOW_DRAW_SET_TITLE_BAR_TEXT;
                    break;		
				}
				else
				{
					state = GFX_GOL_WINDOW_DRAW_IDLE;
					return (GFX_STATUS_SUCCESS);
				}

			case GFX_GOL_WINDOW_DRAW_SET_TITLE_BAR_TEXT:
				GFX_FontSet(pW->hdr.pGolScheme->pFont);

				if(!GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_DISABLED_STATE))
				{
					if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_FOCUSED_STATE))
					{
						GFX_ColorSet(pW->hdr.pGolScheme->TextColor1);
					}
					else
					{
						GFX_ColorSet(pW->hdr.pGolScheme->TextColor0);
					}
				}
				else
				{
					GFX_ColorSet(pW->hdr.pGolScheme->TextColorDisabled);
				}

				temp = pW->hdr.left + GFX_GOL_EMBOSS_SIZE + GFX_GOL_WINDOW_INDENT;

				if(pW->pBitmap != NULL)
				{
					temp += GFX_ImageWidthGet(pW->pBitmap);
				}

				if(GFX_GOL_ObjectStateGet(pW, GFX_GOL_WINDOW_TITLECENTER_STATE))
				{
					temp = (temp + (pW->hdr.right - GFX_TextStringWidthGet(pW->pText, pW->hdr.pGolScheme->pFont))) >> 1;
				}

				GFX_LinePositionSet(temp, pW->hdr.top + GFX_GOL_EMBOSS_SIZE + ((GFX_GOL_WINDOW_TITLE_HEIGHT - pW->textHeight) >> 1));

				state = GFX_GOL_WINDOW_DRAW_TITLE_BAR_TEXT;

			case GFX_GOL_WINDOW_DRAW_TITLE_BAR_TEXT:

                if(GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), pW->pText, 0) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                
                state = GFX_GOL_WINDOW_DRAW_IDLE;
                return (GFX_STATUS_SUCCESS);
        }   //end of switch
    }       //end of while
}
