/*******************************************************************************
 USB HOST MSD Class Driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_msd.c

  Summary:
    USB MSD Host class driver.

  Description:
    USB MSD Host class driver.
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


#include "system_config.h"
#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"
#include "usb/usb_host_msd.h"

// *****************************************************************************
/* MSD Host Instance structure

  Summary:
    Defines the MSD instance(s).

  Description:
    This data type defines the MSD instance(s). The number of instances is
    defined by the application using USB_HOST_MSD_INSTANCES_NUMBER.

  Remarks:
    This structure is private to the MSD.
 */

USB_HOST_MSD_INSTANCE  gUSBHostMSDInstance[USB_HOST_MSD_INSTANCES_NUMBER];

// *****************************************************************************
/* MSD Host driver structure

  Summary:
    Defines the Host driver structure required for the host layer.

  Description:
    This data type defines the host driver structure required for the
    host layer.

  Remarks:
    This structure is private to the USB Host stack.
 */

USB_HOST_DRIVER msdDriver =
{
    /*name of the driver */
   
    .initializeDeviceDriver = NULL ,
    .initializeInterfaceDriver = _USB_HOST_MSD_InterfaceInitialize ,
    .deInitializeDriver = _USB_HOST_MSD_DeInitialize ,
    .task           = USB_HOST_MSD_Tasks

};

/*************************************************************************/

