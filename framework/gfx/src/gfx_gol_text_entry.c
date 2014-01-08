/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  GOL Layer 
 *  TextEntry
 *****************************************************************************
 * File Name:       Textentry.c
 * Dependencies:    Textentry.h
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30 Version 3.00, C32
 * Linker:          MPLAB LINK30, LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 10/24/08	    ...
 * 07/01/09	    Updated for 2D accelerated primitive support.
 * 04/15/10	    Corrected TeSetBuffer() issue on string max size.
 * 08/04/11     Modified widget draw states to correct flow of rendering.
 *              Added check on the GFX_RectangleDraw() calls in cases when the non-blocking
 *              is used.
 * 12/02/11     Fix memory leak issue when TeCreateKeyMembers fails to allocate
 *              memory for all keys.
 * 12/13/11     Fix issue when displaying string with length equal to max size.
 * 03/05/12     - Added Gradient feature.
 *              - Enabled use of rounded buttons. User can now specify the rounded
 *                edge radius in the GraphicsConfing.h file. 
*                 (See TE_ROUNDEDBUTTON_RADIUS macro for deatils).
 *****************************************************************************/
#include "gfx/gfx.h"

#ifdef USE_TEXTENTRY

/*********************************************************************
* Function: GFX_OBJ_TEXTENTRY *TeCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t state
*					uint16_t horizontalKeys, uint16_t verticalKeys, XCHAR *pText[],
*					void *pBuffer, uint16_t bufferLength, void *pDisplayFont, 
*					GFX_OBJ_SCHEME *pScheme)
*
*
* Notes: 
*
********************************************************************/
GFX_OBJ_TEXTENTRY *GFX_GOL_TextEntryCreate
(
    uint8_t     instance,
    uint16_t        ID,
    uint16_t       left,
    uint16_t       top,
    uint16_t       right,
    uint16_t       bottom,
    uint16_t        state,
    uint16_t       horizontalKeys,
    uint16_t       verticalKeys,
    XCHAR       *pText[],
    void        *pBuffer,
    uint16_t        bufferLength,
    void        *pDisplayFont,
    GFX_OBJ_SCHEME  *pScheme
)
{
    GFX_OBJ_TEXTENTRY   *pTe = NULL;                    //Text entry
    pTe = (GFX_OBJ_TEXTENTRY *)GFX_malloc(sizeof(GFX_OBJ_TEXTENTRY));
    if(pTe == NULL)
        return (NULL);

    pTe->hdr.ID = ID;
    pTe->hdr.pNxtObj = NULL;
    pTe->hdr.type = OBJ_TEXTENTRY;              // set object type
    pTe->hdr.left = left;                       // left parameter of the text-entry
    pTe->hdr.top = top;                         // top parameter of the text-entry
    pTe->hdr.right = right;                     // right parameter of the text-entry
    pTe->hdr.bottom = bottom;                   // bottom parameter of the text-entry
    pTe->hdr.state = state;                     // State of the Text-Entry
    pTe->horizontalKeys = horizontalKeys;       // number of horizontal keys
    pTe->verticalKeys = verticalKeys;           // number of vertical keys
    pTe->CurrentLength = 0;                     // current length of text
    pTe->pHeadOfList = NULL;
    GFX_GOL_TextEntrySetBuffer(pTe, pBuffer, bufferLength);    // set the text to be displayed buffer length is also initialized in this call
    pTe->pActiveKey = NULL;
    pTe->hdr.DrawObj = GFX_GOL_TextEntryDraw;					// draw function
    pTe->hdr.MsgObj = GFX_GOL_TextEntryActionGet;			// message function
    pTe->hdr.MsgDefaultObj = GFX_GOL_TextEntryActionSet;		// default message function
    pTe->hdr.FreeObj = GFX_GOL_TextEntryDelKeyMembers;			// free function

    // Set the color scheme to be used
    if(pScheme == NULL)
        pTe->hdr.pGolScheme = _pDefaultGolScheme;
    else
        pTe->hdr.pGolScheme = (GFX_OBJ_SCHEME *)pScheme;

    // Set the font to be used
    if(pDisplayFont == NULL)
        pTe->pDisplayFont = (void *) &FONTDEFAULT;
    else
        pTe->pDisplayFont = pDisplayFont;

    //check if either values of horizontal keys and vertical keys are equal to zero
    if((pTe->horizontalKeys != 0) || (pTe->verticalKeys != 0))
    {

        //create the key members, return null if not successful
        if(GFX_GOL_TextEntryCreateKeyMembers(pTe, pText) == NULL)
        {
            GFX_GOL_TextEntryDelKeyMembers(pTe);
            GFX_free(pTe);
            return (NULL);
        }
    }

    //Add this new widget object to the GOL list	
    GFX_GOL_Add((GFX_OBJ_HEADER *)pTe);
    return (pTe);
}   //end TeCreate()

