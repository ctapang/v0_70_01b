/*******************************************************************************
 USART Driver Configuration Template

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_config_template.h

  Summary:
    USART Driver Configuration Template.

  Description:
    These file provides the list of all the configurations that can be used with
    the driver. This file should not be included in the driver.

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

#ifndef _DRV_USART_CONFIG_TEMPLATE_H
#define _DRV_USART_CONFIG_TEMPLATE_H

//#error "This is a configuration template file.  Do not include it directly."

// *****************************************************************************
// *****************************************************************************
// Section: Core Functionality Configuration Options
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* USART driver objects configuration

  Summary
    Sets up the maximum number of hardware instances that can be supported

  Description
    Sets up the maximum number of hardware instances that can be supported

  Remarks:
    None
*/

#define DRV_USART_INSTANCES_NUMBER                      2


// *****************************************************************************
/* USART Client Count Configuration

  Summary
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Description
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Remarks:
    None
*/

#define DRV_USART_CLIENTS_NUMBER                      2


// *****************************************************************************
/* Index - Used for static drivers

  Summary:
    USART Static Index selection

  Description:
    USART Static Index selection for the driver object reference

  Remarks:
    This index is required to make a reference to the driver object

*/

#define DRV_USART_INDEX										DRV_USART_INDEX_2


// *****************************************************************************
/* Plib id

  Summary:
    Configures the PLIB id

  Description:
    This macro configures the PLIB Id for the driver. This is the static
    override of the dynamic intialization passed using DRV_USART_INIT.
*/

#define DRV_USART_PERIPHERAL_ID


// *****************************************************************************
/* USART RX Polarity Mode.

  Summary
    Defines the polarity of the RX pin.

  Description
    This macro defines the polarity of the RX pin. The possible values it can
    take are
    - true - polarity is inverted
    - false - polarity is not inverted


  Remarks:
    None.
*/

#define DRV_USART_POLARITY_INVERTED_RX       true


// *****************************************************************************
/* USART TX Polarity Mode.

  Summary
    Defines the polarity of the TX pin.

  Description
    This macro defines the polarity of the TX pin. The possible values it can
    take are
    - true - polarity is inverted
    - false - polarity is not inverted

  Remarks:
    None
*/

#define DRV_USART_POLARITY_INVERTED_TX               true


// *****************************************************************************
/* USART mode

  Summary
    Defines the mode to be used for the USART driver

  Description
    This macro controls support modes of the USART driver .
    The possible values it can take are:
    - DRV_USART_OPERATION_MODE_IRDA
    - DRV_USART_OPERATION_MODE_RS232
    - DRV_USART_OPERATION_MODE_RS485
    - DRV_USART_OPERATION_MODE_SYNC_MASTER
    - DRV_USART_OPERATION_MODE_SYNC_SLAVE
    - DRV_USART_OPERATION_MODE_LOOPBACK

  Remarks:
    None
*/

#define DRV_USART_OPERATION_MODE       DRV_USART_OPERATION_MODE_RS232


// *****************************************************************************
/* USART Interrupt Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation.The possible values it can take are
    - true - Enables the interrupt mode
    - false - Enables the polling mode

*/

#define DRV_USART_INTERRUPT_MODE


// *****************************************************************************
/* USART Baud Rate configuration

  Summary:
    Macro controls operation of the driver for Baud rate configuration

  Description:
    This macro controls the operation of the driver for Baud rate configuration.
    This is the static override of the dynamic intialization passed using
    DRV_USART_INIT.
*/

#define DRV_USART_BAUD_RATE


// *****************************************************************************
/* USART Byte mode internal buffer Tx size configuration

  Summary:
    Macro controls operation of the driver for defining the size of the Tx buffer

  Description:
    This macro controls the operation of the driver for defining the size of the Tx buffer
*/

#define DRV_USART_BYTE_Q_SIZE_TX        16


// *****************************************************************************
/* USART Byte mode internal buffer Rx size configuration

  Summary:
    Macro controls operation of the driver for defining the size of the Rx buffer

  Description:
    This macro controls the operation of the driver for defining the size of the Rx buffer


*/

