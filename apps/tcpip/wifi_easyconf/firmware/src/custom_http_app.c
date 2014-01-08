/*******************************************************************************
  Application to Demo HTTP2 Server

  Summary:
    Support for HTTP2 module in Microchip TCP/IP Stack
    
  Description:
    -Implements the application 
    -Reference: RFC 1002
*******************************************************************************/

/*******************************************************************************
File Name:  CustomHTTPApp.c
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

#define __CUSTOMHTTPAPP_C
#include <ctype.h>
#include "tcpip_config.h"

#if defined(TCPIP_STACK_USE_HTTP_SERVER)

#include "tcpip/tcpip.h"
#include "../../../../../framework/driver/wifi/mrf24w/src/drv_wifi_easy_config.h"
#include "http_config.h"

#include "main_demo.h"
//#include "../tcpip/wifi/wf_configData.h"

#include "tcpip/src/common/hashes.h"
extern DRV_WIFI_EZ_CONFIG_SCAN_CONTEXT  g_ScanCtx;

uint8_t HexToBin(uint8_t hexChar);

/****************************************************************************
  Section:
    Definitions
  ***************************************************************************/


/****************************************************************************
  Section:
    Function Prototypes and Memory Globalizers
  ***************************************************************************/
#if defined(HTTP_USE_POST)
    #if defined(SYS_OUT_ENABLE)
        static HTTP_IO_RESULT HTTPPostLCD(HTTP_CONN_HANDLE connHandle);
    #endif
    #if defined(HTTP_APP_USE_MD5)
        static HTTP_IO_RESULT HTTPPostMD5(HTTP_CONN_HANDLE connHandle);
    #endif
    #if defined(TCPIP_STACK_USE_EZ_CONFIG)
        static HTTP_IO_RESULT HTTPPostWifiConfig(HTTP_CONN_HANDLE connHandle);
    #endif
    #if defined(HTTP_APP_USE_RECONFIG)
        static HTTP_IO_RESULT HTTPPostConfig(HTTP_CONN_HANDLE connHandle);
        #if defined(TCPIP_STACK_USE_SNMP_SERVER)
        static HTTP_IO_RESULT HTTPPostSNMPCommunity(HTTP_CONN_HANDLE connHandle);
        #endif
    #endif
    #if defined(HTTP_APP_USE_EMAIL) || defined(TCPIP_STACK_USE_SMTP_CLIENT)
        static HTTP_IO_RESULT HTTPPostEmail(HTTP_CONN_HANDLE connHandle);
    #endif
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
        static HTTP_IO_RESULT HTTPPostDDNSConfig(HTTP_CONN_HANDLE connHandle);
    #endif
#endif
extern bool convertAsciiToHexInPlace(char *p_string, uint8_t expectedHexBinSize );
// bss descriptor fetched from on-chip
static DRV_WIFI_SCAN_RESULT bssDesc;
static bool bssDescIsValid = false;

// RAM allocated for DDNS parameters
#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    static uint8_t DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static bool lastSuccess = false;

// Stick status message variable.  See lastSuccess for details.
static bool lastFailure = false;
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP) || (DRV_WIFI_DEFAULT_ADHOC_PRESCAN == DRV_WIFI_ENABLED) 
extern DRV_WIFI_SCAN_RESULT preScanResult[50]; // WF_PRESCAN
#endif

/****************************************************************************
  Section:
    Authorization Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
    uint8_t HTTPNeedsAuth(HTTP_CONN_HANDLE connHandle, uint8_t* cFile)

  Internal:
      See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
uint8_t HTTPNeedsAuth(HTTP_CONN_HANDLE connHandle, uint8_t* cFile)
{
    // If the filename begins with the folder "protect", then require auth
    if(memcmp(cFile, (const void*)"protect", 7) == 0)
        return 0x00;        // Authentication will be needed later

    // If the filename begins with the folder "snmp", then require auth
    if(memcmp(cFile, (const void*)"snmp", 4) == 0)
        return 0x00;        // Authentication will be needed later

    #if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
    if(memcmp(cFile, (const void*)"mpfsupload", 10) == 0)
        return 0x00;
    #endif
    // You can match additional strings here to password protect other files.
    // You could switch this and exclude files from authentication.
    // You could also always return 0x00 to require auth for all files.
    // You can return different values (0x00 to 0x79) to track "realms" for below.

    return 0x80;            // No authentication required
}
#endif

/*****************************************************************************
  Function:
    uint8_t HTTPCheckAuth(HTTP_CONN_HANDLE connHandle, uint8_t* cUser, uint8_t* cPass)

  Internal:
      See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
uint8_t HTTPCheckAuth(HTTP_CONN_HANDLE connHandle, uint8_t* cUser, uint8_t* cPass)
{
    if(strcmp((char *)cUser,(const char *)"admin") == 0
        && strcmp((char *)cPass, (const char *)"microchip") == 0)
        return 0x80;        // We accept this combination

    // You can add additional user/pass combos here.
    // If you return specific "realm" values above, you can base this
    //   decision on what specific file or folder is being accessed.
    // You could return different values (0x80 to 0xff) to indicate
    //   various users or groups, and base future processing decisions
    //   in HTTPExecuteGet/Post or HTTPPrint callbacks on this value.

    return 0x00;            // Provided user/pass is invalid
}
#endif

/****************************************************************************
  Section:
    GET Form Handlers
  ***************************************************************************/
  typedef union 
{
    uint16_t Val;
    uint8_t v[2];
} MCHP_UINT16_VAL;
/*****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPExecuteGet(HTTP_CONN_HANDLE connHandle)

  Internal:
      See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr, *ptr1;
    uint8_t filename[20];
    uint8_t* httpDataBuff;
    uint8_t bssIdx;
    MCHP_UINT16_VAL bssIdxStr;
    // Load the file name
    // Make sure uint8_t filename[] above is large enough for your longest name
    MPFSGetFilename(TCPIP_HTTP_CurrentConnectionFileGet(connHandle), filename, 20);

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
    // If its the forms.htm page
    if(!memcmp(filename, "forms.htm", 9))
    {
        // Seek out each of the four LED strings, and if it exists set the LED states
        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"led4");
        if(ptr)
            LED4_IO = (*ptr == '1');

        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"led3");
        if(ptr)
            LED3_IO = (*ptr == '1');

        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"led2");
        if(ptr)
            LED2_IO = (*ptr == '1');

        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"led1");
        if(ptr)
            LED1_IO = (*ptr == '1');
    }

    // If it's the LED updater file
    else if(!memcmp(filename, "cookies.htm", 11))
    {
        // This is very simple.  The names and values we want are already in
        // the data array.  We just set the hasArgs value to indicate how many
        // name/value pairs we want stored as cookies.
        // To add the second cookie, just increment this value.
        // remember to also add a dynamic variable callback to control the printout.
        TCPIP_HTTP_CurrentConnectionHasArgsSet(connHandle, 0x01);
    }


    // If it's the LED updater file
    else if(!memcmp(filename, "leds.cgi", 8))
    {
        // Determine which LED to toggle
        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"led");

        // Toggle the specified LED
        switch(*ptr) {
            case '1':
                LED1_IO ^= 1;
                break;
            case '2':
                LED2_IO ^= 1;
                break;
            case '3':
                LED3_IO ^= 1;
                break;
            case '4':
                LED4_IO ^= 1;
                break;
            case '5':
                LED5_IO ^= 1;
                break;
            case '6':
                LED6_IO ^= 1;
                break;
            case '7':
                LED7_IO ^= 1;
                break;
        }

    }
    else if(!memcmp(filename, "scan.cgi", 8))
    {
        ptr = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"scan");
        ptr1 = TCPIP_HTTP_ArgGet(httpDataBuff, (const uint8_t *)"getBss");
        
        if ((ptr != NULL) && (ptr1 == NULL))
        {
            bssDescIsValid = false;
            // scan request
            #if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP) || (DRV_WIFI_DEFAULT_ADHOC_PRESCAN == DRV_WIFI_ENABLED) 
            // display pre-scan results before starting as SoftAP. SoftAP does not scan.
            SYS_CONSOLE_MESSAGE("HTTPExecuteGet: ... Scan bypass scan  ................. \r\n");
            #else
            if (WFStartScan() == DRV_WIFI_SUCCESS)
            {
                if (WFStartScan() == DRV_WIFI_SUCCESS)
                {
                    SYS_CONSOLE_MESSAGE("HTTPExecuteGet: WFStartScan success ................. \r\n");
                    SCAN_SET_DISPLAY(SCANCXT.scanState);
                    SCANCXT.displayIdx = 0;
                }
            }
            #endif
        }
        else if ((ptr == NULL) && (ptr1 != NULL))
        {
            // getBss request
            // use the value to get the nth bss stored on chip
            bssDescIsValid = false;
            bssIdxStr.v[1] = *ptr1;
            bssIdxStr.v[0] = *(ptr1+1);    
            bssIdx = hexatob(bssIdxStr.Val);

            #if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP) || (DRV_WIFI_DEFAULT_ADHOC_PRESCAN == DRV_WIFI_ENABLED) 
            // display pre-scan results before starting as SoftAP. SoftAP does not scan.
            bssDesc = preScanResult[bssIdx];
            if(bssDesc.ssidLen<32)
                bssDesc.ssid[bssDesc.ssidLen]=0;
            //putsUART("HTTPExecuteGet: SoftAP ... display pre-scan  ................. \r\n");
            #else 
            WFRetrieveScanResult(bssIdx, &bssDesc);
            #endif
            bssDescIsValid = true;
        }
        else
        {
            // impossible to get here
        }                  
    }
    return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
    POST Form Handlers
  ***************************************************************************/
#if defined(HTTP_USE_POST)

