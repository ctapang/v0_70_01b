/***********************************************************************
  Company:
    Microchip Technology Inc.
    
  File Name:
    plib_ebi.h
    
  Summary:
    External Bus Interface (EBI) Peripheral Library Interface Header.
    
  Description:    
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the EBI
    Peripheral Library.
  ***********************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef _PLIB_EBI_H
#define _PLIB_EBI_H



// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************

#include "peripheral/ebi/processor/ebi_processor.h"

// *****************************************************************************
// *****************************************************************************
// Section: EBI Peripheral Library Exists Routines
// *****************************************************************************
// *****************************************************************************


/*********************************************************************************************
  Function:
      PLIB_EBI_BaseAddressSet(EBI_MODULE_ID index, int ChipSelectNumber, uint32_t BaseAddress)
    
  Summary:
    This function sets the Base address for physical memory at each chip
    select
  Description:
    CSADDR- in datasheet.
    
    This function sets the base address for physical memory at each chip
    select pin.
  Conditions:
    EBI has to be supported by the microcontroller and has to have a device
    attached to it.
  Input:
    index -             Identifier for the device instance.
    ChipSelectNumber -  Identifies what chip select address pin is being
                        assigned an address
    BaseAddress -       a physical address for memory
  Return:
    None.
  Remarks:
    None.                                                                                     
  *********************************************************************************************/
void PLIB_EBI_BaseAddressSet(EBI_MODULE_ID index, int ChipSelectNumber, uint32_t BaseAddress);
/**************************************************************************
  Function:
        PLIB_EBI_BaseAddressGet (EBI_MODULE_ID index, int ChipSelectNumber)
    
  Summary:
    This function returns the Base Address set for each chip select
  Description:
    CSADDR- in datasheet.
    
    This function returns the base address for each chip select pin
  Conditions:
    Input:
    index -             Identifier for the device instance.
    ChipSelectNumber -  Identifies what chip select address pin address is
                        being read.
  Return:
    \Returns a unsigned integer that is the physical address of the
    attached device
  Remarks:
    None.                                                                  
  **************************************************************************/
uint32_t PLIB_EBI_BaseAddressGet (EBI_MODULE_ID index, int ChipSelectNumber);
/****************************************************************************************************************************************************************
  Function:
     PLIB_EBI_MemoryCharacteristicsSet(EBI_MODULE_ID index, int ChipSelectNumber,EBI_MEMORY_TYPE MemoryType, EBI_MEMORY_SIZE MemorySize, EBI_CS_TIMING TimingReg)
    
  Summary:
    This function set the Memory Characteristics for Memory or attached
    devices attached to that pin
  Description:
    EBIMSKx -SRF name index - Identifier for the device instance.
    
    ChipSelectNumber - Identifies what chip select address pin is being
    assigned an address
    
    MEMTYPE - in datasheet.
    
    MEMSIZE - in the datasheet.
    
    REGSEL - in the datasheet.
  Conditions:
    EBI has to be supported by the microcontroller.
  Input:
    index -             Identifier for the device instance.
    ChipSelectNumber -  Identifies which chip select pin 
    MemoryType -        Identifies which memory is used
    MemorySize -        a enum type, sets the size of the attached memory
                        device
    TimingRegSet -      Identifies the timing register
  Return:
    None.
  Remarks:
    None.                                                                                                                                                        
  ****************************************************************************************************************************************************************/
void PLIB_EBI_MemoryCharacteristicsSet(EBI_MODULE_ID index, int ChipSelectNumber,EBI_MEMORY_TYPE MemoryType,EBI_MEMORY_SIZE MemorySize, EBI_CS_TIMING TimingReg);

/**************************************************************************************************************************************************************************************************************
  Function:
         PLIB_EBI_MemoryTimingConfigSet(EBI_MODULE_ID index, int CS_Timing_Reg, int PageReadTime,int  DataTurnAroundTime, int WritePulseWidth, int AddressHoldTime, int AddressSetupTime, int ReadCycleTime)
    
  Summary:
    This function is to set the cycle time for page reading
  Description:
    SFR = EBISMT[0:2]
    TPRC - in datasheet. Read cycle time = TPRC + 1cycle.
    
    TBTA - in the datasheet. Clock cycles (0-7) for static memory between
    read-to-write, write-to-read, and read-to-read when Chip Select
    changes.
    
    TWP in the datasheet. Write Pulse with = TWP + 1 clock cycle.
    
    TWR - in datasheet. Write Address/Data Hold Time
    
    TAS - in datasheet. Clock cycles for address setup time. A value of ‘0’
    is only valid in the case of SSRAM.
    
    TRC - in datasheet. Read Cycle time = TRC +1 clock cycle.
  Conditions:
    EBI has to be supported by the microcontroller.
  Input:
    index -               Identifier for the device instance
    CS_Timing_Reg -    Identifies which chip select Timing register to use EBISMT[0:2]
    PageReadTime -        The clock cycle needed for a Memory Page read
    DataTurnAroundTime -  Time between read\-to\-write, write\-to\-read, and
                          read\-to\-read when Chip Select changes state.
    WritePulseWidth -     The clock cycles needed for a memory write
    AddressHoldTime -     The clock time needed for the address bus to hold
    AddressSetupTime -    The time needed for the address to settle
    ReadCycleTime -       _nt_
  Return:
    None.
  Remarks:
    None.                                                                                                                                                                                                      
  **************************************************************************************************************************************************************************************************************/
