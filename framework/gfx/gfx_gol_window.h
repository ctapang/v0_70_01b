/*******************************************************************************
  Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol_window.h

  Summary:
    This is the header file for the window object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    Window Object.

*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END


#ifndef _GFX_GOL_WINDOW_H
    #define _GFX_GOL_WINDOW_H

// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************

#include <gfx/gfx_gol.h>

/*********************************************************************
* Object States Definition: 
*********************************************************************/
typedef enum
{
    GFX_GOL_WINDOW_FOCUSED_STATE       =  0x0001,  // Bit for focus state
    GFX_GOL_WINDOW_DISABLED_STATE      =  0x0002,  // Bit for disabled state
    GFX_GOL_WINDOW_TITLECENTER_STATE   =  0x0004,  // Bit to center the text on the Title Area
    GFX_GOL_WINDOW_HIDE_STATE          =  0x8000,  // Bit to indicate window must be removed from screen
    GFX_GOL_WINDOW_DRAW_CLIENT_STATE   =  0x4000,  // Bit to indicate client area must be redrawn
    GFX_GOL_WINDOW_DRAW_TITLE_STATE    =  0x2000,  // Bit to indicate title area must be redrawn
    GFX_GOL_WINDOW_DRAW_STATE          =  0x6000,  // Bits to indicate whole window must be redrawn
} GFX_GOL_WINDOW_STATE;
// *****************************************************************************
// *****************************************************************************
// Section: type definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*

  Summary:
     The structure contains data for the window

  Description:

  Remarks:

*/
typedef struct
{
    GFX_GOL_OBJ_HEADER      hdr;        // Generic header for all Objects (see GFX_GOL_OBJ_HEADER).
    uint16_t                textHeight; // Pre-computed text height
    GFX_XCHAR               *pText;     // Pointer to the title text
    GFX_ALIGNMENT           alignment;  // text alignment
    GFX_RESOURCE_HDR        *pBitmap;   // Pointer to the bitmap for the title bar
} GFX_GOL_WINDOW;


// *****************************************************************************
// *****************************************************************************
// Section: Graphics Module Initialization Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*  Function:
    GFX_GOL_WINDOW  *GFX_GOL_WindowCreate(
                                uint16_t            ID,
                                uint16_t            left,
                                uint16_t            top,
                                uint16_t            right,
                                uint16_t            bottom,
                                uint16_t            state,
                                GFX_RESOURCE_HDR    *pImage,
                                GFX_XCHAR           *pText,
                                GFX_ALIGNMENT       alignment,
                                GFX_GOL_OBJ_SCHEME  *pScheme)
    Summary:
        This function creates a GFX_GOL_WINDOW object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

    Description:
        This function creates a GFX_GOL_WINDOW object with the parameters
        given. It automatically attaches the new object into a global
        linked list of objects and returns the address of the object.

        This function returns the pointer to the newly created object.
        If the object is not successfully created, it returns NULL.

    Precondition:
        None.

    Parameters:
        ID - Unique user defined ID for the object instance.
        left - Left most position of the object.
        top - Top most position of the object.
        right - Right most position of the object.
        bottom - Bottom most position of the object.
        state - Sets the initial state of the object.
        pImage - Pointer to the image used on the face of the object.
        pText - Pointer to the text of the object.
        alignment - text alignment of the text used in the object.
        pScheme - Pointer to the style scheme used.

    Returns:
        Pointer to the newly created object.

    Example:
        <code>
            GFX_GOL_OBJ_SCHEME *pScheme;
            GFX_GOL_WINDOW *pWindow;
            GFX_GOL_WINDOW_STATE state;

            // assume pScheme is initialized to a scheme in memory.
            state = GFX_GOL_WINDOW_DRAW_STATE;


            pWindow  = GFX_GOL_WindowCreate(1,			// ID
                   0,0,GFX_Primitive_MaxXGet(),GFX_Primitive_MaxYGet(),	// whole screen dimension
                   state,					// set state to draw all
                   (char*)myIcon,				// icon
                   "Place Title Here.",		                // text
                   NULL);					// use default GOL scheme

            if (pWindow == NULL)
                return 0;

            return 1;
        </code>

*/

GFX_GOL_WINDOW  *GFX_GOL_WindowCreate
        (
            uint16_t            ID,
            uint16_t            left,
            uint16_t            top,
            uint16_t            right,
            uint16_t            bottom,
            uint16_t            state,
            void                *pBitmap,
            GFX_XCHAR           *pText,
            GFX_ALIGNMENT       alignment,
            GFX_GOL_OBJ_SCHEME  *pScheme
        );

