/*******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    S1D13517.c
    
  Summary:
    Interface for the graphics library where the primitives are renderred and sent to the graphics controller
    either external or internal

  Description:
    None
*******************************************************************************/
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

#include "driver/gfx/drv_gfx_display.h"

#if defined(GFX_USE_DISPLAY_CONTROLLER_S1D13517)

#include "driver/gfx/gfx_s1d13517/drv_gfx_s1d13517.h"

DRV_HANDLE       pmphandle;
DRV_PMP_MODE_CONFIG config;

GFX_COLOR _color;             //global color for the driver
uint8_t   _instance = 0;          //global instance for the driver
uint8_t   s1d13517TaskActive = 0; //task machine busy flag

GFX_DRV_S1D13517_COMMAND S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE];  //This contains the commands to send to the graphics driver
GFX_DRV_S1D13517_COMMAND *S1D13517queueIndex = &S1D13517commandBuffer[0];                             //pointer to where the command Buffer is currently

uint16_t* BarAlpha(GFX_ALPHA_PARAMS* alphaParams, uint16_t width, uint16_t height, uint8_t alpha);
 
uint16_t S1D13517queueCount = 0;
volatile uint16_t S1D13517driverBusy = 0;                              //Flag to state driver is busy
uint8_t S1D13517TaskReady = 0;
uint8_t instances[GFX_CONFIG_DRIVER_COUNT] = {0};

uint8_t   _dataWidth = 1; //PMP Data Width
uint8_t    displayReg = 0x01;

#define TRANSPARENTCOLOR()                GFX_RGBConvert(0xFF, 0x00, 0xCC)          //Transparent Color chosen for the application
#define RED8(color16)   (uint8_t) ((color16 & 0xF800) >> 8)
#define GREEN8(color16) (uint8_t) ((color16 & 0x07E0) >> 3)
#define BLUE8(color16)  (uint8_t) ((color16 & 0x001F) << 3)

volatile GFX_DRV_DATA GFX_DRV_instance[1] =
    {
        DISP_ORIENTATION, 
        DISP_HOR_RESOLUTION,
        DISP_VER_RESOLUTION,
        DISP_DATA_WIDTH,
        DISP_HOR_PULSE_WIDTH,
        DISP_HOR_BACK_PORCH,
        DISP_HOR_FRONT_PORCH,
        DISP_VER_PULSE_WIDTH,
        DISP_VER_BACK_PORCH,
        DISP_VER_FRONT_PORCH,
    	DISP_INV_LSHIFT,
        LCD_TFT,
        0,
        TCON_MODULE,
        {GFX_DRV_S1D13517_PixelsPut, NULL, GFX_DRV_S1D13517_PixelArrayPut, NULL, GFX_DRV_S1D13517_PixelPut,
         GFX_DRV_S1D13517_SetColor, GFX_DRV_S1D13517_SetInstance, GFX_DRV_S1D13517_SetPage, GFX_DRV_S1D13517_Layer,
         NULL,GFX_DRV_S1D13517_AlphaBlendWindow},
        1
    };

    const LAYER_REGISTERS PIPRegister[2] = 
    {
	REG32_PIP1_WIN_X_SP,REG38_PIP1_WIN_X_EP,REG34_PIP1_WIN_Y_SP_0,REG36_PIP1_WIN_Y_SP_1,
        REG3A_PIP1_WIN_Y_EP_0,REG3C_PIP1_WIN_Y_EP_1,REG2C_PIP1_DSP_SA_0,REG2E_PIP1_DSP_SA_1,
        REG30_PIP1_DSP_SA_2,
	REG44_PIP2_WIN_X_SP,REG4A_PIP2_WIN_X_EP,REG46_PIP2_WIN_Y_SP_0,REG48_PIP2_WIN_Y_SP_1,
	REG4C_PIP2_WIN_Y_EP_0,REG4E_PIP2_WIN_Y_EP_1,REG3E_PIP2_DSP_SA_0,REG40_PIP2_DSP_SA_1,
	REG42_PIP2_DSP_SA_2
    };

// *****************************************************************************
/*
  Macro:
	WritePixel(color)

  Summary:
	Writes a pixel to the LCD controller taking into account the color and COLOR_DEPTH macro
*/
//

// *****************************************************************************
/*
  Function: GFX_DRV_S1D13517_Open(uint8_t instance)

  Summary:
    opens an instance of the graphics controller

  Description:
    none

  Input:
    instance of the driver

  Output:
    1 - driver not initialied
    2 - instance doesn't exist
    3 - instance already open
    instance to driver when successful
*/
uint16_t GFX_DRV_S1D13517_Open(uint8_t instance)
{

   if(GFX_DRV_instance[instance].ready == 0)
      return(1);

   if(instance>=GFX_CONFIG_DRIVER_COUNT)
      return(2); //instance doesn't exist

   if(instances[instance] == 0)
   {   instances[instance] = 1; //Flag to let driver know instance is open 
       return(instance);
   }
   else
   {
     return(3); //Instance already open
   }
}

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
uint16_t GFX_DRV_S1D13517_Close(uint8_t instance)
{
      
   if(instance>=GFX_CONFIG_DRIVER_COUNT)
      return(2); //instance doesn't exist

   if(instances[instance] == 1)
   {   instances[instance] = 0; //Flag to let driver know instance is closed 
       return(0);
   }
   else
   {
     return(3); //Instance already closed
   }
}

// *****************************************************************************
/*
  Function: void GFX_DRV_S1D13517_SetColor(GFX_COLOR color)

  Summary: Sets the color for the driver instance

  Description:
  
  Output: none

*/

