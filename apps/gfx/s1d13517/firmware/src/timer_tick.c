/*****************************************************************************
 * Microchip Graphics Library Demo Application
 * This program shows how to use the Graphics Objects Layer.
 *****************************************************************************
 * File Name:       main_screen.c
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

/*****************************************************************************
 * Section: Includes
 *****************************************************************************/
#include "app.h"

/*****************************************************************************
 * Section: Defines
 *****************************************************************************/
// for a system clock of 80 MHz
#define TIMER_TICK_PERIOD           (GetSystemClock()/300000)
#define __TIMER_TICK_ISR            __ISR( _TIMER_3_VECTOR)

#define TIMER_TICK_PRESCALER	    16
#define TimerTickInterrupt          _T3Interrupt
/*****************************************************************************
 * Section: Variables
 *****************************************************************************/
extern void TouchProcessTouch(void);
extern short TouchDetectPosition(void);
/*****************************************************************************
 * Section: Variables
 *****************************************************************************/
static uint32_t tickscaler;
volatile uint32_t tick = 0;

/*********************************************************************
* Function: void TickInit(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: sets tick timer
*
* Note: none
*
********************************************************************/
void TickInit(void)
{
    TMR3 = 0;
    T3CONbits.TCKPS = 3;
    PR3 = 50;						//(for approximately 100 us)
    IPC3bits.T3IP = 5;
    IFS0bits.T3IF = 0;  						//Clear flag
    IEC0bits.T3IE = 1;  						//Enable interrupt
    T3CONbits.TON = 1;

    TMR4 = 0;
    T4CONbits.TCKPS = 3;
    PR4 = 500;//TICK_PERIOD;						//(for approximately 100 us)
    IPC4bits.T4IP = 1;
    IFS0bits.T4IF = 0;  						//Clear flag
    IEC0bits.T4IE = 1;  						//Enable interrupt
    T4CONbits.TON = 1;

}
