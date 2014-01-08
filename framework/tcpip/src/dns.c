/*******************************************************************************
  Domain Name System (DNS) Client 
  Module for Microchip TCP/IP Stack

  Summary:
    DNS client implementation file
    
  Description:
    This source file contains the functions of the 
    DNS client routines
    
    Provides  hostname to IP address translation
    Reference: RFC 1035
*******************************************************************************/

/*******************************************************************************
File Name:  DNS.c
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

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_STACK_USE_DNS)

/****************************************************************************
  Section:
	Constants and Global Variables
  ***************************************************************************/


static UDP_SOCKET       DNSSocket = INVALID_UDP_SOCKET;	// UDP socket to use for DNS queries
static const char*      DNSHostName;					// Host name in to look up
static uint8_t             RecordType;						// Record type being queried
static  union
{
    IPV4_ADDR ipv4Address;
    IPV6_ADDR ipv6Address;
} ResolvedAddress; 
static SYS_TICK		    stateStartTime;
static TCPIP_UINT16_VAL		    SentTransactionID;
static TCPIP_NET_IF*      pDNSNet;                        // current interface the DNS is working on
static IPV4_ADDR          DNSServers[2];                  // servers associated with the current interface
static int              vDNSServerIx;                   // current server used

static tcpipAsyncHandle   dnsTimerHandle = 0;

static int              dnsInitCount = 0;               // module initialization count

// Semaphore flags for the DNS module
static union
{
	uint8_t Val;
	struct
	{
		unsigned char DNSInUse 		: 1;	// Indicates the DNS module is in use
		unsigned char AddressValid	: 1;	// Indicates that the address resolution is valid and complete
		unsigned char AddressType 	: 2;    // IP_ADDRESS_TYPE_IPV6 or IP_ADDRESS_TYPE_IPV4
        unsigned char filler        : 4;
	} bits;
} Flags = {0x00};

// State machine for a DNS query
typedef enum
{
	DNS_IDLE = 0, 				// Initial state to reset client state variables
    // running, transient state
	DNS_START, 				    // resolution process started
	DNS_OPEN_SOCKET,			// Open UDP socket
	DNS_QUERY,					// Send DNS query to DNS server
	DNS_GET_RESULT,				// Wait for response from DNS server
	DNS_FAIL_ARP,				// ARP server not responding
	DNS_FAIL_SERVER,			// DNS server not responding
    // success state
	DNS_DONE,					// DNS query is finished OK
    // some error state
	DNS_FAIL_ARP_TMO,			// ARP resolution TMO
	DNS_FAIL_OPEN_TMO,			// Open Socket TMO
	DNS_FAIL_SERVER_TMO,		// DNS server TMO
}DNS_STATE;

static DNS_STATE smDNS = DNS_IDLE;

// Structure for the DNS header
typedef struct
{
	TCPIP_UINT16_VAL TransactionID;
	TCPIP_UINT16_VAL Flags;
	TCPIP_UINT16_VAL Questions;
	TCPIP_UINT16_VAL Answers;
	TCPIP_UINT16_VAL AuthoritativeRecords;
	TCPIP_UINT16_VAL AdditionalRecords;
} DNS_HEADER;

typedef struct
{
	// Response name is first, but it is variable length and must be retrieved using the DNSDiscardName() function
	TCPIP_UINT16_VAL	ResponseType;
	TCPIP_UINT16_VAL	ResponseClass;
	TCPIP_UINT32_VAL	ResponseTTL;
	TCPIP_UINT16_VAL	ResponseLen;
} DNS_ANSWER_HEADER;


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/

static void DNSPutString(UDP_SOCKET s, const char* String);
static void DNSDiscardName(UDP_SOCKET s);
static DNS_STATE DNSRetry(DNS_STATE currState);

