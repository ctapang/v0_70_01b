#ifndef __SYSTEM_CONFIG_H
#define	__SYSTEM_CONFIG_H
/*
*********************************************************************************************************
*                                         DEFINES
*********************************************************************************************************
*/

/*configuring the harmony system*/
#define USB_DEVICE_HID_INSTANCES_NUMBER     1
#define USB_DEVICE_HID_FUNC_INDEX           0
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED 2
#define USB_DEVICE_MAX_INSTANCES            1
#define USB_DEVICE_MAX_CLIENTS              1
#define USB_DEVICE_EP0_BUFFER_SIZE          64
#define DRV_USB_INSTANCES_NUMBER            USB_DEVICE_MAX_INSTANCES
#define DRV_USB_CLIENTS_NUMBER              1
#define DRV_USB_INTERRUPT_MODE              true
#define DRV_USB_ENDPOINTS_NUMBER            2
#define DRV_USB_DEVICE_SUPPORT              true
#define DRV_USB_HOST_SUPPORT                false


/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void SYS_Initialize ( void * data );
void SystemUSBDeviceTask (void *p_arg);
void SYS_Tasks (void);

#endif	/* SYSTEM_CONFIG_H */

