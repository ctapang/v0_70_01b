/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_meter.c

  Summary:
    This implements the meter object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Meter Object.
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

#include "gfx/gfx_gol_meter.h"
#include "gfx/gfx_gol_font_default.h"

#include <math.h>
#include <stdio.h>

/* Internal Used Constants */
#define RADIAN      1144            // Radian definition. Equivalent to sine(1) * 2^16.
#define PIIOVER2    102944          // The constant Pii divided by two (pii/2).

/* Internal Used Constants */
#define ARC225_DEGREE 225
#define ARC180_DEGREE 180 // defines one arc1 limit (used to determine colors)
#define ARC135_DEGREE 135 // defines one arc2 limit (used to determine colors)
#define ARC090_DEGREE 90  // defines one arc3 limit (used to determine colors)
#define ARC045_DEGREE 45  // defines one arc4 limit (used to determine colors)
#define ARC000_DEGREE 0   // defines one arc5 limit (used to determine colors)

/* Internal Functions */
// used to calculate the meter dimensions
void    MtrCalcDimensions(GFX_GOL_METER *pMeter);
void GFX_GOL_MeterValueToCoordinatePosition(
                                GFX_GOL_METER *pMeter,
                                int16_t angle,
                                uint16_t radius,
                                int16_t *pX,
                                int16_t *pY);
void GFX_GOL_MeterStartEndGet(
                                GFX_GOL_METER *pMeter,
                                int16_t *start,
                                int16_t *end);
int16_t GFX_GOL_MeterAngleGet(
                                GFX_GOL_METER *pMeter,
                                int16_t start,
                                int16_t end);

typedef union
{
    struct
    {
        int8_t int8Data[4];
    };

    struct
    {
        int16_t int16Data[2];
    };

    int32_t int32Data;
}METER_INT32_UNION;

#define GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
#define GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT  4

/***************************************************************************
 * Overview: This is a Meter compile time option to define how many degrees
 *           per scale, computed per octant
 *           Example: for 5 division per octant 45/5 = 9.
 *                    So every 9 degrees a scale is drawn
 *                    for a 5 scale division per octant.
 ***************************************************************************/
#define MTR_BUILD_OPTION_DEGREECOUNT 9

/***************************************************************************
 * Overview: This is a Meter compile time option to define the factor
 *           that the meter widget will divide minValue, maxValue
 ***************************************************************************/
#define MTR_BUILD_OPTION_RESOLUTION  10

/* Internal Functions */
void MtrCalcDimensions(GFX_GOL_METER *pMtr); // used to calculate the meter dimensions

// which is dependent on meter type

/*********************************************************************
 * Function: METER  *MtrCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *							  uint16_t bottom, uint16_t state, uint16_t value,
 *							  uint16_t minValue, uint16_t maxValue, GFX_XCHAR *pText,
 *							  GFX_GOL_OBJ_SCHEME *pScheme)
 *
 *
 * Notes: Creates a METER object and adds it to the current active list.
 *        If the creation is successful, the pointer to the created Object
 *        is returned. If not successful, NULL is returned.
 *
 ********************************************************************/
GFX_GOL_METER *GFX_GOL_MeterCreate
(
 uint16_t ID,
 uint16_t left,
 uint16_t top,
 uint16_t right,
 uint16_t bottom,
 uint16_t state,
 GFX_GOL_METER_DRAW_TYPE type,
 int16_t value,
 int16_t minValue,
 int16_t maxValue,
 GFX_RESOURCE_HDR *pTitleFont,
 GFX_RESOURCE_HDR *pValueFont,
 GFX_XCHAR *pText,
 GFX_GOL_OBJ_SCHEME *pScheme
 )
{
    GFX_GOL_METER *pMtr = NULL;

    pMtr = (GFX_GOL_METER *) GFX_malloc(sizeof (GFX_GOL_METER));
    if (pMtr == NULL)
        return (NULL);

    //pMtr->hdr.instance = instance;
    pMtr->hdr.ID = ID; // unique id assigned for referencing
    pMtr->hdr.pNxtObj = NULL; // initialize pointer to NULL
    pMtr->hdr.type = GFX_GOL_METER_TYPE; // set object type
    pMtr->hdr.left = left; // left,top coordinate
    pMtr->hdr.top = top; //
    pMtr->hdr.right = right; // right,bottom coordinate
    pMtr->hdr.bottom = bottom; //
    pMtr->minValue = minValue;
    pMtr->maxValue = maxValue;
    pMtr->value = value;
    pMtr->hdr.state = state; // state
    pMtr->pText = pText;
    pMtr->hdr.DrawObj = GFX_GOL_MeterDraw; // draw function
    pMtr->hdr.actionGet = GFX_GOL_MeterActionGet; // message function
    pMtr->hdr.actionSet = GFX_GOL_MeterActionSet; // default message function
    pMtr->hdr.FreeObj = NULL; // free function

    pMtr->type = type;

    // set the default scale colors
    GFX_GOL_MeterScaleColorsSet(pMtr, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF);

    // Set the color scheme to be used
    pMtr->hdr.pGolScheme = pScheme;

    // Set the Title Font to be used
    pMtr->pTitleFont = pTitleFont;

    // Set the Value Font to be used
    pMtr->pValueFont = pValueFont;

    // calculate dimensions of the meter	
    MtrCalcDimensions(pMtr);

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pMtr);

    return (pMtr);
}

