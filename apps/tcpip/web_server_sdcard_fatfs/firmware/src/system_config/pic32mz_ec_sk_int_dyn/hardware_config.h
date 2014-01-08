/*******************************************************************************
Hardware specific definitions

  Summary:

  Description:
    - PIC32 Ethernet Starter Kit
    - PIC32MX795F512L
    - Internal 10/100 Ethernet MAC with National DP83848 10/100 PHY
*******************************************************************************/

/*******************************************************************************
File Name:  hardware_config.h
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include <xc.h>

// Define a macro describing this hardware set up (used in other files)
// PIC32 Ethernet Starter Kit (04-02146) with PIC32MX795F512L processor and National DP83848 10/100 PHY
#define PIC32_ENET_SK_DM320004


// Hardware IO pin mappings

// using the PIC32 internal MAC interface
#define TCPIP_IF_PIC32INT


// missing definition from the processor file
#define _ETH


// External SMSC 8720 PHY configuration
#define PHY_RMII                // external PHY runs in RMII mode
#define PHY_CONFIG_DEFAULT  // alternate configuration used
//#define PHY_WOL_ENABLE       // This is enabled only when WOL functionality is required

// just for 144 pin device, RMII
#define _ETH_MDC_PORT   IOPORT_D
#define  _ETH_MDC_BIT   BIT_11

#define _ETH_MDIO_PORT  IOPORT_J
#define  _ETH_MDIO_BIT  BIT_1

#define _ETH_TXEN_PORT  IOPORT_D
#define  _ETH_TXEN_BIT  BIT_6

#define _ETH_TXD0_PORT  IOPORT_J
#define  _ETH_TXD0_BIT  BIT_8

#define _ETH_TXD1_PORT  IOPORT_J
#define  _ETH_TXD1_BIT  BIT_9

#define _ETH_RXCLK_PORT IOPORT_J
#define  _ETH_RXCLK_BIT BIT_11

#define _ETH_RXDV_PORT  IOPORT_H
#define  _ETH_RXDV_BIT  BIT_13

#define _ETH_RXD0_PORT  IOPORT_H
#define  _ETH_RXD0_BIT  BIT_8

#define _ETH_RXD1_PORT  IOPORT_H
#define  _ETH_RXD1_BIT  BIT_5

#define _ETH_RXERR_PORT IOPORT_H
#define  _ETH_RXERR_BIT BIT_4



// Hardware I/O pin mappings
// LEDs
#define LED0_TRIS           (TRISHbits.TRISH0)  // Ref LED1
#define LED0_IO             (LATHbits.LATH0)
#define LED1_TRIS           (TRISHbits.TRISH1)  // Ref LED2
#define LED1_IO             (LATHbits.LATH1)
#define LED2_TRIS           (TRISHbits.TRISH2)  // Ref LED3
#define LED2_IO             (LATHbits.LATH2)
#define LED3_TRIS           (TRISBbits.TRISB12)  // Ref LED3
#define LED3_IO             (PORTBbits.RB12)
#define LED4_TRIS           (TRISBbits.TRISB12)  // Ref LED3
#define LED4_IO             (PORTBbits.RB12)
#define LED5_TRIS           (TRISBbits.TRISB12)  // Ref LED3
#define LED5_IO             (PORTBbits.RB12)
#define LED6_TRIS           (TRISBbits.TRISB12)  // Ref LED3
#define LED6_IO             (PORTBbits.RB12)
#define LED7_TRIS           (TRISBbits.TRISB12)  // Ref LED3
#define LED7_IO             (PORTBbits.RB12)

#define LED_GET()           ((uint8_t)LATH & 0x07)
#define LED_PUT(a)          do{LATH = (LATH & 0xFFF8) | ((a)&0x07);}while(0)

// Momentary push buttons
#define BUTTON0_TRIS        (TRISBbits.TRISB12)  // Ref SW1
#define BUTTON0_IO          (PORTBbits.RB12)
#define BUTTON1_TRIS        (TRISBbits.TRISB13)  // Ref SW2
#define BUTTON1_IO          (PORTBbits.RB13)
#define BUTTON2_TRIS        (TRISBbits.TRISB14) // Ref SW3
#define BUTTON2_IO          (PORTBbits.RB14)
#define BUTTON3_TRIS        (TRISBbits.TRISB14) // Ref SW3
#define BUTTON3_IO          (1)

#include "system_config.h"

// define what type of storage we use
#define MEDIA_STORAGE_INTERNAL_FLASH


#endif // #ifndef HARDWARE_PROFILE_H

