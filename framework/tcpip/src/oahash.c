/*******************************************************************************
  Hash table implementation file

  Summary:
    Hash Table manipulation routines
    
  Description:
    This source file contains the functions and storage of the 
    hash table manipulation routines
*******************************************************************************/

/*******************************************************************************
File Name:  oahash.c
Copyright � 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
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

#include <stdint.h>
#include <stdbool.h>

#include "tcpip/src/oahash.h"


// local prototypes
// 

static OA_HASH_ENTRY*   _OAHashFindBkt(OA_HASH_DCPT* pOH, void* key);

static __inline__ void __attribute__((always_inline)) _OAHashRemoveEntry(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* pOE)
{
    pOE->flags.busy = 0;
    pOH->fullSlots--;
}


/*static __inline__*/static  size_t /*__attribute__((always_inline))*/ _OAHashProbeStep(OA_HASH_DCPT* pOH, void* key)
{
    size_t probeStep;
    
#if defined(OA_DOUBLE_HASH_PROBING)
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
    probeStep = (*pOH->probeHash)(pOH, key);
#else
    probeStep = TCPIP_OAHASH_HashProbe(pOH, key);
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
    if(probeStep == 0)
    {   // try to avoid probing the same bucket over and over again
        // when probeHash returns 0.
        probeStep = pOH->probeStep;
    }
#else
    probeStep = pOH->probeStep;
#endif  // defined(OA_DOUBLE_HASH_PROBING)

    return probeStep;
}


// implementation

// Initializes a OA hash table
void TCPIP_OAHASH_Initialize(OA_HASH_DCPT* pOH)
{
    OA_HASH_ENTRY*  pHE;    
    size_t  ix;

    pOH->fullSlots = 0; 
    
    pHE = (OA_HASH_ENTRY*)pOH->memBlk;
    for(ix = 0; ix < pOH->hEntries; ix++)
    {
        pHE->flags.value = 0;
        pHE = (OA_HASH_ENTRY*)((uint8_t*)pHE + pOH->hEntrySize);
    }
}


// performs look up only
// if no such entry found, it returns NULL
OA_HASH_ENTRY* TCPIP_OAHASH_EntryLookup(OA_HASH_DCPT* pOH, void* key)
{
    OA_HASH_ENTRY*  pBkt;
    size_t      bkts = 0;
    size_t      bktIx;
    size_t      probeStep;
   
    probeStep = _OAHashProbeStep(pOH, key);
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
    bktIx = (*pOH->hashF)(pOH, key);
#else
    bktIx = TCPIP_OAHASH_KeyHash(pOH, key);
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

    if(bktIx < 0)
    {
        bktIx += pOH->hEntries;
    }
    
    while(bkts < pOH->hEntries)
    {
        pBkt = (OA_HASH_ENTRY*)((uint8_t*)(pOH->memBlk) + bktIx * pOH->hEntrySize);
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
        if(pBkt->flags.busy && (*pOH->cmpF)(pOH, pBkt, key) == 0)
        {   // found entry
            pBkt->flags.newEntry = 0;
            return pBkt;
        }
#else
        if(pBkt->flags.busy && TCPIP_OAHASH_KeyCompare(pOH, pBkt, key) == 0)
        {   // found entry
            pBkt->flags.newEntry = 0;
            return pBkt;
        }
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

        // advance to the next hash slot
        bktIx += probeStep;
        if(bktIx < 0)
        {
            bktIx += pOH->hEntries;
        }
        else if(bktIx >= pOH->hEntries)
        {
            bktIx -= pOH->hEntries;
        }

        bkts++;
    }
    
    return 0;   // not found
}

