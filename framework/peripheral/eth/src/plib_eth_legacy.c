/*******************************************************************************
  Ethernet Library Interface Definition for Legacy Software Support

  Summary:
    This file contains the Application Program Interface (API) definition  for
    the Ethernet peripheral library.

  Description:
    This library provides a low-level abstraction of the Ethernet module
    on Microchip PIC32MX family microcontrollers with a convenient C language
    interface.  It can be used to simplify low-level access to the module
    without the necessity of interacting directly with the module's registers,
    thus hiding differences from one microcontroller variant to another.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:      plib_eth_legacy.c
Processor:      PIC32MX
Compiler:       Microchip MPLAB C32 v1.00 or higher

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
//DOM-IGNORE-END

#include <string.h>
#if defined (__PIC32MX__)
#include <peripheral/int.h>
#endif
#include "peripheral/eth/src/plib_eth_legacy.h"

#if defined(__PIC32MZ__)
  #define _ETH // All PIC32MZ devices have Ethernet
#endif

#ifdef _ETH // The Ethernet device is present

// *****************************************************************************
// *****************************************************************************
// Section: PLIB Legacy Functions
// *****************************************************************************
// *****************************************************************************
/*
        Harmony Ethernet MAC Driver                     Legacy PLIB
    ===============================         ============================
    DRV_ETHMAC_LegacyClose                  EthClose
    DRV_ETHMAC_LegacyDescriptorGetBuffer    EthDescriptorGetBuffer
    DRV_ETHMAC_LegacyDescriptorsPoolAdd     EthDescriptorsPoolAdd
    DRV_ETHMAC_LegacyDescriptorsPoolCleanUp EthDescriptorsPoolCleanUp
    DRV_ETHMAC_LegacyDescriptorsPoolRemove  EthDescriptorsPoolRemove
    DRV_ETHMAC_LegacyInit                   EthInit
    DRV_ETHMAC_LegacyMACOpen                EthMACOpen
    DRV_ETHMAC_LegacyRxAcknowledgeBuffer    EthRxAcknowledgeBuffer
    DRV_ETHMAC_LegacyRxAcknowledgePacket    EthRxAcknowledgePacket
    DRV_ETHMAC_LegacyRxBuffersAppend        EthRxBuffersAppend
    DRV_ETHMAC_LegacyRxGetBuffer            EthRxGetBuffer
    DRV_ETHMAC_LegacyRxGetPacket            EthRxGetPacket
    DRV_ETHMAC_LegacyTxAcknowledgeBuffer    EthTxAcknowledgeBuffer
    DRV_ETHMAC_LegacyTxAcknowledgePacket    EthTxAcknowledgePacket
    DRV_ETHMAC_LegacyTxGetBufferStatus      EthTxGetBufferStatus
    DRV_ETHMAC_LegacyTxGetPacketStatus      EthTxGetPacketStatus
    DRV_ETHMAC_LegacyTxSendBuffer           EthTxSendBuffer
    DRV_ETHMAC_LegacyTxSendPacket           EthTxSendPacket

           Harmony Ethernet PLIB                       Legacy PLIB
    ===============================         ============================
    PLIB_ETH_EventsClr                EthEventsClr
    PLIB_ETH_EventsEnableClr          EthEventsEnableClr
    PLIB_ETH_EventsEnableGet          EthEventsEnableGet
    PLIB_ETH_EventsEnableSet          EthEventsEnableSet
    PLIB_ETH_EventsEnableWrite        EthEventsEnableWrite
    PLIB_ETH_EventsGet                EthEventsGet
    PLIB_ETH_MACGetAddress            EthMACGetAddress
    PLIB_ETH_MACSetAddress            EthMACSetAddress
    PLIB_ETH_MACSetMaxFrame           EthMACSetMaxFrame
    PLIB_ETH_RxFiltersClr             EthRxFiltersClr
    PLIB_ETH_RxFiltersHTSet           EthRxFiltersHTSet
    PLIB_ETH_RxFiltersPMClr           EthRxFiltersPMClr
    PLIB_ETH_RxFiltersPMSet           EthRxFiltersPMSet
    PLIB_ETH_RxFiltersSet             EthRxFiltersSet
    PLIB_ETH_RxFiltersWrite           EthRxFiltersWrite
    PLIB_ETH_RxSetBufferSize          EthRxSetBufferSize
    PLIB_ETH_StatRxAlgnErrCnt         EthStatRxAlgnErrCnt
    PLIB_ETH_StatRxFcsErrCnt          EthStatRxFcsErrCnt
    PLIB_ETH_StatRxOkCnt              EthStatRxOkCnt
    PLIB_ETH_StatRxOvflCnt            EthStatRxOvflCnt
    PLIB_ETH_StatTxMColCnt            EthStatTxMColCnt
    PLIB_ETH_StatTxOkCnt              EthStatTxOkCnt
    PLIB_ETH_StatTxSColCnt            EthStatTxSColCnt

            Legacy PLIB                                   Harmony
    ============================            ===============================
    EthClose                                DRV_ETHMAC_LegacyClose
    EthDescriptorGetBuffer                  DRV_ETHMAC_LegacyDescriptorGetBuffer
    EthDescriptorsPoolAdd                   DRV_ETHMAC_LegacyDescriptorsPoolAdd
    EthDescriptorsPoolCleanUp               DRV_ETHMAC_LegacyDescriptorsPoolCleanUp
    EthDescriptorsPoolRemove                DRV_ETHMAC_LegacyDescriptorsPoolRemove
    EthEventsClr                            PLIB_ETH_EventsClr
    EthEventsEnableClr                      PLIB_ETH_EventsEnableClr
    EthEventsEnableGet                      PLIB_ETH_EventsEnableGet
    EthEventsEnableSet                      PLIB_ETH_EventsEnableSet
    EthEventsEnableWrite                    PLIB_ETH_EventsEnableWrite
    EthEventsGet                            PLIB_ETH_EventsGet
    EthInit                                 DRV_ETHMAC_LegacyInit
    EthMACGetAddress                        PLIB_ETH_MACGetAddress
    EthMACOpen                              DRV_ETHMAC_LegacyMACOpen
    EthMACSetAddress                        PLIB_ETH_MACSetAddress
    EthMACSetMaxFrame                       PLIB_ETH_MACSetMaxFrame
    EthRxAcknowledgeBuffer                  DRV_ETHMAC_LegacyRxAcknowledgeBuffer
    EthRxAcknowledgePacket                  DRV_ETHMAC_LegacyRxAcknowledgePacket
    EthRxBuffersAppend                      DRV_ETHMAC_LegacyRxBuffersAppend
    EthRxFiltersClr                         PLIB_ETH_RxFiltersClr
    EthRxFiltersHTSet                       PLIB_ETH_RxFiltersHTSet
    EthRxFiltersPMClr                       PLIB_ETH_RxFiltersPMClr
    EthRxFiltersPMSet                       PLIB_ETH_RxFiltersPMSet
    EthRxFiltersSet                         PLIB_ETH_RxFiltersSet
    EthRxFiltersWrite                       PLIB_ETH_RxFiltersWrite
    EthRxGetBuffer                          DRV_ETHMAC_LegacyRxGetBuffer
    EthRxGetPacket                          DRV_ETHMAC_LegacyRxGetPacket
    EthRxSetBufferSize                      PLIB_ETH_RxSetBufferSize
    EthStatRxAlgnErrCnt                     PLIB_ETH_StatRxAlgnErrCnt
    EthStatRxFcsErrCnt                      PLIB_ETH_StatRxFcsErrCnt
    EthStatRxOkCnt                          PLIB_ETH_StatRxOkCnt
    EthStatRxOvflCnt                        PLIB_ETH_StatRxOvflCnt
    EthStatTxMColCnt                        PLIB_ETH_StatTxMColCnt
    EthStatTxOkCnt                          PLIB_ETH_StatTxOkCnt
    EthStatTxSColCnt                        PLIB_ETH_StatTxSColCnt
    EthTxAcknowledgeBuffer                  DRV_ETHMAC_LegacyTxAcknowledgeBuffer
    EthTxAcknowledgePacket                  DRV_ETHMAC_LegacyTxAcknowledgePacket
    EthTxGetBufferStatus                    DRV_ETHMAC_LegacyTxGetBufferStatus
    EthTxGetPacketStatus                    DRV_ETHMAC_LegacyTxGetPacketStatus
    EthTxSendBuffer                         DRV_ETHMAC_LegacyTxSendBuffer
    EthTxSendPacket                         DRV_ETHMAC_LegacyTxSendPacket

*/


