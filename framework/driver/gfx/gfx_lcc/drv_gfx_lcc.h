/***********************************************************************
  Company:
    Microchip Technology Inc.
  File Name:
    drv_gfx_lcc.h
  Summary:
    Interface for the graphics library where the primitives are rendered
    and sent to the graphics controller either external or internal
  Description:
    None                                                                
  ***********************************************************************/
//DOM-IGNORE-BEGIN
 /* Software License Agreement
  Copyright © 2008 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).  
 
  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.
 
  SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS. */
 //DOM-IGNORE-END

#ifndef _DRV_GFX_LCC_H
#define _DRV_GFX_LCC_H

#include "driver/gfx/drv_gfx_display.h"


#define USE_PIP
#define USE_LCC_SCROLLING

#define GFX_DRV_lcc_COMMANDQUEUESIZE 480

#ifdef USE_LCC_SCROLLING
extern uint16_t scroll,scrollLine,scrollPage;
#endif

#if defined (USE_PIP)
void GFX_PRIM_SetPIPWindow(uint16_t left, uint16_t top, uint16_t hlength, uint16_t vlength, uint16_t pipx, uint16_t pipy);
#define PIP_BUFFER  (3)
#endif

	typedef    enum 
    {
        UPDATE_CLOCK = 0,
	INITIALIZE,
        WAIT_TRANSMIT_PIXELS,
        FINISH_TRANSMIT_PIXELS,
        WAIT_TRANSMIT_ARRAY,
        FINISH_TRANSMIT_ARRAY,
        WAIT_RECEIVE,
        READ_RECEIVE,
	PUT_ARRAY,
	PUT_PIXELS,
        GET_PIXELS,
        COPY_PIXELS,
        PAGE,
        LAYERS
	} LCC_TASK;

	typedef    enum 
    {
        ACTIVE_PERIOD = 0,
	BLANKING_PERIOD,
        FINISH_LINE,
        OVERFLOW,
        PIP,
	SCROLL,
	} DMA_ISR_TASK;

//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *********************************************************************
/* 
  Structure: GFX_DRV_lcc_COMMAND

  Summary: Structure for the commands in the driver queue.

  Description: None
*/
// 
typedef struct
{
   uint8_t                      instance;
   union
   {
   uint32_t                      Val;
       struct
    {
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
        uint8_t b8:1;
        uint8_t b9:1;
        uint8_t b10:1;
        uint8_t b11:1;
        uint8_t b12:1;
        uint8_t b13:1;
        uint8_t b14:1;
        uint8_t b15:1;
        uint8_t b16:1;
        uint8_t b17:1;
        uint8_t b18:1;
        uint8_t b19:1;
        uint8_t b20:1;
        uint8_t b21:1;
        uint8_t b22:1;
        uint8_t b23:1;
        uint8_t b24:1;
        uint8_t b25:1;
        uint8_t b26:1;
        uint8_t b27:1;
        uint8_t b28:1;
        uint8_t b29:1;
        uint8_t b30:1;
        uint8_t b31:1;
    } bits;
   } address;
   uint16_t                       *array;
   uint16_t                         data;
   uint16_t                        count;
   uint16_t                    lineCount;
   uint8_t                          task; 
} GFX_DRV_lcc_COMMAND;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*
  Function: void GFX_DRV_lcc_SetColor(uint8_t instance, GFX_COLOR color)

  Summary: Sets the color for the driver instance

  Description:
  
  Output: none

*/

void GFX_DRV_lcc_SetColor(GFX_COLOR color);
uint16_t GFX_DRV_lcc_SetPage(uint8_t pageType,uint8_t page);
// *****************************************************************************
/*
  Function: void GFX_DRV_lcc_SetInstance(uint8_t instance)

  Summary: Sets the instance for the driver

  Description:
  
  Output: none

*/

void GFX_DRV_lcc_SetInstance(uint8_t instance);

/*********************************************************************
  Function:
     uint16_t GFX_DRV_lcc_Open(uint8_t instance)
    
  Summary:
    opens an instance of the graphics controller
  Description:
    none
  Return:
    1 - driver not initialized 2 - instance doesn't exist 3 - instance
    already open instance to driver when successful                   
  *********************************************************************/
uint16_t GFX_DRV_lcc_Open(uint8_t instance);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_lcc_Close(uint8_t instance)

  Summary:
    closes an instance of the graphics controller

  Description:
    none

  Input:
    instance of the driver

  Output:
    0 - instance closed
    2 - instance doesn't exist
    3 - instance already closed
*/
uint16_t GFX_DRV_lcc_Close(uint8_t instance);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_lcc_PixelsPut(short x, short y, uint16_t count)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        x,y - pixel coordinates

  Output:
          NULL - call not successful (lcc driver busy)
          !NULL - address of the display driver queue command
*/
uint16_t GFX_DRV_lcc_PixelsPut(short x, short y, uint16_t count, uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_lcc_PixelPut(short x, short y)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        x,y - pixel coordinates
  Output:
    NULL - call not successful (lcc driver busy)
    !NULL - address of the display driver queue command
*/
uint16_t GFX_DRV_lcc_PixelPut(short x, short y);

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_lcc_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count)

  Summary:
    outputs an array of pixels of length count starting at *color 

  Description:
    none

  Input:
          instance - driver instance
          *color - start of the array
	    x - x coordinate of the start point.
          y - y coordinate of the end point.
	    count - number of pixels
  Output:
         NULL - call not successful
         !NULL - handle to the number of pixels remaining
*/
uint16_t* GFX_DRV_lcc_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count, uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_lcc_PixelArrayGet(uint16_t *color, short x, short y, uint16_t count)

  Summary:
    gets an array of pixels of length count starting at *color 

  Description:
    none

  Input:
          instance - driver instance
          *color - start of the array
		  x - x coordinate of the start point.
		  y - y coordinate of the end point.
		  count - number of pixels
  Output:
         NULL  - call not successful (lcc driver busy)
         !NULL - address of the display driver queue command
*/ 
uint16_t* GFX_DRV_lcc_PixelArrayGet(uint16_t *color,short x, short y, uint16_t count);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_lcc_Initialize(uint8_t instance)

  Summary:
    resets LCD, initializes PMP

  Description:
    none

  Input:
        instance - driver instance
  Output:
    NULL - call not successful (PMP driver busy)
    !NULL - address of the display driver queue command
*/
uint16_t GFX_DRV_lcc_Initialize(uint8_t instance);

/*************************************************************************
  Function:
      void GFX_DRV_lcc_Tasks(void)
    
  Summary:
    Task machine that renders the driver calls for the graphics library it
    must be called periodically to output the contents of its circular
    buffer                                                                
  *************************************************************************/
void GFX_DRV_lcc_Tasks(void);

uint16_t* GFX_DRV_lcc_Layer(uint8_t instance, GFX_LAYER_PARAMS* layer);
// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_lcc_BrightnessSet(uint8_t instance, uint16_t level)

  Summary:
    Sets the brightness of the display backlight.

  Description:
    none

  Input:
        level - Brightness level. Valid values are 0 to 100.
			             -   0: brightness level is zero or display is turned off
			             - 100: brightness level is maximum 
  Output:
    none
*/
void GFX_DRV_lcc_BrightnessSet(uint8_t instance, uint16_t  level);

//DOM-IGNORE-BEGIN
     
#endif // _DRV_GFX_LCC_H
