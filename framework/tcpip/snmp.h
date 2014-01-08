/*******************************************************************************
  SNMP Defs for Microchip TCP/IP Stack

  Company:
    Microchip Technology Inc.
    
  File Name:
    snmp.h

  Summary:
    
  Description:
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

#ifndef SNMP_H
#define SNMP_H

#include "tcpip/tcpip.h"
#include "snmp_config.h"




/****************************************************************************
  Section:
	Macros and Definitions 
  ***************************************************************************/

#define SNMP_START_OF_VAR       (0)
#define SNMP_END_OF_VAR         (0xff)
#define SNMP_INDEX_INVALID      (0xff)

// Section:  SNMP agent version types
#define SNMP_V1                 (0)
#define SNMP_V2C				(1)
#define SNMP_V3					(3)
//This is the SNMP OID variable id.
//This id is assigned via MIB file.  Only dynamic and AgentID
//variables can contian ID.  MIB2BIB utility enforces this
//rules when BIB was generated.
//typedef int SNMP_ID;

typedef uint32_t SNMP_ID;
typedef uint8_t SNMP_INDEX;

typedef enum
{
	IPV4_SNMP_TRAP=1,
	IPV6_SNMP_TRAP,
}SNMP_TRAP_IP_ADDRESS_TYPE;


typedef union
{
    uint32_t dword;				//double word value
    uint16_t  word;					//word value
    uint8_t  byte;					//byte value
    uint8_t  v[sizeof(uint32_t)];		//byte array
} SNMP_VAL;

typedef enum {
    SNMP_HOME = 0,
    SNMP_LISTEN,
    SNMP_PROCESS,
    SNMP_PACKET_DISCARD,
}TCPIP_SNMP_SM;

typedef enum
{
	READ_COMMUNITY=1,		//Read only community	
	WRITE_COMMUNITY=2,		//Read write community
	INVALID_COMMUNITY=3			//Community invalid
}SNMP_COMMUNITY_TYPE;


typedef enum
{
	COLD_START 			=0x0,
	WARM_START			=0x1,
	LINK_DOWN			=0x2,
	LINK_UP				=0x3,
	AUTH_FAILURE		=0x4,	
	EGP_NEBOR_LOSS		=0x5,
	ENTERPRISE_SPECIFIC	=0x6
	
} GENERIC_TRAP_NOTIFICATION_TYPE; 


typedef enum
{
	VENDOR_TRAP_DEFAULT 	=0x0,
	BUTTON_PUSH_EVENT		=0x1,
	POT_READING_MORE_512	=0x2
} VENDOR_SPECIFIC_TRAP_NOTIFICATION_TYPE;

// SNMPv1/v2c
typedef struct 
{	
	uint8_t *head;
	uint16_t length;
}SNMP_BUFFER_DATA;


typedef struct
{
	uint8_t oidstr[16];
	uint8_t version;
}SNMP_NON_MIB_RECD_INFO;


typedef struct
{
} SNMP_MODULE_CONFIG;

typedef struct
{
	// SNMPv2C Read community names
	// SNMP_COMMUNITY_MAX_LEN (8) + 1 null termination byte
	uint8_t readCommunity[SNMP_MAX_COMMUNITY_SUPPORT][SNMP_COMMUNITY_MAX_LEN+1];

	// SNMPv2C Write community names
	// SNMP_COMMUNITY_MAX_LEN (8) + 1 null termination byte
	uint8_t writeCommunity[SNMP_MAX_COMMUNITY_SUPPORT][SNMP_COMMUNITY_MAX_LEN+1];

	uint32_t SnmpEngineBootRcrd;
}SNMP_NET_CONFIG;