void GFX_DRV_S1D13517_SetColor(GFX_COLOR color)
{
     GFX_DRV_instance[_instance].color = color;
}

// *****************************************************************************
/*
  Function: void GFX_DRV_S1D13517_SetInstance(uint8_t instance)

  Summary: Sets the instance for the driver

  Description:
  
  Output: none

*/

void GFX_DRV_S1D13517_SetInstance(uint8_t instance)
{
  _instance = instance;
}

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
uint16_t GFX_DRV_S1D13517_SetReg(uint8_t index, uint8_t value)
{
    static uint32_t myWriteBuffer;
    static uint8_t state = 0;

    switch(state)
    {
        case 0:
        myWriteBuffer = index;
        if(DRV_PMP_Write ( &pmphandle, true, &myWriteBuffer, (1+ _dataWidth), 0) == NULL)
            return(1);
        state = 1;

        case 1:
        myWriteBuffer = value;
        if(DRV_PMP_Write (&pmphandle, false, &myWriteBuffer, (1+_dataWidth), 0) == NULL)
            return(1);
        state = 0;
     }

    return(0);

}

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
uint8_t  GFX_DRV_S1D13517_GetReg(uint8_t  index)
{
    static uint16_t myReadBuffer = 0xff;
    static uint32_t myWriteBuffer;
    static QUEUE_ELEMENT_OBJECT* getRegCommand = NULL;
    static uint8_t   state = 0;

switch(state)
{
     case 0:
     myWriteBuffer = index;
     if(DRV_PMP_Write(&pmphandle, true, &myWriteBuffer, (1 + _dataWidth), 0) == NULL)
        return(0);  
     state = 2;

     case 2:
     getRegCommand = DRV_PMP_Read ( pmphandle, false, &myReadBuffer, 1);
     if(getRegCommand == NULL)
     {   
          return(0);
     }
     state=3;
     case 3:
     if(DRV_PMP_TransferStatus(getRegCommand) != PMP_TRANSFER_FINISHED)
          return(0);
}

    state = 0;
//    myReadBuffer >>= (8*_dataWidth);
    return((uint8_t)myReadBuffer);
    
}

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
void GFX_DRV_S1D13517_BrightnessSet(uint8_t instance, uint16_t  level)
{
   if(level == 100)
   {
       while(GFX_DRV_S1D13517_SetReg(REG70_PWM_CONTROL,0x85));          //Turn on Backlight
   }else if (level == 0) 
   {    
       GFX_DRV_S1D13517_SetReg(REG70_PWM_CONTROL,0x84);       //Turn off Backlight 
   }else if (level <=50)
   {
       level >>= 1;
       level *=  5;  //Sets the value from (0-250)

       GFX_DRV_S1D13517_SetReg(REG72_PWM_HIGH_DC_0,0xff);
       GFX_DRV_S1D13517_SetReg(REG74_PWM_HIGH_DC_1,level);
       GFX_DRV_S1D13517_SetReg(REG7A_PWM_LOW_DC_0,0xff);
       GFX_DRV_S1D13517_SetReg(REG7C_PWM_LOW_DC_1,0xff);
     
       GFX_DRV_S1D13517_SetReg(REG70_PWM_CONTROL,0x86);   //Turn off Backlight PWM
       }
       else
       {
       level >>= 1;
       level *=  5;  //Sets the value from (0-250)
       GFX_DRV_S1D13517_SetReg(REG72_PWM_HIGH_DC_0,level);
       GFX_DRV_S1D13517_SetReg(REG74_PWM_HIGH_DC_1,0xff);
       GFX_DRV_S1D13517_SetReg(REG7A_PWM_LOW_DC_0,0xff);
       GFX_DRV_S1D13517_SetReg(REG7C_PWM_LOW_DC_1,0xff);
     
       GFX_DRV_S1D13517_SetReg(REG70_PWM_CONTROL,0x86);   //Turn off Backlight PWM

       }      
}    

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
    1 - call not successful (PMP driver busy)
    0 - call successful
