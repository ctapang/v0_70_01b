/*******************************************************************************
  USART Driver Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart.h

  Summary:
    USART Driver Interface Definition

  Description:
    The USART device driver provides a simple interface to manage the USART or
    UART modules on Microchip microcontrollers.  This file defines the
    interface definition for the USART driver.
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
#ifndef _DRV_USART_H
#define _DRV_USART_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  A file that maps the interface definitions above to appropriate static
          implementations (depending on build mode) is included at the bottom of
          this file.
*/

#include "system/common/sys_common.h"
#include "driver/driver_common.h"
#include "peripheral/usart/plib_usart.h"
#include "system/common/sys_module.h"
#include "system/int/sys_int.h"


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Driver USART Module Index reference

  Summary:
    USART driver index definitions

  Description:
    These constants provide timer driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the DRV_USART_Initialize and  DRV_USART_Open
    routines to identify the driver instance in use.
*/

#define      DRV_USART_INDEX_0      0
#define      DRV_USART_INDEX_1      1
#define      DRV_USART_INDEX_2      2
#define      DRV_USART_INDEX_3      3
#define      DRV_USART_INDEX_4      4
#define      DRV_USART_INDEX_5      5


// *****************************************************************************
/* USART Driver Module Index Count

  Summary:
    Number of valid USART driver indices

  Description:
    This constant identifies USART driver index definitions.

  Remarks:
    This constant should be used in place of hard-coded numeric literals.
    
    This value is part-specific.
*/

#define DRV_USART_INDEX_COUNT     USART_NUMBER_OF_MODULES


// *****************************************************************************
/* USART Transfer Handle

  Summary:
    Handle for requested transfer..

  Description:
    Handle for requested transfer..

  Remarks:
    None
*/

typedef uintptr_t DRV_USART_XFER_HANDLE;


// *****************************************************************************
/* USART Modes of Operation

  Summary:
    Identifies the modes of the operation of the USART module

  Description:
    This data type identifies the modes of the operation of the USART module.

  Remarks:
    Not all modes are available on all microcontrollers.  Refer to the data
    sheet for the microcontroller in use.
*/

typedef enum
{
    DRV_USART_OPERATION_MODE_IRDA                                     = (1 << 0),
    /* RS232 Mode (Asynchronous Mode of Operation) */
    DRV_USART_OPERATION_MODE_RS232               /*DOM-IGNORE-BEGIN*/ = (1 << 1)  /*DOM-IGNORE-END*/,

    /* RS485 Mode (Asynchronous Mode of Operation) */
    DRV_USART_OPERATION_MODE_RS485               /*DOM-IGNORE-BEGIN*/ = (1 << 2) /*DOM-IGNORE-END*/,

    /* Synchronous Master Mode */
    DRV_USART_OPERATION_MODE_SYNCHRONOUS_MASTER  /*DOM-IGNORE-BEGIN*/ = (1 << 3) /*DOM-IGNORE-END*/,

    /* Synchronous Slave Mode */
    DRV_USART_OPERATION_MODE_SYNCHRONOUS_SLAVE   /*DOM-IGNORE-BEGIN*/ = (1 << 4) /*DOM-IGNORE-END*/,

    /* Loopback Mode */
    DRV_USART_OPERATION_MODE_LOOPBACK            /*DOM-IGNORE-BEGIN*/ = (1 << 5) /*DOM-IGNORE-END*/

} DRV_USART_OPERATION_MODES;

// *****************************************************************************
/* USART Callback Function

   Summary
    Pointer to a USART callback function

   Description
    This data type defines a pointer callback function.

   Remarks:
    A USART callback function must have the following function signature:

        void MyCallBack ( DRV_USART_BUFFER_HANDLE *bufferHandle );

    Where "MyCallBack" can be any name desired as the routine is called through
    the pointer.

    A pointer of this type is passed into the DRV_USART_RegisterCallbacks
    routine.
*/

typedef void (*DRV_USART_CALLBACK) (void);


// *****************************************************************************
/* USART Handshake Modes

  Summary:
    Identifies the handshaking modes available on the USART

  Description:
    This data type identifies the handshaking modes available on the USART 
    module.

  Remarks:
    Not all modes are available on all micro-controllers.
*/

typedef enum
{
    /* Handshaking occurs in Flow Control Mode */
    DRV_USART_HANDSHAKE_MODE_FLOWCONTROL    /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,

    /* Handshaking occurs in Simplex Mode */
    DRV_USART_HANDSHAKE_MODE_SIMPLEX        /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /* No Handshaking */
    DRV_USART_HANDSHAKE_MODE_NONE           /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/

} DRV_USART_HANDSHAKE_MODES;


// *****************************************************************************
/* USART Line Control Modes

  Summary:
    Identifies the line control modes available

  Description:
    This data type identifies the line control modes available

  Remarks:
    None
*/