/* Function:
 USB_ERROR      _USB_HOST_MSD_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *msdInstance
                                                       uint8_t  speed)

  Summary:
    Initialize the MSD host driver.

  Description:
    After enumeration Host will initialize the MSD driver

  Parameters:
     HC_DEVICE_ID                           id ,
     uint8_t                                interfaceId,
     uint8_t *                              msdinstance

  Returns:
    None
*/
 USB_ERROR      _USB_HOST_MSD_InterfaceInitialize(     HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *msdInstance,
                                                       uint8_t speed)
{
    USB_HOST_DRIVER_QUERY  msdQuery;
    USB_ERROR  status;
    USB_INTERFACE_DESCRIPTOR *interfaceDesc;
    USB_ENDPOINT_DESCRIPTOR *bulkInEndpointDesc ,
                            *bulkOutEndpointDesc ;
    USB_ENDPOINT_DESCRIPTOR controlEndpointDesc;
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    uint32_t  buffer;
    uint8_t     count;
    status = USB_ERROR_NONE;
    /* Find the free space for MSD instance*/
    for(count = 0 ; count < USB_HOST_MSD_INSTANCES_NUMBER ; count ++)
    {
        msdDriverInfo = &(gUSBHostMSDInstance[count]);
        if (msdDriverInfo->assigned == false )
            break;
    }
	/* validate the instance */
    if ( count >= USB_HOST_MSD_INSTANCES_NUMBER)
    {
        /* Assert on invalid MSD index */
        SYS_ASSERT ( false , "Invalid MSD instance number" );
        return USB_ERROR_HOST_DRIVER_INSTANCE_INVALID;
    }
    //  *msdinstance = count;
    msdDriverInfo->assigned = true;
    msdDriverInfo->msdDeviceId = id;
    msdDriverInfo->instanceNumber = count;
    msdDriverInfo->interfaceNumber = interfaceId;
    msdQuery.id = id;
    /* active configuration number will change after*/
    msdQuery.configurationNumber = 0;
    msdQuery.interfaceClass = USB_HOST_MSD_CLASS;
    msdQuery.interfaceSubClass = USB_HOST_MSD_SUBCLASS;
    msdQuery.interfaceProtocol = USB_HOST_MSD_PROTOCOL;
    /* class match */
    msdQuery.flags = USB_MATCH_CLASS;
    msdQuery.interfaceNumber = interfaceId;
    msdQuery.alternateSettingNumber = 0;
	/* Find interface */
    status = USB_HOST_FindInterface(&(msdQuery), &(interfaceDesc));
    if ( status != USB_ERROR_NONE)
        return USB_ERROR_HOST_DRIVER_INSTANCE_INVALID;
  
    /* Get control pipe information */
    controlEndpointDesc.bmAttributes =  (USB_TRANSFER_TYPE_CONTROL )& 0x03;
    msdDriverInfo->controlPipeHandle =  USB_HOST_PipeSetup
                                ( id ,  &controlEndpointDesc , speed );
    /* Fill Control IRP */
    msdDriverInfo->controlIRP.callback = _USB_HOST_MSD_ControlTransferComplete;
   /* Fine bulkIn endpoint descriptor */
    msdQuery.alternateSettingNumber = interfaceDesc->bAlternateSetting;
    msdQuery.endpointAddress = 0 ; // we have to get temp
    msdQuery.endpointType = USB_TRANSFER_TYPE_BULK;
    msdQuery.endpointDirection = USB_DATA_DIRECTION_DEVICE_TO_HOST ;
    msdQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    /* Find the Bulk in  endpoint descriptor */
    status = USB_HOST_FindEndpoint (&(msdQuery), &(bulkInEndpointDesc));
     if( status != USB_ERROR_NONE )
    {
        SYS_ASSERT ( false , "Bulk in endpoint not found " );
        return USB_ERROR_HOST_ENDPOINT_INVALID;
    }
    /* Create Bulkin pipe */
    msdDriverInfo->bulkInPipeHandle = USB_HOST_PipeSetup
                                ( id ,  bulkInEndpointDesc ,speed );
     if(msdDriverInfo->bulkInPipeHandle == NULL )
    {
        SYS_ASSERT ( false , "Bulk in  pipe is not created " );
        return USB_ERROR_HOST_PIPE_INVALID;
    }
    /* Fill Bulkin IRP */
    msdDriverInfo->bulkInIRP.callback =
                            (void * )_USB_HOST_MSD_BulkInTransferComplete;
   
    msdDriverInfo->bulkInIRP.size = bulkInEndpointDesc->wMaxPacketSize ;
    msdDriverInfo->bulkInIRP.userData = (uintptr_t)msdDriverInfo;
     /* Fill the msdQuery to find bulkOut endpoint */
    msdQuery.alternateSettingNumber = interfaceDesc->bAlternateSetting;
    msdQuery.endpointAddress = 0 ; // we have to get temp
    msdQuery.endpointType = USB_TRANSFER_TYPE_BULK;
    msdQuery.endpointDirection = USB_DATA_DIRECTION_HOST_TO_DEVICE;
    msdQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    /* Find the bulkout endpoint descriptor */
    status = USB_HOST_FindEndpoint (&(msdQuery), &(bulkOutEndpointDesc));
    /* Create Bulkout pipe */
    msdDriverInfo->bulkOutPipeHandle = USB_HOST_PipeSetup
                                ( id ,  bulkOutEndpointDesc , speed );
    /* Fill Bulk out piep */
    msdDriverInfo->bulkOutIRP.callback = _USB_HOST_MSD_BulkOutTransferComplete;
   
    msdDriverInfo->bulkOutIRP.size = bulkOutEndpointDesc->wMaxPacketSize ;
    msdDriverInfo->bulkOutIRP.userData = (uintptr_t )msdDriverInfo;
    /* State the default state for msd device */
    msdDriverInfo->msdState =  USB_HOST_MSD_STATE_INITIALIZE_DEVICE ;
     msdDriverInfo->msdSubState = SUBSTATE_HOLDING;
   //  _USB_HOST_MSD_reset( msdDriverInfo );
     msdDriverInfo->appEventCallBack(
                                    msdDriverInfo->instanceNumber,
                                    USB_HOST_MSD_EVENT_ATTACH,
                                    &buffer);
    return status;
}
/*************************************************************************/

/* Function:
   void  USB_HOST_MSD_DeInitialize(HC_DEVICE_ID id )

  Summary:
    DeInitialize the MSD host driver.

  Description:
    After deenumeration Host will Deinitialize the MSD driver

  Parameters:
     HC_DEVICE_ID                           id ,

  Returns:
        void
*/

void  _USB_HOST_MSD_DeInitialize(HC_DEVICE_ID id )
 {

      USB_HOST_MSD_INSTANCE *msdDriverInfo;
      uint8_t msdInstance;
      uint32_t buffer;
	  /* Find instance */
      msdInstance = _USB_HOST_MSD_findInstance( id );
      msdDriverInfo = &(gUSBHostMSDInstance[msdInstance]);
      /* Close MSD device related pipes */
      USB_HOST_PipeClose( msdDriverInfo->bulkInPipeHandle );
      USB_HOST_PipeClose( msdDriverInfo->bulkOutPipeHandle );
    //  USB_HOST_PipeClose( msdDriverInfo->controlPipeHandle );
       /* close the instance */
      msdDriverInfo->assigned = 0x0;
     // memset(msdDriverInfo , 0 ,sizeof( USB_HOST_MSD_INSTANCE));
	 /* inform to the msd device detach event to the application */
     msdDriverInfo->appEventCallBack ( msdDriverInfo->instanceNumber ,
                                        USB_HOST_MSD_EVENT_DETACH ,
                                        &buffer );
 }

