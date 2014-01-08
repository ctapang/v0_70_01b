/*************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    sys_fs.h

  Summary:
    This file contains function and type declarations required to interact
    with the MPLAB Harmony File System Framework.

  Description:
    File System System-Library Interface Declarations and types.
    
    This file contains function and type declarations required to interact
    with the MPLAB Harmony File System Framework.                         
  *************************************************************************/

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

#ifndef		_SYS_FS
#define		_SYS_FS

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// *****************************************************************************
/* SYS FS File Handle 

  Summary:
    This type defines the file handle.

  Description:
    While the application code opens a file, a file handle is returned by the open 
	function (on successful open). This type defines the type of file handle.  

  Remarks:
    None.
*/
typedef uintptr_t       SYS_FS_HANDLE;

// *****************************************************************************
/* SYS FS File Invalid Handle 

  Summary:
    This definitions defines the SYS FS file invalid handle.

  Description:
    While the application code opens a file, if the file open is unsuccessful, an
	invalid file handle is returned. This definition defines the type of  
	invalid file handle.  

  Remarks:
    None.
*/
#define SYS_FS_HANDLE_INVALID ((SYS_FS_HANDLE)(-1))

//*******************************************************************************
/* File System type

  Summary:
    Enumerated data type identifying native file systems supported.

  Description:
    These enumerated values are the possible native file system that can be supported
	by the SYS FS layer.

  Remarks:
	None.

*/
typedef enum
{
	/* FAT FS native File system */
	FAT,
	/* MPFS2 native File system */	
	MPFS2
}SYS_FS_FILE_SYSTEM_TYPE;



// *****************************************************************************
/* File Seek control

  Summary:
    Lists the various modes of file seek
	
  Description:
    This enumeration lists the various modes of file seek. When the application
	calls the SYS_FS_FileSeek function, it specifies the kind of seek that needs to
	be performed. The enumeration lists the various modes of file seek.

  Remarks:
    None.	
*/
typedef enum
{
    /* The file offset shall be set to input number of bytes from the start */
	SYS_FS_SEEK_SET,
	/* The file offset shall be set to its current location plus input number of bytes */
	SYS_FS_SEEK_CUR,
	/* The file offset shall be set to the size of the file plus input number of bytes */
	SYS_FS_SEEK_END,

}SYS_FS_FILE_SEEK_CONTROL;

// *****************************************************************************
/* File operation result enum

  Summary:
    Lists the various results of a file operation
	
  Description:
    This enumeration lists the various results of a file operation. When a file 
	operation function is called from the application, and if the return type of
	the function is SYS_FS_RESULT, then, the enumration below specifies the 
	value of function return.

*/

typedef enum
{
	/* Operation successful */
    SYS_FS_RES_SUCCESS	=  0,
	/* operation failed */
    SYS_FS_RES_FAILURE	= -1

}SYS_FS_RESULT;

// *****************************************************************************
/* File open attributes

  Summary:
    Lists the various attributes (modes) in which a file can be opened

  Description:
    Lists the various attributes (modes) in which a file can be opened

*/

