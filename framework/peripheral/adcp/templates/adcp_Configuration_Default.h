/*******************************************************************************
  ADCP Peripheral Library Template Implementation

  File Name:
    adcp_Configuration_Default.h

  Summary:
    ADCP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Configuration
    and its Variant : Default
    For following APIs :
        PLIB_ADCP_Configure
        PLIB_ADCP_ExistsConfiguration

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

#ifndef _ADCP_CONFIGURATION_DEFAULT_H
#define _ADCP_CONFIGURATION_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADCP_VOLTAGE_REF_SELECT_VREG(index)
    _ADCP_BOOST_VREF_VREG(index)
    _ADCP_FRACTIONAL_MODE_VREG(index)
    _ADCP_STOP_IN_IDLE_VREG(index)
    _ADCP_LV_GLOBAL_INT_ENABLE_VREG(index)
    _ADCP_CLOCK_SRC_SELECT_VREG(index)
    _ADCP_CLOCK_DIVIDER_VREG(index)
    _ADCP_SCAN_TRIG_SRC_VREG(index)
    _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_VREG(index)
    _ADCP_EARLY_INT_ENABLE_VREG(index)
    _ADCP_CLASS23_SH_SAMPLE_TIME_VREG(index)
    _ADCP_CALIBRATION_DATA_VREG(index)

  MASKs: 
    _ADCP_VOLTAGE_REF_SELECT_MASK(index)
    _ADCP_BOOST_VREF_MASK(index)
    _ADCP_FRACTIONAL_MODE_MASK(index)
    _ADCP_STOP_IN_IDLE_MASK(index)
    _ADCP_LV_GLOBAL_INT_ENABLE_MASK(index)
    _ADCP_CLOCK_SRC_SELECT_MASK(index)
    _ADCP_CLOCK_DIVIDER_MASK(index)
    _ADCP_SCAN_TRIG_SRC_MASK(index)
    _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_MASK(index)
    _ADCP_EARLY_INT_ENABLE_MASK(index)
    _ADCP_CLASS23_SH_SAMPLE_TIME_MASK(index)
    _ADCP_CALIBRATION_DATA_MASK(index)

  POSs: 
    _ADCP_VOLTAGE_REF_SELECT_POS(index)
    _ADCP_BOOST_VREF_POS(index)
    _ADCP_FRACTIONAL_MODE_POS(index)
    _ADCP_STOP_IN_IDLE_POS(index)
    _ADCP_LV_GLOBAL_INT_ENABLE_POS(index)
    _ADCP_CLOCK_SRC_SELECT_POS(index)
    _ADCP_CLOCK_DIVIDER_POS(index)
    _ADCP_SCAN_TRIG_SRC_POS(index)
    _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_POS(index)
    _ADCP_EARLY_INT_ENABLE_POS(index)
    _ADCP_CLASS23_SH_SAMPLE_TIME_POS(index)
    _ADCP_CALIBRATION_DATA_POS(index)

  LENs: 
    _ADCP_VOLTAGE_REF_SELECT_LEN(index)
    _ADCP_BOOST_VREF_LEN(index)
    _ADCP_FRACTIONAL_MODE_LEN(index)
    _ADCP_STOP_IN_IDLE_LEN(index)
    _ADCP_LV_GLOBAL_INT_ENABLE_LEN(index)
    _ADCP_CLOCK_SRC_SELECT_LEN(index)
    _ADCP_CLOCK_DIVIDER_LEN(index)
    _ADCP_SCAN_TRIG_SRC_LEN(index)
    _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_LEN(index)
    _ADCP_EARLY_INT_ENABLE_LEN(index)
    _ADCP_CLASS23_SH_SAMPLE_TIME_LEN(index)
    _ADCP_CALIBRATION_DATA_LEN(index)

 */


//******************************************************************************

/* Function :  ADCP_Configure_Default

  Summary:
    Implements Default variant of PLIB_ADCP_Configure 

  Description:
    This template implements the Default variant of the PLIB_ADCP_Configure function.
 */

