/*******************************************************************************
  USB CDC class definitions

  Company:
    Microchip Technology Inc.

  File Name:
    usb_audio.h

  Summary:
    USB Audio class definitions

  Description:
    This file describes the Audio v1.0 class specific definitions.
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

#ifndef _USB_AUDIO_H_
#define _USB_AUDIO_H_

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************



#define  USB_AUDIO_INTERFACE_CLASS_CODE_AUDIO 0x01

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Audio Interface subclass codes

  Summary:
    Identifies the subclass codes for Audio interface. 

  Description:
    This enumeration identifies the possible subclass codes for 
    audio interface. 

  Remarks:
    The "ISC" in the enumeration member names is an acronym for Interface 
    Subclass Code.
*/


typedef enum
{
    USB_AUDIO_ISC_SUBCLASS_UNDEFINED    = 0x00,
    USB_AUDIO_ISC_AUDIOCONTROL          = 0x01,
    USB_AUDIO_ISC_AUDIOSTREAMING        = 0x02,
    USB_AUDIO_ISC_MIDISTREAMING         = 0x03

}USB_AUDIO_INTERFACE_SUBCLASS_CODES; 

// *****************************************************************************
/* Audio Interface Protocol codes

  Summary:
    Identifies the protocol codes for Audio interface. 

  Description:
    This enumeration identifies the possible protocol codes for 
    audio interface

  Remarks:
    The "PC" in the enumeration memeber names is an acronym for Interface 
    Protocol Code.
*/

typedef enum
{
    USB_AUDIO_IPC_PR_PROTOCOL_UNDEFINED    = 0x0

}USB_AUDIO_INTERFACE_PROTOCOL_CODES;

// *****************************************************************************
/* Audio Class Specific Descriptor Types

  Summary:
    Identifies the Audio class specific descriptor types for Audio. 

  Description:
    This enumeration identifies the Audio Class specific descriptor types. 

  Remarks:
    The "CSDT" in the enumeration member names is an acronym for Class Specific
    Descriptor Type.
*/
typedef enum
{
    USB_AUDIO_CSDT_CS_UNDEFINED       = 0x20,
    USB_AUDIO_CSDT_CS_DEVICE          = 0x21,
    USB_AUDIO_CSDT_CS_CONFIGURATION   = 0x22,
    USB_AUDIO_CSDT_CS_STRING          = 0x23,
    USB_AUDIO_CSDT_CS_INTERFACE       = 0x24,
    USB_AUDIO_CSDT_CS_ENDPOINT        = 0x25

}USB_AUDIO_CLASS_SPECIFIC_DESCRIPTOR_TYPES;

// *****************************************************************************
/* Audio Class Specfic AC Interface Descriptor Subtypes

  Summary:
    Identifies the Audio Class Specific AC Interface Descriptor Subtypes.

  Description:
    This enumeration identifies the possible Audio Class Specific AC Interface
    Descriptor Subtypes.

  Remarks:
    The "CSACIDS" in the enumeration member names is an acronym for Class Specific
    AC Interface Descriptor.
*/
typedef enum
{
    USB_AUDIO_CSACIDS_PTOR_UNDEFINED    = 0x00,
    USB_AUDIO_CSACIDS_HEADER                     = 0x01,
    USB_AUDIO_CSACIDS_INPUT_TERMINAL             = 0x02,
    USB_AUDIO_CSACIDS_OUTPUT_TERMINAL            = 0x03,
    USB_AUDIO_CSACIDS_MIXER_UNIT                 = 0x04,
    USB_AUDIO_CSACIDS_SELECTOR_UNIT              = 0x05,
    USB_AUDIO_CSACIDS_FEATURE_UNIT               = 0x06,
    USB_AUDIO_CSACIDS_PROCESSING_UNIT            = 0x07,
    USB_AUDIO_CSACIDS_EXTENSION_UNIT             = 0x08,

}USB_AUDIO_CLASS_SPECIFIC_AC_INTERFACE_DESCRIPTOR_SUBTYPES;