/*static __inline__*/static  void /*__attribute__((always_inline))*/ _DNSReleaseSocket(void)
{
	if(DNSSocket != INVALID_UDP_SOCKET)
	{
		TCPIP_UDP_Close(DNSSocket);
		DNSSocket = INVALID_UDP_SOCKET;
	}
}

/****************************************************************************
  Section:
	Implementation
  ***************************************************************************/


/*****************************************************************************
  Function:
	bool TCPIP_DNS_ClientInitialize(const TCPIP_STACK_MODULE_CTRL* const stackData,
                       const DNS_CLIENT_MODULE_GONFIG* dnsData);

  Summary:
	Initializes the DNS module.
	
  Description:
	This function perform the initialization of the DNS client module.
    It has to be called before any other operation with the DNS client
    is possible.

  Precondition:
	Stack is initialized.

  Parameters:
    stackData - stack initialization data

    dnsData   - DNS client module specific initialization data    

  Return Values:
  	true      - the initialization was performed OK and the module is ready to be used
  	false     - The DNS module initialization failed.
  	
  Remarks:
	None
  ***************************************************************************/
bool TCPIP_DNS_ClientInitialize(const TCPIP_STACK_MODULE_CTRL* const stackData,
                       const DNS_CLIENT_MODULE_CONFIG* dnsData)
{
    if(stackData->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface restart
        return true;
    }

    // stack start up
    if(dnsInitCount != 0)
    {   // initialize just once
        dnsInitCount++;
        return true;
    }

    // 1st time init    
    smDNS = DNS_IDLE;
    Flags.Val = 0;
    DNSSocket = INVALID_UDP_SOCKET;

    if(dnsTimerHandle == 0)
    {   // once per service
        dnsTimerHandle = _TCPIPStackAsyncHandlerRegister(TCPIP_DNS_ClientTask, 0, DNS_CLIENT_TASK_PROCESS_RATE);
        if(dnsTimerHandle == 0)
        {
            return false;
        }
    }

    dnsInitCount++;
    return true;
}

/*****************************************************************************
  Function:
	void TCPIP_DNS_ClientDeinitialize(const TCPIP_STACK_MODULE_CTRL* const stackData);

  Summary:
	De-Initializes the DNS module.
	
  Description:
	This function perform the de-initialization of the DNS client module.
    It is used to release all the resources that are in use by the DNS client.
    
  Precondition:
	Stack is initialized.

  Parameters:
	stackData   - interface to use
                Normally should be a default DNS interface
                
  Return Values:
  	None
  	
  Remarks:
	None
  ***************************************************************************/
void TCPIP_DNS_ClientDeinitialize(const TCPIP_STACK_MODULE_CTRL* const stackData)
{
    // interface going down
    if(pDNSNet == stackData->pNetIf)
    {   // my interface is shut down
        TCPIP_DNS_UsageEnd(0);
    }
        
    if(stackData->stackAction == TCPIP_STACK_ACTION_DEINIT)
    {   // stack shut down
        if(dnsInitCount > 0)
        {   // we're up and running

            if(--dnsInitCount == 0)
            {   // all closed
                // release resources
                if(dnsTimerHandle)
                {
                    _TCPIPStackAsyncHandlerDeRegister(dnsTimerHandle);
                    dnsTimerHandle = 0;
                }
            }
        }
    }


}

/*****************************************************************************
  Function:
	DNS_RESULT TCPIP_DNS_UsageBegin(TCPIP_NET_HANDLE netH)

  Summary:
	Claims access to the DNS module.
	
  Description:
	This function acts as a semaphore to obtain usage of the DNS module.
	Call this function and ensure that it returns DNS_RES_OK before calling any
	other DNS APIs.  Call TCPIP_DNS_UsageEnd when this application no longer 
	needs the DNS module so that other applications may make use of it.

  Precondition:
	Stack is initialized.

  Parameters:
	netH   - interface to use
                If 0, a default interface will be selected

  Return Values:
  	DNS_RES_OK      - the calling application has sucessfully taken ownership of the DNS module
  	DNS_RES_BUSY    - The DNS module is currently in use.
                      Yield to the stack and attempt this call again later.
  	
  Remarks:
	Ensure that TCPIP_DNS_UsageEnd is always called once your application has
	obtained control of the DNS module.  If this is not done, the stack
	will hang for all future applications requiring DNS access.
  ***************************************************************************/