/*****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPExecutePost(HTTP_CONN_HANDLE connHandle)

  Internal:
      See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(HTTP_CONN_HANDLE connHandle)
{
    // Resolve which function to use and pass along
    uint8_t filename[20];

    // Load the file name
    // Make sure uint8_t filename[] above is large enough for your longest name
    MPFSGetFilename(TCPIP_HTTP_CurrentConnectionFileGet(connHandle), filename, sizeof(filename));

#if defined(SYS_OUT_ENABLE)
    if(!memcmp(filename, "forms.htm", 9))
        return HTTPPostLCD(connHandle);
#endif

#if defined(HTTP_APP_USE_MD5)
    if(!memcmp(filename, "upload.htm", 10))
        return HTTPPostMD5(connHandle);
#endif

#if defined(TCPIP_STACK_USE_EZ_CONFIG)
    if(!memcmp(filename, "configure.htm", 13))
        return HTTPPostWifiConfig(connHandle) /*HTTPPostConfig()*/;
#endif
#if defined(HTTP_APP_USE_RECONFIG)
    if(!memcmp(filename, "protect/config.htm", 18))
        return HTTPPostConfig(connHandle);
    #if defined(TCPIP_STACK_USE_SNMP_SERVER)
    else if(!memcmp(filename, "snmp/snmpconfig.htm", 19))
        return HTTPPostSNMPCommunity(connHandle);
    #endif
#endif

#if defined(TCPIP_STACK_USE_SMTP_CLIENT)
    if(!strcmp((char*)filename, "email/index.htm"))
        return HTTPPostEmail(connHandle);
#endif

#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    if(!strcmp((char*)filename, "dyndns/index.htm"))
        return HTTPPostDDNSConfig(connHandle);
#endif

    return HTTP_IO_DONE;
}

/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostLCD(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the LCD form on forms.htm

  Description:
    Locates the 'lcd' parameter and uses it to update the text displayed
    on the board's LCD display.

    This function has four states.  The first reads a name from the data
    string returned as part of the POST request.  If a name cannot
    be found, it returns, asking for more data.  Otherwise, if the name
    is expected, it reads the associated value and writes it to the LCD.
    If the name is not expected, the value is discarded and the next name
    parameter is read.

    In the case where the expected string is never found, this function
    will eventually return HTTP_IO_NEED_DATA when no data is left.  In that
    case, the HTTP2 server will automatically trap the error and issue an
    Internal Server Error to the browser.

  Precondition:
    None

  Parameters:
    None

  Return Values:
      HTTP_IO_DONE - the parameter has been found and saved
      HTTP_IO_WAITING - the function is pausing to continue later
      HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(SYS_OUT_ENABLE)
static HTTP_IO_RESULT HTTPPostLCD(HTTP_CONN_HANDLE connHandle)
{
    uint8_t* cDest;
    uint8_t* httpDataBuff;

    #define SM_POST_LCD_READ_NAME        (0u)
    #define SM_POST_LCD_READ_VALUE        (1u)

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
    switch(TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle))
    {
        // Find the name
        case SM_POST_LCD_READ_NAME:

            // Read a name
            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_POST_LCD_READ_VALUE);
            // No break...continue reading value

        // Found the value, so store the LCD and return
        case SM_POST_LCD_READ_VALUE:

            // If value is expected, read it to data buffer,
            // otherwise ignore it (by reading to NULL)
            if(!strcmp((char*)httpDataBuff, (const char*)"lcd"))
                cDest = httpDataBuff;
            else
                cDest = NULL;

            // Read a value string
            if(TCPIP_HTTP_PostValueRead(connHandle, cDest, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // If this was an unexpected value, look for a new name
            if(!cDest)
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_POST_LCD_READ_NAME);
                break;
            }

                        SYS_OUT_MESSAGE((char*)cDest);

            // This is the only expected value, so callback is done
            strcpy((char*)httpDataBuff, "/forms.htm");
            TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
            return HTTP_IO_DONE;
    }

    // Default assumes that we're returning for state machine convenience.
    // Function will be called again later.
    return HTTP_IO_WAITING;
}
#endif
/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostWifiConfig(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the wifi config data

  Description:
    Accepts wireless configuration data from the www site and saves them to a
    structure to be applied by the ZG configuration manager.

    The following configurations are possible:
         i) Mode: adhoc or infrastructure
        ii) Security:
               - None
               - WPA/WPA2 passphrase
               - WPA/WPA2 pre-calculated key
               - WEP 64-bit
               - WEP 128-bit
       iii) Key material
    
    If an error occurs, such as data is invalid they will be redirected to a page
    informing the user of such results.  

    NOTE: This code for modified originally from HTTPPostWifiConfig as distributed
          by Microchip.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    HTTP_IO_DONE - all parameters have been processed
    HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(TCPIP_STACK_USE_EZ_CONFIG)
static HTTP_IO_RESULT HTTPPostWifiConfig(HTTP_CONN_HANDLE connHandle)
{
        uint8_t ssidLen;
        TCPIP_NET_HANDLE currNet;//, newNet;
        uint32_t byteCount;
        TCP_SOCKET sktHTTP;
        uint8_t* httpDataBuff = 0;
        byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
        sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
        if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
            goto ConfigFailure;

        // current interface we're working on
        currNet = TCPIP_TCP_SocketNetGet(sktHTTP);
        // ensure our static approach is working OK

        // Ensure that all data is waiting to be parsed.  If not, keep waiting for
        // all of it to arrive.
        if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
            return HTTP_IO_NEED_DATA;

        httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
        // Read all browser POST data
        while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
        {
            // Read a form field name
            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
                goto ConfigFailure;

            // Read a form field value
            if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
                goto ConfigFailure;

            // Parse the value that was read
            if(!strcmp((char*)httpDataBuff, (const char*)"sec"))
            {// Read security type
                char   security_type[7];

                if (strlen((char*)(httpDataBuff+6)) > 6) /* Sanity check */
                    goto ConfigFailure;

                memcpy(security_type, (void*)(httpDataBuff+6), strlen((char*)(httpDataBuff+6)));
                security_type[strlen((char*)(httpDataBuff+6))] = 0; /* Terminate string */

                if (!strcmp((char*)security_type, (const char*)"no"))
                {
                    CFGCXT.security = DRV_WIFI_SECURITY_OPEN;
                    SYS_CONSOLE_MESSAGE("\r\n1.0 sec=open\r\n");
                }
                else if(!strcmp((char*)security_type, (const char*)"wpa"))
                {
                    CFGCXT.security = DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE;
                    SYS_CONSOLE_MESSAGE("\r\n1.1 WPA passphrase\r\n");
                }
                else if(!strcmp((char*)security_type, (const char*)"calc"))
                {    /* Pre-calculated key */
                    CFGCXT.security = DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY;
                }
                else if(!strcmp((char*)security_type, (const char*)"wep40"))
                {
                    CFGCXT.security = DRV_WIFI_SECURITY_WEP_40;
                    SYS_CONSOLE_MESSAGE("\r\n1.3 Select wep64 on www\r\n");
                }
                else if(!strcmp((char*)security_type, (const char*)"wep104"))
                {
                    CFGCXT.security = DRV_WIFI_SECURITY_WEP_104;
                    SYS_CONSOLE_MESSAGE("\r\n1.4 Select wep128 on www\r\n");
                }
                else
                {    //Security type no good  :-(
                    SYS_CONSOLE_MESSAGE("\r\n1.5 Unknown key type on www\r\n");
                    goto ConfigFailure;
                }
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"key"))
            {// Read new key material
                uint8_t key_size = 0, ascii_key = 0;
                switch ((uint8_t)CFGCXT.security) {
                    case DRV_WIFI_SECURITY_OPEN:     //keep compiler happy, nothing to do here!
                        break;
                    case DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE:  //wpa passphrase
                        //putrsUART((ROM char*)"\r\nPassphrase type of key! ");
                        ascii_key = 1;
                        key_size = strlen((char *)(httpDataBuff+6));
                        //between 8-63 characters, passphrase
                        if ((key_size < 8 ) || (key_size > 63))
                              goto ConfigFailure;
                        break;
                    case DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY: //wpa pre-calculated key!!!
                        key_size = 64;
                        break;
                    case DRV_WIFI_SECURITY_WEP_40:
                        key_size = 10; /* Assume hex size */
                        if (strlen((char *)(httpDataBuff+6)) == 5) {
                            key_size = 5;  /* ASCII key support */
                            ascii_key = 1;
                         }
                        CFGCXT.defaultWepKey = 0; /* Example uses only key idx 0 (sometimes called 1) */
                        break;
                    case DRV_WIFI_SECURITY_WEP_104:
                        key_size = 26; /* Assume hex size */
                        if (strlen((char *)(httpDataBuff+6)) == 13) {
                            key_size = 13;    /* ASCII key support */
                            ascii_key = 1;
                        }
                        CFGCXT.defaultWepKey = 0; /* Example uses only key idx 0 (sometimes called 1) */
                        break;
                }
                if (strlen((char *)(httpDataBuff+6)) != key_size) {
                    SYS_CONSOLE_MESSAGE("\r\nIncomplete key received\r\n");
                    goto ConfigFailure;
                }
                memcpy(CFGCXT.key, (void*)(httpDataBuff+6), key_size);
                CFGCXT.key[key_size] = 0; /* terminate string */
                CFGCXT.SecurityKeyLength = key_size;
                if (!ascii_key) {
                    //if ((cfg.security == sec_wep64) || (cfg.security == sec_wep128))
                        key_size /= 2;
                        //CFGCXT.SecurityKeyLength = key_size;   // yes Or No? Need more debug
                    if (!convertAsciiToHexInPlace((char *)&CFGCXT.key[0], key_size)) {
                        SYS_CONSOLE_MESSAGE("\r\nFailed to convert ASCII to hex!\r\n");
                        goto ConfigFailure;
                    }
                }
            }
            else if(!strcmp((char*)httpDataBuff, "ssid"))
            {// Get new ssid and make sure it is valid
                if(strlen((char*)(httpDataBuff+6)) < 33u)
                {
                    memcpy(CFGCXT.ssid, (void*)(httpDataBuff+6), strlen((char*)(httpDataBuff+6)));
                    CFGCXT.ssid[strlen((char*)(httpDataBuff+6))] = 0; /* Terminate string */

                    /* save current profile SSID for displaying later */
                    DRV_WIFI_SsidGet((uint8_t*)&CFGCXT.prevSSID, &ssidLen);
                    CFGCXT.prevSSID[ssidLen] = 0;
                }
                else
                {    //Invalid SSID... fail :-(
                    goto ConfigFailure;
                }
            }
            else if(!strcmp((char*)httpDataBuff, (const char*)"wlan"))
            {// Get the wlan mode: adhoc or infrastructure
                char mode[6];
                if (strlen((char*)(httpDataBuff+6)) > 5) /* Sanity check */
                    goto ConfigFailure;

                memcpy(mode, (void*)(httpDataBuff+6), strlen((char*)(httpDataBuff+6)));
                mode[strlen((char*)(httpDataBuff+6))] = 0; /* Terminate string */
                if(!strcmp((char*)mode, (const char*)"infra"))
                {
                    SYS_CONSOLE_MESSAGE((const char*)"\r\nSetting mode to infrastructure!\r\n");
                    CFGCXT.type = DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE;
                }
                else if(!strcmp((char*)mode, "adhoc"))
                {
                    DRV_WIFI_ADHOC_NETWORK_CONTEXT adhocContext;

                    SYS_CONSOLE_MESSAGE((const char*)"\r\nSetting mode to adhoc!\r\n");
                    CFGCXT.type = DRV_WIFI_NETWORK_TYPE_ADHOC;

                    // always setup adhoc to attempt to connect first, then start
                    adhocContext.mode = DRV_WIFI_ADHOC_CONNECT_THEN_START;
                    adhocContext.beaconPeriod = DRV_WIFI_DEFAULT_ADHOC_BEACON_PERIOD;
                    adhocContext.hiddenSsid   = DRV_WIFI_DEFAULT_ADHOC_HIDDEN_SSID;
                    DRV_WIFI_AdhocContextSet(&adhocContext);
                }
                else
                {    //Mode type no good  :-(
                    //memset(LCDText, ' ', 32);
                    //putrsUART((ROM char*)"\r\nUnknown mode type on www! ");
                    //strcpy((char*)LCDText, (char*)mode);
                    //LCDUpdate();
                    SYS_CONSOLE_MESSAGE((const char*)"\r\nUnknown mode type on www! ");
                    goto ConfigFailure;
                }

                // save old WLAN mode
                DRV_WIFI_NetworkTypeGet(&CFGCXT.prevWLAN);
            }
        }

        /* Check if WPA hasn't been selected with adhoc, if it has we choke! */
        if ((CFGCXT.type == DRV_WIFI_NETWORK_TYPE_ADHOC) &&
          ((CFGCXT.security == DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE) || (CFGCXT.security == DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY)))
            goto ConfigFailure;

        /*
         * All parsing complete!  If we have got to here all data has been validated and
         * We can handle what is necessary to start the reconfigure process of the WiFi device
         */