typedef enum
{
        /* 
		
           reading the file    =   possible, if file exists.
		   
           reading the file    =   file open returns error, if file does not
                                   exist.
								   
           writing to the file =   not possible. Write operation returns error
		   
         */
    SYS_FS_FILE_OPEN_READ	=  0,

        /*
		
           reading the file    =  not possble. Read operation returns error
		   
           writing to the file =  possible. If file exists, write happens from
                                  the begining of the file, overwriting the existing
                                  content of the file. 
								  
           writing to the file =  If file does not exist, a new file will be created
                                  and data will be written into the newly created file.
								  
         */
    SYS_FS_FILE_OPEN_WRITE,

        /*
		
           reading the file    =  not possble. Read operation returns error
		   
           writing to the file =  possible. If file exists, write happens from
                                  the end of the file, preserving the existing
                                  content of the file. 
								  
           writing to the file =  If file does not exist, a new file will be created
                                  and data will be written into the newly created file.
		 
         */
    SYS_FS_FILE_OPEN_APPEND,

        /*
		
           reading the file    =   possible, if file exists.
		   
           reading the file    =   file open returns error, if file does not
                                   exist.
								   
           writing to the file =   possible, if file exists, staring from the begining
                                   of the file (overwriting).
								   
            writing to the file =  file open returns error, if file does not
                                   exist.
								   
         */
    SYS_FS_FILE_OPEN_READ_PLUS,

        /*
		
           reading the file    =  possible, if file exists.
		   
           reading the file    =  If file does not exist, a new file will be
                                  created.
								  
           writing to the file =  possible. If file exists, write happens from
                                  the begining of the file, overwriting the existing
                                 content of the file.
								 
           writing to the file =  If file does not exist, a new file will be created
                                  and data will be written into the newly created file.
		 
         */
    SYS_FS_FILE_OPEN_WRITE_PLUS,

        /*
		
           reading the file    =  possible, if file exists.
		   
           reading the file    =  If file does not exist, a new file will be
                                  created.
								  
           writing to the file =  possible. If file exists, write happens from
                                  the end of the file, preserving the existing
                                  content of the file.
								  
           writing to the file =  If file does not exist, a new file will be created
                                  and data will be written into the newly created file.
		 
         */
    SYS_FS_FILE_OPEN_APPEND_PLUS

}SYS_FS_FILE_OPEN_ATTRIBUTES;

// *****************************************************************************
/* File Error error enumeration

  Summary:
    Lists the various error cases
	
  Description:
    This enumeration lists the various error cases. When the application calls for
	a file system function which has a return type of SYS_FS_RESULT and if the return
	value is SYS_FS_RES_FAILURE, the application can know the specific reason for 
	failure by calling the SYS_FS_FileError function. The return value of SYS_FS_FileError
	function will be one of the enumeration of the type SYS_FS_ERROR.

*/

typedef enum
{
    /* Success */
    SYS_FS_ERROR_OK = 0,
    /* (1) A hard error occurred in the low level disk I/O layer */
    SYS_FS_ERROR_DISK_ERR,
    /* (2) Assertion failed */
    SYS_FS_ERROR_INT_ERR,
    /* (3) The physical drive cannot work */
    SYS_FS_ERROR_NOT_READY,
    /* (4) Could not find the file */
    SYS_FS_ERROR_NO_FILE,
    /* (5) Could not find the path */
    SYS_FS_ERROR_NO_PATH,
    /* (6) The path name format is invalid */
    SYS_FS_ERROR_INVALID_NAME,
    /* (7) Access denied due to prohibited access or directory full */
    SYS_FS_ERROR_DENIED,
    /* (8) Access denied due to prohibited access */
    SYS_FS_ERROR_EXIST,
    /* (9) The file/directory object is invalid */
    SYS_FS_ERROR_INVALID_OBJECT,
    /* (10) The physical drive is write protected */
    SYS_FS_ERROR_WRITE_PROTECTED,
    /* (11) The logical drive number is invalid */
    SYS_FS_ERROR_INVALID_DRIVE,
    /* (12) The volume has no work area */
    SYS_FS_ERROR_NOT_ENABLED,
    /* (13) There is no valid volume */
    SYS_FS_ERROR_NO_FILESYSTEM,
    /* (14) The Format() aborted due to any parameter error */
    SYS_FS_ERROR_FORMAT_ABORTED,
    /* (15) Could not get a grant to access the volume within defined period */
    SYS_FS_ERROR_TIMEOUT,
    /* (16) The operation is rejected according to the file sharing policy */
    SYS_FS_ERROR_LOCKED,
    /* (17) LFN working buffer could not be allocated */
    SYS_FS_ERROR_NOT_ENOUGH_CORE,
    /* (18) Number of open files */
    SYS_FS_ERROR_TOO_MANY_OPEN_FILES,
    /* (19) Given parameter is invalid */
    SYS_FS_ERROR_INVALID_PARAMETER,
    /* (20) Too many mounts requested. Not enough free volume available */
    SYS_FS_ERROR_NOT_ENOUGH_FREE_VOLUME,
    /* (21) Requested native file system is not supported */
    SYS_FS_ERROR_FS_NOT_SUPPORTED,
    /* (22) Requested native file system does not match the format of volume */
    SYS_FS_ERROR_FS_NOT_MATCH_WITH_VOLUME,
    /* (23) Function not supported in native file system layer */
    SYS_FS_ERROR_NOT_SUPPORTED_IN_NATIVE_FS
}SYS_FS_ERROR;


