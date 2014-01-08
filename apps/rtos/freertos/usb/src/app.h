#ifndef __APP_H
#define	__APP_H
/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APPLICATION_LEDBLINKTASK_PRIO                  2u
#define  APPLICATION_USBDEVICETASK_PRIO                 4u
#define  SYSTEM_USBDEVICETASK_PRIO                      5u
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/
#define  APPLICATION_LEDBLINKTASK_SIZE                  1024u
#define  APPLICATION_USBDEVICETASK_SIZE                 1024u
#define  SYSTEM_USBDEVICETASK_SIZE                      1024u
/*
*********************************************************************************************************
*                                         ENUM, UNION, STRUCTURES
*********************************************************************************************************
*/
typedef enum
{
   /* Application opens the device layer in this state */
   APP_STATE_INIT,

   /* Application waits for configuration in this state */
   APP_STATE_WAIT_FOR_CONFIGURATION,

   /* Application checks if an output report is available */
   APP_STATE_CHECK_FOR_OUTPUT_REPORT,

   /* Application updates the switch states */
   APP_STATE_SWITCH_PROCESS,

   /* Application checks if it is still configured*/
   APP_STATE_CHECK_IF_CONFIGURED,

   /* Application emulates keyboard */
   APP_STATE_EMULATE_KEYBOARD,

   /* Application error state */
   APP_STATE_ERROR
}APP_STATES;


typedef struct
{
   /* Handle to the device layer */
   USB_DEVICE_HANDLE deviceHandle;

   /* Application HID instance */
   USB_DEVICE_HID_INDEX hidInstance;

   /* Application state */
   APP_STATES state;

   /* Is device configured */
   bool isConfigured;

   /*Keyboard Report to be transmitted*/
   KEYBOARD_INPUT_REPORT keyboardInputReport;

   /* Keyboard modifier keys*/
   KEYBOARD_MODIFIER_KEYS keyboardModifierKeys;

   /* Keyboard output report */
   KEYBOARD_OUTPUT_REPORT keyboardOutputReport;

   /* Key code array*/
   KEYBOARD_KEYCODE_ARRAY keyCodeArray;

   /* Switch state*/
   bool ignoreSwitchPress;

   /* Tracks switch press*/
   bool isSwitchPressed;

   /* Track the send report status */
   bool isReportSentComplete;

   /* Track if a report was received */
   bool isReportReceived;

   /* Receive transfer handle */
   USB_DEVICE_HID_TRANSFER_HANDLE receiveTransferHandle;

   /* Send transfer handle */
   USB_DEVICE_HID_TRANSFER_HANDLE sendTransferHandle;

   /* Keycode to be sent */
   USB_HID_KEYBOARD_KEYPAD key;


} APP_DATA;

/*
*********************************************************************************************************
*                                            PROTOTYPES
*********************************************************************************************************
*/
void ApplicationInitialize ( void );
void ApplicationStateReset(void);
void  ApplicationUSBDeviceTask (void *p_arg);
void ApplicationInitialize ( void );
void ApplicationStateReset(void);
void ApplicationLEDblinkTask (void* p_arg);
USB_DEVICE_HID_EVENT_RESPONSE ApplicationUSBDeviceHIDEventHandler(
                                 USB_DEVICE_HID_INDEX hidInstance,
                                 USB_DEVICE_HID_EVENT event,
                                 USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                                 void * eventData,
                                 uintptr_t userData);
void ApplicationUSBDeviceEventHandler(USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData);
#endif	/* APP_H */

