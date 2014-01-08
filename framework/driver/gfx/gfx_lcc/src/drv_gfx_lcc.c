/*******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    lcc.c
    
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

#include "driver/gfx/gfx_lcc/drv_gfx_lcc.h"

#include <xc.h>
#include <sys/attribs.h>

#include "peripheral/int/plib_int.h"
#include "system/int/sys_int.h"
#include "peripheral/dma/plib_dma.h"
#include "peripheral/pmp/plib_pmp.h"

void __attribute__((always_inline)) BlockingUpdate(void);

/*These define the size (in resolution) of the LCD being used*/
#define LINE_LENGTH              DISP_HOR_RESOLUTION
#define FRAME_HEIGHT             DISP_VER_RESOLUTION

#define PIXEL_DRAW_PER_DMA_TX          20

/*This defines the polarity of the pixel clock as defined in LCD specs*/
#if(DISP_INV_LSHIFT == 1)
#define PCLK_POLARITY PMP_POLARITY_ACTIVE_LOW
#else
#define PCLK_POLARITY PMP_POLARITY_ACTIVE_HIGH
#endif

/*These define the size (in resolution) of the LCD being used*/
#define LINE_LENGTH              DISP_HOR_RESOLUTION
#define FRAME_HEIGHT             DISP_VER_RESOLUTION

#define VER_BLANK                 (DISP_VER_PULSE_WIDTH+DISP_VER_BACK_PORCH+DISP_VER_FRONT_PORCH-1)

volatile GFX_DRV_lcc_COMMAND lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE];  //This contains the commands to send to the graphics driver
volatile GFX_DRV_lcc_COMMAND *lccqueueIndex = &lcccommandBuffer[0];                             //pointer to where the command Buffer is currently
volatile GFX_DRV_lcc_COMMAND  *taskIndex = &lcccommandBuffer[0];

volatile uint16_t lccqueueCount = 0;
uint8_t instances[1] = {0};

volatile uint16_t lccdriverBusy = 0;                              //Flag to state driver is busy

#define DMA_CHANNEL DMA_CHANNEL_1


#define SRAM_ADDR_CS0  0xE0000000

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
        {GFX_DRV_lcc_PixelsPut, NULL, GFX_DRV_lcc_PixelArrayPut, GFX_DRV_lcc_PixelArrayGet, 
         GFX_DRV_lcc_PixelPut, GFX_DRV_lcc_SetColor, GFX_DRV_lcc_SetInstance,
         GFX_DRV_lcc_SetPage, GFX_DRV_lcc_Layer},
        1
    };

volatile uint8_t DrawCount = 0;                          /* The current status of how many pixels have been drawn inbetween a DMA IR*/
volatile uint8_t overflowcount;                      /* The count for the amount of overflows that have happened in the PMP Adress*/

#ifdef LCC_INTERNAL_MEMORY
uint8_t lccTaskActive = 1;
#define PMP_ADDRESS_LINES 0
volatile GFX_COLOR GraphicsFrame[1][(DISP_VER_RESOLUTION)][(DISP_HOR_RESOLUTION)];

#else
volatile uint8_t lccTaskActive = 0;
#if !defined(ADDR15)
#define PMP_ADDRESS_LINES 0xffff
#else
#define PMP_ADDRESS_LINES 0x7fff
#endif
uint16_t GraphicsFrame[LINE_LENGTH];
#endif 

#if(GFX_CONFIG_COLOR_DEPTH == 16)
    #define PMP_DATA_LENGTH PMP_DATA_SIZE_16_BITS
#else //(COLOR_DEPTH == 8)
    #define PMP_DATA_LENGTH PMP_DATA_SIZE_8_BITS
#endif

uint16_t HBackPorch = (DISP_HOR_PULSE_WIDTH+DISP_HOR_BACK_PORCH)-1;
uint16_t HFrontPorch = 1;

#ifdef USE_PIP
//PIP Variables (NULL at start)
uint16_t PipStartT = 0;
uint16_t PipStartL = 0;
uint16_t PipVLength = 0;
uint16_t PipHLength = 0;
static uint32_t PipX,PipY;
uint8_t _GFXPIPPage;
#endif

#ifdef USE_LCC_SCROLLING
uint16_t scroll,scrollLine,scrollPage = 0;
#endif

// *****************************************************************************
/*
  Function: GFX_DRV_lcc_Open(uint8_t instance)

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
uint16_t GFX_DRV_lcc_Open(uint8_t instance)
{

   if(GFX_DRV_instance[instance].ready == 0)
      return(1);

   if(instance >= 1)
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
  Function: GFX_DRV_lcc_Close(uint8_t instance)

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
uint16_t GFX_DRV_lcc_Close(uint8_t instance)
{
      
   if(instance >= 1)
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
void GFX_DRV_lcc_BrightnessSet(uint8_t instance, uint16_t  level)
{
     
}    

uint16_t GFX_DRV_lcc_SetPage(uint8_t pageType,uint8_t page)
{

    if(lccTaskActive)
    {
        switch(pageType)
        {
            case ACTIVE_PAGE:
                GFX_DRV_instance[0].activePage = page;
                break;
            case VISUAL_PAGE:
                GFX_DRV_instance[0].visualPage = page;
                #ifdef LCC_EXTERNAL_MEMORY
                ADDR17 = page;
                ADDR18 = page>>1;
                #endif
                break;
        }
    return(0);
    }

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
     return (1); //queue is full
    }
     lccdriverBusy = 1;
     lccqueueIndex->task = PAGE;
     lccqueueIndex->data = pageType;
     lccqueueIndex->instance = 0;
     lccqueueIndex->count = page;

      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      } 

     lccqueueCount++;
     lccdriverBusy = 0;
     return(0);
}
// *****************************************************************************
/*
  Function: void GFX_DRV_lcc_SetColor(uint8_t instance, GFX_COLOR color)

  Summary: Sets the color for the driver instance

  Description:
  
  Output: none

*/

