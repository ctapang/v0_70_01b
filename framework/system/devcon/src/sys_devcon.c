/*******************************************************************************
  Device Control System Service Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    sys_devcon.c

  Summary:
    Device Control System Service implementation.

  Description:
    The DEVCON system service provides a simple interface to manage the Device 
    Control module on Microchip microcontrollers. This file Implements the core
    interface routines for the Device Control system service. While building 
    the system service from source, ALWAYS include this file in the build.
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
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "sys_devcon_local.h"
#include "peripheral/peripheral.h"
#include "system/clk/sys_clk.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
static bool int_status;

// *****************************************************************************
// *****************************************************************************
// Section: Variable Definitions
// *****************************************************************************
// *****************************************************************************

/* System Device Control Instance */
SYS_DEVCON_OBJECT sysDevconObj;


// *****************************************************************************
// *****************************************************************************
// Section: SYS DEVCON Module Initialization Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ SYS_DEVCON_Initialize( const SYS_MODULE_INDEX           index,
                                       const SYS_MODULE_INIT * const    init )

  Summary:
    Initializes data for the instance of the Device Control module and opens
    the specific module instance.

  Description:
    This function initializes the instance of the Device Control module,
    using the specified initialization data. It also initializes any
    internal data structures.

  Precondition:
    None.

  Parameters:
    index           - Index for the instance to be initialized

    init            - Pointer to a data structure containing any data necessary
                      to initialize the Device Control module. This pointer may 
                      be null if no data is required because static overrides 
                      have been provided.

  Returns:
    If successful, returns a valid handle to an object.  Otherwise, it
    returns SYS_MODULE_OBJ_INVALID. The returned object must be passed as
    argument to SYS_DEVCON_Reinitialize, SYS_DEVCON_Deinitialize, SYS_DEVCON_Tasks and
    SYS_DEVCON_Status routines.

  Remarks:
    This routine should only be called once during system initialization
    unless SYS_DEVCON_Deinitialize is first called to deinitialize the device
    instance before reinitializing it. If the system was already initialized
    it safely returns without causing any disturbance.
*/