typedef enum
{
    /* 8 Data Bits, No Parity, 1 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_8NONE1  /*DOM-IGNORE-BEGIN*/ = (0 << 0) /*DOM-IGNORE-END*/,

    /* 9 Data Bits, No Parity, 1 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_9NONE1  /*DOM-IGNORE-BEGIN*/ = (1 << 1) /*DOM-IGNORE-END*/,

    /* 8 Data Bits, Even Parity, 1 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_8EVEN1  /*DOM-IGNORE-BEGIN*/ = (1 << 2) /*DOM-IGNORE-END*/,

    /* 8 Data Bits, Even Parity, 2 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_8EVEN2  /*DOM-IGNORE-BEGIN*/ = (1 << 3) /*DOM-IGNORE-END*/,

    /* 8 Data Bits, Odd Parity, 1 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_8ODD1   /*DOM-IGNORE-BEGIN*/ = (1 << 4) /*DOM-IGNORE-END*/,

    /* 8 Data Bits, Odd Parity, 2 Stop Bits*/
    DRV_USART_LINE_CONTROL_MODE_8ODD2   /*DOM-IGNORE-BEGIN*/ = (1 << 5) /*DOM-IGNORE-END*/

} DRV_USART_LINE_CONTROL_MODES;


// *****************************************************************************
/* USART Initialization flags

  Summary:
    Defines specific initialization features

  Description:
    Defines the various flags which determine specific modes

  Remarks:
    None
*/

typedef enum
{

    /* Flag to setup Wake on Start Operation*/
    DRV_USART_INIT_FLAG_WAKE_ON_START_ENABLE    /*DOM-IGNORE-BEGIN*/ = (1 << 1)  /*DOM-IGNORE-END*/,

    /* Flag to enable auto baud detection enable. */
    DRV_USART_INIT_FLAG_AUTO_BAUD_ENABLE        /*DOM-IGNORE-BEGIN*/ = (1 << 2)  /*DOM-IGNORE-END*/

} DRV_USART_INIT_FLAGS;


// *****************************************************************************
/* USART Client Status

  Summary
    Defines the client status

  Description
    Defines the various client status codes.

  Remarks:
    None
*/

typedef enum
{
    /* Up and running, ready to start new operations */
    DRV_USART_CLIENT_STATUS_READY
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_READY + 0 /*DOM-IGNORE-END*/,

    /* Operation in progress, unable to start a new one */
    DRV_USART_CLIENT_STATUS_BUSY
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_BUSY      /*DOM-IGNORE-END*/,

    /* Overrun Error Occured */
    DRV_USART_OVERRUN_ERROR
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_ERROR - 0 /*DOM-IGNORE-END*/,

    /* Parity Error */
    DRV_USART_PARITY_ERROR
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_ERROR - 1 /*DOM-IGNORE-END*/,

    /* Framing Error */
    DRV_USART_FRAMING_ERROR
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_ERROR - 2 /*DOM-IGNORE-END*/,

    /* client Invalid */
    DRV_USART_STATUS_INVALID
        /*DOM-IGNORE-BEGIN*/  = DRV_CLIENT_STATUS_ERROR - 3 /*DOM-IGNORE-END*/

} DRV_USART_CLIENT_STATUS;


// *****************************************************************************
/* Operation Mode Initialization

  Summary:
    Defines the initialization data required for different operation modes of
    USART

  Description:
    This data type defines the initialization data required for different
    operation modes of USART.

  Remarks:
    None
*/

typedef union
{
    /* Initialization for RS485 mode */
    struct
    {
        /* Address of the device. */
        uint8_t address;

    }RS485Init;

} DRV_USART_OPERATION_MODE_INIT;


// *****************************************************************************
/* USART Driver Initialization Data

  Summary:
    Defines the data required to initialize or reinitialize the USART driver

  Description:
    This data type defines the data required to initialize or reinitialize the 
    USART driver.

  Remarks:
    Not all the init features are available for all the microcontrollers
*/

typedef struct
{
    /* System module initialization */
    SYS_MODULE_INIT                 moduleInit;

    /* Identifies USART hardware module (PLIB-level) ID */
    USART_MODULE_ID                 usartID;

    /* Operation Modes of the driver */
    uint8_t                         operationMode;

    /* Flags for the usart initialization */
    uint8_t                         initFlags;

    /* Control the line control configuration */
    DRV_USART_LINE_CONTROL_MODES    lineControlMode;

    /* Baud Rate value to be used, if not using auto baud */
    uint32_t                        brgValue;

    /* Operation mode initialization data */
    DRV_USART_OPERATION_MODE_INIT   operationModeInit;

    /* Handshake Mode */
    DRV_USART_HANDSHAKE_MODES       handShakeMode;

    /* Interrupt Source for TX Interrupt */
    //INT_SOURCE                    txInterruptSource;
    uint32_t                          txInterruptSource;
    /* Interrupt Source for RX Interrupt */
    //INT_SOURCE                  rxInterruptSource;
    uint32_t                          rxInterruptSource;
    /* Interrupt Source for Error Interrupt */
    //INT_SOURCE                  errorInterruptSource;
    uint32_t                          errorInterruptSource;

    uint32_t                          rxQueueSize;

    uint32_t                          txQueueSize;

} DRV_USART_INIT;

// *****************************************************************************
/* USART IO Types

   Summary
    Defines the IO types that can be serviced by the USART driver

   Description
    This enumeration defines the IO types that can be serviced by the USART
    driver.

   Remarks:
    None
*/

