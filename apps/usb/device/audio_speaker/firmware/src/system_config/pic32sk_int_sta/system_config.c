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
 
#include <GenericTypeDefs.h>
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
    USB_DEVICE_CDC_DEVICE_CLASS_CODE,

    // Subclass code
    USB_DEVICE_CDC_DEVICE_SUBCLASS_CODE,

    // Protocol code
    0x00,

    // TODO need to be defined in the config.h (given by the app)
    // Max packet size for EP0, see usb_config.h
    USB_EP0_BUFF_SIZE,

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
const BYTE configDescriptor1[]={
    
       /* Configuration Descriptor */
    //sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    0x09,
    // CONFIGURATION descriptor type
    USB_DESCRIPTOR_CONFIGURATION,
    // Total length of data for this cfg
    67,0,
    // Number of interfaces in this cfg
    2,
    // Index value of this configuration
    1,
    // Configuration string index
    0,
    // Attributes, see usb_device.h
    _DEFAULT | _SELF,
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
    USB_DEVICE_CDC_COMM_INF_CLASS_CODE,
    // Subclass code
    USB_DEVICE_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL,
    // Protocol code
    USB_DEVICE_CDC_PROTOCOL_AT_V250,
    // Interface string index
    0,

    /* CDC Class-Specific Descriptors */
    // Size of the descriptor
    sizeof(USB_DEVICE_CDC_HEADER_FUNC_DESCRIPTOR),
    // CS_INTERFACE
    USB_DEVICE_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_DEVICE_CDC_FUNC_HEADER,
    //CDC spec version
	0x20,0x01,

    // Size of the descriptor
    sizeof(USB_DEVICE_CDC_ACM_FUNC_DESCRIPTOR),
    // CS_INTERFACE
    USB_DEVICE_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_DEVICE_CDC_FUNC_ACM,
    // bmCapabilities of ACM
    USB_DEVICE_CDC_ACM_SUPPORT_LINE_CODING_LINE_STATE_AND_NOTIFICATION,

    // Size of the descriptor
    sizeof(USB_DEVICE_CDC_UNION_FUNC_DESCRIPTOR),
    // CS_INTERFACE
    USB_DEVICE_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_DEVICE_CDC_FUNC_UNION,
    //com interface number
    // TODO: Have #define for these magic numbers
	0,
    //data interface number
	1,

    // Size of the descriptor
    sizeof(USB_DEVICE_CDC_CALL_MANAGEMENT_DESCRIPTOR),
    // CS_INTERFACE
    USB_DEVICE_CDC_DESC_CS_INTERFACE,
    // Type of functional descriptor
    USB_DEVICE_CDC_FUNC_CALL_MANAGEMENT,
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
    USB_DEVICE_CDC_DATA_INF_CLASS_CODE,
    // Subclass code
    0,
    // Protocol code
    USB_DEVICE_CDC_PROTOCOL_NO_CLASS_SPECIFIC,
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
const struct{BYTE bLength;BYTE bDscType;WORD string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409
}};

//Manufacturer string descriptor
const struct{BYTE bLength;BYTE bDscType;WORD string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};

//Product string descriptor
const struct{BYTE bLength;BYTE bDscType;WORD string[22];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'S','i','m','p','l','e',' ','C','D','C',' ',
'D','e','v','i','c','e',' ','D','e','m','o'
}};


//Array of string descriptors
const BYTE *const USB_SD_Ptr[3]=
{
    (const BYTE *const)&sd000,
    (const BYTE *const)&sd001,
    (const BYTE *const)&sd002
};


//Array of full speed config descriptors
const uint8_t *const fullSpeedConfigDescSet[2] =
{
    (const uint8_t *const)&configDescriptor1[0],
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

const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] = 
{

    {
    // Speed
    USB_SPEED_FULL,
    // Configuration value
    1,
    
    // function driver index
    APP_USBCDC_FUNC_INDEX,
    
    // function driver init
    (void*)&cdcInit,

    // CDC data exposed to device layer
    &cdcFuncDriver
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
    NULL,
    
    /*Total number of high speed configurations available */
    0,
    
    /* Pointer to array of high speed configurations descriptors. Not supported*/
    NULL,
    
    /* Total number of string descriptors available */
    3,
    
    /* Pointer to array of string descriptors */
    (USB_DEVICE_STRING_DESCS_PTR)USB_SD_Ptr,
    
    /* Pointer to full speed dev qualifier. Not supported */
    NULL,
    
    /* Pointer to high speed dev qualifier. Not supported */
    NULL,
    
};    


USB_DEVICE_CDC_LINE_CODING lineCoding[USB_DEVICE_CDC_MAX_INSTANCES] =
{
    {
        /* data terminal rate in bits per second */
        9600,

        /* stop bits */
        0,

        /* Parity */
        0,

        /* Data bits */
        8
    }
};
