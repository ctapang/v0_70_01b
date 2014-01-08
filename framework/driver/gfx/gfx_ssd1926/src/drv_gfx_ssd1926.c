/*******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    SSD1926.c
    
  Summary:
    Interface for the graphics library where the primitives are renderred and sent to the graphics controller
    either external or internal

  Description:
    None
*******************************************************************************/
 /* Software License Agreement
  Copyright � 2008 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
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
  OR OTHER SIMILAR COSTS. */

#include "driver/gfx/drv_gfx_display.h"

#if defined(GFX_USE_DISPLAY_CONTROLLER_SSD1926)

#include "driver/gfx/gfx_ssd1926/drv_gfx_ssd1926.h"
DRV_HANDLE       pmphandle;
DRV_PMP_MODE_CONFIG config;

GFX_DRV_SSD1926_COMMAND  SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE];  //This contains the commands to send to the graphics driver
GFX_DRV_SSD1926_COMMAND* SSD1926queueIndex = &SSD1926commandBuffer[0];                             //pointer to where the command Buffer is currently 

volatile uint16_t SSD1926queueCount = 0;
volatile uint16_t SSD1926driverBusy = 0;  
volatile uint8_t SSD1926taskBusy=0;  //Flag to state driver is busy
uint8_t SSD1926TaskReady = 0;
uint8_t instances[GFX_CONFIG_DRIVER_COUNT] = {0};

GFX_COLOR _barColor;

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
        {GFX_DRV_SSD1926_PixelsPut, GFX_DRV_SSD1926_BarFill, GFX_DRV_SSD1926_PixelArrayPut, GFX_DRV_SSD1926_PixelArrayGet,
         GFX_DRV_SSD1926_PixelPut, GFX_DRV_SSD1926_SetColor, GFX_DRV_SSD1926_SetInstance, NULL, NULL, NULL, NULL},
        1,
        0
    };

uint8_t   _instance = 0; //global instance for the driver
uint8_t   _dataWidth; //PMP Data Width

// *****************************************************************************
/*
  Function: GFX_DRV_SSD1926_Open(uint8_t instance)

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
uint16_t GFX_DRV_SSD1926_Open(uint8_t instance)
{

   if(GFX_DRV_instance[0].ready == 0)
       return(3);

   if(instance >= GFX_CONFIG_DRIVER_COUNT)
      return(2); //instance doesn't exist

   if(instances[instance] == 0)
   {
       instances[instance] = 1; //Flag to let driver know instance is open
       return(instance);
   }
   else
   {
     return(3); //Instance already open
   }
}

// *****************************************************************************
/*
  Function: GFX_DRV_SSD1926_Close(uint8_t instance)

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
uint16_t GFX_DRV_SSD1926_Close(uint8_t instance)
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
  Function: uint16_t GFX_DRV_SSD1926_SetAddress(DWORD address)

  Summary:
    sets the pmp address for read/write operations

  Description:
    none

  Input:
    address - address

  Output:
    0 - when call was passed
*/
uint16_t GFX_DRV_SSD1926_SetAddress(uint32_t address)
{
    static uint32_t temp;
    temp = (address << 8);
    temp |= (0x80000001);
    if(DRV_PMP_Write ( &pmphandle, true, &temp, 4, 0) == NULL)
         return(1);

   return(0);

}

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_SSD1926_SetReg(uint16_t index, uint8_t value)

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
uint16_t GFX_DRV_SSD1926_SetReg(uint16_t index, uint8_t value)
{
    static uint32_t myWriteBuffer;
    static uint8_t state = 0;

    switch(state)
    {
        case 0:
        myWriteBuffer = index;
        if(DRV_PMP_Write ( &pmphandle, true, &myWriteBuffer, 3, 0) == NULL)
            return(1);
        state = 1;

        case 1:
        myWriteBuffer = (value << (_dataWidth*8*(!(index & 0x0001))));
        if(DRV_PMP_Write (&pmphandle, false, &myWriteBuffer, (1 + _dataWidth), 0) == NULL)
            return(1);
        state = 0;
     }

     return(0);
}

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_SSD1926_GetReg(uint16_t index, uint8_t *data)

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
uint8_t  GFX_DRV_SSD1926_GetReg(uint16_t  index, uint8_t *data)
{  
    static uint16_t myReadBuffer = 0xff;
    static uint32_t myWriteBuffer;
    static QUEUE_ELEMENT_OBJECT* getRegCommand = NULL;
    static uint8_t   state = 0;

switch(state)
{
     case 0:
     myWriteBuffer = index;
     if(DRV_PMP_Write(&pmphandle, true, &myWriteBuffer, 3, 0) == NULL)
        return(1);  
     state = 1;
     case 1:
     if(DRV_PMP_Read ( pmphandle, false, &myReadBuffer, 1) == NULL)
         return(1);
     state = 2;
     case 2:
     getRegCommand = DRV_PMP_Read ( pmphandle, false, &myReadBuffer, 1);
     if(getRegCommand == NULL)
     {   
          return(1);
     }
     state=3;
     case 3:
     if(DRV_PMP_TransferStatus(getRegCommand) != PMP_TRANSFER_FINISHED)
          return(1);
         break;
}

    state = 0;
    myReadBuffer >>= (8*_dataWidth);
    *data = (uint8_t)myReadBuffer;
    return(0);
    
}

