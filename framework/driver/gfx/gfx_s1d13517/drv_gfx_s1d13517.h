/***********************************************************************
  Company:
    Microchip Technology Inc.
  File Name:
    S1D13517.h
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
 
#ifndef _S1D13517_H
    #define _S1D13517_H

    #include "driver/gfx/drv_gfx_display.h"

#if defined(GFX_USE_DISPLAY_CONTROLLER_S1D13517)

    extern uint8_t   _instance; //global color for the driver

#define GFX_DRV_S1D13517_COMMANDQUEUESIZE 480

	typedef enum {
	GFX_PAGE0 = 0,
	GFX_PAGE1,
	GFX_PAGE2,
	GFX_PAGE3,
	GFX_PAGE4,
	GFX_PAGE5,
	GFX_PAGE6,
	GFX_PAGE7,
	GFX_PAGE8,
	GFX_PAGE9,
	GFX_PAGE10,
	GFX_PAGE11,
	GFX_PAGE12,
	GFX_PAGE13,
	GFX_PAGE14,
	GFX_PAGE15,
	GFX_NUM_OF_PAGES
	} GFX_PAGE;

	typedef    enum 
    {
	INITIALIZE = 200,
        WINDOW_SETUP_8BIT,
        WINDOW_SETUP_16BIT,
	    PUT_ARRAY,
	    PUT_PIXELS,
        COPY_PIXELS,
        PAGE,
        ALPHA_BLEND,
        LAYERS
	} SSD1926_TASK;

//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************

// *********************************************************************
/* 
  Structure: GFX_DRV_S1D13517_COMMAND

  Summary: Structure for the commands in the driver queue.

  Description: None
*/
// 
typedef struct
{
   uint8_t                      instance;
   short                               x;
   short                               y;
   uint16_t                       *array;
   uint16_t                         data;
   uint16_t                        count;
   uint16_t                    lineCount;
   uint8_t                          task; 
} GFX_DRV_S1D13517_COMMAND;

// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*
  Function: void GFX_DRV_S1D13517_SetColor(GFX_COLOR color)

  Summary: Sets the color for the driver instance

  Description:
  
  Output: none

*/

void GFX_DRV_S1D13517_SetColor(GFX_COLOR color);

// *****************************************************************************
/*
  Function: void GFX_DRV_S1D13517_SetInstance(uint8_t instance)

  Summary: Sets the instance for the driver

  Description:
  
  Output: none

*/

void GFX_DRV_S1D13517_SetInstance(uint8_t instance);

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_S1D13517_SetReg(uint8_t index, uint8_t value)

  Summary:
    updates graphics controller register value (byte access)

  Description:
    none

  Input:
    index - register number 
    value - value to write to register

  Output:
    1 - call was not passed
    0 - call was passed
*/
uint16_t GFX_DRV_S1D13517_SetReg(uint8_t index, uint8_t value);

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_S1D13517_GetReg(uint8_t index, uint8_t *data)

  Summary:
    returns graphics controller register value (byte access)

  Description:
    none

  Input:
    index - register number 
    *data - array to store data

  Output:
    0 - when call was passed
*/
uint8_t  GFX_DRV_S1D13517_GetReg(uint8_t  index);

/*********************************************************************
  Function:
     GFX_DRV_S1D13517_Open(uint8_t instance)
    
  Summary:
    opens an instance of the graphics controller
  Description:
    none
  Return:
    1 - driver not initialized 2 - instance doesn't exist 3 - instance
    already open instance to driver when successful                   
  *********************************************************************/
uint16_t GFX_DRV_S1D13517_Open(uint8_t instance);

// *****************************************************************************
/*
  Function: GFX_DRV_S1D13517_Close(uint8_t instance)

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
uint16_t GFX_DRV_S1D13517_Close(uint8_t instance);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_S1D13517_PixelsPut(short x, short y, uint16_t count)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates

  Output:
          NULL - call not successful (PMP driver busy)
         !NULL - address of the display driver queue command
*/
uint16_t GFX_DRV_S1D13517_PixelsPut(short x, short y, uint16_t count, uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_S1D13517_PixelPut(uint8_t instance,uint16_t color, short x, short y)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates
  Output:
    NULL - call not successful (PMP driver busy)
    !NULL - address of the display driver queue command
*/
uint16_t GFX_DRV_S1D13517_PixelPut(short x, short y);

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_S1D13517_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count)

  Summary:
    outputs an array of pixels of length count starting at *color 

  Description:
    none

  Input:
          *color - start of the array
		  x - x coordinate of the start point.
		  y - y coordinate of the end point.
		  count - number of pixels
  Output:
         NULL - call not successful (PMP driver busy)
        !NULL - address to the number of pixels yet to be serviced
