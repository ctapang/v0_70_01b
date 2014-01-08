/***********************************************************************
  Company:
    Microchip Technology Incorporated
  File Name:
    drv_gfx_otm2201a.h
  Summary:
    Interface for the graphics library where the primitives are rendered
    and sent to the graphics controller either external or internal
  Description:
    None                                                                
  ***********************************************************************/
//DOM-IGNORE-BEGIN
 /* Software License Agreement
  Copyright ? 2008 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).

  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.

  SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY
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

#ifndef _DRV_GFX_OTM2201A_H
    #define _DRV_GFX_OTM2201A_H

    #include "driver/gfx/drv_gfx_display.h"

#if defined(GFX_USE_DISPLAY_CONTROLLER_OTM2201A)

#define GFX_DRV_OTM2201A_COMMANDQUEUESIZE    480

#define DEGREE_0                            0
#define DEGREE_90                           90
#define DEGREE_180                          180
#define DEGREE_270                          270

#define RAM_LINE_WIDTH                      256

#define DRV_OTM2201A_NEW_INSTANCE_OPEN       1
#define DRV_OTM2201A_INSTANCE_DOESNT_EXIST   2
#define DRV_OTM2201A_INSTANCE_ALREADY_OPEN   3

#define DRV_OTM2201A_INSTANCE_CLOSED         0
#define DRV_OTM2201A_INSTANCE_VALID          1
#define DRV_OTM2201A_INSTANCE_ALREADY_CLOSED 3

#define NUM_BYTES_2                         2

#define REPEAT_CNT_0                        0

#define REG_ADDR_LOW_INDEX_SET              0
#define REG_ADDR_LOW_DATA_SET               1
#define REG_ADDR_HIGH_INDEX_SET             2
#define REG_ADDR_HIGH_DATA_SET              3

#define REG_WRITE_INDEX_SET                 0
#define REG_WRITE_DATA_SET                  1
#define REG_READ_DUMMY_DATA                 1
#define REG_READ_DATA                       2
#define REG_TRANSFER_STATUS                 3

#define DRV_OTM2201A_ERROR_NO_ERROR          0
#define DRV_OTM2201A_ERROR_PMP_WRITE         1
#define DRV_OTM2201A_ERROR_PMP_READ          1
#define DRV_OTM2201A_ERROR_QUEUE_FULL        1
#define DRV_OTM2201A_ERROR_REG_GET           1
#define DRV_OTM2201A_ERROR_REG_SET           1
#define DRV_OTM2201A_ERROR_DEVICE_BUSY       1


#define DRV_OTM2201A_ADDR_LOW_MASK           0x000000FF
#define DRV_OTM2201A_ADDR_LOW_SHIFT          0

#define DRV_OTM2201A_ADDR_HIGH_MASK          0x0000FF00
#define DRV_OTM2201A_ADDR_HIGH_SHIFT         8

#define DRV_OTM2201A_FEATURE_NOT_SUPPORTED   1

#define DATA_WIDTH_18                       18
#define DATA_WIDTH_24                       24

//DOM-IGNORE-END

// *********************************************************************
/*
  Enum: OTM2201A_TASK

  Summary:
        Enumeration for command type.

  Description:
        Enumeration for command type.

  Input:
        INITIALIZE  - driver initialization task
        BUSY        - driver busy task
        PUT_ARRAY   - driver put array task
        PUT_PIXELS  - driver put pixels task
*/

typedef enum
{
    INITIALIZE = 0,
    BUSY,
    PUT_ARRAY,
    PUT_PIXELS,
} OTM2201A_TASK;



// *********************************************************************
/*
  Structure: GFX_DRV_OTM2201A_COMMAND

  Summary:
        Structure for the commands in the driver queue.

  Description:
        Structure for the commands in the driver queue.

  Input:
        instance    - instance of the driver
        address     - pixel address
        array       - pointer to array of pixel data
        data        - pixel color
        count       - count number of pixels in one line
        lineCount   - lineCount number of lines of display
        task        - Type of task (OTM2201A_TASK enum)
*/

