/*******************************************************************************
 Graphics Resource Types Header for Microchip Graphics Library

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_resource_types.h

  Summary:
    This is the definition of the Graphics Resource Types used with
    the Microchip Graphics Library.

  Description:
    This header defines the different structures used for the Graphics
    Resources used in the Graphics Library. This also contains helpful
    macros as well as data types used.

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

#ifndef GFX_TYPES_RESOURCE_H
    #define GFX_TYPES_RESOURCE_H

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/
#include <stdint.h>
#include "system_config.h"
#include "gfx/gfx_types_palette.h"
#include "gfx/gfx_types_font.h"
#include "gfx/gfx_types_image.h"

/*********************************************************************
* Overview: Memory type enumeration to determine the source of data.
*           Used in interpreting images, fonts and palette from different
*           memory sources.
*
*********************************************************************/
typedef enum
{
    GFX_RESOURCE_MEMORY_FLASH            = 0x0000,  // internal flash
    GFX_RESOURCE_MEMORY_EXTERNAL         = 0x0001,  // external memory
    GFX_RESOURCE_MEMORY_RAM              = 0x0004,  // RAM
    GFX_RESOURCE_MEMORY_EDS_EPMP         = 0x0005,  /*memory in EPMP, base addresses are set in the hardware profile*/

    GFX_RESOURCE_TYPE_MCHP_MBITMAP       = 0x0000,  // data resource is type Microchip
                                                    // bitmap
    GFX_RESOURCE_TYPE_JPEG               = 0x0100,  // data resource is type JPEG
    GFX_RESOURCE_TYPE_BINARY             = 0x0200,  // data resource is type binary
    GFX_RESOURCE_TYPE_FONT               = 0x0300,  // data resource is type font
    GFX_RESOURCE_TYPE_PALETTE            = 0x0400,  // data resource is type palette

    GFX_RESOURCE_COMP_NONE               = 0x0000,  // data resource has no compression
    GFX_RESOURCE_COMP_RLE                = 0x1000,  // data resource is compressed with RLE
    GFX_RESOURCE_COMP_IPU                = 0x2000,  // data resource compressed with
                                                    // DEFLATE (for IPU)

    // These are common resource combinations used by the graphics library
    // Bitmaps
    GFX_RESOURCE_MCHP_MBITMAP_FLASH_NONE = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_MCHP_MBITMAP_FLASH_RLE  = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_RLE),
    GFX_RESOURCE_MCHP_MBITMAP_FLASH_IPU  = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_IPU),

    GFX_RESOURCE_MCHP_MBITMAP_EXTERNAL_NONE    = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_MCHP_MBITMAP_EXTERNAL_RLE     = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_RLE),
    GFX_RESOURCE_MCHP_MBITMAP_EXTERNAL_IPU     = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_IPU),

    GFX_RESOURCE_MCHP_MBITMAP_EDS_EPMP_NONE    = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_MCHP_MBITMAP_EDS_EPMP_RLE     = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_RLE),
    GFX_RESOURCE_MCHP_MBITMAP_EDS_EPMP_IPU     = (GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_IPU),
    // JPEGS
    GFX_RESOURCE_JPEG_FLASH_NONE         = (GFX_RESOURCE_TYPE_JPEG | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_JPEG_EXTERNAL_NONE      = (GFX_RESOURCE_TYPE_JPEG | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_JPEG_EDS_EPMP_NONE      = (GFX_RESOURCE_TYPE_JPEG | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_NONE),
    // Binary
    GFX_RESOURCE_BINARY_FLASH_NONE       = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_BINARY_FLASH_IPU        = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_IPU),

    GFX_RESOURCE_BINARY_EXTERNAL_NONE    = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_BINARY_EXTERNAL_IPU     = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_IPU),

    GFX_RESOURCE_BINARY_EDS_EPMP_NONE    = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_BINARY_EDS_EPMP_IPU     = (GFX_RESOURCE_TYPE_BINARY | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_IPU),
    // Fonts
    GFX_RESOURCE_FONT_FLASH_NONE         = (GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_FONT_EXTERNAL_NONE      = (GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_FONT_RAM_NONE           = (GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_MEMORY_RAM | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_FONT_EDS_NONE           = (GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_MEMORY_EDS_EPMP | GFX_RESOURCE_COMP_NONE),
    // Palettes
    GFX_RESOURCE_PALETTE_FLASH_NONE      = (GFX_RESOURCE_TYPE_PALETTE | GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_PALETTE_EXTERNAL_NONE   = (GFX_RESOURCE_TYPE_PALETTE | GFX_RESOURCE_MEMORY_EXTERNAL | GFX_RESOURCE_COMP_NONE),
    GFX_RESOURCE_PALETTE_RAM_NONE        = (GFX_RESOURCE_TYPE_PALETTE | GFX_RESOURCE_MEMORY_RAM | GFX_RESOURCE_COMP_NONE),
} GFX_RESOURCE;

#define GFX_TYPE_MASK           0x0F00
#define GFX_COMP_MASK           0xF000
#define GFX_MEM_MASK            0x000F

#define MCHP_BITMAP_NORMAL      0x00                // no compression, palette is present
                                                    // for color depth = 8, 4 and 1 BPP
#define MCHP_BITMAP_PALETTE_STR 0x10                // palette is provided as a separate
                                                    // object (see PALETTE_HEADER) for
                                                    // color depth = 8, 4, and 1 BPP,
                                                    // ID to the palette is embedded in the bitmap.


/*********************************************************************
* Overview: Structure for Graphics Resource - image.
*
*********************************************************************/
typedef struct
{
    union
    {
        uint32_t                extAddress;         // generic address
        uint8_gfx_image_prog    *progByteAddress;   // for addresses in program
                                                    // section
        uint16_gfx_image_prog   *progWordAddress;   // for addresses in program
                                                    // section
        const char              *constAddress;      // for addresses in FLASH
        char                    *ramAddress;        // for addresses in RAM
#if defined(__PIC24F__)
        __eds__ char            *edsAddress;        // for addresses in EDS
#endif
    }location;
    
    uint16_t            width;                      // width of the image
    uint16_t            height;                     // height of the image

    union
    {
        uint32_t        compressedSize;             // Parameters used for the GFX_RESOURCE.
                                                    // Depending on the GFX_RESOURCE type
                                                    // definition of param1 can change. For
                                                    // IPU and RLE compressed images, param1
                                                    // indicates the compressed size of the image.
        uint32_t        reserved;
    } parameter1;
    union
    {
        uint32_t        rawSize;                    // Parameters used for the GFX_RESOURCE.
                                                    // Depending on the GFX_RESOURCE type
                                                    // definition of param2 can change. For
                                                    // IPU and RLE compressed images, param2
                                                    // indicates the uncompressed size of the image.
        uint32_t        reserved;
    } parameter2;

    uint8_t             colorDepth;                 // color depth of the image
    uint8_t             type;                       // type of image, information on how to 
                                                    // render the image  
                                                    // 0x00 - no compression, palette is present    
                                                    //       for color depth = 8, 4 and 1 BPP   
                                                    // 0x10 - palette is provided as a separate   
                                                    //        object (see PALETTE_HEADER) for    
                                                    //        color depth = 8, 4, and 1 BPP,    
                                                    //        ID to the palette is embedded
                                                    //        color depth = 8, 4, and 1 BPP,    
                                                    //        in the bitmap.
                                                    // 0xYY - reserved
    uint16_t            paletteID;                  // if type == MCHP_BITMAP_PALETTE_STR (0x10),
                                                    // this represents the unique 
                                                    // ID of the palette being used 
    
}GFX_RESOURCE_IMAGE;


/*********************************************************************
* Overview: Structure for Graphics Resource - Fonts.
*
*********************************************************************/
typedef struct
{
    union
    {
        uint32_t                extAddress;
        GFX_FONT_SPACE char     *progByteAddress;
        char                    *ramAddress;
#if defined(__PIC24F__)
        __eds__ char            *edsAddress;        // for addresses in EDS
#endif
    }location;
    GFX_FONT_HEADER             header;
}GFX_RESOURCE_FONT;

/*********************************************************************
* Overview: Structure for Graphics Resource - Palette.
*
*********************************************************************/
typedef struct
{
    union
    {
        uint32_t                extAddress;
        const GFX_PALETTE_ENTRY *constByteAddress;
        GFX_PALETTE_ENTRY       *ramAddress;
    }location;
    uint16_t numberOfEntries;
    uint16_t paletteID;                             // Unique ID of the palette that will match the ID
                                                    // in the GFX_RESOURCE_HDR if the image has palette
                                                    // removed and supplied as a separate object.

}GFX_RESOURCE_PALETTE;

/*********************************************************************
* Overview: Structure for Graphics Resource - binary data.
*
*********************************************************************/
typedef struct
{
    union
    {
        uint32_t                extAddress;         // generic address
        uint8_gfx_image_prog    *progByteAddress;   // for addresses in program section
        uint16_gfx_image_prog   *progWordAddress;   // for addresses in program section
        const char              *constAddress;      // for addresses in FLASH
        char                    *ramAddress;        // for addresses in RAM
#if defined(__PIC24F__)
        __eds__ char            *edsAddress;        // for addresses in EDS
#endif
    }location;

    uint32_t                    size;
    uint32_t                    param1;             // Parameters used for the GFX_RESOURCE. Depending on the GFX_RESOURCE type
                                                    // definition of param1 can change. For IPU and RLE compressed images, param1
                                                    // indicates the compressed size of the image.
    uint32_t                    param2;             // Parameters used for the GFX_RESOURCE. Depending on the GFX_RESOURCE type

}GFX_RESOURCE_BINARY;

/*********************************************************************
* Overview: Structure for Graphics Resource Header. This is the
*           common header for all Graphics Resources.
*
*********************************************************************/
typedef struct
{
    GFX_RESOURCE                type;               // Graphics resource type, determines the type 
                                                    // and location of data
    uint16_t                    ID;                 // memory ID, user defined value to differentiate
                                                    // between graphics resources of the same type
						    //   When using EDS_EPMP the following ID values are
						    //   reserved and used by the Microchip display driver
						    //   0 - reserved (do not use)
						    //   1 - reserved for base address of EPMP CS1
						    //   2 - reserved for base address of EPMP CS2

    union
    {
        GFX_RESOURCE_IMAGE      image;
        GFX_RESOURCE_FONT       font;
        GFX_RESOURCE_BINARY     binary;
        GFX_RESOURCE_PALETTE    palette;
    }resource;

}GFX_RESOURCE_HDR;

#endif // GFX_TYPES_RESOURCE_H

