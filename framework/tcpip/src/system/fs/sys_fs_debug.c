/*******************************************************************************
File Name: sys_fs.h
Copyright ?2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
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
/*******************************************************************************
 * Microchip File System API defintion
 *
 * Summary:
 * FS (File System) is the virtual file system module of the ISP. The
 * FS provides an API abstration layer to lower file system layers by
 * providing a consistant posix like API to the end user. The FS API defined in
 * system/fs/sys_fs.h contains logic that handles underlying file system services
 * (such ans MPFS and MDD).

 * Description:

 * Rules for Pathnames usage in file access method
 * Directories are considered to be files.
 * A complete file name such as "MyFile1/MyFile2/Somefile.txt" has multiple filename
 * entries that complete the filename path.
 * A contiguous set of string character beginning at the first byte up to and
 * excluding any present SYS_FS_CHAR shall be known throughout this document as the first file name.
 * If the extracted first file name of a path cannot be found in the current working
 * directory then it will be
 * assumed that the first file name is a mount point residing off of the top-most
 * directory (a.k.a root dir). If filename does not match the string pattern of
 * any mount name stored in the system mount table then it will be assumed
 * that the identified first file name is not a file or directory that exist. The
 * behavior that follows will be dtermined by mode (an FS owned private mount table called
 * SYS_FS_pMountRec contains a list of mount points and their associated device).
 *
 * Here are some examples of first file names.
 * filename = "File1"         First file name is File1
 * filename = "/File1"        First file name is File1
 * filename = "./File1"       First file name is File1
 * filename = "File2/File1"   First file name is File2
 * filename = "/File2/File1"  First file name is File2
 * filename = "./File2/File1" First file name is File2
 * filename = "../File1"      First file name is ..
 * filename = "../File1"      First file name is ..
 * filename = "../File1"      First file name is ..
 *
 * The logic abstracted from the above use cases are:
 * If SYS_FS_CHAR is the first character in filename, then SYS_FS_CHAR will be translated to mean
 * that the filename that follows resides at the root directory.
 *
 * The very first file system to be mounted must be mounted at SYS_FS_CHAR.
 *
 * Subsequent file systems of the same type can be mounted together to form complex
 * file tree structures. However, all branches of a file system tree must be of
 * the same file system type.
 *
 * File systems of different types must start always start at SYS_FS_CHAR.
 *
 * If "." appears as the first char in filename then "/" must be the second.
 * The character sequence "./" will be interpreted to mean that the filename that
 * follows "/" resides in the cur directory. In other words "./" is synonymous with
 * the current working directory (captured in SYS_FS_sGcwd).
 *
 * If '..' appears as the first two chars in filename then the third character must
 * be SYS_FS_CHAR The character sequence "../" will mean that the filename that follows
 * resides in the directory one level above the current working directory.
 *
 * The final set of characters in filename can never be "..", '.' or SYS_FS_CHAR
 *
 * If filename does not contain "..", "." or SYS_FS_CHAR, the filename is the name of the file.
 *
 * All characters following the last SYS_FS_CHAR represent the file of interest.
 *
 * All character preceding the last SYS_FS_CHAR represent the directory path and or mount
 *  point where the file of interest resides.
 *
 * The delimiters "..", "." and SYS_FS_CHAR are not concepts belonging to any file system
 * that FS supports but are interpreted by the FS frame work to have specific meaning
 * (i.e. they are not recorded on the media as part of a filename). In the future
 * when OS support is provided, other delimiters of choice will be selected by the
 * resident kernel.
 *
 *                +++++++++++++++++++++ NOTE ++++++++++++++++++++
 * 
 * NOTE: This file has stub code for the MDD file system. However, that stub code
 * (surounded with with #ifdef SYS_FS_FILESYSTEM_MDD ) has not be tested not has it
 * even been compiled. It is included only as a place holder for when MDD is
 * integrated.
*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <fcntl.h>

#include "system/fs/sys_fs.h"
#include "system/fs/mpfs2.h"
#include "system/fs/mdd_fs.h"
#include "system/fs/system_fs_private.h"
#include "system/system_services.h"

#include "system_config.h"
#include "sys_fs_config.h"

#if defined (SYS_FS_ENABLE)

static void SYS_FS_ExtractFirstFilename(const char *filepath, char * buffer,int32_t len);
static int32_t SYS_FS_NextDescriptorGet(char *fsName);
static int32_t SYS_FS_DescriptorNameGet(int32_t desc, char *fsName);
static int32_t SYS_FS_DescriptorIndexGet(int32_t filedes, char *fsName);
static int32_t SYS_FS_Loc2SysDesc(int32_t desc, char *fs);
static int32_t SYS_FS_Sys2LocDesc(int32_t desc, char *fs);

int32_t SYS_FS_FileTypeGet(const char *path);
uint32_t SYS_FS_mpfs2fs_ArrayGet(MPFS_HANDLE hMPFS, uint8_t* cData, uint32_t wLen);

// Move all of the following statics into the SYS_FS_FILE_DESC_t type
static int32_t SYS_FS_nMounts=0; // Total number of devices
static SYS_FS_MOUNT_REC_t *SYS_FS_pMountRec=0;
static char SYS_FS_sGcwd[SYS_FS_MAX_DRIVE+SYS_FS_MAX_PATH];     // Current working directory of active user
static char SYS_FS_sGdefcwd[SYS_FS_MAX_DRIVE+SYS_FS_MAX_PATH];  // working directory at boot
static SYS_FS_t SYS_FS_Recs;
static  void SYS_FS_GenError(char *file, int32_t ln);



//////////////////////////////// MPFS to FS private mappings ///////////////////
// SYS_FS = File System - A very non-creative name for the file system abstraction layer
// The following functionality are the middle layer API which is private to the user space.
// This middle layer acts as wrapper to the mpfs2 filesystem and is meant to be called by a public
//level interface such as the ANSI/POSIC compliant API listed above.
#ifdef SYS_FS_FILESYSTEM_MPFS // If MPFS file system is supported. Defined in bsp_profile/system_profile.h

bool        SYS_FS_mpfs2fs_Init(void){return MPFSInit();}
void        SYS_FS_mpfs2fs_Deinit(void){ MPFSDeinit();}
MPFS_HANDLE SYS_FS_mpfs2fs_Open(const char* cFile){return MPFSOpen((const uint8_t*)cFile);}
MPFS_HANDLE SYS_FS_mpfs2fs_OpenID(uint16_t hFatID){return MPFSOpenID(hFatID);}
void        SYS_FS_mpfs2fs_Close(MPFS_HANDLE hMPFS){MPFSClose(hMPFS);}

bool        SYS_FS_mpfs2fs_Get(MPFS_HANDLE hMPFS, uint8_t* c){return MPFSGet(hMPFS,c);}
uint32_t    SYS_FS_mpfs2fs_ArrayGet(MPFS_HANDLE hMPFS, uint8_t* cData, uint32_t wLen){return MPFSGetArray(hMPFS, cData, wLen);}
bool        SYS_FS_mpfs2fs_LongGet(MPFS_HANDLE hMPFS, uint32_t* ul){ return MPFSGetLong(hMPFS, ul);}

bool        SYS_FS_mpfs2fs_Seek(MPFS_HANDLE hMPFS, uint32_t dwOffset, MPFS_SEEK_MODE tMode){return MPFSSeek( hMPFS,  dwOffset, tMode);}
MPFS_HANDLE SYS_FS_mpfs2fs_Format(void){return MPFSFormat();}

uint32_t    SYS_FS_mpfs2fs_ArrayPut(MPFS_HANDLE hMPFS, uint8_t* cData, uint32_t wLen){return MPFSPutArray( hMPFS, cData, wLen);}
bool        SYS_FS_mpfs2fs_PutEnd(MPFS_HANDLE hMPFS, bool final){return MPFSPutEnd(hMPFS, final);}

uint32_t    SYS_FS_mpfs2fs_TimestampGet(MPFS_HANDLE hMPFS){return MPFSGetTimestamp(hMPFS);}
uint32_t    SYS_FS_mpfs2fs_MicrotimeGet(MPFS_HANDLE hMPFS){return MPFSGetMicrotime(hMPFS);}
uint16_t    SYS_FS_mpfs2fs_FlagsGet(MPFS_HANDLE hMPFS){ return MPFSGetFlags(hMPFS);}
uint32_t    SYS_FS_mpfs2fs_SizeGet(MPFS_HANDLE hMPFS){return MPFSGetSize(hMPFS);}
uint32_t    SYS_FS_mpfs2fs_BytesRemGet(MPFS_HANDLE hMPFS){return MPFSGetBytesRem(hMPFS);}
MPFS_PTR    SYS_FS_mpfs2fs_StartAddrGet(MPFS_HANDLE hMPFS) {return MPFSGetStartAddr( hMPFS);}
MPFS_PTR    SYS_FS_mpfs2fs_EndAddrGet(MPFS_HANDLE hMPFS){return MPFSGetEndAddr( hMPFS);}
bool        SYS_FS_mpfs2fs_FilenameGet(MPFS_HANDLE hMPFS, uint8_t* cName, uint16_t wLen){return MPFSGetFilename( hMPFS, cName,  wLen);}
uint32_t    SYS_FS_mpfs2fs_PositionGet(MPFS_HANDLE hMPFS){return MPFSGetPosition( hMPFS);}

uint16_t    SYS_FS_mpfs2fs_IDGet(MPFS_HANDLE hMPFS){ return MPFSGetID( hMPFS);}

#endif // end SYS_FS_FILESYSTEM_MPFS

#ifdef SYS_FS_FILESYSTEM_MDD
bool SYS_FS_mddfs_Init(void) {return FSInit();}
MDDFS_HANDLE SYS_FS_mddfs_Open(const char* cFile, const char *mode) {return FSfopen(cFile, mode);}
int32_t SYS_FS_mddfs_Close(MDDFS_HANDLE cFile) {return FSfclose(cFile);}
uint32_t SYS_FS_mddfs_Read(void * ptr, size_t size, size_t n, MDDFS_HANDLE cFile) {return FSfread(ptr, size, n, cFile);}
int32_t SYS_FS_mddfs_Seek(MDDFS_HANDLE cFile, off_t offset, int32_t whence) {return FSfseek(cFile, offset, whence);}
uint32_t SYS_FS_mddfs_Tell(MDDFS_HANDLE cFile) {return FSftell(cFile);}
#endif

/////////////////////////// ANSI/POSIX-like API /////////////////////
/*************************** SYS_FS_ExtractFirstFilenameDEF ******************
 * at the file header to understand "first file name"
 * A contiguous set of string character beginning at the first byte up to and
 * excluding any present SYS_FS_CHAR (except if the SYS_FS_CHAR is the first char)
 * shall be known throughout this document as the "first file name".
 * If SYS_FS_CHAR is the first char in filepath and other characters
 * follow , SYS_FS_CHAR will be ignored.
 * If SYS_FS_CHAR is the first and only char in filepath then buffer will be
 * set to SYS_FS_CHAR.
 * PARAMS -  filepath - A null terminated string containing a directory or
 *           file path of interest.
 *           buffer - A pointer to an an allocated block of memory used to
 *                    store the extracted first file name
 *           len (input) max number of chars to copy to buffer
 *
 * Here are some examples of first file names.
 * filename = "File1"         First file name is "File1"
 * filename = "/File1"        First file name is "File1"
 * filename = "./File1"       First file name is "File1"
 * filename = "File1/File2"   First file name is "File1"
 * filename = "/File1/File2"  First file name is "File1"
 * filename = "./File1/File2" First file name is "File1"
 * filename = "../File1"      First file name is ".."
 * filename = "../File1"      First file name is ".."
 * filename = "../File1"      First file name is ".."
 * filename = ".File1"        error
 * filename = "..File1"       error
 * filename = "..."
 * filename = "//"            error
 *
*******************************************************************************/
static void SYS_FS_ExtractFirstFilename(const char *filepath, char * buffer,int32_t len)
{
   char *ptr = 0;
   int pathLen;

   // Consider the example path "/MyDriver1"
   // Locate the first file separator in filepath (the SYS_FS_CHAR in this example)
   ptr=strchr(filepath,SYS_FS_CHAR); // FS is defined in system_profile.h

   if(ptr==0) // SYS_FS_CHAR not found
   {   // If there is no SYS_FS_CHAR in filepath, then assume all char in filepath
       // represent the "first file name"
       pathLen=strlen(filepath);
       strncpy(buffer,filepath,len);
       *(buffer+pathLen+1)=0;
       return; // All char within filepath belong to a single file
   }
   else if(( *(filepath+0) == SYS_FS_CHAR) && ( *(filepath+1) == 0))
   {
       // SYS_FS_CHAR is the only char so return it as the first file name
       strncpy(buffer,SYS_FS_STRING,strlen(SYS_FS_STRING));
       *(buffer+strlen(SYS_FS_STRING)+1)=0;
   }
   else
   {
       // The first occurence of SYS_FS_CHAR was found and other filename chars 
       // follow so calc the length of the remaining chars
       pathLen = strlen(ptr+1);
       strncpy(buffer,ptr+1,SYS_FS_MAX_PATH); //Isolate chars following SYS_FS_CHAR
       *(buffer+pathLen)=0; 
   }
}