// *****************************************************************************
/* FAT File System Sector size

  Summary:
    Lists the definitions for FAT file system sector size.

  Description:
    Maximum sector size to be handled.
    Always set the value of sector size to 512

*/
#define	FAT_FS_MAX_SS	512


// *****************************************************************************
/* FAT File System LFN (long file name) selection

  Summary:
    Lists the definitions for FAT file system LFN selection

  Description:
    The FAT_FS_USE_LFN option switches the LFN support.
	Set the value to 1

*/
#define	FAT_FS_USE_LFN	1

// *****************************************************************************
/* FAT File System LFN (long file name) max length

  Summary:
    Lists the maximum length of file name during LFN selection

  Description:
	Set the value to 255

*/
#define	FAT_FS_MAX_LFN	255		

// *****************************************************************************
/* SYS FS Function signature structure for native file systems

  Summary:
    SYS FS Function signature structure for native file systems

  Description:
    The SYS FS layer supports functions from each native file system layer. This
    structure specifies the signature for each function from native file system
    (parameter that needs to be passed to each function and return type for each
    function). If a new native file system is to be integrated with the SYS FS
    layer, the functions should follow the signature.
	
	The structure of function pointer for 2 native file system	-- FAT FS and
	MPFS2 is already provided in the respective source files for the native
	file system. Hence the following structure is not immediately useful for the
	user. But the explanation for the structure is still provided for 
	advanced users who would wish to integrate a new native file system to the 
	Harmony File system framework.

  Remarks:
    None.

*/

typedef struct
{
            /* Function pointer of native file system for mounting a volume */
	int (*mount) (uint8_t vol);
            /* Function pointer of native file system for unmounting a volume */
	int (*unmount) (uint8_t vol);
            /* Function pointer of native file system for opening a file */
	int (*open) (uintptr_t handle, const char* path, uint8_t mode);
            /* Function pointer of native file system for reading a file */
	int (*read) (uintptr_t fp, void* buff, uint32_t btr, uint32_t *br);
            /* Function pointer of native file system for writing to a file */
	int (*write) (uintptr_t fp, const void* buff, uint32_t btw, uint32_t* bw);
            /* Function pointer of native file system for closing a file */
	int (*close) (uintptr_t fp);
            /* Function pointer of native file system for moving the file pointer by a desired offset */
	int (*seek) (uintptr_t handle, uint32_t offset);
            /* Function pointer of native file system for finding the position of the file pointer */
	uint32_t (*tell) (uintptr_t handle);
            /* Function pointer of native file system to check if the end of file is reached */
	bool (*eof) (uintptr_t handle);
            /* Function pointer of native file system to know the size of file */
	uint32_t (*size) (uintptr_t handle);
            /* Function pointer of native file system to know the status of file */
	int (*fstat) (const char* path, uintptr_t fno);
}
SYS_FS_FUNCTIONS;

// *****************************************************************************
/* SYS_FS_REGISTRATION_TABLE structure

  Summary:
    The sys_fs layer has to be initialized by passing this structure with suitably
	initialized members.

  Description:
    When the SYS FS layer is initialised, it has to know the type of native file
	system it has to support and the list of functions for native file system. 
	The members of this structure can be initialized with suitable values and then 
	passed on to SYS_FS_Initialize initialization function. Please refer to the 
	example code provided for SYS_FS_Initialize.

  Remarks:
    None.
    
*/
typedef struct
{
	/* Native file system of type SYS_FS_FILE_SYSTEM_TYPE */
    SYS_FS_FILE_SYSTEM_TYPE nativeFileSystemType;
	
	/* Pointer to the structure of type SYS_FS_FUNCTIONS which has the list of 
	function-pointers for the native file system */	
    const SYS_FS_FUNCTIONS    *nativeFileSystemFunctions;
	
}SYS_FS_REGISTRATION_TABLE;

