/*******************************************************************************
 Module for Microchip Graphics Library 

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_types.h

  Summary:
    Data types used in Microchip Graphics Library.

  Description:
    This module defines the data types used in the Microchip
    Graphics Library for use of Primitive and Driver Layers.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
// DOM-IGNORE-END

#ifndef _GFX_TYPES_MACROS_H
    #define _GFX_TYPES_MACROS_H

#include <stdint.h>
#include "gfx/gfx_types_palette.h"
#include "gfx/gfx_types_font.h"
#include "gfx/gfx_types_image.h"
#include "gfx/gfx_types_resource.h"

/*********************************************************************
* Section: Macro Error Checking
*********************************************************************/
#ifndef GFX_CONFIG_COLOR_DEPTH
    #error "Please define GFX_CONFIG_COLOR_DEPTH in gfx_config.h; valid values (dependent on the driver used) are: 1, 4, 8, 16, 24)"
#endif

#if ((GFX_CONFIG_COLOR_DEPTH != 1) && (GFX_CONFIG_COLOR_DEPTH != 4)  && \
     (GFX_CONFIG_COLOR_DEPTH != 8) && (GFX_CONFIG_COLOR_DEPTH != 16) && \
     (GFX_CONFIG_COLOR_DEPTH != 24))
    #error "Defined GFX_CONFIG_COLOR_DEPTH value is not suppported. Valid values (dependent on the driver used) are: 1, 4, 8, 16, 24)"
#endif

/*********************************************************************
* Overview: Data type that defines the color data. This type is dependent
*           on the COLOR_DEPTH setting. See COLOR_DEPTH.
*           - GFX_COLOR is type uint8_t  if COLOR_DEPTH <= 8
*           - GFX_COLOR is type uint16_t if COLOR_DEPTH = 16
*           - GFX_COLOR is type uint32_t if COLOR_DEPTH = 24
*
*********************************************************************/
#if (GFX_CONFIG_COLOR_DEPTH <= 8)
    typedef uint8_t GFX_COLOR;
#elif (GFX_CONFIG_COLOR_DEPTH == 16)
    typedef uint16_t GFX_COLOR;
#elif (GFX_CONFIG_COLOR_DEPTH == 24)
    typedef uint32_t GFX_COLOR;
#endif


/*********************************************************************
 Overview: Defines the types of line styles.

*********************************************************************/
typedef enum
{
    GFX_LINE_TYPE_MASK          = 0x0007, // DO NOT document, mask for line type
    GFX_LINE_THICKNESS_MASK     = 0x0010, // DO NOT document, mask for thickness
    GFX_LINE_STYLE_THIN_SOLID   = 0x0A00, // solid line, 1 pixel wide (default)
    GFX_LINE_STYLE_THIN_DOTTED  = 0x0A01, // dotted line, 1 pixel wide
    GFX_LINE_STYLE_THIN_DASHED  = 0x0A04, // dashed line, , 1 pixel wide
    GFX_LINE_STYLE_THICK_SOLID  = 0x0A10, // solid line, 3 pixel wide
    GFX_LINE_STYLE_THICK_DOTTED = 0x0A11, // dotted line, 3 pixel wide
    GFX_LINE_STYLE_THICK_DASHED = 0x0A14, // dashed line, 3 pixel wide
    GFX_LINE_STYLE_ANTI_ALIASED = 0x0A20, // anti-aliased line (future feature)
} GFX_LINE_STYLE;

/*********************************************************************
 Overview: Defines the types of fill styles.

*********************************************************************/
typedef enum
{
    GFX_FILL_STYLE_NONE         = 0x0B00, // no fill
    GFX_FILL_STYLE_COLOR,                 // color fill
    GFX_FILL_STYLE_ALPHA_COLOR,           // color fill with alpha blending
    GFX_FILL_STYLE_GRADIENT_DOWN,         // gradient, vertical-down direction
    GFX_FILL_STYLE_GRADIENT_UP,           // gradient, vertical-up direction
    GFX_FILL_STYLE_GRADIENT_RIGHT,        // gradient, horizontal-right
                                          // direction
    GFX_FILL_STYLE_GRADIENT_LEFT,         // gradient, horizontal-left
                                          // direction
    GFX_FILL_STYLE_GRADIENT_DOUBLE_VER,   // gradient, vertical-up/down
                                          // direction
    GFX_FILL_STYLE_GRADIENT_DOUBLE_HOR,   // gradient, horizontal-left/right
                                          // direction
} GFX_FILL_STYLE;

