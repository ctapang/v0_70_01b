/*******************************************************************************
  Clock System Service Configuration Templates

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk_config_template.h

  Summary:
    Clock System Service configuration templates.

  Description:
    This file contains constants to configure the Clock System Service.
*******************************************************************************/

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

#ifndef _SYS_OSC_CONFIG_TEMPLATE_H
#define _SYS_OSC_CONFIG_TEMPLATE_H

// *****************************************************************************
/* Primary Oscillator clock frequency

  Summary:
    Sets up the Primary Oscillator clock frequency.

  Description:
    This macro sets up the Primary Oscillator clock frequency.

  Remarks:
    None.
*/

#define SYS_CLK_PRIMARY_CLOCK                                       8000000L


// *****************************************************************************
/* Secondary Oscillator clock frequency

  Summary:
    Sets up the Secondary Oscillator clock frequency.

  Description:
    This macro sets up the Secondary Oscillator clock frequency.

  Remarks:
    None.
*/

#define SYS_CLK_SECONDARY_CLOCK                                         8000000


// *****************************************************************************
/* Primary Oscillator stop in Sdle configuration

  Summary:
    Sets up the Primary Oscillator Stop in Idle feature.

  Description:
    This macro sets up the Primary Oscillator Stop in Idle feature:
    - true  - The Primary Oscillator stops when the device enters Idle mode
    - false - The Primary Oscillator continues operation when the device enters Idle mode

  Remarks:
    None.
*/

#define SYS_CLK_PRIMARY_STOP_IN_IDLE           				true


// *****************************************************************************
/* Primary Oscillator suspend in Sleep configuration

  Summary:
    Sets up the Primary Oscillator Stop in Idle feature.

  Description:
    This macro sets up the Primary Oscillator Stop in Idle feature:
    - true  - The Primary Oscillator is suspended when the device enters Sleep mode
    - false - The Primary Oscillator continues operation when the device enters Sleep mode

  Remarks:
    None.
*/

#define SYS_CLK_PRIMARY_SUSPEND_IN_SLEEP                                true


// *****************************************************************************
/* Oscillator on wait operation Sleep mode configuration

  Summary:
    Sets Oscillator operation to go to Sleep mode upon a WAIT instruction.

  Description:
    This macro sets Oscillator operation to go to Sleep mode upon a WAIT instruction.

  Remarks:
    None.
*/

#define SYS_CLK_ON_WAIT_SLEEP                                           0


// *****************************************************************************
/* Oscillator on wait operation Idle mode configuration

  Summary:
    Sets Oscillator operation to go to Idle mode upon a WAIT instruction.

  Description:
    This macro sets Oscillator operation to go to Idle mode upon a WAIT instruction.

  Remarks:
    None.
*/

#define SYS_CLK_ON_WAIT_IDLE											1


// *****************************************************************************
/* System clock PLL enable configuration

  Summary:
    Defines the status of the USB PLL.

  Description:
    Setting this macro to 'true' states that USB PLL is enabled through
    the Configuration bits.

  Remarks:
    None.
*/

#define SYS_CLK_CONFIG_USBPLL_ENABLE                                    true


// *****************************************************************************
/* System clock output divisor configured through configuration bits

  Summary:
    Sets up the Oscillator System Clock output divisor.

  Description:
    This macro sets up the Oscillator System Clock output divisor.

  Remarks:
    This should be configured through Configuration bits.
*/

#define SYS_CLK_CONFIG_SYSCLK_OP_DIVISOR								1


// *****************************************************************************
/* Oscillator System clock input divisor configured through configuration bits

  Summary:
    Sets up the Oscillator System Clock input divisor.

  Description:
    This macro sets up the scillator System Clock input divisor.

  Remarks:
    This should be configured through Configuration bits.
*/

#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR                               2


// *****************************************************************************
/* Oscillator USB clock divisor configured through configuration bits

  Summary:
    Sets up the Oscillator USB clock divisor.

  Description:
    This macro sets up the Oscillator USB clock divisor. Use OSC_CONFIGBITS_PLLIDIV 
    to select the configuration.

  Remarks:
    This should be configured through Configuration bits.
*/

#define SYS_CLK_CONFIG_USBPLL_DIVISOR								2


// *****************************************************************************
/* Frequency Configuration error percentage

  Summary:
    Sets the allowed frequency configuration error percentage.

  Description:
    This macro sets the allowed frequency error percentage.

  Remarks:
    None.
*/

#define SYS_CLK_CLOCK_CONFIG_ERROR                                  10


// *****************************************************************************
/* External clock frequency

  Summary:
    Sets the clock that is provided on the REFCLKI pin.

  Description:
    This macro sets the clock that is provided on the REFCLKI pin.

  Remarks:
    None.
*/

#define SYS_CLK_EXTERNAL_CLOCK				          4000000




// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************




#endif //_SYS_OSC_CONFIG_TEMPLATE_H

/*******************************************************************************
 End of File
*/

