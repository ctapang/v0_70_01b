/*******************************************************************************
 Board support configuration file.

 Company:      
    Microchip Technology Inc.

 File Name:   
    bsp_config.h

 Summary:      
    Board support configuration file.

 Description:
    This contains all the configuration that is required to be done for the 
    application running on PIC32 USB starter kit
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _BSP_CONFIG_H
#define _BSP_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Input Constant

  Summary:
    Defines the constant which identifies input

  Description:
    This constant identifies input
*/

#define BSP_INPUT                               1

// *****************************************************************************
/* Output Constant

  Summary:
    Defines the constant which identifies output

  Description:
    This constant identifies output
*/

#define BSP_OUTPUT                              0

// *****************************************************************************
/* Digital Pin Constant

  Summary:
    Defines the constant which identifies digital pin

  Description:
    This constant identifies digital pin
*/

#define BSP_DIGITAL_PIN                         PORTS_PIN_MODE_DIGITAL

// *****************************************************************************
/* analog Pin Constant

  Summary:
    Defines the constant which identifies analog pin

  Description:
    This constant identifies analog pin
*/

#define BSP_ANALOG_PIN                          PORTS_PIN_MODE_ANALOG


// *****************************************************************************
/* BSP Switch.

  Summary:
    Holds Switch numbers.

  Description:
    This enumeration defines the Switch numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* SWITCH 1 */
     SWITCH_1 = 12,

    /* SWITCH 2 */
     SWITCH_2 = 13,

    /* SWITCH 3 */
     SWITCH_3 = 14

}BSP_SWITCH;


// *****************************************************************************
/* BSP Switch state.

  Summary:
    Holds Switch status.

  Description:
    This enumeration defines the switch state.

  Remarks:
    None.
*/

typedef enum
{
    /* Switch pressed */
    BSP_SWITCH_STATE_PRESSED = 0,

   /* Switch not pressed */
    BSP_SWITCH_STATE_RELEASED = 1
}BSP_SWITCH_STATE;


// *****************************************************************************
/* LED Number.

  Summary:
    Holds LED numbers.

  Description:
    This enumeration defines the LED numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* LED 1 on SK */
    LED_1 = 0,

    /* LED 3 on SK */
    LED_2 = 1,

    /* LED 2 on SK */
    LED_3 = 2,
}BSP_LED;


// *****************************************************************************
// *****************************************************************************
// Section: UART Pins
// *****************************************************************************
// *****************************************************************************
/* The section below identifies the pins that are associated with the UART
   connected to RS232 on the board */


// *****************************************************************************
// *****************************************************************************
// Section: Analog Inputs Connected Potentiometer
// *****************************************************************************
// *****************************************************************************
/* The section below identifies the analog inputs connected to potentiometer */


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board
*/

void BSP_Initialize(void);

// *****************************************************************************
/* Function: void BSP_SwitchONLED(BSP_LED led)

  Summary:
    Switches ON the onboard LED.

  Description:
    This routine switches ON the onboard LED.
*/

void BSP_SwitchONLED(BSP_LED led);

// *****************************************************************************
/* Function: void BSP_SwitchOFFLED(BSP_LED led)

  Summary:
    Switches OFF the onboard LED.

  Description:
    This routine switches OFF the onboard LED.
*/

void BSP_SwitchOFFLED(BSP_LED led);


// *****************************************************************************
/* Function: unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)

  Summary:
    Configures the system cache and flash wait states for maximum performance

  Description:
    Configures the system cache and flash wait states for maximum performance.
*/

unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);


// *****************************************************************************
/* Function: bool BSP_ReadSwitch(uint8_t bspSwitch)

  Summary:
    Reads the switch status.Returns true, if switch is pressed.

  Description:
    Reads the switch status passed as parameter, bspSwitch.
*/

BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch);


// *****************************************************************************
/* Function: void BSP_ToggleLED(BSP_LED led)

  Summary:
    Toggles the LED on board.

  Description:
    
*/

void BSP_ToggleLED(BSP_LED led);

// *****************************************************************************
/* Function: uint32_t BSP_ReadCoreTimer()

  Summary:
    Returns the current core timer value..

  Description:

*/

uint32_t BSP_ReadCoreTimer();

// *****************************************************************************
/* Function: void BSP_VBUSSwitchEnable(void)

  Summary:
    Enables the VBUS switch.

  Description:

*/

void BSP_VBUSSwitchEnable(void);


#endif //_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
