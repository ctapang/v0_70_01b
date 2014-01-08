/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  GOL Layer 
 *  Analog Clock
 *****************************************************************************
 * File Name:       AnalogClock.c
 * Dependencies:    AnalogClock.h
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
 *****************************************************************************/
#include "gfx/gfx.h"

#define THICKNESS_SECOND 4

#define SECOND 1
#define MINUTE 2
#define HOUR 3

/*********************************************************************
* Function: GFX_OBJ_ANALOGCLOCK  *GFX_AnalogClock_Create(uint16_t ID, short left,short top,
*                        short right,short bottom,short hour,short minute,
*                        short radius,BOOL sechand,uint16_t state,void *pBitmap,
*                        GFX_OBJ_SCHEME  *pScheme)
*
*
* Notes: Creates an ANALOGCLOCK object and adds it to the current active list.
*        If the creation is successful, the pointer to the created Object 
*        is returned. If not successful, NULL is returned.
*
********************************************************************/
GFX_GOL_ANALOGCLOCK *GFX_AnalogClockCreate
(
    uint16_t    ID,
    short       left,
    short       top,
    short       right,
    short       bottom,
    short       hour,
    short       minute,
    short       radius,
    bool        sechand,
    uint16_t    state,
    void        *pBitmap,
    GFX_GOL_OBJ_SCHEME  *pScheme
)
{
    GFX_GOL_ANALOGCLOCK  *pAc = NULL;
    pAc = (GFX_GOL_ANALOGCLOCK *)GFX_malloc(sizeof(GFX_GOL_ANALOGCLOCK));
    if(pAc == NULL)
        return (NULL);

    //pAc->hdr.instance = instance;
    pAc->hdr.ID = ID;                   // unique id assigned for referencing
    pAc->hdr.pNxtObj = NULL;            // initialize pointer to NULL
    pAc->hdr.type = GFX_GOL_ANALOGCLOCK_TYPE;    // set object type
    pAc->hdr.left = left;               // left position
    pAc->hdr.top = top;                 // top position
    pAc->hdr.right = right;              // left position
    pAc->hdr.bottom = bottom;              // top position
    pAc->radius = radius;
    pAc->valueS = 0;
    pAc->prev_valueS = pAc->valueS;
    pAc->valueM = minute;
    pAc->prev_valueM = pAc->valueM-1;
    pAc->valueH = (hour*5) + (minute/12);
    pAc->prev_valueH = pAc->valueH-1;
    pAc->centerx = (left + ((right-left)>>1)); 
    pAc->centery = (top + ((bottom-top)>>1));
    pAc->pBitmap = pBitmap;             // location of bitmap
    pAc->hdr.state = state;             // state
    pAc->hdr.DrawObj = GFX_GOL_AnalogClockDraw;			// draw function
    pAc->hdr.actionSet = NULL;             // no message function
    pAc->hdr.actionGet = NULL;		// no default message function
    pAc->hdr.FreeObj = NULL;
 
    // Set the color scheme to be used
    if(pScheme == NULL)
        pAc->hdr.pGolScheme = _pDefaultGolScheme;
    else
        pAc->hdr.pGolScheme = (GFX_GOL_OBJ_SCHEME *)pScheme;

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *)pAc);

    return (pAc);
}

