/*******************************************************************************
  Dynamic Host Configuration Protocol (DHCP) Server

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    - Provides automatic IP address, subnet mask, gateway address, 
      DNS server address, and other configuration parameters on DHCP 
      enabled networks.
    - Reference: RFC 2131, 2132
*******************************************************************************/

/*******************************************************************************
File Name:  dhcps.c
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
#define __DHCPS_C

#include "tcpip/src/tcpip_private.h"
#include "tcpip/src/dhcp_private.h"
#include "tcpip/udp.h"
#include "tcpip/src/dhcps_private.h"
#include "tcpip/src/hash_fnv.h"


#if defined(TCPIP_STACK_USE_DHCP_SERVER)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_DHCP_SERVER

SYS_TICK initTime ;

const DHCPS_MODULE_CONFIG dhcpsConfigDefaultData = 
{
	true,
	true,
	DHCPS_LEASE_ENTRIES_DEFAULT,
    DHCPS_LEASE_SOLVED_ENTRY_TMO,
    DHCPS_IP_ADDRESS_RANGE_START,
};

static DHCPS_HASH_DCPT dhcpsHashDcpt = { 0, {0} };

// DHCP is running on all interfaces
static DHCP_SRVR_DCPT      dhcpSDcpt;
static const void*          dhcpSMemH = 0;        // memory handle

static int                  dhcpSInitCount = 0;     // initialization count

static void _DHCPSUpdateEntry(DHCPS_HASH_ENTRY* dhcpsHE);

static void DHCPReplyToDiscovery(BOOTP_HEADER *Header,DHCP_SRVR_DCPT * pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt );
static void DHCPReplyToRequest(BOOTP_HEADER *Header, bool bAccept, int netIx, bool bRenew,
														DHCP_SRVR_DCPT* pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt );
static void _DHCPServerCleanup(int netIx);
static DHCPS_RESULT preAssignToDHCPClient(BOOTP_HEADER *Header,DHCP_SRVR_DCPT * pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt);
static bool isMacAddrEffective(const TCPIP_MAC_ADDR *macAddr);
static void DHCPSReplyToInform(BOOTP_HEADER *boot_header, DHCP_SRVR_DCPT* pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt,bool bAccept);
static void _DHCPSrvClose(TCPIP_NET_IF* pNetIf, bool disable);
static void _DHCPSDeleteResources(void);
static size_t DHCPSgetFreeHashIndex(OA_HASH_DCPT* pOH,void* key);
static DHCPS_RESULT DHCPSLocateRequestedIpAddress(IPV4_ADDR *requestedAddr);
static  DHCPS_RESULT DHCPSRemoveHashEntry(TCPIP_MAC_ADDR* hwAdd,IPV4_ADDR* pIPAddr);
static bool DHCPSCopyDataArrayToProcessBuff(uint8_t *val ,DHCPSERVERDATA *putbuf,int len);
static bool TCPIP_DHCPS_DataCopyToProcessBuffer(uint8_t val ,DHCPSERVERDATA *putbuf);
static bool _DHCPSAddCompleteEntry(int intfIdx,IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd,DHCPS_ENTRY_FLAGS entryFlag);

/*static __inline__*/static  void /*__attribute__((always_inline))*/ _DHCPSSetHashEntry(DHCPS_HASH_ENTRY* dhcpsHE, DHCPS_ENTRY_FLAGS newFlags,TCPIP_MAC_ADDR* hwAdd,IPV4_ADDR* pIPAddr)
{
    dhcpsHE->hEntry.flags.value &= ~DHCPS_FLAG_ENTRY_VALID_MASK;
    dhcpsHE->hEntry.flags.value |= newFlags;
    
    if(hwAdd)
    {
        dhcpsHE->hwAdd = *hwAdd;		
		dhcpsHE->ipAddress.Val = ((DHCPS_UNALIGNED_KEY*)pIPAddr)->v;
    }
    
    dhcpsHE->Client_Lease_Time = SYS_TICK_Get();
	dhcpsHE->pendingTime = SYS_TICK_Get();
}

/*static __inline__*/static  void /*__attribute__((always_inline))*/ _DHCPSRemoveCacheEntries(DHCPS_HASH_DCPT* pDHCPSHashDcpt)
{

    if(pDHCPSHashDcpt->hashDcpt)
    {
        TCPIP_OAHASH_EntriesRemoveAll(pDHCPSHashDcpt->hashDcpt);
    }
}

static  DHCPS_RESULT DHCPSRemoveHashEntry(TCPIP_MAC_ADDR* hwAdd,IPV4_ADDR* pIPAddr)
{
	DHCPS_HASH_DCPT *pDhcpsHashDcpt;
	OA_HASH_ENTRY*	hE;


	pDhcpsHashDcpt = &dhcpsHashDcpt;
	
    if(hwAdd)
    {
    	hE = TCPIP_OAHASH_EntryLookup(pDhcpsHashDcpt->hashDcpt,hwAdd);
		if(hE != 0)
		{
			if(TCPIP_DHCPS_HashIPKeyCompare(pDhcpsHashDcpt->hashDcpt,hE,pIPAddr)== 0)
			{
				TCPIP_OAHASH_EntryRemove(pDhcpsHashDcpt->hashDcpt,hE);				
				return DHCPS_RES_OK;
			}				
		}
    }

	return DHCPS_RES_NO_ENTRY;
    
}


/*****************************************************************************
  Function:
	static void _DHCPSUpdateEntry(DHCPS_HASH_ENTRY* dhcpsHE)

  Description:
    Updates the info for an existing DHCPS Hash entry

  Precondition:
    None

  Parameters:
    pIf             - interface
    dhcpsHE           - particular cache entry to be updated
    hwAdd           - the (new) hardware address

  Return Values:
    None
  ***************************************************************************/
static void _DHCPSUpdateEntry(DHCPS_HASH_ENTRY* dhcpsHE)
{
    
	 dhcpsHE->Client_Lease_Time = SYS_TICK_Get();
	 dhcpsHE->pendingTime = 0;		
	 
	 dhcpsHE->hEntry.flags.value &= ~DHCPS_FLAG_ENTRY_VALID_MASK;
	 dhcpsHE->hEntry.flags.value |= DHCPS_FLAG_ENTRY_COMPLETE;

}