void GFX_DRV_lcc_SetColor(GFX_COLOR color)
{
  GFX_DRV_instance[0].color = color;
}

// *****************************************************************************
/*
  Function: void GFX_DRV_lcc_SetInstance(uint8_t instance)

  Summary: Sets the instance for the driver

  Description:
  
  Output: none

*/

void GFX_DRV_lcc_SetInstance(uint8_t instance)
{
  //_instance = instance;
}

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
    1 - call not successful (PMP driver busy)
    0 - call successful
*/
uint16_t GFX_DRV_lcc_Initialize(uint8_t instance)
{

   static uint16_t  horizontalSize, verticalSize;

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

    /*Suspend DMA Module*/
    PLIB_DMA_SuspendEnable(0);

    #if defined(MEB_2_BOARD)
    TRISJbits.TRISJ7 = 0; //Camera
    LATJbits.LATJ7 = 1; //Camera

    TRISJbits.TRISJ12 = 0; //UB
    LATJbits.LATJ12 = 0; //UB

    TRISJbits.TRISJ10 = 0; //LB
    LATJbits.LATJ10 = 0; //LB

    CFGEBIA = 0;               //Address Lines of EBI are not
    CFGEBIC = 0;
    EBICS0  = 0x20000000;
    EBIMSK0 = 0x00000026;
    EBISMT0 = 0x00002010;
    EBISMCON = 0x00000000;      //SFR control for Static Memory
    ADDR19_TRIS = 0;
    ADDR19 = 0;
    #endif

    HSYNC_TRIS =0;
    LCD_CS_TRIS =0;
    VSYNC_TRIS =0;
    LCD_RESET_TRIS =0;

    BACKLIGHT_TRIS = 0;
    DATA_ENABLE_TRIS = 0;

    LCD_RESET = 1;
    LCD_CS    = 1;

    PIXELCLOCK_TRIS = 0;
    PIXELCLOCK = GFX_DRV_instance[0].logicShift;

    if(GFX_DRV_instance[instance].TCON_Init != NULL)
    {
        GFX_DRV_instance[instance].TCON_Init();
    }

    GFX_DRV_instance[0].activePage = 0;
    GFX_DRV_instance[0].visualPage = 0;

#if defined(LCC_EXTERNAL_MEMORY)
    /* Disable the PMP module */
    PLIB_PMP_Disable(0);

    PLIB_PMP_OperationModeSelect(0, PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT);

    /* pins polarity setting */
    PLIB_PMP_ReadWriteStrobePolaritySelect(0, PCLK_POLARITY );
    PLIB_PMP_WriteEnableStrobePolaritySelect(0, PMP_POLARITY_ACTIVE_LOW );
	
    PLIB_PMP_ReadWriteStrobePortEnable(0);
    PLIB_PMP_WriteEnableStrobePortEnable(0);

    PLIB_PMP_DataSizeSelect(0, PMP_DATA_LENGTH);

    /* wait states setting */
    PLIB_PMP_WaitStatesDataHoldSelect(0, PMP_DATA_HOLD_1);
    PLIB_PMP_WaitStatesDataSetUpSelect( 0, PMP_DATA_WAIT_ONE);
    PLIB_PMP_WaitStatesStrobeSelect(0, PMP_STROBE_WAIT_1);

    SRAM_TRIS = 0;
    #ifdef ADDR15_TRIS
    ADDR15_TRIS = 0;
    #endif
    ADDR16_TRIS = 0;
    ADDR17_TRIS = 0;
    ADDR18_TRIS = 0;

    SRAM_CS   = 0;
    ADDR17    = 0;
    ADDR18    = 0;

    /* setting the hardware for the required interrupt mode */
    PLIB_PMP_InterruptModeSelect(0, PMP_INTERRUPT_EVERY_RW_CYCLE);

    /* Ports Setting */
    PLIB_PMP_AddressPortEnable(0, PMP_ADDRESS_LINES);

    PLIB_PMP_AddressSet(0, 0);
    PLIB_PMP_AddressIncrementModeSelect(0,PMP_ADDRESS_AUTO_INCREMENT);

     /* Enable the PMP module */
    PLIB_PMP_Enable(0);
#else
    CFGEBIA = 0;               //Address Lines of EBI are not
    CFGEBIC = 0x00003313;
    EBICS0  = 0x20000000;
    EBICS1  = 0x20040000;
    EBIMSK0 = 0x00000025;
    EBIMSK1 = 0x00000125;
    EBISMT0 = 0x00001010;
    EBISMT1 = 0x00001010;
    EBISMCON = 0x00000000;      //SFR control for Static Memory

    DCH1DSA = 0x20000000; /*DMA destination address*/
#endif

    PLIB_DMA_Enable(0);

    /*Turn Backlight on*/
    #if defined(GFX_USE_DISPLAY_PANEL_TFT_G240320LTSW_118W_E)
    BACKLIGHT =0;     //Turn Backlight on
    #else
    BACKLIGHT =1;
    #endif

    // set the transfer parameters: source & destination address, source & destination size, number of bytes per event
    #ifdef LCC_INTERNAL_MEMORY
    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL, DMA_TRIGGER_TIMER_2);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL, DMA_CHANNEL_TRIGGER_TRANSFER_START);
    PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame);
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL,(1<<PMP_DATA_LENGTH));
    PLIB_DMA_ChannelXSourceSizeSet(0,DMA_CHANNEL,HBackPorch<<1);
    PLIB_DMA_ChannelXCellSizeSet(0,DMA_CHANNEL,HBackPorch<<1);

    #else //LCC_EXTERNAL_MEMORY
    // set the transfer event control: what event is to start the DMA transfer
    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL, DMA_TRIGGER_TIMER_2);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL, DMA_CHANNEL_TRIGGER_TRANSFER_START);   /*Setup DMA Trigger*/
    PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&PMDIN);
    PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[0]);
    PLIB_DMA_ChannelXSourceSizeSet(0,DMA_CHANNEL,2);
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL,HBackPorch); 
    PLIB_DMA_ChannelXCellSizeSet(0,DMA_CHANNEL, 2);
    #endif

    SYS_INT_VectorPrioritySet(INT_VECTOR_DMA1, INT_PRIORITY_LEVEL6);
 
    /* Enable the transfer done interrupt, when all buffer transferred */
    PLIB_DMA_ChannelXINTSourceEnable(0, DMA_CHANNEL, DMA_INT_BLOCK_TRANSFER_COMPLETE);

    SYS_INT_SourceEnable(INT_SOURCE_DMA_1);

    // once we configured the DMA channel we can enable it
    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL);
   
    TMR2 = 0;
    T2CONbits.TCKPS = 0;

    PR2 = 1;			//(for approximately 100 us)

    /*Unsuspend DMA Module*/
    PLIB_DMA_SuspendDisable(0);

    #if !defined(LCC_EXTERNAL_MEMORY)
    PLIB_DMA_StartTransferSet(0, DMA_CHANNEL);
    #else
    T2CONbits.TON = 1;
    #endif

    GFX_DRV_instance[0].horizontalResolution = horizontalSize;
    GFX_DRV_instance[0].verticalResolution = verticalSize;
    GFX_DRV_instance[0].ready = 1;
    GFX_DRV_instance[0].driverBusy =0;
    return (0); //Driver initialized successfully
}

