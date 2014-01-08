/*******************************************************************************
 System Interrupt Source File

  File Name:
    sys_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the 
    interrupt sub-system.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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

#include <sys/attribs.h>
#include "app.h"

#include <sys/kmem.h>

extern volatile GFX_COLOR GraphicsFrame[1][(DISP_VER_RESOLUTION)][(DISP_HOR_RESOLUTION)];


uint16_t cameraLine = 0;

void __ISR(_CHANGE_NOTICE_A_VECTOR) _HSyncHandler(void)
{
   if(PORTAbits.RA1 == 1)
   {
    //1st HSYNC Occured so Enable VSYNC and start Dma Transfer
    if(cameraLine < 272)
    {

    DCH0DSA = KVA_TO_PA(&GraphicsFrame[0][cameraLine][0]);
    // once we configured the DMA channel we can enable it
    DCH0CONSET = 0x80;

    }
       cameraLine++;
    }

    IFS3bits.CNAIF = 0; //Clear intterupt flag
}

void __ISR(_CHANGE_NOTICE_J_VECTOR) _VSyncHandler(void)
{
   if(PORTJbits.RJ2 == 1)
   {
       cameraLine = 0;
   }
       IFS3bits.CNJIF = 0; //Clear intterupt flag
}

/*******************************************************************************
 End of File
 */

