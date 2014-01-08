/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_list_box.c

  Summary:
    This implements the list box object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    ListBox Object.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "gfx/gfx_gol_list_box.h"

#define GFX_GOL_LISTBOX_INDENT 2

// *****************************************************************************
/* Function:
    GFX_GOL_LISTBOX  *GFX_GOL_ListboxCreate(uint16_t ID, uint16_t left, uint16_t top,
                                     uint16_t right, uint16_t bottom, uint16_t state,
                                     GFX_XCHAR* pText, GFX_GOL_OBJ_SCHEME *pScheme)

  Summary:
    Creates a list box object with the parameters given.

  Description:
    This function creates a group box at the given position using state,
    pText, and pScheme.

  Precondition:
    None.

  Parameters:
         instance - device instance.
         ID - Unique user defined ID for the object instance.
         left - Left most position of the Object.
         top - Top most position of the Object.
	 right - Right most position of the Object.
         bottom - Bottom most position of the object.
         state - Sets the initial state of the object.
         pText - The pointer to the text used for the group box.
				 Length of string must be checked not to exceed the
				 object’s width. Clipping is not supported for the
				 text of this object.
         pScheme - Pointer to the style scheme used for the object.
				   Set to NULL if default style scheme is used.

  Returns:
    Returns a pointer to the list box.

  Example:
    None.

  Remarks:
    None.
*/
GFX_GOL_LISTBOX *GFX_GOL_ListboxCreate(
                  uint16_t ID,
                  uint16_t left,
                  uint16_t top,
                  uint16_t right,
                  uint16_t bottom,
                  uint16_t state,
                  GFX_XCHAR *pText,
                  GFX_ALIGNMENT       alignment,
                  GFX_GOL_OBJ_SCHEME *pScheme)
{
    GFX_GOL_LISTBOX *pLb = NULL;
    GFX_XCHAR *pointer;
    uint16_t counter;

    pLb = (GFX_GOL_LISTBOX *) GFX_malloc(sizeof (GFX_GOL_LISTBOX));

    if (pLb == NULL)
        return (pLb);

    // = instance;
    pLb->hdr.ID = ID;
    pLb->hdr.pNxtObj = NULL;
    pLb->hdr.type = GFX_GOL_LISTBOX_TYPE;
    pLb->hdr.left = left;
    pLb->hdr.top = top;
    pLb->hdr.right = right;
    pLb->hdr.bottom = bottom;
    pLb->hdr.state = state;
    pLb->pItemList = NULL;
    pLb->scrollY = 0;
    pLb->itemsNumber = 0;
    pLb->hdr.DrawObj = GFX_GOL_ListBoxDraw; // draw function
    pLb->hdr.actionGet = GFX_GOL_ListBoxActionGet; // message function
    pLb->hdr.actionSet = GFX_GOL_ListBoxActionSet; // default message function
    pLb->hdr.FreeObj = GFX_GOL_ListBoxItemListRemove; // free function
    pLb->alignment = alignment;
    
    // Set the style scheme to be used
    pLb->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *) pScheme;

    pLb->textHeight = GFX_TextStringHeightGet(pLb->hdr.pGolScheme->pFont);

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *) pLb);

    // Add items if there's an initialization text (each line will become one item,
    // lines must be separated by '\n' character)
    if (pText != NULL)
    {
        pointer = pText;
        counter = 0;
        while (*pointer)
        {
            if (NULL == GFX_GOL_ListBoxItemAdd(pLb, NULL, pointer, NULL, 0, counter))
                break;
            while ((GFX_XCHAR) * pointer++ > (GFX_XCHAR) 31);
            if (*(pointer) == 0)
                break;
            counter++;
        }
    }

    pLb->pFocusItem = pLb->pItemList;

    // Set focus for the object if GFX_GOL_STATE_FOCUSED state is set
#ifdef USE_FOCUS
    if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_FOCUSED))
        GFX_GOL_FocusSet((GFX_GOL_HEADER *) pLb);
#endif
    return (pLb);
}

