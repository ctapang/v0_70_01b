/*******************************************************************************
  USB HOST HUB driver Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_hub.h

  Summary:
    USB HUB Layer Interface Header

  Description:
    This header file contains the function prototypes and definitions of the
    data types and constants that make up the interface to the USB HOST HUB driver
   • Connectivity behavior
   • Power management
   • Device connect/disconnect detection
   • Bus fault detection and recovery
   • High-, full-, and low-speed device support
    
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END


#ifndef _USB_HOST_HUB_H
#define _USB_HOST_HUB_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  A file that maps the interface definitions above to appropriate static
          implementations (depending on build mode) is included at the bottom of
          this file.
*/

#include <stdint.h>
#include <stdbool.h>

#include "peripheral/usb/plib_usb.h"
#include "system/common/sys_common.h"
#include "driver/driver_common.h"


// *****************************************************************************
// *****************************************************************************
// Section: USB HOST HUB CLASS DRIVER Constants
// *****************************************************************************
// *****************************************************************************

/* Hub  Status   Table  11-19 from spec */
#define HUB_LOW_POWER_SOURCE                     (0x01 << 0)
#define HUB_OVER_CURRENT                         (0x01 << 1)




/* HUB change Table 11-20 from spec */

#define C_HUB_LOCAL_POWER   (0x01 << 0)
#define C_HUB_OVER_CURRENT  (0x01 << 1)


/* HUB Class codes as defined by USB            */
#define USB_HUB_CLASS                          0x09
/* Port status Bit numbers  Table 11-21 from spec*/

#define HUB_PORT_CONNECTION_POS                 (0x01 << 0)
#define HUB_PORT_ENABLE_POS                     (0x01 << 1)
#define HUB_PORT_SUSPEND_POS                    (0x01 << 2)
#define HUB_PORT_OVER_CURRENT_POS               (0x01 << 3)
#define HUB_PORT_RESET_POS                     (0x01 << 4)
#define HUB_PORT_POWER_POS                      (0x01 << 8)
#define HUB_PORT_LOW_SPEED_POS                  (0x01 << 9)
#define HUB_PORT_HIGH_SPEED_POS                 (0x01 << 10)
#define HUB_PORT_TEST_POS                       (0x01 << 11)
#define HUB_PORT_INDICATOR_POS                  (0x01 << 12)

/* Port Change  Bit numbers Table 11-22 from spec */

// #define HUB_CHANGE_PORT_CONNECTION               (0x01 << 0)
// #define HUB_CHANGE_PORT_ENABLE                   (0x01 << 1)
// #define HUB_CHANGE_PORT_SUSPEND                  (0x01 << 2)
// #define HUB_CHANGE_PORT_OVER_CURRENT             (0x01 << 3)
// #define HUB_CHANGE_PORT_RESET                    (0x01 << 4)


/* HUB Commands  */

#define USB_HOST_HUB_COMMAND_GET_STATUS                      0x0
#define USB_HOST_HUB_COMMAND_CLEAR_FEATURE                   0x1
#define USB_HOST_HUB_COMMAND_SET_FEATURE                     0x3
#define USB_HOST_HUB_COMMAND_GET_DESCRIPTOR                  0x6
#define USB_HOST_HUB_COMMAND_SET_DESCRIPTOR                  0x7


/* Port commands */

#define HUB_PORT_CONNECTION                     0
#define HUB_PORT_ENABLE                         1
#define HUB_PORT_SUSPEND                        2
#define HUB_PORT_OVER_CURRENT                   3
#define HUB_PORT_RESET                          4
#define HUB_PORT_POWER                          8
#define HUB_PORT_LOW_SPEED                      9
#define HUB_PORT_HIGH_SPEED                     10
#define HUB_PORT_TEST                           11
#define HUB_PORT_INDICATOR                      12


#define HUB_NORMAL                              0x0
#define HUB_SHUTDOWN                            0x1
#define HUB_DIRTY                               0x2

#define HUB_CHANGE_PORT_CONNECTION           16
#define HUB_CHANGE_PORT_ENABLE               17
#define HUB_CHANGE_PORT_SUSPEND              18
#define HUB_CHANGE_PORT_OVER_CURRENT         19
#define HUB_CHANGE_PORT_RESET                20



/* Genarally Hub may support 2 or 4 or 7 ports */

#define  HUB_MAX_SUPPORTS_DEVICES             4
#define  HUB_MAX_SUPPORTS_TRANSFERS           2         /* Modify this value */

#define  HUB_STATUS_IRP                       2
#define  USB_MAX_HUB_SUPPORTED                2
#define  USB_HOST_HUB_EVENTS_SUPPORTED        1

#define  PORT_REQUEST      0x00
#define  HUB_REQUEST        0x01

#define USB_HOST_HUB_PORT_REQ    0x00
#define USB_HOST_HUB_REQ         0x01




