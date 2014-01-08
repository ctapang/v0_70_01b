/***********************************************************************
  Company:
    Microchip Technology Inc.
    
  File Name:
    drv_ethmac.h

  Summary:
    Ethernet MAC device driver interface file

  Description:
    Ethernet MAC Device Driver Interface
    
    The Ethernet MAC device driver provides a simple interface to manage
    the Ethernet peripheral. This file defines the interface definitions
    and prototypes for the Ethernet MAC driver.                         
  ***********************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _DRV_ETHMAC_H
#define _DRV_ETHMAC_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "driver/driver_common.h"
#include "peripheral/eth/plib_eth.h"

#include "system_config.h"

#include "driver/ethmac/drv_ethernet_flags.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/*****************************************************************************/
/* SYS_MODULE_OBJ

  Summary:
    Generic handle to any ISP system object.

  Description:
    Generic handle to any ISP system object.

  Remarks:
    None.
*/

#if !defined(_SYS_OBJ_HANDLE_)
    #define _SYS_OBJ_HANDLE_
    typedef uintptr_t SYS_OBJ_HANDLE;
    #define SYS_OBJ_HANDLE_INVALID  ( (SYS_OBJ_HANDLE) -1 )
    #define SYS_OBJ_HANDLE_STATIC   ( (SYS_OBJ_HANDLE)  0 )
#endif//#if !defined(SYS_OBJ_HANDLE)


// *****************************************************************************
/* Ethernet Driver Module Index Numbers

  Summary:
    Ethernet driver index definitions.

  Description:
    These constants provide Ethernet driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the DRV_ETHMAC_Initialize and
    DRV_ETHMAC_Open routines to identify the driver instance in use.
*/

#define DRV_ETHMAC_INDEX_0         0
#define DRV_ETHMAC_INDEX_1         1


// *****************************************************************************
/* Ethernet Driver Module Index Count

  Summary:
    Number of valid Ethernet driver indices.

  Description:
    This constant identifies number of valid Ethernet driver indices.

  Remarks:
    This constant should be used in place of hard-coded numeric literals.

    This value is derived from part-specific header files defined as part of the
    peripheral libraries.
*/

#define DRV_ETHMAC_INDEX_COUNT  ETH_NUMBER_OF_MODULES


// *****************************************************************************
/* Ethernet Controller Status Codes

  Summary:
    Defines the possible status codes of the Ethernet controller.

  Description:
    This enumeration defines the flags describing the status of the Ethernet
    controller.
*/

typedef enum
{
    // A packet is currently received
    ETH_ST_RXBUSY   /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // A packet is currently transmitted
    ETH_ST_TXBUSY   /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // Module is on or completing a transaction
    ETH_ST_BUSY     /*DOM-IGNORE-BEGIN*/ = 0x4 /*DOM-IGNORE-END*/

} ETH_MODULE_STATUS; /*DOM-IGNORE-BEGIN*/ /* in eth.h, eEthStat;  */ /*DOM-IGNORE-END*/


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - Client Level
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    TCPIP_MAC_RES       DRV_ETHMAC_PIC32MACSetup(TCPIP_MAC_MODULE_CTRL* const stackData, const TCPIP_MODULE_MAC_PIC32INT_CONFIG* initData);

  Summary:
    Supports PIC32 Ethernet MAC setup.

  Description:
    This function supports setup of the PIC32 Ethernet MAC.  Used by tcpip_module_manager.

  Precondition:
    DRV_ETHMAC_Open must have been called to obtain a valid opened device handle.

  Parameters:
    pStackData - Pointer to stack data
    initData  - Pointer to initialization data

  Returns:
    TCPIP_MAC_RES_OK if initialization completed; otherwise, error enumeration value.

  Example:
    <code>
    </code>

  Remarks:
    This function initializes the Ethernet controller, the MAC and the associated PHY.
    It should be called to be able to schedule any Ethernet transmit or receive operation.

*/
TCPIP_MAC_RES       DRV_ETHMAC_PIC32MACSetup(TCPIP_MAC_MODULE_CTRL* const stackData, const TCPIP_MODULE_MAC_PIC32INT_CONFIG* initData);


