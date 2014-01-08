/*******************************************************************************
  Sample Application

  File Name:
    app.c

  Summary:
    Sample "hello world" application

  Description:
    This file contains the sample "hello world" application's implementation.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

//#include "system_config.h"
#include "app.h"
#include "system_config.h"

// Include all headers for any enabled tcpip functions
#include "tcpip/src/tcpip_private.h"
#include "tcpip/tcpip.h"

// Include functions specific to this stack application
#include "tcpip/src/system/system_userio.h"

#define SERVER_PORT 9760

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appData;

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObjects;

int nNets;
TCPIP_NET_HANDLE    netH;
SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize( void )
{
    int i;
    const char          *netName, *netBiosName;


#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)

    appData.state = APP_TCPIP_WAIT_FOR_IP;

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

    /* Intialize the app state to wait for
     * media attach. */

}


/*******************************************************************************
  Function:
    void APP_Tasks( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks( void )
{
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int i;

    switch(appData.state)
    {

        case APP_TCPIP_WAIT_FOR_IP:

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
                    if (ipAddr.v[0] != 0 && ipAddr.v[0] != 169) // Wait for a Valid IP
                    {
                        appData.state = APP_TCPIP_OPENING_SERVER;
                    }
                }
            }
            break;
        case APP_TCPIP_OPENING_SERVER:
        {
            SYS_CONSOLE_PRINT("Waiting for Client Connection on port: %d\r\n", SERVER_PORT);
            appData.socket = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, SERVER_PORT, 0);
            if (appData.socket == INVALID_SOCKET)
            {
                SYS_CONSOLE_MESSAGE("Couldn't open server socket\r\n");
                break;
            }
            appData.state = APP_TCPIP_WAIT_FOR_CONNECTION;
        }
        break;

        case APP_TCPIP_WAIT_FOR_CONNECTION:
        {
            if (!TCPIP_UDP_IsConnected(appData.socket))
            {
                return;
            }
            else
            {
                // We got a connection
                appData.state = APP_TCPIP_SERVING_CONNECTION;
                SYS_CONSOLE_MESSAGE("Received a connection\r\n");
            }
        }
        break;

        case APP_TCPIP_SERVING_CONNECTION:
        {
            if (!TCPIP_UDP_IsConnected(appData.socket))
            {
                appData.state = APP_TCPIP_CLOSING_CONNECTION;
                SYS_CONSOLE_MESSAGE("Connection was closed\r\n");
                break;
            }
            int16_t wMaxGet, wMaxPut, wCurrentChunk;
            uint16_t w, w2;
            uint8_t AppBuffer[32];
            // Figure out how many bytes have been received and how many we can transmit.
            wMaxGet = TCPIP_UDP_GetIsReady(appData.socket);	// Get UDP RX FIFO byte count
            wMaxPut = UDPIsPutReady(appData.socket);

            //SYS_CONSOLE_PRINT("\t%d bytes are available.\r\n", wMaxGet);
            if (wMaxGet == 0)
            {
                break;
            }

            if (wMaxPut < wMaxGet)
            {
                wMaxGet = wMaxPut;
            }

            // Process all bytes that we can
            // This is implemented as a loop, processing up to sizeof(AppBuffer) bytes at a time.
            // This limits memory usage while maximizing performance.  Single byte Gets and Puts are a lot slower than multibyte GetArrays and PutArrays.
            wCurrentChunk = sizeof(AppBuffer);
            for(w = 0; w < wMaxGet; w += sizeof(AppBuffer))
            {
                // Make sure the last chunk, which will likely be smaller than sizeof(AppBuffer), is treated correctly.
                if(w + sizeof(AppBuffer) > wMaxGet)
                    wCurrentChunk = wMaxGet - w;

                // Transfer the data out of the TCP RX FIFO and into our local processing buffer.
                TCPIP_UDP_ArrayGet(appData.socket, AppBuffer, wCurrentChunk);

                SYS_CONSOLE_PRINT("\tReceived a message of '%s'\r\n", AppBuffer);

                // Perform the "ToUpper" operation on each data byte
                for(w2 = 0; w2 < wCurrentChunk; w2++)
                {
                    i = AppBuffer[w2];
                    if(i >= 'a' && i <= 'z')
                    {
                            i -= ('a' - 'A');
                            AppBuffer[w2] = i;
                    }
                    else if(i == '\e')   //escape
                    {
                        SYS_CONSOLE_MESSAGE("Connection was closed\r\n");
                    }
                }

                SYS_CONSOLE_PRINT("\tSending a messages '%s'\r\n", AppBuffer);

                // Transfer the data out of our local processing buffer and into the TCP TX FIFO.
                TCPIP_UDP_ArrayPut(appData.socket, AppBuffer, wCurrentChunk);

                TCPIP_UDP_Flush(appData.socket);

                appData.state = APP_TCPIP_CLOSING_CONNECTION;
            }
        }
        break;
        case APP_TCPIP_CLOSING_CONNECTION:
        {
            			// Close the socket connection.
            TCPIP_UDP_Close(appData.socket);

            appData.state = APP_TCPIP_OPENING_SERVER;

        }
        break;
        default:
            break;
    }
}

/*******************************************************************************
 End of File
*/

