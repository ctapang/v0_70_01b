/*******************************************************************************
  File System System-Library Interface Implementation.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_fs.c

  Summary:
    This file contains implementation of SYS_FS functions. 

  Description:
    This file contains implementation of SYS_FS functions. 
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


#include "system/fs/src/sys_fs_local.h"
#include "system/fs/sys_fs_media_manager.h"

// *****************************************************************************
/* Registration table for each native file system

  Summary:
    Defines the registration table for each native file system.

  Description:
    Defines the registration table for each native file system.

  Remarks:
    None
*/
SYS_FS_REGISTRATION_TABLE gSYSFSObj[ SYS_FS_MAX_FILE_SYSTEM_TYPE ];

// *****************************************************************************
/* Mount point

  Summary:
    Defines the mount point required for mounting each volume.

  Description:
    Defines the mount point required for mounting each volume.

  Remarks:
    None
*/
SYS_FS_MOUNT_POINT gSYSFSMountPoint[SYS_FS_VOLUME_NUMBER];

// *****************************************************************************
/* File object

  Summary:
    Defines the File object for each file opened.

  Description:
    Defines the File object for each file opened on the system.

  Remarks:
    None
*/
SYS_FS_OBJ gSYSFSFileObj[SYS_FS_MAX_FILES];

/* Variable to hold the error value */
SYS_FS_ERROR errorValue;

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Initialize(const void* initData)

    Summary:
        Initializes the Abstration Layer

    Description:
        Initializes the abstraction Layer and sets up the necessary parameters

    Precondition:
        This is the first function to be called during initialization of SYS FS.
		Calling other functions from SYS FS without initializing the SYS FS will
		cause un-predictable behavior.

    Parameters:
        initData	-	The Set of initialization parameters

    Returns:
        If Success: SYS_FS_RES_SUCCESS
        If Failure: SYS_FS_RES_FAILURE
            Sets error code which can be retrieved with SYS_FS_Error

***************************************************************************/
SYS_FS_RESULT SYS_FS_Initialize(const void* initData)
{
    SYS_FS_REGISTRATION_TABLE *inData = ( SYS_FS_REGISTRATION_TABLE *)initData;
    int index;

    for( index = 0; index < SYS_FS_MAX_FILE_SYSTEM_TYPE; index++ )
    {
        gSYSFSObj[index].nativeFileSystemType = inData->nativeFileSystemType;
        gSYSFSObj[index].nativeFileSystemFunctions = inData->nativeFileSystemFunctions;
        inData++;
    }

    return SYS_FS_RES_SUCCESS;
}

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Mount(const char *devName, const char *mountName,
	SYS_FS_FILE_SYSTEM_TYPE filesystemtype, unsigned long mountflags, const void *data);

    Summary:
        Mount filesystems

    Description:
        Attaches the filesystem specified by source to a specified media.

    Precondition:
        The "devName" for the media has to be known. The convention that is
		followed in Harmony file system is: -

		For NVM			- "nvm"<media number><volume number>
		For SD card		- "mmcblk"<media number><volume number>
		For MSD			- "sd"<media number><volume number>

		<media number> 	- a, b, c... depending upon number of media of certain type
						  connected.
	    <volume number>	- 1, 2, 3... depending upon number of partitions in that
						  media.

    Parameters:
        devName 		- The device name (name of media) which needs to be mounted
        mountName 		- Mount name for the device to be mounted
        filesystemtype 	- native file system type
        mountflags 		- mounting control flags. This parameter is kept for future
						  expansion. Hence, always pass zero.
        data 			- The data argument is interpreted by the different file systems.
					      This parameter is kept for future expansion. Hence, always
						  pass NULL.

    Returns:
        If Success: SYS_FS_RES_SUCCESS
        If Failure: SYS_FS_RES_FAILURE
            Sets error code which can be retrieved with SYS_FS_Error
