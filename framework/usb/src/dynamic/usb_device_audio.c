/*******************************************************************************
 USB Audio Class Function Driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_audio.c

  Summary:
    USB audio class function driver.

  Description:
    USB audio class function driver.
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

 SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
#include "usb/usb_device_audio.h"
#include "usb/usb_device.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Data Types
// *****************************************************************************
// *****************************************************************************
void _USB_DEVICE_AUDIO_SetupPacketHandler (USB_DEVICE_AUDIO_INDEX iAudio , USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                           USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA* controlEventData);

void _USB_DEVICE_AUDIO_Initialize (SYS_MODULE_INDEX iAudio, DRV_HANDLE usbDeviceHandle,
               void* funcDriverInit, uint8_t interfaceNumber, uint8_t alternateSetting,
               uint8_t descriptorType, uint8_t * pDescriptor );

void _USB_DEVICE_AUDIO_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iAudio,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA* controlEventData);

void _USB_DEVICE_AUDIO_ReadIRPCallBack ( struct _USB_DEVICE_IRP * irp);

void _USB_DEVICE_AUDIO_WriteIRPCallBack ( struct _USB_DEVICE_IRP * irp);

void _USB_DEVICE_AUDIO_Deinitialize ( SYS_MODULE_INDEX funcDriverIndex );

// *****************************************************************************
/* Function:
    void _USB_DEVICE_AUDIO_IRPCancelAll(USB_DEVICE_AUDIO_INDEX iAudio )
   Summary:
    This function cancels all pending Read and Write requests placed to
    USB Device Audio function driver.

   Description:
    This function cancels all pending Read and Write requests placed to
    USB Device Audio function driver.
   Precondition:
    The function driver should have been configured.
   Parameters:
    iAudio - USB Device Audio Function Driver instance.

   Returns:
    None
   Example:

   Remarks:
     None
 */
void _USB_DEVICE_AUDIO_IRPCancelAll(USB_DEVICE_AUDIO_INDEX iAudio );

// *****************************************************************************
/* AUDIO Device function driver structure

  Summary:
    Defines the function driver structure required for the device layer.

  Description:
    This data type defines the function driver structure required for the
    device layer.

  Remarks:
    This structure is private to the USB stack.
 */
USB_DEVICE_FUNCTION_DRIVER audioFuncDriver =
{

    /* AUDIO init function */
    .initializeByDescriptor             = &_USB_DEVICE_AUDIO_Initialize ,

    /* AUDIO de-init function */
    .deInitialize           = &_USB_DEVICE_AUDIO_Deinitialize ,

    /* AUDIO set-up packet handler */
    .controlTransferNotification     = &_USB_DEVICE_AUDIO_ControlTransferHandler,

    /* AUDIO tasks function */
    .tasks                  = NULL
        
};

// *****************************************************************************
/* Audio function instance objects.

  Summary:
    Holds all of the variables required by audio instance.

  Description:
    This structure holds all of the variables required by audio instance.

  Remarks:
    None.
*/

USB_DEVICE_AUDIO_INSTANCE gUSBDeviceAudioInstance[USB_DEVICE_AUDIO_MAX_INSTANCES];


// *****************************************************************************
/* AUDIO Device IRPs

  Summary:
    Array of AUDIO Device IRP.

  Description:
    Array of AUDIO Device IRP. This array of IRP will be shared by read, write and
    notification data requests.

  Remarks:
    This array is private to the USB stack.
 */

USB_DEVICE_IRP gUSBDeviceAudioIRP[USB_DEVICE_AUDIO_QUEUE_SIZE];
//******************************************************************************

//******************************************************************************