/*********************************************************************
* Overview: Defines the types of background information.
*           Knowing the background information allows easier refresh
*           of an area on the display buffer.
*
*********************************************************************/
typedef enum
{
    GFX_BACKGROUND_NONE           = 0x00, // No background information set.
    GFX_BACKGROUND_COLOR          = 0x01, // Background is set to a color.
    GFX_BACKGROUND_IMAGE          = 0x02, // Background is set to an image.
    GFX_BACKGROUND_DISPLAY_BUFFER = 0x03, // Background is set to the current
                                          // content of the display buffer.
                                          // This requires support of
                                          // GFX_PixelArrayGet().
} GFX_BACKGROUND_TYPE;

/***************************************************************
  Description:
    Defines the states of a Graphics Library feature that can be
    enabled/disabled at run time.                               
  ***************************************************************/
typedef enum
{
    GFX_FEATURE_ENABLED = 1,
    GFX_FEATURE_DISABLED = 0,
} GFX_FEATURE_STATUS;


/*********************************************************************
 Overview: Defines the types of text alignment. The text alignment
           is used in GFX_TextStringBoxDraw().

*********************************************************************/
typedef enum
{
    GFX_ALIGN_LEFT             = 0x0C01,   // left aligned text
    GFX_ALIGN_HCENTER          = 0x0C02,   // horizontal center aligned text
    GFX_ALIGN_RIGHT            = 0x0C04,   // right aligned text

    GFX_ALIGN_TOP              = 0x0C10,   // top aligned text
    GFX_ALIGN_VCENTER          = 0x0C20,   // vertical center aligned text
    GFX_ALIGN_BOTTOM           = 0x0C40,   // bottom aligned text

    GFX_ALIGN_CENTER           = 0x0C22,   // vertical & horizontal center
                                           // aligned text

// DOM-IGNORE-START
    GFX_ALIGN_HORIZONTAL_MASK  = 0x0C07,   // horizontal mask, DO
                                           // NOT document this item
    GFX_ALIGN_VERTICAL_MASK    = 0x0C70,   // vertical mask, DO
                                           // NOT document this item
// DOM-IGNORE-END
            
} GFX_ALIGNMENT;

/*********************************************************************
 Overview: Transparency type when rendering characters with
           anti-aliasing.

*********************************************************************/
typedef enum
{
    GFX_FONT_ANTIALIAS_OPAQUE = 0,        // Mid colors are calculated only
                                          // once while rendering each
                                          // character. This is ideal for
                                          // rendering text over a constant
                                          // background.
    GFX_FONT_ANTIALIAS_TRANSLUCENT = 1    // Mid colors are calculated for
                                          // every necessary pixel. This
                                          // feature is useful when rendering
                                          // text over an image or when the
                                          // background is not one flat color.
} GFX_FONT_ANTIALIAS_TYPE;


/*********************************************************************
 Overview: Status types for rendering.

*********************************************************************/
typedef enum
{
    GFX_STATUS_FAILURE          = 0,
    GFX_STATUS_SUCCESS          = 1,
} GFX_STATUS;

/*********************************************************************
 Overview: Bit masks for additional status information.

*********************************************************************/
typedef enum
{
    GFX_STATUS_FAILURE_BIT      = 0,
    GFX_STATUS_SUCCESS_BIT      = 1,
    GFX_STATUS_ERROR_BIT        = 2,
    GFX_STATUS_BUSY_BIT         = 4,
    GFX_STATUS_READY_BIT        = 8,
} GFX_STATUS_BIT;

// DOM-IGNORE-BEGIN
/*********************************************************************
 Overview: Internal macro that returns the graphics GFX_STATUS.

*********************************************************************/
#define BITS_2_GFX_STATUS(mask) (mask & GFX_STATUS_SUCCESS)
// DOM-IGNORE-END

/*********************************************************************
* Overview: Bevel shapes can be rendered in full or half size. The following
*	    types defines the full, top and bottom halves.
*
*********************************************************************/
typedef enum
{
    GFX_DRAW_FULLBEVEL          = 0xFF,   // render full bevel shape
    GFX_DRAW_TOPBEVEL           = 0xF0,   // render top bevel shape
    GFX_DRAW_BOTTOMBEVEL        = 0x0F    // render bottom half bevel shape
} GFX_BEVEL_RENDER_TYPE;

