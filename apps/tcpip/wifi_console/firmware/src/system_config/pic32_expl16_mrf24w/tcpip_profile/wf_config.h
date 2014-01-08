/*******************************************************************************
  MRF24W Driver Customization

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Provides access to MRF24W WiFi controller
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard
*******************************************************************************/

/*******************************************************************************
File Name: wf_config.h 
Copyright 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS?WITHOUT WARRANTY OF ANY KIND,
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

#ifndef __WF_CONFIG_H_
#define __WF_CONFIG_H_

#define WF_CONSOLE_DEMO

/************************************************************************
 * Select a default network mode for Console Demo.                      *
 *                                                                      *
 * Console Demo:                                                        *
 *      DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE                            *
 *      DRV_WIFI_NETWORK_TYPE_ADHOC                                     *
 *      DRV_WIFI_NETWORK_TYPE_P2P                                       *
 * EasyConfig Demo:                                                     *
 *      DRV_WIFI_NETWORK_TYPE_ADHOC                                     *
 *      DRV_WIFI_NETWORK_TYPE_SOFT_AP                                   *
 * Web Server Demo:                                                     *
 *      DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE                            *
 ************************************************************************/
#define WF_DEFAULT_NETWORK_TYPE     DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE

/****************************************************************************************************************************************
 * Configure network for Infrastructure mode                                                                                            *
 *                                                                                                                                      *
 * Available security configuration:                                                                                                    *
 * DRV_WIFI_SECURITY_OPEN                      : No security                                                                            *
 * DRV_WIFI_SECURITY_WEP_40                    : WEP Encryption using 40 bit keys                                                       *
 * DRV_WIFI_SECURITY_WEP_104                   : WEP Encryption using 104 bit keys                                                      *
 * DRV_WIFI_SECURITY_WPA_WITH_KEY              : WPA-PSK Personal where binary key is given to MRF24W                                   *
 * DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE      : WPA-PSK Personal where passphrase is given to MRF24W and it calculates the binary key  *
 * DRV_WIFI_SECURITY_WPA2_WITH_KEY             : WPA2-PSK Personal where binary key is given to MRF24W                                  *
 * DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE     : WPA2-PSK Personal where passphrase is given to MRF24W and it calculates the binary key *
 * DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY         : WPA-PSK Personal or WPA2-PSK Personal where binary key is given and MRF24W will        *
 *                                             connect at highest level AP supports (WPA or WPA2)                                       *
 * DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE : WPA-PSK Personal or WPA2-PSK Personal where passphrase is given to MRF24W and it       *
 *                                             calculates the binary key and connects at highest level AP supports (WPA or WPA2)        *
 * DRV_WIFI_SECURITY_WPS_PUSH_BUTTON           : WPS push button method - for MRF24WG only                                              *
 * DRV_WIFI_SECURITY_WPS_PIN                   : WPS PIN method - for MRF24WG only                                                      *
 ****************************************************************************************************************************************/
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE)
    #define WF_DEFAULT_WIFI_SECURITY_MODE              	DRV_WIFI_SECURITY_OPEN
    #define WF_DEFAULT_SCAN_TYPE                       	DRV_WIFI_ACTIVE_SCAN
    #define WF_DEFAULT_SSID_NAME                        "MicrochipDemoAP"        /* Set the SSID of the network we want to join. For WPS Push button set to "" */
    #define WF_DEFAULT_LIST_RETRY_COUNT             	(DRV_WIFI_RETRY_FOREVER) /* Number (1..255) of times to try to connect to the SSID when using Infrastructure network type */
    #define WF_DEFAULT_CHANNEL_LIST                   	{}                       /* Channel list for Domain - use default in module */
    #define WF_DEFAULT_PS_POLL                          DRV_WIFI_DISABLED        /* DRV_WIFI_ENABLED or DRV_WIFI_DISABLED */
    #define WF_DEFAULT_BEACON_TIMEOUT                   (40)                     /* Number of missed beacon periods before losing connection */
#endif  /* Infrastructure   */


/************************************************************************************
 * Configure network for Ad-Hoc mode                                                *
 *                                                                                  *
 * Available secruity configuation:                                                 *
 *      DRV_WIFI_SECURITY_OPEN                : No security                         *
 *      DRV_WIFI_SECURITY_WEP_40              : WEP encryption using 40 bit keys    *
 *      DRV_WIFI_SECURITY_WEP_104             : WEP encryption using 104 bit keys   *
 ************************************************************************************/
