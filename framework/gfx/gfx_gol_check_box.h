/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_checkbox.h

  Summary:
    This is the header file for the check box object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    CheckBox Object.
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

#ifndef _GFX_GOL_CHECKBOX_H
    #define _GFX_GOL_CHECKBOX_H

#include <stdint.h>
#include "gfx/gfx_gol.h"

/*********************************************************************
* Object States Definition: 
*********************************************************************/
//    #define GFX_GOL_CHECKBOX_FOCUSED_STATE      0x0001  // Focus state
//    #define GFX_GOL_CHECKBOX_DISABLED_STATE     0x0002  // Disabled state
//    #define GFX_GOL_CHECKBOX_CHECKED_STATE      0x0004  // Checked state
//    #define GFX_GOL_CHECKBOX_HIDE_STATE         0x8000  // Check box must be removed from screen
//    #define GFX_GOL_CHECKBOX_DRAW_FOCUS_STATE   0x2000  // Focus must be redrawn
//    #define GFX_GOL_CHECKBOX_DRAW_STATE         0x4000  // Whole check box must be redrawn
//    #define GFX_GOL_CHECKBOX_DRAW_CHECK_STATE   0x1000  // Check box mark should be redrawn

typedef enum
{
    GFX_GOL_CHECKBOX_FOCUSED_STATE    = 0x0001,  // Bit for focus state.
    GFX_GOL_CHECKBOX_DISABLED_STATE   = 0x0002,  // Bit to indicate object is disabled
    GFX_GOL_CHECKBOX_CHECKED_STATE    = 0x0004,  // Bit to indicate object is checked
    GFX_GOL_CHECKBOX_DRAW_CHECK_STATE = 0x1000,  // Bit to indicate the check must be redrawn.
    GFX_GOL_CHECKBOX_DRAW_FOCUS_STATE = 0x2000,  // Bit to indicate focus must be redrawn.
    GFX_GOL_CHECKBOX_DRAW_STATE       = 0x4000,  // Bit to indicate object must be redrawn.
    GFX_GOL_CHECKBOX_HIDE_STATE       = 0x8000,  // Bit to indicate object must be removed from screen.
} GFX_GOL_CHECKBOX_STATE;

/*********************************************************************
* Overview: The structure contains check box data
*********************************************************************/
typedef struct
{
    GFX_GOL_OBJ_HEADER  hdr;        // Generic header for all Objects (see GFX_GOL_OBJ_HEADER).
    uint16_t            textHeight; // Pre-computed text height
    GFX_XCHAR           *pText;     // Pointer to text
    GFX_ALIGNMENT       alignment;  // text alignment
} GFX_GOL_CHECKBOX;

