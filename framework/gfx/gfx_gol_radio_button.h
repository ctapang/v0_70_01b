/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_radio_button.h

  Summary:
    This is the header file for the radio button object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    RadioButton Object.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _GFX_GOL_RADIO_BUTTON_H
    #define _GFX_GOL_RADIO_BUTTON_H

#include <stdint.h>
#include "gfx/gfx_gol.h"

/*********************************************************************
* Object States Definition: 
*********************************************************************/
typedef enum
{
    GFX_GOL_RADIOBUTTON_FOCUSED_STATE    = 0x0001,  // Bit for focus state.
    GFX_GOL_RADIOBUTTON_DISABLED_STATE   = 0x0002,  // Bit for disabled state.
    GFX_GOL_RADIOBUTTON_CHECKED_STATE    = 0x0004,  // Bit to indicate Radio Button is checked.
    GFX_GOL_RADIOBUTTON_GROUP_STATE      = 0x0008,  // Bit to indicate the first Radio Button in the group.
                                                    // Each group MUST have this bit set for its first member
                                                    // even for a single member group. This means that any
                                                    // independent or stand alone Radio Button, the RB_GROUP bit
                                                    // must be always set.
                                                    // or alone in the group.
    GFX_GOL_RADIOBUTTON_DRAW_CHECK_STATE = 0x1000,  // Bit to indicate check mark should be redrawn.
    GFX_GOL_RADIOBUTTON_DRAW_FOCUS_STATE = 0x2000,  // Bit to indicate focus must be redrawn.
    GFX_GOL_RADIOBUTTON_DRAW_STATE       = 0x4000,  // Bit to indicate object must be redrawn.
    GFX_GOL_RADIOBUTTON_HIDE_STATE       = 0x8000,  // Bit to indicate object must be removed from screen.
} GFX_GOL_RADIOBUTTON_STATE;

/*****************************************************************************
* Overview: the structure contains data for the Radio Button
*****************************************************************************/
typedef struct
{
    GFX_GOL_OBJ_HEADER  hdr;        // Generic header for all Objects (see OBJ_HEADER).
    GFX_GOL_OBJ_HEADER  *pHead;     // Pointer to the first Radio Button in the group
    GFX_GOL_OBJ_HEADER  *pNext;     // Pointer to the next Radio Button in the group
    uint16_t            textHeight; // Pre-computed text height
    GFX_XCHAR           *pText;     // Pointer to the text
    GFX_ALIGNMENT       alignment;  // text alignment
} GFX_GOL_RADIOBUTTON;