***************************************************************************/
SYS_FS_RESULT SYS_FS_Mount
(
    const char *devName,
    const char *mountName,
    SYS_FS_FILE_SYSTEM_TYPE filesystemtype,
    unsigned long mountflags,
    const void *data
 )
{	
    int fileStatus;
    SYS_FS_MOUNT_POINT *disk;
    int mountPoint;
    SYS_FS_VOLUME_PROPERTY volProperty;
    int index;

    /* First check if the media is attached or not */
    if(SYS_FS_MEDIA_MANAGER_MediaStatusGet(devName) !=
            SYS_FS_MEDIA_ATTACHED)
    {
        errorValue = SYS_FS_ERROR_NOT_READY;
        /* The media name specified is not attached */
        return SYS_FS_RES_FAILURE;
    }
    // Start with 0th disk and find a disk which is available (not in use)
    for(mountPoint = 0; mountPoint < SYS_FS_VOLUME_NUMBER; mountPoint++)
    {
        disk = &gSYSFSMountPoint[mountPoint];
        if(disk->inUse != true) // not in use, hence this is available
            break;
    }

    if(mountPoint >= SYS_FS_VOLUME_NUMBER)
    {
        SYS_ASSERT(false, "Invalid Disk");
        errorValue = SYS_FS_ERROR_NOT_ENOUGH_FREE_VOLUME;
        return SYS_FS_RES_FAILURE;
    }

    /* Verify if the requested file system is supported by SYS_FS */
    for( index = 0; index < SYS_FS_MAX_FILE_SYSTEM_TYPE; index++ )
    {
        if(gSYSFSObj[index].nativeFileSystemType == filesystemtype)
            break;  /* Now, index, holds the element number for the requested file system */
    }

    /* If the requested file system type is not supported by SYS_FS */
    if(index >= SYS_FS_MAX_FILE_SYSTEM_TYPE)
    {
        errorValue = SYS_FS_ERROR_FS_NOT_SUPPORTED;
        return SYS_FS_RES_FAILURE;
    }

    switch(filesystemtype)
    {
        case FAT:            
             if(SYS_FS_MEDIA_MANAGER_VolumePropertyGet(devName, &volProperty) == false)
             {
                 errorValue = SYS_FS_ERROR_DISK_ERR;
                 return SYS_FS_RES_FAILURE;
             }

             if(volProperty.fsType != FAT)
             {
                 errorValue = SYS_FS_ERROR_FS_NOT_MATCH_WITH_VOLUME;
                 return SYS_FS_RES_FAILURE;
             }

            if(disk->inUse == 0)
            {
                disk->inUse = 1;
                disk->fsType = FAT;
                disk->fsFunctions = gSYSFSObj[index].nativeFileSystemFunctions;
                disk->mountName = (mountName + 5);  // Save only mountName. Do not save "/mnt/"
                disk->diskNumber = volProperty.volNumber;
            }
            break;
        case MPFS2:
             if(SYS_FS_MEDIA_MANAGER_VolumePropertyGet(devName, &volProperty) == false)
             {
                 errorValue = SYS_FS_ERROR_DISK_ERR;
                 return SYS_FS_RES_FAILURE;
             }

             if(volProperty.fsType != MPFS2)
             {
                 errorValue = SYS_FS_ERROR_FS_NOT_MATCH_WITH_VOLUME;
                 return SYS_FS_RES_FAILURE;
             }

            if ( disk->inUse == 0 )
            {
                disk->inUse = 1;
                disk->fsType = MPFS2;
                disk->fsFunctions = gSYSFSObj[index].nativeFileSystemFunctions;
                disk->mountName = (mountName + 5);  // Save only mountName. Do not save "/mnt/"
                disk->diskNumber = volProperty.volNumber;
            }
            break;
        default:
            break;
    }

    if(disk->fsFunctions->mount == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return SYS_FS_RES_FAILURE;
    }

    fileStatus = disk->fsFunctions->mount(disk->diskNumber);

    if(fileStatus == 0)
    {
        return SYS_FS_RES_SUCCESS;
    }
    else
    {
        errorValue = fileStatus;
        return SYS_FS_RES_FAILURE;
    }
}

