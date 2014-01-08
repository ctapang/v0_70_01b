 /*******************************************************************************
  USB CDC class definitions

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_cdc_local.h

  Summary:
    USB CDC class definitions

  Description:
    This file describes the CDC class specific definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _USB_HOST_SCSI_LOCAL_H
#define _USB_HOST_SCSI_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_host_msd.h"
#include "system/fs/sys_fs_media_manager.h"


typedef uintptr_t USB_HOST_SCSI_HANDLE;


#define USB_HOST_SCSI_HANDLE_INVALID /*DOM-IGNORE-BEGIN*/((USB_HOST_SCSI_HANDLE)(-1))/*DOM-IGNORE-END*/

typedef uintptr_t USB_HOST_SCSI_CLIENT_OBJ_HANDLE ;

typedef uintptr_t USB_HOST_SCSI_BUFFER_HANDLE;


#define _USB_HOST_SCSI_OBJ_GET(obj)    &gUsbHostScsiObj[obj];



typedef enum
{
    USB_HOST_SCSI_CMD_SUCCESS = 0 ,
    USB_HOST_SCSI_CMD_PENDING ,
    USB_HOST_SCSI_CMD_FAIL ,
    USB_HOST_SCSI_CMD_INVALID
} USB_HOST_SCSI_CMD_STATES ;



typedef enum
{

    /* Client in an invalid state */
    USB_HOST_SCSI_MEDIA_STATUS_INVALID = -1 ,
    /* Unspecified error condition */
    USB_HOST_SCSI_MEDIA_STATUS_ERROR = -2,
    /* Client is not open */
    USB_HOST_SCSI_MEDIA_STATUS_CLOSED = -3,
    /* An operation is currently in progress */
    USB_HOST_SCSI_MEDIA_STATUS_BUSY = -4,
    /* Up and running, no operations running */
    USB_HOST_SCSI_MEDIA_STATUS_READY  = 0,
    USB_HOST_SCSI_MEDIA_STATUS_STOPPED = -5

}USB_HOST_SCSI_MEDIA_STATUS;

//******************************************************************************
/* Function:
SYS_MODULE_OBJ USB_HOST_SCSI_Initialize ( const SYS_MODULE_INDEX    drvIndex,
                                      const SYS_MODULE_INIT     * const init )

  Summary:
    Initializes SCSI and register with Filesystem ,MSD module

  Description:


  Parameters:
    drvIndex        - Identifies the driver instance to be initialized.

    init            - Pointer to the data structure containing all data
                      necessary to initialize the hardware. This pointer may
                      be null if no data is required and static initialization
                      values are to be used.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.
*/

SYS_MODULE_OBJ USB_HOST_SCSI_Initialize ( const SYS_MODULE_INDEX    drvIndex,
                                      const SYS_MODULE_INIT     * const init );


//******************************************************************************
/* Function:
SYS_MODULE_OBJ USB_HOST_SCSI_DeInitialize ( const SYS_MODULE_INDEX    drvIndex,
                                      const SYS_MODULE_INIT     * const init )

  Summary:
    DeInitializes SCSI and unregister with Filesystem .

  Description:


  Parameters:
    drvIndex        - DeIdentifies the driver instance to be initialized.

    init            - Pointer to the data structure containing all data
                      necessary to deinitialize the FS.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.
*/

SYS_MODULE_OBJ USB_HOST_SCSI_DeInitialize ( const SYS_MODULE_INDEX    drvIndex,
                                      const SYS_MODULE_INIT     * const init );

// *****************************************************************************
/* Function:
    void USB_HOST_SCSI_Task( SYS_MODULE_OBJ obj)

  Summary:
    Scsi task will call the USB MSD Task

  Description:
    

  Precondition:
   File system will call this function

  Parameters:
    object      - Object handle for the specified scsi instance (returned from
                  USB_HOST_SCSI_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from USB_HOST_Initialize

    
        USB_HOST_Tasks (object);

        // Do other tasks
    
    </code>

  Remarks:
    This routine is normally not called directly by File System.
*/
void USB_HOST_SCSI_Task( SYS_MODULE_OBJ obj);

