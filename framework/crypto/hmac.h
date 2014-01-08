/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    hmac.h
  
  Summary:
    Crypto Framework Libarary header for cryptographic functions.

  Description:
    This header file contains function prototypes and definitions of
    the data types and constants that make up the Cryptographic Framework
    Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
Copyright © 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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
//DOM-IGNORE-END




#ifndef NO_HMAC

#ifndef CTAO_CRYPT_HMAC_H
#define CTAO_CRYPT_HMAC_H

#ifndef NO_MD5
    #include <md5.h>
#endif

#include <sha.h>

#ifndef NO_SHA256
    #include <sha256.h>
#endif

#ifdef CYASSL_SHA384
    #include <sha512.h>
#endif

#ifdef HAVE_CAVIUM
    #include <logging.h>
    #include "cavium_common.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


#define CYASSL_HMAC_CAVIUM_MAGIC 0xBEEF0005

enum {
    IPAD    = 0x36,
    OPAD    = 0x5C,
#ifdef NO_MD5
    MD5     = 0,
#endif
#if defined(CYASSL_SHA512)
    INNER_HASH_SIZE = SHA512_DIGEST_SIZE,
    HMAC_BLOCK_SIZE = SHA512_BLOCK_SIZE
#elif defined(CYASSL_SHA384)
    INNER_HASH_SIZE = SHA384_DIGEST_SIZE,
    HMAC_BLOCK_SIZE = SHA384_BLOCK_SIZE
#elif !defined(NO_SHA256)
    INNER_HASH_SIZE = SHA256_DIGEST_SIZE,
    HMAC_BLOCK_SIZE = SHA256_BLOCK_SIZE,
    SHA512          = 4,
    SHA384          = 5
#else
    INNER_HASH_SIZE = SHA_DIGEST_SIZE,
    HMAC_BLOCK_SIZE = SHA_BLOCK_SIZE,
    SHA256          = 2,                     /* hash type unique */
    SHA512          = 4,
    SHA384          = 5
#endif
};


/* hash union */
typedef union {
    #ifndef NO_MD5
        Md5 md5;
    #endif
    #ifndef NO_SHA
        Sha sha;
    #endif
    #ifndef NO_SHA256
        Sha256 sha256;
    #endif
    #ifdef CYASSL_SHA384
        Sha384 sha384;
    #endif
    #ifdef CYASSL_SHA512
        Sha512 sha512;
    #endif
} Hash;

/* Hmac digest */
typedef struct Hmac {
    Hash    hash;
    word32  ipad[HMAC_BLOCK_SIZE  / sizeof(word32)];  /* same block size all*/
    word32  opad[HMAC_BLOCK_SIZE  / sizeof(word32)];
    word32  innerHash[INNER_HASH_SIZE / sizeof(word32)]; /* max size */
    byte    macType;                                     /* md5 sha or sha256 */
    byte    innerHashKeyed;                              /* keyed flag */
#ifdef HAVE_CAVIUM
    word16   keyLen;          /* hmac key length */
    word16   dataLen;
    HashType type;            /* hmac key type */
    int      devId;           /* nitrox device id */
    word32   magic;           /* using cavium magic */
    word64   contextHandle;   /* nitrox context memory handle */
    byte*    data;            /* buffered input data for one call */
#endif
} Hmac;


/* does init */
CYASSL_API void HmacSetKey(Hmac*, int type, const byte* key, word32 keySz);
CYASSL_API void HmacUpdate(Hmac*, const byte*, word32);
CYASSL_API void HmacFinal(Hmac*, byte*);

#ifdef HAVE_CAVIUM
    CYASSL_API int  HmacInitCavium(Hmac*, int);
    CYASSL_API void HmacFreeCavium(Hmac*);
#endif


#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* CTAO_CRYPT_HMAC_H */

#endif /* NO_HMAC */