/*********************************************************************
* Function: uint16_t TeDraw(void *pObj)
*
* Notes: This function draws the keys with their appropriate text
*
********************************************************************/
uint16_t GFX_GOL_TextEntryDraw(void *pObj)
{
    static GFX_COLOR    faceClr, embossLtClr, embossDkClr;
    static uint16_t     xText, yText;
    static XCHAR        XcharTmp;
    static KEYMEMBER    *pKeyTemp = NULL;

    static uint16_t     CountOfKeys = 0;
    static uint16_t     counter = 0;
    static XCHAR        hideChar[2] = {0x2A, 0x00};
    
    GFX_COLOR           color1, color2;

    typedef enum
    {
        TE_START,
        TE_HIDE_WIDGET,
        TE_DRAW_PANEL,
        TE_INIT_DRAW_EDITBOX,
        TE_DRAW_EDITBOX,
        TE_DRAW_KEY_INIT,
        TE_DRAW_KEY_SET_PANEL,
        TE_DRAW_KEY_DRAW_PANEL,
        TE_DRAW_KEY_TEXT,
        TE_DRAW_KEY_UPDATE,
        TE_UPDATE_STRING_INIT,
        TE_UPDATE_STRING,
        TE_WAIT_ERASE_EBOX_AREA,
        TE_UPDATE_CHARACTERS,
    } TE_DRAW_STATES;

    static TE_DRAW_STATES state = TE_START;
    GFX_OBJ_TEXTENTRY *pTe;

    pTe = (GFX_OBJ_TEXTENTRY *)pObj;

	while(1)
	{
		switch(state)
		{
			case TE_START:

				if(GFX_GOL_StateGet(pTe, TE_HIDE))
				{
					GFX_ColorSet(pTe->hdr.pGolScheme->CommonBkColor);
					state = TE_HIDE_WIDGET;
					// no break here so it falls through to the TE_HIDE_WIDGET state.
				}
				else
				{
					if(GFX_GOL_StateGet(pTe, TE_DRAW))
					{
                        if (TE_ROUNDEDBUTTON_RADIUS == 0)
                        {
                            color1 = pTe->hdr.pGolScheme->EmbossDkColor;
                            color2 = pTe->hdr.pGolScheme->EmbossLtColor;
                        }
                        else
                        {                    
                            color1 = pTe->hdr.pGolScheme->Color0;
                            color2 = pTe->hdr.pGolScheme->Color0;
                        }

						/************GFX_OBJ_STATE_DRAW THE WIDGET PANEL*****************************/
						GFX_GOL_PanelDraw
						(
                            
							pTe->hdr.left,
							pTe->hdr.top,
							pTe->hdr.right,
							pTe->hdr.bottom,
							0,
							pTe->hdr.pGolScheme->Color0,        //face color of panel
							color1, //emboss dark color
							color2, //emboss light color
							NULL,
							GFX_OBJ_EMBOSS_SIZE
						);
						state = TE_DRAW_PANEL;
						break;
					}

					// update the keys (if TE_UPDATE_TEXT is also set it will also be redrawn)
					// at the states after the keys are updated
					else if(GFX_GOL_StateGet(pTe, TE_UPDATE_KEY))
					{
						state = TE_DRAW_KEY_INIT;
						break;
					}

					// check if updating only the text displayed
					else if(GFX_GOL_StateGet(pTe, TE_UPDATE_TEXT))
					{
						state = TE_UPDATE_STRING_INIT;
						break;
					}
				}

			/*hide the widget*/
			case TE_HIDE_WIDGET:
			    // this state only gets entered if IsDeviceBusy() immediately after while(1) returns a 0.
				if (GFX_RectangleDraw(pTe->hdr.left, pTe->hdr.top, pTe->hdr.right, pTe->hdr.bottom) == NULL)
                    return (0);
                else 
                {
    				state = TE_START;
	    			return (1);
                }

			/*Draw the widget of the Text-Entry*/
			case TE_DRAW_PANEL:
				if(!GFX_GOL_PanelDrawTsk())
					return (0);
				state = TE_INIT_DRAW_EDITBOX;

			case TE_INIT_DRAW_EDITBOX:

				//Draw the editbox
				GFX_GOL_PanelDraw
				(
                    
					pTe->hdr.left,
					pTe->hdr.top,
					pTe->hdr.right,
					pTe->hdr.top + GFX_TextStringHeightGet(pTe->pDisplayFont) + GFX_OBJ_EMBOSS_SIZE,
					0,
					pTe->hdr.pGolScheme->Color1; ,
					pTe->hdr.pGolScheme->EmbossDkColor,
					pTe->hdr.pGolScheme->EmbossLtColor,
					NULL,
					GFX_OBJ_EMBOSS_SIZE
				);

				state = TE_DRAW_EDITBOX;

			case TE_DRAW_EDITBOX:
				if(!GFX_GOL_PanelDrawTsk())
					return (0);
				state = TE_DRAW_KEY_INIT;

			/* ********************************************************************* */
			/*                  Update the keys                                      */
			/* ********************************************************************* */
			case TE_DRAW_KEY_INIT:
				embossLtClr = pTe->hdr.pGolScheme->EmbossLtColor;
				embossDkClr = pTe->hdr.pGolScheme->EmbossDkColor;
				faceClr = pTe->hdr.pGolScheme->Color0;

				// if the active key update flag is set, only one needs to be redrawn
				if((GFX_GOL_StateGet(pTe, TE_DRAW) != TE_DRAW) && (pTe->pActiveKey->update == TRUE))
				{
					CountOfKeys = (pTe->horizontalKeys * pTe->verticalKeys) -
					1;
					pKeyTemp = pTe->pActiveKey;
				}
				else
				{
					CountOfKeys = 0;
					pKeyTemp = pTe->pHeadOfList;
				}

				state = TE_DRAW_KEY_SET_PANEL;

			case TE_DRAW_KEY_SET_PANEL:
				if(CountOfKeys < (pTe->horizontalKeys * pTe->verticalKeys))
				{

					// check if we need to draw the panel
					if(GFX_GOL_StateGet(pTe, TE_DRAW) != TE_DRAW)
					{
						if(pKeyTemp->update == TRUE)
						{

							// set the colors needed
							if(GFX_GOL_StateGet(pTe, TE_KEY_PRESSED))
							{
								embossLtClr = pTe->hdr.pGolScheme->EmbossDkColor;
								embossDkClr = pTe->hdr.pGolScheme->EmbossLtColor;
								faceClr = pTe->hdr.pGolScheme->Color1;
							}
							else
							{
								embossLtClr = pTe->hdr.pGolScheme->EmbossLtColor;
								embossDkClr = pTe->hdr.pGolScheme->EmbossDkColor;
								faceClr = pTe->hdr.pGolScheme->Color0;
							}
						}
						else
						{
							state = TE_DRAW_KEY_UPDATE;
							break;
						}
					}

					if(GFX_GOL_StateGet(pTe, TE_DISABLED) == TE_DISABLED)
					{
						faceClr = GFX_ColorSet(pTe->hdr.pGolScheme->ColorDisabled);
					}

					// set up the panel
					GFX_GOL_PanelDraw
					(
                        
						pKeyTemp->left+TE_ROUNDEDBUTTON_RADIUS,
						pKeyTemp->top+TE_ROUNDEDBUTTON_RADIUS,
						pKeyTemp->right-TE_ROUNDEDBUTTON_RADIUS,
						pKeyTemp->bottom-TE_ROUNDEDBUTTON_RADIUS,
						TE_ROUNDEDBUTTON_RADIUS,
						faceClr,
						embossLtClr,
						embossDkClr,
						NULL,
						GFX_OBJ_EMBOSS_SIZE
					);

					state = TE_DRAW_KEY_DRAW_PANEL;
				}
				else
				{
					state = TE_UPDATE_STRING_INIT;
					break;
				}

			case TE_DRAW_KEY_DRAW_PANEL:
				if(!GFX_GOL_PanelDrawTsk())
					return (0);

				// reset the update flag since the key panel is already redrawn   	
				pKeyTemp->update = FALSE;

				//set the text coordinates of the drawn key
				xText = ((pKeyTemp->left) + (pKeyTemp->right) - (pKeyTemp->textWidth)) >> 1;
				yText = ((pKeyTemp->bottom) + (pKeyTemp->top) - (pKeyTemp->textHeight)) >> 1;

				//set color of text
				// if the object is disabled, draw the disabled colors
				if(GFX_GOL_StateGet(pTe, TE_DISABLED) == TE_DISABLED)
				{
					GFX_ColorSet(pTe->hdr.pGolScheme->TextColorDisabled);
				}
				else
				{
					if((GFX_GOL_StateGet(pTe, TE_DRAW) != TE_DRAW) && (GFX_GOL_StateGet(pTe, TE_KEY_PRESSED)) == TE_KEY_PRESSED)
					{
						GFX_ColorSet(pTe->hdr.pGolScheme->TextColor1);
					}
					else
					{
						GFX_ColorSet(pTe->hdr.pGolScheme->TextColor0);
					}
				}

				//output the text
				GFX_LinePositionSet(xText, yText);

				// set the font to be used
				GFX_FontSet(&GFX_Primitive_instance[pTe->hdr.instance].currentFont,pTe->hdr.pGolScheme->pFont);

				state = TE_DRAW_KEY_TEXT;

			case TE_DRAW_KEY_TEXT:
				if(!GFX_TextStringDraw(pKeyTemp->pKeyName))
					return (0);
				state = TE_DRAW_KEY_UPDATE;

			case TE_DRAW_KEY_UPDATE:

				// update loop variables
				CountOfKeys++;
				pKeyTemp = pKeyTemp->pNextKey;

				state = TE_DRAW_KEY_SET_PANEL;
				break;

			/* ********************************************************************* */
			/*                  Update the displayed string                          */
			/* ********************************************************************* */
			case TE_UPDATE_STRING_INIT:

				// check if there are characters to remove
				if(pTe->pActiveKey != NULL)
				{
					if(pTe->pActiveKey->command == TE_DELETE_COM)
					{
						if(pTe->CurrentLength == 0)
						{
							state = TE_START;
							return (1);
						}
					}
				}
				else
				{

					// check if text indeed needs to be updated
					if((pTe->CurrentLength == pTe->outputLenMax) && (GFX_GOL_StateGet(pTe, TE_UPDATE_TEXT)))
					{
						state = TE_START;
						return (1);
					}
				}

				//set the clipping region
	/*			SetClipRgn
				(   
                                        
					pTe->hdr.left + GFX_OBJ_EMBOSS_SIZE,
					pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE,
					pTe->hdr.right - GFX_OBJ_EMBOSS_SIZE,
					pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE + GFX_TextStringHeightGet(pTe->pDisplayFont)
				);
       */
				GFX_ClipSet(1);     //set the clipping
				if(GFX_GOL_StateGet(pTe, TE_DRAW))
				{

					// update only the displayed text
					// position the string rendering on the right position
					if(GFX_GOL_StateGet(pTe, TE_ECHO_HIDE))
					{

						// fill the area with '*' character so we use the width of this character
						GFX_LinePositionSet
						(   
							pTe->hdr.right - 4 - GFX_OBJ_EMBOSS_SIZE - (GFX_TextStringWidthGet(hideChar, pTe->pDisplayFont) * pTe->CurrentLength),
							pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE
						);
					}
					else
					{
						GFX_LinePositionSet
						(   
							pTe->hdr.right - 4 - GFX_OBJ_EMBOSS_SIZE - GFX_TextStringWidthGet(pTe->pTeOutput, pTe->pDisplayFont),
							pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE
						);
					}
				}
				else if(GFX_GOL_StateGet(pTe, TE_UPDATE_TEXT))
				{

					// erase the current text by drawing a bar over the edit box area
					GFX_ColorSet(pTe->hdr.pGolScheme->Color1);

					// we have to make sure we finish the GFX_RectangleDraw() first before we continue.
					state = TE_WAIT_ERASE_EBOX_AREA;
					break;
				}
				else
				{
					GFX_ClipSet(0); //reset the clipping
					state = TE_START;
					return (1);
				}

				counter = 0;
				state = TE_UPDATE_STRING;
				break;

			case TE_WAIT_ERASE_EBOX_AREA:
                if (GFX_RectangleFillDraw
					(
                        
						pTe->hdr.left + GFX_OBJ_EMBOSS_SIZE,
						pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE,
						pTe->hdr.right - GFX_OBJ_EMBOSS_SIZE,
						pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE + GFX_TextStringHeightGet(pTe->pDisplayFont)
					) == NULL)
                    return 0;

				// check if the command given is delete a character
				if(pTe->pActiveKey->command == TE_DELETE_COM)
				{
					*(pTe->pTeOutput + (--pTe->CurrentLength)) = 0;
				}

				// position the cursor to the start of string rendering
				// notice that we need to remove the characters first before we position the cursor when
				// deleting characters
				if(GFX_GOL_StateGet(pTe, TE_ECHO_HIDE))
				{

					// fill the area with '*' character so we use the width of this character
					GFX_LinePositionSet
					(   
						pTe->hdr.right - 4 - GFX_OBJ_EMBOSS_SIZE - (GFX_TextStringWidthGet(hideChar, pTe->pDisplayFont) * (pTe->CurrentLength)),
						pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE
					);
				}
				else
				{
					GFX_LinePositionSet
					(   
						pTe->hdr.right - 4 - GFX_OBJ_EMBOSS_SIZE - GFX_TextStringWidthGet(pTe->pTeOutput, pTe->pDisplayFont),
						pTe->hdr.top + GFX_OBJ_EMBOSS_SIZE
					);
				}

				counter = 0;
				state = TE_UPDATE_STRING;
                // add a break here to force a check of IsDeviceBusy() so when last GFX_RectangleDraw() function is still
                // ongoing it will wait for it to finish.
                break;

			case TE_UPDATE_STRING:

				//output the text
				GFX_ColorSet(pTe->hdr.pGolScheme->TextColor1);
				GFX_FontSet(&GFX_Primitive_instance[pTe->hdr.instance].currentFont,pTe->pDisplayFont);

				// this is manually doing the GFX_TextStringDraw() function but with the capability to replace the
				// characters to the * character when hide echo is enabled.							
				XcharTmp = *((pTe->pTeOutput) + counter);
				if(XcharTmp < (XCHAR)15)
				{

					// update is done time to return to start and exit with success
					GFX_ClipSet(0); //reset the clipping
					state = TE_START;
					return (1);
				}
				else
				{
					if(GFX_GOL_StateGet(pTe, TE_ECHO_HIDE))
						GFX_TextCharDraw(0x2A);
					else
						GFX_TextCharDraw(XcharTmp);
					state = TE_UPDATE_CHARACTERS;
				}

			case TE_UPDATE_CHARACTERS:
				counter++;
				state = TE_UPDATE_STRING;
				break;
		} //end switch
	} // end of while(1)
} //end TeDraw()

