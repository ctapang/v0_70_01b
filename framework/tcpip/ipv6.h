/*******************************************************************************
  IPv6 Defs for Microchip TCP/IP Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
    ipv6.h

  Summary:
    IP is the workhorse protocol of the TCP/IP protocol suite.

  Description:
    IP is the workhorse protocol of the TCP/IP protocol suite. All TCP, UDP, ICMP,
    and IGMP data gets transmitted as IP datagrams. IP provides an reliable, 
    connectionless datagram delivery service.
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

#ifndef __IPV6_H_
#define __IPV6_H_

// *****************************************************************************
// *****************************************************************************
// Section: public definitions
// *****************************************************************************
// *****************************************************************************

#include "tcpip/src/link_list.h"

// *****************************************************************************
/* IPV6_NEXT_HEADER_TYPE Enumeration

  Summary:
    Defines a list of next header types

  Description:
    Defines a list of next header types

  Remarks:
    None
 */
typedef enum
{
    IPV6_PROT_HOP_BY_HOP_OPTIONS_HEADER = (0u), // IPv6 Hop-by-Hop Opt. Header
    IPV6_PROT_ICMP = (1u),
    IPV6_PROT_TCP = (6u),
    IPV6_PROT_UDP = (17u),
    IPV6_PROT_IPV6 = (41u), // IPv6 Protocol
    IPV6_PROT_ROUTING_HEADER = (43u), // IPv6 Routing Header
    IPV6_PROT_FRAGMENTATION_HEADER = (44u), // IPv6 Fragmentation Header
    IPV6_PROT_ENCAPSULATING_SECURITY_PAYLOAD_HEADER = (50u), // Encapsulating Security Payload Header
    IPV6_PROT_AUTHENTICATION_HEADER = (51u), // Authentication Header
    IPV6_PROT_ICMPV6 = (58u), // ICMPv6 Protocol
    IPV6_PROT_NONE = (59u), // No next header
    IPV6_PROT_DESTINATION_OPTIONS_HEADER = (60u) // Destination Options Header
} IPV6_NEXT_HEADER_TYPE;

#define IP_VERSION_6    (1u) // Using IPv6
#define IP_VERSION_4    (0u) // Using IPv4


// *****************************************************************************
/* IPV6_ACTION Enumeration

  Summary:
    Provides a list of possible IPv6 actions.

  Description:
    Provides a list of possible IPv6 actions.

  Remarks:
    None
 */
typedef enum {
    IPV6_ACTION_NONE = 0,
    IPV6_ACTION_DISCARD_SILENT,
    IPV6_ACTION_DISCARD_PP_0,
    IPV6_ACTION_DISCARD_PP_2,
    IPV6_ACTION_DISCARD_PP_2_NOT_MC,
    IPV6_ACTION_BEGIN_EX_HEADER_PROCESSING
} IPV6_ACTION;

// IPv6 Type-length-value type code for the Pad 1 option
#define IPV6_TLV_PAD_1                          0u
// IPv6 Type-length-value type code for the Pad N option
#define IPV6_TLV_PAD_N                          1u
// IPv6 Type-length-value type code for the Hop-by-hop "Jumbogram Payload" option
#define IPV6_TLV_HBHO_PAYLOAD_JUMBOGRAM         0xC2u
// IPv6 Type-length-value type code for the Hop-by-hop "Router Alert" option
#define IPV6_TLV_HBHO_ROUTER_ALERT              0x05u

// IPv6 action code for the unrecognized option reaction to skip the option
#define IPV6_TLV_UNREC_OPT_SKIP_OPTION          0b00
// IPv6 action code for the unrecognized option reaction to discard the packet silently
#define IPV6_TLV_UNREC_OPT_DISCARD_SILENT       0b01
// IPv6 action code for the unrecognized option reaction to discard the packet and send
// an ICMP parameter problem message
#define IPV6_TLV_UNREC_OPT_DISCARD_PP           0b10
// IPv6 action code for the unrecognized option reaction to discard the packet and send
// an ICMP parameter problem message is the destination addr isn't a multicast address
#define IPV6_TLV_UNREC_OPT_DISCARD_PP_NOT_MC    0b11

#define IPV6_HEADER_OFFSET_PAYLOAD_LENGTH       (0x04u) // Header offset for payload length
#define IPV6_HEADER_OFFSET_NEXT_HEADER          (0x06u) // Header offset for next header
#define IPV6_HEADER_OFFSET_SOURCE_ADDR          (0x08u) // Header offset for source address
#define IPV6_HEADER_OFFSET_DEST_ADDR            (0x08u + sizeof (IPV6_ADDR)) // Header offset for destination address


