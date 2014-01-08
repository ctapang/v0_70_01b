/**************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_msd.c

  Summary:
    This file contains implementations of both private and public functions
    of USB Device MSD function driver.

  Description:
    This file contains the USB MSD function driver Implementation.
  **************************************************************************/

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

 
/** I N C L U D E S **************************************************/
#include "system/common/sys_module.h"
#include "driver/driver_common.h"
#include "mdd_internal_flash.h"
#include "usb/usb_device_msd.h"


/* Setup packet related */
#define USB_DEVICE_MSD_REQUEST_CLASS_SPECIFIC       0x21
#define USB_DEVICE_MSD_REQUEST_ENDPONT_SPECIFIC     0x02

// These are private macros.
#define USB_DEVICE_MSD_CBW_DIRECTION_BITMASK   0x80




/* SCSI Transparent Command Set Sub-class code */
#define USB_DEVICE_MSD_INQUIRY 				            0x12
#define USB_DEVICE_MSD_READ_FORMAT_CAPACITY 			0x23
#define USB_DEVICE_MSD_READ_CAPACITY 					0x25
#define USB_DEVICE_MSD_READ_10 						    0x28
#define USB_DEVICE_MSD_WRITE_10 						0x2a
#define USB_DEVICE_MSD_REQUEST_SENSE 					0x03
#define USB_DEVICE_MSD_MODE_SENSE  					    0x1a
#define USB_DEVICE_MSD_PREVENT_ALLOW_MEDIUM_REMOVAL 	0x1e
#define USB_DEVICE_MSD_TEST_UNIT_READY 				    0x00
#define USB_DEVICE_MSD_VERIFY 						    0x2f
#define USB_DEVICE_MSD_STOP_START 						0x1b


//------------------------------------------------------------------------------
//ASC/ASCQ Codes for Sense Data (only those that we plan to use):
//The ASC/ASCQ code expand on the information provided in the sense key error
//code, and provide the host with more details about the specific issue/status.
//------------------------------------------------------------------------------
//For use with sense key Illegal request for a command not supported
#define USB_DEVICE_MSD_ASC_NO_ADDITIONAL_SENSE_INFO         0x00
#define USB_DEVICE_MSD_ASCQ_NO_ADDITIONAL_SENSE_INFO        0x00

#define USB_DEVICE_MSD_ASC_INVALID_COMMAND_OPCODE           0x20
#define USB_DEVICE_MSD_ASCQ_INVALID_COMMAND_OPCODE          0x00

// from SPC-3 Table 185
// with sense key Illegal Request for test unit ready
#define USB_DEVICE_MSD_ASC_LUN_NOT_SUPPORTED                0x25
#define USB_DEVICE_MSD_ASCQ_LUN_NOT_SUPPORTED               0x00

//For use with sense key Not ready
#define USB_DEVICE_MSD_ASC_LUN_DOES_NOT_RESPOND             0x05
#define USB_DEVICE_MSD_ASCQ_LUN_DOES_NOT_RESPOND            0x00

//For use with S_UNIT_ATTENTION
#define USB_DEVICE_MSD_ASC_NOT_READY_TO_READY_CHANGE        0x28
#define USB_DEVICE_MSD_ASCQ_MEDIUM_MAY_HAVE_CHANGED         0x00

#define USB_DEVICE_MSD_ASC_MEDIUM_NOT_PRESENT               0x3a
#define USB_DEVICE_MSD_ASCQ_MEDIUM_NOT_PRESENT              0x00

#define USB_DEVICE_MSD_ASC_LUN_NOT_READY_CAUSE_NOT_REPORTABLE      0x04
#define USB_DEVICE_MSD_ASCQ_LUN_NOT_READY_CAUSE_NOT_REPORTABLE     0x00

#define USB_DEVICE_MSD_ASC_LUN_IN_PROCESS                           0x04
#define USB_DEVICE_MSD_ASCQ_LUN_IN_PROCESS                          0x01

#define USB_DEVICE_MSD_ASC_LUN_NOT_READY_INIT_REQD                  0x04
#define USB_DEVICE_MSD_ASCQ_LUN_NOT_READY_INIT_REQD                 0x02

#define USB_DEVICE_MSD_ASC_LUN_NOT_READY_INTERVENTION_REQD          0x04
#define USB_DEVICE_MSD_ASCQ_LUN_NOT_READY_INTERVENTION_REQD         0x03

#define USB_DEVICE_MSD_ASC_LUN_NOT_READY_FORMATTING                 0x04
#define USB_DEVICE_MSD_ASCQ_LUN_NOT_READY_FORMATTING                0x04

#define USB_DEVICE_MSD_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE       0x21
#define USB_DEVICE_MSD_ASCQ_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE      0x00

#define USB_DEVICE_MSD_ASC_WRITE_PROTECTED                          0x27
#define USB_DEVICE_MSD_ASCQ_WRITE_PROTECTED                         0x00



//Possible command status codes returned in the Command Status Wrapper (CSW)
#define USB_DEVICE_MSD_CSW_COMMAND_PASSED  0x00
#define USB_DEVICE_MSD_CSW_COMMAND_FAILED  0x01
#define USB_DEVICE_MSD_CSW_PHASE_ERROR     0x02


/* Sense Key Error Codes */
//------------------------------------------------------------------------------
#define USB_DEVICE_MSD_SENSE_NO_SENSE           0x0
#define USB_DEVICE_MSD_SENSE_RECOVERED_ERROR    0x1
#define USB_DEVICE_MSD_SENSE_NOT_READY          0x2
#define USB_DEVICE_MSD_SENSE_MEDIUM_ERROR       0x3
#define USB_DEVICE_MSD_SENSE_HARDWARE_ERROR     0X4
#define USB_DEVICE_MSD_SENSE_ILLEGAL_REQUEST    0x5
#define USB_DEVICE_MSD_SENSE_UNIT_ATTENTION     0x6
#define USB_DEVICE_MSD_SENSE_DATA_PROTECT       0x7
#define USB_DEVICE_MSD_SENSE_BLANK_CHECK        0x8
#define USB_DEVICE_MSD_SENSE_VENDOR_SPECIFIC    0x9
#define USB_DEVICE_MSD_SENSE_COPY_ABORTED       0xa
#define USB_DEVICE_MSD_SENSE_ABORTED_COMMAND    0xb
#define USB_DEVICE_MSD_SENSE_OBSOLETE           0xc
#define USB_DEVICE_MSD_SENSE_VOLUME_OVERFLOW    0xd
#define USB_DEVICE_MSD_SENSE_MISCOMPARE         0xe

#define USB_DEVICE_MSD_SENSE_CURRENT            0x70
#define USB_DEVICE_MSD_SENSE_DEFERRED           0x71

/* Class Commands */
#define USB_DEVICE_MSD_RESET 0xff
#define USB_DEVICE_MSD_GET_MAX_LUN 0xfe

#define USB_DEVICE_MSD_CSW_SIZE    0x0d	// 10 bytes CSW data
#define USB_DEVICE_MSD_CBW_SIZE    0x1f	// 31 bytes CBW data
#define USB_DEVICE_MSD_MAX_CB_SIZE 0x10    //MSD BOT Command Block (CB) size is 16 bytes maximum (bytes 0x0F-0x1E in the CBW)
#define USB_DEVICE_MSD_CBWFLAGS_RESERVED_BITS_MASK    0x3F //Bits 5..0 of the bCBWFlags byte are reserved, and should be set = 0 by host in order for CBW to be considered meaningful

#define USB_DEVICE_MSD_VALID_CBW_SIGNATURE (uint32_t)0x43425355
#define USB_DEVICE_MSD_VALID_CSW_SIGNATURE (uint32_t)0x53425355


#define USB_DEVICE_MSD_EP0_MAX_SIZE                 USB_EP0_BUFF_SIZE

// *****************************************************************************
/* MSD bulk transfer status enumeration.

  Summary:
    Defines the status of bulk transfer.

  Description:
    Defines the status of bulk transfer.

  Remarks:
    This enum is private to USB MSD function driver.
 */

typedef enum _USB_DEVICE_MSD_BULK_XFER_STATUS_
{
    USB_DEV_MSD_BULK_XFER_COMPLETE,
    USB_DEV_MSD_BULK_XFER_PENDING,
    USB_DEV_MSD_BULK_STALLED
}USB_DEVICE_MSD_BULK_XFER_STATUS;


// *****************************************************************************
/* USB device MSD CBW structure.

  Summary:
   CBW structure.

  Description:
    CBW structure.

  Remarks:
    This structure is private to USB MSD function driver.
 */

typedef struct __attribute__ ((packed)) _USB_DEVICE_MSD_CBW             //31 bytes total Command Block Wrapper
{
    uint32_t dCBWSignature;             // 55 53 42 43h
    uint32_t dCBWTag;					// sent by host, device echos this value in CSW (associated a CSW with a CBW)
    uint32_t dCBWDataTransferLength; 	// number of bytes of data host expects to transfer
    uint8_t bCBWFlags;                  // CBW flags, bit 7 = 0-data out from host to device,
                                        //					= 1-device to host, rest bits 0
    uint8_t bCBWLUN;					// Most Significant 4bits are always zero, 0 in our case as only one logical unit
    uint8_t bCBWCBLength;				// Here most significant 3bits are zero
	uint8_t CBWCB[16];		            // Command block to be executed by the device
} USB_DEVICE_MSD_CBW;


