/*******************************************************************************
 USB Host scsi Driver Definition

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_scsi.c

  Summary:
    USB Host scsi driver dynamic implementation

  Description:
    USB MSD scsi driver is simple interface to manage the SCSI device
    modules on Microchip microcontrollers.  This file Implements the core
    interface routines for the SCSI driver.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "usb/usb_host_scsi.h"
#include "system/fs/sys_fs_media_manager.h"

// *****************************************************************************
/* SCSI media functions.

  Summary:
    These functions are used by the 'media manager' to access the USB thumbdrive.

  Description:
	These functions are used by the 'media manager' to access the Scsi media. The
	call will be by using a function pointer. So scsi driver must attach these
	functions to the media manager on initialize.

  Remarks:
    None.
*/

SYS_FS_MEDIA_FUNCTIONS scsiUSBMediaFunctions =
{
    .mediaStatusGet     = USB_HOST_SCSI_MediaStatusGet,
    .sectorRead         = USB_HOST_SCSI_SectorRead,
    .sectorWrite        = USB_HOST_SCSI_SectorWrite,
    .bufferStatusGet    = USB_HOST_SCSI_BufferStatusGet,
    .open               = USB_HOST_SCSI_Open,
    .close              = USB_HOST_SCSI_Close,
    .tasks              = USB_HOST_SCSI_Task,
};

// *****************************************************************************
/* Driver Hardware instance objects.

  Summary:
    Defines the hardware instances objects that are available on the part

  Description:
    This data type defines the hardware instance objects that are available on
    the part, so as to capture the hardware state of the instance.

  Remarks:
    Not all modes are available on all micro-controllers.
*/

USB_HOST_SCSI_OBJ gUsbHostScsiObj[USB_HOST_MSD_MAX_PHYSICAL_DRIVE];