/*********************************************************************
* Overview: Structure describing the background information. Useful in
*           refreshing the whole screen or an area of the screen.
*           The background information, when used, can be one of the
*           enumerated types in GFX_BACKGROUND_TYPE.
*           - pBackGroundImage - pointer to a GFX_RESOURCE_HEADER with
*                                the type GFX_RESOURCE_TYPE_MCHP_MBITMAP.
*           - backGroundColor - value of the background color used when
*                                pBackgroundImage is NULL.
*           The pBackGroundImage has the high priority and will assume
*           an image is used as a background when the pointer is
*           initialized. If this is NULL the backgroundColor is
*           assumed to be the background.
*   TODO: needs to move this to gfx_types_macros.h
*********************************************************************/
typedef struct
{
    uint16_t            left;     // Horizontal starting position of the background.
    uint16_t            top;      // Horizontal starting position of the background.
    GFX_BACKGROUND_TYPE type;     // Specifies the type of background to use.
    GFX_RESOURCE_HDR    *pImage;  // Pointer to the background image used. Set this
                                  // to NULL if not used.
    GFX_COLOR           color;    // If the background image is NULL, background is
                                  // assumed to be this color.

} GFX_BACKGROUND;

/*********************************************************************
* Overview: Structure describing the partial image area to render.
*
*********************************************************************/
typedef struct
{
    uint16_t            width;              // Partial Image width
    uint16_t            height;             // Partial Image height
    uint16_t            xoffset;            /*******************************************************************
                                              xoffset of the partial image (with respect to the image horizontal
                                              origin)                                                           
                                              *******************************************************************/
    uint16_t            yoffset;            /*****************************************************************
                                              yoffset of the partial image (with respect to the image vertical
                                              origin)                                                         
                                              *****************************************************************/
} GFX_PARTIAL_IMAGE_PARAM;

/*********************************************************************
* Overview: Structure describing a rectangular area in the frame buffer.
*
*********************************************************************/
typedef struct
{
    uint16_t left;
    uint16_t top;
    uint16_t right;
    uint16_t bottom;
} GFX_RECTANGULAR_AREA;

#ifndef GFX_MAX_INVALIDATE_AREAS
#define GFX_MAX_INVALIDATE_AREAS 5
#endif

/*********************************************************************
* Overview: Structure used to manage double buffering feature.
*
*********************************************************************/
typedef struct
{
    GFX_FEATURE_STATUS      gfxDoubleBufferFeature;
    GFX_FEATURE_STATUS      gfxDoubleBufferRequestSync;
    GFX_FEATURE_STATUS      gfxDoubleBufferFullSync;
    GFX_RECTANGULAR_AREA    gfxDoubleBufferAreas[GFX_MAX_INVALIDATE_AREAS];
    uint16_t                gfxUnsyncedAreaCount;
} GFX_DOUBLE_BUFFERING_MODE;

/*********************************************************************
* Overview: RGB Conversion macro. 24 BPP color to x BPP color
*           conversion.
*           Color depths of 1, 2 or 4 are usually for monochrome/grayscale
*           format so we are not defining any RGB conversion here.
*
*********************************************************************/
#if (GFX_CONFIG_COLOR_DEPTH == 8)

    #ifndef GFX_RGBConvert
		/*********************************************************************
		* Macros:  GFX_RGBConvert(red, green, blue)
		*
		* Overview: This macro converts the color data to the selected
		*           COLOR_DEPTH. This macro is only valid when COLOR_DEPTH is 8, 16, or 24.
		*
		*	<TABLE>
		*    	COLOR_DEPTH            Conversion
		*     	##################     ############
		*     	8                      8-8-8 to 3-3-2 conversion
		*     	16                     8-8-8 to to 5-6-5 conversion
		*     	24                     8-8-8 to 8-8-8 conversion or no conversion
		*	</TABLE>
		*
		* PreCondition: none
		*
		* Input: red - red component of the color.
		*        green - green component of the color.
		*        blue - blue component of the color.
		*
		* Output: none
		*
		* Side Effects: none
		*
		********************************************************************/
        #define GFX_RGBConvert(red, green, blue)    (GFX_COLOR) (((GFX_COLOR)(red) & 0xE0) | (((GFX_COLOR)(green) & 0xE0) >> 3) | (((GFX_COLOR)(blue)) >> 6))
    #endif