//******************************************************************************
/* Function:
	SYS_FS_HANDLE SYS_FS_FileOpen(const char* fname, int attributes);

  Summary:
     Open a file

  Description:
	The SYS_FS_FileOpen opens a requested file.

  Precondition:
    None.

  Parameters:
    path      	     			- Path to the file

    attributes				- Access mode of the file


  Returns:
        If Success: Valid handle will be returned
        If Failure: returned handle will be SYS_FS_HANDLE_INVALID

  Remarks:
	None
*/

SYS_FS_HANDLE SYS_FS_FileOpen
(
 const char *fname,
 SYS_FS_FILE_OPEN_ATTRIBUTES attributes
 )
{
    int fileStatus = SYS_FS_ERROR_NOT_READY;
    uint32_t j;
    SYS_FS_OBJ * obj;
    uint8_t pathWithDiskNo[FAT_FS_MAX_LFN];
    int diskIndex;
    const char *Temp, *Temp1;
    SYS_FS_MOUNT_POINT *disk;

    /* Need to set up the file name
     * wiht disk number. Initialize
     * the path name array. */
    for(j = 0; j < FAT_FS_MAX_LFN; j ++)
    {
        pathWithDiskNo[j] = 0;
    }

    // Start with 0th disk and find a disk which is available (not in use)
    for(diskIndex = 0; diskIndex < SYS_FS_VOLUME_NUMBER; diskIndex++)
    {
        disk = &gSYSFSMountPoint[diskIndex];
        if(disk->inUse == true)
        {
            // Find the element from "gSYSFSMediaDiskObject" which has matching "mountName"
            // I did not use "strcmp" as not sure if its implementation is re-entrant or not
            Temp = (fname + 5); // ignore the first 5 chars --> "/mnt/"
            Temp1 = disk->mountName;
            while(*Temp != '/') // compare untill you reach the starting of file name --> "/FILE.TXT"
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
            // as well, as we have got the "disk" with required name
            if(*Temp == '/')
                break;
        }
    }

    if(diskIndex >= SYS_FS_VOLUME_NUMBER)
    {
        SYS_ASSERT(false, "Invalid Disk");
        errorValue = SYS_FS_ERROR_INVALID_NAME;
        return SYS_FS_HANDLE_INVALID;
    }

    if(disk->inUse == false)
    {
        SYS_ASSERT(false, "Invalid mount point. Was the disk mounted?");
        errorValue = SYS_FS_ERROR_NO_FILESYSTEM;
        return SYS_FS_HANDLE_INVALID;
    }

    /* For MPFS file system, opening a file is possible only in "READ" mode */
    if((disk->fsType == MPFS2) && (attributes != SYS_FS_FILE_OPEN_READ))
    {
        errorValue = SYS_FS_ERROR_DENIED;
        return SYS_FS_HANDLE_INVALID;
    }

    obj = NULL;

    for(j = 0; j < SYS_FS_MAX_FILES; j ++)
    {
        if(gSYSFSFileObj[j].inUse == false)
        {
            gSYSFSFileObj[j].inUse = true;
            gSYSFSFileObj[j].mountPoint = disk;
            obj = &gSYSFSFileObj[j];
            break;
        }
    }

    /* If the object is NULL, then we dont have a free
     * file system object */

    if(obj == NULL)
    {
        errorValue = SYS_FS_ERROR_TOO_MANY_OPEN_FILES;
        return(SYS_FS_HANDLE_INVALID);
    }

    /* Append "0:" before the file name. This is required
     * for different disks */

    pathWithDiskNo[0] = (uint8_t)disk->diskNumber + '0';
    pathWithDiskNo[1] = ':';

    /* "Temp" is holding the pointer to "/FILE.TXT". Hence, increment "Temp" once, to remove "/" */
    Temp++;

    /* Form the name with the drive letter */
    for(j = 2;  j < FAT_FS_MAX_LFN; Temp ++, j ++)
    {
        pathWithDiskNo[j] = *Temp;
        /* Save the file name for future use */
        obj->fileName[j - 2] = *Temp;
        if(*Temp == '\0')
            break;
    }

    /* Now, call the real file open function */

    if(disk->fsFunctions->open == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        obj->inUse = false;
        return (SYS_FS_HANDLE_INVALID);
    }

    /* Convert the SYS_FS file open attributes to FAT FS attributes */
    switch(attributes)
    {
        case SYS_FS_FILE_OPEN_READ:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_READ);
            break;
        case SYS_FS_FILE_OPEN_WRITE:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_WRITE | FA_OPEN_ALWAYS);
            break;
        case SYS_FS_FILE_OPEN_APPEND:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_WRITE | FA_OPEN_ALWAYS);
            if(fileStatus == 0)
            {
                fileStatus = SYS_FS_FileSeek((SYS_FS_HANDLE)obj, 0, SYS_FS_SEEK_END);
            }
            break;