void _USB_DEVICE_AUDIO_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iAudio,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA* controlEventData)
{
    
    /* check the validity of the function driver index */
    if ( USB_DEVICE_AUDIO_MAX_INSTANCES <= iAudio )
    {
        /* invalid handle */
        SYS_ASSERT (false, "invalid Audio Index");
        //return;
    }

    /* check if Audio function is initialized properly */
    if (gUSBDeviceAudioInstance[iAudio].state != USB_DEVICE_AUDIO_INSTANCE_INITIALIZED)
    {
        /* Audio Function driver not initialized */
        //SYS_ASSERT (false, "audio function driver is not initialized yet");
        //return;
    }

    
    switch(controlEvent)
    {
        case USB_DEVICE_CONTROL_SETUP_REQUEST:
            _USB_DEVICE_AUDIO_SetupPacketHandler(iAudio, controlHandle, controlEventData );
            break;
        case USB_DEVICE_CONTROL_DATA_RECEIVED:
            gUSBDeviceAudioInstance[iAudio].appEventCallBack
            (
                iAudio,
                USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVED,
                controlHandle,
                NULL,
                0
            );
             
            break;
        case USB_DEVICE_CONTROL_DATA_SENT:
            gUSBDeviceAudioInstance[iAudio].appEventCallBack
            (
                iAudio,
                USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_SENT,
                controlHandle,
                NULL,
                0
            );
            break;
        default:
            break;
    }
}// end of function _USB_DEVICE_AUDIO_ControlTransferHandler

void _USB_DEVICE_AUDIO_SetupPacketHandler (USB_DEVICE_AUDIO_INDEX iAudio , USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                           USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA* controlEventData)
{
    uint8_t audioControlInterfaceId;
    uint8_t interfaceId;
    uint8_t alternateSetting;
    uint8_t streamIntfcIndex;
    uint8_t noOfEndpoints;
    USB_ENDPOINT ep; 
    uint16_t maxPacketSize;
    USB_DEVICE_HANDLE usbDeviceHandle;
    USB_SETUP_PACKET * setupPkt;
    USB_DEVICE_AUDIO_INTERFACE_INFO interfaceInfo;
    setupPkt =  controlEventData->setupRequest;
    USB_ERROR endpointEnableResult; 
 
    usbDeviceHandle = gUSBDeviceAudioInstance[iAudio].devLayerHandle;
    /* Check if the request is an standard interface request*/
    if((setupPkt->bmRequestType == (USB_SETUP_DIRN_HOST_TO_DEVICE | USB_SETUP_TYPE_STANDARD | USB_SETUP_RECIPIENT_INTERFACE))
        && (setupPkt->bRequest == USB_REQUEST_SET_INTERFACE))
    {
        //We have recieved Standard Set request
            interfaceId = setupPkt->bIntfID;

            audioControlInterfaceId = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;
            streamIntfcIndex = interfaceId - audioControlInterfaceId - 1;

            alternateSetting = setupPkt->bAltID;
            
            // Set correct alternate interface.
            if (alternateSetting)
            {
                gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamIntfcIndex].activeSetting = alternateSetting;
                noOfEndpoints = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamIntfcIndex].alterntSetting[alternateSetting].numEndPoints;
                if (noOfEndpoints)
                {
                    ep = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamIntfcIndex].alterntSetting[alternateSetting].isoDataEp.epAddr;
                    maxPacketSize = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamIntfcIndex].alterntSetting[alternateSetting].isoDataEp.epMaxPacketSize;
                    //Enable ISO Data Endpoint
                    endpointEnableResult = USB_DEVICE_EndpointEnable ( usbDeviceHandle ,
                                    ep ,
                                    USB_TRANSFER_TYPE_ISOCHRONOUS ,
                                    256 );
                    if (endpointEnableResult != USB_ERROR_NONE)
                        SYS_ASSERT (false, "Endpoint not Enabled");

                    //Change Audio Instance object state to Initialized.
                    gUSBDeviceAudioInstance[iAudio].state = USB_DEVICE_AUDIO_INSTANCE_INITIALIZED;
                    interfaceInfo.interfaceNumber = interfaceId;
                    interfaceInfo.interfaceAlternateSettting = alternateSetting;
                    gUSBDeviceAudioInstance[iAudio].appEventCallBack
                    (
                        iAudio,
                        USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING,
                        controlHandle,
                        &interfaceInfo,
                        0
                    );
                }    
            }
            else //alternateSetting  = 0
            {
                //should be removed later;
                USB_DEVICE_EndpointDisable(usbDeviceHandle ,0x01);
                gUSBDeviceAudioInstance[iAudio].state = USB_DEVICE_AUDIO_INSTANCE_NOT_INITIALIZED;
                interfaceInfo.interfaceNumber = interfaceId;
                interfaceInfo.interfaceAlternateSettting = alternateSetting;
                gUSBDeviceAudioInstance[iAudio].appEventCallBack
                (
                    iAudio,
                    USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING,
                    controlHandle,
                    (void *)&interfaceInfo,
                    0
                );
                _USB_DEVICE_AUDIO_IRPCancelAll(0);
            }
            USB_DEVICE_ControlStatus( gUSBDeviceAudioInstance[iAudio].devLayerHandle,
                                                 controlHandle, USB_DEVICE_CONTROL_STATUS_OK);
    }//end of if((setupPkt->bmRequestType == 
    else if ((setupPkt->bmRequestType == (USB_SETUP_DIRN_DEVICE_TO_HOST | USB_SETUP_TYPE_STANDARD | USB_SETUP_RECIPIENT_INTERFACE))
            && (setupPkt->RequestType == USB_REQUEST_GET_INTERFACE))
    {
            //reply with active alternate interface settings to Host.
            interfaceId = setupPkt->bIntfID;
            audioControlInterfaceId = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;
            streamIntfcIndex = interfaceId - audioControlInterfaceId - 1;
            alternateSetting = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamIntfcIndex].activeSetting;

            USB_DEVICE_ControlSend( gUSBDeviceAudioInstance[iAudio].devLayerHandle,
                            controlHandle,
                            (void *)&alternateSetting, 1);
    }

    /*Check if request type is a class-specific */
    else if ((setupPkt->bmRequestType == (USB_SETUP_DIRN_DEVICE_TO_HOST | USB_SETUP_TYPE_CLASS | USB_SETUP_RECIPIENT_INTERFACE))
            ||(setupPkt->bmRequestType ==  (USB_SETUP_DIRN_HOST_TO_DEVICE | USB_SETUP_TYPE_CLASS | USB_SETUP_RECIPIENT_INTERFACE))
             )
    {
        if ( gUSBDeviceAudioInstance[iAudio].appEventCallBack)
        {
            /* inform the application about the request */
            /* the application needs to handle both EP and entity specific requests */
           gUSBDeviceAudioInstance[iAudio].appEventCallBack
           (
                iAudio,
                USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED,
                controlHandle,
                controlEventData->setupRequest,
                0
            );
                
        }        
    }// end of else if
}//end of function _USB_DEVICE_AUDIO_SetupPacketHandler