/*********************************************************************
* Function: GFX_GOL_TextEntryActionGet(void *pObj, GFX_OBJ_MESSAGE *pMsg)
*
* Notes: Function to check which key was pressed/released
*
********************************************************************/
uint16_t GFX_GOL_TextEntryActionGet(void *pObj, GFX_OBJ_MESSAGE *pMsg)
{
    uint16_t       NumberOfKeys, param1, param2;
    KEYMEMBER   *pKeyTemp = NULL;
    GFX_OBJ_TEXTENTRY *pTe;

    pTe = (GFX_OBJ_TEXTENTRY *)pObj;

    // Check if disabled first
    if(GFX_GOL_StateGet(pTe, TE_DISABLED))
        return (OBJ_MSG_INVALID);

        #ifdef USE_TOUCHSCREEN

    //find the total number of keys
    NumberOfKeys = (pTe->horizontalKeys) * (pTe->verticalKeys);
    param1 = pMsg->param1;
    param2 = pMsg->param2;

    if((pMsg->type == TYPE_TOUCHSCREEN))
    {

        // Check if it falls in the panel of the GFX_OBJ_TEXTENTRY
        if
        (
            (pTe->hdr.left < pMsg->param1) &&
            (pTe->hdr.right > pMsg->param1) &&
            (pTe->hdr.top + (GFX_TextStringHeightGet(pTe->pDisplayFont) + (GFX_OBJ_EMBOSS_SIZE << 1)) < pMsg->param2) &&
            (pTe->hdr.bottom > pMsg->param2)
        )
        {

            /* If it fell inside the TextEntry panel, go through the link list and check which one was pressed
			   At this point the touch screen event is either EVENT_MOVE or EVENT_PRESS.   
			*/

            //point to the head of the link list
            pKeyTemp = pTe->pHeadOfList;

            while(pKeyTemp != NULL)
            {
                if
                (
                    (pKeyTemp->left < param1) &&
                    (pKeyTemp->right > param1) &&
                    (pKeyTemp->top < param2) &&
                    (pKeyTemp->bottom > param2)
                )
                {
                    if(pMsg->uiEvent == EVENT_RELEASE)
                    {
                        pTe->pActiveKey = pKeyTemp;
                        pKeyTemp->update = TRUE;

                        if(pTe->pActiveKey->state == TE_KEY_PRESSED)
                        {
                            if(pKeyTemp->command == 0)
                                return (TE_MSG_ADD_CHAR);

                            //command for a TE_DELETE_COM key
                            if(pKeyTemp->command == TE_DELETE_COM)
                                return (TE_MSG_DELETE);

                            //command for a TE_SPACE_COM key 0x20	
                            if(pKeyTemp->command == TE_SPACE_COM)
                                return (TE_MSG_SPACE);

                            //command for a TE_ENTER_COM key        	
                            if(pKeyTemp->command == TE_ENTER_COM)
                                return (TE_MSG_ENTER);
                        }

                        // this is a catch all backup
                        return (TE_MSG_RELEASED);
                    }
                    else
                    {

                        // to shift the press to another key make sure that there are no other
                        // keys currently pressed. If there is one it must be released first.
                        // check if there are previously pressed keys
                        if(GFX_GOL_StateGet(pTe, TE_KEY_PRESSED))
                        {

                            // there is a key being pressed.
                            if(pKeyTemp->index != pTe->pActiveKey->index)
                            {

                                // release the currently pressed key first
                                pTe->pActiveKey->update = TRUE;
                                return (TE_MSG_RELEASED);
                            }
                        }
                        else
                        {

                            // check if the active key is not pressed
                            // if not, set to press since the current touch event
                            // is either move or press
                            // check if there is an active key already set
                            // if none, set the current key as active and return a pressed mesage
                            if(pTe->pActiveKey == NULL)
                            {
                                pTe->pActiveKey = pKeyTemp;
                                pKeyTemp->update = TRUE;
                                return (TE_MSG_PRESSED);
                            }

                            if(pTe->pActiveKey->state != TE_KEY_PRESSED)
                            {
                                pTe->pActiveKey = pKeyTemp;
                                pKeyTemp->update = TRUE;
                                return (TE_MSG_PRESSED);
                            }
                            else
                            {
                                return (OBJ_MSG_INVALID);
                            }
                        }
                    }
                }
                else
                {

                    // if the key is in the pressed state and current touch is not here
                    // then it has to be redrawn
                    if(pKeyTemp->state == TE_KEY_PRESSED)
                    {
                        pTe->pActiveKey = pKeyTemp;
                        pKeyTemp->update = TRUE;
                        return (TE_MSG_RELEASED);
                    }
                }

                //access the next link list
                pKeyTemp = pKeyTemp->pNextKey;
            }   //end while
        }
        else
        {
            if((pMsg->uiEvent == EVENT_MOVE) && (GFX_GOL_StateGet(pTe, TE_KEY_PRESSED)))
            {
                pTe->pActiveKey->update = TRUE;
                return (TE_MSG_RELEASED);
            }
        }
    }

    return (OBJ_MSG_INVALID);
        #endif // USE_TOUCHSCREEN		
}               //end GFX_GOL_TextEntryActionGet()

