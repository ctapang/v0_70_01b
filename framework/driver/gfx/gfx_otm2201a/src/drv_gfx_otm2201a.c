/*
 ******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    drv_gfx_otm2201a.c

  Summary:
    Driver library for device OTM2201A with TFT display connected

  Description:
    Driver library for device OTM2201A includes:
    - Writing to device registers and GRAM using PMP Driver
    - Initialization of the OTM2201A
    - Supports rotation of the display
    - Supports displaying single pixel, n pixels, array of pixels

    PMP Bus width is 8 bit, GRAM address is 16 bit(8 - horizontal, 8 -
    vertical) and color format if 16 bit(5 - Red, 6 - Green, 5 - Blue)
 *******************************************************************************
*/
/*
******************************************************************************
  Software License Agreement
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
  OR OTHER SIMILAR COSTS.
*******************************************************************************
*/

#include "driver/gfx/drv_gfx_display.h"

#if defined (GFX_USE_DISPLAY_CONTROLLER_OTM2201A)

#include "driver/gfx/gfx_otm2201a/drv_gfx_otm2201a.h"

/*
 ******************************************************************************
 *                      Gloabal Variables
 ******************************************************************************
 */

//global instance for the driver
uint8_t             _instance;
//PMP Data Width
//uint8_t             _dataWidth;
//pmp driver handle
DRV_HANDLE          pmphandle;
DRV_PMP_MODE_CONFIG config;

//This contains the commands to send to the graphics driver
GFX_DRV_OTM2201A_COMMAND  OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE];

//pointer to where the command Buffer is currently
GFX_DRV_OTM2201A_COMMAND* OTM2201AqueueIndex = &OTM2201AcommandBuffer[0];

volatile uint16_t   OTM2201AqueueCount   = 0;
//Flag to state driver is busy
volatile uint16_t   OTM2201AdriverBusy   = false;
//Flag to state task is busy
volatile uint8_t    OTM2201AtaskBusy     = false;
//Flag to state task is Ready
volatile uint8_t    OTM2201AtaskReady    = false;

//holds instances of GFX_CONFIG_DRIVER_COUNT number of drivers
uint8_t instances[GFX_CONFIG_DRIVER_COUNT] = {0};

uint8_t xCount = 0;
uint8_t yCount = 0;

//driver configuration
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
        USE_TCON_MODULE,
        {GFX_DRV_OTM2201A_PixelsPut,
         NULL,
         GFX_DRV_OTM2201A_PixelArrayPut,
         GFX_DRV_OTM2201A_PixelArrayGet,
         GFX_DRV_OTM2201A_PixelPut,
         GFX_DRV_OTM2201A_ColorSet,
         GFX_DRV_OTM2201A_InstanceSet,
         NULL,
         NULL,
         NULL,
         NULL},
        1,
        0,
    };

uint32_t _PixelStartAddress(short x, short y, uint16_t orientation)
{
    switch(orientation)
    {
        case DEGREE_90:

            return (((GFX_DRV_instance[_instance].horizontalResolution - x - 1)
                     << 8) | y);

         break;

         case DEGREE_180:
             return (GFX_DRV_instance[_instance].horizontalResolution - x - 1) |
                    ((GFX_DRV_instance[_instance].verticalResolution - y - 1) <<
                     8);
         break;

         case DEGREE_270:

             return ((GFX_DRV_instance[_instance].horizontalResolution - x - 1) 
                     << 8) |
                     (GFX_DRV_instance[_instance].verticalResolution - y - 1);

         break;

         case DEGREE_0:
         default:

             return x | (y << 8);

         break;
    }
}

uint32_t _PixelAddressUpdate(uint16_t x, uint16_t y,
                            uint16_t lineCount, uint16_t orientation)
{

    switch(orientation)
    {
        case DEGREE_90:

            return (x + lineCount) | (y << 8);

            break;

        case DEGREE_180:

            return x | ((y - lineCount) << 8);

            break;

        case DEGREE_270:

            return (x - lineCount) | (y << 8);
            
            break;

        case DEGREE_0:
        default:
            
            return x | ((y + lineCount) << 8);

            break;
    }
}