*/
uint16_t GFX_DRV_S1D13517_Initialize(uint8_t instance)
{

   static uint8_t   state =0;
   static uint16_t  horizontalSize, verticalSize;
   static uint16_t  index;
   uint16_t horizontalTiming = GFX_DRV_instance[instance].horizontalPulseWidth+GFX_DRV_instance[instance].horizontalFrontPorch+GFX_DRV_instance[instance].horizontalBackPorch; 
   uint16_t verticalTiming = GFX_DRV_instance[instance].verticalPulseWidth+GFX_DRV_instance[instance].verticalFrontPorch+GFX_DRV_instance[instance].verticalBackPorch; 
       
   if(s1d13517TaskActive != 1)
   {
        if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-1)) 
        {
             return(1); //queue is full
        }

        S1D13517queueCount++;              //Add 1 to the queue count

        S1D13517queueIndex->task = INITIALIZE; //Start the state machine in the init function
        S1D13517queueIndex->instance = instance; //Start the state machine in the init function

        if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
        {
            S1D13517queueIndex = &S1D13517commandBuffer[0];
        }
        else
        {
            S1D13517queueIndex++;
        }
   } 

   while(state <= 40)
   {

   switch(state)
   {

    case 0:

    DriverInterfaceInit(&pmphandle, &config); //Initialize PMP

    _dataWidth = config.portSize;

    DisplayResetDisable();              // release from reset

    DisplayEnable();

   if((GFX_DRV_instance[instance].orientation == 90) || (GFX_DRV_instance[instance].orientation == 270))
   { 
        horizontalSize = GFX_DRV_instance[instance].verticalResolution; 
        verticalSize   = GFX_DRV_instance[instance].horizontalResolution;
   }
   else
   {
        horizontalSize = GFX_DRV_instance[instance].horizontalResolution; 
        verticalSize   = GFX_DRV_instance[instance].verticalResolution;
   }

   state++;
   break;

   case 11:
   SYS_TMR_DelayMS(100);
   break;
   
   }

   //S1D13517 Registers to be initialized
   uint8_t registers[40][2] = {
                                    REG2A_DSP_MODE,0x00,
                                    REG68_POWER_SAVE,0x00,
                                    REG04_PLL_DDIVIDER,0x17,
                                    REG06_PLL_0,0x29,
                                    REG08_PLL_1,0x01,
                                    REG0A_PLL_2,0x08,
                                    REG0C_PLL_NDIVIDER,0x59,
                                    REG12_CLK_SRC_SELECT,0x92,
                                    REG04_PLL_DDIVIDER,0x97,
                                    REG0E_SS_CONTROL_0,0x8F,
                                    #if (COLOR_DEPTH == 24)
		                            REG14_LCD_PANEL_TYPE,0x02,
	                                #else
		                            REG14_LCD_PANEL_TYPE,0x05,
	                                #endif
                                    REG16_HDISP_WIDTH,(GFX_DRV_instance[instance].horizontalResolution>>3)-1,
	                                REG18_HNDP_PERIOD,((horizontalTiming)>>1)-1,         
	                                REG1A_VDISP_HEIGHT_0,GFX_DRV_instance[instance].verticalResolution-1,
	                                REG1C_VDISP_HEIGHT_1,(GFX_DRV_instance[instance].verticalResolution-1)>>8,
	                                REG1E_VNDP_PERIOD,((verticalTiming)>>1)-1,          
	                                REG20_PHS_PULSE_WIDTH,GFX_DRV_instance[instance].horizontalPulseWidth -1,    
	                                REG22_PHS_PULSE_START,GFX_DRV_instance[instance].horizontalFrontPorch,     
	                                REG24_PVS_PULSE_WIDTH,GFX_DRV_instance[instance].verticalPulseWidth -1,     
	                                REG26_PVS_PULSE_START,GFX_DRV_instance[instance].verticalFrontPorch,    
                                    REG28_PCLK_POLARITY,(GFX_DRV_instance[instance].logicShift << 7),       	
	                                REG82_SDRAM_CONTROL_0,0x03,	
	                                REG8C_SDRAM_RFS_CNT_0,0xFF,		
	                                REG8E_SDRAM_RFS_CNT_1,0x03,
	                                REG90_SDRAM_BUF_SIZE,0x50,		
	                                REG68_POWER_SAVE,0xE8,			
	                                REG68_POWER_SAVE,0x00,
	                                REG68_POWER_SAVE,0x01,			
	                                REG84_SDRAM_STATUS_0,0x86,		
	                                REG52_INPUT_MODE,0x08,        	
                                    REG54_TRANSP_KEY_RED, RED8(TRANSPARENTCOLOR()),   	
                                    REG56_TRANSP_KEY_GREEN, GREEN8(TRANSPARENTCOLOR()), 
                                    REG58_TRANSP_KEY_BLUE, BLUE8(TRANSPARENTCOLOR()), 
	                            REG6E_GPO_1,0x07,   		
                                    REG2A_DSP_MODE, displayReg,
                                    REG50_DISPLAY_CONTROL,0x80,   
	                            REGB2_INTERRUPT_CTRL,0x01,
                                    REG9E_ALP_VALUE,0x80,
                                    REG94_ALP_CONTROL,0x01, 				      
                                    REG94_ALP_CONTROL,0x00                    				
                                    };

  if(GFX_DRV_S1D13517_SetReg(*registers[state-1], registers[state-1][1]))
  {
      return(1);
  }

  state++;

        }

     if(GFX_DRV_instance[instance].TCON_Init != NULL)
     {
          GFX_DRV_instance[instance].TCON_Init();
      }

      SYS_TMR_DelayMS(500);

      DisplayBacklightOn();

      GFX_DRV_S1D13517_BrightnessSet(instance,100);      //Sets Backlight Brightness Level - PWM

      GFX_DRV_instance[instance].horizontalResolution = horizontalSize; 
      GFX_DRV_instance[instance].verticalResolution = verticalSize;
      GFX_DRV_instance[instance].ready = 1;
      GFX_DRV_instance[instance].driverBusy =0;
      return (0); //Driver initialized successfully
}

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_S1D13517_PixelPut(short x, short y)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates
  Output:
    1 - call not successful (S1D13517 driver busy)
    0 - call successful
*/
uint16_t GFX_DRV_S1D13517_PixelPut(short x, short y)
{

    uint8_t commandCount = 2;

    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-commandCount)) 
    {
     return (1); //queue is full
    }

    S1D13517driverBusy = 1;

     while(commandCount--)
     {
          S1D13517queueIndex->instance = _instance;
          S1D13517queueIndex->count = 1;
          S1D13517queueIndex->lineCount = 1;

     if(commandCount == 1)
     {
          S1D13517queueIndex->task = WINDOW_SETUP_8BIT + _dataWidth;
          S1D13517queueIndex->y = y;
          S1D13517queueIndex->x = x;
     }
     else
     {
            S1D13517queueIndex->task = PUT_PIXELS;
            S1D13517queueIndex->data = GFX_DRV_instance[_instance].color;
     }

      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      } 
     }
     S1D13517queueCount += 2;
     S1D13517driverBusy = 0;

     return(0);

}  

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
          1 - call not successful (S1D13517 driver busy)
          0 - call successful