#ifdef LCC_EXTERNAL_MEMORY

volatile short pixelX;
volatile GFX_COLOR pixelColor;
volatile uint16_t pixelCount = 0;
volatile uint8_t pixelUpdate = 0;

// handler for the DMA channel 1 interrupt
void __ISR(_DMA1_VECTOR) DmaHandler1()
{
  static uint8_t GraphicsState = ACTIVE_PERIOD;
  static uint16_t remaining=0;
  static uint16_t remainingPixels=0;
  static short line = 0;
  static uint32_t pixelAddress=0;
  static uint8_t prevGraphicsState = BLANKING_PERIOD;
  #if defined(USE_PIP)
  static uint16_t pipLine =0;
  #endif

       switch(GraphicsState)
       {

         case ACTIVE_PERIOD:  
           remaining = LINE_LENGTH;
           GraphicsState = BLANKING_PERIOD;

            if(line >= 0)
            {
                PMADDR = ((PMP_ADDRESS_LINES) & ((line) * LINE_LENGTH));

              if((line) == (FRAME_HEIGHT)) 
              {         
                VSYNC =0;  
                line = (-VER_BLANK);
                  #ifdef ADDR15
                  ADDR15 = 0;          //count holds the additional address line count
                  #endif
                ADDR16 = 0;
                overflowcount = 0;

                #ifdef USE_PIP
                pipLine = 0;
                #endif

               }

             else
             { 

               VSYNC =1; 
               DATA_ENABLE =1;

   #ifdef USE_PIP
               if((line >= PipStartT)&&(line <= (PipStartT + PipVLength))&&(PipVLength != 0))
               {    
                     overflowcount = ((line) * LINE_LENGTH)/PMADDR_OVERFLOW; 
                     remaining = PipStartL;
                     GraphicsState = PIP;

                if(!PipStartL)
                {
       case PIP:     //Draw PIP Line      
                  ADDR17= _GFXPIPPage;
                  ADDR18= _GFXPIPPage>>1;
 
                  pixelAddress = (uint32_t)(((PipY+pipLine++)*(DISP_HOR_RESOLUTION))+(PipX));

                  PLIB_PMP_AddressSet(0, (pixelAddress&(PMP_ADDRESS_LINES)));

                  overflowcount = pixelAddress/PMADDR_OVERFLOW;
                  remaining = PipHLength;

                  remainingPixels = LINE_LENGTH-PipHLength-PipStartL;
                  pixelAddress = ((line*LINE_LENGTH)+PipHLength+PipStartL);
 
                  GraphicsState = FINISH_LINE;
                 }

                  #ifdef ADDR15_TRIS
                  ADDR15 = overflowcount;          //count holds the additional address line count
                  ADDR16 = (overflowcount>>1);
                  #else
                  ADDR16 = overflowcount;
                  #endif
                 }
  #endif
  #ifdef USE_LCC_SCROLLING
              if(scroll >0)
              {   
                 switch(scroll)
                 {
                  case 1:             //Up
                  case 2:             //Down
                   if(line < scrollLine)
                   {
                   pixelAddress = ((GFX_DRV_instance[0].verticalResolution-1)-(scrollLine-line)) * LINE_LENGTH;
                   ADDR17 = GFX_DRV_instance[0].visualPage;
                   ADDR18 = GFX_DRV_instance[0].visualPage>>1;
                   }
                   else
                   {
                   pixelAddress = (line-scrollLine) * LINE_LENGTH;
                   ADDR17 = scrollPage;
                    ADDR18 = scrollPage>>1;
                   }

                   PLIB_PMP_AddressSet(0,(pixelAddress)&(PMP_ADDRESS_LINES));
                   overflowcount = pixelAddress/PMADDR_OVERFLOW;
                   break;   

                  case 3://Left
                  case 4://Right
                   pixelAddress = ((line+1) * LINE_LENGTH) + ((GFX_DRV_instance[0].horizontalResolution-1)-scrollLine);
                   
                   PLIB_PMP_AddressSet(0, (pixelAddress)&(PMP_ADDRESS_LINES));
                   overflowcount = pixelAddress/PMADDR_OVERFLOW;

                  if(scroll == 3)
                  {
                       ADDR17 = GFX_DRV_instance[0].visualPage;
                       ADDR18 = GFX_DRV_instance[0].visualPage>>1;
                  }
                  else
                  {
                       ADDR17 = scrollPage;
                       ADDR18 = scrollPage>>1;
                  }
                   remaining = scrollLine;
                   remainingPixels = LINE_LENGTH - scrollLine;
                   pixelAddress = (line) * LINE_LENGTH;
                   GraphicsState = FINISH_LINE;
                   break; 
                   } 

                  if((scroll>2) && (GraphicsState != FINISH_LINE))
                  {
case FINISH_LINE:            //Finish Line Render
                   remaining = remainingPixels;
                   
                   PLIB_PMP_AddressSet(0, (pixelAddress)&(PMP_ADDRESS_LINES));
                   overflowcount = pixelAddress/PMADDR_OVERFLOW;

                  if(scroll == 3)
                  {
                   ADDR17 = scrollPage;
                   ADDR18 = scrollPage>>1;
                  }
                  else
                  {
                   ADDR17 = GFX_DRV_instance[0].visualPage;
                   ADDR18 = GFX_DRV_instance[0].visualPage>>1;
                  }
 
                   GraphicsState = BLANKING_PERIOD;
                  }

                  #ifdef ADDR15_TRIS
                  ADDR15 = overflowcount;          //count holds the additional address line count
                  ADDR16 = (overflowcount>>1);
                  #else
                  ADDR16 = overflowcount;
                  #endif
              }
 #endif
              prevGraphicsState = GraphicsState;

               if((PMADDR_OVERFLOW - PMADDR) < (remaining))       
               {   
                    GraphicsState = OVERFLOW;      //Do Overflow routine
                    DCH1DSIZ =  (uint16_t)(((PMADDR_OVERFLOW)- PMADDR)<<1);
                    remaining = remaining - ((PMADDR_OVERFLOW)- PMADDR);
                    break;
               }           
              }
              }  

            //Setup DMA Transfer
            DCH1DSIZ =  (uint16_t)(remaining<<1);
            break;

       case OVERFLOW:                    //Adjust the address lines that aren't part of PMP
             GraphicsState = prevGraphicsState;     //goto Front Porch
             //Setup DMA Transfer
             DCH1DSIZ =  (uint16_t)(remaining<<1);
                  #ifdef ADDR15_TRIS
                  ADDR15 = ++overflowcount;          //count holds the additional address line count
                  ADDR16 = (overflowcount>>1);
                  #else
                  ADDR16 = ++overflowcount;
                  #endif
             break;

        case BLANKING_PERIOD:   //Front Porch then Back Porch Start 
           HSYNC = 0; 
           DATA_ENABLE = 0; 
           PLIB_PMP_MasterReceive(0);
           HSYNC = 1;

            //Setup DMA Back Porch
            DCH1DSIZ =  HBackPorch<<1;
            GraphicsState = ACTIVE_PERIOD;   
            line++;      
           break;

   default: 
           break;
}

    DrawCount = 0;
    PLIB_DMA_ChannelXINTSourceFlagClear(0, DMA_CHANNEL, DMA_INT_BLOCK_TRANSFER_COMPLETE);
    SYS_INT_SourceStatusClear(INT_SOURCE_DMA_1);
    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL);
}
#endif
  
