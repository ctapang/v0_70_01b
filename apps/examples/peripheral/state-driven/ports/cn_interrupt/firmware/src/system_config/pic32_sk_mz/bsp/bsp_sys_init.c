/*******************************************************************************
 Board initialization file for PIC32 USB starter kit

 Company:
    Microchip Technology Inc.

 File Name:
    bsp_sys_init.c

 Summary:
    Board initialization file for PIC32 USB starter kit

 Description:
    This file contains the initialization of board specific I/O.
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

#if defined(cfg_pic32_sk_mz)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "peripheral/peripheral.h"


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board

  Remarks:
    This routine performs direct register accesses, when the PORTS PLIB and
    system service become available, these register accesses will be be replaced
    by the PLIB\system service interfaces.

*/

void BSP_Initialize(void )
{
    /* set the switch pins as input */
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB13 = 1;
    TRISBbits.TRISB14 = 1;

    ANSELBbits.ANSB12 = 0;
    ANSELBbits.ANSB13 = 0;
    ANSELBbits.ANSB14 = 0;

    /* Enable weak pullups on switch pins */
    CNPUBbits.CNPUB12 = 1;
    CNPUBbits.CNPUB13 = 1;
    CNPUBbits.CNPUB14 = 1;
    
  /*
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_H, LED_1 );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_H, LED_2 );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_H, LED_3 );

    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_H, LED_1 );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_H, LED_2 );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_H, LED_3 ); */


    TRISHbits.TRISH0 = 0;
    TRISHbits.TRISH1 = 0;
    TRISHbits.TRISH2 = 0;

    LATHbits.LATH0 = 0;
    LATHbits.LATH1 = 0;
    LATHbits.LATH2 = 0;
}

void BSP_SwitchONLED(BSP_LED led)
{

    /* switch ON the LED */
    /*PLIB_PORTS_PinWrite ( PORTS_ID_0 ,
                         PORT_CHANNEL_H ,
                         led,
                         1 ); */
    LATHSET = (1 << led);

}

void BSP_SwitchOFFLED(BSP_LED led)
{
    
    /* switch OFF the LED */
    /*PLIB_PORTS_PinWrite ( PORTS_ID_0 ,
                         PORT_CHANNEL_H ,
                         led,
                         0 ); */

    LATHCLR = (1 << led);
}

void BSP_ToggleLED(BSP_LED led)
{

   // PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H,led );
    LATHINV = (1 << led);
}



BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch )
{
    return ( PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, bspSwitch) );
}

uint32_t BSP_ReadCoreTimer()
{
    uint32_t timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}

void BSP_WriteCoreTimer( uint32_t timer )
{
    /* get the count reg */
    asm volatile("mtc0   %0, $9": "+r"(timer));
}


/******************************************************************************/
/******************************************************************************/

#endif //__32MZ2048ECH144__

/*******************************************************************************
 End of File
*/
