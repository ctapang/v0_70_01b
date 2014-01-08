/*******************************************************************************
  USB HOST functionality of Enumeration and Deenmeration devices.
  
  File Name:
    app.c

  Summary:
  This application validate the Host stack functionality Enumeration/Deenumeration
  of devices and attaching a best matching driver for these devices.

  Description:
 The main functionality of the Host stack is PNP ( plug and play )
 Dynamically attach and detach a drivers.
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

#include "app.h"

USB_HOST_SCSI_INIT usbHostScsiInit =
{
    .devName = "usb"
};
// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

/* This is the string that will written to the file */
const uint8_t writeData[13] = "Hello World";

 // *****************************************************************************
/* Application Data

  Summary:
    Contains application data

  Description:
    This structure contains application data.
 */

APP_DATA appData ;
USB_HOST_MSD_TRANSFER_HANDLE  txHandle , rxHandle ; 

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Initialize (APP_DATA * appData )
{
     appData->state = APP_STATE_OPEN_HOST_LAYER;
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Tasks ( APP_DATA * appData )
{
    /* The application task state machine */

    switch(appData->state)
    {
        case APP_STATE_OPEN_HOST_LAYER:

            /* Open the host layer and then enable Host layer operation */
            appData->hostHandle = USB_HOST_Open(USB_HOST_0, DRV_IO_INTENT_EXCLUSIVE);

            if (appData->hostHandle != USB_HOST_HANDLE_INVALID)
            {
                /* Host layer was opened successfully. Enable operation
                 * and then wait for operation to be enabled  */

                USB_HOST_OperationEnable(appData->hostHandle );
                appData->state = APP_STATE_WAIT_FOR_HOST_ENABLE;

            }
            else
            {
                /* Could not open host. Goto error state */
                appData->state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WAIT_FOR_HOST_ENABLE:

            /* Check if the host operation has been enabled */
            if(USB_HOST_OperationIsEnabled(appData->hostHandle))
            {
                /* This means host operation is enabled. We can 
                 * move on to the next state */

                appData->state = APP_STATE_WAIT_FOR_DEVICE_ATTACH;
            }

            break;
          
        case APP_STATE_WAIT_FOR_DEVICE_ATTACH:

            /* Wait for device attach. The state machine will move
             * to the next state when the attach event
             * is received.  */

            break;
            
           case APP_STATE_DEVICE_CONNECTED:

            
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_MOUNT_DISK;
          
            break;
 
        case  APP_STATE_MOUNT_DISK:
            if(SYS_FS_Mount("/dev/sda1", "/mnt/myDrive", FAT, 0, NULL) != 0)
            {
                /* The disk could not be mounted. Try
                 * mounting again untill success. */

                appData->state = APP_STATE_MOUNT_DISK;
            }
            else
            {
                /* Mount was successful. Unmount the disk, for testing. */
                  appData->state = APP_STATE_OPEN_FILE;
            }
            break;

        case APP_STATE_UNMOUNT_DISK:
            BSP_SwitchOFFLED(LED_2);
            if(SYS_FS_Unmount("/mnt/myDrive") != 0)
            {
                /* The disk could not be un mounted. Try
                 * un mounting again untill success. */

                appData->state = APP_STATE_UNMOUNT_DISK;
            }
            else
            {
                /* UnMount was successful. Mount the disk again */
                 appData->state =  APP_STATE_WAIT_FOR_DEVICE_ATTACH;
               
            }
            break;
        
        case APP_STATE_OPEN_FILE:

            appData->fileHandle = SYS_FS_FileOpen("/mnt/myDrive/File.txt",
                    (SYS_FS_FILE_OPEN_APPEND_PLUS));
            if(appData->fileHandle == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData->state = APP_STATE_ERROR;
            }
            else
            {
                   /* Could not open the file. Error out*/
                appData->state = APP_STATE_WRITE_TO_FILE;

            }
            break;

        case APP_STATE_WRITE_TO_FILE:

            /* If read was success, try writing to the new file */
            if (SYS_FS_FileWrite((const void *) writeData, 13,
                    appData->fileHandle) == -1)
            {
                /* Write was not successful. Close the file
                 * and error out.*/
                SYS_FS_FileClose(appData->fileHandle);
                appData->state = APP_STATE_ERROR;

            }
            else
            {
                appData->state = APP_STATE_CLOSE_FILE;
            }

            break;

        case APP_STATE_CLOSE_FILE:
            
            /* Close the file */
            SYS_FS_FileClose(appData->fileHandle);
          
             /* The test was successful. Lets idle. */
            appData->state = APP_STATE_IDLE;
            break;

        case APP_STATE_IDLE:

            /* The appliction comes here when the demo
             * has completed successfully. Switch on
             * green LED. */

            BSP_SwitchONLED(LED_2);
            break;

        case APP_STATE_ERROR:

            /* The appliction comes here when the demo
             * has failed. Switch on the red LED.*/

            BSP_SwitchONLED(LED_1);
            break;

        default:
            break;

    }

} //End of APP_Tasks


bool USB_HOST_MSD_ApplicationEventHandler(USB_HOST_MSD_INDEX index,
        USB_HOST_MSD_EVENT event, void* pData)
{
    switch ( event)
    {
        case USB_HOST_MSD_EVENT_ATTACH:
            
            USB_HOST_SCSI_Initialize(index , (SYS_MODULE_INIT  *) &usbHostScsiInit );
            appData.state =  APP_STATE_DEVICE_CONNECTED;
            break;

        case USB_HOST_MSD_EVENT_DETACH:

            USB_HOST_SCSI_DeInitialize(index ,(SYS_MODULE_INIT  *) &usbHostScsiInit );
            appData.state = APP_STATE_UNMOUNT_DISK;
            break;
       
        default:
            break;
    }

    return 0;
}


USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler
            (USB_HOST_EVENTS event, void * eventData, uintptr_t context)
{

     switch(event)
    {
        case USB_HOST_EVENT_VBUS_REQUEST_POWER:
            break;
        case USB_HOST_EVENT_UNSUPPORTED_DEVICE:
            break;

        case USB_HOST_EVENT_CANNOT_ENUMERATE:
            break;
    }
        return USB_HOST_EVENT_RESPONSE_NONE;
}

/*****************************  End of File ***********/