// *****************************************************************************
/* IPV6_ADDRESS_PREFERENCE Enumeration

  Summary:
    Provides selection of public versus temporary addresses.

  Description:
    Provides selection of public versus temporary addresses.

  Remarks:
    None
 */
typedef enum
{
    IPV6_PREFER_PUBLIC_ADDRESSES = 0,
    IPV6_PREFER_TEMPORARY_ADDRESSES
} IPV6_ADDRESS_PREFERENCE;


// *****************************************************************************
/* IPV6_SEGMENT_TYPE Enumeration

  Summary:
    Provides an enumeration of IPv6 segment types.

  Description:
    Provides an enumeration of IPv6 segment types.

  Remarks:
    None
 */
typedef enum
{
    TYPE_IPV6_HEADER = 1u,
    TYPE_IPV6_EX_HEADER_HOP_BY_HOP_OPTIONS,
    TYPE_IPV6_EX_HEADER_DESTINATION_OPTIONS_1,
    TYPE_IPV6_EX_HEADER_ROUTING,
    TYPE_IPV6_EX_HEADER_FRAGMENT,
    TYPE_IPV6_EX_HEADER_AUTHENTICATION_HEADER,
    TYPE_IPV6_EX_HEADER_ENCAPSULATING_SECURITY_PAYLOAD,
    TYPE_IPV6_EX_HEADER_DESTINATION_OPTIONS_2,
    TYPE_IPV6_UPPER_LAYER_HEADER,
    TYPE_IPV6_UPPER_LAYER_PAYLOAD,
    TYPE_IPV6_BEGINNING_OF_WRITABLE_PART,
    TYPE_IPV6_END_OF_LIST
} IPV6_SEGMENT_TYPE;

extern const IPV6_ADDR IPV6_FIXED_ADDR_UNSPECIFIED;
extern const IPV6_ADDR IPV6_FIXED_ADDR_ALL_NODES_MULTICAST;
extern const IPV6_ADDR IPV6_FIXED_ADDR_ALL_ROUTER_MULTICAST;
extern const IPV6_ADDR IPV6_SOLICITED_NODE_MULTICAST;

extern const TCPIP_MAC_ADDR  IPV6_MULTICAST_MAC_ADDRESS;

// *****************************************************************************
/* IPV6_TLV_OPTION_TYPE Union Typedef

  Summary:
    Data structure for IPv6 TLV options.

  Description:
    Data structure for IPv6 TLV options.

  Remarks:
    None
 */
typedef union
{
    unsigned char b;

    struct
    {
        unsigned option : 6;
        unsigned unrecognizedAction : 2;
    } bits;
} IPV6_TLV_OPTION_TYPE;


// *****************************************************************************
/* IPV6_ADDRESS_TYPE Union Typedef

  Summary:
    Data structure for IPv6 addresses.

  Description:
    Data structure for IPv6 addresses.

  Remarks:
    None
 */
typedef union
{
    unsigned char byte;

    struct
    {
        unsigned scope : 4;
        unsigned type : 2;
    } bits;
} IPV6_ADDRESS_TYPE;


// *****************************************************************************
/* IPV6_ADDRESS_POLICY Structure Typedef

  Summary:


  Description:


  Remarks:
    None
 */
typedef struct
{
    IPV6_ADDR address;
    unsigned char prefixLength;
    unsigned char precedence;
    unsigned char label;
} IPV6_ADDRESS_POLICY;


// *****************************************************************************
/* IPV6_DATA_SEGMENT_HEADER Structure Typedef

  Summary:


  Description:


  Remarks:
    None
 */
typedef struct _IPV6_DATA_SEGMENT_HEADER
{
    uint8_t* dataLocation; // Location of the data to transmit
    unsigned short segmentSize; // Size of this data segment
    unsigned short segmentLen; // Number of bytes of data in this segment
    unsigned char memory; // Type: IPV6_DATA_NONE, IPV6_DATA_DYNAMIC_BUFFER, IPV6_DATA_NETWORK_FIFO, IPV6_DATA_PIC_RAM
    unsigned char segmentType; // Type of segment contents
    struct _IPV6_DATA_SEGMENT_HEADER * nextSegment; // Pointer to the next data segment
    void * data[0]; // Optional buffer space
} IPV6_DATA_SEGMENT_HEADER;



// *****************************************************************************
/* IPV6_RX_FRAGMENT_BUFFER Structure Typedef

  Summary:


  Description:


  Remarks:
    None
 */
