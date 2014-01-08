/*******************************************************************************
  USART Driver Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_local.h

  Summary:
    USART Driver Local Data Structures

  Description:
    Driver Local Data Structures
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
#ifndef _DRV_USART_LOCAL_H
#define _DRV_USART_LOCAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


#include "system/clk/sys_clk.h"
#include "driver/usart/drv_usart.h"
#include "driver/usart/src/drv_usart_variant_mapping.h"
#include "osal/osal.h"
#include "system/int/sys_int.h"


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Static Object Generation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_USART_OBJ_MAKE_NAME(name)

  Summary:
    Creates an instance-specific static object name

  Description:
     This macro creates the instance-specific name of the given static object
     by inserting the index number into the name.

  Remarks:
    This macro does not affect the dynamic objects
*/

#define _DRV_STATIC_OBJ_NAME_B(name,id) name ## id

#define _DRV_STATIC_OBJ_NAME_A(name,id) _DRV_STATIC_OBJ_NAME_B(name,id)

#define _DRV_USART_OBJ_MAKE_NAME(name)  _DRV_STATIC_OBJ_NAME_A(name, DRV_USART_INDEX)


// *****************************************************************************
// *****************************************************************************
// Section: Data Type Definitions
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* USART Operational Flags

  Summary:
    Defines the various flags which needed for the USART driver operation.

  Description:
    Defines the various flags which needed for the USART driver operation.

  Remarks:
    None
*/

typedef enum
{

    /* Object is in use */
    DRV_USART_OPERATIONAL_FLAG_IN_USE           = 0x1,

    /* Loopback mode is enabled */
    DRV_USART_OPERATIONAL_FLAG_LOOPBACK         = 0x2,

    /* Exclusive access is enabled for the hardware */
    DRV_USART_OPERATIONAL_FLAG_EXCLUSIVE_ACCESS = 0x4,

    /* Buffer Object related handle is closed */
    DRV_USART_OPERATIONAL_FLAG_HANDLE_CLOSED    = 0x8

} DRV_USART_OPERATIONAL_FLAGS ;

typedef struct
{
	bool                            inUse;
	char                            *dataPointer;
	uint32_t                        size;
	uint32_t                        nbytes;
	DRV_USART_CALLBACK		eventCallback;
	DRV_USART_BUFFER_STATUS         status;
}DRV_USART_XFER_OBJECT;


typedef struct
{
	DRV_USART_XFER_OBJECT				*queueStart;
	uint8_t						queueSize;
	uint8_t                                         currentPointer;
}DRV_USART_QUEUE_OBJECT;

typedef enum
{
	DRV_USART_BYTE_PENDING,
	DRV_USART_BYTE_IS_READY,
	DRV_USART_BYTE_DATA_AVAILABLE,
	DRV_USART_BYTE_IDLE
}DRV_USART_BYTE_TRANSFER_STATUS;

// *****************************************************************************
/* USART Driver Hardware Instance Object

  Summary:
    Defines the object required for the maintainence of the hardware instance.

  Description:
    This defines the object required for the maintainence of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None
*/

typedef struct
{
    /* The module index associated with the object*/
    USART_MODULE_ID                             moduleId;

    /* The buffer Q for the write operations */
    DRV_USART_QUEUE_OBJECT                      writeQ;

    /* The buffer Q for the read operations */
    DRV_USART_QUEUE_OBJECT                      readQ;

    /* The status of the driver */
    SYS_STATUS                                  status;

    /* Required : Flag to indicate in use  */
    bool                                        inUse;

    /* Flag to indicate that SAMPLE is used in exclusive access mode */
    bool                                        isExclusive;

    /* number of clients connected to the hardware instance */
    uint8_t                                     numClients;

    /* number of clients connected to the hardware instance */
    uint8_t                                     receivedByte;

    /* Interrupt Source for TX Interrupt */
    INT_SOURCE                  		txInterruptSource;

    /* Interrupt Source for TX Interrupt */
    INT_SOURCE                  		rxInterruptSource;

    /* Interrupt Source for TX Interrupt */
    INT_SOURCE                  		errorInterruptSource;

    DRV_USART_OPERATIONAL_FLAGS                 operationalFlags;

    uint8_t					txStatus;

    uint8_t					rxStatus;

    DRV_USART_BYTE_TRANSFER_STATUS              byteTxStatus;

    DRV_USART_BYTE_TRANSFER_STATUS              byteRxStatus;

    OSAL_MUTEX_DECLARE(mutexUSART_clientHandle);

    OSAL_MUTEX_DECLARE(mutexUSART_txBufferTransfer);

    OSAL_MUTEX_DECLARE(mutexUSART_rxBufferTransfer);

    OSAL_MUTEX_DECLARE(mutexUSART_txByteTransfer);

    OSAL_MUTEX_DECLARE(mutexUSART_rxByteTransfer);


}DRV_USART_OBJECT;


// *****************************************************************************
/* USART Driver Client Object

  Summary:
    Defines the object required for the maintainence of the software clients

  Description:
    This defines the object required for the maintainence of the software
    clients instance. This object exists once per client instance.

  Remarks:
    None
*/

typedef struct
{
    /* The hardware instance object associate with the client */
    void                                *driverObj;

    /* Flag to indicate that the client object is in use */
    DRV_USART_OPERATIONAL_FLAGS         operationalFlags;

    /* Status of the client object */
    SYS_STATUS                          status;

    /* The intent with which the client was opened */
    DRV_IO_INTENT                       intent;

    bool                                inUse;
}DRV_USART_CLIENT_OBJECT;


// *****************************************************************************
// *****************************************************************************
// Section: Extern data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*  Hardware Objects for the dynamic driver
*/

bool _DRV_USART_QueueAllocate(DRV_USART_QUEUE_OBJECT *, uint32_t );

DRV_USART_XFER_OBJECT * _DRV_USART_XferObjectAllocate(  DRV_USART_IO_BUFFER *, DRV_USART_QUEUE_OBJECT *);

extern DRV_USART_XFER_OBJECT        gDrvUSARTXferQObj[];

extern DRV_USART_OBJECT             gDrvUSARTObj[];

// *****************************************************************************
/*  Client Objects for the multi-client driver
*/

extern DRV_USART_CLIENT_OBJECT      gDrvUSARTClientObj[];

// *****************************************************************************
/*  Hardware Objects for the static driver
*/

extern DRV_USART_OBJECT  gDrvUSARTObj0;
extern DRV_USART_OBJECT  gDrvUSARTObj1;
extern DRV_USART_OBJECT  gDrvUSARTObj2;
extern DRV_USART_OBJECT  gDrvUSARTObj3;
extern DRV_USART_OBJECT  gDrvUSARTObj4;
extern DRV_USART_OBJECT  gDrvUSARTObj5;
extern DRV_USART_OBJECT  gDrvUSARTObj6;

// *****************************************************************************
/*  Client Objects for the single-client driver
*/

extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj0;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj1;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj2;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj3;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj4;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj5;
extern DRV_USART_CLIENT_OBJECT   gDrvUSARTClientObj6;


#endif //#ifndef _DRV_USART_PRIVATE_H

/*******************************************************************************
 End of File
*/

