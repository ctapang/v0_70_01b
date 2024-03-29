/*******************************************************************************
  HyperText Transfer Protocol (HTTP) Server

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    - Serves dynamic pages to web browsers such as Microsoft Internet 
      Explorer, Mozilla Firefox, etc.
    - Reference: RFC 2616
*******************************************************************************/

/*******************************************************************************
File Name:  HTTP.c
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

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_STACK_USE_HTTP_SERVER)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_HTTP_SERVER
  
#if !defined (SYS_FS_ENABLE)
#error "HTTP need SYS_FS service, please define SYS_FS_ENABLE in system_config.h"
#endif

#include "http_private.h"
#include "http_print.h"
#if defined (HARMONY_FS)
#include "driver/nvm/drv_nvm.h"
#include "app.h"
#define SYS_FS_ATTR_ZIP_COMPRESSED  ((uint16_t)0x0001)
#else
#include "tcpip/src/system/drivers/drv_media.h"
#include <tcpip/src/system/fs/sys_fs.h>
#endif

#define HTTP_FILE_ERR_DEBUG
/****************************************************************************
  Section:
	String Constants
  ***************************************************************************/
	static const uint8_t HTTP_CRLF[] = "\r\n";	// New line sequence
	#define HTTP_CRLF_LEN	2				// Length of above string
		
/****************************************************************************
  Section:
	File and Content Type Settings
  ***************************************************************************/
	// File type extensions corresponding to HTTP_FILE_TYPE
	static const char * const httpFileExtensions[HTTP_UNKNOWN+2] =
	{
	    "txt",          // HTTP_TXT
	    "htm",          // HTTP_HTM
	    "html",         // HTTP_HTML
	    "cgi",          // HTTP_CGI
	    "xml",          // HTTP_XML
	    "css",          // HTTP_CSS
	    "gif",          // HTTP_GIF
	    "png",          // HTTP_PNG
	    "jpg",          // HTTP_JPG
	    "js",          // HTTP_JAVA
        "cla",          // HTTP_JAVA
	    "wav",          // HTTP_WAV
		"\0\0\0"		// HTTP_UNKNOWN
	};
	
	// Content-type strings corresponding to HTTP_FILE_TYPE
	static const char * const httpContentTypes[HTTP_UNKNOWN+2] =
	{
	    "text/plain",            // HTTP_TXT
	    "text/html",             // HTTP_HTM
	    "text/html",             // HTTP_HTML
	    "text/html",             // HTTP_CGI
	    "text/xml",              // HTTP_XML
	    "text/css",              // HTTP_CSS
	    "image/gif",             // HTTP_GIF
	    "image/png",             // HTTP_PNG
	    "image/jpeg",            // HTTP_JPG
	    "application/x-javascript",   // HTTP_JAVA
	    "application/java-vm",   // HTTP_JAVA
	    "audio/x-wave",          // HTTP_WAV
		""						 // HTTP_UNKNOWN
	};
		
/****************************************************************************
  Section:
	Commands and Server Responses
  ***************************************************************************/

	// Initial response strings (Corresponding to HTTP_STATUS)
	static const char * const HTTPResponseHeaders[] =
	{
		"HTTP/1.1 200 OK\r\nConnection: close\r\n",
		"HTTP/1.1 200 OK\r\nConnection: close\r\n",
		"HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n400 Bad Request: can't handle Content-Length\r\n",
		"HTTP/1.1 401 Unauthorized\r\nWWW-Authenticate: Basic realm=\"Protected\"\r\nConnection: close\r\n\r\n401 Unauthorized: Password required\r\n",
		#if defined(HTTP_FILE_UPLOAD)
		"HTTP/1.1 404 Not found\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n404: File not found<br>Use <a href=\"/" HTTP_FILE_UPLOAD "\">MPFS Upload</a> to program web pages\r\n",
		#else		
		"HTTP/1.1 404 Not found\r\nConnection: close\r\n\r\n404: File not found\r\n",
		#endif
		"HTTP/1.1 414 Request-URI Too Long\r\nConnection: close\r\n\r\n414 Request-URI Too Long: Buffer overflow detected\r\n",
		"HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\n500 Internal Server Error: Expected data not present\r\n",
		"HTTP/1.1 501 Not Implemented\r\nConnection: close\r\n\r\n501 Not Implemented: Only GET and POST supported\r\n",
		"HTTP/1.1 302 Found\r\nConnection: close\r\nLocation: ",
		"HTTP/1.1 403 Forbidden\r\nConnection: close\r\n\r\n403 Forbidden: SSL Required - use HTTPS\r\n",

		#if defined(HTTP_FILE_UPLOAD)
		"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n<html><body style=\"margin:100px\"><form method=post action=\"/" HTTP_FILE_UPLOAD "\" enctype=\"multipart/form-data\"><b>MPFS Image Upload</b><p><input type=file name=i size=40> &nbsp; <input type=submit value=\"Upload\"></form></body></html>",
		"",
		"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n<html><body style=\"margin:100px\"><b>MPFS Update Successful</b><p><a href=\"/\">Site main page</a></body></html>",
		"HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n<html><body style=\"margin:100px\"><b>MPFS Image Corrupt or Wrong Version</b><p><a href=\"/" HTTP_FILE_UPLOAD "\">Try again?</a></body></html>",
		#endif

	};
	
/****************************************************************************
  Section:
	Header Parsing Configuration
  ***************************************************************************/
	
	// Header strings for which we'd like to parse
	static const char * const HTTPRequestHeaders[] =
	{
		"Cookie:",
		"Authorization:",
		"Content-Length:"
	};
	
/****************************************************************************
  Section:
	HTTP Connection State Global Variables
  ***************************************************************************/
static HTTP_CONN*           httpConnCtrl = 0;        // all http connections
static uint8_t*             httpConnData = 0;       // http conenctions data space
static int                  httpConnNo = 0;         // number of HTTP connections
static int                  httpInitCount = 0;      // module init counter
static HTTP_MODULE_FLAGS    httpConfigFlags = 0;    // run time flags


static const HTTP_MODULE_CONFIG httpConfigDefault = 
{
    HTTP_MAX_CONNECTIONS,
    HTTP_MAX_DATA_LEN,
    HTTP_SKT_TX_BUFF_SIZE,
    HTTP_SKT_RX_BUFF_SIZE,
    HTTP_CONFIG_FLAGS,

};


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/
static void _HTTP_HeaderParseLookup(HTTP_CONN* pHttpCon, int i);
	#if defined(HTTP_USE_COOKIES)
  static void _HTTP_HeaderParseCookie(HTTP_CONN* pHttpCon);
	#endif
	#if defined(HTTP_USE_AUTHENTICATION)
  static void _HTTP_HeaderParseAuthorization(HTTP_CONN* pHttpCon);
	#endif
	#if defined(HTTP_USE_POST)
  static void _HTTP_HeaderParseContentLength(HTTP_CONN* pHttpCon);
  static HTTP_READ_STATUS _HTTP_ReadTo(HTTP_CONN* pHttpCon, uint8_t delim, uint8_t* buf, uint16_t len);
	#endif
	
	static void TCPIP_HTTP_Process(HTTP_CONN* pHttpCon);
	static bool TCPIP_HTTP_FileSend(HTTP_CONN* pHttpCon);
static bool TCPIP_HTTP_WebPageIsDynamic(HTTP_CONN* pHttpCon);

	#if defined(HTTP_FILE_UPLOAD)
static HTTP_IO_RESULT _HTTP_MPFSUpload(HTTP_CONN* pHttpCon);
	#endif

	#define mMIN(a, b)	((a<b)?a:b)

#if defined(HTTP_FILE_UPLOAD)
    static bool     _HTTP_SetMediaWriteHeader(HTTP_CONN* pHttpCon, const uint8_t* buffer, unsigned int nBytes);
    static void     _HTTP_ReleaseMedia(HTTP_CONN* pHttpCon);
#endif  // defined(HTTP_FILE_UPLOAD)

static int8_t fileErr = 0;

//#define HTTP_FILERD_ERR_DEBUG

static void _HTTP_FileRdCheck(int condt, char *file, int32_t line)
{
    if (condt == 0) {
        #if defined(HTTP_FILE_ERR_DEBUG)
        SYS_CONSOLE_PRINT("%s, at line: %d\r\n", file, line);
        #endif
        fileErr = 1;
        //while(1);
    }
}

static void _HTTP_Cleanup(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    if(httpConnData)
    {
        TCPIP_HEAP_Free(stackCtrl->memH, httpConnData);
        httpConnData = 0;
    }
    if(httpConnCtrl)
    {
        TCPIP_HEAP_Free(stackCtrl->memH, httpConnCtrl);
        httpConnCtrl = 0;
    }

    httpConnNo = 0;
}


/*****************************************************************************
  Function:
	bool TCPIP_HTTP_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, 
        const HTTP_MODULE_CONFIG* httpInitData)

  Summary:
	Initializes the HTTP server module.

  Description:
	Sets all HTTP sockets to the listening state, and initializes the
	state machine and file handles for each connection.  If SSL is
	enabled, opens a socket on that port as well.

  Precondition:
	TCP must already be initialized.

  Parameters:
	None

  Returns:
  	true if initialization succeeded,
    false otherwise
  	
  Remarks:
	This function is called only one during lifetime of the application.
  ***************************************************************************/
bool TCPIP_HTTP_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl,
              const HTTP_MODULE_CONFIG* httpInitData)
{
    bool        initFail;
    int         conn;
    HTTP_CONN*  pHttpCon;
    uint8_t*    pHttpData;

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface restart
        return true;
    }

    // stack init
    initFail = false;
    while(httpInitCount == 0)
    {   // first time we're run

        if(httpInitData == 0)
        {
            httpInitData = &httpConfigDefault;
        }
        httpConnNo = httpInitData->nConnections;
        httpConfigFlags = httpInitData->configFlags;

        if(httpConnNo)
        {
            httpConnCtrl = (HTTP_CONN*)TCPIP_HEAP_Calloc(stackCtrl->memH, httpConnNo, sizeof(*httpConnCtrl));
            httpConnData = (uint8_t*)TCPIP_HEAP_Malloc(stackCtrl->memH, httpConnNo * httpInitData->dataLen);
            if(httpConnCtrl == 0 || httpConnData == 0)
            {   // failed
                SYS_ERROR(SYS_ERROR_ERROR, " HTTP: Dynamic allocation failed");
                initFail = true;
                break;
            }

            // initialize all connections
            pHttpCon = httpConnCtrl + 0;
            pHttpData = httpConnData;
            for(conn = 0; conn < httpConnNo ; conn++)
            {
                pHttpCon->sm = SM_HTTP_IDLE;
                pHttpCon->socket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_ANY, HTTP_PORT, 0);
                if( pHttpCon->socket == INVALID_SOCKET)
                {   // failed to open the socket
                    SYS_ERROR(SYS_ERROR_ERROR, " HTTP: Socket creation failed");
                    initFail = true;
                    break;
                }

                // set socket options
                if((httpConfigFlags & HTTP_MODULE_FLAG_NO_DELAY) != 0)
                {
                    void* tcpForceFlush = (void*)1;
                    TCPIP_TCP_OptionsSet(pHttpCon->socket, TCP_OPTION_NODELAY, (void*)tcpForceFlush);
                }
                if(httpInitData->sktTxBuffSize != 0)
                {
                    void* tcpBuffSize = (void*)(unsigned int)httpInitData->sktTxBuffSize;
                    TCPIP_TCP_OptionsSet(pHttpCon->socket, TCP_OPTION_TX_BUFF, tcpBuffSize);
                }
                if(httpInitData->sktRxBuffSize != 0)
                {
                    void* tcpBuffSize = (void*)(unsigned int)httpInitData->sktRxBuffSize;
                    TCPIP_TCP_OptionsSet(pHttpCon->socket, TCP_OPTION_RX_BUFF, tcpBuffSize);
                }

#if defined(TCPIP_STACK_USE_SSL_SERVER)
                TCPIP_TCPSSL_ListenerAdd(pHttpCon->socket, HTTPS_PORT);
#endif

                // Save the default record (just invalid file handles)
                pHttpCon->file = -1;
                pHttpCon->data = pHttpData;
                pHttpCon->connIx = (uint16_t)conn;
                pHttpCon++;
                pHttpData += httpInitData->dataLen;
            }
        }

        break;
    }

    if(initFail)
    {
        _HTTP_Cleanup(stackCtrl);
        return false;
    }

    httpInitCount++;
    return true;    
}
	
/*****************************************************************************
  Function:
	bool TCPIP_HTTP_Deinitialize(void)

  Summary:
	DeInitializes the HTTP server module.

  Description:
	Takes down all HTTP sockets, the state machine and file handles for 
	each connection.  If SSL is enabled, closes a socket on that port as well.

  Precondition:
	None

  Parameters:
	None

  Returns:
	None
  	
  Remarks:
	This function is called only one during lifetime of the application.
  ***************************************************************************/