// *****************************************************************************
/* Function:
    TCPIP_MAC_RES DRV_ETHMAC_PIC32MACTeardown(const TCPIP_STACK_MODULE_CTRL* const pStackData )

  Summary:
    Supports PIC32 Ethernet MAC Teardown (opposite of setup).

  Description:
    This function supports teardown of the PIC32 Ethernet MAC (opposite of setup).  Used by tcpip_module_manager.

  Precondition:
    DRV_ETHMAC_PIC32MACSetup must have been called to setup the driver.

  Parameters:
    pStackData - Pointer to Stack Data

  Returns:
    TCPIP_MAC_RES_OK if initialization completed, error enumeration value otherwise.

  Example:
    <code>
    </code>

  Remarks:
    This function deinitializes the Ethernet controller, the MAC and the associated PHY.
    It should be called to be able to schedule any Ethernet transmit or receive operation.

*/
TCPIP_MAC_RES DRV_ETHMAC_PIC32MACTeardown(const TCPIP_MAC_MODULE_CTRL* const stackData );

/***************************************************************************************************************************
  Function:
       size_t DRV_ETHMAC_PIC32MACGetConfig(TCPIP_STACK_MODULE modId, void* configBuff, size_t buffSize, size_t* pConfigSize)
    
  Summary:
    Supports PIC32 Ethernet MAC by copying its configuration.
  Description:
    Supports PIC32 Ethernet MAC Teardown (opposite of Setup). Used by
    tcpip_module_manager.
  Conditions:
    Supports PIC32 Ethernet MAC by copying its configuration.
  Input:
    modId -        Module ID from TCPIP_STACK_MODULE enumeration, identifying
                   MAC
    configBuff -   Pointer to configuration buffer to be copied
    buffSize -     Size of configuration buffer provided by configBuff
    pConfigSize -  Pointer to size of configuration buffer copied
  Return:
    Size of configuration buffer copied.
  Example:
    <code>
    
    </code>
  Remarks:
    This function deinitializes the Ethernet controller, the MAC and the
    associated PHY. It should be called to be able to schedule any Ethernet
    transmit or receive operation.                                                                                          
  ***************************************************************************************************************************/
size_t DRV_ETHMAC_PIC32MACGetConfig(TCPIP_STACK_MODULE modId, void* configBuff, size_t buffSize, size_t* pConfigSize);

/**************************************************************************
  Function:
       TCPIP_MAC_HANDLE DRV_ETHMAC_PIC32MACOpen( TCPIP_STACK_MODULE macId )
    
  Summary:
    Opens a client instance of the PIC32 MAC Driver.
  Description:
    This function opens a client instance of the PIC32 MAC Driver. Used by
    tcpip_module_manager.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup should have been called.
  Input:
    macId -  MAC identification, from the TCPIP_STACK_MODULE enumeration
  Return:
    TCPIP_MAC_HANDLE - handle (pointer) to MAC client
  Example:
    <code>
    
    </code>
  Remarks:
    \ \                                                                    
  **************************************************************************/
TCPIP_MAC_HANDLE DRV_ETHMAC_PIC32MACOpen( TCPIP_STACK_MODULE macId );


/************************************************************************
  Function:
       TCPIP_MAC_RES DRV_ETHMAC_PIC32MACClose( TCPIP_STACK_MODULE macId )
    
  Summary:
    Closes a client instance of the PIC32 MAC Driver.
  Description:
    This function closes a client instance of the PIC32 MAC Driver.
  Conditions:
    DRV_ETHMAC_PIC32MACOpen should have been called.
  Input:
    macId -  MAC identification, from the TCPIP_STACK_MODULE enumeration
  Return:
    TCPIP_MAC_RES_OK if initialization completed; otherwise, the error
    enumeration value.
  Example:
    <code>
    
    </code>
  Remarks:
    \ \                                                                  
  ************************************************************************/

TCPIP_MAC_RES DRV_ETHMAC_PIC32MACClose( TCPIP_MAC_HANDLE hMac );


// *****************************************************************************
/* Function:
    bool DRV_ETHMAC_PIC32MACLinkCheck( TCPIP_MAC_HANDLE hMac )

  Summary:
    Checks current link status.

  Description:
    This function checks the link status, performing a MAC reconfiguration if
    the link went up after being down.

  Precondition:
    None.

  Parameters:
    hMac - Ethernet MAC client handle

  Returns:
    - true  - If the link is up
    - false - If the link is not up

  Example:
<code>
</code>

  Remarks:
    If auto negotiation is enabled the MAC we may have to be reconfigured.

*/

bool DRV_ETHMAC_PIC32MACLinkCheck( TCPIP_MAC_HANDLE hMac );


// *****************************************************************************
/* Function:
    bool DRV_ETHMAC_PIC32MACPowerMode( TCPIP_MAC_HANDLE hMac, TCPIP_MAC_POWER_MODE pwrMode )

  Summary:
    Powers down the Ethernet MAC.

  Description:
    This function powers down the Ethernet MAC.

  Precondition:
    None.

  Parameters:
    hMac - Ethernet MAC client handle
    pwrMode - Power Mode (?)

  Returns:
    None.

  Example:
<code>
</code>

  Remarks:

*/

