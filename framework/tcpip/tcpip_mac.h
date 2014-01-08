/*******************************************************************************
  MAC Module Defs for Microchip Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
    tcpip_mac.h

  Summary:
    
  Description:
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

#ifndef __TCPIP_MAC_H_
#define __TCPIP_MAC_H_

#include <stdint.h>
#include <stdbool.h>

#include "../driver/ethmac/drv_ethernet_flags.h"

// *****************************************************************************
// *****************************************************************************
// Section: MAC interface definitions
// *****************************************************************************
// *****************************************************************************

// Structure to contain a MAC address
typedef struct __attribute__((__packed__))
{
    uint8_t v[6];
} TCPIP_MAC_ADDR;


// A generic structure representing the Ethernet header starting all Ethernet
// frames
typedef struct  __attribute__((aligned(2), packed))
{
    TCPIP_MAC_ADDR            DestMACAddr;
    TCPIP_MAC_ADDR            SourceMACAddr;
    uint16_t            Type;
} TCPIP_MAC_ETHERNET_HEADER;
        
// MAC initialization data
// Each supported MAC has its own specific init/configuration data

typedef struct
{
}TCPIP_MODULE_MAC_ENCJ60_CONFIG;


typedef struct
{
}TCPIP_MODULE_MAC_ENCJ600_CONFIG;

typedef struct
{
}TCPIP_MODULE_MAC_97J60_CONFIG;

typedef struct
{
    int                 nTxDescriptors; // number of TX descriptors
    int                 rxBuffSize;     // size of the corresponding RX buffer
    int                 nRxDescriptors; // number of RX descriptors
    ETH_OPEN_FLAGS      ethFlags;       // flags to use for the ETH connection
    ETHPHY_CONFIG_FLAGS phyFlags;       // PHY configuration 
    int                 linkInitDelay;  // PHYs initialization delay (milliseconds)
                                        // for insuring that the PHY is ready to transmit data.
}TCPIP_MODULE_MAC_PIC32INT_CONFIG;

typedef struct
{
}TCPIP_MODULE_MAC_MRF24W_CONFIG;



typedef const void* TCPIP_MAC_HANDLE;     // handle to a MAC

// *****************************************************************************
/*  MAC Data Segment Definitions */


// *****************************************************************************
/*  MAC Segment Flags

  Summary:
    Flags belonging to MAC data segment.

  Description:
    This enumeration contains the definitions of MAC segment flags.
  
  Notes:
*/


typedef enum
{
    // general segment allocation flags
    TCPIP_MAC_SEG_FLAG_STATIC       = 0x0001,       // segment can not be dynamically deallocated
                                                    // set when the segment is allocated
    TCPIP_MAC_SEG_FLAG_TX           = 0x0002,       /********************************************************************
                                                      if set, it's a TX segment; otherwise, is a RX packet available user
                                                      segment flags start here                                           
                                                      ********************************************************************/
    TCPIP_MAC_SEG_FLAG_USER         = 0x0100,


}TCPIP_MAC_SEGMENT_FLAGS;        // 16 bits only segment flags!

// *****************************************************************************
/*  TCPIP MAC Data Segment

  Summary:
    A data segment that's part of a TX/RX packet.

  Description:
    Structure of a segment buffer transferred with the MAC.
    A MAC TX or RX packet can consist of multiple data segments.
    On TX the MAC has to be able to transmit packets that span
    multiple data segments.
    On RX of a network frame the MAC may have to use multiple segments to 
    construct a packet.
    (For performance reasons, a contiguous MAC packet, with just one segment, if possible, is preferred).
   
  
  Remarks:
    See notes for the segLoadOffset member.

    On 32 bit machines the segment payload is allocated so that it is always
    32 bit aligned and its size is 32 bits multiple.
    The segLoadOffset adds to the payload address and insures that the network layer data
    is 32 bit aligned.

*/


