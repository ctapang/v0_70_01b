/*******************************************************************************
  USB Device Driver Core Routines

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usb.c

  Summary:
    USB Device Driver Dynamic Implementation of Core routines

  Description:
    The USB device driver provides a simple interface to manage the USB
    modules on Microchip microcontrollers.  This file Implements the core
    interface routines for the USB driver.

    While building the driver from source, ALWAYS use this file in the build.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip  Technology  Inc.   All  rights  reserved.

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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "driver/usb/usbfs/src/drv_usb_local.h"

DRV_USB_GROUP gDrvUSBGroup[DRV_USB_INSTANCES_NUMBER];

#define DRIVER __attribute__((section("Driver")))

SYS_MODULE_OBJ DRIVER DRV_USB_Initialize 
( 
    const SYS_MODULE_INDEX  drvIndex,
    const SYS_MODULE_INIT * const init
)
{
    
    DRV_USB_OBJ * drvObj;
    USB_MODULE_ID  usbID;  
    DRV_USB_INIT * usbInit;

    if( drvIndex >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_ASSERT(false,"Increase the value of DRV_USB_INSTANCES_NUMBER");
        return SYS_MODULE_OBJ_INVALID;
    }

    if(gDrvUSBGroup[drvIndex].gDrvUSBObj.inUse == true)
    {
        /* Cannot initialize an object that is
         * already in use. */

        SYS_ASSERT(false, "Instance already in use");
        return SYS_MODULE_OBJ_INVALID;
    }

    usbInit     = (DRV_USB_INIT *) init;
    usbID       = usbInit->usbID;

    drvObj = &gDrvUSBGroup[drvIndex].gDrvUSBObj;

    /* Populate the driver object with
     * the required data */

    drvObj->inUse   = true;
    drvObj->status  = SYS_STATUS_BUSY; 
    drvObj->usbID   = usbID;            
    drvObj->operationMode  = usbInit->operationMode; 
    drvObj->pBDT    = (DRV_USB_BDT_ENTRY *)(usbInit->endpointTable);

    /* Assign the endpoint table */
    drvObj->endpointTable = &gDrvUSBGroup[drvIndex].gDrvUSBEndpoints[0];

    drvObj->interruptSource  = usbInit->interruptSource;

    /* Turn off USB module */

    PLIB_USB_Disable( usbID );

    /* Setup the Hardware */

    if ( usbInit->stopInIdle )
    {
        PLIB_USB_StopInIdleEnable( usbID );
    }
    else
    {
        PLIB_USB_StopInIdleDisable( usbID );
    }

    if ( usbInit->suspendInSleep )
    {
        PLIB_USB_AutoSuspendEnable( usbID );
    }
    else
    {
        PLIB_USB_AutoSuspendDisable( usbID );
    }

    /* Setup the USB Module based on the selected
     * mode */

    switch(usbInit->operationMode)
    {
        case USB_OPMODE_DEVICE:
            _DRV_USB_DEVICE_INIT(drvObj, drvIndex);
            break;
        case USB_OPMODE_HOST:
            _DRV_USB_HOST_INIT(drvObj, drvIndex);
            break;
        case USB_OPMODE_OTG:
            break;
        default:
            SYS_ASSERT(false, "What mode are you trying?");
            break;

    }

//    if (usbInit->operationSpeed == USB_SPEED_LOW)
//    {
//        //PLIB_USB_FullSpeedDisable ( drvIndex ); //
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DMINUS_PULLUP, true );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DPLUS_PULLUP, false );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DMINUS_PULLDN, false );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DPLUS_PULLDN, false );
//    }
//    else
//    {
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DMINUS_PULLUP, false );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DPLUS_PULLUP, true );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DMINUS_PULLDN, false );
//        USB_OTG_PullUpPullDownSetup_Default( drvIndex, USB_OTG_DPLUS_PULLDN, false );
//    }

    /* Clear and enable the interrupts */
    _DRV_USB_InterruptSourceClear(usbInit->interruptSource);
//    _DRV_USB_InterruptSourceEnable(usbInit->interruptSource);

    /* Assign the BDT address */

    SYS_ASSERT((drvObj->pBDT == 0xA0000400), "bad BDT address");
    PLIB_USB_BDTBaseAddressSet( usbID , 
            (void *)((uint32_t)KVA_TO_PA(drvObj->pBDT) ));

    /* Set number of clients to zero */

    drvObj->nClients = 0;
    drvObj->pDrvUSBClientObj = (DRV_USB_CLIENT_OBJ*)DRV_HANDLE_INVALID;

    /* Indicate that the object is ready and in use
     * and return the driver handle */

    drvObj->status = SYS_STATUS_READY; 
    return ((SYS_MODULE_OBJ)drvIndex); 

} /* DRV_USB_Initialize */