typedef enum
{
    /* Write Buffer*/
    DRV_USART_BUFFER_FLAG_WRITE                 /*DOM-IGNORE-BEGIN*/ = 1 << 0/*DOM-IGNORE-END*/,

    /* Write Buffer After Sending Break*/
    DRV_USART_BUFFER_FLAG_WRITE_AFTER_BREAK     /*DOM-IGNORE-BEGIN*/ = (1 << 1 | 1 << 0)/*DOM-IGNORE-END*/,

    /* Write Buffer to the address */
    DRV_USART_BUFFER_FLAG_WRITE_TO_ADDRESS      /*DOM-IGNORE-BEGIN*/ = (1 << 2| 1 << 0)/*DOM-IGNORE-END*/,

    /* Raed Buffer from the address */
    DRV_USART_BUFFER_FLAG_READ_FROM_ADDRESS     /*DOM-IGNORE-BEGIN*/ = (1 << 4| 1 << 3)/*DOM-IGNORE-END*/,

    /* Read Buffer */
    DRV_USART_BUFFER_FLAG_READ                  /*DOM-IGNORE-BEGIN*/ = 1 << 3/*DOM-IGNORE-END*/,

    /* Instructs the driver to stop processing if error is encountered */
    DRV_USART_BUFFER_FLAG_STOP_ON_ERROR         /*DOM-IGNORE-BEGIN*/ = 1 << 5/*DOM-IGNORE-END*/

}DRV_USART_BUFFER_FLAGS;

// *****************************************************************************
/* USART Driver IO Buffer

   Summary
    IO buffer information structure

   Description
    This structure holds information that the client must pass the driver to
    enqueue a buffer to be transferred by a read or write operation.

   Remarks:
    A pointer to an instance of this structure must be passed to the
    DRV_USART_BufferAdd routine.
*/

typedef struct
{
    /* Defines the IO Type this buffer is associated with */
    DRV_USART_BUFFER_FLAGS flags;

    /* The buffer which needs to be read or written */
    char                *buffer;

    /* The size of the buffer which needs to be read or written */
    uint32_t                 bufferSize;

    /* The address which needs to be written */
    uint8_t                 address;

    DRV_USART_CALLBACK      xferCallback;

} DRV_USART_IO_BUFFER;

// *****************************************************************************
/* USART Driver Transfer Flags

  Summary
    Specifies the status of the receive or transmit

  Description
    This type specifies the status of the receive or transmit operation.

  Remarks:
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interrest must be
    AND'ed with value and checked to see if the result is non-zero.
*/

typedef enum
{
    /* Indicates that the core driver buffer is full */
    DRV_USART_TRANSFER_STATUS_RX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

    /* Indicates that at least one byte of Data has been received */
    DRV_USART_TRANSFER_STATUS_RX_DATA_PRESENT
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver receiver buffer is empty */
    DRV_USART_TRANSFER_STATUS_RX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is full */
    DRV_USART_TRANSFER_STATUS_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is empty */
    DRV_USART_TRANSFER_STATUS_TX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

} DRV_USART_TRANSFER_STATUS;


// *****************************************************************************
/* USART Buffer Status

   Summary
    Defines the buffer status

   Description
    Defines the states that an USART buffer can be in during its lifetime

   Remarks:
    As buffers may have a limited life span, so too have the associated handles
    and status info. Once a buffer transfer is completed (and possibly
    notified and acknowledged) it will be discarded. The status of a discarded
    buffer is no longer maintained by the driver.

*/

typedef enum
{
    /*Done OK and ready */
    DRV_USART_BUFFER_COMPLETED
        /*DOM-IGNORE-BEGIN*/ = 0  /*DOM-IGNORE-END*/,

    /*Scheduled but not started */
    DRV_USART_BUFFER_QUEUED
        /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /*Currently being in transfer */
    DRV_USART_BUFFER_IN_PROGRESS
        /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/,

    /*Unknown buffer */
    DRV_USART_BUFFER_ERROR_UNKNOWN
        /*DOM-IGNORE-BEGIN*/ = -1 /*DOM-IGNORE-END*/,

    /*Read data lost: rx process not fast enough */
    DRV_USART_BUFFER_ERROR_RX_OVERFLOW
        /*DOM-IGNORE-BEGIN*/ = -2  /*DOM-IGNORE-END*/

} DRV_USART_BUFFER_STATUS;


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Module Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
      SYS_MODULE_OBJ DRV_USART_Initialize( const SYS_MODULE_INDEX index,
                                           const SYS_MODULE_INIT * const init )

  Summary:
    Initializes the USART instance for the specified driver index

  Description:
    This routine initializes the USART driver instance for the specified driver 
    index, making it ready for clients to open and use it.

  Precondition:
    None.

  Input:
    index  - Identifier for the instance to be initialized
    
    init   - Pointer to a data structure containing any data necessary to
             initialize the drivver. This pointer may be null if no data is
             required because static overrides have been provided.

  Return:
    If successful, returns a valid handle to a driver instance object.  
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.

  Example:
    <code>
    DRV_USART_INIT              usartInitData;
    //Alternatively NULL can be passed to Initialize which then
    //makes sure that static overrides as selected by the user
    //will be used as default values
    SYS_MODULE_OBJ              objectHandle;

    usartInitData.moduleInit.value      = SYS_MODULE_POWER_RUN_FULL;
    usartInitData.moduleId              = USART_ID_2;
    usartInitData.operationMode         = DRV_USART_OPERATION_MODE_RS232;
    usartInitData.initFlags             = 0;
    usartInitData.lineControlMode       = DRV_USART_LINE_CONTROL_MODE_8NONE1;
    usartInitData.brgClock              = 4000000;
    usartInitData.brgValue              = 9600;
    usartInitData.operationModeInit     = 0;
    usartInitData.handShakeMode         = DRV_USART_HANDSHAKE_MODE_FLOWCONTROL;
    usartInitData.txInterruptSource     = INT_SOURCE_USART_2_TRANSMIT;
    usartInitData.rxInterruptSource     = INT_SOURCE_USART_2_RECEIVE;
    usartInitData.errorInterruptSource  = INT_SOURCE_USART_2_ERROR;
	usartInitData.txQueueSize			= 3;
	usartInitData.rxQueueSize			= 3;

    objectHandle = DRV_USART_Initialize(DRV_USART_INDEX_1, (SYS_MODULE_INIT*)usartInitData);
    if (SYS_MODULE_OBJ_INVALID == objectHandle)
    {
        // Handle error
    }
    </code>
  Remarks:
    This routine must be called before any other USART routine is called.

    This routine should only be called once during system initialization
    unless DRV_USART_Deinitialize is called to de-initialize the driver 
    instance.

    This routine will NEVER block for hardware access. If the operation requires
    time to allow the hardware to re-initialize, it will be reported by the 
    DRV_USART_Status operation. The system must use DRV_USART_Status to find out 
    when the driver is in the ready state.  
    
    Build configuration options may be used to staticaly override options in the 
    "init" sructure and will take precedance over initialization data passed 
    using this routine.