/*****************************************************************************
  Function:
    bool TCPIP_DHCPS_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const DHCPS_MODULE_CONFIG* pDhcpConfig);

  Summary:
	Resets the DHCP server module for the specified interface.

  Description:
	Resets the DHCP server module for the specified interface.

  Precondition:
	None

  Parameters:
	stackCtrl - pointer to stack structure specifying the interface to initialize

  Returns:
	None

  Remarks:
	This function should be called internally just once per interface 
    by the stack manager.
***************************************************************************/
bool TCPIP_DHCPS_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const DHCPS_MODULE_CONFIG* pDhcpsConfig)
{    
    size_t hashMemSize=0;
    OA_HASH_DCPT*   hashDcpt;
    DHCP_SRVR_DCPT* pServer;

	
    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface restart
        pServer = &dhcpSDcpt; // + stackCtrl->netIx;
        if(stackCtrl->pNetIf->Flags.bIsDHCPSrvEnabled != 0)
        {
            TCPIP_DHCPS_Enable(stackCtrl->pNetIf);
        }
		dhcpSMemH = stackCtrl->memH;
        return true;
    }
	
    if(pDhcpsConfig == 0)
    {
        pDhcpsConfig = &dhcpsConfigDefaultData;
    }
    // stack init
    if(dhcpSInitCount == 0)
    {   // first time we're run
        // store the memory allocation handle
        dhcpSMemH = stackCtrl->memH;

		hashMemSize = sizeof(OA_HASH_DCPT) + pDhcpsConfig->leaseEntries * sizeof(DHCPS_HASH_ENTRY);
		
		hashDcpt = (OA_HASH_DCPT*)TCPIP_HEAP_Malloc(dhcpSMemH, hashMemSize);
		
		if(hashDcpt == 0)
		{	// failed
		// Remove all the DHCPS lease entries.
			return false;
		}
		// populate the entries
		hashDcpt->memBlk = hashDcpt+1;
		hashDcpt->hParam = &dhcpsHashDcpt;
		hashDcpt->hEntrySize = sizeof(DHCPS_HASH_ENTRY);
		hashDcpt->hEntries = pDhcpsConfig->leaseEntries;
        hashDcpt->probeStep = DHCPS_HASH_PROBE_STEP;

		hashDcpt->hashF= TCPIP_DHCPS_MACHashKeyHash;
#if defined(OA_DOUBLE_HASH_PROBING)
        hashDcpt->probeHash = TCPIP_DHCPS_HashProbeHash;
#endif  // defined(OA_DOUBLE_HASH_PROBING)
		hashDcpt->cpyF = TCPIP_DHCPS_HashMACKeyCopy;
		hashDcpt->delF = TCPIP_DHCPS_HashDeleteEntry;
		hashDcpt->cmpF = TCPIP_DHCPS_HashMACKeyCompare;
		TCPIP_OAHASH_Initialize(hashDcpt);	
		dhcpsHashDcpt.hashDcpt = hashDcpt;
		dhcpsHashDcpt.leaseDuartion = pDhcpsConfig->entrySolvedTmo;
		if(pDhcpsConfig->startIpAddressRange)
		{
			TCPIP_Helper_StringToIPAddress(pDhcpsConfig->startIpAddressRange,&dhcpsHashDcpt.dhcpSStartAddress);
		}
		if(pDhcpsConfig->deleteOldLease)
		{	// remove the old entries, if there
			_DHCPSRemoveCacheEntries(&dhcpsHashDcpt);
		}
		
		pServer = &dhcpSDcpt; //+stackCtrl->netIx;
		pServer->uSkt = INVALID_UDP_SOCKET;
		pServer->enabled = false;
		pServer->smServer = DHCP_SERVER_OPEN_SOCKET;
		pServer->dhcpNextLease.Val = 0;
		pServer->netIx = -1;
		// Ip address
		TCPIP_Helper_StringToIPAddress((char*)DHCP_SERVER_IP_ADDRESS,&pServer->intfAddrsConf.serverIPAddress);
		//NET Mask
		TCPIP_Helper_StringToIPAddress((char*)DHCP_SERVER_NETMASK_ADDRESS,&pServer->intfAddrsConf.serverMask);
		// Gateway 
		TCPIP_Helper_StringToIPAddress((char*)DHCP_SERVER_GATEWAY_ADDRESS,&pServer->intfAddrsConf.serverGateway);

#if defined(TCPIP_STACK_USE_DNS)
		// primary DNS server		
		TCPIP_Helper_StringToIPAddress((char*)DHCP_SERVER_PRIMARY_DNS_ADDRESS,&pServer->intfAddrsConf.serverDNS);

		// Secondary DNS server		
		TCPIP_Helper_StringToIPAddress((char*)DHCP_SERVER_SECONDARY_DNS_ADDRESS,&pServer->intfAddrsConf.serverDNS2);
#endif
		pServer->timerHandle = _TCPIPStackAsyncHandlerRegister(TCPIP_DHCPS_TaskForLeaseTime, 0, DHCPS_TASK_PROCESS_RATE);
		if(pServer->timerHandle == 0)
		{
			_DHCPSRemoveCacheEntries(&dhcpsHashDcpt);
			return false;
		}
		
    }

	
	
    if(stackCtrl->pNetIf->Flags.bIsDHCPSrvEnabled != 0)
    {   // override the pDhcpsConfig->dhcpEnable passed with the what the stack manager says
        TCPIP_DHCPS_Enable(stackCtrl->pNetIf);
    }

            
    // Reset state machine and flags to default values

    dhcpSInitCount++;

    return true;
}

/*****************************************************************************
  Function:
    bool TCPIP_DHCPS_Deinitilize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl);

  Summary:
	Turns off the DHCP server module for the specified interface.

  Description:
	Closes out UDP socket.

  Precondition:
	None

  Parameters:
	stackData - pointer to stack structure specifying the interface to deinitialize

  Returns:
	None

  Remarks:
	This function should be called internally just once per interface 
    by the stack manager.
***************************************************************************/
void TCPIP_DHCPS_Deinitilize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    _DHCPSrvClose(stackCtrl->pNetIf,true);
	
    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
    {   // whole stack is going down
    	
        if(dhcpSInitCount > 0)
        {   // we're up and running
        	
            if(--dhcpSInitCount == 0)
            {   // all closed
                // release resources
                _DHCPSDeleteResources();
                _DHCPServerCleanup(stackCtrl->netIx);
                dhcpSMemH = 0;
            }
        }
    }
}


static void _DHCPServerCleanup(int netIx)
{
	if(dhcpsHashDcpt.hashDcpt != NULL)
	{
		TCPIP_HEAP_Free(dhcpSMemH,dhcpsHashDcpt.hashDcpt);
	}
}

static void _DHCPSrvClose(TCPIP_NET_IF* pNetIf, bool disable)
{
    DHCP_SRVR_DCPT *pDhcpsDcpt = &dhcpSDcpt; //+TCPIP_STACK_NetIxGet(pNetIf);
    
    if(pDhcpsDcpt->enabled != 0)
    {
        if(pDhcpsDcpt->uSkt != INVALID_UDP_SOCKET)
        {
            TCPIP_UDP_Close(pDhcpsDcpt->uSkt);
            pDhcpsDcpt->uSkt = INVALID_UDP_SOCKET;
        }        
        if(disable)
        {
            pDhcpsDcpt->enabled = false;
            pNetIf->Flags.bIsDHCPSrvEnabled = false;
        }
        else
        {   // let it active
            pDhcpsDcpt->smServer = DHCP_SERVER_OPEN_SOCKET;
        }
    }
}


/*****************************************************************************
  Function:
	bool TCPIP_DHCPS_Task(TCPIP_NET_IF* pNetIf)

  Summary:
	Performs periodic DHCP server tasks.

  Description:
	This function performs any periodic tasks requied by the DHCP server 
	module, such as processing DHCP requests and distributing IP addresses.

  Precondition:
	None

  Parameters:
	pNetIf   - interface

  Returns:
  	None
  ***************************************************************************/
