/*******************************************************************************
 Header file for the Wolf SSL glue functions to work with Harmony


  Summary:


  Description:
    
*******************************************************************************/

/*******************************************************************************
File Name: wold_ssl_glue.h
Copyright © 2013 released Microchip Technology Inc.  All rights
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

#ifndef WOLF_SSL_GLUE_H
#define	WOLF_SSL_GLUE_H

#include <cyassl/ssl.h>
#include <cyassl/internal.h>

#ifdef	__cplusplus
extern "C" {
#endif

// *****************************************************************************
/* WOLF_SSL_CONNECTION_STATE Enumeration

  Summary:
    This enumeration provides the status of the wolf ssl connection.

  Description:
    This enumeration provides the status of the wolf ssl connection.

  Remarks:
    None.
*/
typedef enum
{
    WOLF_SSL_CS_ERROR = -1,
    WOLF_SSL_CS_UNKNOWN = 0,
    WOLF_SSL_CS_DNS_QUERY_STARTED,
    WOLF_SSL_CS_SYN_SENT,
    WOLF_SSL_CS_TCP_OPEN,
    WOLF_SSL_CS_SSL_CONNECTED,
    WOLF_SSL_CS_SSL_CLOSING,
    WOLF_SSL_CS_CLOSED
} WOLF_SSL_CONNECTION_STATE;

// *****************************************************************************
/* WOLF_SSL_CONNECTION_INFO Structure Typedef

  Summary:
    Provides the information and the stuff needed to be stored for a wolf SSL
 connection

  Description:
    Provides the information and the stuff needed to be stored for a wolf SSL
 connection

  Remarks:
    None.
*/
typedef struct
{
    TCP_SOCKET socket;
    TCP_PORT port;
    const char * hostname;
    CYASSL_CTX*     ctx;
    CYASSL* ssl;
    int8_t state;

} WOLF_SSL_CONNECTION_INFO;


/*****************************************************************************
  Function:
    void TCPIP_WSSL_Logging_cb(const int logLevel, const char *const logMessage)

  Summary:
    Callback given to WolfSSL during initialization for logging

  Description:
   This function allows Wolf SSL to send debug messages.

  Precondition:
   None

  Parameters:
    logLevel   - log level the Wolf SSL is sending out
    logMessage - the log message

  Return Values:
    None

  Remarks:
  ***************************************************************************/
void TCPIP_WSSL_Logging_cb(const int logLevel, const char *const logMessage);

/*****************************************************************************
  Function:
    int TCPIP_WSSL_Receive_cb(CYASSL *ssl, char *buf, int sz, void *ctx)

  Summary:
    Callback given to WolfSSL during initialization to receive network packets

  Description:
   This function allows Wolf SSL to receive network packets

  Precondition:
   TCPIP must be initialized

  Parameters:
    ssl   - pointer to the ssl structure
    buf   - the receive buffer
    sz    - size of the receive buffer
    ctx   - the context passed into WolfSSL

  Return Values:
    CYASSL_CBIO_ERR_WANT_READ - Connection would block waiting on data
    CYASSL_CBIO_ERR_TIMEOUT - Socket timeout
    CYASSL_CBIO_ERR_CONN_RST - Connection reset
    CYASSL_CBIO_ERR_ISR - Socket interrupted
    CYASSL_CBIO_ERR_CONN_CLOSE - Connection Closed
    CYASSL_CBIO_ERR_GENERAL - All other errors
    > 0 the number of bytes returned.

  Remarks:
    Don't call this function directly, its for use by Wolf SSL.  It is set up
 to be non-blocking.
  ***************************************************************************/
int TCPIP_WSSL_Receive_cb(CYASSL *ssl, char *buf, int sz, void *ctx);

/*****************************************************************************
  Function:
    int TCPIP_WSSL_Send_cb(CYASSL *ssl, char *buf, int sz, void *ctx)

  Summary:
    Callback given to WolfSSL during initialization to send network packets

  Description:
   This function allows Wolf SSL to send network packets

  Precondition:
   TCPIP must be initialized

  Parameters:
    ssl   - pointer to the ssl structure
    buf   - the send buffer
    sz    - size of the send buffer
    ctx   - the context passed into WolfSSL

  Return Values:
    CYASSL_CBIO_ERR_WANT_WRITE - Connection would block writing data
    CYASSL_CBIO_ERR_CONN_RST - Connection reset
    CYASSL_CBIO_ERR_ISR - Socket interrupted
    CYASSL_CBIO_ERR_CONN_CLOSE - Connection Closed
    CYASSL_CBIO_ERR_GENERAL - All other errors
    > 0 the number of bytes returned.

  Remarks:
    Don't call this function directly, its for use by Wolf SSL.  It is set up
 to be non-blocking.
  ***************************************************************************/