/****************************************************************************
 * Function:        PLIB_ETH_MACSetAddress
 *****************************************************************************/
void PLIB_ETH_MACSetAddress(ETH_MODULE_ID index,unsigned char bAddress[6])
{
    PLIB_ETH_StationAddressSet(index,1,bAddress[0]);
    PLIB_ETH_StationAddressSet(index,2,bAddress[1]);
    PLIB_ETH_StationAddressSet(index,3,bAddress[2]);
    PLIB_ETH_StationAddressSet(index,4,bAddress[3]);
    PLIB_ETH_StationAddressSet(index,5,bAddress[4]);
    PLIB_ETH_StationAddressSet(index,6,bAddress[5]);
}


/****************************************************************************
 * Function:        PLIB_ETH_MACGetAddress
 *****************************************************************************/
void PLIB_ETH_MACGetAddress(ETH_MODULE_ID index,unsigned char bAddress[6])
{
    *bAddress++ = PLIB_ETH_StationAddressGet(index,1);
    *bAddress++ = PLIB_ETH_StationAddressGet(index,2);
    *bAddress++ = PLIB_ETH_StationAddressGet(index,3);
    *bAddress++ = PLIB_ETH_StationAddressGet(index,4);
    *bAddress++ = PLIB_ETH_StationAddressGet(index,5);
    *bAddress   = PLIB_ETH_StationAddressGet(index,6);
}