*/
uint16_t* GFX_DRV_S1D13517_PixelArrayPut(uint16_t *color,short x, short y, uint16_t count, uint16_t lineCount);

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_S1D13517_Initialize(uint8_t instance)

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
uint16_t GFX_DRV_S1D13517_Initialize(uint8_t instance);

/*************************************************************************
  Function:
      void GFX_DRV_S1D13517_Tasks(void)
    
  Summary:
    Task machine that renders the driver calls for the graphics library it
    must be called periodically to output the contents of its circular
    buffer                                                                
  *************************************************************************/
void GFX_DRV_S1D13517_Tasks(void);

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_S1D13517_BrightnessSet(uint8_t instance, uint16_t level)

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
void GFX_DRV_S1D13517_BrightnessSet(uint8_t instance, uint16_t  level);

// *****************************************************************************
/*
  Function:
    void GFX_DRV_S1D13517_SetPage(uint8_t pageType, uint8_t page)

  Summary:
    Sets the page of a certain page type

  Description:
    none

  Input:
        instance - driver instance
  Output:
     NULL - call not successful (PMP driver busy)
    !NULL - address of the display driver queue command
*/
uint16_t      GFX_DRV_S1D13517_SetPage(uint8_t pageType, uint8_t page);

// *****************************************************************************
/*
  Function:
    uint16_t* GFX_DRV_S1D13517_Layer(uint8_t type, GFX_LAYER_PARAMS* layer)

  Summary:
    Updates a Layer depending on the layer parameters.

  Description:
    none

  Input:
        type - layer type
        layer - parameters for Layer function call
  Output:
     NULL - call not successful (PMP driver busy)
    !NULL - address of the display driver queue command
*/
uint16_t*     GFX_DRV_S1D13517_Layer(uint8_t type, GFX_LAYER_PARAMS* layer);

// *****************************************************************************
/*
  Function:
	void GFX_DRV_S1D13517_AlphaBlendWindow(uint8_t pageType, uint8_t page)

  Summary:
    SEE primitive layer alphablendWindow definition

*/
uint16_t*      GFX_DRV_S1D13517_AlphaBlendWindow(GFX_ALPHA_PARAMS* alphaParams, uint16_t width, uint16_t height, uint8_t alpha);

