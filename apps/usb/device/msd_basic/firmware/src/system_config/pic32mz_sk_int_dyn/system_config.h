/*******************************************************************************
  CDC Basic Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    sys_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the CDC Basic demo
    application for the PIC32 USB starter kit.
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

#ifndef _SYS_CONFIG_H    
#define _SYS_CONFIG_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_DEVICE_MODE_SUPPORT_ENABLE true

#define DRV_USB_HOST_MODE_SUPPORT_ENABLE    false

#define DRV_USB_ENDPOINTS_NUMBER 3

/* EP0 buffer size. Used by controller driver */
#define USB_DEVICE_EP0_BUFFER_SIZE 64

// *****************************************************************************
/* USB hardware instance configuration

  Summary:
    Selects the maximum number of hardware instances that can be supported by
    the dynamic driver

  Description:
    This definition selects the maximum number of hardware instances that can be
    supported by the dynamic driver. Comment this line for a static build of the
    driver.

  Remarks:
    None
*/

#define DRV_USB_INSTANCES_NUMBER  /*DOM-IGNORE-BEGIN*/ 1 /*DOM-IGNORE-END*/

// *****************************************************************************
/* USB Maximum Number of Clients

  Summary:
    Selects the maximum number of clients

  Description:
    This definition select the maximum number of clients that the USB driver can
    support at run time. In almost all realistic USB device applications, the driver
    will atleast have 2 or more clients.

  Remarks:
    None.

*/

#define DRV_USB_CLIENTS_NUMBER  /*DOM-IGNORE-BEGIN*/ 1/*DOM-IGNORE-END*/





// *****************************************************************************
/* USB Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is

    - true  - Select if interrupt mode of timer operation is desired

    - false - Select if polling mode of timer operation is desired

    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_USB_INTERRUPT_MODE  /*DOM-IGNORE-BEGIN*/true/*DOM-IGNORE-END*/




// *****************************************************************************
// *****************************************************************************
// Section: Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            2

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              3


// *****************************************************************************
// *****************************************************************************
// Section: MSD Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* CDC function driver index */
#define APP_USBMSD_FUNC_INDEX                       0





/*  Following are the file system settings */

/*********** Sector Address Calculation macros ********************
    These macros are used to calculate the sector address of each
    of the blocks.  These are then used to locate where the blocks
    go in program memory on certain processors using processor specific
    attribute() commands
*******************************************************************/
#define BOOT_SECTOR_ADDRESS         1
#define FAT0_ADDRESS                (BOOT_SECTOR_ADDRESS + 1)
#define FATx_ADDRESS                (FAT0_ADDRESS + 1)
#define ROOTDIRECTORY0_ADDRESS      (FAT0_ADDRESS + MDD_INTERNAL_FLASH_NUM_FAT_SECTORS)



/************************************************************************/

//---------------------------------------------------------------------------------------
    //The size (in number of sectors) of the desired usable data portion of the MSD volume
    //---------------------------------------------------------------------------------------
    //Note: Windows 7 appears to require a minimum capacity of at least 13 sectors.
    //Note2: Windows will not be able to format a drive if it is too small.  The reason
    //for this, is that Windows will try to put a "heavyweight" (comparatively) filesystem
    //on the drive, which will consume ~18kB of overhead for the filesystem.  If the total
    //drive size is too small to fit the filesystem, then Windows will give an error.
    //This also means that formatting the drive will "shrink" the usuable data storage
    //area, since the default FAT12 filesystem implemented in the Files.c data tables is very
    //lightweight, with very low overhead.
    //Note3: It is important to make sure that no part of the MSD volume shares a flash
    //erase page with the firmware program memory.  This can be done by using a custom
    //modified linker script, or by carefully selecting the starting address and the
    //total size of the MSD volume.  See also below code comments.
    //Note4: It is also important to make sure that no part of the MSD volume shares
    //an erase page with the erase page that contains the microcontroller's configuration
    //bits (for microcontrollers that use flash for storing the configuration bits,
    //see device datasheet). This can be accomplished by using a modified linker script,
    //which protects the flash page with the configuration bits (if applicable), or,
    //by carefully choosing the FILES_ADDRESS and MDD_INTERNAL_FLASH_DRIVE_CAPACITY,
    //to make sure the MSD volume does extend into the erase page with the configuration
    //bits.
    #define MDD_INTERNAL_FLASH_DRIVE_CAPACITY 14   


