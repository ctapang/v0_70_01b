/*******************************************************************************
  Microchip TCP/IP Stack Definitions

  Company:
    Microchip Technology Inc.
    
  File Name:
    tcpip_manager_control.h

  Summary:
    
  Description:
*******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright � 2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _TCPIP_MANAGER_CONTROL_H_
#define _TCPIP_MANAGER_CONTROL_H_

#include "tcpip/tcpip_mac.h"



#if defined (TCPIP_IF_MRF24W)
    #include "wf_config.h" // pull in additional defines from wireless settings
#endif

#if defined(TCPIP_STACK_USE_SNMP_SERVER)
	#include "snmp_config.h"
#endif


// module timeout/asynchronous event handler
// the stack manager calls it when there's an tmo/asynchronous event pending
// it should clear the pending status
typedef void    (*tcpipModuleAsyncHandler)(void);


// function that is called by the stack manager to detect 
// if the corresponding module has some tmo/asynchronous event
// pending. It should return true if an asynchronous
// event is pending, false otherwise.
// This could be a timer event created by the module
// or other specific module events
typedef bool    (*tcpipModuleAsyncPending)(void);


// handle for the registration of a timeout/async handler
typedef const void* tcpipAsyncHandle;



typedef enum
{
    TCPIP_STACK_ADDRESS_SERVICE_NONE    = 0,    // no service
    TCPIP_STACK_ADDRESS_SERVICE_DHCPC,          // DHCP client
    TCPIP_STACK_ADDRESS_SERVICE_ZCLL,           // ZCLL
    TCPIP_STACK_ADDRESS_SERVICE_DHCPS,          // DHCP server
    //
    TCPIP_STACK_ADDRESS_SERVICE_MASK    = 0x7,     // mask of address services
                                                // hast to match the position in the TCPIP_STACK_NET_IF_FLAGS!!!
}TCPIP_STACK_ADDRESS_SERVICE_TYPE;

typedef enum
{
    TCPIP_STACK_ADDRESS_SERVICE_EVENT_NONE    = 0,      // no event
    TCPIP_STACK_ADDRESS_SERVICE_EVENT_RUN_FAIL,         // run time failure event
    TCPIP_STACK_ADDRESS_SERVICE_EVENT_CONN_LOST,        // conn lost event
    TCPIP_STACK_ADDRESS_SERVICE_EVENT_USER_STOP,        // user stop event
}TCPIP_STACK_ADDRESS_SERVICE_EVENT;


typedef union
{
    struct
    {
        // stack configuration dynamic flags
        uint16_t bIsDHCPEnabled         : 1;    // init: controls the DHCP enable/disable on the interface
                                                // runtime: mirror bit set by the DHCP to reflect the current/last status
        uint16_t bIsZcllEnabled         : 1;    // init: controls the ZCLL service enable/disable on the interface
                                                // runtime: mirror bit set by the ZCLL Server to reflect the current/last status
        uint16_t bIsDHCPSrvEnabled      : 1;    // init: controls the DHCP Server enable/disable on the interface
                                                // runtime: mirror bit set by the DHCP Server to reflect the current/last status
                                                // TCPIP_STACK_ADDRESS_SERVICE_MASK has to match!!!
        uint16_t bIsDNSServerAuto       : 1;    // DNS Server auto enable/disable on this interface
        uint16_t bInterfaceEnabled      : 1;    // 0 when TCPIP_MAC_POWER_DOWN/TCPIP_MAC_POWER_LOW 
        uint16_t bIPv6Enabled           : 1;
        uint16_t bIPv6InConfig          : 1;
volatile uint16_t bNewTcpipEventAvlbl   : 1;    // event available flag
        uint16_t powerMode              : 2;    // current power mode
        uint16_t localAndType           : 2;    // type of AND operation to be performed for local/nonlocal detection
        uint16_t localOrType            : 2;    // type of OR operation to be performed for local/nonlocal detection
        uint16_t bInConfig              : 1;    // stack is configuring itself
        uint16_t bMacProcessOnEvent     : 1;    // TCPIP_MAC_Process function needed on event
    };
    uint16_t v;
}TCPIP_STACK_NET_IF_FLAGS;      // flags per interface

// network interface descriptor
// 4 bytes aligned!
typedef struct
{
    uint16_t        size;                   // structure size; used in the configuration save/restore
    uint16_t        macId;                  // corresponding MAC id
	IPV4_ADDR		netIPAddr;              // IP address; currently only one IP add per interface
	IPV4_ADDR		netMask;                // Subnet mask
	IPV4_ADDR		netGateway;             // Gateway
	IPV4_ADDR		PrimaryDNSServer;       // Primary DNS Server
	IPV4_ADDR		SecondaryDNSServer;     // Secondary DNS Server
	IPV4_ADDR		DefaultIPAddr;          // Default IP address
	IPV4_ADDR		DefaultMask;            // Default subnet mask
	IPV4_ADDR		DefaultGateway;         // Default Gateway
	IPV4_ADDR		DefaultDNSServer;       // Default DNS Server
	IPV4_ADDR		DefaultDNSServer2;      // Default Secondary DNS Server
	uint8_t		    NetBIOSName[16];        // NetBIOS name
	TCPIP_MAC_ADDR	netMACAddr;             // MAC address
    TCPIP_STACK_NET_IF_FLAGS Flags;
#if defined(TCPIP_STACK_USE_IPV6)
    uint16_t        startFlags;  // TCPIP_NETWORK_CONFIG_FLAGS: flags for interface start up
    uint16_t        ipv6PrefixLen;  // IPv6 subnet ID
    IPV6_ADDR       netIPv6Addr;    // static IPv6 address
    IPV6_ADDR       netIPv6Gateway; // default IPv6 gateway
#else
    TCPIP_NETWORK_CONFIG_FLAGS startFlags;  // flags for interface start up
#endif
}TCPIP_STACK_NET_IF_DCPT;



#include "tcpip/src/tcpip_helpers_private.h"

// TCPIP network structure containing interface information
//  
typedef struct
{
    struct  // TCPIP_STACK_NET_IF_DCPT!!!; Anonymous for now;
    // KEEP IN SYNC! ALIGNED! ALWAYS AT BEGINNING!
    {
        uint16_t        size;                   // structure size; used in the configuration save/restore
        uint16_t        macId;                  // corresponding MAC id
        IPV4_ADDR		netIPAddr;              // IP address; currently only one IP add per interface
        IPV4_ADDR		netMask;                // Subnet mask
        IPV4_ADDR		netGateway;             // Gateway
        IPV4_ADDR		PrimaryDNSServer;       // Primary DNS Server
        IPV4_ADDR		SecondaryDNSServer;     // Secondary DNS Server
        IPV4_ADDR		DefaultIPAddr;          // Default IP address
        IPV4_ADDR		DefaultMask;            // Default subnet mask
        IPV4_ADDR		DefaultGateway;         // Default Gateway
        IPV4_ADDR		DefaultDNSServer;       // Default DNS Server
        IPV4_ADDR		DefaultDNSServer2;      // Default Secondary DNS Server
        uint8_t		    NetBIOSName[16];        // NetBIOS name
        TCPIP_MAC_ADDR	netMACAddr;             // MAC address
        TCPIP_STACK_NET_IF_FLAGS Flags;
#if defined(TCPIP_STACK_USE_IPV6)
        uint16_t        startFlags;  // TCPIP_NETWORK_CONFIG_FLAGS: flags for interface start up
        uint16_t        ipv6PrefixLen;  // IPv6 subnet ID
        IPV6_ADDR       netIPv6Addr;    // static IPv6 address
        IPV6_ADDR       netIPv6Gateway; // default IPv6 gateway
#else
        TCPIP_NETWORK_CONFIG_FLAGS startFlags;  // flags for interface start up
#endif

    };

    // NOTE the alignmment!
    IPV4_ADDR           localAndMask;           // AND mask for local/nonlocal destination network detection 
    IPV4_ADDR           localOrMask;            // OR mask for local/nonlocal destination network detection 
    
    TCPIP_MAC_HANDLE    hIfMac;                 // quick reference to which MAC this interface belongs to
                                                // ((__aligned__)) !!!
#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
    SINGLE_LIST         registeredClients;      // stack notification clients
                                                // ((__aligned__)) !!!
#endif  // defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
    uint16_t            netIfIx;                // index of this entry in the tcpipNetIf table.
                                                // netIfIx = (this - &tcpipNetIf[0])/sizeof(TCPIP_NET_IF)
                                                // stored to avoid the run time division
    uint16_t            activeEvents;           // TCPIP_MAC_EVENT accumulated event available
                                                // TCPIP_MAC_EVENT fits within 16 bits!
                                                // link up/down events are not 
                                                // necessarily triggered by hardware
    uint16_t            currEvents;             // current TCPIP_MAC_EVENT processed event
    uint8_t             linkPrev;               // previous status of the link
} TCPIP_NET_IF;


// TCPIP stack event registration

typedef struct  _TAG_TCPIP_LIST_NODE
{
	struct _TAG_TCPIP_LIST_NODE *next;	// next node in list
                                                // safe cast to SGL_LIST_NODE node!!!
    TCPIP_STACK_EVENT_HANDLER   handler;    // handler to be called for event
    const void*                 hParam;     // handler parameter
    TCPIP_EVENT                 evMask;     // event that triggers the notification
    TCPIP_NET_IF*               pNetIf;     // interface it belongs to
}TCPIP_EVENT_LIST_NODE;


// network interface action for initialization/de-initialization
typedef enum
{
    TCPIP_STACK_ACTION_INIT,         // stack is initialized 
    TCPIP_STACK_ACTION_REINIT,       // stack is re-initialized
    TCPIP_STACK_ACTION_DEINIT,       // stack is de-initialized
    TCPIP_STACK_ACTION_IF_UP,        // interface is brought up 
    TCPIP_STACK_ACTION_IF_DOWN,      // interface is brought down
}TCPIP_STACK_ACTION;


// data that's passed as reference to each other module init/deinit, etc
typedef struct _TCPIP_STACK_MODULE_CTRL
{
    // permanent data; this data is maintained by the stack for one full session
    // i.e. accross StackInit() -> StackDeInit() calls
    // 
    //
    // number of the interfaces supported in this seession
    int     nIfs;         
	// number of the modules enabled in this session
	int 	nMdls;
    // allocation parameters
    const void* memH;                                   // handle to be used in the TCPIP_HEAP_ calls

    // transient data; contains info for a specific call
    //
    //
    // pointer to the current interface
    TCPIP_NET_IF* pNetIf;
    // index of the current interface addressed
    int     netIx;
    // current action for the stack
    TCPIP_STACK_ACTION      stackAction;
    // the power mode for this interface to go to
    // valid only if stackAction == init/re-init; ignored for de-init
    TCPIP_MAC_POWER_MODE  powerMode;
    
}TCPIP_STACK_MODULE_CTRL;


TCPIP_NET_IF*         TCPIP_STACK_IPAddToNet(IPV4_ADDR* pIpAddress, bool useDefault);

TCPIP_NET_IF*         _TCPIPStackIpAddFromAnyNet(TCPIP_NET_IF* pNetIf, IPV4_ADDR* pIpAddress);


extern __inline__ bool __attribute__((always_inline)) _TCPIPStackIpAddFromLAN(TCPIP_NET_IF* pIf, const IPV4_ADDR* pIpAddress)
{
    return ((pIf->netIPAddr.Val ^ pIpAddress->Val) & pIf->netMask.Val) == 0;
}

int  TCPIP_STACK_NetIxGet(TCPIP_NET_IF* pNetIf);


uint32_t  TCPIP_STACK_NetAddressGet(TCPIP_NET_IF* pNetIf);

const IPV6_ADDR* TCPIP_STACK_NetStaticIPv6AddressGet(TCPIP_NET_IF* pNetIf, int* pPrefixLen);

const IPV6_ADDR* TCPIP_STACK_NetDefaultIPv6GatewayGet(TCPIP_NET_IF* pNetIf);


void  TCPIP_STACK_NetworkAddressSet(TCPIP_NET_IF* pNetIf, IPV4_ADDR* ipAddress, IPV4_ADDR* mask, bool setDefault);


uint32_t  TCPIP_STACK_NetMaskGet(TCPIP_NET_IF* pNetIf);

void  TCPIP_STACK_GatewayAddressSet(TCPIP_NET_IF* pNetIf, IPV4_ADDR* ipAddress);
void  TCPIP_STACK_PrimaryDNSAddressSet(TCPIP_NET_IF* pNetIf, IPV4_ADDR* ipAddress);

void  TCPIP_STACK_SecondaryDNSAddressSet(TCPIP_NET_IF* pNetIf, IPV4_ADDR* ipAddress);

TCPIP_NET_IF*         TCPIP_STACK_NetByAddress(IPV4_ADDR* pIpAddress);


bool  TCPIP_STACK_AddressIsOfNet( TCPIP_NET_IF* pNetIf, IPV4_ADDR* pIpAdd);

// detects net-directed bcast
bool  TCPIP_STACK_NetIsBcastAddress(TCPIP_NET_IF* pNetIf, IPV4_ADDR* pIpAdd);

// detects limited or net-directed bcast
bool  TCPIP_STACK_IsBcastAddress(TCPIP_NET_IF* pNetIf, IPV4_ADDR* pIpAdd);


bool  TCPIP_STACK_NetworkIsLinked(TCPIP_NET_IF* pNetIf);

TCPIP_NET_IF*         TCPIP_STACK_MACIdToNet(TCPIP_STACK_MODULE macId);

TCPIP_STACK_MODULE  TCPIP_STACK_NetMACIdGet(TCPIP_NET_IF* pNetIf);

TCPIP_NET_IF*     TCPIP_STACK_MacToNet(TCPIP_MAC_HANDLE hMac);

TCPIP_MAC_HANDLE  TCPIP_STACK_NetToMAC(TCPIP_NET_IF* pNetIf);

int         TCPIP_STACK_MacToNetIndex(TCPIP_MAC_HANDLE hMac);



const uint8_t*  TCPIP_STACK_NetMACAddressGet(TCPIP_NET_IF* pNetIf);

extern __inline__ TCPIP_NET_IF*  __attribute__((always_inline)) _TCPIPStackHandleToNet(TCPIP_NET_HANDLE hNet)
{
    // do some checking
    // if #debug enabled, etc
    return (TCPIP_NET_IF*)hNet; 
}

extern __inline__ bool  __attribute__((always_inline)) TCPIP_STACK_NetworkIsUp(TCPIP_NET_IF* pNetIf)
{
    if(pNetIf && pNetIf->Flags.bInterfaceEnabled)
    {
        return true;
    }
    return false;
}

// checks for valid up interface
extern __inline__ TCPIP_NET_IF*  __attribute__((always_inline)) _TCPIPStackHandleToNetUp(TCPIP_NET_HANDLE hNet)
{
    TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNet(hNet);
    if(TCPIP_STACK_NetworkIsUp(pNetIf))
    {
        return pNetIf;
    }

    return 0;
}

// checks for valid up and linked interface
TCPIP_NET_IF* _TCPIPStackHandleToNetLinked(TCPIP_NET_HANDLE hNet);

// returns a valid, linked interface, if any
// can start search with the default one
TCPIP_NET_IF* _TCPIPStackAnyNetLinked(bool useDefault);


// detects if an IP address is a local network
bool    TCPIP_STACK_IPAddressIsLocalNetwork(TCPIP_NET_IF* pNetIf, IPV4_ADDR destIpAdd);

// converts between an interface name and a MAC (TCPIP_STACK_MODULE) ID 
// TCPIP_MODULE_MAC_NONE - no MAC id could be found
TCPIP_STACK_MODULE    TCPIP_STACK_StringToMACId(const char* str);

// string (interface name) corresponding to the given MAC id.
// NULL if no such MAC id.
const char*     TCPIP_STACK_MACIdToString(TCPIP_STACK_MODULE macId);

// helper to select an address service for interface
TCPIP_STACK_ADDRESS_SERVICE_TYPE TCPIP_STACK_AddressServiceSelect(TCPIP_NET_IF* pNetIf, TCPIP_NETWORK_CONFIG_FLAGS configFlags);

// helper to decide if an address service can be started
bool    TCPIP_STACK_AddressServiceCanStart(TCPIP_NET_IF* pNetIf, TCPIP_STACK_ADDRESS_SERVICE_TYPE adSvcType);

// notification helper that an address service has some stop event
void    TCPIP_STACK_AddressServiceEvent(TCPIP_NET_IF* pNetIf, TCPIP_STACK_ADDRESS_SERVICE_TYPE adSvcType, TCPIP_STACK_ADDRESS_SERVICE_EVENT evType);

// address service default status
void    TCPIP_STACK_AddressServiceDefaultSet(TCPIP_NET_IF* pNetIf);

// helper to check if an address service is running
TCPIP_STACK_ADDRESS_SERVICE_TYPE _TCPIPStackAddressServiceIsRunning(TCPIP_NET_IF* pNetIf);

// stack configuration helpers
extern __inline__ void __attribute__((always_inline)) _TCPIPStackSetConfig(TCPIP_NET_IF* pNetIf, bool config)
{
    pNetIf->Flags.bInConfig = config;
}

extern __inline__ bool __attribute__((always_inline)) _TCPIPStackIsConfig(TCPIP_NET_IF* pNetIf)
{
    return pNetIf->Flags.bInConfig != 0;
}


void  _TCPIPStackSetConfigAddress(TCPIP_NET_IF* pNetIf, IPV4_ADDR* ipAddress, IPV4_ADDR* mask, bool config);

// finds an interface that has the IPv6 address
TCPIP_NET_IF* _TCPIPStackIPv6AddToNet(IPV6_ADDR* pIPv6Address, IPV6_ADDR_TYPE addType, bool useDefault);

// register a timeout handler with the stack manager
// returns 0 if failed, a valid handle otherwise
// if asyncPending is 0, then the asyncTmo is used (msec); 
// the entries are identified by the asyncHandler;
// a second call with the same asyncHandler will succeed and not create a new timer entry
tcpipAsyncHandle _TCPIPStackAsyncHandlerRegister(tcpipModuleAsyncHandler asyncHandler, tcpipModuleAsyncPending asyncPending, int16_t asyncTmoMs);


// changes the timeout parameters (asyncPending, asyncTmoMs) for a registered handler
// asyncTmo == 0 could be used to stop the timer without de-registration
bool           _TCPIPStackAsyncHandlerSetParams(tcpipAsyncHandle handle, tcpipModuleAsyncPending asyncPending, int16_t asyncTmoMs);


// de-registers a previous registered timeout handler
void           _TCPIPStackAsyncHandlerDeRegister(tcpipAsyncHandle handle); 

#endif  // _TCPIP_MANAGER_CONTROL_H_