// *****************************************************************************
/* USB device MSD CSW structure.

  Summary:
   CSW structure.

  Description:
   CSW structure.

  Remarks:
    This structure is private to USB MSD function driver.
 */

typedef struct __attribute__ ((packed)) _USB_DEVICE_MSD_CSW			// Command Status Wrapper
{
	uint32_t dCSWSignature;			// 55 53 42 53h Signature of a CSW packet
	uint32_t dCSWTag;					// echo the dCBWTag of the CBW packet
	uint32_t dCSWDataResidue;			// difference in data expected (dCBWDataTransferLength) and actual amount processed/sent
	uint8_t bCSWStatus;				// 00h Command Passed, 01h Command Failed, 02h Phase Error, rest obsolete/reserved
} USB_DEVICE_MSD_CSW;


// *****************************************************************************
/* USB device MSD state enumeration.

  Summary:
    Enumeration values for different MSD states.

  Description:
    Enumeration values for different MSD states.

  Remarks:
    USB device MSD state enumeration.
 */

typedef enum _USB_DEVICE_MSD_STATE_
{
    USB_DEVICE_MSD_STATE_CBW,        
    USB_DEVICE_MSD_STATE_STALL_IN,
    USB_DEVICE_MSD_STATE_STALL_OUT,
    USB_DEVICE_MSD_STATE_DATA_IN,
    USB_DEVICE_MSD_STATE_DATA_OUT,
    USB_DEVICE_MSD_STATE_CSW,
    USB_DEVICE_MSD_STATE_IDLE
}USB_DEVICE_MSD_STATE;


// *****************************************************************************
/* USB device MSD sense data structure.

  Summary:
    Structure for USB device MSD sense data.

  Description:
    Structure for USB device MSD sense data.

  Remarks:
    
 */

typedef union __attribute__((packed)) _USB_DEVICE_MSD_SENSE_DATA_{
	struct
    {
        uint8_t _byte[18];
    };
	struct __attribute__((packed)){
		unsigned ResponseCode:7;			// b6-b0 is Response Code Fixed or descriptor format
		unsigned VALID:1;					// Set to 1 to indicate information field is a valid value

		uint8_t Obsolete;

		unsigned SenseKey:4;				// Refer SPC-3 Section 4.5.6
		unsigned Resv:1;
		unsigned ILI:1;						// Incorrect Length Indicator
		unsigned EOM:1;						// End of Medium
		unsigned FILEMARK:1; 				// for READ and SPACE commands

		uint8_t InformationB0;					// device type or command specific (SPC-33.1.18)
        uint8_t InformationB1;					// device type or command specific (SPC-33.1.18)
        uint8_t InformationB2;					// device type or command specific (SPC-33.1.18)
        uint8_t InformationB3;					// device type or command specific (SPC-33.1.18)
		uint8_t AddSenseLen;					// number of additional sense bytes that follow <=244
		uint32_t CmdSpecificInfo;				// depends on command on which exception occured
		uint8_t ASC;							// additional sense code
		uint8_t ASCQ;							// additional sense code qualifier Section 4.5.2.1 SPC-3
		uint8_t FRUC;							// Field Replaceable Unit Code 4.5.2.5 SPC-3

		uint8_t SenseKeySpecific[3];			// msb is SKSV sense-key specific valied field set=> valid SKS
											// 18-n additional sense bytes can be defined later
											// 18 Bytes Request Sense Fixed Format
	};
} USB_DEVICE_MSD_SENSE_DATA;


// *****************************************************************************
/* USB device MSD media operation state.

  Summary:
    Enumeration values for USB device MSD media operation state.

  Description:
    Enumeration values for USB device MSD media operation state.

  Remarks:

 */

typedef enum _USB_DEVICE_MSD_MEDIA_OPERATION_
{
    USB_DEVICE_MSD_MEDIA_OPERATION_IDLE,
    USB_DEVICE_MSD_MEDIA_OPERATION_COMPLETE,
    USB_DEVICE_MSD_MEDIA_OPERATION_PENDING
}USB_DEVICE_MSD_MEDIA_OPERATION;  


// *****************************************************************************
/* Structure that carries all media info.

  Summary:
    Structure that carries all media info.

  Description:
    
  Remarks:

 */

typedef struct _USB_DEVICE_MSD_MEDIA_INFO_
{
    bool resetSenseData ;
    USB_DEVICE_MSD_SENSE_DATA gblSenseData ;
    uint16_t sectorSize ;
    bool mediaPresent ;
    DRV_HANDLE mediaHandle;
    USB_DEVICE_MSD_MEDIA_OPERATION mediaState;
} USB_DEVICE_MSD_MEDIA_DYNAMIC_DATA;


// *****************************************************************************
/* USB MSD device instance structure.

  Summary:
    USB MSD device instance structure

  Description:

  Remarks:
    This is a private structure of USB MSD device.
 */

typedef struct _USB_DEVICE_MSD_INSTANCE_
{
    DRV_HANDLE          hUsbDevHandle;                        // Handle to USB device
    USB_DEVICE_MSD_CBW msdCbw;                          // MSD CBW structure.
    uint8_t msdBuffer[USB_DEVICE_MSD_MAX_SECTOR_SIZE];  // msd buffer.
    USB_DEVICE_MSD_STATE msdMainState;                  // Main State.
    USB_DEVICE_MSD_CSW msdCSW;                          // CSW.
    uint32_t rxTxTotalDataByteCount;                    // Receive /Transmit data byte count.
    USB_DEVICE_MSD_MEDIA_DYNAMIC_DATA mediaDynamicData[USB_DEVICE_MSD_MAX_LUN]; // Dynamic data related to media.
    USB_ENDPOINT bulkEndpointTx;
    USB_ENDPOINT bulkEndpointRx;
    uint16_t bulkEndpointRxSize;
    uint16_t bulkEndpointTxSize;
    USB_DEVICE_IRP irpTx;
    USB_DEVICE_IRP irpRx;
    USB_DEVICE_MSD_INIT * msdInit;
}USB_DEVICE_MSD_INSTANCE;


// *****************************************************************************
/* USB MSD device DWORD structure.

  Summary:
    USB MSD device  DWORD structure.

  Description:

  Remarks:
    This is a private structure of USB MSD device.
 */

typedef union
{
    uint32_t Val;
    uint16_t w[2];
    uint8_t v[4];
    struct
    {
        uint16_t LW;
        uint16_t HW;
    } word;
    struct
    {
        uint8_t LB;
        uint8_t HB;
        uint8_t UB;
        uint8_t MB;
    } byte;

} USB_DEVICE_MSD_DWORD_VAL;


// *****************************************************************************
/* USB device MSD instance objects.

  Summary:
    USB device MSD instance objects.

  Description:

  Remarks:
    
 */

static USB_DEVICE_MSD_INSTANCE gUsbDeviceMsdInstance[USB_DEVICE_MSD_MAX_INSTANCES];


// *****************************************************************************
/* USB device MSD init objects.

  Summary:
    USB device MSD init objects.

  Description:

  Remarks:

 */

USB_DEVICE_MSD_INIT gUsbDeviceMsdInit[USB_DEVICE_MSD_MAX_INSTANCES];


// *****************************************************************************
/* USB device MSD private function signatures.
 */
// *****************************************************************************
/* Function:
    void _USB_DEVICE_MSD_CallBackBulkRxTransfer( void *  hMsdInstance, DRV_USB_PIPE_HANDLE hPipe,
                                                 DRV_USB_XFER_HANDLE hTransfer,
                                                 unsigned short int  transferByteCount  ,
                                                 DRV_USB_DEVICE_XFER_STATUS  statusTransfer )


  Summary:
    This callback will be called by the controller driver after the bulk out
    transfer.

  Description:


  Precondition:
    None.

  Parameters:
    hMsdInstance          -   Handle to MSD instance.
    hPipe                 -   Handle to pipe instance.
    hTransfer             -   Transfer handle.
    transferByteCount     -   Transfer byte count.
    statusTransfer        -   Transfer status.

  Returns:
    none.
 
  Remarks:

*/

void _USB_DEVICE_MSD_CallBackBulkRxTransfer( USB_DEVICE_IRP *  hMsdInstance );


// *****************************************************************************
/* Function:
   void _USB_DEVICE_MSD_ResetSenseData
                                ( USB_DEVICE_MSD_SENSE_DATA *  msdSenseDataPtr )

  Summary:
    Reset's sense data that is pointed by "msdSenseDataPtr".

  Description:


  Precondition:
    None.

  Parameters:
    msdSenseDataPtr       -   Pointer to sense data.
   

  Returns:
    none.

  Remarks:

*/

void _USB_DEVICE_MSD_ResetSenseData( USB_DEVICE_MSD_SENSE_DATA *  msdSenseDataPtr );


// *****************************************************************************
/* Function:
   USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_ProcessCommand(SYS_MODULE_INDEX iMSD,
                                            uintptr_t *rxTxBufferAdrs,
                                            uint32_t * rxTxBufferSize,
                                                   uint8_t * commandStatus )

  Summary:
    Process the CBW command.

  Description:
    This function processes the command and returns buffer address, buffer
    size and command status.

  Precondition:
    None.

  Parameters:
    iMSD                -  MSD instance index.
    rxTxBufferAdrs      -  Receive/Transmit buffer address.
    rxTxBufferSize      -  Receive/Transmit buffer size.
    commandStatus       -  Command status.

  Returns:
    MSD state.

  Remarks:

*/

USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_ProcessCommand(SYS_MODULE_INDEX iMSD,
                                            uintptr_t *rxTxBufferAdrs,
                                            uint32_t * rxTxBufferSize,
                                                   uint8_t * commandStatus );


// *****************************************************************************
/* Function:
   USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_VerifyCommand(SYS_MODULE_INDEX iMSD )

  Summary:
    Verifies CBW and checks the validity of the command.
 
  Description:

  Precondition:
    None.

  Parameters:
    iMSD                -  MSD instance index.
   
  Returns:
    MSD state.

  Remarks:

*/

USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_VerifyCommand(SYS_MODULE_INDEX iMSD );


// *****************************************************************************
/* Function:
   USB_ERROR_STATUS _USB_DEVICE_MSD_Initialization ( SYS_MODULE_INDEX iMSD,
                                                 SYS_MODULE_INDEX iDriver,
                                                 SYS_MODULE_INDEX iUsbDevice,
                                                 void* funcDriverInit ,
                                                 uint8_t* pConfigDesc )

  Summary:
    Does MSD initialization.

  Description:
    

  Precondition:
    None.

  Parameters:
    iMSD                -  MSD instance index.
    iDriver             -  Receive/Transmit buffer address.
    iUsbDevice          -  Receive/Transmit buffer size.
    funcDriverInit      -  Command status.
    pConfigDesc         -  Pointer to configuration descriptor.

  Returns:
   Success state.

  Remarks:

*/

void _USB_DEVICE_MSD_InitializeByDescriptorType(SYS_MODULE_INDEX iMSD, DRV_HANDLE usbDeviceHandle,
                                            void* funcDriverInit, uint8_t intfNumber, uint8_t altSetting,
                                            uint8_t descriptorType, uint8_t * pDescriptor);


// *****************************************************************************
/* Function:
   USB_ERROR_STATUS _USB_DEVICE_MSD_Deinitialization ( SYS_MODULE_INDEX iMSD,
                                                 SYS_MODULE_INDEX iDriver,
                                                 SYS_MODULE_INDEX iUsbDevice,
                                                 void* funcDriverInit ,
                                                 uint8_t* pConfigDesc )

  Summary:
    Does MSD initialization.

  Description:
    

  Precondition:
    None.

  Parameters:
    iMSD                -  MSD instance index.
    iDriver             -  Receive/Transmit buffer address.
    iUsbDevice          -  Receive/Transmit buffer size.
    funcDriverInit      -  Command status.
    pConfigDesc         -  Pointer to configuration descriptor.

  Returns:
   Success state.

  Remarks:

*/

void _USB_DEVICE_MSD_Deinitialization ( SYS_MODULE_INDEX iMSD );


// *****************************************************************************
/* Function:
   USB_ERROR_STATUS _USB_DEVICE_MSD_CheckInterface ( SYS_MODULE_INDEX funcDriverIndex ,
                                                 uint16_t interfaceNumber )

  Summary:
    This function returns success if the interface number belongs to this instance
    of the function driver.

  Description:


  Precondition:
    None.

  Parameters:
    funcDriverindex - Instance index of MSD function driver.
    interfaceNumber - Interface number.

  Returns:
    USB_ERROR_OK if interface number belongs to this instance of the
    function driver.

  Remarks:

*/

USB_ERROR _USB_DEVICE_MSD_CheckInterface ( SYS_MODULE_INDEX funcDriverIndex ,
                                                 uint16_t interfaceNumber );


// *****************************************************************************
/* Function:
  void _USB_DEVICE_MSD_EndpointNotification(SYS_MODULE_INDEX MSDIndex,
                       USB_ENDPOINT epAddress, uint16_t epSize, uint8_t epType)

  Summary:
    This function is called by the device layer to inform the MSD
    about the endpoints that are opened for this particular instance
    of the MSD.
  Description:


  Precondition:
    None.

  Parameters:
    MSDIndex  - Instance index of MSD function driver.
    epAddress - Endpoint address and direction.
    epSize    - Endpoint size.
    epType    - Endpoint type.

  Returns:
     None.
  Remarks:

*/

void _USB_DEVICE_MSD_DescriptorNotification(SYS_MODULE_INDEX funcDriverIndex,
                                 uint8_t descriptorType, uint8_t * pDescriptor);


// *****************************************************************************
/* Function:
   bool _USB_DEVICE_MSD_ControlTransferHandler ( SYS_MODULE_INDEX iMSD ,
            SETUP_PKT *setupPkt, USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlDataObject )

  Summary:
    MSD control transfer handler.

  Description:
    MSD control transfer handler. This is the callback the device layer calls
    when there is a setup packet that is targeted to this particular instance
    of MSD.

  Precondition:
    None.

  Parameters:
    iMSD          -  Instance index of MSD function driver.
    setupPkt      -  Pointer to setup packet buffer.
    controlDataObject - Control transfer data object.

  Returns:
    None.

  Remarks:

*/

void  _USB_DEVICE_MSD_ControlTransferHandler (  USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                                SYS_MODULE_INDEX iMSD,
                                                USB_DEVICE_CONTROL_TRANSFER_EVENT transferState,
                                                USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA  * pEventData );


// *****************************************************************************
/* Function:
   void _USB_DEVICE_MSD_Tasks ( SYS_MODULE_INDEX iMSD )

  Summary:
   MSD function driver tasks.

  Description:


  Precondition:
    None.

  Parameters:
    iMSD          -  Instance index of MSD function driver.
    
  Returns:
    None.

  Remarks:

*/

void _USB_DEVICE_MSD_Tasks ( SYS_MODULE_INDEX iMSD );

/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_CallBackBulkTxTransfer( void *  handle )

  Summary:
    This is a callback function that gets called by controller driver,
    after the completion of bulk-in transfer.

  Description:

  Precondition:
    None.

  Parameters:
    hMsdInstance        : Handle to MSD instance.
    hPipe               : Handle to pipe.
    hTransfer           : Handle to transfers.
    transferByteCount   : Total byte count.
    statusTransfer      : Status of the transfer.

  Returns:
    None.


  Remarks:
    None
*/

void _USB_DEVICE_MSD_CallBackBulkTxTransfer( USB_DEVICE_IRP *  handle );

// *****************************************************************************
/* MSD Device function driver structure

  Summary:
    Defines the function driver structure required for the device layer

  Description:
    This data type defines the function driver structure required for the
    device layer

  Remarks:
    This structure is private to USB stack.
 */