void TCPIP_HTTP_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT) // stack shut down
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN) // interface down

    // one way or another this interface is going down
    HTTP_CONN* pHttpCon;
    int  conn;

    pHttpCon = httpConnCtrl + 0;
    for (conn = 0; conn < httpConnNo; conn++)
    {
        // Close the connections that were associated with this interface
        if (pHttpCon->socket != INVALID_SOCKET)
        {
            if (TCPIP_TCP_SocketNetGet(pHttpCon->socket) == stackCtrl->pNetIf)
            {
                if(pHttpCon->file != -1)
#if defined (HARMONY_FS)
                SYS_FS_FileClose(pHttpCon->file);
#else
                SYS_FS_close(pHttpCon->file);
#endif
                pHttpCon->file = -1;

                if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
                {   // stack going down
                    TCPIP_TCP_Close(pHttpCon->socket);
                    pHttpCon->socket = INVALID_SOCKET;
                }
                else 
                {   // TCPIP_STACK_ACTION_IF_DOWN - interface down
                    TCPIP_TCP_Disconnect(pHttpCon->socket);
                }
            }
        }
        pHttpCon++;
    }

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
    {   // stack shut down
        if(httpInitCount > 0)
        {   // we're up and running
            if(--httpInitCount == 0)
            {   // all closed
                // release resources
                _HTTP_Cleanup(stackCtrl);
            }
        }
    }
}

/*****************************************************************************
  Function:
	void TCPIP_HTTP_Server(void)

  Summary:
	Performs periodic tasks for the HTTP module.

  Description:
	Browses through each open connection and attempts to process any
	pending operations.

  Precondition:
	TCPIP_HTTP_Initialize() must already be called.

  Parameters:
	None

  Returns:
  	None
  	
  Remarks:
	This function acts as a task (similar to one in an RTOS).  It
	performs its task in a co-operative manner, and the main application
	must call this function repeatedly to ensure that all open or new
	connections are served in a timely fashion.
  ***************************************************************************/
void TCPIP_HTTP_Server(void)
{
    HTTP_CONN* pHttpCon;
    int conn;

    pHttpCon = httpConnCtrl + 0;
	for(conn = 0; conn < httpConnNo; conn++, pHttpCon++)
    {
        if(pHttpCon->socket == INVALID_SOCKET)
            continue;

        // If a socket is disconnected at any time 
        // forget about it and return to idle state.
        // Must do this here, otherwise we will wait until a new
        // connection arrives, which causes problems with Linux and with SSL
        if(TCPIP_TCP_WasReset(pHttpCon->socket))
        {
            pHttpCon->sm = SM_HTTP_IDLE;
            pHttpCon->file_sm = SM_IDLE;

            // Make sure any opened files are closed
#if defined (HARMONY_FS)
           if(pHttpCon->file != SYS_FS_HANDLE_INVALID)
#else
           if(pHttpCon->file != RETURN_FAILED)
#endif
            {
#if defined (HARMONY_FS)
                SYS_FS_FileClose(pHttpCon->file);
#else
                SYS_FS_close(pHttpCon->file);
#endif
                pHttpCon->file = -1;
                // Important to clear related control variables,
                // or serving continuous refresh(F5) by IE etc... will meet issue
                memset((void *)&pHttpCon->TxFile, 0, sizeof(FILE_CTRL));
            }
            if((httpConfigFlags & HTTP_MODULE_FLAG_ADJUST_SKT_FIFOS) != 0)
            {
                // Adjust FIFO sizes to half and half.  Default state must remain
                // here so that SSL handshakes, if required, can proceed
                TCPIP_TCP_FifoSizeAdjust(pHttpCon->socket, 1, 0, TCP_ADJUST_PRESERVE_RX);
            }
        }

        // Determine if this connection is eligible for processing
        if(pHttpCon->sm != SM_HTTP_IDLE || TCPIP_TCP_GetIsReady(pHttpCon->socket))
        {
            TCPIP_HTTP_Process(pHttpCon);
        }
    }
}

