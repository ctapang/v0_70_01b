/*******************************************************************************
  TCP/IP notifications implementation file

  Company:
    Microchip Technology Inc.

  File Name:
   tcpip_notify.c

  Summary:
   TCPIP notifications mechanism header file

  Description:
    This source file contains the internal notifications API
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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


#include "tcpip/src/tcpip_private.h"
#include "tcpip/src/tcpip_notify.h"

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_TCPIP_MANAGER

SGL_LIST_NODE* TCPIP_Notification_Add(SINGLE_LIST* notifyList, TCPIP_HEAP_HANDLE heapH, size_t nBytes)
{
    SGL_LIST_NODE* newNode = TCPIP_HEAP_Malloc(heapH, nBytes);

    if(newNode)
    {
        TCPIP_Helper_SingleListTailAdd(notifyList, newNode);
    }
    return newNode;

}



bool TCPIP_Notification_Remove(SGL_LIST_NODE* node, SINGLE_LIST* notifyList, TCPIP_HEAP_HANDLE heapH)
{
    if(TCPIP_Helper_SingleListNodeRemove(notifyList, node))
    {
        TCPIP_HEAP_Free(heapH, node);
        return true;
    }

    return false;

}


void TCPIP_Notification_RemoveAll(SINGLE_LIST* notifyList, TCPIP_HEAP_HANDLE heapH)
{
    SGL_LIST_NODE* dNode;

    while( (dNode = TCPIP_Helper_SingleListHeadRemove(notifyList)) != 0 )
    {
        TCPIP_HEAP_Free(heapH, dNode);
    }

}




