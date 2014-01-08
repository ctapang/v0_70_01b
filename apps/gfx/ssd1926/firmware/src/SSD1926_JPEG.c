/******************************************************************************
 *    SSD1926 hardware JPEG decoder driver
 ******************************************************************************
 * File Name:       SSD1926_JPEG.c
 * Dependencies:    see included files below
 * Processor:       PPIC24F, PIC24H, dsPIC, PIC32
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

/**************************************************************************
 EXTERNS
**************************************************************************/
extern uint32_t Cluster2Sector(DISK * disk, uint32_t cluster);
extern uint8_t SDSectorDMARead(uint32_t sector_addr, uint32_t dma_addr, uint16_t num_blk);

/**************************************************************************
 LOCAL FUNCTIONS PROTOTYPES
**************************************************************************/
uint8_t         SDFile2JPEGFIFO(uint32_t fifoAddress, uint32_t byteSize, FSFILE *stream);
bool            SSD1926Setup(SSD_JPEG_DECODE *decode);
SSD_JPEG_ERR    JPEGHeader(SSD_JPEG_DECODE *decode);
bool            JPEGResize(SSD_JPEG_DECODE *decode);
bool            JPEGStart(void);
SSD_JPEG_ERR    JPEGData(SSD_JPEG_DECODE *decode);
bool            JPEGStop(void);

/**************************************************************************
  Function:
    void SSD1926SetRGB(void)
  Conditions:
    None.
  Input:
    None.
  Return:
    None.
  Side Effects:
    None.
  Description:
    Sets main and floating windows to RGB mode
  Remarks:
    This mode is used by the graphics library.
  **************************************************************************/
uint8_t GFX_DRV_SSD1926_SetRGB(void)
{
    if(GFX_DRV_SSD1926_SetReg(REG_RGB_SETTING, 0xc0) == 1)
        return(1);

    return(0);
}

/**************************************************************************
  Function:
    void SSD1926SetYUV(void)
  Conditions:
    None.
  Input:
    None.
  Return:
    None.
  Side Effects:
    Objects drawn by graphics library cannot be displayed correctly in this mode.
  Description:
    Sets main and floating windows to YUV mode
  Remarks:
    Usually JPEG files use YUV format.
  **************************************************************************/
uint8_t GFX_DRV_SSD1926_SetYUV(void)
{
    if(GFX_DRV_SSD1926_SetReg(REG_RGB_SETTING, 0x00) == 1)
        return(1);

    return(0);
}

/**************************************************************************
  Function:
    BYTE JPEGPutImage(char* filename)
  Conditions:
    FSInit() file system initialization must be done, 
    SSD1926SetYUV() YUV mode must be set.
  Input:
    filename - pointer to the file name string.
  Return:
    Non-zero if the operation was successful.
  Side Effects:
    None.
  Description:
    Displays the JPEG image form the JPEG file specified in the screen center.
  Remarks:
    Usually JPEG files use YUV format.
  **************************************************************************/
uint8_t JPEGPutImage(char *filename)
{
    static FSFILE          *jpeg_file;
    static SSD_JPEG_DECODE jpeg_decode;
    static uint8_t state = 0;

    while(1)
    {
    switch(state)
    {

    case 0:
    if(GFX_DRV_SSD1926_SetYUV())    // Switching shows a little green flicker
        return(false);

    if((jpeg_file = FSfopen(filename, "r")) == 0)
        return (false);

    jpeg_decode.stream = (void *)jpeg_file;
    break;
    case 2:
    if(SSD1926Setup(&jpeg_decode) == false)
        return(false);
    break;
    case 3:
    if(JPEGHeader(&jpeg_decode) != NO_ERR)
        return(false);
    break;
    case 4:
    if(JPEGResize(&jpeg_decode) == false)
        return(false);
    break;
    case 5:
    if(JPEGStart() == false)
        return(false);
    break;
    case 6:
    if(JPEGData(&jpeg_decode) != NO_ERR)
        return( false );
    break;
    case 7:
    if(JPEGStop() == false)
        return( false );

    FSfclose(jpeg_file);
    state = 0;
    return (true);
    }
    state++;
    }

}

/**************************************************************************
  Function:
    BYTE SDFile2JPEGFIFO(DWORD fifoAddress, WORD byteSize, FSFILE *stream)
  Summary:
    Read portion data from a file on SD card and put it in SSD1926 memory
  Conditions:
    File is opened in a read mode
  Input:
    fifoAddress -   Destination buffer in SSD1926 memory
    byteSize    -   Size in bytes
    stream      -   File to be read from
  Return:
    non-zero if the operation was successful.
  Side Effects:
    None.
  Description:
    The SDFile2JPEGFIFO function will read data from the specified file on SD card connected
    directly to SSD1926 and move the data to SSD1926 internal RAM assigned for JPEG FIFO.
  Remarks:
    None.
  **************************************************************************/
