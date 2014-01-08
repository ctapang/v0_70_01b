/* ******************************************************************************
  USB Host Layer Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_local.h

  Summary:
    USB HOST Layer Interface Header

  Description:
    This header file contains the function prototypes and definitions of the
    data types and constants that make up the interface to the USB HOST
    layer.
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

#ifndef _USB_HOST_LOCAL_H
#define _USB_HOST_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_host.h"
#include "system_config.h"
#include "driver/usb/drv_usb.h"




// *****************************************************************************
/* USB_HOST_MATCH_HC_DEVICE_ID

  Summary:
    This macro use for validate the device id or find the correct id from the list

  Description:

  Remarks:

*/
/* USB host layer client object structure */

#define USB_HOST_MATCH_HC_DEVICE_ID(  X , Y ) (((X.deviceID == Y.deviceID) &&\
                        (  X.hostcontrollerID == Y.hostcontrollerID )) ? 1: 0)


/* Call back should be function pointer */
#define  USB_HOST_IRP_CALLBACK                 void*

/* Root hub address */
#define USB_ROOT_HUB                1    /* Root hub address */

#define USB_MAX_USB_ADDRESS       127
// *****************************************************************************
/* USB_HOST_PIPE_HANDLE

  Summary:
    pipe information

  Description:
    Pipe Create will get pipe Handle, useing this we can transfer the data

  Remarks:
    None.
*/

/* Host Pipe handle */
typedef uintptr_t USB_HOST_PIPE_HANDLE;

typedef struct _HC_DEVICE_ID_
{
  /* Device unique id */
  uint8_t    deviceID;
  /* Host index id  support multiple controllers */
  uint8_t    hostcontrollerID;
}HC_DEVICE_ID;


// *****************************************************************************
/*  USB Host Driver Structure.

  Summary:
    USB HOST function driver should provide all APIs to assign this structere.

  Description:

  Remarks:

*/
typedef struct _USB_HOST_DRIVER_
{
    /*initialize the host driver */
    USB_ERROR     (*initializeDeviceDriver) (HC_DEVICE_ID id,
                                                    void *instance);
    /* Initialisation for Interface Drivers */
    USB_ERROR     (*initializeInterfaceDriver) (HC_DEVICE_ID id ,
                                                      uint8_t interfaceId,
                                                      uint8_t *instance , uint8_t speed);
    /* Deattach event function for USB drivers */
    void           (*deInitializeDriver ) (HC_DEVICE_ID id);
    void           (* task )(void);
    /* Driver instance Number */
    uint8_t         instanceNumber;

}USB_HOST_DRIVER;


// *****************************************************************************
/*  USB Host Driver query Structure.

  Summary:
    USB HOST function driver should fill the query structere to get the
    information from the Host

  Description:
  Query the host and get any information
  Remarks:

*/
typedef struct _USB_HOST_DRIVER_QUERY_
{
    /* Host controller id + Device Id */
    HC_DEVICE_ID       id;
    /* Alternate setting number */
    uint8_t            alternateSettingNumber;
    /* Interface Number */
    uint8_t            interfaceNumber;
    /* configuration Number */
    uint8_t            configurationNumber;
    /* class */
    uint8_t            interfaceClass;
    /* subclass */
    uint8_t            interfaceSubClass;
    /* protocol */
    uint8_t            interfaceProtocol;
    /* Endpoint Address */
    uint8_t            endpointAddress;
    /* Endpoint Type */
    uint8_t            endpointType;
    /* Endpoint Direction in or out */
    uint8_t            endpointDirection;
    /* Any flags to match */
    uint16_t           flags;

} USB_HOST_DRIVER_QUERY;



// *****************************************************************************
/* USB_MATCH_CLASS

  Summary:
  USB HOST can find the matching driver based on macros
  and Function drivers query the host based on macros

  Description:


  Remarks:
    None.
*/
#define USB_MATCH_CLASS				0x10
#define USB_MATCH_SUB_CLASS			0x20
#define USB_MATCH_PROTOCOL			0x40
#define USB_MATCH_ENDPOINT_TYPE                 0x8
#define USB_MATCH_ENDPOINT_DIRECTION 		0x10


