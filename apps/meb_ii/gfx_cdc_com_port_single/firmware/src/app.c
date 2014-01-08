/*******************************************************************************
  USB DEVICE CDC Basic Demo Application
  
  File Name:
    app.c

  Summary:
    USB DEVICE CDC Basic Demo application

  Description:
    This file contains the USB DEVICE CDC Basic Demo application logic.
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "ChineseFontsfontref.h"

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
#define ID_KEYPAD               100

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

/****************************************************
 * This is the text that is sent to the host
 * when a switch is pressed
 ****************************************************/

uint8_t switchPrompt[] = "\r\nPUSH BUTTON PRESSED";

/*****************************************************
 * Initialize the application data structure. All
 * application related variables are stored in this
 * data structure.
 *****************************************************/

APP_DATA appData = 
{
    /* Device Layer Handle  */
    .deviceHandle = -1 ,

    /* CDC Instance index for this app object00*/
    .cdcInstance = 0,

    /* app state */
    .state = APP_STATE_INIT ,

    /* device configured status */
    .isConfigured = false,

    /* Initial get line coding state */
    .getLineCodingData = {9600, 0, 0, 8},

    /* Read Transfer Handle */
    .readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID,

    /* Write Transfer Handle */
    .writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID,

    /* Intialize the read complete flag */
    .isReadComplete = true,

    /*Initialize the write complete flag*/
    .isWriteComplete = true,

    /* Initialize Ignore switch flag */
    .ignoreSwitchPress = false

};


/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////

void CreatePage(GFX_XCHAR *pText); // creates the navigation buttons and window for each screen

void CreateEditBox(void); // creates edit box demo screen
uint16_t MsgEditBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for edit box demo screen

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

const GFX_RESOURCE_HDR *ptrLargeAsianFont = &GOLFontDefault;

/////////////////////////////////////////////////////////////////////////////
//                            DEMO STATES
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
    CREATE_EDITBOX,
    DISPLAY_EDITBOX,
} SCREEN_STATES;

/////////////////////////////////////////////////////////////////////////////
//                       GLOBAL VARIABLES FOR DEMO
/////////////////////////////////////////////////////////////////////////////
SCREEN_STATES screenState = CREATE_EDITBOX; // current state of main demo state mashine

GFX_GOL_OBJ_SCHEME *altScheme; // alternative style scheme
GFX_GOL_OBJ_SCHEME *navScheme; // style scheme for the navigation

/////////////////////////////////////////////////////////////////////////////
//                            MACROS
/////////////////////////////////////////////////////////////////////////////
#define WAIT_UNTIL_FINISH(x)    while(x == GFX_STATUS_FAILURE)

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

        case DISPLAY_EDITBOX:
            return (MsgEditBox(objMsg, pObj, pMsg));

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
    switch (screenState)
    {

        case CREATE_EDITBOX:
            CreateEditBox(); // create edit box test screen
            screenState = DISPLAY_EDITBOX; // switch to next state
            return (1); // draw objects created

        case DISPLAY_EDITBOX:
            return (1);

    }

    return (1); // release drawing control to GOL
}

/*****************************************************
 * This function is called in every step of the
 * application state machine.
 *****************************************************/

bool APP_StateReset(void)
{
    /* This function returns true if the device
     * was reset  */
    
    bool retVal;
    
    if(appData.isConfigured == false)
    {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.isReadComplete = true;
        appData.isWriteComplete = true;
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    
    return(retVal);
}

/*******************************************************
 * USB Device Layer Events - Application Event Handler
 *******************************************************/

void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * eventData )
{

    switch ( event )
    {
        case USB_DEVICE_EVENT_RESET:
       
            // USB device is reset or device is deconfigured.
            // This means that USB device layer is about to deininitialize
            // all function drivers. 

            // Also turn ON LEDs to indicate reset/deconfigured state.
            /* Switch on red and orange, switch off green */

            BSP_SwitchONLED ( LED_1 );
            BSP_SwitchONLED ( LED_2 );
            BSP_SwitchOFFLED ( LED_3 );

            appData.isConfigured = false;
            
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* check the configuration */

            if ( eventData->eventConfigured.configurationValue == 1)
            {
                /* the device is in configured state */
                /* Switch on green and switch off red and orange */
                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );

                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the 
                 * user data */

                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0,
                        APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);
                
                /* mark that set configuration is complete */
                appData.isConfigured = true;

            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Switch on green and orange, switch off red */
            BSP_SwitchOFFLED ( LED_1 );
            BSP_SwitchONLED ( LED_2 );
            BSP_SwitchONLED ( LED_3 );
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ATTACHED:
        case USB_DEVICE_EVENT_DETACHED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;

    }

}

