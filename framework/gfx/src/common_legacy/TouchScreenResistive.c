/*****************************************************************************
 *
 * Simple 4 wire resistive touch screen driver
 *
 *****************************************************************************
 * File Name:       TouchScreenResistive.c
 * Processor:       PIC24, PIC32, dsPIC, PIC24H
 * Compiler:       	MPLAB C30, MPLAB C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright � 2011 Microchip Technology Inc.  All rights reserved.
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
 * 01/19/11		Ported from TouchScreen driver.
 * 05/06/11     Added IDLE state and set start up state to IDLE.
 * 10/03/11     - Modified the calibration sequence.
 *              - Modified TouchDetectPosition() sampling to single A/D sampling.
 *              - Modified TouchDetectPosition() to return status of sampling.
 *              - Added Touch_ADCInit() to separate A/D initialization. This 
 *                will be useful when A/D is shared by multiple drivers.
 * 01/13/12     - Modified the calibration to store 8 data points.  
 *              - Modified the calculation of the x,y touch positions to fix
 *                overflow issue.
 * 05/16/12     Modified macros to be flexible with other PIC devices:
 *              - TRIS_XPOS, TRIS_YPOS, TRIS_XNEG, TRIS_YNEG,    
 *                LAT_XPOS, LAT_YPOS, LAT_XNEG, LAT_YNEG to 
 *                ResistiveTouchScreen_X(Y)Plus_Drive_High(), 
 *                ResistiveTouchScreen_X(Y)Plus_Drive_Low(), 
 *                ResistiveTouchScreen_X(Y)Plus_Config_As_Input(), 
 *                ResistiveTouchScreen_X(Y)Plus_Config_As_Output()  
 *                ResistiveTouchScreen_X(Y)Minus_Drive_High(), 
 *                ResistiveTouchScreen_X(Y)Minus_Drive_Low(), 
 *                ResistiveTouchScreen_X(Y)Minus_Config_As_Input(), 
 *                ResistiveTouchScreen_X(Y)Minus_Config_As_Output().
 *              - added two macros RESISTIVETOUCH_ANALOG and 
 *                RESISTIVETOUCH_DIGITAL to indicate pin mode.
 *
 *****************************************************************************/

#include "system_config.h"

#if defined (USE_TOUCHSCREEN_RESISTIVE)

#define INSTANCE 0

#include "gfx/gfx.h"
#include "gfx/src/common_legacy/TouchScreen.h"
#include "gfx/src/common_legacy/TouchScreenResistive.h"
#include "peripheral/adc/plib_adc.h"
#include "internal_resource.h"

// Default Calibration Inset Value (percentage of vertical or horizontal resolution)
// Calibration Inset = ( CALIBRATIONINSET / 2 ) % , Range of 0�20% with 0.5% resolution
// Example with CALIBRATIONINSET == 20, the calibration points are measured
// 10% from the corners.
#ifndef CALIBRATIONINSET
#define CALIBRATIONINSET   20       // range 0 <= CALIBRATIONINSET <= 40 
#endif

#define CAL_X_INSET    (((GFX_MaxXGet()+1)*(CALIBRATIONINSET>>1))/100)
#define CAL_Y_INSET    (((GFX_MaxYGet()+1)*(CALIBRATIONINSET>>1))/100)
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
#if (GFX_CONFIG_COLOR_DEPTH == 1)
#define RESISTIVETOUCH_FOREGROUNDCOLOR() RGBConvert(0, 0, 0)
#define RESISTIVETOUCH_BACKGROUNDCOLOR() GFX_RGBConvert(255, 255, 255)
#elif (GFX_CONFIG_COLOR_DEPTH == 4)
#define RESISTIVETOUCH_FOREGROUNDCOLOR() RGBConvert(0, 0, 0)
#define RESISTIVETOUCH_BACKGROUNDCOLOR() GFX_RGBConvert(255, 255, 255)
#elif (GFX_CONFIG_COLOR_DEPTH == 8) || (GFX_CONFIG_COLOR_DEPTH == 16) || (GFX_CONFIG_COLOR_DEPTH == 24)
#define RESISTIVETOUCH_FOREGROUNDCOLOR GFX_RGBConvert(128, 0, 0)
#define RESISTIVETOUCH_BACKGROUNDCOLOR GFX_RGBConvert(255, 255, 255)
#endif