/*************************** SYS_FS_IsLegalDirStringDEF ***********************
 * Description:
 * Determines if buffer contains any characters which are not supported by
 * FS directory names.
 * PARAMS: buffer - A null terminated string of characters representing a dir name
 *         len - the size in bytes of the memory pointed to by buffer
 *
 * Return: RETURN_SUCCESS if no error.
 *         On error returns the ASCII value of the offending character.
*******************************************************************************/
int32_t SYS_FS_IsLegalDirString(const char * buffer,int32_t len)
{
    int i;

    for(i=0;i<len;i++)
    {
        // Character sequence "//" is not allowed
        if( (*(buffer+i)==SYS_FS_CHAR) && (*(buffer+i+1)==SYS_FS_CHAR) )
            return (SYS_FS_CHAR);      // OK for directory but not filename

        // A '.' character cannot be followed by a character in a filename. It
        // can only be followed by a character that is legal in a directory name
        // Essentially this means that only '.' and SYS_FS_CHAR are allowed.
        if((*(buffer+i)=='.') &&
             SYS_FS_IsLegalDirString((buffer+i+1),strlen(buffer+i+1)))
        {
            return (*(buffer+i+1));      // OK for directory but not filename
        }
        if(SYS_FS_IsLegalDirChar(*(buffer+i)))
            return *(buffer+i); //index of first illegal character
    }
    return RETURN_SUCCESS; // All characters in buffer are OK
}


/*************************** SYS_FS_IsLegalFileStringDEF ***********************
 * Description:
 * Determines if buffer contains any characters which are not supported by
 * FS file names.
 * PARAMS: buffer - A null terminated string of characters representing a dir name
 *         len - the size in bytes of the memory pointed to by buffer
 *
 * Return: RETURN_SUCCESS if no error.
 *         On error returns the ASCII value of the offending character.
*******************************************************************************/
int32_t SYS_FS_IsLegalFileString(const char * buffer,int32_t len)
{
    int i;

    for(i=0;i<len;i++)
    {
        if(SYS_FS_IsLegalFileChar(*(buffer+i)))
           return *(buffer+i); //index of first illegal character
        // The sequence ".." is not a legal file name
        else if((*(buffer+i)=='.') && (*(buffer+i+1)=='.'))
             return *(buffer+i); //index of first illegal character
    }
    return RETURN_SUCCESS; // All characters in buffer are OK
}

