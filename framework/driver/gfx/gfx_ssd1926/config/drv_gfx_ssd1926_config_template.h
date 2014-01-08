/**************************************************************************
    * Module for Microchip Graphics Library
    * This file contains compile time options for the Graphics Library.
  * ******************************************************************* *
    * File Name: GraphicsConfig.h
    * Dependencies: none
    * Processor: PIC24F, PIC24H, dsPIC, PIC32
    * Compiler: C30 V3.00/C32
    * Company: Microchip Technology Inc.
  &#42;
    * Software License Agreement
  &#42;
    * Copyright © 2008 Microchip Technology Inc. All rights reserved.
    * Microchip licenses to you the right to use, modify, copy and
      distribute
    * Software only when embedded on a Microchip microcontroller or
      digital
    * signal controller, which is integrated into your product or third
      party
    * product (pursuant to the sublicense terms in the accompanying
      license
    * agreement).
  &#42;
    * You should refer to the license agreement accompanying this
      Software
    * for additional information regarding your rights and obligations.
  &#42;
    * SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF
      ANY
    * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
      WARRANTY
    * OF MERCHANTABILITY, TITLE, NON&#45;INFRINGEMENT AND FITNESS FOR A
      PARTICULAR
    * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
    * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,
      CONTRIBUTION,
    * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR
      INDIRECT
    * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL,
      SPECIAL,
    * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
      DATA,
    * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR
      ANY
    * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
      THEREOF),
    * OR OTHER SIMILAR COSTS.
  &#42;
    * Author Date Comment
  &#42;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * Anton Alkhimenok 10/28/2007 Initial Version
    * Pradeep Budagutta 10/28/2007 Display related defines
    * moved to DisplayConfig.h
  \ \                                                                      
  **************************************************************************/
#ifndef _GRAPHICSCONFIG_H
    #define _GRAPHICSCONFIG_H

//////////////////// COMPILE OPTIONS AND DEFAULTS ////////////////////
	
/*********************************************************************
* Overview: Using Palettes, different colors can be used with the same
*			bit depth. Define this in GraphicsConfig.h
*
********************************************************************/
//#define USE_PALETTE 
	
/*********************************************************************
* Overview: Palettes can also be specified to reside in external memory
*           similar to fonts and images. Use this when the palette is
*           located in external memory. Define this in GraphicsConfig.h
*
********************************************************************/
//#define USE_PALETTE_EXTERNAL 

/*********************************************************************
* Overview: Keyboard control on some objects can be used by enabling
*			the GOL Focus (USE_FOCUS)support. Define this in GraphicsConfig.h
*
*********************************************************************/
//#define USE_FOCUS

/*********************************************************************
* Overview: Input devices macros that defines the messages that Objects 
*			will process. The following definitions indicate the usage  
*			of the different input devices:
*			- USE_TOUCHSCREEN - enables the touch screen support.
*			- USE_KEYBOARD - enables the key board support.
*           Define in GraphicsConfig.h
*         
*********************************************************************/
#define USE_TOUCHSCREEN			
//#define USE_KEYBOARD // <COPY USE_TOUCHSCREEN>

/*********************************************************************
* Overview: To save program memory, unused Widgets or Objects can be 
*			removed at compile time. Define in GraphicsConfig.h
*
*********************************************************************/
#define USE_GOL                 // Enable Graphics Object Layer.
#define USE_BUTTON          	// Enable Button Object.
#define USE_WINDOW				// Enable Window Object.
#define USE_CHECKBOX			// Enable Checkbox Object.
#define USE_RADIOBUTTON			// Enable Radio Button Object.
#define USE_EDITBOX				// Enable Edit Box Object.
#define USE_LISTBOX				// Enable List Box Object.
#define USE_SLIDER          	// Enable Slider or Scroll Bar Object.
#define USE_PROGRESSBAR			// Enable Progress Bar Object.
#define USE_STATICTEXT			// Enable Static Text Object.
#define USE_PICTURE				// Enable Picture Object.
#define USE_GROUPBOX			// Enable Group Box Object.
#define USE_ROUNDDIAL			// Enable Dial Object.
#define USE_METER				// Enable Meter Object.
#define USE_DIGITALMETER        // Enable DigitalMeter Object.
#define USE_TEXTENTRY			// Enable TextEntry Object.
#define USE_CUSTOM				// Enable Custom Control Object (an example to create customized Object).
#define USE_ANALOGCLOCK         // Enable Analog Clock Object.
#define USE_CHART

/*********************************************************************
* Overview: To enable support for unicode fonts, USE_MULTIBYTECHAR  
*			must be defined. This sets the XCHAR definition 
*           (0-2^16 range). See XCHAR for details. Define this in GraphicsConfig.h
*
*********************************************************************/
    #define USE_MULTIBYTECHAR

/*********************************************************************
* Overview: To enable support for unsigned characters data type for 
*           fonts, USE_UNSIGNED_XCHAR must be defined. This sets the 
*           XCHAR definition (0-255 range). See XCHAR for details.
*           Define this in GraphicsConfig.h
*
*********************************************************************/
 //   #define USE_UNSIGNED_XCHAR

