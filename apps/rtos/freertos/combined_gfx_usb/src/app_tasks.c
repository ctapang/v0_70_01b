#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system/system.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"
#include "gfx/gfx_primitive.h"
#include "gfx/gfx.h"
#include "app_keyboard.h"
#include "app.h"
#include "bsp.h"
#include "FreeRTOS.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define MAXSCREENCOLORS             7

/*
*********************************************************************************************************
*                                                GLOBALS
*********************************************************************************************************
*/
APP_DATA                   appData;
extern SYS_MODULE_OBJ      deviceLayerObject;
unsigned short             ScreenColor[MAXSCREENCOLORS] = {BRIGHTBLUE,BRIGHTGREEN,BRIGHTCYAN,BRIGHTRED,
                                                           BRIGHTMAGENTA,SIENNA,GOLD};

/*
*********************************************************************************************************
*                                          ApplicationUSBDevcieTask
*
* Description : USB Device Task calls the USB Device task routine and application tasks routines.
* Arguments   : p_arg   is the argument passed to 'ApplicationUSBDeviceTask()' by the OS through the RTOS
*               task create function.
*********************************************************************************************************
*/
void  ApplicationUSBDeviceTask (void *p_arg)
{
   while (1) 
   {
      /* Call the application's tasks routine */
      switch(appData.state)
      {
         case APP_STATE_INIT:
              
            /* Open an instance of the device layer */
            appData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );
   
            /* Register a callback with device layer to get
             * event notification (for end point 0) */
            USB_DEVICE_EventCallBackSet(appData.deviceHandle,
                    ApplicationUSBDeviceEventHandler);
   
            /* Attach the device */
   
            USB_DEVICE_Attach(appData.deviceHandle);
   
            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            break;
         case APP_STATE_WAIT_FOR_CONFIGURATION:
   
            /* Check if the device is configured. The
             * isConfigured flag is updated in the
             * Device Event Handler */
            if(appData.isConfigured)
            {
               /* Initialize the flag and place a request for a
                * output report */
               appData.isReportReceived = false;
               USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                       &appData.receiveTransferHandle,
                       (uint8_t *)&appData.keyboardOutputReport,1);
               appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            }
            break;
         case APP_STATE_CHECK_IF_CONFIGURED:
   
            /* This state is needed because the device can get
             * unconfigured asynchronously. Any application state
             * machine reset should happen within the state machine
             * context only. */
   
            if(appData.isConfigured)
            {
               appData.state = APP_STATE_SWITCH_PROCESS;
            }
            else
            {
               /* This means the device got de-configured.
                * We reset the state and the wait for configuration */
   
               ApplicationStateReset();
               appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;
         case APP_STATE_SWITCH_PROCESS:
            /* Process the switch state and go to the next state. */
            appData.state = APP_STATE_CHECK_FOR_OUTPUT_REPORT;

            appData.isSwitchPressed = false;

            /* Check if the switch was pressed, this state machine must be 
            called quickly enough to catch the user pressing the switch. This
            could lead to problems if not implemented correctly.*/
            if(BSP_ReadSwitch(SWITCH_3) == BSP_SWITCH_STATE_PRESSED)
            {
               /*pause the task for 200ms, to ensure user has let go of switch,
               if switch is still pressed, stay here until switch is let go.  If
               user presses switch and holds on, worst case the usb task will not
               progess thorough the state machine, but rest of system will be 
               functional.*/
               do
               {
                  vTaskDelay(BSP_SWITCH_DEBOUNCE_PERIOD / portTICK_RATE_MS);
               }while(BSP_ReadSwitch(SWITCH_3) == BSP_SWITCH_STATE_PRESSED);

               /* get here, this means this is a valid switch press */
               appData.isSwitchPressed = true;
            }
            break;
         case APP_STATE_CHECK_FOR_OUTPUT_REPORT:
            appData.state = APP_STATE_EMULATE_KEYBOARD;
            
            /*was a report receieved*/
            if(!appData.isReportReceived)
               break;
            
            /* Get here report received, update the LED, schedule and request*/
            if(appData.keyboardOutputReport.ledState.numLock == KEYBOARD_LED_STATE_ON)
            {
               BSP_SwitchONLED(LED_2);
            }
            else
            {
               BSP_SwitchOFFLED(LED_2);
            }
            
            if(appData.keyboardOutputReport.ledState.capsLock == KEYBOARD_LED_STATE_ON)
            {
               BSP_SwitchONLED(LED_3);
            }
            else
            {
               BSP_SwitchOFFLED(LED_3);
            }
            appData.isReportReceived = false;
            USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                    &appData.receiveTransferHandle,
                    (uint8_t *)&appData.keyboardOutputReport,1);
            break;
         case APP_STATE_EMULATE_KEYBOARD:
            /*go to next state no matter what..*/
            appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            
            /*only process if report is complete*/
            if(!appData.isReportSentComplete)
               break;

            /*Get here, this means report can be sent, Emulate keyboard*/
            if(appData.isSwitchPressed)
            {
               /* Clear the switch pressed flag */
               appData.isSwitchPressed = false;
               /* If the switch was pressed, update the key counter and then
                * add the key to the keycode array. */
               appData.key ++;
               if(appData.key == USB_HID_KEYBOARD_KEYPAD_KEYBOARD_RETURN_ENTER)
               {
                  appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
               }
               appData.keyCodeArray.keyCode[0] = appData.key;
            }
            else
            {
                /* Indicate no event */
               appData.keyCodeArray.keyCode[0] =
                  USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
            }

            KEYBOARD_InputReportCreate(&appData.keyCodeArray,
               &appData.keyboardModifierKeys, &appData.keyboardInputReport);               
            
            /*clear report complete for next time through*/
            appData.isReportSentComplete = false;
            
            USB_DEVICE_HID_ReportSend(appData.hidInstance,
                &appData.sendTransferHandle,
                (uint8_t *)&appData.keyboardInputReport,
                sizeof(KEYBOARD_INPUT_REPORT));
            break;
         case APP_STATE_ERROR:
             break;
         default:
             break;
      }
      /* Sleep for 50ms*/
      vTaskDelay(50 / portTICK_RATE_MS);
   }
}

/*                                                                                                       
*********************************************************************************************************
*                                          DisplayTask()                                               
*                                                                                                        
* Description : Application Task which writes to the screen.  In this case it just changes the screen 
*               every 500mS                                                                
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
void  ApplicationDisplayTask (void *p_arg)
{
   static unsigned int ScreenColor_Index=0;   
   
   while (1) 
   {                                          
      GFX_ColorSet(ScreenColor[ScreenColor_Index++]);
      GFX_RectangleFillDraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());
      if(ScreenColor_Index == MAXSCREENCOLORS)
         ScreenColor_Index = 0;

      /*delay task to give time back to CPU.*/
      vTaskDelay(500 / portTICK_RATE_MS);
   }
}

/*
*********************************************************************************************************
*                                          ApplicationLEDblinkTask()
*
* Description : Create application tasks.
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
void ApplicationLEDblinkTask (void *p_arg)
{
   while (1) /* Task body, always written as an infinite loop.       */
   {
      LED_Toggle();
      vTaskDelay(500 / portTICK_RATE_MS);
   }
}