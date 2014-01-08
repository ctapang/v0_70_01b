/******************************************************************************
*
*               Microchip Memory Disk Drive File System
*
******************************************************************************
* File Name:          FSIO.c
* Dependencies:       GenericTypeDefs.h
*                     FSIO.h
*                     Physical interface include file (SD-SPI.h, CF-PMP.h, ...)
*                     string.h
*                     stdlib.h
*                     FSDefs.h
*                     ctype.h
*                     salloc.h
* Processor:          PIC18/PIC24/dsPIC30/dsPIC33/PIC32
* Compiler:           C18/C30/C32
* Company:            Microchip Technology, Inc.
*
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the �Company�) for its PICmicro� Microcontroller is intended and
* supplied to you, the Company�s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
********************************************************************
 File Description:

 Change History:
  Rev     Description
  -----   -----------
  1.2.5   Fixed bug that prevented writes to alternate FAT tables
          Fixed bug that prevented FAT being updated when media is re-inserted

  1.2.6   Fixed bug that resulted in a bus error when attempts to read a invalid memory region
          Fixed bug that prevented the Windows Explorer to show the Date Creation field for directories

  x.x.x   Fixed issue on some USB drives where the information written
            to the drive is cached in a RAM for 500ms before it is 
            written to the flash unless the sector is accessed again.
          Add some error recovery for FAT32 systems when there is
            corruption in the boot sector.

  1.3.0   Modified to support Long File Name(LFN) format
  1.3.4   1) Initialized some of the local variables to default values
             to remove non-critical compiler warnings for code sanitation.
          2) The sector size of the media device is obtained from the MBR of media.So, 
             instead of using the hard coded macro "DIRENTRIES_PER_SECTOR", the variables
             "dirEntriesPerSector" & "disk->sectorSize" are used in the code. Refer 
             "Cache_File_Entry","EraseCluster" & "writeDotEntries" fucntions to see 
             the change.
  1.3.6   1) The function "FILEget_next_cluster" is made public.
          2) Modified "FILEfind" function such that when using 8.3 format
             the file searches are not considered as case sensitive.
          3) In function 'CacheTime', the variables 'ptr1' & 'ptr0' are not used
             when compiled for PIC32. So there definitions were removed for PIC32.
          4) Modified "rmdirhelper", "FormatDirName" & "writeDotEntries" functions
             to remove non-critical warnings during compilation.
          5) Updated comments in most of the function header blocks.
  1.4.0   1) While creating files in LFN format with file name length as 13,26,39,52...etc(multiples of 13),
             MDD library was creating incorrect directory entries. To fix this issue,
             functions "FILEfind", "CreateFileEntry", "Alias_LFN_Object", "FormatFileName", 
             "FormatDirName", "FSgetcwd", "GetPreviousEntry" & "rmdirhelper" were modified.
             Now "utf16LFNlength" variable part of "FSFILE" structure, indicates LFN length
             excluding the NULL uint16_t at the last.
          2) When creating large number of files in LFN format, some files were not getting created in disk.
             To fix this issue,function "FILEfind" was modified.
          3) Modified "FSformat" function to initialize "disk->sectorSize" to default value.
          4) Modified "CreateFileEntry" & "FindEmptyEntries" functions to remove unnecessary
             assignments & optimize the code.
          5) Modified "FSfopen" function to prevent creating an empty file in the directory, when SD card
             is write protected.
          6) Variable "entry" in "writeDotEntries" function is made volatile & properly typecasted
             in it's usage.
          7) Modified "FSFopen" function so that when you try to open a file that doesn't exist on the disk,
             variable "FSerrno" is assigned to CE_FILE_NOT_FOUND.
  1.4.2   1) Minor Modification in "CreateFileEntry" function to fix a bug for file name lengths of
             26,39....characters (multiples of 13)
          2) Fixed the LoadMBR() function to scan all of the MBR entries and return success on the first
             supported drive or fail after the 4 table entries.
********************************************************************/
#include "legacy_MDD/FSIO.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "legacy_MDD/FSDefs.h"


#ifndef ALLOW_WRITES
   #ifdef ALLOW_FORMATS
      #error Write functions must be enabled to use the format function
   #endif
   #ifdef ALLOW_FSFPRINTF
      #error Write functions must be enabled to use the FSfprintf function
   #endif
#endif

#ifdef USEREALTIMECLOCK
    #ifdef USERDEFINEDCLOCK
        #error Please select only one timestamp clocking mode in FSconfig.h
    #endif
    #ifdef INCREMENTTIMESTAMP
        #error Please select only one timestamp clocking mode in FSconfig.h
    #endif
#elif defined USERDEFINEDCLOCK
    #ifdef INCREMENTTIMESTAMP
        #error Please select only one timestamp clocking mode in FSconfig.h
    #endif
#endif
/*****************************************************************************/
/*                         Global Variables                                  */
/*****************************************************************************/

#ifndef FS_DYNAMIC_MEM
    FSFILE  gFileArray[FS_MAX_FILES_OPEN];      // Array that contains file information (static allocation)
    uint8_t    gFileSlotOpen[FS_MAX_FILES_OPEN];   // Array that indicates which elements of gFileArray are available for use
	#ifdef SUPPORT_LFN
		// Array that stores long file name (static allocation)
		unsigned short int lfnData[FS_MAX_FILES_OPEN][257];
	#endif
#endif

#ifdef SUPPORT_LFN
	#ifdef ALLOW_FILESEARCH
		// Array that stores long file name for File Search operation (static allocation)
		unsigned short int recordSearchName[257];
		unsigned short int recordFoundName[257];
		unsigned short int recordSearchLength;
	#endif
	unsigned short int fileFoundString[261];
#endif

#if defined(USEREALTIMECLOCK) || defined(USERDEFINEDCLOCK)
// Timing variables
uint8_t    gTimeCrtMS;     // Global time variable (for timestamps) used to indicate create time (milliseconds)
uint16_t    gTimeCrtTime;   // Global time variable (for timestamps) used to indicate create time
uint16_t    gTimeCrtDate;   // Global time variable (for timestamps) used to indicate create date
uint16_t    gTimeAccDate;   // Global time variable (for timestamps) used to indicate last access date
uint16_t    gTimeWrtTime;   // Global time variable (for timestamps) used to indicate last update time
uint16_t    gTimeWrtDate;   // Global time variable (for timestamps) used to indicate last update date
#endif

uint32_t       gLastFATSectorRead = 0xFFFFFFFF;    // Global variable indicating which FAT sector was read last
uint8_t        gNeedFATWrite = FALSE;              // Global variable indicating that there is information that needs to be written to the FAT
FSFILE  *   gBufferOwner = NULL;                // Global variable indicating which file is using the data buffer
uint32_t       gLastDataSectorRead = 0xFFFFFFFF;   // Global variable indicating which data sector was read last
uint8_t        gNeedDataWrite = FALSE;             // Global variable indicating that there is information that needs to be written to the data section
uint8_t        nextClusterIsLast = FALSE;          // Global variable indicating that the entries in a directory align with a cluster boundary

uint8_t    gBufferZeroed = FALSE;      // Global variable indicating that the data buffer contains all zeros

uint32_t   FatRootDirClusterValue;     // Global variable containing the cluster number of the root dir (0 for FAT12/16)

uint8_t    FSerrno;                    // Global error variable.  Set to one of many error codes after each function call.

uint32_t   TempClusterCalc;            // Global variable used to store the calculated value of the cluster of a specified sector.
uint8_t    dirCleared;                 // Global variable used by the "recursive" FSrmdir function to indicate that all subdirectories and files have been deleted from the target directory.
uint8_t    recache = FALSE;            // Global variable used by the "recursive" FSrmdir function to indicate that additional cache reads are needed.
FSFILE  tempCWDobj;                 // Global variable used to preserve the current working directory information.
FSFILE  gFileTemp;                  // Global variable used for file operations.

FSFILE   cwd;               // Global current working directory
FSFILE * cwdptr = &cwd;     // Pointer to the current working directory

#ifdef __18CXX
    #pragma udata dataBuffer = DATA_BUFFER_ADDRESS
    uint8_t gDataBuffer[MEDIA_SECTOR_SIZE];    // The global data sector buffer
    #pragma udata FATBuffer = FAT_BUFFER_ADDRESS
    uint8_t gFATBuffer[MEDIA_SECTOR_SIZE];     // The global FAT sector buffer
    #pragma udata
#endif

#if defined (__C30__) || defined (__PIC32MX__)
    uint8_t __attribute__ ((aligned(4)))   gDataBuffer[MEDIA_SECTOR_SIZE];     // The global data sector buffer
    uint8_t __attribute__ ((aligned(4)))   gFATBuffer[MEDIA_SECTOR_SIZE];      // The global FAT sector buffer
#endif

DISK gDiskData;         // Global structure containing device information.

/* Global Variables to handle ASCII & UTF16 file operations */
char *asciiFilename;
unsigned short int fileNameLength;
#ifdef SUPPORT_LFN
	unsigned short int *utf16Filename;
	bool	utfModeFileName = FALSE;
	bool	twouint8_tMode = FALSE;
#endif
/************************************************************************/
/*                        Structures and defines                        */
/************************************************************************/

// Directory entry structure
typedef struct
{
    char      DIR_Name[DIR_NAMESIZE];           // File name
    char      DIR_Extension[DIR_EXTENSION];     // File extension
    uint8_t      DIR_Attr;                         // File attributes
    uint8_t      DIR_NTRes;                        // Reserved uint8_t
    uint8_t      DIR_CrtTimeTenth;                 // Create time (millisecond field)
    uint16_t      DIR_CrtTime;                      // Create time (second, minute, hour field)
    uint16_t      DIR_CrtDate;                      // Create date
    uint16_t      DIR_LstAccDate;                   // Last access date
    uint16_t      DIR_FstClusHI;                    // High uint16_t of the entry's first cluster number
    uint16_t      DIR_WrtTime;                      // Last update time
    uint16_t      DIR_WrtDate;                      // Last update date
    uint16_t      DIR_FstClusLO;                    // Low uint16_t of the entry's first cluster number
    uint32_t     DIR_FileSize;                     // The 32-bit file size
}_DIRENTRY;

typedef _DIRENTRY * DIRENTRY;                   // A pointer to a directory entry structure

#define DIRECTORY 0x12          // Value indicating that the CreateFileEntry function will be creating a directory

#define DIRENTRIES_PER_SECTOR   (MEDIA_SECTOR_SIZE / 32)        // The number of directory entries in a sector

// Maximum number of UTF16 uint16_ts in single Root directory entry
#define MAX_UTF16_CHARS_IN_LFN_ENTRY      (uint8_t)13

// Long File Name Entry
typedef struct
{
   uint8_t LFN_SequenceNo;   // Sequence number,
   uint8_t LFN_Part1[10];    // File name part 1
   uint8_t LFN_Attribute;    // File attribute
   uint8_t LFN_Type;		// LFN Type
   uint8_t LFN_Checksum;     // Checksum
   unsigned short int LFN_Part2[6];    // File name part 2
   unsigned short int LFN_Reserved2;	// Reserved for future use
   unsigned short int LFN_Part3[2];     // File name part 3
}LFN_ENTRY;

/* Summary: Possible type of file or directory name.
** Description: See the FormatFileName() & FormatDirName() function for more information.
*/
typedef enum
{
    NAME_8P3_ASCII_CAPS_TYPE,
    NAME_8P3_ASCII_MIXED_TYPE,
    NAME_8P3_UTF16_TYPE, // SUBTYPES OF 8P3 UTF16 TYPE
	    NAME_8P3_UTF16_ASCII_CAPS_TYPE,
	    NAME_8P3_UTF16_ASCII_MIXED_TYPE,
	    NAME_8P3_UTF16_NONASCII_TYPE,
    NAME_LFN_TYPE,
    NAME_ERROR
} FILE_DIR_NAME_TYPE;

// internal errors
#define CE_FAT_EOF            60   // Error that indicates an attempt to read FAT entries beyond the end of the file
#define CE_EOF                61   // Error that indicates that the end of the file has been reached

typedef FSFILE   * FILEOBJ;         // Pointer to an FSFILE object

#ifdef ALLOW_FSFPRINTF

#define _FLAG_MINUS 0x1             // FSfprintf minus flag indicator
#define _FLAG_PLUS  0x2             // FSfprintf plus flag indicator
#define _FLAG_SPACE 0x4             // FSfprintf space flag indicator
#define _FLAG_OCTO  0x8             // FSfprintf octothorpe (hash mark) flag indicator
#define _FLAG_ZERO  0x10            // FSfprintf zero flag indicator
#define _FLAG_SIGNED 0x80           // FSfprintf signed flag indicator

#ifdef __18CXX
    #define _FMT_UNSPECIFIED 0      // FSfprintf unspecified argument size flag
    #define _FMT_LONG 1             // FSfprintf 32-bit argument size flag
    #define _FMT_SHRTLONG 2         // FSfprintf 24-bit argument size flag
    #define _FMT_uint8_t   3           // FSfprintf 8-bit argument size flag
#else
    #define _FMT_UNSPECIFIED 0      // FSfprintf unspecified argument size flag
    #define _FMT_LONGLONG 1         // FSfprintf 64-bit argument size flag
    #define _FMT_LONG 2             // FSfprintf 32-bit argument size flag
    #define _FMT_uint8_t 3             // FSfprintf 8-bit argument size flag
#endif

#ifdef __18CXX
    static const rom char s_digits[] = "0123456789abcdef";      // FSfprintf table of conversion digits
#else
    static const char s_digits[] = "0123456789abcdef";          // FSfprintf table of conversion digits
#endif

#endif

/************************************************************************************/
/*                               Prototypes                                         */
/************************************************************************************/

uint32_t ReadFAT (DISK *dsk, uint32_t ccls);
DIRENTRY Cache_File_Entry( FILEOBJ fo, uint16_t * curEntry, uint8_t ForceRead);
uint8_t Fill_File_Object(FILEOBJ fo, uint16_t *fHandle);
uint32_t Cluster2Sector(DISK * disk, uint32_t cluster);
DIRENTRY LoadDirAttrib(FILEOBJ fo, uint16_t *fHandle);
#ifdef INCREMENTTIMESTAMP
    void IncrementTimeStamp(DIRENTRY dir);
#elif defined USEREALTIMECLOCK
    void CacheTime (void);
#endif

#if defined (__C30__) || defined (__PIC32MX__)
    uint8_t Readuint8_t( uint8_t* pBuffer, uint16_t index );
    uint16_t Reauint32_t( uint8_t* pBuffer, uint16_t index );
    uint32_t Readuint32_t( uint8_t* pBuffer, uint16_t index );
#endif

void FileObjectCopy(FILEOBJ foDest,FILEOBJ foSource);
FILE_DIR_NAME_TYPE ValidateChars(uint8_t mode);
uint8_t FormatFileName( const char* fileName, FILEOBJ fptr, uint8_t mode);
CETYPE FILEfind( FILEOBJ foDest, FILEOBJ foCompareTo, uint8_t cmd, uint8_t mode);
CETYPE FILEopen (FILEOBJ fo, uint16_t *fHandle, char type);
#if defined(SUPPORT_LFN)
bool Alias_LFN_Object(FILEOBJ fo);
uint8_t Fill_LFN_Object(FILEOBJ fo, LFN_ENTRY *lfno, uint16_t *fHandle);
#endif

// Directory functions
#ifdef ALLOW_DIRS
    uint8_t GetPreviousEntry (FSFILE * fo);
    uint8_t FormatDirName (char * string,FILEOBJ fptr, uint8_t mode);
    int CreateDIR (char * path);
    uint8_t writeDotEntries (DISK * dsk, uint32_t dotAddress, uint32_t dotdotAddress);
    int eraseDir (char * path);
#ifdef ALLOW_PGMFUNCTIONS
    #ifdef ALLOW_WRITES
        int mkdirhelper (uint8_t mode, char * ramptr, const rom char * romptr);
        int rmdirhelper (uint8_t mode, char * ramptr, const rom char * romptr, unsigned char rmsubdirs);
    #endif
int chdirhelper (uint8_t mode, char * ramptr, const rom char * romptr);
#else
    #ifdef ALLOW_WRITES
        int mkdirhelper (uint8_t mode, char * ramptr, char * romptr);
        int rmdirhelper (uint8_t mode, char * ramptr, char * romptr, unsigned char rmsubdirs);
    #endif
    int chdirhelper (uint8_t mode, char * ramptr, char * romptr);
#endif
#endif

#ifdef ALLOW_FSFPRINTF
    #ifdef __18CXX
        int FSvfprintf (auto FSFILE *handle, auto const rom char *formatString, auto va_list ap);
    #else
        int FSvfprintf (FSFILE *handle, const char *formatString, va_list ap);
    #endif
    int FSputc (char c, FSFILE * file);
    unsigned char str_put_n_chars (FSFILE * handle, unsigned char n, char c);
#endif

uint8_t DISKmount( DISK *dsk);
uint8_t LoadMBR(DISK *dsk);
uint8_t LoadBootSector(DISK *dsk);
uint32_t GetFullClusterNumber(DIRENTRY entry);


/*************************************************************************
  Function:
    int FSInit(void)
  Summary:
    Function to initialize the device.
  Conditions:
    The physical device should be connected to the microcontroller.
  Input:
    None
  Return Values:
    TRUE -  Initialization successful
    FALSE - Initialization unsuccessful
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    This function initializes the file system stack & the interfacing device.
    Initializes the static or dynamic memory slots for holding file
    structures. Initializes the device with the DISKmount function. Loads 
    MBR and boot sector information. Initializes the current working
    directory to the root directory for the device if directory support
    is enabled.
  Remarks:
    None
  *************************************************************************/

int FSInit(void)
{
    int fIndex;
#ifndef FS_DYNAMIC_MEM
    for( fIndex = 0; fIndex < FS_MAX_FILES_OPEN; fIndex++ )
        gFileSlotOpen[fIndex] = TRUE;
#else
    #ifdef __18CXX
        SRAMInitHeap();
    #endif
#endif

    gBufferZeroed = FALSE;
    gNeedFATWrite = FALSE;             
    gLastFATSectorRead = 0xFFFFFFFF;       
    gLastDataSectorRead = 0xFFFFFFFF;  

    MDD_InitIO();

    if(DISKmount(&gDiskData) == CE_GOOD)
    {
    // Initialize the current working directory to the root
#ifdef ALLOW_DIRS
        cwdptr->dsk = &gDiskData;
        cwdptr->sec = 0;
        cwdptr->pos = 0;
        cwdptr->seek = 0;
        cwdptr->size = 0;
        cwdptr->name[0] = '\\';
        for (fIndex = 1; fIndex < 11; fIndex++)
        {
            cwdptr->name[fIndex] = 0x20;
        }
        cwdptr->entry = 0;
        cwdptr->attributes = ATTR_DIRECTORY;
        // "FatRootDirClusterValue" indicates the root
        cwdptr->dirclus = FatRootDirClusterValue;
        cwdptr->dirccls = FatRootDirClusterValue;
	#if defined(SUPPORT_LFN)
		// Initialize default values for LFN support
        cwdptr->AsciiEncodingType = TRUE;
        cwdptr->utf16LFNlength = 0x0000;
	#endif
#endif

        FSerrno = 0;
        return TRUE;
    }

    return FALSE;
}


/********************************************************************************
  Function:
    CETYPE FILEfind (FILEOBJ foDest, FILEOBJ foCompareTo, uint8_t cmd, uint8_t mode)
  Summary
    Finds a file on the device
  Conditions:
    This function should not be called by the user.
  Input:
    foDest -       FSFILE object containing information of the file found
    foCompareTo -  FSFILE object containing the name/attr of the file to be
                   found
    cmd -
        -          LOOK_FOR_EMPTY_ENTRY: Search for empty entry.
        -          LOOK_FOR_MATCHING_ENTRY: Search for matching entry.
    mode -
         -         0: Match file exactly with default attributes.
         -         1: Match file to user-specified attributes.
  Return Values:
    CE_GOOD -            File found.
    CE_FILE_NOT_FOUND -  File not found.
  Side Effects:
    None.
  Description:
    The FILEfind function will sequentially cache directory entries within
    the current working directory into the foDest FSFILE object.  If the cmd
    parameter is specified as LOOK_FOR_EMPTY_ENTRY the search will continue
    until an empty directory entry is found. If the cmd parameter is specified
    as LOOK_FOR_MATCHING_ENTRY these entries will be compared to the foCompareTo
    object until a match is found or there are no more entries in the current
    working directory. If the mode is specified a '0' the attributes of the FSFILE
    entries are irrelevant. If the mode is specified as '1' the attributes of the
    foDest entry must match the attributes specified in the foCompareTo file and
    partial string search characters may bypass portions of the comparison.
  Remarks:
    None
  ********************************************************************************/