typedef struct _IPV6_RX_FRAGMENT_BUFFER {
    struct _IPV6_RX_FRAGMENT_BUFFER * next; // Next fragmented packet    
    //uint8_t packet[TCPIP_IPV6_RX_FRAGMENTED_BUFFER_SIZE]; // Packet information
    uint8_t *ptrPacket; // Packet information
    uint32_t identification; // Fragment id
    uint16_t bytesInPacket; // Number of bytes written to packet
    uint16_t packetSize; // Packet size (packet is complete when this matches bytesInPacket)
    uint16_t firstFragmentLength; // Length of the first fragment
    uint8_t secondsRemaining; // Number of seconds remaining during which the fragment can be reassembled
} IPV6_RX_FRAGMENT_BUFFER;


// *****************************************************************************
/* IPV6_FRAGMENT_HEADER Structure Typedef

  Summary:


  Description:


  Remarks:
    None
 */
typedef struct __attribute__((__packed__))
{
    uint8_t nextHeader;
    uint8_t reserved;

    union {

        struct __attribute__((__packed__))
        {
            uint16_t m : 1;
            uint16_t reserved2 : 2;
            uint16_t fragmentOffset : 13;
        }
        bits;
        uint16_t w;
    } offsetM;
    uint32_t identification;
} IPV6_FRAGMENT_HEADER;

#define IPV6_DATA_NONE                (0x0u)          // The data segment is unused
#define IPV6_DATA_DYNAMIC_BUFFER      (0x1u)          // Data to transmit is allocated in dynamically allocated RAM
#define IPV6_DATA_NETWORK_FIFO        (0x2u)          // Data to transmit is stored in the Network Controller's FIFOs
#define IPV6_DATA_PIC_RAM             (0x3u)          // Data to transmit is stored in PIC RAM

#define IPV6_NO_UPPER_LAYER_CHECKSUM  (0xFFFFu) // Value flag for no upper layer checksum


// *****************************************************************************
/* IPv6 packet header definition

  Summary:
    None

  Description:
    None

  Remarks:
    None
 */
typedef struct
{
    unsigned long V_T_F;
    unsigned short PayloadLength;
    unsigned char NextHeader;
    unsigned char HopLimit;
    IPV6_ADDR SourceAddress;
    IPV6_ADDR DestAddress;
} IPV6_HEADER;


// *****************************************************************************
/* IPV6_EVENT_TYPE Enumeration

  Summary:
    None

  Description:
    None

  Remarks:
    None
 */
typedef enum {
    IPV6_EVENT_ADDRESS_ADDED = 1,
    IPV6_EVENT_ADDRESS_REMOVED,
    //
    IPV6_EVENT_ULA_ADDRESS_GENERATED,
    IPV6_EVENT_ULA_ADDRESS_FAILED,

} IPV6_EVENT_TYPE;

typedef const void * IPV6_HANDLE; // Pointer to IPv6 object


// *****************************************************************************
/* IPV6_MODULE_CONFIG Structure Typedef

  Summary:
    Provides a placeholdef for IPv6 configuration.

  Description:
    Provides a placeholdef for IPv6 configuration.

  Remarks:
    None
 */
typedef struct
{
    uint32_t        rxfragmentBufSize;  // rx fragmented buffer size
    uint32_t        fragmentPktRxTimeout;  // fragmented packet timeout value
}IPV6_MODULE_CONFIG;

// *****************************************************************************
/* Prototype of an IPv6 event handler

  Summary:
    Clients can register a handler with the IPv6 service.

  Description:
    Once an IPv6 event occurs the IPv6 service will call the registered handler
    The handler has to be short and fast.
    It is meant for setting an event flag, not for lengthy processing!

    evParam is a parameter that's associated to an IPv6 event
    - For an address event (IPV6_EVENT_ADDRESS_ADDED, IPV6_EVENT_ADDRESS_REMOVED) it should be typecasted
      to (const IPV6_ADDR_STRUCT*)
    - For an IPV6_EVENT_ULA_ADDRESS_GENERATED ULA event it should be typecasted
      to (const IPV6_ADDR*)
    - For an IPV6_EVENT_ULA_ADDRESS_FAILED ULA event the evParam is an IPV6_ULA_RESULT error code

    The evParam is invalid outside of the IPV6_EVENT_HANDLER context call and should not be stored
    by the caller. Info that's needed has to be copied into caller's own context.

    usrParam is an user supplied parameter

  Remarks:
    For address related events the passed (const IPV6_ADDR_STRUCT*) parameter
    is invalid after the notification call.

 */
typedef void (*IPV6_EVENT_HANDLER)(TCPIP_NET_HANDLE hNet, IPV6_EVENT_TYPE evType, const void* evParam, const void* usrParam);


