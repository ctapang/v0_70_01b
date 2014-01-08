/*******************************************************************************
  Main Application Entry Point and TCP/IP Stack Demo

  Summary:
    Module for Microchip TCP/IP Stack

  Description:
    -Demonstrates how to call and use the Microchip TCP/IP stack
    -Reference: Microchip TCP/IP Stack Help (tcpip Help.chm)
 *******************************************************************************/

/*******************************************************************************
File Name: main_demo.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
//#define TCPIP_STACK_MODULE_CONFIGURATION
// Include all headers for any enabled tcpip functions
#include "tcpip/tcpip.h"

#include "tcpip_modules_config.h"

// Include functions specific to this stack application
#include "main_demo.h"
#include "tcpip/src/system/system_userio.h"

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


// Local functions prototypes

void ICMPv6Callback(TCPIP_NET_HANDLE hNetIf, uint8_t type, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, void * header);

void test_ADC(void);
#if defined(WF_UPDATE_FIRMWARE_UART_24G)|| defined(WF_UPDATE_FIRMWARE_TCPCLIENT_24G)
bool	WF_FirmwareUpdate_Uart_24G(void);
void WF_FirmwareUpdate_TcpClient_24G(void);
#endif
//
// Main application entry point.
//
int main(void)
{
    static SYS_TICK startTick = 0;
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;

    SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    const char          *netName, *netBiosName;

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)


    // perform system initialization
    SYS_Initialize(0);

    SYS_CONSOLE_MESSAGE("\r\n\n\n ---  TCPIP Demo Starts!  --- \r\n");
    SYS_OUT_MESSAGE("TCPIPStack " TCPIP_STACK_VERSION "  ""                ");

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

#if defined(WF_UPDATE_FIRMWARE_UART_24G)
    extern bool    WF_FirmwareUpdate_Uart_24G(void);
    WF_FirmwareUpdate_Uart_24G();
#endif

    // Now that all items are initialized, begin the co-operative
    // multitasking loop.  This infinite loop will continuously
    // execute all stack-related tasks, as well as your own
    // application's functions.  Custom functions should be added
    // at the end of this loop.
    // Note that this is a "co-operative mult-tasking" mechanism
    // where every task performs its tasks (whether all in one shot
    // or part of it) and returns so that other tasks can do their
    // job.
    // If a task needs very long time to do its job, it must be broken
    // down into smaller pieces so that other tasks can have CPU time.
    while (1)
    {
        SYS_Tasks();

        // Blink LED0 every second.
        if (SYS_TICK_Get() - startTick >= SYS_TICK_TicksPerSecondGet() / 2ul)
        {
            startTick = SYS_TICK_Get();
            LEDstate ^= SYS_USERIO_LED_ASSERTED;
            SYS_USERIO_SetLED(SYS_USERIO_LED_0, LEDstate);
        }

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

#if (WF_DEFAULT_NETWORK_TYPE == WF_NETWORK_TYPE_SOFT_AP)

        if (g_scan_done) {
           if (g_prescan_waiting) {
               SYS_CONSOLE_MESSAGE((const char*)"\n SoftAP prescan results ........ \r\n\n");
               SCANCXT.displayIdx = 0;
               extern void WFDisplayScanMgr(void);
               while (IS_SCAN_STATE_DISPLAY(SCANCXT.scanState)) {
                   WFDisplayScanMgr();
               }
               SYS_CONSOLE_MESSAGE((const char*)"\r\n ");

       #if defined(WF_CS_TRIS)
                Demo_Wifi_Connect();
       #endif
               g_scan_done = 0;
               g_prescan_waiting = 0;
           }
        }
#endif // (WF_DEFAULT_NETWORK_TYPE == WF_NETWORK_TYPE_SOFT_AP)

#if defined(WF_UPDATE_FIRMWARE_UART_24G)
    WF_FirmwareUpdate_Uart_24G();
#endif

#if defined(WF_UPDATE_FIRMWARE_TCPCLIENT_24G)
    WF_FirmwareUpdate_TcpClient_24G();
#endif

    }
}