void PLIB_EBI_MemoryTimingConfigSet(EBI_MODULE_ID index, int CS_Timing_Reg, int PageReadTime, int  DataTurnAroundTime, int WritePulseWidth, int AddressHoldTime, int AddressSetupTime, int ReadCycleTime);
/************************************************************************************************
  Function:
      PLIB_EBI_ReadyModeSet (EBI_MODULE_ID index, bool ReadyPin0, bool ReadyPin1, bool ReadyPin2)
    
  Summary:
    This function sets the use of ready mode for each pin. The attached
    device will either pull the ready pin high or low.
  Description:
    RDYMODE- The device associated with EBI is a data-ready device, and
    will use the READY pin.
    
    1 = Ready input is used 0 = Ready input is not used
  Conditions:
    Input:
    index -        Identifier for the device instance ReadyPin0 ReadyPin1
                   ReadyPin2
    ReadyPin(x) -  Identifies the ready pin (1\-3) that 
  Return:
    None.
  Remarks:
    None.                                                                                        
  ************************************************************************************************/
void PLIB_EBI_ReadyModeSet (EBI_MODULE_ID index, bool ReadyPin0, bool ReadyPin1, bool ReadyPin2);
/*************************************************************************
  Function:
      PLIB_EBI_ReadyModeGet (EBI_MODULE_ID index, int ChipSelectNumber)
    
  Summary:
    This function returns whether or not the Ready Mode was set.
  Description:
    RDYMODE - in datasheet.
    
    This Function returns the state of the register RDYMODE, If the
    \function returns a 1, Ready input is used. If the Function returns a
    0, Ready input is not used.
    
    
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    This function Returns a bool, 1 = Ready input is used, 0 = Ready input
    is not used.
  Remarks:
    None.                                                                 
  *************************************************************************/
bool PLIB_EBI_ReadyModeGet (EBI_MODULE_ID index, int ChipSelectNumber);
/************************************************************************************************************************
  Function:
        PLIB_EBI_MemoryPagingSet (EBI_MODULE_ID index, int ChipSelectNumber, bool PageMode, EBI_PAGE_SIZE MemoryPageSize)
    
  Summary:
    This function sets the size of the memory page if paging is used.
  Description:
    PAGESIZE in datasheet.
    
    PAGEMODE in datasheet.
    
    1 = Device supports Page mode
    
    0 = Device does not support Page mode
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Sets for that Chip Select pin [0\:3]
    PageMode -          enable or disable page mode
    MemoryPageSize -    size of memory pages
  Return:
    none
  Remarks:
    None.                                                                                                                
  ************************************************************************************************************************/
void PLIB_EBI_MemoryPagingSet (EBI_MODULE_ID index, int ChipSelectNumber, bool PageMode, EBI_PAGE_SIZE MemoryPageSize);
/**************************************************************************
  Function:
            PLIB_EBI_PageModeGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function returns Paging mode settings
  Description:
    PAGEMODE - in datasheet.
    
    This Function returns the state of the register PAGEMODE, If the
    \function returns a 1, Device supports Page mode. If the Function
    \returns a 0,Device does not support Page mode .
    
    
    
    
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    This function Returns a bool, 1 = Page Mode is used, 0 = Page Mode is
    not used.
  Remarks:
    None.                                                                  
  **************************************************************************/
bool PLIB_EBI_PageModeGet (EBI_MODULE_ID index,int ChipSelectNumber);
//******************************************************************************

/***************************************************************************
  Function:
            PLIB_EBI_PageSizeGet (EBI_MODULE_ID index, int ChipSelectNumber)
    
  Summary:
    This function returns Paging mode settings
  Description:
    PAGESIZE- in datasheet.
    
    
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    This function Returns the size of the memory page.
  Remarks:
    None.                                                                   
  ***************************************************************************/
EBI_PAGE_SIZE PLIB_EBI_PageSizeGet (EBI_MODULE_ID index,int ChipSelectNumber);
/*********************************************************************************
  Function:
          PLIB_EBI_PageReadCycleTimeGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function returns the cycle time for a page read.
  Description:
    TPRC - in datasheet.
    
    Read cycle time = TPRC + 1cycle. The value set and return are the same,
    the controller performs the read on the next clock, that is why there
    is a +1.
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    \Returns a integer, the number of clock cycles used to read a memory
    page.
  Remarks:
    None.                                                                         
  *********************************************************************************/