typedef struct
{
   uint8_t                     instance;
   uint32_t                     address;
   uint16_t                      *array;
   uint16_t                        data;
   uint16_t                       count;
   uint16_t                   lineCount;
   OTM2201A_TASK                    task;
} GFX_DRV_OTM2201A_COMMAND;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_OTM2201A_AddressSet(uint32_t address)

  Summary:
    Sets the start GRAM address where pixel data to be written

  Description:
    Address consists of Lower 8 bit at Register REG_RAM_ADDR_LOW and Higher
    8 bit at Register REG_RAM_ADDR_HIGH

  Input:
    address - pixel address

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write,
    DRV_OTM2201A_ERROR_NO_ERROR - returns success without any error.
*/

uint16_t GFX_DRV_OTM2201A_AddressSet(uint32_t address);

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_OTM2201A_RegSet(
                                            uint16_t index,
                                            uint8_t value,
                                            uint32_t repeatCount
                                            )

  Summary:
    Updates graphics controller register value (byte access)

  Description:
    This call can set "value" of the register accessed by its "index" and can
 repeat the same by number of times mentioned in "repeatCount"

  Input:
    index       - register number
    value       - value to write to register
    repeatCount - repeatCount number of times value is to be written to the
                    register.

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write,
    DRV_OTM2201A_ERROR_NO_ERROR - returns success without any error.
*/
uint16_t GFX_DRV_OTM2201A_RegSet(
                                    uint16_t index,
                                    uint16_t value,
                                    uint32_t repeatCount
                                );

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_OTM2201A_RegGet(
                                            uint16_t index,
                                            uint8_t *data
                                            )

  Summary:
    Returns graphics controller register value (byte access)

  Description:
    Returns graphics controller register value (byte access)

  Input:
    index - register number
    *data - array to store register data

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write,
    DRV_OTM2201A_ERROR_PMP_READ  - returns error during PMP Read,
    DRV_OTM2201A_ERROR_NO_ERROR  - returns success without any error.
*/
uint8_t  GFX_DRV_OTM2201A_RegGet(
    uint16_t  index,
    uint16_t *data
);

/********************************************************************
  Function:
     GFX_DRV_OTM2201A_Open(uint8_t instance)
    
  Summary:
    Opens an instance of the graphics controller
  Description:
    Opens the instance of driver if instance is valid and not already
    opened
  Input:
    instance -  instance of the driver
  Return:
    DRV_OTM2201A_NEW_INSTANCE_OPEN - driver not initialized,
    DRV_OTM2201A_INSTANCE_DOESNT_EXIST - instance doesn't exist,
    DRV_OTM2201A_INSTANCE_ALREADY_OPEN - instance already open.      
  ********************************************************************/

uint16_t GFX_DRV_OTM2201A_Open(uint8_t instance);

// *****************************************************************************
/*
  Function: GFX_DRV_OTM2201A_Close(uint8_t instance)

  Summary:
    Closes an instance of the graphics controller

  Description:
    Closes an instance if instance exists and not already closed

  Input:
    instance - instance of the driver

  Output:
    DRV_OTM2201A_INSTANCE_CLOSED         - instance closed,
    DRV_OTM2201A_INSTANCE_DOESNT_EXIST   - instance doesn't exist,
    DRV_OTM2201A_INSTANCE_ALREADY_CLOSED - instance already closed.
 
*/

uint16_t GFX_DRV_OTM2201A_Close(uint8_t instance);

// *****************************************************************************
/*
 
  Function: void GFX_DRV_OTM2201A_ColorSet(GFX_COLOR color)

  Summary:
    Sets the color for the driver instance

  Description:
    Sets the color for the driver instance

  Input:
    color - 16 bit 565 format color value

  Output: none

*/

void GFX_DRV_OTM2201A_ColorSet(GFX_COLOR color);

// *****************************************************************************
/*

 Function: void GFX_DRV_OTM2201A_InstanceSet(uint8_t instance)

  Summary:
    Sets the instance for the driver

  Description:
    Sets the instance for the driver

  Input:
    instance - driver instance

  Output: none
 
*/