*/
uint16_t  GFX_DRV_S1D13517_PixelsPut(short x, short y, uint16_t count, uint16_t lineCount)
{

    uint8_t commandCount = 2;

    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-commandCount)) 
    {
     return (1); //queue is full
    }

    S1D13517driverBusy = 1;

     while(commandCount--)
     {

          S1D13517queueIndex->instance = _instance;
          S1D13517queueIndex->count = count;
          S1D13517queueIndex->lineCount = lineCount;

     if(commandCount == 1)
     {
            if(((count-(8-(x&7)))>7)&&(lineCount>1))
            {
                 S1D13517queueIndex->task = COPY_PIXELS;
                 S1D13517queueIndex->data = GFX_DRV_instance[_instance].color;
                 commandCount--;
            }
            else
            {
                 S1D13517queueIndex->task = WINDOW_SETUP_8BIT + _dataWidth;
            }
          S1D13517queueIndex->y = y;
          S1D13517queueIndex->x = x;
     }
     else
     {
          S1D13517queueIndex->task = PUT_PIXELS;
          S1D13517queueIndex->data = GFX_DRV_instance[_instance].color;
     }

      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      } 
       S1D13517queueCount++;
     }
     S1D13517driverBusy = 0;
     return(0);

}  

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_S1D13517_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count)

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
         handle to the number of pixels remaining
*/
uint16_t*  GFX_DRV_S1D13517_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count, uint16_t lineCount)
{
    static GFX_DRV_S1D13517_COMMAND  *index;
    uint8_t commandCount = 2;

    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-commandCount)) 
    {
     return (NULL); //queue is full
    }

    S1D13517driverBusy = 1;

     while(commandCount--)
     {
          S1D13517queueIndex->instance = _instance;
          S1D13517queueIndex->count = count;
          S1D13517queueIndex->lineCount = lineCount;

     if(commandCount == 1)
     {
          S1D13517queueIndex->x = x;
          S1D13517queueIndex->task = WINDOW_SETUP_8BIT + _dataWidth;
          S1D13517queueIndex->y = y;
     }
     else
     {
            S1D13517queueIndex->task = PUT_ARRAY;
            S1D13517queueIndex->array = color;
            index = S1D13517queueIndex;
     }

      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      } 
     }
     S1D13517queueCount += 2;
     S1D13517driverBusy = 0;
     return(&index->count);

} 

// *****************************************************************************
/*
  Function:
	void GFX_DRV_S1D13517_SetPage(uint8_t pageType, uint8_t page)

  Summary:
	Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer
*/
//
uint16_t GFX_DRV_S1D13517_SetPage(uint8_t pageType, uint8_t page)
{

    static uint8_t state = 0;

   if(s1d13517TaskActive != 1)
   {
       
    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-1)) 
    {
        return (1); //queue is full
    }

    S1D13517driverBusy = 1;
    
     S1D13517queueIndex->instance = _instance;
     S1D13517queueIndex->task = PAGE;     
     S1D13517queueIndex->x = pageType;
     S1D13517queueIndex->y = page;

      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      } 

     S1D13517queueCount++;
     S1D13517driverBusy = 0;
     return(0);
   }

 switch(pageType)
 {
   case ACTIVE_PAGE:
    if(GFX_DRV_S1D13517_SetReg(REG52_INPUT_MODE, 0x08 | (page<<4)))
        return(1);
    GFX_DRV_instance[_instance].activePage = page;
    break;
   case VISUAL_PAGE:
       if(state == 0)
       {
            displayReg &= 0x0f;

            if(GFX_DRV_S1D13517_SetReg(REG2A_DSP_MODE, ((displayReg) | (page << 4))))
                return(1);

            state++;
       }
       if(state == 1)
       {
            if(GFX_DRV_S1D13517_SetReg(REG50_DISPLAY_CONTROL,0x80))
                return(1);
            state = 0;
            GFX_DRV_instance[_instance].visualPage = page;
       }
   default: break;
 }  

return(0);
}

