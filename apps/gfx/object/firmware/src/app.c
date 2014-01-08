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

/*****************************************************************************
 * Section: Includes
 *****************************************************************************/
#include "app.h"
#include "ChineseFontsfontref.h"

uint8_t handle = 0xff;

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define ID_WINDOW1              10

#define ID_BUTTON1              11
#define ID_BUTTON2              12
#define ID_BUTTON3              13
#define ID_BUTTON4              14
#define ID_BUTTON5              15
#define ID_BUTTON6              16
#define ID_BUTTON7              17

#define ID_BUTTON_BACK          18
#define ID_BUTTON_NEXT          19

#define ID_CHECKBOX1            20
#define ID_CHECKBOX2            21
#define ID_CHECKBOX3            22
#define ID_CHECKBOX4            23
#define ID_CHECKBOX5            24

#define ID_RADIOBUTTON1         30
#define ID_RADIOBUTTON2         31
#define ID_RADIOBUTTON3         32
#define ID_RADIOBUTTON4         33
#define ID_RADIOBUTTON5         34
#define ID_RADIOBUTTON6         35
#define ID_RADIOBUTTON7         36
#define ID_RADIOBUTTON8         37

#define ID_SLIDER1              40
#define ID_SLIDER2              41
#define ID_SLIDER3              42

#define ID_GROUPBOX1            50
#define ID_GROUPBOX2            51
#define ID_STATICTEXT1          52
#define ID_STATICTEXT2          53
#define ID_STATICTEXT3          54

#define ID_PICTURE1             55
//#define ID_STATICTEXT4        56

#define ID_PROGRESSBAR1         60
#define ID_CUSTOM1              70

#define ID_LISTBOX1             80
#define ID_LISTBOX2             81
#define ID_LISTBOX3             82
#define ID_EDITBOX1             83

#define ID_CALL                 91
#define ID_STOPCALL             92
#define ID_HOLD                 93
#define ID_BACKSPACE            94
#define ID_POUND                95
#define ID_ASTERISK             96
#define ID_KEYPAD               100                         /* uses 100 to 110 for phone key pad demo */

#define ID_ROUNDDIAL            120
#define ID_METER1               130
#define ID_METER2               131
#define ID_DIGITALMETER1        132
#define ID_DIGITALMETER2        133

#define ID_BUTTONHR_P           150
#define ID_BUTTONHR_M           151
#define ID_BUTTONMN_P           152
#define ID_BUTTONMN_M           153
#define ID_BUTTONSC_P           154
#define ID_BUTTONSC_M           155

#define ID_BUTTON_DATE_UP       180
#define ID_BUTTON_DATE_DN       181

#define ID_BUTTON_MO            186
#define ID_BUTTON_DY            187
#define ID_BUTTON_YR            188
#define ID_BUTTON_RET           189

#define ID_GFX_GOL_EDITBOX_MONTH             200
#define ID_GFX_GOL_EDITBOX_DAY               201
#define ID_GFX_GOL_EDITBOX_YEAR              202

#define ID_GFX_GOL_EDITBOX_HOUR              205
#define ID_GFX_GOL_EDITBOX_MINUTE            206
#define ID_GFX_GOL_EDITBOX_SECOND            207

#define NAV_GFX_GOL_BUTTON_WIDTH           25

// Language offset definitions
#define LANG_ENGLISH            0
#define LANG_CHINESE            1

//volatile GFX_PRIMITIVE_COMMAND *queueIndex = NULL;

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void StartScreen(); // draws intro screen

void CreatePage(GFX_XCHAR *pText); // creates the navigation buttons and window for each screen

void CreateButtons(void); // creates buttons demo screen
uint16_t MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for buttons demo screen

void CreateRoundButtons(void); // creates rounded buttons demo screen
uint16_t MsgRoundButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for rounded buttons demo screen

void CreateCheckBoxes(void); // creates checkboxes demo screen
uint16_t MsgCheckBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for checkboxes demo screen

void CreateRadioButtons(void); // creates radio buttons demo screen
uint16_t MsgRadioButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for radio buttons demo screen

