/*******************************************************************************
  Clock System Service Internal Function Prototypes

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk_internal.h

  Summary:
    Clock System Service internal function prototypes.

  Description:
    This file contains the Clock System Service internal function prototypes.
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

#ifndef _SYS_CLK_INTERNAL_H
#define _SYS_CLK_INTERNAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

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

unsigned int SYS_CLK_SystemClockSet (   SYS_CLK_SOURCE clockSource,
                                        unsigned long clockFrequency );


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

unsigned int SYS_CLK_UsbClockSet (  SYS_CLK_SOURCE clockSource,
                                    unsigned long clockFrequency );


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
					   unsigned long clockFrequency );


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

void SYS_CLK_SystemClockSourceSwitch ( SYS_CLK_SOURCE clockSource );


/******************************************************************************
  Function:
    bool SYS_CLK_FrequencyErrorCheck( unsigned long inpFreq,
                                        unsigned long acheivedFreq )
  Summary:
    Checks whether the difference between the user requested clock rate and
    the maximum achievable clock is within limits.

  Description:
    This function checks whether the difference between the user requested clock
    rate and the maximum achievable clock is within limits.
    
  Returns:
    - true  - The difference between clocks is within limits
    - false - The difference between clocks is not within limits

  Remarks:
    None.
*/

bool SYS_CLK_FrequencyErrorCheck(unsigned long inpFreq,
                                    unsigned long acheivedFreq);


/******************************************************************************
  Function:
    unsigned long SYS_CLK_ClosestFactorsGet(    unsigned long sourceFrequency,
                                                unsigned long requestedFrequency,
                                                unsigned char *valueToReg1,
                                                unsigned char *valueToReg2 )

  Summary:
    Gets the value of the multiplier and divisor that is closest to the
    expected value for the system PLL.

  Description:
    This function gets the value of the multiplier and divisor that is closest
    to the expected value for the system PLL.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ClosestFactorsGet(   unsigned long sourceFrequency,
                                        unsigned long requestedFrequency,
                                        unsigned char *valueToReg1,
                                        unsigned char *valueToReg2 );



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

void SYS_CLK_UsbClockSourceSwitch ( SYS_CLK_SOURCE clockSource );



/******************************************************************************
  Function:
    unsigned long SYS_CLK_ReferenceClockSet ( SYS_CLK_SOURCE clockSource,
                                                unsigned long clockFrequency )
  Summary:
    Sets the clock source and frequency of the reference clock.

  Description:
    This function sets the clock frequency and source for the reference clock.

  Remarks:
    None.
*/

unsigned long SYS_CLK_ReferenceClockSet ( SYS_CLK_SOURCE clockSource,
                                            unsigned long clockFrequency );



/******************************************************************************
  Function:
    char SYS_CLK_ReferenceClosestDivisorGet( unsigned char regValue,
						unsigned char *valueToReg )

  Summary:
    Gets the value of the reference clock divisor that is closest to the
    expected value.

  Description:
    This function gets the value of the reference clock divisor that is closest
    to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_ReferenceClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valuetoWrite );


/******************************************************************************
  Function:
    void SYS_CLK_ReferenceClockSwitch( SYS_CLK_SOURCE clockSource )

  Summary:
    Initiates the clock switch for the reference clock out.

  Description:
    This function initiates the reference clock switch.

  Remarks:
    None.
*/

void SYS_CLK_ReferenceClockSwitch( SYS_CLK_SOURCE clockSource );


/******************************************************************************
  Function:
   char SYS_CLK_PeripheralClosestDivisorGet( unsigned char regValue,
                                                    unsigned char *valueToReg )

  Summary:
    Gets the value of the peripheral clock divisor that is closest to the
    expected value.

  Description:
    This function gets the value of the peripheral clock divisor that is
    closest to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_PeripheralClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valueToReg );


/******************************************************************************
  Function:
   char SYS_CLK_FRCClosestDivisorGet( unsigned char regValue,
                                                    unsigned char *valueToReg )

  Summary:
    Gets the value of the FRC clock divisor that is closest to the
    expected value.

  Description:
    This function gets the value of the FRC clock divisor that is
    closest to the expected value.

  Remarks:
    None.
*/

char SYS_CLK_FRCClosestDivisorGet( unsigned char regValue,
                                            unsigned char *valueToReg );


/******************************************************************************
  Function:
   void SYS_CLK_HardwareRegisterUpdate ( const SYS_CLK_INIT const * clkInit )

  Summary:
   Does the actual register write on initializing the clock.

  Description:
    This function does the actual register write on initializing the clock.

  Remarks:
    None.
*/

void SYS_CLK_HardwareRegisterUpdate ( const SYS_CLK_INIT const * clkInit );


#endif //#ifndef _SYS_OSC_INTERNAL_H

/*******************************************************************************
 End of File
*/

