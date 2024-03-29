/*******************************************************************************
  Peripheral Library Interface Header

  Company:
    Microchip Technology Inc.

  File Name:
    plib.h

  Summary:
    This file aggregates all of the peripheral library interface headers.

  Description:
    This file aggregates all of the peripheral library interface headers so
    client code only needs to include this one single header to obtain
    prototypes and definitions for the interfaces to all peripheral libraries.

    Peripheral Libraries (PLIBs) provide low-level abstractions of peripherals
    found on Microchip microcontrollers in the form of a convenient C language
    interface.  PLIBs can be used to simplify low-level access to peripheral
    modules without the necessity of interacting directly with module
    registers, thus hiding differences from one microcontroller to another.

  Remarks:
    The directory in which this file resides should be added to the compiler's
    search path for header files.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012,2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _PLIB_H_
#define _PLIB_H_

  
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

/* Individual Peripheral Library Interface Headers */
#include "peripheral/adc/plib_adc.h" // not present in mz devices, use adcp in stead
#include "peripheral/adcp/plib_adcp.h" // only in mz devices
#include "peripheral/bmx/plib_bmx.h" // not present in mz devices, use sb in stead
#include "peripheral/can/plib_can.h"
#include "peripheral/cmp/plib_cmp.h"
#include "peripheral/devcon/plib_devcon.h"
#include "peripheral/dma/plib_dma.h"
#include "peripheral/dmt/plib_dmt.h"
#include "peripheral/ebi/plib_ebi.h" // only in mz devices
#include "peripheral/eth/plib_eth.h"
#include "peripheral/eth/src/plib_eth_legacy.h"
#include "peripheral/i2c/plib_i2c.h"
#include "peripheral/i2c/plib_i2c_helper_macros.h"
#include "peripheral/ic/plib_ic.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/nvm/plib_nvm.h"
#include "peripheral/oc/plib_oc.h"
#include "peripheral/osc/plib_osc.h"
#include "peripheral/pcache/plib_pcache.h"
#include "peripheral/pmp/plib_pmp.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/power/plib_power.h"
#include "peripheral/reset/plib_reset.h"
#include "peripheral/rtcc/plib_rtcc.h"
#include "peripheral/sb/plib_sb.h" // only in mz devices
#include "peripheral/spi/plib_spi.h"
#include "peripheral/sqi/plib_sqi.h" // only in mz devices
#include "peripheral/tmr/plib_tmr.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/wdt/plib_wdt.h"

#endif // _PLIB_H

/*******************************************************************************
 End of File
*/

