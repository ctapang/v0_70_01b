/*******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    Primitive.c
    
  Summary:
    Interface for the graphics library where the primitives are renderred and sent to the graphics controller
    either external or internal

  Description:
    This file contains the interface definition for the graphics library where
    the primitives are renderred and sent to the graphics controller
    either external or internal.  It provides a way to interact with the
    display driver supported by the system
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

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "gfx/gfx_primitive.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************
uint8_t doubleBuffEnabled = 0;

GFX_LAYER_PARAMS primitiveLayer[1];
PUTIMAGE_PARAM   primitiveTaskImage;

/////////////////////// LOCAL FUNCTIONS PROTOTYPES ////////////////////////////
#if !defined GFX_CONFIG_IMAGE_FLASH_DISABLE || !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

/* GFX image function

  Summary:

  Description:

  Remarks:
  None.
*/
typedef enum
{
    _1BPP,
    _4BPP,
    _8BPP,
    _16BPP,
    RLE
} GFX_IMAGE_FUNCTION;

#if !defined GFX_CONFIG_RLE_DECODE_DISABLE
    uint16_t ImageRLE(uint16_t left, uint16_t top);
    uint16_t (*DecodeRLE)(uint8_gfx_image_prog*, uint16_t*, uint16_t); //Function pointer for RLE Decoding
#endif
    uint16_t Image1BPP(uint16_t left, uint16_t top);
    uint16_t Image4BPP(uint16_t left, uint16_t top);
    uint16_t Image8BPP(uint16_t left, uint16_t top);
    uint16_t Image16BPP(uint16_t left, uint16_t top);

uint16_t (*PutImageTask[5])(uint16_t,uint16_t) =
{
    Image1BPP,
    Image4BPP,
    Image8BPP,
    Image16BPP,

#if !defined GFX_CONFIG_RLE_DECODE_DISABLE
    ImageRLE
#endif
}; 

#endif

GFX_STATUS GFX_TextCharDraw(GFX_XCHAR ch);

GFX_Primitive_DATA GFX_Primitive_instance;                         //structure to store the primitive driver structures

#define COSINETABLEENTRIES	90

// Cosine table used to calculate angles when rendering circular objects and  arcs
// Make cosine values * 256 instead of 100 for easier math later
const int16_t   _CosineTable[COSINETABLEENTRIES+1] __attribute__((aligned(2))) =
		{
                    256, 256, 256, 256, 255, 255, 255, 254, 254, 253,
                    252, 251, 250, 249, 248, 247, 246, 245, 243, 242,
                    241, 239, 237, 236, 234, 232, 230, 228, 226, 224,
                    222, 219, 217, 215, 212, 210, 207, 204, 202, 199,
                    196, 193, 190, 187, 184, 181, 178, 175, 171, 168,
                    165, 161, 158, 154, 150, 147, 143, 139, 136, 132,
                    128, 124, 120, 116, 112, 108, 104, 100, 96,  92,
                    88,  83,  79,  75,  71,  66,  62,  58,  53,  49,
                    44,  40,  36,  31,  27,  22,  18,  13,  9,   4,
                    0
                };

int16_t GFX_LinePositionXGet()
{
   return(GFX_Primitive_instance.cursorX);

}
int16_t GFX_LinePositionYGet()
{
    return(GFX_Primitive_instance.cursorY);
}

GFX_STATUS GFX_LinePositionSet(uint16_t x, uint16_t y)
{
    GFX_Primitive_instance.cursorX = x;
    GFX_Primitive_instance.cursorY = y;
}

GFX_STATUS GFX_LinePositionRelativeSet(int16_t x, int16_t y)
{
    GFX_Primitive_instance.cursorX += x;
    GFX_Primitive_instance.cursorY += y;
}

void GFX_ColorSet(GFX_COLOR newColor)
{
    GFX_Primitive_instance.currentColor = newColor;
    GFX_DRV_instance[0].PrimitiveFunction.ColorSet(newColor);
}

GFX_STATUS GFX_CircleDraw(uint16_t x, uint16_t y, uint16_t radius)
{
    return(GFX_RectangleRoundDraw(x, y, x, y, radius));
}


/******************************************************************************
  Function:
    void GFX_Initialize()

  Summary:
    Initializes primitive data structurse for the general features
    of the primitive layer.

  Description:
    Initializes external and internal data structure for the general
    features of the primitive layer.

    This function must be called at system intialization.

  Remarks:
    None.
*/
void __attribute__((weak)) GFX_Initialize()
{
     // Current line type
    GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

    // Current cursor coordinates to 0,0
    GFX_LinePositionSet(0, 0);

    #ifdef USE_ALPHABLEND_LITE
    GFX_AlphaBlendingValueSet(100);
    GFX_PrevAlphaColorSet(0);
    #endif

    // Set font orientation
    GFX_SetFontOrientation(GFX_ALIGN_HORIZONTAL_MASK);

    // set Bevel drawing
    GFX_BevelDrawTypeSet(GFX_DRAW_FULLBEVEL);

    GFX_ImageStretchSet(IMAGE_NORMAL);
}

/******************************************************************************
  Function:
    GFX_STATUS  GFX_LineDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)

  Summary:
    Draws a line from (x1, y1) to (x2, y2) and sets the current cursor
    position to (x2, y2).

  Description:
    Returns a handle to the primitive on the queue.

  Remarks:
    None.
*/
//
GFX_STATUS  GFX_LineDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    static uint8_t   state = 0;
    static int16_t   deltaX, deltaY;
    static int16_t   error, stepErrorLT, stepErrorGE;
    static int16_t   stepX, stepY;
    static int16_t   steep;
    static int16_t   temp, style, type;
    static int16_t   x,y; //used as storage for the x,y data
    
    if(y2 == y1) //horizontal 1 color line
    {
         switch(state)
         {
              case 0:
                  if(x1 > x2)
                  {
                    temp = x1;
                    x1 = x2;
                    x2 = temp;
                  }

                  style = 0;
                  type = 1;
                  state = 1;
                  temp = x1;
        
             case 1:
                  while(temp < (x2 + 1))
                  {

                      if((++style) == (GFX_Primitive_instance.lineType & 4))
                      {
                           type ^= 1;
                           style = 0;
                      }

                     if(type)
                     {

                          if(GFX_Primitive_instance.lineType & GFX_LINE_THICKNESS_MASK) //Thick lines are odd
                          {
                           state = 3;
           case 3:
                               if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(temp, y1 - 1, 1, 3))return(GFX_STATUS_FAILURE);
                          }
                          else
                          {
                           state = 4;
          case 4:
                                if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(temp, y1))return(GFX_STATUS_FAILURE);
                          }

                     }
                     temp++;
                 }
        state = 0;
        return (GFX_STATUS_SUCCESS);
        break;
        }  
}
    else if(x1 == x2)
    {
switch(state)
{

case 0:
          if(y1 > y2)
          {
               y = y1;
               temp = y2;
          }
          else
          { 
               y = y2;
               temp = y1;
          }

          style = 0;
          type = 1;
          state++;
 
case 1:
           while(temp < (y + 1))
           {
                if((++style) == (GFX_Primitive_instance.lineType&4))
                {
                     type ^= 1;
                     style = 0;
                }

            if(type)
            {
                state = 2;
 case 2:        
                if(GFX_Primitive_instance.lineType & GFX_LINE_THICKNESS_MASK) //Thick lines are odd
                {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(x1 - 1, temp, 3, 1))return(GFX_STATUS_FAILURE);
                }
                else
                {
                   if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(x1, temp))return(GFX_STATUS_FAILURE);
                }
            }  

            temp++; 

            }
      
      state = 0;
      return(GFX_STATUS_SUCCESS);
      break;
}
}
 else
{

//Diagonal Line Section
switch(state)
{
     case 0:
         stepX = 0;
         deltaX = x2 - x1;
         
         if(deltaX < 0)
         {
              deltaX = -deltaX;
              --stepX;
         }
         else
         {
              ++stepX;
         }

         stepY = 0;
         deltaY = y2 - y1;
    
         if(deltaY < 0)
         {
              deltaY = -deltaY;
              --stepY;
         }
         else
         {
              ++stepY;
         }

         steep = 0;

         if(deltaX < deltaY)
         {
              ++steep;
              temp = deltaX;
              deltaX = deltaY;
              deltaY = temp;
              y = x1;
              x = y1;
              temp = stepX;
              stepX = stepY;
              stepY = temp;
         }
         else
         {
              y = y1;
              x = x1;
         }
         state=1;
     case 1: 
          if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(x1, y1))return(GFX_STATUS_FAILURE);

          // If the current error greater or equal zero
          stepErrorGE = deltaX << 1;

          // If the current error less than zero
          stepErrorLT = deltaY << 1;

          // Error for the first pixel
          error = stepErrorLT - deltaX;

          style = 0;
          type = 1;

          while(--deltaX >= 0)
          {
        
               if(error >= 0)
               {
                    y += stepY;
                    error -= stepErrorGE;
          }

          x += stepX;
          error += stepErrorLT;

          if((++style) == (GFX_Primitive_instance.lineType & 4))
          {
               type ^= 1;
               style = 0;
          }

          if(type)
          {
               state = 2;
     case 2:
          if(steep)
          {
               if(GFX_Primitive_instance.lineType & GFX_LINE_THICKNESS_MASK) //Thick lines are odd
               {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(y-1, x, 3, 1))return(GFX_STATUS_FAILURE);
               }
               else
               {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(y, x)) return(GFX_STATUS_FAILURE);
               }

          }
          else
          {
               
               if(GFX_Primitive_instance.lineType & GFX_LINE_THICKNESS_MASK) //Thick lines are odd
               {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(x, (y - 1), 1, 3)) return(GFX_STATUS_FAILURE);
               }
               else
               {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(x, y))return(GFX_STATUS_FAILURE);
               }
          }
         
        } 
   }
      state = 0;
      return(GFX_STATUS_SUCCESS);
    }     
}
    return(GFX_STATUS_FAILURE);
}

GFX_STATUS GFX_LineStyleSet(GFX_LINE_STYLE style)
{
    GFX_Primitive_instance.lineType = style;
}

