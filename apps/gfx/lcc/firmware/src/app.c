/*******************************************************************************
  Graphics Objects Layer Demo Application

  File Name:
    app.c

  Summary:
    Graphics Objects Layer Demo application

  Description:
    This file contains the Graphics Objects Layer Demo application logic.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

#include "gfx/gfx.h"
#include "driver/spi/drv_spi.h"
#include "gfx/src/common_legacy/SST25VF016.h"
#include "gfx/src/common_legacy/TouchScreen.h"
#include "AlphaBlendScreen.h"
#include "JPEGImage.h"
#include "internal_resource.h"
#include "driver/gfx/gfx_lcc/drv_gfx_lcc.h"

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
#define ID_BACK             0xF050

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT DIMENSIONS
/////////////////////////////////////////////////////////////////////////////
#define ICON_WIDTH          (72)
#define ICON_HEIGHT         (100)   
#define ICON_COLUMNSNUM     (2)
#define ICON_ROWSNUM        (2)
#define ICON_XINDENT        ((GFX_MaxXGet() - ICON_COLUMNSNUM * ICON_WIDTH) / (ICON_COLUMNSNUM + 1))
#define ICON_YINDENT        ((GFX_MaxYGet() - ICON_ROWSNUM * ICON_HEIGHT) / (ICON_ROWSNUM + 1))
#define IconTop(row)        (((row + 1) * ICON_YINDENT) + (row * ICON_HEIGHT))
#define IconBottom(row)     ((row + 1) * (ICON_YINDENT + ICON_HEIGHT))
#define IconLeft(column)    (((column + 1) * ICON_XINDENT) + (column * ICON_WIDTH))
#define IconRight(column)   ((column + 1) * (ICON_XINDENT + ICON_WIDTH))

/////////////////////////////////////////////////////////////////////////////
//                            IMAGES USED
/////////////////////////////////////////////////////////////////////////////
// iinternal flash image
//extern const IMAGE_FLASH    MCHPFolderFile_8bpp_72x72;
//extern const IMAGE_FLASH    MCHPFolderEmpty_8bpp_72x72;

/////////////////////////////////////////////////////////////////////////////
//                            FONTS USED
/////////////////////////////////////////////////////////////////////////////
//extern const FONT_FLASH     GOLFontDefault; // default GOL font
//extern const FONT_FLASH     Gentium;

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void            TickInit(void);            // starts tick counter         
uint16_t        CreateMainMenu();
uint16_t        CreateBackButton();
void            SpeedDemo(void);
void            PIPDemo(void);
void            PagingDemo(void);
void            ScrollScreen(uint8_t direction, uint16_t delay);

volatile uint32_t  tick = 0, prevTick;             // tick counter,

/////////////////////////////////////////////////////////////////////////////
//                            IMAGES USED
/////////////////////////////////////////////////////////////////////////////
// see InternalResources.h

/////////////////////////////////////////////////////////////////////////////
//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
GFX_GOL_OBJ_SCHEME      *demoScheme;                // alternative style scheme
GFX_GOL_OBJ_SCHEME      *AlphaScheme;                // alternative style scheme

// current state of main demo state mashine
SCREEN_STATES   screenState = CREATE_MAINMENU;


GFX_XCHAR Labels[4][10] = { {'P','I','P',0},
                       {'S','p','e','e','d',0},
                       {'A','.','B','l','e','n','d',0},
                       {'P','a','g','i','n','g',0},
                     };

GFX_XCHAR Scroll[4][3] = { {'<',0},
                       {'/',0x5c,0},
                       {'>',0},
                       {0x5c,'/',0},
                     };

GFX_XCHAR MainMenuStr[5] = {'M','A','I','N',0};


bool GFX_GOL_DrawCallback (void);
bool GFX_GOL_MessageCallback (GFX_GOL_TRANSLATED_ACTION translatedMsg,
                              GFX_GOL_OBJ_HEADER *pObj,
                              GFX_GOL_MESSAGE * pMsg);

extern const GFX_GOL_OBJ_SCHEME GOLSchemeDefault;

GFX_GOL_OBJ_SCHEME *GFX_GOL_SchemeCreate(void)
{
    GFX_GOL_OBJ_SCHEME  *pTemp;

    pTemp = (GFX_GOL_OBJ_SCHEME *)GFX_malloc(sizeof(GFX_GOL_OBJ_SCHEME));

    if(pTemp != NULL)
    {
        memcpy(pTemp, &GOLSchemeDefault, sizeof(GFX_GOL_OBJ_SCHEME));
    }

    return (pTemp);
}

void APP_Initialize ( void )
{

    demoScheme = GFX_GOL_SchemeCreate();  // create alternative style scheme
    AlphaScheme = GFX_GOL_SchemeCreate();  // create alternative style scheme

    demoScheme->TextColor0 = BLUE;
    demoScheme->TextColor1 = RED;
    demoScheme->pFont = (void*)&Gentium_16;
    demoScheme->fillStyle = GFX_FILL_STYLE_COLOR;

    AlphaScheme->Color0 = GFX_RGBConvert(0x4C, 0x8E, 0xFF);
    AlphaScheme->Color1 = GFX_RGBConvert(255, 102, 0);
    AlphaScheme->EmbossDkColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    AlphaScheme->EmbossLtColor = GFX_RGBConvert(0xA9, 0xDB, 0xEF);
    AlphaScheme->ColorDisabled = GFX_RGBConvert(0xD4, 0xE1, 0xF7);
    AlphaScheme->TextColor1 = BLUE;
    AlphaScheme->TextColor0 = GFX_RGBConvert(255, 102, 0);
    AlphaScheme->TextColorDisabled = GFX_RGBConvert(0xB8, 0xB9, 0xBC);
    AlphaScheme->AlphaValue = 50;
    AlphaScheme->pFont = (void*)&Gentium_16;
    AlphaScheme->fillStyle = GFX_FILL_STYLE_COLOR;

     SYS_TMR_DelayMS(5000);

    GFX_GOL_MessageCallbackSet(&GFX_GOL_MessageCallback);
    GFX_GOL_DrawCallbackSet(&GFX_GOL_DrawCallback);

    CreateMainMenu();

}

/* */
void APP_Tasks(void)
{

       GFX_GOL_ObjectListDraw();

}

