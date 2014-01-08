/******************************************************************************
 *    SSD1926 hardware SD card driver
 ******************************************************************************
 * File Name:       SSD1926_SDCard.c
 * Dependencies:    see included files below
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:        C30 v2.01/C32 v0.00.18
 * Company:         Microchip Technology, Inc.
 * Software License Agreement
 *
 * Copyright � 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 
Author                 Date           Comments
--------------------------------------------------------------------------------
Sean Justice        15_Sept-2008      First release
Anton Alkhimenok    06_Jun-2009       Ported to PIC24
*******************************************************************************/
#include "app.h"
//#include "driver/gfx_ssd1926/drv_gfx_ssd1926.h"
#include "driver/gfx/gfx_ssd1926/drv_gfx_ssd1926.h"

/******************************************************************************
 * Global Variables
 *****************************************************************************/
uint32_t               finalLBA;
uint16_t                sectorSize;
uint32_t               maxBusClock;
uint8_t 	            hcMode;
MEDIA_INFORMATION   mediaInformation;

/******************************************************************************
 * Local Prototypes
 *****************************************************************************/
uint8_t                SDInit(void);
uint8_t                SDSetClock(uint32_t);
uint8_t                SDSendCommand(uint8_t cmd_idx, uint8_t flags, uint32_t arg);
uint8_t                SDSendAppCommand(uint8_t cmd_idx, uint8_t flags, uint32_t arg1, uint32_t arg2);
bool                   SDReset(uint8_t type);

/******************************************************************************
 * Helper Macros
 *****************************************************************************/
#define SetDataPortReg0(data)   GFX_DRV_SSD1926_SetReg(0x1120, data)
#define SetTransferMode(mode)   GFX_DRV_SSD1926_SetReg(0x110C, mode)

/******************************************************************************
 * Helper Functions
 *****************************************************************************/

bool SetCommandArgument(uint32_t arg)
{
    static uint8_t state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    if(GFX_DRV_SSD1926_SetReg(0x110B, arg>>24) == 1)
        return( false );
    break;
            case 1:
    if(GFX_DRV_SSD1926_SetReg(0x110A, arg>>16) == 1)
        return( false );
    break;
            case 2:
    if(GFX_DRV_SSD1926_SetReg(0x1109, arg>>8) == 1)
        return( false );
    break;
            case 3:
    if(GFX_DRV_SSD1926_SetReg(0x1108, arg) == 1)
        return( false );
    state = 0;
    return( true );
        }
        state++;
    }
}

/* */
bool SetCommand(uint8_t idx, uint8_t flags)
{
    static uint8_t state = 0;

    while(1)
    {
    switch(state)
    {
        case 0:
    if(GFX_DRV_SSD1926_SetReg(0x110E, flags) == 1)  //set response type
        return( false );
    break;
        case 1:
    if(GFX_DRV_SSD1926_SetReg(0x110F, idx) == 1)
        return( false );
    state = 0;
    return( true );
    }
    state++;
    }

}

/* */
bool GetCommandResponse(uint8_t idx, uint32_t *rsp)
{

    static uint8_t    *point;
    static uint8_t    state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
            idx <<= 2;
            point = (uint8_t*) rsp;
    if(GFX_DRV_SSD1926_GetReg(0x1110 + idx, &point[0]) == 1)
        return( false );
    break;
            case 1:
    if(GFX_DRV_SSD1926_GetReg(0x1111 + idx, &point[1]) == 1)
        return( false );
    break;
            case 2:
    if(GFX_DRV_SSD1926_GetReg(0x1112 + idx, &point[2]) == 1)
        return( false );
    break;
            case 3:
    if(GFX_DRV_SSD1926_GetReg(0x1113 + idx, &point[3]) == 1)
        return( false );

    state = 0;
    return ( true );
        }
        state++;
    }
}

/* */
bool ReadCmdResponse(uint32_t *rsp, uint16_t size)
{
    static uint32_t   idx = 0;

    while(idx < size)
    {
        if(GetCommandResponse(idx, rsp) == false)
            return( false );
        rsp++;
        idx++;
    }

    idx = 0;
    return( true );
}

/******************************************************************************
 * Function:
 *  uint8_t SDSetClock(DWORD clockMax)
 * PreCondition:
 *  None.
 * Input:           
 *  clockMax - SD card maximum frequency,
 * Output:
 *  returns non-zero if the operation is successfull.
 * Side Effects:
 *  None.
 * Overview:
 *  Sets the SD card clock frequency close to clockMax
 * Note:
 *  None
 *****************************************************************************/