// *****************************************************************************
/* Audio Class Specific AS Interface Descriptor Subtypes

  Summary:
    Identifies the Audio Class Specific AS Interface Descriptor Subtypes. 

  Description:
    This enumeration identifies the possible Audio Class Specific AS Interface 
    Descriptor Subtypes. 

  Remarks:
    The "CSASID" in the enumeration member names is an acronym for Class Specific
    AS Interface Descriptor.
*/
typedef enum
{
    USB_AUDIO_CSASIDS_AS_DESCRIPTOR_UNDEFINED    = 0x00,
    USB_AUDIO_CSASIDS_AS_GENERAL                 = 0x01,
    USB_AUDIO_CSASIDS_FORMAT_TYPE                = 0x02,
    USB_AUDIO_CSASIDS_FORMAT_SPECIFIC            = 0x03

}USB_AUDIO_CLASS_SPECIFIC_AS_INTERFACE_DESCRIPTOR_SUBTYPES;

// *****************************************************************************
/* Audio Processing Unit Process Types

  Summary:
    Identifies the Audio Process Unit Process Types.

  Description:
    This enumeration identifies the possible Audio Process Unit Process types. 

  Remarks:
    The "PUPT" in the enumeration member names is an acronym for Processing Unit
    Process Type.
*/
typedef enum
{
    USB_AUDIO_PUPT_UNDEFINED                            = 0x00,
    USB_AUDIO_PUPT_UP_DOWNMIX_PROCESS                   = 0x01,
    USB_AUDIO_PUPT_DOLBY_PROLOGIC_PROCESS               = 0x02,
    USB_AUDIO_PUPT_3D_STEREO_EXTENDER_PROCESS           = 0x03,
    USB_AUDIO_PUPT_REVERBERATION_PROCESS                = 0x04,
    USB_AUDIO_PUPT_CHORUS_PROCESS                       = 0x05,   
    USB_AUDIO_PUPT_DYN_RANGE_COMP_PROCESS               = 0x06

}USB_AUDIO_PROCESSING_UNIT_PROCESS_TYPES;

// *****************************************************************************
/* Audio Class Specific Endpoint Descriptor Subtypes.

  Summary:
    Identifies the Audio Class Specific Endpoint Descriptor Subtypes.

  Description:
    This enumeration identifies the possible Audio Class Specific Endpoint 
    Descriptor Subtypes.

  Remarks:
    The "CSEDS" in the enumeration member names is an acronym for Class Specific
    Endpoint Descriptor Subtype.
*/
typedef enum
{
    USB_AUDIO_CSEDS_DESCRIPTOR_UNDEFINED   = 0x00,
    USB_AUDIO_CSEDS_EP_GENERAL            = 0x01

}USB_AUDIO_CLASS_SPECIFIC_ENDPOINT_DESCRIPTOR_SUBTYPES;

// *****************************************************************************
/* Audio Class Specific Request Codes.

  Summary:
    Identifies the Audio Class Specific Request Codes.

  Description:
    This enumeration identifies the possible Audio Class Specific Request codes.

  Remarks:
    The "CSRC" in the enumeration member names is an acronym for Class Specific
    Request Code.
*/

typedef enum
{
    USB_AUDIO_CSRC_REQUEST_CODE_UNDEFINED = 0x00,
    USB_AUDIO_CSRC_SET_CUR   = 0x01,
    USB_AUDIO_CSRC_GET_CUR   = 0x81,
    USB_AUDIO_CSRC_SET_MIN   = 0x02,
    USB_AUDIO_CSRC_GET_MIN   = 0x82,
    USB_AUDIO_CSRC_SET_MAX   = 0x03,
    USB_AUDIO_CSRC_GET_MAX   = 0x83,
    USB_AUDIO_CSRC_SET_RES   = 0x04,
    USB_AUDIO_CSRC_GET_RES   = 0x84,
    USB_AUDIO_CSRC_SET_MEM   = 0x05,
    USB_AUDIO_CSRC_GET_MEM   = 0x85,
    USB_AUDIO_CSRC_GET_STAT  = 0xFF

}USB_AUDIO_CLASS_SPECIFIC_REQUEST_CODES;

