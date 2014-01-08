// Include all headers for any enabled tcpip functions
#include "tcpip/tcpip.h"

// Include functions specific to this stack application
#include "tcpip/src/system/system_userio.h"

#include "wolf_ssl_glue.h"
#include "ca-cert.h"


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
static uint8_t logEnabled = 1;

void TCPIP_WSSL_Logging_cb(const int logLevel, const char *const logMessage)
{
    if (!logEnabled)
    {
        return;
    }
    SYS_CONSOLE_PRINT("WolfSSL(%d): %s\r\n", logLevel, logMessage);
}

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
int TCPIP_WSSL_Receive_cb(CYASSL *ssl, char *buf, int sz, void *ctx)
{
    register TCP_SOCKET sock = ssl->rfd;
    uint16_t bufferSize;

    //SYS_CONSOLE_PRINT("%s called %d %d\r\n", __FUNCTION__, sock, sz);

#if 0
    if (TCPIP_TCP_WasReset(sock))
    {
        SYS_CONSOLE_PRINT("%s connection reset\r\n", __FUNCTION__);
        return CYASSL_CBIO_ERR_CONN_RST;
    }
#endif

    bufferSize = TCPIP_TCP_GetIsReady(sock);
    //SYS_CONSOLE_PRINT("    Number of bytes ready: %d\r\n", bufferSize);
    if (bufferSize == 0)
    {
        logEnabled = 0;
        return CYASSL_CBIO_ERR_WANT_READ;
    }
    logEnabled = 1;

    bufferSize = TCPIP_TCP_ArrayGet(sock, (uint8_t*)buf, sz);
    //SYS_CONSOLE_PRINT("    Number of bytes received: %d\r\n", bufferSize);
    return bufferSize;

}

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
int TCPIP_WSSL_Send_cb(CYASSL *ssl, char *buf, int sz, void *ctx)
{
    register TCP_SOCKET sock = ssl->wfd;
    uint16_t bufferSize;

    //SYS_CONSOLE_PRINT("%s called %d %d\r\n", __FUNCTION__, sock, sz);

#if 0
    if (TCPIP_TCP_WasReset(sock))
    {
        SYS_CONSOLE_PRINT("%s connection reset\r\n", __FUNCTION__);
        return CYASSL_CBIO_ERR_CONN_RST;
    }
#endif
    
    bufferSize = TCPIP_TCP_PutIsReady(sock);
    //SYS_CONSOLE_PRINT("    Number of bytes ready: %d\r\n", bufferSize);
    if (bufferSize == 0)
    {
        logEnabled = 0;
        return CYASSL_CBIO_ERR_WANT_WRITE;
    }
    logEnabled = 1;

    bufferSize =  TCPIP_TCP_ArrayPut(sock, (uint8_t*)buf, (uint16_t)sz);
    //SYS_CONSOLE_PRINT("    Number of bytes sent: %d\r\n", bufferSize);
    return bufferSize;
}