/*****************************************************************************
  Function:
	static void TCPIP_HTTP_Process(HTTP_CONN* pHttpCon)

  Description:
	Performs any pending operations for the currently loaded HTTP connection.

  Precondition:
	TCPIP_HTTP_Initialize() and HTTPLoadConn() have been called.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

static void TCPIP_HTTP_Process(HTTP_CONN* pHttpCon)
{
    uint16_t lenA, lenB;
    int i;
    uint8_t c;
    bool isDone;
    uint8_t * ptr = NULL;
    uint8_t *ext;
    uint8_t buffer[HTTP_MAX_HEADER_LEN+1];
#if defined (HARMONY_FS)
    SYS_FS_FSTAT fs_attr = {0};
#else
    FILE_STAT fs_attr = {0};
#endif

    do
    {
        isDone = true;

        switch(pHttpCon->sm)
        {

            case SM_HTTP_IDLE:

                // Check how much data is waiting
                lenA = TCPIP_TCP_GetIsReady(pHttpCon->socket);

                // If a connection has been made, then process the request
                if(lenA)
                {// Clear out state info and move to next state
                    pHttpCon->ptrData = pHttpCon->data;
                    pHttpCon->sm = SM_HTTP_PARSE_REQUEST;
                    pHttpCon->isAuthorized = 0xff;
                    pHttpCon->hasArgs = false;
                    pHttpCon->httpTick = SYS_TICK_Get() + HTTP_TIMEOUT*SYS_TICK_TicksPerSecondGet();
                    pHttpCon->callbackPos = 0xffffffff;
                    pHttpCon->byteCount = 0;
                    pHttpCon->nameHash = 0;
#if defined(HTTP_USE_POST)
                    pHttpCon->smPost = 0x00;
#endif
                    pHttpCon->TxFile.fileTxDone = 0;
                    if((httpConfigFlags & HTTP_MODULE_FLAG_ADJUST_SKT_FIFOS) != 0)
                    {
                        // Adjust the TCP FIFOs for optimal reception of 
                        // the next HTTP request from the browser
                        TCPIP_TCP_FifoSizeAdjust(pHttpCon->socket, 1, 0, TCP_ADJUST_PRESERVE_RX | TCP_ADJUST_GIVE_REST_TO_RX);
                    }
                }
                else
                    // Don't break for new connections.  There may be
                    // an entire request in the buffer already.
                    break;

            case SM_HTTP_PARSE_REQUEST:

                // Verify the entire first line is in the FIFO
                if(TCPIP_TCP_Find(pHttpCon->socket, '\n', 0, 0, false) == 0xffff)
                {// First line isn't here yet
                    if(TCPIP_TCP_FifoRxFreeGet(pHttpCon->socket) == 0u)
                    {// If the FIFO is full, we overflowed
                        pHttpCon->httpStatus = HTTP_OVERFLOW;
                        pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                        isDone = false;
                    }
                    if(SYS_TICK_Get() > pHttpCon->httpTick)
                    {// A timeout has occurred
                        TCPIP_TCP_Disconnect(pHttpCon->socket);
                        pHttpCon->sm = SM_HTTP_DISCONNECT;
                        isDone = false;
                    }
                    break;
                }

                // Reset the watchdog timer
                pHttpCon->httpTick = SYS_TICK_Get() + HTTP_TIMEOUT*SYS_TICK_TicksPerSecondGet();

                // Determine the request method
                lenA = TCPIP_TCP_Find(pHttpCon->socket, ' ', 0, 0, false);
                if(lenA > 5u)
                    lenA = 5;
                TCPIP_TCP_ArrayGet(pHttpCon->socket, pHttpCon->data, lenA+1);

                if ( memcmp(pHttpCon->data, (const void*)"GET", 3) == 0)
                    pHttpCon->httpStatus = HTTP_GET;
#if defined(HTTP_USE_POST)
                else if ( memcmp(pHttpCon->data, (const void*)"POST", 4) == 0)
                    pHttpCon->httpStatus = HTTP_POST;
#endif
                else
                {// Unrecognized method, so return not implemented
                    pHttpCon->httpStatus = HTTP_NOT_IMPLEMENTED;
                    pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                    isDone = false;
                    break;
                }

                // Find end of filename
                lenA = TCPIP_TCP_Find(pHttpCon->socket, ' ', 0, 0, false);
                lenB = TCPIP_TCP_Find(pHttpCon->socket, '?', 0, lenA, false);
                lenA = mMIN(lenA, lenB);

                // If the file name is too long, then reject the request
                if(lenA > HTTP_MAX_DATA_LEN - HTTP_DEFAULT_LEN - 1)
                {
                    pHttpCon->httpStatus = HTTP_OVERFLOW;
                    pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                    isDone = false;
                    break;
                }

                // Read in the filename and decode
                lenB = TCPIP_TCP_ArrayGet(pHttpCon->socket, pHttpCon->data, lenA);
                pHttpCon->data[lenB] = '\0';
                TCPIP_HTTP_URLDecode(pHttpCon->data);

                // Decode may have changed the string length - update it here
                lenB = strlen((char*)pHttpCon->data);

                // Check if this is an MPFS Upload
#if defined(HTTP_FILE_UPLOAD)
                if(memcmp(&pHttpCon->data[1], HTTP_FILE_UPLOAD, sizeof(HTTP_FILE_UPLOAD)) == 0)
                {// Read remainder of line, and bypass all file opening, etc.
#if defined(HTTP_USE_AUTHENTICATION)
				pHttpCon->isAuthorized = HTTPNeedsAuth(pHttpCon, &pHttpCon->data[1]);
#endif
                    if(pHttpCon->httpStatus == HTTP_GET)
                        pHttpCon->httpStatus = HTTP_MPFS_FORM;
                    else
                        pHttpCon->httpStatus = HTTP_MPFS_UP;

                    pHttpCon->sm = SM_HTTP_PARSE_HEADERS;
                    isDone = false;
                    break;
                }
#endif

                // If the last character is a not a directory delimiter, then try to open the file
                // String starts at 2nd character, because the first is always a '/'
            if(pHttpCon->data[lenB-1] != '/') {
#if defined (HARMONY_FS)
                pHttpCon->file = SYS_FS_FileOpen_Wrapper((char *)&pHttpCon->data[1],SYS_FS_FILE_OPEN_READ);
                strcpy((void*)&pHttpCon->fileName, (char *)&pHttpCon->data[1]);
#else
                    pHttpCon->file = SYS_FS_open((char *)&pHttpCon->data[1], 0);
#endif
            }

                // If the open fails, then add our default name and try again
#if defined (HARMONY_FS)
           if(pHttpCon->file == SYS_FS_HANDLE_INVALID)
#else
           if(pHttpCon->file == RETURN_FAILED)
#endif
                {
                    // Add the directory delimiter if needed
                    if(pHttpCon->data[lenB-1] != '/')
                        pHttpCon->data[lenB++] = '/';

                    // Add our default file name
#if defined(TCPIP_STACK_USE_SSL_SERVER)
                    if(TCPIP_TCP_SocketIsSecuredBySSL(pHttpCon->socket))
                    {
                        strcpy((void*)&pHttpCon->data[lenB], HTTPS_DEFAULT_FILE);
                        lenB += strlen(HTTPS_DEFAULT_FILE);
                    }
                    else
#endif
                    {
                        strcpy((void*)&pHttpCon->data[lenB], HTTP_DEFAULT_FILE);
                        lenB += strlen(HTTP_DEFAULT_FILE);
                    }
                    // Try to open again
#if defined (HARMONY_FS)
                pHttpCon->file = SYS_FS_FileOpen_Wrapper((char *)&pHttpCon->data[1],SYS_FS_FILE_OPEN_READ);
//                if (pHttpCon->file == SYS_FS_HANDLE_INVALID)
//                {
//                    pHttpCon->httpStatus = HTTP_NOT_FOUND;
//                    pHttpCon->sm = SM_HTTP_PARSE_REQUEST;
//                }
                strcpy((void*)&pHttpCon->fileName, (char *)&pHttpCon->data[1]);
#else
                    pHttpCon->file = SYS_FS_open((char *)&pHttpCon->data[1], 0);
#endif
                }

                //Calculate 2 Bytes HashIndex for  pHttpCon->file->name
                // Calculate the name hash to speed up searching
                for(pHttpCon->nameHash = 0, ptr = (uint8_t*)(&pHttpCon->data[1]); ptr !=(uint8_t*) (&pHttpCon->data[lenB]); ptr++)
                {
                    if(*ptr != 0x20)
                    {
                        pHttpCon->nameHash += *ptr;
                        pHttpCon->nameHash <<= 1;
                    }
                }

                // Find the extension in the filename
                for(ext = pHttpCon->data + lenB-1; ext != pHttpCon->data; ext--)
                    if(*ext == '.')
                        break;

                // Compare to known extensions to determine Content-Type
                ext++;
                for(pHttpCon->fileType = HTTP_TXT; pHttpCon->fileType < HTTP_UNKNOWN; pHttpCon->fileType++)
                    if(!stricmppgm2ram(ext, (const void*)httpFileExtensions[pHttpCon->fileType]))
                        break;

                // Perform first round authentication (pass file name only)
#if defined(HTTP_USE_AUTHENTICATION)
                pHttpCon->isAuthorized = HTTPNeedsAuth(pHttpCon, &pHttpCon->data[1]);
#endif

                // If the file was found, see if it has an index
                // Index file is not needed any more, because of FileRcrd.bin and DynRcrd.bin used

                // Read GET args, up to buffer size - 1
                lenA = TCPIP_TCP_Find(pHttpCon->socket, ' ', 0, 0, false);
                if(lenA != 0u)
                {
                    pHttpCon->hasArgs = true;

                    // Trash the '?'
                    TCPIP_TCP_Get(pHttpCon->socket, &c);

                    // Verify there's enough space
                    lenA--;
                    if(lenA >= HTTP_MAX_DATA_LEN - 2)
                    {
                        pHttpCon->httpStatus = HTTP_OVERFLOW;
                        pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                        isDone = false;
                        break;
                    }

                    // Read in the arguments and '&'-terminate in anticipation of cookies
                    pHttpCon->ptrData += TCPIP_TCP_ArrayGet(pHttpCon->socket, pHttpCon->data, lenA);
                    *(pHttpCon->ptrData++) = '&';

                }

                // Clear the rest of the line
                lenA = TCPIP_TCP_Find(pHttpCon->socket, '\n', 0, 0, false);
                TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, lenA + 1);

                // Move to parsing the headers
                pHttpCon->sm = SM_HTTP_PARSE_HEADERS;

                // No break, continue to parsing headers

            case SM_HTTP_PARSE_HEADERS:

                // Loop over all the headers
                while(1)
                {
                    // Make sure entire line is in the FIFO
                    lenA = TCPIP_TCP_Find(pHttpCon->socket, '\n', 0, 0, false);
                    if(lenA == 0xffff)
                    {// If not, make sure we can receive more data
                        if(TCPIP_TCP_FifoRxFreeGet(pHttpCon->socket) == 0u)
                        {// Overflow
                            pHttpCon->httpStatus = HTTP_OVERFLOW;
                            pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                            isDone = false;
                        }
                        if(SYS_TICK_Get() > pHttpCon->httpTick)
                        {// A timeout has occured
                            TCPIP_TCP_Disconnect(pHttpCon->socket);
                            pHttpCon->sm = SM_HTTP_DISCONNECT;
                            isDone = false;
                        }
                        break;
                    }

                    // Reset the watchdog timer
                    pHttpCon->httpTick = SYS_TICK_Get() + HTTP_TIMEOUT*SYS_TICK_TicksPerSecondGet();

                    // If a CRLF is immediate, then headers are done
                    if(lenA == 1u)
                    {// Remove the CRLF and move to next state
                        TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, 2);
                        pHttpCon->sm = SM_HTTP_AUTHENTICATE;
                        isDone = false;
                        break;
                    }

                    // Find the header name, and use isDone as a flag to indicate a match
                    lenB = TCPIP_TCP_Find(pHttpCon->socket, ':', 0, lenA, false) + 2;
                    isDone = false;

                    // If name is too long or this line isn't a header, ignore it
                    if(lenB > sizeof(buffer))
                    {
                        TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, lenA+1);
                        continue;
                    }

                    // Read in the header name
                    TCPIP_TCP_ArrayGet(pHttpCon->socket, buffer, lenB);
                    buffer[lenB-1] = '\0';
                    lenA -= lenB;

                    // Compare header read to ones we're interested in
                    for(i = 0; i < sizeof(HTTPRequestHeaders)/sizeof(HTTPRequestHeaders[0]); i++)
                    {
                        if(strcmp((char*)buffer, (const char *)HTTPRequestHeaders[i]) == 0)
                        {// Parse the header and stop the loop
                        _HTTP_HeaderParseLookup(pHttpCon, i);
                            isDone = true;
                            break;
                        }
                    }

                    // Clear the rest of the line, and call the loop again
                    if(isDone)
                    {// We already know how much to remove unless a header was found
                        lenA = TCPIP_TCP_Find(pHttpCon->socket, '\n', 0, 0, false);
                    }
                    TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, lenA+1);
                }

                break;

            case SM_HTTP_AUTHENTICATE:

#if defined(HTTP_USE_AUTHENTICATION)
                // Check current authorization state
                if(pHttpCon->isAuthorized < 0x80)
                {// 401 error
                    pHttpCon->httpStatus = HTTP_UNAUTHORIZED;
                    pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                    isDone = false;

#if defined(HTTP_NO_AUTH_WITHOUT_SSL)
                    if(!TCPIP_TCP_SocketIsSecuredBySSL(pHttpCon->socket))
                        pHttpCon->httpStatus = HTTP_SSL_REQUIRED;
#endif

                    break;
                }
#endif

                // Parse the args string
                *pHttpCon->ptrData = '\0';
                pHttpCon->ptrData = TCPIP_HTTP_URLDecode(pHttpCon->data);

                // If this is an MPFS upload form request, bypass to headers
#if defined(HTTP_FILE_UPLOAD)
                if(pHttpCon->httpStatus == HTTP_MPFS_FORM)
                {
                    pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                    isDone = false;
                    break;
                }
#endif

                // Move on to GET args, unless there are none
                pHttpCon->sm = SM_HTTP_PROCESS_GET;
                if(!pHttpCon->hasArgs)
                    pHttpCon->sm = SM_HTTP_PROCESS_POST;
                isDone = false;
                pHttpCon->hasArgs = false;
                break;

            case SM_HTTP_PROCESS_GET:

                // Run the application callback HTTPExecuteGet()
                if(HTTPExecuteGet(pHttpCon) == HTTP_IO_WAITING)
                {// If waiting for asynchronous process, return to main app
                    break;
                }

                // Move on to POST data
                pHttpCon->sm = SM_HTTP_PROCESS_POST;

            case SM_HTTP_PROCESS_POST:

#if defined(HTTP_USE_POST)

                // See if we have any new data
                if(TCPIP_TCP_GetIsReady(pHttpCon->socket) == pHttpCon->callbackPos)
                {
                    if(SYS_TICK_Get() > pHttpCon->httpTick)
                    {// If a timeout has occured, disconnect
                        TCPIP_TCP_Disconnect(pHttpCon->socket);
                        pHttpCon->sm = SM_HTTP_DISCONNECT;
                        isDone = false;
                        break;
                    }
                }

                if(pHttpCon->httpStatus == HTTP_POST
#if defined(HTTP_FILE_UPLOAD)
                        || (pHttpCon->httpStatus >= HTTP_MPFS_UP && pHttpCon->httpStatus <= HTTP_MPFS_ERROR)
#endif
                  )
                {
                    // Run the application callback HTTPExecutePost()
#if defined(HTTP_FILE_UPLOAD)
                    if(pHttpCon->httpStatus >= HTTP_MPFS_UP && pHttpCon->httpStatus <= HTTP_MPFS_ERROR)
                    {
                    c = _HTTP_MPFSUpload(pHttpCon);
                        if(c == (uint8_t)HTTP_IO_DONE)
                        {
                            pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                            isDone = false;
                            break;
                        }
                    }
                    else
#endif
                        c = HTTPExecutePost(pHttpCon);

                    // If waiting for asynchronous process, return to main app
                    if(c == (uint8_t)HTTP_IO_WAITING)
                    {// return to main app and make sure we don't get stuck by the watchdog
                        pHttpCon->callbackPos = TCPIP_TCP_GetIsReady(pHttpCon->socket) - 1;
                        break;
                    }
                    else if(c == (uint8_t)HTTP_IO_NEED_DATA)
                    {// If waiting for more data
                        pHttpCon->callbackPos = TCPIP_TCP_GetIsReady(pHttpCon->socket);
                        pHttpCon->httpTick = SYS_TICK_Get() + HTTP_TIMEOUT*SYS_TICK_TicksPerSecondGet();

                        // If more is expected and space is available, return to main app
                        if(pHttpCon->byteCount > pHttpCon->callbackPos && TCPIP_TCP_FifoRxFreeGet(pHttpCon->socket) != 0u)
                            break;

                        // Handle cases where application ran out of data or buffer space
                        pHttpCon->httpStatus = HTTP_INTERNAL_SERVER_ERROR;
                        pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                        isDone = false;
                        break;
                    }
                }
#endif

                // We're done with POST
                pHttpCon->sm = SM_HTTP_PROCESS_REQUEST;
                // No break, continue to sending request

            case SM_HTTP_PROCESS_REQUEST:

                // Check for 404
#if defined (HARMONY_FS)
           if(pHttpCon->file == SYS_FS_HANDLE_INVALID)
#else
           if(pHttpCon->file == RETURN_FAILED)
#endif
                {
                    pHttpCon->httpStatus = HTTP_NOT_FOUND;
                    pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                    isDone = false;
                    break;
                }

                // Set up the dynamic substitutions
                pHttpCon->byteCount = 0;

                // Move to next state
                pHttpCon->sm = SM_HTTP_SERVE_HEADERS;

            case SM_HTTP_SERVE_HEADERS:

                // We're in write mode now:
                if((httpConfigFlags & HTTP_MODULE_FLAG_ADJUST_SKT_FIFOS) != 0)
                {
                    // Adjust the TCP FIFOs for optimal transmission of 
                    // the HTTP response to the browser
                    TCPIP_TCP_FifoSizeAdjust(pHttpCon->socket, 1, 0, TCP_ADJUST_GIVE_REST_TO_TX);
                }
                // Send headers
                TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)HTTPResponseHeaders[pHttpCon->httpStatus]);

                // If this is a redirect, print the rest of the Location: header
                if(pHttpCon->httpStatus == HTTP_REDIRECT)
                {
                    TCPIP_TCP_StringPut(pHttpCon->socket, pHttpCon->data);
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"\r\n\r\n304 Redirect: ");
                    TCPIP_TCP_StringPut(pHttpCon->socket, pHttpCon->data);
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)HTTP_CRLF);
                }

                // If not GET or POST, we're done
                if(pHttpCon->httpStatus != HTTP_GET && pHttpCon->httpStatus != HTTP_POST)
                {// Disconnect
                    pHttpCon->sm = SM_HTTP_DISCONNECT;
                    break;
                }

                // Output the content type, if known
                if(pHttpCon->fileType != HTTP_UNKNOWN)
                {
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"Content-Type: ");
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)httpContentTypes[pHttpCon->fileType]);
                    TCPIP_TCP_StringPut(pHttpCon->socket, HTTP_CRLF);
                }

                // Output the gzip encoding header if needed
#if defined (HARMONY_FS)
            if(SYS_FS_FileStat_Wrapper((const char *)&pHttpCon->fileName, &fs_attr) != SYS_FS_HANDLE_INVALID) {
                 if (fs_attr.fattrib == SYS_FS_ATTR_ZIP_COMPRESSED)
                 {
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"Content-Encoding: gzip\r\n");
                 }
            }
#else
                if(SYS_FS_fstat(pHttpCon->file, &fs_attr) != -1) {
                    if (fs_attr.st_attr & SYS_FS_ATTR_ZIP_COMPRESSED)
                    {
                        TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"Content-Encoding: gzip\r\n");
                    }
               }
#endif
                // Output the cache-control
                TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"Cache-Control: ");
            if((pHttpCon->httpStatus == HTTP_POST) || (TCPIP_HTTP_WebPageIsDynamic(pHttpCon)))
                {// This is a dynamic page or a POST request, so no cache
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"no-cache");
                }
                else
                {// This is a static page, so save it for the specified amount of time
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"max-age=");
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)HTTP_CACHE_LEN);
                }
                TCPIP_TCP_StringPut(pHttpCon->socket, HTTP_CRLF);

                // Check if we should output cookies
                if(pHttpCon->hasArgs)
                    pHttpCon->sm = SM_HTTP_SERVE_COOKIES;
                else
                {// Terminate the headers
                    TCPIP_TCP_StringPut(pHttpCon->socket, HTTP_CRLF);
                    pHttpCon->sm = SM_HTTP_SERVE_BODY;
                }

                // Move to next stage
                isDone = false;
                break;

            case SM_HTTP_SERVE_COOKIES:

#if defined(HTTP_USE_COOKIES)
                // If the TX FIFO runs out of space, the client will never get CRLFCRLF
                // Avoid writing huge cookies - keep it under a hundred bytes max

                // Write cookies one at a time as space permits
                for(pHttpCon->ptrRead = pHttpCon->data; pHttpCon->hasArgs != 0u; pHttpCon->hasArgs--)
                {
                    // Write the header
                    TCPIP_TCP_StringPut(pHttpCon->socket, (const uint8_t*)"Set-Cookie: ");

                    // Write the name, URL encoded, one character at a time
                    while((c = *(pHttpCon->ptrRead++)))
                    {
                        if(c == ' ')
                            TCPIP_TCP_Put(pHttpCon->socket, '+');
                        else if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
                        {
                            TCPIP_TCP_Put(pHttpCon->socket, '%');
                            TCPIP_TCP_Put(pHttpCon->socket, btohexa_high(c));
                            TCPIP_TCP_Put(pHttpCon->socket, btohexa_low(c));
                        }
                        else
                            TCPIP_TCP_Put(pHttpCon->socket, c);
                    }

                    TCPIP_TCP_Put(pHttpCon->socket, '=');

                    // Write the value, URL encoded, one character at a time
                    while((c = *(pHttpCon->ptrRead++)))
                    {
                        if(c == ' ')
                            TCPIP_TCP_Put(pHttpCon->socket, '+');
                        else if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
                        {
                            TCPIP_TCP_Put(pHttpCon->socket, '%');
                            TCPIP_TCP_Put(pHttpCon->socket, btohexa_high(c));
                            TCPIP_TCP_Put(pHttpCon->socket, btohexa_low(c));
                        }
                        else
                            TCPIP_TCP_Put(pHttpCon->socket, c);
                    }

                    // Finish the line
                    TCPIP_TCP_StringPut(pHttpCon->socket, HTTP_CRLF);

                }
#endif

                // We're done, move to next state
                TCPIP_TCP_StringPut(pHttpCon->socket, HTTP_CRLF);
                pHttpCon->sm = SM_HTTP_SERVE_BODY;

            case SM_HTTP_SERVE_BODY:

                isDone = false;

                // Try to send next packet
                if(pHttpCon->TxFile.fileTxDone) //if(TCPIP_HTTP_FileSend())
                {// If EOF, then we're done so close and disconnect
                    //SYS_FS_close(pHttpCon->file);
                    //pHttpCon->file = -1;
                    pHttpCon->sm = SM_HTTP_DISCONNECT;
                    isDone = true;
                }
                else
                {
                    TCPIP_HTTP_FileSend(pHttpCon);
                }

                // If the TX FIFO is full, then return to main app loop
                if(TCPIP_TCP_PutIsReady(pHttpCon->socket) == 0u)
                {
                    isDone = true;
                }
                break;

            case SM_HTTP_DISCONNECT:
                // Make sure any opened files are closed
                if(pHttpCon->file != -1)
                {
#if defined (HARMONY_FS)
                    SYS_FS_FileClose(pHttpCon->file);
#else
                    SYS_FS_close(pHttpCon->file);
#endif
                    pHttpCon->file = -1;
                }

                if(TCPIP_TCP_Disconnect(pHttpCon->socket))
                {
                    pHttpCon->sm = SM_HTTP_IDLE;
                }
                // else retry next time
                break;
        }
    } while(!isDone);

}

/*****************************************************************************
  Function:
	static void IsDynamicWebPage(HTTP_CONN* pHttpCon)

  Description:
	Identify if currrent requested web page is dynamic(containing dynamic
        variable) or not. This is judged by if the file name hash is within the
        FileRcrd.bin or not, because all web pages, which has dynamic variable,
        will be recored in to the FileRcrd.bin.

  Precondition:
        None

  Parameters:
	pHttpCon

  Returns:
  	true - dynamic page;
        false - static page;
  ***************************************************************************/