/*******************************************************
 * USB CDC Device Events - Application Event Handler
 *******************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler
( 
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void* pData,
    uintptr_t userData 
)
{
    APP_DATA * appDataObject;
    appDataObject = (APP_DATA *)userData;
    USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE * controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK * breakData;

    switch ( event )
    {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            /* This means the host wants to know the current line
             * coding. This is a control transfer request. Use the 
             * USB_DEVICE_ControlSend() function to send the data to
             * host.  */

             USB_DEVICE_CDC_ControlSend(index, controlTransferHandle,
                    &appDataObject->getLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the 
             * data from the host */

            USB_DEVICE_CDC_ControlReceive(index, controlTransferHandle,
                    &appDataObject->setLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData =
                    (USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE *)pData;
            appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->controlLineStateData.carrier =
                    controlLineStateData->carrier;

            USB_DEVICE_CDC_ControlStatus(index, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent. Read the break duration */

            breakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData;
            appDataObject->breakData.duration = breakData->duration;
            break; 

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            /* This means that the host has sent some data*/
            appDataObject->isReadComplete = true;
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. For now we accept all the data */

            USB_DEVICE_CDC_ControlStatus(index, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We dont
             * do much with this data in this demo. */
            break;

        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the data write got completed. We can schedule
             * the next read. */

            appDataObject->isWriteComplete = true;
            break;
   
        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/******************************************************
 * Application Initialize is currently not used. It is
 * called from the SYS_Initialized() function.
 ******************************************************/

void APP_Initialize ( APP_DATA * appData )
{
    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

    DisplayResetEnable();               // hold in reset by default

    DisplayResetConfig();               // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                    // enable chip select line

    DisplayBacklightOff();              // initially set the backlight to off

    DisplayBacklightConfig();           // set the backlight control pin

    GFX_GOL_MessageCallbackSet(&GFX_GOL_MessageCallback);
    GFX_GOL_DrawCallbackSet(&GFX_GOL_DrawCallback);

    InitializeSchemes();
}

/********************************************************
 * Application switch press routine
 ********************************************************/

void APP_ProcessSwitchPress(APP_DATA * appData)
{
    /* This function checks if the switch is pressed and then 
     * debounces the switch press*/
    
    if(!appData->ignoreSwitchPress)
    {
        /* Check if the switch was pressed */
        if(BSP_ReadSwitch(SWITCH_1) == BSP_SWITCH_STATE_PRESSED)
        {
            /* The switch was pressed. Ignore any more switch presses
             * and then start the debounce timer. The debounce timer
             * is implemented using the core timer */
            
            appData->ignoreSwitchPress = true;
            BSP_StartTimer(APP_SWITCH_DEBOUNCE_PERIOD);
            SYS_INT_SourceEnable(INT_SOURCE_TIMER_CORE);
            
        }
    }
}

/**********************************************************
 * Application tasks routine. This function implements the
 * application state machine.
 ***********************************************************/
void APP_Tasks ( APP_DATA * appData )
{

    /* Update the application state machine based
     * on the current state */

    USB_DEVICE_CDC_RESULT result;
    GFX_GOL_EDITBOX *pEb;

    APP_ProcessSwitchPress(appData);

    switch(appData->state)
    {
        case APP_STATE_INIT:

            /* Open the device layer */
            appData->deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData->deviceHandle == USB_DEVICE_HANDLE_INVALID)
            {
                SYS_ASSERT(false, "Could not open device layer");
                appData->state = APP_STATE_ERROR;
                break;
            }

            /* Register a callback with device layer to get event notification (for end point 0) */
            USB_DEVICE_EventCallBackSet(appData->deviceHandle, APP_USBDeviceEventHandler);

            /* Attach the device */
            USB_DEVICE_Attach (appData->deviceHandle);

            appData->state = APP_STATE_WAIT_FOR_CONFIGURATION;

            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device was configured */
            if(appData->isConfigured)
            {
                /* If the device is configured then lets start reading */
                appData->state = APP_STATE_SCHEDULE_READ;
            }
            break;
            
        case APP_STATE_SCHEDULE_READ:

            if(APP_StateReset())
            {
                break;
            }

            /* If a read is complete, then schedule a read
             * else wait for the current read to complete */

            appData->state = APP_STATE_WAIT_FOR_READ_COMPLETE;
            if(appData->isReadComplete == true)
            {
                appData->isReadComplete = false;
                appData->readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
                USB_DEVICE_CDC_Read (appData->cdcInstance, &appData->readTransferHandle,
                        appData->readBuffer, 64);
                if(appData->readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
                {
                    appData->state = APP_STATE_ERROR;
                    break;
                }
            }
           
            break;

        case APP_STATE_WAIT_FOR_READ_COMPLETE:
        case APP_STATE_CHECK_SWITCH_PRESSED:
        
            if(APP_StateReset())
            {
                break;
            }

            /* Check if a character was received or a switch was pressed.
             * The isReadComplete flag gets updated in the CDC event handler. */

            if(appData->isReadComplete || appData->isSwitchPressed)
            {
                 appData->state = APP_STATE_SCHEDULE_WRITE;
            }

            break;
          
            
        case APP_STATE_SCHEDULE_WRITE:

            if(APP_StateReset())
            {
                break;
            }

            /* Setup the write */

            appData->writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData->isWriteComplete = false;
            appData->state = APP_STATE_WAIT_FOR_WRITE_COMPLETE;

            if(appData->isSwitchPressed)
            {
                /* If the switch was pressed, then send the switch prompt*/
                appData->isSwitchPressed = false;
                result = USB_DEVICE_CDC_Write(appData->cdcInstance, &appData->writeTransferHandle,
                     switchPrompt, 23, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }
            else
            {
                /* Else echo the received character + 1*/
                if ( appData->readBuffer[0] == '\b' )
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharRemove(pEb);
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }
                if ( appData->readBuffer[0] >= '1' && appData->readBuffer[0] <= '9' )
                {
                    pEb = (GFX_GOL_EDITBOX *) GFX_GOL_ObjectFind(ID_EDITBOX1);
                    GFX_GOL_EditBoxCharAdd(pEb, appData->readBuffer[0]);
                    GFX_GOL_ObjectStateSet(pEb, GFX_GOL_EDITBOX_DRAW_STATE);
                }
                appData->readBuffer[0] = appData->readBuffer[0] + 1;
                USB_DEVICE_CDC_Write(appData->cdcInstance, &appData->writeTransferHandle,
                    appData->readBuffer, 1, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }
                   
            break;

        case APP_STATE_WAIT_FOR_WRITE_COMPLETE:

            if(APP_StateReset())
            {
                break;
            }

            /* Check if a character was sent. The isWriteComplete
             * flag gets updated in the CDC event handler */

            if(appData->isWriteComplete == true)
            {
                appData->state = APP_STATE_SCHEDULE_READ;

            }

            break;

        case APP_STATE_ERROR:
            break;
        default:
            break;
    }

       GFX_GOL_ObjectListDraw();
} 

void CreatePage(GFX_XCHAR *pText)
{

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
}

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
        {'9', 0}
//        ,
//        {'*', 0},
//        {'#', 0}
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

            default:
                break;
        }
    }
    return (1); // process by default
}

void InitializeSchemes()
{
    // create schemes
    altScheme = GFX_GOL_SchemeCreate();
    altScheme->pFont = (void *) ptrLargeAsianFont;
    altScheme->CommonBkColor = GRAY096;
    altScheme->CommonBkColor = BLACK;
    altScheme->EmbossDkColor = BLACK;
    altScheme->Color0 = GRAY096;
    altScheme->Color1 = GRAY096;

    navScheme = GFX_GOL_SchemeCreate();
    navScheme->pFont = (void *) ptrLargeAsianFont;
    navScheme->CommonBkColor = BLACK;
    navScheme->EmbossDkColor = BLACK;
    navScheme->EmbossLtColor = BLACK;
    navScheme->Color0 = GRAY096;
    navScheme->Color1 = GRAY096;
}
/*******************************************************************************
 End of File
 */

