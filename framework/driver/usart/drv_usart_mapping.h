/*******************************************************************************
  USART Device Driver interface names mapping

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_mapping.h

  Summary:
    USART Device Driver Interface names mapping

  Description:
    This header file contains the data type definitions.
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
#ifndef _DRV_USART_MAPPING_H
#define _DRV_USART_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>

#include "system_config.h"
#include "driver/usart/drv_usart_static_single.h"
#include "driver/usart/drv_usart_static_multi.h"
#include "peripheral/usart/plib_usart.h"


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Static API Name Generation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_USART_MAKE_NAME(name)

  Summary:
    Creates an instance-specific static interface name

  Description:
     This macro creates the instance-specific name of the given static interface
     routine by inserting the index number into the name.

     Example DRV_USART_Initialize becomes DRV_USART1_Initialize for an index of 1.

  Remarks:
    Multi-client configurations add the word "multi" to the API name, single-
    client configurations do not.

    Example DRV_USART_Initialize becomes DRV_USART1multi_Initialize for an index
    of 1.
*/

#if !defined(DRV_USART_INSTANCES_NUMBER)

    #if !defined(DRV_USART_CLIENTS_NUMBER)

        // Static Single-Client Interface Name Generation
        #define _DRV_USART_STATIC_API_A(index, name)    DRV_USART ## index ## _ ## name

    #else

        // Static multi-client interface name generation
        #define _DRV_USART_STATIC_API_A(index , name)   DRV_USART ## index ## multi_ ## name

    #endif

    // Static Naming Macros
    #define _DRV_USART_STATIC_API(index , name)     _DRV_USART_STATIC_API_A(index , name)
    #define _DRV_USART_MAKE_NAME(name)              _DRV_USART_STATIC_API(DRV_USART_INDEX, name)

#else // dynamic build

        // Dynamic Interface Name Generation
        #define _DRV_USART_MAKE_NAME(name)  DRV_USART_ ## name

#endif


// *****************************************************************************
// *****************************************************************************
// Section: ADC Driver Static API Mapping
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Static Interface Mapping

  Summary:
    Maps the dynamic interface calls to appropriate static interface

  Description:
    These macros map calls to the dynamic interface routines to calls to the
    appropriate instance-specific static interface routine when a static build
    (DRV_USART_INSTANCES_NUMBER is not defined) is configured.

    Example:

        DRV_USART_Status(DRV_USART_CONFIG_INDEX_1);

    Becomes:

        DRV_USART_Status();

  Remarks:
    Static configuration eliminate the need to pass the object parameter.
    However, the index is "returned" as the object handle (from the
    "Initialize" routine) to allow code written for the dynamic API to continue
    to build when using a static configuration.

    Example:

        object = DRV_USART_Initialize(DRV_USART_CONFIG_INDEX_1, &initData);

    Becomes:

        object = ( DRV_USART1_Initialize(&initData), DRV_USART_CONFIG_INDEX);

    Static single-client configurations also eliminate the client handle
    parameter.  However, the index (the driver-object index) is "returned" from
    the "Open" routine to allow code written for multi-client drivers to build
    when using a static single-open configuration.

    Example:

        handle = DRV_USART_Open(DRV_USART_CONFIG_INDEX_1, intent);

    Becomes:

        handle = ( DRV_USART_Open(intent), DRV_USART_CONFIG_INDEX);
*/

