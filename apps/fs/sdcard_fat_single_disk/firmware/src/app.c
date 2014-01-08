/*******************************************************************************
  SDCARD FAT Single Disk Demo Application

  File Name:
    app.c

  Summary:
    SDCARD FAT Single Disk Demo

  Description:
    This file contains the SDCARD FAT Single Disk Demo application logic.
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

 APP_DATA appData;

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObjects;


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************


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

void APP_Initialize ( void )
{
    /* Intialize the app state to wait for
     * media attach. */
    appData.state = APP_MOUNT_DISK;

}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Tasks ( void )
{
    /* The application task state machine */

    switch(appData.state)
    {
        case APP_MOUNT_DISK:
            if(SYS_FS_Mount("/dev/mmcblka1", "/mnt/myDrive", FAT, 0, NULL) != 0)
            {
                /* The disk could not be mounted. Try
                 * mounting again untill success. */

                appData.state = APP_MOUNT_DISK;
            }
            else
            {
                /* Mount was successful. Unmount the disk, for testing. */

                appData.state = APP_UNMOUNT_DISK;
            }
            break;

        case APP_UNMOUNT_DISK:
            if(SYS_FS_Unmount("/mnt/myDrive") != 0)
            {
                /* The disk could not be un mounted. Try
                 * un mounting again untill success. */

                appData.state = APP_UNMOUNT_DISK;
            }
            else
            {
                /* UnMount was successful. Mount the disk again */

                appData.state = APP_MOUNT_DISK_AGAIN;
            }
            break;

        case APP_MOUNT_DISK_AGAIN:
            if(SYS_FS_Mount("/dev/mmcblka1", "/mnt/myDrive", FAT, 0, NULL) != 0)
            {
                /* The disk could not be mounted. Try
                 * mounting again untill success. */

                appData.state = APP_MOUNT_DISK_AGAIN;
            }
            else
            {
                /* Mount was successful. Open a file for testing. */

                appData.state = APP_OPEN_FILE;
            }
            break;

        case APP_OPEN_FILE:

            appData.fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE_TOO_LONG_NAME_EXAMPLE_123.JPG",
                    (SYS_FS_FILE_OPEN_READ));
            if(appData.fileHandle == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                appData.fileHandle1 = SYS_FS_FileOpen("/mnt/myDrive/FILE_TOO_LONG_NAME_EXAMPLE_123_1.JPG",
                        (SYS_FS_FILE_OPEN_WRITE));
                if(appData.fileHandle1 == SYS_FS_HANDLE_INVALID)
                {
                    /* Could not open the file. Error out*/
                    appData.state = APP_ERROR;
                }
                else
                {
                    /* Read from one file and write to another file */
                    appData.state = APP_READ_WRITE_TO_FILE;
                }
            }
            break;

        case APP_READ_WRITE_TO_FILE:

            if(SYS_FS_FileRead((void *)appData.data, 512, appData.fileHandle) == -1)
            {
                /* There was an error while reading the file.
                 * Close the file and error out. */

                SYS_FS_FileClose(appData.fileHandle);
                appData.state = APP_ERROR;
            }
            else 
            {
                /* If read was success, try writing to the new file */
                if(SYS_FS_FileWrite((const void *)appData.data, 512, appData.fileHandle1) == -1)
                {
                    /* Write was not successful. Close the file
                     * and error out.*/
                    SYS_FS_FileClose(appData.fileHandle1);
                    appData.state = APP_ERROR;
                }
                else if(SYS_FS_FileEOF(appData.fileHandle) == 1)    /* Test for end of file */
                {
                    /* Continue the read and write process, untill the end of file is reached */
                    appData.state = APP_CLOSE_FILE;
                }
            }
            break;

        case APP_CLOSE_FILE:
            /* Close both files */
            SYS_FS_FileClose(appData.fileHandle);
            SYS_FS_FileClose(appData.fileHandle1);
             /* The test was successful. Lets idle. */
            appData.state = APP_IDLE;
            break;

        case APP_IDLE:
            /* The appliction comes here when the demo
             * has completed successfully. Switch on
             * green LED. */
            BSP_SwitchONSuccessLED();
            break;
        case APP_ERROR:
            /* The appliction comes here when the demo
             * has failed. Switch on the red LED.*/
            BSP_SwitchONFailureLED();
            break;
        default:
            break;

    }

} //End of APP_Tasks


/*******************************************************************************
 End of File
 */