/*********************************************************************
* Function: GFX_GOL_TextEntryActionSet(uint16_t translatedMsg, void *pObj, GFX_OBJ_MESSAGE* pMsg)
*
*
* Notes: This the default operation to change the state of the key.
*		 Called inside GFX_OBJ_Message() when GFX_OBJ_MessageCallback() returns a 1.
*
********************************************************************/
void GFX_GOL_TextEntryActionSet(uint16_t translatedMsg, void *pObj, GFX_OBJ_MESSAGE *pMsg)
{
    GFX_OBJ_TEXTENTRY *pTe;

    pTe = (GFX_OBJ_TEXTENTRY *)pObj;

    switch(translatedMsg)
    {
        case TE_MSG_DELETE:
            GFX_GOL_StateSet(pTe, TE_UPDATE_KEY | TE_UPDATE_TEXT);
            break;

        case TE_MSG_SPACE:
            GFX_GOL_TextEntrySpaceChar(pTe);
            GFX_GOL_StateSet(pTe, TE_UPDATE_KEY | TE_UPDATE_TEXT);
            break;

        case TE_MSG_ENTER:
            GFX_GOL_StateSet(pTe, TE_UPDATE_KEY);
            break;

        case TE_MSG_ADD_CHAR:
            GFX_GOL_TextEntryAddChar(pTe);
            GFX_GOL_StateSet(pTe, TE_UPDATE_KEY | TE_UPDATE_TEXT);
            break;

        case TE_MSG_PRESSED:
            (pTe->pActiveKey)->state = TE_KEY_PRESSED;
            GFX_GOL_StateSet(pTe, TE_KEY_PRESSED | TE_UPDATE_KEY);
            return;

        case TE_MSG_RELEASED:
            (pTe->pActiveKey)->state = 0;
            GFX_GOL_StateSet(pTe, TE_KEY_PRESSED);  // reset pressed
            GFX_GOL_StateSet(pTe, TE_UPDATE_KEY);   // redraw
            return;
    }

    if(pTe->pActiveKey != NULL)
        (pTe->pActiveKey)->state = 0;
    GFX_GOL_StateSet(pTe, TE_KEY_PRESSED);
}