/************************** SYS_FS_IsLegalFileCharDEF **************************
 * Description:
 * The characters SYS_FS_CHAR is illegal as are all characters that are not
 * valid characters within a directory name
 * Returns RETURN_SUCCESS if the character within buf is legal. 
 * Returns RETURN_FAILED if buf is an illegal character
 *******************************************************************************/
int32_t SYS_FS_IsLegalFileChar(const char buf)
{

    if(buf==SYS_FS_CHAR)
        return (SYS_FS_CHAR);      // OK for directory but not filename

      SYS_FS_IsLegalDirChar(buf);
      
     return RETURN_SUCCESS;
}

/************************** SYS_FS_IsLegalDirCharDEF ***************************
 * Description:
 * All characters between and including ASCII values 0x20 and 0x5f are legal.
 * Returns RETURN_SUCCESS if the character within buf is legal.
 * Returns RETURN_FAILED if buf is an illegal character
 *  ***************************************************************************/
int32_t SYS_FS_IsLegalDirChar(const char buf)
{
      if(buf < 0x20 || buf>0x7e)
      {
          SYS_FS_GenError(__FILE__,__LINE__);
          return RETURN_FAILED;
      }
     return RETURN_SUCCESS;
}

/************************** SYS_FS_ExtractFilenameDEF **************************
 * Description:
 * Given that filepath is a null terminated string representing a file name
 * appended to at least one directory name, buffer will be populate with
 * the filename portion of filepath.
 * Params
 *        filepath - A full pathname of a file
 *        buffer - A pointer to an allocated area of memory large enough to
 *                 hold the filename portion of filepath. Upon completion
 *                 buffer will contain a null terminated string of characters
 *                 representing a filename
 *        len      The total number of bytes allocated to buffer.
 *  Return:
 *         None
 *  ***************************************************************************/
void SYS_FS_ExtractFilename(const char *filepath, char * buffer,int32_t len)
{
   // locate end of path, which is the last slash in filepath
   char *ptr = 0;
   int PathLen;

   if(SYS_FS_IsBadString(filepath, len))
      return;

   ptr= strrchr(filepath,SYS_FS_CHAR); // FS is defined in system_profile.h

   if(ptr==0) //No FS delimiter,
   {   //Assume filepath is the name of the file
       PathLen=strlen(filepath);
       strncpy(buffer,filepath,len-1);
       *(buffer+PathLen)=0; // This works OK
   } 
   else //SYS_FS_CHAR delimiter was found. Copy remainder of string that follows SYS_FS_CHAR
   {
       PathLen=strlen(ptr+1);
       strncpy(buffer,ptr+1,len-1); // FS delimiter was found. Remaining string is
                                   // the name of a file (or local directory)
       *(buffer+PathLen)=0;// This works OK
   }
}

/************************** SYS_FS_IsBadStringDEF **************************
 * Description:
 * Checks the str pointer to make sure it is not null.
 * Checks str to make sure that it is not an emptry string
 * Checks for pointer a null terminator
 * Params:
 *        str - A pointer to memory to validate the string properties.
 *        len - Len of memory pointed to by str
 * Return:
 *         1 = Pointer is NULL
 *         2 = String is empty
 *         3 = No terminator found within len bytes from start of str
 *  ***************************************************************************/
int SYS_FS_IsBadString(const char *str,int len)
{
   int i;
   bool nullFound=false;

   if(str!=(const char*)0) // Good/Bad pointer?
   {
       if(*(str+0)==(char)0)     // NULL string
       {
          return 2; // String is empty
       }
   }
   else
       return 1; //Pointer is NULL


   // Check for null terminator
   for(i=0;i<=len;i++)
       if(*(str+i)==(char)0)
       {
         nullFound=true;
         break;
       }

   if(!nullFound)
       return 3; //No terminator found

   return 0;     // A OK
}

/************************** SYS_FS_ExtractPathnameDEF **************************
 * Description:
 * Given that filepath is a null terminated string representing a file name
 * appended to at least one directory name, buffer will be populate with
 * the file path portion of filepath minus the file name.
 * Params:
 *        filepath - A full path name of a file
 *        buffer - A pointer to an allocated area of memory large enough to
 *                 hold the pathname portion of filepath. Upon completion
 *                 buffer will contain a null terminated string of characters
 *                 representing filepath with the filename removed.
 *        len      The total number of bytes allocated to buffer.
 * Return:
 *         None
 *  ***************************************************************************/
void SYS_FS_ExtractPathname(const char *filepath, char * buffer,int32_t len)
{
   int pathLen;
   char filename[SYS_FS_MAX_FNAME+SYS_FS_MAX_EXT];
   char *ptr = 0;

   if(SYS_FS_IsBadString(filepath, len))
      return;

   // locate end of path, which is the last slash in filepath
   ptr= strrchr(filepath,SYS_FS_CHAR); // FS is defined in system_profile.h
   if(ptr==0)
   {   // If there is no FS delimiter, then assume filepath is the name of the file
       pathLen=strlen(filepath);
       strncpy(buffer,filepath,len-1);
       *(buffer+pathLen)=0; 
       return;
   }

   // Obtain the file name so that we can use it in pattern matching
   strncpy(filename,ptr+1,SYS_FS_MAX_FNAME+SYS_FS_MAX_EXT);

   //Now that we have the file name located within filename, use filename
   //in the strstr as the pattern matching criteria.
   ptr=strstr(filepath, filename);

   //The length is pathname minus the length of the filename
   if (ptr==0) {
       pathLen = strlen(filepath);
   } else {
       pathLen = strlen(filepath) - strlen(ptr);
   }

   //Copy only the pathname
   strncpy(buffer,filepath,pathLen);
   *(buffer+pathLen)=0; // Working OK
}


/****************************** SYS_FS_openDEF *********************************
 * Function:
 *         int32_t SYS_FS_open(const char *pathname, int32_t oflag, ...)
 *
 * Summary:
 * Provides an FS aware wrapper around the open() command, thus providing the
 * ability to perform file access on name regardless of what file system and
 * media are used to store name. It examines the string pattern of name
 * for clues that can be used to determine what device and file system are
 * used name. Although the file system type and device are not part of the name
 * the string pattern of name can be used to reference FS state info that can
 * ultimatley determine that type of info
 *
 * Description:
 * Directories are files.
 * A complete file name such as MyFile1/MyFile2/Somefile.txt? has multiple filename
 * entries that complete the filename path.
 * A contiguous set of string character beginning at the first byte up to and
 * excluding any present file separator shall be known throughout this document
 * as the first file name.
 * If first file name cannot be found in the current directory then it will be
 * assumed that the first file name is a mount point residing off of the top-most
 * directory (a.k.a root dir). If filename does not match the string pattern of
 * any mount name stored in the system mount table then it will be assumed
 * that filename does not exist and follow the behavior appropriate for mode (an
 * FS owned private mount table called SYS_FS_pMountRec contains a list of  mount
 * points and their associated device).

 * Example: If name="email/index.htm", this function will determine if "email" is
 * a name of a folder or a mount name. If it is not the name of a mount name, then
 * is will assume that it is the name of a folder. It will then proceed to looking
 * at "index.htm" and assume that is the name of the file to open.
 *
 * Parameters:
 *             name - A null terminated string sequence representing a full file 
 *             path or relative file path of a file to open.
 * 
 * Returns: A file handle generated by the underlying fs on success
 *         assocaited with the file is not supported.
 *         errno set to ENOENT iff the file could not be found.
 *         errno set to EINVAL if the filepath contains an illegal character
 *
 ******************************************************************************/
