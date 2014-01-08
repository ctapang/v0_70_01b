/*****************************************************************************
 * File Name:       Transitions.c
 * Dependencies:    Transitions.h
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30 Version 3.00, C32
 * Linker:          MPLAB LINK30, LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright � 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
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
 * Date                     Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 24/12/2010	    		Initial version
 * 11/23/2011               Fix ExpandRectangle() issue where the edge shows 
 *                          garbage data. 
 * 11/29/2011               Fix ContractRectangle() issue where one line 
 *                          is not copied correctly. 
 *****************************************************************************************/
#include "gfx/gfx_primitive.h"
#include "gfx/gfx_transitions.h"

#ifdef USE_TRANSITION_EFFECTS

/* Local Function Prototypes*/
GFX_STATUS     PushRectangle(void);
GFX_STATUS     ExpandRectangle(void);
GFX_STATUS     ContractRectangle(void);
GFX_STATUS     SlideRectangle(void);
GFX_STATUS     ExpandLine(void);
GFX_STATUS     ContractLine(void);
/****************************************/

uint16_t _left, _top, _width, _height, _type, _delay_ms, _param1, _param2;
uint32_t _srcpageaddr, _destpageaddr;
uint8_t  _visualPage,_instance;
uint16_t Startx;
uint16_t Starty;
uint16_t x,y;
uint16_t Width;
uint16_t Height;

GFX_STATUS (*TransitionTask[6])(void) =
{
    ExpandRectangle,
    ContractRectangle,
    SlideRectangle,
    PushRectangle,
    ExpandLine,
    ContractLine
}; 

/************************************************************************
* Function: BYTE GFX_PRIM_SetTransitionParameters(short left, short top, short width, 
*                                   short height, GFX_TRANSITION_TYPE type, 
*                                   uint16_t delay_ms, uint16_t param1, uint16_t param2)
*                                                                       
* Overview: This function saves the parameters to be used and marks the 
*           transition to be pending which is executed when 
*           GFXExecutePendingTransition() is called. (Used with DOUBLE_BUFFERING)
*                                                                       
* Input:    left     ->  left x coordinate
*           top      ->  top y coordinate
*           type     ->  Transition type
*           delay_ms ->  Delay in milli seconds between redraws in the 
*                        screen while executing the transition
*           param1   ->  Transition-type specific parameter
*           param2   ->  Transition-type specific parameter
*                                                                       
* Output:   0       ->  Parameters successfully saved for the new transition
*           -1      ->  Parameters not saved as a transition is still pending
*                                                                       
************************************************************************/
GFX_STATUS GFX_TransitionParametersSet(short left, short top, GFX_TRANSITION_TYPE type, uint8_t sourcePage,
                                         uint8_t destinationPage, uint16_t delay_ms, uint16_t param1, 
                                         uint16_t param2)
{
    GFX_Primitive_instance.transitionParams.left = left;
    GFX_Primitive_instance.transitionParams.top = top;
    GFX_Primitive_instance.transitionParams.sourcePage = sourcePage;
    GFX_Primitive_instance.transitionParams.destinationPage = destinationPage;
    GFX_Primitive_instance.transitionParams.type = type;
    GFX_Primitive_instance.transitionParams.delay_ms = delay_ms;
    GFX_Primitive_instance.transitionParams.param1 = param1;
    GFX_Primitive_instance.transitionParams.param2 = param2;
    return(GFX_STATUS_SUCCESS);
}

