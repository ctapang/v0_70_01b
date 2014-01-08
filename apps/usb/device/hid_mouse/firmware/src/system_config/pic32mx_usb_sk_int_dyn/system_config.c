/*******************************************************************************
  USB Descriptors and class specific data for this Device

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    USB Descriptors and class specific data for this Device

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

#define MY_VID 0x04D8
#define MY_PID 0x0000

/* Number of HID endpoints and report descriptor */
#define HID_EP 		1   
#define HID_NUM_OF_DSC  1   

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    0x00,                   // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_DEVICE_EP0_BUFFER_SIZE,      // Max packet size for EP0, see system_config.h
    MY_VID,                 // Vendor ID
    MY_PID,                 // Product ID: Custom HID device demo
    0x0003,                 // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    0x00,                   // Device serial number string index
    0x01                    // Number of possible configurations
};

const uint8_t configDescriptor1[]=
{
   0x09,                            // Size of this descriptor in bytes
   USB_DESCRIPTOR_CONFIGURATION,    // CONFIGURATION descriptor type
   0x22,0x00,                       // Total length of data for this cfg
   1,                               // Number of interfaces in this cfg
   1,                               // Index value of this configuration
   0,                               // Configuration string index
   
   USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED,  // Attributes, see usb_device.h
   50,                                          // Max power consumption (2X mA)

   /* Interface Descriptor */

   0x09,                        // Size of this descriptor in bytes
   USB_DESCRIPTOR_INTERFACE,    // INTERFACE descriptor type
   0,                           // Interface Number
   0,                           // Alternate Setting Number
   1,                           // Number of endpoints in this intf
   USB_HID_CLASS_CODE,          // Class code
   
   USB_HID_SUBCLASS_CODE_BOOT_INTERFACE_SUBCLASS ,  // Subclass code
   USB_HID_PROTOCOL_CODE_MOUSE,                     // Protocol code
   0,                                               // Interface string index

   /* HID Class-Specific Descriptor */

   0x09,                            // Size of this descriptor in bytes
   USB_HID_DESCRIPTOR_TYPES_HID,    // HID descriptor type

   0x11, 0x01,             // HID Spec Release Number in BCD format (1.11)
   0x00,                   // Country Code (0x00 for Not supported)
   HID_NUM_OF_DSC,         // Number of class descriptors, see usbcfg.h
   
   USB_HID_DESCRIPTOR_TYPES_REPORT, // Report descriptor type
   0x32,0x00,                       // Size of the report descriptor
   
   /* Endpoint Descriptor */

   0x07,                            // Size of this descriptor
   USB_DESCRIPTOR_ENDPOINT,         // Endpoint Descriptor
   HID_EP | USB_EP_DIRECTION_IN,        // EndpointAddress
   USB_TRANSFER_TYPE_INTERRUPT,     // Attributes
   0x40, 0x00,                      // size
   0x01                             // Interval
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
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[14];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'H','I','D',' ',
'M','o','u','s','e',' ','D','e','m','o'
}};

/* Class specific descriptor - HID Report descriptor */

const uint8_t hid_rpt01[] =
{
   0x05, 0x01, /* Usage Page (Generic Desktop)             */
   0x09, 0x02, /* Usage (Mouse)                            */
   0xA1, 0x01, /* Collection (Application)                 */
   0x09, 0x01, /*  Usage (Pointer)                         */
   0xA1, 0x00, /*  Collection (Physical)                   */
   0x05, 0x09, /*      Usage Page (Buttons)                */
   0x19, 0x01, /*      Usage Minimum (01)                  */
   0x29, 0x03, /*      Usage Maximum (03)                  */
   0x15, 0x00, /*      Logical Minimum (0)                 */
   0x25, 0x01, /*      Logical Maximum (1)                 */
   0x95, 0x03, /*      Report Count (3)                    */
   0x75, 0x01, /*      Report Size (1)                     */
   0x81, 0x02, /*      Input (Data, Variable, Absolute)    */
   0x95, 0x01, /*      Report Count (1)                    */
   0x75, 0x05, /*      Report Size (5)                     */
   0x81, 0x01, /*      Input (Constant)    ;5 bit padding  */
   0x05, 0x01, /*      Usage Page (Generic Desktop)        */
   0x09, 0x30, /*      Usage (X)                           */
   0x09, 0x31, /*      Usage (Y)                           */
   0x15, 0x81, /*      Logical Minimum (-127)              */
   0x25, 0x7F, /*      Logical Maximum (127)               */
   0x75, 0x08, /*      Report Size (8)                     */
   0x95, 0x02, /*      Report Count (2)                    */
   0x81, 0x06, /*      Input (Data, Variable, Relative)    */
   0xC0, 0xC0
};

//Array of string descriptors
const uint8_t *const USB_SD_Ptr[]=
{
    (const uint8_t *const)&sd000,
    (const uint8_t *const)&sd001,
    (const uint8_t *const)&sd002
};

//Array of full speed config descriptors
const uint8_t *const fullSpeedConfigDescSet[1] =
{
    (const uint8_t *const)&configDescriptor1[0],
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

/* HID Function Driver Initialization data structure */

USB_DEVICE_HID_INIT hidInit =
{
    .hidReportDescriptor = (void*)&hid_rpt01,
    .hidReportDescriptorSize = sizeof(hid_rpt01),
    .queueSizeReportSend = 1
    
};

/* This is the device layer function driver registration table */

const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] = 
{
    {
        USB_SPEED_FULL|USB_SPEED_HIGH,  /* Speed */
        1,                              /* Configuration Value */
        0,                              /* Interface Number */
        1,                              /* Number of interfaces */
        0,                              /* Function Driver Index */
        (void*)&hidInit,                /* Function Driver Initialization */
        &hidFuncDriver                  /* Pointer to the function driver functions */
    }
	        
};