*/

SYS_MODULE_OBJ DRV_USART_Initialize( const SYS_MODULE_INDEX index,
                                     const SYS_MODULE_INIT * const init);


// *****************************************************************************
/* Function:
    void DRV_USART_Reinitialize( SYS_MODULE_OBJ object,
                                 const DRV_USART_INIT * const init )
  Summary:
    Reinitializes the USART driver and refreshes any associated hardware
    settings

  Description:
    This routine reinitializes the driver and refreshes any associated hardware
    settings using the initialization data given, but it will not interrupt any
    ongoing operations.

  Precondition:
    Function DRV_USART_Initialize must have been called before calling this
    routine and a valid SYS_MODULE_OBJ must have been returned.

  Parameters:
    object          - Driver object handle, returned from the 
                      DRV_USART_Initialize routine

    init            - Pointer to the initialization data structure

  Returns:
    None.

  Example:
    <code>
    DRV_USART_INIT  usartInitData;
    //Alternatively NULL can be passed to Initialize which then
    //makes sure that static overrides as selected by the user
    //will be used as default values

    SYS_STATUS      usartStatus;
    SYS_MODULE_OBJ  object;

    usartInitData.moduleInit.value      = SYS_MODULE_POWER_RUN_FULL;
    usartInitData.moduleId              = USART_ID_2;
    usartInitData.operationMode         = DRV_USART_OPERATION_MODE_RS232;
    usartInitData.initFlags             = 0;
    usartInitData.lineControlMode       = DRV_USART_LINE_CONTROL_MODE_8NONE1;
    usartInitData.brgClock              = 4000000;
    usartInitData.brgValue              = 9600;
    usartInitData.operationModeInit     = 0;
    usartInitData.handShakeMode         = DRV_USART_HANDSHAKE_MODE_FLOWCONTROL;
    usartInitData.txInterruptSource     = INT_SOURCE_USART_2_TRANSMIT;
    usartInitData.rxInterruptSource     = INT_SOURCE_USART_2_RECEIVE;
    usartInitData.errorInterruptSource  = INT_SOURCE_USART_2_ERROR;

    DRV_USART_Reinitialize(object, (SYS_MODULE_INIT*)usartInitData);
    
    usartStatus = DRV_USART_Status(object);
    if (SYS_STATUS_BUSY == usartStatus)
    {
        // Check again later to ensure the driver is ready
    }
    else if (SYS_STATUS_ERROR >= usartStatus)
    {
        // Handle error
    }
    </code>

  Remarks:
    This function can be called multiple times to reinitialize the module.
    
    This operation can be used to refresh any supported hardware registers as 
    specified by the initialization data or to change the power state of the 
    module.

    This routine will NEVER block for hardware access. If the operation requires
    time to allow the hardware to re-initialize, it will be reported by the 
    DRV_USART_Status operation. The system must use DRV_USART_Status to find out 
    when the driver is in the ready state.  
    
    Build configuration options may be used to staticaly override options in the 
    "init" sructure and will take precedance over initialization data passed 
    using this routine.
*/

void DRV_USART_Reinitialize( SYS_MODULE_OBJ object,  const SYS_MODULE_INIT * const init);


// *****************************************************************************
/* Function:
    void DRV_USART_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specified instance of the USART driver module

  Description:
    Deinitializes the specified instance of the USART driver module, disabling 
    its operation (and any hardware).  Invalidates all the internal data.

  Precondition:
    Function DRV_USART_Initialize should have been called before calling this
    function.

  Parameters:
    object          - Driver object handle, returned from the 
                      DRV_USART_Initialize routine

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     //  Returned from DRV_USART_Initialize
    SYS_STATUS          status;


    DRV_USART_Deinitialize(object);

    status = DRV_USART_Status(object);
    if (SYS_MODULE_DEINITIALIZED != status)
    {
        // Check again later if you need to know 
        // when the driver is deinitialized.
    }
    </code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize operation
    must be called before the Initialize operation can be called again.

    This routine will NEVER block waiting for hardware. If the operation 
    requires time to allow the hardware to complete, this will be reported by 
    the DRV_USART_Status operation.  The system has to use DRV_USART_Status to find 
    out when the module is in the ready state.
*/

void DRV_USART_Deinitialize( SYS_MODULE_OBJ object);