bool TCPIP_DHCPS_Task(TCPIP_NET_IF* pNetIf)
{
	uint8_t 		i;
	uint8_t			Option, Len;
	BOOTP_HEADER		BOOTPHeader;
	uint32_t		dw;
	bool			bAccept, bRenew;
        int                     netIx;
        UDP_SOCKET              s;
	OA_HASH_ENTRY   	*hE;
	DHCPS_HASH_DCPT  	*pdhcpsHashDcpt;
	DHCP_SRVR_DCPT		*pDhcpsDcpt;
  

	if(pNetIf == 0 || pNetIf->Flags.bInterfaceEnabled == 0)
	{
		return false;
	}
    
#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
	// Make sure we don't clobber anyone else's DHCP server
	if(TCPIP_DHCP_IsServerDetected(pNetIf)|| TCPIP_DHCP_IsEnabled(pNetIf))
	{
            return false;
	}
#endif
    netIx = TCPIP_STACK_NetIxGet(pNetIf);
	
	if(TCPIP_DHCPS_IsEnabled(pNetIf) != true)
	{
            return false;
	}


	pDhcpsDcpt = &dhcpSDcpt; //[netIx];
	pdhcpsHashDcpt = &dhcpsHashDcpt;
    s = pDhcpsDcpt->uSkt;

    
	switch(pDhcpsDcpt->smServer)
	{
            case DHCP_SERVER_OPEN_SOCKET:
                // Obtain a UDP socket to listen/transmit on
                pDhcpsDcpt->uSkt = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, DHCP_SERVER_PORT,  0);
                if(pDhcpsDcpt->uSkt == INVALID_UDP_SOCKET)
                        break;
// Configure the server address, netmask, gateway and DNS addresses				
				
				TCPIP_STACK_NetworkAddressSet(pNetIf, &pDhcpsDcpt->intfAddrsConf.serverIPAddress, &pDhcpsDcpt->intfAddrsConf.serverMask, false);
				TCPIP_STACK_GatewayAddressSet(pNetIf, &pDhcpsDcpt->intfAddrsConf.serverGateway);
#if defined(TCPIP_STACK_USE_DNS)
				if(pNetIf->Flags.bIsDNSServerAuto != 0)
				{
					TCPIP_STACK_PrimaryDNSAddressSet(pNetIf, &pDhcpsDcpt->intfAddrsConf.serverDNS);
					TCPIP_STACK_SecondaryDNSAddressSet(pNetIf, &pDhcpsDcpt->intfAddrsConf.serverDNS2);
				}
#endif

                TCPIP_UDP_SocketNetSet(pDhcpsDcpt->uSkt, pNetIf);
                s = pDhcpsDcpt->uSkt;
				pDhcpsDcpt->netIx = netIx;
				pDhcpsDcpt->enabled = true;
                pDhcpsDcpt->smServer++;

            case DHCP_SERVER_LISTEN:
                // Check to see if a valid DHCP packet has arrived
                if(TCPIP_UDP_GetIsReady(s) < 241u)
                        break;
                // Retrieve the BOOTP header
                TCPIP_UDP_ArrayGet(s, (uint8_t*)&BOOTPHeader, sizeof(BOOTPHeader));
                hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &BOOTPHeader.ClientMAC);
                if(hE != 0)
                {
                    if(TCPIP_DHCPS_HashIPKeyCompare(pdhcpsHashDcpt->hashDcpt,hE,&BOOTPHeader.ClientIP.Val) == 0)
                    {
                        bRenew= true;
                        bAccept = true;
                    }
                    else
                    {
                        bRenew = false;
                        bAccept = false;
                    }
                }
                else if(BOOTPHeader.ClientIP.Val == 0x00000000u)
                {
                    bRenew = false;
                    bAccept = true;
                }
                else
                {
                    bRenew = false;
                    bAccept = false;
                }

                // Validate first three fields
                if(BOOTPHeader.MessageType != 1u)
                    break;
                if(BOOTPHeader.HardwareType != 1u)
                    break;
                if(BOOTPHeader.HardwareLen != 6u)
                    break;

                // Throw away 10 unused bytes of hardware address,
                // server host name, and boot file name -- unsupported/not needed.
                for(i = 0; i < DHCPS_UNUSED_BYTES_FOR_TX; i++)
                {
                    TCPIP_UDP_Get(s, &Option);
                }

                // Obtain Magic Cookie and verify DHCP
                TCPIP_UDP_ArrayGet(s, (uint8_t*)&dw, sizeof(uint32_t));
                if(dw != 0x63538263ul)
                    break;

                // Obtain options
                while(1)
                {
                    // Get option type
                    if(!TCPIP_UDP_Get(s, &Option))
                            break;
                    if(Option == DHCP_END_OPTION)
                            break;

                    // Get option length
                    TCPIP_UDP_Get(s, &Len);

                    // Process option
                    switch(Option)
                    {
                        case DHCP_MESSAGE_TYPE:
                            TCPIP_UDP_Get(s, &i);
                            switch(i)
                            {
                                case DHCP_DISCOVER_MESSAGE:
                                    DHCPReplyToDiscovery(&BOOTPHeader,pDhcpsDcpt,pdhcpsHashDcpt);
                                    break;

                                case DHCP_REQUEST_MESSAGE:
                                      DHCPReplyToRequest(&BOOTPHeader, bAccept, netIx, bRenew,pDhcpsDcpt,pdhcpsHashDcpt);

                                        break;
                                        /*
                                        Release the leased address from the hash table by checking
                                        BOOTPHeader.ClientMAC and BOOTPHeader.ClientIP.Val.
                                        */
                                // Need to handle these if supporting more than one DHCP lease
                                case DHCP_RELEASE_MESSAGE:
                                case DHCP_DECLINE_MESSAGE:
									DHCPSRemoveHashEntry(&BOOTPHeader.ClientMAC,&BOOTPHeader.ClientIP);
                                    break;
                                case DHCP_INFORM_MESSAGE:
                                    DHCPSReplyToInform(&BOOTPHeader,pDhcpsDcpt,pdhcpsHashDcpt,bAccept);
                                    break;
                            }
                            break;

                        case DHCP_PARAM_REQUEST_IP_ADDRESS:
                            break;

                        case DHCP_END_OPTION:
                            TCPIP_UDP_Discard(s);
                            return true;
                    }

                    // Remove any unprocessed bytes that we don't care about
                    while(Len--)
                    {
                            TCPIP_UDP_Get(s, &i);
                    }
                }

                TCPIP_UDP_Discard(s);
                break;
	}

	return true;
}


/****************************************************************************
  Function:
	bool TCPIP_DHCPS_DataCopyToProcessBuffer(uint8_t val ,DHCPSERVERDATA *putbuf)
	
  Summary:
  	Copies uint8_t data to dynamically allocated memory buffer.

  Description:
	The DHCP Server OFFER and RESPONSE  and INFORM packet  uses dynamically allocated memory buffer for
	processing . This routine copies the uint8_t data to the allocated buffer and updates the offset length couter. 
		  	 		 		  	
  Precondition:
	The DHCP Server has sucessfully allocated dynamic memory buffer from the Heap
   	
  Parameters:
  	val: uint8_t value to be written to the buffer
  	putbuf: pointer to the dynamically allocated buffer to which the 'val' to be written 
  	
  Return Values:
	true: if successfully write to the buffer
	false: failure in writing to the buffer
	
  Remarks:
  	This routine is used by the DHCP Server stack. If required to be used by the application
  	code, valid pointers should be passed to this routine. 
  	
***************************************************************************/
static bool TCPIP_DHCPS_DataCopyToProcessBuffer(uint8_t val ,DHCPSERVERDATA *putbuf)
{
	if(putbuf->length < putbuf->maxlength)
	{
		putbuf->head[putbuf->length] = (uint8_t)val;
		putbuf->length++;
		return true;
	}

	return false;
}

static bool DHCPSCopyDataArrayToProcessBuff(uint8_t *val ,DHCPSERVERDATA *putbuf,int len)
{
	uint8_t pos=0;

	for(pos = 0;pos<len;pos++)
	{
		if(putbuf->length < putbuf->maxlength)
		{
			putbuf->head[putbuf->length] = (uint8_t)(*(val+pos));
			putbuf->length++;			
		}
		else
		{
			return false;
		}
	}
	
	return true;

}


/*****************************************************************************
  Function:
	static void DHCPReplyToDiscovery(BOOTP_HEADER *Header,DHCP_SRVR_DCPT * pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt )

  Summary:
	Replies to a DHCP Discover message.

  Description:
	This function replies to a DHCP Discover message by sending out a 
	DHCP Offer message.

  Precondition:
	None

  Parameters:
	Header - the BootP header this is in response to.
    netIx   - interface index

  Returns:
  	None
  ***************************************************************************/
static void DHCPReplyToDiscovery(BOOTP_HEADER *Header,DHCP_SRVR_DCPT * pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt )
{
	uint8_t         i;
    TCPIP_NET_IF*     pNetIf;
	DHCPS_RESULT	res;
    UDP_SOCKET      s;
	OA_HASH_ENTRY   *hE;
	DHCPSERVERDATA   putBuffer;
	DHCPS_HASH_ENTRY *dhcpsHE = 0;

	// Set the correct socket to active and ensure that 
	// enough space is available to generate the DHCP response
    s = pDhcpsDcpt->uSkt;
    if(TCPIP_UDP_TxPutIsReady(s, 300) < 300u)
		return;

    pNetIf = (TCPIP_NET_IF*)TCPIP_UDP_SocketNetGet(s);
	pDhcpsDcpt->dhcpNextLease.Val = 0;

	// Search through all remaining options and look for the Requested IP address field
	// Obtain options
	while(TCPIP_UDP_GetIsReady(s))
	{
		uint8_t Option, Len;
		uint32_t dw;

		// Get option type
		if(!TCPIP_UDP_Get(s, &Option))
			break;
		if(Option == DHCP_END_OPTION)
			break;

		// Get option length
		TCPIP_UDP_Get(s, &Len);
		switch(Option)
		{
			case DHCP_PARAM_REQUEST_IP_ADDRESS:
				{
					TCPIP_UDP_ArrayGet(s, (uint8_t*)&dw, 4);
					if(Len != 4)
					{
						break;
					}
					hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &Header->ClientMAC);
					if(hE != 0)
					{	//found entry and this MAC is already in use					
						return;
					}
					/* Validating if the requested IP address should not be part of any Hash Entry */
					if(DHCPSLocateRequestedIpAddress((IPV4_ADDR *)&dw) == DHCPS_RES_OK)
					{
						// use the alternate address
						pDhcpsDcpt->dhcpNextLease.Val = 0;
					}
					else
					{
					// the requested address should be in the same address block.
						if((pNetIf->netIPAddr.Val & 0x00ffffff) == (dw & 0x00ffffff))
						{
							// use the requested Ip address
							pDhcpsDcpt->dhcpNextLease.Val = dw;
						}
						else
						{
							pDhcpsDcpt->dhcpNextLease.Val = 0;
						}
					}
				}
				break;
		}
		
	}

	// find in pool
	res = preAssignToDHCPClient(Header,pDhcpsDcpt,pdhcpsHashDcpt);
	if( res != DHCPS_RES_OK) return;


