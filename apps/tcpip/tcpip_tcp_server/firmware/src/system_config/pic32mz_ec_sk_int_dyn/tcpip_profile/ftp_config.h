/*******************************************************************************
  File Transfer Protocol (FTP) Configuration file

  Summary:
    FTP configuration file

  Description:
    This file contains the FTP module configuration options

*******************************************************************************/

/*******************************************************************************
File Name:  ftp_config.h
Copyright � 2012 released Microchip Technology Inc.  All rights
reserved.

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

#ifndef _FTP_CONFIG_H_
#define _FTP_CONFIG_H_

#define TCPIP_STACK_USE_FTP_SERVER

// Specifies the max length for user name
#define TCPIP_FTP_USER_NAME_LEN		(10)

// Specifies the max length of FTP login password
#define TCPIP_FTP_PASSWD_LEN      (10)

// Comment this line out to disable MPFS
#define TCPIP_FTP_PUT_ENABLED

// Maximum number of FTP connections allowed per interface
#define TCPIP_FTP_MAX_CONNECTIONS		(1)

// Define the size of the TX buffer for the FTP Data socket
// Use 0 for default
#define     TCPIP_FTP_DATA_SKT_TX_BUFF_SIZE   0

// Define the size of the RX buffer for the FTP Data socket
// Use 0 for default
#define     TCPIP_FTP_DATA_SKT_RX_BUFF_SIZE   0


#endif  // _FTP_CONFIG_H_
