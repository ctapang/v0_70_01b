/*******************************************************************************

  Summary:

  Description:
*******************************************************************************/

/*******************************************************************************
File Name: sys_fs_config.h
Copyright ?2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS?WITHOUT WARRANTY OF ANY KIND,
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
#ifndef __SYS_FS_CONFIG_H_
#define __SYS_FS_CONFIG_H_

/*****************************************************************************
 * The system MPFS file system module
 * Use to enable the system MPFS file system functionality.
 *****************************************************************************/
#define SYS_FS_FILESYSTEM_MPFS

// *****************************************************************************
// *****************************************************************************
// Section: NVM Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* NVM Driver setup for interrupt mode */
#define DRV_NVM_INTERRUPT_MODE true

/* NVM Driver will support one instance */
#define DRV_NVM_INSTANCES_NUMBER 1

/* NVM Driver will have only one client */
#define DRV_NVM_CLIENTS_NUMBER 1

/* NVM Driver can support upto five data
 * requests */
#define DRV_NVM_BUFFER_OBJECT_NUMBER 5

/* NVM Driver Flash Memory row size
 * in bytes */
#define DRV_NVM_ROW_SIZE 2048

/* NVM Driver Flash Memory page size
 * in bytes */
#define DRV_NVM_PAGE_SIZE 16384

/* NVM Driver Flash Memory programming
 * key 1*/

#define DRV_NVM_PROGRAM_UNLOCK_KEY1 0xAA996655

/* NVM Driver Flash Memory programming
 * key 1*/

#define DRV_NVM_PROGRAM_UNLOCK_KEY2 0x556699AA


// *****************************************************************************
// *****************************************************************************
// Section: NVM Media Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* This is the number of NVM disks */
#define DRV_NVM_MEDIA_OBJECT_NUMBER 1

// *****************************************************************************
// *****************************************************************************
// Section: NVM Media Manager Configuration
// *****************************************************************************
// *****************************************************************************

/* This is the number of media disks */
#define SYS_FS_MEDIA_NUMBER 50

/* This is the number of volumes used in the application */
#define SYS_FS_VOLUME_NUMBER    50

// *****************************************************************************
// *****************************************************************************
// Section: SYS FS Configuration
// *****************************************************************************
// *****************************************************************************

/* This is the maximum number for files
 * that can be opened. */
#define SYS_FS_MAX_FILES    25

/* This is the maximum number of fil systems used in the application */
#define SYS_FS_MAX_FILE_SYSTEM_TYPE     1

// *****************************************************************************
// *****************************************************************************
// Section: SPI Driver Configuration
// *****************************************************************************
// *****************************************************************************


/* Number of driver instances */
#define DRV_SPI_INSTANCES_NUMBER                    1

/* Number of client to be supported */
#define DRV_SPI_CLIENTS_NUMBER                      1

/* Driver will work in polling mode */
#define DRV_SPI_INTERRUPT_MODE                      true

#define DRV_SPI_PORTS_REMAP_USAGE                   false

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

#define DRV_SPI_PERIPHERAL_ID                       SPI_ID_2

// *****************************************************************************
// *****************************************************************************
// Section: SDCARD Driver Configuration
// *****************************************************************************
// *****************************************************************************
#define DRV_SDCARD_INSTANCES_NUMBER                             1
#define DRV_SDCARD_CLIENTS_NUMBER                               1
#define DRV_SDCARD_INDEX_MAX                                    1
#define DRV_SDCARD_INDEX                                        DRV_SDCARD_INDEX_0
#define DRV_SDCARD_QUEUE_POOL_SIZE                              10

// *****************************************************************************
// *****************************************************************************
// Section: Media Manager Configuration
// *****************************************************************************
// *****************************************************************************
/*****************************************************************************
 * The file seperator used in directory paths.
 *****************************************************************************/
#ifndef SYS_FS_MAX_DIR
#define SYS_FS_MAX_DIR   235 //Maximum length of directory component
#endif
#ifndef SYS_FS_MAX_FNAME
#define SYS_FS_MAX_FNAME 8   //Maximum length of filename component
#endif
#ifndef SYS_FS_MAX_DRIVE
#define SYS_FS_MAX_DRIVE SYS_FS_MAX_FNAME   //Maximum length of a drive, volume name or mount point
#endif
#ifndef SYS_FS_MAX_EXT
#define SYS_FS_MAX_EXT   4   //Maximum length of extension component (including '.')
#endif
#ifndef SYS_FS_MAX_PATH
#define SYS_FS_MAX_PATH 256  //Maximum length of full path (components above not to exceed)
#endif
#ifndef SYS_FS_MAX_DESCRIPTORS
#define SYS_FS_MAX_DESCRIPTORS 1000 // Per file system
#endif

#define SYS_FS_NVM_VOL          "/dev/nvma1"
#define SYS_FS_MPFS_STRING     "MPFS2"
#define LOCAL_WEBSITE_PATH_FS        "/mnt/mchpSite1"
#define LOCAL_WEBSITE_PATH           "/mnt/mchpSite1/"
#define WEBSITE_PATH_LENGTH         15
#define SYS_FS_DRIVE           "FLASH"

#endif	// __SYS_FS_CONFIG_H