/*******************************************************************************
  USB MDD internal flash source file.

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_mdd_internal_flash.c

  Summary:
    Media driver for internal flash.

  Description:
   Media driver interface source file
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
// DOM-IGNORE-END


#include <stdint.h>
#include "system_config.h"
#include "system/common/sys_module.h"
#include "driver/driver_common.h"
#include "mdd_internal_flash.h"
#include "p32xxxx.h"
#include "sys/kmem.h"


typedef struct _USB_DEVICE_MDD_INTFLASH_INSTANCE_
{
    SYS_STATUS sysState;
    USB_DEVICE_MDD_INTFLASH_INIT intFlashInit;
}USB_DEVICE_MDD_INTFLASH_INSTANCE;


typedef struct _USB_DEVICE_MDD_INTFLASH_CLIENT_
{
    SYS_MODULE_INDEX parentIndex;
    /* Client status */
    DRV_CLIENT_STATUS clientState;
    
}USB_DEVICE_MDD_INTFLASH_CLIENT;


USB_DEVICE_MDD_INTFLASH_CLIENT intFlashClient[USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES][USB_DEVICE_MDD_INTFLASH_MAX_CLIENTS];
USB_DEVICE_MDD_INTFLASH_INSTANCE intFlashInstance[USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES];


#define NVMemIsError()    (NVMCON & (_NVMCON_WRERR_MASK | _NVMCON_LVDERR_MASK))

//#define KVA_TO_PA(v) 	((v) & 0x1fffffff)

#define NVMOP_WORD_PGM          0x4001      // Word program operation
#define NVMOP_PAGE_ERASE        0x4004      // Page erase operation
#define NVMOP_ROW_PGM           0x4003      // Row program operation
#define NVMOP_NOP               0x4000      // NOP operation

unsigned int INTDisableInterrupts(void);
void INTRestoreInterrupts(unsigned int status);

/********************************************************************
* Function: 	NVMemOperation()
*
* Precondition: 
*
* Input: 		NV operation
*
* Output:		NV eror
*
* Side Effects:	This function must generate MIPS32 code only and 
				hence the attribute (nomips16)
*
* Overview:     Performs reuested operation.
*
*			
* Note:		 	None.
********************************************************************/
uint32_t __attribute__((nomips16)) NVMemOperation(uint32_t nvmop)
{
    int	int_status;
    //int	susp;

  
	int_status = INTDisableInterrupts(); 


    // Enable Flash Write/Erase Operations
    NVMCON = NVMCON_WREN | nvmop;
    // Data sheet prescribes 6us delay for LVD to become stable.
    // To be on the safer side, we shall set 7us delay.
     // wait at least 6 us for LVD start-up
    // assume we're running at max frequency
    // (80 MHz) so we're always safe
    {
        unsigned long t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < (80/2)*6);
    }

    NVMKEY 		= 0xAA996655;
    NVMKEY 		= 0x556699AA;
    NVMCONSET 	= NVMCON_WR;

    // Wait for WR bit to clear
    while(NVMCON & NVMCON_WR);
    
    // Disable Flash Write/Erase operations
    NVMCONCLR = NVMCON_WREN;  


	// Enable DMA & Enable Interrupts

	INTRestoreInterrupts(int_status);


	// Return Error Status
    return(NVMemIsError());
}


/*********************************************************************
 * Function:        unsigned int NVMErasePage(void* address)
 *
 * Description:     A page erase will erase a single page of program flash,
 *                  which equates to 1k instructions (4KBytes). The page to
 *                  be erased is selected using NVMADDR. The lower bytes of
 *                  the address given by NVMADDR are ignored in page selection.
 *
 * PreCondition:    None
 *
 * Inputs:          address:  Destination page address to Erase.
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:         NVMemErasePage((void*) 0xBD000000)
 ********************************************************************/
uint32_t NVMemErasePage(void* address)
{
    uint32_t res;

    // Convert Address to Physical Address
	NVMADDR = KVA_TO_PA((unsigned int)address);

	// Unlock and Erase Page
	res = NVMemOperation(NVMOP_PAGE_ERASE);

	// Return WRERR state.
	return res;

}


/*********************************************************************
 * Function:        unsigned int NVMWriteWord(void* address, unsigned int data)
 *
 * Description:     The smallest block of data that can be programmed in
 *                  a single operation is 1 instruction word (4 Bytes).  The word at
 *                  the location pointed to by NVMADDR is programmed.
 *
 * PreCondition:    None
 *
 * Inputs:          address:   Destination address to write.
 *                  data:      Word to write.
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:         NVMWriteWord((void*) 0xBD000000, 0x12345678)
 ********************************************************************/
uint32_t NVMemWriteWord(void* address, uint32_t data)
{
    uint32_t res;

    NVMADDR = KVA_TO_PA((unsigned int)address);

    // Load data into NVMDATA register
    NVMDATA = data;

    // Unlock and Write Word
    res = NVMemOperation(NVMOP_WORD_PGM);

	return res;
}



