/*******************************************************************************
  Graphics Image Decoder

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_imageDecoder.c

  Summary:
    This implements the image decoding of the primitive layer.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Image Decoder.
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

#include "../gfx_imageDecoder.h"

/**************************/
/**** GLOBAL VARIABLES ****/
/**************************/
IMG_FILE *IMG_pCurrentFile;

uint16_t IMG_wStartX;
uint16_t IMG_wStartY;
uint16_t IMG_wWidth;
uint16_t IMG_wHeight;
uint16_t IMG_wImageWidth;
uint16_t IMG_wImageHeight;
uint8_t IMG_bDownScalingFactor;
uint8_t IMG_bAlignCenter;
uint8_t IMG_blAbortImageDecoding;

#ifndef IMG_USE_ONLY_565_GRAPHICS_DRIVER_FOR_OUTPUT
IMG_PIXEL_OUTPUT IMG_pPixelOutput;
IMG_PIXEL_XY_RGB_888 IMG_PixelXYColor;
#endif

#ifndef IMG_USE_ONLY_MDD_FILE_SYSTEM_FOR_INPUT
IMG_FILE_SYSTEM_API *IMG_pFileAPIs;
#endif

/**************************/
/*******************************************************************************
Function:       void ImageDecoderInit(void)

Precondition:   None

Overview:       This function resets the variables and initializes the display

Input:          None

Output:         None
*******************************************************************************/
void ImageDecoderInit(void)
{
     IMG_wStartX = 0;
     IMG_wStartY = 0;
     IMG_wWidth  = 0;
     IMG_wHeight = 0;
     IMG_wImageWidth = 0;
     IMG_wImageHeight = 0;

   #ifndef IMG_USE_ONLY_565_GRAPHICS_DRIVER_FOR_OUTPUT
     IMG_pPixelOutput = NULL;
     IMG_PixelXYColor.X = 0;
     IMG_PixelXYColor.Y = 0;
     IMG_PixelXYColor.R = 0;
     IMG_PixelXYColor.G = 0;
     IMG_PixelXYColor.B = 0;
   #endif

   #ifndef IMG_USE_ONLY_MDD_FILE_SYSTEM_FOR_INPUT
     IMG_pFileAPIs = NULL;
   #endif

    IMG_blAbortImageDecoding = 0;

#ifdef IMG_USE_NON_BLOCKING_DECODING
    IMG_pCurrentFile = NULL;
#endif
}

/*******************************************************************************
Function:       BYTE ImageDecode(IMG_FILE *pImageFile, IMG_FILE_FORMAT eImgFormat, WORD wStartx, WORD wStarty, WORD wWidth, WORD wHeight, WORD wFlags, IMG_FILE_SYSTEM_API *pFileAPIs, IMG_PIXEL_OUTPUT pPixelOutput)

Precondition:   None

Overview:       This function uses the approperiate image decoding function to
                decode and display the image

Input:          File pointer, Kind of image, Image position and boundaries, If center alignment and downscaling to fit into the display is required, File System API pointer and function to output the decoded pixels

Output:         Error code - '0' means no error
*******************************************************************************/
uint8_t ImageDecode(IMG_FILE *pImageFile, IMG_FILE_FORMAT eImgFormat,
                 uint16_t wStartx, uint16_t wStarty, uint16_t wWidth, uint16_t wHeight,
                 uint16_t wFlags, IMG_FILE_SYSTEM_API *pFileAPIs,
                 IMG_PIXEL_OUTPUT pPixelOutput)
{

     static uint8_t state = 0;
     static uint8_t bRetVal = 0;

switch(state)
{
case 0:

     IMG_wStartX = wStartx;
     IMG_wStartY = wStarty;
     IMG_wWidth  = wWidth;
     IMG_wHeight = wHeight;
     IMG_wImageWidth = 0;
     IMG_wImageHeight = 0;

     IMG_bDownScalingFactor = (wFlags & IMG_DOWN_SCALE)? 1: 0;
     IMG_bAlignCenter = (wFlags & IMG_ALIGN_CENTER)? 1: 0;
     
   #ifndef IMG_USE_ONLY_565_GRAPHICS_DRIVER_FOR_OUTPUT
     IMG_pPixelOutput = pPixelOutput;
   #endif

   #ifndef IMG_USE_ONLY_MDD_FILE_SYSTEM_FOR_INPUT
     IMG_pFileAPIs = pFileAPIs;
   #endif
    state = 1;

case 1:
     switch(eImgFormat)
     {
      #ifdef IMG_SUPPORT_BMP
       case IMG_BMP: 
                     bRetVal = BMP_bDecode(pImageFile);
                     break;
      #endif
      #ifdef IMG_SUPPORT_JPEG
       case IMG_JPEG: bRetVal = JPEG_bDecode(pImageFile);
                     break;
      #endif
      #ifdef IMG_SUPPORT_GIF
       case IMG_GIF: bRetVal = GIF_bDecode(pImageFile);
                     break;
      #endif
       default:      bRetVal = 0xFF;
     }
}
     if(bRetVal != 0xff) 
     {
        state = 0; //Reset State Machine
     }

     return(bRetVal);

}

/*******************************************************************************
Function:       BYTE IMG_vSetboundaries(void)

Precondition:   None

Overview:       This function sets the boundaries and scaling factor. THIS IS
                NOT FOR THE USER.

Input:          None

Output:         None
*******************************************************************************/
void IMG_vSetboundaries(void)
{
     if(IMG_bDownScalingFactor > 0)
     {
         uint16_t wXScalingFactor = IMG_wImageWidth / IMG_wWidth;
         uint16_t wYScalingFactor = IMG_wImageHeight / IMG_wHeight;

         if(wXScalingFactor * IMG_wWidth < IMG_wImageWidth)
         {
             wXScalingFactor++;
         }
         if(wYScalingFactor * IMG_wHeight < IMG_wImageHeight)
         {
             wYScalingFactor++;
         }

         IMG_bDownScalingFactor = (uint8_t)(wXScalingFactor > wYScalingFactor)? wXScalingFactor: wYScalingFactor;

         if(IMG_bDownScalingFactor <= 1)
         {
             IMG_bDownScalingFactor = 0;
         }
     }

     if(IMG_bAlignCenter > 0)
     {
         uint8_t bDownScalingFactor = (IMG_bDownScalingFactor <= 1)? 1: IMG_bDownScalingFactor;
         if(IMG_wWidth > (IMG_wImageWidth / bDownScalingFactor))
         {
             IMG_wStartX += (IMG_wWidth - (IMG_wImageWidth / bDownScalingFactor)) / 2;
         }
         if(IMG_wHeight > (IMG_wImageHeight / bDownScalingFactor))
         {
             IMG_wStartY += (IMG_wHeight - (IMG_wImageHeight / bDownScalingFactor)) / 2;
         }
     }
}
