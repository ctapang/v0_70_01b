/*******************************************************************************
 CDC Basic Demo Configuration file.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    Top-level configuration file for the CDC Basic demo application for
    the PIC32 Starter kit

  Description:
    This file contains the USB descriptors and CDC calss specific data that
	needs to be provided by the application.
*******************************************************************************/
// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{

    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0xEF,                   // Class Code
    0x02,                   // Subclass code
    0x01,                   // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE,      // Max packet size for EP0, see system_config.h
    0x04D8,                 // Vendor ID
    0x0208,                 // Product ID: CDC RS-232 Emulation Demo
    0x0100,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x00,                   // Device serial number string index
    0x01                    // Number of possible configurations
};


/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[]=
{
    /* Configuration Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,   // Descriptor Type
    0x8B,0x00,                      // Size of the descriptor
    0x04,                           // Number of interfaces in this cfg
    0x01,                           // Index value of this configuration
    0x00,                           // Configuration string index

    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED, // Attributes
    50,                                         // Max power consumption (2X mA)

    /* Interface Association Descriptor: CDC Function 1*/

    0x08,   // Size of this descriptor in bytes
    0x0B,   // Interface assocication descriptor type
    0x00,   // The first associated interface
    0x02,   // Number of contiguous associated interface
    0x02,   // bInterfaceClass of the first interface
    0x02,   // bInterfaceSubclass of the first interface
    0x01,   // bInterfaceProtocol of the first interface
    0x00,   // Interface string index

    /* Interface Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,       // Descriptor Type
    0x00,                           // Interface Number
    0x00,                           // Alternate Setting Number
    0x01,                           // Number of endpoints in this intf
    USB_CDC_COMMUNICATIONS_INTERFACE_CLASS_CODE,    // Class code
    USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL,        // Subclass code
    USB_CDC_PROTOCOL_AT_V250,                       // Protocol code
    0x00,                                           // Interface string index

    /* CDC Class-Specific Descriptors */

    sizeof(USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR),   // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                      // CS_INTERFACE
    USB_CDC_FUNCTIONAL_HEADER,                      // Type of functional descriptor
    0x20,0x01,                                      // CDC spec version

    sizeof(USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR),      // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                      // CS_INTERFACE
    USB_CDC_FUNCTIONAL_ABSTRACT_CONTROL_MANAGEMENT, // Type of functional descriptor
    USB_CDC_ACM_SUPPORT_LINE_CODING_LINE_STATE_AND_NOTIFICATION, // bmCapabilities of ACM

    sizeof(USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_HEADER), // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                          // CS_INTERFACE
    USB_CDC_FUNCTIONAL_UNION,                           // Type of functional descriptor
    0x00,                                               // com interface number

    sizeof(USB_CDC_CALL_MANAGEMENT_DESCRIPTOR),  // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,          // CS_INTERFACE
    USB_CDC_FUNCTIONAL_CALL_MANAGEMENT, // Type of functional descriptor
    0x00,                               // bmCapabilities of CallManagement
    0x01,                               // Data interface number

    /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x81,       // EndpointAddress ( EP1 IN INTERRUPT)
    0x03,       // Attributes type of EP (INTERRUPT)
    0x0A,0x00,  // Max packet size of this EP
    0x02,       // Interval (in ms)

    /* Interface Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,       // INTERFACE descriptor type
    0x01,                           // Interface Number
    0x00,                           // Alternate Setting Number
    0x02,
    USB_CDC_DATA_INTERFACE_CLASS_CODE,  // Class code
    0x00,                               // Subclass code
    USB_CDC_PROTOCOL_NO_CLASS_SPECIFIC, // Protocol code
    0x00,                               // Interface string index

    /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x02,       // EndpointAddress ( EP2 OUT INTERRUPT)
    0x02,       // Attributes type of EP (BULK)
    0x40,0x00,  // Max packet size of this EP
    0x00,       // Interval (in ms)

     /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x82,       // EndpointAddress ( EP2 IN )
    0x02,       // Attributes type of EP (BULK)
    0x40,0x00,  // Max packet size of this EP
    0x00,       // Interval (in ms)

    /* Interface Association Descriptor: CDC Function 1*/

    0x08,   // Size of this descriptor in bytes
    0x0B,   // Interface assocication descriptor type
    0x02,   // The first associated interface
    0x02,   // Number of contiguous associated interface
    0x02,   // bInterfaceClass of the first interface
    0x02,   // bInterfaceSubclass of the first interface
    0x01,   // bInterfaceProtocol of the first interface
    0x00,   // Interface string index

     /* Interface Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,       // Descriptor Type
    0x02,                           // Interface Number
    0x00,                           // Alternate Setting Number
    0x01,                           // Number of endpoints in this intf
    USB_CDC_COMMUNICATIONS_INTERFACE_CLASS_CODE,    // Class code
    USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL,        // Subclass code
    USB_CDC_PROTOCOL_AT_V250,                       // Protocol code
    0x00,                                           // Interface string index

    /* CDC Class-Specific Descriptors */

    sizeof(USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR),   // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                      // CS Interface
    USB_CDC_FUNCTIONAL_HEADER,                      // Type of functional descriptor
    0x20,0x01,                                      // CDC Specification version

    sizeof(USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR),      // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                      // CS_INTERFACE
    USB_CDC_FUNCTIONAL_ABSTRACT_CONTROL_MANAGEMENT, // Type of functional descriptor
    USB_CDC_ACM_SUPPORT_LINE_CODING_LINE_STATE_AND_NOTIFICATION, // bmCapabilities of ACM

    sizeof(USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_HEADER), // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,                          // CS_INTERFACE
    USB_CDC_FUNCTIONAL_UNION,                           // Type of functional descriptor
    0x02,                                               // Communication interface number

    sizeof(USB_CDC_CALL_MANAGEMENT_DESCRIPTOR),  // Size of the descriptor
    USB_CDC_DESC_CS_INTERFACE,          // CS_INTERFACE
    USB_CDC_FUNCTIONAL_CALL_MANAGEMENT, // Type of functional descriptor
    0x00,                               // bmCapabilities of CallManagement
    0x01,                               // Data interface number

    /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x83,       // EndpointAddress ( EP3 IN INTERRUPT)
    0x03,       // Attributes type of EP (INTERRUPT)
    0x0A,0x00,  // Max packet size of this EP
    0x02,       // Interval (in ms)

    /* Interface Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,       // INTERFACE descriptor type
    0x03,                           // Interface Number
    0x00,                           // Alternate Setting Number
    0x02,                           // Number for endpoint in this interface
    USB_CDC_DATA_INTERFACE_CLASS_CODE,  // Class code
    0x00,                               // Subclass code
    USB_CDC_PROTOCOL_NO_CLASS_SPECIFIC, // Protocol code
    0x00,                               // Interface string index

     /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x04,       // EndpointAddress ( EP2 OUT INTERRUPT)
    0x02,       // Attributes type of EP (BULK)
    0x40,0x00,  // Max packet size of this EP
    0x00,       // Interval (in ms)

     /* Interrupt Endpoint (IN)Descriptor */

    0x07,                       // Size of this descriptor
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    0x84,       // EndpointAddress ( EP2 IN )
    0x02,       // Attributes type of EP (BULK)
    0x40,0x00,  // Max packet size of this EP
    0x00,       // Interval (in ms)
};