//******************************************************************************
/* Function:
   USB_HOST_SCSI_HANDLE USB_HOST_SCSI_Open( const SYS_MODULE_INDEX index,
                                         const DRV_IO_INTENT    intent )

  Summary:
    Opens the specific module instance and returns a handle

  Description:
    This routine opens a driver for use by any client module and provides a
    handle that must be provided to any of the other driver operations to
    identify the caller and the instance of the driver module.

  Parameters:
    drvIndex        - Identifier for the instance to be initialized
    ioIntent        - Possible values from the enumeration DRV_IO_INTENT

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance)
    If an error occurs, the return value is DRV_HANDLE_INVALID
*/

USB_HOST_SCSI_HANDLE USB_HOST_SCSI_Open( const SYS_MODULE_INDEX index,
                                         const DRV_IO_INTENT    intent );
										 
										 //*****************************************************************************
/* Function:
SYS_FS_MEDIA_BUFFER_STATUS USB_HOST_SCSI_BufferStatusGet ( DRV_HANDLE handle,
					SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle )

  Summary:
    Gets the status of USB MSD command operation (read/write)

  Description:
	This function gets the status of USB MSD command operation.
	To be called only after a read or write is scheduled.

  Precondition:
      USB_HOST_SCSI_Open must have been called to obtain a valid opened device
	handle.

  Parameters:
	handle - A valid open-instance handle, returned from the driver's
				open routine

	bufferHandle - Handle returned by a 'sector write' or a 'sector read'
				function.

  Returns:
    SYS_FS_MEDIA_BUFFER_STATUS - Buffer status.

  Example:
    <code>
    int globalState = 0;
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle;

	switch (globalState)
	{
		case 0:
			bufferHandle = SYS_FS_MEDIA_MANAGER_SectorWrite ( handle,
									,readData //buffer
									, 20 // Sector
									, 1 // Number of Sectors
									);
			globalState++;
			break;
		case 1:
			if ( SYS_FS_MEDIA_MANAGER_BufferStatusGet(handle, bufferHandle) ==
						SYS_FS_MEDIA_BUFFER_COMPLETED)
			{
				//Write complete
			}
			break;
    </code>

  Remarks:
	None.
*/

SYS_FS_MEDIA_BUFFER_STATUS USB_HOST_SCSI_BufferStatusGet ( DRV_HANDLE handle,
					SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle );
					
					
					// *****************************************************************************
/* Function:
	SYS_FS_MEDIA_STATUS USB_HOST_SCSI_MediaStatusGet ( DRV_HANDLE handle )

  Summary:
    Gets the status of the MSD device.

  Description:
	This function gets the status of the MSD device ( attached/detached ).

  Precondition:
    The USB_HOST_SCSI_Initialize routine must have been called.

    USB_HOST_SCSI_Open must have been called to obtain a valid opened device
	handle.

  Parameters:
	handle - A valid open-instance handle, returned from the driver's
				open routine

  Returns:
    SYS_FS_MEDIA_STATUS - Status of the device.

  Example:
    <code>
    DRV_HANDLE sdcardHandle;  // Returned from DRV_SDCARD_Open

    if( USB_HOST_SCSI_MediaStatusGet ( handle ) == SYS_FS_MEDIA_ATTACHED )
	{
		//Device is attached
	}

    </code>

  Remarks:
	None.

*/
SYS_FS_MEDIA_STATUS USB_HOST_SCSI_MediaStatusGet ( DRV_HANDLE handle );