/*********************************************************************
* Function: uint16_t AnalogClockDraw(GFX_OBJ_ANALOGCLOCK *pAc)
*
*
* Notes: This is the state machine to draw the clock.
*
********************************************************************/
GFX_STATUS GFX_GOL_AnalogClockDraw(void *pObj)
{
    typedef enum
    {
        REMOVE,
        BEVEL_DRAW,
        BEVEL_DRAW1,
        TICK,
    } AC_DRAW_STATES;

    static AC_DRAW_STATES state = BEVEL_DRAW;
    static short width, height, radius;
    static GFX_COLOR faceClr, handClr;

    GFX_GOL_ANALOGCLOCK *pAc;
    
    pAc = (GFX_GOL_ANALOGCLOCK *)pObj;
 	
    switch(state)
    {

        case REMOVE:

            if(GFX_GOL_ObjectStateGet(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_HOUR))
            {
                   if(GFX_GOL_AnalogClockHandsDraw(pAc, HOUR, THICKNESS_SECOND+4, handClr) == GFX_STATUS_FAILURE)
                       return(GFX_STATUS_FAILURE);

                 GFX_GOL_ObjectStateClear(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_HOUR);

                 return(GFX_STATUS_SUCCESS);

            }

            if(GFX_GOL_ObjectStateGet(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE))
            {
                   if(GFX_GOL_AnalogClockHandsDraw(pAc, MINUTE, THICKNESS_SECOND+4, handClr) == GFX_STATUS_FAILURE)
                        return(GFX_STATUS_FAILURE);

                    GFX_GOL_ObjectStateClear(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE);

                    return(GFX_STATUS_SUCCESS);
            }

            if(GFX_GOL_ObjectStateGet(pAc, GFX_GOL_ANALOGCLOCK_TICK))
            {
                state = TICK;
                return(GFX_STATUS_FAILURE);
            }

        case BEVEL_DRAW:
            radius = pAc->radius;    // get radius
            width = (pAc->hdr.right - pAc->hdr.left) - (radius << 1);  // get width
            height = (pAc->hdr.bottom - pAc->hdr.top) - (radius << 1); // get height

            faceClr = pAc->hdr.pGolScheme->Color0;
            handClr = pAc->hdr.pGolScheme->Color1;
            state = BEVEL_DRAW;

            GFX_LineTypeSet(SOLID);

            GFX_ColorSet(faceClr);

            if(GFX_CircleFillDraw(pAc->centerx,pAc->centery, radius) == GFX_STATUS_FAILURE)  //Draw Face of Analog Clock
                return(GFX_STATUS_FAILURE); //Not done renderring

            state = BEVEL_DRAW1;

        case BEVEL_DRAW1:

            GFX_ColorSet(handClr);

            if(GFX_CircleFillDraw(pAc->centerx,pAc->centery, 8) == GFX_STATUS_FAILURE)  //Draw Middle of Analog Clock
                return(GFX_STATUS_FAILURE);

            GFX_GOL_ObjectStateSet(pAc, (GFX_GOL_ANALOGCLOCK_UPDATE_HOUR|GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE));
            state = TICK;

        case TICK:

	    if(GFX_GOL_AnalogClockHandsDraw(pAc, SECOND, THICKNESS_SECOND, handClr) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);

            if (pAc->valueS++ == 60) {
                pAc->valueS = 1;
                if (pAc->valueM++ == 60) {
                    pAc->valueM = 1;
                }
                if (pAc->valueM % 12 == 0) {
                    pAc->valueH++;
                    if (pAc->valueH == 60)
                        pAc->valueH = 0;

                    GFX_GOL_ObjectStateSet(pAc, (GFX_GOL_ANALOGCLOCK_UPDATE_HOUR));

                }

                GFX_GOL_ObjectStateSet(pAc, (GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE));
            }

            if (((uint16_t)(pAc->valueS - pAc->valueM) < 4)) //Redraw Minute hand if needed
                GFX_GOL_ObjectStateSet(pAc, (GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE));

            if (((uint16_t) (pAc->valueS - pAc->valueH) < 4)) // Redraw Hour hand if needed
                GFX_GOL_ObjectStateSet(pAc, (GFX_GOL_ANALOGCLOCK_UPDATE_HOUR));

            state = REMOVE;

            if (GFX_GOL_ObjectStateGet(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_HOUR) || GFX_GOL_ObjectStateGet(pAc, GFX_GOL_ANALOGCLOCK_UPDATE_MINUTE))
            {
                return (GFX_STATUS_FAILURE);
            }

    }

    return (GFX_STATUS_SUCCESS);
}