// *****************************************************************************
/* Command Block for each physical drive.

  Summary:
    command Block used by subclass

  Description:
    This command Block data uses by subclass transfer the data to across the usb.

  Remarks:
    Not all modes are available on all micro-controllers.
*/
USB_MSD_COMMAND  commandBlock[USB_HOST_MSD_MAX_PHYSICAL_DRIVE];

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
                                      const SYS_MODULE_INIT     * const init )
{
    USB_HOST_SCSI_INIT *usbHostScsiInit = NULL;
    usbHostScsiInit = ( USB_HOST_SCSI_INIT *)init ;
    USB_HOST_SCSI_OBJ   *scsiObj ;
    SYS_FS_MEDIA_HANDLE  fsHandle;

     /* Validate the driver index */
    if (  drvIndex  >= USB_HOST_SCSI_INSTANCES_NUMBER )
    {
        return SYS_MODULE_OBJ_INVALID;
    }
    scsiObj = _USB_HOST_SCSI_OBJ_GET(drvIndex) ;

   // SYS_ASSERT( gUsbHostScsiObj[drvIndex].inUse == false,
     //                                           "Instance already in use" );
    fsHandle = SYS_FS_MEDIA_MANAGER_Register ( (SYS_MODULE_OBJ) scsiObj,
                                        drvIndex ,
					&scsiUSBMediaFunctions,
					SYS_FS_MEDIA_TYPE_MSD );
    gUsbHostScsiObj[drvIndex].inUse = 0x01;
    gUsbHostScsiObj[drvIndex].fsHandle = fsHandle;
    gUsbHostScsiObj[drvIndex].status = USB_HOST_SCSI_MEDIA_STATUS_CLOSED ;
     /* Return the object structure */
    return ( ( SYS_MODULE_OBJ ) drvIndex );
}

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
                                      const SYS_MODULE_INIT     * const init )
{
    USB_HOST_SCSI_INIT *usbHostScsiInit = NULL;
    usbHostScsiInit = ( USB_HOST_SCSI_INIT *)init ;
    USB_HOST_SCSI_OBJ   *scsiObj ;
    USB_HOST_SCSI_HANDLE scsiHandle;

    SYS_FS_MEDIA_HANDLE fsHandle;

    fsHandle = gUsbHostScsiObj[drvIndex].fsHandle;
     /* Validate the driver index */
    if (  drvIndex  >= USB_HOST_SCSI_INSTANCES_NUMBER )
    {
        return SYS_MODULE_OBJ_INVALID;
    }

    scsiObj = _USB_HOST_SCSI_OBJ_GET(drvIndex) ;

    scsiHandle = (USB_HOST_SCSI_HANDLE )&gUsbHostScsiObj[drvIndex];

    SYS_FS_MEDIA_MANAGER_DeRegister ( fsHandle );

    USB_HOST_SCSI_Close(scsiHandle );

    gUsbHostScsiObj[drvIndex].inUse = 0x00;

    gUsbHostScsiObj[drvIndex].status = USB_HOST_SCSI_MEDIA_STATUS_CLOSED ;
     /* Return the object structure */
    return ( ( SYS_MODULE_OBJ ) drvIndex );

}


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
void USB_HOST_SCSI_Task( SYS_MODULE_OBJ obj)
{
    uint8_t drvIndex;

    drvIndex = (uint8_t ) obj;
    USB_HOST_MSD_Tasks();

}
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
                                         const DRV_IO_INTENT    intent )
{
    uint8_t count;
    USB_HOST_SCSI_HANDLE scsiHandle ;
    USB_HOST_SCSI_OBJ   *usbHostScsiInstance;

     /* Make sure the index is with in range. */
    SYS_ASSERT( ( ( index >= 0 ) && ( index <= USB_HOST_SCSI_MAX_INSTANCES ) ),
                   " USB HOST scsi : Invalid index or value assigned to\
                     USB_HOST_SCSI_MAX_INSTANCES ");
    for(count = 0 ; count < USB_HOST_SCSI_MAX_INSTANCES ; count++  )
    {
        /* Copy this local obj. */
        usbHostScsiInstance = (USB_HOST_SCSI_OBJ *)&gUsbHostScsiObj[index];
     
         /* Check if the instance is initialized. */
         if(  usbHostScsiInstance->inUse ==  1 )
       {
             usbHostScsiInstance->status = USB_HOST_SCSI_MEDIA_STATUS_READY ;
             usbHostScsiInstance->physicalDriveNumber = index;
             scsiHandle = (USB_HOST_SCSI_HANDLE )usbHostScsiInstance;
             //USB_HOST_SCSI_testUintReadyCommand (  usbHostScsiInstance->physicalDriveNumber );
             return scsiHandle ;
        }
    }
     return USB_HOST_SCSI_HANDLE_INVALID;
}

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
					SYS_FS_MEDIA_BUFFER_HANDLE bufferHandle )
{
    USB_HOST_SCSI_OBJ   *usbHostScsiInstance;
    usbHostScsiInstance =  (USB_HOST_SCSI_OBJ   *) handle;
    usbHostScsiInstance->cmdState =
                        ( ( USB_MSD_COMMAND * ) bufferHandle )->commandStatus;
      return ( usbHostScsiInstance->cmdState );
}

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
SYS_FS_MEDIA_STATUS USB_HOST_SCSI_MediaStatusGet ( DRV_HANDLE handle )
{
    USB_HOST_SCSI_OBJ   *usbHostScsiInstance;
    usbHostScsiInstance =  (USB_HOST_SCSI_OBJ   *) handle;

    if( usbHostScsiInstance->status == USB_HOST_SCSI_MEDIA_STATUS_READY )
           return SYS_FS_MEDIA_ATTACHED ;
    else
       return SYS_FS_MEDIA_DETACHED; 
 }

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
                                                        uint32_t sectorCount )
{
    USB_HOST_SCSI_OBJ *usbHostScsiInstance;
    usbHostScsiInstance = (USB_HOST_SCSI_OBJ *) handle;
    return ( _USB_HOST_SCSI_ReadAndWite(usbHostScsiInstance->physicalDriveNumber,
            sectorAddr,sectorCount, 1, buffer));
}

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
                                                        uint32_t sectorCount )
{
    USB_HOST_SCSI_OBJ *usbHostScsiInstance;
    usbHostScsiInstance = (USB_HOST_SCSI_OBJ *) handle;
    return ( _USB_HOST_SCSI_ReadAndWite(usbHostScsiInstance->physicalDriveNumber,
            sectorAddr, sectorCount, 0, buffer));
}

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

void USB_HOST_SCSI_Close(USB_HOST_SCSI_HANDLE handle )
{
    USB_HOST_SCSI_OBJ *usbHostScsiInstance;
    usbHostScsiInstance = (USB_HOST_SCSI_OBJ *) handle;
        /* Check the valid handle. */
    SYS_ASSERT( ( USB_HOST_HANDLE_INVALID != handle ),"Invalid client handle");
     usbHostScsiInstance->inUse = 0x00;
    /* close the handle. */
    usbHostScsiInstance->status = USB_HOST_SCSI_MEDIA_STATUS_CLOSED;
}

//******************************************************************************
/* Function:
USB_HOST_SCSI_BUFFER_HANDLE  _USB_HOST_SCSI_ReadAndWite ( uint8_t physicalDriveNumber ,
                                                          uint32_t sectorNumber,
                                                          uint32_t noOfSectors,
                                                          uint8_t direction,
                                                          uint8_t *buffer )

  Summary:
   This function convert the data into MSD command format

  Description:


  Parameters:
        physicalDriveNumber - drver number

	sector_addr - The address of the sector on the MSD.

	buffer -  The buffer with the data to write.

  Returns:
    If successful, returns a valid handle to a buffer status handle.
    Otherwise, it returns invalid buffer handle .
*/

