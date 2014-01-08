/*******************************************************************************
  System File System Library

  Summary:
    Microchip FS Library
    
    Description
    - Provides support for file search: findFirst, findNext
*******************************************************************************/

/*******************************************************************************
File Name:  fs_helper.c
Copyright ⌐ 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ôAS ISö WITHOUT WARRANTY OF ANY KIND,
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
#include <string.h>
#include "system/fs/sys_fs.h"

#if defined (SYS_FS_ENABLE)

#if defined(SYS_FS_FILESYSTEM_MDD)
static int32_t mddfs_findNext(SearchRec *rcd)
{
    return FindNext(rcd);
}
static int32_t mddfs_findFirst(const char *name, uint32_t attr, SearchRec *rcd)
{
    return FindFirst(name, attr, rcd);
}
#endif

/**************************** file_findFirstDEF ******************************
 * Description:
 *         Initial search function for the input Ascii fileName from CWD
 *
 * Params:
 *        name : The name to search for
 *               - Parital string search characters
 *               - Indicates the rest of the filename or extension can vary (e.g. FILE.*)
 *               - Indicates that one character in a filename can vary (e.g. F?LE.T?T)
 *        attr : The attributes that a found file may have
 *                ATTR_READ_ONLY - File may be read only
 *                ATTR_HIDDEN - File may be a hidden file
 *                ATTR_SYSTEM - File may be a system file
 *                ATTR_VOLUME - Entry may be a volume label
 *                ATTR_DIRECTORY - File may be a directory
 *                ATTR_ARCHIVE - File may have archive attribute
 *                ATTR_MASK - All attributes
 *        rcd : pointer to a structure to put the file information in
 *
 * Return: 0 - RETURN_SUCCESS, other value - failed
 *
 * Note:   MPFS2 has no file searching support.
 ******************************************************************************/
int32_t file_findFirst(const char *name, unsigned int attr, SYS_FS_SearchRec_t *rcd)
{
    char FSType[9];
    int32_t ret = -1;

    // Check if valid file string
    if(SYS_FS_IsLegalFileString(name, strlen(name)) != RETURN_SUCCESS)
    {
        return RETURN_FAILED;
    }

    // Get filesystem type as per CWD
    if(SYS_FS_FSFromCWD(FSType) != RETURN_SUCCESS) {
        return RETURN_FAILED;
    }

#if defined(SYS_FS_FILESYSTEM_MPFS)
    if (strncmp(FSType, "mpfs2", SYS_FS_MAX_DRIVE) == 0)
    {
        return RETURN_FAILED;
    }
#endif

#if defined(SYS_FS_FILESYSTEM_MDD)
    // Get the relative directory(cwd - mount path) for underlying FS
    if (strncmp(FSType, "mdd", SYS_FS_MAX_DRIVE) == 0)
    {
        ret = mddfs_findFirst(name, attr, (SearchRec *)rcd);
    }
#endif

    return ret;
}

/**************************** file_findNexttDEF *******************************
 * Description:
 *      The FindNext function performs the same function as the FindFirst funciton,
 *      except it does not copy any search parameters into the SearchRec structure
 *      (only info about found files) and it begins searching at the last directory
 *      entry offset at which a file was found, rather than at the beginning of the
 *      current working directory.
 *
 * Params:
 *        rcd : pointer to a structure to put the file information in
 *
 * Return: 0 - RETURN_SUCCESS, other value - failed
 *
 * Note:   MPFS2 has no file searching support.
 *         Call SYS_FS_findFirst before calling this function
 ******************************************************************************/
int32_t file_findNext(SYS_FS_SearchRec_t *rcd)
{
    char FSType[9];
    int32_t ret = -1;

    // Get filesystem type as per CWD
    if(SYS_FS_FSFromCWD(FSType) != RETURN_SUCCESS) {
        return RETURN_FAILED;
    }

#if defined(SYS_FS_FILESYSTEM_MPFS)
    if (strncmp(FSType, "mpfs2", SYS_FS_MAX_DRIVE) == 0)
    {
        return RETURN_FAILED;
    }
#endif

#if defined(SYS_FS_FILESYSTEM_MDD)
    // Get the relative directory(cwd - mount path) for underlying FS
    if (strncmp(FSType, "mdd", SYS_FS_MAX_DRIVE) == 0)
    {
        ret = mddfs_findNext((SearchRec *)rcd);
    }
#endif

    return ret;
}

#endif