// *****************************************************************************
/*
  Function: uint8_t GFX_DRV_SSD1926_BrightnessSet(uint8_t instance, uint16_t level)

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
void GFX_DRV_SSD1926_BrightnessSet(uint8_t instance, uint16_t  level)
{
    // If the brightness can be controlled (for example through PWM)
    // add code that will control the PWM here.

    if (level > 0)
    {
        DisplayBacklightOn();           
    }    
    else if (level == 0)
    {
        DisplayBacklightOff();
    }    
        
}    

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_SSD1926_Initialize(uint8_t instance)

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
uint16_t GFX_DRV_SSD1926_Initialize(uint8_t instance)
{

   static uint8_t   state =0;
   static uint8_t   dummy = 1;
   static uint16_t  horizontalSize, verticalSize;
   static uint8_t panelType  = 0; 
   static uint8_t panelWidth = 0; 
   uint16_t  horizontalTotal = (GFX_DRV_instance[instance].horizontalPulseWidth + GFX_DRV_instance[instance].horizontalBackPorch + GFX_DRV_instance[instance].horizontalFrontPorch + GFX_DRV_instance[instance].horizontalResolution);
   uint16_t  verticalTotal = (GFX_DRV_instance[instance].verticalPulseWidth + GFX_DRV_instance[instance].verticalBackPorch + GFX_DRV_instance[instance].verticalFrontPorch + GFX_DRV_instance[instance].verticalResolution);
   static uint32_t  windowOffset;
   static uint32_t  windowStartAddress;    
   static uint16_t  rotation;

   if( SSD1926taskBusy == 0)
   {

        if(SSD1926queueCount >= (GFX_DRV_SSD1926_COMMANDQUEUESIZE-1)) 
        {
             return(1); //queue is full
        }

	SSD1926driverBusy = 1;

        SSD1926queueIndex->task = INITIALIZE; //Start the state machine in the init function
        SSD1926queueIndex->instance = instance; //Start the state machine in the init function

        if(SSD1926queueIndex == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
        {
             SSD1926queueIndex = &SSD1926commandBuffer[0];
        }
        else
        {
             SSD1926queueIndex++;
        } 

          SSD1926queueCount++;              //Add 1 to the queue count
          SSD1926driverBusy = 0;
          return(0); //In the queue
   }

   while(state <= 45)
   {

   switch(state)
   {

   case 0:

    DriverInterfaceInit(&pmphandle, &config);

    _dataWidth = config.portSize;

    DisplayResetDisable();              // release from reset

    DisplayEnable();

    // give time for the controller to power up
    SYS_TMR_DelayMS(500);

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

    if(GFX_DRV_instance[instance].dataWidth == 18)
        panelWidth |= 0x20;
    else if(GFX_DRV_instance[instance].dataWidth == 24)
        panelWidth |= 0x30;
    
    if (GFX_DRV_instance[instance].LCDType == LCD_TFT)
        panelType |= 0x41;
    else if (GFX_DRV_instance[instance].LCDType == LCD_CSTN)
        panelType |= 0x40;
    else if (GFX_DRV_instance[instance].LCDType == LCD_MSTN)
        panelType |= 0x00;

    switch(GFX_DRV_instance[instance].orientation)
    {

     case 90:
        windowStartAddress = ((((uint32_t) horizontalSize + 1) >> 1) - 1);
        rotation = 1;
        break;

     case 180:
        windowStartAddress = (((((uint32_t) horizontalSize + 1) * (verticalSize + 1)) >> 1) - 1);
        rotation = 2;
        break;

     case 270:
        windowStartAddress = ((((uint32_t) horizontalSize + 1) * verticalSize) >> 1);
        rotation = 3;
        break;

     case 0:
     default:
        windowStartAddress = 0ul;
        rotation = 0;
      break;

    }

    windowOffset = (horizontalSize + 1) >> 1;  
    break;

    case 33:
     if(GFX_DRV_SSD1926_GetReg(REG_POWER_SAVE_CONFIG, &dummy))
     {
          return(1);
     }
     state++;
    case 34:
     if(dummy) 
     {
          state = 33; 
          return(1);
     }
     state++;
     return(1);

    case 45:
    if(GFX_DRV_instance[instance].TCON_Init != NULL)
       GFX_DRV_instance[instance].TCON_Init();
    state++;
    return(1);
    default:
       break;
  }

   //SSD1926 Registers to be initialized
   uint16_t registers[44][2] = {    
                                    REG_PLL_CONFIG_0,0x0a,
                                    REG_PLL_CONFIG_1,0xc8,
                                    REG_PLL_CONFIG_2,0xae,
                                    REG_PLL_CONFIG_0,0x8a,
                                    REG_MEMCLK_CONFIG,0,
                                    REG_PCLK_FREQ_RATIO_0,0,
                                    REG_PCLK_FREQ_RATIO_1,0,
                                    REG_PCLK_FREQ_RATIO_2,0x02,
                                    REG_PANEL_TYPE,panelType|panelWidth,
                                    REG_HORIZ_TOTAL_0,(horizontalTotal >> 3),
                                    REG_HORIZ_TOTAL_1,(horizontalTotal % 8),
                                    REG_HDP,(GFX_DRV_instance[instance].horizontalResolution >>3) - 1,
                                    REG_HDP_START_POS0,(GFX_DRV_instance[instance].horizontalPulseWidth + GFX_DRV_instance[instance].horizontalBackPorch),
                                    REG_HDP_START_POS1,(GFX_DRV_instance[instance].horizontalPulseWidth + GFX_DRV_instance[instance].horizontalBackPorch)>>8,
                                    REG_HSYNC_PULSE_WIDTH,(GFX_DRV_instance[instance].horizontalPulseWidth - 1),
                                    REG_VERT_TOTAL0,(verticalTotal),
                                    REG_VERT_TOTAL1,(verticalTotal>>8),
                                    REG_VDP0,(GFX_DRV_instance[instance].verticalResolution - 1),
                                    REG_VDP1,((GFX_DRV_instance[instance].verticalResolution - 1)>>8),
                                    REG_VDP_START_POS0,(GFX_DRV_instance[instance].verticalPulseWidth + GFX_DRV_instance[instance].verticalBackPorch),
                                    REG_VDP_START_POS1,(GFX_DRV_instance[instance].verticalPulseWidth + GFX_DRV_instance[instance].verticalBackPorch)>>8,
                                    REG_VSYNC_PULSE_WIDTH,(GFX_DRV_instance[instance].verticalPulseWidth - 1),
                                    REG_SPECIAL_EFFECTS, (0x40 | rotation),
                                    REG_MAIN_WIN_DISP_START_ADDR0,(windowStartAddress),
                                    REG_MAIN_WIN_DISP_START_ADDR1,(windowStartAddress>>8),
                                    REG_MAIN_WIN_DISP_START_ADDR2,(windowStartAddress>>16),
                                    REG_MAIN_WIN_ADDR_OFFSET0, windowOffset,
                                    REG_MAIN_WIN_ADDR_OFFSET1, (windowOffset >> 8),
                                    REG_DISPLAY_MODE,0x04,
                                    REG_RGB_SETTING,0xc0,
                                    REG_LSHIFT_POLARITY, GFX_DRV_instance[instance].logicShift,
                                    REG_POWER_SAVE_CONFIG,0,
                                    0,0,
                                    0,0,
                                    REG_GPIO_STATUS_CONTROL1,0x80,
                                    REG_2D_1f8, horizontalSize,
                                    REG_2D_1f9,(horizontalSize >> 8),
                                    REG_2D_1d8, horizontalSize,
                                    REG_2D_1d9,(horizontalSize >> 8),
                                    REG_2D_214,1,
                                    REG_2D_215,0,
                                    REG_2D_218,1,
                                    REG_2D_219,0,
                                    REG_2D_1dd,0};

  if(GFX_DRV_SSD1926_SetReg(*registers[state-1], registers[state-1][1]))
  {
      return(1);
  }

  state++;

}
    GFX_DRV_instance[0].ready = 1;
    GFX_DRV_instance[instance].driverBusy =0;
    GFX_DRV_instance[instance].horizontalResolution = horizontalSize; 
    GFX_DRV_instance[instance].verticalResolution = verticalSize;

    DisplayBacklightOn();

    return (0); //Driver initialized successfully
}

// *****************************************************************************
/*
  Function: void GFX_DRV_SSD1926_SetColor(GFX_COLOR color)

  Summary: Sets the color for the driver instance

  Description:
  
  Output: none

*/

