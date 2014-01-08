 /*******************************************************************************
  Clock System Service implementation

  Company:
    Microchip Technology Inc.

  FileName:
    sys_clk_pic32.c

  Summary:
    Clock system service implementation

  Description:
    The Clock system service provides a simple interface to manage the
    Clock modules on Microchip microcontrollers.  This file Implements
    the functions specific to PIC32 devices.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _PLIB_UNSUPPORTED

  Summary:
    Macro definition to avoid 'unsupported' warnings.

  Description:
    This macro should be defined to avoid unsupported warnings.

*/

#define _PLIB_UNSUPPORTED

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************


#include "system/clk/src/sys_clk_local.h"
#include "system/clk/src/sys_clk_lookup_pic32.h"
#include "system_config.h"
#include <stdlib.h>

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void SYS_CLK_HardwareRegisterUpdate ( const SYS_CLK_INIT * const oscInit )

  Summary:
    Initializes the hardware registers as per the user input to the 'Initialize'
	function of the Clock module.

  Description:
    This initializes hardware for the features of the Clock module. This will
	get called by the initialization routine, which will get called by the
	user.

  Remarks:
    None.
*/

void SYS_CLK_HardwareRegisterUpdate ( const SYS_CLK_INIT const * clkInit )
{
    /* Set the system clock register as per the user request */
    SYS_CLK_SystemClockSet ( clkInit->systemClockSource,
                             clkInit->systemClockFrequency );

    /* USB clock is optional. So it has an enable control */
    if(clkInit->usbClockEnable)
    {
        SYS_CLK_UsbClockSet ( clkInit->usbClockSource,
                              clkInit->usbClockFrequency );
    }

    if(clkInit->peripheralClockEnable)
    {
        SYS_CLK_PeripheralClockSet ( clkInit->peripheralClockSource,
                                     clkInit->peripheralClockFrequency );
    }
    if (PLIB_OSC_ExistsReferenceOscEnable(OSC_PLIB_ID))
    {
        /* Enable the reference Oscillator */
        if(true == clkInit->referenceClockEnable)
        {
            PLIB_OSC_ReferenceOscEnable(OSC_PLIB_ID, OSC_REFERENCE_1);
            PLIB_OSC_ReferenceOutputEnable(OSC_PLIB_ID, OSC_REFERENCE_1);

            SYS_CLK_ReferenceClockSet ( clkInit->referenceClockSource,
                          clkInit->referenceClockFrequency );
        }
        else
        {
            PLIB_OSC_ReferenceOscDisable(OSC_PLIB_ID, OSC_REFERENCE_1);
        }
    }
    if (PLIB_OSC_ExistsSecondaryEnable(OSC_PLIB_ID))
    {
        /* Enable the Secondary Oscillator */
        if(true == clkInit->secondaryOscKeepEnabled)
        {
            PLIB_OSC_SecondaryEnable(OSC_PLIB_ID);
        }
        else
        {
            PLIB_OSC_SecondaryDisable(OSC_PLIB_ID);
        }
    }
    if (PLIB_OSC_ExistsOnWaitAction(OSC_PLIB_ID))
    {
        /* Sets the oscillator's response to a 'Wait' instruction */
        PLIB_OSC_OnWaitActionSet(OSC_PLIB_ID, clkInit->onWaitInstruction);
    }
    if (PLIB_OSC_ExistsReferenceOscEnable(OSC_PLIB_ID))
    {
        if(true == clkInit->referenceSuspendInSleep)
        {
            PLIB_OSC_ReferenceOscStopInSleepEnable(OSC_PLIB_ID, OSC_REFERENCE_1);
        }
        else
        {
            PLIB_OSC_ReferenceOscStopInSleepDisable(OSC_PLIB_ID, OSC_REFERENCE_1);
        }

        if(true == clkInit->referenceStopInIdle)
        {
            PLIB_OSC_ReferenceOscStopInIdleEnable(OSC_PLIB_ID, OSC_REFERENCE_1);
        }
        else
        {
            PLIB_OSC_ReferenceOscStopInIdleDisable(OSC_PLIB_ID, OSC_REFERENCE_1);
        }
    }
}

