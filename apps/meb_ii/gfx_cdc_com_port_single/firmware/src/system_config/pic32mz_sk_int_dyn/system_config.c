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


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************

// USB descriptors
/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
    // Size of this descriptor in bytes
    0x12,

    // DEVICE descriptor type
    USB_DESCRIPTOR_DEVICE,

    // USB Spec Release Number in BCD format
    0x0200,

    // Class Code
    USB_CDC_CLASS_CODE,

    // Subclass code
    USB_CDC_SUBCLASS_CODE,

    // Protocol code
    0x00,

    // Max packet size for EP0, see system_config.h
    /* name must be USB_EP0_BUFF_SIZE */
    USB_DEVICE_EP0_BUFFER_SIZE,

    // Vendor ID
    0x04D8,

    // Product ID: CDC RS-232 Emulation Demo
    0x000A,

    // Device release number in BCD format
    0x0100,

    // Manufacturer string index
    0x01,

    // Product string index
    0x02,

    // Device serial number string index
    0x00,
    
    // Number of possible configurations
    0x01
}; 


/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[]={
    
       /* Configuration Descriptor */
    //sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    0x09,
    // CONFIGURATION descriptor type
    USB_DESCRIPTOR_CONFIGURATION,
    // Total length of data for this cfg
    66,0,
    // Number of interfaces in this cfg
    2,
    // Index value of this configuration
    1,
    // Configuration string index
    0,
    // Attributes, see usb_device.h
    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED,
    // Max power consumption (2X mA)
    50,
							
    /* Interface Descriptor */
    //sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    9,
    // INTERFACE descriptor type
    USB_DESCRIPTOR_INTERFACE,
    // Interface Number
    0,
    // Alternate Setting Number
    0,
    // Number of endpoints in this intf
    1,
    // Class code
    USB_CDC_COMMUNICATIONS_INTERFACE_CLASS_CODE,
    // Subclass code
    USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL,
    // Protocol code
    USB_CDC_PROTOCOL_AT_V250,
    // Interface string index
    0,

    /* CDC Class-Specific Descriptors */
    // Size of the descriptor
    sizeof(USB_CDC_HEADER_FUNCTIONAL_DESCRIPTOR),
    // CS_INTERFACE
    USB_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_CDC_FUNCTIONAL_HEADER,
    //CDC spec version
	0x20,0x01,

    // Size of the descriptor
    sizeof(USB_CDC_ACM_FUNCTIONAL_DESCRIPTOR),
    // CS_INTERFACE
    USB_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_CDC_FUNCTIONAL_ABSTRACT_CONTROL_MANAGEMENT,
    // bmCapabilities of ACM
    USB_CDC_ACM_SUPPORT_LINE_CODING_LINE_STATE_AND_NOTIFICATION,

    // Size of the descriptor
    sizeof(USB_CDC_UNION_FUNCTIONAL_DESCRIPTOR_HEADER),
    // CS_INTERFACE
    USB_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_CDC_FUNCTIONAL_UNION,
    //com interface number   
	0,
  
    // Size of the descriptor
    sizeof(USB_CDC_CALL_MANAGEMENT_DESCRIPTOR),
    // CS_INTERFACE
    USB_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_CDC_FUNCTIONAL_CALL_MANAGEMENT,
    // bmCapabilities of CallManagement
    0x00,
    // Data interface number
    1,

    /* Interrupt Endpoint (IN)Descriptor */
    /*sizeof EP descriptor*/
    0x07,
    //Endpoint Descriptor
    USB_DESCRIPTOR_ENDPOINT,    
    //EndpointAddress ( EP1 IN INTERRUPT)
    0x81,
    //Attributes type of EP (INTERRUPT)
    0x03,
    // Max packet size of this EP
    0x0A,0x00,                  
    //Interval (in ms)
    0x02,

    /* Interface Descriptor */
    //sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    9,
    // INTERFACE descriptor type
    USB_DESCRIPTOR_INTERFACE,
    // Interface Number
    1,
    // Alternate Setting Number
    0,
    // Number of endpoints in this intf
    2,
    // Class code
    USB_CDC_DATA_INTERFACE_CLASS_CODE,
    // Subclass code
    0,
    // Protocol code
    USB_CDC_PROTOCOL_NO_CLASS_SPECIFIC,
    // Interface string index
    0,
    
    /* Bulk Endpoint (OUT) Descriptor */
    /*sizeof EP descriptor*/
    0x07,
    //Endpoint Descriptor
    USB_DESCRIPTOR_ENDPOINT,
    //EndpointAddress BULK OUT
    0x02,
    //Attributes BULK EP
	0x02,                       
    // MaxPacket Size of EP (BULK OUT)
    0x40,0x00,
    //Interval Can be ignored for BULK EPs.
    0x00,

    /* Bulk Endpoint (IN)Descriptor */
    /*sizeof EP descriptor*/
    0x07,/*sizeof(USB_EP_DSC)*/
    //Endpoint Descriptor
    USB_DESCRIPTOR_ENDPOINT,
    //EndpointAddress BULK IN
    0x82,            
    //Attributes BULK EP
    0x02,                       
    // MaxPacket Size of EP (BULK IN)
    0x40,0x00,                  
    //Interval Can be ignored for BULK EPs.
    0x00,                       

};

// String descriptors.

//Language code string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409
}};

//Manufacturer string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd001={
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
const uint8_t *const fullSpeedConfigDescSet[2] =
{
    (const uint8_t *const)&configDescriptor1[0],
    (const uint8_t *const)&configDescriptor1[0]
};    

const USB_DEVICE_CDC_INIT  cdcInit =
{
    .queueSizeRead = 1,
    .queueSizeWrite = 1,
    .queueSizeSerialStateNotification = 1
};


// *****************************************************************************
/* Global USB Device function registration structure

  Summary:
    A function driver has to be registered with the USB device layer
    using this structure.

  Description:


  Remarks:

 */


const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] = {

    {
     /* configuration descriptor index */
     .configurationValue = 1 ,
     /* CDC APIs exposed to the device layer */
     .driver = & cdcFuncDriver ,
     /* index of cdc function driver */
     .funcDriverIndex = 0 ,
     /* CDC init data */
     .funcDriverInit =  (void *)&cdcInit ,
     /* start interface number of this instance */
     .interfaceNumber = 0 ,
     /* total number of interfaces handled by this instance */
     .numberOfInterfaces = 2 ,
     /* USB SPEED */
     .speed = USB_SPEED_FULL|USB_SPEED_HIGH
    }

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