/*************************************************************************/

/* Function:
   USB_HOST_MSD_HANDLE  USB_HOST_MSD_Open( uint8_t  instance )

  Summary:
   Application opens a MSD instance.

  Description:
    After deenumeration Host will Deinitialize the MSD driver

  Parameters:
  uint8_t                    instance;

  Returns:
   USB_HOST_MSD_HANDLE         msdHandle
*/

USB_HOST_MSD_HANDLE  USB_HOST_MSD_Open( uint8_t  instance )
{
    USB_HOST_MSD_INSTANCE  *msdDriverInfo;
    USB_HOST_MSD_HANDLE msdHandle;
    /* Get instance driver information */
    msdDriverInfo = &(gUSBHostMSDInstance[instance]);
    if(msdDriverInfo->assigned == 0x01 )
        msdHandle = (USB_HOST_MSD_HANDLE  )msdDriverInfo;
    else
        msdHandle = (USB_HOST_MSD_HANDLE  ) NULL;
    return msdHandle;
}
/****************************************************************************/
/* Function:
   void  USB_HOST_MSD_Close( USB_HOST_MSD_HANDLE msdHandle )

  Summary:
    Closes handle to an instance of the USB MSD driver.

  Description:
   This function closes an opened handle to an instance of the USB host msdlayer,
   invalidating the handle.

   Precondition:
    USB_HOST_MSD_Open must have been called to obtain a valid opened device handle.

  Parameters:
    USB_HOST_MSD_HANDLE msdHandle

  Returns:
      void
*/
void  USB_HOST_MSD_Close( USB_HOST_MSD_HANDLE msdHandle )
{
    USB_HOST_MSD_INSTANCE  *msdDriverInfo;
    msdDriverInfo = (USB_HOST_MSD_INSTANCE  *)msdHandle;
    //Invalidate the handle
    msdHandle = (USB_HOST_MSD_HANDLE  ) NULL;
}
/*************************************************************************/

/* Function:
  USB_HOST_MSD_RESULT USB_HOST_MSD_EventHandlerSet (
                                  USB_HOST_MSD_INSTANCE MSDindex ,
                                  USB_HOST_MSD_APP_EVENT_HANDLER appMSDHandler )

  Summary:
        Application or subclass will register the handler

  Description:


  Parameters:
    USB_HOST_MSD_INSTANCE               MSDindex ,
    USB_HOST_MSD_APP_EVENT_HANDLER      appMSDHandler
  Returns:
        USB_HOST_MSD_RESULT
*/
USB_HOST_MSD_RESULT USB_HOST_MSD_EventHandlerSet (
                                  USB_HOST_MSD_INDEX MSDindex ,
                                  USB_HOST_MSD_APP_EVENT_HANDLER appMSDHandler )
{
    /* check the validity of the function driver index */
    if ( ( MSDindex < 0 ) || ( MSDindex >= USB_HOST_MSD_INSTANCES_NUMBER ) )
    {
        /* invalid MSD index */
           return USB_HOST_MSD_INSTANCE_INVALID;
    }
    /* check if the given event handler is valid */
    if ( appMSDHandler )
    {
        /* update the event handler for this instance */
        gUSBHostMSDInstance[MSDindex].appEventCallBack = appMSDHandler;
        /* return success */
        return USB_HOST_MSD_RESULT_OK;
    }
    else
    {
        /* invalid event handler passed */
        return USB_HOST_MSD_INVALID_HANDLER;
    }
}
/*************************************************************************/

/* Function:
   uint8_t  _USB_HOST_MSD_findInstance(HC_DEVICE_ID id )

  Summary:
    Find the MSD instance

  Description:


  Parameters:
      HC_DEVICE_ID id

  Returns:
    uint8_t           instance
*/

uint8_t  _USB_HOST_MSD_findInstance(HC_DEVICE_ID id )
{
     USB_HOST_MSD_INSTANCE *msdDriverInfo;
     uint8_t                  count;
    for(count = 0 ; count < USB_HOST_MSD_INSTANCES_NUMBER ; count ++)
    {
        msdDriverInfo = &(gUSBHostMSDInstance[count]);
        if( USB_HOST_MATCH_HC_DEVICE_ID (msdDriverInfo->msdDeviceId, id))
         {
             return count;
         }
    }
    return 0;
}
/*************************************************************************/

