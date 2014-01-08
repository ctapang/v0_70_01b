/*******************************************************************************
  USB Descriptors and class specific data for this Device

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    USB Descriptors and class specific data for this Device

  Description:
    This file contains the USB descriptors and HID calss specific data that
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



#define MY_VID 0x04D8
#define MY_PID 0x003F

/* HID EP */
#define HID_EP 		1   // Endpoint number
#define HID_NUM_OF_DSC  1   // Number of class descriptors

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE,      // Max packet size for EP0, see usb_config.h
    MY_VID,                 // Vendor ID
    MY_PID,                 // Product ID: Custom HID device demo
    0x0002,                 // Device release number in BCD format
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
    USB_DESCRIPTOR_CONFIGURATION,   // CONFIGURATION descriptor type
    0x29,0x00,                      // Total length of data for this cfg
    1,                              // Number of interfaces in this cfg
    1,                              // Index value of this configuration
    0,                              // Configuration string index
    
    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED, // Attributes, see usb_chapter_9.h
    50,                                         // Max power consumption (2X mA)

    /* Interface Descriptor */
    
    0x09,                       // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,   // INTERFACE descriptor type

    0,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    USB_HID_CLASS_CODE,     // Class code
    0,                      // Subclass code
    0,                      // Protocol code
    0,                      // Interface string index

    /* HID Class-Specific Descriptor */
    
    0x09,                           // Size of this descriptor in bytes
    USB_HID_DESCRIPTOR_TYPES_HID,   // HID descriptor type
    0x11,0x01,                      // HID Spec Release Number in BCD format (1.11)
    0x00,                           // Country Code (0x00 for Not supported)
    HID_NUM_OF_DSC,                 // Number of class descriptors, see usbcfg.h
    
    USB_HID_DESCRIPTOR_TYPES_REPORT,    // Report descriptor type
    HID_RPT01_SIZE,0x00,                // Size of the report descriptor

    /* Endpoint Descriptor */

    0x07,
    USB_DESCRIPTOR_ENDPOINT,        //Endpoint Descriptor
    HID_EP | USB_EP_DIRECTION_IN,       //EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    //Attributes
    0x40,0x00,                      //size
    0x01,                           //Interval

    /* Endpoint Descriptor */

    0x07,
    USB_DESCRIPTOR_ENDPOINT,        //Endpoint Descriptor
    HID_EP | USB_EP_DIRECTION_OUT,      //EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    //Attributes
    0x40,0x00,                      //size
    0x01                            //Interval
};

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
{'S','i','m','p','l','e',' ','H','I','D',' ',
'D','e','v','i','c','e',' ','D','e','m','o'
}};


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
const uint8_t *const fullSpeedConfigDescSet[] =
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
    (USB_DEVICE_CONFIG_DESCS_PTR)&fullSpeedConfigDescSet[0],

    /* High speed device desc is not supported*/
    (uint8_t *)&device_dsc,

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

//Class specific descriptor - HID Report descriptor
const uint8_t hid_rpt01[]={

    0x06, 0x00, 0xFF,       // Usage Page = 0xFF00 (Vendor Defined Page 1)
    0x09, 0x01,             // Usage (Vendor Usage 1)
    0xA1, 0x01,             // Collection (Application)
    0x19, 0x01,             //      Usage Minimum
    0x29, 0x40,             //      Usage Maximum 	//64 input usages total (0x01 to 0x40)
    0x15, 0x01,             //      Logical Minimum (data bytes in the report may have minimum value = 0x00)
    0x25, 0x40,      	    //      Logical Maximum (data bytes in the report may have maximum value = 0x00FF = unsigned 255)
    0x75, 0x08,             //      Report Size: 8-bit field size
    0x95, 0x40,             //      Report Count: Make sixty-four 8-bit fields (the next time the parser hits an "Input", "Output", or "Feature" item)
    0x81, 0x00,             //      Input (Data, Array, Abs): Instantiates input packet fields based on the above report size, count, logical min/max, and usage.
    0x19, 0x01,             //      Usage Minimum
    0x29, 0x40,             //      Usage Maximum 	//64 output usages total (0x01 to 0x40)
    0x91, 0x00,             //      Output (Data, Array, Abs): Instantiates output packet fields.  Uses same report size and count as "Input" fields, since nothing new/different was specified to the parser since the "Input" item.
    0xC0                   // End Collection
};


// HID Interface Init structure
USB_DEVICE_HID_INIT hidInit =
{
    sizeof(hid_rpt01),
    (uint8_t *)&hid_rpt01,
    .queueSizeReportReceive = 1,
    .queueSizeReportSend = 1,
};



// Used by the device layer.
const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] =
{
    // Speed,
    {USB_SPEED_FULL|USB_SPEED_HIGH,
     1,
     0,
     1,
     USB_DEVICE_HID_FUNC_INDEX,
     &hidInit,
     &hidFuncDriver}

};



