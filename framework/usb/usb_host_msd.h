/*******************************************************************************
  USB CDC class definitions

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_msd.h

  Summary:
    USB MSD class definitions

  Description:
    This file describes the MSD class specific definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _USB_HOST_MSD_H
#define _USB_HOST_MSD_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

#define  USB_HOST_MSD_INDEX_0         0
#define  USB_HOST_MSD_INDEX_1         1


#define USB_HOST_MSD_CLASS          0x08
#define USB_HOST_MSD_SUBCLASS       0x06
#define USB_HOST_MSD_PROTOCOL       0x50

//typedef uint8_t USB_HOST_MSD_INSTANCE ;

// *****************************************************************************
/*  USB Host MSD Class Driver Index

  Summary:
     USB Host MSD Class Driver Index

  Description:
    This uniquely identifies a MSD Class Driver instance.

  Remarks:
    None.
*/
typedef uintptr_t USB_HOST_MSD_INDEX;


 #define USB_MSD_VALID_CBW_SIGNATURE (uint32_t)0x43425355
#define USB_MSD_VALID_CSW_SIGNATURE (uint32_t)0x53425355

 #define USB_MSD_VALID_CBW_TAG     (uint32_t) 0xDD1331DD

 #define USB_MSD_CSW_STATUS_SUCCESS  0x00
#define USB_MSD_CSW_STATUS_INVALID  -1
#define USB_MSD_CSW_TAG_INVALID -2
#define  USB_MSD_CSW_SIGNATURE_INVALID -3

/* BOT CSW Status */
#define USB_MSD_CSW_STATUS_GOOD         0x00
#define USB_MSD_CSW_STATUS_FAIL         0x01
#define USB_MSD_CSW_STATUS_PHASE_ERROR  0x02

#define USB_MSD_CBW_FLAG_IN  0x80
#define USB_MSD_CBW_FLAG_OUT  0x00


 #define USB_MSD_TRANSFER_SUCESSS 0x00
 #define USB_MSD_TRANSFER_FAIL  -1
#define USB_MSD_TRANSPORT_ERROR -2

 
 //Possible command status codes returned in the Command Status Wrapper (CSW)
#define USB_MSD_CSW_COMMAND_PASSED  0x00
#define USB_MSD_CSW_COMMAND_FAILED  0x01
#define USB_MSD_CSW_PHASE_ERROR     0x02

 #define USB_MSD_CSW_SIZE    0x0d	// 10 bytes CSW data
#define USB_MSD_CBW_SIZE    0x1f	// 31 bytes CBW data
#define USB_MSD_MAX_CB_SIZE 0x10    //MSD BOT Command Block (CB) size is 16 bytes maximum (bytes 0x0F-0x1E in the CBW)
#define USB_MSD_CBWFLAGS_RESERVED_BITS_MASK    0x3F //Bits 5..0 of the bCBWFlags byte are reserved, and should be set = 0 by host in order for CBW to be considered meaningful

 /* Class Commands */
#define USB_MSD_RESET           0xff
#define USB_MSD_GET_MAX_LUN     0xfe

/* Interface protocos's */

#define USB_HOST_MSD_CBI   0x00
#define USB_HOST_MSD_CB    0x01
#define USB_HOST_MSD_BOT  0x50   /* Bulk only transfer protocol */

/* bInterfaceProtocol's */

#define MS_PR_CBI   0x00        /* Control/Bulk/Interrupt       */
#define MS_PR_CB    0x01        /* Control/Bulk w/o interrupt   */
#define MS_PR_BULK  0x50        /* bulk only                    */


 #define USB_HOST_DRIVE_NOT_FOUND   -1

 // *****************************************************************************
/* USB device MSD CBW structure.

  Summary:
   CBW structure.

  Description:
    CBW structure.

  Remarks:
    This structure is private to USB MSD function driver.
 */

typedef struct __attribute__ ((packed)) _USB_MSD_CBW             //31 bytes total Command Block Wrapper
{
    uint32_t dCBWSignature;             // 55 53 42 43h
    uint32_t dCBWTag;					// sent by host, device echos this value in CSW (associated a CSW with a CBW)
    uint32_t dCBWDataTransferLength; 	// number of bytes of data host expects to transfer
    uint8_t bCBWFlags;                  // CBW flags, bit 7 = 0-data out from host to device,
                                        //					= 1-device to host, rest bits 0
    uint8_t bCBWLUN;					// Most Significant 4bits are always zero, 0 in our case as only one logical unit
    uint8_t bCBWCBLength;				// Here most significant 3bits are zero
    uint8_t CBWCB[16];		            // Command block to be executed by the device
} USB_MSD_CBW;