/* Function:
   uint8_t  _USB_HOST_MSD_getDriveNumber( HC_DEVICE_ID  id )

  Summary:
    Find the drveNumber for theis MSD instance

  Description:


  Parameters:
      HC_DEVICE_ID id

  Returns:
    uint8_t           driveNumber
*/

uint8_t  _USB_HOST_MSD_getDriveNumber( HC_DEVICE_ID  id )
{
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    uint8_t          count;
      for( count = 0 ; count < USB_HOST_MSD_INSTANCES_NUMBER ; count ++)
    {
        msdDriverInfo = &(gUSBHostMSDInstance[count]);
        if( USB_HOST_MATCH_HC_DEVICE_ID (msdDriverInfo->msdDeviceId, id))
         {
             return msdDriverInfo->driveNumber ;
         }
      }
       return USB_HOST_DRIVE_NOT_FOUND;
}

/*************************************************************************/

/* Function:
   USB_HOST_MSD_INSTANCE *   _USB_HOST_MSD_getDriveInfo  ( uint8_t driveNumber )

  Summary:
  Get the Driver information for this driveNumber

  Description:


  Parameters:
      HC_DEVICE_ID id

  Returns:
    uint8_t           driveNumber
*/

USB_HOST_MSD_INSTANCE *   _USB_HOST_MSD_getDriveInfo  ( uint8_t driveNumber )
{
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    uint8_t                  count;
	/* find instance driver info */
    for(count = 0 ; count < USB_HOST_MSD_INSTANCES_NUMBER ; count ++)
    {
        msdDriverInfo = &(gUSBHostMSDInstance[count]);
        if( (msdDriverInfo->driveNumber ==  driveNumber))
        {
            return msdDriverInfo ;
        }
    }
     return NULL;
}

/*************************************************************************/

/* Function:
   USB_HOST_MSD_RESULT  _USB_HOST_MSD_getMaxLun( USB_HOST_MSD_INSTANCE *msdDriverInfo )

  Summary:
   This function request the LUN number of MSD device.

  Description:


  Parameters:
     USB_HOST_MSD_INSTANCE *msdDriverInfo

  Returns:
    USB_HOST_MSD_RESULT
*/

 USB_HOST_MSD_RESULT  _USB_HOST_MSD_getMaxLun( USB_HOST_MSD_INSTANCE *msdDriverInfo )
{
	/* Fill setup packet */
    msdDriverInfo->setupPacket[0] = 0x21; //interface
    msdDriverInfo->setupPacket[1] =  USB_MSD_GET_MAX_LUN ;
    msdDriverInfo->setupPacket[2] = 0x00;
    msdDriverInfo->setupPacket[3] = 0x00;
    msdDriverInfo->setupPacket[4] = 0x00;
    msdDriverInfo->setupPacket[5] = msdDriverInfo->interfaceNumber;
    msdDriverInfo->setupPacket[6] = 0x00;
    msdDriverInfo->setupPacket[7] = 0x00;
	/* Fill IRP */
    msdDriverInfo->controlIRP.data = &( msdDriverInfo->logicalUnitNumber ) ;
    msdDriverInfo->controlIRP.flags = 0x00;
    msdDriverInfo->controlIRP.size = 0x1;
    msdDriverInfo->controlIRP.setup = msdDriverInfo->setupPacket;
    msdDriverInfo->msdState =  USB_HOST_MSD_STATE_INITIALIZE_DEVICE;
    msdDriverInfo->msdSubState  = SUBSTATE_SEND_GET_MAX_LUN;
	return USB_HOST_MSD_RESULT_OK;
}
/*************************************************************************/

/* Function:
   USB_HOST_MSD_RESULT  _USB_HOST_MSD_reset( USB_HOST_MSD_INSTANCE *msdDriverInfo )

  Summary:
  Reset the Mass storage device

  Description:


  Parameters:
     USB_HOST_MSD_INSTANCE *msdDriverInfo

  Returns:
    USB_HOST_MSD_RESULT
*/