// *****************************************************************************
/*
  Function:
	void GFX_DRV_S1D13517_Tasks(void)

  Summary:
	Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer
*/
//
void GFX_DRV_S1D13517_Tasks(void)
{
   static GFX_DRV_S1D13517_COMMAND  *index = &S1D13517commandBuffer[0];
   static GFX_ALPHA_PARAMS alphaParams;
   static uint16_t beforeCount,afterCount;
   static uint16_t lineCount;
   static uint16_t width,start,count = 4;
   static uint16_t finalWidth;
   static uint32_t color1,color2;
   static uint32_t transparentColor = TRANSPARENTCOLOR();
   static uint8_t myWriteBuffer[4]; //Write buffer for the PMP 
   static uint8_t state = 0;


if(S1D13517driverBusy == 1)
     return;

while(S1D13517queueCount)
{

  switch(index->task)  //State Machine for Putpixel ONLY
  {

    case INITIALIZE: 
    s1d13517TaskActive = 1;
    if(GFX_DRV_S1D13517_Initialize(index->instance))  //Call until the driver is initialized
    {
         s1d13517TaskActive = 0;
         return;
    }
    else
    {
      s1d13517TaskActive = 0;
      GFX_DRV_instance[0].driverBusy = 0;
      GFX_DRV_instance[0].ready = 1;
    }
    break;

    case WINDOW_SETUP_8BIT:
           switch(state)
           {
             case 0:
                if(GFX_DRV_S1D13517_SetReg(REG5A_WRITE_WIN_X_SP,(index->x >> 2)))
                return;

                 state = 1;
                 myWriteBuffer[3]  = index->y >> 2;
                 myWriteBuffer[2]  = index->y;
                 myWriteBuffer[1]  = (index->x + (index->count-1))>>2;
                 myWriteBuffer[0]  = (index->y + index->lineCount)>>2;

              case 1:
                 if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&myWriteBuffer, 4, 0) == NULL)
                 return;

                 state = 2;
                 myWriteBuffer[3] = (index->y + index->lineCount); 
      
              case 2:         
                if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&myWriteBuffer, 1, 0) == NULL)
                 return;

                 beforeCount = ((index->x) & 7);
                 afterCount = (beforeCount + index->count); //Get Pixel Count
                 afterCount &= 7;
                 afterCount = (8-afterCount) & 7;
           }
          break;


    case WINDOW_SETUP_16BIT:
           switch(state)
           {
             case 0:
                if(GFX_DRV_S1D13517_SetReg(REG5A_WRITE_WIN_X_SP,(index->x >> 2)))
                return;

                 state = 1;
                 myWriteBuffer[3] = 0;
                 myWriteBuffer[2]  = index->y >> 2;
                 myWriteBuffer[1] = 0;
                 myWriteBuffer[0]  = index->y;

              case 1:
                 if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&myWriteBuffer, 4, 0) == NULL)
                 return;

                 state = 2;
                 myWriteBuffer[2]  = (index->x + (index->count-1))>>2;
                 myWriteBuffer[0]  = (index->y + index->lineCount)>>2;

              case 2:
                 if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&myWriteBuffer, 4, 0) == NULL)
                 return;

                 state = 3;
                 myWriteBuffer[2] = (index->y + index->lineCount); 
      
              case 3:         
                if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&myWriteBuffer, 2, 0) == NULL)
                 return;
                 state = 2;

                 beforeCount = ((index->x) & 7);
                 afterCount = (beforeCount + index->count); //Get Pixel Count
                 afterCount &= 7;
                 afterCount = (8-afterCount) & 7;

           }
          break;
  
    case PUT_PIXELS:   //This task is 1 PutPixel      

        switch(state)
        {
        case 2:   
                  while(index->lineCount)
                  {

                    if(beforeCount)
                    {
                        state = 3;
              case 3:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&transparentColor, 2, beforeCount-1) == NULL)
                        return;
                    }

                        state = 4;
              case 4:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&index->data, 2, (index->count-1)) == NULL)
                        return;

                    if(afterCount)
                    {
                        state = 5;
              case 5:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&transparentColor, 2, afterCount-1) == NULL)
                            return;          
                    }

                      index->lineCount--;
                 }

                state = 0;
                break;
         }     
    break;

    case COPY_PIXELS:   //This task is 1 PutPixel      

           switch(state)
           {
             case 11:
                  while((lineCount) < (index->lineCount-1))
                  {
                       if(BarAlpha(&alphaParams, finalWidth, 2, 100) == NULL)
                       {
                            return;
                       }

                       alphaParams.destinationTop = (index->y+lineCount);
                       lineCount+=2;
                  }

                       alphaParams.destinationTop = (index->y+index->lineCount-2);
                       state = 12;
              case 12:                      
                       if(BarAlpha(&alphaParams, finalWidth, 1, 100) == NULL)
                       {
                            return;
                       }
                break;   
             break;  //End of task

          case 0:
	            if(GFX_DRV_S1D13517_SetReg(REG62_WRITE_WIN_Y_EP_0,(index->y + index->lineCount)>>2))
                    return;
                state = 1;

          case 1:
	            if(GFX_DRV_S1D13517_SetReg(REG5C_WRITE_WIN_Y_SP_0,index->y >> 2))
                    return;
               state = 2;
          case 2:
	            if(GFX_DRV_S1D13517_SetReg(REG5E_WRITE_WIN_Y_SP_1,index->y))
                    return;
  
        while(count)
        {

             lineCount = index->lineCount;

                 if(count == 4)
                 {
                      width = 8;
                      start = index->x;
                      color1 = transparentColor;
                      color2 = index->data;
                 }
                 else if(count == 3)
                 {
                      width = index->count;

                      if(beforeCount) 
                      {
                            start += (8- beforeCount);
                            width -= (8 - beforeCount);
                      }

                      width &= 0xFFFFFFF8;
                      finalWidth = width;
                      lineCount = 1;

                      //Setup the Alpha Window Parameters for later
                      alphaParams.foregroundPage = GFX_DRV_instance[index->instance].activePage;
                      alphaParams.foregroundLeft = start;
                      alphaParams.foregroundTop = (index->y);
                      alphaParams.destinationPage = GFX_DRV_instance[index->instance].activePage;
                      alphaParams.destinationLeft = start;
                      alphaParams.destinationTop = (index->y+1);
                 }
                 else if(count == 2)
                 {
                      start = (index->x + index ->count);
                      width = 8;
                      color2 = transparentColor;
                      color1 = index->data;
                 }
                 else if(count == 1)
                 {
                      state = 10;
                      
        case 10:      s1d13517TaskActive = 1;
                      if(GFX_DRV_S1D13517_AlphaBlendWindow(&alphaParams, finalWidth, 1, 100) == NULL)
                      {
                         s1d13517TaskActive = 0;
                         return;
                      }
                      s1d13517TaskActive = 0;
                      state = 11;
                      lineCount = 2;
                      return;
                  }
                  beforeCount = (start & 7);
                  state = 3;

          case 3:                
                if(GFX_DRV_S1D13517_SetReg(REG5A_WRITE_WIN_X_SP,(start >> 2)))
                    return;
                state = 4;

                 if(!beforeCount)
                 myWriteBuffer[2]  = (start+width-1)>>2;
                 else
                 myWriteBuffer[2]  = (start)>>2;

          case 4:
	            if(GFX_DRV_S1D13517_SetReg(REG60_WRITE_WIN_X_EP, myWriteBuffer[2]))
                    return; 
               state = 5;

          case 5:
	            if(GFX_DRV_S1D13517_SetReg(REG64_WRITE_WIN_Y_EP_1,index->y + index->lineCount))
                    return;

                  while(lineCount)
                  {

                    if(beforeCount)
                    {
                        state = 7;
              case 7:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&color1, 2, beforeCount-1) == NULL)
                        return;
                    }

                        state = 8;
              case 8:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&color2, 2, (width-beforeCount-1)) == NULL)
                        return;
                
                     lineCount--;
                  }
                  count--;
         }   
         } 
    count = 4;
    state = 0;
    break;

    case PUT_ARRAY:

        switch(state)
        {
         case 2:
                while(index->lineCount)
                {

                    if(beforeCount)
                    {
                        state = 3;
         case 3:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&transparentColor, 2, beforeCount-1) == NULL)
                        return;
                    }

                        state = 4;
         case 4:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)index->array, (index->count)<<1, 0) == NULL)
                        return;

                    if(afterCount)
                    {
                        state = 5;
         case 5:
                        if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&transparentColor, 2, afterCount-1) == NULL)
                            return;   
                    }
                      index->array += index->count;
                      index->lineCount--;
                 }

                index->count = 0;
                state = 0;
                break;
         }     
    break;

    case PAGE:  //SetPage
        if(state == 0)
        {
            if(GFX_DRV_S1D13517_GetReg((REGB4_INTERRUPT_STAT)) == 0)
                return;

            state = 1;
        }

        s1d13517TaskActive = 1;
        if(GFX_DRV_S1D13517_SetPage(index->x, index->y))
        {
            s1d13517TaskActive = 0;
            return;
        }
        s1d13517TaskActive = 0;
        state = 0;
        break;

    case ALPHA_BLEND: //AlphaBlend

     if(index->count == 3)
     {
          alphaParams.foregroundPage = index->data;
          alphaParams.foregroundLeft = index->x;
          alphaParams.foregroundTop = index->y;
     }
     else if(index->count == 2)
     {
          alphaParams.backgroundPage = index->data;
          alphaParams.backgroundLeft = index->x;
          alphaParams.backgroundTop = index->y;
     }
     else if(index->count == 1)
     {
          alphaParams.destinationPage = index->data;
          alphaParams.destinationLeft = index->x;
          alphaParams.destinationTop = index->y;
     }
     else
     {
        _instance = index->instance;

        s1d13517TaskActive = 1;
        if(GFX_DRV_S1D13517_AlphaBlendWindow(&alphaParams, index->x, index->y, index->data) == NULL)
        {
            s1d13517TaskActive = 0;
            return;
        }
        s1d13517TaskActive = 0;
     }
    break;

    case LAYERS:     
    s1d13517TaskActive = 1;
    if(GFX_DRV_S1D13517_Layer(index->data, (GFX_LAYER_PARAMS*)index->array) == NULL)
    {
         s1d13517TaskActive = 0;
         return;
    }
    s1d13517TaskActive = 0;
    index->count = 0;
    break;

    default: //Do nothing
    break;
   }

    S1D13517queueCount--;      //Subtract 1 from the queue count

   if(index++ == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
   {
     index = &S1D13517commandBuffer[0];     
   }
 
}
  
}