//******************************************************************************




//******************************************************************************
// This function is called by the device layer. It gets called multiple times as and when the USB device layer
//starts parsing the descriptors.
void _USB_DEVICE_AUDIO_Initialize (SYS_MODULE_INDEX iAudio, DRV_HANDLE usbDeviceHandle,
               void* funcDriverInit, uint8_t interfaceNumber, uint8_t alternateSetting,
               uint8_t descriptorType, uint8_t * pDescriptor )
{
    /*pointer to Standard Endpoint Descriptor */
    USB_ENDPOINT_DESCRIPTOR *pEPDesc;

    /* pointer to Standard Interface descriptor */
    USB_INTERFACE_DESCRIPTOR *pStdInfDesc;
    
    /* pointer to Class Specific Interface Descriptor */
    USB_AUDIO_CS_AC_INTERFACE_DESCRIPTOR *pCsInfDesc;

    uint8_t epAddressAndDirection;
    uint16_t maxPacketSize;
    //USB_ENDPOINT ep;
    uint8_t cnt;
    uint8_t audioControlInterfaceId;
    uint8_t strmIntrfcIndex;
    USB_ERROR endpointEnableResult;
    //uint8_t noOfEndpoints;


    /* check the validity of the function driver index */
    if ( ( iAudio < 0 ) || ( iAudio >= USB_DEVICE_AUDIO_MAX_INSTANCES ) )
    {
        /* Assert on invalid AUDIO index */
        SYS_ASSERT ( false , "Invalid Audio instance number" );
    }

     //save the device handle to the curresponding Audio Instance object.
    gUSBDeviceAudioInstance[iAudio].devLayerHandle = usbDeviceHandle;

    //save the Audio Index to the curresponding Audio Instance object.
    gUSBDeviceAudioInstance[iAudio].audioIndex = iAudio;

     /* check the type of descriptor passed by device layer */
    switch ( descriptorType )
    { 
        case USB_DESCRIPTOR_INTERFACE: //Interface Descriptor
            
            pStdInfDesc = (USB_INTERFACE_DESCRIPTOR*) pDescriptor;

            /* check if it is USB audio interface descriptor*/
            if (pStdInfDesc->bInterfaceClass == USB_AUDIO_INTERFACE_CLASS_CODE_AUDIO)
            {
                /*Check if it is an Audio Control Interface descriptor*/
                if(pStdInfDesc->bInterfaceSubClass == USB_AUDIO_ISC_AUDIOCONTROL)
                {
                    /* The program control reached here means that the device layer has detected an
                       Standard Audio Control interface descriptor. Now we have to save all the fields
                       present in the Standard Audio Control interface descriptor to the corresponding
                       Audio Instance Object. */

                    /*save the Interface number to the corresponding Audio Instance Object.*/ 
                    gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum = pStdInfDesc->bInterfaceNumber;
                    
                    //save the no of endpoints present in the Audio Control Interface. If there are
                    // endpoints present as part of AC interface descriptor that must be an Interrupt endpoint.
                    gUSBDeviceAudioInstance[iAudio].infCollection.isIntEpExists = pStdInfDesc->bNumEndPoints;
                }
                /* Check if it is an Audio Streaming Interface descriptor */
                else if(pStdInfDesc->bInterfaceSubClass == USB_AUDIO_ISC_AUDIOSTREAMING)
                {
                    /* We have received an Audio Streaming Interface descriptor. Save the interafce
                     * number to an array of Audio streaming interfaces. For an audio function the interface numbers
                     * starts from Audio Control Interface ID.*/
                   
                    //save number of endpoints present in the streaming interface
                    audioControlInterfaceId = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;
                    //find out audio streaming interface array index.
                    strmIntrfcIndex = interfaceNumber-audioControlInterfaceId-1;

                    /*save no of endpoints present in the streaming interface*/
                    gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[strmIntrfcIndex].alterntSetting[alternateSetting].numEndPoints = pStdInfDesc->bNumEndPoints;
                }
            }
        break; //end of case USB_DESCRIPTOR_INTERFACE:

        case USB_AUDIO_CSDT_CS_INTERFACE: //Class Specific Audio Control Interface Descriptor.
            pCsInfDesc = (USB_AUDIO_CS_AC_INTERFACE_DESCRIPTOR*) pDescriptor;

            /* check if this Class specific descriptor belongs to an AC Interafce*/
            if (interfaceNumber == gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum)
            {
                switch (pCsInfDesc->bDescriptorSubtype)
                {
                    case USB_AUDIO_CSACIDS_HEADER:
                        
                        if (pCsInfDesc->bInCollection > USB_DEVICE_AUDIO_MAX_STREAMING_INTERFACES )
                        {
                            SYS_ASSERT(false, "More number of streaming interface present than declared by user in the sys_config.h file");
                        }
                        else
                        {
                            //save number of audio steaming interfaces
                            gUSBDeviceAudioInstance[iAudio].infCollection.numStreamingInf = pCsInfDesc->bInCollection;

                            //save interface numbers of the all available audio streaming and Midi interfaces.
                            for (cnt = 0; cnt<pCsInfDesc->bInCollection; cnt++ )
                            {
                                gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[cnt].interfaceNum = pCsInfDesc->baInterfaceNr[cnt];
                            }

                            //save audio specification number.
                            gUSBDeviceAudioInstance[iAudio].infCollection.bcdADC = pCsInfDesc->bcdADC;
                        }
                    break;

                    default:
                        //SYS_ASSERT(false, "unknown descriptor subtype");
                    break;
                } //end of "switch (pCsInfDesc->bDescriptorSubtype)"
            } //end of "if (interfaceNumber == audioInstance[iAudio].infCollection.bControlInterfaceNum)"
        break; //end of "case DEVICE_AUDIO_CS_INTERFACE"

        case USB_DESCRIPTOR_ENDPOINT:
            /* we have received an Endpoint descriptor from device Layer*/
            pEPDesc = ( USB_ENDPOINT_DESCRIPTOR* ) pDescriptor;
            audioControlInterfaceId = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;
            strmIntrfcIndex = interfaceNumber - audioControlInterfaceId - 1;

            
            // check if this Endpoint belongs to an audio Streaming interface
            if ((interfaceNumber == gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[strmIntrfcIndex].interfaceNum))
            {
                /* save the ep address */
                epAddressAndDirection = pEPDesc->bEndpointAddress;

                /* save max packet size */
                maxPacketSize = ( ( USB_ENDPOINT_DESCRIPTOR* ) pDescriptor )->wMaxPacketSize;

                audioControlInterfaceId = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;

                strmIntrfcIndex = interfaceNumber - audioControlInterfaceId - 1;
                
                /* save ep address to the data interface */
                gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[strmIntrfcIndex].alterntSetting[alternateSetting].isoDataEp.epAddr = epAddressAndDirection;

                /* save max packet size to the data interface */
                gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[strmIntrfcIndex].alterntSetting[alternateSetting].isoDataEp.epMaxPacketSize = maxPacketSize;

                /* enable the endpoint only if the alternatting setting is zero*/
                if (alternateSetting == 0)
                {
                    if (interfaceNumber == gUSBDeviceAudioInstance[iAudio].infCollection.numStreamingInf-1)
                    {
                        gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[interfaceNumber-gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum].activeSetting = 0;
                        endpointEnableResult = USB_DEVICE_EndpointEnable ( usbDeviceHandle ,
                                            epAddressAndDirection ,
                                            USB_TRANSFER_TYPE_ISOCHRONOUS ,
                                            256 );
                        if (endpointEnableResult != USB_ERROR_NONE)
                            SYS_ASSERT(false, "Endpoint is not enabled");
                        gUSBDeviceAudioInstance[iAudio].state = USB_DEVICE_AUDIO_INSTANCE_INITIALIZED;

                    }
                }
            }
            break;

        default:
            //SYS_ASSERT(false, "Unknown descriptor type");
        break; 
    }//end of switch ( descriptorType )
}