#ifndef ResistiveTouchScreen_XPlus_Config_As_Input
#define ResistiveTouchScreen_XPlus_Config_As_Input() (TRIS_XPOS = 1)
#endif
#ifndef ResistiveTouchScreen_YPlus_Config_As_Input
#define ResistiveTouchScreen_YPlus_Config_As_Input() (TRIS_YPOS = 1)
#endif
#ifndef ResistiveTouchScreen_XMinus_Config_As_Input
#define ResistiveTouchScreen_XMinus_Config_As_Input() (TRIS_XNEG = 1)
#endif
#ifndef ResistiveTouchScreen_YMinus_Config_As_Input
#define ResistiveTouchScreen_YMinus_Config_As_Input() (TRIS_YNEG = 1)
#endif
#ifndef ResistiveTouchScreen_XPlus_Config_As_Output
#define ResistiveTouchScreen_XPlus_Config_As_Output() (TRIS_XPOS = 0)
#endif
#ifndef ResistiveTouchScreen_YPlus_Config_As_Output
#define ResistiveTouchScreen_YPlus_Config_As_Output() (TRIS_YPOS = 0)
#endif
#ifndef ResistiveTouchScreen_XMinus_Config_As_Output
#define ResistiveTouchScreen_XMinus_Config_As_Output() (TRIS_XNEG = 0)
#endif
#ifndef ResistiveTouchScreen_YMinus_Config_As_Output
#define ResistiveTouchScreen_YMinus_Config_As_Output() (TRIS_YNEG = 0)
#endif
#ifndef ResistiveTouchScreen_XMinus_Drive_Low
#define ResistiveTouchScreen_XMinus_Drive_Low() (LAT_XNEG = 0)
#endif
#ifndef ResistiveTouchScreen_YMinus_Drive_Low
#define ResistiveTouchScreen_YMinus_Drive_Low() (LAT_YNEG = 0)
#endif
#ifndef ResistiveTouchScreen_XPlus_Drive_High
#define ResistiveTouchScreen_XPlus_Drive_High() (LAT_XPOS = 1)
#endif
#ifndef ResistiveTouchScreen_YPlus_Drive_High
#define ResistiveTouchScreen_YPlus_Drive_High() (LAT_YPOS = 1)
#endif
#ifndef RESISTIVETOUCH_ANALOG
#define RESISTIVETOUCH_ANALOG  0
#endif
#ifndef RESISTIVETOUCH_DIGITAL
#define RESISTIVETOUCH_DIGITAL 1 
#endif

//////////////////////// LOCAL PROTOTYPES ////////////////////////////
void TouchGetCalPoints(void);
void TouchStoreCalibration(void);
void TouchCheckForCalibration(void);
void TouchLoadCalibration(void);
void TouchCalculateCalPoints(void);

#ifdef ENABLE_DEBUG_TOUCHSCREEN
void TouchScreenResistiveTestXY(void);
#endif

extern NVM_READ_FUNC pCalDataRead; // function pointer to data read
extern NVM_WRITE_FUNC pCalDataWrite; // function pointer to data write
extern NVM_SECTORERASE_FUNC pCalDataSectorErase; // function pointer to data sector erase

//////////////////////// GLOBAL VARIABLES ////////////////////////////
#define INSTANCE 0 //TODO: Instance always 0 for now. (in touch functions only)

#ifndef TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD
// you may define the threshold with a value, define the new value in the 
// hardwareprofile.h
#define TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD     256	// between 0-0x03ff the lesser this value 
// the lighter the screen must be pressed
#endif

#define CALIBRATION_DELAY   300				                // delay between calibration touch points

// Current ADC values for X and Y channels
volatile short adcX = -1;
volatile short adcY = -1;
volatile short adcPot = 0;

