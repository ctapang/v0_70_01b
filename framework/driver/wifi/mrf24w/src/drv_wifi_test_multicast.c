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


#if defined(TCPIP_STACK_USE_WF_MCAST_TEST) 

enum mCast_SM_t{
    MDNS_RESPONDER_INIT = 0,
    MDNS_RESPONDER_LISTEN,        
}; 

struct mCast_testing_context_t
{
    UINT8 test_ID;
    UINT8 filter_Id;
    enum mCast_SM_t StateMachine;
    UDP_SOCKET      socket;
    UINT8 mCast_MacAddr[6];
    UINT8 mCast_IPAddr[4];
    UDP_PORT        port;
    NODE_INFO Remote;
    
};

struct mCast_testing_context_t  mCast_testing_context_1 = {
    1,
    WF_MULTICAST_FILTER_1,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFB},
    {224,0,0,251},
    5353,
    {     //static NODE_INFO Remote
        {},//  IPAddr
        {},//  MACAddr
    }
};
struct mCast_testing_context_t  mCast_testing_context_2 = {
    2,
    WF_MULTICAST_FILTER_2,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFC},
    {224,0,0,252},
    5354,
};

struct mCast_testing_context_t  mCast_testing_context_3 = {
    3,
    WF_MULTICAST_FILTER_7,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFD},
    {224,0,0,253},
    5355,
};
struct mCast_testing_context_t  mCast_testing_context_4 = {
    4,
    WF_MULTICAST_FILTER_15,
    MDNS_RESPONDER_INIT,
    INVALID_UDP_SOCKET,
    {0x01, 0x00, 0x5E, 0x00, 0x00, 0xFE},
    {224,0,0,254},
    5356,
};



/////////////////////////////////////////
static void WFTestMCast_Process_Sub(struct mCast_testing_context_t *mCast_Context)
{
    unsigned char pcString[30];
    int rc;
    WORD i,count;

    if(mCast_Context->socket == INVALID_UDP_SOCKET)
    {
        mCast_Context->StateMachine = MDNS_RESPONDER_INIT;        
    }
    switch(mCast_Context->StateMachine) 
    {
        case MDNS_RESPONDER_INIT:
            printf("Opening mCast socket \r\n");
            //mCast_Context->socket = UDPOpenEx((DWORD)(PTR_BASE)&(mCast_Context->Remote),UDP_OPEN_NODE_INFO,mCast_Context->port,mCast_Context->port);
            mCast_Context->socket = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, mCast_Context->port, 0);
            if(mCast_Context->socket == INVALID_UDP_SOCKET)
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
            count = TCPIP_UDP_GetIsReady(mCast_Context->socket);
            if(count == 0)return;
            
            printf("[Get MCAST package at <");
            sprintf(buf_t,"%d>:  ",mCast_Context->test_ID);
            printf(buf_t);
            while(count > 0)
            {
                int num = count > 30? 30:count;
                count -= num;
                rc = TCPIP_UDP_ArrayGet(mCast_Context->socket, pcString, num);
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


void WFTestMCast_Process()  
{
 //   if(!MACIsLinked())return;
    
    WFTestMCast_Process_Sub(&mCast_testing_context_1);
    WFTestMCast_Process_Sub(&mCast_testing_context_2);
    WFTestMCast_Process_Sub(&mCast_testing_context_3);
    WFTestMCast_Process_Sub(&mCast_testing_context_4);
    return;
}

static void WFTestMCast_SetFilter_sub(struct mCast_testing_context_t *mCast_Context)
{

    UINT8 *mcast_addr = mCast_Context->mCast_MacAddr;
   
#ifdef ENABLE_SOFTWARE_MULTICAST_FILTER
        DRV_WIFI_SWMultiCastFilterEnable();
        do {
            t_wfMultiCastConfig p_config;

            p_config.filterId = mCast_Context->filter_Id;
            p_config.action = WF_MULTICAST_USE_FILTERS;
            memcpy((void *)p_config.macBytes, (void *)mcast_addr, WF_MAC_ADDRESS_LENGTH);
            p_config.macBitMask = 0x3F; /* each bit corresponds to 6 mac address bytes. 
                                            * 1 means to force to compare the byte.
                                            * Conversely 0 means not to compare the byte, and
                                            * accept the byte unconditionally.
                                            */
            DRV_WIFI_SWMulticastFilterSet(&p_config);
        } while (0);
#else    /* !ENABLE_SOFTWARE_MULTICAST_FILTER */
        DRV_WIFI_HWMulticastFilterSet(mCast_Context->filter_Id, mcast_addr);
#endif    /* ENABLE_SOFTWARE_MULTICAST_FILTER */

    
    return ;
}

void  WFTestMCast_SetFilter(void)
{
   WFTestMCast_SetFilter_sub(&mCast_testing_context_1);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_2);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_3);
   WFTestMCast_SetFilter_sub(&mCast_testing_context_4);
}

#endif 