static bool TCPIP_HTTP_WebPageIsDynamic(HTTP_CONN* pHttpCon)
{
#if defined (HARMONY_FS)
    SYS_FS_HANDLE fp = -1;
#else
    FILE_HANDLE fp = -1;
#endif
    uint16_t nameHash = 0;
    uint32_t numFile = 0;
    bool ret = false;

#if defined (HARMONY_FS)
    fp = SYS_FS_FileOpen_Wrapper("FileRcrd.bin", SYS_FS_FILE_OPEN_READ);
    if (fp == SYS_FS_HANDLE_INVALID)
	return false;
    SYS_FS_FileRead(&numFile, 4, fp); //Reading Number of files in record
#else
    fp = SYS_FS_open("FileRcrd.bin", 0);
    if (fp == RETURN_FAILED) return false;

    SYS_FS_read(fp, &numFile, 4); //Reading Number of files in record
#endif
    while(numFile)
    {
#if defined (HARMONY_FS)
        SYS_FS_FileRead(&nameHash, 2, fp); //Reading HashName record
#else
        SYS_FS_read(fp, &nameHash, 2); //Reading HashName record
#endif
        if(pHttpCon->nameHash == nameHash) 
        {
            ret = true;
            break;
        }
        else //Seek to next name hash position
        {
#if defined (HARMONY_FS)
            SYS_FS_FileSeek(fp, 8, SYS_FS_SEEK_CUR);
#else
            SYS_FS_lseek(fp, 8, SEEK_CUR);
#endif
        }
        numFile-=1;
    }
    // Close file
    if (fp != -1) {
#if defined (HARMONY_FS)
        SYS_FS_FileClose(fp);
#else
        SYS_FS_close(fp);
#endif
    }

    return ret;
}

/*****************************************************************************
  Function:
	static bool TCPIP_HTTP_FileSend(HTTP_CONN* pHttpCon)

  Description:
	Serves up the next chunk of curHTTP's file, up to:
  a) the available TX FIFO space or
  b) the next callback index, whichever comes first.

  Precondition:
	pHttpCon->file has been opened for reading.

  Parameters:
	None

  Return Values:
	true - the end of the file was reached and reading is done
	false - more data remains to be read
  ***************************************************************************/

static bool TCPIP_HTTP_FileSend(HTTP_CONN* pHttpCon)
{
    uint32_t availbleTcpBuffSize,len;
    uint32_t cntr=0;
    //uint32_t dynVarCallBackID;
    uint32_t UInt32DataFromBinFile;
    uint16_t nameHashRcrd;
    uint32_t recrdcntr=0;
    uint8_t sendDataBuffer[64];
#if defined (HARMONY_FS)
    SYS_FS_HANDLE FileRcrdPtr=-1, DynVarFilePtr = -1;
#else
    FILE_HANDLE FileRcrdPtr=-1, DynVarFilePtr = -1;
#endif

    switch(pHttpCon->file_sm)
    {
        case SM_IDLE:

#if defined (HARMONY_FS)
            pHttpCon->TxFile.numBytes = SYS_FS_FileSize(pHttpCon->file);
#else
            pHttpCon->TxFile.numBytes = SYS_FS_fsize(pHttpCon->file); 
#endif
            if ((pHttpCon->TxFile.numBytes == -1) || (pHttpCon->TxFile.numBytes == 0)) {
                pHttpCon->TxFile.fileTxDone = 1;
                return true;
            }
            pHttpCon->TxFile.bytesReadCount=0;

        case SM_GET_NO_OF_FILES:
#if defined (HARMONY_FS)
            FileRcrdPtr = SYS_FS_FileOpen_Wrapper("FileRcrd.bin", SYS_FS_FILE_OPEN_READ);
            cntr=SYS_FS_FileRead(&recrdcntr, 4,FileRcrdPtr); //Reading Number of files in record
#else
            FileRcrdPtr = SYS_FS_open("FileRcrd.bin", 0); 
            cntr=SYS_FS_read(FileRcrdPtr, &recrdcntr, 4); //Reading Number of files in record
#endif		
            _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);

            //Continue to next state
            pHttpCon->file_sm = SM_GET_HASH_RCRD;

        case SM_GET_HASH_RCRD:

            while(recrdcntr)
            {
#if defined (HARMONY_FS)
                cntr=SYS_FS_FileRead(&nameHashRcrd, 2, FileRcrdPtr); //Reading HashName record
                _HTTP_FileRdCheck(cntr==2, __FILE__, __LINE__);
                if(pHttpCon->nameHash == nameHashRcrd) // Check if namHash calculation contains dir delimiter '/'
                {
                    pHttpCon->TxFile.nameHashMatched = true;
                    cntr=SYS_FS_FileRead(&UInt32DataFromBinFile, 4, FileRcrdPtr);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    pHttpCon->TxFile.DynRcrdRdCount = UInt32DataFromBinFile;
                    cntr=SYS_FS_FileRead(&pHttpCon->TxFile.dynVarCntr, 4, FileRcrdPtr);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    break;
                }
                else //Dummy Read..to hop to next hash name or HOP by "FileSeek" in file handle
                {
                    cntr=SYS_FS_FileRead(&UInt32DataFromBinFile,4, FileRcrdPtr);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    cntr=SYS_FS_FileRead(&UInt32DataFromBinFile,4, FileRcrdPtr);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                }
                recrdcntr-=1;
            }
            if(FileRcrdPtr != -1) {
                SYS_FS_FileClose(FileRcrdPtr);
                FileRcrdPtr = -1;
            }
#else
                cntr=SYS_FS_read(FileRcrdPtr, &nameHashRcrd, 2); //Reading HashName record
                _HTTP_FileRdCheck(cntr==2, __FILE__, __LINE__);

                if(pHttpCon->nameHash == nameHashRcrd) // Check if namHash calculation contains dir delimiter '/'
                {
                    pHttpCon->TxFile.nameHashMatched = true;

                    //Reading OFFSET of dynvar records in dynvarrcrd.bin
                    cntr=SYS_FS_read(FileRcrdPtr, &UInt32DataFromBinFile, 4);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    pHttpCon->TxFile.DynRcrdRdCount = UInt32DataFromBinFile;

                    //Reading Number dynamic variables in the file
                    cntr=SYS_FS_read(FileRcrdPtr, &pHttpCon->TxFile.dynVarCntr, 4);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    break;
                }
                else //Dummy Read..to hop to next hash name or HOP by "FileSeek" in file handle
                {
                    cntr=SYS_FS_read(FileRcrdPtr, &UInt32DataFromBinFile,4);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                    cntr=SYS_FS_read(FileRcrdPtr, &UInt32DataFromBinFile,4);
                    _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
                }
                recrdcntr-=1;
            }

            if(FileRcrdPtr != -1) {
                SYS_FS_close(FileRcrdPtr);
                FileRcrdPtr = -1;
            }
#endif

            if(pHttpCon->TxFile.nameHashMatched == true)
            {
                //Continue to next state
                pHttpCon->file_sm = SM_GET_DYN_VAR_FILE_RCRD;
            }

            //If NO HashName record matched means the requrested webpage do not have dynamic variables
            if(recrdcntr == 0 && pHttpCon->TxFile.nameHashMatched !=true )
            {
                pHttpCon->file_sm=SM_SERVE_TEXT_DATA ;
                pHttpCon->TxFile.EndOfCallBackFileFlag = true; // No variable, so default the flag to 1

                break;
            }

        case SM_GET_DYN_VAR_FILE_RCRD:
            // Open DynRcrd.bin if not opened
#if defined (HARMONY_FS)
            DynVarFilePtr=SYS_FS_FileOpen_Wrapper("DynRcrd.bin", SYS_FS_FILE_OPEN_READ);
            if (DynVarFilePtr == SYS_FS_HANDLE_INVALID)
                return false;
            if(pHttpCon->TxFile.lock_dynrcd == 0)
            {
                SYS_FS_FileSeek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount+6, SYS_FS_SEEK_SET);
                pHttpCon->TxFile.lock_dynrcd = 1;
            } else {
                SYS_FS_FileSeek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount, SYS_FS_SEEK_SET);
            }
            cntr=SYS_FS_FileRead(&pHttpCon->TxFile.dynVarRcrdOffset, 4, DynVarFilePtr);//Reading dynamic variable offset in webpage
            _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
            cntr=SYS_FS_FileRead(&pHttpCon->TxFile.dynVarCallBackID, 4, DynVarFilePtr);//Reading dynamic variable call back ID
            _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
#else
            DynVarFilePtr=SYS_FS_open("DynRcrd.bin", 0);
           if(DynVarFilePtr == RETURN_FAILED)
                return false;
            if(pHttpCon->TxFile.lock_dynrcd == 0)
            {
                SYS_FS_lseek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount+6, SEEK_SET);
                pHttpCon->TxFile.lock_dynrcd = 1;
            } else {
                SYS_FS_lseek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount, SEEK_SET);
            }

            cntr=SYS_FS_read(DynVarFilePtr, &pHttpCon->TxFile.dynVarRcrdOffset, 4);//Reading dynamic variable offset in webpage
            _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
            cntr=SYS_FS_read(DynVarFilePtr, &pHttpCon->TxFile.dynVarCallBackID, 4);//Reading dynamic variable call back ID
            _HTTP_FileRdCheck(cntr==4, __FILE__, __LINE__);
#endif
            
            //Continue to next state
            pHttpCon->file_sm =SM_PARSE_TILL_DYN_VAR;

        case SM_PARSE_TILL_DYN_VAR:
            // Check if it is re-entering service
