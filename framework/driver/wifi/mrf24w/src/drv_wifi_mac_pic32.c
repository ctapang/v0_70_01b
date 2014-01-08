/*******************************************************************************
  MRF24W Driver Medium Access Control (MAC) Layer

  File Name:  
    drv_wifi_mac_pic32.c  
  
  Summary:
    Module for Microchip TCP/IP Stack PIC32 implementation
    for multiple MAC support
    
  Description:
*******************************************************************************/

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


#include "tcpip/src/tcpip_private.h"



// Compile only for PIC32MX MRF24W MAC interface
#if (defined(__PIC32MZ__) && defined(TCPIP_IF_MRF24W))||(defined(__PIC32MX__) && defined(TCPIP_IF_MRF24W))||( defined(__dsPIC33F__) && defined(TCPIP_IF_MRF24W))||( defined(__PIC24F__) && defined(TCPIP_IF_MRF24W))
#include "drv_wifi_mac.h"



// function proto
static TCPIP_MAC_RES          mrf24w_MACClose(TCPIP_MAC_HANDLE hMac);
static bool                   mrf24w_MACCheckLink(TCPIP_MAC_HANDLE hMac);
static TCPIP_MAC_RES          mrf24w_MACRxFilterSetHashTableEntry(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR* DestMACAddr);
static bool                   mrf24w_MACPowerMode(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_POWER_MODE pwrMode);
static TCPIP_MAC_RES          mrf24w_MACTxPacket(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_PACKET * ptrPacket);
static TCPIP_MAC_PACKET *     mrf24w_MACRxPacket (TCPIP_MAC_HANDLE hMac, TCPIP_MAC_RES* pRes, const TCPIP_MAC_PACKET_RX_STAT** ppPktStat);
static TCPIP_MAC_RES          mrf24w_MACProcess(TCPIP_MAC_HANDLE hMac);
#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)

static bool                   mrf24w_MACEventSetMask(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable);
static bool                   mrf24w_MACEventAcknowledge(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents);
static TCPIP_MAC_EVENT        mrf24w_MACEventGetPending(TCPIP_MAC_HANDLE hMac);

#endif  // (TCPIP_STACK_USE_EVENT_NOTIFICATION)

static void     mrf24w_MACDeinitialize(MRF24W_MAC_DCPT* pDcpt );

// the PIC32 MRF24W MAC descriptor
// no support for multiple instances
static const TCPIP_MAC_OBJECT _pic32_mrf24w_mac_obj = 
{
    mrf24w_MACClose,
    mrf24w_MACCheckLink,
    mrf24w_MACRxFilterSetHashTableEntry,
    mrf24w_MACPowerMode,
    mrf24w_MACTxPacket,
    mrf24w_MACRxPacket,
    mrf24w_MACProcess,
#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
    mrf24w_MACEventSetMask,
    mrf24w_MACEventAcknowledge,
    mrf24w_MACEventGetPending,
#endif  // (TCPIP_STACK_USE_EVENT_NOTIFICATION)
};

// only one hardware instance for now!
static MRF24W_MAC_DCPT _pic32_mrf24w_mac_dcpt[1] = 
{
    {
        &_pic32_mrf24w_mac_obj,
        // specific PIC32 MAC data 
        0,                                  // isOpen
    }
};


static TCPIP_MAC_MODULE_CTRL g_p_stackData;

const TCPIP_MAC_MODULE_CTRL * GetStackData()
{
    return &g_p_stackData;
}


/*
 * interface functions
 *
*/
extern void Isp_SpiClose(void);
static bool g_once = false;

TCPIP_MAC_RES MRF24W_MACInitialize(TCPIP_MAC_MODULE_CTRL* const stackData, const TCPIP_MODULE_MAC_MRF24W_CONFIG* initData)
{
    MRF24W_MAC_DCPT* pDcpt;
    TCPIP_MAC_RES    res;

    pDcpt = _pic32_mrf24w_mac_dcpt + 0; // no other instance supported
    if(pDcpt->isOpen != 0)
    {
        return TCPIP_MAC_RES_IS_BUSY;     // have a client connected
    }

    // this function is called repeatedly during init, but we only want stuff in
    // this block called once.
    if (g_once == false)
    {
        g_once = true;
        // save pointer to stack data
        g_p_stackData = *stackData;

        if(stackData->moduleId != TCPIP_MODULE_MAC_MRF24W)
        {
            return TCPIP_MAC_RES_TYPE_ERR;      // no other type supported
        }

        #if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
        if(MRF24W_MACEventInit(pDcpt, stackData->eventF, stackData->eventParam, WIFI_EVENT_IPL, WIFI_EVENT_SIPL) != TCPIP_MAC_RES_OK)
        {
            return TCPIP_MAC_RES_INIT_FAIL;
        }
        #endif

    }

    res =  MRF24W_MACInit(stackData, initData);

    if((res != TCPIP_MAC_RES_OK) && (res != TCPIP_MAC_RES_PENDING))
    {
        mrf24w_MACDeinitialize(pDcpt);
    }

    if(res == TCPIP_MAC_RES_OK)
    {
        stackData->processFlags = (TCPIP_MAC_PROCESS_FLAG_RX | TCPIP_MAC_PROCESS_FLAG_TX); 
        memcpy(stackData->ifPhyAddress.v, g_p_stackData.ifPhyAddress.v, sizeof(stackData->ifPhyAddress));
    }
    
    return res;
}

TCPIP_MAC_RES MRF24W_MACDeinitialize(const TCPIP_MAC_MODULE_CTRL* const stackData )
{
    if(stackData->moduleId != TCPIP_MODULE_MAC_MRF24W)
    {
        return TCPIP_MAC_RES_TYPE_ERR;      // no other type supported
    }

    mrf24w_MACDeinitialize(_pic32_mrf24w_mac_dcpt + 0);   // no other instance supported

    g_once = false;

    return TCPIP_MAC_RES_OK;

}