/********************************************************************************
DETACHED state machine values
This state machine handles the condition when no device is attached.
*/
#define STATE_DETACHED                                  0x0000
#define SUBSTATE_INITIALIZE                             0x0000
#define SUBSTATE_WAIT_FOR_POWER                         0x0010
#define SUBSTATE_TURN_ON_POWER                          0x0020
#define SUBSTATE_WAIT_FOR_DEVICE                        0x0030

/*
*******************************************************************************
ATTACHED state machine values

This state machine gets the device descriptor of the remote device.  We get the
size of the device descriptor, and use that size to get the entire device
descriptor.  Then we check the VID and PID and make sure they appear in the TPL.
*/

#define STATE_ATTACHED                                  0x0100

#define SUBSTATE_SETTLE                                 0x0001
#define SUBSUBSTATE_START_SETTLING_DELAY                0x0002
#define SUBSUBSTATE_WAIT_FOR_SETTLING                   0x0003
#define SUBSUBSTATE_SETTLING_DONE                       0x0004
#define SUBSTATE_RESET_DEVICE                           0x0005
#define SUBSUBSTATE_SET_RESET                           0x0006
#define SUBSUBSTATE_RESET_WAIT                          0x0007
#define SUBSUBSTATE_RESET_RECOVERY                      0x0008
#define SUBSUBSTATE_RECOVERY_WAIT                       0x0009
#define SUBSUBSTATE_RESET_COMPLETE                      0x0010

#define SUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE             0x0011
#define SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR_SIZE     0x0012
#define SUBSUBSTATE_WAIT_FOR_GET_DEVICE_DESCRIPTOR_SIZE 0x0013
#define SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE_COMPLETE 0x0014

#define SUBSTATE_GET_DEVICE_DESCRIPTOR                  0x0015
#define SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR          0x0016
#define SUBSUBSTATE_WAIT_FOR_GET_DEVICE_DESCRIPTOR      0x0017
#define SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_COMPLETE      0x0018

#define SUBSTATE_VALIDATE_VID_PID                       0x0019

/* ADDRESSING state machine values
   This state machine sets the address of the remote device. */
#define STATE_ADDRESSING                                0x0200

#define SUBSTATE_SET_DEVICE_ADDRESS                     0x0020
#define SUBSUBSTATE_SEND_SET_DEVICE_ADDRESS             0x0021
#define SUBSUBSTATE_WAIT_FOR_SET_DEVICE_ADDRESS         0x0022
#define SUBSUBSTATE_SET_DEVICE_ADDRESS_COMPLETE         0x0023

/*
*******************************************************************************
CONFIGURING state machine values

This state machine sets the configuration of the remote device, and sets up
internal variables to support the device.
*/
#define STATE_CONFIGURING                               0x0300

#define SUBSTATE_INIT_CONFIGURATION                     0x0024

#define SUBSTATE_GET_CONFIG_DESCRIPTOR_SIZE             0x0025
#define SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR_SIZE     0x0026
#define SUBSUBSTATE_WAIT_FOR_GET_CONFIG_DESCRIPTOR_SIZE 0x0027
#define SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_SIZE_COMPLETE 0x0028
#define SUBSTATE_GET_CONFIG_DESCRIPTOR                  0x0029
#define SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR          0x0030
#define SUBSUBSTATE_WAIT_FOR_GET_CONFIG_DESCRIPTOR      0x0031
#define SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_COMPLETE      0x0032
#define SUBSTATE_SELECT_CONFIGURATION                   0x0033
#define SUBSUBSTATE_SELECT_CONFIGURATION                0x0034
#define SUBSUBSTATE_SEND_SET_OTG                        0x0035
#define SUBSUBSTATE_WAIT_FOR_SET_OTG_DONE               0x0036
#define SUBSUBSTATE_SET_OTG_COMPLETE                    0x0037
#define SUBSTATE_SET_CONFIGURATION                      0x0038
#define SUBSUBSTATE_SEND_SET_CONFIGURATION              0x0039
#define SUBSUBSTATE_WAIT_FOR_SET_CONFIGURATION          0x0040
#define SUBSUBSTATE_SET_CONFIGURATION_COMPLETE          0x0041
#define SUBSTATE_SET_INTERFACE                          0x0042
#define SUBSUBSTATE_SEND_SET_INTERFACE                  0x0043
#define SUBSUBSTATE_WAIT_FOR_SET_INTERFACE              0x0044
#define SUBSUBSTATE_SET_INTERFACE_COMPLETE              0x0045
#define SUBSUBSTATE_INIT_CLIENT_DRIVERS                 0x0046

