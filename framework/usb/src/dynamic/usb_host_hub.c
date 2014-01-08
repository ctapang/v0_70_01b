

#include "usb/usb_host.h"
#include "usb/usb_hub.h"

USB_HUB_OBJ         gUsbHubObj;

USB_HOST_DRIVER hubDriver =
{
    /*name of the driver */
//    .driverName[20] = "cdc_acm_driver" ,
    .initializeDeviceDriver = NULL ,
    .initializeInterfaceDriver = USB_HOST_HUB_interfaceInitialize ,
    .deInitializeDriver = USB_HOST_HUB_DeInitialize ,
    .matchFlag       = USB_MATCH_CLASS ,
    .task           = USB_HOST_HUB_task,
    .driverName     = "HUB "

};

USB_STATUS      USB_HOST_HUB_interfaceInitialize(HC_DEVICE_ID id , uint8_t interfaceId,  uint8_t *hubInstance)
{
    USB_HOST_DRIVER_QUERY  hubQuery;
    USB_ENDPOINT_DESCRIPTOR *interruptInendPointDesc;
    /* standard configuration descriptor */
    USB_CONFIGURATION_DESCRIPTOR *configurationDescriptor;
    USB_HOST_HUB_DESCRIPTOR *hubDesc;
    USB_STATUS  status;
    uint8_t    selfPoweredHub = 0;
    uint8_t    portCount = 0;
    USB_HOST_HUB_DRIVER_INFO *hubInfo;
    USB_HOST_HUB_STATUS  portStatus ;
    uint8_t      portNumber;
    USB_ENDPOINT_DESCRIPTOR controlendPointDesc;
    static uint8_t instance = 0;
    //*hubInstance = instance ;
    hubInfo =  &(gUsbHubObj.hubList[instance]);

    hubQuery.id = id;
    /* active configuration number will change after*/
    hubQuery.configurationNumber = 0 ;

        /* class match */
   //TODO hubQuery.flags = USB_MATCH_ONLY_ACTIVE_ALT_STTG;

    hubQuery.interfaceNumber = interfaceId;

    hubQuery.alternateSettingNumber = 0;

    hubQuery.endpointAddress = 0 ; // we have to get temp
    hubQuery.endpointType = 3;
    hubQuery.endpointDirection = USB_DIR_IN;
    hubQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    status = USB_HOST_FindEndpoint (&(hubQuery), &(interruptInendPointDesc));
    hubInfo->interruptinpipeHandle = USB_HOST_PipeSetup ( id ,  interruptInendPointDesc , USB_SPEED_FULL );

   

    status = USB_HOST_getActiveConfigDesc (id, &configurationDescriptor);

        /* initialize the hub  */

     for (portCount  = 0; portCount < HUB_MAX_SUPPORTS_DEVICES ; portCount++)
    {
         hubInfo->children[portCount].hostcontrollerID = id.hostcontrollerID ;

    }

      /* check if the hub is a self powered or bus powered    */

    selfPoweredHub = ((configurationDescriptor->bmAttributes) & 0x40);

    if(selfPoweredHub)
    {
        /* No need to give power for self powered hubs */
        hubInfo->power = 0;
    }
    else
    {
           hubInfo->power = 200; /* as per spec 7.2*/
    }

    /* Fill Control IRP */

    controlendPointDesc.bmAttributes =  (USB_TRANSFER_TYPE_CONTROL )& 0x03;
    hubInfo->controlpipeHandle =  USB_HOST_PipeSetup ( id ,  &controlendPointDesc , USB_SPEED_FULL );
    hubInfo->controlTransferIRP.callback = USB_HOST_HUB_controlTransferComplete;
    hubInfo->controlTransferIRP.status  = USB_HOST_IRP_STATUS_PENDING;

    /* pipe info */

     //TODO
    hubInfo->hubState = HUB_NORMAL;

    hubInfo->hubId = id;

    hubInfo->errors = 0;
    /* create 2 status IRPs */
    hubInfo->hubStatusIRP[0].hubInfo = hubInfo;
    hubInfo->hubStatusIRP[0].index = 0;
    hubInfo->hubStatusIRP[0].interuptinIrp.callback = USB_HOST_HUB_interruptTransferComplete;
    hubInfo->hubStatusIRP[0].interuptinIrp.status = USB_HOST_IRP_STATUS_PENDING;
    hubInfo->hubStatusIRP[0].interuptinIrp.userData = &(hubInfo->hubStatusIRP[0]);
    hubInfo->hubStatusIRP[0].interuptinIrp.size = 1;
    hubInfo->hubStatusIRP[0].interuptinIrp.data = &(hubInfo->hubStatusIRP[0].portStatus[0]);


    hubInfo->hubStatusIRP[1].hubInfo = hubInfo;
    hubInfo->hubStatusIRP[1].index = 1;
    hubInfo->hubStatusIRP[1].interuptinIrp.callback = USB_HOST_HUB_interruptTransferComplete;
    hubInfo->hubStatusIRP[1].interuptinIrp.status = USB_HOST_IRP_STATUS_PENDING;
    hubInfo->hubStatusIRP[1].interuptinIrp.data = &(hubInfo->hubStatusIRP[1].portStatus[0]);
    hubInfo->hubStatusIRP[1].interuptinIrp.size = 1;
    hubInfo->hubStatusIRP[1].interuptinIrp.userData = &(hubInfo->hubStatusIRP[1]);


    // deviceAddress = id;
    // endPointAddress =  interruptInendPointDesc->epAddress;
    // endPointdirection  =  interruptInendPointDesc->dirn;

      status = _usb_host_getHubDescriptor (hubInfo);

        _usb_host_hub_getStatus(hubInfo, &portStatus, 0 , HUB_REQUEST);

        for (portNumber = 1; portNumber <= hubInfo->hubDesc.bNbrPorts; portNumber++)
        {
            _usb_host_hub_getStatus (hubInfo, &portStatus, portNumber , PORT_REQUEST );  //requestType is valid only if hubstatus
            _usb_host_hub_setFeature (hubInfo, portNumber , HUB_PORT_POWER ,USB_HOST_HUB_COMMAND_SET_FEATURE, PORT_REQUEST );
        }

    /* submit the status irp */
     USB_HOST_IRPSubmit(hubInfo->interruptinpipeHandle, &(hubInfo->hubStatusIRP[0].interuptinIrp));
   
            instance ++;
}
/*****************************************************************************/