void CreateStaticText(void); // creates static text demo screen
uint16_t MsgStaticText(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for static text demo screen

void CreatePicture(void); // creates picture demo screen
uint16_t MsgPicture(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for picture demo screen

void CreateSlider(void); // creates slider demo screen
void DrawSliderCursor(uint16_t color, short x, short y); // draws cursor for slider demo screen
uint16_t MsgSlider(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for slider demo screen

void CreateProgressBar(void); // creates progress bar demo screen
uint16_t MsgProgressBar(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); //  processes messages for progress bar demo screen

void CreateSignature(void); // creates signature demo screen
uint16_t PanelSignature(void); // draws box for the signature
uint16_t MsgSignature(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for signature demo screen

void CreateCustomControl(void); // creates custom control demo screen
uint16_t MsgCustomControl(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for custom control demo screen

void CreateListBox(void); // creates list box demo screen
uint16_t MsgListBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for list box demo screen

void CreateEditBox(void); // creates edit box demo screen
uint16_t MsgEditBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for edit box demo screen

void CreateMeter(void); // creates meter demo screen
void UpdateMeter(void);
uint16_t MsgMeter(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for meter demo screen

void CreateDial(void); // creates dial demo screen
uint16_t MsgDial(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj); // processes messages for dial demo screen

void CreatePullDown(void);
uint16_t MsgPullDown(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes screen pull down menu
void DisplayPullDown(void); // refresh the screen when switching screen using pulldown menu
void ShowPullDownMenu(void); // create objects for pull down menu and draw
uint16_t RemovePullDownMenu(void); // removes pop out pull down menu from screen

void ErrorTrap(GFX_XCHAR *message); // outputs text message on screen and stop execution

void TickInit(void); // starts tick counter
void InitializeBoard(void); // Initializes the hardware components including the PIC device
void InitializeSchemes(void); //Initializes the schemes

bool GFX_GOL_DrawCallback (void);
bool GFX_GOL_MessageCallback (GFX_GOL_TRANSLATED_ACTION translatedMsg,
                              GFX_GOL_OBJ_HEADER *pObj,
                              GFX_GOL_MESSAGE * pMsg);

/////////////////////////////////////////////////////////////////////////////
//                             FONTS USED
/////////////////////////////////////////////////////////////////////////////
extern const GFX_RESOURCE_HDR GOLFontDefault; // default GOL font
extern const GFX_RESOURCE_HDR GOLSmallFont; // small font
extern const GFX_RESOURCE_HDR monofont; // equal width font

const GFX_RESOURCE_HDR *ptrLargeAsianFont = &GOLFontDefault;
const GFX_RESOURCE_HDR *ptrSmallAsianFont = &GOLSmallFont;

/////////////////////////////////////////////////////////////////////////////
//                            COLORS USED
/////////////////////////////////////////////////////////////////////////////
#define GRAY20      GFX_RGBConvert(51, 51, 51)
#define RED4        GFX_RGBConvert(139, 0, 0)
#define FIREBRICK1  GFX_RGBConvert(255, 48, 48)
#define DARKGREEN   GFX_RGBConvert(0, 100, 0)
#define PALEGREEN   GFX_RGBConvert(152, 251, 152)

/////////////////////////////////////////////////////////////////////////////
//                            DEMO STATES
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
    CREATE_BUTTONS = 0,
    DISPLAY_BUTTONS,
    CREATE_CHECKBOXES,
    DISPLAY_CHECKBOXES,
    CREATE_RADIOBUTTONS,
    DISPLAY_RADIOBUTTONS,
    CREATE_STATICTEXT,
    DISPLAY_STATICTEXT,
    CREATE_PICTURE,
    DISPLAY_PICTURE,
    CREATE_SLIDER,
    DISPLAY_SLIDER,
    CURSOR_DRAW_SLIDER,
    CREATE_PROGRESSBAR,
    DISPLAY_PROGRESSBAR,
    CREATE_LISTBOX,
    DISPLAY_LISTBOX,
    CREATE_EDITBOX,
    DISPLAY_EDITBOX,
    CREATE_METER,
    DISPLAY_METER,
    CREATE_DIAL,
    DISPLAY_DIAL,
    CREATE_CUSTOMCONTROL,
    DISPLAY_CUSTOMCONTROL,
    CREATE_SIGNATURE,
    DISPLAY_SIGNATURE,
    BOX_DRAW_SIGNATURE,
    CREATE_PULLDOWN,
    DISPLAY_PULLDOWN,

    // these states are for time and date settings 0xF3xx is used here as a
    // state ID to check when date and time are to be updated or not.
    CREATE_DATETIME = 0xF300, // creates the date and time setting menu
    DISPLAY_DATETIME = 0xF301, // displays the menu for the date and time setting
    DISPLAY_DATE_PDMENU = 0xF302, // displays the pulldown menu to set one of the date items (month, day or year)
    SHOW_DATE_PDMENU = 0xF303, // creates the pulldown menu to set one of the date items (month, day or year)
    HIDE_DATE_PDMENU = 0xF304, // hides the pulldown menu to set one of the date items (month, day or year)
} SCREEN_STATES;

/////////////////////////////////////////////////////////////////////////////
//                       GLOBAL VARIABLES FOR DEMO
/////////////////////////////////////////////////////////////////////////////
SCREEN_STATES screenState = CREATE_BUTTONS; // current state of main demo state mashine

GFX_GOL_OBJ_SCHEME *altScheme; // alternative style scheme
GFX_GOL_OBJ_SCHEME *alt2Scheme; // alternative 2 style scheme
GFX_GOL_OBJ_SCHEME *alt3Scheme; // alternative 3 style scheme
GFX_GOL_OBJ_SCHEME *alt4Scheme; // alternative 4 style scheme
GFX_GOL_OBJ_SCHEME *alt5Scheme; // alternative 5 style scheme
GFX_GOL_OBJ_SCHEME *redScheme; // alternative red style scheme
GFX_GOL_OBJ_SCHEME *greenScheme; // alternative green style scheme
GFX_GOL_OBJ_SCHEME *yellowScheme; // alternative yellow style scheme
GFX_GOL_OBJ_SCHEME *meterScheme; // meter scheme
GFX_GOL_OBJ_SCHEME *navScheme; // style scheme for the navigation

GFX_GOL_OBJ_HEADER *pGenObj; // pointer to a general purpose object

GFX_GOL_PROGRESSBAR *pProgressBar; // pointer to progress bar object for progress bar demo

GFX_GOL_SCROLLBAR *pSlider; // pointer to the slider controlling the animation speed

char animate; // switch to control animation for picture demo
GFX_GOL_PICTURECONTROL *pPicture; // pointer to picture object for picture demo

volatile uint32_t tick = 0; // tick counter

// DEFINITIONS FOR CUSTOM CONTROL DEMO
#define CC_ORIGIN_X ((GFX_MaxXGet() - 180 + 1) / 2)
#define CC_ORIGIN_Y ((40 + GFX_MaxYGet() - 175 + 1) / 2)

short x, prevX; // cursor X position
short y, prevY; // cursor Y position
uint16_t cursorUpdate; // update the cursor position if set

SCREEN_STATES prevState = CREATE_BUTTONS; // used to mark state where time setting was called
SCREEN_STATES prevRefreshState = CREATE_BUTTONS; // used to mark the start of the previous screen

/////////////////////////////////////////////////////////////////////////////
//                            MACROS
/////////////////////////////////////////////////////////////////////////////
#define WAIT_UNTIL_FINISH(x)    while(x == GFX_STATUS_FAILURE)

#define MIN(x,y)                ((x > y)? y: x)

#define GFX_SCHEMEDEFAULT GOLSchemeDefault

extern const GFX_GOL_OBJ_SCHEME GFX_SCHEMEDEFAULT;

GFX_GOL_OBJ_SCHEME *GFX_GOL_SchemeCreate(void)
{
    GFX_GOL_OBJ_SCHEME  *pTemp;

    pTemp = (GFX_GOL_OBJ_SCHEME *)GFX_malloc(sizeof(GFX_GOL_OBJ_SCHEME));

    if(pTemp != NULL)
    {
        memcpy(pTemp, &GFX_SCHEMEDEFAULT, sizeof(GFX_GOL_OBJ_SCHEME));
    }

    return (pTemp);
}

void APP_Initialize ( void )
{

    DisplayResetEnable();               // hold in reset by default

    DisplayResetConfig();               // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                    // enable chip select line

    DisplayBacklightOff();              // initially set the backlight to off

    DisplayBacklightConfig();           // set the backlight control pin

    GFX_GOL_MessageCallbackSet(&GFX_GOL_MessageCallback);
    GFX_GOL_DrawCallbackSet(&GFX_GOL_DrawCallback);

}

/////////////////////////////////////////////////////////////////////////////

//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
void APP_Tasks(void)
{
   
       GFX_GOL_ObjectListDraw();

}

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t GFX_GOL_MESSAGECallback(uint16_t objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg)
// Input: objMsg - translated message for the object,
//        pObj - pointer to the object,
//        pMsg - pointer to the non-translated, raw GOL message
// Output: if the function returns non-zero the message will be processed by default
// Overview: this function must be implemented by user. GFX_GOL_MESSAGE() function calls it each
//           time the valid message for the object received
/////////////////////////////////////////////////////////////////////////////

bool GFX_GOL_MessageCallback(GFX_GOL_TRANSLATED_ACTION objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{

    // beep if button is pressed
    if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
    {
        //Beep();
    }

    // process messages for demo screens
    switch (screenState)
    {
        case DISPLAY_BUTTONS:
            return (MsgButtons(objMsg, pObj));

        case DISPLAY_CHECKBOXES:
            return (MsgCheckBoxes(objMsg, pObj));

        case DISPLAY_RADIOBUTTONS:
            return (MsgRadioButtons(objMsg, pObj));

        case DISPLAY_STATICTEXT:
            return (MsgStaticText(objMsg, pObj));

        case DISPLAY_SLIDER:
            return (MsgSlider(objMsg, pObj, pMsg));

        case DISPLAY_PROGRESSBAR:
            return (MsgProgressBar(objMsg, pObj));

        case DISPLAY_LISTBOX:
            return (MsgListBox(objMsg, pObj, pMsg));

        case DISPLAY_EDITBOX:
            return (MsgEditBox(objMsg, pObj, pMsg));

        case DISPLAY_METER:
            return (MsgMeter(objMsg, pObj));
//
//        case DISPLAY_DIAL:
//            return (MsgDial(objMsg, pObj));

        case DISPLAY_PICTURE:
            return (MsgPicture(objMsg, pObj));

        case DISPLAY_CUSTOMCONTROL:
            return (MsgCustomControl(objMsg, pObj, pMsg));

        case DISPLAY_SIGNATURE:
            return (MsgSignature(objMsg, pObj, pMsg));

        case DISPLAY_PULLDOWN:
            //TODO return (MsgPullDown(objMsg, pObj, pMsg));

            // date and time settings display
        case DISPLAY_DATETIME:
            //TODO return (MsgDateTime(objMsg, pObj));

        case DISPLAY_DATE_PDMENU:
            //TODO return (MsgSetDate(objMsg, pObj, pMsg));

        case CREATE_DATETIME:
        case SHOW_DATE_PDMENU:
        case HIDE_DATE_PDMENU:
            return (0);

        default:

            // process message by default
            return (1);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Function: uint16_t GFX_GOL_DrawCallback()
// Output: if the function returns non-zero the draw control will be passed to GOL
// Overview: this function must be implemented by user. GFX_GOL_Draw() function calls it each
//           time when GOL objects drawing is completed. User drawing should be done here.
//           GOL will not change color, line type and clipping region settings while
//           this function returns zero.
/////////////////////////////////////////////////////////////////////////////

bool GFX_GOL_DrawCallback(void)
{
    static uint32_t prevTick = 0; // keeps previous value of tick
    static uint8_t direction = 1; // direction switch for progress bar
    static uint8_t arrowPos = 0; // arrows pictures position for custom control demo
    static uint32_t wDelay = 40; // progress bar delay variable
    GFX_GOL_OBJ_HEADER *pObj = NULL; // used to change text in Window
    GFX_GOL_SCROLLBAR *pSld; // used when updating date and time
    GFX_GOL_LISTBOX *pLb; // used when updating date and time
    static uint8_t* pictStream[4] = {(uint8_t*)&Engine1,(uint8_t*)&Engine2,(uint8_t*)&Engine3,(uint8_t*)&Engine4};

#if !(defined(__dsPIC33FJ128GP804__) || defined(__PIC24HJ128GP504__)||defined(GFX_PICTAIL_LCC)||defined(__32MX250F128D__))

    static uint32_t prevTime = 0; // keeps previous value of time tick
    uint16_t i;

#endif

    switch (screenState)
    {
        case CREATE_BUTTONS:
            prevRefreshState = CREATE_BUTTONS;
            CreateButtons(); // create window and buttons
            screenState = DISPLAY_BUTTONS; // switch to next state
            return (1); // draw objects created

        case DISPLAY_BUTTONS:
            return (1); // redraw objects if needed

        case CREATE_CHECKBOXES:
            prevRefreshState = CREATE_CHECKBOXES;
            CreateCheckBoxes(); // create window and check boxes
            screenState = DISPLAY_CHECKBOXES; // switch to next state
            return (1); // draw objects created

        case DISPLAY_CHECKBOXES:
            return (1); // redraw objects if needed

        case CREATE_RADIOBUTTONS:
            prevRefreshState = CREATE_RADIOBUTTONS;
            CreateRadioButtons(); // create window and radio buttons
            screenState = DISPLAY_RADIOBUTTONS; // switch to next state
            return (1); // draw objects created

        case DISPLAY_RADIOBUTTONS:
            return (1); // redraw objects if needed

        case CREATE_STATICTEXT:
            prevRefreshState = CREATE_STATICTEXT;
            CreateStaticText(); // and radio buttons for control
            screenState = DISPLAY_STATICTEXT; // switch to next state
            return (1); // draw objects created

        case DISPLAY_STATICTEXT:
            if ((tick - prevTick) > 40000)
            {
                pObj = GFX_GOL_ObjectFind(ID_WINDOW1);
                
                if(direction)
                {
                    GFX_GOL_WindowTextSet((GFX_GOL_WINDOW *)pObj, (GFX_XCHAR *)GroupBoxStr);   // "Group Box");
                    direction = 0;
                }
                else
                {
                    GFX_GOL_WindowTextSet((GFX_GOL_WINDOW *)pObj, (GFX_XCHAR *)StaticTextStr); // "Static text");
                    direction = 1;
                }
                 
                // redraw the whole screen
                GFX_GOL_ObjectRectangleRedraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());

                prevTick = tick;
            }
            return (1); // draw objects created

        case CREATE_SLIDER:
            prevRefreshState = CREATE_SLIDER;
            cursorUpdate = 1;
            CreateSlider(); // create window and sliders
            screenState = CURSOR_DRAW_SLIDER; // switch to next state
            return (1); // draw objects created

        case CURSOR_DRAW_SLIDER:
            DrawSliderCursor(BLACK, x, y); // draw sliders position cursor
            prevX = x;
            prevY = y;
            screenState = DISPLAY_SLIDER; // switch to next state

        case DISPLAY_SLIDER:
            if (cursorUpdate)
            {
                // hide previous position
                DrawSliderCursor(altScheme->CommonBkColor, prevX, prevY); // draw sliders position cursor
                // draw new position
                DrawSliderCursor(BLACK, x, y); // draw sliders position cursor
                prevX = x;
                prevY = y;
                cursorUpdate = 0;
            }
            return (1);

        case CREATE_PROGRESSBAR:
            CreateProgressBar(); // create window and progress bar
            screenState = DISPLAY_PROGRESSBAR; // switch to next state
            return (1); // draw objects created

        case DISPLAY_PROGRESSBAR:
            if (GFX_GOL_ObjectStateGet(pGenObj, GFX_GOL_BUTTON_PRESSED_STATE))
                wDelay = 0;
            else
                wDelay = 400;

                      if((tick - prevTick) > wDelay)
                      {
                          if(direction)
                          {
                              if(pProgressBar->pos == pProgressBar->range)
                                  direction = 0;          // change direction
                              else
                                  GFX_GOL_ProgressBarPositionSet(pProgressBar, GFX_GOL_ProgressBarPositionGet(pProgressBar) + 1); // increase
                          }
                          else
                          {
                              if(pProgressBar->pos == 0)
                                  direction = 1;  // change direction
                              else
                                   GFX_GOL_ProgressBarPositionSet(pProgressBar, GFX_GOL_ProgressBarPositionGet(pProgressBar) - 1); // decrease
                          }

                          GFX_GOL_ObjectStateSet(pProgressBar, GFX_GOL_PROGRESSBAR_DRAW_BAR_STATE);                        // redraw bar only
                          prevTick = tick;
                      }
             
            return (1); // redraw objects if needed

        case CREATE_LISTBOX:
            prevRefreshState = CREATE_LISTBOX;
            CreateListBox(); // create list box test screen
            screenState = DISPLAY_LISTBOX; // switch to next state
            return (1); // draw objects created

        case DISPLAY_LISTBOX:

            // this moves the slider and editbox for the date setting to
            // move while the up or down arrow buttons are pressed
            if ((tick - prevTick) > 5000)
            {
                pLb = (GFX_GOL_LISTBOX *) GFX_GOL_ObjectFind(ID_LISTBOX1);
                pSld = (GFX_GOL_SCROLLBAR *) GFX_GOL_ObjectFind(ID_SLIDER1);
                pObj = GFX_GOL_ObjectFind(ID_BUTTON1);

                if (GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
                {
                    GFX_GOL_ListBoxFocusedItemSet(pLb, GFX_GOL_ListBoxFocusedItemGet(pLb) - 1);
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                    GFX_GOL_ScrollBarPositionSet(pSld, GFX_GOL_ScrollBarPositionGet(pSld) + 1);
                    GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
                }

                pObj = GFX_GOL_ObjectFind(ID_BUTTON2);

                if (GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
                {
                    GFX_GOL_ListBoxFocusedItemSet(pLb, GFX_GOL_ListBoxFocusedItemGet(pLb) + 1);
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                    GFX_GOL_ScrollBarPositionSet(pSld, GFX_GOL_ScrollBarPositionGet(pSld) - 1);
                    GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
                }

                prevTick = tick;
            }

            return (1); // draw objects

        case CREATE_EDITBOX:
            prevRefreshState = CREATE_EDITBOX;
            CreateEditBox(); // create edit box test screen
            screenState = DISPLAY_EDITBOX; // switch to next state
            return (1); // draw objects created

        case DISPLAY_EDITBOX:
            return (1);

        case CREATE_METER:
            prevRefreshState = CREATE_METER;
            CreateMeter(); // create meter demo
            screenState = DISPLAY_METER; // switch to next state
            return (1); // draw objects created

        case DISPLAY_METER:
            if ((tick - prevTick) > 600)
            {
                UpdateMeter();
                prevTick = tick;
            }

            return (1); // redraw objects if needed

        case CREATE_PICTURE:
            prevRefreshState = CREATE_PICTURE;
            CreatePicture(); // create window, picture control and some check boxes
            screenState = DISPLAY_PICTURE; // switch to next state
            return (1); // draw objects created

        case DISPLAY_PICTURE:
            if (animate)
            {
                 // if animation is on change picture
                if ((tick - prevTick) > (GFX_GOL_ScrollBarPositionGet(pSlider) + 40) * 100)
                {
                    GFX_GOL_PictureStreamSet(pPicture,(uint32_t*)&pictStream,4,1);
                    prevTick = tick;
                }
            }

            return (1); // redraw objects if needed

        case CREATE_CUSTOMCONTROL:
            prevRefreshState = CREATE_CUSTOMCONTROL;
            CreateCustomControl(); // create window and custom control
            screenState = DISPLAY_CUSTOMCONTROL; // switch to next state
            return (1); // draw objects created

        case DISPLAY_CUSTOMCONTROL:
#define SX_ARROW    18
#define SY_ARROW    26
 
            if ((tick - prevTick) > 20)
            {
                arrowPos++; // change arrows' position
                if (arrowPos > 60 - SY_ARROW)
                    arrowPos = 0;

                WAIT_UNTIL_FINISH(GFX_ImageDraw(CC_ORIGIN_X + 0, CC_ORIGIN_Y + 60 - SY_ARROW - arrowPos, (void *) &arrowUp)); // draw arrows
                WAIT_UNTIL_FINISH(GFX_ImageDraw(CC_ORIGIN_X + 0, CC_ORIGIN_Y + 60 + arrowPos, (void *) &arrowDown));
                WAIT_UNTIL_FINISH(GFX_ImageDraw(CC_ORIGIN_X + 180 - SX_ARROW, CC_ORIGIN_Y + 60 - SY_ARROW - arrowPos, (void *) &arrowUp));
                WAIT_UNTIL_FINISH(GFX_ImageDraw(CC_ORIGIN_X + 180 - SX_ARROW, CC_ORIGIN_Y + 60 + arrowPos, (void *) &arrowDown));

                prevTick = tick;

                #ifdef USE_DOUBLE_BUFFERING
                InvalidateRectangle(CC_ORIGIN_X, CC_ORIGIN_Y, CC_ORIGIN_X + SX_ARROW, CC_ORIGIN_Y + 120);
                InvalidateRectangle(CC_ORIGIN_X + 180 - SX_ARROW, CC_ORIGIN_Y, CC_ORIGIN_X + 180, CC_ORIGIN_Y + 120);
                UpdateDisplayNow();
                #endif
                return(0);
            }

            return (1); // redraw objects if needed

        case CREATE_SIGNATURE:
            prevRefreshState = CREATE_SIGNATURE;
            CreateSignature(); // create window
            screenState = BOX_DRAW_SIGNATURE; // switch to next state
            return (1); // draw objects created

        case BOX_DRAW_SIGNATURE:
            if (0 == PanelSignature()) // draw box for signature
                return (0); // drawing is not completed, don't pass

            // drawing control to GOL, try it again
            screenState = DISPLAY_SIGNATURE; // switch to next state
            return (1); // pass drawing control to GOL, redraw objects if needed

        case DISPLAY_SIGNATURE:
            return (1); // redraw objects if needed

    }

    return (1); // release drawing control to GOL
}

// Shows intro screen and waits for touch

void StartScreen(void)
{
#define SS_ORIGIN_X ((GFX_MaxXGet() - 316 + 1) / 2)
#define SS_ORIGIN_Y ((GFX_MaxYGet() - 140 + 1) / 2)

    short counter;
    uint16_t i, j, k;
    uint16_t ytemp, xtemp, srRes = 0x0001;

    GFX_ColorSet(WHITE);
    while(GFX_ScreenClear() == GFX_STATUS_FAILURE);

    GFX_ImageStretchSet(IMAGE_X2);

    WAIT_UNTIL_FINISH(GFX_ImageDraw(SS_ORIGIN_X, SS_ORIGIN_Y, (GFX_RESOURCE_HDR *) &intro));

    GFX_ImageStretchSet(IMAGE_NORMAL);

    WAIT_UNTIL_FINISH(GFX_ImageDraw(0, 0, (GFX_RESOURCE_HDR *) &mchpLogo));

    for (counter = 0; counter < (GFX_MaxXGet() + 1 - 32); counter++)
    { // move Microchip icon
        WAIT_UNTIL_FINISH(GFX_ImageDraw(counter, GFX_MaxYGet() - 34, (void *) &mchpIcon0));
    }

    GFX_ColorSet(BRIGHTRED);
    GFX_FontSet((GFX_RESOURCE_HDR *) ptrLargeAsianFont);

    GFX_LinePositionSet((GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) eTouchScreenStr, (GFX_RESOURCE_HDR *) ptrLargeAsianFont)) >> 1, SS_ORIGIN_Y + 120);
    WAIT_UNTIL_FINISH(GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(),(GFX_XCHAR *) eTouchScreenStr, 0));
    GFX_LinePositionSet((GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) cTouchScreenStr, (GFX_RESOURCE_HDR *) ptrLargeAsianFont)) >> 1, SS_ORIGIN_Y + 122 + GFX_TextStringHeightGet((void *) ptrLargeAsianFont));
    WAIT_UNTIL_FINISH(GFX_TextStringDraw(GFX_LinePositionXGet(), GFX_LinePositionYGet(), (GFX_XCHAR *) cTouchScreenStr, 0));

    // wait for touch
    while (TouchGetX(0) == -1);
    //TODO: MK Removed //Beep();

    // random fade effect using a Linear Feedback Shift Register (LFSR)
    GFX_ColorSet(WHITE);
    for (i = 1800; i > 0; i--)
    {

        // for a 16 bit LFSR variable the taps are at bits: 1, 2, 4, and 15
        srRes = (srRes >> 1) ^ (-(int) (srRes & 1) & 0x8006);
        xtemp = (srRes & 0x00FF) % 40;
        ytemp = (srRes >> 8) % 30;

        // by replicating the white (1x1) bars into 8 areas fading is faster
        for (j = 0; j < 8; j++)
        {
           // for (k = 0; k < 8; k++)
              //  GFX_PixelsPut(SS_ORIGIN_X + xtemp + (j * 40), ytemp + (k * 30), 1, 1);
        }
    }

   // GFX_SetClip(CLIP_DISABLE);

}

void CreatePage(GFX_XCHAR *pText)
{
    GFX_GOL_OBJ_HEADER *obj;
#if !(defined(__dsPIC33FJ128GP804__) || defined(__PIC24HJ128GP504__)||defined(GFX_PICTAIL_LCC)||defined(__32MX250F128D__))
    short i;
#endif

    GFX_GOL_WindowCreate
            (
             
             ID_WINDOW1, // ID
             0,
             0,
             GFX_MaxXGet(),
             GFX_MaxYGet(), // dimension
             GFX_GOL_WINDOW_DRAW_STATE, // will be dislayed after creation
             (GFX_RESOURCE_HDR *) &mchpIcon, // icon
             pText, // set text
             GFX_ALIGN_LEFT,
             navScheme
             ); // default GOL scheme

    GFX_GOL_ButtonCreate
            (

             ID_BUTTON_BACK, // button ID
             0,
             40, // left, top corner
             NAV_GFX_GOL_BUTTON_WIDTH,
             GFX_MaxYGet(),
             0, // right, bottom corner (with radius = 0)
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) LeftArrowStr, // LEFT arrow as text
             GFX_ALIGN_LEFT,
             navScheme
             ); // use navigation scheme
    obj = (GFX_GOL_OBJ_HEADER *) GFX_GOL_ButtonCreate
            (

             ID_BUTTON_NEXT, // button ID
             GFX_MaxXGet() - NAV_GFX_GOL_BUTTON_WIDTH,
             40,
             GFX_MaxXGet(),
             GFX_MaxYGet(),
             0, // dimension (with radius = 0)
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed and disabled after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) RightArrowStr, // RIGHT arrow as text
             GFX_ALIGN_LEFT,
             navScheme
             ); // use navigation scheme
}

void CreateButtons(void)
{
#define GFX_GOL_BUTTON_ORIGIN_X    ((GFX_MaxXGet() - 258 + 1) / 2)
#define GFX_GOL_BUTTON_ORIGIN_Y    ((40 + GFX_MaxYGet() - 210 + 1) / 2)

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list

    CreatePage((GFX_XCHAR *) ButtonStr); //TODO: MK Removed until page supported

    GFX_GOL_ButtonCreate
            (
             
             ID_BUTTON1, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 0, // left
             GFX_GOL_BUTTON_ORIGIN_Y + 7, // top
             GFX_GOL_BUTTON_ORIGIN_X + 126, // right
             GFX_GOL_BUTTON_ORIGIN_Y + 57, // bottom
             10, // set radius
             GFX_GOL_BUTTON_DRAW_STATE, // draw a beveled button
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) ButtonStr, // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme

    GFX_GOL_ButtonCreate
            (     
             ID_BUTTON2, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 0,
             GFX_GOL_BUTTON_ORIGIN_Y + 67,
             GFX_GOL_BUTTON_ORIGIN_X + 126,
             GFX_GOL_BUTTON_ORIGIN_Y + 117, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // use bitmap
             NULL,
             (GFX_XCHAR *) HomeStr, // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_BUTTON3, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 135,
             GFX_GOL_BUTTON_ORIGIN_Y + 7,
             GFX_GOL_BUTTON_ORIGIN_X + 185,
             GFX_GOL_BUTTON_ORIGIN_Y + 117, // dimension
             25, // set radius
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_TOGGLE_STATE, // draw a vertical capsule button
             // that has a toggle behavior
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) LowStr, // text
             GFX_ALIGN_HCENTER,
             yellowScheme
             ); // use alternate scheme
    GFX_GOL_ButtonCreate
            (           
             ID_BUTTON4, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 195,
             GFX_GOL_BUTTON_ORIGIN_Y + 0,
             GFX_GOL_BUTTON_ORIGIN_X + 255,
             GFX_GOL_BUTTON_ORIGIN_Y + 60, // dimension
             30, // set radius
             GFX_GOL_BUTTON_DRAW_STATE, // draw a vertical capsule button
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) OnStr, // text
             GFX_ALIGN_HCENTER,
             greenScheme
             ); // use alternate scheme
    GFX_GOL_ButtonCreate
            (            
             ID_BUTTON5, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 195,
             GFX_GOL_BUTTON_ORIGIN_Y + 64,
             GFX_GOL_BUTTON_ORIGIN_X + 255,
             GFX_GOL_BUTTON_ORIGIN_Y + 124, // dimension
             30, // set radius
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_PRESSED_STATE, // draw a vertical capsule button
             // that is initially pressed
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) OffStr, // text
             GFX_ALIGN_HCENTER,
             redScheme
             ); // use alternate scheme
    GFX_GOL_ButtonCreate
            (             
             ID_BUTTON6, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 0,
             GFX_GOL_BUTTON_ORIGIN_Y + 127,
             GFX_GOL_BUTTON_ORIGIN_X + 126,
             GFX_GOL_BUTTON_ORIGIN_Y + 177, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation with text
             (void *) &bulbon, // use bitmap
             (void *) &bulboff,
             (GFX_XCHAR *) OffBulbStr, // text
             GFX_ALIGN_RIGHT,
             alt2Scheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (           
             ID_BUTTON7, // button ID
             GFX_GOL_BUTTON_ORIGIN_X + 132,
             GFX_GOL_BUTTON_ORIGIN_Y + 127,
             GFX_GOL_BUTTON_ORIGIN_X + 258,
             GFX_GOL_BUTTON_ORIGIN_Y + 177, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_DISABLED_STATE, // will be dislayed and disabled after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) DisabledStr, // "Disabled",  // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme
}

uint16_t MsgButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{
    GFX_GOL_OBJ_HEADER *pOtherRbtn;

    switch (GFX_GOL_ObjectIDGet(pObj))
    {

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_CHECKBOXES; // goto check box demo screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_SIGNATURE; // goto ECG demo screen
            }

            return (1); // process by default
        case ID_BUTTON3:
            if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            { // change text and scheme
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) HighStr);
            }
            else
            {
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) LowStr);
            }

            return (1); // process by default

        case ID_BUTTON4:
            if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            {
                if (!GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
                {
                    pOtherRbtn = GFX_GOL_ObjectFind(ID_BUTTON5);
                    GFX_GOL_ObjectStateClear(pOtherRbtn, GFX_GOL_BUTTON_PRESSED_STATE);
                    GFX_GOL_ObjectStateSet(pOtherRbtn, GFX_GOL_BUTTON_DRAW_STATE);
                    GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_PRESSED_STATE | GFX_GOL_BUTTON_DRAW_STATE);
                }
            }

            return (0); // Do not process by default

        case ID_BUTTON5:
            if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            {
                if (!GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
                {
                    pOtherRbtn = GFX_GOL_ObjectFind(ID_BUTTON4);
                    GFX_GOL_ObjectStateClear(pOtherRbtn, GFX_GOL_BUTTON_PRESSED_STATE);
                    GFX_GOL_ObjectStateSet(pOtherRbtn, GFX_GOL_BUTTON_DRAW_STATE);
                    GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_PRESSED_STATE | GFX_GOL_BUTTON_DRAW_STATE);
                }
            }

            return (0); // Do not process by default

        case ID_BUTTON6:
            if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            { // change face picture
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) OnBulbStr);
                GFX_GOL_ObjectStateClear(pObj, 0x00F0);
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pObj,GFX_ALIGN_BOTTOM|GFX_ALIGN_RIGHT);
            }

            if ((objMsg == GFX_GOL_BUTTON_ACTION_RELEASED) || (objMsg == GFX_GOL_BUTTON_ACTION_CANCELPRESS))
            {
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) OffBulbStr);
                GFX_GOL_ObjectStateClear(pObj, 0x00F0);
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pObj,GFX_ALIGN_TOP|GFX_ALIGN_LEFT);
            }

            return (1); // process by default
        default:
            return (1); // process by default
    }
}