#if defined ( EZ_CONFIG_STORE )
        /* Copy wifi cfg data to be committed to NVM */
        //TCPIP_NET_IF* p_config= (TCPIP_NET_IF*)GetNetworkConfig();
        strcpy((char *)p_wifi_ConfigData->netSSID, (char *)CFGCXT.ssid);
        p_wifi_ConfigData->SsidLength = strlen((char*)(CFGCXT.ssid));
        /* Going to set security type */
        p_wifi_ConfigData->SecurityMode = CFGCXT.security;
        /* Going to save the key, if required */
        if (CFGCXT.security != DRV_WIFI_SECURITY_OPEN) {
            uint8_t  key_size =0;

            switch ((uint8_t)CFGCXT.security) {
                case DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE:  //wpa passphrase
                    key_size = strlen((char*)(CFGCXT.key)); //ascii so use strlen
                    break;
                case DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY: //wpa pre-calculated key!!!
                    key_size = 32;
                    break;
                case DRV_WIFI_SECURITY_WEP_40:
                    key_size = 5;
                    break;
                case DRV_WIFI_SECURITY_WEP_104:
                    key_size = 13;
                    break;

            }

            memcpy(p_wifi_ConfigData->SecurityKey, CFGCXT.key, key_size);
            p_wifi_ConfigData->SecurityKey[strlen((char*)(CFGCXT.key))] = 0;
            p_wifi_ConfigData->SecurityKeyLength = key_size;

        }
        /* Going to save the network type */
        p_wifi_ConfigData->networkType = CFGCXT.type;
        p_wifi_ConfigData->dataValid = 1; /* Validate wifi configuration */
#endif // EZ_CONFIG_STORE

                strcpy((char*)httpDataBuff, "/reconnect.htm");
                //memcpy((void*)(httpDataBuff+14), TCPIP_STACK_NetBIOSName(newNet), 16);
               // httpDataBuff[14+16] = 0x00;    // Force null termination
               // for(i = 14; i < 14u+16u; i++)
                {
                //    if(httpDataBuff[i] == ' ')
        //    httpDataBuff[i] = 0x00;
                }
                TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
                WF_START_EASY_CONFIG();
                WifiAsyncSetEventPending(ASYNC_EASY_CONFIG_PENDING);


        return HTTP_IO_DONE;


    ConfigFailure:
                lastFailure = true;
                if(httpDataBuff)
                {
                    strcpy((char*)httpDataBuff, "/error.htm");
                }
                TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
        return HTTP_IO_DONE;
}

#endif    

/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostConfig(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the configuration form on config/index.htm

  Description:
    Accepts configuration parameters from the form, saves them to a
    temporary location in RAM, then eventually saves the data to EEPROM or
    external Flash.

    When complete, this function redirects to config/reboot.htm, which will
    display information on reconnecting to the board.

    This function creates a shadow copy of a network info structure in
    RAM and then overwrites incoming data there as it arrives.  For each
    name/value pair, the name is first read to cur connection data[0:5].  Next, the
    value is read to newNetConfig.  Once all data has been read, the new
    network info structure is saved back to storage and the browser is redirected to
    reboot.htm.  That file includes an AJAX call to reboot.cgi, which
    performs the actual reboot of the machine.

    If an IP address cannot be parsed, too much data is POSTed, or any other
    parsing error occurs, the browser reloads config.htm and displays an error
    message at the top.

  Precondition:
    None

  Parameters:
    None

  Return Values:
      HTTP_IO_DONE - all parameters have been processed
      HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(HTTP_APP_USE_RECONFIG)
static HTTP_IO_RESULT HTTPPostConfig(HTTP_CONN_HANDLE connHandle)
{
    // room to store the new network configuration/information
    // to be sure that always you have the right amount of space neede
    // dynamic allocation should be used
    uint8_t newNetInfo[200];
    uint8_t *ptr;
    uint8_t i;
    TCPIP_NET_HANDLE currNet, newNet;
    IPV4_ADDR newIPAddress, newMask;
    TCPIP_MAC_ADDR    myMACAddr;
    uint32_t byteCount;
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff = 0;

    
    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to the network info and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of network info someplace
    // in memory and using it instead of newNetInfo.  Lastly, you could
    // increase the TCP RX FIFO size for the HTTP server.  This will allow more
    // data to be POSTed by the web browser before hitting this limit.
    byteCount = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(byteCount > TCPIP_TCP_GetIsReady(sktHTTP) + TCPIP_TCP_FifoRxFreeGet(sktHTTP))
        goto ConfigFailure;

    // current interface we're working on
    currNet = TCPIP_TCP_SocketNetGet(sktHTTP);
    // ensure our static approach is working OK
    if(sizeof(newNetInfo) < TCPIP_STACK_NetInfoSize(currNet))
    {
        goto ConfigFailure;
    }
    
    // create a copy of the existent network configuration
    newNet = TCPIP_STACK_NetInfoCreate(currNet, newNetInfo, sizeof(newNetInfo), true);
    if(newNet == 0)
    {
        goto ConfigFailure;
    }
    
    // Ensure that all data is waiting to be parsed.  If not, keep waiting for 
    // all of it to arrive.
    if(TCPIP_TCP_GetIsReady(sktHTTP) < byteCount)
        return HTTP_IO_NEED_DATA;

        

    // Start out assuming that DHCP is disabled.  This is necessary since the
    // browser doesn't submit this field if it is unchecked (meaning zero).
    // However, if it is checked, this will be overridden since it will be
    // submitted.
    TCPIP_DHCP_Disable(newNet);

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Read all browser POST data
    while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
    {
        // Read a form field name
        if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, 6) != HTTP_READ_OK)
            goto ConfigFailure;

        // Read a form field value
        if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, HTTP_MAX_DATA_LEN-6-2) != HTTP_READ_OK)
            goto ConfigFailure;

        // Parse the value that was read
        if(!strcmp((char*)httpDataBuff, (const char*)"ip"))
        {// Read new static IP Address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress))
                goto ConfigFailure;

            TCPIP_STACK_NetAddressSet(newNet, &newIPAddress, 0, true);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"gw"))
        {// Read new gateway address
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress))
                goto ConfigFailure;

            TCPIP_STACK_NetAddressGatewaySet(newNet, &newIPAddress);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"sub"))
        {// Read new static subnet
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newMask))
                goto ConfigFailure;

			TCPIP_STACK_NetAddressSet(newNet, 0, &newMask, true);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"dns1"))
        {// Read new primary DNS server
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress))
                goto ConfigFailure;
            TCPIP_STACK_NetAddressDnsPrimarySet(newNet, &newIPAddress);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"dns2"))
        {// Read new secondary DNS server
            if(!TCPIP_Helper_StringToIPAddress((char*)(httpDataBuff+6), &newIPAddress))
                goto ConfigFailure;
            TCPIP_STACK_NetAddressDnsSecondSet(newNet, &newIPAddress);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"mac"))
        {
            // Read new MAC address
            uint16_t w;
            uint8_t i;

            ptr = httpDataBuff+6;

            for(i = 0; i < 12u; i++)
            {// Read the MAC address

                // Skip non-hex bytes
                while( *ptr != 0x00u && !(*ptr >= '0' && *ptr <= '9') && !(*ptr >= 'A' && *ptr <= 'F') && !(*ptr >= 'a' && *ptr <= 'f') )
                    ptr++;

                // MAC string is over, so zeroize the rest
                if(*ptr == 0x00u)
                {
                    for(; i < 12u; i++)
                        httpDataBuff[i] = '0';
                    break;
                }

                // Save the MAC byte
                httpDataBuff[i] = *ptr++;
            }

            // Read MAC Address, one byte at a time
            for(i = 0; i < 6u; i++)
            {
                ((uint8_t*)&w)[1] = httpDataBuff[i*2];
                ((uint8_t*)&w)[0] = httpDataBuff[i*2+1];
                myMACAddr.v[i] = hexatob(w);
            }
            TCPIP_STACK_NetAddressMacSet(newNet, &myMACAddr);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"host"))
        {// Read new hostname
            TCPIP_STACK_NetBiosNameSet(newNet, (const char* )&httpDataBuff[6]);
        }
        else if(!strcmp((char*)httpDataBuff, (const char*)"dhcp"))
        {// Read new DHCP Enabled flag
            if(httpDataBuff[6] == '1')
                TCPIP_DHCP_Enable(newNet);
        }
    }


    // Set the board to reboot and display reconnecting information
    strcpy((char*)httpDataBuff, "/protect/reboot.htm?");
    memcpy((void*)(httpDataBuff+20), TCPIP_STACK_NetBIOSName(newNet), 16);
    httpDataBuff[20+16] = 0x00;    // Force null termination
    for(i = 20; i < 20u+16u; i++)
    {
        if(httpDataBuff[i] == ' ')
            httpDataBuff[i] = 0x00;
    }
    TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);

    return HTTP_IO_DONE;


