/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       AppNotesDemo.c
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright (c) 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
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
 *
 * Date         Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 03/17/11	    ...
 *****************************************************************************/
#include "gfx/gfx.h"
#include "gfx/src/common_legacy/SST25VF016.h"
#include "gfx/src/common_legacy/TouchScreen.h"
#include "AlphaBlendScreen.h"
#include "JPEGImage.h"
#include "InternalResources.h"
#include "driver/gfx/gfx_lcc/drv_gfx_lcc.h"
#include "gfx/gfx_colors_template.h"

#define DIVISOR 1

uint8_t handle = 0xff;

/////////////////////////////////////////////////////////////////////////////
//                            DEMO STATES
/////////////////////////////////////////////////////////////////////////////
typedef enum
{
    CREATE_MAINMENU = 0,
    DISPLAY_MAINMENU,
    CREATE_ALPHABLEND,
    DISPLAY_ALPHABLEND,
    #if defined (MEB_2_BOARD)
    CREATE_MULTITOUCH,
    DISPLAY_MULTITOUCH
    #endif
} SCREEN_STATES;

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define ID_ICON1 		    0xF010
#define ID_ICON2 		    0xF011
#define ID_ICON3 		    0xF012
#define ID_ICON4 		    0xF013
#define ID_SCROLL1 		    0xF014
#define ID_SCROLL2 		    0xF015
#define ID_SCROLL3 		    0xF016
#define ID_SCROLL4 		    0xF017
#define ID_BACK                     0xF050

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT DIMENSIONS
/////////////////////////////////////////////////////////////////////////////
#define ICON_WIDTH          (72)
#define ICON_HEIGHT         (62)
#define ICON_COLUMNSNUM     (2)
#define ICON_ROWSNUM        (2)
#define ICON_XINDENT        ((GFX_MaxXGet() - ICON_COLUMNSNUM * ICON_WIDTH) / (ICON_COLUMNSNUM + 1))
#define ICON_YINDENT        (((GFX_MaxYGet() - ICON_ROWSNUM * ICON_HEIGHT) / (ICON_ROWSNUM + 1))- 3)
#define IconTop(row)        (((row + 1) * ICON_YINDENT) + (row * ICON_HEIGHT))
#define IconBottom(row)     ((row + 1) * (ICON_YINDENT + ICON_HEIGHT))
#define IconLeft(column)    (((column + 1) * ICON_XINDENT) + (column * ICON_WIDTH))
#define IconRight(column)   ((column + 1) * (ICON_XINDENT + ICON_WIDTH))

/////////////////////////////////////////////////////////////////////////////
//                            FONTS USED
/////////////////////////////////////////////////////////////////////////////
extern const FONT_FLASH     GOLFontDefault; // default GOL font
extern const FONT_FLASH     Gentium;

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void            TickInit(void);            // starts tick counter         
WORD            CreateMainMenu();
WORD            CreateBackButton();
void            SpeedDemo(void);
void            PIPDemo(void);
void            PagingDemo(void);
void            ScrollScreen(BYTE direction, WORD delay);

volatile DWORD  tick = 0;             // tick counter,

/////////////////////////////////////////////////////////////////////////////
//                            IMAGES USED
/////////////////////////////////////////////////////////////////////////////
// see InternalResources.h

/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
GFX_GOL_SCHEME      *demoScheme;                // alternative style scheme
GFX_GOL_SCHEME      *AlphaScheme;                // alternative style scheme
IMAGE_FLASH     *pIconPressed  = (void*) &MCHPFolderFile;
IMAGE_FLASH     *pIconReleased = (void*) &MCHPFolderEmpty;

// current state of main demo state mashine
SCREEN_STATES   screenState = CREATE_MAINMENU;


XCHAR Labels[4][11] = {
                       {'M','u','l','t','i','T','o','u','c','h',0},
                       {'S','p','e','e','d',0},
                       {'A','l','p','h','a','B','l','e','n','d',0},
                       {'P','a','g','i','n','g',0},
                     };

