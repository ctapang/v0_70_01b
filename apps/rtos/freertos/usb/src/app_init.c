#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system/system.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"
#include "app_keyboard.h"
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"

/*
*********************************************************************************************************
*                                          GLOBALS
*********************************************************************************************************
*/
extern APP_DATA appData;




/*
*********************************************************************************************************
*                                          ApplicationInitialize
*
* Description :  This function is called by SYS_Initialize() function and run after power up.  Global 
*                are not enabled here (i.e. CP0 Status register).  Interrupts will be enabled by RTOS when
*                the highest priority task is run the first time.
* Arguments   : 
*********************************************************************************************************
*/
void ApplicationInitialize ( void )
{
   portBASE_TYPE errStatus;
   appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
   appData.isConfigured = false;

   /* Initialize the keycode array */
   appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
   appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
   appData.keyCodeArray.keyCode[1] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
   appData.keyCodeArray.keyCode[2] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
   appData.keyCodeArray.keyCode[3] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
   appData.keyCodeArray.keyCode[4] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
   appData.keyCodeArray.keyCode[5] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    
   /* Initialize the modifier keys */
   appData.keyboardModifierKeys.modifierkeys = 0;

   /* Initialise the led state */
   appData.keyboardOutputReport.data = 0;

   /* Intialize the switch state */
   appData.isSwitchPressed = false;
   appData.ignoreSwitchPress = false;

   /* Initialize the HID instance index.  */
   appData.hidInstance = 0;

   /* Initialize tracking variables */
   appData.isReportReceived = false;
   appData.isReportSentComplete = true;

   /* Initialize the application state*/
   appData.state = APP_STATE_INIT;

   errStatus = xTaskCreate((pdTASK_CODE) ApplicationLEDblinkTask,
                (const signed char*)"LED Blink Task",
                APPLICATION_LEDBLINKTASK_SIZE,
                NULL,
                APPLICATION_LEDBLINKTASK_PRIO,
                NULL);

   errStatus = xTaskCreate((pdTASK_CODE) ApplicationUSBDeviceTask,
                (const signed char*)"USB Device Task",
                APPLICATION_USBDEVICETASK_SIZE,
                NULL,
                APPLICATION_USBDEVICETASK_PRIO,
                NULL);
   
   /*setup up interrupt controller to use multi-vectored mode, this is not the internal CP0 register,
   this sets the SFR register*/
   PLIB_INT_MultiVectorSelect(INT_ID_0);

   /* Set priority for USB interrupt source */                                
   PLIB_INT_VectorPrioritySet(INT_ID_0,INT_VECTOR_USB,INT_PRIORITY_LEVEL4);
}

/*
*********************************************************************************************************
*                                          ApplicationStateReset
*
* Description : This function is called by when the device is de-configured. It resets the application
*               state in anticipation for the next device configured event
* Arguments   : 
*********************************************************************************************************
*/
void ApplicationStateReset(void)
{
   appData.isReportReceived = false;
   appData.isReportSentComplete = true;
   appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
   appData.keyboardModifierKeys.modifierkeys = 0;
   appData.keyboardOutputReport.data = 0;
   appData.isSwitchPressed = false;
   appData.ignoreSwitchPress = false;
}