ConfigFailure:
    lastFailure = true;
    if(httpDataBuff)
    {
        strcpy((char*)httpDataBuff, "/protect/config.htm");
    }
    TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);

    return HTTP_IO_DONE;
}

#if defined(TCPIP_STACK_USE_SNMP_SERVER)
static HTTP_IO_RESULT HTTPPostSNMPCommunity(HTTP_CONN_HANDLE connHandle)
{
    uint8_t vCommunityIndex;
    uint8_t *dest;
    uint8_t* httpDataBuff;
    TCP_SOCKET sktHTTP;

    #define SM_CFG_SNMP_READ_NAME    (0u)
    #define SM_CFG_SNMP_READ_VALUE    (1u)

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    switch(TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle))
    {
        case SM_CFG_SNMP_READ_NAME:
            // If all parameters have been read, end
            if(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle) == 0u)
            {
                return HTTP_IO_DONE;
            }

            // Read a name
            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, sizeof(httpDataBuff)-2) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move to reading a value, but no break
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_CFG_SNMP_READ_VALUE);

        case SM_CFG_SNMP_READ_VALUE:
            // Read a value
            if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff + 6, sizeof(httpDataBuff)-6-2) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Default action after this is to read the next name, unless there's an error
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_CFG_SNMP_READ_NAME);

            // See if this is a known parameter and legal (must be null
            // terminator in 4th field name byte, string must no greater than
            // SNMP_COMMUNITY_MAX_LEN bytes long, and SNMP_MAX_COMMUNITY_SUPPORT
            // must not be violated.
            vCommunityIndex = httpDataBuff[3] - '0';
            if(vCommunityIndex >= SNMP_MAX_COMMUNITY_SUPPORT)
                break;
            if(httpDataBuff[4] != 0x00u)
                break;
            if(memcmp((void*)httpDataBuff, (const void*)"rcm", 3) == 0)
                dest = ((SNMP_NET_CONFIG*)TCPIP_TCP_SocketNetGet(sktHTTP))->readCommunity[vCommunityIndex];
            else if(memcmp((void*)httpDataBuff, (const void*)"wcm", 3) == 0)
                dest = ((SNMP_NET_CONFIG*)TCPIP_TCP_SocketNetGet(sktHTTP))->writeCommunity[vCommunityIndex];
            else
                break;
            if(strlen((char*)httpDataBuff + 6) > SNMP_COMMUNITY_MAX_LEN)
                break;

            // String seems valid, lets copy it to the network configuration
            strcpy((char*)dest, (char*)httpDataBuff+6);
            break;
    }

    return HTTP_IO_WAITING;        // Assume we're waiting to process more data
}
#endif //#if defined(TCPIP_STACK_USE_SNMP_SERVER)

#endif    // #if defined(HTTP_APP_USE_RECONFIG)

/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostMD5(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the file upload form on upload.htm

  Description:
    This function demonstrates the processing of file uploads.  First, the
    function locates the file data, skipping over any headers that arrive.
    Second, it reads the file 64 bytes at a time and hashes that data.  Once
    all data has been received, the function calculates the MD5 sum and
    stores it in current connection data buffer.

    After the headers, the first line from the form will be the MIME
    separator.  Following that is more headers about the file, which we
    discard.  After another CRLFCRLF, the file data begins, and we read
    it 16 bytes at a time and add that to the MD5 calculation.  The reading
    terminates when the separator string is encountered again on its own
    line.  Notice that the actual file data is trashed in this process,
    allowing us to accept files of arbitrary size, not limited by RAM.
    Also notice that the data buffer is used as an arbitrary storage array
    for the result.  The ~uploadedmd5~ callback reads this data later to
    send back to the client.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    HTTP_IO_DONE - all parameters have been processed
    HTTP_IO_WAITING - the function is pausing to continue later
    HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(HTTP_APP_USE_MD5)
static HTTP_IO_RESULT HTTPPostMD5(HTTP_CONN_HANDLE connHandle)
{
    uint16_t lenA, lenB;
    static HASH_SUM md5;            // Assume only one simultaneous MD5
    TCP_SOCKET sktHTTP;
    uint8_t* httpDataBuff;

    #define SM_MD5_READ_SEPARATOR    (0u)
    #define SM_MD5_SKIP_TO_DATA        (1u)
    #define SM_MD5_READ_DATA        (2u)
    #define SM_MD5_POST_COMPLETE    (3u)

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    switch(TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle))
    {
        // Just started, so try to find the separator string
        case SM_MD5_READ_SEPARATOR:
            // Reset the MD5 calculation
            MD5Initialize(&md5);

            // See if a CRLF is in the buffer
            lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"\r\n", 2, 0, 0, false);
            if(lenA == 0xffff)
            {//if not, ask for more data
                return HTTP_IO_NEED_DATA;
            }

            // If so, figure out where the last byte of data is
            // Data ends at CRLFseparator--CRLF, so 6+len bytes
            TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA + 6);

            // Read past the CRLF
            TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle,  TCPIP_TCP_ArrayGet(sktHTTP, NULL, lenA+2));

            // Save the next state (skip to CRLFCRLF)
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_MD5_SKIP_TO_DATA);

            // No break...continue reading the headers if possible

        // Skip the headers
        case SM_MD5_SKIP_TO_DATA:
            // Look for the CRLFCRLF
            lenA = TCPIP_TCP_ArrayFind(sktHTTP, (const uint8_t*)"\r\n\r\n", 4, 0, 0, false);

            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPIP_TCP_ArrayGet(sktHTTP, NULL, lenA+4);
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_MD5_READ_DATA);
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPIP_TCP_ArrayGet(sktHTTP, NULL, TCPIP_TCP_GetIsReady(sktHTTP) - 4);
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenA);

                // Return the need more data flag
                return HTTP_IO_NEED_DATA;
            }

            // No break if we found the header terminator

        // Read and hash file data
        case SM_MD5_READ_DATA:
            // Find out how many bytes are available to be read
            httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
            lenA = TCPIP_TCP_GetIsReady(sktHTTP);
            lenB = TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle);
            if(lenA > lenB)
                lenA = lenB;

            while(lenA > 0u)
            {// Add up to 64 bytes at a time to the sum
                lenB = TCPIP_TCP_ArrayGet(sktHTTP, httpDataBuff, (lenA < 64u)?lenA:64);
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, lenB);
                lenA -= lenB;
                MD5AddData(&md5, httpDataBuff, lenB);
            }

            // If we've read all the data
            if(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle) == 0u)
            {// Calculate and copy result data buffer for printout
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_MD5_POST_COMPLETE);
                MD5Calculate(&md5, httpDataBuff);
                return HTTP_IO_DONE;
            }

            // Ask for more data
            return HTTP_IO_NEED_DATA;
    }

    return HTTP_IO_DONE;
}
#endif // #if defined(HTTP_APP_USE_MD5)

