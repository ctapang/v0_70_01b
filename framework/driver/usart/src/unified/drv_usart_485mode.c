#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "drv.h"
#include "usart/src/drv_usart_variant_mapping.h" // Includes Feature Variant Implementations

void DRV_USART_485SetupToReadAddress(DRV_USART_OBJ_T *hwInstance, USART_MODULE_ID index)
{
    if (( hwInstance->currentReadBuffer != (DRV_USART_BUFFER_OBJECT *) NULL ) &&
            ( _DRV_USART_IS_FLAG_SET ( hwInstance->currentReadBuffer->operationalFlags , DRV_USART_BUFFER_OBJECT_FLAG_READ_ADDRESS ) ))
    {
        // Enable Address Detect
        PLIB_USART_ReceiverAddressDetectEnable ( DRV_USART_MODULE_ID ( index ) ) ;
        // Setup FIFO
        DRV_USART_SetupReceiverFIFOLevel ( DRV_USART_MODULE_ID ( index ) ,
                                           PLIB_USART_RECEIVE_FIFO_LEVEL_RECEIVE_BUFFER_ONE_CHAR ) ;
    }
}


void DRV_USART_485ReadComplete(DRV_USART_OBJ_T *hwInstance, uint8_t byte, USART_MODULE_ID index)
{
    bool addressMatched = DRV_USART_CheckAddress ( byte , hwInstance ) ;

    // if the address matches.
    if (addressMatched)
    {
        // Disable address detect mode.
        PLIB_USART_ReceiverAddressDetectDisable ( DRV_USART_MODULE_ID ( index ) ) ;
        // Configure recieve FIFO
        DRV_USART_SetupReceiverFIFOLevel ( DRV_USART_MODULE_ID ( index ) ,
                                           PLIB_USART_RECEIVE_FIFO_LEVEL_RECEIVE_BUFFER_FULL ) ;
        _DRV_USART_CLEAR_FLAG ( hwInstance->currentReadBuffer->operationalFlags ,
                                DRV_USART_BUFFER_OBJECT_FLAG_READ_ADDRESS ) ;
    }

}

/*******************************************************************************
End of File
 */

