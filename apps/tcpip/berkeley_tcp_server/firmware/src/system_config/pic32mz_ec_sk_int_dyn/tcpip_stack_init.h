/*******************************************************************************
 System Initialization File

  File Name:
    tcpip_stack_init.h

  Summary:
    TCP/IP Stack Initialization.

  Description:
    This file contains source code necessary to initialize the tcp/ip stack.
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

#ifndef __TCPIP_MODULES_CONFIG_H_
#define __TCPIP_MODULES_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>

/*********************************************************************
 * Function:        bool TCPIP_STACK_Init()
 *
 * PreCondition:    None
 *
 * Input:
 *
 * Output:          true if Stack and its componets are initialized
 *                  false otherwise
 *
 * Overview:        The function initializes the stack.
 *                  If an error occurs, the SYS_ERROR() is called
 *                  and the function de-initialize itself and will return false.
 *
 * Side Effects:    None
 *
 * Note:            This function must be called before any of the
 *                  stack or its component routines are used.
 *
 ********************************************************************/


bool TCPIP_STACK_Init();

#endif