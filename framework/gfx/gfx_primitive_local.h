/***********************************************************************
  Company:
    Microchip Technology Inc.
  File Name:
    gfx_primitive.h
  Summary:
    Interface for the graphics library where the primitives are rendered
    and sent to the graphics controller either external or internal.
  Description:
    Clock System Service Interface Definition
    
    None.                                                               
  ***********************************************************************/

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

#ifndef _GFX_PRIMITIVE_LOCAL_H
#define _GFX_PRIMITIVE_LOCAL_H

#include <stdint.h>
#include "driver/gfx/drv_gfx_display.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

/*********************************************************************
* Overview: This structure is used to describe the gradient style.
*
*********************************************************************/
typedef struct
{
    GFX_FILL_STYLE         type;        // selected the gradient type
    GFX_COLOR              startColor;  // sets the starting color of gradient transition
    GFX_COLOR              endColor;    // sets the ending color of gradient transition
    uint8_t                length;      // defines the length of the gradient transition in pixels
} GFX_GRADIENT_STYLE;

//******************************************************************************
/* Function:
    void GFX_FontOrientationSet(orient)

  Summary:
    Sets font orientation vertical or horizontal.

  Description:

  Precondition:
    None.

  Parameters:
    orient - sets font orientation when rendering characters and strings.

  Returns:
    None.

  Example:
    <code>
    </code>

  Remarks:
 */
 #define GFX_SetFontOrientation(orient)  GFX_Primitive_instance.currentFont.orientation = orient;

// *****************************************************************************
/* GFX image stretch

  Summary:
     Types of image stretching

  Description:

  Remarks:
  None.
*/
typedef enum
{
    IMAGE_NORMAL  = 1,
    IMAGE_X2 =    2
}IMAGE_STRETCH;

// *****************************************************************************
/* GFX current font

  Summary:
     Internal structure for currently set font.

  Description:

  Remarks:
  None.
*/
typedef struct
{
   GFX_RESOURCE_HDR                *pFont;                     // pointer to the currently set font
   GFX_FONT_HEADER     header;                     // copy of the currently set font header
   GFX_ALIGNMENT      alignment;                  // alignment of the font
   GFX_ALIGNMENT    orientation;                // orientation of the font
   #if !defined GFX_CONFIG_FONT_ANTIALIASED_DISABLE
   uint8_t  antiAliasType;                  // anti-alias type set
   #endif
} GFX_FONT_CURRENT;

// *****************************************************************************
/* GFX put image param

  Summary:
     Partial image area to render.

  Description:

  Remarks:
  None.
*/
typedef struct
{
    uint16_t         width;                       /*Partial Image width*/
    uint16_t         height;                      // Partial Image height
    uint16_t         xoffset;                     // xoffset of image
    uint16_t         yoffset;                     // yoffset of image
    IMAGE_STRETCH          stretch;                     // stretch of the image
    uint8_t          transparentFlag;             // transparent Color flag
    GFX_COLOR        transparentColor;            // transparent Color
    uint8_gfx_image_prog*      image;                       // pointer to the image
    GFX_COLOR        palette[256];                // palette used for <8BPP images
} PUTIMAGE_PARAM;

extern PUTIMAGE_PARAM   primitiveTaskImage;
#define GFX_ImageStretchSet(value) primitiveTaskImage.stretch = value

// *********************************************************************
/* 
   Macro: GFX_FONT_SPACE 

 Summary: Constant used to define the font space in program memory

 Description: Font space section.  The fonts can be located in psv (constant)
 or program space in PIC24/dsPIC MCUs.  This define allows for switching
 of the pointer type used to access the font structure in memory
 See: GraphicsConfig.h for the application define.
*/
//

// *****************************************************************************
/* GFX layering actions

  Summary:

  Description:

  Remarks:
  None.
*/
typedef enum
{
   ENABLE  = 0x80,
   DISABLE = 0,
   UPDATE,
   SET_SIZE,
   SET_PAGE,
   SET_PAGE_START,
   SET_LAYER_START
} LAYER_ACTIONS;