/******************************************************************************
  Function:
    GFX_STATUS GFX_ArcDraw(uint16_t xL, uint16_t yT, uint16_t xR, uint16_t yB,
                                                       uint16_t r1, uint16_t r2, uint8_t octant)

  Summary:
    Draws the octant arc of the beveled figure with the given centers,
    radii and octant mask.

  Description:

  Remarks:
    None.
*/
GFX_STATUS GFX_ArcDraw(uint16_t xL, uint16_t yT, uint16_t xR, uint16_t yB, uint16_t r1, uint16_t r2, uint8_t octant)
{
    typedef enum
    {
        BEGIN,
        QUAD11,
        BARRIGHT1,
        QUAD12,
        BARRIGHT2,
        QUAD21,
        BARLEFT1,
        QUAD22,
        BARLEFT2,
        QUAD31,
        BARTOP1,
        QUAD32,
        BARTOP2,
        QUAD41,
        BARBOTTOM1,
        QUAD42,
        BARBOTTOM2,
        CHECK,
    } OCTANTARC_STATES;

    static uint32_t temp;

    static short y1Limit, y2Limit;
    static short x1, x2, y1, y2, ovrlap;
    static short err1, err2;
    static short x1Cur, y1Cur, y1New;
    static short x2Cur, y2Cur, y2New;
    static OCTANTARC_STATES state = BEGIN;

    while(1)
    {
        switch(state)
        {
            case BEGIN:
                temp = SIN45 * r1;
                y1Limit = temp>>16;
                temp = SIN45 * r2;
                y2Limit = temp>>16;

                temp = (uint32_t) (ONEP25 - ((long) r1 << 16));
                err1 = (short) (temp>>16);

                temp = (uint32_t) (ONEP25 - ((long) r2 << 16));
                err2 = (short) (temp>>16);

                x1 = r1;
                x2 = r2;
                y1 = 0;
                y2 = 0;

                x1Cur = x1;
                y1Cur = y1 + 1;
                y1New = y1;
                x2Cur = x2;
                y2Cur = y2;
                y2New = y2;
                state = CHECK;

            case CHECK:
                if(y2 > y2Limit)
                {
                    state = BARRIGHT1;
                    return(GFX_STATUS_FAILURE);
                }

                // y1New & y2New records the last y positions
                y1New = y1;
                y2New = y2;

                if(y1 <= y1Limit)
                {
                    if(err1 > 0)
                    {
                        x1--;
                        err1 += 5;
                        err1 += (y1 - x1) << 1;
                    }
                    else
                    {
                        err1 += 3;
                        err1 += y1 << 1;
                    }

                    y1++;
                }
                else
                {
                    y1++;
                    if(x1 < y1)
                        x1 = y1;
                }

                if(err2 > 0)
                {
                    x2--;
                    err2 += 5;
                    err2 += (y2 - x2) << 1;
                }
                else
                {
                    err2 += 3;
                    err2 += y2 << 1;
                }

                y2++;

                state = QUAD11;
 
            case QUAD11:
                if((x1Cur != x1) || (x2Cur != x2))
                {

                    // 1st octant
                    if(octant & 0x01)
                    {
                        // check overlaps
                        if (x1Cur > y1New)
                            ovrlap = yT - x1Cur;
                        else    
                            ovrlap = yT - y1New;
                        if(GFX_RectangleFillDraw(xR + y2Cur, yT - x2Cur, xR + y1New, ovrlap) == GFX_STATUS_FAILURE)
                             return(GFX_STATUS_FAILURE);
                    }
                }
                else
                {
                    state = CHECK;
                    return(GFX_STATUS_FAILURE);

                }

                state = QUAD12;
                break;

            case QUAD12:

                // 2nd octant
                if(octant & 0x02)
                {
                    // check overlaps
                    if (x1Cur > y1New)
                        ovrlap = xR + x1Cur;
                    else    
                        ovrlap = xR + y1New;
                    if(GFX_RectangleFillDraw(ovrlap, yT - y1New, xR + x2Cur, yT - y2Cur) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE); 
                }

                state = QUAD21;
                break;

            case QUAD21:

                // 3rd octant
                if(octant & 0x04)
                {
                    // check overlaps
                    if (x1Cur > y2New)
                        ovrlap = xR + x1Cur;
                    else    
                        ovrlap = xR + y2New;
                    if(GFX_RectangleFillDraw(ovrlap, yB + y1Cur, xR + x2Cur, yB + y2New) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE); 
                }
                state = QUAD22;
                break;

            case QUAD22:

                // 4th octant
                if(octant & 0x08)
                {
                    // check overlaps
                    if (x1Cur > y2New)
                        ovrlap = yB + x1Cur;
                    else    
                        ovrlap = yB + y2New;
                    if(GFX_RectangleFillDraw(xR + y1Cur, ovrlap, xR + y2New, yB + x2Cur) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE); 
                }

                state = QUAD31;
                break;

            case QUAD31:

                // 5th octant
                if(octant & 0x10)
                {
                    // check overlaps
                    if (x1Cur > y1New)
                        ovrlap = yB + x1Cur;
                    else    
                        ovrlap = yB + y1New;
                    if(GFX_RectangleFillDraw(xL - y1New, ovrlap, xL - y2Cur, yB + x2Cur) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE);
                }

                state = QUAD32;
                break;

            case QUAD32:

                // 6th octant
                if(octant & 0x20)
                {
                    // check overlaps
                    if (x1Cur > y1New)
                        ovrlap = xL - x1Cur;
                    else    
                        ovrlap = xL - y1New;
                    if(GFX_RectangleFillDraw(xL - x2Cur, yB + y2Cur, ovrlap, yB + y1New) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE);
                }

                state = QUAD41;
                break;

            case QUAD41:

                // 7th octant
                if(octant & 0x40)
                {
                    // check overlaps
                    if (x1Cur > y2New)
                        ovrlap = xL - x1Cur;
                    else    
                        ovrlap = xL - y2New;
                    if(GFX_RectangleFillDraw(xL - x2Cur, yT - y2New, ovrlap, yT - y1Cur) == GFX_STATUS_FAILURE)
                         return(GFX_STATUS_FAILURE);
                }

                state = QUAD42;
                break;

            case QUAD42:

                // 8th octant
                if(octant & 0x80)
                {
                    // check overlaps
                    if (x1Cur > y2New)
                        ovrlap = yT - x1Cur;
                    else    
                        ovrlap = yT - y2New;
                    if(GFX_RectangleFillDraw(xL - y2New, yT - x2Cur, xL - y1Cur, ovrlap) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                // update current values
                x1Cur = x1;
                y1Cur = y1;
                x2Cur = x2;
                y2Cur = y2;
                state = CHECK;
                break;

            case BARRIGHT1:     // draw upper right
                if((xR - xL) || (yB - yT))
                {

                    // draw right
                    if(octant & 0x02)
                    {
                        if(GFX_RectangleFillDraw(xR + r1, yT + 1, xR + r2, (yB + yT) >> 1) == GFX_STATUS_FAILURE)
                            return(GFX_STATUS_FAILURE);
                    }
                }
                else
                {
                    state = BEGIN;
                    return (GFX_STATUS_SUCCESS);
                }

                state = BARRIGHT2;
                break;

            case BARRIGHT2:     // draw lower right
                if(octant & 0x04)
                {
                    if(GFX_RectangleFillDraw(xR + r1, ((yB + yT) >> 1) + 1, xR + r2, yB) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                state = BARBOTTOM1;
                break;

            case BARBOTTOM1:    // draw left bottom
                // draw bottom
                if(octant & 0x10)
                {
                    if(GFX_RectangleFillDraw(xL, yB + r1, ((xR + xL) >> 1), yB + r2) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                state = BARBOTTOM2;
                break;

            case BARBOTTOM2:    // draw right bottom
                if(octant & 0x08)
                {
                    if(GFX_RectangleFillDraw(((xR + xL) >> 1), yB + r1, xR, yB + r2) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                state = BARTOP1;
                break;

            case BARTOP1:       // draw left top
                if(xR - xL)
                {

                    // draw top
                    if(octant & 0x80)
                    {
                        if(GFX_RectangleFillDraw(xL, yT - r2, ((xR + xL) >> 1), yT - r1) == GFX_STATUS_FAILURE)
                            return(GFX_STATUS_FAILURE);
                    }

                    state = BARTOP2;
                }
                else
                    state = BARLEFT1;   // no width go directly to height bar
                break;

            case BARTOP2:               // draw right top
                if(octant & 0x01)
                {
                    if(GFX_RectangleFillDraw(((xR + xL) >> 1) + 1, yT - r2, xR - 1, yT - r1) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                state = BARLEFT1;
                break;

            case BARLEFT1:              // draw upper left
                if(yT - yB)
                {

                    // draw left
                    if(octant & 0x40)
                    {
                        if(GFX_RectangleFillDraw(xL - r2, yT, xL - r1, ((yB + yT) >> 1)) == GFX_STATUS_FAILURE)
                            return(GFX_STATUS_FAILURE);
                    }

                    state = BARLEFT2;
                }
                else
                {
                    state = BEGIN;      // no height go back to BEGIN
                    return (GFX_STATUS_SUCCESS);
                }

                break;

            case BARLEFT2:              // draw lower left
                if(octant & 0x20)
                {
                    if(GFX_RectangleFillDraw(xL - r2, ((yB + yT) >> 1) + 1, xL - r1, yB - 1) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);
                }

                state = BEGIN;
                return (GFX_STATUS_SUCCESS);
        }                               // end of switch
    }   // end of while
}

/******************************************************************************
  Function:
    GFX_STATUS  GFX_BevelDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rad)

  Summary:
    Draws a beveled figure on the screen.

  Description:

  Remarks:
    None.
*/
GFX_STATUS __attribute__ ((always_inline)) GFX_RectangleRoundDraw(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t radius)
{
    static short       style, type, xLimit, xPos, yPos, error;
    static uint32_t   temp;
    static uint8_t state,pixelState = 0;

switch(state)
{

     case 0:
          temp = SIN45 * radius;
          xLimit = (temp>>16) + 1;
          temp = (uint32_t) (ONEP25 - ((long) radius << 16));
          error = (short) (temp>>16);
          yPos = radius;
          style = 0;
          type = 1;
    
          if(radius)
          {
               xPos = 0;
      
               while(xPos <= xLimit)
               {
                    if((++style) == (GFX_Primitive_instance.lineType & 4))
                    {
                         type ^= 1;
                         style = 0;
                    }

                    if(type)
                    {
                         state = 1;
                         if(GFX_Primitive_instance.lineType & GFX_LINE_THICKNESS_MASK)
                         {
                             pixelState = 8;
                         }
                         else
                         {
                             pixelState = 0;
                         }
      case 1:
                         switch(pixelState)
                         {           
                              case 0: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(right + yPos, top - xPos))return(GFX_STATUS_FAILURE);pixelState++;
                              case 1: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(right + xPos, bottom + yPos))return(GFX_STATUS_FAILURE);pixelState++;         // 2nd quadrant
                              case 2: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(left - yPos, bottom + xPos))return(GFX_STATUS_FAILURE);pixelState++;
                              case 3: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(left - yPos, top - xPos))return(GFX_STATUS_FAILURE);pixelState++;        // 4th quadrant
                              case 4: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(left - xPos, bottom + yPos))return(GFX_STATUS_FAILURE);pixelState++;         // 3rd quadrant
                              case 5: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(right + xPos, top - yPos))return(GFX_STATUS_FAILURE);pixelState++;         // 1st quadrant
                              case 6: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(right + yPos, bottom + xPos))return(GFX_STATUS_FAILURE);pixelState++;
                              case 7: if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(left - xPos, top - yPos))return(GFX_STATUS_FAILURE);
                              break;

                              case 8:     if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(right + xPos, top - yPos - 1,1,3))return(GFX_STATUS_FAILURE);pixelState++; // 1st quadrant
                              case 9:     if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(right + yPos - 1, top - xPos,3,1))return(GFX_STATUS_FAILURE);pixelState++;
                              case 10:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(right + xPos, bottom + yPos - 1,1,3))return(GFX_STATUS_FAILURE);pixelState++; // 2nd quadrant
                              case 11:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(right + yPos - 1, bottom + xPos,3,1))return(GFX_STATUS_FAILURE);pixelState++;
                              case 12:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left - xPos, bottom + yPos - 1,1,3))return(GFX_STATUS_FAILURE);pixelState++; // 3rd quadrant
                              case 13:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left - yPos - 1, bottom + xPos,3,1))return(GFX_STATUS_FAILURE);pixelState++;
                              case 14:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left - yPos - 1, top - xPos,3,1))return(GFX_STATUS_FAILURE);pixelState++;
                              case 15:    if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left - xPos, top - yPos - 1,1,3))return(GFX_STATUS_FAILURE);
                          }

                         }

            if(error > 0)
            {
                yPos--;
                error += 5 + ((xPos - yPos) << 1);
            }
            else
                error += 3 + (xPos << 1);

          xPos++;
        }
    }
   state = 2;

     case 2:

          switch(pixelState)
          {

     case 0:
          // Must use lines here since this can also be used to draw focus of round buttons
          if(right - left)       // draw top
          {
               if(GFX_LineDraw(left, top - radius, right, top - radius) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);                
          }
          pixelState++;
     case 1:

          if(bottom - top) // draw left
          {
               if(GFX_LineDraw(left - radius, top, left - radius, bottom) == GFX_STATUS_FAILURE)
                    return(GFX_STATUS_FAILURE);
          }
          pixelState++;
    case 2:
         if((right - left) || (bottom - top)) // draw right
         {
             if(GFX_LineDraw(right + radius, top, right + radius, bottom) == GFX_STATUS_FAILURE)
                  return(GFX_STATUS_FAILURE);
          pixelState++;
    case 3: // draw bottom
        if(GFX_LineDraw(left, bottom + radius, right, bottom + radius) == GFX_STATUS_FAILURE)
             return(GFX_STATUS_FAILURE);
        
    }

      pixelState=0;
      state=0;
 }
}
    return (GFX_STATUS_SUCCESS); //Primitive Drawn
}

GFX_STATUS __attribute__ ((always_inline)) GFX_RectangleDraw(
                                uint16_t left,
                                uint16_t top,
                                uint16_t right,
                                uint16_t bottom)
{
    return(GFX_RectangleRoundDraw(left,top,right,bottom,0));
}

/******************************************************************************
  Function:
    WORD GFX_BevelFill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rad)

  Summary:
    Draws a filled beveled figure on the screen.

  Description:

    Returns a handle to the primitive on the queue.

  Remarks:
    None.
*/
GFX_STATUS GFX_RectangleRoundFillDraw(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t rad)
{
    typedef enum
    {
        FB_BEGIN,
        FB_INIT_FILL,
        FB_CHECK,
        FB_Q8TOQ1,
        FB_Q7TOQ2,
        FB_Q6TOQ3,
        FB_Q5TOQ4,
        FB_DRAW_MISSING_1,    
        FB_DRAW_MISSING_2,    
        FB_WAITFORDONE,        
    } FB_FILLCIRCLE_STATES;

    static short err;
    static short yLimit, xPos, yPos;
    static short xCur, yCur, yNew;
    static short last54Y, last18Y;
    static uint32_t temp;
    static GFX_STATUS index;

    static FB_FILLCIRCLE_STATES state = FB_BEGIN;

    while(1)
    {

        switch(state)
        {
            case FB_BEGIN:

                // draw the face
                if (GFX_Primitive_instance.bevelDrawType == GFX_DRAW_FULLBEVEL)
		        { 
                     index = GFX_RectangleFillDraw(x1 - rad, y1, x2 + rad, y2);
		        }
                else if (GFX_Primitive_instance.bevelDrawType == GFX_DRAW_TOPBEVEL)
		        {
	                index = GFX_RectangleFillDraw(x1 - rad, y1, x2 + rad, y1+((y2-y1)>>1));
                }
		        else    
		        {
			        index = GFX_RectangleFillDraw(x1 - rad, y1+((y2-y1)>>1), x2 + rad, y2);
    		    }   

                if(index == GFX_STATUS_FAILURE)
                {
	               return (GFX_STATUS_FAILURE);
                }         
                state = FB_INIT_FILL;
            
            case FB_INIT_FILL:

                if(!rad)
                {   // no radius object is a filled rectangle
                    state = FB_BEGIN;
                    return(GFX_STATUS_SUCCESS);
                }

                // compute variables
                temp = SIN45 * rad;
                yLimit = temp>>16;
                temp = (uint32_t) (ONEP25 - ((long) rad << 16));
                err = (short) (temp>>16);
                xPos = rad;
                yPos = 0;

                // yCur starts at 1 so the center line is not drawn and will be drawn separately
                // this is to avoid rendering twice on the same line
                yCur = 1;           
                xCur = xPos;
                yNew = yPos;
    
                // note initial values are important
                last54Y = GFX_MaxYGet();
                last18Y = 0;

                state = FB_CHECK;

            case FB_CHECK:

                // check first for limits
                if(yPos > yLimit)
                {
                    if (rad)
                        state = FB_DRAW_MISSING_1;
                    else
                        state = FB_WAITFORDONE;
                    break;
                }

                // yNew records the last y position
                yNew = yPos;

                // calculate the next value of x and y
                if(err > 0)
                {
                    xPos--;
                    err += 5 + ((yPos - xPos) << 1);
                }
                else
                    err += 3 + (yPos << 1);
                yPos++;
                state = FB_Q6TOQ3;

            case FB_Q6TOQ3:

                if(xCur != xPos)
                {

                    // 6th octant to 3rd octant
	            	if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_BOTTOMBEVEL)
	            	{ 

                             // check first if there will be an overlap
                             if (y2 + yNew > last54Y)
                             {
        	                      index = GFX_RectangleFillDraw(x1 - xCur, y2 + yCur, x2 + xCur, last54Y - 1);
                             }        
                             else
                             {
        	                      index = GFX_RectangleFillDraw(x1 - xCur, y2 + yCur, x2 + xCur, y2 + yNew);
                             }

                             if(index == GFX_STATUS_FAILURE)
                             {
	                            return (GFX_STATUS_FAILURE);
                             }
              		}          	
                    state = FB_Q5TOQ4;
                    break;
                }

                state = FB_CHECK;
                break;

            case FB_Q5TOQ4:

            	if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_BOTTOMBEVEL)
            	{ 

   	                // 5th octant to 4th octant
                    // check: if overlapping then no need to proceed
                    if ((xCur) > (yNew))
                    {
   	                    index = GFX_RectangleFillDraw(x1 - yNew, y2 + xCur, x2 + yNew, y2 + xCur);
                            
                          if(index == GFX_STATUS_FAILURE)
                          {
	                         return (GFX_STATUS_FAILURE);
                          }
                          last54Y = (y2 + xCur);
                    }

		       }
                state = FB_Q7TOQ2;

            case FB_Q7TOQ2:

                // 7th octant to 2nd octant
	          if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_TOPBEVEL)
	          {
                     // check: if overlapping then no need to proceed
                     if (y1 - yNew < last18Y)
                     {
	                    index = GFX_RectangleFillDraw(x1 - xCur, last18Y + 1, x2 + xCur, y1 - yCur);
                     }
                     else
                     {
	                    index = GFX_RectangleFillDraw(x1 - xCur, y1 - yNew, x2 + xCur, y1 - yCur);
                     }

                     if(index == GFX_STATUS_FAILURE)
                     {
	                    return (GFX_STATUS_FAILURE);
                     }

		     }
                state = FB_Q8TOQ1;

            case FB_Q8TOQ1:

                // 8th octant to 1st octant
	          if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_TOPBEVEL)
		      {
                    // check first if there will be an overlap
                    if ((xCur) > (yNew))
                    {
    	                   index = GFX_RectangleFillDraw(x1 - yNew, y1 - xCur, x2 + yNew, y1 - xCur);
                          
                         if(index == GFX_STATUS_FAILURE)
                         {
	                        return(GFX_STATUS_FAILURE);
                         }
                        last18Y = y1 - xCur;    
                    }

    			}                	
                // update current values
                xCur = xPos;
                yCur = yPos;

                state = FB_CHECK;
                break;

            case FB_DRAW_MISSING_1:
                // check only one side since they are the same    
                if ((yNew) < (xPos)) 
                {
                    // there is a missing line, draw that line
                    if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_TOPBEVEL)
                    {  
                           index = GFX_RectangleFillDraw(x1 - yNew, y1 - xPos, x2 + yNew, y1 - xPos);
                           
                           if(index == GFX_STATUS_FAILURE)
                           {
	                          return(GFX_STATUS_FAILURE);
                           }
                    }
                    
                    state = FB_DRAW_MISSING_2;
                }
                else
                {
                    state = FB_WAITFORDONE;
                    break;
                }
            case FB_DRAW_MISSING_2:
                if ((yNew) < (xPos)) 
                {
                    if (GFX_Primitive_instance.bevelDrawType & GFX_DRAW_BOTTOMBEVEL)
                    {    
                         index = GFX_RectangleFillDraw(x1 - yNew, y2 + xPos, x2 + yNew, y2 + xPos);
                         
                         if(index == GFX_STATUS_FAILURE)
                         {
	                        return(GFX_STATUS_FAILURE);
                         } 
                    }
                }
                state = FB_WAITFORDONE;

            case FB_WAITFORDONE:
                state = FB_BEGIN;
                return(GFX_STATUS_SUCCESS);
        }           // end of switch
    }               // end of while

}

/******************************************************************************
  Function:
    GFX_STATUS GFX_PolyDraw(uint16_t numPoints, short* polyPoints)

  Summary:
    Draws line polygon.

  Description:

    Returns a handle to the primitive on the queue.

  Remarks:
    None.
*/

GFX_STATUS GFX_PolygonDraw(uint16_t numPoints, uint16_t *polyPoints)
{
    static short sx, sy, ex, ey;

    sx = *polyPoints++;
    sy = *polyPoints++;

    while(--numPoints)
    {
        ex = *polyPoints++;
        ey = *polyPoints++;
        while(GFX_LineDraw(sx, sy, ex, ey) == GFX_STATUS_FAILURE);
        sx = ex;
        sy = ey;
    }

    return (GFX_STATUS_SUCCESS); //Primitive Renderred

}

/******************************************************************************
  Function:
    bool GFX_PixelArrayGet(uint16_t *array, uint16_t x, uint16_t y, uint16_t count)

  Summary:
    Returns the color of the pixels at the given position.

  Description:

  Remarks:
    None.
*/
bool  GFX_PixelArrayGet(uint16_t *array, uint16_t x, uint16_t y, uint16_t count)
{
    
    if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(array,x,y,count))
    {
        return(false);
    }

     return(true);
}