typedef struct __attribute__ ((packed)) _USB_MSD_COMMAND
{
    void    *command;
    uint8_t commandLength;
    void    *data;
    uint32_t receivedDataLength;
    uint32_t length;
    uint8_t commandStatus;
    uint8_t direction ;
 
}USB_MSD_COMMAND;

// *****************************************************************************
/* USB device MSD CSW structure.

  Summary:
   CSW structure.

  Description:
   CSW structure.

  Remarks:
    This structure is private to USB MSD function driver.
 */

typedef struct __attribute__ ((packed)) _USB_MSD_CSW			// Command Status Wrapper
{
	uint32_t dCSWSignature;			// 55 53 42 53h Signature of a CSW packet
	uint32_t dCSWTag;					// echo the dCBWTag of the CBW packet
	uint32_t dCSWDataResidue;			// difference in data expected (dCBWDataTransferLength) and actual amount processed/sent
	uint8_t bCSWStatus;				// 00h Command Passed, 01h Command Failed, 02h Phase Error, rest obsolete/reserved
} USB_MSD_CSW;


// *****************************************************************************
// *****************************************************************************
// Section: Constants Based on Limitation of Host controller or memory
// *****************************************************************************
// *****************************************************************************






// *****************************************************************************
/* USB HOST MSD Function Driver Transfer Handle Definition

  Summary:
    USB HOST MSD Function Driver Transfer Handle Definition.

  Description:
    This definition defines a USB Host MSD Function Driver Transfer Handle.
    A Transfer Handle is owned by the application but its value is modified by
    the USB_HOST_MSD_Write() and USB_HOST_MSD_Read() functions. The
    transfer handle is valid for the life time of the transfer and expires
    when the transfer related event had occurred.

  Remarks:
    None.
*/

typedef uintptr_t USB_HOST_MSD_TRANSFER_HANDLE;
// *****************************************************************************
/* USB HOST MSD Function Driver instance Handle

  Summary:
    USB HOST MSD Function Driver instance Handle

  Description:
    This defines a USB Host MSD Function Driver  Handle.
    A  Handle is owned by the application, USB_HOST_MSD_OPEN() handle is valid
    till the detach event
    

  Remarks:
    None.
*/
typedef uintptr_t USB_HOST_MSD_HANDLE;

// *****************************************************************************
/* USB HOST MSD Function Driver subclass Handle

  Summary:
    USB HOST MSD Function Driver subclass Handle Definition.

  Description:
    This definition defines a USB Host MSD Function Driver subclass Handle.
    This will be usefull if we support multiple subclasses

  Remarks:
    None.
*/

typedef uintptr_t USB_HOST_MSD_SUBCLASS_HANDLE;

// *****************************************************************************
/* USB HOST MSD Function Driver Read and Write Complete Event Data.

  Summary:
    USB HOST MSD Function Driver Read and Write Complete Event Data.

  Description:
    This data type defines the data structure returned by the driver along with
    USB_HOST_MSD_EVENT_READ_COMPLETE and USB_HOST_MSD_EVENT_WRITE_COMPLETE
    events.

  Remarks:
    None.
*/
typedef struct
{
    /* Transfer handle associated with this
     * read or write request */
    USB_HOST_MSD_TRANSFER_HANDLE handle;

    /* Indicates the amount of data (in bytes) that was
     * read or written */
    uint16_t length;
}
USB_HOST_MSD_CLIENT_EVENT_WRITE_COMPLETE_DATA,
USB_HOST_MSD_CLIENT_EVENT_READ_COMPLETE_DATA ;







// *****************************************************************************
// MSD Class Error Codes
// *****************************************************************************


// *****************************************************************************
/* USB Host MSD Transfer Flags

  Summary:
    USB Host MSD Function Driver Transfer Flags

  Description:
    These flags are used to indicate status of the pending data while sending
    data to the device by using the USB_HOST_MSD_Transfer() function.

  Remarks:
    The relevance of the specified flag depends on the size of the buffer. Refer
    to the individual flag descriptions for more details.
*/


typedef enum
{
    /* This flag indicates there is no further data to be sent
     * in this transfer and that the transfer should end. If the
     * size of the transfer is a multiple of the maximum packet
     * size for related endpoint configuration, the function
     * driver will send a zero length packet to indicate end of
     * the transfer to the host. */

    USB_HOST_MSD_TRANSFER_FLAGS_DATA_COMPLETE,

    /* This flag indicates there is more data to be sent in this
     * transfer. If the size of the transfer is a mutiple of the
     * maximum packet size for the related endpoint configuration,
     * the function driver will not send a zero length packet.
     * If the size of the transfer is greater than (but not a
     * multiple of) the maximum packet size, the function driver
     * will only send maximum packet size amount of data. This
     * flag should not be specified if the size of the transfer
     * is less than maximum packet size. */

    USB_HOST_MSD_TRANSFER_FLAGS_MORE_DATA_PENDING
}
USB_HOST_MSD_TRANSFER_FLAGS;