// Performs look up and insert
// if key is found, it returns the pointer to the existing entry
// if key was not found but there's an empty slot it will insert
// the key in this slot and newEntry flag will be set
// If there's no room in the hash it will call the delF to empty
// a slot and place the key there 
// If the delF is NULL it will return NULL.
// NULL is also returned when the probeStep is not properly chosen and
// the hash cannot be properly traversed in one pass
// (detect the situation by probing that the cache was not full:
// fullSlots < hElements)
OA_HASH_ENTRY*   TCPIP_OAHASH_EntryLookupOrInsert(OA_HASH_DCPT* pOH, void* key)
{
    OA_HASH_ENTRY   *pBkt, *pDel;

    pBkt = _OAHashFindBkt(pOH, key);
    if(pBkt == 0)
    {
        if(pOH->fullSlots != pOH->hEntries)
        {   // wrong probeStep!
            return 0;
        }
        
        // else cache is full
        // discard an old entry and retry
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
        if(pOH->delF == 0 || (pDel = (*pOH->delF)(pOH)) == 0)
        {   // nothing else we can do
            return 0;
        }
#else
        if((pDel = TCPIP_OAHASH_EntryDelete(pOH)) == 0)
        {   // nothing else we can do
            return 0;
        }
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

        _OAHashRemoveEntry(pOH, pDel);
        pBkt = _OAHashFindBkt(pOH, key);
        if(pBkt == 0)
        {   // probeStep failure, again
            return 0;
        }
    }

    // we found an entry
    if(pBkt->flags.busy == 0)
    {
        pBkt->flags.busy = 1;
        pBkt->flags.newEntry = 1;
    }
    else
    {   // old entry
        pBkt->flags.newEntry = 0;
    }
    
    return pBkt;
}


// Function to delete an entry from the hash
// SHOULD be called when entries have to be deleted!
// because the hash also has to do some internal clean-up.
// Note: when an entry is deleted by TCPIP_OAHASH_EntryLookupOrInsert (calling pOH->delF)
// the hash state is maintained internally, no need to call TCPIP_OAHASH_EntryRemove();
void TCPIP_OAHASH_EntryRemove(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* pOE)
{
    _OAHashRemoveEntry(pOH, pOE);
}

// Function to remove all entries from the hash
// SHOULD be called when entries have to be deleted!
// because the hash also has to do some internal clean-up.
void TCPIP_OAHASH_EntriesRemoveAll(OA_HASH_DCPT* pOH)
{
    OA_HASH_ENTRY*  pBkt;
    size_t      bktIx;
    
    pBkt = (OA_HASH_ENTRY*)pOH->memBlk;
    for(bktIx = 0; bktIx < pOH->hEntries; bktIx++)
    {
        if(pBkt->flags.busy)
        {   // found entry
            _OAHashRemoveEntry(pOH, pBkt);
        }

        pBkt = (OA_HASH_ENTRY*)((uint8_t*)pBkt + pOH->hEntrySize);
    }
}

OA_HASH_ENTRY* TCPIP_OAHASH_EntryGet(OA_HASH_DCPT* pOH, size_t entryIx)
{
    if(entryIx < pOH->hEntries)
    {
        return (OA_HASH_ENTRY*)((uint8_t*)(pOH->memBlk) + entryIx * pOH->hEntrySize);
    }

    return 0;
}

// implementation

// finds a entry that either contains the desired key
// or is empty and can be used to insert the key 
static OA_HASH_ENTRY* _OAHashFindBkt(OA_HASH_DCPT* pOH, void* key)
{
    OA_HASH_ENTRY*  pBkt;
    size_t      bktIx;
    size_t      probeStep;
    size_t      bkts = 0;

    probeStep = _OAHashProbeStep(pOH, key);
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
    bktIx = (*pOH->hashF)(pOH, key);
#else
    bktIx = TCPIP_OAHASH_KeyHash(pOH, key);
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

    if(bktIx < 0)
    {
        bktIx += pOH->hEntries;
    }
    
    while(bkts < pOH->hEntries)
    {
        pBkt = (OA_HASH_ENTRY*)((uint8_t*)(pOH->memBlk) + bktIx * pOH->hEntrySize);
        if(pBkt->flags.busy == 0)
        {   // found unused entry
#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
            (*pOH->cpyF)(pOH, pBkt, key);   // set the key
#else
            TCPIP_OAHASH_KeyCopy(pOH, pBkt, key);   // set the key
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
            pBkt->probeCount = bkts;
            pOH->fullSlots++;
            return pBkt;
        }

#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
        if((*pOH->cmpF)(pOH, pBkt, key) == 0)
        {   // found entry
            return pBkt;
        }
#else
        if(TCPIP_OAHASH_KeyCompare(pOH, pBkt, key) == 0)
        {   // found entry
            return pBkt;
        }
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

        // advance to the next hash slot
        bktIx += probeStep;
        if(bktIx < 0)
        {
            bktIx += pOH->hEntries;
        }
        else if(bktIx >= pOH->hEntries)
        {
            bktIx -= pOH->hEntries;
        }

        bkts++;
    }
    
    return 0;   // cache full, not found
}