/*
 ******************************************************************************

  Function: GFX_DRV_OTM2201A_Open(uint8_t instance)

  Summary:
    opens an instance of the graphics controller

  Description:
    Opens the instance of driver if instance is valid and not already opened

  Input:
    instance of the driver

  Output:
    DRV_OTM2201A_NEW_INSTANCE_OPEN     - driver not initialied
    DRV_OTM2201A_INSTANCE_DOESNT_EXIST - instance doesn't exist
    DRV_OTM2201A_INSTANCE_ALREADY_OPEN - instance already open

*******************************************************************************
*/
uint16_t GFX_DRV_OTM2201A_Open(uint8_t instance)
{

   if(GFX_DRV_instance[0].ready == false)
   {
       return(DRV_OTM2201A_INSTANCE_ALREADY_OPEN);
   }

   if(instance >= GFX_CONFIG_DRIVER_COUNT)
   {
      return(DRV_OTM2201A_INSTANCE_DOESNT_EXIST);
   }

   if(instances[instance] == 0)
   {
       instances[instance] = DRV_OTM2201A_NEW_INSTANCE_OPEN;
       return(instance);
   }
   else
   {
     return(DRV_OTM2201A_INSTANCE_ALREADY_OPEN);
   }
}

/*
*******************************************************************************

  Function: GFX_DRV_OTM2201A_Close(uint8_t instance)

  Summary:
    closes an instance of the graphics controller

  Description:
    closes an instance if instance exists and not already closed

  Input:
    instance - instance of the driver

  Output:
    DRV_OTM2201A_INSTANCE_CLOSED         - instance closed
    DRV_OTM2201A_INSTANCE_DOESNT_EXIST   - instance doesn't exist
    DRV_OTM2201A_INSTANCE_ALREADY_CLOSED - instance already closed
*******************************************************************************
*/

uint16_t GFX_DRV_OTM2201A_Close(uint8_t instance)
{

   if(instance>=GFX_CONFIG_DRIVER_COUNT)
   {
      return(DRV_OTM2201A_INSTANCE_DOESNT_EXIST);
   }
   
   if(instances[instance] == DRV_OTM2201A_INSTANCE_VALID)
   {   
       instances[instance] = DRV_OTM2201A_INSTANCE_CLOSED;
       return(DRV_OTM2201A_INSTANCE_CLOSED);
   }
   else
   {
     return(DRV_OTM2201A_INSTANCE_ALREADY_CLOSED);
   }
}

/*
*******************************************************************************
  Function: uint16_t GFX_DRV_OTM2201A_AddressSet(uint32_t address)

  Summary:
    Sets the start GRAM address where pixel data to be written

  Description:
    Address consists of: 
        Lower 8 bit at Register REG_RAM_ADDR_LOW
        Higher 8 bit at Register REG_RAM_ADDR_HIGH

  Input:
    address - address

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write
    DRV_OTM2201A_ERROR_NO_ERROR - returns success without any error
*******************************************************************************
*/