int PLIB_EBI_PageReadCycleTimeGet (EBI_MODULE_ID index,int ChipSelectNumber);
/**********************************************************************************
  Function:
          PLIB_EBI_DataTurnAroundTimeGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function gets the data turn time set for the EBI Bus.
  Description:
    TBTA - in the datasheet.
    
    \Returns the clock cycles (0-7) for static memory between
    read-to-write, write-to-read, and read-to-read when Chip Select
    changes.
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    \Returns a integer, the number of clock cycles that is set in the Turn
    Around Register
  Remarks:
    None.                                                                          
  **********************************************************************************/
int PLIB_EBI_DataTurnAroundTimeGet (EBI_MODULE_ID index,int ChipSelectNumber);

/*********************************************************************************
  Function:
            PLIB_EBI_WritePulseWidthGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function returns the set hold time in clock cycles.
  Description:
    TWP in the datasheet.
    
    Write Pulse with = TWP + 1 clock cycle
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    \Returns a integer, the number of clock cycles the write pulse width is
    set to.
  Remarks:
    None.                                                                         
  *********************************************************************************/
int PLIB_EBI_WritePulseWidthGet (EBI_MODULE_ID index,int ChipSelectNumber);
/***********************************************************************************
  Function:
              PLIB_EBI_AddressHoldTimeGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function returns the Address Hold Time
  Description:
    TWR - in the datasheet.
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    \Returns a integer, the Address &amp; Data Hold time in number of
    clocks.
  Remarks:
    None.                                                                           
  ***********************************************************************************/

int PLIB_EBI_AddressHoldTimeGet (EBI_MODULE_ID index,int ChipSelectNumber);
/********************************************************************************
  Function:
          PLIB_EBI_AddressSetupTimeGet (EBI_MODULE_ID index,int ChipSelectNumber)
    
  Summary:
    This function is to get the set hold time
  Description:
    TAS - in the data sheet Clock cycles for address setup time. A value of
    ‘0’ is only valid in the case of SSRAM.
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies the specific chip select pin
  Return:
    \Returns a integer, the address setup time in number of clocks
  Remarks:
    None.                                                                        
  ********************************************************************************/

int PLIB_EBI_AddressSetupTimeGet (EBI_MODULE_ID index,int ChipSelectNumber);
/******************************************************************************
  Function:
          PLIB_EBI_ReadCycleTimeGet (EBI_MODULE_ID index, int ChipSelectNumber)
    
  Summary:
    This function returns the read time in number of clock cycles
  Description:
    TRC in datasheet.
    
    Read Cycle time = TRC +1 clock cycle, the controller will always take 1
    extra clock (the next clock) for a Read Cycle. The return will be the
    time set by the user.
    
    setting a the Read Cycle time to a 0 will return a 0 when read, but the
    controller will add 1 to that value for the next available clock.
  Conditions:
    Input:
    index -             Identifier for the device instance
    ChipSelectNumber -  Identifies which chip select number the device is
                        attached to.
  Return:
    \returns a integer, the read cycle time in system clocks.
  Remarks:
    None.                                                                      
  ******************************************************************************/
int PLIB_EBI_ReadCycleTimeGet (EBI_MODULE_ID index,int ChipSelectNumber);
/*************************************************************************
  Function:
      PLIB_EBI_FlashTimingSet (EBI_MODULE_ID index, int FlashTiming)
    
  Summary:
    This function sets the timing for hold in reset for external flash
  Description:
    TRPD - in datasheet.
    
    The number of clock cycles to hold the external Flash memory in reset.
  Conditions:
    NOR Flash has to be used with EBI instead of SRAM
  Input:
    index -        Identifier for the device instance
    FlashTiming -  an int, the number of clock cycles
  Return:
    None.
  Remarks:
    None.                                                                 
  *************************************************************************/
void PLIB_EBI_FlashTimingSet (EBI_MODULE_ID index, int FlashTiming);
/**********************************************************************
  Function:
          PLIB_EBI_FlashTimingGet (EBI_MODULE_ID index)
    
  Summary:
    This function gets the set flash timing for external flash
  Description:
    TRPD -in data sheet The number of clock cycles to hold the external
    Flash memory in reset.
  Conditions:
    MemoryType set to Flash
  Return:
    \returns a integer, the number of clock cycles
  Remarks:
    None.                                                              
  **********************************************************************/
int PLIB_EBI_FlashTimingGet (EBI_MODULE_ID index,int ChipSelectNumber);
/***************************************************************************************************************************************
  Function:
      PLIB_EBI_StaticMemoryWidthRegisterSet (EBI_MODULE_ID index, int RegstierNumber, EBI_STATIC_MEMORY_WIDTH StaticMemoryWidthRegister)
    
  Summary:
    This function set the data width of static memory.
  Description:
    SMDWIDTH - in the datasheet.
    
    000 = 16 bits
    
    100 = 8 bits
    
    
  Conditions:
    Input:
    index -           Identifier for the device instance
    RegstierNumber -  the ID for the register being set
                      StaticMemoryWidthRegister \-identifies weither a bus
                      width of 8bit or 16bits
  Return:
    None.
  Remarks:
    None.                                                                                                                               
  ***************************************************************************************************************************************/