/************************************************************************
* Function: void ExpandRectangle(void)
*                                                                       
* Overview: Expanding rectangle from the mid to the periphery
*                                                                       
* Input:    param1 (GFXTransition()) -> Pixel-block size to expand
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS ExpandRectangle(void)
{
    #define SCALE 100

    static uint16_t x,y,den,xpitch,ypitch,i,blocksize;
    static uint8_t state=0;

switch(state)
{
case 0:
     blocksize = _param1;  
     x = Width>>1;
     y = Height>>1;
     den = (x > y)? y: x;
     xpitch = x * SCALE / den;
     ypitch = y * SCALE / den;  
    
    for(i = 0; i <= den; i += blocksize)
    {
        x = (Width>>1) - ((i * xpitch) / SCALE);
        y = (Height>>1) - ((i * ypitch) / SCALE);
        state = 1;
case 1:
        GFX_AlphaParamsSet(_srcpageaddr,Startx + x,Starty + y,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage,Startx + x,Starty + y);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        ((xpitch * i)<<1) / SCALE, ((ypitch * i)<<1) / SCALE) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
       SYS_TMR_DelayMS(_delay_ms);
    }

}
state = 0;
return(GFX_STATUS_SUCCESS);

}

/************************************************************************
* Function: void ContractRectangle(void)
*                                                                       
* Overview: Expanding rectangle from the mid to the periphery
*                                                                       
* Input:    param1 (GFXTransition()) -> Pixel-block size to expand
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS ContractRectangle(void)
{
    #define SCALE 100

    static uint16_t x, y, den, xpitch, ypitch, i, blocksize;
    static uint8_t state=0;

switch(state)
{
case 0:
    x = Width>>1;
    y = Height>>1;
    den = (x > y)? y: x;
    xpitch = x * SCALE / den;
    ypitch = y * SCALE / den;
    blocksize = _param1;
    
    for(i = 0; i <= den; i += blocksize)
    {
        x = (i * xpitch) / SCALE;
        y = (i * ypitch) / SCALE;
        state = 1;
case 1:
        GFX_AlphaParamsSet(_srcpageaddr,Startx,Starty,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage,Startx,Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        x, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, y) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        state = 2;
case 2:
        GFX_AlphaParamsSet(_srcpageaddr,Startx + Width - x,Starty,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage,Startx + Width - x,Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        x, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        state = 3;
case 3:
        GFX_AlphaParamsSet(_srcpageaddr,Startx,Starty + Height - y,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage,Startx,Starty + Height - y);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, y) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        
        SYS_TMR_DelayMS(_delay_ms);
    }

}

state = 0;
return(GFX_STATUS_SUCCESS);
}

/************************************************************************
* Function: void ExpandLine(void)
*                                                                       
* Overview: Expanding line from the mid to the periphery
*                                                                       
* Input:    param1 (GFXTransition())  -> Pixel-block size to expand
*           param2 (GFXTransition()) ->  Direction of transition - HORIZONTAL/VERTICAL
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS ExpandLine(void)
{    
    static uint8_t state = 0;
    static uint16_t blocksize,direction;
    static uint16_t i;

switch(state)
{

case 0:

    blocksize = _param1;
    direction = _param2;

    if(direction == HORIZONTAL)
    {
        state = 1;

        for(i = 1; i <= Width / (blocksize<<1); i++)
        {

case 1:        GFX_AlphaParamsSet(_srcpageaddr,Startx + (Width>>1) - (i * blocksize),Starty,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage,Startx + (Width / 2) - (i * blocksize), Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        (i * blocksize)<<1, Height) == NULL) return(0);

        SYS_TMR_DelayMS(_delay_ms);

        }
    }
    else if(direction == VERTICAL)
    {
        state = 2;
        
        for(i = 1; i <= Height / (blocksize<<1); i++)
        {

 case 2:   GFX_AlphaParamsSet(_srcpageaddr,Startx, (Starty + (Height>>1) - (i * blocksize)),
                                             _srcpageaddr,0, 0,
                                             GFX_Primitive_instance.transitionPage,Startx,(Starty + (Height>>1) - (i * blocksize)));

            if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, (i * blocksize)<<1) == NULL) return(0);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
}

state = 0;
return(GFX_STATUS_SUCCESS);
}

/************************************************************************
* Function: void ContractLine(void)
*                                                                       
* Overview: Expanding line from the mid to the periphery
*                                                                       
* Input:    param1 (GFXTransition())  -> Pixel-block size to expand
*               param2 (GFXTransition()) ->  Direction of transition - HORIZONTAL/VERTICAL
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS ContractLine(void)
{    
    static uint16_t i;
    static uint8_t state = 0;
    static uint16_t blocksize,direction;

switch(state)
{
    blocksize = _param1;
    direction = _param2;

case 0:

    if(direction == HORIZONTAL)
    {
        
        for(i = 0; i < Width / (blocksize<<1); i++)
        {

           state = 1;

case 1:    GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty,
                                       _srcpageaddr, 0, 0,
                                       GFX_Primitive_instance.transitionPage, Startx, Starty);

            if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        (i + 1) * blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
           state = 2;

case 2:           GFX_AlphaParamsSet(_srcpageaddr, Startx + Width - (i * blocksize) - blocksize, Starty,
                                       _srcpageaddr,0, 0,
                                       GFX_Primitive_instance.transitionPage, Startx + Width - (i * blocksize) - blocksize, Starty);

            if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        (i + 1) * blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == VERTICAL)
    {
        
        for(i = 0; i < Height / (blocksize<<1); i++)
        {
        state = 3;
case 3:        GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty,
                                       _srcpageaddr,0,0,
                                       GFX_Primitive_instance.transitionPage, Startx, Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, (i + 1) * blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        state = 4;

case 4:        GFX_AlphaParamsSet(_srcpageaddr,Startx, Starty + Height - (i * blocksize) - blocksize,
                                       _srcpageaddr, 0, 0,
                                       GFX_Primitive_instance.transitionPage, Startx, Starty + Height - (i * blocksize) - blocksize);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, (i + 1) * blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
}
state = 0;
return(GFX_STATUS_SUCCESS);
}

/************************************************************************
* Function: uint8_t SlideRectangle(void)
*                                                                       
* Overview: New screen slides-in overwriting the old screen
*                                                                       
* Input:    param1 (GFXTransition()) -> Pixel-block size to expand
*           param2 (GFXTransition()) -> Sliding direction LEFT_TO_RIGHT/RIGHT_TO_LEFT/TOP_TO_BOTTOM/BOTTOM_TO_TOP
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS SlideRectangle(void)
{
    static short x, y;
    static uint16_t blocksize,direction;
    static uint8_t state = 0;

switch(state)
{    
case 0:
    blocksize = _param1;
    direction = _param2;

    if(direction == LEFT_TO_RIGHT)
    {
        for(x = Width; x > 0; x -= blocksize)
        {
        state = 1;
case 1:
        GFX_AlphaParamsSet(_srcpageaddr,Startx + x - blocksize, Starty,
                                       _srcpageaddr, 0, 0,
                                       GFX_Primitive_instance.transitionPage,Startx,Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width - x + blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == RIGHT_TO_LEFT)
    {
        for(x = (Width-blocksize); x > blocksize; x -= blocksize)
        {
        state = 2;
case 2:
        GFX_AlphaParamsSet(_srcpageaddr, Startx,Starty,
                                       _srcpageaddr,0, 0,
                                       GFX_Primitive_instance.transitionPage,Startx + x - blocksize, Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width - x + blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == TOP_TO_BOTTOM)
    {
        for(y = Height; y > 0; y -= blocksize)
        {
        state = 3;
case 3:  GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty + y - blocksize,
                                       _srcpageaddr,0, 0,
                                       GFX_Primitive_instance.transitionPage,Startx, Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, Height - y + blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

           SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == BOTTOM_TO_TOP)
    {
        for(y = Height; y > 0; y -= blocksize)
        {
        state = 4;
case 4:
        GFX_AlphaParamsSet(_srcpageaddr,Startx, Starty,
                                       _srcpageaddr, 0, 0,
                                       GFX_Primitive_instance.transitionPage,Startx,Starty + y - blocksize);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, Height - y + blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

          SYS_TMR_DelayMS(_delay_ms);
        }
    }
}
state = 0;
return(GFX_STATUS_SUCCESS); //Done with the transition

}
/************************************************************************
* Function: uint8_t GFX_Transition(GFX_PRIM_TRANSITION* transitionParams)
*                                                                       
* Overview: This function saves the parameters to be used and marks the 
*           transition to be pending which is executed when 
*           GFXExecutePendingTransition() is called
*                                                                       
* Input:    left         ->  left x coordinate
*           top          ->  top y coordinate
*           width        ->  width of the transition
*           height       ->  height of the transition
*           type         ->  Transition type
*           srcpageaddr  ->  Source page address for the transition
*           destpageaddr ->  Destination page address for the transition
*           delay_ms     ->  Delay in milli seconds between redraws in the 
*                            screen while executing the transition
*           param1       ->  Transition-type specific parameter
*           param2       ->  Transition-type specific parameter
*                                                                       
* Output:   0       ->  Transition executed successfully
*           -1      ->  Transition not executed
*                                                                       
************************************************************************/
GFX_STATUS GFX_Transition(GFX_TRANSITION_PARAMS* transitionParams, short width, short height)
{

    static uint8_t state = 0;

switch(state)
{
case 0: //Copy Visual Page to Transition page
    _instance = 0;
    _visualPage = GFX_Primitive_instance.visualPage;
    
    GFX_AlphaParamsSet(_visualPage, 0, 0,
                              _visualPage, 0, 0,
                              GFX_Primitive_instance.transitionPage, 0, 0);

    if(CopyPageWindow(
                      &GFX_Primitive_instance.alphaArea,
                      GFX_MaxXGet(), GFX_MaxYGet()) == GFX_STATUS_FAILURE)
    {
         return(GFX_STATUS_FAILURE);
    }

    state = 1;

case 1:
    
    if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(VISUAL_PAGE, GFX_Primitive_instance.transitionPage))
    {
        return(GFX_STATUS_FAILURE);
    }

    Startx = transitionParams->left;
    Starty = transitionParams->top;
    x = Startx;
    y = Starty;
    Width = width;
    Height = height;

    _delay_ms = transitionParams->delay_ms;
    _srcpageaddr = transitionParams->sourcePage;
    _destpageaddr = transitionParams->destinationPage;
    _param1 = transitionParams->param1;
    _param2 = transitionParams->param2;
    state = 2;

case 2:
    GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty,
                              _srcpageaddr, Startx, Starty,
                              GFX_Primitive_instance.transitionPage, Startx, Starty);

    if(CopyPageWindow(
                      &GFX_Primitive_instance.alphaArea,
                      Width, Height) == GFX_STATUS_FAILURE)
    {
        return(GFX_STATUS_FAILURE);
    }

    state = 3;