uint8_t SDSetClock(uint32_t clockMax)
{
    static uint32_t   mclk;
    static uint8_t    reg;
    static uint8_t    div;
    static uint8_t    data;
    static uint8_t    state = 0;

    while(1)
    {
        switch(state)
        {
        case 0:
    if(GFX_DRV_SSD1926_GetReg(SSD_REG_PLL_CONFIG1, &data) == 1)
        return(0xff);

    mclk = SSD_SYS_CLOCK * data;
    break;
    case 1:
    if(GFX_DRV_SSD1926_GetReg(SSD_REG_PLL_CONFIG0, &data) == 1)
        return(0xff);

    mclk /= (data & 0x1F);
    break;
    case 2:
    if(GFX_DRV_SSD1926_GetReg(SSD_REG_MCLK_CONIG, &data) == 1)
        return(0xff);
    
    mclk /= ((data & 0x1F) + 1);
    break;
    case 3:
    if(GFX_DRV_SSD1926_GetReg(SSD_REG_MCLK_CONIG, &data) == 1)
        return(0xff);

    if(data & 0x01)
        mclk /= 2;
    break;
    case 4:
    if(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_CLK_CNTL, &reg) == 1)
        return(0xff);

    reg = reg &~((uint8_t) SSD_SD_CLK_ENABLE);
    break;
    case 5:
    if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_CLK_CNTL, reg) == 1)
        return(0xff);

    reg |= SSD_SD_INT_CLK_ENABLE;
    break;
    case 6:
    if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_CLK_CNTL, reg) == 1)
        return(0xff);

    SYS_TMR_DelayMS(1);
    break;
    case 7:
    if(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_CLK_CNTL, &data) == 1)
        return(0xff);
    
    if(!(data & SSD_SD_INT_CLK_STABLE))
        return (0);

    div = 0;
    while(mclk > clockMax)
    {
        mclk >>= 1;
        div++;
    }

    div = 1 << (div - 1);
    break;
    case 8:
    if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_CLK_DIV, div) == 1)
        return(0xff);

    reg |= SSD_SD_CLK_ENABLE;
    break;
    case 9:
    if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_CLK_CNTL, reg) == 1)
        return(0xff);
    state = 0;
    return (1);
    }
    state++;
}
}

/******************************************************************************
 * Function:
 *  BYTE SDSendCommand(BYTE cmd_idx, BYTE flags, DWORD arg)
 * PreCondition:
 *  None. 
 * Input:
 *  cmd_idx - command start index,
 *  flags - command flags,
 *  arg - command arguments. 
 * Output:
 *  Returns non-zero if the operation is successful
 * Side Effects:
 *  None.
 * Overview:
 *  Send SD card command.
 * Note:
 *  None.
 *****************************************************************************/
uint8_t SDSendCommand(uint8_t cmd_idx, uint8_t flags, uint32_t arg)
{
    static uint8_t    data = 0xff;
    static uint32_t   timeout;
    static uint8_t    state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    if(GFX_DRV_SSD1926_SetReg(0x112E, 0x0E) == 1)   // Data Timeout Counter Value = MCLK x 2^27
        return( 0xff );
    break;
    //CheckCommandInhibit(data);
    do
    {
        case 1:
        if(GFX_DRV_SSD1926_GetReg(0x1124, &data) == 1)
            return(0xff);
    }while((data & 0x01));
    break;
            case 2:
    // Clear interrupt flags
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0xff) == 1)
        return( 0xff );
    break;
            case 3:
    if(GFX_DRV_SSD1926_GetReg(0x1134, &data) == 1)
        return( 0xff );
    break;
            case 4:
    // Enable command complete interrupt
    if(GFX_DRV_SSD1926_SetReg(0x1134, data | 0x01) == 1)
        return( 0xff );
    break;
            case 5:
    // Clear error interrupt flags
    if(GFX_DRV_SSD1926_SetReg(0x1132, 0xff) == 1)
        return( 0xff );
    break;
            case 6:
    if(GFX_DRV_SSD1926_SetReg(0x1133, 0xff) == 1)
        return( 0xff );
    break;
            case 7:
    // Enable all interrupts
    if(GFX_DRV_SSD1926_SetReg(0x1136, 0xff) == 1)
        return( 0xff);
    break;
            case 8:
    if(GFX_DRV_SSD1926_SetReg(0x1137, 0xff) == 1)
        return( 0xff );
    break;
            case 9:
                
    if(SetCommandArgument(arg) == false)
        return( 0xff );
    break;
            case 10:
    if(SetCommand(cmd_idx, flags) == false)
        return( 0xff );

    timeout = SD_TIMEOUT;
    break;
    
    while(1)
    {
        case 11:
        if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
            return( 0xff );

        if(data & 0x01)
        {
            state = 0;
            return (true);
        }

        if(!timeout--)
        {
            return (false);
        }
    }

    }
    state++;
    }
}

/******************************************************************************
 * Function:
 *  BYTE SDSendAppCommand(BYTE cmd_idx, BYTE flags, DWORD arg1, DWORD arg2)
 * PreCondition:
 *  None. 
 * Input:
 *  cmd_idx - command start index,
 *  flags - command flags,
 *  arg1 - application command arguments 1 
 *  arg2 - application command arguments 2 
 * Output:
 *  Returns non-zero if the operation is successful
 * Side Effects:
 *  None.
 * Overview:
 *  Send SD card application command.
 * Note:
 *  None.
 *****************************************************************************/