/*****************************************************************************
  Function:
    static HTTP_IO_RESULT HTTPPostEmail(HTTP_CONN_HANDLE connHandle)

  Summary:
    Processes the e-mail form on email/index.htm

  Description:
    This function sends an e-mail message using the SMTP client and
    optionally encrypts the connection to the SMTP server using SSL.  It
    demonstrates the use of the SMTP client, waiting for asynchronous
    processes in an HTTP callback, and how to send e-mail attachments using
    the stack.

    Messages with attachments are sent using multipart/mixed MIME encoding,
    which has three sections.  The first has no headers, and is only to be
    displayed by old clients that cannot interpret the MIME format.  (The
    overwhelming majority of these clients have been obseleted, but the
    so-called "ignored" section is still used.)  The second has a few
    headers to indicate that it is the main body of the message in plain-
    text encoding.  The third section has headers indicating an attached
    file, along with its name and type.  All sections are separated by a
    boundary string, which cannot appear anywhere else in the message.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    HTTP_IO_DONE - the message has been sent
    HTTP_IO_WAITING - the function is waiting for the SMTP process to complete
    HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(TCPIP_STACK_USE_SMTP_CLIENT)
static HTTP_IO_RESULT HTTPPostEmail(HTTP_CONN_HANDLE connHandle)
{
    static uint8_t *ptrData;
    static uint8_t *szPort;
    static SMTP_POINTERS mySMTPClient;
    #if defined(TCPIP_STACK_USE_SSL_CLIENT)
    static uint8_t *szUseSSL;
    #endif
    uint16_t len, rem;
    uint8_t cName[8];
    uint8_t* httpDataBuff;
    TCP_SOCKET sktHTTP;

    #define SM_EMAIL_CLAIM_MODULE                (0u)
    #define SM_EMAIL_READ_PARAM_NAME            (1u)
    #define SM_EMAIL_READ_PARAM_VALUE            (2u)
    #define SM_EMAIL_PUT_IGNORED                (3u)
    #define SM_EMAIL_PUT_BODY                    (4u)
    #define SM_EMAIL_PUT_ATTACHMENT_HEADER        (5u)
    #define SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS    (6u)
    #define SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS    (7u)
    #define SM_EMAIL_PUT_ATTACHMENT_DATA_POT    (8u)
    #define SM_EMAIL_PUT_TERMINATOR                (9u)
    #define SM_EMAIL_FINISHING                    (10u)


    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    switch(TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle))
    {
        case SM_EMAIL_CLAIM_MODULE:
            // Try to claim module
            if(TCPIP_SMTP_UsageBegin())
            {// Module was claimed, so set up static parameters
                memset(&mySMTPClient, 0, sizeof(mySMTPClient));
                mySMTPClient.Subject = "Microchip TCP/IP Stack Status Update";
                mySMTPClient.From = "\"SMTP Service\" <mchpboard@picsaregood.com>";

                // The following two lines indicate to the receiving client that
                // this message has an attachment.  The boundary field *must not*
                // be included anywhere in the content of the message.  In real
                // applications it is typically a long random string.
                mySMTPClient.OtherHeaders = "MIME-version: 1.0\r\nContent-type: multipart/mixed; boundary=\"frontier\"\r\n";

                // Move our state machine forward
                ptrData = httpDataBuff;
                szPort = NULL;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_NAME);
            }
            return HTTP_IO_WAITING;

        case SM_EMAIL_READ_PARAM_NAME:
            // Search for a parameter name in POST data
            if(TCPIP_HTTP_PostNameRead(connHandle, cName, sizeof(cName)) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Try to match the name value
            if(!strcmp((char*)cName, (const char*)"server"))
            {// Read the server name
                mySMTPClient.Server = (char*)ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            else if(!strcmp((char*)cName, (const char*)"port"))
            {// Read the server port
                szPort = ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            #if defined(TCPIP_STACK_USE_SSL_CLIENT)
            else if(!strcmp((char*)cName, (const char*)"ssl"))
            {// Read the server port
                szUseSSL = ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            #endif
            else if(!strcmp((char*)cName, (const char*)"user"))
            {// Read the user name
                mySMTPClient.Username = (char*)ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            else if(!strcmp((char*)cName, (const char*)"pass"))
            {// Read the password
                mySMTPClient.Password = (char*)ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            else if(!strcmp((char*)cName, (const char*)"to"))
            {// Read the To string
                mySMTPClient.To = (char*)ptrData;
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }
            else if(!strcmp((char*)cName, (const char*)"msg"))
            {// Done with headers, move on to the message
                // Delete paramters that are just null strings (no data from user) or illegal (ex: password without username)
                if(mySMTPClient.Server )
                    if(*mySMTPClient.Server == 0x00u)
                        mySMTPClient.Server = NULL;
                if(mySMTPClient.Username )
                    if(*mySMTPClient.Username == 0x00u)
                        mySMTPClient.Username = NULL;
                if(mySMTPClient.Password)
                    if((*mySMTPClient.Password == 0x00u) || (mySMTPClient.Username == NULL))
                        mySMTPClient.Password = NULL;

                // Decode server port string if it exists
                if(szPort)
                    if(*szPort)
                        mySMTPClient.ServerPort = (uint16_t)atol((char*)szPort);

                // Determine if SSL should be used
                #if defined(TCPIP_STACK_USE_SSL_CLIENT)
                if(szUseSSL)
                    if(*szUseSSL == '1')
                        mySMTPClient.UseSSL = true;
                #endif

                // Start sending the message
				TCPIP_SMTP_MailSend(&mySMTPClient);
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_IGNORED);
                return HTTP_IO_WAITING;
            }
            else
            {// Don't know what we're receiving
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_VALUE);
            }

            // No break...continue to try reading the value

        case SM_EMAIL_READ_PARAM_VALUE:
            // Search for a parameter value in POST data
            rem = HTTP_MAX_DATA_LEN - (ptrData - httpDataBuff);
            if(TCPIP_HTTP_PostValueRead(connHandle, ptrData, rem) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move past the data that was just read
            ptrData += strlen((char*)ptrData);
            if(ptrData < httpDataBuff + HTTP_MAX_DATA_LEN - 1)
                ptrData += 1;

            // Try reading the next parameter
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_READ_PARAM_NAME);
            return HTTP_IO_WAITING;

        case SM_EMAIL_PUT_IGNORED:
            // This section puts a message that is ignored by compatible clients.
            // This text will not display unless the receiving client is obselete
            // and does not understand the MIME structure.
            // The "--frontier" indicates the start of a section, then any
            // needed MIME headers follow, then two CRLF pairs, and then
            // the actual content (which will be the body text in the next state).

            // Check to see if a failure occured
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 90u)
                return HTTP_IO_WAITING;

            // Write the ignored text
            TCPIP_SMTP_StringPut("This is a multi-part message in MIME format.\r\n");
            TCPIP_SMTP_StringPut("--frontier\r\nContent-type: text/plain\r\n\r\n");
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_BODY);

        case SM_EMAIL_PUT_BODY:
            // Write as much body text as is available from the TCP buffer
            // return HTTP_IO_NEED_DATA or HTTP_IO_WAITING
            // On completion, => PUT_ATTACHMENT_HEADER and continue

            // Check to see if a failure occurred
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // Loop as long as data remains to be read
            while(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle))
            {
                // See if space is available to write
                len = TCPIP_SMTP_IsPutReady();
                if(len == 0u)
                    return HTTP_IO_WAITING;

                // See if data is ready to be read
                rem = TCPIP_TCP_GetIsReady(sktHTTP);
                if(rem == 0u)
                    return HTTP_IO_NEED_DATA;

                // Only write as much as we can handle
                if(len > rem)
                    len = rem;
                if(len > HTTP_MAX_DATA_LEN - 2)
                    len = HTTP_MAX_DATA_LEN - 2;

                // Read the data from HTTP POST buffer and send it to SMTP
                TCPIP_HTTP_CurrentConnectionByteCountDec(connHandle, TCPIP_TCP_ArrayGet(sktHTTP, httpDataBuff, len));
                httpDataBuff[len] = '\0';
                TCPIP_HTTP_URLDecode(httpDataBuff);
                TCPIP_SMTP_StringPut((char*)httpDataBuff);
                TCPIP_SMTP_Flush();
            }

            // We're done with the POST data, so continue
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_ATTACHMENT_HEADER);

        case SM_EMAIL_PUT_ATTACHMENT_HEADER:
            // This section writes the attachment to the message.
            // This portion generally will not display in the reader, but
            // will be downloadable to the local machine.  Use caution
            // when selecting the content-type and file name, as certain
            // types and extensions are blocked by virus filters.

            // The same structure as the message body is used.
            // Any attachment must not include high-bit ASCII characters or
            // binary data.  If binary data is to be sent, the data should
            // be encoded using Base64 and a MIME header should be added:
            // Content-transfer-encoding: base64

            // Check to see if a failure occurred
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 100u)
                return HTTP_IO_WAITING;

            // Write the attachment header
            TCPIP_SMTP_StringPut("\r\n--frontier\r\nContent-type: text/csv\r\nContent-Disposition: attachment; filename=\"status.csv\"\r\n\r\n");
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS);

        case SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS:
            // The following states output the system status as a CSV file.

            // Check to see if a failure occurred
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 36u)
                return HTTP_IO_WAITING;

            // Write the header and button strings
            TCPIP_SMTP_StringPut("SYSTEM STATUS\r\n");
            TCPIP_SMTP_StringPut("Buttons:,");
            TCPIP_SMTP_Put(BUTTON0_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(BUTTON1_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(BUTTON2_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(BUTTON3_IO + '0');
            TCPIP_SMTP_Put('\r');
            TCPIP_SMTP_Put('\n');
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS);

        case SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS:
            // Check to see if a failure occurred
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 30u)
                return HTTP_IO_WAITING;

            // Write the header and button strings
            TCPIP_SMTP_StringPut("LEDs:,");
            TCPIP_SMTP_Put(LED0_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED1_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED2_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED3_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED4_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED5_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED6_IO + '0');
            TCPIP_SMTP_Put(',');
            TCPIP_SMTP_Put(LED7_IO + '0');
            TCPIP_SMTP_Put('\r');
            TCPIP_SMTP_Put('\n');
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_ATTACHMENT_DATA_POT);

        case SM_EMAIL_PUT_ATTACHMENT_DATA_POT:
            // Check to see if a failure occurred
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 16u)
                return HTTP_IO_WAITING;

            // Do the A/D conversion
            len = (uint16_t)ADC1BUF0;
            uitoa(len, (uint8_t*)&httpDataBuff[1]);

            // Write the header and button strings
            TCPIP_SMTP_StringPut("Pot:,");
            TCPIP_SMTP_StringPut((char*)(httpDataBuff+1));
            TCPIP_SMTP_Put('\r');
            TCPIP_SMTP_Put('\n');
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_PUT_TERMINATOR);

        case SM_EMAIL_PUT_TERMINATOR:
            // This section finishes the message
            // This consists of two dashes, the boundary, and two more dashes
            // on a single line, followed by a CRLF pair to terminate the message.

            // Check to see if a failure occured
            if(!TCPIP_SMTP_IsBusy())
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(TCPIP_SMTP_IsPutReady() < 16u)
                return HTTP_IO_WAITING;

            // Write the ignored text
            TCPIP_SMTP_StringPut("--frontier--\r\n");
            TCPIP_SMTP_PutIsDone();
            TCPIP_SMTP_Flush();

            // Move to the next state
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_EMAIL_FINISHING);

        case SM_EMAIL_FINISHING:
            // Wait for status
            if(!TCPIP_SMTP_IsBusy())
            {
                // Release the module and check success
                // Redirect the user based on the result
                if(TCPIP_SMTP_UsageEnd() == SMTP_SUCCESS)
                    lastSuccess = true;
                else
                    lastFailure = true;

                // Redirect to the page
                strcpy((char*)httpDataBuff, "/email/index.htm");
                TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
                return HTTP_IO_DONE;
            }

            return HTTP_IO_WAITING;
    }

    return HTTP_IO_DONE;
}
#endif    // #if defined(TCPIP_STACK_USE_SMTP_CLIENT)

/****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPPostDDNSConfig(HTTP_CONN_HANDLE connHandle)
    
  Summary:
    Parsing and collecting http data received from http form.

  Description:
    This routine will be excuted every time the Dynamic DNS Client
    configuration form is submitted.  The http data is received 
    as a string of the variables seperated by '&' characters in the TCP RX
    buffer.  This data is parsed to read the required configuration values, 
    and those values are populated to the global array (DDNSData) reserved 
    for this purpose.  As the data is read, DDNSPointers is also populated
    so that the dynamic DNS client can execute with the new parameters.
    
  Precondition:
     cur HTTP connection is loaded.

  Parameters:
    None.

  Return Values:
    HTTP_IO_DONE         -  Finished with procedure
    HTTP_IO_NEED_DATA    -  More data needed to continue, call again later
    HTTP_IO_WAITING     -  Waiting for asynchronous process to complete,
                            call again later
  ***************************************************************************/