void CreateCheckBoxes(void)
{
#define GFX_GOL_CHECKBOX_ORIGIN_X ((GFX_MaxXGet() - 115 + 1) / 2)
#define GFX_GOL_CHECKBOX_ORIGIN_Y ((40 + GFX_MaxYGet() - 175 + 1) / 2)

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) CheckBoxStr); // CreatePage("Checkboxes");
    GFX_GOL_CheckboxCreate
            (        
             ID_CHECKBOX1, // ID
             GFX_GOL_CHECKBOX_ORIGIN_X + 0,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 65,
             GFX_GOL_CHECKBOX_ORIGIN_X + 165,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 100, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) TextLeftStr, // "Text Left"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_CheckboxCreate
            (
             
             ID_CHECKBOX2, // ID
             GFX_GOL_CHECKBOX_ORIGIN_X + 0,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 105,
             GFX_GOL_CHECKBOX_ORIGIN_X + 165,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 140, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed and checked after creation
             (GFX_XCHAR *) TextBottomStr, // "Text Bottom"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_CheckboxCreate
            (
             
             ID_CHECKBOX3, // ID
             GFX_GOL_CHECKBOX_ORIGIN_X + 0,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 145,
             GFX_GOL_CHECKBOX_ORIGIN_X + 150,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 180, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE | GFX_GOL_CHECKBOX_DISABLED_STATE, // will be dislayed and disabled after creation
             (GFX_XCHAR *) DisabledStr, // "Disabled"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    pGenObj = (GFX_GOL_OBJ_HEADER *) GFX_GOL_ButtonCreate
            (          
             ID_BUTTON1, // button ID
             GFX_GOL_CHECKBOX_ORIGIN_X + 0,
             GFX_GOL_CHECKBOX_ORIGIN_Y - 8,
             GFX_GOL_CHECKBOX_ORIGIN_X + 115,
             GFX_GOL_CHECKBOX_ORIGIN_Y + 62, // dimension
             10, // set radius
             GFX_GOL_BUTTON_DRAW_STATE, // draw a beveled button
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) HomeLinesStr, // "Home1\nHome2" the string has two lines \n is the new line character
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme
}

uint16_t MsgCheckBoxes(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_CHECKBOX1:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            {
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pGenObj, GFX_GOL_ButtonTextAlignmentGet((GFX_GOL_BUTTON *)pGenObj)|GFX_ALIGN_LEFT);
                GFX_GOL_ObjectStateSet(pGenObj,GFX_GOL_BUTTON_DRAW_STATE); // set align left and redraw button
            }
            else
            {
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pGenObj, GFX_GOL_ButtonTextAlignmentGet((GFX_GOL_BUTTON *)pGenObj)&(0xfff0)); // clear all text alignment
                GFX_GOL_ObjectStateSet(pGenObj, GFX_GOL_BUTTON_DRAW_STATE); // set align left and redraw button
            }

            return (1); // process by default

        case ID_CHECKBOX2:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            {
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pGenObj, GFX_GOL_ButtonTextAlignmentGet((GFX_GOL_BUTTON *)pGenObj)|GFX_ALIGN_BOTTOM);
                GFX_GOL_ObjectStateSet(pGenObj, GFX_GOL_BUTTON_DRAW_STATE); // set align bottom and redraw button
            }
            else
            {
                GFX_GOL_ButtonTextAlignmentSet((GFX_GOL_BUTTON *)pGenObj, GFX_GOL_ButtonTextAlignmentGet((GFX_GOL_BUTTON *)pGenObj)&(0xff0f));
                GFX_GOL_ObjectStateSet(pGenObj, GFX_GOL_BUTTON_DRAW_STATE); // set align left and redraw button
            }

            return (1); // process by default

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_RADIOBUTTONS; // goto radio buttons screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_BUTTONS; // goto round buttons screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