#ifdef USE_ALPHABLEND_LITE
/******************************************************************************
  Function:
    void BarAlpha(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)

  Summary:
    Draws alpha blended bar.

  Description:

  Remarks:
    None.
*/
uint16_t GFX_BarAlphaDraw(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{

    static short x,y;
    static GFX_COLOR  fcolor; 
    static GFX_COLOR* bcolor;
    static uint8_t state = 0;
    static uint16_t* arrayCount = NULL;

switch(state)
{
case 0:
   y = top;
   fcolor = GFX_DRV_instance[0].color;

    while(y<(bottom+1))
    {
case 1:
        state = 1;
        arrayCount = GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&GFX_Primitive_instance.line[left],left,y,(right-left)+1);

        if(arrayCount == NULL) return(GFX_STATUS_FAILURE);
        state = 2;
case 2:
        if(*arrayCount > 0) return(GFX_STATUS_FAILURE);

        bcolor = &GFX_Primitive_instance.line[left];
        
        if(GFX_PrevAlphaColorGet() != 0)
        {
            
            for(x=left;x<right+1;x++)
            {
                switch(GFX_AlphaBlendingValueGet())
                {
                    case 50: *bcolor += ConvertColor50(fcolor) - ConvertColor50(GFX_PrevAlphaColorGet());
                    break;
                    case 75: *bcolor += ConvertColor75(fcolor) - ConvertColor75(GFX_PrevAlphaColorGet());
                    break;
                    case 25: *bcolor += ConvertColor25(fcolor) - ConvertColor25(GFX_PrevAlphaColorGet());
                    break;
                    default: break;
                }  
               bcolor++;
            }   
        }
        else
        {                          
            for(x=left;x<right+1;x++)
            {
                switch(GFX_AlphaBlendingValueGet())
                {
                    case 50: *bcolor = ConvertColor50(fcolor) + ConvertColor50(*bcolor); break;
                    case 25: *bcolor = ConvertColor25(fcolor) + ConvertColor75(*bcolor); break;
                    case 75: *bcolor = ConvertColor75(fcolor) + ConvertColor25(*bcolor); break;
                    default: break;
                } 
                bcolor++;
            } 
        }
        state = 3;
case 3:
        arrayCount = GFX_DRV_instance[0].PrimitiveFunction.PixelArrayPut(&GFX_Primitive_instance.line[left],left,y, right-left+1,1);
      if(arrayCount == NULL) return(GFX_STATUS_FAILURE);
        state = 4;
case 4:
        if(*arrayCount>0) return(GFX_STATUS_FAILURE);
        y++;
   }
    }
    state = 0;
    return (GFX_STATUS_SUCCESS);
}
#endif

/******************************************************************************
  Function:
    GFX_STATUS GFX_RectangleFillDraw(uint8_t uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)

  Summary:

  Description:

  Remarks:
    None.
*/
GFX_STATUS GFX_RectangleFillDraw(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
   static short pixelCount, lineCount;

    #ifdef USE_ALPHABLEND_LITE
    if(GFX_AlphaBlendingValueGet() != 100)
    {
       if(GFX_BarAlphaDraw(left,top,right,bottom) == GFX_STATUS_FAILURE)
            return(GFX_STATUS_FAILURE);
    }
    else
    #endif
    {
        if(GFX_DRV_instance[0].PrimitiveFunction.BarFill != NULL) //Hardware acclerated available
        {  
          if(GFX_DRV_instance[0].PrimitiveFunction.BarFill(left,top,right,bottom))
               return(GFX_STATUS_FAILURE);
          else
          {
               return(GFX_STATUS_SUCCESS);
          }
        }

          lineCount = (bottom - top) + 1;
          pixelCount = (right - left) + 1; 
  
       if(GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left,top,pixelCount,lineCount))
       {
            return(GFX_STATUS_FAILURE); //Driver Buffer full
       }
       }

       return(GFX_STATUS_SUCCESS);
}

GFX_STATUS GFX_ScreenClear(void)
{
    return(GFX_RectangleFillDraw(0,0,GFX_MaxXGet(),GFX_MaxYGet()));
}

GFX_STATUS __attribute__ ((always_inline)) GFX_CircleFillDraw(
                                uint16_t x,
                                uint16_t y,
                                uint16_t radius)
{

    return(GFX_RectangleRoundFillDraw(x,y,x,y,radius));

}

/******************************************************************************
  Function:
    void GFX_FontSet(void* pFont)

  Summary:
    Sets the current font to pFont.

  Description:

  Remarks:
    None.
*/
GFX_STATUS GFX_FontSet(GFX_RESOURCE_HDR *pFont)
{

    GFX_FONT_SPACE uint8_t *src;
    uint8_t *dest;
    int i;
    GFX_FONT_HEADER *pHeader;

    switch(*((short *)pFont))
    {
        //case GFX_RESOURCE_MEMORY_FLASH:
        case GFX_RESOURCE_FONT_FLASH_NONE:
        src = pFont->resource.font.location.progByteAddress;
        dest = (uint8_t *)&(GFX_Primitive_instance.currentFont.header);
        for(i = 0; i < sizeof(GFX_FONT_HEADER); i++)
        {
           *dest = *src;
           src++;
           dest++;
        }
        break;

        case GFX_RESOURCE_MEMORY_RAM:
            memcpy( &(GFX_Primitive_instance.currentFont.header),
            pFont->resource.font.location.progByteAddress,
            sizeof(GFX_FONT_HEADER));
            break;

		
        case GFX_RESOURCE_MEMORY_EXTERNAL:
                pHeader = &(GFX_Primitive_instance.currentFont.header);
                //ExternalMemoryCallback(pFont, 0, sizeof(GFX_FONT_HEADER), pHeader);
            break;

        default:
            break;
    }

     GFX_Primitive_instance.currentFont.pFont = pFont;
}
#if !defined GFX_CONFIG_FONT_FLASH_DISABLE
/******************************************************************************
  Function:
    uint16_t GFX_TextWidthFlashGet(GFX_XCHAR* textString, void* pFont

  Summary:
    Returns text width for the font

  Description:

  Remarks:
    None.
*/

uint16_t __attribute__((weak)) GFX_TextWidthFlashGet(GFX_XCHAR* textString, GFX_RESOURCE_HDR* pFont)
{ 
    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY *pChTable = NULL;
    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY_EXTENDED *pChTableExtended = NULL;
    GFX_FONT_SPACE GFX_FONT_HEADER *pHeader;

    int16_t       textWidth;
    GFX_XCHAR       ch;
    GFX_XCHAR       fontFirstChar;
    GFX_XCHAR       fontLastChar;

    pHeader = (GFX_FONT_SPACE GFX_FONT_HEADER *)pFont->resource.font.location.progByteAddress;
    fontFirstChar = pHeader->firstChar;
    fontLastChar = pHeader->lastChar;
    if(pHeader->extendedGlyphEntry)
    {
        pChTableExtended = (GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY_EXTENDED *) (pHeader + 1);
    }
    else
    {
        pChTable = (GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY *) (pHeader + 1);
    }    
    textWidth = 0;
    while((GFX_UXCHAR)15 < (GFX_UXCHAR)(ch = *textString++))
    {
        if((GFX_UXCHAR)ch < (GFX_UXCHAR)fontFirstChar)
            continue;
        if((GFX_UXCHAR)ch > (GFX_UXCHAR)fontLastChar)
            continue;
        if(pHeader->extendedGlyphEntry)
        {
            textWidth += (pChTableExtended + ((GFX_UXCHAR)ch - (GFX_UXCHAR)fontFirstChar))->cursorAdvance;
        }
        else
        {
            textWidth += (pChTable + ((GFX_UXCHAR)ch - (GFX_UXCHAR)fontFirstChar))->width;
        }
    }

    return (textWidth);
}
#endif //#if defined (USE_FONT_FLASH)

/******************************************************************************
  Function:
    uint16_t GFX_TextStringWidthGet(GFX_XCHAR *textString, void *pFont)

  Summary:

  Description:

  Remarks:
    None.
*/
uint16_t __attribute__((weak)) GFX_TextStringWidthGet(GFX_XCHAR *textString, GFX_RESOURCE_HDR *pFont)
{
    switch(*((short *)pFont))
    {
#if defined (USE_FONT_RAM)
        case GFX_RESOURCE_MEMORY_RAM:
            return GFX_TextWidthGetRam(textString, pFont);
#endif
#if !defined GFX_CONFIG_FONT_FLASH_DISABLE
        //case GFX_RESOURCE_MEMORY_FLASH:
        case GFX_RESOURCE_FONT_FLASH_NONE:
            return GFX_TextWidthFlashGet(textString, pFont);
#endif
#if !defined GFX_CONFIG_FONT_EXTERNAL_DISABLE
        case GFX_RESOURCE_MEMORY_EXTERNAL:
            return GFX_TextWidthGetExternal(textString, pFont);
#endif            
        default:
            return (GFX_STATUS_SUCCESS);
    }
}

/******************************************************************************
  Function:
    uint16_t GFX_TextStringHeightGet(void* pFont)

  Summary:
    Returns characters height for the font.

  Description:

  Remarks:
    None.
*/
uint16_t GFX_TextStringHeightGet(GFX_RESOURCE_HDR *pFont)
{
        switch(*((short *)pFont))
        {
#ifdef USE_FONT_RAM
            case GFX_RESOURCE_MEMORY_RAM:
                return ((GFX_FONT_HEADER *) ((FONT_RAM *)pFont)->address)->height;
#endif
                    
#if !defined GFX_CONFIG_FONT_FLASH_DISABLE
            //case GFX_RESOURCE_MEMORY_FLASH:
            case GFX_RESOURCE_FONT_FLASH_NONE:
                return pFont->resource.font.header.height;
#endif
                    
#if !defined GFX_CONFIG_FONT_EXTERNAL_DISABLE
            case GFX_RESOURCE_MEMORY_EXTERNAL:
                uint16_t height;
                ExternalMemoryCallback(pFont, sizeof(GFX_FONT_HEADER) - 2, 2, &height);
                return (height);
#endif
    
            default:
                return (GFX_STATUS_SUCCESS);
        }
}

/******************************************************************************
  Function:
    uint16_t GFX_ImageWidthGet(void* image)

  Summary:
    Returns image width.

  Description:

  Remarks:
    None.
*/
int16_t __attribute__((weak)) GFX_ImageWidthGet(GFX_RESOURCE_HDR *image)
{
    return image->resource.image.width;

}

/******************************************************************************
  Function:
    uint16_t GFX_ImageHeightGet(void* image)

  Summary:
    Returns image height

  Description:

  Remarks:
    None.
*/
int16_t __attribute__((weak)) GFX_ImageHeightGet(GFX_RESOURCE_HDR *pImage)
{
    return pImage->resource.image.height;
}

#if !defined GFX_CONFIG_FONT_FLASH_DISABLE
/******************************************************************************
  Function:
    void OutCharGetInfoFlash (GFX_XCHAR ch, OUTCHAR_PARAM *pParam)

  Summary:

  Description:
    Gathers the parameters for the specified character of the
    currently set font from flash memory. This is a step performed
    before the character is rendered.

  Remarks:
    None.
*/
void __attribute__((weak)) OutCharGetInfoFlash(GFX_FONT_CURRENT *Font, GFX_XCHAR ch, GFX_FONT_OUTCHAR *pParam)
{

    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY_EXTENDED    *pChTableExtended;
    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY             *pChTable;

    // set color depth of font,
    // based on 2^bpp where bpp is the color depth setting in the GFX_FONT_HEADER
    pParam->bpp = 1 << Font->header.bpp;

    if(Font->header.extendedGlyphEntry)
    {
        pChTableExtended = (GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY_EXTENDED *) (Font->pFont->resource.font.location.progByteAddress + sizeof(GFX_FONT_HEADER)) + ((GFX_UXCHAR)ch - (GFX_UXCHAR)Font->header.firstChar);
        pParam->pChImage = (GFX_FONT_SPACE uint8_t *) (Font->pFont->resource.font.location.progByteAddress + pChTableExtended->offset);
        pParam->chGlyphWidth = pChTableExtended->glyphWidth;
        pParam->xWidthAdjust = pChTableExtended->glyphWidth - pChTableExtended->cursorAdvance;
        pParam->xAdjust = pChTableExtended->xAdjust;
        pParam->yAdjust = pChTableExtended->yAdjust;
                    
        if(pParam->yAdjust > 0)
        {
            pParam->heightOvershoot = pParam->yAdjust;
        }
    }
    else
    {
       pChTable = (GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY *)
       (Font->pFont->resource.font.location.progByteAddress + sizeof(GFX_FONT_HEADER)) +
       ((GFX_UXCHAR)ch -
       (GFX_UXCHAR)Font->pFont->resource.font.header.firstChar);

        pParam->pChImage = (GFX_FONT_SPACE uint8_t *) (Font->pFont->resource.font.location.progByteAddress + ((uint32_t)(pChTable->offsetMSB) << 8) + pChTable->offsetLSB);
        pParam->chGlyphWidth = pChTable->width;
    }   
}
#endif // #ifdef USE_FONT_FLASH

#if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE

static GFX_COLOR   _fgcolor100;
static GFX_COLOR   _fgcolor25;
static GFX_COLOR   _fgcolor75;
static GFX_COLOR   _bgcolor100;
static GFX_COLOR   _bgcolor25;
static GFX_COLOR   _bgcolor75;

/******************************************************************************
  Function:
    static void __attribute__((always_inline)) calculateColors(void)

  Summary:
    calculates mid values of colors

  Description:

  Remarks:
    Note: Internal to this file
*/

static void __attribute__((always_inline)) calculateColors(void)
{
    GFX_COLOR   _fgcolor50;
    GFX_COLOR   _bgcolor50;
    
#if (GFX_CONFIG_COLOR_DEPTH == 16) || (GFX_CONFIG_COLOR_DEPTH == 24)

    _fgcolor50  = ConvertColor50(_fgcolor100);
    _fgcolor25  = ConvertColor25(_fgcolor100);
    _fgcolor75  = _fgcolor50   +  _fgcolor25;

    _bgcolor50  = ConvertColor50(_bgcolor100);
    _bgcolor25  = ConvertColor50(_bgcolor100);
    _bgcolor75  = _bgcolor50   +  _bgcolor25;

#elif ((GFX_CONFIG_COLOR_DEPTH == 8) || (GFX_CONFIG_COLOR_DEPTH == 4))
        
    _fgcolor50  = _fgcolor100 >> 1;
    _fgcolor25  = _fgcolor50  >> 1;
    _fgcolor75  = _fgcolor50  +  _fgcolor25;

    _bgcolor50  = _bgcolor100 >> 1;
    _bgcolor25  = _bgcolor50  >> 1;
    _bgcolor75  = _bgcolor50  +  _bgcolor25;
    
#endif
    _fgcolor25 += _bgcolor75;
    _fgcolor75 += _bgcolor25;
}

#endif //#ifdef USE_ANTIALIASED_FONTS

/******************************************************************************
  Function:
    void OutCharRender(GFX_XCHAR ch, OUTCHAR_PARAM *pParam)

  Summary:
    Performs the actual rendering of the character using GFX_PixelsPut().

  Description:

  Remarks:
    Note: Application should not call this function. This function is for
    versatility of implementing hardware accelerated text rendering
    only.
*/
uint16_t OutCharRender(GFX_XCHAR ch, GFX_FONT_OUTCHAR *pParam)
{
    static uint8_t        temp = 0;
    static uint8_t        mask;
    static uint8_t        restoremask = 0x01;
    static short          xCnt, yCnt, x = 0, y;
    static uint8_t        state=0;

#if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
    static GFX_COLOR      color;
    static uint8_t        val, shift;
    static uint16_t       bgcolor;

    if(pParam->bpp != 1)
    {
        if(pParam->bpp == 2)
        {
            restoremask = 0x03;
        }

        if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&bgcolor, cursorX, cursorY + (GFX_instance[0].currentFont.header.height >> 1), 1))
        {
             return(GFX_STATUS_FAILURE); //GetPixel not complete yet
        }

        if((_fgcolor100 != GFX_GetColor(0)) || (_bgcolor100 != bgcolor))
        {
            _fgcolor100 = GFX_GetColor(0);
            _bgcolor100 = bgcolor;
            calculateColors();
        }
    }
    else
    {
        restoremask = 0x01;
    }