/* wPortStatus  */

#define HUB_BIT_PORT_CONNECTION                 (0x01 << 0)
#define HUB_BIT_PORT_ENABLE                     (0x01 << 1)
#define HUB_BIT_PORT_SUSPEND                    (0x01 << 2)
#define HUB_BIT_PORT_OVER_CURRENT               (0x01 << 3)
#define HUB_BIT_PORT_RESET                      (0x01 << 4)

#define HUB_BIT_PORT_POWER                      (0x01 << 8)
#define HUB_BIT_PORT_LOW_SPEED                  (0x01 << 9)
#define HUB_BIT_PORT_HIGH_SPEED                 (0x01 << 10)

/* wPortChange  */

#define HUB_BIT_C_PORT_CONNECTION               (0x01 << 0)
#define HUB_BIT_C_PORT_ENABLE                   (0x01 << 1)
#define HUB_BIT_C_PORT_SUSPEND                  (0x01 << 2)
#define HUB_BIT_C_PORT_OVER_CURRENT             (0x01 << 3)
#define HUB_BIT_C_PORT_RESET                    (0x01 << 4)


/* The following commands have a port as the receipient */

#define HUB_FEATURE_PORT_CONNECTION             0
#define HUB_FEATURE_PORT_ENABLE                 1
#define HUB_FEATURE_PORT_SUSPEND                2
#define HUB_FEATURE_PORT_OVER_CURRENT           3
#define HUB_FEATURE_PORT_RESET                  4
#define HUB_FEATURE_PORT_POWER                  8
#define HUB_FEATURE_PORT_LOW_SPEED              9
#define HUB_FEATURE_PORT_HIGH_SPEED             10
#define HUB_FEATURE_C_PORT_CONNECTION           16
#define HUB_FEATURE_C_PORT_ENABLE               17
#define HUB_FEATURE_C_PORT_SUSPEND              18
#define HUB_FEATURE_C_PORT_OVER_CURRENT         19
#define HUB_FEATURE_C_PORT_RESET                20


/*******************************************************************************/

typedef struct _USB_HOST_HUB_STATUS_
{
    uint16_t       status;
    uint16_t       change;
} USB_HOST_HUB_STATUS;




/* Table 11-13 Hub descriptor */
typedef struct _USB_HOST_HUB_DESCRIPTOR_
{

    uint8_t               bDescLength;        /* Number of bytes in this descriptor */
    uint8_t               bDescriptorType;    /* value: 29H for hub descriptor  */
    uint8_t               bNbrPorts;          /* Number of downstream facing ports that this hub supports */
    uint16_t              wHubCharacteristics;    /*  description  in table 11-13 spec*/
    uint8_t               bPwrOn2PwrGood;     /* Time 2ms this    */
    uint8_t               bHubContrCurrent;   /* Max Current */
    uint8_t               DeviceRemovable;    /* Depends number of ports on hub */
    uint8_t               PortPwrCtrlMask;    
	/* TODO  size is depend PortPwrCtrlMask **********/
	/* reseved */
    
}USB_HOST_HUB_DESCRIPTOR;


typedef struct _USB_HOST_HUB_IRP_
{
    void                *hubInfo;
    uint8_t             index;
    uint8_t             transferNumber;        /* Easy to track */
    USB_HOST_IRP        interuptinIrp;
    uint8_t             portStatus[HUB_MAX_SUPPORTS_DEVICES];

}USB_HOST_HUB_IRP;

/* HUB information we have to mainitain in linked list */
typedef struct _USB_HOST_HUB_DRIVER_INFO_
{
    uint8_t             hubState;  /* NORMAL , SLEEP , BUSFAULT */
    uint8_t             errors;   /* More than 5 Bus fault */
    uint8_t             hubcount;  /* ref of hub */
    uint8_t             power;     /* Check available power info on Chap 7 */
    HC_DEVICE_ID          hubId;
    HC_DEVICE_ID           children[HUB_MAX_SUPPORTS_DEVICES];
    USB_HOST_IRP           controlTransferIRP;
    USB_HOST_HUB_IRP           hubStatusIRP[2]; // interuptIn
    USB_HOST_HUB_DESCRIPTOR  hubDesc;
    uint8_t                  setupPacket[8];
     /* setup packet information */
    USB_HOST_PIPE_HANDLE    controlpipeHandle;
     USB_HOST_PIPE_HANDLE    interruptinpipeHandle;
    
} USB_HOST_HUB_DRIVER_INFO;



typedef struct _USB_HUB_OBJ_
{

    USB_HOST_HUB_DRIVER_INFO            hubList[USB_MAX_HUB_SUPPORTED] ;
    uint8_t             submittedRequest;
    uint32_t             completedRequest;
    USB_HOST_IRP         eventList[USB_HOST_HUB_EVENTS_SUPPORTED];
    uint8_t              pendingEvent;

} USB_HUB_OBJ;
// *****************************************************************************
// *****************************************************************************
// Section: USB HOST HUB CLASS DRIVER Interface Routines
// *****************************************************************************
// *****************************************************************************