uint8_t SDSendAppCommand(uint8_t cmd_idx, uint8_t flags, uint32_t arg1, uint32_t arg2)
{

    static uint8_t value;
    static uint8_t state = 0;

    switch(state)
    {
        case 0:
    if((value = SDSendCommand(CMD_APP_CMD, SSD_RESPONSE_48, arg1)) == 0xff)
        return( 0xff );

    if(value == false)
        return (false);

    state = 1;
    case 1:
    if((value = SDSendCommand(cmd_idx, flags, arg2)) == 0xff)
        return( 0xff );
    state = 0;
    return (value);
      }
}

/******************************************************************************
 * Function:
 *  bool SDReset(uint8_t type)
 * PreCondition:
 *  None.
 * Input:
 *  type - type of reset.
 * Output:
 *  None.
 * Side Effects:
 *  None.
 * Overview:
 *  Resets the SD card module
 * Note:
 *  None.
 *****************************************************************************/
bool SDReset(uint8_t type)
{
    static uint32_t   timeout;
    static uint8_t    data;
    static uint8_t    state = 0;

    while(1)
    {
    switch(state)
    {
        case 0:

    if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_SW_RESET, type) == 1)
        return( false );

    timeout = SD_TIMEOUT;
    break;

    while(timeout--)
    {
        case 1:
        if(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_SW_RESET, &data) == 1)
            return ( false );

        if(!(data & type))
            timeout = 0;
    }
    state = 0;
    return( true );

    }
    state++;
    }
}

/******************************************************************************
 * Function:
 *  void SDPower(BYTE on)
 * PreCondition:
 *  None.
 * Input:
 *  on - '0' means off, '1' means on.
 * Output:
 *  None. 
 * Side Effects:
 *  None.
 * Overview:
 *  Powers on the SD card.
 * Note:
 *  None.
 *****************************************************************************/
bool SDPower(uint8_t on)
{
    if(on)
        if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_PWR_CNTL, 0x0F) == 1)
            return( false );
    else
        if(GFX_DRV_SSD1926_SetReg(SSD_SDCARD_REG_PWR_CNTL, 0x0E) == 1)
            return (false);

        return( true );
}

/******************************************************************************
 * Function:
 *  BYTE SDDetect(void)
 * PreCondition:
 *  None.
 * Input:
 *  None. 
 * Output:
 *  TRUE - card detected,
 *  FALSE - no card detected.
 * Side Effects:
 *  None.
 * Overview:
 *  Detects if the SD card is inserted.
 * Note:
 *  None.
 *****************************************************************************/
uint8_t SDDetect(void)
{
   uint8_t    reg;

    while(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_PRSNT_STATE_2, &reg) == 1);

    if(!(reg & SSD_CARD_DETECT))
        return (false);

    if(reg & SSD_CARD_INSERTED)
    {
        uint32_t   timeout;

        timeout = SD_TIMEOUT;

        while(1)
        {
            if(!timeout--)
                return (false);

            while(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_PRSNT_STATE_2, &reg) == 1);

            if(reg & SSD_CARD_STABLE)
                break;
        }
    }
    else
        return (false);

    return (true);
}

/******************************************************************************
 * Function:
 *  BYTE SDWriteProtectState(void)
 * PreCondition:
 *  None.
 * Input:
 *  None
 * Output:
 *  Returns the status of the "write enabled" pin.
 * Side Effects:
 *  None.
 * Overview:
 *  Determines if the card is write-protected.
 * Note:
 *  None.
 *****************************************************************************/
uint8_t SDWriteProtectState(void)
{
    uint8_t data;

    while(GFX_DRV_SSD1926_GetReg(SSD_SDCARD_REG_PRSNT_STATE_2, &data) == 1);

    return (data & SSD_WRITE_PROTECT);
}

/******************************************************************************
 * Function:
 *  BYTE SDInit(void)
 * PreCondition:
 *  None.
 * Input:
 *  None.
 * Output:
 *  Returns TRUE if media is initialized, FALSE otherwise.
 * Overview:
 *  MediaInitialize initializes the media card and supporting variables.
 * Note:
 *  None.
 *****************************************************************************/
