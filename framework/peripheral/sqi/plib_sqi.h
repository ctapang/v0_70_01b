/*******************************************************************************
  SQI Peripheral Library Interface Header

  Company:
    Microchip Technology Inc.

  File Name:
    plib_sqi.h

  Summary:
    SQI PLIB Interface Header for common definitions

  Description:
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the SQI
    PLIB.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _PLIB_SQI_H
#define _PLIB_SQI_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files (continued at end of file)
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are inlcuded in this file.  However,
    please see the bottom of the file for additional implementation header files
    that are also included.
 */

#include "peripheral/sqi/processor/sqi_processor.h"

// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: General Control
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_Enable( SQI_MODULE_ID index )

 Summary:
    Enables the SQI module.

 Description:
    This routine enables the SQI module.

 Precondition:
    None.

 Parameters:
    index           - Identifier for the device instance to be configured

 Returns:
    None.

 Example:
   <code>
   // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
   // application developer.
   PLIB_SQI_Enable(MY_SQI_INSTANCE);
   </code>

 Remarks:
    The SQICLK, SQICSx, SQID0, SQID1, SQID2 and SQID3 pins must be
    assigned to available RPn pins before use.
 */

void PLIB_SQI_Enable( SQI_MODULE_ID index );


//******************************************************************************
/* Function:
   void PLIB_SQI_Disable (SQI_MODULE_ID index)

 Summary:
   Disables the SQI module.

 Description:
   This routine disables the SQI module.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
   // application developer.
   PLIB_SQI_Disable(MY_SQI_INSTANCE);
   </code>

 Remarks:
   None.
 */

void PLIB_SQI_Disable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_TransferModeSet (SQI_MODULE_ID index, SQI_XFER_MODE mode)

  Summary:
   Sets the SQI transfer mode (PIO/DMA/XIP) of operation.

  Description:
    This routine sets the SQI transfer mode (PIO/DMA/XIP) of operation.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    mode			- Transfer mode (PIO/DMA/XIP)

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and SQI_XFER_MODE_DMA is an enum element.
    PLIB_SQI_TransferModeSet(MY_SQI_INSTANCE, SQI_XFER_MODE_DMA);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_TransferModeSet(SQI_MODULE_ID index, SQI_XFER_MODE mode);


//******************************************************************************
/* Function:
    SQI_XFER_MODE PLIB_SQI_TransferModeGet (SQI_MODULE_ID index)

  Summary:
   Returns the SQI transfer mode (PIO/DMA/XIP) of operation.

  Description:
    This routine returns the SQI transfer mode (PIO/DMA/XIP) of operation.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured.

  Returns:
    Transfer mode (PIO/DMA/XIP).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_XFER_MODE xferMode = PLIB_SQI_TransferModeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_XFER_MODE PLIB_SQI_TransferModeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DataModeSet(SQI_MODULE_ID index, SQI_DATA_MODE mode)

  Summary:
   	Sets the SQI data mode of operation (SPI Mode0/Mode3/Serial Flash).

  Description:
    This routine sets the data mode to be SPI Mode 0, SPI Mode 3 or Serial Flash.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    mode			- Data mode (Mode 0/ Mode 3)

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and SQI_DATA_MODE_3 is an enum element.
    PLIB_SQI_DataModeSet(MY_SQI_INSTANCE, SQI_DATA_MODE_SF);
    </code>

  Remarks:
    None.
 */

 void PLIB_SQI_DataModeSet(SQI_MODULE_ID index, SQI_DATA_MODE mode);


//******************************************************************************
/* Function:
    SQI_DATA_MODE PLIB_SQI_DataModeGet(SQI_MODULE_ID index)

  Summary:
   	Returns the SQI data mode of operation (SPI Mode0/Mode3).

  Description:
    This routine returns the SQI data mode (SPI Mode 0/Mode 3) of operation.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Data mode (SPI Mode 0/Mode 3).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_DATA_MODE dataMode = PLIB_SQI_DataModeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

 SQI_DATA_MODE PLIB_SQI_DataModeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DataFormatSet(SQI_MODULE_ID index, SQI_DATA_FORMAT dataformat)

  Summary:
   	Sets the data format to Least Significant Bit First or LITTLE-ENDIAN.

  Description:
    This routine sets the SQI data format to LSBF (LITTLE-ENDIAN).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DataFormatSet(MY_SQI_INSTANCE, SQI_DATA_FORMAT_LSBF);
    </code>

  Remarks:
    Typical data format in most of the Systems is LITTLE ENDIAN.
 */

 void PLIB_SQI_DataFormatSet(SQI_MODULE_ID index,SQI_DATA_FORMAT dataformat);


//******************************************************************************
/* Function:
    SQI_DATA_FORMAT PLIB_SQI_DataFormatGet(SQI_MODULE_ID index)

  Summary:
   Returns the data format to Least Significant Bit First or LITTLE-ENDIAN.

  Description:
    This routine returns the SQI data format (LSBF/MSBF).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    True if Data Format is LSBF, else flase.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_DATA_FORMAT dataFormat = PLIB_SQI_DataFormatGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    Typical data format in most of the Systems is LITTLE ENDIAN.
 */

SQI_DATA_FORMAT PLIB_SQI_DataFormatGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ReceiveLatchEnable (SQI_MODULE_ID index)

  Summary:
   Enable the receive latch so receive data is latched during transmit mode.

  Description:
    This routine enables the receive latch, which latches receive data
    in transmit mode. Otherwise receive data in transmit mode is discarded.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ReceiveLatchEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    As most of the SQI communication is half-duplex, enable this function only
    when it's absolutely required.
 */

void PLIB_SQI_ReceiveLatchEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ReceiveLatchDisable (SQI_MODULE_ID index)

  Summary:
   Disables the receive latch so receive data is discarded when in transmit mode.

  Description:
    This routine disables the receive latch, which disables the receive data to be
    latched in transmit mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ReceiveLatchDisable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ReceiveLatchDisable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_ReceiveLatchGet (SQI_MODULE_ID index)

  Summary:
   Returns the receive latch status in transmit mode.

  Description:
    This routine returns the receive latch status in transmit mode. Returns true,
    if latch is set (enabling latching of receive buffer data), false if latch is
    not set (disabling the latching of the receive buffer data).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    True if Receive latch is set, false if not.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool rxLatch = PLIB_SQI_ReceiveLatchGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_ReceiveLatchGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_WriteProtectSet (SQI_MODULE_ID index)

  Summary:
   This bit sets the Write-Protect function to be enabled on SQID2 in
   single or dual Lane modes only.

  Description:
    This routine enables the SQID2 pin to be used for write-protect in single
    and dual lane modes for supported flash memories.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_WriteProtectSet (MY_SQI_INSTANCE);
    </code>

  Remarks:
    This function should be used only when SQI is in single/dual lane modes.
 */