// *****************************************************************************
/* Packet allocation callback function

  Summary:
    None

  Description:
    1st parameter will be an IPV6_PACKET*
    2nd parameter is supplied by the caller

  Remarks:
    None
*/
typedef void (*IPV6_PACKET_ACK_FNC)(void*, bool, const void*);

// Packet structure/state tracking for IPv6 packets

typedef struct _IPV6_PACKET
{
    struct _IPV6_PACKET * next;                   // Next packet in a queue
    unsigned short payloadLen;                  // Amount of data in payload buffer
    unsigned short headerLen;                   // Total header length (IP header + IPv6 Extension headers)
    unsigned short upperLayerHeaderLen;         // Total length of the upper layer header
    unsigned short upperLayerChecksumOffset;    // Offset of the upper layer checksum
    unsigned char upperLayerHeaderType;         // Type definition for the upper-layer heaer

    union {

        struct {
            unsigned char reserved :         3;
            unsigned char useUnspecAddr :    1; // This packet should use the unspecified address
            unsigned char sourceSpecified :  1; // The upper layer or application layer specified a source address
            unsigned char queued :           1; // Packet has been queued
            unsigned char addressType :      2; // IP_ADDRESS_TYPE_IPV6 or IP_ADDRESS_TYPE_IPV4
        };
        unsigned char val;
    } flags;
    TCPIP_MAC_ADDR remoteMACAddr;                     // The packet's remote MAC address
    IPV6_PACKET_ACK_FNC ackFnc;                 // function to be called when done with the packet
    void* ackParam;                             // parameter to be used
    void* clientData;                           // optional packet client data
    void * neighbor;                            // The neighbor that the message was received from    
    unsigned short offsetInSegment;             // Offset used for storing fragment transmission information
    SYS_TICK queuedPacketTimeout;
    IPV6_DATA_SEGMENT_HEADER payload;
    TCPIP_NET_HANDLE netIfH;                    // packet network interface
    IPV6_HEADER ipv6Header;
} IPV6_PACKET;

// *****************************************************************************
/* IPV6_ULA_FLAGS Enumeration

  Summary:
    Provides a list of possible flags for the Unique Local Address (ULA) generation.

  Description:
    Provides a list of possible ULA action flags.

  Remarks:
    None
 */
typedef enum
{
    IPV6_ULA_FLAG_NTPV4         = 0x01,     // use an IPv4 NTP server access in Unique Local Address generation
                                            // default is an IPv6 server
    IPV6_ULA_FLAG_GENERATE_ONLY = 0x02,     // generate an address only, don't add it to the interface addresses
    IPV6_ULA_FLAG_SKIP_DAD      = 0x04,     // when adding the address to the interface, skip the Duplicate Address Detection

} IPV6_ULA_FLAGS;

// *****************************************************************************
/* IPV6_ULA_RESULT Enumeration

  Summary:
    Provides a list of possible results for the Unique Local Address (ULA) generation.

  Description:
    Provides a list of possible ULA results.

  Remarks:
    None
 */
typedef enum
{
    // success codes
    IPV6_ULA_RES_OK,                // the address generation was started successfully

    // error codes
    IPV6_ULA_RES_BUSY               = -1,   // address generation module is busy
    IPV6_ULA_RES_IF_ERR             = -2,   // interface non existent
    IPV6_ULA_RES_NTP_ACCESS_ERR     = -3,   // NTP module could not be accessed
    IPV6_ULA_RES_NTP_TSTAMP_ERR     = -4,   // wrong NTP time stamp received

} IPV6_ULA_RESULT;


// *****************************************************************************
// *****************************************************************************
// Section: public API
// *****************************************************************************
// *****************************************************************************

/*****************************************************************************
  Function:
    bool TCPIP_IPV6_InterfaceIsReady (TCPIP_NET_HANDLE netH)

  Summary:
    Determines if an interface is ready for IPv6 transactions.

  Description:
    Determines if an interface is ready for IPv6 transactions.

  Precondition:
    None

  Parameters:
    pNetIf - The interface to check

  Returns:
    true if the interface has IPv6 functionality available, false otherwise

  Remarks:
    None
  ***************************************************************************/
bool TCPIP_IPV6_InterfaceIsReady(TCPIP_NET_HANDLE netH);


/*****************************************************************************
  Function:
    IPV6_ADDR_STRUCT * TCPIP_IPV6_DASSourceAddressSelect (TCPIP_NET_HANDLE hNetIf, IPV6_ADDR * dest, IPV6_ADDR * requestedSource)

  Summary:
    Determines the appropriate source address for a given destination
    address.

  Description:
    Determines the appropriate source address for a given destination
    address.

  Precondition:
    None

  Parameters:
    hNetIf - The given interface.
    dest - The destination address.
    requestedSource - A specified source.

  Returns:
    IPV6_ADDR_STRUCT * - The selected source address.

  Remarks:
    None
  ***************************************************************************/