/////////////////////////////////////////////////////////////////////////////
// Function: WORD CreateBackButton()
// Input: none
// Output: Returns 0 if the screen is created and 0 if not.
// Overview: Creates the four icons to launch each of the application 
//           note demos.
/////////////////////////////////////////////////////////////////////////////
uint16_t CreateBackButton()
{
    GFX_GOL_BUTTON *pObj;

    pObj = GFX_GOL_ButtonCreate (
                        
                        ID_BACK,     // object�s ID
                        20, 10,
                        70, 35, 0,
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL,
                        NULL,
                        MainMenuStr,
                        GFX_ALIGN_HCENTER,
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
uint16_t CreateMainMenu()
{

    int i;
    short left = 0, top = 0, right = 0, bottom = 0;

    while(GFX_DoubleBufferEnable() == GFX_STATUS_FAILURE);

            GFX_GOL_ButtonCreate (                        
                        ID_SCROLL1,     // object�s ID
                        0, 26,
                        25, GFX_MaxYGet()-26,
                        0,              
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL,  // use this bitmap
                        NULL,
                        Scroll[0],      // use this text
                        GFX_ALIGN_HCENTER,
                        demoScheme);      // use alternative style scheme
            GFX_GOL_ButtonCreate (                       
                        ID_SCROLL2,     // object�s ID
                        0, 0,
                        GFX_MaxXGet(), 25,
                        0,              
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL,  // use this bitmap
                        NULL,
                        Scroll[1],      // use this text
                        GFX_ALIGN_HCENTER,
                        demoScheme);      // use alternative style scheme
            GFX_GOL_ButtonCreate (
                        
                        ID_SCROLL3,     // object�s ID
                        GFX_MaxXGet()-25, 26,
                        GFX_MaxXGet(), GFX_MaxYGet()-26,
                        0,              // radius if rounded edge
                        // draw the object after creation with
                        // text drawn at the bottom and no panel
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL,  // use this bitmap
                        NULL,
                        Scroll[2],      // use this text
                        GFX_ALIGN_HCENTER,
                        demoScheme);      // use alternative style scheme
             GFX_GOL_ButtonCreate(
                        
                        ID_SCROLL4,     // object�s ID
                        0, GFX_MaxYGet()-25,
                        GFX_MaxXGet(), GFX_MaxYGet(),
                        0,
                        GFX_GOL_BUTTON_DRAW_STATE,
                        NULL,  // use this bitmap
                        NULL,
                        Scroll[3],      // use this text
                        GFX_ALIGN_HCENTER,
                        demoScheme);      // use alternative style scheme

    // loop to create the four icons
    for (i=0; i<4; i++)
    {
        switch (i)
        {
            case 0:
                top    = IconTop(0);
                bottom = IconBottom(0);
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 1:
                top    = IconTop(0);
                bottom = IconBottom(0);
                left   = IconLeft(1);
                right  = IconRight(1);      
                break;
            case 2:
                top    = IconTop(1);
                bottom = IconBottom(1);
                left   = IconLeft(0);
                right  = IconRight(0);      
                break;
            case 3:
                top    = IconTop(1);
                bottom = IconBottom(1);
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
                        GFX_GOL_BUTTON_DRAW_STATE|GFX_GOL_BUTTON_NOPANEL_STATE,
                        (void*) &MCHPFolderFile_8bpp_72x72,  // use this bitmap
                        (void*) &MCHPFolderEmpty_8bpp_72x72,
                        Labels[i],      // use this text
                        GFX_ALIGN_HCENTER|GFX_ALIGN_BOTTOM,
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
bool GFX_GOL_MessageCallback(GFX_GOL_TRANSLATED_ACTION objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t objID;

    // check first if we need to exit the selected demo (if applicable)
    if ((objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) && (pObj->ID == ID_BACK))
    {   
        // check if the button is indeed pressed
        if (GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
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
                        
            objID = GFX_GOL_ObjectIDGet(pObj);
            if ((objID == ID_ICON1) || (objID == ID_ICON2) ||
                (objID == ID_ICON3) || (objID == ID_ICON4))
            {    
                if(objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
                {    
                    // check if button is pressed and show pressed icon
                    GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_PRESSED_STATE);
                }
                else if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
                {
                    // check if button is released and show release icon
                    GFX_GOL_ObjectStateClear(pObj, GFX_GOL_BUTTON_PRESSED_STATE);
                    if (objID == ID_ICON1)
                        {
                         while(GFX_DoubleBufferDisable() == GFX_STATUS_FAILURE);
                         PIPDemo();
                         screenState = CREATE_MAINMENU;
                         }
                        else if (objID == ID_ICON2)
                        {
                         while(GFX_DoubleBufferDisable() == GFX_STATUS_FAILURE);
                         SpeedDemo();
                         screenState = CREATE_MAINMENU;
                        }  
                        
                    else if (objID == ID_ICON3)
                        {
                        screenState = CREATE_ALPHABLEND;
                        } 
                   else if (objID == ID_ICON4)
                        {
                        while(GFX_DoubleBufferDisable() == GFX_STATUS_FAILURE);
                        PagingDemo();
                        screenState = CREATE_MAINMENU;
                        }
                    else
                        // this should not happen 
                        screenState = DISPLAY_MAINMENU;    
                }
                else if(objMsg == GFX_GOL_BUTTON_ACTION_STILLPRESSED)
                {
                    // do not do anything since it is already pressed
                    return 0;     
                }    
                else
                {
                    // check if button is released and show release icon
                    GFX_GOL_ObjectStateClear(pObj, GFX_GOL_BUTTON_PRESSED_STATE);              // reset pressed
                }            
                
                GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_DRAW_STATE);
                return 0;
            }
            if ((objID == ID_SCROLL1) || (objID == ID_SCROLL2) ||
                (objID == ID_SCROLL3) || (objID == ID_SCROLL4))
            {    
                if(objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
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
// Function: uint16_t GFX_GOL_DrawCallback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: it's a user defined function. GOLDraw() function calls it each
//           time when GOL objects drawing is completed. User drawing should be done here.
//           GOL will not change color, line type and clipping region settings while

//           this function returns zero.
/////////////////////////////////////////////////////////////////////////////
bool GFX_GOL_DrawCallback(void)
{
    
   switch(screenState)
    {
        case CREATE_MAINMENU:  

            GFX_GOL_ObjectListFree();

            GFX_ColorSet(WHITE);
            while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

            CreateMainMenu();
            
            screenState = DISPLAY_MAINMENU;       // switch to next state
            break;
            
        case DISPLAY_MAINMENU:
            break;         

        case CREATE_ALPHABLEND:
            GFX_GOL_ObjectListFree();
            
            CreateAlphaBlendScreen();
            CreateBackButton();
            
            screenState = DISPLAY_ALPHABLEND;         // switch to next state
            break;
            
        case DISPLAY_ALPHABLEND:
            break;
            
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
    PR3 = 50;						//(for approximately 100 us)
    IPC3bits.T3IP = 5;
    IFS0bits.T3IF = 0;  						//Clear flag
    IEC0bits.T3IE = 1;  						//Enable interrupt
    T3CONbits.TON = 1;

    TMR4 = 0;
    T4CONbits.TCKPS = 3;
    PR4 = 500;						//(for approximately 100 us)
    IPC4bits.T4IP = 4;
    IFS0bits.T4IF = 0;  						//Clear flag
    IEC0bits.T4IE = 1;  						//Enable interrupt
    T4CONbits.TON = 1;
}

void PIPDemo(void)
{
        int        x,y;

        GFX_XCHAR Title1[] = {'P','I','P',' ','D','e','m','o',0};
        GFX_XCHAR Title2[] = {'P','a','g','e',0};
        GFX_XCHAR Title3[] = {'S','t','a','r','t',0};

        while(GFX_PageSet(ACTIVE_PAGE,0) == GFX_STATUS_FAILURE);
        while(GFX_PageSet(VISUAL_PAGE,0) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BLACK);

        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

        while(GFX_PageSet(ACTIVE_PAGE,PIP_BUFFER) == GFX_STATUS_FAILURE);

        GFX_ColorSet(BLACK);
        while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

        while(GFX_ImageDraw(0,0, (void*)&mouse) == GFX_STATUS_FAILURE);    //Draw Mouse in cursor area
        while(GFX_ImageDraw(15,0, (void*)&Pacman) == GFX_STATUS_FAILURE);   //Draw Pacman in cursor area
 
        while(GFX_PageSet(ACTIVE_PAGE,0) == GFX_STATUS_FAILURE);

        GFX_FontSet((void *) &Monospaced_plain_36);
        GFX_ColorSet(WHITE);

        while(GFX_TextStringBoxDraw(0,40,0,0,(GFX_XCHAR*)Title1,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
        while(GFX_TextStringBoxDraw(0,90,0,0,(GFX_XCHAR*)Title2,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

        GFX_GradientColorSet(WHITE,BLACK);
        GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOWN);
        while(GFX_BevelGradientDraw(200,125,300,165,5) == GFX_STATUS_FAILURE);
        GFX_ColorSet(BLACK);
        while(GFX_TextStringBoxDraw(195,115,0,0,(GFX_XCHAR*)Title3,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

        while(GFX_Layer(0, SET_PAGE, PIP_BUFFER, 0) == GFX_STATUS_FAILURE);
        while(GFX_Layer(0, SET_SIZE, 15, 15) == GFX_STATUS_FAILURE);
        while(GFX_Layer(0, SET_LAYER_START, 0, 0) == GFX_STATUS_FAILURE);
        while(GFX_Layer(0, ENABLE, 0, 0) == GFX_STATUS_FAILURE);

        x = 0;
        y = 224;

             while(x<280)
             {
             while(GFX_Layer(0, SET_PAGE_START, x, y) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, UPDATE, 0, 0) == GFX_STATUS_FAILURE);
             y--;
             SYS_TMR_DelayMS(40);
             x+=5;
             }

             SYS_TMR_DelayMS(500);

             GFX_GradientColorSet(BLUE,BLACK);
             GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOWN);
             while(GFX_BevelGradientDraw(200,125,300,165,5)==GFX_STATUS_FAILURE);
             GFX_ColorSet(WHITE);
             while(GFX_TextStringBoxDraw(195,115,0,0,(GFX_XCHAR*)Title3,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

             SYS_TMR_DelayMS(1000);
             while(GFX_Layer(0, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
             SYS_TMR_DelayMS(1000);
           
             x = GFX_MaxXGet()-50;
             GFX_ColorSet(BLACK);

             while(GFX_Layer(0, SET_SIZE, 45, 45) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, SET_LAYER_START, 15, 0) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, ENABLE, 0, 0) == GFX_STATUS_FAILURE);

             while(x>5)
             {
             while(GFX_Layer(0, SET_PAGE_START, x, 32) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, SET_LAYER_START, 15, 0) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, UPDATE, 0, 0) == GFX_STATUS_FAILURE);
             SYS_TMR_DelayMS(40);
             while(GFX_Layer(0, SET_PAGE_START, x-5, 32) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, SET_LAYER_START, 60, 0) == GFX_STATUS_FAILURE);
             while(GFX_Layer(0, UPDATE, 0, 0) == GFX_STATUS_FAILURE);
             SYS_TMR_DelayMS(40);
             x -= 10;
             }
              while(GFX_Layer(0, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
} 

void SpeedDemo(void)
{

uint16_t counter =0;
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

         while(GFX_RectangleFillDraw(randl,randt,randr,randb) == GFX_STATUS_FAILURE);
}

}

void PagingDemo(void)
{

  int        x,y;
  GFX_XCHAR      Scroll[] = {'C','o','l','o','r','s',' ','C','h','a','n','g','e',' ','w',' ','T','e','m','p','s',0};
  GFX_XCHAR      Cloud[] = {'C','l','o','u','d','y',0};
  GFX_XCHAR      Temper[] = {'T','e','m','p','e','r','a','t','u','r','e',0};
  GFX_XCHAR      SetTemp[] = {'S','e','t',' ','T','e','m','p',0};
  GFX_XCHAR      Time[] = {'8',':','2','0',' ','P','M',0};
  GFX_XCHAR      Date[] = {'J','u','n','e',' ','1','1',',',' ','2','0','1','2',0};
  GFX_XCHAR      Room[] = {'7','4',0};

              while(GFX_PageSet(ACTIVE_PAGE,PIP_BUFFER) == GFX_STATUS_FAILURE);
              GFX_GradientColorSet(GFX_RGBConvert(55,0,0),BLACK);
              GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOWN);
              while(GFX_BarGradientDraw(0,0,GFX_MaxXGet(),55) == GFX_STATUS_FAILURE);
              GFX_ColorSet(WHITE);

              GFX_FontSet((void *) &Monospaced_plain_36);
              while(GFX_TextStringBoxDraw(0,0,0,0,(GFX_XCHAR*)Scroll,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

  GFX_XCHAR Temp[] ={'7','3',0};

for(x=0;x<2;x++)        
{  

  while(GFX_PageSet(ACTIVE_PAGE,x) == GFX_STATUS_FAILURE);

  if(x==0)
  {
     GFX_GradientColorSet(BRIGHTRED,BLACK);
     while(GFX_BarGradientDraw(0,0,GFX_MaxXGet(),GFX_MaxYGet())== GFX_STATUS_FAILURE);
  }
  else
  {
      GFX_GradientColorSet(BRIGHTBLUE,BLACK);
      while(GFX_BarGradientDraw(0,0,GFX_MaxXGet(),GFX_MaxYGet()) == GFX_STATUS_FAILURE);
  }

  GFX_GradientColorSet(WHITE,BLACK);
  while(GFX_BevelGradientDraw(340,120,370,140,10) == GFX_STATUS_FAILURE);
  while(GFX_BevelGradientDraw(340,165,370,185,10) == GFX_STATUS_FAILURE);
  GFX_ColorSet(WHITE);
  GFX_FontSet((void *) &Gentium_16);
  while(GFX_TextStringBoxDraw(50,75,0,0,(GFX_XCHAR*)Cloud,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
  while(GFX_TextStringBoxDraw(190,75,0,0,(GFX_XCHAR*)Temper,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
  while(GFX_TextStringBoxDraw(380,75,0,0,(GFX_XCHAR*)SetTemp,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

   GFX_ColorSet(WHITE);
   while(GFX_TextStringBoxDraw(GFX_MaxXGet()-80,0,0,0,(GFX_XCHAR*)Time,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
   while(GFX_TextStringBoxDraw(10,0,0,0,(GFX_XCHAR*)Date,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

   GFX_FontSet((void *) &Monospaced_plain_36);
   while(GFX_TextStringBoxDraw(345,100,0,0,(GFX_XCHAR*)"+",0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
   while(GFX_TextStringBoxDraw(345,145,0,0,(GFX_XCHAR*)"-",0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

   GFX_FontSet((void *) &Monospaced_bold_Bold_72);

  if(x==0)
  { 
    while(GFX_TextStringBoxDraw(210,100,0,0,(GFX_XCHAR*)Temp,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);   //Room Temp
  }

  while(GFX_TextStringBoxDraw(385,100,0,0,(GFX_XCHAR*)Room,0, GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);

        while(ImageDecode
        (                                              
            (void *)&clouds,
            IMG_JPEG,                          
            10,                              
            100,
            10 + clouds_WIDTH,
            100 + clouds_HEIGHT,
            0,                                 
            &_jpegFileApi,                     
            NULL                   
        ) == 0xff);

}

  while(GFX_PageSet(ACTIVE_PAGE,0) == GFX_STATUS_FAILURE);
  while(GFX_PageSet(VISUAL_PAGE,0) == GFX_STATUS_FAILURE);

  while(GFX_Layer(0, SET_PAGE, PIP_BUFFER, 0) == GFX_STATUS_FAILURE);
  while(GFX_Layer(0, SET_SIZE, GFX_MaxXGet()-10, 55) == GFX_STATUS_FAILURE);
  while(GFX_Layer(0, SET_PAGE_START, 0, GFX_MaxYGet()-56) == GFX_STATUS_FAILURE);
  while(GFX_Layer(0, SET_LAYER_START, 0, 0) == GFX_STATUS_FAILURE);

  SYS_TMR_DelayMS(1000);
  x=0;

  while(x++ < 3)
  {
       while(GFX_Layer(0, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
       SYS_TMR_DelayMS(500);
       while(GFX_Layer(0, ENABLE, 0, 0) == GFX_STATUS_FAILURE);
       SYS_TMR_DelayMS(500);
  }

  x = 0;

  while(x++ < 465)
  {
     while(GFX_Layer(0, SET_LAYER_START, x, 0) == GFX_STATUS_FAILURE);
     while(GFX_Layer(0, SET_SIZE, GFX_MaxXGet()-10-x, 55) == GFX_STATUS_FAILURE);
     while(GFX_Layer(0, UPDATE, 0, 0) == GFX_STATUS_FAILURE);
     SYS_TMR_DelayMS(10);
  }

  while(GFX_Layer(0, DISABLE, 0, 0) == GFX_STATUS_FAILURE);
  GFX_ColorSet(WHITE);

 for(x=0;x<1;x++)
 {
  Temp[1] += 1; SYS_TMR_DelayMS(1000);
  GFX_GradientColorSet(GFX_RGBConvert(148,0,0),BLACK);
  GFX_GradientTypeSet(GFX_FILL_STYLE_GRADIENT_DOWN);
  while(GFX_BarGradientDraw(250,116,300,GFX_MaxYGet()) == GFX_STATUS_FAILURE);
  GFX_ColorSet(WHITE);
  GFX_FontSet((void *) &Gentium_16);
  while(GFX_TextStringBoxDraw(190,75,0,0,(GFX_XCHAR*)Temper,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
  GFX_FontSet((void *) &Monospaced_bold_Bold_72);
  while(GFX_TextStringBoxDraw(210,100,0,0,(GFX_XCHAR*)Temp,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
  } 

  while(GFX_PageSet(ACTIVE_PAGE,1) == GFX_STATUS_FAILURE);
  while(GFX_TextStringBoxDraw(210,100,0,0,(GFX_XCHAR*)Temp,0,GFX_ALIGN_LEFT) == GFX_STATUS_FAILURE);
  while(GFX_PageSet(VISUAL_PAGE,1) == GFX_STATUS_FAILURE);

  SYS_TMR_DelayMS(2000);
  while(GFX_PageSet(ACTIVE_PAGE, 0) == GFX_STATUS_FAILURE);
  while(GFX_PageSet(VISUAL_PAGE, 0) == GFX_STATUS_FAILURE);
  GFX_ColorSet(WHITE);
  while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

}

void ScrollScreen(uint8_t direction, uint16_t delay)
{

   scrollPage = 1;
   //Up = 1, Down = 2, Left = 3, Right = 4 

   switch(direction)
   {

   case 1:
     scroll = 1;
     scrollLine = GFX_MaxYGet();
     while(scrollLine > 0)
     {
      SYS_TMR_DelayMS(delay);
      scrollLine--;
     }
   break;
   case 2:
     scroll = 2;
   scrollLine = 0;
  while(scrollLine < GFX_MaxYGet())
  {
      SYS_TMR_DelayMS(delay);
      scrollLine++;
  }
   break;
   case 3:
     scroll = 3;
   scrollLine = GFX_MaxXGet();
  while(scrollLine > 1)
  {
      SYS_TMR_DelayMS(delay);
      scrollLine--;
  }
   break;
   case 4:
     scroll = 4;
   scrollLine = 1;
  while(scrollLine < (GFX_MaxXGet()))
  {
      SYS_TMR_DelayMS(delay);
      scrollLine++;
  }
   break;

   }

scroll = 0;

}

  