void PLIB_SQI_WriteProtectSet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_WriteProtectClear (SQI_MODULE_ID index)

  Summary:
   This bit clears the Write-Protect function to be disabled on SQID2 in
   single or dual lane modes.

  Description:
    This routine disables the SQID2 pin to be used for write-protect function.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_WriteProtectClear(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_WriteProtectClear(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_WriteProtectGet (SQI_MODULE_ID index)

  Summary:
   This bit gets the Write-Protect state of Write_Protect Feature on SQID2.

  Description:
    This routine gets the Write-Protect feature status on SQID2 pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool wpStatus = PLIB_SQI_WriteProtectGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_WriteProtectGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_HoldSet (SQI_MODULE_ID index)

  Summary:
   This bit sets the hold function to be enabled on SQID3 in single or dual lane
   modes.

  Description:
    This routine sets the SQID3 pin to HIGH/LOW to be be used for hold function in
    single and dual lane modes for supported flash memories.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_HoldSet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    This function should be used only when SQI is in single/dual lane modes.
 */

void PLIB_SQI_HoldSet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_HoldClear (SQI_MODULE_ID index)

  Summary:
   This bit clears the hold function to be disabled on SQID3 in single and dual
   lane modes.

  Description:
    This routine sets SQID3 to be controlled by SQI for normal data operation.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_HoldClear(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_HoldClear(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_HoldGet (SQI_MODULE_ID index)

  Summary:
   This bit gets the status of HOLD function on SQID3 pin.

  Description:
    This routine gets the status of HOLD function on SQID3 pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool holdStatus = PLIB_SQI_HoldGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_HoldGet(SQI_MODULE_ID index);

//******************************************************************************
/* Function:
    void PLIB_SQI_BurstEnable (SQI_MODULE_ID index)

  Summary:
   This bit sets the burst enable (BURSTEN) function for higher throughput. This
   function is artifact of the system bus architecture.

  Description:
    This routine enables burst mode for higher throughput. Burst mode should always
    be enabled.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_BurstEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_BurstEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_SoftReset (SQI_MODULE_ID index)

  Summary:
   This bit issues a soft reset to the SQI module.

  Description:
    This routine issues a software reset to the SQI module clearing all the
   	read/write register, internal state machines and data buffers.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_SoftReset(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_SoftReset(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DataOutputEnableSelect (SQI_MODULE_ID index, SQI_DATA_OEN dataPins)

  Summary:
    Selects the output enables on SQI data outputs.

  Description:
    This routine enables the selected SQI data lines as outputs.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    dataPins        - Data pins for which outputs are enabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DataOutputEnableSelect(MY_SQI_INSTANCE, SQI_DATA_OEN_DUAL);
    </code>

  Remarks:
    Chip select is not actually asserted, only enabled to be asserted.
 */

void PLIB_SQI_DataOutputEnableSelect(SQI_MODULE_ID index, SQI_DATA_OEN dataPins);


//******************************************************************************
/* Function:
    void PLIB_SQI_CSOutputEnableSelect(SQI_MODULE_ID index, SQI_CS_OEN csPins)

  Summary:
    Selects the output enables on SQI chip select pins.

  Description:
    This routine enables the selected SQI chip selects as outputs.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    csPins          - Chip select pins for which outputs are enabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_CSOutputEnableSelect(MY_SQI_INSTANCE, SQI_CS_OEN_0);
    </code>

  Remarks:
    Chip select is not actually asserted, only enabled to be asserted.
 */

void PLIB_SQI_CSOutputEnableSelect(SQI_MODULE_ID index, SQI_CS_OEN csPins);


//******************************************************************************
/* Function:
    void PLIB_SQI_ConfigWordSet(SQI_MODULE_ID index,
                                bool sqiEnable,
                                SQI_CS_OEN csPins,
                                SQI_DATA_OEN dataPins,
                                bool reset,
                                bool burstEn,
                                bool hold,
                                bool writeProtect,
                                bool rxLatch,
                                SQI_DATA_FORMAT lsbf,
                                SQI_DATA_MODE dataMode,
                                SQI_XFER_MODE xferMode
                                )

  Summary:
    Sets SQI Configuration Word.

  Description:
    This routine sets SQI Configuration Word. This API is cumulation of multiple
    APIs, in case driver plans to write the complete configuration word.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    sqiEnable       - Enables/Disables the SQI module
    csPins			- Chip Select Output Enable
    dataPins		- Data Output Enable
    reset			- Resets control, transmit, receive buffers and state machines
    burstEn			- Burst Enable (always set to '1')
    hold			- SQID2 to act as HOLD# signal in single and dual lane modes
    writeProtect	- SQID3 to act as WP# signal in single and dual lane modes
    rxLatch			- Activates receive latch in transmit mode
    lsbf			- Sets data endian mode to least significant bit first (LSBF)
    dataMode		- Sets data mode to mode 0/mode 1/serial flash mode
    xferMode		- Sets transfer mode to XIP/DMA/PIO mode

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ConfigWordSet(MY_SQI_INSTANCE,
                           1,
                           SQI_CS_OEN_0,
                           SQI_DATA_OEN_QUAD,
                           0,
                           1,
                           0,
                           0,
                           0,
                           SQI_DATA_FORMAT_LSBF,
                           SQI_DATA_MODE_3,
                           SQI_XFER_MODE_PIO
                           );
    </code>

  Remarks:
    Chip select is not actually asserted, only enabled to be asserted.
 */

void PLIB_SQI_ConfigWordSet(SQI_MODULE_ID index,
                            bool sqiEnable,
                            SQI_CS_OEN csPins,
                            SQI_DATA_OEN dataPins,
                            bool reset,
                            bool burstEn,
                            bool hold,
                            bool writeProtect,
                            bool rxLatch,
                            SQI_DATA_FORMAT lsbf,
                            SQI_DATA_MODE dataMode,
                            SQI_XFER_MODE xferMode
                            );


//******************************************************************************
/* Function:
    uint32_t PLIB_SQI_ConfigWordGet (SQI_MODULE_ID index)

  Summary:
   	Get the SQI configuration word.

  Description:
    This routine returns the  SQI configuration word.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t sqiCfg = PLIB_SQI_ConfigWordGet (MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

 uint32_t PLIB_SQI_ConfigWordGet (SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ByteCountSet (SQI_MODULE_ID index, uint16_t xferCount)

  Summary:
   Sets the transmit/receive count.

  Description:
    This routine sets the number of bytes to transmit or receive, which is set by
    software and is actively contrtolled and maintained by hardware.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    count           - Transmit/Receive count

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_XFER_COUNT is the transfer count.
    PLIB_SQI_ByteCountSet(MY_SQI_INSTANCE, MY_XFER_COUNT);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ByteCountSet(SQI_MODULE_ID index, uint16_t xferCount);


//******************************************************************************
/* Function:
    uint16_t PLIB_SQI_ByteCountGet (SQI_MODULE_ID index)

  Summary:
   Returns the current transmit/receive count.

  Description:
    This routine returns the transmit/receive count, which is set by software and
    is actively contrtolled and maintained by hardware.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    count           - Transmit/Receive count

  Returns:
    Transfer Count.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint16_t xferCount = PLIB_SQI_ByteCountGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint16_t PLIB_SQI_ByteCountGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_TransferDirectionSet (SQI_MODULE_ID index, SQI_XFER_CMD command)

  Summary:
   Sets the transfer command.

  Description:
    This routine sets the transfer command to Idle/Transmit/Receive.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    command         - Transfer command

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and SQI_CMD_TRANSMIT is an enum element.
    PLIB_SQI_TransferDirectionSet(MY_SQI_INSTANCE, SQI_CMD_TRANSMIT);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_TransferDirectionSet(SQI_MODULE_ID index, SQI_XFER_CMD command);


//******************************************************************************
/* Function:
    SQI_XFER_CMD PLIB_SQI_TransferDirectionGet (SQI_MODULE_ID index)

  Summary:
   Returns the transfer command.

  Description:
    This routine returns the transfer command that is active currently.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Transfer Command (Idle/Receive/Transmit).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_XFER_CMD xferDirection = PLIB_SQI_TransferDirectionGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_XFER_CMD PLIB_SQI_TransferDirectionGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_LaneModeSet (SQI_MODULE_ID index, SQI_LANE_MODE mode)

  Summary:
   Sets the data lane mode (single/dual/quad).

  Description:
    This routine sets the number of lanes (single/dual/quad) used for tansfers.

  Precondition:
    Make sure the output enable is selected on the data lines
    (PLIB_SQI_DataOutputEnableSelect). The device needs to be programmed to the
    same mode that the SQI controller is set to (might require special commands).

  Parameters:
    index           - Identifier for the device instance to be configured
    mode	        - Lane mode (single/dual/quad)

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_LaneModeSet(MY_SQI_INSTANCE, SQI_LANE_QUAD);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_LaneModeSet(SQI_MODULE_ID index, SQI_LANE_MODE mode);


//******************************************************************************
/* Function:
    SQI_LANE_MODE PLIB_SQI_LaneModeGet (SQI_MODULE_ID index)

  Summary:
   Returns the lane mode (single/dual/quad).

  Description:
    This routine returns the number of lanes (single/dual/quad) used for tansfers.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Lane Mode.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_LANE_MODE laneMode = PLIB_SQI_LaneModeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_LANE_MODE PLIB_SQI_LaneModeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ChipSelectSet (SQI_MODULE_ID index, SQI_CS_NUM csNum)

  Summary:
   Activates the chip select.

  Description:
    This routine sets the chip select to be activated on the next transaction.

  Precondition:
    Make sure the chip select output enable is selected on the CS lines
    (PLIB_SQI_CSOutputEnableSelect).

  Parameters:
    index           - Identifier for the device instance to be configured
    csNum           - Chip select number

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and SQI_CS_NUM_0 is the enum element.
    PLIB_SQI_ChipSelectSet(MY_SQI_INSTANCE, SQI_CS_NUM_0);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ChipSelectSet(SQI_MODULE_ID index, SQI_CS_NUM csNum);


//******************************************************************************
/* Function:
    SQI_CS_NUM PLIB_SQI_ChipSelectGet(SQI_MODULE_ID index)

  Summary:
   Returns the chip select that is currently active.

  Description:
    This routine returns the chip select that is currently active.

  Precondition:
	None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Chip Select (2-bit)	- Current chip select active (0/1).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_CS_NUM csNum = PLIB_SQI_ChipSelectGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_CS_NUM PLIB_SQI_ChipSelectGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ChipSelectDeassertEnable (SQI_MODULE_ID index)

  Summary:
   Sets the chip select de-assert.

  Description:
    This routine enables chip select de-assert. Chip select is de-asserted after
    transmission or reception of the specified number of bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ChipSelectDeassertEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ChipSelectDeassertEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ChipSelectDeassertDisable(SQI_MODULE_ID index)

  Summary:
   Clears the chip select de-assert.

  Description:
    This routine disables the chip select de-assert. Chip select stays asserted
    after transmission or reception of specified number of bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ChipSelectDeassertDisable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ChipSelectDeassertDisable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ControlWordSet(SQI_MODULE_ID index,
                                 bool csDeassert,
                                 SQI_CS_NUM csNum,
                                 SQI_LANE_MODE laneMode,
                                 SQI_XFER_CMD command,
                                 uint16_t xferCount
                                )

  Summary:
    Sets SQI Control Word.

  Description:
    This routine sets SQI Control Word. This API is cumulation of multiple
    APIs, in case driver plans to write the complete control word. In PIO
    Mode Control word is before each transfer

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    csDeassert      - Chip select deassert after transfer
    csNum			- Active chip select number (0/1)
    laneMode		- SQI lane mode (QUAL/DUAL/SINGLE)
    command			- Transfer command (TRANSMIT/RECIEVE/IDLE)
    xferCount   	- Number of bytes to be transmitted/received

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ControlWordSet(MY_SQI_INSTANCE,
                            1,
                            SQI_CS_1,
                            SQI_LANE_QUAD,
                            SQI_CMD_TRANSMIT,
                            5
                            );
    </code>

  Remarks:
    Chip select is not actually asserted, only enabled to be asserted.
 */

void PLIB_SQI_ControlWordSet(SQI_MODULE_ID index,
                             bool csDeassert,
                             SQI_CS_NUM csNum,
                             SQI_LANE_MODE laneMode,
                             SQI_XFER_CMD command,
                             uint16_t xferCount
                            );


//******************************************************************************
/* Function:
    uint32_t PLIB_SQI_ControlWordGet (SQI_MODULE_ID index)

  Summary:
   	Get the SQI control word.

  Description:
    This routine returns the  SQI control word.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t sqiCon = PLIB_SQI_ControlWordGet (MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

 uint32_t PLIB_SQI_ControlWordGet (SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ClockEnable (SQI_MODULE_ID index)

  Summary:
   Enables the SQI transfer clock.

  Description:
    This routine enables the SQI transfer clock (divided clock).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ClockEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    SQICLK is enabled.
 */

void PLIB_SQI_ClockEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ClockDisable (SQI_MODULE_ID index)

  Summary:
   Disables the SQI transfer clock.

  Description:
    This routine disables the SQI transfer clock (divided clock).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ClockDisable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    SQICLK is disabled.
 */

void PLIB_SQI_ClockDisable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_ClockIsStable (SQI_MODULE_ID index)

  Summary:
   	Returns SQI transfer clock state.

  Description:
    This routine returns the SQI transfer clock state.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   True if clock is stable and false if it's not.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool clockState = PLIB_SQI_ClockIsStable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_ClockIsStable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ClockDividerSet (SQI_MODULE_ID index, SQI_CLK_DIV clkDivider)

  Summary:
   	Sets the SQI clock (that drives the SQI protocol) divider value.
	Divides the base clock to generate the SQI clock.

  Description:
    This routine sets the SQI clock divider value.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    clkDivider		- Clock divider value

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_ClockDividerSet(MY_SQI_INSTANCE, CLK_DIV_1);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_ClockDividerSet(SQI_MODULE_ID index, SQI_CLK_DIV clkDivider);


//******************************************************************************
/* Function:
    SQI_CLK_DIV PLIB_SQI_ClockDividerGet (SQI_MODULE_ID index)

  Summary:
   	Returns the SQI clock divider value.

  Description:
    This routine returns the SQI clock divider value. The returned value in
    conjuction with the SQI base clock can be used to get the clock rate
    of SQI clock.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Clock Divider Value.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_CLK_DIV clkDiv = PLIB_SQI_ClockDividerGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_CLK_DIV PLIB_SQI_ClockDividerGet(SQI_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: XIP mode Interface
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_XIPLaneModeSet (SQI_MODULE_ID index,
    							  SQI_LANE_MODE dataLanes,
    							  SQI_LANE_MODE dummyLanes,
    							  SQI_LANE_MODE modeLanes,
    							  SQI_LANE_MODE addrLanes,
    							  SQI_LANE_MODE cmdLanes
    							 )

  Summary:
   	Selects the lane (Single/Dual/Quad) mode for different transaction in XIP mode.

  Description:
    This routine selects the lane (Single/Dual/Quad) mode for different transaction
    in XIP mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    dataLanes       - Data lane mode (single/dual/quad)
    dummyLanes      - Dummy lane mode (single/dual/quad)
    modeLanes       - Mode lane mode (single/dual/quad)
    addrLanes       - Address lane mode (single/dual/quad)
    cmdLanes        - Command lane mode (single/dual/quad)

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPLaneModeSet(MY_SQI_INSTANCE,
    						SQI_QUAD_SINGLE,
    						SQI_QUAD_SINGLE,
    						SQI_QUAD_SINGLE,
    						SQI_QUAD_SINGLE,
    						SQI_QUAD_SINGLE
    					   );
    </code>

  Remarks:
    This routine can't be called when in XIP mode.
 */

void PLIB_SQI_XIPLaneModeSet (SQI_MODULE_ID index,
    						  SQI_LANE_MODE dataLanes,
    						  SQI_LANE_MODE dummyLanes,
    						  SQI_LANE_MODE modeLanes,
    						  SQI_LANE_MODE addrLanes,
    						  SQI_LANE_MODE cmdLanes
    					     );


//******************************************************************************
/* Function:
    SQI_LANE_MODE PLIB_SQI_XIPLaneModeGet (SQI_MODULE_ID index)

  Summary:
   	Returns the lane (single/dual/quad) mode in XIP mode.

  Description:
    This routine returns the the number of SQI lanes ((single/dual/quad)) used
    in XIP mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Lane Mode (Single/Dual/Quad) that SQI Command uses.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_LANE_MODE laneMode = PLIB_SQI_XIPCommandTypeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    This routine can't be called when in XIP mode.
 */

SQI_LANE_MODE PLIB_SQI_XIPLaneModeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPReadOpcodeSet (SQI_MODULE_ID index, uint8_t opCode )

  Summary:
   	Sets the read opcode in XIP mode.

  Description:
    This routine sets the flash read opcode in XIP mode. Value of read opcode
    depends on the flash device attached.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    opCode			- Flash read opcode

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_READ_OPCODE is the opcode dependant on
    // attached serial device.
    PLIB_SQI_XIPReadOpcodeSet(MY_SQI_INSTANCE, MY_READ_OPCODE);
    </code>

  Remarks:
    Refer to the flash device datasheet for supported read opcodes.
 */

void PLIB_SQI_XIPReadOpcodeSet(SQI_MODULE_ID index, uint8_t opCode);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_XIPReadOpcodeGet (SQI_MODULE_ID index)

  Summary:
   	Returns the read opcode in XIP mode.

  Description:
    This routine returns the read opcode used in XIP mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Read Opcode.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t readOpcode = PLIB_SQI_XIPReadOpcodeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_XIPReadOpcodeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPAddressBytesSet (SQI_MODULE_ID index, SQI_ADDR_BYTES bytes)

  Summary:
   	Sets the number of address bytes.

  Description:
    This routine sets the number of address bytes to be sent to the flash. Typical flash
    address bytes are 3 (24-bit address).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    bytes			- Number of address bytes

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPAddressBytesSet(MY_SQI_INSTANCE, ADDR_BYTES_3);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_XIPAddressBytesSet(SQI_MODULE_ID index, SQI_ADDR_BYTES bytes);


//******************************************************************************
/* Function:
    SQI_ADDR_BYTES PLIB_SQI_XIPAddressBytesGet (SQI_MODULE_ID index)

  Summary:
   	Returns the number of address bytes.

  Description:
    This routine returns the number of address bytes to be sent to the flash.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Number of Address Bytes.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t addressBytes = PLIB_SQI_XIPAddressBytesGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_ADDR_BYTES PLIB_SQI_XIPAddressBytesGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPDummyBytesSet (SQI_MODULE_ID index, SQI_DUMMY_BYTES bytes)

  Summary:
   	Sets the number of dummy bytes.

  Description:
    This routine sets the number of dummy bytes to be sent to the flash after the
    address bytes, i.e., before doing a fast read.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    bytes			- Number of dummy bytes

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPDummyBytesSet(MY_SQI_INSTANCE, DUMMY_BYTE_1);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_XIPDummyBytesSet(SQI_MODULE_ID index, SQI_DUMMY_BYTES bytes);


//******************************************************************************
/* Function:
    SQI_DUMMY_BYTES PLIB_SQI_XIPDummyBytesGet (SQI_MODULE_ID index)

  Summary:
   	Sets the number of dummy bytes.

  Description:
    This routine returns the number of dummy bytes to be sent to the flash after the
    address bytes, i.e., before doing a fast read.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t dummyBytes = PLIB_SQI_XIPDummyBytesGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_DUMMY_BYTES PLIB_SQI_XIPDummyBytesGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPControlWord1Set (SQI_MODULE_ID   index,
        		                      SQI_DUMMY_BYTES dummyBytes,
    		                          SQI_ADDR_BYTES  addressBytes,
    		                          uint8_t	      readOpcode,
    		                          SQI_LANE_MODE   dataLaneMode,
    		                          SQI_LANE_MODE   dummyLaneMode,
    		                          SQI_LANE_MODE   modeCodeLaneMode,
    		                          SQI_LANE_MODE   addressLaneMode,
    		                          SQI_LANE_MODE   cmdLaneMode
    		                         )

  Summary:
   	Sets the XIP mode control word 1.

  Description:
    This routine sets XIP mode control word 1. This routine combines work of multiple
    PLIB APIs and can be used by the driver where complete XIP control word 1 is being
    modified.

  Precondition:
    None.

  Parameters:
    index           	- Identifier for the device instance to be configured
    dummyBytes			- Number of dummy bytes (0-7)
    addressBytes		- Number of address bytes (0-4)
    readOpcode			- Quad flash read opcode (ex: 0x0B)
    dataLaneMode		- Number of SQI data lanes used for sending data bytes
    dummyLaneMode		- Number of SQI data lanes used for sending dummy bytes
    modeCodeLaneMode	- Number of SQI data lanes used for sending mode code
    addressLaneMode		- Number of SQI data lanes used for sending address
    cmdLaneMode			- Number of SQI data lanes used for sending command

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPControlWord1Set (MY_SQI_INSTANCE,
      		                     DUMMY_BYTES_2,
      		                     ADDR_BYTES_3,
      		                     0x0B,
      		                     SQI_LANE_QUAD,
    		                     SQI_LANE_QUAD,
    		                     SQI_LANE_QUAD,
    		                     SQI_LANE_QUAD,
    		                     SQI_LANE_QUAD,
    		                    );
    </code>

  Remarks:
    None.
 */

 void PLIB_SQI_XIPControlWord1Set (SQI_MODULE_ID   index,
								   SQI_DUMMY_BYTES dummyBytes,
								   SQI_ADDR_BYTES  addressBytes,
								   uint8_t	      readOpcode,
								   SQI_LANE_MODE   dataLaneMode,
								   SQI_LANE_MODE   dummyLaneMode,
								   SQI_LANE_MODE   modeCodeLaneMode,
								   SQI_LANE_MODE   addressLaneMode,
    		                       SQI_LANE_MODE   cmdLaneMode
    		                      );


//******************************************************************************
/* Function:
    uint32_t PLIB_SQI_XIPControlWord1Get (SQI_MODULE_ID   index)

  Summary:
   	Get the XIP mode control word 1.

  Description:
    This routine returns the  XIP mode control word 1.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t xipCon1 = PLIB_SQI_XIPControlWord1Set (MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

 uint32_t PLIB_SQI_XIPControlWord1Get (SQI_MODULE_ID   index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPModeCodeSet (SQI_MODULE_ID index, uint8_t code)

  Summary:
   	Sets the mode code command.

  Description:
    This routine sets the mode code command in XIP mode for the supported flash
    devices.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    code			- Mode code (byte)

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPModeCodeSet(MY_SQI_INSTANCE, MY_MODE_CODE);
    </code>

  Remarks:
    Some of the devices seems to support this command, refer to specific serial
    device data sheet for op-code and sequence details.
 */

void PLIB_SQI_XIPModeCodeSet(SQI_MODULE_ID index, uint8_t code);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_XIPModeCodeGet (SQI_MODULE_ID index)

  Summary:
   	Returns the mode code op-code.

  Description:
    This routine returns the mode code command (opcode) in XIP mode for the
    devices that support it.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Mode Code Opcode.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t modeCode = PLIB_SQI_XIPModeCodeGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
	None.
 */

uint8_t PLIB_SQI_XIPModeCodeGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPModeBytesSet (SQI_MODULE_ID index, SQI_MODE_BYTES bytes)

  Summary:
   	Allocates the bytes for mode code command.

  Description:
    This routine sets the number of bytes for the mode code command in XIP mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    bytes			- Number of bytes of Mode code

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPModeBytesSet(MY_SQI_INSTANCE, MODE_BYTES_0);
    </code>

  Remarks:
    Refer to serial device datasheet for the details on this command.
 */

void PLIB_SQI_XIPModeBytesSet(SQI_MODULE_ID index, SQI_MODE_BYTES bytes);


//******************************************************************************
/* Function:
    SQI_MODE_BYTES PLIB_SQI_XIPModeBytesGet (SQI_MODULE_ID index)

  Summary:
   	Returns the number of bytes used for mode code command.

  Description:
    This routine returns the number of bytes for the mode code command in XIP mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	Number of Bytes used for Mode Code Command.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_MODE_BYTES modeCodeBytes = PLIB_SQI_XIPModeBytesGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_MODE_BYTES PLIB_SQI_XIPModeBytesGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPChipSelectSet (SQI_MODULE_ID index, SQI_CS_NUM csNum)

  Summary:
   Activates the chip select in XIP mode.

  Description:
    This routine sets the chip select that is active in XIP mode.

  Precondition:
    Make sure the chip select output enable is selected on the CS lines
    (PLIB_SQI_CSOutputEnableSelect).

  Parameters:
    index           - Identifier for the device instance to be configured
    csNum           - Chip select number

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPChipSelectSet(MY_SQI_INSTANCE, SQI_CS_0);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_XIPChipSelectSet(SQI_MODULE_ID index, SQI_CS_NUM csNum);


//******************************************************************************
/* Function:
    SQI_CS_NUM PLIB_SQI_XIPChipSelectGet (SQI_MODULE_ID index)

  Summary:
   Returns the current active chip select.

  Description:
    This routine returns the active chip select in XIP mode.

  Precondition:
	None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    SQI_CS_NUM xipCSActive = (PLIB_SQI_XIPChipSelectGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

SQI_CS_NUM PLIB_SQI_XIPChipSelectGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_XIPControlWord2Set (SQI_MODULE_ID   index,
    		                          SQI_CS_NUM		devSelect,
    		                          SQI_MODE_BYTES 	modeBytes,
    		                          uint8_t			modeCode
    		                         )

  Summary:
   	Sets the XIP mode control word 2.

  Description:
    This routine sets XIP mode control word 2. This routine combines work of multiple
    PLIB APIs and can be used by the driver where complete XIP control word 2 is being
    modified.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    modeCode		- Mode code used for supported flash devices
	modeBytes		- Number of mode code bytes
	devSelect		- Chip select for XIP mode

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_XIPControlWord2Set (MY_SQI_INSTANCE,
      		                     SQI_CS_0,
    		                     MODE_BYTES_0,
    		                     0x0
    		                    );
    </code>

  Remarks:
    None.
 */

 void PLIB_SQI_XIPControlWord2Set (SQI_MODULE_ID   index,
    		                       SQI_CS_NUM	   devSelect,
								   SQI_MODE_BYTES  modeBytes,
    		                       uint8_t		   modeCode
    		                      );


//******************************************************************************
/* Function:
    uint32_t PLIB_SQI_XIPControlWord2Get (SQI_MODULE_ID   index)

  Summary:
   	Get the XIP mode control word 2.

  Description:
    This routine returns the  XIP mode control word 2.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t xipCon2 = PLIB_SQI_XIPControlWord2Set (MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

 uint32_t PLIB_SQI_XIPControlWord2Get (SQI_MODULE_ID   index);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: Buffer Control
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_TxBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold)

  Summary:
   Sets the transmit command threshold.

  Description:
    This routine sets the transmit command threshold, which is used to control
    transmits based on the transmit buffer space availability.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold       - Transmit command (buffer) threshold

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_TRANSMIT_THRESHOLD is the threshold value.
    PLIB_SQI_TxBufferThresholdSet(MY_SQI_INSTANCE, MY_TRANSMIT_THRESHOLD);
    </code>

  Remarks:
    Valid threshold values are 0-31.
 */

void PLIB_SQI_TxBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_TxBufferThresholdGet(SQI_MODULE_ID index)

  Summary:
   Returns the transmit command threshold value.

  Description:
    This routine returns the transmit command threshold value that is  used to
    monitor transmits based on the transmit buffer space availability.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Transmit buffer threshold value.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t txThreshold = PLIB_SQI_TxBufferThresholdGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_TxBufferThresholdGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_RxBufferThresholdSet (SQI_MODULE_ID index, uint8_t threshold)

  Summary:
   Sets the receive command threshold.

  Description:
    This routine sets the receive command threshold that is used to monitor
    receives based on the receive buffer space availability.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold       - Receive command (buffer) threshold

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_RECEIVE_THRESHOLD is the receive threshold value.
    PLIB_SQI_RxCommandThresholdSet(MY_SQI_INSTANCE, MY_RECEIVE_THRESHOLD);
    </code>

  Remarks:
    Valid threshold values are 0-31.
 */

void PLIB_SQI_RxBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_RxBufferThresholdGet (SQI_MODULE_ID index)

  Summary:
   Returns the receive command threshold.

  Description:
    This routine returns the receive command threshold that is used to monitor
    receives based on the receive buffer space availability.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Receive Buffer Threshold value.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t rxBufThres = PLIB_SQI_RxCommandThresholdGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_RxBufferThresholdGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_TxBufferThresholdIntSet (SQI_MODULE_ID index, uint8_t threshold)

  Summary:
   Sets the value to tigger the transmit buffer threshold interrupt.

  Description:
    This routine sets the transmit buffer threshold used for an interrupt. When
    enabled, interrupt is triggered when transmit buffer has more space than the
    transmit interrupt threshold bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold       - Transmit interrupt (buffer) threshold

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_TX_INT_THRESHOLD is the threshold value.
    PLIB_SQI_TxBufferThresholdIntSet(MY_SQI_INSTANCE, MY_TX_INT_THRESHOLD);
    </code>

  Remarks:
    This is a 5-bit fild and bits 7,6,5 are ignored in the char.
 */

void PLIB_SQI_TxBufferThresholdIntSet(SQI_MODULE_ID index, uint8_t threshold);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_TxBufferThresholdIntGet (SQI_MODULE_ID index)

  Summary:
   Returns the value to tigger the transmit buffer threshold interrupt.

  Description:
    This routine returns the transmit buffer threshold used to set an interrupt.
    When enabled, interrupt is triggered when transmit buffer has more space
    than the transmit interrupt threshold bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Transmit buffer threshold for interrupt.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t txBufIntThres = PLIB_SQI_TxBufferThresholdIntGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_TxBufferThresholdIntGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_RxBufferThresholdIntSet (SQI_MODULE_ID index, uint8_t threshold)

  Summary:
   Sets the receive buffer threshold for interrupt.

  Description:
    This routine sets the receive buffer threshold used to trigger an interrupt.
    Sets an interrpt condition when receive buffer count is larger than or equal
    to the receive interrupt threshold bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold       - Receive buffer threshold for interrupt

  Returns:
	None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_RX_INT_THRESHOLD is the threshold value.
    PLIB_SQI_RxBufferThresholdIntSet(MY_SQI_INSTANCE, MY_RX_INT_THRESHOLD);
    </code>

  Remarks:
    This is a 5-bit fild and bits 7,6,5 are ignored in the char.
 */

void PLIB_SQI_RxBufferThresholdIntSet(SQI_MODULE_ID index, uint8_t threshold);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_RxBufferThresholdIntGet (SQI_MODULE_ID index)

  Summary:
   Sets the receive buffer threshold interrupt.

  Description:
    This routine returns the receive buffer threshold used to set an interrupt.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold       - Receive interrupt (buffer) threshold

  Returns:
	Receive Buffer Threshold value (used to trigger an interrupt).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t rxBufIntThres = PLIB_SQI_RxBufferThresholdIntGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    This is a 5-bit fild and bits 7,6,5 are ignored in the char.
 */

uint8_t PLIB_SQI_RxBufferThresholdIntGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_ControlBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold)

  Summary:
  	Sets the control buffer threshold value.

  Description:
    This routine sets the control buffer threshold value in bytes, that is used to
    signal control buffer threshold interrupts.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    threshold		- Control buffer threshold

  Returns:
    None.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_CONBUF_THRESHOLD is the threshold value.
    PLIB_SQI_ControlBufferThresholdSet(MY_SQI_INSTANCE, MY_CONBUF_THRESHOLD);
    </code>

  Remarks:
	None.
 */

 void PLIB_SQI_ControlBufferThresholdSet(SQI_MODULE_ID index,  uint8_t threshold);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_ControlBufferThresholdGet(SQI_MODULE_ID index)

  Summary:
  	Returns the transmit buffer space in bytes.

  Description:
    This routine returns the threshold value for the control buffer in bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Control buffer threshold space.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t conBufThres = PLIB_SQI_ControlBufferThresholdGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_ControlBufferThresholdGet(SQI_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: Interrupts
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_InterruptEnable (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Enables the interrupt source passed.

  Description:
    This routine enables the interrupt source passed into the function.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt to be enabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_InterruptEnable(MY_SQI_INSTANCE, SQI_TXFULL);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_InterruptEnable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


//******************************************************************************
/* Function:
    void PLIB_SQI_InterruptDisable (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Disables the interrupt source.

  Description:
    This routine disables the interrupt source passed into the function.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt to be disabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and TXFULL is an enum element.
    PLIB_SQI_InterruptDisable(MY_SQI_INSTANCE, SQI_TXFULL);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_InterruptDisable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


//******************************************************************************
/* Function:
    bool PLIB_SQI_InterruptIsEnabled (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Returns the interrupt state (eanbled/disabled).

  Description:
    This routine returns the interrupt state.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt under check

  Returns:
    True if Interrupt is Enabled, else false.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    if (PLIB_SQI_InterruptIsEnabled(MY_SQI_INSTANCE, SQI_TXFULL))
    {
		..
	}
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_InterruptIsEnabled(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


//******************************************************************************
/* Function:
    void PLIB_SQI_InterruptSignalEnable (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Enables the interrupt signal source passed.

  Description:
    This routine enables the interrupt signal source passed into the function, thus letting it
    go out to the external interrupt controller.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt to be enabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_InterruptSignalEnable(MY_SQI_INSTANCE, SQI_TXFULL);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_InterruptSignalEnable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


//******************************************************************************
/* Function:
    void PLIB_SQI_InterruptSignalDisable (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Disables the interrupt signal source.

  Description:
    This routine disables the interrupt signals source passed into the function, thus
    prohibitting it from reaching to the external interrupt controller.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt to be disabled

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_InterruptSignalDisable(MY_SQI_INSTANCE, SQI_TXFULL);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_InterruptSignalDisable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


//******************************************************************************
/* Function:
    bool PLIB_SQI_InterruptSignalIsEnabled (SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
   Returns the interrupt signal state (eanbled/disabled).

  Description:
    This routine returns the interrupt signal state.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    interruptFlag   - Interrupt signal under check

  Returns:
    Boolean flag	- Interrupt state
    					true  - Interrupt signal is enabled
    					false - Interrupt signal is disabled

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    if (PLIB_SQI_InterruptSignalIsEnabled(MY_SQI_INSTANCE, SQI_TXFULL))
    {
		..
	}
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_InterruptSignalIsEnabled(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


// *****************************************************************************
/* Function:
    bool PLIB_SQI_InterruptFlagGet( SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)

  Summary:
    Return SQI Interrupt flag status.

  Description:
    This routine returns the SQI interrupt source flag status (set/cleared).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance of interest
    interruptFlag   - Interrupt flag of interest

  Returns:
    Interrupt status.

  Example:
  <code>
    if ( PLIB_SQI_InterruptFlagGet(MY_SQI_INSTANCE,SQI_INT_ANY) )
        if ( PLIB_SQI_InterruptFlagGet(MY_SQI_INSTANCE,SQI_TXFULL) )
        {
           ...
        }
        if ( PLIB_SQI_InterruptFlagGet(MY_SQI_INSTANCE,SQI_RXFULL) )
        {
			...
        }
        .
        .
        .
    }
  </code>

  Remarks:
    None.
*/

bool PLIB_SQI_InterruptFlagGet( SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: transmit/receive
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_TransmitData (SQI_MODULE_ID index, uint32_t data)

  Summary:
  Writes data into the SQI transmit buffer.

  Description:
    This routine writes the data into the SQI transmit buffer, which will be
    eventually sent out on SQI bus.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    data 	 	    - Data to be transmitted

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer and MY_TRANSMIT_DATA is the data to be sent.
    PLIB_SQI_TransmitData(MY_SQI_INSTANCE, MY_TRANSMIT_DATA);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_TransmitData(SQI_MODULE_ID index, uint32_t data);


//******************************************************************************
/* Function:
    uint32_t PLIB_SQI_ReceiveData (SQI_MODULE_ID index)

  Summary:
 	Reads the data from the receive buffer.

  Description:
    This routine reads the data from the SQI receive buffer.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t receivedData= PLIB_SQI_ReceiveData(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint32_t PLIB_SQI_ReceiveData(SQI_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: Status
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_ReceiveBufferReadsGet(SQI_MODULE_ID index)

  Summary:
 	Returns the number of receive buffer reads.

  Description:
    This routine returns the number of receive buffer reads for debug purpose.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Number of Receive Buffer Reads.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t rxBufReads = PLIB_SQI_ReceiveBufferReadsGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_NumberOfReceiveBufferReads(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_TransmitBufferFreeSpaceGet(SQI_MODULE_ID index)

  Summary:
 	Returns the number of transmit buffer words available.

  Description:
    This routine returns the number of transmit buffer bytes available.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Amont of transmit buffer space free in bytes.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t txBufFreeSpace = PLIB_SQI_TransmitBufferFreeSpaceGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_TransmitBufferFreeSpaceGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_TransmitBufferHasOverflowed (SQI_MODULE_ID index)

  Summary:
 	Returns the current status of the transmit buffer.

  Description:
    This routine returns the current state of the transmit buffer.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    True if Transmit Buffer has Overflowed, false if not.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool txOv = PLIB_SQI_TransmitBufferHasOverflowed(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_TransmitBufferHasOverflowed(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_ReceiveBufferIsUnderrun (SQI_MODULE_ID index)

  Summary:
 	Returns the status of receive buffer.

  Description:
    This routine returns the status of the receive buffer.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    True if Receive Buffer is Underrun, False if not.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool rxun = PLIB_SQI_ReceiveBufferIsUnderrun(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_ReceiveBufferIsUnderrun(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_DataLineStatus(SQI_MODULE_ID index, uint8_t dataPin)

  Summary:
 	Returns the logical status of the SQI data lines.

  Description:
    This routine returns the logical status of the data lines(0/1).

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    dataPin			- Data pin for which status will be returned (0/1/2/3)

  Returns:
    SQIDx Status (High/Low).

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool sqiDataLineStatus = PLIB_SQI_DataLineStatus(MY_SQI_INSTANCE, 3);
    </code>

  Remarks:
    Parsing values other than 0/1/2/3 returns SQID0 pin status.
 */

bool PLIB_SQI_DataLineStatus(SQI_MODULE_ID index, bool dataPin);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: DMA Control
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_DMAEnable (SQI_MODULE_ID index)

  Summary:
  Enables the built-in DMA logic.

  Description:
    This routine enables the built-in DMA logic for data transfer.

  Precondition:
    DMA buffer descriptors need to be setup before enabling the DMA.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DMAEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_DMAEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DMADisable (SQI_MODULE_ID index)

  Summary:
  Disables the built-in DMA logic.

  Description:
    This routine disables the built-in DMA logic for data transfer.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DMADisable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_DMADisable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_DMAIsEnabled (SQI_MODULE_ID index)

  Summary:
  	Returns true if DAM is eanbled and false if it's disabled.

  Description:
    This routine returns true/false if DMA is enabled/disabled.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Boolean Flag	- DMA Enable Status
    					true  - DMA is enabled
    					false - DMA is disabled

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
   	If (PLIB_SQI_DMAIsEnabled(MY_SQI_INSTANCE))
   	{
	   ...
   	}
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_DMAIsEnabled(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DMABDPollEnable (SQI_MODULE_ID index)

  Summary:
  	Enables the buffer descriptor polling.

  Description:
    This routine enables the buffer descriptor polling and works in tandum with
    poll control register.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DMABDPollEnable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    Enable this control bit only when you are planning to have dead descriptors
    in the linked list.
 */

void PLIB_SQI_DMABDPollEnable(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DMABDPollDisable (SQI_MODULE_ID index)

  Summary:
  	Disables the buffer descriptor polling.

  Description:
    This routine disables the buffer descriptor polling.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DMABDPollDisable(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_DMABDPollDisable (SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_DMABDPollIsEnabled (SQI_MODULE_ID index)

  Summary:
  	Returns true if DAM buffer descriptor poll is eanbled and false if it's disabled.

  Description:
    This routine returns true/false if DMA buffer descriptor poll is enabled/disabled.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   True if DMA Poll Control is Enabled, else it's false.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
   	If (PLIB_SQI_DMABDPollIsEnabled(MY_SQI_INSTANCE))
   	{
	   PLIB_SQI_PollControlSet(MY_SQI_INSTANCE, MY_POLL_CONTROL_VALUE);
   	}
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_DMABDPollIsEnabled(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_SQI_DMABDFetchStart (SQI_MODULE_ID index)

  Summary:
  	Start the DMA buffer descriptor fetch process.

  Description:
    This routine starts the DMA buffer descriptor fetch process.

  Precondition:
    Make sure the buffer descreptors are setup and the buffer descriptor
    base address register is pointing to the first/only buffer descriptor.
    Also ensure any previous BD processing is fixed.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    PLIB_SQI_DMABDFetchStart(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

void PLIB_SQI_DMABDFetchStart(SQI_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: DMA Buffer Handling
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_SQI_DMABDBaseAddressSet (SQI_MODULE_ID index,  void *baseBDAddress)

  Summary:
  	Sets the address of the base buffer descriptor.

  Description:
    This routine writes the address of the base (first/only) buffer descriptor
    into the buffer descriptor base address register.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    baseBDAddress	- Base buffer descriptor address

  Returns:
    None.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    if (!PLIB_SQI_DMAIsActive(MY_SQI_INSTANCE))
    	PLIB_SQI_DMABDBaseAddressSet(MY_SQI_INSTANCE, (void *) (&MY_BD_STRUCT));
    </code>

  Remarks:
    Check to make sure if DMA Buffer Descriptor fetch is in progress.
 */

void PLIB_SQI_DMABDBaseAddressSet(SQI_MODULE_ID index, void *baseBDAddress);


//******************************************************************************
/* Function:
    void PLIB_SQI_DMABDPollCounterSet(SQI_MODULE_ID index,  uint16_t pollCount)

  Summary:
  	Sets the poll counter value.

  Description:
    This routine sets the poll counter value that indicates the number of cycles
    the DMA would wait before fetching the next descriptor word, if the current
    descriptor fetched was disabled.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pollControl		- Polling value

  Returns:
    None.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    if (PLIB_SQI_DMABDPollIsEnabled(MY_SQI_INSTANCE)
    {
    	PLIB_SQI_DMABDPollCounterSet(MY_SQI_INSTANCE, MY_POLL_VALUE);
	}
    </code>

  Remarks:
	None.
 */

 void PLIB_SQI_DMABDPollCounterSet(SQI_MODULE_ID index,  uint16_t pollCount);


// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Interface Routines: DMA Status
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void * PLIB_SQI_DMABDBaseAddressGet(SQI_MODULE_ID index)

  Summary:
  	Returns the address of the base buffer descriptor.

  Description:
    This routine returns the address of the base DMA buffer descriptor.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
   Base Buffer Descriptor Address.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    void *baseBDAddress;

   	If (!PLIB_SQI_DMAIsActive(MY_SQI_INSTANCE))
   	{
	   baseBDAddress = PLIB_SQI_DMABDBaseAddressGet(MY_SQI_INSTANCE);
   	}
    </code>

  Remarks:
    Check to make sure if DMA Buffer Descriptor fetch is in progress.
 */

void* PLIB_SQI_DMABDBaseAddressGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    void* PLIB_SQI_DMABDCurrentAddressGet (SQI_MODULE_ID index)

  Summary:
  	Returns the address of the current buffer descriptor in process.

  Description:
    This routine returns the address of the DMA buffer descriptor that is currently
    in progress.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Current Buffer Descriptor Address.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint32_t currentBDAddress;

   	If (PLIB_SQI_DMAIsActive(MY_SQI_INSTANCE))
   	{
	   void* currentBDAddress = PLIB_SQI_DMABDCurrentAddressGet(MY_SQI_INSTANCE);
   	}
    </code>

  Remarks:
    Check to make sure if DMA Buffer Descriptor fetch is in progress.
 */

void* PLIB_SQI_DMABDCurrentAddressGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    SQI_BD_STATE PLIB_SQI_DMABDStateGet(SQI_MODULE_ID index)

  Summary:
  	Returns the current state of the buffer descriptor in progress.

  Description:
    This routine returns the current state of the buffer descriptor in progress.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Status			- DMA Buffer Descriptor State

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdState = PLIB_SQI_DMABDStateGet(MY_SQI_INSTANCE);

   	switch (bdState)
   	{
	   case BD_IDLE: ...;
	   case BD_FETCH_REQ_PENDING: ...;
	   .
	   .
	   .
   	}
    </code>

  Remarks:
    None.
 */

SQI_BD_STATE PLIB_SQI_DMABDStateGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    bool PLIB_SQI_DMAHasStarted (SQI_MODULE_ID index)

  Summary:
  	Returns true if DMA process has started if not returns false.

  Description:
    This routine returns true if DMA process started and false if DMA process has
    not started.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    True if DMA process has started, false if not.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
   	bool dmaStarted =  PLIB_SQI_DMAHasStarted (MY_SQI_INSTANCE)
    </code>

  Remarks:
    None.
 */

bool PLIB_SQI_DMAHasStarted(SQI_MODULE_ID index);


/*************************************************************************
  Function:
       bool PLIB_SQI_DMABDIsBusy (SQI_MODULE_ID index)

  Summary:
    \Returns true if DMA Buffer Descriptor is busy.
  Description:
    This routine returns true if DMA buffer descriptor process is busy, if
    not returns false.
  Conditions:
    None.
  Input:
    index -  Identifier for the device instance to be configured
  Return:
    True if DMA Buffer Desciptor is Busy.
  Example:
    <code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    bool bdBusy =  PLIB_SQI_DMABDIsBusy(MY_SQI_INSTANCE)
    </code>
  Remarks:
    None.
*/

bool PLIB_SQI_DMABDIsBusy(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint16_t PLIB_SQI_DMABDControlWordGet (SQI_MODULE_ID index)

  Summary:
  	Returns Current Buffer Descriptor Control Word Information.

  Description:
    This routine returns current buffer descriptor control word information
    excluding buffer length. This information is returned in transmit and receive
    status functions.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Control Word	- DMA Buffer Desciptor Control Word

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
   	uint16_t dmabdconword;

   	dmabdconword =  PLIB_SQI_DMABDControlWordGet(MY_SQI_INSTANCE);

   	switch (dmabdconword)
   	{
		case BD_ENABLED: ...;
		case BD_DISABLED: ...;
		.
		.
		.
	}

    </code>

  Remarks:
    None.
 */

uint16_t PLIB_SQI_DMABDControlWordGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    SQI_BD_STATE PLIB_SQI_DMABDTransmitStateGet(SQI_MODULE_ID index)

  Summary:
  	Returns the current state of the buffer descriptor in progress.

  Description:
    This routine returns the current state of the buffer descriptor in progress.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Status			- DMA Buffer Descriptor State

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdTxState = PLIB_SQI_DMABDTransmitStateGet(MY_SQI_INSTANCE);

   	switch (bdTxState)
   	{
	   case BD_IDLE: ...;
	   case BD_FETCH_REQ_PENDING: ...;
	   .
	   .
	   .
   	}
    </code>

  Remarks:
    None.
 */

SQI_BD_STATE PLIB_SQI_DMABDTransmitStateGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_DMABDTransmitBufferCountGet(SQI_MODULE_ID index)

  Summary:
  	Returns the transmit buffer space in bytes.

  Description:
    This routine returns the current transmit buffer space in bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
 	Transmit buffer space in bytes.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdTxBufCount = PLIB_SQI_DMABDTransmitBufferCountGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_DMABDTransmitBufferCountGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_DMABDTransmitBufferLengthGet(SQI_MODULE_ID index)

  Summary:
  	Returns the transmit length in bytes.

  Description:
    This routine returns the current transmit length in bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Transmit buffer space in bytes.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdTxBufLength = PLIB_SQI_DMABDTransmitBufferLengthGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_DMABDTransmitBufferLengthGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    SQI_BD_STATE uint8_t PLIB_SQI_DMABDReceiveStateGet(SQI_MODULE_ID index)

  Summary:
  	Returns the current state of the buffer descriptor in progress.

  Description:
    This routine returns the current state of the buffer descriptor in progress.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Status			- DMA Buffer Descriptor State

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdrxState = PLIB_SQI_DMABDReceiveStateGet(MY_SQI_INSTANCE);

   	switch (bdRxState)
   	{
	   case BD_IDLE: ...;
	   case BD_STATE_FETCH_REQ_PENDING: ...;
	   .
	   .
	   .
   	}
    </code>

  Remarks:
    None.
 */

SQI_BD_STATE PLIB_SQI_DMABDReceiveStateGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_DMABDReceiveBufferCountGet(SQI_MODULE_ID index)

  Summary:
  	Returns the receive buffer space in bytes.

  Description:
    This routine returns the current receive buffer space in bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Receive buffer space in bytes.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdRxBufCount = PLIB_SQI_DMABDReceiveBufferCountGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_DMABDReceiveBufferCountGet(SQI_MODULE_ID index);


//******************************************************************************
/* Function:
    uint8_t PLIB_SQI_DMABDReceiveBufferLengthGet(SQI_MODULE_ID index)

  Summary:
  	Returns the receive length in bytes.

  Description:
    This routine returns the current receive length in bytes.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    Receive buffer space in bytes.

  Example:
  	<code>
    // Where MY_SQI_INSTANCE, is the SQI instance selected for use by the
    // application developer.
    uint8_t bdRxBufLength = PLIB_SQI_DMABDReceiveBufferLengthGet(MY_SQI_INSTANCE);
    </code>

  Remarks:
    None.
 */

uint8_t PLIB_SQI_DMABDReceiveBufferLengthGet(SQI_MODULE_ID index);

// *****************************************************************************
// *****************************************************************************
// Section: SQI Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device.
*/

//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPNumberOfDummyBytes( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPNumberOfDummyBytes feature exists on the SQI module

  Description:
    This function identifies whether the XIPNumberOfDummyBytes feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPDummyBytesSet
    - PLIB_SQI_XIPDummyBytesGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPNumberOfDummyBytes feature is supported on the device
    - false  - The XIPNumberOfDummyBytes feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPNumberOfDummyBytes( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPNumberOfAddressBytes( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPNumberOfAddressBytes feature exists on the SQI module

  Description:
    This function identifies whether the XIPNumberOfAddressBytes feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPAddressBytesSet
    - PLIB_SQI_XIPAddressBytesGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPNumberOfAddressBytes feature is supported on the device
    - false  - The XIPNumberOfAddressBytes feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPNumberOfAddressBytes( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPReadOpCode( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPReadOpCode feature exists on the SQI module

  Description:
    This function identifies whether the XIPReadOpCode feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPReadOpcodeSet
    - PLIB_SQI_XIPReadOpcodeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPReadOpCode feature is supported on the device
    - false  - The XIPReadOpCode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPReadOpCode( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPLaneMode( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPLaneMode feature exists on the SQI module

  Description:
    This function identifies whether the XIPLaneMode feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPLaneModeSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPLaneMode feature is supported on the device
    - false  - The XIPLaneMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPLaneMode( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPControlWord1( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPControlWord1 feature exists on the SQI module

  Description:
    This function identifies whether the XIPControlWord1 feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPControlWord1Set
    - PLIB_SQI_XIPControlWord1Get

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPControlWord1 feature is supported on the device
    - false  - The XIPControlWord1 feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPControlWord1( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPChipSelect( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPChipSelect feature exists on the SQI module

  Description:
    This function identifies whether the XIPChipSelect feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPChipSelectSet
    - PLIB_SQI_XIPChipSelectGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPChipSelect feature is supported on the device
    - false  - The XIPChipSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPChipSelect( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPModeBytes( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPModeBytes feature exists on the SQI module

  Description:
    This function identifies whether the XIPModeBytes feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPModeBytesSet
    - PLIB_SQI_XIPModeBytesGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPModeBytes feature is supported on the device
    - false  - The XIPModeBytes feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPModeBytes( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPModeCode( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPModeCode feature exists on the SQI module

  Description:
    This function identifies whether the XIPModeCode feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPModeCodeSet
    - PLIB_SQI_XIPModeCodeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPModeCode feature is supported on the device
    - false  - The XIPModeCode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPModeCode( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsXIPControlWord2( SQI_MODULE_ID index )

  Summary:
    Identifies whether the XIPControlWord2 feature exists on the SQI module

  Description:
    This function identifies whether the XIPControlWord2 feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_XIPControlWord2Set
    - PLIB_SQI_XIPControlWord2Get

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The XIPControlWord2 feature is supported on the device
    - false  - The XIPControlWord2 feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsXIPControlWord2( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsEnableControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the EnableControl feature exists on the SQI module

  Description:
    This function identifies whether the EnableControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_Enable
    - PLIB_SQI_Disable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The EnableControl feature is supported on the device
    - false  - The EnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsEnableControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsCSOutputEnable( SQI_MODULE_ID index )

  Summary:
    Identifies whether the CSOutputEnable feature exists on the SQI module

  Description:
    This function identifies whether the CSOutputEnable feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_CSOutputEnableSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CSOutputEnable feature is supported on the device
    - false  - The CSOutputEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsCSOutputEnable( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDataOutputEnable( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DataOutputEnable feature exists on the SQI module

  Description:
    This function identifies whether the DataOutputEnable feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DataOutputEnableSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataOutputEnable feature is supported on the device
    - false  - The DataOutputEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDataOutputEnable( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsSoftReset( SQI_MODULE_ID index )

  Summary:
    Identifies whether the SoftReset feature exists on the SQI module

  Description:
    This function identifies whether the SoftReset feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_SoftReset

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SoftReset feature is supported on the device
    - false  - The SoftReset feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsSoftReset( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBurstControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BurstControl feature exists on the SQI module

  Description:
    This function identifies whether the BurstControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_BurstEnable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BurstControl feature is supported on the device
    - false  - The BurstControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBurstControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsHoldPinControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the HoldPinControl feature exists on the SQI module

  Description:
    This function identifies whether the HoldPinControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_HoldSet
    - PLIB_SQI_HoldClear
    - PLIB_SQI_HoldGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The HoldPinControl feature is supported on the device
    - false  - The HoldPinControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsHoldPinControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsWPPinControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the WPPinControl feature exists on the SQI module

  Description:
    This function identifies whether the WPPinControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_WriteProtectSet
    - PLIB_SQI_WriteProtectClear
    - PLIB_SQI_WriteProtectGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WPPinControl feature is supported on the device
    - false  - The WPPinControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsWPPinControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsReceiveLatch( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ReceiveLatch feature exists on the SQI module

  Description:
    This function identifies whether the ReceiveLatch feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ReceiveLatchEnable
    - PLIB_SQI_ReceiveLatchDisable
    - PLIB_SQI_ReceiveLatchGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ReceiveLatch feature is supported on the device
    - false  - The ReceiveLatch feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsReceiveLatch( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDataFormat( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DataFormat feature exists on the SQI module

  Description:
    This function identifies whether the DataFormat feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DataFormatSet
    - PLIB_SQI_DataFormatGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataFormat feature is supported on the device
    - false  - The DataFormat feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDataFormat( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDataModeControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DataModeControl feature exists on the SQI module

  Description:
    This function identifies whether the DataModeControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DataModeSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataModeControl feature is supported on the device
    - false  - The DataModeControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDataModeControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTransferModeControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TransferModeControl feature exists on the SQI module

  Description:
    This function identifies whether the TransferModeControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TransferModeSet
    - PLIB_SQI_TransferModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TransferModeControl feature is supported on the device
    - false  - The TransferModeControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTransferModeControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsConfigWord( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ConfigWord feature exists on the SQI module

  Description:
    This function identifies whether the ConfigWord feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ConfigWordSet
    - PLIB_SQI_ConfigWordGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ConfigWord feature is supported on the device
    - false  - The ConfigWord feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsConfigWord( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsCSDeassert( SQI_MODULE_ID index )

  Summary:
    Identifies whether the CSDeassert feature exists on the SQI module

  Description:
    This function identifies whether the CSDeassert feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ChipSelectDeassertEnable
    - PLIB_SQI_ChipSelectDeassertDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CSDeassert feature is supported on the device
    - false  - The CSDeassert feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsCSDeassert( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsChipSelect( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ChipSelect feature exists on the SQI module

  Description:
    This function identifies whether the ChipSelect feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ChipSelectSet
    - PLIB_SQI_ChipSelectGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChipSelect feature is supported on the device
    - false  - The ChipSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsChipSelect( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsLaneMode( SQI_MODULE_ID index )

  Summary:
    Identifies whether the LaneMode feature exists on the SQI module

  Description:
    This function identifies whether the LaneMode feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_LaneModeSet
    - PLIB_SQI_LaneModeGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LaneMode feature is supported on the device
    - false  - The LaneMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsLaneMode( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTransferCommand( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TransferCommand feature exists on the SQI module

  Description:
    This function identifies whether the TransferCommand feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TransferDirectionSet
    - PLIB_SQI_TransferDirectionGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TransferCommand feature is supported on the device
    - false  - The TransferCommand feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTransferCommand( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTransferCount( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TransferCount feature exists on the SQI module

  Description:
    This function identifies whether the TransferCount feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ByteCountSet
    - PLIB_SQI_ByteCountGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TransferCount feature is supported on the device
    - false  - The TransferCount feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTransferCount( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsControlWord( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ControlWord feature exists on the SQI module

  Description:
    This function identifies whether the ControlWord feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ControlWordSet
    - PLIB_SQI_ControlWordGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ControlWord feature is supported on the device
    - false  - The ControlWord feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsControlWord( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsClockDivider( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ClockDivider feature exists on the SQI module

  Description:
    This function identifies whether the ClockDivider feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ClockDividerSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ClockDivider feature is supported on the device
    - false  - The ClockDivider feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsClockDivider( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsClockReady( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ClockReady feature exists on the SQI module

  Description:
    This function identifies whether the ClockReady feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ClockIsStable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ClockReady feature is supported on the device
    - false  - The ClockReady feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsClockReady( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsClockControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ClockControl feature exists on the SQI module

  Description:
    This function identifies whether the ClockControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ClockEnable
    - PLIB_SQI_ClockDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ClockControl feature is supported on the device
    - false  - The ClockControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsClockControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsRxBufThreshold( SQI_MODULE_ID index )

  Summary:
    Identifies whether the RxBufThreshold feature exists on the SQI module

  Description:
    This function identifies whether the RxBufThreshold feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_RxBufferThresholdSet
    - PLIB_SQI_RxBufferThresholdGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RxBufThreshold feature is supported on the device
    - false  - The RxBufThreshold feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsRxBufThreshold( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTxBufThreshold( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TxBufThreshold feature exists on the SQI module

  Description:
    This function identifies whether the TxBufThreshold feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TxBufferThresholdSet
    - PLIB_SQI_TxBufferThresholdGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TxBufThreshold feature is supported on the device
    - false  - The TxBufThreshold feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTxBufThreshold( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsRxBufIntThreshold( SQI_MODULE_ID index )

  Summary:
    Identifies whether the RxBufIntThreshold feature exists on the SQI module

  Description:
    This function identifies whether the RxBufIntThreshold feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_RxBufferThresholdIntSet
    - PLIB_SQI_RxBufferThresholdIntGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RxBufIntThreshold feature is supported on the device
    - false  - The RxBufIntThreshold feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsRxBufIntThreshold( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTxBufIntThreshold( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TxBufIntThreshold feature exists on the SQI module

  Description:
    This function identifies whether the TxBufIntThreshold feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TxBufferThresholdIntSet
    - PLIB_SQI_TxBufferThresholdIntGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TxBufIntThreshold feature is supported on the device
    - false  - The TxBufIntThreshold feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTxBufIntThreshold( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsInterruptControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the InterruptControl feature exists on the SQI module

  Description:
    This function identifies whether the InterruptControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_InterruptEnable
    - PLIB_SQI_InterruptDisable
    - PLIB_SQI_InterruptIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InterruptControl feature is supported on the device
    - false  - The InterruptControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsInterruptControl( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsInterruptStatus( SQI_MODULE_ID index )

  Summary:
    Identifies whether the InterruptStatus feature exists on the SQI module

  Description:
    This function identifies whether the InterruptStatus feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_InterruptFlagGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InterruptStatus feature is supported on the device
    - false  - The InterruptStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsInterruptStatus( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTxData( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TxData feature exists on the SQI module

  Description:
    This function identifies whether the TxData feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TransmitData

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TxData feature is supported on the device
    - false  - The TxData feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTxData( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsRxData( SQI_MODULE_ID index )

  Summary:
    Identifies whether the RxData feature exists on the SQI module

  Description:
    This function identifies whether the RxData feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ReceiveData

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RxData feature is supported on the device
    - false  - The RxData feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsRxData( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTxBufferFree( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TxBufferFree feature exists on the SQI module

  Description:
    This function identifies whether the TxBufferFree feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TransmitBufferFreeSpaceGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TxBufferFree feature is supported on the device
    - false  - The TxBufferFree feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTxBufferFree( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsRxBufferCount( SQI_MODULE_ID index )

  Summary:
    Identifies whether the RxBufferCount feature exists on the SQI module

  Description:
    This function identifies whether the RxBufferCount feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_NumberOfReceiveBufferReads

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RxBufferCount feature is supported on the device
    - false  - The RxBufferCount feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsRxBufferCount( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDataPinStatus( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DataPinStatus feature exists on the SQI module

  Description:
    This function identifies whether the DataPinStatus feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DataLineStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DataPinStatus feature is supported on the device
    - false  - The DataPinStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDataPinStatus( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsRxUnderRun( SQI_MODULE_ID index )

  Summary:
    Identifies whether the RxUnderRun feature exists on the SQI module

  Description:
    This function identifies whether the RxUnderRun feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ReceiveBufferIsUnderrun

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RxUnderRun feature is supported on the device
    - false  - The RxUnderRun feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsRxUnderRun( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsTxOverFlow( SQI_MODULE_ID index )

  Summary:
    Identifies whether the TxOverFlow feature exists on the SQI module

  Description:
    This function identifies whether the TxOverFlow feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_TransmitBufferHasOverflowed

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TxOverFlow feature is supported on the device
    - false  - The TxOverFlow feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsTxOverFlow( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDmaEnable( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DMAEnable feature exists on the SQI module

  Description:
    This function identifies whether the DMAEnable feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMAEnable
    - PLIB_SQI_DMADisable
    - PLIB_SQI_DMAIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DMAEnable feature is supported on the device
    - false  - The DMAEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDmaEnable( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDPollingEnable( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDPollingEnable feature exists on the SQI module

  Description:
    This function identifies whether the BDPollingEnable feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDPollEnable
    - PLIB_SQI_DMABDPollDisable
    - PLIB_SQI_DMABDPollIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDPollingEnable feature is supported on the device
    - false  - The BDPollingEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDPollingEnable( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsStartDMA( SQI_MODULE_ID index )

  Summary:
    Identifies whether the StartDMA feature exists on the SQI module

  Description:
    This function identifies whether the StartDMA feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDFetchStart

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The StartDMA feature is supported on the device
    - false  - The StartDMA feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsStartDMA( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDCurrentAddress( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDCurrentAddress feature exists on the SQI module

  Description:
    This function identifies whether the BDCurrentAddress feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDCurrentAddressGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDCurrentAddress feature is supported on the device
    - false  - The BDCurrentAddress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDCurrentAddress( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDBaseAddress( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDBaseAddress feature exists on the SQI module

  Description:
    This function identifies whether the BDBaseAddress feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDBaseAddressSet
    - PLIB_SQI_DMABDBaseAddressGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDBaseAddress feature is supported on the device
    - false  - The BDBaseAddress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDBaseAddress( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDProcessState( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDProcessState feature exists on the SQI module

  Description:
    This function identifies whether the BDProcessState feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDStateGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDProcessState feature is supported on the device
    - false  - The BDProcessState feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDProcessState( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDMAProcessInProgress( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DMAProcessInProgress feature exists on the SQI module

  Description:
    This function identifies whether the DMAProcessInProgress feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMAHasStarted

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DMAProcessInProgress feature is supported on the device
    - false  - The DMAProcessInProgress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDMAProcessInProgress( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsDMAEngineBusy( SQI_MODULE_ID index )

  Summary:
    Identifies whether the DMAEngineBusy feature exists on the SQI module

  Description:
    This function identifies whether the DMAEngineBusy feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDIsBusy

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DMAEngineBusy feature is supported on the device
    - false  - The DMAEngineBusy feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsDMAEngineBusy( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDControlWord( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDControlWord feature exists on the SQI module

  Description:
    This function identifies whether the BDControlWord feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDControlWordGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDControlWord feature is supported on the device
    - false  - The BDControlWord feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDControlWord( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDPollCount( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDPollCount feature exists on the SQI module

  Description:
    This function identifies whether the BDPollCount feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDPollCounterSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDPollCount feature is supported on the device
    - false  - The BDPollCount feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDPollCount( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDTxState( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDTxState feature exists on the SQI module

  Description:
    This function identifies whether the BDTxState feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDTransmitStateGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDTxState feature is supported on the device
    - false  - The BDTxState feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDTxState( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDTxBufCount( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDTxBufCount feature exists on the SQI module

  Description:
    This function identifies whether the BDTxBufCount feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDTransmitBufferCountGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDTxBufCount feature is supported on the device
    - false  - The BDTxBufCount feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDTxBufCount( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDTxLength( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDTxLength feature exists on the SQI module

  Description:
    This function identifies whether the BDTxLength feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDTransmitBufferLengthGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDTxLength feature is supported on the device
    - false  - The BDTxLength feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDTxLength( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDRxState( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDRxState feature exists on the SQI module

  Description:
    This function identifies whether the BDRxState feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDReceiveStateGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDRxState feature is supported on the device
    - false  - The BDRxState feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDRxState( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDRxBufCount( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDRxBufCount feature exists on the SQI module

  Description:
    This function identifies whether the BDRxBufCount feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDReceiveBufferCountGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDRxBufCount feature is supported on the device
    - false  - The BDRxBufCount feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDRxBufCount( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsBDRxLength( SQI_MODULE_ID index )

  Summary:
    Identifies whether the BDRxLength feature exists on the SQI module

  Description:
    This function identifies whether the BDRxLength feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_DMABDReceiveBufferLengthGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BDRxLength feature is supported on the device
    - false  - The BDRxLength feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsBDRxLength( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsConBufThreshold( SQI_MODULE_ID index )

  Summary:
    Identifies whether the ConBufThreshold feature exists on the SQI module

  Description:
    This function identifies whether the ConBufThreshold feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_ControlBufferThresholdSet
    - PLIB_SQI_ControlBufferThresholdGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ConBufThreshold feature is supported on the device
    - false  - The ConBufThreshold feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsConBufThreshold( SQI_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_SQI_ExistsInterruptSignalControl( SQI_MODULE_ID index )

  Summary:
    Identifies whether the InterruptSignalControl feature exists on the SQI module

  Description:
    This function identifies whether the InterruptSignalControl feature is available on the SQI module.
    When this function returns true, these functions are supported on the device:
    - PLIB_SQI_InterruptSignalEnable
    - PLIB_SQI_InterruptSignalDisable
    - PLIB_SQI_InterruptSignalIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The InterruptSignalControl feature is supported on the device
    - false  - The InterruptSignalControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_SQI_ExistsInterruptSignalControl( SQI_MODULE_ID index );


#endif // #ifndef _PLIB_SQI_H
/*******************************************************************************
 End of File
 */