void CreateRadioButtons(void)
{
#define GFX_GOL_RADIOBUTTON_ORIGIN_X ((GFX_MaxXGet() - 260 + 1) / 2)
#define GFX_GOL_RADIOBUTTON_ORIGIN_Y ((40 + GFX_MaxYGet() - 185 + 1) / 2)

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) RadioButtonStr); // CreatePage("Radio buttons");
    GFX_GOL_GroupboxCreate
            (             
             ID_GROUPBOX1, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 0,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 0,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 127,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 185, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) Group1Str, // "Group 1"
             GFX_ALIGN_CENTER,
             alt2Scheme
             ); // alternate scheme
    GFX_GOL_GroupboxCreate
            (
             
             ID_GROUPBOX2, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 130,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 0,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 260,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 185, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) Group2Str, // "Group 2"
             GFX_ALIGN_CENTER,
             alt2Scheme
             ); // alternate scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON1, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 5,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 25,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 125,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 60, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_GROUP_STATE | GFX_GOL_RADIOBUTTON_CHECKED_STATE, // will be dislayed and checked after creation
             // first button in the group
             (GFX_XCHAR *) Rb1Str, // "Rb1"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON2, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 5,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 65,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 125,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 100, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed
             (GFX_XCHAR *) Rb2Str, // "Rb2"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON3, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 5,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 105,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 125,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 140, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) Rb3Str, // "Rb3"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON4, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 5,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 145,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 125,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 180, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_DISABLED_STATE, // will be dislayed and disabled after creation
             (GFX_XCHAR *) DisabledStr, // "Disabled"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON5, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 135,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 25,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 255,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 60, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_GROUP_STATE, // will be dislayed and focused after creation
             // first button in the group
             (GFX_XCHAR *) Rb4Str, // "Rb4"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON6, // ID
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 135,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 65,
             GFX_GOL_RADIOBUTTON_ORIGIN_X + 255,
             GFX_GOL_RADIOBUTTON_ORIGIN_Y + 100, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed and checked after creation
             (GFX_XCHAR *) Rb5Str, // "Rb5"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme

    if (_language == LANG_ENGLISH)
    {
        GFX_GOL_ObjectStateSet(GFX_GOL_ObjectFind(ID_RADIOBUTTON5), GFX_GOL_RADIOBUTTON_CHECKED_STATE);
    }
    else if (_language == LANG_CHINESE)
    {
        GFX_GOL_ObjectStateSet(GFX_GOL_ObjectFind(ID_RADIOBUTTON6), GFX_GOL_RADIOBUTTON_CHECKED_STATE);
    }
}

uint16_t MsgRadioButtons(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_STATICTEXT; // goto static text screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_CHECKBOXES; // goto check boxes screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

void CreateStaticText(void)
{
#define GFX_GOL_STATICTEXT_ORIGIN_X ((GFX_MaxXGet() - 260 + 1) / 2)
#define GFX_GOL_STATICTEXT_ORIGIN_Y ((40 + GFX_MaxYGet() - 185 + 1) / 2)

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) StaticTextStr); // CreatePage("Static text");

    GFX_GOL_GroupboxCreate
            (
             
             ID_GROUPBOX1, // ID
             GFX_GOL_STATICTEXT_ORIGIN_X + 0,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 0,
             GFX_GOL_STATICTEXT_ORIGIN_X + 205,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 185, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) GroupBoxStr, // "Group Box"
             GFX_ALIGN_LEFT,
             altScheme
             ); // default GOL scheme

    GFX_GOL_StaticTextCreate
            (
             
             ID_STATICTEXT3, // ID
             GFX_GOL_STATICTEXT_ORIGIN_X + 5,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 35,
             GFX_GOL_STATICTEXT_ORIGIN_X + 195,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 175, // dimension
             GFX_GOL_STATICTEXT_DRAW_STATE | GFX_GOL_STATICTEXT_FRAME_STATE, // will be dislayed, has frame
             (GFX_XCHAR *) StaticTextLstStr, // "Microchip\nGraphics\nLibrary\nStatic Text and\nGroup Box Test.", // multi-line text
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme scheme

    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON1, // ID
             GFX_GOL_STATICTEXT_ORIGIN_X + 210,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 25,
             GFX_GOL_STATICTEXT_ORIGIN_X + 260,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 55, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_GROUP_STATE | GFX_GOL_RADIOBUTTON_CHECKED_STATE, // will be dislayed and checked after creation
             // first button in the group
             (GFX_XCHAR *) LeftStr, // "Left"
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme

    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON2, // ID
             GFX_GOL_STATICTEXT_ORIGIN_X + 210,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 65,
             GFX_GOL_STATICTEXT_ORIGIN_X + 260,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 95, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) CenterStr, // "Center"
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme
    
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON3, // ID
             GFX_GOL_STATICTEXT_ORIGIN_X + 210,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 105,
             GFX_GOL_STATICTEXT_ORIGIN_X + 260,
             GFX_GOL_STATICTEXT_ORIGIN_Y + 135, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) RightStr, // "Right"
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme

}

/* */
uint16_t MsgStaticText(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{
    GFX_GOL_GROUPBOX *pGb;
    GFX_GOL_STATICTEXT *pSt;

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_RADIOBUTTON1: // change aligment to left
            pGb = (GFX_GOL_GROUPBOX *) GFX_GOL_ObjectFind(ID_GROUPBOX1); // get pointer to group box
            GFX_GOL_ObjectStateClear(pGb, GFX_ALIGN_RIGHT | GFX_ALIGN_CENTER); // clear right and center alignment states
            GFX_GOL_ObjectStateSet(pGb, GFX_GOL_GROUPBOX_DRAW_STATE); // set redraw state
            pSt = (GFX_GOL_STATICTEXT *) GFX_GOL_ObjectFind(ID_STATICTEXT3); // get pointer to static text
            GFX_GOL_StaticTextAlignmentSet(pSt,GFX_ALIGN_LEFT);
            GFX_GOL_ObjectStateSet(pSt, GFX_GOL_STATICTEXT_DRAW_UPDATE); // set update state
            GFX_GOL_ObjectRectangleRedraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());

            return (1); // process by default

        case ID_RADIOBUTTON2:
            pGb = (GFX_GOL_GROUPBOX *) GFX_GOL_ObjectFind(ID_GROUPBOX1); // get pointer to group box
            GFX_GOL_ObjectStateClear(pGb, GFX_ALIGN_RIGHT); // clear right alignment state
            GFX_GOL_ObjectStateSet(pGb, GFX_ALIGN_CENTER | GFX_GOL_GROUPBOX_DRAW_STATE); // set center alignment and redraw states
            pSt = (GFX_GOL_STATICTEXT *) GFX_GOL_ObjectFind(ID_STATICTEXT3); // get pointer to static text
            GFX_GOL_StaticTextAlignmentSet(pSt,GFX_ALIGN_HCENTER);
            GFX_GOL_ObjectStateSet(pSt, GFX_GOL_STATICTEXT_DRAW_UPDATE); // set center alignment and update states

            GFX_GOL_ObjectRectangleRedraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());

            return (1); // process by default

        case ID_RADIOBUTTON3:
            pGb = (GFX_GOL_GROUPBOX *) GFX_GOL_ObjectFind(ID_GROUPBOX1); // get pointer to group box
            GFX_GOL_ObjectStateClear(pGb, GFX_ALIGN_CENTER); // clear center alignment state
            GFX_GOL_ObjectStateSet(pGb, GFX_ALIGN_RIGHT | GFX_GOL_GROUPBOX_DRAW_STATE); // set right alignment and redraw state
            pSt = (GFX_GOL_STATICTEXT *) GFX_GOL_ObjectFind(ID_STATICTEXT3); // get pointer to static text
            GFX_GOL_StaticTextAlignmentSet(pSt,GFX_ALIGN_RIGHT);
            GFX_GOL_ObjectStateSet(pSt, GFX_GOL_STATICTEXT_DRAW_UPDATE); // set right alignment and update states

            GFX_GOL_ObjectRectangleRedraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());

            return (1); // process by default

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_SLIDER; // goto slider screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_RADIOBUTTONS; // goto radio buttons screen
            }

            return (1); // process by default

        default:
            return (1);
    }
}

