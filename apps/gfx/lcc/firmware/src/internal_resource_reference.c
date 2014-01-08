/*****************************************************************************
  AUTO-GENERATED CODE:  Graphics Resource Converter version: 4.00.39 BETA

  Company:
      Microchip Technology, Inc.
 
  File Name:
     internal_resource_reference.c
 
  Summary:
      This file is generated by the Microchip's Graphics Resource Converter.
  Description:
      This file is generated by the Graphics Resource Converter containing
      resources such as images and fonts that can be used by Microchip's
      Graphics Library, which is part of the MLA.
 *****************************************************************************/

// DOM-IGNORE-BEGIN
/*****************************************************************************
  Software License Agreement

  Copyright(c) 2013 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller that is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).
 
  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.
 
  SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS.
 *****************************************************************************/
// DOM-IGNORE-END

/*****************************************************************************
 * SECTION:  Includes
 *****************************************************************************/
#include <gfx/gfx.h>
#include <stdint.h>

/*****************************************************************************
 * SECTION:  Graphics Library Firmware Check
 *****************************************************************************/
#if(GRAPHICS_LIBRARY_VERSION != 0x0400)
#warning "It is suggested to use Graphics Library version 4.00 with this version of GRC."
#endif

/*****************************************************************************
 * SECTION:  Graphics Bitmap Padding Check
 *****************************************************************************/
#ifdef GFX_CONFIG_IMAGE_PADDING_DISABLE
#error These bitmap resources have been converted with padding of the horizontal lines, but GFX_CONFIG_IMAGE_PADDING_DISABLE is defined in system_config.h.
#endif


/*****************************************************************************
 * SECTION:  Graphics Configuration: Bitmap Check
 *****************************************************************************/

#ifdef GFX_CONFIG_IMAGE_FLASH_DISABLE
#error The GFX_CONFIG_IMAGE_FLASH_DISABLE is defined in system_config.h header file.
#endif

/*****************************************************************************
 * SECTION:  Graphics Configuration: Font Check
 *****************************************************************************/

#ifdef GFX_CONFIG_FONT_FLASH_DISABLE
#error The GFX_CONFIG_FONT_FLASH_DISABLE is defined in system_config.h header file.
#endif


/*****************************************************************************
 * SECTION:  BITMAPS
 *****************************************************************************/

/*********************************
 * Bitmap Structure
 * Label: Back_4bpp_16x16
 * Description:  16x16 pixels, 4-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __Back_4bpp_16x16[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __Back_4bpp_16x16[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR Back_4bpp_16x16 =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __Back_4bpp_16x16,
    .resource.image.width = 16,
    .resource.image.height = 16,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 164,
    .resource.image.colorDepth = 4,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*********************************
 * Bitmap Structure
 * Label: MCHPFolderEmpty_8bpp_72x72
 * Description:  72x72 pixels, 8-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __MCHPFolderEmpty_8bpp_72x72[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __MCHPFolderEmpty_8bpp_72x72[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR MCHPFolderEmpty_8bpp_72x72 =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __MCHPFolderEmpty_8bpp_72x72,
    .resource.image.width = 72,
    .resource.image.height = 72,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 5700,
    .resource.image.colorDepth = 8,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*********************************
 * Bitmap Structure
 * Label: MCHPFolderFile_8bpp_72x72
 * Description:  72x72 pixels, 16-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __MCHPFolderFile_8bpp_72x72[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __MCHPFolderFile_8bpp_72x72[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR MCHPFolderFile_8bpp_72x72 =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __MCHPFolderFile_8bpp_72x72,
    .resource.image.width = 72,
    .resource.image.height = 72,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 10372,
    .resource.image.colorDepth = 16,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*********************************
 * Bitmap Structure
 * Label: MchpIcon
 * Description:  100x58 pixels, 4-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __MchpIcon[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __MchpIcon[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR MchpIcon =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __MchpIcon,
    .resource.image.width = 100,
    .resource.image.height = 58,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 2936,
    .resource.image.colorDepth = 4,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*********************************
 * Bitmap Structure
 * Label: mouse
 * Description:  13x15 pixels, 4-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __mouse[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __mouse[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR mouse =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __mouse,
    .resource.image.width = 13,
    .resource.image.height = 15,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 140,
    .resource.image.colorDepth = 4,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*********************************
 * Bitmap Structure
 * Label: Pacman
 * Description:  90x50 pixels, 4-bits per pixel
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __Pacman[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __Pacman[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR Pacman =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_MCHP_MBITMAP | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __Pacman,
    .resource.image.width = 90,
    .resource.image.height = 50,
    .resource.image.parameter1.compressedSize = 0,
    .resource.image.parameter2.rawSize = 2284,
    .resource.image.colorDepth = 4,
    .resource.image.type = 0x00,
    .resource.image.paletteID = 0x0000
};

/*****************************************************************************
 * SECTION:  JPEGS
 *****************************************************************************/

/*********************************
 * JPEG Structure
 * Label: clouds
 * Description:  141x107 pixels
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __clouds[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __clouds[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR clouds =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_JPEG | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __clouds,
    .resource.image.width = 141,
    .resource.image.height = 107,
    .resource.image.parameter1.reserved = 0,
    .resource.image.parameter2.reserved = 0,
    .resource.image.colorDepth = 16
};

/*********************************
 * JPEG Structure
 * Label: Demo
 * Description:  480x272 pixels
 ***********************************/