#endif

    if(GFX_Primitive_instance.currentFont.orientation == GFX_ALIGN_HORIZONTAL_MASK)
    {
       if(!state)
       {
            y =  GFX_LinePositionYGet() + pParam->yAdjust;
            state = 1;
            yCnt=0;xCnt=0;
       }

switch(state)
{
case 1:
        while(yCnt < GFX_Primitive_instance.currentFont.header.height + pParam->heightOvershoot)
        {
            x =  GFX_LinePositionXGet() + pParam->xAdjust;
            mask = 0;

            #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
            shift = 0;
            #endif

            while(xCnt < pParam->chGlyphWidth)
            {
                if(mask == 0)
                {
                    temp = *(pParam->pChImage)++;
                    mask = restoremask;
                    #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                    shift = 0;
                    #endif
                }
                #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                if(pParam->bpp != 1)
                {
                    val = (temp & mask) >> shift;
                    if(val)
                    {
                        if(GFX_Font_GetAntiAliasType(0) == ANTIALIAS_TRANSLUCENT)
                        {
                             if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&bgcolor, cursorX, cursorY + (primitiveTaskFont.header.height >> 1), 1))
                             {
                                  return(GFX_STATUS_FAILURE); //GetPixel not complete yet
                             }
                            if(_bgcolor100 != bgcolor)
                            {
                                _bgcolor100 = bgcolor;
                                calculateColors();
                            }
                        }

                        switch(val)
                        {
                            case 1:     color = _fgcolor25;
                                        break;

                            case 2:     color = _fgcolor75;
                                        break;

                            case 3:     color = _fgcolor100;
                        }

                    state = 4;
 case 4:            GFX_DRV_instance[0].PrimitiveFunction.ColorSet(color);

                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(x,y))
                    {
                         return(1);
                    }

                    }
                }
                else
#endif
                if(temp & mask)
                {
                     state = 3;
case 3:             if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(x,y))
                    {
                         return(1);
                    }

                }

                mask <<= pParam->bpp;

                #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                shift  +=  pParam->bpp;
                #endif

                x++;
                xCnt++;
            }
            y++;
            yCnt++;
            xCnt=0;
        }
}
        // move cursor
         GFX_Primitive_instance.cursorX = x - pParam->xAdjust - pParam->xWidthAdjust;
    }
    else    // If extended glyph is used, then vertical alignment may not be rendered properly and hence users must position the texts properly
    {
       if(!state)
       {
            y =  GFX_Primitive_instance.cursorX + pParam->xAdjust;
            state = 1;
            yCnt=0;xCnt=0;
       }

        while(yCnt < GFX_Primitive_instance.currentFont.header.height + pParam->heightOvershoot)
        {
            x =  GFX_Primitive_instance.cursorY + pParam->yAdjust;
            mask = 0;
            #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
            shift = 0;
            #endif

            while(xCnt < pParam->chGlyphWidth)
            {
                if(mask == 0)
                {
                    temp = *(pParam->pChImage)++;
                    mask = restoremask;
                    #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                    shift = 0;
                    #endif
                }
                #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                if(pParam->bpp != 1)
                {
                    val = (temp & mask) >> shift;
                    if(val)
                    {
                        if(GFX_Font_GetAntiAliasType(0) == ANTIALIAS_TRANSLUCENT)
                        {
                            if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&bgcolor, cursorX, cursorY, 1))
                            {
                                 return(1); //GetPixel not complete yet
                            }
                            if(_bgcolor100 != bgcolor)
                            {
                                _bgcolor100 = bgcolor;
                                calculateColors();
                            }
                        }
                        switch(val)
                        {
                            case 1: color = _fgcolor25;
                                    break;

                            case 2: color = _fgcolor75;
                                    break;

                            case 3: color = _fgcolor100;
                        }

                        GFX_DRV_instance[0].PrimitiveFunction.ColorSet(color);
                        if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(y,x))
                        {
                            return(1);
                        }
                    }
                }
                else
#endif
                if(temp & mask)
                {
                    if(GFX_DRV_instance[0].PrimitiveFunction.PixelPut(y,x))
                    {
                         return(1);
                    }
                }

                mask <<= pParam->bpp;

                #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
                shift  +=  pParam->bpp;
                #endif
                x--;xCnt++;
            }
            y++;yCnt++;xCnt=0;
        }

        // move cursor
         GFX_Primitive_instance.cursorY = x - pParam->xAdjust;
    }
    state = 0;
    return (0);
}

/******************************************************************************
  Function:
    uint16_t GFX_TextCharPut(GFX_XCHAR ch)

  Summary:
    outputs a character.

  Description:
    For NON-Blocking configuration:
        - Returns 0 when device is busy and the character is not yet completely drawn.
      - Returns 1 when the character is completely drawn.
      For Blocking configuration:
        - Always return 1.

  Remarks:
*/
GFX_STATUS GFX_TextCharDraw(GFX_XCHAR ch)
{
    static GFX_FONT_OUTCHAR OutCharParam;
    static uint8_t state=0;
 
   if(!state)
   {
    // initialize variables
#if !defined GFX_CONFIG_FONT_EXTERNAL_DISABLE
        OutCharParam.pChImage = NULL;
    #endif
        OutCharParam.xAdjust = 0;
        OutCharParam.yAdjust = 0;
        OutCharParam.xWidthAdjust = 0;
        OutCharParam.heightOvershoot = 0;

        // check for error conditions (a return value of 0xFFFF means error)
        if((GFX_UXCHAR)ch < (GFX_UXCHAR)GFX_Primitive_instance.currentFont.header.firstChar)
             return (-1);
        if((GFX_UXCHAR)ch > (GFX_UXCHAR)GFX_Primitive_instance.currentFont.header.lastChar)
             return (-1);

     #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
        if(GFX_Primitive_instance.currentFont.header.bpp > 1)
             return (-1);
     #endif

         switch(*((short *)GFX_Primitive_instance.currentFont.pFont))
         {
     #if !defined GFX_CONFIG_FONT_FLASH_DISABLE
              //case GFX_RESOURCE_MEMORY_FLASH:
             case GFX_RESOURCE_FONT_FLASH_NONE:
                   OutCharGetInfoFlash(&GFX_Primitive_instance.currentFont, ch, &OutCharParam);
                   break;
     #endif
     #if !defined GFX_CONFIG_FONT_EXTERNAL_DISABLE
              case GFX_RESOURCE_MEMORY_EXTERNAL:
                   OutCharGetInfoExternal(ch, &OutCharParam);
              break;
     #endif        
              default:
                   return (1);
         }   
     state = 1;
     return(1);
     }     
    state = OutCharRender(ch, &OutCharParam); 
    return (state);

}

GFX_STATUS GFX_AlphaBlendingValueSet(uint16_t alpha)
{
    GFX_Primitive_instance.alphaArea.alpha = alpha;
}

uint16_t GFX_AlphaBlendingValueGet(void)
{
    return(GFX_Primitive_instance.alphaArea.alpha);
}

/******************************************************************************
  Function:
    GFX_STATUS GFX_TextStringXYPut(uint16_t x, uint16_t y, uint16_t width, uint16_t height, GFX_XCHAR* textString)

  Summary:
    outputs text from x,y position

  Description:

  Remarks:
*/
GFX_STATUS __attribute__((weak)) GFX_TextStringBoxDraw(uint16_t x, uint16_t y, uint16_t width, uint16_t height, GFX_XCHAR *textString, uint16_t length, GFX_ALIGNMENT align)
{

    static uint16_t counter = 0;
    static uint16_t x1,y1;
    static GFX_XCHAR  ch;
    static uint8_t state = 0;

    if(state == 0)
    {
            // Display text with center alignment
            if (align == GFX_ALIGN_HCENTER)
            {
                x1 = ((x << 1) + width - GFX_TextStringWidthGet(textString, GFX_Primitive_instance.currentFont.pFont)) >> 1;
            }
            // Display text with right alignment
            else if (align == GFX_ALIGN_RIGHT)
            {
                x1 = (x + width) - GFX_TextStringWidthGet(textString, GFX_Primitive_instance.currentFont.pFont);
            }
            else
            {
                x1 = x;
            }

             GFX_Primitive_instance.cursorX = x1;
             GFX_Primitive_instance.cursorY = y;

            y1 = GFX_TextStringHeightGet(GFX_Primitive_instance.currentFont.pFont);
            state = 1;

    }
    
                   ch = *((GFX_XCHAR*)textString + counter);

                   while ((GFX_UXCHAR) (ch != 0))
                   {

                     if (ch == '\n')
                     {
                        counter++;

                        // Display text with center alignment
                        if (align == GFX_ALIGN_HCENTER)
                        {
                            x1 = ((x << 1) + width - GFX_TextStringWidthGet((textString + counter), GFX_Primitive_instance.currentFont.pFont)) >> 1;
                        }
                        // Display text with right alignment
                        else if (align == GFX_ALIGN_RIGHT)
                        {
                            x1 = (x + width) - GFX_TextStringWidthGet( (textString + counter), GFX_Primitive_instance.currentFont.pFont);
                        }
                          GFX_Primitive_instance.cursorX = x1;
                          GFX_Primitive_instance.cursorY += y1;
                     }

                     ch = *((GFX_XCHAR*) textString + counter);

                     if (GFX_TextCharDraw(ch) != 0)
                     {
                        return(GFX_STATUS_FAILURE);
                     }

                       counter++;
                    }

                   counter = 0;
                   state = 0;
                   GFX_Primitive_instance.cursorX = x;
                   GFX_Primitive_instance.cursorY = y;

    return (GFX_STATUS_SUCCESS);
}

GFX_STATUS GFX_TextStringDraw(uint16_t x, uint16_t y, GFX_XCHAR *textString, uint16_t length)
{
    return(GFX_TextStringBoxDraw(x, y, 0, 0, textString, length, GFX_ALIGN_LEFT));
}

/******************************************************************************
  Function:
    WORD GFX_ImagePartialPut(uint16_t left, uint16_t top, void* image, BYTE stretch, uint16_t xoffset, uint16_t yoffset, WORD width, WORD height)

  Summary:
    outputs a full or a partial image starting from left,top coordinates.

  Description:
 left - horizontal starting position of full or partial image on the screen
        top - vertical starting position of full or partial image on the screen,
       image - pointer to the image location.
        stretch - The image stretch factor.
                  - IMAGE_NORMAL : no stretch
                  - IMAGE_X2 : image is stretched to twice
                    its width and height
        xoffset � Specifies the horizontal offset in pixels of the selected partial
                  image from the left most pixel of the full image.
        yoffset � Specifies the vertical offset in pixels of the selected partial
                 image from the top most pixel of the full image.
       width - width of the partial image to be rendered.
                xoffset + width must not exceed the full image width.
        height - height of the partial image to be rendered.
                 yoffset + height must not exceed the full image height.

 Output: For NON-Blocking configuration:
         - Returns 0 when device is busy and the image is not
           yet completely drawn.
         - Returns 1 when the image is completely drawn.
         For Blocking configuration:
         - Always return 1

  Remarks:
*/
GFX_STATUS GFX_ImagePartialDraw(uint16_t x, uint16_t y, uint16_t source_x_offset, uint16_t source_y_offset, uint16_t source_width, uint16_t source_height, GFX_RESOURCE_HDR *pImage)
{

    static uint8_gfx_image_prog *flashAddress;
    uint8_t        colorDepth;
    static uint8_t         functionIndex = 0;
    static uint16_t        resType;
    static uint8_t         commandCount = 0;

   if(!commandCount)
   {

    resType = *((uint16_t *)pImage);

    switch(resType & (GFX_MEM_MASK | GFX_COMP_MASK))
    {

       #if !defined GFX_CONFIG_RLE_DECODE_DISABLE
       #if !defined GFX_CONFIG_IMAGE_FLASH_DISABLE
        //case (FLASH | COMP_RLE):
        case (GFX_RESOURCE_MCHP_MBITMAP_FLASH_RLE):

            // Draw picture
            functionIndex = RLE;
            break;

       #endif //#ifdef USE_BITMAP_FLASH

                #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
        case (EXTERNAL | COMP_RLE):

            // Image address
            flashAddress = ((IMAGE_FLASH *)image)->address;

            // Draw picture
            functionIndex = RLE;

            break;
                #endif //#ifdef USE_BITMAP_EXTERNAL
                #endif // #ifdef USE_COMP_RLE

            #if !defined GFX_CONFIG_IMAGE_FLASH_DISABLE

        case (GFX_RESOURCE_MCHP_MBITMAP_FLASH_NONE):

            // Image address
            flashAddress = pImage->resource.image.location.progByteAddress;

            // Read color depth
            colorDepth = pImage->resource.image.colorDepth;

            // Draw picture
            switch(colorDepth)
            {
                case 1:
                functionIndex = _1BPP; break;

                    #if (GFX_CONFIG_COLOR_DEPTH >= 4)
                case 4:
                functionIndex = _4BPP; break;
                    #endif

                    #if (GFX_CONFIG_COLOR_DEPTH >= 8)
                case 8:
                functionIndex = _8BPP;
                break;
                    #endif

                    #if (GFX_CONFIG_COLOR_DEPTH == 16)
                case 16:
                functionIndex = _16BPP;
                break;
                    #endif

                default:    break;

            }

            break;
                #endif // #ifdef USE_BITMAP_FLASH

                #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

        case (EXTERNAL | COMP_NONE):

            // Get color depth
            ExternalMemoryCallback(image, 1, 1, &colorDepth);

            // Draw picture
            switch(colorDepth)
            {
                case 1:
                    functionIndex = _1BPP; break;

                    #if (GFX_CONFIG_COLOR_DEPTH >= 4)
                case 4:
                    functionIndex = _4BPP; break;
                    #endif

                    #if (GFX_CONFIG_COLOR_DEPTH >= 8)
                case 8:
                    functionIndex = _8BPP; break;
                    #endif

                    #if (GFX_CONFIG_COLOR_DEPTH == 16)
                case 16:
                    functionIndex = _16BPP; break;
                    #endif

                default:    break;
            }

            break;
                #endif //#ifdef USE_BITMAP_EXTERNAL

        default:
            break;
    }

      primitiveTaskImage.xoffset  = source_x_offset;
      primitiveTaskImage.yoffset  = source_y_offset;
      primitiveTaskImage.transparentColor  = GFX_Primitive_instance.currentColor;
      primitiveTaskImage.width = source_width;
      primitiveTaskImage.height = source_height;
      primitiveTaskImage.transparentFlag = 0;
      primitiveTaskImage.image = flashAddress;

      GFX_Primitive_instance.pResource = pImage;

      commandCount = 1;
 }

      if(PutImageTask[functionIndex](x,y) == GFX_STATUS_FAILURE)
            return(GFX_STATUS_FAILURE);

       commandCount = 0;
       return(GFX_STATUS_SUCCESS); //Wait for the task engine to complete
}

GFX_STATUS GFX_ImageDraw(uint16_t left,uint16_t top,GFX_RESOURCE_HDR *pImage)
{

    return(GFX_ImagePartialDraw(left,top,0,0,0,0,pImage));
}

void GFX_BevelDrawTypeSet(GFX_BEVEL_RENDER_TYPE type)
{
    GFX_Primitive_instance.bevelDrawType = type;
}


#if !defined GFX_CONFIG_IMAGE_FLASH_DISABLE || !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE

/******************************************************************************
  Function:
    uint8_t ImageArrayPut(uint8_t stretch, uint16_t left, uint16_t top, uint16_t hlength, uint16_t vlength, uint16_t *array)
  Summary:

  Description:

  Remarks:
*/
inline uint8_t ImageArrayPut(uint8_t stretch, uint16_t left, uint16_t top, uint16_t hlength, uint16_t vlength, uint16_t *array)
{
   static  uint16_t x = 0;
   static  uint16_t y = 0;
   static  uint16_t *driverIndex = NULL;
   static  uint8_t imageState = 0;

   switch(imageState)
   {
        case 0:
        driverIndex = array;
   if(primitiveTaskImage.transparentFlag == 1)
   {
       imageState = 1;

       while(y < (vlength*stretch))
       {
           
          // Write pixel(s) to screen
          while(x < (hlength*stretch))
          {
              if(*array != primitiveTaskImage.transparentColor)
              {
        case 1:
                    GFX_DRV_instance[0].PrimitiveFunction.PixelsPut(left + x , top + y, (stretch),(stretch));
              }
              array++;  //move index of array
              x += (stretch);
          }
          
          y += (stretch);
       }
       break;
   }
        imageState = 2;
         // Write pixel(s) to screen
   while(x < stretch)
   { 

       case 2:
        driverIndex = GFX_DRV_instance[0].PrimitiveFunction.PixelArrayPut(array, left, top+x ,hlength, vlength);
        if(driverIndex == NULL) 
        {
             return(GFX_STATUS_FAILURE); //Buffer must have been full
        }
        imageState = 3;
 
        case 3:
            if(*driverIndex != 0) return(GFX_STATUS_FAILURE);
     imageState = 2;
     x++;
   } 

   }
   x = 0;
   imageState = 0;
   return(GFX_STATUS_SUCCESS);

}

/******************************************************************************
  Function:
    uint16_t Image1BPP(uint16_t left, uint16_t top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)

  Summary:

  Description:

  Remarks:
*/