typedef struct _tag_MAC_DATA_SEGMENT
{
    struct _tag_MAC_DATA_SEGMENT* next;      // multi-segment support, next segment in the chain
    uint8_t*                 segLoad;        // pointer to segment data payload
                                             // this specifies the address of the 1st byte to be transmitted.
                                             // A number of segLen bytes will be transmitted.
    uint16_t                 segLen;         // segment payload size; this number of bytes from this segment 
                                             // has to be transmitted
    uint16_t                 segSize;        // segment allocated total usable size
                                             // this does not include the segLoadOffset (see below).
    uint16_t                 segFlags;       // TCPIP_MAC_SEGMENT_FLAGS segment flags:
                                             // TCPIP_MAC_SEG_FLAG_STATIC and TCPIP_MAC_SEG_FLAG_RX, TCPIP_MAC_SEG_FLAG_RX
    uint16_t                 segLoadOffset;  // offset in bytes between the address pointed by segLoad
                                             // and the address where the segment buffer starts/was allocated;
                                             // It specifies some available space at the beginning of the 
                                             // segment buffer.
                                             // Note 1. This offset is used as a performance improvement.
                                             // It allows for the MAC frame to start on an analigned address
                                             // but enforces the alignment of the network layer data and
                                             // improves the IP checksum calculation.
                                             // The value of this offset is MAC dependent.
                                             // A typical value for an Ethernet MAC should be 2 bytes
                                             // (size of the MAC frame is 14 bytes).
                                             // Note 2. Normally only the 1st segment of a packet needs
                                             // this extra room at the begining of the segment buffer.
                                             // Note 3. The MAC may make use of this space at the beginning of the
                                             // segment buffer. This is a space reserved for the MAC purposes.
                                             // Note 4. It is up to the MAC to check that the value of this offset is enforced.
                                             //
                                             // PIC32 MAC specific notes:
                                             //     1. The MAC will reject the packet if the load offset is not at least 2 bytes.
                                             //     2. The PIC32 MAC uses these 2 bytes to calculate the offset between the segLoad
                                             //        and the TCPIP_MAC_PACKET packet it belongs to.
                                             //        That means that the TCPIP_MAC_PACKET* and the segLoad cannot be
                                             //        more than 64 KB apart!
                                             //
    // additional client segment data; ignored by the MAC driver 
    uint8_t                  segClientData[4];
    // additional client segment payload; ignored by the MAC driver 
    uint8_t                  segClientLoad[0];
}TCPIP_MAC_DATA_SEGMENT;




// *****************************************************************************
/*  MAC Data Packet Definitions */


// *****************************************************************************
/*  Received Packet Status

  Summary:
    Status of a received packet.

  Description:
    This structure contains the status of a received packet.
  
  Notes:
    Not all the MACs have hardware support for the received packet status.

*/

typedef struct __attribute__ ((__packed__))
{

    // correct checksum filled in
    unsigned        chksumOk        : 1;
    // Packet payload checksum
    unsigned        pktChecksum     :16;

    // Runt packet received
    unsigned        runtPkt         : 1;

    // Unicast, not me packet,
    unsigned        notMeUcast      : 1;

    // Hash table match
    unsigned        htMatch         : 1;

    // Magic packet match
    unsigned        magicMatch      : 1;

    // Pattern match match
    unsigned        pmMatch         : 1;

    // Unicast match
    unsigned        uMatch          : 1;

    // Broadcast match
    unsigned        bMatch          : 1;

    // Multicast match
    unsigned        mMatch          : 1;

    // Received bytes
    unsigned        rxBytes         :16;

    // CRC error in packet
    unsigned        crcError        : 1;

    // Receive length check error
    unsigned        lenError        : 1;

    // Receive length out of range
    unsigned        lenRange        : 1;

    // Receive OK
    unsigned        rxOk            : 1;

    // Multicast packet
    unsigned        mcast           : 1;

    // Broadcast packet
    unsigned        bcast           : 1;

    // Control frame received
    unsigned        rxCtrl          : 1;

    // Received VLAN tagged frame
    unsigned        rxVLAN          : 1;

}TCPIP_MAC_PACKET_RX_STAT;


/*****************************************************************************/
/*  MAC Packet Flags

  Summary:
    Flags belonging to MAC packet.

  Description:
    This enumeration contains the definitions of MAC packet flags.
  
  Notes:
*/


typedef enum
{
    // general packet allocation flags
    TCPIP_MAC_PKT_FLAG_STATIC       = 0x0001,       // packet/segment can not be dynamically deallocated
                                                    // set when the packet is allocated
    TCPIP_MAC_PKT_FLAG_TX           = 0x0002,       // if set, it is a TX packet/segment; otherwise, it is a RX packet
    TCPIP_MAC_PKT_FLAG_SPLIT        = 0x0004,       // packet data spans multiple segments - ZC functionality
                                                    // if not set the packet has only one data segment 
                                                    // set by the MAC driver when a RX packet spans multiple
                                                    // data segments
    TCPIP_MAC_PKT_FLAG_QUEUED       = 0x0008,       // packet data is queued somewhere, cannot be freed
                                                    // flag is set by the packet source when the packet is passed for further processing to a destination
                                                    // cleared by the packet destination when the packet processing was completed.
                                                    
    // RX packets flags
    TCPIP_MAC_PKT_FLAG_UNICAST      = 0x0010,      // MAC updated: it's an unicast packet
    TCPIP_MAC_PKT_FLAG_BCAST        = 0x0020,      // MAC updated: it's a broadcast packet
    TCPIP_MAC_PKT_FLAG_MCAST        = 0x0040,      // MAC updated: it's an multicast packet
    TCPIP_MAC_PKT_FLAG_CAST_MASK    = 0x0070,      // packet cast mask bits
    TCPIP_MAC_PKT_FLAG_CAST_DISABLED= 0x0000,      // if all zeroes MAC packet MCAST/BCAST fields are not updated by the MAC RX process
    
    // available user flags start here
    //
    TCPIP_MAC_PKT_FLAG_USER         = 0x0100,


}TCPIP_MAC_PACKET_FLAGS;        // 16 bits only packet flags!



