/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_picture.c

  Summary:
    This implements the meter object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Picture Object.
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

#include "gfx/gfx_gol_picture.h"
    
/*********************************************************************
* Function: PICTURE  *PictCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
*                              uint16_t bottom, uint16_t state, char scale, void *pImage,
*                              GFX_GOL_OBJ_SCHEME *pScheme)
*
* Overview: creates the picture control
*
********************************************************************/
GFX_GOL_PICTURECONTROL *GFX_GOL_PictureControlCreate
(
    uint16_t        ID,
    uint16_t       left,
    uint16_t       top,
    uint16_t       right,
    uint16_t       bottom,
    uint16_t        state,
    int8_t        scale,
    GFX_RESOURCE_HDR        *pBitmap,
    GFX_GOL_OBJ_SCHEME  *pScheme
)
{
    GFX_GOL_PICTURECONTROL *pPict = NULL;

    pPict = (GFX_GOL_PICTURECONTROL *)GFX_malloc(sizeof(GFX_GOL_PICTURECONTROL));
    if(pPict == NULL)
        return (pPict);

    //pPict->hdr.instance = instance;
    pPict->hdr.ID = ID;
    pPict->hdr.pNxtObj = NULL;
    pPict->hdr.type = GFX_GOL_PICTURECONTROL_TYPE;
    pPict->hdr.left = left;
    pPict->hdr.top = top;
    pPict->hdr.right = right;
    pPict->hdr.bottom = bottom;
    pPict->pImage = pBitmap;
    pPict->hdr.state = state;
    pPict->scaleFactor = scale;
    pPict->count = 0;                             //Hard coded for now
    pPict->hdr.DrawObj = GFX_GOL_PictureControlDraw;	          // draw function
    pPict->hdr.actionGet = GFX_GOL_PictureControlActionGet;         // message function
    pPict->hdr.actionSet = NULL;		  // default message function
    pPict->hdr.FreeObj = NULL;		          // free function
    pPict->delay = 0;

    pPict->partial.width=0;                       //This voids the partial image

    // Set the style scheme to be used
    pPict->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *)pScheme;

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *)pPict);

    return (pPict);
}

/*********************************************************************
 * Function: GFX_GOL_Picture_StreamSet(BUTTON *button, XCHAR *pText)
 *
 *
 * Notes: Sets the text used in the button.
 *
 ********************************************************************/
bool GFX_GOL_PictureStreamSet(GFX_GOL_PICTURECONTROL *picture, uint32_t* pStream, uint8_t count, uint8_t delayMs)
{
    if(picture->count != 0)
        return false;

    picture->count = count;
    picture->delay = delayMs;
    picture->stream = pStream;
    GFX_GOL_ObjectStateSet(picture, GFX_GOL_PICTURECONTROL_STREAM_STATE|GFX_GOL_PICTURECONTROL_DRAW_STATE);
    return true;
}