// String descriptors.

//Language code string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409
}};

//Manufacturer string descriptor
const struct{uint8_t bLength;uint8_t  bDscType;uint16_t string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};

//Product string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[22];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'S','i','m','p','l','e',' ','C','D','C',' ',
'D','e','v','i','c','e',' ','D','e','m','o'
}};


//Array of string descriptors
const uint8_t *const USB_SD_Ptr[3]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002
};

//Array of full speed config descriptors
const uint8_t *const fullSpeedConfigDescSet[1] =
{
    (const uint8_t *const)&configDescriptor1[0]
};

// *****************************************************************************
/* Global USB Device function registration structure

  Summary:
    A function driver has to be registered with the USB device layer
    using this structure.

  Description:


  Remarks:

*/

USB_DEVICE_CDC_INIT cdcInit =
{
    .queueSizeRead = 1,
    .queueSizeWrite = 1,
    .queueSizeSerialStateNotification = 1
};

const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[2] =
{
    /* This is the first instance of the CDC Function Driver */
    {
        .speed = USB_SPEED_FULL|USB_SPEED_HIGH,
        .configurationValue = 1,
        .interfaceNumber = 0,
        .numberOfInterfaces = 2,
        .funcDriverIndex = 0,
        .funcDriverInit = &cdcInit,
        .driver = &cdcFuncDriver
    },

    /* This is the second instance of the CDC Function Driver */
    {
        .speed = USB_SPEED_FULL|USB_SPEED_HIGH,
        .configurationValue = 1,
        .interfaceNumber = 2,
        .numberOfInterfaces = 2,
        .funcDriverIndex = 1,
        .funcDriverInit = &cdcInit,
        .driver = &cdcFuncDriver
    },
};


// *****************************************************************************
/* Global USB Descriptor Structure

  Summary:
    Global USB descriptor structure containing pointers to standard USB
    descriptor structures.

  Description:


  Remarks:

*/

const USB_MASTER_DESCRIPTOR usbMasterDescriptor =
{
    /* Full speed descriptor */
    (uint8_t*)&device_dsc,

    /* Total number of full speed configurations available */
    1,

    /* Pointer to array of full speed configurations descriptors*/
    (USB_DEVICE_CONFIG_DESCS_PTR)&fullSpeedConfigDescSet[0],

    /* High speed device desc is not supported*/
    (uint8_t*)&device_dsc,

    /*Total number of high speed configurations available */
    1,

    /* Pointer to array of high speed configurations descriptors. Not supported*/
    (USB_DEVICE_CONFIG_DESCS_PTR)&fullSpeedConfigDescSet[0],

    /* Total number of string descriptors available */
    3,

    /* Pointer to array of string descriptors */
    (USB_DEVICE_STRING_DESCS_PTR)USB_SD_Ptr,

    /* Pointer to full speed dev qualifier. Not supported */
    NULL,

    /* Pointer to high speed dev qualifier. Not supported */
    NULL,

};