#ifdef LCC_INTERNAL_MEMORY
void __ISR( _DMA1_VECTOR) DmaHandler1(void)
{

  static uint8_t GraphicsState = ACTIVE_PERIOD;
  static uint16_t remaining = 0;
  static uint16_t remainingPixels=0;
  static short line = 0;
  static uint32_t pixelAddress=0;
  static uint16_t scrollPos,scrollState;
  static uint32_t* EBIStart = (uint32_t*)(SRAM_ADDR_CS0+4);

  #if defined(USE_PIP)
  static uint16_t pipLine =0;
  #endif

    switch(GraphicsState)
    {
        case ACTIVE_PERIOD:
            remaining = DISP_HOR_RESOLUTION<<1;
            GraphicsState = BLANKING_PERIOD;

           if(line >= 0)
           { 
            PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[GFX_DRV_instance[0].visualPage][line][0]);

            if(line == (DISP_VER_RESOLUTION))
            {
                 VSYNC = 0;
                 line = -(VER_BLANK);

                #ifdef USE_PIP
                pipLine = 0;
                #endif

                #ifdef USE_LCC_SCROLLING
                scrollState = scroll;
                scrollPos = scrollLine;
                #endif
            }
            else
            {
                 VSYNC = 1;
                 DATA_ENABLE = 1;

            #ifdef USE_PIP
               if(((line) >= PipStartT)&&((line) <= (PipStartT + PipVLength))&&(PipVLength != 0))
               {

                   remaining = PipStartL;
                   GraphicsState = PIP;

                if(!PipStartL) //Draw PIP Line
                {
case PIP:
                   PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[_GFXPIPPage][(PipY+pipLine)][PipX]);
                   pipLine++;

                  remaining = PipHLength;
                  remainingPixels = (DISP_HOR_RESOLUTION)-PipHLength-PipStartL;
                  pixelAddress = PipHLength-PipStartL;

                  GraphicsState = FINISH_LINE;
                 }

                }
            #endif
  #ifdef USE_LCC_SCROLLING
              if(scrollState >0)
              {
                 switch(scroll)
                 {
                  case 1:             //Up
                  case 2:             //Down
                   if((line) < scrollPos)
                   {
                   pixelAddress = (DISP_VER_RESOLUTION-1)-(scrollPos-(line));
                   PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[GFX_DRV_instance[0].visualPage][pixelAddress][0]);
                   }
                   else
                   {
                   pixelAddress = ((line)-scrollPos);
                   PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[scrollPage][pixelAddress][0]);
                   }
                   break;

                  case 3://Left
                  case 4://Right
                   remainingPixels = (DISP_HOR_RESOLUTION-1)-scrollPos;
                   pixelAddress = (line+1);

                  if(scroll == 3)
                  {
                       PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[GFX_DRV_instance[0].visualPage][pixelAddress][remainingPixels]);
                  }
                  else
                  {
                       PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[scrollPage][pixelAddress][remainingPixels]);
                  }

                   remaining = scrollPos;
                   remainingPixels = (DISP_HOR_RESOLUTION - scrollLine);
                   pixelAddress = 0;
                   GraphicsState = FINISH_LINE;
                   }
                    
                  if((scroll>2) && (GraphicsState != FINISH_LINE))
                  {
case FINISH_LINE:       //Finish Line Render

                   if(scroll == 3)
                   {
                       PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[scrollPage][line][pixelAddress]);
                   }
                   else
                   {
                       PLIB_DMA_ChannelXSourceStartAddressSet(0,DMA_CHANNEL, (uint32_t)&GraphicsFrame[GFX_DRV_instance[0].visualPage][line][pixelAddress]);
                   }
                   remaining = remainingPixels;
                   GraphicsState = BLANKING_PERIOD;
                    }
        }
 #endif
           }
           }

            PLIB_DMA_ChannelXSourceSizeSet(0,DMA_CHANNEL,remaining);
            #if defined(__PIC32MZ__)
            DCH1CSIZ = remaining;
            #endif          
    break;
            
    case BLANKING_PERIOD:
         
           HSYNC =0; 
           DATA_ENABLE =0;

            #if defined(__PIC32MZ__)
           *EBIStart = 2;
            #else
           PMDINSET = 1;
           while(PMMODEbits.BUSY == 1);
           #endif

           HSYNC = 1;
           DCH1SSIZ = HBackPorch<<1;
           GraphicsState = ACTIVE_PERIOD;
           line++;
           PLIB_DMA_ChannelXINTSourceFlagClear(0, DMA_CHANNEL, DMA_INT_BLOCK_TRANSFER_COMPLETE);
           SYS_INT_SourceStatusClear(INT_SOURCE_DMA_1);
           DCH1CONSET = 0x80;
           #if defined(__PIC32MZ__)
           DCH1CSIZ = DCH1SSIZ;
           DCH1ECONbits.CFORCE = 1;          /* force DMA transfer 7*/
           #endif
           return;
    }

    PLIB_DMA_ChannelXINTSourceFlagClear(0, DMA_CHANNEL, DMA_INT_BLOCK_TRANSFER_COMPLETE);

    SYS_INT_SourceStatusClear(INT_SOURCE_DMA_1);

    DCH1CONbits.CHEN = 1;
    #if defined(__PIC32MZ__)
    DCH1ECONbits.CFORCE = 1;          /* force DMA transfer 7*/
    #endif
}
#endif

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
    1 - call not successful (lcc driver busy)
    0 - call successful
