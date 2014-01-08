
/*******************************************************************************
  I2C Library Interface Definition: Private Header

  Summary:
    This file contains private definitions for the the Application Program
    Interface (API) definition  for the I2C peripheral library.
    
  Description:
    This file defines the register structure for the I2C library.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:      I2Cprivate.h
Processor:      PIC32MX
Compiler:       Microchip MPLAB XC32 v1.00 or higher

Copyright © 2008-2009 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _I2C_PRIVATE_H_
#define _I2C_PRIVATE_H_


#include <xc.h>
#include <GenericTypeDefs.h>
#include "i2c.h"

// *****************************************************************************
// Bit Definitions
// *****************************************************************************

#define _I2CCON_SEN_POSITION                    0x00000000
#define _I2CCON_SEN_MASK                        0x00000001
#define _I2CCON_SEN_LENGTH                      0x00000001

#define _I2CCON_RSEN_POSITION                   0x00000001
#define _I2CCON_RSEN_MASK                       0x00000002
#define _I2CCON_RSEN_LENGTH                     0x00000001

#define _I2CCON_PEN_POSITION                    0x00000002
#define _I2CCON_PEN_MASK                        0x00000004
#define _I2CCON_PEN_LENGTH                      0x00000001

#define _I2CCON_RCEN_POSITION                   0x00000003
#define _I2CCON_RCEN_MASK                       0x00000008
#define _I2CCON_RCEN_LENGTH                     0x00000001

#define _I2CCON_ACKEN_POSITION                  0x00000004
#define _I2CCON_ACKEN_MASK                      0x00000010
#define _I2CCON_ACKEN_LENGTH                    0x00000001

#define _I2CCON_ACKDT_POSITION                  0x00000005
#define _I2CCON_ACKDT_MASK                      0x00000020
#define _I2CCON_ACKDT_LENGTH                    0x00000001

#define _I2CCON_STREN_POSITION                  0x00000006
#define _I2CCON_STREN_MASK                      0x00000040
#define _I2CCON_STREN_LENGTH                    0x00000001

#define _I2CCON_GCEN_POSITION                   0x00000007
#define _I2CCON_GCEN_MASK                       0x00000080
#define _I2CCON_GCEN_LENGTH                     0x00000001

#define _I2CCON_SMEN_POSITION                   0x00000008
#define _I2CCON_SMEN_MASK                       0x00000100
#define _I2CCON_SMEN_LENGTH                     0x00000001

#define _I2CCON_DISSLW_POSITION                 0x00000009
#define _I2CCON_DISSLW_MASK                     0x00000200
#define _I2CCON_DISSLW_LENGTH                   0x00000001

#define _I2CCON_A10M_POSITION                   0x0000000A
#define _I2CCON_A10M_MASK                       0x00000400
#define _I2CCON_A10M_LENGTH                     0x00000001

#define _I2CCON_STRICT_POSITION                 0x0000000B
#define _I2CCON_STRICT_MASK                     0x00000800
#define _I2CCON_STRICT_LENGTH                   0x00000001

#define _I2CCON_SCLREL_POSITION                 0x0000000C
#define _I2CCON_SCLREL_MASK                     0x00001000
#define _I2CCON_SCLREL_LENGTH                   0x00000001

#define _I2CCON_SIDL_POSITION                   0x0000000D
#define _I2CCON_SIDL_MASK                       0x00002000
#define _I2CCON_SIDL_LENGTH                     0x00000001

#define _I2CCON_ON_POSITION                     0x0000000F
#define _I2CCON_ON_MASK                         0x00008000
#define _I2CCON_ON_LENGTH                       0x00000001

#define _I2CCON_IPMIEN_POSITION                 0x0000000B
#define _I2CCON_IPMIEN_MASK                     0x00000800
#define _I2CCON_IPMIEN_LENGTH                   0x00000001

#define _I2CCON_I2CSIDL_POSITION                0x0000000D
#define _I2CCON_I2CSIDL_MASK                    0x00002000
#define _I2CCON_I2CSIDL_LENGTH                  0x00000001

#define _I2CCON_I2CEN_POSITION                  0x0000000F
#define _I2CCON_I2CEN_MASK                      0x00008000
#define _I2CCON_I2CEN_LENGTH                    0x00000001

#define _I2CCON_w_POSITION                      0x00000000
#define _I2CCON_w_MASK                          0xFFFFFFFF
#define _I2CCON_w_LENGTH                        0x00000020

#define _I2CSTAT_TBF_POSITION                   0x00000000
#define _I2CSTAT_TBF_MASK                       0x00000001
#define _I2CSTAT_TBF_LENGTH                     0x00000001

#define _I2CSTAT_RBF_POSITION                   0x00000001
#define _I2CSTAT_RBF_MASK                       0x00000002
#define _I2CSTAT_RBF_LENGTH                     0x00000001

#define _I2CSTAT_R_W_POSITION                   0x00000002
#define _I2CSTAT_R_W_MASK                       0x00000004
#define _I2CSTAT_R_W_LENGTH                     0x00000001

#define _I2CSTAT_S_POSITION                     0x00000003
#define _I2CSTAT_S_MASK                         0x00000008
#define _I2CSTAT_S_LENGTH                       0x00000001

#define _I2CSTAT_P_POSITION                     0x00000004
#define _I2CSTAT_P_MASK                         0x00000010
#define _I2CSTAT_P_LENGTH                       0x00000001

#define _I2CSTAT_D_A_POSITION                   0x00000005
#define _I2CSTAT_D_A_MASK                       0x00000020
#define _I2CSTAT_D_A_LENGTH                     0x00000001

#define _I2CSTAT_I2COV_POSITION                 0x00000006
#define _I2CSTAT_I2COV_MASK                     0x00000040
#define _I2CSTAT_I2COV_LENGTH                   0x00000001

#define _I2CSTAT_IWCOL_POSITION                 0x00000007
#define _I2CSTAT_IWCOL_MASK                     0x00000080
#define _I2CSTAT_IWCOL_LENGTH                   0x00000001

#define _I2CSTAT_ADD10_POSITION                 0x00000008
#define _I2CSTAT_ADD10_MASK                     0x00000100
#define _I2CSTAT_ADD10_LENGTH                   0x00000001

#define _I2CSTAT_GCSTAT_POSITION                0x00000009
#define _I2CSTAT_GCSTAT_MASK                    0x00000200
#define _I2CSTAT_GCSTAT_LENGTH                  0x00000001

#define _I2CSTAT_BCL_POSITION                   0x0000000A
#define _I2CSTAT_BCL_MASK                       0x00000400
#define _I2CSTAT_BCL_LENGTH                     0x00000001

#define _I2CSTAT_TRSTAT_POSITION                0x0000000E
#define _I2CSTAT_TRSTAT_MASK                    0x00004000
#define _I2CSTAT_TRSTAT_LENGTH                  0x00000001

#define _I2CSTAT_ACKSTAT_POSITION               0x0000000F
#define _I2CSTAT_ACKSTAT_MASK                   0x00008000
#define _I2CSTAT_ACKSTAT_LENGTH                 0x00000001

#define _I2CSTAT_I2CPOV_POSITION                0x00000006
#define _I2CSTAT_I2CPOV_MASK                    0x00000040
#define _I2CSTAT_I2CPOV_LENGTH                  0x00000001

#define _I2CSTAT_w_POSITION                     0x00000000
#define _I2CSTAT_w_MASK                         0xFFFFFFFF
#define _I2CSTAT_w_LENGTH                       0x00000020

#endif // _I2C_PRIVATE_H_