void GFX_DRV_SSD1926_SetColor(GFX_COLOR color)
{
  GFX_DRV_instance[0].color = color;
}

// *****************************************************************************
/*
  Function: void GFX_DRV_SSD1926_SetInstance(uint8_t instance)

  Summary: Sets the instance for the driver

  Description:
  
  Output: none

*/

void GFX_DRV_SSD1926_SetInstance(uint8_t instance)
{
  _instance = instance;
}

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_SSD1926_BarFill(short left, short top, short right, short bottom)

  Summary:
    Hardware accelerated barfill function

  Description:
    see primitive BarDraw
  
  Output:
    1 - call not successful (PMP driver busy)
    0 - call successful
*/
uint16_t  GFX_DRV_SSD1926_BarFill(short left, short top, short right, short bottom)
{
   
   static uint32_t   address;
   static short      width, height;
   uint8_t           commandCount = 3;
   static uint32_t   myWriteBuffer;
   static uint8_t    state = 0;

   static uint16_t barParams[13][2] = {{REG_2D_1f4,0},{REG_2D_1f5, 0},{REG_2D_1f6,0}, //Destination Address
                                       {REG_2D_204,0},{REG_2D_205,0},{REG_2D_206,0},  //Brush Address
                                       {REG_2D_1e4,0},{REG_2D_1e5,0},{REG_2D_1e8,0},{REG_2D_1e9,0}, //Width and Height
                                       {REG_2D_1fc,0xf0},{REG_2D_1d1,0x09},{REG_2D_1d2,0x01}}; //Bar 2d Commands

   if(SSD1926taskBusy == 0)
   {
       if(SSD1926queueCount >= (GFX_DRV_SSD1926_COMMANDQUEUESIZE-commandCount)) 
       {
           return (1); //queue is full
       }

       SSD1926driverBusy = 1;

       while(commandCount--)
       {

           if(commandCount == 0)
           {
                SSD1926queueIndex->task = BUSY; //Set Address
           }
           else if(commandCount == 2)
           {
                SSD1926queueIndex->task = BAR; //Set Address
                SSD1926queueIndex->address = left;
                SSD1926queueIndex->count = 1;
                SSD1926queueIndex->lineCount = top;
           }
           else
           {
                SSD1926queueIndex->task = BAR; //Set Address
                SSD1926queueIndex->address = right;
                SSD1926queueIndex->count = 0;
                SSD1926queueIndex->data = GFX_DRV_instance[0].color;
                SSD1926queueIndex->lineCount = bottom;
           }

          if(SSD1926queueIndex == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
          {
               SSD1926queueIndex = &SSD1926commandBuffer[0];
          }
          else
          {
               SSD1926queueIndex++;
          } 
       }

 SSD1926queueCount += 3;
 SSD1926driverBusy = 0;
 return(0);
}

switch(state)
{
case 0:
    width = right - left + 1;
    barParams[6][1] = width;
    barParams[7][1] = width>>8;

    height = bottom - top + 1;
    barParams[8][1] = height;
    barParams[9][1] = (height >> 8);

    address = ((uint32_t) (GFX_DRV_instance[0].horizontalResolution) * top + left);
    barParams[0][1] = address;
    barParams[1][1] = (address >> 8);
    barParams[2][1] = (address >> 16);
    barParams[3][1] = barParams[0][1];
    barParams[4][1] = barParams[1][1];
    barParams[5][1] = barParams[2][1];
    state++;
case 1:
    if(GFX_DRV_SSD1926_SetAddress(address<<1)) return(1);
    myWriteBuffer = _barColor;
    state++;
case 2:
    if(DRV_PMP_Write ( &pmphandle, false, &myWriteBuffer, 2, 0) == NULL)return(1);
    state++;
default: break;
}

while(1)
{
if(GFX_DRV_SSD1926_SetReg(barParams[state-3][0], (uint8_t)barParams[state-3][1])) return(1);
if(state++ == 15)
{
     state = 0;
     return(0);
}
}

}

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_SSD1926_PixelPut(short x, short y)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates
  Output:
    1 - call not successful (SSD1926 driver busy)
    0 - call successful
*/
uint16_t GFX_DRV_SSD1926_PixelPut(short x, short y)
{

    if(SSD1926queueCount >= (GFX_DRV_SSD1926_COMMANDQUEUESIZE-1)) 
    {
     return (1); //queue is full
    }

     SSD1926driverBusy = 1;
     
     SSD1926queueIndex->task = PUT_PIXELS;
     SSD1926queueIndex->address = (((uint32_t) (GFX_DRV_instance[0].horizontalResolution)) * (y) + (x)) << 1;
     SSD1926queueIndex->data = GFX_DRV_instance[0].color;
     SSD1926queueIndex->instance = _instance;
     SSD1926queueIndex->count = 1;
     SSD1926queueIndex->lineCount = 1;

      if(SSD1926queueIndex == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
      {
          SSD1926queueIndex = &SSD1926commandBuffer[0];
      }
      else
      {
          SSD1926queueIndex++;
      } 

     SSD1926queueCount++;
     SSD1926driverBusy = 0;
     return(0);

}  

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_SSD1926_PixelsPut(short x, short y, uint16_t count)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates

  Output:
          1 - call not successful (SSD1926 driver busy)
          0 - call successful
*/
uint16_t  GFX_DRV_SSD1926_PixelsPut(short x, short y, uint16_t count, uint16_t lineCount)
{

    if(SSD1926queueCount >= (GFX_DRV_SSD1926_COMMANDQUEUESIZE-1)) 
    {
         return (1); //queue is full
    }

     SSD1926driverBusy = 1;

     SSD1926queueIndex->instance = _instance;
     SSD1926queueIndex->task = PUT_PIXELS;
     SSD1926queueIndex->address = (((uint32_t) (GFX_DRV_instance[_instance].horizontalResolution)) * (y) + (x)) << 1;
     SSD1926queueIndex->data = GFX_DRV_instance[0].color;
     SSD1926queueIndex->count = count;
     SSD1926queueIndex->lineCount = lineCount;

      if(SSD1926queueIndex == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
      {
          SSD1926queueIndex = &SSD1926commandBuffer[0];
      }
      else
      {
          SSD1926queueIndex++;
      } 

     SSD1926queueCount++;
     SSD1926driverBusy = 0;
     return(0);

}  

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_SSD1926_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count)

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
uint16_t*  GFX_DRV_SSD1926_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count, uint16_t lineCount)
{
    static GFX_DRV_SSD1926_COMMAND  *imageIndex;

    if(SSD1926queueCount >= (GFX_DRV_SSD1926_COMMANDQUEUESIZE-1)) 
    {
     return (NULL); //queue is full
    }

     SSD1926driverBusy = 1;
   
     imageIndex = SSD1926queueIndex;      //Inrement the queue pointer and index the value in case we are interrupted 

     SSD1926queueIndex->task = PUT_ARRAY;
     SSD1926queueIndex->address = (((uint32_t) (GFX_DRV_instance[_instance].horizontalResolution)) * (y) + (x)) << 1;
     SSD1926queueIndex->array = color;   //Starting address of the array
     SSD1926queueIndex->count = count;
     SSD1926queueIndex->lineCount = lineCount;

      if(SSD1926queueIndex == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
      {
          SSD1926queueIndex = &SSD1926commandBuffer[0];
      }
      else
      {
          SSD1926queueIndex++;
      } 

     SSD1926queueCount++;
     SSD1926driverBusy = 0;
     return(&imageIndex->count);

} 

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_SSD1926_PixelArrayGet(uint16_t *color, short x, short y, uint16_t count)

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
         1 - call not successful (SSD1926 driver busy)
         0 - call successful
*/ 
uint16_t*  GFX_DRV_SSD1926_PixelArrayGet(uint16_t *color,short x, short y, uint16_t count)
{
    //Not yet supported
    return(NULL);
}  

// *****************************************************************************
/*
  Function: uint16_t  GFX_DRV_SSD1926_Busy(uint8_t instance)

  Summary:
    Returns non-zero if LCD controller is busy 
          (previous drawing operation is not completed).

  Description:
    none

  Input:
          instance - driver instance
  Output:
         1 - busy
         0 - not busy
*/ 
uint16_t  GFX_DRV_SSD1926_Busy(uint8_t instance)
{  

   uint8_t dummy = 0x00;
 
   if(GFX_DRV_SSD1926_GetReg(REG_2D_220,(uint8_t*)&dummy)) 
        return(1);

   if(dummy == 1)
   {
      return(0);
   }
   else
   {
      return(1);
   }

}

// *****************************************************************************
/*
  Function:
	void GFX_DRV_SSD1926_Tasks(void)

  Summary:
	Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer
*/
//
void GFX_DRV_SSD1926_Tasks(void)
{
   static GFX_DRV_SSD1926_COMMAND  *index = &SSD1926commandBuffer[0];
   static uint16_t x,y;
   static uint8_t state = 0;
   static QUEUE_ELEMENT_OBJECT* regCommand = NULL;

if(SSD1926driverBusy == 1)
	return;


while(SSD1926queueCount != 0)
{

  switch(index->task)  //State Machine for Putpixel ONLY
  {

    case INITIALIZE: 
    if(GFX_DRV_instance[0].ready != 1)
    {
         SSD1926taskBusy = 1;
         if(GFX_DRV_SSD1926_Initialize(index->instance))
         {
               SSD1926taskBusy = 0;
               return;  //Call until the driver is initialized
         }
         SSD1926taskBusy = 0;
    }
    break;
  
    case PUT_PIXELS:

    while(index->lineCount)
    {
    if(state == 0)
    {
    if(GFX_DRV_SSD1926_SetAddress(index->address)) 
        return;
    state = 1;
    }
    if(DRV_PMP_Write ( &pmphandle, false, (uint32_t*)&index->data, 2, index->count-1) == NULL)
        return;
    state = 0;
    index->address += ((GFX_DRV_instance[index->instance].horizontalResolution)<<1);
    index->lineCount--;
     }
    break;

    case PUT_ARRAY:

    while(index->lineCount)
    {

    if(state == 0)
    {
        if(GFX_DRV_SSD1926_SetAddress(index->address))
            return;
        state = 1;
    }
    else if(state == 2)
    {
              if(DRV_PMP_TransferStatus(regCommand) != PMP_TRANSFER_FINISHED)
                   return;

              state = 0;
              index->address += ((GFX_DRV_instance[index->instance].horizontalResolution)<<1);
              index->lineCount--;
    }
    else
    {
         regCommand = DRV_PMP_Write ( &pmphandle, false, (uint32_t*)index->array, (index->count)<<1, 0);
         if(regCommand == NULL)
         return;
         state = 2;
    }
  
    }
    index->count = 0;
    break;

    case BUSY:

    if(GFX_DRV_SSD1926_Busy(index->instance) == 1)
    {     
         return; //return if busy
    }
    break;

    case BAR:    //Bar Drawing
    if(index->count == 1)
    {
         x = index->address;
         y = index->lineCount;
    }
    else
    {
         SSD1926taskBusy = 1;
         _barColor = index->data;
         if(GFX_DRV_SSD1926_BarFill(x, y, index->address, index->lineCount))
         {     
            SSD1926taskBusy = 0;
            return;
         }
         SSD1926taskBusy = 0; 
    }
    break;
    default: //Do nothing
    break;
   }

    SSD1926queueCount--;      //Subtract 1 from the queue count

   if(index++ == &SSD1926commandBuffer[GFX_DRV_SSD1926_COMMANDQUEUESIZE-1])
   {
     index = &SSD1926commandBuffer[0];     
   }
}
}
#endif // #if (GFX_USE_DISPLAY_CONTROLLER_SSD1926)    