XCHAR Scroll[4][3] = { {'<',0},
                       {'/',0x5c,0},
                       {'>',0},
                       {0x5c,'/',0},
                     };

XCHAR MainMenuStr[5] = {'M','A','I','N',0};

XCHAR PCAP[] = {'P','r','e','s','s',' ','W','i','t','h',' ','1','-','3',' ','f','i','n','g','e','r','s',
                     ' ','t','o',' ','m','a','k','e',' ','s','h','a','p','e','s',0};


void APP_Initialize ( void )
{

    demoScheme = GFX_GOL_SchemeCreate();  // create alternative style scheme
    AlphaScheme = GFX_GOL_SchemeCreate();  // create alternative style scheme

    demoScheme->TextColor0 = BRIGHTBLUE();
    demoScheme->TextColor1 = BRIGHTRED();
    demoScheme->pFont = (void*)&Gentium;

    AlphaScheme->Color0 = RGBConvert(0x4C, 0x8E, 0xFF);
    AlphaScheme->Color1 = RGBConvert(255, 102, 0);
    AlphaScheme->EmbossDkColor = RGBConvert(0x1E, 0x00, 0xE5);
    AlphaScheme->EmbossLtColor = RGBConvert(0xA9, 0xDB, 0xEF);
    AlphaScheme->ColorDisabled = RGBConvert(0xD4, 0xE1, 0xF7);
    AlphaScheme->TextColor1 = BRIGHTBLUE();
    AlphaScheme->TextColor0 = RGBConvert(255, 102, 0);
    AlphaScheme->TextColorDisabled = RGBConvert(0xB8, 0xB9, 0xBC);
    AlphaScheme->AlphaValue = 50;
    
    GFX_ColorSet(WHITE());

    while(GFX_ScreenClear() == NULL);

    while(GFX_DoubleBufferEnable(1) == NULL);
    while(GFX_DoubleBufferEnable(0) == NULL);

}

/* */
void APP_Tasks(void)
{

    static GFX_GOL_MESSAGE msg;

       GFX_GOL_Draw();

}

/////////////////////////////////////////////////////////////////////////////
// Function: WORD CreateBackButton()
// Input: none
// Output: Returns 0 if the screen is created and 0 if not.
// Overview: Creates the four icons to launch each of the application 
//           note demos.
/////////////////////////////////////////////////////////////////////////////
WORD CreateBackButton()
{
    GFX_GOL_BUTTON *pObj;

    pObj = GFX_GOL_ButtonCreate (
                        ID_BACK,
                        10>>DIVISOR, 5>>DIVISOR,
                        80>>DIVISOR, 45>>DIVISOR, 0,
                        GFX_GOL_BUTTON_DRAW,
                        NULL,
                        MainMenuStr,  
                        demoScheme
                     );
                     
    if(pObj == NULL)
        return (0);        
        
    return 1;
    
}    