// *****************************************************************************
/* Function:
    SYS_STATUS DRV_USART_Status( SYS_MODULE_OBJ object )

  Summary:
    Gets the current status of the USART driver module.

  Description:
    This routine provides the current status of the USART driver module.

  Precondition:
    Function DRV_USART_Initialize should have been called before calling this
    function.

  Parameters:
    object          - Driver object handle, returned from the 
                      DRV_USART_Initialize routine

  Returns:
    SYS_STATUS_READY          - Indicates that the driver is busy with a 
                                previous system level operation and cannot start
                                another
                                
                                Note Any value greater than SYS_STATUS_READY is
                                also a normal running state in which the driver
                                is ready to accept new operations.
                                
    SYS_STATUS_BUSY           - Indicates that the driver is busy with a 
                                previous system level operation and cannot start
                                another
                                
    SYS_STATUS_ERROR          - Indicates that the driver is in an error state
                                
                                Note:  Any value less than SYS_STATUS_ERROR is 
                                also an error state.
    
    SYS_MODULE_DEINITIALIZED  - Indicates that the driver has been 
                                de-initialized
                                
                                Note:  This value is less than SYS_STATUS_ERROR

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_USART_Initialize
    SYS_STATUS          usartStatus;

    usartStatus = DRV_USART _Status(object);
    else if (SYS_STATUS_ERROR >= usartStatus)
    {
        // Handle error
    }
    </code>

  Remarks:
    The this operation can be used to determine when any of the driver's module 
    level operations has completed.
    
    If the status operation returns SYS_STATUS_BUSY, the a previous operation 
    has not yet completed.  Once the status operation returns SYS_STATUS_READY, 
    any previous operations have completed.

    The value of SYS_STATUS_ERROR is negative (-1).  Any value less than that is
    also an error state.

    This routine will NEVER block waiting for hardware.
    
    If the Status operation returns an error value, the error may be cleared by
    calling the reinitialize operation.  If that fails, the deinitialize
    operation will need to be called, followed by the initialize operation to
    return to normal operations.
*/

SYS_STATUS DRV_USART_Status( SYS_MODULE_OBJ object);


// *****************************************************************************
/* Function:
    void DRV_USART_TasksTX ( SYS_MODULE_OBJ object );

  Summary:
    Maintains the driver's tramsmitter state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal transmitter state 
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified 
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_USART_Initialize

    while (true)
    {
        DRV_USART_TasksTX (object);
        
        // Do other tasks
    }
    </code>

  Remarks:
    This routine is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the apropriate raw
    ISR.
    
    This routine may excute in an ISR context and will never block or access any
    resources that may cause it to block.
*/