IPV6_ADDR_STRUCT * TCPIP_IPV6_DASSourceAddressSelect(TCPIP_NET_HANDLE hNetIf, IPV6_ADDR * dest, IPV6_ADDR * requestedSource);


/*****************************************************************************
  Function:
    IPV6_PACKET * TCPIP_IPV6_TxPacketAllocate (TCPIP_NET_HANDLE netH, IPV6_PACKET_ACK_FNC ackFnc, void* ackParam);


  Summary:
    Dynamically allocates a packet for transmitting IP protocol data.

  Description:
    Dynamically allocates a packet for transmitting IP protocol data.

  Precondition:
    None

  Parameters:
    netH        - Interface of the outgoing packet.
    ackFnc      - function to be called when IP is done with the TX packet
                  (finished transmitting)
    ackParam    - parameter to be used for this callback
                  This has meaning only for the caller of the
                  TCPIP_IPV6_TxPacketAllocate

  Returns:
    IPV6_PACKET * - Pointer to the allocated packet.

  Remarks:
    None
  ***************************************************************************/
IPV6_PACKET * TCPIP_IPV6_TxPacketAllocate(TCPIP_NET_HANDLE netH, IPV6_PACKET_ACK_FNC ackFnc, void* ackParam);


/*****************************************************************************
  Function:
    unsigned short TCPIP_IPV6_TxIsPutReady (IPV6_PACKET * ptrPacket,
        unsigned short count)

  Summary:
    Determines whether a TX packet can be written to.

  Description:
    Determines whether a TX packet can be written to.  This function will
    allocate additional space to the packet to accomodate the user.

  Precondition:
    None

  Parameters:
    ptrPacket - The packet to check.
    count - The amount of writable space to check for,

  Returns:
    unsigned short - The amount of space available.

  Remarks:
    None
  ***************************************************************************/
unsigned short TCPIP_IPV6_TxIsPutReady(IPV6_PACKET * pkt, unsigned short count);


/*****************************************************************************
  Function:
    void TCPIP_IPV6_PacketFree (IPV6_PACKET * ptrPacket)

  Summary:
    Frees a TCP/IP Packet structure from dynamic memory.

  Description:
    Frees a TCP/IP Packet structure from dynamic memory.

  Precondition:
    None

  Parameters:
    ptrPacket - The packet to free.

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void TCPIP_IPV6_PacketFree(IPV6_PACKET * pkt);


/*****************************************************************************
  Function:
    bool TCPIP_IPV6_Put (IPV6_PACKET * pkt, unsigned char v)

  Summary:
    Writes a character of data to a packet.

  Description:
    Writes a character of data to a packet.

  Precondition:
    None

  Parameters:
    pkt - The packet.
    v - The characeter.

  Returns:
    true if the character was written, false otherwise

  Remarks:
    None
  ***************************************************************************/
bool TCPIP_IPV6_Put(IPV6_PACKET * pkt, unsigned char v);


/*****************************************************************************
  Function:
    unsigned short TCPIP_IPV6_ArrayPutHelper (IPV6_PACKET * ptrPacket, const void * dataSource, uint8_t dataType, unsigned short len)

  Summary:
    Helper function to write data to a packet.

  Description:
    Helper function to write data to a packet.

  Precondition:
    None

  Parameters:
    ptrPacket - The packet.
    dataSource - The address of the data on its medium.
    dataType - Descriptor of the data type (dynamic memory on PIC, in a
                    network FIFO, in static PIC RAM)
    len - Length of the data.

  Returns:
    unsigned short - The number of bytes of data written.

  Remarks:
    None
  ***************************************************************************/
unsigned short TCPIP_IPV6_ArrayPutHelper(IPV6_PACKET * pkt, const void * dataSource, uint8_t dataType, unsigned short len);


/******************************************************************************
  Function:
        unsigned short TCPIP_IPV6_PutArray (IPV6_PACKET * ptrPacket, const void * dataSource, unsigned short len)

  Summary:
        Writes data to a packet

  Description:
        Writes data to an outgoing packet.

  Precondition:
        The TCPIP_IPV6_TxIsPutReady function must have returned a value greater
    than or equal to 'len.'

  Parameters:
        ptrPacket - The packet.
    dataSource - Pointer to the data to copy to the packet.
    len - Length of the data.

  Returns:
        unsigned short - The number of bytes of data written.

  Remarks:
        None
 */
