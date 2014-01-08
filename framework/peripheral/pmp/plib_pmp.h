/***********************************************************************
  Company:
    Microchip Technology Inc.
    
  File Name:
    plib_pmp.h
    
  Summary:
    Parallel Master Port (PMP) Peripheral Library Interface Header.
    
  Description:    
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the PMP
    Peripheral Library.
  ***********************************************************************/

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

#ifndef _PLIB_PMP_H
#define _PLIB_PMP_H


// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************

#include "peripheral/pmp/processor/pmp_processor.h"

// *****************************************************************************
// *****************************************************************************
// Section: PMP Peripheral Library Exists Routines
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function :  PLIB_PMP_ExistsEnableControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the EnableControl feature exists on the PMP module. 

  Description:
    This interface identifies that the EnableControl feature is available on 
    the PMP module. When this interface returns true, these functions are 
    supported on the device: 
    - PLIB_PMP_Disable
    - PLIB_PMP_Enable
    - PLIB_PMP_IsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The EnableControl feature is supported on the device
    - false  - The EnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsEnableControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsStopInIdleControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the StopInIdleControl feature exists on the PMP module. 

  Description:
    This interface identifies that the StopInIdleControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_StopInIdleEnable
    - PLIB_PMP_StopInIdleDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The StopInIdleControl feature is supported on the device
    - false  - The StopInIdleControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsStopInIdleControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsMUXModeSelect( PMP_MODULE_ID index )

  Summary:
    Identifies that the MUXModeSelect feature exists on the PMP module. 

  Description:
    This interface identifies that the MUXModeSelect feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_MultiplexModeSelect
    - PLIB_PMP_MultiplexModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MUXModeSelect feature is supported on the device
    - false  - The MUXModeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsMUXModeSelect( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsByteEnablePortControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the ByteEnablePortControl feature exists on the PMP module. 

  Description:
    This interface identifies that the ByteEnablePortControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_ByteEnablePortEnable
    - PLIB_PMP_ByteEnablePortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ByteEnablePortControl feature is supported on the device
    - false  - The ByteEnablePortControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsByteEnablePortControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsWriteEnablePortControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the WriteEnablePortControl feature exists on the PMP module. 

  Description:
    This interface identifies that the WriteEnablePortControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_WriteEnableStrobePortEnable
    - PLIB_PMP_WriteEnableStrobePortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WriteEnablePortControl feature is supported on the device
    - false  - The WriteEnablePortControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsWriteEnablePortControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsReadWriteStrobePortControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the ReadWriteStrobePortControl feature exists on the PMP module. 

  Description:
    This interface identifies that the ReadWriteStrobePortControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_ReadWriteStrobePortEnable
    - PLIB_PMP_ReadWriteStrobePortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadWriteStrobePortControl feature is supported on the device
    - false  - The ReadWriteStrobePortControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsReadWriteStrobePortControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipSelectoperation( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipSelectoperation feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipSelectoperation feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectFunctionSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipSelectoperation feature is supported on the device
    - false  - The ChipSelectoperation feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipSelectoperation( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsAddressLatchPolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the AddressLatchPolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the AddressLatchPolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_AddressLatchPolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressLatchPolarity feature is supported on the device
    - false  - The AddressLatchPolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsAddressLatchPolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXPolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXPolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXPolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXPolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXPolarity feature is supported on the device
    - false  - The ChipXPolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXPolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsByteEnablePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ByteEnablePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ByteEnablePolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ByteEnablePolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ByteEnablePolarity feature is supported on the device
    - false  - The ByteEnablePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsByteEnablePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXByteEnablePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXByteEnablePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXByteEnablePolarity feature is available 
    on the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXByteEnablePortPolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXByteEnablePolarity feature is supported on the device
    - false  - The ChipXByteEnablePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXByteEnablePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsWriteEnablePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the WriteEnablePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the WriteEnablePolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_WriteEnableStrobePolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WriteEnablePolarity feature is supported on the device
    - false  - The WriteEnablePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsWriteEnablePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXWriteEnablePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXWriteEnablePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXWriteEnablePolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXWriteEnableStrobePolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXWriteEnablePolarity feature is supported on the device
    - false  - The ChipXWriteEnablePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXWriteEnablePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsReadWritePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ReadWritePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ReadWritePolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ReadWriteStrobePolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadWritePolarity feature is supported on the device
    - false  - The ReadWritePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsReadWritePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXReadWritePolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXReadWritePolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXReadWritePolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXReadWriteStrobePolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXReadWritePolarity feature is supported on the device
    - false  - The ChipXReadWritePolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXReadWritePolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBusyStatus( PMP_MODULE_ID index )

  Summary:
    Identifies that the BusyStatus feature exists on the PMP module. 

  Description:
    This interface identifies that the BusyStatus feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_PortIsBusy

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BusyStatus feature is supported on the device
    - false  - The BusyStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBusyStatus( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsInterruptMode( PMP_MODULE_ID index )

  Summary:
    Identifies that the InterruptMode feature exists on the PMP module. 

  Description:
    This interface identifies that the InterruptMode feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_InterruptModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InterruptMode feature is supported on the device
    - false  - The InterruptMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsInterruptMode( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsIncrementMode( PMP_MODULE_ID index )

  Summary:
    Identifies that the IncrementMode feature exists on the PMP module. 

  Description:
    This interface identifies that the IncrementMode feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_AddressIncrementModeSelect
    - PLIB_PMP_AddressIncrementModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The IncrementMode feature is supported on the device
    - false  - The IncrementMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsIncrementMode( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsDataTransferSize( PMP_MODULE_ID index )

  Summary:
    Identifies that the DataTransferSize feature exists on the PMP module. 

  Description:
    This interface identifies that the DataTransferSize feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_DataSizeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataTransferSize feature is supported on the device
    - false  - The DataTransferSize feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsDataTransferSize( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsOperationMode( PMP_MODULE_ID index )

  Summary:
    Identifies that the OperationMode feature exists on the PMP module. 

  Description:
    This interface identifies that the OperationMode feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_OperationModeSelect
    - PLIB_PMP_OperationModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The OperationMode feature is supported on the device
    - false  - The OperationMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsOperationMode( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsDataSetUpWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the DataSetUpWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the DataSetUpWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_WaitStatesDataSetUpSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataSetUpWaitStates feature is supported on the device
    - false  - The DataSetUpWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsDataSetUpWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsDataStrobeWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the DataStrobeWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the DataStrobeWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_WaitStatesStrobeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataStrobeWaitStates feature is supported on the device
    - false  - The DataStrobeWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsDataStrobeWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsDataHoldWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the DataHoldWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the DataHoldWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_WaitStatesDataHoldSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataHoldWaitStates feature is supported on the device
    - false  - The DataHoldWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsDataHoldWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipSelectEnable( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipSelectEnable feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipSelectEnable feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_ChipSelectXEnable
    - PLIB_PMP_ChipSelectXDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipSelectEnable feature is supported on the device
    - false  - The ChipSelectEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipSelectEnable( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsAddressControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the AddressControl feature exists on the PMP module. 

  Description:
    This interface identifies that the AddressControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_AddressSet
    - PLIB_PMP_AddressLinesA0A1Set
    - PLIB_PMP_AddressLinesA0A1Get

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressControl feature is supported on the device
    - false  - The AddressControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsAddressControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsAddressPortPinControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the AddressPortPinControl feature exists on the PMP module. 

  Description:
    This interface identifies that the AddressPortPinControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_AddressPortEnable
    - PLIB_PMP_AddressPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressPortPinControl feature is supported on the device
    - false  - The AddressPortPinControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsAddressPortPinControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsAddressLatchStrobePortControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the AddressLatchStrobePortControl feature exists on the PMP module. 

  Description:
    This interface identifies that the AddressLatchStrobePortControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_AddressLatchStrobeEnable
    - PLIB_PMP_AddressLatchStrobeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressLatchStrobePortControl feature is supported on the device
    - false  - The AddressLatchStrobePortControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsAddressLatchStrobePortControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsInputBufferFull( PMP_MODULE_ID index )

  Summary:
    Identifies that the InputBufferFull feature exists on the PMP module. 

  Description:
    This interface identifies that the InputBufferFull feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_InputBuffersAreFull

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InputBufferFull feature is supported on the device
    - false  - The InputBufferFull feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsInputBufferFull( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBufferOverFlow( PMP_MODULE_ID index )

  Summary:
    Identifies that the BufferOverFlow feature exists on the PMP module. 

  Description:
    This interface identifies that the BufferOverFlow feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_InputOverflowHasOccurred
    - PLIB_PMP_InputOverflowClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BufferOverFlow feature is supported on the device
    - false  - The BufferOverFlow feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBufferOverFlow( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsInputBufferXStatus( PMP_MODULE_ID index )

  Summary:
    Identifies that the InputBufferXStatus feature exists on the PMP module. 

  Description:
    This interface identifies that the InputBufferXStatus feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_InputBufferXIsFull
    - PLIB_PMP_IsDataReceived

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InputBufferXStatus feature is supported on the device
    - false  - The InputBufferXStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsInputBufferXStatus( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsOutPutBufferEmpty( PMP_MODULE_ID index )

  Summary:
    Identifies that the OutPutBufferEmpty feature exists on the PMP module. 

  Description:
    This interface identifies that the OutPutBufferEmpty feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_OutputBuffersAreEmpty

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The OutPutBufferEmpty feature is supported on the device
    - false  - The OutPutBufferEmpty feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsOutPutBufferEmpty( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBufferUnderFlow( PMP_MODULE_ID index )

  Summary:
    Identifies that the BufferUnderFlow feature exists on the PMP module. 

  Description:
    This interface identifies that the BufferUnderFlow feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_OutputUnderflowHasOccurred
    - PLIB_PMP_OutputUnderflowClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BufferUnderFlow feature is supported on the device
    - false  - The BufferUnderFlow feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBufferUnderFlow( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsOutputBufferXStatus( PMP_MODULE_ID index )

  Summary:
    Identifies that the OutputBufferXStatus feature exists on the PMP module. 

  Description:
    This interface identifies that the OutputBufferXStatus feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_OutputBufferXIsEmpty
    - PLIB_PMP_IsDataTransmitted

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The OutputBufferXStatus feature is supported on the device
    - false  - The OutputBufferXStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsOutputBufferXStatus( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBufferRead( PMP_MODULE_ID index )

  Summary:
    Identifies that the BufferRead feature exists on the PMP module. 

  Description:
    This interface identifies that the BufferRead feature is available on
    the PMP module. When this interface returns true, this function is  
    supported on the device:
    - PLIB_PMP_InputBufferXByteReceive

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BufferRead feature is supported on the device
    - false  - The BufferRead feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBufferRead( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBufferWrite( PMP_MODULE_ID index )

  Summary:
    Identifies that the BufferWrite feature exists on the PMP module. 

  Description:
    This interface identifies that the BufferWrite feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_OutputBufferXByteSend

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BufferWrite feature is supported on the device
    - false  - The BufferWrite feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBufferWrite( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBufferType( PMP_MODULE_ID index )

  Summary:
    Identifies that the BufferType feature exists on the PMP module. 

  Description:
    This interface identifies that the BufferType feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_InputBufferTypeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BufferType feature is supported on the device
    - false  - The BufferType feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBufferType( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsSmartAddress( PMP_MODULE_ID index )

  Summary:
    Identifies that the SmartAddress feature exists on the PMP module. 

  Description:
    This interface identifies that the SmartAddress feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_SmartAddressStrobeEnable
    - PLIB_PMP_SmartAddressStrobeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SmartAddress feature is supported on the device
    - false  - The SmartAddress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsSmartAddress( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsBusKeeper( PMP_MODULE_ID index )

  Summary:
    Identifies that the BusKeeper feature exists on the PMP module. 

  Description:
    This interface identifies that the BusKeeper feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_BusKeeperEnable
    - PLIB_PMP_BusKeeperDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BusKeeper feature is supported on the device
    - false  - The BusKeeper feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsBusKeeper( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsTransactionError( PMP_MODULE_ID index )

  Summary:
    Identifies that the TransactionError feature exists on the PMP module. 

  Description:
    This interface identifies that the TransactionError feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_TransactionErrorHasOccurred
    - PLIB_PMP_TransactionErrorClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TransactionError feature is supported on the device
    - false  - The TransactionError feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsTransactionError( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsTransactionTimeOut( PMP_MODULE_ID index )

  Summary:
    Identifies that the TransactionTimeOut feature exists on the PMP module. 

  Description:
    This interface identifies that the TransactionTimeOut feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_TransactionHasTimedOut
    - PLIB_PMP_TransactionTimeoutClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TransactionTimeOut feature is supported on the device
    - false  - The TransactionTimeOut feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsTransactionTimeOut( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsAltMasterRequest( PMP_MODULE_ID index )

  Summary:
    Identifies that the AltMasterRequest feature exists on the PMP module. 

  Description:
    This interface identifies that the AltMasterRequest feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_AlternateMasterRequestStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AltMasterRequest feature is supported on the device
    - false  - The AltMasterRequest feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsAltMasterRequest( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsCurrentMaster( PMP_MODULE_ID index )

  Summary:
    Identifies that the CurrentMaster feature exists on the PMP module. 

  Description:
    This interface identifies that the CurrentMaster feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_AlternateMasterHasAccess

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CurrentMaster feature is supported on the device
    - false  - The CurrentMaster feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsCurrentMaster( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsEnhancedMasterMode( PMP_MODULE_ID index )

  Summary:
    Identifies that the EnhancedMasterMode feature exists on the PMP module. 

  Description:
    This interface identifies that the EnhancedMasterMode feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_EnhancedMasterModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The EnhancedMasterMode feature is supported on the device
    - false  - The EnhancedMasterMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsEnhancedMasterMode( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsReservedAddrSpace( PMP_MODULE_ID index )

  Summary:
    Identifies that the ReservedAddrSpace feature exists on the PMP module. 

  Description:
    This interface identifies that the ReservedAddrSpace feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_ReservedAddressSpaceBitsSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReservedAddrSpace feature is supported on the device
    - false  - The ReservedAddrSpace feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsReservedAddrSpace( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsWaitStatesAddrLatchStrobe( PMP_MODULE_ID index )

  Summary:
    Identifies that the WaitStatesAddrLatchStrobe feature exists on the PMP module. 

  Description:
    This interface identifies that the WaitStatesAddrLatchStrobe feature is 
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_WaitStatesAddressLatchStrobeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WaitStatesAddrLatchStrobe feature is supported on the device
    - false  - The WaitStatesAddrLatchStrobe feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsWaitStatesAddrLatchStrobe( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsWaitStatesAddrHoldStrobe( PMP_MODULE_ID index )

  Summary:
    Identifies that the WaitStatesAddrHoldStrobe feature exists on the PMP module. 

  Description:
    This interface identifies that the WaitStatesAddrHoldStrobe feature is
    available on the PMP module. When this interface returns true, these 
    functions are supported on the device:
    - PLIB_PMP_WaitStatesAddressHoldStrobeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WaitStatesAddrHoldStrobe feature is supported on the device
    - false  - The WaitStatesAddrHoldStrobe feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsWaitStatesAddrHoldStrobe( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsCSXActiveStatus( PMP_MODULE_ID index )

  Summary:
    Identifies that the CSXActiveStatus feature exists on the PMP module. 

  Description:
    This interface identifies that the CSXActiveStatus feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXIsActive

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CSXActiveStatus feature is supported on the device
    - false  - The CSXActiveStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsCSXActiveStatus( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsCSXPortControl( PMP_MODULE_ID index )

  Summary:
    Identifies that the CSXPortControl feature exists on the PMP module. 

  Description:
    This interface identifies that the CSXPortControl feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_ChipSelectXPortEnable
    - PLIB_PMP_ChipSelectXPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CSXPortControl feature is supported on the device
    - false  - The CSXPortControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsCSXPortControl( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXEnableStorbeSelect( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXEnableStorbeSelect feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXEnableStorbeSelect feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_ChipSelectXEnableStrobeSelect
    - PLIB_PMP_ChipSelectXEnableStrobeDeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXEnableStorbeSelect feature is supported on the device
    - false  - The ChipXEnableStorbeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXEnableStorbeSelect( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXACKPolarity( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXACKPolarity feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXACKPolarity feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipSelectXAckPolaritySelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXACKPolarity feature is supported on the device
    - false  - The ChipXACKPolarity feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXACKPolarity( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXDataSize( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXDataSize feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXDataSize feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXDataSizeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXDataSize feature is supported on the device
    - false  - The ChipXDataSize feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXDataSize( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXBaseAddress( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXBaseAddress feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXBaseAddress feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXBaseAddressSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXBaseAddress feature is supported on the device
    - false  - The ChipXBaseAddress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXBaseAddress( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXACKMode( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXACKMode feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXACKMode feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXAckModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXACKMode feature is supported on the device
    - false  - The ChipXACKMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXACKMode( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXAltMasterWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXAltMasterWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXAltMasterWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXWaitStatesAlternateMasterSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXAltMasterWaitStates feature is supported on the device
    - false  - The ChipXAltMasterWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXAltMasterWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXDataSetupWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXDataSetupWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXDataSetupWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXWaitStatesDataSetupSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXDataSetupWaitStates feature is supported on the device
    - false  - The ChipXDataSetupWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXDataSetupWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXStrobeWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXStrobeWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXStrobeWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXWaitStatesStrobeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXStrobeWaitStates feature is supported on the device
    - false  - The ChipXStrobeWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXStrobeWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsChipXDataHoldWaitStates( PMP_MODULE_ID index )

  Summary:
    Identifies that the ChipXDataHoldWaitStates feature exists on the PMP module. 

  Description:
    This interface identifies that the ChipXDataHoldWaitStates feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_ChipXWaitStatesDataHoldSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipXDataHoldWaitStates feature is supported on the device
    - false  - The ChipXDataHoldWaitStates feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsChipXDataHoldWaitStates( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsMasterRXTX( PMP_MODULE_ID index )

  Summary:
    Identifies that the MasterRXTX feature exists on the PMP module. 

  Description:
    This interface identifies that the MasterRXTX feature is available on
    the PMP module. When this interface returns true, these functions are 
    supported on the device:
    - PLIB_PMP_MasterSend
    - PLIB_PMP_MasterReceive

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MasterRXTX feature is supported on the device
    - false  - The MasterRXTX feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsMasterRXTX( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsSlaveTX( PMP_MODULE_ID index )

  Summary:
    Identifies that the SlaveTX feature exists on the PMP module. 

  Description:
    This interface identifies that the SlaveTX feature is available on
    the PMP module. When this interface returns true, this function is
    supported on the device:
    - PLIB_PMP_SlaveSend

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SlaveTX feature is supported on the device
    - false  - The SlaveTX feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsSlaveTX( PMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PMP_ExistsSlaveRX( PMP_MODULE_ID index )

  Summary:
    Identifies that the SlaveRX feature exists on the PMP module.

  Description:
    This interface identifies that the SlaveRX feature is available on
    the PMP module. When this interface returns true, this function is  
    supported on the device:
    - PLIB_PMP_SlaveReceive

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SlaveRX feature is supported on the device
    - false  - The SlaveRX feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PMP_ExistsSlaveRX( PMP_MODULE_ID index );



// *****************************************************************************
// *****************************************************************************
// Section: PMP Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_PMP_Enable ( PMP_MODULE_ID index )
    
  Summary:
    Enables the specific PMP module.
    
  Description:
    This function enables the specific PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_Enable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the EnableControl feature.  
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_PMP_ExistsEnableControl in your application to automatically 
    determine whether this feature is available.
*/

void PLIB_PMP_Enable ( PMP_MODULE_ID index );


/******************************************************************************
  Function:
    void PLIB_PMP_Disable ( PMP_MODULE_ID index )
    
  Summary:
    Disables the specific PMP module.
    
  Description:
    This function disables the specific PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_Disable( PMP_ID_0 );
    </code>

  Remarks:
    The default state after any reset for a PMP module is the disable state.
    If the PMP is disabled, all the related pins are in control of the 
    general purpose I/O logic.
    
    Disabling the PMP module resets the buffers to empty states. Any data 
    characters in the buffers are lost. All error and status bits are also reset. 
    
    Disabling the PMP while the PMP is active, will abort all pending 
    transmissions and receptions.  Re-enabling the PMP will restart the 
    module in the same configuration. 
    
    When disabled, the PMP power consumption is minimal.

    This function implements an operation of the EnableControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsEnableControl in your application to
    to automatically determine whether this feature is available. 
    
*/

void PLIB_PMP_Disable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    bool PLIB_PMP_IsEnabled ( PMP_MODULE_ID index )
    
  Summary:
    Checks whether or not the PMP module is enabled.
    
  Description:
    This function checks whether or not the PMP module is enabled.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true 	- If the PMP module is enabled
    - false 	- if the PMP module is disabled 

  Example:
    <code>
    bool pmpStatus;
    pmpStatus = PLIB_PMP_IsEnabled( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the EnableControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsEnableControl in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_IsEnabled ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_StopInIdleEnable ( PMP_MODULE_ID index )
    
  Summary:
    Discontinues PMP module operation when the device enters Idle mode.
    
  Description:
    This function enables the PMP module to discontinue operation when the device
    enters Idle mode.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_StopInIdleEnable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the StopInIdleControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsStopInIdleControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_StopInIdleEnable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_StopInIdleDisable ( PMP_MODULE_ID index )
    
  Summary:
    Enables the PMP module to continue operation in Idle mode.
    
  Description:
    This function disables the stop in idle flag. The PMP module continues
    operation in Idle mode.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_StopInIdleDisable( PMP_ID_0 );
    </code>

  Remarks:
    By default, the PMP module will continue operation in Idle mode.
    
    This function implements an operation of the StopInIdleControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsStopInIdleControl in your application to
    to automatically determine whether this feature is available.
    */

void PLIB_PMP_StopInIdleDisable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_MultiplexModeSelect( PMP_MODULE_ID index, 
                                       PMP_MUX_MODE multiplexMode )
    
  Summary:
    Configures the multiplexing between the address and data of the PMP module.
    
  Description:
    This function configures the pins used by the PMP module. Refer to 
    the enumeration PMP_MUX_MODE for the possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    multiplexMode	- One of the possible values from the PMP_MUX_MODE
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_MultiplexModeSelect( PMP_ID_0, PMP_MUX_NONE );
    </code>

  Remarks:
    This function implements an operation of the MUXModeSelect feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsMUXModeSelect in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_MultiplexModeSelect( PMP_MODULE_ID index, 
                                   PMP_MUX_MODE multiplexMode );


//******************************************************************************
/* Function:
    PMP_MUX_MODE PLIB_PMP_MultiplexModeGet( PMP_MODULE_ID index )
    
  Summary:
    Gets the current multiplexing mode configured between the address and data of
    the PMP module.
    
  Description:
    This function gets the current multiplexing mode configured between the address
    and data of the PMP module.

  Precondition:
    None.

  Parameters:
    None.
    
  Returns:
    index		- Identifier for the device instance to be addressed
    PMP_MUX_MODE	- One of the possible values from PMP_MUX_MODE

  Example:
    <code>
    PMP_MUX_MODE currentMuxMode; 
    currentMuxMode = PLIB_PMP_MultiplexModeGet( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the MUXModeSelect feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsMUXModeSelect in your application to
    to automatically determine whether this feature is available.
*/

PMP_MUX_MODE PLIB_PMP_MultiplexModeGet( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_InputBufferTypeSelect ( PMP_MODULE_ID index, 
                                          PMP_INPUT_BUFFER_TYPE inputBuffer )
    
  Summary:
    Selects the input buffer based on the input passed.
    
  Description:
    This function selects the input buffer based on the input passed. Either TTL or
    Schmitt Trigger input buffers are selected.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    inputBuffer		- One of the possible input buffer types
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_InputBufferTypeSelect( PMP_ID_0, PMP_INPUT_BUFFER_TTL );
    </code>

  Remarks:
    This function implements an operation of the BufferType feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferType in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_InputBufferTypeSelect ( PMP_MODULE_ID index, 
                                      PMP_INPUT_BUFFER_TYPE inputBuffer );


//******************************************************************************
/* Function:
    void PLIB_PMP_WriteEnableStrobePortEnable ( PMP_MODULE_ID index )
    
  Summary:
    Enables the PMP module write strobe port.
    
  Description:
    This function enables the write strobe port of the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WriteEnableStrobePortEnable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the WriteEnablePortControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsWriteEnablePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WriteEnableStrobePortEnable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_WriteEnableStrobePortDisable ( PMP_MODULE_ID index )
    
  Summary:
    Disables the PMP module write strobe port.
    
  Description:
    This function disables the write strobe port of the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WriteEnableStrobePortDisable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the WriteEnablePortControl feature.
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsWriteEnablePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WriteEnableStrobePortDisable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_ReadWriteStrobePortEnable ( PMP_MODULE_ID index )
    
  Summary:
    Enables the PMP module read strobe port.
    
  Description:
    This function enables the read strobe port of the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ReadWriteStrobePortEnable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the ReadWriteStrobePortControl 
    feature. This feature may not be available on all devices. Please refer 
    to the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsReadWriteStrobePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ReadWriteStrobePortEnable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_ReadWriteStrobePortDisable ( PMP_MODULE_ID index )
    
  Summary:
    Disables the PMP module read strobe port.
    
  Description:
    This function disables the read strobe port of the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ReadWriteStrobePortDisable( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the ReadWriteStrobePortControl 
    feature. This feature may not be available on all devices. Please refer
    to the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsReadWriteStrobePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ReadWriteStrobePortDisable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipSelectFunctionSelect( PMP_MODULE_ID index, 
                                            PMP_CHIPSELECT_FUNCTION chipselfunct )
    
  Summary:
    Defines the functionality of the pins intended to be used as Chip Select.
    
  Description:
    This function selects the PMCS1/PMCS2 as either Chip Select or as address
    lines depending on the way these bits are programmed.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    chipselfunct	- One of the possible values from PMP_CHIPSELECT_FUNCTION
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectFunctionSelect( PMP_ID_0, PMCS1_PMCS2_AS_ADDRESS_LINES );
    </code>

  Remarks:
    This function implements an operation of the ChipSelectoperation feature.  
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipSelectoperation in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectFunctionSelect( PMP_MODULE_ID index, 
                                        PMP_CHIPSELECT_FUNCTION chipselfunct );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressLatchPolaritySelect( PMP_MODULE_ID index, 
                                              PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the address latch strobe polarity.

  Description:
    This function sets the address latch polarity to the level specified.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    polarity	        - Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_AddressLatchPolaritySelect( PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH );
    </code>

  Remarks:
    This function implements an operation of the AddressLatchPolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressLatchPolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressLatchPolaritySelect ( PMP_MODULE_ID index, 
                                           PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipSelectXPolaritySelect ( PMP_MODULE_ID index, 
                                              PMP_CHIP_SELECT chipSelect,
                                              PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the specified Chip Select polarity.

  Description:
    This function sets the specified Chip Select polarity to the level specified.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- Identifier for Chip Select
    polarity	- Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PMP_CHIP_SELECT chipSelect = PMP_CHIP_SELECT_ONE;
    PLIB_PMP_ChipSelectXPolaritySelect( PMP_ID_0, 
                                        chipSelect, 
                                        PMP_POLARITY_ACTIVE_HIGH );
    </code>

  Remarks:
    This function implements an operation of the ChipXPolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXPolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXPolaritySelect ( PMP_MODULE_ID index, 
                                          PMP_CHIP_SELECT chipSelect,
                                          PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
    void PLIB_PMP_WriteEnableStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                    PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the polarity of the write enable strobe.

  Description:
    This function sets the polarity of the write enable strobe to the level 
    specified.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    polarity		- Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WriteEnableStrobePolaritySelect( PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH );
    </code>

  Remarks:
    This function implements an operation of the WriteEnablePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsWriteEnablePolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WriteEnableStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
    void PLIB_PMP_ReadWriteStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                  PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the polarity of the read strobe.

  Description:
    This function sets polarity of the read strobe to the level specified.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    polarity		- Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ReadWriteStrobePolaritySelect( PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH );
    </code>

  Remarks:
    This function implements an operation of the ReadWritePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsReadWritePolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ReadWriteStrobePolaritySelect ( PMP_MODULE_ID index, 
                                              PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
     bool	PLIB_PMP_PortIsBusy ( PMP_MODULE_ID index )
    
  Summary:
    Identifies if the (Master mode) PMP port is busy.
    
  Description:
    This function identifies if the PMP port is busy (in Master mode).
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true        - If the port is busy
    - false       - If the port is not busy

  Example:
    <code>
    bool status;
    status = PLIB_PMP_PortIsBusy( PMP_ID_0 );
    </code>

  Remarks:
    Works only in Master mode.
    This function implements an operation of the BusyStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBusyStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_PortIsBusy ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_InterruptModeSelect( PMP_MODULE_ID index, 
                                       PMP_INTERRUPT_MODE interruptMode )
    
  Summary:
    Configures the interrupt request mode being used with the PMP module.
    
  Description:
    This function configures the pins used by the PMP module. Refer to 
    the enumeration PMP_INTERRUPT_MODE for the possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    interruptMode	- One of the possible values from PMP_INTERRUPT_MODE
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_InterruptModeSelect( PMP_ID_0, PMP_INTERRUPT_NONE );
    </code>

  Remarks:
    This function implements an operation of the InterruptMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsInterruptMode in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_InterruptModeSelect( PMP_MODULE_ID index, 
                                   PMP_INTERRUPT_MODE interruptMode );


//******************************************************************************
/* Function:
    PMP_INTERRUPT_MODE PLIB_PMP_InterruptModeGet ( PMP_MODULE_ID index )
    
  Summary:
    Gets the current configured interrupt mode being used with the 
    PMP module.
    
  Description:
    This function gets the current configured interrupt mode being 
    used with the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    One of the possible values from PMP_INTERRUPT_MODE.

  Example:
    <code>
    PMP_INTERRUPT_MODE currentIntMode;
    currentIntMode = PLIB_PMP_InterruptModeGet ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the InterruptMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsInterruptMode in your application to
    to automatically determine whether this feature is available.
*/

PMP_INTERRUPT_MODE PLIB_PMP_InterruptModeGet ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressIncrementModeSelect( PMP_MODULE_ID index, 
                                              PMP_INCREMENT_MODE incrementMode )
    
  Summary:
    Configures the increment mode being used with the address of the PMP module.
    
  Description:
    This function configures the pins used by the PMP module. Refer to 
    the enumeration PMP_INCREMENT_MODE for the possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    incrementMode	- One of the possible values from PMP_INCREMENT_MODE

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_AddressIncrementModeSelect( PMP_ID_0, PMP_ADDRESS_INCREMENT_DECREMENT_DISABLE );
    </code>

  Remarks:
    This function implements an operation of the IncrementMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsIncrementMode in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressIncrementModeSelect( PMP_MODULE_ID index, 
                                          PMP_INCREMENT_MODE incrementMode );


//******************************************************************************
/* Function:
    PMP_INCREMENT_MODE PLIB_PMP_AddressIncrementModeGet ( PMP_MODULE_ID index )
    
  Summary:
    Gets the increment mode being used with the address of the PMP module.
    
  Description:
    This function gets the pins used by the PMP module. Refer to 
    the enumeration PMP_INCREMENT_MODE for the possible settings.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    PMP_INCREMENT_MODE	- One of the possible values from PMP_INCREMENT_MODE

  Example:
    <code>
    PMP_INCREMENT_MODE curAddressIncMode;
    curAddressIncMode = PLIB_PMP_AddressIncrementModeGet( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the IncrementMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsIncrementMode in your application to
    to automatically determine whether this feature is available.
*/

PMP_INCREMENT_MODE PLIB_PMP_AddressIncrementModeGet ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_DataSizeSelect ( PMP_MODULE_ID index, 
                                   PMP_DATA_SIZE size )
    
  Summary:
    Enables data transfer size for the PMP module.
    
  Description:
    This function enables 4-bit, 8-bit, or 16-bit data transfer for the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    size	- Identifier for the data size to be used

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_DataSizeSelect( PMP_ID_0, PMP_DATA_SIZE_8_BITS );
    </code>

  Remarks:
    This function implements an operation of the DataTransferSize feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsDataTransferSize in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_DataSizeSelect ( PMP_MODULE_ID index, 
                               PMP_DATA_SIZE size );


//******************************************************************************
/* Function:
    void PLIB_PMP_OperationModeSelect( PMP_MODULE_ID index, 
                                       PMP_OPERATION_MODE operationMode )
    
  Summary:
    Configures the operation mode of the PMP module.
    
  Description:
    This function configures operation mode of the PMP module. Refer to 
    the enumeration PMP_OPERATION_MODE for the possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    operationMode	- One of the possible values from PMP_OPERATION_MODE

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_OperationModeSelect( PMP_ID_0, 
                                  PMP_MASTER_READ_WRITE_STROBES_MULTIPLEXED );
    </code>

  Remarks:
    This function implements an operation of the OperationMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsOperationMode in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_OperationModeSelect( PMP_MODULE_ID index, 
                                   PMP_OPERATION_MODE operationMode );


//******************************************************************************
/* Function:
    PMP_OPERATION_MODE PLIB_PMP_OperationModeGet ( PMP_MODULE_ID index )
    
  Summary:
    Gets the current operation mode of the PMP module.
    
  Description:
    This function gets the current operation mode of the PMP module.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    PMP_OPERATION_MODE	- One of the possible values from PMP_OPERATION_MODE

  Example:
    <code>
    PMP_OPERATION_MODE curOpMode;
    curOpMode = PLIB_PMP_OperationModeGet( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the OperationMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsOperationMode in your application to
    to automatically determine whether this feature is available.
*/

PMP_OPERATION_MODE PLIB_PMP_OperationModeGet ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_WaitStatesDataSetUpSelect( PMP_MODULE_ID index, 
                                             PMP_DATA_WAIT_STATES dataWaitState )
    
  Summary:
    Configures the data wait states (before the data transfer) needed to be used 
    with the PMP module.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states. Refer to the enumeration PMP_DATA_WAIT_STATES for the 
    possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    dataWaitState	- One of the possible values from PMP_DATA_WAIT_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WaitStatesDataSetUpSelect( PMP_ID_0, PMP_DATA_WAIT_TWO );
    </code>

  Remarks:
    This function implements an operation of the DataSetUpWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsDataSetUpWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WaitStatesDataSetUpSelect( PMP_MODULE_ID index, 
                                         PMP_DATA_WAIT_STATES dataWaitState );


//******************************************************************************
/* Function:
    void PLIB_PMP_WaitStatesStrobeSelect( PMP_MODULE_ID index, 
                                          PMP_STROBE_WAIT_STATES strobeWaitState )
    
  Summary:
    Configures the strobe wait states (during the data transfer) needed to be 
    used with the PMP module.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states. Refer to the enumeration PMP_STROBE_WAIT_STATES for the 
    possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    strobeWaitState	- One of the possible values from PMP_STROBE_WAIT_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WaitStatesStrobeSelect( PMP_ID_0, PMP_STROBE_WAIT_2 );
    </code>

  Remarks:
    This function implements an operation of the DataStrobeWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use
     PLIB_PMP_ExistsDataStrobeWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WaitStatesStrobeSelect( PMP_MODULE_ID index, 
                                      PMP_STROBE_WAIT_STATES strobeWaitState );


//******************************************************************************
/* Function:
    void PLIB_PMP_WaitStatesDataHoldSelect( PMP_MODULE_ID index, 
                                            PMP_DATA_HOLD_STATES dataHoldState )
    
  Summary:
    Configures the data hold states (after data transfer) needed to be used with 
    the PMP module.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for 
    wait states. Refer to the enumeration PMP_DATA_HOLD_STATES for the possible 
    settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    dataHoldState	- One of the possible values from PMP_DATA_HOLD_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WaitStatesDataHoldSelect( PMP_ID_0, PMP_DATA_HOLD_2 );
    </code>

  Remarks:
    This function implements an operation of the DataHoldWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsDataHoldWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WaitStatesDataHoldSelect( PMP_MODULE_ID index, 
                                        PMP_DATA_HOLD_STATES dataHoldState );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipSelectXEnable( PMP_MODULE_ID index, 
                                     PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Configures the Chip Select.
    
  Description:
    This function configures the Chip Select(s) being used by the PMP module.
    The specified Chip Select pin functions as ChipSelect.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    chipSelect	- Identifier for which Chip Select to configure
    
  Returns:
    None.

  Example:
    <code>
    PMP_CHIP_SELECT chipSelect = PMP_CHIP_SELECT_ONE;
    PLIB_PMP_ChipSelectXEnable( PMP_ID_0, chipSelect );
    </code>

  Remarks:
    This function implements an operation of the ChipSelectEnable feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipSelectEnable in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXEnable( PMP_MODULE_ID index, 
                                 PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipSelectXDisable( PMP_MODULE_ID index, 
                                      PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Configures the Chip Select.
    
  Description:
    This function configures the Chip Select(s) being used by the PMP module.
    The specified Chip Select pin functions as the address pin.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    chipSelect		- Identifier for which Chip Select to configure
    
  Returns:
    None.

  Example:
    <code>
    PMP_CHIP_SELECT chipSelect = PMP_CHIP_SELECT_ONE;
    PLIB_PMP_ChipSelectXDisable( PMP_ID_0, chipSelect );
    </code>

  Remarks:
    This function implements an operation of the ChipSelectEnable feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipSelectEnable in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXDisable( PMP_MODULE_ID index, 
                                  PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressSet ( PMP_MODULE_ID index, 
                               uint32_t address )

  Summary:
    Sets the current address of the PMP module to the specified address.

  Description:
    This function sets the current address of the PMP module to the specified 
    value.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    address		- Device address to be set
    
  Returns:
    None. 

  Example:
    <code>
    uint8_t no_of_addressLines = 8;
    PLIB_PMP_AddressSet( PMP_ID_0, 0xff );
    </code>

  Remarks:
    This function implements an operation of the AddressControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressSet ( PMP_MODULE_ID index, 
                           uint32_t address );
                           
                           
//******************************************************************************
/* Function:
    uint32_t PLIB_PMP_AddressGet ( PMP_MODULE_ID index )

  Summary:
    Gets the current address of the PMP module.

  Description:
    This function gets the current address of the PMP module.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    
  Returns:
    address		- Device address to be set

  Example:
    <code>
    uint32_t address;
    address = PLIB_PMP_AddressGet( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the AddressControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressControl in your application to
    to automatically determine whether this feature is available.
*/

uint32_t PLIB_PMP_AddressGet ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressLinesA0A1Set ( PMP_MODULE_ID index, 
                                        uint8_t address )

  Summary:
    Sets the address lines PMA0 and PMA1 with the value specified.

  Description:
    This function sets the address lines PMA0 and PMA1 with the value 
    specified. This function is used in the addressable parallel slave port
    mode.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    address	- The two-bit address
    
  Returns:
    None.

  Example:
    <code>
    uint8_t bufferAddress = 0x2;
    PLIB_PMP_AddressLinesA0A1Set( PMP_ID_0, bufferAddress );
    </code>

  Remarks:
    This function implements an operation of the AddressControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressLinesA0A1Set ( PMP_MODULE_ID index, 
                                    uint8_t address );


//******************************************************************************
/* Function:
    uint8_t PLIB_PMP_AddressLinesA0A1Get ( PMP_MODULE_ID index )

  Summary:
    Gets the value of the address lines PMA0 and PMA1.

  Description:
    This function gets the value of the address lines PMA0 and PMA1.
    This function is used in the addressable parallel slave port mode.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    uint8_t	- The two-bit address

  Example:
    <code>
    uint8_t bufferAddress;
    bufferAddress = PLIB_PMP_AddressLinesA0A1Get( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the AddressControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressControl in your application to
    to automatically determine whether this feature is available.
*/

uint8_t PLIB_PMP_AddressLinesA0A1Get ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressPortEnable ( PMP_MODULE_ID index, 
                                      PMP_ADDRESS_PORT portfunctions )

  Summary:
    Enables the port lines specified as PMP address lines.

  Description:
    This function enables the port lines specified as PMP address lines.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    portfunctions	- One of the possible values from PMP_ADDRESS_PORT

  Returns:
    None.

  Example:
    <code>
    //Example-1
    PMP_ADDRESS_PORT portfunctions = PMP_PMA2_TO_PMA13_PORTS;
    PLIB_PMP_AddressPortEnable( PMP_ID_0, PMP_PMA2_TO_PMA13_PORTS );
    
    //Example-2
    PLIB_PMP_AddressPortEnable( PMP_ID_0, 
                               ( PMP_PMA14_PORT | PMP_PMA15_PORT ) );
    </code>

  Remarks:
    This function implements an operation of the AddressPortPinControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressPortPinControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressPortEnable ( PMP_MODULE_ID index, 
                                  PMP_ADDRESS_PORT portfunctions );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressPortDisable ( PMP_MODULE_ID index, 
                                       PMP_ADDRESS_PORT portfunctions )

  Summary:
    Disables the port lines specified as PMP address lines.

  Description:
    This function disables the port lines specified as PMP address lines. They 
    function as normal I/O lines.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    portfunctions	- One of the possible values from PMP_ADDRESS_PORT
    
  Returns:
    None.

  Example:
    <code>
    //Example-1
    PMP_ADDRESS_PORT portfunctions = PMP_PMA2_TO_PMA13_PORTS;
    PLIB_PMP_AddressPortDisable( PMP_ID_0, PMP_PMA2_TO_PMA13_PORTS );
    
    //Example-2
    PLIB_PMP_AddressPortDisable( PMP_ID_0, 
                                ( PMP_PMA14_PORT | PMP_PMA15_PORT ) );
    </code>

  Remarks:
    This function implements an operation of the AddressPortPinControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressPortPinControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressPortDisable ( PMP_MODULE_ID index, 
                                   PMP_ADDRESS_PORT portfunctions );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressLatchStrobeEnable ( PMP_MODULE_ID index, 
                                             PMP_ADDRESS_LATCH latch )
    
  Summary:
    Enables the specific address latch strobe.
    
  Description:
    This function enables the PMP module with a specific address latch strobe 
    depending on which strobes are needed.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    latch	- Identifier for the latch to be enabled

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_AddressLatchStrobeEnable( PMP_ID_0, PMP_ADDRESS_LATCH_UPPER );
    PLIB_PMP_AddressLatchStrobeEnable( PMP_ID_0, PMP_ADDRESS_LATCH_HIGH );
    PLIB_PMP_AddressLatchStrobeEnable( PMP_ID_0, PMP_ADDRESS_LATCH_LOW );
    </code>

  Remarks:
    This function implements an operation of the AddressLatchStrobePortControl 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressLatchStrobePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressLatchStrobeEnable ( PMP_MODULE_ID index, 
                                         PMP_ADDRESS_LATCH latch );


//******************************************************************************
/* Function:
    void PLIB_PMP_AddressLatchStrobeDisable ( PMP_MODULE_ID index, 
                                              PMP_ADDRESS_LATCH latch )
    
  Summary:
    Disables the specific address latch strobe.
    
  Description:
    This function disables the PMP module with a specific address latch strobe 
    depending on which strobes are not needed. 

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    latch	- Identifier for the latch to be disabled

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_AddressLatchStrobeDisable( PMP_ID_0, PMP_ADDRESS_LATCH_UPPER );
    PLIB_PMP_AddressLatchStrobeDisable( PMP_ID_0, PMP_ADDRESS_LATCH_HIGH );
    PLIB_PMP_AddressLatchStrobeDisable( PMP_ID_0, PMP_ADDRESS_LATCH_LOW );
    </code>

  Remarks:
    This function implements an operation of the AddressLatchStrobePortControl 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAddressLatchStrobePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_AddressLatchStrobeDisable ( PMP_MODULE_ID index, 
                                          PMP_ADDRESS_LATCH latch );


//******************************************************************************
/* Function:
    bool PLIB_PMP_InputBuffersAreFull ( PMP_MODULE_ID index )
    
  Summary:
    Gets the state of the input buffers.    
    
  Description:
    This function gets the state of the input buffers. 
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true	-  If all input buffers are full
    - false	-  If all input buffers are not full
    
  Example:
    <code>
    uint8_t value;
    if(PLIB_PMP_InputBuffersAreFull( PMP_ID_0 ))
    {
     value = PLIB_PMP_InputBufferXByteReceive( PMP_ID_0, 1 );
    }
    </code>

  Remarks:
    This function implements an operation of the InputBufferFull feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsInputBufferFull in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_InputBuffersAreFull ( PMP_MODULE_ID index );


/***********************************************************************
  Function:
      bool PLIB_PMP_InputOverflowHasOccurred ( PMP_MODULE_ID index )
    
  Summary:
    Identifies if there was a receiver overflow error.
    
  Description:
    This function identifies if there was a receiver overflow error.
    
  Conditions:
    None.
    
  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Return:
    - true  - If the input buffer has overflowed
    - false - If the input buffer has not overflowed
    
  Example:
    <code>
    if(PLIB_PMP_InputOverflowHasOccurred( PMP_ID_0 ))
    {
        PLIB_PMP_InputOverflowClear( PMP_ID_0 );
    }
    </code>
    
  Remarks:
    This function implements an operation of the BufferOverFlow feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferOverFlow in your application to
    to automatically determine whether this feature is available.
 */

bool PLIB_PMP_InputOverflowHasOccurred ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_InputOverflowClear ( PMP_MODULE_ID index )
    
  Summary:
    Clears a PMP Overflow error.
    
  Description:
    This function clears an overflow error.  Clearing the error resets the
    receive buffer.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    if(PLIB_PMP_InputOverflowHasOccurred( PMP_ID_0 ))
    {
        PLIB_PMP_InputOverflowClear( PMP_ID_0 );
    }
    </code>

  Remarks:
    This function implements an operation of the BufferOverFlow feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferOverFlow in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_InputOverflowClear ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    bool PLIB_PMP_InputBufferXIsFull ( PMP_MODULE_ID index, 
                                       uint8_t buffer )
    
  Summary:
    Gets the state of the identified input buffer.
    
  Description:
    This function gets the state of the identified input buffer.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- The input buffer number (valid values are 0 to 3)
    
  Returns:
    - true	-  If all input buffers are full
    - false	-  If all input buffers are not full
    
  Example:
    <code>
    uint8_t value;
    // Check the status of buffer-2
    if(PLIB_PMP_InputBufferXIsFull( PMP_ID_0, 2 ))
    {
       // get data from buffer 2
       value = PLIB_PMP_InputBufferXByteReceive( PMP_ID_0, 2 );
    }
    </code>

  Remarks:
    This function implements an operation of the InputBufferXStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsInputBufferXStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_InputBufferXIsFull ( PMP_MODULE_ID index, 
                                   uint8_t buffer );
                                   
                                   
//******************************************************************************
/* Function:
    bool PLIB_PMP_IsDataReceived ( PMP_MODULE_ID index, 
                                   uint8_t buffer )
    
  Summary:
    Checks and returns if the data has been received in the specified buffer in
    Slave mode.
    
  Description:
    This function checks and returns if the data has been received in the 
    specified buffer in Slave mode.
    
  Precondition:
    The PMP module should be configured for Slave mode operation.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- One of the possible input buffers (valid values are 0 to 3)
    
  Returns:
    - true	- Data has been received in the specified buffer
    - false	- Data has not been received in the specified buffer
    
  Example:
    <code>
    int8_t data;
    // Check if data is received on buffer-2
    if(PLIB_PMP_IsDataReceived( PMP_ID_0, 2 ))
    {
        // get data from buffer-2
        data = PLIB_PMP_InputBufferXByteReceive( PMP_ID_0, 2 );
    }
    </code>

  Remarks:
    This function implements an operation of the InputBufferXStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsInputBufferXStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_IsDataReceived ( PMP_MODULE_ID index, 
                               uint8_t buffer );


//******************************************************************************
/* Function:
    bool PLIB_PMP_OutputBuffersAreEmpty ( PMP_MODULE_ID index )
    
  Summary:
    Gets the state of the output buffers.
    
  Description:
    This function gets the state of the output buffers. 
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true   -  If all output buffers are empty
     -false  -  If all output buffers are not empty

  Example:
    <code>
    uint8_t value=0xEF;
    
    if(PLIB_PMP_OutputBuffersAreEmpty( PMP_ID_0 ))
    {
     PLIB_PMP_OutputBufferXByteSend( PMP_ID_0, 1, value);
    }
    </code>

  Remarks:
    This function implements an operation of the OutPutBufferEmpty feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsOutPutBufferEmpty in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_OutputBuffersAreEmpty ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    bool PLIB_PMP_OutputUnderflowHasOccurred ( PMP_MODULE_ID index )
    
  Summary:
    Identifies if there was an output buffer sent out with no data.
    
  Description:
    This function identifies if there was a output buffer was sent out with 
    no data.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true	- If the input buffer was empty when data was sent
    - false	- If the output buffer was not empty when data was sent

  Example:
    <code>
    if(PLIB_PMP_OutputUnderflowHasOccurred( PMP_ID_0 ))
    {
        PLIB_PMP_OutputUnderflowClear( PMP_ID_0 );
    }
    </code>

  Remarks:
    This function implements an operation of the BufferUnderFlow feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferUnderFlow in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_OutputUnderflowHasOccurred ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_OutputUnderflowClear ( PMP_MODULE_ID index )
    
  Summary:
   Clears a PMP output underflow error.
    
  Description:
    This function clears a PMP output underflow error.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    if(PLIB_PMP_OutputUnderflowHasOccurred( PMP_ID_0 ))
    {
        PLIB_PMP_OutputUnderflowClear( PMP_ID_0 );
    }
    </code>

  Remarks:
    This function implements an operation of the BufferUnderFlow feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferUnderFlow in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_OutputUnderflowClear ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    bool PLIB_PMP_OutputBufferXIsEmpty ( PMP_MODULE_ID index, 
                                         uint8_t buffer )
    
  Summary:
    Gets the state of the input buffer.
    
  Description:
    This function gets the state of the input buffer. 
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- Output buffer number (valid range is 0 to 3)
    
  Returns:
    - true	-  If the identified output buffer is empty
    - false	-  If the identified output buffer is not empty

  Example:
    <code>
    uint8_t value = 0xEF;
    
    if(PLIB_PMP_OutputBufferXIsEmpty( PMP_ID_0, 1 ) )
    {
     PLIB_PMP_OutputBufferXByteSend( PMP_ID_0,1, value);
    }
    </code>

  Remarks:
    This function implements an operation of the OutputBufferXStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsOutputBufferXStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_OutputBufferXIsEmpty ( PMP_MODULE_ID index, 
                                     uint8_t buffer );
                                     
                                     
//******************************************************************************
/* Function:
    bool PLIB_PMP_IsDataTransmitted ( PMP_MODULE_ID index, 
                                      uint8_t buffer )
    
  Summary:
    Checks and returns if the data has been transmitted from the specified buffer
    in Slave mode.
    
  Description:
    Checks and returns if data has been transmitted from the specified buffer.
    
  Precondition:
    The PMP module should be configured for Slave mode operation.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- One of the possible output buffers (valid range is 0 to 3)
    
  Returns:
    - true	- If data has been transmitted from the specified buffer
    - false	- If data has not been transmitted from the specified buffer
    
  Example:
    <code>
    uint8_t data;
    if(PLIB_PMP_IsDataTransmitted( PMP_ID_0, 2 ))
    {
        PLIB_PMP_OutputBufferXByteSend( PMP_ID_0, 2, data );
    }
    </code>

  Remarks:
    This function implements an operation of the OutputBufferXStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsOutputBufferXStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_IsDataTransmitted ( PMP_MODULE_ID index, 
                                  uint8_t buffer );


//******************************************************************************
/* Function:
    uint8_t PLIB_PMP_InputBufferXByteReceive ( PMP_MODULE_ID index, 
                                               uint8_t buffer )
    
  Summary:
    Data to be received in Byte mode.
    
  Description:
    The data to be received in Byte mode from the specified PMP module.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- One of the possible buffers (valid values are 0 to 3)
    
  Returns:
    data	- Data to be received

  Example:
    <code>
    uint8_t mydata;
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        // get data from buffer-1
        mydata = PLIB_PMP_InputBufferXByteReceive( PMP_ID_0, 1 );
    }
    </code>

  Remarks:
    This function implements an operation of the BufferRead feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferRead in your application to
    to automatically determine whether this feature is available.
*/

uint8_t PLIB_PMP_InputBufferXByteReceive( PMP_MODULE_ID index, 
                                          uint8_t buffer );                                         
                                          

//******************************************************************************
/* Function:
    void PLIB_PMP_OutputBufferXByteSend ( PMP_MODULE_ID index, 
                                          uint8_t buffer, 
                                          uint8_t data )
    
  Summary:
    Data to be transmitted in Byte mode.
    
  Description:
    The data is transmitted in Byte mode for the specified PMP module.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    buffer	- One of the possible output buffers (valid range is 0 to 3)
    data	- Data to be transmitted
    
  Returns:
    None.

  Example:
    <code>
    uint8_t data = 'a';
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        PLIB_PMP_OutputBufferXByteSend( PMP_ID_0, 1, data );
    }
    </code>

  Remarks:
    This function implements an operation of the BufferWrite feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBufferWrite in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_OutputBufferXByteSend ( PMP_MODULE_ID index, 
                                      uint8_t buffer, 
                                      uint8_t data );

                     					 
//******************************************************************************
/* Function:
    void PLIB_PMP_MasterSend ( PMP_MODULE_ID index, 
                         		uint16_t data )

  Summary:
    Sends the specified data in Master mode.

  Description:
    This function sends the specified data. The data flow is from master to 
    slave.

  Precondition:
    The PMP module is configured for Master Mode.

  Parameters:
    index	- Identifier for the device instance to be addressed
    data  	- Data to be transmitted

  Returns:
    None.

  Example:
    <code>
    uint16_t data = 'a';
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        PLIB_PMP_MasterSend( PMP_ID_0, data );
    }
    </code>

  Remarks:
    This function to be used only when the PMP is acting as master.
    This function implements an operation of the MasterRXTX feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsMasterRXTX in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_MasterSend ( 	PMP_MODULE_ID index, 
                     		uint16_t data );
                     
//******************************************************************************
/* Function:
    uint16_t PLIB_PMP_MasterReceive ( PMP_MODULE_ID index )

  Summary:
    Receives the data in the master mode.

  Description:
    This function receives the data. The dataflow is from slave to master.

  Precondition:
    The PMP module is configured as master.

  Parameters:
    index	- Identifier for the device instance to be addressed.

  Returns:
    uint16_t    - Data received

  Example:
    <code>
    uint16_t data;
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        data = PLIB_PMP_MasterReceive( PMP_ID_0 );
    }
    </code>

  Remarks:
    This function to be used only when the PMP is acting as master.
    This function implements an operation of the MasterRXTX feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsMasterRXTX in your application to
    to automatically determine whether this feature is available.
*/

uint16_t PLIB_PMP_MasterReceive ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_SlaveSend ( 	PMP_MODULE_ID index, 
                                uint16_t data )

  Summary:
    Sends the specified data in Slave mode.

  Description:
    This function sends the specified data. The data flow is from slave to master.

  Precondition:
    The PMP module is configured for Slave Mode.

  Parameters:
    index	- Identifier for the device instance to be addressed
    data  	- Data to be transmitted

  Returns:
    None.

  Example:
    <code>
    uint16_t data = 'a';
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        PLIB_PMP_SlaveSend( PMP_ID_0, data );
    }
    </code>

  Remarks:
    This function to be used only when the PMP is acting as slave.
    This function implements an operation of the SlaveTX feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsSlaveTX in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_SlaveSend ( 	PMP_MODULE_ID index, 
                     		uint16_t data );


//******************************************************************************
/* Function:
    uint16_t PLIB_PMP_SlaveReceive ( PMP_MODULE_ID index )

  Summary:
    Receives the data in Slave mode.

  Description:
    This function receives the data. The dataflow is from master to slave.

  Precondition:
    The PMP module is configured as slave.

  Parameters:
    index	- Identifier for the device instance to be addressed.

  Returns:
    uint16_t    - Data received

  Example:
    <code>
    uint16_t data;
    if(!PLIB_PMP_PortIsBusy( PMP_ID_0 ))
    {
        data = PLIB_PMP_SlaveReceive( PMP_ID_0 );
    }
    </code>

  Remarks:
    This function to be used only when the PMP is acting as slave.
    This function implements an operation of the SlaveRX feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsSlaveRX in your application to
    to automatically determine whether this feature is available.
*/

uint16_t PLIB_PMP_SlaveReceive ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_ByteEnablePortEnable( PMP_MODULE_ID index, 
                                        PMP_PMBE_PORT pmbeInstance )
    
  Summary:
    Enables the byte enable port.
    
  Description:
    This function enables the byte enable port.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    pmbeInstance	- One of the possible  values from PMP_PMBE_PORT

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ByteEnablePortEnable( PMP_ID_0, PMBE_0 );
    </code>

  Remarks:
    This function implements an operation of the ExistsByteEnablePortControl 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsExistsByteEnablePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ByteEnablePortEnable( PMP_MODULE_ID index, 
                                    PMP_PMBE_PORT pmbeInstance);


//******************************************************************************
/* Function:
    void PLIB_PMP_ByteEnablePortDisable( PMP_MODULE_ID index, 
                                         PMP_PMBE_PORT pmbeInstance)
    
  Summary:
    Disables the byte enable port.
    
  Description:
    This function disables the byte enable port.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    pmbeInstance	- One of the possible values from PMP_PMBE_PORT

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ByteEnablePortDisable( PMP_ID_0, PMBE_0 );
    </code>

  Remarks:
    This function implements an operation of the ExistsByteEnablePortControl 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsExistsByteEnablePortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ByteEnablePortDisable( PMP_MODULE_ID index, 
                                     PMP_PMBE_PORT pmbeInstance);


//******************************************************************************
/* Function:
    void PLIB_PMP_ByteEnablePolaritySelect ( PMP_MODULE_ID index, 
                                            PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the byte enable polarity.

  Description:
    This function sets the byte enable polarity to the level specified.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    polarity		- Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ByteEnablePolaritySelect ( PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH );
    </code>

  Remarks:
    This function implements an operation of the ByteEnablePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsByteEnablePolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ByteEnablePolaritySelect ( PMP_MODULE_ID index, 
                                         PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
    void PLIB_PMP_SmartAddressStrobeEnable ( PMP_MODULE_ID index )
    
  Summary:
    Enables "smart" address strobes.
    
  Description:
    This function enables "smart" address strobes (each address phase is only 
    present if  the current access would cause a different address in the latch 
    than the previous address).

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_SmartAddressStrobeEnable ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the SmartAddress feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsSmartAddress in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_SmartAddressStrobeEnable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_SmartAddressStrobeDisable ( PMP_MODULE_ID index )
    
  Summary:
    Disables "smart" address strobes.
    
  Description:
    This function disables "smart" address strobes (each address phase is only 
    present if the current access would cause a different address in the latch 
    than the previous address).

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_SmartAddressStrobeDisable ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the SmartAddress feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsSmartAddress in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_SmartAddressStrobeDisable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_BusKeeperEnable ( PMP_MODULE_ID index )
   
  Summary:
    Enables the bus keeper (high-impedance) state.

  Description:
    The data bus can be kept in a high-impedance state when not actively being
    driven. This function enables this "bus keeper" state.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_BusKeeperEnable ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the BusKeeper feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBusKeeper in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_BusKeeperEnable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
    void PLIB_PMP_BusKeeperDisable ( PMP_MODULE_ID index )
    
  Summary:
    Disables the bus keeper (high-impedance) state.
    
  Description:
    The data bus can be kept in a high-impedance state when not actively being 
    driven.  This function disables this "bus keeper" state.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_BusKeeperDisable ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the BusKeeper feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsBusKeeper in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_BusKeeperDisable ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     bool	PLIB_PMP_TransactionErrorHasOccurred ( PMP_MODULE_ID index )
    
  Summary:
    Returns the status of a transaction error.
    
  Description:
    This function returns the status of a transaction error if an illegal
    transaction was requested.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true        - If illegal transaction was requested
    - false       - Transaction completed successfully

  Example:
    <code>
    status = PLIB_PMP_TransactionErrorHasOccurred ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the TransactionError feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsTransactionError in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_TransactionErrorHasOccurred ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     void	PLIB_PMP_TransactionErrorClear ( PMP_MODULE_ID index )
    
  Summary:
    Clears the transaction error flag.
    
  Description:
    This function clears the transaction error flag.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    if(PLIB_PMP_TransactionErrorHasOccurred ( PMP_ID_0 ) )
        PLIB_PMP_TransactionErrorClear ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the TransactionError feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsTransactionError in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_TransactionErrorClear ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     bool	PLIB_PMP_TransactionHasTimedOut ( PMP_MODULE_ID index )
    
  Summary:
    Returns the time-out status.
    
  Description:
    This function returns the time-out status of the PMP transaction.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true        - If the transaction timed out
    - false       - If the transaction completed successfully

  Example:
    <code>
    status = PLIB_PMP_TransactionHasTimedOut ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the TransactionTimeOut feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsTransactionTimeOut in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_TransactionHasTimedOut ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     void PLIB_PMP_TransactionTimeoutClear ( PMP_MODULE_ID index )
    
  Summary:
    Clears the time-out flag.
    
  Description:
    This function clears the time-out flag.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    None.

  Example:
    <code>
    if(PLIB_PMP_TransactionHasTimedOut ( PMP_ID_0 ))
        PLIB_PMP_TransactionTimeoutClear ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the TransactionTimeOut feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsTransactionTimeOut in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_TransactionTimeoutClear ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     bool	PLIB_PMP_AlternateMasterRequestStatus ( PMP_MODULE_ID index )
    
  Summary:
    Gets the status of the request from the alternate master.
    
  Description:
    This function gets the status of the request from the alternate master,
    whether or not the master is requesting use of the PMP module.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true        - If the alternate master is requesting use of the PMP module
    - false       - If the alternate master is not a making request for the PMP module

  Example:
    <code>
    status = PLIB_PMP_AlternateMasterRequestStatus ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the AltMasterRequest feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsAltMasterRequest in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_AlternateMasterRequestStatus  ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     bool	PLIB_PMP_AlternateMasterHasAccess ( PMP_MODULE_ID index )
    
  Summary:
    Gets the status of which alternate masters have gained access to the PMP module.
    
  Description:
    This function gets the status of the alternate masters that have gained access 
    to the PMP module, whether or not the alternate master has access to the 
    PMP module.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    
  Returns:
    - true        - If the alternate master has gained access to the PMP module
    - false       - If the CPU has gained access to the PMP module

  Example:
    <code>
    status = PLIB_PMP_AlternateMasterHasAccess ( PMP_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the CurrentMaster feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsCurrentMaster in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_AlternateMasterHasAccess  ( PMP_MODULE_ID index );


//******************************************************************************
/* Function:
     void PLIB_PMP_EnhancedMasterModeSelect ( PMP_MODULE_ID index, 
                                              PMP_MASTER_MODE master )
    
  Summary:
    Selects Master mode for the PMP module.
    
  Description:
    This function sets the PMP module for Master mode (either CPU or alternate master). 
    The alternate master can have direct I/O access.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    master	- Identifier for the master to be selected
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_EnhancedMasterModeSelect ( PMP_ID_0, PMP_CPU_MASTER );
    </code>

  Remarks:
    This function implements an operation of the EnhancedMasterMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsEnhancedMasterMode in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_EnhancedMasterModeSelect ( PMP_MODULE_ID index, 
                                         PMP_MASTER_MODE master );


//******************************************************************************
/* Function:
     void PLIB_PMP_ReservedAddressSpaceBitsSet ( PMP_MODULE_ID index, 
                                                 uint8_t reservedAddress )
    
  Summary:
    Sets the address bits of the reserved address space of the EPMP. The
    end address of the Chip Select-2 (if present).
    
  Description:
    This function sets the address bits of the reserved address space of the EPMP. The
    reserved address space determines the end address of the Chip Select-2 (if used).
    If the reserved address space is set to 0, the last EDS address for the 
    Chip Select-2 will be 0xFFFFFF. For the address range to be accessible for
    the Chip Select-2 set the reserved address space to a value higher than
    Chip Select-2 base address.
    
  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    reservedAddress	- The reserved address bits
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ReservedAddressSpaceBitsSet ( PMP_ID_0, 0xDF );
    </code>

  Remarks:
    This function implements an operation of the ReservedAddrSpace feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsReservedAddrSpace in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ReservedAddressSpaceBitsSet ( PMP_MODULE_ID index, 
                                            uint8_t reservedAddress );


//******************************************************************************
/* Function:
    void PLIB_PMP_WaitStatesAddressLatchStrobeSelect( PMP_MODULE_ID index, 
                                                      PMP_ADDRESS_LATCH_WAIT_STATES waitState )
    
  Summary:
    Configures the address wait states needed to be used with the PMP module.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states. Refer to the enumeration PMP_ADDRESS_LATCH_WAIT_STATES for the 
    possible settings.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    waitState	- One of the possible values from PMP_ADDRESS_LATCH_WAIT_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WaitStatesAddressLatchStrobeSelect( PMP_ID_0, 
                                                 PMP_ADDRESS_WAIT_ONE_AND_HALF );
    </code>

  Remarks:
    This function implements an operation of the WaitStatesAddrLatchStrobe 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsWaitStatesAddrLatchStrobe in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WaitStatesAddressLatchStrobeSelect( PMP_MODULE_ID index, 
                                                  PMP_ADDRESS_LATCH_WAIT_STATES waitState );


//******************************************************************************
/* Function:
    void PLIB_PMP_WaitStatesAddressHoldStrobeSelect( PMP_MODULE_ID index, 
                                                     PMP_ADDRESS_HOLD_LATCH_WAIT_STATES waitState )
    
  Summary:
    Configures the address wait states needed to be used with the PMP module.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states. Refer to the enumeration PMP_ADDRESS_HOLD_LATCH_WAIT_STATES for the 
    possible settings.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    waitState	- One of the possible values from PMP_ADDRESS_HOLD_LATCH_WAIT_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_WaitStatesAddressHoldStrobeSelect( PMP_ID_0, 
                                                PMP_ADDRESS_HOLD_ONE_AND_ONE_QUARTER );
    </code>

  Remarks:
    This function implements an operation of the WaitStatesAddrHoldStrobe 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsWaitStatesAddrHoldStrobe in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_WaitStatesAddressHoldStrobeSelect( PMP_MODULE_ID index, 
                                                 PMP_ADDRESS_HOLD_LATCH_WAIT_STATES waitState );


//******************************************************************************
/* Function:
    bool PLIB_PMP_ChipSelectXIsActive ( PMP_MODULE_ID index, 
                                        PMP_CHIP_SELECT chipSelect )

  Summary:
    Gets the current status of the specified Chip Select.

  Description:
    This function gets the current status of the specified Chip Select.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- Identifier for the Chip Select to be checked
    
  Returns:
    - true	- Chip Select is active
    - false	- Chip Select is not active

  Example:
    <code>
    PMP_CHIP_SELECT chipSelect = PMP_CHIP_SELECT_ONE;
    if(PLIB_PMP_ChipSelectXIsActive( PMP_ID_0, chipSelect ))
    {
      //Do something useful
    }
    </code>

  Remarks:
    This function implements an operation of the CSXActiveStatus feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsCSXActiveStatus in your application to
    to automatically determine whether this feature is available.
*/

bool PLIB_PMP_ChipSelectXIsActive ( PMP_MODULE_ID index, 
                                    PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXPortEnable ( PMP_MODULE_ID index, 
                                           PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Enables the specified Chip Select's port.
    
  Description:
    This function enables the specified Chip Select's port.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXPortEnable ( PMP_ID_0, PMP_CHIP_SELECT_ONE );
    </code>

  Remarks:
    This function implements an operation of the CSXPortControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsCSXPortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXPortEnable ( PMP_MODULE_ID index, 
                                      PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXPortDisable ( PMP_MODULE_ID index, 
                                            PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Disables the specified Chip Select's port.
    
  Description:
    This function disables the specified Chip Select's port.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXPortDisable ( PMP_ID_0, PMP_CHIP_SELECT_ONE );
    </code>

  Remarks:
    This function implements an operation of the CSXPortControl feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsCSXPortControl in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXPortDisable ( PMP_MODULE_ID index, 
                                       PMP_CHIP_SELECT chipSelect );


/*******************************************************************************
  Function:
       void PLIB_PMP_ChipSelectXByteEnablePortPolaritySelect ( PMP_MODULE_ID index, 
                                                               PMP_CHIP_SELECT chipSelect,
                                                   PMP_POLARITY_LEVEL polarity );
    
  Summary:
    Sets the nibble/byte enable polarity.
    
  Description:
    This function sets the nibble/byte enable polarity to the level
    specified.
    
  Conditions:
    None.
    
  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect 	- One of the possible values from PMP_CHIP_SELECT
    polarity 	- Possible polarity levels
    
  Return:
    None.
    
  Example:
    <code>
    PLIB_PMP_ChipSelectXByteEnablePortPolaritySelect ( PMP_ID_0, 
                                                       PMP_CHIP_SELECT_ONE, 
                                                       PMP_POLARITY_ACTIVE_LOW );
    </code>
    
  Remarks:
    This function implements an operation of the ChipXByteEnablePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXByteEnablePolarity in your application to
    to automatically determine whether this feature is available.   
*/	
                                                        
void PLIB_PMP_ChipSelectXByteEnablePortPolaritySelect ( PMP_MODULE_ID index, 
                                                           PMP_CHIP_SELECT chipSelect,
                                                           PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXWriteEnableStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                                PMP_CHIP_SELECT chipSelect
                                                                PMP_POLARITY_LEVEL polarity )
    
  Summary:
    Sets the write/enable strobe polarity.
    
  Description:
    This function sets the write/enable strobe polarity to the level specified.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    polarity	- Possible polarity levels
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXWriteEnableStrobePolaritySelect ( PMP_ID_0, 
                                                          PMP_CHIP_SELECT_ONE, 
                                                          PMP_POLARITY_ACTIVE_LOW );
    </code>

  Remarks:
    This function implements an operation of the ChipXWriteEnablePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXWriteEnablePolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXWriteEnableStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                           PMP_CHIP_SELECT chipSelect,
                                                           PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXReadWriteStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                              PMP_CHIP_SELECT chipSelect 
                                                              PMP_POLARITY_LEVEL polarity )
    
  Summary:
    Sets the read/write strobe polarity.
    
  Description:
    This function sets the read/write strobe polarity to the level specified.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    polarity	- Possible polarity levels
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXReadWriteStrobePolaritySelect ( PMP_ID_0, 
                                                        PMP_CHIP_SELECT_ONE, 
                                                        PMP_POLARITY_ACTIVE_LOW );
    </code>

  Remarks:
    This function implements an operation of the ChipXReadWritePolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXReadWritePolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXReadWriteStrobePolaritySelect ( PMP_MODULE_ID index, 
                                                         PMP_CHIP_SELECT chipSelect, 
                                                         PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXEnableStrobeSelect ( PMP_MODULE_ID index, 
                                                   PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Selects the read/write and enable strobes.
    
  Description:
    This function selects the read/write and enable strobes.
    The read and write strobes share a common line. A separate enable line
    is provided to differentiate between read and write operations.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXEnableStrobeSelect ( PMP_ID_0, PMP_CHIP_SELECT_ONE );
    </code>

  Remarks:
    This function implements an operation of the ChipXEnableStorbeSelect feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXEnableStorbeSelect in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXEnableStrobeSelect ( PMP_MODULE_ID index, 
                                              PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipSelectXEnableStrobeDeSelect ( PMP_MODULE_ID index, 
                                                     PMP_CHIP_SELECT chipSelect )
    
  Summary:
    Selects the read and write strobes. The enable strobe is not selected
    (not required).
    
  Description:
    This function selects the read and write strobes. The read and write
    strobes have independent lines.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipSelectXEnableStrobeDeSelect ( PMP_ID_0, PMP_CHIP_SELECT_ONE );
    </code>

  Remarks:
    This function implements an operation of the ChipXEnableStorbeSelect feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXEnableStorbeSelect in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXEnableStrobeDeSelect ( PMP_MODULE_ID index, 
                                                PMP_CHIP_SELECT chipSelect );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipSelectXAckPolaritySelect ( PMP_MODULE_ID index, 
                                                 PMP_CHIP_SELECT chipSelect 
                                                 PMP_POLARITY_LEVEL polarity )

  Summary:
    Sets the Chip Select acknowledge polarity.

  Description:
    This function sets the Chip Select acknowledge polarity to the level specified.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    chipSelect	- Identifier for the Chip Select
    polarity	- Possible polarity levels

  Returns:
    None.

  Example:
    <code>
    PMP_CHIP_SELECT chipSelect = PMP_CHIP_SELECT_ONE;
    PLIB_PMP_ChipSelectXAckPolaritySelect( PMP_ID_0, 
                                           chipSelect, 
                                           PMP_POLARITY_ACTIVE_LOW );
    </code>

  Remarks:
    This function implements an operation of the ChipXACKPolarity feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXACKPolarity in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipSelectXAckPolaritySelect ( PMP_MODULE_ID index, 
                                             PMP_CHIP_SELECT chipSelect, 
                                             PMP_POLARITY_LEVEL polarity );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipXDataSizeSelect ( PMP_MODULE_ID index, 
                                        PMP_CHIP_SELECT chipSelect, 
                                        PMP_DATA_SIZE size )
    
  Summary:
    Enables data transfer size for the PMP for the specified device.
    
  Description:
    This function enables 4-bit, 8-bit, or 16-bit data transfer for the PMP for the 
    specified device.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    size	- Identifier for the data size to be used
    chipSelect	- One of the possible values from PMP_CHIP_SELECT

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipXDataSizeSelect( PMP_ID_0, 
                                  PMP_CHIP_SELECT_ONE, 
                                  PMP_DATA_SIZE_8_BITS );
    </code>

  Remarks:
    This function implements an operation of the ChipXDataSize feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXDataSize in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXDataSizeSelect ( PMP_MODULE_ID index, 
                                    PMP_CHIP_SELECT chipSelect, 
                                    PMP_DATA_SIZE size ); 


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipXBaseAddressSet ( PMP_MODULE_ID index, 
                                        PMP_CHIP_SELECT chipSelect, 
                                        uint16_t baseAddress )
    
  Summary:
    Sets the base address of the specified device.
    
  Description:
    This function sets the base address of the specified device.

  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    baseAddress	- Base address of the chip
    chipSelect	- One of the possible values from PMP_CHIP_SELECT

  Returns:
    None.

  Example:
    <code>
    uint16_t baseAddress = 0x00FF;
    PLIB_PMP_ChipXBaseAddressSet( PMP_ID_0, PMP_CHIP_SELECT_ONE, baseAddress );
    </code>

  Remarks:
    This function implements an operation of the ChipXBaseAddress feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXBaseAddress in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXBaseAddressSet ( PMP_MODULE_ID index, 
                                    PMP_CHIP_SELECT chipSelect, 
                                    uint16_t baseAddress );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipXAckModeSelect ( PMP_MODULE_ID index, 
                                        PMP_CHIP_SELECT chipSelect, 
                                        PMP_ACK_MODE mode )
    
  Summary:
    Selects the acknowledge mode for the PMP module.
    
  Description:
    This function sets the acknowledge for the PMP module. Either enables, disables,
    or enables it with time-out. See the PMP_ACK_MODE enumeration for additional 
    information.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    mode        - Identifier for the acknowledge mode to be selected
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns: 
    None.

  Example:
    <code>
    PLIB_PMP_ChipXAckModeSelect ( PMP_ID_0, PMP_CHIP_SELECT_ONE, PMP_ACK_DISABLED ); 
    </code>

  Remarks:
    This function implements an operation of the ChipXACKMode feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXACKMode in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXAckModeSelect ( PMP_MODULE_ID index, 
                                   PMP_CHIP_SELECT chipSelect, 
                                   PMP_ACK_MODE mode );


//******************************************************************************
/* Function:
     void PLIB_PMP_ChipXWaitStatesAlternateMasterSelect ( PMP_MODULE_ID index, 
                                                          PMP_CHIP_SELECT chipSelect,  
                                                          PMP_ALTERNATE_MASTER_WAIT_STATESS waitStates )
    
  Summary:
    Selects the wait states of the alternate master for Chip Select-X.
    
  Description:
    Selects the wait states of the alternate master for Chip Select-X.
    
  Precondition:
    None.

  Parameters:
    index	- Identifier for the device instance to be addressed
    waitStates  - Identifier for wait states
    chipSelect	- One of the possible values from PMP_CHIP_SELECT
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipXWaitStatesAlternateMasterSelect ( PMP_ID_0, 
                                                    PMP_CHIP_SELECT_ONE, 
                                                    PMP_ALTERNATE_MASTER_WAIT_THREE );
    </code>

  Remarks:
    This function implements an operation of the ChipXAltMasterWaitStates 
    feature. This feature may not be available on all devices. Please refer to 
    the specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXAltMasterWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXWaitStatesAlternateMasterSelect  ( PMP_MODULE_ID index, 
                                                      PMP_CHIP_SELECT chipSelect, 
                                                      PMP_ALTERNATE_MASTER_WAIT_STATES waitStates );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipXWaitStatesDataSetupSelect( PMP_MODULE_ID index, 
                                                  PMP_CHIP_SELECT chipselect, 
                                                  PMP_DATA_WAIT_STATES dataWaitState )
    
  Summary:
    Configures the data wait states (before the data transfer) needed to be used with 
    the PMP module for the specified device.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states for the specified device. Refer to the enumeration PMP_DATA_WAIT_STATES
    for the possible settings.

  Precondition:
    None.

  Parameters:
    index		 - Identifier for the device instance to be addressed
    chipselect		- One of the possible values from PMP_CHIP_SELECT
    dataWaitState	- One of the possible values from PMP_DATA_WAIT_STATES
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipXWaitStatesDataSetupSelect( PMP_ID_0, 
                                             PMP_CHIP_SELECT_ONE, 
                                             PMP_DATA_WAIT_ONE );
    </code>

  Remarks:
    This function implements an operation of the ChipXDataSetupWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXDataSetupWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXWaitStatesDataSetupSelect( PMP_MODULE_ID index, 
                                              PMP_CHIP_SELECT chipselect, 
                                              PMP_DATA_WAIT_STATES dataWaitState );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipXWaitStatesStrobeSelect( PMP_MODULE_ID index, 
                                               PMP_CHIP_SELECT chipselect, 
                                               PMP_STROBE_WAIT_STATES strobeWaitState )
    
  Summary:
    Configures the strobe wait states (during the data transfer) needed to be 
    used with the PMP module for the specified device.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for
    wait states for the specified device. Refer to the enumeration PMP_STROBE_WAIT_STATES
    for the possible settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    chipselect		- One of the possible values from PMP_CHIP_SELECT
    strobeWaitState	- One of the possible values from PMP_STROBE_WAIT_STATES

  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipXWaitStatesStrobeSelect( PMP_ID_0, 
                                          PMP_CHIP_SELECT_ONE, 
                                          PMP_STROBE_WAIT_3 );
    </code>

  Remarks:
    This function implements an operation of the ChipXStrobeWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXStrobeWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXWaitStatesStrobeSelect( PMP_MODULE_ID index, 
                                           PMP_CHIP_SELECT chipselect, 
                                           PMP_STROBE_WAIT_STATES strobeWaitState );


//******************************************************************************
/* Function:
    void PLIB_PMP_ChipXWaitStatesDataHoldSelect( PMP_MODULE_ID index, 
                                                 PMP_CHIP_SELECT chipselect, 
                                                 PMP_DATA_HOLD_STATES dataHoldState )
    
  Summary:
    Configures the data hold states (after data transfer) needed to be used with
    the PMP module for the specified device.
    
  Description:
    This function configures the number of peripheral bus clock cycles needed for 
    wait states. Refer to the enumeration PMP_DATA_HOLD_STATES for the possible 
    settings.

  Precondition:
    None.

  Parameters:
    index		- Identifier for the device instance to be addressed
    chipselect		- One of the possible values from PMP_CHIP_SELECT
    dataHoldState	- One of the possible values from PMP_DATA_HOLD_STATES
    
  Returns:
    None.

  Example:
    <code>
    PLIB_PMP_ChipXWaitStatesDataHoldSelect( PMP_ID_0, 
                                            PMP_CHIP_SELECT_ONE, 
                                            PMP_DATA_HOLD_2 );
    </code>

  Remarks:
    This function implements an operation of the ChipXDataHoldWaitStates feature.
    This feature may not be available on all devices. Please refer to the 
    specific device data sheet to determine availability or use 
    PLIB_PMP_ExistsChipXDataHoldWaitStates in your application to
    to automatically determine whether this feature is available.
*/

void PLIB_PMP_ChipXWaitStatesDataHoldSelect( PMP_MODULE_ID index, 
                                             PMP_CHIP_SELECT chipselect, 
                                             PMP_DATA_HOLD_STATES dataHoldState );



#endif // #ifndef _PLIB_PMP_H
/*******************************************************************************
 End of File
*/