// coefficient values
volatile long _trA;
volatile long _trB;
volatile long _trC;
volatile long _trD;

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
volatile short xRawTouch[SAMPLE_POINTS] = {TOUCHCAL_ULX, TOUCHCAL_URX, TOUCHCAL_LRX, TOUCHCAL_LLX};
volatile short yRawTouch[SAMPLE_POINTS] = {TOUCHCAL_ULY, TOUCHCAL_URY, TOUCHCAL_LRY, TOUCHCAL_LLY};

// WARNING: Watch out when selecting the value of SCALE_FACTOR 
// since a big value will overflow the signed int type 
// and the multiplication will yield incorrect values.
#ifndef TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR
// default scale factor is 256
    #define TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR 8
#endif


// use this scale factor to avoid working in floating point numbers
#define SCALE_FACTOR (1<<TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR)

typedef enum {
    IDLE,
    SET_X,
    RUN_X,
    GET_X,
    RUN_CHECK_X,
    CHECK_X,
    SET_Y,
    RUN_Y,
    GET_Y,
    CHECK_Y,
    SET_VALUES,
    GET_POT,
    RUN_POT
} TOUCH_STATES;

volatile TOUCH_STATES state = IDLE;

/*********************************************************************
 * Function: void TouchDetectPosition(void)
 ********************************************************************/
short TouchDetectPosition(void) {
    static short tempX, tempY;
    short temp;

    switch (state) {
        case IDLE:
            adcX = -1;
            adcY = -1;
#ifdef ADC_POT
            adcPot = 0;
#endif
            break;

        case SET_VALUES:
#ifdef RESISTIVETOUCH_MANUAL_SAMPLE_MODE
            TOUCH_ADC_START = 0; // stop sampling
#endif
            if (!TOUCH_ADC_DONE)
                break;

            if ((uint16_t) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD < (uint16_t) PLIB_ADC_ResultGetByIndex(0,0)) {
                adcX = -1;
                adcY = -1;
            } else {
                adcX = tempX;
                adcY = tempY;
            }
            // If the hardware supports an analog pot, if not skip it

            state = SET_X;
            return 1; // touch screen acquisition is done

        case SET_X:

            TOUCH_ADC_INPUT_SEL = ADC_XPOS;

            ResistiveTouchScreen_XPlus_Config_As_Input();
            ResistiveTouchScreen_YPlus_Config_As_Input();
            ResistiveTouchScreen_XMinus_Config_As_Input();
            ResistiveTouchScreen_YMinus_Drive_Low();
            ResistiveTouchScreen_YMinus_Config_As_Output();

#ifdef ADPCFG_YPOS
            ADPCFG_YPOS = RESISTIVETOUCH_DIGITAL; // set to digital pin
#endif
#ifdef ADPCFG_YPOS
            ADPCFG_XPOS = RESISTIVETOUCH_ANALOG; // set to analog pin
#endif

            TOUCH_ADC_START = 1; // run conversion
            state = CHECK_X;
            break;

        case CHECK_X:
        case CHECK_Y:
#ifdef RESISTIVETOUCH_MANUAL_SAMPLE_MODE
            TOUCH_ADC_START = 0; // stop sampling
#endif
            if (TOUCH_ADC_DONE == 0) {
                break;
            }

            if ((uint16_t) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD > (uint16_t) PLIB_ADC_ResultGetByIndex(0,0)) {
                if (state == CHECK_X) {
                    ResistiveTouchScreen_YPlus_Drive_High();
                    ResistiveTouchScreen_YPlus_Config_As_Output();
                    tempX = -1;
                    state = RUN_X;
                }
                else {
                    ResistiveTouchScreen_XPlus_Drive_High();
                    ResistiveTouchScreen_XPlus_Config_As_Output();
                    tempY = -1;
                    state = RUN_Y;
                }
            } else {
                adcX = -1;
                adcY = -1;

                state = SET_X;
                return 1; // touch screen acquisition is done
    
                break;
            }

        case RUN_X:
        case RUN_Y:
            TOUCH_ADC_START = 1;
            state = (state == RUN_X) ? GET_X : GET_Y;
            // no break needed here since the next state is either GET_X or GET_Y
            break;

        case GET_X:
        case GET_Y:
#ifdef RESISTIVETOUCH_MANUAL_SAMPLE_MODE
            TOUCH_ADC_START = 0; // stop sampling
#endif
            if (!TOUCH_ADC_DONE)
                break;

            temp = PLIB_ADC_ResultGetByIndex(0,0);
            if (state == GET_X) {
                if (temp != tempX) {
                    tempX = temp;
                    state = RUN_X;
                    break;
                }
            } else {
                if (temp != tempY) {
                    tempY = temp;
                    state = RUN_Y;
                    break;
                }
            }

            if (state == GET_X)
                ResistiveTouchScreen_YPlus_Config_As_Input();
            else
                ResistiveTouchScreen_XPlus_Config_As_Input();
            TOUCH_ADC_START = 1;
            state = (state == GET_X) ? SET_Y : SET_VALUES;
            break;

        case SET_Y:
#ifdef RESISTIVETOUCH_MANUAL_SAMPLE_MODE
            TOUCH_ADC_START = 0; // stop sampling
#endif
            if (!TOUCH_ADC_DONE)
                break;

            if ((uint16_t) TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD < (uint16_t) PLIB_ADC_ResultGetByIndex(0,0)) {
                adcX = -1;
                adcY = -1;
                state = SET_X;
                return 1; // touch screen acquisition is done
                break;
            }

            TOUCH_ADC_INPUT_SEL = ADC_YPOS;

            ResistiveTouchScreen_XPlus_Config_As_Input();
            ResistiveTouchScreen_YPlus_Config_As_Input();
            ResistiveTouchScreen_XMinus_Drive_Low();
            ResistiveTouchScreen_XMinus_Config_As_Output();
            ResistiveTouchScreen_YMinus_Config_As_Input();

#ifdef ADPCFG_YPOS
            ADPCFG_YPOS = RESISTIVETOUCH_ANALOG; // set to analog pin
#endif
#ifdef ADPCFG_YPOS
            ADPCFG_XPOS = RESISTIVETOUCH_DIGITAL; // set to digital pin
#endif


            TOUCH_ADC_START = 1; // run conversion

            state = CHECK_Y;
            break;

        default:
            state = SET_X;
            return 1; // touch screen acquisition is done
    }

    return 0; // touch screen acquisition is not done
}

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
 * Overview: Initializes the A/D channel used for the touch detection.
 *
 * Note: none
 *
 ********************************************************************/
