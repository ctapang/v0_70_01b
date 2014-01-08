/*******************************************************************************
  USB Descriptors and class specific data for this Device

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    USB Descriptors and class specific data for this Device

  Description:
    This file contains the USB descriptors and Win USB calss specific data that
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

#define MY_VID 0x04D8
#define MY_PID 0x0053

/*Generic USB */
#define GEN_USB_EP 		1   // Endpoint number

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE,          // Max packet size for EP0, see usb_config.h
    MY_VID,                 // Vendor ID: 0x04D8 is Microchip's Vendor ID
    MY_PID,                 // Product ID: 0x0053
    0x0000,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x00,                   // Device serial number string index
    0x01                   // Number of possible configurations
};

/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[]={
    /* Configuration Descriptor */
    0x09,//sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                // CONFIGURATION descriptor type
    0x20,0x00,            // Total length of data for this cfg
    1,                      // Number of interfaces in this cfg
    1,                      // Index value of this configuration
    0,                      // Configuration string index
    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED,               // Attributes, see usb_device.h
    50,                     // Max power consumption (2X mA)

    /* Interface Descriptor */
    0x09,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    0,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    0xFF,                   // Class code
    0xFF,                   // Subclass code
    0xFF,                   // Protocol code
    0,                      // Interface string index

    /* Endpoint Descriptor */
    0x07,                           /*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,        //Endpoint Descriptor
    GEN_USB_EP|USB_EP_DIRECTION_OUT,    //EndpointAddress
    USB_TRANSFER_TYPE_BULK,             //Attributes
    0x40,0x00,            //size
    1,                              //Interval

    0x07,                           /*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,        //Endpoint Descriptor
    GEN_USB_EP|USB_EP_DIRECTION_IN,    //EndpointAddress
    USB_TRANSFER_TYPE_BULK,             //Attributes
    0x40,0x00,            //size
    1                               //Interval
};


//Language code string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409}};

//Manufacturer string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'M','i','c','r','o','c','h','i','p',' ',
'T','e','c','h','n','o','l','o','g','y',' ','I','n','c','.'
}};

//Product string descriptor
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[25];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'S','i','m','p','l','e',' ','W','i','n','U','S','B',
' ','D','e','v','i','c','e',' ','D','e','m','o'}};

//Array of configuration descriptors
const uint8_t *const USB_CD_Ptr[]=
{
    (const uint8_t *const)&configDescriptor1
};

//Array of string descriptors
const uint8_t *const USB_SD_Ptr[]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002
};

//Array of full speed config descriptors
const uint8_t *const ConfigDescSet[] =
{
    (const uint8_t *const)&configDescriptor1[0]
};


const USB_MASTER_DESCRIPTOR usbMasterDescriptor =
{
    /* Full speed descriptor */
    (uint8_t *)&device_dsc,

    /* Total number of full speed configurations available */
    1,

    /* Pointer to array of full speed configurations descriptors*/
    (USB_DEVICE_CONFIG_DESCS_PTR)&ConfigDescSet[0],

    /* High speed device desc is not supported*/
    (uint8_t *)&device_dsc,

    /*Total number of high speed configurations available */
    1,

    /* Pointer to array of high speed configurations descriptors. */
    (USB_DEVICE_CONFIG_DESCS_PTR)&ConfigDescSet[0],

    /* Total number of string descriptors available */
    3,

    /* Pointer to array of string descriptors */
    (USB_DEVICE_STRING_DESCS_PTR)USB_SD_Ptr,

    /* Pointer to full speed dev qualifier. Not supported */
    NULL,

    /* Pointer to high speed dev qualifier. Not supported */
    NULL,

};



// Used by the device layer.
const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] =
{
   
    {
            USB_SPEED_FULL|USB_SPEED_HIGH, // Speed.
            1,              // Configuration value
            0,              // Interface number
            1,              // Number of interfaces
            USB_DEVICE_GENERIC_INDEX_0,  // Instance index
            NULL,               // Init structure is null
            &genFuncDriver      // Generic driver
    }

};