/*********************************************************************
* Overview: Font data can be placed in two locations. One is in 
*			FLASH memory and the other is from external memory.
*			Definining one or both enables the support for fonts located
*			in internal flash and external memory. Define this in GraphicsConfig.h
*	- USE_FONT_FLASH - Font in internal flash memory support.	
*	- USE_FONT_EXTERNAL - Font in external memory support (including external memory mapped to EDS).	
*
*********************************************************************/
    #define USE_FONT_FLASH          
//    #define USE_FONT_EXTERNAL		// <COPY USE_FONT_FLASH>

/*********************************************************************
* Overview: Similar to Font data bitmaps can also be placed in 
*			two locations. One is in FLASH memory and the other is 
*			from external memory.
*			Definining one or both enables the support for bitmaps located
*			in internal flash and external memory. Define this in GraphicsConfig.h
*	- USE_BITMAP_FLASH - Images located in internal flash memory.	
*	- USE_BITMAP_EXTERNAL - Images located in external memory (including external memory mapped to EDS)..	
*
*********************************************************************/
    #define USE_BITMAP_FLASH        

/*********************************************************************
* Overview: When using Operating Systems (OS), define the OS specific 
*           malloc() and free() functions for compatibility with the  
*           OS based systems. Define these in GraphicsConfig.h
*
*********************************************************************/
	#define GFX_malloc(size)    	malloc(size)
	#define GFX_free(pObj)    	    free(pObj)		// <COPY GFX_malloc>

/*********************************************************************
* Overview: Specifies the color depth used in the application defined
*           in GraphicsConfig.h.  
*
*********************************************************************/
    #define COLOR_DEPTH             16

/*********************************************************************
* Overview: To enable support for Gradient bars and bevel primitives.
*           Define this in GraphicsConfig.h.
*
*********************************************************************/
	#define USE_GRADIENT

/*********************************************************************
* Overview: To enable support for Anti-aliased fonts. Use this feature
*           if the font table generated through the "Graphics Resource 
*           Converter" tool has the anti-aliasing enabled.
*           Define this in GraphicsConfig.h
*
*********************************************************************/
//	#define USE_ANTIALIASED_FONTS
     
/*********************************************************************
* Overview: Declare this macro to enable application layer to override
*           the Graphics Library supplied default GOL Scheme.
*           When this is defined, the application code must define 
*           GFX_OBJECT_SCHEME GOLSchemeDefault structure and initialize its
*           structure members to the user desired initial values.
*           Each call to GFX_OBJECT_SchemeCreate() will use the user defined
*           style scheme initialization. Define this in GraphicsConfig.h
*
*********************************************************************/
//    #define GFX_SCHEMEDEFAULT	

/*********************************************************************
* Overview: To enable support for transparent color in PutImage().
*           Enabling this macro enables the use of a transparent color
*           (set by TransparentColorEnable()) in rendering images by
*           PutImage(). When a pixel in the image matches the transparent
*           color set, the pixel is not rendered to the screen.
*           This is useful in rendering rounded icons or images to the 
*           screen with a complex background. Define this in GraphicsConfig.h
*
*********************************************************************/
//	#define USE_TRANSPARENT_COLOR	

/*********************************************************************
* Overview: Specifies the default font to be used is the user defined
*           font. This replaces the default font supplied by the 
*           Graphics Library.
*
*********************************************************************/
//    #define FONTDEFAULT  (YOUR_FONT_NAME)
	
/*********************************************************************
* Overview: To enable support for DEFLATE compressed images for PutImage(). 
*           When this macro is enabled, the PutImage() function will 
*           be able to process images generated by the Graphics Resource 
*           Converter (GRC) that are compressed using the DEFLATE algorithm.
*           PutImage() will need the IPU module of the Microchip Graphics 
*           Module to decompress. Enable this feature only when the driver
*           features the IPU module (example: PIC24FJ2456DA210).
*           Define this in GraphicsConfig.h
*
*********************************************************************/
//	#define USE_COMP_IPU	

	#define USE_COMP_RLE
	
/*********************************************************************
* Overview: When this macro is enabled, bitmap images used has no padding.
*           Define this in GraphicsConfig.h. 
*           When converting images for use in the Graphics Library, the 
*           Graphics Resource Converter has an option to set the images
*           to be padded or not padded. When bitmaps are padded, this means
*           that each horizontal line will start on a byte boundary. Unpadded  
*           bitmaps allows the least resource space for a bitmap. Unpadded
*           bitmaps also allows support for display controllers with windowing
*           and auto-increment features. 

*
*********************************************************************/
//#define USE_BITMAP_NO_PADDING_LINE

/*********************************************************************
* Overview: For XC16 or C30 builds only: When placing fonts in internal 
*           data memory, there is a 32K limit for data space. The total 
*           data should not exceed 32K. When this is unavoidable, the macro 
*           USE_GFX_FONT_IN_PROGRAM_SECTION will relocate the font in  
*           program space. This will remove the 32K restriction but at 
*           the expense of slower access. 
*           Define this in GraphicsConfig.h to enable the font to be 
*           placed in program space.
*
*********************************************************************/
//#define USE_GFX_FONT_IN_PROGRAM_SECTION

#define DRIVER_COUNT            1

#include "system_config.h"
	
#endif // _GRAPHICSCONFIG_H