// prototype of a MAC packet acknowledge function
// Once an TX/RX packet is done, the MAC will call the associated acknowledge function

typedef enum
{
    TCPIP_MAC_PKT_ACK_NONE              = 0,    // packet result unknown, unspecified
    // TX success code - positive
    TCPIP_MAC_PKT_ACK_TX_OK             = 1,    // packet was transmitted successfully
    // RX success code - positive
    TCPIP_MAC_PKT_ACK_RX_OK             = 2,    // packet was received/processed successfully
    // TX error codes - negative
    TCPIP_MAC_PKT_ACK_LINK_DOWN         = -1,   // packet was dropped because the link was down
    TCPIP_MAC_PKT_ACK_NET_DOWN          = -2,   // packet was dropped because the network is down
    TCPIP_MAC_PKT_ACK_BUFFER_ERR        = -3,   // packet was dropped because the buffer type is not supported
    TCPIP_MAC_PKT_ACK_ARP_TMO           = -4,   // packet was dropped because of an ARP timeout
    TCPIP_MAC_PKT_ACK_ARP_NET_ERR       = -5,   // packet associated interface is down or non existent
    //
    // RX error codes - negative
    TCPIP_MAC_PKT_ACK_CHKSUM_ERR        = -10,  // packet was dropped because the checksum was incorrect
    TCPIP_MAC_PKT_ACK_SOURCE_ERR        = -11,  // packet was dropped because of wrong interface source address
    TCPIP_MAC_PKT_ACK_TYPE_ERR          = -12,  // packet was dropped because the type was unknown
    TCPIP_MAC_PKT_ACK_STRUCT_ERR        = -13,  // internal packet structure error
    TCPIP_MAC_PKT_ACK_PROTO_DEST_ERR    = -14,  // the packet protocol couldn't find a destination for it
    TCPIP_MAC_PKT_ACK_FRAGMENT_ERR      = -15,  // the packet too fragmented
    TCPIP_MAC_PKT_ACK_PROTO_DEST_CLOSE  = -16,  // the packet destination is closing
    TCPIP_MAC_PKT_ACK_ALLOC_ERR         = -17,  // memory allocation error
    
    
}TCPIP_MAC_PKT_ACK_RES;         // list of return codes for a packet acknowledge function
                                // 16 bits only acknowledge results!






// forward declaration
typedef struct _tag_TCPIP_MAC_PACKET    TCPIP_MAC_PACKET;

typedef void    (*TCPIP_MAC_PACKET_ACK_FUNC)(TCPIP_MAC_PACKET* pkt,  const void* param);