#if defined (HARMONY_FS)
            if (DynVarFilePtr == -1) {
                DynVarFilePtr=SYS_FS_FileOpen_Wrapper("DynRcrd.bin", SYS_FS_FILE_OPEN_READ);
		SYS_FS_FileSeek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount, SYS_FS_SEEK_SET);				
            }
            if( pHttpCon->TxFile.dynVarRcrdOffset== 0x00)
            {
                pHttpCon->file_sm = SM_PARSE_DYN_VAR_STRING;
            }
            else
            {                
                availbleTcpBuffSize = TCPIP_TCP_PutIsReady(pHttpCon->socket);
                if(availbleTcpBuffSize >= 64)
                {
                    if((pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount) >= 64)
                    {
                        len = SYS_FS_FileRead(sendDataBuffer, 64, pHttpCon->file);
                        _HTTP_FileRdCheck(len==64, __FILE__, __LINE__);
                        TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, 64);
                        pHttpCon->TxFile.numBytes -=64;
                        pHttpCon->TxFile.bytesReadCount+=64;
                    }
                    else
                    {
                        cntr = pHttpCon->TxFile.dynVarRcrdOffset - pHttpCon->TxFile.bytesReadCount;
                        len = SYS_FS_FileRead(sendDataBuffer, cntr, pHttpCon->file);
                        _HTTP_FileRdCheck((len==cntr), __FILE__, __LINE__);
                        TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, cntr);
                        pHttpCon->TxFile.numBytes -=cntr;
                        pHttpCon->TxFile.bytesReadCount+=cntr;
                    }
                }
                else if(availbleTcpBuffSize != 0)
                {
                    if(pHttpCon->TxFile.bytesReadCount != pHttpCon->TxFile.dynVarRcrdOffset )
                    {
                        if((pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount) >= availbleTcpBuffSize)
                        {
                            len = SYS_FS_FileRead(sendDataBuffer, availbleTcpBuffSize, pHttpCon->file);
                            _HTTP_FileRdCheck(len==availbleTcpBuffSize, __FILE__, __LINE__);
                            TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, availbleTcpBuffSize);
                            pHttpCon->TxFile.numBytes -=availbleTcpBuffSize;
                            pHttpCon->TxFile.bytesReadCount+=availbleTcpBuffSize;
                        }
                        else
                        {
                            cntr = pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount;
                            len = SYS_FS_FileRead(sendDataBuffer, cntr, pHttpCon->file);
                            _HTTP_FileRdCheck((len==cntr), __FILE__, __LINE__);
                            TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, cntr);
                            pHttpCon->TxFile.numBytes -=cntr;
                            pHttpCon->TxFile.bytesReadCount+=cntr;
                        }
                    }
                }
            }
            pHttpCon->TxFile.DynRcrdRdCount = SYS_FS_FileTell(DynVarFilePtr);
            if(pHttpCon->TxFile.dynVarRcrdOffset == pHttpCon->TxFile.bytesReadCount)
            {
                pHttpCon->file_sm = SM_PARSE_DYN_VAR_STRING;
            }
            SYS_FS_FileClose(DynVarFilePtr);
#else
            if (DynVarFilePtr == -1) {
                DynVarFilePtr=SYS_FS_open("DynRcrd.bin", 0);
                SYS_FS_lseek(DynVarFilePtr, pHttpCon->TxFile.DynRcrdRdCount, SEEK_SET);
            }
            //If the dynamic variable starts at the begining of any file, Parse the dynamic var string
            if( pHttpCon->TxFile.dynVarRcrdOffset== 0x00)
            {
                pHttpCon->file_sm = SM_PARSE_DYN_VAR_STRING;
            }
            else
            {                
                // Determine and keep parsing data depending on the number of bytes available in the TCP transmit buffer
                availbleTcpBuffSize = TCPIP_TCP_PutIsReady(pHttpCon->socket);

                if(availbleTcpBuffSize >= 64)
                {
                    if((pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount) >= 64)
                    {
                        len = SYS_FS_read(pHttpCon->file, sendDataBuffer, 64);
                        _HTTP_FileRdCheck(len==64, __FILE__, __LINE__);
                        TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, 64);
                        pHttpCon->TxFile.numBytes -=64;
                        pHttpCon->TxFile.bytesReadCount+=64;
                    }
                    else
                    {
                        cntr = pHttpCon->TxFile.dynVarRcrdOffset - pHttpCon->TxFile.bytesReadCount;
                        len = SYS_FS_read(pHttpCon->file, sendDataBuffer, cntr);//len=FSfread(sendDataBuffer, (dynVarRcrdOffset-bytesReadCount), 1, pHttpCon->file);
                        _HTTP_FileRdCheck((len==cntr), __FILE__, __LINE__);
                        TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, cntr);
                        pHttpCon->TxFile.numBytes -=cntr;
                        pHttpCon->TxFile.bytesReadCount+=cntr;
                    }
                }
                else if(availbleTcpBuffSize != 0)
                {
                    if(pHttpCon->TxFile.bytesReadCount != pHttpCon->TxFile.dynVarRcrdOffset )
                    {
                        if((pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount) >= availbleTcpBuffSize)
                        {
                            len = SYS_FS_read(pHttpCon->file, sendDataBuffer, availbleTcpBuffSize);
                            _HTTP_FileRdCheck(len==availbleTcpBuffSize, __FILE__, __LINE__);
                            TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, availbleTcpBuffSize);
                            pHttpCon->TxFile.numBytes -=availbleTcpBuffSize;
                            pHttpCon->TxFile.bytesReadCount+=availbleTcpBuffSize;
                        }
                        else
                        {
                            cntr = pHttpCon->TxFile.dynVarRcrdOffset-pHttpCon->TxFile.bytesReadCount;
                            len = SYS_FS_read(pHttpCon->file, sendDataBuffer, cntr);
                            _HTTP_FileRdCheck((len==cntr), __FILE__, __LINE__);
                            TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, cntr);
                            pHttpCon->TxFile.numBytes -=cntr;
                            pHttpCon->TxFile.bytesReadCount+=cntr;
                        }
                    }
                }
            }
            pHttpCon->TxFile.DynRcrdRdCount = SYS_FS_ftell(DynVarFilePtr);

            if(pHttpCon->TxFile.dynVarRcrdOffset == pHttpCon->TxFile.bytesReadCount)
            {
                //Continue to next state
                pHttpCon->file_sm = SM_PARSE_DYN_VAR_STRING;
            }

            SYS_FS_close(DynVarFilePtr);
#endif
            break;

        case SM_PARSE_DYN_VAR_STRING:
#if defined (HARMONY_FS)
            len = SYS_FS_FileRead(sendDataBuffer, 1, pHttpCon->file);
#else
            len = SYS_FS_read(pHttpCon->file, sendDataBuffer, 1);
#endif
            _HTTP_FileRdCheck(len==1, __FILE__, __LINE__);
            pHttpCon->TxFile.numBytes-=1;
            pHttpCon->TxFile.bytesReadCount+=1;
            if(sendDataBuffer[0]=='~')
            {
                do
                {
#if defined (HARMONY_FS)
                    len = SYS_FS_FileRead(sendDataBuffer, 1, pHttpCon->file);
#else
                    len = SYS_FS_read(pHttpCon->file, sendDataBuffer, 1);
#endif
                    _HTTP_FileRdCheck(len==1, __FILE__, __LINE__);
                    pHttpCon->TxFile.numBytes-=1;
                    pHttpCon->TxFile.bytesReadCount+=1;
                }
                while(sendDataBuffer[0]!='~');
            }

            //Continue to next state to process the dynamic variable callback
            pHttpCon->file_sm =SM_PROCESS_DYN_VAR_CALLBACK;


        case SM_PROCESS_DYN_VAR_CALLBACK:

            pHttpCon->TxFile.EndOfCallBackFileFlag = true;
            HTTPPrint(pHttpCon, pHttpCon->TxFile.dynVarCallBackID);

            if(pHttpCon->TxFile.EndOfCallBackFileFlag == true)
            {
                pHttpCon->TxFile.dynVarCntr-=1;
                pHttpCon->file_sm=SM_GET_DYN_VAR_FILE_RCRD;
                if(pHttpCon->TxFile.dynVarCntr == 0)
                {       
                    if (pHttpCon->TxFile.numBytes != 0)
                    {
                        pHttpCon->file_sm =SM_SERVE_TEXT_DATA;
                    }
                    pHttpCon->TxFile.lock_dynrcd = 0;
                }

            }

            break;

        case SM_SERVE_TEXT_DATA:

            // If HashIndex do not match,that means no entry in the "FilRcrd.bin", means no dynamic variables for this wepage,
            //then proceed to serve the page as normal HTML text

            availbleTcpBuffSize = TCPIP_TCP_PutIsReady(pHttpCon->socket);

            if(availbleTcpBuffSize >= 64)
            {
                if(pHttpCon->TxFile.numBytes >= 64)
                {
#if defined (HARMONY_FS)
                    len = SYS_FS_FileRead(sendDataBuffer, 64, pHttpCon->file);
#else
                    len = SYS_FS_read(pHttpCon->file, sendDataBuffer, 64);
#endif
                    _HTTP_FileRdCheck(len==64, __FILE__, __LINE__);
                    TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, 64);
                    pHttpCon->TxFile.numBytes -=64;
                    pHttpCon->TxFile.bytesReadCount+=64;
                }
                else
                {
#if defined (HARMONY_FS)
                    len = SYS_FS_FileRead(sendDataBuffer, pHttpCon->TxFile.numBytes, pHttpCon->file);
#else
                    len = SYS_FS_read(pHttpCon->file, sendDataBuffer, pHttpCon->TxFile.numBytes);
#endif
                    _HTTP_FileRdCheck(len==pHttpCon->TxFile.numBytes, __FILE__, __LINE__);
                    TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, pHttpCon->TxFile.numBytes);
                    pHttpCon->TxFile.bytesReadCount+=pHttpCon->TxFile.numBytes;
                    pHttpCon->TxFile.numBytes=0;
                }
            }
            else if(availbleTcpBuffSize != 0)
            {
                if(pHttpCon->TxFile.numBytes >= availbleTcpBuffSize)
                {
#if defined (HARMONY_FS)
                    len = SYS_FS_FileRead(sendDataBuffer, availbleTcpBuffSize, pHttpCon->file);
#else
                    len = SYS_FS_read(pHttpCon->file, sendDataBuffer, availbleTcpBuffSize);
#endif
                    _HTTP_FileRdCheck(len==availbleTcpBuffSize, __FILE__, __LINE__);
                    TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, availbleTcpBuffSize);
                    pHttpCon->TxFile.numBytes -=availbleTcpBuffSize;
                    pHttpCon->TxFile.bytesReadCount+=availbleTcpBuffSize;
                }
                else
                {
#if defined (HARMONY_FS)
                    len = SYS_FS_FileRead(sendDataBuffer, pHttpCon->TxFile.numBytes, pHttpCon->file);
#else
                    len = SYS_FS_read(pHttpCon->file, sendDataBuffer, pHttpCon->TxFile.numBytes);
#endif
                    _HTTP_FileRdCheck(len==pHttpCon->TxFile.numBytes, __FILE__, __LINE__);
                    TCPIP_TCP_ArrayPut(pHttpCon->socket, sendDataBuffer, pHttpCon->TxFile.numBytes);
                    pHttpCon->TxFile.bytesReadCount+=pHttpCon->TxFile.numBytes;
                    pHttpCon->TxFile.numBytes=0;
                }
            }

            break;

        default:
            return false;
    }

    if((((pHttpCon->TxFile.numBytes == 0)) && (pHttpCon->TxFile.EndOfCallBackFileFlag == true)) \
        || (fileErr==1))    // Exception on file reading
    {
        TCPIP_TCP_Flush(pHttpCon->socket);

        pHttpCon->TxFile.nameHashMatched = false;
        pHttpCon->TxFile.lock_dynrcd = 0;
        pHttpCon->TxFile.dynVarCallBackID = 0;
        pHttpCon->TxFile.DynRcrdRdCount = 0;
        
        pHttpCon->TxFile.bytesReadCount=0;
        pHttpCon->file_sm=SM_IDLE;
        pHttpCon->TxFile.fileTxDone = 1;

        fileErr = 0;
        return true;
    }

    return false;
}

/*****************************************************************************
  Function:
	static void HTTPHeaderParseLookup(HTTP_CONN* pHttpCon, int i)

  Description:
	Calls the appropriate header parser based on the index of the header
	that was read from the request.

  Precondition:
	None

  Parameters:
	i - the index of the string found in HTTPRequestHeaders

  Return Values:
	true - the end of the file was reached and reading is done
	false - more data remains to be read
  ***************************************************************************/
static void _HTTP_HeaderParseLookup(HTTP_CONN* pHttpCon, int i)
{
    // i corresponds to an index in HTTPRequestHeaders

#if defined(HTTP_USE_COOKIES)
    if(i == 0u)
    {
        _HTTP_HeaderParseCookie(pHttpCon);
        return;
    }
#endif

#if defined(HTTP_USE_AUTHENTICATION)	
    if(i == 1u)
    {
        _HTTP_HeaderParseAuthorization(pHttpCon);
        return;
    }
#endif

#if defined(HTTP_USE_POST)
    if(i == 2u)
    {
        _HTTP_HeaderParseContentLength(pHttpCon);
        return;
    }
#endif
}