// *****************************************************************************
/*  Function:
    GFX_GOL_CHECKBOX  *GFX_GOL_CheckBoxCreate(
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
        This function creates a GFX_GOL_CHECKBOX object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

    Description:
        This function creates a GFX_GOL_CHECKBOX object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

        This function returns the pointer to the newly created object.
        If the object is not successfully created, it returns NULL.

        The behavior of GFX_GOL_CheckBoxCreate() will be undefined if one
        of the following is true:
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
            GFX_GOL_OBJ_SCHEME  *pScheme;
            GFX_GOL_CHECKBOX    *pCb[2];

            pCb[0] = GFX_GOL_CheckBoxCreate(
                                ID_CHECKBOX1,                // ID
                                20,135,150,175,              // dimension
                                GFX_GOL_CHECKBOX_DRAW_STATE, // Draw the object
                                "Scale",                     // text
                                GFX_ALIGN_CENTER,            // text alignment
                                pScheme);                    // use this scheme

            pCb[1] = GFX_GOL_CheckBoxCreate(
                                ID_CHECKBOX2,                // ID
                                170,135,300,175,             // dimension
                                GFX_GOL_CHECKBOX_DRAW_STATE, // Draw the object
                                "Animate",                   // text
                                GFX_ALIGN_LEFT | GFX_ALIGN_VCENTER, // text alignment
                                pScheme);                    // use this scheme
        </code>

*/
// *****************************************************************************
GFX_GOL_CHECKBOX *GFX_GOL_CheckBoxCreate(
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
    GFX_XCHAR *GFX_GOL_CheckBoxTextGet(
                                GFX_GOL_CHECKBOX *pObject)

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
            // assume CHECK_BOX_OBJECT is a radio button that exists
            GFX_XCHAR *pChar;
            GFX_GOL_CHECKBOX *pObject = &CHECK_BOX_OBJECT;

            pChar = GFX_GOL_CheckBoxTextGet(pObject);
       </code>

*/
// *****************************************************************************
#define GFX_GOL_CheckBoxTextGet(pObject)  (((GFX_GOL_CHECKBOX *)pObject)->pText)

/************************************************************************
  Function:
      GFX_XCHAR *GFX_GOL_CheckBoxTextSet(
                                  GFX_GOL_CHECKBOX *pObject,
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
    
       GFX_XCHAR Label0[] = "Enabled";
       GFX_XCHAR Label1[] = "Disabled";
       GFX_GOL_CHECKBOX GFX_GOL_CHECKBOX[2];
    
       GFX_GOL_CheckBoxTextSet(GFX_GOL_CHECKBOX[0], Label0);
       GFX_GOL_CheckBoxTextSet(GFX_GOL_CHECKBOX[1], Label1);
    
    </code>
                                                                         
  ************************************************************************/
void GFX_GOL_CheckBoxTextSet(
                                GFX_GOL_CHECKBOX *pObject,
                                GFX_XCHAR * pText);

// *****************************************************************************
/*  Function:
    GFX_ALIGNMENT GFX_GOL_CheckBoxTextAlignmentGet(
                                GFX_GOL_CHECKBOX *pObject)

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
GFX_ALIGNMENT GFX_GOL_CheckBoxTextAlignmentGet(GFX_GOL_CHECKBOX *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_CheckBoxTextAlignmentSet(
                                GFX_GOL_CHECKBOX *pObject,
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
void GFX_GOL_CheckBoxTextAlignmentSet(
                                GFX_GOL_CHECKBOX *pObject,
                                GFX_ALIGNMENT align);

/***********************************************************************************************
  Function:
      void GFX_GOL_CheckBoxActionSet(
                                  GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                  void *pObject,
                                  GFX_GOL_MESSAGE *pMessage)
    
  Summary:
    This function performs the state change of the object based on the
    translated action.
  Description:
    This function performs the state change of the object based on the
    translated action. This change can be overridden by the application
    using the application defined GFX_GOL_MESSAGE_CALLBACK_FUNC. When the
    user message is determined to affect the object, application can
    perform the state change in the message callback function. The
    following state changes are supported:
    <table>
    Translated Message                  \Input     Set/Clear                        \Description
                                         Source     State Bit                        
    GFX_GOL_CHECKBOX_ACTION_CHECKED     Touch      Set                              Check Box
                                         Screen,    GFX_GOL_CHECKBOX_CHECKED_STATE   will be
                                                                                     redrawn in
                                                                                     checked
                                                                                     state.
    \                                   Keyboard                                    
    GFX_GOL_CHECKBOX_ACTION_UNCHECKED   Touch      Clear                            Check Box
                                         Screen,    GFX_GOL_CHECKBOX_CHECKED_STATE   will be
                                                                                     redrawn in
                                                                                     unchecked
                                                                                     state.
    \                                   Keyboard                                    
    </table>
  Conditions:
    Object must exist in memory.
  Input:
    translatedMsg -  The action of the object based on the message.
    pObject -        The pointer to the object whose state will be modified.
    pMessage -       The pointer to the original message.
  Return:
    None.
  Example:
    None.                                                                                       
  **********************************************************************************************
  ##################                  ############    ###################                         ###########*/
void GFX_GOL_CheckBoxActionSet(
                                GFX_GOL_TRANSLATED_ACTION translatedMsg,
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

/***********************************************************************************************************
  Function:
      GFX_GOL_TRANSLATED_ACTION GFX_GOL_CheckBoxActionGet(
                                  void *pObject,
                                  GFX_GOL_MESSAGE *pMessage);
    
  Summary:
    This function evaluates the message from a user if the message will
    affect the object or not.
  Description:
    This function evaluates the message from a user if the message will
    affect the object or not. The table below enumerates the action for
    each event of the touch screen and keyboard inputs.
    
    <table>
    Translated                          \Input     Set/Clear       \Description
     Message                             Source     State Bit       
    GFX_GOL_CHECKBOX_ACTION_CHECKED     Touch      EVENT_RELEASE   If events occurs and the x,y position
                                         Screen                     falls in the area of the check box while
                                                                    the check box is unchecked.
    \                                   Keyboard   EVENT_KEYSCAN   If event occurs and parameter1 passed
                                                                    matches the object's ID and parameter 2
                                                                    passed matches SCAN_CR_PRESSED or
                                                                    SCAN_SPACE_PRESSED while the check box
                                                                    is unchecked.
    GFX_GOL_CHECKBOX_ACTION_UNCHECKED   Touch      EVENT_RELEASE   If events occurs and the x,y position
                                         Screen                     falls in the area of the check box while
                                                                    the check box is checked.
    \                                   Keyboard   EVENT_KEYSCAN   If event occurs and parameter1 passed
                                                                    matches the object's ID and parameter 2
                                                                    passed matches SCAN_CR_PRESSED or
                                                                    SCAN_SPACE_PRESSED while the check box
                                                                    is checked.
    GFX_GOL_OBJECT_ACTION_INVALID       Any        Any             If the message did not affect the
                                                                    object.
    </table>
  Conditions:
    Object must exist in memory.
  Input:
    pObject -   The pointer to the object where the message will be
                evaluated to check if the message will affect the object.
    pMessage -  Pointer to the message from the user interface.
  Return:
      * GFX_GOL_CHECKBOX_ACTION_CHECKED &#45; Check box is checked
      * GFX_GOL_CHECKBOX_ACTION_UNCHECKED &#45; Check box is unchecked
      * GFX_GOL_OBJECT_ACTION_INVALID &#45; Object is not affected
  Example:
    None.                                                                                                   
  **********************************************************************************************************
  ##################                  ############    #######################     ##################################################################################################################################################################*/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_CheckBoxActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_CheckBoxDraw(void *pObject)

    Summary:
        This function renders the object on the screen based on the
        current state of the object.

    Description:
        This function renders the object on the screen based on the
        current state of the object. Location of the object is
        determined by the left, top, right and bottom parameters.
        The colors used are dependent on the state of the object.
        The font used is determined by the style scheme set.

        The text on the GFX_GOL_CHECKBOX is drawn with the text
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
GFX_STATUS GFX_GOL_CheckBoxDraw(void *pObject);

#endif // _GFX_GOL_CHECKBOX_H