CETYPE FILEfind( FILEOBJ foDest, FILEOBJ foCompareTo, uint8_t cmd, uint8_t mode)
{
    uint16_t   attrib, compareAttrib;
    uint16_t   fHandle = foDest->entry;                  // current entry counter
    CETYPE   statusB = CE_FILE_NOT_FOUND;
    uint8_t   character,test,state,index;

	#if defined(SUPPORT_LFN)

 	LFN_ENTRY lfnObject;	// Long File Name Object
	unsigned char *dst = (unsigned char *)&fileFoundString[0];
	unsigned short int *templfnPtr = (unsigned short int *)foCompareTo -> utf16LFNptr;
	UINT16_VAL tempShift;
	short int   fileCompareLfnIndex,fileFoundLfnIndex = 0,fileFoundMaxLfnIndex = 0,lfnCountIndex,fileFoundLength = 0;
	bool  lfnFirstCheck = FALSE,foundSFN,foundLFN,fileFoundDotPosition = FALSE,fileCompareDotPosition;
	uint8_t  lfnCompareMaxSequenceNum = 0,lfnFoundMaxSequenceNum,reminder = 0;
	char  tempDst[13];
	fileNameLength = foCompareTo->utf16LFNlength;

	// If 'fileNameLength' is non zero then it means that file name is of LFN format.
	// If 'fileNameLength' is zero then it means that file name is of 8.3 format
	if(fileNameLength)
	{
		// Find out the number of root entries for the given LFN
		reminder = fileNameLength % MAX_UTF16_CHARS_IN_LFN_ENTRY;

		index = fileNameLength/MAX_UTF16_CHARS_IN_LFN_ENTRY;

		if(reminder || (fileNameLength < MAX_UTF16_CHARS_IN_LFN_ENTRY))
		{
			index++;
		}

		// The maximum sequence number of the LFN
		lfnCompareMaxSequenceNum = index;
	}
	#endif

    // reset the cluster
    foDest->dirccls = foDest->dirclus;
	// Attribute to be compared as per application layer request
    compareAttrib = 0xFFFF ^ foCompareTo->attributes;

    if (fHandle == 0)
    {
        if (Cache_File_Entry(foDest, &fHandle, TRUE) == NULL)
        {
            statusB = CE_BADCACHEREAD;
        }
    }
    else
    {
		// Maximum 16 entries possible
        if ((fHandle & MASK_MAX_FILE_ENTRY_LIMIT_BITS) != 0)
        {
            if (Cache_File_Entry (foDest, &fHandle, TRUE) == NULL)
            {
                statusB = CE_BADCACHEREAD;
            }
        }
    }

    if (statusB != CE_BADCACHEREAD)
    {
        // Loop until you reach the end or find the file
        while(1)
        {
            if(statusB != CE_GOOD) //First time entry always here
            {
				#if defined(SUPPORT_LFN)
					foundSFN = FALSE;
					foundLFN = FALSE;

                	state = Fill_LFN_Object(foDest,&lfnObject,&fHandle);
				#else
                	state = Fill_File_Object(foDest, &fHandle);
				#endif

                if(state == NO_MORE) // Reached the end of available files. Comparision over and file not found so quit.
                {
                    break;
                }
            }
            else // statusB == CE_GOOD then exit
            {
                break; // Code below intializes"statusB = CE_GOOD;" so, if no problem in the filled file, Exit the while loop.
            }

            if(state == FOUND) // Validate the correct matching of filled file data with the required(to be found) one.
            {
				#if defined(SUPPORT_LFN)

				if(lfnObject.LFN_Attribute != ATTR_LONG_NAME)
				{
					lfnFirstCheck = FALSE;

					*dst = lfnObject.LFN_SequenceNo;
					for(index = 0;index < 10;index++)
						dst[index + 1] = lfnObject.LFN_Part1[index];
					foundSFN = TRUE;
				}
				else
				{
					if(lfnObject.LFN_SequenceNo & 0x40)
					{
						lfnFoundMaxSequenceNum = lfnObject.LFN_SequenceNo & 0x1F;
						
						if((mode == 0x00) && ((fileNameLength && (lfnFoundMaxSequenceNum != lfnCompareMaxSequenceNum)) || 
						   (!fileNameLength && (lfnFoundMaxSequenceNum != 0x01))))
						{
//							fHandle = fHandle + lfnFoundMaxSequenceNum + 1;
							fHandle++;
							continue;
						}

						fileFoundLfnIndex = (lfnObject.LFN_SequenceNo & 0xBF) * MAX_UTF16_CHARS_IN_LFN_ENTRY - 1;
						fileCompareLfnIndex = fileFoundLfnIndex;

						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part3[1];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part3[0];

						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[5];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[4];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[3];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[2];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[1];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[0];

						tempShift.uint8_t.LB = lfnObject.LFN_Part1[8];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[9];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[6];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[7];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[4];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[5];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[2];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[3];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[0];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[1];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;

						
						fileFoundLength = fileCompareLfnIndex + 1;
						for(index = 1;index <= MAX_UTF16_CHARS_IN_LFN_ENTRY;index++)
						{
							if(fileFoundString[fileFoundLfnIndex + index] == 0x0000)
								fileFoundLength = fileFoundLfnIndex + index;
						}

						if(mode == 0x00)
						{
							if((fileNameLength != fileFoundLength) && fileNameLength)
							{
//								fHandle = fHandle + lfnFoundMaxSequenceNum + 1;
								fHandle++;
								continue;
							}
						}

						fileFoundMaxLfnIndex = fileFoundLength - 1;
						lfnFirstCheck = TRUE;
					}
					else if(lfnFirstCheck == TRUE)
					{
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part3[1];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part3[0];

						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[5];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[4];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[3];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[2];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[1];
						fileFoundString[fileFoundLfnIndex--] = lfnObject.LFN_Part2[0];

						tempShift.uint8_t.LB = lfnObject.LFN_Part1[8];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[9];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[6];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[7];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[4];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[5];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[2];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[3];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
						tempShift.uint8_t.LB = lfnObject.LFN_Part1[0];
						tempShift.uint8_t.HB = lfnObject.LFN_Part1[1];
						fileFoundString[fileFoundLfnIndex--] = tempShift.Val;
					}
					else
         			{
         				fHandle++;
						continue;
					}

         			if(fileFoundLfnIndex > 0)
         			{
         				fHandle++;
						continue;
					}

					foundLFN = TRUE;
				}

				lfnFirstCheck = FALSE;
				statusB = CE_GOOD;
          	    switch (mode)
          	    {
          	        case 0:

							// Copy the contents of any SFN found to temporary string
							// for future comparision tests
							for(index = 0;index < FILE_NAME_SIZE_8P3;index++)
								tempDst[index] = dst[index];

							// Try to deduce the original name from the found SFN
							if(dst[8] != ' ')
							{
								for(index = 0;index < 8;index++)
								{
									if(dst[index] == ' ')
										break;
								}
								tempDst[index++] = '.';
								tempDst[index++] = dst[8];
								
								if(dst[9] != ' ')
									tempDst[index++] = dst[9];
								else
									tempDst[index++] = 0x00;
							
								if(dst[10] != ' ')
									tempDst[index++] = dst[10];
								else
									tempDst[index++] = 0x00;
							}
          	    		    else
							{
          	    		    	for(index = 0;index < 8;index++)
								{
									if(tempDst[index] == ' ')
										break;
								}
							}

							// Terminate the string using the NULL value
							tempDst[index] = 0x00;
          
          	            	if(fileNameLength)
          	            	{
          	        			if(foundLFN)
          	        			{
          	        				// see if we are a volume id or hidden, ignore
          	        				// search for one. if status = TRUE we found one
          	        				for(fileCompareLfnIndex = 0;fileCompareLfnIndex < fileNameLength;fileCompareLfnIndex++)
          	        				{
				  						if(foCompareTo -> AsciiEncodingType)
				  						{
          	        					       // get the source character
          	        					       character = (uint8_t)templfnPtr[fileCompareLfnIndex];
          	        					       // get the destination character
          	        					       test = (uint8_t)fileFoundString[fileCompareLfnIndex];
          	        					       if((fileFoundString[fileCompareLfnIndex] > 0xFF) || (tolower(character) != tolower(test)))
          	        					       {
          	        								statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	        								break;
          	        					       }
				  						}
				  						else
				  						{
				  							if(templfnPtr[fileCompareLfnIndex] != fileFoundString[fileCompareLfnIndex])
				  							{
          	    	  							statusB = CE_FILE_NOT_FOUND; // Nope its not a match
				  								break;
				  							}
				  						}
          	        				}// for loop
								}
								else if(foundSFN && foCompareTo -> AsciiEncodingType)
								{
          	        				if(strlen(tempDst) != fileNameLength)
          	        					statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	        				else
          	        				{
          	        					for(fileCompareLfnIndex = 0;fileCompareLfnIndex < fileNameLength;fileCompareLfnIndex++)
          	        					{
          	        						// get the source character
          	        						character = (uint8_t)templfnPtr[fileCompareLfnIndex];
          	        						// get the destination character
          	        						test = tempDst[fileCompareLfnIndex];
          	        						if(tolower(character) != tolower(test))
          	        						{
          	        							statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	        							break;
          	        						}
          	        					}// for loop
									}
								}
								else
								{
          	        				statusB = CE_FILE_NOT_FOUND; // Nope its not a match
								}
							}
							else
          	            	{
          	    				if(foundLFN)
          	    				{
          	        				if(strlen(tempDst) != fileFoundLength)
          	        					statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	        				else
          	        				{
          	        					for(fileCompareLfnIndex = 0;fileCompareLfnIndex < fileFoundLength;fileCompareLfnIndex++)
          	        					{
          	        						// get the source character
          	        						character = (uint8_t)fileFoundString[fileCompareLfnIndex];
          	        						// get the destination character
          	        						test = tempDst[fileCompareLfnIndex];
          	        						if((fileFoundString[fileCompareLfnIndex] > 0xFF) || (tolower(character) != tolower(test)))
          	        						{
          	        							statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	        							break;
          	        						}
          	        					}// for loop
									}
          	    				}
          	    				else
          	    				{
          	     					// search for one. if status = TRUE we found one
          	     					for(index = 0; index < DIR_NAMECOMP; index++)
          	     					{
          	     					    // get the source character
          	     					    character = dst[index];
          	     					    // get the destination character
          	     					    test = foCompareTo->name[index];
          	     					    if(tolower(character) != tolower(test))
          	     					    {
          	     					        statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	     					        break;
          	     					    }
          	     					}// for loop
								}
							}
          	        		break;

          	        case 1:
							if(fileNameLength)
          	            	{
								fileFoundDotPosition = FALSE;
								if(foundLFN)
								{
									lfnCountIndex = fileFoundMaxLfnIndex;
									while(lfnCountIndex > 0)
									{
										if(fileFoundString[lfnCountIndex] == '.')
										{
											fileFoundDotPosition = TRUE;
											lfnCountIndex--;
											break;
										}
										lfnCountIndex--;
									}

									if(fileFoundDotPosition == FALSE)
										lfnCountIndex = fileFoundMaxLfnIndex;
								}
								else
								{
									if(dst[DIR_NAMESIZE] != ' ')
										fileFoundDotPosition = TRUE;
									lfnCountIndex = DIR_NAMESIZE - 1;
								}

								fileFoundLfnIndex = fileNameLength - 1;
								fileCompareDotPosition = FALSE;
								while(fileFoundLfnIndex > 0)
								{
									if(templfnPtr[fileFoundLfnIndex] == '.')
									{
										fileCompareDotPosition = TRUE;
										fileFoundLfnIndex--;
										break;
									}
									fileFoundLfnIndex--;
								}
								if(fileCompareDotPosition == FALSE)
									fileFoundLfnIndex = fileNameLength - 1;

          	         			// Check for attribute match
          	         			for(fileCompareLfnIndex = 0;;)
          	         			{
          	         				if (templfnPtr[fileCompareLfnIndex] == '*')
          	         					break;
          	         			   
									if(fileCompareLfnIndex > lfnCountIndex)
          	         			    {
          	         			    	statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    	break;
          	         			    }
          	         			   
          	         			   if (templfnPtr[fileCompareLfnIndex] != '?')
          	         			   {
				  						if(foCompareTo -> AsciiEncodingType)
				  						{
          	         			    		// get the source character
          	         			    		character = (uint8_t)templfnPtr[fileCompareLfnIndex];
          	         			    		// get the destination character
          	         			    		if(foundLFN)
          	         			    			test = (uint8_t)fileFoundString[fileCompareLfnIndex];
											else
          	         			    			test = dst[fileCompareLfnIndex];

											if((foundLFN && (fileFoundString[fileCompareLfnIndex] > 0xFF)) ||
          	         			    			(tolower(character) != tolower(test)))
          	         			    		{
          	         			    			statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    			break;
          	         			    		}
				  						}
				  						else
				  						{
				  							if((templfnPtr[fileCompareLfnIndex] != fileFoundString[fileCompareLfnIndex]) || foundSFN)
				  							{
          	    	   							statusB = CE_FILE_NOT_FOUND; // Nope its not a match
				  								break;
				  							}
				  						}
          	         				}

               		    	 		fileCompareLfnIndex++;
               		    	 		if(fileCompareLfnIndex > fileFoundLfnIndex)
               		    	        {
               		    	            if(fileCompareLfnIndex <= lfnCountIndex)
               		    	            {
          	    	   						statusB = CE_FILE_NOT_FOUND; // Nope its not a match
										}
               		    	            break;
									}
          	         			}// for loop

								if(fileCompareDotPosition == FALSE)
								{
									if(fileFoundDotPosition == TRUE)
          	         			    {
          	         			    	statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    }
									break;
								}
								else
								{
									if(fileFoundDotPosition == FALSE)
          	         			    {
          	         			    	statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    	break;
          	         			    }

									if(foundLFN)
										lfnCountIndex = lfnCountIndex + 2;
									else
										lfnCountIndex = DIR_NAMESIZE;
								}

          	         			// Check for attribute match
          	         			for(fileCompareLfnIndex = fileFoundLfnIndex + 2;;)
          	         			{
          	         				if (templfnPtr[fileCompareLfnIndex] == '*')
          	         					break;
          	         			   
									if((foundLFN && (lfnCountIndex > fileFoundMaxLfnIndex)) || (foundSFN && (lfnCountIndex == 11)))
									{
          	         			    	statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    	break;
									}
          	         			   
          	         			   if (templfnPtr[fileCompareLfnIndex] != '?')
          	         			   {
				  						if(foCompareTo -> AsciiEncodingType)
				  						{
          	         			    	    // get the source character
          	         			    	    character = (uint8_t)templfnPtr[fileCompareLfnIndex];
          	         			    	    // get the destination character
          	         			    		if(foundLFN)
          	         			    			test = (uint8_t)fileFoundString[lfnCountIndex];
											else
          	         			    			test = dst[lfnCountIndex];
											if((foundLFN && (fileFoundString[lfnCountIndex] > 0xFF)) ||
          	         			    			(tolower(character) != tolower(test)))
          	         			    		{
          	         			    			statusB = CE_FILE_NOT_FOUND; // Nope its not a match
          	         			    			break;
          	         			    		}
				  						}
				  						else
				  						{
				  							if((templfnPtr[fileCompareLfnIndex] != fileFoundString[lfnCountIndex]) || foundSFN)
				  							{
          	    	   							statusB = CE_FILE_NOT_FOUND; // Nope its not a match
				  								break;
				  							}
				  						}
          	         				}
               		    	 		lfnCountIndex++;
               		    	 		fileCompareLfnIndex++;
               		    	 		if(fileCompareLfnIndex == fileNameLength)
               		    	        {
               		    	            if((foundLFN && (lfnCountIndex <= fileFoundMaxLfnIndex)) || (foundSFN && (lfnCountIndex < 11) && (dst[lfnCountIndex] != ' ')))
               		    	            {
          	    	   						statusB = CE_FILE_NOT_FOUND; // Nope its not a match
										}
               		    	            break;
									}
          	         			}// for loop
							}
							else
							{
          	    				/* We got something */
               		    		if(foundLFN)
               		    		{
									fileCompareLfnIndex = fileFoundMaxLfnIndex;
									fileFoundDotPosition = FALSE;
									while(fileCompareLfnIndex > 0)
									{
										if(fileFoundString[fileCompareLfnIndex] == '.')
										{
											fileFoundDotPosition = TRUE;
											fileCompareLfnIndex--;
											break;
										}
										fileCompareLfnIndex--;
									}

									if(fileFoundDotPosition == FALSE)
										fileCompareLfnIndex = fileFoundMaxLfnIndex;
								}
								else
									fileCompareLfnIndex = DIR_NAMESIZE - 1;	// Short File name last char position

               		    	    if (foCompareTo->name[0] != '*')   //If "*" is passed for comparion as 1st char then don't proceed. Go back, file alreay found.
               		    	    {
               		    	        for (index = 0;;)
               		    	        {
               		    	            if(foundLFN)
               		    	            {
               		    	            	if((fileFoundString[index] > 0xFF) || (index > fileCompareLfnIndex))
               		    	            	{
               		    	                	statusB = CE_FILE_NOT_FOUND; // it's not a match
               		    	                	break;
											}
										}

               		    	            // Get the source character
          	         					if(foundLFN)
          	         						character = (uint8_t)fileFoundString[index];
										else
          	         						character = dst[index];

               		    	            // Get the destination character
               		    	            test = foCompareTo->name[index];
               		    	            if (test == '*')
               		    	                break;
               		    	            if (test != '?')
               		    	            {
               		    	                if(tolower(character) != tolower(test))
               		    	                {
               		    	                    statusB = CE_FILE_NOT_FOUND; // it's not a match
               		    	                    break;
               		    	                }
               		    	            }
               		    	 
               		    	 			index++;
               		    	 			if(index == DIR_NAMESIZE)
               		    	        	{
               		    	        	    if(foundLFN && (index <= fileCompareLfnIndex))
               		    	        	    {
               		    	                	statusB = CE_FILE_NOT_FOUND; // it's not a match
											}
               		    	                break;
										}
               		    	        }
               		    	    }

               		    	    // Before calling this "FILEfind" fn, "formatfilename" must be called. Hence, extn always starts from position "8".
               		    	    if ((foCompareTo->name[8] != '*') && (statusB == CE_GOOD))
               		    	    {
               		    	        if(foundLFN)
               		    	        {
										if(foCompareTo->name[8] == ' ')
										{
											if(fileFoundDotPosition == TRUE)
               		    	        	    {
               		    	                	statusB = CE_FILE_NOT_FOUND; // it's not a match
											}
											break;
										}
										else
										{
											if(fileFoundDotPosition == FALSE)
											{
               		    	                	statusB = CE_FILE_NOT_FOUND; // it's not a match
												break;
											}
										}
										fileCompareLfnIndex = fileCompareLfnIndex + 2;
									}
									else
										fileCompareLfnIndex = DIR_NAMESIZE;

               		    	        for (index = 8;;)
               		    	        {
               		    	            if(foundLFN)
               		    	            {
               		    	            	if((fileFoundString[fileCompareLfnIndex] > 0xFF) || (fileCompareLfnIndex > fileFoundMaxLfnIndex))
               		    	            	{
               		    	                	statusB = CE_FILE_NOT_FOUND; // it's not a match
               		    	                	break;
											}
										}
               		    	            // Get the destination character
               		    	            test = foCompareTo->name[index];
               		    	            // Get the source character
          	         					if(foundLFN)
          	         						character = (uint8_t)fileFoundString[fileCompareLfnIndex++];
										else
          	         						character = dst[fileCompareLfnIndex++];

               		    	            if (test == '*')
               		    	                break;
               		    	            if (test != '?')
               		    	            {
               		    	                if(tolower(character) != tolower(test))
               		    	                {
               		    	                    statusB = CE_FILE_NOT_FOUND; // it's not a match
               		    	                    break;
               		    	                }
               		    	            }

										index++;
										if(index == DIR_NAMECOMP)
										{
											if(foundLFN && (fileCompareLfnIndex <= fileFoundMaxLfnIndex))
												statusB = CE_FILE_NOT_FOUND; // it's not a match
											break;
										}
               		    	        }
               		    	    }
							}
          	            	break;
				  }

				// If the comparision of each character in LFN is completed
				if(statusB == CE_GOOD)
				{
					if(foundLFN)
						fHandle++;

                	state = Fill_File_Object(foDest, &fHandle);

					if(foundLFN)
						fHandle--;

               		/* We got something get the attributes */
               		attrib = foDest->attributes;

               		attrib &= ATTR_MASK;

               		switch (mode)
               		{
               		    case 0:
               		        // see if we are a volume id or hidden, ignore
               		        if(attrib == ATTR_VOLUME)
               		            statusB = CE_FILE_NOT_FOUND;
               		        break;

               		    case 1:
               		        // Check for attribute match
               		        if ((attrib & compareAttrib) != 0)
               		            statusB = CE_FILE_NOT_FOUND; // Indicate the already filled file data is correct and go back
               		        if(foundLFN)
               		        	foDest->utf16LFNlength = fileFoundLength;
               		        else
								foDest->utf16LFNlength = 0;
               		        break;
               		}
				}
				#else
				{
               		 /* We got something */
               		 // get the attributes
               		 attrib = foDest->attributes;

               		 attrib &= ATTR_MASK;
               		 switch (mode)
               		 {
               		     case 0:
               		         // see if we are a volume id or hidden, ignore
               		         if(attrib != ATTR_VOLUME)
               		         {
               		             statusB = CE_GOOD;
               		             character = (uint8_t)'m'; // random value

               		             // search for one. if status = TRUE we found one
               		             for(index = 0; index < DIR_NAMECOMP; index++)
               		             {
               		                 // get the source character
               		                 character = foDest->name[index];
               		                 // get the destination character
               		                 test = foCompareTo->name[index];
               		                 if(tolower(character) != tolower(test))
               		                 {
               		                     statusB = CE_FILE_NOT_FOUND; // Nope its not a match
               		                     break;
               		                 }
               		             }// for loop
               		         } // not dir nor vol
               		         break;

               		     case 1:
               		         // Check for attribute match
               		         if (((attrib & compareAttrib) == 0) && (attrib != ATTR_LONG_NAME))
               		         {
               		             statusB = CE_GOOD;                 // Indicate the already filled file data is correct and go back
               		             character = (uint8_t)'m';             // random value
               		             if (foCompareTo->name[0] != '*')   //If "*" is passed for comparion as 1st char then don't proceed. Go back, file alreay found.
               		             {
               		                 for (index = 0; index < DIR_NAMESIZE; index++)
               		                 {
               		                     // Get the source character
               		                     character = foDest->name[index];
               		                     // Get the destination character
               		                     test = foCompareTo->name[index];
               		                     if (test == '*')
               		                         break;
               		                     if (test != '?')
               		                     {
               		                         if(tolower(character) != tolower(test))
               		                         {
               		                             statusB = CE_FILE_NOT_FOUND; // it's not a match
               		                             break;
               		                         }
               		                     }
               		                 }
               		             }

               		             // Before calling this "FILEfind" fn, "formatfilename" must be called. Hence, extn always starts from position "8".
               		             if ((foCompareTo->name[8] != '*') && (statusB == CE_GOOD))
               		             {
               		                 for (index = 8; index < DIR_NAMECOMP; index++)
               		                 {
               		                     // Get the source character
               		                     character = foDest->name[index];
               		                     // Get the destination character
               		                     test = foCompareTo->name[index];
               		                     if (test == '*')
               		                         break;
               		                     if (test != '?')
               		                     {
               		                         if(tolower(character) != tolower(test))
               		                         {
               		                             statusB = CE_FILE_NOT_FOUND; // it's not a match
               		                             break;
               		                         }
               		                     }
               		                 }
               		             }

               		         } // Attribute match

               		         break;
               		 }
            	}
  				#endif
            } // not found
            else
            {
				#if defined(SUPPORT_LFN)
					lfnFirstCheck = FALSE;
				#endif
                /*** looking for an empty/re-usable entry ***/
                if ( cmd == LOOK_FOR_EMPTY_ENTRY)
                    statusB = CE_GOOD;
            } // found or not

			#if defined(SUPPORT_LFN)
//            if(foundLFN)
//				fHandle = fHandle + 2;
//			 	fHandle++;
//			else
			#endif
            	// increment it no matter what happened
            	fHandle++;

        }// while
    }

    return(statusB);
} // FILEFind


/**************************************************************************
  Function:
    CETYPE FILEopen (FILEOBJ fo, uint16_t *fHandle, char type)
  Summary:
    Loads file information from the device
  Conditions:
    This function should not be called by the user.
  Input:
    fo -       File to be opened
    fHandle -  Location of file
    type -
         -     FS_WRITE -  Create a new file or replace an existing file
         -     FS_READ -   Read data from an existing file
         -     FS_APPEND - Append data to an existing file
  Return Values:
    CE_GOOD -            FILEopen successful
    CE_NOT_INIT -        Device is not yet initialized
    CE_FILE_NOT_FOUND -  Could not find the file on the device
    CE_BAD_SECTOR_READ - A bad read of a sector occured
  Side Effects:
    None
  Description:
    This function will cache a directory entry in the directory specified
    by the dirclus parameter of hte FSFILE object 'fo.'  The offset of the
    entry in the directory is specified by fHandle.  Once the directory entry
    has been loaded, the first sector of the file can be loaded using the
    cluster value specified in the directory entry. The type argument will
    specify the mode the files will be opened in.  This will allow this
    function to set the correct read/write flags for the file.
  Remarks:
    If the mode the file is being opened in is a plus mode (e.g. FS_READ+) the
    flags will be modified further in the FSfopen function.
  **************************************************************************/

CETYPE FILEopen (FILEOBJ fo, uint16_t *fHandle, char type)
{
    DISK   *dsk;      //Disk structure
    uint8_t    r;               //Result of search for file
    uint32_t    l;               //lba of first sector of first cluster
    CETYPE    error = CE_GOOD;
    uint8_t value;

    dsk = (DISK *)(fo->dsk);
    if (dsk->mount == FALSE)
    {
        error = CE_NOT_INIT;
    }
    else
    {
        // load the sector
        fo->dirccls = fo->dirclus;
        // Cache no matter what if it's the first entry
        if (*fHandle == 0)
        {
            if (Cache_File_Entry(fo, fHandle, TRUE) == NULL)
            {
                error = CE_BADCACHEREAD;
            }
        }
        else
        {
            // If it's not the first, only cache it if it's
            // not divisible by the number of entries per sector
            // If it is, Fill_File_Object will cache it
            if ((*fHandle & 0xf) != 0)
            {
                if (Cache_File_Entry (fo, fHandle, TRUE) == NULL)
                {
                    error = CE_BADCACHEREAD;
                }
            }
        }

        // Fill up the File Object with the information pointed to by fHandle
        r = Fill_File_Object(fo, fHandle);
        if (r != FOUND)
            error = CE_FILE_NOT_FOUND;
        else
        {
            fo->seek = 0;               // first uint8_t in file
            fo->ccls = fo->cluster;     // first cluster
            fo->sec = 0;                // first sector in the cluster
            fo->pos = 0;                // first uint8_t in sector/cluster

            if  ( r == NOT_FOUND)
            {
                error = CE_FILE_NOT_FOUND;
            }
            else
            {
                // Determine the lba of the selected sector and load
                l = Cluster2Sector(dsk,fo->ccls);

                gBufferOwner = fo;
                if (gLastDataSectorRead != l)
                {
                    gBufferZeroed = FALSE;
                    while((value = MDD_SectorRead( l, dsk->buffer)) == 0xff);
                    if(value == 0)
                        error = CE_BAD_SECTOR_READ;
                    gLastDataSectorRead = l;
                }
            } // -- found

            fo->flags.FileWriteEOF = FALSE;
            // Set flag for operation type

        } // -- r = Found
    } // -- Mounted
    return (error);
} // -- FILEopen


/*************************************************************************
  Function:
    uint8_t FILEget_next_cluster(FSFILE *fo, uint32_t n)
  Summary:
    Step through a chain of clusters
  Conditions:
    None
  Input:
    fo - The file to get the next cluster of
    n -  Number of links in the FAT cluster chain to jump through
  Return Values:
    CE_GOOD - Operation successful
    CE_BAD_SECTOR_READ - A bad read occured of a sector
    CE_INVALID_CLUSTER - Invalid cluster value \> maxcls
    CE_FAT_EOF - Fat attempt to read beyond EOF
  Side Effects:
    None
  Description:
    This function will load 'n' proximate clusters for a file from
    the FAT on the device.  It will stop checking for clusters if the
    ReadFAT function returns an error, if it reaches the last cluster in
    a file, or if the device tries to read beyond the last cluster used
    by the device.
  Remarks:
    None
  *************************************************************************/

uint8_t FILEget_next_cluster(FSFILE *fo, uint32_t n)
{
    uint32_t         c, c2, ClusterFailValue, LastClustervalue;
    uint8_t          error = CE_GOOD;
    DISK *      disk;

    disk = fo->dsk;

    /* Settings based on FAT type */
    switch (disk->type)
    {
#ifdef SUPPORT_FAT32 // If FAT32 supported.
        case FAT32:
            LastClustervalue = LAST_CLUSTER_FAT32;
            ClusterFailValue  = CLUSTER_FAIL_FAT32;
            break;
#endif
        case FAT12:
            LastClustervalue = LAST_CLUSTER_FAT12;
            ClusterFailValue  = CLUSTER_FAIL_FAT16;
            break;
        case FAT16:
        default:
            LastClustervalue = LAST_CLUSTER_FAT16;
            ClusterFailValue  = CLUSTER_FAIL_FAT16;
            break;
    }

    // loop n times
    do
    {
        // get the next cluster link from FAT
        c2 = fo->ccls;
        if ( (c = ReadFAT( disk, c2)) == ClusterFailValue)
            error = CE_BAD_SECTOR_READ;
        else
        {
            // check if cluster value is valid
            if ( c >= disk->maxcls)
            {
                error = CE_INVALID_CLUSTER;
            }

            // compare against max value of a cluster in FAT
            // return if eof
            if ( c >= LastClustervalue)    // check against eof
            {
                error = CE_FAT_EOF;
            }
        }

        // update the FSFILE structure
        fo->ccls = c;

    } while ((--n > 0) && (error == CE_GOOD));// loop end

    return(error);
} // get next cluster


/**************************************************************************
  Function:
    uint8_t DISKmount ( DISK *dsk)
  Summary:
    Initialies the device and loads MBR and boot sector information
  Conditions:
    This function should not be called by the user.
  Input:
    dsk -  The disk structure to be initialized.
  Return Values:
    CE_GOOD -       Disk mounted
    CE_INIT_ERROR - Initialization error has occured
    CE_UNSUPPORTED_SECTOR_SIZE - Media sector size bigger than
                MEDIA_SECTOR_SIZE as defined in FSconfig.h.
  Side Effects:
    None
  Description:
    This function will use the function pointed to by the MDD_MediaInitialize
    function pointer to initialize the device (if any initialization is
    required).  It then attempts to load the master boot record with the
    LoadMBR function and the boot sector with the LoadBootSector function.
    These two functions will be used to initialize a global DISK structure
    that will be used when accessing file information in the future.
  Remarks:
    None
  **************************************************************************/