void  USB_HOST_HUB_controlTransferComplete( USB_HOST_IRP *irp)
{
   static uint8_t   errorCount = 0 ;
    if( irp->status == USB_HOST_IRP_STATUS_COMPLETED )
          gUsbHubObj.completedRequest++;
    else
        errorCount++;

}

void  USB_HOST_HUB_interruptTransferComplete(USB_HOST_IRP *irp )
{
    USB_HOST_HUB_DRIVER_INFO *hubinfo ;
    USB_HOST_HUB_IRP   *hubIrp;
    uint8_t             index;

    hubinfo = (( USB_HOST_HUB_IRP *)irp->userData)->hubInfo;
    hubIrp = (( USB_HOST_HUB_IRP *)irp->userData);
    index = hubIrp->index;

 

    if (hubinfo->hubcount != 0)
    {
        hubinfo->hubcount--;
    }

     if ( hubinfo->hubState == HUB_SHUTDOWN)
     {
         return;  // No more irps
     }
      else if ( hubinfo->hubState == HUB_DIRTY)
    {
        if (hubinfo->hubcount == 0)
        {
            /* make invalid id */
            hubinfo->hubId.hostcontrollerID = 0;
          
        }
        return;
    }

     gUsbHubObj.eventList[index] = *irp;
     gUsbHubObj.pendingEvent = true;

    // USB_HOST_HUB_task();
      // TODO update the event list
}

/*************************************************************************/


