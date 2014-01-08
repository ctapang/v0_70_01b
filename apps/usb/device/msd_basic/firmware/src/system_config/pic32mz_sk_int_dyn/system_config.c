/*******************************************************************************
 MSD Basic Demo Configuration file.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    Top-level configuration file for the CDC Basic demo application for
    the PIC32 Starter kit

  Description:
    This file contains the USB descriptors and CDC calss specific data that
	needs to be provided by the application.
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

#include <GenericTypeDefs.h>
#include "app.h"


#define MSD_IN_EP_SIZE           64u
#define MSD_OUT_EP_SIZE          64u
// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************

// USB descriptors
/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{


     0x12,    // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,                // DEVICE descriptor type
    0x0110,                     // USB Spec Release Number in BCD format
    0x00,                       // Class Code
    0x00,                       // Subclass code
    0x00,                       // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE, // Max packet size for EP0, see usbcfg.h
    0x04D8,                     // Vendor ID
    0x0009,                     // Product ID: mass storage device demo
    0x0001,                     // Device release number in BCD format
    0x01,                       // Manufacturer string index
    0x02,                       // Product string index
    0x03,                       // Device serial number string index
    0x01                    // Number of possible configurations
};


/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[]={
    /* Configuration Descriptor */
    9,                                                          // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                               // CONFIGURATION descriptor type
    0x20,0x00,                                                  // Total length of data for this cfg
    1,                                                          // Number of interfaces in this cfg
    1,                                                          // Index value of this configuration
    0,                                                          // Configuration string index
    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED,                 // Attributes, see usbdefs_std_dsc.h
    50,                                                         // Max power consumption (2X mA)

    /* Interface Descriptor */
    9,   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    0,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    USB_DEVICE_MSD_INTF,               // Class code
    USB_DEVICE_MSD_INTF_SUBCLASS,      // Subclass code
    USB_DEVICE_MSD_PROTOCOL, 		    // Protocol code
    0,                      // Interface string index

    /* Endpoint Descriptor */
    7,
    USB_DESCRIPTOR_ENDPOINT,
    0x01 | USB_EP_DIRECTION_IN,
    USB_TRANSFER_TYPE_BULK,
    MSD_IN_EP_SIZE,
    0x00,
    0x00,

    7,
    USB_DESCRIPTOR_ENDPOINT,
    0x01 | USB_EP_DIRECTION_OUT,
    USB_TRANSFER_TYPE_BULK,
    MSD_OUT_EP_SIZE,
    0x00,
    0x00
};


// String descriptors.

//Language code string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409
}};

//Manufacturer string descriptor
const struct{const uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};

//Product string descriptor
const struct{const uint8_t bLength;uint8_t bDscType;uint16_t string[22];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'S','i','m','p','l','e',' ','M','S','D',' ',
'D','e','v','i','c','e',' ','D','e','m','o'
}};

//Serial number string descriptor.  Note: This should be unique for each unit
//built on the assembly line.  Plugging in two units simultaneously with the
//same serial number into a single machine can cause problems.  Additionally, not
//all hosts support all character values in the serial number string.  The MSD
//Bulk Only Transport (BOT) specs v1.0 restrict the serial number to consist only
//of ASCII characters "0" through "9" and capital letters "A" through "F".
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[12];}sd003={
sizeof(sd003),USB_DESCRIPTOR_STRING,
{'1','2','3','4','5','6','7','8','9','9','9','9'}};


//Array of string descriptors
const uint8_t *const USB_SD_Ptr[4]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002,
    (const uint8_t *const)&sd003
};


//Array of full speed config descriptors
const uint8_t *const fullSpeedConfigDescSet[1] =
{
    (const uint8_t *const)&configDescriptor1[0]
};


//Array of full speed config descriptors
const uint8_t *const highSpeedConfigDescSet[1] =
{
    (const uint8_t *const)&configDescriptor1[0]
};