/*********************************************************************
 * Function: MtrCalcDimensions(void)
 *
 * Notes: Calculates the dimension of the meter. Dependent on the
 *		 meter type set.
 *
 ********************************************************************/
void MtrCalcDimensions(GFX_GOL_METER *pMtr)
{
    uint16_t tempHeight, tempWidth;
    uint16_t left, top, right, bottom;
    GFX_XCHAR tempChar[2] = {'8', 0};

    left = pMtr->hdr.left;
    right = pMtr->hdr.right;
    top = pMtr->hdr.top;
    bottom = pMtr->hdr.bottom;

    // get the text width reference. This is used to scale the meter
    if (pMtr->pText != NULL)
    {
        tempHeight = (GFX_GOL_EMBOSS_SIZE << 1) + GFX_TextStringHeightGet(pMtr->hdr.pGolScheme->pFont);
    }
    else
    {
        tempHeight = (GFX_GOL_EMBOSS_SIZE << 1);
    }

    tempWidth = (GFX_GOL_EMBOSS_SIZE << 1) + (GFX_TextStringWidthGet(tempChar, pMtr->hdr.pGolScheme->pFont) * GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT);

    // Meter size is dependent on the width or height.
    // The radius is also adjusted to add space for the scales
#if (METER_TYPE == GFX_GOL_METER_WHOLE_TYPE)

    // choose the radius
    if ((right - left - tempWidth) > (bottom - top - tempHeight - GFX_TextStringHeightGet(pMtr->pTitleFont)))
    {
        pMtr->radius = ((bottom - top - tempHeight - GFX_TextStringHeightGet(pMtr->pTitleFont)) >> 1) - ((tempHeight + bottom - top) >> 3);
    }
    else
        pMtr->radius = ((right - left) >> 1) - (tempWidth + ((right - left) >> 3));

    // center the meter on the given dimensions
    pMtr->xCenter = (left + right) >> 1;
    pMtr->yCenter = ((bottom + top) >> 1) - (tempHeight >> 1);

#elif (METER_TYPE == GFX_GOL_METER_HALF_TYPE)

    // choose the radius
    if ((right - left) >> 1 > (bottom - top))
    {
        pMtr->radius = (bottom - top) - ((tempHeight << 1) + ((bottom - top) >> 3));
        pMtr->yCenter = ((bottom + top) >> 1) + ((pMtr->radius + ((bottom - top) >> 3)) >> 1);
    }
    else
    {
        pMtr->radius = ((right - left) >> 1) - (tempWidth + ((right - left) >> 3));
        pMtr->yCenter = ((bottom + top) >> 1) + ((pMtr->radius + ((right - left) >> 3)) >> 1);
    }

    // center the meter on the given dimensions
    pMtr->xCenter = (left + right) >> 1;

#elif (METER_TYPE == GFX_GOL_METER_QUARTER_TYPE)

    // choose the radius
    if
        (
         (right - left - tempWidth) >
         (bottom - top - (GFX_TextStringHeightGet(pMtr->pTitleFont) + GFX_TextStringHeightGet(pMtr->hdr.pGolScheme->pFont))) -
         (GFX_GOL_EMBOSS_SIZE << 1)
         )
    {
        pMtr->radius = bottom - top - (GFX_TextStringHeightGet(pMtr->pTitleFont) + GFX_TextStringHeightGet(pMtr->hdr.pGolScheme->pFont) + (GFX_GOL_EMBOSS_SIZE << 1));
    }
    else
    {
        pMtr->radius = right -
                left -
                (GFX_TextStringWidthGet(tempChar, pMtr->hdr.pGolScheme->pFont) * (GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT + 1)) -
                GFX_GOL_EMBOSS_SIZE;
    }

    pMtr->radius -= (((pMtr->radius) >> 2) + GFX_GOL_EMBOSS_SIZE);

    // center the meter on the given dimensions
    pMtr->xCenter = ((left + right) >> 1) - ((pMtr->radius + tempWidth + (pMtr->radius >> 2)) >> 1);
    pMtr->yCenter = ((top + bottom) >> 1) + ((pMtr->radius + (pMtr->radius >> 2)) >> 1);
#endif

}