// *****************************************************************************
/*  MAC Packet

  Summary:
    A TX/RX packet descriptor.

  Description:
    Structure of a packet transferred with the MAC.
    This is the structure used for both TX and RX.
    See the description of each individual field.

  Remarks:
    Specific TCP/IP stack implementations might offer packet support functions
    to assist in driver development.
    (For the MCHP TCP/IP stack see tcpip_packet.h)
*/
struct _tag_TCPIP_MAC_PACKET
{
    struct _tag_TCPIP_MAC_PACKET*   next;           // multi-packet/ queing support
                                                    // This field is used for chaining/queuing packets.
    TCPIP_MAC_PACKET_ACK_FUNC       ackFunc;        // packet acknowledgement function
                                                    // Since packets may be dynamically allocated, an acknowledge function can result
                                                    // in data de-allocation. Therefore the acknowledgement function should NOT be called
                                                    // from within an interrupt context!
                                                    // On TX: A stack module owns the packet.
                                                    //  Once the MAC is done transmitting the packet (success or failure)
                                                    //  it has to set an appropriate acknowledge result in the ackRes field ( a TCPIP_MAC_PKT_ACK_RES)
                                                    //  adjust some packet flags (see TCPIP_MAC_PKT_FLAG_QUEUED) and call the packet acknowledge function (ackFunc).
                                                    //  This call informs the packet owner that the MAC is done with using that packet.
                                                    //  It is up to the implementation what action the ackFunc takes: reuse, free, discard the packet or if
                                                    //  some of the above steps are included in the ackFunc itself.
                                                    // On RX: The packet is under the MAC control and it's passed to the stack
                                                    //  when it contains valid data.
                                                    //  Once the recipient of the packet (IP, ICMP, UDP, TCP, etc.) is done with the packet processing
                                                    //  it has to set an appropriate acknowledge result in the ackRes field ( a TCPIP_MAC_PKT_ACK_RES)
                                                    //  adjust some packet flags (see TCPIP_MAC_PKT_FLAG_QUEUED) and call the packet acknowledge function (ackFunc).
                                                    //  This call informs the packet owner that the processing of the packet is completed.
                                                    //  It is up to the implementation what action the ackFunc takes: reuse, free, discard the packet or if
                                                    //  some of the above steps are included in the ackFunc itself.
    const void*                     ackParam;       // associated acknowledgement parameter to be used when ackFunc is called
                                                    // For TX packets: this is a client supplied parameter and
                                                    // is not used by the MAC driver
                                                    // For RX: If the MAC owns the RX packet then the MAC driver can use this field
                                                    // for further dispatching in the MAC driver owned acknoledgment function. 
    TCPIP_MAC_DATA_SEGMENT*         pDSeg;          // data (root) segment associated to this packet
                                                    // It is up to the design if the root data segment associated with a packet
                                                    // is contiguous in memory with the packet itself
                                                    // It can be 0 if the packet has no associated data.
    uint8_t*                        pMacLayer;      // pointer to the MAC frame
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    // on RX: the MAC driver updates this field before handing over the packet.
                                                    // (MCHP TCP/IP stack note: The packet allocation function update this field automatically).
    uint8_t*                        pNetLayer;      // pointer to the network layer data
                                                    // The MAC driver shouldn't need this field
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    // on RX: the MAC driver updates this field before handing over the packet.
                                                    // (MCHP TCP/IP stack note: The packet allocation function update this field automatically).
    uint8_t*                        pTransportLayer;// pointer to the transport layer
                                                    // The MAC driver shouldn't need this field
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    // on RX: the MAC driver updates this field before handing over the packet.
                                                    // (MCHP TCP/IP stack note: The packet allocation function update this field automatically).
    uint16_t                        totTransportLen;// total length of the transport layer
                                                    // The MAC driver shouldn't need this field
    uint16_t                        pktFlags;       // TCPIP_MAC_PACKET_FLAGS associated packet flags
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    // on RX: the MAC driver updates this field before handing over the packet.
                                                    // Flags that the MAC driver has to set/clear:
                                                    //      TCPIP_MAC_PKT_FLAG_RX
                                                    //         and TCPIP_MAC_PKT_FLAG_UNICAST, TCPIP_MAC_PKT_FLAG_BCAST and TCPIP_MAC_PKT_FLAG_MCAST
                                                    //      TCPIP_MAC_PKT_FLAG_QUEUED
                                                    //      TCPIP_MAC_PKT_FLAG_SPLIT
    uint32_t                        tStamp;         // time stamp value
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    //      The MAC driver shouldn't need this field
                                                    // on RX: the MAC driver updates this field before handing over the packet.
    const void*                     pktIf;          // packet interface
                                                    // on TX: the sending higher layer protocol updates this field.
                                                    //      The MAC driver doesn't use this field
                                                    // on RX: the receiving higher level protocol updates this value
                                                    //      The MAC driver doesn't use this field
    int16_t                         ackRes;         // a TCPIP_MAC_PKT_ACK_RES code associated with the packet
                                                    // on TX: The MAC driver sets this field when calling the packet ackFunc
                                                    // on RX: The higher level protocol which is the recipient of the packet
                                                    //       sets this field when calling the packet ackFunc
    //
    uint16_t                        pktClientData;  // client/padding data; ignored by the MAC driver
                                                    // can be used by the packet client.


    // additional client packet payload; ignored by the MAC driver 
    uint32_t                        pktClientLoad[0];// variable packet data
};


typedef enum
{
    TCPIP_MAC_RES_OK                = 0,   // operation successful
    // benign operation results - positive codes
    TCPIP_MAC_RES_PENDING           = 1,    // operation is pending upon some hardware resource
                                            // call again to completion
    // error codes - negative
    TCPIP_MAC_RES_TYPE_ERR          = -1,   // unsupported type
    TCPIP_MAC_RES_IS_BUSY           = -2,   // device is in use
    TCPIP_MAC_RES_INIT_FAIL         = -3,   // generic initialization failure
    TCPIP_MAC_RES_PHY_INIT_FAIL     = -4,   // PHY initialization failure
    TCPIP_MAC_RES_EVENT_INIT_FAIL   = -5,   // Event system initialization failure
    TCPIP_MAC_RES_OP_ERR            = -6,   // unsupported operation
    TCPIP_MAC_RES_ALLOC_ERR         = -7,   // memory allocation error
    TCPIP_MAC_RES_INSTANCE_ERR      = -8,   // already instantiated, initialized error
    TCPIP_MAC_RES_FRAGMENT_ERR      = -9,   // too fragmented, RX buffer too small
    TCPIP_MAC_RES_PACKET_ERR        = -10,  // unsupported/corrupted packet error
    TCPIP_MAC_RES_QUEUE_TX_FULL     = -11,  // TX queue exceeded the limit
    
    
}TCPIP_MAC_RES;         // list of return codes from MAC functions