// 	   // the only if that runs SNMP
// Section:  SNMP trap notification information for agent
typedef struct 
{
	char community[NOTIFY_COMMUNITY_LEN];	//Community name array
	uint8_t communityLen;						//Community name length
	SNMP_ID agentIDVar; 					//Agent id for trap identification
	uint8_t notificationCode;					//Trap notification code
	UDP_SOCKET socket;						//Udp socket number 
	TCPIP_UINT32_VAL timestamp;					//Time stamp for trap
#if defined(SNMP_STACK_USE_V2_TRAP) || defined(SNMP_V1_V2_TRAP_WITH_SNMPV3) 
	SNMP_ID trapIDVar;						// SNMPV2 specific trap
#endif	
	TCPIP_NET_HANDLE snmpTrapInf; // interface we use for the SNMP TRAP

} SNMP_NOTIFY_INFO;


typedef struct tSNMP_TRAP_INFO
{
   uint8_t Size;
   struct
   {
       uint8_t communityLen;					//Community name length
       char community[TRAP_COMMUNITY_MAX_LEN];	//Community name array
       IPV4_ADDR IPAddress;					//IP address to which trap to be sent
       struct
       {
           unsigned int bEnabled : 1;		//Trap enabled flag	
       } Flags;
   } table[TRAP_TABLE_SIZE];				
} SNMP_TRAP_INFO;

#ifdef TCPIP_STACK_USE_IPV6
typedef struct tIPV6_SNMP_TRAP_INFO
{
   uint8_t Size;
   struct
   {
       uint8_t communityLen;					//Community name length
       char community[TRAP_COMMUNITY_MAX_LEN];	//Community name array
       IPV6_ADDR IPv6Address;					//IPv6 address to which trap to be sent
       struct
       {
           unsigned int bEnabled : 1;		//Trap enabled flag	
       } Flags;
   } table[TRAP_TABLE_SIZE];				
} IPV6_SNMP_TRAP_INFO;

#endif  /* TCPIP_STACK_USE_IPV6 */

typedef struct
{
    TCPIP_SNMP_SM   sm;     // current status
    UDP_SOCKET      skt;    // associated socket
	bool readFromSnmpBuf;
#if defined (TCPIP_STACK_USE_IPV6)
    IPV6_HANDLE snmpIPV6Handler;
    IPV6_EVENT_TYPE ipv6EventType;
#endif
}TCPIP_SNMP_DCPT;
/****************************************************************************
  Section:
	Global Variables
  ***************************************************************************/

typedef struct
{
	
	uint8_t gOIDCorrespondingSnmpMibID;

	#if defined(SNMP_STACK_USE_V2_TRAP)
	uint8_t	gSetTrapSendFlag;
	#endif
	
	bool getZeroInstance;
	uint8_t appendZeroToOID;

	uint8_t gSendTrapFlag;
	uint8_t gGenericTrapNotification;
	uint8_t gSpecificTrapNotification;
	SNMP_NOTIFY_INFO SNMPNotifyInfo; //notify info for trap
	SNMP_BUFFER_DATA outPduBufData;
	
	SNMP_BUFFER_DATA trapPduOutBufData;
	SNMP_NET_CONFIG snmpNetConfig;

}SNMP_STACK_DCPT_STUB;


typedef struct 
{

SNMP_STACK_DCPT_STUB* snmpStkDynMemStubPtr;
const void* snmpHeapMemHandler; 
TCPIP_SNMP_DCPT* snmpDcptPtr;
}SNMP_PROCESSING_MEM_INFO_PTRS;



/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/

#if !defined(SNMP_TRAP_DISABLED)
TCPIP_NET_HANDLE TCPIP_SNMP_ClientGetNet(void);


/**************************************************************************
  Function:
    void SNMPSendTrap(void)

  Summary:
     Prepare, validate remote node which will receive trap and send trap pdu.

  Description:
     This function is used to send trap notification to previously
     configured ip address if trap notification is enabled. There are
     different trap notification code. The current implementation
     sends trap for authentication failure (4).

  PreCondition:
     If application defined event occurs to send the trap.

  parameters:
     None.

  Returns:
     None.

  Remarks:
     This is a callback function called by the application on certain
     predefined events. This routine only implemented to send a
     authentication failure Notification-type macro with PUSH_BUTTON
     oid stored in MPFS. If the ARP is no resolved i.e. if
     TCPIP_SNMP_NotifyIsReady() returns false, this routine times
     out in 5 seconds. This routine should be modified according to
     event occured and should update corrsponding OID and notification
     type to the trap pdu.
 *************************************************************************/