void GFX_DRV_OTM2201A_InstanceSet(uint8_t instance);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_OTM2201A_PixelsPut(
                                                short x,
                                                short y,
                                                uint16_t count
                                                uint16_t lineCount
                                                )

  Summary:
    Outputs count number of pixels into the frame buffer from the given x,y
    coordinate.

  Description:
    Outputs count number of pixels into the frame buffer from the given x,y
    coordinate.

  Input:

        x           - pixel coordinate on x axis
        y           - pixel coordinate on y axis
        count       - count number of pixels
        lineCount   - lineCount number of display lines

  Output:

    DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full,
    DRV_OTM2201A_ERROR_NO_ERROR     - Success without any error.
 
*/

uint16_t GFX_DRV_OTM2201A_PixelsPut( short x,
                                    short y,
                                    uint16_t count,
                                    uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_OTM2201A_PixelPut(short x, short y)

  Summary:
    Outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    Outputs one pixel into the frame buffer at the x,y coordinate given

  Input:
 
        x           - pixel coordinate on x axis
        y           - pixel coordinate on y axis

  Output:

        DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full,
        DRV_OTM2201A_ERROR_NO_ERROR     - Success without any error.
 
*/
uint16_t GFX_DRV_OTM2201A_PixelPut(short x, short y);

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_OTM2201A_PixelArrayPut(
                                                      uint16_t *color,
                                                      short x,
                                                      short y,
                                                      uint16_t count,
                                                      uint16_t lineCount
                                                    )

  Summary:
    Outputs an array of pixels of length count starting at *color

  Description:
    Outputs an array of pixels of length count starting at *color

  Input:
        color       - pointer to array of color of pixels
        x           - pixel coordinate on x axis.
        y           - pixel coordinate on y axis.
        count       - count number of pixels
        lineCount   - lineCount number of display lines
 
  Output:
        handle - handle to the number of pixels remaining,
        DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full.
 
*/
uint16_t* GFX_DRV_OTM2201A_PixelArrayPut(   uint16_t *color,
                                            short x,
                                            short y,
                                            uint16_t count,
                                            uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_OTM2201A_PixelArrayGet(uint16_t *color,
                                                    short x,
                                                    short y,
                                                    uint16_t count)

  Summary:
    Gets an array of pixels of length count into an array starting at *color

  Description:
    Gets an array of pixels of length count into an array starting at *color

  Input:
            color   - Pointer to array where color data is to be loaded
            x       - pixel coordinate on x axis
            y       - pixel coordinate on y axis
            count   - count number of pixels
  Output:
         DRV_OTM2201A_ERROR_QUEUE_FULL  - OTM2201A command queue is full,
         DRV_OTM2201A_ERROR_NO_ERROR    - Success without any error.
*/

uint16_t* GFX_DRV_OTM2201A_PixelArrayGet(uint16_t *color, short x, short y, uint16_t count);


/*************************************************************************
  Function:
     uint16_t GFX_DRV_OTM2201A_Initialize(uint8_t instance)
    
  Summary:
    Initialize OTM2201A device
  Description:
    Initialize OTM2201A device by initializing PMP interface, initializing
    command buffer for current instance initialize device registers
  Input:
    instance -  driver instance
  Return:
    DRV_OTM2201A_ERROR_QUEUE_FULL - OTM2201A command queue is full,
    DRV_OTM2201A_ERROR_REG_GET - OTM2201A Error while reading register,
    DRV_OTM2201A_ERROR_REG_SET - OTM2201A Error while writing register,
    DRV_OTM2201A_ERROR_DEVICE_BUSY - OTM2201A device is busy,
    DRV_OTM2201A_ERROR_NO_ERROR - Success without any error.              
  *************************************************************************/
uint16_t GFX_DRV_OTM2201A_Initialize(uint8_t instance);

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_OTM2201A_Busy(uint8_t instance)

  Summary:
    Returns non-zero value if LCD controller is busy
          (previous drawing operation is not completed).

  Description:
    Returns non-zero value if LCD controller is busy
          (previous drawing operation is not completed).

  Input:
          instance - driver instance

  Output:
         DRV_OTM2201A_ERROR_DEVICE_BUSY - Device is busy,
         DRV_OTM2201A_ERROR_NO_ERROR    - Success, driver is not busy.
 
*/
uint16_t GFX_DRV_OTM2201A_Busy(uint8_t instance);

/*************************************************************************
  Function:
      void GFX_DRV_OTM2201A_Tasks(void)
    
  Summary:
    Task machine that renders the driver calls for the graphics library it
    must be called periodically to output the contents of its circular
    buffer
  Description:
    Task machine that renders the driver calls for the graphics library it
    must be called periodically to output the contents of its circular
    buffer.                                                               
  *************************************************************************/
void GFX_DRV_OTM2201A_Tasks(void);

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_OTM2201A_BrightnessSet(
    uint8_t instance,
    uint16_t level
    )

  Summary:
    Sets the brightness of the display backlight.

  Description:
    Sets the brightness of the display backlight.

  Input:
        instance    - instance of the driver
        level       - Brightness level. Valid values are 0 to 100.
		0   = brightness level is zero or display is turned off.
                100 = brightness level is maximum.

  Output:
    none
*/
void GFX_DRV_OTM2201A_BrightnessSet(uint8_t instance, uint16_t  level);

//DOM-IGNORE-BEGIN
/*
*******************************************************************************
* Overview: OTM2201A registers definitions.
*******************************************************************************
*/

#define REG_DEV_CODE_READ                       0x00
#define REG_DRV_OUT_CTRL                        0x01
#define REG_LCD_AC_DRV_CTRL                     0x02
#define REG_ENTRY_MODE                          0x03
#define REG_DISP_CTRL                           0x07
#define REG_BLANKING_CTRL                       0x08
#define REG_FRAME_CYCLE_CTRL                    0x0B
#define REG_EXTERNAL_INTERFACE_CTRL             0x0C
#define REG_OSC_CTRL                            0x0F
#define REG_POWER_CTRL_1                        0x10
#define REG_POWER_CTRL_2                        0x11
#define REG_POWER_CTRL_3                        0x12
#define REG_POWER_CTRL_4                        0x13
#define REG_POWER_CTRL_5                        0x14
#define REG_VCI_PERIOD                          0x15
#define REG_RAM_ADDR_LOW                        0x20
#define REG_RAM_ADDR_HIGH                       0x21
#define REG_GRAM_DATA                           0x22
#define REG_SW_RESET                            0x28
#define REG_GATE_SCAN_START_POS                 0x30
#define REG_VERT_SCROLL_CTRL_1                  0x31
#define REG_VERT_SCROLL_CTRL_2                  0x32
#define REG_VERT_SCROLL_CTRL_3                  0x33
#define REG_PART_SCREEN_AREA_1                  0x34
#define REG_PART_SCREEN_AREA_2                  0x35
#define REG_HORZ_WND_ADDR_1                     0x36
#define REG_HORZ_WND_ADDR_2                     0x37
#define REG_VERT_WND_ADDR_1                     0x38
#define REG_VERT_WND_ADDR_2                     0x39
#define REG_GAMMA_CTRL_1                        0x50
#define REG_GAMMA_CTRL_2                        0x51
#define REG_GAMMA_CTRL_3                        0x52
#define REG_GAMMA_CTRL_4                        0x53
#define REG_GAMMA_CTRL_5                        0x54
#define REG_GAMMA_CTRL_6                        0x55
#define REG_GAMMA_CTRL_7                        0x56
#define REG_GAMMA_CTRL_8                        0x57
#define REG_GAMMA_CTRL_9                        0x58
#define REG_GAMMA_CTRL_10                       0x59

//DOM-IGNORE-END

#endif //defined(GFX_USE_DISPLAY_CONTROLLER_OTM2201A)

#endif //defined (_DRV_GFX_OTM2201A_H)