// Before sending OFFER, get the perfect Hash Entry
	
	hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &Header->ClientMAC);
	if(hE != 0)
	{
		dhcpsHE = ( DHCPS_HASH_ENTRY *) hE;
	}

	putBuffer.head = (uint8_t *)(TCPIP_HEAP_Calloc(dhcpSMemH,1,DHCPS_MAX_REPONSE_PACKET_SIZE+1));
	if(putBuffer.head == 0)
	{
		return;
	}
	
	putBuffer.length = 0;
	putBuffer.maxlength = DHCPS_MAX_REPONSE_PACKET_SIZE;
	
	// Begin putting the BOOTP Header and DHCP options
	TCPIP_DHCPS_DataCopyToProcessBuffer(BOOT_REPLY,&putBuffer);
	// Reply with the same Hardware Type, Hardware Address Length, Hops, and Transaction ID fields
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(Header->HardwareType),&putBuffer,7);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Seconds Elapsed: 0 (Not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Seconds Elapsed: 0 (Not used)

	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(Header->BootpFlags),&putBuffer,sizeof(Header->BootpFlags));
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Your (client) IP Address: 0.0.0.0 (none yet assigned)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Your (client) IP Address: 0.0.0.0 (none yet assigned)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Your (client) IP Address: 0.0.0.0 (none yet assigned)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Your (client) IP Address: 0.0.0.0 (none yet assigned)
	
	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(dhcpsHE->ipAddress),&putBuffer,sizeof(IPV4_ADDR));
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);   // Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)

	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(Header->ClientMAC),&putBuffer,sizeof(TCPIP_MAC_ADDR));
	for(i = 0; i < DHCPS_UNUSED_BYTES_FOR_TX; i++)	// Remaining 10 bytes of client hardware address, server host name: Null string (not used)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);
	}
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(0X63,&putBuffer); // Magic Cookie: 0x63538263 
	TCPIP_DHCPS_DataCopyToProcessBuffer(0X82,&putBuffer); 
	TCPIP_DHCPS_DataCopyToProcessBuffer(0X53,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0X63,&putBuffer);

	// Options: DHCP Offer
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_MESSAGE_TYPE,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(1,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_OFFER_MESSAGE,&putBuffer);

	// Option: Subnet Mask
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SUBNET_MASK,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netMask,&putBuffer,sizeof(IPV4_ADDR));

	// Option: Lease duration
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_IP_LEASE_TIME,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(4,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>24) & 0xFF,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>16) & 0xFF,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>8) & 0xFF,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion) & 0xFF,&putBuffer);

	// Option: Server identifier
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SERVER_IDENTIFIER,&putBuffer);	
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// Option: Router/Gateway address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_ROUTER,&putBuffer);	
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// Option: DNS server address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_DNS,&putBuffer);	
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// No more options, mark ending
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_END_OPTION,&putBuffer);	

	// Add zero padding to ensure compatibility with old BOOTP relays that discard small packets (<300 UDP octets)
	while(putBuffer.length < putBuffer.maxlength)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer); 
	}

	
	// Put complete DHCP packet buffer to the UDP buffer
	TCPIP_UDP_ArrayPut(s, putBuffer.head, putBuffer.length);
	TCPIP_HEAP_Free(dhcpSMemH,putBuffer.head);
	
	// Force remote destination address to be the broadcast address, regardless 
	// of what the node's source IP address was (to ensure we don't try to 
	// unicast to 0.0.0.0).
	TCPIP_UDP_BcastIPV4AddressSet( s,UDP_BCAST_NETWORK_LIMITED,pNetIf);
	//TCPIP_UDP_SourceIPAddressSet(s,IP_ADDRESS_TYPE_IPV4,&(pNetIf->netIPAddr));
	IP_MULTI_ADDRESS tmp_MultiAddr; tmp_MultiAddr.v4Add = pNetIf->netIPAddr;
	TCPIP_UDP_SourceIPAddressSet(s,IP_ADDRESS_TYPE_IPV4,&tmp_MultiAddr);

	// Transmit the packet
	TCPIP_UDP_Flush(s);
}


/*****************************************************************************
  Function:
	static void DHCPSReplyToInform(BOOTP_HEADER *boot_header, DHCP_SRVR_DCPT* pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt,bool bAccept, )

  Summary:
	Replies to a DHCP Inform message.

  Description:
	This function replies to a DHCP Inform message by sending out a 
	DHCP Acknowledge message.

  Precondition:
	None

  Parameters:
	Header - the BootP header this is in response to.
	bAccept - whether or not we've accepted this request
    netIx   - interface index

  Returns:
  	None
  
  Internal:
	Needs to support more than one simultaneous lease in the future.
  ***************************************************************************/