/////////////////////////////////////////////////////////////////////////////
// Function: WORD CreateMainMenu()
// Input: none
// Output: Returns 0 if the screen is created and 0 if not.
// Overview: Creates the four icons to launch each of the application 
//           note demos.
/////////////////////////////////////////////////////////////////////////////
WORD CreateMainMenu()
{

     while(GFX_DoubleBufferEnable(1) == NULL);

    int i;
    SHORT left = 0, top = 0, right = 0, bottom = 0;

            GFX_GOL_ButtonCreate (
                        ID_SCROLL1,     // object�s ID
                        0, 32>>DIVISOR,
                        32>>DIVISOR, (GFX_MaxYGet()-(32>>DIVISOR)),
                        0,              
                        GFX_GOL_BUTTON_DRAW,
                        NULL,  // use this bitmap 
                        Scroll[0],      // use this text
                        demoScheme);      // use alternative style scheme
            GFX_GOL_ButtonCreate (
                        ID_SCROLL2,     // object�s ID
                        0, 0,
                        GFX_MaxXGet(), 32>>DIVISOR,
                        0,              
                        GFX_GOL_BUTTON_DRAW,
                        NULL,  // use this bitmap 
                        Scroll[1],      // use this text
                        demoScheme);      // use alternative style scheme
            GFX_GOL_ButtonCreate (
                        ID_SCROLL3,     // object�s ID
                        (GFX_MaxXGet()-(32>>DIVISOR)), 32>>DIVISOR,
                        GFX_MaxXGet(), (GFX_MaxYGet()-(32>>DIVISOR)),
                        0,              // radius if rounded edge
                        // draw the object after creation with
                        // text drawn at the bottom and no panel
                        GFX_GOL_BUTTON_DRAW,
                        NULL,  // use this bitmap 
                        Scroll[2],      // use this text
                        demoScheme);      // use alternative style scheme
             GFX_GOL_ButtonCreate(
                        ID_SCROLL4,     // object�s ID
                        0, (GFX_MaxYGet()-(32>>1)),
                        GFX_MaxXGet(), GFX_MaxYGet(),
                        0,
                        GFX_GOL_BUTTON_DRAW,
                        NULL,  // use this bitmap 
                        Scroll[3],      // use this text
                        demoScheme);      // use alternative style scheme

    // loop to create the four icons
    for (i=0; i<4; i++)
    {
        switch (i)
        {
            case 0:
                top    = IconTop(0)+5;
                bottom = IconBottom(0)+5;
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 1:
                top    = IconTop(0)+5;
                bottom = IconBottom(0)+5;
                left   = IconLeft(1);
                right  = IconRight(1);      
                break;
            case 2:
                top    = IconTop(1)-2;
                bottom = IconBottom(1)-2;
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 3:
                top    = IconTop(1)-2;
                bottom = IconBottom(1)-2;
                left   = IconLeft(1);
                right  = IconRight(1);      
                break;
            default: break;    
        }    

        if (!GFX_GOL_ButtonCreate (
                        ID_ICON1+i,     // object�s ID
                        left, top,
                        right, bottom,
                        0,              // radius if rounded edge
                        // draw the object after creation with
                        // text drawn at the bottom and no panel
                        GFX_GOL_BUTTON_DRAW|GFX_GOL_BUTTON_NOPANEL|GFX_GOL_BUTTON_TEXTBOTTOM,
                        pIconReleased,  // use this bitmap 
                        Labels[i],      // use this text
                        demoScheme      // use alternative style scheme
                        )
            )
            return 0;   
    }
    return 1;
    
}    

