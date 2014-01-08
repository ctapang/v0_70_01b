/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_progress_bar.c

  Summary:
    This implements the progress bar object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    ProgressBar Object.
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


#include "gfx/gfx_gol_progress_bar.h"

/*********************************************************************
* Function: void GFX_GOL_ProgressBarWordToString(uint16_t value, GFX_XCHAR* buffer)
*
* Input: value  - value to be converted (from 0 - 100)
*        buffer - buffer receiving string (must be at least 5 bytes)
*
* Output: none
*
* Overview: converts short into string with % at the end
*
********************************************************************/
void GFX_GOL_ProgressBarWordToString(uint16_t value, GFX_XCHAR *buffer)
{
    uint16_t    result;
    uint8_t    pos;

    if(value > 99)
    {
        buffer[0] = '1';
        buffer[1] = '0';
        buffer[2] = '0';
        buffer[3] = '%';
        buffer[4] = 0;
        return;
    }

    pos = 0;
    result = value / 10;
    if(result)
        buffer[pos++] = result + '0';
    result = value - 10 * result;

    buffer[pos++] = result + '0';
    buffer[pos++] = '%';
    buffer[pos++] = 0;
}

/*********************************************************************
* Function: GFX_GOL_PROGRESSBAR  *GFX_GOL_ProgressBarCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
*                              uint16_t bottom, uint16_t state, uint16_t pos, uint16_t range,
*                              GFX_GOL_OBJ_SCHEME *pScheme)
*
* Overview: creates the progress bar
*
********************************************************************/
GFX_GOL_PROGRESSBAR *GFX_GOL_ProgressBarCreate
(
    uint16_t        ID,
    uint16_t       left,
    uint16_t       top,
    uint16_t       right,
    uint16_t       bottom,
    uint16_t       state,
    uint16_t        pos,
    uint16_t        range,
    GFX_GOL_OBJ_SCHEME  *pScheme
)
{
    GFX_GOL_PROGRESSBAR *pPb = NULL;

    pPb = (GFX_GOL_PROGRESSBAR *)GFX_malloc(sizeof(GFX_GOL_PROGRESSBAR));
    if(pPb == NULL)
        return (pPb);

    //pPb->hdr.instance   = instance; //Device Instance set
    pPb->hdr.ID         = ID;
    pPb->hdr.pNxtObj    = NULL;
    pPb->hdr.type       = GFX_GOL_PROGRESSBAR_TYPE;
    pPb->hdr.left       = left;
    pPb->hdr.top        = top;
    pPb->hdr.right      = right;
    pPb->hdr.bottom     = bottom;
    pPb->pos            = pos;
    pPb->range          = (range == 0) ? 100 : range;
    pPb->prevPos        = 0;
    pPb->hdr.state      = state;
    pPb->hdr.DrawObj    = GFX_GOL_ProgressBarDraw;   // draw function
    pPb->hdr.actionGet     = NULL;     // message function
    pPb->hdr.actionSet = NULL;  // default message function
    pPb->hdr.FreeObj    = NULL;		// free function

    // Set the style scheme to be used
    pPb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *)pScheme;

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *)pPb);

    return (pPb);
}

/*********************************************************************
* Function: void GFX_GOL_ProgressBar_PosSet(GFX_GOL_PROGRESSBAR *pPb, uint16_t position)
*
* Overview: sets the current position of the progress bar
*
********************************************************************/
void GFX_GOL_ProgressBarPositionSet(GFX_GOL_PROGRESSBAR *pPb, uint16_t position)
{
    if(pPb->range < position)
        position = pPb->range;

    pPb->pos = position;
}

/*********************************************************************
* Function: void GFX_GOL_ProgressBar_RangeSet(PROGRESSBAR *pPb, uint16_t range)
*
* Overview: sets the range of the progress bar
*
********************************************************************/
void GFX_GOL_ProgressBarRangeSet(GFX_GOL_PROGRESSBAR *pPb, uint16_t range)
{

    // range cannot be assigned a zero value
    if(range != 0)
        pPb->range = range;
    pPb->pos = range;
    pPb->prevPos = 0;
}