// *****************************************************************************
/*  Function:
    GFX_GOL_RADIOBUTTON  *GFX_GOL_RadioButtonCreate(
                                uint16_t            ID,
                                uint16_t            left,
                                uint16_t            top,
                                uint16_t            right,
                                uint16_t            bottom,
                                uint16_t            state,
                                GFX_XCHAR           *pText,
                                GFX_ALIGNMENT       alignment,
                                GFX_GOL_OBJ_SCHEME  *pScheme)
 
    Summary:
        This function creates a GFX_GOL_RADIOBUTTON object with the
        parameters given. It automatically attaches the new object
        into a global linked list of objects and returns the address
        of the object.

    Description:
        This function creates a GFX_GOL_RADIOBUTTON object with the
        parameters given. It automatically attaches the new object
        into a global linked list of objects and returns the address
        of the object.

        This function returns the pointer to the newly created object.
        If the object is not successfully created, it returns NULL.

        The behavior of GFX_GOL_RadioButtonCreate() will be undefined
        if one of the following is true:
        - left >= right
        - top >= bottom
        - pScheme is not pointing to a GFX_GOL_OBJ_SCHEME
        - pText is an unterminated string

    Precondition:
        None.

    Parameters:
        ID - Unique user defined ID for the object instance.
        left - Left most position of the object.
        top - Top most position of the object.
        right - Right most position of the object.
        bottom - Bottom most position of the object.
        state - Sets the initial state of the object.
        pText - Pointer to the text of the object.
        alignment - text alignment of the text used in the object.
        pScheme - Pointer to the style scheme used.

    Returns:
        Pointer to the newly created object.

    Example:
        <code>

            static  GFX_XCHAR   label0[] = "RB1";
            static  GFX_XCHAR   label1[] = "RB2";
            static  GFX_XCHAR   label2[] = "RB3";
                    uint16_t    state;
                    GFX_GOL_OBJ_SCHEME  *pScheme;
                    RADIOBUTTON *pRb[3];

            pScheme = GFX_GOL_ObjectSchemeCreate();

            // Object will be drawn after creation
            // Object will be first button in the group
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE |
                    GFX_GOL_RADIOBUTTON_CHECKED_STATE;

            pRb[0] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON1,
                              255,40,310,80,	
                              state,
                              label0,
                              GFX_ALIGN_CENTER,
                              pScheme);         

            // Object will be drawn after creation
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE;

            pRb[1] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON2,
                              255,85,310,125,   
                              state,
                              label1,
                              GFX_ALIGN_CENTER,
                              pScheme);         

            // Object will be drawn after creation
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE;

            pRb[2] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON3,
                              255,130,310,170,  
                              state,
                              label2,
                              GFX_ALIGN_CENTER,
                              pScheme);         

            // draw the objects
            while(GFX_GOL_ObjectListDraw() != GFX_STATUS_SUCCESS);

        </code>

*/
// *****************************************************************************
GFX_GOL_RADIOBUTTON  *GFX_GOL_RadioButtonCreate(
                                uint16_t            ID,
                                uint16_t            left,
                                uint16_t            top,
                                uint16_t            right,
                                uint16_t            bottom,
                                uint16_t            state,
                                GFX_XCHAR           *pText,
                                GFX_ALIGNMENT       alignment,
                                GFX_GOL_OBJ_SCHEME  *pScheme);

// *****************************************************************************
/*  Function:
    GFX_XCHAR *GFX_GOL_RadioButtonTextGet(
                                GFX_GOL_RADIOBUTTON *pObject)

    Summary:
        This function returns the address of the current text
        string used by the object.

    Description:
        This function returns the address of the current text
        string used by the object.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.

    Returns:
        Pointer to text string.

    Example:
        <code>
            // assume RADIO_BUTTON_OBJECT is a radio button that exists
            GFX_XCHAR *pChar;
            GFX_GOL_RADIOBUTTON *pRadioButton = &RADIO_BUTTON_OBJECT;

            pChar = GFX_GOL_ButtonRadioTextGet(pRadioButton);
       </code>

*/
// *****************************************************************************
#define GFX_GOL_RadioButtonTextGet(pObject)  (((GFX_GOL_RADIOBUTTON *)pObject)->pText)

/************************************************************************
  Function:
      GFX_XCHAR *GFX_GOL_RadioButtonTextSet(
                                  GFX_GOL_RADIOBUTTON *pObject,
                                  GFX_XCHAR *pText)
    
  Summary:
    This function sets the address of the current text string used by the
    object.
  Description:
    This function sets the address of the current text string used by the
    object.
  Conditions:
    Object must exist in memory.
  Input:
    pObject -  pointer to the object.
    pText -    pointer to the text string to be used.
  Return:
    None.
  Example:
    <code>
    
       GFX_XCHAR Label0[] = "ON";
       GFX_XCHAR Label1[] = "OFF";
       GFX_GOL_RADIOBUTTON GFX_GOL_RADIOBUTTON[2];
    
       GFX_GOL_RadioButtonTextSet(GFX_GOL_RADIOBUTTON[0], Label0);
       GFX_GOL_RadioButtonTextSet(GFX_GOL_RADIOBUTTON[1], Label1);
    
    </code>
                                                                         
  ************************************************************************/
void GFX_GOL_RadioButtonTextSet(
                                GFX_GOL_RADIOBUTTON *pObject,
                                GFX_XCHAR * pText);