/******************************************************************************
 * Function:        SYS_MODULE_OBJ 
        USB_DEVICE_MDD_INTFLASH_Initialize(const SYS_MODULE_INDEX index,
                                        const SYS_MODULE_INIT * const initData)
 *
 * PreCondition:    None.
 *
 * Input:           void
 *
 * Output:          SYS_MODULE_OBJ - module object.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 *****************************************************************************/ 
SYS_MODULE_OBJ USB_DEVICE_MDD_INTFLASH_Initialize(const SYS_MODULE_INDEX index,
                                        const SYS_MODULE_INIT * const initData)
{
      // Make sure the index is with in range.
    SYS_ASSERT( ( ( index >= 0 ) && ( index < USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES ) ),
                      " USB Device MDD Internal Flash Layer: Invalid index or value assigned to USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES ");

    SYS_ASSERT(initData != NULL, " USB Device MDD Internal Flash Layer: Pointer to init data passed is NULL");

    // Change the state to initialized.
    intFlashInstance[index].sysState = SYS_STATUS_READY;

    // Copy init data.
    memcpy( &intFlashInstance[index].intFlashInit, initData, sizeof(USB_DEVICE_MDD_INTFLASH_INIT));

    return index;
}


/******************************************************************************
 * Function:        SYS_STATUS 
                    USB_DEVICE_MDD_INTFLASH_Status(SYS_MODULE_OBJ objIndex)
 *
 * PreCondition:    None.
 *
 * Input:           void
 *
 * Output:          SYS_MODULE_OBJ - module object.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 *****************************************************************************/ 
 
SYS_STATUS USB_DEVICE_MDD_INTFLASH_Status(SYS_MODULE_OBJ objIndex)
{

    SYS_ASSERT( ( ( objIndex >= 0 ) && ( objIndex < USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES ) ),
                      " USB Device MDD Internal Flash Layer: Invalid index or value assigned to USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES ");
    return (intFlashInstance[objIndex].sysState);
}


DRV_HANDLE USB_DEVICE_MDD_INTFLASH_Open(const SYS_MODULE_INDEX index, const DRV_IO_INTENT  intent )
{
    uint8_t count;

     // Make sure the index is with in range.
    SYS_ASSERT( ( ( index >= 0 ) && ( index < USB_DEVICE_MDD_INTFLASH_MAX_INSTANCES ) ),
                      " USB Device Layer: Invalid index or value assigned to USB_DEVICE_MAX_INSTANCES ");

    if( intFlashInstance[index].sysState <= 0 )
    {
        // Iternal flash is not yet initialized.
        return DRV_HANDLE_INVALID;

    }
    //else check if we have a free client.

    for( count = 0; count < USB_DEVICE_MDD_INTFLASH_MAX_CLIENTS; count++)
    {
        if(intFlashClient[index][count].clientState <= 0 )
        {
            // This client is free, assign this client.
            intFlashClient[index][count].clientState = DRV_CLIENT_STATUS_READY;

            // Remember the parent index.
            intFlashClient[index][count].parentIndex = index;

            return (DRV_HANDLE)&intFlashClient[index][count];
        }
    }

     return DRV_HANDLE_INVALID;
}


void USB_DEVICE_MDD_INTFLASH_Close(DRV_HANDLE hClient )
{

    //DRV_HANDLE usbClientHandle;
    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle;

    // Check the handle.
    SYS_ASSERT( ( DRV_HANDLE_INVALID != hClient ), "Invalid client handle");

  
    intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT * )hClient;
    
    // close the handle.
    intFlashClientHandle->clientState = DRV_CLIENT_STATUS_CLOSED;
}




uint32_t USB_DEVICE_MDD_INTFLASH_ReadCapacity(DRV_HANDLE hClient)
{
    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT  *)hClient;
    SYS_MODULE_INDEX index;

    SYS_ASSERT( DRV_HANDLE_INVALID != hClient,
                    " USB Device internal flash MDD: Invalid handle passed inside read capacity funciton");

    //The SCSI READ_CAPACITY command wants to know the last valid LBA address 
    //that the host is allowed to read or write to.  Since LBA addresses start
    //at and include 0, a return value of 0 from this function would mean the 
    //host is allowed to read and write the LBA == 0x00000000, which would be 
    //1 sector worth of capacity.
    //Therefore, the last valid LBA that the host may access is 
    //MDD_INTERNAL_FLASH_TOTAL_DISK_SIZE - 1.

    index = intFlashClientHandle->parentIndex;

    return(intFlashInstance[index].intFlashInit.totalDiskSize - 1);
}


/******************************************************************************
 * Function:        WORD ReadSectorSize(void)
 *
 * PreCondition:    MediaInitialize() is complete
 *
 * Input:           void
 *
 * Output:          WORD - size of the sectors for this physical media.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 *****************************************************************************/