/*********************************************************************
* Function: void TeClearBuffer(GFX_OBJ_TEXTENTRY *pTe)
*
* Notes: This function will clear the edibox and the buffer.
*		 You must set the drawing state bit TE_UPDATE_TEXT 
*		 to update the TEXTENTRY on the screen.
*
********************************************************************/
void GFX_GOL_TextEntryClearBuffer(GFX_OBJ_TEXTENTRY *pTe)
{
    uint16_t    i;

    //clear the buffer
    for(i = 0; i < (pTe->outputLenMax); i++)
    {
        *(pTe->pTeOutput + i) = 0;
    }

    pTe->CurrentLength = 0;
}

/*********************************************************************
* Function: void TeSetBuffer(GFX_OBJ_TEXTENTRY *pTe, XCHAR *pText, uint16_t size)
*
* Notes: This function will replace the currently used buffer.
*		 MaxSize defines the length of the buffer. Buffer must be
*		 a NULL terminated string.
*
********************************************************************/
void GFX_GOL_TextEntrySetBuffer(GFX_OBJ_TEXTENTRY *pTe, XCHAR *pText, uint16_t MaxSize)
{
    uint16_t    count = 0;
    XCHAR   *pTemp;

    pTemp = pText;

    while(*pTemp != 0)
    {
        if(count >= MaxSize)
            break;
        pTemp++;
        count++;
    }

    // terminate the string
    *pTemp = 0;

    pTe->CurrentLength = count;
    pTe->outputLenMax = MaxSize-1;
    pTe->pTeOutput = pText;
}