/* */
void CreateSlider(void)
{
#define GFX_GOL_SLIDER_ORIGIN_X    ((GFX_MaxXGet() - 260 + 1) / 2)
#define GFX_GOL_SLIDER_ORIGIN_Y    ((40 + GFX_MaxYGet() - 180 + 1) / 2)
#define CUR_BAR_SIZE    3                                   // half size of center point for cursor
#define CUR_BGFX_GOL_ROUNDDIAL_LEFT    GFX_GOL_SLIDER_ORIGIN_X + 37 + CUR_BAR_SIZE    // cursor area left border
#define CUR_BGFX_GOL_ROUNDDIAL_RIGHT   GFX_GOL_SLIDER_ORIGIN_X + 223 - CUR_BAR_SIZE   // cursor area right border
#define CUR_BGFX_GOL_ROUNDDIAL_TOP     GFX_GOL_SLIDER_ORIGIN_Y + 2 + CUR_BAR_SIZE     // cursor area top border
#define CUR_BGFX_GOL_ROUNDDIAL_BOTTOM  GFX_GOL_SLIDER_ORIGIN_Y + 134 - CUR_BAR_SIZE   // cursor area bottom border

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) SliderStr); //
    GFX_GOL_GroupboxCreate
            (
             
             ID_GROUPBOX1, // ID
             GFX_GOL_SLIDER_ORIGIN_X + 35,
             GFX_GOL_SLIDER_ORIGIN_Y + 0,
             GFX_GOL_SLIDER_ORIGIN_X + 225,
             GFX_GOL_SLIDER_ORIGIN_Y + 135, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE, // will be dislayed after creation
             NULL, // no text
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ScrollBarCreate
            (
             
             ID_SLIDER1, // ID
             GFX_GOL_SLIDER_ORIGIN_X + 0,
             GFX_GOL_SLIDER_ORIGIN_Y + 140,
             GFX_GOL_SLIDER_ORIGIN_X + 260,
             GFX_GOL_SLIDER_ORIGIN_Y + 170, // dimension
             GFX_GOL_SCROLLBAR_DRAW_STATE, // will be dislayed after creation
             CUR_BGFX_GOL_ROUNDDIAL_RIGHT - CUR_BGFX_GOL_ROUNDDIAL_LEFT, // range
             10, // page
             (CUR_BGFX_GOL_ROUNDDIAL_RIGHT - CUR_BGFX_GOL_ROUNDDIAL_LEFT) / 2, // pos
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ScrollBarCreate
            (
             
             ID_SLIDER2, // ID
             GFX_GOL_SLIDER_ORIGIN_X + 0,
             GFX_GOL_SLIDER_ORIGIN_Y + 0,
             GFX_GOL_SLIDER_ORIGIN_X + 30,
             GFX_GOL_SLIDER_ORIGIN_Y + 135, // dimension
             GFX_GOL_SCROLLBAR_DRAW_STATE | GFX_GOL_SCROLLBAR_VERTICAL_STATE | GFX_GOL_SCROLLBAR_DISABLED_STATE, // vertical, will be dislayed and disabled after creation
             100, // range
             100, // page
             50, // pos
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ScrollBarCreate
            (
             
             ID_SLIDER3, // ID
             GFX_GOL_SLIDER_ORIGIN_X + 230,
             GFX_GOL_SLIDER_ORIGIN_Y + 0,
             GFX_GOL_SLIDER_ORIGIN_X + 260,
             GFX_GOL_SLIDER_ORIGIN_Y + 135, // dimension
             GFX_GOL_SCROLLBAR_DRAW_STATE | GFX_GOL_SCROLLBAR_VERTICAL_STATE, // vertical, will be dislayed after creation
             CUR_BGFX_GOL_ROUNDDIAL_BOTTOM - CUR_BGFX_GOL_ROUNDDIAL_TOP, // range
             10, // page
             (CUR_BGFX_GOL_ROUNDDIAL_BOTTOM - CUR_BGFX_GOL_ROUNDDIAL_TOP) / 2, // pos
             altScheme
             ); // alternative GOL scheme

    // Set cursor to the middle
    prevX = x = (CUR_BGFX_GOL_ROUNDDIAL_RIGHT + CUR_BGFX_GOL_ROUNDDIAL_LEFT) / 2; // cursor X position
    prevY = y = (CUR_BGFX_GOL_ROUNDDIAL_BOTTOM + CUR_BGFX_GOL_ROUNDDIAL_TOP) / 2; // cursor Y position
}

// Draw sliders' position cursor

void DrawSliderCursor(uint16_t color, short xPos, short yPos)
{
    GFX_ColorSet(color);
    WAIT_UNTIL_FINISH(GFX_RectangleFillDraw(xPos - CUR_BAR_SIZE, yPos - CUR_BAR_SIZE, xPos + CUR_BAR_SIZE, yPos + CUR_BAR_SIZE));
    WAIT_UNTIL_FINISH(GFX_LineDraw(xPos, CUR_BGFX_GOL_ROUNDDIAL_TOP, xPos, CUR_BGFX_GOL_ROUNDDIAL_BOTTOM));
    WAIT_UNTIL_FINISH(GFX_LineDraw(CUR_BGFX_GOL_ROUNDDIAL_LEFT, yPos, CUR_BGFX_GOL_ROUNDDIAL_RIGHT, yPos));

#ifdef USE_DOUBLE_BUFFERING
    InvalidateAll();
#endif
}

// Process messages for slider screen

uint16_t MsgSlider(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    uint16_t id;
    GFX_GOL_SCROLLBAR *pSld;

    switch (id = GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_WINDOW1:

            // check if window is touched in cursor box area
            if
                (
                 (pMsg->param1 > CUR_BGFX_GOL_ROUNDDIAL_LEFT) &&
                 (pMsg->param1 < CUR_BGFX_GOL_ROUNDDIAL_RIGHT) &&
                 (pMsg->param2 > CUR_BGFX_GOL_ROUNDDIAL_TOP) &&
                 (pMsg->param2 < CUR_BGFX_GOL_ROUNDDIAL_BOTTOM)
                 )
            {
                // do some kind of debouncing so the lines on the screen will be stable.
                if ((abs((pMsg->param1 - x)) > 2) || (abs((pMsg->param2 - y)) > 2))
                {
                    // get new cursor x,y
                    x = pMsg->param1;
                    y = pMsg->param2;
                    cursorUpdate = 1;

                    // set new sliders positions
                    pSld = (GFX_GOL_SCROLLBAR *) GFX_GOL_ObjectFind(ID_SLIDER1); // get pointer for horizontal slider
                    GFX_GOL_ScrollBarPositionSet(pSld, x - CUR_BGFX_GOL_ROUNDDIAL_LEFT); // set new position
                    GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_STATE); // redraw thumb only
                    pSld = (GFX_GOL_SCROLLBAR *) GFX_GOL_ObjectFind(ID_SLIDER3); // get pointer for vertical slider
                    GFX_GOL_ScrollBarPositionSet(pSld, CUR_BGFX_GOL_ROUNDDIAL_BOTTOM - y); // set new position
                    GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_STATE); // redraw thumb only
                }

            }

            return (1); // process by default

        case ID_SLIDER1:
        case ID_SLIDER3:

            if ((objMsg == GFX_GOL_SCROLLBAR_ACTION_INC) || (objMsg == GFX_GOL_SCROLLBAR_ACTION_DEC))
            {
                // process message by default
                GFX_GOL_ScrollBarActionGet((GFX_GOL_SCROLLBAR *) pObj, pMsg);

                // get new X position from horizontal slider
                if (id == ID_SLIDER1)
                {
                    x = CUR_BGFX_GOL_ROUNDDIAL_LEFT + GFX_GOL_ScrollBarPositionGet((GFX_GOL_SCROLLBAR *) pObj);
                    if (x > CUR_BGFX_GOL_ROUNDDIAL_RIGHT)
                        x = CUR_BGFX_GOL_ROUNDDIAL_RIGHT;
                }

                // get new Y position from vertical slider
                if (id == ID_SLIDER3)
                {
                    y = CUR_BGFX_GOL_ROUNDDIAL_BOTTOM - GFX_GOL_ScrollBarPositionGet((GFX_GOL_SCROLLBAR *) pObj);
                    if (y < CUR_BGFX_GOL_ROUNDDIAL_TOP)
                        y = CUR_BGFX_GOL_ROUNDDIAL_TOP;
                }
                cursorUpdate = 1;
            }
            return (0); // it was processed

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_PROGRESSBAR; // goto progress bar screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_STATICTEXT; // goto static text screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

// Creates progress bar screen

void CreateProgressBar(void)
{
 uint16_t GFX_GOL_PROGRESSBAR_ORIGIN_X = ((GFX_MaxXGet() - 240 + 1) / 2);
 uint16_t GFX_GOL_PROGRESSBAR_ORIGIN_Y = ((40 + GFX_MaxYGet() - 130 + 1) / 2);

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list

    CreatePage((GFX_XCHAR *) ProgressBarStr); //

    pProgressBar = GFX_GOL_ProgressBarCreate
            (
             
             ID_PROGRESSBAR1, // ID
             GFX_GOL_PROGRESSBAR_ORIGIN_X + 0,
             GFX_GOL_PROGRESSBAR_ORIGIN_Y + 0,
             GFX_GOL_PROGRESSBAR_ORIGIN_X + 240,
             GFX_GOL_PROGRESSBAR_ORIGIN_Y + 50, // dimension
             GFX_GOL_PROGRESSBAR_DRAW_STATE, // will be dislayed after creation
             25, // position
             50, // range
             altScheme
             ); // use default scheme
       GFX_GOL_StaticTextCreate
       (
           
           ID_STATICTEXT3,             // ID
           GFX_GOL_PROGRESSBAR_ORIGIN_X + 30,
           GFX_GOL_PROGRESSBAR_ORIGIN_Y + 70,
           GFX_GOL_PROGRESSBAR_ORIGIN_X + 185,
           GFX_GOL_PROGRESSBAR_ORIGIN_Y + 130,          // dimension
           GFX_GOL_STATICTEXT_DRAW_STATE,  // display text
           (GFX_XCHAR *)PIC24SpeedStr,     // text
           GFX_ALIGN_HCENTER,
           altScheme
       );      // use alternate scheme
    pGenObj = (GFX_GOL_OBJ_HEADER *) GFX_GOL_ButtonCreate
            (
             
             ID_BUTTON1, // button ID
             GFX_GOL_PROGRESSBAR_ORIGIN_X + 180,
             GFX_GOL_PROGRESSBAR_ORIGIN_Y + 83,
             GFX_GOL_PROGRESSBAR_ORIGIN_X + 220,
             GFX_GOL_PROGRESSBAR_ORIGIN_Y + 113, // dimension
             10, // set radius
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_TOGGLE_STATE, // draw button
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) QuestionStr, // "?",
             GFX_ALIGN_HCENTER,// text
             altScheme
             ); // use alternate scheme
}

// Processes messages for progress bar screen

uint16_t MsgProgressBar(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_LISTBOX; // goto list box screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_SLIDER; // goto slider screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

#define pMyItemList (GFX_XCHAR*)ListboxLstStr

void CreateListBox(void)
{
    GFX_GOL_LISTBOX *pLb;

#define GFX_GOL_LISTBOX_ORIGIN_X ((GFX_MaxXGet() - 260 + 1) / 2)
#define GFX_GOL_LISTBOX_ORIGIN_Y ((40 + GFX_MaxYGet() - 192 + 1) / 2)

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) ListBoxStr); //
    pLb = (GFX_GOL_LISTBOX*)GFX_GOL_ListboxCreate
            (
             ID_LISTBOX1, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 10,
             GFX_GOL_LISTBOX_ORIGIN_Y + 52,
             GFX_GOL_LISTBOX_ORIGIN_X + 220,
             GFX_GOL_LISTBOX_ORIGIN_Y + 192, // dimension
             GFX_GOL_LISTBOX_DRAW_STATE | GFX_GOL_LISTBOX_FOCUSED_STATE, // will be dislayed after creation
             pMyItemList,
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme
    GFX_GOL_ScrollBarCreate
            (
             
             ID_SLIDER1, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 220,
             GFX_GOL_LISTBOX_ORIGIN_Y + 82,
             GFX_GOL_LISTBOX_ORIGIN_X + 250,
             GFX_GOL_LISTBOX_ORIGIN_Y + 160, // dimension
             GFX_GOL_SCROLLBAR_DRAW_STATE | GFX_GOL_SCROLLBAR_SLIDER_MODE_STATE | GFX_GOL_SCROLLBAR_VERTICAL_STATE, // vertical, will be dislayed after creation
             GFX_GOL_ListBoxItemCountGet(pLb), // range
             1, // page
             GFX_GOL_ListBoxItemCountGet(pLb) - 1, // pos
             altScheme
             ); // use alternate scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_BUTTON1, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 220,
             GFX_GOL_LISTBOX_ORIGIN_Y + 52,
             GFX_GOL_LISTBOX_ORIGIN_X + 250,
             GFX_GOL_LISTBOX_ORIGIN_Y + 82,
             0, // dimension (no radius)
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) UpArrowStr, // Up Arrow
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_BUTTON2, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 220,
             GFX_GOL_LISTBOX_ORIGIN_Y + 162,
             GFX_GOL_LISTBOX_ORIGIN_X + 250,
             GFX_GOL_LISTBOX_ORIGIN_Y + 192,
             0, // dimension (no radius)
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) DownArrowStr, // Down Arrow
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme
    GFX_GOL_CheckboxCreate
            (
             
             ID_CHECKBOX1, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 10,
             GFX_GOL_LISTBOX_ORIGIN_Y + 20,
             GFX_GOL_LISTBOX_ORIGIN_X + 110,
             GFX_GOL_LISTBOX_ORIGIN_Y + 45, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) SingleStr, // "Single"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_CheckboxCreate
            (            
             ID_CHECKBOX2, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 140,
             GFX_GOL_LISTBOX_ORIGIN_Y + 20,
             GFX_GOL_LISTBOX_ORIGIN_X + 240,
             GFX_GOL_LISTBOX_ORIGIN_Y + 45, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) AlignCenterStr, // "Center"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_GroupboxCreate
            (
             
             ID_GROUPBOX1, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 0,
             GFX_GOL_LISTBOX_ORIGIN_Y + 0,
             GFX_GOL_LISTBOX_ORIGIN_X + 127,
             GFX_GOL_LISTBOX_ORIGIN_Y + 50, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) SelectionStr, // "Selection"
             GFX_ALIGN_CENTER,
             alt4Scheme
             ); // alternate scheme
    GFX_GOL_GroupboxCreate
            (
             
             ID_GROUPBOX2, // ID
             GFX_GOL_LISTBOX_ORIGIN_X + 130,
             GFX_GOL_LISTBOX_ORIGIN_Y + 0,
             GFX_GOL_LISTBOX_ORIGIN_X + 260,
             GFX_GOL_LISTBOX_ORIGIN_Y + 50, // dimension
             GFX_GOL_GROUPBOX_DRAW_STATE,  // will be dislayed after creation
             (GFX_XCHAR *) AlignmentStr, // "Alignment"
             GFX_ALIGN_CENTER,
             alt4Scheme
             ); // alternate scheme
}

// processes messages for list box demo screen

uint16_t MsgListBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_LISTBOX *pLb;
    GFX_GOL_SCROLLBAR *pSld;

    pLb = (GFX_GOL_LISTBOX *) GFX_GOL_ObjectFind(ID_LISTBOX1);
    pSld = (GFX_GOL_SCROLLBAR *) GFX_GOL_ObjectFind(ID_SLIDER1);

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_LISTBOX1:

            // Process message by default
            GFX_GOL_ListBoxActionSet(objMsg, (GFX_GOL_LISTBOX *) pObj, pMsg);

            // Set new list box position
            GFX_GOL_ScrollBarPositionSet(pSld, GFX_GOL_ListBoxItemCountGet(pLb) - GFX_GOL_ListBoxFocusedItemGet(pLb));
            GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);

            // The message was processed
            return (0);

        case ID_SLIDER1:

            if ((objMsg == GFX_GOL_SCROLLBAR_ACTION_INC) || (objMsg == GFX_GOL_SCROLLBAR_ACTION_DEC))
            {
                // Process message by default
                GFX_GOL_ScrollBarActionGet((GFX_GOL_SCROLLBAR *) pObj, pMsg);

                // Set new list box position
                if (GFX_GOL_ListBoxFocusedItemGet(pLb) != GFX_GOL_ListBoxItemCountGet(pLb) - GFX_GOL_ScrollBarPositionGet(pSld))
                {
                    GFX_GOL_ListBoxFocusedItemSet(pLb, GFX_GOL_ListBoxItemCountGet(pLb) - GFX_GOL_ScrollBarPositionGet(pSld));
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                }
            }

            // The message was processed
            return (0);

        case ID_BUTTON1:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                GFX_GOL_ListBoxFocusedItemSet(pLb, GFX_GOL_ListBoxFocusedItemGet(pLb) - 1);
                GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                GFX_GOL_ScrollBarPositionSet(pSld, GFX_GOL_ScrollBarPositionGet(pSld) + 1);
                GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
            }

            return (1);

        case ID_BUTTON2:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                GFX_GOL_ListBoxFocusedItemSet(pLb, GFX_GOL_ListBoxFocusedItemGet(pLb) + 1);
                GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                GFX_GOL_ScrollBarPositionSet(pSld, GFX_GOL_ScrollBarPositionGet(pSld) - 1);
                GFX_GOL_ObjectStateSet(pSld, GFX_GOL_SCROLLBAR_DRAW_THUMB_STATE);
            }

            return (1);

        case ID_CHECKBOX1:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            {
                GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_SINGLE_SELECT_STATE | GFX_GOL_LISTBOX_DRAW_STATE);
                GFX_GOL_ListBoxSelectionChange(pLb, pLb->pFocusItem);
            }
            else
            {
                GFX_GOL_ObjectStateClear(pLb, GFX_GOL_LISTBOX_SINGLE_SELECT_STATE);
            }

            return (1);

        case ID_CHECKBOX2:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            {
                pLb->alignment = GFX_ALIGN_HCENTER;
            }
            else
            {
                pLb->alignment = GFX_ALIGN_LEFT;
            }

            GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_STATE);
            return (1);

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_EDITBOX; // goto edit box screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_PROGRESSBAR; // goto progress bar screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