uint16_t GFX_DRV_OTM2201A_AddressSet(uint32_t address)
{
    static uint32_t data = 0x00000000;
    static QUEUE_ELEMENT_OBJECT *regCommand = NULL;

    data = REG_RAM_ADDR_LOW;
    if(DRV_PMP_Write ( &pmphandle, 
                       true,
                       &data,
                       NUM_BYTES_2,
                      REPEAT_CNT_0) == NULL)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }

    data  = address & DRV_OTM2201A_ADDR_LOW_MASK;
    regCommand = DRV_PMP_Write (&pmphandle,
                                false,
                                &data,
                                NUM_BYTES_2,
                                REPEAT_CNT_0);

    if(DRV_PMP_TransferStatus(regCommand) != PMP_TRANSFER_FINISHED)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }

    data = REG_RAM_ADDR_HIGH;
    if(DRV_PMP_Write ( &pmphandle, 
                                true,
                                &data,
                                NUM_BYTES_2,
                                REPEAT_CNT_0) == NULL)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }

    data = (address & DRV_OTM2201A_ADDR_HIGH_MASK)
            >> DRV_OTM2201A_ADDR_HIGH_SHIFT;
            
    regCommand = DRV_PMP_Write (   &pmphandle,
                                    false,
                                    &data,
                                    NUM_BYTES_2,
                                    REPEAT_CNT_0);

    if(DRV_PMP_TransferStatus(regCommand) != PMP_TRANSFER_FINISHED)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }

    return(DRV_OTM2201A_ERROR_NO_ERROR);
}

/*
 *****************************************************************************
  Function: uint8_t GFX_DRV_OTM2201A_RegSet(uint16_t index,
                                            uint16_t value,
                                            uint32_t repeatCount)

  Summary:
    updates graphics controller register value (byte access)

  Description:
    This call can set "value" of the register accessed by its "index" and can
 repeat the same by number of times mentioned in "repeatCount"

  Input:
    index       - register number
    value       - value to write to register
    repeatCount - repeatCount number of times value is to be written to the
                    register.

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write
    DRV_OTM2201A_ERROR_NO_ERROR - returns success without any error
 
*******************************************************************************
*/
uint16_t GFX_DRV_OTM2201A_RegSet(uint16_t index,
                                uint16_t value,
                                uint32_t repeatCount)
{
    static uint32_t myWriteBuffer = 0;
    static QUEUE_ELEMENT_OBJECT* regCommand = NULL;
    
     myWriteBuffer = index;
     if(DRV_PMP_Write ( &pmphandle,
                        true,
                        &myWriteBuffer,
                        NUM_BYTES_2,
                        REPEAT_CNT_0) == NULL)
     {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
     }
            
     myWriteBuffer = value;
     regCommand = DRV_PMP_Write (  &pmphandle,
                                    false,
                                    &myWriteBuffer,
                                    NUM_BYTES_2,
                                    repeatCount);
            
    if(DRV_PMP_TransferStatus(regCommand) != PMP_TRANSFER_FINISHED)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }

     return(DRV_OTM2201A_ERROR_NO_ERROR);
}

/*
*******************************************************************************
  Function: uint8_t GFX_DRV_OTM2201A_RegGet(
                                            uint16_t index,
                                            uint8_t *data
                                            )

  Summary:
    returns graphics controller register value (byte access)

  Description:
    returns graphics controller register value (byte access)

  Input:
    index - register number
    *data - array to store register data

  Output:
    DRV_OTM2201A_ERROR_PMP_WRITE - returns error during PMP Write
    DRV_OTM2201A_ERROR_PMP_READ  - returns error during PMP Read
    DRV_OTM2201A_ERROR_NO_ERROR  - returns success without any error
*******************************************************************************
*/
uint8_t  GFX_DRV_OTM2201A_RegGet(uint16_t  index, uint16_t *data)
{

#if !defined(DRV_OTM2201A_FEATURE_NOT_SUPPORTED)
    static uint16_t myReadBuffer = 0x0000;
    static uint32_t myWriteBuffer;
    static QUEUE_ELEMENT_OBJECT* getRegCommand = NULL;

    myWriteBuffer = index;

    if(DRV_PMP_Write(   &pmphandle,
                        true,
                        &myWriteBuffer,
                        NUM_BYTES_2,
                        REPEAT_CNT_0) == NULL)
    {
        return(DRV_OTM2201A_ERROR_PMP_WRITE);
    }
    
    if (DRV_PMP_Read (  pmphandle,
                        false,
                        &myReadBuffer,
                        NUM_BYTES_2) == NULL)
    {
        return(DRV_OTM2201A_ERROR_PMP_READ);
    }

    getRegCommand = DRV_PMP_Read (  pmphandle,
                                    false,
                                    &myReadBuffer,
                                    NUM_BYTES_2);
    if(getRegCommand == NULL)
    {
        return(DRV_OTM2201A_ERROR_PMP_READ);
    }
    
    if(DRV_PMP_TransferStatus(getRegCommand) != PMP_TRANSFER_FINISHED)
    {
        return(DRV_OTM2201A_ERROR_PMP_READ);
    }

    *data  = myReadBuffer;
    return(DRV_OTM2201A_ERROR_NO_ERROR);
    
#else

    *data = 1;
    return (DRV_OTM2201A_ERROR_NO_ERROR);

#endif
}