void SNMPSendTrap(void);


/****************************************************************************
  Function:
    bool TCPIP_SNMP_Notify(SNMP_ID var,SNMP_VAL val,SNMP_INDEX index)

  Summary:
    Creates and Sends TRAP pdu.

  Description:
    This function creates SNMP V2 Trap PDU and sends it to previously specified
    remoteHost.

    SNMP V1 trap pdu:
       | PDU-type | enterprise | agent-addr | generic-trap | specific-trap |
       | time-stamp | varbind-list |

       The v1 enterprise is mapped directly to SNMPv2TrapOID.0

    SNMP V2 trap pdu:
       version (0 or 1) | community | SNMP-PDU |pdu-type | request-id | error-status
       |err-index |varbinds

       The first two variables (in varbind-list) of snmpv2 are: sysUpTime.0 and
        SNMPv2TrapOID.0

        Generic Trap OID is used as the varbind for authentication failure.

  Precondition:
    TCPIP_SNMP_NotifyIsReady() is already called and returned true.

  Parameters:
    var     - SNMP var ID that is to be used in notification
    val     - Value of var. Only value of uint8_t, uint16_t or uint32_t can be sent.
    index   - Index of var. If this var is a single,index would be 0, or else
              if this var Is a sequence, index could be any value
              from 0 to 127

  Return Values:
    true    -   if SNMP notification was successful sent.
                This does not guarantee that remoteHost recieved it.
    false   -   Notification sent failed.
                This would fail under following contions:
                1) Given SNMP_BIB_FILE does not exist in file system
                2) Given var does not exist.
                3) Previously given agentID does not exist
                4) Data type of given var is unknown -
                   possible if file system itself was corrupted.

  Remarks:
    This would fail if there were not UDP socket to open.
 */
bool TCPIP_SNMP_Notify(SNMP_ID var, SNMP_VAL val, SNMP_INDEX index);


/****************************************************************************
  Function:
    bool TCPIP_SNMP_NotifyIsReady(IP_MULTI_ADDRESS* remoteHost,SNMP_TRAP_IP_ADDRESS_TYPE eTrapMultiAddressType)

  Summary:
    Resolves given remoteHost IP address into MAC address.

  Description:
    This function resolves given remoteHost IP address into MAC address using
    ARP module. If remoteHost is not aviailable, this function would never
    return true. Application must implement timeout logic to handle
    "remoteHost not avialable" situation.

  Precondition:
    TCPIP_SNMP_NotifyPrepare() is already called.

  Parameters:
    remoteHost  - Pointer to remote Host IP address

  Return Values:
    true    -   If remoteHost IP address is resolved and
                TCPIP_SNMP_Notify may be called.
    false   -   If remoteHost IP address is not resolved.

  Remarks:
    This would fail if there were not UDP socket to open.
 */
bool TCPIP_SNMP_NotifyIsReady(IP_MULTI_ADDRESS* remoteHost,SNMP_TRAP_IP_ADDRESS_TYPE eTrapMultiAddressType);


/****************************************************************************
  Function:
    void TCPIP_SNMP_NotifyPrepare(IP_MULTI_ADDRESS* remoteHost,
                                  char* community,
                                  uint8_t communityLen,
                                  SNMP_ID agentIDVar,
                                  uint8_t notificationCode,
                                  uint32_t timestamp         )

  Summary:
    Collects trap notification info and send ARP to remote host.

  Description:
    This function prepares SNMP module to send SNMP trap notification
    to remote host. It sends ARP request to remote host to learn remote
    host MAC address.

  Precondition:
    TCPIP_SNMP_Initialize() is already called.

  Parameters:
    remoteHost  - pointer to remote Host IP address
    community   - Community string to use to notify
    communityLen- Community string length
    agentIDVar  - System ID to use identify this agent
    notificaitonCode - Notification Code to use
    timestamp   - Notification timestamp in 100th of second.

  Returns:
    None

  Remarks:
    This is first of series of functions to complete SNMP notification.
 */