//-----------------------------------------------------------------------------------
        case SYS_FS_FILE_OPEN_READ_PLUS:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_READ | FA_WRITE);
            break;
        case SYS_FS_FILE_OPEN_WRITE_PLUS:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            break;
        case SYS_FS_FILE_OPEN_APPEND_PLUS:
            fileStatus = disk->fsFunctions->open((uintptr_t)&obj->nativeFSFileObj, (const char *)pathWithDiskNo, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if(fileStatus == 0)
            {
                fileStatus = SYS_FS_FileSeek((SYS_FS_HANDLE)obj, 0, SYS_FS_SEEK_END);
            }
            break;
    }


    if(fileStatus == 0)
    {
        return((SYS_FS_HANDLE)obj);
    }
    else
    {
        errorValue = fileStatus;
        obj->inUse = false;
        return(SYS_FS_HANDLE_INVALID);
    }

}

//******************************************************************************
/*Function:
    bool SYS_FS_FileNameGet(SYS_FS_HANDLE handle, uint8_t* cName, uint16_t wLen)

    Summary:
        Reads the file name.

    Description:
        Reads the file name of a file that is already open.

    Precondition:
        The file handle referenced by handle is already open.

    Parameters:
        handle 	- file handle obtaind during file Open.
 	cName - where to store the name of the file.
	wLen - the maximum length of data to store in cName.

    Returns:
		If Success	-

			The file name was successfully located	- true

        	If Failure
                        The file handle provided is not currently open	- false

		The reason for failure could be retrieved with SYS_FS_Error

  Remarks:
	None
***************************************************************************/
bool SYS_FS_FileNameGet(SYS_FS_HANDLE handle, uint8_t* cName, uint16_t wLen)
{
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    uint32_t j;

    if(handle == SYS_FS_HANDLE_INVALID)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        return false;
    }

    if(obj->inUse == false)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        return false;
    }

    if(wLen > FAT_FS_MAX_LFN)
    {
        wLen = FAT_FS_MAX_LFN;
    }
    
    for(j = 0;  j < wLen; j ++)
    {
        cName[j] = obj->fileName[j];
        /* break, in case end of string reached */
        if(obj->fileName[j] == '\0')
            break;
    }

    return true;

}

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Unmount(const char *mountName);


    Summary:
        unmount filesystems

    Description:
        remove the attachment of the (topmost) filesystem mounted on target

    Precondition:
        none

    Parameters:
        mountName - Mount name for the device to be mounted

    Returns:
        If Success: SYS_FS_RES_SUCCESS
        If Failure: SYS_FS_RES_FAILURE
            Sets error code which can be retrieved with SYS_FS_Error