// *****************************************************************************
/* Audio Terminal Control Selectors.

  Summary:
    Identifies the Audio Terminal Control Selectors.

  Description:
    This enumeration identifies the possible Audio Terminal Control Selectors.

  Remarks:
    The "TCS" in the enumeration member names is an acronym for Terminal Control 
    Selector.
*/
typedef enum
{
    USB_AUDIO_TCS_TE_CONTROL_UNDEFINED = 0x00,
    USB_AUDIO_TCS_COPY_PROTECT_CONTROL = 0x01

}USB_AUDIO_TERMINAL_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Feature Unit Control Selector.

  Summary:
    Identifies the Audio Feature Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Feature Unit Control Selectors.

  Remarks:
    The "FCS" in the enumeration member names is an acronym for Feature unit Control
    Selector.
*/
typedef enum
{
    USB_AUDIO_FCS_FU_CONTROL_UNDEFINED        = 0x00,
    USB_AUDIO_FCS_MUTE_CONTROL                = 0x01,
    USB_AUDIO_FCS_VOLUME_CONTROL              = 0x02,
    USB_AUDIO_FCS_BASS_CONTROL                = 0x03,
    USB_AUDIO_FCS_MID_CONTROL                 = 0x04,
    USB_AUDIO_FCS_TREBLE_CONTROL              = 0x05,
    USB_AUDIO_FCS_GRAPHIC_EQUALIZER_CONTROL   = 0x06,
    USB_AUDIO_FCS_AUTOMATIC_GAIN_CONTROL      = 0x07,
    USB_AUDIO_FCS_DELAY_CONTROL               = 0x08,
    USB_AUDIO_FCS_BASS_BOOST_CONTROL          = 0x09,
    USB_AUDIO_FCS_LOUDNESS_CONTROL            = 0x0A

}USB_AUDIO_FEATURE_UNIT_CONTROL_SELECTORS;    

// *****************************************************************************
/* Audio Up/Down-mix Processing Unit Control Selector.

  Summary:
    Identifies the Audio Up/Down-mix Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Up/Down-mix Processing Unit 
    Control Selectors.

  Remarks:
    The "UDMPUCS" in the enumeration member names is an acronym for Up Down Mix
    Processing Unit Control Selector.
*/
typedef enum
{
    USB_AUDIO_UDMPUCS_UD_CONTROL_UNDEFINED     = 0x00,
    USB_AUDIO_UDMPUCS_UD_ENABLE_CONTROL        = 0x01,
    USB_AUDIO_UDMPUCS_UD_MODE_SELECT_CONTROL   = 0x02

}USB_AUDIO_UP_DOWN_MIX_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Dolby Prologic Processing Unit Control Selector.

  Summary:
    Identifies the Audio Dolby Prologic Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Dolby Prologic Processing Unit 
    Control Selectors.

  Remarks:
    The "DPPUCS" in the enumeration member names is an acronym for Dolby Prologic
    Processing Unit Control Selector.
*/
typedef enum
{
    USB_AUDIO_DPPUCS_DP_CONTROL_UNDEFINED      = 0x00,
    USB_AUDIO_DPPUCS_DP_ENABLE_CONTROL         = 0x01,
    USB_AUDIO_DPPUCS_DP_MODE_SELECT_CONTROL    = 0x02

}USB_AUDIO_DOLBY_PROLOGIC_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio 3D Stereo Extender Processing Unit Control Selector.

  Summary:
    Identifies the Audio 3D Stereo Extender Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio 3D Stereo Extender Processing Unit 
    Control Selectors.

  Remarks:
    The "3DSEPUCS" in the enumeration member names is an acronym for 3D Stereo Extender
    Processing Unit Control Selector.
