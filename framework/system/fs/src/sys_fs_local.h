/*******************************************************************************
  File System System-Library Local Types and Defintions

  Company:
    Microchip Technology Inc.

  File Name:
    sys_fs_local.h

  Summary:
    Contains local types and defintions required by the SYS_FS functions.

  Description:
    This file contains local types and defintions required by the SYS_FS 
    functions. These types are internal to the SYS_FS function implementation
    and should not be used directly by the application. 
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is fsegrated fso your product or third party product
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

#ifndef _SYS_FS_PRIVATE_H
#define _SYS_FS_PRIVATE_H

#include "system_config.h"
#include "system/system.h"
#include "system/fs/sys_fs.h"
#include "system/fs/fat_fs/src/file_system/ff.h"
#include "system/fs/sys_fs_media_manager.h"

// *****************************************************************************
/* Mount point

  Summary:
    Defines the mount point for each volume.

  Description:
    This structure defines the mount point that is utilized when a volume is
 * mounted by application code. This mount point is one per volume mounted.

  Remarks:
    None.
*/
typedef struct
{
    /* If the mount point is in use or is it free */
    uint32_t inUse;
    /* Type of native file system implemented on the volume mounted */
    SYS_FS_FILE_SYSTEM_TYPE fsType;
    /* List of function pointers associated with the native file system */
    const SYS_FS_FUNCTIONS * fsFunctions;
    /* Mount name. The format for mount name should follow: "/mnt/myDrive1" */
    const char *mountName;
    /* Volume number */
    int diskNumber;
}
SYS_FS_MOUNT_POINT;

// *****************************************************************************
/* File Object

  Summary:
    Defines the file object for each file opened.

  Description:
    This structure defines the file object which is allocated when a file is
 * opened by application code.

  Remarks:
    None.
*/
typedef struct
{
    /* If the file object is in use or is it free */
    bool                inUse;
    /* pointer to the mount point associated with the volume from where file
       is being opened */
    SYS_FS_MOUNT_POINT  *mountPoint;
    /* File object as obtained from the native file system */
    uintptr_t            nativeFSFileObj;
    /* Name of file is stored in a buffer for future use */
    uint8_t fileName[FAT_FS_MAX_LFN];

}SYS_FS_OBJ;



#endif // _SYS_FS_PRIVATE_H