void Touch_ADCInit(void) {

    PLIB_ADC_Disable(0);
    PLIB_ADC_VoltageReferenceSelect(0, ADC_REFERENCE_VDD_TO_AVSS);
    PLIB_ADC_SamplingModeSelect(0, ADC_SAMPLING_MODE_MUXA);
    PLIB_ADC_SamplesPerInterruptSelect(0, ADC_1SAMPLE_PER_INTERRUPT);
    PLIB_ADC_SampleAcqusitionTimeSet(0, 31);
    PLIB_ADC_ConversionClockSet(0, 256, 80000000);
    PLIB_ADC_ConversionTriggerSourceSelect(0, ADC_CONVERSION_TRIGGER_INTERNAL_COUNT);
    PLIB_ADC_Enable(0);
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
void TouchHardwareInit(void *initValues) {
    Touch_ADCInit();

    // set the used D/A port to be analog
#ifdef ADPCFG_XPOS
    ADPCFG_XPOS = RESISTIVETOUCH_ANALOG;
#endif
#ifdef ADPCFG_YPOS
    ADPCFG_YPOS = RESISTIVETOUCH_ANALOG;
#endif   
#ifdef ADC_POT
    ADC_POT_PCFG = RESISTIVETOUCH_ANALOG;
#endif	

    PLIB_ADC_MuxAInputScanDisable(0);

    state = SET_X; // set the state of the statemachine to start the sampling

}

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
short TouchGetX(uint8_t touchNumber) {
    long result;

    result = TouchGetRawX();

    if (result >= 0) {
        result = (long) ((((long) _trC * result) + _trD) >> TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR);

#ifdef TOUCHSCREEN_RESISTIVE_FLIP_X
        result = GFX_MaxXGet() - result;
#endif	
    }
    return ((short) result);
}

/*********************************************************************
 * Function: short TouchGetRawX()
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
short TouchGetRawX(void) {
#ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcY;
#else
    return adcX;
#endif
}

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
short TouchGetY(uint8_t touchNumber) {

    long result;

    result = TouchGetRawY();

    if (result >= 0) {
        result = (long) ((((long) _trA * result) + (long) _trB) >> TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR);

#ifdef TOUCHSCREEN_RESISTIVE_FLIP_Y
        result = GFX_MaxYGet() - result;
#endif	
    }
    return ((short) result);
}

/*********************************************************************
 * Function: short TouchGetRawY()
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
short TouchGetRawY(void) {
#ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcX;
#else
    return adcY;
#endif
}

/*********************************************************************
 * Function: void TouchStoreCalibration(void)
 *
 * PreCondition: Non-volatile memory initialization function must be called before
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: stores calibration parameters into non-volatile memory
 *
 * Note: none
 *
 ********************************************************************/
void TouchStoreCalibration(void) {
    if (pCalDataWrite != NULL) {
        // the upper left X sample address is used since it is the first one
        // and this assumes that all stored values are located in one
        // sector
        if (pCalDataSectorErase != NULL)
            pCalDataSectorErase(ADDRESS_RESISTIVE_TOUCH_ULX);

        pCalDataWrite(xRawTouch[0], ADDRESS_RESISTIVE_TOUCH_ULX);
        pCalDataWrite(yRawTouch[0], ADDRESS_RESISTIVE_TOUCH_ULY);

        pCalDataWrite(xRawTouch[1], ADDRESS_RESISTIVE_TOUCH_URX);
        pCalDataWrite(yRawTouch[1], ADDRESS_RESISTIVE_TOUCH_URY);

        pCalDataWrite(xRawTouch[3], ADDRESS_RESISTIVE_TOUCH_LLX);
        pCalDataWrite(yRawTouch[3], ADDRESS_RESISTIVE_TOUCH_LLY);

        pCalDataWrite(xRawTouch[2], ADDRESS_RESISTIVE_TOUCH_LRX);
        pCalDataWrite(yRawTouch[2], ADDRESS_RESISTIVE_TOUCH_LRY);

        pCalDataWrite(mchpTouchScreenVersion, ADDRESS_RESISTIVE_TOUCH_VERSION);

    }

}

/*********************************************************************
 * Function: void TouchLoadCalibration(void)
 *
 * PreCondition: Non-volatile memory initialization function must be called before
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: loads calibration parameters from non-volatile memory
 *
 * Note: none
 *
 ********************************************************************/
void TouchLoadCalibration(void) {

    if (pCalDataRead != NULL) {

        xRawTouch[0] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_ULX);
        yRawTouch[0] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_ULY);

        xRawTouch[1] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_URX);
        yRawTouch[1] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_URY);

        xRawTouch[3] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_LLX);
        yRawTouch[3] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_LLY);

        xRawTouch[2] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_LRX);
        yRawTouch[2] = pCalDataRead(ADDRESS_RESISTIVE_TOUCH_LRY);

    }

    TouchCalculateCalPoints();

}