int TCPIP_WSSL_Send_cb(CYASSL *ssl, char *buf, int sz, void *ctx);


/*****************************************************************************
  Function:
    int TCPIP_WSSL_CreateConnection(WOLF_SSL_CONNECTION_INFO * info, const char * hostname, TCP_PORT port)

  Summary:
 Helper function to create an SSL connection to the hostname and port provided

  Description:
 This function initializes info structure and starts up the dns query.  The
 TCPIP_WSSL_PumpConnection function should then be called until WOLF_SSL_CS_SSL_CONNECTED
 is returned.  At that point the SSL connection is opened.

  Precondition:
   TCPIP must be initialized, CyaSSL_Init() must be called to initialize the
 Wolf SSL stack

  Parameters:
    info   - pointer to the ssl connection structure
    hostname   - the name of the host to initiate the connection to.
    port    - the port to connect to

  Return Values:
    WOLF_SSL_CS_ERROR - Something has gone wrong
    WOLF_SSL_CS_DNS_QUERY_STARTED - If everything started properly.
    All other values should not be returned.

  Remarks:
 Use this function to start a connection.
  ***************************************************************************/

int8_t TCPIP_WSSL_CreateConnection(WOLF_SSL_CONNECTION_INFO * info, const char * hostname, TCP_PORT port);

/*****************************************************************************
  Function:
    int8_t TCPIP_WSSL_PumpConnection(WOLF_SSL_CONNECTION_INFO * info);

  Summary:
 Helper function to walk the connection state machine

  Description:
 This function will handle the DNS query, and open up a TCP/IP connection.
 It will also handle closing and cleaning up the connection

  Precondition:
   TCPIP must be initialized, and a info structure initialized with
 TCPIP_WSSL_CreateConnection()

  Parameters:
    info   - pointer to the ssl connection structure

  Return Values:
    WOLF_SSL_CS_ERROR - Something has gone wrong
    WOLF_SSL_CS_DNS_QUERY_STARTED - The DNS query is still running
    WOLF_SSL_CS_SYN_SENT - The TCP/IP connection is opening
    WOLF_SSL_CS_TCP_OPEN - The TCP/IP connection has started and
                           the SSL connection opened, but negotiation
                           is still executing
    WOLF_SSL_CS_SSL_CONNECTED - The SSL connection is fully open
    WOLF_SSL_CS_SSL_CLOSING - The connection is being torn down
    WOLF_SSL_CS_CLOSED - The connection is closed
    All other values should not be returned

  Remarks:
 Use this function while waiting for the connection to open and close.
 You don't need to use it while in the WOLF_SSL_CS_SSL_CONNECTED state.
  ***************************************************************************/

int8_t TCPIP_WSSL_PumpConnection(WOLF_SSL_CONNECTION_INFO * info);


/*****************************************************************************
  Function:
    int8_t TCPIP_WSSL_CloseConnection(WOLF_SSL_CONNECTION_INFO * info);

  Summary:
 Helper function to close the connection

  Description:
 This function will handle the DNS query, and open up a TCP/IP connection.

  Precondition:
   TCPIP must be initialized, and a info structure initialized with
 TCPIP_WSSL_CreateConnection()

  Parameters:
    info   - pointer to the ssl connection structure

  Return Values:
    WOLF_SSL_CS_ERROR - Something has gone wrong
    WOLF_SSL_CS_SSL_CLOSING - The connection is being torn down
    All other values should not be returned

  Remarks:
 Use this function to close a connection.  After calling this keep calling
 TCPIP_WSSL_PumpConnection until  WOLF_SSL_CS_CLOSED is returned
  ***************************************************************************/

int8_t TCPIP_WSSL_CloseConnection(WOLF_SSL_CONNECTION_INFO * info);
#ifdef	__cplusplus
}
#endif

#endif	/* WOLF_SSL_GLUE_H */