const USB_DEVICE_FUNCTION_DRIVER msdFunctionDriver = {
    /* MSD init function */
    .initializeByDescriptor = _USB_DEVICE_MSD_InitializeByDescriptorType ,

    /* MSD de-init function */
    .deInitialize = _USB_DEVICE_MSD_Deinitialization , 

      
    /* MSD set-up packet handler */
    .controlTransferNotification = _USB_DEVICE_MSD_ControlTransferHandler ,

    /* MSD tasks function */
    .tasks = _USB_DEVICE_MSD_Tasks
};


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_InitializeEndpoint( USB_DEVICE_MSD_INSTANCE * msdInstance,
                                             DRV_HANDLE usbDevHandle,
                                             USB_ENDPOINT_DESCRIPTOR * epDescriptor)

  Summary:
    USB Device MSD endpoint initialization.

  Description:
    Initialize endpoints and endpoint related variables here.

 Precondition:
    None.

  Parameters:
    msdInstance         : MSD instance.
    usbDevHandle        : USB device handle.
    epDescriptor        : Endpoint descriptor.
 
  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_InitializeEndpoint( USB_DEVICE_MSD_INSTANCE * msdInstance,
                                         DRV_HANDLE usbDevHandle,
                                         USB_ENDPOINT_DESCRIPTOR * epDescriptor)
{

    if( epDescriptor->transferType == USB_TRANSFER_TYPE_BULK )
    {
        if(epDescriptor->dirn == USB_DATA_DIRECTION_DEVICE_TO_HOST)
        {
           // Save the Tx endpoint information.
            msdInstance->bulkEndpointTx = epDescriptor->bEndpointAddress;
            msdInstance->bulkEndpointTxSize =  epDescriptor->wMaxPacketSize;
            // Open the endpoint.
            USB_DEVICE_EndpointEnable(usbDevHandle, msdInstance->bulkEndpointTx, epDescriptor->transferType,
                                          epDescriptor->wMaxPacketSize);            
        }
        else
        {
            // Direction is OUT
            msdInstance->bulkEndpointRx = epDescriptor->bEndpointAddress;
            msdInstance->bulkEndpointRxSize = epDescriptor->wMaxPacketSize;

            // Now since device layer has already opened the bulk endpoint we can submit an
            // IRP to receive the CBW.
            msdInstance->irpRx.data = (void *)&msdInstance->msdCbw;
            msdInstance->irpRx.size = epDescriptor->wMaxPacketSize;
            msdInstance->irpRx.flags = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;

             // Open the endpoint.
            USB_DEVICE_EndpointEnable(usbDevHandle, msdInstance->bulkEndpointRx, epDescriptor->transferType,
                                          epDescriptor->wMaxPacketSize);          

            // Arm rx endpoint to receive data.
            USB_DEVICE_IRPSubmit( msdInstance->hUsbDevHandle,
                                  msdInstance->bulkEndpointRx,
                                  &msdInstance->irpRx);
        }
    }
    else
    {
        SYS_ASSERT( false, "USB DEVICE MSD: MSD doesnot support anything other than Bulk endpoints. Please check the descriptors.");
    }    
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_InitializeInterface( SYS_MODULE_INDEX iMSD,
                                              DRV_HANDLE usbDeviceHandle,
                                              void * funcDriverInit,
                                              USB_INTERFACE_DESCRIPTOR * intfDesc)

  Summary:
    USB Device MSD Interface Initialization.

  Description:
    Initialize only the interface related variables here.

 Precondition:
    None.

  Parameters:
    iMSD                : Function driver index.
    usbDeviceHandle     : USB device handle.
    funcDriverInit      : Pointer to MSD init structure.
    intfDesc            : Pointer to interface descriptor.
 *
  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_InitializeInterface( SYS_MODULE_INDEX iMSD, DRV_HANDLE usbDeviceHandle, void * funcDriverInit,
                                            USB_INTERFACE_DESCRIPTOR * intfDesc)
{
    uint8_t count;

    // Reset MSD instance.
   // memset( &gUsbDeviceMsdInit[iMSD], 0, sizeof( USB_DEVICE_MSD_INSTANCE ) );

    // Copy the msd init structure.
    memcpy(&gUsbDeviceMsdInit[iMSD], funcDriverInit, sizeof(USB_DEVICE_MSD_INIT));

    // Save the pointer to msd init.
    gUsbDeviceMsdInstance[iMSD].msdInit = &gUsbDeviceMsdInit[iMSD];

    // Validate all MDD drive handles.
    for(count = 0; count < gUsbDeviceMsdInit[iMSD].numberOfLogicalUnits; count++)
    {
        gUsbDeviceMsdInstance[iMSD].mediaDynamicData[count].mediaHandle = DRV_HANDLE_INVALID;

        if((gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.mediaDetect == NULL)
           || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.mediaInitState == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.open == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.readCapacity == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.readSectorSize == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.writeProtectState == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.sectorRead == NULL)
                || (gUsbDeviceMsdInit[iMSD].mediaInit[count].mediaCallBackPtrs.sectorWrite == NULL) )
        {
            //  None of the media callback functions can be NULL.
            SYS_ASSERT (true, "USB Device MSD: None of the Media callback functions can be NULL");
        }
    }

     // Initializing some of the variables.
    gUsbDeviceMsdInstance[iMSD].hUsbDevHandle = usbDeviceHandle;

    // Partially initialize the IRP with known data.
    gUsbDeviceMsdInstance[iMSD].irpRx.userData = ( uintptr_t )&gUsbDeviceMsdInstance[iMSD];
    gUsbDeviceMsdInstance[iMSD].irpTx.userData = ( uintptr_t )&gUsbDeviceMsdInstance[iMSD];
    gUsbDeviceMsdInstance[iMSD].irpRx.status = USB_DEVICE_IRP_STATUS_COMPLETED;
    gUsbDeviceMsdInstance[iMSD].irpTx.status = USB_DEVICE_IRP_STATUS_COMPLETED;
    gUsbDeviceMsdInstance[iMSD].irpTx.callback = &_USB_DEVICE_MSD_CallBackBulkTxTransfer;
    gUsbDeviceMsdInstance[iMSD].irpRx.callback = &_USB_DEVICE_MSD_CallBackBulkRxTransfer;

}