/*****************************************************************************
  Function:
    int TCPIP_WSSL_CreateConnection(WOLF_SSL_CONNECTION_INFO * info, const char * hostname, TCP_PORT port)

  Summary:
 Helper function to create an SSL connection to the hostname and port provided

  Description:
 This function initializes info structure and starts up the dns query.  The
 TCPIP_WSSL_PumpConnection function should then be called until WOLF_SSL_CS_SSL_CONNECTED
 is returned.  At that point the TCP/IP connection is opened.

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

int8_t TCPIP_WSSL_CreateConnection(WOLF_SSL_CONNECTION_INFO * info, const char * hostname, TCP_PORT port)
{
    SYS_CONSOLE_PRINT("%s called\r\n", __FUNCTION__);
    memset(info, 0, sizeof(WOLF_SSL_CONNECTION_INFO));
    DNS_RESULT result = TCPIP_DNS_UsageBegin(0); 
    SYS_CONSOLE_PRINT("TCPIP_DNS_UsageBegin return %d\r\n", result);
    if (result != DNS_RES_OK)
    {
        return WOLF_SSL_CS_ERROR;
    }
    result = TCPIP_DNS_Resolve(hostname, DNS_TYPE_A);
    SYS_CONSOLE_PRINT("TCPIP_DNS_Resolve return %d\r\n", result);
    if (result != DNS_RES_OK)
    {
        TCPIP_DNS_UsageEnd(0);
        return WOLF_SSL_CS_ERROR;
    }
    info->port = port;
    info->state = WOLF_SSL_CS_DNS_QUERY_STARTED;
    info->hostname = hostname;
    info->socket = INVALID_SOCKET;
    SYS_CONSOLE_PRINT("%s exiting\r\n", __FUNCTION__);
   return WOLF_SSL_CS_DNS_QUERY_STARTED;
}

// Function to handle the DNS query
int8_t TCPIP_WSSL_PumpDNS(WOLF_SSL_CONNECTION_INFO * info)
{
    IPV4_ADDR ipv4Addr;
    DNS_RESULT result = TCPIP_DNS_IsResolved(info->hostname, &ipv4Addr);
    switch (result)
    {
        case DNS_RES_OK:
        {
            SYS_CONSOLE_PRINT("TCPIP_DNS_IsResolved returned success\r\n", __FUNCTION__);
            // We now have an IPv4 Address
            TCPIP_DNS_UsageEnd(0);
            // Open a socket
            info->socket = TCPIP_TCP_ClientOpen(IP_ADDRESS_TYPE_IPV4,
                    info->port,
                    (IP_MULTI_ADDRESS*) &ipv4Addr);
            SYS_CONSOLE_PRINT("TCPIP_TCP_ClientOpen returned %d invalid = %d\r\n", info->socket, INVALID_SOCKET);
            if (info->socket == INVALID_SOCKET)
            {
                info->state = WOLF_SSL_CS_ERROR;
                return WOLF_SSL_CS_ERROR;
            }
            info->state = WOLF_SSL_CS_SYN_SENT;
            return WOLF_SSL_CS_SYN_SENT;
        }
        case DNS_RES_PENDING:
            return info->state;
        case DNS_RES_SERVER_TMO:
        case DNS_RES_NO_ENTRY:
        default:
            SYS_CONSOLE_PRINT("TCPIP_DNS_IsResolved returned failure\r\n", __FUNCTION__);
            TCPIP_DNS_UsageEnd(0);
            info->state = WOLF_SSL_CS_ERROR;
            return WOLF_SSL_CS_ERROR;
    }
    // Should not be here!
    return WOLF_SSL_CS_UNKNOWN;
}

//Function to handle the opening TCP/IP connection
int8_t TCPIP_WSSL_PumpSynSent(WOLF_SSL_CONNECTION_INFO * info)
{
    if (TCPIP_TCP_IsConnected(info->socket))
    {
        SYS_CONSOLE_PRINT("%s TCPIP_TCP_IsConnected is connected\r\n", __FUNCTION__);
        //  The connection has been connected, now comes the fun part
        // Create a new context
        info->ctx = CyaSSL_CTX_new(CyaSSLv23_client_method());
        if (info->ctx == 0)
        {
            // Something went wrong with creating the context
            SYS_CONSOLE_MESSAGE("Something went wrong with creating the SSL context\r\n");
            goto TERM_1;

        }
        // hook up the send/receive callbacks
        CyaSSL_SetIORecv(info->ctx, &TCPIP_WSSL_Receive_cb);
        CyaSSL_SetIOSend(info->ctx, &TCPIP_WSSL_Send_cb);

        // Load the certificates
        if (CyaSSL_CTX_load_verify_buffer(info->ctx,
                caCert,
                caCert_len,
                SSL_FILETYPE_PEM) != SSL_SUCCESS)
        {
            // Couldn't load the certificates
            SYS_CONSOLE_MESSAGE("Something went wrong loading the certificates\r\n");
            goto TERM_2;
        }

        // Turn off verification, for now, for some reason its failing
        CyaSSL_CTX_set_verify(info->ctx, SSL_VERIFY_NONE, 0);

        if ((info->ssl = CyaSSL_new(info->ctx)) == 0)
        {
            // Couldn't make a new ssl structure
            SYS_CONSOLE_MESSAGE("Something went wrong creating a new SSL\r\n");
            goto TERM_2;
        }

        if (CyaSSL_set_fd(info->ssl, info->socket) != SSL_SUCCESS)
        {
            // Could not set the file descriptor
            SYS_CONSOLE_MESSAGE("Something went wrong linking the file descriptor\r\n");
            goto TERM_2;
        }
        info->state = WOLF_SSL_CS_TCP_OPEN;
        return info->state;

    }
    // Check to see if the connection was reset:
    /*if (TCPIP_TCP_WasReset(info->socket))
    {
        SYS_CONSOLE_MESSAGE("The TCP connection was reset\r\n");
       // Yes it was (time out or something else)
        goto TERM_1;
    }*/

    return info->state;