// Creates the edit box demo screen

void CreateEditBox(void)
{
    static GFX_XCHAR pTempXchar[][2] = {
        {'0', 0},
        {'1', 0},
        {'2', 0},
        {'3', 0},
        {'4', 0},
        {'5', 0},
        {'6', 0},
        {'7', 0},
        {'8', 0},
        {'9', 0},
        {'*', 0},
        {'#', 0}
    };

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) EditBoxStr);

#define GFX_GOL_EDITBOX_ORIGIN_X ((GFX_MaxXGet() - 212 + 1) / 2)
#define GFX_GOL_EDITBOX_ORIGIN_Y ((40 + GFX_MaxYGet() - 195 + 1) / 2)
#define KEYSTARTX   GFX_GOL_EDITBOX_ORIGIN_X
#define KEYSTARTY   GFX_GOL_EDITBOX_ORIGIN_Y
#define KEYSIZEX    53
#define KEYSIZEY    39
#define MAXCHARSIZE 17

    GFX_GOL_EditBoxCreate
            (
             
             ID_EDITBOX1, // ID
             KEYSTARTX,
             KEYSTARTY + 1,
             KEYSTARTX + 4 * KEYSIZEX,
             KEYSTARTY + 1 * KEYSIZEY - GFX_GOL_EMBOSS_SIZE, // dimension
             GFX_GOL_EDITBOX_DRAW_STATE, // will be dislayed after creation
             NULL,
             MAXCHARSIZE,
             GFX_ALIGN_LEFT,
             altScheme
             ); // default GOL scheme
 
   GFX_GOL_ButtonCreate
            (           
             ID_KEYPAD + 0, // ID
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY,
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 5 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[0], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (           
             ID_KEYPAD + 1, // ID
             KEYSTARTX + 0 * KEYSIZEX,
             KEYSTARTY + 1 * KEYSIZEY,
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[1], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (           
             ID_KEYPAD + 2, // ID
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 1 * KEYSIZEY,
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[2], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (             
             ID_KEYPAD + 3, // ID
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 1 * KEYSIZEY,
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[3], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 4, // ID
             KEYSTARTX + 0 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY,
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[4], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 5, // ID
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY,
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[5], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 6, // ID
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY,
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[6], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 7, // ID
             KEYSTARTX + 0 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY,
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[7], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 8, // ID
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY,
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[8], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_KEYPAD + 9, // ID
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY,
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[9], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_ASTERISK, // ID
             KEYSTARTX + 0 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY,
             KEYSTARTX + 1 * KEYSIZEX,
             KEYSTARTY + 5 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[10], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_POUND, // ID
             KEYSTARTX + 2 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY,
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 5 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             pTempXchar[11], // text
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_BACKSPACE, // ID
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 1 * KEYSIZEY,
             KEYSTARTX + 4 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL,
             NULL, // no bitmap
             (GFX_XCHAR *) LeftArrowStr, // Left Arrow
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_CALL, // ID
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 2 * KEYSIZEY,
             KEYSTARTX + 4 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             (void *) &greenphone, // use green phone bitmap
             (void *) &greenphone,
             NULL, // text
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (
             
             ID_STOPCALL, // ID
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 3 * KEYSIZEY,
             KEYSTARTX + 4 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             (void *) &redphone, // use redphone bitmap
             (void *) &redphone,
             NULL, // text
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
    GFX_GOL_ButtonCreate
            (            
             ID_HOLD, // ID
             KEYSTARTX + 3 * KEYSIZEX,
             KEYSTARTY + 4 * KEYSIZEY,
             KEYSTARTX + 4 * KEYSIZEX,
             KEYSTARTY + 5 * KEYSIZEY, // dimension
             0,
             GFX_GOL_BUTTON_DRAW_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) HoldStr, // "Hld"
             GFX_ALIGN_HCENTER,
             altScheme
             ); // alternative GOL scheme
}

// Processes messages for the edit box demo screen

uint16_t MsgEditBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_EDITBOX *pEb;
    short id;
    GFX_XCHAR temp;
    static char status = 0; // status to check if calling, holding or not
    id = GFX_GOL_ObjectIDGet(pObj);

    // ignore all touch screen messages to the edit box
    // since we do not want the caret to show up
    if ((id == ID_EDITBOX1) && (pMsg->type == TYPE_TOUCHSCREEN))
    {
        return 0;
    }

    // If number key is pressed
    if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
    {
        if (id >= ID_KEYPAD)
            if (id < ID_KEYPAD + 10)
            {
                if (!status)
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharAdd(pEb, '0' + id - ID_KEYPAD);
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }

                return (1);
            }

        switch (id)
        {
            case ID_CALL:
                pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                GFX_GOL_EditBoxTextSet(pEb, (GFX_XCHAR *) CallingStr);
                GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                status = 1;
                break;

            case ID_STOPCALL:
                pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                temp = 0x0000;
                GFX_GOL_EditBoxTextSet(pEb, &temp);
                GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                status = 0;
                break;

            case ID_BACKSPACE:
                if (!status)
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharRemove(pEb);
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }
                break;

            case ID_HOLD:
                pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                if (status == 1)
                {
                    GFX_GOL_EditBoxTextSet(pEb, (GFX_XCHAR *) HoldingStr);
                    status = 2;
                }
                else if (status == 2)
                {
                    GFX_GOL_EditBoxTextSet(pEb, (GFX_XCHAR *) CallingStr);
                    status = 1;
                }

                GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                break;

            case ID_ASTERISK:
                if (!status)
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharAdd(pEb, (GFX_XCHAR) '*');
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }
                break;

            case ID_POUND:
                if (!status)
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharAdd(pEb, (GFX_XCHAR) '#');
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }
                break;

            case ID_BUTTON_NEXT:
                screenState = CREATE_METER; // goto meter screen
                status = 0;
                break;

            case ID_BUTTON_BACK:
                screenState = CREATE_LISTBOX; // goto list box screen
                status = 0;
                break;

            default:
                break;
        }
    }
    return (1); // process by default
}

#define MAXMETER1VALUE  150
#define MAXMETER2VALUE  300

#define MINMETER1VALUE  0
#define MINMETER2VALUE  0

// Creates meter screen

void CreateMeter(void)
{
#define GFX_GOL_METER_ORIGIN_X    ((GFX_MaxXGet() - 260 + 1) / 2)
#define GFX_GOL_METER_ORIGIN_Y    (((40 + GFX_MaxYGet() - 180 + 1) / 2) - 10)

    GFX_GOL_METER *pMtr;

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) MeterStr); // CreatePage("Meter");

    pMtr = GFX_GOL_MeterCreate
            (             
             ID_METER1,
             GFX_GOL_METER_ORIGIN_X + 0,
             GFX_GOL_METER_ORIGIN_Y + 0,
             GFX_GOL_METER_ORIGIN_X + 128,
             GFX_GOL_METER_ORIGIN_Y + 130, // set dimension
             GFX_GOL_METER_DRAW_STATE | GFX_GOL_METER_RING_STATE | GFX_GOL_METER_ACCURACY_STATE, // draw meter object with ring scale & accuracy set
             GFX_GOL_METER_WHOLE_TYPE,
             MINMETER1VALUE, // set initial value
             MINMETER1VALUE, // meter minimum value
             MAXMETER1VALUE, // meter maximum value
             (GFX_RESOURCE_HDR*)&GOLFontDefault,
             (GFX_RESOURCE_HDR*)&GOLFontDefault,
             (GFX_XCHAR *) Meter1Str, // "METER1"
             meterScheme
             ); // alternative GOL scheme

    // set scaling values
    GFX_GOL_MeterScaleColorsSet(pMtr, BRIGHTGREEN, BRIGHTGREEN, BRIGHTGREEN, BRIGHTGREEN, BRIGHTYELLOW, BRIGHTRED);

    pMtr = GFX_GOL_MeterCreate
            (
             
             ID_METER2,
             GFX_GOL_METER_ORIGIN_X + 130,
             GFX_GOL_METER_ORIGIN_Y + 0,
             GFX_GOL_METER_ORIGIN_X + 258,
             GFX_GOL_METER_ORIGIN_Y + 130, // set dimension
             GFX_GOL_METER_DRAW_STATE | GFX_GOL_METER_RING_STATE | GFX_GOL_METER_ACCURACY_STATE, // draw meter object with ring scale & accuracy set
             GFX_GOL_METER_WHOLE_TYPE,
             MINMETER2VALUE, // set initial value
             MINMETER2VALUE, // set minimum value
             MAXMETER2VALUE, // set maximum value
             (GFX_RESOURCE_HDR*)&GOLFontDefault,
             (GFX_RESOURCE_HDR*)&GOLFontDefault,
             (GFX_XCHAR *) Meter2Str, // "METER2"
             meterScheme
             ); // alternative GOL scheme

        // set scaling values
    GFX_GOL_MeterScaleColorsSet(pMtr, BRIGHTGREEN, BRIGHTGREEN, BRIGHTGREEN, BRIGHTGREEN, BRIGHTYELLOW, BRIGHTRED);


            GFX_GOL_DigitalMeterCreate
            (

             ID_DIGITALMETER1,
             GFX_GOL_METER_ORIGIN_X + 20,
             GFX_GOL_METER_ORIGIN_Y + 140, // left, top corner
             GFX_GOL_METER_ORIGIN_X + 100,
             GFX_GOL_METER_ORIGIN_Y + 160, // right, bottom corner
             GFX_GOL_DIGITALMETER_DRAW_STATE | GFX_GOL_DIGITALMETER_FRAME_STATE,
             0,
             3,
             1,
             GFX_ALIGN_CENTER,
             alt5Scheme
             );

    GFX_GOL_DigitalMeterCreate
            (

             ID_DIGITALMETER2,
             GFX_GOL_METER_ORIGIN_X + 150,
             GFX_GOL_METER_ORIGIN_Y + 140, // left, top corner
             GFX_GOL_METER_ORIGIN_X + 230,
             GFX_GOL_METER_ORIGIN_Y + 160, // right, bottom corner
             GFX_GOL_DIGITALMETER_DRAW_STATE | GFX_GOL_DIGITALMETER_FRAME_STATE,
             0,
             2,
             0,
             GFX_ALIGN_CENTER,
             alt5Scheme
             );

    GFX_GOL_ButtonCreate
            (           
             ID_BUTTON1, // button ID
             GFX_GOL_METER_ORIGIN_X + 20,
             GFX_GOL_METER_ORIGIN_Y + 165, // left, top corner
             GFX_GOL_METER_ORIGIN_X + 100,
             GFX_GOL_METER_ORIGIN_Y + 195, // right, bottom corner
             0, // draw rectangular button
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_TOGGLE_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) DecelStr, // decelerate
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme

    GFX_GOL_ButtonCreate
            (         
             ID_BUTTON2, // button ID
             GFX_GOL_METER_ORIGIN_X + 150,
             GFX_GOL_METER_ORIGIN_Y + 165, // left, top corner
             GFX_GOL_METER_ORIGIN_X + 230,
             GFX_GOL_METER_ORIGIN_Y + 195, // right, bottom corner
             0, // draw rectangular button
             GFX_GOL_BUTTON_DRAW_STATE | GFX_GOL_BUTTON_TOGGLE_STATE, // will be dislayed after creation
             NULL, // no bitmap
             NULL,
             (GFX_XCHAR *) DecelStr, // decelerate
             GFX_ALIGN_HCENTER,
             altScheme
             ); // use alternate scheme

}

// Processes messages for meter screen

uint16_t MsgMeter(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
//                screenState = CREATE_DIAL; // goto dial screen
                screenState = CREATE_PICTURE; // goto picture control screen
            }

            return (1); // process by default

        case ID_BUTTON1:
        case ID_BUTTON2:
            if (objMsg == GFX_GOL_BUTTON_ACTION_PRESSED)
            {
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) AccelStr); // set text to accelerate
            }

            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) DecelStr); // set text to decelerate
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_EDITBOX; // goto edit box screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

