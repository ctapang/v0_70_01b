/*******************************************************************************
  USART Driver Interface Definition for static multi instance driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_static_multi.h
  
  Summary:
    USART Driver Interface Definition for static multi instance driver

  Description:
    The USART device driver provides a simple interface to manage the USART or 
    UART modules on Microchip microcontrollers.  This file defines the 
    interface definition for the USART driver.
    
  Remarks:
    Static interfaces encorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
    
    Static multi-open interfaces do not eliminate the open handle as it is 
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

#ifndef _DRV_USART_STATIC_MULTI_H
#define _DRV_USART_STATIC_MULTI_H


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART0multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART0multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART0multi_Deinitialize( void );

SYS_STATUS DRV_USART0multi_Status( void );

void DRV_USART0multi_TasksTX ( void   );

void DRV_USART0multi_TasksRX ( void   );

void DRV_USART0multi_TasksError ( void   );

DRV_HANDLE DRV_USART0multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART0multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART0multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART0multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART0multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART0multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART0multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART0multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART0multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART0multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART0multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);


// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART1multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART1multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART1multi_Deinitialize( void );

SYS_STATUS DRV_USART1multi_Status( void );

void DRV_USART1multi_TasksTX ( void   );

void DRV_USART1multi_TasksRX ( void   );

void DRV_USART1multi_TasksError ( void   );

DRV_HANDLE DRV_USART1multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART1multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART1multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART1multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART1multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART1multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART1multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART1multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART1multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART1multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART1multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 2 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART2multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART2multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART2multi_Deinitialize( void );

SYS_STATUS DRV_USART2multi_Status( void );

void DRV_USART2multi_TasksTX ( void   );

void DRV_USART2multi_TasksRX ( void   );

void DRV_USART2multi_TasksError ( void   );

DRV_HANDLE DRV_USART2multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART2multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART2multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART2multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART2multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART2multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART2multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART2multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART2multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART2multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART2multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 3 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART3multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART3multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART3multi_Deinitialize( void );

SYS_STATUS DRV_USART3multi_Status( void );

void DRV_USART3multi_TasksTX ( void   );

void DRV_USART3multi_TasksRX ( void   );

void DRV_USART3multi_TasksError ( void   );

DRV_HANDLE DRV_USART3multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART3multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART3multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART3multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART3multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART3multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART3multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART3multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART3multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART3multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART3multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 4 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART4multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART4multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART4multi_Deinitialize( void );

SYS_STATUS DRV_USART4multi_Status( void );

void DRV_USART4multi_TasksTX ( void   );

void DRV_USART4multi_TasksRX ( void   );

void DRV_USART4multi_TasksError ( void   );

DRV_HANDLE DRV_USART4multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART4multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART4multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART4multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART4multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART4multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART4multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART4multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART4multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART4multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART4multi_BufferStatus(DRV_HANDLE handle ,  DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 5 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART5multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART5multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART5multi_Deinitialize( void );

SYS_STATUS DRV_USART5multi_Status( void );

void DRV_USART5multi_TasksTX ( void   );

void DRV_USART5multi_TasksRX ( void   );

void DRV_USART5multi_TasksError ( void   );

DRV_HANDLE DRV_USART5multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART5multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART5multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART5multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART5multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART5multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART5multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART5multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART5multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART5multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART5multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 6 for the static multi open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USART6multi_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USART6multi_Reinitialize( const SYS_MODULE_INIT *init);

void DRV_USART6multi_Deinitialize( void );

SYS_STATUS DRV_USART6multi_Status( void );

void DRV_USART6multi_TasksTX ( void   );

void DRV_USART6multi_TasksRX ( void   );

void DRV_USART6multi_TasksError ( void   );

DRV_HANDLE DRV_USART6multi_Open( const DRV_IO_INTENT ioIntent );

void DRV_USART6multi_Close( const DRV_HANDLE handle );

DRV_USART_CLIENT_STATUS DRV_USART6multi_ClientStatus(  const DRV_HANDLE handle  );;

int DRV_USART6multi_Read(  const DRV_HANDLE handle , uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART6multi_ReadByte( const DRV_HANDLE handle, char *byte );

unsigned int DRV_USART6multi_Write(  const DRV_HANDLE handle , const uint8_t *buffer,  const unsigned int numbytes);

bool DRV_USART6multi_WriteByte( const DRV_HANDLE handle , const uint8_t byte);

DRV_USART_TRANSFER_STATUS DRV_USART6multi_TransferStatus ( const DRV_HANDLE handle );

uintptr_t DRV_USART6multi_BufferAdd(DRV_HANDLE handle ,DRV_USART_IO_BUFFER *bufferObject);

int8_t DRV_USART6multi_BufferTransferStatus(DRV_HANDLE handle ,DRV_HANDLE bufferHandle);

uint8_t DRV_USART6multi_BufferStatus(DRV_HANDLE handle , DRV_HANDLE bufferHandle);

#endif // #ifndef _DRV_USART_STATIC_MULTI_H

/*******************************************************************************
 End of File
*/

