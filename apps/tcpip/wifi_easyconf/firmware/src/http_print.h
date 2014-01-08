/*********************************************************************
 * File Name: http_print.h
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * Processor: PIC24E, PIC24F, PIC24H, dsPIC30F, dsPIC33F, dsPIC33E,PIC32
 * Compiler:  Microchip C30, C32,XC30,XC32
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
 * reserved.
 * Microchip licenses to you the right to use, modify, copy, and distribute
 * software only embedded on a Microchip microcontroller or digital signal 
 * controller that is integrated into your product or third party product
 * (pursuant to the sublicense terms in the accompanying license agreement)

 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *********************************************************************/

#ifndef __HTTPPRINT_H
#define __HTTPPRINT_H

#include "tcpip/tcpip.h"

#if defined(TCPIP_STACK_USE_HTTP_SERVER)

void HTTPPrint(HTTP_CONN_HANDLE connHandle,uint32_t callbackID);
void HTTPPrint_led(HTTP_CONN_HANDLE connHandle,uint16_t);
void HTTPPrint_nextSSID(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_prevSSID(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_prevWLAN(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_nextWLAN(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_scan(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_fwver(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_bssCount(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_ssid(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_valid(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_name(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_privacy(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_wlan(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_strength(HTTP_CONN_HANDLE connHandle);
void HTTPPrint_btn(HTTP_CONN_HANDLE connHandle,uint16_t);
void HTTPPrint_pot(HTTP_CONN_HANDLE connHandle);

void HTTPPrint(HTTP_CONN_HANDLE connHandle,uint32_t callbackID)
{
TCP_SOCKET sktHTTP; 
	switch(callbackID)
	{
        case 0x00000000:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t*)"header.inc");
			break;
        case 0x00000001:
			TCPIP_HTTP_FileInclude(connHandle,(const uint8_t*)"footer.inc");
			break;
        case 0x00000002:
			HTTPPrint_led(connHandle,0);
			break;
        case 0x00000003:
			HTTPPrint_nextSSID(connHandle);
			break;
        case 0x00000004:
			HTTPPrint_prevSSID(connHandle);
			break;
        case 0x00000005:
			HTTPPrint_prevWLAN(connHandle);
			break;
        case 0x00000006:
			HTTPPrint_nextWLAN(connHandle);
			break;
        case 0x00000007:
			HTTPPrint_scan(connHandle);
			break;
        case 0x00000008:
			HTTPPrint_fwver(connHandle);
			break;
        case 0x00000009:
			HTTPPrint_bssCount(connHandle);
			break;
        case 0x0000000a:
			HTTPPrint_ssid(connHandle);
			break;
        case 0x0000000b:
			HTTPPrint_valid(connHandle);
			break;
        case 0x0000000c:
			HTTPPrint_name(connHandle);
			break;
        case 0x0000000d:
			HTTPPrint_privacy(connHandle);
			break;
        case 0x0000000e:
			HTTPPrint_wlan(connHandle);
			break;
        case 0x0000000f:
			HTTPPrint_strength(connHandle);
			break;
        case 0x00000010:
			HTTPPrint_led(connHandle,1);
			break;
        case 0x00000011:
			HTTPPrint_led(connHandle,2);
			break;
        case 0x00000012:
			HTTPPrint_led(connHandle,3);
			break;
        case 0x00000013:
			HTTPPrint_led(connHandle,4);
			break;
        case 0x00000014:
			HTTPPrint_led(connHandle,5);
			break;
        case 0x00000015:
			HTTPPrint_led(connHandle,6);
			break;
        case 0x00000016:
			HTTPPrint_led(connHandle,7);
			break;
        case 0x00000017:
			HTTPPrint_btn(connHandle,0);
			break;
        case 0x00000018:
			HTTPPrint_btn(connHandle,1);
			break;
        case 0x00000019:
			HTTPPrint_btn(connHandle,2);
			break;
        case 0x0000001a:
			HTTPPrint_btn(connHandle,3);
			break;
        case 0x0000001b:
			HTTPPrint_pot(connHandle);
			break;
		default:
			// Output notification for undefined values
                       sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
			TCPIP_TCP_ArrayPut(sktHTTP, (const uint8_t*)"!DEF", 4);
	}

	return;
}

void HTTPPrint_(HTTP_CONN_HANDLE connHandle)
{
       TCP_SOCKET sktHTTP = TCPIP_HTTP_CurrentConnectionSocketGet(connHandle);
	TCPIP_TCP_Put(sktHTTP, '~');
	return;
}

#endif

#endif
