/*******************************************************************************
  ADC Driver Multiple Client 

  Company:    
    Microchip Technology Inc.

  File Name:
    drv_adc_client_multi.c

  Summary:
    ADC Driver multiple client implementations.

  Description:
    This file implements the functions for the multiple client support. 
    While building the driver from source, use this file in the build when
    DRV_ADC_CLIENTS_NUMBER is defined in the system configuration
    or when DRV_ADC_INSTANCES_NUMBER is defined in the system
    configuration. 
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
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "driver/adc/src/drv_adc_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the client state of the instance.
    It uses the configuration of maximum number of clients, which can get
    registered per hardware instance.

  Remarks:
    Not all modes are available on all devices.
*/

DRV_ADC_CLIENT_OBJECT gDrvADCClientObj[_DRV_ADC_INSTANCES_NUMBER * DRV_ADC_CLIENTS_NUMBER];


// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* DRV_ADC_CLIENT_OBJ _DRV_ADC_ClientObjectAllocate (SYS_MODULE_INDEX drvIndex )

  Summary:
    Creates a client instance object and returns it.

  Description:
    This function creates a client instance object and returns it.

  Remarks:
    None
*/

DRV_ADC_CLIENT_OBJ _DRV_ADC_ClientObjectAllocate (SYS_MODULE_INDEX drvIndex )
{
    /* Local Variables */
    _DRV_ADC_MC( DRV_ADC_CLIENT_OBJ clientObj = (DRV_ADC_CLIENT_OBJ) 0 );
    uint8_t i = 0;

    for (i = 0; i < DRV_ADC_CLIENTS_NUMBER ; i++)
    {
        clientObj = (i + ( drvIndex * DRV_ADC_CLIENTS_NUMBER) );
        // Return the matching index associated the hardware instance.
        if (!(( _DRV_ADC_CLIENT_OBJ(clientObj, inUse) == true )))
        {
            _DRV_ADC_CLIENT_OBJ(clientObj, driverObject) = drvIndex;
            _DRV_ADC_CLIENT_OBJ(clientObj, accessMask) = 1 << i;
            
            return clientObj;
        }
    }
    
    // Returns the available client object
    return -1;
}

/*******************************************************************************
End of File
*/