// *****************************************************************************
// *****************************************************************************
// Section: MAC interface Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* TCP/IP MAC Action

  Summary:
    Network interface action for initialization/de-initialization

  Description:

  Remarks:

*/

typedef enum
{
    TCPIP_MAC_ACTION_INIT,         // stack is initialized 
    TCPIP_MAC_ACTION_REINIT,       // stack is re-initialized
    TCPIP_MAC_ACTION_DEINIT,       // stack is de-initialized
    TCPIP_MAC_ACTION_IF_UP,        // interface is brought up 
    TCPIP_MAC_ACTION_IF_DOWN,      // interface is brought down
}TCPIP_MAC_ACTION;


// supported MAC power mode state
typedef enum
{
    TCPIP_MAC_POWER_NONE,     // unknown power mode; 
    TCPIP_MAC_POWER_FULL,     // up and running; valid for init/re-init
    TCPIP_MAC_POWER_LOW,      // low power mode; valid for init/re-init
    TCPIP_MAC_POWER_DOWN,     // interface is down;
}TCPIP_MAC_POWER_MODE;

// *****************************************************************************
/* TCP/IP MAC Event

  Summary:
    Defines the possible event types.

  Description:
    TCP/IP MAC Events Codes
    
    This enumeration defines all the possible events that can be reported
    by the MAC to the stack.
    
    Depending on the type of the hardware Ethernet/Wi-Fi interface, etc.,
    not all events are possible.

  Remarks:

*/

typedef enum
{
    // no event
    TCPIP_MAC_EV_NONE               = 0x0000,
    
    // RX triggered events: A receive packet is pending
    TCPIP_MAC_EV_RX_PKTPEND         = 0x0001,

    // RX triggered events: RX FIFO overflow (system level latency, no descriptors, etc.)
    TCPIP_MAC_EV_RX_OVFLOW          = 0x0002,

    // RX triggered events: no RX descriptor available to receive a new packet
    TCPIP_MAC_EV_RX_BUFNA           = 0x0004,

    // RX triggered events: There's RX data available
    TCPIP_MAC_EV_RX_ACT             = 0x0008,

    // RX triggered events: A packet was sucessfully received
    TCPIP_MAC_EV_RX_DONE            = 0x0010,

    // RX triggered events: the number of received packets is greater than or equal to than the RX Full Watermark
    TCPIP_MAC_EV_RX_FWMARK          = 0x0020,

    // RX triggered events: the number of received packets is less than or equal to than the RX Empty Watermark
    TCPIP_MAC_EV_RX_EWMARK          = 0x0040,

    // RX triggered events: a bus error encountered during an RX transfer
    TCPIP_MAC_EV_RX_BUSERR          = 0x0080,

    // TX triggered events: A packet was transmitted and its status is available
    TCPIP_MAC_EV_TX_DONE            = 0x0100,          

    // TX triggered events: a TX packet was aborted by the MAC (jumbo/system underrun/excessive defer/late collision/excessive collisions)
    TCPIP_MAC_EV_TX_ABORT           = 0x0200,

    // TX triggered events: a bus error encountered during a TX transfer
    TCPIP_MAC_EV_TX_BUSERR          = 0x0400,

    // Connection triggered events: Connection established
    TCPIP_MAC_EV_CONN_ESTABLISHED   = 0x0800,

    // Connection triggered events: Connection lost
    TCPIP_MAC_EV_CONN_LOST          = 0x1000,

    // Useful Masks: all RX related events
    TCPIP_MAC_EV_RX_ALL             = (TCPIP_MAC_EV_RX_PKTPEND|TCPIP_MAC_EV_RX_OVFLOW|TCPIP_MAC_EV_RX_BUFNA|TCPIP_MAC_EV_RX_ACT|TCPIP_MAC_EV_RX_DONE|TCPIP_MAC_EV_RX_FWMARK|TCPIP_MAC_EV_RX_EWMARK|TCPIP_MAC_EV_RX_BUSERR),

    // Useful Masks: all TX related events
    TCPIP_MAC_EV_TX_ALL            = (TCPIP_MAC_EV_TX_DONE|TCPIP_MAC_EV_TX_ABORT|TCPIP_MAC_EV_TX_BUSERR),

    // abnormal traffic/system events: Action should be taken accordingly by the stack (or the stack user)
    TCPIP_MAC_EV_RXTX_ERRORS        = (TCPIP_MAC_EV_RX_OVFLOW|TCPIP_MAC_EV_RX_BUFNA|TCPIP_MAC_EV_RX_BUSERR|TCPIP_MAC_EV_TX_ABORT|TCPIP_MAC_EV_TX_BUSERR),

    // Mask of all Connection related events
    TCPIP_MAC_EV_CONN_ALL            = (TCPIP_MAC_EV_CONN_ESTABLISHED|TCPIP_MAC_EV_CONN_LOST)

}TCPIP_MAC_EVENT;


//*******************************************************************************
    // memory allocation funcions