#define      SUBSTATE_GET_STRING_DESCRIPTOR             0x0047
#define      SUBSTATE_SEND_LANGUAGE_ID                    0x0048
#define      SUBSTATE_SEND_LANGUAGE_ID_COMPLETE         0x0049
/* RUNNING state machine values */
#define DEVICE_READY                                    0x0400
#define HOST_STATE_RUNNING                                   0x0400
#define SUBSTATE_NORMAL_RUN                             0x0050
#define SUBSTATE_SUSPEND_AND_RESUME                     0x0051
#define SUBSUBSTATE_SUSPEND                             0x0052
#define SUBSUBSTATE_RESUME                              0x0053
#define SUBSUBSTATE_RESUME_WAIT                         0x0054
#define SUBSUBSTATE_RESUME_RECOVERY                     0x0055
#define SUBSUBSTATE_RESUME_RECOVERY_WAIT                0x0056
#define SUBSUBSTATE_RESUME_COMPLETE                     0x0057
/* HOLDING state machine values */
#define STATE_HOLDING                                   0x0410
#define SUBSTATE_HOLD_INIT                              0x0058
#define SUBSTATE_HOLD                                   0x0059

#define SUBSTATE_SEND_MANUFACTURE_NAME                 0x0060
#define SUBSTATE_SEND_PRODUCT_NAME                        0x061
#define SUBSTATE_SEND_SERIAL_NUMBER                       0x0062
#define SUBSTATE_SEND_MANUFACTURENAME_COMPLETE              0x0063
#define SUBSTATE_SEND_PRODUCT_NAME_COMPLETE              0x0064
#define SUBSTATE_SEND_SERIAL_NUMBER_COMPLETE                 0x0065

#define USB_VENDOR_DEVICE_DRIVER          1
#define USB_STANDARD_DEVICE_DRIVER        2
#define USB_STANDARD_INTERFACE_DRIVER     3
#define USB_CONFIG_DESCRPTR_SIZE          9

/* End point descriptor information  private */
typedef struct _USB_ENDPOINT_DESC_INFO_
{
    /* usb standard descriptor*/
    USB_ENDPOINT_DESCRIPTOR *endpointDescriptor;
    /* Bandwidth based on endpoint type and speed */
    uint8_t                  bandwidth;
    /* class specific descriptor information */
    uint8_t                 *classSpecific;
    /* pointer to the end of class specific descriptor */
    uint8_t                 *classEndPtr;
    /* Pipe Handle for talk to controler driver */
    USB_HOST_PIPE_HANDLE    PipeHandle;
}USB_ENDPOINT_DESC_INFO;


/* Alternate setting information */

typedef struct _USB_ALTERNATE_SETTING_INFO_
{
    /* standard interface desctiptor */
    USB_INTERFACE_DESCRIPTOR *interfaceDescriptor;
    /* Endpoint descriptor info */
    USB_ENDPOINT_DESC_INFO  endpointInfo[DRV_USB_HOST_PIPES_NUMBER];
    /* class specific descriptor information */
    uint8_t                 *classSpecific;
    /* pointer to the end of class specific descriptor */
    uint8_t                 *classEndPtr;

}USB_ALTERNATE_SETTING_INFO;


