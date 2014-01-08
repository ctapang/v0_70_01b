/*******************************************************************************
  Domain Name System (DNS) Server dummy

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    - Acts as a DNS server, but gives out the local IP address for all 
      queries to force web browsers to access the board.
    - Reference: RFC 1034 and RFC 1035
*******************************************************************************/

/*******************************************************************************
File Name:  DNSs.c
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
#define DNSS_C

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_STACK_USE_DNS_SERVER)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_DNS_SERVER

static void DNSCopyRXNameToTX(UDP_SOCKET s);

typedef enum
{
    DNSS_STATE_START             = 0,
    DNSS_STATE_WAIT_REQUEST,
    DNSS_STATE_PUT_REQUEST,
    DNSS_STATE_DONE,
}DNSS_STATE;


static DNSS_STATE   dnssState = DNSS_STATE_START;

#define BUF_SIZE_DNS_NAME 64
static uint8_t DnsName_buf[BUF_SIZE_DNS_NAME];  
static uint8_t Size_HostName = 0;

static void DNSGetRXName(UDP_SOCKET s);
static bool DNSName_valified(char *name,int name_size);

bool TCPIP_DNSS_Intialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const DNS_SERVER_MODULE_CONFIG* pDnsConfig)
{
    return true;
}

void TCPIP_DNSS_Deintialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
}


/*********************************************************************
 * Function:        void TCPIP_DNSS_Task(TCPIP_NET_IF* pNet)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Sends dummy responses that point to ourself for DNS requests
 *
 * Note:            None
 ********************************************************************/
void TCPIP_DNSS_Task(TCPIP_NET_IF* pNet)
{
	static UDP_SOCKET	MySocket = INVALID_UDP_SOCKET;
	static struct
	{
		uint16_t wTransactionID;
		uint16_t wFlags;
		uint16_t wQuestions;
		uint16_t wAnswerRRs;
		uint16_t wAuthorityRRs;
		uint16_t wAdditionalRRs;
	} DNSHeader;

    TCPIP_NET_IF* pSktIf;

    switch(dnssState)
    {
        case DNSS_STATE_START:

            // Create a socket to listen on if this is the first time calling this function
            if(MySocket == INVALID_UDP_SOCKET)
            {
                MySocket = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, DNS_PORT, 0);
                if(MySocket == INVALID_UDP_SOCKET)
                    break;
            }
            
            dnssState = DNSS_STATE_WAIT_REQUEST;
            break;

        case DNSS_STATE_WAIT_REQUEST:

            // See if a DNS query packet has arrived
            if(TCPIP_UDP_GetIsReady(MySocket) < sizeof(DNSHeader))
                break;

            // Read DNS header
            TCPIP_UDP_ArrayGet(MySocket, (uint8_t*)&DNSHeader, sizeof(DNSHeader));

            // Ignore this packet if it isn't a query
            if((DNSHeader.wFlags & 0x8000) == 0x8000u)
            {
                TCPIP_UDP_Discard(MySocket);
                break;
            }

            // Ignore this packet if there are no questions in it
            if(DNSHeader.wQuestions == 0u)
            {
                TCPIP_UDP_Discard(MySocket);
                break;
            }

			
			// Ignore this packet if the last works is not ".local"
			DNSGetRXName(MySocket);
			if(false == DNSName_valified(".local", 6))
			{TCPIP_UDP_Discard(MySocket);    break;}
            dnssState = DNSS_STATE_PUT_REQUEST;
            break;

        case DNSS_STATE_PUT_REQUEST:

            // get the interface the message came on
            pSktIf = (TCPIP_NET_IF*)TCPIP_UDP_SocketNetGet(MySocket);
            // check that we can transmit a DNS response packet
            if(!TCPIP_UDP_TxPutIsReady(MySocket, 64))
            {   
                break;
            }

            // Write DNS response packet
            TCPIP_UDP_ArrayPut(MySocket, (uint8_t*)&DNSHeader.wTransactionID, 2);	// 2 byte Transaction ID
            if(DNSHeader.wFlags & 0x0100)
                TCPIP_UDP_Put(MySocket, 0x81);	// Message is a response with recursion desired
            else
                TCPIP_UDP_Put(MySocket, 0x80);	// Message is a response without recursion desired flag set
            
            TCPIP_UDP_Put(MySocket, 0x80);	// Recursion available
            TCPIP_UDP_Put(MySocket, 0x00);	// 0x0000 Questions
            TCPIP_UDP_Put(MySocket, 0x00);
            TCPIP_UDP_Put(MySocket, 0x00);	// 0x0001 Answers RRs
            TCPIP_UDP_Put(MySocket, 0x01);
            TCPIP_UDP_Put(MySocket, 0x00);	// 0x0000 Authority RRs
            TCPIP_UDP_Put(MySocket, 0x00);
            TCPIP_UDP_Put(MySocket, 0x00);	// 0x0000 Additional RRs
            TCPIP_UDP_Put(MySocket, 0x00);
            DNSCopyRXNameToTX(MySocket);	// Copy hostname of first question over to TX packet
            TCPIP_UDP_Put(MySocket, 0x00);	// Type A Host address
            TCPIP_UDP_Put(MySocket, 0x01);
            TCPIP_UDP_Put(MySocket, 0x00);	// Class INternet
            TCPIP_UDP_Put(MySocket, 0x01);
            TCPIP_UDP_Put(MySocket, 0x00);	// Time to Live 10 seconds
            TCPIP_UDP_Put(MySocket, 0x00);
            TCPIP_UDP_Put(MySocket, 0x00);
            TCPIP_UDP_Put(MySocket, 0x0A);
            TCPIP_UDP_Put(MySocket, 0x00);	// Data Length 4 bytes
            TCPIP_UDP_Put(MySocket, 0x04);
            TCPIP_UDP_ArrayPut(MySocket, (uint8_t*)&pSktIf->netIPAddr.Val, 4);	// Our IP address

            TCPIP_UDP_Flush(MySocket);

            dnssState = DNSS_STATE_DONE;
            break;
            
         case DNSS_STATE_DONE:
            break;
    }
            
           
}