void PLIB_EBI_StaticMemoryWidthRegisterSet (EBI_MODULE_ID index, int RegstierNumber,  EBI_STATIC_MEMORY_WIDTH StaticMemoryWidthRegister);
//******************************************************************************
/* Function :  PLIB_EBI_StaticMemoryWidthRegisterGet (EBI_MODULE_ID index, int RegstierNumber)

  Summary:
        This function get the width of the set data bus

  Description:
        SMDWIDTH - in data sheet
        100 = 16 bits
        000 = 8 bits

  Preconditions:

  Parameters:
        index - Identifier for the device instance

  Returns:
        returns a enum type, which bus mode is used
  Remarks:
	None.
*/
EBI_STATIC_MEMORY_WIDTH PLIB_EBI_StaticMemoryWidthRegisterGet (EBI_MODULE_ID index, int RegstierNumber);

/**********************************************************************************
  Function:
      PLIB_EBI_FlashPowerDownModeSet (EBI_MODULE_ID index, bool FlashPowerDownMode)
    
  Summary:
    This function sets the pin state for flash devices on power down/reset
  Description:
    SMRP- in datasheet.
    
    After a Reset, the controller internally performs a power-down for
    Flash, and then sets this bit to ‘1’.
    
    1 = Flash is taken out of Power-down mode.
    
    0 = Flash is forced into Power-down mode.
  Conditions:
    Input:
    index -               Identifier for the device instance
    FlashPowerDownMode -  a bool, sets the power down state for flash memory
  Return:
    None.
  Remarks:
    None.                                                                          
  **********************************************************************************/
void PLIB_EBI_FlashPowerDownModeSet (EBI_MODULE_ID index, bool FlashPowerDownMode);

//******************************************************************************
//******************************************************************************
/* Function :  PLIB_EBI_FlashPowerDownModeGet (EBI_MODULE_ID index)

  Summary:
        This function gets the set power down state.

  Description:
        SMRP - in datasheet
        After a Reset, the controller internally performs a power-down for Flash, and then sets this bit to ‘1’.
        1 = Flash is taken out of Power-down mode
        0 = Flash is forced into Power-down mode

  Preconditions:

  Parameters:
        index - Identifier for the device instance

  Returns:
        returns a bool, depending on how FlashPowerDownMode its set
  Remarks:
	None.
*/
bool PLIB_EBI_FlashPowerDownModeGet (EBI_MODULE_ID index);
//*******************************************************************************

//*******************************************************************************
//*******************************************************************************
/* CFGEBIA: EBI Address Pin Configuration  */
//*******************************************************************************
//*******************************************************************************

/**************************************************************************
  Function:
      PLIB_EBI_ControlEnableSet (EBI_MODULE_ID index, bool EnableBit)
    
  Summary:
    This function sets the enable bit for turning on or off the EBI Bus.
  Description:
    EBIPINEN - in datasheet.
    
    EBI Pin Enable bit, 1 = EBI controls access of pins shared with PMP 0 =
    Pins shared with EBI are available for general use.
  Conditions:
    Input:
    index -      Identifier for the device instance
    EnableBit -  Identifes the enable bit
  Return:
    None
  Remarks:
    None.                                                                  
  **************************************************************************/
void PLIB_EBI_ControlEnableSet (EBI_MODULE_ID index, bool EnableBit);
/*************************************************************************
  Function:
      PLIB_EBI_ControlEnableGet (EBI_MODULE_ID index)
    
  Summary:
    This function gets the status of the enable bit for EBI.
  Description:
    EBIPINEN - in datasheet.
    
    EBI Pin Enable bit 1 = EBI controls access of pins shared with PMP 0 =
    Pins shared with EBI are available for general use
  Conditions:
    Input:
    index -  Identifier for the device instance
  Return:
    \Returns a bool, if EBI is ON or OFF.
  Remarks:
    None.                                                                 
  *************************************************************************/
bool PLIB_EBI_ControlEnableGet (EBI_MODULE_ID index);
//*******************************************************************************
/* Function :  PLIB_EBI_ControlEnableClear (EBI_MODULE_ID index)

  Summary:
        This function gets the set power down state.

  Description:
        EBIPINEN - in datasheet
        EBI Pin Enable bit
	1 = EBI controls access of pins shared with PMP
	0 = Pins shared with EBI are available for general use

  Preconditions:

  Parameters:
        index - Identifier for the device instance

  Returns:
        None
  Remarks:
	None.
*/
void PLIB_EBI_ControlEnableClear (EBI_MODULE_ID index);
//*******************************************************************************

/*******************************************************************************************
  Function:
        PLIB_EBI_AddressPinEnableBitsSet (EBI_MODULE_ID index, EBI_ADDRESS_PORT AddressPort)
    
  Summary:
    This function sets the address pins used for EBI.
  Description:
    These pins have to be enabled for the size of the data bus in a
    contiguous order.
    
    EBIA23EN:EBIA0EN - in datasheet.
    
    EBI Address Pin Enable bits,
    
    1 = pin is enabled for use by EBI, 0 = pin has is available for general
    use.
  Conditions:
    Input:
    index -        Identifier for the device instance.
    AddressPort -  Identifies how many pins are used for addressing on the EBI
                   bus.
  Return:
    None.
  Remarks:
    None.                                                                                   
  *******************************************************************************************/