***************************************************************************/
SYS_FS_RESULT SYS_FS_Unmount(const char *fname)
{
    int fileStatus;
    int diskIndex;
    const char *Temp, *Temp1;
    SYS_FS_MOUNT_POINT *disk;

    // Start with 0th disk and find a disk which is available (not in use)
    for(diskIndex = 0; diskIndex < SYS_FS_VOLUME_NUMBER; diskIndex++)
    {
        disk = &gSYSFSMountPoint[diskIndex];
        if(disk->inUse == true)
        {
            // Find the element from "gSYSFSMediaDiskObject" which has matching "mountName"
            // I did not use "strcmp" as not sure if its implementation is re-entrant or not
            Temp = (fname + 5); // ignore the first 5 chars --> "/mnt/"
            Temp1 = disk->mountName;
            while(*Temp != '\0') // compare untill you reach the end of string
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
            // as well, as we have got the "disk" with required name
            if(*Temp == '\0')
                break;
        }
    }

    if(diskIndex >= SYS_FS_VOLUME_NUMBER)
    {
        SYS_ASSERT(false, "Invalid Disk");
        errorValue = SYS_FS_ERROR_INVALID_NAME;
        return SYS_FS_RES_FAILURE;
    }

    if(disk->inUse == false)
    {
        SYS_ASSERT(false, "Invalid mount point. Was the disk mounted?");
        errorValue = SYS_FS_ERROR_NO_FILESYSTEM;
        return SYS_FS_RES_FAILURE;
    }


    /* Now, call the real file mount function */
	
    if(disk->fsFunctions->unmount == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return SYS_FS_RES_FAILURE;
    }	

    fileStatus = disk->fsFunctions->unmount(disk->diskNumber);

    if(fileStatus == 0)
    {
        disk->inUse = 0;
        disk->mountName = NULL;
        disk->fsFunctions = NULL;
        return SYS_FS_RES_SUCCESS;
    }
    else
    {	
        errorValue = fileStatus;
        return SYS_FS_RES_FAILURE;
    }

}

//******************************************************************************
/* Function:
	size_t SYS_FS_FileRead(void *buf, size_t nbyte, SYS_FS_HANDLE handle)


  Summary:
     Read specified bytes from a file

  Description:
	The SYS_FS_FileRead() function shall attempt to read nbyte bytes from the file associated with
	the open file handle into the buffer pointed to by buf.

  Precondition:
    A valid file handle must be obtained before reading a file.

  Parameters:
        handle			- File handle obtained during file open.
		buf				- Pointer to buffer in which data is read into.
		nbyte			- No of bytes to be read


  Returns:
        If Success: The number of bytes read (0 or positive number)
        If Failure: -1

  Remarks:
	None
*/
size_t SYS_FS_FileRead
(
    void *buffer,
    size_t nbyte,
    SYS_FS_HANDLE handle
 )
{
    int fileStatus;
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    uint32_t nosOfDataRead;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}

    if(obj->inUse == 0)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}

    /* Now, call the real file open function */

    if(obj->mountPoint->fsFunctions->read == NULL)
	{
            errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
            return -1;
	}

    fileStatus = 	obj->mountPoint->fsFunctions->read(obj->nativeFSFileObj, buffer,
            nbyte, &nosOfDataRead);

    if(fileStatus == 0)
    {
        return nosOfDataRead;
    }
    else
    {
        errorValue = fileStatus;
        return -1;
    }
}

//******************************************************************************
/* Function:
	size_t SYS_FS_FileWrite(const void *buf, size_t nbyte, SYS_FS_HANDLE handle)

  Summary:
     Write on the file

  Description:
	The SYS_FS_FileWrite() function shall attempt to write nbyte bytes from the buffer pointed to by buf to
	the file associated with the open file handle.

  Precondition:
    A valid file handle must be obtained before reading a file.

  Parameters:
        handle			- File handle obtained during file open.
		buf				- Pointer to buffer from which data is to be written
		nbyte			- No of bytes to be written


  Returns:
        If Success: The number of bytes written (0 or positive number)
        If Failure: -1

  Remarks:
	None
*/
size_t SYS_FS_FileWrite
(
    const void *buffer,
    size_t nbyte,
    SYS_FS_HANDLE handle
 )
{
    int fileStatus;
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    uint32_t nosOfDataWritten;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == 0)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}

    /* Now, call the real file open function */
    if(obj->mountPoint->fsFunctions->write == NULL)
	{
            errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
            return -1;
	}

    fileStatus = 	obj->mountPoint->fsFunctions->write(obj->nativeFSFileObj, buffer,
            nbyte, &nosOfDataWritten);

    if(fileStatus == 0)
    {
        return nosOfDataWritten;
    }
    else
    {
        errorValue = fileStatus;
        return -1;
    }
}