int32_t SYS_FS_open(const char *name, int32_t oflag, ...)
{
    int32_t i;
    int32_t fsIndex=RETURN_FAILED;
    char FSType[9];
    int32_t hFile;
    int32_t FileType;
#ifdef SYS_FS_FILESYSTEM_MDD
    char *pMode;
#endif
    char Pathname[SYS_FS_MAX_PATH+1];
    char Filename[SYS_FS_MAX_FNAME+SYS_FS_MAX_EXT+1];
    char FirstFilename[SYS_FS_MAX_PATH+1]; // First file name may be a dir which 
                                           // can be longer than SYS_FS_MAX_FNAME
                                           // which is why SYS_FS_MAX_PATH is used

    Pathname[0]=Filename[0]=FirstFilename[0]=0;

    if( SYS_FS_IsLegalDirString(name,strlen(name)))
    {
        SYS_FS_GenError(__FILE__,__LINE__);
        errno=EINVAL;
        return RETURN_FAILED; 
    }

    // Filename = Extract the Filename, Pathname and FirstFileName
    SYS_FS_ExtractFilename(name,Filename,SYS_FS_MAX_FNAME+SYS_FS_MAX_EXT);

    if( SYS_FS_IsLegalFileString(Filename,strlen(Filename)))
    {
       errno=EINVAL;
       SYS_FS_GenError(__FILE__,__LINE__);
       return RETURN_FAILED; // File not found
    }
    SYS_FS_ExtractPathname(name,Pathname,SYS_FS_MAX_PATH);
    SYS_FS_ExtractFirstFilename(name,FirstFilename,SYS_FS_MAX_PATH);

    //Find out it FirstFilename a file, dir or mount point?
    FileType=SYS_FS_FileTypeGet(FirstFilename);

    switch(FileType)
    {
        case SYS_FS_DATAFILE: // Use the current directory to obtain the FS
                              // type used to store the file
            SYS_FS_FSFromCWD(FSType);
        break;
        case SYS_FS_MOUNT_LABEL:  // Use the mount name to obtain the file system
                                  // type used to store the file.
            SYS_FS_FSFromMountName(FirstFilename,FSType);
        break;
        default:
            SYS_FS_GenError(__FILE__,__LINE__);
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(FSType,"mpfs2",8)==0)  // if filesystem type is MPFS
    {
       // Try MyFileName first, Note, MPFS has only one directory, so just using name
       if((hFile=SYS_FS_mpfs2fs_Open(name))==MPFS_INVALID_HANDLE)
       {
           // Try ./MyFileName and /MyFileName as an alternatives
           //if((hFile=SYS_FS_mpfs2fs_Open(Filename))==MPFS_INVALID_HANDLE)
           {
              errno=ENOENT;
              SYS_FS_GenError(__FILE__,__LINE__);
              return RETURN_FAILED; // File not found
           }
       }

       // Search for the filesstem type mpfs2 within the descriptor tables
       for(i=0;i<SYS_FS_Recs.nFileSystems;i++)
       {
         // The descriptor table for mpfs2 was found.
         fsIndex=SYS_FS_NextDescriptorGet("mpfs2");
         if(fsIndex==RETURN_FAILED)
         {
             SYS_FS_GenError(__FILE__,__LINE__);
              break; // Error is set by SYS_FS_NextDescriptorGet
         }
         else
         {
            *((*(SYS_FS_Recs.ppfs+i))->fd+fsIndex)= SYS_FS_Loc2SysDesc(hFile,"mpfs2");
            return(*((*(SYS_FS_Recs.ppfs+i))->fd+fsIndex)); // Return sys desc value
         }
       }
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    switch (oflag) {
        case 0:                    
        case SYS_FS_IO_INTENT_READ:// Read only
            pMode = FS_READ;
            break;
        case SYS_FS_IO_INTENT_WRITE: // Write
            pMode = FS_WRITE;
            break;
        case SYS_FS_IO_INTENT_READWRITE: // Read & Write
            pMode = FS_READPLUS;
            break;
        default: // Default as read
            pMode = FS_READ;
            break;
    }
    if(strncmp(FSType,"mdd",8)==0)  // if filesystem type is MDD
    {
       // Try MyFileName first
       if((hFile=(uint32_t)SYS_FS_mddfs_Open(Filename, pMode))==MDD_INVALID_HANDLE)
       {
           // Try ./MyFileName and /MyFileName as an alternatives
           if((hFile=(uint32_t)SYS_FS_mddfs_Open(name, pMode))==MDD_INVALID_HANDLE)
           {
              errno=ENOENT;
              SYS_FS_GenError(__FILE__,__LINE__);
              return RETURN_FAILED; // File not found
           }
       }

       // Search for the filesstem type mdd within the descriptor tables
       for(i=0;i<SYS_FS_Recs.nFileSystems;i++)
       {
         // The descriptor table for mdd was found.
         fsIndex=SYS_FS_NextDescriptorGet("mdd");
         if(fsIndex==RETURN_FAILED)
         {
             SYS_FS_GenError(__FILE__,__LINE__);
              break; // Error is set by SYS_FS_NextDescriptorGet
         }
         else
         {
            *((*(SYS_FS_Recs.ppfs+i))->fd+fsIndex)= SYS_FS_Loc2SysDesc(hFile,"mdd");
            return(*((*(SYS_FS_Recs.ppfs+i))->fd+fsIndex)); // Return sys desc value
         }
       }
    }
#endif
    return fsIndex;
}


/****************************** SYS_FS_closeDEF ********************************
 * Description: Close a file that has been opend by SYS_FS_open()
 *
 * Params: filedes  - a file descriptor returned by SYS_FS_open()
 *
 * Return:
 *         Returns RETURN_SUCCESS if no errors were detected
 *         Upon error returns -1 and sets the global variable errno to a value
 *         the indicates the cause of the error.
 *         The var errno is set to EBADF if the descriptor is not valid.
 *         The var errno is set to SYS_FS_MEDIA_UNKNOWN if the media type is not
 *         recognized.
 ******************************************************************************/
int32_t SYS_FS_close (int32_t filedes)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t desc;
    int32_t i, findex;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        SYS_FS_GenError(__FILE__,__LINE__);
        errno=EBADF; // Bad file number
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mpfs2");

        for(i=0;i<SYS_FS_Recs.nFileSystems;i++)  // For each file system
        {
            // Is this an MPFS2 file system?
            if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mpfs2",SYS_FS_MAX_DRIVE)==0) 
                break; // found the MPFS descriptor table at index i
        }
        findex = SYS_FS_DescriptorIndexGet(desc, "mpfs2");
        *((*(SYS_FS_Recs.ppfs+i))->fd+findex)=0; // invalidate the descriptor
        SYS_FS_mpfs2fs_Close(desc);
        return RETURN_SUCCESS;
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MDD descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        
        for(i=0;i<SYS_FS_Recs.nFileSystems;i++)  // For each file system
        {
            // Is this an MPFS2 file system?
            if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mdd",SYS_FS_MAX_DRIVE)==0)
                break; // found the MDD descriptor table at index i
        }
        findex = SYS_FS_DescriptorIndexGet(desc, "mpfs2");
        *((*(SYS_FS_Recs.ppfs+i))->fd+findex)=0; // invalidate the descriptor
        SYS_FS_mddfs_Close((MDDFS_HANDLE)desc);
        return RETURN_SUCCESS;
    }
#endif
    SYS_FS_GenError(__FILE__,__LINE__);
    errno=SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
    return -1;
}



/**************************** SYS_FS_Loc2SysDescDEF ****************************
 * Description:
 * This function converts a file descriptor created by an underlying
 * file system & converts it to a descriptor value that is unique through the
 * system. This prevents the FS from using identical file descriptors created by
 * two or more file systems.
 *
 * Params:
 *         desc - A file descriptor returned by SYS_FS_open(). This descriptor
 *                will converted and returned as a unique descriptor value.
 *         fs   - The file system type that generated desc.
 * Return:
 *        A system wide unique file descriptor to be used in other FS calls
 *        SYS_FS_MEDIA_UNKNOWN if fs is not a recognized file system
 *
 ******************************************************************************/