/******************************************************************************
  Function:
    void SYS_CLK_PIC32MZInit ( const SYS_CLK_INIT * const oscInit )

  Summary:
    Initializes the clkObject data structure as per the user input to the 
    'Initialize' function of the Clock module.

  Description:
    Initializes the clkObject data structure as per the user input. This
	gets called by the initialization routine, which will get called by the
	user.

  Remarks:
    None.
*/
#if defined (__PIC32MZ__)
void SYS_CLK_PIC32MZInit ( const SYS_CLK_INIT const * clkInit )
{
    int i;

    clkObject.systemClock = clkInit->systemClockFrequency;

    for (i = OSC_PERIPHERAL_BUS_1; i <= OSC_PERIPHERAL_BUS_5; i++) {
        clkObject.MZperipheralClock[i+1] = clkObject.systemClock /
            PLIB_OSC_PBClockDivisorGet(OSC_ID_0, i);
    }
    clkObject.MZperipheralClock[7] = clkObject.systemClock /
            PLIB_OSC_PBClockDivisorGet(OSC_ID_0, OSC_PERIPHERAL_BUS_7);
    clkObject.MZperipheralClock[8] = clkObject.systemClock /
            PLIB_OSC_PBClockDivisorGet(OSC_ID_0, OSC_PERIPHERAL_BUS_8);
    /* TODO: initialize ref clocks */

}
#endif

/******************************************************************************
  Function:
    unsigned int SYS_CLK_SystemClockSet ( SYS_CLK_SOURCE clockSource,
                                            unsigned long clockFrequency )
  Summary:
    Sets the clock source and frequency for the system clock.

  Description:
    This function sets the clock frequency and source for the system clock.

  Remarks:
    None.
*/

unsigned int SYS_CLK_SystemClockSet ( SYS_CLK_SOURCE clockSource,
                                        unsigned long clockFrequency )
{
    unsigned char calculatedRegValue, valueToReg, valueToReg2;
    unsigned long acheivedFreq = 0;
    unsigned int actualRegValue;

    switch (clockSource)
    {
        case SYS_CLK_SOURCE_FRC_BY_DIV:
            /* As we know the output and input frequencies, get the multiplier
            needed to get the output */
            calculatedRegValue = (SYS_CLK_FRC_CLOCK / clockFrequency)+0.5;

            /* Find the closest register value in the hardware */
            actualRegValue = SYS_CLK_FRCClosestDivisorGet(calculatedRegValue,
                                                    &valueToReg);

            /* The closest frequency that could be achieved */
            acheivedFreq = SYS_CLK_FRC_CLOCK / actualRegValue;
            break;
        case SYS_CLK_SOURCE_FRC_BY_16:
            /* The requested clock is FRC/16 */
            acheivedFreq = SYS_CLK_FRC_CLOCK / 16;
            break;

        case SYS_CLK_SOURCE_LPRC:
            /* Processor's internal LPRC clock */
            acheivedFreq = SYS_CLK_LPRC_CLOCK;
            break;
        /* Source of system clock is secondary oscillator */
        case SYS_CLK_SOURCE_SECONDARY:
            acheivedFreq = SYS_CLK_SECONDARY_CLOCK;
            break;
        /* Source of system clock is primary oscillator multiplied by
        the PLL value and divided by the divisor configured by software */
        case SYS_CLK_SOURCE_PRIMARY_SYSPLL:
            /* Find the closest register value in the hardware */
            acheivedFreq = SYS_CLK_ClosestFactorsGet(SYS_CLK_PRIMARY_CLOCK,
                    clockFrequency, &valueToReg, &valueToReg2);
            break;
        /* Source of system clock is primary oscillator */
        case SYS_CLK_SOURCE_PRIMARY:
            /* If the System clock is directly using the from the Primary oscillator
            clock, return the configured primary oscillator frequency */
            acheivedFreq = SYS_CLK_PRIMARY_CLOCK;
            break;
        /* Source of system clock is internal fast RC with PLL  */
        case SYS_CLK_SOURCE_FRC_SYSPLL:
            /* Find the closest register value in the hardware */
            acheivedFreq = SYS_CLK_ClosestFactorsGet(SYS_CLK_FRC_CLOCK,
                    clockFrequency, &valueToReg, &valueToReg2);
            break;
        /* Source of system clock is internal fast RC */
        case SYS_CLK_SOURCE_FRC:
            /* If the System clock is directly using the fast RC clock,
            return the Fast RC clock */
            acheivedFreq = SYS_CLK_FRC_CLOCK;
            break;
        default:
            break;
    }
    /* Check whether the difference between the achievable frequency and the
    frequecy requested is within the allowed range */
    if (true == SYS_CLK_FrequencyErrorCheck(clockFrequency, acheivedFreq))
    {
        SYS_CLK_SystemClockSourceSwitch (clockSource);
        /* Update the new clock source and clock frequency for the system
        clock */
        clkObject.systemClock = acheivedFreq;
    }
    else
    {
        return 0;
    }
    if (clockSource == SYS_CLK_SOURCE_FRC_BY_DIV)
    {
        PLIB_OSC_FRCDivisorSelect(OSC_PLIB_ID, valueToReg);
    }
    if (((clockSource == SYS_CLK_SOURCE_PRIMARY_SYSPLL))||
            (clockSource == SYS_CLK_SOURCE_FRC_SYSPLL))
    {
        //PLIB_OSC_SysPLLMultiplierSelect (OSC_PLIB_ID, valueToReg);
       // PLIB_OSC_SysPLLOutputDivisorSelect(OSC_PLIB_ID, valueToReg2);

    }

    return acheivedFreq;
}