#if WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_ADHOC
    #define WF_DEFAULT_WIFI_SECURITY_MODE		DRV_WIFI_SECURITY_OPEN      /* Set security mode */
    #define WF_DEFAULT_SCAN_TYPE                        DRV_WIFI_ACTIVE_SCAN        /* Set network scan mode */
    #define WF_DEFAULT_SSID_NAME                        "MicrochipDemoAdHoc"         /* Set the SSID of the network we want to join or create */
    #define WF_DEFAULT_CHANNEL_LIST                     {3}                         /* Ad-hoc network channel - use default channel for Domain in module */
    #define WF_DEFAULT_PS_POLL                          DRV_WIFI_DISABLED           /* PS_POLL not supported in Ad-Hoc - must be set to DRV_WIFI_DISABLED */
    #define WF_DEFAULT_LIST_RETRY_COUNT                 (3)                         /* Number (1..254) of times to try to connect to the SSID when using Ad/Hoc network type */
    #define WF_DEFAULT_BEACON_TIMEOUT                   (40)                        /* Number of missed beacon periods before losing connection */
#endif


/************************************************************************************
 * Configure network for SoftAP mode                                                *
 *                                                                                  *
 * Available secruity configuration:                                                *
 *      DRV_WIFI_SECURITY_OPEN                : No security                         *
 *      DRV_WIFI_SECURITY_WEP_40              : WEP Encryption using 40 bit keys    *
 *      DRV_WIFI_SECURITY_WEP_104             : WEP Encryption using 104 bit keys   *
 ************************************************************************************/
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
    /* SoftAP function has the full "EasyConfig" function.
    * Your STA can connect to the SoftAP as a client, get the DHCP IP, run ping, and run web browser to connect to Web Server
    * of SoftAP. It will allow you to re-connect / redirect to another AP in infrastructure mode.
    * The reason this demo sits here is simply A) borrow DHCP server; B) borrow HTTP server.
    *
    * Before starting up as SoftAP, prescan (MY_DEFAULT_CHANNEL_LIST_PRESCAN) will be executed.
    * For SoftAP, default channel is assigned as MY_DEFAULT_CHANNEL_LIST i.e single channel 6. This means SoftAP
    * will start up in channel 6.
    * When scan option is selected in EZConfig web browser in SoftAP mode, the prescan results will be displayed.
    * Repeated selection of this scan option will always display the prescan results. From this prescan list, the user can select
    * an AP to be redirected to.
    * When redirected to another AP, the channel list will change to allow more channel listings in infrastructure mode,
    * i.e all channels MY_DEFAULT_CHANNEL_LIST_POSTSCAN. This means AP will scan MY_DEFAULT_CHANNEL_LIST_POSTSCAN
    * channel list.
    *
    * Also note that this is a very simplified SoftAP. So its function is limited as , A) no routing supported; B) only 1 client allowed
    * at a time.  And security wise currently it supports both open mode and WEP security.
    *
    * SoftAP's default IP is 192.168.1.3 and its Network Mask is 255.255.0.0
    * SoftAP on certain setups with IP adress 192.168.1.1 has problem with DHCP client assigning new IP address on redirection.
    * 192.168.1.1 is a common IP address with most APs. This is still under investigation.
    * For now, assign this as 192.168.1.3
    */

    #define WF_DEFAULT_SSID_NAME                "MCHPSoftAP"            /* Set SoftAP ssid    */
    #define WF_DEFAULT_WIFI_SECURITY_MODE	DRV_WIFI_SECURITY_OPEN        /* Set secruity mode */
    #define WF_DEFAULT_LIST_RETRY_COUNT         (3)                     /* Dummy, Not used */
    #define WF_DEFAULT_CHANNEL_LIST             {6}                     /* Set SoftAP network channel */
    #define WF_DEFAULT_CHANNEL_LIST_PRESCAN     {1, 6, 11}              /* SoftAP: Pre-scan channel list WF_PRESCAN */
    #define WF_DEFAULT_CHANNEL_LIST_POSTSCAN    {}                      /* SoftAP: Post-scan channel list */
    #define SOFTAP_CHECK_LINK_STATUS		DRV_WIFI_DISABLED           /* DRV_WIFI_ENABLED to use with SOFTAP_LINK_FAILURE_THRESHOLD */
    #define WF_DEFAULT_PS_POLL                  DRV_WIFI_DISABLED       /* PS_POLL not supported in SoftAP - must be set to DRV_WIFI_DISABLED */
    #define WF_DEFAULT_SCAN_TYPE                DRV_WIFI_PASSIVE_SCAN   /* For SoftAP use Passive Scan */
    #define WF_DEFAULT_BEACON_TIMEOUT           (40)                    /* Number of missed beacon periods before losing connection */

    /* Consecutive null packet transmission failures for this amount of times.
     * Then SoftAP considers the client has gone away. This is only effective
     * when SOFTAP_CHECK_LINK_STATUS is enabled. This function is only valid
     * with MRF24WG module with FW 0x3107 or the later.
     */
    #define SOFTAP_LINK_FAILURE_THRESHOLD	40