void PLIB_EBI_AddressPinEnableBitsSet (EBI_MODULE_ID index, EBI_ADDRESS_PORT AddressPort);
//*******************************************************************************
//*******************************************************************************


//*******************************************************************************
//*******************************************************************************
/* CFGEBIC: EBI Control Pin Configuration  */
//*******************************************************************************
//*******************************************************************************



/****************************************************************************************************
  Function:
        PLIB_EBI_ReadyPin3ConfigSet (EBI_MODULE_ID index, bool ReadyPin3Enable, bool ReadyPin3Invert)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status
  Description:
    EBIRDYEN2 - in datasheet.
    
    EBIRDY2 Pin Enable bit, 1 = pin is enabled for use by the EBI module, 0
    = pin is available for general use
    
    EBIRDYINV2 - in datasheet.
    
    EBIRDYx Inversion Control bit 1 = Invert EBIRDYx pin before use 0 = Do
    not invert EBIRDYx pin before use.
  Conditions:
    Input:
    index -            Identifier for the device instance
    ReadyPin3Invert -  Identifies the on/off for invert
    ReadyPin3Enable -  Identifies if this pin is used by the control part
  Return:
    None.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
void PLIB_EBI_ReadyPin3ConfigSet (EBI_MODULE_ID index, bool ReadyPin3Enable, bool ReadyPin3Invert);

/****************************************************************************************************
  Function:
        PLIB_EBI_ReadyPin2ConfigSet (EBI_MODULE_ID index, bool ReadyPin2Enable, bool ReadyPin2Invert)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status
  Description:
    EBIRDYEN2 - in datasheet.
    
    EBIRDY2 Pin Enable bit, 1 = pin is enabled for use by the EBI module, 0
    = pin is available for general use
    
    EBIRDYINV2 - in datasheet.
    
    EBIRDYx Inversion Control bit 1 = Invert EBIRDYx pin before use 0 = Do
    not invert EBIRDYx pin before use.
  Conditions:
    Input:
    index -            Identifier for the device instance
    ReadyPin2Invert -  Identifies the on/off for invert
    ReadyPin2Enable -  Identifies if this pin is used by the control part
  Return:
    None.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
void PLIB_EBI_ReadyPin2ConfigSet (EBI_MODULE_ID index, bool ReadyPin2Enable, bool ReadyPin2Invert);

/****************************************************************************************************
  Function:
        PLIB_EBI_ReadyPin1ConfigSet (EBI_MODULE_ID index, bool ReadyPin1Enable, bool ReadyPin1Invert)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status.
  Description:
    EBIRDYEN1 - in datasheet.
    
    EBIRDY1 Pin Enable bit, 1 = pin is enabled for use by the EBI module, 0
    = pin is available for general use
    
    EBIRDYINV1 - in datasheet.
    
    EBIRDYx Inversion Control bit 1 = Invert EBIRDYx pin before use 0 = Do
    not invert EBIRDYx pin before use.
  Conditions:
    Input:
    index -            Identifier for the device instance
    ReadyPin1Invert -  Identifies the on/off for invert
    ReadyPin1Enable -  Identifies if this pin is used by the control part
  Return:
    None.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
void PLIB_EBI_ReadyPin1ConfigSet (EBI_MODULE_ID index, bool ReadyPin1Enable, bool ReadyPin1Invert);
/****************************************************************************************************
  Function:
      PLIB_EBI_ReadyPinSensSet (EBI_MODULE_ID index, bool SensitivityControl)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status
  Description:
    EBIRDYLVL - in datasheet.
    
    EBI Ready Pin trigger detection 1 = Use level detect for EBIRDYx pins,
    0 = Use edge detect for EBIRDYx pins
  Conditions:
    Input:
    index -               Identifier for the device instance

    SensitivityControl -  for selection edge or level detection
  Return:
    None.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
void PLIB_EBI_ReadyPinSensSet (EBI_MODULE_ID index, bool SensitivityControl);
/******************************************************************************************************

  Function:
      PLIB_EBI_FlashResetPinSet (EBI_MODULE_ID index,  bool FlashReadPin)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status
  Description:
    EBIRPEN - in datasheet.
    
    EBIRP Flash Reset pin, 1 = pin is enabled for use by the
    EBI module 0 = pin is available for general use.

  Conditions:
    Input:
    index -               Identifier for the device instance
    FlashReadPin  -       Flash Rest Pin is Used

  Return:
    None.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
void PLIB_EBI_FlashResetPinSet (EBI_MODULE_ID index, bool FlashResetPin);
/******************************************************************************************************

  Function:
      PLIB_EBI_FlashResetPinGet (EBI_MODULE_ID index)
    
  Summary:
    This function sets the the control use of Ready pin and the inverts
    status
  Description:
    EBIRPEN - in datasheet.
    
    EBIRP Flash Reset pin, 1 = pin is enabled for use by the
    EBI module 0 = pin is available for general use.

  Conditions:
    Input:
    index -               Identifier for the device instance

  Return:
    returns a bool.
  Remarks:
    None.                                                                                            
  ****************************************************************************************************/
