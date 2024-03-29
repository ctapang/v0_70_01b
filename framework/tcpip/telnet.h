/*******************************************************************************
  Telnet Server Module for Microchip TCP/IP Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
    telnet.h
    
  Summary:
    Telnet provides bidirectional, interactive communication between two nodes
    on the Internet or on a Local Area Network.
        
  Description:
    Telnet provides bidirectional, interactive communication between two nodes 
    on the Internet or on a Local Area Network. The Telnet code included with 
    Microchip's TCP/IP stack is a demonstration of the structure of a Telnet 
    application. This demo begins by listening for a Telnet connection. When 
    a client attempts to make one, the demo will prompt the client for a 
    username and password, and if the correct one is provided, will output 
    and periodically refresh several values obtained from the demo board.
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

#ifndef __TELNET_H
#define __TELNET_H

#include <stdint.h>
#include <stdbool.h>

// *****************************************************************************
/*
 Telnet Configuration structure placeholder
*/
typedef struct
{
}TELNET_MODULE_CONFIG;


    
#endif	//#ifndef __TELNET_H