DNS_RESULT TCPIP_DNS_UsageBegin(TCPIP_NET_HANDLE netH)
{
    TCPIP_NET_IF* pNewIf;
    
	if(Flags.bits.DNSInUse)
		return DNS_RES_BUSY;

    pNewIf = _TCPIPStackHandleToNetLinked(netH);
    
    if(pNewIf == 0)
    {   // try a default interface
        if(TCPIP_STACK_NetworkIsLinked(pDNSNet))
        {
            pNewIf = pDNSNet;
        }
        else
        {
            pNewIf = _TCPIPStackAnyNetLinked(true);
        }
    }
    // else pNewIf should do just fine

    if(pNewIf == 0)
    {
        return DNS_RES_NO_INTERFACE;
    }
    
    pDNSNet = pNewIf;
    
	Flags.bits.DNSInUse = true;
    DNSServers[0] = pDNSNet->PrimaryDNSServer;
    DNSServers[1] = pDNSNet->SecondaryDNSServer;
    
    smDNS = DNS_IDLE;

	return DNS_RES_OK;
}


/*****************************************************************************
  Function:
	DNS_RESULT TCPIP_DNS_UsageEnd(TCPIP_NET_HANDLE netH)

  Summary:
	Releases control of the DNS module.
	
  Description:
	This function acts as a semaphore to release control of the DNS module.
	Call this function when this application no longer needs the DNS 
	module so that other applications may make use of it.

  Precondition:
	TCPIP_DNS_UsageBegin returned DNS_RES_OK on a previous call.

  Parameters:
	netH   - interface to release
                Not used.

  Return Values:
  	DNS_RES_OK - The DNS module successfully released.
  	
  Remarks:
	Ensure that TCPIP_DNS_UsageEnd is always called once your application has
	obtained control of the DNS module.  If this is not done, the stack
	will hang for all future applications requiring DNS access.
  ***************************************************************************/
DNS_RESULT TCPIP_DNS_UsageEnd(TCPIP_NET_HANDLE netH)
{
    _DNSReleaseSocket();
    smDNS = DNS_IDLE;
	Flags.bits.DNSInUse = false;

    return DNS_RES_OK;
}


/*****************************************************************************
  Function:
	void TCPIP_DNS_Resolve(uint8_t* Hostname, DNS_RESOLVE_TYPE Type)

  Summary:
	Begins resolution of an address.
	
  Description:
	This function attempts to resolve a host name to an IP address.  When 
	called, it starts the DNS state machine.  Call TCPIP_DNS_IsResolved repeatedly
	to determine if the resolution is complete.
	
	Only one DNS resoultion may be executed at a time.  The Hostname must 
	not be modified in memory until the resolution is complete.

  Precondition:
	TCPIP_DNS_UsageBegin returned DNS_RES_OK on a previous call.

  Parameters:
	Hostname - A pointer to the null terminated string specifiying the
		host for which to resolve an IP.
	RecordType - DNS_TYPE_A or DNS_TYPE_MX depending on what type of
		record resolution is desired.

  Returns:
  	DNS_RES_OK
  	
  Remarks:
	This function requires access to one UDP socket.  If none are available,
	UDP_MAX_SOCKETS may need to be increased.

  ***************************************************************************/