/*********************************************************************
 * Function: void TouchGetCalPoints(void)
 *
 * PreCondition: InitGraph() must be called before
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: gets values for 3 touches
 *
 * Note: none
 *
 ********************************************************************/
//void TouchCalculateCalPoints(uint16_t *xRawTouch, uint16_t *yRawTouch, uint16_t *xPoint, uint16_t *yPoint)

void TouchCalculateCalPoints(void) {
    long trA, trB, trC, trD; // variables for the coefficients
    long trAhold, trBhold, trChold, trDhold;
    long test1, test2; // temp variables (must be signed type)

    short xPoint[SAMPLE_POINTS], yPoint[SAMPLE_POINTS];

    yPoint[0] = yPoint[1] = CAL_Y_INSET;
    yPoint[2] = yPoint[3] = (GFX_MaxYGet() - CAL_Y_INSET);
    xPoint[0] = xPoint[3] = CAL_X_INSET;
    xPoint[1] = xPoint[2] = (GFX_MaxXGet() - CAL_X_INSET);

    // calculate points transfer functiona
    // based on two simultaneous equations solve for the
    // constants

    // use sample points 1 and 4
    // Dy1 = aTy1 + b; Dy4 = aTy4 + b
    // Dx1 = cTx1 + d; Dy4 = aTy4 + b

    test1 = (long) yPoint[0] - (long) yPoint[3];
    test2 = (long) yRawTouch[0] - (long) yRawTouch[3];

    trA = ((long) ((long) test1 * SCALE_FACTOR) / test2);
    trB = ((long) ((long) yPoint[0] * SCALE_FACTOR) - (trA * (long) yRawTouch[0]));

    test1 = (long) xPoint[0] - (long) xPoint[2];
    test2 = (long) xRawTouch[0] - (long) xRawTouch[2];

    trC = ((long) ((long) test1 * SCALE_FACTOR) / test2);
    trD = ((long) ((long) xPoint[0] * SCALE_FACTOR) - (trC * (long) xRawTouch[0]));

    trAhold = trA;
    trBhold = trB;
    trChold = trC;
    trDhold = trD;

    // use sample points 2 and 3
    // Dy2 = aTy2 + b; Dy3 = aTy3 + b
    // Dx2 = cTx2 + d; Dy3 = aTy3 + b

    test1 = (long) yPoint[1] - (long) yPoint[2];
    test2 = (long) yRawTouch[1] - (long) yRawTouch[2];

    trA = ((long) (test1 * SCALE_FACTOR) / test2);
    trB = ((long) ((long) yPoint[1] * SCALE_FACTOR) - (trA * (long) yRawTouch[1]));

    test1 = (long) xPoint[1] - (long) xPoint[3];
    test2 = (long) xRawTouch[1] - (long) xRawTouch[3];

    trC = ((long) ((long) test1 * SCALE_FACTOR) / test2);
    trD = ((long) ((long) xPoint[1] * SCALE_FACTOR) - (trC * (long) xRawTouch[1]));

    // get the average and use the average
    _trA = (trA + trAhold) >> 1;
    _trB = (trB + trBhold) >> 1;
    _trC = (trC + trChold) >> 1;
    _trD = (trD + trDhold) >> 1;

}