// *****************************************************************************
/* GFX transition parameters

  Summary:

  Description:

  Remarks:
  None.
*/
typedef struct
{
    uint16_t left;
    uint16_t top;
    uint16_t delay_ms; 
    uint8_t sourcePage; 
    uint8_t destinationPage;
    uint8_t type; 
    uint8_t param1; 
    uint8_t param2;		            
} GFX_TRANSITION_PARAMS;

// *****************************************************************************
/* GFX primitive data

  Summary:

  Description:

  Remarks:
  None.
*/
typedef struct
{         
    uint8_t              activePage;
    uint8_t              visualPage;
    uint8_t                       transitionPage;
    uint8_t                       foregroundPage;   //Initialize Alpha Values
    uint8_t                       backgroundPage;
    uint8_t                       destinationPage;
    GFX_LINE_STYLE                lineType;
    uint16_t                      cursorX;
    uint16_t                      cursorY;
    GFX_BEVEL_RENDER_TYPE         bevelDrawType;
    GFX_COLOR                     currentColor;                //Current Color for the instance
    GFX_FONT_CURRENT              currentFont;
    GFX_RESOURCE_HDR              *pResource;
    GFX_ALPHA_PARAMS              alphaArea;
    GFX_TRANSITION_PARAMS         transitionParams;
    GFX_COLOR                     line[480];                   // Storage for line data
    GFX_COLOR                     alphaLine[480];              // Storage for alpha line data
    uint8_t                       InvalidatedRectangleCount;    //Double Buffer Variable
    GFX_GRADIENT_STYLE            gradientStyle;
} GFX_Primitive_DATA;

#define GFX_GradientTypeSet(value) GFX_Primitive_instance.gradientStyle.type = value

// *****************************************************************************
/* Function:
    GFX_ActivePageGet(handle)

  Summary:
    Returns the active page.

  Description:

  Precondition:
    None.

  Parameters:

  Returns:
    None.

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_ActivePageGet()    GFX_Primitive_instance.activePage

// *****************************************************************************
/* Function:
    GFX_VisualPageGet()

  Summary:
    Returns the visual page.

  Description:

  Precondition:
    None.

  Parameters:

  Returns:
    None.

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_VisualPageGet()    GFX_Primitive_instance.visualPage

extern GFX_Primitive_DATA GFX_Primitive_instance; //structure to store the primitive driver structures

// *****************************************************************************
/* Function:
     void GFX_MaxXGet()

  Summary:

  Description:

  Precondition:

  Parameters:

  Returns:

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_MaxXGet() (GFX_DRV_instance[0].horizontalResolution-1)

// *****************************************************************************
/* Function:
     void GFX_MaxYGet()

  Summary:

  Description:

  Precondition:

  Parameters:

  Returns:

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_MaxYGet() (GFX_DRV_instance[0].verticalResolution-1)

// *****************************************************************************
/* Function:
     GFX_PrevAlphaColorSet(color)
 
  Summary:
 
  Description:

  Precondition:

  Parameters:

  Returns:

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_PrevAlphaColorSet(color) GFX_Primitive_instance.alphaArea.prevAlphaColor = color

// *****************************************************************************
/* Function:
     GFX_PrevAlphaColorGet()
 
  Summary:
 
  Description:

  Precondition:

  Parameters:

  Returns:

  Example:
    <code>
    <code>

  Remarks:
*/
#define GFX_PrevAlphaColorGet() GFX_Primitive_instance.alphaArea.prevAlphaColor