/*********************************************************************
 * Function: GFX_GOL_MeterValueSet(METER *pMtr, uint16_t newVal)
 *
 * Notes: Sets the value of the meter to newVal. If newVal is less
 *		 than 0, 0 is assigned. If newVal is greater than range,
 *		 range is assigned.
 *
 ********************************************************************/
void GFX_GOL_MeterValueSet(GFX_GOL_METER *pObject, int16_t value)
{

    GFX_GOL_METER *pMtr;

    pMtr = (GFX_GOL_METER *) pObject;

    if ((value < 0) || (value < pMtr->minValue))
    {
        pMtr->value = pMtr->minValue;
        return;
    }

    if (value > pMtr->maxValue)
    {
        pMtr->value = pMtr->maxValue;
        return;
    }

    pMtr->value = value;
}

/*********************************************************************
 * Function: GFX_GOL_MeterActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 * Notes: This the default operation to change the state of the meter.
 *		 Called inside GFX_GOL_Message() when GFX_GOL_MessageCallback() returns a 1.
 *
 ********************************************************************/
void GFX_GOL_MeterActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg,void *pObject,GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_METER *pMtr;

    pMtr = (GFX_GOL_METER *) pObject;

    if (translatedMsg == GFX_GOL_METER_ACTION_SET)
    {
        GFX_GOL_MeterValueSet(pMtr, pMessage->param2); // set the value
        GFX_GOL_ObjectStateSet(pMtr, GFX_GOL_METER_UPDATE_DRAW_STATE); // update the meter
    }
}

/*********************************************************************
 * Function: uint16_t MtrTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Notes: Evaluates the message if the object will be affected by the
 *		 message or not.
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_MeterActionGet(void *pObject,GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_METER *pMtr;

    pMtr = (GFX_GOL_METER *) pObject;

    // Evaluate if the message is for the meter
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_DISABLED_STATE))
        return (GFX_GOL_METER_ACTION_SET);

    if (pMessage->type == TYPE_SYSTEM)
    {
        if (pMessage->param1 == pMtr->hdr.ID)
        {
            if (pMessage->uiEvent == EVENT_SET)
            {
                return (GFX_GOL_METER_ACTION_SET);
            }
        }
    }

    return (GFX_GOL_METER_ACTION_SET);
}

void GFX_GOL_MeterScaleColorsSet(
                                GFX_GOL_METER *pObject,
                                GFX_COLOR color1,
                                GFX_COLOR color2,
                                GFX_COLOR color3,
                                GFX_COLOR color4,
                                GFX_COLOR color5,
                                GFX_COLOR color6)
{

pObject->color1 = color1;
pObject->color2 = color2;
pObject->color3 = color3;
pObject->color4 = color4;
pObject->color5 = color5;
pObject->color6 = color6;


}


// *****************************************************************************
/*  Function:
    void GFX_GOL_MeterStartEndGet(
                                GFX_GOL_METER *pMeter,
                                int16_t *pStart,
                                int16_t *pEnd)

    Summary:
        This function calculates the start and end angles of the
        meter.

    Description:
        This function calculates the start and end angles of the
        meter. This is a internal function of the object. This
        function is intended to help the object calculate the
        start and end angles of the scales of the object.

*/
// *****************************************************************************
void __attribute__ ((always_inline)) GFX_GOL_MeterStartEndGet(
                                GFX_GOL_METER *pMeter,
                                int16_t *pStart,
                                int16_t *pEnd)
{
    switch(pMeter->type)
    {
        case GFX_GOL_METER_QUARTER_TYPE:
            *pStart = 0;
            *pEnd   = 90;
            break;
        case GFX_GOL_METER_HALF_TYPE:
            *pStart = 0;
            *pEnd   = 180;
            break;
        case GFX_GOL_METER_WHOLE_TYPE:
        default:
            *pStart = -45;
            *pEnd   = 225;
            break;
    }
}

