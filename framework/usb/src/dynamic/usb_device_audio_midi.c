/*******************************************************************************
 USB audio class function driver.

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_audio_midi.c

  Summary:
    USB AUDIO class function driver.

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



//******************************************************************************
uint32_t rxCount;

void USB_DEVICE_AUDIO_MIDIRxDataCallBack ( void * hClient ,
                                     DRV_USB_PIPE_HANDLE hPipe ,
                                     DRV_USB_XFER_HANDLE hTransfer ,
                                     unsigned short int transferByteCount ,
                                     DRV_USB_DEVICE_XFER_STATUS statusTransfer )
{

    /* Get the instance structure */
    USB_DEVICE_AUDIO_INSTANCE* instance = ( USB_DEVICE_AUDIO_INSTANCE* ) hClient;

    if(USB_XFER_COMPLETED == statusTransfer)
    {

        if(instance->appEventCallBack)
        {
            instance->infCollection.streamInf[0].ep[0].dataState = USB_DEVICE_AUDIO_INSTANCE_RX_READY;

            instance->appEventCallBack(instance->audioIndex,
                                   USB_DEVICE_AUDIO_CALLBACK_MIDI_RX,
                                   USB_DEVICE_AUDIO_CALLBACK_RX_COMPLETE,
                                   0,
                                   1,
                                   transferByteCount);
        }



    }

}


//DRV_USB_OBJ *refPipeHandle;

USB_ERROR_STATUS USB_DEVICE_AUDIO_MIDI_Read ( USB_DEVICE_AUDIO_CLIENT_HANDLE cHandle ,
                                         uint8_t interfaceNum ,
                                         USB_DEVICE_AUDIO_DATA_BUFFER_OBJECT* bufferObj )
{

    uint8_t streamInfIndex;

    /* check if the handle passed is valid */
    if ( ( USB_DEVICE_AUDIO_MAX_INSTANCES <= cHandle ) || ( cHandle == USB_DEVICE_AUDIO_CLIENT_HANDLE_INVALID ) )
    {
        /* invalid handle */
        return USB_ERROR_INVALID_HANDLE;
    }

    /* Check if user passed valid buffer */
    if ( bufferObj == NULL )
    {
        /* return error */
        return USB_ERROR_INVALID_BUFFER;
    }


    /* most likely case */
    if ( audioInstance[cHandle].infCollection.streamInf[0].interfaceNum == interfaceNum )
    {

        streamInfIndex = 0;
    }

    else
    {
        //TODO find the required streaming interface index
        SYS_ASSERT ( false , "Invalid interface number " );
    }


    /* update the data OUT end point state to pending */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].dataState = USB_DEVICE_AUDIO_INSTANCE_RX_PENDING;

    /* Copy a reference of the application buffer for future use */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].bufferObject[0] = bufferObj;




    /* Place a transfer request to controller driver */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].cdxferHandle[0] =

        DRV_USB_Device_TransferRequest ( audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].pipeHandle ,
                                         USB_XFER_BULK_WRITE ,
                                         ( int8_t* ) bufferObj->data ,
                                         bufferObj->dataLen ,
                                         USB_XFER_REGULAR ,
                                         &audioInstance[cHandle] ,
                                         USB_DEVICE_AUDIO_MIDIRxDataCallBack );


    //refPipeHandle = audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[EP_STREAM_INDEX].pipeHandle;

    /* Check if controller driver accepted the request */
    if ( DRV_HANDLE_INVALID == audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].cdxferHandle[0] )
    {
        /* We are not checking why it failed because all the cases where it could fail
         * are already checked in the AUDIO layer. The only possibility of error here is the
         * non availability of slot in the controller driver's Q.*/

        /* prepare AUDIO to accept new requets */
        audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].dataState = USB_DEVICE_AUDIO_INSTANCE_RX_READY;

        /* Invalidate the buffer */
        audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[1].bufferObject[0] = NULL;

        /* We dont want to inform the application via callback, because
         the application is given a return status right away */

        //while(1);

        /* return error. Inform the application to try after some time */
        return USB_ERROR_RETRY;
    }


    /* return success */
    return USB_ERROR_OK;

}


//******************************************************************************