/*****************************************************************************
  Function:
	static void HTTPHeaderParseAuthorization(HTTP_CONN* pHttpCon)

  Summary:
	Parses the "Authorization:" header for a request and verifies the
	credentials.

  Description:
	Parses the "Authorization:" header for a request.  For example, 
	"BASIC YWRtaW46cGFzc3dvcmQ=" is decoded to a user name of "admin" and
	a password of "password".  Once read, HTTPCheckAuth is called from
	CustomHTTPApp.c to determine if the credentials are acceptable.

	The return value of HTTPCheckAuth is saved in pHttpCon->isAuthorized for
	later use by the application.

  Precondition:
	None

  Parameters:
	None

  Returns:
	None

  Remarks:
	This function is ony available when HTTP_USE_AUTHENTICATION is defined.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
static void _HTTP_HeaderParseAuthorization(HTTP_CONN* pHttpCon)
{
    uint16_t len;
    uint8_t buf[40];
    uint8_t *ptrBuf;

    // If auth processing is not required, return
    if(pHttpCon->isAuthorized & 0x80)
        return;

    // Clear the auth type ("BASIC ")
    TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, 6);

    // Find the terminating CRLF and make sure it's a multiple of four
    len = TCPIP_TCP_ArrayFind(pHttpCon->socket, HTTP_CRLF, HTTP_CRLF_LEN, 0, 0, false);
    len += 3;
    len &= 0xfc;
    len = mMIN(len, sizeof(buf)-4);

    // Read in 4 bytes at a time and decode (slower, but saves RAM)
    for(ptrBuf = buf; len > 0u; len-=4, ptrBuf+=3)
    {
        TCPIP_TCP_ArrayGet(pHttpCon->socket, ptrBuf, 4);
        TCPIP_Helper_Base64Decode(ptrBuf, 4, ptrBuf, 3);
    }

    // Null terminate both, and make sure there's at least two terminators
    *ptrBuf = '\0';
    for(len = 0, ptrBuf = buf; len < sizeof(buf); len++, ptrBuf++)
        if(*ptrBuf == ':')
            break;
    *(ptrBuf++) = '\0';

    // Verify credentials
    pHttpCon->isAuthorized = HTTPCheckAuth(pHttpCon, buf, ptrBuf);

    return;
}
#endif

/*****************************************************************************
  Function:
	static void HTTPHeaderParseCookie(HTTP_CONN* pHttpCon)

  Summary:
	Parses the "Cookie:" headers for a request and stores them as GET
	variables.

  Description:
	Parses the "Cookie:" headers for a request.  For example, 
 	"Cookie: name=Wile+E.+Coyote; order=ROCKET_LAUNCHER" is decoded to 
	"name=Wile+E.+Coyote&order=ROCKET_LAUNCHER&" and stored as any other 
	GET variable in pHttpCon->data.

	The user application can easily access these values later using the
	TCPIP_HTTP_ArgGet() and TCPIP_HTTP_ArgGet() functions.

  Precondition:
	None

  Parameters:
	None

  Returns:
	None

  Remarks:
	This function is ony available when HTTP_USE_COOKIES is defined.
  ***************************************************************************/
#if defined(HTTP_USE_COOKIES)
static void _HTTP_HeaderParseCookie(HTTP_CONN* pHttpCon)
{
    uint16_t lenA, lenB;

    // Verify there's enough space
    lenB = TCPIP_TCP_ArrayFind(pHttpCon->socket, HTTP_CRLF, HTTP_CRLF_LEN, 0, 0, false);
    if(lenB >= (uint16_t)(pHttpCon->data + HTTP_MAX_DATA_LEN - pHttpCon->ptrData - 2))
    {// If not, overflow
        pHttpCon->httpStatus = HTTP_OVERFLOW;
        pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
        return;
    }

    // While a CRLF is not immediate, grab a cookie value
    while(lenB != 0u)
    {
        // Look for a ';' and use the shorter of that or a CRLF
        lenA = TCPIP_TCP_Find(pHttpCon->socket, ';', 0, 0, false);

        // Read to the terminator
        pHttpCon->ptrData += TCPIP_TCP_ArrayGet(pHttpCon->socket, pHttpCon->ptrData, mMIN(lenA, lenB));

        // Insert an & to anticipate another cookie
        *(pHttpCon->ptrData++) = '&';

        // If semicolon, trash it and whitespace
        if(lenA < lenB)
        {
            TCPIP_TCP_Get(pHttpCon->socket, NULL);
            while(TCPIP_TCP_Find(pHttpCon->socket, ' ', 0, 0, false) == 0u)
                TCPIP_TCP_Get(pHttpCon->socket, NULL);
        }

        // Find the new distance to the CRLF
        lenB = TCPIP_TCP_ArrayFind(pHttpCon->socket, HTTP_CRLF, HTTP_CRLF_LEN, 0, 0, false);
    }

    return;

}
#endif

/*****************************************************************************
  Function:
	static void HTTPHeaderParseContentLength(HTTP_CONN* pHttpCon)

  Summary:
	Parses the "Content-Length:" header for a request.

  Description:
	Parses the "Content-Length:" header to determine how many bytes of
	POST data to expect after the request.  This value is stored in 
	pHttpCon->byteCount.

  Precondition:
	None

  Parameters:
	None

  Returns:
	None

  Remarks:
	This function is ony available when HTTP_USE_POST is defined.
  ***************************************************************************/
#if defined(HTTP_USE_POST)
static void _HTTP_HeaderParseContentLength(HTTP_CONN* pHttpCon)
{
    uint16_t len;
    uint8_t buf[10];

    // Read up to the CRLF (max 9 bytes or ~1GB)
    len = TCPIP_TCP_ArrayFind(pHttpCon->socket, HTTP_CRLF, HTTP_CRLF_LEN, 0, 0, false);
    if(len >= sizeof(buf))
    {
        pHttpCon->httpStatus = HTTP_BAD_REQUEST;
        pHttpCon->byteCount = 0;
        return;
    }	
    len = TCPIP_TCP_ArrayGet(pHttpCon->socket, buf, len);
    buf[len] = '\0';

    pHttpCon->byteCount = atol((char*)buf);
}
#endif

/*****************************************************************************
  Function:
	uint8_t* TCPIP_HTTP_URLDecode(uint8_t* cData)

  Summary:
	Parses a string from URL encoding to plain-text.

  Description:
	Parses a string from URL encoding to plain-text.  The following
	conversions are made: ??to ?0? ??to ?0? ??to ?? and
	?xx?to a single hex byte.
 
	After completion, the data has been decoded and a null terminator
	signifies the end of a name or value.  A second null terminator (or a
	null name parameter) indicates the end of all the data.

  Precondition:
	The data parameter is null terminated and has at least one extra
	byte free.

  Parameters:
	cData - The string which is to be decoded in place.

  Returns:
	A pointer to the last null terminator in data, which is also the
	first free byte for new data.

  Remarks:
	This function is called by the stack to parse GET arguments and 
	cookie data.  User applications can use this function to decode POST
	data, but first need to verify that the string is null-terminated.
  ***************************************************************************/
uint8_t* TCPIP_HTTP_URLDecode(uint8_t* cData)
{
    uint8_t *pRead, *pWrite;
    uint16_t wLen;
    uint8_t c;
    uint16_t hex;

    // Determine length of input
    wLen = strlen((char*)cData);

    // Read all characters in the string
    for(pRead = pWrite = cData; wLen != 0u; )
    {
        c = *pRead++;
        wLen--;

        if(c == '=' || c == '&')
            *pWrite++ = '\0';
        else if(c == '+')
            *pWrite++ = ' ';
        else if(c == '%')
        {
            if(wLen < 2u)
                wLen = 0;
            else
            {
                ((uint8_t*)&hex)[1] = *pRead++;
                ((uint8_t*)&hex)[0] = *pRead++;
                wLen--;
                wLen--;
                *pWrite++ = hexatob(hex);
            }
        }
        else
            *pWrite++ = c;
    }

    // Double null terminate the last value
    *pWrite++ = '\0';
    *pWrite = '\0';

    return pWrite;
}

/*****************************************************************************
  Function:
	const uint8_t* TCPIP_HTTP_ArgGet(const uint8_t* cData, const uint8_t* cArg)

  Summary:
	Locates a form field value in a given data array.

  Description:
	Searches through a data array to find the value associated with a
	given argument.  It can be used to find form field values in data
	received over GET or POST.
	
	The end of data is assumed to be reached when a null name parameter is
	encountered.  This requires the string to have an even number of 
	null-terminated strings, followed by an additional null terminator.

  Precondition:
	The data array has a valid series of null terminated name/value pairs.

  Parameters:
	data - the buffer to search
	arg - the name of the argument to find

  Returns:
	A pointer to the argument value, or NULL if not found.
  ***************************************************************************/
const uint8_t* TCPIP_HTTP_ArgGet(const uint8_t* cData, const uint8_t* cArg)
{
    // Search through the array while bytes remain
    while(*cData != '\0')
    { 
        // Look for arg at current position
        if(!strcmp((const char*)cArg, (const char*)cData))
        {// Found it, so return parameter
            return cData + strlen((const char*)cArg) + 1;
        }

        // Skip past two strings (NUL bytes)
        cData += strlen((const char*)cData) + 1;
        cData += strlen((const char*)cData) + 1;
    }

    // Return NULL if not found
    return NULL;
}


/*****************************************************************************
  Function:
	HTTP_READ_STATUS TCPIP_HTTP_PostNameRead(uint8_t* cData, uint16_t wLen)

  Summary:
	Reads a name from a URL encoded string in the TCP buffer.

  Description:
	Reads a name from a URL encoded string in the TCP buffer.  This function
	is meant to be called from an HTTPExecutePost callback to facilitate
	easier parsing of incoming data.  This function also prevents buffer
	overflows by forcing the programmer to indicate how many bytes are
	expected.  At least 2 extra bytes are needed in cData over the maximum
	length of data expected to be read.
	
	This function will read until the next '=' character, which indicates the
	end of a name parameter.  It assumes that the front of the buffer is
	the beginning of the name paramter to be read.
	
	This function properly updates pHttpCon->byteCount by decrementing it
	by the number of bytes read.  It also removes the delimiting '=' from
	the buffer.

  Precondition:
	Front of TCP buffer is the beginning of a name parameter, and the rest of
	the TCP buffer contains a URL-encoded string with a name parameter 
	terminated by a '=' character.

  Parameters:
	cData - where to store the name once it is read
	wLen - how many bytes can be written to cData

  Return Values:
	HTTP_READ_OK - name was successfully read
	HTTP_READ_TRUNCTATED - entire name could not fit in the buffer, so the
							value was truncated and data has been lost
	HTTP_READ_INCOMPLETE - entire name was not yet in the buffer, so call
							this function again later to retrieve
  ***************************************************************************/
#if defined(HTTP_USE_POST)
HTTP_READ_STATUS TCPIP_HTTP_PostNameRead(HTTP_CONN_HANDLE connHandle, uint8_t* cData, uint16_t wLen)
{
    HTTP_READ_STATUS status;
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;

    status = _HTTP_ReadTo(pHttpCon, '=', cData, wLen);

    // Decode the data (if not reading to null or blank) and return
    if(cData && *cData)
    {
        TCPIP_HTTP_URLDecode(cData);
    }
    return status;
}	
#endif

/*****************************************************************************
  Function:
	HTTP_READ_STATUS TCPIP_HTTP_PostValueRead(uint8_t* cData, uint16_t wLen)

  Summary:
	Reads a value from a URL encoded string in the TCP buffer.

  Description:
	Reads a value from a URL encoded string in the TCP buffer.  This function
	is meant to be called from an HTTPExecutePost callback to facilitate
	easier parsing of incoming data.  This function also prevents buffer
	overflows by forcing the programmer to indicate how many bytes are
	expected.  At least 2 extra bytes are needed in cData above the maximum
	length of data expected to be read.
	
	This function will read until the next '&' character, which indicates the
	end of a value parameter.  It assumes that the front of the buffer is
	the beginning of the value paramter to be read.  If pHttpCon->byteCount
	indicates that all expected bytes are in the buffer, it assumes that 
	all remaining data is the value and acts accordingly.
	
	This function properly updates pHttpCon->byteCount by decrementing it
	by the number of bytes read.  The terminating '&' character is also 
	removed from the buffer.
	
  Precondition:
	Front of TCP buffer is the beginning of a name parameter, and the rest of
	the TCP buffer contains a URL-encoded string with a name parameter 
	terminated by a '=' character.

  Parameters:
	cData - where to store the value once it is read
	wLen - how many bytes can be written to cData

  Return Values:
	HTTP_READ_OK - value was successfully read
	HTTP_READ_TRUNCTATED - entire value could not fit in the buffer, so the
							value was truncated and data has been lost
	HTTP_READ_INCOMPLETE - entire value was not yet in the buffer, so call
							this function again later to retrieve
  ***************************************************************************/