/****************** Interface information *****************/

typedef struct _USB_INTERFACE_DESC_INFO_
{
    /* standard interface descriptor */
    USB_INTERFACE_DESCRIPTOR *interface;
    /* alternate setting information */
    USB_ALTERNATE_SETTING_INFO  alternateSettingInfo[USB_HOST_MAX_ALTERNATE_SETTINGS];
    /*interface driver */
    USB_HOST_DRIVER *interfaceDriver;

}USB_INTERFACE_DESC_INFO;

/******************* Configuration information ******************/
typedef struct _USB_CONFIGURATION_INFO_
{
    /* standard configuration descriptor */
    USB_CONFIGURATION_DESCRIPTOR *configurationDescriptor;
    /* Local interface info */
    USB_INTERFACE_DESC_INFO interfaceInfo[USB_HOST_MAX_INTERFACES];
    /* bandwidth for each configuration */
    uint8_t   load;
    /* Active configuration number */
    uint8_t   activeConfigurationNumber ;

}USB_CONFIGURATION_INFO;


/*************** Device information *************************/

typedef struct  _USB_DEVICE_INFO_
{
    uint8_t       assigned;
    /* Host controller id + Device Id */
    HC_DEVICE_ID deviceId;
    /* Device name for display purpose */
    int8_t devicename[4];
    /* Parent device information for Hub support */
    HC_DEVICE_ID parentId;
    /* default pipe handle */
    USB_HOST_PIPE_HANDLE  defaultPipeHandle;
    /* control pipe handle */
    USB_HOST_PIPE_HANDLE controlPipeHandle;
    /* host controller handle */
    USB_HOST_HANDLE        hostControllerHandle;
    /* Original device descriptor information */
    USB_DEVICE_DESCRIPTOR  deviceDescriptor;
    /* Configurations information */
    USB_CONFIGURATION_INFO configDescriptorInfo[USB_HOST_MAX_CONFIGURATION];
    /* control irp*/
    USB_HOST_IRP controlIrp;
    /* Active configuration number */
    uint8_t activeConfigurationNumber;
    /* speed of the device */
    USB_SPEED speed;
    /* Port number for reset/suspend/resume/power */
    uint8_t portnumber;
    /* vendor information */
    uint16_t vendorid;
    uint16_t productid;
    uint16_t versionNumber;
    int8_t  ManufacturerName[31];
    int8_t  productName[20];
    int8_t  serialNumber[12];
    int8_t  languageId[4];
    /* Class specific device information */
    uint8_t classid;
    uint8_t subclass;
    uint8_t protocol;
     /* Driver attached */
    USB_HOST_DRIVER *driver;
    /* Driver type */
    uint8_t driverType;
    /* setup packet information */
    uint8_t setupPacket[8];
    /* Buffer for raw data information */
    uint8_t buffer[255];
    /* status of endpoint or device */
    uint16_t  devicestatus;
    /* Device state information */
    uint32_t deviceState;
    /* Device substate information for internal usage */
    uint16_t deviceSubState;
    /* Device sub sub state information for internal usage */
    uint16_t deviceSubSubState;
    /* Enumeration fail count*/
    uint8_t  enumerationFailCount;
 
}USB_DEVICE_INFO;


/**************** Root hub information *****************/
typedef struct _USB_ROOT_HUB_INFO_
{
    uint8_t  always_powered;
    //TODO more
    /* number of ports in root hub is only one */

}USB_ROOT_HUB_INFO;


/***************** Bus/controller information  ************/

