/*******************************************************************************
  USART Driver Interface Definition for single client

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_static_single.h
  
  Summary:
    USART Driver Interface Definition for single client

  Description:
    This file defines interfaces for supporting single clients
    
  Remarks:
    Static interfaces encorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
    
    Static multi-open interfaces do not eliminat the open handle as it is 
    necessary to identify which client is calling.
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

#ifndef _DRV_USART_STATIC_SINGLE_H
#define _DRV_USART_STATIC_SINGLE_H

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART0_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART0_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART0_Deinitialize( void );

SYS_STATUS DRV_USART0_Status( void );

void DRV_USART0_TasksTX ( void );

void DRV_USART0_TasksRX ( void );

void DRV_USART0_TasksError ( void );

void DRV_USART0_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART0_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART0_ClientStatus( void );;

int DRV_USART0_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART0_ReadByte( char* byte );

unsigned int DRV_USART0_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART0_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART0_TransferStatus ( void );

uintptr_t DRV_USART0_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART0_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART0_BufferStatus(DRV_HANDLE bufferHandle);
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART1_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART1_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART1_Deinitialize( void );

SYS_STATUS DRV_USART1_Status( void );

void DRV_USART1_TasksTX ( void );

void DRV_USART1_TasksRX ( void );

void DRV_USART1_TasksError ( void );

void DRV_USART1_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART1_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART1_ClientStatus( void );;

int DRV_USART1_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART1_ReadByte( char* byte );

unsigned int DRV_USART1_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART1_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART1_TransferStatus ( void );

uintptr_t DRV_USART1_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART1_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART1_BufferStatus(DRV_HANDLE bufferHandle);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 2 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART2_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART2_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART2_Deinitialize( void );

SYS_STATUS DRV_USART2_Status( void );

void DRV_USART2_TasksTX ( void );

void DRV_USART2_TasksRX ( void );

void DRV_USART2_TasksError ( void );

void DRV_USART2_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART2_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART2_ClientStatus( void );;

int DRV_USART2_Read( uint8_t *buffer,  const uint32_t numbytes);

bool DRV_USART2_ReadByte( char* byte );

unsigned int DRV_USART2_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART2_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART2_TransferStatus ( void );

uintptr_t DRV_USART2_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART2_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART2_BufferStatus(DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 3 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART3_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART3_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART3_Deinitialize( void );

SYS_STATUS DRV_USART3_Status( void );

void DRV_USART3_TasksTX ( void );

void DRV_USART3_TasksRX ( void );

void DRV_USART3_TasksError ( void );

void DRV_USART3_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART3_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART3_ClientStatus( void );;

int DRV_USART3_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART3_ReadByte( char* byte );

unsigned int DRV_USART3_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART3_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART3_TransferStatus ( void );

uintptr_t DRV_USART3_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART3_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART3_BufferStatus(DRV_HANDLE bufferHandle);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 4 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART4_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART4_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART4_Deinitialize( void );

SYS_STATUS DRV_USART4_Status( void );

void DRV_USART4_TasksTX ( void );

void DRV_USART4_TasksRX ( void );

void DRV_USART4_TasksError ( void );

void DRV_USART4_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART4_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART4_ClientStatus( void );;

int DRV_USART4_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART4_ReadByte( char* byte );

unsigned int DRV_USART4_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART4_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART4_TransferStatus ( void );

uintptr_t DRV_USART4_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART4_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART4_BufferStatus(DRV_HANDLE bufferHandle);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 5 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART5_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART5_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART5_Deinitialize( void );

SYS_STATUS DRV_USART5_Status( void );

void DRV_USART5_TasksTX ( void );

void DRV_USART5_TasksRX ( void );

void DRV_USART5_TasksError ( void );

void DRV_USART5_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART5_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART5_ClientStatus( void );;

int DRV_USART5_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART5_ReadByte( char* byte );

unsigned int DRV_USART5_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART5_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART5_TransferStatus ( void );

uintptr_t DRV_USART5_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART5_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART5_BufferStatus(DRV_HANDLE bufferHandle);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 6 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART6_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART6_Reinitialize( const SYS_MODULE_INIT * const init);

void DRV_USART6_Deinitialize( void );

SYS_STATUS DRV_USART6_Status( void );

void DRV_USART6_TasksTX ( void );

void DRV_USART6_TasksRX ( void );

void DRV_USART6_TasksError ( void );

void DRV_USART6_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART6_Close( void );

DRV_USART_CLIENT_STATUS DRV_USART6_ClientStatus( void );;

int DRV_USART6_Read( uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART6_ReadByte( char* byte );

unsigned int DRV_USART6_Write( const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART6_WriteByte( const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART6_TransferStatus ( void );

uintptr_t DRV_USART6_BufferAdd(DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART6_BufferTransferStatus(DRV_HANDLE handle, DRV_HANDLE bufferHandle);

uint8_t DRV_USART6_BufferStatus(DRV_HANDLE bufferHandle);


#endif // #ifndef _DRV_USART_H

/*******************************************************************************
 End of File
*/