uint8_t SDInit(void)
{
    uint32_t   timeout;
    uint32_t   response;
    uint32_t   voltage;
    uint32_t   CSD_C_SIZE;
    uint32_t   CSD_C_SIZE_MULT;
    uint32_t   CSD_RD_BL_LEN;
    uint32_t   RCA;
    uint32_t   CSD[4];
    uint8_t    value;

    while((value = SDSendCommand(CMD_RESET, SSD_NO_RESPONSE, 0xFFFFFFFF)) == 0xff);

     if(value == false)
        return (false);

     while((value = SDSendCommand(CMD_SEND_IF_COND, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, 0x000001AA)) == 0xff);

     if(value == false)
	return (false);

	while(GetCommandResponse(0, &response) == false);

	if(response == 0x000001AA)
	{
	    voltage = 0x40200000;
		hcMode = 1;
	}else{
	    voltage = 0x00200000;
		hcMode = 0;
	}

	timeout = 10;
    do
    {
        if(!timeout--)
        {
            return (false);
        }

		while(SDReset(SSD_RESET_DATA|SSD_RESET_CMD) == false);
        while((value = SDSendAppCommand(ACMD_SEND_OCR, SSD_RESPONSE_48, 0, voltage)) == 0xff);
        if(value == 0)
                return (false); // ask card send OCR back
		SYS_TMR_DelayMS(150);
		while(GetCommandResponse(0, &response) == false);
    } while((response&0x80000000) == 0);
	
	if((response&0x40000000L) == 0){
		hcMode = 0;
	}

    while((value = SDSendCommand(CMD_SEND_ALL_CID, SSD_RESPONSE_136 | SSD_CMD_CRC_CHK, 0xFFFFFFFF)) == 0xff);

    if(value == false)
        return (false);

    SYS_TMR_DelayMS(150);

    while((value = SDSendCommand(CMD_SEND_RCA, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, 0xFFFFFFFF)) == 0xff);

    if(value == false)
        return (false);

    while(GetCommandResponse(0, &RCA) == false);
    RCA |= 0x0000ffff;

    //CMD9 - Request CSD from SD Card
    while((value = SDSendCommand(CMD_SEND_CSD, SSD_CMD_IDX_CHK | SSD_CMD_CRC_CHK | SSD_RESPONSE_136, RCA)) == 0xff);

    if(value == false)
        return (false);

    while(ReadCmdResponse(CSD, 4) == false);

    CSD_C_SIZE = ((CSD[2] & 0x00000003) << 10) | ((CSD[1] & 0xFFC00000) >> 22); //CSD Bit[73:62] => Bit[65:54] (Deduct CRC-7 as CRC-7 is not stored in response register)
    CSD_C_SIZE_MULT = ((CSD[1] & 0x00000380) >> 7);                             //CSD Bit[49:47] =? Bit[41:39]
    CSD_RD_BL_LEN = (CSD[2] & 0x00000F00) >> 8; //CSD Bit[83:80] -> Bit[75:72]
    finalLBA = (CSD_C_SIZE + 1) * (1 << (CSD_C_SIZE_MULT + 2));
    sectorSize = (1 << CSD_RD_BL_LEN);
    if((CSD[3] & 0x000000FF) == 0x32)
        maxBusClock = 25000000;                 // 25MHz
    else
        maxBusClock = 25000000;                 // 50MHz
    while(SDReset(SSD_RESET_CMD) == false);

    //CMD7 Select Card
    while((value = SDSendCommand(CMD_SELECT_CARD, SSD_RESPONSE_48_BUSY | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, RCA)) == 0xff);

    if(value == false)
        return (false);

	sectorSize = 512L;	

    //CMD16 Set the block size.
    while((value = SDSendCommand(CMD_SET_BLKLEN, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, sectorSize)) == 0xff);

    if(value == false)
        return (false);

    //CMD55 + ACMD6 Set bus width = 4 Bit
    while((value = SDSendAppCommand(ACMD_SET_BUS_WIDTH, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, RCA, 0xFFFFFFFE)) == 0xff);
        if(value == false)
            return (false);

    //Data width 4bits
    while(GFX_DRV_SSD1926_SetReg(0x1128, 0x02) == 1);

    return (true);
}

/******************************************************************************
 * Function:        
 *  INT32 SDGetStatus(void)
 * PreCondition:    
 *  None.
 * Input:           
 *  None.
 * Output:          
 *  SD card status.                
 * Side Effects:    
 *  None.
 * Overview:        
 *  Returns SD card status. If the returned value is -1 the there's an error.
 * Note:
 *  None.
 *****************************************************************************/
