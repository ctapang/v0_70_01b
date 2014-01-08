/*******************************************************************************
 USB DEVICE Audio Speaker Demo Configuration file.

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.c

  Summary:
    Top-level configuration file for the USB DEVICE Audio Speaker Demo application for
    the PIC32 audio accessory board.

  Description:
    This file contains the USB descriptors and AUDIO calss specific data that
	needs to be provided by the application.
*******************************************************************************/
// DOM-IGNORE-BEGIN
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

/* Device Descriptor */
const USB_DEVICE_DESCRIPTOR device_dsc=
{
   sizeof(USB_DEVICE_DESCRIPTOR),    // Size of this descriptor in bytes
   USB_DESCRIPTOR_DEVICE, 		               // DEVICE descriptor type
   0x0110,                 // USB Spec Release Number in BCD format
   0x00,                   // Class Code
   0x00,                   // Subclass code
   0x00,                   // Protocol code
   USB_DEVICE_EP0_BUFFER_SIZE ,      // Max packet size for EP0
   0x04D8,                 // Vendor ID
   0x0064,                 // Product ID
   0x0100,                 // Device release number in BCD format
   0x01,                   // Manufacturer string index
   0x02,                   // Product string index
   0x00,                   // Device serial number string index
   0x01                    // Number of possible configurations
};