// *****************************************************************************
/* USB HOST MSD Function Driver Events

  Summary:
    USB HOST MSD Function Driver Events

  Description:
    These events are specific to the USB HOST MSD  Function  Driver  instance.
    Each event description contains details on  the  values  of  the  parameters
    passed with event handler. The contents of pData depends on the generated
    event.
 */


typedef enum
{
    /* Attach event */
    USB_HOST_MSD_EVENT_ATTACH,
    /*Detach event*/
    USB_HOST_MSD_EVENT_DETACH,
       /* This event occurs when a scheduled write has completed.
     * The event data is of the type USB_HOST_MSD_EVENT_WRITE_COMPLETE_DATA */
    USB_HOST_MSD_EVENT_WRITE_COMPLETE,
    /* This event occurs when a scheduled read has completed.
     * The event data is of the type USB_HOST_MSD_EVENT_READ_COMPLETE_DATA */
    USB_HOST_MSD_EVENT_READ_COMPLETE ,

    USB_HOST_MSD_EVENT_RESET,
    USB_HOST_MSD_EVENT_MAX_LUN,

    USB_HOST_MSD_READY
} USB_HOST_MSD_EVENT;

// *****************************************************************************
/* USB HOST MSD Event Handler Function Pointer Type.

  Summary:
    USB HOST MSD Event Handler Function Pointer Type.

  Description:
    This defines the USB HOST MSD Function Driver event handler function
    pointer type. The application must register a function of this type to
    receive MSD Function Driver events. The function driver will invoke this
    function with event relevant parameters.

  Remarks:
    None.
*/
typedef bool (*USB_HOST_MSD_APP_EVENT_HANDLER)(
    USB_HOST_MSD_INDEX index,
    USB_HOST_MSD_EVENT event,
    void* pData
);


// *****************************************************************************

/* USB HOST MSD Function Driver data structer

  Summary:
    USB HOST MSD Function Driver information

  Description:
    This structer has the details about USB HOST MSD Function Driver info
    event handler function , states of device , instance , pipes info
    contain all the information about the device driver.

  Remarks:
    None.
 */


typedef struct _USB_HOST_MSD_INSTANCE_ {
    /* use or not*/
    bool assigned;
    /* msd driver state for state machine */
    uint8_t msdState;
    uint8_t msdSubState;
    uint8_t msdSubSubState;
    /* drive number */
    uint8_t driveNumber;
    /* instance number */
    uint8_t instanceNumber;
    uint8_t interfaceNumber;
    /* hcid + device id */
    HC_DEVICE_ID msdDeviceId;
    /* IRPS for each endpoint */
    USB_HOST_IRP controlIRP;
    USB_HOST_IRP bulkInIRP;
    USB_HOST_IRP bulkOutIRP;
    /*Pipes for each endpoint */
    USB_HOST_PIPE_HANDLE controlPipeHandle;
    USB_HOST_PIPE_HANDLE bulkInPipeHandle;
    USB_HOST_PIPE_HANDLE bulkOutPipeHandle;
    /*Rx handle */
    USB_HOST_MSD_TRANSFER_HANDLE rxHandle;
    /*Tx handle */
    USB_HOST_MSD_TRANSFER_HANDLE txHandle;
    /* setup packet information */
    uint8_t setupPacket[8];
    /*Ready for the transmit data */
    uint8_t deviceReady;
    /*connectd MSD devices*/
    uint8_t msdConnectedDevices;
    /* Application callback */
    USB_HOST_MSD_APP_EVENT_HANDLER appEventCallBack;
    /* For Bulk only transfer protocol */
    USB_MSD_CBW   msdCBW;
    USB_MSD_CSW   msdCSW;
    USB_MSD_COMMAND *msdCommand;
    uint8_t       logicalUnitNumber;

} USB_HOST_MSD_INSTANCE;

// *****************************************************************************
/* USB HOST MSD transfer result

  Summary:
    USB HOST MSD transfer result

  Description:
    These macros are useful to identify  USB HOST MSD transfer status.

 */
typedef enum
{
    /* The operation was successful */
    USB_HOST_MSD_RESULT_OK = 1 ,
    /* The transfer size is invalid. Refer to the description
     * of the read or write function for more details */
    USB_HOST_MSD_RESULT_ERROR_TRANSFER_SIZE_INVALID =
                                        USB_ERROR_IRP_SIZE_INVALID ,
    /* The transfer queue is full and no new transfers can be
     * scheduled */
    USB_HOST_MSD_RESULT_ERROR_TRANSFER_QUEUE_FULL =
                                        USB_ERROR_IRP_QUEUE_FULL ,

    /* The specified instance is not provisioned in the system */
    USB_HOST_MSD_INSTANCE_INVALID =
                                USB_ERROR_DEVICE_FUNCTION_INSTANCE_INVALID ,

    /* The specified instance is not confifgured yet */
    USB_HOST_MSD_RESULT_ERROR_INSTANCE_NOT_CONFIGURED =
                            USB_ERROR_DEVICE_FUNCTION_NOT_CONFIGURED ,

    /* invalid event handler */
    USB_HOST_MSD_INVALID_HANDLER = - 15
}USB_HOST_MSD_RESULT;