int32_t SDGetStatus(void)
{
    uint32_t   status;
    uint32_t   RCA;
    uint8_t data = 0xff;
    uint8_t data1 = 0xff;
    uint8_t value;

    while(SDReset(SSD_RESET_CMD) == false);

    while(GFX_DRV_SSD1926_GetReg(0x1134, &data) == 1);

    //Normal interrupt handling
    while(GFX_DRV_SSD1926_SetReg(0x1134, data | 0x01) == 1);  //enable read interrupt
    while(GFX_DRV_SSD1926_SetReg(0x1130, 0x01) == 1);                   //clear previous interrupt

    while(GFX_DRV_SSD1926_GetReg(0x1136, &data) == 1);

    //Error interrupt handling
    while(GFX_DRV_SSD1926_SetReg(0x1136, data | 0x8F) == 1);  //enable error interrupt

    while(GFX_DRV_SSD1926_GetReg(0x1137, &data) == 1);

    while(GFX_DRV_SSD1926_SetReg(0x1137, data | 0x71) == 1);  //enable error interrupt
    while(GFX_DRV_SSD1926_SetReg(0x1132, 0x8F) == 1);                   //enable error interrupt
    while(GFX_DRV_SSD1926_SetReg(0x1133, 0x71) == 1);                   //enable error interrupt
    while((value = SDSendCommand(CMD_SEND_RCA, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, 0xFFFFFFFF)) == 0xff);

    if(value == false)
        return (uint32_t) (-1);

    while(GetCommandResponse(0, &RCA) == false);
    RCA |= 0x0000ffff;

    while((value = SDSendCommand(CMD_SEND_STATUS, SSD_RESPONSE_48 | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK, RCA)) == 0xff);

    if(value == false)
        return (uint32_t) (-1);

    do
    {
        while(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1);
    } while(!(data & 0x01));

    //check cmd complt int
    while(GFX_DRV_SSD1926_SetReg(0x1130, 0x01) == 1);                   //clear previous int

    do
    {
        while(GFX_DRV_SSD1926_GetReg(0x1132, &data) == 1);
        while(GFX_DRV_SSD1926_GetReg(0x1133, &data1) == 1);
    }while((data & 0x8F) || (data1 & 0x71));

    while(GFX_DRV_SSD1926_SetReg(0x1132, 0x8F) == 1);                   //enable error interrupt
    while(GFX_DRV_SSD1926_SetReg(0x1133, 0x71) == 1);                   //enable error interrupt

    while(ReadCmdResponse(&status, 1) == false);

    return (status);
}

/******************************************************************************
 * Function:
 *  MEDIA_INFORMATION* SDInitialize(void)
 * PreCondition:
 *  None.
 * Input:
 *  None.
 * Output:
 *  Returns a pointer to the media inforamtion structure.
 * Overview:
 *  SDInitialize initializes the media card and supporting variables.
 *  Sets maximum clock frequency for the SD card.
 * Note:
 *  None.
 *****************************************************************************/
MEDIA_INFORMATION *SDInitialize(void)
{
    static uint32_t   timeout;
    static uint8_t    value;
    static uint8_t    state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    if(SDReset(SSD_RESET_DATA | SSD_RESET_CMD | SSD_RESET_ALL) == false)
        return( NULL );
    break;
            case 1:
    if(SDPower(true) == false)
        return( NULL );

    mediaInformation.errorCode = MEDIA_NO_ERROR;
    mediaInformation.validityFlags.value = 0;
    break;

            case 2:
    if((value = SDSetClock(SSD_SD_CLK_INIT)) == 0xff)
        return( NULL );

    if(value == 0)
    {
        mediaInformation.errorCode = MEDIA_DEVICE_NOT_PRESENT;
        return (&mediaInformation);
    }

    timeout = 10;
    value = false;

    while(value != true)
    { 
        state = 3;
      case 3:
        if((value = SDInit()) == 0xff)
            return ( NULL );

        if(!timeout--)
        {
            state = 0;
            mediaInformation.errorCode = MEDIA_DEVICE_NOT_PRESENT;
            return (&mediaInformation);
        }
    }

    mediaInformation.validityFlags.bits.sectorSize = 1;
    mediaInformation.sectorSize = sectorSize;
    break;
    case 4:
    if((value = SDSetClock(maxBusClock>>1)) == 0xff)
        return( NULL );

    if(value == 0)
        mediaInformation.errorCode = MEDIA_DEVICE_NOT_PRESENT;

    state = 0;
    return (&mediaInformation);
    }
    state++;
    }
}

/******************************************************************************
 * Function:        BYTE SDSectorRead(DWORD sector_addr, BYTE *buffer)
 *
 * PreCondition:    None
 *
 * Input:           sector_addr - Sector address
 *                  buffer      - Buffer where data will be stored, see
 *                                'ram_acs.h' for 'block' definition.
 *                                'Block' is dependent on whether internal or
 *                                external memory is used
 *
 * Output:          Returns TRUE if read successful, false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        SectorRead reads data from the card starting
 *                  at the sector address specified by sector_addr and stores
 *                  them in the location pointed to by 'buffer'.
 *
 * Note:            The device expects the address field in the command packet
 *                  to be byte address. Therefore the sector_addr must first
 *                  be converted to byte address.
 *****************************************************************************/