DNS_RESULT TCPIP_DNS_Resolve(const char* Hostname, DNS_RESOLVE_TYPE Type)
{
	if(TCPIP_Helper_StringToIPAddress(Hostname, &ResolvedAddress.ipv4Address))
	{
		Flags.bits.AddressValid = true;
		smDNS = DNS_DONE;
        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV4;
	}
#if defined (TCPIP_STACK_USE_IPV6)
    else if (TCPIP_Helper_StringToIPv6Address (Hostname, &ResolvedAddress.ipv6Address))
    {
        Flags.bits.AddressValid = true;
        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV6;
        smDNS = DNS_DONE;
    }
#endif
	else
	{	
		smDNS = DNS_START;
		RecordType = (uint8_t)Type;
		Flags.bits.AddressValid = false;
    }

    DNSHostName = Hostname;
    return DNS_RES_OK;
}


/*****************************************************************************
  Function:
	DNS_RESULT TCPIP_DNS_IsResolved(const char* HostName, IPV4_ADDR* HostIP)

  Summary:
	Determines if the DNS resolution is complete and provides the IP.
	
  Description:
	Call this function to determine if the DNS resolution of an address has
	been completed.  If so, the resolved address will be provided in HostIP.

  Precondition:
	TCPIP_DNS_Resolve has been called.

  Parameters:
	Hostname - A pointer to the null terminated string specifiying the
		host for which to resolve an IP.
	HostIP - A pointer to an IPV4_ADDR structure in which to store the 
		resolved IP address once resolution is complete.

  Return Values:
  	DNS_RES_OK       - The DNS client has obtained an IP
  		               HostIP will contain the resolved address.
  	DNS_RES_PENDING  - The resolution process is still in progress.
    DNS_RES_SERVER_TMO  - DNS server timed out
    DNS_RES_NO_ENTRY - no such entry to be resolved exists
    
    
  Remarks:
    None.
    
  ***************************************************************************/
DNS_RESULT TCPIP_DNS_IsResolved(const char* HostName, void* HostIP)
{
    
    if(smDNS == DNS_IDLE || strcmp(DNSHostName, HostName)!= 0)
    {
        return DNS_RES_NO_ENTRY;
    }
    
    if (smDNS == DNS_DONE)
    {
#if defined (TCPIP_STACK_USE_IPV6)
        if (Flags.bits.AddressType == IP_ADDRESS_TYPE_IPV6)
        {
            memcpy (HostIP, &ResolvedAddress.ipv6Address, sizeof (IPV6_ADDR));
        }
        else
#endif
        {
			((IPV4_ADDR *)HostIP)->Val = ResolvedAddress.ipv4Address.Val;
        }

        return DNS_RES_OK;   
    }
    
    if(smDNS < DNS_DONE)
    {
        return DNS_RES_PENDING;
    }
    
    // some kind of error
    switch (smDNS)
    {
        case DNS_FAIL_ARP_TMO:
            return DNS_RES_ARP_TMO; 

        case DNS_FAIL_OPEN_TMO:
            return DNS_RES_OPEN_TMO; 

        default:    // DNS_FAIL_SERVER_TMO:
            return DNS_RES_SERVER_TMO; 
    }

}


/*****************************************************************************
  Function:
	void TCPIP_DNS_ClientTask(void)

  Summary:
	DNS client state machine
	
  Description:
    Process the DNS client state machine
  
  Precondition:
	TCPIP_DNS_ClientInitialize has been called.

  Parameters:
    None
    
  Return Values:
    None

  ***************************************************************************/
