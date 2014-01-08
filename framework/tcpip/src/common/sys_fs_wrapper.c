/*******************************************************************************
  Harmony File System Wrapper for TCPIP

  File Name:
    sys_fs_wrapper.c

  Summary:
    This file provides wrapping functions for Harmony SYS_FS calls (unmount,
    open and stat)

  Description:
    This file provides wrapping functions for Harmony SYS_FS calls (unmount,
    open and stat) to add the local site path to web path before passing to
    SYS_FS for processing. This is a temporary file and need to be fixed in the
    long run.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "tcpip/src/common/sys_fs_wrapper.h"
#include "sys_fs_config.h"

//******************************************************************************
/*Function:
  SYS_FS_HANDLE SYS_FS_FileOpen_Wrapper(const char *fname,
                                 SYS_FS_FILE_OPEN_ATTRIBUTES attributes);

***************************************************************************/
SYS_FS_HANDLE SYS_FS_FileOpen_Wrapper(const char *fname,
                                 SYS_FS_FILE_OPEN_ATTRIBUTES attributes)
{
    uint32_t compareResult, strCopyLoop;
    SYS_FS_HANDLE fileOpenResult;
    uint8_t localSitePath[WEBSITE_PATH_LENGTH+12];
    uint8_t fnameString[WEBSITE_PATH_LENGTH];
    const char *fnameBuf;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; strCopyLoop++)
        fnameString[strCopyLoop] = 0;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH+12; strCopyLoop++)
        localSitePath[strCopyLoop] = 0;

    fnameBuf = fname;

    /* Copy fname into a string */
    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; fnameBuf++, strCopyLoop++)
        fnameString[strCopyLoop] = *fnameBuf;

    /* Copy the local website path to to a string*/
    strncpy((char*)localSitePath,(const char*)LOCAL_WEBSITE_PATH, strlen((const char*)LOCAL_WEBSITE_PATH));

    /* Check web path name to see if it already contains local website name*/
    compareResult = strncmp((const char *)fnameString,(const char *)localSitePath,strlen((char *)localSitePath));

    /* If it does*/
    if (compareResult == 0)
    {
        /* Pass the fname directly to the FileOpen function*/
        fileOpenResult = SYS_FS_FileOpen(fname, attributes);
    }
    /* If not*/
    else
    {
        /*Append local path to web path*/
        strncat((char*)localSitePath,(const char*)fname,WEBSITE_PATH_LENGTH+12);
        fileOpenResult = SYS_FS_FileOpen((const char *)localSitePath, attributes);
    }

    return fileOpenResult;
}

//******************************************************************************
/*Function:
  SYS_FS_HANDLE SYS_FS_FileOpen_Wrapper(const char *fname,
                                 SYS_FS_FILE_OPEN_ATTRIBUTES attributes);

***************************************************************************/
SYS_FS_RESULT SYS_FS_FileStat_Wrapper(const char *fname,
                                      SYS_FS_FSTAT *buf)
{
    uint32_t compareResult, strCopyLoop;
    SYS_FS_HANDLE fileStatResult;
    uint8_t localSitePath[14];
    uint8_t fnameString[WEBSITE_PATH_LENGTH];
    const char *fnameBuf;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; strCopyLoop++)
        fnameString[strCopyLoop] = 0;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH+12; strCopyLoop++)
        localSitePath[strCopyLoop] = 0;

    fnameBuf = fname;

    /* Copy fname into a string */
    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; fnameBuf++, strCopyLoop++)
        fnameString[strCopyLoop] = *fnameBuf;

    /* Copy the local website path to to a string*/
    strncpy((char*)localSitePath,(const char*)LOCAL_WEBSITE_PATH, strlen((const char*)LOCAL_WEBSITE_PATH));

    /* Check web path name to see if it already contains local website name*/
    compareResult = strncmp((const char *)fnameString,(const char *)localSitePath,strlen((char *)localSitePath));

    /* If it does*/
    if (compareResult == 0)
    {
        /* Pass the fname directly to the FileOpen function*/
        fileStatResult = SYS_FS_FileStat(fname, buf);
    }
    /* If not*/
    else
    {
        /*Append local path to web path*/
        strncat((char*)localSitePath,(const char*)fname,WEBSITE_PATH_LENGTH+12);
        fileStatResult = SYS_FS_FileStat((const char *)localSitePath, buf);
    }

    return fileStatResult;
}

//******************************************************************************
/*Function:
  SYS_FS_HANDLE SYS_FS_FileOpen_Wrapper(const char *fname,
                                 SYS_FS_FILE_OPEN_ATTRIBUTES attributes);

***************************************************************************/
SYS_FS_RESULT SYS_FS_Unmount_Wrapper(const char *fname)
{
    uint32_t compareResult, strCopyLoop;
    SYS_FS_HANDLE fileStatResult;
    uint8_t localSitePath[14];
    uint8_t fnameString[WEBSITE_PATH_LENGTH];
    const char *fnameBuf;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; strCopyLoop++)
        fnameString[strCopyLoop] = 0;

    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH+12; strCopyLoop++)
        localSitePath[strCopyLoop] = 0;

    fnameBuf = fname;

    /* Copy fname into a string */
    for (strCopyLoop=0; strCopyLoop <WEBSITE_PATH_LENGTH; fnameBuf++, strCopyLoop++)
        fnameString[strCopyLoop] = *fnameBuf;

    /* Copy the local website path to to a string*/
    strncpy((char*)localSitePath,(const char*)LOCAL_WEBSITE_PATH, strlen((const char*)LOCAL_WEBSITE_PATH));

    /* Check web path name to see if it already contains local website name*/
    compareResult = strncmp((const char *)fnameString,(const char *)localSitePath,strlen((char *)localSitePath));

    /* If it does*/
    if (compareResult == 0)
    {
        /* Pass the fname directly to the FileOpen function*/
        fileStatResult = SYS_FS_Unmount(fname);
    }
    /* If not*/
    else
    {
        /*Append local path to web path*/
         strncat((char*)localSitePath,(const char*)fname,WEBSITE_PATH_LENGTH+12);
        fileStatResult = SYS_FS_Unmount((const char *)localSitePath);
    }

    return fileStatResult;
}

/*******************************************************************************
 End of File
*/