/******************************************************************************
  Function:
    unsigned int SYS_CLK_UsbClockSet ( SYS_CLK_SOURCE clockSource,
					unsigned long clockFrequency )
  Summary:
    Sets the clock source and frequency for the USB clock.

  Description:
    This function sets the clock frequency and source for the USB clock.

  Remarks:
    None.
*/

unsigned int SYS_CLK_UsbClockSet ( SYS_CLK_SOURCE clockSource,
                                    unsigned long clockFrequency )
{
    unsigned long uFin;
    unsigned long acheivedFreq;

    switch (clockSource)
    {
        /* Source of USB clock is primary oscillator multiplied by
        the PLL value and divided by the divisor configured by software */
        case SYS_CLK_SOURCE_PRIMARY_USBPLL:
            /* If USB PLL is not enabled through configuration bits, this
            clock source option is invalid */
            if(SYS_CLK_CONFIG_USBPLL_ENABLE != true)
            {
                return 0;
            }
            //SYS_ASSERT( SYS_CLK_CONFIG_USBPLL_ENABLE == true ,
            //"For the selected clock source, USB PLL should be enabled
            //through configuration bits" );

            uFin = SYS_CLK_PRIMARY_CLOCK /
                       SYS_CLK_CONFIG_USBPLL_DIVISOR;
            /* Check whether the frequency input to the PLL is within limit */
            if(uFin > OSC_USBPLL_UFIN_MAX)
            {
                return 0;
            }
            //SYS_ASSERT( uFin < OSC_USBPLL_UFIN_MAX , "Input frequency to the
            //PLL is more than allowed limit, change the configuration setting" );

#if defined (__PIC32MX__)
            acheivedFreq = SYS_CLK_PRIMARY_CLOCK * SYS_CLK_USB_FIXED_PLL_MULTIPLIER/
                    (SYS_CLK_CONFIG_USBPLL_DIVISOR * SYS_CLK_USB_FIXED_DIVISOR );
#endif
            break;
        case SYS_CLK_SOURCE_PRIMARY:
            /* If the System clock is directly using the from the Primary oscillator
            clock, return the configured primary oscillator frequency */
            acheivedFreq = SYS_CLK_PRIMARY_CLOCK;
            break;
        /* Source of system clock is internal fast RC */
        case SYS_CLK_SOURCE_FRC:
            /* If the System clock is directly using the fast RC clock,
            return the Fast RC clock */
            acheivedFreq = SYS_CLK_FRC_CLOCK;
            break;
        default:
            break;
    }
    /* Check whether the achievable frequecy is withi limit */
    if (true == SYS_CLK_FrequencyErrorCheck(clockFrequency, acheivedFreq))
    {
        SYS_CLK_UsbClockSourceSwitch (clockSource);
    }
    else
    {
        return 0;
    }
    clkObject.usbClock = acheivedFreq;
    return acheivedFreq;
}