// this updates the meters on the screen

void UpdateMeter(void)
{
    GFX_GOL_OBJ_HEADER *pObj, *pDigMtrObj1, *pDigMtrObj2;
    GFX_GOL_METER *pMtrObj;
    uint16_t i, value;

    pDigMtrObj1 = GFX_GOL_ObjectFind(ID_DIGITALMETER1);
    pDigMtrObj2 = GFX_GOL_ObjectFind(ID_DIGITALMETER2);

    /* Meter 1 is controlled by ID_BUTTON1
           Meter 2 is controlled by ID_BUTTON2
           Both meters goes from 0 to maximum when their respective
           buttons are pressed.	Both button have a toggle property. So
           when pressed it will remain to be pressed until the meter has reached
           the maximum value. The only difference is that ID_BUTTON1 is controlled
           by the code while ID_BUTTON2 is manually controlled.
     */
    //    for (i = ID_BUTTON1; i < ID_BUTTON2 + 1; i++)
    //    {
    //        pObj = GFX_GOL_ObjectFind(i);
    //
    //        if (i == ID_BUTTON1)
    //        {
    pObj = GFX_GOL_ObjectFind(ID_BUTTON1);

    pMtrObj = (GFX_GOL_METER *) GFX_GOL_ObjectFind(ID_METER1); // get meter 1 pointer
    value = GFX_GOL_MeterValueGet(pMtrObj); // get current value
    if (value == MINMETER1VALUE)
    { // when zero turn on ID_BUTTON1
        GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) AccelStr); // set text to accelerate
        GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_PRESSED_STATE | GFX_GOL_BUTTON_DRAW_STATE);
    }

    if (value == MAXMETER1VALUE)
    { // when maximum turn off ID_BUTTON1
        GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) DecelStr); // set text to decelerate
        GFX_GOL_ObjectStateClear(pObj, GFX_GOL_BUTTON_PRESSED_STATE);
        GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_DRAW_STATE);
    }

    if (GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE)) // increment meter value when button
        value += 2; // is pressed
    else
        value -= 2;
    GFX_GOL_MeterValueSet(pMtrObj, value); // decrement meter value when button
    GFX_GOL_DigitalMeterValueSet((GFX_GOL_DIGITALMETER *) pDigMtrObj1, value);
    GFX_GOL_ObjectStateSet(pDigMtrObj1, GFX_GOL_DIGITALMETER_UPDATE_STATE);
    GFX_GOL_ObjectStateSet(pMtrObj, GFX_GOL_METER_UPDATE_DRAW_STATE); // is released
    //        }
    //        else
    //        {
    pObj = GFX_GOL_ObjectFind(ID_BUTTON2);

    pMtrObj = (GFX_GOL_METER *) GFX_GOL_ObjectFind(ID_METER2); // get meter 2 pointer
    value = GFX_GOL_MeterValueGet(pMtrObj); // get meter current value
    if (GFX_GOL_ObjectStateGet(pObj, GFX_GOL_BUTTON_PRESSED_STATE))
    { // check if ID_BUTTON2 is pressed
        GFX_GOL_MeterValueSet(pMtrObj, value + 1); // increment value of meter
        GFX_GOL_DigitalMeterValueSet((GFX_GOL_DIGITALMETER *) pDigMtrObj2, GFX_GOL_MeterValueGet(pMtrObj));
        GFX_GOL_ObjectStateSet(pMtrObj, GFX_GOL_METER_UPDATE_DRAW_STATE); // redraw meter
        GFX_GOL_ObjectStateSet(pDigMtrObj2, GFX_GOL_DIGITALMETER_UPDATE_STATE);
    }
    else
    {
        if (value > 0)
        { // if ID_BUTTON2 is released
            GFX_GOL_MeterValueSet(pMtrObj, value - 1); // decrement meter if not yet zero
            GFX_GOL_DigitalMeterValueSet((GFX_GOL_DIGITALMETER *) pDigMtrObj2, GFX_GOL_MeterValueGet(pMtrObj));
            GFX_GOL_ObjectStateSet(pMtrObj, GFX_GOL_METER_UPDATE_DRAW_STATE); // redraw meter
            GFX_GOL_ObjectStateSet(pDigMtrObj2, GFX_GOL_DIGITALMETER_UPDATE_STATE);
        }
    }

    if (value == MAXMETER2VALUE)
    { // check if meter 2 reached max value
        GFX_GOL_ObjectStateClear(pObj, GFX_GOL_BUTTON_PRESSED_STATE); // release ID_BUTTON2 when max is reached
        GFX_GOL_ButtonTextSet((GFX_GOL_BUTTON *) pObj, (GFX_XCHAR *) DecelStr); // set text to decelerate
        GFX_GOL_ObjectStateSet(pObj, GFX_GOL_BUTTON_DRAW_STATE); // redraw button
        //            }
        //        }
    }
}

// Creates dial screen

//void CreateDial(void)
//{
//#define DIAL_ORIGIN_X   ((GFX_MaxXGet() - 247 + 1) / 2)
//#define DIAL_ORIGIN_Y   ((40 + GFX_MaxYGet() - 143 + 1) / 2)
//
//    GFX_ImageStretchSet(IMAGE_NORMAL);
//    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
//
//    CreatePage((GFX_XCHAR *) DialStr); //
//    GFX_GOL_RoundDialCreate
//            (
//
//             ID_ROUNDDIAL, // ID
//             DIAL_ORIGIN_X + 50,
//             DIAL_ORIGIN_Y + 72,
//             55, // dimensions
//             GFX_GOL_ROUNDDIAL_DRAW, // draw after creation
//             1, // resolution
//             400, // initial value
//             700, // maximum value
//             altScheme
//             ); // use alternative scheme
//    GFX_GOL_MeterCreate
//            (
//
//             ID_METER1,
//             DIAL_ORIGIN_X + 112,
//             DIAL_ORIGIN_Y + 0,
//             DIAL_ORIGIN_X + 247,
//             DIAL_ORIGIN_Y + 135, // set dimension
//             GFX_GOL_METER_DRAW, // draw object after creation
//             400, // set initial value
//             0, // set minimum value
//             700, // set maximum value
//             (void *) &GOLFontDefault, // set title font
//             (void *) &GOLSmallFont, // set value font
//             (GFX_XCHAR *) ValueLabelStr, // "VALUE"
//             NULL,
//             meterScheme
//             ); // alternative GOL scheme
//
//    // set scaling values
//    GFX_GOL_MeterScaleColorsSet
//            (
//             ((GFX_GOL_METER *) GFX_GOL_ObjectFind(ID_METER1)),
//             BRIGHTGREEN,
//             BRIGHTGREEN,
//             BRIGHTGREEN,
//             BRIGHTBLUE,
//             BRIGHTYELLOW,
//             BRIGHTRED
//             );
//}
//
//// Processes messages for dial screen
//
//uint16_t MsgDial(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
//{
//    GFX_GOL_OBJ_HEADER *pMtrObj;
//    short dialVal;
//
//    switch (GFX_GOL_ObjectIDGet(pObj))
//    {
//        case ID_ROUNDDIAL:
//            dialVal = GFX_GOL_RoundDialValueGet((GFX_GOL_ROUNDDIAL *) pObj);
//            pMtrObj = GFX_GOL_ObjectFind(ID_METER1);
//            GFX_GOL_MeterValueSet((GFX_GOL_METER *) pMtrObj, dialVal);
//            GFX_GOL_ObjectStateSet(pMtrObj, GFX_GOL_METER_DRAW_UPDATE);
//            if (objMsg == GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE)
//                if (dialVal == 700)
//                    return (0);
//            if (objMsg == GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE)
//                if (dialVal == 0)
//                    return (0);
//
//            dialVal = (dialVal - 1) % 70; // -1 is used to avoid 70 which is also 0 after mod.
//            break; // process by default
//
//        case ID_BUTTON_NEXT:
//            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
//            {
//                screenState = CREATE_PICTURE; // goto picture control screen
//            }
//
//            break; // process by default
//
//        case ID_BUTTON_BACK:
//            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
//            {
//                screenState = CREATE_METER; // goto meter screen
//            }
//
//            break; // process by default
//
//        default:
//            break; // process by default
//    }
//
//    return (1);
//}

/* */
void CreatePicture(void)
{

uint16_t PIC_ORIGIN_X = ((GFX_MaxXGet() - 190 + 1) / 2);
uint16_t PIC_ORIGIN_Y = ((40 + GFX_MaxYGet() - 170 + 1) / 2);

    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list

    CreatePage((GFX_XCHAR *) PictureStr); // CreatePage("Picture control");

    pPicture = GFX_GOL_PictureControlCreate
            (
             
             ID_PICTURE1, // ID
             PIC_ORIGIN_X + 0,
             PIC_ORIGIN_Y + 0,
             PIC_ORIGIN_X + 155,
             PIC_ORIGIN_Y + 120, // dimension
             GFX_GOL_PICTURECONTROL_DRAW_STATE | GFX_GOL_PICTURECONTROL_FRAME_STATE, // will be dislayed, has frame
             1, // scale factor is x1
             (void*)&Engine1, // bitmap
             altScheme
             ); // default GOL scheme

    pSlider = GFX_GOL_ScrollBarCreate
            (
             
             ID_SLIDER1, // ID
             PIC_ORIGIN_X + 160,
             PIC_ORIGIN_Y + 0,
             PIC_ORIGIN_X + 190,
             PIC_ORIGIN_Y + 120, // dimension
             GFX_GOL_SCROLLBAR_DRAW_STATE | GFX_GOL_SCROLLBAR_DISABLED_STATE | GFX_GOL_SCROLLBAR_VERTICAL_STATE, // draw with disabled state
             50, // range
             1, // page
             25, // pos
             altScheme
             ); // alternative GOL scheme

    GFX_GOL_CheckboxCreate
            (            
             ID_CHECKBOX1, // ID
             PIC_ORIGIN_X - 20,
             PIC_ORIGIN_Y + 130,
             PIC_ORIGIN_X + 80,
             PIC_ORIGIN_Y + 170, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) ScaleStr, // "Scale"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme

    GFX_GOL_CheckboxCreate
            (            
             ID_CHECKBOX2, // ID
             PIC_ORIGIN_X + 90,
             PIC_ORIGIN_Y + 130,
             PIC_ORIGIN_X + 220,
             PIC_ORIGIN_Y + 170, // dimension
             GFX_GOL_CHECKBOX_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) AnimateStr, // "Animate"
             GFX_ALIGN_LEFT,
             altScheme
             ); // alternative GOL scheme
}

/* */
uint16_t MsgPicture(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj)
{
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_CHECKBOX1:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            { // set new scale factor
                GFX_GOL_PictureControlScaleSet(pPicture, 2); // x2
            }
            else
            {
                GFX_GOL_PictureControlScaleSet(pPicture, 1); // x1
            }

            GFX_GOL_ObjectStateSet(pPicture, GFX_GOL_PICTURECONTROL_DRAW_STATE); // set redraw state
            return (1); // process by default

        case ID_CHECKBOX2:
            if (objMsg == GFX_GOL_CHECKBOX_ACTION_CHECKED)
            { // switch on/off animation
                GFX_GOL_ObjectStateClear(pSlider, GFX_GOL_SCROLLBAR_DISABLED_STATE); // enable slider
                GFX_GOL_ObjectStateSet(pSlider, GFX_GOL_SCROLLBAR_DRAW_STATE); // redraw slider to show new state
                animate = 1;
            }
            else
            {
                GFX_GOL_ObjectStateSet(pSlider, GFX_GOL_SCROLLBAR_DISABLED_STATE | GFX_GOL_SCROLLBAR_DRAW_STATE); // disable the slider and redraw
                animate = 0;
            }

            return (1); // process by default

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_CUSTOMCONTROL; // goto cutom control screen
                animate = 0; // switch off animation
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
//                screenState = CREATE_DIAL; // goto dial screen
                screenState = CREATE_METER; // goto meter screen
                animate = 0; // switch off animation
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

// Creates custom control screen

void CreateCustomControl(void)
{
    GFX_ImageStretchSet(IMAGE_NORMAL);
    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) CustomStr); // CreatePage("Custom control");
    GFX_GOL_CustomControlCreate
            (
             
             ID_CUSTOM1, // ID
             CC_ORIGIN_X + 30,
             CC_ORIGIN_Y + 0,
             CC_ORIGIN_X + 150,
             CC_ORIGIN_Y + 120, // dimension
             GFX_GOL_CUSTOMCONTROL_DRAW, // will be dislayed after creation
             alt3Scheme
             ); // use alternate 3 scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON1, // ID
             CC_ORIGIN_X - 20,
             CC_ORIGIN_Y + 130,
             CC_ORIGIN_X + 80,
             CC_ORIGIN_Y + 150, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_GROUP_STATE, // will be dislayed and focused after creation
             // first button in the group
             (GFX_XCHAR *) HeavyLoadStr, // "Heavy Load"
             GFX_ALIGN_LEFT,
             alt2Scheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON2, // ID
             CC_ORIGIN_X - 20,
             CC_ORIGIN_Y + 155,
             CC_ORIGIN_X + 80,
             CC_ORIGIN_Y + 175, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE | GFX_GOL_RADIOBUTTON_CHECKED_STATE, // will be dislayed and checked after creation
             (GFX_XCHAR *) NormalLoadStr, // "Normal Load"
             GFX_ALIGN_LEFT,
             alt2Scheme
             ); // alternative GOL scheme
    GFX_GOL_RadioButtonCreate
            (
             
             ID_RADIOBUTTON3, // ID
             CC_ORIGIN_X + 100,
             CC_ORIGIN_Y + 130,
             CC_ORIGIN_X + 200,
             CC_ORIGIN_Y + 150, // dimension
             GFX_GOL_RADIOBUTTON_DRAW_STATE, // will be dislayed after creation
             (GFX_XCHAR *) LightLoadStr, // "Light Load"
             GFX_ALIGN_LEFT,
             alt2Scheme
             ); // alternative GOL scheme
}