bool DRV_ETHMAC_PIC32MACPowerMode( TCPIP_MAC_HANDLE hMac, TCPIP_MAC_POWER_MODE pwrMode );

/*********************************************************************************************************************
  Function:
        TCPIP_MAC_RES DRV_ETHMAC_PIC32MACRxFilterHashTableEntrySet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR* DestMACAddr)
    
  Summary:
    Calculates a CRC-32 and sets the appropriate bit in the ETHHTx
    registers.
  Description:
    This function calculates a CRC-32 using polynomial 0x4C11DB7 and then,
    using bits 28 through 23 of the CRC, sets the appropriate bit in the
    ETHHT0-ETHHT1 registers.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup() should have been called.
  Input:
    hMac -         Ethernet MAC client handle
    DestMACAddr -  6\-byte group destination MAC address to allow through
                   the Hash Table Filter. If DestMACAddr is set to '0000
                   0000 0000', the hash table will be cleared of all entries
                   and the filter will be disabled.
  Return:
    TCPIP_MAC_RES_OK if success, an error code otherwise.
  Example:
    <code>
    
    </code>
  Remarks:
    Sets the appropriate bit in the ETHHT0/1 registers to allow packets
    sent to DestMACAddr to be received and enabled the Hash Table receive
    filter
    
    There is no way to individually unset destination MAC addresses from
    the hash table since it is possible to have a hash collision and
    therefore multiple MAC addresses relying on the same hash table bit.
    The stack would have to individually store each 6 byte MAC address to
    support this feature, which would waste a lot of RAM and be unnecessary
    in most applications. As a simple compromise, you can call
    DRV_ETHMAC_PIC32MACRxFilterHashTableEntrySet() using a
    00-00-00-00-00-00 destination MAC address, which will clear the entire
    hash table and disable the hash table filter. This will allow you to
    then reads the necessary destination addresses.                                                                   
  *********************************************************************************************************************/
TCPIP_MAC_RES DRV_ETHMAC_PIC32MACRxFilterHashTableEntrySet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR* DestMACAddr);

/******************************************************************************************************
  Function:
        TCPIP_MAC_RES DRV_ETHMAC_PIC32MACPacketTx(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_PACKET * ptrPacket);
    
  Summary:
    A packet is submitted to the MAC driver for transmission.
  Description:
    This is the MAC transmit function. The MAC driver has to support
    \internal queueing! A packet is to be rejected only if it's not
    properly formatted. Otherwise it has to be scheduled for transmission
    in an internal queue!
    
    Once the packet is scheduled for transmission the MAC driver has to set
    the TCPIP_MAC_PKT_FLAG_QUEUED flag so that the stack is aware that this
    packet is under processing and cannot be modified!
    
    Once the packet is transmitted, the TCPIP_MAC_PKT_FLAG_QUEUED has to be
    cleared, the proper packet acknowledgement result (ackRes) has to be
    set and the packet acknowledgement function (ackFunc) has to be called.
    It is implementation dependant if all these steps are implemented as
    part of the ackFunc itself or as discrete steps.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup() should have been called.
  Input:
    hMac -       Ethernet MAC client handle
    ptrPacket -  pointer to a TCPIP_MAC_PACKET that's completely formatted
                 and ready to be transmitted over the network
  Return:
    TCPIP_MAC_RES_OK if the packet transmitted, TCPIP_MAC_RES error code
    for not properly formatted packets, etc.
  Example:
    <code>
    
    </code>
                                                                                                       
  ******************************************************************************************************/
TCPIP_MAC_RES DRV_ETHMAC_PIC32MACPacketTx(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_PACKET * ptrPacket);