static int32_t SYS_FS_Loc2SysDesc(int32_t desc, char *fs)
{
#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
        return desc;
#endif
    
#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
        return desc+=1000;
#endif
    SYS_FS_GenError(__FILE__,__LINE__);
    return SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
}


/**************************** SYS_FS_Sys2LocDescDEF ****************************
 * Description:
 * This function converts file descriptor created by SYS_FS_Loc2SysDesc()
 * back to the native file system descriptor value.
 *
 * Params:
 *         desc - A file descriptor generated by SYS_FS_Loc2SysDesc().
 *                This descriptor will converted back to its original
 *                descriptor value.
 *         fs   - The target file system type.
 *
 * Return:
 *        A system wide unique file descriptor to be used in other FS calls
 *        SYS_FS_MEDIA_UNKNOWN if fs is not a recognized file system
 ******************************************************************************/
static int32_t SYS_FS_Sys2LocDesc(int32_t desc, char *fs)
{
    // MPFS Numbers are stored unconverted by FS
#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        if(desc>0 && desc<=1000)
            return desc;
    }
#endif

    // MDD Numbers are stored converted by adding a 1000 to the value.
    // This keeps number from clashing with MFPS and other file systems
#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        if((uint32_t)desc>1000 )//(desc>1000 && desc<=2000)
            return desc - 1000;
    }
#endif
    SYS_FS_GenError(__FILE__,__LINE__);
    return SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
}


/**************************** SYS_FS_Sys2LocDescDEF ****************************
 * Description:
 *        Returns the next available file descriptor
 *
 * Params:
 *         fsName - A null termianted string representing the file system type
 *                  that the decriptor should be obtained from.
 * Return:
 *        The next unused descriptor slot within the descriptor table
 *        Sets the global variable errno and returns RETURN_FAILED on error
 *        The global variable errno is set to SYS_FS_MEDIA_UNKNOWN if the file
 *        system type identified in fsName is not supported.
 *
 ******************************************************************************/
static int32_t SYS_FS_NextDescriptorGet(char *fsName)
{
    int32_t i;
    int32_t index;
    int32_t nMaxHandles;

    for(i=0;i<SYS_FS_Recs.nFileSystems;i++)  // For each file system
    {
#ifdef SYS_FS_FILESYSTEM_MPFS
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mpfs2",SYS_FS_MAX_DRIVE)==0)
            nMaxHandles = MAX_MPFS_HANDLES;
#endif
#ifdef SYS_FS_FILESYSTEM_MDD
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mdd",SYS_FS_MAX_DRIVE)==0)
            nMaxHandles = FS_MAX_FILES_OPEN;
#endif
       // Do not allow the local file system descriptor limites to
       // exceed the system imposed limites.
       if(nMaxHandles>SYS_FS_MAX_DESCRIPTORS)
            nMaxHandles=SYS_FS_MAX_DESCRIPTORS;

       // Search for fsName within the descriptor tables
       if(strcmp((*(SYS_FS_Recs.ppfs+i))->fsName,fsName)==0)
       {
          // Found the filesystem descriptor table for fsName
          // Now find an available descriptor record
          for(index=0;index<nMaxHandles;index++)
          {
             if(*((*(SYS_FS_Recs.ppfs+i))->fd+index)==0)
                 return index; // found one
          }
       }
    }
    errno = SYS_FS_MEDIA_UNKNOWN;
    return RETURN_FAILED; // not a recognized file system
}

/************************ SYS_FS_DescriptorIndexGetDEF *************************
 * Description:
 *        Returns file index of specified file handle
 *
 * Params:
 *         filedes - File handle
 *         fsName - A null termianted string representing the file system type
 *                  that the decriptor should be obtained from.
 * Return:
 *        The file index of specified file handle, which is hold in the memory
 *        pointed by fd in struct SYS_FS_FILE_DESC_t
 *
 ******************************************************************************/
static int32_t SYS_FS_DescriptorIndexGet(int32_t filedes, char *fsName)
{
    int32_t i;
    int32_t index;
    int32_t nMaxHandles;

    for(i=0;i<SYS_FS_Recs.nFileSystems;i++)  // For each file system
    {
#ifdef SYS_FS_FILESYSTEM_MPFS
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mpfs2",SYS_FS_MAX_DRIVE)==0)
            nMaxHandles = MAX_MPFS_HANDLES;
#endif
#ifdef SYS_FS_FILESYSTEM_MDD
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mdd",SYS_FS_MAX_DRIVE)==0)
            nMaxHandles = MAX_MPFS_HANDLES;
#endif
       // Do not allow the local file system descriptor limites to
       // exceed the system imposed limites.
       if(nMaxHandles>SYS_FS_MAX_DESCRIPTORS)
            nMaxHandles=SYS_FS_MAX_DESCRIPTORS;

       // Search for fsName within the descriptor tables
       if(strcmp((*(SYS_FS_Recs.ppfs+i))->fsName,fsName)==0)
       {
          // Found the filesystem descriptor table for fsName
          // Now find an available descriptor record
          for(index=0;index<nMaxHandles;index++)
          {
             if(*((*(SYS_FS_Recs.ppfs+i))->fd+index)==filedes)
                 return index; // found one
          }
       }
    }
    errno = SYS_FS_MEDIA_UNKNOWN;
    return RETURN_FAILED; // not a recognized file system
}

/*************************** SYS_FS_DescriptorNameGetDEF ***********************
 * Description:
 *            Given a descriptor name,  returns the file system name
 *            associated with that descriptor.
 *
 * Params: desc   - A file descriptor returned by SYS_FS_Loc2SysDesc()
 *         fsName - A null terminated string representing the file system type
 *                  of interest.
 * return SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
 *
 ******************************************************************************/
static int32_t SYS_FS_DescriptorNameGet(int32_t desc, char *fsName)
{
    int32_t i;
    int32_t index;
    int32_t nMaxHandles;

    for(i=0;i<SYS_FS_Recs.nFileSystems;i++)  // For each file system
    {
#ifdef SYS_FS_FILESYSTEM_MPFS
        // Is this an MPFS2 file system?
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mpfs2",SYS_FS_MAX_DRIVE)==0) 
            nMaxHandles = MAX_MPFS_HANDLES;
#endif
#ifdef SYS_FS_FILESYSTEM_MDD
        if(strncmp((*(SYS_FS_Recs.ppfs+i))->fsName,"mdd",SYS_FS_MAX_DRIVE)==0)
            nMaxHandles = FS_MAX_FILES_OPEN;
#endif
        // Do not allow the local file system descriptor limites to
        // exceed the system imposed limites.
        if(nMaxHandles>SYS_FS_MAX_DESCRIPTORS)
            nMaxHandles=SYS_FS_MAX_DESCRIPTORS;

        for(index=0;index<nMaxHandles;index++)
        {
           if(*((*(SYS_FS_Recs.ppfs+i))->fd+index)==desc)
           {
              strncpy(fsName,(*(SYS_FS_Recs.ppfs+i))->fsName,SYS_FS_MAX_DRIVE); // found one
              return RETURN_SUCCESS;
           }
        }
        return RETURN_FAILED; // Did find an available descriptor
    }
    return SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
}

/******************************** SYS_FS_fsize ******************************
 * Description:   The SYS_FS_fsize will return the size of specified file
 *
 * Params: filedes - A file descriptor returned by a call to SYS_FS_open
 * Return: file size or -1 if any error
 ******************************************************************************/
ssize_t SYS_FS_fsize(int32_t filedes)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t desc;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        errno=EBADF; // Bad file number
        SYS_FS_GenError(__FILE__,__LINE__);
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mpfs2");
        return SYS_FS_mpfs2fs_SizeGet((MPFS_HANDLE)desc);
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        return ((MDDFS_HANDLE)desc)->size;
    }
#endif
    SYS_FS_GenError(__FILE__,__LINE__);
    return -1; // not a recognized file system
}