const USB_DEVICE_MSD_INIT msdInit =
{
    1, // Number of logical unit (LUN)

    { // Begin first LUN info
        {
            USB_DEVICE_MDD_INTFLASH_INDEX,
            // Inquiry response for the first logical unit.
            {
                0x00,		// peripheral device is connected, direct access block device
            	0x80,           // removable
            	0x04,	 	// version = 00=> does not conform to any standard, 4=> SPC-2
            	0x02,		// response is in format specified by SPC-2
            	0x20,		// n-4 = 36-4=32= 0x20
            	0x00,		// sccs etc.
            	0x00,		// bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
            			// but as in case of other device, we are just using 00
            	0x00,		// 00 obsolete, 0x80 for basic task queueing
            	{'M','i','c','r','o','c','h','p'
                },
            	// this is the T10 assigned Vendor ID
            	{'M','a','s','s',' ','S','t','o','r','a','g','e',' ',' ',' ',' '
                },
            	{'0','0','0','1'
                }
            },

            // MDD function callback pointers for first loical uint.
             {
                &USB_DEVICE_MDD_INTFLASH_Status,
                &USB_DEVICE_MDD_INTFLASH_Open,
                &USB_DEVICE_MDD_INTFLASH_Close,
                &USB_DEVICE_MDD_INTFLASH_ReadCapacity, //&MDD_IntFlash_ReadCapacity,
                &USB_DEVICE_MDD_INTFLASH_ReadSectorSize , //&MDD_IntFlash_ReadSectorSize,
                &USB_DEVICE_MDD_INTFLASH_MediaDetect, //&MDD_IntFlash_MediaDetect,
                &USB_DEVICE_MDD_INTFLASH_SectorRead, //&MDD_IntFlash_SectorRead,
                &USB_DEVICE_MDD_INTFLASH_WriteProtectState, //&MDD_IntFlash_WriteProtectState,
                &USB_DEVICE_MDD_INTFLASH_SectorWrite //&MDD_IntFlash_SectorWrite
            }
        }
    }// End of first LUN info

   // { // Start of second LUN info


    // }// End of second LUN info


};



// *****************************************************************************
/* Global USB Device function registration structure

  Summary:
    A function driver has to be registered with the USB device layer
    using this structure.

  Description:


  Remarks:

*/

const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] =
{
    {
        // Speed                                    Configuration value   interfaceNumber  number of interfaces
        USB_SPEED_FULL | USB_SPEED_HIGH,                 1,      0,              1,
                                // function driver index      MSD driver init       MSD driver
                                APP_USBMSD_FUNC_INDEX,     (void*)&msdInit,     (USB_DEVICE_FUNCTION_DRIVER*) &msdFunctionDriver
    }

};


// *****************************************************************************
/* Global USB Descriptor Structure

  Summary:
    Global USB descriptor structure containing pointers to standard USB
    descriptor structures.

  Description:


  Remarks:

*/

const USB_MASTER_DESCRIPTOR usbMasterDescriptor =
{
    /* Full speed descriptor */
    (uint8_t*)&device_dsc,

    /* Total number of full speed configurations available */
    1,

    /* Pointer to array of full speed configurations descriptors*/
    (USB_DEVICE_CONFIG_DESCS_PTR)&fullSpeedConfigDescSet[0],

    /* High speed device desc is not supported*/
    (uint8_t*)&device_dsc,

    /*Total number of high speed configurations available */
    1,

    /* Pointer to array of high speed configurations descriptors. Not supported*/
    (USB_DEVICE_CONFIG_DESCS_PTR)&highSpeedConfigDescSet[0],

    /* Total number of string descriptors available */
    4,

    /* Pointer to array of string descriptors */
    (USB_DEVICE_STRING_DESCS_PTR)USB_SD_Ptr,

    /* Pointer to full speed dev qualifier. Not supported */
    NULL,

    /* Pointer to high speed dev qualifier. Not supported */
    NULL,

};




//------------------------------------------------------------------------------
//Master boot record at LBA = 0
//------------------------------------------------------------------------------
const uint8_t MBR_ATTRIBUTES MasterBootRecord[MEDIA_SECTOR_SIZE] =
{
//Code Area
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	//0x0000
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0010
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0020
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0030
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0040
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0050
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0060
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0070
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0080
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0090
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00A0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00B0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00C0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00D0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00E0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x00F0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0100
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0110
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0120
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0130
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0140
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0150
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0160
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0170
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                     //0x0180

//IBM 9 byte/entry x 4 entries primary partition table
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                             //0x018A
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x0190
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,             //0x01A0

//???
0x00, 0x00,                                                                                     //0x01AE
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                 //0x01B0

//Disk signature
0xF5, 0x8B, 0x16, 0xEA,                                                                         //0x01B8

//??? - usually 0x0000
0x00, 0x00,                                                                                     //0x01BC

//Table of Primary Partitions (16 bytes/entry x 4 entries)
//Note: Multi-byte fields are in little endian format.
//Partition Entry 1                                                                             //0x01BE
0x80,                   //Status - 0x80 (bootable), 0x00 (not bootable), other (error)
0x01, 0x01, 0x00,       //Cylinder-head-sector address of first sector in partition
0x01,                   //Partition type - 0x01 = FAT12 up to 2MB
0x07, 0xFF, 0xE6,       //Cylinder-head-sector address of last sector in partition
0x01, 0x00, 0x00, 0x00, //Logical Block Address (LBA) of first sector in partition
(uint8_t)MDD_INTERNAL_FLASH_PARTITION_SIZE, (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 8), (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 16), (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 24), //Length of partition in sectors (MBR sits at LBA = 0, and is not in the partition.)

//Partition Entry 2
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x01CE
//Partition Entry 3
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x01DE
//Partition Entry 4
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //0x01EE

//MBR signature
0x55, 0xAA                                                                                      //0x01FE
};