/////////////////////////////////////////////////////////////////////////////
// Function: WORD GOLMsgCallback(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns non-zero the message will be processed by default
// Overview: it's a user defined function. GOLMsg() function calls it each
//           time the valid message for the object received
/////////////////////////////////////////////////////////////////////////////
uint16_t GFX_GOL_MessageCallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t objID;

    // check first if we need to exit the selected demo (if applicable)
    if ((objMsg == GFX_GOL_BUTTON_MSG_RELEASED) && (pObj->ID == ID_BACK))
    {   
        // check if the button is indeed pressed
        if (GFX_GOL_StateGet(pObj, GFX_GOL_BUTTON_PRESSED))
        {
            screenState = CREATE_MAINMENU;
            return 1;
        }    
    }
    // process messages for demo screens
    switch(screenState)
    {
        case DISPLAY_MAINMENU:

            // In this portion, all management of the Button states are 
            // done here. This portion will always return 0 to inhibit
            // the button default message processing to take place.
                        
            objID = GFX_GOL_IDGet(pObj);
            if ((objID == ID_ICON1) || (objID == ID_ICON2) ||
                (objID == ID_ICON3) || (objID == ID_ICON4))
            {    
                if(objMsg == GFX_GOL_BUTTON_MSG_PRESSED)
                {    
                    // check if button is pressed and show pressed icon
                    GFX_GOL_ButtonBitmapSet(pObj, pIconPressed);
                    GFX_GOL_StateSet(pObj, GFX_GOL_BUTTON_PRESSED);
                }
                else if(objMsg == GFX_GOL_BUTTON_MSG_RELEASED)
                {
                    // check if button is released and show release icon
                    GFX_GOL_ButtonBitmapSet(pObj, pIconReleased);
                    GFX_GOL_StateClear(pObj, GFX_GOL_BUTTON_PRESSED);
                    if (objID == ID_ICON1)
                        {
                         while(GFX_DoubleBufferEnable(0) == NULL);
                         screenState = CREATE_MULTITOUCH;
                         }
                        else if (objID == ID_ICON2)
                        {
                          while(GFX_DoubleBufferEnable(0) == NULL);
                          SpeedDemo();
                          screenState = CREATE_MAINMENU;
                        }  
                        
                    else if (objID == ID_ICON3)
                        {
                        screenState = CREATE_ALPHABLEND;
                        } 
                   else if (objID == ID_ICON4)
                        {
                        while(GFX_DoubleBufferEnable(0) == NULL);
                        PagingDemo();
                        screenState = CREATE_MAINMENU;
                        }  
                }
                else if(objMsg == GFX_GOL_BUTTON_MSG_STILLPRESSED)
                {
                    // do not do anything since it is already pressed
                    return 0;     
                }    
                else
                {
                    // check if button is released and show release icon
                    GFX_GOL_ButtonBitmapSet(pObj, pIconReleased);
                    GFX_GOL_StateClear(pObj, GFX_GOL_BUTTON_PRESSED);              // reset pressed
                }            
                
                GFX_GOL_StateSet(pObj, GFX_GOL_BUTTON_DRAW);
                return 0;
            }
            if ((objID == ID_SCROLL1) || (objID == ID_SCROLL2) ||
                (objID == ID_SCROLL3) || (objID == ID_SCROLL4))
            {    
                if(objMsg == GFX_GOL_BUTTON_MSG_RELEASED)
                {
                 switch(objID) //Up = 1, Down = 2, Left = 3, Right = 4 
                 {
                    case ID_SCROLL1:
                    ScrollScreen(3,10);
                    break;
                    case ID_SCROLL2:
                    ScrollScreen(1,10);
                    break;
                    case ID_SCROLL3:
                    ScrollScreen(4,10);
                    break;
                    case ID_SCROLL4:
                    ScrollScreen(2,10);
                    break;
                 }

                }
            }
            break;

        case DISPLAY_ALPHABLEND:
            return (MsgAlphaBlendScreenCallback(objMsg, pObj, pMsg));

        default:
            break;
    }        

    return (1);
}

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t GFX_OBJ_DrawCallback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: it's a user defined function. GOLDraw() function calls it each
//           time when GOL objects drawing is completed. User drawing should be done here.
//           GOL will not change color, line type and clipping region settings while

