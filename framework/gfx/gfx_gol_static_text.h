/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_static_text.h

  Summary:
    This is the header file for the static text object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Static Text Object.
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

#ifndef _GFX_GOL_STATICTEXT_H
    #define _GFX_GOL_STATICTEXT_H

#include <stdint.h>
#include "gfx/gfx_gol.h"

/*********************************************************************
* Object States Definition: 
*********************************************************************/
typedef enum
{
    GFX_GOL_STATICTEXT_DISABLED_STATE     = 0x0002,  // Bit for disabled state.
    GFX_GOL_STATICTEXT_FRAME_STATE        = 0x0010,  // Bit to indicate frame is enabled.
    GFX_GOL_STATICTEXT_NOBACKGROUND_STATE = 0x0020,  // Bit to indicate background is enabled.
    GFX_GOL_STATICTEXT_DRAW_UPDATE        = 0x2000,  // Bit to indicate object must be redrawn.
    GFX_GOL_STATICTEXT_DRAW_STATE         = 0x4000,  // Bit to indicate object must be redrawn.
    GFX_GOL_STATICTEXT_HIDE_STATE         = 0x8000,  // Bit to indicate object must be removed from screen.
} GFX_GOL_STATICTEXT_STATE;

/*********************************************************************
* Overview: Defines the parameters required for a Static Text Object.
*
*********************************************************************/
typedef struct
{
    GFX_GOL_OBJ_HEADER   hdr;       // Generic header for all Objects (see OBJ_HEADER).
    GFX_XCHAR           *pText;     // The pointer to text used.
    GFX_ALIGNMENT        alignment; // text alignment
} GFX_GOL_STATICTEXT;

// *****************************************************************************
/*  Function:
    GFX_GOL_STATICTEXT  *GFX_GOL_StaticTextCreate(
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
        This function creates a GFX_GOL_STATICTEXT object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.


    Description:
        This function creates a GFX_GOL_STATICTEXT object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

        This function returns the pointer to the newly created object.
        If the object is not successfully created, it returns NULL.

        The text can be configured to have text aligned. See GFX_ALIGNMENT
        for details. Text can also have multiple lines by inserting
        the new line character to the text string supplied to the object.
        Any string that exceeds the dimension of the object will be clipped.

        When the object is used with no background, application must manage
        the object when text is modified and redrawn. i.e. the previous
        text must be removed. Use GFX_GOL_STATICTEXT_NOBACKGROUND_STATE
        state bit to disable the background.

        The behavior of GFX_GOL_StaticTextCreate() will be undefined if one
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
            // assume pScheme is initialized
            GFX_GOL_OBJ_SCHEME *pScheme;
            GFX_GOL_STATICTEXT *pSt;

            pScheme = GOLCreateScheme();
            StCreate(
                ID_STATICTEXT1,                 // ID
	        30,80,235,160,                  // dimension
	        GFX_GOL_STATICTEXT_DRAW_STATE,  // draw the object
	        "Static Text\n Example",        // 2 lines of text
                GFX_ALIGN_CENTER,               // align text on the center
	        pScheme);                       // use given scheme

        </code>

*/
// *****************************************************************************
GFX_GOL_STATICTEXT  *GFX_GOL_StaticTextCreate(
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
    GFX_XCHAR *GFX_GOL_StaticTextGet(
                                GFX_GOL_STATICTEXT *pObject)

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
            GFX_XCHAR *pChar;
            GFX_GOL_STATICTEXT OBJECT_ARRAY[2];

            pChar = GFX_GOL_StaticTextGet(OBJECT_ARRAY[0]);
       </code>

*/
// *****************************************************************************
GFX_XCHAR *GFX_GOL_StaticTextGet(GFX_GOL_STATICTEXT *pObject);


// *****************************************************************************
/*  Function:
    GFX_XCHAR *GFX_GOL_StaticTextSet(
                                GFX_GOL_STATICTEXT *pObject,
                                GFX_XCHAR *pText)

    Summary:
        This function sets the address of the current text
        string used by the object.

    Description:
        This function sets the address of the current text
        string used by the object.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.
        pText - pointer to the text string to be used.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_StaticTextSet(
                                GFX_GOL_STATICTEXT *pObject,
                                GFX_XCHAR *pText);

// *****************************************************************************
/*  Function:
    GFX_ALIGNMENT GFX_GOL_StaticTextAlignmentGet(
                                GFX_GOL_STATICTEXT *pObject)

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
GFX_ALIGNMENT GFX_GOL_StaticTextAlignmentGet(GFX_GOL_STATICTEXT *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_StaticTextAlignmentSet(
                                GFX_GOL_STATICTEXT *pObject,
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
void GFX_GOL_StaticTextAlignmentSet(GFX_GOL_STATICTEXT *pObject, GFX_ALIGNMENT align);

/*******************************************************************************************
  Function:
      GFX_GOL_TRANSLATED_ACTION GFX_GOL_StaticTextActionGet(
                                  void *pObject,
                                  GFX_GOL_MESSAGE *pMessage);
    
  Summary:
    This function sets the text alignment of the text string used by the
    object.
  Description:
    This function evaluates the message from a user if the message will
    affect the object or not. The table below enumerates the action for
    each event of the touch screen inputs.
    
    <table>
    Translated Message                   \Input   Events          \Description
                                          Source                   
    GFX_GOL_STATICTEXT_ACTION_SELECTED   Touch    EVENT_PRESS,    If events occurs and the
                                          Screen   EVENT_RELEASE   x,y position falls in the
                                                                   area of the static text.
    GFX_GOL_OBJECT_ACTION_INVALID        Any      Any             If the message did not
                                                                   affect the object.
    </table>
  Conditions:
    Object must exist in memory.
  Input:
    pObject -   The pointer to the object where the message will be
                evaluated to check if the message will affect the object.
    pMessage -  Pointer to the message from the user interface.
  Return:
      * GFX_GOL_STATICTEXT_ACTION_SELECTED – Object is selected
      * GFX_GOL_OBJECT_ACTION_INVALID – Object is not affected
  Example:
    None.                                                                                   
  ******************************************************************************************
  ##################                  ############     ######                      ###########*/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_StaticTextActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_StaticTextDraw(void *pObject)

    Summary:
        This function renders the object on the screen based on the
        current state of the object.

    Description:
        This function renders the object on the screen based on the
        current state of the object. Location of the object is
        determined by the left, top, right and bottom parameters.
        The colors used are dependent on the state of the object.
        The font used is determined by the style scheme set.

        Text alignment based on the alignment parameter set on the object.

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
GFX_STATUS GFX_GOL_StaticTextDraw(void *pObject);

#endif // _GFX_GOL_STATICTEXT_H
