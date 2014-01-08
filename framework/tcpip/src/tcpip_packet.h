/*******************************************************************************
  TCPIP network packet manager - private stack API

  Company:
    Microchip Technology Inc.
    
  File Name:
    tcpip_packet.h

  Summary:
    
  Description:
*******************************************************************************/
// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef __TCPIP_PACKET_H_
#define __TCPIP_PACKET_H_

#include <stdint.h>
#include <stdbool.h>

#include "tcpip/tcpip_mac.h"


// Extra debugging packet flags
// TX packets flags
// NOTE: // 16 bits only packet flags!

#define    TCPIP_MAC_PKT_FLAG_ARP          (TCPIP_MAC_PKT_FLAG_USER)        // ARP packet data
                                                                            // set when the packet is allocated by ARP
#define    TCPIP_MAC_PKT_FLAG_IPV4         (TCPIP_MAC_PKT_FLAG_USER << 1)   // IPv4 packet data
                                                                            // set when the packet is allocated by IPV4
#define    TCPIP_MAC_PKT_FLAG_IPV6         (TCPIP_MAC_PKT_FLAG_USER << 2)   // IPv6 packet data
                                                                            // set when the packet is allocated by IPV6
#define    TCPIP_MAC_PKT_FLAG_ICMPV4       (TCPIP_MAC_PKT_FLAG_USER << 3)   // ICMPv4 packet data
                                                                            // set when the packet is allocated by ICMPv4
#define    TCPIP_MAC_PKT_FLAG_ICMPV6       (TCPIP_MAC_PKT_FLAG_USER << 4)   // ICMPv6 packet data
                                                                            // set when the packet is allocated by ICMPv6
#define    TCPIP_MAC_PKT_FLAG_UDP          (TCPIP_MAC_PKT_FLAG_USER << 5)   // UDP packet data
                                                                            // set when the packet is allocated by UDP
#define    TCPIP_MAC_PKT_FLAG_TCP          (TCPIP_MAC_PKT_FLAG_USER << 6)   // TCP packet data
                                                                            // set when the packet is allocated by TCP
#define    TCPIP_MAC_PKT_FLAG_CONFIG       (TCPIP_MAC_PKT_FLAG_USER << 7)   // packet needs to be transmitted even when the stack
                                                                            // is not properly configured
                                                                            // probably a stack configuration packet


// initialization API

// sets the heap handle to be used for packet allocations
bool            TCPIP_PKT_Initialize(TCPIP_HEAP_HANDLE heapH);

void            TCPIP_PKT_Deinitialize(void);


// packet allocation API


// allocates a socket/transport IPv4/IPv6 packet
// The MAC, IPv4/IPv6 and transport headers (tHdrLen != 0) are all located in the 1st segment
// if payloadLen != 0 then the 1st segment will contain the/some payload too
// if needed, extra segments could be eventually added to the packet
// pktLen - size of the packet structure (at least TCPIP_MAC_PACKET will be allocated)
// tHdrLen - optional transport header length to be part of the 1st data segment
// payloadLen - optional transport payload to be part of the 1st data segment
// flags     - packet + 1st segment flags
TCPIP_MAC_PACKET*  TCPIP_PKT_SocketAlloc(uint16_t pktLen, uint16_t tHdrLen, uint16_t payloadLen, TCPIP_MAC_PACKET_FLAGS flags);


// allocates a TCPIP_MAC_PACKET packet (TCPIP_MAC_ETHERNET_HEADER always added);
// pktLen - the size of the packet (it will be 32 bits rounded up)
// segLoadLen - the payload size for the segment associated to this packet; Payload is always 32 bit aligned
//              if 0 no segment is created
// flags are attached to the 1st segment too 
TCPIP_MAC_PACKET* TCPIP_PKT_PacketAlloc(uint16_t pktLen, uint16_t segLoadLen, TCPIP_MAC_PACKET_FLAGS flags);


// forces freeing a previously allocated packet
// note that neither the packet nor segments marked
// with TCPIP_MAC_PKT_FLAG_STATIC are not freed
// Also note that this function does not free explicitely the segment payload.
// A payload that was created contiguously when the segment was created
// will be automatically freed by this function.
void            TCPIP_PKT_PacketFree(TCPIP_MAC_PACKET* pPkt);

extern __inline__ void __attribute__((always_inline)) TCPIP_PKT_PacketAcknowledgeSet(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_PACKET_ACK_FUNC ackFunc, const void* ackParam)
{
    pPkt->ackFunc = ackFunc;
    pPkt->ackParam = ackParam;
}

// acknowledges a packet
// clears the TCPIP_MAC_PKT_FLAG_QUEUED flag!
// a packet should always have an acknowledgment function
// packet's ackRes is updated only if the parameter ackRes != TCPIP_MAC_PKT_ACK_NONE.
void            TCPIP_PKT_PacketAcknowledge(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_PKT_ACK_RES ackRes);


//  simple segment allocation/manipulation

// allocates a segment with payload following immediately the segment header 
// this segment can be added to a packet using TCPIP_PKT_SegmentAppend
// loadLen specifies the segment allocated payload (could be 0)
// The segment payload is always allocated to be 32 bit aligned.
// The segment payload pointer will point loadOffset bytes after this address 
// 
TCPIP_MAC_DATA_SEGMENT* TCPIP_PKT_SegmentAlloc(uint16_t loadLen, uint16_t loadOffset, TCPIP_MAC_SEGMENT_FLAGS flags);

// adds a segment to the tail of segments of a packet
// segment should be fully constructed, with flags updated
void            TCPIP_PKT_SegmentAppend(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_DATA_SEGMENT* pSeg);           

// frees a created segment
void            TCPIP_PKT_SegmentFree(TCPIP_MAC_DATA_SEGMENT* pSeg);


// packet helpers
//

// sets the proper source, destination and type for a packet
// it also updated the packet length to include the MAC header size
// dstAddr can be 0 if not known
// packet should have been properly allocated and pMacLayer set
// returns false if the srcAddress is 0 though
// (intended for checking that a network interface is down)
bool             TCPIP_PKT_PacketMACFormat(TCPIP_MAC_PACKET* pPkt, const TCPIP_MAC_ADDR* dstAddr, const TCPIP_MAC_ADDR* srcAddr, uint16_t pktType);


// returns the segment to which dataAddress belongs
// the search occurs in every segment of the packet
// if srchTransport is set, the search starts with the transport data, i.e.
//      startPoint = pTransportLayer,
//      endPoint = startPoint + totTransportLen
// otherwise
//      startPoint = segLoad
//      endPoint = startPoint + segSize
// 0 if not in this packet
TCPIP_MAC_DATA_SEGMENT* TCPIP_PKT_DataSegmentGet(TCPIP_MAC_PACKET* pPkt, uint8_t* dataAddress, bool srchTransport);




#endif // __TCPIP_PACKET_H_