uint8_t DISKmount( DISK *dsk)
{
    uint8_t                error = CE_GOOD;
    MEDIA_INFORMATION   *mediaInformation;

    dsk->mount = FALSE; // default invalid
    dsk->buffer = gDataBuffer;    // assign buffer

    // Initialize the device
    while((mediaInformation = MDD_MediaInitialize()) == NULL);
    if (mediaInformation->errorCode != MEDIA_NO_ERROR)
    {
        error = CE_INIT_ERROR;
        FSerrno = CE_INIT_ERROR;
    }
    else
    {
        // If the media initialization routine determined the sector size,
        // check it and make sure we can support it.
        if (mediaInformation->validityFlags.bits.sectorSize)
        {
			dsk->sectorSize = mediaInformation->sectorSize;
            if (mediaInformation->sectorSize > MEDIA_SECTOR_SIZE)
            {
                error = CE_UNSUPPORTED_SECTOR_SIZE;
                FSerrno = CE_UNSUPPORTED_SECTOR_SIZE;
                return error;
            }
        }

        // Load the Master Boot Record (partition)
        if((error = LoadMBR(dsk)) == CE_GOOD)
        {
            // Now the boot sector
            if((error = LoadBootSector(dsk)) == CE_GOOD)
                dsk->mount = TRUE; // Mark that the DISK mounted successfully
        }
    } // -- Load file parameters

    return(error);
} // -- mount



/********************************************************************
  Function:
    CETYPE LoadMBR ( DISK *dsk)
  Summary:
    Loads the MBR and extracts necessary information
  Conditions:
    This function should not be called by the user.
  Input:
    dsk -  The disk containing the master boot record to be loaded
  Return Values:
    CE_GOOD -            MBR loaded successfully
    CE_BAD_SECTOR_READ - A bad read occured of a sector
    CE_BAD_PARTITION -   The boot record is bad
  Side Effects:
    None
  Description:
    The LoadMBR function will use the function pointed to by the
    MDD_SectorRead function pointer to read the 0 sector from the
    device.  If a valid boot signature is obtained, this function
    will compare fields in that cached sector to the values that
    would be present if that sector was a boot sector.  If all of
    those values match, it will be assumed that the device does not
    have a master boot record and the 0 sector is actually the boot
    sector.  Otherwise, data about the partition and the actual
    location of the boot sector will be loaded from the MBR into
    the DISK structure pointed to by 'dsk.'
  Remarks:
    None
  ********************************************************************/

uint8_t LoadMBR(DISK *dsk)
{
    PT_MBR  Partition;
    uint8_t error = CE_GOOD;
    uint8_t type;
    BootSec BSec;
    uint8_t value;

    while((value = MDD_SectorRead( FO_MBR, dsk->buffer)) == 0xff);
    // Get the partition table from the MBR
    if ( value != TRUE)
    {
        error = CE_BAD_SECTOR_READ;
        FSerrno = CE_BAD_SECTOR_READ;
    }
    else
    {
        // Check if the card has no MBR
        BSec = (BootSec) dsk->buffer;

        if((BSec->Signature0 == FAT_GOOD_SIGN_0) && (BSec->Signature1 == FAT_GOOD_SIGN_1))
        {
         // Technically, the OEM name is not for indication
         // The alternative is to read the CIS from attribute
         // memory.  See the PCMCIA metaformat for more details
#if defined (__C30__) || defined (__PIC32MX__)
            if ((Readuint8_t( dsk->buffer, BSI_FSTYPE ) == 'F') && \
            (Readuint8_t( dsk->buffer, BSI_FSTYPE + 1 ) == 'A') && \
            (Readuint8_t( dsk->buffer, BSI_FSTYPE + 2 ) == 'T') && \
            (Readuint8_t( dsk->buffer, BSI_FSTYPE + 3 ) == '1') && \
            (Readuint8_t( dsk->buffer, BSI_BOOTSIG) == 0x29))
#else
            if ((BSec->FAT.FAT_16.BootSec_FSType[0] == 'F') && \
                (BSec->FAT.FAT_16.BootSec_FSType[1] == 'A') && \
                (BSec->FAT.FAT_16.BootSec_FSType[2] == 'T') && \
                (BSec->FAT.FAT_16.BootSec_FSType[3] == '1') && \
                (BSec->FAT.FAT_16.BootSec_BootSig == 0x29))
#endif
             {
                dsk->firsts = 0;
                dsk->type = FAT16;
                return CE_GOOD;
             }
             else
             {
#if defined (__C30__) || defined (__PIC32MX__)
                if ((Readuint8_t( dsk->buffer, BSI_FAT32_FSTYPE ) == 'F') && \
                    (Readuint8_t( dsk->buffer, BSI_FAT32_FSTYPE + 1 ) == 'A') && \
                    (Readuint8_t( dsk->buffer, BSI_FAT32_FSTYPE + 2 ) == 'T') && \
                    (Readuint8_t( dsk->buffer, BSI_FAT32_FSTYPE + 3 ) == '3') && \
                    (Readuint8_t( dsk->buffer, BSI_FAT32_BOOTSIG) == 0x29))
#else
                if ((BSec->FAT.FAT_32.BootSec_FilSysType[0] == 'F') && \
                    (BSec->FAT.FAT_32.BootSec_FilSysType[1] == 'A') && \
                    (BSec->FAT.FAT_32.BootSec_FilSysType[2] == 'T') && \
                    (BSec->FAT.FAT_32.BootSec_FilSysType[3] == '3') && \
                    (BSec->FAT.FAT_32.BootSec_BootSig == 0x29))
#endif
                {
                    dsk->firsts = 0;
                    dsk->type = FAT32;
                    return CE_GOOD;
                }
            }
        }
        // assign it the partition table strucutre
        Partition = (PT_MBR)dsk->buffer;

        // Ensure its good
        if((Partition->Signature0 != FAT_GOOD_SIGN_0) || (Partition->Signature1 != FAT_GOOD_SIGN_1))
        {
            FSerrno = CE_BAD_PARTITION;
            error = CE_BAD_PARTITION;
        }
        else
        {
            uint8_t i;
            PTE_MBR* partitionEntry = &Partition->Partition0;

            for(i=0; i<4; i++)
            {                
                /*    Valid Master Boot Record Loaded   */

                // Get the 32 bit offset to the first partition
                dsk->firsts = partitionEntry->PTE_FrstSect;

                // check if the partition type is acceptable
                  type = partitionEntry->PTE_FSDesc;

                switch (type)
                {
                    case 0x01:
                        dsk->type = FAT12;
                        break;

                case 0x04:
                    case 0x06:
                    case 0x0E:
                        dsk->type = FAT16;
                        return(error);

                    case 0x0B:
                    case 0x0C:
                        #ifdef SUPPORT_FAT32 // If FAT32 supported.
                            dsk->type = FAT32;    // FAT32 is supported too
                            return(error);
                        #endif
                } // switch

                /* If we are here, we didn't find a matching partition.  We
                   should increment to the next partition table entry */
                partitionEntry++;
            }

            FSerrno = CE_UNSUPPORTED_FS;
            error = CE_UNSUPPORTED_FS;
        }
    }

    return(error);
}// -- LoadMBR

/**************************************************************************
  Function:
    uint8_t LoadBootSector (DISK *dsk)
  Summary:
    Load the boot sector and extract the necessary information
  Conditions:
    This function should not be called by the user.
  Input:
    dsk -  The disk containing the boot sector
  Return Values:
    CE_GOOD -                    Boot sector loaded
    CE_BAD_SECTOR_READ -         A bad read occured of a sector
    CE_NOT_FORMATTED -           The disk is of an unsupported format
    CE_CARDFAT32 -               FAT 32 device not supported
    CE_UNSUPPORTED_SECTOR_SIZE - The sector size is not supported
  Side Effects:
    None
  Description:
    LoadBootSector will use the function pointed to by the MDD_SectorWrite
    function pointer to load the boot sector, whose location was obtained
    by a previous call of LoadMBR.  If the boot sector is loaded successfully,
    partition information will be calcualted from it and copied into the DISK
    structure pointed to by 'dsk.'
  Remarks:
    None
  **************************************************************************/


uint8_t LoadBootSector(DISK *dsk)
{
    uint32_t       RootDirSectors;
    uint32_t       TotSec,DataSec;
    uint8_t        error = CE_GOOD;
    BootSec        BSec;
    uint16_t        uint8_tsPerSec;
    uint16_t        ReservedSectorCount;
    uint8_t        value;
    #if defined(SUPPORT_FAT32)
    bool        TriedSpecifiedBackupBootSec = FALSE;
    bool        TriedBackupBootSecAtAddress6 = FALSE;
    #endif

    // Get the Boot sector
    while((value =  MDD_SectorRead( dsk->firsts, dsk->buffer)) == 0xff);

    if(value != TRUE)
    {
        error = CE_BAD_SECTOR_READ;
    }
    else
    {
        BSec = (BootSec)dsk->buffer;

        do      //test each possible boot sector (FAT32 can have backup boot sectors)
        {

            //Verify the Boot Sector has a valid signature
            if(    (BSec->Signature0 != FAT_GOOD_SIGN_0)
                || (BSec->Signature1 != FAT_GOOD_SIGN_1)
              )
            {
                error = CE_NOT_FORMATTED;
            }
            else   
            {

                do      //loop just to allow a break to jump out of this section of code
                {
    
                    // Read the count of reserved sectors
                    ReservedSectorCount = Reauint32_t( dsk->buffer, BSI_RESRVSEC );
                    // Load the count of sectors per cluster
                    dsk->SecPerClus = Readuint8_t( dsk->buffer, BSI_SPC );
                    // Load the sector number of the first FAT sector
                    dsk->fat = dsk->firsts + ReservedSectorCount;
                    // Load the count of FAT tables
                    dsk->fatcopy    = Readuint8_t( dsk->buffer, BSI_FATCOUNT );
                    // Load the size of the FATs
                    dsk->fatsize = Reauint32_t( dsk->buffer, BSI_SPF );
                    if(dsk->fatsize == 0)
                        dsk->fatsize  = Readuint32_t( dsk->buffer, BSI_FATSZ32 );
                    // Calculate the location of the root sector (for FAT12/16)
                    dsk->root = dsk->fat + (uint32_t)(dsk->fatcopy * (uint32_t)dsk->fatsize);
                    // Determine the max size of the root (will be 0 for FAT32)
                    dsk->maxroot = Reauint32_t( dsk->buffer, BSI_ROOTDIRENTS );
    
                    // Determine the total number of sectors in the partition
                    TotSec = Reauint32_t( dsk->buffer, BSI_TOTSEC16 );
                    if( TotSec == 0 )
                        TotSec = Readuint32_t( dsk->buffer, BSI_TOTSEC32 );
    
                    // Calculate the number of uint8_ts in each sector
                    uint8_tsPerSec = Reauint32_t( dsk->buffer, BSI_BPS );
                    if( (uint8_tsPerSec == 0) || ((uint8_tsPerSec & 1) == 1) )
                    {
                        error = CE_UNSUPPORTED_SECTOR_SIZE;
                        break;
                    }
    
                    // Calculate the number of sectors in the root (will be 0 for FAT32)
                    RootDirSectors = ((dsk->maxroot * NUMBER_OF_BYTES_IN_DIR_ENTRY) + (uint8_tsPerSec - 1)) / uint8_tsPerSec;
                    // Calculate the number of data sectors on the card
                    DataSec = TotSec - (ReservedSectorCount + (dsk->fatcopy * dsk->fatsize )  + RootDirSectors);
                    // Calculate the maximum number of clusters on the card
                    dsk->maxcls = DataSec / dsk->SecPerClus;
    
                    // Determine the file system type based on the number of clusters used
                    if(dsk->maxcls < 4085)
                    {
                        dsk->type = FAT12;
                    }
                    else
                    {
                        if(dsk->maxcls < 65525)
                        {
                            dsk->type = FAT16;
                        }
                        else
                        {
                            #ifdef SUPPORT_FAT32
                                dsk->type = FAT32;
                            #else
                                error = CE_CARDFAT32;
                            #endif
                        }
                    }
        
                    #ifdef SUPPORT_FAT32
                        if (dsk->type == FAT32)
                        {
                            #ifdef __18CXX
                                FatRootDirClusterValue =  BSec->FAT.FAT_32.BootSec_RootClus;
                            #else
                                FatRootDirClusterValue = Readuint32_t( dsk->buffer, BSI_ROOTCLUS );
                            #endif
                            dsk->data = dsk->root + RootDirSectors;
                        }
                        else
                    #endif
                    {
                        FatRootDirClusterValue = 0;
                        dsk->data = dsk->root + ( dsk->maxroot >> 4);
                    }
    
                #ifdef __18CXX
                    if(BSec->FAT.FAT_16.BootSec_BPS > MEDIA_SECTOR_SIZE)
                #else
                    if(uint8_tsPerSec > MEDIA_SECTOR_SIZE)
                #endif
                    {
                        error = CE_UNSUPPORTED_SECTOR_SIZE;
                    }

                }while(0);  // do/while loop designed to allow to break out if
                            //   there is an error detected without returning
                            //   from the function.

            }

            #if defined(SUPPORT_FAT32)
            if ((dsk->type == FAT32) || ((error != CE_GOOD) && ((BSec->FAT.FAT_32.BootSec_BootSig == 0x29) || (BSec->FAT.FAT_32.BootSec_BootSig == 0x28))))
            {
                //Check for possible errors in the formatting
                if(    (BSec->FAT.FAT_32.BootSec_TotSec16 != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[0] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[1] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[2] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[3] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[4] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[5] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[6] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[7] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[8] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[9] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[10] != 0)
                    || (BSec->FAT.FAT_32.BootSec_Reserved[11] != 0)
                    || ((BSec->FAT.FAT_32.BootSec_BootSig != 0x29) && (BSec->FAT.FAT_32.BootSec_BootSig != 0x28))
                  )
                {
                    error = CE_NOT_FORMATTED;
                }
    
                //If there were formatting errors then in FAT32 we can try to use
                //  the backup boot sector
                if((error != CE_GOOD) && (TriedSpecifiedBackupBootSec == FALSE))
                {
                    TriedSpecifiedBackupBootSec = TRUE;
    
                    while((value =  MDD_SectorRead( dsk->firsts + BSec->FAT.FAT_32.BootSec_BkBootSec, dsk->buffer)) == 0xff);

                    if(value != TRUE)
                    {
                        FSerrno = CE_BAD_SECTOR_READ;
                        return CE_BAD_SECTOR_READ;
                    }
                    else
                    {
                        error = CE_GOOD;
                        continue;
                    }
                }
    
                if((error != CE_GOOD) && (TriedBackupBootSecAtAddress6 == FALSE))
                {
                    TriedBackupBootSecAtAddress6 = TRUE;
    
                    //Here we are using the magic number 6 because the FAT32 specification
                    //  recommends that "No value other than 6 is recommended."  We've
                    //  already tried using the value specified in the BPB_BkBootSec
                    //  field and it must have failed
                    while((value = MDD_SectorRead( dsk->firsts + 6, dsk->buffer)) == 0xff);
                    if(value != TRUE)
                    {
                        FSerrno = CE_BAD_SECTOR_READ;
                        return CE_BAD_SECTOR_READ;
                    }
                    else
                    {
                        error = CE_GOOD;
                        continue;
                    }
                }

            }   //type == FAT32
            #endif  //SUPPORT_FAT32
            break;
        }
        while(1);
    }

    if(error != CE_GOOD)
    {
        FSerrno = error;
    }

    return(error);
}



/*************************************************************************
  Function:
    uint32_t GetFullClusterNumber (DIRENTRY entry)
  Summary:
    Gets the cluster number from a directory entry
  Conditions:
    This function should not be called by the user.
  Input:
    entry - The cached directory entry to get the cluster number from
  Returns:
    The cluster value from the passed directory entry
  Side Effects:
    None.
  Description:
    This function will load both the high and low 16-bit first cluster
    values of a file from a directory entry and copy them into a 32-bit
    cluster number variable, which will be returned.
  Remarks:
    None
  *************************************************************************/

uint32_t GetFullClusterNumber(DIRENTRY entry)
{

    uint32_t TempFullClusterCalc = 0;

#ifndef SUPPORT_FAT32 // If FAT32 Not supported.
    entry->DIR_FstClusHI = 0; // If FAT32 is not supported then Higher uint16_t of the address is "0"
#endif

    // Get the cluster
    TempFullClusterCalc = (entry->DIR_FstClusHI);
    TempFullClusterCalc = TempFullClusterCalc << 16;
    TempFullClusterCalc |= entry->DIR_FstClusLO;

    return TempFullClusterCalc;
}

/**************************************************************************
  Function:
    DIRENTRY Cache_File_Entry( FILEOBJ fo, uint16_t * curEntry, uint8_t ForceRead)
  Summary:
    Load a file entry
  Conditions:
    This function should not be called by the user.
  Input:
    fo -         File information
    curEntry -   Offset of the directory entry to load.
    ForceRead -  Forces loading of a new sector of the directory.
  Return:
    DIRENTRY - Pointer to the directory entry that was loaded.
  Side Effects:
    Any unwritten data in the data buffer will be written to the device.
  Description:
    Load the sector containing the file entry pointed to by 'curEntry'
    from the directory pointed to by the variables in 'fo.'
  Remarks:
    Any modification of this function is extremely likely to
    break something.
  **************************************************************************/

DIRENTRY Cache_File_Entry( FILEOBJ fo, uint16_t * curEntry, uint8_t ForceRead)
{
    DIRENTRY dir;
    DISK *dsk;
    uint32_t sector;
    uint32_t cluster, LastClusterLimit;
    uint32_t ccls;
    uint8_t offset2;
    uint8_t numofclus;
    uint8_t dirEntriesPerSector;
    uint8_t value;

    dsk = fo->dsk;

    // get the base sector of this directory
    cluster = fo->dirclus;
    ccls = fo->dirccls;

	dirEntriesPerSector = dsk->sectorSize/32;

     // figure out the offset from the base sector
    offset2  = (*curEntry / dirEntriesPerSector);

    /* Settings based on FAT type */
    switch (dsk->type)
    {
#ifdef SUPPORT_FAT32 // If FAT32 supported.
        case FAT32:
            // the ROOT is always cluster based in FAT32
            /* In FAT32: There is no ROOT region. Root etries are made in DATA region only.
            Every cluster of DATA which is accupied by ROOT is tracked by FAT table/entry so the ROOT can grow
            to an amount which is restricted only by available free DATA region. */
            offset2  = offset2 % (dsk->SecPerClus);   // figure out the offset
            LastClusterLimit = LAST_CLUSTER_FAT32;
            break;
#endif
        case FAT12:
        case FAT16:
        default:
            // if its the root its not cluster based
            if(cluster != 0)
                offset2  = offset2 % (dsk->SecPerClus);   // figure out the offset
            LastClusterLimit = LAST_CLUSTER_FAT16;
            break;
    }

    // check if a new sector of the root must be loaded
    if (ForceRead || ((*curEntry & MASK_MAX_FILE_ENTRY_LIMIT_BITS) == 0))     // only 16 entries per sector
    {
        // see if we have to load a new cluster
        if(((offset2 == 0) && (*curEntry >= dirEntriesPerSector)) || ForceRead)
        {
            if(cluster == 0)
            {
                ccls = 0;
            }
            else
            {
                // If ForceRead, read the number of sectors from 0
                if(ForceRead)
                    numofclus = ((uint16_t)(*curEntry) / (uint16_t)(((uint16_t)dirEntriesPerSector) * (uint16_t)dsk->SecPerClus));
                // Otherwise just read the next sector
                else
                    numofclus = 1;

                // move to the correct cluster
                while(numofclus)
                {
                    ccls = ReadFAT(dsk, ccls);

                    if(ccls >= LastClusterLimit)
                        break;
                    else
                        numofclus--;
                }
            }
        }

        // see if that we have a valid cluster number
        if(ccls < LastClusterLimit)
        {
            fo->dirccls = ccls; // write it back

            sector = Cluster2Sector(dsk,ccls);

            /* see if we are root and about to go pass our boundaries
            FAT32 stores the root directory in the Data Region along with files and other directories,
            allowing it to grow without such a restraint */
            if((ccls == FatRootDirClusterValue) && ((sector + offset2) >= dsk->data) && (FAT32 != dsk->type))
            {
                dir = ((DIRENTRY)NULL);   // reached the end of the root
            }
            else
            {
                gBufferOwner = NULL;
                gBufferZeroed = FALSE;

                while((value =  MDD_SectorRead( sector + offset2, dsk->buffer)) == 0xff); // if FALSE: sector could not be read.
                if(value != TRUE)
                {
                    dir = ((DIRENTRY)NULL);
                }
                else // Sector has been read properly, Copy the root entry info of the file searched.
                {
                    if(ForceRead)    // Buffer holds all 16 root entry info. Point to the one required.
                        dir = (DIRENTRY)((DIRENTRY)dsk->buffer) + ((*curEntry)%dirEntriesPerSector);
                    else
                        dir = (DIRENTRY)dsk->buffer;
                }
                gLastDataSectorRead = 0xFFFFFFFF;
            }
        }
        else
        {
            nextClusterIsLast = TRUE;
            dir = ((DIRENTRY)NULL);
        }
    }
    else
        dir = (DIRENTRY)((DIRENTRY)dsk->buffer) + ((*curEntry)%dirEntriesPerSector);

    return(dir);
} // Cache_File_Entry

/*********************************************************************************
  Function:
    void FSGetDiskProperties(FS_DISK_PROPERTIES* properties)
  Summary:
    Allows user to get the disk properties (size of disk, free space, etc)
  Conditions:
    1) ALLOW_GET_DISK_PROPERTIES must be defined in FSconfig.h
    2) a FS_DISK_PROPERTIES object must be created before the function is called
    3) the new_request member of the FS_DISK_PROPERTIES object must be set before
        calling the function for the first time.  This will start a new search.
    4) this function should not be called while there is a file open.  Close all
        files before calling this function.
  Input:
    properties - a pointer to a FS_DISK_PROPERTIES object where the results should
      be stored.
  Return Values:
    This function returns void.  The properties_status of the previous call of this 
      function is located in the properties.status field.  This field has the 
      following possible values:

    FS_GET_PROPERTIES_NO_ERRORS - operation completed without error.  Results
      are in the properties object passed into the function.
    FS_GET_PROPERTIES_DISK_NOT_MOUNTED - there is no mounted disk.  Results in
      properties object is not valid
    FS_GET_PROPERTIES_CLUSTER_FAILURE - there was a failure trying to read a 
      cluster from the drive.  The results in the properties object is a partial
      result up until the point of the failure.
    FS_GET_PROPERTIES_STILL_WORKING - the search for free sectors is still in
      process.  Continue calling this function with the same properties pointer 
      until either the function completes or until the partial results meets the
      application needs.  The properties object contains the partial results of
      the search and can be used by the application.  
  Side Effects:
    Can cause errors if called when files are open.  Close all files before
    calling this function.

    Calling this function without setting the new_request member on the first
    call can result in undefined behavior and results.

    Calling this function after a result is returned other than
    FS_GET_PROPERTIES_STILL_WORKING can result in undefined behavior and results.
  Description:  
    This function returns the information about the mounted drive.  The results 
    member of the properties object passed into the function is populated with 
    the information about the drive.    

    Before starting a new request, the new_request member of the properties
    input parameter should be set to TRUE.  This will initiate a new search
    request.

    This function will return before the search is complete with partial results.
    All of the results except the free_clusters will be correct after the first
    call.  The free_clusters will contain the number of free clusters found up
    until that point, thus the free_clusters result will continue to grow until
    the entire drive is searched.  If an application only needs to know that a 
    certain number of uint8_ts is available and doesn't need to know the total free
    size, then this function can be called until the required free size is
    verified.  To continue a search, pass a pointer to the same FS_DISK_PROPERTIES
    object that was passed in to create the search.

    A new search request sould be made once this function has returned a value 
    other than FS_GET_PROPERTIES_STILL_WORKING.  Continuing a completed search
    can result in undefined behavior or results.

    Typical Usage:
    <code>
    FS_DISK_PROPERTIES disk_properties;

    disk_properties.new_request = TRUE;

    do
    {
        FSGetDiskProperties(&disk_properties);
    } while (disk_properties.properties_status == FS_GET_PROPERTIES_STILL_WORKING);
    </code>

    results.disk_format - contains the format of the drive.  Valid results are 
      FAT12(1), FAT16(2), or FAT32(3).

    results.sector_size - the sector size of the mounted drive.  Valid values are
      512, 1024, 2048, and 4096.

    results.sectors_per_cluster - the number sectors per cluster.

    results.total_clusters - the number of total clusters on the drive.  This 
      can be used to calculate the total disk size (total_clusters * 
      sectors_per_cluster * sector_size = total size of drive in uint8_ts)

    results.free_clusters - the number of free (unallocated) clusters on the drive.
      This can be used to calculate the total free disk size (free_clusters * 
      sectors_per_cluster * sector_size = total size of drive in uint8_ts)

  Remarks:
    PIC24F size estimates:
      Flash - 400 uint8_ts (-Os setting)

    PIC24F speed estimates:
      Search takes approximately 7 seconds per Gigauint8_t of drive space.  Speed
        will vary based on the number of sectors per cluster and the sector size.
  *********************************************************************************/