// handle to a heap
typedef const void* TCPIP_MAC_HEAP_HANDLE;

// malloc function
typedef void*   (*TCPIP_MAC_HEAP_MallocF)(TCPIP_MAC_HEAP_HANDLE heapH, size_t nBytes);

// calloc function
typedef void*   (*TCPIP_MAC_HEAP_CallocF)(TCPIP_MAC_HEAP_HANDLE heapH, size_t nElems, size_t elemSize);

// free function
typedef int     (*TCPIP_MAC_HEAP_FreeF)(TCPIP_MAC_HEAP_HANDLE heapH, const void* pBuff);

//*******************************************************************************
    // packet allocation funcions

// allocates a TCPIP_MAC_PACKET packet (TCPIP_MAC_ETHERNET_HEADER always added);
// pktLen - the size of the packet (it will be 32 bits rounded up)
// segLoadLen - the payload size for the segment associated to this packet; Payload is always 32 bit aligned
//              if 0 no segment is created/attached to the packet
typedef TCPIP_MAC_PACKET* (*TCPIP_MAC_PKT_AllocF)(uint16_t pktLen, uint16_t segLoadLen, TCPIP_MAC_PACKET_FLAGS flags);

// frees a previously allocated packet
// that neither the packet nor segments marked
// with TCPIP_MAC_PKT_FLAG_STATIC/TCPIP_MAC_SEG_FLAG_STATIC are not freed
// Also note that this function does not free explicitely the external segment payload.
// A payload that was created contiguously when the segment was created
// will be automatically freed by this function.
typedef void      (*TCPIP_MAC_PKT_FreeF)(TCPIP_MAC_PACKET* pPkt);


// acknowledges a packet
// clears the TCPIP_MAC_PKT_FLAG_QUEUED flag
// a packet should always have an acknowledgment function
// packet's ackRes is updated only if the parameter ackRes != TCPIP_MAC_PKT_ACK_NONE.
typedef void      (*TCPIP_MAC_PKT_AckF)(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_PKT_ACK_RES ackRes);


/*******************************************************************************
  event notification Function:
    typedef void    (*TCPIP_MAC_EventF)(TCPIP_MAC_EVENT event, const void* eventParam);

  Summary:
    MAC event notification handler.

  Description:
    This function describes the MAC event notification handler.
    This is a handler specified by the user of the MAC (the TCP/IP stack).
    The stack can use the handler to be notified of MAC events.
    Whenever a notification occurs the passed events have to be eventually processed:
    - Stack should process the TCPIP_EV_RX_PKTPEND/TCPIP_EV_RX_DONE, TCPIP_EV_TX_DONE  events
    - Process the specific (error) condition
    - Acknowledge the events by calling TCPIP_MAC_EventAcknowledge() so that they can be re-enabled.

  Precondition:
   None

  Parameters:
    event        - event that's reported (multiple events can be OR-ed)  
    eventParam   - user parameter that's used in the notification handler
    
  Returns:
   None


  Remarks:   
    The notification handler will be called from the ISR which detects the corresponding event.
    The event notification handler has to be kept as short as possible and non-blocking.
    Mainly useful for RTOS integration where this handler will wake-up a thread that waits for a MAC event to occur.

    The event notification system also enables the user of the TCPIP stack to call into the stack
    for processing only when there are relevant events rather than being forced to periodically call
    from within a loop at unknown moments.

    Without a notification handler the stack user can still call TCPIP_MAC_EventPendingGet() to see if processing by the stack needed.

    This is a default way of adding MAC interrupt processing to the TCP/IP stack.
*****************************************************************************/
typedef void    (*TCPIP_MAC_EventF)(TCPIP_MAC_EVENT event, const void* eventParam);

// specific MAC process flags
// multiple flags can be orred
typedef enum
{
    TCPIP_MAC_PROCESS_FLAG_NONE     = 0x0000, // the stack never has to call the TCPIP_MAC_Process function
    TCPIP_MAC_PROCESS_FLAG_RX       = 0x0001, // the stack has to call the TCPIP_MAC_Process after an RX signal
    TCPIP_MAC_PROCESS_FLAG_TX       = 0x0002, // the stack has to call the TCPIP_MAC_Process after an TX signal

    TCPIP_MAC_PROCESS_FLAG_ANY      = 0x0100, // the stack has to call the TCPIP_MAC_Process after any type of signal


}TCPIP_MAC_PROCESS_FLAGS;