static void DHCPSReplyToInform(BOOTP_HEADER *boot_header, DHCP_SRVR_DCPT* pDhcpsDcpt,
										DHCPS_HASH_DCPT *pdhcpsHashDcpt,bool bAccept)
{
	uint8_t         i;
    TCPIP_NET_IF*     pNetIf;
    UDP_SOCKET      s;
  	IPV4_ADDR       ipAddr;	
	OA_HASH_ENTRY   	*hE;
	DHCPS_HASH_ENTRY * dhcpsHE;
	DHCPSERVERDATA   putBuffer;
	
	// Set the correct socket to active and ensure that 
	// enough space is available to generate the DHCP response
    s = pDhcpsDcpt->uSkt;
    if(TCPIP_UDP_TxPutIsReady(s, 300) < 300u)
		return;
    
    pNetIf = (TCPIP_NET_IF*)TCPIP_UDP_SocketNetGet(s);

	// Search through all remaining options and look for the Requested IP address field
	// Obtain options
	while(TCPIP_UDP_GetIsReady(s))
	{
		uint8_t Option, Len;
		TCPIP_MAC_ADDR tmp_MacAddr;

		// Get option type
		if(!TCPIP_UDP_Get(s, &Option))
			break;
		if(Option == DHCP_END_OPTION)
			break;

		// Get option length
		TCPIP_UDP_Get(s, &Len);

		if((Option == DHCP_PARAM_REQUEST_CLIENT_ID) && (Len == 7u))
		{
			// Get the requested IP address and see if it is the one we have on offer.	If not, we should send back a NAK, but since there could be some other DHCP server offering this address, we'll just silently ignore this request.
			TCPIP_UDP_Get(s, &i);
			TCPIP_UDP_ArrayGet(s, (uint8_t*)&tmp_MacAddr, 6);
			Len -= 7;
			hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &tmp_MacAddr);
			if(hE !=0)
			{
				if(TCPIP_DHCPS_HashIPKeyCompare(pdhcpsHashDcpt->hashDcpt,hE,&boot_header->ClientIP.Val) == 0)
				{
					dhcpsHE = (DHCPS_HASH_ENTRY *)hE;
				}
				else
					bAccept = false;
			}
			else
			{
				bAccept = false;
			}
			
			break;
		}
		
		// Remove the unprocessed bytes that we don't care about
		while(Len--)
		{
			TCPIP_UDP_Get(s, &i);
		}
	}

	putBuffer.head = (uint8_t *)(TCPIP_HEAP_Calloc(dhcpSMemH,1,DHCPS_MAX_REPONSE_PACKET_SIZE+1));
	if(putBuffer.head == 0)
	{
		return;
	}
	
	putBuffer.length = 0;
	putBuffer.maxlength = DHCPS_MAX_REPONSE_PACKET_SIZE;

	
	// Begin putting the BOOTP Header and DHCP options
	TCPIP_DHCPS_DataCopyToProcessBuffer(BOOT_REPLY,&putBuffer); // Message Type: 2 (BOOTP Reply)
	// Reply with the same Hardware Type, Hardware Address Length, Hops, and Transaction ID fields
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->HardwareType),&putBuffer,7);
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer); // Seconds Elapsed: 0 (Not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer); // Seconds Elapsed: 0 (Not used)
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->BootpFlags),&putBuffer,sizeof(boot_header->BootpFlags));
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->ClientIP),&putBuffer,sizeof(IPV4_ADDR)); // Your (client) IP Address:

	ipAddr.Val=0u;
	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&ipAddr,&putBuffer,sizeof(IPV4_ADDR));
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);   // Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->ClientMAC),&putBuffer,sizeof(TCPIP_MAC_ADDR)); // Client MAC address: Same as given by client
	
	for(i = 0; i < DHCPS_UNUSED_BYTES_FOR_TX; i++)	// Remaining 10 bytes of client hardware address, server host name: Null string (not used)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer); // Boot filename: Null string (not used)
	}

	TCPIP_DHCPS_DataCopyToProcessBuffer(0x63,&putBuffer); // Magic Cookie: 0x63538263
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x82,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x53,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x63,&putBuffer);

	// Options: DHCP lease ACKnowledge
	if(bAccept)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_OPTION_ACK_MESSAGE,&putBuffer);
		TCPIP_DHCPS_DataCopyToProcessBuffer(1,&putBuffer);
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_ACK_MESSAGE,&putBuffer);
	}

	// Option: Server identifier
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SERVER_IDENTIFIER,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// Option: Subnet Mask	
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SUBNET_MASK,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netMask,&putBuffer,sizeof(IPV4_ADDR));

	// Option: Router/Gateway address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_ROUTER,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// Option: DNS server address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_DNS,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR));

	// No more options, mark ending
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_END_OPTION,&putBuffer);

	// Add zero padding to ensure compatibility with old BOOTP relays that discard small packets (<300 UDP octets)
	while(putBuffer.length < putBuffer.maxlength)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);
	}
	// Put complete DHCP packet buffer to the UDP buffer
	TCPIP_UDP_ArrayPut(s, putBuffer.head, putBuffer.length);
	TCPIP_HEAP_Free(dhcpSMemH,putBuffer.head);

	IP_MULTI_ADDRESS tmp_MultiAddr; tmp_MultiAddr.v4Add = pNetIf->netIPAddr;
	TCPIP_UDP_SourceIPAddressSet(s,IP_ADDRESS_TYPE_IPV4,&tmp_MultiAddr);
	// Transmit the packet
	TCPIP_UDP_Flush(s);
}


/*****************************************************************************
  Function:
	static void DHCPReplyToRequest(BOOTP_HEADER *Header, bool bAccept, int netIx, bool bRenew)

  Summary:
	Replies to a DHCP Request message.

  Description:
	This function replies to a DHCP Request message by sending out a 
	DHCP Acknowledge message.

  Precondition:
	None

  Parameters:
	Header - the BootP header this is in response to.
	bAccept - whether or not we've accepted this request
    netIx   - interface index

  Returns:
  	None
  
  Internal:
	Needs to support more than one simultaneous lease in the future.
  ***************************************************************************/
static void DHCPReplyToRequest(BOOTP_HEADER *boot_header, bool bAccept, int netIx, bool bRenew,
														DHCP_SRVR_DCPT* pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt )
{
	uint8_t         i;
    TCPIP_NET_IF*     pNetIf;
    UDP_SOCKET      s;
  	IPV4_ADDR       ipAddr;	
	DHCPSERVERDATA   putBuffer;
	OA_HASH_ENTRY   *hE = 0;
	
	// Set the correct socket to active and ensure that 
	// enough space is available to generate the DHCP response
    s = pDhcpsDcpt->uSkt;
    if(TCPIP_UDP_TxPutIsReady(s, 300) < 300u)
		return;
    
    pNetIf = (TCPIP_NET_IF*)TCPIP_UDP_SocketNetGet(s);

	// Search through all remaining options and look for the Requested IP address field
	// Obtain options
	while(TCPIP_UDP_GetIsReady(s))
	{
		uint8_t Option, Len;
		uint32_t dw;
		TCPIP_MAC_ADDR tmp_MacAddr;

		// Get option type
		if(!TCPIP_UDP_Get(s, &Option))
			break;
		if(Option == DHCP_END_OPTION)
			break;

		// Get option length
		TCPIP_UDP_Get(s, &Len);

		
		// Process option
		if(bRenew)
		{
			if((Option == DHCP_PARAM_REQUEST_CLIENT_ID) && (Len == 7u))
			{
				// Get the requested IP address and see if it is the one we have on offer.  If not, we should send back a NAK, but since there could be some other DHCP server offering this address, we'll just silently ignore this request.
				TCPIP_UDP_Get(s, &i);
				TCPIP_UDP_ArrayGet(s, (uint8_t*)&tmp_MacAddr, 6);
				Len -= 7;
                hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &tmp_MacAddr);
				if(hE !=0)
				{
					if(TCPIP_DHCPS_HashIPKeyCompare(pdhcpsHashDcpt->hashDcpt,hE,&boot_header->ClientIP.Val) == 0)
					{
						DHCPS_HASH_ENTRY * dhcpsHE = (DHCPS_HASH_ENTRY *)hE;
						// update lease time;
						_DHCPSUpdateEntry(dhcpsHE);
					}
					else
					{
						TCPIP_OAHASH_EntryRemove(pdhcpsHashDcpt->hashDcpt,hE);
						bAccept = false;
					}
				}
				else
				{
					bAccept = false;
				}
				
				break;
			}
		}
		else
		{
			if((Option == DHCP_PARAM_REQUEST_IP_ADDRESS) && (Len == 4u))
			{
				// Get the requested IP address and see if it is the one we have on offer.  If not, we should send back a NAK, but since there could be some other DHCP server offering this address, we'll just silently ignore this request.
				TCPIP_UDP_ArrayGet(s, (uint8_t*)&dw, 4);
				Len -= 4;
                hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &boot_header->ClientMAC);
				if(hE != 0)
				{
					
					if(TCPIP_DHCPS_HashIPKeyCompare(pdhcpsHashDcpt->hashDcpt,hE,&dw) == 0)
					{
						DHCPS_HASH_ENTRY * dhcpsHE = (DHCPS_HASH_ENTRY *)hE;
						bAccept = true;
						_DHCPSUpdateEntry(dhcpsHE);
					}
					else
					{
						bAccept = false;
						//remove Hash entry;
						TCPIP_OAHASH_EntryRemove(pdhcpsHashDcpt->hashDcpt,hE);
					}
				}
				break;
			}
		}
		// Remove the unprocessed bytes that we don't care about
		while(Len--)
		{
			TCPIP_UDP_Get(s, &i);
		}
	}

	putBuffer.head = (uint8_t *)(TCPIP_HEAP_Calloc(dhcpSMemH,1,DHCPS_MAX_REPONSE_PACKET_SIZE+1));
	if(putBuffer.head == 0)
	{
		return;
	}
	
	putBuffer.length = 0;
	putBuffer.maxlength = DHCPS_MAX_REPONSE_PACKET_SIZE;

	// Begin putting the BOOTP Header and DHCP options
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(BOOT_REPLY,&putBuffer);  // Message Type: 2 (BOOTP Reply)
	// Reply with the same Hardware Type, Hardware Address Length, Hops, and Transaction ID fields	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->HardwareType),&putBuffer,7);
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);  // Message Type: 2 (BOOTP Reply)	
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);  // Message Type: 2 (BOOTP Reply)
	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->BootpFlags),&putBuffer,sizeof(boot_header->BootpFlags));	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->ClientIP),&putBuffer, sizeof(IPV4_ADDR)); // Your (client) IP Address:
	if(bAccept)		
	{
		if(hE != 0)
		{
			ipAddr = ((DHCPS_HASH_ENTRY*)hE)->ipAddress;
		}
		else
		{
			bAccept =  false;
			ipAddr.Val = 0;
		}		
	}
	else 		
	{
		ipAddr.Val=0u;
	}
	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&ipAddr,&putBuffer,sizeof(IPV4_ADDR)); // Lease IP address to give out
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);   // Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Next Server IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)
	TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);	// Relay Agent IP Address: 0.0.0.0 (not used)

	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&(boot_header->ClientMAC),&putBuffer,sizeof(TCPIP_MAC_ADDR)); // Client MAC address: Same as given by client
	for(i = 0; i < DHCPS_UNUSED_BYTES_FOR_TX; i++)	// Remaining 10 bytes of client hardware address, server host name: Null string (not used)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer); // Boot filename: Null string (not used)
	}

	TCPIP_DHCPS_DataCopyToProcessBuffer(0x63,&putBuffer); // Magic Cookie: 0x63538263
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x82,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x53,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(0x63,&putBuffer);

	// Options: DHCP lease ACKnowledge
	if(bAccept)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_OPTION_ACK_MESSAGE,&putBuffer);
		TCPIP_DHCPS_DataCopyToProcessBuffer(1,&putBuffer);		
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_ACK_MESSAGE,&putBuffer);
	}
	else	// Send a NACK
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_OPTION_ACK_MESSAGE,&putBuffer);
		TCPIP_DHCPS_DataCopyToProcessBuffer(1,&putBuffer);		
		TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_NAK_MESSAGE,&putBuffer);
	}

	// Option: Lease duration	
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_IP_LEASE_TIME,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(4,&putBuffer);		
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>24) & 0xFF,&putBuffer);	
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>16) & 0xFF,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion>>8) & 0xFF,&putBuffer);		
	TCPIP_DHCPS_DataCopyToProcessBuffer((pdhcpsHashDcpt->leaseDuartion) & 0xFF,&putBuffer);

	// Option: Server identifier
	
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SERVER_IDENTIFIER,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR)); 

	// Option: Subnet Mask
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_SUBNET_MASK,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netMask,&putBuffer,sizeof(IPV4_ADDR)); 

	// Option: Router/Gateway address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_ROUTER,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR)); 

	// Option: DNS server address
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_DNS,&putBuffer);
	TCPIP_DHCPS_DataCopyToProcessBuffer(sizeof(IPV4_ADDR),&putBuffer);	
	DHCPSCopyDataArrayToProcessBuff((uint8_t*)&pNetIf->netIPAddr,&putBuffer,sizeof(IPV4_ADDR)); 

	// No more options, mark ending
	TCPIP_DHCPS_DataCopyToProcessBuffer(DHCP_END_OPTION,&putBuffer);

	// Add zero padding to ensure compatibility with old BOOTP relays that discard small packets (<300 UDP octets)
	while(putBuffer.length < putBuffer.maxlength)
	{
		TCPIP_DHCPS_DataCopyToProcessBuffer(0,&putBuffer);
	}
	
	// Put complete DHCP packet buffer to the UDP buffer
	TCPIP_UDP_ArrayPut(s, putBuffer.head, putBuffer.length);
	TCPIP_HEAP_Free(dhcpSMemH,putBuffer.head);

	// Force remote destination address to be the broadcast address, regardless 
	// of what the node's source IP address was (to ensure we don't try to 
	// unicast to 0.0.0.0).
	if(false == bRenew)
		TCPIP_UDP_BcastIPV4AddressSet( s,UDP_BCAST_NETWORK_LIMITED,pNetIf);

	IP_MULTI_ADDRESS tmp_MultiAddr; tmp_MultiAddr.v4Add = pNetIf->netIPAddr;
	TCPIP_UDP_SourceIPAddressSet(s,IP_ADDRESS_TYPE_IPV4,&tmp_MultiAddr);
	// Transmit the packet
	TCPIP_UDP_Flush(s);
}