#if defined(ALLOW_GET_DISK_PROPERTIES)
void FSGetDiskProperties(FS_DISK_PROPERTIES* properties)
{
    uint8_t    i;
    uint32_t   value = 0x0;

    if(properties->new_request == TRUE)
    {
        properties->disk = &gDiskData;
        properties->results.free_clusters = 0;
        properties->new_request = FALSE;

        if(properties->disk->mount != TRUE)
        {
            properties->properties_status = FS_GET_PROPERTIES_DISK_NOT_MOUNTED;
            return;
        }

        properties->properties_status = FS_GET_PROPERTIES_STILL_WORKING;
   
        properties->results.disk_format = properties->disk->type;
        properties->results.sector_size = properties->disk->sectorSize;
        properties->results.sectors_per_cluster = properties->disk->SecPerClus;
        properties->results.total_clusters = properties->disk->maxcls;

        /* Settings based on FAT type */
        switch (properties->disk->type)
        {
    #ifdef SUPPORT_FAT32 // If FAT32 supported.
            case FAT32:
                properties->private.EndClusterLimit = END_CLUSTER_FAT32;
                properties->private.ClusterFailValue = CLUSTER_FAIL_FAT32;
                break;
    #endif
            case FAT16:
                properties->private.EndClusterLimit = END_CLUSTER_FAT16;
                properties->private.ClusterFailValue = CLUSTER_FAIL_FAT16;
                break;
            case FAT12:
                properties->private.EndClusterLimit = END_CLUSTER_FAT12;
                properties->private.ClusterFailValue = CLUSTER_FAIL_FAT16;
                break;
        }
    
        properties->private.c = 2;

        properties->private.curcls = properties->private.c;
        ReadFAT(properties->disk, properties->private.c);
    }

    if(properties->disk == NULL)
    {
        properties->properties_status = FS_GET_PROPERTIES_DISK_NOT_MOUNTED;
        return;
    }

    if(properties->properties_status != FS_GET_PROPERTIES_STILL_WORKING)
    {
        return;
    }

    // sequentially scan through the FAT looking for an empty cluster
    for(i=0;i<255;i++)
    {
        // look at its value
        if ( (value = ReadFAT(properties->disk, properties->private.c)) == properties->private.ClusterFailValue)
        {
            properties->properties_status = FS_GET_PROPERTIES_CLUSTER_FAILURE;
            return;
        }

        // check if empty cluster found
        if (value == CLUSTER_EMPTY)
        {
            properties->results.free_clusters++;
        }

        properties->private.c++;    // check next cluster in FAT
        // check if reached last cluster in FAT, re-start from top
        if ((value == properties->private.EndClusterLimit) || (properties->private.c >= (properties->results.total_clusters + 2)))
            properties->private.c = 2;

        // check if full circle done, disk full
        if ( properties->private.c == properties->private.curcls)
        {
            properties->properties_status = FS_GET_PROPERTIES_NO_ERRORS;
            return;
        }
    }  // scanning for an empty cluster

    properties->properties_status = FS_GET_PROPERTIES_STILL_WORKING;
    return;
}
#endif

/************************************************************
  Function:
    int FSfclose(FSFILE *fo)
  Summary:
    Update file information and free FSFILE objects
  Conditions:
    File opened
  Input:
    fo -  Pointer to the file to close
  Return Values:
    0 -   File closed successfully
    EOF - Error closing the file
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    This function will update the directory entry for the
    file pointed to by 'fo' with the information contained
    in 'fo,' including the new file size and attributes.
    Timestamp information will also be loaded based on the
    method selected by the user and written to the entry
    as the last modified time and date.  The file entry will
    then be written to the device.  Finally, the memory
    used for the specified file object will be freed from
    the dynamic heap or the array of FSFILE objects.
  Remarks:
    A function to flush data to the device without closing the
    file can be created by removing the portion of this
    function that frees the memory and the line that clears
    the write flag.
  ************************************************************/

int FSfclose(FSFILE   *fo)
{
    uint16_t        fHandle;
#ifndef FS_DYNAMIC_MEM
    uint16_t        fIndex;
#endif
    int        error = 72;
#ifdef ALLOW_WRITES
    DIRENTRY    dir;
#endif

    FSerrno = CE_GOOD;
    fHandle = fo->entry;

#ifdef FS_DYNAMIC_MEM
    #ifdef	SUPPORT_LFN
		FS_free((unsigned char *)fo->utf16LFNptr);
	#endif
	FS_free((unsigned char *)fo);
#else

    for( fIndex = 0; fIndex < FS_MAX_FILES_OPEN; fIndex++ )
    {
        if( fo == &gFileArray[fIndex] )
        {
            gFileSlotOpen[fIndex] = TRUE;
            break;
        }
    }
#endif

    // File opened in read mode
    if (error == 72)
        error = 0;

    return(error);
} // FSfclose


/*******************************************************
  Function:
    void IncrementTimeStamp(DIRENTRY dir)
  Summary:
    Automatically set the timestamp to "don't care" data
  Conditions:
    Should not be called by the user.
  Input:
    dir -  Pointer to directory structure
  Return Values:
    None
  Side Effects:
    None
  Description:
    This function will increment the timestamp variable in
    the 'dir' directory entry.  This is used for the
    don't-care timing method.
  Remarks:
    None
  *******************************************************/
#ifdef INCREMENTTIMESTAMP
void IncrementTimeStamp(DIRENTRY dir)
{
    uint8_t          seconds;
    uint8_t          minutes;
    uint8_t          hours;

    uint8_t          day;
    uint8_t          month;
    uint8_t          year;

    seconds = (dir->DIR_WrtTime & 0x1f);
    minutes = ((dir->DIR_WrtTime & 0x07E0) >> 5);
    hours   = ((dir->DIR_WrtTime & 0xF800) >> 11);

    day     = (dir->DIR_WrtDate & 0x1f);
    month   = ((dir->DIR_WrtDate & 0x01E0) >> 5);
    year    = ((dir->DIR_WrtDate & 0xFE00) >> 9);

    if(seconds < 29)
    {
        // Increment number of seconds by 2
        // This clock method isn't intended to be accurate anyway
        seconds++;
    }
    else
    {
        seconds = 0x00;

        if(minutes < 59)
        {
            minutes++;
        }
        else
        {
            minutes = 0;

            if(hours < 23)
            {
                hours++;
            }
            else
            {
                hours = 0;
                if(day < 30)
                {
                    day++;
                }
                else
                {
                    day = 1;

                    if(month < 12)
                    {
                        month++;
                    }
                    else
                    {
                        month = 1;
                        // new year
                        year++;
                        // This is only valid until 2107
                    }
                }
            }
        }
    }

    dir->DIR_WrtTime = (uint16_t)(seconds);
    dir->DIR_WrtTime |= ((uint16_t)(minutes) << 5);
    dir->DIR_WrtTime |= ((uint16_t)(hours) << 11);

    dir->DIR_WrtDate = (uint16_t)(day);
    dir->DIR_WrtDate |= ((uint16_t)(month) << 5);
    dir->DIR_WrtDate |= ((uint16_t)(year) << 9);
}
#endif

/*****************************************************************
  Function:
    uint8_t Fill_File_Object(FILEOBJ fo, uint16_t *fHandle)
  Summary:
    Fill a file object with specified dir entry data
  Conditions:
    This function should not be called by the user.
  Input:
    fo -       Pointer to file structure
    fHandle -  Passed member's location
  Return Values:
    FOUND -     Operation successful
    NOT_FOUND - Operation failed
  Side Effects:
    None
  Description:
    This function will cache the sector of directory entries
    in the directory pointed to by the dirclus value in
    the FSFILE object 'fo' that contains the entry that
    corresponds to the fHandle offset.  It will then copy
    the file information for that entry into the 'fo' FSFILE
    object.
  Remarks:
    None.
  *****************************************************************/

uint8_t Fill_File_Object(FILEOBJ fo, uint16_t *fHandle)
{
    DIRENTRY    dir;
    uint8_t        index, a;
    uint8_t        character;
    uint8_t        status;
    uint8_t        test = 0;

    // Get the entry
    if (((*fHandle & MASK_MAX_FILE_ENTRY_LIMIT_BITS) == 0) && (*fHandle != 0)) // 4-bit mask because 16-root entries max per sector
    {
        fo->dirccls = fo->dirclus;
        dir = Cache_File_Entry(fo, fHandle, TRUE);
    }
    else
    {
        dir = Cache_File_Entry (fo, fHandle, FALSE);
    }


    // Make sure there is a directory left
    if(dir == (DIRENTRY)NULL)
    {
        status = NO_MORE;
    }
    else
    {
        // Read the first char of the file name
        a = dir->DIR_Name[0];

        // Check for empty or deleted directory
        if ( a == DIR_DEL)
		{
            status = NOT_FOUND;
		}
		else if ( a == DIR_EMPTY)
		{
			status = NO_MORE;
		}
        else
        {
            // Get the attributes
            a = dir->DIR_Attr;

            // print the file name and extension
            for (index=0; index < DIR_NAMESIZE; index++)
            {
                character = dir->DIR_Name[index];
                character = (uint8_t)toupper(character);
                fo->name[test++] = character;
            }

            // Get the attributes
            a = dir->DIR_Attr;

            // its possible to have an extension in a directory
            character = dir->DIR_Extension[0];

            // Get the file extension if its there
            for (index=0; index < DIR_EXTENSION; index++)
            {
                character = dir->DIR_Extension[index];
                character = (uint8_t)toupper(character);
                fo->name[test++] = character;
            }

            // done and done with the name
            //         fo->name[++test] = (uint8_t)'\0';

            // Now store the identifier
            fo->entry = *fHandle;

            // see if we are still a good file
            a = dir->DIR_Name[0];

            if(a == DIR_DEL)
                status = NOT_FOUND;
            else
                status = FOUND;

            // Now store the size
            fo->size = (dir->DIR_FileSize);

            fo->cluster = GetFullClusterNumber(dir); // Get Complete Cluster number.

            /// -Get and store the attributes
            a = dir->DIR_Attr;
            fo->attributes = a;

            // get the date and time
            if ((a & ATTR_DIRECTORY) != 0)
            {
                fo->time = dir->DIR_CrtTime;
                fo->date = dir->DIR_CrtDate;
            }
            else
            {
                fo->time = dir->DIR_WrtTime;
                fo->date = dir->DIR_WrtDate;
            }

        }// deleted directory
    }// Ensure we are still good
    return(status);
} // Fill_File_Object

/*****************************************************************
  Function:
    uint8_t Fill_LFN_Object(FILEOBJ fo, LFN_ENTRY *lfno, uint16_t *fHandle)
  Summary:
    Fill a LFN object with specified entry data
  Conditions:
    This function should not be called by the user.
  Input:
    fo -   Pointer to file structure
    lfno - Pointer to Long File Name Object
    fHandle -  Passed member's location
  Return Values:
    FOUND -     Operation successful
    NOT_FOUND - Operation failed
  Side Effects:
    None
  Description:
    This function will cache the sector of LFN entries
    in the directory pointed to by the dirclus value in
    the FSFILE object 'fo' that contains the entry that
    corresponds to the fHandle offset.  It will then copy
    the file information for that entry into the 'fo' FSFILE
    object.
  Remarks:
    None.
  *****************************************************************/
#if defined(SUPPORT_LFN)
uint8_t Fill_LFN_Object(FILEOBJ fo, LFN_ENTRY *lfno, uint16_t *fHandle)
{
    DIRENTRY    dir;
    uint8_t        tempVariable;
    uint8_t        *src,*dst;
    uint8_t        status;

    // Get the entry
    if (((*fHandle & MASK_MAX_FILE_ENTRY_LIMIT_BITS) == 0) && (*fHandle != 0)) // 4-bit mask because 16-root entries max per sector
    {
        fo->dirccls = fo->dirclus;
        dir = Cache_File_Entry(fo, fHandle, TRUE);
    }
    else
    {
        dir = Cache_File_Entry (fo, fHandle, FALSE);
    }


    // Make sure there is a directory left
    if(dir == (DIRENTRY)NULL)
    {
        status = NO_MORE;
    }
    else
    {
        // Read the first char of the file name
        tempVariable = dir->DIR_Name[0];

        // Check for empty or deleted directory
        if ( tempVariable == DIR_DEL)
		{
            status = NOT_FOUND;
		}
		else if ( tempVariable == DIR_EMPTY)
		{
			status = NO_MORE;
		}
        else
        {
            status = FOUND;

			dst = (uint8_t *)lfno;
			src = (uint8_t *)dir;

			// Copy the entry in the lfno object
			for(tempVariable = 0;tempVariable < 32;tempVariable++)
			{
				*dst++ = *src++;
			}
        }// deleted directory
    }// Ensure we are still good
    return(status);
} // Fill_File_Object
#endif
/************************************************************************
  Function:
    DIRENTRY LoadDirAttrib(FILEOBJ fo, uint16_t *fHandle)
  Summary:
    Load file information from a directory entry and cache the entry
  Conditions:
    This function should not be called by the user.
  Input:
    fo -       Pointer to file structure
    fHandle -  Information location
  Return Values:
    DIRENTRY - Pointer to the directory entry
    NULL -     Directory entry could not be loaded
  Side Effects:
    None
  Description:
    This function will cache the sector of directory entries
    in the directory pointed to by the dirclus value in
    the FSFILE object 'fo' that contains the entry that
    corresponds to the fHandle offset.  It will then return a pointer
    to the directory entry in the global data buffer.
  Remarks:
    None.
  ************************************************************************/

DIRENTRY LoadDirAttrib(FILEOBJ fo, uint16_t *fHandle)
{
    DIRENTRY    dir;
    uint8_t      a;

    fo->dirccls = fo->dirclus;
    // Get the entry
    dir = Cache_File_Entry( fo, fHandle, TRUE);
    if (dir == NULL)
        return NULL;

    // Read the first char of the file name
    a = dir->DIR_Name[0];

    // Make sure there is a directory left
    if(a == DIR_EMPTY)
        dir = (DIRENTRY)NULL;

    if(dir != (DIRENTRY)NULL)
    {
        // Check for empty or deleted directory
        if ( a == DIR_DEL)
            dir = (DIRENTRY)NULL;
        else
        {
            // Get the attributes
            a = dir->DIR_Attr;

            // scan through all the long dir entries
            while(a == ATTR_LONG_NAME)
            {
                (*fHandle)++;
                dir = Cache_File_Entry( fo, fHandle, FALSE);
                if (dir == NULL)
                    return NULL;
                a = dir->DIR_Attr;
            } // long file name while loop
        } // deleted dir
    }// Ensure we are still good

    return(dir);
} // LoadDirAttrib

/*********************************************************************
  Function:
    FSFILE * wFSfopen (const unsigned short int * fileName, const char *mode)
  Summary:
    Opens a file with UTF16 input 'fileName' on PIC24/PIC32/dsPIC MCU's.
  Conditions:
    For read modes, file exists; FSInit performed
  Input:
    fileName -  The name of the file to open
    mode -
         - FS_WRITE -      Create a new file or replace an existing file
         - FS_READ -       Read data from an existing file
         - FS_APPEND -     Append data to an existing file
         - FS_WRITEPLUS -  Create a new file or replace an existing file (reads also enabled)
         - FS_READPLUS -   Read data from an existing file (writes also enabled)
         - FS_APPENDPLUS - Append data to an existing file (reads also enabled)
  Return Values:
    FSFILE * - The pointer to the file object
    NULL -     The file could not be opened
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    This function opens a file with UTF16 input 'fileName' on PIC24/PIC32/dsPIC MCU's.
    First, RAM in the dynamic heap or static array will be allocated to a
    new FSFILE object. Then, the specified file name will be formatted to
    ensure that it's in 8.3 format or LFN format. Next, the FILEfind function
    will be used to search for the specified file name. If the name is found,
    one of three things will happen: if the file was opened in read mode, its
    file info will be loaded using the FILEopen function; if it was opened in
    write mode, it will be erased, and a new file will be constructed in
    its place; if it was opened in append mode, its file info will be
    loaded with FILEopen and the current location will be moved to the
    end of the file using the FSfseek function.  If the file was not
    found by FILEfind, a new file will be created if the mode was specified as
    a write or append mode.  In these cases, a pointer to the heap or
    static FSFILE object array will be returned. If the file was not
    found and the mode was specified as a read mode, the memory
    allocated to the file will be freed and the NULL pointer value
    will be returned.
  Remarks:
    None.
  *********************************************************************/
#ifdef SUPPORT_LFN
FSFILE * wFSfopen( const unsigned short int * fileName, const char *mode )
{
	FSFILE *result;
	utfModeFileName = TRUE;
	result = FSfopen((const char *)fileName,mode);
	utfModeFileName = FALSE;
	return result;
}
#endif

/*********************************************************************
  Function:
    FSFILE * FSfopen (const char * fileName, const char *mode)
  Summary:
    Opens a file with ascii input 'fileName' on PIC24/PIC32/dsPIC MCU's.
  Conditions:
    For read modes, file exists; FSInit performed
  Input:
    fileName -  The name of the file to open
    mode -
         - FS_WRITE -      Create a new file or replace an existing file
         - FS_READ -       Read data from an existing file
         - FS_APPEND -     Append data to an existing file
         - FS_WRITEPLUS -  Create a new file or replace an existing file (reads also enabled)
         - FS_READPLUS -   Read data from an existing file (writes also enabled)
         - FS_APPENDPLUS - Append data to an existing file (reads also enabled)
  Return Values:
    FSFILE * - The pointer to the file object
    NULL -     The file could not be opened
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    This function will open a ascii name file or directory on PIC24/PIC32/dsPIC MCU's.
    First, RAM in the dynamic heap or static array will be allocated to a
    new FSFILE object. Then, the specified file name will be formatted to
    ensure that it's in 8.3 format or LFN format. Next, the FILEfind function
    will be used to search for the specified file name. If the name is found,
    one of three things will happen: if the file was opened in read mode, its
    file info will be loaded using the FILEopen function; if it was opened in
    write mode, it will be erased, and a new file will be constructed in
    its place; if it was opened in append mode, its file info will be
    loaded with FILEopen and the current location will be moved to the
    end of the file using the FSfseek function.  If the file was not
    found by FILEfind, a new file will be created if the mode was specified as
    a write or append mode.  In these cases, a pointer to the heap or
    static FSFILE object array will be returned. If the file was not
    found and the mode was specified as a read mode, the memory
    allocated to the file will be freed and the NULL pointer value
    will be returned.
  Remarks:
    None.
  *********************************************************************/

FSFILE * FSfopen( const char * fileName, const char *mode )
{
    FILEOBJ    filePtr;
#ifndef FS_DYNAMIC_MEM
    int      fIndex;
#endif
    uint8_t   ModeC;
    uint16_t    fHandle;
    CETYPE   final;

    //Read the mode character
    ModeC = mode[0];

    if(MDD_WriteProtectState() && (ModeC != 'r') && (ModeC != 'R')) 
    { 
        FSerrno = CE_WRITE_PROTECTED; 
        return NULL; 
    } 

#ifdef FS_DYNAMIC_MEM
    filePtr = (FILEOBJ) FS_malloc(sizeof(FSFILE));
#else

    filePtr = NULL;

    //Pick available file structure
    for( fIndex = 0; fIndex < FS_MAX_FILES_OPEN; fIndex++ )
    {
        if( gFileSlotOpen[fIndex] )   //this slot is available
        {
            gFileSlotOpen[fIndex] = FALSE;
            filePtr = &gFileArray[fIndex];
			break;
        }
    }

    if( filePtr == NULL )
    {
        FSerrno = CE_TOO_MANY_FILES_OPEN;
        return NULL;      //no file structure slot available
    }
#endif

	#if defined(SUPPORT_LFN)
		#if defined(FS_DYNAMIC_MEM)
			filePtr -> utf16LFNptr = (unsigned short int *)FS_malloc(514);
		#else
			filePtr->utf16LFNptr = &lfnData[fIndex][0];
		#endif
    #endif

    //Format the source string.
    if( !FormatFileName(fileName, filePtr, 0) )
    {
		#ifdef FS_DYNAMIC_MEM
			#if defined(SUPPORT_LFN)
				FS_free((unsigned char *)filePtr->utf16LFNptr);
			#endif
        	FS_free( (unsigned char *)filePtr );
		#else
        	gFileSlotOpen[fIndex] = TRUE;   //put this slot back to the pool
		#endif
        
		FSerrno = CE_INVALID_FILENAME;
        return NULL;   //bad filename
    }

    filePtr->dsk = &gDiskData;
    filePtr->cluster = 0;
    filePtr->ccls    = 0;
    filePtr->entry = 0;
    filePtr->attributes = ATTR_ARCHIVE;

    // start at the current directory
#ifdef ALLOW_DIRS
    filePtr->dirclus    = cwdptr->dirclus;
    filePtr->dirccls    = cwdptr->dirccls;
#else
    filePtr->dirclus = FatRootDirClusterValue;
    filePtr->dirccls = FatRootDirClusterValue;
#endif

    // copy file object over
    FileObjectCopy(&gFileTemp, filePtr);

    // See if the file is found
    if(FILEfind (filePtr, &gFileTemp, LOOK_FOR_MATCHING_ENTRY, 0) == CE_GOOD)
    {
        // File is Found
        switch(ModeC)
        {

            case 'R':
            case 'r':
            {
                fHandle = filePtr->entry;

                final = FILEopen (filePtr, &fHandle, 'r');
                break;
            }

            default:
                FSerrno = CE_INVALID_ARGUMENT;
                final = 0xFF;;  //indicate error condition
                break;
        }
    }
    else
    {
		{
            final = CE_FILE_NOT_FOUND;
        	FSerrno = CE_FILE_NOT_FOUND;
    	}
    }

    if (MDD_WriteProtectState())
    {
        filePtr->flags.write = 0;;
    }

#ifdef FS_DYNAMIC_MEM
    if( final != CE_GOOD )
    {
        #ifdef	SUPPORT_LFN
			FS_free((unsigned char *)filePtr->utf16LFNptr);
		#endif
		FS_free( (unsigned char *)filePtr );
        filePtr = NULL;
    }
#else
    if( final != CE_GOOD )
    {
        gFileSlotOpen[fIndex] = TRUE;   //put this slot back to the pool
        filePtr = NULL;
    }
#endif
    else
    {
        FSerrno = CE_GOOD;
    }

    return filePtr;
}

/*******************************************************************
  Function:
    long FSftell (FSFILE * fo)
  Summary:
    Determine the current location in a file
  Conditions:
    File opened
  Input:
    fo -  Pointer to file structure
  Return: Current location in the file
  Side Effects:
    The FSerrno variable will be changed
  Description:
    The FSftell function will return the current position in the
    file pointed to by 'fo' by returning the 'seek' variable in the
    FSFILE object, which is used to keep track of the absolute
    location of the current position in the file.
  Remarks:
    None
  *******************************************************************/

long FSftell (FSFILE * fo)
{
    FSerrno = CE_GOOD;
    return (fo->seek);
}

/*********************************************************
  Function:
    void FSrewind (FSFILE * fo)
  Summary:
    Set the current position in a file to the beginning
  Conditions:
    File opened.
  Input:
    fo -  Pointer to file structure
  Return Values:
    None
  Side Effects:
    None.
  Description:
    The FSrewind funciton will reset the position of the
    specified file to the beginning of the file.  This
    functionality is faster than using FSfseek to reset
    the position in the file.
  Remarks:
    None.
  *********************************************************/

void FSrewind (FSFILE * fo)
{
    fo->seek = 0;
    fo->pos = 0;
    fo->sec = 0;
    fo->ccls = fo->cluster;
    gBufferOwner = NULL;
    return;
}

