/*******************************************************************************
  Sample Application

  File Name:
    app_commands.c

  Summary:
    commands for the tcp client demo app.

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

#include "tcpip/src/tcpip_private.h"
#include "tcpip/tcpip_manager.h"
#include "app_commands.h"
#include "app.h"

#if defined(TCPIP_STACK_COMMAND_ENABLE)



static int _APP_Commands_SendUDPPacket(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _APP_Commands_SetOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _APP_Commands_GetOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);

static const _SYS_CMD_DCPT    appCmdTbl[]=
{
    {"sendudppacket",     _APP_Commands_SendUDPPacket,              ": Sends the UDP Packet"},
    {"getudppacketoptions",     _APP_Commands_GetOptions,              ": Sets the hostname, port and message"},
    {"setudppacketoptions",     _APP_Commands_SetOptions,              ": Gets the current hostname, port, and message"},
};

bool APP_Commands_Init()
{
    if (!_SYS_COMMAND_ADDGRP(appCmdTbl, sizeof(appCmdTbl)/sizeof(*appCmdTbl), "app", ": app commands"))
    {
        SYS_ERROR(SYS_ERROR_ERROR, "Failed to create TCPIP Commands\r\n");
        return false;
    }
    strcpy(APP_Hostname_Buffer, "10.0.1.4");
    strcpy(APP_Port_Buffer, "9760");
    strcpy(APP_Message_Buffer, "Hello");
    APP_Send_Packet = false;
    return true;
}

char APP_Hostname_Buffer[MAX_URL_SIZE];
char APP_Port_Buffer[6];
char APP_Message_Buffer[MAX_URL_SIZE];
bool APP_Send_Packet = false;

int _APP_Commands_SendUDPPacket(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;


    if (argc != 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: sendudppacket\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: sendudppacket\r\n");
        return false;
    }
    APP_Send_Packet = true;
    return true;
}

int _APP_Commands_SetOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;


    if (argc != 4)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: getudppacketoptions <hostname> <port> <message>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: getudppacketoptions 10.0.1.4 9760 Hello\r\n");
        return false;
    }

    strcpy(APP_Hostname_Buffer, argv[1]);
    strcpy(APP_Port_Buffer, argv[2]);
    strcpy(APP_Message_Buffer, argv[3]);
    return true;
}

int _APP_Commands_GetOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;
    char buffer[160];

    if (argc != 1)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: getudppacketoptions\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: getudppacketoptions\r\n");
        return false;
    }

     (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Current UDP Options:\r\n");
     sprintf(buffer, "\thostname: '%s'\r\n", APP_Hostname_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, buffer);
     sprintf(buffer, "\tport: '%s'\r\n", APP_Port_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, buffer);
     sprintf(buffer, "\tmessage: '%s'\r\n", APP_Message_Buffer);
     (*pCmdIO->pCmdApi->msg)(cmdIoParam, buffer);

    return true;
}


#endif