*/
uint16_t GFX_DRV_lcc_PixelPut(short x, short y)
{

    #if (DISP_ORIENTATION == 270)
    uint16_t tempx=x;
    x = (DISP_HOR_RESOLUTION-1) - y;
    y = tempx; 
    #elif (DISP_ORIENTATION == 90)
    uint16_t tempy=y;
    y = (DISP_VER_RESOLUTION-1) - x;
    x = tempy; 
    #elif (DISP_ORIENTATION == 180)
    x = (DISP_HOR_RESOLUTION-1) - x;
    y = (DISP_VER_RESOLUTION-1) - y;
    #endif

    #ifdef LCC_INTERNAL_MEMORY
    GFX_COLOR *point = (GFX_COLOR*)KVA0_TO_KVA1(&GraphicsFrame[GFX_DRV_instance[0].activePage][y][x]);
    *point = GFX_DRV_instance[0].color;
    #else

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
     return (1); //queue is full
    }

    lccdriverBusy = 1;

    lccqueueCount++;
     
     lccqueueIndex->task = PUT_PIXELS;
     lccqueueIndex->address.Val = (uint32_t)(((y)*(DISP_HOR_RESOLUTION))+(x));
     lccqueueIndex->data = GFX_DRV_instance[0].color;
     lccqueueIndex->count = 1;
     lccqueueIndex->lineCount = 1;

      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      } 

     lccdriverBusy = 0;
     #endif
     return(0);

}  

