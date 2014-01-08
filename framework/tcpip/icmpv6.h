/*******************************************************************************
 Internet Control Message Protocol (ICMP) IPv6 API Header File

 Company:
    Microchip Technology Inc.

  File Name:
    icmpv6.h
	
  Summary:
    IPv6 Internet Communication Message Protocol

  Description:
    Internet Control Message Protocol (ICMP) in IPv6 functions the same as
    ICMP in IPv4.ICMPv6 is used to report error messages and information messages 
    for IPv6 nodes. ICMP packets in IPv6 are used in the IPv6 neighbor discovery process,
    path MTU discovery, and the Multicast Listener Discovery (MLD) protocol for IPv6.
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

#ifndef _ICMPV6_H
#define _ICMPV6_H


//*********************
// ICMPv6 Public Types
//*********************

// a handle that a client can use
// after the event handler has been registered
typedef const void* ICMPV6_HANDLE;

// ICMPv6 packet types
typedef enum
{
    ICMPV6_ERROR_DEST_UNREACHABLE =      1u,        // Destination Unreachable error packet
    ICMPV6_ERROR_PACKET_TOO_BIG =        2u,        // Packet Too Big error packet
    ICMPV6_ERROR_TIME_EXCEEDED =         3u,        // Time Exceeded error packet
    ICMPV6_ERROR_PARAMETER_PROBLEM =     4u,        // Parameter Problem error packet
    ICMPV6_INFO_ECHO_REQUEST =           128u,      // Echo Request packet
    ICMPV6_INFO_ECHO_REPLY =             129u,      // Echo Reply packet
    ICMPV6_INFO_ROUTER_SOLICITATION =    133u,      // Router solicitation NDP packet
    ICMPV6_INFO_ROUTER_ADVERTISEMENT =   134u,      // Router advertisement NDP packet
    ICMPV6_INFO_NEIGHBOR_SOLICITATION =  135u,      // Neighbor Solicitation NDP packet
    ICMPV6_INFO_NEIGHBOR_ADVERTISEMENT = 136u,      // Neighbor Advertisement NDP packet
    ICMPV6_INFO_REDIRECT =               137u       // Redirect NDP packet
} ICMPV6_PACKET_TYPES;

// Definitions for ICMPv6 Destination Unreachable error code
typedef enum
{
    ICMPV6_ERR_DU_NO_ROUTE =                         0u,  // No route to destination
    ICMPV6_ERR_DU_PROHIBITED =                       1u,  // Communication with destination administratively prohibited
    ICMPV6_ERR_DU_OUTSIDE_SCOPE =                    2u,  // Beyond scope of source address
    ICMPV6_ERR_DU_ADDR_UNREACHABLE =                 3u,  // Address unreachable
    ICMPV6_ERR_DU_PORT_UNREACHABLE =                 4u,  // Port unreachable
    ICMPV6_ERR_DU_SRC_FAILED_INGRESS_POLICY =        5u,  // Source address failed ingress/egress policy
    ICMPV6_ERR_DU_REJECT_ROUTE =                     6u   // Reject route to destination
} ICMPV6_ERR_DU_CODE;

// Definition for ICMPv6 Packet Too Big error code
#define ICMPV6_ERR_PTB_CODE                             0u

// Definitions for ICMPv6 Time Exceeded error code
typedef enum
{
    ICMPV6_ERR_TE_HOP_LIMIT_EXCEEDED =               0u,  // Hop limit exceeded in transit
    ICMPV6_ERR_TE_FRAG_ASSEMBLY_TIME_EXCEEDED =      1u   // Fragment reassembly time exceeded
} ICMPV6_ERR_TE_CODE;

// Definitions for ICMPv6 Parameter Problem error code
typedef enum
{
    ICMPV6_ERR_PP_ERRONEOUS_HEADER =                 0u,  // Erroneous header field encountered
    ICMPV6_ERR_PP_UNRECOGNIZED_NEXT_HEADER =         1u,  // Unrecognized Next Header type encountered
    ICMPV6_ERR_PP_UNRECOGNIZED_IPV6_OPTION =         2u   // Unrecognized IPv6 option encountered
} ICMPV6_ERR_PP_CODE;

// Definition for ICMPv6 Packet Echo Request info code
#define ICMPV6_INFO_EREQ_CODE                           0u

// Definition for ICMPv6 Packet Echo Reply info code
#define ICMPV6_INFO_ERPL_CODE                           0u

// Header for an ICMPv6 Error packet
typedef struct __attribute__((__packed__))
{
    uint8_t vType;  // icmpV6 	request or reply type 
    uint8_t vCode; // error code
    uint16_t wChecksum; // Packet TX and RX checksum
    uint32_t additionalData;   // Unused for Dest. Unreachable and Time Exceeded.  MTU for MTU.  Pointer for Parameter Problem.
} ICMPV6_HEADER_ERROR;

// Header for an ICMPv6 Echo Request/Reply packet
typedef struct __attribute__((__packed__))
{
    uint8_t vType;   // icmpV6 	request or reply type
    uint8_t vCode;   // Erro code
    uint16_t wChecksum;  // Packet TX and RX checksum
    uint16_t identifier; // incoming and outgoing packet identifier
    uint16_t sequenceNumber; // request and reply  sequence number
} ICMPV6_HEADER_ECHO;


//*********************
// ICMPv6 Public APIs
//*********************

/*****************************************************************************
  Function:
    IPV6_PACKET * TCPIP_ICMPV6_HeaderEchoRequestPut (TCPIP_NET_HANDLE hNetIf, 
        IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, uint8_t type, 
        uint16_t identifier, uint16_t sequenceNumber)	

  Summary:
	Allocates a packet, IPv6 Header, and Upper-layer header for an ICMPv6 
    echo request.

  Description:
	Allocates a packet, IPv6 Header, and Upper-layer header for an ICMPv6 
    echo request.

  Precondition:
	None

  Parameters:
	pNetIf - The interface for the outgoing packet.
    localIP - The local address that should be used for this packet.
    remoteIP - The packet's destination address
    type - Echo Request or Echo Reply
    identifier - The Echo Request id.
    sequenceNumber - The Echo request sequence number

  Returns:
  	IPV6_PACKET * - The constructed error packet or NULL
  	
  Remarks:
	None
  ***************************************************************************/