/*
*******************************************************************************

  Function: uint8_t GFX_DRV_OTM2201A_BrightnessSet(
    uint8_t instance,
    uint16_t level
    )

  Summary:
    Sets the brightness of the display backlight.

  Description:
    Sets the brightness of the display backlight.

  Input:
        level - Brightness level. Valid values are 0 to 100.
		0   = brightness level is zero or display is turned off.
                100 = brightness level is maximum.

  Output:
    none
 
********************************************************************************
*/
void GFX_DRV_OTM2201A_BrightnessSet(uint8_t instance, uint16_t  level)
{

#if !defined(DRV_OTM2201A_FEATURE_NOT_SUPPORTED)

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

#else

    return;

#endif

}

/*
*******************************************************************************
  Function: uint16_t GFX_DRV_OTM2201A_Initialize(uint8_t instance)

  Summary:
    Intialize OTM2201A device

  Description:
    Initialize OTM2201A device by initializing PMP interface, initializing
    command buffer for current instance initialize device registers

  Input:
        instance - driver instance

  Output:

    DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full
    DRV_OTM2201A_ERROR_REG_GET      - OTM2201A Error while reading register
    DRV_OTM2201A_ERROR_REG_SET      - OTM2201A Error while writing register
    DRV_OTM2201A_ERROR_DEVICE_BUSY  - OTM2201A device is busy
    DRV_OTM2201A_ERROR_NO_ERROR     - Success without any error
    
*******************************************************************************
*/