//DOM-IGNORE-BEGIN
/*********************************************************************
* Overview: S1D13517 registers definitions.
*********************************************************************/
 	#define REG00_PROD_CODE        0x00     // Product Code Register [READONLY]
	#define REG02_READBACK         0x02     // Configuration Readback Register [READONLY]
	#define REG04_PLL_DDIVIDER     0x04     // PLL D-Divider Register
	#define REG06_PLL_0            0x06     // PLL Setting Register 0
	#define REG08_PLL_1            0x08     // PLL Setting Register 1
	#define REG0A_PLL_2            0x0A     // PLL Setting Register 2
	#define REG0C_PLL_NDIVIDER     0x0C     // PLL N-Divider Register
	#define REG0E_SS_CONTROL_0     0x0E     // SS Control Register 0
	#define REG10_SS_CONTROL_1     0x10     // SS Control Register 1
	#define REG12_CLK_SRC_SELECT   0x12     // Clock Source Select Register
	#define REG14_LCD_PANEL_TYPE   0x14     // LCD Panel Type Register
	#define REG16_HDISP_WIDTH      0x16     // Horizontal Display Width Register
	#define REG18_HNDP_PERIOD      0x18     // Horizontal Non-Display Period Register
	#define REG1A_VDISP_HEIGHT_0   0x1A     // Vertical Display Height Register 0
	#define REG1C_VDISP_HEIGHT_1   0x1C     // Vertical Display Height Register 1
	#define REG1E_VNDP_PERIOD      0x1E     // Vertical Non-Display Period Register
	#define REG20_PHS_PULSE_WIDTH  0x20     // PHS Pulse Width (HSW) Register
	#define REG22_PHS_PULSE_START  0x22     // PHS Pulse Start Position (HPS) Register
	#define REG24_PVS_PULSE_WIDTH  0x24     // PVS Pulse Width (VSW) Register
	#define REG26_PVS_PULSE_START  0x26     // PVS Pulse Start Position (VPS) Register
	#define REG28_PCLK_POLARITY    0x28     // PCLK Polarity Register
	#define REG2A_DSP_MODE         0x2A     // Display Mode Register
	#define REG2C_PIP1_DSP_SA_0    0x2C     // PIP1 Display Start Address Register 0
	#define REG2E_PIP1_DSP_SA_1    0x2E     // PIP1 Display Start Address Register 1
	#define REG30_PIP1_DSP_SA_2    0x30     // PIP1 Display Start Address Register 2
	#define REG32_PIP1_WIN_X_SP    0x32     // PIP1 Window X Start Position Register
	#define REG34_PIP1_WIN_Y_SP_0  0x34     // PIP1 Window Y Start Position Register 0
	#define REG36_PIP1_WIN_Y_SP_1  0x36     // PIP1 Window Y Start Position Register 1
	#define REG38_PIP1_WIN_X_EP    0x38     // PIP1 Window X End Position Register
	#define REG3A_PIP1_WIN_Y_EP_0  0x3A     // PIP1 Window Y End Position Register 0
	#define REG3C_PIP1_WIN_Y_EP_1  0x3C     // PIP1 Window Y End Position Register 1
	#define REG3E_PIP2_DSP_SA_0    0x3E     // PIP2 Display Start Address Register 0
	#define REG40_PIP2_DSP_SA_1    0x40     // PIP2 Display Start Address Register 1
	#define REG42_PIP2_DSP_SA_2    0x42     // PIP2 Display Start Address Register 2
	#define REG44_PIP2_WIN_X_SP    0x44     // PIP2 Window X Start Position Register
	#define REG46_PIP2_WIN_Y_SP_0  0x46     // PIP2 Window Y Start Position Register 0
	#define REG48_PIP2_WIN_Y_SP_1  0x48     // PIP2 Window Y Start Position Register 1
	#define REG4A_PIP2_WIN_X_EP    0x4A     // PIP2 Window X End Position Register
	#define REG4C_PIP2_WIN_Y_EP_0  0x4C     // PIP2 Window Y End Position Register 0
	#define REG4E_PIP2_WIN_Y_EP_1  0x4E     // PIP2 Window Y End Position Register 1
	#define REG50_DISPLAY_CONTROL  0x50     // Display Control Register [WRITEONLY]
	#define REG52_INPUT_MODE       0x52     // Input Mode Register
	#define REG54_TRANSP_KEY_RED   0x54     // Transparency Key Color Red Register
	#define REG56_TRANSP_KEY_GREEN 0x56     // Transparency Key Color Green Register
	#define REG58_TRANSP_KEY_BLUE  0x58     // Transparency Key Color Blue Register
	#define REG5A_WRITE_WIN_X_SP   0x5A     // Write Window X Start Position Register
	#define REG5C_WRITE_WIN_Y_SP_0 0x5C     // Write Window Start Position Register 0
	#define REG5E_WRITE_WIN_Y_SP_1 0x5E     // Write Window Start Position Register 1
	#define REG60_WRITE_WIN_X_EP   0x60     // Write Window X End Position Register
	#define REG62_WRITE_WIN_Y_EP_0 0x62     // Write Window Y End Position Register 0
	#define REG64_WRITE_WIN_Y_EP_1 0x64     // Write Window Y End Position Register 1
	#define REG66_MEM_DATA_PORT_0  0x66     // Memory Data Port Register 0 [WRITEONLY]
	#define REG67_MEM_DATA_PORT_1  0x67     // Memory Data Port Register 1 [WRITEONLY]
	#define REG68_POWER_SAVE       0x68     // Power Save Register
	#define REG6A_N_DISP_PER_CTRS  0x6A     // Non-Display Period Control/Status Register
	#define REG6C_GPO_0            0x6C     // General Purpose Output Register 0
	#define REG6E_GPO_1            0x6E     // General Purpose Output Register 1
	#define REG70_PWM_CONTROL      0x70     // PWM Control Register
	#define REG72_PWM_HIGH_DC_0    0x72     // PWM High Duty Cycle Register 0
	#define REG74_PWM_HIGH_DC_1    0x74     // PWM High Duty Cycle Register 1
	#define REG76_PWM_HIGH_DC_2    0x76     // PWM High Duty Cycle Register 2
	#define REG78_PWM_HIGH_DC_3    0x78     // PWM High Duty Cycle Register 3
	#define REG7A_PWM_LOW_DC_0     0x7A     // PWM Low Duty Cycle Register 0
	#define REG7C_PWM_LOW_DC_1     0x7C     // PWM Low Duty Cycle Register 1
	#define REG7E_PWM_LOW_DC_2     0x7E     // PWM Low Duty Cycle Register 2
	#define REG80_PWM_LOW_DC_3     0x80     // PWM Low Duty Cycle Register 3
	#define REG82_SDRAM_CONTROL_0  0x82     // SDRAM Control Register 0
	#define REG84_SDRAM_STATUS_0   0x84     // SDRAM Status Register 0 [WRITEONLY]
	#define REG86_SDRAM_STATUS_1   0x86     // SDRAM Status Register 1 [READONLY]
	#define REG88_SDRAM_MRS_VAL_0  0x88     // SDRAM MRS Value Register 0
	#define REG8A_SDRAM_MRS_VAL_1  0x8A     // SDRAM MRS Value Register 1
	#define REG8C_SDRAM_RFS_CNT_0  0x8C     // SDRAM Refresh Counter Register 0
	#define REG8E_SDRAM_RFS_CNT_1  0x8E     // SDRAM Refresh Counter Register 1
	#define REG90_SDRAM_BUF_SIZE   0x90     // SDRAM Write Buffer Memory Size Register
	#define REG92_SDRAM_DEBUG      0x92     // SDRAM Debug Register
	#define REG94_ALP_CONTROL      0x94     // Alpha-Blend Control Register [WRITEONLY]
	#define REG96_ALP_STATUS       0x96     // Alpha-Blend Status Register [READONLY]
	#define REG98_ALP_HR_SIZE      0x98     // Alpha-Blend Horizontal Size Register
	#define REG9A_ALP_VR_SIZE_0    0x9A     // Alpha-Blend Vertical Size Register 0
	#define REG9C_ALP_VR_SIZE_1    0x9C     // Alpha-Blend Vertical Size Register 1
	#define REG9E_ALP_VALUE        0x9E     // Alpha-Blend Value Register
	#define REGA0_ALP_IN_IMG1_SA_0 0xA0     // Alpha-Blend Input Image 1 Start Address Register 0
	#define REGA2_ALP_IN_IMG1_SA_1 0xA2     // Alpha-Blend Input Image 1 Start Address Register 1
	#define REGA4_ALP_IN_IMG1_SA_2 0xA4     // Alpha-Blend Input Image 1 Start Address Register 2
	#define REGA6_ALP_IN_IMG2_SA_0 0xA6     // Alpha-Blend Input Image 2 Start Address Register 0
	#define REGA8_ALP_IN_IMG2_SA_1 0xA8     // Alpha-Blend Input Image 2 Start Address Register 1
	#define REGAA_ALP_IN_IMG2_SA_2 0xAA     // Alpha-Blend Input Image 2 Start Address Register 2
	#define REGAC_ALP_OUT_IMG_SA_0 0xAC     // Alpha-Blend Output Image Start Address Register 0
	#define REGAE_ALP_OUT_IMG_SA_1 0xAE     // Alpha-Blend Output Image Start Address Register 1
	#define REGB0_ALP_OUT_IMG_SA_2 0xB0     // Alpha-Blend Output Image Start Address Register 2
	#define REGB2_INTERRUPT_CTRL   0xB2     // Interrupt Control Register
	#define REGB4_INTERRUPT_STAT   0xB4     // Interrupt Status Register [READONLY]
	#define REGB6_INTERRUPT_CLEAR  0xB6     // Interrupt Clear Register [WRITEONLY]
	#define REGFLAG_BASE           0xF0     // Special reserved flags beyond this point
	#define REGFLAG_DELAY          0xFC     // PLL Register Programming Delay (in us)
	#define REGFLAG_OFF_DELAY      0xFD     // LCD Panel Power Off Delay (in ms)
	#define REGFLAG_ON_DELAY       0xFE     // LCD Panel Power On Delay (in ms)
	#define REGFLAG_END_OF_TABLE   0xFF     // End of Registers Marker
//DOM-IGNORE-END
/*********************************************************************
* Overview: This structure is used to describe layer registers.
*
*********************************************************************/
typedef struct
{
	uint8_t XStart;
    uint8_t XEnd;
	uint8_t YStart0;  
	uint8_t YStart1;
    uint8_t YEnd0;
	uint8_t YEnd1;
    uint8_t StartAddress0; 
	uint8_t StartAddress1;
	uint8_t StartAddress2;
} LAYER_REGISTERS;
      
#endif // _S1D13517_H
#endif