uint16_t __attribute__((weak)) Image1BPP(uint16_t left, uint16_t top)
{
    static uint8_gfx_image_prog *flashAddress, *tempFlashAddress;
    static uint8_t                 temp = 0;
    static uint16_t                sizeX, sizeY, lineLength;
    static uint16_t                x, y;
    static uint16_t                yc;
    static uint16_t                mask;
    static uint16_t                OffsetFlag = 0x01;     //Offset from BYTE color bit0 for the partial image
    static uint8_t                 state =0;
    static uint32_t                memOffset;
    static GFX_MCHP_BITMAP_HEADER           bmp;
    static uint16_t                *pixel;
    static uint8_gfx_image_prog                 *pData;
    static short                   byteWidth;
    GFX_RESOURCE_HDR             * pImage;

    pImage = GFX_Primitive_instance.pResource;

if(!state)
{
    // Move pointer to size information
    flashAddress = primitiveTaskImage.image;

         #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
        if(((*primitiveTaskImage.image) & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_NONE))
        {
        // Get image header
        ExternalMemoryCallback(primitiveTaskImage.image, 0, sizeof(BITMAP_HEADER), &bmp);

        // Get pallete (16 entries)
        ExternalMemoryCallback(primitiveTaskImage.image, sizeof(BITMAP_HEADER), 16 * sizeof(WORD), primitiveTaskImage.palette);

        // Set offset to the image data
        flashAddress += sizeof(BITMAP_HEADER) + 16 * sizeof(WORD);

        memOffset = 1;
    }
    else
    #endif
    {

    // Read image size
    bmp.height = pImage->resource.image.height;
    bmp.width = pImage->resource.image.width;

    primitiveTaskImage.palette[0] = *((uint16_t *)flashAddress);
    flashAddress += 2;
    primitiveTaskImage.palette[1] = *((uint16_t *)flashAddress);
    flashAddress += 2;

    }
    // Line width in bytes
    byteWidth = (bmp.width >> 3);
    if(bmp.width & 0x07)
        byteWidth++;

    if(primitiveTaskImage.width != 0)
    {

         flashAddress += primitiveTaskImage.yoffset*byteWidth;
         flashAddress += (primitiveTaskImage.xoffset)>>3;

         OffsetFlag <<= ((primitiveTaskImage.xoffset) & 0x07);

         sizeY = primitiveTaskImage.height;
         sizeX = primitiveTaskImage.width;
    }
    else
    {
        // Get size
        sizeX = bmp.width;
        sizeY = bmp.height;
    }

    yc = top;
    y = 0;

    // store current line data address
    tempFlashAddress = flashAddress;

    if(memOffset)
    {
         memOffset = (uint8_gfx_image_prog*)flashAddress - primitiveTaskImage.image;

        // calculate the length of bytes needed per line
        lineLength = (sizeX >> 3) + 1;
        if (sizeX & 0x07)
           lineLength++;
    }

    state = 1;
}

switch(state)
{

case 1:

        while(y < sizeY)
        {

          pixel = &GFX_Primitive_instance.line[0];

     #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
         if(memOffset)
         {
          // Get line
          ExternalMemoryCallback(primitiveTaskImage.image, memOffset, lineLength, primitiveTaskImage.line[0]);
          memOffset += byteWidth;
          tempFlashAddress = (uint8_t*)&primitiveTaskImage.line[0];
         }
     #endif
          pData = tempFlashAddress;
          mask = OffsetFlag;
          temp = *pData++;

         // Note: For speed the code for loops are repeated. A small code size increase for performance
         if (primitiveTaskImage.stretch == IMAGE_NORMAL)
         {
            for(x = 0; x < sizeX; x++)
            {
                // Set color
                if(mask & temp)
                {
                // Set color
                    #ifndef GFX_CONFIG_PALETTE_DISABLE
                        *pixel++ = 1;
                    #else
                        *pixel++ = primitiveTaskImage.palette[1];
                    #endif
                }
                else
                {
                    // Set color
                    #ifndef GFX_CONFIG_PALETTE_DISABLE
                        *pixel++ = 0;
                    #else
                        *pixel++ = primitiveTaskImage.palette[0];
                    #endif
                }

                               // Read 8 pixels from flash
                if(mask == 0x80)
                {
                    temp = *pData++;
                    mask = 0x01;
                }
                else
                {
                    // Shift to the next pixel
                    mask <<= 1;
                }
            }
        }
    else
    {
            for(x = 0; x < sizeX; x++)
            {
                    // Set color
                if(mask & temp)
                {
                    // Set color
                    #ifndef GFX_CONFIG_PALETTE_DISABLE
                        *pixel++ = 1;
                        *pixel++ = 1;
                    #else
                        *pixel++ = primitiveTaskImage.palette[1];
                        *pixel++ = primitiveTaskImage.palette[1];
                    #endif
                }
                else
                {
                    // Set color
                    #ifndef GFX_CONFIG_PALETTE_DISABLE
                        *pixel++ = 0;
                        *pixel++ = 0;
                    #else
                        *pixel++ = primitiveTaskImage.palette[0];
                        *pixel++ = primitiveTaskImage.palette[0];
                    #endif
                }

                // Read 8 pixels from flash
                if(mask == 0x80)
                {
                    temp = *pData++;
                    mask = 0x01;
                }
                else
                {
                    // Shift to the next pixel
                    mask <<= 1;
                }
            }
     }

          state = 2;
case 2:   if(ImageArrayPut(primitiveTaskImage.stretch, left, yc, sizeX*primitiveTaskImage.stretch,1 , &GFX_Primitive_instance.line[0]) == GFX_STATUS_FAILURE)
          return(GFX_STATUS_FAILURE);

            y++;
            tempFlashAddress += byteWidth;
            yc += primitiveTaskImage.stretch;
    }
}
state = 0;
return (GFX_STATUS_SUCCESS);
}

/******************************************************************************
  Function:
    uint16_t Image4BPP(uint16_t left, uint16_t top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)

  Summary:
    outputs 16 color image starting from left,top coordinates

  Description:

  Remarks:
  Note: image must be located in flash
*/
#if (GFX_CONFIG_COLOR_DEPTH >= 4)

uint16_t __attribute__((weak)) Image4BPP(uint16_t left, uint16_t top)
{
    static uint8_gfx_image_prog *flashAddress;
    static uint16_t                sizeX, sizeY;
    static uint16_t                x, y, lineLength;
    static uint16_t                yc;
    static uint8_t                 temp = 0;
    static uint16_t                counter;
    static uint16_t                addressOffset = 0;
    static uint8_t                 state=0;
    static uint32_t                memOffset;
    static short byteWidth;        //External Memory
    static GFX_MCHP_BITMAP_HEADER           bmp;
    static uint16_t                nibbleOffset = 0; 
    static uint16_t                *pixel;
    GFX_RESOURCE_HDR             * pImage;

    pImage = GFX_Primitive_instance.pResource;

    if(!state)
    {
         // Move pointer to size information
         flashAddress = primitiveTaskImage.image;

         #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
        if(((*primitiveTaskImage.image) & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_NONE))
        {
        // Get image header
        ExternalMemoryCallback(primitiveTaskImage.image, 0, sizeof(BITMAP_HEADER), &bmp);

        // Get pallete (16 entries)
        ExternalMemoryCallback(primitiveTaskImage.image, sizeof(BITMAP_HEADER), 16 * sizeof(WORD), primitiveTaskImage.palette);

        // Set offset to the image data
        flashAddress += sizeof(BITMAP_HEADER) + 16 * sizeof(WORD);

        memOffset = 1;
    }
    else
    #endif
    {
         memOffset = 0;

         // Read image size
        bmp.height = pImage->resource.image.height;
        bmp.width = pImage->resource.image.width;
    
         // Read pallete
         for(counter = 0; counter < 16; counter++)
         {
              primitiveTaskImage.palette[counter] = *((uint16_gfx_image_prog *)flashAddress);
              flashAddress += 2;
         }
   }

     // Line width in bytes
    byteWidth = (bmp.width) >> 1;

    if(primitiveTaskImage.width != 0)
    {
        // check the bit position of the starting pixel
        nibbleOffset = primitiveTaskImage.xoffset & 0x01;

        memOffset += (primitiveTaskImage.yoffset)*byteWidth;
        memOffset += (primitiveTaskImage.xoffset) >> 1;

        sizeY = primitiveTaskImage.height;
        sizeX = primitiveTaskImage.width;
    }
    else
    {
        // Get size
        sizeX = bmp.width;
        sizeY = bmp.height;
    }

    if(memOffset)
    {
         memOffset = (uint8_gfx_image_prog*)flashAddress - primitiveTaskImage.image;
    }

    lineLength = (sizeX >> 1) + 1;
    if (sizeX & 0x01)
    lineLength++;

    yc = top;
    y = 0;
    state = 1;
    }

     switch(state)
     {
         case 1:
         while(y < sizeY)
         {

             #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
            if(memOffset)
            {
                ExternalMemoryCallback(primitiveTaskImage.image, memOffset, lineLength, primitiveTaskImage.line[0]);
                memOffset += byteWidth;
                flashAddress = &primitiveTaskImage.line[0];
            }
            #endif

            pixel = &GFX_Primitive_instance.line[0];

            temp = *flashAddress;
            flashAddress += nibbleOffset;

          // Note: For speed the code for loops are repeated. A small code size increase for performance
          if (primitiveTaskImage.stretch == IMAGE_NORMAL)
          {
                    for(x = nibbleOffset; x < (sizeX+nibbleOffset); x++)
                    {
                         // Read 2 pixels from flash
                         if(x & 0x01)
                         {
                              // second pixel in byte
                             // Set color
                             #ifndef GFX_CONFIG_PALETTE_DISABLE
                             *pixel++ = temp >> 4;
                             #else
                             *pixel++ = primitiveTaskImage.palette[temp >> 4];
                             #endif
                         }
                         else
                         {
                              temp = *flashAddress++;
                              // first pixel in byte
                             // Set color
                             #ifndef GFX_CONFIG_PALETTE_DISABLE
                             *pixel++ = temp & 0x0f;
                             #else
                             *pixel++ = primitiveTaskImage.palette[temp & 0x0f];
                             #endif
                          }
                    }  
        }
       else
      {
            for(x = nibbleOffset; x < (sizeX+nibbleOffset); x++)
            {

               if(x & 0x01)
               {
                // second pixel in byte
                // Set color
                #ifndef GFX_CONFIG_PALETTE_DISABLE
                    *pixel++ = temp >> 4;
                    *pixel++ = temp >> 4;
                #else
                    *pixel++ = primitiveTaskImage.palette[temp >> 4];
                    *pixel++ = primitiveTaskImage.palette[temp >> 4];
                #endif
                }
                else
                {
                    temp = *flashAddress++;

                // first pixel in byte
                // Set color
                #ifndef GFX_CONFIG_PALETTE_DISABLE
                    *pixel++ = temp & 0x0f;
                    *pixel++ = temp & 0x0f;
                #else
                    *pixel++ = primitiveTaskImage.palette[temp & 0x0f];
                    *pixel++ = primitiveTaskImage.palette[temp & 0x0f];
                #endif
                }
            }
     }

          state = 2;
case 2:   if(ImageArrayPut(primitiveTaskImage.stretch, left, yc, sizeX*primitiveTaskImage.stretch,1, &GFX_Primitive_instance.line[0]) == GFX_STATUS_FAILURE)
          return(GFX_STATUS_FAILURE);

            y++;
            flashAddress += addressOffset;         
            yc += primitiveTaskImage.stretch;  
    }
}
     state = 0;
     return(GFX_STATUS_SUCCESS); //Renderring Complete
}
#endif
// #if (GFX_CONFIG_COLOR_DEPTH >= 4)
/******************************************************************************
  Function:
    uint16_t Image8BPP(uint16_t left, uint16_t top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)

  Summary:
    outputs 256 color image starting from left,top coordinates

  Description:

  Remarks:
  Note: image must be located in flash
*/
#if (GFX_CONFIG_COLOR_DEPTH >= 8)

uint16_t __attribute__((weak)) Image8BPP(uint16_t left, uint16_t top)
{
    static uint8_gfx_image_prog              *flashAddress;
    static uint16_t                sizeX, sizeY;
    static uint16_t                x, y;
    static uint16_t                yc;
    static uint16_t                counter;
    static uint16_t                addressOffset = 0;
    static uint8_t                 state=0; 
    static uint8_t                 stretch;
    static uint32_t                memOffset;
    static uint16_t                *pixel;
    static GFX_MCHP_BITMAP_HEADER           bmp;
    GFX_RESOURCE_HDR             * pImage;

    pImage = GFX_Primitive_instance.pResource;

if(!state)
{
    // Move pointer to size information
    flashAddress = primitiveTaskImage.image;

    #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
    if(((*primitiveTaskImage.image) & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_NONE))
    {
       // Get image header
       ExternalMemoryCallback(primitiveTaskImage.image, 0, sizeof(BITMAP_HEADER), &bmp);

       // Get pallete (256 entries)
       ExternalMemoryCallback(image, sizeof(BITMAP_HEADER), 256 * sizeof(WORD), pallete);

       // Set offset to the image data
       memOffset = sizeof(BITMAP_HEADER) + 256 * sizeof(WORD);

       // Set offset to the image data
       flashAddress += sizeof(BITMAP_HEADER) 256 * sizeof(WORD);
       memOffset = 1;
    }
    else
    #endif
    {
 
    memOffset = 0; //No external memory

     // Read image size
    bmp.height = pImage->resource.image.height;
    bmp.width = pImage->resource.image.width;

    // Read pallete
    for(counter = 0; counter < 256; counter++)
    {
        primitiveTaskImage.palette[counter] = *((uint16_gfx_image_prog *)flashAddress);
        flashAddress += 2;
    }
    }

    if(primitiveTaskImage.width != 0)
    {
         flashAddress += primitiveTaskImage.xoffset + primitiveTaskImage.yoffset*(bmp.width);
         addressOffset = bmp.width - primitiveTaskImage.width;
         sizeY = primitiveTaskImage.height;
         sizeX = primitiveTaskImage.width;
    }
    else
    {
        // Get size
        sizeX = bmp.width;
        sizeY = bmp.height;
    }

    stretch = primitiveTaskImage.stretch;
    yc = top;
    state = 1;
    y=0;

    if(memOffset)
    {
         memOffset = (uint8_gfx_image_prog*)flashAddress - primitiveTaskImage.image;
    }

}

switch(state)
{
case 1:
        while(y < sizeY)
        {

            #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
            if(((*primitiveTaskImage.image) & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_NONE))
            {
               ExternalMemoryCallback(primitiveTaskImage.image, memOffset, (bmp.width), primitiveTaskImage.line[0]);
               memOffset += (bmp.width);
               flashAddress = &primitiveTaskImage.line[0];
            }
            #endif

           pixel = &GFX_Primitive_instance.line[0];

           if(stretch != IMAGE_NORMAL)
           { 
                for(x = 0; x < (sizeX); x++)
                {
                // Set color
                #ifdef GFX_CONFIG_PALETTE_DISABLE
                    *pixel++ = primitiveTaskImage.palette[*flashAddress];
                    *pixel++ = primitiveTaskImage.palette[*flashAddress++];  
                #endif
                }
           }
          else
          {
                for(x = 0; x < (sizeX); x++)
                {
                // Set color
                #ifdef GFX_CONFIG_PALETTE_DISABLE
                    *pixel++ = primitiveTaskImage.palette[*flashAddress++];      
                #endif
                }
          }
          state = 2;
case 2:   if(ImageArrayPut(stretch, left, yc, sizeX*stretch,1, &GFX_Primitive_instance.line[0]) == GFX_STATUS_FAILURE)
          return(GFX_STATUS_FAILURE);
            y++;
            flashAddress += addressOffset;         
            yc += stretch;
        }
}
state = 0;
return(GFX_STATUS_SUCCESS);
}
        #endif // #if (GFX_CONFIG_COLOR_DEPTH >= 8)

/******************************************************************************
  Function:
    uint16_t Image16BPP(uint16_t left, uint16_t top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)

  Summary:
    outputs hicolor image starting from left,top coordinates

  Description:

  Remarks:
      Note: image must be located in flash
*/