//------------------------------------------------------------------------------
//Partition boot sector at LBA = 1
//------------------------------------------------------------------------------
//Physical Sector - 1, Logical Sector - 0.
//This is the first sector in the partition, and is known as the "volume boot record" or "partition boot sector"
//Note: This table is filesystem specific.  Re-formatting the drive will overwrite this table.
const uint8_t PARTITION_ATTRIBUTES(BOOT_SECTOR_ADDRESS) BootSector[MEDIA_SECTOR_SIZE]  =
{
0xEB, 0x3C, 0x90,			//Jump instruction
'M', 'S', 'D', 'O', 'S', '5', '.', '0',	//OEM Name "MSDOS5.0"
(MEDIA_SECTOR_SIZE&0xFF), (MEDIA_SECTOR_SIZE>>8),	    //Bytes per sector (MEDIA_SECTOR_SIZE)
0x01,			    //Sectors per cluster
MDD_INTERNAL_FLASH_NUM_RESERVED_SECTORS, 0x00,			//Reserved sector count (usually 1 for FAT12 or FAT16)
0x01,			    //number of FATs
MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT, 0x00,			//Max number of root directory entries - 16 files allowed
0x00, 0x00,			//total sectors (0x0000 means: use the 4 byte field at offset 0x20 instead)
0xF8,			    //Media Descriptor
MDD_INTERNAL_FLASH_NUM_FAT_SECTORS, 0x00,         //Sectors per FAT
0x3F, 0x00,	                //Sectors per track
0xFF, 0x00,                 //Number of heads
0x01, 0x00, 0x00, 0x00,		//Hidden sectors
(uint8_t)MDD_INTERNAL_FLASH_PARTITION_SIZE, (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 8), (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 16), (uint8_t)(MDD_INTERNAL_FLASH_PARTITION_SIZE >> 24),	//Total sectors (when WORD value at offset 20 is 0x0000)

0x00,			//Physical drive number
0x00,			//Reserved("current head")
0x29,			//Signature
0x32, 0x67, 0x94, 0xC4,		//ID(serial number)
'N', 'O', ' ', 'N', 'A', 'M', 'E', ' ', ' ', ' ', ' ',	//Volume Label (11 bytes) - "NO NAME    "
'F', 'A', 'T', '1', '2', ' ', ' ', ' ',	//FAT system "FAT12   "
//Operating system boot code
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x55, 0xAA			//End of sector (0x55AA)
};


//------------------------------------------------------------------------------
//First FAT sector at LBA = 2
//------------------------------------------------------------------------------
//Please see:  http://technet.microsoft.com/en-us/library/cc938438.aspx
//For short summary on how this table works.
//Note: This table consists of a series of 12-bit entries, and are fully packed
//(no pad bits).  This means every other byte is a "shared" byte, that is split
//down the middle and is part of two adjacent 12-bit entries.
//The entries are in little endian format.
const uint8_t PARTITION_ATTRIBUTES(FAT0_ADDRESS) FAT0[MEDIA_SECTOR_SIZE] =
{
    0xF8,0x0F,   //Copy of the media descriptor 0xFF8
    0x00,
    0xFF,0x0F
};

//Optional additional FAT space here, only needed for drives > ~174kB.
#if(MDD_INTERNAL_FLASH_NUM_FAT_SECTORS > 1)
ROM BYTE PARTITION_ATTRIBUTES(FATx_ADDRESS) FATx[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_NUM_FAT_SECTORS - 1)];
#endif