// *****************************************************************************
/* Function:
   USB_HOST_SCSI_BUFFER_HANDLE USB_HOST_SCSI_SectorRead ( USB_HOST_SCSI_HANDLE handle,
                                                        uint8_t *buffer,
                                                        uint32_t sectorAddr,
                                                        uint32_t sectorCount )
  Summary:
    Reads data from the sectors of the MSD device.

  Description:
	This function reads data from the sectors of the MSD device starting from
        the sector address and stores it in the location pointed by 'buffer'.

  Precondition:
    The USB_HOST_SCSI_Initialize routine must have been called.

    USB_HOST_SCSI_Open must have been called to obtain a valid opened device
	handle.

  Parameters:
	handle - A valid open-instance handle, returned from the driver's
				open routine

	sector_addr - The address of the sector on the card.

	sectorCount - Number of sectors to be read.

	buffer -  The buffer where the retrieved data will be stored.  If
				buffer is NULL, do not store the data anywhere.

  Returns:
    SYS_FS_MEDIA_BUFFER_HANDLE - Buffer handle.

  Example:
    <code>
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle;

    bufferHandle = DRV_SDCARD_SectorRead ( handle,readData //buffer
 					, 20 //  Sector
        				, 1 // Number of Sectors
					);

    </code>

  Remarks:
    
*/
USB_HOST_SCSI_BUFFER_HANDLE USB_HOST_SCSI_SectorRead ( USB_HOST_SCSI_HANDLE handle,
                                                        uint8_t *buffer,
                                                        uint32_t sectorAddr,
                                                        uint32_t sectorCount );
														
														// *****************************************************************************
/* Function:
USB_HOST_SCSI_BUFFER_HANDLE USB_HOST_SCSI_SectorWrite ( DRV_HANDLE handle,
                                                        uint32_t sectorAddr,
                                                        uint8_t *buffer,
                                                        uint32_t sectorCount )

  Summary:
    Writes sector(s) of data to MSD.

  Description:
	This function writes sector(s) of data (512 bytes) of data from the
	location pointed to by 'buffer' to the specified sector of the MSD.

  Precondition:
    The USB_HOST_SCSI_Initialize routine must have been called.

    USB_HOST_SCSI_Open must have been called to obtain a valid opened device
	handle.

  Parameters:
	handle - A valid open-instance handle, returned from the driver's
				open routine

	sector_addr - The address of the sector on the MSD.

	buffer -  The buffer with the data to write.

  Returns:
    SYS_FS_MEDIA_BUFFER_HANDLE - Buffer handle.

  Example:
    <code>
    SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle;

	bufferHandle = DRV_SDCARD_SectorWrite ( handle, readData //buffer
						, 20 // Sector
					        , 1 // Number of Sectors
						);
    </code>

  Remarks:
	

*/
USB_HOST_SCSI_BUFFER_HANDLE USB_HOST_SCSI_SectorWrite ( DRV_HANDLE handle,
                                                        uint32_t sectorAddr,
                                                        uint8_t *buffer,
                                                        uint32_t sectorCount );
														// *****************************************************************************
/* Function:
    void USB_HOST_SCSI_Close(USB_HOST_SCSI_HANDLE handle )

  Summary:
    Closes an opened-instance of the SCSI instance

  Description:
    This routine closes an opened-instance of the MSD, invalidating
    the handle.

  Precondition:
    The USB_HOST_SCSI_Initialize routine must have been called for the specified
    Scsi driver instance.

    USB_HOST_SCSI_Open must have been called to obtain a valid opened device
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None

  Example:
    <code>
    USB_HOST_SCSI_HANDLE handle;  // Returned from DRV_SDCARD_Open

    USB_HOST_SCSI_Close ( handle );
    </code>

  Remarks:
  
*/

void USB_HOST_SCSI_Close(USB_HOST_SCSI_HANDLE handle );


typedef struct _USB_HOST_SCSI_OBJ_
{
    USB_HOST_SCSI_HANDLE  scsiHandle;
    SYS_FS_MEDIA_HANDLE   fsHandle;
    uint8_t               physicalDriveNumber;

     /* Flag to indicate in use  */
    bool                            inUse;
     /* Different states in sending a command */
    USB_HOST_SCSI_CMD_STATES           cmdState;
    /* The status of the scsi obj*/
    USB_HOST_SCSI_MEDIA_STATUS     status;


}USB_HOST_SCSI_OBJ;


typedef struct _USB_HOST_PHYSICAL_DRIVE_INFO
{
    uint8_t  driveNumber;
    uint8_t  NoOfPartitions;
    uint8_t  openCount;
    uint32_t cylinders;
    uint32_t sectors;
    uint32_t capacity;
    uint8_t  driveId;  // MSD will assign


}USB_HOST_PHYSICAL_DRIVE_INFO;