case 3:
if(!TransitionTask[transitionParams->type]()) return(GFX_STATUS_FAILURE);

state = 4;

case 4:
   GFX_AlphaParamsSet(_destpageaddr, Startx, Starty,
                              _destpageaddr, Startx, Starty,
                              GFX_Primitive_instance.transitionPage, Startx, Starty);

    if(CopyPageWindow(
                      &GFX_Primitive_instance.alphaArea,
                      Width, Height) == GFX_STATUS_FAILURE)
   {
        return(GFX_STATUS_FAILURE);
    }
    state = 5;

state = 5;

case 5:
   GFX_AlphaParamsSet(GFX_Primitive_instance.transitionPage, 0, 0,
                              GFX_Primitive_instance.transitionPage, 0, 0,
                              _visualPage, 0, 0);

    if(CopyPageWindow(
                      &GFX_Primitive_instance.alphaArea,
                      GFX_MaxXGet(), GFX_MaxYGet()) == GFX_STATUS_FAILURE)
    {
        return(GFX_STATUS_FAILURE);
    }
    state = 6;

case 6:
    if(GFX_DRV_instance[0].PrimitiveFunction.PageSet(VISUAL_PAGE, _visualPage))
    {
        return(GFX_STATUS_FAILURE);
    }

}

    state = 0;
    return (GFX_STATUS_SUCCESS);
}