// *****************************************************************************
/* USB HOST MSD function driver state machine

  Summary:
    USB HOST MSD function driver state machine

  Description:
    These defines are useful to execute state machine with out any blocking
 */

#define SEND_VENDER_COMMANDS                      0x40 //TODO temp


/* usb msd state machine values */
#define USB_HOST_MSD_STATE_DETACHED                 0x0001
#define USB_HOST_MSD_STATE_INITIALIZE_DEVICE        0x0002 //
#define USB_HOST_MSD_STATE_RUNNING                  0x0003
#define USB_HOST_MSD_STATE_RESET_RECOVERY           0x0004
#define USB_HOST_MSD_STATE_CLEAR_DATA_IN            0x0005
#define USB_HOST_MSD_STATE_CLEAR_DATA_OUT           0x0006
#define USB_HOST_MSD_STATE_HOLDING                  0x0007


#define SUBSTATE_WAIT_FOR_ENUMERATION   0x10
#define SUBSTATE_SEND_GET_MAX_LUN       0x11
#define SUBSTATE_WAIT_FOR_MAX_LUN       0x12
#define SUBSTATE_HOLDING                0x13
#define SUBSTATE_SEND_CBW               0x14
#define SUBSTATE_CBW_WAIT               0x15
#define SUBSTATE_TRANSFER_DATA          0x16
#define SUBSTATE_IN_TRANSFER_WAIT       0x17
#define SUBSTATE_OUT_TRANSFER_WAIT      0x18
#define SUBSTATE_REQUEST_CSW            0x19
#define SUBSTATE_CSW_WAIT               0x20
#define SUBSTATE_TRANSFER_DONE          0x21
#define SUBSTATE_SEND_RESET             0x22
#define SUBSTATE_WAIT_FOR_RESET         0x23
#define SUBSTATE_WAIT_FOR_RESET_DONE         0x24
#define SUBSTATE_SEND_CLEAR_IN          0x25
#define SUBSTATE_WAIT_FOR_CLEAR_IN      0x26
#define SUBSTATE_CLEAR_IN_COMPLETE      0x27
#define SUBSTATE_SEND_CLEAR_OUT         0x28
#define SUBSTATE_WAIT_FOR_CLEAR_OUT     0x29
#define SUBSTATE_CLEAR_OUT_COMPLETE     0x2a

// *****************************************************************************
// *****************************************************************************
// Section: MSD Interface Function Definitions
// *****************************************************************************
// *****************************************************************************


USB_ERROR      _USB_HOST_MSD_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *msdinstance,
                                                       uint8_t speed);
void                 _USB_HOST_MSD_DeInitialize(HC_DEVICE_ID id );


USB_HOST_MSD_HANDLE  USB_HOST_MSD_Open( uint8_t  instance );

void                 USB_HOST_MSD_Close( USB_HOST_MSD_HANDLE msdHandle );


USB_HOST_MSD_RESULT  USB_HOST_MSD_EventHandlerSet (
                                  USB_HOST_MSD_INDEX msdIndex ,
                                  USB_HOST_MSD_APP_EVENT_HANDLER appMSDHandler);


void USB_HOST_MSD_Tasks(void);



USB_ERROR USB_HOST_MSD_Transfer (uint8_t driveNumber, USB_MSD_COMMAND *msdCommand);

USB_HOST_MSD_INSTANCE *   _USB_HOST_MSD_getDriveInfo  ( uint8_t driveNumber );

uint8_t  _USB_HOST_MSD_getDriveId(HC_DEVICE_ID  id );


USB_HOST_MSD_RESULT  _USB_HOST_MSD_reset( USB_HOST_MSD_INSTANCE *msdDriverInfo );
uint8_t _USB_HOST_MSD_validateCSW( USB_MSD_CSW csw, USB_MSD_COMMAND * msdCommand);
uint8_t  _USB_HOST_MSD_findInstance(HC_DEVICE_ID id );

 uint8_t _USB_HOST_MSD_BulkInTransferComplete(USB_HOST_IRP *irp);
 void _USB_HOST_MSD_BulkOutTransferComplete( USB_HOST_IRP *irp);

void _USB_HOST_MSD_ControlTransferComplete( USB_HOST_IRP *irp);
#endif

/*********** End of file ***************************************/

