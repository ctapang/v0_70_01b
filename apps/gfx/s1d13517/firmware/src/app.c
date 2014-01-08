/*******************************************************************************
  S1D13517 Driver Demo Application

  File Name:
    app.c

  Summary:
    S1D13517 Driver Demo application

  Description:
    This file contains the S1D13517 Driver Demo application logic.
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

#include "gfx_schemes.h"
#include "gfx_strings.h"
#include "gfx_screens.h"
#include "gol_ids.h"
#include "timer_tick.h"
#include "gfx/src/common_legacy/TouchScreen.h"
#include "JPEGImage.h"

/////////////////////////////////////////////////////////////////////////////
//                            LOCAL PROTOTYPES
/////////////////////////////////////////////////////////////////////////////
void  TickInit(void);
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
//                       GLOBAL VARIABLES FOR DEMO
/////////////////////////////////////////////////////////////////////////////
SCREEN_STATES   screenState = CREATE_BACKGROUND;			// current state of main demo state mashine

/////////////////////////////////////////////////////////////////////////////

//                                  MAIN
/////////////////////////////////////////////////////////////////////////////
void APP_Tasks(void)
{
    GFX_GOL_ObjectListDraw();
}