// *****************************************************************************
/* SYS FS File status structure
	
  Summary:
    The structure to obtain the status of a file.

  Description:
    This structure holds the various status of a file. The stucture is passed when
	SYS_FS_Stat function is called and after a successful execution of the function,
	the members of this structure carries the file status.	

  Remarks:
    None.
    
*/
typedef struct 
{
	/* File size */
	uint32_t	fsize;		
	/* Last modified date */
	uint16_t	fdate;		
	/* Last modified time */
	uint16_t	ftime;		
	/* Attribute */	
	uint8_t	fattrib;	
	/* Short file name (8.3 format) */
	char            fname[13];	
#if FAT_FS_USE_LFN
	/* Pointer to the LFN buffer */
	char*	lfname;		
	/* Size of LFN buffer in TCHAR */
	uint32_t 	lfsize;			
#endif
} SYS_FS_FSTAT;

// ****************************************************************************
// ****************************************************************************
// Section: File System Abstraction Layer Interface Routines
// ****************************************************************************
// ****************************************************************************

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Initialize(const void* initData)

    Summary:
        Initializes the File system Abstration Layer (sys_fs layer).

    Description:
        Initializes the abstraction layer (sys_fs layer) and sets up the necessary parameters.

    Precondition:
        This is the first function to be called during usage of sys_fs.
		Calling other functions from sys_fs without initializing the sys_fs will
		cause un-predictable behavior.

    Parameters:
        initData	-	The pointer to array of the type SYS_FS_REGISTRATION_TABLE, 
						but type casted to (const void *).
						The number of elements of array is decided by the definition 
						SYS_FS_MAX_FILE_SYSTEM_TYPE. If the application uses 1 file system 
						(say only FAT FS), then SYS_FS_MAX_FILE_SYSTEM_TYPE is defined to be 1. 
						Otherwise, if the application uses 2 file systems (say FAT FS and MPFS2), 
						then SYS_FS_MAX_FILE_SYSTEM_TYPE is defined to be 2. The 
						SYS_FS_MAX_FILE_SYSTEM_TYPE has to be defined in system_config.h file.
						
    Returns:
        If Success	-	SYS_FS_RES_SUCCESS
		
        If Failure	-	SYS_FS_RES_FAILURE
		
		The reason for failure could be retrieved with SYS_FS_Error
			
	Example:
		<code>
		// This code snippet shows an example of how the
		// SYS FS is initialized

		// Only 1 file system is used
		
		#define SYS_FS_MAX_FILE_SYSTEM_TYPE			1

		// Functions pointer table for FAT FS		
		
		const SYS_FS_FUNCTIONS FatFsFunctions =
		{
			.mount  = f_mount,
			.unmount = f_unmount,
			.open   = f_open,
			.read   = f_read,
			.write  = f_write,
			.close  = f_close,
			.seek   = f_lseek,
			.tell   = f_tell,
			.eof    = f_eof,
			.size   = f_size,
			.fstat   = f_stat,
		};

		const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
		{
			{
			.nativeFileSystemType = FAT,
			.nativeFileSystemFunctions = &FatFsFunctions
			}
		};
		
		SYS_FS_Initialize( (const void *) sysFSInit );

		</code>			
