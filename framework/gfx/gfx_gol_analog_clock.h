/************************************************************************
  Company:
    Microchip Technology Inc.
    
    \File Name:
    
    gfx_gol_analog_clock.h
  Summary:
    This implements the analog clock object of the GOL.
  Description:
    Graphics Library Implementation
    
    Refer to Microchip Graphics Library for complete documentation of the
    AnalogClock Object.                                                  
  ************************************************************************/

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
#ifndef _ANALOGCLOCK_H
    #define _ANALOGCLOCK_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <gfx/gfx_gol.h>

/*********************************************************************
* Object States Definition: 
*********************************************************************/
    #define GFX_GOL_ANALOGCLOCK_DISABLED    0x0002   // Bit for disabled state.
    #define GFX_GOL_ANALOGCLOCK_PRESSED     0x0004   // Bit for press state.
    #define GFX_GOL_ANALOGCLOCK_TICK	   0x1000   // Bit to tick second hand
    #define GFX_GOL_ANALOGCLOCK_UPDATE_HOUR    0x2000   // Bit to indicate hour hand must be redrawn
    #define GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE  0x0100   // Bit to indicate minute hand must be redrawn
    #define GFX_GOL_ANALOGCLOCK_UPDATE_SECOND  0x0200   // Bit to indicate minute hand must be redrawn
    #define GFX_GOL_ANALOGCLOCK_DRAW        0x4000   // Bit to indicate button must be redrawn.
    #define GFX_GOL_ANALOGCLOCK_HIDE        0x8000   // Bit to indicate button must be removed from screen.

/**********************************************************************
  Description:
    Defines the parameters required for a clock Object. The following
    relationships of the parameters determines the general shape of the
    clock:
      1. centerx and centery determine the middle of the clock.
      2. radius defines the radius of the clock.
      3. *pBitmap points to the background image for the analog clock.
                                                                       
  **********************************************************************/           
  **********************************************************************/
typedef struct
{
    GFX_GOL_OBJ_HEADER        hdr;              // Generic header for all Objects (see GFX_OBJ_HEADER).
    short                 radius;           // Radius of the clock.
    short		  centerx;          // center location in X-axis.
    short		  centery;          // center location in Y-axis.
    short		  valueS;           // time in Second
    short		  prev_valueS;      // previous time in Second
    short		  valueM;           // time in Minute
    short		  prev_valueM;      // previous time in Minute
    short		  valueH;           // time in Hour
    short		  prev_valueH;      // previous time in Hour
    void                  *pBitmap;         // Pointer to bitmap used.
} GFX_GOL_ANALOGCLOCK;


// *****************************************************************************
/* Function:
    GFX_GOL_ANALOGCLOCK *GFX_AnalogClock_Create(uint16_t ID, short left, short top, short right,
                          short bottom, short radius, void *pBitmap, XCHAR *pText,
                          GFX_GOL_SCHEME *pScheme)

  Summary:
    Creates a analog clock object.

  Description:
    This function creates a analog clock at the given position using state,
    radius, pBitmap, pText, and pScheme.

  Precondition:
    None.

  Parameters:
    ID - Unique user defined ID for the object instance.
        left - Left most position of the object.
        top - Top most position of the object.
        right - Right most position of the object.
        bottom - Bottom most position of the object.
        hour - Initial hour value.
        minute - Initial minute value.
        radius - Sets the radius of the clock.
        sechand - Flag to indicate if the second hand will be drawn or not.
        state - Sets the initial state of the object.
        pBitmap - Pointer to the bitmap used on the face of the analog clock
                  dimension of the image must match the dimension of the
				   widget.
        pScheme - Pointer to the style scheme used

  Returns:
    Returns a pointer to the digital meter.

  Example:
    <code>
	GFX_GOL_SCHEME *pScheme;
	uint16_t state;

		pScheme = GFX_GOL_SCHEMeCreate();
		state = AC_DRAW;

		AnalogClock = GFX_AnalogClock_Create(ANALOGCLOCK_ID, 20, 64, 50, 118,
                    1, 20, 30, FALSE, state, NULL, pScheme);

     <code>

  Remarks:
*/
GFX_GOL_ANALOGCLOCK *GFX_AnalogClockCreate
(
    uint16_t        ID,
    short       left,
    short       top,
    short       right,
    short       bottom,
    short       hour,
    short       minute,
    short       radius,
    bool	    sechand,
    uint16_t        state,
    void        *pBitmap,
    GFX_GOL_OBJ_SCHEME  *pScheme
);