#endif  /* SoftAP   */




 /*----------------------------------------------------------------------*
 * For WPS Push-Button demo, press the button of AP (Registrar) first   *
 * before running this demo. Input this pin number on AP (Registrar),   *
 * and activate Registrar first before connection attempt. Also note    *
 * that this 8 digit is not randomly generated. Last digit is the       *
 * checksum of first 7 digits. The checksum must be correct, otherwise  *
 * MRF24WG module wil reject the pin code.                              *
 *----------------------------------------------------------------------*/
#define WF_DEFAULT_WPS_PIN    "12390212"

#define WF_DEFAULT_TX_MODE    DRV_WIFI_TXMODE_G_RATES    /* DRV_WIFI_TXMODE_G_RATES, DRV_WIFI_TXMODE_B_RATES, or */
                                                         /*  DRV_WIFI_TXMODE_LEGACY_RATES (1 and 2 Mbps)   */

/*------------------------------------------------------------------------------------------*
 * Warning !!! Please note that :                                                           *
 * RF Module FW has a built-in connection manager, and it is enabled by default.            *
 * So if you want to run your own connection manager in host stack application side,        *
 * then you should disable the module connection manager to avoid some possible conflict    *
 * between the two.  These two APIs can be affected if you do not disable it.               *
 *   A) DRV_WIFI_Disconnect()                                                               *
 *   B) DRV_WIFI_Scan()                                                                     *
 * If some conflict occurs then these APIs will return failure.                             *
 *                                                                                          *
 * Note: This feature is current available with Infrastructure mode only.                   *
 *------------------------------------------------------------------------------------------*/
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE)
    //#define DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE
#endif

/*--------------------------------------------------------------------------------------------------------------*
 * This option allows host to convert the passphrase to the key by itself instead of relying on RF module FW.   *
 * Even if you do not use this option, RF module FW will still take care of this key deriviation.               *
 * However it will take much more time such as 32 seconds for MRF24W or 25 seconds for MRF24WG.                 *
 * Also note that the reason PIC18/24 are not allowed to use this option is just to save memory space on it.    *
 * So if you have enough memory on PIC18/24, then you can also use this option with adding WF_pbkdf2.c          *
 * in your projects.                                                                                            *
 * Note: This feature is not available in  Ad-Hoc network, as WPA/WPA2 is not supported security mode.          *
 *--------------------------------------------------------------------------------------------------------------*/
#if defined(__C32__)
    #define DERIVE_KEY_FROM_PASSPHRASE_IN_HOST
#endif


/*----------------------------------------------------------------------------------------------------------*
 * By default the module HW has 2 hardware multicast filters. If that is not enough on your application,    *
 * then you can choose this option to extend it to max 16.  As the macro name indicates this forces         *
 * the module FW to use software to run the filters instead of hardware.  Downside of this option           *
 * is the performance can degrade when there are so many multicast packets on air and the filtering is      *
 * done in SW.                                                                                              *
 *----------------------------------------------------------------------------------------------------------*/
#define ENABLE_SOFTWARE_MULTICAST_FILTER

/*----------------------------------------------------------------------------------------------------------*
 * This option allows a host stack to save and store aquired credentials through WPS process, and reuse     *
 * them to reconnect to same AP later on.  WPS process takes a relatively long time to get through.         *
 * So storing the credentials in non-volatile memory  and reusing it for reconnect is always good idea.     *
 * But this is not hard requirement, so we will let our customers decide whether to use this option or not. *
 * In order to save memory space in a host application side, we disable this option by default              *
 *----------------------------------------------------------------------------------------------------------*/
#if (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPS_PUSH_BUTTON) || \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPS_PIN)
    #define SAVE_WPS_CREDENTIALS
#endif

/*----------------------------------------------------------------------*
 * Enable stack support for "Host Scan"                                 *
 *----------------------------------------------------------------------*/
#define EZ_CONFIG_SCAN
#define TCPIP_STACK_USE_EZ_CONFIG
#define EZ_CONFIG_STALL
#define EZ_CONFIG_STORE
/*-----------------------------------------------------------------------------------------------*
 * Select IP configuration                                                                       *
 *                                                                                               *
 * Note: Select Static IP for DRV_WIFI_NETWORK_TYPE_ADHOC and DRV_WIFI_NETWORK_TYPE_SOFT_AP      *
 *-----------------------------------------------------------------------------------------------*/
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_ADHOC || WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
    #define ENABLE_STATIC_IP                // static IP
