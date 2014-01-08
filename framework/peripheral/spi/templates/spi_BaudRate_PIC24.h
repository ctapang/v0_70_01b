/*******************************************************************************
  SPI Peripheral Library Template Implementation

  File Name:
    spi_BaudRate_PIC24.h

  Summary:
    SPI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : BaudRate
    and its Variant : PIC24
    For following APIs :
        PLIB_SPI_BaudRateSet
        PLIB_SPI_ExistsBaudRate

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

//DOM-IGNORE-END

#ifndef _SPI_BAUDRATE_PIC24_H
#define _SPI_BAUDRATE_PIC24_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SPI_BAUD_RATE_PIC24_VREG(index)

  MASKs: 
    _SPI_BAUD_RATE_PIC24_MASK(index)

  POSs: 
    _SPI_BAUD_RATE_PIC24_POS(index)

  LENs: 
    _SPI_BAUD_RATE_PIC24_LEN(index)

*/

typedef struct
{
    SPI_PRESCALE_PRIMARY    priPrescale;
    uint16_t                priDivisor;

} _PRI_DIVISOR;


static const _PRI_DIVISOR s_priPrescale[] =
{
    {SPI_PRESCALE_PRIMARY_1,       1},
    {SPI_PRESCALE_PRIMARY_4,       4},
    {SPI_PRESCALE_PRIMARY_16,      16},
    {SPI_PRESCALE_PRIMARY_64,      64}
};


typedef struct
{
    SPI_PRESCALE_SECONDARY  secPrescale;
    uint16_t                secDivisor;

} _SEC_DIVISOR;


static const _SEC_DIVISOR s_secPrescale[] =
{
    {SPI_PRESCALE_SECONDARY_1,       1},
    {SPI_PRESCALE_SECONDARY_2,       2},
    {SPI_PRESCALE_SECONDARY_3,       3},
    {SPI_PRESCALE_SECONDARY_4,       4},
    {SPI_PRESCALE_SECONDARY_5,       5},
    {SPI_PRESCALE_SECONDARY_6,       6},
    {SPI_PRESCALE_SECONDARY_7,       7},
    {SPI_PRESCALE_SECONDARY_8,       8}
};


//******************************************************************************
/* Function :  SPI_BaudRateSet_PIC24

  Summary:
    Implements PIC24 variant of PLIB_SPI_BaudRateSet 

  Description:
    This template implements the PIC24 variant of the PLIB_SPI_BaudRateSet function.
*/

PLIB_TEMPLATE void SPI_BaudRateSet_PIC24( SPI_MODULE_ID index , uint32_t clockFrequency , uint32_t baudRate )
{
    uint32_t calcPrescaler = 0;
    uint16_t t_prescaler, i, j;
    SPI_PRESCALE_PRIMARY t_pri;
    SPI_PRESCALE_SECONDARY t_sec;

    /* Baud Clock formula,
       Fsck = Fcy / (Pri Prescaler * Sec Prescaler) */

    /* Normalize the prescaler so as not to loose out the
       very first precision */
    calcPrescaler = ( clockFrequency * 10 / baudRate );

    /* If prescaler value is 1 & the freq is 16MHz, just return */
    if( ( calcPrescaler == 10 ) && ( clockFrequency == 16000000 ) )
        return;

    for( i=0 ; i<=sizeof(s_priPrescale)/4 ; i++ )
    {
        /* Get the primary prescale divisor value */
        t_pri = s_priPrescale[i].priDivisor;

        for( j=0 ; j<=sizeof(s_secPrescale)/4 ; j++ )
        {
            /* Get the secondary prescale divisor value */
            t_sec = s_secPrescale[j].secDivisor;

            t_prescaler = t_pri * t_sec * 10;

            /* Little tolerance to check around the calculated prescaler */
            if( ( t_prescaler >= ( calcPrescaler - 2 ) ) &&
                ( t_prescaler <= ( calcPrescaler + 2 ) ) )
            {
                /* Update the Primary prescale value */
                _SFR_FIELD_WRITE( _SPI_PRIMARY_PRESCALE_VREG( index ),
                                  _SPI_PRIMARY_PRESCALE_MASK( index ),
                                  _SPI_PRIMARY_PRESCALE_POS( index ),
                                  s_priPrescale[i].priPrescale );
                
                /* Update the Secondary prescale value */
                _SFR_FIELD_WRITE( _SPI_SECONDARY_PRESCALE_VREG( index ),
                                  _SPI_SECONDARY_PRESCALE_MASK( index ),
                                  _SPI_SECONDARY_PRESCALE_POS( index ),
                                  s_secPrescale[i].secPrescale );
            }
        }
    }
}


//******************************************************************************
/* Function :  SPI_ExistsBaudRate_PIC24

  Summary:
    Implements PIC24 variant of PLIB_SPI_ExistsBaudRate

  Description:
    This template implements the PIC24 variant of the PLIB_SPI_ExistsBaudRate function.
*/

PLIB_TEMPLATE bool SPI_ExistsBaudRate_PIC24( SPI_MODULE_ID index )
{
    return true;
}


#endif /*_SPI_BAUDRATE_PIC24_H*/

/******************************************************************************
 End of File
*/