USB_HOST_MSD_RESULT  _USB_HOST_MSD_reset( USB_HOST_MSD_INSTANCE *msdDriverInfo )
{
	/* Fill setup packet */
    msdDriverInfo->setupPacket[0] = 0x21; //interface
    msdDriverInfo->setupPacket[1] =  USB_MSD_RESET ;
    msdDriverInfo->setupPacket[2] = 0x00;
    msdDriverInfo->setupPacket[3] = 0x00;
    msdDriverInfo->setupPacket[4] = 0x00;
    msdDriverInfo->setupPacket[5] = msdDriverInfo->interfaceNumber;
    msdDriverInfo->setupPacket[6] = 0x00;
    msdDriverInfo->setupPacket[7] = 0x00;
	/* Fill IRP */
    msdDriverInfo->bulkOutIRP.data = NULL;
    msdDriverInfo->bulkOutIRP.flags = 0x00;
    msdDriverInfo->bulkOutIRP.size = 0x00;
    msdDriverInfo->controlIRP.setup = msdDriverInfo->setupPacket;
	/* set msd task state for submit IRP */
    msdDriverInfo->msdState =  USB_HOST_MSD_STATE_RESET_RECOVERY;
    msdDriverInfo->msdSubState  = SUBSTATE_SEND_RESET;
    return USB_HOST_MSD_RESULT_OK;
}
/*************************************************************************/
/* Function:
   void USB_HOST_MSD_Tasks(void)

  Summary:
        State machine of the MSD device

  Description:


  Parameters:
        None

  Returns:
        None
 */
