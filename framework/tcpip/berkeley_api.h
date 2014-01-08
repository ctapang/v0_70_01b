/*******************************************************************************
  Berkeley Socket Distribution API Header File

  Company:
    Microchip Technology Inc.
    
  File Name:
    berkeley_api.h

  Summary:
    The Berkeley Socket Distribution (BSD) APIs provide a BSD wrapper to the native 
    Microchip TCP/IP Stack APIs.
    
  Description:
    The Berkeley Socket Distribution (BSD) APIs provide a BSD wrapper to the native 
    Microchip TCP/IP Stack APIs. Using this interface, programmers familiar with
    BSD sockets can quickly develop applications using Microchip's TCP/IP Stack.
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

#ifndef _BERKELEY_API_HEADER_FILE
#define _BERKELEY_API_HEADER_FILE

typedef int16_t SOCKET;   //Socket descriptor

#define AF_INET         2			// Internet Address Family - UDP, TCP, etc.

#define IP_ADDR_ANY     0u			// IP Address for server binding
#define INADDR_ANY      0x00000000u	// IP address for server binding.


#define SOCK_STREAM 100  //Connection based byte streams. Use TCP for the internet address family.
#define SOCK_DGRAM  110  //Connectionless datagram socket. Use UDP for the internet address family.
 
#define IPPROTO_IP      0   // Indicates IP pseudo-protocol.
#define IPPROTO_TCP     6   // Indicates TCP for the internet address family.
#define IPPROTO_UDP     17  // Indicates UDP for the internet address family.

#define SOCKET_ERROR            (-1) //Socket error
#define SOCKET_CNXN_IN_PROGRESS (-2) //Socket connection state.
#define SOCKET_DISCONNECTED     (-3) //Socket disconnected


#define INVALID_TCP_PORT   (0L)  //Invalid TCP port

struct in_addr
{
    union
   {
       struct { uint8_t s_b1,s_b2,s_b3,s_b4; } S_un_b; // IP address in Byte
       struct { uint16_t s_w1,s_w2; } S_un_w; //IP address in Word
       uint32_t S_addr; //IP address
   }S_un; //union of IP address
    
#define s_addr  S_un.S_addr //can be used for most tcp & ip code
#define s_host  S_un.S_un_b.s_b2 //host on imp
#define s_net   S_un.S_un_b.s_b1 // network
#define s_imp   S_un.S_un_w.s_w2 // imp
#define s_impno S_un.S_un_b.s_b4 // imp number
#define s_lh    S_un.S_un_b.s_b3 // logical host
}; // in_addr structure

struct __attribute__((__packed__)) sockaddr
{
    unsigned short   sa_family;   //address family
    char    sa_data[14];       //up to 14 bytes of direct address
}; //generic address structure for all address families

struct __attribute__((__packed__)) sockaddr_in
{
    short   sin_family; //Address family; must be AF_INET.
    uint16_t    sin_port;  //Internet Protocol (IP) port.
    struct  in_addr sin_addr; //IP address in network byte order.
    char    sin_zero[8];  //Padding to make structure the same size as SOCKADDR. 
}; //In the Internet address family

typedef struct sockaddr_in SOCKADDR_IN; //In the Internet address family
typedef struct sockaddr SOCKADDR;  // generic address structure for all address families

/*
 * Berkeley API module configuration structure
 */

typedef struct
{
} BERKELEY_MODULE_CONFIG;


/*****************************************************************************
 Function:
   SOCKET socket( int af, int type, int protocol )

 Summary:
   This function creates a new Berkeley socket.

 Description:
   This function creates a new BSD socket for the microchip
   TCPIP stack. The return socket descriptor is used for the subsequent
   BSD operations.

 Precondition:
   BerkeleySocketInit function should be called.

 Parameters:
   af - address family - AF_INET.
   type - socket type SOCK_DGRAM or SOCK_STREAM.
   protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP.

 Returns:
   New socket descriptor. SOCKET_ERROR in case of error.
   (and errno set accordingly).

 Remarks:
   None.
*/
SOCKET  socket( int af, int type, int protocol );

/*****************************************************************************
  Function:
    int bind( SOCKET s, const struct sockaddr* name, int namelen )

  Summary:
    This function assigns a name to the socket descriptor.

  Description:
    The bind function assigns a name to an unnamed socket. The
    name represents the local address of the communication
    endpoint. For sockets of type SOCK_STREAM, the name of the
    remote endpoint is assigned when a connect or accept function
    is executed.

  Precondition:
    socket function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    name - pointer to the sockaddr structure containing the
    local address of the socket.
    namelen - length of the sockaddr structure.

  Returns:
    If bind is successful, a value of 0 is returned. A return
    value of SOCKET_ERROR indicates an error.
    (and errno set accordingly).

  Remarks:
    None.
 */