/**************************************************************************
  Function:
    int FSerror (void)
  Summary:
    Return an error code for the last function call
  Conditions:
    The return value depends on the last function called.
  Input:
    None
  Side Effects:
    None.
  Return Values:
    FSInit       -
                 - CE_GOOD �                  No Error
                 - CE_INIT_ERROR �            The physical media could not be initialized
                 - CE_BAD_SECTOR_READ �       The MBR or the boot sector could not be
                                              read correctly
                 - CE_BAD_PARITION �          The MBR signature code was incorrect.
                 - CE_NOT_FORMATTED �         The boot sector signature code was incorrect or
                                              indicates an invalid number of uint8_ts per sector.
                 - CE_UNSUPPORTED_SECTOR_SIZE - The number of uint8_ts per sector is unsupported
                 - CE_CARDFAT32 �             The physical media is FAT32 type (only an error
                                              when FAT32 support is disabled).
                 - CE_UNSUPPORTED_FS �        The device is formatted with an unsupported file
                                              system (not FAT12 or 16).
    FSfopen      -
                 - CE_GOOD �                  No Error
                 - CE_NOT_INIT �              The device has not been initialized.
                 - CE_TOO_MANY_FILES_OPEN �   The function could not allocate any
                                              additional file information to the array
                                              of FSFILE structures or the heap.
                 - CE_INVALID_FILENAME �      The file name argument was invalid.
                 - CE_INVALID_ARGUMENT �      The user attempted to open a directory in a
                                              write mode or specified an invalid mode argument.
                 - CE_FILE_NOT_FOUND �        The specified file (which was to be opened in read
                                              mode) does not exist on the device.
                 - CE_BADCACHEREAD �          A read from the device failed.
                 - CE_ERASE_FAIL �            The existing file could not be erased (when opening
                                              a file in FS_WRITE mode).
                 - CE_DIR_FULL �              The directory is full.
                 - CE_DISK_FULL�              The data memory section is full.
                 - CE_WRITE_ERROR �           A write to the device failed.
                 - CE_SEEK_ERROR �            The current position in the file could not be set to
                                              the end (when the file was opened in FS_APPEND mode).
    FSfclose     -
                 - CE_GOOD �                  No Error
                 - CE_WRITE_ERROR �           The existing data in the data buffer or the new file
                                              entry information could not be written to the device.
                 - CE_BADCACHEREAD �          The file entry information could not be cached
    FSfread      -
                 - CE_GOOD �                  No Error
                 - CE_WRITEONLY �             The file was opened in a write-only mode.
                 - CE_WRITE_ERROR �           The existing data in the data buffer could not be
                                              written to the device.
                 - CE_BAD_SECTOR_READ �       The data sector could not be read.
                 - CE_EOF �                   The end of the file was reached.
                 - CE_COULD_NOT_GET_CLUSTER � Additional clusters in the file could not be loaded.
    FSfwrite     -
                 - CE_GOOD �                  No Error
                 - CE_READONLY �              The file was opened in a read-only mode.
                 - CE_WRITE_PROTECTED �       The device write-protect check function indicated
                                              that the device has been write-protected.
                 - CE_WRITE_ERROR �           There was an error writing data to the device.
                 - CE_BADCACHEREAD �          The data sector to be modified could not be read from
                                              the device.
                 - CE_DISK_FULL �             All data clusters on the device are in use.
    FSfseek      -
                 - CE_GOOD �                  No Error
                 - CE_WRITE_ERROR �           The existing data in the data buffer could not be
                                              written to the device.
                 - CE_INVALID_ARGUMENT �      The specified offset exceeds the size of the file.
                 - CE_BADCACHEREAD �          The sector that contains the new current position
                                              could not be loaded.
                 - CE_COULD_NOT_GET_CLUSTER � Additional clusters in the file could not be
                                              loaded/allocated.
    FSftell      -
                 - CE_GOOD �                  No Error
    FSattrib     -
                 - CE_GOOD �                  No Error
                 - CE_INVALID_ARGUMENT �      The attribute argument was invalid.
                 - CE_BADCACHEREAD �          The existing file entry information could not be
                                              loaded.
                 - CE_WRITE_ERROR �           The file entry information could not be written to
                                              the device.
    FSrename     -
                 - CE_GOOD �                  No Error
                 - CE_FILENOTOPENED �         A null file pointer was passed into the function.
                 - CE_INVALID_FILENAME �      The file name passed into the function was invalid.
                 - CE_BADCACHEREAD �          A read from the device failed.
                 - CE_FILENAME_EXISTS �       A file with the specified name already exists.
                 - CE_WRITE_ERROR �           The new file entry data could not be written to the
                                              device.
    FSfeof       -
                 - CE_GOOD �                  No Error
    FSformat     -
                 - CE_GOOD �                  No Error
                 - CE_INIT_ERROR �            The device could not be initialized.
                 - CE_BADCACHEREAD �          The master boot record or boot sector could not be
                                              loaded successfully.
                 - CE_INVALID_ARGUMENT �      The user selected to create their own boot sector on
                                              a device that has no master boot record, or the mode
                                              argument was invalid.
                 - CE_WRITE_ERROR �           The updated MBR/Boot sector could not be written to
                                              the device.
                 - CE_BAD_PARTITION �         The calculated number of sectors per clusters was
                                              invalid.
                 - CE_NONSUPPORTED_SIZE �     The card has too many sectors to be formatted as
                                              FAT12 or FAT16.
    FSremove     -
                 - CE_GOOD �                  No Error
                 - CE_WRITE_PROTECTED �       The device write-protect check function indicated
                                              that the device has been write-protected.
                 - CE_INVALID_FILENAME �      The specified filename was invalid.
                 - CE_FILE_NOT_FOUND �        The specified file could not be found.
                 - CE_ERASE_FAIL �            The file could not be erased.
    FSchdir      -
                 - CE_GOOD �                  No Error
                 - CE_INVALID_ARGUMENT �      The path string was mis-formed or the user tried to
                                              change to a non-directory file.
                 - CE_BADCACHEREAD �          A directory entry could not be cached.
                 - CE_DIR_NOT_FOUND �         Could not find a directory in the path.
    FSgetcwd     -
                 - CE_GOOD �                  No Error
                 - CE_INVALID_ARGUMENT �      The user passed a 0-length buffer into the function.
                 - CE_BADCACHEREAD �          A directory entry could not be cached.
                 - CE_BAD_SECTOR_READ �       The function could not determine a previous directory
                                              of the current working directory.
    FSmkdir      -
                 - CE_GOOD �                  No Error
                 - CE_WRITE_PROTECTED �       The device write-protect check function indicated
                                              that the device has been write-protected.
                 - CE_INVALID_ARGUMENT �      The path string was mis-formed.
                 - CE_BADCACHEREAD �          Could not successfully change to a recently created
                                              directory to store its dir entry information, or
                                              could not cache directory entry information.
                 - CE_INVALID_FILENAME �      One or more of the directory names has an invalid
                                              format.
                 - CE_WRITE_ERROR �           The existing data in the data buffer could not be
                                              written to the device or the dot/dotdot entries could
                                              not be written to a newly created directory.
                 - CE_DIR_FULL �              There are no available dir entries in the CWD.
                 - CE_DISK_FULL �             There are no available clusters in the data region of
                                              the device.
    FSrmdir      -
                 - CE_GOOD �                  No Error
                 - CE_DIR_NOT_FOUND �         The directory specified could not be found or the
                                              function could not change to a subdirectory within
                                              the directory to be deleted (when recursive delete is
                                              enabled).
                 - CE_INVALID_ARGUMENT �      The user tried to remove the CWD or root directory.
                 - CE_BADCACHEREAD �          A directory entry could not be cached.
                 - CE_DIR_NOT_EMPTY �         The directory to be deleted was not empty and
                                              recursive subdirectory removal was disabled.
                 - CE_ERASE_FAIL �            The directory or one of the directories or files
                                              within it could not be deleted.
                 - CE_BAD_SECTOR_READ �       The function could not determine a previous directory
                                              of the CWD.
    SetClockVars -
                 - CE_GOOD �                  No Error
                 - CE_INVALID_ARGUMENT �      The time values passed into the function were
                                              invalid.
    FindFirst    -
                 - CE_GOOD �                  No Error
                 - CE_INVALID_FILENAME �      The specified filename was invalid.
                 - CE_FILE_NOT_FOUND �        No file matching the specified criteria was found.
                 - CE_BADCACHEREAD �          The file information for the file that was found
                                              could not be cached.
    FindNext     -
                 - CE_GOOD �                  No Error
                 - CE_NOT_INIT �              The SearchRec object was not initialized by a call to
                                              FindFirst.
                 - CE_INVALID_ARGUMENT �      The SearchRec object was initialized in a different
                                              directory from the CWD.
                 - CE_INVALID_FILENAME �      The filename is invalid.
                 - CE_FILE_NOT_FOUND �        No file matching the specified criteria was found.
    FSfprintf    -
                 - CE_GOOD �                  No Error
                 - CE_WRITE_ERROR �           Characters could not be written to the file.
  Description:
    The FSerror function will return the FSerrno variable.  This global
    variable will have been set to an error value during the last call of a
    library function.
  Remarks:
    None
  **************************************************************************/

int FSerror (void)
{
    return FSerrno;
}


/**************************************************************
  Function:
    void FileObjectCopy(FILEOBJ foDest,FILEOBJ foSource)
  Summary:
    Copy a file object
  Conditions:
    This function should not be called by the user.
  Input:
    foDest -    The destination
    foSource -  the source
  Return:
    None
  Side Effects:
    None
  Description:
    The FileObjectCopy function will make an exacy copy of
    a specified FSFILE object.
  Remarks:
    None
  **************************************************************/

void FileObjectCopy(FILEOBJ foDest,FILEOBJ foSource)
{
    int size;
    uint8_t *dest;
    uint8_t *source;
    int Index;

    dest = (uint8_t *)foDest;
    source = (uint8_t *)foSource;

    size = sizeof(FSFILE);

    for(Index=0;Index< size; Index++)
    {
        dest[Index] = source[Index];
    }
}

#if defined (__C30__) || defined (__PIC32MX__)

/***************************************************
  Function:
    uint8_t Readuint8_t(uint8_t * pBuffer, uint16_t index)
  Summary:
    Read a uint8_t from a buffer
  Conditions:
    This function should not be called by the user.
  Input:
    pBuffer -  pointer to a buffer to read from
    index -    index in the buffer to read to
  Return:
    uint8_t - the uint8_t read
  Side Effects:
    None
  Description:
    Reads a uint8_t from a buffer
  Remarks:
    None.
  ***************************************************/

uint8_t Readuint8_t( uint8_t* pBuffer, uint16_t index )
{
    return( pBuffer[index] );
}


/***************************************************
  Function:
    uint8_t Reauint32_t(uint8_t * pBuffer, uint16_t index)
  Summary:
    Read a 16-bit uint16_t from a buffer
  Conditions:
    This function should not be called by the user.
  Input:
    pBuffer -  pointer to a buffer to read from
    index -    index in the buffer to read to
  Return:
    uint16_t - the uint16_t read
  Side Effects:
    None
  Description:
    Reads a 16-bit uint16_t from a buffer
  Remarks:
    None.
  ***************************************************/

uint16_t Reauint32_t( uint8_t* pBuffer, uint16_t index )
{
    uint8_t louint8_t, hiuint8_t;
    uint16_t res;

    louint8_t = pBuffer[index];
    hiuint8_t = pBuffer[index+1];
    res = hiuint8_t;
    res *= 0x100;
    res |= louint8_t;
    return( res );
}


/****************************************************
  Function:
    uint8_t Readuint32_t(uint8_t * pBuffer, uint16_t index)
  Summary:
    Read a 32-bit double uint16_t from a buffer
  Conditions:
    This function should not be called by the user.
  Input:
    pBuffer -  pointer to a buffer to read from
    index -    index in the buffer to read to
  Return:
    uint32_t - the double uint16_t read
  Side Effects:
    None
  Description:
    Reads a 32-bit double uint16_t from a buffer
  Remarks:
    None.
  ****************************************************/

uint32_t Readuint32_t( uint8_t* pBuffer, uint16_t index )
{
    uint16_t louint16_t, hiuint16_t;
    uint32_t result;

    louint16_t = Reauint32_t( pBuffer, index );
    hiuint16_t = Reauint32_t( pBuffer, index+2 );

    result = hiuint16_t;
    result *= 0x10000;
    result |= louint16_t;
    return result;
}

#endif



/****************************************************
  Function:
    uint32_t Cluster2Sector(DISK * dsk, uint32_t cluster)
  Summary:
    Convert a cluster number to the corresponding sector
  Conditions:
    This function should not be called by the user.
  Input:
    disk -     Disk structure
    cluster -  Cluster to be converted
  Return:
    sector - Sector that corresponds to given cluster
  Side Effects:
    None
  Description:
    The Cluster2Sector function will calculate the
    sector number that corresponds to the first sector
    of the cluster whose value was passed into the
    function.
  Remarks:
    None.
  ****************************************************/

uint32_t Cluster2Sector(DISK * dsk, uint32_t cluster)
{
    uint32_t sector;

    /* Rt: Settings based on FAT type */
    switch (dsk->type)
    {
#ifdef SUPPORT_FAT32 // If FAT32 supported.
        case FAT32:
            /* In FAT32, there is no separate ROOT region. It is as well stored in DATA region */
            sector = (((uint32_t)cluster-2) * dsk->SecPerClus) + dsk->data;
            break;
#endif
        case FAT12:
        case FAT16:
        default:
            // The root dir takes up cluster 0 and 1
            if((cluster == 0) || (cluster == 1))
                sector = dsk->root + cluster;
            else
                sector = (((uint32_t)cluster-2) * dsk->SecPerClus) + dsk->data;
            break;
    }

    return(sector);

}

/****************************************************
  Function:
    int FSfeof( FSFILE * stream )
  Summary:
    Indicate whether the current file position is at the end
  Conditions:
    File is open in a read mode
  Input:
    stream -  Pointer to the target file
  Return Values:
    Non-Zero - EOF reached
    0 - Not at end of File
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    The FSfeof function will indicate that the end-of-
    file has been reached for the specified file by
    comparing the absolute location in the file to the
    size of the file.
  Remarks:
    None.
  ****************************************************/

int FSfeof( FSFILE * stream )
{
    FSerrno = CE_GOOD;
    return( stream->seek == stream->size );
}


/**************************************************************************
  Function:
    size_t FSfread(void *ptr, size_t size, size_t n, FSFILE *stream)
  Summary:
    Read data from a file
  Conditions:
    File is opened in a read mode
  Input:
    ptr -     Destination buffer for read uint8_ts
    size -    Size of units in uint8_ts
    n -       Number of units to be read
    stream -  File to be read from
  Return:
    size_t - number of units read
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    The FSfread function will read data from the specified file.  First,
    the appropriate sector of the file is loaded.  Then, data is read into
    the specified buffer until the specified number of uint8_ts have been read.
    When a cluster boundary is reached, a new cluster will be loaded.  The
    parameters 'size' and 'n' indicate how much data to read.  'Size'
    refers to the size of one object to read (in uint8_ts), and 'n' will refer
    to the number of these objects to read.  The value returned will be equal
    to 'n' unless an error occured or the user tried to read beyond the end
    of the file.
  Remarks:
    None.
  **************************************************************************/

size_t FSfread (void *ptr, size_t size, size_t n, FSFILE *stream)
{
    uint32_t   len = size * n;
    uint8_t    *pointer = (uint8_t *) ptr;
    DISK    *dsk;               // Disk structure
    uint32_t    seek, sec_sel;
    uint16_t    pos;       //position within sector
    CETYPE   error = CE_GOOD;
    uint16_t    readCount = 0;
    uint8_t value;

    FSerrno = CE_GOOD;

    dsk    = (DISK *)stream->dsk;
    pos    = stream->pos;
    seek    = stream->seek;

    if( !stream->flags.read )
    {
        FSerrno = CE_WRITEONLY;
        return 0;   // CE_WRITEONLY
    }

    // if it not my buffer, then get it from the disk.
    if( (gBufferOwner != stream) && (pos != dsk->sectorSize))
    {
        gBufferOwner = stream;
        sec_sel = Cluster2Sector(dsk,stream->ccls);
        sec_sel += (uint16_t)stream->sec;      // add the sector number to it

        gBufferZeroed = FALSE;

        while((value = MDD_SectorRead( sec_sel, dsk->buffer)) == 0xff);

        if(value == 0)
        {
            FSerrno = CE_BAD_SECTOR_READ;
            error = CE_BAD_SECTOR_READ;
            return 0;
        }
        gLastDataSectorRead = sec_sel;
    }

    //loop reading (count) uint8_ts
    while( len )
    {
        if( seek == stream->size )
        {
            FSerrno = CE_EOF;
            error = CE_EOF;
            break;
        }

        // In fopen, pos is init to 0 and the sect is loaded
        if( pos == dsk->sectorSize )
        {
            // reset position
            pos = 0;
            // point to the next sector
            stream->sec++;

            // get a new cluster if necessary
            if( stream->sec == dsk->SecPerClus )
            {
                stream->sec = 0;
                if( (error = FILEget_next_cluster( stream, 1)) != CE_GOOD )
                {
                    FSerrno = CE_COULD_NOT_GET_CLUSTER;
                    break;
                }
            }

            sec_sel = Cluster2Sector(dsk,stream->ccls);
            sec_sel += (uint16_t)stream->sec;      // add the sector number to it


            gBufferOwner = stream;
            gBufferZeroed = FALSE;

            while((value = MDD_SectorRead( sec_sel, dsk->buffer)) == 0xff);

            if(value == 0)
            {
                FSerrno = CE_BAD_SECTOR_READ;
                error = CE_BAD_SECTOR_READ;
                break;
            }
            gLastDataSectorRead = sec_sel;
        }

        // copy one uint8_t at a time
        *pointer = RAMread( dsk->buffer, pos++ );
        pointer++;
        seek++;
        readCount++;
        len--;
    }

    // save off the positon
    stream->pos = pos;
    // save off the seek
    stream->seek = seek;

    return(readCount / size);
} // fread


/***************************************************************************
  Function:
    uint8_t FormatFileName( const char* fileName, FILEOBJ fptr, uint8_t mode )
  Summary:
    Format a file name into dir entry format
  Conditions:
    This function should not be called by the user.
  Input:
    fileName -  The name to be formatted
    fN2 -       The location the formatted name will be stored
    mode -      Non-zero if parital string search chars are allowed
  Return Values:
    TRUE - Name formatted successfully
    FALSE - File name could not be formatted
  Side Effects:
    None
  Description:
    Format an 8.3 filename into FSFILE structure format. If filename is less
    than 8 chars, then it will be padded with spaces. If the extension name is
    fewer than 3 chars, then it will also be oadded with spaces. The
    ValidateChars function is used to ensure the characters in the specified
    filename are valid in this filesystem.
  Remarks:
    None.
  ***************************************************************************/
uint8_t FormatFileName( const char* fileName, FILEOBJ fptr, uint8_t mode)
{
	char *fN2;
	FILE_DIR_NAME_TYPE fileNameType;
    int temp,count1,count2,count3,count4;
    bool supportLFN = FALSE;
	char *localFileName = NULL;

	// go with static allocation
	#if defined(SUPPORT_LFN)
		unsigned short int tempString[256];
		bool	AscciIndication = TRUE;
		count1 = 256;
	#else
		unsigned short int	tempString[13];
		count1 = 12;
	#endif

	// Check whether the length of the file name is valid
	// for LFN support as well as Non LFN support
	#ifdef SUPPORT_LFN
	if(utfModeFileName)
	{
		utf16Filename = (unsigned short int *)fileName;
		fileNameLength = 0;
		while(utf16Filename[fileNameLength])
		{
			fileNameLength++;
		}

		if((fileNameLength > count1) || (*utf16Filename == '.') ||
			(*utf16Filename == 0))
		{
			return FALSE;
		}
		
		for (count1 = 0;count1 < fileNameLength; count1++)
		{
			tempString[count1] = utf16Filename[count1];
		}
		
		utf16Filename = tempString;
	}
	else
	#endif
	{
		fileNameLength = strlen(fileName);

		if((fileNameLength > count1) || (*fileName == '.') || (*fileName == 0))
		{
			return FALSE;
		}
		
		asciiFilename = (char *)tempString;
		for (count1 = 0;count1 < fileNameLength; count1++)
		{
			asciiFilename[count1] = fileName[count1];
		}
	}

    // Make sure the characters are valid
   	fileNameType = ValidateChars(mode);

    // If the file name doesn't follow 8P3 or LFN format, then return FALSE
    if(NAME_ERROR == fileNameType)
	{
		return FALSE;
	}

	temp = fileNameLength;

	#if defined(SUPPORT_LFN)
		fptr->AsciiEncodingType = TRUE;
		fptr->utf16LFNlength = 0;
	#endif

	// If LFN is supported and the file name is UTF16 type or Ascii mixed type,
	// go for LFN support rather than trying to adjust in 8P3 format
	if(NAME_8P3_ASCII_MIXED_TYPE == fileNameType)
	{
		#if defined(SUPPORT_LFN)
			supportLFN = TRUE;
		#endif
	}

	#if defined(SUPPORT_LFN)
	if(NAME_8P3_UTF16_TYPE == fileNameType)
	{
		for (count3 = 0; count3 < temp; count3++)
		{
			if(utf16Filename[count3] > 0xFF)
			{
				fileNameType = NAME_8P3_UTF16_NONASCII_TYPE;
				supportLFN = TRUE;
				break;
			}
		}

		if(count3 == temp)
		{
			fileNameType = NAME_8P3_UTF16_ASCII_CAPS_TYPE;

			for (count3 = 0; count3 < temp; count3++)
			{
				if((utf16Filename[count3] >= 0x61) && (utf16Filename[count3] <= 0x7A))
				{
					fileNameType = NAME_8P3_UTF16_ASCII_MIXED_TYPE;
					supportLFN = TRUE;
					break;
				}
			}
		}
	}
	#endif

	// If the file name follows 8P3 type
	if((NAME_LFN_TYPE != fileNameType) && (FALSE == supportLFN))
	{
		for (count3 = 0; count3 < temp; count3++)
		{
			#ifdef SUPPORT_LFN
			if(utfModeFileName)
			{
				if(((utf16Filename[count3] == '.') && ((temp - count3) > 4)) ||
					(count3 > 8))
				{
					// UTF File name extension greater then 3 characters or
				    // UTF File name greater then 8 charcters
					supportLFN = TRUE;
					break;
				}
				else if(utf16Filename[count3] == '.')
				{
					break;
				}
			}
			else
			#endif
			{
				if(((asciiFilename[count3] == '.') && ((temp - count3) > 4)) ||
					(count3 > 8))
				{
					// File extension greater then 3 characters or
					// File name greater then 8 charcters
					#if !defined(SUPPORT_LFN)
						return FALSE;
					#endif
					supportLFN = TRUE;
					break;
				}
				else if(asciiFilename[count3] == '.')
				{
					break;
				}
			}
		}
		
		// If LFN not supported try to adjust in 8P3 format
		if(FALSE == supportLFN)
		{
		    // point fN2 to short file name
		    fN2 = fptr -> name;
		    
		    // Load destination filename to be space intially.
		    for (count1 = 0; count1 < FILE_NAME_SIZE_8P3; count1++)
		    {
		        *(fN2 + count1) = ' ';
		    }

			// multiply the length by 2 as each UTF uint16_t has 2 uint8_t
			#ifdef SUPPORT_LFN
			if(utfModeFileName)
			{
				count4 = count3 * 2;
				temp = temp * 2;
				localFileName = (char *)utf16Filename;
			}
			else
			#endif
			{
				count4 = count3;
				localFileName = asciiFilename;
			}

		    //copy only file name ( not the extension part )
		    for (count1 = 0,count2 = 0; (count2 < 8) && (count1 < count4);count1++ )
		    {
				if(localFileName[count1])
				{
					fN2[count2] = localFileName[count1]; // Destination filename initially filled with SPACE. Now copy only available chars.

	    			// Convert lower-case to upper-case
	    			if ((fN2[count2] >= 0x61) && (fN2[count2] <= 0x7A))
	    			{
	    			    fN2[count2] -= 0x20;
					}
					count2++;
				}
		    }

			if(count4 < temp)
			{
				// Discard the '.' part
				count4++;

    		    // Copy the extn to 8th position onwards. Ex: "FILE    .Tx "
    		    for (count3 = 8; (count3 < 11) && (count4 < temp);count4++ )
    		    {
					if(localFileName[count4])
					{
    		        	fN2[count3] = localFileName[count4];

		   	 			// Convert lower-case to upper-case
		   	 			if ((fN2[count3] >= 0x61) && (fN2[count3] <= 0x7A))
		   	 			{
		   	 			    fN2[count3] -= 0x20;
						}
						count3++;
					}
    		    }
			}
		}
	}

	// If the file name follows LFN format
    if((NAME_LFN_TYPE == fileNameType) || (TRUE == supportLFN))
	{
		#if defined(SUPPORT_LFN)  	

			// point fN2 to long file name
			fN2 = (char *)(fptr -> utf16LFNptr);

			if(!utfModeFileName)
			{
				localFileName = asciiFilename;
			}

			// Copy the LFN name in the adress specified by FSFILE pointer
			count2 = 0;
			for(count1 = 0;count1 < temp;count1++)
			{
				if(utfModeFileName)
				{
					fptr -> utf16LFNptr[count1] = utf16Filename[count1];
					if(AscciIndication)
					{
						if(utf16Filename[count1] > 0xFF)
						{
							fptr->AsciiEncodingType = FALSE;
							AscciIndication = FALSE;
						}
					}
				}
				else
				{
					fN2[count2++] = localFileName[count1];
					fN2[count2++] = (uint8_t)0x00;
				}
			}
			fptr -> utf16LFNptr[count1] = 0x0000;

			fptr->utf16LFNlength = fileNameLength;
		#else
			return FALSE;
		#endif
	}

	// Free the temporary heap used for intermediate execution
	return TRUE;
}

#ifdef ALLOW_DIRS

/*************************************************************************
  Function:
    uint8_t FormatDirName (char * string,FILEOBJ fptr, uint8_t mode)
  Summary:
    Format a dir name into dir entry format
  Conditions:
    This function should not be called by the user.
  Input:
    string -  The name to be formatted
    mode -
         - TRUE -  Partial string search characters are allowed
         - FALSE - Partial string search characters are forbidden
  Return Values:
    TRUE - The name was formatted correctly
    FALSE - The name contained invalid characters
  Side Effects:
    None
  Description:
    Format an 8.3 filename into directory structure format. If the name is less
    than 8 chars, then it will be padded with spaces. If the extension name is
    fewer than 3 chars, then it will also be oadded with spaces. The
    ValidateChars function is used to ensure the characters in the specified
    directory name are valid in this filesystem.
  Remarks:
    None.
  *************************************************************************/

