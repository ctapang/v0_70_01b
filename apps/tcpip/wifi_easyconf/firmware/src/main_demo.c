/*******************************************************************************
  Main Application Entry Point and TCP/IP Stack Demo

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Demonstrates how to call and use the Microchip TCP/IP stack
    -Reference: Microchip TCP/IP Stack Help (tcpip Help.chm)
 *******************************************************************************/

/*******************************************************************************
File Name: MainDemo.c 
Copyright © 2012 released Microchip Technology Inc.  All rights
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

// Include all headers for any enabled tcpip functions
#include "tcpip/tcpip.h"

#include "tcpip_modules_config.h"

// Include functions specific to this stack application
#include "main_demo.h"
#include <tcpip/src/system/system_userio.h>
#include "driver/wifi/mrf24w/src/drv_wifi_easy_config.h"
#if defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)

int stackNotifyCnt = 0;
const void* stackNotifyHandle;
TCPIP_EVENT stackTotEvents = 0;


#if defined(TCPIP_IF_MRF24W)
uint16_t mrf_txEvents = 0, mrf_txEventInfo = 0;
uint16_t mrf_mgmtEvents = 0, mrf_mgmtEventInfo = 0;
int mrf_EventCnt = 0;
#endif
#endif  // defined(TCPIP_STACK_USE_EVENT_NOTIFICATION)


#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP) || (DRV_WIFI_DEFAULT_ADHOC_PRESCAN == DRV_WIFI_ENABLED)
uint8_t g_scan_done = 0;        // WF_PRESCAN   This will be set wheneven event scan results are ready.
uint8_t g_prescan_waiting = 1;  // WF_PRESCAN   This is used only to allow POR prescan once.
extern void WFDisplayScanMgr(void);
#endif            


#if defined(WF_UPDATE_FIRMWARE_UART_24G)|| defined(WF_UPDATE_FIRMWARE_TCPCLIENT_24G)
bool	WF_FirmwareUpdate_Uart_24G(void);
void    WF_FirmwareUpdate_TcpClient_24G(void);
#endif


//
// Main application entry point.
//

int main(void)
{
    static SYS_TICK startTick = 0;
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };

    SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;
    IPV4_ADDR           ipAddr;
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    const char          *netName, *netBiosName;

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)

    // perform system initialization
    SYS_Initialize(0);

    SYS_CONSOLE_MESSAGE("\r\n\n\n --- WiFi Demo Starts! --- \r\n");

    // Display the names associated with each interface
    nNets = TCPIP_STACK_NumberOfNetworksGet();
    for(i = 0; i < nNets; i++)
    {

        netH = TCPIP_STACK_IndexToNet(i);
        netName = TCPIP_STACK_NetNameGet(netH);
        netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif  // defined(TCPIP_STACK_USE_NBNS)

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
        mDNSServiceName[sizeof(mDNSServiceName) - 2] = '1' + i;
        TCPIP_MDNS_ServiceRegister( netH
                , mDNSServiceName                   // name of the service
                ,"_http._tcp.local"                 // type of the service
                ,80                                 // TCP or UDP port, at which this service is available
                ,((const uint8_t *)"path=/index.htm")  // TXT info
                ,1                                  // auto rename the service when if needed
                ,NULL                               // no callback function
                ,NULL);                             // no application context
#endif //TCPIP_STACK_USE_ZEROCONF_MDNS_SD
    }
    while (1)
    {
#if (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP) || (DRV_WIFI_DEFAULT_ADHOC_PRESCAN == DRV_WIFI_ENABLED)
        if (g_scan_done)
        {
            if (g_prescan_waiting)
            {
                if(IS_SCAN_STATE_DISPLAY(SCANCXT.scanState) && SCANCXT.numScanResults > 0)
                {
                    SYS_CONSOLE_MESSAGE((const char*)"\n SoftAP prescan results ........ \r\n\n");
                    SCANCXT.displayIdx = 0;
                    while (IS_SCAN_STATE_DISPLAY(SCANCXT.scanState))
                    {
                        WFDisplayScanMgr();
                    }
                    SYS_CONSOLE_MESSAGE((const char*)"\r\n ");
                }
                else
                {
                    SYS_CONSOLE_MESSAGE((const char*)"No AP found.\r\n ");
                }
                g_prescan_waiting = 0;
            }
            if (TCPIP_MAC_RES_OK == Demo_Wifi_Connect())
            {
                g_scan_done = 0;
            }
        }
#endif // (WF_DEFAULT_NETWORK_TYPE == DRV_WIFI_NETWORK_TYPE_SOFT_AP)

       SYS_Tasks();

        // Blink LED0 every second.
        if (SYS_TICK_Get() - startTick >= SYS_TICK_TicksPerSecondGet() / 2ul)
        {
            startTick = SYS_TICK_Get();
            LEDstate ^= SYS_USERIO_LED_ASSERTED;
                  
            SYS_USERIO_SetLED(SYS_USERIO_LED_0, LEDstate);
        }
        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        TCPIP_STACK_Task();

        // if the IP address of an interface has changed
        // display the new value on the system console
        nNets = TCPIP_STACK_NumberOfNetworksGet();
        for (i = 0; i < nNets; i++)
        {
            netH = TCPIP_STACK_IndexToNet(i);
            ipAddr.Val = TCPIP_STACK_NetAddress(netH);
            if(dwLastIP[i].Val != ipAddr.Val)
            {
                dwLastIP[i].Val = ipAddr.Val;

                SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                SYS_CONSOLE_MESSAGE(" IP Address: ");
                SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
            }
        }

#if defined(WF_UPDATE_FIRMWARE_UART_24G)
    WF_FirmwareUpdate_Uart_24G();
#endif

#if defined(WF_UPDATE_FIRMWARE_TCPCLIENT_24G)
    WF_FirmwareUpdate_TcpClient_24G();
#endif
    
#if defined(WF_ERASE_CONFIGDATA_BY_BUTTON)
    if( BUTTON2_IO == 0u)
    {
        SYS_CONSOLE_MESSAGE("erase EEPROM configure\r\n");
        DRV_WIFI_ConfigDataErase();
        SYS_CONSOLE_MESSAGE("now reset system...\r\n");
        SYS_Reboot();
    }
#endif
    }
}

// Writes an IP address to the LCD display and the UART as available

void DisplayIPValue(IPV4_ADDR IPVal)
{
    char message[16 + 1];

    //    printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
#if defined (__dsPIC33E__) || defined (__PIC24E__)
    static uint8_t IPDigit[4]; /* Needs to be declared as static to avoid the array getting optimized by C30 v3.30 compiler for dsPIC33E/PIC24E.
                  Otherwise the LCD displays corrupted IP address on Explorer 16. To be fixed in the future compiler release*/
#else
    uint8_t IPDigit[4];
#endif
    int i;

    strcpy(message, "");
    for (i = 0; i < sizeof (IPV4_ADDR); i++)
    {
        uitoa((uint16_t) IPVal.v[i], IPDigit);
        strcat(message, (char *) IPDigit);
        if (i < sizeof (IPV4_ADDR) - 1)
        {
            strcat(message, ".");
        }
    }
    SYS_OUT_MESSAGE_LINE(message, 1);
    SYS_CONSOLE_MESSAGE((char *) message);
}