void TCPIP_SNMP_NotifyPrepare(IP_MULTI_ADDRESS* remoteHost, char* community, uint8_t communityLen, SNMP_ID agentIDVar, uint8_t notificationCode, uint32_t timestamp);

#endif//#if !defined(SNMP_TRAP_DISABLED)


/****************************************************************************
  Function:
    void TCPIP_SNMP_PacketProcStubPtrsGet( SNMP_PROCESSING_MEM_INFO_PTRS * dynMemInfoPtr)

  Summary:
    Get SNMP packet processing memory pointer.

  Description:
    This function is used to get dynamic memory allocation pointer details which is used for SNMP
    packet processing.

  Precondition:
    TCPIP_SNMP_Initialize() is already called.

  Parameters:
    dynMemInfoPtr  - Dynamic memory pointer for packet processing

  Return Values:
    None.

  Remarks:
    None.
*/
void TCPIP_SNMP_PacketProcStubPtrsGet( SNMP_PROCESSING_MEM_INFO_PTRS * dynMemInfoPtr);


/****************************************************************************
  Function:
    SYS_TICK TCPIP_SNMP_TrapTimeGet(void)

  Summary:
    Get SNMP Trap UDP client open socket timeout.

  Description:
    This function returns a SYS_TICK time(snmpTrapTimer) which is used to timeout a SNMP TRAP
    notification for a HOST. snmpTrapTimer is initialized when there is UDP client socket open
    either for a HOST IPv4 or IPv6 address.

  Precondition:
    TCPIP_SNMP_Initialize() is already called.

  Parameters:
    Void.

  Return Values:
    SYS_TICK time.
  Remarks:
    None.
*/
SYS_TICK TCPIP_SNMP_TrapTimeGet(void);


/*********************************************************************
  Function:
    bool SNMPSetVar(SNMP_ID var, SNMP_INDEX index,
                                   uint8_t ref, SNMP_VAL val)

  Summary:
    This routine Set the mib variable with the requested value.

  Description:
    This is a callback function called by module for the snmp
    SET request.User application must modify this function
    for the new variables address.

  Precondition:
    TCPIP_SNMP_ProcessVariables() is called.

  Parameters:
    var -   Variable id whose value is to be set

    ref -   Variable reference used to transfer multi-byte data
            0 if first byte is set otherwise nonzero value to indicate
            corresponding byte being set.

    val -   Up to 4 byte data value.
            If var data type is uint8_t, variable
               value is in val->byte
            If var data type is uint16_t, variable
               value is in val->word
            If var data type is uint32_t, variable
               value is in val->dword.
            If var data type is IP_ADDRESS, COUNTER32,
               or GAUGE32, value is in val->dword
            If var data type is OCTET_STRING, ASCII_STRING
               value is in val->byte; multi-byte transfer
               will be performed to transfer remaining
               bytes of data.

  Return Values:
    true    -   if it is OK to set more byte(s).
    false   -   if otherwise.

  Remarks:
    This function may get called more than once depending on number
    of bytes in a specific set request for given variable.
    only dynamic read-write variables needs to be handled.
 */
bool SNMPSetVar(SNMP_ID var, SNMP_INDEX index,uint8_t ref, SNMP_VAL val);


/*********************************************************************
  Function:
    bool SNMPGetVar(SNMP_ID var, SNMP_INDEX index,uint8_t* ref, SNMP_VAL* val)

  Summary:
    Used to Get/collect OID variable information.

  Description:
    This is a callback function called by SNMP module. SNMP user must
    implement this function in user application and provide appropriate
    data when called.

  PreCondition:
    None

  parameters:
    var     -   Variable id whose value is to be returned
    index   -   Index of variable that should be transferred
    ref     -   Variable reference used to transfer
                multi-byte data
                It is always SNMP_START_OF_VAR when very
                first byte is requested.
                Otherwise, use this as a reference to
                keep track of multi-byte transfers.
    val     -   Pointer to up to 4 byte buffer.
                If var data type is uint8_t, transfer data
                  in val->byte
                If var data type is uint16_t, transfer data in
                  val->word
                If var data type is uint32_t, transfer data in
                  val->dword
                If var data type is IP_ADDRESS, transfer data
                  in val->v[] or val->dword
                If var data type is COUNTER32, TIME_TICKS or
                  GAUGE32, transfer data in val->dword
                If var data type is ASCII_STRING or OCTET_STRING
                  transfer data in val->byte using multi-byte
                  transfer mechanism.

  Return Values:
    true    -   If a value exists for given variable at given index.
    false   -   Otherwise.

  Remarks:
    None.
 */