bool PLIB_EBI_FlashResetPinGet (EBI_MODULE_ID index);
/******************************************************************************************************
  Function:
              PLIB_EBI_WriteOutputControlSet (EBI_MODULE_ID index, bool WriteEnable, bool OutputEnable)
    
  Summary:
    This function sets the Write Enable &amp; Output Enable control pins
  Description:
    EBIWEEN - in datasheet.
    
    EBIWE, This controls the Enable bit for the Write Enable Pin.
    
    1 = pin is enabled for use by the EBI module, 0 = pin is available for
    general use.
    
    EBIOEEN - in datasheet.
    
    EBIOE, This controls the enable bit for the Output Enable Pin.
    
    1 = pin is enabled for use by the EBI module, 0 = pin is available for
    general use.
  Conditions:
    Input:
    index -         Identifier for the device instance
    WriteEnable -   for enabling Write Enable
    OutputEnable -  for enabling Output Enable
  Return:
    None.
  Remarks:
    None.                                                                                              
  ******************************************************************************************************/
void PLIB_EBI_WriteOutputControlSet (EBI_MODULE_ID index, bool WriteEnable, bool OutputEnable);
/************************************************************************************************
  Function:
              PLIB_EBI_ByteSelectPinSet (EBI_MODULE_ID index, bool ByteSelect0, bool ByteSelect1)
    
  Summary:
    This function sets the data Byte Select High [15:8] and Low [7:0]
    enable pins for use.
  Description:
    If the system uses Byte Select High/Low pins for the data, the pins
    must be enabled for use in the EBI controller.
    
    EBIBSEN0 - in datasheet.
    
    EBIBSEN0, This Controls the pin Enable bit for the Lower Data Byte
    Select. Lower Data Byte is bits 8:0.
    
    1 = pin is enabled for use by the EBI module, 0 = pin is available for
    general use.
    
    EBIBSEN1 - in datasheet.
    
    EBIBSEN1, This Controls the pin Enable bit for the Upper Data Byte
    Select. Upper Data Byte is bits 15:8.
    
    1 = pin is enabled for use by the EBI module, 0 = pin is available for
    general use.
  Conditions:
    Registers EBIDEN0 &amp; EBIDEN1 must be enabled first, this can be done
    in the function PLIB_EBI_DataEnableSet().
  Input:
    index -        Identifier for the device instance
    ByteSelect0 -  Identifies Lower Byte Select Pin for enabling.
    ByteSelect1 -  Identifies Upper Byte Select Pin for enabling.
  Return:
    None.
  Remarks:
    None.                                                                                        
  ************************************************************************************************/
void PLIB_EBI_ByteSelectPinSet (EBI_MODULE_ID index, bool ByteSelect0, bool ByteSelect1);
/*********************************************************************************************************************************
  Function:
        PLIB_EBI_ChipSelectEnableSet (EBI_MODULE_ID index, bool ChipSelect0, bool ChipSelect1, bool ChipSelect2, bool ChipSelect3)
    
  Summary:
    This function sets the Chip Select pins for use with the EBI or GPIO.
  Description:
    EBICSEN0 = EBI ChipSelect0 Pin Enable bit. 1 = pin is enabled for use
    by the EBI module, 0 = pin is available for general use.
    
    EBICSEN1 = EBI ChipSelect1 Pin Enable bit. 1 = pin is enabled for use
    by the EBI module, 0 = pin is available for general use.
    
    EBICSEN2 = EBI ChipSelect2 Pin Enable bit. 1 = pin is enabled for use
    by the EBI module, 0 = pin is available for general use.
    
    EBICSEN3 = EBI ChipSelect3 Pin Enable bit. 1 = pin is enabled for use
    by the EBI module, 0 = pin is available for general use.
  Conditions:
    Input:
    index -        Identifier for the device instance
    ChipSelect0 -  Identifies control of Chip Select 0 for enabling.
    ChipSelect1 -  Identifies control of Chip Select 1 for enabling.
    ChipSelect2 -  Identifies control of Chip Select 2 for enabling.
    ChipSelect3 -  Identifies control of Chip Select 3 for enabling.
  Return:
    None.
  Remarks:
    None.                                                                                                                         
  *********************************************************************************************************************************/
