 /*******************************************************************************
  Clock System Service Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    sys_clk.c

  Summary:
    Clock System Service implementation.

  Description:
    The Clock System Service provides a simple interface to manage the clock
    on Microchip microcontrollers. This file implements the core interface routines 
    for the Clock System Service. While building the system service from source, 
    ALWAYS include this file in the build.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "../sys_clk.h"

SYS_CLK_OBJECT clkObject;


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void SYS_CLK_Initialize ( const SYS_CLK_INIT * const oscInit )

  Summary:
    Initializes hardware and internal data structure for the general features
    of the clock.

  Description:
    This function initializes hardware and internal data structure for the general
    features of the clock. Preferably, this API should be called erly in the 
    initialization (before other modules are initialized so that the clock gets 
    the necessary settling time before normal execution of the code starts).

  Remarks:
    None.
*/

void SYS_CLK_Initialize ( const SYS_CLK_INIT const * clkInit )
{
    /* Call the actual initialize routine which is specific to the family */
#if defined(__PIC32MX__)
    SYS_CLK_HardwareRegisterUpdate ( clkInit );
#endif
#if defined(__PIC32MZ__)
    SYS_CLK_PIC32MZInit ( clkInit );
#endif
}


/******************************************************************************
  Function:
    bool SYS_CLK_ClockIsReady ( SYS_ CLK_OUTPUT clockOutput )

  Summary:
    Checks whether the oscillator is ready.

  Description:
    This function returns 'true' if the specified clock is stable and ready. It
    checks for the lock status of all the enabled PLLs and initial stabilization
    time for the oscillator.

  Remarks:
    This is non-blocking code.
*/

bool SYS_CLK_ClockIsReady ( SYS_CLK_OUTPUT clockOutput )
{
    OSC_SYS_TYPE systemClockSource;

    /* Check for the startup timer fail */
    if (true == PLIB_OSC_ExistsClockFail(OSC_PLIB_ID))
    {
        if(true == PLIB_OSC_ClockHasFailed(OSC_PLIB_ID))
        {
            return false;
        }
    }
    switch (clockOutput)
    {
        case CLK_SYSTEM:
        case CLK_PERIPHERAL:
        case CLK_REFERENCE:
#if defined (__PIC32MX__)
            /* If PLL is enabled, it needs time to stabalize */
            systemClockSource = PLIB_OSC_CurrentSysClockGet(OSC_PLIB_ID);
            if ((systemClockSource == OSC_PRIMARY_WITH_PLL) ||
            (systemClockSource == OSC_FRC_WITH_PLL))
            {
                return (!PLIB_OSC_PLLIsLocked(OSC_PLIB_ID, OSC_PLL_SYSTEM));
            }
#endif
            /* If control reaches here, means the oscillator is ready */
            return true;
            break;
        case CLK_USB:
#if defined (__PIC32MX__)
            if(SYS_CLK_CONFIG_USBPLL_ENABLE == true)
            {
                return (!PLIB_OSC_PLLIsLocked(OSC_ID_0, OSC_PLL_USB));
            }
#endif
            /* If control reaches here, means the oscillator is ready */
            return true;
            break;
        default:
            break;
    }

    return false;
}


/******************************************************************************
  Function:
    uint32_t SYS_CLK_ClockFrequencyGet ( SYS_CLK_OUTPUT clockOutput )

  Summary:
    Gets the frequency of the specified clock.

  Description:
    This function returns the frequency of the specified clock.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ClockFrequencyGet ( SYS_CLK_OUTPUT clockOutput )
{
    switch (clockOutput)
    {
        case CLK_SYSTEM:
            return clkObject.systemClock;
        case CLK_PERIPHERAL:
            return clkObject.peripheralClock;
        case CLK_USB:
            return clkObject.usbClock;
        case CLK_REFERENCE:
            return clkObject.referenceClock;
        default:
            break;
    }

    return 0;
}

unsigned long SYS_CLK_MZPeriphBusFreqGet ( CLK_PERIPH_BUS_MZ periphBus )
{
    switch (periphBus)
    {
        case CLK_PERIPH_BUS_1:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_1];
        case CLK_PERIPH_BUS_2:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_2];
        case CLK_PERIPH_BUS_3:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_3];
        case CLK_PERIPH_BUS_4:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_4];
        case CLK_PERIPH_BUS_5:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_5];
        case CLK_PERIPH_BUS_7:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_7];
        case CLK_PERIPH_BUS_8:
            return clkObject.MZperipheralClock[CLK_PERIPH_BUS_8];
        default:
            break;
    }
    return 0;
}

/******************************************************************************
  Function:
    uint32_t SYS_CLK_ClockFrequencySet ( SYS_CLK_OUTPUT clockOutput )

  Summary:
    Sets the clock source and frequency of the specified clock.

  Description:
   This function sets the clock frequency and source for the selected output
   clock.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ClockFrequencySet( SYS_CLK_OUTPUT outputClock,
                                         SYS_CLK_SOURCE clockSource,
                                         unsigned long clockFrequency )
{
    switch (outputClock)
    {
        case CLK_SYSTEM:
            return SYS_CLK_SystemClockSet ( clockSource, clockFrequency );
        case CLK_USB:
            return SYS_CLK_UsbClockSet ( clockSource, clockFrequency );
        case CLK_REFERENCE:
            return SYS_CLK_ReferenceClockSet ( clockSource, clockFrequency );
        case CLK_PERIPHERAL:
            return SYS_CLK_PeripheralClockSet ( clockSource, clockFrequency );
        default:
            break;
    }

    return 0; // Ratheesh, please check if this is right return value on failure
}


/******************************************************************************
  Function:
    void SYS_CLK_FRCTune ( OSC_FRC_TUNE tuningData )

  Summary:
    Triggers the direct value-based FRC oscillator tuning.

  Description:
    This function triggers the FRC tuning based on the selected mode. FRC
    tuning functionality has been provided to help customers compensate for
    temperature effects on the FRC frequency over a wide range of temperatures.

  Remarks:
    None.
*/

void SYS_CLK_FRCTune ( OSC_FRC_DIV tuningData )
{
    PLIB_OSC_FRCTuningSelect(OSC_ID_0, tuningData);
}


/*******************************************************************************
End of File
*/