// *****************************************************************************
/* Function:
    LISTITEM* GFX_GOL_ListboxItemAdd(GFX_GOL_LISTBOX *pLb, LISTITEM *pPrevItem,
                                      GFX_XCHAR *pText, void* pBitmap,
                                      uint16_t status, uint16_t data)

  Summary:
    Allocates memory for a new item.

  Description:
    This function allocates memory for a new item and adds it to the list box.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the list box,
         pPrevItem - pointer to the item after which a new item must be inserted,
                     if this pointer is NULL, the item will be appended at the end of the items list,
         pText -  pointer to the text,
         pBitmap - pointer to the bitmap,
         status - status after creation,
         data -  some data associated with the ite

  Returns:
    Returns a pointer to the list box of created, otherwise NULL.

  Example:
    None.

  Remarks:
    None.
*/
GFX_GOL_LISTITEM *GFX_GOL_ListBoxItemAdd(GFX_GOL_LISTBOX *pObject, GFX_GOL_LISTITEM *pPrevItem, GFX_XCHAR *pText, GFX_RESOURCE_HDR *pImage, uint16_t status, uint16_t data)
{
    GFX_GOL_LISTITEM *pItem;
    GFX_GOL_LISTITEM *pCurItem;

    pItem = (GFX_GOL_LISTITEM *) GFX_malloc(sizeof (GFX_GOL_LISTITEM));

    if (pItem == NULL)
    {
        return (NULL);
    }

    pObject->itemsNumber++;

    if (pObject->pItemList == NULL)
    {
        pObject->pItemList = pItem;
        pItem->pNextItem = NULL;
        pItem->pPrevItem = NULL;
    }
    else
    {
        if (pPrevItem == NULL)
        {

            // Find last item
            pCurItem = (GFX_GOL_LISTITEM *) pObject->pItemList;
            while (pCurItem->pNextItem != NULL)
                pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
        }
        else
        {
            pCurItem = (GFX_GOL_LISTITEM *) pPrevItem;
        }

        // Insert a new item
        pItem->pNextItem = pCurItem->pNextItem;
        pItem->pPrevItem = pCurItem;
        pCurItem->pNextItem = pItem;
    }

    pItem->pText = pText;
    pItem->pImage = pImage;
    pItem->status = status;
    pItem->data = data;

    return (pItem);
}

// *****************************************************************************
/* Function:
    void GFX_GOL_ListboxItemDelete(LISTBOX *pLb, LISTITEM *pItem))

  Summary:
    Removes an item from the list box.

  Description:
    This function removes an item from the list box and frees memory.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the object,
         pItem - the pointer to the item must be deleted

  Returns:
    None.

  Example:
    None.

  Remarks:
    None.
*/
void GFX_GOL_ListBoxItemRemove(GFX_GOL_LISTBOX *pLb, GFX_GOL_LISTITEM *pItem)
{
    if (pItem->pNextItem != NULL)
    {
        ((GFX_GOL_LISTITEM *) pItem->pNextItem)->pPrevItem = pItem->pPrevItem;
        if (pItem->pPrevItem == NULL)
            pLb->pItemList = (GFX_GOL_LISTITEM *) pItem->pNextItem;
    }

    if (pItem->pPrevItem != NULL)
        ((GFX_GOL_LISTITEM *) pItem->pPrevItem)->pNextItem = pItem->pNextItem;

    GFX_free(pItem);

    pLb->itemsNumber--;

    if (pLb->itemsNumber == 0)
        pLb->pItemList = NULL;
}

// *****************************************************************************
/* Function:
    void GFX_GOL_ListboxItemsListDelete(void *pObj)

  Summary:
    Removes all items from list box.

  Description:
    This function removes all items from list box and frees memory.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the object,

  Returns:
    None.

  Example:
    None.

  Remarks:
    None.
*/
void GFX_GOL_ListBoxItemListRemove(void *pObj)
{
    GFX_GOL_LISTITEM *pCurItem;
    GFX_GOL_LISTITEM *pItem;
    GFX_GOL_LISTBOX *pLb;

    pLb = (GFX_GOL_LISTBOX *) pObj;

    pCurItem = pLb->pItemList;

    while (pCurItem != NULL)
    {
        pItem = pCurItem;
        pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
        GFX_free(pItem);
    }

    pLb->pItemList = NULL;
    pLb->itemsNumber = 0;
}