// *****************************************************************************
/*  Function:
    void GFX_GOL_MeterAngleGet(
                                GFX_GOL_METER *pMeter,
                                int16_t start,
                                int16_t end)

    Summary:
        This function calculates the angle based on the current
        meter value and its corresponding start and end angles.

    Description:
        This function calculates the angle based on the current
        meter value and its corresponding start and end angles.
        This is a internal function of the object. This
        function is intended to help the object calculate the
        start and end angles of the scales of the object.

*/
// *****************************************************************************
int16_t __attribute__ ((always_inline)) GFX_GOL_MeterAngleGet(
                                GFX_GOL_METER *pMeter,
                                int16_t start,
                                int16_t end)
{
    METER_INT32_UNION   dTemp;

    dTemp.int32Data = 0;
    dTemp.int16Data[1] = pMeter->value - pMeter->minValue;
    dTemp.int32Data /= (pMeter->maxValue - pMeter->minValue);
    dTemp.int32Data *= (end - start);

    return (end - (dTemp.int16Data[1]));

}

// *****************************************************************************
/*  Function:
    void GFX_GOL_MeterValueToCoordinatePosition(
                                GFX_GOL_METER *pMeter,
                                int16_t angle,
                                uint16_t radius,
                                int16_t *pX,
                                int16_t *pY)

    Summary:
        This function calculates the pixel position of a segment
        from the center of a cicle with the given radius.

    Description:
        This function calculates the pixel position of a segment
        from the center of a cicle with the given radius.
        This is an internal function to the object.

*/
// *****************************************************************************
void __attribute__ ((always_inline)) GFX_GOL_MeterValueToCoordinatePosition(
                                GFX_GOL_METER *pMeter,
                                int16_t angle,
                                uint16_t radius,
                                int16_t *pX,
                                int16_t *pY)
{
    // given the angle, use sine and cosine values to calculate the
    // pixel position of the point. This is used to calculate the
    // line for the needle as well as the positions of the scales
    // of the meter.
    // Look up table is used in sine and cosine functions

    *pX = ( (int32_t)GFX_CosineGet(angle) * radius) >> 8;
    *pY = (((int32_t)GFX_SineGet(angle)   * radius) >> 8) * -1;

    *pX += pMeter->xCenter;
    *pY += pMeter->yCenter;

}