/******************************** SYS_FS_ftell ******************************
 * Description:   The SYS_FS_ftell function will return the current position in
 *        the file handle 'filedes', which is used to keep track of the absolute
 *        location of the current position in the file.
 *
 * Params: filedes - A file descriptor returned by a call to SYS_FS_open
 * Return: Current location in the file or -1 if any error encountered
 ******************************************************************************/
ssize_t SYS_FS_ftell(int32_t filedes)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t desc;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        errno=EBADF; // Bad file number
        SYS_FS_GenError(__FILE__,__LINE__);
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mpfs2");
        return SYS_FS_mpfs2fs_PositionGet((MPFS_HANDLE)desc);
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        return SYS_FS_mddfs_Tell((MDDFS_HANDLE)desc);
    }
#endif
    
    SYS_FS_GenError(__FILE__,__LINE__);
    return -1; // not a recognized file system
}

/******************************** SYS_FS_fstat ******************************
 * Description:   The SYS_FS_fstat function will return the current position in
 *        the file handle 'filedes', which is used to keep track of the absolute
 *        location of the current position in the file.
 *
 * Params: filedes - A file descriptor returned by a call to SYS_FS_open
 *         buf  - Pointer to attribute struct
 * Return: -1 on failure/error
 ******************************************************************************/
int32_t SYS_FS_fstat(int32_t filedes, FILE_STAT *buf)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t desc;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        errno=EBADF; // Bad file number
        SYS_FS_GenError(__FILE__,__LINE__);
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mpfs2");
        if(SYS_FS_mpfs2fs_FlagsGet((MPFS_HANDLE)desc) & MPFS2_FLAG_ISZIPPED) {
            buf->st_attr = SYS_FS_ATTR_ZIP_COMPRESSED;
        } else {
            buf->st_attr = SYS_FS_ATTR_UNCOMPRESSED;
        }

        return 0;
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        buf->st_attr = SYS_FS_ATTR_UNCOMPRESSED; // Default to uncompressed file now for MDD file
        return 0;
    }
#endif
    
    SYS_FS_GenError(__FILE__,__LINE__);
    return -1; // not a recognized file system
}

/******************************** SYS_FS_readDEF ******************************
 * Description:   Reads a file that was previsously opened with SYS_FS_open()
 *
 * Params: filedes - A file descriptor returned by a call to SYS_FS_open
 *         buffer - A pointer to an allocated area of memory. This memory space
 *                  will be populated with the file contents read.
 *         size   - The maximum number of bytes to write to buffer.
 * Return: The number of bytes read or -1 on error.
 *         On error the global variable errno is set to EIO if there was some
 *         unrecognised error I/O error generated by the underlying file system.
 *         Errno is set to SYS_FS_MEDIA_UNKNOWN if filedes is not a recognized
 *         file system
 ******************************************************************************/
ssize_t SYS_FS_read(int32_t filedes, void *buffer, size_t size)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t ret;
    int32_t desc;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        errno=EBADF; // Bad file number
        SYS_FS_GenError(__FILE__,__LINE__);
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MPFS2 descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mpfs2");
        if((size==0) || (size==1))
           ret=SYS_FS_mpfs2fs_Get((MPFS_HANDLE)desc, (uint8_t*) buffer);
        else if(size>1)
           ret=SYS_FS_mpfs2fs_ArrayGet((MPFS_HANDLE)desc, (uint8_t*) buffer,size);
        if(ret==0)
        {
          errno=EIO; // I/O error. MPFS does not indicate why
          SYS_FS_GenError(__FILE__,__LINE__);
          return -1;
        }
        else return ret; // return the number of bytes read
    }
#endif
    
#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MDD descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        ret = SYS_FS_mddfs_Read((uint8_t*)buffer, 1, size, (MDDFS_HANDLE)desc);
        if(ret==0)
        {
          errno=EIO; // I/O error. MDDFS does not indicate why
          SYS_FS_GenError(__FILE__,__LINE__);
          return -1;
        }
        else return ret;// return the number of bytes read
    }
#endif
    SYS_FS_GenError(__FILE__,__LINE__);
    return SYS_FS_MEDIA_UNKNOWN; // not a recognized file system
}


/****************************** SYS_FS_FSFromCWDDEF ****************************
 * Description:   Get the file system type of the current working directory
 *
 * Params:
 *        FSType - A null terminated string containing the string ID of the
 *        file system of interest.
 * Return: RETURN_SUCCESS
 *         RETURN_FAILED - If FSType could not be associate with a mount name
 ******************************************************************************/
int32_t SYS_FS_FSFromCWD(char *FSType)
{
   char cwd[SYS_FS_MAX_PATH];
   char buffer[SYS_FS_MAX_PATH];
   int32_t i;

   strncpy(cwd,SYS_FS_sGcwd,SYS_FS_MAX_PATH);
   // CWD is /MyDrive1
   
   SYS_FS_ExtractFirstFilename(cwd, buffer,SYS_FS_MAX_PATH);

   for(i=0;i<SYS_FS_nMounts;i++)
   {
       // See if the FirstFilename within buffer matches a mount name
       if(strncmp(buffer,SYS_FS_pMountRec[i].mount_name,SYS_FS_MAX_DRIVE)==0)
       {
          // return the device type associated with the mount name
          strncpy(FSType,SYS_FS_pMountRec[i].cpFileSystemType,SYS_FS_MAX_DRIVE);
          return RETURN_SUCCESS;
       }
    }
   SYS_FS_GenError(__FILE__,__LINE__);
   return RETURN_FAILED;
}



/************************** SYS_FS_FSFromMountNameDEF **************************
 * Description:
 *             Search for mountName in the mount table. Populates FSType with the
 *             file system type (i.e "mpfs2") associated with mountName
 *
 * Params:
 *        mountName - A null terminted string representing a mount name
 *                    previously created by a call to SYS_FS_mount()
 *        FSType - A null terminated string containing the string ID of the
 *        file system of interest.
 * Return: RETURN_SUCCESS
 *         ENOENT if mountName is not found within the mount table
 ******************************************************************************/
int32_t SYS_FS_FSFromMountName(const char *mountName, char *FSType)
{
    int32_t i;

    for(i=0;i<SYS_FS_nMounts;i++)
    {
        // If media is found within the mount records
        if(strncmp(mountName,SYS_FS_pMountRec[i].mount_name,SYS_FS_MAX_DRIVE)==0)
        {
          // return the device type associated with the mount
          strncpy(FSType,SYS_FS_pMountRec[i].cpFileSystemType,8);
          return RETURN_SUCCESS;
        }
    }
   // SYS_FS_GenError(__FILE__,__LINE__);
    return ENOENT; // No such file or directory
}

/***************************** SYS_FS_FileTypeGetDEF ***************************
 * Description:
 *            Currently, the code assumes that all files are either mount
 * points or a proper file. The code below simulates interigating a file's
 * properies. It does so by making use of SYS_FS_FSFromMountName().
 * The code should be replaced with code that returns the file type by
 * actually interigating the file properies once they are coded.
 *
 * Params:
 *        path - A null terminated string containign a file path, directory or
 *               mount name.
 * Return: SYS_FS_DATAFILE if path is a data file or directory
 *         SYS_FS_MOUNT_LABEL if path is a mount name
 ******************************************************************************/
int32_t SYS_FS_FileTypeGet(const char *path)
{
    char FSType[9]="";

    SYS_FS_FSFromMountName(path,FSType);

    if(strncmp(FSType,"mpfs2",SYS_FS_MAX_DRIVE)==0)  // if filesystem type is MPFS
      return SYS_FS_MOUNT_LABEL;
    else return SYS_FS_DATAFILE;

    SYS_FS_GenError(__FILE__,__LINE__);
}