// *****************************************************************************
/* Function:
    TCPIP_MAC_PACKET* DRV_ETHMAC_PIC32MACPacketRx (TCPIP_MAC_HANDLE hMac, TCPIP_MAC_RES* pRes, const TCPIP_MAC_PACKET_RX_STAT** ppPktStat);

  Summary:
    A packet is returned if  such a pending packet exists.

  Description:
    This is the MAC receive function.
    
    Once a pending packet is available in the MAC driver internal RX queues
    this function will dequeue the packet and hand it over to the
    MAC driver's client - i.e. the stack - for further processing.


    The flags for a RX packet have to be updated by the MAC driver:
        - TCPIP_MAC_PKT_FLAG_RX has to be set
          If the MAC supports it, it should set: 
            - TCPIP_MAC_PKT_FLAG_UNICAST has to be set if that packet is a unicast packet
            - TCPIP_MAC_PKT_FLAG_BCAST has to be set if that packet is a broadcast packet
            - TCPIP_MAC_PKT_FLAG_MCAST has to be set if that packet is a multicast packet
        - TCPIP_MAC_PKT_FLAG_QUEUED has to be set
        - TCPIP_MAC_PKT_FLAG_SPLIT has to be set if the packet has multiple data segments

    Additional information about the packet is available by providing the pRes and
    ppPktStat fields.

  Precondition:
    DRV_ETHMAC_PIC32MACSetup() should have been called.

  Parameters:
    hMac        - Ethernet MAC client handle
    pRes        - optional pointer to an address that will receive an additional
                  result associated with the operation.
                  Can be 0 if not needed.
    ppPktStat   - optional pointer to an address that will receive the received
                  packet status.
                  Note that this pointer cannot be used once the packet
                  acknowledgement function was called.
                  Can be 0 if not needed.


  Returns:
    a valid pointer to an available RX packet
    0 if no packet pending/available

  Example:
<code>
</code>

  Remarks:
    The MAC driver dequeues and return to the caller just one single packet. 

    Once the higher level layers in the stack are done with processing the RX packet,
    they have to call the corresponding packet acknowledgement function
    that tells the MAC driver that it can resume control of that packet.

    Once the stack modules are done processing the RX packets and the acknowledge function is called
    the MAC driver will reuse the RX packets.

    The MAC driver may use the DRV_ETHMAC_PIC32MACProcess() for obtaining new RX packets if needed.

*/
TCPIP_MAC_PACKET* DRV_ETHMAC_PIC32MACPacketRx (TCPIP_MAC_HANDLE hMac, TCPIP_MAC_RES* pRes, const TCPIP_MAC_PACKET_RX_STAT** ppPktStat);


/*****************************************************************************
  Function:
        TCPIP_MAC_RES DRV_ETHMAC_PIC32MACProcess(TCPIP_MAC_HANDLE hMac);
    
  Summary:
    MAC periodic processing function.
  Description:
    This is a function that allows for internal processing by the MAC
    driver. It is meant for processing that cannot be done from within ISR.
    
    Some of the processing that this is intended for:
      * the MAC driver can process its pending TX queues (although it
        should do that preferably from within the TX ISR)
      * RX buffers replenishing. If the number of packets in the RX queue
        falls below a specified limit, the MAC driver can use this function to
        allocate some extra RX packets. Similarly, if there are too many
        allocated RX packets, the MAC driver can free some of them.
    
    Normally this function will be called in response to an TX and/or RX
    event signalled by the driver. This is specified by the MAC driver at
    initialization time using TCPIP_MAC_MODULE_CTRL.
    
    An alternative approach is that the MAC driver uses a system service to
    create a timer signal that will call the TCPIP_MAC_Process on a
    periodic basis.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup() should have been called.
  Input:
    hMac -  Ethernet MAC client handle
  Return:
    TCPIP_MAC_RES_OK if all processing went on OK a TCPIP_MAC_RES error
    code if processing failed for some reason
  Example:
    <code>
    
    </code>
  Remarks:
    The MAC driver may use the DRV_ETHMAC_PIC32MACProcess() for obtaining
    new RX packets if needed.                                                 
  *****************************************************************************/
TCPIP_MAC_RES DRV_ETHMAC_PIC32MACProcess(TCPIP_MAC_HANDLE hMac);



/***********************************************************************************************************
  Function:
        bool DRV_ETHMAC_PIC32MACEventMaskSet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable);
    
  Summary:
    Enables the MAC events.
  Description:
    This function sets the enabled events. Multiple events can be ORed
    together. All events that are set will be added to the notification
    process. The old events will be disabled. The stack (or stack user) has
    to catch the events that are notified and process them:
      * The stack should process the
        TCPIP_MAC_EV_RX_PKTPEND/TCPIP_MAC_EV_RX_DONE, TCPIP_MAC_EV_TX_DONE
        transfer events
      * Process the specific condition and acknowledge them calling
        DRV_ETHMAC_PIC32MACEventAcknowledge() so that they can be re&#45;enabled.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup() should have been called.
  Input:
    hMac -       Ethernet MAC client handle
    macEvMask -  events the user of the stack wants to add/delete for
                 notification
    enable -     if true, the events will be enabled, else disabled
  Return:
    always true, operation succeeded.
  Example:
    <code>
        DRV_ETHMAC_PIC32MACEventMaskSet( hMac, TCPIP_MAC_EV_RX_OVFLOW | TCPIP_MAC_EV_RX_BUFNA, true );
    </code>
  Remarks:
    The event notification system enables the user of the TCP/IP stack to
    call into the stack for processing only when there are relevant events
    rather than being forced to periodically call from within a loop.
    
    If the notification events are nill, the interrupt processing will be
    disabled. Otherwise, the event notification will be enabled and the
    interrupts relating to the requested events will be enabled.
    
    \Note that once an event has been caught by the stack ISR (and reported
    if a notification handler is in place) it will be disabled until the
    DRV_ETHMAC_PIC32MACEventAcknowledge() is called.                                                        
  ***********************************************************************************************************/