// *****************************************************************************

void _USB_DEVICE_AUDIO_Deinitialize ( SYS_MODULE_INDEX iAudio )
{
    /* Cancel all IRPs on the owned endpoints and then
     * disable the endpoint */

    if(iAudio >= USB_DEVICE_AUDIO_MAX_INSTANCES)
    {
        SYS_ASSERT(false," Invalid instance");
        return;
    }

   gUSBDeviceAudioInstance[iAudio].state = USB_DEVICE_AUDIO_INSTANCE_NOT_INITIALIZED;

   _USB_DEVICE_AUDIO_IRPCancelAll(iAudio);
}





// *****************************************************************************
/* Function:
    USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Read ( USB_DEVICE_AUDIO_INDEX iAudio ,
                                      uint8_t interfaceNum ,
                                      void * data ,
                                      size_t size )

  Summary:
    Reads the data received from the Audio Interface for
 *  specified instance of the USB device layer.

  Description:
    Reads the data received from the Audio Interface for
 *  specified instance of the USB device layer.

 *
  Parameters:
    USB_DEVICE_AUDIO_INDEX iAudio    - Audio function driver Index number
 *
 *  uint8_t interfaceNum    - Audio streaming or Control Interface number
 *
 *  data - pointer to the data buffer where read data will be stored.
 *  size - Size of the data buffer. Refer to the description section for more
           details on how the size affects the transfer.
 *
 *
  Returns:
    USB_DEVICE_AUDIO_RESULT

*/

USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Read
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
    uint8_t interfaceNum ,
    void * data ,
    size_t size
)
{
    /* Holds Audio Stream Interface array index for the corresponding streaming interface interfaceNum */
    uint8_t streamInfIndex;

    /*Holds audio Control Interaface ID of audio function instance iAudio*/
    uint8_t audioControlIntrfcID;

    /*Holds value of active alternate settings for this interface*/
    uint8_t activeAlternateSetting;

    uint8_t cnt = 0;

    USB_ENDPOINT epStruct;

    USB_DEVICE_IRP_STATUS irpStatus;

    USB_ERROR irpErr;

    USB_DEVICE_AUDIO_EP_INSTANCE* tempEndpointInstance;

    bool freeSlot = false;

    * transferHandle = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;

    /* check the validity of the function driver index */
    if ( USB_DEVICE_AUDIO_MAX_INSTANCES <= iAudio ) 
    {
        /* invalid handle */
        return USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID;
    }

    /* check if Audio function is initialized properly */
    if (gUSBDeviceAudioInstance[iAudio].state != USB_DEVICE_AUDIO_INSTANCE_INITIALIZED)
    {
        return USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_NOT_CONFIGURED;
    }

    /* Check if user passed valid buffer */
    if ( data == NULL )
    {
        /* return error */
        return USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_BUFFER;
    }


    /* Retrive Audio Control Interface ID. We are going to use it to locate the Audio streaming
     * Interface array index from the interfaceNum passed to this function */
    audioControlIntrfcID = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;

    /*Find out the array streaming interface */
    streamInfIndex = interfaceNum - audioControlIntrfcID- 1;

    /*Retriev the active alternate setting of the interface from Audio Instance object */
    activeAlternateSetting = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].activeSetting;

    /* Check if the interface number passed to this fucntion is valid*/
    if (interfaceNum != gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].interfaceNum)
    {
        SYS_ASSERT ( false , "Invalid interface number " );
        return USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_INTERFACE_ID;
    }
    if (gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].alterntSetting[activeAlternateSetting].numEndPoints == 0)
    {
        return USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_INTERFACE_ID;
    }
    tempEndpointInstance = &(gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].alterntSetting[activeAlternateSetting].isoDataEp);
  
    /* Loop and find a free IRP in the Q */
    for ( cnt = 0; cnt < USB_DEVICE_AUDIO_QUEUE_SIZE; cnt ++ )
    {
        /* get the IRP status */
        irpStatus = tempEndpointInstance->irpObject[cnt].irp.status;

        /* check if it can be used */
        if ( ( irpStatus != USB_DEVICE_IRP_STATUS_IN_PROGRESS ) && ( irpStatus != USB_DEVICE_IRP_STATUS_PENDING ) )
        {
            /* got a free slot in the Q 'cnt' denotes the free slot index */
            freeSlot = true;

            break;
        }
        else
        {
                Nop();
        }
    }

   
    /* check if free slot is available */
    if(freeSlot)
    {
        //retrieve endpoint address
        epStruct = tempEndpointInstance->epAddr;

        /* fill the required IRP fields */

        /*fill audio function index(instance ID)*/
        tempEndpointInstance->irpObject[cnt].iAudio = iAudio;

        /* fill IRP object with the pointer to the data that is to be transferred to the Host*/
        tempEndpointInstance->irpObject[cnt].irp.data = data;

        /* fill IRP object wirh size of the data that is to be transferred to the USB host*/
        tempEndpointInstance->irpObject[cnt].irp.size = size;

        tempEndpointInstance->irpObject[cnt].irp.callback = _USB_DEVICE_AUDIO_ReadIRPCallBack;

        tempEndpointInstance->irpObject[cnt].irp.userData = iAudio;

        *transferHandle = (USB_DEVICE_AUDIO_TRANSFER_HANDLE) &(tempEndpointInstance->irpObject[cnt].irp);

        irpErr = USB_DEVICE_IRPSubmit ( gUSBDeviceAudioInstance[iAudio].devLayerHandle ,
                                            epStruct ,
                                            &(tempEndpointInstance->irpObject[cnt].irp) );

        /* check if IRP submit is success */
        if ( USB_ERROR_NONE == irpErr )
        {

            /* return success */
            return USB_DEVICE_AUDIO_RESULT_OK;
        }

        else
        {
            /* only possibility  */
            return USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL;
        }

    }

    /* no free slot */
    else
    {

        /* Q full */
        return USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL;
    }
}