/*********************************************************************
* Function: BOOL TeIsKeyPressed(GFX_OBJ_TEXTENTRY *pTe,uint16_t index)
*
* Notes: This function will check if the key was pressed. If no 
*		 key was pressed it will return FALSE.
*
********************************************************************/
BOOL GFX_GOL_TextEntryIsKeyPressed(GFX_OBJ_TEXTENTRY *pTe, uint16_t index)
{
    KEYMEMBER   *pTemp;

    pTemp = pTe->pHeadOfList;

    //search the key using the given index
    while(index != pTemp->index)
    {

        // catch all check
        if(pTemp == NULL)
            return (FALSE);
        pTemp = pTemp->pNextKey;
    }

    if(pTemp->state == TE_KEY_PRESSED)
    {
        return (TRUE);
    }
    else
    {
        return (FALSE);
    }
}

/*********************************************************************
* Function: BOOL TeSetKeyCommand(GFX_OBJ_TEXTENTRY *pTe,uint16_t index,uint16_t command)
*
* Notes: This function will assign a command to a particular key. 
*		 Returns TRUE if sucessful and FALSE if not.
*
********************************************************************/
BOOL GFX_GOL_TextEntrySetKeyCommand(GFX_OBJ_TEXTENTRY *pTe, uint16_t index, uint16_t command)
{
    KEYMEMBER   *pTemp;

    pTemp = pTe->pHeadOfList;

    //search the key using the given index
    while(index != pTemp->index)
    {

        // catch all check
        if(pTemp == NULL)
            return (FALSE);
        pTemp = pTemp->pNextKey;
    }

    pTemp->command = command;
    return (TRUE);
}