#if defined (GFX_CONFIG_IMAGE_PACKED_ENABLE) && (__XC16_VERSION__ >= 1011)
extern uint8_gfx_image_prog __Demo[] __attribute__((section("grc_images")));
#else
extern uint8_gfx_image_prog __Demo[] __attribute__((section("grc_images"), aligned(2)));
#endif

const GFX_RESOURCE_HDR Demo =
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_JPEG | GFX_RESOURCE_COMP_NONE),
    .ID = 0,
    .resource.image.location.progByteAddress = (uint8_gfx_image_prog *) __Demo,
    .resource.image.width = 480,
    .resource.image.height = 272,
    .resource.image.parameter1.reserved = 0,
    .resource.image.parameter2.reserved = 0,
    .resource.image.colorDepth = 16
};

/*****************************************************************************
 * SECTION:  FONTS
 *****************************************************************************/

/*********************************
 * Installed Font Structure
 * Label: Monospaced_bold_Bold_72
 * Description:  Height: 95 pixels, 1 bit per pixel, Range: '0' to '9'
 ***********************************/
#if defined(GFX_CONFIG_FONT_PROG_SPACE_ENABLE) && (__XC16_VERSION__ >= 1011)
#ifndef GFX_CONFIG_FONT_PACKED_ENABLE
extern GFX_FONT_SPACE char __Monospaced_bold_Bold_72[] __attribute__((section("grc_text"), aligned(2)));
#else
extern GFX_FONT_SPACE char __Monospaced_bold_Bold_72[] __attribute__((section("grc_text")));
#endif
#else
extern GFX_FONT_SPACE char __Monospaced_bold_Bold_72[] __attribute__((aligned(2)));
#endif

const GFX_RESOURCE_HDR Monospaced_bold_Bold_72 = 
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_COMP_NONE),
    .ID = 0x0000,
    .resource.font.location.progByteAddress = (GFX_FONT_SPACE char *) __Monospaced_bold_Bold_72,
    .resource.font.header.fontID = 0,
    .resource.font.header.extendedGlyphEntry = 0,
    .resource.font.header.res1 = 0,
    .resource.font.header.bpp = 0,
    .resource.font.header.orientation = 0,
    .resource.font.header.res2 = 0,
    .resource.font.header.firstChar = 0x0030,
    .resource.font.header.lastChar = 0x0039,
    .resource.font.header.height = 0x005F,
};
/*********************************
 * Installed Font Structure
 * Label: Monospaced_plain_36
 * Description:  Height: 48 pixels, 1 bit per pixel, Range: ' ' to 'z'
 ***********************************/
#if defined(GFX_CONFIG_FONT_PROG_SPACE_ENABLE) && (__XC16_VERSION__ >= 1011)
#ifndef GFX_CONFIG_FONT_PACKED_ENABLE
extern GFX_FONT_SPACE char __Monospaced_plain_36[] __attribute__((section("grc_text"), aligned(2)));
#else
extern GFX_FONT_SPACE char __Monospaced_plain_36[] __attribute__((section("grc_text")));
#endif
#else
extern GFX_FONT_SPACE char __Monospaced_plain_36[] __attribute__((aligned(2)));
#endif

const GFX_RESOURCE_HDR Monospaced_plain_36 = 
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_COMP_NONE),
    .ID = 0x0000,
    .resource.font.location.progByteAddress = (GFX_FONT_SPACE char *) __Monospaced_plain_36,
    .resource.font.header.fontID = 0,
    .resource.font.header.extendedGlyphEntry = 0,
    .resource.font.header.res1 = 0,
    .resource.font.header.bpp = 0,
    .resource.font.header.orientation = 0,
    .resource.font.header.res2 = 0,
    .resource.font.header.firstChar = 0x0020,
    .resource.font.header.lastChar = 0x007A,
    .resource.font.header.height = 0x0030,
};
/*********************************
 * TTF Font File Structure
 * Label: Gentium_16
 * Description:  Height: 19 pixels, 1 bit per pixel, Range: ' ' to '~'
 ***********************************/
#if defined(GFX_CONFIG_FONT_PROG_SPACE_ENABLE) && (__XC16_VERSION__ >= 1011)
#ifndef GFX_CONFIG_FONT_PACKED_ENABLE
extern GFX_FONT_SPACE char __Gentium_16[] __attribute__((section("grc_text"), aligned(2)));
#else
extern GFX_FONT_SPACE char __Gentium_16[] __attribute__((section("grc_text")));
#endif
#else
extern GFX_FONT_SPACE char __Gentium_16[] __attribute__((aligned(2)));
#endif

const GFX_RESOURCE_HDR Gentium_16 = 
{
    .type = (GFX_RESOURCE_MEMORY_FLASH | GFX_RESOURCE_TYPE_FONT | GFX_RESOURCE_COMP_NONE),
    .ID = 0x0000,
    .resource.font.location.progByteAddress = (GFX_FONT_SPACE char *) __Gentium_16,
    .resource.font.header.fontID = 0,
    .resource.font.header.extendedGlyphEntry = 0,
    .resource.font.header.res1 = 0,
    .resource.font.header.bpp = 0,
    .resource.font.header.orientation = 0,
    .resource.font.header.res2 = 0,
    .resource.font.header.firstChar = 0x0020,
    .resource.font.header.lastChar = 0x007E,
    .resource.font.header.height = 0x0013,
};