uint16_t GFX_DRV_OTM2201A_Initialize(uint8_t instance)
{
    static uint8_t  state           = 0;
    static uint16_t horizontalSize;
    static uint16_t verticalSize;
    static uint16_t dummy           = 1;
    static uint16_t entryMode       = 0;
    static uint16_t scanMode        = 0x001C;
    
    if( OTM2201AtaskBusy == false)
    {
        if(OTM2201AqueueCount >= (GFX_DRV_OTM2201A_COMMANDQUEUESIZE - 1))
        {
            return(DRV_OTM2201A_ERROR_QUEUE_FULL);
        }

        //Start the state machine in the init function
        OTM2201AqueueIndex->task     = INITIALIZE;
        //Start the state machine in the init function
        OTM2201AqueueIndex->instance = instance;

        if(OTM2201AqueueIndex ==
                &OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1])
        {
             OTM2201AqueueIndex = &OTM2201AcommandBuffer[0];
        }
        else
        {
             OTM2201AqueueIndex++;
        }

          OTM2201AqueueCount++;
          return(DRV_OTM2201A_ERROR_NO_ERROR);
    }


    while(state <= 32)
    {
        switch(state)
        {
            case 0:

                DriverInterfaceInit(&pmphandle, &config);

                //_dataWidth = config.portSize;

                DisplayResetDisable();
                SYS_TMR_DelayMS(10);
                DisplayResetEnable();
                SYS_TMR_DelayMS(100);
                // release from reset
                DisplayResetDisable();
                // give time for the controller to power up
                SYS_TMR_DelayMS(100);
                DisplayEnable();

                if((GFX_DRV_instance[instance].orientation  == DEGREE_90) ||
                    (GFX_DRV_instance[instance].orientation == DEGREE_270))
                {
                    horizontalSize =
                            GFX_DRV_instance[instance].verticalResolution;
                    verticalSize   =
                            GFX_DRV_instance[instance].horizontalResolution;
                }
                else
                {
                    horizontalSize =
                            GFX_DRV_instance[instance].horizontalResolution;
                    verticalSize   =
                            GFX_DRV_instance[instance].verticalResolution;
                }

                switch(GFX_DRV_instance[instance].orientation)
                {
                    case DEGREE_90:
                        entryMode = 0x1008;
                        scanMode  = 0x011C;
                        break;

                    case DEGREE_180:
                        entryMode = 0x1000;
                        scanMode  = 0x011C;
                        break;

                    case DEGREE_270:
                        entryMode = 0x1008;
                        scanMode  = 0x031C;
                        break;

                    case DEGREE_0:
                    default:
                        entryMode = 0x1030;
                        scanMode  = 0x001C;
                        break;
                }
                
            break;

            case 1:
                    
                if(GFX_DRV_OTM2201A_RegGet(REG_POWER_CTRL_2, &dummy))
                {
                    return(DRV_OTM2201A_ERROR_REG_GET);
                }

            break;
                    
            case 2:

                if(!dummy)
                {
                    state = 1;
                    return(DRV_OTM2201A_ERROR_DEVICE_BUSY);
                }

            break;

            case 3:

#if(USE_TCON_MODULE == 1)
                    if(GFX_DRV_instance[instance].timingControl == 1)
                    GfxTconInit();
#endif
            break;

            default:
                break;
        }

        //OTM2201A Registers to be initialized
        uint16_t registers[33][2] = {
                            REG_POWER_CTRL_2,               0x0018,
                            REG_POWER_CTRL_3,               0x0000,
                            REG_POWER_CTRL_4,               0x0063,
                            REG_POWER_CTRL_5,               0x556A,
                            REG_POWER_CTRL_1,               0x0800,
                            REG_POWER_CTRL_2,               0x0118,
                            REG_POWER_CTRL_2,               0x0318,
                            REG_POWER_CTRL_2,               0x0718,
                            REG_POWER_CTRL_2,               0x0F18,
                            REG_POWER_CTRL_2,               0x0F38,
                            REG_DISP_CTRL,                  0x001A,
                            REG_DRV_OUT_CTRL,               scanMode,
                            REG_ENTRY_MODE,                 entryMode,
                            REG_DISP_CTRL,                  0x0000,
                            REG_BLANKING_CTRL,              0x0808,
                            REG_VCI_PERIOD,                 0x0020,
                            REG_HORZ_WND_ADDR_1,            0x00AF,
                            REG_HORZ_WND_ADDR_2,            0x0000,
                            REG_VERT_WND_ADDR_1,            0x00DB,
                            REG_VERT_WND_ADDR_2,            0x0000,
                            REG_GAMMA_CTRL_1,               0x0001,
                            REG_GAMMA_CTRL_2,               0x0208,
                            REG_GAMMA_CTRL_3,               0x0805,
                            REG_GAMMA_CTRL_4,               0x0404,
                            REG_GAMMA_CTRL_5,               0x0C0C,
                            REG_GAMMA_CTRL_6,               0x000C,
                            REG_GAMMA_CTRL_7,               0x0100,
                            REG_GAMMA_CTRL_8,               0x0400,
                            REG_GAMMA_CTRL_9,               0x1108,
                            REG_GAMMA_CTRL_10,              0x050C,
                            REG_OSC_CTRL,                   0x1F01,
                            REG_DISP_CTRL,                  0x0012,
                            REG_DISP_CTRL,                  0x0017};

         if(GFX_DRV_OTM2201A_RegSet(*registers[state],
                                    registers[state][1],
                                    REPEAT_CNT_0))
         {
            return(DRV_OTM2201A_ERROR_REG_SET);
         }

            SYS_TMR_DelayMS(50);
            state++;
    }

    GFX_DRV_instance[0].ready                       = true;
    GFX_DRV_instance[instance].driverBusy           = false;
    GFX_DRV_instance[instance].horizontalResolution = horizontalSize;
    GFX_DRV_instance[instance].verticalResolution   = verticalSize;

    return(DRV_OTM2201A_ERROR_NO_ERROR);
}

