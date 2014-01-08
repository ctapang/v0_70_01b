/*******************************************************************************
 System Initialization File

  File Name:
    tcpip_stack_init.c

  Summary:
    TCP/IP Stack Initialization.

  Description:
    This file contains source code necessary to initialize the tcp/ip stack.
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

#include "tcpip_config.h"
#include "tcpip_stack_init.h"
#include "tcpip/tcpip.h"
#include "tcpip_stack_config.h"

// Arp Configuration
const ARP_MODULE_CONFIG arpConfigData =
{
    ARP_CACHE_ENTRIES_DEFAULT,
    true,
    ARP_CACHE_SOLVED_ENTRY_TMO,
    ARP_CACHE_PENDING_ENTRY_TMO,
    ARP_CACHE_PENDING_RETRY_TMO,
    ARP_CACHE_PERMANENT_QUOTA,
    ARP_CACHE_PURGE_THRESHOLD,
    ARP_CACHE_PURGE_QUANTA,
};


#if defined(TCPIP_STACK_USE_DHCP_SERVER)
const DHCPS_MODULE_CONFIG dhcpsConfigData =
{
    true,
    true,
    DHCPS_LEASE_ENTRIES_DEFAULT,
    DHCPS_LEASE_SOLVED_ENTRY_TMO,
    DHCPS_IP_ADDRESS_RANGE_START,
};
#endif

#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
const DHCP_MODULE_CONFIG dhcpConfigData =
{
    DHCP_CLIENT_ENABLED,
    DHCP_TIMEOUT,
    DHCP_CLIENT_PORT,
    DHCP_SERVER_PORT,
};
#endif



#if defined(TCPIP_STACK_USE_FTP_SERVER)
const FTP_MODULE_CONFIG ftpConfigData =
{
    TCPIP_FTP_DATA_SKT_TX_BUFF_SIZE,
    TCPIP_FTP_DATA_SKT_RX_BUFF_SIZE,
    "admin",
    "microchip",
};
#endif

#if defined(TCPIP_STACK_USE_HTTP_SERVER)
const HTTP_MODULE_CONFIG httpConfigData =
{
    HTTP_MAX_CONNECTIONS,
    HTTP_MAX_DATA_LEN,
    HTTP_SKT_TX_BUFF_SIZE,
    HTTP_SKT_RX_BUFF_SIZE,
    HTTP_CONFIG_FLAGS,

};
#endif

#if defined(TCPIP_STACK_USE_IPV6)
const IPV6_MODULE_CONFIG ipv6ConfigData =
{
    TCPIP_IPV6_RX_FRAGMENTED_BUFFER_SIZE,
    TCPIP_IPV6_FRAGMENT_PKT_TIMEOUT,
};
#endif



#if defined(TCPIP_STACK_USE_TCP)
const TCP_MODULE_CONFIG tcpConfigData =
{
    TCP_MAX_SOCKETS,
    TCP_SOCKET_DEFAULT_TX_SIZE,
    TCP_SOCKET_DEFAULT_RX_SIZE,

};
#endif

#if defined(TCPIP_STACK_USE_UDP)
const UDP_MODULE_CONFIG udpConfigData =
{
    UDP_MAX_SOCKETS,
    UDP_SOCKET_DEFAULT_TX_SIZE,
    UDP_SOCKET_POOL_BUFFERS,
    UDP_SOCKET_POOL_BUFFER_SIZE,
};
#endif


//TCP/IP Mac config

const TCPIP_MODULE_MAC_PIC32INT_CONFIG macPIC32INTConfigData =
{
    EMAC_TX_DESCRIPTORS, // nTxDescriptors
    EMAC_RX_BUFF_SIZE, // rxBuffSize
    EMAC_RX_DESCRIPTORS, // nRxDescriptors
    ETH_OPEN_DEFAULT, // ethFlags
    ETH_PHY_CFG_RMII | ETH_PHY_CFG_ALTERNATE, // phyFlags
    500, // linkInitDelay
};

// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ60 - MAC Layer Options
//   If not using an external ENC28J60 MAC, ignore this section.
// =======================================================================


const TCPIP_MODULE_MAC_ENCJ60_CONFIG macENCJ60ConfigData =
{
};

// =======================================================================
//   TCPIP_MODULE_MAC_ENCJ600 - MAC Layer Options
//   If not using an external ENC24J600 MAC, ignore this section.
// =======================================================================

const TCPIP_MODULE_MAC_ENCJ600_CONFIG macENCJ600ConfigData =
{
};



// =======================================================================
//   TCPIP_MODULE_MAC_97J60 - MAC Layer Options
//   If not using an external 97J60 MAC, ignore this section.
// =======================================================================

const TCPIP_MODULE_MAC_97J60_CONFIG mac97J60ConfigData =
{
};


// =======================================================================
//   TCPIP_MODULE_MAC_MRF24W - MAC Layer Options
//   If not using an external MRF24W Wi-Fi MAC, ignore this section.
// =======================================================================

const TCPIP_MODULE_MAC_MRF24W_CONFIG macMRF24WConfigData =
{
};


const TCPIP_STACK_MODULE_CONFIG TCPIP_STACK_MODULE_CONFIG_TBL [] =
{
    //ModuleID                  // configData
#if defined(TCPIP_STACK_USE_IPV4)
    {TCPIP_MODULE_IPV4, 0},
#endif
#if defined(TCPIP_STACK_USE_ICMP_CLIENT) || defined(TCPIP_STACK_USE_ICMP_SERVER)
    {TCPIP_MODULE_ICMP, 0}, // TCPIP_MODULE_ICMP
#endif
    {TCPIP_MODULE_ARP, &arpConfigData}, // TCPIP_MODULE_ARP
#if defined(TCPIP_STACK_USE_IPV6)
    {TCPIP_MODULE_IPV6, &ipv6ConfigData}, // TCPIP_MODULE_IPV6
    {TCPIP_MODULE_ICMPV6, 0}, // TCPIP_MODULE_ICMPV6
    {TCPIP_MODULE_NDP, 0}, // TCPIP_MODULE_NDP
#endif
#if defined(TCPIP_STACK_USE_UDP)
    {TCPIP_MODULE_UDP, &udpConfigData}, // TCPIP_MODULE_UDP,
#endif
#if defined(TCPIP_STACK_USE_TCP)
    {TCPIP_MODULE_TCP, &tcpConfigData}, // TCPIP_MODULE_TCP,
#endif
#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
    {TCPIP_MODULE_DHCP_CLIENT, &dhcpConfigData}, // TCPIP_MODULE_DHCP_CLIENT,
#endif
#if defined(TCPIP_STACK_USE_DHCP_SERVER)
    {TCPIP_MODULE_DHCP_SERVER, &dhcpsConfigData}, // TCPIP_MODULE_DHCP_SERVER,
#if defined(TCPIP_STACK_USE_AUTOIP)
    {TCPIP_MODULE_AUTOIP, 0}, // TCPIP_MODULE_AUTOIP
#endif
#endif
#if defined(TCPIP_STACK_USE_ANNOUNCE)
    {TCPIP_MODULE_ANNOUNCE, 0}, // TCPIP_MODULE_ANNOUNCE,
#endif
#if defined(TCPIP_STACK_USE_DNS)
    {TCPIP_MODULE_DNS_CLIENT, 0}, // TCPIP_MODULE_DNS_CLIENT,
#endif // TCPIP_STACK_USE_DNS
#if defined(TCPIP_STACK_USE_NBNS)
    {TCPIP_MODULE_NBNS, 0}, // TCPIP_MODULE_NBNS
#endif
#if defined(TCPIP_STACK_USE_SNTP_CLIENT)
    {TCPIP_MODULE_SNTP, 0}, // TCPIP_MODULE_SNTP,
#endif
#if defined(TCPIP_STACK_USE_BERKELEY_API)
    {TCPIP_MODULE_BERKELEY, 0}, // TCPIP_MODULE_BERKELEY,
#endif
#if defined(TCPIP_STACK_USE_HTTP_SERVER)
    {TCPIP_MODULE_HTTP_SERVER, &httpConfigData}, // TCPIP_MODULE_HTTP_SERVER,
#endif
#if defined(TCPIP_STACK_USE_TELNET_SERVER)
    {TCPIP_MODULE_TELNET_SERVER, 0}, // TCPIP_MODULE_TELNET_SERVER,
#endif
#if defined(TCPIP_STACK_USE_SSL_SERVER) || defined(TCPIP_STACK_USE_SSL_CLIENT)
    {TCPIP_MODULE_RSA, 0}, // TCPIP_MODULE_RSA,
#endif
#if defined(TCPIP_STACK_USE_SSL_SERVER) || defined(TCPIP_STACK_USE_SSL_CLIENT)
    {TCPIP_MODULE_SSL, 0}, // TCPIP_MODULE_SSL,
#endif
#if defined(TCPIP_STACK_USE_FTP_SERVER)
    {TCPIP_MODULE_FTP_SERVER, 0}, // TCPIP_MODULE_FTP,
#endif
#if defined(TCPIP_STACK_USE_SNMP_SERVER)
    {TCPIP_MODULE_SNMP_SERVER, 0}, // TCPIP_MODULE_SNMP_SERVER,
#endif
#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    {TCPIP_MODULE_DYNDNS_CLIENT, 0}, // TCPIP_MODULE_DYNDNS_CLIENT,
#endif
#if defined(TCPIP_STACK_USE_REBOOT_SERVER)
    {TCPIP_MODULE_REBOOT_SERVER, 0}, // TCPIP_MODULE_REBOOT_SERVER,
#endif
#if defined(TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL)
    {TCPIP_MODULE_ZCLL, 0}, // TCPIP_MODULE_ZCLL,
    {TCPIP_MODULE_MDNS, 0}, // TCPIP_MODULE_MDNS,
#endif
#if defined(TCPIP_STACK_COMMAND_ENABLE)
    {TCPIP_MODULE_TCPIP_COMMAND, 0}, // TCPIP_MODULE_TCPIP_COMMAND
#endif


    // MAC modules
#if defined(TCPIP_IF_ENC28J60)
    {TCPIP_MODULE_MAC_ENCJ60, &macENCJ60ConfigData}, // TCPIP_MODULE_MAC_ENCJ60
#endif
#if defined(TCPIP_IF_ENCX24J600)
    {TCPIP_MODULE_MAC_ENCJ600, &macENCJ600ConfigData}, // TCPIP_MODULE_MAC_ENCJ600
#endif
#if defined(TCPIP_IF_97J60)
    {TCPIP_MODULE_MAC_97J60, &mac97J60ConfigData}, // TCPIP_MODULE_MAC_97J60
#endif
#if defined(TCPIP_IF_PIC32INT)
    {TCPIP_MODULE_MAC_PIC32INT, &macPIC32INTConfigData}, // TCPIP_MODULE_MAC_PIC32INT
#endif
#if defined(TCPIP_IF_MRF24W)
    {TCPIP_MODULE_MAC_MRF24W, &macMRF24WConfigData}, // TCPIP_MODULE_MAC_MRF24W
#endif
};




const TCPIP_NETWORK_CONFIG __attribute__((unused)) TCPIP_HOSTS_CONFIGURATION[] =
{
    {
        "PIC32INT", // interface
        "MCHPBOARD_E", // hostName // Max characters is 15
        0,           // or 0 for the factory pre-programmed address
        "169.254.1.2", // ipAddr
        "255.255.0.0", // ipMask
        "169.254.1.1", // gateway
        "169.254.1.1", // priDNS
        "0.0.0.0", // secondDNS
        "full", // powerMode
        (TCPIP_NETWORK_CONFIG_DHCP_CLIENT_ON), // start up flags
    },
};



/*********************************************************************
 * Function:        bool TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          true if Stack and its componets are initialized
 *                  false otherwise
 *
 * Overview:        The function initializes the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


bool TCPIP_STACK_Init() 
{
    return TCPIP_STACK_Initialize(TCPIP_HOSTS_CONFIGURATION,
            sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION),
            TCPIP_STACK_MODULE_CONFIG_TBL,
            sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL));
}

