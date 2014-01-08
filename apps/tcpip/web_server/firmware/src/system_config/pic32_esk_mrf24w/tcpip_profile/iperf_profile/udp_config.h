/*******************************************************************************
  User Datagram Protocol (UDP) Configuration file

  Summary:
    UDP onfiguration file
    
  Description:
    This file contains the UDP module configuration options
    
*******************************************************************************/

/*******************************************************************************
File Name:  udp_config.h
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

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

#ifndef _UDP_CONFIG_H_
#define _UDP_CONFIG_H_

// The dynamic port range defined by IANA consists of the 49152-65535 range
// and is meant for the selection of ephemeral ports (RFC 6056).
// Adjust to your needs but stay within the IANA range 
// First port number for randomized local port number selection
#define UDP_LOCAL_PORT_START_NUMBER (49152)
// Last port number for randomized local port number selection
#define UDP_LOCAL_PORT_END_NUMBER   (65535)

// global number of UDP sockets created dynamically
#define UDP_MAX_SOCKETS			(6)

// default socket Tx buffer size
#define UDP_SOCKET_DEFAULT_TX_SIZE	1024

// default socket Rx buffer size
#define UDP_SOCKET_DEFAULT_RX_SIZE	1024

// This slows UDP TX performance by nearly 50%,
// except when using the ENCX24J600, which has a
// super fast DMA and incurs virtually no speed pentalty.
#define UDP_USE_TX_CHECKSUM

// check incoming packets to have proper checksum
#define UDP_USE_RX_CHECKSUM

// the maximum number of packets that can be queued
// by an UDP socket at a certain time.
// For sockets that need to transfer a lot of data (iperf, for example),
// especially on slow conenctions this limit prevents running out of memory
// because the MAC transfer cannot keep up with the UDP packet allocation rate
// imposed by the aapplication.
// Adjust depending on the UDP_SOCKET_DEFAULT_TX_SIZE, the connection speed
// and the amount of memory available to the stack.
#define UDP_SOCKET_DEFAULT_TX_QUEUE_LIMIT   3

// number of buffers in the private UDP pool
// pre-allocated buffers that are to be used
// by UDP sockets only.
// This improves the UDP socket throughput
// However, this memory is not returned to the stack heap,
// it belongs to UDP
// A socket needs to have an option set in order to use the buffers pool
// (see the UDPSetOptions()).
#define UDP_SOCKET_POOL_BUFFERS         4       // use 0 to disable the feature

#define UDP_SOCKET_POOL_BUFFER_SIZE     512     // size of the buffers in the UDP pool
                                                // any UDP socket that is enabled to use the pool
                                                // and has the TX size <= than this size can use 
                                                // a buffer from the pool

/* Reference only:
typedef struct
{
    uint16_t        nSockets;       // number of sockets to be created
    uint16_t        sktTxBuffSize;  // size of the socket tx buffer
    uint16_t        poolBuffers;    // number of buffers in the pool; 0 if none
    uint16_t        poolBufferSize; // size of the buffers in the pool; all equal    
}UDP_MODULE_CONFIG;
*/


// This is a template of how the UDP module should be initialized and
// the parameters that it needs.
#ifdef TCPIP_STACK_MODULE_CONFIGURATION
const UDP_MODULE_CONFIG udpConfigData = 
{
	UDP_MAX_SOCKETS,
	UDP_SOCKET_DEFAULT_TX_SIZE,
    UDP_SOCKET_POOL_BUFFERS,
    UDP_SOCKET_POOL_BUFFER_SIZE,
};
#else
extern const UDP_MODULE_CONFIG udpConfigData;
#endif  // TCPIP_STACK_MODULE_CONFIGURATION


#endif  // _UDP_CONFIG_H_