typedef struct  _USB_HOST_BUS_INFO_
{
    /* Handle to the Host controller driver */
    DRV_HANDLE      hostControllerHandle;
    /* index of the host controller */
    uint8_t         hostcontrollerid ;
    /* Status of Host controller */
    uint8_t         inuse;
    /* Type of Host controller  Full / High speed */
    uint8_t         hostcontrollertype;
    /* Available BandWidth per controller in a frame */
    uint32_t        totalbandwidth;
    /* BandWidth available for new End points */
    uint32_t        availableBandwidth;
    /* Device connected database */
    USB_DEVICE_INFO attachedDevicesList[USB_HOST_MAX_DEVICE_SUPPORTED];
    uint8_t         attachdevicesCount;
    /* Based on bits position the device address assigned and free*/
    uint8_t         addressBits[16];
    /* Root hub information */
    USB_ROOT_HUB_INFO      usbRootHubInfo;
    /* initilisation done */
        /* State of this instance */
    SYS_STATUS    usbHostInstanceState;
    uint8_t         initDone;

   
}USB_HOST_BUS_INFO;

typedef struct _USB_HOST_CLIENT_STRUCT_
{
    SYS_MODULE_INDEX hostLayerIndex;
    /* Client status */
    DRV_CLIENT_STATUS clientState;
    /* Pointer to the callback function */
    USB_HOST_EVENT_CALLBACK callBackFunc;
    /*Bus information*/
    USB_HOST_BUS_INFO       *usbHostInstance;

}*USB_HOST_CLIENT_HANDLE, USB_HOST_CLIENT_STRUCT;

/* Global information about USB HOST*/
typedef struct _USB_HOST_OBJ_
{
   /* Multiple Host controllers support */
   USB_HOST_BUS_INFO  businfo[USB_HOST_INSTANCES_NUMBER];
   /* Multiple Host drivers information */
   USB_HOST_TARGET_PERIPHERAL_LIST *hostDeviceDriverinfo;

}USB_HOST_OBJ;


/* This values based on usb standards It will change based on controller driver */
#define  USB_FULL_SPEED_BANDWIDTH   900
#define  USB_HIGH_SPEED_BANDWIDTH   800


// *****************************************************************************
// *****************************************************************************
// Section: Local functions
// *****************************************************************************
// *****************************************************************************
/******************************************************************************
  Function:
    USB_HOST_BUS_INFO * _USB_HOST_GetBusInfo( HC_DEVICE_ID Id)

  Summary:
    Get the  controller/ bus information based on deviceID

  Description:
    Bus information is global.collect the information based on attached devices.

  Parameters:
    HC_DEVICE_ID                 - Host controller Id + device id.

  Returns:
    USB_HOST_BUS_INFO *          - return to the pointer to the bus information
*/

USB_HOST_BUS_INFO*  _USB_HOST_GetBusInfo( HC_DEVICE_ID Id);

 /******************************************************************************
  Function:
  uint8_t _usb_get_new_address(HC_DEVICE_ID id )

  Summary:
    Allocate a unique 8 bit device address

  Description:
 Assign address for Host controller and device address

  Parameters:
   USB_HOST_BUS_INFO *                - bus information pointer

  Returns:
  uint8_t
*/

uint8_t _USB_HOST_GetNewAddress(HC_DEVICE_ID id);

/******************************************************************************
  Function:
    int8_t _usb_parse_config_desc(uint8_t *buffer,
                              USB_CONFIGURATION_INFO *config_desc_info,
                              uint8_t length)
  Summary:
 Parse descriptors

  Description:
    This routine is parse the configuration descriptor that holds the
 configuration descriptor, interface descriptor and endpoint descriptors

  Parameters:
    uint8_t*                             - raw configuration descriptor
    USB_CONFIGURATION_INFO *             - configuration information
    uint8_t                              - Length of the configuration descriptor

  Returns:
    int8_t                              - Status
*/

int8_t _USB_HOST_ParseConfigDescriptor(uint8_t *buffer,
                              USB_CONFIGURATION_INFO *configDescriptorInfo,
                              uint8_t length);