uint16_t __attribute__((weak)) Image16BPP(uint16_t left, uint16_t top)
{
#if (GFX_CONFIG_COLOR_DEPTH >= 16)

    static uint16_gfx_image_prog   *flashAddress;
    static uint16_gfx_image_prog   *tempflashAddress;
    static uint16_t     sizeX, sizeY;
    static uint16_t     x, y;
    static uint16_t     yc;
    static uint16_t     addressOffset = 0;
    static uint8_t      state = 0;
    static GFX_MCHP_BITMAP_HEADER       bmp;
    static uint32_t     memOffset;
    static uint16_t     *pixel;
    GFX_RESOURCE_HDR             * pImage;

    pImage = GFX_Primitive_instance.pResource;

if(!state)
{

    // Move pointer to size information
    flashAddress = (uint16_gfx_image_prog *)primitiveTaskImage.image;

    #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
    if(((*primitiveTaskImage.image) & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_NONE))
    {
       // Get image header
       ExternalMemoryCallback(image, 0, sizeof(BITMAP_HEADER), &bmp);

       // Set offset to the image data
       flashAddress += sizeof(BITMAP_HEADER);
       memOffset = 1;
    }
    else
    #endif
    {

     // Read image size
    bmp.height = pImage->resource.image.height;
    bmp.width = pImage->resource.image.width;

    memOffset = 0; //No external memory
    }
    if(primitiveTaskImage.width != 0)
    {
         flashAddress += primitiveTaskImage.xoffset + primitiveTaskImage.yoffset *(bmp.width);
         sizeY = primitiveTaskImage.height;
         sizeX = primitiveTaskImage.width;
    }
    else
    {
         sizeX = bmp.width;
         sizeY = bmp.height;
    }
  
    addressOffset = bmp.width;
    yc = top;
    state = 1;

    if(memOffset)
    {
         memOffset = (uint8_gfx_image_prog*)flashAddress - primitiveTaskImage.image;
    }

}

switch(state)
{
case 1:
    // Note: For speed the code for loops are repeated. A small code size increase for performance
    if ((primitiveTaskImage.stretch == IMAGE_NORMAL) && (primitiveTaskImage.transparentFlag == 0))
    {
        for(y = 0; y < sizeY; y++)
        {  
            #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
            if(memOffset != 0)
            {
               ExternalMemoryCallback(primitiveTaskImage.image, memOffset, (bmp.width << 1), primitiveTaskImage.line[0]);
               memOffset += (bmp.width << 1);
               flashAddress = &primiti veTaskImage.line[0];
            }
            #endif

                       // Write pixel(s) to screen
                       state = 4;

  case 4:              if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayPut((uint16_t*)flashAddress,left,yc,sizeX, 1) == NULL)
                       {
                            return(GFX_STATUS_FAILURE);
                       } 
       
                       flashAddress += addressOffset;  
                       yc++;
        }
    }
    else
    {
        for(y = 0; y < sizeY; y++)
        {

            #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
            if(memOffset != 0)
            {
               ExternalMemoryCallback(primitiveTaskImage.image, memOffset, (bmp.width << 1), primitiveTaskImage.line[0]);
               memOffset += (bmp.width << 1);
               flashAddress = &primitiveTaskImage.line[0];
            }
            #endif

            tempflashAddress = flashAddress;
            pixel = &GFX_Primitive_instance.line[0];

            for(x = 0; x < sizeX; x++)
            {             
                *pixel++ = *tempflashAddress; 
                *pixel++ = *tempflashAddress++; 
            }   

          state = 2;
case 2:   if(ImageArrayPut(primitiveTaskImage.stretch, left, yc, sizeX*primitiveTaskImage.stretch,1, &GFX_Primitive_instance.line[0]) == GFX_STATUS_FAILURE)
          return(GFX_STATUS_FAILURE);

           flashAddress += addressOffset;      
           yc += (primitiveTaskImage.stretch);
    }  
    }
}
state = 0; 
#endif //#if (GFX_CONFIG_COLOR_DEPTH == 16)
return(GFX_STATUS_SUCCESS);
}
    #endif // #ifdef USE_BITMAP_FLASH


     #if !defined GFX_CONFIG_RLE_DECODE_DISABLE
     #if !defined GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
    
        #if (GFX_CONFIG_COLOR_DEPTH >= 8)

/*********************************************************************
* Function: WORD DecodeRLE8Ext(DWORD  memAddress, BYTE *pixelrow, WORD size)
*
* PreCondition: tempFlashAddress should point to the beginning of a RLE compressed block
*
* Input: image - External memory image pointer
*        memAddress - Address of the beginning of a RLE compressed block
*        pixelrow - Pointer to an array where the decoded row must be stored
*        size - Size of the decoded data in bytes
*
* Output: Number of source bytes traversed
*
* Side Effects: none
*
* Overview: Decodes the data from the external flash
*
********************************************************************/
uint16_t DecodeRLE8Ext(FLASH_BYTE *flashAddress, uint8_t *pixel_row, uint16_t size)
{
    uint16_t sourceOffset = 0;
    uint16_t decodeSize = 0;
    uint32_t memAddress = flashAddress - primitiveTaskImage.image;

    while(decodeSize < size)
    {
        uint8_t code, value;
        
        ExternalMemoryCallback(primitiveTaskImage.image, memAddress, sizeof(uint8_t), &code);
        memAddress++;
        ExternalMemoryCallback(primitiveTaskImage.image, memAddress, sizeof(uint8_t), &value);
        memAddress++;

        sourceOffset += 2;
        
        if(code > 0)
        {
            decodeSize += code;
            
            if(decodeSize > size) //To avoid writing oustide the array bounds
            {
                code -= (decodeSize - size);
            }
            
            while(code)
            {
                *pixel_row++ = value;
                code--;
            }
        }
        else
        {
            decodeSize += value;
            sourceOffset += value;
            
            if(decodeSize > size) //To avoid writing oustide the array bounds
            {
                value -= (decodeSize - size);
            }
            
            ExternalMemoryCallback(primitiveTaskImage.image, memAddress, value * sizeof(BYTE), pixel_row);
            pixel_row += value;
            memAddress += value;
        }
    }    
    return (sourceOffset);
}
 #endif

        #if (GFX_CONFIG_COLOR_DEPTH >= 4)

/*********************************************************************
* Function: WORD DecodeRLE4Ext(void *image, DWORD memAddress, BYTE *pixelrow, WORD size)
*
* PreCondition: tempFlashAddress should point to the beginning of a RLE compressed block
*
* Input: image - External memory image pointer
*        memAddress - Address of the beginning of a RLE compressed block
*        pixelrow - Pointer to an array where the decoded row must be stored
*        size - Size of the decoded data in bytes
*
* Output: Number of source bytes traversed
*
* Side Effects: none
*
* Overview: Decodes the data
*
********************************************************************/
uint16_t DecodeRLE4Ext(FLASH_BYTE *flashAddress, uint8_t *pixel_row, uint16_t size)
{
    uint16_t sourceOffset = 0;
    uint16_t decodeSize = 0;
    uint32_t memAddress = flashAddress - primitiveTaskImage.image;

    while(decodeSize < size)
    {
        uint8_t code, value;
        uint8_t counter, temp;
        
        ExternalMemoryCallback(primitiveTaskImage.image, memAddress, sizeof(BYTE), &code);
        memAddress++;
        ExternalMemoryCallback(primitiveTaskImage.image, memAddress, sizeof(BYTE), &value);
        memAddress++;
        
        sourceOffset += 2;
        
        if(code > 0)
        {
            decodeSize += code;
            
            if(decodeSize > size) //To avoid writing oustide the array bounds
            {
                code -= (decodeSize - size);
            }
            
            for(counter = 0; counter < code; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = (value >> 4) & 0x0F;
                }
                else
                {
                    *pixel_row++ = (value) & 0x0F;
                }
            }
        }
        else
        {
            decodeSize += value;
            sourceOffset += (value + 1) >> 1;
            
            if(decodeSize > size) //To avoid writing oustide the array bounds
            {
                value -= (decodeSize - size);
            }
            
            for(counter = 0; counter < value; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = (temp >> 4) & 0x0F;
                    memAddress++;
                }
                else
                {
                    ExternalMemoryCallback(primitiveTaskImage.image, memAddress, sizeof(BYTE), &temp);
                    *pixel_row++ = temp & 0x0F;
                }
            }
        }
    }

    return (sourceOffset);
}
#endif // 4BPP
#endif //EXTERNAL

    #if !defined GFX_CONFIG_IMAGE_FLASH_DISABLE

        #if (GFX_CONFIG_COLOR_DEPTH >= 4)
        
/*********************************************************************
* Function: WORD DecodeRLE4(FLASH_BYTE *flashAddress, BYTE *pixelrow, WORD size)
*
* PreCondition: tempFlashAddress should point to the beginning of a RLE compressed block
*
* Input: flashAddress - Address of the beginning of a RLE compressed block
*        pixelrow - Pointer to an array where the decoded row must be stored
*        size - Size of the decoded data in bytes
*
* Output: Number of source bytes traversed
*
* Side Effects: none
*
* Overview: Decodes the data
*
********************************************************************/
uint16_t DecodeRLE4(uint8_gfx_image_prog *flashAddress, uint16_t *pixel_row, uint16_t size)
{
    uint16_t sourceOffset = 0;
    uint16_t decodeSize = 0;
    uint8_t  code;
    uint8_t  counter;

if(primitiveTaskImage.stretch == IMAGE_NORMAL)
{
    while(decodeSize < size)
    {
        code = *flashAddress++;

        sourceOffset += 2;

        if(code > 0)
        {

            decodeSize += code;

            for(counter = 0; counter < code; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress >> 4) & 0x0F];
                }
                else
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress) & 0x0F];
                }
            }

         flashAddress++;
        }
        else
        {
            code = *flashAddress++;
            decodeSize += code;
            sourceOffset += (code) >> 1;

            for(counter = 0; counter < code; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress >> 4) & 0x0F];
                    flashAddress++;
                }
                else
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress) & 0x0F];
                }
            }
        }
    }
}
else
{
    while(decodeSize < size)
    {
        code = *flashAddress++;

        sourceOffset += 2;

        if(code > 0)
        {

            decodeSize += code;

            for(counter = 0; counter < code; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress >> 4) & 0x0F];
                }
                else
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress) & 0x0F];
                }

                *pixel_row = *(pixel_row - 1);
                pixel_row++;
            }
         flashAddress++;
        }
        else
        {
            code = *flashAddress++;
            decodeSize += code;
            sourceOffset += (code) >> 1;

            for(counter = 0; counter < code; counter++)
            {
                if(counter & 0x01)
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress >> 4) & 0x0F];
                    flashAddress++;
                }
                else
                {
                    *pixel_row++ = primitiveTaskImage.palette[(*flashAddress) & 0x0F];
               }

                *pixel_row = *(pixel_row - 1);
                pixel_row++;
            }
        }
    }
}
    return (sourceOffset);
}
#endif //GFX_CONFIG_COLOR_DEPTH == 4
#if (GFX_CONFIG_COLOR_DEPTH >= 8)
/*********************************************************************
* Function: uint16_t DecodeRLE8(FLASH_BYTE *flashAddress, uint8_t *pixelrow, uint16_t size)
*
* PreCondition: tempFlashAddress should point to the beginning of a RLE compressed block
*
* Input: flashAddress - Address of the beginning of a RLE compressed block
*        pixelrow - Pointer to an array where the decoded row must be stored
*        size - Size of the decoded data in bytes
*
* Output: Number of source bytes traversed
*
* Side Effects: none
*
* Overview: Decodes the data
*
********************************************************************/
uint16_t DecodeRLE8(uint8_gfx_image_prog *flashAddress, uint16_t *pixel_row, uint16_t size)
{
    uint16_t sourceOffset = 0;
    uint16_t decodeSize = 0;

if(primitiveTaskImage.stretch == IMAGE_NORMAL)
{
    while(decodeSize < size)
    {
        uint8_t code = *flashAddress++;
        uint8_t value = *flashAddress++;
        sourceOffset += 2;

        if(code > 0)
        {
            decodeSize += code;

            while(code)
            {
                *pixel_row++ = primitiveTaskImage.palette[value];
                code--;
            }
        }
        else
        {
            decodeSize += value;
            sourceOffset += value;

            while(value)
            {
                *pixel_row++ = primitiveTaskImage.palette[*flashAddress++];
                value--;
            }
        }
    }
}
else
{
    while(decodeSize < size)
    {
        uint8_t code = *flashAddress++;
        uint8_t value = *flashAddress++;
        sourceOffset += 2;

        if(code > 0)
        {
            decodeSize += code;

            while(code)
            {
                *pixel_row++ = primitiveTaskImage.palette[value];
                *pixel_row = *(pixel_row-1);
                 pixel_row++;
                code--;
            }
        }
        else
        {
            decodeSize += value;
            sourceOffset += value;

            while(value)
            {
                *pixel_row++ = primitiveTaskImage.palette[*flashAddress++];
                *pixel_row = *(pixel_row-1);
                pixel_row++;
                value--;
            }
        }
    }
}
    return (sourceOffset);
}
    #endif //    #ifdef (GFX_CONFIG_COLOR_DEPTH >= 8)
        #endif //#if EXTERNAL
/*********************************************************************
* Function: uint16_t ImageRLE(uint16_t left, uint16_t top)
*
* PreCondition: none
*
* Input: left,top - left top image corner, image - image pointer,
*        stretch - Should be NORMAL when RLE is used
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs the image starting from left,top coordinates
*
* Note: image must be located in internal memory
*
********************************************************************/
uint16_t ImageRLE(uint16_t left, uint16_t top)
{
    static uint8_gfx_image_prog   *flashAddress;
    static uint8_gfx_image_prog   *tempFlashAddress;
    static uint16_t     sizeX, sizeY;
    static uint16_t     y;
    static uint16_t     yc;
    static uint8_t      stretchY;
    static uint16_t     counter;
    static uint16_t     offset;
    static uint8_t      state = 0;
    static uint8_t      stretch = 0;
    static uint16_t     colorDepth = 0;
    GFX_RESOURCE_HDR             * pImage;

    pImage = GFX_Primitive_instance.pResource;

if(!state)
{

    // Read color depth
    colorDepth = pImage->resource.image.colorDepth;
/*
    if((pimghdr & (GFX_MEM_MASK | GFX_COMP_MASK)) == (EXTERNAL | COMP_RLE))
    {
        // Get image header
        ExternalMemoryCallback(primitiveTaskImage.image, 0, sizeof(BITMAP_HEADER), &bmp);

        // Get pallete (16 entries)
        ExternalMemoryCallback(primitiveTaskImage.image, sizeof(BITMAP_HEADER), (1<<colorDepth) * sizeof(WORD), pallete);

        // Set offset to the image data
        memOffset = sizeof(BITMAP_HEADER) + (1<<colorDepth) * sizeof(WORD);

        // Get size
        sizeX = bmp.width;
        sizeY = bmp.height;

        if(colorDepth == 4)
        {
            Decode = DecodeRLE4Ext; 
        }
        else
        {
            Decode = DecodeRLE8Ext;
        }
    }
    else
    {*/
        // Move pointer to size information
        flashAddress = (uint8_gfx_image_prog*)pImage->resource.image.location.progByteAddress;

        // Read image size
        sizeY = pImage->resource.image.height;
        sizeX = pImage->resource.image.width;

        #if GFX_CONFIG_COLOR_DEPTH == 24
        flashAddress += 2;          // pad for alignment
        #endif

        // Read pallete
        for(counter = 0; counter < (1 << colorDepth); counter++)
        {
            #if GFX_CONFIG_COLOR_DEPTH == 16
            primitiveTaskImage.palette[counter] = *((uint16_gfx_image_prog *)flashAddress);
            flashAddress += 2;
            #endif

            #if GFX_CONFIG_COLOR_DEPTH == 24
            primitiveTaskImage.palette[counter] = *((uint32_gfx_image_prog *)flashAddress);
            flashAddress += 4;
            #endif
        }
 
        if(colorDepth == 4)
        {
            DecodeRLE = &DecodeRLE4; 
        }
        else
        {
            DecodeRLE = &DecodeRLE8;
        }

  //  } 

    yc = top;
    tempFlashAddress = flashAddress;
    state = 1;
    stretch = primitiveTaskImage.stretch;
}

switch(state)
{
case 1:
    for(y = 0; y < sizeY; y++)
    {
        offset = DecodeRLE(tempFlashAddress, &GFX_Primitive_instance.line[0], sizeX);

        tempFlashAddress += offset;

        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
          state = 2;
          case 2:   if(ImageArrayPut(stretch, left, yc, sizeX*stretch,1, &GFX_Primitive_instance.line[0]) == GFX_STATUS_FAILURE)
          return(GFX_STATUS_FAILURE);

            yc++;
       }
    }
}

state = 0;
return(GFX_STATUS_SUCCESS);
}
#endif //IMAGE RLE

