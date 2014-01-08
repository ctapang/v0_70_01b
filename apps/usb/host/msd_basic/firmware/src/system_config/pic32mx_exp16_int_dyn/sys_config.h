/*******************************************************************************
  CDC Basic Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:    
    sys_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the CDC Basic demo
    application for the PIC32 USB starter kit.
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

#ifndef _SYS_CONFIG_H    
#define _SYS_CONFIG_H



// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_INSTANCES_NUMBER  			1
#define DRV_USB_CLIENTS_NUMBER  			1
#define DRV_USB_INDEX  						DRV_USB_INDEX_0
#define DRV_USB_INTERRUPT_MODE  			true
#define DRV_USB_HOST_SUPPORT		 	true
#define DRV_USB_DEVICE_SUPPORT	 		false
#define DRV_USB_HOST_PIPES_NUMBER 			15
#define DRV_USB_HOST_IRP_PER_FRAME_NUMBER 	        5
#define DRV_USB_HOST_IRP_NUMBER 			5
#define DRV_USB_ENDPOINTS_NUMBER			1
#define DRV_USB_HOST_NAK_LIMIT				2000

//#endif // #ifndef _DRV_USB_CONFIG_H
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

#define _DEFAULT    (0x01<<7)       //Default Value (Bit 7 is set)
#define _SELF       (0x01<<6)       //Self-powered (Supports if set)

// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* EP0 buffer size. Used by controller driver */
#define USB_EP0_BUFF_SIZE 64

// *****************************************************************************
/* USB hardware instance configuration

  Summary:
    Selects the maximum number of hardware instances that can be supported by
    the dynamic driver

  Description:
    This definition selects the maximum number of hardware instances that can be
    supported by the dynamic driver. Comment this line for a static build of the
    driver.

  Remarks:
    None
*/

//#define DRV_USB_INSTANCES_NUMBER  /*DOM-IGNORE-BEGIN*/ 2 /*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Maximum Number of Clients

  Summary:
    Selects the maximum number of clients

  Description:
    This definition select the maximum number of clients that the USB driver can
    support at run time. In almost all realistic USB device applications, the driver
    will atleast have 2 or more clients.

  Remarks:
    None.

*/

//#define DRV_USB_CLIENTS_NUMBER  /*DOM-IGNORE-BEGIN*/ 2/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Maximum Number of Pipes

  Summary:
    Selects the maximum number of Pipes

  Description:
    Selects the maximum number of Pipes. Endpoint 0 will require one pipe that
    supports both directions. All other endpoints will require one pipe for each
    direction.

  Remarks:
    None.

*/

//#define DRV_USB_PIPES_NUMBER   /*DOM-IGNORE-BEGIN*/4 /*DOM-IGNORE-END*/



// *****************************************************************************
/* USB Maximum Number of Transfer Requests

  Summary:
    Selects the maximum number of Transfer Requests

  Description:
    Selects the maximum number of Transfer Requests. These transfers form the 
    transfer queues for each pipe.

  Remarks:
    None.

*/

#define DRV_USB_XFERS_NUMBER  /*DOM-IGNORE-BEGIN*/13/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Static Index Selection

  Summary:
    USB Static Index selection

  Description:
    USB Static Index selection for the driver object reference. This is a static
    override.

  Remarks:
    This index is required to make a reference to the driver object
*/

//#define DRV_USB_INDEX  /*DOM-IGNORE-BEGIN*/DRV_USB_INDEX_0/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is

    - true  - Select if interrupt mode of timer operation is desired

    - false - Select if polling mode of timer operation is desired

    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_USB_INTERRUPT_MODE  /*DOM-IGNORE-BEGIN*/true/*DOM-IGNORE-END*/

// *****************************************************************************
/* USB Driver Endpoints Number

  Summary:

    Number of endpoints.

  Description:
    This macro defines the number of endpoints to be supported by the
    driver. It is recommended that the application use contiguous endpoints.
    In case of an example endpoint selection such as 0,1 and 2, this value
    will be 3. In case of non-contiguous selection such as 0,1 nand 5, this
    value will be 6.

    This macro is an initialization override of the nEndpoints number of
    driver initialization configuration.

  Remarks:
    None.
*/
// #define DRV_USB_ENDPOINTS_NUMBER    3

// *****************************************************************************
/* USB Interrupt Source

  Summary:
    USB peripheral interrupt source.

  Description:
    Defines an override of the interrupt source in case of static driver. This
    is an initialization override of the interruptSource member of the driver
    initialization configuration.

  Remarks:
    Refer to the INT PLIB document for more information on INT_SOURCE
    enumeration.

*/

#define DRV_USB_INTERRUPT_SOURCE  INT_SOURCE_USB_1
// *****************************************************************************
/* USB power state configuration

  Summary:
    Power state of the USB driver.

  Description:
    Defines an override of the power state of the USB driver. This is an
    initialization override of the usbModuleSetup.OpMode member of the
    driver initialization configuration.

  Remarks:
    Note: This feature may not be available in the device or the USB module
    selected.
*/

#define DRV_USB_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP

#define DRV_USB_STOP_IN_IDLE	false

#define DRV_USB_SUSPEND_IN_SLEEP false

#define DRV_USB_OPERATION_MODE USB_OPMODE_DEVICE

#define DRV_USB_GEN_INT_ENABLES  ( USB_INT_ALL & ~USB_INT_SOF )

#define DRV_USB_OTG_INT_ENABLES  ( ~USB_OTG_INT_ALL )

#define DRV_USB_ERR_INT_ENABLES  ( USB_ERR_INT_ALL )

#define DRV_USB_DEVICE_ISOC_XFERS_ENABLE true

#define DRV_USB_HOST_MODE_SUPPORT_ENABLE true

#define DRV_USB_DEVICE_MODE_SUPPORT_ENABLE false

//#define DRV_USB_HOST_PIPES_NUMBER 5

// #define DRV_USB_HOST_IRP_PER_FRAME_NUMBER 5

// #define DRV_USB_HOST_IRP_NUMBER 5


// *****************************************************************************
// *****************************************************************************
// Section: Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            2

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              3

/* EP0 max size (in bytes) */
#define MAX_SIZE_EP0                        8

/* Maximum size of control transfer in bytes. */
#define MAX_SIZE_CONTROL_TX                 (MAX_SIZE_EP0 * 2)

/* Maximum function drivers allowed per instance of the USB device layer */
#define USB_DEVICE_MAX_FUNCTION_DRIVER      1


// *****************************************************************************
// *****************************************************************************
// Section: CDC Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* CDC function driver index */
#define APP_USBCDC_FUNC_INDEX                       0

/* data EP max size */
#define USB_CDC_DATA_EP_MAX_SIZE            		512

/* notiication EP max size **/
#define USB_CDC_NOTIFICATION_EP_MAX_SIZE    		1024

/* Maximum instances of CDC function driver */
#define USB_CDC_MAX_INSTANCES						1


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration options for the application
*/

/* IN buffer max size */
#define IN_BUFFER_MAX_SIZE 17

#define TOTAL_EP    3

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