#elif (GFX_CONFIG_COLOR_DEPTH == 16)

    #ifndef GFX_RGBConvert
		/*********************************************************************
		* Macros:  GFX_RGBConvert(red, green, blue)
		*
		* Overview: This macro converts the color data to the selected
		*           COLOR_DEPTH. This macro is only valid when COLOR_DEPTH is 8, 16, or 24.
		*
		*	<TABLE>
		*    	COLOR_DEPTH            Conversion
		*     	##################     ############
		*     	8                      8-8-8 to 3-3-2 conversion
		*     	16                     8-8-8 to to 5-6-5 conversion
		*     	24                     8-8-8 to 8-8-8 conversion or no conversion
		*	</TABLE>
		*
		* PreCondition: none
		*
		* Input: red - red component of the color.
		*        green - green component of the color.
		*        blue - blue component of the color.
		*
		* Output: none
		*
		* Side Effects: none
		*
		********************************************************************/
        #define GFX_RGBConvert(red, green, blue)    (GFX_COLOR) ((((GFX_COLOR)(red) & 0xF8) << 8) | (((GFX_COLOR)(green) & 0xFC) << 3) | ((GFX_COLOR)(blue) >> 3))
    #endif

   #define ConvertColor50(color)  (GFX_COLOR)((color & (0b1111011111011110))>>1)
   #define ConvertColor25(color)  (GFX_COLOR)((color & (0b1110011110011100))>>2)
   #define ConvertColor75(color)  (GFX_COLOR)(ConvertColor50(color) + ConvertColor25(color))

#elif (GFX_CONFIG_COLOR_DEPTH == 24)

    #ifndef GFX_RGBConvert
 		/***********************************************************************
 		  Description:
 		    Macros: GFX_RGBConvert(red, green, blue)
 		    
 		    This macro converts the color data to the selected COLOR_DEPTH. This
 		    macro is only valid when COLOR_DEPTH is 8, 16, or 24.
 		    
 		    <table>
 		    COLOR_DEPTH   Conversion
 		    ############  ###########################################
 		    8             8-8-8 to 3-3-2 conversion
 		    16            8-8-8 to 5-6-5 conversion
 		    24            8-8-8 to 8-8-8 conversion or no conversion
 		    </table>
 		  Conditions:
 		    none
 		  Input:
 		    red -    red component of the color.
 		    green -  green component of the color.
 		    blue -   blue component of the color.
 		  Return:
 		    none
 		  Side Effects:
 		    none                                                                
 		  ***********************************************************************/
         #define GFX_RGBConvert(red, green, blue)    (GFX_COLOR) (((GFX_COLOR)(red) << 16) | ((GFX_COLOR)(green) << 8) | (GFX_COLOR)(blue))
    #endif

   #define ConvertColor50(color)  (GFX_COLOR)((color & (0x00FEFEFEul))>>1)
   #define ConvertColor25(color)  (GFX_COLOR)((color & (0x00FCFCFCul))>>2)
   #define ConvertColor75(color)  (GFX_COLOR)(ConvertColor50(color) + ConvertColor25(color))

#endif

/*********************************************************************
* Overview: 75, 50, 25 percentage color conversion macros.
*           Used in converting colors to these percentages when
*           performing alpha blending of colors using software
*           alpha blending operation.
*
*********************************************************************/
#if (GFX_CONFIG_COLOR_DEPTH == 16)

   #define ConvertColor50(color)  (GFX_COLOR)((color & (0b1111011111011110))>>1)
   #define ConvertColor25(color)  (GFX_COLOR)((color & (0b1110011110011100))>>2)
   #define ConvertColor75(color)  (GFX_COLOR)(ConvertColor50(color) + ConvertColor25(color))

#elif (GFX_CONFIG_COLOR_DEPTH == 24)

   #define ConvertColor50(color)  (GFX_COLOR)((color & (0x00FEFEFEul))>>1)
   #define ConvertColor25(color)  (GFX_COLOR)((color & (0x00FCFCFCul))>>2)
   #define ConvertColor75(color)  (GFX_COLOR)(ConvertColor50(color) + ConvertColor25(color))

#endif

// Note: Gradient feature does not support
//       GFX_CONFIG_COLOR_DEPTH values of 8, 4 and 1.
//       Gradient feature is not enabled when palette is enabled

#if (GFX_CONFIG_COLOR_DEPTH == 24)
    #define GFX_ComponentRedGet(color)       (((color) & 0xFF0000) >> 16)
    #define GFX_ComponentGreenGet(color)     (((color) & 0x00FF00) >> 8)
    #define GFX_ComponentBlueGet(color)      ((color) & 0x0000FF)
#else
    #define GFX_ComponentRedGet(color)       (((color) & 0xF800) >> 8)
    #define GFX_ComponentGreenGet(color)     (((color) & 0x07E0) >> 3)
    #define GFX_ComponentBlueGet(color)      (((color) & 0x001F) << 3)
#endif

#endif // _GFX_TYPES_MACROS_H
