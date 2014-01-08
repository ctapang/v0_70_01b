/*******************************************************************************
  File System System-Library Interface Implementation.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_fs_media_manager.c

  Summary:
    This file contains implementation of SYS FS Media Manager functions. 

  Description:
    This file contains implementation of SYS FS Media Manager functions. 
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

#include "system/fs/src/sys_fs_media_manager_local.h"
#include "system/fs/src/sys_fs_local.h"

// *****************************************************************************
/* Media object

  Summary:
    Defines the media object for each media that should be controlled by media manager

  Description:
    This data type defines the media objects that are available on
    the part.
  Remarks:
    None
*/
SYS_FS_MEDIA gSYSFSMediaObject[SYS_FS_MEDIA_NUMBER];

// *****************************************************************************
/* Volume object

  Summary:
    Defines the volume object for each media that should be controlled by media manager

  Description:
     Each partition of the media is assigned as a volume using the volume object.

  Remarks:
    None
*/
SYS_FS_VOLUME gSYSFSVolumeObject[SYS_FS_VOLUME_NUMBER];


// *****************************************************************************
/* Volume to Partition translation

  Summary:
    Defines the volume to partition translation table, used by FAT FS.

  Description:
 * The following array was added to enable the "multipartition"
 * feature of FAT FS. This array is already declared in ff.h and
 * the intention was to make as little change on ff.h. Also, type of this
 * array is non-standard since, it is defined in ff.c. The implementation
 * is kept unchanged to maintain compatibility with future releases of FAT FS

  Remarks:
    None
*/
PARTITION VolToPart[SYS_FS_VOLUME_NUMBER];

/* Following structure holds the variables for media manager, including the task states */
SYS_FS_MEDIA_MANAGER_TASK_OPERATION gSYSFSMediaManagerVar =
{
    0,
    (SYS_FS_MEDIA *)0,
    SYS_FS_MEDIA_MANAGER_TASK_STATE_SELECT_NEW_REGISTERED_DISK,
    {0}
};

/*****************************************************************************
  Function:
    SYS_FS_MEDIA_HANDLE SYS_FS_MEDIA_MANAGER_Register
    (
            SYS_MODULE_OBJ	obj,
            SYS_MODULE_INDEX index,
            const SYS_FS_MEDIA_FUNCTIONS * mediaFunctions,
            SYS_FS_MEDIA_TYPE mediaType
    )

  Description:
    Function called by a media to register itself to the media manager. For static
 * media, (like NVM or SD card), this "register function" is called during static
 * initialization. For dynamic media (like MSD), this register function is called
 * dynamically, once the MSD media is connected.

  Precondition:
    None

  Parameters:
    obj             - driver object (of type SYS_MODULE_OBJ,
                     value returned when driver is initialized)
    index           - driver index (of type SYS_MODULE_INDEX,
                     value passed during driver initilization and opening)
    mediaFunctions  - List of driver functions
    mediaType       - Type of media
 *
  Returns:
    handle          - Of type SYS_FS_MEDIA_HANDLE
*/