/*
*******************************************************************************

  Function: void GFX_DRV_OTM2201A_ColorSet(GFX_COLOR color)

  Summary:
    Sets the color for the driver instance

  Description:
    Sets the color for the driver instance

  Input:
    color - 16 bit 565 format color value

  Output: none

*******************************************************************************
*/

void GFX_DRV_OTM2201A_ColorSet(GFX_COLOR color)
{
  GFX_DRV_instance[_instance].color = color;
}

/*
*******************************************************************************

  Function: void GFX_DRV_OTM2201A_InstanceSet(uint8_t instance)

  Summary:
    Sets the instance for the driver

  Description:
    Sets the instance for the driver

  Input:
    instance - driver instance
 
  Output: none
 
*******************************************************************************
*/

void GFX_DRV_OTM2201A_InstanceSet(uint8_t instance)
{
  _instance = instance;
}


/*
*******************************************************************************

  Function: uint16_t GFX_DRV_OTM2201A_PixelPut(short x, short y)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        x           - pixel coordinate on x axis
        y           - pixel coordinate on y axis
 
  Output:

        DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full
        DRV_OTM2201A_ERROR_NO_ERROR     - Success without any error

*******************************************************************************
*/
uint16_t GFX_DRV_OTM2201A_PixelPut(short x, short y)
{

    if(OTM2201AqueueCount >= (GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1))
    {
        return (DRV_OTM2201A_ERROR_QUEUE_FULL);
    }

     OTM2201AqueueIndex->task        = PUT_PIXELS;
     OTM2201AqueueIndex->data        = GFX_DRV_instance[_instance].color;
     OTM2201AqueueIndex->instance    = _instance;
     OTM2201AqueueIndex->count       = 1;
     OTM2201AqueueIndex->lineCount   = 1;
     OTM2201AqueueIndex->address     = _PixelStartAddress(x, y,
                                    GFX_DRV_instance[_instance].orientation);

      if(OTM2201AqueueIndex ==
              &OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1])
      {
          OTM2201AqueueIndex = &OTM2201AcommandBuffer[0];
      }
      else
      {
          OTM2201AqueueIndex++;
      }

     OTM2201AqueueCount++;

     return(DRV_OTM2201A_ERROR_NO_ERROR);

}

/*
*******************************************************************************
  Function: uint16_t GFX_DRV_OTM2201A_PixelsPut(
                                                short x,
                                                short y,
                                                uint16_t count
                                                uint16_t lineCount
                                                )

  Summary:
    outputs count number of pixels into the frame buffer from the given x,y
    coordinate.

  Description:
    outputs count number of pixels into the frame buffer from the given x,y
    coordinate.

  Input:
 
        x           - pixel coordinate on x axis
        y           - pixel coordinate on y axis
        count       - count number of pixels
        lineCount   - lineCount number of display lines

  Output:

    DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full
    DRV_OTM2201A_ERROR_NO_ERROR     - Success without any error

*******************************************************************************
*/
uint16_t  GFX_DRV_OTM2201A_PixelsPut(short x,
                                    short y,
                                    uint16_t count,
                                    uint16_t lineCount)
{

    if(OTM2201AqueueCount >= (GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1))
    {
         return (DRV_OTM2201A_ERROR_QUEUE_FULL);
    }

     OTM2201AqueueIndex->instance    = _instance;
     OTM2201AqueueIndex->task        = PUT_PIXELS;
     OTM2201AqueueIndex->data        = GFX_DRV_instance[_instance].color;
     OTM2201AqueueIndex->count       = count;
     OTM2201AqueueIndex->lineCount   = lineCount;
     OTM2201AqueueIndex->address     = _PixelStartAddress(x, y,
                                    GFX_DRV_instance[_instance].orientation);

     if(OTM2201AqueueIndex ==
              &OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1])
      {
          OTM2201AqueueIndex = &OTM2201AcommandBuffer[0];
      }
      else
      {
          OTM2201AqueueIndex++;
      }

     OTM2201AqueueCount++;

     return(DRV_OTM2201A_ERROR_NO_ERROR);

}