USB_STATUS _usb_host_getHubDescriptor( USB_HOST_HUB_DRIVER_INFO *hubInfo )
{
    USB_HOST_IRP  *controlIrp;

    controlIrp    = &(hubInfo->controlTransferIRP );

    hubInfo->setupPacket[0] =  0xA0;
    hubInfo->setupPacket[1] = 0x06;
    hubInfo->setupPacket[2] = 0x00;
    hubInfo->setupPacket[3] = 0x29;
    hubInfo->setupPacket[4] = 0x00;
    hubInfo->setupPacket[5] = 0x00;
    hubInfo->setupPacket[6] = 0x09; // this may change
    hubInfo->setupPacket[7] = 0x00;

    controlIrp->setup = hubInfo->setupPacket;
    controlIrp->data = &(hubInfo->hubDesc );
    controlIrp->size = 0x09 ; //TODO change
    USB_HOST_IRPSubmit(hubInfo->controlpipeHandle, controlIrp );

    //TO be removed
    while( 1 )
    {
       if ( controlIrp->status == USB_HOST_IRP_STATUS_COMPLETED )
           break;
    }

}

/**********************************************************************/

void  _usb_host_hub_getStatus (USB_HOST_HUB_DRIVER_INFO *hubInfo, USB_HOST_HUB_STATUS  *hubStatus , uint8_t portNumber , uint8_t requestType)
 {
     uint8_t bmRequest ;
     USB_HOST_IRP *controlIrp;
     uint32_t  data;

      controlIrp = & (hubInfo->controlTransferIRP ) ;

     if ( requestType == PORT_REQUEST )
     {
         hubInfo->setupPacket[0] =  0xA3;
     }

     if (requestType == HUB_REQUEST )
     {
         hubInfo->setupPacket[0] =  0xA0;
         portNumber = 0x0;
     }


    hubInfo->setupPacket[1] = 0x00;   //brequest command get status
    hubInfo->setupPacket[2] = 0x00;
    hubInfo->setupPacket[3] = 0x00;   // wvalue is zero
    hubInfo->setupPacket[4] = portNumber ;
    hubInfo->setupPacket[5] = 0x00;  // windex is port number
    hubInfo->setupPacket[6] = 0x04;
    hubInfo->setupPacket[7] = 0x00; // wlength is 4 bytes

    controlIrp->setup = hubInfo->setupPacket;
    controlIrp->data = &data;
    controlIrp->size = 0x4; //TODO change
    USB_HOST_IRPSubmit(hubInfo->controlpipeHandle, &(hubInfo->controlTransferIRP ) );

    while (1)
    {

        /* state machine after data is completed */
        if (controlIrp->status == USB_HOST_IRP_STATUS_COMPLETED)
        {
            hubStatus->status = (uint16_t) (data & 0xFFFF);
            hubStatus->change = (uint16_t) ((data >> 16) & 0x00FFFF);
            break;
        }
        else
        {

            hubStatus->status = 0x00;
            hubStatus->change = 0x00;
           
        }
    }
   
}


/*******************************************************************/

USB_STATUS _usb_host_hub_setFeature (USB_HOST_HUB_DRIVER_INFO * hubInfo, uint8_t portNumber ,uint8_t Feature, uint8_t hubCommand ,uint8_t requestType )