typedef struct _USB_HOST_MSD_DEVICE_INFO
{
    uint16_t   deviceConfiguration;
    uint16_t   numberOfCylinders;
    uint16_t   reseved0;
    uint16_t   numberOflogicalHeads;
    uint16_t   retire0[2];
    uint16_t   numberOfsectorsInTrack;
    uint16_t   retire1[3];
    uint8_t    serialNumber[20];
    uint16_t   retire[2];
    uint16_t   obsolete;
    uint8_t    firmwareVersion;
    uint8_t    modelNumber[40];
    uint8_t    readWrireSupport;
    uint16_t   reserved3;
    uint16_t   capability[2];
    uint16_t   pioMode;
    uint16_t   retire4;
    uint16_t   fieldValid;
    uint16_t   noOfLogicalCylinders;
    uint16_t   currentLogicalHead;
    uint16_t   noOfcurrentLogicalSectors;
    uint16_t   capacityInsector;
    uint16_t   multisector;
    uint16_t   addressableSectors;
    uint16_t   retire5;
    uint16_t   advancePIOmode;
    uint16_t   reserved[191];


}USB_HOST_MSD_DEVICE_INFO;


/* scsi commands */
#define    USB_HOST_SCSI_FORMAT_COMMAND        0x04  // Format
#define    USB_HOST_SCSI_READ6_COMMAND        0x08   // Read
#define    USB_HOST_SCSI_READ10_COMMAND        0x28  // Read
#define    USB_HOST_SCSI_WRITE6_COMMAND        0x0A  // write
#define    USB_HOST_SCSI_WRITE10_COMMAND        0x2A  // write
#define    USB_HOST_SCSI_SEEK6_COMMAND          0x0B  // track access
#define    USB_HOST_SCSI_SEEK10_COMMAND        0x2B  // track access



 /* SCSI Transparent Command Set Sub-class code */
#define USB_MSD_INQUIRY 				0x12
#define USB_MSD_READ_FORMAT_CAPACITY 			0x23
#define USB_MSD_READ_CAPACITY 					0x25
#define USB_MSD_READ_10 						    0x28
#define USB_MSD_WRITE_10 						0x2a
#define USB_MSD_REQUEST_SENSE 					0x03
#define USB_MSD_MODE_SENSE  					    0x1a
#define USB_MSD_PREVENT_ALLOW_MEDIUM_REMOVAL                0x1e
#define USB_MSD_TEST_UNIT_READY 				    0x00
#define USB_MSD_VERIFY 						    0x2f
#define USB_MSD_STOP_START 						0x1b

/* command status */
#define    USB_HOST_SCSI_COMMAND_SUCCESS         0x00
#define    USB_HOST_SCSI_COMMAND_FAIL            0x02  //command fail, send request sense
#define    USB_HOST_SCSI_BUSY                    0x08  // Busy

#define USB_HOST_MSD_MAX_PHYSICAL_DRIVE    1
#define USB_HOST_SCSI_MAX_INSTANCES        2


/* Error */
#define USB_HOST_DRIVE_NUMBER_INVALID  -1
#define USB_HOST_DRIVE_MAP_INVALID     -2


typedef struct _USB_HOST_SCSI_INIT
{
        /* Disk Name to be used by the application */
    const char *                        devName;

}USB_HOST_SCSI_INIT;



 USB_HOST_SCSI_BUFFER_HANDLE  _USB_HOST_SCSI_ReadAndWite ( uint8_t physicalDriveNumber ,
                                                          uint32_t sectorNumber,
                                                          uint32_t noOfSectors,
                                                          uint8_t direction,
                                                          uint8_t *buffer );

 USB_HOST_SCSI_BUFFER_HANDLE _USB_HOST_SCSI_processCommand(uint8_t driveNumber);
bool USB_HOST_SCSI_EventHandler(USB_HOST_MSD_INSTANCE index,
        USB_HOST_MSD_EVENT event, void* pData);

 USB_ERROR  USB_HOST_SCSI_testUintReadyCommand (  uint8_t physicalDriveNumber );

#endif

 /************ End of file *************************************/