static bool isMacAddrEffective(const TCPIP_MAC_ADDR *macAddr)
{
	int i;
	for(i=0;i<6;i++)
	{
		if(macAddr->v[i] != 0) return true;
	}
	return false;
}

/*****************************************************************************
  Function:
    static bool _DHCPSAddCompleteEntry(int intfIdx,IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd,DHCPS_ENTRY_FLAGS entryFlag)

  Description:
    Updates the info for an existing ARP cache entry

  Precondition:
    None

  Parameters:
    intfIdx             - network interface index
    arpHE           - particular cache entry to be updated
    hwAdd           - the (new) hardware address
	entryFlag    -  Entry Flag
  Return Values:
    ARP_RES_CACHE_FULL  - cache full error
    ARP_RES_OK          - success
  ***************************************************************************/
static bool _DHCPSAddCompleteEntry(int intfIdx,IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd,DHCPS_ENTRY_FLAGS entryFlag)
{
    DHCPS_HASH_DCPT  *pdhcpsDcpt;
    OA_HASH_ENTRY   *hE;
	DHCPS_HASH_ENTRY* dhcpsHE;

    pdhcpsDcpt = &dhcpsHashDcpt;
    
    hE = TCPIP_OAHASH_EntryLookupOrInsert(pdhcpsDcpt->hashDcpt, hwAdd);
    if(hE == 0)
    {   // oops, hash full?
        return DHCPS_RES_CACHE_FULL;
    }

    // now in cache
    dhcpsHE = (DHCPS_HASH_ENTRY*)hE;
    if(dhcpsHE->hEntry.flags.newEntry != 0)
    {   // populate the new entry
    	dhcpsHE->intfIdx = intfIdx;
        _DHCPSSetHashEntry(dhcpsHE, entryFlag, hwAdd,pIPAddr);
    }
    else
    {   // existent entry
        _DHCPSUpdateEntry(dhcpsHE);
    }

    return DHCPS_RES_OK;
}


void TCPIP_DHCPS_TaskForLeaseTime(void)
{
	SYS_TICK current_timer = SYS_TICK_Get();	
	DHCPS_HASH_ENTRY* dhcpsHE;
	DHCPS_HASH_DCPT  *pdhcpsDcpt;
	OA_HASH_ENTRY	*hE;
	int 			bktIx=0;
	OA_HASH_DCPT	*pOH;
	DHCP_SRVR_DCPT*	pServer;
	TCPIP_NET_IF* pNetIf;

	pdhcpsDcpt = &dhcpsHashDcpt;
	pOH = pdhcpsDcpt->hashDcpt;
	pServer =  &dhcpSDcpt;

	pNetIf = (TCPIP_NET_IF*)TCPIP_UDP_SocketNetGet(pServer->uSkt);

// check the lease values and if there is any entry whose lease value exceeds the lease duration remove the lease entries from the HASH.

    for(bktIx = 0; bktIx < pOH->hEntries; bktIx++)
    {
		hE = TCPIP_OAHASH_EntryGet(pOH, bktIx);
    	if((hE->flags.busy != 0) && (hE->flags.value & DHCPS_FLAG_ENTRY_COMPLETE))
    	{
    		dhcpsHE = (DHCPS_HASH_ENTRY*)hE;
			if((current_timer - dhcpsHE->Client_Lease_Time) >= pdhcpsDcpt->leaseDuartion* SYS_TICK_TicksPerSecondGet())
			{
				dhcpsHE->Client_Lease_Time = 0;
				TCPIP_OAHASH_EntryRemove(pOH,hE);
			}
    	}
    }
	
// Check if there is any entry whose DHCPS flag is INCOMPLETE, i,e DHCPS server did not receive the request from the client regarding that leased address.
    for(bktIx = 0; bktIx < pOH->hEntries; bktIx++)
    {
		hE = TCPIP_OAHASH_EntryGet(pOH, bktIx);
    	if((hE->flags.busy != 0) && (hE->flags.value & DHCPS_FLAG_ENTRY_INCOMPLETE))
    	{
    		dhcpsHE = (DHCPS_HASH_ENTRY*)hE;
			if((current_timer - dhcpsHE->pendingTime) >= DHCPS_LEASE_REMOVED_BEFORE_ACK* SYS_TICK_TicksPerSecondGet())
			{
				dhcpsHE->pendingTime = 0;
				TCPIP_OAHASH_EntryRemove(pOH,hE);
			}
    	}
    }
}