#if defined(HTTP_USE_POST)
HTTP_READ_STATUS TCPIP_HTTP_PostValueRead(HTTP_CONN_HANDLE connHandle, uint8_t* cData, uint16_t wLen)
{
    HTTP_READ_STATUS status;
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;

    // Try to read the value
    status = _HTTP_ReadTo(pHttpCon, '&', cData, wLen);

    // If read was incomplete, check if we're at the end
    if(status == HTTP_READ_INCOMPLETE)
    {
        // If all data has arrived, read all remaining data
        if(pHttpCon->byteCount == TCPIP_TCP_GetIsReady(pHttpCon->socket))
            status = _HTTP_ReadTo(pHttpCon, '\0', cData, wLen);
    }

    // Decode the data (if not reading to null or blank) and return
    if(cData && *cData)
        TCPIP_HTTP_URLDecode(cData);
    return status;
}	
#endif

/*****************************************************************************
  Function:
	static HTTP_READ_STATUS HTTPReadTo(HTTP_CONN* pHttpCon, uint8_t cDelim, uint8_t* cData, uint16_t wLen)

  Summary:
	Reads to a buffer until a specified delimiter character.

  Description:
	Reads from the TCP buffer to cData until either cDelim is reached, or
	until wLen - 2 bytes have been read.  The value read is saved to cData and 
	null terminated.  (wLen - 2 is used so that the value can be passed to
	TCPIP_HTTP_URLDecode later, which requires a null terminator plus one extra free
	byte.)
	
	The delimiter character is removed from the buffer, but not saved to 
	cData. If all data cannot fit into cData, it will still be removed from 
	the buffer but will not be saved anywhere.

	This function properly updates pHttpCon->byteCount by decrementing it
	by the number of bytes read. 

  Precondition:
	None

  Parameters:
  	cDelim - the character at which to stop reading, or NULL to read to
  			 the end of the buffer
	cData - where to store the data being read
	wLen - how many bytes can be written to cData

  Return Values:
	HTTP_READ_OK - data was successfully read
	HTTP_READ_TRUNCTATED - entire data could not fit in the buffer, so the
							data was truncated and data has been lost
	HTTP_READ_INCOMPLETE - delimiter character was not found
  ***************************************************************************/
#if defined(HTTP_USE_POST)
static HTTP_READ_STATUS _HTTP_ReadTo(HTTP_CONN* pHttpCon, uint8_t cDelim, uint8_t* cData, uint16_t wLen)
{
    HTTP_READ_STATUS status;
    uint16_t wPos;

    // Either look for delimiter, or read all available data
    if(cDelim)
        wPos = TCPIP_TCP_Find(pHttpCon->socket, cDelim, 0, 0, false);
    else
        wPos = TCPIP_TCP_GetIsReady(pHttpCon->socket);

    // If not found, return incomplete
    if(wPos == 0xffff)
        return HTTP_READ_INCOMPLETE;

    // Read the value
    if(wLen < 2u && cData != NULL)
    {// Buffer is too small, so read to NULL instead
        pHttpCon->byteCount -= TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, wPos);
        status = HTTP_READ_TRUNCATED;
    }
    else if(cData == NULL)
    {// Just remove the data
        pHttpCon->byteCount -= TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, wPos);
        status = HTTP_READ_OK;
    }
    else if(wPos > wLen - 2)
    {// Read data, but truncate at max length
        pHttpCon->byteCount -= TCPIP_TCP_ArrayGet(pHttpCon->socket, cData, wLen - 2);
        pHttpCon->byteCount -= TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, wPos - (wLen - 2));
        cData[wLen - 2] = '\0';
        status = HTTP_READ_TRUNCATED;
    }
    else
    {// Read the data normally
        pHttpCon->byteCount -= TCPIP_TCP_ArrayGet(pHttpCon->socket, cData, wPos);
        cData[wPos] = '\0';
        status = HTTP_READ_OK;
    }

    // Remove the delimiter
    if(cDelim)
        pHttpCon->byteCount -= TCPIP_TCP_Get(pHttpCon->socket, NULL);

    return status;
}	
#endif

/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPMPFSUpload(HTTP_CONN* pHttpCon)

  Summary:
	Saves a file uploaded via POST as the new MPFS image in EEPROM or 
	external Flash.

  Description:
	Allows the MPFS image in EEPROM or external Flash to be updated via a 
	web page by accepting a file upload and storing it to the external memory.

  Precondition:
	None

  Parameters:
	None

  Return Values:
	HTTP_IO_DONE - on success
	HTTP_IO_NEED_DATA - if more data is still expected

  Remarks:
	This function is only available when MPFS uploads are enabled and
	the MPFS image is stored in EEPROM.

  Internal:
	After the headers, the first line from the form will be the MIME
	separator.  Following that is more headers about the file, which
	are discarded.  After another CRLFCRLF pair the file data begins,
	which is read 16 bytes at a time and written to external memory.
  ***************************************************************************/
#if defined(HTTP_FILE_UPLOAD)
#if defined (HARMONY_FS)
static HTTP_IO_RESULT _HTTP_MPFSUpload(HTTP_CONN* pHttpCon)
{
    uint8_t c[16];
    uint16_t lenA, lenB;

    switch(pHttpCon->httpStatus)
    {
        // New upload, so look for the CRLFCRLF
        case HTTP_MPFS_UP:

            lenA = TCPIP_TCP_ArrayFind(pHttpCon->socket, (const uint8_t*)"\r\n\r\n", 4, 0, 0, false);

            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, lenA);
                pHttpCon->byteCount -= lenA;

                // Make sure first 6 bytes are also in
                if(TCPIP_TCP_GetIsReady(pHttpCon->socket) < (4u + 6u) )
                {
                    lenA++;
                    return HTTP_IO_NEED_DATA;
                }
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, c, 10);
                pHttpCon->byteCount -= lenA;
                pHttpCon->mediaHndl = (const void *)DRV_NVM_BUFFER_HANDLE_INVALID;
                if(memcmp(c, (const void*)"\r\n\r\nMPFS\x02\x01", 10) == 0)
                {   // Read as Ver 2.1
                    if(_HTTP_SetMediaWriteHeader(pHttpCon, c + 4, 6))
                    {   // success
                        pHttpCon->httpStatus = HTTP_MPFS_OK;
                        return HTTP_IO_WAITING;
                    }
                }
                _HTTP_ReleaseMedia(pHttpCon);
                pHttpCon->httpStatus = HTTP_MPFS_ERROR;
                return HTTP_IO_WAITING;
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, TCPIP_TCP_GetIsReady(pHttpCon->socket) - 4);
                pHttpCon->byteCount -= lenA;
            }
            break;
        case HTTP_MPFS_ERROR:
            pHttpCon->byteCount -= TCPIP_TCP_GetIsReady(pHttpCon->socket);
            TCPIP_TCP_Discard(pHttpCon->socket);
            if(pHttpCon->byteCount < 100u || pHttpCon->byteCount > 0x80000000u)
            {// If almost all data was read, or if we overflowed, then return
                pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                return HTTP_IO_DONE;
            }
            break;
        case HTTP_MPFS_OK:
            lenA = TCPIP_TCP_GetIsReady(pHttpCon->socket);
            if(lenA > pHttpCon->byteCount)
                lenA = pHttpCon->byteCount;
            while(lenA > 0u)
            {
                lenB = TCPIP_TCP_ArrayGet(pHttpCon->socket, c, mMIN(lenA,16u));
                pHttpCon->byteCount -= lenB;
                lenA -= lenB;
                SYS_FS_FileWrite(c, lenB,(SYS_FS_HANDLE)&pHttpCon->mediaHndl);
            }
            if(pHttpCon->byteCount == 0u)
            {
                SYS_FS_FileClose((SYS_FS_HANDLE)&pHttpCon->mediaHndl);
                _HTTP_ReleaseMedia(pHttpCon);
                pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                return HTTP_IO_DONE;
            }
        default:
            break;
    }
    return HTTP_IO_NEED_DATA;
}//_HTTP_MPFSUpload
static bool _HTTP_SetMediaWriteHeader(HTTP_CONN* pHttpCon, const uint8_t* buffer, unsigned int nBytes)
{
    DRV_IO_INTENT ioIntent;
    SYS_FS_Unmount_Wrapper((const char *)&pHttpCon->data[1]);
    ioIntent = DRV_IO_INTENT_WRITE | DRV_IO_INTENT_BLOCKING | DRV_IO_INTENT_EXCLUSIVE;
    pHttpCon->mediaHndl = (const void *) DRV_NVM_Open(DRV_NVM_INDEX_0, ioIntent);
    if(pHttpCon->mediaHndl != (const void *)DRV_NVM_BUFFER_HANDLE_INVALID)
    {   // success
        if(DRV_NVM_Write((DRV_HANDLE)pHttpCon->mediaHndl, 0, (uint8_t*) buffer, nBytes) != DRV_NVM_BUFFER_HANDLE_INVALID)
        {   // success
            return true;
        }
    }
    return false;
}//_HTTP_SetMediaWriteHeader
static void _HTTP_ReleaseMedia(HTTP_CONN* pHttpCon)
{
    if(pHttpCon->mediaHndl != (const void *)DRV_NVM_BUFFER_HANDLE_INVALID)
    {
        pHttpCon->mediaHndl = (const void *)DRV_NVM_BUFFER_HANDLE_INVALID;
    }
    const int dumy=0;
    SYS_FS_Mount("/dev/nvma1", "/mnt/myDrive1", MPFS2, 0, NULL);
}//_HTTP_ReleaseMedia

#else

static HTTP_IO_RESULT _HTTP_MPFSUpload(HTTP_CONN* pHttpCon)
{
    uint8_t c[16];
    uint16_t lenA, lenB;
    switch(pHttpCon->httpStatus)
    {
        case HTTP_MPFS_UP:
            lenA = TCPIP_TCP_ArrayFind(pHttpCon->socket, (const uint8_t*)"\r\n\r\n", 4, 0, 0, false);
            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, lenA);
                pHttpCon->byteCount -= lenA;
                if(TCPIP_TCP_GetIsReady(pHttpCon->socket) < (4u + 6u) )
                {
                    lenA++;
                    return HTTP_IO_NEED_DATA;
                }

                // Make sure it's an MPFS of the correct version
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, c, 10);
                pHttpCon->byteCount -= lenA;
                pHttpCon->mediaHndl = DRV_MEDIA_HANDLE_INVALID;

                if(memcmp(c, (const void*)"\r\n\r\nMPFS\x02\x01", 10) == 0)
                {   // Read as Ver 2.1
                    // Format the Media storage and put 6 byte tag
                    if(_HTTP_SetMediaWriteHeader(pHttpCon, c + 4, 6))
                    {   // success
                        pHttpCon->httpStatus = HTTP_MPFS_OK;
                        return HTTP_IO_WAITING;
                    }
                }

                // Version is wrong or media error
                _HTTP_ReleaseMedia(pHttpCon);
                pHttpCon->httpStatus = HTTP_MPFS_ERROR;
                return HTTP_IO_WAITING;
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPIP_TCP_ArrayGet(pHttpCon->socket, NULL, TCPIP_TCP_GetIsReady(pHttpCon->socket) - 4);
                pHttpCon->byteCount -= lenA;
            }

            break;

            // Received file is invalid
        case HTTP_MPFS_ERROR:
            pHttpCon->byteCount -= TCPIP_TCP_GetIsReady(pHttpCon->socket);
            TCPIP_TCP_Discard(pHttpCon->socket);
            if(pHttpCon->byteCount < 100u || pHttpCon->byteCount > 0x80000000u)
            {// If almost all data was read, or if we overflowed, then return
                pHttpCon->sm = SM_HTTP_SERVE_HEADERS;
                return HTTP_IO_DONE;
            }
            break;

            // File is verified, so write the data
        case HTTP_MPFS_OK:
            // Determine how much to read
            lenA = TCPIP_TCP_GetIsReady(pHttpCon->socket);
            if(lenA > pHttpCon->byteCount)
                lenA = pHttpCon->byteCount;

            while(lenA > 0u)
            {
                lenB = TCPIP_TCP_ArrayGet(pHttpCon->socket, c, mMIN(lenA,16u));
                pHttpCon->byteCount -= lenB;
                lenA -= lenB;
                DRV_MEDIA_Write(pHttpCon->mediaHndl, c, lenB);
            }

            // If we've read all the data
            if(pHttpCon->byteCount == 0u)
            {
                DRV_MEDIA_WriteFlush(pHttpCon->mediaHndl);
                _HTTP_ReleaseMedia(pHttpCon);
                pHttpCon->sm = SM_HTTP_SERVE_HEADERS;

                SYS_CONSOLE_MESSAGE("\r\nMPFSUPLOAD completed");
                SYS_CONSOLE_MESSAGE("\r\nReboot system");
                SYS_CONSOLE_MESSAGE("\r\n");
                SYS_CONSOLE_MESSAGE("\r\n");
                SYS_Reboot();

                return HTTP_IO_DONE;
            }

            // Other states are not valid here
        default:
            break;
    }

    // Ask for more data
    return HTTP_IO_NEED_DATA;

}

