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

int nNets;
TCPIP_NET_HANDLE    netH;

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
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    const char          *netName, *netBiosName;

    SYS_CONSOLE_MESSAGE("\r\n\n\n --- ISP TCPIP Demo Starts! --- \r\n");

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

    }

    /* Intialize the app state to wait for
     * media attach. */
    appData.state = APP_GETTING_IP;
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
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    // if the IP address of an interface has changed
    // display the new value on the system console
     nNets = TCPIP_STACK_NumberOfNetworksGet();
    for (i = 0; i < nNets; i++)
    {
        switch (appData.state)
        {
            case APP_GETTING_IP:
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                    if (ipAddr.v[0] != 0 && ipAddr.v[0] != 169) // 0.0.0.0 is the boot up address
                                                                // 169.254.1.2 is the auto-config address
                    {
                        SYS_CONSOLE_MESSAGE("Firing up CyaSSL\r\n");
                        appData.state = APP_OPENING_SSL_CONNECTION;
                        CyaSSL_SetLoggingCb(&TCPIP_WSSL_Logging_cb);
                        #if defined(DEBUG_CYASSL)
                        CyaSSL_Debugging_ON();
                        #endif
                        CyaSSL_Init();
                        TCPIP_WSSL_CreateConnection(&appData.sslInfo, "www.google.com", 443);
                    }
                }
            }
            break;
            case APP_OPENING_SSL_CONNECTION:
            {
                TCPIP_WSSL_PumpConnection(&appData.sslInfo);
                if (appData.sslInfo.state == WOLF_SSL_CS_SSL_CONNECTED)
                {
                    // Lets send something!
                    char getStr[] = "GET https://www.google.com/ HTTP/1.1\r\n"
                                    "User-Agent: Fiddler\r\n"
                                    "Host: www.google.com\r\n"
                                    "Connection: close\r\n\r\n";
                    int ret;
                    appData.state = 1;

                    SYS_CONSOLE_MESSAGE("Sending the message to google.\r\n");

                    if ((ret = CyaSSL_write(appData.sslInfo.ssl, getStr, strlen(getStr))) != strlen(getStr))
                    {
                        SYS_CONSOLE_PRINT("Could not send to google, got a return %d\n", ret);
                    }
                    appData.state = APP_WAITING_RESPONSE;
                }
            }
            break;
            case APP_WAITING_RESPONSE:
            {
                int ret = CyaSSL_read(appData.sslInfo.ssl, appData.receiveBuffer, sizeof(appData.receiveBuffer));
                if (ret < 0)
                {
                    int error = CyaSSL_get_error(appData.sslInfo.ssl, ret);
                    if ((error == SSL_ERROR_WANT_READ) ||
                        (error == SSL_ERROR_WANT_WRITE))
                    {
                        //This is fine go along
                    }
                    else
                    {
                        appData.state = APP_CLOSING_CONNECTION;
                        TCPIP_WSSL_CloseConnection(&appData.sslInfo);
                    }
                }
                else
                {
                    // we got something
                    SYS_CONSOLE_PRINT("%s", appData.receiveBuffer);
                    appData.state = APP_CLOSING_CONNECTION;
                }

            }
            break;
            case APP_CLOSING_CONNECTION:
            {
                TCPIP_WSSL_CloseConnection(&appData.sslInfo);
                appData.state = APP_DONE;
            }
            break;
            case APP_DONE:
            default:
                break;
        }
    }
}

/*******************************************************************************
 End of File
*/