uint8_t SDFile2JPEGFIFO(uint32_t fifoAddress, uint32_t byteSize, FSFILE *stream)
{
    static DISK     *dsk;
    static uint32_t len;
    static uint32_t seek, sec_sel;
    static uint32_t pos;
    static uint8_t  state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    len = byteSize / MEDIA_SECTOR_SIZE;
    dsk = stream->dsk;
    pos = stream->pos;
    seek = stream->seek;

    sec_sel = (uint32_t) Cluster2Sector(dsk, stream->ccls);
    sec_sel += (uint32_t) stream->sec;         // add the sector number to it

    while(len)
    {
        if(seek >= stream->size)
        {
            seek = stream->size;
            pos = 0;
            break;
        }

        if(stream->sec >= dsk->SecPerClus)
        {
            stream->sec = 0;
            if(FILEget_next_cluster(stream, (uint32_t) 1) != CE_GOOD)
            {
                state = 0;
                return (false);
            }

            sec_sel = (uint32_t) Cluster2Sector(dsk, (uint32_t) stream->ccls);
            sec_sel += (uint32_t) stream->sec;  // add the sector number to it
        }

        if(((uint32_t) (stream->sec) + (uint32_t) len) > (uint32_t) (dsk->SecPerClus))
            pos = dsk->SecPerClus - stream->sec;
        else
            pos = len;
        state = 1;
        case 1:
        if(SDSectorDMARead(sec_sel, fifoAddress, pos) == 0xff)
            return (false);

        len -= pos;
        stream->sec += pos;
        sec_sel += pos;
        seek += pos * MEDIA_SECTOR_SIZE;
        fifoAddress += pos * MEDIA_SECTOR_SIZE;
    }
    state = 0;
    stream->pos = 0;                        // save off the positon
    stream->seek = seek;                    // save off the seek
    return (true);
    }
    state++;
    }
}

/*********************************************************************
 * Function:       
 *  bool SSD1926Setup(SSD_JPEG_DECODE *decode)
 * PreCondition:    
 *  JPEG file should be opened.
 * Input:           
 *  decode - pointer to decoder parameters 
 * Output:          
 *  None.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Sets up JPEG engine for a new file
 * Note:
 *  None.           
 ********************************************************************/
bool SSD1926Setup(SSD_JPEG_DECODE *decode)
{
    static uint32_t   size;
    static uint8_t    state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    decode->bytes_read = 0;

    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RST_MARKER_STATUS, 0) == 1)
        return( false );
    break;

            case 1:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_FIFO_SIZE, (uint8_t) (SSD_JPEG_FIFO_BLK_NUMBER - 1)) == 1)
        return( false );

    // set the FIFO address
    decode->fifo_addr = SSD_JPEG_FIFO_START_ADDR;
    decode->fifo_addr_end = SSD_JPEG_FIFO_START_ADDR + (SSD_JPEG_FIFO_BLK_NUMBER * SSD_JPEG_FIFO_BLK_SIZE);

    size = (SSD_JPEG_FIFO_START_ADDR >> 2);    // each address is 32 bits
    break;
            case 2:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_DEST_START_ADDR_0, size) == 1)
        return( false );
    break;
            case 3:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_DEST_START_ADDR_1, size>>8) == 1)
        return( false );
    break;
            case 4:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_DEST_START_ADDR_2, size>>16) == 1)
        return( false );
    break;
            case 5:
    // enable the JPEG and set YUV range
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_CTRL, 0x11) == 1)
        return( false );
    break;
            case 6:
    // reset the module
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_CMD, 0x80) == 1)
        return( false );

    SYS_TMR_DelayMS(1);
    break;
            case 7:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_CMD, 0x00) == 1)
        return( false );
    break;
            case 8:
    // Set the RST Marker Operatation to Data revise
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RST_MARKER, 0x02) == 1)
        return( false );
    break;
            case 9:
    // Set the RST Marker Status
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RST_MARKER_STATUS, 0x00) == 1)
        return( false );

    // load the file size in bytes
    FSfseek(decode->stream, 0, SEEK_END);
    size = FSftell(decode->stream);
    FSfseek(decode->stream, size, SEEK_END);

    decode->size = size;
    break;
            case 10:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_FILE_SIZE_0, size) == 1)
        return( false );
    break;
            case 11:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_FILE_SIZE_1, size>>8) == 1)
        return( false );
    break;
            case 12:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_FILE_SIZE_2, size>>16) == 1)
        return( false );
    break;
            case 13:
    // set the JPEG Op mode
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_OP_MODE_ENC, 0x04) == 1)
        return( false );
    break;
            case 14:
    // turn on the resizer
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_CTL, 0x01) == 1)
        return( false );
    break;
            case 15:
    // start!
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_CMD, 0x01) == 1)
        return( false );
    state = 0;
    return( true );
        }
        state++;
    }
}

