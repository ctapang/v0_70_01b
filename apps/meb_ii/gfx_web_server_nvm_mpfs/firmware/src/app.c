/*******************************************************************************
  Sample Application

  File Name:
    app.c

  Summary:
    Sample "hello world" application

  Description:
    This file contains the sample "hello world" application's implementation.
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

//#include "system_config.h"
#include "app.h"
#include "system_config.h"
#include "ChineseFontsfontref.h"

// Include all headers for any enabled tcpip functions
#include "tcpip/src/tcpip_private.h"
#include "tcpip_modules_config.h"
#include "tcpip/tcpip.h"

// Include functions specific to this stack application
#include "tcpip/src/system/system_userio.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appData;

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObjects;

int nNets;
TCPIP_NET_HANDLE    netH;
SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;

/////////////////////////////////////////////////////////////////////////////
//                              OBJECT'S IDs
/////////////////////////////////////////////////////////////////////////////
#define ID_WINDOW1              10

#define ID_LISTBOX1             80
#define ID_LISTBOX2             81
#define ID_LISTBOX3             82
#define ID_EDITBOX1             83


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
SCREEN_STATES screenState = CREATE_LISTBOX; // current state of main demo state mashine


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

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void CreatePage(GFX_XCHAR *pText); // creates the navigation buttons and window for each screen

void CreateListBox(void); // creates list box demo screen
uint16_t MsgListBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg); // processes messages for list box demo screen

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize( void )
{
    int i;
    const char          *netName, *netBiosName;

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)

    appData.state = APP_USERIO_LED_DEASSERTED;

    nNets = TCPIP_STACK_NumberOfNetworksGet();

    for(i = 0; i < nNets; i++)
    {

        netH = TCPIP_STACK_IndexToNet(i);
        netName = TCPIP_STACK_NetNameGet(netH);
        netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif  // defined(TCPIP_STACK_USE_NBNS)

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
        mDNSServiceName[sizeof(mDNSServiceName) - 2] = '1' + i;
        TCPIP_MDNS_ServiceRegister( netH
                , mDNSServiceName                   // name of the service
                ,"_http._tcp.local"                 // type of the service
                ,80                                 // TCP or UDP port, at which this service is available
                ,((const uint8_t *)"path=/index.htm")  // TXT info
                ,1                                  // auto rename the service when if needed
                ,NULL                               // no callback function
                ,NULL);                             // no application context
#endif //TCPIP_STACK_USE_ZEROCONF_MDNS_SD

    }

    /* Intialize the app state to wait for
     * media attach. */
    appData.state = APP_MOUNT_DISK;

    GFX_GOL_MessageCallbackSet(&GFX_GOL_MessageCallback);
    GFX_GOL_DrawCallbackSet(&GFX_GOL_DrawCallback);

    InitializeSchemes();
    GFX_GOL_DrawCallback();
}


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

/*******************************************************************************
  Function:
    void APP_Tasks( void )

  Remarks:
    See prototype in app.h.
 */

    GFX_XCHAR addr[50];

void APP_Tasks( void )
{
    static SYS_TICK startTick = 0;
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int i;
    GFX_GOL_LISTBOX *pLb;
    GFX_GOL_LISTITEM *pItem = NULL;

    pLb = (GFX_GOL_LISTBOX *) GFX_GOL_ObjectFind(ID_LISTBOX1);


    switch(appData.state)
    {
        case APP_MOUNT_DISK:
            if(SYS_FS_Mount(SYS_FS_NVM_VOL, LOCAL_WEBSITE_PATH_FS, MPFS2, 0, NULL)  == 0)
            {
                SYS_CONSOLE_PRINT("SYS_Initialize: The %s File System is mounted.\r\n", SYS_FS_MPFS_STRING);
                appData.state = APP_TCPIP_TRANSACT;
            }
            else
            {
                //SYS_CONSOLE_Print("SYS_Initialize: Failed to mount the %s File System! \r\n", SYS_FS_MPFS_STRING);
                appData.state = APP_MOUNT_DISK;
            }
            break;

        case APP_TCPIP_TRANSACT:

            if (SYS_TICK_Get() - startTick >= SYS_TICK_TicksPerSecondGet() / 2ul)
            {
                startTick = SYS_TICK_Get();
                LEDstate ^= APP_USERIO_LED_ASSERTED;
                SYS_USERIO_SetLED(SYS_USERIO_LED_0, LEDstate);
            }

            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);

                    sprintf(addr, "IP Address: %d.%d.%d.%d\0", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                    if ( ipAddr.v[0] > 0 )
                    {
                        GFX_GOL_ListBoxItemAdd(pLb, NULL, addr, NULL, 0, 0);
                        GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_STATE);
                    }
                }
            }
            break;

         default:
            break;
    }

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
        case DISPLAY_LISTBOX:
            return (MsgListBox(objMsg, pObj, pMsg));

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
    GFX_GOL_OBJ_HEADER *pObj = NULL; // used to change text in Window
    GFX_GOL_LISTBOX *pLb; // used when updating date and time

    switch (screenState)
    {
        case CREATE_LISTBOX:
            prevRefreshState = CREATE_LISTBOX;
            CreateListBox(); // create list box test screen
            screenState = DISPLAY_LISTBOX; // switch to next state
            return (1); // draw objects created

        case DISPLAY_LISTBOX:

            // this moves the slider and editbox for the date setting to
            // move while the up or down arrow buttons are pressed

            return (1); // draw objects
    }

    return (1); // release drawing control to GOL
}

// Shows intro screen and waits for touch
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
             NULL,
             GFX_ALIGN_LEFT,
             altScheme
             ); // use alternate scheme
}

// processes messages for list box demo screen

uint16_t MsgListBox(uint16_t objMsg, GFX_GOL_OBJ_HEADER *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_LISTBOX *pLb;
    GFX_GOL_SCROLLBAR *pSld;

    pLb = (GFX_GOL_LISTBOX *) GFX_GOL_ObjectFind(ID_LISTBOX1);

    switch (GFX_GOL_ObjectIDGet(pObj))
    {
        case ID_LISTBOX1:

            // Process message by default
            GFX_GOL_ListBoxActionSet(objMsg, (GFX_GOL_LISTBOX *) pObj, pMsg);

            // The message was processed
            return (0);


        default:
            return (1); // process by default
    }
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

