/*******************************************************************************
  USB MDD internal flash header file.

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_mdd_internal_flash.h

  Summary:
    Media driver for internal flash.

  Description:
   Media driver interface header
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _USB_DEVICE_MDD_INTERNAL_FLASH_H
#define _USB_DEVICE_MDD_INTERNAL_FLASH_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/
#include <stdint.h>
#include <stdbool.h>
#include "driver/driver_common.h"


typedef enum
{
    USB_DEVICE_MDD_INTFLASH_WP_STATE_PROTECTED = 0x80,
    USB_DEVICE_MDD_INTFLASH_WP_STATE_UNPROTECTED = 0x00

}USB_DEVICE_MDD_INTFLASH_WP_STATE;


typedef struct _USB_DEVICE_MDD_INTFLASH_INIT_
{
    uint16_t    mediaSectorSize;
    uint32_t    totalDiskSize;
    uint8_t *   masterBootRecordAdrs;
    uint16_t    eraseBlockSize;
    uint8_t *   scratchBuffer;
    USB_DEVICE_MDD_INTFLASH_WP_STATE        wpState;
}USB_DEVICE_MDD_INTFLASH_INIT;

typedef void (*MEDIA_OP_CMPLT_CB) ( void * refHandle, bool success);

uint32_t USB_DEVICE_MDD_INTFLASH_ReadCapacity( DRV_HANDLE hClient );
uint32_t USB_DEVICE_MDD_INTFLASH_ReadSectorSize( DRV_HANDLE hClient );
bool USB_DEVICE_MDD_INTFLASH_SectorRead(DRV_HANDLE hClient, uint32_t sector_addr, uint8_t * buffer,
                                        void * refHandle, MEDIA_OP_CMPLT_CB callBack);
uint8_t USB_DEVICE_MDD_INTFLASH_WriteProtectState( DRV_HANDLE hClient );
bool  USB_DEVICE_MDD_INTFLASH_SectorWrite(DRV_HANDLE hClient, uint32_t sector_addr, uint8_t* buffer,
                                                    void * refHandle, MEDIA_OP_CMPLT_CB callBack);
bool USB_DEVICE_MDD_INTFLASH_MediaDetect(DRV_HANDLE hClient);

SYS_MODULE_OBJ USB_DEVICE_MDD_INTFLASH_Initialize(const SYS_MODULE_INDEX index,
                                        const SYS_MODULE_INIT * const initData);

DRV_HANDLE USB_DEVICE_MDD_INTFLASH_Open(const SYS_MODULE_INDEX index,
                                        const DRV_IO_INTENT  intent );

void USB_DEVICE_MDD_INTFLASH_Close(DRV_HANDLE hClient );

SYS_STATUS USB_DEVICE_MDD_INTFLASH_Status(SYS_MODULE_OBJ objIndex);

#endif // _USB_DEVICE_MSD_INTERNAL_FLASH_H

/*******************************************************************************
 End of File
*/