#define BUFFER_SIZE 0x140000l  //WVGA

/*********************************************************************
* Function: DWORD GFXGetPageOriginAddress(SHORT pageNumber)
********************************************************************/
uint32_t GFXGetPageOriginAddress(short pageNumber)
{
	return(BUFFER_SIZE * (uint32_t)pageNumber);
}

/*********************************************************************
* Function: DWORD GFXGetPageXYAddress(SHORT pageNumber, WORD x, WORD y)
********************************************************************/
uint32_t GFXGetPageXYAddress(uint8_t pageNumber, uint16_t x, uint16_t y)
{
    uint32_t address;

    #if (DISP_ORIENTATION == 90)       //Added for rotation capabilities
    uint32_t tempx;
    tempx = x;

    x=y;
    y = (uint32_t)(DISP_VER_RESOLUTION-1) - tempx;
    if(tempx ==0) y=0;
    #endif

    address = (uint32_t)y * (uint32_t)DISP_HOR_RESOLUTION;
    address += (uint32_t)x;
    address *= 3;
    address += GFXGetPageOriginAddress(pageNumber);

    return address;
}

uint16_t* BarAlpha(GFX_ALPHA_PARAMS* alphaParams, uint16_t width, uint16_t height, uint8_t alpha) //Internal Function for Hardware Bar Renderring
{
    static uint8_t state = 0;
    static uint32_t destinationWindowAddr;

    switch(state)
    {

    case 0:
        if(GFX_DRV_S1D13517_GetReg((REGB4_INTERRUPT_STAT)) == 0)
            return(NULL);
        state = 16;
	case 16:    
        if(GFX_DRV_S1D13517_SetReg(REGB6_INTERRUPT_CLEAR,0x01))
            return(NULL);
        state = 17;
    case 17:                
	    if(GFX_DRV_S1D13517_SetReg(REGB6_INTERRUPT_CLEAR,0x00))
            return(NULL);				
    
    destinationWindowAddr = GFXGetPageXYAddress(alphaParams->destinationPage, alphaParams->destinationLeft, alphaParams->destinationTop);
    state = 1;
    case 1: 
    if(GFX_DRV_S1D13517_SetReg(REG9A_ALP_VR_SIZE_0,height))
        return(NULL); 
	state = 2;
    case 2:
    if(GFX_DRV_S1D13517_SetReg(REGAC_ALP_OUT_IMG_SA_0,destinationWindowAddr))
        return(NULL);
	state = 3;
    case 3:  
    if(GFX_DRV_S1D13517_SetReg(REGAE_ALP_OUT_IMG_SA_1,destinationWindowAddr>>8))
        return(NULL);
	state = 4;
    case 4: 
    if(GFX_DRV_S1D13517_SetReg(REGB0_ALP_OUT_IMG_SA_2,destinationWindowAddr>>16))
	    return(NULL); 
    state = 5;
    case 5:
    if(GFX_DRV_S1D13517_SetReg(REG94_ALP_CONTROL,0x01)) 				    //Enable Alpha Blend  
         return(NULL);
    state = 6;
    case 6:
	if(GFX_DRV_S1D13517_SetReg(REG94_ALP_CONTROL,0x00))                    // Added From DataSheet
         return(NULL);
   }
    state = 0;
    return((uint16_t*)&state);
}