***************************************************************************/
SYS_FS_RESULT SYS_FS_Initialize(const void* initData);

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Mount(const char *devName, const char *mountName, 
	SYS_FS_FILE_SYSTEM_TYPE filesystemtype, unsigned long mountflags, const void *data);

    Summary:
        Mount filesystems

    Description:
        The mount command attaches the filesystem specified to a volume. 
						  
		When a media (say, SD card or USB thumb drive) is attached to the system, the 
		SYS_FS_Tasks() function needs to run atleast 8 times (for each partition),
		from the SYS_Tasks(), before the volume names are assigned to each partitions. 
		Hence it is mandatory that the SYS_FS_Tasks() is run periodically.
		Also, it is mandatory that the SYS_FS_Mount() function call from the application code, is 
		not blocking. The application code has to allow the SYS_FS_Tasks() to
		run periodically while calling the SYS_FS_Mount function. If the SYS_FS_Mount() is called
		in a blocking mode, then the SYS_Tasks() never gets a chance to run and hence, the media 
		will not be analyzed and finally, the SYS_FS_Mount will never succed. This will result 
		in a dead-lock.

		There is no mechanism available for the application to know if the specified volume (devName)
		is really attached or not. The only available possibilty is to keep trying to mount the volume
		(with the devname), untill success is achieved. 	
		It is prudent that the application code implements a time out mechanism while trying to
		mount a volume (by calling SYS_FS_Mount). The trial for mount should continue atleast
		10 times before before assuming that the mount will never succedeed. This has to be done
		for every new volume to be mounted.
		
		The name standard of volume (devName) used in Harmony file system is as below: -
		
		For NVM			- "nvm" "media number" "volume number"	
		
		For SD card		- "mmcblk" "media number" "volume number"	
		
		For MSD			- "sd" "media number" "volume number"	
		
		Where, "media number" 	- a, b, c... depending upon number of media of certain type 
						  connected.
						  
	    Where, "volume number"	- 1, 2, 3... depending upon number of partitions in that
						  media.		
		
		The convention for assigning names to volumes is given by an example: -
		
		If an SD card (with 4 partitiona) is attached to the system, and assuming all 4
		partitions are recognized, then there will be 4 devNames -- mmcblka1, mmcblka2, mmcblka3
		and mmcblka4.
		
		Subsequently, a NVM media is attached which has only 1 partition, then the devname
		will be -- nvma1.
		
		Later, another SD card is attached to the system which has 1 partition, then the devname
		will be -- mmcblkb1.
		
		Finally, there will be 6 volume names (or devNames), which is available for the application
		to be mounted and used for file system.

    Precondition:
        The "devName" name for the volume has to be known. 
		The file sytem type with which each of the volumes are formatted has to be known. 
		Trying to mount a volume with a file system which is different from what the volume
		is actually formatted, will cause mounting failure.

    Parameters:
        devName 		- The device name (name of volume) which needs to be mounted. The devName
						  has to be preceeded by the string "/dev/".
						  
        mountName 		- Mount name for the device to be mounted. This is a name provided
						  by the user. In future, while accessing the mounted volume (say,
						  during SYS_FS_FileOpen operation), the mountName is used to refer the
						  path for file. The mount name has to be preceeded by the string
						  "/mnt/"
						  
        filesystemtype 	- native file system of SYS_FS_FILE_SYSTEM_TYPE type.
		
        mountflags 		- mounting control flags. This parameter is reserved for future
						  enhancements. Hence, always pass zero.
						  
        data 			- The data argument is interpreted by the different file systems. 
					      This parameter is reserved for future enhancements. Hence, always 
						  pass NULL.

    Returns:
        If Success		- SYS_FS_RES_SUCCESS
		
        If Failure		- SYS_FS_RES_FAILURE
		
		The reason for failure could be retrieved with SYS_FS_Error

	Example:
		<code>
			switch(appState)
			{
				case TRY_MOUNT:
					if(SYS_FS_Mount("/dev/mmcblka1", "/mnt/myDrive", FAT, 0, NULL) != SYS_FS_RES_SUCCESS)
					{
						// Failure, hence try mouting again
					}
					else
					{
						// Mount was successful. Do further file operations
						appState = DO_FURTHER_STUFFS;
						
					}
					break;
		</code>			
***************************************************************************/
SYS_FS_RESULT SYS_FS_Mount(const char *devName, const char *mountName, 
	SYS_FS_FILE_SYSTEM_TYPE filesystemtype, unsigned long mountflags, const void *data);

//******************************************************************************
/*Function:
    SYS_FS_RESULT SYS_FS_Unmount(const char *mountName);
    

    Summary:
        unmount filesystems

    Description:
        remove the attachment of the volume from the fil system

    Precondition:
		The volume name has to be know in order to pass as input to Unmount.
        The specified volume name to be unmounted should have been already mounted.

    Parameters:
        mountName 	-	Mount name for the volume to be mounted. The mount name 
						has to be preceeded by the string "/mnt/".

    Returns:
        If Success	-	SYS_FS_RES_SUCCESS
		
        If Failure	-	SYS_FS_RES_FAILURE

		The reason for failure could be retrieved with SYS_FS_Error
		
	Example:
		<code>
            if(SYS_FS_Unmount("/mnt/myDrive") != SYS_FS_RES_SUCCESS)
            {
                // Failure, hence try unmouting again
            }
            else
            {
                // Unmount was successful.
            }
		</code>				
***************************************************************************/
SYS_FS_RESULT SYS_FS_Unmount(const char *mountName);

//******************************************************************************
/* Function:
	SYS_FS_HANDLE SYS_FS_FileOpen(const char* fname, SYS_FS_FILE_OPEN_ATTRIBUTES attributes);
  
  Summary:
     Open a file 

  Description:
	The SYS_FS_FileOpen opens a requested file in a specific mode (attaribute).

  Precondition:
    Prior to opening a file, the name of the volume on which the 
	file resides should be known. Also, that volume should be already mounted.
	While opening the file, the name of	the volume is to be passed along with the file name.

  Parameters:
    path      	     			- Path to the file along with the volume name. The string of 
								  volume and file name has to be preceeded by "/mnt/". Also,
								  the volume name and file name has to be separated by a 
								  slash "/".

    attributes					- Access mode of the file, of the type
								  SYS_FS_FILE_OPEN_ATTRIBUTES
	
			
  Returns:
	If Success					- Valid handle will be returned
	
	If Failure 					- Returned handle will be SYS_FS_HANDLE_INVALID
	
	The reason for failure could be retrieved with SYS_FS_Error
  
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
		</code>

  Remarks:
	None
*/

SYS_FS_HANDLE SYS_FS_FileOpen(const char* fname, SYS_FS_FILE_OPEN_ATTRIBUTES attributes);

//******************************************************************************
/* Function:
	SYS_FS_RESULT SYS_FS_FileClose(SYS_FS_HANDLE handle);
  
  Summary:
     Close a file.

  Description:
	The SYS_FS_FileClose() function closes an opened file

  Precondition:
    A valid file handle must be obtained before closing a file. 

  Parameters:
    handle			- A valid handle, which was obtained while opening the file.

  Returns:
	If Success		- SYS_FS_RES_SUCCESS
	
	If Failure		- SYS_FS_RES_FAILURE	
	
	The reason for failure could be retrieved with SYS_FS_Error
  
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...
	  
			SYS_FS_FileClose(fileHandle);
		
		</code>

  Remarks:
	None
*/

SYS_FS_RESULT SYS_FS_FileClose(SYS_FS_HANDLE handle);

//******************************************************************************
/* Function:
	size_t SYS_FS_FileRead(void *buf, size_t nbyte, SYS_FS_HANDLE handle)

  
  Summary:
     Read specified bytes from a file

  Description:
	The SYS_FS_FileRead() function shall attempt to read nbyte bytes from the file associated with 
	the file handle into the buffer pointed to by buf. 
	
  Precondition:
    A valid file handle must be obtained before reading a file. 

  Parameters:
        handle			- File handle obtained during file open.
		
		buf				- Pointer to buffer into which data is read.	
		
		nbyte			- Number of bytes to be read
	

  Returns:
	If Success			- The number of bytes successfully read (0 or positive number)
	
	If Failure			- (-1)  
	
	The reason for failure could be retrieved with SYS_FS_Error
	
	
  Example:
		<code>
			...
			char buf[20];
			size_t nbytes;
			size_t bytes_read;
			SYS_FS_HANDLE fd;
			...
			nbytes = sizeof(buf);
			bytes_read = SYS_FS_FileRead(buf, nbytes, fd);
			...	
		</code>

  Remarks:
	None
*/

size_t SYS_FS_FileRead(void *buf, size_t nbyte, SYS_FS_HANDLE handle);

//******************************************************************************
/* Function:
	size_t SYS_FS_FileWrite(const void *buf, size_t nbyte, SYS_FS_HANDLE handle)
  
  Summary:
     Write on the file

  Description:
	The SYS_FS_FileWrite() function shall attempt to write nbyte bytes from the buffer pointed to by buf to 
	the file associated with the file handle. 

  Precondition:
    A valid file handle must be obtained before writing a file. 

  Parameters:
        handle			- File handle obtained during file open.
		
		buf				- Pointer to buffer from which data is to be written
		
		nbyte			- Number of bytes to be written
	

  Returns:
        If Success		- The number of bytes successfully written (0 or positive number)
		
        If Failure		- (-1)
		
		The reason for failure could be retrieved with SYS_FS_Error
  
  Example:
		<code>
			...
			const char *buf = "Hello World";
			size_t nbytes;
			size_t bytes_written;
			SYS_FS_HANDLE fd;
			...

			bytes_written = SYS_FS_FileWrite((const void *)buf, nbytes, fd);
			...
		</code>

  Remarks:
	None
*/

size_t SYS_FS_FileWrite(const void *buf, size_t nbyte, SYS_FS_HANDLE handle);

//******************************************************************************
/* Function:
	SYS_FS_RESULT SYS_FS_FileStat(const char* path, SYS_FS_FSTAT *buf)

  Summary:
     Get file status

  Description:
	The SYS_FS_FileStat() function shall obtain information about a file associated
	with the file name, and shall write it to the structure pointed to by buf.

	The buf argument is a pointer to a SYS_FS_FSTAT structure,into which information 
	is placed concerning the file.
	
	This function can read the status of file irrespective of a file is opened or not.

  Precondition:
    Prior to opening a file, the name of the volume on which the 
	file resides should be known. Also, that volume should be already mounted.
	While opening the file, the name of	the volume is to be passed along with the file name.

  Parameters:
    path      	     			- Path to the file along with the volume name. The string of 
								  volume and file name has to be preceeded by "/mnt/". Also,
								  the volume name and file name has to be separated by a 
								  slash "/".
								  
	buf							- pointer to SYS_FS_FSTAT structure.

  Returns:
	If Success					- SYS_FS_RES_SUCCESS
	
	If Failure					- SYS_FS_RES_FAILURE	
	
	The reason for failure could be retrieved with SYS_FS_Error

  Example:
		<code>
			SYS_FS_fStat fileStat;
			
			
			if(SYS_FS_FileStat("/mnt/myDrive/FILE.TXT", &fileStat) == SYS_FS_RES_SUCCESS)
			{
				// Successfully read the status of file "FILE.TXT"
			}
			
			
		</code>

  Remarks:
	None
*/

SYS_FS_RESULT SYS_FS_FileStat(const char* fname, SYS_FS_FSTAT *buf);

//******************************************************************************
/* Function:
	int32_t SYS_FS_FileSeek(SYS_FS_HANDLE handle, int32_t offset, SYS_FS_FILE_SEEK_CONTROL whence)
  
  Summary:
     Move the file pointer.

  Description:
	The SYS_FS_FileSeek() function shall set the file pointer for a open file associated with 
	the file handle, as follows:

    If whence is SYS_FS_SEEK_SET, the file offset shall be set to offset bytes from the begining.
	
    If whence is SYS_FS_SEEK_CUR, the file offset shall be set to its current location plus offset.
	
    If whence is SYS_FS_SEEK_END, the file offset shall be set to the size of the file plus offset. If
	SYS_FS_SEEK_END is selected, then offset has to be a negative number, inorder for the file pointer
	to be valid.
	
	Trying to move the file pointer using SYS_FS_FileSeek, beyond the range of file will only cause the
	pointer to be moved to the last location of the file.

  Precondition:
    A valid file handle must be obtained before seeking a file. 

  Parameters:
    handle				- A valid file handle obtained during file open.
	
	offset				- The number of bytes which act as file offset. This value could be a positive
						  or negative value.
	whence				- File seek control input of type SYS_FS_FILE_SEEK_CONTROL.

  Returns:
	If Success			- The number of bytes by which file pointer is moved (0 or positive number)
	
	If Failure			- (-1) If the choosen offset value was (-1), then the success or failure can be
							ascertained with SYS_FS_Error.

							The reason for failure could be retrieved with SYS_FS_Error
 
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			int status;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...
			
			status = SYS_FS_FileSeek(fileHandle, 5, SYS_FS_SEEK_CUR);
			
			if((status != -1) && (status == 5))
			{
				// Success
			}

		</code>

  Remarks:
	None
*/

int32_t SYS_FS_FileSeek(SYS_FS_HANDLE fildes, int32_t offset, SYS_FS_FILE_SEEK_CONTROL whence);

//******************************************************************************
/*Function:
    int32_t SYS_FS_FileTell(SYS_FS_HANDLE handle)

    Summary:
        Obtains the file pointer position 

    Description:
        Obtains the current value of the file position indicator for the 
        file, pointed to by handle.
       
    Precondition:
        A valid file handle must be obtained before performing a file tell.

    Parameters:
        handle 		- 	File handle obtained during file Open.

    Returns:
        If Success	-	current file position
		
        If Failure	-	(-1)

		The reason for failure could be retrieved with SYS_FS_Error
			
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			int32_t tell;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...
			
			tell = SYS_FS_FileTell(fileHandle);
			
			if(tell != -1)
			{
				// Success
			}

		</code>

  Remarks:
	None			
			
***************************************************************************/
int32_t SYS_FS_FileTell(SYS_FS_HANDLE handle);

//******************************************************************************
/*Function:
    int32_t SYS_FS_FileSize( SYS_FS_HANDLE handle )

    Summary:
    Returns the size of the file

    Description:
        Returns the size of the file as pointed by the handle.

    Precondition:
        A valid file handle must be obtained before knowing a file size.

    Parameters:
        handle 		- File handle obtained during file Open.

    Returns:
        If Success	- file size
		
        If Failure	- (-1)

		The reason for failure could be retrieved with SYS_FS_Error
		
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			long fileSize;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...
			
			fileSize = SYS_FS_FileSize(fileHandle);
			
			if(fileSize != -1)
			{
				// Success
			}

		</code>

  Remarks:
	None		
***************************************************************************/
int32_t SYS_FS_FileSize( SYS_FS_HANDLE handle );

//******************************************************************************
/*Function:
    bool SYS_FS_FileEOF(SYS_FS_HANDLE handle)

    Summary:
        check handle status 

    Description:
        Checks whether or not the file position indicator is at the end of 
        the file.

    Precondition:
        A valid file handle must be obtained before knowing a file eof. 

    Parameters:
        handle 											- file handle obtaind during file Open.

    Returns:
		If Success	-
		
			When file pointer has not reached the end of file	- false
		
			When file pointer has reached the end of file		- true
		
		If Failure									- false

		The reason for failure could be retrieved with SYS_FS_Error
			
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			bool eof;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...
			
			eof = SYS_FS_FileEOF(fileHandle);
			
			if(eof == false)
			{
				// could be not EOF or a failure
				// Check the error state using SYS_FS_FileError
			}

		</code>

  Remarks:
	None			
***************************************************************************/
bool SYS_FS_FileEOF(SYS_FS_HANDLE handle);

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

  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			bool stat;
                        uint8_t fileName[255];

			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));

			if(fileHandle != SYS_FS_HANDLE_INVALID)
			{
				// File open is successful
			}
			...
			...

			stat = SYS_FS_FileNameGet(fileHandle, fileName, 8 );

			if(stat == false)
			{
				// file not located based on handle passed
				// Check the error state using SYS_FS_FileError
			}

		</code>

  Remarks:
	None