//--------------------------------------------------------------------------
    //Maximum files supported
    //--------------------------------------------------------------------------
    //MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT must be a multiple of 16
    //Note: Even if MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT is 16, this does not
    //necessarily mean the drive will always work with 16 files.  The drive will
    //suppport "up to" 16 files, but other limits could be hit first, even before
    //the drive is full.  The RootDirectory0[] sector could get full with less
    //files, especially if the files are using long filenames.
    #define MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT 16


//Note: If only 1 FAT sector is used, assuming 12-bit (1.5 byte) FAT entry size
//(ex: FAT12 filesystem), then the total FAT entries that can fit in a single 512
//byte FAT sector is (512 bytes) / (1.5 bytes/entry) = 341 entries.  This allows
//the FAT table to reference up to 341*512 = ~174kB of space.  Therfore, more
//FAT sectors are needed if creating an MSD volume bigger than this.
#define MDD_INTERNAL_FLASH_NUM_RESERVED_SECTORS 1
#define MDD_INTERNAL_FLASH_NUM_VBR_SECTORS 1
#define MDD_INTERNAL_FLASH_NUM_FAT_SECTORS 1
#define MDD_INTERNAL_FLASH_NUM_ROOT_DIRECTORY_SECTORS ((MDD_INTERNAL_FLASH_MAX_NUM_FILES_IN_ROOT+15)/16) //+15 because the compiler truncates
#define MDD_INTERNAL_FLASH_OVERHEAD_SECTORS (\
            MDD_INTERNAL_FLASH_NUM_RESERVED_SECTORS + \
            MDD_INTERNAL_FLASH_NUM_VBR_SECTORS + \
            MDD_INTERNAL_FLASH_NUM_ROOT_DIRECTORY_SECTORS + \
            MDD_INTERNAL_FLASH_NUM_FAT_SECTORS)
#define MDD_INTERNAL_FLASH_TOTAL_DISK_SIZE (\
            MDD_INTERNAL_FLASH_OVERHEAD_SECTORS + \
            MDD_INTERNAL_FLASH_DRIVE_CAPACITY)
#define MDD_INTERNAL_FLASH_PARTITION_SIZE (uint32_t)(MDD_INTERNAL_FLASH_TOTAL_DISK_SIZE - 1)  //-1 is to exclude the sector used for the MBR




#define ERASE_BLOCK_SIZE        ( 16 * 1024 )
#define WRITE_BLOCK_SIZE        ( 16 * 1024 )
/************************************************************************/

// The size of a sector
// Must be 512, 1024, 2048, or 4096
// 512 bytes is the value used by most cards
#define MEDIA_SECTOR_SIZE 		512

#define MASTER_BOOT_RECORD_ADDRESS &MasterBootRecord[0]




#define USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES 1
#define USB_DEVICE_MDD_INTFLASH_MAX_CLIENTS   1

#define USB_DEVICE_MDD_INTFLASH_INDEX 0


#define MBR_ATTRIBUTES                      __attribute__((aligned (ERASE_BLOCK_SIZE),section(".MDD_FILES")))
#define PARTITION_ATTRIBUTES(sector_num)    __attribute__ ((section(".MDD_FILES")))

//************ Following are MSD function driver configurations ************************
#define USB_DEVICE_MSD_MAX_INSTANCES                2

#define USB_DEVICE_MSD_MAX_LUN                      1
#define USB_DEVICE_MSD_MAX_SECTOR_SIZE              512


/***************************************************************************************/

#define DRV_USB_DEVICE_SUPPORT true
#define DRV_USB_HOST_SUPPORT false
#define DRV_USB_DEVICE_IRP_QUEUE_SIZE 10


#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