/************************************************************************
* Function: uint8_t PushRectangle(void)
*                                                                       
* Overview: New screen slides-in pushing out the old slide
*                                                                       
* Input:    param1 (GFXTransition()) -> Pixel-block size to expand
*           param2 (GFXTransition()) -> Sliding direction LEFT_TO_RIGHT/RIGHT_TO_LEFT/TOP_TO_BOTTOM/BOTTOM_TO_TOP                                                         
*                                                                       
* Output:   none
*                                                                       
************************************************************************/
GFX_STATUS PushRectangle()
{
    static short x, y;
    static uint16_t blocksize,direction;
    static uint8_t state = 0;

if(!state)
{
    blocksize = _param1;
    direction = _param2;
}
switch(state)
{

case 0:

    if(direction == LEFT_TO_RIGHT)
    {
        for(x = Width; x > blocksize; x -= blocksize)
        {
        state = 1;
case 1:
        GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty,
                                       _srcpageaddr, 0, 0, //Doesn't matter
                                       GFX_Primitive_instance.transitionPage, Startx + (Width - x) + blocksize, Starty);

            if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        (x - blocksize), Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        state = 2;
case 2:

        GFX_AlphaParamsSet(_destpageaddr,Startx + x - blocksize, Starty,
                                       _destpageaddr,0, 0, //Doesn't matter
                                       GFX_Primitive_instance.transitionPage, Startx, Starty);
        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width - x + blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

         SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == RIGHT_TO_LEFT)
    {
        for(x = Width; x > blocksize; x -= blocksize)
        {

        state = 3;
case 3:
        GFX_AlphaParamsSet(_srcpageaddr,Startx + (Width-x) + blocksize, Starty,
                                  _srcpageaddr,0, 0, //Doesn't matter
                                  GFX_Primitive_instance.transitionPage,Startx,Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        x - blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
       
       state = 4;
case 4:

        GFX_AlphaParamsSet(_destpageaddr,Startx, Starty,
                                       _destpageaddr,0, 0, //Doesn't matter
                                       GFX_Primitive_instance.transitionPage, Startx + x - blocksize, Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width - x + blocksize, Height) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);

           SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == TOP_TO_BOTTOM)
    {
        for(y = Height; y > blocksize; y -= blocksize)
        {

        state = 5;
case 5:

        GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty,
                                  _srcpageaddr, 0, 0,
                                  GFX_Primitive_instance.transitionPage, Startx, Starty + (Height-y) + blocksize);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, y - blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
           
        state = 6;
case 6:
        GFX_AlphaParamsSet(_destpageaddr,Startx, Starty + y - blocksize,
                                       _destpageaddr,0, 0,
                                       GFX_Primitive_instance.transitionPage, Startx, Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                        Width, Height - y + blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
         SYS_TMR_DelayMS(_delay_ms);
        }
    }
    else if(direction == BOTTOM_TO_TOP)
    {
        for(y = Height; y > blocksize; y -= blocksize)
        {
        state = 7;
case 7:
        GFX_AlphaParamsSet(_srcpageaddr, Startx, Starty + (Height-y) + blocksize,
                                       _srcpageaddr,0, 0,
                                       GFX_Primitive_instance.transitionPage,Startx,Starty);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                         Width, y - blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
        state = 8;
case 8:
        GFX_AlphaParamsSet(_destpageaddr,Startx, Starty,
                                       _destpageaddr, 0, 0,
                                       GFX_Primitive_instance.transitionPage, Startx, Starty + y - blocksize);

        if(CopyPageWindow(
                        &GFX_Primitive_instance.alphaArea,
                         Width, Height - y + blocksize) == GFX_STATUS_FAILURE) return(GFX_STATUS_FAILURE);
           SYS_TMR_DelayMS(_delay_ms);
        }
    }
}
state = 0; // Reset state machine
return(GFX_STATUS_SUCCESS); //Done renderring

}

#endif //USE_TRANSITION_EFFECTS