void TCPIP_DNS_ClientTask(void)
{
	uint8_t 				i;
	TCPIP_UINT16_VAL			w;
	DNS_HEADER			DNSHeader;
	DNS_ANSWER_HEADER	DNSAnswerHeader;
    

    switch(smDNS)
	{
		case DNS_IDLE:
            break;  // nothing to do

		case DNS_START:
            smDNS = DNSRetry(DNS_START);
            stateStartTime = 0;  // flag the first Open try
			break;

		case DNS_OPEN_SOCKET:
            DNSSocket = TCPIP_UDP_ClientOpen(IP_ADDRESS_TYPE_IPV4, DNS_CLIENT_PORT, (IP_MULTI_ADDRESS*)(DNSServers + vDNSServerIx));
			if(DNSSocket == INVALID_UDP_SOCKET)
            {
                if(stateStartTime == 0)
                {
                    stateStartTime = SYS_TICK_Get();
                }
                else if(SYS_TICK_Get() - stateStartTime > (DNS_CLIENT_OPEN_TMO * SYS_TICK_TicksPerSecondGet()))
                {
					smDNS = DNS_FAIL_OPEN_TMO;
                }
                
                break;
            }
            
            // got a valid UDP socket
            TCPIP_UDP_SocketNetSet(DNSSocket, pDNSNet);
            stateStartTime = SYS_TICK_Get();
            smDNS = DNS_QUERY;
            // no break, start sending the query;

		case DNS_QUERY:
            // since we don't do ARP here anymore we have to wait for the UDP to do it!
            if(!TCPIP_UDP_IsOpened(DNSSocket) || (TCPIP_UDP_TxPutIsReady(DNSSocket, 18 + strlen (DNSHostName)) < (18 + strlen (DNSHostName))))
            {
                if(SYS_TICK_Get() - stateStartTime > (DNS_CLIENT_OPEN_TMO * SYS_TICK_TicksPerSecondGet()))
                {
					smDNS = DNS_FAIL_OPEN_TMO;
                }
                
				break;  // wait some more
            }
			
			// Put DNS query here
			SentTransactionID.Val = (uint16_t)SYS_Rand();
			TCPIP_UDP_Put(DNSSocket, SentTransactionID.v[1]);// User chosen transaction ID
			TCPIP_UDP_Put(DNSSocket, SentTransactionID.v[0]);
			TCPIP_UDP_Put(DNSSocket, 0x01);		// Standard query with recursion
			TCPIP_UDP_Put(DNSSocket, 0x00);	
			TCPIP_UDP_Put(DNSSocket, 0x00);		// 0x0001 questions
			TCPIP_UDP_Put(DNSSocket, 0x01);
			TCPIP_UDP_Put(DNSSocket, 0x00);		// 0x0000 answers
			TCPIP_UDP_Put(DNSSocket, 0x00);
			TCPIP_UDP_Put(DNSSocket, 0x00);		// 0x0000 name server resource records
			TCPIP_UDP_Put(DNSSocket, 0x00);
			TCPIP_UDP_Put(DNSSocket, 0x00);		// 0x0000 additional records
			TCPIP_UDP_Put(DNSSocket, 0x00);

			// Put hostname string to resolve
            DNSPutString(DNSSocket, DNSHostName);

			TCPIP_UDP_Put(DNSSocket, 0x00);		// Type: DNS_TYPE_A A (host address) or DNS_TYPE_MX for mail exchange
			TCPIP_UDP_Put(DNSSocket, RecordType);
			TCPIP_UDP_Put(DNSSocket, 0x00);		// Class: IN (Internet)
			TCPIP_UDP_Put(DNSSocket, 0x01);

			TCPIP_UDP_Flush(DNSSocket);
			stateStartTime = SYS_TICK_Get();
			smDNS = DNS_GET_RESULT;
			break;

		case DNS_GET_RESULT:
			if(!TCPIP_UDP_GetIsReady(DNSSocket))
			{
				if(SYS_TICK_Get() - stateStartTime > (DNS_CLIENT_SERVER_TMO * SYS_TICK_TicksPerSecondGet()))
                {
					smDNS = DNS_FAIL_SERVER;
                }
				break;
			}


			// Retrieve the DNS header and de-big-endian it
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.TransactionID.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.TransactionID.v[0]);

			// Throw this packet away if it isn't in response to our last query
			if(DNSHeader.TransactionID.Val != SentTransactionID.Val)
			{
				TCPIP_UDP_Discard(DNSSocket);
				break;
			}

			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Flags.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Flags.v[0]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Questions.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Questions.v[0]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Answers.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.Answers.v[0]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.AuthoritativeRecords.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.AuthoritativeRecords.v[0]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.AdditionalRecords.v[1]);
			TCPIP_UDP_Get(DNSSocket, &DNSHeader.AdditionalRecords.v[0]);

			// Remove all questions (queries)
			while(DNSHeader.Questions.Val--)
			{
				DNSDiscardName(DNSSocket);
				TCPIP_UDP_Get(DNSSocket, &w.v[1]);		// Question type
				TCPIP_UDP_Get(DNSSocket, &w.v[0]);
				TCPIP_UDP_Get(DNSSocket, &w.v[1]);		// Question class
				TCPIP_UDP_Get(DNSSocket, &w.v[0]);
			}
			
			// Scan through answers
			while(DNSHeader.Answers.Val--)
			{				
				DNSDiscardName(DNSSocket);					// Throw away response name
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[1]);		// Response type
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[1]);	// Response class
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[3]);		// Time to live
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[2]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[1]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[1]);		// Response length
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[0]);

				// Make sure that this is a 4 byte IP address, response type A or MX, class 1
				// Check if this is Type A, MX, or AAAA
				if( DNSAnswerHeader.ResponseClass.Val	== 0x0001u) // Internet class
				{
                    if (DNSAnswerHeader.ResponseType.Val	== 0x0001u &&
    					DNSAnswerHeader.ResponseLen.Val		== 0x0004u)
                    {
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV4;
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[0]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[1]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[2]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[3]);
    					goto DoneSearchingRecords;
                    }
                    else if (DNSAnswerHeader.ResponseType.Val == 0x001Cu &&
    					        DNSAnswerHeader.ResponseLen.Val	== 0x0010u)
                    {
                        if (RecordType != DNS_TYPE_AAAA)
                        {
        					while(DNSAnswerHeader.ResponseLen.Val--)
        					{
        						TCPIP_UDP_Get(DNSSocket, &i);
        					}
                            break;
                        }
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV6;
                        TCPIP_UDP_ArrayGet (DNSSocket, (void *)&ResolvedAddress.ipv6Address, sizeof (IPV6_ADDR));
    					goto DoneSearchingRecords;                        
                    }
                    else
                    {
    					while(DNSAnswerHeader.ResponseLen.Val--)
    					{
    						TCPIP_UDP_Get(DNSSocket, &i);
    					}
                    }
				}
				else
				{
					while(DNSAnswerHeader.ResponseLen.Val--)
					{
						TCPIP_UDP_Get(DNSSocket, &i);
					}
				}
			}

			// Remove all Authoritative Records
			while(DNSHeader.AuthoritativeRecords.Val--)
			{
				DNSDiscardName(DNSSocket);					// Throw away response name
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[1]);		// Response type
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[1]);	// Response class
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[3]);		// Time to live
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[2]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[1]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[1]);		// Response length
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[0]);

				// Make sure that this is a 4 byte IP address, response type A or MX, class 1
				// Check if this is Type A
				if( DNSAnswerHeader.ResponseClass.Val	== 0x0001u) // Internet class
				{
                    if (DNSAnswerHeader.ResponseType.Val	== 0x0001u &&
    					DNSAnswerHeader.ResponseLen.Val		== 0x0004u)
                    {
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV4;
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[0]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[1]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[2]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[3]);
    					goto DoneSearchingRecords;
                    }
                    else if (DNSAnswerHeader.ResponseType.Val == 0x001Cu &&
    					        DNSAnswerHeader.ResponseLen.Val	== 0x0010u)
                    {
                        if (RecordType != DNS_TYPE_AAAA)
                        {
        					while(DNSAnswerHeader.ResponseLen.Val--)
        					{
        						TCPIP_UDP_Get(DNSSocket, &i);
        					}
                            break;
                        }
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV6;
                        TCPIP_UDP_ArrayGet (DNSSocket, (void *)&ResolvedAddress.ipv6Address, sizeof (IPV6_ADDR));
    					goto DoneSearchingRecords;                        
                    }
                    else
                    {
    					while(DNSAnswerHeader.ResponseLen.Val--)
    					{
    						TCPIP_UDP_Get(DNSSocket, &i);
    					}
                    }
				}
				else
				{
					while(DNSAnswerHeader.ResponseLen.Val--)
					{
						TCPIP_UDP_Get(DNSSocket, &i);
					}
				}
			}

			// Remove all Additional Records
			while(DNSHeader.AdditionalRecords.Val--)
			{
				DNSDiscardName(DNSSocket);					// Throw away response name
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[1]);		// Response type
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseType.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[1]);	// Response class
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseClass.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[3]);		// Time to live
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[2]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[1]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseTTL.v[0]);
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[1]);		// Response length
				TCPIP_UDP_Get(DNSSocket, &DNSAnswerHeader.ResponseLen.v[0]);

				// Make sure that this is a 4 byte IP address, response type A or MX, class 1
				// Check if this is Type A
				if( DNSAnswerHeader.ResponseClass.Val	== 0x0001u) // Internet class
				{
                    if (DNSAnswerHeader.ResponseType.Val	== 0x0001u &&
    					DNSAnswerHeader.ResponseLen.Val		== 0x0004u)
                    {
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV4;
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[0]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[1]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[2]);
    					TCPIP_UDP_Get(DNSSocket, &ResolvedAddress.ipv4Address.v[3]);
    					goto DoneSearchingRecords;
                    }
                    else if (DNSAnswerHeader.ResponseType.Val == 0x001Cu &&
    					        DNSAnswerHeader.ResponseLen.Val	== 0x0010u)
                    {
                        if (RecordType != DNS_TYPE_AAAA)
                        {
        					while(DNSAnswerHeader.ResponseLen.Val--)
        					{
        						TCPIP_UDP_Get(DNSSocket, &i);
        					}
                            break;
                        }
    					Flags.bits.AddressValid = true;
                        Flags.bits.AddressType = IP_ADDRESS_TYPE_IPV6;
                        TCPIP_UDP_ArrayGet (DNSSocket, (void *)&ResolvedAddress.ipv6Address, sizeof (IPV6_ADDR));
    					goto DoneSearchingRecords;                        
                    }
                    else
                    {
    					while(DNSAnswerHeader.ResponseLen.Val--)
    					{
    						TCPIP_UDP_Get(DNSSocket, &i);
    					}
                    }
				}
				else
				{
					while(DNSAnswerHeader.ResponseLen.Val--)
					{
						TCPIP_UDP_Get(DNSSocket, &i);
					}
				}
			}