//******************************************************************************
/* Function:
	int SYS_FS_FileSeek(SYS_FS_HANDLE handle, int offset, SYS_FS_FILE_SEEK_CONTROL whence)

  Summary:
     Move the read/write file pointer

  Description:
	The SYS_FS_FileSeek() function shall set the file offset for the open file description associated with
	the file handle, as follows:

    If whence is SYS_FS_SEEK_SET, the file offset shall be set to offset bytes from the begining.
    If whence is SYS_FS_SEEK_CUR, the file offset shall be set to its current location plus offset.
    If whence is SYS_FS_SEEK_END, the file offset shall be set to the size of the file plus offset.

	The behavior of SYS_FS_FileSeek() on devices which are incapable of seeking is implementation-defined.
	The value of the file offset associated with such a device is undefined.

  Precondition:
    None.

  Parameters:
    handle				- A valid file handle
	offset				- The number of bytes which act as file offset
	whence				- File seek control input

  Returns:
        If Success: The number of bytes written (0 or positive number)
        If Failure: -1

  Remarks:
	None
*/
int32_t SYS_FS_FileSeek
(
    SYS_FS_HANDLE handle,
    int32_t offset,
    SYS_FS_FILE_SEEK_CONTROL whence
 )
{
    int fileStatus = SYS_FS_ERROR_NOT_READY;
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    long tell = 0;
    uint32_t size = 0;
    int temp;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == 0)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}

    if((obj->mountPoint->fsFunctions->seek == NULL) || (obj->mountPoint->fsFunctions->tell == NULL) ||
            (obj->mountPoint->fsFunctions->size == NULL))
        {
            errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
            return -1;
        }


    switch (whence)
    {
        case SYS_FS_SEEK_SET:
            fileStatus = obj->mountPoint->fsFunctions->seek(obj->nativeFSFileObj, offset);
            break;
        case SYS_FS_SEEK_CUR:
            tell = obj->mountPoint->fsFunctions->tell(obj->nativeFSFileObj);
            temp = (offset + tell);
            fileStatus = obj->mountPoint->fsFunctions->seek(obj->nativeFSFileObj, temp);
            break;
        case SYS_FS_SEEK_END:
            size = obj->mountPoint->fsFunctions->size(obj->nativeFSFileObj);
            temp = (offset + size);
            fileStatus = obj->mountPoint->fsFunctions->seek(obj->nativeFSFileObj, temp);
            break;
    }

    

    if(fileStatus == 0)
    {
		/* This is success value, but required in special case, where requested offset was (-1) */
		errorValue = SYS_FS_ERROR_OK;
        return offset;
    }
    else
    {
        errorValue = fileStatus;
        return -1;
    }
}

//******************************************************************************
/*Function:
    int32_t SYS_FS_FileTell(SYS_FS_HANDLE handle)

    Summary:
        Obtains the file pointer position

    Description:
        Obtains the current value of the file position indicator for the
        handle pointed to by handle.

    Precondition:
        none

    Parameters:
        handle - File handle

    Returns:
        If Success: current offset
        If Failure:  -1
            Sets error code which can be retrieved with SYS_FS_FileError

  Remarks:
	None

***************************************************************************/
int32_t SYS_FS_FileTell
(
    SYS_FS_HANDLE handle
 )
{
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    long status;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == 0)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        return -1;
    }

    if(obj->mountPoint->fsFunctions->tell == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return -1;
    }

    status = obj->mountPoint->fsFunctions->tell(obj->nativeFSFileObj);

    return status;
}