//           this function returns zero.
/////////////////////////////////////////////////////////////////////////////
uint16_t GFX_GOL_DrawCallback(void)
{

   static int16_t x1, y1, x2, y2, x3, y3 = (-1);
   static uint8_t previousShape = 4; //Start with no previous shape
   static long prevTick = 50000;
    
   switch(screenState)
   {
        case CREATE_MAINMENU:  

            GFX_GOL_Free();

            GFX_ColorSet(WHITE());
            while(GFX_ScreenClear() == NULL);
 
            CreateMainMenu();
            
            screenState = DISPLAY_MAINMENU;       // switch to next state
            break;
            
        case DISPLAY_MAINMENU:
            break;         

        case CREATE_ALPHABLEND:
            GFX_GOL_Free() ;
            
            CreateBackButton();
            CreateAlphaBlendScreen();
            
            screenState = DISPLAY_ALPHABLEND;         // switch to next state
            break;
            
        case DISPLAY_ALPHABLEND:
            break;

#if defined(MEB_2_BOARD)

         case CREATE_MULTITOUCH:
            GFX_GOL_Free();

            GFX_ColorSet(WHITE());
            while(GFX_ScreenClear() == NULL);

            CreateBackButton();

            screenState = DISPLAY_MULTITOUCH; // switch to next state
            break;

        case DISPLAY_MULTITOUCH:

            if ((TouchGetX(2) != -1) && (TouchGetX(1) != -1) && (TouchGetX(0) != -1)) {
                tick = 0;

                if ((x3 != TouchGetX(2)) && (y3 != TouchGetY(2))) {


                    GFX_ColorSet(WHITE());

                    switch (previousShape)
                    {
                        case 0: //Circle
                            while(GFX_CircleFillDraw(x1, y1, 10>>DIVISOR)== NULL);
                            break;
                        case 1: //Line
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            break;
                        case 2: //Triangle
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            while(GFX_LineDraw(x2, y2, x3, y3)== NULL);
                            while(GFX_LineDraw(x1, y1, x3, y3)== NULL);
                            break;
                        default: break;
                    }

                    x1 = TouchGetX(0);
                    y1 = TouchGetY(0);
                    x2 = TouchGetX(1);
                    y2 = TouchGetY(1);
                    x3 = TouchGetX(2);
                    y3 = TouchGetY(2);

                    GFX_ColorSet(BRIGHTRED());
                    while(GFX_LineDraw(x1, y1, x2, y2) == NULL);
                    while(GFX_LineDraw(x2, y2, x3, y3) == NULL);
                    while(GFX_LineDraw(x1, y1, x3, y3) == NULL);
                    previousShape = 2;
                }
            }
            else if ((TouchGetX(1) != -1) && (TouchGetX(0) != -1)) {
                tick = 0;
                if ((x2 != TouchGetX(1)) && (y2 != TouchGetY(1))) {
                     GFX_ColorSet(WHITE());
                    switch (previousShape)
                    {
                        case 0: //Circle
                            while(GFX_CircleFillDraw(x1, y1, 10>>DIVISOR)== NULL);
                            break;
                        case 1: //Line
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            break;
                        case 2: //Triangle
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            while(GFX_LineDraw(x2, y2, x3, y3)== NULL);
                            while(GFX_LineDraw(x1, y1, x3, y3)== NULL);
                            break;
                        default: break;
                    }

                    x1 = TouchGetX(0);
                    y1 = TouchGetY(0);
                    x2 = TouchGetX(1);
                    y2 = TouchGetY(1);
                    GFX_ColorSet(BRIGHTRED());
                    while(GFX_LineDraw(x1, y1, x2, y2) == NULL);
                    previousShape = 1;
                }
            }
            else if (TouchGetX(0) != -1) {
                tick = 0;
                if ((x1 != TouchGetX(0)) && (y1 != TouchGetY(0)))
                {

                    GFX_ColorSet(WHITE());

                    switch (previousShape)
                    {
                        case 0: //Circle
                            while(GFX_CircleFillDraw(x1, y1, 10>>DIVISOR)== NULL);
                            break;
                        case 1: //Line
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            break;
                        case 2: //Triangle
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            while(GFX_LineDraw(x2, y2, x3, y3)== NULL);
                            while(GFX_LineDraw(x1, y1, x3, y3)== NULL);
                            break;
                        default: break;
                    }

                    x1 = TouchGetX(0);
                    y1 = TouchGetY(0);
                    x2,y2,y3,y3 = -1;
                    if((x1>5) && (x1<235) && (y1>25) && (y1<131))
                    {
                        GFX_ColorSet(BRIGHTRED());
                        while(GFX_CircleFillDraw(x1, y1, 10>>DIVISOR) == NULL);
                        previousShape = 0;
                    }
                }
            }
            else {

                if (tick++ == prevTick) {

                    GFX_ColorSet(WHITE());

                    switch (previousShape)
                    {
                        case 0: //Circle
                            while(GFX_CircleFillDraw(x1, y1, (10>>DIVISOR))== NULL);
                            break;
                        case 1: //Line
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            break;
                        case 2: //Triangle
                            while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                            while(GFX_LineDraw(x2, y2, x3, y3)== NULL);
                            while(GFX_LineDraw(x1, y1, x3, y3)== NULL);
                            break;
                        default: break;
                    }

                    GFX_ColorSet(BRIGHTRED());

                    x1 = rand() % GFX_MaxXGet();
                    y1 = rand() % GFX_MaxYGet();
                    x2 = rand() % GFX_MaxXGet();
                    y2 = rand() % GFX_MaxYGet();
                    x3 = rand() % GFX_MaxXGet();
                    y3 = rand() % GFX_MaxYGet();
                    while(GFX_LineDraw(x1, y1, x2, y2)== NULL);
                    while(GFX_LineDraw(x2, y2, x3, y3)== NULL);
                    while(GFX_LineDraw(x1, y1, x3, y3)== NULL);
                    tick = 0;
                    previousShape = 2;
                }
            }

            break;
#endif
        default: 
            break;    
    }    
    return (1);
}