uint32_t USB_DEVICE_MDD_INTFLASH_ReadSectorSize(DRV_HANDLE hClient)
{
    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT  *)hClient;
    SYS_MODULE_INDEX index;

    SYS_ASSERT( DRV_HANDLE_INVALID != hClient,
                    " USB Device internal flash MDD: Invalid handle passed inside read sector size function");

     index = intFlashClientHandle->parentIndex;

    return(intFlashInstance[index].intFlashInit.mediaSectorSize);
}



bool USB_DEVICE_MDD_INTFLASH_SectorRead(DRV_HANDLE hClient, uint32_t sector_addr, uint8_t * buffer,
                                        void * refHandle, MEDIA_OP_CMPLT_CB callBack)
{

    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT  *)hClient;
    SYS_MODULE_INDEX index;

    SYS_ASSERT( DRV_HANDLE_INVALID != hClient,
                    " USB Device internal flash MDD: Invalid handle passed inside sector read function");

    index = intFlashClientHandle->parentIndex;


    //Error check.  Make sure the host is trying to read from a legitimate
    //address, which corresponds to the MSD volume (and not some other program
    //memory region beyond the end of the MSD volume).
    if(sector_addr >= intFlashInstance[index].intFlashInit.totalDiskSize)
    {
        return false;
    }

    //Read a sector worth of data, and copy it to the specified scratch RAM "buffer".
    memcpy
    (
        (void*)buffer,
        (const void*)(intFlashInstance[index].intFlashInit.masterBootRecordAdrs +
            (sector_addr * intFlashInstance[index].intFlashInit.mediaSectorSize)),
        intFlashInstance[index].intFlashInit.mediaSectorSize
    );

    // Internal flash is not a slow device. We complete the operation almost immediately.
    // Call the callback function and inform the caller that operation is complete.
    callBack (refHandle, true);

    return true;
}//end SectorRead


uint8_t USB_DEVICE_MDD_INTFLASH_WriteProtectState(DRV_HANDLE hClient)
{
    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT  *)hClient;
    SYS_MODULE_INDEX index;

    SYS_ASSERT( DRV_HANDLE_INVALID != hClient,
                    " USB Device internal flash MDD: Invalid handle passed inside write protect function");

    index = intFlashClientHandle->parentIndex;

    return(intFlashInstance[index].intFlashInit.wpState);

   /* #if defined(INTERNAL_FLASH_WRITE_PROTECT)
        return 0x80 ;
    #else
	    return 0x00;
    #endif*/
}



bool  USB_DEVICE_MDD_INTFLASH_SectorWrite(DRV_HANDLE hClient, uint32_t sector_addr, uint8_t* buffer,
                                                    void * refHandle, MEDIA_OP_CMPLT_CB callBack)
{
    uint8_t* nvDest;
    uint8_t* pageAddress;
    uintptr_t ramDest;
    uint32_t i;
    USB_DEVICE_MDD_INTFLASH_CLIENT  * intFlashClientHandle = (USB_DEVICE_MDD_INTFLASH_CLIENT  * )hClient;
    SYS_MODULE_INDEX index;
    
    SYS_ASSERT( DRV_HANDLE_INVALID != hClient,
                    " USB Device internal flash MDD: Invalid handle passed inside sector read function");

    index = intFlashClientHandle->parentIndex;
   
    //First, error check the resulting address, to make sure the MSD host isn't trying
    //to erase/program illegal LBAs that are not part of the designated MSD volume space.
    if( sector_addr >= intFlashInstance[index].intFlashInit.totalDiskSize )
    {
        return false;
    }
    
     

    nvDest = (uint8_t *)(intFlashInstance[index].intFlashInit.masterBootRecordAdrs +
                    (sector_addr * intFlashInstance[index].intFlashInit.mediaSectorSize));
                    
   
    pageAddress = (uint8_t *)(((uint32_t)nvDest) & ~(intFlashInstance[index].intFlashInit.eraseBlockSize - 1));

    // Read the page.
    memcpy(intFlashInstance[index].intFlashInit.scratchBuffer, pageAddress, intFlashInstance[index].intFlashInit.eraseBlockSize);

    ramDest = (uintptr_t)&intFlashInstance[index].intFlashInit.scratchBuffer[nvDest - pageAddress] ;

    memcpy((void *)ramDest, (void *)buffer, MEDIA_SECTOR_SIZE);

    // Erase the flash page.
    NVMemErasePage((void *)pageAddress);
    
    nvDest = pageAddress;
    
    // Write the updated page.
    for( i = 0; i < (ERASE_BLOCK_SIZE); i = i+4 )
    {
        NVMemWriteWord((void*)nvDest, *((uint32_t *)&intFlashInstance[index].intFlashInit.scratchBuffer[i]));
        nvDest = nvDest + 4;    
    }    
    
     // Internal flash is not a slow device. We complete the operation almost immediately.
    // Call the callback function and inform the caller that operation is complete.
    callBack (refHandle, true);
    
    return true;
}


bool USB_DEVICE_MDD_INTFLASH_MediaDetect(DRV_HANDLE hClient)
{

    // Media is always present in case of internal flash.
    return true;

}