{
     uint8_t bmRequest ;
     USB_HOST_IRP *controlIrp;
     uint32_t  data;

      controlIrp = & (hubInfo->controlTransferIRP ) ;

     if ( requestType == PORT_REQUEST )
     {
         hubInfo->setupPacket[0] =  0x23;        // bmrequest
     }

     if (requestType == HUB_REQUEST )
     {
         hubInfo->setupPacket[0] =  0x20;
         portNumber = 0x0;
     }

      hubInfo->setupPacket[1] = hubCommand ;   //brequest is command

    hubInfo->setupPacket[2] =  (Feature & 0xFF )  ;
    hubInfo->setupPacket[3] =  (Feature & 0xFF00 ) >> 7;   // wvalue is zero
    hubInfo->setupPacket[4] = portNumber;
    hubInfo->setupPacket[5] = 0x00;  // windex is port number
    hubInfo->setupPacket[6] = 0x00;
    hubInfo->setupPacket[7] = 0x00; // wlength is 4 bytes

      controlIrp->setup = hubInfo->setupPacket;
    controlIrp->data = NULL;
    controlIrp->size = 0x00; //TODO change
    USB_HOST_IRPSubmit(hubInfo->controlpipeHandle, controlIrp );

    while( 1 )
    {
        /* state machine after data is completed */
        if (controlIrp->status == USB_HOST_IRP_STATUS_COMPLETED)
        {
            break;
       }
     }

}







/**************************************************************/

USB_HOST_HUB_DRIVER_INFO*  _usb_host_find_hubInfo(HC_DEVICE_ID id )

{
    USB_HOST_HUB_DRIVER_INFO            *hubInfo;
    uint8_t                              count;

    for ( count = 0 ; count < USB_MAX_HUB_SUPPORTED ; count++)
    {
         hubInfo = &(gUsbHubObj.hubList[count]);
         if( USB_HOST_MATCH_HC_DEVICE_ID (hubInfo->hubId, id))
         {
             return hubInfo;

         }

    }
}



/******************************************************************/



/****************************************************************/



/********************************************************************/
// process the events
void USB_HOST_HUB_task( void )
{
    USB_HOST_IRP *irp , *nextirp;
    USB_HOST_HUB_DRIVER_INFO            *hubInfo;
    uint8_t count;
    HC_DEVICE_ID parentDeviceId;
    uint8_t  irpIndex , nextirpIndex ;
    uint32_t  data;

   if( gUsbHubObj.pendingEvent == true )
   {
    for ( count = 0; count < USB_HOST_HUB_EVENTS_SUPPORTED ; count++)
    {
        gUsbHubObj.pendingEvent = false;
        irp = &(gUsbHubObj.eventList[count]);

        hubInfo = ((USB_HOST_HUB_IRP *) irp->userData)->hubInfo ;

        if( irp->status != USB_HOST_IRP_STATUS_COMPLETED)
        {
             /* check the errors */
            //TODO
            while(1);
             // Get parent information
            parentDeviceId.hostcontrollerID =  hubInfo->hubId.hostcontrollerID;
            // Get the port information
            //find hub
            //shut down the hub

        }
        else
        {
            // clear all errors
            hubInfo->errors = 0x00;

            // while processing we have to remove from the eventlist;
            
            // submit another IRP
               irpIndex = ((USB_HOST_HUB_IRP *) irp->userData)->index ;
               nextirpIndex = ( irpIndex + 1 ) % HUB_STATUS_IRP ;
             
               /* submit the status irp */
         //  USB_HOST_IRPSubmit(hubInfo->interruptinpipeHandle, &(hubInfo->hubStatusIRP[nextirpIndex].interuptinIrp));

               /* Handle the success irp */
                data = *(uint32_t * )irp->data ;

                if(data & 0x01) //Hub status changed
                {
                    //process the hub status change
                    while(1); //TO be implemented
                  //  USB_HOST_HUB_statusChange(hubInfo);

                }
                data =  data & ~0x01;

                if( data)
                {
                    // port status change
                    USB_HOST_HUB_portStatusChange(hubInfo, data);
                }

          
        }
    }
   }

}

