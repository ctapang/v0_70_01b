/*******************************************************************************
  USB Device Chapter-9 Definition

  Company:
    Microchip Technology Inc.

  File Name:
    usb_chapter_9.h

  Summary:
    USB device chapter-9 definitions header.

  Description:
    This file defines data structures, constants, and macros that are used 
    to support the "USB Device Framework" described in Chapter 9 of the
    USB 2.0 specification.

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

#ifndef _USB_CHAPTER_9_H
#define _USB_CHAPTER_9_H

// *****************************************************************************
/* A generic structure for accessing the word in byte and value format.

  Summary:
    

  Description:
   

  Remarks:
    
*/

typedef union
{
    uint16_t Val;
    uint8_t v[2];
    struct
    {
        uint8_t LB;
        uint8_t HB;
    } byte;
    
} USB_WORD_VAL;


// *****************************************************************************
/* Descriptor header structure.

  Summary:
   Descriptor header structure.

  Description:
   Any USB descriptor starts with "size" and "descriptor type".
   This structure is used by USB device layer to determine the
   size and type of a descriptor.

  Remarks:
    Note that this structure may need to be packed, or even accessed as bytes, 
    to properly access the correct fields when used on some device architectures.
    
*/

typedef struct __attribute__ ((packed))
{
    uint8_t size;
    uint8_t descType;    
    
}USB_DESCRIPTOR_HEADER;    


// *****************************************************************************
/* Configuration descriptor structure

  Summary:
   Structure that contains all configuration descriptor fields
   as described in Table 9-10 of USB 2.0 spec.

  Description:
      

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures.
*/

typedef struct __attribute__ ((packed))
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
}USB_CONFIGURATION_DESCRIPTOR;    


// *****************************************************************************
/* Interface descriptor structure

  Summary:
   Structure that contains all interface descriptor fields
   as described in Table 9-12 of USB 2.0 spec.

  Description:
    

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures. 
    
*/
    
typedef struct __attribute__ ((packed))
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndPoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
}USB_INTERFACE_DESCRIPTOR;    


// *****************************************************************************
/* Endpoint descriptor structure

  Summary:
   Structure that contains all endpoint descriptor fields
   as described in Table 9-13 of USB 2.0 spec.

  Description:
    

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures.
    
*/

typedef struct __attribute__ ((packed))
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    union 
    {
          struct __attribute__ ((packed))
         {
            unsigned epAddress:4;
            unsigned :3;
            unsigned dirn: 1;
          };
        uint8_t bEndpointAddress;
    }; 
    
    union
    {        
        struct __attribute__ ((packed))
        {
            unsigned transferType:2;
            unsigned syncType:2;
            unsigned usageType:2;
            unsigned :2;
        };
        uint8_t bmAttributes;
    };
    
    union
    {
        struct __attribute__ ((packed))
        {
            unsigned packetSize:14;
            unsigned addTransaction:2;
        };       
        
        uint16_t wMaxPacketSize;       
    };               
    
    
    uint8_t  bInterval;
}USB_ENDPOINT_DESCRIPTOR;


// *****************************************************************************
/* Setup packet structure

  Summary:
   This structure contains members of the "standard setup" as requested by
   the USB host.
   
  Description:
    

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures. 
*/