// *****************************************************************************
/*  Function:
    GFX_ALIGNMENT GFX_GOL_RadioButtonTextAlignmentGet(
                                GFX_GOL_RADIOBUTTON *pObject)

    Summary:
        This function returns the text alignment of the text
        string used by the object.

    Description:
        This function returns the text alignment of the text
        string used by the object.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.

    Returns:
        The text alignment set in the object. See GFX_ALIGNMENT for more
        details.

    Example:
        None.

*/
// *****************************************************************************
GFX_ALIGNMENT GFX_GOL_RadioButtonTextAlignmentGet(GFX_GOL_RADIOBUTTON *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_RadioButtonTextAlignmentSet(
                                GFX_GOL_RADIOBUTTON *pObject,
                                GFX_ALIGNMENT align)

    Summary:
        This function sets the text alignment of the text
        string used by the object.

    Description:
        This function sets the text alignment of the text
        string used by the object.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - Pointer to the object.
        align - The alignment set for the text in the object.
                See GFX_ALIGNMENT for more details.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_RadioButtonTextAlignmentSet(
                                GFX_GOL_RADIOBUTTON *pObject,
                                GFX_ALIGNMENT align);

// *****************************************************************************
/*  Function:
    GFX_XCHAR GFX_GOL_RadioButtonCheckSet(
                                GFX_GOL_RADIOBUTTON *pObject,
                                uint16_t id)

    Summary:
        This function sets the ID of the currently checked
        radio button in the group.

    Description:
        This function sets the ID of the currently checked
        radio button in the group. When there is only one
        member of the group, then that member will have
        the check.

        When the id given does not exist in the group, the
        function will do nothing.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.
        id - id of the member of the group.

    Returns:
        None.

    Example:
 	See GFX_GOL_RadioButtonCheckGet() example.

*/
// *****************************************************************************
void GFX_GOL_RadioButtonCheckSet(GFX_GOL_RADIOBUTTON *pObject, uint16_t id);

// *****************************************************************************
/*  Function:
    uint16_t GFX_GOL_RadioButtonCheckGet(
                                GFX_GOL_RADIOBUTTON *pObject)

    Summary:
        This function returns the ID of the currently checked
        radio button in the group.

    Description:
        This function returns the ID of the currently checked
        radio button in the group. When there is only one
        member of the group, then that member will have
        the check.

        When no member of the group is checked, then the id
        returned is (-1 or 0xFFFF).

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.

    Returns:
        The ID of the member of the group with the check.

    Example:
        <code>


            static  GFX_XCHAR   label0[] = "RB1";
            static  GFX_XCHAR   label1[] = "RB2";
            static  GFX_XCHAR   label2[] = "RB3";
                    uint16_t    state;
                    GFX_GOL_OBJ_SCHEME  *pScheme;
                    RADIOBUTTON *pRb[3];
                    uint16_t    ID;

            pScheme = GFX_GOL_ObjectSchemeCreate();

            // Object will be drawn after creation
            // Object will be first button in the group
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE |
                    GFX_GOL_RADIOBUTTON_CHECKED_STATE;

            pRb[0] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON1,
                              255,40,310,80,
                              state,
                              label0,
                              GFX_ALIGN_CENTER,
                              pScheme);

            // Object will be drawn after creation
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE;

            pRb[1] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON2,
                              255,85,310,125,
                              state,
                              label1,
                              GFX_ALIGN_CENTER,
                              pScheme);

            // Object will be drawn after creation
            state = GFX_GOL_RADIOBUTTON_DRAW_STATE;

            pRb[2] = GFX_GOL_RadioButtonCreate(ID_RADIOBUTTON3,
                              255,130,310,170,
                              state,
                              label2,
                              GFX_ALIGN_CENTER,
                              pScheme);

            // draw the objects
            while(GFX_GOL_ObjectListDraw() != GFX_STATUS_SUCCESS);

            // can also use pRb[1] or pRb[0] to search the checked 
            // radio button of the group. ID here should be ID_RADIOBUTTON1           
            ID = GFX_GOL_RadioButtonCheckGet(pRb[2]);

            if (ID == ID_RADIOBUTTON1)
            {
                // do something here then clear the check
		GFX_GOL_ObjectStateClear(pRb[0], RB_CHECKED);
		// Change the checked object. Pointer used is 
                // any of the three. The ID used will find the
                // correct object to be checked
		GFX_GOL_RadioButtonCheckSet(pRb[3], ID_RADIOBUTTON2);
            }
        </code>


*/
// *****************************************************************************
uint16_t GFX_GOL_RadioButtonCheckGet(
                                GFX_GOL_RADIOBUTTON *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_RadioButtonActionSet(
                                GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage)

    Summary:
        This function performs the state change of the object based on the
        translated action.

    Description:
        This function performs the state change of the object based on the
        translated action. This change can be overridden by the application
        using the application defined GFX_GOL_MESSAGE_CALLBACK_FUNC.
        When the user message is determined to affect the object, application
        can perform the state change in the message callback function.
        The following state changes are supported:
 	<TABLE>
    	Translated Message                  Input Source	Set/Clear State Bit                         Description
     	##################                  ############	###################                         ###########
        GFX_GOL_RADIOBUTTON_ACTION_CHECKED  Touch Screen,       Set GFX_GOL_RADIOBUTTON_DRAW_STATE,         Depending on the current value of RB_CHECKED Check Box will be redrawn.
                                            Keyboard            Set/Clear GFX_GOL_RADIOBUTTON_CHECKED_STATE
	</TABLE>

    Precondition:
        Object must exist in memory.

    Parameters:
        translatedMsg - The action of the object based on the message.
        pObject       - The pointer to the object whose state will be modified.
        pMessage      - The pointer to the original message.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_RadioButtonActionSet(
                                GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

/*********************************************************************************************************
  Function:
      GFX_GOL_TRANSLATED_ACTION GFX_GOL_RadioButtonActionGet(
                                  void *pObject,
                                  GFX_GOL_MESSAGE *pMessage)
    
  Summary:
    This function evaluates the message from a user if the message will
    affect the object or not.
  Description:
    This function evaluates the message from a user if the message will
    affect the object or not. The table below enumerates the action for
    each event of the touch screen and keyboard inputs.
    
    <table>
    Translated                           \Input     Set/Clear       \Description
     Message                              Source     State Bit       
    GFX_GOL_RADIOBUTTON_ACTION_CHECKED   Touch      EVENT_PRESS     If event occurs and the x,y position
                                          Screen                     falls in the area of the Radio Button
                                                                     while the Radio Button is not
                                                                     checked.
    \                                    Keyboard   EVENT_KEYSCAN   If event occurs and parameter1 passed
                                                                     matches the object's ID and parameter
                                                                     2 passed matches SCAN_CR_PRESSED or
                                                                     SCAN_SPACE_PRESSED while the Radio
                                                                     Button is not checked.
    GFX_GOL_OBJECT_ACTION_INVALID        Any        Any             If the message did not affect the
                                                                     object.
    </table>
  Conditions:
    Object must exist in memory.
  Input:
    pObject -   The pointer to the object where the message will be
                evaluated to check if the message will affect the object.
    pMessage -  Pointer to the message from the user interface.
  Return:
      * GFX_GOL_RADIOBUTTON_ACTION_CHECKED &#45; Radio Button is checked
      * GFX_GOL_OBJECT_ACTION_INVALID &#45; object is not affected
  Example:
    None.                                                                                                 
  ********************************************************************************************************
  ##################                  ############    #######################     ##################################################################################################################################################################*/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_RadioButtonActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_RadioButtonDraw(void *pObject)

    Summary:
        This function renders the object on the screen based on the
        current state of the object.

    Description:
        This function renders the object on the screen based on the
        current state of the object. Location of the object is
        determined by the left, top, right and bottom parameters.
        The colors used are dependent on the state of the object.
        The font used is determined by the style scheme set.

        The text on the GFX_GOL_RADIOBUTTON is drawn with the text
        alignment based on the alignment parameter set on the object.

        When rendering objects of the same type, each object
        must be rendered completely before the rendering of the
        next object is started. This is to avoid incomplete
        object rendering.

        Normally, application will just call GFX_GOL_ObjectListDraw()
        to allow the Graphics Library to manage all object rendering.
        See GFX_GOL_ObjectListDraw() for more information on object rendering.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - Pointer to the object.

    Returns:
        GFX_STATUS_SUCCESS - When the object rendering is finished.
        GFX_STATUS_FAILURE - When the object rendering is not yet finished.
                             Application needs to call this rendering
                             function again to continue the rendering.

    Example:
        None.

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_RadioButtonDraw(void *pObject);

#endif // _GFX_GOL_RADIO_BUTTON_H