//******************************************************************************
/*Function:
    int32_t SYS_FS_FileSize( SYS_FS_HANDLE handle )

    Summary:
    Returns the size of the file

    Description:
        Returns the size of the file as pointed by the handle.

    Precondition:
        none

    Parameters:
        handle - File handle

    Returns:
        If Success: file size
        If Failure: -1
			Sets error code which can be retrieved with SYS_FS_FileError

  Remarks:
	None
***************************************************************************/
int32_t SYS_FS_FileSize
(
    SYS_FS_HANDLE handle
 )
{
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    long status;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == 0)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        return -1;
    }

    if(obj->mountPoint->fsFunctions->size == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return -1;
    }

    status = obj->mountPoint->fsFunctions->size(obj->nativeFSFileObj);

    return status;
}

//******************************************************************************
/*Function:
    bool SYS_FS_FileEOF(SYS_FS_HANDLE handle)

    Summary:
        check handle status

    Description:
        Checks weather or not the file position indicator is at the end of
        the file.

    Precondition:
        none

    Parameters:
        handle - file handle

    Returns:
		When file pointer not reached the end of file:	false
		When file pointer reached the end of file:		true
		When failure:						false
			Sets error code which can be retrieved with SYS_FS_FileError
  Remarks:
	None
***************************************************************************/
bool SYS_FS_FileEOF
(
    SYS_FS_HANDLE handle
 )
{
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
    volatile bool status;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == 0)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        return false;
    }

    if(obj->mountPoint->fsFunctions->eof == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return false;
    }

    status = obj->mountPoint->fsFunctions->eof(obj->nativeFSFileObj);

	/* This is success value, but required in special case, where requested offset was (-1) */
	errorValue = SYS_FS_ERROR_OK;	
    return (bool)status;
}

//******************************************************************************
/* Function:
	SYS_FS_RESULT SYS_FS_FileStat(const char* path, SYS_FS_FSTAT *buf)

  Summary:
     Get file status

  Description:
	The SYS_FS_FileStat() function shall obtain information about a file associated
	with the file name, and shall write it to the area pointed to by buf.

	The buf argument is a pointer to a SYS_FS_FSTAT structure,into which information
	is placed concerning the file.

	This function can read the status of file irrespective of a file is opened or not.

  Precondition:
    None.

  Parameters:
    path      	     			- Path to the file
	buf							- pointer to SYS_FS_FSTAT variable

  Returns:
        If Success: SYS_FS_RES_SUCCESS
        If Failure: SYS_FS_RES_FAILURE

  Remarks:
	None
*/
SYS_FS_RESULT SYS_FS_FileStat
(
    const char *fname,
    SYS_FS_FSTAT *buf
 )
{
    int fileStatus;
    uint32_t j;
    uint8_t pathWithDiskNo[FAT_FS_MAX_LFN];
    int diskIndex;
    const char *Temp, *Temp1;
    SYS_FS_MOUNT_POINT *disk;

    /* Need to set up the file name
     * wiht disk number. Initialize
     * the path name array. */
    for(j = 0; j < FAT_FS_MAX_LFN; j ++)
    {
        pathWithDiskNo[j] = 0;
    }

    // Start with 0th disk and find a disk which is available (not in use)
    for(diskIndex = 0; diskIndex < SYS_FS_VOLUME_NUMBER; diskIndex++)
    {
        disk = &gSYSFSMountPoint[diskIndex];
        if(disk->inUse == true)
        {
            // Find the element from "gSYSFSMediaDiskObject" which has matching "mountName"
            // I did not use "strcmp" as not sure if its implementation is re-entrant or not
            Temp = (fname + 5); // ignore the first 5 chars --> "/mnt/"
            Temp1 = disk->mountName;
            while(*Temp != '/') // compare untill you reach the starting of file name --> "/FILE.TXT"
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
            // as well, as we have got the "disk" with required name
            if(*Temp == '/')
                break;
        }
    }

    if(diskIndex >= SYS_FS_VOLUME_NUMBER)
    {
        SYS_ASSERT(false, "Invalid Disk");
        errorValue = SYS_FS_ERROR_INVALID_NAME;
        return SYS_FS_RES_FAILURE;
    }

    if(disk->inUse == false)
    {
        SYS_ASSERT(false, "Invalid mount point. Was the disk mounted?");
        errorValue = SYS_FS_ERROR_NO_FILESYSTEM;
        return SYS_FS_RES_FAILURE;
    }

    /* Append "0:" before the file name. This is required
     * for different disks */

    pathWithDiskNo[0] = (uint8_t)disk->diskNumber + '0';
    pathWithDiskNo[1] = ':';

    /* "Temp" is holding the pointer to "/FILE.TXT". Hence, increment "Temp" once, to remove "/" */
    Temp++;

    /* Form the name with the drive letter */
    for(j = 2;  j < FAT_FS_MAX_LFN; Temp ++, j ++)
    {
        pathWithDiskNo[j] = *Temp;
        if(*Temp == '\0')
            break;
    }

    if(disk->fsFunctions->fstat == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return SYS_FS_RES_FAILURE;
    }
		
    fileStatus = disk->fsFunctions->fstat((const char *)pathWithDiskNo, (uintptr_t)buf);

    if(fileStatus == 0)
    {
        return SYS_FS_RES_SUCCESS;
    }
    else
    {
        errorValue = fileStatus;
        return SYS_FS_RES_FAILURE;
    }
}