/****************************************************************************
 * Function:        PLIB_ETH_MACSetMaxFrame
 *****************************************************************************/
void PLIB_ETH_MACSetMaxFrame(ETH_MODULE_ID index,unsigned short maxFrmSz)
{
    PLIB_ETH_MaxFrameLengthSet(index,maxFrmSz);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersSet
 *****************************************************************************/
void PLIB_ETH_RxFiltersSet(ETH_MODULE_ID index,ETH_RX_FILTERS rxFilters)
{
    PLIB_ETH_ReceiveFilterEnable(index,rxFilters);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersClr
 *****************************************************************************/
void PLIB_ETH_RxFiltersClr(ETH_MODULE_ID index,ETH_RX_FILTERS rxFilters)
{
    PLIB_ETH_ReceiveFilterDisable(index,rxFilters);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersWrite
 *****************************************************************************/
void PLIB_ETH_RxFiltersWrite(ETH_MODULE_ID index,ETH_RX_FILTERS rxFilters)
{
    PLIB_ETH_ReceiveFilterEnable(index,rxFilters);
    PLIB_ETH_ReceiveFilterDisable(index,~rxFilters);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersHTSet
 *****************************************************************************/
void PLIB_ETH_RxFiltersHTSet(ETH_MODULE_ID index,uint64_t htable)
{
    PLIB_ETH_HashTableSet(index,htable);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersPMSet
 *****************************************************************************/
void PLIB_ETH_RxFiltersPMSet(ETH_MODULE_ID index,
                                   ETH_PMATCH_MODE mode,
                                   uint64_t matchMask,
                                   unsigned int matchOffs,
                                   unsigned int matchChecksum)
{
    PLIB_ETH_PatternMatchModeSet(index,ETH_PATTERN_MATCH_DISABLED);

    PLIB_ETH_PatternMatchSet(index,matchMask);
    PLIB_ETH_PatternMatchOffsetSet(index,matchOffs);
    PLIB_ETH_PatternMatchChecksumSet(index,matchChecksum);

    if(mode&ETH_FILT_PMATCH_INVERT)
    {
        PLIB_ETH_ReceiveFilterEnable(index,ETH_PATTERN_MATCH_INVERSION);
    }
    else
    {
        PLIB_ETH_ReceiveFilterDisable(index,ETH_PATTERN_MATCH_INVERSION);
    }

 // Enable Pattern Match mode
    PLIB_ETH_PatternMatchModeSet(index,mode&(~ETH_FILT_PMATCH_INVERT));
}


/****************************************************************************
 * Function:        PLIB_ETH_RxFiltersPMClr
 *****************************************************************************/
void PLIB_ETH_RxFiltersPMClr(ETH_MODULE_ID index)
{
    PLIB_ETH_PatternMatchModeSet(index,(uint64_t)0);
}


/*********************************************************************
 * Function:        void PLIB_ETH_EventsEnableSet(ETH_LEGACY_EVENTS eEvents)
 ********************************************************************/
void PLIB_ETH_EventsEnableSet(ETH_MODULE_ID index,ETH_LEGACY_EVENTS eEvents)
{
    PLIB_ETH_InterruptSourceEnable(index,eEvents);
}


/*********************************************************************
 * Function:        void PLIB_ETH_EventsEnableClr(ETH_LEGACY_EVENTS eEvents)
 ********************************************************************/
void PLIB_ETH_EventsEnableClr(ETH_MODULE_ID index,ETH_LEGACY_EVENTS eEvents)
{
    PLIB_ETH_InterruptSourceDisable(index,eEvents);
}


/*********************************************************************
 * Function:        void PLIB_ETH_EventsEnableWrite(ETH_LEGACY_EVENTS eEvents)
 ********************************************************************/
void PLIB_ETH_EventsEnableWrite(ETH_MODULE_ID index,ETH_LEGACY_EVENTS eEvents)
{
    PLIB_ETH_InterruptSourceEnable(index,eEvents);
    PLIB_ETH_InterruptSourceDisable(index,~eEvents);
}


/*********************************************************************
 * Function:        ETH_LEGACY_EVENTS PLIB_ETH_EventsEnableGet(void)
 ********************************************************************/
ETH_LEGACY_EVENTS PLIB_ETH_EventsEnableGet(ETH_MODULE_ID index)
{
    return PLIB_ETH_InterruptSourcesGet(index);
}


/*******************************************************************************
  Function:
    void PLIB_ETH_EventsClr ( ETH_MODULE_ID index, ETH_LEGACY_EVENTS eEvents )
 */
void PLIB_ETH_EventsClr(ETH_MODULE_ID index,ETH_LEGACY_EVENTS eEvents)
{
    PLIB_ETH_InterruptClear(index,eEvents);
}

/*******************************************************************************
  Function:
    ETH_LEGACY_EVENTS PLIB_ETH_EventsGet ( ETH_MODULE_ID index )
 */

ETH_LEGACY_EVENTS __attribute__((always_inline)) PLIB_ETH_EventsGet(ETH_MODULE_ID index)
{
    return PLIB_ETH_InterruptsGet(index);
}


/****************************************************************************
 * Function:        PLIB_ETH_RxSetBufferSize
 *****************************************************************************/
ETH_RESULT_CODE PLIB_ETH_RxSetBufferSize(ETH_MODULE_ID index,int rxBuffSize)
{
    rxBuffSize/=16;     // truncate
    if(!rxBuffSize)
    {
        return ETH_RES_RX_SIZE_ERR;
    }

    PLIB_ETH_ReceiveBufferSizeSet(index,rxBuffSize);

    return ETH_RES_OK;
}


#endif  // _ETH
