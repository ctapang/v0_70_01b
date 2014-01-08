#include <xc.h>
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system/system.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"
#include "peripheral/int/plib_int.h"
#include "app_keyboard.h"
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"

/*
*********************************************************************************************************
*                                          GLOBALS
*********************************************************************************************************
*/
extern SYS_MODULE_OBJ       deviceLayerObject;


/*
*********************************************************************************************************
*                                          SYS_Tasks()
*
* Description : Starts the OS, never returns
*
* Argument(s) : none
*
* Caller(s)   : main
*********************************************************************************************************
*/
void SYS_Tasks (void)
{
   vTaskStartScheduler();       /* Start multitasking (i.e. give control to FreeRTOS).                */
}


/*
*********************************************************************************************************
*                                          SystemUSBDeviceTask
*
* Description : device layer tasks routine, HID tasks gets called from device layer tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : OS called after waiting time delay()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void SystemUSBDeviceTask (void *p_arg)
{
   while (1) 
   {
      USB_DEVICE_Tasks(deviceLayerObject);
      vTaskDelay(40 / portTICK_RATE_MS);
   }
}