/****************************************************************************/

 void USB_HOST_HUB_portStatusChange(USB_HOST_HUB_DRIVER_INFO  *hubInfo, uint32_t status )
 {
     uint8_t portNumber;
     USB_HOST_HUB_STATUS portStatus;
     HC_DEVICE_ID parentId , newdeviceId;
     uint8_t        level;

     status = status >> 1;

     for ( portNumber = 1 ; portNumber <= hubInfo->hubDesc.bNbrPorts ; portNumber ++ ,status>>= 1 )
     {
         if( status == 0 )
             continue;      // means this port no status change

          portStatus.change = HUB_BIT_C_PORT_CONNECTION;
          portStatus.status = HUB_BIT_PORT_CONNECTION;

          // Get port status and port change status
          _usb_host_hub_getStatus ( hubInfo, &portStatus, portNumber , PORT_REQUEST);

          if( portStatus.change & HUB_BIT_C_PORT_CONNECTION )
          {
              // port status changed so clear the event
              _usb_host_hub_clearFeature (hubInfo,portNumber ,HUB_FEATURE_C_PORT_CONNECTION, USB_HOST_HUB_COMMAND_CLEAR_FEATURE ,PORT_REQUEST );

              if ( !( portStatus.status & HUB_BIT_PORT_CONNECTION))
              {

              }
          
             else
             {
              // This is new device connected
              
              parentId = hubInfo->hubId ;
              level = 0;
              
              //TODO will do next
            /*  do
              {
                  newdeviceId = parentId ;
                  level++;
                  
              }while (level < 5 && parentId->deviceID != USB_ROOT_HUB ) */
              
              _USB_HUB_portConnect(hubInfo->hubId , portNumber , USB_SPEED_FULL  );
    
            }

         }
       if( portStatus.change & HUB_BIT_C_PORT_ENABLE )
       {
           while(1);
           //TODO clear port feature
       }
       
      if( portStatus.change & HUB_BIT_C_PORT_SUSPEND )
      {
          while(1);
          //TODO port suspended clear feature;
      }
          
            if( portStatus.change & HUB_BIT_C_PORT_OVER_CURRENT )
            {
                while(1);
                    //TODO clear feature
            }
          
          if (portStatus.change & HUB_BIT_C_PORT_RESET)
          {
              while(1);
              //Port reset
          }

     }


 }

 /******************************************************************************************************/


 USB_STATUS _usb_host_hub_clearFeature (USB_HOST_HUB_DRIVER_INFO * hubInfo, uint8_t portNumber ,uint8_t Feature, uint8_t hubCommand ,uint8_t requestType )

