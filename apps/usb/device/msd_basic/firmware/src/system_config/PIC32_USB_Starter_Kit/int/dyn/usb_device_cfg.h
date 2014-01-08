#ifndef _USB_DEVICE_CFG_H_
#define _USB_DEVICE_CFG_H_

// Set the maximum size of EP0 in bytes
#define MAX_SIZE_EP0  8

#define USB_DEVICE_MAX_INSTANCES 2
#define USB_DEVICE_MAX_CLIENTS 3



// Set the maximum size of control transfer in bytes.
#define MAX_SIZE_CONTROL_TX (MAX_SIZE_EP0 * 2)

// Maximum function drivers allowed per instance of the USB device layer */
#define USB_DEVICE_MAX_FUNCTION_DRIVER 5


#endif