void USB_HOST_MSD_Tasks(void)
{
    uint8_t instance;
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    uint32_t buffer;
    uint8_t TransferStatus;
    /* find instance */
    for (instance = 0; instance < USB_HOST_MSD_INSTANCES_NUMBER; instance++)
    {
        msdDriverInfo = &(gUSBHostMSDInstance[instance]);
        if (msdDriverInfo->assigned == 0x00)
            continue;
        switch (msdDriverInfo->msdState)
        {
            case USB_HOST_MSD_STATE_DETACHED:
                /* send detach event to the application*/
                msdDriverInfo->appEventCallBack(msdDriverInfo->instanceNumber,
                                    USB_HOST_MSD_EVENT_DETACH,
                                    &buffer);
                break;
           case USB_HOST_MSD_STATE_INITIALIZE_DEVICE:
                if (msdDriverInfo->msdDeviceId.deviceID > 0)
                {
                    msdDriverInfo->msdSubState = SUBSTATE_WAIT_FOR_ENUMERATION;
                }

                switch (msdDriverInfo->msdSubState)
                {
                   case SUBSTATE_WAIT_FOR_ENUMERATION:
                       break;
                    case SUBSTATE_SEND_GET_MAX_LUN:
                        msdDriverInfo->msdSubState = SUBSTATE_WAIT_FOR_MAX_LUN;
                       USB_HOST_IRPSubmit(msdDriverInfo->controlPipeHandle,
                                &(msdDriverInfo->controlIRP));
                        
                        break;
                    case SUBSTATE_WAIT_FOR_MAX_LUN:
                       if (msdDriverInfo->controlIRP.status ==
                                USB_HOST_IRP_STATUS_COMPLETED)
                       {
                            buffer = msdDriverInfo->logicalUnitNumber;
                              msdDriverInfo->msdState = USB_HOST_MSD_STATE_RUNNING;
                            msdDriverInfo->msdSubState = SUBSTATE_HOLDING;
                            msdDriverInfo->appEventCallBack(
                                            msdDriverInfo->instanceNumber,
                                            USB_HOST_MSD_EVENT_MAX_LUN,
                                            &buffer);
                          
                        }
                        if (msdDriverInfo->controlIRP.status < 0) {
                            msdDriverInfo->msdState = USB_HOST_MSD_STATE_HOLDING;
                            USB_HOST_ClearEndpointHalt(
                                                msdDriverInfo->msdDeviceId, 0);
                            
                       }
                       break;
               }
               break;
           case USB_HOST_MSD_STATE_RUNNING:
               switch (msdDriverInfo->msdSubState)
               {
                    case SUBSTATE_HOLDING:
                        break;
                    case SUBSTATE_SEND_CBW:
                         msdDriverInfo->msdSubState = SUBSTATE_CBW_WAIT;
                        USB_HOST_IRPSubmit(msdDriverInfo->bulkOutPipeHandle,
                                &(msdDriverInfo->bulkOutIRP));
                       
                        break;
                    case SUBSTATE_CBW_WAIT:
                       if (msdDriverInfo->bulkOutIRP.status ==
                                            USB_HOST_IRP_STATUS_COMPLETED)
                       {
                            if (msdDriverInfo->msdCBW.dCBWDataTransferLength == 0)
                            {
                                msdDriverInfo->msdSubState = SUBSTATE_REQUEST_CSW;
                            } 
                            else
                            {
                                msdDriverInfo->msdSubState = SUBSTATE_TRANSFER_DATA;
                            }
                        }

                       else if (msdDriverInfo->bulkOutIRP.status < 0)
                        {

                        }
                        break;
                    case SUBSTATE_TRANSFER_DATA:
                        /* if payload is available*/
                        if (msdDriverInfo->msdCBW.dCBWDataTransferLength)
                        {
                            if (msdDriverInfo->msdCBW.bCBWFlags == 
                                                    USB_MSD_CBW_FLAG_IN)
                            {
                                msdDriverInfo->bulkInIRP.flags = 0x00;
                                msdDriverInfo->bulkInIRP.data =
                                                msdDriverInfo->msdCommand->data;
                                msdDriverInfo->bulkInIRP.size =
                                            msdDriverInfo->msdCommand->length;
                                msdDriverInfo->msdSubState = SUBSTATE_IN_TRANSFER_WAIT;
                                USB_HOST_IRPSubmit(msdDriverInfo->bulkInPipeHandle,
                                        &(msdDriverInfo->bulkInIRP));
                                
                            } else {
                                msdDriverInfo->bulkOutIRP.flags = 0x00;
                                msdDriverInfo->bulkOutIRP.data =
                                                msdDriverInfo->msdCommand->data;
                                msdDriverInfo->bulkOutIRP.size =
                                        msdDriverInfo->msdCommand->length;
                                msdDriverInfo->msdSubState =
                                        SUBSTATE_OUT_TRANSFER_WAIT;
                                USB_HOST_IRPSubmit(msdDriverInfo->bulkOutPipeHandle,
                                        &(msdDriverInfo->bulkOutIRP));
                                
                            }
                        }
                        break;
                    case SUBSTATE_IN_TRANSFER_WAIT:
                        if (msdDriverInfo->bulkInIRP.status ==
                                            USB_HOST_IRP_STATUS_COMPLETED)
                        {
                            msdDriverInfo->msdSubState = SUBSTATE_REQUEST_CSW;
                        }
                        else if ((msdDriverInfo->bulkInIRP.status ==
                                USB_HOST_IRP_STATUS_COMPLETED_SHORT) )
                        {
                            msdDriverInfo->msdSubState = SUBSTATE_REQUEST_CSW;
                        }
                        else if (msdDriverInfo->bulkInIRP.status < 0) {
                        }
                        break;
                    case SUBSTATE_OUT_TRANSFER_WAIT:
                        if (msdDriverInfo->bulkOutIRP.status ==
                                USB_HOST_IRP_STATUS_COMPLETED)
                        {
                            msdDriverInfo->msdSubState = SUBSTATE_REQUEST_CSW;
                        }
                        else if (msdDriverInfo->bulkOutIRP.status < 0) {
                        }
                        break;
                    case SUBSTATE_REQUEST_CSW:
                        msdDriverInfo->bulkInIRP.flags = 0x00;
                        msdDriverInfo->bulkInIRP.data = &msdDriverInfo->msdCSW;
                        msdDriverInfo->bulkInIRP.size = 0x0D;
                        msdDriverInfo->msdSubState = SUBSTATE_CSW_WAIT;
                        USB_HOST_IRPSubmit(msdDriverInfo->bulkInPipeHandle,
                                &(msdDriverInfo->bulkInIRP));
                        
                        break;
                    case SUBSTATE_CSW_WAIT:
                        if (msdDriverInfo->bulkInIRP.status ==
                                USB_HOST_IRP_STATUS_COMPLETED) {
                            msdDriverInfo->msdSubState = SUBSTATE_TRANSFER_DONE;
                        }
                        else if (msdDriverInfo->bulkInIRP.status < 0) {
                        }
                        break;
                    case SUBSTATE_TRANSFER_DONE:

                        TransferStatus =
                        _USB_HOST_MSD_validateCSW(msdDriverInfo->msdCSW,
                                 msdDriverInfo->msdCommand);
                        if( TransferStatus == USB_MSD_CSW_STATUS_SUCCESS)
                        {
                           msdDriverInfo->msdCommand->commandStatus = 0x00;
                        }
                        else
                        {
                          msdDriverInfo->msdCommand->commandStatus =
                                                    USB_MSD_TRANSFER_FAIL;
                        }
                        break;
                }
                break;
            case USB_HOST_MSD_STATE_RESET_RECOVERY:
                switch (msdDriverInfo->msdSubState) {
                    case SUBSTATE_SEND_RESET:
                        msdDriverInfo->msdSubState = SUBSTATE_WAIT_FOR_RESET;
                        USB_HOST_IRPSubmit(msdDriverInfo->controlPipeHandle,
                                &(msdDriverInfo->controlIRP));
                        
                        break;
                    case SUBSTATE_WAIT_FOR_RESET:
                        if (msdDriverInfo->controlIRP.status ==
                                USB_HOST_IRP_STATUS_COMPLETED) {
                            msdDriverInfo->appEventCallBack(
                                    msdDriverInfo->instanceNumber,
                                    USB_HOST_MSD_EVENT_ATTACH,
                                    &buffer);
                            msdDriverInfo->msdSubState = SUBSTATE_HOLDING;
                        }
                        if (msdDriverInfo->controlIRP.status < 0)
                        {
                            // Clear the STALL.  Since it is EP0, we do not have to clear the stall.
                            USB_HOST_ClearEndpointHalt(msdDriverInfo->msdDeviceId, 0);
                            msdDriverInfo->msdState = USB_HOST_MSD_STATE_HOLDING;
                        }
                        break;
                }
                break;
            case USB_HOST_MSD_STATE_CLEAR_DATA_IN:
                switch (msdDriverInfo->msdSubState) {
                    case SUBSTATE_SEND_CLEAR_IN:
                        break;
                    case SUBSTATE_WAIT_FOR_CLEAR_IN:
                        break;
                    case SUBSTATE_CLEAR_IN_COMPLETE:
                        break;
                }
                break;
            case USB_HOST_MSD_STATE_CLEAR_DATA_OUT:
                switch (msdDriverInfo->msdSubState) {
                    case SUBSTATE_SEND_CLEAR_OUT:
                        break;
                    case SUBSTATE_WAIT_FOR_CLEAR_OUT:
                        break;
                    case SUBSTATE_CLEAR_OUT_COMPLETE:
                        break;
                }
                break;
            case USB_HOST_MSD_STATE_HOLDING:
                break;
        }
    }
}
/*************************************************************************/
/* Function:
uint8_t _USB_HOST_MSD_validateCSW( USB_MSD_CSW csw, USB_MSD_COMMAND * msdCommand)

  Summary:
 validate the CSW status and signatures

  Description:


  Parameters:
        None

  Returns:
        None
 */