uint8_t FormatDirName (char * string,FILEOBJ fptr, uint8_t mode)
{
    char tempString [12];
	FILE_DIR_NAME_TYPE fileNameType;
    int temp,count1,count2;
    bool supportLFN = FALSE;
	char *localFileName;

	// go with static allocation
	#if defined(SUPPORT_LFN)
    	int count3,count4;
		bool	AscciIndication = TRUE;
		count1 = 256;
	#else
		count1 = 12;
	#endif

	// Calculate the String length
	#ifdef SUPPORT_LFN
	if(utfModeFileName)
	{
		utf16Filename = (unsigned short int *)string;
		fileNameLength = 0;
		while(utf16Filename[fileNameLength])
		{
			fileNameLength++;
		}
	}
	else
	#endif
	{
		asciiFilename = string;
		fileNameLength = strlen(string);
	}

	if(fileNameLength > count1)
	{
		return FALSE;
	}

    // Make sure the characters are valid
    fileNameType = ValidateChars(mode);

    // If the file name doesn't follow 8P3 or LFN format, then return FALSE
    if(NAME_ERROR == fileNameType)
	{
		return FALSE;
	}

	temp = fileNameLength;

	#if defined(SUPPORT_LFN)
		fptr->AsciiEncodingType = TRUE;
		fptr->utf16LFNlength = 0;
	#endif

	// If LFN is supported and the file name is UTF16 type or Ascii mixed type,
	// go for LFN support rather than trying to adjust in 8P3 format
	if(NAME_8P3_ASCII_MIXED_TYPE == fileNameType)
	{
		#if defined(SUPPORT_LFN)
			supportLFN = TRUE;
		#endif
	}

	#if defined(SUPPORT_LFN)
	if(NAME_8P3_UTF16_TYPE == fileNameType)
	{
		for (count3 = 0; count3 < temp; count3++)
		{
			if(utf16Filename[count3] > 0xFF)
			{
				fileNameType = NAME_8P3_UTF16_NONASCII_TYPE;
				supportLFN = TRUE;
				break;
			}
		}

		if(count3 == temp)
		{
			fileNameType = NAME_8P3_UTF16_ASCII_CAPS_TYPE;

			for (count3 = 0; count3 < temp; count3++)
			{
				if((utf16Filename[count3] >= 0x61) && (utf16Filename[count3] <= 0x7A))
				{
					fileNameType = NAME_8P3_UTF16_ASCII_MIXED_TYPE;
					supportLFN = TRUE;
					break;
				}
			}
		}
	}
	#endif

	// If the file name follows LFN format
    if((NAME_LFN_TYPE == fileNameType) || (TRUE == supportLFN))
	{
		#if !defined(SUPPORT_LFN)
        	return FALSE;
		#else
			fptr -> utf16LFNptr = (unsigned short int *)string;
		
			if(utfModeFileName)
			{
				if(utf16Filename != (unsigned short int *)string)
				{
					// Copy the validated/Fomated name in the UTF16 string
					for(count1 = 0; count1 < temp; count1++)
					{
						fptr -> utf16LFNptr[count1] = utf16Filename[count1];
						if(AscciIndication)
						{
							if(utf16Filename[count1] > 0xFF)
							{
								fptr->AsciiEncodingType = FALSE;
								AscciIndication = FALSE;
							}
						}
					}
					fptr -> utf16LFNptr[count1] = 0x0000;
				}
				else
				{
					for(count1 = 0; count1 < temp; count1++)
					{
						if(AscciIndication)
						{
							if(utf16Filename[count1] > 0xFF)
							{
								fptr->AsciiEncodingType = FALSE;
								AscciIndication = FALSE;
								break;
							}
						}
					}
				}
			}
			else
			{
				#ifdef FS_DYNAMIC_MEM
	    			unsigned short int *tempAsciiLFN = (unsigned short int *)FS_malloc((temp + 1) * 2);
				#else
					unsigned short int	tempAsciiLFN[temp + 1];
				#endif

				localFileName = (char *)tempAsciiLFN;

				// Copy the validated/Fomated name in the Ascii string
				count2 = 0;

				for(count1 = 0; count1 < temp; count1++)
				{
					localFileName[count2++] = asciiFilename[count1];

					localFileName[count2++] = (uint8_t)0x00;

				}

				// Copy the validated/Fomated name in the UTF16 string
				for(count1 = 0; count1 < temp; count1++)
				{
					fptr -> utf16LFNptr[count1] = tempAsciiLFN[count1];
				}

				#ifdef FS_DYNAMIC_MEM
	    			FS_free((unsigned char *)tempAsciiLFN);
				#endif
				fptr -> utf16LFNptr[count1] = 0x0000;
			}

			fptr->utf16LFNlength = fileNameLength;
		#endif
	}
	else
	{
		#ifdef SUPPORT_LFN
		if(utfModeFileName)
		{
			localFileName = (char *)utf16Filename;

			// Copy the name part in the temporary string
		    count4 = 0;
		    for (count3 = 0; (count3 < temp) && (utf16Filename[count3] != '.') && (utf16Filename[count3] != 0); count3++)
		    {
				count1 = count3 * 2;
				if(localFileName[count1])
				{
			        tempString[count4] = localFileName[count1];
					count4++;
					if(count4 == 8)
						break;
				}
		 
				if(localFileName[count1 + 1])
				{
			        tempString[count4] = localFileName[count1 + 1];
					count4++;
					if(count4 == 8)
						break;
				}
		    }

			// File the remaining name portion with spaces
		    while (count4 < 8)
		    {
		        tempString [count4++] = 0x20;
		    }

			// Copy the extension part in the temporary string
		    if (utf16Filename[count3] == '.')
		    {
				count1 = count3 * 2 + 2;
		        while (localFileName[count1] != 0)
		        {
					if(localFileName[count3])
					{
				        tempString[count4] = localFileName[count3];
						count4++;
						if(count4 == 11)
							break;
					}
		        }
		    }

			count1 = count4;
		}
		else
		#endif
		{
			// Copy the name part in the temporary string
		    for (count1 = 0; (count1 < 8) && (*(asciiFilename + count1) != '.') && (*(asciiFilename + count1) != 0); count1++)
		    {
		        tempString[count1] = *(asciiFilename + count1);
		    }

			count2 = count1;

			// File the remaining name portion with spaces
		    while (count1 < 8)
		    {
		        tempString [count1++] = 0x20;
		    }

			// Copy the extension part in the temporary string
		    if (*(asciiFilename + count2) == '.')
		    {
		        count2++;
		        while ((*(asciiFilename + count2) != 0) && (count1 < FILE_NAME_SIZE_8P3))
		        {
		            tempString[count1++] = *(asciiFilename + count2++);
		        }
		    }
		}

		// File the remaining portion with spaces
		while (count1 < FILE_NAME_SIZE_8P3)
		{
		    tempString[count1++] = 0x20;
		}

		// Forbidden
		if (tempString[0] == 0x20)
		{
		    tempString[0] = '_';
		}

		// point fN2 to short file name
		localFileName = fptr -> name;

		// Copy the formated name in string
		for (count1 = 0; count1 < FILE_NAME_SIZE_8P3; count1++)
		{
		    localFileName[count1] = tempString[count1];

			// Convert lower-case to upper-case
			if ((tempString[count1] >= 0x61) && (tempString[count1] <= 0x7A))
			{
			    localFileName[count1] -= 0x20;
			}
		}
	}

	return TRUE;
}
#endif


/*************************************************************
  Function:
    FILE_DIR_NAME_TYPE ValidateChars(uint8_t mode)
  Summary:
    Validate the characters in a given file name
  Conditions:
    This function should not be called by the user.
  Input:
    fileName -  The name to be validated
    mode -      Determines if partial string search is allowed
  Return Values:
    TRUE - Name was validated
    FALSE - File name was not valid
  Side Effects:
    None
  Description:
    The ValidateChars function will compare characters in a
    specified filename to determine if they're permissable
    in the FAT file system.  Lower-case characters will be
    converted to upper-case.  If the mode argument is specifed
    to be 'TRUE,' partial string search characters are allowed.
  Remarks:
    None.
  *************************************************************/
FILE_DIR_NAME_TYPE ValidateChars(uint8_t mode)
{
	FILE_DIR_NAME_TYPE fileNameType;
    unsigned short int count1;
	#if defined(SUPPORT_LFN)
	unsigned short int utf16Value;
    unsigned short int count2;
	int		count3;
	#endif
    unsigned char radix = FALSE,asciiValue;

	#if defined(SUPPORT_LFN)

		// Remove the spaces if they are present before the file name
		for (count1 = 0; count1 < fileNameLength; count1++)
		{
	        if(utfModeFileName)
			{
				if((utf16Filename[count1] != ' ') && (utf16Filename[count1] != '.'))
				{
					utf16Filename = utf16Filename + count1;
					break;
				}
			}
			else if((asciiFilename[count1] != ' ') && (asciiFilename[count1] != '.'))
			{
				asciiFilename = asciiFilename + count1;
				break;
	    	}
	    }

	    count2 = 0;

		// Remove the spaces  & dots if they are present after the file name
	    for (count3 = fileNameLength - count1 - 1; count3 > 0; count3--)
	    {
	        if(utfModeFileName)
			{
				if((utf16Filename[count3] != ' ') && (utf16Filename[count3] != '.'))
				{
					break;
				}
			}
			else if((asciiFilename[count3] != ' ') && (asciiFilename[count3] != '.'))
			{
				break;
	    	}

	    	count2++;
	    }

		fileNameLength = fileNameLength - count1 - count2;

    	if(( fileNameLength > MAX_FILE_NAME_LENGTH_LFN ) || (fileNameLength == 0))// 255
        	return NAME_ERROR; //long file name

    #endif

 	// If the string length is greater then 8P3 length, then assume
	// the file name as LFN type provided there are no errors in the
	// below for loop.
	#ifdef SUPPORT_LFN
	if(utfModeFileName)
	{
		if((fileNameLength * 2) > (TOTAL_FILE_SIZE_8P3 * 2))
		{
			fileNameType = NAME_LFN_TYPE;
		}
		else
		{
			fileNameType = NAME_8P3_UTF16_TYPE;
		}
	}
	else
	#endif
	{
		if(fileNameLength > TOTAL_FILE_SIZE_8P3)
		{
			fileNameType = NAME_LFN_TYPE;
		}
		else
		{
			fileNameType = NAME_8P3_ASCII_CAPS_TYPE;
		}
	}

	for( count1 = 0; count1 < fileNameLength; count1++ )
	{
		#ifdef SUPPORT_LFN
		if(utfModeFileName)
		{
			utf16Value = utf16Filename[count1];
		    // Characters not valid for either of 8P3 & LFN format
		    if (((utf16Value < 0x20) && (utf16Value != 0x05)) || (utf16Value == 0x22) || 
				(utf16Value == 0x2F) || (utf16Value == 0x3A) || (utf16Value == 0x3C) || 
		        (utf16Value == 0x3E) || (utf16Value == 0x5C) || (utf16Value == 0x7C))
		    {
		        return NAME_ERROR;
		    }

	        // Check for partial string search chars
	        if (mode == FALSE)
	        {
	            if ((utf16Value == '*') || (utf16Value == '?'))
	            {
	    		    return NAME_ERROR;
	        	}
	        }

			if(fileNameType != NAME_LFN_TYPE)
			{
				// Characters valid for LFN format only
			    if ((utf16Value == 0x20) || (utf16Value == 0x2B) || (utf16Value == 0x2C) || 
					(utf16Value == 0x3B) || (utf16Value == 0x3D) || (utf16Value == 0x5B) || 
					(utf16Value == 0x5D) || ((utf16Value == 0x2E) && (radix == TRUE)))
			    {
					fileNameType = NAME_LFN_TYPE;
					continue;
			    }

	    	    // only one radix ('.') character is allowed in 8P3 format, where as 
				// multiple radices can be present in LFN format
	    	    if (utf16Filename[count1] == 0x2E)
	    	    {
	    	        radix = TRUE;
	    	    }
			}
		}
		else 
		#endif
		{
			asciiValue = asciiFilename[count1];
			if(((asciiValue < 0x20) && (asciiValue != 0x05)) || (asciiValue == 0x22) ||
				(asciiValue == 0x2F) || (asciiValue == 0x3A) || (asciiValue == 0x3C) ||
				(asciiValue == 0x3E) || (asciiValue == 0x5C) || (asciiValue == 0x7C))
			{
				return NAME_ERROR;
			}

	        // Check for partial string search chars
	        if (mode == FALSE)
	        {
	            if ((asciiValue == '*') || (asciiValue == '?'))
	            {
	    		    return NAME_ERROR;
	        	}
	        }

			if(fileNameType != NAME_LFN_TYPE)
			{
				// Characters valid for LFN format only
			    if ((asciiValue == 0x20) || (asciiValue == 0x2B) || (asciiValue == 0x2C) ||
			    	(asciiValue == 0x3B) || (asciiValue == 0x3D) || (asciiValue == 0x5B) ||
			        (asciiValue == 0x5D) || ((asciiValue == 0x2E) && (radix == TRUE)))
			    {
					fileNameType = NAME_LFN_TYPE;
					continue;
			    }

	    	    // only one radix ('.') character is allowed in 8P3 format, where as 
				// multiple radices can be present in LFN format
	    	    if (asciiValue == 0x2E)
	    	    {
	    	        radix = TRUE;
	    	    }

				// If the characters are mixed type & are within 8P3 length range
				// then store file type as 8P3 mixed type format
				if(fileNameType != NAME_8P3_ASCII_MIXED_TYPE)
				{
					if((asciiValue >= 0x61) && (asciiValue <= 0x7A))
					{
						fileNameType = NAME_8P3_ASCII_MIXED_TYPE;
					}
				}
			}
		}
	}

	return fileNameType;
}


/**********************************************************************
  Function:
    int FSfseek(FSFILE *stream, long offset, int whence)
  Summary:
    Change the current position in a file
  Conditions:
    File opened
  Input:
    stream -    Pointer to file structure
    offset -    Offset from base location
    whence -
           - SEEK_SET -  Seek from start of file
           - SEEK_CUR -  Seek from current location
           - SEEK_END -  Seek from end of file (subtract offset)
  Return Values:
    0 -  Operation successful
    -1 - Operation unsuccesful
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    The FSfseek function will change the current position in the file to
    one specified by the user.  First, an absolute offset is calculated
    using the offset and base location passed in by the user.  Then, the
    position variables are updated, and the sector number that corresponds
    to the new location.  That sector is then loaded.  If the offset
    falls exactly on a cluster boundary, a new cluster will be allocated
    to the file and the position will be set to the first uint8_t of that
    cluster.
  Remarks:
    None
  **********************************************************************/

int FSfseek(FSFILE *stream, long offset, int whence)
{
    uint32_t    numsector, temp;   // lba of first sector of first cluster
    DISK*   dsk;            // pointer to disk structure
    uint8_t   test;
    long offset2 = offset;
    uint8_t value;

    dsk = stream->dsk;

    switch(whence)
    {
        case SEEK_CUR:
            // Apply the offset to the current position
            offset2 += stream->seek;
            break;
        case SEEK_END:
            // Apply the offset to the end of the file
            offset2 = stream->size - offset2;
            break;
        case SEEK_SET:
            // automatically there
        default:
            break;
   }

    // start from the beginning
    temp = stream->cluster;
    stream->ccls = temp;

    temp = stream->size;

    if (offset2 > temp)
    {
        FSerrno = CE_INVALID_ARGUMENT;
        return (-1);      // past the limits
    }
    else
    {
        // if we are writing we are no longer at the end
        stream->flags.FileWriteEOF = FALSE;

        // set the new postion
        stream->seek = offset2;

        // figure out how many sectors
        numsector = offset2 / dsk->sectorSize;

        // figure out how many uint8_ts off of the offset
        offset2 = offset2 - (numsector * dsk->sectorSize);
        stream->pos = offset2;

        // figure out how many clusters
        temp = numsector / dsk->SecPerClus;

        // figure out the stranded sectors
        numsector = numsector - (dsk->SecPerClus * temp);
        stream->sec = numsector;

        // if we are in the current cluster stay there
        if (temp > 0)
        {
            test = FILEget_next_cluster(stream, temp);
            if (test != CE_GOOD)
            {
                if (test == CE_FAT_EOF)
                {
                        stream->ccls = stream->cluster;
                        test = FILEget_next_cluster(stream, temp - 1);
                        if (test != CE_GOOD)
                        {
                            FSerrno = CE_COULD_NOT_GET_CLUSTER;
                            return (-1);
                        }
                        stream->pos = dsk->sectorSize;
                        stream->sec = dsk->SecPerClus - 1;
                }
                else
                {
                    FSerrno = CE_COULD_NOT_GET_CLUSTER;
                    return (-1);   // past the limits
                }
            }
        }

        // Determine the lba of the selected sector and load
        temp = Cluster2Sector(dsk,stream->ccls);

        // now the extra sectors
        numsector = stream->sec;
        temp += numsector;

        gBufferOwner = NULL;
        gBufferZeroed = FALSE;
        while((value = MDD_SectorRead(temp, dsk->buffer)) == 0xff);
        if(value == 0)
        {
            FSerrno = CE_BADCACHEREAD;
            return (-1);   // Bad read
        }
        gLastDataSectorRead = temp;
    }

    FSerrno = CE_GOOD;

    return (0);
}


// FSfopenpgm, FSremovepgm, and FSrenamepgm will only work on PIC18s
#ifdef __18CXX
#ifdef ALLOW_PGMFUNCTIONS

#ifdef ALLOW_WRITES

/*****************************************************************
  Function:
    int FSrenamepgm(const rom char * fileName, FSFILE * fo)
  Summary:
    Renames the file with the ascii ROM string(PIC18)
  Conditions:
    File opened.
  Input:
    fileName -  The new name of the file (in ROM)
    fo -        The file to rename
  Return Values:
    0 -  File renamed successfully
    -1 - File could not be renamed
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    Renames the file with the ascii ROM string(PIC18).The Fsrenamepgm
    function will copy the rom fileName specified by the user into a 
    RAM array and pass that array into the FSrename function.
  Remarks:
    This function is for use with PIC18 when passing arguments in ROM.                       
  *****************************************************************/

int FSrenamepgm (const rom char * fileName, FSFILE * fo)
{
	#if defined(SUPPORT_LFN)

		char tempArray[257];
		unsigned short int count;
	#else

		char	tempArray[13];

	    uint8_t count;
	#endif


    *fileName;
    for(count = 0; count < sizeof(tempArray); count++)
    {
        _asm TBLRDPOSTINC _endasm
        tempArray[count] = TABLAT;
    }//end for(...)

    return FSrename (tempArray, fo);
}
#endif

/******************************************************************************
  Function:
    FSFILE * FSfopenpgm(const rom char * fileName, const rom char *mode)
  Summary:
    Opens a file on PIC18 Microcontrollers where 'fileName' ROM string is given
    in Ascii format.
  Conditions:
    For read modes, file exists; FSInit performed
  Input:
    fileName -  The name of the file to be opened (ROM)
    mode -      The mode the file will be opened in (ROM)
  Return Values:
    FSFILE * - A pointer to the file object
    NULL -     File could not be opened
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    This function opens a file on PIC18 Microcontrollers where 'fileName' ROM string
    is given in Ascii format.The FSfopenpgm function will copy a PIC18 ROM fileName and
    mode argument into RAM arrays, and then pass those arrays to the FSfopen function.
  Remarks:
    This function is for use with PIC18 when passing arguments in ROM.
  ******************************************************************************/

FSFILE * FSfopenpgm(const rom char * fileName, const rom char *mode)
{
	#if defined(SUPPORT_LFN)
    	char tempArray[257];
    	unsigned short int count = 0;
    #else
    	char tempArray[13];
    	uint8_t count = 0;
	#endif
    char M[2];

    for(;;)
	{
		tempArray[count] = fileName[count];
		if(tempArray[count])
			count++;
		else
			break;
	}

    for (count = 0; count < 2; count++)
    {
        M[count] = *(mode + count);
    }

    return FSfopen(tempArray, M);
}

/*************************************************************
  Function:
    int FSremovepgm (const rom char * fileName)
  Summary:
    Deletes the file on PIC18 device
  Conditions:
    File not opened; file exists
  Input:
    fileName -  The name of the file to be deleted (ROM)
  Return Values:
    0 -  File was removed successfully
    -1 - File could not be removed
  Side Effects:
    The FSerrno variable will be changed.
  Description:
    Deletes the file on PIC18 device.The FSremovepgm function will copy a
    PIC18 ROM fileName argument into a RAM array, and then pass that array
    to the FSremove function.
  Remarks:
    This function is for use with PIC18 when passing arguments in ROM.
  *************************************************************/
#ifdef ALLOW_WRITES
int FSremovepgm (const rom char * fileName)
{
	#ifdef SUPPORT_LFN
		char tempArray[257];
		unsigned short int count;
	#else

		char	tempArray[13];

	    uint8_t count;
	#endif


    *fileName;
    for(count = 0; count < sizeof(tempArray); count++)
    {
        _asm TBLRDPOSTINC _endasm
        tempArray[count] = TABLAT;
    }//end for(...)

    return FSremove (tempArray);
}
#endif

/**************************************************************************************
  Function:
    int FindFirstpgm (const char * fileName, unsigned int attr, SearchRec * rec)
  Summary:
    Find a file named with a ROM string on PIC18
  Conditions:
    None
  Input:
    fileName -  The name of the file to be found (ROM)
    attr -      The attributes of the file to be found
    rec -       Pointer to a search record to store the file info in
  Return Values:
    0 -  File was found
    -1 - No file matching the given parameters was found
  Side Effects:
    Search criteria from previous FindFirstpgm call on passed SearchRec object
    will be lost.The FSerrno variable will be changed.
  Description:
    This function finds a file named with 'fileName' on PIC18. The FindFirstpgm
    function will copy a PIC18 ROM fileName argument into a RAM array, and then
    pass that array to the FindFirst function.
  Remarks:
    Call FindFirstpgm or FindFirst before calling FindNext.
    This function is for use with PIC18 when passing arguments in ROM.
  **************************************************************************************/
#ifdef ALLOW_FILESEARCH
int FindFirstpgm (const rom char * fileName, unsigned int attr, SearchRec * rec)
{
	#if defined(SUPPORT_LFN)

		char tempArray[257];
		unsigned short int count;
	#else

		char	tempArray[13];

	    uint8_t count;
	#endif


    *fileName;
    for(count = 0; count < sizeof(tempArray); count++)
    {
        _asm TBLRDPOSTINC _endasm
        tempArray[count] = TABLAT;
    }//end for

    return FindFirst (tempArray,attr,rec);
}
#endif
#endif
#endif


/***********************************************
  Function:
    uint32_t ReadFAT (DISK *dsk, uint32_t ccls)
  Summary:
    Read the next entry from the FAT
  Conditions:
    This function should not be called by the user.
  Input:
    dsk -   The disk structure
    ccls -  The current cluster
  Return:
    uint32_t - The next cluster in a file chain
  Side Effects:
    None
  Description:
    The ReadFAT function will read the FAT and
    determine the next cluster value after the
    cluster specified by 'ccls.' Note that the
    FAT sector that is read is stored in the
    global FAT cache buffer.
  Remarks:
    None.
  ***********************************************/

uint32_t ReadFAT (DISK *dsk, uint32_t ccls)
{
    uint8_t q;
    uint32_t p, l;  // "l" is the sector Address
    uint32_t c = 0, d, ClusterFailValue,LastClusterLimit;   // ClusterEntries
    uint8_t value;
    gBufferZeroed = FALSE;

    /* Settings based on FAT type */
    switch (dsk->type)
    {
#ifdef SUPPORT_FAT32 // If FAT32 supported.
        case FAT32:
            p = (uint32_t)ccls * 4;
            q = 0; // "q" not used for FAT32, only initialized to remove a warning
            ClusterFailValue = CLUSTER_FAIL_FAT32;
            LastClusterLimit = LAST_CLUSTER_FAT32;
            break;
#endif
        case FAT12:
            p = (uint32_t) ccls *3;  // Mulby1.5 to find cluster pos in FAT
            q = p&1;
            p >>= 1;
            ClusterFailValue = CLUSTER_FAIL_FAT16;
            LastClusterLimit = LAST_CLUSTER_FAT12;
            break;
        case FAT16:
        default:
            p = (uint32_t)ccls *2;     // Mulby 2 to find cluster pos in FAT
            q = 0; // "q" not used for FAT16, only initialized to remove a warning
            ClusterFailValue = CLUSTER_FAIL_FAT16;
            LastClusterLimit = LAST_CLUSTER_FAT16;
            break;
    }

    l = dsk->fat + (p / dsk->sectorSize);     //
    p &= dsk->sectorSize - 1;                 // Restrict 'p' within the FATbuffer size

    // Check if the appropriate FAT sector is already loaded
    if (gLastFATSectorRead == l)
    {
#ifdef SUPPORT_FAT32 // If FAT32 supported.
        if (dsk->type == FAT32)
            c = RAMreadD (gFATBuffer, p);
        else
#endif
            if(dsk->type == FAT16)
                c = RAMreadW (gFATBuffer, p);
            else if(dsk->type == FAT12)
            {
                c = RAMread (gFATBuffer, p);
                if (q)
                {
                    c >>= 4;
                }
                // Check if the MSB is across the sector boundry
                p = (p +1) & (dsk->sectorSize-1);
                if (p == 0)
                {
                    // Start by writing the sector we just worked on to the card
                    // if we need to

                    while((value = MDD_SectorRead (l+1, gFATBuffer)) == 0xff);

                    if(value == 0)
                    {
                        gLastFATSectorRead = 0xFFFF;
                        return ClusterFailValue;
                    }
                    else
                    {
                        gLastFATSectorRead = l +1;
                    }
                }
                d = RAMread (gFATBuffer, p);
                if (q)
                {
                    c += (d <<4);
                }
                else
                {
                    c += ((d & 0x0F)<<8);
                }
            }
        }
        else
        {
            // If there's a currently open FAT sector,
            // write it back before reading into the buffer
            while((value = MDD_SectorRead (l, gFATBuffer)) == 0xff);
            
            if(value == 0)
            {
                gLastFATSectorRead = 0xFFFF;  // Note: It is Sector not Cluster.
                return ClusterFailValue;
            }
            else
            {
                gLastFATSectorRead = l;

#ifdef SUPPORT_FAT32 // If FAT32 supported.
                if (dsk->type == FAT32)
                    c = RAMreadD (gFATBuffer, p);
                else
#endif
                    if(dsk->type == FAT16)
                        c = RAMreadW (gFATBuffer, p);
                    else if (dsk->type == FAT12)
                    {
                        c = RAMread (gFATBuffer, p);
                        if (q)
                        {
                            c >>= 4;
                        }
                        p = (p +1) & (dsk->sectorSize-1);
                        d = RAMread (gFATBuffer, p);
                        if (q)
                        {
                            c += (d <<4);
                        }
                        else
                        {
                            c += ((d & 0x0F)<<8);
                        }
                    }
            }
    }

    // Normalize it so 0xFFFF is an error
    if (c >= LastClusterLimit)
        c = LastClusterLimit;

   return c;
}   // ReadFAT

#ifdef ALLOW_DIRS

// This string is used by dir functions to hold dir names temporarily
#if defined(SUPPORT_LFN)
	char tempDirectoryString [522];
#else
	char tempDirectoryString [14];
#endif
/**************************************************************************
  Function:
    int FSchdir (char * path)
  Summary:
    Changes the current working directory to the ascii input path(PIC24/PIC32/dsPIC)
  Conditions:
    None
  Input:
    path - The path of the directory to change to.
  Return Values:
    0 -   The current working directory was changed successfully
    EOF - The current working directory could not be changed
  Side Effects:
    The current working directory may be changed. The FSerrno variable will
    be changed.
  Description:
    Changes the current working directory to the ascii input path(PIC24/PIC32/dsPIC).
    The FSchdir function passes a RAM pointer to the path to the chdirhelper function.
  Remarks:
    None                                            
  **************************************************************************/

int FSchdir (char * path)
{
    return chdirhelper (0, path, NULL);
}

