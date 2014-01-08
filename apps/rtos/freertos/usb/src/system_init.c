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
#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"

/*
*********************************************************************************************************
*                                                CONFIGURATION WORDS
* Description : Sets the fuses during programming of the device.  This will cause the hardware to come up
*               in a preconfigured state.  
*               We set the CPU clock to 200MHz and use the SystemPLL output as the main clock source.  
*               The input is feed from the internal Fast RC at approximately 8MHz.
*********************************************************************************************************
*/
// DEVCFG3
#pragma config FMIIEN   = OFF
#pragma config FETHIO   = ON
#pragma config PGL1WAY  = OFF
#pragma config PMDL1WAY = OFF
#pragma config IOL1WAY  = OFF
#pragma config FUSBIDIO = OFF
// DEVCFG2
#pragma config FPLLIDIV = DIV_1         
#pragma config FPLLRNG = RANGE_5_10_MHZ 
#pragma config FPLLICLK = PLL_FRC       
#pragma config FPLLMULT = MUL_50        
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ    
#pragma config UPLLEN = ON              
// DEVCFG1
#pragma config FNOSC = SPLL             
#pragma config DMTINTV = WIN_127_128    
#pragma config FSOSCEN = OFF            
#pragma config IESO = OFF               
#pragma config POSCMOD = EC             
#pragma config OSCIOFNC = ON            
#pragma config FCKSM = CSECMD           
#pragma config WDTPS = PS1048576        
#pragma config WDTSPGM = STOP           
#pragma config WINDIS = NORMAL          
#pragma config FWDTEN = OFF             
#pragma config FWDTWINSZ = WINSZ_25     
#pragma config FDMTEN = OFF             
#pragma config DMTCNT = 0
/* DEVCFG0 */
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER =   PG_ALL
#pragma config FSLEEP =   OFF
#pragma config FECCCON = OFF_UNLOCKED
#pragma config BOOTISA = MIPS32
#pragma config TRCEN =   OFF
#pragma config ICESEL = ICS_PGx2
#pragma config DEBUG = ON
// DEVCP0
#pragma config CP = OFF                 
#pragma config_alt FWDTEN=OFF
#pragma config_alt USERID = 0x1234u

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/
SYS_MODULE_OBJ       deviceLayerObject;
extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1];
extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

USB_DEVICE_INIT usbDevInitData =
{
   /* System module initialization */
   .moduleInit = {SYS_MODULE_POWER_RUN_FULL},
   /* Identifies peripheral (PLIB-level) ID */
   .usbID = USBHS_ID_0,
   /* stop in idle */
   .stopInIdle = false,
   /* suspend in sleep */
   .suspendInSleep = false,
   /* Interrupt Source for USB module */
   .interruptSource = INT_SOURCE_USB_1,
   /* Number of function drivers registered to this instance of the
   USB device layer */
   .registeredFuncCount = 1,
   /* Function driver table registered to this instance of the USB device layer*/
   .registeredFunctions = (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,
   /* Pointer to USB Descriptor structure */
   .usbMasterDescriptor = (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor,
   /* USB Device Speed */
   .deviceSpeed = USB_SPEED_FULL
};




/*
*********************************************************************************************************
*                                          SYS_Initialize
*
* Description : This routine initializes the board, services, drivers, application and other modules as
*               configured at build time.
* Caller      : called from main
*********************************************************************************************************
*/
void SYS_Initialize ( void * data )
{
   portBASE_TYPE errStatus;
   
   /* Initialize the BSP */
   BSP_Initialize( );
   
   /* Initialize the USB device layer */
   deviceLayerObject = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 ,
         ( SYS_MODULE_INIT* ) & usbDevInitData);

   /*initialize application specific items*/
   ApplicationInitialize();

   /*create system task(s)*/
   errStatus = xTaskCreate((pdTASK_CODE) SystemUSBDeviceTask,
                (const signed char*)"Sys USB Device Task",
                SYSTEM_USBDEVICETASK_SIZE,
                NULL,
                SYSTEM_USBDEVICETASK_PRIO,
                NULL);
}