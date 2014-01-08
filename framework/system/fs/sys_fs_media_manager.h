#ifndef _SYS_FS_MEDIA_MANAGER_H_
#define _SYS_FS_MEDIA_MANAGER_H_

#include "driver/driver_common.h"
#include "system/fs/sys_fs.h"
#include "system/common/sys_module.h"

// *****************************************************************************
/* Status of media

  Summary:
    The state of media.

  Description:
    This enumeration states if the media is attached or not

  Remarks:
    None.
*/
typedef enum
{
    /* Media is detached */
    SYS_FS_MEDIA_DETACHED,
    /* Media is attached */
    SYS_FS_MEDIA_ATTACHED
}
SYS_FS_MEDIA_STATUS;

// *****************************************************************************
/* State of media

  Summary:
    The enumeration for state of media.

  Description:
    The media manager task picks a disk for analysis and takes it through a number
 *  of states. This enumeration mentions the state of the media.

  Remarks:
    None.
*/
typedef enum
{
    /* Media is detached */
    SYS_FS_MEDIA_STATE_DETACHED = 0,
    /* Media is registered with the media manager */
    SYS_FS_MEDIA_STATE_REGISTERED,
    /* Media driver is successfully opened by the media manager */
    SYS_FS_MEDIA_STATE_OPENED,
    /* Media is attached as detected by the media manager */
    SYS_FS_MEDIA_STATE_ATTACHED,
    /* Media maanger has completed all analysis of the media */
    SYS_FS_MEDIA_STATE_ANALYZED,      
}
SYS_FS_MEDIA_STATE;

// *****************************************************************************
/* Type of media

  Summary:
    The enumeration for type of media.

  Description:
    This enumeration is for the type of media registered with the media manager.
  Remarks:
    None.
*/
typedef enum
{
    /* Media is of type NVM (internal flash (non volatile) memory)*/
    SYS_FS_MEDIA_TYPE_NVM,
    /* Media is of type mass storage device */
    SYS_FS_MEDIA_TYPE_MSD,
    /* Media is of type SD card */
    SYS_FS_MEDIA_TYPE_SD_CARD,
    /* Media is of type RAM */
    SYS_FS_MEDIA_TYPE_RAM

}SYS_FS_MEDIA_TYPE;

// *****************************************************************************
/* Status of buffer

  Summary:
    The enumeration for status os buffer

  Description:
    This enumeration contains the various status of buffer.

  Remarks:
    None.
*/
typedef enum
{
    /*Done OK and ready */
    SYS_FS_MEDIA_BUFFER_COMPLETED          = 0 ,

    /*Scheduled but not started */
    SYS_FS_MEDIA_BUFFER_QUEUED             = 1,

    /*Currently being in transfer */
    SYS_FS_MEDIA_BUFFER_IN_PROGRESS        = 2,

    /*Unknown buffer */
    SYS_FS_MEDIA_BUFFER_UNKNOWN      = -1,

}
SYS_FS_MEDIA_BUFFER_STATUS;

// *****************************************************************************
/* Volume property

  Summary:
    Structure to obtain the property of volume

  Description:
    This structure is passed by sys_fs layer to know the property of a volume.
 * The function "SYS_FS_MEDIA_MANAGER_VolumePropertyGet" is used for the call.

  Remarks:
    None.
*/
typedef struct _SYS_FS_VOLUME_PROPERTY
{
    /* Volume # */
    unsigned int volNumber;
    /* File system type */
    SYS_FS_FILE_SYSTEM_TYPE fsType;
}
SYS_FS_VOLUME_PROPERTY;

typedef uintptr_t SYS_FS_MEDIA_BUFFER_HANDLE ;
typedef uintptr_t   SYS_FS_MEDIA_HANDLE;
#define  SYS_FS_MEDIA_HANDLE_INVALID DRV_HANDLE_INVALID
#define SYS_FS_MEDIA_BUFFER_HANDLE_INVALID DRV_HANDLE_INVALID

// *****************************************************************************
/* Media function pointers

  Summary:
    Structure of function pointers for media driver

  Description:
    This structure contains the definition for functions of media driver, which is
 * registered with the media maanger. In future, if any new driver needs to be
 * registered with the media manager (say, to act as a media for file system), the
 * new driver should have implemented all these functions.

  Remarks:
    None.
*/
typedef struct
{

    /* To obtains status of media */
    SYS_FS_MEDIA_STATUS (*mediaStatusGet)(DRV_HANDLE handle);
    /* Function for sector read */
    SYS_FS_MEDIA_BUFFER_HANDLE (*sectorRead)(DRV_HANDLE clientHandle,
                    uint8_t * buffer, uint32_t sectorStart, uint32_t nSector);
    /* Function for sector write */
    SYS_FS_MEDIA_BUFFER_HANDLE (*sectorWrite)(DRV_HANDLE clientHandle,
                    uint32_t sectorStart, uint8_t * buffer, uint32_t nSector);
    /* Function to obtain the buffer status */
    SYS_FS_MEDIA_BUFFER_STATUS (*bufferStatusGet)(DRV_HANDLE handle,
					SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle);
    /* Function to read certain bytes from the media */
    SYS_FS_MEDIA_BUFFER_HANDLE (*Read) ( const DRV_HANDLE hClient, uint8_t * destination,
                                uint8_t * source, const unsigned int nBytes);
    /* Functin to obtain the address of the media (to be used for NVM only) */
    uintptr_t (*addressGet) ( const DRV_HANDLE hClient);
    /* Function to open the media driver */
    DRV_HANDLE (*open)(SYS_MODULE_INDEX index, DRV_IO_INTENT intent);
    /* Function to close the media */
    void (*close)(DRV_HANDLE client);
    /* Task function of the media */
    void (*tasks)(SYS_MODULE_OBJ obj);

}
SYS_FS_MEDIA_FUNCTIONS;

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
);

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
);

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
);

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
);

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
);

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

bool SYS_FS_MEDIA_MANAGER_VolumePropertyGet
(
    const char *devName, SYS_FS_VOLUME_PROPERTY *str
);

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

SYS_FS_MEDIA_STATUS SYS_FS_MEDIA_MANAGER_MediaStatusGet
(
        const char *devName
);

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
( uint16_t diskNo, uint8_t* destination, uint8_t * source, const unsigned int nBytes );

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
);

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

void SYS_FS_MEDIA_MANAGER_Tasks ( void );

#endif
