/*******************************************************************************
  Internet Protocol (IP) Configuration file

  Summary:
    IP configuration file
    
  Description:
    This file contains the IP module configuration options
    
*******************************************************************************/

/*******************************************************************************
File Name:  ip_config.h
Copyright © 2011 released Microchip Technology Inc.  All rights
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

#ifndef _IP_CONFIG_H_
#define _IP_CONFIG_H_

// Not implemented
//#define IP_DEFAULT_TX_BUFFER_SIZE           (1500u)

// Used to configure payload size
#define IP_DEFAULT_ALLOCATION_BLOCK_SIZE    (64u)


// This option defines the maximum number of queued IPv4 TX packets.  If an additional
// packet is queued, the oldest packet in the queue will be removed.
#define IPV4_QUEUED_PACKET_LIMIT              4u

// This option defines the number of seconds an IPv4 TX packet will remain in the
// queue before being timed out
#define IPV4_QUEUED_PACKET_TIMEOUT            10u


// IPv4 task processing rate, miliseconds
#define IPV4_TASK_PROCESS_RATE              (1000)      // default 1 second



#endif  // _IP_CONFIG_H_