/*********************************************************************
 * Function: void TouchGetCalPoints(void)
 *
 * PreCondition: InitGraph() must be called before
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: gets values for 3 touches
 *
 * Note: none
 *
 ********************************************************************/
void TouchCalHWGetPoints(void) {
#define TOUCH_DIAMETER	10
#define SAMPLE_POINTS   4

    GFX_XCHAR calStr1[] = {'o', 'n', ' ', 't', 'h', 'e', ' ', 'f', 'i', 'l', 'l', 'e', 'd', 0};
    GFX_XCHAR calStr2[] = {'c', 'i', 'r', 'c', 'l', 'e', 0};
    GFX_XCHAR calTouchPress[] = {'P', 'r', 'e', 's', 's', ' ', '&', ' ', 'R', 'e', 'l', 'e', 'a', 's', 'e', 0};

    GFX_XCHAR calRetryPress[] = {'R', 'e', 't', 'r', 'y', 0};
    GFX_XCHAR *pMsgPointer;
    short counter;

    uint16_t dx[SAMPLE_POINTS], dy[SAMPLE_POINTS];
    uint16_t textHeight, msgX, msgY;
    short tempX, tempY;

    GFX_FontSet((void *) &GOLFontDefault);
    GFX_ColorSet(RESISTIVETOUCH_FOREGROUNDCOLOR);

    textHeight = GFX_TextStringHeightGet((void *) &GOLFontDefault);

//    while
//        (
//            GFX_TextStringXYPut
//            (
//            (GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) calStr1, (void *) &FONTDEFAULT)) >> 1,
//            (GFX_MaxYGet() >> 1),
//            GFX_MaxXGet(),
//            0,
//            (GFX_XCHAR *) calStr1
//            )==NULL
//            );
//
//    while
//        (
//            GFX_TextStringXYPut
//            (
//            (GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) calStr2, (void *) &FONTDEFAULT)) >> 1,
//            ((GFX_MaxYGet() >> 1) + textHeight),
//            GFX_MaxXGet(),
//            0,
//            (GFX_XCHAR *) calStr2
//            )==NULL
//            );

    // calculate center points (locate them at 15% away from the corners)
    // draw the four touch points

    dy[0] = dy[1] = CAL_Y_INSET;
    dy[2] = dy[3] = (GFX_MaxYGet() - CAL_Y_INSET);
    dx[0] = dx[3] = CAL_X_INSET;
    dx[1] = dx[2] = (GFX_MaxXGet() - CAL_X_INSET);


    msgY = ((GFX_MaxYGet() >> 1) - textHeight);
    pMsgPointer = calTouchPress;

    // get the four samples or calibration points
    for (counter = 0; counter < SAMPLE_POINTS;) {

        // redraw the filled circle to unfilled (previous calibration point)
        if (counter > 0) {
            GFX_ColorSet( RESISTIVETOUCH_BACKGROUNDCOLOR);
            while ((GFX_CircleFillDraw( dx[counter - 1], dy[counter - 1], TOUCH_DIAMETER - 3)==NULL));
        }

        // draw the new filled circle (new calibration point)
        GFX_ColorSet( RESISTIVETOUCH_FOREGROUNDCOLOR);
        while ((GFX_CircleDraw( dx[counter], dy[counter], TOUCH_DIAMETER)==NULL));
        while ((GFX_CircleFillDraw( dx[counter], dy[counter], TOUCH_DIAMETER - 3)==NULL));

        // show points left message
        msgX = (GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) pMsgPointer, (void *) &GOLFontDefault)) >> 1;
        TouchShowMessage( pMsgPointer, RESISTIVETOUCH_FOREGROUNDCOLOR, msgX, msgY, 0, 0);

        // Wait for press
        do {
        } while ((TouchGetRawX() == -1) && (TouchGetRawY() == -1));

        tempX = TouchGetRawX();
        tempY = TouchGetRawY();

        // wait for release
        do {
        } while ((TouchGetRawX() != -1) && (TouchGetRawY() != -1));

        // check if the touch was detected properly
        if ((tempX == -1) || (tempY == -1)) {
            // cannot proceed retry the touch, display RETRY PRESS message 

            // remove the previous string
            TouchShowMessage( pMsgPointer, RESISTIVETOUCH_BACKGROUNDCOLOR, msgX, msgY, 0, 0);
            pMsgPointer = calRetryPress;
            // show the retry message
            msgX = (GFX_MaxXGet() - GFX_TextStringWidthGet((GFX_XCHAR *) pMsgPointer, (void *) &GOLFontDefault)) >> 1;
            TouchShowMessage( pMsgPointer, RESISTIVETOUCH_FOREGROUNDCOLOR, msgX, msgY, 0, 0);
        } else {

            // remove the previous string
            TouchShowMessage( pMsgPointer, RESISTIVETOUCH_BACKGROUNDCOLOR, msgX, msgY, 0, 0);
            pMsgPointer = calTouchPress;



#ifdef TOUCHSCREEN_RESISTIVE_FLIP_Y
            yRawTouch[3 - counter] = tempY; //TouchGetRawY();
#else
            yRawTouch[counter] = tempY; //ouchGetRawY();
#endif

#ifdef TOUCHSCREEN_RESISTIVE_FLIP_X
            xRawTouch[3 - counter] = tempX; //TouchGetRawX();
#else
            xRawTouch[counter] = tempX; //TouchGetRawX();
#endif

            counter++;

        }

        // Wait for release
        do {
        } while ((TouchGetRawX() != -1) && (TouchGetRawY() != -1));

        SYS_TMR_DelayMS(CALIBRATION_DELAY);

    }

    TouchCalculateCalPoints();