uint8_t SDSectorRead(uint32_t sector_addr, uint8_t *buffer)
{

    static uint8_t data;
    static uint8_t value;
    static uint16_t    counter = 0;
    static uint8_t state = 0;
    static uint8_t *pointer;
    
    while(1)
    {
        switch(state)
        {
            case 0:
                pointer = buffer;
                counter = 0;
  do
    {
      state = 1;
      case 1:
        if(GFX_DRV_SSD1926_GetReg(0x1124, &data) == 1)
            return( 0xff );
    }while(data & 0x02);
    state = 2;
    case 2:
    if(SDReset(SSD_RESET_DATA) == false)
        return( 0xff );
    state = 3;
            case 3:
    if(SetTransferMode(0x10) == 1)
        return( 0xff );
    state = 4;
            case 4:
    // Block size is one sector
    if(GFX_DRV_SSD1926_SetReg(0x1104, sectorSize) == 1)   // write block size
        return( 0xff );
    state = 5;
            case 5:
    if(GFX_DRV_SSD1926_SetReg(0x1105, sectorSize>>8) == 1)   // write block size
    return( 0xff );
    state = 6;
            case 6:
    //Clear error interrupt flags
    if(GFX_DRV_SSD1926_SetReg(0x1136, 0xff) == 1)
        return( 0xff );
    state = 7;
            case 7:
    if(GFX_DRV_SSD1926_SetReg(0x1137, 0xff) == 1)
        return( 0xff );
    state = 8;
            case 8:
    if(GFX_DRV_SSD1926_SetReg(0x1132, 0xff) == 1)
        return( 0xff );
    state = 9;
            case 9:
    if(GFX_DRV_SSD1926_SetReg(0x1133, 0xff) == 1)
        return( 0xff );
    state = 10;
            case 10:
    // Buffer Read Ready, Transfer Complete, Command Complete interrupts enable
    if(GFX_DRV_SSD1926_SetReg(0x1134, 0x23) == 1)
        return( 0xff );
    state = 11;
            case 11:
    // Clear previous interrupt flags
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x23) == 1)
        return( 0xff);
    state = 12;
            case 12:
    // Send command
    if(!hcMode)
    {
        sector_addr *= sectorSize;
    }

    if
    (
        (value = SDSendCommand
            (
                CMD_RD_SINGLE,
                SSD_RESPONSE_48 | SSD_DATA_PRESENT | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK,
                sector_addr
            )) == 0xff
    )return( 0xff);

    if(value == false)
        return (false);

    // Wait for transfer complete
    do
    {
        state = 13;
        case 13:
        if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
            return( 0xff );
    } while(!(data & 0x20));
    state = 14;
            case 14:
    // Clear transfer complete flag
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x20) == 1)
        return( 0xff );
    state = 15;
            case 15:
    if(GFX_DRV_SSD1926_GetReg(0x1125, &data) == 1)
    return( 0xff );

    while(data & 0x08)
    {
        state = 16;
        if(counter < sectorSize)
        {
            case 16:
            if(GFX_DRV_SSD1926_GetReg(0x1120, pointer) == 1)
                return( 0xff );
            pointer++;
        }
        state = 17;
        case 17:
        if(GFX_DRV_SSD1926_GetReg(0x1125, &data) == 1)
            return( 0xff );
        counter++;
    }

    state = 0;

    if(counter > sectorSize)
        return (false);

    return (true);
        }
        state++;
    }
}

/******************************************************************************
 * Function:
 *  uint8_t SDSectorDMARead(DWORD sector_addr,  DWORD dma_addr, UINT16 num_blk)
 * PreCondition:
 *  None.
 * Input:
 *  sector_addr - Sector address
 *  buffer      - Buffer where data will be stored, see
 *                'ram_acs.h' for 'block' definition.
 *                'Block' is dependent on whether internal or
 *                external memory is used
 *
 * Output:
 *  Returns TRUE if read successful, false otherwise.
 * Side Effects:
 *  None.
 * Overview:        SectorRead reads data from the card starting
 *                  at the sector address specified by sector_addr and stores
 *                  them in the location pointed to by 'buffer'.
 *
 * Note:            The device expects the address field in the command packet
 *                  to be byte address. Therefore the sector_addr must first
 *                  be converted to byte address.
 *****************************************************************************/