/******************************************************************************
  Function:
    int8_t  _USB_HOST_FindDriver( USB_DEVICE_INFO *newdevice)

  Summary:
    Find a maching a driver from the target peripheral list

  Description:
 Driver has to find based on Vendorid , productid, version number in
 device descritor
 or class - subclass - protocol values in device descriptor
 or class - subclass - protocol values in interface descriptor

  Parameters:
    USB_DEVICE_INFO *                   - newdevice information
  Returns:
    int8_t                                 - return status
*/
int8_t  _USB_HOST_FindDriver( USB_DEVICE_INFO *newdevice);

/******************************************************************************
  Function:
    int8_t  _USB_HOST_AttachDriver( USB_DEVICE_INFO *newdevice ,
                                    USB_HOST_BUS_INFO *bus_info )

  Summary:
   Initialize a device or interface

  Description:

  Parameters:
    USB_DEVICE_INFO *                   - newdevice information

  Returns:
   none
*/
void _USB_HOST_AttachDriver(USB_DEVICE_INFO *newdevice );

/******************************************************************************
  Function:
    _USB_HOST_FreeAddress (USB_HOST_BUS_INFO *bus , uint8_t deviceAddress)

  Summary:
    Free address

  Description:
    It is used for free the adress to the Host controller


  Parameters:
   USB_HOST_BUS_INFO *                 - bus information
   uint8_t                             - deviceAddress to be free

  Returns:
    uint8_t
*/
 uint8_t _USB_HOST_FreeAddress (USB_HOST_BUS_INFO *busInfo ,
                                uint8_t deviceAddress);

 /******************************************************************************
  Function:
    _USB_HOST_GetDeviceInfo(HC_DEVICE_ID Id )

  Summary:
 Get device information based on host controller id and device id

  Description:
 Collect all the device related information

  Parameters:
    HC_DEVICE_ID                - Host controllerId + device ID

  Returns:
    USB_DEVICE_INFO *           - pointer to the device information
*/

USB_DEVICE_INFO * _USB_HOST_GetDeviceInfo(HC_DEVICE_ID Id );

/******************************************************************************
  Function:
    void _USB_HOST_EventHandler(void* referenceHandle,
        DRV_USB_CLIENT_STATUS eventType, DRV_USB_EVENT_DATA *eventData )

  Summary:
    Handles the events originating from USB Host Controller Driver

  Description:
    This routine is registered into the USB Host controller driver as a callback
    function. The USB Host controller driver calls this function in case of events
    from the USB controller driver.

  Parameters:
    referenceHandle           - USB Host Instance
    eventType                 - Event type
    eventData                 - Data associated with the event

  Returns:
    none.
*/

void _USB_HOST_EventHandler( uintptr_t referenceHandle,
            DRV_USB_EVENT eventType, void * eventData );




// *****************************************************************************
/* USB HOST result

  Summary:
    USB HOST result

  Description:
    These macros are useful to identify  USB HOST function status.

 */
typedef enum {
    /* No Error, Operation was successful */
    USB_HOST_SUCCESS = 1,
    USB_HOST_CONFIG_DESCRPTR_SIZE_INVALID = -1,
    USB_HOST_MAX_INTERFACES_INVALID = -2,
    USB_HOST_HEADER_INVALID = -3,
    USB_HOST_INTERFACE_DESC_SIZE_INVALID = -4,
    USB_HOST_ENDPOINT_DESC_SIZE_INVALID = -5,
    USB_HOST_MAX_ENDPOINT_INVALID = -6,
    USB_HOST_DESC_INVALID = -7,
    USB_HOST_ALT_SETTING_INVALID = -8,
    USB_HOST_NO_BANDWIDTH = -9,
    USB_HOST_INVALID_ARG = -10,
    USB_HOST_ERROR = -11,
    USB_HOST_UNKNOWN_DEVICE = -12,
    USB_HOST_ENDPOINT_NOT_FOUND = -13,
    USB_HOST_MAX_INSTANCES_INVALID = -14


}USB_HOST_STATUS;

 /******************************************************************************
  Function:
    USB_CONFIGURATION_INFO* _USB_HOST_GetConfigurationInfo (
                                                        HC_DEVICE_ID id,
                                                uint8_t configurationNumber)

  Summary:
     Get device configuration information

  Description:
    Based  on device Identifier  and bConfiguration value get the
    configuration information

  Parameters:
    HC_DEVICE_ID                - Host controllerId + device ID
    uint8_t                     - configurationNumbe

  Returns:
    USB_CONFIGURATION_INFO*    - pointer to the device configuration information
*/
USB_CONFIGURATION_INFO* _USB_HOST_GetConfigurationInfo
                                                ( HC_DEVICE_ID id,
                                                  uint8_t configurationNumber);

