/*******************************************************************************
  Dynamic Host Configuration Protocol (DHCP) Server API Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dhcps.h

  Summary:
    Dynamic Host Configuration Protocol(DHCP) Server APIs.

  Description:
     The DHCP server permanently assigns a free IP address to a requesting 
     client from the range defined in the dhcps_config.h  file.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright © 2012 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef __DHCPS_H
#define __DHCPS_H

// DHCP server configuration details
typedef struct
{
    bool    enabled;   // enable DHCP server
    bool    deleteOldLease;  // delete old cache if still in place,
    // specific DHCP params
    size_t  leaseEntries;   // max number of lease entries
    int     entrySolvedTmo; // solved entry removed after this tmo
                            // if not referenced - seconds
    char    *startIpAddressRange; // start value of the IP address  for DHCP clients.

} DHCPS_MODULE_CONFIG;


// listing of the leases
//
typedef struct
{
    TCPIP_MAC_ADDR    hwAdd; // Client MAC address
    IPV4_ADDR   ipAddress; // Leased IP address
    uint32_t    leaseTime; // Lease period
}DHCPS_LEASE_ENTRY;

// DHCP server pool types are used to get the leased IP address details.
typedef enum
{
    DHCP_SERVER_POOL_ENTRY_ALL,   // Get or Remove all the Leased address . There might be a address which may not be used. 
    DHCP_SERVER_POOL_ENTRY_IN_USE // Get or remove only Leased IP address.
}DHCP_SERVER_POOL_ENTRY_TYPE;

// Lease details which is used by the CLI command prompt.
typedef const void* DHCPS_LEASE_HANDLE;


/*****************************************************************************
  Function:
    bool TCPIP_DHCPS_IsEnabled(CPIP_NET_HANDLE hNet)

  Summary:
    Determines if the DHCP Server is enabled on the specified interface.

  Description:
    Determines if the DHCP Server is enabled on the specified interface.

  Precondition:
    None

  Parameters:
     hNet- Interface to query.

  Returns:
    None
***************************************************************************/
bool TCPIP_DHCPS_IsEnabled(TCPIP_NET_HANDLE hNet);

/*****************************************************************************
  Function:
    bool TCPIP_DHCPS_Disable(TCPIP_NET_HANDLE hNet)

  Summary:
    Disables the DHCP Server for the specified interface.

  Description:
    Disables the DHCP Server for the specified interface.

  Precondition:
    None

  Parameters:
    pNetIf - Interface to disable the DHCP Server on.

  Returns:
    true if success
    false otherwise

  Remarks:
    When the interface continues using its old configuration, it is possible
    that the lease may take sometime to expire. And The communication will 
    be there till it is not expired.Lease time is configured in dhcps_config.h.
 */

bool TCPIP_DHCPS_Disable(TCPIP_NET_HANDLE hNet);

/*****************************************************************************
  Function:
    void TCPIP_DHCPS_Enable(TCPIP_NET_HANDLE hNet)

  Summary:
    Enables the DHCP Server for the specified interface.

  Description:
    Enables the DHCP Server for the specified interface, if it is disabled.
    If it is already enabled, nothing is done.

  Precondition:
    None

  Parameters:
     hNet - Interface to enable the DHCP Server on.

  Returns:
    true if success
    false otherwise
*/


bool TCPIP_DHCPS_Enable(TCPIP_NET_HANDLE hNet);


// returns a lease entry and allows iteration through the whole list of leases
// if leaseHandle it starts from the begining
// returns a non-zero DHCPS_LEASE_HANDLE to be used in the subsequent calls or 0 if end of list or wrong interface, or DHCP server not running on that interface
DHCPS_LEASE_HANDLE  TCPIP_DHCPS_LeaseEntryGet(TCPIP_NET_HANDLE netH, DHCPS_LEASE_ENTRY* pLeaseEntry, DHCPS_LEASE_HANDLE leaseHandle);

/******************************************************************************
 Function:
    bool TCPIP_DHCPS_RemovePoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type);

  Summary:
    Removes all the entries or only used entries of a certain type belonging to a network interface.

  Description:
    This API is used to remove the DHCP server entries from the pool as per DHCP_SERVER_POOL_ENTRY_TYPE. 
  Precondition:
    DHCP server module should have been initialized

  Parameters:
    hNet    -   Interface handle to use
    type    -   type of entries to remove:
        valid types:     DHCP_SERVER_POOL_ENTRY_ALL,
                            DHCP_SERVER_POOL_ENTRY_IN_USE

  Returns:
   true or false

  Example:
    None

  Remarks:
    None
  ***************************************************************************/

bool TCPIP_DHCPS_RemovePoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type);

/******************************************************************************
 Function:
    int TCPIP_DHCPS_GetPoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type);

  Summary:
    Get all the entries or only used entries of a certain type belonging to a network interface.

  Description:
    This API is used to get the DHCP server entries from the pool as per DHCP_SERVER_POOL_ENTRY_TYPE. 
  Precondition:
    DHCP server module should have been initialized

  Parameters:
    hNet    -   Interface handle to use
    type    -   type of entries to remove:
        valid types:     DHCP_SERVER_POOL_ENTRY_ALL,
                            DHCP_SERVER_POOL_ENTRY_IN_USE

  Returns:
   true or false

  Example:
    None

  Remarks:
    None
  ***************************************************************************/

int TCPIP_DHCPS_GetPoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type);


#endif // __DHCPS_H