/******************************************************************************
  Function:
    USB_ERROR_STATUS _USB_DEVICE_MSD_InitializeByDescriptorType ( SYS_MODULE_INDEX iMSD,
                                                 SYS_MODULE_INDEX iDriver,
                                                 SYS_MODULE_INDEX iUsbDevice,
                                                 void* funcDriverInit ,
                                                 uint8_t* pConfigDesc )

  Summary:
    USB Device MSD Initialization. The device layer calls this function to
    initialize the MSD based on the descriptor found (from the configurations descriptor).
    MSD is responsible for

  Description:
    This function initializes MSD function driver based on the descriptor.

 Precondition:
    None.

  Parameters:
    iMSD                : Function driver index.
    usbDeviceHandle     : USB device handle.
    funcDriverInit      : Pointer to MSD init structure.
    intfNumber          : The interface number the descriptor identified
                          by descriptorType belongs to.
    altSetting          : The alternate setting of the descriptor that is identified
                          by descriptorType belongs to.
    pDescriptor         : Pointer to the descriptor. This can point to interface descriptor
                          or endpoint descriptor based on the descriptorType.
  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_InitializeByDescriptorType(SYS_MODULE_INDEX iMSD, DRV_HANDLE usbDeviceHandle,
                                            void* funcDriverInit, uint8_t intfNumber, uint8_t altSetting,
                                            uint8_t descriptorType, uint8_t * pDescriptor)
 {

    SYS_ASSERT(altSetting == 0, "USB Device MSD: MSD supports only one setting \
                                and does not support alternate settings ");
    
    switch(descriptorType )
    {
        case USB_DESCRIPTOR_ENDPOINT:
            // Device layer has configured and opened an endpoint.
            // We just have to save the endpoint and arm if necessary.
            
            _USB_DEVICE_MSD_InitializeEndpoint(&gUsbDeviceMsdInstance[iMSD], usbDeviceHandle,
                                                (USB_ENDPOINT_DESCRIPTOR *)pDescriptor);
            break;

        case USB_DESCRIPTOR_INTERFACE:
            // Do interface specific initialization here.
            _USB_DEVICE_MSD_InitializeInterface(iMSD, usbDeviceHandle, funcDriverInit,
                                                (USB_INTERFACE_DESCRIPTOR *)pDescriptor);
             
            break;

        default:
            SYS_ASSERT( false, "USB DEVICE MSD: MSD doesnot support this descriptor type. Please check the descriptors");
            break;
    }

    
 }


/******************************************************************************
  static USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_MSD_ControlTransferHandler ( SYS_MODULE_INDEX iMSD ,
            SETUP_PKT *setupPkt, USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlDataObject )

  Summary:
    MSD control transfer handler.

  Description:
    MSD control transfer handler. This is the callback the device layer calls
    when there is a setup packet that is targeted to this particular instance
    of MSD.

  Precondition:
    None.

  Parameters:
    iMSD          -  Instance index of MSD function driver.
    setupPkt      -  Pointer to setup packet buffer.
    controlDataObject - Control transfer data object.

  Returns:
    None.
*/
void _USB_DEVICE_MSD_ControlTransferHandler ( USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                              SYS_MODULE_INDEX MSDIndex,
                                              USB_DEVICE_CONTROL_TRANSFER_EVENT transferState,
                                              USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData )
{
    USB_DEVICE_MSD_INSTANCE *msdThisInstance;
    USB_SETUP_PACKET * setupPkt = pEventData->setupRequest;
    
    msdThisInstance = &gUsbDeviceMsdInstance[MSDIndex] ;

    if( transferState == USB_DEVICE_CONTROL_SETUP_REQUEST )
    {
        if( setupPkt->bmRequestType & USB_DEVICE_MSD_REQUEST_CLASS_SPECIFIC )
        {
            // We have got setup request.
            switch ( setupPkt->bRequest )
            {
                case USB_DEVICE_MSD_GET_MAX_LUN:
                    //First make sure all request parameters are correct:
                    //MSD BOT specs require wValue to be == 0x0000, and wLengh == 1
                    if((setupPkt->wValue != 0) || (setupPkt->wLength != 1))
                    {
                        return ;
                    }


                    msdThisInstance->msdBuffer[0]  = msdThisInstance->msdInit->numberOfLogicalUnits-1;

                    USB_DEVICE_ControlSend( msdThisInstance->hUsbDevHandle,
                                            controlHandle,
                                            msdThisInstance->msdBuffer, 1 );

                break;

                case USB_DEVICE_MSD_RESET:
                    // Reset the MSD states.
                    // Cancel the pipes

                    USB_DEVICE_ControlStatus( msdThisInstance->hUsbDevHandle,
                                              controlHandle,
                                              USB_DEVICE_CONTROL_STATUS_OK );
                    break;

                default:
                    // Stall the EP0 tx endpoint.
                    //USB_DEVICE_ControlTransferPipeStall( msdThisInstance->iDevLayer, USB_EP_TX);
                     USB_DEVICE_ControlStatus( msdThisInstance->hUsbDevHandle,
                                               controlHandle,
                                               USB_DEVICE_CONTROL_STATUS_ERROR );
                    break;
            } // switch ( setupPkt->bRequest )
        }
    }
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_CallBackBulkRxTransfer( void * handle )

  Summary:
    This is a callback function that gets called by controller driver,
    after the completion of bulk-out transfer.

  Description:

  Precondition:
    None.

  Parameters:
    handle : Handle to IRP

  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_CallBackBulkRxTransfer( USB_DEVICE_IRP *  handle )
{

  
    /*USB_DEVICE_IRP * hIRP = (USB_DEVICE_IRP *)handle;
    msdThisInstance = (USB_DEVICE_MSD_INSTANCE *)hIRP->userData;*/

    // TODO: Add code if required in the future.

               
  

}

/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_CallBackBulkTxTransfer( void *  handle )

  Summary:
    This is a callback function that gets called by controller driver,
    after the completion of bulk-in transfer.

  Description:

  Precondition:
    None.

  Parameters:
    hMsdInstance        : Handle to IRP.
  

  Returns:
    None.


  Remarks:
    None
*/

void _USB_DEVICE_MSD_CallBackBulkTxTransfer( USB_DEVICE_IRP *  handle )
{

   /* USB_DEVICE_MSD_INSTANCE *msdThisInstance;
    USB_DEVICE_IRP * hIRP = (USB_DEVICE_IRP *)handle;*/

    // TODO: Add code if required in the future.

}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_PreDataStageRoutine ( SYS_MODULE_INDEX iMSD )

  Summary:
    Do some routine pre-data stage checks.

  Description:
    After we received CBW and before entering data stage we will have to
    do some settings.

  Precondition:
    None.

  Parameters:
    iMSD    : MSD index.

  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_PreDataStageRoutine ( SYS_MODULE_INDEX iMSD )
{

    uint8_t logicalUnit;

    logicalUnit = gUsbDeviceMsdInstance[iMSD].msdCbw.bCBWLUN;
    
    // Reset media state
    gUsbDeviceMsdInstance[iMSD].mediaDynamicData[logicalUnit].mediaState = USB_DEVICE_MSD_MEDIA_OPERATION_IDLE;
    
    // Reset the total bytes sent/rcvd counter.
    gUsbDeviceMsdInstance[iMSD].rxTxTotalDataByteCount = 0;   
  
    // Reset irp rx size.
    gUsbDeviceMsdInstance[iMSD].irpRx.size = 0;
       
    // See if last command was request sense. If so host has already read the
    // sense data. Now we should reset sense data.
    if(gUsbDeviceMsdInstance[iMSD].mediaDynamicData[logicalUnit].resetSenseData)
    {
        gUsbDeviceMsdInstance[iMSD].mediaDynamicData[logicalUnit].resetSenseData = false;
        _USB_DEVICE_MSD_ResetSenseData(&gUsbDeviceMsdInstance[iMSD].mediaDynamicData[logicalUnit].gblSenseData);
    }
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_PostDataStageRoutine ( SYS_MODULE_INDEX iMSD )

  Summary:
    Do some post data stage routines (Before we initiate CSW).

  Description:


  Precondition:
    None.

  Parameters:
    iMSD     : MSD index  

  Returns:
    none.    

  Remarks:
    None
*/

void _USB_DEVICE_MSD_PostDataStageRoutine ( SYS_MODULE_INDEX iMSD )
{
    uint32_t residueLength;
    // Build CSW.
    gUsbDeviceMsdInstance[iMSD].msdCSW.dCSWSignature = USB_DEVICE_MSD_VALID_CSW_SIGNATURE;
    gUsbDeviceMsdInstance[iMSD].msdCSW.dCSWTag = gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWTag;

    residueLength = (gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWDataTransferLength - gUsbDeviceMsdInstance[iMSD].rxTxTotalDataByteCount);
    
           
    if(residueLength >= gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWDataTransferLength)
    {
        // Clip residue length to transfer length requested by host and as indicated in CBW.
        residueLength = gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWDataTransferLength;

    }

    if(  residueLength != 0 )
    {
        // If residue is not zero, then we have a phase error.
        // This takes care of Error case 1, case 2 and case 3.
         gUsbDeviceMsdInstance[iMSD].msdCSW.bCSWStatus = USB_DEVICE_MSD_CSW_PHASE_ERROR;

    }

    // Residue length to CSW.
    gUsbDeviceMsdInstance[iMSD].msdCSW.dCSWDataResidue = residueLength;
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_Tasks ( SYS_MODULE_INDEX iMSD )

  Summary:
    This function handles the main MSD state machine.

  Description:

  Precondition:
    None.

  Parameters:
    iMSD                : MSD index.
   
  Returns:
    None.

  Remarks:
    None
*/
void _USB_DEVICE_MSD_Tasks ( SYS_MODULE_INDEX iMSD )
{
    uintptr_t rxTxBufferAdrs;
    uint32_t rxTxBufferSize;    
    uint8_t commandStatus;
  

    
    // Check if we are busy. See if IRPs are busy.
    if(  ( gUsbDeviceMsdInstance[iMSD].irpRx.status <= USB_DEVICE_IRP_STATUS_COMPLETED_SHORT )
            && ( gUsbDeviceMsdInstance[iMSD].irpTx.status <= USB_DEVICE_IRP_STATUS_COMPLETED_SHORT )
            && ( !USB_DEVICE_EndpointIsStalled( gUsbDeviceMsdInstance[iMSD].hUsbDevHandle,
                                                    gUsbDeviceMsdInstance[iMSD].bulkEndpointTx )) )
    {
         
        switch (gUsbDeviceMsdInstance[iMSD].msdMainState)
        {

            case USB_DEVICE_MSD_STATE_CBW :
                // Process the command.
                gUsbDeviceMsdInstance[iMSD].msdMainState = _USB_DEVICE_MSD_VerifyCommand (iMSD);
                // We have got a command. We need to reset some variables
                _USB_DEVICE_MSD_PreDataStageRoutine( iMSD );
                break;

            case USB_DEVICE_MSD_STATE_STALL_IN:
                // Stall the IN endpoint.
                gUsbDeviceMsdInstance[iMSD].msdCSW.bCSWStatus = USB_DEVICE_MSD_CSW_COMMAND_FAILED;
                USB_DEVICE_EndpointStall(gUsbDeviceMsdInstance[iMSD].hUsbDevHandle,
                                             gUsbDeviceMsdInstance[iMSD].bulkEndpointTx );

                // Set Rx/Tx byte count to requested transfer length.
                // Eventhough, we have not sent the entire bytes, this is very much required to assume that
                // we have sent all the bytes. Otherwise we generate a PHASE ERROR in post data-stage routine.
                gUsbDeviceMsdInstance[iMSD].rxTxTotalDataByteCount = gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWDataTransferLength;

                gUsbDeviceMsdInstance[iMSD].msdMainState = USB_DEVICE_MSD_STATE_CSW;
                break;


            case USB_DEVICE_MSD_STATE_DATA_IN:
                // Check if we have any/more data to send.
                gUsbDeviceMsdInstance[iMSD].msdMainState = _USB_DEVICE_MSD_ProcessCommand(iMSD, &rxTxBufferAdrs, &rxTxBufferSize, &commandStatus );

                 gUsbDeviceMsdInstance[iMSD].msdCSW.bCSWStatus= commandStatus;

                if( rxTxBufferSize != 0) // If response size is 0, this means data is not yet ready. We shall retry in the next pass.
                {

                    gUsbDeviceMsdInstance[iMSD].rxTxTotalDataByteCount += rxTxBufferSize;  

                    gUsbDeviceMsdInstance[iMSD].irpTx.data = (void *)rxTxBufferAdrs;
                    gUsbDeviceMsdInstance[iMSD].irpTx.size = rxTxBufferSize;
                    if( rxTxBufferSize < gUsbDeviceMsdInstance[iMSD].msdCbw.dCBWDataTransferLength )
                    {
                        gUsbDeviceMsdInstance[iMSD].irpRx.flags = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
                    }
                    else
                    {
                        gUsbDeviceMsdInstance[iMSD].irpRx.flags = USB_DEVICE_IRP_FLAG_DATA_PENDING;
                    }

                    // Arm bulk IN endpoint to send data
                    USB_DEVICE_IRPSubmit( gUsbDeviceMsdInstance[iMSD].hUsbDevHandle,
                                               gUsbDeviceMsdInstance[iMSD].bulkEndpointTx,
                                               &gUsbDeviceMsdInstance[iMSD].irpTx);


                }
                break;

            case USB_DEVICE_MSD_STATE_DATA_OUT:

                // Check if we have any/more data to receive.
                gUsbDeviceMsdInstance[iMSD].msdMainState = _USB_DEVICE_MSD_ProcessCommand(iMSD, &rxTxBufferAdrs, &rxTxBufferSize, &commandStatus );

                 gUsbDeviceMsdInstance[iMSD].msdCSW.bCSWStatus = commandStatus;

                if( rxTxBufferSize != 0) // If response size is 0, this means data is not yet ready. We shall retry in the next pass.
                {

                    gUsbDeviceMsdInstance[iMSD].rxTxTotalDataByteCount += rxTxBufferSize;                

                    gUsbDeviceMsdInstance[iMSD].irpRx.data = (void *)rxTxBufferAdrs;
                    gUsbDeviceMsdInstance[iMSD].irpRx.size = rxTxBufferSize;                    

                    // Arm bulk OUT endpoint to send data
                    USB_DEVICE_IRPSubmit( gUsbDeviceMsdInstance[iMSD] .hUsbDevHandle,
                                               gUsbDeviceMsdInstance[iMSD].bulkEndpointRx,
                                               &gUsbDeviceMsdInstance[iMSD].irpRx);
                }

                break;

            case USB_DEVICE_MSD_STATE_CSW:

                _USB_DEVICE_MSD_PostDataStageRoutine(iMSD);

                 // Arm bulk IN endpoint to send CSW
                gUsbDeviceMsdInstance[iMSD].irpTx.data = (void *)&gUsbDeviceMsdInstance[iMSD].msdCSW;
                gUsbDeviceMsdInstance[iMSD].irpTx.size = sizeof(USB_DEVICE_MSD_CSW);
                gUsbDeviceMsdInstance[iMSD].irpTx.flags = USB_DEVICE_IRP_FLAG_DATA_PENDING;

                // Arm bulk IN endpoint to send data
                USB_DEVICE_IRPSubmit( gUsbDeviceMsdInstance[iMSD].hUsbDevHandle,
                                           gUsbDeviceMsdInstance[iMSD].bulkEndpointTx,
                                           &gUsbDeviceMsdInstance[iMSD].irpTx);

                gUsbDeviceMsdInstance[iMSD].irpRx.data = (void *)&gUsbDeviceMsdInstance[iMSD].msdCbw;
                gUsbDeviceMsdInstance[iMSD].irpRx.size = gUsbDeviceMsdInstance[iMSD].bulkEndpointRxSize;
                gUsbDeviceMsdInstance[iMSD].irpRx.flags = USB_DEVICE_IRP_FLAG_DATA_PENDING;


                // Arm bulk OUT endpoint to send data
                USB_DEVICE_IRPSubmit( gUsbDeviceMsdInstance[iMSD].hUsbDevHandle,
                                           gUsbDeviceMsdInstance[iMSD].bulkEndpointRx,
                                           &gUsbDeviceMsdInstance[iMSD].irpRx);


                gUsbDeviceMsdInstance[iMSD].msdMainState = USB_DEVICE_MSD_STATE_CBW;

               
                break;

            case USB_DEVICE_MSD_STATE_STALL_OUT:
            case USB_DEVICE_MSD_STATE_IDLE:
                break;
        }
    }
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_MediaOperationComplete(void * mediaState )

  Summary:
    This is a callback function called by the media after the completion of
    media operation.

  Description:

  Precondition:
    None.

  Parameters:
    mediaState          : Reference handle given by MSD.
    success             : True/False.

  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_MediaOperationComplete(void * mediaState, bool success )
{
    if(success == true)
    {
       (* (USB_DEVICE_MSD_MEDIA_OPERATION *)mediaState) = USB_DEVICE_MSD_MEDIA_OPERATION_COMPLETE;
    }   
}


/******************************************************************************
  Function:
    void _USB_DEVICE_MSD_CheckAndUpdateMediaState(SYS_MODULE_INDEX iMSD,
                                                        uint8_t logicalUnit)

  Summary:
     This function must be called periodically in the MSD task to
     update the media state.

  Description:

  Precondition:
    None.

  Parameters:
    iMSD          :   MSD index
    logicalUnit   :   logicalUnit

  Returns:
    None.

  Remarks:
    None
*/

void _USB_DEVICE_MSD_CheckAndUpdateMediaState(SYS_MODULE_INDEX iMSD, uint8_t logicalUnit)
{

    USB_DEVICE_MSD_MEDIA_FUNCTIONS * lunFunctionPtr;
    USB_DEVICE_MSD_MEDIA_DYNAMIC_DATA * mediaDynamicData;
    SYS_MODULE_INDEX mediaInstanceIndex;
    //DRV_HANDLE mediaHandle;


    mediaDynamicData = &gUsbDeviceMsdInstance[iMSD].mediaDynamicData[logicalUnit];
    lunFunctionPtr = &gUsbDeviceMsdInit[iMSD].mediaInit[logicalUnit].mediaCallBackPtrs;
    mediaInstanceIndex = gUsbDeviceMsdInit[iMSD].mediaInit[logicalUnit].instanceIndex;

    if( lunFunctionPtr->mediaInitState (mediaInstanceIndex) > 0 )
    {
        // Media is initialized.        
        if( mediaDynamicData->mediaHandle == DRV_HANDLE_INVALID )
        {
            // This media is initialized but not yet opened. Try to open the media.
            mediaDynamicData->mediaHandle =
                    lunFunctionPtr->open( mediaInstanceIndex, 0 );
        }

        if ( mediaDynamicData->mediaHandle != DRV_HANDLE_INVALID )
        {
            // Media is initialized. Now check if media is present.
            mediaDynamicData->mediaPresent =
                        lunFunctionPtr->mediaDetect(mediaDynamicData->mediaHandle);

            // Read sector size.
            mediaDynamicData->sectorSize =
                     lunFunctionPtr->readSectorSize(mediaDynamicData->mediaHandle);
             
           SYS_ASSERT(mediaDynamicData->sectorSize <= USB_DEVICE_MSD_MAX_SECTOR_SIZE,
                    "USB Device MSD Layer: Increase the value of USB_DEVICE_MSD_MAX_SECTOR_SIZE to max value used");

            
        }
    }
    else
    {
        // Media is not yet initialized by the system. So consider it as media not being present.
        mediaDynamicData->mediaPresent = false;
    }    
}


/******************************************************************************
  Function:
    USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_VerifyCommand(SYS_MODULE_INDEX iMSD )

  Summary:
    This function verifies the recieved CBW.

  Description:

  Precondition:
    None.

  Parameters:
    iMSD    : MSD index.
 
  Returns:
    Next MSD state.

  Remarks:
    None
*/

USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_VerifyCommand(SYS_MODULE_INDEX iMSD )
{

    USB_DEVICE_MSD_CBW *lCBW;
    USB_DEVICE_MSD_STATE msdNextState = USB_DEVICE_MSD_STATE_CSW ;
    //uint32_t residueLength;
    //bool commandSupported = true;

     //The host asked for the total capacity of the device.  The response
    //packet is 8-bytes (32-bits for last LBA implemented, 32-bits for block size).
    //USB_DEVICE_MSD_DWORD_VAL sectorSize;
    //USB_DEVICE_MSD_DWORD_VAL capacity;


    lCBW = (USB_DEVICE_MSD_CBW *)&gUsbDeviceMsdInstance[iMSD].msdCbw;

    if((gUsbDeviceMsdInstance[iMSD].irpRx.size == USB_DEVICE_MSD_CBW_SIZE)
                    && (lCBW->dCBWSignature == USB_DEVICE_MSD_VALID_CBW_SIGNATURE))
    {
            if((lCBW->bCBWLUN < gUsbDeviceMsdInit[iMSD].numberOfLogicalUnits )      //Verify the command is addressed to a supported LUN
                &&(lCBW->bCBWCBLength <= USB_DEVICE_MSD_MAX_CB_SIZE)  //Verify the claimed CB length is reasonable/valid
                &&(lCBW->bCBWCBLength >= 0x01)                        //Verify the claimed CB length is reasonable/valid
                &&((lCBW->bCBWFlags & USB_DEVICE_MSD_CBWFLAGS_RESERVED_BITS_MASK) == 0x00))   //Verify reserved bits are clear
                {


                   //Look for media state update.
                   _USB_DEVICE_MSD_CheckAndUpdateMediaState(iMSD, lCBW->bCBWLUN);
                    
                    //Decide on the next state.
                    if (lCBW->bCBWFlags & USB_DEVICE_MSD_CBW_DIRECTION_BITMASK)
                    {
                        msdNextState = USB_DEVICE_MSD_STATE_DATA_IN;
                    }
                    else //else direction must be OUT from host
                    {
                        msdNextState = USB_DEVICE_MSD_STATE_DATA_OUT;

                    }
            }
     }
    else
    {
        //else the CBW wasn't meaningful.  Section 6.4 of BOT specs v1.0 says,
	    //"The response of a device to a CBW that is not meaningful is not specified."
	    //Lets keep arming the rx bulk endpoint and hope at one point of time
	    //the host sends correct CBW.
        
        
 
        
        msdNextState = USB_DEVICE_MSD_STATE_CBW;

    }

    return msdNextState;
}

/******************************************************************************
  Function:
    void  _USB_DEVICE_MSD_GetBlockAddressAndLength(USB_DEVICE_MSD_CBW * lCBW,
                                USB_DEVICE_MSD_DWORD_VAL * logicalBlockAddress,
                                USB_DEVICE_MSD_DWORD_VAL * logicalBlockLength)

  Summary:
    This function retrieves the logical unit's block address and block length
    from CBW.

  Description:

  Precondition:
    None.

  Parameters:
    lCBW                    : Pointer to CBW structure.
    logicalBlockAddress     : Logical block address.
    logicalBlockLength      : Logical block length.

  Returns:
    None.

  Remarks:
    None
*/

void  _USB_DEVICE_MSD_GetBlockAddressAndLength(USB_DEVICE_MSD_CBW * lCBW,
                                    USB_DEVICE_MSD_DWORD_VAL * logicalBlockAddress,
                                  USB_DEVICE_MSD_DWORD_VAL * logicalBlockLength)
{
    // Get block address and block length from CBW command structure.
    logicalBlockAddress->v[3] =  lCBW->CBWCB[2];
    logicalBlockAddress->v[2] =  lCBW->CBWCB[3];
    logicalBlockAddress->v[1] =  lCBW->CBWCB[4];
    logicalBlockAddress->v[0] =  lCBW->CBWCB[5];        
    logicalBlockLength->byte.HB = lCBW->CBWCB[7];   //MSB of Transfer Length (in number of blocks, not bytes)
    logicalBlockLength->byte.LB = lCBW->CBWCB[8];   //LSB of Transfer Length (in number of blocks, not bytes)   
    
}    

/******************************************************************************
  Function:
    void  __USB_DEVICE_MSD_SaveBlockAddressAndLength(USB_DEVICE_MSD_CBW * lCBW,
                                USB_DEVICE_MSD_DWORD_VAL * logicalBlockAddress,
                                USB_DEVICE_MSD_DWORD_VAL * logicalBlockLength)

  Summary:
    This function saves the logical unit's block address and block length back
    into the CBW structure.

  Description:

  Precondition:
    None.

  Parameters:
    lCBW                            : Pointer to CBW structure.
    logicalBlockAddress             : logical block address.


  Returns:
    None.

  Remarks:
    None
*/

void  _USB_DEVICE_MSD_SaveBlockAddressAndLength(USB_DEVICE_MSD_CBW * lCBW,
                                        USB_DEVICE_MSD_DWORD_VAL * logicalBlockAddress,
                                        USB_DEVICE_MSD_DWORD_VAL * logicalBlockLength)
{
    // Save back the updated address and logical block into the CBW command structure.
    lCBW->CBWCB[2] = logicalBlockAddress->v[3];
    lCBW->CBWCB[3] = logicalBlockAddress->v[2];
    lCBW->CBWCB[4] = logicalBlockAddress->v[1];
    lCBW->CBWCB[5] = logicalBlockAddress->v[0];
    lCBW->CBWCB[7] = logicalBlockLength->byte.HB;   //MSB of Transfer Length (in number of blocks, not bytes)
    lCBW->CBWCB[8] = logicalBlockLength->byte.LB;   //LSB of Transfer Length (in number of blocks, not bytes)
    
}    


/******************************************************************************
  Function:
    USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_ProcessCommand(SYS_MODULE_INDEX iMSD,
                                            uintptr_t *rxTxBufferAdrs,
                                         uint32_t * rxTxBufferSize, uint8_t * commandStatus )
  Summary:
    Processes the command.

  Description:

  Returns:
    Next MSD state.


  Remarks:
    None
*/
USB_DEVICE_MSD_STATE _USB_DEVICE_MSD_ProcessCommand(SYS_MODULE_INDEX iMSD,
                            uintptr_t *rxTxBufferAdrs,
                            uint32_t * rxTxBufferSize, uint8_t * commandStatus )
{
    
    USB_DEVICE_MSD_CBW *lCBW;
    USB_DEVICE_MSD_STATE msdNextState = USB_DEVICE_MSD_STATE_CSW ;
    //uint32_t residueLength;
    //bool commandSupported = true;
    USB_DEVICE_MSD_MEDIA_INIT_DATA * thisLUNMediaInitData;
    USB_DEVICE_MSD_MEDIA_DYNAMIC_DATA * thisLUNMediaInfo;
    uint8_t logicalUnit;
    USB_DEVICE_MSD_INSTANCE * thisMSDInstance;
    uint8_t * msdBuffer;
    USB_DEVICE_MSD_INIT * thisMSDInit;
  
     //The host asked for the total capacity of the device.  The response
    //packet is 8-bytes (32-bits for last LBA implemented, 32-bits for block size).
    USB_DEVICE_MSD_DWORD_VAL sectorSize;
    USB_DEVICE_MSD_DWORD_VAL capacity;
    USB_DEVICE_MSD_DWORD_VAL logicalBlockLength;
    USB_DEVICE_MSD_DWORD_VAL logicalBlockAddress;
    USB_DEVICE_MSD_DWORD_VAL transferLength;

    /* Initializing some of the local variables */
    lCBW = (USB_DEVICE_MSD_CBW *)&gUsbDeviceMsdInstance[iMSD].msdCbw; // Pointer to CBW
    logicalUnit = lCBW->bCBWLUN;    // The CBW addresses this CBW.
    thisMSDInstance = &gUsbDeviceMsdInstance[iMSD]; // MSD instance.
    thisMSDInit = &gUsbDeviceMsdInit[iMSD] ; //Media init pointer
    thisLUNMediaInfo = &thisMSDInstance->mediaDynamicData[logicalUnit] ; // Media info pointer.
    thisLUNMediaInitData = &gUsbDeviceMsdInit[iMSD].mediaInit[logicalUnit];
    msdBuffer = &gUsbDeviceMsdInstance[iMSD].msdBuffer[0]; // msd buffer.

    // These are some assumptions before we start.
    // These are going to change when we further parse the command.
    (* rxTxBufferSize) = 0; // Assume that we don't have anything to send or receive.
    (* commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_PASSED; // Assume that the command is going to pass.

    // Reset some of the local variables.
    logicalBlockAddress.Val = 0;
    logicalBlockLength.Val = 0;
    transferLength.Val = 0;
    capacity.Val = 0;
    sectorSize.Val = 0;
    
    // Process command.
    switch(lCBW->CBWCB[0])
    {
        case USB_DEVICE_MSD_INQUIRY:
           // Build the response to inquiry command.
           *rxTxBufferAdrs = (uintptr_t)&thisLUNMediaInitData->inquiryResponse ;
           *rxTxBufferSize = sizeof(USB_DEVICE_MSD_INQUIRY_RESPONSE);
           break;


        case USB_DEVICE_MSD_MODE_SENSE:
            // Pad the bytes with zeroes first.
            memset(msdBuffer, 0, lCBW->dCBWDataTransferLength);
            // Add required information.
            msdBuffer[0] = 0x03;
            msdBuffer[1] = 0x00;
            msdBuffer[2]= thisLUNMediaInitData->mediaCallBackPtrs.writeProtectState( thisLUNMediaInfo->mediaHandle);
            msdBuffer[3]= 0x00;
            // Response buffer address.
            *rxTxBufferAdrs = (uintptr_t)&msdBuffer[0];
            // Response buffer size is same as whatever host requested for.
            *rxTxBufferSize = lCBW->dCBWDataTransferLength;
            break;

        case USB_DEVICE_MSD_REQUEST_SENSE:
            if(thisLUNMediaInfo->mediaPresent == false)
            {
                // Media is not present.
                thisLUNMediaInfo->gblSenseData.SenseKey = USB_DEVICE_MSD_SENSE_NOT_READY;
                thisLUNMediaInfo->gblSenseData.ASC = USB_DEVICE_MSD_ASC_MEDIUM_NOT_PRESENT;
                thisLUNMediaInfo->gblSenseData.ASCQ = USB_DEVICE_MSD_ASCQ_MEDIUM_NOT_PRESENT;
            }

            // Request sense.
            // Host requests for a sense, if the device has responded with an error.
            *rxTxBufferAdrs = (uintptr_t)&thisLUNMediaInfo->gblSenseData;
            *rxTxBufferSize = sizeof(USB_DEVICE_MSD_SENSE_DATA);
            
            // Now the host is reading the sense data, we are good to reset in the next cbw stage.
            thisLUNMediaInfo->resetSenseData = true;
            break;

        case USB_DEVICE_MSD_TEST_UNIT_READY:
            msdNextState = USB_DEVICE_MSD_STATE_CSW;

            if( thisLUNMediaInfo->mediaPresent == false )
            {
                //Status failed.
                (* commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_FAILED;
            }
            break;


        case USB_DEVICE_MSD_READ_CAPACITY:

            //get the information from the physical media
            capacity.Val = thisLUNMediaInitData->mediaCallBackPtrs.readCapacity( thisLUNMediaInfo->mediaHandle );
            sectorSize.Val = thisLUNMediaInitData->mediaCallBackPtrs.readSectorSize( thisLUNMediaInfo->mediaHandle );
                    
            //Copy the data to the buffer.  Host expects the response in big endian format.
            msdBuffer[0] = capacity.v[3];
            msdBuffer[1] = capacity.v[2];
            msdBuffer[2] = capacity.v[1];
            msdBuffer[3] = capacity.v[0];

            msdBuffer[4] = sectorSize.v[3];
            msdBuffer[5] = sectorSize.v[2];
            msdBuffer[6] = sectorSize.v[1];
            msdBuffer[7] = sectorSize.v[0];

            *rxTxBufferAdrs = (uintptr_t)&msdBuffer[0];
            *rxTxBufferSize = 8;

        break;

        case USB_DEVICE_MSD_READ_10:
            //The host issues a "Read 10" request when it wants to read some number
            //of 10-bit length blocks (512 byte blocks) of data from the media.

            // Let's first assume that the next CBW state by default is
            // going to be USB_DEVICE_MSD_STATE_DATA_IN. We shall change to CSW
            // state (see code further below) only if we are done reading all the blocks.
            msdNextState = USB_DEVICE_MSD_STATE_DATA_IN; 
            
            _USB_DEVICE_MSD_GetBlockAddressAndLength(lCBW, &logicalBlockAddress, &logicalBlockLength);            

            if( thisLUNMediaInfo->mediaState == USB_DEVICE_MSD_MEDIA_OPERATION_IDLE  )
            {
                // There are no bytes queued with the controller driver.
                // Read next sector from media and queue it up with the controller driver.
                thisLUNMediaInfo->mediaState = USB_DEVICE_MSD_MEDIA_OPERATION_PENDING;
                // Try to read one block.
                thisLUNMediaInitData->mediaCallBackPtrs.sectorRead(thisLUNMediaInfo->mediaHandle, logicalBlockAddress.Val,
                                (uint8_t*)&msdBuffer[0], &thisLUNMediaInfo->mediaState, &_USB_DEVICE_MSD_MediaOperationComplete );
                                
                logicalBlockLength.Val --;
                // Increment logical block address. In the next pass read from this address.
                logicalBlockAddress.Val ++;
                
                _USB_DEVICE_MSD_SaveBlockAddressAndLength(lCBW, &logicalBlockAddress, &logicalBlockLength);
                
            }
            else if( thisLUNMediaInfo->mediaState == USB_DEVICE_MSD_MEDIA_OPERATION_COMPLETE )
            {
                thisLUNMediaInfo->mediaState = USB_DEVICE_MSD_MEDIA_OPERATION_IDLE;
                // Last operation was complete. We have something to send to host.
                *rxTxBufferSize = thisLUNMediaInfo->sectorSize; // sector size.
           
                *rxTxBufferAdrs = (uintptr_t)&msdBuffer[0];
                
                if(logicalBlockLength.Val <= 0)
                {
                    msdNextState = USB_DEVICE_MSD_STATE_CSW;
                }   
            }       
            break;

        case USB_DEVICE_MSD_WRITE_10:
            // We have recieved some data from host. This needs to be written into media.
            //But befrore we write into the media, check if the media is write protected 
      		if((thisLUNMediaInitData->mediaCallBackPtrs.writeProtectState( thisLUNMediaInfo->mediaHandle ) == 0x80))
            {
                // Media is write protected.
                //Set sense keys so the host knows what caused the error.
          	    thisLUNMediaInfo->gblSenseData.SenseKey = USB_DEVICE_MSD_SENSE_DATA_PROTECT;
          	    thisLUNMediaInfo->gblSenseData.ASC = USB_DEVICE_MSD_ASC_WRITE_PROTECTED;
          	    thisLUNMediaInfo->gblSenseData.ASCQ = USB_DEVICE_MSD_ASCQ_WRITE_PROTECTED;
                // Request main state machine to stall the endpoint.
                msdNextState = USB_DEVICE_MSD_STATE_STALL_IN;
                // Indicate in CSW that command failed.
                (*commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_FAILED;
          	}
            else
            {

                /* Media is not write protected. Go ahead writing the media */
                /* Get the logical block address, transfer length fields from Command Block Wrapper */
                _USB_DEVICE_MSD_GetBlockAddressAndLength(lCBW, &logicalBlockAddress, &logicalBlockLength);

                 /* Let's stay in data-out state until we are done writing all logical blocks*/
                msdNextState = USB_DEVICE_MSD_STATE_DATA_OUT;


                if( thisMSDInstance->irpRx.size ) // See if we have some data.
                {
                    /* Yes, we have received a sector worth of data */
                    /* Now check if media is free */
                    if( thisLUNMediaInfo->mediaState != USB_DEVICE_MSD_MEDIA_OPERATION_PENDING  )
                    {
                        // Put media into busy state..
                        thisLUNMediaInfo->mediaState = USB_DEVICE_MSD_MEDIA_OPERATION_PENDING;

                        // Write data into the media.
                        thisLUNMediaInitData->mediaCallBackPtrs.sectorWrite(thisLUNMediaInfo->mediaHandle, logicalBlockAddress.Val,
                                                                    (uint8_t*)&msdBuffer[0], &thisLUNMediaInfo->mediaState,
                                                                    &_USB_DEVICE_MSD_MediaOperationComplete );
                        //We have written a sector. Now decrement the block.
                        logicalBlockLength.Val --;
                        // Increment logical block address. In the next pass write into this address.
                        logicalBlockAddress.Val ++;

                        // Save back the updated address and logical block
                         _USB_DEVICE_MSD_SaveBlockAddressAndLength(lCBW, &logicalBlockAddress, &logicalBlockLength);

                        if( (logicalBlockLength.Val <= 0) || (thisMSDInstance->irpRx.status == USB_DEVICE_IRP_STATUS_COMPLETED_SHORT) )
                        {
                            // We have received all the blocks or host has completed the transfer.
                            /* End the data stage and move to CSW state */
                            *rxTxBufferSize = 0; // No more data to be received.
                            msdNextState = USB_DEVICE_MSD_STATE_CSW;

                        }
                    }
                }
                
                if(logicalBlockLength.Val > 0 )
                {
                     // We are not yet done receiving all the blocks.
                    // Request the main state machine to receive a sector worth of data.
                    *rxTxBufferSize = thisLUNMediaInfo->sectorSize; // endpoint size
                    // Buffer address, where the main state machine has to copy the incomming data.
                    *rxTxBufferAdrs = (uintptr_t)&msdBuffer[0];
                }
            }              
            break;
            
         case USB_DEVICE_MSD_VERIFY:
         case USB_DEVICE_MSD_STOP_START:
            msdNextState = USB_DEVICE_MSD_STATE_CSW;
            if(thisLUNMediaInfo->mediaPresent == false)
            {
                (* commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_FAILED;
            }
            break;
            
        case USB_DEVICE_MSD_PREVENT_ALLOW_MEDIUM_REMOVAL:
        	thisLUNMediaInfo->gblSenseData.SenseKey=USB_DEVICE_MSD_SENSE_ILLEGAL_REQUEST;
        	thisLUNMediaInfo->gblSenseData.ASC=USB_DEVICE_MSD_ASC_INVALID_COMMAND_OPCODE;
        	thisLUNMediaInfo->gblSenseData.ASCQ=USB_DEVICE_MSD_ASCQ_INVALID_COMMAND_OPCODE;
        	(* commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_FAILED;
			msdNextState = USB_DEVICE_MSD_STATE_CSW;
            break;

        default:
            _USB_DEVICE_MSD_ResetSenseData(&thisLUNMediaInfo->gblSenseData);
            // Set sense data.
            thisLUNMediaInfo->gblSenseData.SenseKey = USB_DEVICE_MSD_SENSE_ILLEGAL_REQUEST;
            thisLUNMediaInfo->gblSenseData.ASC = USB_DEVICE_MSD_ASC_INVALID_COMMAND_OPCODE;
            thisLUNMediaInfo->gblSenseData.ASCQ = USB_DEVICE_MSD_ASCQ_INVALID_COMMAND_OPCODE;
            msdNextState = USB_DEVICE_MSD_STATE_STALL_IN;
            (* commandStatus) = USB_DEVICE_MSD_CSW_COMMAND_FAILED;          
            break;
    }
   
    return msdNextState;
}


// *****************************************************************************

/* Function:
    void    _USB_DEVICE_MSD_Deinitialization (SYS_MODULE_INDEX iMSD)

  Summary:
    MSD function driver deinitialization.

  Description:
    Deinitializes the given instance of the MSD function driver. This function
    is called by the USB DEVICE layer.

  Precondition:
    None.

  Parameters:
    iMSD	- USB function driver index

  Returns:
    None.

  
  Remarks:
    This function is internal to the USB stack. This API should not be
    called explicitly.
 */

void _USB_DEVICE_MSD_Deinitialization ( SYS_MODULE_INDEX iMSD )
{
    USB_DEVICE_MSD_INSTANCE * msdInstance;
    USB_DEVICE_MSD_MEDIA_INIT_DATA * mediaInit;
    uint8_t count;

    msdInstance = &gUsbDeviceMsdInstance[ iMSD ] ;
    mediaInit = &gUsbDeviceMsdInit[iMSD].mediaInit[0];

    // close all open logical units..
    for(count = 0; count < gUsbDeviceMsdInit[iMSD].numberOfLogicalUnits; count++)
    {
        if( msdInstance->mediaDynamicData[count].mediaHandle != DRV_HANDLE_INVALID )
        {
            mediaInit->mediaCallBackPtrs.close(msdInstance->mediaDynamicData[count].mediaHandle);
            
        }
    }
    // Cancel all IRPs
    USB_DEVICE_IRPCancelAll( msdInstance->hUsbDevHandle, msdInstance->bulkEndpointRx );
    
    // Cancel all IRPs on tx.
    USB_DEVICE_IRPCancelAll( msdInstance->hUsbDevHandle, msdInstance->bulkEndpointTx );

    // close the endpoint.
    USB_DEVICE_EndpointDisable( msdInstance->hUsbDevHandle, msdInstance->bulkEndpointRx );

    USB_DEVICE_EndpointDisable( msdInstance->hUsbDevHandle, msdInstance->bulkEndpointTx );

    

}




/******************************************************************************
 	Function:
 		void USB_DEVICE_MSD_ResetSenseData
 *                                     ( USB_DEVICE_MSD_SENSE_DATA * senseData )

 	Description:
 		This routine resets the Sense Data, initializing the
 		structure USB_DEVICE_MSD_SENSE_DATA gblSenseData.

 	PreCondition:
 		None

 	Parameters:
        senseData - Pointer to sense data.

 	Return Values:
 		None

 	Remarks:
 		None

  *****************************************************************************/
void _USB_DEVICE_MSD_ResetSenseData( USB_DEVICE_MSD_SENSE_DATA * senseData )
{
   	senseData->ResponseCode = USB_DEVICE_MSD_SENSE_CURRENT;
	senseData->VALID = 0;			// no data in the information field
	senseData->Obsolete = 0x0;
	senseData->SenseKey = USB_DEVICE_MSD_SENSE_NO_SENSE;
	//gblSenseData.Resv;
	senseData->ILI = 0;
	senseData->EOM = 0;
	senseData->FILEMARK = 0;
	senseData->InformationB0 = 0x00;
	senseData->InformationB1 = 0x00;
	senseData->InformationB2 = 0x00;
	senseData->InformationB3 = 0x00;
	senseData->AddSenseLen = 0x0a;	// n-7 (n=17 (0..17))
	senseData->CmdSpecificInfo = 0x00000000;
	senseData->ASC = 0x0;
	senseData->ASCQ = 0x0;
	senseData->FRUC = 0x0;
	senseData->SenseKeySpecific[0] = 0x0;
	senseData->SenseKeySpecific[1] = 0x0;
	senseData->SenseKeySpecific[2] = 0x0;
}

