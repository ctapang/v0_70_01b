 /*******************************************************************************
  USB CDC class definitions

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_cdc_local.h

  Summary:
    USB CDC class definitions

  Description:
    This file describes the CDC class specific definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _USB_HOST_CDC_LOCAL_H
#define _USB_HOST_CDC_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_host.h"
#include "usb/usb_cdc.h"




/*************************************************************************/
/* Function:
   void USB_HOST_CDC_Initbuffers(void))
  Summary:
    Initialize the defult values for the CDC device.
  Description:

  Parameters:
      None

  Returns:
    None
*/
void _USB_HOST_CDC_Initbuffers();
/*************************************************************************/

/* Function:
   _USB_HOST_CDC_findInstance(HC_DEVICE_ID id )

  Summary:
    Find the CDC instance

  Description:

  Parameters:
      HC_DEVICE_ID id

  Returns:
    uint8_t           instance
*/

uint8_t  _USB_HOST_CDC_findInstance(HC_DEVICE_ID id );


/*************************************************************************/

/* Function:
   _USB_HOST_CDC_ControlTransferComplete( USB_HOST_IRP *irp)

  Summary:
        Call back function for controltransfer status

  Description:


  Parameters:
      USB_HOST_IRP *irp

  Returns:
   void
*/
 void  _USB_HOST_CDC_ControlTransferComplete( USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_BulkInTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkin IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/

 uint8_t _USB_HOST_CDC_BulkInTransferComplete(USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_BulkOutTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkout IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/
void _USB_HOST_CDC_BulkOutTransferComplete( USB_HOST_IRP *irp);
  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_InterruptInTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Interrupt in IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/
void _USB_HOST_CDC_InterruptInTransferComplete( USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
    uint8_t USB_HOST_CDC_DeviceDetect())

  Summary:
    Number of CDC devices connected

  Description:


  Parameters:


  Returns:
       uint8_t        count
*/
 uint8_t USB_HOST_CDC_DeviceDetect();

#endif

 /************ End of file *************************************/
