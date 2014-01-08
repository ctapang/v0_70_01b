/*******************************************************************************
  MPLAB Harmony ADC Potentiometer Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony adc_pot main function

  Description:
    This example repeatedly reads the Explorer-16 potentiometer and
    outputs a pattern on the LEDs corresponding to the potentiometer's
    position.

  Tested with:
    -PIC32MX795F512L on the Explorer-16 Demo Board
    -XC32 compiler, MPLAB X IDE
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include <stdlib.h>
#include "peripheral/ports/plib_ports.h"
#include "peripheral/adc/plib_adc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx2, FCKSM = CSECME, OSCIOFNC = ON
#define SYS_FREQUENCY (80000000L)


// *****************************************************************************
// *****************************************************************************
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

int readPotentiometer(void);


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
     /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Set lower 8 bits of PORTA as output for LEDs, clear the bits to ensure
       there is no mismatch when they are toggled */
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Set pin AN2 as analog input */
    PLIB_PORTS_PinModeSelect(PORTS_ID_0, PORTS_ANALOG_PIN_2, PORTS_PIN_MODE_ANALOG);
    
    /* ADC setup - ouput in integer format, trigger mode auto, enable autosample */
    PLIB_ADC_ResultFormatSelect(ADC_ID_1, ADC_RESULT_FORMAT_INTEGER_16BIT);
    PLIB_ADC_SamplingModeSelect(ADC_ID_1, ADC_SAMPLING_MODE_MUXA);
    PLIB_ADC_ConversionTriggerSourceSelect(ADC_ID_1, ADC_CONVERSION_TRIGGER_INTERNAL_COUNT);
    PLIB_ADC_VoltageReferenceSelect(ADC_ID_1, ADC_REFERENCE_VDD_TO_AVSS );
    PLIB_ADC_SampleAcqusitionTimeSet(ADC_ID_1, 0x1F);
    PLIB_ADC_ConversionClockSet(ADC_ID_1, SYS_FREQUENCY, 32);

    /* Connect AN2 as positive input, Vref- as negative input */
    PLIB_ADC_MuxChannel0InputPositiveSelect(ADC_ID_1, ADC_MUX_A, ADC_INPUT_POSITIVE_AN2);
    PLIB_ADC_MuxChannel0InputNegativeSelect(ADC_ID_1, ADC_MUX_A, ADC_INPUT_NEGATIVE_VREF_MINUS);

    /* Enable the ADC module */
    PLIB_ADC_Enable(ADC_ID_1);

    int potValue;
    int i;
    int ledMask;

    /* Stuck in this loop, reading the potentiometer and writing to the LEDs */
    while (1)
    {
        potValue = readPotentiometer();
        potValue = potValue >> 7; /* 10-bit value to 3-bit value */

        ledMask = 0;

        /* Creates a mask for the LEDs, corresponding to the value read from
           the potentiometer */
        for (i = 0; i <= potValue; i++)
        {
            ledMask |=  1<<(i);
        }

        /* Write the mask to the LEDs */
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)ledMask);
    }

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
/*
  Function:
    int readPotentiometer (void)

  Summary:
    Reads the ADC and returns the result

  Description:
    Samples the ADC input and conversion is started automatically (automatic
    sample mode). Reads back the result when conversion is complete.
*/

int readPotentiometer(void)
{
    PLIB_ADC_SamplingStart(ADC_ID_1);
    
    while (!PLIB_ADC_ConversionHasCompleted(ADC_ID_1));

    return PLIB_ADC_ResultGetByIndex(ADC_ID_1, 0);
}


/*******************************************************************************
 End of File
*/