/******************************************************************************
  Function:
    unsigned long SYS_CLK_ReferenceClockSet ( SYS_CLK_SOURCE clockSource,
                                                unsigned long clockFrequency )
  Summary:
    Sets the clock source and frequency of the reference clock.

  Description:
    This function sets the clock frequency and source for the Reference clock.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ReferenceClockSet ( SYS_CLK_SOURCE clockSource,
                                            unsigned long clockFrequency )
{
    unsigned char calculatedRegValue, actualRegValue, valueToReg;
    unsigned long acheivedFreq, clockSourceFrequency;

    switch (clockSource)
        {
        case SYS_CLK_SOURCE_PBCLK_OUT:
            clockSourceFrequency = clkObject.peripheralClock;
            break;
        case SYS_CLK_SOURCE_SYSCLK_OUT:
            clockSourceFrequency = clkObject.systemClock;
            break;
        /* Source of Reference clock is primary oscillator */
        case SYS_CLK_SOURCE_PRIMARY:
            clockSourceFrequency = SYS_CLK_PRIMARY_CLOCK;
            break;
        case SYS_CLK_SOURCE_FRC:
            clockSourceFrequency = SYS_CLK_FRC_CLOCK;
            break;
        case SYS_CLK_SOURCE_LPRC:
            /* Processor's internal LPRC clock */
            clockSourceFrequency = SYS_CLK_LPRC_CLOCK;
            break;
        /* Source of reference clock is secondary oscillator */
        case SYS_CLK_SOURCE_SECONDARY:
            clockSourceFrequency = SYS_CLK_SECONDARY_CLOCK;
            break;
        case SYS_CLK_SOURCE_USBPLL_OUT:
            clockSourceFrequency = clkObject.usbClock;
            break;
        case SYS_CLK_SOURCE_SYSPLL_OUT:
#if defined (__PIC32MX__)
             clockSourceFrequency = SYS_CLK_PRIMARY_CLOCK /
                                    SYS_CLK_CONFIG_USBPLL_DIVISOR *
                                    SYS_CLK_USB_FIXED_PLL_MULTIPLIER;
#endif
            break;
        case SYS_CLK_SOURCE_EXTERNAL:
            clockSourceFrequency = SYS_CLK_EXTERNAL_CLOCK;
            break;
        default:
            return 0;
    }
    calculatedRegValue = (clockSourceFrequency / clockFrequency )+0.5;
    if(calculatedRegValue == 0x01)
    {
        valueToReg = 0;
        acheivedFreq = clockFrequency;
    }
    else
    {
        /* As we know the output and input frequencies, get the multiplier
        needed to get the output */
        /* Find the closest register value in the hardware */
        actualRegValue = SYS_CLK_ReferenceClosestDivisorGet(calculatedRegValue,
                                                &valueToReg);
        /* The closest frequency that could be achieved */
        acheivedFreq = clockSourceFrequency / actualRegValue;

        if (true != SYS_CLK_FrequencyErrorCheck(clockFrequency, acheivedFreq))
        {
            //SYS_ASSERT( "The Reference clock frequency reuested is not
            //    achievable" );
            return 0;
        }
    }

//    PLIB_OSC_ReferenceOscDivisorValueSet (OSC_PLIB_ID, valueToReg);

    /* Do the actual clock switch */
    SYS_CLK_ReferenceClockSwitch(clockSource);
    clkObject.referenceClock = acheivedFreq;
    return acheivedFreq;
}


