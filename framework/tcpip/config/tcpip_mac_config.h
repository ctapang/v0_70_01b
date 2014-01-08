/*******************************************************************************
  MAC Configuration file

  Summary:
    configuration file
    
  Description:
    This file contains the MAC module configuration options
    
*******************************************************************************/

/*******************************************************************************
File Name:  tcpip_mac_config.h
Copyright © 2011 released Microchip Technology Inc.  All rights
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

#ifndef _MAC_CONFIG_H_
#define _MAC_CONFIG_H_

// =======================================================================
//   TCPIP_MODULE_MAC_PIC32INT - PIC32MX7XX/6XX MAC Layer Options
//   If not using a PIC32MX7XX/6XX device with internal MAC, ignore this section.
// =======================================================================

// set to 1 if you need to config the link to specific following parameters
// otherwise the default connection will be attempted
// depending on the selected PHY
#define	ETH_CFG_LINK		0		

// use auto negotiation
#define	ETH_CFG_AUTO		1

// use/advertise 10 Mbps capability
#define	ETH_CFG_10		1

// use/advertise 100 Mbps capability
#define	ETH_CFG_100		1

// use/advertise half duplex capability
#define	ETH_CFG_HDUPLEX		1

// use/advertise full duplex capability
#define	ETH_CFG_FDUPLEX		1

// use/advertise auto MDIX capability
#define	ETH_CFG_AUTO_MDIX	1

// use swapped MDIX. else normal MDIX
#define	ETH_CFG_SWAP_MDIX	1

// some PHYs need an initialization delay for
// insuring that the PHY is ready to transmit data.
// milliseconds
#define ETH_CFG_LINK_INIT_DELAY   500


// MAC Configuration parameters
// Note: These values are used as defaults
// The actual values passed in at initialization time
// take precedence!

// number of the TX descriptors to be created
#define EMAC_TX_DESCRIPTORS	8

// number of the RX descriptors and RX buffers to be created
#define EMAC_RX_DESCRIPTORS	6

// size of a RX buffer. should be multiple of 16
// this is the size of all receive buffers processed by the ETHC
// The size should be enough to accomodate any network received packet
// If the packets are larger, they will have to take multiple RX buffers
// and the packet manipulation is less efficient
//#define	EMAC_RX_BUFF_SIZE	512
#define	EMAC_RX_BUFF_SIZE	1536

// Maximum MAC supported RX frame size.
// Any incoming ETH frame that's longer than this size
// will be discarded.
// The default value is 1536
// (allows for VLAN tagged frames, although the VLAN
// tagged frames are discarded)
// Normally you shouldn't need to touch this value
// unless you know exactly the maximum size of the 
// frames you want to process or you need to control
// packets fragmentation (together with the EMAC_RX_BUFF_SIZE.
// Note: Always multiple of 16!
#define EMAC_RX_MAX_FRAME   1536


// MAC maximum number of supported fragments
// Based on the values of EMAC_RX_MAX_FRAME and EMAC_RX_BUFF_SIZE
// an incoming frame may span multiple RX buffers (fragments).
// Note that excessive fragmentation leads to performance degradation.
// The default and recommended value should be 1.
//#define EMAC_RX_FRAGMENTS      1
// Alternatively you can use the calculation of the
// number of fragments based on the selected RX sizes:
#define EMAC_RX_FRAGMENTS      ((EMAC_RX_MAX_FRAME + (EMAC_RX_BUFF_SIZE -1 )) / (EMAC_RX_BUFF_SIZE))




// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ60 - MAC Layer Options
//   If not using an external ENC28J60 MAC, ignore this section.
// =======================================================================


// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ600 - MAC Layer Options
//   If not using an external ENC24J600 MAC, ignore this section.
// =======================================================================


// =======================================================================
//   TCPIP_MODULE_MAC_97J60 - MAC Layer Options
//   If not using an external 97J60 MAC, ignore this section.
// =======================================================================



// =======================================================================
//   TCPIP_MODULE_MAC_MRF24W - MAC Layer Options
//   If not using an external MRF24W Wi-Fi MAC, ignore this section.
// =======================================================================



#endif  // _MAC_CONFIG_H_