DoneSearchingRecords:

			TCPIP_UDP_Discard(DNSSocket);
            _DNSReleaseSocket();
			if(Flags.bits.AddressValid)
            {
                smDNS = DNS_DONE;
            }
            else
            {
                smDNS = DNSRetry(DNS_FAIL_SERVER);
            }
            break;  // done
            
		case DNS_FAIL_ARP:
            // see if there is other server we may try
            smDNS = DNSRetry(DNS_FAIL_ARP);
            break;

		case DNS_FAIL_SERVER:
            smDNS = DNSRetry(DNS_FAIL_SERVER);
			break;

        default:    // DNS_DONE, DNS_FAIL_ARP_TMO, DNS_FAIL_OPEN_TMO, DNS_FAIL_SERVER_TMO  
            // either done or some error state
            break;
	}
    
}

// see if we can perform a retry
static DNS_STATE DNSRetry(DNS_STATE currState)
{
    _DNSReleaseSocket();
    
    if(currState == DNS_START)
    {
        vDNSServerIx = 0;
    }
    else
    {
        vDNSServerIx++;
    }
    
    for( ; vDNSServerIx < sizeof(DNSServers)/sizeof(*DNSServers); vDNSServerIx++) 
    {   // can try another server if valid address
        if(DNSServers[vDNSServerIx].Val != 0)
        {
            return DNS_OPEN_SOCKET;   // new state
        }
    }

    // nothing else to try
    if(currState == DNS_FAIL_ARP)
    {
        return DNS_FAIL_ARP_TMO;
    }

    // default: DNS_FAIL_SERVER
    return DNS_FAIL_SERVER_TMO;
}