/*
*******************************************************************************
  Function: uint16_t*  GFX_DRV_OTM2201A_PixelArrayPut(
                                                      uint16_t *color,
                                                      short x,
                                                      short y,
                                                      uint16_t count,
                                                      uint16_t lineCount
                                                    )

  Summary:
    outputs an array of pixels of length count starting at *color

  Description:
    outputs an array of pixels of length count starting at *color

  Input:
        color       - pointer to array of color of pixels
        x           - pixel coordinate on x axis.
        y           - pixel coordinate on y axis.
        count       - count number of pixels
        lineCount   - lineCount number of display lines
 
  Output:
         handle - handle to the number of pixels remaining
         DRV_OTM2201A_ERROR_QUEUE_FULL   - OTM2201A command queue is full

*******************************************************************************
*/
uint16_t*  GFX_DRV_OTM2201A_PixelArrayPut(   uint16_t *color,
                                            short x,
                                            short y,
                                            uint16_t count,
                                            uint16_t lineCount)
{

    static GFX_DRV_OTM2201A_COMMAND  *imageIndex;

    if(OTM2201AqueueCount >= (GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1))
    {
        return ((uint16_t *)DRV_OTM2201A_ERROR_QUEUE_FULL);
    }

     //Inrement the queue pointer and index the value in case we are interrupted
     imageIndex = OTM2201AqueueIndex;

     OTM2201AqueueIndex->task        = PUT_ARRAY;
     //Starting address of the array
     OTM2201AqueueIndex->array       = color;
     OTM2201AqueueIndex->count       = count;
     OTM2201AqueueIndex->lineCount   = lineCount;
     OTM2201AqueueIndex->address     = _PixelStartAddress(x, y,
                                    GFX_DRV_instance[_instance].orientation);

      if(OTM2201AqueueIndex ==
              &OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1])
      {
          OTM2201AqueueIndex = &OTM2201AcommandBuffer[0];
      }
      else
      {
          OTM2201AqueueIndex++;
      }

     OTM2201AqueueCount++;

     return(&imageIndex->count);

}

/*
*******************************************************************************

  Function: uint16_t  GFX_DRV_OTM2201A_PixelArrayGet(uint16_t *color,
                                                    short x,
                                                    short y,
                                                    uint16_t count)

  Summary:
    gets an array of pixels of length count into an array starting at *color

  Description:
    gets an array of pixels of length count into an array starting at *color

  Input:
            color   - Pointer to array where color data is to be loaded
            x       - pixel coordinate on x axis
            y       - pixel coordinate on y axis
            count   - count number of pixels
  Output:
         DRV_OTM2201A_ERROR_QUEUE_FULL  - OTM2201A command queue is full
         DRV_OTM2201A_ERROR_NO_ERROR    - Success without any error

*******************************************************************************
*/

uint16_t*  GFX_DRV_OTM2201A_PixelArrayGet(uint16_t *color,
                                        short x,
                                        short y,
                                        uint16_t count)
{
    //Not yet supported
    return(DRV_OTM2201A_ERROR_NO_ERROR);
}

/*
*******************************************************************************

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
         DRV_OTM2201A_ERROR_DEVICE_BUSY - Device is busy
         DRV_OTM2201A_ERROR_NO_ERROR    - Success, driver is not busy
 
*******************************************************************************
*/

