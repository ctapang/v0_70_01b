/*******************************************************************************
Microchip TCP/IP Stack Network Configuration Header

  Summary:

  Description:

*******************************************************************************/

/*******************************************************************************
File Name:	network_config.h
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

#ifndef __NETWORK_PROFILE_H_
#define __NETWORK_PROFILE_H_


// =======================================================================
//   Network Interfaces Configuration Options
// =======================================================================

// Defalut values
// These values are used only if the application doesn't supply
// run time parameters for the TCPIP stack!

// the default number of interfaces
// Always 1 if no runtime parameter is supplied!
#define TCPIP_NETWORK_DEFAULT_INTERFACES_NO      1

// default values for the default interface
// Adjust them as needed.
#define TCPIP_NETWORK_DEFAULT_INTERFACE_NAME    "PIC32INT"
#define TCPIP_NETWORK_DEFAULT_HOST_NAME         "MCHPBOARD_E"
#define TCPIP_NETWORK_DEFAULT_MAC_ADDR          0
#define TCPIP_NETWORK_DEFAULT_IP_ADDRESS        "192.168.100.115"
#define TCPIP_NETWORK_DEFAULT_IP_MASK           "255.255.255.0"
#define TCPIP_NETWORK_DEFAULT_GATEWAY           "192.168.100.1"
#define TCPIP_NETWORK_DEFAULT_DNS               "192.168.100.1"
#define TCPIP_NETWORK_DEFAULT_SECOND_DNS        "0.0.0.0"
#define TCPIP_NETWORK_DEFAULT_POWER_MODE        "full"
#define TCPIP_NETWORK_INTERFACE_FLAGS   (TCPIP_NETWORK_CONFIG_DHCP_CLIENT_ON | TCPIP_NETWORK_CONFIG_DNS_SERVER_AUTO)







#endif  // __NETWORK_PROFILE_H_

