/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    error.c
  
  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic 
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
File Name:  error.c
Copyright � 2013 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END



#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif
 
#include <error.h>

#ifdef _MSC_VER
    /* 4996 warning to use MS extensions e.g., strcpy_s instead of XSTRNCPY */
    #pragma warning(disable: 4996)
#endif


void CTaoCryptErrorString(int error, char* buffer)
{
    const int max = MAX_ERROR_SZ;   /* shorthand */

#ifdef NO_ERROR_STRINGS

    (void)error;
    XSTRNCPY(buffer, "no support for error strings built in", max);

#else

    switch (error) {

    case OPEN_RAN_E :        
        XSTRNCPY(buffer, "opening random device error", max);
        break;

    case READ_RAN_E :
        XSTRNCPY(buffer, "reading random device error", max);
        break;

    case WINCRYPT_E :
        XSTRNCPY(buffer, "windows crypt init error", max);
        break;

    case CRYPTGEN_E : 
        XSTRNCPY(buffer, "windows crypt generation error", max);
        break;

    case RAN_BLOCK_E : 
        XSTRNCPY(buffer, "random device read would block error", max);
        break;

    case MP_INIT_E :
        XSTRNCPY(buffer, "mp_init error state", max);
        break;

    case MP_READ_E :
        XSTRNCPY(buffer, "mp_read error state", max);
        break;

    case MP_EXPTMOD_E :
        XSTRNCPY(buffer, "mp_exptmod error state", max);
        break;

    case MP_TO_E :
        XSTRNCPY(buffer, "mp_to_xxx error state, can't convert", max);
        break;

    case MP_SUB_E :
        XSTRNCPY(buffer, "mp_sub error state, can't subtract", max);
        break;

    case MP_ADD_E :
        XSTRNCPY(buffer, "mp_add error state, can't add", max);
        break;

    case MP_MUL_E :
        XSTRNCPY(buffer, "mp_mul error state, can't multiply", max);
        break;

    case MP_MULMOD_E :
        XSTRNCPY(buffer, "mp_mulmod error state, can't multiply mod", max);
        break;

    case MP_MOD_E :
        XSTRNCPY(buffer, "mp_mod error state, can't mod", max);
        break;

    case MP_INVMOD_E :
        XSTRNCPY(buffer, "mp_invmod error state, can't inv mod", max);
        break; 
        
    case MP_CMP_E :
        XSTRNCPY(buffer, "mp_cmp error state", max);
        break; 
        
    case MP_ZERO_E :
        XSTRNCPY(buffer, "mp zero result, not expected", max);
        break; 
        
    case MEMORY_E :
        XSTRNCPY(buffer, "out of memory error", max);
        break;

    case RSA_WRONG_TYPE_E :
        XSTRNCPY(buffer, "RSA wrong block type for RSA function", max);
        break; 

    case RSA_BUFFER_E :
        XSTRNCPY(buffer, "RSA buffer error, output too small or input too big",
                max);
        break; 

    case BUFFER_E :
        XSTRNCPY(buffer, "Buffer error, output too small or input too big",max);
        break; 

    case ALGO_ID_E :
        XSTRNCPY(buffer, "Setting Cert AlogID error", max);
        break; 

    case PUBLIC_KEY_E :
        XSTRNCPY(buffer, "Setting Cert Public Key error", max);
        break; 

    case DATE_E :
        XSTRNCPY(buffer, "Setting Cert Date validity error", max);
        break; 

    case SUBJECT_E :
        XSTRNCPY(buffer, "Setting Cert Subject name error", max);
        break; 

    case ISSUER_E :
        XSTRNCPY(buffer, "Setting Cert Issuer name error", max);
        break; 

    case CA_TRUE_E :
        XSTRNCPY(buffer, "Setting basic constraint CA true error", max);
        break; 

    case EXTENSIONS_E :
        XSTRNCPY(buffer, "Setting extensions error", max);
        break; 

    case ASN_PARSE_E :
        XSTRNCPY(buffer, "ASN parsing error, invalid input", max);
        break;

    case ASN_VERSION_E :
        XSTRNCPY(buffer, "ASN version error, invalid number", max);
        break;

    case ASN_GETINT_E :
        XSTRNCPY(buffer, "ASN get big int error, invalid data", max);
        break;

    case ASN_RSA_KEY_E :
        XSTRNCPY(buffer, "ASN key init error, invalid input", max);
        break;

    case ASN_OBJECT_ID_E :
        XSTRNCPY(buffer, "ASN object id error, invalid id", max);
        break;

    case ASN_TAG_NULL_E :
        XSTRNCPY(buffer, "ASN tag error, not null", max);
        break;

    case ASN_EXPECT_0_E :
        XSTRNCPY(buffer, "ASN expect error, not zero", max);
        break;

    case ASN_BITSTR_E :
        XSTRNCPY(buffer, "ASN bit string error, wrong id", max);
        break;

    case ASN_UNKNOWN_OID_E :
        XSTRNCPY(buffer, "ASN oid error, unknown sum id", max);
        break;

    case ASN_DATE_SZ_E :
        XSTRNCPY(buffer, "ASN date error, bad size", max);
        break;

    case ASN_BEFORE_DATE_E :
        XSTRNCPY(buffer, "ASN date error, current date before", max);
        break;

    case ASN_AFTER_DATE_E :
        XSTRNCPY(buffer, "ASN date error, current date after", max);
        break;

    case ASN_SIG_OID_E :
        XSTRNCPY(buffer, "ASN signature error, mismatched oid", max);
        break;

    case ASN_TIME_E :
        XSTRNCPY(buffer, "ASN time error, unkown time type", max);
        break;

    case ASN_INPUT_E :
        XSTRNCPY(buffer, "ASN input error, not enough data", max);
        break;

    case ASN_SIG_CONFIRM_E :
        XSTRNCPY(buffer, "ASN sig error, confirm failure", max);
        break;

    case ASN_SIG_HASH_E :
        XSTRNCPY(buffer, "ASN sig error, unsupported hash type", max);
        break;

    case ASN_SIG_KEY_E :
        XSTRNCPY(buffer, "ASN sig error, unsupported key type", max);
        break;

    case ASN_DH_KEY_E :
        XSTRNCPY(buffer, "ASN key init error, invalid input", max);
        break;

    case ASN_NTRU_KEY_E :
        XSTRNCPY(buffer, "ASN NTRU key decode error, invalid input", max);
        break;

    case ECC_BAD_ARG_E :
        XSTRNCPY(buffer, "ECC input argument wrong type, invalid input", max);
        break;

    case ASN_ECC_KEY_E :
        XSTRNCPY(buffer, "ECC ASN1 bad key data, invalid input", max);
        break;

    case ECC_CURVE_OID_E :
        XSTRNCPY(buffer, "ECC curve sum OID unsupported, invalid input", max);
        break;

    case BAD_FUNC_ARG :
        XSTRNCPY(buffer, "Bad function argument", max);
        break;

    case NOT_COMPILED_IN :
        XSTRNCPY(buffer, "Feature not compiled in", max);
        break;

    case UNICODE_SIZE_E :
        XSTRNCPY(buffer, "Unicode password too big", max);
        break;

    case NO_PASSWORD :
        XSTRNCPY(buffer, "No password provided by user", max);
        break;

    case ALT_NAME_E :
        XSTRNCPY(buffer, "Alt Name problem, too big", max);
        break;

    case AES_GCM_AUTH_E:
        XSTRNCPY(buffer, "AES-GCM Authentication check fail", max);
        break;

    case AES_CCM_AUTH_E:
        XSTRNCPY(buffer, "AES-CCM Authentication check fail", max);
        break;

    case CAVIUM_INIT_E:
        XSTRNCPY(buffer, "Cavium Init type error", max);
        break;

    case COMPRESS_INIT_E:
        XSTRNCPY(buffer, "Compress Init error", max);
        break;

    case COMPRESS_E:
        XSTRNCPY(buffer, "Compress error", max);
        break;

    case DECOMPRESS_INIT_E:
        XSTRNCPY(buffer, "DeCompress Init error", max);
        break;

    case DECOMPRESS_E:
        XSTRNCPY(buffer, "DeCompress error", max);
        break;

    default:
        XSTRNCPY(buffer, "unknown error number", max);

    }

#endif /* NO_ERROR_STRINGS */

}