int     bind( SOCKET s, const struct sockaddr* name, int namelen );


/*****************************************************************************
  Function:
    int listen( SOCKET s, int backlog )

  Summary:
    The listen function sets the specified socket in a listen mode

  Description:
    This function sets the specified socket in a listen
    mode. Calling the listen function indicates that the
    application is ready to accept connection requests arriving
    at a socket of type SOCK_STREAM. The connection request is
    queued (if possible) until accepted with an accept function.
    The backlog parameter defines the maximum number of pending
    connections that may be queued.

  Precondition:
    bind() must have been called on the s socket first.

  Parameters:
    s - Socket identifier returned from a prior socket() call.
    backlog - Maximum number of connection requests that can be queued.  Note
        that each backlog requires a TCP socket to be allocated.

  Returns:
    Returns 0 on success, else return SOCKET_ERROR.
    (and errno set accordingly).

  Remarks:
    None
 */int     listen( SOCKET s, int backlog );

/*****************************************************************************
  Function:
    SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen)

  Summary:
    This function accepts connection requests queued for a listening socket.

  Description:
    The accept function is used to accept connection requests
    queued for a listening socket. If a connection request is
    pending, accept removes the request from the queue, and a new
    socket is created for the connection. The original listening
    socket remains open and continues to queue new connection
    requests. The socket must be a SOCK_STREAM type socket.

  Precondition:
    listen function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to
    socket. must be bound to a local name and in listening mode.
    addr - Optional pointer to a buffer that receives the address
    of the connecting entity.
    addrlen - Optional pointer to an integer that contains the
    length of the address addr

  Returns:
    If the accept function succeeds, it returns a non-negative
    integer that is a descriptor for the accepted socket.
    Otherwise, the value SOCKET_ERROR is returned.
    (and errno set accordingly).

  Remarks:
    None.
 */
SOCKET  accept( SOCKET s, struct sockaddr* addr, int* addrlen );
/*****************************************************************************
  Function:
    int connect( SOCKET s, struct sockaddr* name, int namelen )

  Summary:
    This function connects to the peer communications end point.

  Description:
    The connect function assigns the address of the peer
    communications endpoint. For stream sockets, connection is
    established between the endpoints. For datagram sockets, an
    address filter is established between the endpoints until
    changed with another connect() function.

  Precondition:
    socket function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    name - pointer to the sockaddr structure containing the
    peer address and port number.
    namelen - length of the sockaddr structure.

  Returns:
    If the connect() function succeeds, it returns 0. Otherwise,
    the value SOCKET_ERROR is returned to indicate an error
    condition (and errno set accordingly).
    For stream based socket, if the connection is not
    established yet, connect returns SOCKET_ERROR and
    errno = EINPROGRESS.

  Remarks:
    None.
 */
int     connect( SOCKET s, struct sockaddr* name, int namelen );
/*****************************************************************************
  Function:
    int send( SOCKET s, const char* buf, int len, int flags )

  Summary:
    The send function is used to send outgoing data on an already
    connected socket.

  Description:
    The send function is used to send outgoing data on an already
    connected socket. This function is used to send a reliable,
    ordered stream of data bytes on a socket of type SOCK_STREAM
    but can also be used to send datagrams on a socket of type SOCK_DGRAM.

  Precondition:
    connect function should be called for TCP and UDP sockets.
    Server side, accept function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    buf - application data buffer containing data to transmit.
    len - length of data in bytes.
    flags - message flags. Currently this field is not supported.

  Returns:
    On success, send returns number of bytes sent.
    Zero indicates no data send.
    In case of error it returns SOCKET_ERROR
    (and errno set accordingly).

  Remarks:
    None.
 */
int     send( SOCKET s, const char* buf, int len, int flags );

/*****************************************************************************
  Function:
    int sendto(SOCKET s, const char* buf, int len, int flags, const struct sockaddr* to, int tolen)

  Summary:
    This function used to send the data for both connection oriented and connection-less
    sockets.

  Description:
    The sendto function is used to send outgoing data on a socket.
    The destination address is given by to and tolen. Both
    Datagram and stream sockets are supported.

  Precondition:
    socket function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    buf - application data buffer containing data to transmit.
    len - length of data in bytes.
    flags - message flags. Currently this field is not supported.
    to - Optional pointer to the the sockaddr structure containing the
        destination address.  If NULL, the currently bound remote port and IP
        address are used as the destination.
    tolen - length of the sockaddr structure.

  Returns:
    On success, sendto returns number of bytes sent. In case of
    error returns SOCKET_ERROR (and errno set accordingly).

  Remarks:
    None.
 */