/////////////////////////////////////////////////////////////////////////////
// Function: void TickInit(void)
// Input: none
// Output: none
// Overview: Initilizes the tick timer.
/////////////////////////////////////////////////////////////////////////////

/*********************************************************************
 * Section: Tick Delay
 *********************************************************************/
#define SAMPLE_PERIOD       500 // us
#define TICK_PERIOD			(GetPeripheralClock() * SAMPLE_PERIOD) / 4000000

/* */
void TickInit(void)
{
    TMR3 = 0;
    T3CONbits.TCKPS = 3;
    PR3 = 500;						//(for approximately 100 us)
    IPC3bits.T3IP = 1;
    IFS0bits.T3IF = 0;  						//Clear flag
    IEC0bits.T3IE = 1;  						//Enable interrupt
    T3CONbits.TON = 1;
}

void SpeedDemo(void)
{

uint32_t counter =0;
float       randl,randt,randr,randb,temp;

while(counter++ < 150)
{
	// draw random bars in the middle of the screen
        GFX_ColorSet(rand()%65536);
 
        randl = rand()%GFX_MaxXGet();
        randr = rand()%GFX_MaxXGet();

        if(randl > randr)
        {
           temp = randl;
           randl = randr;
           randr = temp;
        }

        randt = rand()%GFX_MaxYGet();
        randb = rand()%GFX_MaxYGet();

        if(randt > randb)
        {
           temp = randt;
           randt = randb;
           randb = temp;
        }

         while(GFX_RectangleFillDraw(randl,randt,randr,randb) == NULL);
         SYS_TMR_DelayMS(10);
}

}

