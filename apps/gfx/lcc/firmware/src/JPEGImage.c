/******************************************************************************
* This module allows displaying JPEG files from internal and external memories
*******************************************************************************
* File Name:       JPEG.c
* Dependencies:    Image decoding library
* Processor:       PIC24F, PIC24H, dsPIC, PIC32
* Compiler:        C30 v2.01/C32 v0.00.18
* Company:         Microchip Technology, Inc.

 * Software License Agreement
 *
 * Copyright © 2009 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.

Author                 Date           Comments
--------------------------------------------------------------------------------
Pradeep Budagutta    25-Jun-2008    First release
Anton Alkhimenok     05-May-2009    support for JPEG files from external memory
*******************************************************************************/
#include "JPEGImage.h"

/*******************************************************************************
    GLOBAL VARIABLES
*******************************************************************************/
uint32_t               _jpegImageIndex;    // pointer to current location in image
IMG_FILE_SYSTEM_API _jpegFileApi;       // structure with data access functions pointers

/*******************************************************************************
    LOCAL FUNCTIONS PROTOTYPES
*******************************************************************************/
size_t              JPEGfread(void *ptr, size_t size, size_t n, void *stream);  // read form image
bool                 JPEGfseek(void *stream, long offset, int whence);           // seek in image
bool                 JPEGfeof(void *stream); // eof of image

/*******************************************************************************
Function:       void JPEGInit()

Precondition:   None

Overview:       This function initializes JPEG decoder

Input:          None

Output:         None
*******************************************************************************/
void JPEGInit(void)
{
    _jpegFileApi.pFread = JPEGfread;
    _jpegFileApi.pFseek = JPEGfseek;
    _jpegFileApi.pFtell = NULL; // not used by JPEG decoder;
    _jpegFileApi.pFeof = JPEGfeof;
}

/*******************************************************************************
Function:       size_t JPEGfread(void *ptr, size_t size, size_t n, void* file)

Precondition:   None

Overview:       This function emulates file system's fread() on constant data
                in internal flash or external memory

Input:          Data buffer, size of data chunk, size of data type, file pointer

Output:         Number of bytes copied
*******************************************************************************/
size_t JPEGfread(void *ptr, size_t size, size_t n, void *file)
{
    size_t      index;
    uint8_t  *pFile;
    #ifdef USE_JPEG_EXTERNAL
    uint32_t       address;
    #endif
    int type;

    type = *((GFX_RESOURCE *)file);

    if((type & GFX_RESOURCE_TYPE_JPEG) != GFX_RESOURCE_TYPE_JPEG)
        return 0;

    
    switch(type & GFX_MEM_MASK)
    {
    #ifdef USE_JPEG_FLASH

        case GFX_RESOURCE_MEMORY_FLASH:
            pFile = (uint8_t*)((GFX_RESOURCE_HDR *)file)->resource.image.location.progByteAddress;

            uint8_t    *bptr = (uint8_t *)ptr;
            for(index = 0; index < size * n; index++)
            {
                bptr[index] = (uint8_t) pFile[_jpegImageIndex];
                _jpegImageIndex++;
            }

            break;
    #endif
    #ifdef USE_JPEG_EXTERNAL

        case EXTERNAL:
            address = _jpegImageIndex + ((IMAGE_EXTERNAL *)file)->address;
            ReadArray(address, (uint8_t *)ptr, size * n);  // macro calling the ReadArray function from the external memory driver

            // see JPEGImage.h
            index = size * n;
            _jpegImageIndex += index;
            break;
    #endif

        default:
            return (0);
    }

    return (index);
}

/*******************************************************************************
Function:       int JPEGfseek(void* stream, long offset, int whence)

Precondition:   None

Overview:       This function emulates file system's fseek() on constant data
                in internal flash or external memory. JPEG Decoder uses ONLY absolute and relative offsets.

Input:          File pointer, offset and the referance position

Output:         TRUE if success
*******************************************************************************/
bool JPEGfseek(void *stream, long offset, int whence)
{
    if(whence == 0)
    {
        _jpegImageIndex = offset;
    }
    else if(whence == 1)
    {
        _jpegImageIndex += offset;
    }
    else
    {
        return (false); // JPEG Decoder uses ONLY absolute and relative offsets
    }

    return (true);
}

/*******************************************************************************
Function:       int JPEGfeof(void *stream)

Precondition:   None

Overview:       This function emulates file system's feof() on constant data
                in Flash. JPEG Decoder doesn't use EOF.

Input:          File pointer

Output:         True if end of file is reached. JPEG Decoder doesn't use EOF.
                FALSE is returned.
*******************************************************************************/
bool JPEGfeof(void *stream)
{
    return (false); // JPEG Decoder doesn't use EOF
}

/*******************************************************************************
Function:       void* JPEGfopen(void* jpegImage)

Precondition:   None

Overview:       This function sets up the variables to emulate a file
                using constant data in internal flash or external memory

Input:          pointer to JPEG file image

Output:         pointer to JPEG file image
*******************************************************************************/
void *JPEGfopen(void *jpegImage)
{
    _jpegImageIndex = 0;
    return (jpegImage);
}