// data that's passed as reference to MAC driver module init/deinit.
typedef struct
{
    // permanent data; this data is maintained by the stack for one full session
    // i.e. accross Initialize() -> DeInitialize() calls
    // number of the interfaces supported in this seession
    int     nIfs;         

    // transient data; contains info for a specific module call
    //
    //
    // allocation functions/parameters
    TCPIP_MAC_HEAP_MallocF  mallocF;
    TCPIP_MAC_HEAP_CallocF  callocF;
    TCPIP_MAC_HEAP_FreeF    freeF;
    TCPIP_MAC_HEAP_HANDLE   memH;   // handle to be used in the stack allocation service calls

    // packet allocation functions
    TCPIP_MAC_PKT_AllocF    pktAllocF;
    TCPIP_MAC_PKT_FreeF     pktFreeF;
    TCPIP_MAC_PKT_AckF      pktAckF;

    // event notification function
    TCPIP_MAC_EventF        eventF;     // function to be used by the MAC for event reporting
    const void*             eventParam; // parameter to be used when the event function is called   

    // module identifier; allows multiple channels/ports, etc. MAC support
    unsigned int            moduleId;
    // index of the current interface
    int                     netIx;
    // current action for the MAC/stack
    TCPIP_MAC_ACTION        macAction;
    // the power mode for this interface to go to
    // valid only if stackAction == init/re-init; ignored for de-init
    TCPIP_MAC_POWER_MODE    powerMode;

    // output data
    // data that's used by the MAC driver to return its settings
    // MAC sets these fields as initialization function returns to the stack
    TCPIP_MAC_ADDR                ifPhyAddress;   // physical address of the interface
    TCPIP_MAC_PROCESS_FLAGS processFlags;
    
}TCPIP_MAC_MODULE_CTRL;


// *****************************************************************************
/*  TCPIP_MAC_Initialize

  Summary:
    MAC driver initialization function.
    Returns a result to indicate that the initialization was successful.
    If it fails, the stack won't turn up that interface
    If the operation needs to wait for the hardware, the initialization
    fuction can return a pending code

Prameters:
    stackData   - stack prepared data
    moduleData  - driver specific. Dependent on the MAC type
                 For PIC32 MAC driver, the TCPIP_MODULE_MAC_PIC32INT_CONFIG is used 
    setupData   - MAC returns its settings: the host MAC address, processing requirements, etc.


Note:

*/
TCPIP_MAC_RES       TCPIP_MAC_Initialize(TCPIP_MAC_MODULE_CTRL* const stackData, const void* const moduleData);

// MAC de-initialization function
// Returns a result to indicate that everything has been
// cleaned up.
TCPIP_MAC_RES       TCPIP_MAC_Deinitialize(const TCPIP_MAC_MODULE_CTRL * const);


// MAC re-initialization function
// Allows re-initialization of the MAC with different power modes, etc.
// probably the same signature as TCPIP_MAC_Initialize
// Optional function
TCPIP_MAC_RES       TCPIP_MAC_Reinitialize(const TCPIP_MAC_MODULE_CTRL* const stackData, const void* const moduleData);


// function to open a MAC and get a client handle
typedef TCPIP_MAC_HANDLE    TCPIP_MAC_Open( unsigned int macId );

// all subsequent MAC functions take the hMac as the 1st parameter 
// hMac is a handle to a MAC

// closes a MAC client
TCPIP_MAC_RES       TCPIP_MAC_Close(TCPIP_MAC_HANDLE hMac);

// transfer interface

/**************************************************************************
  Summary:
    A packet is submitted to the MAC driver for transmission.
  Description:
    TCPIP_MAC_PacketTx
    
    This is the MAC transmit function. The MAC driver has to support
    \internal queueing! A packet is to be rejected only if it's not
    properly formatted. Otherwise it has to be scheduled for transmission
    in an internal queue!
    
    Once the packet is scheduled for transmission the MAC driver has to set
    the TCPIP_MAC_PKT_FLAG_QUEUED flag so that the stack is aware that this
    packet is under processing and cannot be modified!
    
    Once the packet is transmitted, the TCPIP_MAC_PKT_FLAG_QUEUED has to be
    cleared, the proper packet acknowledgement result (ackRes) has to be
    set and the packet acknowledgement function (ackFunc) has to be called.
    It is implementation dependant if all these steps are implemented as
    part of the ackFunc itself or as discrete steps.
  Input:
    hMac -       handle identifying the MAC driver client
    ptrPacket -  pointer to a TCPIP_MAC_PACKET that's completely formatted
                 and ready to be transmitted over the network
  Remarks:
    See notes for the segLoadOffset member.
    
    On 32 bit machines the 1st segment payload of a packet is allocated so
    that it is always 32 bit aligned and its size is 32 bits multiple. The
    segLoadOffset adds to the payload address and insures that the network
    layer data is 32 bit aligned.
      * PIC32 MAC driver specific : the driver checks that the
        segLoadOffset \>= 2.
    The packet is not required to contain the Frame Check Sequence
    (FCS/CRC32) field. The MAC driver/controller will insert that field
    itself, if it's required.
    
    The MAC driver is required to support the transmission of multiple
    chained packets.                                                       
  **************************************************************************/
TCPIP_MAC_RES       TCPIP_MAC_PacketTx(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_PACKET * ptrPacket);