/*********************************************************************
 * Function:       
 *  SSD_JPEG_ERR JPEGHeader(SSD_JPEG_DECODE *decode)
 * PreCondition:    
 *  SSD1926Setup(...) must be called first.
 * Input:           
 *  decode - pointer to decoder parameters
 * Output:          
 *  Error code. Returns NO_ERR if the operation was successful.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Loads the JPEG header.
 * Note:
 *  None. 
 ********************************************************************/
SSD_JPEG_ERR JPEGHeader(SSD_JPEG_DECODE *decode)
{

    static uint8_t value;
    static uint8_t state = 0;

    static uint16_t size;
    static uint8_t *point = (uint8_t*)&size;

    while(1)
    {
        switch(state)
        {
            case 0:
        if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RST_MARKER_STATUS, &value) == 1)
            return(ERR_DECODE);

        if(value)
            return (ERR_DECODE);
        state++;
            case 1:

        if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RAW_STATUS1, &value) == 1)
            return(ERR_DECODE);

        if(value & 0x10) // has decode information availble
        {
            state = 2;
            case 2:
            if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_DECODE_X_SIZE, &point[0]) == 1)
                return(ERR_DECODE);
            state++;
            case 3:
            if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_DECODE_X_SIZE + 1, &point[1]) == 1)
                return(ERR_DECODE);
            decode->image_width = size;
            state++;
            case 4:
            if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_DECODE_Y_SIZE, &point[0]) == 1)
                return(ERR_DECODE);
            state++;
            case 5:
            if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_DECODE_Y_SIZE + 1, &point[1]) == 1)
                return(ERR_DECODE);
            decode->image_height = size;
            state++;
            case 6:
            if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_OP_MODE, (uint8_t*)&decode->op_mode) == 1)
                return(ERR_DECODE);

            state = 0;
            return (NO_ERR);
        }
        state = 7;
            case 7:
        if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RAW_STATUS, &value) == 1)
            return(ERR_DECODE);

        if(!(value & 0x01))
        {
            state = 0;
            continue;
        }
        if(decode->bytes_read < decode->size)
        {
            state = 8;
            case 8:
            if(SDFile2JPEGFIFO(SSD_JPEG_FIFO_START_ADDR, SSD_JPEG_FIFO_SIZE, decode->stream)== 0xff)
                return(ERR_DECODE);

            decode->bytes_read += SSD_JPEG_FIFO_SIZE;
        }
        else
        {
            state = 0;
            return (ERR_NO_DATA);
        }
        }
        state = 0;
    }
}

/*********************************************************************
 * Function:
 *  bool SSDJPEGResize(SSD_JPEG_DECODE *decode)
 * PreCondition:    
 *  Should be called after JPEGHeader(...)
 * Input:           
 *  decode - pointer to decoder parameters 
 * Output:          
 *  None.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Calculates the size reducing factor (can be only a power of 2) and 
 *  sets it for the JPEG engine. Changes the image size parameters accordingly.
 * Note:
 *  None.           
 ********************************************************************/
bool JPEGResize(SSD_JPEG_DECODE *decode)
{
    const uint32_t __align[] = { 8, 16, 16, 32};
    static uint16_t       size;
    static uint8_t        div = 1;
    static uint8_t        state = 0;
    static uint32_t       destAddr;
    static uint32_t       x, y;

    while(1)
    {
        switch(state)
        {
            case 0:

    if((decode->image_height > (GFX_MaxYGet() + 1)) || (decode->image_width > (GFX_MaxXGet() + 1)))
    {
        div = 2;
        while(div < 8)
        {
            if(((decode->image_height / div) <= (GFX_MaxYGet() + 1)) && ((decode->image_width / div) <= (GFX_MaxXGet() + 1)))
                break;

            div <<= 1;
        }
        break;
        case 1:
        if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_OP_0, div) == 1)
            return( false );
        break;
        case 2:
        if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_OP_1, 0x02) == 1)
            return( false );

    }

    state = 3;
    decode->display_height = div * (GFX_MaxYGet() + 1);
    decode->display_width = div * (GFX_MaxXGet() + 1);

    // set the source address
    x = (decode->display_width - decode->image_width) / div / 2;
    y = (decode->display_height - decode->image_height) / div / 2;

    destAddr = ((y * (GFX_MaxXGet() + 1) + x) >> 1);    // each address is 32 bits, each pixel is 2 bytes
    destAddr &= ~0xFFFFFF01;                             // LSB must be zero

     case 3:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_SRC_START_ADDR_0, destAddr) == 1)
        return( false );
    break;
            case 4:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_SRC_START_ADDR_1, (destAddr>>8)) == 1)
        return( false );
    break;
            case 5:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_SRC_START_ADDR_2, (destAddr>>16)) == 1)
        return( false );

    decode->display_height = decode->display_height & (~(__align[decode->op_mode] - 1));
    decode->display_width = decode->display_width & (~(__align[decode->op_mode] - 1));

    size = decode->display_width - 1;
    break;
            case 6:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_STARTX_0, 0) == 1)
        return( false);
    break;
            case 7:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_STARTX_1, 0) == 1)
        return( false );
    break;
            case 8:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_ENDX_0, size) == 1)
        return( false );
    break;
            case 9:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_ENDX_1, size>>8) == 1)
        return( false );

    size = decode->display_height - 1;
    break;
            case 10:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_STARTY_0, 0) == 1)
        return( false );
    break;
            case 11:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_STARTY_1, 0) == 1)
        return( false );
    break;
            case 12:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_ENDY_0, size) == 1)
        return( false );
    break;
            case 13:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_RESIZER_ENDY_1, size>>8) == 1)
        return( false );

    state = 0;
    return( true );
        }
        state++;
    }
}