uint16_t  GFX_DRV_OTM2201A_Busy(uint8_t instance)
{

#if !defined(DRV_OTM2201A_FEATURE_NOT_SUPPORTED)
    
   static uint16_t dummy = 0x00;

   if(GFX_DRV_OTM2201A_RegGet(REG_POWER_CTRL_2,(uint16_t*)&dummy))
        return(1);

   if(dummy == 1)
   {
      return(DRV_OTM2201A_ERROR_NO_ERROR);
   }
   else
   {
      return(DRV_OTM2201A_ERROR_DEVICE_BUSY);
   }
   
#endif

//   return(DRV_OTM2201A_ERROR_NO_ERROR);
}

/*
*******************************************************************************
  Function:
	void GFX_DRV_OTM2201A_Tasks(void)

  Summary:
	Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer

  Description:
        Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer

  Input:
        none
 
  Output:
        none
********************************************************************************
*/
//
void GFX_DRV_OTM2201A_Tasks(void)
{
    static GFX_DRV_OTM2201A_COMMAND  *index  = &OTM2201AcommandBuffer[0];
    static uint32_t data                    = 0;
    static uint32_t address                 = 0;
    static uint16_t y                       = 0;
    static QUEUE_ELEMENT_OBJECT* regCommand = NULL;

    while(OTM2201AqueueCount != 0)
    {
        switch(index->task)  //State Machine for Putpixel ONLY
        {
            case INITIALIZE:

                if(GFX_DRV_instance[0].ready != true)
                {
                    OTM2201AtaskBusy = true;
                    if(GFX_DRV_OTM2201A_Initialize(index->instance))
                    {
                        OTM2201AtaskBusy = false;
                        return;  //Call until the driver is initialized
                    }
                    OTM2201AtaskBusy = false;
                }
                
            break;

            case PUT_PIXELS:
                
                while(index->lineCount)
                {
                    address = _PixelAddressUpdate((index->address & 0x00FF),
                                           ((index->address & 0xFF00) >> 8),
                                            y,
                                   GFX_DRV_instance[_instance].orientation);

                    if(GFX_DRV_OTM2201A_AddressSet(address))
                    {
                        return;
                    }

                    if(GFX_DRV_OTM2201A_RegSet ( REG_GRAM_DATA ,
                                                index->data,
                                                index->count))
                    {
                        return;
                    }
                    
                    index->lineCount--;
                    y++;
                }

                y = 0;

            break;

            case PUT_ARRAY:
                
                while(index->lineCount)
                {
                    address = _PixelAddressUpdate((index->address & 0x00FF),
                                           ((index->address & 0xFF00) >> 8),
                                            y,
                                   GFX_DRV_instance[_instance].orientation);

                    if(GFX_DRV_OTM2201A_AddressSet(address))
                    {
                        return;
                    }

                    data = REG_GRAM_DATA;
                    
                    if(DRV_PMP_Write ( &pmphandle,
                                       true,
                                       &data,
                                       NUM_BYTES_2,
                                       REPEAT_CNT_0) == NULL)
                    {
                        return;
                    }

                    regCommand = DRV_PMP_Write (    &pmphandle,
                                                    false,
                                                    (uint32_t *)index->array,
                                                    index->count << 1,
                                                    0);

                    if(DRV_PMP_TransferStatus(regCommand) !=
                            PMP_TRANSFER_FINISHED)
                    {
                        return;
                    }

                    index->lineCount--;
                    y++;
                }

                index->count = 0;
                y = 0;

            break;
            
            default:
            break;
        }

        OTM2201AqueueCount--;      //Subtract 1 from the queue count

        if(index++ == &OTM2201AcommandBuffer[GFX_DRV_OTM2201A_COMMANDQUEUESIZE-1])
        {
            index = &OTM2201AcommandBuffer[0];
        }
    }
}

#endif