const uint8_t PARTITION_ATTRIBUTES(ROOTDIRECTORY0_ADDRESS) RootDirectory0[MEDIA_SECTOR_SIZE] =
{
    //Root
    'D','r','i','v','e',' ','N','a','m','e',' ',   //Drive Name (11 characters, padded with spaces)
    0x08, //specify this entry as a volume label
    0x00, //Reserved
    0x00, 0x00, 0x00, 0x00, 0x11, //Create time
    0x00, 0x11,             //Last Access
    0x00, 0x00,             //EA-index
    0x00, 0x00, 0x00, 0x11, //Last modified time
    0x00, 0x00,             //First FAT cluster
    0x00, 0x00, 0x00, 0x00, //File Size (number of bytes)

    'F','I','L','E',' ',' ',' ',' ',    //File name (exactly 8 characters)
    'T','X','T',                        //File extension (exactly 3 characters)
    0x20, //specify this entry as a volume label
    0x00, //Reserved
    0x06, 0x28, 0x78, 0xDE, 0x38, //Create time
    0xDE, 0x38,             //Last Access
    0x00, 0x00,             //EA-index
    0x04, 0x77, 0xDE, 0x38, //Last modified
    0x02, 0x00,             //First FAT cluster
    0x04, 0x00, 0x00, 0x00, //File Size (number of bytes)
};

#if (MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT>16)
        ROM BYTE PARTITION_ATTRIBUTES(ROOTDIRECTORY1_ADDRESS) RootDirectory1[MEDIA_SECTOR_SIZE] =
        {0};
#endif

#if (MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT>32)
    ROM BYTE PARTITION_ATTRIBUTES(ROOTDIRECTORY2_ADDRESS) RootDirectory2[MEDIA_SECTOR_SIZE] =
    {0};
#endif

#if (MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT>48)
    ROM BYTE PARTITION_ATTRIBUTES(ROOTDIRECTORY3_ADDRESS) RootDirectory3[MEDIA_SECTOR_SIZE] =
    {0};
#endif

//********************* Data Sectors ************************

//Create a place holder in flash for each of sector of data defined by
//  the MDD_INTERNAL_FLASH_DRIVE_CAPACITY definition.
//
//We will initialize the the first sector worth placeholder with the ASCII
//contents "Data".  This is the contents of the FILE.TXT, based on our
//RootDirectory0[] and FAT0[] settings above.
#if (MDD_INTERNAL_FLASH_DRIVE_CAPACITY>0)
const uint8_t PARTITION_ATTRIBUTES(SLACK0_ADDRESS) slack0[MEDIA_SECTOR_SIZE] =
{
    'D','a','t','a'
};
#endif

//The rest of the MSD volume is unused/blank/not currently filled with any file(s).
//However, we still need to declare a BYTE array to fill the space, so the linker
//knows not to allocate anything else into this region of flash memory.
//Technically, this array declaration could be:
//ROM BYTE PARTITION_ATTRIBUTES slack1[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 1u)] = {0};
//In practice, some compilers will run into limitations when trying to declare arrays
//with more than 32767 elements.  Therefore, we declare the MSD volume placeholder as a
//series of arrays instead (each 32767 bytes or less), so as to support large MSD
//volume sizes.

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY>1)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 64)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK1_ADDRESS) slack1[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        const uint8_t PARTITION_ATTRIBUTES(SLACK1_ADDRESS) slack1[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 1u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 64)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 127)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK2_ADDRESS) slack2[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK2_ADDRESS) slack2[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 64u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 127)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 190)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK3_ADDRESS) slack3[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK3_ADDRESS) slack3[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 127u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 190)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 253)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK4_ADDRESS) slack4[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK4_ADDRESS) slack4[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 190u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 253)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 316)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK5_ADDRESS) slack5[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK5_ADDRESS) slack5[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 253u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 316)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 379)
        ROM BYTE PARTITION_ATTRIBUTES(SLACK6_ADDRESS) slack6[MEDIA_SECTOR_SIZE*63] = {0};
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK6_ADDRESS) slack6[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 316u)] = {0};
    #endif
#endif

#if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 379)
    #if(MDD_INTERNAL_FLASH_DRIVE_CAPACITY >= 442)
        #error "Your MSD Volume is larger than this example has provisions for.  Double click this message and add more flash memory placeholder bytes."
        //If your MDD_INTERNAL_FLASH_DRIVE_CAPACITY is > 442 sectors, then you need to declare more place holder
        //BYTE arrays to allocate to the MSD volume.  If you don't do this, the linker might try to "re-use" the
        //flash memory by placing program code inside the MSD volume, which would cause unanticipated behavior.
        //Please use the existing slack1[] to slack6[] placeholder array declarations as an example/template
        //to follow, and keep adding as many more slackx[] arrays as needed to meet your
        //MDD_INTERNAL_FLASH_DRIVE_CAPACITY size requirements.
    #else
        ROM BYTE PARTITION_ATTRIBUTES(SLACK7_ADDRESS) slack7[MEDIA_SECTOR_SIZE*(MDD_INTERNAL_FLASH_DRIVE_CAPACITY - 379u)] = {0};
    #endif
#endif