/*****************************************************************************
  Function:
	static void DNSCopyRXNameToTX(UDP_SOCKET s)

  Summary:
	Copies a DNS hostname, possibly including name compression, from the RX 
	packet to the TX packet (without name compression in TX case).
	
  Description:
	None

  Precondition:
	RX pointer is set to currently point to the DNS name to copy

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
static void DNSCopyRXNameToTX(UDP_SOCKET s)
{
	uint16_t w;
	uint8_t i;
	uint8_t len;

	while(1)
	{
		// Get first byte which will tell us if this is a 16-bit pointer or the 
		// length of the first of a series of labels
		if(!TCPIP_UDP_Get(s, &i))
			return;
		
		// Check if this is a pointer, if so, get the reminaing 8 bits and seek to the pointer value
		if((i & 0xC0u) == 0xC0u)
		{
			((uint8_t*)&w)[1] = i & 0x3F;
			TCPIP_UDP_Get(s, (uint8_t*)&w);
			TCPIP_UDP_RxOffsetSet(s, w);
			continue;
		}

		// Write the length byte
		len = i;
		TCPIP_UDP_Put(s, len);
		
		// Exit if we've reached a zero length label
		if(len == 0u)
			return;
		
		// Copy all of the bytes in this label	
		while(len--)
		{
			TCPIP_UDP_Get(s, &i);
			TCPIP_UDP_Put(s, i);
		}
	}
}

static void DNSGetRXName(UDP_SOCKET s)
{
	uint16_t w;
	uint8_t i;
	uint8_t len;
	
	for(Size_HostName=0;Size_HostName<BUF_SIZE_DNS_NAME;Size_HostName++) DnsName_buf[Size_HostName] = 0x00;
	Size_HostName = 0;
	
	while(1)
	{
		// Get first byte which will tell us if this is a 16-bit pointer or the 
		// length of the first of a series of labels
		if(!TCPIP_UDP_Get(s,&i))
			return;
		
		// Check if this is a pointer, if so, get the reminaing 8 bits and seek to the pointer value
		if((i & 0xC0u) == 0xC0u)
		{
			((uint8_t*)&w)[1] = i & 0x3F;
			TCPIP_UDP_Get(s,(uint8_t*)&w);
			//IPSetRxBuffer(sizeof(UDP_HEADER) + w);
			continue;
		}

		// Write the length byte
		len = i;
		TCPIP_UDP_Put(s,len);
		
		// Exit if we've reached a zero length label
		if(len == 0u)
			return;
		
		// Copy all of the bytes in this label	
		while(len--)
		{
			TCPIP_UDP_Get(s,&i);
			if(Size_HostName < BUF_SIZE_DNS_NAME) DnsName_buf[Size_HostName++] = i;
		}
		if(Size_HostName < BUF_SIZE_DNS_NAME) DnsName_buf[Size_HostName++] = '.';
	}
}


static bool DNSName_valified(char *name,int name_size)
{
   int buf_size = Size_HostName - 1;  //ignore the last character "."
   int pos_Start = buf_size - name_size;
   int i;
   for(i = 0; i<name_size; i++)
   {
	   if(DnsName_buf[pos_Start + i] != name[i])
		   return false;
   }
   return true;
}

#endif //#if defined(TCPIP_STACK_USE_DNS_SERVER)