/******************************************************************************
  Function:
    unsigned long SYS_CLK_PeripheralClockSet ( SYS_CLK_SOURCE clockSource,
						unsigned long clockFrequency )
  Summary:
    Sets the clock source and frequency for the peripheral clock.

  Description:
    This function sets the clock frequency and source for the peripheral clock.

  Remarks:
    None.
*/

unsigned long SYS_CLK_PeripheralClockSet ( SYS_CLK_SOURCE clockSource,
					   unsigned long clockFrequency )
{
    unsigned char calculatedRegValue, actualRegValue, valueToReg=0;
    unsigned long acheivedFreq, clockSourceFrequency;

    //SYS_ASSERT( clkObject.systemClock == 0,
    //"SYS_CLK_Initialize function should be called before calling this API. " );
    switch (clockSource)
    {
        case SYS_CLK_SOURCE_SYSCLK_OUT:
            clockSourceFrequency = clkObject.systemClock;
            break;
        default:
            return 0;
    }
    /* As we know the output and input frequencies, get the multiplier
    needed to get the output */
    calculatedRegValue = (clockSourceFrequency / clockFrequency )+0.5;

    /* Find the closest register value in the hardware */
    actualRegValue = SYS_CLK_PeripheralClosestDivisorGet(calculatedRegValue,
                                            &valueToReg);
    if (actualRegValue == 0)
    {
        return 0;
    }
    /* The closest frequency that could be achieved */
    acheivedFreq = clockSourceFrequency / actualRegValue;

    if (true == SYS_CLK_FrequencyErrorCheck(clockFrequency, acheivedFreq))
    {
       // PLIB_OSC_PBClockDivisorSet ( OSC_PLIB_ID, valueToReg );
        clkObject.peripheralClock = acheivedFreq;
        return acheivedFreq;
    }
    //SYS_ASSERT( "The peripheral clock frequency reuested is not achievable" );
    return 0;
}


/******************************************************************************
  Function:
    bool SYS_CLK_FrequencyErrorCheck( unsigned long inpFreq,
                                        unsigned long acheivedFreq )
  Summary:
    Checks whether the difference between the user requested clock rate and
    the maximum achievable clock is within limit.

  Description:
    This function checks whether the difference between the user requested clock
    rate and the maximum achievable clock is within limit.
   		true - The differece betwee clocks is within limit.
		false - The differece betwee clocks is not within limit.

  Remarks:
    None.
*/

bool SYS_CLK_FrequencyErrorCheck(unsigned long inpFreq, unsigned long acheivedFreq)
{
    /* Get the difference between frequency requested and achieved  */
    if (abs(inpFreq - acheivedFreq) >SYS_CLK_CLOCK_CONFIG_ERROR)
    {
        return false;
    }
    return true;
}


/******************************************************************************
  Function:
    void SYS_CLK_SystemClockSourceSwitch ( SYS_CLK_SOURCE clockSource )

  Summary:
    Initiates the clock switch for the system clock.

  Description:
    This function initiates the clock switch for the system clock.

  Remarks:
    None.
*/

void SYS_CLK_SystemClockSourceSwitch ( SYS_CLK_SOURCE clockSource )
{
    //SYS_ASSERT (SYS_CLK_SysSourceToRegValue(clockSource) != -1, "Invalid source");
    PLIB_OSC_SysClockSelect(OSC_PLIB_ID,
            SYS_CLK_SysSourceToRegValue(clockSource));
}


/******************************************************************************
  Function:
    void SYS_CLK_UsbClockSourceSwitch ( SYS_CLK_SOURCE clockSource )

  Summary:
    Initiates the clock switch for the USB clock.

  Description:
    This function initiates the clock switch for the system clock.

  Remarks:
    None.
*/

void SYS_CLK_UsbClockSourceSwitch ( SYS_CLK_SOURCE clockSource )
{
    //SYS_ASSERT (SYS_CLK_UsbSourceToRegValue(clockSource) != -1, "Invalid source");
    PLIB_OSC_UsbClockSourceSelect(OSC_PLIB_ID,
        SYS_CLK_UsbSourceToRegValue(clockSource));
}


