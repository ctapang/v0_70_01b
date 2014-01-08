#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include "system_config.h"
#include "driver/usb/drv_usb.h"
#include "system/system.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"
#include "app_keyboard.h"
#include "app.h"


/*
*********************************************************************************************************
*                                          _InterruptHandler_USB_stub
*
* Description : Calls the USB driver in Harmony Framework to get work done.
*********************************************************************************************************
*/
void __ISR ( _USB_VECTOR,ipl4 ) _InterruptHandler_USB_stub ( void )
{
   DRV_USB_Tasks_ISR((SYS_MODULE_OBJ)0);
}