void _USB_DEVICE_AUDIO_IRPCancelAll(USB_DEVICE_AUDIO_INDEX iAudio )
{
    USB_DEVICE_IRPCancelAll(gUSBDeviceAudioInstance[iAudio].devLayerHandle,  0x01);
    //USB_DEVICE_IRPCancelAll(audioInstance[iAudio].devLayerHandle,  0x81);
}

void _USB_DEVICE_AUDIO_WriteIRPCallBack (struct _USB_DEVICE_IRP * irp )
{
    USB_DEVICE_AUDIO_INDEX iAudio;
    USB_DEVICE_AUDIO_EVENT_DATA_WRITE_COMPLETE writeEventData;
    unsigned int transferByteCount;

    /* get the Audio instance number */
    iAudio = irp->userData;

    transferByteCount = irp->size;

    gUSBDeviceAudioInstance[iAudio].appEventCallBack(iAudio,
                                   USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE,
                                   (USB_DEVICE_CONTROL_TRANSFER_HANDLE)0,
                                   &writeEventData,
                                   transferByteCount);
   
}


//******************************************************************************


void _USB_DEVICE_AUDIO_ReadIRPCallBack ( struct _USB_DEVICE_IRP * irp )
{
    USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE readEventData;
    USB_DEVICE_AUDIO_INDEX iAudio;
    unsigned int transferByteCount;

    /* get the Audio instance number */
    iAudio =  irp->userData;
    transferByteCount = irp->size;
    if (transferByteCount)
    {
        gUSBDeviceAudioInstance[iAudio].appEventCallBack(iAudio,
                                   USB_DEVICE_AUDIO_EVENT_READ_COMPLETE,
                                   (USB_DEVICE_CONTROL_TRANSFER_HANDLE)0,
                                   &readEventData,
                                   transferByteCount);
    }
   

}