/*********************************************************************
* Function: TeSetKeyCommand(pTe, index)
*				
* Notes: This function will return the currently used command by a key 
*		 with the given index.
*
********************************************************************/
uint16_t GFX_GOL_TextEntryGetKeyCommand(GFX_OBJ_TEXTENTRY *pTe, uint16_t index)
{
    KEYMEMBER   *pTemp;

    pTemp = pTe->pHeadOfList;

    //search the key using the given index
    while(index != pTemp->index)
    {

        // catch all check
        if(pTemp == NULL)
            return (0);
        pTemp = pTemp->pNextKey;
    }

    return (pTemp->command);
}

/*********************************************************************
* Function: BOOL TeSetKeyText(GFX_OBJ_TEXTENTRY *pTe,uint16_t index, XCHAR *pText)
*
* Notes: This function will set the string associated with the key 
*		 with the new string pText. The key to be modified is determined 
*        by the index. Returns TRUE if sucessful and FALSE if not.
*
********************************************************************/
BOOL GFX_GOL_TextEntrySetKeyText(GFX_OBJ_TEXTENTRY *pTe, uint16_t index, XCHAR *pText)
{
    KEYMEMBER   *pTemp;

    pTemp = pTe->pHeadOfList;

    //search the key using the given index
    while(index != pTemp->index)
    {
        // catch all check
        if(pTemp == NULL)
            return (FALSE);
        pTemp = pTemp->pNextKey;
    }

	// Set the the text 
    pTemp->pKeyName = pText;

    return (TRUE);
}


