/*******************************************************************************
 Board initialization file for PIC32 USB Digital Audio Accessary Board

 Company:
    Microchip Technology Inc.

 File Name:
    bsp_sys_init.c

 Summary:
    Board initialization file for PIC32 USB Digital Audio Accessary Board

 Description:
    This file contains the initialization of board specific I/O. At the time
 * this file was created there is no Harmony ports PLIB support availble for the
 * device PIC32MX250F128B. So accessing all the ports directly.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#if defined(__32MX250F128B__)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "bsp_config.h"


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
    #define mInitAllLEDs()      ANSELBbits.ANSB0 = 0; TRISBbits.TRISB0=0; ANSELBbits.ANSB13 = 0; TRISBbits.TRISB13=0; ANSELBbits.ANSB15 = 0; TRISBbits.TRISB15=0;
    #define mLED_1              LATBbits.LATB0
    #define mLED_2              LATBbits.LATB15
    #define mLED_3              LATBbits.LATB13
    #define mLED_4              LATBbits.LATB15

    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3
    #define mGetLED_4()         mLED_4

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;
    #define mLED_4_On()         mLED_4 = 1;

    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    #define mLED_4_Off()        mLED_4 = 0;

    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;
    #define mLED_4_Toggle()     mLED_4 = !mLED_4;

    /** SWITCH *********************************************************/
    #define mInitSwitch2()      TRISBbits.TRISB3=1;
    #define mInitSwitch3()      TRISBbits.TRISB7=1;
    #define mInitAllSwitches()  {CNPUBSET=0x8C; CNCONBbits.ON=1; mInitSwitch2();mInitSwitch3();}
    #define sw2                 PORTBbits.RB3
    #define sw3                 PORTBbits.RB7
/*******************************************************************************
  Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board

  Remarks:
    This routine performs direct register accesses, when the PORTS PLIB and
    system service become available, these register accesses will be be replaced
    by the PLIB\system service interfaces.

*/

void BSP_Initialize(void )
{

    /* set the switch pins as input */
    /* Ports PLIB not available for PIC32MX250F128B device. So direct;y accessing the ports*/
    /*
    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,
                                      PORT_CHANNEL_B ,
                                      SWITCH_1 );

    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,
                                      PORT_CHANNEL_B ,
                                      SWITCH_2 );

    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,
                                      PORT_CHANNEL_B ,
                                      SWITCH_3 );
                                       
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, LED_1 );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, LED_2 );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, LED_3 );

    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, LED_1 );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, LED_2 );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, LED_3 );
    */
    /* Enable pullups on the Switch ports*/
    /*
    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, CN2);
    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, CN3);
    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, CN7);
    */
    mInitAllLEDs() ;
    mInitAllSwitches();


}

void BSP_SwitchONLED(BSP_LED led)
{

    /* switch ON the LED */
    /*
    PLIB_PORTS_PinWrite ( PORTS_ID_0 ,
                         PORT_CHANNEL_B ,
                         led,
                         1 ); */
    switch (led)
    {
            case 1: mLED_1_On(); break;
            case 2: mLED_2_On(); break;
            case 3: mLED_3_On(); break;
            default: break;
    }

}

void BSP_SwitchOFFLED(BSP_LED led)
{
    
    /* switch OFF the LED */
    /*
    PLIB_PORTS_PinWrite ( PORTS_ID_0 ,
                         PORT_CHANNEL_B ,
                         led,
                         0 );*/
    switch (led)
    {
            case 1: mLED_1_Off(); break;
            case 2: mLED_2_Off(); break;
            case 3: mLED_3_Off(); break;
            default: break;
    }

}

void BSP_ToggleLED(BSP_LED led)
{

    /*PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B,led );*/
    switch (led)
    {
            case 1: mLED_1_Toggle(); break;
            case 2: mLED_2_Toggle(); break;
            case 3: mLED_3_Toggle(); break;
            default: break;
    }

}



BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch )
{
    return 0; 
    /*return ( PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, bspSwitch) );*/
}

uint32_t BSP_ReadCoreTimer()
{
    uint32_t timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}


/******************************************************************************/
/******************************************************************************/

#endif //__32MX250F128B__

/*******************************************************************************
 End of File
*/
