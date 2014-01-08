/*******************************************************************************
 System Initialization File

  File Name:
    tcpip_stack_config.h

  Summary:
    TCP/IP Stack Configuration.

  Description:
    This file contains includes necessary for the TCP/IP stack
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef _TCPIP_STACK_CONFIG_H_
#define _TCPIP_STACK_CONFIG_H_

#include "tcpip_config.h"
#include "tcpip/tcpip.h"


// Arp Configuration
#if defined(TCPIP_STACK_USE_ANNOUNCE)
#include "tcpip_announce_config.h"
#endif

#include "arp_config.h"


#if defined(TCPIP_STACK_USE_BERKELEY_API)
#include "berkeley_api_config.h"
#endif


#if defined(TCPIP_STACK_USE_DHCP_SERVER)
#include "dhcps_config.h"
#endif

#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
#include "dhcp_config.h"
#endif

#if defined(TCPIP_STACK_USE_DNS_SERVER)
#include "dnss_config.h"
#endif

#if defined(TCPIP_STACK_USE_DNS)
#include "dns_config.h"
#endif

#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
#include "ddns_config.h"
#endif


#if defined(TCPIP_STACK_USE_FTP_SERVER)
#include "ftp_config.h"

#endif

#if defined(TCPIP_STACK_USE_HTTP_SERVER)
#include "http_config.h"
#endif

#if defined(TCPIP_STACK_USE_IPV6)
#include "icmpv6_config.h"
#include "ndp_config.h"
#include "ipv6_config.h"
#endif

#if defined(TCPIP_STACK_USE_ICMP_SERVER) || defined(TCPIP_STACK_USE_ICMP_CLIENT)
#include "icmp_config.h"
#endif

#include "iperf_config.h"

#include "ip_config.h"

//TCP/IP Mac config
#include "tcpip_mac_config.h"


#if defined(TCPIP_STACK_USE_NBNS)
#include "nbns_config.h"
#endif

#if defined(TCPIP_STACK_USE_REBOOT_SERVER)
#include "tcpip_reboot_config.h"
#endif

#if defined(TCPIP_STACK_USE_SMTP_CLIENT)
#include "smtp_config.h"
#endif

#if defined(TCPIP_STACK_USE_SNMPV3_SERVER)
#include "snmpv3_config.h"
#endif

#if defined(TCPIP_STACK_USE_SNMP_SERVER)
#include "snmp_config.h"
#endif

#if defined(TCPIP_STACK_USE_SNTP_CLIENT)
#include "sntp_config.h"
#endif

#if defined(TCPIP_STACK_USE_SSL_SERVER) || defined(TCPIP_STACK_USE_SSL_CLIENT)
#include "ssl_config.h"
#endif


#if defined(TCPIP_STACK_USE_TCP)
#include "tcp_config.h"
#endif

#if defined(TCPIP_STACK_USE_TELNET_SERVER)
#include "telnet_config.h"
#endif

#if defined(TCPIP_STACK_USE_TFTP_CLIENT)
#include "tftpc_config.h"
#endif


#if defined(TCPIP_STACK_USE_UDP)
#include "udp_config.h"
#endif

#include "network_config.h"


#endif