//******************************************************************************
/* Function:
	SYS_FS_RESULT SYS_FS_FileClose(SYS_FS_HANDLE handle);

  Summary:
     Close a file descriptor

  Description:
	The SYS_FS_FileClose() function closes an opened file

  Precondition:
    None.

  Parameters:
    handle			- A valid handle, which was obtained while opening the file.

  Returns:
        If Success: SYS_FS_RES_SUCCESS
        If Failure: SYS_FS_RES_FAILURE

  Remarks:
	None
*/
SYS_FS_RESULT SYS_FS_FileClose
(
 SYS_FS_HANDLE handle
 )
{
    int fileStatus;
    SYS_FS_OBJ *obj = (SYS_FS_OBJ *)handle;
	
	if(handle == SYS_FS_HANDLE_INVALID)
	{
            errorValue = SYS_FS_ERROR_INVALID_OBJECT;
            return -1;
	}	

    if(obj->inUse == false)
    {
        errorValue = SYS_FS_ERROR_INVALID_OBJECT;
        SYS_ASSERT(false,"File object is not in use");
        return SYS_FS_RES_FAILURE;
    }

    if(obj->mountPoint->fsFunctions->close == NULL)
    {
        errorValue = SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS;
        return SYS_FS_RES_FAILURE;
    }

    /* Now, call the real file open function */

    fileStatus = obj->mountPoint->fsFunctions->close(obj->nativeFSFileObj);
    if(fileStatus == 0)
    {
        /* Return the SYS_FS file system object. */
        obj->inUse = false;
        return SYS_FS_RES_SUCCESS;
    }
    else
    {
        errorValue = fileStatus;
        return SYS_FS_RES_FAILURE;
    }

    /* Do the following in disk un-mount only */
    //	sysFsObject[mountPoint].inUse = 0;
}

//******************************************************************************
/*Function:
    SYS_FS_ERROR SYS_FS_FileError(void)

    Summary:
        check the type of error

    Description:
        When a function returns "failure", the application can know the exact
		reason of failure by calling the SYS_FS_FileError.

    Precondition:
        none

    Parameters:
        none

    Returns:
		Error code of type SYS_FS_ERROR

  Remarks:
	None
***************************************************************************/
SYS_FS_ERROR SYS_FS_FileError(void)
{
    return errorValue;
}

// *****************************************************************************
/* Function:
    void SYS_FS_Tasks ( void )

  Summary:
    Tasks for the sys_fs layer

  Description:
    This routine is used to run the varioius tasks and functionalities of sys_fs
    layer.

  Precondition:
    The SYS_FS_Initialize routine must have been called before running the tasks.

  Parameters:
    None.

  Returns:
    None
*/

void SYS_FS_Tasks ( void )
{
    /* Task routine for media manager */
    SYS_FS_MEDIA_MANAGER_Tasks();
}
