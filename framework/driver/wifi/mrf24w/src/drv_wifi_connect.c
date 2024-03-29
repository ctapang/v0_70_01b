/*******************************************************************************
  MRF24W Connection Support

  File Name: 
    drv_wifi_connect.c  
  
  Summary:
    
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


/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/

#include "tcpip/src/tcpip_private.h"

// Compile only for PIC32MX MRF24W MAC interface
#if defined(TCPIP_IF_MRF24W)

#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
extern void DhcpEventHandler(TCPIP_NET_HANDLE hNet, TCPIP_DHCP_EVENT_TYPE evType, const void* param);
#endif  // defined(TCPIP_STACK_USE_DHCP_CLIENT)

static void SetWepSecurity(void);
static TCPIP_MAC_RES SetWpaSecurity(void);
static void SetWpsSecurity(void);
static void SetEapSecurity(void);

#if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
extern TCPIP_MAC_RES DRV_WIFI_ConvPassphraseToKey(uint8_t key_len, uint8_t *key, uint8_t ssid_len, uint8_t *ssid);
#endif

static TCPIP_DHCP_HANDLE DhcpHandle_Mrf24w = NULL;

/*****************************************************************************
 * FUNCTION: Demo_Wifi_Connect
 *
 * RETURNS:  TCPIP_MAC_RES
 *
 * PARAMS:   None
 *
 *  NOTES:   Connects to an 802.11 network.
 *****************************************************************************/
 TCPIP_MAC_RES Demo_Wifi_Connect(void)
{
    typedef enum {
        demo_Wifi_Connect_SM_1=0,
        demo_Wifi_Connect_SM_2,
        demo_Wifi_Connect_SM_3,
        demo_Wifi_Connect_SM_done
    }enum_demoWifiConnect_SM;
    static enum_demoWifiConnect_SM demoWifiConnect_SM = demo_Wifi_Connect_SM_1;
    TCPIP_MAC_RES RetCode = TCPIP_MAC_RES_PENDING;
	

    switch(demoWifiConnect_SM)
    {
        case demo_Wifi_Connect_SM_1:
        {
            uint8_t channelList[] = WF_DEFAULT_CHANNEL_LIST;
            DRV_WIFI_SCAN_CONTEXT scanContext;

#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
            uint8_t channelList_postscan[] = WF_DEFAULT_CHANNEL_LIST_POSTSCAN;
#endif

            DRV_WIFI_SsidSet(p_wifi_ConfigData->netSSID, p_wifi_ConfigData->SsidLength);

#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_ADHOC) || (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
            DRV_WIFI_NetworkTypeSet(p_wifi_ConfigData->networkType);
#else
            DRV_WIFI_NetworkTypeSet(WF_DEFAULT_NETWORK_TYPE);
#endif

#ifndef WF_DEFAULT_SCAN_TYPE
            scanContext.scanType = DRV_WIFI_ACTIVE_SCAN;    
#else
            scanContext.scanType = WF_DEFAULT_SCAN_TYPE;
#endif

            scanContext.minChannelTime = DRV_WIFI_DEFAULT_SCAN_MIN_CHANNEL_TIME;
            scanContext.maxChannelTime = DRV_WIFI_DEFAULT_SCAN_MAX_CHANNEL_TIME;
            scanContext.probeDelay     = DRV_WIFI_DEFAULT_SCAN_PROBE_DELAY;
            scanContext.scanCount      = DRV_WIFI_DEFAULT_SCAN_COUNT;
            DRV_WIFI_ScanContextSet(&scanContext);

#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
            if (((CFGCXT.type != DRV_WIFI_NETWORK_TYPE_SOFT_AP) && (CFGCXT.prevWLAN == DRV_WIFI_NETWORK_TYPE_SOFT_AP)) ||
                (p_wifi_ConfigData->networkType != DRV_WIFI_NETWORK_TYPE_SOFT_AP))
            {
                DRV_WIFI_ChannelListSet(channelList_postscan, sizeof(channelList_postscan));
            }
            else
            {
                DRV_WIFI_ChannelListSet(channelList, sizeof(channelList));
            }
#else // not network type not DRV_WIFI_NETWORK_TYPE_SOFT_AP
            DRV_WIFI_ChannelListSet(channelList, sizeof(channelList));
#endif // (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)

            // The Retry Count parameter tells the WiFi Connection manager how many attempts to make when trying
            // to connect to an existing network.  In the Infrastructure case, the default is to retry forever so that
            // if the AP is turned off or out of range, the radio will continue to attempt a connection until the
            // AP is eventually back on or in range.  In the Adhoc case, the default is to retry 3 times since the
            // purpose of attempting to establish a network in the Adhoc case is only to verify that one does not
            // initially exist.  If the retry count was set to DRV_WIFI_RETRY_FOREVER in the AdHoc mode, an AdHoc network
            // would never be established.
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_ADHOC) || (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
            if(p_wifi_ConfigData->networkType == DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE)
            {
                DRV_WIFI_ReconnectModeSet(DRV_WIFI_RETRY_FOREVER,   // retry forever to connect to WiFi network
                                    DRV_WIFI_ATTEMPT_TO_RECONNECT,  // reconnect on deauth from AP
                                    40,                             // beacon timeout is 40 beacon periods
                                    DRV_WIFI_ATTEMPT_TO_RECONNECT); // reconnect on beacon timeout
            }
            else if((p_wifi_ConfigData->networkType == DRV_WIFI_NETWORK_TYPE_ADHOC) || (p_wifi_ConfigData->networkType == DRV_WIFI_NETWORK_TYPE_SOFT_AP))
            {
                DRV_WIFI_ReconnectModeSet(WF_DEFAULT_LIST_RETRY_COUNT,    // retry N times to start or join AdHoc network
                                    DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT, // do not attempt to reconnect on deauth from station
                                    40,                                   // beacon timeout is 40 beacon periods
                                    DRV_WIFI_ATTEMPT_TO_RECONNECT);             // reconnect on beacon timeout
            }
            else
            {
                SYS_CONSOLE_MESSAGE("Please compile with correct XX_RETRY_COUNT\r\n");
                while(1);
            }
#else // network type not DRV_WIFI_NETWORK_TYPE_ADHOC or DRV_WIFI_NETWORK_TYPE_SOFT_AP
            DRV_WIFI_ReconnectModeSet(WF_DEFAULT_LIST_RETRY_COUNT, // retry N times to start or join AdHoc network
                                DRV_WIFI_ATTEMPT_TO_RECONNECT,     // reconnect on deauth from AP
                                40,                                // beacon timeout is 40 beacon periods
                                DRV_WIFI_ATTEMPT_TO_RECONNECT);    // reconnect on beacon timeout

#endif // (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_ADHOC) || (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)


            // Set Tx Mode
            DRV_WIFI_TxModeSet(WF_DEFAULT_TX_MODE); // WF_TXMODE_G_RATES, WF_TXMODE_B_RATES, WF_TXMODE_LEGACY_RATES

            // Error check items specific to WPS Push Button mode
#if (WF_DEFAULT_WIFI_SECURITY_MODE==DRV_WIFI_SECURITY_WPS_PUSH_BUTTON)
                //    SYS_ASSERT(strlen(p_wifi_ConfigData->netSSID) == 0, "");  // SSID must be empty when using WPS
                // To Do: fix this to work with different Domain and also empty channelList
                // SYS_ASSERT(sizeof(channelList)==11, "");      // must scan all channels for WPS
#endif
        
        }
        demoWifiConnect_SM++;
        break;

        case demo_Wifi_Connect_SM_2:
        {
            TCPIP_MAC_RES tmp = TCPIP_MAC_RES_OK;
            if (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_OPEN)
            {
                DRV_WIFI_SecurityOpenSet();
            }
            else if ((p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WEP_40) || (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WEP_104))
            {
                SetWepSecurity();
            }
            else if ((p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY)         ||
                     (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_WITH_KEY)              ||
                     (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE) ||
                     (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE)      ||
                     (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA2_WITH_KEY)             ||
                     (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE))
            {
                tmp = SetWpaSecurity();
            }
            else if ((p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPS_PIN) ||
                    (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPS_PUSH_BUTTON))
            {
                SetWpsSecurity();
            }
            else if (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_EAP)
            {
                SetEapSecurity();
            }

            if(TCPIP_MAC_RES_OK == tmp ) demoWifiConnect_SM++;
        }
            
            break;
        
        case demo_Wifi_Connect_SM_3:
        {
#if WF_DEFAULT_PS_POLL == DRV_WIFI_ENABLED
            {
                DRV_WIFI_PS_POLL_CONTEXT psPollContext;
                psPollContext.dtimInterval   = DRV_WIFI_DEFAULT_PS_DTIM_INTERVAL;
                psPollContext.listenInterval = DRV_WIFI_DEFAULT_PS_LISTEN_INTERVAL;
                psPollContext.useDtim        = true;
                DRV_WIFI_PsPollEnable(&psPollContext);
            }
 #else    /* WF_DEFAULT_PS_POLL == DRV_WIFI_DISABLED */
            DRV_WIFI_PsPollDisable();
#endif    /* WF_DEFAULT_PS_POLL == DRV_WIFI_ENABLED */

#if defined(TCPIP_STACK_USE_GRATUITOUS_ARP)
            DRV_WIFI_GratuitousArpStart(5);  // output a gratuitous arp every 5 seconds (after connection)
#endif

 #if defined(SYS_CONSOLE_ENABLE)
             OutputDemoHeader();
#endif

        // override reconnect mode if connection manager disabled
#if defined(DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE)
            DRV_WIFI_ReconnectModeSet(0,                               // report-only when connection lost (no reconnect)
                                DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT,  // report-only when deauth received (no reconnect)
                                40,                                    // set beacon timeout to 40 beacon periods
                                DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT); // report only when beacon timeout occurs
#endif

            WF_EnableDebugPrint(ENABLE_WPS_PRINTS);
            SYS_CONSOLE_MESSAGE("\r\nStart WiFi Connect . . .\r\n");

#if defined(TCPIP_STACK_USE_DHCP_CLIENT)
            if( DhcpHandle_Mrf24w == NULL)
            {    DhcpHandle_Mrf24w =  TCPIP_DHCP_HandlerRegister(TCPIP_STACK_NetHandleGet("MRF24W"), DhcpEventHandler, NULL);
            }
#endif  // defined(TCPIP_STACK_USE_DHCP_CLIENT)

            // start the WiFi connection process
            DRV_WIFI_Connect();

            WifiAsyncSetEventPending(ASYNC_DHCP_CONFIG_PENDING);  // ken test
        }
            demoWifiConnect_SM++;
            RetCode = TCPIP_MAC_RES_OK;
            //break;   //not break, will continue to demo_Wifi_Connect_SM_done
            
        case demo_Wifi_Connect_SM_done:
            demoWifiConnect_SM = demo_Wifi_Connect_SM_1;
            break;
    }
 
	return RetCode;
}

