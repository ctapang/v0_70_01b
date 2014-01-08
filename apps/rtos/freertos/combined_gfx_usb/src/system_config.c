#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system/system.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"
#include "app_keyboard.h"
#include "app.h"
#include "bsp.h"


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/
#define MY_VID 0x04D8
#define MY_PID 0x0055
#define HID_EP 		1
#define HID_NUM_OF_DSC  1

/*
*********************************************************************************************************
*                                                GLOBALS
*********************************************************************************************************
*/
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

const uint8_t configDescriptor1[]=
{
    /* Configuration Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,   // CONFIGURATION descriptor type
    0x29,0x00,                      // Total length of data for this cfg
    1,                              // Number of interfaces in this cfg
    1,                              // Index value of this configuration
    0,                              // Configuration string index

    USB_ATTRIBUTE_DEFAULT | USB_ATTRIBUTE_SELF_POWERED, // Attributes, see usb_device.h
    50,                                         // Max power consumption (2X mA)

    /* Interface Descriptor */

    0x09,                       // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,   // INTERFACE descriptor type
    0,                          // Interface Number
    0,                          // Alternate Setting Number
    2,                          // Number of endpoints in this interface
    USB_HID_CLASS_CODE,         // Class code

    USB_HID_SUBCLASS_CODE_BOOT_INTERFACE_SUBCLASS,  // Subclass code
    USB_HID_PROTOCOL_CODE_KEYBOARD,                 // Keyboard Protocol
    0,                                              // Interface string index

    /* HID Class-Specific Descriptor */

    0x09,                           // Size of this descriptor in bytes
    USB_HID_DESCRIPTOR_TYPES_HID,   // HID descriptor type

    0x11,0x01,              // HID Spec Release Number in BCD format (1.11)
    0x00,                   // Country Code (0x00 for Not supported)
    HID_NUM_OF_DSC,         // Number of class descriptors, see usbcfg.h

    USB_HID_DESCRIPTOR_TYPES_REPORT,// Report descriptor type
    0x3F,0x00,                      // Size of the report descriptor

    /* Endpoint Descriptor */

    0x07,
    USB_DESCRIPTOR_ENDPOINT,        // Endpoint Descriptor
    HID_EP | USB_EP_DIRECTION_IN,       // EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    // Attributes
    0x40,0x00,                      // size
    0x01,                           // Interval

    /* Endpoint Descriptor */

    0x07,
    USB_DESCRIPTOR_ENDPOINT,        // Endpoint Descriptor
    HID_EP | USB_EP_DIRECTION_OUT,      // EndpointAddress
    USB_TRANSFER_TYPE_INTERRUPT,    // Attributes
    0x40,0x00,                      // size
    0x01,                           // Interval
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
{'H','I','D',' ','k','e','y','b','o','r','d',' ',
'D','e','m','o'
}};

//Class specific descriptor - HID Report descriptor

const uint8_t hid_rpt01[]=
{
   0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
   0x09, 0x06,                    // USAGE (Keyboard)
   0xa1, 0x01,                    // COLLECTION (Application)
   0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
   0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
   0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
   0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
   0x75, 0x01,                    //   REPORT_SIZE (1)
   0x95, 0x08,                    //   REPORT_COUNT (8)
   0x81, 0x02,                    //   INPUT (Data,Var,Abs)
   0x95, 0x01,                    //   REPORT_COUNT (1)
   0x75, 0x08,                    //   REPORT_SIZE (8)
   0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
   0x95, 0x05,                    //   REPORT_COUNT (5)
   0x75, 0x01,                    //   REPORT_SIZE (1)
   0x05, 0x08,                    //   USAGE_PAGE (LEDs)
   0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
   0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
   0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
   0x95, 0x01,                    //   REPORT_COUNT (1)
   0x75, 0x03,                    //   REPORT_SIZE (3)
   0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
   0x95, 0x06,                    //   REPORT_COUNT (6)
   0x75, 0x08,                    //   REPORT_SIZE (8)
   0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
   0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
   0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
   0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
   0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
   0xc0                           // End Collection
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
   /* High speed device desc is supported*/
   (uint8_t *)&device_dsc,
   /*Total number of high speed configurations available */
   1,
   /* Pointer to array of high speed configurations descriptors. */
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

/* HID Instance Init structure */
USB_DEVICE_HID_INIT hidInit =
{
   .hidReportDescriptor = (void*)&hid_rpt01,
   .hidReportDescriptorSize = sizeof(hid_rpt01),
   .queueSizeReportReceive = 1,
   .queueSizeReportSend = 1
};

// Used by the device layer.
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

