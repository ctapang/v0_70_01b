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
Copyright � 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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
#define LED0_TRIS           (TRISDbits.TRISD0)  // Ref LED1
#define LED0_IO             (LATDbits.LATD0)
#define LED1_TRIS           (TRISDbits.TRISD1)  // Ref LED2
#define LED1_IO             (LATDbits.LATD1)
#define LED2_TRIS           (TRISDbits.TRISD2)  // Ref LED3
#define LED2_IO             (LATDbits.LATD2)
#define LED3_TRIS           (LED2_TRIS)         // No such LED
#define LED3_IO             (LATDbits.LATD6)
#define LED4_TRIS           (LED2_TRIS)         // No such LED
#define LED4_IO             (LATDbits.LATD6)
#define LED5_TRIS           (LED2_TRIS)         // No such LED
#define LED5_IO             (LATDbits.LATD6)
#define LED6_TRIS           (LED2_TRIS)         // No such LED
#define LED6_IO             (LATDbits.LATD6)
#define LED7_TRIS           (LED2_TRIS)         // No such LED
#define LED7_IO             (LATDbits.LATD6)

#define LED_GET()           ((uint8_t)LATD & 0x07)
#define LED_PUT(a)          do{LATD = (LATD & 0xFFF8) | ((a)&0x07);}while(0)

// Momentary push buttons
#define BUTTON0_TRIS        (TRISDbits.TRISD6)  // Ref SW1
#define BUTTON0_IO          (PORTDbits.RD6)
#define BUTTON1_TRIS        (TRISDbits.TRISD7)  // Ref SW2
#define BUTTON1_IO          (PORTDbits.RD7)
#define BUTTON2_TRIS        (TRISDbits.TRISD13) // Ref SW3
#define BUTTON2_IO          (PORTDbits.RD13)
#define BUTTON3_TRIS        (TRISDbits.TRISD13) // No BUTTON3 on this board
#define BUTTON3_IO          (1)

// Note, it is not possible to use a MRF24W 802.11 WiFi PICtail
// Plus card with this starter kit.  The required interrupt signal, among
// possibly other I/O pins aren't available on the Starter Kit board.

#include "system_config.h"

// define what type of storage we use
#define MEDIA_STORAGE_INTERNAL_FLASH
//----------------------------
// MRF24W WiFi I/O pins
//----------------------------
// If you have a MRF24W WiFi PICtail, you must uncomment one of 
// these two lines to use it.  SPI1 is the top-most slot in the Explorer 16 
// (closer to the LCD and prototyping area) while SPI2 corresponds to 
// insertion of the PICtail into the middle of the side edge connector slot.
// specify we want to use the MRF24W interface
#define MRF24W_IN_SPI1
//#define MRF24W_IN_SPI2

#if defined(TCPIP_IF_MRF24W)
        // Interrupt source selection
        //#define MRF24W_USE_CN_INT
        //#define MRF24W_USE_INT3_INT
         #define MRF24W_USE_INT1_INT

	#if defined (MRF24W_IN_SPI1)
		#define MRF24W_SPI_CHN   1   // 1 - SPI1, 2 - SPI2
        
		// IO mapping for general control pins, inlcuding CS, RESET and HIBERNATE  
        #if defined(__32MX795F512L__)
            // MRF24W in SPI1 slot
            #define WF_CS_TRIS                  (TRISBbits.TRISB2)
            #define WF_CS_IO                    (LATBbits.LATB2)
            #define WF_RESET_TRIS               (TRISFbits.TRISF0)
            #define WF_RESET_IO                 (LATFbits.LATF0)
            #define WF_HIBERNATE_TRIS           (TRISFbits.TRISF1)
            #define WF_HIBERNATE_IO             (PORTFbits.RF1)
        #elif defined (__32MZ2048ECH144__)
            // MRF24W in SPI1 slot
            #define WF_CS_TRIS                  (TRISEbits.TRISE9)
            #define WF_CS_IO                    (LATEbits.LATE9)
            #define WF_RESET_TRIS               (TRISFbits.TRISF0)
            #define WF_RESET_IO                 (LATFbits.LATF0)
            #define WF_HIBERNATE_TRIS           (TRISFbits.TRISF1)
            #define WF_HIBERNATE_IO             (PORTFbits.RF1)
        #endif // defined(__32MX460F512L__)

	#elif defined (MRF24W_IN_SPI2)
		#define MRF24W_SPI_CHN   2   // 1 - SPI1, 2 - SPI2
	#endif  // defined (MRF24W_IN_SPI1) || defined(MRF24W_IN_SPI2)

#endif  // defined(TCPIP_IF_MRF24W)


#endif // #ifndef HARDWARE_PROFILE_H