static void SetWepSecurity(void)
{
    DRV_WIFI_WEP_CONTEXT wepContext;

    wepContext.wepSecurityType = p_wifi_ConfigData->SecurityMode;
    wepContext.wepKeyLength    = p_wifi_ConfigData->SecurityKeyLength;
    memcpy(wepContext.wepKey, p_wifi_ConfigData->SecurityKey, wepContext.wepKeyLength);
    wepContext.wepKeyType      = DRV_WIFI_DEFAULT_WEP_KEY_TYPE;
    DRV_WIFI_SecurityWepSet(&wepContext);
}

static TCPIP_MAC_RES SetWpaSecurity(void)
{
    DRV_WIFI_WPA_CONTEXT wpaContext;

    typedef enum {
        SetWpaSecurity_SM_1=0,
        SetWpaSecurity_SM_2,
        SetWpaSecurity_SM_done
    }enum_SetWpaSecurity_SM;
    static enum_SetWpaSecurity_SM SetWpaSecurity_SM = SetWpaSecurity_SM_1;
    TCPIP_MAC_RES RetCode = TCPIP_MAC_RES_PENDING, tmp;
    switch(SetWpaSecurity_SM)
    {
        case SetWpaSecurity_SM_1:
        #if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
            if (p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE          ||
                p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE         ||
                p_wifi_ConfigData->SecurityMode == DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
            {
                tmp = DRV_WIFI_ConvPassphraseToKey(p_wifi_ConfigData->SecurityKeyLength, p_wifi_ConfigData->SecurityKey, p_wifi_ConfigData->SsidLength, p_wifi_ConfigData->netSSID);
                if( TCPIP_MAC_RES_OK == tmp )
                {
                    p_wifi_ConfigData->SecurityMode--;
                    p_wifi_ConfigData->SecurityKeyLength = 32;
                    SetWpaSecurity_SM ++;
                }
            }
            else
                SetWpaSecurity_SM++;
        #else // defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
            SetWpaSecurity_SM++;
        #endif // defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
            break;
        case SetWpaSecurity_SM_2:
            wpaContext.wpaSecurityType   = p_wifi_ConfigData->SecurityMode;
            wpaContext.keyInfo.keyLength = p_wifi_ConfigData->SecurityKeyLength;
            memcpy(wpaContext.keyInfo.key, p_wifi_ConfigData->SecurityKey, wpaContext.keyInfo.keyLength);
            DRV_WIFI_SecurityWpaSet(&wpaContext);
            RetCode = TCPIP_MAC_RES_OK;
            SetWpaSecurity_SM++;
            //break;  //no break, continue to next state
        case SetWpaSecurity_SM_done:
            SetWpaSecurity_SM = SetWpaSecurity_SM_1;
            break;
    }
    




	return RetCode;
}

static void SetWpsSecurity(void)
{
    DRV_WIFI_WPS_CONTEXT wpsContext;

    wpsContext.wpsSecurityType = p_wifi_ConfigData->SecurityMode;

    if (wpsContext.wpsSecurityType == DRV_WIFI_SECURITY_WPS_PUSH_BUTTON)
    {
        memset(wpsContext.wpsPin, 0x00, DRV_WIFI_WPS_PIN_LENGTH);
        wpsContext.wpsPinLength = 0;
    }
#if WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPS_PIN
    else
    {
        memcpy(wpsContext.wpsPin, (const void*)WF_DEFAULT_WPS_PIN, WF_WPS_PIN_LENGTH);
        wpsContext.wpsPinLength = DRV_WIFI_WPS_PIN_LENGTH;
    }
#endif
    
    DRV_WIFI_SecurityWpsSet(&wpsContext);
    DRV_WIFI_YieldPassphraseToHost();  // will convert WPA phrase in host pic32
}

static void SetEapSecurity(void)
{
    // TBD
}


#endif  // defined(TCPIP_IF_MRF24W)

//DOM-IGNORE-END