// *****************************************************************************
/* Function:
    USB_HOST_PipeClose(USB_HOST_PIPE_HANDLE PipeHandle)

  Summary:
     Close the pipe

  Description:
     After detach the device we have close all the pipes related to the device.

  Parameters:
    USB_HOST_PIPE_HANDLE          PipeHandle          //Pipe handle

  Returns:
    USB_HOST_STATUS
*/

 USB_ERROR USB_HOST_PipeClose(USB_HOST_PIPE_HANDLE PipeHandle);

 /*****************************************************************************/
/* Function:
    USB_ERROR USB_HOST_IRPSubmit (USB_HOST_PIPE_HANDLE PipeHandle ,
                                     USB_HOST_IRP *irp )
  Summary:
    It configure the hardware and transfer the data

  Description:
      Send request to the Host controller driver

  Parameters:
    USB_HOST_IRP      - i/o request packet from class drivers

  Returns:
    USB_HOST_STATUS
*/

USB_ERROR USB_HOST_IRPSubmit (USB_HOST_PIPE_HANDLE PipeHandle ,
                                     USB_HOST_IRP *irp);


// *****************************************************************************
/*
 *  Function:
    USB_HOST_STATUS   USB_HOST_ClearEndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )

  Summary:
        setup packet with set feature of clear halt endpoint

  Description:
    Use for prevent the device from deenumerated and clear the halt

  Precondition:
    None.

  Parameters:
         HC_DEVICE_ID                   deviceId
         uint8_t                        endpointNumber
   Returns:
        USB_HOST_STATUS

  Remarks:

 */
USB_HOST_STATUS   USB_HOST_ClearEndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber );

USB_HOST_PIPE_HANDLE  USB_HOST_PipeSetup( HC_DEVICE_ID id ,
                                          USB_ENDPOINT_DESCRIPTOR *endPointDesc,
                                          uint8_t speed );

 
// These API only Demo purpose
void  USB_HOST_displayAttachedDevicesList( uint8_t *USB_HOST_deviceList);


int8_t _usb_set_configuration(USB_DEVICE_INFO *newdevice_info,USB_HOST_BUS_INFO *bus_info,USB_CONFIGURATION_INFO *configuatation_info );
uint32_t _usb_calculating_load (uint8_t direction_n_type,uint8_t speed, uint32_t max_pkt_size);
int8_t  _usb_set_interface_id (USB_DEVICE_INFO * newdevice, USB_HOST_BUS_INFO * bus_info,
                             USB_CONFIGURATION_INFO * config_info, uint8_t  interface_index,
                            uint8_t  alt_setting_index); 
uint8_t usb_calc_direction_n_type (USB_ENDPOINT_DESCRIPTOR *endpoint_desc);
uint32_t BitStuffTime(uint32_t Data_bc);
void _setupPacketCallback (USB_HOST_IRP * irp);
uint8_t USB_HOST_DeviceDetect();
void USB_HOST_EnumerateDevice();

USB_ERROR USB_HOST_FindEndpoint ( USB_HOST_DRIVER_QUERY *query,
                                        USB_ENDPOINT_DESCRIPTOR **endPointDesc);
USB_ERROR USB_HOST_FindInterface ( USB_HOST_DRIVER_QUERY *query,
                                      USB_INTERFACE_DESCRIPTOR **interfaceDesc);

USB_HOST_STATUS   USB_HOST_ClearEndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber );

#endif