typedef union __attribute__ ((packed))
{
    /** Standard Device Requests ***********************************/
    struct __attribute__ ((packed))
    {
        uint8_t bmRequestType; //from table 9-2 of USB 2.0 spec
        uint8_t bRequest; //from table 9-2 of USB 2.0 spec
        uint16_t wValue; //from table 9-2 of USB 2.0 spec
        uint16_t wIndex; //from table 9-2 of USB 2.0 spec
        uint16_t wLength; //from table 9-2 of USB 2.0 spec
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        USB_WORD_VAL W_Value; //from table 9-2 of USB 2.0 spec, allows byte/bitwise access
        USB_WORD_VAL W_Index; //from table 9-2 of USB 2.0 spec, allows byte/bitwise access
        USB_WORD_VAL W_Length; //from table 9-2 of USB 2.0 spec, allows byte/bitwise access
    };
    struct __attribute__ ((packed))
    {
        unsigned Recipient:5;   //Device,Interface,Endpoint,Other
        unsigned RequestType:2; //Standard,Class,Vendor,Reserved
        unsigned DataDir:1;     //Host-to-device,Device-to-host
        unsigned :8;
        uint8_t bFeature;          //DEVICE_REMOTE_WAKEUP,ENDPOINT_HALT
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        union                           // offset   description
        {                               // ------   ------------------------
            uint8_t bmRequestType;         //   0      Bit-map of request type
            struct
            {
                uint8_t    recipient:  5;  //          Recipient of the request
                uint8_t    type:       2;  //          Type of request
                uint8_t    direction:  1;  //          Direction of data X-fer
            };
        }requestInfo;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        uint8_t bDscIndex;         //For Configuration and String DSC Only
        uint8_t bDescriptorType;          //Device,Configuration,String
        uint16_t wLangID;           //Language ID
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        uint8_t bDevADR;       //Device Address 0-127
        uint8_t bDevADRH;          //Must equal zero
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        uint8_t bConfigurationValue;         //Configuration Value 0-255
        uint8_t bCfgRSD;           //Must equal zero (Reserved)
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        uint8_t bAltID;            //Alternate Setting Value 0-255
        uint8_t bAltID_H;          //Must equal zero
        uint8_t bIntfID;           //Interface Number Value 0-255
        uint8_t bIntfID_H;         //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        uint8_t bEPID;             //Endpoint ID (Number & Direction)
        uint8_t bEPID_H;           //Must equal zero
        unsigned :8;
        unsigned :8;
    };
    struct __attribute__ ((packed))
    {
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned :8;
        unsigned EPNum:4;       //Endpoint Number 0-15
        unsigned :3;
        unsigned EPDir:1;       //Endpoint Direction: 0-OUT, 1-IN
        unsigned :8;
        unsigned :8;
        unsigned :8;
    };

    /** End: Standard Device Requests ******************************/

} USB_SETUP_PACKET ;


// *****************************************************************************
/* Standard device descriptor

  Summary:
    Structure that contains all device descriptor fields.

  Description:
    This structure contains all device descriptor fields as described in Table 9-8 
    of the USB 2.0 spec.

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures. 
    
*/

typedef struct __attribute__ ((packed)) _USB_DEVICE_DESCRIPTOR_
{
    uint8_t bLength;               // Length of this descriptor.
    uint8_t bDescriptorType;       // DEVICE descriptor type (USB_DESCRIPTOR_DEVICE).
    uint16_t bcdUSB;                // USB Spec Release Number (BCD).
    uint8_t bDeviceClass;          // Class code (assigned by the USB-IF). 0xFF-Vendor specific.
    uint8_t bDeviceSubClass;       // Subclass code (assigned by the USB-IF).
    uint8_t bDeviceProtocol;       // Protocol code (assigned by the USB-IF). 0xFF-Vendor specific.
    uint8_t bMaxPacketSize0;       // Maximum packet size for endpoint 0.
    uint16_t idVendor;              // Vendor ID (assigned by the USB-IF).
    uint16_t idProduct;             // Product ID (assigned by the manufacturer).
    uint16_t bcdDevice;             // Device release number (BCD).
    uint8_t iManufacturer;         // Index of String Descriptor describing the manufacturer.
    uint8_t iProduct;              // Index of String Descriptor describing the product.
    uint8_t iSerialNumber;         // Index of String Descriptor with the device's serial number.
    uint8_t bNumConfigurations;    // Number of possible configurations.
} USB_DEVICE_DESCRIPTOR;


// *****************************************************************************
/* Device_Qualifier

  Summary:
    Structure that contains all device_qualifier descriptor fields.

  Description:
    This structure contains all device_qualifier descriptor fields
    as described in Table 9-9 of USB 2.0 spec.

  Remarks:
    Note that this structure may need to be packed, or even accessed 
    as bytes, to properly access the correct fields when used on some device 
    architectures. 
    
*/

