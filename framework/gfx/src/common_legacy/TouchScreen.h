/*****************************************************************************
 * Simple 4 wire resistive touch screen driver
 *****************************************************************************
 * File Name:       TouchScreenResistive.h
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:       	MPLAB C30, MPLAB C32
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * Copyright (c) 2011 Microchip Technology Inc.  All rights reserved.
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
 * Date        	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 01/19/11		Ported from TouchScreen.h. 
 * 10/03/11     Modified TouchDetectPosition() to return status of touch
 *              sampling.
 *****************************************************************************/

/*****************************************************************************
 Description:  This is a resistive touch screen driver that is using the 
			   Microchip Graphics Library. The calibration values are 
			   automatically checked (by reading a specific memory location
			   on the non-volatile memory) when initializing the module if the 
			   function pointers to the read and write callback functions 
			   are initialized. If the read value is invalid calibration 
			   will automatically be executed. Otherwise, the calibration
			   values will be loaded and used.
			   The driver assumes that the application side provides the 
			   read and write routines to a non-volatile memory. 
			   If the callback functions are not initialized, the calibration
			   routine will always be called at startup to initialize the
			   global calibration values.
			   This driver assumes that the Graphics Library is initialized 
			   and will be using the default font of the library.
 *****************************************************************************/

#ifndef _TOUCHSCREEN_H
#define _TOUCHSCREEN_H

#include "gfx/gfx_gol.h"

#include "system/msg/sys_msg.h"
#include "system/msg/src/sys_msg_local.h"

extern SYS_MSG_OBJECT myMessage;
extern SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;
extern SYS_MSG_INSTANCE iSysMsg;

typedef uint16_t (*NVM_READ_FUNC)(uint32_t);           // typedef for read function pointer
typedef void (*NVM_WRITE_FUNC)(uint16_t, uint32_t);    // typedef for write function pointer
typedef void (*NVM_SECTORERASE_FUNC)(uint32_t);    // typedef for sector erase function pointer
#include "TouchScreenCapacitive.h"
/*********************************************************************
* Function: short TouchDetectPosition(void)
*
* PreCondition: none
*
* Input: none
*
* Output: Returns 1 if touch sampling is done.
*         Returns 0 if the touch sampling is not finished.  
*
* Side Effects: none
*
* Overview: Process the detection of touch
*
* Note: none
*
********************************************************************/
short TouchDetectPosition(void);

/*********************************************************************
* Function: void TouchInit(NVM_WRITE_FUNC pWriteFunc, NVM_READ_FUNC pReadFunc, NVM_SECTORERASE_FUNC pSectorErase, void *initValues)
*
* PreCondition: none
*
* Input: pWriteFunc - non-volatile memory write function pointer
*        pReadFunc - non-volatile memory read function pointer
*        pSectorErase - non-volatile memory sector function pointer
*
* Output: none
*
* Side Effects: none
*
* Overview: Initializes the touch screen hardware.
*
* Note: none
*
********************************************************************/
void TouchInit(NVM_WRITE_FUNC pWriteFunc, NVM_READ_FUNC pReadFunc, NVM_SECTORERASE_FUNC pSectorErase, void *initValues);

/*********************************************************************
* Function: short TouchGetX()
*
* PreCondition: none
*
* Input: none
*
* Output: x coordinate
*
* Side Effects: none
*
* Overview: returns x coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
short TouchGetX(uint8_t);
/*********************************************************************
* Function: short TouchGetRawX()
*
* PreCondition: none
*
* Input: none
*
* Output: x raw value
*
* Side Effects: none
*
* Overview: returns x coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
short TouchGetRawX(void);

/*********************************************************************
* Function: short TouchGetY()
*
* PreCondition: none
*
* Input: none
*
* Output: y coordinate
*
* Side Effects: none
*
* Overview: returns y coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
short TouchGetY(uint8_t);

/*********************************************************************
* Function: short TouchGetRawY()
*
* PreCondition: none
*
* Input: none
*
* Output: raw y value
*
* Side Effects: none
*
* Overview: returns y coordinate if touch screen is pressed
*           and -1 if not
*
* Note: none
*
********************************************************************/
short TouchGetRawY(void);

/*********************************************************************
* Function: void TouchGetMsg()
*
* PreCondition: none
*
* Input: pointer to the message structure to be populated
*
* Output: none
*
* Side Effects: none
*
* Overview: populates GOL message structure
*
* Note: none
*
********************************************************************/
void TouchGetMsg();

/*********************************************************************
* Function: void TouchCalibration()
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Runs the calibration routine. 
*
* Note: none
*
********************************************************************/
void TouchCalibration(void);


/*********************************************************************
* Function: void Touch_ADCInit(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Initializes the ADC for the touch detection.
*
* Note: none
*
********************************************************************/
void Touch_ADCInit(void);


// macro to draw repeating text
#define TouchShowMessage( pStr, color, x, y, width, height)             \
                {                                       \
                    GFX_ColorSet( color);                    \
                    while(GFX_TextStringBoxDraw(x,y,width,height,pStr, 0, 0)==1);        \
                }	

#endif //_TOUCHSCREEN_RESISTIVE_H