// *****************************************************************************
/*  TCPIP_MAC_PacketRx

  Summary:
    A packet is returned if  such a pending packet exists.

  Description:
    This is the MAC receive function.
    
    Once a pending packet is available in the MAC driver internal RX queues
    this function will dequeue the packet and hand it over to the
    MAC driver's client - i.e. the stack - for further processing.


    The flags for a RX packet have to be updated by the MAC driver:
        - TCPIP_MAC_PKT_FLAG_RX has to be set
          If the MAC supports it, it should set: 
            - TCPIP_MAC_PKT_FLAG_UNICAST has to be set if that packet is a unicast packet
            - TCPIP_MAC_PKT_FLAG_BCAST has to be set if that packet is a broadcast packet
            - TCPIP_MAC_PKT_FLAG_MCAST has to be set if that packet is a multicast packet
        - TCPIP_MAC_PKT_FLAG_QUEUED has to be set
        - TCPIP_MAC_PKT_FLAG_SPLIT has to be set if the packet has multiple data segments

    Additional information about the packet is available by providing the pRes and
    ppPktStat fields.



  Parameters:
    hMac        - handle identifying the MAC driver client
    pRes        - optional pointer to an address that will receive an additional
                  result associated with the operation.
                  Can be 0 if not needed.
    ppPktStat   - optional pointer to an address that will receive the received
                  packet status.
                  Note that this pointer cannot be used once the packet
                  acknowledgement function was called.
                  Can be 0 if not needed.

  Returns:
    a valid pointer to an available RX packet
    0 if no packet pending/available



  Remarks:
    The MAC driver should dequeue and return to the caller just one single packet, 
    and not multiple chained packets!

    Once the higher level layers in the stack are done with processing the RX packet,
    they have to call the corresponding packet acknowledgement function
    that tells the owner of that packet that it can resume control of that packet.

    Once the stack modules are done processing the RX packets and the acknowledge function is called
    it is up to the driver design to reuse the RX packets, or simply return them to the pool
    they were allocated from (assuming that some sort of allocation is implemented).
    This document makes no requirement about how the MAC RX packets are obtained,
    using dynamic or static allocation techniques.
    This is up to the design of the MAC.

    The MAC driver can use the TCPIP_MAC_Process() for obtaining new RX packets if needed.

    Not all the MACs have hardware support for the received packet status.
    If the MAC driver cannot supply the TCPIP_MAC_PACKET_RX_STAT info,
    it should set the ppPktStat to 0.


*/
TCPIP_MAC_PACKET*   TCPIP_MAC_PacketRx (TCPIP_MAC_HANDLE hMac, TCPIP_MAC_RES* pRes, const TCPIP_MAC_PACKET_RX_STAT** ppPktStat);

// *****************************************************************************
/*  TCPIP_MAC_Process

  Summary:
    MAC periodic processing function.

  Description:
    This is a function that allows for internal processing by the MAC driver.
    It is meant for processing that cannot be done from within ISR.

    Some of the processing that this is intended for:
    - the MAC driver can process its pending TX queues
      (although it should do that preferrably from within the TX ISR)
    - RX buffers replenishing. If the number of packets in the RX queue
      falls below a specified limit, the MAC driver can use this function
      to allocate some extra RX packets.
      Similarly, if there are too many allocated RX packets, the MAC driver
      can free some of them.


    Normally this function will be called in response to an TX and/or RX event
    signalled by the driver.
    This is specified by the MAC driver at initialization time using TCPIP_MAC_MODULE_CTRL.

    An alternative approach is that the MAC driver uses a system service
    to create a timer signal that will call the TCPIP_MAC_Process on a periodic basis.



  Parameters:
    hMac        - handle identifying the MAC driver client

  Returns:
    TCPIP_MAC_RES_OK if all processing went on OK
    a TCPIP_MAC_RES error code if processing failed for some reason



  Remarks:
    None.


*/
TCPIP_MAC_RES       TCPIP_MAC_Process(TCPIP_MAC_HANDLE hMac);




/****************************
 *  Link Interface functions
 **************************************/

bool                TCPIP_MAC_LinkCheck(TCPIP_MAC_HANDLE hMac);


/****************************
 *  Event Notification functions
 **************************************/

// enables/disables the events to be reported 
// multiple events could be or-ed
// returns false if some error occurred
bool                    TCPIP_MAC_EventMaskSet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable);

// acknowledges reported event(s)
// returns false if no event to be acknowledged
// true otherwise 
bool                    TCPIP_MAC_EventAcknowledge(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents);

// returns current pending events
TCPIP_MAC_EVENT         TCPIP_MAC_EventPendingGet(TCPIP_MAC_HANDLE hMac);




/****************************
 *  MAC Filtering functions
 **************************************/

// set the hash table filter
TCPIP_MAC_RES        TCPIP_MAC_RxFilterHashTableEntrySet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR* DestMACAddr);

    

#endif // __TCPIP_MAC_H_

