/*******************************************************************************
  MRF24W multicast filter testing

  File Name: 
    drv_wifi_test_multicast.c  
  
  Summary:
    Module for Microchip TCP/IP Stack

  Description:
    -testing tool to verify multi cast filter
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard
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
//DOM-IGNORE-END

/*
*********************************************************************************************************
*                                           INCLUDES
*********************************************************************************************************
*/
#include "tcpip/src/tcpip_private.h"


#if 1 //defined(TCPIP_STACK_USE_WF_MCAST_TEST) 

enum mCast_SM_t{
    MDNS_RESPONDER_INIT = 0,
    MDNS_RESPONDER_LISTEN,        
}; 

struct mCast_testing_context_t
{
    enum mCast_SM_t StateMachine;
    UDP_SOCKET      socket;
};
#define WF_MULTICAST_FILTER_1 1
struct mCast_testing_context_t  mCast_testing_context_1 = {
    MDNS_RESPONDER_INIT,
};

static UDP_SOCKET      socket_1 = INVALID_UDP_SOCKET;
static UDP_SOCKET      socket_2 = INVALID_UDP_SOCKET;
static UDP_PORT        port_1 = 5353;
static UDP_PORT        port_2 = 5354;

/////////////////////////////////////////
 void WFTestUdpServer_Process(void)
{
    unsigned char pcString[30];
    int rc;
    WORD i,count;
	struct mCast_testing_context_t *mCast_Context = &mCast_testing_context_1;
    if(socket_1 == INVALID_UDP_SOCKET)
    {
        mCast_Context->StateMachine = MDNS_RESPONDER_INIT;        
    }
    switch(mCast_Context->StateMachine) 
    {
        case MDNS_RESPONDER_INIT:
            printf("Opening mCast socket_1 \r\n");
            socket_1 = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, port_1, 0);
			socket_2 = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, port_2, 0);
            if(socket_1 == INVALID_UDP_SOCKET)
            {
                printf("Can't open mCast UDP-Socket \r\n");
                return;
            }
            else
                mCast_Context->StateMachine = MDNS_RESPONDER_LISTEN ;
            /* Called from TCPIP_MDNS_Initialize. So return immediately */
            break;

        case MDNS_RESPONDER_LISTEN:
        {
            char buf_t[10];
            count = TCPIP_UDP_GetIsReady(socket_1);
            if(count == 0)return;
            
            printf("[Get MCAST package at <");

            while(count > 0)
            {
                int num = count > 30? 30:count;
                count -= num;
                rc = TCPIP_UDP_ArrayGet(socket_1, pcString, num);
                for(i=0;i<rc;i++)
                {
                    sprintf(buf_t,"%02x ",pcString[i]);
                    printf(buf_t);
                }
            }
            printf(" ]\r\n\r\n");
            break;
        }
            

        default:
            break;
    }

    return;
}







#endif 





