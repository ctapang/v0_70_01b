/*******************************************************************************
  NVM FAT Single Disk Demo Application
  
  File Name:
    app.c

  Summary:
    NVM FAT Single Disk Demo

  Description:
    This file contains the NVM FAT Single Disk Demo application logic.
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

/* This string contins the original value of FILE.txt (before being written by the demo */
const uint8_t originalData[4] = "Data";

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
            if(SYS_FS_Mount("/dev/nvma1", "/mnt/myDrive", FAT, 0, NULL) != 0)
            {
                /* The disk could not be mounted. Try
                 * mounting again untill success. */

                appData.state = APP_MOUNT_DISK;
            }
            else
            {
                /* Mount was successful. Open a file.
                 * Let the switch case fall through. */
                appData.state = APP_OPEN_FILE;
            }
            break;

        case APP_OPEN_FILE:

            appData.fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.TXT", SYS_FS_FILE_OPEN_READ_PLUS);
            if(appData.fileHandle == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                /* Check the file status */
                appData.state = APP_READ_FILE_STAT;
            }
            break;

        case APP_READ_FILE_STAT:
            if( SYS_FS_FileStat("/mnt/myDrive/FILE.TXT", &appData.fileStatus ) == SYS_FS_RES_FAILURE )
            {
                /* Reading file status was a failure */
                appData.state = APP_ERROR;
            }
            else
            {
                /* Read file size */
                appData.state = APP_READ_FILE_SIZE;
            }
            break;

        case APP_READ_FILE_SIZE:
            appData.fileSize = SYS_FS_FileSize( appData.fileHandle );

            if(appData.fileSize == -1)
            {
                /* Reading file size was a failure */
                appData.state = APP_ERROR;
            }
            else
            {
                if(appData.fileSize == appData.fileStatus.fsize)
                {
                    appData.state = APP_DO_FILE_SEEK;
                }
                else
                    appData.state = APP_ERROR;
            }
            break;

        case APP_DO_FILE_SEEK:
            if(SYS_FS_FileSeek( appData.fileHandle, 4, SYS_FS_SEEK_SET ) == -1)
            {
                /* File seek caused an error */
                appData.state = APP_ERROR;
            }
            else
            {
                /* Check for End of file */
                appData.state = APP_CHECK_EOF;
            }
            break;

        case APP_CHECK_EOF:
            if(SYS_FS_FileEOF( appData.fileHandle ) == false )
            {
                /* Either, EOF is not reached or there was an error
                 In any case, for the application, its an error condition */
                appData.state = APP_ERROR;
            }
            else
            {
                appData.state = APP_DO_ANOTHER_FILE_SEEK;
            }
            break;

        case APP_DO_ANOTHER_FILE_SEEK:
            /* Move file pointer to begining of file */
            if(SYS_FS_FileSeek( appData.fileHandle, (-1 * appData.fileSize), SYS_FS_SEEK_END ) == -1)
            {
                /* File seek caused an error */
                appData.state = APP_ERROR;
            }
            else
            {
                /* Check for original file content */
                appData.state = APP_READ_ORIGINAL_FILE_CONTENT;
            }
            break;

        case APP_READ_ORIGINAL_FILE_CONTENT:
            if(SYS_FS_FileRead((void *)appData.data, 4, appData.fileHandle) == -1)
            {
                /* There was an error while reading the file.
                 * Close the file and error out. */

                SYS_FS_FileClose(appData.fileHandle);
                appData.state = APP_ERROR;
            }
            else
            {
                if(memcmp(appData.data, originalData, 4) != 0)
                {
                    /* The written and the read data dont
                     * match. */
                    appData.state = APP_ERROR;
                }
                else
                {
                    /* The test was successful. Lets do a file seek to move to begin of file . */
                    appData.state = APP_FINAL_FILE_SEEK;
                }

                break;
            }

        case APP_FINAL_FILE_SEEK:
            /* Move file pointer to begining of file */
            if(SYS_FS_FileSeek( appData.fileHandle, (-1 * appData.fileSize), SYS_FS_SEEK_END ) == -1)
            {
                /* File seek caused an error */
                appData.state = APP_ERROR;
            }
            else
            {
                /* Do a file write now */
                appData.state = APP_WRITE_TO_FILE;
            }
            break;

        case APP_WRITE_TO_FILE:
            if(SYS_FS_FileWrite((const void *)writeData, 13, appData.fileHandle) == -1)
            {
                /* Write was not successful. Close the file
                 * and error out.*/
                SYS_FS_FileClose(appData.fileHandle);
                appData.state = APP_ERROR;
            }
            else
            {
                /* Write was successful. Close the file and
                 * open again for read. */
                SYS_FS_FileClose(appData.fileHandle);
                appData.state = APP_OPEN_FOR_READ;
            }
            break;

        case APP_OPEN_FOR_READ:

            appData.fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.TXT", SYS_FS_FILE_OPEN_READ);
            if(appData.fileHandle == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                /* Try wrting to the file. Let the
                 * switch case fall through. */
                appData.state = APP_READ_VERIFY_FILE;
            }
            break;

        case APP_READ_VERIFY_FILE:

            if(SYS_FS_FileRead((void *)appData.data, 13, appData.fileHandle) == -1)
            {
                /* There was an error while reading the file.
                 * Close the file and error out. */

                SYS_FS_FileClose(appData.fileHandle);
                appData.state = APP_ERROR;
            }
            else
            {
                if(strcmp((const char *)appData.data, (const char *)writeData) != 0)
                {
                    /* The written and the read data dont
                     * match. */
                    appData.state = APP_ERROR;
                }
                else
                {
                    /* The test was successful. Lets idle. */
                    appData.state = APP_IDLE;
                }

                SYS_FS_FileClose(appData.fileHandle);
                break;
            }
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