// Processes messages for custom control screen

uint16_t MsgCustomControl(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_RADIOBUTTON *pRb;
    GFX_GOL_CUSTOMCONTROL *pCc;

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_RADIOBUTTON1: // set load to high
            pCc = (GFX_GOL_CUSTOMCONTROL *) GFX_GOL_ObjectFind(ID_CUSTOM1); // get pointer to custom control object
            GFX_GOL_CustomControlSetPos(pCc, 75);
            GFX_GOL_ObjectStateSet(pCc, GFX_GOL_CUSTOMCONTROL_DRAW_BAR); // set to redraw the level
            return (1); // process by default

        case ID_RADIOBUTTON2: // set load to normal
            pCc = (GFX_GOL_CUSTOMCONTROL *) GFX_GOL_ObjectFind(ID_CUSTOM1); // get pointer to custom control object
            GFX_GOL_CustomControlSetPos(pCc, 120);
            GFX_GOL_ObjectStateSet(pCc, GFX_GOL_CUSTOMCONTROL_DRAW_BAR); // set to redraw the level
            return (1); // process by default

        case ID_RADIOBUTTON3: // set load to light
            pCc = (GFX_GOL_CUSTOMCONTROL *) GFX_GOL_ObjectFind(ID_CUSTOM1); // get pointer to custom control object
            GFX_GOL_CustomControlSetPos(pCc, 150);
            GFX_GOL_ObjectStateSet(pCc, GFX_GOL_CUSTOMCONTROL_DRAW_BAR); // set to redraw the level
            return (1); // process by default

        case ID_CUSTOM1: // level is changed
            if (objMsg == GFX_GOL_CUSTOMCONTROL_ACTION_SELECTED)
            {
                if (pMsg->param2 <= 110)
                {
                    pRb = (GFX_GOL_RADIOBUTTON *) GFX_GOL_ObjectFind(ID_RADIOBUTTON1); // get pointer heavy load setting
                    GFX_GOL_RadioButtonCheckSet(pRb, ID_RADIOBUTTON1); // set radio button for heavy to be checked
                    GFX_GOL_ObjectStateSet(pRb, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE);
                }
                else if (pMsg->param2 <= 140)
                {
                    pRb = (GFX_GOL_RADIOBUTTON *) GFX_GOL_ObjectFind(ID_RADIOBUTTON2); // get pointer heavy load setting
                    GFX_GOL_RadioButtonCheckSet(pRb, ID_RADIOBUTTON2); // set radio button for normal to be checked
                    GFX_GOL_ObjectStateSet(pRb, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE);
                }
                else
                {
                    pRb = (GFX_GOL_RADIOBUTTON *) GFX_GOL_ObjectFind(ID_RADIOBUTTON3); // get pointer heavy load setting
                    GFX_GOL_RadioButtonCheckSet(pRb, ID_RADIOBUTTON3); // set radio button for light to be checked
                    GFX_GOL_ObjectStateSet(pRb, GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE);
                }
            }

            return (1);

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_SIGNATURE; // goto signature screen
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_PICTURE; // goto picture screen
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
}

// dimensions for signature box
#define SIG_ORIGIN_X        ((GFX_MaxXGet() - 260 + 1) / 2)
#define SIG_ORIGIN_Y        ((40 + GFX_MaxYGet() - 170 + 1) / 2)
#define SIG_PANEL_LEFT      35
#define SIG_PANEL_RIGHT     GFX_MaxXGet() - 35
#define SIG_PANEL_TOP       50
#define SIG_PANEL_BOTTOM    GFX_MaxYGet() - 10

// Creates signature screen

void CreateSignature(void)
{
    GFX_GOL_ObjectListFree(); // free memory for the objects in the previous linked list and start new list
    CreatePage((GFX_XCHAR *) SignatureStr);
}

// Draws box for signature

uint16_t PanelSignature(void)
{
#define SIG_STATE_SET   0
#define SIG_STATE_DRAW  1

    static uint8_t state = SIG_STATE_SET;

    if (state == SIG_STATE_SET)
    { // set data for panel drawing
        GFX_GOL_PanelParameterSet
                (
                 
                 SIG_PANEL_LEFT,
                 SIG_PANEL_TOP,
                 SIG_PANEL_RIGHT,
                 SIG_PANEL_BOTTOM,
                 0,
                 WHITE,
                 altScheme->EmbossLtColor,
                 altScheme->EmbossDkColor,
                 NULL,
                GFX_FILL_STYLE_COLOR,
                 GFX_GOL_EMBOSS_SIZE
                 );

        state = SIG_STATE_DRAW; // change state
    }

    if (!GFX_GOL_PanelDraw())
    {
        return (0); // drawing is not completed
    }
    else
    {
        state = SIG_STATE_SET; // set state to initial
        return (1); // drawing is done
    }
}

// Processes messages for signature screen

uint16_t MsgSignature(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    static short prevX = -1; // previous point
    static short prevY = -1;
    short x, y; // current point
    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_WINDOW1:

            // get touched position
            x = pMsg->param1;
            y = pMsg->param2;

            // Check if it falls in the signature box
            if
                (
                 ((SIG_PANEL_LEFT + GFX_GOL_EMBOSS_SIZE) < x) &&
                 ((SIG_PANEL_RIGHT - GFX_GOL_EMBOSS_SIZE) > x) &&
                 ((SIG_PANEL_TOP + GFX_GOL_EMBOSS_SIZE) < y) &&
                 ((SIG_PANEL_BOTTOM - GFX_GOL_EMBOSS_SIZE) > y)
                 )
            {
                GFX_ColorSet(BRIGHTRED);

                // if previous position is not valid or event is PRESS
                if ((pMsg->uiEvent == EVENT_PRESS) || (prevX > 0))
                {
                    WAIT_UNTIL_FINISH(GFX_RectangleFillDraw(x, y, x+4, y+4)); // draw pixel
                }
                else
                {
                    WAIT_UNTIL_FINISH(GFX_LineDraw(prevX, prevY, x, y)); // connect with thick line previous and current points
                    WAIT_UNTIL_FINISH(GFX_LineDraw(prevX - 1, prevY, x - 1, y));
                    WAIT_UNTIL_FINISH(GFX_LineDraw(prevX + 1, prevY, x + 1, y));
                    WAIT_UNTIL_FINISH(GFX_LineDraw(prevX, prevY - 1, x, y - 1));
                    WAIT_UNTIL_FINISH(GFX_LineDraw(prevX, prevY + 1, x, y + 1));
                }

                prevX = x;
                prevY = y; // store position
            }
            else
            {
                // reset if outside of box
                prevX = -1;
            }

            return (1); // process by default

        case ID_BUTTON_NEXT:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_BUTTONS; // goto potentiometer graph screen
                animate = 0;
            }

            return (1); // process by default

        case ID_BUTTON_BACK:
            if (objMsg == GFX_GOL_BUTTON_ACTION_RELEASED)
            {
                screenState = CREATE_CUSTOMCONTROL; // goto custom control screen
                animate = 0;
            }

            return (1); // process by default

        default:
            return (1); // process by default
    }
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
#define TICK_PERIOD	    (GetPeripheralClock() * SAMPLE_PERIOD) / 4000000

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
    PR4 = 500;//TICK_PERIOD;						//(for approximately 100 us)
    IPC4bits.T4IP = 1;
    IFS0bits.T4IF = 0;  						//Clear flag
    IEC0bits.T4IE = 1;  						//Enable interrupt
    T4CONbits.TON = 1;
}

void InitializeSchemes()
{
    // create the alternate schemes
    altScheme = GFX_GOL_SchemeCreate(); // create alternative 1 style scheme
    alt2Scheme = GFX_GOL_SchemeCreate(); // create alternative 2 style scheme
    alt3Scheme = GFX_GOL_SchemeCreate(); // create alternative 3 style scheme
    alt4Scheme = GFX_GOL_SchemeCreate(); // create alternative 4 style scheme
    alt5Scheme = GFX_GOL_SchemeCreate(); // create alternative 5 style scheme
    redScheme = GFX_GOL_SchemeCreate(); // create red style scheme
    greenScheme = GFX_GOL_SchemeCreate(); // create green style scheme
    yellowScheme = GFX_GOL_SchemeCreate(); // create yellow style scheme
    meterScheme = GFX_GOL_SchemeCreate(); // create meter scheme
    navScheme = GFX_GOL_SchemeCreate(); // alternative scheme for the navigate buttons

    /* for Truly display */
    altScheme->Color0 = GFX_RGBConvert(0x4C, 0x8E, 0xFF);
    altScheme->Color1 = GFX_RGBConvert(255, 102, 0);
    altScheme->EmbossDkColor = GFX_RGBConvert(0x1E, 0x00, 0xE5);
    altScheme->EmbossLtColor = GFX_RGBConvert(0xA9, 0xDB, 0xEF);
    altScheme->ColorDisabled = GFX_RGBConvert(0xD4, 0xE1, 0xF7);
    altScheme->TextColor1 = BRIGHTBLUE;
    altScheme->TextColor0 = GFX_RGBConvert(255, 102, 0);
    altScheme->TextColorDisabled = GFX_RGBConvert(0xB8, 0xB9, 0xBC);

    altScheme->pFont = (void *) ptrLargeAsianFont;

    alt2Scheme->TextColor1 = BRIGHTRED;
    alt2Scheme->TextColor0 = BRIGHTBLUE;
    alt2Scheme->pFont = (void *) ptrSmallAsianFont;

    alt3Scheme->Color0 = LIGHTBLUE;
    alt3Scheme->Color1 = BRIGHTGREEN;
    alt3Scheme->TextColor0 = BLACK;
    alt3Scheme->TextColor1 = WHITE;
    alt3Scheme->pFont = (void *) ptrSmallAsianFont;

    alt4Scheme->Color0 = LIGHTBLUE;
    alt4Scheme->Color1 = BRIGHTGREEN;
    alt4Scheme->TextColor0 = BLACK;
    alt4Scheme->TextColor1 = WHITE;
    alt4Scheme->pFont = (void *) ptrSmallAsianFont;

    alt5Scheme->Color0 = LIGHTBLUE;
    alt5Scheme->Color1 = BRIGHTRED;
    alt5Scheme->TextColor0 = BLACK;
    alt5Scheme->TextColor1 = WHITE;
    alt5Scheme->pFont = (void *) &monofont; //monofont is equal width font, required for digitalmeter widget

    redScheme->Color0 = GFX_RGBConvert(0xCC, 0x00, 0x00);
    redScheme->Color1 = BRIGHTRED;
    redScheme->EmbossDkColor = RED4;
    redScheme->EmbossLtColor = FIREBRICK1;
    redScheme->TextColor0 = GFX_RGBConvert(0xC8, 0xD5, 0x85);
    redScheme->TextColor1 = BLACK;
    redScheme->pFont = (void *) ptrLargeAsianFont;

    greenScheme->Color0 = GFX_RGBConvert(0x23, 0x9E, 0x0A);
    greenScheme->Color1 = BRIGHTGREEN;
    greenScheme->EmbossDkColor = DARKGREEN;
    greenScheme->EmbossLtColor = PALEGREEN;
    greenScheme->TextColor0 = GFX_RGBConvert(0xDF, 0xAC, 0x83);
    greenScheme->TextColor1 = BLACK;
    greenScheme->pFont = (void *) ptrLargeAsianFont;

    yellowScheme->Color0 = BRIGHTYELLOW;
    yellowScheme->Color1 = YELLOW;
    yellowScheme->EmbossDkColor = GFX_RGBConvert(0xFF, 0x94, 0x4C);
    yellowScheme->EmbossLtColor = GFX_RGBConvert(0xFD, 0xFF, 0xB2);
    yellowScheme->TextColor0 = GFX_RGBConvert(0xAF, 0x34, 0xF3);
    yellowScheme->TextColor1 = RED;
    yellowScheme->pFont = (void *) ptrLargeAsianFont;

    meterScheme->Color0 = BLACK;
    meterScheme->Color1 = WHITE;
    meterScheme->TextColor0 = BRIGHTBLUE;
    meterScheme->TextColor1 = WHITE;
    meterScheme->EmbossDkColor = GRAY20;
    meterScheme->EmbossLtColor = GRAY204;
    meterScheme->pFont = (void *) ptrSmallAsianFont;

    navScheme->pFont = (void *) ptrLargeAsianFont;
}