/******************************* FS_MountRecGetDEF *****************************
 * Description:
 *            Returns the mount record associated with a mount name
 *
 * Params:
 *        name - A null terminated string representing the name if a mount point
 *               that has been succfully mounted by calling SYS_FS_mount()
 *
 * Return: SYS_FS_DATAFILE if path is a data file or directory
 *         SYS_FS_MOUNT_LABEL if path is a mount name
 ******************************************************************************/
int32_t FS_MountRecGet(const char *name,SYS_FS_MOUNT_REC_t *rec)
{
   int32_t i;

   for(i=0;i<SYS_FS_nMounts;i++)
      if(strcmp(SYS_FS_pMountRec[i].mount_name,name)==0)
          *rec = SYS_FS_pMountRec[i];

   SYS_FS_GenError(__FILE__,__LINE__);
   return RETURN_FAILED;
}

int SYS_FS_fclose(FILE *fp){return RETURN_SUCCESS;}
int SYS_FS_fflush(FILE *fp){return RETURN_SUCCESS;}
int SYS_FS_fread(void *buffer,size_t size,size_t count,FILE *stream){return RETURN_SUCCESS;}
size_t	SYS_FS_fwrite(const void *buffer,size_t size,size_t count,FILE *stream ){return RETURN_SUCCESS;}
int SYS_FS_remove( const char *fname ){return RETURN_SUCCESS;}
char *SYS_FS_getcwd(const char *pathname,char *buf, size_t size){return RETURN_SUCCESS;}
int32_t SYS_FS_chdir(const char *path);



////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Non ANSI/POSIX like functions /////////////////////
// SYS_FS functionality which do not neccesarily have a ANSI/POSIX equivalent
////////////////////////////////////////////////////////////////////////////////


/**************************** SYS_FS_initializeDEF *****************************
 * Description:
 *           Prepares the virtual file system (FS) by allocating memory and
 *           initializing state descriptor tables
 *
 * Params:
 *        intData - null pointer to initializatio data values. Unused at this time
 *
 * Return: RETURN_SUCCESS
 ******************************************************************************/
int32_t SYS_FS_initialize(const void* const initData)
{
    int32_t index,i;
    int32_t fsTypes=0;
    int32_t nMaxHandles;

    SYS_FS_Recs.nFileSystems=0;

    SYS_FS_setdefdir(SYS_FS_STRING); // SYS_FS_STRING used as root directory
#ifdef SYS_FS_FILESYSTEM_MPFS
    SYS_FS_Recs.nFileSystems++;
    SYS_FS_mpfs2fs_Init();
    fsTypes |= _SYS_FS_MASK_MPFS;
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    SYS_FS_Recs.nFileSystems++;
    SYS_FS_mddfs_Init();
    fsTypes |= _SYS_FS_MASK_MDD;
#endif


#if defined( SYS_FS_FILESYSTEM_MPFS) || defined(SYS_FS_FILESYSTEM_MDD)
    // Allocate memory for the file descriptor tables
    SYS_FS_Recs.ppfs = (SYS_FS_FILE_DESC_t**) SystemMalloc(sizeof(SYS_FS_FILE_DESC_t*)*SYS_FS_Recs.nFileSystems);
#endif

#ifdef SYS_FS_FILESYSTEM_MPFS
    for(index=0;index<SYS_FS_Recs.nFileSystems;index++)
    {
       *(SYS_FS_Recs.ppfs+index) = (SYS_FS_FILE_DESC_t*) SystemMalloc(sizeof(SYS_FS_FILE_DESC_t));
        if(fsTypes && _SYS_FS_MASK_MPFS)
        {
            nMaxHandles = MAX_MPFS_HANDLES;

            // Do not allow the underlying files system more descriptors
            // than then the FS system can handle
            if(nMaxHandles>SYS_FS_MAX_DESCRIPTORS)
                nMaxHandles=SYS_FS_MAX_DESCRIPTORS;

            // Initialize the descriptors
             (*(SYS_FS_Recs.ppfs+index))->fd = (int32_t*)SystemMalloc(sizeof(int32_t)*nMaxHandles);
            for(i=0;i<nMaxHandles;i++)  // Set all descriptors to 0
                *((*(SYS_FS_Recs.ppfs+index))->fd+i)=0;
            strncpy((*(SYS_FS_Recs.ppfs+index))->fsName,"mpfs2",SYS_FS_MAX_DRIVE);
        }
    }

#endif
    
#ifdef SYS_FS_FILESYSTEM_MDD
    for(index=0;index<SYS_FS_Recs.nFileSystems;index++)
    {
       *(SYS_FS_Recs.ppfs+index) = (SYS_FS_FILE_DESC_t*)SystemMalloc(sizeof(SYS_FS_FILE_DESC_t));
        if(fsTypes && _SYS_FS_MASK_MDD)
        {
            nMaxHandles = FS_MAX_FILES_OPEN;

            // Do not allow the underlying files system more descriptors
            // than then the FS system can handle
            if(nMaxHandles>SYS_FS_MAX_DESCRIPTORS)
                nMaxHandles=SYS_FS_MAX_DESCRIPTORS;

            // Initialize the descriptors
           (*(SYS_FS_Recs.ppfs+index))->fd = SystemMalloc(sizeof(int32_t)*nMaxHandles);
           for(i=0;i<nMaxHandles;i++)  // Set all descriptors to 0
             *((*(SYS_FS_Recs.ppfs)+index)->fd+i)=0;
           strncpy((*(SYS_FS_Recs.ppfs)+index)->fsName,"mdd",SYS_FS_MAX_DRIVE);
        }
    }
#endif
    return RETURN_SUCCESS;
}


/**************************** SYS_FS_deinitializeDEF *****************************
 * Description:
 *           Prepares the virtual file system (FS) for shutting down by
 *           deallocating memory and and freeing descriptors within the descriptor
 *           tables
 *
 * Params:
 *        intData - null pointer to initializatio data values. Unused at this time
 *
 * Return: RETURN_SUCCESS
 ******************************************************************************/
int32_t SYS_FS_deinitialize(const void* const initData)
{
    int32_t index;

#if defined (SYS_FS_FILESYSTEM_MPFS) || defined (SYS_FS_FILESYSTEM_MDD)
    for(index=0;index<SYS_FS_Recs.nFileSystems;index++)
    {
       // Deinitialize the descriptor table memory block
       if((*(SYS_FS_Recs.ppfs+index))->fd !=(int32_t*)0)
       {
           SystemFree((*(SYS_FS_Recs.ppfs+index))->fd);
           (*(SYS_FS_Recs.ppfs+index))->fd = (int32_t*)0;
       }
       // Deinitialize the file system records
       if(*(SYS_FS_Recs.ppfs+index) != (SYS_FS_FILE_DESC_t*)0)
       {
           SystemFree( *(SYS_FS_Recs.ppfs+index));
           *(SYS_FS_Recs.ppfs+index) = (SYS_FS_FILE_DESC_t*)0;
       }
    }
    // Free memory for the file descriptor tables
    if(SYS_FS_Recs.ppfs != (SYS_FS_FILE_DESC_t**)0)
    {
        SystemFree(SYS_FS_Recs.ppfs);
        SYS_FS_Recs.ppfs = (SYS_FS_FILE_DESC_t**)0;
    }
#endif

    return RETURN_SUCCESS;
}

/**************************** SYS_FS_reinitializeDEF *****************************
 * Description:
 *           Reinializes the FS
 *
 * Params:
 *        intData - null pointer to initializatio data values. Unused at this time
 *
 * Return: RETURN_SUCCESS
 ******************************************************************************/
int32_t SYS_FS_reinitialize(const void* const initData)
{
    SYS_FS_setdefdir(SYS_FS_STRING);

    SYS_FS_deinitialize((void*)0);
    SYS_FS_initialize((void*)0);

    return RETURN_SUCCESS;
}


