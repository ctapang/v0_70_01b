/*******************************************************************************
  DHCP Private file for Microchip TCP/IP Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
    dhcp_private.h

  Summary:
    DHCP Private file for Microchip TCP/IP Stack

  Description:
    This file provides the TCP/IP Stack DHCP Private file API definitions.
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright � 2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef __DHCP_PRIVATE_H_
#define __DHCP_PRIVATE_H_


#define BOOT_REQUEST                    (1u)	// BOOT_REQUEST DHCP type
#define BOOT_REPLY                      (2u)	// BOOT_REPLY DHCP type
#define BOOT_HW_TYPE                    (1u)	// BOOT_HW_TYPE DHCP type
#define BOOT_LEN_OF_HW_TYPE             (6u)	// BOOT_LEN_OF_HW_TYPE DHCP type

#define DHCP_MESSAGE_TYPE               (53u)	// DHCP Message Type constant
#define DHCP_MESSAGE_TYPE_LEN           (1u)	// Length of DHCP Message Type

#define DHCP_UNKNOWN_MESSAGE            (0u)	// Code for unknown DHCP message

#define DHCP_INFORM_MESSAGE           	(8u)	// DCHP INFORM Message
#define DHCP_DISCOVER_MESSAGE           (1u)	// DCHP Discover Message
#define DHCP_OFFER_MESSAGE              (2u)	// DHCP Offer Message
#define DHCP_REQUEST_MESSAGE            (3u)	// DHCP Request message
#define DHCP_DECLINE_MESSAGE            (4u)	// DHCP Decline Message
#define DHCP_ACK_MESSAGE                (5u)	// DHCP ACK Message
#define DHCP_NAK_MESSAGE                (6u)	// DHCP NAK Message
#define DHCP_RELEASE_MESSAGE            (7u)	// DCHP Release message

#define DHCP_SERVER_IDENTIFIER          (54u)	// DHCP Server Identifier
#define DHCP_SERVER_IDENTIFIER_LEN      (4u)	// DHCP Server Identifier length

#define DHCP_OPTION_ACK_MESSAGE			(53u)	// DHCP_OPTION_ACK_MESSAGE Type
#define DHCP_PARAM_REQUEST_LIST         (55u)	// DHCP_PARAM_REQUEST_LIST Type
#define DHCP_PARAM_REQUEST_LIST_LEN     (4u)	// DHCP_PARAM_REQUEST_LIST_LEN Type
#define DHCP_PARAM_REQUEST_IP_ADDRESS       (50u)	// DHCP_PARAM_REQUEST_IP_ADDRESS Type
#define DHCP_PARAM_REQUEST_IP_ADDRESS_LEN   (4u)	// DHCP_PARAM_REQUEST_IP_ADDRESS_LEN Type
#define DHCP_PARAM_REQUEST_CLIENT_ID       (61u)	// DHCP_PARAM_REQUEST_IP_ADDRESS Type
#define DHCP_PARAM_REQUEST_CLIENT_ID_LEN   (7u)	// DHCP_PARAM_REQUEST_IP_ADDRESS_LEN Type

#define DHCP_SUBNET_MASK                (1u)	// DHCP_SUBNET_MASK Type
#define DHCP_ROUTER                     (3u)	// DHCP_ROUTER Type
#define DHCP_DNS						(6u)	// DHCP_DNS Type
#define DHCP_HOST_NAME					(12u)	// DHCP_HOST_NAME Type
#define DHCP_IP_LEASE_TIME              (51u)	// DHCP_IP_LEASE_TIME Type
#define DHCP_END_OPTION                 (255u)	// DHCP_END_OPTION Type

// DHCP or BOOTP Header structure
typedef struct __attribute__((aligned(2), packed))
{
	uint8_t		MessageType;	// Message type for this message
	uint8_t		HardwareType;	// Hardware type for this message
	uint8_t		HardwareLen;	// Length of hardware type
	uint8_t		Hops;			// Number of hops
	uint32_t		TransactionID;	// DHCP Transaction ID
	uint16_t		SecondsElapsed;	// Number of elapsed seconds
	uint16_t		BootpFlags;		// BOOTP Flags
	IPV4_ADDR		ClientIP;		// Client IP
	IPV4_ADDR		YourIP;			// Your IP
	IPV4_ADDR		NextServerIP;	// Next Server IP
	IPV4_ADDR		RelayAgentIP;	// Relay Agent IP
	TCPIP_MAC_ADDR	ClientMAC;		// Client MAC Address
} BOOTP_HEADER;

// DHCP State Machine
typedef enum
{
    SM_DHCP_IDLE = 0,           // idle state
    SM_DHCP_WAIT_LINK,          // waiting for an active connection
	SM_DHCP_GET_SOCKET,			// DHCP is trying to obtain a socket
    SM_DHCP_WAIT_OPEN,          // DHCP waiting for the open socket
	SM_DHCP_SEND_DISCOVERY,		// DHCP is sending a DHCP Discover message
	SM_DHCP_GET_OFFER,			// DHCP is waiting for a DHCP Offer
	SM_DHCP_SEND_REQUEST,		// DHCP is sending a DHCP Send Reequest message
	SM_DHCP_GET_REQUEST_ACK,	// DCHP is waiting for a Request ACK message
	SM_DHCP_BOUND,				// DHCP is bound
	SM_DHCP_SEND_RENEW,			// DHCP is sending a DHCP renew message (first try)
	SM_DHCP_GET_RENEW_ACK,		// DHCP is waiting for a renew ACK
	SM_DHCP_SEND_RENEW2,		// DHCP is sending a DHCP renew message (second try)
	SM_DHCP_GET_RENEW_ACK2,		// DHCP is waiting for a renew ACK
	SM_DHCP_SEND_RENEW3,		// DHCP is sending a DHCP renew message (third try)
	SM_DHCP_GET_RENEW_ACK3		// DHCP is waiting for a renew ACK
} SM_DHCP;

// current operation performed by the DHCP SM
typedef enum
{
    DHCP_OPER_NONE,             // invalid operation       
    DHCP_OPER_INIT,             // initialization, all new process
    DHCP_OPER_INIT_REBOOT,      // use a known IP address
    DHCP_OPER_RENEW,            // lease renewal
}DHCP_OPERATION_TYPE;

// operation requested by a DHCP user
typedef enum
{
    DHCP_OP_REQ_ENABLE,       // enable the service
    DHCP_OP_REQ_RENEW,        // perform a renewal
    DHCP_OP_REQ_REQUEST,      // perform a request with a known IP address
}DHCP_OPERATION_REQ;

// DHCP event registration

typedef struct  _TAG_DHCP_LIST_NODE
{
	struct _TAG_DHCP_LIST_NODE*		next;		// next node in list
                                                // makes it valid SGL_LIST_NODE node
    TCPIP_DHCP_EVENT_HANDLER              handler;    // handler to be called for event
    const void*                     hParam;     // handler parameter
    TCPIP_NET_HANDLE                hNet;       // interface that's registered for
                                                // 0 if all    
}DHCP_LIST_NODE;




#endif  // __DHCP_PRIVATE_H_