/* */
/*********************************************************************
* Function: uint16_t  GFX_GOL_AnalogHandsDraw(GFX_OBJ_ANALOGCLOCK *pAc, short hand, short thickness, uint16_t color, void *pBitmap)
*
*
* Notes: This is the state machine to draw the current hand positions of the clock.
*
********************************************************************/
GFX_STATUS  GFX_GOL_AnalogClockHandsDraw(GFX_GOL_ANALOGCLOCK *pAc, short hand, short thickness, GFX_COLOR color)
{
    static uint16_t templ=0,tempr, temps;
    static short   x1, y1;
    static short   x2_prev, y2_prev, xi_prev, yi_prev;
    static short   value=0, prev_value=0;
    static short   deltaX, deltaY;
    static short   error, stepErrorLT, stepErrorGE;
    static short   stepX, stepY;
    static short   steep;
    static short   temp;
    static short   cnt_thick=0;
    static short   radius;
    GFX_STATUS index = NULL;
    static uint8_t state = 0;
    static GFX_COLOR currentColor;
    static uint8_t redraw = 0;

while(redraw < 2)
{

switch(state)
{		

case 0:	

    radius = pAc->radius;
    
    switch(hand)
    {
		case SECOND:
			//value = pAc->valueS;
			prev_value = pAc->prev_valueS; 
			pAc->prev_valueS = pAc->valueS;
                        radius -=10;
			break;  

		case MINUTE:
			//value = pAc->valueM;
			prev_value = pAc->prev_valueM; 
			pAc->prev_valueM = pAc->valueM;
			radius -= 3;
			break;  
			
		case HOUR:
		//	value = pAc->valueH;
			prev_value = pAc->prev_valueH; 
			pAc->prev_valueH = pAc->valueH;
			radius -= 30;
			break;  

		default:
			break;  	   
	}

     x1 = pAc->centerx;
     y1 = pAc->centery;

     x2_prev = pAc->centerx;
     y2_prev = pAc->centery;

     prev_value += 45;

     if(prev_value >= 60)
        prev_value -= 60;

    GetCirclePoint(radius, (prev_value*6),&x2_prev,&y2_prev);

    x2_prev += pAc->centerx;
    y2_prev += pAc->centery;

    if(prev_value == 15)
	    x2_prev += 1;

    if(prev_value == 30)
	    y2_prev += 1;

    tempr = (thickness*thickness)>>1;
    temps = ((radius-(11))*(radius-(11)));

    switch(redraw)
    {
        case 0:
        currentColor = pAc->hdr.pGolScheme->Color0;
        break;
        case 1:
        currentColor = color;
        break;
    }

    redraw++;

    if(x1 == x2_prev)
    {
        if(y1 > y2_prev)
        {
            temp = y1;
            y1 = y2_prev;
            y2_prev = temp;
        }


        for(temp = y1; temp < y2_prev + 1; temp++)   //reDraws at top and bottom
        {
			
				for(cnt_thick=-thickness>>2;cnt_thick<thickness>>2;cnt_thick++)
				{	
					if(prev_value==45)
					templ = ((x1 + cnt_thick-x2_prev )*(x1 + cnt_thick-x2_prev ) + (temp - y1 )*(temp - y1 ));
					else if(prev_value==15)
					templ = ((x1 + cnt_thick-x2_prev )*(x1 + cnt_thick-x2_prev ) + (temp - y2_prev )*(temp - y2_prev ));
					
					
					if(templ>tempr && templ<temps)
					{
                    state = 1;
case 1:             GFX_ColorSet(currentColor);
                    
      			    if((index = GFX_PixelPut(x1 + cnt_thick, temp))== GFX_STATUS_FAILURE)
                                return(GFX_STATUS_FAILURE);
					}
				}	
        }

        state = 0;
        break;
    }

    if(y1 == y2_prev)
    {
        if(x1 > x2_prev)
        {
            temp = x1;
            x1 = x2_prev;
            x2_prev = temp;
        }

        for(temp = x1; temp <= x2_prev; temp++)    //redraws at left and right
        {
				for(cnt_thick=-thickness>>2;cnt_thick<thickness>>2;cnt_thick++)
				{
					if(prev_value==30)
					templ = ((temp-x1 )*(temp-x1 ) + (y1 + cnt_thick - y2_prev )*(y1 + cnt_thick - y2_prev ));
					else
					templ = ((temp-x2_prev )*(temp-x2_prev ) + (y1 + cnt_thick - y2_prev )*(y1 + cnt_thick - y2_prev ));
						
					if(templ>tempr && templ<temps)
					{
                    state = 2;
 case 2:                   
                                    GFX_ColorSet(currentColor);
			    if((index = GFX_PixelPut(temp, y1 + cnt_thick)) == GFX_STATUS_FAILURE)
                                return(GFX_STATUS_FAILURE);
					}
				}

        }

        state = 0;
        break;
    }

    stepX = 0;
    deltaX = x2_prev - x1;
    if(deltaX < 0)
    {
        deltaX = -deltaX;
        --stepX;
    }
    else
    {
        ++stepX;
    }

    stepY = 0;
    deltaY = y2_prev - y1;
    if(deltaY < 0)
    {
        deltaY = -deltaY;
        --stepY;
    }
    else
    {
        ++stepY;
    }

    steep = 0;
    if(deltaX < deltaY)
    {
        ++steep;
        temp = deltaX;
        deltaX = deltaY;
        deltaY = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
        temp = stepX;
        stepX = stepY;
        stepY = temp;
    }

    state = 3;
case 3:

    GFX_ColorSet(currentColor);

    if(GFX_PixelPut(x1, y1) == GFX_STATUS_FAILURE)
                return(GFX_STATUS_FAILURE);

    // If the current error greater or equal zero
    stepErrorGE = deltaX << 1;

    // If the current error less than zero
    stepErrorLT = deltaY << 1;

    // Error for the first pixel
    error = stepErrorLT - deltaX;

    while(--deltaX >= 0)
    {
        if(error >= 0)
        {
            y1 += stepY;
            error -= stepErrorGE;
        }

        x1 += stepX;
        error += stepErrorLT;

            if(steep)
            {
				for(cnt_thick=-thickness>>2;cnt_thick<thickness>>2;cnt_thick++)
				{
					templ = ((y1 + cnt_thick-x2_prev) *(y1 + cnt_thick-x2_prev) + (x1 - y2_prev)*(x1 - y2_prev));
					
					if(templ>tempr && templ<temps)
					{
                    state = 4;
case 4:
                    
                        GFX_ColorSet(currentColor);

					if((index = GFX_PixelPut(y1 + cnt_thick,x1)) == GFX_STATUS_FAILURE)
                                            return(GFX_STATUS_FAILURE);
					}
				}	

            }
            else
            {

				for(cnt_thick=-thickness>>2;cnt_thick<thickness>>2;cnt_thick++)
				{
					templ = ((x1-x2_prev)*(x1-x2_prev) + (y1 + cnt_thick - y2_prev)*(y1 + cnt_thick - y2_prev));
					
					if(templ>tempr && templ<temps)
					{
                        state = 5;
 case 5:                GFX_ColorSet(currentColor);
        
						if((index = GFX_PixelPut(x1,y1 + cnt_thick)) == GFX_STATUS_FAILURE)
                                                    return(GFX_STATUS_FAILURE);
					}
				}

            }
    }   
    state = 0;
    break;
}
}

redraw = 0;
state = 0;

return( GFX_STATUS_SUCCESS );

}

/*********************************************************************
* Function: GFX_GOL_AnalogClockHourSet(STATICTEXT *pAc, XCHAR *pText)
*
* Notes: Sets the Hour value of time.
*
********************************************************************/
void GFX_GOL_AnalogClockHourSet(GFX_GOL_ANALOGCLOCK *pAc, short hour)
{
     pAc->valueH = (hour*5) + (pAc->valueM/12);
}

/*********************************************************************
* Function: GFX_GOL_AnalogClockMinuteSet(STATICTEXT *pSt, XCHAR *pText)
*
* Notes: Sets the Second value of time.
*
********************************************************************/
void GFX_GOL_AnalogClockHourSecondSet(GFX_GOL_ANALOGCLOCK *pAc, short second)
{
     pAc->valueS = second;
}

/*********************************************************************
* Function: GFX_GOL_AnalogClock_SetMinute(STATICTEXT *pSt, XCHAR *pText)
*
* Notes: Sets the Minute value of time.
*
********************************************************************/
void GFX_GOL_AnalogClock_SetMinute(GFX_GOL_ANALOGCLOCK *pAc, short minute)
{
     pAc->valueM = minute;
}