USB_HOST_SCSI_BUFFER_HANDLE  _USB_HOST_SCSI_ReadAndWite ( uint8_t physicalDriveNumber ,
                                                          uint32_t sectorNumber,
                                                          uint32_t noOfSectors,
                                                          uint8_t direction,
                                                          uint8_t *buffer )
 {
     uint8_t command[10];
       /* Validate the drive number */
    if ( physicalDriveNumber > USB_HOST_MSD_MAX_PHYSICAL_DRIVE )
        return USB_HOST_DRIVE_NUMBER_INVALID;
    if ( direction == 0x01 )          //Read
    {
        command[0] = USB_HOST_SCSI_READ10_COMMAND;
    }
    else
    {
        /* write command */
        command[0] = USB_HOST_SCSI_WRITE10_COMMAND;
    }
     /* Fill the command */
     command[1] = 0x00;
     command[2] = (uint8_t ) ( sectorNumber >> 24 );
     command[3] = (uint8_t ) (sectorNumber >> 16 );
     command[4] = (uint8_t ) (sectorNumber >> 8 );
     command[5] = (uint8_t ) sectorNumber;
     command[6] = 0x00;
     command[7] = (uint8_t  ) (noOfSectors >> 8 );
     command[8] = (uint8_t  ) noOfSectors ;
     command[9] = 0x00;

    commandBlock[physicalDriveNumber].command = command;
    commandBlock[physicalDriveNumber].commandLength = 0x0A;
    commandBlock[physicalDriveNumber].data = buffer;
    commandBlock[physicalDriveNumber].length = noOfSectors * 0x200;
    commandBlock[physicalDriveNumber].direction = direction;

    return( _USB_HOST_SCSI_processCommand(physicalDriveNumber));
 
 }

//******************************************************************************
/* Function:
USB_HOST_SCSI_BUFFER_HANDLE _USB_HOST_SCSI_processCommand(uint8_t driveNumber)

  Summary:
   This function process the command to MSD to tranfer

  Description:


  Parameters:
        physicalDriveNumber - drver number

  Returns:
    Returns the Buffer status handle .
*/
 USB_HOST_SCSI_BUFFER_HANDLE _USB_HOST_SCSI_processCommand(uint8_t driveNumber)
 {
     commandBlock[driveNumber].commandStatus = 0x01;
     USB_HOST_MSD_Transfer( driveNumber , &commandBlock[driveNumber] );
     return ( (USB_HOST_SCSI_BUFFER_HANDLE)  &commandBlock[driveNumber]);

 }

 //******************************************************************************
/* Function:
 USB_ERROR  USB_HOST_SCSI_identifyCommand ( USB_HOST_MSD_DEVICE_INFO *deviceInfo,
                                            uint8_t physicalDriveNumber )

  Summary:
   This function is to identify the deviceinfo based on drivenumber
   inquiry device Informatio

  Description:


  Parameters:
        physicalDriveNumber - drver number

  Returns:
    Returns the Device information about size ( bootsector information ) .
*/
/*******************************************************************************/

 USB_ERROR  USB_HOST_SCSI_identifyCommand ( USB_HOST_MSD_DEVICE_INFO *deviceInfo,
                                            uint8_t physicalDriveNumber )
 {
    uint8_t  command[6];

    /* inquiry device Informatio */
    command[0] = USB_MSD_INQUIRY;
    command[1] = 0x00;
    command[2] = 0x00;
    command[3] = 0x00;
    command[4] = 0x24;
    command[5] = 0x00;

    commandBlock[physicalDriveNumber].command = command;
    commandBlock[physicalDriveNumber].commandLength = 0x06;
    commandBlock[physicalDriveNumber].data = deviceInfo;
    commandBlock[physicalDriveNumber].length = 0x24;
    commandBlock[physicalDriveNumber].direction = 0x01;

    _USB_HOST_SCSI_processCommand(physicalDriveNumber);

    return USB_ERROR_NONE ;

 }
 //******************************************************************************
/* Function:
 USB_ERROR  USB_HOST_SCSI_testUintReadyCommand (  uint8_t physicalDriveNumber )

  Summary:
  Test unit ready command to identify the device status.

  Description:


  Parameters:
        physicalDriveNumber - drver number

  Returns:
    Returns the Device status information.
*/
/*******************************************************************************/
 USB_ERROR  USB_HOST_SCSI_testUintReadyCommand (  uint8_t physicalDriveNumber )
  {
   
      uint8_t command[6];
      /* Set the command*/
    command[0] = USB_MSD_TEST_UNIT_READY;    /*Test Unit Ready Command */
    command[1] = 0x00;
    command[2] = 0x00;
    command[3] = 0x00;
    command[4] = 0x00;
    command[5] = 0x00;
    commandBlock[physicalDriveNumber].command = command;
    commandBlock[physicalDriveNumber].commandLength = 0x06;
    commandBlock[physicalDriveNumber].direction = 0x01;
    commandBlock[physicalDriveNumber].length = 0x00;
    _USB_HOST_SCSI_processCommand(physicalDriveNumber);
    return USB_ERROR_NONE;
  }




/************************** EOF *********************************************/