// *****************************************************************************
/* Function:
    LISTITEM* GFX_GOL_ListboxSelectionGet(GFX_GOL_LISTBOX *pLb, LISTITEM *pFromItem)

  Summary:
    Searches for selected items.

  Description:
    This function searches for selected items using pFromItem.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the object,
         pFromItem - pointer to the item the seach must start from,
                 if the pointer is NULL the search begins from the
                 start of the items list

  Returns:
    None.

  Example:
    None.

  Remarks:
    None.
*/
GFX_GOL_LISTITEM *GFX_GOL_ListBoxSelectionGet(GFX_GOL_LISTBOX *pLb, GFX_GOL_LISTITEM *pFromItem)
{
    if (pFromItem == NULL)
    {
        pFromItem = pLb->pItemList;
    }

    while (pFromItem != NULL)
    {
        if (pFromItem->status & GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED)
            break;
        pFromItem = (GFX_GOL_LISTITEM *) pFromItem->pNextItem;
    }

    return (pFromItem);
}

// *****************************************************************************
/* Function:
   void GFX_GOL_ListboxSelectionChange(GFX_GOL_LISTBOX *pLb, LISTITEM *pItem)

  Summary:
    Changes selection status of an item.

  Description:
    This function changes selection status of pItem.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the object,
         pItem - pointer to the item the selection status will be changed

  Returns:
    None.

  Example:
    None.

  Remarks:
    None.
*/
void GFX_GOL_ListBoxSelectionChange(GFX_GOL_LISTBOX *pLb, GFX_GOL_LISTITEM *pItem)
{
    GFX_GOL_LISTITEM *pCurItem;

    if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_SINGLE_SELECT_STATE))
    {

        // Remove selection from all items
        pCurItem = pLb->pItemList;
        while (pCurItem != NULL)
        {
            if (pCurItem->status & GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED)
            {
                pCurItem->status &= ~GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED;
                pCurItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
            }

            pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
        }
    }

    pItem->status ^= GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED;
    pItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
}

// *****************************************************************************
/* Function:
   void GFX_GOL_ListboxFocusedItemSet(GFX_GOL_LISTBOX* pLb, uint16_t index)

  Summary:
    Sets focus for the item.

  Description:
    This function sets focus for the item at index.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the object
         index - item number from the list beginning

  Returns:
    None.

  Example:
    None.

  Remarks:
    None.
*/
void GFX_GOL_ListBoxFocusedItemSet(GFX_GOL_LISTBOX *pLb, uint16_t index)
{
    GFX_GOL_LISTITEM *pCurItem;

    // Look for item to be focused
    pCurItem = pLb->pItemList;

    if (pCurItem == NULL)
        return;

    while (pCurItem->pNextItem != NULL)
    {
        if (index <= 0)
            break;
        index--;
        pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
    }

    if (pCurItem != NULL)
    {
        if (pLb->pFocusItem != NULL)
        {
            pLb->pFocusItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
        }

        pLb->pFocusItem = pCurItem;
        pCurItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
    }
}

// *****************************************************************************
/* Function:
   uint16_t GFX_GOL_ListboxFocusedItemGet(GFX_GOL_LISTBOX* pLb)

  Summary:
    Returns focused item number from beginning of the list.

  Description:
    This function returns focused item number from beginning of the list.

  Precondition:
    None.

  Parameters:
         pLb - the pointer to the list box

  Returns:
    Returns the focused item.

  Example:
    None.

  Remarks:
    None.
*/
uint16_t GFX_GOL_ListBoxFocusedItemGet(GFX_GOL_LISTBOX *pLb)
{
    GFX_GOL_LISTITEM *pCurItem;
    uint16_t index;

    if (pLb->pFocusItem == NULL)
        return (-1);

    // Look for the focused item index
    index = 0;
    pCurItem = pLb->pItemList;
    while (pCurItem->pNextItem != NULL)
    {
        if (pCurItem == pLb->pFocusItem)
            break;
        index++;
        pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
    }

    return (index);
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_ListboxActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Overview: translates the GOL message for the list box
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_ListBoxActionGet(void *pObject,GFX_GOL_MESSAGE *pMessage)
{
    GFX_GOL_LISTBOX *pLb;

    pLb = (GFX_GOL_LISTBOX *) pObject;

    // Evaluate if the message is for the list box
    // Check if disabled first
    if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DISABLED_STATE))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