#ifndef GFX_CONFIG_GRADIENT_DISABLE
GFX_STATUS GFX_GradientColorSet(
                                GFX_COLOR startColor,
                                GFX_COLOR endColor)
{

    GFX_Primitive_instance.gradientStyle.startColor = startColor;
    GFX_Primitive_instance.gradientStyle.endColor = endColor;
    GFX_Primitive_instance.gradientStyle.length = 100;
    return(GFX_STATUS_SUCCESS);
}


GFX_STATUS  GFX_BarGradientDraw(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{

    static uint16_t startRed, startBlue, startGreen;
    static uint16_t endRed, endBlue, endGreen;
    static uint8_t  state = 0;
    static GFX_COLOR startColor, endColor;
    static long rdiff=0,gdiff=0,bdiff=0;
    static short i,steps;
    static int16_t cTop,cRight,cLeft,cBottom;
    static uint16_t length = 100;
    
switch(state)
{

case 0:
    cLeft = left;
    cRight = right;
    cTop = top;
    cBottom = bottom;
    length = GFX_Primitive_instance.gradientStyle.length;
    startColor = GFX_Primitive_instance.gradientStyle.startColor;
    endColor = GFX_Primitive_instance.gradientStyle.endColor;

    GFX_DRV_instance[0].PrimitiveFunction.ColorSet(endColor);
    // if length is 100, why waste the bar call?
    switch(GFX_Primitive_instance.gradientStyle.type)
    {
    case GFX_FILL_STYLE_GRADIENT_UP:
        length = length * (bottom - top);
        length /= 100;
        steps = length;
        if(GFX_RectangleFillDraw(left,top,right,bottom-steps) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

    case GFX_FILL_STYLE_GRADIENT_DOWN:
        length = length * (bottom - top); 
        length /= 100; 
        steps = length;    
        if(GFX_RectangleFillDraw(left,top+steps,right,bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

    case GFX_FILL_STYLE_GRADIENT_RIGHT:
        length = length * (right - left);
        length /= 100;
        steps = length;
        if(GFX_RectangleFillDraw(left+steps,top,right,bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

    case GFX_FILL_STYLE_GRADIENT_LEFT:
        length = length * (right - left);
        length /= 100;
        steps = length;
        if(GFX_RectangleFillDraw(left,top,right-steps,bottom)== GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

    case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
        steps = (right - left) >> 1;
        break;

    case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
        steps = (bottom - top) >> 1;
        break; 

    default:
        return(GFX_STATUS_SUCCESS);
    }

    startRed    = GFX_ComponentRedGet(startColor);
    startGreen  = GFX_ComponentGreenGet(startColor);
    startBlue   = GFX_ComponentBlueGet(startColor);

    endRed      = GFX_ComponentRedGet(endColor);
    endGreen    = GFX_ComponentGreenGet(endColor);
    endBlue     = GFX_ComponentBlueGet(endColor);

    ///////////////////////////////////

    //Find the step size for the red portion//
    rdiff = ((long)endRed - (long)startRed) << 8;
    rdiff /= steps;

    //Find the step size for the green portion//
    gdiff = ((long)endGreen - (long)startGreen) << 8;
    gdiff /= steps;

    //Find the step size for the blue portion//
    bdiff = ((long)endBlue - (long)startBlue) << 8;
    bdiff /= steps;

    static short barSize = 1;
    startColor = GFX_RGBConvert(startRed, startGreen, startBlue);

    // PERCENTAGE BASED CODE
    for(i=0; i < steps; i++)
    {
        //Calculate the starting RGB values
        endRed      = startRed + ((rdiff*i) >> 8);
        endGreen    = startGreen + ((gdiff*i) >> 8);
        endBlue     = startBlue + ((bdiff*i) >> 8);

        endColor = GFX_RGBConvert(endRed, endGreen, endBlue);

        if(endColor == startColor)
        {
            barSize++;
            continue;
        }

        state = 1;
case 1:
        GFX_DRV_instance[0].PrimitiveFunction.ColorSet(endColor);
        startColor = endColor;

        switch(GFX_Primitive_instance.gradientStyle.type)          //This switch statement draws the gradient depending on direction chosen
        {
        case GFX_FILL_STYLE_GRADIENT_DOWN:
            if(GFX_RectangleFillDraw(left, cTop, right, cTop + barSize) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cTop += barSize;
        break;
        
        case GFX_FILL_STYLE_GRADIENT_UP:
            if(GFX_RectangleFillDraw(left,cBottom - barSize,right,cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cBottom -= barSize;
        break;

        case GFX_FILL_STYLE_GRADIENT_RIGHT:
            if(GFX_RectangleFillDraw(cLeft, top, cLeft + barSize, bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cLeft += barSize;
        break;
        
        case GFX_FILL_STYLE_GRADIENT_LEFT:
            if(GFX_RectangleFillDraw(cRight - barSize, top, cRight, bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cRight -= barSize;
        break;

        case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
            if(GFX_RectangleFillDraw(cRight - barSize, cTop, cRight, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cRight -= barSize;
            state = 2;
case 2:
           GFX_DRV_instance[0].PrimitiveFunction.ColorSet(endColor);
            if(GFX_RectangleFillDraw(cLeft, cTop, cLeft + barSize, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cLeft += barSize;
        break;

        case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
            if(GFX_RectangleFillDraw(cLeft, cBottom - barSize, cRight, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            cBottom -= barSize;
            state = 3;
case 3:
           GFX_DRV_instance[0].PrimitiveFunction.ColorSet(endColor);
            if(GFX_RectangleFillDraw(cLeft, cTop, cRight, cTop + barSize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
            cTop += barSize;
        break; 

        default: 
            break;
        }

        barSize = 1;
    }

    if(barSize > 1)
    {
        state = 4;
case 4: 
        GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_RGBConvert(endRed, endGreen, endBlue));
      
        switch(GFX_Primitive_instance.gradientStyle.type)          //This switch statement draws the gradient depending on direction chosen
        {
        case GFX_FILL_STYLE_GRADIENT_DOWN:
            if(GFX_RectangleFillDraw(left, cTop, right, cTop + barSize) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;
        
        case GFX_FILL_STYLE_GRADIENT_UP:
            if(GFX_RectangleFillDraw(left,cBottom - barSize,right,cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

        case GFX_FILL_STYLE_GRADIENT_RIGHT:
            if(GFX_RectangleFillDraw(cLeft, top, cLeft + barSize, bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;
        
        case GFX_FILL_STYLE_GRADIENT_LEFT:
            if(GFX_RectangleFillDraw(cRight - barSize, top, cRight, bottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break;

        case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
            if(GFX_RectangleFillDraw(cRight - barSize, cTop, cRight, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            state = 5;
case 5:
            GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_RGBConvert(endRed, endGreen, endBlue));
            if(GFX_RectangleFillDraw(cLeft, cTop, cLeft + barSize, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            break;

        case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
            if(GFX_RectangleFillDraw(cLeft, cBottom - barSize, cRight, cBottom) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
            state = 6;
case 6:
            GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_RGBConvert(endRed, endGreen, endBlue));
            if(GFX_RectangleFillDraw(cLeft, cTop, cRight, cTop + barSize) == GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
        break; 

        default: 
            break;
        }
    }
}

    state = 0;
    return (GFX_STATUS_SUCCESS);
}

GFX_STATUS GFX_BevelGradientDraw(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t rad)
{
    static uint16_t i;
    static uint16_t sred,sblue,sgreen;
    static uint16_t ered,eblue,egreen;
    static GFX_COLOR StartColor,EndColor;
    static long rdiff=0,gdiff=0,bdiff=0;
    static short steps;
    static uint8_t state=0;
    static uint16_t length;
    static GFX_COLOR color1;

    while(1)
    {

switch(state)
{
case 0:
    EndColor = GFX_Primitive_instance.gradientStyle.endColor;
    color1 = GFX_Primitive_instance.gradientStyle.startColor;
    length = GFX_Primitive_instance.gradientStyle.length;
    
    switch(GFX_Primitive_instance.gradientStyle.type)     //This switch statement calculates the amount of transitions needed
    {
    case GFX_FILL_STYLE_GRADIENT_UP:
    case GFX_FILL_STYLE_GRADIENT_DOWN:
        length = length * (bottom - top +(rad << 1));
        length /= 100;
        steps = length;
        break;

    case GFX_FILL_STYLE_GRADIENT_RIGHT:
    case GFX_FILL_STYLE_GRADIENT_LEFT:
        length = length * (right - left +(rad << 1));
        length /= 100;
        steps = length;
        break;

    case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
        steps = (right - left +(rad << 1)) >> 1;
        break;

    case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
        steps = (bottom - top +(rad << 1)) >> 1;
        break; 

    default:
        return (GFX_STATUS_SUCCESS);
    }

    //Calculate the starting RGB values
    sred    = GFX_ComponentRedGet(color1);
    sgreen  = GFX_ComponentGreenGet(color1);
    sblue   = GFX_ComponentBlueGet(color1);
            
    ered    = GFX_ComponentRedGet(EndColor);
    egreen  = GFX_ComponentGreenGet(EndColor);
    eblue   = GFX_ComponentBlueGet(EndColor);

    ///////////////////////////////////

    //Find the step size for the red portion//
    rdiff = ((long)ered - (long)sred) << 8;
    rdiff /= steps;

    //Find the step size for the green portion//
    gdiff = ((long)egreen - (long)sgreen) << 8;
    gdiff /= steps;

    //Find the step size for the blue portion//
    bdiff = ((long)eblue - (long)sblue) << 8;
    bdiff /= steps;

    typedef enum
    {
        BEGIN = 200,
        CHECK,
        Q8TOQ1,
        Q7TOQ2,
        Q6TOQ3,
        Q5TOQ4,
        WAITFORDONE,
        FACE
    } FILLCIRCLE_STATES;

    static uint32_t temp;
    static long err;
    static short yLimit, xPos, yPos;
    static short xCur, yCur, yNew;

    state = BEGIN;

            case BEGIN:
                if(!rad)
                {   // no radius object is a filled rectangle
                    state = FACE;
                    break;
                }

                // compute variables
                temp = SIN45 * rad;
                yLimit = temp>>16;
                temp = (uint32_t) (ONEP25 - ((long) rad << 16));
                 err = (short) (temp>>16);
                xPos = rad;
                yPos = 0;
                xCur = xPos;
                yCur = yPos;
                yNew = yPos;
                state = CHECK;

            case CHECK:
                if(yPos > yLimit)
                {
                    state = FACE;
                    break;
                }

                // New records the last y position
                yNew = yPos;

                // calculate the next value of x and y
                if(err > 0)
                {
                    xPos--;
                    err += 5 + ((yPos - xPos) << 1);
                }
                else
                    err += 3 + (yPos << 1);
                yPos++;
                state = Q6TOQ3;

            case Q6TOQ3:
                if(xCur != xPos)
                {

                    // 6th octant to 3rd octant
	            	//if (_bevelDrawType & DRAWBOTTOMBEVEL) 
	            	{ 
                        if(GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOUBLE_VER
                                || GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR)
                            i = (top - yCur) - top + rad;
                        else
                            i = (bottom + yCur) - top + rad;
                
                        ered = sred + ((rdiff*i) >> 8);
                        egreen = sgreen + ((gdiff*i) >> 8);
                        eblue = sblue + ((bdiff*i) >> 8);
 
                        GFX_Primitive_instance.gradientStyle.endColor = GFX_RGBConvert(ered,egreen,eblue);
                                         
                         if(i>length)
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(EndColor);
                         else
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_Primitive_instance.gradientStyle.endColor);

                        state = 1;
case 1:
                        switch(GFX_Primitive_instance.gradientStyle.type)    //Direction matter because different portions of the circle are drawn
                        {
                           case GFX_FILL_STYLE_GRADIENT_LEFT:
                               if(GFX_RectangleFillDraw(left - yNew, top - xCur, left - yCur, bottom + xCur)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                               break;
                           
                           case GFX_FILL_STYLE_GRADIENT_RIGHT:
                           case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
                                if(GFX_RectangleFillDraw(right + yCur, top - xCur, right + yNew, bottom + xCur)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                                break;
                           
                           case GFX_FILL_STYLE_GRADIENT_UP:
                                if(GFX_RectangleFillDraw(left - xCur, top - yNew, right + xCur, top - yCur)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                                break;

                           case GFX_FILL_STYLE_GRADIENT_DOWN:
                           case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
                                if(GFX_RectangleFillDraw(left - xCur, bottom + yCur, right + xCur, bottom + yNew)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                           
                           default: 
                               break;
                        }

                  	}          	
                    state = Q5TOQ4;
                    break;
                }

                state = CHECK;
                return(GFX_STATUS_FAILURE);

            case Q5TOQ4:

                    if(GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOUBLE_VER
                            || GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR)
                    i = xPos   + rad;
                    else     // 5th octant to 4th octant
                    i = (bottom + xPos) - top + rad ;

                    //Calculate the starting RGB values
                    ered = sred + ((rdiff*i) >> 8);
                    egreen = sgreen + ((gdiff*i) >> 8);
                    eblue = sblue + ((bdiff*i) >> 8);
                    
                     GFX_Primitive_instance.gradientStyle.endColor = GFX_RGBConvert(ered,egreen,eblue);
                    state = 2;
 case 2:
                    if(i>length)
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(EndColor);
                    else
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_Primitive_instance.gradientStyle.endColor);


                    switch(GFX_Primitive_instance.gradientStyle.type)    //Direction matter because different portions of the circle are drawn
                    {
                       case GFX_FILL_STYLE_GRADIENT_LEFT:
                           if(GFX_RectangleFillDraw(left - xCur, top - yNew, left - xPos, bottom + yNew)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_RIGHT:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
                           if(GFX_RectangleFillDraw(right + xPos, top - yNew, right + xCur, bottom + yNew)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_UP:
                            if(GFX_RectangleFillDraw(left - yNew, top - xCur, right + yNew, top - xPos)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;

                       case GFX_FILL_STYLE_GRADIENT_DOWN:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
                            if(GFX_RectangleFillDraw(left - yNew, bottom + xPos, right + yNew, bottom + xCur)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                       default: 
                           break;
                    }

                state = Q8TOQ1;
                break;

            case Q8TOQ1:

                // 8th octant to 1st octant
	            //if (_bevelDrawType & DRAWTOPBEVEL) 
				{
                    i = (top - xCur) - top + rad;

                    //Calculate the starting RGB values
                    ered = sred + ((rdiff*i) >> 8);
                    egreen = sgreen + ((gdiff*i) >> 8);
                    eblue = sblue + ((bdiff*i) >> 8);

                     GFX_Primitive_instance.gradientStyle.endColor = GFX_RGBConvert(ered,egreen,eblue);
                    state = 3;
case 3:
                    if(i>length)
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(EndColor);
                    else
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_Primitive_instance.gradientStyle.endColor);


                    switch(GFX_Primitive_instance.gradientStyle.type)    //Direction matter because different portions of the circle are drawn
                    {
                       case GFX_FILL_STYLE_GRADIENT_LEFT:
                           if(GFX_RectangleFillDraw(right + xPos, top - yNew, right + xCur, bottom + yNew)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_RIGHT:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
                           if(GFX_RectangleFillDraw(left - xCur, top - yNew, left - xPos, bottom + yNew)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_UP:
                            if(GFX_RectangleFillDraw(left - yNew, bottom + xPos, right + yNew, bottom + xCur)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;

                       case GFX_FILL_STYLE_GRADIENT_DOWN:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
                            if(GFX_RectangleFillDraw(left - yNew, top - xCur, right + yNew, top - xPos)==GFX_STATUS_FAILURE)return(GFX_STATUS_FAILURE);
                            break;
                       
                       default: 
                           break;
                    }

    			}                	
                state = Q7TOQ2;
                break;

            case Q7TOQ2:

                // 7th octant to 2nd octant
	            //if (_bevelDrawType & DRAWTOPBEVEL) 
				{             
                    i = (top - yNew) - top + rad;

                    //Calculate the starting RGB values
                    ered = sred + ((rdiff*i) >> 8);
                    egreen = sgreen + ((gdiff*i) >> 8);
                    eblue = sblue + ((bdiff*i) >> 8);

                     GFX_Primitive_instance.gradientStyle.endColor = GFX_RGBConvert(ered,egreen,eblue);

                    state = 4;
case 4:
                    if(i>length)
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(EndColor);
                    else
                         GFX_DRV_instance[0].PrimitiveFunction.ColorSet(GFX_Primitive_instance.gradientStyle.endColor);

                    switch(GFX_Primitive_instance.gradientStyle.type)    //Direction matter because different portions of the circle are drawn
                    {
                       case GFX_FILL_STYLE_GRADIENT_LEFT:

                           if(GFX_RectangleFillDraw(right + yCur, top - xCur, right + yNew, bottom + xCur)==GFX_STATUS_FAILURE)
                            return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_RIGHT:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_VER:
                           if(GFX_RectangleFillDraw(left - yNew, top - xCur, left - yCur, bottom + xCur)==GFX_STATUS_FAILURE)
                               return(GFX_STATUS_FAILURE);
                            break;
                       
                       case GFX_FILL_STYLE_GRADIENT_UP:
                            if(GFX_RectangleFillDraw(left - xCur, bottom + yCur, right + xCur, bottom + yNew)==GFX_STATUS_FAILURE)
                                return(GFX_STATUS_FAILURE);
                            break;

                       case GFX_FILL_STYLE_GRADIENT_DOWN:
                       case GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR:
                            if(GFX_RectangleFillDraw(left - xCur, top - yNew, right + xCur, top - yCur)==GFX_STATUS_FAILURE)
                                return(GFX_STATUS_FAILURE);
                            break;
                       
                       default: 
                           break;
                    }

				}
                // update current values
                xCur = xPos;
                yCur = yPos;
                state = CHECK;
                break;

            case FACE:
                if((right - left) || (bottom - top))
                {
                i = (top) - top + rad;
                //Calculate the starting RGB values
                ered = sred + ((rdiff*i) >> 8);
                egreen = sgreen + ((gdiff*i) >> 8);
                eblue = sblue + ((bdiff*i) >> 8);

                StartColor = GFX_RGBConvert(ered,egreen,eblue);
 
                if(i>length) 
                    StartColor = EndColor;  

                i = (bottom) - top + rad;
                //Calculate the ending RGB values
                ered = sred + ((rdiff*i) >> 8);
                egreen = sgreen + ((gdiff*i) >> 8);
                eblue = sblue + ((bdiff*i) >> 8);

                if(i<=length) 
                   EndColor = GFX_RGBConvert(ered,egreen,eblue);
      
                length -= rad;   //Subtract the radius from the length needed for gradient   
              
                if(GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_UP
                        || GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOWN
                        || GFX_Primitive_instance.gradientStyle.type == GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR)
                {
                   if(length>= bottom-top)
                   {
                       length = 100;
                   }
                   else
                   {
                       length *= 100;
                       length /= (bottom -top);
                   } 
                   state = 5;
                   GFX_GradientColorSet(StartColor,EndColor);
case 5:
                   if(GFX_BarGradientDraw(left-rad, top, right+rad, bottom) == GFX_STATUS_FAILURE)
                       return(GFX_STATUS_FAILURE);
                }
                else
                {
                  if(length>=right-left)
                  {
                      length = 100;
                  }
                  else
                  {
                       length *= 100;
                       length /= (right - left);
                  }
                   state = 6;
                   GFX_GradientColorSet(StartColor,EndColor);
case 6:
                   if(GFX_BarGradientDraw(left, top-rad, right, bottom+rad) == GFX_STATUS_FAILURE)
                       return(GFX_STATUS_FAILURE);
                }

 
    }               // end of while
        state = 0;
        return (GFX_STATUS_SUCCESS);
  }
}
}
#endif

/*********************************************************************
* Function:  SHORT GetSineCosine(SHORT v, WORD type)
*
* PreCondition: none
*
* Input: v - the angle used to calculate the sine or cosine value. 
*			 The angle must be in the range of -360 to 360 degrees.
*		 type - sets if the angle calculation is for a sine or cosine
*				- GETSINE (0) - get the value of sine(v).
*				- GETCOSINE (1) - return the value of cosine(v).
*
* Output: Returns the sine or cosine of the angle given.
*
* Side Effects: none
*
* Overview: This calculates the sine or cosine value of the given angle.
*
* Note: none
*
********************************************************************/
int16_t GFX_SineCosineGet(int16_t v, GFX_TRIG_FUNCTION_TYPE type)
{
    // if angle is neg, convert to pos equivalent
    if (v < 0)
    	v += 360;

    if(v > COSINETABLEENTRIES * 3)
    {
        v -= (COSINETABLEENTRIES * 3);
        if (type == GFX_TRIG_SINE_TYPE)
            return (-_CosineTable[v]);
        else
            return (_CosineTable[COSINETABLEENTRIES - v]);
    }
    else if(v > COSINETABLEENTRIES * 2)
    {
        v -= (COSINETABLEENTRIES * 2);
        if (type == GFX_TRIG_SINE_TYPE)
            return (-_CosineTable[(COSINETABLEENTRIES - v)]);
        else
            return (-_CosineTable[v]);
    }
    else if(v > COSINETABLEENTRIES)
    {
        v -= (COSINETABLEENTRIES);
        if (type == GFX_TRIG_SINE_TYPE)
            return (_CosineTable[v]);
        else
            return (-_CosineTable[COSINETABLEENTRIES - v]);
    }
    else
    {
        if (type == GFX_TRIG_SINE_TYPE)
            return (_CosineTable[COSINETABLEENTRIES - v]);
        else
            return (_CosineTable[v]);
    }


}

void GetCirclePoint(int16_t radius, int16_t angle, int16_t *x, int16_t *y)
{
    uint32_t   rad;
    short   ang;
    short   temp;

    ang = angle % 45;
    if((angle / 45) & 0x01)
        ang = 45 - ang;

    rad = radius;
    // there is a shift by 8 bits here since this function assumes a shift on the calculations for accuracy
    // and to avoid long and complex multiplications.
    rad *= ((uint32_t) GFX_SineCosineGet(ang, GFX_TRIG_COSINE_TYPE) << 8);

    *x = ((uint32_t) (rad)>>16);
    rad = radius;
    rad *= ((uint32_t) GFX_SineCosineGet(ang, GFX_TRIG_SINE_TYPE) << 8);

    *y = ((uint32_t) (rad)>>16);

    if(((angle > 45) && (angle < 135)) || ((angle > 225) && (angle < 315)))
    {
        temp = *x;
        *x = *y;
        *y = temp;
    }

    if((angle > 90) && (angle < 270))
    {
        *x = -*x;
    }

    if((angle > 180) && (angle < 360))
    {
        *y = -*y;
    }
}

/******************************************************************************
  Function:
    GFX_STATUS GFX_PageSet(uint8_t pageType, uint8_t page)

  Summary:

  Description:

  Remarks:

*/
GFX_STATUS GFX_PageSet(uint8_t pageType, uint8_t page)
{

    if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(pageType, page))
        return(GFX_STATUS_FAILURE);

       switch(pageType)
       {
          case ACTIVE_PAGE:
              GFX_Primitive_instance.activePage = page;
              break;
          case VISUAL_PAGE:
               GFX_Primitive_instance.visualPage = page;
               break;
          case BACKGROUND_PAGE:  //Used for AlphaBlending
               GFX_Primitive_instance.backgroundPage = page;
           case TRANSITION_PAGE:
               GFX_Primitive_instance.transitionPage = page;
               break;
        }

    return(GFX_STATUS_SUCCESS);
}

/******************************************************************************
  Function:
    GFX_STATUS GFX_AlphaBlendWindow(GFX_ALPHA_PARAMS *alphaParams,uint16_t  width, uint16_t height, uint8_t  alphaPercent)

  Summary:

  Description:

  Remarks:

*/
GFX_STATUS GFX_AlphaBlendWindow(GFX_ALPHA_PARAMS *alphaParams,uint16_t  width, uint16_t height, uint8_t  alphaPercent)
{  
static uint16_t x,y;
static GFX_COLOR *bcolor, *fcolor;
static uint8_t state  = 0;
static uint16_t *arrayCount = NULL;

        if(GFX_DRV_instance[0].PrimitiveFunction.AlphaBlendWindow != NULL)
        {
          if(GFX_DRV_instance[0].PrimitiveFunction.AlphaBlendWindow(alphaParams,width,height,alphaPercent) == NULL)
              return(GFX_STATUS_FAILURE);
        }
        else
        {
switch(state)
{

case 0:
y=0;

while(y< height)
{
        state = 1;
case 1:
        if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(ACTIVE_PAGE, alphaParams->foregroundPage))
            return(GFX_STATUS_FAILURE);
        state = 2;
case 2:
        if(GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&GFX_Primitive_instance.line[0],alphaParams->foregroundLeft,alphaParams->foregroundTop, width) == NULL)
            return(GFX_STATUS_FAILURE);
        state = 3;
case 3:
        if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(ACTIVE_PAGE, alphaParams->backgroundPage))
            return(GFX_STATUS_FAILURE);
        state = 4;
case 4:
        arrayCount = GFX_DRV_instance[0].PrimitiveFunction.PixelArrayGet(&GFX_Primitive_instance.alphaLine[0],alphaParams->backgroundLeft,alphaParams->backgroundTop, width);
        if(arrayCount == NULL) return(GFX_STATUS_FAILURE);
        state = 5;
case 5:
        if(*arrayCount>0) return(GFX_STATUS_FAILURE);

         fcolor = &GFX_Primitive_instance.line[0];
         bcolor = &GFX_Primitive_instance.alphaLine[0];

      if(alphaPercent != 100)
      {
            for(x=0; x< width; x++) 
           {
             switch(alphaPercent)
             {
                case 50: *fcolor = ConvertColor50(*fcolor)+ ConvertColor50(*bcolor);break;
                case 75: *fcolor = ConvertColor75(*fcolor)+ ConvertColor25(*bcolor);break;
                case 25: *fcolor = ConvertColor25(*fcolor)+ ConvertColor75(*bcolor);break;
                default: break;
             }
      
              fcolor++;
              bcolor++;
           }
      }
       state = 6;
case 6:
    if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(ACTIVE_PAGE, alphaParams->destinationPage)) return(GFX_STATUS_FAILURE);
    state = 7;
case 7:
    arrayCount = GFX_DRV_instance[0].PrimitiveFunction.PixelArrayPut(&GFX_Primitive_instance.line[0],alphaParams->destinationLeft,
                 alphaParams->destinationTop, width, 1);
    if(arrayCount == NULL) return(GFX_STATUS_FAILURE);
    state = 8;
case 8:
    if(*arrayCount > 0) return(GFX_STATUS_FAILURE);

    alphaParams->foregroundTop++;
    alphaParams->backgroundTop++;
    alphaParams->destinationTop++;
    y++;
}

}
state = 0;
        }
return (GFX_STATUS_SUCCESS);

}

#if !defined GFX_CONFIG_DOUBLE_BUFFERING_DISABLE

GFX_RECTANGULAR_AREA InvalidatedArea[GFX_MAX_INVALIDATE_AREAS];
/******************************************************************************
  Function:
    GFX_DoubleBufferingEnable(uint8_t enable)

  Summary:

  Description:

  Remarks:

*/
GFX_STATUS GFX_DoubleBufferEnable()
{
    GFX_Primitive_instance.InvalidatedRectangleCount = GFX_MAX_INVALIDATE_AREAS;
    doubleBuffEnabled = 1;

    return(GFX_STATUS_SUCCESS);
}

GFX_STATUS GFX_DoubleBufferDisable()
{
     static uint8_t state =0;

switch(state)
{
case 0:
        if(doubleBuffEnabled == 0) 
        {
            return (GFX_STATUS_SUCCESS);
        }
        state = 2;
case 2:        
        if(GFX_DoubleBufferSynchronize() == GFX_STATUS_FAILURE)
            return(GFX_STATUS_FAILURE);
        GFX_Primitive_instance.activePage = (GFX_Primitive_instance.activePage == GFX_BUFFER1)? GFX_BUFFER2: GFX_BUFFER1;
        state = 3;
case 3:
        if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(ACTIVE_PAGE,GFX_Primitive_instance.activePage))
            return(GFX_STATUS_FAILURE);
        doubleBuffEnabled = 0;
    
}

    state = 0;
    return(GFX_STATUS_SUCCESS);
}
/******************************************************************************
  Function:
    GFX_STATUS GFX_DoubleBufferAreaMark(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)

  Summary:

  Description:

  Remarks:

*/
void GFX_DoubleBufferAreaMark(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{

    if(doubleBuffEnabled == 0)
    {
        return;    //Do Nothing
    }

    if(!left && !top && (right == GFX_MaxXGet()) && (bottom == GFX_MaxYGet()))
    {
         GFX_Primitive_instance.InvalidatedRectangleCount = GFX_MAX_INVALIDATE_AREAS;
    }
    else if(GFX_Primitive_instance.InvalidatedRectangleCount < GFX_MAX_INVALIDATE_AREAS)
    {
        InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].left = left;
        InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].top = top;
        InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].right = right;
        InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].bottom = bottom;
        GFX_Primitive_instance.InvalidatedRectangleCount++;
    }
}

/******************************************************************************
  Function:
    GFX_STATUS GFX_DoubleBufferSynchronize()

  Summary:
    Synchronizes the draw and frame buffers

  Description:

  Remarks:
*/

GFX_STATUS GFX_DoubleBufferSynchronize()
{

     static uint32_t SourceBuffer, DestBuffer;
     static uint8_t state =0;
     static uint16_t width, height;

switch(state)
{

case 0:
    if(GFX_Primitive_instance.activePage == GFX_BUFFER1)
    {
        SourceBuffer = GFX_BUFFER1;
        DestBuffer   = GFX_BUFFER2;
    }
    else
    {
        SourceBuffer = GFX_BUFFER2;
        DestBuffer   = GFX_BUFFER1;
    }

     GFX_Primitive_instance.activePage = DestBuffer;
     GFX_Primitive_instance.visualPage = SourceBuffer;

case 1:
     state = 1;
     if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(ACTIVE_PAGE,GFX_Primitive_instance.activePage))
         return(GFX_STATUS_FAILURE);
    
     state = 2;
case 2:
     if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(VISUAL_PAGE,GFX_Primitive_instance.visualPage))
         return(GFX_STATUS_FAILURE);
     

    if(GFX_Primitive_instance.InvalidatedRectangleCount >= GFX_MAX_INVALIDATE_AREAS)
    {
        GFX_AlphaParamsSet(SourceBuffer,0,0,SourceBuffer,0,0,DestBuffer,0,0);
case 3:
        state = 3;
        if(CopyPageWindow(&GFX_Primitive_instance.alphaArea, GFX_MaxXGet()+1, GFX_MaxYGet()+1) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
         GFX_Primitive_instance.InvalidatedRectangleCount = 0;
    }
    else
    {
        while(GFX_Primitive_instance.InvalidatedRectangleCount)
        {
            GFX_Primitive_instance.InvalidatedRectangleCount--;

            width =  InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].right - InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].left + 1;
            height =  InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].bottom - InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].top + 1;

            GFX_AlphaParamsSet(SourceBuffer,InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].left,InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].top,
                                    SourceBuffer,InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].left,InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].top,DestBuffer,
                                    InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].left,InvalidatedArea[GFX_Primitive_instance.InvalidatedRectangleCount].top);
case 4:
            state = 4;
            if(CopyPageWindow(&GFX_Primitive_instance.alphaArea,width, height)==GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);

       }
    }
}
   state = 0;
   return(GFX_STATUS_SUCCESS);

}
#endif //USE_DOUBLE_BUFFERING

/******************************************************************************
  Function:
    GFX_STATUS GFX_Layer(uint8_t layer, uint8_t action, uint16_t param1, uint16_t param2)

  Summary:

  Description:

  Remarks:
*/
GFX_STATUS GFX_Layer(uint8_t layer, uint8_t action, uint16_t param1, uint16_t param2)
{

 static uint16_t* command = NULL;
 static uint8_t state = 0;

if(!state)
{
switch(action)
{
    case ENABLE:
    primitiveLayer[layer].on = 1;
    break;
    case DISABLE:
    primitiveLayer[layer].on = 0;
    break;
    case SET_SIZE:
    primitiveLayer[layer].width = param1;
    primitiveLayer[layer].height = param2;
    return(GFX_STATUS_SUCCESS);
    break;
    case SET_PAGE:
    primitiveLayer[layer].page = param1;
    return(GFX_STATUS_SUCCESS);
    break;
    case SET_PAGE_START:
    primitiveLayer[layer].left = param1;
    primitiveLayer[layer].top = param2;
    return(GFX_STATUS_SUCCESS);
    break;
    case SET_LAYER_START:
    primitiveLayer[layer].layerLeft = param1;
    primitiveLayer[layer].layerTop = param2;
    return(GFX_STATUS_SUCCESS);
    break;
}
state = 1;
}

if(command == NULL)
{
    command = GFX_DRV_instance[0].PrimitiveFunction.Layer(layer, &primitiveLayer[layer]);
    if(command == NULL) return(GFX_STATUS_FAILURE);
}
   
if(*command > 0) return(GFX_STATUS_FAILURE);

command = NULL;
state = 0;
return(GFX_STATUS_SUCCESS);

}