void USB_DEVICE_AUDIO_MIDITxDataCallBack ( void * hClient ,
                                     DRV_USB_PIPE_HANDLE hPipe ,
                                     DRV_USB_XFER_HANDLE hTransfer ,
                                     unsigned short int transferByteCount ,
                                     DRV_USB_DEVICE_XFER_STATUS statusTransfer )
{

    uint16_t infNum;

    /* Get the instance structure */
    USB_DEVICE_AUDIO_INSTANCE* instance = ( USB_DEVICE_AUDIO_INSTANCE* ) hClient;

    if(USB_XFER_COMPLETED == statusTransfer)
    {
        instance->infCollection.streamInf[0].ep[0].dataState = USB_DEVICE_AUDIO_INSTANCE_TX_READY;

        if(instance->appEventCallBack)
        {
             instance->appEventCallBack(instance->audioIndex,
                                   USB_DEVICE_AUDIO_CALLBACK_MIDI_TX,
                                   USB_DEVICE_AUDIO_CALLBACK_TX_COMPLETE,
                                   0,
                                   1,
                                   transferByteCount);
        }

    }

}

// *****************************************************************************



USB_ERROR_STATUS USB_DEVICE_AUDIO_MIDI_Write ( USB_DEVICE_AUDIO_CLIENT_HANDLE cHandle ,
                                          uint8_t interfaceNum ,
                                          USB_DEVICE_AUDIO_DATA_BUFFER_OBJECT* bufferObj )
{

    uint8_t streamInfIndex=0;

    //TODO find streamInfIndex

    if(audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].dataState != USB_DEVICE_AUDIO_INSTANCE_TX_READY)
    {
        return USB_ERROR_RETRY;
    }

    /* check if the handle passed is valid */
    if ( ( USB_DEVICE_AUDIO_MAX_INSTANCES <= cHandle ) || ( cHandle == USB_DEVICE_AUDIO_CLIENT_HANDLE_INVALID ) )
    {
        /* invalid handle */
        return USB_ERROR_INVALID_HANDLE;
    }

    /* Check if user passed valid buffer */
    if ( bufferObj == NULL )
    {
        /* return error */
        return USB_ERROR_INVALID_BUFFER;
    }


    /* most likely case */
    if ( audioInstance[cHandle].infCollection.streamInf[0].interfaceNum == interfaceNum )
    {

        streamInfIndex = 0;
    }

    else
    {
        //TODO find the required streaming interface index
        SYS_ASSERT ( false , "Invalid interface number " );
    }

    /* update the data OUT end point state to pending */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].dataState = USB_DEVICE_AUDIO_INSTANCE_TX_PENDING;

    /* Copy a reference of the application buffer for future use */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].bufferObject[0] = bufferObj;


    /* Place a transfer request to controller driver */
    audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].cdxferHandle[0] =

        DRV_USB_Device_TransferRequest ( audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].pipeHandle ,
                                         USB_XFER_BULK_READ ,
                                         ( int8_t* ) bufferObj->data ,
                                         bufferObj->dataLen ,
                                         USB_XFER_REGULAR ,
                                         &audioInstance[cHandle] ,
                                         USB_DEVICE_AUDIO_MIDITxDataCallBack );


    //refPipeHandle = audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[EP_STREAM_INDEX].pipeHandle;

    /* Check if controller driver accepted the request */
    if ( DRV_HANDLE_INVALID == audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].cdxferHandle[0] )
    {
        /* We are not checking why it failed because all the cases where it could fail
         * are already checked in the AUDIO layer. The only possibility of error here is the
         * non availability of slot in the controller driver's Q.*/

        /* prepare AUDIO to accept new requets */
        audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].dataState = USB_DEVICE_AUDIO_INSTANCE_RX_READY;

        /* Invalidate the buffer */
        audioInstance[cHandle].infCollection.streamInf[streamInfIndex].ep[0].bufferObject[0] = NULL;

        /* We dont want to inform the application via callback, because
         the application is given a return status right away */

        //while(1);

        /* return error. Inform the application to try after some time */
        return USB_ERROR_RETRY;
    }


    /* return success */
    return USB_ERROR_OK;

}






/*******************************************************************************
 End of File
 */
