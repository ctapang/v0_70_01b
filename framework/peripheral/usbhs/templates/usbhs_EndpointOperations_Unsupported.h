/*******************************************************************************
  USBHS Peripheral Library Template Implementation

  File Name:
    usbhs_EndpointOperations_Unsupported.h

  Summary:
    USBHS PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : EndpointOperations
    and its Variant : Unsupported
    For following APIs :
        PLIB_USBHS_EndpointRxRequestEnable
        PLIB_USBHS_HostRxEndpointConfigure
        PLIB_USBHS_HostTxEndpointConfigure
        PLIB_USBHS_ExistsEndpointOperations

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _USBHS_ENDPOINTOPERATIONS_UNSUPPORTED_H
#define _USBHS_ENDPOINTOPERATIONS_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  USBHS_EndpointRxRequestEnable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USBHS_EndpointRxRequestEnable 

  Description:
    This template implements the Unsupported variant of the PLIB_USBHS_EndpointRxRequestEnable function.
*/

PLIB_TEMPLATE void USBHS_EndpointRxRequestEnable_Unsupported( USBHS_MODULE_ID index , uint8_t endpoint )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USBHS_EndpointRxRequestEnable");
}

//******************************************************************************
/* Function :  USBHS_EndpointRxRequestClear_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USBHS_EndpointRxRequestClear 

  Description:
    This template implements the Unsupported variant of the PLIB_USBHS_EndpointRxRequestClear function.
*/

PLIB_TEMPLATE void USBHS_EndpointRxRequestClear_Unsupported( USBHS_MODULE_ID index , uint8_t endpoint )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USBHS_EndpointRxRequestClear");
}


//******************************************************************************
/* Function :  USBHS_HostRxEndpointConfigure_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USBHS_HostRxEndpointConfigure 

  Description:
    This template implements the Unsupported variant of the PLIB_USBHS_HostRxEndpointConfigure function.
*/

PLIB_TEMPLATE void USBHS_HostRxEndpointConfigure_Unsupported( USBHS_MODULE_ID index , uint8_t hostEndpoint , USB_SPEED speed , USB_TRANSFER_TYPE pipeType , uint16_t endpointSize , uint16_t receiveFIFOAddress , uint16_t fifoSize , uint8_t  targetEndpoint , uint8_t  targetDevice , uint8_t  targetHub , uint8_t  targetHubPort )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USBHS_HostRxEndpointConfigure");
}


//******************************************************************************
/* Function :  USBHS_HostTxEndpointConfigure_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USBHS_HostTxEndpointConfigure 

  Description:
    This template implements the Unsupported variant of the PLIB_USBHS_HostTxEndpointConfigure function.
*/

PLIB_TEMPLATE void USBHS_HostTxEndpointConfigure_Unsupported( USBHS_MODULE_ID index , uint8_t hostEndpoint , USB_SPEED speed , USB_TRANSFER_TYPE pipeType , uint16_t endpointSize , uint16_t receiveFIFOAddress , uint16_t fifoSize , uint8_t  targetEndpoint , uint8_t  targetDevice , uint8_t  targetHub , uint8_t  targetHubPort )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USBHS_HostTxEndpointConfigure");
}


//******************************************************************************
/* Function :  USBHS_ExistsEndpointOperations_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USBHS_ExistsEndpointOperations

  Description:
    This template implements the Unsupported variant of the PLIB_USBHS_ExistsEndpointOperations function.
*/

PLIB_TEMPLATE bool USBHS_ExistsEndpointOperations_Unsupported( USBHS_MODULE_ID index )
{
    return false;
}


#endif /*_USBHS_ENDPOINTOPERATIONS_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

