/*******************************************************************
  Company:
    Microchip Technology Inc.
    
  File Name:
    gfx_display_driver.h

  Summary:
    GFX Display Driver definitions
    
  Description:
    GFX Display Driver definitions
    
    This file describes the GFX Display Driver specific definitions.
  *******************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _DISPLAYDRIVER_H
#define _DISPLAYDRIVER_H

#include "system_config.h"
#include "gfx/gfx_types_macros.h"
#include "driver/pmp/drv_pmp.h"


#if !defined (GFX_CONFIG_DRIVER_COUNT)
    #define GFX_CONFIG_DRIVER_COUNT 1
#endif

extern inline void __attribute__ ((always_inline)) DriverInterfaceInit(DRV_HANDLE *pmphandle, DRV_PMP_MODE_CONFIG *config)
{ 

    // Open the instance DRV_PMP_INDEX_0 with Non-blocking and Shared intent
    *pmphandle = DRV_PMP_Open(DRV_PMP_INDEX_0, DRV_IO_INTENT_SHARED | DRV_IO_INTENT_NONBLOCKING);

    if( *pmphandle == DRV_HANDLE_INVALID )
    {
        // Client cannot open the instance.
    }

    config->pmpMode = PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT;
    #ifdef USE_16BIT_PMP
    config->portSize = PMP_DATA_SIZE_16_BITS;
    #else
    config->portSize = PMP_DATA_SIZE_8_BITS;
    #endif

    config->waitStates.dataHoldWait = PMP_DATA_HOLD_1;
    config->waitStates.dataWait = PMP_DATA_WAIT_THREE;
    config->waitStates.strobeWait = PMP_STROBE_WAIT_8;
    config->intMode = PMP_INTERRUPT_EVERY_RW_CYCLE;

    // Configure the client
    DRV_PMP_ModeConfig ( *pmphandle, *config );

}

typedef struct
{
    uint8_t type;
    uint8_t on;
    uint8_t page;
    short   left;
    short   top;
    uint16_t width;
    uint16_t height;
    short   layerLeft;
    short   layerTop;
} GFX_LAYER_PARAMS;

typedef struct
{
    uint8_t foregroundPage;
    short   foregroundLeft; 
    short   foregroundTop;
    uint8_t backgroundPage; 
    short   backgroundLeft; 
    short   backgroundTop;
    uint8_t destinationPage; 
    short   destinationLeft; 
    short   destinationTop;
    uint8_t alpha;
    GFX_COLOR prevAlphaColor;		            
} GFX_ALPHA_PARAMS;

/*********************************************************************
* Function: Alpha Macros
********************************************************************/
#define 	NUM_ALPHA_LEVELS 	0x20			// Specific to device
#define 	ALPHA_DELTA 		((NUM_ALPHA_LEVELS) << 5)
/*********************************************************************
* Function: BYTE Percentage2Alpha(BYTE alphaPercentage)
********************************************************************/
extern inline uint8_t __attribute__ ((always_inline)) Percentage2Alpha(uint8_t alphaPercentage)
{
    uint32_t percent = (uint32_t)(alphaPercentage);
    percent *= (ALPHA_DELTA);
    percent /= 100;
    percent >>= 5;

    return (uint8_t)percent;
}