IPV6_PACKET * TCPIP_ICMPV6_HeaderEchoRequestPut (TCPIP_NET_HANDLE hNetIf, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, uint8_t type, uint16_t identifier, uint16_t sequenceNumber);
#define TCPIP_ICMPV6_PutHeaderEchoReply TCPIP_ICMPV6_HeaderEchoRequestPut

/*****************************************************************************
  Function:
	bool TCPIP_ICMPV6_Flush (IPV6_PACKET * pkt)

  Summary:
	Flushes an ICMPv6 Packet

  Description:
	Flushes an ICMPv6 Packet	

  Precondition:
	None

  Parameters:
	pkt - The packet to flush

  Returns:
  	true if the packet was flushed, false if the packet was queued
  	
  Remarks:
	None
***************************************************************************/
bool TCPIP_ICMPV6_Flush (IPV6_PACKET * pkt);

void TCPIP_ICMPV6_Close (IPV6_PACKET * pkt);

/*****************************************************************************
  Function:
	ICMPV6_HANDLE TCPIP_ICMPV6_CallbackRegister (void (*callback)(TCPIP_NET_HANDLE hNetIf,
        uint8_t type, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, void * header))

  Summary:
	Registers an upper-layer function for ICMPv6 callback.

  Description:
	Registers an upper-layer function to handle ICMPv6 messages that may 
    require action at the application layer (Echo Replies, Error messages)	

  Precondition:
	None

  Parameters:
	type - ICMPv6 header type
    localIP - IPv6 destination address of the incoming message
    remoteIP - IPv6 address of the node that originated the incoming message
    header - Pointer to the ICMPv6 header

  Returns:
  	A ICMPV6_HANDLE
  	
  Remarks:
	None
***************************************************************************/
ICMPV6_HANDLE TCPIP_ICMPV6_CallbackRegister (void (*callback)(TCPIP_NET_HANDLE hNetIf, uint8_t type, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, void * header));

/*****************************************************************************
  Function:
	ICMPV6_HANDLE TCPIP_ICMPV6_CallbackRegister (void (*callback)(TCPIP_NET_HANDLE hNetIf,
        uint8_t type, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, void * header))

  Summary:
	Deregisters an upper-layer function from ICMPv6 callback.

  Description:
	deregisters an upper-layer function from the ICMPv6 register list.     

  Precondition:
	None

  Parameters:
	hIcmpv6 - ICMPv6 handler
    

  Returns:
  	true or false
  	
  Remarks:
	None
***************************************************************************/
bool          TCPIP_ICMPV6_CallbackDeregister(ICMPV6_HANDLE hIcmpv6);


#endif