{
     uint8_t bmRequest ;
     USB_HOST_IRP *controlIrp;
     uint32_t  data;

      controlIrp = & (hubInfo->controlTransferIRP ) ;

     if ( requestType == PORT_REQUEST )
     {
         hubInfo->setupPacket[0] =  0x23;        // bmrequest
     }

     if (requestType == HUB_REQUEST )
     {
         hubInfo->setupPacket[0] =  0x20;
         portNumber = 0x0;
     }

      hubInfo->setupPacket[1] = hubCommand ;   //brequest is command

    hubInfo->setupPacket[2] = (Feature & 0xFF );
    hubInfo->setupPacket[3] = (Feature & 0xFF00 ) >> 7 ;   // wvalue is zero
    hubInfo->setupPacket[4] = portNumber ;
    hubInfo->setupPacket[5] = 0x00;  // windex is port number
    hubInfo->setupPacket[6] = 0x00;
    hubInfo->setupPacket[7] = 0x00; // wlength is 4 bytes

      controlIrp->setup = hubInfo->setupPacket;
    controlIrp->data = NULL;
    controlIrp->size = 0x00; //TODO change
    USB_HOST_IRPSubmit(hubInfo->controlpipeHandle, controlIrp );

    while( 1 )
    {
        /* state machine after data is completed */
        if (controlIrp->status == USB_HOST_IRP_STATUS_COMPLETED)
        {
            break;
       }
     }

}

 /********************************************************/
 USB_STATUS      USB_HOST_HUB_DeInitialize(HC_DEVICE_ID id  )
 {

 }


 /*********************************************************************/

  void _USB_HUB_portConnect(HC_DEVICE_ID hubId , uint8_t portNumber, uint8_t speed )
  {

        USB_HOST_HUB_DRIVER_INFO            *hubInfo;
        USB_HOST_HUB_STATUS portStatus;
        uint8_t      retrycount;
       
     hubInfo = _usb_host_find_hubInfo(hubId );
      /* Wait for debounce time */
          if(   _USB_HOST_HUB_portDebounce( hubInfo , portNumber , &portStatus ))
          {
              while(1);
              
          }

    
     
      for (retrycount = 0; retrycount < 3 ; retrycount++)
      {
              /* Reset the port */

           _USB_HOST_HUB_portReset( hubInfo , portNumber , &speed );


               /* enumerate the device */
          USB_HOST_HUB_enumerateDevice(hubInfo->hubId ,portNumber , speed );

           hubInfo->hubStatusIRP[0].hubInfo = hubInfo;
    hubInfo->hubStatusIRP[0].index = 0;
    hubInfo->hubStatusIRP[0].interuptinIrp.callback = USB_HOST_HUB_interruptTransferComplete;
    hubInfo->hubStatusIRP[0].interuptinIrp.status = USB_HOST_IRP_STATUS_PENDING;
    hubInfo->hubStatusIRP[0].interuptinIrp.userData = &(hubInfo->hubStatusIRP[0]);
    hubInfo->hubStatusIRP[0].interuptinIrp.size = 1;
    hubInfo->hubStatusIRP[0].interuptinIrp.data = &(hubInfo->hubStatusIRP[0].portStatus[0]);

    USB_HOST_IRPSubmit(hubInfo->interruptinpipeHandle, &(hubInfo->hubStatusIRP[0].interuptinIrp));

          break;

      }

  }

  /*************************************************************/

 uint8_t  _USB_HOST_HUB_portDebounce(USB_HOST_HUB_DRIVER_INFO  *hubInfo , uint8_t portNumber , USB_HOST_HUB_STATUS *portStatus )
 {
     //TODO
     uint32_t  count;
    // just give delay for 200 millseconds
     // hubInfo->hubId
     // DRV_USB_HOST_TimerStart(enumerateDeviceinfo.hostControllerHandle, 100);
     for ( count = 0 ; count < 500000 ; count++ )
     {
         
     }

     return 0;

 }

 void   _USB_HOST_HUB_portReset(USB_HOST_HUB_DRIVER_INFO  *hubInfo , uint8_t portNumber , uint8_t *speed )
 {
     uint8_t count;
     USB_HOST_HUB_STATUS  portStatus ;
     uint32_t timeDelay;
     uint8_t  ref;

     
     for( count = 0 ; count < 1 ; count++)
     {
         /* port reset */
         _usb_host_hub_setFeature ( hubInfo, portNumber ,HUB_PORT_RESET, USB_HOST_HUB_COMMAND_SET_FEATURE, PORT_REQUEST );

         for( ref = 0 ; ref < 1 ; ref++ )
         {
                // Some time delay
                for( timeDelay = 0 ; timeDelay < 0x50000 ; timeDelay++);
                
                _usb_host_hub_getStatus ( hubInfo,&portStatus, portNumber, PORT_REQUEST);
                
                if(!(portStatus.status & HUB_BIT_PORT_CONNECTION ))
                {
                    return;
                }
             if (( portStatus.change & HUB_BIT_C_PORT_RESET) &&   ( portStatus.status & HUB_BIT_PORT_ENABLE))
            {
                //reset complete
                 _usb_host_hub_clearFeature (hubInfo,portNumber ,HUB_FEATURE_C_PORT_RESET, USB_HOST_HUB_COMMAND_CLEAR_FEATURE ,PORT_REQUEST );

                 // check the speed

                if ( portStatus.status & HUB_BIT_PORT_LOW_SPEED  )
                {
                    *speed  =  USB_SPEED_LOW;
                }
                else if (  portStatus.status & HUB_BIT_PORT_HIGH_SPEED )
                {
                    *speed  =  USB_SPEED_HIGH;
                }
                else
                {
                    *speed  =  USB_SPEED_FULL;
                }

                return ;

            }

         }
         
        }
         
     }
     