// *********************************************************************
/* 
  Structure: GFX_DRV_FUNCTIONS

  Summary: Structure containing the driver functions used by the primitive layer.

  Description: This structure needs to be defined in the driver file to inform the primitive layer
  as to what functions are available.
*/
//
typedef struct
{
// *****************************************************************************
/*
  Function: *PixelsPut(short x,short y,uint16_t count, uint16_t lineCount)

  Summary:
    This function sends pixels of an X,Y location to the LCD controller of a given count and linecount.

  Description:

  Input:
     x - x pixel location
     y - y pixel location
     count - amount of pixels for one line
     lineCount - amount of lines to render

  Output:
    Queue Status
*/
uint16_t      (*PixelsPut)(short,short,uint16_t, uint16_t);
// *****************************************************************************
/*
  Function: *BarFill(short left, short top, short right, short bottom)

  Summary:
    This function sends a 2D accelerated Bar command to the LCD controller

  Description:
    

  Input:
    left - left pixel location for the bar
     top - top pixel location for the bar
   right - right pixel location for the bar
  bottom - bottom pixel location for the bar

  Output:
     Queue Status 
*/
uint16_t      (*BarFill)(short,short,short,short);
// *****************************************************************************
/*
  Function: *PixelArrayPut(uint16_t* array,short x,short y,uint16_t count, uint16_t lineCount)

  Summary:
    This function sends an array of pixels at an X,Y location to the LCD controller of a given count and linecount 
    from a memory location.

  Description:   

  Input:
     array - starting location of the array to "put"
         x - x pixel location
         y - y pixel location
     count - number of pixels to render per line
 lineCount - number of lines
    

  Output:
    Queue Status
*/
uint16_t*     (*PixelArrayPut)(uint16_t*,short,short,uint16_t, uint16_t);
// *****************************************************************************
/*
  Function: *PixelArrayGet(uint16_t* array,short x,short y,uint16_t count)

  Summary:
    This function gets an array of pixels at an X,Y location to the LCD controller of a given count and linecount 
    from a memory location.

  Description:

  Input:
         array - starting location of the array to "get"
         x - x pixel location
         y - y pixel location
         count - number of pixels to render per line

  Output:
    Queue Status
*/
uint16_t*     (*PixelArrayGet)(uint16_t*,short,short,uint16_t);
/************************************************************************
  Function:
     uint16_t PixelPut(short x, short y)
    
  Summary:
    This function sends a pixel of an X,Y location to the LCD controller.
  Description:
    Input:
    x -  x pixel location
    y -  y pixel location
  Return:
    Queue Status                                                         
  ************************************************************************/
uint16_t      (*PixelPut)(short,short);
// *****************************************************************************
/*
  Function: *ColorSet(GFX_COLOR color)

  Summary:
    This function sets the global color for the display driver

  Description:
    TODO

  Input:
    color - color of the driver

  Output:
    None
*/
void          (*ColorSet)(GFX_COLOR);
// *****************************************************************************
/*
  Function: *InstanceSet(uint8_t instance)

  Summary:
    This function sets the global color for the display driver

  Description:

  Input:
	instance - instance of the driver

  Output:
    None.
*/
void          (*InstanceSet)(uint8_t);
/*********************************************
  Function:
     uint16_t PageSet(uint8_t pageType, uint8_t page)
    
  Summary:
    See Primitive PageSet Definition
  Description:
    See Primitive PageSet Definition
  Return:
    Queue Status                              
  *********************************************/
uint16_t      (*PageSet)(uint8_t, uint8_t);
// *****************************************************************************
/*
  Function: *Layer(uint8_t, GFX_LAYER_PARAMS*)

  Summary:
    See Primitive Layer Definition

  Description:
    See Primitive Layer Definition

  Input:
    See Primitive Layer Definition

  Output:
    Queue Status
*/
uint16_t*     (*Layer)(uint8_t, GFX_LAYER_PARAMS*);
// *****************************************************************************
/*
  Function: *PixelGet(short x,short y)

  Summary:
    This function gets a pixel of an X,Y location to the LCD controller.

  Description:


  Input:
    x - x pixel location.
    y - y pixel location

  Output:
    pixel color
*/
uint16_t      (*PixelGet)(short,short);
// *****************************************************************************
/*
  Function: *AlphaBlendWindow(GFX_ALPHA_PARAMS*, uint16_t, uint16_t, uint8_t)

  Summary:
    See Primitive AlphaBlendWindow Definition

  Description:
    See Primitive AlphaBlendWindow Definition

  Input:
    See Primitive AlphaBlendWindow Definition

  Output:
    Queue Status
*/
uint16_t*     (*AlphaBlendWindow)(GFX_ALPHA_PARAMS*, uint16_t, uint16_t, uint8_t);
} GFX_DRV_FUNCTIONS;

// *********************************************************************
/* 
  Structure: GFX_DRV_DATA

  Summary: Structure containing the driver graphics controller data.

  Description: Each driver in order to be registered with the primitive layer needs these values.
	they are mainly dependent on the chosen LCD.
*/
//
typedef struct
{
   uint16_t	 orientation;  // Orientation of the display (given in degrees of 0,90,180,270)
   uint16_t      horizontalResolution; // Horizontal Resolution of the displayed orientation in Pixels		
   uint16_t      verticalResolution; // Vertical resolution of the displayed orientation in pixels
   uint16_t      dataWidth;
   uint16_t      horizontalPulseWidth; // Horizontal Pulse Width of the LCD
   uint16_t      horizontalBackPorch; // Horizontal BackPorch of the LCD
   uint16_t      horizontalFrontPorch; // Horizontal FrontPorch of the LCD
   uint16_t      verticalPulseWidth; // Vertical Pulse width of the LCD
   uint16_t      verticalBackPorch; // Vertical BackPorch of the LCD
   uint16_t      verticalFrontPorch; // Vertical FrontPorch of the LCD
   uint8_t       logicShift; // Rising/Falling edge indicator of the LCD pixel clock
   enum          {LCD_TFT = 1,LCD_MSTN,LCD_CSTN} LCDType; //LCD type
   uint8_t       colorType;                 //color depth (18BPP, 24BPP, 8BPP, palette)
   void          (*TCON_Init)(void);             //flag to
   GFX_DRV_FUNCTIONS      PrimitiveFunction; // List of Primitive Rendering functions available by the driver
   uint8_t       driverBusy; // Flag to indicate driver is currently busy
   uint8_t       ready; // Flag to indicate driver has been initialized and recognized by the primitive layer
   GFX_COLOR     color; // current Color set for the display driver
   volatile uint8_t       activePage; // current activepage set for the display driver
   volatile uint8_t       visualPage; //current visualPage set for the display driver
} GFX_DRV_DATA;

// *********************************************************************
/* 
  Enumeration: PAGE_TYPE

  Summary: types of pages supported by the GFX Library

  Description: 

*/
//

typedef enum
{
	ACTIVE_PAGE   = 0, 
	VISUAL_PAGE,
    BACKGROUND_PAGE,
    FOREGROUND_PAGE,
    DESTINATION_PAGE,
    TRANSITION_PAGE      //Page that displays the transition 
} PAGE_TYPE;

// *********************************************************************
/* 
  Enumeration: LAYER_TYPE

  Summary: types of Layers supported by the GFX Library

  Description: 

*/
//

typedef enum
{
    PIP1 = 0,
    PIP2
} LAYER_TYPE;

extern volatile GFX_DRV_DATA GFX_DRV_instance[1];
    
#endif