SYS_MODULE_OBJ SYS_DEVCON_Initialize( const SYS_MODULE_INDEX index,
                                   const SYS_MODULE_INIT * const init )
{
    SYS_DEVCON_INIT *sysDevconInit = (SYS_DEVCON_INIT*)init;

    sysDevconObj.status = SYS_STATUS_UNINITIALIZED;

    sysDevconObj.state = SYS_DEVCON_STATE_INIT;
    
    if (sysDevconInit != NULL)
    {
        if (sysDevconInit->sysClkFreq)
        {
            sysDevconObj.sysClk = sysDevconInit->sysClkFreq;
        }
        else
        {
            SYS_ASSERT(false, "No system clock specified");
        }
    }
    else
    {
        //TODO: fix when clk service is available
        //sysDevconObj.sysClk = SYS_CLK_ClockFrequencyGet(CLK_SYSTEM);
    }

    sysDevconObj.status = SYS_STATUS_READY;

    sysDevconObj.state = SYS_DEVCON_STATE_READY;

    return (SYS_MODULE_OBJ)SYS_DEVCON_INDEX_0;
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_Reinitialize( SYS_MODULE_OBJ                  object,
                               const SYS_MODULE_INIT * const   init )

   Summary:
    Reinitializes and refreshes the hardware for the instance of the Device 
    Control module.

   Description:
    This function reinitializes the instance of the Device Control module using 
    the supplied data. It modifies the internal data structure.

  Precondition:
    The SYS_DEVCON_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - Identifies the SYS DEVCON Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware

   Returns:
    None

   Remarks:
    This operation uses the same initialization data structure as the
    SYS_DEVCON_Initialize operation. This operation can be used to change the
    power state of a DEVCON module. This function can be called multiple times
    to reinitialize the module. This operation uses the same initialization
    data structure as the Initialize operation. This operation can also be
    used to refresh the hardware registers as defined by the initialization
    data.
*/

void SYS_DEVCON_Reinitialize( SYS_MODULE_OBJ object,
                           const SYS_MODULE_INIT * const init )
{
    SYS_DEVCON_INIT *sysDevconInit = (SYS_DEVCON_INIT*)init;

    sysDevconObj.status = SYS_STATUS_UNINITIALIZED;

    sysDevconObj.state = SYS_DEVCON_STATE_INIT;

    if (sysDevconInit != NULL)
    {
        if (sysDevconInit->sysClkFreq)
        {
            sysDevconObj.sysClk = sysDevconInit->sysClkFreq;
        }
        else
        {
            SYS_ASSERT(false, "No system clock specified");
        }
    }
    else
    {
        //TODO: fix when clk service is available
        //sysDevconObj.sysClk = SYS_CLK_ClockFrequencyGet(CLK_SYSTEM);
    }

    sysDevconObj.status = SYS_STATUS_READY;

    sysDevconObj.state = SYS_DEVCON_STATE_READY;
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the DEVCON module

  Description:
    This function deinitializes the specific module instance disabling its operation 
    (and any hardware for driver modules). Resets all of the internal data
    structures and fields for the specified instance to the default settings.

  Precondition:
    The SYS_DEVCON_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - SYS DEVCON object handle, returned from SYS_DEVCON_Initialize

  Returns:
    None.

  Remarks:
    Once the Initialize operation has been called, the Deinitialize
    operation must be called before the Initialize operation can be called
    again.
*/

void SYS_DEVCON_Deinitialize( SYS_MODULE_OBJ object )
{
    sysDevconObj.status = SYS_STATUS_UNINITIALIZED;
}


// *****************************************************************************
/* Function:
    SYS_STATUS SYS_DEVCON_Status( SYS_MODULE_OBJ object )

  Summary:
    Returns status of the specific instance of the Device Control module.

  Description:
    This function returns the status of the specific module instance disabling its 
    operation (and any hardware for driver modules).

  Precondition:
    The SYS_DEVCON_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - SYS DEVCON object handle, returned from SYS_DEVCON_Initialize

  Returns:
    SYS_STATUS_READY          - Indicates that any previous operations have 
                                succeeded and the module is ready for additional 
                                operations.

                                Note: Any value greater than SYS_STATUS_READY is
                                also a normal running state in which the driver
                                is ready to accept new operations

    SYS_STATUS_BUSY           - Indicates that the driver is busy with a
                                previous system level operation and cannot start
                                another

    SYS_STATUS_ERROR          - Indicates that the driver is in an error state

                                Note: Any value less than SYS_STATUS_ERROR is
                                also an error state.

    SYS_MODULE_DEINITIALIZED  - Indicates that the driver has been
                                de-initialized

                                Note:  This value is less than SYS_STATUS_ERROR.

  Remarks:
    Once the Initialize operation has been called, the Deinitialize
    operation must be called before the Initialize operation can be called
    again.
*/

SYS_STATUS SYS_DEVCON_Status( SYS_MODULE_OBJ object )
{
    return sysDevconObj.status; 
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_Tasks( SYS_MODULE_OBJ object )

  Summary:
    Maintains the system Device Control state machine.

  Description:
    This function is used to maintain the system Device Control internal state machine.

  Precondition:
    The SYS_DEVCON_Initialize function must have been called for the specified DEVCON
    driver instance.

  Parameters:
    object          - SYS DEVCON object handle, returned from SYS_DEVCON_Initialize

  Returns:
    None

  Remarks:
    This function is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the apropriate raw
    ISR.
*/

void SYS_DEVCON_Tasks( SYS_MODULE_OBJ object )
{
    switch (sysDevconObj.state)
    {
        case SYS_DEVCON_STATE_INIT:
        case SYS_DEVCON_STATE_BUSY:
        case SYS_DEVCON_STATE_READY:
        default:
            break;
    }
}

    
// *****************************************************************************
// *****************************************************************************
// Section: SYS DEVCON Client Setup Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    void SYS_DEVCON_PerformanceConfig( void )

  Summary:
    Configures the PFM wait states and prefetch (cache) module for maximum 
    performance.

  Description:
    This function configures the PFM wait states and prefetch (cache) module 
    for maximum performance.

  Precondition:
    The SYS_DEVCON_Initialize function should have been called before calling this 
    function.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void SYS_DEVCON_PerformanceConfig( void )
{
#if defined(__PIC32MX__)
    int pbclk;
#endif
#if defined(__PIC32MZ__)
    bool ecc;
#endif

#if defined(__PIC32MX__)
    pbclk = sysDevconObj.sysClk > SYS_DEVCON_PIC32MX_MAX_PB_FREQ ? 2 : 1;
    /* TODO: replace with clock system service call when available */
    if (PLIB_OSC_PBClockDivisorGet(OSC_ID_0, OSC_PERIPHERAL_BUS_1) != pbclk)
    {
        SYS_DEVCON_SystemUnlock();
        PLIB_OSC_PBClockDivisorSet (OSC_ID_0, OSC_PERIPHERAL_BUS_1, pbclk);
        SYS_DEVCON_SystemLock();
    }
#endif

    if (PLIB_PCACHE_ExistsWaitState(PCACHE_ID_0))
    {
        int ws;
#if defined(__PIC32MX__)
        if (sysDevconObj.sysClk <= 30000000)
            ws = 0;
        else if (sysDevconObj.sysClk <= 60000000)
            ws = 1;
        else
            ws = 2;
#endif
#if defined(__PIC32MZ__)
        /* TODO: replace register read with plib when available */
        ecc = (((CFGCON & 0x00000030) >> 4) < 2) ? true : false;
        if (sysDevconObj.sysClk <= (ecc ? 66000000 : 83000000))
            ws = 0;
        else if (sysDevconObj.sysClk <= (ecc ? 133000000 : 166000000))
            ws = 1;
        else
            ws = 2;
#endif
        if (PLIB_INT_IsEnabled (INT_ID_0))
        {
            int_status = true;
            PLIB_INT_Disable(INT_ID_0);
        }

        PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, ws);

        if (int_status)
        {
            PLIB_INT_Enable(INT_ID_0);
            int_status = false;
        }
    }

    if (PLIB_INT_IsEnabled (INT_ID_0))
    {
        int_status = true;
        PLIB_INT_Disable(INT_ID_0);
    }

    if (PLIB_PCACHE_ExistsPrefetchEnable(PCACHE_ID_0))
    {
        PLIB_PCACHE_PrefetchEnableSet(PCACHE_ID_0, PLIB_PCACHE_PREFETCH_ENABLE_ALL);
    }
#if defined (__PIC32MX__)
    if (PLIB_BMX_ExistsDataRamWaitState(BMX_ID_0))
    {
        PLIB_BMX_DataRamWaitStateSet(BMX_ID_0, PLIB_BMX_DATA_RAM_WAIT_ZERO);
    }            
#endif
    
    if (int_status)
    {
        PLIB_INT_Enable(INT_ID_0);
        int_status = false;
    }
}

// *****************************************************************************
/* Function:
    void SYS_DEVCON_SystemUnlock( void )

  Summary:
    Performs a system unlock sequence by writing to the SYSKEY register.

  Description:
    Performs a system unlock sequence by writing to the SYSKEY register. A 
    system unlock sequence is required before performing certain actions such
    as changing a clock frequency or IO unlocking.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void SYS_DEVCON_SystemUnlock( void )
{
    if (PLIB_INT_IsEnabled (INT_ID_0))
    {
        int_status = true;
        PLIB_INT_Disable(INT_ID_0);
    }

    if (PLIB_DMA_ExistsEnableControl(DMA_ID_0)) 
    {
        PLIB_DMA_Disable(DMA_ID_0);
    }

    PLIB_DEVCON_SystemUnlock(DEVCON_ID_0);
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_SystemLock( void )

  Summary:
    Performs a system lock sequence by writing to the SYSKEY register.

  Description:
    Performs a system lock sequence by writing to the SYSKEY register. A 
    system lock sequence is required after performing the action that required
    a system lock sequence.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void SYS_DEVCON_SystemLock( void )
{
    PLIB_DEVCON_SystemLock(DEVCON_ID_0);

    if (int_status)
    {
        PLIB_INT_Enable(INT_ID_0);
        int_status = false;
    }
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_JTAGEnable( void )

  Summary:
    Enables the JTAG port on the device.

  Description:
    Enables the JTAG port on the device.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void SYS_DEVCON_JTAGEnable( void )
{
    PLIB_DEVCON_JTAGPortEnable(DEVCON_ID_0);
}


// *****************************************************************************
/* Function:
    void SYS_DEVCON_JTAGDisable( void )

  Summary:
    Disables the JTAG port on the device.

  Description:
    Disables the JTAG port on the device.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None.
*/

void SYS_DEVCON_JTAGDisable( void )
{
    PLIB_DEVCON_JTAGPortDisable(DEVCON_ID_0);
}


/*******************************************************************************
 End of File
*/