#ifdef USE_TOUCHSCREEN
    if (pMessage->type == TYPE_TOUCHSCREEN)
    {

        // Check if it falls in list box borders
        // We do not check any touch events here so application can have
        // the versatility to define the action on any of the touch events that
        // will be peformed on the list box. Once application sees the GFX_GOL_LISTBOX_ACTION_TOUCHSCREEN
        // reply (returned by this translate message function when touch was performed
        // on the list box), application can define any behavior for the list box.
        if
            (
             (pLb->hdr.left < pMessage->param1) &&
             (pLb->hdr.right > pMessage->param1) &&
             (pLb->hdr.top < pMessage->param2) &&
             (pLb->hdr.bottom > pMessage->param2)
             ) return (GFX_GOL_LISTBOX_ACTION_TOUCHSCREEN);
    }

#endif
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
        if ((uint16_t) pMessage->param1 == pLb->hdr.ID)
        {
            // Check of the event is done here to properly detect that a keyscan event occured.
            // GFX_GOL_LISTBOX_MSG_MOVE can move the highlight (selection) of the items on the list box when
            // scan up or down was performed (example: pressing up or down keys) or GFX_GOL_LISTBOX_MSG_SEL
            // can indicate to the application that the highlighted item is selected by the user.
            // Application can then call the application function that corresponds to the selected item.
            if (pMsg->uiEvent == EVENT_KEYSCAN)
            {
                if ((pMessage->param2 == SCAN_UP_PRESSED) || (pMessage->param2 == SCAN_DOWN_PRESSED))
                    return (GFX_GOL_LISTBOX_MSG_MOVE);

                if ((pMessage->param2 == SCAN_SPACE_PRESSED) || (pMessage->param2 == SCAN_CR_PRESSED))
                    return (GFX_GOL_LISTBOX_MSG_SEL);
            }

        }

#endif
    return (GFX_GOL_OBJECT_ACTION_INVALID);
}

/*********************************************************************
 * Function: void GFX_GOL_ListboxActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * Overview: changes the state of the list box by default
 *
 ********************************************************************/
void GFX_GOL_ListBoxActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg,void *pObject,GFX_GOL_MESSAGE *pMessage)
{

    GFX_GOL_LISTBOX *pLb;

    pLb = (GFX_GOL_LISTBOX *) pObject;

#ifdef USE_TOUCHSCREEN

    short pos;
    GFX_GOL_LISTITEM *pItem;

    if (pMessage->type == TYPE_TOUCHSCREEN)
    {
#ifdef USE_FOCUS
        if (pMessage->type == TYPE_TOUCHSCREEN)
        {
            if (!GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_FOCUSED))
            {
                GFX_GOL_FocusSet((GFX_GOL_HEADER *) pLb);
            }
        }

#endif
        if (pMessage->uiEvent == EVENT_PRESS)
        {
            pos = (pMessage->param2 - pLb->scrollY - pLb->hdr.top - GFX_GOL_LISTBOX_INDENT - GFX_GOL_EMBOSS_SIZE) / pLb->textHeight;
            pItem = (GFX_GOL_LISTITEM *) pLb->pItemList;
            while (pos)
            {
                if (pItem == NULL)
                    break;
                if (pItem->pNextItem == NULL)
                    break;
                pItem = (GFX_GOL_LISTITEM *) pItem->pNextItem;
                pos--;
            }

            if (pLb->pFocusItem != pItem)
            {
                pItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
                pLb->pFocusItem->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
                pLb->pFocusItem = pItem;
                GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
            }

            GFX_GOL_ListBoxSelectionChange(pLb, pItem);
            GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
        }
    }

#endif
#ifdef USE_KEYBOARD
    if (pMessage->type == TYPE_KEYBOARD)
    {
        switch (translatedMsg)
        {
            case GFX_GOL_LISTBOX_MSG_SEL:
                if (pLb->pFocusItem != NULL)
                    GFX_GOL_Listbox_SelChange(pLb, pLb->pFocusItem);
                GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS);
                break;

            case GFX_GOL_LISTBOX_MSG_MOVE:
                switch (pMessage->param2)
                {
                    case SCAN_UP_PRESSED:
                        GFX_GOL_Listbox_FocusedItemSet(pLb, LbGetFocusedItem(pLb) - 1);
                        GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS);
                        break;

                    case SCAN_DOWN_PRESSED:
                        GFX_GOL_Listbox_FocusedItemSet(pLb, LbGetFocusedItem(pLb) + 1);
                        GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS);
                        break;
                }

                break;
        }
    } // end of if
#endif
}