bool DRV_ETHMAC_PIC32MACEventMaskSet(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable);


/****************************************************************************************************
  Function:
        bool    DRV_ETHMAC_PIC32MACEventAcknowledge(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT tcpAckEv);
    
        Acknowledges and re-enables processed events.
    
  Description:
    This function acknowledges and re-enables processed events. Multiple
    events can be ORed together as they are processed together. The events
    acknowledged by this function should be the events that have been
    retrieved from the stack by calling
    DRV_ETHMAC_PIC32MACEventPendingGet() or have been passed to the user by
    the stack using the notification handler
    (PIC32MACEventSetNotifyHandler()) and have been processed and have to
    be re-enabled.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup() should have been called.
  Input:
    hMac -      Ethernet MAC client handle
    tcpAckEv -  the events that the user processed and need to be re\-enabled
  Return:
    true if events acknowledged false if no events to be acknowledged
  Example:
    <code>
        DRV_ETHMAC_PIC32MACEventAcknowledge( hMac, stackNewEvents );
    </code>
  Remarks:
    All events should be acknowledged, in order to be re-enabled.
    
    Some events are fatal errors and should not be acknowledged
    (TCPIP_MAC_EV_RX_BUSERR, TCPIP_MAC_EV_TX_BUSERR). Stack
    re-initialization is needed under such circumstances.
    
    Some events are just system/application behavior and they are intended
    only as simple info (TCPIP_MAC_EV_RX_OVFLOW, TCPIP_MAC_EV_RX_BUFNA,
    TCPIP_MAC_EV_TX_ABORT, TCPIP_MAC_EV_RX_ACT).
    
    The TCPIP_MAC_EV_RX_FWMARK and TCPIP_MAC_EV_RX_EWMARK events are part
    of the normal flow control operation (if auto flow control was
    enabled). They should be enabled alternatively, if needed.
    
    The events are persistent. They shouldn't be re-enabled unless they
    have been processed and the condition that generated them was removed.
    Re-enabling them immediately without proper processing will have
    dramatic effects on system performance.                                                          
  ****************************************************************************************************/
bool    DRV_ETHMAC_PIC32MACEventAcknowledge(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT tcpAckEv);



/******************************************************************************
  Function:
      TCPIP_MAC_EVENT DRV_ETHMAC_PIC32MACEventPendingGet(TCPIP_MAC_HANDLE hMac)
    
  Summary:
    \Returns the currently pending events.
  Description:
    This function returns the currently pending events belonging to a
    group. Multiple events can be ORed together as they accumulate. The
    stack should be called for processing whenever a stack managed event
    (TCPIP_MAC_EV_RX_PKTPEND, TCPIP_MAC_EV_TX_DONE) is present. The other,
    non critical events, may not be managed by the stack and passed to an
    user. They will have to be eventually acknowledged if re-enabling is
    needed.
  Conditions:
    DRV_ETHMAC_PIC32MACSetup should have been called.
  Input:
    hMac -  parameter identifying the intended MAC client
  Return:
    The currently stack pending events.
  Example:
    <code>
    TCPIP_MAC_EVENT currEvents = DRV_ETHMAC_PIC32MACEventPendingGet( hMac);
    </code>
  Remarks:
    This is the preferred method to get the current pending MAC events. The
    stack maintains a proper image of the events from their occurrence to
    their acknowledgement.
    
    Even with a notification handler in place it's better to use this
    \function to get the current pending events rather than using the
    events passed by the notification handler which could be stale.
    
    The events are persistent. They shouldn't be re-enabled unless they
    have been processed and the condition that generated them was removed.
    Re-enabling them immediately without proper processing will have
    dramatic effects on system performance.
    
    The returned value is just a momentary value. The pending events can
    change any time.                                                           
  ******************************************************************************/
TCPIP_MAC_EVENT DRV_ETHMAC_PIC32MACEventPendingGet(TCPIP_MAC_HANDLE hMac);



#endif // #ifndef _DRV_ETHMAC_H

/*******************************************************************************
 End of File
*/