/*********************************************************************
 * Function: uint16_t GFX_GOL_MeterDraw(void *pObj)
 *
 * Notes: This is the state machine to draw the meter.
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_MeterDraw(void *pObject)
{

    typedef enum
    {
        IDLE,
        FRAME_DRAW,
        NEEDLE_DRAW,
        NEEDLE_ERASE,
        TEXT_DRAW,
        TEXT_DRAW_RUN,
        ARC_DRAW_SETUP,
        ARC_DRAW,
        SCALE_COMPUTE,
        SCALE_LABEL_DRAW,
        SCALE_DRAW,
#ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
        VALUE_ERASE,
        VALUE_DRAW,
        VALUE_DRAW_RUN,
#endif
    } GFX_GOL_METER_DRAW_STATES;

    static GFX_GOL_METER_DRAW_STATES state = IDLE;
    static int16_t x1, y1, x2, y2, rad1, rad2;
    static int16_t temp, j, i, angle;
    static GFX_XCHAR strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT + 1]; // add one more space here for the NULL character
    #ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
    static GFX_XCHAR tempXchar[2] = {'8', 0}; // NULL is pre-defined here
    #endif
    static float radian;
    static METER_INT32_UNION dTemp;
    GFX_GOL_METER *pMtr;
    static int16_t degreeStart, degreeEnd;
   
    pMtr = (GFX_GOL_METER *) pObject;

    while (1)
    {
        switch (state)
        {
                // location of this case is strategic so the partial redraw of the Meter will be faster
            case FRAME_DRAW:
                if (GFX_GOL_PanelDraw()==GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = TEXT_DRAW;
                break;

            case IDLE:

                /* These selects the parameters of the meter
                   that are dependent on the shape.
                */
                GFX_GOL_MeterStartEndGet(pMtr, &degreeStart, &degreeEnd);

                if (GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_HIDE_STATE))
                { // Hide the meter (remove from screen)
                    GFX_ColorSet(pMtr->hdr.pGolScheme->CommonBkColor);
                    if (GFX_RectangleFillDraw(pMtr->hdr.left, pMtr->hdr.top, pMtr->hdr.right, pMtr->hdr.bottom) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                    return (GFX_STATUS_SUCCESS);
                }

                // Check if we need to draw the whole object
                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
                if (GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_DRAW_STATE))
                {
                    // set parameters to draw the frame
                    GFX_GOL_PanelParameterSet
                            (                            
                             pMtr->hdr.left, pMtr->hdr.top, pMtr->hdr.right, pMtr->hdr.bottom, 0, pMtr->hdr.pGolScheme->Color0,
                             pMtr->hdr.pGolScheme->EmbossLtColor, pMtr->hdr.pGolScheme->EmbossDkColor, NULL,
                            GFX_FILL_STYLE_COLOR,
                            GFX_GOL_EMBOSS_SIZE - 1
                             );
                    state = FRAME_DRAW;
                    break;
                }
                else
                {
                    state = NEEDLE_ERASE;
                    break;
                }

            case TEXT_DRAW:

                // draw the meter title
                GFX_ColorSet(pMtr->hdr.pGolScheme->TextColor1);
                GFX_FontSet(pMtr->pTitleFont);

                temp = GFX_TextStringWidthGet(pMtr->pText, pMtr->pTitleFont);

                // set the start location of the meter title
                if(pMtr->type == GFX_GOL_METER_WHOLE_TYPE)
                #ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
                GFX_LinePositionSet(pMtr->xCenter - (temp >> 1), pMtr->yCenter + pMtr->radius + GFX_TextStringHeightGet(pMtr->pValueFont));
                #else
                GFX_LinePositionSet(pMtr->xCenter - (temp >> 1), pMtr->yCenter + pMtr->radius + GFX_TextStringHeightGet(pMtr->hdr.pGolScheme->pFont));
                #endif
                else if (pMtr->type == GFX_GOL_METER_HALF_TYPE)
                GFX_LinePositionSet(pMtr->xCenter - (temp >> 1), pMtr->yCenter + 3);
                else
                {
                GFX_LinePositionSet
                        (                         
                         ((pMtr->hdr.right + pMtr->hdr.left) >> 1) - (temp >> 1), pMtr->hdr.bottom - GFX_GOL_EMBOSS_SIZE - GFX_TextStringHeightGet
                         (pMtr->pTitleFont)
                         );
                }
                state = TEXT_DRAW_RUN;

            case TEXT_DRAW_RUN:
                // render the title of the meter
                if (GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), pMtr->pText, 0) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                state = ARC_DRAW_SETUP;

                //case ARC0_DRAW:
            case ARC_DRAW_SETUP:

                // check if we need to draw the arcs
                if (!GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_RING_STATE))
                {

                    // if meter is not RING type, for scale label colors use
                    // the three colors (normal, critical and danger)
                    i = degreeEnd;
                    state = SCALE_COMPUTE;
                    break;
                }
                else
                {

                    // set the arc radii: x1 smaller radius and x2 as the larger radius
                    x1 = pMtr->radius + 2;
                    x2 = pMtr->radius + (pMtr->radius >> 2) + 2;
                   
                    if(pMtr->type == GFX_GOL_METER_HALF_TYPE)
                    temp = 4;
                    else if(pMtr->type == GFX_GOL_METER_QUARTER_TYPE)
                    temp = 3;
                    else // if(pMtr->type == GFX_GOL_METER_WHOLE_TYPE)
                    temp = 6;
                    state = ARC_DRAW;
                }

            case ARC_DRAW:

                // draw the arcs
                while (temp)
                {
                    // decide which arc will be drawn
                    switch (temp)
                    {
                        case 6:
                            GFX_ColorSet(pMtr->color1);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x20) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        case 5:
                            GFX_ColorSet(pMtr->color2);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x40) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        case 4:
                            GFX_ColorSet(pMtr->color3);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x80) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        case 3:
                            GFX_ColorSet(pMtr->color4);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x01) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        case 2:
                            GFX_ColorSet(pMtr->color5);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x02) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        case 1:
                            GFX_ColorSet(pMtr->color6);
                            if (GFX_ArcDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xCenter, pMtr->yCenter, x1, x2, 0x04) == GFX_STATUS_FAILURE)
                                return (GFX_STATUS_FAILURE);
                            break;

                        default:
                            break;
                    }
                    temp--;
                }

                // set the color for the scale labels
                GFX_ColorSet(pMtr->hdr.pGolScheme->Color1);
                i = degreeEnd;
                state = SCALE_COMPUTE;

            case SCALE_COMPUTE:

                if (i >= degreeStart)
                {
                    radian = i * .0175;

                    if (!GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_RING_STATE))
                    {
                        if (i >= ARC180_DEGREE)
                        {
                            GFX_ColorSet(pMtr->color1);
                        }
                        else if (i >= ARC135_DEGREE)
                        {
                            GFX_ColorSet(pMtr->color2);
                        }
                        else if (i >= ARC090_DEGREE)
                        {
                            GFX_ColorSet(pMtr->color3);
                        }
                        else if (i >= ARC045_DEGREE)
                        {
                            GFX_ColorSet(pMtr->color4);
                        }
                        else if (i >= ARC000_DEGREE)
                        {
                            GFX_ColorSet(pMtr->color5);
                        }
                        else
                        {
                            GFX_ColorSet(pMtr->color6);
                        }
                    }

                    // compute for the effective radius of the scales
                    if((i % 45) == 0)
                        rad1 = pMtr->radius + (pMtr->radius >> 2) + 2;
                    else
                        rad1 = pMtr->radius + (pMtr->radius >> 3) + 3;

                    rad2 = (pMtr->radius + 3);

                    // compute the starting x and y positions of the scales
                    GFX_GOL_MeterValueToCoordinatePosition(
                            pMtr, i, rad1, &x1, &y1);
                    GFX_GOL_MeterValueToCoordinatePosition(
                            pMtr, i, rad2, &x2, &y2);

                    state = SCALE_DRAW;
                    break;
                }
                else
                {
                    state = NEEDLE_ERASE;
                    break;
                }

            case SCALE_DRAW:
                if (GFX_LineDraw(x1, y1, x2, y2) == GFX_STATUS_FAILURE) // now draw the scales
                    return (GFX_STATUS_FAILURE);

                if ((i % 45) == 0)
                {

                   // draw the scale labels
                    // reusing radian, x2 and y2
                    // compute for the actual angle of needle to be shown in screen
                    radian = (degreeEnd - degreeStart) - (i - (degreeStart));

                    // compute the values of the label to be shown per 45 degree
                    temp = (pMtr->maxValue - pMtr->minValue) * (radian / (degreeEnd - degreeStart));

                    // adjust for the minimum or offset value
                    temp += pMtr->minValue;

                    // this implements sprintf(strVal, "%d", temp); faster
                    // note that this is just for values >= 0, while sprintf covers negative values.
                    j = 1;

                    // get the ones value first and account for the required decimal point if enabled
                    if(GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_ACCURACY_STATE))
                    {

                        // round off to nearest tens
                        dTemp.int16Data[0] = (  temp % GFX_CONFIG_OBJECT_METER_RESOLUTION) / \
                                                (GFX_CONFIG_OBJECT_METER_RESOLUTION / 10);
                        if((dTemp.int16Data[0]) > (GFX_CONFIG_OBJECT_METER_RESOLUTION >> 1))
                            temp += (GFX_CONFIG_OBJECT_METER_RESOLUTION - dTemp.int16Data[0]);
                        temp /= GFX_CONFIG_OBJECT_METER_RESOLUTION;
                    }

                    do
                    {
                        strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j] = (temp % 10) + '0';
                        if (((temp /= 10) == 0) || (j >= GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT))
                            break;
                        j++;
                    } while (j <= GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT);

                    // the (&strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT-j]) removes the leading zeros.
                    // if leading zeroes will be printed change (&strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT-j])
                    // to simply strVal and remove the break statement above in the do-while loop
                    x2 = GFX_TextStringWidthGet((&strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j]), pMtr->hdr.pGolScheme->pFont);
                    y2 = GFX_TextStringHeightGet(pMtr->hdr.pGolScheme->pFont);

                    if (i == -45)
                    {
                        GFX_LinePositionSet(x1 + 3, y1);
                    }
                    else if (i == 0)
                    {
                        GFX_LinePositionSet(x1 + 3, y1 - (y2 >> 1));
                    }
                    else if (i == 45)
                    {
                        GFX_LinePositionSet(x1 + 3, y1 - (y2 >> 1) - 3);
                    }
                    else if (i == 90)
                    {
                        GFX_LinePositionSet(x1 - (x2 >> 1), y1 - (y2) - 3);
                    }
                    else if (i == 135)
                    {
                        GFX_LinePositionSet(x1 - (x2), y1 - (y2));
                    }
                    else if (i == 180)
                    {
                        GFX_LinePositionSet(x1 - (x2) - 3, y1 - (y2 >> 1));
                    }
                    else if (i == 225)
                    {
                        GFX_LinePositionSet(x1 - (x2 + 3), y1);
                    }

                    state = SCALE_LABEL_DRAW;
                    GFX_FontSet(pMtr->hdr.pGolScheme->pFont);
                }
                else
                {
                    i -= MTR_BUILD_OPTION_DEGREECOUNT;
                    state = SCALE_COMPUTE;
                    break;
                }

            case SCALE_LABEL_DRAW:

                if(GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), &strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j], 0)== GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);

                i -= MTR_BUILD_OPTION_DEGREECOUNT;
                state = SCALE_COMPUTE;
                break;

            case NEEDLE_ERASE:

                if (GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_UPDATE_DRAW_STATE))
                {
                         // to update the needle, redraw the old position with background color
                    GFX_LineStyleSet(GFX_LINE_STYLE_THICK_SOLID);
                    GFX_ColorSet(pMtr->hdr.pGolScheme->Color0);
                    if (GFX_LineDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xPos, pMtr->yPos) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                }

                state = NEEDLE_DRAW;

            case NEEDLE_DRAW:
                // At this point, pMtr->value is assumed to contain the new value of the meter.
                // calculate the new angle:
                angle = GFX_GOL_MeterAngleGet(pMtr, degreeStart, degreeEnd);

                GFX_GOL_MeterValueToCoordinatePosition(
                        pMtr,
                        angle,
                        pMtr->radius,
                        &(pMtr->xPos),
                        &(pMtr->yPos));

                // now draw the needle with the new position
                // needle will be drawn with color6 parameter
                GFX_ColorSet(pMtr->color6);
                GFX_LineStyleSet(GFX_LINE_STYLE_THICK_SOLID);
                if(GFX_LineDraw(pMtr->xCenter, pMtr->yCenter, pMtr->xPos, pMtr->yPos) != GFX_STATUS_SUCCESS)
                {
                    return (GFX_STATUS_FAILURE);
                }
                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);
                #ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
                state = VALUE_ERASE;
                break;
                #endif
                state = IDLE;
                return (GFX_STATUS_SUCCESS);

#ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE

            case VALUE_ERASE:

                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

                // display the value
                // erase previous value first. The temp>>1 accomodates fonts with characters that has unequal widths
                temp = GFX_TextStringWidthGet(tempXchar, pMtr->pValueFont);
                temp = temp * GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT + (temp >> 1);

                GFX_ColorSet(pMtr->hdr.pGolScheme->Color0);

                if(pMtr->type == GFX_GOL_METER_WHOLE_TYPE)
                {
                if
                    (
                     GFX_RectangleFillDraw
                     (
                      
                      pMtr->xCenter -
                      (temp >> 1), pMtr->yCenter +
                      pMtr->radius, pMtr->xCenter +
                      (temp >> 1), pMtr->yCenter +
                      pMtr->radius +
                      GFX_TextStringHeightGet(pMtr->pValueFont)
                      ) == GFX_STATUS_FAILURE
                     ) return (GFX_STATUS_FAILURE);
                }
                else if(pMtr->type == GFX_GOL_METER_HALF_TYPE)
                {
                if
                    (
                     GFX_RectangleFillDraw
                     (
                      
                      pMtr->xCenter -
                      (temp >> 1), pMtr->yCenter -
                      GFX_TextStringHeightGet(pMtr->pValueFont), pMtr->xCenter +
                      (temp >> 1), pMtr->yCenter
                      ) == GFX_STATUS_FAILURE
                     ) return (GFX_STATUS_FAILURE);
                }
                else //(pMtr->type == GFX_GOL_METER_QUARTER_TYPE)
                {
                if
                    (
                     GFX_RectangleFillDraw
                     (
                      
                      pMtr->xCenter -
                      1, pMtr->yCenter -
                      GFX_TextStringHeightGet(pMtr->pValueFont), pMtr->xCenter +
                      temp, pMtr->yCenter +
                      1
                      ) == GFX_STATUS_FAILURE
                     ) return (GFX_STATUS_FAILURE);
                }
                state = VALUE_DRAW;

            case VALUE_DRAW:

               if(angle >= ARC180_DEGREE)
                {
                    GFX_ColorSet(pMtr->color1);
                }
                else if(angle >= ARC135_DEGREE)
                {
                    GFX_ColorSet(pMtr->color2);
                }
                else if(angle >= ARC090_DEGREE)
                {
                    GFX_ColorSet(pMtr->color3);
                }
                else if(angle >= ARC045_DEGREE)
                {
                    GFX_ColorSet(pMtr->color4);
                }
                else if(angle >= ARC000_DEGREE)
                {
                    GFX_ColorSet(pMtr->color5);
                }
                else
                {
                    GFX_ColorSet(pMtr->color6);
                }

                // display the current value
                GFX_FontSet(pMtr->pValueFont);

                // this implements sprintf(strVal, "%03d", pMtr->value); faster
                // note that this is just for values >= 0, while sprintf covers negative values.
                i = pMtr->value;
                j = 1;

                // get the ones value first and account for the required decimal point if enabled
                if (GFX_GOL_ObjectStateGet(pMtr, GFX_GOL_METER_ACCURACY_STATE))
                {
                    strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j] = (((i % MTR_BUILD_OPTION_RESOLUTION)) / (MTR_BUILD_OPTION_RESOLUTION / 10)) + '0';
                    i /= MTR_BUILD_OPTION_RESOLUTION;
                    j++;
                    strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j] = '.';
                    j++;
                }

                do
                {
                    strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j] = (i % 10) + '0';
                    if (((i /= 10) == 0) || (j >= GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT))
                        break;
                    j++;
                } while (j <= GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT);

                temp = GFX_TextStringWidthGet(&strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j], pMtr->pValueFont);

                if(pMtr->type == GFX_GOL_METER_WHOLE_TYPE)
                GFX_LinePositionSet(pMtr->xCenter - (temp >> 1), pMtr->yCenter + pMtr->radius);
                else if(pMtr->type == GFX_GOL_METER_HALF_TYPE)
                GFX_LinePositionSet(pMtr->xCenter - (temp >> 1), pMtr->yCenter - GFX_TextStringHeightGet(pMtr->pValueFont));
                else//(pMtr->type == GFX_GOL_METER_QUARTER_TYPE)
                GFX_LinePositionSet(pMtr->xCenter, pMtr->yCenter - GFX_TextStringHeightGet(pMtr->pValueFont));

                state = VALUE_DRAW_RUN;

            case VALUE_DRAW_RUN:

                if(GFX_TextStringBoxDraw(
                                             pMtr->hdr.left,
                                             GFX_LinePositionYGet(),
                                             pMtr->hdr.right - pMtr->hdr.left,
                                             0,
                                             &strVal[GFX_GOL_METER_BUILD_OPTION_SCALECHARCOUNT - j], 0, GFX_ALIGN_HCENTER) == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                state = IDLE;
                return (GFX_STATUS_SUCCESS);
#endif // end of #ifdef GFX_GOL_METER_BUILD_OPTION_DISPLAY_VALUES_ENABLE
        } // endo of switch()
    } // end of while(1)
}