#define TCPIP_IPV6_PutArray(pkt,data,len)  TCPIP_IPV6_ArrayPutHelper(pkt, data, IPV6_DATA_PIC_RAM, len)


/*****************************************************************************
  Function:
    unsigned short TCPIP_IPV6_PayloadSet (IPV6_PACKET * ptrPacket, uint8_t* payload, unsigned short len)

  Summary:
    Allocates a segment on the end of a packet segment chain and uses it to
    address pre-buffered data.

  Description:
    This function will allocate a data segment header and append it to the
    end of a chain of segments in a TX packet.  It will set the data ptr in
    the packet segment to a pre-existing buffer of data.

  Precondition:
    None

  Parameters:
    ptrPacket - The packet.
    payload - Address of the data payload.
    len - Length of the data payload

  Returns:
    unsigned short - The amount of data added to the packet length.

  Remarks:
    This function is useful for adding payloads to outgoing packets without
    copying them if the data is in another preexisting buffer (i.e. TCP).
  ***************************************************************************/
unsigned short TCPIP_IPV6_PayloadSet(IPV6_PACKET * pkt, uint8_t* payload, unsigned short len);


/*****************************************************************************
  Function:
    int TCPIP_IPV6_Flush (IPV6_PACKET * ptrPacket)

  Summary:
    Flushes an IP TX packet.

  Description:
    Flushes an IP TX packet.  Determines the link-layer address if necessary.
    Calculates the upper-layer checksum if necessary.

  Precondition:
    None

  Parameters:
    ptrPacket - The packet to flush.

  Returns:
    1   - if the packet has been transmitted
    0   - if the packet has been queued.
    < 0 - if the packet has been discarded for some error

  Remarks:
    None
  ***************************************************************************/
int TCPIP_IPV6_Flush(IPV6_PACKET * pkt);


/******************************************************************************
  Function:
        uint8_t TCPIP_IPV6_Get (TCPIP_MAC_PACKET* pRxPkt, uint8_t* pData)

  Summary:
        Reads the next byte of data from the specified MAC.

  Description:
    Reads a character of data from a packet.

  Precondition:
        None

  Parameters:
        pRxPkt - The MAC RX packet to read data from

  Returns:
    The data read.

  Remarks:
        None
 */
uint8_t TCPIP_IPV6_Get (TCPIP_MAC_PACKET* pRxPkt, uint8_t* pData);


/******************************************************************************
  Function:
        uint8_t TCPIP_IPV6_ArrayGet (TCPIP_MAC_PACKET* pRxPkt, uint8_t *val,
        uint16_t len);

  Summary:
        Reads the next byte of data from the specified MAC.

  Description:
    Reads a character of data from a packet.

  Precondition:
        None

  Parameters:
        pRxPkt - The MAC RX packet to read data from
    val - The buffer to store the data
    len - The amount of data to read

  Returns:
    uint8_t - The number of bytes read.

  Remarks:
        None
 */
uint8_t TCPIP_IPV6_ArrayGet (TCPIP_MAC_PACKET* pRxPkt, uint8_t *val, uint16_t len);


/*****************************************************************************
  Function:
    void  TCPIP_IPV6_DestAddressSet(IPV6_PACKET * p, const IPV6_ADDR * addr)

  Summary:
    Sets the destination address for an IPv6 packet.

  Description:
    Sets the destination address for an IPv6 packet.

  Precondition:
    None.

  Parameters:
    p - pointer to IPv6 packet
    addrValue - destination address

  Returns:
    None.

  Remarks:
    None
 */
void  TCPIP_IPV6_DestAddressSet(IPV6_PACKET * p, const IPV6_ADDR * addr);


/*****************************************************************************
  Function:
    IPV6_ADDR *  TCPIP_IPV6_DestAddressGet(IPV6_PACKET * p)

  Summary:
    Gets the destination address for an IPv6 packet.

  Description:
    Gets the destination address for an IPv6 packet.

  Precondition:
    None.

  Parameters:
    p - pointer to IPv6 packet

  Returns:
    Destination address.

  Remarks:
    None.
 */
IPV6_ADDR *  TCPIP_IPV6_DestAddressGet(IPV6_PACKET * p);


/*****************************************************************************
  Function:
    void  TCPIP_IPV6_SourceAddressSet(IPV6_PACKET * p, const IPV6_ADDR * addr)

  Summary:
    Sets the source address for an IPv6 packet.

  Description:
    Sets the source address for an IPv6 packet.

  Precondition:
    None.

  Parameters:
    p - pointer to IPv6 packet
    addrValue - source address

  Returns:
    None.

  Remarks:
    None
 */