void DRIVER DRV_USB_Deinitialize
( 
    const SYS_MODULE_OBJ  object
)
{
    DRV_USB_OBJ * drvObj;
    USB_MODULE_ID  usbID;  
    
    if(object == SYS_MODULE_OBJ_INVALID)
    { 
	    /* Invalid object */
	    
	    SYS_ASSERT(false, "Invalid object");
	    return;
	} 
    
    if( object >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_ASSERT(false,"Invalid driver Index");
        return ;
    }

    if(gDrvUSBGroup[object].gDrvUSBObj.inUse == false)
    {
        /* Cannot deinitialize an object that is 
         * not already in use. */

        SYS_ASSERT(false, "Instance not in use");
        return ;
    }

    drvObj = &gDrvUSBGroup[object].gDrvUSBObj;
    usbID  = drvObj->usbID;

    /* Populate the driver object with
     * the required data */

    drvObj->inUse   = false;
    drvObj->status  = SYS_STATUS_UNINITIALIZED; 

    /* Turn off USB module */

    PLIB_USB_Disable( usbID );

    /* Clear and disable the interrupts */
    _DRV_USB_InterruptSourceDisable(drvObj->interruptSource);
    _DRV_USB_InterruptSourceClear(drvObj->interruptSource);

    /* Set number of clients to zero */

    drvObj->nClients = 0;
    drvObj->pDrvUSBClientObj = (DRV_USB_CLIENT_OBJ*)DRV_HANDLE_INVALID;

    return;

} /* DRV_USB_Initialize */



SYS_STATUS DRIVER DRV_USB_Status ( SYS_MODULE_OBJ object )
{
    if(object == SYS_MODULE_OBJ_INVALID)
    {
        SYS_ASSERT(false, "System Module Object is invalid");
        return SYS_STATUS_ERROR;
    }
    
    /* Return the status of the driver object */
    return(gDrvUSBGroup[object].gDrvUSBObj.status);
}


DRV_HANDLE DRIVER DRV_USB_Open
(
    const SYS_MODULE_INDEX iDriver,
    const DRV_IO_INTENT    ioIntent 
)
{
    DRV_USB_CLIENT_OBJ * hClient;
    DRV_USB_OBJ * drvObj;

    /* The iDriver value should be valid. It should be
     * less the number of driver object instances. 
     */

    if(iDriver >= DRV_USB_INSTANCES_NUMBER)
    {
        SYS_ASSERT(false, "Bad Driver Index");
        return DRV_HANDLE_INVALID;
    }

    drvObj = &gDrvUSBGroup[iDriver].gDrvUSBObj;

    if(drvObj->status != SYS_STATUS_READY)
    {
        /* The USB module should be ready */

        SYS_ASSERT(false, "Was the driver initialized?");
        return DRV_HANDLE_INVALID;
    }

    if(ioIntent != (DRV_IO_INTENT_EXCLUSIVE|DRV_IO_INTENT_NONBLOCKING
                |DRV_IO_INTENT_READWRITE))
    {
        /* The driver only supports this mode */

        SYS_ASSERT(false, "IO intent mode not supported");
        return DRV_HANDLE_INVALID;
    }	

    if(drvObj->nClients > 0)
    {
        /* Driver supports exclusive open only */
        SYS_ASSERT(false, "Driver already opened once. Cannot open again");
        return DRV_HANDLE_INVALID;
    }

    /* One to One mapping between client object
     * and driver object */

    hClient = &gDrvUSBGroup[iDriver].gDrvUSBClientObj;

       /* Remember which USB control driver owns me */
    hClient->hDriver        = drvObj; 
    hClient->usbID          = drvObj->usbID;

    /* Clear prior value */

    hClient->pEventCallBack = NULL;

    /* Store the handle in the driver object
     * client table and update the number of
     * clients*/

    drvObj->pDrvUSBClientObj = hClient;
    drvObj->nClients ++;

    /* Return the client object */

    return ( ( DRV_HANDLE ) hClient );
}

void DRIVER DRV_USB_Close( DRV_HANDLE client )
{
    DRV_USB_CLIENT_OBJ * hClient;
    DRV_USB_OBJ * hDriver;

    if(client == DRV_HANDLE_INVALID)
    {
        SYS_ASSERT(false, "Bad Client Handle");
        return;
    }

    hClient = (DRV_USB_CLIENT_OBJ *) client;
    
    hDriver = (DRV_USB_OBJ *)hClient->hDriver;

    /* Remove this client from the driver client
     * table */

    hDriver->nClients--;
    hDriver->pDrvUSBClientObj = (DRV_USB_CLIENT_OBJ *)DRV_HANDLE_INVALID;

    hClient->pEventCallBack = NULL;
}

void DRIVER DRV_USB_Tasks_ISR( SYS_MODULE_OBJ object )
{
    DRV_USB_OBJ * 	hDriver; 
    hDriver = &gDrvUSBGroup[object].gDrvUSBObj;
    hDriver->isInInterruptContext = true;

	switch(hDriver->operationMode)
	{
            case USB_OPMODE_DEVICE:
                _DRV_USB_DEVICE_TASKS_ISR(hDriver);
                break;
            case USB_OPMODE_HOST:
                _DRV_USB_HOST_TASKS_ISR(hDriver);
                break;
            case USB_OPMODE_OTG:
                break;
            default:
                SYS_ASSERT(false, "What mode are you trying?");
                break;
	}	
  
    /* Clear the interrupt */
    _DRV_USB_InterruptSourceClear(hDriver->interruptSource);
    hDriver->isInInterruptContext = false;
}


void DRIVER DRV_USB_ClientEventCallBackSet
( 
    DRV_HANDLE   client          ,
    uintptr_t    hReferenceData ,
    DRV_USB_EVENT_CALLBACK eventCallBack 
)
{
    DRV_USB_CLIENT_OBJ * hClient;

    if(client == DRV_HANDLE_INVALID)
    {
        SYS_ASSERT(false, "Bad Client Handle");
        return;
    }

    hClient = (DRV_USB_CLIENT_OBJ *) client;
    
   /* Assign event call back and reference data */
    hClient->hClientArg = hReferenceData;
    hClient->pEventCallBack = eventCallBack;
   
    return;
    
}