***************************************************************************/
bool SYS_FS_FileNameGet(SYS_FS_HANDLE handle, uint8_t* cName, uint16_t wLen);

//******************************************************************************
/*Function:
    SYS_FS_ERROR SYS_FS_FileError(void)

    Summary:
        check the type of error

    Description:
        When a file system operation fails, the application can know the exact
		reason of failure by calling the SYS_FS_FileError.

    Precondition:
        This function has to be called immediately after a failure is observed while doing
		a file operation. Any subsequent failure will overwrite the cause
		of pervious failure.

    Parameters:
        none

    Returns:
		Error code of type SYS_FS_ERROR
			
  Example:
		<code>
			SYS_FS_HANDLE fileHandle;
			SYS_FS_ERROR err;
			
			fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.JPG",
					(SYS_FS_FILE_OPEN_READ));
					
			if(fileHandle == SYS_FS_HANDLE_INVALID)
			{
				// If failure, now know the specific reason for failure
				err = SYS_FS_FileError();
			}

		</code>

  Remarks:
	None			
***************************************************************************/
SYS_FS_ERROR SYS_FS_FileError(void);

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

  Example:
    <code>

    void SYS_Tasks ( void )
    {
        SYS_FS_Tasks ();

        // Do other tasks
    }
    </code>

  Remarks:
    This routine is not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks).
*/

void SYS_FS_Tasks ( void );

#endif