// prepares the media storage for writing and writes
// the supplied header
// returns true if success, false otherwise
// pHttpCon->mediaHndl stores the media handle
static bool _HTTP_SetMediaWriteHeader(HTTP_CONN* pHttpCon, const uint8_t* buffer, unsigned int nBytes)
{
    DRV_MEDIA_IO_INTENT ioIntent;    

    const int dumy=0; // Replace with some meaningfull init variable
    SYS_FS_initialize(&dumy);

    ioIntent = DRV_MEDIA_IO_INTENT_WRITE | DRV_MEDIA_IO_INTENT_BLOCKING | DRV_MEDIA_IO_INTENT_EXCLUSIVE;
    pHttpCon->mediaHndl = DRV_MEDIA_Open(DRV_MEDIA_DEFAULT, "mpfs2", ioIntent);
    if(pHttpCon->mediaHndl != DRV_MEDIA_HANDLE_INVALID)
    {   // success
        DRV_MEDIA_WriteSetOffset(pHttpCon->mediaHndl, 0);
        if(DRV_MEDIA_Write(pHttpCon->mediaHndl, buffer, nBytes) == nBytes)
        {   // success
            return true;
        }
    }

    return false;
}

static void _HTTP_ReleaseMedia(HTTP_CONN* pHttpCon)
{
    if(pHttpCon->mediaHndl != DRV_MEDIA_HANDLE_INVALID)
    {
        DRV_MEDIA_Close(pHttpCon->mediaHndl);

        pHttpCon->mediaHndl = DRV_MEDIA_HANDLE_INVALID;
    }


    const int dumy=0; 
    SYS_FS_deinitialize(&dumy);
}
#endif //defined (HARMONY_FS)
#endif //defined (HTTP_FILE_UPLOAD)

/*****************************************************************************
  Function:
	void TCPIP_HTTP_FileInclude(const uint8_t* cFile)

  Summary:
	Writes a file byte-for-byte to the currently loaded TCP socket.

  Description:
	Allows an entire file to be included as a dynamic variable, providing
	a basic templating system for HTML web pages.  This reduces unneeded
	duplication of visual elements such as headers, menus, etc.

	When pHttpCon->callbackPos is 0, the file is opened and as many bytes
	as possible are written.  The current position is then saved to 
	pHttpCon->callbackPos and the file is closed.  On subsequent calls, 
	reading begins at the saved location and continues.  Once the end of
	the input file is reached, pHttpCon->callbackPos is set back to 0 to 
	indicate completion.

  Precondition:
	None

  Parameters:
	cFile - the name of the file to be sent

  Returns:
  	None
  	
  Remarks:
	Users should not call this function directly, but should instead add
	dynamic variables in the form of ~inc:filename.ext~ in their HTML code
	to include (for example) the file "filename.ext" at that specified
	location.  The MPFS2 Generator utility will handle the rest.
  ***************************************************************************/
void TCPIP_HTTP_FileInclude(HTTP_CONN_HANDLE connHandle, const uint8_t* cFile)
{
#if defined (HARMONY_FS)
    SYS_FS_HANDLE fp;
#else
    FILE_HANDLE fp;
#endif
    uint8_t incDataBuffer[64];
    uint32_t availbleTcpBuffSize,len;
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
#if defined (HARMONY_FS)
    if((fp = SYS_FS_FileOpen_Wrapper((const char *)cFile, SYS_FS_FILE_OPEN_READ)) == SYS_FS_HANDLE_INVALID)
#else
    if((fp = SYS_FS_open((const char *)cFile, 0)) == -1)
#endif
    {// File not found, so abort
        pHttpCon->TxFile.incFileRdCnt = 0;
        return;
    }
    else
    {// The file opened successfully, so seek the file
        if(pHttpCon->TxFile.lock_hdr == 0)
        {
#if defined (HARMONY_FS)
            pHttpCon->TxFile.numBytesHdrFile = SYS_FS_FileSize(fp);
#else
            pHttpCon->TxFile.numBytesHdrFile = SYS_FS_fsize(fp);
#endif
            pHttpCon->TxFile.incFileRdCnt = 0x00;
            if ((pHttpCon->TxFile.numBytesHdrFile == -1) || (pHttpCon->TxFile.numBytesHdrFile == 0)) {
#if defined (HARMONY_FS)
                SYS_FS_FileClose(fp);
                pHttpCon->TxFile.EndOfCallBackFileFlag=0x01;
#else
                SYS_FS_close(fp);
                pHttpCon->TxFile.EndOfCallBackFileFlag=true;
#endif
                return;   
            }
            pHttpCon->TxFile.lock_hdr=1;
        }
#if defined (HARMONY_FS)
        SYS_FS_FileSeek(fp, pHttpCon->TxFile.incFileRdCnt, SYS_FS_SEEK_SET);
#else
        SYS_FS_lseek(fp, pHttpCon->TxFile.incFileRdCnt, SEEK_SET);
#endif
    }

    availbleTcpBuffSize = TCPIP_TCP_PutIsReady(pHttpCon->socket);

    if(availbleTcpBuffSize == 0)
    {
        // Save the new address and close the file
#if defined (HARMONY_FS)
        pHttpCon->TxFile.incFileRdCnt = SYS_FS_FileTell(fp);
        SYS_FS_FileClose(fp);
        pHttpCon->TxFile.EndOfCallBackFileFlag=0x00;
#else
        pHttpCon->TxFile.incFileRdCnt = SYS_FS_ftell(fp);

        SYS_FS_close(fp);
        pHttpCon->TxFile.EndOfCallBackFileFlag=false;
#endif
        return;
    }

    if(availbleTcpBuffSize >= 64)
    {
        if(pHttpCon->TxFile.numBytesHdrFile <= 64)
        {
#if defined (HARMONY_FS)
            len = SYS_FS_FileRead(incDataBuffer, pHttpCon->TxFile.numBytesHdrFile, fp);
#else
            len = SYS_FS_read(fp, incDataBuffer, pHttpCon->TxFile.numBytesHdrFile);
#endif
            _HTTP_FileRdCheck(len==pHttpCon->TxFile.numBytesHdrFile, __FILE__, __LINE__);
            TCPIP_TCP_ArrayPut(pHttpCon->socket, incDataBuffer, pHttpCon->TxFile.numBytesHdrFile);
            pHttpCon->TxFile.numBytesHdrFile=0;
        }
        else
        {
#if defined (HARMONY_FS)
            len = SYS_FS_FileRead(incDataBuffer, 64, fp);
#else
            len = SYS_FS_read(fp, incDataBuffer, 64);
#endif
            _HTTP_FileRdCheck(len==64, __FILE__, __LINE__);
            TCPIP_TCP_ArrayPut(pHttpCon->socket, incDataBuffer, 64);
            pHttpCon->TxFile.numBytesHdrFile -=64;
        }
    }
    else //if(availbleTcpBuffSize != 0)
    {
        if(pHttpCon->TxFile.numBytesHdrFile <= availbleTcpBuffSize)
        {
#if defined (HARMONY_FS)
            len = SYS_FS_FileRead(incDataBuffer, pHttpCon->TxFile.numBytesHdrFile, fp);
#else
            len = SYS_FS_read(fp, incDataBuffer, pHttpCon->TxFile.numBytesHdrFile);
#endif
            _HTTP_FileRdCheck(len==pHttpCon->TxFile.numBytesHdrFile, __FILE__, __LINE__);
            TCPIP_TCP_ArrayPut(pHttpCon->socket, incDataBuffer, pHttpCon->TxFile.numBytesHdrFile);
            pHttpCon->TxFile.numBytesHdrFile=0;
        }
        else
        {
#if defined (HARMONY_FS)
            len = SYS_FS_FileRead(incDataBuffer, availbleTcpBuffSize, fp);
#else
            len = SYS_FS_read(fp, incDataBuffer, availbleTcpBuffSize);
#endif
            _HTTP_FileRdCheck(len==availbleTcpBuffSize, __FILE__, __LINE__);
            TCPIP_TCP_ArrayPut(pHttpCon->socket, incDataBuffer, availbleTcpBuffSize);
            pHttpCon->TxFile.numBytesHdrFile -=availbleTcpBuffSize;
        }
    }
    if(pHttpCon->TxFile.numBytesHdrFile == 0)
    {// If no bytes were read, an EOF was reached
#if defined (HARMONY_FS)
	SYS_FS_FileClose(fp);
        pHttpCon->TxFile.incFileRdCnt = 0x00;
        pHttpCon->TxFile.EndOfCallBackFileFlag=0x01;
#else
        SYS_FS_close(fp);
        pHttpCon->TxFile.incFileRdCnt = 0x00;
        pHttpCon->TxFile.EndOfCallBackFileFlag=true;
#endif
        pHttpCon->TxFile.lock_hdr=0;
        return;
    }

    // Save the new address and close the file
#if defined (HARMONY_FS)
    pHttpCon->TxFile.incFileRdCnt = SYS_FS_FileTell(fp);
    SYS_FS_FileClose(fp);
    pHttpCon->TxFile.EndOfCallBackFileFlag=-1;
#else
    pHttpCon->TxFile.incFileRdCnt = SYS_FS_ftell(fp);
    SYS_FS_close(fp);
    pHttpCon->TxFile.EndOfCallBackFileFlag=false;
#endif
}

#if defined (HARMONY_FS)
SYS_FS_HANDLE TCPIP_HTTP_CurrentConnectionFileGet(HTTP_CONN_HANDLE connHandle)
#else
FILE_HANDLE TCPIP_HTTP_CurrentConnectionFileGet(HTTP_CONN_HANDLE connHandle)
#endif
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
    return pHttpCon->file;
}

int TCPIP_HTTP_CurrentConnectionPostSmGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->smPost;
}

void TCPIP_HTTP_CurrentConnectionPostSmSet(HTTP_CONN_HANDLE connHandle, int stat)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->smPost = stat;
}

uint8_t* TCPIP_HTTP_CurrentConnectionDataBufferGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->data;
}

uint32_t TCPIP_HTTP_CurrentConnectionCallbackPosGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->callbackPos;
}

void TCPIP_HTTP_CurrentConnectionCallbackPosSet(HTTP_CONN_HANDLE connHandle, uint32_t pos)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->callbackPos = pos;
}

void TCPIP_HTTP_CurrentConnectionStatusSet(HTTP_CONN_HANDLE connHandle, HTTP_STATUS stat)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->httpStatus = stat;
}

void TCPIP_HTTP_CurrentConnectionHasArgsSet(HTTP_CONN_HANDLE connHandle, bool args)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->hasArgs = args;
}

uint32_t TCPIP_HTTP_CurrentConnectionByteCountGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->byteCount;
}

void TCPIP_HTTP_CurrentConnectionByteCountSet(HTTP_CONN_HANDLE connHandle, uint32_t byteCount)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->byteCount = byteCount;
}

void TCPIP_HTTP_CurrentConnectionByteCountDec(HTTP_CONN_HANDLE connHandle, uint32_t byteCount)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->byteCount -= byteCount;
}

TCP_SOCKET TCPIP_HTTP_CurrentConnectionSocketGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->socket;
}

uint8_t TCPIP_HTTP_CurrentConnectionIsAuthorizedGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	return pHttpCon->isAuthorized;
}

void TCPIP_HTTP_CurrentConnectionIsAuthorizedSet(HTTP_CONN_HANDLE connHandle, uint8_t auth)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
	pHttpCon->isAuthorized = auth;
}

void TCPIP_HTTP_CurrentConnectionUserDataSet(HTTP_CONN_HANDLE connHandle, const void* uData)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
    pHttpCon->userData = uData;
}

const void* TCPIP_HTTP_CurrentConnectionUserDataGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
    return pHttpCon->userData;
}

uint16_t TCPIP_HTTP_CurrentConnectionIndexGet(HTTP_CONN_HANDLE connHandle)
{
    HTTP_CONN* pHttpCon = (HTTP_CONN*)connHandle;
    return pHttpCon->connIx;
}


int TCPIP_HTTP_ActiveConnectionCountGet(void)
{
    HTTP_CONN* pHttpCon;
    int connIx;
    int connCount;

    connCount = 0;

    pHttpCon = httpConnCtrl + 0;
    for(connIx = 0; connIx < httpConnNo; connIx++, pHttpCon++)
    {
        if(pHttpCon->socket != INVALID_SOCKET && pHttpCon->sm != SM_HTTP_IDLE)
        {
            connCount++;
        }
    }

    return connCount;
}



#endif  // defined(TCPIP_STACK_USE_HTTP_SERVER)