uint8_t _USB_HOST_MSD_validateCSW( USB_MSD_CSW csw, USB_MSD_COMMAND * msdCommand)
{
    if ( csw.dCSWSignature != USB_MSD_VALID_CSW_SIGNATURE )
        return USB_MSD_CSW_SIGNATURE_INVALID ;

    if (csw.dCSWTag !=  USB_MSD_VALID_CBW_TAG )
        return USB_MSD_CSW_TAG_INVALID ;
    if(csw.bCSWStatus != USB_MSD_CSW_STATUS_GOOD)
       return USB_MSD_TRANSFER_FAIL;



    return USB_MSD_CSW_STATUS_SUCCESS;
}
/*************************************************************************/

/* Function:
   uint8_t _USB_HOST_MSD_BulkInTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkin IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/

 uint8_t _USB_HOST_MSD_BulkInTransferComplete(USB_HOST_IRP *irp)
 {
    USB_HOST_MSD_TRANSFER_HANDLE rxHandle;
    uint16_t data;
    uint8_t msdInstance;
    static uint8_t errorCount = 0;
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    if (irp->status == USB_HOST_IRP_STATUS_COMPLETED || irp->status == USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        msdDriverInfo = ((USB_HOST_MSD_INSTANCE *) (irp->userData));
        msdInstance = msdDriverInfo->instanceNumber;
        rxHandle = msdDriverInfo->rxHandle;
        data = irp->size;
        /* inform the application */
      //  msdDriverInfo->appEventCallBack(msdInstance,
      //                                   USB_HOST_MSD_EVENT_READ_COMPLETE,&data);
        return true; // Bulkin successfull
    }
    else
    {
       // handle error status
        errorCount++;
    }
    return false;
}

  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_MSD_BulkOutTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkout IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/
