/*******************************************************************************
 Graphics Resource Types Header for Microchip Graphics Library 

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_font_types.h

  Summary:
    This header file defines the types used in fonts for the Microchip Graphics 
    Library.

  Description:
    This header defines the different structures used for fonts resources in the 
    Microchip Graphics Library. 
    
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

#ifndef GFX_TYPES_FONTS_H
    #define GFX_TYPES_FONTS_H

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "system_config.h"


/*******************************************************************************
  Summary:
    Configuration for the text character size.
  Description:
    GFX_CONFIG_FONT_CHAR_SIZE
    
    This configuration sets the text character size used in the library.
    
    To enable support for unicode fonts, GFX_CONFIG_FONT_CHAR_SIZE must be
    defined as 16 (size is 16 bits). For standard ASCII fonts, this can be
    defined as 8. This changes the GFX_XCHAR definition. See GFX_XCHAR for
    details.
    
    <table>
    Set in configuration        GFX_XCHAR            \Description
    \#define                    \#define GFX_XCHAR   Use multiuint8_t characters
     GFX_CONFIG_FONT_CHAR_SIZE   uint16_t             (0-2^16 range).
     16                                               
    \#define                    \#define GFX_XCHAR   Use multiuint8_t characters
     GFX_CONFIG_FONT_CHAR_SIZE   uint8_t              (0-255 range).
     8                                                
    </table>
  Remarks:
    None.                                                                       
  ******************************************************************************
  ####################################    #############################   ##########################*/
#if (GFX_CONFIG_FONT_CHAR_SIZE == 16)
    #define GFX_XCHAR   uint16_t
    #define GFX_UXCHAR  uint16_t
#elif (GFX_CONFIG_FONT_CHAR_SIZE == 8)
    #define GFX_XCHAR   char
    #define GFX_UXCHAR  uint8_t
#else
    #define GFX_XCHAR   char
    #define GFX_UXCHAR  uint8_t
#endif

/**************************************************************************
 * Overview: Font space section.  The fonts can be located in psv (constant)
 * or program space in PIC24/dsPIC MCUs.  This define allows for switching
 * of the pointer type used to access the font structure in memory
 * See: GraphicsConfig.h for the application define.
 ***************************************************************************/
#ifdef GFX_LIB_CFG_USE_GFX_FONT_IN_PROGRAM_SECTION
#ifndef __PIC32MX__
#ifndef GFX_LIB_CFG_USE_PROG_PACKED_FONT
#define GFX_FONT_SPACE __prog__
#else
#define GFX_FONT_SPACE __pack_upper_byte
#endif
#else
#define GFX_FONT_SPACE const
#endif
#else
#define GFX_FONT_SPACE const
#endif

/*********************************************************************
* Overview: Structure describing the font header.
*
*********************************************************************/
typedef struct
{
    uint8_t     fontID;                     // User assigned value
    uint8_t     extendedGlyphEntry : 1;     // Extended Glyph entry flag. When set font has extended glyph feature enabled.
    uint8_t     res1               : 1;     // Reserved for future use  (must be set to 0)
    uint8_t     bpp                : 2;     // Actual BPP = 2<sup>bpp</sup>  
                                            //   - 0 - 1 BPP
                                            //   - 1 - 2 BPP
                                            //   - 2 - 4 BPP
                                            //   - 3 - 8 BPP
    uint8_t     orientation        : 2;     // Orientation of the character glyphs (0,90,180,270 degrees)
                                            //   - 00 - Normal
                                            //   - 01 - Characters rotated 270 degrees clockwise
                                            //   - 10 - Characters rotated 180 degrees
                                            //   - 11 - Characters rotated 90 degrees clockwise
                                            // Note: Rendering DO NOT rotate the characters. The table contains rotated characters
                                            //       and will be rendered as is.
    uint8_t     res2               : 2;     // Reserved for future use (must be set to 0).
    uint16_t    firstChar;                  // Character code of first character (e.g. 32).
    uint16_t    lastChar;                   // Character code of last character in font (e.g. 3006).
    uint16_t    height;                     // Font characters height in pixels.
} GFX_FONT_HEADER;

/*********************************************************************
* Overview: Structures describing the glyph entry.
*
*********************************************************************/
typedef struct
{
    uint8_t     width;                      // width of the glyph
    uint8_t     offsetLSB;                  // Least Significant uint8_t of the glyph location offset 
    uint16_t    offsetMSB;                  // Most Significant (2) uint8_ts of the glyph location offset
} GFX_FONT_GLYPH_ENTRY;

typedef struct
{
    uint32_t    offset;                     // Offset Order: LSW_LSB LSW_MSB MSW_MSB MSW_MSB
    uint16_t    cursorAdvance;              // x-value by which cursor has to advance after rendering the glyph
    uint16_t    glyphWidth;                 // width of the glyph
    int16_t     xAdjust;                    // x-position is adjusted as per this signed number
    int16_t     yAdjust;                    // y-position is adjusted as per this signed number
} GFX_FONT_GLYPH_ENTRY_EXTENDED;

/*********************************************************************
* Overview: Structure for character information when rendering the character.
*
*********************************************************************/
typedef struct 
{ 
#ifndef GFX_CONFIG_FONT_FLASH_DISABLE
    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY             *pChTable;
    GFX_FONT_SPACE GFX_FONT_GLYPH_ENTRY_EXTENDED    *pChTableExtended;
#endif
#ifndef GFX_CONFIG_FONT_EXTERNAL_DISABLE
    uint8_t                 chImage[GFX_EXTERNAL_FONT_RASTER_BUFFER_SIZE];
    int16_t                 chEffectiveGlyphWidth;
#endif
    uint8_t                 bpp;
    int16_t                 chGlyphWidth;
    GFX_FONT_SPACE uint8_t  *pChImage;
    int16_t                 xAdjust;
    int16_t                 yAdjust;
    int16_t                 xWidthAdjust;
    int16_t                 heightOvershoot;
} GFX_FONT_OUTCHAR;

#endif // GFX_TYPES_FONTS_H