/*********************************************************************
 * Function: uint16_t GFX_GOL_ListboxDraw(void *pObj)
 *
 * Output: returns the status of the drawing
 *		  0 - not completed
 *         1 - done
 *
 * Overview: draws edit box
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_ListBoxDraw(void *pObject)
{

    typedef enum
    {
        GFX_GOL_LISTBOX_STATE_START,
        GFX_GOL_LISTBOX_STATE_PANEL,
        GFX_GOL_LISTBOX_STATE_DRAW_ITEMS,
        GFX_GOL_LISTBOX_STATE_DRAW_CURRENT_ITEMS,
        GFX_GOL_LISTBOX_STATE_SET_ERASEITEM,
        GFX_GOL_LISTBOX_STATE_ERASEITEM,
        GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS,
        GFX_GOL_LISTBOX_STATE_ITEMFOCUS,
        GFX_GOL_LISTBOX_STATE_GET_NEXTITEM,
        GFX_GOL_LISTBOX_STATE_BITMAP,
        GFX_GOL_LISTBOX_STATE_TEXT,
    } GFX_GOL_LISTBOX_DRAW_STATES;

    static GFX_GOL_LISTBOX_DRAW_STATES state = GFX_GOL_LISTBOX_STATE_START;
    static GFX_GOL_LISTITEM *pCurItem;
    static GFX_COLOR tempColor;
    static short temp;
    static GFX_STATUS index = GFX_STATUS_FAILURE;
    GFX_GOL_LISTBOX *pLb;

    pLb = (GFX_GOL_LISTBOX *) pObject;

    while (1)
    {
        switch (state)
        {
                // location of this case is strategic so the partial redraw
                // of the ListBox will be faster
            case GFX_GOL_LISTBOX_STATE_PANEL:
                if (GFX_GOL_PanelDraw() == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);

                state = GFX_GOL_LISTBOX_STATE_DRAW_ITEMS;
                break;

            case GFX_GOL_LISTBOX_STATE_START:

                /////////////////////////////////////////////////////////////////////
                // REMOVE FROM SCREEN
                /////////////////////////////////////////////////////////////////////
                if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_HIDE_STATE))
                {
                    GFX_ColorSet(pLb->hdr.pGolScheme->CommonBkColor);
                    if (GFX_RectangleFillDraw(pLb->hdr.left, pLb->hdr.top, pLb->hdr.right, pLb->hdr.bottom) == GFX_STATUS_FAILURE)
                        return (GFX_STATUS_FAILURE);
                    return (GFX_STATUS_SUCCESS);
                }

                if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DRAW_FOCUS_STATE))
                {
                    if (pLb->pFocusItem != NULL)
                        ((GFX_GOL_LISTITEM *) pLb->pFocusItem)->status |= GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_ITEMS_STATE);
                }

                /////////////////////////////////////////////////////////////////////
                // GFX_GOL_STATE_DRAW PANEL
                /////////////////////////////////////////////////////////////////////
                if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DRAW_STATE))
                {
                    if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DISABLED_STATE))
                    {
                        tempColor = pLb->hdr.pGolScheme->ColorDisabled;
                    }
                    else
                    {
                        tempColor = pLb->hdr.pGolScheme->Color0;
                    }

                    GFX_GOL_PanelParameterSet
                            (
                             
                             pLb->hdr.left,
                             pLb->hdr.top,
                             pLb->hdr.right,
                             pLb->hdr.bottom,
                             0,
                             tempColor,
                             pLb->hdr.pGolScheme->EmbossDkColor,
                             pLb->hdr.pGolScheme->EmbossLtColor,
                             NULL,
                             GFX_FILL_STYLE_COLOR,
                             GFX_GOL_EMBOSS_SIZE
                             );

                    state = GFX_GOL_LISTBOX_STATE_PANEL;
                    break;
                }
                else
                {
                    state = GFX_GOL_LISTBOX_STATE_DRAW_ITEMS;
                }

            case GFX_GOL_LISTBOX_STATE_DRAW_ITEMS:

                /////////////////////////////////////////////////////////////////////
                // GFX_GOL_STATE_DRAW ITEMS
                /////////////////////////////////////////////////////////////////////
                GFX_FontSet(pLb->hdr.pGolScheme->pFont);

                // Set graphics cursor
                GFX_LinePositionSet(pLb->hdr.left + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT, pLb->hdr.top + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT + pLb->scrollY);

                pCurItem = pLb->pItemList;
                state = GFX_GOL_LISTBOX_STATE_DRAW_CURRENT_ITEMS;

            case GFX_GOL_LISTBOX_STATE_DRAW_CURRENT_ITEMS:

                /////////////////////////////////////////////////////////////////////
                // GFX_GOL_STATE_DRAW CURRENT ITEM
                /////////////////////////////////////////////////////////////////////

                // check if at the end of the list of items
                // this is the exit from the drawing state machine
                if (pCurItem == NULL)
                {
                    state = GFX_GOL_LISTBOX_STATE_START;

                    return (GFX_STATUS_SUCCESS);
                }

                /////////////////////////////////////////////////////////////////////
                // pCurItem is a valid item, check first if within the bounds
                /////////////////////////////////////////////////////////////////////
                if (GFX_LinePositionYGet() >= pLb->hdr.bottom - GFX_GOL_EMBOSS_SIZE - GFX_GOL_LISTBOX_INDENT)
                {
                    state = GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS;
                    break;
                }
                // yes, still within bounds process the item
                if ((GFX_LinePositionYGet() + pLb->textHeight) >= (pLb->hdr.top + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT))
                {
                    if (!GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DRAW_STATE))
                        if (!(pCurItem->status & GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW))
                        {
                            state = GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS;
                            break;
                        }

                    pCurItem->status &= ~GFX_GOL_LISTBOX_ITEM_STATUS_REDRAW;
                    state = GFX_GOL_LISTBOX_STATE_SET_ERASEITEM;
                }
                else
                {
                    state = GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS;
                    break;
                }

            case GFX_GOL_LISTBOX_STATE_SET_ERASEITEM:

                if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DISABLED_STATE))
                {
                    tempColor = pLb->hdr.pGolScheme->ColorDisabled;
                }
                else
                {
                    tempColor = pLb->hdr.pGolScheme->Color0;

                    if (pCurItem != NULL)
                        if (pCurItem->status & GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED)
                        {
                            tempColor = pLb->hdr.pGolScheme->Color1;
                        }             
                }
                state = GFX_GOL_LISTBOX_STATE_ERASEITEM;

            case GFX_GOL_LISTBOX_STATE_ERASEITEM:
                GFX_ColorSet(tempColor);
                if
                    (
                     GFX_RectangleFillDraw
                     (         
                      pLb->hdr.left + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT,
                      GFX_LinePositionYGet(),
                      pLb->hdr.right - GFX_GOL_EMBOSS_SIZE - GFX_GOL_LISTBOX_INDENT,
                      GFX_LinePositionYGet() + pLb->textHeight
                      ) == GFX_STATUS_FAILURE
                     ) return (GFX_STATUS_FAILURE);

                if (pLb->alignment == GFX_ALIGN_LEFT)
                {
                    GFX_LinePositionSet(pLb->hdr.left + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT, GFX_LinePositionYGet());
                }
                else
                {
                    temp = GFX_TextStringWidthGet(pCurItem->pText, pLb->hdr.pGolScheme->pFont);
                    if (pCurItem->pImage != NULL)
                    {
                        temp += GFX_ImageWidthGet(pCurItem->pImage) + GFX_GOL_LISTBOX_INDENT;
                    }

                    if (pLb->alignment == GFX_ALIGN_RIGHT)
                    {
                        GFX_LinePositionSet(pLb->hdr.right - temp - GFX_GOL_LISTBOX_INDENT - GFX_GOL_EMBOSS_SIZE, GFX_LinePositionYGet());
                    }
                    else
                    {
                        GFX_LinePositionSet((pLb->hdr.left + pLb->hdr.right - temp) >> 1, GFX_LinePositionYGet());
                    }
                }

                if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_DISABLED_STATE))
                {
                        tempColor = pLb->hdr.pGolScheme->TextColorDisabled;
                }
                else
                {
                    if (pCurItem->status & GFX_GOL_LISTBOX_ITEM_STATUS_SELECTED)
                    {
                        tempColor = pLb->hdr.pGolScheme->TextColor1;
                    }
                    else
                    {
                        tempColor = pLb->hdr.pGolScheme->TextColor0;
                    }
                }

                if (pCurItem->pImage != NULL)
                {
                state = GFX_GOL_LISTBOX_STATE_BITMAP;

            case GFX_GOL_LISTBOX_STATE_BITMAP:

                    // check if the image will go beyond the list box (bottom check only)
                    if ((GFX_LinePositionYGet() + GFX_TextStringHeightGet(pCurItem->pImage)) < pLb->hdr.bottom)
                    {
                        if
                            (
                             GFX_ImageDraw
                             (                     
                              GFX_LinePositionXGet(),
                              GFX_LinePositionYGet() + ((pLb->textHeight - GFX_TextStringHeightGet(pCurItem->pImage)) >> 1),
                              pCurItem->pImage
                              ) == GFX_STATUS_FAILURE
                             ) return (GFX_STATUS_FAILURE);
                    }

                    GFX_LinePositionRelativeSet(GFX_ImageWidthGet(pCurItem->pImage) + GFX_GOL_LISTBOX_INDENT, 0);
                }

                state = GFX_GOL_LISTBOX_STATE_TEXT;

            case GFX_GOL_LISTBOX_STATE_TEXT:

                GFX_ColorSet(tempColor);
                index = GFX_TextStringBoxDraw(
                                             pLb->hdr.left + GFX_GOL_EMBOSS_SIZE + 2,
                                             GFX_LinePositionYGet(),
                                             pLb->hdr.right - pLb->hdr.left - (GFX_GOL_EMBOSS_SIZE + 2 << 1),
                                             pLb->hdr.bottom - pLb->hdr.top - (GFX_GOL_EMBOSS_SIZE + 2 << 1),
                                             pCurItem->pText, 0, pLb->alignment);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
                
                state = GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS;

                /////////////////////////////////////////////////////////////////////

            case GFX_GOL_LISTBOX_STATE_SET_ITEMFOCUS:
                if (pLb->pFocusItem == pCurItem)
                {
                    temp = GFX_LinePositionYGet();
                    state = GFX_GOL_LISTBOX_STATE_ITEMFOCUS;
                }
                else
                {
                    state = GFX_GOL_LISTBOX_STATE_GET_NEXTITEM;
                    break;
                }

            case GFX_GOL_LISTBOX_STATE_ITEMFOCUS:
                    if (GFX_GOL_ObjectStateGet(pLb, GFX_GOL_LISTBOX_FOCUSED_STATE))
                    {
                        GFX_ColorSet(pLb->hdr.pGolScheme->TextColor1);
                    }
                    else
                    {
                        GFX_ColorSet(pLb->hdr.pGolScheme->TextColor0);
                    }

                GFX_LineStyleSet(GFX_GOL_FOCUS_LINE);

                index = GFX_RectangleDraw(
                                     pLb->hdr.left + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT,
                                     GFX_LinePositionYGet(),
                                     pLb->hdr.right - GFX_GOL_EMBOSS_SIZE - GFX_GOL_LISTBOX_INDENT,
                                     GFX_LinePositionYGet() + pLb->textHeight - 1);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }

                GFX_LinePositionSet(0, temp);
                GFX_LineStyleSet(GFX_LINE_STYLE_THIN_SOLID);

                // Scroll if needed
                if (GFX_LinePositionYGet() < (pLb->hdr.top + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT))
                {
                    pLb->scrollY += (pLb->hdr.top + GFX_GOL_EMBOSS_SIZE + GFX_GOL_LISTBOX_INDENT) - GFX_LinePositionYGet();
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_STATE);
                    state = GFX_GOL_LISTBOX_STATE_DRAW_ITEMS;
                    break;
                }

                if ((GFX_LinePositionYGet() + pLb->textHeight) > (pLb->hdr.bottom - GFX_GOL_EMBOSS_SIZE - GFX_GOL_LISTBOX_INDENT))
                {
                    pLb->scrollY += pLb->hdr.bottom - GFX_LinePositionYGet() - pLb->textHeight - GFX_GOL_EMBOSS_SIZE - GFX_GOL_LISTBOX_INDENT;
                    GFX_GOL_ObjectStateSet(pLb, GFX_GOL_LISTBOX_DRAW_STATE);
                    state = GFX_GOL_LISTBOX_STATE_DRAW_ITEMS;
                    break;
                }
                state = GFX_GOL_LISTBOX_STATE_GET_NEXTITEM;

            case GFX_GOL_LISTBOX_STATE_GET_NEXTITEM:

                pCurItem = (GFX_GOL_LISTITEM *) pCurItem->pNextItem;
                GFX_LinePositionRelativeSet(0, pLb->textHeight);
                state = GFX_GOL_LISTBOX_STATE_DRAW_CURRENT_ITEMS;
                break;

        } // end of switch
    } // end of while(1)
}