/*********************************************************************
 * Function:       
 *  void JPEGStart(void)
 * PreCondition:    
 *  should be called after JPEGHeader(...).   
 * Input:           
 *  None.
 * Output:          
 *  None.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Starts the JPEG data decoding
 * Note:           
 ********************************************************************/
bool JPEGStart(void)
{
    static uint8_t state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
    // clear all status of the JPEG Link Buffer and FIFO
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_STATUS, 0x07) == 1)  // write 1 to clear
        return( false );
    break;
            case 1:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_STATUS1, 0x30) == 1) // write 1 to clear
        return( false );
    break;

    case 2:
        if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_START_STOP, 0x01) == 1)
            return( false );
    state = 0;
    return( true );
        }
    state++;
    }
}

/*********************************************************************
 * Function:       
 *  SSD_JPEG_ERR JPEGData(SSD_JPEG_DECODE *decode)
 * PreCondition:    
 *  should be called after JPEGStart(...).
 * Input:           
 *  decode - pointer to decoder parameters
 * Output:          
 *  Error code. Returns NO_ERR if the operation was successful.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Decodes the picture on the screen.
 * Note:
 *  None. 
 ********************************************************************/
SSD_JPEG_ERR JPEGData(SSD_JPEG_DECODE *decode)
{

    static uint8_t data;
    static uint8_t state = 0;

    while(1)
    {
        switch(state)
        {
            case 0:
         if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RST_MARKER_STATUS, &data) == 1)
             return (ERR_DECODE);

        if(data)
            return (ERR_DECODE);
         break;
            case 1:
         if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_DECODE_VALUE, &data) == 1)
             return (ERR_DECODE);

        if(data & 0xF8)
            return (ERR_DECODE);
         break;
            case 2:
        if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RAW_STATUS1, &data) == 1)
            return (ERR_DECODE);

        if(data == 0x22)
        {
            state = 0;
            return (NO_ERR);
        }

        break;
        case 3:
        if(GFX_DRV_SSD1926_GetReg(SSD_JPEG_REG_RAW_STATUS, &data) == 1)   // FIFO is not empty
            return(ERR_DECODE);

       if(!(data & 0x01))   // FIFO is not empty
       {
           state = 0;
           continue;
       }
        if(decode->bytes_read < decode->size)
        {
            state = 4;
            case 4:
            if(SDFile2JPEGFIFO(SSD_JPEG_FIFO_START_ADDR, SSD_JPEG_FIFO_SIZE, decode->stream) == 0xff)
                return( ERR_DECODE );

            decode->bytes_read += SSD_JPEG_FIFO_SIZE;
        }
        else
        {
            state = 0;
            return (ERR_NO_DATA);
        }

        state = 0;
        return (ERR_DECODE);
        }
      state++;
    }
}

/*********************************************************************
 * Function:       
 *  bool JPEGStop(void)
 * PreCondition:    
 *  None.
 * Input:           
 *  None.
 * Output:          
 *  None.
 * Side Effects:    
 *  None.
 * Overview:        
 *  Stops the JPEG data decoding
 * Note:           
 ********************************************************************/
bool JPEGStop(void)
{
    static uint8_t state = 0;
        switch(state)
        {
            case 0:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_CTRL, 0x10) == 1)
        return( false );
    state = 1;
            case 1:
    if(GFX_DRV_SSD1926_SetReg(SSD_JPEG_REG_START_STOP, 0x00) == 1)
        return( false );
    state = 0;
    return( true );
        }
}