PLIB_TEMPLATE void ADCP_Configure_Default ( ADCP_MODULE_ID index , ADCP_VREF_SOURCE voltageRefSelect , bool boostVref , bool fractionalOutputOn , bool stopInIdle ,
        ADCP_CLOCK_SOURCE adcClockSource , int8_t adcClockDivider , int8_t oversampleDigFilterSamTime , int8_t earlyIntEnable , int8_t class2and3SampleTime )
{
    _SFR_FIELD_WRITE ( _ADCP_VOLTAGE_REF_SELECT_VREG ( index ) , _ADCP_VOLTAGE_REF_SELECT_MASK ( index ) , _ADCP_VOLTAGE_REF_SELECT_POS ( index ) , voltageRefSelect ) ;
    _SFR_BIT_WRITE ( _ADCP_BOOST_VREF_VREG ( index ) , _ADCP_BOOST_VREF_POS ( index ) , boostVref ) ;
    _SFR_BIT_WRITE ( _ADCP_FRACTIONAL_MODE_VREG ( index ) , _ADCP_FRACTIONAL_MODE_POS ( index ) , fractionalOutputOn ) ;
    _SFR_BIT_WRITE ( _ADCP_STOP_IN_IDLE_VREG ( index ) , _ADCP_STOP_IN_IDLE_POS ( index ) , stopInIdle ) ;
    _SFR_FIELD_WRITE ( _ADCP_CLOCK_SRC_SELECT_VREG ( index ) , _ADCP_CLOCK_SRC_SELECT_MASK ( index ) , _ADCP_CLOCK_SRC_SELECT_POS ( index ) , adcClockSource ) ;
    _SFR_FIELD_WRITE ( _ADCP_CLOCK_DIVIDER_VREG ( index ) , _ADCP_CLOCK_DIVIDER_MASK ( index ) , _ADCP_CLOCK_DIVIDER_POS ( index ) , adcClockDivider ) ;
    _SFR_FIELD_WRITE ( _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_VREG ( index ) , _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_MASK ( index ) , _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_POS ( index ) , oversampleDigFilterSamTime ) ;
    _SFR_FIELD_WRITE ( _ADCP_EARLY_INT_ENABLE_VREG ( index ) , _ADCP_EARLY_INT_ENABLE_MASK ( index ) , _ADCP_EARLY_INT_ENABLE_POS ( index ) , earlyIntEnable ) ;
    _SFR_FIELD_WRITE ( _ADCP_CLASS23_SH_SAMPLE_TIME_VREG ( index ) , _ADCP_CLASS23_SH_SAMPLE_TIME_MASK ( index ) , _ADCP_CLASS23_SH_SAMPLE_TIME_POS ( index ) , class2and3SampleTime ) ;
    _SFR_WRITE ( _ADCP_CALIBRATION_DATA_VREG ( index )  , DEVADC1 ) ;
    _SFR_WRITE ( _ADCP_CALIBRATION_DATA_VREG ( index ) + 1 , DEVADC2 ) ;
    _SFR_WRITE ( _ADCP_CALIBRATION_DATA_VREG ( index ) + 2 , DEVADC3 ) ;
    _SFR_WRITE ( _ADCP_CALIBRATION_DATA_VREG ( index ) + 3 , DEVADC4 ) ;
    _SFR_WRITE ( _ADCP_CALIBRATION_DATA_VREG ( index ) + 4 , DEVADC5 ) ;
}


//******************************************************************************

/* Function :  ADCP_ExistsConfiguration_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ExistsConfiguration

  Description:
    This template implements the Default variant of the PLIB_ADCP_ExistsConfiguration function.
 */

PLIB_TEMPLATE bool ADCP_ExistsConfiguration_Default ( ADCP_MODULE_ID index )
{
    return true ;
}


#endif /*_ADCP_CONFIGURATION_DEFAULT_H*/

/******************************************************************************
 End of File
 */