// *****************************************************************************
/*
  Function: uint16_t GFX_DRV_lcc_PixelsPut(short x, short y, uint16_t count)

  Summary:
    outputs one pixel into the frame buffer at the x,y coordinate given

  Description:
    none

  Input:
        instance - driver instance
        color - color to output
        x,y - pixel coordinates

  Output:
          1 - call not successful (lcc driver busy)
          0 - call successful
*/
uint16_t  GFX_DRV_lcc_PixelsPut(short x, short y, uint16_t count, uint16_t lineCount)
{

    #ifdef LCC_INTERNAL_MEMORY
       static GFX_COLOR *point;
       uint16_t tempy = y;
       uint16_t tempx = x;
       uint16_t tempCount = count;

    while(lineCount--)
    {
       #if (DISP_ORIENTATION == 270)
       x = (DISP_HOR_RESOLUTION-1) - tempy;
       y = tempx;
       #elif (DISP_ORIENTATION == 90)
       y = (DISP_VER_RESOLUTION-1) - tempx;
       x = tempy;
       #elif (DISP_ORIENTATION == 180)
       x = (DISP_HOR_RESOLUTION-1) - tempx;
       y = (DISP_VER_RESOLUTION-1) - tempy;
       #else
       x = tempx;
       y = tempy;
       #endif

      point = (GFX_COLOR*)KVA0_TO_KVA1(&GraphicsFrame[GFX_DRV_instance[0].activePage][y][x]);

    while(tempCount--)
    {
        *point = GFX_DRV_instance[0].color;
         #if (DISP_ORIENTATION	== 90)
         point -= DISP_HOR_RESOLTUION;
         #elif (DISP_ORIENTATION == 270)
         point += DISP_HOR_RESOLUTION;
         #elif (DISP_ORIENTATION == 180)
         point--;
         #else
         point++;
         #endif
    }
      tempCount = count;
      tempy++;
    }
    #else

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
     return (1); //queue is full
    }

       #if (DISP_ORIENTATION == 270)
       #elif (DISP_ORIENTATION == 90)
       uint16_t hchange = count;
       uint16_t vchange = lineCount;
       uint16_t tempy = y;
       y = (DISP_VER_RESOLUTION) - (x+count);
       x = tempy;
       lineCount = hchange;
       count = vchange;
       #elif (DISP_ORIENTATION == 180)
       #endif
     lccdriverBusy = 1;
     lccqueueCount++;
     
     lccqueueIndex->task = PUT_PIXELS;
     lccqueueIndex->address.Val = (uint32_t)(((y)*(DISP_HOR_RESOLUTION))+(x));
     lccqueueIndex->data = GFX_DRV_instance[0].color;
     lccqueueIndex->count = count;
     lccqueueIndex->lineCount = lineCount;

      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      } 
     lccdriverBusy = 0;
     #endif
     return(0);

}  

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
         handle to the number of pixels remaining
*/
uint16_t*  GFX_DRV_lcc_PixelArrayPut(uint16_t *color, short x, short y, uint16_t count, uint16_t lineCount)
{

    #ifdef LCC_INTERNAL_MEMORY

       uint16_t tempy = y;
       uint16_t tempx = x;
       uint16_t tempCount = count;
       GFX_COLOR *point;

    while(lineCount--)
    {
       #if (DISP_ORIENTATION == 270)
       x = (DISP_HOR_RESOLUTION-1) - tempy;
       y = tempx;
       #elif (DISP_ORIENTATION == 90)
       y = (DISP_VER_RESOLUTION-1) - tempx;
       x = tempy;
       #elif (DISP_ORIENTATION == 180)
       x = (DISP_HOR_RESOLUTION-1) - tempx;
       y = (DISP_VER_RESOLUTION-1) - tempy;
       #else
       x = tempx;
       y = tempy;
       #endif

       point = (GFX_COLOR*)KVA0_TO_KVA1(&GraphicsFrame[GFX_DRV_instance[0].activePage][y][x]);

    while(tempCount--)
    {

         *point = *color++;

         #if (DISP_ORIENTATION	== 90)
         point -= DISP_HOR_RESOLTUION;
         #elif (DISP_ORIENTATION == 270)
         point += DISP_HOR_RESOLUTION;
         #elif (DISP_ORIENTATION == 180)
         point--;
         #else
         point++;
         #endif
    }
       
      tempCount = count;
      tempy++;     
    }
    lccqueueIndex->count = 0;
    return(&lccqueueIndex->count);
    #else

    static uint16_t  *index1;

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
     return (NULL); //queue is full
    }

       #if (DISP_ORIENTATION == 270)
       #elif (DISP_ORIENTATION == 90)
       uint16_t hchange = count;
       uint16_t tempy = y;
       y = (DISP_VER_RESOLUTION-2) - (x);
       x = tempy;
       count = lineCount;
       lineCount = hchange;
       #elif (DISP_ORIENTATION == 180)
       #endif
     lccdriverBusy = 1;
     lccqueueCount++;
     
     lccqueueIndex->instance = 0;
     lccqueueIndex->task = PUT_ARRAY;
     lccqueueIndex->address.Val = (uint32_t)(((y)*(DISP_HOR_RESOLUTION))+(x));
     lccqueueIndex->array = color;   //Starting address of the array
     lccqueueIndex->count = count;
     lccqueueIndex->lineCount = lineCount;

     index1 = (uint16_t*)&lccqueueIndex->count;

      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      }
     lccdriverBusy = 0;
     return(index1);
     #endif
} 