uint8_t SDSectorDMARead(uint32_t sector_addr, uint32_t dma_addr, uint16_t num_blk)
{
    static uint32_t   dma_size;
    static uint8_t    boundary;
    static uint8_t    data = 0xff;
    static uint8_t    data1 = 0xff;
    static uint8_t    state = 0;
    static uint8_t    value;

    while(1)
    {
    switch(state)
    {

        case 0:
	if(!hcMode)
	{
		sector_addr *= sectorSize;
	}

    do
    {
        state = 1;
        case 1:
         if(GFX_DRV_SSD1926_GetReg(0x1124, &data) == 1)
             return( 0xff );
    }while(data & 0x02);
        
    break;
    case 2:
    if(SDReset(SSD_RESET_DATA) == false)
        return( 0xff );
    break;
        case 3:
    // set up the DMA address
    if(GFX_DRV_SSD1926_SetReg(0x1100, dma_addr) == 1)
        return( 0xff );
    break;
        case 4:
    if(GFX_DRV_SSD1926_SetReg(0x1101, dma_addr>>8) == 1)
        return( 0xff );
    break;
        case 5:
    if(GFX_DRV_SSD1926_SetReg(0x1102, dma_addr>>16) == 1)
        return( 0xff );
    break;
        case 6:
    if(GFX_DRV_SSD1926_SetReg(0x1103, dma_addr>>24) == 1)
        return( 0xff );
    break;
        case 7:
    // set up the transefer mode (Multi-Blk, Read, Blk Cnt, DMA)
    if(SetTransferMode(0x33) == 1)
       return( 0xff );

    // set up the DMA buffer size (4k) and sector block size
    dma_size = (uint32_t) num_blk * sectorSize;

    dma_size >>= 12;
    boundary = 0;
    while(dma_size)
    {
        dma_size >>= 1;
        boundary++;
    }

    boundary <<= 4;
    boundary |= (sectorSize>>8) & 0x0F;
    break;
        case 8:
    if(GFX_DRV_SSD1926_SetReg(0x1104, sectorSize) == 1)   // write block size
        return( 0xff );
    break;
        case 9:
    if(GFX_DRV_SSD1926_SetReg(0x1105, boundary) == 1)                       // write block size
        return( 0xff );
    break;
        case 10:
    // Set the number of blocks to read
    if(GFX_DRV_SSD1926_SetReg(0x1106, (uint8_t) (num_blk & 0xFF)) == 1)        // write block size
        return( 0xff );
    break;
        case 11:
    if(GFX_DRV_SSD1926_SetReg(0x1107, (uint8_t) (num_blk >> 8)) == 1)          // write block size
        return( 0xff );
    break;
        case 12:
    // set up the normal status register 0
    if(GFX_DRV_SSD1926_SetReg(0x1134, 0x0B) == 1)                           // enable read interrupt
        return( 0xff );
    break;
        case 13:
    if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
        return( 0xff );
    break;
        case 14:
    if(GFX_DRV_SSD1926_SetReg(0x1130, data | 0x0B) == 1)          // clear previous interrupt
        return( 0xff );
    break;
        case 15:
    // set up the error status register
    if(GFX_DRV_SSD1926_SetReg(0x1136, 0xFF) == 1)                           // clear previous interrupt
        return( 0xff );
    break;
        case 16:
    if(GFX_DRV_SSD1926_SetReg(0x1132, 0xFF) == 1)                           // clear previous interrupt
        return( 0xff );
    break;
        case 17:
    if(GFX_DRV_SSD1926_SetReg(0x1133, 0x01) == 1)                           // clear previous interrupt
        return( 0xff );
    break;
        case 18:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x08) == 1)                           // clear previous interrupt
        return( 0xff );
    break;
        case 19:
    // set the command to read multiple blocks
    if
    (
        (value = SDSendCommand
            (
                CMD_RD_MULTIPLE,
                SSD_RESPONSE_48 | SSD_DATA_PRESENT | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK,
                sector_addr
            )) == 0xff) return( 0xff );

    if(value == false)
        return (false);
    break;

    // wait until the dma transfer is done
    do
    {
        state = 20;
        case 20:
        if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
            return( 0xff );
        break;
        case 21:
        if(GFX_DRV_SSD1926_GetReg(0x1125, &data1) == 1)
            return( 0xff );
    } while(!(data & 0x08) && (data1 & 0x02));
    break;
        case 22:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x08) == 1)
        return( 0xff );
    break;
        case 23:

    // stop the transmission
    if
    (
        (value = SDSendCommand
            (
                CMD_STOP_TRANSMISSION,
                SSD_CMD_TYPE_ABORT | SSD_RESPONSE_48_BUSY | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK,
                0xFFFFFFFF
            ))  == 0xff
    ) return( 0xff );

    if(value == false)
        return (false);
    break;
        case 24:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x01) == 1)                           //clear previous interrupt
        return( 0xff );
    break;
        case 25:
    if(GFX_DRV_SSD1926_SetReg(0x1106, 0) == 1)                              // write block size
        return( 0xff );
    break;
        case 26:
    if(GFX_DRV_SSD1926_SetReg(0x1107, 0) == 1)                              // write block size
        return( 0xff );
    break;
        case 27:
    // disable the transfer mode
    if(SetTransferMode(0) == 1)
        return( 0xff );
    state = 0;
    return (true);
    }
    state++; //Update the state machine
    }
 
}

/******************************************************************************
 * Function:        BYTE SDSectorWrite(DWORD sector_addr, BYTE *buffer, BYTE allowWriteToZero)
 *
 * PreCondition:    None
 *
 * Input:           sector_addr - Sector address
 *                  buffer      - Buffer where data will be read
 *                  allowWriteToZero - If true, writes to the MBR will be valid
 *
 * Output:          Returns TRUE if write successful, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        SectorWrite sends data from the location
 *                  pointed to by 'buffer' to the card starting
 *                  at the sector address specified by sector_addr.
 *
 * Note:            The sample device expects the address field in the command packet
 *                  to be byte address. Therefore the sector_addr must first
 *                  be converted to byte address.
 *****************************************************************************/