// *****************************************************************************
// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_AUDIO_Write ( USB_DEVICE_AUDIO_INDEX iAudio ,
                                         uint8_t interfaceNum ,
                                         USB_DEVICE_AUDIO_DATA_BUFFER_OBJECT* bufferObj )

  Summary:
    sends to the Audio Interface for
 *  the specified instance of the USB device layer.

  Description:
    sends to the Audio Interface for
 *  the specified instance of the USB device layer.

 *
  Parameters:
    USB_DEVICE_AUDIO_INDEX iAudio    - Audio function driver Index number
 *
 *  uint8_t interfaceNum    - Audio streaming or Control Interface number
 *
 *  USB_DEVICE_AUDIO_DATA_BUFFER_OBJECT* bufferObj - pointer to the buffer where received data
 *
 * is to be stored.
 *
 *
  Returns:
    USB_DEVICE_AUDIO_RESULT

*/


USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Write
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
    uint8_t interfaceNum ,
    void * data ,
    size_t size
)
{

    /* Holds Audio Stream Interface array index for the corresponding streaming interface interfaceNum */
    uint8_t streamInfIndex;

    /*Holds audio Control Interaface ID of audio function instance iAudio*/
    uint8_t audioControlIntrfcID;
    
    /*Holds value of active alternate settings for this interface*/
    uint8_t activeAlternateSetting;

    uint8_t cnt;

    USB_ENDPOINT epStruct;

    USB_DEVICE_IRP_STATUS irpStatus;
    
    USB_ERROR irpErr;

    USB_DEVICE_AUDIO_EP_INSTANCE* tempEndpointInstance;

    bool freeSlot = false;

    *transferHandle = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID;

    /* check the validity of the function driver index */
    if ( USB_DEVICE_AUDIO_MAX_INSTANCES <= iAudio )
    {
        /* invalid handle */
        return USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID;
    }
    
    /* check if Audio function is initialized properly */
    if (gUSBDeviceAudioInstance[iAudio].state != USB_DEVICE_AUDIO_INSTANCE_INITIALIZED)
    {
       // return USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_NOT_CONFIGURED;
    }
    
    /* Check if user passed valid buffer */
    if ( data == NULL )
    {
        /* return error */
        return USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_BUFFER;
    }

    

    /* Retrive Audio Control Interface ID. We are going to use it to locate the Audio streaming
     * Interface array index from the interfaceNum passed to this function */
    audioControlIntrfcID = gUSBDeviceAudioInstance[iAudio].infCollection.bControlInterfaceNum;

    /*Find out the array streaming interface */
    streamInfIndex = interfaceNum - audioControlIntrfcID- 1;

    /*Retriev the active alternate setting of the interface from Audio Instance object */
    activeAlternateSetting = gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].activeSetting;

    /* Check if the interface number passed to this fucntion is valid*/
    if (interfaceNum != gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].interfaceNum)
    {
        SYS_ASSERT ( false , "Invalid interface number " );
        return USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_INTERFACE_ID;
    }

    tempEndpointInstance = &(gUSBDeviceAudioInstance[iAudio].infCollection.streamInf[streamInfIndex].alterntSetting[activeAlternateSetting].isoDataEp);

    /* Loop and find a free IRP in the Q */
    for ( cnt = 0; cnt < USB_DEVICE_AUDIO_QUEUE_SIZE; cnt ++ )
    {
        /* get the IRP status */
        irpStatus = tempEndpointInstance->irpObject[cnt].irp.status;

        /* check if it can be used */
        if ( ( irpStatus != USB_DEVICE_IRP_STATUS_IN_PROGRESS ) && ( irpStatus != USB_DEVICE_IRP_STATUS_PENDING ) )
        {
            /* got a free slot in the Q 'cnt' denotes the free slot index */
            freeSlot = true;

            break;
        }
    }

    /* check if free slot is available */
    if(freeSlot)
    {
        //retrieve endpoint address
        epStruct = tempEndpointInstance->epAddr;

        /* fill the required IRP fields */
        
        /*fill audio function index(instance ID)*/
        tempEndpointInstance->irpObject[cnt].iAudio = iAudio;

        /* fill IRP object with the pointer to the data that is to be transferred to the Host*/
        tempEndpointInstance->irpObject[cnt].irp.data = data;

        /* fill IRP object wirh size of the data that is to be transferred to the USB host*/
        tempEndpointInstance->irpObject[cnt].irp.size = size;
        
        tempEndpointInstance->irpObject[cnt].irp.callback = _USB_DEVICE_AUDIO_WriteIRPCallBack;
        
        tempEndpointInstance->irpObject[cnt].irp.userData = iAudio;

        *transferHandle = (USB_DEVICE_AUDIO_TRANSFER_HANDLE) &(tempEndpointInstance->irpObject[cnt].irp);
        irpErr = USB_DEVICE_IRPSubmit ( gUSBDeviceAudioInstance[iAudio].devLayerHandle ,
                                            epStruct ,
                                            &(tempEndpointInstance->irpObject[cnt].irp) );
        
        /* check if IRP submit is success */
        if ( USB_ERROR_NONE == irpErr )
        {

            /* return success */
            return USB_DEVICE_AUDIO_RESULT_OK;
        }

        else
        {
            /* only possibility  */
            return USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL;
        }
        
    }

    /* no free slot */
    else
    {

        /* Q full */
        return USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL;
    }
}

// *****************************************************************************


USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_EventHandlerSet
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT_HANDLER eventHandler ,
    uintptr_t userData
)
{
    USB_DEVICE_AUDIO_RESULT error = USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_HANDLER;

    if(eventHandler != NULL)
    {
        gUSBDeviceAudioInstance[iAudio].appEventCallBack = eventHandler;
        gUSBDeviceAudioInstance[iAudio].userData = userData;
        error = USB_DEVICE_AUDIO_RESULT_OK;
    }
    return error;
}

USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlSend
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    void * data, size_t size
)
{
    return ((USB_DEVICE_AUDIO_RESULT)
            (USB_DEVICE_ControlSend
            (gUSBDeviceAudioInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlReceive
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * data, size_t size
)
{
    return ((USB_DEVICE_AUDIO_RESULT)
            (USB_DEVICE_ControlReceive
            (gUSBDeviceAudioInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlStatus
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    USB_DEVICE_AUDIO_CONTROL_STATUS status
)
{
    return((USB_DEVICE_AUDIO_RESULT)
            (USB_DEVICE_ControlStatus
            (gUSBDeviceAudioInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            (USB_DEVICE_CONTROL_STATUS)(status))));
}

/*******************************************************************************
 End of File
 */
