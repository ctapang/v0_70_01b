/*****************************************************************************
 * File Name:       TouchScreenCapacitive.c
 * Processor:       PIC24, PIC32, dsPIC, PIC24H
 * Compiler:        MPLAB C30, MPLAB C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
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
 */

#include "gfx/src/common_legacy/TouchScreen.h"
#include "gfx/src/common_legacy/TouchScreenCapacitive.h"
#include <sys/attribs.h>
#include <sys/kmem.h>

     volatile short PCapX[5]= {-1,-1,-1,-1,-1};
     volatile short PCapY[5]= {-1,-1,-1,-1,-1};

// Default Calibration Inset Value (percentage of vertical or horizontal resolution)
// Calibration Inset = ( CALIBRATIONINSET / 2 ) % , Range of 0–20% with 0.5% resolution
// Example with CALIBRATIONINSET == 20, the calibration points are measured
// 10% from the corners.
#ifndef CALIBRATIONINSET
    #define CALIBRATIONINSET   5       // range 0 <= CALIBRATIONINSET <= 40
#endif

#define CAL_X_INSET    (((480)*(CALIBRATIONINSET>>1))/100)
#define CAL_Y_INSET    (((272)*(CALIBRATIONINSET>>1))/100)
#define SAMPLE_POINTS   4

//////////////////////// Resistive Touch Driver Version ////////////////////////////
// The first four bits is the calibration inset, next 8 bits is assigned the version 
// number and 0xF is assigned to this 4-wire resistive driver.
const uint16_t mchpTouchScreenVersion = 0xF110 | CALIBRATIONINSET;

//////////////////////// A/D Sampling Mode ///////////////////////
// first some error check
#if defined (RESISTIVETOUCH_MANUAL_SAMPLE_MODE) &&  defined (RESISTIVETOUCH_AUTO_SAMPLE_MODE)
    #error Cannot have two resistive touch modes enabled.
#endif
#ifndef RESISTIVETOUCH_MANUAL_SAMPLE_MODE
    // enable auto sampling mode
    #define RESISTIVETOUCH_AUTO_SAMPLE_MODE
    // else manual sampling mode is enabled 
#endif

//////////////////////// GUI Color Assignments ///////////////////////
// Set the colors used in the calibration screen, defined by 
// GraphicsConfig.h or gfxcolors.h 
#if (COLOR_DEPTH == 1)
    #define RESISTIVETOUCH_FOREGROUNDCOLOR BLACK	   
    #define RESISTIVETOUCH_BACKGROUNDCOLOR WHITE	   
#elif (COLOR_DEPTH == 4)
    #define RESISTIVETOUCH_FOREGROUNDCOLOR BLACK	   
    #define RESISTIVETOUCH_BACKGROUNDCOLOR WHITE	   
#elif (COLOR_DEPTH == 8) || (COLOR_DEPTH == 16) || (COLOR_DEPTH == 24) 
    #define RESISTIVETOUCH_FOREGROUNDCOLOR BRIGHTRED	   
    #define RESISTIVETOUCH_BACKGROUNDCOLOR WHITE	   
#endif

//////////////////////// LOCAL PROTOTYPES ////////////////////////////
void    TouchGetCalPoints(void);
void 	TouchStoreCalibration(void);
void 	TouchCheckForCalibration(void);
void 	TouchLoadCalibration(void);
void    TouchCalculateCalPoints(void);

#ifdef ENABLE_DEBUG_TOUCHSCREEN
void    TouchScreenResistiveTestXY(void);
#endif

extern NVM_READ_FUNC           pCalDataRead;                // function pointer to data read
extern NVM_WRITE_FUNC          pCalDataWrite;               // function pointer to data write
extern NVM_SECTORERASE_FUNC    pCalDataSectorErase;         // function pointer to data sector erase

//////////////////////// GLOBAL VARIABLES ////////////////////////////
#define CALIBRATION_DELAY   300				                // delay between calibration touch points