#if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
static HTTP_IO_RESULT HTTPPostDDNSConfig(HTTP_CONN_HANDLE connHandle)
{
    static uint8_t *ptrDDNS;
    uint8_t* httpDataBuff;
    uint8_t    smPost;

    #define SM_DDNS_START            (0u)
    #define SM_DDNS_READ_NAME        (1u)
    #define SM_DDNS_READ_VALUE        (2u)
    #define SM_DDNS_READ_SERVICE    (3u)
    #define SM_DDNS_DONE            (4u)

    #define DDNS_SPACE_REMAINING                (sizeof(DDNSData) - (ptrDDNS - DDNSData))

    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);
    smPost = TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle);
    switch(smPost)
    {
        // Sets defaults for the system
        case SM_DDNS_START:
            ptrDDNS = DDNSData;
            TCPIP_DDNS_ServiceSet(0);
            DDNSClient.Host.szROM = NULL;
            DDNSClient.Username.szROM = NULL;
            DDNSClient.Password.szROM = NULL;
            DDNSClient.ROMPointers.Host = 0;
            DDNSClient.ROMPointers.Username = 0;
            DDNSClient.ROMPointers.Password = 0;
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, ++smPost);

        // Searches out names and handles them as they arrive
        case SM_DDNS_READ_NAME:
            // If all parameters have been read, end
            if(TCPIP_HTTP_CurrentConnectionByteCountGet(connHandle) == 0u)
            {
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_DDNS_DONE);
                break;
            }

            // Read a name
            if(TCPIP_HTTP_PostNameRead(connHandle, httpDataBuff, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            if(!strcmp((char *)httpDataBuff, (const char*)"service"))
            {
                // Reading the service (numeric)
                TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_DDNS_READ_SERVICE);
                break;
            }
            else if(!strcmp((char *)httpDataBuff, (const char*)"user"))
                DDNSClient.Username.szRAM = ptrDDNS;
            else if(!strcmp((char *)httpDataBuff, (const char*)"pass"))
                DDNSClient.Password.szRAM = ptrDDNS;
            else if(!strcmp((char *)httpDataBuff, (const char*)"host"))
                DDNSClient.Host.szRAM = ptrDDNS;

            // Move to reading the value for user/pass/host
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, ++smPost);

        // Reads in values and assigns them to the DDNS RAM
        case SM_DDNS_READ_VALUE:
            // Read a name
            if(TCPIP_HTTP_PostValueRead(connHandle, ptrDDNS, DDNS_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move past the data that was just read
            ptrDDNS += strlen((char*)ptrDDNS);
            if(ptrDDNS < DDNSData + sizeof(DDNSData) - 1)
                ptrDDNS += 1;

            // Return to reading names
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_DDNS_READ_NAME);
            break;

        // Reads in a service ID
        case SM_DDNS_READ_SERVICE:
            // Read the integer id
            if(TCPIP_HTTP_PostValueRead(connHandle, httpDataBuff, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Convert to a service ID
            TCPIP_DDNS_ServiceSet((uint8_t)atol((char*)httpDataBuff));

            // Return to reading names
            TCPIP_HTTP_CurrentConnectionPostSmSet(connHandle, SM_DDNS_READ_NAME);
            break;

        // Sets up the DDNS client for an update
        case SM_DDNS_DONE:
            // Since user name and password changed, force an update immediately
            TCPIP_DDNS_UpdateForce();

            // Redirect to prevent POST errors
            lastSuccess = true;
            strcpy((char*)httpDataBuff, "/dyndns/index.htm");
            TCPIP_HTTP_CurrentConnectionStatusSet(connHandle, HTTP_REDIRECT);
            return HTTP_IO_DONE;
    }

    return HTTP_IO_WAITING;        // Assume we're waiting to process more data
}
#endif    // #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)

#endif //(use_post)


/****************************************************************************
  Section:
    Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
    void HTTPPrint_varname(HTTP_CONN_HANDLE connHandle)

  Internal:
      See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/

void HTTPPrint_builddate(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
    if(TCPIP_TCP_PutIsReady(sktHTTP) < strlen((const char*)__DATE__" "__TIME__))
        return;
 
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
    TCPIP_TCP_StringPut(sktHTTP, (const void*)__DATE__" "__TIME__);
}

void HTTPPrint_version(HTTP_CONN_HANDLE connHandle)
{
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const void*)TCPIP_STACK_VERSION);
}




const uint8_t HTML_UP_ARROW[] = "up";
const uint8_t HTML_DOWN_ARROW[] = "dn";

void HTTPPrint_btn(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
    // Determine which button
    switch(num)
    {
        case 0:
            num = BUTTON0_IO;
            break;
        case 1:
            num = BUTTON1_IO;
            break;
        case 2:
            num = BUTTON2_IO;
            break;
        case 3:
            num = BUTTON3_IO;
            break;
        default:
            num = 0;
    }

    // Print the output
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (num?HTML_UP_ARROW:HTML_DOWN_ARROW));
}

void HTTPPrint_led(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
    // Determine which LED
    switch(num)
    {
        case 0:
            num = LED0_IO;
            break;
        case 1:
            num = LED1_IO;
            break;
        case 2:
            num = LED2_IO;
            break;
        case 3:
            num = LED3_IO;
            break;
        case 4:
            num = LED4_IO;
            break;
        case 5:
            num = LED5_IO;
            break;
        case 6:
            num = LED6_IO;
            break;
        case 7:
            num = LED7_IO;
            break;

        default:
            num = 0;
    }

    // Print the output
    TCPIP_TCP_Put(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (num?'1':'0'));
}

void HTTPPrint_ledSelected(HTTP_CONN_HANDLE connHandle, uint16_t num, uint16_t state)
{
    // Determine which LED to check
    switch(num)
    {
        case 0:
            num = LED0_IO;
            break;
        case 1:
            num = LED1_IO;
            break;
        case 2:
            num = LED2_IO;
            break;
        case 3:
            num = LED3_IO;
            break;
        case 4:
            num = LED4_IO;
            break;
        case 5:
            num = LED5_IO;
            break;
        case 6:
            num = LED6_IO;
            break;
        case 7:
            num = LED7_IO;
            break;

        default:
            num = 0;
    }

    // Print output if true and ON or if false and OFF
    if((state && num) || (!state && !num))
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const uint8_t*)"SELECTED");
}

void HTTPPrint_pot(HTTP_CONN_HANDLE connHandle)
{
    uint8_t AN0String[8];
    uint16_t ADval;
#if defined(__PIC32MZ__)
    ADval = 0;  // Todo: jw
#else
    ADval = (uint16_t)ADC1BUF0;
#endif
    //ADval *= (uint16_t)10;
    //ADval /= (uint16_t)102;
    uitoa(ADval, (uint8_t*)AN0String);

       TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), AN0String);
}

void HTTPPrint_lcdtext(HTTP_CONN_HANDLE connHandle)
{
// This function is no longer supported.
#if 0
    TCP_SOCKET sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    // If just starting, set callbackPos
    uint16_t len;
    uint32_t callbackPos;

    // Determine how many bytes we can write
    len = TCPIP_TCP_PutIsReady(sktHTTP);
    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);

    if(callbackPos == 0u)
        callbackPos = 32;

    // Write a byte at a time while we still can
    // It may take up to 12 bytes to write a character
    // (spaces and newlines are longer)
    while(len > 12u && callbackPos)
    {
        // After 16 bytes write a newline
        if(callbackPos == 16u)
            len -= TCPIP_TCP_ArrayPut(sktHTTP, (const uint8_t*)"<br />", 6);

        if(LCDText[32-callbackPos] == ' ' || LCDText[32-callbackPos] == '\0')
            len -= TCPIP_TCP_ArrayPut(sktHTTP, (const uint8_t*)"&nbsp;", 6);
        else
            len -= TCPIP_TCP_Put(sktHTTP, LCDText[32-callbackPos]);

        callbackPos--;
    }
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
#endif
}

void HTTPPrint_hellomsg(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr;
    TCP_SOCKET sktHTTP;

    ptr = TCPIP_HTTP_ArgGet(TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle), (const uint8_t*)"name");

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // We omit checking for space because this is the only data being written
    if(ptr != NULL)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"Hello, ");
        TCPIP_TCP_StringPut(sktHTTP, ptr);
    }

}

void HTTPPrint_cookiename(HTTP_CONN_HANDLE connHandle)
{
    const uint8_t *ptr;
    TCP_SOCKET sktHTTP;

    ptr = TCPIP_HTTP_ArgGet(TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle), (const uint8_t*)"name");

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(ptr)
        TCPIP_TCP_StringPut(sktHTTP, ptr);
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"not set");

}

void HTTPPrint_uploadedmd5(HTTP_CONN_HANDLE connHandle)
{
    uint8_t i;
    uint8_t* httpDataBuff;
    TCP_SOCKET sktHTTP;

    // Set a flag to indicate not finished
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 1);

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Make sure there's enough output space
    if(TCPIP_TCP_PutIsReady(sktHTTP) < 32u + 37u + 5u)
        return;

    // Check for flag set in HTTPPostMD5
#if defined(HTTP_APP_USE_MD5)
    if(TCPIP_HTTP_CurrentConnectionPostSmGet(connHandle) != SM_MD5_POST_COMPLETE)
#endif
    {// No file uploaded, so just return
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"<b>Upload a File</b>");
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0);
        return;
    }

    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"<b>Uploaded File's MD5 was:</b><br />");
    httpDataBuff = TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle);

    // Write a byte of the md5 sum at a time
    for(i = 0; i < 16u; i++)
    {
        TCPIP_TCP_Put(sktHTTP, btohexa_high(httpDataBuff[i]));
        TCPIP_TCP_Put(sktHTTP, btohexa_low(httpDataBuff[i]));
        if((i & 0x03) == 3u)
            TCPIP_TCP_Put(sktHTTP, ' ');
    }

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
}


void HTTPPrintIP(HTTP_CONN_HANDLE connHandle, IPV4_ADDR ip)
{
    uint8_t digits[4];
    uint8_t i;
    TCP_SOCKET sktHTTP;

    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    for(i = 0; i < 4u; i++)
    {
        if(i)
            TCPIP_TCP_Put(sktHTTP, '.');
        uitoa(ip.v[i], digits);
        TCPIP_TCP_StringPut(sktHTTP, digits);
    }
}

void HTTPPrint_config_hostname(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_StringPut(sktHTTP, (uint8_t*)TCPIP_STACK_NetBIOSName(TCPIP_TCP_SocketNetGet(sktHTTP)));
}

void HTTPPrint_config_dhcpchecked(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(TCPIP_DHCP_IsEnabled(TCPIP_TCP_SocketNetGet(sktHTTP)))
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"checked");
    }
}

void HTTPPrint_config_ip(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR ipAddress;    
    
    ipAddress.Val = TCPIP_STACK_NetAddress(netH);    
    HTTPPrintIP(connHandle, ipAddress);
}

void HTTPPrint_config_gw(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR gwAddress;    

    gwAddress.Val = TCPIP_STACK_NetAddressGateway(netH);    
    
    HTTPPrintIP(connHandle, gwAddress);
}

void HTTPPrint_config_subnet(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR ipMask;    

    ipMask.Val = TCPIP_STACK_NetMask(netH);    
    HTTPPrintIP(connHandle, ipMask);
}

void HTTPPrint_config_dns1(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR priDnsAddr;    

    priDnsAddr.Val = TCPIP_STACK_NetAddressDnsPrimary(netH);    

    HTTPPrintIP(connHandle, priDnsAddr);
}

void HTTPPrint_config_dns2(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_NET_HANDLE netH = TCPIP_TCP_SocketNetGet(sktHTTP);
    IPV4_ADDR secondDnsAddr;    

    secondDnsAddr.Val = TCPIP_STACK_NetAddressDnsSecond(netH);    

    HTTPPrintIP(connHandle, secondDnsAddr);
}

void HTTPPrint_config_mac(HTTP_CONN_HANDLE connHandle)
{
    uint8_t i;
    TCP_SOCKET sktHTTP;
    TCPIP_NET_HANDLE hNet; 
    const uint8_t* pMacAdd;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    if(TCPIP_TCP_PutIsReady(sktHTTP) < 18u)
    {//need 17 bytes to write a MAC
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
        return;
    }

    hNet = TCPIP_TCP_SocketNetGet(sktHTTP); 
    pMacAdd = TCPIP_STACK_NetAddressMac(hNet);
    // Write each byte
    for(i = 0; i < 6u; i++)
    {
        if(i)
            TCPIP_TCP_Put(sktHTTP, ':');
        TCPIP_TCP_Put(sktHTTP, btohexa_high(pMacAdd[i]));
        TCPIP_TCP_Put(sktHTTP, btohexa_low(pMacAdd[i]));
    }

    // Indicate that we're done
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x00);
    return;
}


// SNMP Read communities configuration page
void HTTPPrint_read_comm(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
    #if defined(TCPIP_STACK_USE_SNMP_SERVER)
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Ensure no one tries to read illegal memory addresses by specifying
    // illegal num values.
    if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
        return;

    // Send proper string
    TCPIP_TCP_StringPut(sktHTTP, ((SNMP_NET_CONFIG*)TCPIP_TCP_SocketNetGet(sktHTTP))->readCommunity[num]);
    #endif
}

// SNMP Write communities configuration page
void HTTPPrint_write_comm(HTTP_CONN_HANDLE connHandle, uint16_t num)
{
    #if defined(TCPIP_STACK_USE_SNMP_SERVER)
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // Ensure no one tries to read illegal memory addresses by specifying
    // illegal num values.
    if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
        return;

    // Send proper string
    TCPIP_TCP_StringPut(sktHTTP, ((SNMP_NET_CONFIG*)TCPIP_TCP_SocketNetGet(sktHTTP))->writeCommunity[num]);
    #endif
}


void HTTPPrint_reboot(HTTP_CONN_HANDLE connHandle)
{
    // This is not so much a print function, but causes the board to reboot
    // when the configuration is changed.  If called via an AJAX call, this
    // will gracefully reboot the system and bring it back online immediately
    SYS_Reboot();
}

void HTTPPrint_rebootaddr(HTTP_CONN_HANDLE connHandle)
{// This is the expected address of the board upon rebooting
    TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), TCPIP_HTTP_CurrentConnectionDataBufferGet(connHandle));
}

void HTTPPrint_ddns_user(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;

    if(DDNSClient.ROMPointers.Username || !DDNSClient.Username.szRAM)
        return;

    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);
    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Username.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

void HTTPPrint_ddns_pass(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;
    if(DDNSClient.ROMPointers.Password || !DDNSClient.Password.szRAM)
        return;

    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);

    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Password.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

void HTTPPrint_ddns_host(HTTP_CONN_HANDLE connHandle)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    uint32_t callbackPos;
    if(DDNSClient.ROMPointers.Host || !DDNSClient.Host.szRAM)
        return;
    callbackPos = TCPIP_HTTP_CurrentConnectionCallbackPosGet(connHandle);
    if(callbackPos == 0x00u)
        callbackPos = (uint32_t)DDNSClient.Host.szRAM;
    callbackPos = (uint32_t)TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (uint8_t*)callbackPos);
    if(*(uint8_t*)callbackPos == '\0')
        callbackPos = 0x00;
    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, callbackPos);
    #endif
}

extern const char * const ddnsServiceHosts[];
void HTTPPrint_ddns_service(HTTP_CONN_HANDLE connHandle, uint16_t i)
{
    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    if(!DDNSClient.ROMPointers.UpdateServer || !DDNSClient.UpdateServer.szROM)
        return;
    if((const char*)DDNSClient.UpdateServer.szROM == ddnsServiceHosts[i])
        TCPIP_TCP_StringPut(TCPIP_HTTP_CurrentConnectionSocketGet(connHandle), (const uint8_t*)"selected");
    #endif
}


void HTTPPrint_ddns_status(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    DDNS_STATUS s;
    s = TCPIP_DDNS_LastStatusGet();
    if(s == DDNS_STATUS_GOOD || s == DDNS_STATUS_UNCHANGED || s == DDNS_STATUS_NOCHG)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"ok");
    else if(s == DDNS_STATUS_UNKNOWN)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"unk");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"fail");
    #else
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"fail");
    #endif
}

void HTTPPrint_ddns_status_msg(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(TCPIP_TCP_PutIsReady(sktHTTP) < 75u)
    {
        TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0x01);
        return;
    }

    #if defined(TCPIP_STACK_USE_DYNAMICDNS_CLIENT)
    switch(TCPIP_DDNS_LastStatusGet())
    {
        case DDNS_STATUS_GOOD:
        case DDNS_STATUS_NOCHG:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The last update was successful.");
            break;
        case DDNS_STATUS_UNCHANGED:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The IP has not changed since the last update.");
            break;
        case DDNS_STATUS_UPDATE_ERROR:
        case DDNS_STATUS_CHECKIP_ERROR:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"Could not communicate with DDNS server.");
            break;
        case DDNS_STATUS_INVALID:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The current configuration is not valid.");
            break;
        case DDNS_STATUS_UNKNOWN:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The Dynamic DNS client is pending an update.");
            break;
        default:
            TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"An error occurred during the update.<br />The DDNS Client is suspended.");
            break;
    }
    #else
    TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"The Dynamic DNS Client is not enabled.");
    #endif

    TCPIP_HTTP_CurrentConnectionCallbackPosSet(connHandle, 0);
}

void HTTPPrint_smtps_en(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    #if defined(TCPIP_STACK_USE_SSL_CLIENT)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"inline");
    #else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    #endif
}

void HTTPPrint_snmp_en(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    #if defined(TCPIP_STACK_USE_SNMP_SERVER)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    #else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    #endif
}

void HTTPPrint_status_ok(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(lastSuccess)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    lastSuccess = false;
}

void HTTPPrint_status_fail(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if(lastFailure)
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"block");
    else
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"none");
    lastFailure = false;
}
void HTTPPrint_scan(HTTP_CONN_HANDLE connHandle)
{
    uint8_t scanInProgressString[4];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    uitoa(IS_SCAN_IN_PROGRESS(g_ScanCtx.scanState), scanInProgressString);
    TCPIP_TCP_StringPut(sktHTTP, scanInProgressString);
}

void HTTPPrint_fwver(HTTP_CONN_HANDLE connHandle)
{
    static bool firstTime = true;
    static DRV_WIFI_DEVICE_INFO deviceInfo;
    uint8_t fwVerString[8];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if (firstTime)
    {
        firstTime = false;
        DRV_WIFI_DeviceInfoGet(&deviceInfo);  // only call this once, not continually
    }    
    
    uitoa((deviceInfo.romVersion << 8) | deviceInfo.patchVersion, fwVerString);
    TCPIP_TCP_StringPut(sktHTTP, fwVerString);
}

void HTTPPrint_ssid(HTTP_CONN_HANDLE connHandle)
{
    static bool firstTime = true;
    static uint8_t ssidString[33];
    static uint8_t ssidLength;
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    // we don't need to check the connection state as the only way this function
    // is called is from the webserver.  if the webserver is requesting this,
    // then you can infer that we should be connected to the network
    if (firstTime)
    {
        firstTime = false;
        DRV_WIFI_SsidGet(ssidString, &ssidLength);
    }
    TCPIP_TCP_ArrayPut(sktHTTP, ssidString, ssidLength);
}    

void HTTPPrint_bssCount(HTTP_CONN_HANDLE connHandle)
{
    uint8_t bssCountString[4];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    uitoa(SCANCXT.numScanResults, bssCountString);
    TCPIP_TCP_StringPut(sktHTTP, bssCountString);
}

void HTTPPrint_valid(HTTP_CONN_HANDLE connHandle)
{
    uint8_t bssDescIsValidString[4];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    uitoa((uint8_t)bssDescIsValid, bssDescIsValidString);
    TCPIP_TCP_StringPut(sktHTTP, bssDescIsValidString);
}    

void HTTPPrint_name(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    if (bssDescIsValid)
    {
        if(strlen((const char*)bssDesc.ssid)<32)
            TCPIP_TCP_StringPut(sktHTTP, bssDesc.ssid);
		else
		{
            uint8_t buf_tmp[33];
            int i;
            for(i=0;i<32;i++) buf_tmp[i] = bssDesc.ssid[i];
            buf_tmp[32] = 0;
            TCPIP_TCP_StringPut(sktHTTP, buf_tmp);
		}
    }
    else
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t *)"0");
    }        

}    

void HTTPPrint_privacy(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    uint8_t security = (bssDesc.apConfig & 0xd0) >> 4;
    uint8_t secString[4];
    
    if (bssDescIsValid)
    {
        uitoa(security, secString);
        TCPIP_TCP_StringPut(sktHTTP, secString);
    }
    else
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"0");
    }    
}    

void HTTPPrint_wlan(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    uint8_t bssTypeString[4];
    if (bssDescIsValid)
    {
        uitoa(bssDesc.bssType, bssTypeString);
        TCPIP_TCP_StringPut(sktHTTP, bssTypeString);
    }
    else
    {    
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"0");
    }    
}    

void HTTPPrint_strength(HTTP_CONN_HANDLE connHandle)
{
    uint8_t strVal;
    uint8_t strString[4];
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    if (bssDescIsValid)
    {
        if (bssDesc.rssi < 121)
        {
            strVal = 1;
        }
        else if (bssDesc.rssi < 141)
        {
            strVal = 2;
        }
        else if (bssDesc.rssi < 161)
        {
            strVal = 3;
        }
        else
        {
            strVal = 4;
        }
        
        uitoa(strVal, strString);
        TCPIP_TCP_StringPut(sktHTTP, strString);
    }
    else
    {                
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"0");
    }
}

void HTTPPrint_nextSSID(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_StringPut(sktHTTP, (uint8_t*)CFGCXT.ssid); //nextSSID
}
void HTTPPrint_prevSSID(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
    TCPIP_TCP_StringPut(sktHTTP, (uint8_t*)CFGCXT.prevSSID);//prevSSID
}
void HTTPPrint_prevWLAN(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    if (CFGCXT.prevWLAN == DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"infrastructure (BSS)");
    }

    else if (CFGCXT.prevWLAN == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"softAP (BSS)");
    }
    else
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"adhoc (IBSS)");
    }
}
void HTTPPrint_nextWLAN(HTTP_CONN_HANDLE connHandle)
{
    TCP_SOCKET sktHTTP;
    sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);

    if (CFGCXT.type == DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"infrastructure (BSS)");
    }
        
    else if (CFGCXT.type == DRV_WIFI_NETWORK_TYPE_ADHOC)
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"adhoc (IBSS)");
    }
    else if (CFGCXT.type == DRV_WIFI_NETWORK_TYPE_SOFT_AP)
    {     
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"softAP (BSS)");
    }
    else
    {
        TCPIP_TCP_StringPut(sktHTTP, (const uint8_t*)"unknown");
    }
}

//==============================================================================
//                      Local Function Prototypes for iwpriv
//==============================================================================

/*****************************************************************************
 * FUNCTION: HexToBin
 *
 * RETURNS: binary value associated with ASCII hex input value
 *
 * PARAMS:  hexChar -- ASCII hex character
 *
 * NOTES:   Converts an input ascii hex character to its binary value.  Function
 *          does not error check; it assumes only hex characters are passed in.
 *****************************************************************************/
#if 0
uint8_t HexToBin(uint8_t hexChar)
{
    if ((hexChar >= 'a') && (hexChar <= 'f'))
    {
        return (0x0a + (hexChar - 'a'));
    }
    else if ((hexChar >= 'A') && (hexChar <= 'F'))
    {
        return (0x0a + (hexChar - 'A'));
    }
    else //  ((hexChar >= '0') && (hexChar <= '9'))
    {
        return (0x00 + (hexChar - '0'));
    }

}
#endif

#if 0
/*****************************************************************************
 * FUNCTION: ConvertASCIIHexToBinary
 *
 * RETURNS: true if conversion successful, else false
 *
 * PARAMS:  p_ascii   -- ascii string to be converted
 *          p_binary  -- binary value if conversion successful
 *
 * NOTES:   Converts an input ascii hex string to binary value (up to 32-bit value)
 *****************************************************************************/
static bool ConvertASCIIHexToBinary(char *p_ascii, uint16_t *p_binary)
{
    int8_t  i;
    uint32_t multiplier = 1;

    *p_binary = 0;

    // not allowed to have a string of more than 4 nibbles
    if (strlen((char*)p_ascii) > 8u)
    {
        return false;
    }

    // first, ensure all characters are a hex digit
    for (i = (uint8_t)strlen((char *)p_ascii) - 1; i >= 0 ; --i)
    {
        if (!isxdigit(p_ascii[i]))
        {
            return false;
        }
        *p_binary += multiplier * HexToBin(p_ascii[i]);
        multiplier *= 16;
    }

    return true;
}
#endif


#if 0  //This API has been defined in wf_commands.c
bool convertAsciiToHexInPlace(char *p_string, uint8_t expectedHexBinSize )
{

    char  ascii_buffer[3];
    uint8_t  hex_binary_index = 0;
    char  *hex_string_start = p_string;
    uint16_t hex_buffer = 0;

    /* gobble up any hex prefix */
    if ( memcmp(hex_string_start, (const char*) "0x", 2) == 0 )
         hex_string_start+=2;

   if ( strlen( (char *) hex_string_start) != (expectedHexBinSize*2) )
      return false;

    while ( hex_binary_index < expectedHexBinSize )
    {

      memcpy ( ascii_buffer, (const char*) hex_string_start, 2 );
      ascii_buffer[2] = '\0';

      /* convert the hex string to a machine hex value */
      if ( !ConvertASCIIHexToBinary( ascii_buffer,&hex_buffer) )
        return false;

      p_string[hex_binary_index++] = (uint8_t) hex_buffer;

      hex_string_start +=2;

    }

    return true;
}
#endif
#endif