// *****************************************************************************
/*
  Function: uint16_t*  GFX_DRV_lcc_PixelArrayGet(uint16_t *color, short x, short y, uint16_t count)

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
uint16_t*  GFX_DRV_lcc_PixelArrayGet(uint16_t *color, short x, short y, uint16_t count)
{

    #if (DISP_ORIENTATION == 270)
    uint16_t tempx = x;
    x = (DISP_HOR_RESOLUTION-1) - y;
    y = tempx; 
    #elif (DISP_ORIENTATION == 90)
    uint16_t tempy = y;
    y = (DISP_VER_RESOLUTION-1) - x;
    x = tempy; 
    #elif (DISP_ORIENTATION == 180)
    x = (DISP_HOR_RESOLUTION-1) - x;
    y = (DISP_VER_RESOLUTION-1) - y;
    #endif

    #ifdef LCC_INTERNAL_MEMORY

    GFX_COLOR *point = (uint16_t*)KVA0_TO_KVA1(&GraphicsFrame[GFX_DRV_instance[0].activePage][y][x]);

    while(count--)
    {
         *color = *point;
         color++;
         #if (DISP_ORIENTATION	== 90)
         point -= DISP_HOR_RESOLUTION;
         #elif (DISP_ORIENTATION == 270)
         point += DISP_HOR_RESOLUTION;
         #elif (DISP_ORIENTATION == 180)
         point--;
         #else
         point++;
         #endif
    }
    return(&lccqueueIndex->count);
    #else

    static uint16_t  *qindex;

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
     return (NULL); //queue is full
    }
     lccdriverBusy = 1;
     lccqueueCount++;
     
     lccqueueIndex->instance = 0;
     lccqueueIndex->task = GET_PIXELS;
     lccqueueIndex->address.Val =  (uint32_t)(((y)*(DISP_HOR_RESOLUTION))+(x));
     lccqueueIndex->array = color;   //Starting address of the array
     lccqueueIndex->count = count;

     qindex = (uint16_t*)&lccqueueIndex->count;      //Inrement the queue pointer and index the value in case we are interrupted


      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      }
     lccdriverBusy = 0;
     return(qindex);
     #endif
} 

// *****************************************************************************
/*
  Function:
	void GFX_DRV_lcc_Tasks(void)

  Summary:
	Task machine that renders the driver calls for the graphics library
    it must be called peridically to output the contents of its circular buffer
*/
//
void GFX_DRV_lcc_Tasks(void)
{

   static uint16_t count;

   if(lccdriverBusy == 1)
        return;

   while(lccqueueCount != 0)
   {

        switch(taskIndex->task)  //State Machine for Putpixel ONLY
        {

            case INITIALIZE: 
                if(GFX_DRV_lcc_Initialize(0) == 1)  //Call until the driver is initialized
                    return;
        
                GFX_DRV_instance[0].driverBusy = 0;
                GFX_DRV_instance[0].ready = 1;
                break;
        #if defined (LCC_EXTERNAL_MEMORY)
            case PUT_PIXELS:
                taskIndex->task = WAIT_TRANSMIT_PIXELS;
                count = taskIndex->count;

                while(taskIndex->lineCount)
                {
                     taskIndex->count = count;
                     
                    while(taskIndex->count)
                    {
                        /*Suspend DMA Trigger*/
                        BlockingUpdate();

                        taskIndex->count--;
                        taskIndex->address.Val++;
                    }
                   
                    taskIndex->address.Val += (DISP_HOR_RESOLUTION - count);
                    taskIndex->lineCount--;
                }
                break;

            case PUT_ARRAY:

                taskIndex->task = WAIT_TRANSMIT_ARRAY;
                count = taskIndex->count;

                while(taskIndex->lineCount)
                {
                    taskIndex->count = count;

                    while(taskIndex->count)
                    {  
                        /*Suspend DMA Trigger*/
                        BlockingUpdate();

                        taskIndex->count--;
                        taskIndex->address.Val++;     
                    }
                   
                    taskIndex->address.Val += (DISP_HOR_RESOLUTION - count);
                    taskIndex->lineCount--;
                }
                taskIndex->array = NULL;
                break;
        
            case PAGE:
              lccTaskActive = 1;
              GFX_DRV_lcc_SetPage(taskIndex->data,taskIndex->count);
              lccTaskActive = 0;
              break;
        
            case LAYERS:
              lccTaskActive = 1;
              GFX_DRV_lcc_Layer(0,(GFX_LAYER_PARAMS*)taskIndex->array);
              lccTaskActive = 0;
              break;
        
            case GET_PIXELS:
              taskIndex->task = WAIT_RECEIVE;
        
              while(taskIndex->count)
              {     
                /*Suspend DMA Trigger*/
                BlockingUpdate();
                
                taskIndex->array++;
                taskIndex->count--;
                taskIndex->address.Val++; 
              }
              taskIndex->array = NULL;
              break;
        #endif
            default: //Do nothing
            break;
           }
        taskIndex->count = 0;
        lccqueueCount--;      //Subtract 1 from the queue count

        if(taskIndex++ == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
        {
            taskIndex = &lcccommandBuffer[0];     
        }
    }
}

uint16_t* GFX_DRV_lcc_Layer(uint8_t instance, GFX_LAYER_PARAMS* layer)
{
#ifdef USE_PIP
   static uint16_t* LayerIndex = NULL;

    if(lccTaskActive)
    {

    _GFXPIPPage = layer->page;

   if(layer->on == 0)
   {    
       PipVLength = 0;
       return((uint16_t*)&lccqueueIndex->count);
   }

   #if (DISP_ORIENTATION == 90)
     PipStartL = (layer->top);
     PipStartT = (DISP_VER_RESOLUTION-1)-(layer->left + layer->width);
     PipVLength = layer->width;
     PipHLength = layer->height;
     PipY = (DISP_VER_RESOLUTION-1) - (layer->layerLeft+layer->width);
     PipX = (layer->layerTop);
   #elif (DISP_ORIENTATION == 0) 
    PipStartT = layer->top;
    PipStartL = layer->left;
    PipVLength = layer->height;
    PipHLength = layer->width;
    PipX = layer->layerLeft;
    PipY = layer->layerTop;
   #endif
   return((uint16_t*)&lccqueueIndex->count);
   }

    if(lccqueueCount >= (GFX_DRV_lcc_COMMANDQUEUESIZE-1)) 
    {
        return (NULL); //queue is full
    }
    lccdriverBusy = 1;
    lccqueueCount++;
     
     lccqueueIndex->task = LAYERS;
     lccqueueIndex->instance = 0;
     lccqueueIndex->array = (uint16_t*)layer; 
     lccqueueIndex->count = 1;
     LayerIndex = (uint16_t*)&lccqueueIndex->count;
 
      if(lccqueueIndex == &lcccommandBuffer[GFX_DRV_lcc_COMMANDQUEUESIZE-1])
      {
          lccqueueIndex = &lcccommandBuffer[0];
      }
      else
      {
          lccqueueIndex++;
      } 
     lccdriverBusy = 0;
     return(LayerIndex);
#endif
}

#if defined (LCC_EXTERNAL_MEMORY)

void __attribute__((always_inline)) BlockingUpdate(void)
{
  static uint16_t prevaddr;
  uint16_t* point = (uint16_t*)0xE0000000;
  
  while(DrawCount > PIXEL_DRAW_PER_DMA_TX);
 
  T2CONCLR = 0x8000; //Turn back off the DMA Trigger
  while(PMMODEbits.BUSY == 1); //WAIT for DMA transfer to be suspended

  switch(taskIndex->task)
  {

    case WAIT_TRANSMIT_PIXELS:
         ADDR17 = GFX_DRV_instance[0].activePage;
         ADDR18 = GFX_DRV_instance[0].activePage>>1;
        
        #if !defined(__PIC32MZ__)
        //Perform Write
        #if defined(ADDR15)
        ADDR15 = taskIndex->address.bits.b15;
        #endif
        ADDR16 = taskIndex->address.bits.b16;
        
        //Save previous address value
        prevaddr = PMADDR;

        PLIB_PMP_AddressSet(0, taskIndex->address.Val);       
     
        if((taskIndex->count > 8) && (PMADDR < 32500)) //Write 8 pixels at once
        {
            PMDIN = taskIndex->data;while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; while(PMMODEbits.BUSY==1);
            PMDINSET = 0; 
            taskIndex->count -= 7;
            taskIndex->address.Val += 7;
        }
        else
        {
           PMDIN = taskIndex->data;//PLIB_PMP_MasterSend(0, taskIndex->data);
        }
        while(PMMODEbits.BUSY==1);
        break;
        #else
        CFGEBIA = 0x0001ffff;
        CFGEBIC = 0x00002003;
        point += (taskIndex->address.Val);

        if(taskIndex->count > 8) //Write 8 pixels at once
        {
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        *point++ = taskIndex->data;
        taskIndex->count -= 7;
        taskIndex->address.Val += 7;
        }

        *point = taskIndex->data;
        break;
        #endif

    case WAIT_TRANSMIT_ARRAY:
         ADDR17 = GFX_DRV_instance[0].activePage;
         ADDR18 = GFX_DRV_instance[0].activePage>>1;

        #if !defined(__PIC32MZ__)
        //Perform Write
        #if defined(ADDR15)
        ADDR15 = taskIndex->address.bits.b15;
        #endif
        ADDR16 = taskIndex->address.bits.b16;

        //Save previous address value
        prevaddr = PMADDR;
        PLIB_PMP_AddressSet(0, taskIndex->address.Val);
        PLIB_PMP_MasterSend(0, *taskIndex->array);
        taskIndex->array++;
        while(PMMODEbits.BUSY ==1);
        break;
        #else
        CFGEBIA = 0x0001ffff;
        CFGEBIC = 0x00002003;
        point += (taskIndex->address.Val);

        if(taskIndex->count > 8) //Write 8 pixels at once
        {
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        *point++ = *taskIndex->array++;
        taskIndex->count -= 7;
        taskIndex->address.Val += 7;
        }

        *point = *taskIndex->array++;      
        break;
        #endif

    case WAIT_RECEIVE:
        ADDR17 = GFX_DRV_instance[0].activePage;
        ADDR18 = GFX_DRV_instance[0].activePage>>1;
        #if !defined(__PIC32MZ__)
        //Perform Write
        #if defined(ADDR15)
        ADDR15 = taskIndex->address.bits.b15;
        #endif
        ADDR16 = taskIndex->address.bits.b16;

        //Save previous address value
        prevaddr = PMADDR;
    
        PLIB_PMP_ReadWriteStrobePortDisable(0);

        PLIB_PMP_AddressSet(0,(uint16_t)(taskIndex->address.Val));

        *taskIndex->array = PMDIN;
        while(PMMODEbits.BUSY ==1);
        *taskIndex->array = PMDIN;

        PLIB_PMP_ReadWriteStrobePortEnable(0);
        break;
    #else
        CFGEBIA = 0x0001ffff;
        CFGEBIC = 0x00000003;
        point += (taskIndex->address.Val);

     //   if(taskIndex->count > 8) //Write 8 pixels at once
     //   {
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       *taskIndex->array++ = *point++;
     //       taskIndex->count -= 7;
     //       taskIndex->address.Val += 7;
     //   }
        *taskIndex->array = *point;
    #endif
   }

        #if !defined(__PIC32MZ__)
        //Clean-up Address Lines
        #if defined(ADDR15)
        ADDR15 = overflowcount;          //count holds the additional address line count
        ADDR16 = (overflowcount>>1);
        #else
        ADDR16 = overflowcount;
        #endif
        PMADDR = prevaddr;
        #else
        CFGEBIA = 0;
        CFGEBIC = 0;
        #endif

        ADDR17 = GFX_DRV_instance[0].visualPage;
        ADDR18 = GFX_DRV_instance[0].visualPage>>1;
 
        DCH1ECONSET = 0x80; //Force a DMA tx
        T2CONSET = 0x8000;
        DrawCount++;
        return; //end of putpixel
}

#endif // LCC_EXTERNAL_MEMORY