typedef struct __attribute__ ((packed)) _USB_DEVICE_QUALIFIER_
{
    uint8_t bLength;               // Length of this descriptor.
    uint8_t bDescriptorType;       // DEVICE descriptor type (USB_DESCRIPTOR_DEVICE).
    uint16_t bcdUSB;                // USB Spec Release Number (BCD).
    uint8_t bDeviceClass;          // Class code (assigned by the USB-IF). 0xFF-Vendor specific.
    uint8_t bDeviceSubClass;       // Subclass code (assigned by the USB-IF).
    uint8_t bDeviceProtocol;       // Protocol code (assigned by the USB-IF). 0xFF-Vendor specific.
    uint8_t bMaxPacketSize0;       // Maximum packet size for endpoint 0.
    uint8_t bNumConfigurations;    // Number of possible configurations.
    uint8_t bReserved;             // Reserved for future use.
} USB_DEVICE_QUALIFIER;


// *****************************************************************************
/* Descriptor types

  Summary:
    These definitions provide "descriptor type" constants.

  Description:
    The "descriptor types" are listed in table 9-5 of USB 2.0 spec.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define USB_DESCRIPTOR_DEVICE           0x01    // bDescriptorType for a Device Descriptor.
#define USB_DESCRIPTOR_CONFIGURATION    0x02    // bDescriptorType for a Configuration Descriptor.
#define USB_DESCRIPTOR_STRING           0x03    // bDescriptorType for a String Descriptor.
#define USB_DESCRIPTOR_INTERFACE        0x04    // bDescriptorType for an Interface Descriptor.
#define USB_DESCRIPTOR_ENDPOINT         0x05    // bDescriptorType for an Endpoint Descriptor.
#define USB_DESCRIPTOR_DEVICE_QUALIFIER 0x06    // bDescriptorType for a Device Qualifier.
#define USB_DESCRIPTOR_OTHER_SPEED      0x07    // bDescriptorType for a Other Speed Configuration.
#define USB_DESCRIPTOR_INTERFACE_POWER  0x08    // bDescriptorType for Interface Power.
#define USB_DESCRIPTOR_OTG              0x09    // bDescriptorType for an OTG Descriptor.


// *****************************************************************************
/* Standard device requests

  Summary:
    These definitions provide constant values of the "bRequest" field of
    standard device request.

  Description:
    The "standard device requests" are listed in table 9-3 of USB 2.0 spec.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define USB_REQUEST_GET_STATUS                  0       // Standard Device Request - GET STATUS
#define USB_REQUEST_CLEAR_FEATURE               1       // Standard Device Request - CLEAR FEATURE
#define USB_REQUEST_SET_FEATURE                 3       // Standard Device Request - SET FEATURE
#define USB_REQUEST_SET_ADDRESS                 5       // Standard Device Request - SET ADDRESS
#define USB_REQUEST_GET_DESCRIPTOR              6       // Standard Device Request - GET DESCRIPTOR
#define USB_REQUEST_SET_DESCRIPTOR              7       // Standard Device Request - SET DESCRIPTOR
#define USB_REQUEST_GET_CONFIGURATION           8       // Standard Device Request - GET CONFIGURATION
#define USB_REQUEST_SET_CONFIGURATION           9       // Standard Device Request - SET CONFIGURATION
#define USB_REQUEST_GET_INTERFACE               10      // Standard Device Request - GET INTERFACE
#define USB_REQUEST_SET_INTERFACE               11      // Standard Device Request - SET INTERFACE
#define USB_REQUEST_SYNCH_FRAME                 12      // Standard Device Request - SYNCH FRAME


// *****************************************************************************
/* Characteristics of request.

  Summary:
    Characteristics of "bmRequestType" field of setup data as described in
    Table 9-2 of USB 2.0 spec.

  Description:
    ORing these constants with "bmRequestType" field gives characteristics of the
    setup data.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define USB_SETUP_DIRN_HOST_TO_DEVICE               0x00    // Setup request direction is Host -> Device
#define USB_SETUP_DIRN_DEVICE_TO_HOST               0x80    // Setup request direction is Device -> Host
#define USB_SETUP_TYPE_STANDARD                     0x00    // Setup request type is "Standard"
#define USB_SETUP_TYPE_CLASS                        0x20    // Setup request type is "Class"
#define USB_SETUP_TYPE_VENDOR                       0x40    // Setup request type is "Vendor"
#define USB_SETUP_TYPE_RESERVED                     0x60    // Reserved
#define USB_SETUP_RECIPIENT_DEVICE                  0x00    // Recipient is Device
#define USB_SETUP_RECIPIENT_INTERFACE               0x01    // Recipient is interface
#define USB_SETUP_RECIPIENT_ENDPOINT                0x02    // Recipient is endpoint
#define USB_SETUP_RECIPIENT_OTHER                   0x03    // Recipient is other


// *****************************************************************************
/* Standard feature selectors.

  Summary:
    Standard feature selectors as described in Table 9-2 of USB 2.0 spec.

  Description:
    

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/
#define USB_FEATURE_SELECTOR_ENDPOINT_HALT                          0
#define USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP                   1
#define USB_FEATURE_SELECTOR_DEVICE_TEST_MODE                       2


// *****************************************************************************
/*  bmAttributes field of standard configuration descriptor.

  Summary:
    Characteristics of "bmAttributes" field of standard configuration descriptor
    as described in Table 9-10 of USB 2.0 spec.

  Description:
    ORing these constants with "bmAttributes" field gives configuration
    characteristics of standard configuration descriptor.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define USB_ATTRIBUTE_DEFAULT                       0x80  // Reserved (set to one)
#define USB_ATTRIBUTE_SELF_POWERED                  0x40  // Self powered
#define USB_ATTRIBUTE_REMOTE_WAKEUP                 0x20  // Remote wakeup


// *****************************************************************************
/*  Endpoint direction for standard endpoint descriptor.

  Summary:
    Specifies the direction for the endpoint.

  Description:
    OR-ing these constants with "bEndpointAddress" field specifies the direction
    for the endpoint. Refer to Table 9-13 of USB 2.0 spec.
 
  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/

#define USB_EP_DIRECTION_IN                     0x80    // IN direction
#define USB_EP_DIRECTION_OUT                    0x00    // OUT direction


// *****************************************************************************
/*  bmAttributes for standard endpoint descriptor.

  Summary:
    Defines the attributes of the endpoint.

  Description:
    ORing these constants with "bmAttributes" field defines the attributes
    of the endpoint. Refer to Table 9-13 of USB 2.0 spec.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.
*/
/* Transfer type (Bits 1..0 of bmAttributes field inside endpoint descriptor)*/

typedef enum
{
    USB_TRANSFER_TYPE_CONTROL       = 0x00,     // Control transfer
    USB_TRANSFER_TYPE_ISOCHRONOUS   = 0x01,     // Isochronous
    USB_TRANSFER_TYPE_BULK          = 0x02,     // Bulk
    USB_TRANSFER_TYPE_INTERRUPT     = 0x03      // Interrupt
}
USB_TRANSFER_TYPE;

/* Synchonization type (Bits 3..2 of bmAttributes field inside endpoint descriptor)*/
#define USB_SYNCH_TYPE_NO_SYNCH                 0x00    //No synchronisation
#define USB_SYNCH_TYPE_ASYNCHRONOUS             0x04    // Asynchonous
#define USB_SYNCH_TYPE_ADAPTIVE                 0x08    //
#define USB_SYNCH_TYPE_SYNCHRONOUS              0x0C

/* Usage type (Bits 5..4 of bmAttributes field inside endpoint descriptor*/
#define USB_USAGE_DATA_ENDPOINT                 0x00
#define USB_USAGE_FEEDBACK_ENDPOINT             0x10
#define USB_USAGE_IMPLICIT_FEEDBACK_DATA_EP     0x20
#define USB_USAGE_RESERVED                      0x30




#endif
