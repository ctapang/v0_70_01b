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

/* This string is already present in a file in the disk image */
const uint8_t compareString[] = "1234567890";
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
            if(SYS_FS_Mount("/dev/nvma1", "/mnt/myDrive", MPFS2, 0, NULL) != 0)
            {
                /* The disk could not be mounted. Try
                 * mounting again untill success. */

                appData.state = APP_MOUNT_DISK;
            }
            else
            {
                /* Mount was successful. opens
                 * the first file */
                appData.state = APP_OPEN_FILE_1;
            }
            break;

        case APP_OPEN_FILE_1:
            appData.fileHandle_1 = SYS_FS_FileOpen("/mnt/myDrive/FILE.TXT", SYS_FS_FILE_OPEN_READ);
            if(appData.fileHandle_1 == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                /* If first file was opened successfully, open the second file */
                appData.state = APP_OPEN_FILE_2;
            }
            break;

        case APP_OPEN_FILE_2:
            appData.fileHandle_2 = SYS_FS_FileOpen("/mnt/myDrive/TEST.txt", SYS_FS_FILE_OPEN_READ);
            if(appData.fileHandle_2 == SYS_FS_HANDLE_INVALID)
            {
                /* Could not open the file. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                /* If first file was opened successfully, check status of 3rd file */
                appData.state = APP_CHECK_FILE_3_STAT;
            }
            break;

        case APP_CHECK_FILE_3_STAT:
            if(SYS_FS_FileStat("/mnt/myDrive/ABC.txt", &appData.fileStatus) == SYS_FS_RES_FAILURE)
            {
                /* Could not read the file staus. Error out*/
                appData.state = APP_ERROR;
            }
            else
            {
                /* While creating the MPFS disk image, the file ABC.txt was chose to be of the following size */
                if(appData.fileStatus.fsize != 31744)
                {
                    /* reading file status had been wrong somewhere  */
                    appData.state = APP_ERROR;
                }
                else
                {
                    /* If status read was success, then do a file size check */
                    appData.state = APP_DO_FILE_SIZE_CHECK;
                }
            }
            break;
            
        case APP_DO_FILE_SIZE_CHECK:
            if(SYS_FS_FileSize(appData.fileHandle_1) != 11)
            {
                /* File size check went wrong somewhere  */
                appData.state = APP_ERROR;                  
            }
            else
            {
                /* If status read was success, then do a file seek */
                appData.state = APP_DO_FILE_SEEK;                
            }
            /* We are done with this file, hence close it */
            SYS_FS_FileClose(appData.fileHandle_1);
            break;

        case APP_DO_FILE_SEEK:
            if(SYS_FS_FileSeek(appData.fileHandle_2, -10, SYS_FS_SEEK_END) != -10)
            {
                /* File seek went wrong somewhere  */
                appData.state = APP_ERROR;
            }
            else
            {
                /* Compare the remaining file content with a known string */
                appData.state = APP_READ_VERIFY_CONTENT;
            }
            break;

        case APP_READ_VERIFY_CONTENT:
            if(SYS_FS_FileRead((void *)appData.data, 10, appData.fileHandle_2) == -1)
            {
                /* There was an error while reading the file.
                 * Close the file and error out. */

                SYS_FS_FileClose(appData.fileHandle_2);
                appData.state = APP_ERROR;
                break;
            }
            else
            {
                if(strncmp((const char *)appData.data, (const char *)compareString, 10) != 0)
                {
                    /* The written and the read data dont
                     * match. */
                    appData.state = APP_ERROR;
                }
                else
                {
                    /* The test was successful. Lets idle. */
                    appData.state = APP_CHECK_EOF;
                }
                break;
            }
        case APP_CHECK_EOF:
            /* By now, we should have reached end of file */
            if(SYS_FS_FileEOF(appData.fileHandle_2) != true)
            {
                /* Error */
                appData.state = APP_ERROR;
            }
            else
            {
                /* We have completed all tests. Hence go to idle state */
                appData.state = APP_IDLE;
            }

        case APP_IDLE:
            /* The appliction comes here when the demo
             * has completed successfully. Switch on
             * green LED. */
            SYS_FS_FileClose(appData.fileHandle_2);
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

