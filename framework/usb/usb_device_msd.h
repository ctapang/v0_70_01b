/*******************************************************************************
  USB MSD function driver interface header

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_msd.h

  Summary:
    USB device MSD function driver interface header

  Description:
    USB device MSD function driver interface header
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

#ifndef _USB_DEVICE_MSD_H
#define _USB_DEVICE_MSD_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/
#include <stdint.h>
#include <stdbool.h>
#include "system/common/sys_common.h"
#include "system/common/sys_module.h"
#include "driver/driver_common.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "system_config.h"


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

/* MSD Interface Class Code */
#define USB_DEVICE_MSD_INTF               0x08


/* MSD Interface Class SubClass Codes */
#define USB_DEVICE_MSD_INTF_SUBCLASS       0x06 // Only scsi transparent is supported.


/* MSD Interface Class Protocol Codes */
#define USB_DEVICE_MSD_PROTOCOL           0x50

/*DOM-IGNORE-BEGIN*/
extern const USB_DEVICE_FUNCTION_DRIVER msdFunctionDriver ;
/*DOM-IGNORE-END*/


// *****************************************************************************
/* 
  Summary:
    This structure contains all the media driver callback function pointers.
    The MSD driver makes call to these function pointers at run time to know the
    status of the media and to read and write the media.
  
  Description:
    The user must provide the callback function address of the media at compile
    time. MSD driver calls these function during run time to perform
    media operation or to know the media status.

  Remarks:
    None.
*/
typedef struct USB_DEVICE_MSD_MEDIA_FUNCTIONS
{
    // Media init state.
    SYS_STATUS (*mediaInitState) (SYS_MODULE_OBJ objIndex);

    //Function pointer to the MediaInitialize() function of the physical media
    //  being used.
    DRV_HANDLE (* open) (const SYS_MODULE_INDEX index, const DRV_IO_INTENT  intent );

    // Function pointer for closing the physical media.
    void (* close)(DRV_HANDLE hClient );

    //Function pointer to the ReadCapacity() function of the physical media
    //  being used.
    uint32_t (*readCapacity)( DRV_HANDLE drvHandle );
    //Function pointer to the ReadSectorSize() function of the physical media
    //  being used.
    uint32_t  (*readSectorSize)( DRV_HANDLE drvHandle );
    //Function pointer to the MediaDetect() function of the physical media
    //  being used.
    bool  (*mediaDetect)( DRV_HANDLE drvHandle );
    //Function pointer to the SectorRead() function of the physical media being
    //  used.
    bool  (*sectorRead)(DRV_HANDLE drvHandle, uint32_t sector_addr, uint8_t * buffer,
                            void * refHandle, MEDIA_OP_CMPLT_CB callBack);
    //Function pointer to the WriteProtectState() function of the physical
    //  media being used.
    uint8_t  (*writeProtectState)( DRV_HANDLE drvHandle );
    //Function pointer to the SectorWrite() function of the physical media
    //  being used.
    bool  (*sectorWrite)( DRV_HANDLE drvHandle, uint32_t sector_addr, uint8_t* buffer,
                                void * refHandle, MEDIA_OP_CMPLT_CB callBack);
} USB_DEVICE_MSD_MEDIA_FUNCTIONS;


// *****************************************************************************
/* 
  Summary:
    Inquiry response structure.

  Description:
    USB Device MSD inquiry response structure as defined in 
    SCSI Primary Commands - 4.
 
  Remarks:
    None.
*/

typedef struct USB_DEVICE_MSD_INQUIRY_RESPONSE
{
    /* Peripheral_Qualifier:3; Peripheral_DevType:5; */
    uint8_t peripheral;

    /* Removable medium bit7 = 0 means non removable, rest reserved */
    uint8_t removable;

    /* Version */
    uint8_t version;

    /* b7,b6 Obsolete, b5 Access control co-ordinator, b4 hierarchical addressing support */
    /* b3:0 response data format 2 indicates response is in format defined by spec */
    uint8_t responseDataFormat;

    /* length in bytes of remaining in standard inquiry data */
    uint8_t additionalLength;

    /* b7 SCCS, b6 ACC, b5-b4 TGPS, b3 3PC, b2-b1 Reserved, b0 Protected */
    uint8_t sccstp;

    /* b7 bque, b6- EncServ, b5-VS, b4-MultiP, b3-MChngr, b2-b1 Obsolete, b0-Addr16 */
    uint8_t bqueetc;

    /* b7-b6 Obsolete, b5-WBUS, b4-Sync, b3-Linked, b2 Obsolete,b1 Cmdque, b0-VS */
    uint8_t cmdQue;

    /* Vendor ID */
    uint8_t vendorID[8];

    /* Product ID */
    uint8_t productID[16];

    /* Product Revision */
    uint8_t productRev[4];
    
} USB_DEVICE_MSD_INQUIRY_RESPONSE;     

// *****************************************************************************
/*
 
  Summary:
    This structure holds media related data of a particular logical unit.
   
  Description:
    It holds pointer to inquiry response, instance index and pointer to a
    structure that contains  all media callback functions.

  Remarks:
    An object of this structure must be configured by the user at compile time.
*/

typedef struct USB_DEVICE_MSD_MEDIA_INIT_DATA
{
    /* Instance index of the media */
    SYS_MODULE_INDEX instanceIndex;

    /* Pointer to inquiry response */
    USB_DEVICE_MSD_INQUIRY_RESPONSE inquiryResponse;

    /* Callback function pointers of the media */
    USB_DEVICE_MSD_MEDIA_FUNCTIONS mediaCallBackPtrs;

}USB_DEVICE_MSD_MEDIA_INIT_DATA;


// *****************************************************************************
/* USB MSD init structure.

  Summary:
    This structure contains required parameters for MSD initialization.

  Description:
    This structure contains interface number, bulk-IN and bulk-OUT endpoint 
    addresses, endpointSize, number of logical units supported and pointer to
    array of structure that contains media initialization.

  Remarks:
    This structure must be configured by the user at compile time.
*/

typedef struct USB_DEVICE_MSD_INIT
{
    /* Number of logical units supported. */
    uint8_t     numberOfLogicalUnits;
    /* Media related data */
    USB_DEVICE_MSD_MEDIA_INIT_DATA mediaInit[USB_DEVICE_MSD_MAX_LUN];
}USB_DEVICE_MSD_INIT;



#endif // _USB_DEVICE_MSD_H

/*******************************************************************************
 End of File
*/