*/
typedef enum
{
    USB_AUDIO_3DSEPUCS_3D_CONTROL_UNDEFINED  = 0x00,
    USB_AUDIO_3DSEPUCS_3D_ENABLE_CONTROL     = 0x01,
    USB_AUDIO_3DSEPUCS_SPACIOUSNESS_CONTROL  = 0x02

}USB_AUDIO_3D_STEREO_EXTENDER_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Reverberation Processing Unit Control Selector.

  Summary:
    Identifies the Audio Reverberation Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Reverberation Processing Unit 
    Control Selectors.

  Remarks:
    The "RPUCS" in the enumeration member names stands for reverberation processing
    unit control selector.
*/

typedef enum
{
    USB_AUDIO_RPUCS_REVERB_CONTROL_UNDEFINED       = 0x00,
    USB_AUDIO_RPUCS_REVERB_ENABLE_CONTROL          = 0x01,
    USB_AUDIO_RPUCS_REVERB_LEVEL_CONTROL       = 0x02,
    USB_AUDIO_RPUCS_REVERB_TIME_CONTROL        = 0x03,
    USB_AUDIO_RPUCS_REVERB_FEEDBACK_CONTROL    = 0x04

}USB_AUDIO_REVERBERATION_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Chorus Processing Unit Control Selector.

  Summary:
    Identifies the Audio Chorus Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Chorus Processing Unit 
    Control Selectors.

  Remarks:
    The "CPUCS" in the enumeration member names stands for chorus processing
    unit control selector.
*/
typedef enum
{
    USB_AUDIO_CPUCS_CHORUS_CONTROL_UNDEFINED  = 0x00,
    USB_AUDIO_CPUCS_CHORUS_ENABLE_CONTROL     = 0x01,
    USB_AUDIO_CPUCS_CHORUS_LEVEL_CONTROL  = 0x02,
    USB_AUDIO_CPUCS_CHORUS_RATE_CONTROL   = 0x03,
    USB_AUDIO_CPUCS_CHORUS_DEPTH_CONTROL  = 0x04

}USB_AUDIO_CHORUS_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Dynamic Range Compressor Processing Unit Control Selector.

  Summary:
    Identifies the Audio Dynamic Range Compressor Processing Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Dynamic Range Compressor 
    Processing Unit Control Selectors.

  Remarks:
    The "DRCPUCS" in the enumeration member names stands for dynamic range compressor
    processing unit control selector.
*/
typedef enum
{
    USB_AUDIO_DRCPUCS_DR_CONTROL_UNDEFINED        = 0x00,
    USB_AUDIO_DRCPUCS_DR_ENABLE_CONTROL           = 0x01,
    USB_AUDIO_DRCPUCS_COMPRESSION_RATE_CONTROL    = 0x02,
    USB_AUDIO_DRCPUCS_MAXAMPL_CONTROL             = 0x03,
    USB_AUDIO_DRCPUCS_THRESHOLD_CONTROL           = 0x04,
    USB_AUDIO_DRCPUCS_ATTACK_TIME                 = 0x05,
    USB_AUDIO_DRCPUCS_RELEASE_TIME                = 0x06

}USB_AUDIO_DYNAMIC_RANGE_COMPRESSOR_PROCESSING_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Extension Unit Control Selector.

  Summary:
    Identifies the Audio Extension Unit Control Selector.

  Description:
    This enumeration identifies the possible Audio Extension Unit Control Selectors.

  Remarks:
    The "EUCS" in the enumeration member names is an acronym for Extension Unit 
    Control Selectors.
