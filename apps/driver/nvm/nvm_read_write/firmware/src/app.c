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

/*Let's reserve 16KB memory where NVM write and read
 operation will be performed
 In this example, we are reserving 16KB starting from flash
 memory address 0x9D004000
 */

uint8_t NVM_DATA_READ_BUFF[DRV_NVM_PAGE_SIZE] = {0};
const uint8_t NVM_DATA_FLASH_RESERVE[DRV_NVM_PAGE_SIZE*2]__attribute__((address(NVM_BASE_ADDRESS))) = {0};


uint8_t NVM_DATA_WRITE_BUFF[DRV_NVM_PAGE_SIZE] =
{
    1,2,3,4,5,6,7,8,9,10,
    11,12,13,14,15,16,17,18,19,20,
    21,22,23,24,25,26,27,28,29,30,
    31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,
    51,52,53,54,55,56,57,58,59,60,
    61,62,63,64,65,66,67,68,69,70,
    71,72,73,74,75,76,77,78,79,80,
    81,82,83,84,85,86,87,88,89,90,
    91,92,93,94,95,96,97,98,99,100,
    101,102,103,104,105,106,107,108,109,110,
    111,112,113,114,115,116,117,118,119,120,
    121,122,123,124,125,126,127,128,
    1,2,3,4,5,6,7,8,9,10,
    11,12,13,14,15,16,17,18,19,20,
};

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
    appData.state = APP_STATE_INIT;
    
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
*/

void APP_Tasks(void)
{        
    switch(appData.state)
    {
        case APP_STATE_INIT:
            
            appData.nvmHandle = DRV_NVM_Open(0, DRV_IO_INTENT_READWRITE);

            if(DRV_HANDLE_INVALID == appData.nvmHandle)
            {
                SYS_ASSERT(DRV_HANDLE_INVALID != appData.nvmHandle,
                    "Error Opening Driver");
                appData.state = APP_STATE_ERROR;
                break;
            }
            appData.state = APP_STATE_INIT_READ_NVM_DRV;
            break;

        case APP_STATE_INIT_READ_NVM_DRV:
            appData.nvmbufferHandle = DRV_NVM_Read(appData.nvmHandle,
                    NVM_DATA_READ_BUFF, (uint8_t*)NVM_BASE_ADDRESS, DRV_NVM_PAGE_SIZE);
            
            if(DRV_NVM_BUFFER_HANDLE_INVALID == appData.nvmbufferHandle)
            {
                SYS_ASSERT(false, "Driver Read Failed");
                appData.state = APP_STATE_ERROR;
                break;
            }
            appData.state = APP_STATE_NVM_ERASE;
            break;

        case APP_STATE_NVM_ERASE:
            appData.nvmbufferHandle = DRV_NVM_Erase(appData.nvmHandle,
                    (uint8_t*)NVM_BASE_ADDRESS, DRV_NVM_PAGE_SIZE);
            appData.state = APP_STATE_BUFF_STATUS_CHK;
            break;

        case APP_STATE_BUFF_STATUS_CHK:
            if(DRV_NVM_BUFFER_COMPLETED ==
               DRV_NVM_BufferStatus(appData.nvmHandle, appData.nvmbufferHandle))
            {
                appData.state = APP_STATE_WRITE_NVM_DRV;
            }
            break;

        case APP_STATE_WRITE_NVM_DRV:

            appData.nvmbufferHandle = DRV_NVM_Write(appData.nvmHandle, 
            (uint8_t *)(NVM_BASE_ADDRESS), (uint8_t *)NVM_DATA_WRITE_BUFF, NO_OF_BYTES_TO_WRITE);
            
            if(DRV_NVM_BUFFER_HANDLE_INVALID == appData.nvmbufferHandle)
            {
                SYS_ASSERT(false, "Driver Writing Failed");
                appData.state = APP_STATE_ERROR;
                break;
            }
            appData.state = APP_STATE_NVM_WRITE_STATUS;
            break;

        case APP_STATE_NVM_WRITE_STATUS:
            if(DRV_NVM_BUFFER_COMPLETED ==
               DRV_NVM_BufferStatus(appData.nvmHandle, appData.nvmbufferHandle))
            {
                appData.state = APP_STATE_READ_NVM_DRV;
            }
            break;

        case APP_STATE_READ_NVM_DRV:

            appData.nvmbufferHandle = DRV_NVM_Read(appData.nvmHandle, 
                    NVM_DATA_READ_BUFF, (uint8_t*)NVM_BASE_ADDRESS, NO_OF_BYTES_TO_READ);
            if(DRV_NVM_BUFFER_HANDLE_INVALID == appData.nvmbufferHandle)
            {
                SYS_ASSERT(false, "Driver Read Failed");
                appData.state = APP_STATE_ERROR;
                break;
            }
            appData.state = APP_STATE_NVM_READ_STATUS;
            break;

        case APP_STATE_NVM_READ_STATUS:
            if(DRV_NVM_BUFFER_COMPLETED == DRV_NVM_BufferStatus(
                    appData.nvmHandle, appData.nvmbufferHandle))
            {
                appData.state = APP_STATE_VERIFY;
            }
            break;

        case APP_STATE_VERIFY:

            if(strncmp(NVM_DATA_READ_BUFF, NVM_DATA_WRITE_BUFF, strlen(NVM_DATA_WRITE_BUFF)) != 0)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.state = APP_STATE_IDLE;
            }
            break;

        case APP_STATE_IDLE:
            BSP_SwitchONSuccessLED();
            break;

        case APP_STATE_ERROR:
            BSP_SwitchONFailureLED();
            break;

        default:
            break;
    }
}

/*******************************************************************************
 End of File
 */