uint16_t*      GFX_DRV_S1D13517_AlphaBlendWindow(GFX_ALPHA_PARAMS* alphaParams, uint16_t width, uint16_t height, uint8_t alpha)
{

    if(s1d13517TaskActive == 1)
    {
        static uint8_t state = 0;
        static uint32_t foregroundWindowAddr, backgroundWindowAddr, destinationWindowAddr;
        static uint8_t alphaReg;

    switch(state)
    {

    case 0:
        if(GFX_DRV_S1D13517_GetReg((REGB4_INTERRUPT_STAT)) == 0)
            return(NULL);
        state = 16;
    case 16:
        if(GFX_DRV_S1D13517_SetReg(REGB6_INTERRUPT_CLEAR,0x01))
            return(NULL);
        state = 17;
    case 17:                
	    if(GFX_DRV_S1D13517_SetReg(REGB6_INTERRUPT_CLEAR,0x00))
            return(NULL);				
    
    foregroundWindowAddr = GFXGetPageXYAddress(alphaParams->foregroundPage, alphaParams->foregroundLeft, alphaParams->foregroundTop);
    destinationWindowAddr = GFXGetPageXYAddress(alphaParams->destinationPage, alphaParams->destinationLeft, alphaParams->destinationTop);
    state = 1;
    case 1:
    if(GFX_DRV_S1D13517_SetReg(REG98_ALP_HR_SIZE,((width-1)>> 3)))
        return(NULL);
    state = 2;
    case 2: 
    if(GFX_DRV_S1D13517_SetReg(REG9A_ALP_VR_SIZE_0,height))
        return(NULL);
    state = 3;
    case 3: 
    if(GFX_DRV_S1D13517_SetReg(REG9C_ALP_VR_SIZE_1,(height >> 8)))
        return(NULL); 

    foregroundWindowAddr  += (foregroundWindowAddr & 7);
    destinationWindowAddr += (destinationWindowAddr & 7);
	state = 4;
    case 4:
    if(GFX_DRV_S1D13517_SetReg(REGA0_ALP_IN_IMG1_SA_0,foregroundWindowAddr))
        return(NULL);
	state = 5;
    case 5:    
    if(GFX_DRV_S1D13517_SetReg(REGA2_ALP_IN_IMG1_SA_1,foregroundWindowAddr>>8))
        return(NULL); 
	state = 6;
    case 6:
    if(GFX_DRV_S1D13517_SetReg(REGA4_ALP_IN_IMG1_SA_2,foregroundWindowAddr>>16))
        return(NULL);
	state = 10;
    case 10:
    if(GFX_DRV_S1D13517_SetReg(REGAC_ALP_OUT_IMG_SA_0,destinationWindowAddr))
        return(NULL);
	state = 11;
    case 11:  
    if(GFX_DRV_S1D13517_SetReg(REGAE_ALP_OUT_IMG_SA_1,destinationWindowAddr>>8))
        return(NULL);
	state = 12;
    case 12: 
    if(GFX_DRV_S1D13517_SetReg(REGB0_ALP_OUT_IMG_SA_2,destinationWindowAddr>>16))
	    return(NULL);

    if(alpha == 100)
    {
         alphaReg = (0xC0 | 0x20);
    }
    else
    {
        backgroundWindowAddr = GFXGetPageXYAddress(alphaParams->backgroundPage, alphaParams->backgroundLeft, alphaParams->backgroundTop);
        backgroundWindowAddr  += (backgroundWindowAddr & 7);
        alphaReg = (0x80 | Percentage2Alpha(alpha));
        state = 7;

    case 7: 
        if(GFX_DRV_S1D13517_SetReg(REGA6_ALP_IN_IMG2_SA_0,backgroundWindowAddr))
        return(NULL);
	    state = 8;
    case 8:    
        if(GFX_DRV_S1D13517_SetReg(REGA8_ALP_IN_IMG2_SA_1,backgroundWindowAddr>>8))
        return(NULL);
	    state = 9;
    case 9: 
        if(GFX_DRV_S1D13517_SetReg(REGAA_ALP_IN_IMG2_SA_2,backgroundWindowAddr>>16))
        return(NULL); 
    }
    state = 13;

    case 13:
	if(GFX_DRV_S1D13517_SetReg(REG9E_ALP_VALUE, alphaReg))  
        return(NULL);  
    state = 14;
    case 14:
    if(GFX_DRV_S1D13517_SetReg(REG94_ALP_CONTROL, 0x01)) 				    //Enable Alpha Blend  
         return(NULL);
    state = 15;
    case 15:
	if(GFX_DRV_S1D13517_SetReg(REG94_ALP_CONTROL, 0x00))                    // Added From DataSheet
         return(NULL);
    }
    state = 0;
    return((uint16_t*)&state);

    }

    static uint8_t commandCount = 4;

    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-commandCount)) 
    {
        return (NULL); //queue is full
    }

    S1D13517driverBusy = 1;

     while(commandCount--)
     {

         S1D13517queueIndex->count = commandCount;
         S1D13517queueIndex->task = ALPHA_BLEND; //AlphaBlend

     if(commandCount == 3)
     {
          S1D13517queueIndex->data = alphaParams->foregroundPage;
          S1D13517queueIndex->x = alphaParams->foregroundLeft;
          S1D13517queueIndex->y = alphaParams->foregroundTop;
     }
     else if(commandCount == 2)
     {
          S1D13517queueIndex->data = alphaParams->backgroundPage;
          S1D13517queueIndex->x = alphaParams->backgroundLeft;
          S1D13517queueIndex->y = alphaParams->backgroundTop;
     }
     else if(commandCount == 1)
     {
          S1D13517queueIndex->data = alphaParams->destinationPage;
          S1D13517queueIndex->x = alphaParams->destinationLeft;
          S1D13517queueIndex->y = alphaParams->destinationTop;
     }
     else
     {
        S1D13517queueIndex->instance = _instance;
        S1D13517queueIndex->x = width;
        S1D13517queueIndex->y = height;
        S1D13517queueIndex->data = alpha;
     }
 
      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      }

     S1D13517queueCount++;
     }
     S1D13517driverBusy = 0;
     commandCount = 4;
     return((uint16_t*)S1D13517queueIndex);
}