bool SNMPGetVar(SNMP_ID var, SNMP_INDEX index,uint8_t* ref, SNMP_VAL* val);


/*********************************************************************
  Function:
    bool SNMPGetNextIndex(SNMP_ID var,SNMP_INDEX* index)

  Summary:
    To search for next index node in case of a Sequence variable.

  Description:
    This is a callback function called by SNMP module.
    SNMP user must implement this function in user application and
    provide appropriate data when called.  This function will only
    be called for OID variable of type sequence.

  PreCondition:
    None

  Parameters:
    var     -   Variable id whose value is to be returned
    index   -   Next Index of variable that should be transferred

  Return Values:
    true    -    If a next index value exists for given variable at given
                 index and index parameter contains next valid index.
    false   -    Otherwise.

  Remarks:
      Only sequence index needs to be handled in this function.
 */
bool SNMPGetNextIndex(SNMP_ID var, SNMP_INDEX* index);


/*********************************************************************
  Function:
    bool SNMPGetExactIndex(SNMP_ID var,SNMP_INDEX *index)

  Summary:
    To search for exact index node in case of a Sequence variable.

  Description:
    This is a callback function called by SNMP module.
    SNMP user must implement this function in user application and
    provide appropriate data when called.  This function will only
    be called for OID variable of type sequence.

  PreCondition:
    None

  Parameters:
    var     -   Variable id as per mib.h (input)
    index      -     Index of variable (input)

  Return Values:
    true    -    If the exact index value exists for given variable at given
                 index.
    false   -    Otherwise.

  Remarks:
      Only sequence index needs to be handled in this function.
 */
bool SNMPGetExactIndex(SNMP_ID var, SNMP_INDEX *index);


/*********************************************************************
  Function:
  bool SNMPIsValidSetLen(SNMP_ID var, uint8_t len,uint8_t index)

  Summary:
    Validates the set variable data length to data type.

  Description:
    This routine is used to validate the dyanmic variable data length
    to the variable data type. It is used when SET request is processed.
    This is a callback function called by module. User application
    must implement this function.

  PreCondition:
    TCPIP_SNMP_ProcessSetVar() is called.

  Parameters:
    var -   Variable id whose value is to be set
    len -   Length value that is to be validated.

  Return Values:
    true  - if given var can be set to given len
    false - if otherwise.

  Remarks:
    This function will be called for only dynamic variables that are
    defined as ASCII_STRING and OCTET_STRING (i.e. data length greater
    than 4 bytes)
 */
bool SNMPIsValidSetLen(SNMP_ID var, uint8_t len,uint8_t index);


/*********************************************************************
  Function:
     uint8_t SNMPValidateCommunity(uint8_t* community)

  Summary:
     Validates community name for access control.

  Description:
     This function validates the community name for the mib access to NMS.
     The snmp community name received in the request pdu is validated for
     read and write community names. The agent gives an access to the mib
     variables only if the community matches with the predefined values.
     This routine also sets a gloabal flag to send trap if authentication
     failure occurs.

  PreCondition:
     TCPIP_SNMP_Initialize is already called.

  parameters:
     community - Pointer to community string as sent by NMS.

  Returns:
     This routine returns the community validation result as
     READ_COMMUNITY or WRITE_COMMUNITY or INVALID_COMMUNITY

  Remarks:
     This is a callback function called by module. User application must
     implement this function and verify that community matches with
     predefined value. This validation occurs for each NMS request.
 */
