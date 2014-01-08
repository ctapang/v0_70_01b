/*******************************************************************************
  Sample Application

  File Name:
    app.c

  Summary:
    USART driver echo demo application

  Description:
    This file contains the USART driver echo demo application's implementation.
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

#include "system_config.h"
#include "system_definitions.h"
#include "app.h"
#include "system/system.h"
#include "driver/usart/drv_usart.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize( void )
{    
    /* Prepare a buffer object for transfer using the USART driver.  */
    appData.bufferObject.buffer     = appData.buffer;
    appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE, strlen(appData.buffer));
    appData.bufferObject.flags      = DRV_USART_BUFFER_FLAG_WRITE;
    appData.demoState               = APP_DISP_MSG_1;

    /* Place the App state machine in it's initial state. */
    appData.state = APP_INIT;
}

/*******************************************************************************
  Function:
    void APP_Tasks( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks( void )
{
    /* Status of USART driver */
    DRV_USART_CLIENT_STATUS usartStatus;

    /* Status of buffer submitted to USART */
    DRV_USART_BUFFER_STATUS bufferStatus;

    /* Check the application state*/
    switch ( appData.state )
    {
        /* Keep trying to open the driver until we succeed. */
        case APP_INIT:
        {
            /* open an instance of USART driver */
            appData.usartHandle = DRV_USART_Open(SYS_USART_DRIVER_INDEX,
                    DRV_IO_INTENT_READWRITE);
            
            if (appData.usartHandle != DRV_HANDLE_INVALID ) 
            {
                /* Update the state */
                UpdateTaskState();
            }
            else
            {
                appData.state = APP_ERROR;
            }
            break;
        }

        /* Send the message when the driver is ready. */
        case APP_WAIT_FOR_READY:
        {
            /* Get the USART driver status */
            usartStatus = DRV_USART_ClientStatus( appData.usartHandle );
            if ( usartStatus == DRV_USART_CLIENT_STATUS_READY )
            {                
                /* Submit buffer to USART */
                appData.usartBufferHandle = DRV_USART_BufferAdd(
                        appData.usartHandle, &appData.bufferObject);
                
                if ( appData.usartBufferHandle != DRV_HANDLE_INVALID )
                {
                    /* Buffer is accepted. Driver will transmit. */
                    appData.state = APP_WAIT_FOR_DONE;
                }
                else
                {
                    appData.state = APP_ERROR;
                }
            }
            break;

        }

        case APP_WAIT_FOR_DONE:
        {
            //Check buffer status
            bufferStatus = DRV_USART_BufferStatus(appData.usartHandle,
                    appData.usartBufferHandle);

            //Update task state if the buffer transfer is complete
            if ( DRV_USART_BUFFER_COMPLETED == bufferStatus )
            {
                UpdateTaskState();
            }
        }
        break;
        
        case APP_IDLE:
            /* The appliction comes here when the demo
             * has completed successfully. Switch on
             * LED 5. */
            BSP_SwitchONLED(LED_5);
            break;

        case APP_ERROR:
            /* The appliction comes here when the demo
             * has failed. Switch on the LED 9.*/
            BSP_SwitchONLED(LED_9);
            break;
            
        default:
            break;
    }
}

/*******************************************************************************
  Function:
    void UpdateTaskState( void )

  Remarks:
    See prototype in app.h.
 */


void UpdateTaskState(void)
{
    switch(appData.demoState)
    {
        case APP_DISP_MSG_1:
        {
            strcpy(appData.buffer, APP_MSG_1);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_DISP_MSG_2;
        }
        break;

        case APP_DISP_MSG_2:
        {
            strcpy(appData.buffer, APP_MSG_2);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_DISP_MSG_3;
        }
        break;

        case APP_DISP_MSG_3:
        {
            strcpy(appData.buffer, APP_MSG_3);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_DISP_MSG_4;
        }
        break;

        case APP_DISP_MSG_4:
        {
            strcpy(appData.buffer, APP_MSG_4);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_DISP_MSG_5;
        }
        break;

        case APP_DISP_MSG_5:
        {
            strcpy(appData.buffer, APP_MSG_1);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_RX_DATA;
        }
        break;

        case APP_RX_DATA:
        {
            strncpy(appData.buffer, "0", APP_NO_OF_BYTES_TO_READ);
            /* Update Buffer Size */
            appData.bufferObject.bufferSize = APP_NO_OF_BYTES_TO_READ;
            /* Switch to Read Mode */
            appData.bufferObject.flags = DRV_USART_BUFFER_FLAG_READ;
            /* Update application state */
            appData.state = APP_WAIT_FOR_READY;
            appData.demoState = APP_TX_DATA;
        }
        break;

        case APP_TX_DATA:
        {
            if(appData.buffer[0] == APP_ESC_MSG)
            {
                strcpy(appData.buffer, APP_MSG_5);
                /* Update Buffer Size */
                appData.bufferObject.bufferSize = min(APP_BUFFER_SIZE,
                            strlen(appData.buffer));
                appData.demoState = APP_DEMO_COMPLETE;
            }
            else
            {
                /* Update Buffer Size */
                appData.demoState = APP_RX_DATA;
            }
            appData.bufferObject.flags = DRV_USART_BUFFER_FLAG_WRITE;
            appData.state = APP_WAIT_FOR_READY;
        }
        break;

        case APP_DEMO_COMPLETE:
        {
            DRV_USART_Close( appData.usartHandle );
            DRV_USART_Deinitialize( appDrvObjects.drvUSARTObject );
            //Go to Idle mode
            appData.state = APP_IDLE;
        }
        break;
    }
}


/*******************************************************************************
 End of File
*/