// *****************************************************************************
/* Function:
     GFX_STATUS* GFX_PageSet(uint8_t pageType, uint8_t page);

  Summary:

  Description:

  Precondition:

  Parameters:

  Returns:

  Example:
    <code>
    <code>

  Remarks:
*/
GFX_STATUS GFX_PageSet(uint8_t pageType, uint8_t page);

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*
  Function:
	GFX_STATUS*  GFX_PixelsPut(uint16_t x, uint16_t y, uint16_t count);

  Summary:
	This function renders one line of pixels of a given length 

  Description:
	None

  Precondition:
	None

  Parameters:
             instance - primitive instance
             x - x position of the left top corner.
		     y -  y position of the left top corner.
		     count - number of pixels

   Returns: Queue handle once the primitive has been place in queue

  Example:
    <code>
    None
    </code>
*/
//
#define GFX_PixelsPut(x, y, count, lineCount) GFX_RectangleFillDraw(x, y, x+count, y+lineCount)
#define GFX_PixelPut(x, y) GFX_PixelsPut(x, y, 1, 1)

//#ifdef USE_ALPHABLEND

// *****************************************************************************
/*
  Function:
	GFX_AlphaParamsSet(fArea,fLeft,fTop,bArea,bLeft,bTop,dArea,dLeft,dTop)

  Summary:

  Description:
	None

  Precondition:
	None

  Parameters:
    None - None

  Returns:
    None

  Example:
    <code>
    None
    </code>
*/
#define GFX_AlphaParamsSet(fArea,fLeft,fTop,bArea,bLeft,bTop,dArea,dLeft,dTop)\
                                                GFX_Primitive_instance.alphaArea.foregroundPage = fArea;\
                                                GFX_Primitive_instance.alphaArea.foregroundLeft = fLeft;\
                                                GFX_Primitive_instance.alphaArea.foregroundTop = fTop;\
                                                GFX_Primitive_instance.alphaArea.backgroundPage = bArea;\
                                                GFX_Primitive_instance.alphaArea.backgroundLeft = bLeft;\
                                                GFX_Primitive_instance.alphaArea.backgroundTop = bTop;\
                                                GFX_Primitive_instance.alphaArea.destinationPage = dArea;\
                                                GFX_Primitive_instance.alphaArea.destinationLeft = dLeft;\
                                                GFX_Primitive_instance.alphaArea.destinationTop = dTop

// *****************************************************************************
/*
  Function:
	GFX_STATUS* GFX_AlphaBlendWindow(GFX_ALPHA_PARAMS *alphaParams,uint16_t  width, uint16_t height, uint8_t  alphaPercent)
 *
  Summary:

  Description:
	None

  Precondition:
	None

  Parameters:
    None - None

  Returns:
    None

  Example:
    <code>
    None
    </code>
*/
GFX_STATUS GFX_AlphaBlendWindow(GFX_ALPHA_PARAMS *alphaParams,uint16_t  width, uint16_t height, uint8_t  alphaPercent);

// *****************************************************************************
/*
  Function:
	GFX_STATUS* GFX_AlphaBlendWindow(GFX_ALPHA_PARAMS *alphaParams,uint16_t  width, uint16_t height, uint8_t  alphaPercent)

  Summary:

  Description:
	None

  Precondition:
	None

  Parameters:
    None - None

  Returns:
    None

  Example:
    <code>
    None
    </code>
*/
#define CopyPageWindow(alphaArea, width, height)\
                            GFX_AlphaBlendWindow(alphaArea,width,height,100)

#define GFX_BUFFER1 (0)
#define GFX_BUFFER2 (1)

extern uint8_t doubleBuffEnabled;

// *****************************************************************************
/*
  Function:
	GFX_STATUS* GFX_Layer(uint8_t layer, uint8_t action, uint16_t param1, uint16_t param2)

  Summary:

  Description:
	None

  Precondition:
	None

  Parameters:
    None - None

  Returns:
    None

  Example:
    <code>
    None
    </code>
*/
GFX_STATUS GFX_Layer(uint8_t layer, uint8_t action, uint16_t param1, uint16_t param2);

extern volatile uint8_t DisplayUpdatePending;

#endif // _PRIMITIVE_LOCAL_H
