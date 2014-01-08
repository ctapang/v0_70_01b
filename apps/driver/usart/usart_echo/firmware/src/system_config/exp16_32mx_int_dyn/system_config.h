/*******************************************************************************
  USART Echo Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the Explorer-16 board with PIC32MX795F512L.

  Description:
    This file is the top-level configuration header for the ISP Demo
    application for the Explorer-16 board with PIC32MX795F512L.
*******************************************************************************/

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

#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: General System Configuration
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_FREQUENCY  (80000000ul)

#define SYS_CLK_ClockFrequencyGet(i)        SYS_CLK_FREQUENCY
#define SYS_CLK_PeripheralClockGet(i)       SYS_CLK_FREQUENCY   // 1:1
#define SYS_CLK_PeriphBusFreqGet(i)         SYS_CLK_FREQUENCY   // 1:1


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

/* Define the size of the application's message buffer. */
#define APP_BUFFER_SIZE         60
#define APP_UART_BAUDRATE       9600
#define APP_NO_OF_BYTES_TO_READ 1
#define APP_ESC_MSG             0x1B

/* Define the application's message strings. */
#define APP_MSG_1   "/****************************************************\r\n"
#define APP_MSG_2   "Welcome to Microchip USART Echo Demo App.\r\n"
#define APP_MSG_3   "Press any character. Data will be echoed back.\r\n"
#define APP_MSG_4   "Press 'ESC' key to exit the application\r\n"
#define APP_MSG_5   "\r\n\r\n**********************End of demo*********************\r\n"

// *****************************************************************************
// *****************************************************************************
// Section: System Services Configuration
// *****************************************************************************
// *****************************************************************************

/* Define the index for the driver we'll use. */
#define SYS_USART_DRIVER_INDEX          DRV_USART_INDEX_0

/* Define the hardware (PLIB) index associted with this instance of the driver. */
#define SYS_USART_ID                    USART_ID_2

// *****************************************************************************
// *****************************************************************************
// Section: UART Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USART_INSTANCES_NUMBER      1
#define DRV_USART_CLIENTS_NUMBER        1
#define DRV_USART_INTERRUPT_MODE        true
#define DRV_USART_XFER_BUFFER_NUMBER    10
#define DRV_USART_INTERRUPT_SOURCE_TX   INT_SOURCE_USART_2_TRANSMIT
#define DRV_USART_INTERRUPT_SOURCE_RX   INT_SOURCE_USART_2_RECEIVE

#define DRV_USART_PERIPHERAL_BUS        

#define DRV_USART_CONFIG_BYTE_Q_SIZE_TX         1
#define DRV_USART_CONFIG_BYTE_Q_SIZE_RX         1
#define DRV_USART_CONFIG_BLOCK_DEVICE_MODE

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