uint8_t SNMPValidateCommunity(uint8_t* community);


/****************************************************************************
  Function:
    uint8_t *TCPIP_SNMP_WriteCommunityGet
(int index)

  Summary:
    Get the writeCommunity String with Snmp index.

  Description:
    Get the writeCommunity String with Snmp index.

  Precondition  :
    _SNMP_ProcessVariables() is called.

  Parameters:
    index       -   SNMP_MAX_COMMUNITY_SUPPORT.

  Return Values:
    uint8_t *   -   unsigned char community string

  Remarks:
    None.
 */
uint8_t*  TCPIP_SNMP_WriteCommunityGet(int index);


/****************************************************************************
  Function:
    uint8_t *TCPIP_SNMP_ReadCommunityGet(int index)

  Summary:
    Get the readCommunity String with Snmp index.

  Description:
    Get the readCommunity String with Snmp index.

  Precondition  :
    _SNMP_ProcessVariables() is called.

  Parameters:
    index       -   SNMP_MAX_COMMUNITY_SUPPORT.

  Return Values:
    uint8_t *   -   unsigned char community string

  Remarks:
    None.
 */
uint8_t*  TCPIP_SNMP_ReadCommunityGet(int index);


/****************************************************************************
  Function:
    bool TCPIP_SNMP_DataCopyToProcessBuffer(uint8_t val ,SNMP_BUFFER_DATA *putbuf)

  Summary:
    Copies uint8_t data to dynamically allocated memory buffer.

  Description:
    The SNMPv1 and v2c stack implementation uses dynamically allocated memory buffer for
    processing of request and response packets. This routine copies the uint8_t data to the
    allocated buffer and updates the offset length couter.

  Precondition:
    The SNMPv1 and v2c stack has sucessfully allocated dynamic memory buffer from the Heap

  Parameters:
    val: uint8_t value to be written to the buffer
    putbuf: pointer to the dynamically allocated buffer to which the 'val' to be written

  Return Values:
    true: if successfully write to the buffer
    false: failure in writing to the buffer

  Remarks:
    This routine is used by the SNMP stack. If required to be used by the application
    code, valid pointers should be passed to this routine.

 */
bool TCPIP_SNMP_DataCopyToProcessBuffer(uint8_t val ,SNMP_BUFFER_DATA *putbuf);


/****************************************************************************
  Function:
    uint8_t TCPIP_SNMP_ProcessBufferDataGet(SNMP_BUFFER_DATA getbuf,uint16_t pos)

  Summary:
    Reads uint8_t data from dynamically allocated memory buffer.

  Description:
    The SNMPstack implementation uses dynamically allocated memory buffer for
    processing of request and response packets. This routine reads the uint8_t data from
    the allocated buffer at the positions (offset) provided.

  Precondition:
    The SNMPv1 and v2c stack has sucessfully allocated dynamic memory buffer from the Heap

  Parameters:
    getbuf: Structure from where to read the data byte.
    pos: position in the buffer from which the data to be read

  Return Values:
    uint8_t: 1 byte value read

  Remarks:
    The read position offset is required to be provided every time the routine is called.
    This API do not increment the buffer read offset automatically, everytime it is called.

 */
uint8_t TCPIP_SNMP_ProcessBufferDataGet(SNMP_BUFFER_DATA getbuf,uint16_t pos);

/****************************************************************************
  Function:
    DHCP_EVENT_TYPE TCPIP_SNMP_EventNotifyGet(void);
	
  Summary:
  	To Get the IPv6 DHCP event notification.
  	
  Description:
  	This rutine is used to get the DHCP with IPv6 notication if the IPv6 unicast address
  	is updated.
  	
  Precondition	:
	TCPIP_SNMP_Initialize() is called.	
		
  Parameters:
    hNet - Interface    
  Return Values:
    IPV6_EVENT_TYPE
	
  Remarks:
  	None.
***************************************************************************/

IPV6_EVENT_TYPE TCPIP_SNMP_EventNotifyGet(TCPIP_NET_HANDLE hNet);


#endif
