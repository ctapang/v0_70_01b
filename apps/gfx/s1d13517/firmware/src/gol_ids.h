/*****************************************************************************
 * File Name:       ID.h
 * Dependencies:    See Includes Section
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30 V3.00, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
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
 *
 *****************************************************************************/
#ifndef ID_H
#define ID_H

typedef enum
{
    MAIN_SCREEN_ID_COMFORT_BUT = 10,
    MAIN_SCREEN_ID_SLIDE_SHOW_BUT,
    MAIN_SCREEN_ID_SPEED_BUT,
    MAIN_SCREEN_ID_GRADIENT_BUT,
    MAIN_SCREEN_ID_INFO_BUT,
    MAIN_SCREEN_ID_ALPHA_BUT,
    MAIN_SCREEN_ID_ANALOG_CLOCK,

    INFO_SCREEN_ID_STATIC_TXT,

    COMFORT_SCREEN_ID_LEVEL_STATIC_TXT,
    COMFORT_SCREEN_ID_LEVEL_TEMP_STATIC_TXT,
    COMFORT_SCREEN_ID_COOL_STATIC_TXT,
    COMFORT_SCREEN_ID_HEAT_STATIC_TXT,
    COMFORT_SCREEN_ID_LEFT_ARROW_BUT,
    COMFORT_SCREEN_ID_RIGHT_ARROW_BUT,
    COMFORT_SCREEN_ID_AUTO_BUT,
    COMFORT_SCREEN_ID_HEAT_BUT,
    COMFORT_SCREEN_ID_OFF_BUT,
    COMFORT_SCREEN_ID_COOL_BUT,
    COMFORT_SCREEN_ID_SYSTEM_MODE_GROUP_BOX,
    COMFORT_SCREEN_ID_FAN_MODE_GROUP_BOX,
    COMFORT_SCREEN_ID_FAN_ON_BUT,
    COMFORT_SCREEN_ID_FAN_AUTO_BUT,
    COMFORT_SCREEN_ID_COOL_MINUS_BUT,
    COMFORT_SCREEN_ID_HEAT_MINUS_BUT,
    COMFORT_SCREEN_ID_COOL_PLUS_BUT,
    COMFORT_SCREEN_ID_HEAT_PLUS_BUT,

}GOL_IDS;

#endif