// *****************************************************************************
/*  Function:
    GFX_RESOURCE_HDR *GFX_GOL_windowImageGet(
                                GFX_GOL_WINDOW *pObject)

    Summary:
        This function gets the image.

    Description:
        This function gets the image used.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.

    Returns:
        Pointer to the image resource.

    Example:
        None.

*/
// *****************************************************************************
#define GFX_GOL_WindowImageGet(pObject, pImage) \
            (((GFX_GOL_WINDOW *)pObject)->pImage)

// *****************************************************************************
/*  Function:
    GFX_RESOURCE_HDR *GFX_GOL_WindowImageGet(
                                GFX_GOL_WINDOW *pObject)

    Summary:
        This function gets the image used.

    Description:
        This function gets the image used.

    Precondition:
        Object must exist in memory.

    Parameters:
        pObject - pointer to the object.

    Returns:
        Pointer to the image resource.

    Example:
        None.

*/
// *****************************************************************************
#define GFX_GOL_WindowImageGet(pObject, pImage) \
            (((GFX_GOL_WINDOW *)pObject)->pImage)

// *****************************************************************************
/*  Function:
    GFX_XCHAR *GFX_GOL_WindowTextGet(
                                GFX_GOL_WINDOW *pObject)

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
            GFX_GOL_WINDOW pWindow;

            pChar = GFX_GOL_WindowTextGet(pWindow);
       </code>

*/
// *****************************************************************************
#define GFX_GOL_WindowTextGet(pObject)  (((GFX_GOL_WINDOW *)pObject)->pText)

// *****************************************************************************
/*  Function:
    GFX_XCHAR *GFX_GOL_WindowTextSet(
                                GFX_GOL_WINDOW *pObject,
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
        <code>
           GFX_XCHAR Label0[] = ?ON?;
           GFX_XCHAR Label1[] = ?OFF?;
           GFX_GOL_WINDOW pWindow;

           GFX_GOL_WindowTextSet(pWindow, Label0);
           GFX_GOL_WindowTextSet(pWindow, Label1);
       </code>

*/
// *****************************************************************************
void GFX_GOL_WindowTextSet(GFX_GOL_WINDOW *pObject, GFX_XCHAR * pText);

// *****************************************************************************
/*  Function:
    GFX_ALIGNMENT GFX_GOL_WindowTextAlignmentGet(
                                GFX_GOL_WINDOW *pObject)

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
GFX_ALIGNMENT GFX_GOL_WindowTextAlignmentGet(GFX_GOL_WINDOW *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_WindowTextAlignmentSet(
                                GFX_GOL_WINDOW *pObject,
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
void GFX_GOL_WindowTextAlignmentSet(
                                GFX_GOL_WINDOW *pObject,
                                GFX_ALIGNMENT align);

/****************************************************************************
  Function:
      GFX_GOL_TRANSLATED_ACTION GFX_GOL_WindowActionGet(
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
    Translated                      \Input Source Events Description
     Message                         
    GFX_GOL_WINDOW_ACTION_TITLE     Touch Screen EVENT_PRESS, EVENT_RELEASE,
                                     EVENT_MOVE If events occurs and the x,y
                                     position falls in the TITLE area of the
                                     window
    GFX_GOL_WINDOW_ACTION_CLIENT    Touch Screen EVENT_PRESS, EVENT_RELEASE,
                                     EVENT_MOVE If events occurs and the x,y
                                     position falls in the CLIENT area of the
                                     window
    GFX_GOL_OBJECT_ACTION_INVALID   Any If the message did not affect the
                                     object.
    </table>
  Conditions:
    Object must exist in memory.
  Input:
    pObject -   The pointer to the object where the message will be
                evaluated to check if the message will affect the object.
    pMessage -  Pointer to the message from the user interface.
  Return:
      * GFX_GOL_WINDOW_ACTION_CLIENT // Window client area selected action
        ID.
      * GFX_GOL_WINDOW_ACTION_TITLE // Window title bar selected action ID.
  Example:
    None.                                                                    
  ***************************************************************************
  ##################                       ############  ######                                   ###########*/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_WindowActionGet(
                                void *pObject,
                                GFX_GOL_MESSAGE *pMessage);


// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_WindowDraw(void *pObject)

    Summary:
        This function renders the object on the screen based on the
        current state of the object.

    Description:
        This function renders the object on the screen based on the
        current state of the object. Location of the object is
        determined by the left, top, right and bottom parameters.
        The colors used are dependent on the state of the object.
        The font used is determined by the style scheme set.

        The text on the face of the GFX_GOL_WINDOW is drawn on top of
        the bitmap. Text alignment based on the alignment parameter
        set on the object.

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
GFX_STATUS GFX_GOL_WindowDraw(void *pObject);

#endif // _GFX_GOL_WINDOW_H