#define DRV_USART_BYTE_Q_SIZE_RX        16


// *****************************************************************************
/* Line Control Mode

  Summary:
    Macro defines the line control mode

  Description:
    This macro defines the line control mode as 8 data bits, even parity and 1
    stop bit. It provides a static override of the initialization configuration
    of the line control mode. The possible values it can take are:
    - DRV_USART_LINE_CONTROL_8E1
    - DRV_USART_LINE_CONTROL_8E2
    - DRV_USART_LINE_CONTROL_8O1
    - DRV_USART_LINE_CONTROL_8O2
    - DRV_USART_LINE_CONTROL_8N1
    - DRV_USART_LINE_CONTROL_8N2
    - DRV_USART_LINE_CONTROL_9N1
*/

#define DRV_USART_LINE_CONTROL      DRV_USART_LINE_CONTROL_8N1


// *****************************************************************************
/* Hand Shake Mode

  Summary:
    Configures the handshake mode

  Description:
    This macro configures the handshake mode. This is the static override of the
    dynamic intialization passed using DRV_USART_INIT.  The possible values that
    it can take are
    - DRV_USART_HANDSHAKE_MODE_FLOWCONTROL
    - DRV_USART_HANDSHAKE_MODE_SIMPLEX
    - DRV_USART_HANDSHAKE_MODE_NONE
*/

#define DRV_USART_HANDSHAKE_MODE


// *****************************************************************************
/* Wake on start enable

  Summary:
    Macro configures that the peripheral should wake up on start

  Description:
    This macro configures that the peripheral should wake up on start.
*/

#define DRV_USART_WAKE_ON_START_ENABLE


// *****************************************************************************
/* Auto Baud enable

  Summary:
    Macro configures enabling the auto baud.

  Description:
    This macro configures enabling the auto baud. This is a static override of
    initialization parameter. This is the static override of the dynamic
    intialization passed using DRV_USART_INIT. The possible values it can take:
    - true - Enables Auto Baud
    - false - Disable Auto Baud
*/

#define DRV_USART_AUTO_BAUD_ENABLE          true


// *****************************************************************************
/* TX Interrupt Source

  Summary:
    Macro to define the Tx interrupt source in case of static driver

  Description:
    Macro to define the Tx interrupt source in case of static driver

  Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration

*/

#define DRV_USART_INTERRUPT_SOURCE_TX		INT_SOURCE_USART_2_TRANSMIT


// *****************************************************************************
/* RX Interrupt Source

  Summary:
    Macro to define the Rx interrupt source in case of static driver

  Description:
    Macro to define the Rx interrupt source in case of static driver

  Remarks:
    Refer to the INT PLIB document for more information on INT_SOURCE
    enumeration


*/

#define DRV_USART_INTERRUPT_SOURCE_RX			INT_SOURCE_USART_2_RECEIVE


// *****************************************************************************
/* Error Interrupt Source

  Summary:
    Defines the interrupt source for the error interrupt

  Description:
    This macro defines the interrupt source for the error interrupt. This is the
    static override of the dynamic intialization passed using DRV_USART_INIT.
*/

#define DRV_USART_INTERRUPT_SOURCE_ERROR		INT_SOURCE_USART_2_ERROR


// *****************************************************************************
/* USART power state configuration

  Summary:
    Macro controls power state of the USART

  Description:
    This macro controls the power state of the USART

  Remarks:
    Note: This feature may not be available in the device or the USART module
    selected
*/

#define DRV_USART_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP

// *****************************************************************************
/* USART transfer buffer configuration

  Summary:
    Transfer buffer depth

  Description:
    This macro controls the transfer buffer depth 

  Remarks:
    Note: This feature may not be available in the device or the USART module
    selected
*/
#define DRV_USART_XFER_BUFFER_NUMBER 		  10

#endif // #ifndef _DRV_USART_CONFIG_TEMPLATE_H

/*******************************************************************************
 End of File
*/