/*********************************************************************
* Function: uint16_t PictTranslateMsg(void *pObj, GFX_OBJ_MESSAGE *pMsg)
*
* Overview: translates the GOL message for the picture control
*
********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_PictureControlActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_PICTURECONTROL *pPict;

    pPict = (GFX_GOL_PICTURECONTROL *)pObj;

    // Evaluate if the message is for the picture
    // Check if disabled first
    if(GFX_GOL_ObjectStateGet(pPict, GFX_GOL_PICTURECONTROL_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

        #ifdef USE_TOUCHSCREEN
    if(pMsg->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in the picture area
        if
        (
            (pPict->hdr.left < pMsg->param1) &&
            (pPict->hdr.right > pMsg->param1) &&
            (pPict->hdr.top < pMsg->param2) &&
            (pPict->hdr.bottom > pMsg->param2)
        )
        {
            return (GFX_GOL_PICTURECONTROL_ACTION_SELECTED);
        }
    }

        #endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
* Function: uint16_t GFX_GOL_PictureDraw(void *pObj)
*
* Output: returns the status of the drawing
*		  0 - not completed
*         1 - done
*
* Overview: draws picture
*
********************************************************************/
GFX_STATUS GFX_GOL_PictureControlDraw(void *pObj)
{
    typedef enum
    {
        REMOVE,
        DRAW_IMAGE,
        DRAW_BACKGROUND1,
        DRAW_BACKGROUND2,
        DRAW_BACKGROUND3,
        DRAW_BACKGROUND4,
        DRAW_FRAME,
    } GFX_GOL_PICTURE_DRAW_STATES;

    static GFX_GOL_PICTURE_DRAW_STATES state = REMOVE;
    static uint16_t posleft;
    static uint16_t postop;
    static uint16_t posright;
    static uint16_t posbottom;
    static GFX_STATUS index = GFX_STATUS_FAILURE;
    GFX_GOL_PICTURECONTROL *pPict;


    pPict = (GFX_GOL_PICTURECONTROL *)pObj;

    switch(state)
    {
        case REMOVE:
            if(GFX_GOL_ObjectStateGet(pPict, GFX_GOL_PICTURECONTROL_HIDE_STATE))
            {
                GFX_ColorSet(pPict->hdr.pGolScheme->CommonBkColor);
                if(GFX_RectangleFillDraw(pPict->hdr.left, pPict->hdr.top, pPict->hdr.right, pPict->hdr.bottom) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                return (GFX_STATUS_SUCCESS);
            }

            posleft = (pPict->hdr.left + 1 + pPict->hdr.right - pPict->scaleFactor * GFX_ImageWidthGet(pPict->pImage)) >> 1;
            postop = (pPict->hdr.top + 1 + pPict->hdr.bottom - pPict->scaleFactor * GFX_ImageHeightGet(pPict->pImage)) >> 1;
            posright = (pPict->hdr.right + pPict->hdr.left + pPict->scaleFactor * GFX_ImageWidthGet(pPict->pImage)) >> 1;
            posbottom = (pPict->hdr.bottom + pPict->hdr.top + pPict->scaleFactor * GFX_ImageHeightGet(pPict->pImage)) >> 1;

            GFX_ImageStretchSet(pPict->scaleFactor);

            state = DRAW_IMAGE;

        case DRAW_IMAGE:

            if(pPict->pImage != NULL)
            {
                if(GFX_ImagePartialDraw(posleft, postop, pPict->partial.xoffset,pPict->partial.yoffset,pPict->partial.width,pPict->partial.height, pPict->pImage)==GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
            }

            if(GFX_GOL_ObjectStateGet(pPict, GFX_GOL_PICTURECONTROL_STREAM_STATE))
            {

                    if(pPict->count > 0)
                    {
                        SYS_TMR_DelayMS(pPict->delay);
                        pPict->count -= 1;
                        pPict->pImage = (GFX_RESOURCE_HDR*)*pPict->stream++; //Index to next bitmap in stream
                        return(GFX_STATUS_FAILURE);
                    }
            }

             state = DRAW_BACKGROUND1;

        case DRAW_BACKGROUND1:
             GFX_ColorSet(pPict->hdr.pGolScheme->CommonBkColor);

            if(GFX_RectangleFillDraw(pPict->hdr.left + 1, pPict->hdr.top + 1, pPict->hdr.right - 1, postop - 1) == GFX_STATUS_FAILURE)
                return (GFX_STATUS_FAILURE);
            state = DRAW_BACKGROUND2;

        case DRAW_BACKGROUND2:
            if(GFX_RectangleFillDraw(pPict->hdr.left + 1, posbottom, pPict->hdr.right - 1, pPict->hdr.bottom - 1) == GFX_STATUS_FAILURE)
                return (GFX_STATUS_FAILURE);
            state = DRAW_BACKGROUND3;

        case DRAW_BACKGROUND3:
            if(GFX_RectangleFillDraw(pPict->hdr.left + 1, postop, posleft - 1, posbottom) == GFX_STATUS_FAILURE)
                return (GFX_STATUS_FAILURE);
            state = DRAW_BACKGROUND4;

        case DRAW_BACKGROUND4:
            index = GFX_RectangleFillDraw(posright, postop, pPict->hdr.right - 1, posbottom);
            if(index == GFX_STATUS_FAILURE)
            {
                return (GFX_STATUS_FAILURE);
            }
            state = DRAW_FRAME;

        case DRAW_FRAME:
            if(GFX_GOL_ObjectStateGet(pPict, GFX_GOL_PICTURECONTROL_FRAME_STATE))
            {
                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
                GFX_ColorSet(pPict->hdr.pGolScheme->TextColor0);
                index = GFX_RectangleDraw(pPict->hdr.left, pPict->hdr.top, pPict->hdr.right, pPict->hdr.bottom);
                if(index == GFX_STATUS_FAILURE)
                {
                     return (GFX_STATUS_FAILURE);
                }
            }
            state = REMOVE;
            return (GFX_STATUS_SUCCESS);
    }

    return (GFX_STATUS_SUCCESS);
}