// Current ADC values for X and Y channels
volatile short  adcX = -1;
volatile short  adcY = -1;
volatile short  adcPot = 0;

// coefficient values
volatile long   _trA;
volatile long   _trB;
volatile long   _trC;
volatile long   _trD;

// copy of the stored or sampled raw points (this is the calibration data stored)
/*      xRawTouch[0] - x sample from upper left corner; 
        xRawTouch[1] - x sample from upper right corner
        xRawTouch[2] - x sample from lower right corner
        xRawTouch[3] - x sample from lower left corner
        yRawTouch[0] - y sample from upper left corner; 
        yRawTouch[1] - y sample from upper right corner
        yRawTouch[2] - y sample from lower right corner
        yRawTouch[3] - y sample from lower left corner
*/
volatile short  xRawTouch[SAMPLE_POINTS] = {TOUCHCAL_ULX, TOUCHCAL_URX, TOUCHCAL_LRX, TOUCHCAL_LLX};
volatile short  yRawTouch[SAMPLE_POINTS] = {TOUCHCAL_ULY, TOUCHCAL_URY, TOUCHCAL_LRY, TOUCHCAL_LLY};

void TouchInit(NVM_WRITE_FUNC pWriteFunc, NVM_READ_FUNC pReadFunc, NVM_SECTORERASE_FUNC pSectorErase, void *initValues)
{

   unsigned int val;

    //Change the cache mode for I2C PCAP Touch
    asm volatile("mfc0   %0,$16" : "=r"(val));
    val |= 0x07;
    val ^= 0x07;
    val |= 0x01;
    asm volatile("mtc0   %0,$16" : "+r"(val));
   
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.DMAPRI = 1;
    INT1Rbits.INT1R = 0x0d;  //Enable INT1 on PPS
    SYSKEY = 0x33333333;
    ANSELA, ANSELB, ANSELC, ANSELD, ANSELE = 0;
    ANSELF, ANSELG, ANSELH, ANSELJ, ANSELK = 0;
    I2C_Init();
}


/*********************************************************************
* Function: void TouchHardwareInit(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Initializes touch screen module.
*
* Note: none
*
********************************************************************/
void TouchHardwareInit(void *initValues)
{
}

/*********************************************************************
* Function: SHORT TouchGetX()
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
short TouchGetX(uint8_t touchNumber)
{
    static short    result;

    result = PCapX[touchNumber];
    return ((short)result);
}

/*********************************************************************
* Function: SHORT TouchGetY()
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
short TouchGetY(uint8_t touchNumber)
{
    static short    result;
    result = PCapY[touchNumber];
    return ((short)result);
}

void __ISR_AT_VECTOR(_EXTERNAL_1_VECTOR, IPL5) _PCAPHandler(void)
{
     static uint8_t data[6] = {0,0,0,0,0,0};
     static uint8_t touchpoint;
     static uint8_t penstatus;
     static short lastX;
     static short lastY;

     I2C1CONCLR = 0x8000; //Reset Status Registers
     I2C1CONSET = 0x8000;

     if(!I2C_ReadBlock(0x4a,0x55, &data[0], 6))
     {

        penstatus = (data[1] & 0x01);
        touchpoint = (data[1]&0x78)>>3;

        if(penstatus == 1)
        {

            lastX = data[2];
            lastX |= (uint16_t)(data[3]<<7);

            lastY = data[4];
            lastY |= (uint16_t)(data[5]<<7);

            PCapX[touchpoint] = ((lastX * (480))>>10) - CAL_X_INSET;
            PCapY[touchpoint] = ((lastY * (272))>>10);
            TouchGetMsg();
        }
        else if(penstatus == 0)
        {
            PCapX[touchpoint] = -1;
            PCapY[touchpoint] = -1;
            TouchGetMsg();
        }
    }
     
    IFS0CLR = 0x100;
}