void  TCPIP_IPV6_SourceAddressSet(IPV6_PACKET * p, const IPV6_ADDR * addr);


/*****************************************************************************
  Function:
``  IPV6_ADDR *  TCPIP_IPV6_SourceAddressGet(IPV6_PACKET * p)

  Summary:
    Gets the source address for an IPv6 packet.

  Description:
    Gets the source address for an IPv6 packet.

  Precondition:

  Parameters:
    p - pointer to IPv6 packet

  Returns:
    Source address.

  Remarks:
    None.
 */
IPV6_ADDR *  TCPIP_IPV6_SourceAddressGet(IPV6_PACKET * p);


/*****************************************************************************
  Function:
    IPV6_ADDR_STRUCT * TCPIP_IPV6_UnicastAddressAdd (TCPIP_NET_HANDLE netH, IPV6_ADDR * address, int prefixLen, uint8_t skipProcessing)

  Summary:
    Adds a unicast address to a specified interface

  Description:
    Adds a unicast address to a specified interface.  Starts duplicate address
    detection if necessary.

  Precondition:
    None

  Parameters:
    netH            - The interface to add the address to.
    address         - The address to add.
    prefixLen       - The prefix length associated to this static address
                      (giving the subnet prefix length)
                      if 0, the default value of 64 will be used
    skipProcessing  - true to skip Duplicate address detection, false otherwise

  Returns:
    IPV6_ADDR_STRUCT * - Pointer to the structure of the newly allocated
        address

  Remarks:
    The RFC (4291) requires the interface ID for all unicast addresses,
    (except those that start with the binary value 000)
    to be 64 bits long and to be constructed in Modified EUI-64 format.
    Therefore the prefixLen parameter should probably always be 64.

  ***************************************************************************/
IPV6_ADDR_STRUCT * TCPIP_IPV6_UnicastAddressAdd(TCPIP_NET_HANDLE netH, IPV6_ADDR * address, int prefixLen, uint8_t skipProcessing);


/*****************************************************************************
  Function:
    void TCPIP_IPV6_AddressUnicastRemove(TCPIP_NET_HANDLE netH, IPV6_ADDR * address)

  Summary:
    Removed a configured unicast address from an interface.

  Description:
    Removed a configured unicast address from an interface.

  Precondition:
    None

  Parameters:
    netH    - The interface.
    address - The address

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void TCPIP_IPV6_AddressUnicastRemove(TCPIP_NET_HANDLE netH, IPV6_ADDR * address);


/*****************************************************************************
  Function:
    IPV6_ADDR_STRUCT * TCPIP_IPV6_MulticastListenerAdd(TCPIP_NET_HANDLE netH, IPV6_ADDR * address)

  Summary:
    Adds a multicast listener to an interface.

  Description:
    Adds a multicast listener to an interface.

  Precondition:
    None

  Parameters:
    pNetIf - The interface to add the address to.
    address - The new listener

  Returns:
    IPV6_ADDR_STRUCT * - Pointer to the new listener, or NULL

  Remarks:
    None
  ***************************************************************************/
IPV6_ADDR_STRUCT * TCPIP_IPV6_MulticastListenerAdd(TCPIP_NET_HANDLE hNet, IPV6_ADDR * address);