*/
typedef enum
{
    USB_AUDIO_EUCS_XU_CONTROL_UNDEFINED  = 0x00,
    USB_AUDIO_EUCS_XU_ENABLE_CONTROL     = 0x01

}USB_AUDIO_EXTENSION_UNIT_CONTROL_SELECTORS;

// *****************************************************************************
/* Audio Endpoint Control Selector.

  Summary:
    Identifies the Audio Endpoint Control Selector.

  Description:
    This enumeration identifies the possible Audio Endpoint Control Selectors.

  Remarks:
    The "ECS" in the enumeration member names is an acronym for Extension  
    Control Selectors.
*/
typedef enum
{
    USB_AUDIO_ECS_EP_CONTROL_UNDEFINED        = 0x00,
    USB_AUDIO_ECS_SAMPLING_FREQUENCY_CONTROL  = 0x01,
    USB_AUDIO_ECS_PITCH_CONTROL               = 0x02

}USB_AUDIO_ENDPOINT_CONTROL_SELECTORS;


// *****************************************************************************
/* USB Audio Copy Protect Control Codes.

  Summary:
    Identifies the Copy Control codes for USB Audio Class.

  Description:
    This enumeration identifies the possible Copy Control Protect codes for
    USB Audio Class. Refer the document "Universal Serial Bus Device Class Definition
    for Audio Devices revision 1.0" Section 5.2.2.1.3.1.

  Remarks:
    None.
*/
typedef enum
{
    /* copying is permitted without restriction.
     * The material is either not copyrighted or the copyright is not asserted */
    USB_AUDIO_COPY_PROTECT_CONTROL_CPL0 = 0x00 ,

    /* One generation of copies can be made.
     * The material is copyright protected and is the original */
    USB_AUDIO_COPY_PROTECT_CONTROL_CPL1 = 0x01 ,

    /* The material is copyright protected and no digital copying is permitted  */
    USB_AUDIO_COPY_PROTECT_CONTROL_CPL2 = 0x02

} USB_AUDIO_COPY_PROTECT_CONTROL;
// *****************************************************************************
/* Audio Input Terminal Descriptor Type

  Summary:
    Identifies the Audio Input Terminal Descriptor Type.

  Description:
    This type identifies the Audio Input Terminal Descriptor. This structure is 
    as per the USB protocol.

  Remarks:
    Needs to packed always.
*/

typedef struct __attribute__ ((packed))
{
    /* Size of this descriptor */
    uint8_t bLength;

    /* Interface descriptor type */
    uint8_t bDescriptorType;

    /* Interface Descriptor Subtype */
    uint8_t bDescriptorSubtype;

    /* Unique Terminal Identifier Constant */
    uint8_t bTerminalID;

    /* Terminal Type */
    uint16_t wTerminalType;

    /* ID of the associated Output Terminal */
    uint8_t bAssocTerminal;

    /* Number of channels in the terminal output */
    uint8_t bNrChannels;

    /* Spatial location of the logical channels */
    uint16_t wChannelConfig;

    /* First Logical Channel String descriptor index */
    uint8_t iChannelNames;

    /* Input Terminal String Descriptor Index */
    uint8_t iTerminal;

}USB_AUDIO_INPUT_TERMINAL_DESCRIPTOR;

// *****************************************************************************
/* Audio Output Terminal Descriptor Type

  Summary:
    Identifies the Audio Output Terminal Descriptor Type.

  Description:
    This type identifies the Audio Output Terminal Descriptor. This structure is 
    as per the USB protocol.

  Remarks:
    Needs to packed always.
*/


typedef struct __attribute__ ((packed))
{
    /* Size of this descriptor */
    uint8_t bLength;

    /* Interface descriptor type */
    uint8_t bDescriptorType;

    /* Interface Descriptor Subtype */
    uint8_t bDescriptorSubtype;

    /* Unique Terminal Identifier Constant */
    uint8_t bTerminalID;

    /* Terminal Type */
    uint16_t wTerminalType;

    /* ID of the associated Input Terminal */
    uint8_t bAssocTerminal;

    /* Source Unit or Terminal ID */
    uint8_t bSourceID;

    /* Output Terminal String Descriptor Index */
    uint8_t iTerminal;

}USB_AUDIO_OUTPUT_TERMINAL_DESCRIPTOR;

