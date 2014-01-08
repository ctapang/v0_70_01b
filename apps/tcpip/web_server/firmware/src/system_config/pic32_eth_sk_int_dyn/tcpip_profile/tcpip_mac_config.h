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

/*
 * Reference only: TCPIP_MODULE_MAC_PIC32INT module configuration structure
 *
typedef struct
{
    int             nTxDescriptors; // number of TX descriptors
    int             rxBuffSize;     // size of the corresponding RX buffer
    int             nRxDescriptors; // number of RX descriptors
    ETH_OPEN_FLAGS      ethFlags;   // flags to use for the ETH connection
    ETHPHY_CONFIG_FLAGS phyFlags;   // PHY configuration 
    int                 linkInitDelay;  // PHYs initialization delay (milliseconds)
                                        // for insuring that the PHY is ready to transmit data.
}TCPIP_MODULE_MAC_PIC32INT_CONFIG;
*/

// This is a template of how the TCPIP_MODULE_MAC_PIC32INT module
// should be initialized and the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const TCPIP_MODULE_MAC_PIC32INT_CONFIG macPIC32INTConfigData = 
{
    EMAC_TX_DESCRIPTORS,    // nTxDescriptors
    EMAC_RX_BUFF_SIZE,      // rxBuffSize
    EMAC_RX_DESCRIPTORS,    // nRxDescriptors
    ETH_OPEN_DEFAULT,       // ethFlags
    ETH_PHY_CFG_RMII | ETH_PHY_CFG_ALTERNATE,   // phyFlags
    500,                    // linkInitDelay
};
#else
extern const TCPIP_MODULE_MAC_PIC32INT_CONFIG macPIC32INTConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION




// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ60 - MAC Layer Options
//   If not using an external ENC28J60 MAC, ignore this section.
// =======================================================================

/*
 * Reference only: TCPIP_MODULE_MAC_ENCJ60 module configuration structure
 *
typedef struct
{
}TCPIP_MODULE_MAC_ENCJ60_CONFIG;
*/

// This is a template of how the TCPIP_MODULE_MAC_ENCJ60 module
// should be initialized and the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const TCPIP_MODULE_MAC_ENCJ60_CONFIG macENCJ60ConfigData = 
{
};
#else
extern const TCPIP_MODULE_MAC_ENCJ60_CONFIG macENCJ60ConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION

// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ600 - MAC Layer Options
//   If not using an external ENC24J600 MAC, ignore this section.
// =======================================================================

/*
 * Reference only: TCPIP_MODULE_MAC_ENCJ600 module configuration structure
 *
typedef struct
{
}TCPIP_MODULE_MAC_ENCJ600_CONFIG;
*/

// This is a template of how the TCPIP_MODULE_MAC_ENCJ600 module
// should be initialized and the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const TCPIP_MODULE_MAC_ENCJ600_CONFIG macENCJ600ConfigData = 
{
};
#else
extern const TCPIP_MODULE_MAC_ENCJ600_CONFIG macENCJ600ConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION



// =======================================================================
//   TCPIP_MODULE_MAC_97J60 - MAC Layer Options
//   If not using an external 97J60 MAC, ignore this section.
// =======================================================================

/*
 * Reference only: TCPIP_MODULE_MAC_97J60 module configuration structure
 *
typedef struct
{
}TCPIP_MODULE_MAC_97J60_CONFIG;
*/

// This is a template of how the TCPIP_MODULE_MAC_97J60 module
// should be initialized and the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const TCPIP_MODULE_MAC_97J60_CONFIG mac97J60ConfigData = 
{
};
#else
extern const TCPIP_MODULE_MAC_97J60_CONFIG mac97J60ConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION


// =======================================================================
//   TCPIP_MODULE_MAC_MRF24W - MAC Layer Options
//   If not using an external MRF24W Wi-Fi MAC, ignore this section.
// =======================================================================

/*
 * Reference only: TCPIP_MODULE_MAC_MRF24W module configuration structure
 *
typedef struct
{
}TCPIP_MODULE_MAC_MRF24W_CONFIG;
*/

// This is a template of how the TCPIP_MODULE_MAC_MRF24W module
// should be initialized and the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const TCPIP_MODULE_MAC_MRF24W_CONFIG macMRF24WConfigData = 
{
};
#else
extern const TCPIP_MODULE_MAC_MRF24W_CONFIG macMRF24WConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION




#endif  // _MAC_CONFIG_H_