/**************************** SYS_FS_setdefdirDEF ******************************
 * Description:
 *          Set the default cur working directory on boot
 * Since this sets the global current working directory for the system, this
 * function must be called at least once after boot and prior to mounting any device.
 * This should be a root priviledged call.
 *
 * Params:
 *        path - Null terminated string to a valid directory path to be used
 *               as the default directory whenever the system boots
 *
 * Return: RETURN_SUCCESS
 *         RETURN_FAILED
 ******************************************************************************/
int32_t SYS_FS_setdefdir(const char *path)
{
    if(SYS_FS_chdir(path) == RETURN_SUCCESS)
    {
       strncpy(SYS_FS_sGdefcwd,path,SYS_FS_MAX_PATH);
       return RETURN_SUCCESS;
    }
    else 
    {
        SYS_FS_GenError(__FILE__,__LINE__);
        return RETURN_FAILED;
    }
}


/**************************** SYS_FS_chdirDEF ******************************
 * Description:
 *         Sets the current working directory
 *
 * Params:
 *        path - Null terminated string to a valid directory path to be used
 *               as the new current directory
 *
 * Return: RETURN_SUCCESS
 ******************************************************************************/
int32_t SYS_FS_chdir(const char *path)
{
    strncpy(SYS_FS_sGcwd, path,SYS_FS_MAX_PATH); // Set the cur working directory

    return RETURN_SUCCESS;
}

/**************************** SYS_FS_mountDEF ******************************
 * Description:
 *         Assignes an alias name (i.e. target) to an assocaiation established
 * between source and target. The association details are added to the mount
 * table. The provided name to (target) will serve as future reference when
 * performing file operations.
 *
 * Params:
 *         source - Normally "source" should represent a device file, however,
 *                  since the concept of device files are not yet known by the
 *                  system, we must instead choose a device directly. The source
 *                  must contain  a previously created file system which can be
 *                  created using the SYS_FS_format() command.
 *
 *         target - A pathname to use as an alias for the mount point.
 *         A directory will be created using this name provided. If no directoy
 *         path is provided within pathname, the current working directory will
 *         be used as the root and pathname will be created within the working
 *         directory
 *
 * Return: - if the mount was successfull ERR_NOWORKINGDIRECTORY - If no current
 *           working directory is established. This can occure if a call to
 *           SYS_FS_setdefdir() or SYS_FS_chgdir() has not been successfully
 *           called.
 *           SYS_FS_STATUS_PARAM_ERROR if file system type is not a recognized
 *           supported type
 ******************************************************************************/
int32_t SYS_FS_mount(SYS_FS_MEDIA_TYPE source
               , const char *target // Alias name
               , const char *filesystemtype
               , SYS_FS_IO_INTENT mountflags
               , const void *data)
{
    if((strncmp(filesystemtype,"mpfs2",SYS_FS_MAX_DRIVE)==0)
        || (strncmp(filesystemtype,"mdd",SYS_FS_MAX_DRIVE)==0))
    {
        switch(mountflags)
        {
            case SYS_FS_IO_INTENT_READWRITE:
            case SYS_FS_IO_INTENT_READ:
            case SYS_FS_IO_INTENT_WRITE:
                // plus 1 since we start with SYS_FS_nMounts=0
                if(!SYS_FS_pMountRec) // Already have memory allocated?
                   SYS_FS_pMountRec=SystemMalloc(sizeof(SYS_FS_MOUNT_REC_t)*(SYS_FS_nMounts+1));
                else
                    SYS_FS_pMountRec=realloc(SYS_FS_pMountRec,sizeof(SYS_FS_MOUNT_REC_t)*SYS_FS_nMounts+1);

                // Initialize the mount name
                if(*(target+0)==SYS_FS_CHAR) // Ignore the leading SYS_FS_CHAR
                   strncpy((SYS_FS_pMountRec+SYS_FS_nMounts)->mount_name,target+1,SYS_FS_MAX_DRIVE);
                else strncpy((SYS_FS_pMountRec+SYS_FS_nMounts)->mount_name,target,SYS_FS_MAX_DRIVE);

                // Initialize the mount path
                strncpy((SYS_FS_pMountRec+SYS_FS_nMounts)->mount_path,target,SYS_FS_MAX_PATH);

                // Initialize the mount dev and file system type
                (SYS_FS_pMountRec+SYS_FS_nMounts)->dev=source;
                strncpy((SYS_FS_pMountRec+SYS_FS_nMounts)->cpFileSystemType,filesystemtype,8);
                SYS_FS_nMounts++; // Total number of existing mount points
                return RETURN_SUCCESS;
            break;
            default:
              SYS_FS_GenError(__FILE__,__LINE__);
              return SYS_FS_STATUS_OPERATION_ERROR;
              break;
        }
    }

    SYS_FS_GenError(__FILE__,__LINE__);
    return SYS_FS_STATUS_PARAM_ERROR;
}

/**************************** SYS_FS_GenErrorDEF ******************************
 * Description:
 *         General error trapping routine. Needs to be populated with meaning
 *         error trapping code.
 *
 * Params:
 *        file - Name of the source code file that generated the error
 *        ln   - Line number of the offending code
 *
 * Return: None
 ******************************************************************************/
void SYS_FS_GenError(char *file, int32_t ln)
{
    // TBD
}

/****************************** SYS_FS_lseekDEF ****************************
 * Description: sition read/write file offset
 *
 * Params:
 *         fd - File descriptor returned by the call to SYS_FS_open()
 *         offset - the offset of the open file
 *         whence - is as follows:
           SEEK_SET: The offset is set to offset bytes.
 *         SEEK_CUR: The offset is set to its current location plus offset bytes.
 *         SEEK_END: The offset is set to the size of the file plus offset bytes
 * Return: Upon successful completion, lseek() returns the resulting offset
 *         location as measured in bytes from the beginning of the file.
 *         On error, the value (off_t) -1 is returned and errno is set to
 *         indicate the error.
 ******************************************************************************/
off_t SYS_FS_lseek(int32_t filedes, off_t offset, int32_t whence)
{
    char fs[SYS_FS_MAX_DRIVE];
    int32_t desc;

    if(SYS_FS_DescriptorNameGet(filedes,fs)!=RETURN_SUCCESS)
    {
        errno=EBADF; // Bad file number
        SYS_FS_GenError(__FILE__,__LINE__);
        return -1;
    }

#ifdef SYS_FS_FILESYSTEM_MPFS
    if(strncmp(fs,"mpfs2",SYS_FS_MAX_DRIVE)==0)
    {
        if(whence==SEEK_SET)
            whence=MPFS_SEEK_START;
        else if(whence==SEEK_CUR)
            whence=MPFS_SEEK_FORWARD;
        else if(whence==SEEK_END)
            whence=MPFS_SEEK_END;

        SYS_FS_mpfs2fs_Seek((MPFS_HANDLE )filedes, (uint32_t) offset, whence);

        // Return the new location
	return (off_t)MPFSGetPosition((MPFS_HANDLE )filedes);
    }
#endif

#ifdef SYS_FS_FILESYSTEM_MDD
    if(strncmp(fs,"mdd",SYS_FS_MAX_DRIVE)==0)
    {
        // Convert the system level file descriptor back to MDD descriptor
        desc=SYS_FS_Sys2LocDesc(filedes, "mdd");
        
        SYS_FS_mddfs_Seek((MDDFS_HANDLE )desc, (uint32_t) offset, whence);

        // Return the new location
	return (off_t)SYS_FS_mddfs_Tell((MDDFS_HANDLE )desc);
    }
#endif
    errno=EBADF; // Bad file number
    return -1;
}

int32_t SYS_FS_format(char mode, long serialNumber, char * mountName){return RETURN_SUCCESS;}
int32_t SYS_FS_unmount(const char *target){return RETURN_SUCCESS;}
int32_t SYS_FS_error(void){return errno;}
void SYS_FS_clearerror(void){errno=0;}


#endif  // defined (SYS_FS_ENABLE)