size_t MRF24W_MACGetConfig(TCPIP_STACK_MODULE modId, void* configBuff, size_t buffSize, size_t* pConfigSize)
{

    if(pConfigSize)
    {
        *pConfigSize =  (modId == TCPIP_MODULE_MAC_MRF24W)?sizeof(TCPIP_MODULE_MAC_MRF24W_CONFIG):0;
    }

    if(modId == TCPIP_MODULE_MAC_MRF24W)
    {
        if(configBuff && buffSize >= sizeof(TCPIP_MODULE_MAC_MRF24W_CONFIG))
        {   // can copy the data
            #if 0
            avoid warnings until fixed
                    
            TCPIP_MODULE_MAC_MRF24W_CONFIG* pWiFiConfig = (TCPIP_MODULE_MAC_MRF24W_CONFIG*)configBuff;
            MRF24W_MAC_DCPT* pMacD = _pic32_mrf24w_mac_dcpt + 0; // no other instance supported
            #endif
        
            // TODO aa: fill in the pWiFiConfig fields from pMacD


            return sizeof(TCPIP_MODULE_MAC_MRF24W_CONFIG);
        }

        return 0;
    }

    return -1;  // unknown module
}

TCPIP_MAC_HANDLE MRF24W_MACOpen( TCPIP_STACK_MODULE macId )
{
    MRF24W_MAC_DCPT* pMacD;
    TCPIP_MAC_HANDLE    hMac = 0;

    if(macId == TCPIP_MODULE_MAC_MRF24W)
    {
        pMacD = _pic32_mrf24w_mac_dcpt + 0; // no other instance supported
        if((pMacD->isOpen) == 0)
        {   // only one client for now
            pMacD->isOpen = 1;
            hMac = pMacD;
        }
    }
   
    return hMac;
}


static TCPIP_MAC_RES mrf24w_MACClose(TCPIP_MAC_HANDLE hMac)
{
    MRF24W_MAC_DCPT* pMacD = (MRF24W_MAC_DCPT*)hMac;

    pMacD->isOpen = 0;

    return TCPIP_MAC_RES_OK;


}

/****************************************************************************
 * Function:        mrf24w_MACCheckLink
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          true if the link is up
 *                  false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function periodically checks the link status
 *                  performing the MAC reconfiguration if the link went up
 *                  after being down.
 *
 * Note:            If auto negotiation is enabled the MAC we may have to be reconfigured.
 *****************************************************************************/
static bool mrf24w_MACCheckLink(TCPIP_MAC_HANDLE hMac)
{
    // TODO aa: update!
    return MRF24W_MACCheckLink();
    //return true;
}


static TCPIP_MAC_RES mrf24w_MACRxFilterSetHashTableEntry(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_ADDR* DestMACAddr)
{
    return TCPIP_MAC_RES_OK;
}


static bool mrf24w_MACPowerMode(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_POWER_MODE pwrMode)
{
    switch(pwrMode)
    {
        case TCPIP_MAC_POWER_FULL:
            MRF24W_MACPowerUp();
            break;

        case TCPIP_MAC_POWER_DOWN:
            MRF24W_MACPowerDown();
            break;

        default:
            return false;
    }

    return true;
}


static TCPIP_MAC_RES mrf24w_MACTxPacket(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_PACKET * ptrPacket)
{
    TCPIP_MAC_RES res;

    res = MRF24W_TxPacket(ptrPacket);
    return res;
}

#include "tcpip/src/system/system_userio.h"   // delete later
static TCPIP_MAC_PACKET* mrf24w_MACRxPacket (TCPIP_MAC_HANDLE hMac, TCPIP_MAC_RES* pRes, const TCPIP_MAC_PACKET_RX_STAT** ppPktStat)
{
    // get the oldest Rx packet
    return MRF24W_GetRxPacket();
}

static TCPIP_MAC_RES mrf24w_MACProcess(TCPIP_MAC_HANDLE hMac)
{
    MRF24W_USR_EV_DCPT eventInfo;

    // if any events occurred
    if (WF_MgmtEventsGet(&eventInfo))
    {
        // process the wifi event
        DRV_WIFI_ProcessEvent(eventInfo.mgmtEvents, eventInfo.mgmtEventInfo);
    }

    return TCPIP_MAC_RES_OK;
}

#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
static bool mrf24w_MACEventSetMask(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents, bool enable)
{
    return MRF24W_MACEventSetMask(hMac, macEvents, enable);
}

static bool mrf24w_MACEventAcknowledge(TCPIP_MAC_HANDLE hMac, TCPIP_MAC_EVENT macEvents)
{
    return MRF24W_MACEventAcknowledge(hMac, macEvents);
}
    
static TCPIP_MAC_EVENT mrf24w_MACEventGetPending(TCPIP_MAC_HANDLE hMac)
{
    return MRF24W_MACEventGetPending(hMac);
}

#endif  // (TCPIP_STACK_USE_EVENT_NOTIFICATION)


static void mrf24w_MACDeinitialize(MRF24W_MAC_DCPT* pDcpt )
{
    DRV_WIFI_Deinitialize();
    MRF24W_ChipReset();  // will stop the MR24W from transmitting
    Isp_SpiClose();
    WifiAsyncClearAllEvents();
    
#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)
    MRF24W_MACEventDeInit(pDcpt);    
#endif

    DRV_WIFI_HibernateEnable();

}
#endif  // defined(__PIC32MX__) && defined(TCPIP_IF_MRF24W)


//DOM-IGNORE-END