#ifdef ENABLE_DEBUG_TOUCHSCREEN
    TouchScreenResistiveTestXY();
#endif
}


/*********************************************************************
 * Function: void TouchScreenResistiveTestXY(void)
 *
 * PreCondition: TouchHardwareInit has been called
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: prints raw x,y calibrated x,y and calibration factors to screen
 *
 * Note: modify pre-processor macro to include/exclude this test code
 *       a common place to call this from is at the end of TouchCalHWGetPoints()
 *
 ********************************************************************/
#ifdef ENABLE_DEBUG_TOUCHSCREEN
#include <stdio.h>

void TouchScreenResistiveTestXY(void) {
#define BUFFCHARLEN 60
    char buffChar[BUFFCHARLEN];
    uint16_t buffCharW[BUFFCHARLEN];
    unsigned char i;
    short tempXX, tempYY, tempXX2, tempYY2, calXX, calYY;
    tempXX = tempYY = -1;
    tempXX2 = tempYY2 = 0;

    // store the last calibration
    TouchStoreCalibration();

    while (1) {

        // use this to always show the values even if not pressing the screen
        //        tempXX = TouchGetRawX();
        //        tempYY = TouchGetRawY();

        calXX = TouchGetX(0);
        calYY = TouchGetY(0);

        if ((tempXX != tempXX2) || (tempYY != tempYY2)) {
            GFX_ColorSet( RESISTIVETOUCH_BACKGROUNDCOLOR);
            while (GFX_PRIM_ScreenClear() == NULL);
            GFX_ColorSet( RESISTIVETOUCH_FOREGROUNDCOLOR);
            sprintf(buffChar, "raw_x=%d, raw_y=%d", (uint16_t) tempXX, (uint16_t) tempYY);

#ifdef USE_MULTIBYTECHAR
            for (i = 0; i < BUFFCHARLEN; i++) {
                buffCharW[i] = buffChar[i];
            }
            while (!OutTextXY(0, 0, (GFX_XCHAR*) buffCharW));
#else
            while (!OutTextXY(0, 0, (GFX_XCHAR*) buffChar));
#endif

            sprintf(buffChar, "cal_x=%d, cal_y=%d", (uint16_t) calXX, (uint16_t) calYY);
#ifdef USE_MULTIBYTECHAR
            for (i = 0; i < BUFFCHARLEN; i++) {
                buffCharW[i] = buffChar[i];
            }
            while (!OutTextXY(0, 40, (GFX_XCHAR*) buffCharW));
#else
            while (!OutTextXY(0, 40, (GFX_XCHAR*) buffChar));
#endif

            sprintf(buffChar, "_tr:A=%d,B=%d", (uint16_t) _trA, (uint16_t) _trB);
#ifdef USE_MULTIBYTECHAR
            for (i = 0; i < BUFFCHARLEN; i++) {
                buffCharW[i] = buffChar[i];
            }
            while (!OutTextXY(0, 80, (GFX_XCHAR*) buffCharW));
#else
            while (!OutTextXY(0, 80, (GFX_XCHAR*) buffChar));
#endif

            sprintf(buffChar, "_tr:C=%d,D=%d", (uint16_t) _trC, (uint16_t) _trD);
#ifdef USE_MULTIBYTECHAR
            for (i = 0; i < BUFFCHARLEN; i++) {
                buffCharW[i] = buffChar[i];
            }
            while (!OutTextXY(0, 100, (GFX_XCHAR*) buffCharW));
#else
            while (!OutTextXY(0, 100, (GFX_XCHAR*) buffChar));
#endif


        }

        tempXX2 = tempXX;
        tempYY2 = tempYY;

        do {
            tempXX = TouchGetRawX();
            tempYY = TouchGetRawY();
        } while ((tempXX == -1) && (tempYY == -1));
    }
}
#endif //#ifdef ENABLE_DEBUG_TOUCHSCREEN


#endif // #if defined (USE_TOUCHSCREEN_RESISTIVE)