SYS_FS_MEDIA_HANDLE SYS_FS_MEDIA_MANAGER_Register
(
	SYS_MODULE_OBJ	obj,    // Used to run the "Tasks" routine
        SYS_MODULE_INDEX index, // Used to open the driver
	const SYS_FS_MEDIA_FUNCTIONS * mediaFunctions,
	SYS_FS_MEDIA_TYPE mediaType // To know if NVM, SD card or MSD etc..
)
{
    int diskIndex;
    SYS_FS_MEDIA *disk;
    SYS_FS_MEDIA *findDisk;

    // Start with 0th disk and find a disk which is available (not in use)
    for(diskIndex = 0; diskIndex < SYS_FS_MEDIA_NUMBER; diskIndex++)
    {
        disk = &gSYSFSMediaObject[diskIndex];
        if(disk->inUse != true) // not in use, hence this is available
            break;
    }

    if(diskIndex >= SYS_FS_MEDIA_NUMBER)
    {
        SYS_ASSERT(false, "Invalid Disk Number");
        return SYS_FS_MEDIA_HANDLE_INVALID;
    }


    disk->inUse = true;
    disk->mediaDriverFunctions = mediaFunctions;
    disk->mediaDriverObject = obj;
    disk->index = index;
    disk->mediaDriverClientHandle = DRV_HANDLE_INVALID;  // Initially, INVALID
    disk->mediaState = SYS_FS_MEDIA_STATE_REGISTERED;
    disk->mediaType = mediaType;
    disk->numberOfPartitions = 0;
    disk->volumeCounter = 0;

    /* For every new media connected, increment media counter and make volume as "1" */

    switch(disk->mediaType)
    {
        case SYS_FS_MEDIA_TYPE_NVM:
            disk->mediaCounter = 'a';
            /* Now, traverse through other media and find if any one uses 'a' */
            for(diskIndex = 0; diskIndex < SYS_FS_MEDIA_NUMBER; diskIndex++)
            {
                findDisk = &gSYSFSMediaObject[diskIndex];
                if(disk != findDisk)
                {
                    if((findDisk->inUse == true) && (findDisk->mediaType == SYS_FS_MEDIA_TYPE_NVM))
                    {
                        if(disk->mediaCounter == findDisk->mediaCounter)
                        {
                            disk->mediaCounter++;
                        }
                    }
                }
            }

             break;
        case SYS_FS_MEDIA_TYPE_MSD:
            disk->mediaCounter = 'a';
            /* Now, traverse through other media and find if any one uses 'a' */
            for(diskIndex = 0; diskIndex < SYS_FS_MEDIA_NUMBER; diskIndex++)
            {
                findDisk = &gSYSFSMediaObject[diskIndex];
                if(disk != findDisk)
                {
                    if((findDisk->inUse == true) && (findDisk->mediaType == SYS_FS_MEDIA_TYPE_MSD))
                    {
                        if(disk->mediaCounter == findDisk->mediaCounter)
                        {
                            disk->mediaCounter++;
                        }
                    }
                }
            }
            break;
        case SYS_FS_MEDIA_TYPE_SD_CARD:
            disk->mediaCounter = 'a';
            /* Now, traverse through other media and find if any one uses 'a' */
            for(diskIndex = 0; diskIndex < SYS_FS_MEDIA_NUMBER; diskIndex++)
            {
                findDisk = &gSYSFSMediaObject[diskIndex];
                if(disk != findDisk)
                {
                    if((findDisk->inUse == true) && (findDisk->mediaType == SYS_FS_MEDIA_TYPE_SD_CARD))
                    {
                        if(disk->mediaCounter == findDisk->mediaCounter)
                        {
                            disk->mediaCounter++;
                        }
                    }
                }
            }
            break;
        case SYS_FS_MEDIA_TYPE_RAM:
            disk->mediaCounter = 'a';
            /* Now, traverse through other media and find if any one uses 'a' */
            for(diskIndex = 0; diskIndex < SYS_FS_MEDIA_NUMBER; diskIndex++)
            {
                findDisk = &gSYSFSMediaObject[diskIndex];
                if(disk != findDisk)
                {
                    if((findDisk->inUse == true) && (findDisk->mediaType == SYS_FS_MEDIA_TYPE_RAM))
                    {
                        if(disk->mediaCounter == findDisk->mediaCounter)
                        {
                            disk->mediaCounter++;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    return (SYS_FS_MEDIA_HANDLE)disk;
}

/*****************************************************************************
  Function:
    void SYS_FS_MEDIA_MANAGER_DeRegister
    (
            SYS_FS_MEDIA_HANDLE	handle
    )

  Description:
    Function called by a media to deregister itself to the media manager. For static
 * media, (like NVM or SD card), this "deregister function" is never called, since
 * static media never gets deregistered once they are initialized.
 * For dynamic media (like MSD), this register function is called
 * dynamically, once the MSD media is connected.

  Precondition:
    None

  Parameters:
    handle          - handle of type SYS_FS_MEDIA_HANDLE received when the media
                      was registered
*
  Returns:
    None
*/
void SYS_FS_MEDIA_MANAGER_DeRegister
(
	SYS_FS_MEDIA_HANDLE	handle
)
{
    volatile int volIndex;
    volatile SYS_FS_VOLUME *vol;
    SYS_FS_MEDIA *disk = (SYS_FS_MEDIA *)handle;

    if(handle == SYS_FS_MEDIA_HANDLE_INVALID)
        return;

    disk->inUse = false;
    disk->numberOfPartitions = 0;
    disk->mediaState = SYS_FS_MEDIA_STATE_DETACHED;
    disk->mediaCounter = 0;
    disk->volumeCounter = 0;

    /* If the media is detached, clear all paramaters in the "volume" object */
    for(volIndex = 0; volIndex < SYS_FS_VOLUME_NUMBER; volIndex++)
    {
        vol = &gSYSFSVolumeObject[volIndex];
        if((vol->inUse == true) && (vol->obj == disk))
        {
            vol->inUse = false;
            vol->devName[0] = 0;
            vol->devName[1] = 0;
            vol->devName[2] = 0;
            vol->devName[3] = 0;
            vol->devName[4] = 0;
        }
    }

}

/*****************************************************************************
 * Function:
 * void SYS_FS_MEDIA_MANAGER_Tasks(void)
 *
 * Description:
 *   Task function of media manager. This task must be called repeteadly from the
 * main loop.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   None.
 *
 * Returns:
 *   None.
*/

void SYS_FS_MEDIA_MANAGER_Tasks ( void )
{
    volatile int volIndex;
    volatile SYS_FS_VOLUME *vol;
    volatile unsigned int tempNumberOfPartitions;

    switch(gSYSFSMediaManagerVar.taskState)
    {
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_SELECT_NEW_REGISTERED_DISK:
            gSYSFSMediaManagerVar.disk = &gSYSFSMediaObject[gSYSFSMediaManagerVar.diskIndex];
            gSYSFSMediaManagerVar.diskIndex++;
            /* Take a disk which is already in use */
            if(gSYSFSMediaManagerVar.disk->inUse == true)
            {
                /* If the disk is one which is just "registered" newly */
                if(gSYSFSMediaManagerVar.disk->mediaState == SYS_FS_MEDIA_STATE_REGISTERED)
                {
                    gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_OPEN_MEDIA;
                }
                else if(gSYSFSMediaManagerVar.disk->mediaState == SYS_FS_MEDIA_STATE_ANALYZED)
                /* If it an existing disk, which is already analyzed, check if it is still attached */
                {
                    if(gSYSFSMediaManagerVar.disk->mediaDriverFunctions->mediaStatusGet(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle) != SYS_FS_MEDIA_ATTACHED)
                    {
                        /* Do not call close. For SD card, closing SD card driver will prevent getting media status */
                        //gSYSFSMediaManagerVar.disk->mediaDriverFunctions->close(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle);

                        /* If the media is detached, clear all paramaters in the "volume" object */
                        for(volIndex = 0; volIndex < SYS_FS_VOLUME_NUMBER; volIndex++)
                        {
                            vol = &gSYSFSVolumeObject[volIndex];
                            if((vol->inUse == true) && (vol->obj == gSYSFSMediaManagerVar.disk))
                            {
                                vol->inUse = false;
                                vol->devName[0] = 0;
                                vol->devName[1] = 0;
                                vol->devName[2] = 0;
                                vol->devName[3] = 0;
                                vol->devName[4] = 0;
                            }
                        }
                        gSYSFSMediaManagerVar.disk->volumeCounter = 0;

                        gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_DETACHED;
                        gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_DETACHED;
                    }
                }
                else if(gSYSFSMediaManagerVar.disk->mediaState == SYS_FS_MEDIA_STATE_DETACHED)
                /* Check if the media is attached again*/
                {
                    if(gSYSFSMediaManagerVar.disk->mediaDriverFunctions->mediaStatusGet(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle) == SYS_FS_MEDIA_ATTACHED)
                    {
                        gSYSFSMediaManagerVar.disk->mediaStatus = SYS_FS_MEDIA_ATTACHED;
                        gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_ATTACHED;
                        gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ATTACHED;
                    }
                    else /* If media is still detached */
                    {
                        gSYSFSMediaManagerVar.disk->mediaStatus = SYS_FS_MEDIA_DETACHED;
                        gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_DETACHED;
                        gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_DETACHED;
                    }
                }
            }
            if(gSYSFSMediaManagerVar.diskIndex >= SYS_FS_MEDIA_NUMBER)
                gSYSFSMediaManagerVar.diskIndex = 0;
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_DETACHED:
            gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_SELECT_NEW_REGISTERED_DISK;
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_OPEN_MEDIA:
            /* Open the driver of the media */
            gSYSFSMediaManagerVar.disk->mediaDriverClientHandle = gSYSFSMediaManagerVar.disk->mediaDriverFunctions->open(gSYSFSMediaManagerVar.disk->index, 0);
            gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_OPENING_MEDIA;
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_OPENING_MEDIA:
            if(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle != DRV_HANDLE_INVALID)
            {
                gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_OPENED;
                gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_CHECK_ATTACHED_MEDIA;
            }
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_CHECK_ATTACHED_MEDIA:
            if(gSYSFSMediaManagerVar.disk->mediaDriverFunctions->mediaStatusGet(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle) == SYS_FS_MEDIA_ATTACHED)
            {
                gSYSFSMediaManagerVar.disk->mediaStatus = SYS_FS_MEDIA_ATTACHED;
                gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_ATTACHED;
                gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ATTACHED;
            }
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_ATTACHED:
            /* Ideally, we should be doing sectorSizeGet(). But that function is missing, so we read 0th sector */
            gSYSFSMediaManagerVar.disk->mediaBufferHandle = gSYSFSMediaManagerVar.disk->mediaDriverFunctions->sectorRead(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle,gSYSFSMediaManagerVar.buffer,0,1);
            if(gSYSFSMediaManagerVar.disk->mediaBufferHandle != SYS_FS_MEDIA_BUFFER_HANDLE_INVALID)
            {
                gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZING_FILE_SYSTEM;
            }
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZING_FILE_SYSTEM:
            if(gSYSFSMediaManagerVar.disk->mediaDriverFunctions->bufferStatusGet(gSYSFSMediaManagerVar.disk->mediaDriverClientHandle, gSYSFSMediaManagerVar.disk->mediaBufferHandle) == SYS_FS_MEDIA_BUFFER_COMPLETED)
            {
                if((gSYSFSMediaManagerVar.buffer[510] == 0x55) || (gSYSFSMediaManagerVar.buffer[511] == 0xAA))
                {
                    /* As per Jan Axelson book, chapter-7, page - 170 */
                    /* The partition table in the MBR sector has room
                     * for four 16-byte entries that each specify the sectors
                     * that belong to a partition. The table is in bytes 446
                     * through 509. An entry can begin at byte 446, 462, 478, or 494.*/

                    /* Debraj:
                     * 1st partition, total sectors = 461, 460, 459, 458
                     * 1st partition type = 450
                     * 1st partition, start sector number =  457, 456, 455, 454
                     *
                     * 2nd partition, total sectors = 477, 476, 475, 474
                     * 2nd partition type = 466
                     * 2nd partition, start sector number =  473, 472, 471, 470
                     *
                     * 3rd partition, total sectors = 493, 492, 491, 490
                     * 3rd partition type = 482
                     * 3rd partition, start sector number = 489, 488, 487, 486
                     *
                     * 4th partition, total sectors = 510, 509, 508, 507
                     * 4th partition type = 498
                     * 4th partition, start sector number = 506, 505, 504, 503
                     */

                    /* Determine total partitions in the media */
                    if(gSYSFSMediaManagerVar.buffer[450] != 0)    // 1st
                        gSYSFSMediaManagerVar.disk->numberOfPartitions++;
                    if(gSYSFSMediaManagerVar.buffer[466] != 0)    // 2nd
                        gSYSFSMediaManagerVar.disk->numberOfPartitions++;
                    if(gSYSFSMediaManagerVar.buffer[482] != 0)    // 3rd
                        gSYSFSMediaManagerVar.disk->numberOfPartitions++;
                    if(gSYSFSMediaManagerVar.buffer[498] != 0)    // 4th
                        gSYSFSMediaManagerVar.disk->numberOfPartitions++;

                    /* In case the media has many paritions, but the user wants
                     * to use only few, then ignore all the others */
                    //if(disk->numberOfPartitions > SYS_FS_VOLUME_NUMBER)
                    //    disk->numberOfPartitions = SYS_FS_VOLUME_NUMBER;

                    gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ALLOCATING_VOLUME;
                }
                else if ( ( gSYSFSMediaManagerVar.buffer[0] == 'M' ) && ( gSYSFSMediaManagerVar.buffer[1] == 'P' ) &&
                   ( gSYSFSMediaManagerVar.buffer[2] == 'F' ) && ( gSYSFSMediaManagerVar.buffer[3] == 'S' ) )
                {
                 /* No partitions in MPFS, hence, go to other state */
                    /* allocate a new volume to each partition */
                    gSYSFSMediaManagerVar.disk->numberOfPartitions = 1;
                    gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ALLOCATING_VOLUME;
                }
            }
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_ALLOCATING_VOLUME:

            tempNumberOfPartitions = 0;

            for(volIndex = 0; volIndex < SYS_FS_VOLUME_NUMBER; volIndex++)
            {
                vol = &gSYSFSVolumeObject[volIndex];
                if(vol->inUse != true) /* Found a free volume */
                {
                    switch(gSYSFSMediaManagerVar.disk->mediaType)
                    {
                        case SYS_FS_MEDIA_TYPE_SD_CARD:
                            vol->devName[0] = 'm';
                            vol->devName[1] = 'm';
                            vol->devName[2] = 'c';
                            vol->devName[3] = 'b';
                            vol->devName[4] = 'l';
                            vol->devName[5] = 'k';
                            vol->devName[6] = gSYSFSMediaManagerVar.disk->mediaCounter;
                            gSYSFSMediaManagerVar.disk->volumeCounter++;
                            vol->devName[7] =  gSYSFSMediaManagerVar.disk->volumeCounter + '0';

                            break;
                        case SYS_FS_MEDIA_TYPE_NVM:
                            vol->devName[0] = 'n';
                            vol->devName[1] = 'v';
                            vol->devName[2] = 'm';
                            vol->devName[3] = gSYSFSMediaManagerVar.disk->mediaCounter;
                            gSYSFSMediaManagerVar.disk->volumeCounter++;
                            vol->devName[4] =  gSYSFSMediaManagerVar.disk->volumeCounter + '0';

                            break;
                        case SYS_FS_MEDIA_TYPE_MSD:
                            vol->devName[0] = 's';
                            vol->devName[1] = 'd';
                            vol->devName[2] = gSYSFSMediaManagerVar.disk->mediaCounter;
                            gSYSFSMediaManagerVar.disk->volumeCounter++;
                            vol->devName[3] =  gSYSFSMediaManagerVar.disk->volumeCounter + '0';

                            break;
                        default:
                            break;
                    }
                    _SYS_FS_MEDIA_MANAGER_updateVolToPart( volIndex, (gSYSFSMediaManagerVar.disk->mediaCounter - 'a'), gSYSFSMediaManagerVar.disk->volumeCounter);
                    vol->inUse = true;
                    vol->obj = gSYSFSMediaManagerVar.disk;

                    if((gSYSFSMediaManagerVar.buffer[510] == 0x55) || (gSYSFSMediaManagerVar.buffer[511] == 0xAA))
                    {
                        switch(tempNumberOfPartitions)
                        {
                                case 0: /* 1st partition */
                                    vol->numberOfSector = ((gSYSFSMediaManagerVar.buffer[461] << 24) + (gSYSFSMediaManagerVar.buffer[460] << 16) + (gSYSFSMediaManagerVar.buffer[459] << 8) + gSYSFSMediaManagerVar.buffer[458]);
                                    vol->startSector = ((gSYSFSMediaManagerVar.buffer[457] << 24) + (gSYSFSMediaManagerVar.buffer[456] << 16) + (gSYSFSMediaManagerVar.buffer[455] << 8) + gSYSFSMediaManagerVar.buffer[454]);
                                    vol->fileSystemType = gSYSFSMediaManagerVar.buffer[450];
                                    break;
                                case 1: /* 2nd partition */
                                    vol->numberOfSector = ((gSYSFSMediaManagerVar.buffer[477] << 24) + (gSYSFSMediaManagerVar.buffer[476] << 16) + (gSYSFSMediaManagerVar.buffer[475] << 8) + gSYSFSMediaManagerVar.buffer[474]);
                                    vol->startSector = ((gSYSFSMediaManagerVar.buffer[473] << 24) + (gSYSFSMediaManagerVar.buffer[472] << 16) + (gSYSFSMediaManagerVar.buffer[471] << 8) + gSYSFSMediaManagerVar.buffer[470]);
                                    vol->fileSystemType = gSYSFSMediaManagerVar.buffer[466];
                                    break;
                                case 2: /* 3rd partition */
                                    vol->numberOfSector = ((gSYSFSMediaManagerVar.buffer[493] << 24) + (gSYSFSMediaManagerVar.buffer[492] << 16) + (gSYSFSMediaManagerVar.buffer[491] << 8) + gSYSFSMediaManagerVar.buffer[490]);
                                    vol->startSector = ((gSYSFSMediaManagerVar.buffer[489] << 24) + (gSYSFSMediaManagerVar.buffer[488] << 16) + (gSYSFSMediaManagerVar.buffer[487] << 8) + gSYSFSMediaManagerVar.buffer[486]);
                                    vol->fileSystemType = gSYSFSMediaManagerVar.buffer[482];
                                    break;
                                case 3: /* 4th partition */
                                    vol->numberOfSector = ((gSYSFSMediaManagerVar.buffer[510] << 24) + (gSYSFSMediaManagerVar.buffer[509] << 16) + (gSYSFSMediaManagerVar.buffer[508] << 8) + gSYSFSMediaManagerVar.buffer[507]);
                                    vol->startSector = ((gSYSFSMediaManagerVar.buffer[506] << 24) + (gSYSFSMediaManagerVar.buffer[505] << 16) + (gSYSFSMediaManagerVar.buffer[504] << 8) + gSYSFSMediaManagerVar.buffer[503]);
                                    vol->fileSystemType = gSYSFSMediaManagerVar.buffer[498];
                                    break;
                        }
                    }
                    else if ( ( gSYSFSMediaManagerVar.buffer[0] == 'M' ) && ( gSYSFSMediaManagerVar.buffer[1] == 'P' ) &&
                   ( gSYSFSMediaManagerVar.buffer[2] == 'F' ) && ( gSYSFSMediaManagerVar.buffer[3] == 'S' ) )
                    {
                            vol->numberOfSector = 0;
                            vol->startSector = 0;
                            vol->fileSystemType = 'M';  // inidcation for MPFS2
                    }
                    tempNumberOfPartitions++;
                    if(tempNumberOfPartitions == gSYSFSMediaManagerVar.disk->numberOfPartitions)
                        break;
                }
            }
            gSYSFSMediaManagerVar.disk->mediaState = SYS_FS_MEDIA_STATE_ANALYZED;
            gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZED;
            break;
        case SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZED:
            gSYSFSMediaManagerVar.taskState = SYS_FS_MEDIA_MANAGER_TASK_STATE_SELECT_NEW_REGISTERED_DISK;
            break;
        default:
            break;
    }
}

/*****************************************************************************
 * Function:
 * SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_SectorRead
 *   (
 *       uint16_t diskNo,
 *       uint8_t * dataBuffer,
 *       uint32_t sector,
 *       uint32_t noSectors
 *   )
 *
 * Description:
 * Function to read a sector of specified media (disk). This is the function in
 * media manager layer. This function in turn call the specific sector read function from
 * the list of function pointer of media driver.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   diskNo         - media number
 *   dataBuffer     - pointer to buffer where data to be placed after read
 *   sector         - Sector # which is to be read
 *   noSectors      - Number of sectors to read
 *
 * Returns:
 *   Buffer handle of type SYS_FS_MEDIA_BUFFER_HANDLE
*/

SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_SectorRead
(
    uint16_t diskNo,        /* SYS_FS_MEDIA disk no */
    uint8_t * dataBuffer,   /* Application buffer */
    uint32_t sector,        /* Start sector */
    uint32_t noSectors      /* Number of sectors to read */
)
{
	volatile SYS_FS_MEDIA *media;
	
	if(diskNo >= SYS_FS_VOLUME_NUMBER)
	{
		SYS_ASSERT(false, "Invalid Disk");
		return SYS_FS_MEDIA_BUFFER_HANDLE_INVALID;
	}	
	
	media = &gSYSFSMediaObject[diskNo];
        
        if(media->mediaDriverClientHandle == DRV_HANDLE_INVALID)
        {
            return SYS_FS_MEDIA_HANDLE_INVALID;
        }
                
        return(media->mediaDriverFunctions->sectorRead(media->mediaDriverClientHandle,
                                                          dataBuffer, sector, noSectors));
}

/*****************************************************************************
 * Function:
 * SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_Read
 * (
 *  uint16_t diskNo,
 *  uint8_t* destination,
 *  uint8_t * source,
 *  const unsigned int nBytes
 * )
 *
 * Description:
 * Function to data from a specific address of media. This function is intended to work with
 * NVM media only, which can have byte level adressing. For other media (like SD card),byte
 * addressing is not possible and hence this function will not work. Also, this function is
 * intended to work with MPFS2 file system only, which uses byte adressing.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   diskNo         - media number
 *   destination    - pointer to buffer where data to be placed after read
 *   source         - pointer from where data to be read
 *   nBytes         - Number of bytes to be read
 *
 * Returns:
 *   Buffer handle of type SYS_FS_MEDIA_BUFFER_HANDLE
*/

SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_Read
( uint16_t diskNo, uint8_t* destination, uint8_t * source, const unsigned int nBytes )
{
    SYS_FS_VOLUME * vol;

    if(diskNo >= SYS_FS_VOLUME_NUMBER)
    {
            SYS_ASSERT(false, "Invalid Disk");
            return SYS_FS_MEDIA_BUFFER_HANDLE_INVALID;
    }

    vol = &gSYSFSVolumeObject[diskNo];

    if(vol->obj->mediaDriverClientHandle == DRV_HANDLE_INVALID)
    {
        return SYS_FS_MEDIA_HANDLE_INVALID;
    }

    return(vol->obj->mediaDriverFunctions->Read(vol->obj->mediaDriverClientHandle,
                                                destination, source, nBytes));
}

/*****************************************************************************
 * Function:
 * uintptr_t SYS_FS_MEDIA_MANAGER_AddressGet
 * (
 *  uint16_t diskNo,
 * )
 *
 * Description:
 * Function to know the NVM memory address against a disk number. This function
 * is intended to work only with MPFS2, which does byte adressing and hence needs
 * memory address (not disk number).
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   diskNo         - media number
 *
 * Returns:
 *   memory address of type uintptr_t
*/

uintptr_t SYS_FS_MEDIA_MANAGER_AddressGet
(
	uint16_t	diskNo
)
{
    SYS_FS_VOLUME * vol;

    if(diskNo >= SYS_FS_VOLUME_NUMBER)
    {
            SYS_ASSERT(false, "Invalid Disk");
            return (uintptr_t)NULL;
    }

    vol = &gSYSFSVolumeObject[diskNo];

    return(vol->obj->mediaDriverFunctions->addressGet(vol->obj->mediaDriverClientHandle));
}

/*****************************************************************************
 * Function:
 * SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_SectorWrite
 *   (
 *       uint16_t diskNo,
 *       uint32_t sector,
 *       uint8_t * dataBuffer,
 *       uint32_t noSectors
 *   )
 *
 * Description:
 * Function to write to a sector of specified media (disk). This is the function in
 * media manager layer. This function in turn call the specific sector write function from
 * the list of function pointer of media driver.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   diskNo         - media number
 *   sector         - Sector # to which data to be written
 *   dataBuffer     - pointer to buffer which holds the data to be written
 *   noSectors      - Number of sectors to be written
 *
 * Returns:
 *   Buffer handle of type SYS_FS_MEDIA_BUFFER_HANDLE
*/
SYS_FS_MEDIA_BUFFER_HANDLE SYS_FS_MEDIA_MANAGER_SectorWrite
(
    uint16_t diskNo,        /* SYS_FS_MEDIA disk no */
    uint32_t sector,        /* Start sector */
    uint8_t * dataBuffer,   /* Application buffer */
    uint32_t noSectors      /* Number of sectors to write */
)
{
	volatile SYS_FS_MEDIA *media;
	
	if(diskNo >= SYS_FS_VOLUME_NUMBER)
	{
		SYS_ASSERT(false, "Invalid Disk");
		return SYS_FS_MEDIA_BUFFER_HANDLE_INVALID;
	}	
	
	media = &gSYSFSMediaObject[diskNo];

        if(media->mediaDriverClientHandle == DRV_HANDLE_INVALID)
        {
            return SYS_FS_MEDIA_HANDLE_INVALID;
        }
                
        return(media->mediaDriverFunctions->sectorWrite(media->mediaDriverClientHandle,
                                                          sector, dataBuffer, noSectors));

}

/*****************************************************************************
 * Function:
 * SYS_FS_MEDIA_BUFFER_STATUS SYS_FS_MEDIA_MANAGER_BufferStatusGet
 *   (
 *       uint16_t diskNo,
 *       SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle
 *   )
 *
 * Description:
 * Function to know the buffer status. The sector read and sector write are
 * non blocking functions. Hence, this interface is provided, where the code
 * should periodically poll for the buffer status. If status is completed,
 * the read/ write operation is considered to be complete.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   diskNo         - media number
 *   bufferHandle   - the buffer handle which was obtained during sector read/ write
 *
 * Returns:
 *   Buffer status of type SYS_FS_MEDIA_BUFFER_STATUS
*/
SYS_FS_MEDIA_BUFFER_STATUS SYS_FS_MEDIA_MANAGER_BufferStatusGet
(
    uint16_t     diskNo,
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle
)
{
        volatile SYS_FS_MEDIA *media;
	
	if(diskNo >= SYS_FS_VOLUME_NUMBER)
	{
		SYS_ASSERT(false, "Invalid Disk");
		return SYS_FS_MEDIA_BUFFER_HANDLE_INVALID;
	}	
	
	media = &gSYSFSMediaObject[diskNo];

        if(media->mediaDriverClientHandle == DRV_HANDLE_INVALID)
        {
            return SYS_FS_MEDIA_BUFFER_UNKNOWN;
        }

        return(media->mediaDriverFunctions->bufferStatusGet(media->mediaDriverClientHandle,
                                                                bufferHandle));
}

/*****************************************************************************
 * Function:
 * SYS_FS_MEDIA_STATUS SYS_FS_MEDIA_MANAGER_MediaStatusGet
 *   (
 *       const char *devName
 *   )
 *
 * Description:
 * Function to know the media status. This function is used by higher layers
 * (sys_fs layer) to know the status of the media, whether, the media is attached
 * or detached.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   devName        - string name of the media
 *
 * Returns:
 *   Media status of type SYS_FS_MEDIA_STATUS
*/
SYS_FS_MEDIA_STATUS SYS_FS_MEDIA_MANAGER_MediaStatusGet( const char *devName )
{
	SYS_FS_VOLUME * vol;
        const char *Temp;
        char *Temp1;
        int volIndex;

        // Start with 0th disk and find a disk which is available (not in use)
        for(volIndex = 0; volIndex < SYS_FS_VOLUME_NUMBER; volIndex++)
        {
            vol = &gSYSFSVolumeObject[volIndex];
            if(vol->inUse == true)
            {
                // Find the element from "gSYSFSVolumeObject" which has matching "devName"
                // I did not use "strcmp" as not sure if its implementation is re-entrant or not
                Temp = (devName + 5);   // ignore the first 5 chars --> "/dev/"
                Temp1 = vol->devName;
                while(*Temp != '\0')
                {
                    // Let's compare each chars. If they do not match, break and take the next
                    // string from element of "gSYSFSMediaDiskObject"
                    if(*(Temp) != *(Temp1))
                    {
                        break;
                    }
                    else
                    {
                        Temp++;
                        Temp1++;
                    }
                }
                // once the top "while" loop ends (either due to complete match of string or
                // due to unmatched string), code will come here.
                // To check if the code came here due to complete match of string,
                // check the "Temp". If "Temp" is NULL, then "break" the for loop
                // as well, as we have got the "vol" with required name
                if(*Temp == '\0')
                    break;
            }
        }

        if(volIndex >= SYS_FS_VOLUME_NUMBER)
        {
            //SYS_ASSERT(false, "Invalid Volume");
            return SYS_FS_MEDIA_DETACHED;
        }

        /* Check if the media is opened and a valid handle is available or not */
        if(vol->obj->mediaDriverClientHandle == DRV_HANDLE_INVALID)
        {
            return SYS_FS_MEDIA_DETACHED;
        }

        return (vol->obj->mediaDriverFunctions->mediaStatusGet(
                                                    vol->obj->mediaDriverClientHandle));
}	

/*****************************************************************************
 * Function:
 * bool SYS_FS_MEDIA_MANAGER_VolumePropertyGet
 *   (
 *       const char *devName
 *       SYS_FS_VOLUME_PROPERTY *str
 *   )
 *
 * Description:
 * Function to know the property of the volume. This function is used by higher layers
 * (sys_fs layer) to know the property of the volume as specified in the
 * SYS_FS_VOLUME_PROPERTY structure.
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   devName        - string name of the media
 *   *str           - pointer to structure of type SYS_FS_VOLUME_PROPERTY
 *
 * Returns:
 *   true or false
*/

bool SYS_FS_MEDIA_MANAGER_VolumePropertyGet( const char *devName, SYS_FS_VOLUME_PROPERTY *str)
{
	SYS_FS_VOLUME * vol;
        const char *Temp;
        char *Temp1;
        int volIndex;

        // Start with 0th disk and find a disk which is available (not in use)
        for(volIndex = 0; volIndex < SYS_FS_VOLUME_NUMBER; volIndex++)
        {
            vol = &gSYSFSVolumeObject[volIndex];
            if(vol->inUse == true)
            {
                // Find the element from "gSYSFSVolumeObject" which has matching "devName"
                // I did not use "strcmp" as not sure if its implementation is re-entrant or not
                Temp = (devName + 5);   // ignore the first 5 chars --> "/dev/"
                Temp1 = vol->devName;
                while(*Temp != '\0')
                {
                    // Let's compare each chars. If they do not match, break and take the next
                    // string from element of "gSYSFSMediaDiskObject"
                    if(*(Temp) != *(Temp1))
                    {
                        break;
                    }
                    else
                    {
                        Temp++;
                        Temp1++;
                    }
                }
                // once the top "while" loop ends (either due to complete match of string or
                // due to unmatched string), code will come here.
                // To check if the code came here due to complete match of string,
                // check the "Temp". If "Temp" is NULL, then "break" the for loop
                // as well, as we have got the "vol" with required name
                if(*Temp == '\0')
                    break;
            }
        }

        if(volIndex >= SYS_FS_VOLUME_NUMBER)
        {
            return false;
        }

        /* Check if the media is opened and a valid handle is available or not */
        if(vol->obj->mediaDriverClientHandle == DRV_HANDLE_INVALID)
        {
            return false;
        }

        if((vol->fileSystemType == 0x01) ||         // FAT12
                (vol->fileSystemType == 0x04) ||    // FAT16
                (vol->fileSystemType == 0x05) ||    // Extended partitino
                (vol->fileSystemType == 0x06) ||    // FAT16
                (vol->fileSystemType == 0x0B) ||    // FAT32
                (vol->fileSystemType == 0x0C) ||    // FAT32
                (vol->fileSystemType == 0x0E) ||    // FAT16
                (vol->fileSystemType == 0x0F))      // FAT16
                {
                    str->fsType = FAT;
                }
        else if(vol->fileSystemType == 'M')
        {
            str->fsType = MPFS2;
        }

        str->volNumber = volIndex;

	return(true);
}

/*****************************************************************************
 * Function:
 * void _SYS_FS_MEDIA_MANAGER_updateVolToPart(uint8_t volNumber, uint8_t pd, uint8_t pt)
 *
 * Description:
 * This function is present to enable the multipartition operation
 * of FAT FS. FAT FS uses the structure VolToPart to know the physical
 * drive media number and partition number of that media, using this
 * structure. This function is used to populate the structure.
 * REFER TO MORE EXPLANATION on SYS_fs_media_manager_local.h
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   volNumber      - volume number
 *   pd             - physical drive number (media number)
 *   pt             - partition number from that media
 *
 * Returns:
 *   none.
*/

void _SYS_FS_MEDIA_MANAGER_updateVolToPart(uint8_t volNumber, uint8_t pd, uint8_t pt)
{
    /* Update the "VolToPart" table for multipartition support on FAT FS */
    /* pd = Physical drive, starting from "zero". This is to be compatible with FAT FS code */
    VolToPart[volNumber].pd = pd;
    /* pt = partition, starting from "one". This is to be compatible with FAT FS code */
    VolToPart[volNumber].pt = pt;
}

/*****************************************************************************
 * Function:
 * DRESULT disk_read
 *   (
 *       uint8_t pdrv,
 *       uint8_t *buff,
 *       uint32_t sector,
 *       uint8_t count
 *   )
 *
 * Description:
 * Function to read a sector of specified media (disk). This is the function
 * called from ff.c. This function is block untill the read is complete.
 * Since this function is called by ff.c, the name of function, parameter passed
 * and return types are not changed. This is to avoid compatibility issues if we
 * use future releases of ff.c
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   pdrv         - media number
 *   buff         - pointer to buffer where data to be placed after read
 *   sector       - Sector # which is to be read
 *   count        - Number of sectors to read
 *
 * Returns:
 *   DRESULT
*/

DRESULT disk_read (
        uint8_t pdrv,		/* Physical drive nmuber (0..) */
        uint8_t *buff,		/* Data buffer to store read data */
        uint32_t sector,	/* Sector address (LBA) */
        uint8_t count		/* Number of sectors to read (1..128) */
        )
{
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle;
    volatile SYS_FS_MEDIA *media;

    bufferHandle = SYS_FS_MEDIA_MANAGER_SectorRead(pdrv /* DISK 0 */ ,
            buff /* Destination Sector*/,
            sector,
            count /* Number of Sectors */);

    if(bufferHandle == SYS_FS_MEDIA_BUFFER_HANDLE_INVALID)
    {
        return RES_PARERR;
    }

    media = &gSYSFSMediaObject[pdrv];

    while(SYS_FS_MEDIA_MANAGER_BufferStatusGet(pdrv, bufferHandle) !=
            SYS_FS_MEDIA_BUFFER_COMPLETED)
    {
        if(media->mediaDriverFunctions->tasks != NULL)
            media->mediaDriverFunctions->tasks(media->mediaDriverObject);
    }

    return RES_OK;
}



/*****************************************************************************
 * Function:
 * DRESULT disk_write
 *   (
 *       uint8_t pdrv,
 *       uint8_t *buff,
 *       uint32_t sector,
 *       uint8_t count
 *   )
 *
 * Description:
 * Function to write to a sector of specified media (disk). This is the function
 * called from ff.c. This function is block untill the write is complete.
 * Since this function is called by ff.c, the name of function, parameter passed
 * and return types are not changed. This is to avoid compatibility issues if we
 * use future releases of ff.c
 *
 * Precondition:
 *   None
 *
 * Parameters:
 *   pdrv         - media number
 *   buff         - pointer to buffer which holds the data to write
 *   sector       - Sector # where data to be written
 *   count        - Number of sectors to write
 *
 * Returns:
 *   DRESULT
*/

#if _USE_WRITE
DRESULT disk_write (
        uint8_t pdrv,			/* Physical drive nmuber (0..) */
        const uint8_t *buff,	/* Data to be written */
        uint32_t sector,		/* Sector address (LBA) */
        uint8_t count			/* Number of sectors to write (1..128) */
        )
{
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle;
    volatile SYS_FS_MEDIA *media;

    bufferHandle = SYS_FS_MEDIA_MANAGER_SectorWrite(pdrv /* DISK 0 */ ,
            sector /* Destination Sector*/,
            (uint8_t *)buff,
            count /* Number of Sectors */);

    if(bufferHandle == SYS_FS_MEDIA_BUFFER_HANDLE_INVALID)
    {
        return RES_PARERR;
    }

    media = &gSYSFSMediaObject[pdrv];

    while(SYS_FS_MEDIA_MANAGER_BufferStatusGet(pdrv, bufferHandle) !=
            SYS_FS_MEDIA_BUFFER_COMPLETED)
    {
        if(media->mediaDriverFunctions->tasks != NULL)
            media->mediaDriverFunctions->tasks(media->mediaDriverObject);
    }

    return RES_OK;
}
#endif