uint8_t SDSectorWrite(uint32_t sector_addr, uint8_t *buffer, uint8_t allowWriteToZero)
{
    static uint16_t  i;
    static uint8_t data = 0xff;
    static uint8_t data1 = 0xff;
    static uint8_t value;
    static uint8_t state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:

	if(!hcMode)
	{
		sector_addr *= sectorSize;
	}

    do
    {
        state = 1;
        case 1:
        if(GFX_DRV_SSD1926_GetReg(0x1124, &data) == 1)
            return( 0xff );
    }while(data & 0x02);

    break;
            case 2:
    if(SDReset(SSD_RESET_DATA) == false)
        return( 0xff );
    break;
            case 3:
    if(SetTransferMode(0) == 1)
        return( 0xff );
    break;
            case 4:
    if(GFX_DRV_SSD1926_SetReg(0x1104, sectorSize) == 1)   // write block size
        return( 0xff );
    break;
            case 5:
    if(GFX_DRV_SSD1926_SetReg(0x1105, sectorSize>>8) == 1)   // write block size
        return( 0xff );
    break;
            case 6:
    //Clear error interrupt flags
    if(GFX_DRV_SSD1926_SetReg(0x1136, 0xff) == 1)
        return( 0xff );
    break;
            case 7:
    if(GFX_DRV_SSD1926_SetReg(0x1137, 0xff) == 1)
        return( 0xff );
    break;
            case 8:
    if(GFX_DRV_SSD1926_SetReg(0x1132, 0xff) == 1)
        return( 0xff );
    break;
            case 9:
    if(GFX_DRV_SSD1926_SetReg(0x1133, 0xff) == 1)
        return( 0xff );
    break;
            case 10:
    //Normal interrupt handling
    if(GFX_DRV_SSD1926_SetReg(0x1134, 0x13) == 1)          //enable write interrupt
        return( 0xff );
    break;
            case 11:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x13) == 1)          //clear all type of normal interrupt
        return( 0xff );
    break;
            case 12:
    if
    (
        (value = SDSendCommand
            (
                CMD_WR_SINGLE,
                SSD_RESPONSE_48 | SSD_DATA_PRESENT | SSD_CMD_CRC_CHK | SSD_CMD_IDX_CHK,
                sector_addr
            )) == 0xff
    )return( 0xff );

    if(value == false)
        return (false);
    break;
            case 13:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x01) == 1) 			//clear previous interrupt
        return( 0xff );

    do	//check Buffer write int
    {
        state = 14;
        if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
            return( 0xff );
        break;
        case 15:
        if(GFX_DRV_SSD1926_GetReg(0x1125, &data1) == 1)
            return( 0xff );
    } while(!(data&0x10) && !(data1 & 0x04));

    break;
            case 16:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x10) == 1) 			//clear previous interrupt
        return( 0xff );

    for(i = 0; i < sectorSize; i++)
    {
 
        //check if Write Enable bit set, which mean buffer is free for new data
        do
        {
            state = 17;
                case 17:
            if(GFX_DRV_SSD1926_GetReg(0x1125, &data) == 1)
                return( 0xff );
        }while(!(data & 0x04));
        break;
        case 18:
        //put data that need be written into SSD1928 buffers
        if(SetDataPortReg0(*buffer) == 1)
            return( 0xff );
        buffer++;
    }
    break;
            case 19:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x10) == 1) 			//clear previous interrupt
        return( 0xff );
    do	//check Transfer complt int
    {
        state = 20;
        case 20:
        if(GFX_DRV_SSD1926_GetReg(0x1130, &data) == 1)
            return( 0xff );
    } while(!(data&0x02));
    break;
            case 21:
    if(GFX_DRV_SSD1926_SetReg(0x1130, 0x02) == 1) 		    // clear previous interrupt
        return( 0xff );
    state = 0;
    return (true);
        }
        state++;
    }
}

/******************************************************************************
 * Function:
 *  void SDInitIO(void)
 * PreCondition:
 *  None.
 * Input:
 *  None.
 * Output:
 *  None.
 * Side Effects:
 *  None.
 * Overview:
 *  Configuration of IOs connected to SD card. Not required for SSD1926 but used by the file system. 
 * Note:
 *  None.
 *****************************************************************************/
void SDInitIO(void)
{
}

/******************************************************************************
 * Function:
 *  WORD SDReadSectorSize(void)
 * PreCondition:
 *  MediaInitialize() is complete
 * Input:
 *  None.
 * Output:
 *  Size of the sectors for this physical media.
 * Side Effects:
 *  None.
 * Overview:
 *  Returns size of the sectors for this physical media.
 * Note:
 *  None.
 *****************************************************************************/
uint16_t SDReadSectorSize(void)
{
    return (sectorSize);
}

/******************************************************************************
 * Function:
 *  DWORD SDReadCapacity(void)
 * PreCondition:
 *  MediaInitialize() is complete
 * Input:
 *  None.
 * Output:
 *  Number of sectors.
 * Side Effects:
 *  None
 * Overview:
 *  Returns number of sectors.
 * Note:
 *  None
 *****************************************************************************/
uint32_t SDReadCapacity(void)
{
    return (finalLBA);
}

