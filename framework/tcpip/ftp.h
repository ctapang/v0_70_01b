/*******************************************************************************
  FTP Server Defs for Microchip TCP/IP Stack
  
  Company:
    Microchip Technology Inc.
    
  File Name: ftp.h

  Summary:
    An embedded FTP (File Transfer Protocol) server is an excellent addition to
    any network-enabled device.

  Description:
    An embedded FTP (File Transfer Protocol) server is an excellent addition to 
    any network-enabled device. FTP server capability facilitates the uploading 
    of files to, and downloading of files from, an embedded device. Almost all 
    computers have, at the very least, a command line FTP client that will allow 
    a user to connect to an embedded FTP server.
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

#ifndef __FTP_H
#define __FTP_H



// FTP module dynamic configuration data
typedef struct
{
    uint16_t    dataSktTxBuffSize;  // size of Data socket TX buffer for the associatted socket; leave 0 for default
    uint16_t    dataSktRxBuffSize;  // size of Data Socket RX buffer for the associatted socket; leave 0 for default
    uint8_t     userName[10+1]; // FTP login User name   TCPIP_FTP_USER_NAME_LEN
    uint8_t     password[10+1]; // FTP login password  TCPIP_FTP_PASSWD_LEN
} FTP_MODULE_CONFIG;


#endif