/*********************************************************************
* Function: KEYMEMBER *TeCreateKeyMembers(GFX_OBJ_TEXTENTRY *pTe,XCHAR *pText[])
*
* Notes: This function will create the members of the list
*
********************************************************************/
KEYMEMBER *GFX_GOL_TextEntryCreateKeyMembers(GFX_OBJ_TEXTENTRY *pTe, XCHAR *pText[])
{
    uint16_t       NumberOfKeys, width, height;
    uint16_t       keyTop, keyLeft;
    uint16_t        rowcount, colcount;
    uint16_t        index = 0;

    KEYMEMBER   *pKl = NULL;    //link list
    KEYMEMBER   *pTail = NULL;

    // determine starting positions of the keys
    keyTop = pTe->hdr.top + GFX_TextStringHeightGet(pTe->pDisplayFont) + (GFX_OBJ_EMBOSS_SIZE << 1);
    keyLeft = pTe->hdr.left;    

    //calculate the total number of keys, and width and height of each key
    NumberOfKeys = pTe->horizontalKeys * pTe->verticalKeys;
    width = (pTe->hdr.right - keyLeft + 1) / pTe->horizontalKeys;
    height = (pTe->hdr.bottom - keyTop + 1) / pTe->verticalKeys;

    /*create the list and calculate the coordinates of each bottom, and the textwidth/textheight of each font*/

    //Add a list for each key
    for(colcount = 0; colcount < pTe->verticalKeys; colcount++)
    {
        for(rowcount = 0; rowcount < pTe->horizontalKeys; rowcount++)
        {

            //get storage for new entry
            pKl = (KEYMEMBER *)GFX_malloc(sizeof(KEYMEMBER));
            if(pKl == NULL)
			{
				GFX_GOL_TextEntryDelKeyMembers(pTe);
                return (NULL);
			}	
            if(pTe->pHeadOfList == NULL)
                pTe->pHeadOfList = pKl;
            if(pTail == NULL)
            {
                pTail = pKl;
            }
            else
            {
                pTail->pNextKey = pKl;
                pTail = pTail->pNextKey;
            }

            //set the index for the new list
            pKl->index = index;

            // set update flag to off
            pKl->update = FALSE;

            //calculate the x-y coordinate for each key
            pKl->left 	= keyLeft + (rowcount * width);
            pKl->top 	= keyTop  + (colcount * height);
            pKl->right 	= keyLeft + ((rowcount + 1) * width);
            pKl->bottom = keyTop  + ((colcount + 1) * height);

            //Add the text to the list and increase the index
            pKl->pKeyName = pText[index++];

            //set the COMMAND to NULL for all keys
            pKl->command = 0;

            //calculate the textwidth, textheight
            pKl->textWidth = 0;
            pKl->textHeight = 0;
            if(pKl->pKeyName != NULL)
            {

                // Calculate the text width & height
                pKl->textWidth = GFX_TextStringWidthGet(pKl->pKeyName, pTe->hdr.pGolScheme->pFont);
                pKl->textHeight = GFX_TextStringHeightGet(pTe->hdr.pGolScheme->pFont);
            } //end if
        } //end for	
    } //end for	

    pTail->pNextKey = NULL;

    return (pKl);
}

/*********************************************************************
* Function: void GFX_GOL_TextEntryDelKeyMembers(void *pObj)
*
* Notes: This function will delete the members of the list
********************************************************************/
void GFX_GOL_TextEntryDelKeyMembers(void *pObj)
{
    KEYMEMBER   *pCurItem;
    KEYMEMBER   *pItem;
    GFX_OBJ_TEXTENTRY *pTe;

    pTe = (GFX_OBJ_TEXTENTRY *)pObj;

    pCurItem = pTe->pHeadOfList;

    while(pCurItem != NULL)
    {
        pItem = pCurItem;
        pCurItem = pCurItem->pNextKey;
        GFX_free(pItem);
    }

    pTe->pHeadOfList = NULL;
}

/*********************************************************************
* Function: void TeSpaceChar(GFX_OBJ_TEXTENTRY *pTe)
*
* Notes: This function will add a space to the buffer/editbox
********************************************************************/
void GFX_GOL_TextEntrySpaceChar(GFX_OBJ_TEXTENTRY *pTe)
{

    //first determine if the array has not overflown
    if((pTe->CurrentLength) < pTe->outputLenMax)
    {
        *(pTe->pTeOutput + (pTe->CurrentLength)) = 0x20;
        *(pTe->pTeOutput + (pTe->CurrentLength) + 1) = 0;
    }   //end if	
    (pTe->CurrentLength)++;
}

/*********************************************************************
* Function: void GFX_GOL_TextEntryAddChar(GFX_OBJ_TEXTENTRY *pTe)
*
* Notes: This function will add a character to the buffer/editbox
********************************************************************/
void GFX_GOL_TextEntryAddChar(GFX_OBJ_TEXTENTRY *pTe)
{
    XCHAR   *pPoint;

    //first determine if the array has not overflown
    if((pTe->CurrentLength) < pTe->outputLenMax)
    {
        pPoint = (pTe->pActiveKey)->pKeyName;
        while(*(pPoint) != 0)
        {
            *(pTe->pTeOutput + (pTe->CurrentLength)) = *(pPoint)++;
        }
    }   //end if
    else
    {

        // it is full ignore the added key
        return;
    }

    (pTe->CurrentLength)++;
    // add the string terminator 
    *(pTe->pTeOutput + pTe->CurrentLength) = 0;
}

#endif // USE_TEXTENTRY