uint16_t* GFX_DRV_S1D13517_Layer(uint8_t type, GFX_LAYER_PARAMS* layer)
{

   static GFX_DRV_S1D13517_COMMAND* LayerIndex = NULL;
   static uint8_t state = 0;
   static uint32_t PIPStartAddress;

    if(s1d13517TaskActive)
    {

        switch(state)
        {
            case 0:

                if((displayReg = GFX_DRV_S1D13517_GetReg(REG2A_DSP_MODE))==0)
                    return(NULL);

                layer->left &= 0xf8; //X must be a multiple of 8
                PIPStartAddress = GFXGetPageXYAddress(layer->page,layer->left,layer->top);

                if(layer->on == 0)
                {
                 displayReg &= 0xf1;
                 state = 10;
                 return(NULL);
                }

                displayReg |= 0x04;
                state++;
            case 1:
                //PIP screen
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].XStart, (layer->layerLeft)>>2))
                    return(NULL);
                    state++;
            case 2:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].XEnd, (layer->layerLeft +(layer->width)) >> 2   ))
                    return(NULL);
                    state++;
            case 3:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].YStart0, (layer->layerTop) >> 2))
                    return(NULL);
                    state++;
            case 4:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].YStart1, layer->layerTop))
                    return(NULL);
                    state++;
            case 5:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].YEnd0, (layer->layerTop+layer->height) >> 2  ))
                    return(NULL);
                    state++;
            case 6:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].YEnd1, layer->layerTop + layer->height ))
                    return(NULL);
                    state++;
            case 7:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].StartAddress0,PIPStartAddress))
                    return(NULL);
                    state++;
            case 8:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].StartAddress1,PIPStartAddress >> 8))
                    return(NULL);
                    state++;
            case 9:
                if(GFX_DRV_S1D13517_SetReg(PIPRegister[type].StartAddress2,PIPStartAddress >> 16))
                    return(NULL);
                    state++;
            case 10:
                if(GFX_DRV_S1D13517_SetReg(REG2A_DSP_MODE, displayReg))                      //Turn on PIP 1
                    return(NULL);
                    state++;
            case 11:
                if(GFX_DRV_S1D13517_SetReg(REG50_DISPLAY_CONTROL,0x80))                    //Refresh must be callsed after swapping screens
                    return(NULL);
        }
        state = 0;
        return(&LayerIndex->count);
    }

    if(S1D13517queueCount >= (GFX_DRV_S1D13517_COMMANDQUEUESIZE-1)) 
    {
        return (NULL); //queue is full
    }

    S1D13517queueCount++;
     
     S1D13517queueIndex->task = LAYERS; //Set Page
     S1D13517queueIndex->instance = _instance;
     S1D13517queueIndex->array = (uint16_t*)layer; 
     S1D13517queueIndex->data = type; 
     S1D13517queueIndex->count = 1;
     LayerIndex = S1D13517queueIndex;
 
      if(S1D13517queueIndex == &S1D13517commandBuffer[GFX_DRV_S1D13517_COMMANDQUEUESIZE-1])
      {
          S1D13517queueIndex = &S1D13517commandBuffer[0];
      }
      else
      {
          S1D13517queueIndex++;
      } 

     return(&LayerIndex->count);
}

#endif // #if (GFX_USE_DISPLAY_CONTROLLER_S1D13517)    