void DRV_USART_TasksTX ( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    void DRV_USART_TasksRX ( SYS_MODULE_OBJ object )

  Summary:
    Maintains the driver's receiver state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal receiver state 
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified 
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_USART_Initialize

    while (true)
    {
        DRV_USART_TasksRX (object);
        
        // Do other tasks
    }
    </code>

  Remarks:
    This routine is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the apropriate raw
    ISR.
    
    This routine may excute in an ISR context and will never block or access any
    resources that may cause it to block.
*/

void DRV_USART_TasksRX ( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    void DRV_USART_TasksError ( SYS_MODULE_OBJ object )

  Summary:
    Maintains the driver's error-handling state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal error-handling state 
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified 
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_USART_Initialize

    while (true)
    {
        DRV_USART_TasksError (object);
        
        // Do other tasks
    }
    </code>

  Remarks:
    This routine is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the apropriate raw
    ISR.
    
    This routine may excute in an ISR context and will never block or access any
    resources that may cause it to block.
*/

void DRV_USART_TasksError ( SYS_MODULE_OBJ object );


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Client Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    DRV_HANDLE DRV_USART_Open( const SYS_MODULE_INDEX index,
                               const DRV_IO_INTENT    ioIntent )

  Summary:
    Opens the specified timer driver instance and returns a handle to it

  Description:
    This routine opens the specified USART driver instance and provides a
    handle that must be provided to all other client-level operations to
    identify the caller and the instance of the driver.

  Precondition:
    Function DRV_USART_Initialize must have been called before calling this
    function.

  Parameters:
    drvIndex    - Identifier for the object instance to be opened
    
    intent      - Zero or more of the values from the enumeration
                  DRV_IO_INTENT "or'd" together to indicate the intended use
                  of the driver

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance).
    
    If an error occurs, the return value is DRV_HANDLE_INVALID.

  Example:
    <code>
    DRV_HANDLE handle;

    handle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
    if (DRV_HANDLE_INVALID == handle)
    {
        // Unable to open the driver
    }
    </code>

  Remarks:
    The handle returned is valid until the DRV_USART_Close routine is called.

    This routine will NEVER block waiting for hardware.
    
    If the DRV_IO_INTENT_BLOCKING is requested and the driver was built 
    appropriately to support blocking behavior, then other client-level
    operations may block waiting on hardware until they are complete.

    If DRV_IO_INTENT_NON_BLOCKING is requested the driver client can call the
    DRV_USART_ClientStatus operation to find out when the module is in the ready 
    state.

    If the requested intent flags are not supported, the routine will return
    DRV_HANDLE_INVALID.
*/

DRV_HANDLE DRV_USART_Open( const SYS_MODULE_INDEX index, const DRV_IO_INTENT ioIntent);


// *****************************************************************************
/* Function:
    SYS_STATUS DRV_USART_Close( DRV_Handle handle )

  Summary:
    Closes an opened-instance of the USART driver

  Description:
    This routine closes an opened-instance of the USART driver, invalidating the
    handle.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None

  Example:
    <code>
    DRV_HANDLE handle;  // Returned from DRV_USART_Open

    DRV_USART_Close(handle);
    </code>

  Remarks:
    After calling this routine, the handle passed in "handle" must not be used 
    with any of the remaining driver routines.  A new handle must be obtained by 
    calling DRV_USART_Open before the caller may use the driver again.

    If DRV_IO_INTENT_BLOCKING was requested and the driver was built 
    appropriately to support blocking behavior call may block until the 
    operation is complete.

    If DRV_IO_INTENT_NON_BLOCKING request the driver client can call the
    DRV_USART_Status operation to find out when the module is in
    the ready state (the handle is no longer valid).

    Note:
    Usually there is no need for the driver client to verify that the Close 
    operation has completed.
*/

void DRV_USART_Close( const DRV_HANDLE handle);


// *****************************************************************************
/* Function:
    DRV_USART_CLIENT_STATUS DRV_USART_ClientStatus(DRV_HANDLE handle);

  Summary:
    Gets current client-specific status the USART driver

  Description:
    This routine gets the client-specfic status of the USART driver associated 
    with the given handle.

  Precondition:
    The DRV_USART_Initialize routine must have been called.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_USART_CLIENT_STATUS value describing the current status of the driver

  Example:
    <code>
    DRV_HANDLE                  handle;         // Returned from DRV_USART_Open
    DRV_USART_CLIENT_STATUS     clientStatus;
    
    clientStatus = DRV_USART_ClientStatus(handle);
    if(DRV_USART_CLIENT_STATUS_ERROR >= clientStatus)
    {
        // Handle the error
    }
    </code>

  Remarks:
    This routine will not block for hardware access and will immediately return 
    the current status.
*/

DRV_USART_CLIENT_STATUS DRV_USART_ClientStatus( const DRV_HANDLE handle );


// *****************************************************************************
/*
  Function:
    DRV_HANDLE DRV_USART_BufferAdd( const DRV_HANDLE handle,
        DRV_USART_IO_BUFFER *bufferObject) ;

  Summary:
    Starts the writes to the communication channel.

  Description:
    Starts the writes to the communication channel.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART device instance and the DRV_USART_Status must have returned
    SYS_STATUS_READY.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_READ or DRV_IO_INTENT_WRITE or DRV_IO_INTENT_READWRITE must
    have been specified in the DRV_USART_Open call.

  Parameters:
    handle       - Handle of the communication channel as return by the
                   DRV_USART_Open function.
    bufferObject - Buffer Object that needs to be specified for the buffer that
                   needs to be read or written.

  Returns:
     The buffer handle, which should be used to query how many bytes have been
     written or read using the function DRV_USART_OperationStatus

  Example:
    <code>
	
	void Callback(void);
    uint8_t mybuffer[MY_BUFFER_SIZE];
    int8_t bytesWritten = 0;
    DRV_BUFFER_HANDLE bufferHandle = NULL;
    DRV_USART_IO_BUFFER buffer1;
	void Callback(void)
	{
		Nop();
	}

	buffer1.buffer       = writeBuffer2;
	buffer1.bufferSize   = sizeof(writeBuffer2);
	buffer1.xferCallback = Callback;
	buffer1.flags        = DRV_USART_BUFFER_FLAG_WRITE;

    // myUSARTHandle is the handle returned by the DRV_USART_Open function.

    bufferHandle = DRV_USART_BufferAdd(myUSARThandle, &buffer1);

    while(bytesWritten < MY_BUFFER_SIZE)
    {
        bytesWritten = DRV_USART_BufferTransferStatus(handle, bufferHandle);
    }

    </code>

    </code>

  Remarks:
    If the DRV_IO_INTENT_BLOCKING is requested and the driver was built appropriately
    to support blocking behavior in an OS environment the call will block until
    the operation is complete.

    For DRV_IO_INTENT_NONBLOCKING request the driver client can call the
    DRV_USART_ClientStatus operation to find out when the module is in the ready
    state.

    In any circumstance, the client supplied buffer has to be non-volatile and
    it is not allowed to go out of scope until the operation completes.

    Affected by the following configuration options:
    - DRV_USART_CONFIG_SUPPORT_CLIENT_ACCESS_BLOCKING
    - DRV_USART_CONFIG_BUFFER_QUEUE_SLOTS_MAX
    - DRV_USART_CONFIG_SUPPORT_BUFFERQ

*/

DRV_HANDLE DRV_USART_BufferAdd( const DRV_HANDLE handle, DRV_USART_IO_BUFFER *bufferObject) ;


// *****************************************************************************
/*
  Function:
    DRV_USART_BUFFER_STATUS DRV_USART_BufferStatus( DRV_HANDLE handle, 
                                const DRV_HANDLE bufferHandle );

  Summary:
    Provides the status of the given buffer

  Description:
    This function provides the current status of the buffer identified by the 
    given buffer handle.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART device instance and the DRV_USART_Status must have returned
    SYS_STATUS_READY.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_READ or DRV_IO_INTENT_WRITE or DRV_IO_INTENT_READWRITE must
    have been specified in the DRV_USART_Open call.
    
    The "bufferHandle parameter must be the return value from a call to the 
    "DRV_USART_BufferAdd" function.

  Parameters:
    handle       - Handle of the communication channel as return by the
                   DRV_USART_Open function.
                   
    bufferHandle - Handle to the buffer in question.  Must be the return value
                   from a call to the "DRV_USART_BufferAdd" function.

  Returns:
     The current status of the given buffer.
     
  Example:
    <code>
    DRV_USART_BUFFER_STATUS bufferStatus;
    
    bufferStatus = DRV_USART_BufferStatus ( uartHandle, uartBufferHandle );
    if ( DRV_USART_BUFFER_COMPLETED == bufferStatus )
    {
        // Handle Buffer Complete
    }else
    {
        // Handle other
    }
    </code>

  Remarks:
    See the definition of "DRV_USART_BUFFER_STATUS" for a complete description
    of all possible status values.
*/

DRV_USART_BUFFER_STATUS DRV_USART_BufferStatus( DRV_HANDLE handle, const DRV_HANDLE bufferHandle );


// *****************************************************************************
/* Function:
    int DRV_USART_Read( const DRV_HANDLE handle,  uint8_t *buffer,
                        const unsigned int numbytes )

  Summary:
    Reads data from the USART

  Description:
    This routine reads data from the USART.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_READ or DRV_IO_INTENT_READWRITE must have been specified in
    the DRV_USART_Open call.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
                   
    buffer       - Buffer into which the data read from the USART instance
                   will be placed.
                   
    numbytes     - Total number of bytes that need to be read from the module
                   instance (must be equal to or less than the size of the 
                   buffer)

  Returns:
    Number of bytes actually copied into the caller's buffer or -1 if there
    is an error (call DRV_USART_ClientStatus to identify the error).

  Example:
    <code>
    DRV_HANDLE      handle;    // Returned from DRV_USART_Open
    char            myBuffer[MY_BUFFER_SIZE];
    unsigned int    count;
    unsigned int    total;

    total = 0;
    do
    {
        count  = DRV_USART_Read(myUSARTHandle, &myBuffer[total], MY_BUFFER_SIZE - total);
        total += count;

        // Do something else...

    } while( total < MY_BUFFER_SIZE );
    </code>

  Remarks:
    If the DRV_IO_INTENT_BLOCKING flag was given in the call to the 
    DRV_USART_Open routine and the driver was built to support blocking behavior
    the call will block until the operation is complete.

    If the DRV_IO_INTENT_NONBLOCKING flag was given in the call to the 
    DRV_USART_Open routine or the driver was built to only support non-blocking 
    behavior the call will return immediately, identifying how many bytes of
    data were actually copied into the client's buffer and the client must call
    DRV_USART_Read again with adjusted parameters as shown in the example.
*/

int DRV_USART_Read( const DRV_HANDLE handle, uint8_t *buffer,  const unsigned int numbytes);


// *****************************************************************************
/* Function:
    bool DRV_USART_ReadByte( const DRV_HANDLE handle, char *byte)

  Summary:
    Reads a byte of data from the USART
    
  Description:
    This routine reads a byte of data from the USART.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_READ or DRV_IO_INTENT_READWRITE must have been specified in
    the DRV_USART_Open call.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
				   
	byte		 - A variable in which data is read into			   

  Returns:
    true		 - Read successful
	false		 - Read failed

  Example:
    <code>
    DRV_HANDLE      handle;    // Returned from DRV_USART_Open
	bool			status;
	char			byte;

	bool = DRV_USART_ReadByte(handle, &byte);

        // Do something else...

    </code>

  Remarks:
    If the DRV_IO_INTENT_BLOCKING flag was given in the call to the 
    DRV_USART_Open routine and the driver was built to support blocking behavior
    the call will block until the operation is complete.

    If the DRV_IO_INTENT_NONBLOCKING flag was given in the call to the 
    DRV_USART_Open routine or the driver was built to only support non-blocking 
    behavior the call will return immediately.  If data is not available, a zero
    (0) value will be returned and an underrun error status will be captured.  
    To ensure that valid data is returned, the caller must first check the 
    return value to DRV_USART_TransferStatus as shown in the example.
*/

bool DRV_USART_ReadByte( const DRV_HANDLE handle, char *byte);


// *****************************************************************************
/* Function:
    bool DRV_USART_Write( const DRV_HANDLE   handle,  
                                  const uint8_t *    buffer,  
                                  const unsigned int numbytes);

  Summary:
    Writes data to the USART

  Description:
    This routine writes data to the USART.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_WRITE or DRV_IO_INTENT_READWRITE must have been specified in
    the DRV_USART_Open call.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
                   
    buffer       - Buffer containing the data write to the USART instance
                   
    numbytes     - Total number of bytes that to write to the USART instance 
                   (must be equal to or less than the size of the buffer)

  Returns:
    Number of bytes actually written to the USART or -1 if there is an error 
    (call DRV_USART_ClientStatus to identify the error)

  Example:
    <code>
    DRV_HANDLE      handle;    // Returned from DRV_USART_Open
    char            myBuffer[MY_BUFFER_SIZE];
    unsigned int    count;
    unsigned int    total;

    total = 0;
    do
    {
        count  = DRV_USART_Write(myUSARTHandle, &myBuffer[total], MY_BUFFER_SIZE - total);
        total += count;

        // Do something else...

    } while( total < MY_BUFFER_SIZE );
    </code>

  Remarks:
    If the DRV_IO_INTENT_BLOCKING flag was given in the call to the 
    DRV_USART_Open routine and the driver was built to support blocking behavior
    the call will block until the operation is complete.

    If the DRV_IO_INTENT_NONBLOCKING flag was given in the call to the 
    DRV_USART_Open routine or the driver was built to only support non-blocking 
    behavior the call will return immediately, identifying how many bytes of
    data were actually written to the USART and the client must call 
    DRV_USART_Write again with adjusted parameters as shown in the example.
*/

bool DRV_USART_Write( const DRV_HANDLE handle,  const uint8_t *buffer,  const uint32_t numbytes );


// *****************************************************************************
/* Function:
    bool DRV_USART_WriteByte( const DRV_HANDLE handle,  const uint8_t byte)

  Summary:
    Writes a byte of data to the USART
    
  Description:
    This routine writes a byte of data to the USART.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_WRITE or DRV_IO_INTENT_READWRITE must have been specified in
    the DRV_USART_Open call.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    byte         - Data byte to write to the USART

  Returns:
    true		  - Write successful.
	false		  - Write failed.

  Example:
    <code>
    DRV_HANDLE      handle;    // Returned from DRV_USART_Open
    
    bool    		status;
    
    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

         status =   DRV_USART_WriteByte(handle, myBuffer[numBytes++]);

        // Do something else...
    }
    </code>

  Remarks:
    If the DRV_IO_INTENT_BLOCKING flag was given in the call to the 
    DRV_USART_Open routine and the driver was built to support blocking behavior
    the call will block until the operation is complete.

    If the DRV_IO_INTENT_NONBLOCKING flag was given in the call to the 
    DRV_USART_Open routine or the driver was built to only support non-blocking 
    behavior the call will return immediately.  If the driver was not able to 
    accept the data, an overrun error status will be captured.  To ensure that 
    the driver is ready to accept data, the caller must first check the 
    return value to DRV_USART_TransferStatus as shown in the example.
*/

bool DRV_USART_WriteByte( const DRV_HANDLE handle,  const uint8_t byte);


// *****************************************************************************
/* Function:
    DRV_USART_TRANSFER_STATUS DRV_USART_TransferStatus (const DRV_HANDLE handle)

  Summary:
    Returns the transmitter and receiver transfer status

  Description:
    This returns the transmitter and receiver transfer status.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

    DRV_USART_Open must have been called to obtain a valid opened device handle.


  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_USART_TRANSFER_STATUS value describing the current status of the
    transfer.

  Example:
    <code>
    DRV_HANDLE handle;    // Returned from DRV_USART_Open

    if (DRV_USART_TRANSFER_STATUS_TX_EMPTY & DRV_USART_TransferStatus(handle) )
    {
        // All transmitter data has been sent.
    }
    </code>

  Remarks:
    The returned status may contain a value with more than one of the bits
    specified in the DRV_USART_TRANSFER_STATUS enumeration set.  The caller
    should perform an "AND" with the bit of interest and verify if the 
    result is non-zero (as shown in the example) to verify the desired status
    bit.
*/

DRV_USART_TRANSFER_STATUS DRV_USART_TransferStatus (const DRV_HANDLE handle );

// *****************************************************************************
/*
  Function:
    int8_t DRV_USART_BufferTransferStatus(  const DRV_HANDLE handle,
        const DRV_USART_BUFFER_HANDLE *bufferHandle);

  Summary:
    Gets the number of bytes which are written or read

  Description:
    Gets the number of bytes which are written or read for the transaction
    handle

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART device instance and the DRV_USART_Status must have returned
    SYS_STATUS_READY.

    DRV_USART_Open must have been called to obtain a valid opened device handle.

    The function DRV_USART_BufferAdd should be called before calling
    this function and should have returned a valid buffer handle.

  Parameters:
    handle       - Handle of the communication channel as return by the
                   DRV_USART_Open function.
    bufferHandle - Handle of the buffer returned by the DRV_USART_BufferAdd

  Returns:
    The number of bytes read if the buffer id is DRV_IO_BUFFER_READ or number
    of bytes written when the buffer id is DRV_IO_BUFFER_WRITE. If -1 is returned


  Example:
    <code>
	
	void Callback(void);
    uint8_t mybuffer[MY_BUFFER_SIZE];
    int8_t bytesWritten = 0;
    DRV_BUFFER_HANDLE bufferHandle = NULL;
    DRV_USART_IO_BUFFER buffer1;
	void Callback(void)
	{
		Nop();
	}

	buffer1.buffer       = writeBuffer2;
	buffer1.bufferSize   = sizeof(writeBuffer2);
	buffer1.xferCallback = Callback;
	buffer1.flags        = DRV_USART_BUFFER_FLAG_WRITE;

    // myUSARTHandle is the handle returned by the DRV_USART_Open function.

    bufferHandle = DRV_USART_BufferAdd(myUSARThandle, &buffer1);

    while(bytesWritten < MY_BUFFER_SIZE)
    {
        bytesWritten = DRV_USART_BufferTransferStatus(handle, bufferHandle);
    }

    </code>

  Remarks:
    None.
*/

int8_t DRV_USART_BufferTransferStatus(  const DRV_HANDLE handle, const DRV_HANDLE bufferHandle);



// ****************************************************************************
// ****************************************************************************
// Section: Included Files (continued)
// ****************************************************************************
// ****************************************************************************
/*  The files included below map the interface definitions above to appropriate
    static implementations, depending on build mode.
*/

#include "driver/usart/drv_usart_mapping.h"


#endif // #ifndef _DRV_USART_H
/*******************************************************************************
 End of File
*/