// *****************************************************************************
/* USB Audio Class Specific AS Interface Descriptor

  Summary:
    Identifies the USB Audio Class Specific AS Interface Descriptor.

  Description:
    This type identifies the USB Audio Class Specific AS Interface Descriptor.
    This structure is as per the USB protocol.

  Remarks:
    Needs to packed always.
*/


typedef struct __attribute__ ((packed))
{
    /* Size of this descriptor */
    uint8_t bLength;

    /* Interface descriptor type */
    uint8_t bDescriptorType;

    /* Interface Descriptor Subtype */
    uint8_t bDescriptorSubtype;

    /* Terminal ID to which interface endpoint is connected */
    uint8_t bTerminalLink;

    /* Delay introduced by data path */
    uint8_t bDelay;


}USB_AUDIO_CS_AS_INTERFACE_DESCRIPTOR;


typedef struct __attribute__ ((packed))
{
	/* Size of this descriptor */
    uint8_t bLength;
	
	/* Interface descriptor type */
    uint8_t bDescriptorType;
	
	/* Interface Descriptor Subtype */
    uint8_t bDescriptorSubtype;
	
	
    uint16_t bcdADC;
	
	
    uint16_t wTotalLength;
	
	
    uint8_t bInCollection;
	
    uint8_t baInterfaceNr[USB_DEVICE_AUDIO_MAX_STREAMING_INTERFACES];

} USB_AUDIO_CS_AC_INTERFACE_DESCRIPTOR;

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    unsigned :8;
    uint8_t controlSelector;
    uint8_t interfaceNo;
    uint8_t entityID;

    uint16_t wLength;
} USB_AUDIO_CONTROL_INTERFACE_REQUEST;
typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    unsigned :8;
    uint8_t controlSelector;
    uint8_t interfaceNo;
    uint8_t terminalId;
    uint16_t wLength;
} USB_AUDIO_TERMINAL_CONTROL_REQUEST;

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint8_t OCN;
    uint8_t ICN;
    uint8_t interfaceNo;
    uint8_t mixerUnitID;
    uint16_t wLength;
} USB_AUDIO_MIXER_CONTROL_REQUEST;

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    unsigned :16;
    uint8_t interfaceNo;
    uint8_t selectorUnitId;
    uint16_t wLength;

} USB_AUDIO_SELECTOR_CONTROL_REQUEST;

typedef struct
{
    unsigned direction : 1;
    unsigned type: 2;
    unsigned Recipient: 5;
    uint8_t bRequest;
    uint8_t channelNumber;
    uint8_t controlSelector;
    uint8_t interfaceId;
    uint8_t featureUnitId;
    uint16_t wLength;
} USB_AUDIO_FEATURE_CONTROL_REQUEST;

typedef struct
{
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint8_t controlSelector;
    uint8_t channelNo;

} USB_AUDIO_PROCESSING_CONTROL_REQUEST;


typedef union
{
    unsigned long Val;
    union
    {
        struct
        {
            uint8_t CIN :4;
            uint8_t CN  :4;
            uint8_t MIDI_0;
            uint8_t MIDI_1;
            uint8_t MIDI_2;
        };
        struct
        {
            uint8_t CodeIndexNumber :4;
            uint8_t CableNumber     :4;
            uint8_t DATA_0;
            uint8_t DATA_1;
            uint8_t DATA_2;
        };
    };
} USB_DEVICE_AUDIO_MIDI_EVENT_PACKET, *P_USB_AUDIO_MIDI_EVENT_PACKET;
#endif