/**************************************************************************
  Function:
    int wFSchdir (unsigned short int * path)
  Summary:
    Change the current working directory as per the path specified in
    UTF16 format (PIC24/PIC32/dsPIC)
  Conditions:
    None
  Input:
    path - The path of the directory to change to.
  Return Values:
    0 -   The current working directory was changed successfully
    EOF - The current working directory could not be changed
  Side Effects:
    The current working directory may be changed. The FSerrno variable will
    be changed.
  Description:
    Change the current working directory as per the path specified in
    UTF16 format (PIC24/PIC32/dsPIC).The FSchdir function passes a RAM
    pointer to the path to the chdirhelper function.
  Remarks:
    None                                            
  **************************************************************************/
#ifdef SUPPORT_LFN
int wFSchdir (unsigned short int * path)
{
	int result;
	utfModeFileName = TRUE;
    result = chdirhelper (0, (char *)path, NULL);
	utfModeFileName = FALSE;
    return result;
}
#endif

/**************************************************************************
  Function:
    int FSchdirpgm (const rom char * path)
  Summary:
    Changes the CWD to the input path on PIC18
  Conditions:
    None
  Input:
    path - The path of the directory to change to (ROM)
  Return Values:
    0 -   The current working directory was changed successfully
    EOF - The current working directory could not be changed
  Side Effects:
    The current working directory may be changed. The FSerrno variable will
    be changed.
  Description:
    Changes the CWD to the input path on PIC18.The FSchdirpgm function
    passes a PIC18 ROM path pointer to the chdirhelper function.
  Remarks:
    This function is for use with PIC18 when passing arguments in ROM
  **************************************************************************/

#ifdef ALLOW_PGMFUNCTIONS
int FSchdirpgm (const rom char * path)
{
    return chdirhelper (1, NULL, path);
}

/**************************************************************************
  Function:
    int wFSchdirpgm (const rom unsigned short int * path)
  Summary:
    Changed the CWD with a path in ROM on PIC18
  Conditions:
    None
  Input:
    path - The path of the directory to change to (ROM)
  Return Values:
    0 -   The current working directory was changed successfully
    EOF - The current working directory could not be changed
  Side Effects:
    The current working directory may be changed. The FSerrno variable will
    be changed.
  Description:
    The FSchdirpgm function passes a PIC18 ROM path pointer to the
    chdirhelper function.
  Remarks:
    This function is for use with PIC18 when passing arguments in ROM
  **************************************************************************/
#ifdef SUPPORT_LFN
int wFSchdirpgm (const rom unsigned short int * path)
{
	int result;
	utfModeFileName = TRUE;
    result = chdirhelper (1, NULL, (const char *)path);
	utfModeFileName = FALSE;
	return result;
}
#endif

#endif

/*************************************************************************
  Function:
    // PIC24/30/33/32
    int chdirhelper (uint8_t mode, char * ramptr, char * romptr);
    // PIC18
    int chdirhelper (uint8_t mode, char * ramptr, const rom char * romptr);
  Summary:
    Helper function for FSchdir
  Conditions:
    None
  Input:
    mode -    Indicates which path pointer to use
    ramptr -  Pointer to the path specified in RAM
    romptr -  Pointer to the path specified in ROM
  Return Values:
    0 -   Directory was changed successfully.
    EOF - Directory could not be changed.
  Side Effects:
    The current working directory will be changed. The FSerrno variable
    will be changed. Any unwritten data in the data buffer will be written
    to the device.
  Description:
    This helper function is used by the FSchdir function. If the path
    argument is specified in ROM for PIC18 this function will be able to
    parse it correctly.  The function will loop through a switch statement
    to process the tokens in the path string.  Dot or dotdot entries are
    handled in the first case statement.  A backslash character is handled
    in the second case statement (note that this case statement will only
    be used if backslash is the first character in the path; backslash
    token delimiters will automatically be skipped after each token in the
    path is processed).  The third case statement will handle actual
    directory name strings.
  Remarks:
    None.
  *************************************************************************/

#ifdef ALLOW_PGMFUNCTIONS
int chdirhelper (uint8_t mode, char * ramptr, const rom char * romptr)
#else
int chdirhelper (uint8_t mode, char * ramptr, char * romptr)
#endif
{
    unsigned short int i,j,k = 0;
    uint16_t curent = 1;
    DIRENTRY entry;
    char * temppath = ramptr;
#ifdef ALLOW_PGMFUNCTIONS
    rom char * temppath2 = romptr;
    rom unsigned short int * utf16path2 = (rom unsigned short int *)romptr;
#endif
	#ifdef SUPPORT_LFN
		unsigned short int *utf16path = (unsigned short int *)ramptr;
	#endif

    FSFILE tempCWDobj2;
    FILEOBJ tempCWD = &tempCWDobj2;

    FileObjectCopy (tempCWD, cwdptr);

    FSerrno = CE_GOOD;

   // Check the first char of the path
#ifdef ALLOW_PGMFUNCTIONS
    if (mode)
	{
		#ifdef SUPPORT_LFN
		if(utfModeFileName)

		{

			i = *utf16path2;
		}
		else
		#endif
		{
			i = *temppath2;
		}
    }
    else
#endif
	{
		#ifdef SUPPORT_LFN
		if(utfModeFileName)

		{

			i = *utf16path;
		}
		else
		#endif
		{
			i = *temppath;
		}
    }

	// if NULL character return error
    if (i == 0)
    {
        FSerrno = CE_INVALID_ARGUMENT;
        return -1;
    }

    while(1)
    {
        switch (i)
        {
            // First case: dot or dotdot entry
            case '.':
                // Move past the dot
#ifdef ALLOW_PGMFUNCTIONS
                if (mode)
                {
					#ifdef SUPPORT_LFN
					if(utfModeFileName)

					{

                	    utf16path2++;
                	    i = *utf16path2;
					}
					else
					#endif
					{
                	    temppath2++;
                	    i = *temppath2;
					}
                }
                else
                {
#endif
					#ifdef SUPPORT_LFN
					if(utfModeFileName)

					{

                	    utf16path++;
                	    i = *utf16path;
					}
					else
					#endif
					{
                	    temppath++;
                	    i = *temppath;
					}
#ifdef ALLOW_PGMFUNCTIONS
                }
#endif
                // Check if it's a dotdot entry
                if (i == '.')
                {
                    // Increment the path variable
#ifdef ALLOW_PGMFUNCTIONS
                    if (mode)
                    {
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                		    utf16path2++;
                		    i = *utf16path2;
						}
						else
						#endif
						{
                		    temppath2++;
                		    i = *temppath2;
						}
                    }
                    else
                    {
#endif
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                		    utf16path++;
                		    i = *utf16path;
						}
						else
						#endif
						{
                		    temppath++;
                		    i = *temppath;
						}
#ifdef ALLOW_PGMFUNCTIONS
                    }
#endif
                    // Check if we're in the root
                    if (tempCWD->dirclus == FatRootDirClusterValue)
                    {
                        // Fails if there's a dotdot chdir from the root
                        FSerrno = CE_INVALID_ARGUMENT;
                        return -1;
                    }
                    else
                    {
                        // Cache the dotdot entry
                        tempCWD->dirccls = tempCWD->dirclus;
                        curent = 1;
                        entry = Cache_File_Entry (tempCWD, &curent, TRUE);
                        if (entry == NULL)
                        {
                            FSerrno = CE_BADCACHEREAD;
                            return -1;
                        }

                        // Get the cluster
                        tempCWD->dirclus = GetFullClusterNumber(entry); // Get Complete Cluster number.
                        tempCWD->dirccls = tempCWD->dirclus;

                        // If we changed to root, record the name
                        if (tempCWD->dirclus == VALUE_DOTDOT_CLUSTER_VALUE_FOR_ROOT) // "0" is the value of Dotdot entry for Root in both FAT types.
                        {
                            j = 0;
                            tempCWD->name[j++] = '\\';
//                            if(utfModeFileName)
//							{
//                            	tempCWD->name[j++] = 0x00;
//							}
                            for (;j < 11;)
                            {
                                tempCWD->name[j] = 0x20;
                            	++j;
                            }

                            /* While moving to Root, get the Root cluster value */
                            tempCWD->dirccls = FatRootDirClusterValue;
                            tempCWD->dirclus = FatRootDirClusterValue;
                        }
                        else
                        {
                            // Otherwise set the name to ..
                            j = 0;
                            tempCWD->name[j++] = '.';
//                            if(utfModeFileName)
//							{
//                            	tempCWD->name[j++] = 0x00;
//                            	tempCWD->name[j++] = '.';
//                            	tempCWD->name[j++] = 0x00;
//							}
//							else
							{
                            	tempCWD->name[j++] = '.';
                            }
                            for (; j < 11;)
                            {
                                tempCWD->name[j] = 0x20;
                            	++j;
                            }
                        }
                        // Cache the dot entry
                        curent = 0;
                        if (Cache_File_Entry(tempCWD, &curent, TRUE) == NULL)
                        {
                            FSerrno = CE_BADCACHEREAD;
                            return -1;
                        }
                        // Move past the next backslash, if necessary
                        while (i == '\\')
                        {
#ifdef ALLOW_PGMFUNCTIONS
                            if (mode)
                            {
								#ifdef SUPPORT_LFN
								if(utfModeFileName)

								{

                				    utf16path2++;
                				    i = *utf16path2;
								}
								else
								#endif
								{
                				    temppath2++;
                				    i = *temppath2;
								}
                            }
                            else
                            {
#endif
								#ifdef SUPPORT_LFN
								if(utfModeFileName)

								{

                				    utf16path++;
                				    i = *utf16path;
								}
								else
								#endif
								{
                				    temppath++;
                				    i = *temppath;
								}
#ifdef ALLOW_PGMFUNCTIONS
                            }
#endif
                        }
                        // Copy and return, if we're at the end
                        if (i == 0)
                        {
                            FileObjectCopy (cwdptr, tempCWD);
                            return 0;
                        }
                    }
                }
                else
                {
                    // If we ended with a . entry,
                    // just return what we have
                    if (i == 0)
                    {
                        FileObjectCopy (cwdptr, tempCWD);
                        return 0;
                    }
                    else
                    {
                        if (i == '\\')
                        {
                            while (i == '\\')
                            {
#ifdef ALLOW_PGMFUNCTIONS
                                if (mode)
                                {
									#ifdef SUPPORT_LFN
									if(utfModeFileName)

									{

                					    utf16path2++;
                					    i = *utf16path2;
									}
									else
									#endif
									{
                					    temppath2++;
                					    i = *temppath2;
									}
                                }
                                else
                                {
#endif
									#ifdef SUPPORT_LFN
									if(utfModeFileName)

									{

                					    utf16path++;
                					    i = *utf16path;
									}
									else
									#endif
									{
                					    temppath++;
                					    i = *temppath;
									}
#ifdef ALLOW_PGMFUNCTIONS
                                }
#endif
                            }
                            if (i == 0)
                            {
                                FileObjectCopy (cwdptr, tempCWD);
                                return 0;
                            }
                        }
                        else
                        {
                            // Anything else after a dot doesn't make sense
                            FSerrno = CE_INVALID_ARGUMENT;
                            return -1;
                        }
                    }
                }

                break;

            // Second case: the first char is the root backslash
            // We will ONLY switch to this case if the first char
            // of the path is a backslash
            case '\\':
            // Increment pointer to second char
#ifdef ALLOW_PGMFUNCTIONS
            if (mode)
            {
				#ifdef SUPPORT_LFN
				if(utfModeFileName)

				{

                    utf16path2++;
                    i = *utf16path2;
				}
				else
				#endif
				{
                    temppath2++;
                    i = *temppath2;
				}
            }
            else
            {
#endif
				#ifdef SUPPORT_LFN
				if(utfModeFileName)

				{

                    utf16path++;
                    i = *utf16path;
				}
				else
				#endif
				{
                    temppath++;
                    i = *temppath;
				}
#ifdef ALLOW_PGMFUNCTIONS
            }
#endif
            // Can't start the path with multiple backslashes
            if (i == '\\')
            {
                FSerrno = CE_INVALID_ARGUMENT;
                return -1;
            }

            if (i == 0)
            {
                // The user is changing directory to
                // the root
                cwdptr->dirclus = FatRootDirClusterValue;
                cwdptr->dirccls = FatRootDirClusterValue;
                j = 0;
                cwdptr->name[j++] = '\\';
//                if(utfModeFileName)
//				{
//                	cwdptr->name[j++] = 0x00;
//				}
                for (; j < 11;)
                {
                    cwdptr->name[j] = 0x20;
                	++j;
                }
                return 0;
            }
            else
            {
                // Our first char is the root dir switch
                tempCWD->dirclus = FatRootDirClusterValue;
                tempCWD->dirccls = FatRootDirClusterValue;
                j = 0;
                tempCWD->name[j++] = '\\';
//                if(utfModeFileName)
//				{
//                	tempCWD->name[j++] = 0x00;
//				}
                for (; j < 11;)
                {
                    tempCWD->name[j] = 0x20;
                	++j;
                }
            }
            break;

        default:
            // We should be at the beginning of a string of letters/numbers
            j = 0;
#ifdef ALLOW_PGMFUNCTIONS
            if (mode)
            {
				#ifdef SUPPORT_LFN
				if(utfModeFileName)

				{

            	    // Change directories as specified
					k = 512;



            	    // Parse the next token
            	    while ((i != 0) && (i != '\\') && (j < k))
            	    {
            	        tempDirectoryString[j++] = i;
            	        tempDirectoryString[j++] = i >> 8;
            	        i = *(++utf16path2);
            	    }

					tempDirectoryString[j++] = 0;
				}

				else

				#endif
        		{

					#if defined(SUPPORT_LFN)

						k = 256;

					#else

						k = 12;

					#endif



            	    // Parse the next token
            	    while ((i != 0) && (i != '\\') && (j < k))
            	    {
            	        tempDirectoryString[j++] = i;
            	        i = *(++temppath2);
            	    }
				}

            }
            else
            {
#endif
				#ifdef SUPPORT_LFN
				if(utfModeFileName)

				{

            	    // Change directories as specified
					k = 512;



            	    // Parse the next token
            	    while ((i != 0) && (i != '\\') && (j < k))
            	    {
            	        tempDirectoryString[j++] = i;
            	        tempDirectoryString[j++] = i >> 8;
            	        i = *(++utf16path);
            	    }

					tempDirectoryString[j++] = 0;
				}

				else

				#endif
        		{

					#if defined(SUPPORT_LFN)

						k = 256;

					#else

						k = 12;

					#endif



            	    // Parse the next token
            	    while ((i != 0) && (i != '\\') && (j < k))
            	    {
            	        tempDirectoryString[j++] = i;
            	        i = *(++temppath);
            	    }
				}

#ifdef ALLOW_PGMFUNCTIONS
            }
#endif
 
            tempDirectoryString[j++] = 0;

            // We got a whole 12 chars
            // There could be more- truncate it
            if (j > k)
            {
                while ((i != 0) && (i != '\\'))
                {
#ifdef ALLOW_PGMFUNCTIONS
                    if (mode)
                    {
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                        	i = *(++utf16path2);
                    	}
						else
						#endif
						{

                        	i = *(++temppath2);
                    	}
                    }
                    else
                    {
#endif
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                        	i = *(++utf16path);
                    	}
						else
						#endif
						{

                        	i = *(++temppath);
                    	}
#ifdef ALLOW_PGMFUNCTIONS
                    }
#endif
                }
            }

            if (FormatDirName (tempDirectoryString, tempCWD,0) == FALSE)
                return -1;

            // copy file object over
            FileObjectCopy(&gFileTemp, tempCWD);

            // See if the directory is there
            if(FILEfind (&gFileTemp, tempCWD, LOOK_FOR_MATCHING_ENTRY, 0) != CE_GOOD)
            {
                // Couldn't find the DIR
                FSerrno = CE_DIR_NOT_FOUND;
                return -1;
            }
            else
            {
                // Found the file
                // Check to make sure it's actually a directory
                if ((gFileTemp.attributes & ATTR_DIRECTORY) == 0 )
                {
                    FSerrno = CE_INVALID_ARGUMENT;
                    return -1;
                }

                // Get the new name
				#if defined(SUPPORT_LFN)
					if(!tempCWD->utf16LFNlength)
				#endif
                		for (j = 0; j < 11; j++)
                		{
                    		tempCWD->name[j] = gFileTemp.name[j];
                		}

                tempCWD->dirclus = gFileTemp.cluster;
                tempCWD->dirccls = tempCWD->dirclus;
            }

            if (i == 0)
            {
                // If we're at the end of the string, we're done
                FileObjectCopy (cwdptr, tempCWD);
                return 0;
            }
            else
            {
                while (i == '\\')
                {
                    // If we get to another backslash, increment past it
#ifdef ALLOW_PGMFUNCTIONS
                    if (mode)
                    {
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                		    utf16path2++;
                		    i = *utf16path2;
						}
						else
						#endif
						{
                		    temppath2++;
                		    i = *temppath2;
						}
                    }
                    else
                    {
#endif
						#ifdef SUPPORT_LFN
						if(utfModeFileName)

						{

                		    utf16path++;
                		    i = *utf16path;
						}
						else
						#endif
						{
                		    temppath++;
                		    i = *temppath;
						}
#ifdef ALLOW_PGMFUNCTIONS
                    }
#endif
                    if (i == 0)
                    {
                        FileObjectCopy (cwdptr, tempCWD);
                        return 0;
                    }
                }
            }
            break;
        }
    } // loop
}



// This string is used by FSgetcwd to return the cwd name if the path
// passed into the function is NULL
char defaultArray [10];


/**************************************************************
  Function:
    char * FSgetcwd (char * path, int numchars)
  Summary:
    Get the current working directory path in Ascii format
  Conditions:
    None
  Input:
    path -      Pointer to the array to return the cwd name in
    numchars -  Number of chars in the path
  Return Values:
    char * - The cwd name string pointer (path or defaultArray)
    NULL -   The current working directory name could not be loaded.
  Side Effects:
    The FSerrno variable will be changed
  Description:
    Get the current working directory path in Ascii format.
    The FSgetcwd function will get the name of the current
    working directory and return it to the user.  The name
    will be copied into the buffer pointed to by 'path,'
    starting at the root directory and copying as many chars
    as possible before the end of the buffer.  The buffer
    size is indicated by the 'numchars' argument.  The first
    thing this function will do is load the name of the current
    working directory, if it isn't already present.  This could
    occur if the user switched to the dotdot entry of a
    subdirectory immediately before calling this function.  The
    function will then copy the current working directory name 
    into the buffer backwards, and insert a backslash character.  
    Next, the function will continuously switch to the previous 
    directories and copy their names backwards into the buffer
    until it reaches the root.  If the buffer overflows, it
    will be treated as a circular buffer, and data will be
    copied over existing characters, starting at the beginning.
    Once the root directory is reached, the text in the buffer
    will be swapped, so that the buffer contains as much of the
    current working directory name as possible, starting at the 
    root.
  Remarks:
    None                                                       
  **************************************************************/
char * FSgetcwd (char * path, int numchars)
{
    // If path is passed in as null, set up a default
    // array with 10 characters
    unsigned short int totalchars = (path == NULL) ? 10 : numchars;
    char * returnPointer;
    char * bufferEnd;
    FILEOBJ tempCWD = &gFileTemp;
    uint8_t bufferOverflow = FALSE;
    signed char j;
    uint32_t curclus;
    uint16_t fHandle, tempindex;
    short int i = 0, index = 0;
    char aChar;
    DIRENTRY entry;

	#if defined(SUPPORT_LFN)
	uint16_t prevHandle;
	UINT16_VAL tempShift;
	FSFILE cwdTemp;
	LFN_ENTRY *lfno;
	unsigned short int *tempLFN = (unsigned short int *)&tempDirectoryString[0];
	#endif

    FSerrno = CE_GOOD;

    // Set up the return value
    if (path == NULL)
        returnPointer = defaultArray;
    else
    {
        returnPointer = path;
        if (numchars == 0)
        {
            FSerrno = CE_INVALID_ARGUMENT;
            return NULL;
        }
    }

    bufferEnd = returnPointer + totalchars - 1;

    FileObjectCopy (tempCWD, cwdptr);

    if (((tempCWD->name[0] == '.') && (tempCWD->name[1] == '.'))
		#if defined(SUPPORT_LFN)	
	 	|| tempCWD->utf16LFNlength
		#endif
		)
    {
        // We last changed directory into a dotdot entry
        // Save the value of the current directory
        curclus = tempCWD->dirclus;
        // Put this dir's dotdot entry into the dirclus
        // Our cwd absolutely is not the root
        fHandle = 1;
        tempCWD->dirccls = tempCWD->dirclus;
        entry = Cache_File_Entry (tempCWD,&fHandle, TRUE);
        if (entry == NULL)
        {
            FSerrno = CE_BADCACHEREAD;
            return NULL;
        }

       // Get the cluster
       TempClusterCalc = GetFullClusterNumber(entry); // Get complete cluster number.

        // For FAT32, if the .. entry is 0, the cluster won't be 0
#ifdef SUPPORT_FAT32
        if (TempClusterCalc == VALUE_DOTDOT_CLUSTER_VALUE_FOR_ROOT)
        {
            tempCWD->dirclus = FatRootDirClusterValue;
        }
        else
#endif
            tempCWD->dirclus = TempClusterCalc;

        tempCWD->dirccls = tempCWD->dirclus;

        // Find the direntry for the entry we were just in
        fHandle = 0;
        entry = Cache_File_Entry (tempCWD, &fHandle, TRUE);
        if (entry == NULL)
        {
            FSerrno = CE_BADCACHEREAD;
            return NULL;
        }

        // Get the cluster
        TempClusterCalc = GetFullClusterNumber(entry); // Get complete cluster number.

        while ((TempClusterCalc != curclus) ||
            ((TempClusterCalc == curclus) &&
            (((unsigned char)entry->DIR_Name[0] == 0xE5) || (entry->DIR_Attr == ATTR_VOLUME) || (entry->DIR_Attr == ATTR_LONG_NAME))))
        {
            fHandle++;
            entry = Cache_File_Entry (tempCWD, &fHandle, FALSE);
            if (entry == NULL)
            {
                FSerrno = CE_BADCACHEREAD;
                return NULL;
            }

            // Get the cluster
            TempClusterCalc = GetFullClusterNumber(entry); // Get complete cluster number in a loop.
        }

		#if defined(SUPPORT_LFN)
       	FileObjectCopy (&cwdTemp, tempCWD);
	   	prevHandle = fHandle - 1;

	   	lfno = (LFN_ENTRY *)Cache_File_Entry (tempCWD, &prevHandle, FALSE);


	   	while((lfno->LFN_Attribute == ATTR_LONG_NAME) && (lfno->LFN_SequenceNo != DIR_DEL)

	   			&& (lfno->LFN_SequenceNo != DIR_EMPTY))

	   	{

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[0];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[1];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[2];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[3];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[4];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[5];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[6];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[7];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[8];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[9];

	   		tempLFN[i++] = tempShift.Val;



	   		tempLFN[i++] = lfno->LFN_Part2[0];

	   		tempLFN[i++] = lfno->LFN_Part2[1];

	   		tempLFN[i++] = lfno->LFN_Part2[2];

	   		tempLFN[i++] = lfno->LFN_Part2[3];

	   		tempLFN[i++] = lfno->LFN_Part2[4];

	   		tempLFN[i++] = lfno->LFN_Part2[5];



	   		tempLFN[i++] = lfno->LFN_Part3[0];

	   		tempLFN[i++] = lfno->LFN_Part3[1];

	   

	   		prevHandle = prevHandle - 1;

	   		lfno = (LFN_ENTRY *)Cache_File_Entry (tempCWD, &prevHandle, FALSE);

	   	}

	   	FileObjectCopy (tempCWD, &cwdTemp);
		#endif

	   	if(i == 0)
	   	{
	   	    for (j = 0; j < 11; j++)
       	    {
        	    tempCWD->name[j] = entry->DIR_Name[j];
        	    cwdptr->name[j] = entry->DIR_Name[j];
       	    }
			#if defined(SUPPORT_LFN)
	   		cwdptr->utf16LFNlength = 0;

	   		tempCWD->utf16LFNlength = 0;

			#endif
	   	}

		#if defined(SUPPORT_LFN)
	   	else
	   	{

	   		tempCWD->utf16LFNlength = i;

			for(j = 12;j >= 0;j--)
			{
				if((tempLFN[i - j - 1]) == 0x0000)
				{
					tempCWD->utf16LFNlength = i - j - 1;
					break;
				}
			}
			cwdptr->utf16LFNlength = tempCWD->utf16LFNlength;

	   		tempCWD->utf16LFNptr = (unsigned short int *)&tempDirectoryString[0];

	   		cwdptr->utf16LFNptr = (unsigned short int *)&tempDirectoryString[0];

	   	}

		#endif
        // Reset our temp dir back to that cluster
        tempCWD->dirclus = curclus;
        tempCWD->dirccls = curclus;
        // This will set us at the cwd, but it will actually
        // have the name in the name field this time
    }

    // There's actually some kind of name value in the cwd
	#if defined(SUPPORT_LFN)
    if (((tempCWD->name[0] == '\\') && (tempCWD->utf16LFNlength == 0x0000)) || 
		((tempCWD->utf16LFNlength != 0x0000) && (tempCWD->utf16LFNptr[0] == (unsigned short int)'\\')) || (numchars == 0x02)) 
	#else
    if ((tempCWD->name[0] == '\\') || (numchars == 0x02))
	#endif
    {
        // Easy, our CWD is the root
        *returnPointer = '\\';
        *(returnPointer + 1) = 0;
        return returnPointer;
    }
    else
    {
        index = 0;
        // Loop until we get back to the root
        while (tempCWD->dirclus != FatRootDirClusterValue)
        {
			#if defined(SUPPORT_LFN)
            if(tempCWD->utf16LFNlength)
            {
			    i = tempCWD->utf16LFNlength * 2 - 1;
			    while(i >= 0)
				{
					#ifdef SUPPORT_LFN
					if(twouint8_tMode)
					{
						returnPointer[index++] = tempDirectoryString[i--];
	            	    if (index == totalchars)
	            	    {
	            	        index = 0;
	            	        bufferOverflow = TRUE;
	            	    }
					}
					else
					#endif
					{
						if(tempDirectoryString[i])
						{
							returnPointer[index++] = tempDirectoryString[i];
	           		  	  	if (index == totalchars)
	           		  	  	{
	           		  	  	    index = 0;
	           		  	  	    bufferOverflow = TRUE;
	           		  	  	}
							
						}
						i--;
					}
				}
			}
			else
			#endif
			{
	            j = 10;
	            while (tempCWD->name[j] == 0x20)
	                j--;
	            if (j >= 8)
	            {
	                while (j >= 8)
	                {
	                    *(returnPointer + index++) = tempCWD->name[j--];
	                    // This is a circular buffer
	                    // Any unnecessary values will be overwritten
	                    if (index == totalchars)
	                    {
	                        index = 0;
	                        bufferOverflow = TRUE;
	                    }

						#ifdef SUPPORT_LFN
						if(twouint8_tMode)
						{
							returnPointer[index++] = 0x00;
	   	    		  	   if (index == totalchars)
	   	    		  	   {
	   	    		  	       index = 0;
	   	    		  	       bufferOverflow = TRUE;
	   	    		  	   }
						}
						#endif
	                }

	                *(returnPointer + index++) = '.';
	                if (index == totalchars)
	                {
	                    index = 0;
	                    bufferOverflow = TRUE;
	                }

					#ifdef SUPPORT_LFN
					if(twouint8_tMode)
					{
						returnPointer[index++] = 0x00;
	   	    		    if (index == totalchars)
	   	    		    {
	   	    		        index = 0;
	   	    		        bufferOverflow = TRUE;
	   	    		    }
					}
					#endif
	            }

	            while (tempCWD->name[j] == 0x20)
	                j--;

	            while (j >= 0)
	            {
	                *(returnPointer + index++) = tempCWD->name[j--];
	                // This is a circular buffer
	                // Any unnecessary values will be overwritten
	                if (index == totalchars)
	                {
	                    index = 0;
	                    bufferOverflow = TRUE;
	                }

					#ifdef SUPPORT_LFN
					if(twouint8_tMode)
					{
						returnPointer[index++] = 0x00;
	   	    		    if (index == totalchars)
	   	    		    {
	   	    		        index = 0;
	   	    		        bufferOverflow = TRUE;
	   	    		    }
					}
					#endif
	            }
			}

			#ifdef SUPPORT_LFN
			if(twouint8_tMode)
			{
				returnPointer[index++] = 0x00;
	            if (index == totalchars)
	            {
	                index = 0;
	                bufferOverflow = TRUE;
	            }
			}
			#endif

            // Put a backslash delimiter in front of the dir name
            *(returnPointer + index++) = '\\';
            if (index == totalchars)
            {
                index = 0;
                bufferOverflow = TRUE;
            }

            // Load the previous entry
            tempCWD->dirccls = tempCWD->dirclus;
            if (GetPreviousEntry (tempCWD))
            {
                FSerrno = CE_BAD_SECTOR_READ;
                return NULL;
            }
        }
    }

    // Point the index back at the last char in the string
    index--;

    i = 0;
    // Swap the chars in the buffer so they are in the right places
    if (bufferOverflow)
    {
        tempindex = index;
        // Swap the overflowed values in the buffer
        while ((index - i) > 0)
        {
             aChar = *(returnPointer + i);
             *(returnPointer + i) = * (returnPointer + index);
             *(returnPointer + index) = aChar;
             index--;
             i++;
        }

        // Point at the non-overflowed values
        i = tempindex + 1;
        index = bufferEnd - returnPointer;

        // Swap the non-overflowed values into the right places
        while ((index - i) > 0)
        {
             aChar = *(returnPointer + i);
             *(returnPointer + i) = * (returnPointer + index);
             *(returnPointer + index) = aChar;
             index--;
             i++;
        }
        // All the values should be in the right place now
        // Null-terminate the string
        *(bufferEnd) = 0;
    }
    else
    {
        // There was no overflow, just do one set of swaps
        tempindex = index;
        while ((index - i) > 0)
        {
            aChar = *(returnPointer + i);
            *(returnPointer + i) = * (returnPointer + index);
            *(returnPointer + index) = aChar;
            index--;
            i++;
        }
        *(returnPointer + tempindex + 1) = 0;
    }

    return returnPointer;
}

