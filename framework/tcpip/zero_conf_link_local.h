/*******************************************************************************
  Zero Configuration (Zeroconf) IPV4 Link Local Addressing Module for the Microchip 
  TCP/IP Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
   zero_conf_link_local.h

  Summary:
    Zero configuration (Zeroconf), provides a mechanism to ease the configuration 
    of a device on a network.
    
  Description:
    Zero configuration (Zeroconf), provides a mechanism to ease the configuration
    of a device on a network. It also provides for a more human-like naming 
    convention, instead of relying on IP addresses alone. Zeroconf also goes 
    by the names Bonjour (Apple) and Avahi (Linux), and is an IETF standard.
*******************************************************************************/
//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END
#ifndef __ZEROCONF_LINK_LOCAL_H
#define __ZEROCONF_LINK_LOCAL_H


// Placeholder for Zero Configuration Link Layer module configuration.
typedef struct
{
}ZCLL_MODULE_CONFIG;

// ZCLL API
//

// enables ZCLL on an interface
bool    TCPIP_ZCLL_Enable(TCPIP_NET_HANDLE hNet);

// disables the ZCLL on an interface
bool    TCPIP_ZCLL_Disable(TCPIP_NET_HANDLE hNet);

// returns true if ZCLL is currently enabled on that interface
bool    TCPIP_ZCLL_IsEnabled(TCPIP_NET_HANDLE hNet);


#endif //#ifndef __ZEROCONF_LINK_LOCAL_H