void PagingDemo(void)
{

  int        x,y;
  XCHAR      Scroll[] = {'B','a','c','k','g','r','o','u','n','d',' ','W','i','l','l',' ','C','h','a','n','g','e',0};

  while(GFX_PageSet(ACTIVE_PAGE,PIP_BUFFER) == NULL);
  while(GFX_BarGradient(0,0,GFX_MaxXGet(),55,RGBConvert(55,0,0),BLACK(),100,GRAD_DOWN) == NULL);

  GFX_ColorSet(WHITE());

  GFX_Primitive_instance[handle].currentFont.alignment = LEFT;
  GFX_FontSet(&GFX_Primitive_instance[handle].currentFont,(void *)&FONTDEFAULT);
  while(GFX_TextStringXYPut(0,0,0,0,(XCHAR*)Scroll) == NULL); 

for(x=0;x<2;x++)        
{  

  while(GFX_PageSet(ACTIVE_PAGE,x) == NULL);

  if(x==0)
  {
     while(GFX_BarGradient(0,0,GFX_MaxXGet(),GFX_MaxYGet(),BRIGHTRED(),BLACK(),100,GRAD_DOWN)== NULL);
  }
  else
  {
      while(GFX_BarGradient(0,0,GFX_MaxXGet(),GFX_MaxYGet(),BRIGHTBLUE(),BLACK(),100,GRAD_DOWN) == NULL);
  }

        while(GFX_ImageDraw(70,10, (void*)&MchpIcon,1) == NULL);

}

  while(GFX_PageSet(ACTIVE_PAGE,0) == NULL);
  while(GFX_PageSet(VISUAL_PAGE,0) == NULL);

  while(GFX_Layer(0, SET_PAGE, PIP_BUFFER, 0) == NULL);
  while(GFX_Layer(0, SET_SIZE, DISP_HOR_RESOLUTION-1-10, 55) == NULL);
  while(GFX_Layer(0, SET_PAGE_START, 0, DISP_VER_RESOLUTION-1-56) == NULL);
  while(GFX_Layer(0, SET_LAYER_START, 0, 10) == NULL);

  SYS_TMR_DelayMS(1000);

  x=0;

  while(x++ < 3)
  {
       while(GFX_Layer(0, DISABLE, 0, 0) == NULL);
       SYS_TMR_DelayMS(2000);
       while(GFX_Layer(0, ENABLE, 0, 0) == NULL);
       SYS_TMR_DelayMS(2000);
  }

  x = 0;

  while(x++ < (DISP_HOR_RESOLUTION-1))
  {
     while(GFX_Layer(0, SET_LAYER_START, x, 10) == NULL);
     while(GFX_Layer(0, SET_SIZE, DISP_HOR_RESOLUTION-x, 55) == NULL);
     while(GFX_Layer(0, UPDATE, 0, 0) == NULL);
     SYS_TMR_DelayMS(10);
  }

  while(GFX_Layer(0, DISABLE, 0, 0) == NULL);
  GFX_ColorSet(WHITE());

  SYS_TMR_DelayMS(3000);

  while(GFX_PageSet(ACTIVE_PAGE,1) == NULL);
  while(GFX_PageSet(VISUAL_PAGE,1) == NULL);

  SYS_TMR_DelayMS(2000);
  while(GFX_PageSet(ACTIVE_PAGE,0) == NULL);
  while(GFX_PageSet(VISUAL_PAGE,1) == NULL);

  while(GFX_PageSet(ACTIVE_PAGE,2) == NULL);
  GFX_ColorSet(WHITE());
  while(GFX_ScreenClear() == NULL);

}

void ScrollScreen(BYTE direction, WORD delay)
{

   scrollPage = 0;
   //Up = 1, Down = 2, Left = 3, Right = 4 

   switch(direction)
   {

   case 1:
     scroll = 1;
     scrollLine = (DISP_VER_RESOLUTION-1);
     while(scrollLine > 0)
     {
      SYS_TMR_DelayMS(delay);
      scrollLine--;
     }
   break;
   case 2:
     scroll = 2;
   scrollLine = 0;
  while(scrollLine < (DISP_VER_RESOLUTION-1))
  {
      SYS_TMR_DelayMS(delay);
      scrollLine++;
  }
   break;
   case 3:
     scroll = 3;
   scrollLine = (DISP_HOR_RESOLUTION-1);//GFX_MaxXGet();
  while(scrollLine > 1)
  {
      SYS_TMR_DelayMS(delay);
      scrollLine--;
  }
   break;
   case 4:
     scroll = 4;
   scrollLine = 1;
  while(scrollLine < (DISP_HOR_RESOLUTION-1))//(GFX_MaxXGet()))
  {
      SYS_TMR_DelayMS(delay);
      scrollLine++;
  }
   break;

   }

scroll = 0;

}