#if 0
void USB_HOST_HUB_Task( void);
 /* look event list 
    Check hub is removed
	check Errors on the bus 
	find port
	find parent
	find hub status change or port status change 
	*/
 
USB_STATUS  USB_HOST_HUB_Class_init()   ;

     /* 1. Entry point for class driver
	    2. Create one Hub task if it is OS based 
		3. Allocate Memory */
		

void USB_HOST_HUB_Class_deinit( void);

  /* if parent device is root hub then will call this function
      delete the task
	  delete all memory, semaphore ...etc */
	  

void USB_HOST_HUB_Connect( uint8_t DeviceId);
 
  /*  newly connected hub info add into linked list */


USB_HOST_HUB_Status_request();
/* send control request to the hub */

USB_HOST_HUB_Connect_Device();

USB_HOST_HUB_Disconnect_Device(deviceID);
/* find parent hub , port number , disable port and deenumerate device */

USB_HOST_HUB_Interrupt_Endpoint_Transfercomplete();
USB_HOST_HUB_Control_Endpoint_Transfercomplete();

USB_HOST_HUB_Port_connect(deviceID , portnumber);
/* Reset the hub port and Enumerate the device */
USB_HOST_HUB_Port_reset(deviceID, portnumber);
/* Reset the hub port */
USB_HOST_HUB_Port_debounce();
/* devices specific after disconnected wait 200ms to stabilize */

void USB_HOST_HUB_Port_status_change( hub);
     /* Find port nub and sent port status request and take action based on event */


USB_HOST_HUB_connected_device_status_change();
/* port status change information will get through interrupt endpoint */


void USB_HOST_HUB_release_power( deviceID , power);
/* Once remove the device ...we have to add the power information into the HUB */

USB_HOST_HUB_allocate_power(deviceID, power);

/* After enumerate we have to update the power information into the parent HUB info */

/* Find hub **********/
void USB_HOST_findHub( devid );
 /* All hubs info into linked list check where the device id match */

		
#endif

#define   USB_HOST_HUB_SET_PORT_FEATURE     0x10
#define   USB_HOST_HUB_CLEAR_PORT_FEATURE   0x20
#define   USB_HOST_HUB_SET_HUB_FEATURE      0x30
#define   USB_HOST_HUB_CLEAR_HUB_FEATURE    0x40
#define   USB_HOST_GET_HUB_STATUS           0x50
#define   USB_HOST_GET_PORT_STATUS          0x60


//APIs
USB_STATUS      USB_HOST_HUB_interfaceInitialize(HC_DEVICE_ID id , uint8_t interfaceId,  uint8_t *hubInstance);
void            USB_HOST_HUB_task(void);
void            USB_HOST_HUB_interruptTransferComplete(USB_HOST_IRP *irp );
void             USB_HOST_HUB_controlTransferComplete( USB_HOST_IRP *irp);



 USB_STATUS  _usb_host_getHubDescriptor (USB_HOST_HUB_DRIVER_INFO *hubInfo);
void _usb_host_hub_getStatus (USB_HOST_HUB_DRIVER_INFO * hubinfo,USB_HOST_HUB_STATUS *hubAndportStatus, uint8_t portNumber, uint8_t requestType);
 USB_STATUS _usb_host_hub_setFeature (USB_HOST_HUB_DRIVER_INFO * hubinfo, uint8_t portNumber ,uint8_t Feature, uint8_t hubCommand ,uint8_t requestType );
 USB_STATUS _usb_host_hub_clearFeature (USB_HOST_HUB_DRIVER_INFO * hubInfo, uint8_t portNumber ,uint8_t Feature, uint8_t hubCommand ,uint8_t requestType );
USB_STATUS usb_host_get_parentinfo( HC_DEVICE_ID hubId , HC_DEVICE_ID *parentDeviceId );
void USB_HOST_HUB_statusChange(USB_HOST_HUB_DRIVER_INFO * hubinfo);
void USB_HOST_HUB_portStatusChange(USB_HOST_HUB_DRIVER_INFO * hubinfo, uint32_t status);
 USB_STATUS      USB_HOST_HUB_DeInitialize(HC_DEVICE_ID id  );
 void _USB_HUB_portConnect(HC_DEVICE_ID hubId , uint8_t portNumber, uint8_t speed );
  void   _USB_HOST_HUB_portReset(USB_HOST_HUB_DRIVER_INFO  *hubInfo , uint8_t portNumber , uint8_t *speed );
  uint8_t  _USB_HOST_HUB_portDebounce(USB_HOST_HUB_DRIVER_INFO  *hubInfo , uint8_t portNumber , USB_HOST_HUB_STATUS *portStatus );
#endif