/*****************************************************************************
  Function:
    void TCPIP_IPV6_MulticastListenerRemove (TCPIP_NET_HANDLE netH, IPV6_ADDR * address)

  Summary:
    Removes a multicast listener from a given interface.

  Description:
    Removes a multicast listener from a given interface.

  Precondition:
    None

  Parameters:
    netH  - The interface
    address - The address

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void TCPIP_IPV6_MulticastListenerRemove(TCPIP_NET_HANDLE netH, IPV6_ADDR * address);


/**************************************************************************************************************************************************************
  Function:
      IPV6_ULA_RESULT TCPIP_IPV6_UniqueLocalUnicastAddressAdd (TCPIP_NET_HANDLE netH, uint16_t subnetID, IPV6_ULA_FLAGS genFlags, IP_MULTI_ADDRESS* ntpAddress)
    
  Summary:
    Adds a Unique Local Unicast Address (ULA) to a specified interface
  Description:
    This function starts the process of adding an ULA address to the
    specified interface. The segments of the generated address are as
    follows:
    - FC00::/7     - ULA prefix
    - L            - 1 bit set to 1, locally assigned
    - Global ID    - 40 bit random generated identifier
    - subnet ID    - 16 bit subnet identifier
    - Interface ID - 64 bit interface identifier generated as a EUI64 from the 
                     specified interface MAC.
    
    The randomness of the "Global ID" prefix of the generated IPv6 address
    is obtained by using an NTP server. The supplied NTP server will be
    contacted to obtain an NTP timestamp. This timestamp together with the
    EUI64 identifier obtained from the interface MAC are passed through a
    160 bits hash algorithm (SHA1) and the least significant 40 bits are
    used as the GlobalID of the interface.
  Conditions:
    None.
  Input:
    netH -        The interface to add the address to.
    subnetID -    The subnet ID to be used.
    genFlags -    Address generation flags\:
                  * IPV6_ULA_FLAG_NTPV4
                    * if set, the ntpAddress is an IPv4 address and the NTP
                      server will be contacted over an IPv4 connection
                    * otherwise, a default IPv6 connection will be attempted
                  * IPV6_ULA_FLAG_GENERATE_ONLY
                    * if set, the address will not be added to the list of
                      the addresses for the specified interface
                  * IPV6_ULA_FLAG_SKIP_DAD
                    * if set, the DAD processing will be skipped
    ntpAddress -  The NTP server address \-\- it's an IPv4/IPv6 address as
                  selected by the IPV6_ULA_FLAG_NTPV4 flag (the IP address
                  could be obtained with an DNS call into the stack)
  Return:
    IPV6_ULA_RES_OK - if the call succeeded and the generation process was
    started an error code otherwise
  Remarks:
    Only one address generation at a time is supported for now. Before
    attempting a new address generation the previous operation has to be
    completed, otherwise the call will fail.
    
    This function requires that the NTP client is enabled in the stack. If
    not, the call will fail.
    
    The caller will be notified by the outcome of the operation by the
    stack using the standard IPv6 notification handler (registered by
    TCPIP_IPV6_HandlerRegister() call).                                                                                                                        
  **************************************************************************************************************************************************************/
IPV6_ULA_RESULT    TCPIP_IPV6_UniqueLocalUnicastAddressAdd (TCPIP_NET_HANDLE netH, uint16_t subnetID, IPV6_ULA_FLAGS genFlags, IP_MULTI_ADDRESS* ntpAddress);


/*****************************************************************************
  Function:
    bool    TCPIP_IPV6_RouterAddressAdd(TCPIP_NET_HANDLE netH, IPV6_ADDR * rAddress, unsigned long validTime, int flags);

  Summary:
    Adds a new router address to a specified interface

  Description:
    Adds a unicast address as a routing addressto a specified interface.

  Precondition:
    rAddress pointer to a valid IPv6 router address
    IPv6 stack initialized, interface up and configured

  Parameters:
    netH            - The interface to add the address to.
    rAddress        - The router address to add.
    validTime       - The time this valid will be valid, seconds
                      If 0, the entry will be valid forever
    flags           - Creation flags
                      Not used for now, should be 0

  Returns:
    true  - operation succeeded
    false - operation failed (interface not valid, interface still configuring, no memory, etc.)

  Remarks:
    The validTime parameter is relevant for an existent router on the network.
    If such router does not exist the stack will eventually discard the entry automatically.

  ***************************************************************************/
bool    TCPIP_IPV6_RouterAddressAdd(TCPIP_NET_HANDLE netH, IPV6_ADDR * rAddress, unsigned long validTime, int flags);

/*****************************************************************************
  Function:
    IPV6_HANDLE TCPIP_IPV6_HandlerRegister(TCPIP_NET_HANDLE hNet, IPV6_EVENT_HANDLER handler, const void* hParam)

  Summary:
    Registers an IPv6 event handler callback function.

  Description:
    Registers an IPv6 event handler callback function.

  Precondition:
    None

  Parameters:
    netH  - The interface
    handler - event handler
    hParam -

  Returns:
    Handle to registered callback.

  Remarks:
    None
  ***************************************************************************/
IPV6_HANDLE TCPIP_IPV6_HandlerRegister(TCPIP_NET_HANDLE hNet, IPV6_EVENT_HANDLER handler, const void* hParam);


/*****************************************************************************
  Function:
    bool TCPIP_IPV6_HandlerDeregister(IPV6_HANDLE hIpv6)

  Summary:
    Deregisters an IPv6 event handler callback function.

  Description:
    Deregisters an IPv6 event handler callback function.

  Precondition:
    None

  Parameters:
    hIpv6 - Handle to registered callback

  Returns:
    true - if deregister successful
    false - otherwise.

  Remarks:
    None
  ***************************************************************************/
bool TCPIP_IPV6_HandlerDeregister(IPV6_HANDLE hIpv6);


#endif // __IPV6_H_