/*****************************************************************************
  Function:
	static void DNSPutString(UDP_SOCKET s, const char* String)

  Summary:
	Writes a string to the DNS socket.
	
  Description:
	This function writes a string to the DNS socket, ensuring that it is
	properly formatted.

  Precondition:
	UDP socket is obtained and ready for writing.

  Parameters:
	String - the string to write to the UDP socket.

  Returns:
  	None
  ***************************************************************************/
static void DNSPutString(UDP_SOCKET s, const char* String)
{
	const char *RightPtr;
	uint8_t i;
	uint8_t Len;

	RightPtr = String;

	while(1)
	{
		do
		{
			i = *RightPtr++;
		} while((i != 0x00u) && (i != '.') && (i != '/') && (i != ',') && (i != '>'));
	
		// Put the length and data
		// Also, skip over the '.' in the input string
		Len = (uint8_t)(RightPtr-String-1);
		TCPIP_UDP_Put(s, Len);
		String += TCPIP_UDP_ArrayPut(s, (uint8_t*)String, Len) + 1;

		if(i == 0x00u || i == '/' || i == ',' || i == '>')
			break;
	}
	
	// Put the string null terminator character (zero length label)
	TCPIP_UDP_Put(s, 0x00);
}


/*****************************************************************************
  Function:
	static void DNSDiscardName(UDP_SOCKET s)

  Summary:
	Reads a name string or string pointer from the DNS socket and discards it.
	
  Description:
	This function reads a name string from the DNS socket.  Each string 
	consists of a series of labels.  Each label consists of a length prefix 
	byte, followed by the label bytes.  At the end of the string, a zero length 
	label is found as termination.  If name compression is used, this function 
	will automatically detect the pointer and discard it.

  Precondition:
	UDP socket is obtained and ready for reading a DNS name

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
static void DNSDiscardName(UDP_SOCKET s)
{
	uint8_t i;

	while(1)
	{
		// Get first byte which will tell us if this is a 16-bit pointer or the 
		// length of the first of a series of labels
		if(!TCPIP_UDP_Get(s, &i))
			return;
		
		// Check if this is a pointer, if so, get the reminaing 8 bits and return
		if((i & 0xC0u) == 0xC0u)
		{
			TCPIP_UDP_Get(s, &i);
			return;
		}

		// Exit once we reach a zero length label
		if(i == 0u)					
			return;

		// Discard complete label
		TCPIP_UDP_ArrayGet(DNSSocket, NULL, i);		
	}
}


#else
DNS_RESULT  TCPIP_DNS_UsageBegin(TCPIP_NET_HANDLE netH)
{
    return DNS_RES_NO_SERVICE; 
}

DNS_RESULT  TCPIP_DNS_Resolve(const char* HostName, DNS_RESOLVE_TYPE Type)
{
    return DNS_RES_NO_SERVICE; 
}

DNS_RESULT  TCPIP_DNS_IsResolved(const char* HostName, void* HostIP)
{
    return DNS_RES_NO_SERVICE; 
}

DNS_RESULT  TCPIP_DNS_UsageEnd(TCPIP_NET_HANDLE netH)
{
    return DNS_RES_OK; 
}


#endif	//#if defined(TCPIP_STACK_USE_DNS)