/*********************************************************************
* Function: uint16_t GFX_GOL_ProgressBarActionGet(GFX_GOL_PROGRESSBAR *pPb, GFX_GOL_MESSAGE *pMsg)
*
* Overview: translates the GOL message for the progress bar
*
********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_ProgressBarActionGet(void *pObject, GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_PROGRESSBAR *pPb = pObject;

    // Evaluate if the message is for the progress bar
    // Check if disabled first
    if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

        #ifdef USE_TOUCHSCREEN
    if(pMessage->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in the progress bar border
        if
        (
            (pPb->hdr.left < pMessage->param1) &&
            (pPb->hdr.right > pMessage->param1) &&
            (pPb->hdr.top < pMessage->param2) &&
            (pPb->hdr.bottom > pMessage->param2)
        )
        {
            return (GFX_GOL_PROGRESSBAR_ACTION_SELECTED);
        }
    }

        #endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
* Function: uint16_t GFX_GOL_ProgressBarDraw(void *pObj)
*
* Output: returns the status of the drawing
*		  0 - not complete
*         1 - done
*
* Overview: draws progress bar
*
********************************************************************/
GFX_STATUS GFX_GOL_ProgressBarDraw(void *pObject)
{
    typedef enum
    {
        REMOVE,
        BOX_DRAW,
        RUN_DRAW,
        BAR_DRAW_SET,
        BAR_DRAW,
        TEXT_DRAW1,
        TEXT_DRAW2,
        TEXT_DRAW3
    } GFX_GOL_PROGRESSBAR_DRAW_STATES;

    static GFX_GOL_PROGRESSBAR_DRAW_STATES state = REMOVE;
    static uint32_t x1;
    static uint32_t x2;
    static uint16_t  intLeft, intTop, intRight, intBottom;
    static GFX_XCHAR text[5] = {'0','0','%',0};
    GFX_GOL_PROGRESSBAR *pPb;

    pPb = (GFX_GOL_PROGRESSBAR *)pObject;

    while(1)
    {
   
        switch(state)
        {
            case RUN_DRAW:
                if(GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                state = BAR_DRAW_SET;
                break;

            case REMOVE:

                if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_HIDE_STATE))
                {
                    GFX_ColorSet(pPb->hdr.pGolScheme->CommonBkColor);
                    if(GFX_RectangleFillDraw(pPb->hdr.left, pPb->hdr.top, pPb->hdr.right, pPb->hdr.bottom)==GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);

                    return (1);
                }
                state = BOX_DRAW;
    
            case BOX_DRAW:
                if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_DRAW_STATE))
                {
                    GFX_GOL_PanelParameterSet
                    (   
                        pPb->hdr.left,
                        pPb->hdr.top,
                        pPb->hdr.right,
                        pPb->hdr.bottom,
                        0,
                        pPb->hdr.pGolScheme->Color0,
                        pPb->hdr.pGolScheme->EmbossDkColor,
                        pPb->hdr.pGolScheme->EmbossLtColor,
                        NULL,
                        GFX_FILL_STYLE_COLOR,
                        GFX_GOL_EMBOSS_SIZE
                    );
                    state = RUN_DRAW;
                    break;
                } 
                // else progress bar state = GFX_GOL_PROGRESSBAR_DRAW_BAR, refresh only the level
                state = BAR_DRAW_SET;
    
            case BAR_DRAW_SET:
            	if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_VERTICAL_STATE))
                {
    	            x1 = ((uint32_t) (pPb->range-pPb->prevPos)) * (pPb->hdr.bottom - pPb->hdr.top - (2 * GFX_GOL_EMBOSS_SIZE)) / pPb->range;
    	            x2 = ((uint32_t) (pPb->range-pPb->pos)) * (pPb->hdr.bottom - pPb->hdr.top - (2 * GFX_GOL_EMBOSS_SIZE)) / pPb->range;
    	            x1 += (pPb->hdr.top + GFX_GOL_EMBOSS_SIZE);
    	            x2 += (pPb->hdr.top + GFX_GOL_EMBOSS_SIZE);
    	        }
    	        else
    	        { 
    	            x1 = ((uint32_t) pPb->pos) * (pPb->hdr.right - pPb->hdr.left - (2 * GFX_GOL_EMBOSS_SIZE)) / pPb->range;
    	            x2 = ((uint32_t) pPb->prevPos) * (pPb->hdr.right - pPb->hdr.left - (2 * GFX_GOL_EMBOSS_SIZE)) / pPb->range;
    	            x1 += (pPb->hdr.left + GFX_GOL_EMBOSS_SIZE);
    	            x2 += (pPb->hdr.left + GFX_GOL_EMBOSS_SIZE);
             	}   

                if(pPb->prevPos > pPb->pos)
                {
    	            GFX_ColorSet(pPb->hdr.pGolScheme->Color0);
    	        	if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_VERTICAL_STATE))
                    {
                        intLeft   = pPb->hdr.left + GFX_GOL_EMBOSS_SIZE;
                        intTop    = x1;
                        intRight  = pPb->hdr.right - GFX_GOL_EMBOSS_SIZE;
                        intBottom = x2;
                    } 
                    else
                    {
                        intLeft   = x1; 
                        intTop    = pPb->hdr.top + GFX_GOL_EMBOSS_SIZE;
                        intRight  = x2;
                        intBottom = pPb->hdr.bottom - GFX_GOL_EMBOSS_SIZE;
                    }
                }
                else
                {
                    GFX_ColorSet(pPb->hdr.pGolScheme->Color1);
    	        	if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_VERTICAL_STATE))
        	        {
                        intLeft   = pPb->hdr.left + GFX_GOL_EMBOSS_SIZE;
                        intTop    = x2;
                        intRight  = pPb->hdr.right - GFX_GOL_EMBOSS_SIZE;
                        intBottom = x1;
    	    	    } 
                    else
                    {
                        intLeft   = x2; 
                        intTop    = pPb->hdr.top + GFX_GOL_EMBOSS_SIZE;
                        intRight  = x1;
                        intBottom = pPb->hdr.bottom - GFX_GOL_EMBOSS_SIZE;
        	        }     
                }
                state = BAR_DRAW;

            case BAR_DRAW:
   
                if(GFX_RectangleFillDraw(intLeft, intTop, intRight, intBottom)==GFX_STATUS_FAILURE)
   	                return (GFX_STATUS_FAILURE);
    
                if (GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_NOPROGRESS_STATE) || (pPb->hdr.pGolScheme->pFont == NULL))
                {
                    state = REMOVE;
                    pPb->prevPos = pPb->pos;
                    return (GFX_STATUS_SUCCESS);
                }

           	    if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_VERTICAL_STATE))
       	        {
    	            GFX_ColorSet(pPb->hdr.pGolScheme->Color0);
                    intLeft   = pPb->hdr.left + GFX_GOL_EMBOSS_SIZE;
                    intTop    = (pPb->hdr.top + pPb->hdr.bottom - GFX_TextStringHeightGet(pPb->hdr.pGolScheme->pFont)) >> 1;
    	            intRight  = pPb->hdr.right - GFX_GOL_EMBOSS_SIZE;
    	            intBottom = x2;
    			} 
    			else
    			{
    	            GFX_ColorSet(pPb->hdr.pGolScheme->Color1);
                    intLeft   = (pPb->hdr.left + pPb->hdr.right - GFX_TextStringWidthGet(text, pPb->hdr.pGolScheme->pFont)) >> 1;
    	            intTop    = pPb->hdr.top + GFX_GOL_EMBOSS_SIZE;
    	            intRight  = x1;
    	            intBottom = pPb->hdr.bottom - GFX_GOL_EMBOSS_SIZE;
    			}	
               
                state = TEXT_DRAW1;
    
            case TEXT_DRAW1:
                if(intLeft < intRight) 
                if(GFX_RectangleFillDraw(intLeft, intTop, intRight, intBottom)==GFX_STATUS_FAILURE)
   	                return (GFX_STATUS_FAILURE);

            	if(GFX_GOL_ObjectStateGet(pPb, GFX_GOL_PROGRESSBAR_VERTICAL_STATE))
       	        {
    	            GFX_ColorSet(pPb->hdr.pGolScheme->Color1);
                    intLeft   = pPb->hdr.left + GFX_GOL_EMBOSS_SIZE;
                    intTop    = x2;
    	            intRight  = pPb->hdr.right - GFX_GOL_EMBOSS_SIZE;
    	            intBottom = (pPb->hdr.top + pPb->hdr.bottom + GFX_TextStringHeightGet(pPb->hdr.pGolScheme->pFont)) >> 1;
    			}
    			else 
    			{
    	            GFX_ColorSet(pPb->hdr.pGolScheme->Color0);
                    intLeft   = x1;
    	            intTop    = pPb->hdr.top + GFX_GOL_EMBOSS_SIZE;
    	            intRight  = (pPb->hdr.left + pPb->hdr.right + GFX_TextStringWidthGet(text, pPb->hdr.pGolScheme->pFont)) >> 1;
    	            intBottom = pPb->hdr.bottom - GFX_GOL_EMBOSS_SIZE;
    			}	 
                state = TEXT_DRAW2;
    
            case TEXT_DRAW2:
               if(intLeft < intRight)
                if(GFX_RectangleFillDraw(intLeft, intTop, intRight, intBottom)==GFX_STATUS_FAILURE)
   	                return (GFX_STATUS_FAILURE);

                GFX_GOL_ProgressBarWordToString((uint32_t) pPb->pos * 100 / pPb->range, text);
                GFX_ColorSet(pPb->hdr.pGolScheme->TextColor0);
    
                GFX_LinePositionSet
                (   
                    (pPb->hdr.left + pPb->hdr.right - GFX_TextStringWidthGet(text, pPb->hdr.pGolScheme->pFont)) >> 1,
                    (pPb->hdr.top + pPb->hdr.bottom - GFX_TextStringHeightGet(pPb->hdr.pGolScheme->pFont)) >> 1
                );
    
                GFX_FontSet(pPb->hdr.pGolScheme->pFont);
                state = TEXT_DRAW3;
    
            case TEXT_DRAW3:
                if(GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), text, 0) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
    
                pPb->prevPos = pPb->pos;
                state = REMOVE;
                return (GFX_STATUS_SUCCESS);
        } // end of switch()
    } // end of while(1)
}