#ifdef SUPPORT_LFN

/**************************************************************
  Function:
    char * wFSgetcwd (unsigned short int * path, int numchars)
  Summary:
    Get the current working directory path in UTF16 format
  Conditions:
    None
  Input:
    path -      Pointer to the array to return the cwd name in
    numchars -  Number of chars in the path
  Return Values:
    char * - The cwd name string pointer (path or defaultArray)
    NULL -   The current working directory name could not be loaded.
  Side Effects:
    The FSerrno variable will be changed
  Description:
    Get the current working directory path in UTF16 format.
    The FSgetcwd function will get the name of the current
    working directory and return it to the user.  The name
    will be copied into the buffer pointed to by 'path,'
    starting at the root directory and copying as many chars
    as possible before the end of the buffer.  The buffer
    size is indicated by the 'numchars' argument.  The first
    thing this function will do is load the name of the current
    working directory, if it isn't already present.  This could
    occur if the user switched to the dotdot entry of a
    subdirectory immediately before calling this function.  The
    function will then copy the current working directory name 
    into the buffer backwards, and insert a backslash character.  
    Next, the function will continuously switch to the previous 
    directories and copy their names backwards into the buffer
    until it reaches the root.  If the buffer overflows, it
    will be treated as a circular buffer, and data will be
    copied over existing characters, starting at the beginning.
    Once the root directory is reached, the text in the buffer
    will be swapped, so that the buffer contains as much of the
    current working directory name as possible, starting at the 
    root.
  Remarks:
    None                                                       
  **************************************************************/
char * wFSgetcwd (unsigned short int * path, int numchars)
{
	char *result;
	twouint8_tMode = TRUE;
    result = FSgetcwd ((char *)path,numchars);
	twouint8_tMode = FALSE;
	return result;
}
#endif

/**************************************************************************
  Function:
    void GetPreviousEntry (FSFILE * fo)
  Summary:
    Get the file entry info for the parent dir of the specified dir
  Conditions:
    Should not be called by the user.
  Input:
    fo -  The file to get the previous entry of
  Return Values:
    0 -  The previous entry was successfully retrieved
    -1 - The previous entry could not be retrieved
  Side Effects:
    None
  Description:
    The GetPreviousEntry function is used by the FSgetcwd function to
    load the previous (parent) directory.  This function will load the
    parent directory and then search through the file entries in that
    directory for one that matches the cluster number of the original
    directory.  When the matching entry is found, the name of the
    original directory is copied into the 'fo' FSFILE object.
  Remarks:
    None.
  **************************************************************************/

uint8_t GetPreviousEntry (FSFILE * fo)
{
    int i,j;
    uint16_t fHandle = 1;
    uint32_t dirclus;
    DIRENTRY dirptr;

	#ifdef SUPPORT_LFN
		unsigned short int *tempLFN = (unsigned short int *)&tempDirectoryString[0];
		FSFILE cwdTemp;
		LFN_ENTRY *lfno;

		uint16_t prevHandle;
		UINT16_VAL tempShift;

	#endif

    // Load the previous entry
    dirptr = Cache_File_Entry (fo, &fHandle, TRUE);
    if (dirptr == NULL)
        return -1;

    // Get the cluster
    TempClusterCalc = GetFullClusterNumber(dirptr); // Get complete cluster number.

    if (TempClusterCalc == VALUE_DOTDOT_CLUSTER_VALUE_FOR_ROOT)
    {
        // The previous directory is the root
        fo->name[0] = '\\';
        for (i = 0; i < 11; i++)
        {
            fo->name[i] = 0x20;
        }
        fo->dirclus = FatRootDirClusterValue;
        fo->dirccls = FatRootDirClusterValue;
    }
    else
    {
        // Get the directory name
        // Save the previous cluster value
       // Get the cluster

        dirclus = TempClusterCalc;
        fo->dirclus = TempClusterCalc;
        fo->dirccls = TempClusterCalc;


        // Load the previous previous cluster
        dirptr = Cache_File_Entry (fo, &fHandle, TRUE);
        if (dirptr == NULL)
            return -1;

       // Get the cluster
        TempClusterCalc = GetFullClusterNumber(dirptr); // Get complete cluster number.
#ifdef SUPPORT_FAT32
        // If we're using FAT32 and the previous previous cluster is the root, the
        // value in the dotdot entry will be 0, but the actual cluster won't
        if (TempClusterCalc == VALUE_DOTDOT_CLUSTER_VALUE_FOR_ROOT)
        {
            fo->dirclus = FatRootDirClusterValue;
        }
        else
#endif
            fo->dirclus = TempClusterCalc;

        fo->dirccls = fo->dirclus;

        fHandle = 0;
        dirptr = Cache_File_Entry (fo, &fHandle, TRUE);
        if (dirptr == NULL)
            return -1;
        // Look through it until we get the name
        // of the previous cluster
        // Get the cluster
        TempClusterCalc = GetFullClusterNumber(dirptr); // Get complete cluster number.
        while ((TempClusterCalc != dirclus) ||
            ((TempClusterCalc == dirclus) &&
            (((unsigned char)dirptr->DIR_Name[0] == 0xE5) || (dirptr->DIR_Attr == ATTR_VOLUME) || (dirptr->DIR_Attr == ATTR_LONG_NAME))))
        {
            // Look through the entries until we get the
            // right one
            dirptr = Cache_File_Entry (fo, &fHandle, FALSE);
            if (dirptr == NULL)
                return -1;
            fHandle++;

           TempClusterCalc = GetFullClusterNumber(dirptr); // Get complete cluster number in a loop.
        }

        // The name should be in the entry now
        // Copy the actual directory location back
        fo->dirclus = dirclus;
        fo->dirccls = dirclus;
	}

   	i = 0;
	#ifdef SUPPORT_LFN
       	FileObjectCopy (&cwdTemp, fo);
	   	prevHandle = fHandle - 2;

	   	lfno = (LFN_ENTRY *)Cache_File_Entry (fo, &prevHandle, FALSE);

		// Get the long file name of the short file name(if present)
	   	while((lfno->LFN_Attribute == ATTR_LONG_NAME) && (lfno->LFN_SequenceNo != DIR_DEL)

	   			&& (lfno->LFN_SequenceNo != DIR_EMPTY))

	   	{

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[0];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[1];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[2];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[3];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[4];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[5];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[6];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[7];

	   		tempLFN[i++] = tempShift.Val;

	   		tempShift.uint8_t.LB = lfno->LFN_Part1[8];

	   		tempShift.uint8_t.HB = lfno->LFN_Part1[9];

	   		tempLFN[i++] = tempShift.Val;


	   		tempLFN[i++] = lfno->LFN_Part2[0];

	   		tempLFN[i++] = lfno->LFN_Part2[1];

	   		tempLFN[i++] = lfno->LFN_Part2[2];

	   		tempLFN[i++] = lfno->LFN_Part2[3];

	   		tempLFN[i++] = lfno->LFN_Part2[4];

	   		tempLFN[i++] = lfno->LFN_Part2[5];


	   		tempLFN[i++] = lfno->LFN_Part3[0];

	   		tempLFN[i++] = lfno->LFN_Part3[1];

	   

	   		prevHandle = prevHandle - 1;

	   		lfno = (LFN_ENTRY *)Cache_File_Entry (fo, &prevHandle, FALSE);

	   	}


	   	FileObjectCopy (fo, &cwdTemp);
	#endif

   	if(i == 0)

	{
   	    for (j = 0; j < 11; j++)
        	fo->name[j] = dirptr->DIR_Name[j];
		#ifdef SUPPORT_LFN
   			fo->utf16LFNlength = 0;

   		#endif
   	}
	#ifdef SUPPORT_LFN
   	else

   	{

		fo->utf16LFNlength = i;

		

		for(j = 12;j >= 0;j--)

		{

			if((tempLFN[i - j - 1]) == 0x0000)

			{

				fo->utf16LFNlength = i - j - 1;

				break;

			}

		}

		
   		fo->utf16LFNptr = (unsigned short int *)&tempDirectoryString[0];

   	}

	#endif

    return 0;
}
#endif


#ifdef ALLOW_FILESEARCH

/***********************************************************************************
  Function:
    int FindFirst (const char * fileName, unsigned int attr, SearchRec * rec)
  Summary:
    Initial search function for the input Ascii fileName on PIC24/PIC32/dsPIC devices.
  Conditions:
    None
  Input:
    fileName - The name to search for
             - Parital string search characters
             - * - Indicates the rest of the filename or extension can vary (e.g. FILE.*)
             - ? - Indicates that one character in a filename can vary (e.g. F?LE.T?T)
    attr -            The attributes that a found file may have
         - ATTR_READ_ONLY -  File may be read only
         - ATTR_HIDDEN -     File may be a hidden file
         - ATTR_SYSTEM -     File may be a system file
         - ATTR_VOLUME -     Entry may be a volume label
         - ATTR_DIRECTORY -  File may be a directory
         - ATTR_ARCHIVE -    File may have archive attribute
         - ATTR_MASK -       All attributes
    rec -             pointer to a structure to put the file information in
  Return Values:
    0 -  File was found
    -1 - No file matching the specified criteria was found
  Side Effects:
    Search criteria from previous FindFirst call on passed SearchRec object
    will be lost. "utf16LFNfound" is overwritten after subsequent FindFirst/FindNext
    operations.It is the responsibility of the application to read the "utf16LFNfound"
    before it is lost.The FSerrno variable will be changed.
  Description:
    Initial search function for the input Ascii fileName on PIC24/PIC32/dsPIC devices.
    The FindFirst function will search for a file based on parameters passed in
    by the user.  This function will use the FILEfind function to parse through
    the current working directory searching for entries that match the specified
    parameters.  If a file is found, its parameters are copied into the SearchRec
    structure, as are the initial parameters passed in by the user and the position
    of the file entry in the current working directory.If the return value of the 
    function is 0 then "utf16LFNfoundLength" indicates whether the file found was 
    long file name or short file name(8P3 format). The "utf16LFNfoundLength" is non-zero
    for long file name and is zero for 8P3 format."utf16LFNfound" points to the
    address of long file name if found during the operation.
  Remarks:
    Call FindFirst or FindFirstpgm before calling FindNext
  ***********************************************************************************/
int FindFirst (const char * fileName, unsigned int attr, SearchRec * rec)
{
    FSFILE f;
    FILEOBJ fo = &f;
    uint16_t fHandle;
    uint8_t j;
    uint8_t Index;
	#ifdef SUPPORT_LFN
		short int indexLFN;
	#endif

    FSerrno = CE_GOOD;

	#ifdef SUPPORT_LFN
		fo->utf16LFNptr = &recordSearchName[0];
		rec->utf16LFNfound = &recordFoundName[0];
	#endif

	// Format the file name as per 8.3 format or LFN format
    if( !FormatFileName(fileName, fo, 1) )
    {
        FSerrno = CE_INVALID_FILENAME;
        return -1;
    }

    rec->initialized = FALSE;

	#if defined(SUPPORT_LFN)
	rec->AsciiEncodingType = fo->AsciiEncodingType;
	recordSearchLength = fo->utf16LFNlength;

	// If file name is 8.3 format copy it in 'searchname' string
    if(!recordSearchLength)
	#endif
    {
    	for (Index = 0; (Index < 12) && (fileName[Index] != 0); Index++)
    	{
        	rec->searchname[Index] = fileName[Index];
    	}

    	for (;Index < FILE_NAME_SIZE_8P3 + 2; Index++)
    	{
        	rec->searchname[Index] = 0;
    	}
	}

    rec->searchattr = attr;
#ifdef ALLOW_DIRS
    rec->cwdclus = cwdptr->dirclus;
#else
    rec->cwdclus = FatRootDirClusterValue;
#endif

    fo->dsk = &gDiskData;
    fo->cluster = 0;
    fo->ccls    = 0;
    fo->entry = 0;
    fo->attributes = attr;

#ifndef ALLOW_DIRS
    // start at the root directory
    fo->dirclus    = FatRootDirClusterValue;
    fo->dirccls    = FatRootDirClusterValue;
#else
    fo->dirclus = cwdptr->dirclus;
    fo->dirccls = cwdptr->dirccls;
#endif

    // copy file object over
    FileObjectCopy(&gFileTemp, fo);

    // See if the file is found
    if (FILEfind (fo, &gFileTemp,LOOK_FOR_MATCHING_ENTRY, 1) != CE_GOOD)
    {
        FSerrno = CE_FILE_NOT_FOUND;
        return -1;
    }

    fHandle = fo->entry;

    if (FILEopen (fo, &fHandle, 'r') == CE_GOOD)
    {
		#if defined(SUPPORT_LFN)
		rec->utf16LFNfoundLength = fo->utf16LFNlength;
		if(fo->utf16LFNlength)
		{
			indexLFN = fo->utf16LFNlength;
			recordFoundName[indexLFN] = 0x0000;
			while(indexLFN--)
				recordFoundName[indexLFN] = fileFoundString[indexLFN];
		}
		#endif

		for(j = 0; j < FILE_NAME_SIZE_8P3 + 2 ; j++)
		{
            rec->filename[j] = 0;
		}

        // Copy as much name as there is
        if (fo->attributes != ATTR_VOLUME)
        {
            for (Index = 0, j = 0; (j < 8) && (fo->name[j] != 0x20); Index++, j++)
            {
               rec->filename[Index] = fo->name[j];
            }

			if(fo->name[8] != 0x20)
			{
            	rec->filename[Index++] = '.';

	            // Move to the extension, even if there are more space chars
	            for (j = 8; (j < 11) && (fo->name[j] != 0x20); Index++, j++)
	            {
	               rec->filename[Index] = fo->name[j];
	            }
			}
        }
        else
        {
            for (Index = 0; Index < DIR_NAMECOMP; Index++)
            {
                rec->filename[Index] = fo->name[Index];
            }
        }

        rec->attributes = fo->attributes;
        rec->filesize = fo->size;
        rec->timestamp = (uint32_t)((uint32_t)fo->date << 16) + fo->time;
        rec->entry = fo->entry;
        rec->initialized = TRUE;
        return 0;
    }
    else
    {
        FSerrno = CE_BADCACHEREAD;
        return -1;
    }
}

/**********************************************************************
  Function:
    int FindNext (SearchRec * rec)
  Summary:
    Sequential search function
  Conditions:
    None
  Input:
    rec -  The structure to store the file information in
  Return Values:
    0 -  File was found
    -1 - No additional files matching the specified criteria were found
  Side Effects:
    Search criteria from previous FindNext call on passed SearchRec object
    will be lost. "utf16LFNfound" is overwritten after subsequent FindFirst/FindNext
    operations.It is the responsibility of the application to read the "utf16LFNfound"
    before it is lost.The FSerrno variable will be changed.
  Description:
    The FindNext function performs the same function as the FindFirst
    funciton, except it does not copy any search parameters into the
    SearchRec structure (only info about found files) and it begins
    searching at the last directory entry offset at which a file was
    found, rather than at the beginning of the current working
    directory.If the return value of the function is 0 then "utf16LFNfoundLength"
    indicates whether the file found was long file name or short file
    name(8P3 format). The "utf16LFNfoundLength" is non-zero for long file name
    and is zero for 8P3 format."utf16LFNfound" points to the address of long 
    file name if found during the operation.
  Remarks:
    Call FindFirst or FindFirstpgm before calling this function
  **********************************************************************/
int FindNext (SearchRec * rec)
{
    FSFILE f;
    FILEOBJ fo = &f;
    uint8_t i, j;
	#ifdef SUPPORT_LFN
		short int indexLFN;
	#endif

    FSerrno = CE_GOOD;

    // Make sure we called FindFirst on this object
    if (rec->initialized == FALSE)
    {
        FindFirst("*.*", ATTR_ARCHIVE, rec);
        return 0;
    }

    // Make sure we called FindFirst in the cwd
#ifdef ALLOW_DIRS
    if (rec->cwdclus != cwdptr->dirclus)
    {
        FSerrno = CE_INVALID_ARGUMENT;
        return -1;
    }
#endif
    
	#if defined(SUPPORT_LFN)
    fo->AsciiEncodingType = rec->AsciiEncodingType;
    fo->utf16LFNlength = recordSearchLength;
	if(fo->utf16LFNlength)
	{
	    fo->utf16LFNptr = &recordSearchName[0];
    }
	else
	#endif
	{
		// Format the file name
	    if( !FormatFileName(rec->searchname, fo, 1) )
	    {
	        FSerrno = CE_INVALID_FILENAME;
	        return -1;
	    }
    }

    /* Brn: Copy the formatted name to "fo" which is necesary before calling "FILEfind" function */
    //strcpy(fo->name,rec->searchname);

    fo->dsk = &gDiskData;
    fo->cluster = 0;
    fo->ccls    = 0;
    fo->entry = rec->entry + 1;
    fo->attributes = rec->searchattr;

#ifndef ALLOW_DIRS
    // start at the root directory
    fo->dirclus    = FatRootDirClusterValue;
    fo->dirccls    = FatRootDirClusterValue;
#else
    fo->dirclus = cwdptr->dirclus;
    fo->dirccls = cwdptr->dirccls;
#endif

    // copy file object over
    FileObjectCopy(&gFileTemp, fo);

    // See if the file is found
    if (CE_GOOD != FILEfind (fo, &gFileTemp,LOOK_FOR_MATCHING_ENTRY, 1))
    {
        FSerrno = CE_FILE_NOT_FOUND;
        return -1;
    }
    else
    {
		#if defined(SUPPORT_LFN)
		rec->utf16LFNfoundLength = fo->utf16LFNlength;
		if(fo->utf16LFNlength)
		{
			indexLFN = fo->utf16LFNlength;
			recordFoundName[indexLFN] = 0x0000;
			while(indexLFN--)
				recordFoundName[indexLFN] = fileFoundString[indexLFN];
		}
		#endif

		for(j = 0; j < FILE_NAME_SIZE_8P3 + 2 ; j++)
		{
            rec->filename[j] = 0;
		}

        if (fo->attributes != ATTR_VOLUME)
        {
            for (i = 0, j = 0; (j < 8) && (fo->name[j] != 0x20); i++, j++)
            {
               rec->filename[i] = fo->name[j];
            }

			if(fo->name[8] != 0x20)
			{
            	rec->filename[i++] = '.';

	            // Move to the extension, even if there are more space chars
	            for (j = 8; (j < 11) && (fo->name[j] != 0x20); i++, j++)
	            {
	               rec->filename[i] = fo->name[j];
	            }
			}
        }
        else
        {
            for (i = 0; i < DIR_NAMECOMP; i++)
            {
                rec->filename[i] = fo->name[i];
            }
        }

        rec->attributes = fo->attributes;
        rec->filesize = fo->size;
        rec->timestamp = (uint32_t)((uint32_t)fo->date << 16) + fo->time;
        rec->entry = fo->entry;
        return 0;
    }
}

/***********************************************************************************
  Function:
    int wFindFirst (const unsigned short int * fileName, unsigned int attr, SearchRec * rec)
  Summary:
    Initial search function for the 'fileName' in UTF16 format on PIC24/PIC32/dsPIC devices.
  Conditions:
    None
  Input:
    fileName - The name to search for
             - Parital string search characters
             - * - Indicates the rest of the filename or extension can vary (e.g. FILE.*)
             - ? - Indicates that one character in a filename can vary (e.g. F?LE.T?T)
    attr -            The attributes that a found file may have
         - ATTR_READ_ONLY -  File may be read only
         - ATTR_HIDDEN -     File may be a hidden file
         - ATTR_SYSTEM -     File may be a system file
         - ATTR_VOLUME -     Entry may be a volume label
         - ATTR_DIRECTORY -  File may be a directory
         - ATTR_ARCHIVE -    File may have archive attribute
         - ATTR_MASK -       All attributes
    rec -             pointer to a structure to put the file information in
  Return Values:
    0 -  File was found
    -1 - No file matching the specified criteria was found
  Side Effects:
    Search criteria from previous wFindFirst call on passed SearchRec object
    will be lost. "utf16LFNfound" is overwritten after subsequent wFindFirst/FindNext
    operations.It is the responsibility of the application to read the "utf16LFNfound"
    before it is lost.The FSerrno variable will be changed.
  Description:
    Initial search function for the 'fileName' in UTF16 format on PIC24/PIC32/dsPIC devices.
    The wFindFirst function will search for a file based on parameters passed in
    by the user.  This function will use the FILEfind function to parse through
    the current working directory searching for entries that match the specified
    parameters.  If a file is found, its parameters are copied into the SearchRec
    structure, as are the initial parameters passed in by the user and the position
    of the file entry in the current working directory.If the return value of the 
    function is 0 then "utf16LFNfoundLength" indicates whether the file found was 
    long file name or short file name(8P3 format). The "utf16LFNfoundLength" is non-zero
    for long file name and is zero for 8P3 format."utf16LFNfound" points to the
    address of long file name if found during the operation.
  Remarks:
    Call FindFirst or FindFirstpgm before calling FindNext
  ***********************************************************************************/

#ifdef SUPPORT_LFN
int wFindFirst (const unsigned short int * fileName, unsigned int attr, SearchRec * rec)
{
	int result;
	utfModeFileName = TRUE;
	result = FindFirst ((const char *)fileName,attr,rec);
	utfModeFileName = FALSE;
	return result;
}
#endif

#endif

#ifdef ALLOW_FSFPRINTF

/**********************************************************************
  Function:
    int FSputc (char c, FSFILE * file)
  Summary:
    FSfprintf helper function to write a char
  Conditions:
    This function should not be called by the user.
  Input:
    c - The character to write to the file.
    file - The file to write to.
  Return Values:
    0 -   The character was written successfully
    EOF - The character was not written to the file.
  Side Effects:
    None
  Description:
    This is a helper function for FSfprintf.  It will write one
    character to a file.
  Remarks:
    None
  **********************************************************************/

int FSputc (char c, FSFILE * file)
{
    if (FSfwrite ((void *)&c, 1, 1, file) != 1)
        return EOF;
    else
        return 0;
}

#endif
