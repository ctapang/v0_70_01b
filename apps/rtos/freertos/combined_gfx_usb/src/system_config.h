#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H
/*
*********************************************************************************************************
*                                         DEFINES 
*********************************************************************************************************
*/

/*configuring the harmony system for USB*/
#define USB_DEVICE_HID_INSTANCES_NUMBER      1
#define USB_DEVICE_HID_FUNC_INDEX            0
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED  2
#define USB_DEVICE_MAX_INSTANCES             1
#define USB_DEVICE_MAX_CLIENTS               1
#define USB_DEVICE_EP0_BUFFER_SIZE           64
#define DRV_USB_INSTANCES_NUMBER             USB_DEVICE_MAX_INSTANCES
#define DRV_USB_CLIENTS_NUMBER               1
#define DRV_USB_INTERRUPT_MODE               true
#define DRV_USB_ENDPOINTS_NUMBER             2
#define DRV_USB_DEVICE_SUPPORT               true
#define DRV_USB_HOST_SUPPORT                 false

/*configuring the harmony system for GFX*/
#define MEB_2_BOARD
#define GFX_PICTAIL_LCC
#define LCC_INTERNAL_MEMORY_EBI
#define MEB_2_BOARD
#define PIC_SK
#define GFX_USE_DISPLAY_CONTROLLER_LCC
#define GFX_CONFIG_FONT_ANTIALIASED_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_CONFIG_IMAGE_EXTERNAL_DISABLE
#define GFX_CONFIG_COLOR_DEPTH               16
#define GFX_CONFIG_FONT_CHAR_SIZE            8
#define GFX_CONFIG_PALETTE_DISABLE
#define GFX_CONFIG_GOL_DISABLE
#define GFX_CONFIG_FONT_EXTERNAL_DISABLE
#define GFX_USE_DISPLAY_PANEL_PH480272T_005_I11Q
#define LCC_INTERNAL_MEMORY
#undef  USE_MULTIBYTECHAR
#define BACKLIGHT_ENABLE_LEVEL               1
#define BACKLIGHT_DISABLE_LEVEL              0

#define PIXELCLOCK                           LATDbits.LATD5
#define PIXELCLOCK_TRIS                      TRISDbits.TRISD5
#define DATA_ENABLE                          LATBbits.LATB4
#define DATA_ENABLE_TRIS                     TRISBbits.TRISB4
#define HSYNC                                LATBbits.LATB1
#define HSYNC_TRIS                           TRISBbits.TRISB1
#define VSYNC                                LATAbits.LATA9
#define VSYNC_TRIS                           TRISAbits.TRISA9
#define BACKLIGHT                            LATFbits.LATF13
#define BACKLIGHT_TRIS                       TRISFbits.TRISF13
#define LCD_RESET                            LATJbits.LATJ3
#define LCD_RESET_TRIS                       TRISJbits.TRISJ3
#define LCD_CS                               LATJbits.LATJ6
#define LCD_CS_TRIS                          TRISJbits.TRISJ6
#define DisplayResetConfig()                 TRISCCLR = _TRISC_TRISC1_MASK
#define DisplayResetEnable()                 LATCCLR = _LATC_LATC1_MASK
#define DisplayResetDisable()                LATCSET = _LATC_LATC1_MASK
#define DisplayCmdDataConfig()               TRISCCLR = _TRISC_TRISC2_MASK
#define DisplaySetCommand()                  LATCCLR = _LATC_LATC2_MASK
#define DisplaySetData()                     LATCSET = _LATC_LATC2_MASK
#define DisplayConfig()                      TRISDCLR = _TRISD_TRISD10_MASK
#define DisplayEnable()                      LATDCLR = _LATD_LATD10_MASK
#define DisplayDisable()                     LATDSET = _LATD_LATD10_MASK
#define DisplayBacklightConfig()             (TRISDbits.TRISD0 = 0)
#define DisplayBacklightOn()                 (LATDbits.LATD0 = BACKLIGHT_ENABLE_LEVEL)
#define DisplayBacklightOff()                (LATDbits.LATD0 = BACKLIGHT_DISABLE_LEVEL)
#define ADDR16                               LATKbits.LATK0
#define ADDR16_TRIS                          TRISKbits.TRISK0
#define ADDR17                               LATKbits.LATK3
#define ADDR17_TRIS                          TRISKbits.TRISK3
#define ADDR18                               LATKbits.LATK4
#define ADDR18_TRIS                          TRISKbits.TRISK4
#define ADDR19                               LATKbits.LATK5
#define ADDR19_TRIS                          TRISKbits.TRISK5
#define SRAM_CS                              LATJbits.LATJ4
#define SRAM_TRIS                            TRISJbits.TRISJ4

#define PMP_INTERRUPT                        IEC4bits.PMPIE
#define PMADDR_OVERFLOW                      65536

#define USE_TCON_MODULE                      0
#define GFX_USE_TCON_CUSTOM
#define DISP_ORIENTATION		     0
#define DISP_HOR_RESOLUTION		     480
#define DISP_VER_RESOLUTION		     272
#define DISP_DATA_WIDTH			     24
#define DISP_HOR_PULSE_WIDTH                 41
#define DISP_HOR_BACK_PORCH                  2
#define DISP_HOR_FRONT_PORCH                 2
#define DISP_VER_PULSE_WIDTH                 10
#define DISP_VER_BACK_PORCH                  2
#define DISP_VER_FRONT_PORCH                 2
#define DISP_INV_LSHIFT                      0
#define GFX_LCD_TYPE                         GFX_LCD_TFT
#define TCON_MODULE                          NULL

/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void SYS_Initialize ( void * data );
void SystemUSBDeviceTask (void *p_arg);
void SYS_Tasks (void);
void SystemDisplayDriverTask (void *p_arg);
#endif	/* SYSTEM_CONFIG_H */