static DHCPS_RESULT preAssignToDHCPClient(BOOTP_HEADER *Header,DHCP_SRVR_DCPT * pDhcpsDcpt,DHCPS_HASH_DCPT *pdhcpsHashDcpt)
{
    //TCPIP_NET_IF*     pNetIf;
    OA_HASH_ENTRY   	*hE;
	IPV4_ADDR		  tempIpv4Addr;
	size_t bktIx = 0;
	
	// if MAC==00:00:00:00:00:00, then return -1
	if(false == isMacAddrEffective(&(Header->ClientMAC))) return -1;

		
	// Find in Pool, look for the same MAC addr
	hE = TCPIP_OAHASH_EntryLookup(pdhcpsHashDcpt->hashDcpt, &Header->ClientMAC);
	if(hE !=0)
	{
		return DHCPS_RES_ENTRY_EXIST;
	}
	else
	{
		if(pDhcpsDcpt->dhcpNextLease.Val == 0)
		{
			bktIx = DHCPSgetFreeHashIndex(pdhcpsHashDcpt->hashDcpt, &Header->ClientMAC);
		    if(bktIx == -1)
		    {
				return DHCPS_RES_CACHE_FULL;
		    }
			tempIpv4Addr.v[0] = pdhcpsHashDcpt->dhcpSStartAddress.v[0] & 0xFF;
			tempIpv4Addr.v[1] = pdhcpsHashDcpt->dhcpSStartAddress.v[1] & 0xFF;
			tempIpv4Addr.v[2] = pdhcpsHashDcpt->dhcpSStartAddress.v[2] & 0xFF;
			tempIpv4Addr.v[3] = (pdhcpsHashDcpt->dhcpSStartAddress.v[3] & 0xFF) + bktIx;
		}
		else
		{
			tempIpv4Addr.Val = pDhcpsDcpt->dhcpNextLease.Val;
		}
		/* enter a this decided entry to the HASH POOL with a DHCPS_FLAG_ENTRY_INCOMPLETE flag
		After receiving Request and before sending ACK , make this entry to DHCPS_FLAG_ENTRY_COMPLETE
		*/
		if(_DHCPSAddCompleteEntry(pDhcpsDcpt->netIx,&tempIpv4Addr,&Header->ClientMAC,DHCPS_FLAG_ENTRY_INCOMPLETE)!= DHCPS_RES_OK)
			return DHCPS_RES_CACHE_FULL;
		
	}

	return DHCPS_RES_OK;
	
}


int TCPIP_DHCPS_HashMACKeyCompare(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* hEntry, void* key)
{
	return memcmp((void*)&((DHCPS_HASH_ENTRY*)hEntry)->hwAdd, key, DHCPS_HASH_KEY_SIZE);
}
int TCPIP_DHCPS_HashIPKeyCompare(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* hEntry, void* key)
{
    return ((DHCPS_HASH_ENTRY*)hEntry)->ipAddress.Val != ((DHCPS_UNALIGNED_KEY*)key)->v;
}

void TCPIP_DHCPS_HashIPKeyCopy(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* dstEntry, void* key)
{
    ((DHCPS_HASH_ENTRY*)dstEntry)->ipAddress.Val = ((DHCPS_UNALIGNED_KEY*)key)->v;
}

void TCPIP_DHCPS_HashMACKeyCopy(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* dstEntry, void* key)
{
 	memcpy(&(((DHCPS_HASH_ENTRY*)dstEntry)->hwAdd), key, DHCPS_HASH_KEY_SIZE);
}

OA_HASH_ENTRY* TCPIP_DHCPS_HashDeleteEntry(OA_HASH_DCPT* pOH)
{
    OA_HASH_ENTRY*  pBkt;
    size_t      bktIx;
    DHCPS_HASH_ENTRY  *pE;
	uint32_t current_timer = SYS_TICK_Get();
    
    for(bktIx = 0; bktIx < pOH->hEntries; bktIx++)
    {
        pBkt = TCPIP_OAHASH_EntryGet(pOH, bktIx);		
		if(pBkt->flags.busy != 0)
		{
			pE = (DHCPS_HASH_ENTRY*)pBkt;
			if((current_timer - pE->Client_Lease_Time) >= DHCPS_LEASE_DURATION* SYS_TICK_TicksPerSecondGet())
			{
				return pBkt;
			}
		}
    }
	return 0;
}

static size_t DHCPSgetFreeHashIndex(OA_HASH_DCPT* pOH,void* key)
{
    OA_HASH_ENTRY*  pBkt;
    size_t      bktIx=-1;
    size_t      probeStep=0;
    size_t      bkts = 0;

	
#if defined(OA_DOUBLE_HASH_PROBING)
	probeStep = TCPIP_DHCPS_HashProbeHash(pOH, key);
	if(probeStep == 0)
	{	// try to avoid probing the same bucket over and over again
		// when probeHash returns 0.
		probeStep = pOH->probeStep;
	}
#else
	probeStep = pOH->probeStep;
#endif  // defined(OA_DOUBLE_HASH_PROBING)
	
	bktIx = TCPIP_DHCPS_MACHashKeyHash(pOH,key);
	
	if(bktIx < 0)
	{
		bktIx += pOH->hEntries;
	}
		
	while(bkts < pOH->hEntries)
	{
        pBkt = TCPIP_OAHASH_EntryGet(pOH, bktIx);
		if(pBkt->flags.busy == 0)
		{	// found unused entry			
			return bktIx;
		}
		// advance to the next hash slot
		bktIx += probeStep;
		if(bktIx < 0)
		{
			bktIx += pOH->hEntries;
		}
		else if(bktIx >= pOH->hEntries)
		{
			bktIx -= pOH->hEntries;
		}

		bkts++;
	}
		
	return -1;	// cache full, not found
}

static DHCPS_RESULT DHCPSLocateRequestedIpAddress(IPV4_ADDR *requestedIpAddr)
{
	DHCPS_HASH_DCPT *pdhcpsDcpt;
	OA_HASH_ENTRY	*hE;
	int 			bktIx=0;
	OA_HASH_DCPT	*pOH;
	
	pdhcpsDcpt = &dhcpsHashDcpt;
	pOH = pdhcpsDcpt->hashDcpt;

// check the Requested Ip address is matching anyone of the hash entry.
	for(bktIx = 0; bktIx < pOH->hEntries; bktIx++)
	{
        hE = TCPIP_OAHASH_EntryGet(pOH, bktIx);
		if((hE->flags.busy != 0) && (hE->flags.value & DHCPS_FLAG_ENTRY_COMPLETE))
		{
			if(TCPIP_DHCPS_HashIPKeyCompare(pOH,hE,requestedIpAddr) == 0)
				return DHCPS_RES_OK;
		}
	}
	return DHCPS_RES_NO_ENTRY;
}

DHCPS_LEASE_HANDLE TCPIP_DHCPS_LeaseEntryGet(TCPIP_NET_HANDLE netH, DHCPS_LEASE_ENTRY* pLeaseEntry, DHCPS_LEASE_HANDLE leaseHandle)
{
    int                 entryIx;
    OA_HASH_DCPT*       pOH;
    DHCPS_HASH_ENTRY*   pDsEntry;
	DHCPS_HASH_DCPT*	pDSHashDcpt;
	SYS_TICK 			current_time = SYS_TICK_Get();
    
    TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(netH);
    if(pNetIf == 0 || pNetIf->Flags.bIsDHCPSrvEnabled == 0)
    {
        return 0;
    }

	pDSHashDcpt = &dhcpsHashDcpt;

    pOH = pDSHashDcpt->hashDcpt;
    if(pOH != 0)
    {   // DHCP Server proper initialized
        for(entryIx = (int)leaseHandle; entryIx < pOH->hEntries; entryIx++)
        {
            pDsEntry = (DHCPS_HASH_ENTRY*)TCPIP_OAHASH_EntryGet(pOH, entryIx);
            if(pDsEntry && (pDsEntry->hEntry.flags.busy != 0) && (pDsEntry->hEntry.flags.value & DHCPS_FLAG_ENTRY_COMPLETE) != 0)
            {
	            if(pDsEntry->intfIdx != TCPIP_STACK_NetIxGet(pNetIf))
            	{
					continue;
            	}

                // found entry
                if(pLeaseEntry)
                {
                    memcpy(&pLeaseEntry->hwAdd, &pDsEntry->hwAdd, sizeof(pDsEntry->hwAdd));
                    pLeaseEntry->ipAddress.Val = pDsEntry->ipAddress.Val;
                    pLeaseEntry->leaseTime = pDSHashDcpt->leaseDuartion*SYS_TICK_TicksPerSecondGet() - (current_time - pDsEntry->Client_Lease_Time);
                }
                return (DHCPS_LEASE_HANDLE)(entryIx + 1);
            }
        }
    }

    // no other entry
    return 0;
}