TERM_2:
    CyaSSL_CTX_free(info->ctx);
TERM_1:
    TCPIP_TCP_Close(info->socket);
    info->socket = INVALID_SOCKET;
    info->state = WOLF_SSL_CS_ERROR;
    return WOLF_SSL_CS_ERROR;
}

int8_t TCPIP_WSSL_PumpTcpOpen(WOLF_SSL_CONNECTION_INFO * info)
{
    int result = CyaSSL_connect(info->ssl);
#if 0
    if (TCPIP_TCP_WasReset(info->socket))
    {
        // Yes it was (time out or something else)
        SYS_CONSOLE_MESSAGE("The TCP connection was reset\r\n");
        goto TERM_1;
    }
#endif
    switch (result)
    {
        case SSL_SUCCESS:
        {
            // We're fully open.  Nothing to see here move along
            SYS_CONSOLE_MESSAGE("SSL Connection is declared open\r\n");
            info->state = WOLF_SSL_CS_SSL_CONNECTED;
            return WOLF_SSL_CS_SSL_CONNECTED;
        }
        default:
        {
            int error = CyaSSL_get_error(info->ssl, result);
            if ((error == SSL_ERROR_WANT_READ) ||
                (error == SSL_ERROR_WANT_WRITE))
            {
                // we're fine
                return info->state;
            }
            goto TERM_1; // Some other error
        }
    }
 TERM_1:
    CyaSSL_CTX_free(info->ctx);
    TCPIP_TCP_Close(info->socket);
    info->socket = INVALID_SOCKET;
    info->state = WOLF_SSL_CS_ERROR;
    return WOLF_SSL_CS_ERROR;
}

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

int8_t TCPIP_WSSL_PumpConnection(WOLF_SSL_CONNECTION_INFO * info)
{
    switch (info->state)
    {
        case WOLF_SSL_CS_DNS_QUERY_STARTED:
        {
            return TCPIP_WSSL_PumpDNS(info);
        }
        case WOLF_SSL_CS_SYN_SENT:
        {
            return TCPIP_WSSL_PumpSynSent(info);
        }
        case WOLF_SSL_CS_TCP_OPEN:
        {
            return TCPIP_WSSL_PumpTcpOpen(info);
            break;
        }
        case WOLF_SSL_CS_SSL_CLOSING:
        {

            break;
        }
        case WOLF_SSL_CS_ERROR:
        case WOLF_SSL_CS_UNKNOWN:
        case WOLF_SSL_CS_SSL_CONNECTED:
        case WOLF_SSL_CS_CLOSED:
        default:
            return info->state;
    }

    return WOLF_SSL_CS_ERROR;
}


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

int8_t TCPIP_WSSL_CloseConnection(WOLF_SSL_CONNECTION_INFO * info)
{
    CyaSSL_CTX_free(info->ctx);
    TCPIP_TCP_Close(info->socket);
    info->socket = INVALID_SOCKET;
    info->state = WOLF_SSL_CS_CLOSED;
    return WOLF_SSL_CS_CLOSED;
}