/******************************************************************************
  Function:
    unsigned long SYS_CLK_ClosestFactorsGet(    unsigned long sourceFrequency,
                                                unsigned long requestedFrequency,
                                                unsigned char *valueToReg1,
                                                unsigned char *valueToReg2 )

  Summary:
    Gets the value of the multiplier and divisor which is closest to the
    expected value for the system PLL.

  Description:
    This function gets the value of the multiplier and divisor which is closest
    to the expected value for the system PLL.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ClosestFactorsGet(   unsigned long sourceFrequency,
                                        unsigned long requestedFrequency,
                                        unsigned char *valueToReg1,
                                        unsigned char *valueToReg2 )
{
    uint8_t index1, index2;
    unsigned long tempFrequency, PrevFrequency =0;

    for(index1=0;index1<8;index1++)
    {
        for(index2=0;index2<8;index2++)
        {
        tempFrequency = ((sourceFrequency / SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR)*
            (sysPllMultiplierLookup[index1]) /
            sysPllDivisorLookup[index2] );

            if ((abs(requestedFrequency - tempFrequency)) <
                    (abs(requestedFrequency - PrevFrequency)))
            {
                    PrevFrequency = tempFrequency;
                    *valueToReg1 = index1;
                    *valueToReg2 = index2;
            }

        }
    }
    return PrevFrequency;
}


/******************************************************************************
  Function:
    char SYS_CLK_ReferenceClosestDivisorGet( unsigned char regValue,
						unsigned char *valueToReg )

  Summary:
    Gets the value of the reference clock divisor which is closest to the
    expected value.

  Description:
    This function gets the value of the reference clock divisor which is closest
    to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_ReferenceClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valueToReg )
{
   /* if(regValue > OSC_REFERENCE_MAX_DIV)
    {
        return 0;
    }
    *valueToReg = regValue/2;*/

    return (*valueToReg * 2);
}


/******************************************************************************
  Function:
    void SYS_CLK_ReferenceClockSwitch( SYS_CLK_SOURCE clockSource )

  Summary:
    Initiates the clock switch for the Reference clock out.

  Description:
    This function initiates the reference clock switch.

  Remarks:
    None.
*/

void SYS_CLK_ReferenceClockSwitch( SYS_CLK_SOURCE clockSource )
{
    //SYS_ASSERT (SYS_CLK_ReferenceSourceToRegValue(clockSource) != -1,
    //"Invalid source");
  //  PLIB_OSC_ReferenceOscBaseClockSelect ( OSC_PLIB_ID,
           // SYS_CLK_ReferenceSourceToRegValue(clockSource) );

}


/******************************************************************************
  Function:
   char SYS_CLK_FRCClosestDivisorGet( unsigned char regValue,
                                                    unsigned char *valueToReg )

  Summary:
    Gets the value of the FRC clock divisor which is closest to the
    expected value.
.
  Description:
    This function gets the value of the FRC clock divisor which is
    closest to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_FRCClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valueToReg )
{
    uint8_t index, prevValue =0;

    for(index=0;index<8;index++)
    {
        if ((abs(regValue - FRCDivisorLookup[index])) <
                        (abs(regValue - prevValue)))
        {
            prevValue = FRCDivisorLookup[index];
            *valueToReg = index;
        }
    }
    return prevValue;
}


/******************************************************************************
  Function:
   char SYS_CLK_PeripheralClosestDivisorGet( unsigned char regValue,
                                                    unsigned char *valueToReg )

  Summary:
    Gets the value of the peripheral clock divisor which is closest to the
    expected value.
.
  Description:
    This function gets the value of the peripheral clock divisor which is
    closest to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_PeripheralClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valueToReg )
{
    uint8_t index, prevValue =0;

    for(index=0;index<4;index++)
    {
        if ((abs(regValue - peripheralDivisorLookup[index])) <
                        (abs(regValue - prevValue)))
        {
            prevValue = peripheralDivisorLookup[index];
            *valueToReg = index;
        }
    }
    return prevValue;
}
/*******************************************************************************
End of File
*/