void _USB_HOST_MSD_BulkOutTransferComplete( USB_HOST_IRP *irp)
{

   USB_HOST_MSD_TRANSFER_HANDLE txHandle;
    uint16_t data;
    uint8_t msdInstance;
    USB_HOST_MSD_INSTANCE *msdDriverInfo;
    static uint8_t errorCount = 0;
    if (irp->status == USB_HOST_IRP_STATUS_COMPLETED || irp->status == USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        msdDriverInfo = ((USB_HOST_MSD_INSTANCE *) (irp->userData));
        msdInstance = msdDriverInfo->instanceNumber;
        txHandle = msdDriverInfo->txHandle;
        data = irp->size;
        /* inform the application */
    //    msdDriverInfo->appEventCallBack(msdInstance,
    //                            USB_HOST_MSD_EVENT_WRITE_COMPLETE, &data);
        errorCount = 0; // Bulk out successfull
    }
}
/*************************************************************************/

/* Function:
   _USB_HOST_MSD_ControlTransferComplete( USB_HOST_IRP *irp)

  Summary:
        Call back function for controltransfer status

  Description:


  Parameters:
      USB_HOST_IRP *irp

  Returns:
   void
*/

void _USB_HOST_MSD_ControlTransferComplete( USB_HOST_IRP *irp)
{
  USB_HOST_MSD_INSTANCE *msdDriverInfo;
     USB_HOST_STATUS status;
     msdDriverInfo = ((USB_HOST_MSD_INSTANCE *) (irp->userData));
     if(irp->status != USB_HOST_IRP_STATUS_COMPLETED )
    {
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT)
        {
            // Timing problem will resend the same packet
        }
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_DATA ||
                 irp->status == USB_HOST_IRP_STATUS_ERROR_BUS )
        {
            // Resend the request
        }
          if( irp->status == USB_HOST_IRP_STATUS_ERROR_STALL)
        {
              status = USB_HOST_ClearEndpointHalt (msdDriverInfo->msdDeviceId ,
                      (uint8_t )0 );
            //clear the stall
        }
     }

}
/*************************************************************************/
/* Function:
USB_ERROR USB_HOST_MSD_Transfer (uint8_t driveNumber, USB_MSD_COMMAND *msdCommand)

  Summary:
        Transfer the data to/from the MSD

  Description:


  Parameters:
       uint8_t        driveNumber
   USB_MSD_COMMAND      *msdCommand
  Returns:
       USB_ERROR                             status
*/



USB_ERROR USB_HOST_MSD_Transfer (uint8_t driveNumber, USB_MSD_COMMAND *msdCommand)
{
    USB_HOST_STATUS status;
    uint8_t         count;
    USB_HOST_MSD_INSTANCE *msdDriverInfo;

    status  = USB_HOST_SUCCESS;
	/* Get drive info */
    msdDriverInfo  = _USB_HOST_MSD_getDriveInfo  (  driveNumber );
	/* Fill CBW */
    msdDriverInfo->msdCommand = msdCommand;
    msdDriverInfo->msdCBW.dCBWSignature = USB_MSD_VALID_CBW_SIGNATURE ;
    msdDriverInfo->msdCBW.dCBWTag = USB_MSD_VALID_CBW_TAG;
    msdDriverInfo->msdCBW.dCBWDataTransferLength = msdCommand->length;
    if ( msdCommand ->direction == 0x01 )
    msdDriverInfo->msdCBW.bCBWFlags = USB_MSD_CBW_FLAG_IN ;
    else
         msdDriverInfo->msdCBW.bCBWFlags = USB_MSD_CBW_FLAG_OUT ;
    msdDriverInfo->msdCBW.bCBWLUN = 0x00;
    msdDriverInfo->msdCBW.bCBWCBLength = msdCommand->commandLength;
    for ( count = 0 ; count<16 ; count++)
        msdDriverInfo->msdCBW.CBWCB[count] = 0x00;

    for( count = 0 ; count < msdCommand->commandLength ; count++)
        msdDriverInfo->msdCBW.CBWCB[count] = * (uint8_t *)( msdCommand->command + count );
    /* Fill irp */
   // msdDriverInfo->bulkoutIRP.status =
    msdDriverInfo->bulkOutIRP.flags = 0x00;
    msdDriverInfo->bulkOutIRP.data = & msdDriverInfo->msdCBW ;
    msdDriverInfo->bulkOutIRP.size =  0x1F;
    msdDriverInfo->msdState =  USB_HOST_MSD_STATE_RUNNING;
    msdDriverInfo->msdSubState = SUBSTATE_SEND_CBW ;
    return USB_ERROR_NONE;
}



/***************  End of  File ************************************/