/* Configuration 1 Descriptor */
const uint8_t configDescriptor1[] ={
   /* USB Speaker Configuration Descriptor */
   0x09,							 // Size of this descriptor in bytes
   USB_DESCRIPTOR_CONFIGURATION,	 // CONFIGURATION descriptor type
   0x6E,0x00,						 // Total length of data for this cfg
   0x02,							 // Number of interfaces in this cfg
   0x01,							 // Index value of this configuration
   0x00,							 // Configuration string index
   USB_ATTRIBUTE_DEFAULT |USB_ATTRIBUTE_SELF_POWERED,  // Attributes, see usb_chapter_9.h
   0xFA,						     // Max power consumption (2X mA)

   /* USB Speaker Standard AC Interface Descriptor	*/
   0x09,							 // Size of this descriptor in bytes (bLength)
   USB_DESCRIPTOR_INTERFACE,      	 // INTERFACE descriptor type (bDescriptorType)
   USB_DEVICE_AUDIO_CONTROL_INTERFACE_ID,		 // Interface Number  (bInterfaceNumber)
   0x00,						 	 // Alternate Setting Number (bAlternateSetting)
   0x00,							 // Number of endpoints in this intf (bNumEndpoints)
   USB_AUDIO_INTERFACE_CLASS_CODE_AUDIO,					 // Class code  (bInterfaceClass)
   USB_AUDIO_ISC_AUDIOCONTROL,					 // Subclass code (bInterfaceSubclass)
   USB_AUDIO_IPC_PR_PROTOCOL_UNDEFINED,							 // Protocol code  (bInterfaceProtocol)
   0x00,						     // Interface string index (iInterface)

   /* USB Speaker Class-specific AC Interface Descriptor  */
	0x09,							 // Size of this descriptor in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,					 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSACIDS_HEADER,							 // HEADER descriptor subtype 	(bDescriptorSubtype)
	0x00,0x01,						 // Audio Device compliant to the USB Audio specification version 1.00 (bcdADC)
	0x28,0x00,						 // Total number of bytes returned for the class-specific AudioControl interface descriptor. (wTotalLength)
								  	 // Includes the combined length of this descriptor header and all Unit and Terminal descriptors.
	0x01,						 	 // The number of AudioStreaming interfaces in the Audio Interface Collection to which this AudioControl interface belongs  (bInCollection)
	0x01,							 // AudioStreaming interface 1 belongs to this AudioControl interface. (baInterfaceNr(1))

	/* USB Speaker Input Terminal Descriptor */
	0x0C,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,	    			 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSACIDS_INPUT_TERMINAL,					 // INPUT_TERMINAL descriptor subtype (bDescriptorSubtype)
	APP_ID_INPUT_TERMINAL,				 // ID of this Terminal.(bTerminalID)
	0x01,0x01,						 // (wTerminalType)
	0x00,							 // No association (bAssocTerminal)
	0x02,							 // Two Channels (bNrChannels)
	0x03,0x00,						 // (wChannelConfig)
	0x00,							 // Unused.(iChannelNames)
	0x00,							 // Unused. (iTerminal)

	/* USB Speaker Feature Unit Descriptor */
	0x0A,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,					 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSACIDS_FEATURE_UNIT,					 // FEATURE_UNIT  descriptor subtype (bDescriptorSubtype)
	APP_ID_FEATURE_UNIT,				 // ID of this Unit ( bUnitID  ).
	APP_ID_INPUT_TERMINAL,				 // Input terminal is connected to this unit(bSourceID)
	0x01,							 // (bControlSize) //was 0x03
	0x01,                                           // (bmaControls(0)) Controls for Master Channel
        0x00,                                           // (bmaControls(1)) Controls for Channel 1
        0x00,                                           // (bmaControls(2)) Controls for Channel 2
	0x00,							 //  iFeature

	/* USB Speaker Output Terminal Descriptor */
	0x09,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,					 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSACIDS_OUTPUT_TERMINAL,				 // OUTPUT_TERMINAL  descriptor subtype (bDescriptorSubtype)
	APP_ID_OUTPUT_TERMINAL,				 // ID of this Terminal.(bTerminalID)
	0x01,0x03,						 // (wTerminalType)See USB Audio Terminal Types.
	0x00,							 // No association (bAssocTerminal)
	APP_ID_FEATURE_UNIT,				 // (bSourceID)
	0x00,							 // Unused. (iTerminal)

	/* USB Speaker Standard AS Interface Descriptor (Alt. Set. 0) */
	0x09,							 // Size of the descriptor, in bytes (bLength)
	USB_DESCRIPTOR_INTERFACE,      	 // INTERFACE descriptor type (bDescriptorType)
	USB_DEVICE_AUDIO_STREAMING_INTERFACE_ID,	 // Interface Number  (bInterfaceNumber)
	0x00,							 // Alternate Setting Number (bAlternateSetting)
	0x00,							 // Number of endpoints in this intf (bNumEndpoints)
	USB_AUDIO_INTERFACE_CLASS_CODE_AUDIO,					 // Class code  (bInterfaceClass)
	USB_AUDIO_ISC_AUDIOSTREAMING,					 // Subclass code (bInterfaceSubclass)
	0x00,							 // Protocol code  (bInterfaceProtocol)
	0x00,							 // Interface string index (iInterface)

	/* USB Speaker Standard AS Interface Descriptor (Alt. Set. 1) */
	0x09,							 // Size of the descriptor, in bytes (bLength)
	USB_DESCRIPTOR_INTERFACE,      	 // INTERFACE descriptor type (bDescriptorType)
	USB_DEVICE_AUDIO_STREAMING_INTERFACE_ID,	 // Interface Number  (bInterfaceNumber)
	0x01,							 // Alternate Setting Number (bAlternateSetting)
	0x01,							 // Number of endpoints in this intf (bNumEndpoints)
	USB_AUDIO_INTERFACE_CLASS_CODE_AUDIO,	    			 // Class code  (bInterfaceClass)
	USB_AUDIO_ISC_AUDIOSTREAMING,					 // Subclass code (bInterfaceSubclass)
	0x00,							 // Protocol code  (bInterfaceProtocol)
	0x00,							 // Interface string index (iInterface)

	/*  USB Speaker Class-specific AS General Interface Descriptor */
	0x07,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,					 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSASIDS_AS_GENERAL,						 // GENERAL subtype (bDescriptorSubtype)
	APP_ID_INPUT_TERMINAL,							 // Unit ID of the Output Terminal.(bTerminalLink)
	0x01,							 // Interface delay. (bDelay)
	0x01,0x00,						 // PCM Format (wFormatTag)

	/*  USB Speaker Type 1 Format Type Descriptor */
	0x0B,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_INTERFACE,					 // CS_INTERFACE Descriptor Type (bDescriptorType)
	USB_AUDIO_CSASIDS_FORMAT_TYPE ,					 // FORMAT_TYPE subtype. (bDescriptorSubtype)
	0x01,							 // FORMAT_TYPE_1. (bFormatType)
	0x02,							 // two channel.(bNrChannels)
	0x02,							 // 2 byte per audio subframe.(bSubFrameSize)
	0x10,							 // 16 bits per sample.(bBitResolution)
	0x01,							 // One frequency supported. (bSamFreqType)
	0x80,0xBB,0x00,				 	 // Sampling Frequency = 48000 Hz(tSamFreq)

	/*  USB Speaker Standard Endpoint Descriptor */
	0x09,							 // Size of the descriptor, in bytes (bLength)
	USB_DESCRIPTOR_ENDPOINT,		 // ENDPOINT descriptor (bDescriptorType)
	0x01,							 // OUT Endpoint 1. (bEndpointAddress)
	0x09,							 // ?(bmAttributes) Isochronous, Asynchronized, data endpoint
	(192),0x00,						 // ?(wMaxPacketSize) //48 * 4
	0x01,							 // One packet per frame.(bInterval)
	0x00,							 // Unused. (bRefresh)
	0x00,							 // Unused. (bSynchAddress)

	/* USB Speaker Class-specific Isoc. Audio Data Endpoint Descriptor*/
	0x07,							 // Size of the descriptor, in bytes (bLength)
	USB_AUDIO_CSDT_CS_ENDPOINT,					 // CS_ENDPOINT Descriptor Type (bDescriptorType)
	USB_AUDIO_CSEDS_EP_GENERAL,							 // GENERAL subtype. (bDescriptorSubtype)
	0x00,							 // No sampling frequency control, no pitch control, no packet padding.(bmAttributes)
	0x00,							 // Unused. (bLockDelayUnits)
	0x00,0x00						 // Unused. (wLockDelay)


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
const struct{uint8_t bLength;uint8_t bDscType;uint16_t string[23];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'I','S','P',' ','U','S','B',' ','S','p','e','a','k','e','r',' ','E','x','a','m','p','l','e'}};

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

const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1] = {

    {
     // Speed
     .speed = USB_SPEED_FULL|USB_SPEED_HIGH,
	 
     // Configuration value
     .configurationValue = 1,

    //interfaceNumber
    .interfaceNumber = 0,

    //number of interfaces
    .numberOfInterfaces = 2,

    // function driver index
    .funcDriverIndex = 0,

     // function driver init
     .funcDriverInit = NULL,//&audioInit ,

     // USB Audio function data exposed to device layer
     .driver = &audioFuncDriver
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