#else
    #define ENABLE_DHCP_IP                  // dynamic IP
    #define TCPIP_STACK_USE_DHCP_CLIENT     // Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
#endif

//#define TCPIP_STACK_USE_GRATUITOUS_ARP

/*----------------------------------------------------------------------------------*
 * Default WEP keys used in DRV_WIFI_SECURITY_WEP_40 and DRV_WIFI_SECURITY_WEP_104  *
 * security mode.                                                                   *
 *----------------------------------------------------------------------------------*/
#if (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WEP_40)   \
                    ||                                            \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WEP_104)

#define WF_DEFAULT_WEP_KEY_INDEX        (0)             /* MRF24W only support Key Index 0 */

#define WF_DEFAULT_WEP_PHRASE           "WEP Phrase"

#if (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WEP_40)
// string 4 40-bit WEP keys -- corresponding to passphraseof "WEP Phrase"
#define WF_DEFAULT_WEP_KEYS_40 "\
\x5a\xfb\x6c\x8e\x77\
\xc1\x04\x49\xfd\x4e\
\x43\x18\x2b\x33\x88\
\xb0\x73\x69\xf4\x78"
// Do not indent above string as it will inject spaces

#endif

#if (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WEP_104)
// string containing 4 104-bit WEP keys -- corresponding to passphraseof "WEP Phrase"
#define WF_DEFAULT_WEP_KEYS_104 "\
\x90\xe9\x67\x80\xc7\x39\x40\x9d\xa5\x00\x34\xfc\xaa\
\x77\x4a\x69\x45\xa4\x3d\x66\x63\xfe\x5b\x1d\xb9\xfd\
\x82\x29\x87\x4c\x9b\xdc\x6d\xdf\x87\xd1\xcf\x17\x41\
\xcc\xd7\x62\xde\x92\xad\xba\x3b\x62\x2f\x7f\xbe\xfb"
// Do not indent above string as it will inject spaces 
#endif


#endif /* WEP40 and WEP104 */

/*----------------------------------------------------------------------*
 * Default PSK passphrase used in WPA and WPA2                          *
 *----------------------------------------------------------------------*/
#if ((WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE)      \
                            ||                                                      \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE)      \
                            ||                                                      \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE))

#define WF_DEFAULT_PSK_PHRASE               "Microchip 802.11 Secret PSK Password"

#endif  /* WPA and WPA2 PSK Passphrase */

/*------------------------------------------------------------------------------*
 * If using security mode of DRV_WIFI_SECURITY_WPA_WITH_KEY or                  *
 * DRV_WIFI_SECURITY_WPA2_WITH_KEY, then this section must be set to  match     *
 * the key for WF_DEFAULT_SSID_NAME and WF_DEFAULT_PSK_PHRASE                   *
 * combination.  The values below are derived from the SSID "MicrochipDemoAP"   *
 * and the pass phrase "Microchip 802.11 Secret PSK Password".                  *
 * The tool at http://www.wireshark.org/tools/wpa-psk.html can be used to       *
 * generate this field.
 *------------------------------------------------------------------------------*/
#if ((WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA_WITH_KEY)      \
                            ||                                              \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA2_WITH_KEY)      \
                            ||                                              \
    (WF_DEFAULT_WIFI_SECURITY_MODE == DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY))

#define WF_DEFAULT_PSK "\
\x86\xC5\x1D\x71\xD9\x1A\xAA\x49\
\x40\xC8\x88\xC6\xE9\x7A\x4A\xD5\
\xE5\x6D\xDA\x44\x8E\xFB\x9C\x0A\
\xE1\x47\x81\x52\x31\x1C\x13\x7C"
// Do not indent above string as it will inject spaces
#endif  /* WPA and WPA2 PSK */



#define WF_UPDATE_FIRMWARE_UART_24G           // when you undate wifi firmware by uart, please enable this line
//#define WF_UPDATE_FIRMWARE_TCPCLIENT_24G      // when you undate wifi firmware by tcpip client, please enable this line

//#define WF_SAVE_CONFIG_TO_MEMORY   //If define this macro, system will save configure data into MEMORY
#if defined (WF_SAVE_CONFIG_TO_MEMORY)
 //#define WF_MEMORY_INSIDE_FLASH
 #define WF_MEMORY_EXTERN_EEPROM

 #if defined(WF_MEMORY_INSIDE_FLASH) && defined(WF_MEMORY_EXTERN_EEPROM)
  error, we cannot define the WF_MEMORY_INSIDE_FLASH and WF_MEMORY_EXTERN_EEPROM at same time
 #endif
#endif

#endif /* __WF_CONFIG_H_ */