int TCPIP_DHCPS_GetPoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type)
{
    int                 entryIx;
    int                 noOfEntries=0;
    OA_HASH_DCPT*       pOH;
    DHCPS_HASH_ENTRY*   pDsEntry;
	DHCPS_HASH_DCPT*	pDSHashDcpt;
	
    TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(netH);
    if(pNetIf == 0 || pNetIf->Flags.bIsDHCPSrvEnabled == 0)
    {
        return 0;
    }

    
	pDSHashDcpt = &dhcpsHashDcpt;

    pOH = pDSHashDcpt->hashDcpt;
    
    if(pOH != 0)
    {   // DHCP Server proper initialized
        for(entryIx = (int)0; entryIx < pOH->hEntries; entryIx++)
        {
            pDsEntry = (DHCPS_HASH_ENTRY*)TCPIP_OAHASH_EntryGet(pOH, entryIx);
            
            switch(type)
            {
                case DHCP_SERVER_POOL_ENTRY_ALL:
                    if(pDsEntry && (pDsEntry->hEntry.flags.busy != 0))
                    {
                        if(pDsEntry->intfIdx != TCPIP_STACK_NetIxGet(pNetIf))
                        {
                            continue;
                        }
                        noOfEntries++;
                    }
                    break;
                case DHCP_SERVER_POOL_ENTRY_IN_USE:
                    if(pDsEntry && (pDsEntry->hEntry.flags.busy != 0) && (pDsEntry->hEntry.flags.value & DHCPS_FLAG_ENTRY_COMPLETE) != 0)
                    {
                        if(pDsEntry->intfIdx != TCPIP_STACK_NetIxGet(pNetIf))
                        {
                            continue;
                        }
                        noOfEntries++;
                    }
                    break;
            }

        }
    }
    return noOfEntries;
        
}

bool TCPIP_DHCPS_RemovePoolEntries(TCPIP_NET_HANDLE netH, DHCP_SERVER_POOL_ENTRY_TYPE type)
{
    int                 entryIx;
    OA_HASH_DCPT*       pOH;
    DHCPS_HASH_ENTRY*   pDsEntry;
	DHCPS_HASH_DCPT*	pDSHashDcpt;
	
    TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(netH);
    if(pNetIf == 0 || pNetIf->Flags.bIsDHCPSrvEnabled == 0)
    {
        return false;
    }

    
	pDSHashDcpt = &dhcpsHashDcpt;

    pOH = pDSHashDcpt->hashDcpt;
    
    if(pOH != 0)
    {   // DHCP Server proper initialized
        for(entryIx = (int)0; entryIx < pOH->hEntries; entryIx++)
        {
            pDsEntry = (DHCPS_HASH_ENTRY*)TCPIP_OAHASH_EntryGet(pOH, entryIx);
            
            switch(type)
            {
                case DHCP_SERVER_POOL_ENTRY_ALL:
                    if(pDsEntry && (pDsEntry->hEntry.flags.busy != 0))
                    {
                        if(pDsEntry->intfIdx != TCPIP_STACK_NetIxGet(pNetIf))
                        {
                            continue;
                        }
                        TCPIP_OAHASH_EntryRemove(pOH,&pDsEntry->hEntry);
                    }
                    break;
                case DHCP_SERVER_POOL_ENTRY_IN_USE:
                    if(pDsEntry && (pDsEntry->hEntry.flags.busy != 0) && (pDsEntry->hEntry.flags.value & DHCPS_FLAG_ENTRY_COMPLETE) != 0)
                    {
                        if(pDsEntry->intfIdx != TCPIP_STACK_NetIxGet(pNetIf))
                        {
                            continue;
                        }
                        TCPIP_OAHASH_EntryRemove(pOH,&pDsEntry->hEntry);
                    }
                    break;
            }
        }
    }
    return true;
}

size_t TCPIP_DHCPS_MACHashKeyHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32_hash(key, DHCPS_HASH_KEY_SIZE) % (pOH->hEntries);
}

#if defined(OA_DOUBLE_HASH_PROBING)
size_t TCPIP_DHCPS_HashProbeHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32a_hash(key, DHCPS_HASH_KEY_SIZE) % (pOH->hEntries);
}
#endif  // defined(OA_DOUBLE_HASH_PROBING)

size_t TCPIP_DHCPS_IPAddressHashKeyHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32_hash(key, 4) % (pOH->hEntries);
}


static void _DHCPSDeleteResources(void)
{
	// Remove all the HASH entries		
	_DHCPSRemoveCacheEntries(&dhcpsHashDcpt);

    if(dhcpSDcpt.timerHandle)
    {
        _TCPIPStackAsyncHandlerDeRegister(dhcpSDcpt.timerHandle);
		dhcpSDcpt.timerHandle = 0;
    }
}

bool TCPIP_DHCPS_Disable(TCPIP_NET_HANDLE hNet)
{
	TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(hNet);
    if(pNetIf == 0)
    {
        return false;
    }
//  Now stop DHCP server
	dhcpSDcpt.enabled = false;
	pNetIf->Flags.bIsDHCPSrvEnabled = false;
	if( dhcpSDcpt.uSkt != INVALID_UDP_SOCKET)
	{
		TCPIP_UDP_Close(dhcpSDcpt.uSkt);
		dhcpSDcpt.uSkt = INVALID_UDP_SOCKET;
	}
	
    TCPIP_STACK_AddressServiceEvent(pNetIf, TCPIP_STACK_ADDRESS_SERVICE_DHCPS, TCPIP_STACK_ADDRESS_SERVICE_EVENT_USER_STOP);
	return true;

}

bool TCPIP_DHCPS_Enable(TCPIP_NET_HANDLE hNet)
{
	TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(hNet);
	DHCP_SRVR_DCPT* pServer;
	pServer  = &dhcpSDcpt;
    if(pNetIf == 0)
    {
        return false;
    }
	if(TCPIP_STACK_AddressServiceCanStart(pNetIf, TCPIP_STACK_ADDRESS_SERVICE_DHCPS))
	{ 
		if(pServer->enabled == false)
		{
			pServer->smServer = DHCP_SERVER_OPEN_SOCKET;
			pServer->enabled = true;
			pNetIf->Flags.bIsDHCPSrvEnabled = true;
            // Remove all the HASH entries if there is anything
			// Remove all the HASH entries	
		}
		return true;
		
	}

        return false;
	
}

/*****************************************************************************
  Function:
	bool TCPIP_DHCPS_IsEnabled(CPIP_NET_HANDLE hNet)

  Summary:
	Determins if the DHCP Server is enabled on the specified interface.

  Description:
	Determins if the DHCP Server is enabled on the specified interface.

  Precondition:
	None

  Parameters:
	 hNet- Interface to query.

  Returns:
	None
***************************************************************************/
bool TCPIP_DHCPS_IsEnabled(TCPIP_NET_HANDLE hNet)
{
    TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNetUp(hNet);
    if(pNetIf)
    {
        return pNetIf->Flags.bIsDHCPSrvEnabled != 0;
    }
    return false;
}


#else
bool TCPIP_DHCPS_Disable(TCPIP_NET_HANDLE hNet){return false;}
bool TCPIP_DHCPS_Enable(TCPIP_NET_HANDLE hNet){return false;}
bool TCPIP_DHCPS_IsEnabled(TCPIP_NET_HANDLE hNet){return false;}
#endif //#if defined(TCPIP_STACK_USE_DHCP_SERVER)