/*********************************************************************
* Function: uint16_t GFX_GOL_AnalogClockDraw(GFX_GOL_ANALOGCLOCK *pAc)
*
* Overview: This function renders the object on the screen using 
* 			the current parameter settings. Location of the object is 
*			determined by the left, top, right and bottom parameters. 
*			The colors used are dependent on the state of the object. 
*			The font used is determined by the style scheme set.
*			
*
* PreCondition: Object must be created before this function is called.
*
* Input: pAc - Pointer to the object to be rendered.
*        
* Output: Returns the status of the drawing
*		  - 1 - If the rendering was completed and 
*		  - 0 - If the rendering is not yet finished. 
*		  Next call to the function will resume the 
*		  rendering on the pending drawing state.
*
* Example:
*   <CODE> 
*	void MyGOLDraw(){
*		static GFX_OBJ_HEADER *pCurrentObj = NULL;
*		int done;
*		
*		// There are no objects
*		if(GFX_OBJ_ListGet() == NULL)
*			return;
*
* 		// If it's last object jump to head
*		if(pCurrentObj == NULL)
*			pCurrentObj = GFX_OBJ_ListGet();
*
*		done = 0;
*
*		// this only process Button and Window
*		while(pCurrentObj != NULL){
*			// check if object state indicates redrawing
*			if(pCurrentObj->state&0xFC00) {
*				switch(pCurrentObj->type){
*					case OBJ_ANALOGCLOCK:
*						done = AcDraw((ANALOGCLOCK*)pCurrentObj);
*						break;
*					case OBJ_WINDOW:
*						done = WndDraw((WINDOW*)pCurrentObj);
*						break;
*					default: 
*						done = 1;
*						break;
*				}
*				if(done){
*					// reset only the state if drawing was finished
*					pCurrentObj->state = 0;
*				}else{
*					// done processing the list
*					return;
*				}
*			}
*			// go to next object
*			pCurrentObj = pCurrentObj->pNxtObj;
*		}
*	}
*	</CODE> 
*
* Side Effects: none
*
********************************************************************/
GFX_STATUS    GFX_GOL_AnalogClockDraw(void *pAc);

/*********************************************************************
* Function: GFX_GOL_AnalogClockHandsDraw(GFX_GOL_ANALOGCLOCK *pAc, short hand, short thickness, uint16_t color, void *pBitmap);
*
* Overview: Draws the current position of the clock hands with the given thickness and color.
*
* PreCondition: none
*
* Input: pAc - The pointer to the object whose hands will be modified.
*        hand - which hand to be drawn (second, minute, hour)
*        thickness - thickness to draw the hand
*        color - color to draw the hand
*        *pBitmap - bitmap background to be redrawn
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
GFX_STATUS GFX_GOL_AnalogClockHandsDraw(GFX_GOL_ANALOGCLOCK *pAc, short hand, short thickness, GFX_COLOR color);


/*********************************************************************
* Function: GFX_GOL_AnalogClock_SetHour(GFX_GOL_ANALOGCLOCK *pAc, short hour)
*
* Overview: Sets the hour value of the analog clock.
*
* PreCondition: none
*
* Input: pAc - The pointer to the object whose hands will be modified.
*        hour - New hour time. 
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void GFX_GOL_AnalogClockHourSet(GFX_GOL_ANALOGCLOCK *pAc, short hour);

/*********************************************************************
* Function: GFX_GOL_AnalogClock_SetMinute(GFX_GOL_ANALOGCLOCK *pAc, short minute)
*
* Overview: Sets the minute value of the analog clock.
*
* PreCondition: none
*
* Input: pAc - The pointer to the object whose hands will be modified.
*        minute - New minute time. 
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void GFX_GOL_AnalogClockMinuteSet(GFX_GOL_ANALOGCLOCK *pAc, short minute);

/*********************************************************************
* Function: GFX_GOL_AnalogClock_SetSecond(GFX_GOL_ANALOGCLOCK *pAc, short second)
*
* Overview: Sets the second value of the analog clock.
*
* PreCondition: none
*
* Input: pAc -    The pointer to the object whose hands will be modified.
*        second - New second time. 
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void GFX_GOL_AnalogClockSecondSet(GFX_GOL_ANALOGCLOCK *pAc, short second);

#endif // _ANALOGCLOCK_H