void PLIB_EBI_ChipSelectEnableSet (EBI_MODULE_ID index, bool ChipSelect0, bool ChipSelect1, bool ChipSelect2, bool ChipSelect3);
/***********************************************************************************************
  Function:
            PLIB_EBI_DataEnableSet (EBI_MODULE_ID index, bool DataUpperByte, bool DataLowerByte)
    
  Summary:
    This function sets the use of Data Byte Select Pins, High and Low, for
    control with EBI or GPIO use.
  Description:
    EBIDEN1 - in datasheet.
    
    EBI Data Upper Byte Pin Enable bit.
    
    1 = [15:8] pins are enabled for use by the EBI module, 0 = [15:8] pins
    have reverted to general use.
    
    EBIDEN0 - in datasheet.
    
    EBI Data Upper Byte Pin Enable bit.
    
    1 = [7:0] pins are enabled for use by the EBI module, 0 = [7:0] pins
    have reverted to general use.
  Conditions:
    Input:
    index -          Identifier for the device instance
    DataUpperByte -  Identifies control of Upper Data Byte for enabling.
    DataLowerByte -  Identifies control of Lower Data Byte for enabling.
  Return:
    None.
  Remarks:
    None.                                                                                       
  ***********************************************************************************************/
void PLIB_EBI_DataEnableSet (EBI_MODULE_ID index, bool DataUpperByte, bool DataLowerByte);
//*******************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: EBI Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_EBI_ExistsBaseAddress( EBI_MODULE_ID index )

  Summary:
    Identifies whether the Base_Address feature exists on the EBI module 

  Description:
    This function identifies whether the Base_Address feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_BaseAddressSet
    - PLIB_EBI_BaseAddressGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The Base_Address feature is supported on the device
    - false  - The Base_Address feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsBaseAddress( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsMemoryCharacteristics( EBI_MODULE_ID index )

  Summary:
    Identifies whether the MemoryCharacteristics feature exists on the EBI module 

  Description:
    This function identifies whether the MemoryCharacteristics feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_MemoryCharacteristicsSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MemoryCharacteristics feature is supported on the device
    - false  - The MemoryCharacteristics feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsMemoryCharacteristics( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsMemoryTimingConfig( EBI_MODULE_ID index )

  Summary:
    Identifies whether the MemoryTimingConfig feature exists on the EBI module 

  Description:
    This function identifies whether the MemoryTimingConfig feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_MemoryTimingConfigSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MemoryTimingConfig feature is supported on the device
    - false  - The MemoryTimingConfig feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsMemoryTimingConfig( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadyMode( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadyMode feature exists on the EBI module 

  Description:
    This function identifies whether the ReadyMode feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadyModeSet
    - PLIB_EBI_ReadyModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadyMode feature is supported on the device
    - false  - The ReadyMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadyMode( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsMemoryPaging( EBI_MODULE_ID index )

  Summary:
    Identifies whether the MemoryPaging feature exists on the EBI module 

  Description:
    This function identifies whether the MemoryPaging feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_MemoryPagingSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MemoryPaging feature is supported on the device
    - false  - The MemoryPaging feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsMemoryPaging( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsPageMode( EBI_MODULE_ID index )

  Summary:
    Identifies whether the PageMode feature exists on the EBI module 

  Description:
    This function identifies whether the PageMode feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_PageModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PageMode feature is supported on the device
    - false  - The PageMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsPageMode( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsPageReadTime( EBI_MODULE_ID index )

  Summary:
    Identifies whether the PageReadTime feature exists on the EBI module 

  Description:
    This function identifies whether the PageReadTime feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_PageReadCycleTimeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PageReadTime feature is supported on the device
    - false  - The PageReadTime feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsPageReadTime( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsDataTurnAroundTime( EBI_MODULE_ID index )

  Summary:
    Identifies whether the DataTurnAroundTime feature exists on the EBI module 

  Description:
    This function identifies whether the DataTurnAroundTime feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_DataTurnAroundTimeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataTurnAroundTime feature is supported on the device
    - false  - The DataTurnAroundTime feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsDataTurnAroundTime( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsWritePulseWidth( EBI_MODULE_ID index )

  Summary:
    Identifies whether the WritePulseWidth feature exists on the EBI module 

  Description:
    This function identifies whether the WritePulseWidth feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_WritePulseWidthGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WritePulseWidth feature is supported on the device
    - false  - The WritePulseWidth feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsWritePulseWidth( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsAddressHoldTime( EBI_MODULE_ID index )

  Summary:
    Identifies whether the AddressHoldTime feature exists on the EBI module 

  Description:
    This function identifies whether the AddressHoldTime feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_AddressHoldTimeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressHoldTime feature is supported on the device
    - false  - The AddressHoldTime feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsAddressHoldTime( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsAddressSetupTime( EBI_MODULE_ID index )

  Summary:
    Identifies whether the AddressSetupTime feature exists on the EBI module 

  Description:
    This function identifies whether the AddressSetupTime feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_AddressSetupTimeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressSetupTime feature is supported on the device
    - false  - The AddressSetupTime feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsAddressSetupTime( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadCycleTime( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadCycleTime feature exists on the EBI module 

  Description:
    This function identifies whether the ReadCycleTime feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadCycleTimeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadCycleTime feature is supported on the device
    - false  - The ReadCycleTime feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadCycleTime( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsFlashTiming( EBI_MODULE_ID index )

  Summary:
    Identifies whether the FlashTiming feature exists on the EBI module 

  Description:
    This function identifies whether the FlashTiming feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_FlashTimingSet
    - PLIB_EBI_FlashTimingGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The FlashTiming feature is supported on the device
    - false  - The FlashTiming feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsFlashTiming( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsStaticMemoryWidthRegister( EBI_MODULE_ID index )

  Summary:
    Identifies whether the StaticMemoryWidthRegister feature exists on the EBI module 

  Description:
    This function identifies whether the StaticMemoryWidthRegister feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_StaticMemoryWidthRegisterSet
    - PLIB_EBI_StaticMemoryWidthRegisterGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The StaticMemoryWidthRegister feature is supported on the device
    - false  - The StaticMemoryWidthRegister feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsStaticMemoryWidthRegister( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsFlashPowerDownMode( EBI_MODULE_ID index )

  Summary:
    Identifies whether the FlashPowerDownMode feature exists on the EBI module 

  Description:
    This function identifies whether the FlashPowerDownMode feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_FlashPowerDownModeSet
    - PLIB_EBI_FlashPowerDownModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The FlashPowerDownMode feature is supported on the device
    - false  - The FlashPowerDownMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsFlashPowerDownMode( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsControlEnable( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ControlEnable feature exists on the EBI module 

  Description:
    This function identifies whether the ControlEnable feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ControlEnableSet
    - PLIB_EBI_ControlEnableGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ControlEnable feature is supported on the device
    - false  - The ControlEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsControlEnable( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsAddressPinEnableBits( EBI_MODULE_ID index )

  Summary:
    Identifies whether the AddressPinEnableBits feature exists on the EBI module 

  Description:
    This function identifies whether the AddressPinEnableBits feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_AddressPinEnableBitsSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressPinEnableBits feature is supported on the device
    - false  - The AddressPinEnableBits feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsAddressPinEnableBits( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadyPin3Config( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadyPin3Config feature exists on the EBI module 

  Description:
    This function identifies whether the ReadyPin3Config feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadyPin3ConfigSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadyPin3Config feature is supported on the device
    - false  - The ReadyPin3Config feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadyPin3Config( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadyPin2Config( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadyPin2Config feature exists on the EBI module 

  Description:
    This function identifies whether the ReadyPin2Config feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadyPin2ConfigSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadyPin2Config feature is supported on the device
    - false  - The ReadyPin2Config feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadyPin2Config( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadyPin1Config( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadyPin1Config feature exists on the EBI module 

  Description:
    This function identifies whether the ReadyPin1Config feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadyPin1ConfigSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadyPin1Config feature is supported on the device
    - false  - The ReadyPin1Config feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadyPin1Config( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsReadyPinSens( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ReadyPinSens feature exists on the EBI module 

  Description:
    This function identifies whether the ReadyPinSens feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ReadyPinSensSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReadyPinSens feature is supported on the device
    - false  - The ReadyPinSens feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsReadyPinSens( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsFlashResetPin( EBI_MODULE_ID index )

  Summary:
    Identifies whether the FlashResetPin feature exists on the EBI module 

  Description:
    This function identifies whether the FlashResetPin feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_FlashResetPinSet
    - PLIB_EBI_FlashResetPinGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The FlashResetPin feature is supported on the device
    - false  - The FlashResetPin feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsFlashResetPin( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsWriteOutputControl( EBI_MODULE_ID index )

  Summary:
    Identifies whether the WriteOutputControl feature exists on the EBI module 

  Description:
    This function identifies whether the WriteOutputControl feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_WriteOutputControlSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WriteOutputControl feature is supported on the device
    - false  - The WriteOutputControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsWriteOutputControl( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsByteSelectPin( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ByteSelectPin feature exists on the EBI module 

  Description:
    This function identifies whether the ByteSelectPin feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ByteSelectPinSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ByteSelectPin feature is supported on the device
    - false  - The ByteSelectPin feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsByteSelectPin( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsChipSelectEnable( EBI_MODULE_ID index )

  Summary:
    Identifies whether the ChipSelectEnable feature exists on the EBI module 

  Description:
    This function identifies whether the ChipSelectEnable feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_ChipSelectEnableSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipSelectEnable feature is supported on the device
    - false  - The ChipSelectEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsChipSelectEnable( EBI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_EBI_ExistsDataEnable( EBI_MODULE_ID index )

  Summary:
    Identifies whether the DataEnable feature exists on the EBI module 

  Description:
    This function identifies whether the DataEnable feature is available on the EBI module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_EBI_DataEnableSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataEnable feature is supported on the device
    - false  - The DataEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_EBI_ExistsDataEnable( EBI_MODULE_ID index );







//*******************************************************************************
//*******************************************************************************
#endif // #ifndef _PLIB_EBI_H
/*******************************************************************************
 End of File
*/