#if !defined(DRV_USART_INSTANCES_NUMBER) // Static Configuration

    #if !defined(DRV_USART_CLIENTS_NUMBER)    // Single-Client

        #define DRV_USART_Initialize(sysID,init)   (_DRV_USART_MAKE_NAME(Initialize)(init),DRV_USART_CONFIG_INDEX)

        #define DRV_USART_Reinitialize(sysObj,init) _DRV_USART_MAKE_NAME(Reinitialize)(init)

        #define DRV_USART_Deinitialize(sysObj)      _DRV_USART_MAKE_NAME(Deinitialize)()

        #define DRV_USART_Status(sysObj)            _DRV_USART_MAKE_NAME(Status)()

        #define DRV_USART_TasksTX(sysObj)           _DRV_USART_MAKE_NAME(TasksTX)()

        #define DRV_USART_TasksRX(sysObj)           _DRV_USART_MAKE_NAME(TasksRX)()

        #define DRV_USART_TasksError(sysObj)        _DRV_USART_MAKE_NAME(TasksError)()

        #define DRV_USART_Open(sysID,intent)       (_DRV_USART_MAKE_NAME(Open)(intent), DRV_USART_CONFIG_INDEX)

        #define DRV_USART_Close(handle)             _DRV_USART_MAKE_NAME(Close)()

        #define DRV_USART_ClientStatus(handle)      _DRV_USART_MAKE_NAME(ClientStatus)()

        #define DRV_USART_Read(handle,b,n)          _DRV_USART_MAKE_NAME(Read)(b,n)

        #define DRV_USART_ReadByte(c)               _DRV_USART_MAKE_NAME(ReadByte)(c)

        #define DRV_USART_Write(handle,b,n)         _DRV_USART_MAKE_NAME(Write)(b,n)

        #define DRV_USART_WriteByte(handle,b)       _DRV_USART_MAKE_NAME(WriteByte)(b)

        #define DRV_USART_TransferStatus(handle)    _DRV_USART_MAKE_NAME(TransferStatus)()

        #define DRV_USART_BufferTransferStatus(handle, bhandle) _DRV_USART_MAKE_NAME(BufferTransferStatus)(handle,bhandle)

        #define DRV_USART_BufferAdd(handle, bobject) _DRV_USART_MAKE_NAME(BufferAdd)(bobject)

        #define DRV_USART_BufferStatus(handle1, handle2)    _DRV_USART_MAKE_NAME(BufferStatus)(handle2)

    #else // multi-Client, (DRV_USART_CLIENTS_NUMBER >= 1)

        #define DRV_USART_Initialize(sysID,init)   (_DRV_USART_MAKE_NAME(Initialize)(init),DRV_USART_CONFIG_INDEX)

        #define DRV_USART_Reinitialize(sysObj,init) _DRV_USART_MAKE_NAME(Reinitialize)(init)

        #define DRV_USART_Deinitialize(sysObj)      _DRV_USART_MAKE_NAME(Deinitialize)()

        #define DRV_USART_Status(sysObj)            _DRV_USART_MAKE_NAME(Status)()

        #define DRV_USART_TasksTX(sysObj)           _DRV_USART_MAKE_NAME(TasksTX)()

        #define DRV_USART_TasksRX(sysObj)           _DRV_USART_MAKE_NAME(TasksRX)()

        #define DRV_USART_TasksError(sysObj)        _DRV_USART_MAKE_NAME(TasksError)()

        #define DRV_USART_Open(sysID,intent)        _DRV_USART_MAKE_NAME(Open)(intent)

        #define DRV_USART_Close(handle)             _DRV_USART_MAKE_NAME(Close)(handle)

        #define DRV_USART_ClientStatus(handle)      _DRV_USART_MAKE_NAME(ClientStatus)(handle)

        #define DRV_USART_Read(handle,b,n)          _DRV_USART_MAKE_NAME(Read)(handle,b,n)

        #define DRV_USART_ReadByte(handle)          _DRV_USART_MAKE_NAME(ReadByte)(handle)

        #define DRV_USART_Write(handle,b,n)         _DRV_USART_MAKE_NAME(Write)(handle,b,n)

        #define DRV_USART_WriteByte(handle,b)       _DRV_USART_MAKE_NAME(WriteByte)(handle,b)

        #define DRV_USART_TransferStatus(handle)    _DRV_USART_MAKE_NAME(TransferStatus)(handle)

        #define DRV_USART_BufferTransferStatus(handle, bhandle) _DRV_USART_MAKE_NAME(BufferTransferStatus)(handle, bhandle)

        #define DRV_USART_BufferAdd(handle, bobject) _DRV_USART_MAKE_NAME(BufferAdd)(handle, bobject)

        #define DRV_USART_BufferStatus(handle, bhandle)    _DRV_USART_MAKE_NAME(BufferStatus)(handle, bhandle)

    #endif

#endif


#endif // #ifndef _DRV_USART_MAPPING_H

/*******************************************************************************
 End of File
*/

