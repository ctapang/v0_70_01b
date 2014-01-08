/*******************************************************************************
  Domain Name System (DNS) Client API Header file
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    dns.h

  Summary:
    DNS definitions and interface file

  Description:
    This source file contains the DNS client module API
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

#ifndef __DNS_H
#define __DNS_H

// *****************************************************************************
/* DNS_RESOLVE_TYPE Enumeration

  Summary:
    This enumeration provides the RecordType argument for TCPIP_DNS_Resolve.

  Description:
    This enumeration provides the RecordType argument for TCPIP_DNS_Resolve.

  Remarks:
    None.
*/
typedef enum
{

    DNS_TYPE_A      = 1,        // Constant for record type in TCPIP_DNS_Resolve.  Indicates an A (standard address) record.
    DNS_TYPE_MX     = 15,       // Constant for record type in TCPIP_DNS_Resolve.  Indicates an MX (mail exchanger) record.
    DNS_TYPE_AAAA   = 28u       // Constant for record type in TCPIP_DNS_Resolve.  Indicates a quad-A (IPv6 address) address record.
}DNS_RESOLVE_TYPE;


// *****************************************************************************
/* DNS_RESULT Enumeration

  Summary:
    This enumeration provides result codes for various DNS operations.

  Description:
    This enumeration provides result codes for various DNS operations.

  Remarks:
    None.
*/
typedef enum
{
    // success codes
    DNS_RES_OK                  = 0,    // operation succeeded
    DNS_RES_PENDING,                    // operation is ongoing


    // failure codes
    DNS_RES_NO_ENTRY            = -1,   // no such entry exists
    DNS_RES_CACHE_FULL          = -2,   // the cache is full and no entry could be
    DNS_RES_OPEN_TMO            = -3,   // DNS client couldn't get a socket
    DNS_RES_SERVER_TMO          = -4,   // DNS server response tmo
    DNS_RES_NO_SERVICE          = -5,   // DNS service not implemented

    // backward compatibility results
    DNS_RES_NO_INTERFACE        = -10,   // an active/requested interface could not be found
    DNS_RES_BUSY                = -11,   // module is in use by other task; retry later
    DNS_RES_ARP_TMO             = -12,   // ARP tmo

}DNS_RESULT;


// *****************************************************************************
/* DNS_CLIENT_MODULE_CONFIG Structure Typedef

  Summary:
    Provides a placeholder for DNS client configuration.

  Description:
    Provides a placeholder for DNS client configuration.

  Remarks:
    None.
*/
typedef struct
{
}DNS_CLIENT_MODULE_CONFIG;


// *****************************************************************************
/* DNS_SERVER_MODULE_CONFIG Structure Typedef

  Summary:
    Provides a placeholder for DNS server configuration.

  Description:
    Provides a placeholder for DNS server configuration.

  Remarks:
    None.
*/
typedef struct
{
}DNS_SERVER_MODULE_CONFIG;


/*****************************************************************************
  Function:
    DNS_RESULT TCPIP_DNS_UsageBegin(TCPIP_NET_HANDLE netH)

  Summary:
    Claims access to the DNS module.

  Description:
    This function acts as a semaphore to obtain usage of the DNS module.
    Call this function and ensure that it returns DNS_RES_OK before calling any
    other DNS APIs.  Call TCPIP_DNS_UsageEnd when this application no longer
    needs the DNS module so that other applications may make use of it.

  Precondition:
    Stack is initialized.

  Parameters:
    netH   - interface to use
                If 0, a default interface will be selected

  Return Values:
    DNS_RES_OK      - the calling application has sucessfully taken ownership of the DNS module
    DNS_RES_BUSY    - The DNS module is currently in use.
                      Yield to the stack and attempt this call again later.

  Remarks:
    Ensure that TCPIP_DNS_UsageEnd is always called once your application has
    obtained control of the DNS module.  If this is not done, the stack
    will hang for all future applications requiring DNS access.
  ***************************************************************************/
DNS_RESULT  TCPIP_DNS_UsageBegin(TCPIP_NET_HANDLE netH);


/*****************************************************************************
  Function:
    void TCPIP_DNS_Resolve(uint8_t* Hostname, DNS_RESOLVE_TYPE Type)

  Summary:
    Begins resolution of an address.

  Description:
    This function attempts to resolve a host name to an IP address.  When
    called, it starts the DNS state machine.  Call TCPIP_DNS_IsResolved repeatedly
    to determine if the resolution is complete.

    Only one DNS resoultion may be executed at a time.  The Hostname must
    not be modified in memory until the resolution is complete.

  Precondition:
    TCPIP_DNS_UsageBegin returned DNS_RES_OK on a previous call.

  Parameters:
    Hostname - A pointer to the null terminated string specifiying the
        host for which to resolve an IP.
    RecordType - DNS_TYPE_A or DNS_TYPE_MX depending on what type of
        record resolution is desired.

  Returns:
    DNS_RES_OK

  Remarks:
    This function requires access to one UDP socket.  If none are available,
    UDP_MAX_SOCKETS may need to be increased.

  ***************************************************************************/
DNS_RESULT  TCPIP_DNS_Resolve(const char* HostName, DNS_RESOLVE_TYPE Type);


/*****************************************************************************
  Function:
    DNS_RESULT TCPIP_DNS_IsResolved(const char* HostName, IPV4_ADDR* HostIP)

  Summary:
    Determines if the DNS resolution is complete and provides the IP.

  Description:
    Call this function to determine if the DNS resolution of an address has
    been completed.  If so, the resolved address will be provided in HostIP.

  Precondition:
    TCPIP_DNS_Resolve has been called.

  Parameters:
    Hostname - A pointer to the null terminated string specifiying the
        host for which to resolve an IP.
    HostIP - A pointer to an IPV4_ADDR structure in which to store the
        resolved IP address once resolution is complete.

  Return Values:
    DNS_RES_OK       - The DNS client has obtained an IP
                       HostIP will contain the resolved address.
    DNS_RES_PENDING  - The resolution process is still in progress.
    DNS_RES_SERVER_TMO  - DNS server timed out
    DNS_RES_NO_ENTRY - no such entry to be resolved exists


  Remarks:
    None.

  ***************************************************************************/
DNS_RESULT  TCPIP_DNS_IsResolved(const char* HostName, void* HostIP);


/*****************************************************************************
  Function:
    DNS_RESULT TCPIP_DNS_UsageEnd(TCPIP_NET_HANDLE netH)

  Summary:
    Releases control of the DNS module.

  Description:
    This function acts as a semaphore to release control of the DNS module.
    Call this function when this application no longer needs the DNS
    module so that other applications may make use of it.

  Precondition:
    TCPIP_DNS_UsageBegin returned DNS_RES_OK on a previous call.

  Parameters:
    netH   - interface to release
                Not used.

  Return Values:
    DNS_RES_OK - The DNS module successfully released.

  Remarks:
    Ensure that TCPIP_DNS_UsageEnd is always called once your application has
    obtained control of the DNS module.  If this is not done, the stack
    will hang for all future applications requiring DNS access.
  ***************************************************************************/
DNS_RESULT  TCPIP_DNS_UsageEnd(TCPIP_NET_HANDLE netH);


#endif