int     sendto( SOCKET s, const char* buf, int len, int flags, const struct sockaddr* to, int tolen );
/*****************************************************************************
  Function:
    int recv( SOCKET s, char* buf, int len, int flags )

  Summary:
    The recv() function is used to receive incoming data that has
    been queued for a socket.

  Description:
    The recv() function is used to receive incoming data that has
    been queued for a socket. This function can be used with both
    datagram and stream socket. If the available data
    is too large to fit in the supplied application buffer buf,
    excess bytes are discarded in case of SOCK_DGRAM type
    sockets.  For SOCK_STREAM types, the data is buffered
    internally so the application can retreive all data by
    multiple calls of recvfrom.

  Precondition:
    connect function should be called for TCP and UDP sockets.
    Server side, accept function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    buf - application data receive buffer.
    len - buffer length in bytes.
    flags - no significance in this implementation

  Returns:
    If recv is successful, the number of bytes copied to
    application buffer buf is returned.
    A return value of SOCKET_ERROR (-1)
    indicates an error condition (and errno set accordingly).
    A value of zero indicates socket has been shutdown by the peer.

  Remarks:
    None.
 */
int     recv( SOCKET s, char* buf, int len, int flags );

/*****************************************************************************
  Function:
    int recvfrom(SOCKET s, char* buf, int len, int flags, struct sockaddr* from, int* fromlen)

  Summary:
    The recvfrom() function is used to receive incoming data that
    has been queued for a socket.

  Description:
    The recvfrom() function is used to receive incoming data that
    has been queued for a socket. This function can be used with
    both datagram and stream type sockets. If the available data
    is too large to fit in the supplied application buffer buf,
    excess bytes are discarded in case of SOCK_DGRAM type
    sockets. For SOCK_STREAM types, the data is buffered
    internally so the application can retreive all data by
    multiple calls of recvfrom.

  Precondition:
    socket function should be called.

  Parameters:
    s - Socket descriptor returned from a previous call to socket.
    buf - application data receive buffer.
    len - buffer length in bytes.
    flags - message flags. Currently this is not supported.
    from - pointer to the sockaddr structure that will be
    filled in with the destination address.
    fromlen - size of buffer pointed by from.

  Returns:
    If recvfrom is successful, the number of bytes copied to
    application buffer buf is returned.
    A return value of SOCKET_ERROR (-1)
    indicates an error condition (and errno set accordingly).
    A value of zero indicates socket has been shutdown by the peer.

  Remarks:
    None.
 */
int     recvfrom( SOCKET s, char* buf, int len, int flags, struct sockaddr* from, int* fromlen );
/*****************************************************************************
  Function:
    int gethostname(char* name, int namelen )

  Summary:
    Returns the standard host name for the system.

  Description:
    This function returns the standard host name of the system which is
    calling this function.  The returned name is null-terminated.

  Precondition:
    None.

  Parameters:
    name - Pointer to a buffer that receives the local host name.
    namelen - size of the name array.

  Returns:
    Success will return a value of 0.
    If name is too short to hold the host name or any other error occurs,
    SOCKET_ERROR (-1) will be returned (and errno set accordingly).
    On error, *name will be unmodified
    and no null terminator will be generated.

  Remarks:
    The function returns the host name as set on the default network interface.
 */
int     gethostname(char* name, int namelen);

/*****************************************************************************
  Function:
    int closesocket( SOCKET s )

  Summary:
    The closesocket function closes an existing socket.

  Description:
    The closesocket function closes an existing socket.
    This function releases the socket descriptor s.
    Any data buffered at the socket is discarded.  If the
    socket s is no longer needed, closesocket() must be
    called in order to release all resources associated with s.

  Precondition:
    None.

  Parameters:
    s - Socket descriptor returned from a previous call to socket

  Returns:
    If closesocket is successful, a value of 0 is returned.
    A return value of SOCKET_ERROR (-1) indicates an error.
    (and errno set accordingly).

  Remarks:
    None.
 */
int     closesocket( SOCKET s );

#endif  // _BERKELEY_API_HEADER_FILE


