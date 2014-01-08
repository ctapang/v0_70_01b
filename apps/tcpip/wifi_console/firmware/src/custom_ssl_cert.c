/*******************************************************************************
  RSA Public Key Encryption Library Data Storage

  Summary:
    Library for Microchip TCP/IP Stack
    
  Description:
    - Initializes a sample RSA Key and Certificate for use over SSL
    - Reference: PKCS #1
*******************************************************************************/

/*******************************************************************************
File Name: CustomSSLCert.c 
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

#define __CUSTOMSSLCERT_C

#include "tcpip_config.h"

#if defined(TCPIP_STACK_USE_SSL_SERVER)

#include "tcpip/tcpip.h"

#include "ssl_config.h"

// Key Material

// NOTE: the ENCX24J600 RSA is not yet ported to the Unified stack.
//#if defined(ENC100_INTERFACE_MODE)
#if (0)
	// For ENC424J600/624J600, use the on-board crypto with the full 
	// modulus and private key.  For this option, enter the key
	// in big-endian byte order.  SSL_N[] is the modulus and SSL_D[] 
	// is the exponent.
	#if SSL_RSA_KEY_SIZE == 512u
		const uint8_t SSL_N[] = {
			0xAA, 0x96, 0xCA, 0x97, 0xEA, 0x27, 0xB0, 0xD7,
			0xE9, 0x21, 0xD0, 0x40, 0xD4, 0x2C, 0x09, 0x5A,
			0x2E, 0x3A, 0xE4, 0x12, 0x64, 0x2D, 0x4B, 0x1B,
			0x92, 0xDF, 0x79, 0x68, 0x4E, 0x3C, 0x51, 0xF4,
			0x43, 0x48, 0x0D, 0xF2, 0xC8, 0x50, 0x9B, 0x6E,
			0xE5, 0xEA, 0xFE, 0xEF, 0xD9, 0x10, 0x41, 0x08,
			0x14, 0xF9, 0x85, 0x49, 0xFC, 0x50, 0xD3, 0x57,
			0x34, 0xDC, 0x3A, 0x0D, 0x79, 0xF8, 0xD3, 0x99
		};
		
		const uint8_t SSL_D[] = {
			0x68, 0x5B, 0x6E, 0xFC, 0x98, 0x46, 0x47, 0xAD,
			0x0D, 0xF5, 0x9D, 0x8C, 0xCB, 0x3F, 0x55, 0x49,
			0x51, 0xD6, 0xBD, 0x07, 0x73, 0x39, 0x32, 0x25,
			0x60, 0x28, 0x4E, 0x01, 0x3D, 0x3B, 0x31, 0x76,
			0x98, 0x94, 0x9F, 0x7E, 0x8F, 0xC2, 0x95, 0x37,
			0xE5, 0x76, 0x7E, 0x53, 0x44, 0x21, 0xBC, 0xD6,
			0x80, 0x11, 0xB2, 0xB1, 0x80, 0xCF, 0x1B, 0x09,
			0x5D, 0x2E, 0xE8, 0x31, 0xB2, 0x56, 0xE5, 0xB1
		};
		
	#elif SSL_RSA_KEY_SIZE == 768u
		const uint8_t SSL_N[] = {
			0xE7, 0x9B, 0x59, 0xE0, 0xE3, 0xA9, 0xBC, 0xBD,
			0xE4, 0x66, 0xF0, 0x3B, 0x47, 0x8A, 0x28, 0x88,
			0xA3, 0xE6, 0x10, 0x1E, 0xBD, 0x21, 0x8E, 0x4F,
			0xFA, 0xA1, 0xA8, 0x9F, 0x27, 0x19, 0xE9, 0x3D,
			0x0F, 0x0C, 0x9C, 0xC6, 0x4E, 0xEE, 0x3B, 0x2A,
			0xDF, 0x5A, 0x5D, 0x96, 0xAE, 0x38, 0x92, 0x6D,
			0xAF, 0xFE, 0x9F, 0xB6, 0x9F, 0x95, 0xB6, 0xFF,
			0xEF, 0xB5, 0xAB, 0x1A, 0x8D, 0xAD, 0xE1, 0x14,
			0xF3, 0xC5, 0xF4, 0x35, 0xAC, 0x6F, 0x46, 0x9A,
			0xE5, 0xE0, 0x26, 0xC9, 0xF8, 0x04, 0xF8, 0x8F,
			0xD5, 0x58, 0x8D, 0x25, 0x4A, 0x6B, 0x55, 0x78,
			0x92, 0x0A, 0x6A, 0xA4, 0x87, 0xA4, 0x63, 0x29
		};
			
		const uint8_t SSL_D[] = {
			0x7A, 0x07, 0x4E, 0x29, 0xC1, 0x8A, 0x13, 0x19,
			0xF2, 0x17, 0x92, 0x87, 0x89, 0x3F, 0xEF, 0xEF,
			0x5E, 0x7B, 0xBF, 0x0E, 0x93, 0x13, 0xF5, 0x09,
			0x8A, 0xC2, 0x56, 0x37, 0xD4, 0xC0, 0x40, 0x35,
			0x9D, 0x92, 0x45, 0x9F, 0xEE, 0xC2, 0x72, 0x86,
			0x3A, 0x3C, 0x40, 0x87, 0x3D, 0xB0, 0x2C, 0xE5,
			0x81, 0x74, 0x96, 0x15, 0x0E, 0xFE, 0x26, 0xFF,
			0x0E, 0x55, 0x66, 0x10, 0x75, 0xCD, 0x64, 0xE3,
			0xA3, 0x23, 0x5D, 0x57, 0x69, 0x69, 0xFD, 0xD1,
			0x18, 0xF8, 0x4D, 0xFF, 0x57, 0x8E, 0xE8, 0x9F,
			0x88, 0xE7, 0x83, 0x58, 0x95, 0x79, 0x30, 0x08,
			0x3B, 0xDF, 0x74, 0xFB, 0xD7, 0x3C, 0xF1, 0x21
		};
		
	#elif SSL_RSA_KEY_SIZE == 1024u
		const uint8_t SSL_N[] = {
			0xBF, 0x75, 0xE7, 0xC7, 0x6F, 0xCA, 0xCA, 0x64,
			0x2F, 0x04, 0x7C, 0x2D, 0x78, 0x41, 0xF6, 0xB5,
			0x8D, 0xA4, 0xA9, 0x24, 0x51, 0x08, 0x80, 0xF1,
			0x6C, 0xAE, 0xBD, 0xCA, 0x81, 0xE3, 0x00, 0x82,
			0x7B, 0xB1, 0x90, 0x61, 0x74, 0xE2, 0x0E, 0x86,
			0xFE, 0x45, 0xAE, 0xCA, 0x9D, 0xAE, 0x71, 0x2D,
			0x72, 0x65, 0x52, 0xBA, 0x0C, 0x51, 0x2F, 0xE6,
			0xFD, 0x95, 0x59, 0xC1, 0x60, 0x10, 0x2F, 0x93,
			0x4E, 0x99, 0xDD, 0x8A, 0xAD, 0xC1, 0xCE, 0x1C,
			0xD1, 0x1D, 0xD4, 0xBF, 0x33, 0x25, 0x8A, 0x6A,
			0xCA, 0xC4, 0xD2, 0xC0, 0x68, 0x10, 0x77, 0xC4,
			0xD0, 0x25, 0x42, 0x13, 0xCE, 0x17, 0xFD, 0x59,
			0xDB, 0xE0, 0x4C, 0x70, 0x39, 0x2C, 0xBD, 0x9A,
			0xD6, 0x83, 0x4B, 0x56, 0x11, 0xED, 0x6A, 0xE8,
			0x60, 0xA3, 0x3D, 0x9E, 0xEB, 0xC6, 0xE9, 0x18,
			0xB9, 0x9D, 0xE3, 0x94, 0xBB, 0x85, 0x7D, 0x0F
		};
		
		const uint8_t SSL_D[] = {
			0x95, 0x5C, 0xEF, 0x17, 0xC8, 0x5F, 0xC4, 0xEA,
			0xC9, 0x3F, 0x4F, 0x7C, 0xCD, 0x7F, 0x70, 0x6F,
			0x0C, 0x74, 0x33, 0xBB, 0xF0, 0x37, 0x99, 0x18,
			0x3E, 0xF8, 0x47, 0x79, 0xCF, 0x40, 0x7F, 0x6A,
			0x4C, 0x03, 0x27, 0x26, 0xD0, 0x5F, 0x76, 0x83,
			0xDB, 0xA4, 0x13, 0x0B, 0x60, 0x5D, 0xF1, 0x4F,
			0x4A, 0x1A, 0x3F, 0xA2, 0x82, 0xEF, 0x67, 0x56,
			0x65, 0xE7, 0xF8, 0xA0, 0x82, 0x47, 0xBE, 0x44,
			0x6C, 0x89, 0x08, 0x4B, 0x17, 0x2D, 0xD9, 0xC7,
			0x57, 0xDA, 0x38, 0x4A, 0xC3, 0x09, 0x37, 0x93,
			0x21, 0x3B, 0xAD, 0xE5, 0x55, 0x7B, 0xAD, 0xEC,
			0x39, 0xAF, 0xDF, 0x98, 0xDB, 0xEC, 0x39, 0x31,
			0x65, 0x8B, 0x25, 0x23, 0xFD, 0x66, 0x9C, 0xAC,
			0x74, 0xE7, 0x20, 0xA4, 0x7F, 0x27, 0x86, 0x9E,
			0xD4, 0xA9, 0x66, 0xBA, 0x73, 0x50, 0xD0, 0x9F,
			0xB3, 0x8C, 0xAA, 0x31, 0xBE, 0xDB, 0x7A, 0xA1
		};
	#elif SSL_RSA_KEY_SIZE == 2048u
		const uint8_t SSL_N[] = {
            0xC5, 0xED, 0xD8, 0x35, 0x23, 0x00, 0x33, 0xA6, 
            0xAA, 0xFB, 0x6C, 0xA0, 0xBF, 0x4A, 0x44, 0x92, 
            0x7F, 0xD3, 0x75, 0x4F, 0x8A, 0x6B, 0x33, 0x4D, 
            0xEF, 0x66, 0x51, 0x2D, 0xF2, 0xD0, 0xB2, 0x85, 
            0xF0, 0x24, 0xB7, 0x86, 0x96, 0x66, 0xE6, 0x9A, 
            0x91, 0x61, 0x97, 0x11, 0x3A, 0x4A, 0x78, 0x3A, 
            0x71, 0xB8, 0x5F, 0x69, 0x47, 0xA6, 0x1B, 0x17, 
            0x4F, 0xDE, 0x37, 0x9C, 0x12, 0xB7, 0xD6, 0x72, 
            0x11, 0xCD, 0x94, 0x2B, 0x39, 0xC5, 0x92, 0x9D, 
            0x4B, 0x6B, 0x6C, 0x69, 0x30, 0x99, 0x9E, 0xCC, 
            0x85, 0x80, 0x5F, 0x68, 0x83, 0x41, 0x86, 0xA4, 
            0x2B, 0x9A, 0xEB, 0x95, 0xE0, 0x25, 0xAE, 0x3D, 
            0x9F, 0x76, 0x9B, 0x98, 0x47, 0x82, 0x85, 0x84, 
            0x78, 0x79, 0x0B, 0x5F, 0x7B, 0x0C, 0x31, 0x6D, 
            0x65, 0x8B, 0xFA, 0x65, 0x65, 0x62, 0x79, 0x22, 
            0x01, 0xAD, 0x96, 0x01, 0x84, 0x0C, 0x8B, 0x2D, 
            0xF2, 0x7C, 0x92, 0xB0, 0x08, 0xE6, 0x48, 0xD6, 
            0xA7, 0x57, 0xD8, 0x2D, 0x89, 0x20, 0xF6, 0x49, 
            0x3F, 0xEA, 0xEF, 0xB7, 0x88, 0x31, 0x26, 0x4F, 
            0x1F, 0x96, 0xF0, 0xA1, 0x8B, 0x56, 0xD1, 0x2A, 
            0x11, 0x32, 0x7C, 0xC0, 0xBA, 0xC5, 0x73, 0xFC, 
            0x94, 0x6B, 0xB9, 0x05, 0x6C, 0xFA, 0x6D, 0xF1, 
            0x93, 0x34, 0x41, 0xE1, 0x7A, 0x13, 0xB3, 0xC9, 
            0x40, 0xD1, 0x2D, 0xE2, 0x85, 0xFD, 0x64, 0x6D, 
            0x97, 0xEC, 0xFB, 0xB8, 0x08, 0x53, 0x09, 0x11, 
            0xC3, 0x44, 0x29, 0x5A, 0x2E, 0x96, 0xC4, 0xA6, 
            0x24, 0xB5, 0x00, 0x99, 0xD1, 0x3F, 0x70, 0x2C, 
            0xAA, 0x2A, 0xEC, 0xE7, 0x2A, 0xC9, 0x5C, 0xA6, 
            0x72, 0x33, 0x35, 0x02, 0xB7, 0xC7, 0x4C, 0x33, 
            0x03, 0x3D, 0x2B, 0xD6, 0x66, 0xB7, 0xE2, 0x84, 
            0x45, 0x76, 0x2E, 0xC3, 0x8A, 0x0B, 0x56, 0x8B, 
            0xD9, 0xC9, 0x89, 0xBE, 0x20, 0x20, 0x05, 0x87
	    };

		const uint8_t SSL_D[] = {
            0x2E, 0x84, 0xCF, 0x1A, 0xF6, 0x05, 0xF7, 0x1D, 
            0xC5, 0xF3, 0xDF, 0xBD, 0x0C, 0x18, 0x7D, 0x73, 
            0x5D, 0x1D, 0xAA, 0xE5, 0xAD, 0xE7, 0xB2, 0x20, 
            0x30, 0x13, 0x01, 0x23, 0x66, 0x7D, 0x4C, 0x68, 
            0x14, 0x5F, 0xDC, 0xCE, 0x82, 0x0C, 0xDF, 0x48, 
            0x16, 0xC1, 0x34, 0x0B, 0x35, 0x83, 0x09, 0x2C, 
            0xDB, 0x4B, 0x75, 0x09, 0x3E, 0x70, 0xB8, 0xCF, 
            0x4A, 0xD3, 0x34, 0x88, 0xB7, 0x11, 0x84, 0x12, 
            0x3D, 0x42, 0xEE, 0xFF, 0x15, 0xCD, 0xEC, 0xBE, 
            0x91, 0x5A, 0x47, 0x19, 0x95, 0xF5, 0x95, 0x10, 
            0x06, 0x94, 0x7C, 0x58, 0x08, 0xF9, 0x5E, 0x96, 
            0xB9, 0x34, 0xE9, 0x07, 0xC9, 0xAD, 0xB1, 0x7D, 
            0x04, 0x3C, 0x91, 0x27, 0x42, 0x2F, 0x58, 0x08, 
            0x21, 0x74, 0x79, 0x8A, 0xD0, 0x55, 0xB6, 0x4C, 
            0x3A, 0xE0, 0xA2, 0x52, 0x30, 0x78, 0xEB, 0x75, 
            0x65, 0xA5, 0x91, 0xAA, 0xFB, 0x89, 0x23, 0x30, 
            0x98, 0x81, 0xB2, 0xF5, 0xC4, 0xF0, 0xA9, 0xFB, 
            0xF7, 0x72, 0xD4, 0x1A, 0xBB, 0x40, 0xE3, 0xCB, 
            0xB1, 0xBB, 0x4B, 0x28, 0x7C, 0x1E, 0xC3, 0xA4, 
            0x44, 0xE1, 0x82, 0x24, 0xF5, 0xC7, 0x3D, 0x52, 
            0x82, 0xB5, 0x44, 0x70, 0x33, 0x1A, 0xD6, 0x97, 
            0x6E, 0x64, 0xDA, 0x1F, 0xFC, 0xF5, 0x97, 0x16, 
            0xD1, 0xEB, 0x6F, 0x5B, 0x2A, 0xA2, 0xB5, 0xB7, 
            0x9B, 0x62, 0x30, 0xBB, 0x0F, 0x7E, 0x95, 0x83, 
            0x4C, 0x1F, 0x17, 0x4E, 0xCA, 0xB7, 0x17, 0xD7, 
            0xB6, 0x57, 0xED, 0xCE, 0x4A, 0x31, 0x32, 0x25, 
            0x2E, 0xB3, 0xB4, 0x4E, 0xF9, 0x6E, 0x14, 0x89, 
            0xAE, 0x72, 0x03, 0xA6, 0x8A, 0xEB, 0xC5, 0x72, 
            0xAF, 0x93, 0xF1, 0x03, 0xBD, 0x14, 0x8B, 0xE9, 
            0xD2, 0x18, 0xBE, 0xC9, 0xA3, 0xBF, 0x86, 0x74, 
            0x95, 0x0A, 0x05, 0xC6, 0x44, 0xCB, 0xAF, 0xE0, 
            0xB0, 0x97, 0xF2, 0xEA, 0x80, 0xD4, 0xCD, 0x29
	    };
	#endif
#else
	// For all others without onboard crypto, use the CRT
	// key values for speed. These must all be in little 
	// endian byte order, not network byte order (big endian).
	#if SSL_RSA_KEY_SIZE == 512u

		const uint8_t SSL_P[]__attribute__((aligned(2))) = {	
			0xF7, 0x1D, 0x08, 0xE4, 0xA2, 0xDF, 0xB5, 0x33,
			0x02, 0xAB, 0x6F, 0xDB, 0x5B, 0x3E, 0x5E, 0x91,
			0x7D, 0x50, 0x89, 0x6D, 0xB6, 0x00, 0x02, 0x61,
			0xCD, 0x9F, 0x02, 0x80, 0x67, 0x56, 0x77, 0xD7
		}; 
		
		const uint8_t SSL_Q[]__attribute__((aligned(2))) = {	
			0xEF, 0x76, 0xD3, 0x8A, 0x71, 0xE9, 0x1E, 0x9F,
			0xE4, 0xC5, 0x08, 0x47, 0x94, 0x6D, 0xC5, 0x9A,
			0x57, 0xA6, 0x73, 0x00, 0x3E, 0xC2, 0x1E, 0xA7,
			0x60, 0x66, 0x30, 0x43, 0xD3, 0x35, 0xAE, 0xCA
		};
		
		const uint8_t SSL_dP[]__attribute__((aligned(2))) = {	
			0x49, 0xBF, 0x4E, 0x65, 0x78, 0xAC, 0x03, 0x68,
			0xC9, 0x03, 0xFD, 0x06, 0x04, 0xC2, 0x29, 0x5E,
			0xD7, 0xA1, 0x98, 0xAE, 0x12, 0x44, 0x71, 0x63,
			0xA9, 0xEA, 0x2D, 0xB7, 0xDC, 0xFF, 0xE7, 0x33
		}; 
		
		const uint8_t SSL_dQ[]__attribute__((aligned(2))) = {	
			0xE5, 0x4B, 0x03, 0x39, 0x7F, 0x2D, 0x08, 0xE5,
			0x57, 0x8C, 0xA6, 0x6C, 0x8E, 0xC8, 0x9E, 0xF7,
			0xEE, 0xE9, 0xAC, 0xC7, 0xEE, 0xF7, 0xDE, 0xEC,
			0x19, 0x51, 0x27, 0x3C, 0x85, 0x2B, 0xAF, 0x99
		}; 
		
		const uint8_t SSL_qInv[]__attribute__((aligned(2))) = {	
			0x3D, 0x41, 0xA6, 0xF7, 0xF8, 0x31, 0x37, 0x32,
			0x7E, 0x44, 0x67, 0x71, 0x7B, 0x2F, 0xAB, 0x0C,
			0x05, 0x89, 0xA6, 0x33, 0x58, 0x63, 0x45, 0xF7,
			0x42, 0x8A, 0x77, 0xC7, 0xF0, 0x93, 0xB8, 0x4C
		};
		
	#elif SSL_RSA_KEY_SIZE == 768u
		const uint8_t SSL_P[]__attribute__((aligned(2))) = {	
			0x9D, 0x5F, 0x8A, 0x1E, 0xE2, 0x6E, 0xFB, 0x0B,
			0xD2, 0x12, 0xD4, 0x44, 0x23, 0x4D, 0x2F, 0x3C,
			0x1A, 0xC4, 0xA5, 0xE0, 0xF2, 0x3C, 0xAE, 0x8D,
			0x7B, 0x5C, 0x6F, 0x15, 0x41, 0xF1, 0x05, 0xED,
			0x9B, 0x38, 0x10, 0x60, 0x9A, 0x4C, 0x52, 0xFB,
			0x84, 0x34, 0x67, 0xE7, 0x92, 0xAA, 0xE2, 0xF5
		}; 

		const uint8_t SSL_Q[]__attribute__((aligned(2))) = {	
			0xFD, 0xE9, 0xF6, 0x73, 0xB9, 0x11, 0xE8, 0x6D,
			0x1F, 0xB3, 0x15, 0xB4, 0x11, 0x32, 0x75, 0x91,
			0xF9, 0xE7, 0xDD, 0x06, 0x89, 0x87, 0x3B, 0x5C,
			0xDA, 0x1A, 0x4C, 0x71, 0x62, 0x6F, 0x12, 0xE0,
			0xF5, 0xC0, 0x11, 0xFB, 0x01, 0x3F, 0x8C, 0x85,
			0x13, 0xF7, 0x18, 0xEA, 0x73, 0x52, 0x22, 0xF1
		};
		
		const uint8_t SSL_dP[]__attribute__((aligned(2))) = {	
			0xE1, 0xE9, 0xAD, 0xCE, 0x1E, 0x2D, 0x57, 0xB9,
			0xD6, 0x27, 0x1B, 0x54, 0x9B, 0xA9, 0xCD, 0x33,
			0x4D, 0xE2, 0xCF, 0x3D, 0x2D, 0x6E, 0x22, 0x4C,
			0xC2, 0x95, 0x53, 0x8D, 0xC3, 0x3F, 0xB4, 0x6D,
			0xBB, 0xF5, 0xD6, 0x61, 0x90, 0x73, 0xC8, 0x42,
			0x90, 0x8B, 0xDD, 0x72, 0x43, 0x23, 0x15, 0xBB
		}; 
		
		const uint8_t SSL_dQ[]__attribute__((aligned(2))) = {	
			0xC9, 0xCE, 0xC7, 0x6C, 0xC4, 0x6E, 0x16, 0x28,
			0xCC, 0x39, 0x81, 0x45, 0xB2, 0x20, 0x13, 0x62,
			0x94, 0x84, 0x1F, 0x72, 0x75, 0x71, 0x17, 0xDE,
			0x9B, 0xC1, 0xD4, 0xFA, 0xE1, 0xE0, 0x38, 0xA0,
			0xD3, 0xF0, 0xF2, 0xB4, 0x0E, 0xBB, 0x4D, 0xF1,
			0xD0, 0xB3, 0xB5, 0xA5, 0xF4, 0x82, 0x7C, 0x1D
		}; 
		
		const uint8_t SSL_qInv[]__attribute__((aligned(2))) = {	
			0x5A, 0x4A, 0xB6, 0xBA, 0x96, 0x0D, 0x0A, 0x3D,
			0x3C, 0x60, 0x15, 0xA8, 0xAD, 0x98, 0x01, 0x5F,
			0xA2, 0x6E, 0xC8, 0x4C, 0x4E, 0x43, 0x2F, 0x54,
			0x78, 0x4F, 0x7B, 0x87, 0xBE, 0x42, 0xFE, 0x52,
			0x35, 0x01, 0x5B, 0xCC, 0xAC, 0x09, 0x7E, 0x31,
			0x65, 0x26, 0x6F, 0x90, 0xE7, 0xD5, 0x15, 0x42
		};
		
	#elif SSL_RSA_KEY_SIZE == 1024u
		const uint8_t SSL_P[]__attribute__((aligned(2))) = {	
			0xD1, 0x1D, 0x9B, 0xB1, 0xA1, 0x13, 0xFB, 0xF2,
			0xD3, 0x7D, 0xC0, 0x8C, 0xB7, 0xEA, 0xFD, 0x16,
			0x6E, 0xB2, 0x7F, 0x8A, 0x3F, 0xA9, 0x04, 0x0C,
			0xC2, 0x2F, 0x97, 0xA0, 0x88, 0x33, 0x93, 0xB0,
			0x42, 0xFA, 0xEB, 0x96, 0x27, 0x66, 0x0E, 0x86,
			0x8D, 0x90, 0xBE, 0x66, 0x29, 0x44, 0x99, 0x3E,
			0x41, 0x4D, 0xC0, 0x4B, 0x84, 0x7B, 0xC3, 0x0B,
			0xF8, 0xF7, 0xB3, 0x15, 0x1A, 0xD6, 0x6C, 0xE4
		}; 
		
		const uint8_t SSL_Q[]__attribute__((aligned(2))) = {	
			0xDF, 0x44, 0x8B, 0xD1, 0x6D, 0x72, 0x23, 0xBF,
			0xFF, 0xC4, 0x6F, 0x33, 0xA1, 0x8E, 0xC1, 0x7B,
			0xDA, 0xE7, 0x49, 0xF4, 0x07, 0xDB, 0xB6, 0xAC,
			0x70, 0xA5, 0x38, 0xBF, 0x1E, 0xFA, 0x9F, 0xC6,
			0xB8, 0x25, 0x3E, 0x9A, 0x43, 0x84, 0xCC, 0x93,
			0x6C, 0x91, 0xFB, 0x61, 0x11, 0x2B, 0xC0, 0x53,
			0x9C, 0x01, 0x54, 0x28, 0x57, 0x2F, 0x19, 0xAF,
			0x41, 0x96, 0x3B, 0x2A, 0xDC, 0xBA, 0x92, 0xD6
		};	
		
		const uint8_t SSL_dP[]__attribute__((aligned(2))) = {	
			0xA1, 0x99, 0xFE, 0x1E, 0x6A, 0x08, 0x59, 0x4F,
			0x13, 0xFE, 0x7D, 0x81, 0xC9, 0x4A, 0x89, 0xF4,
			0xC2, 0x7C, 0x3F, 0xCE, 0x68, 0x64, 0xA6, 0xAF,
			0x99, 0x5F, 0xE8, 0xE6, 0x35, 0xC3, 0x96, 0xA8,
			0xAE, 0xE6, 0x5E, 0xEF, 0x62, 0xB5, 0x57, 0x5A,
			0xDA, 0x92, 0xF2, 0xEF, 0x8E, 0x0B, 0xF8, 0x44,
			0xB6, 0xFB, 0x8A, 0x7D, 0x9E, 0x7F, 0x5E, 0xDA,
			0x5C, 0x23, 0x8A, 0x71, 0xA3, 0xFA, 0xC3, 0xAA
		}; 
		
		const uint8_t SSL_dQ[]__attribute__((aligned(2))) = {	
			0xEB, 0x86, 0xCC, 0xEB, 0xE7, 0x5C, 0xEC, 0x0A,
			0x2F, 0xE5, 0xCD, 0xAE, 0x94, 0xB0, 0x5D, 0x59,
			0xCE, 0xE0, 0xF9, 0xF0, 0xBB, 0xB6, 0x44, 0xF7,
			0x80, 0x74, 0xCB, 0x6E, 0x5C, 0x49, 0x70, 0x8F,
			0x12, 0xCF, 0x47, 0xDE, 0xF9, 0xE9, 0x38, 0x86,
			0x55, 0x57, 0x37, 0xEE, 0x68, 0x7D, 0x0A, 0xD7,
			0xF8, 0xB0, 0x74, 0x2D, 0xB4, 0x4A, 0xE4, 0xCD,
			0x03, 0xB3, 0xFD, 0x42, 0x1E, 0x90, 0xBB, 0x4B
		}; 
		
		const uint8_t SSL_qInv[]__attribute__((aligned(2))) = {	
			0xE3, 0x65, 0xCD, 0x09, 0x56, 0x40, 0x99, 0x3B,
			0xE3, 0xE4, 0x15, 0xAC, 0xBF, 0xDE, 0xBD, 0x64,
			0xA2, 0xF9, 0xB1, 0xE1, 0x58, 0xF9, 0x75, 0x4C,
			0xBA, 0x63, 0x61, 0xB8, 0x90, 0x4A, 0xBB, 0x10,
			0x56, 0xA6, 0x47, 0xF0, 0x16, 0x95, 0x47, 0x4E,
			0x26, 0x5B, 0x76, 0xB0, 0x5E, 0xDE, 0x7B, 0x2F,
			0x6E, 0xC6, 0x70, 0x17, 0xDD, 0xEA, 0x03, 0xCE,
			0x92, 0xF2, 0x21, 0x5D, 0x93, 0x5A, 0xC6, 0xA9
		};
	#elif SSL_RSA_KEY_SIZE == 2048u
		const uint8_t SSL_P[]__attribute__((aligned(2))) = {	
            0x73, 0x8A, 0x2E, 0xA7, 0x13, 0xB5, 0xB2, 0xC2, 
            0xAC, 0x1E, 0xAA, 0xA3, 0xF4, 0xC8, 0xE3, 0x5B, 
            0xD9, 0xCF, 0xE0, 0x6A, 0x9E, 0x13, 0x6A, 0x84, 
            0xD7, 0x08, 0x0B, 0xD7, 0x0F, 0xF1, 0x4A, 0x30, 
            0xC0, 0x90, 0x13, 0x05, 0xC2, 0x1E, 0x0D, 0x9B, 
            0xF3, 0xF8, 0x64, 0xBB, 0xC2, 0x88, 0x7B, 0x43, 
            0xDA, 0x87, 0xBD, 0x50, 0x47, 0x5A, 0x2E, 0x43, 
            0x2B, 0xDD, 0x37, 0x4D, 0x0C, 0xF9, 0x56, 0xB1, 
            0x7F, 0x07, 0x5B, 0x34, 0xE6, 0xE4, 0x7D, 0x97, 
            0x96, 0xAF, 0x8D, 0xE2, 0x0E, 0xAB, 0xC6, 0x4F, 
            0x57, 0x90, 0x7E, 0x1D, 0x4A, 0x07, 0x68, 0xC4, 
            0x93, 0xF0, 0x14, 0x0A, 0x19, 0xCE, 0x79, 0x90, 
            0x91, 0x06, 0xB2, 0x0B, 0xA5, 0xC4, 0xE0, 0x55, 
            0x51, 0x80, 0x57, 0x53, 0x33, 0xE3, 0xB3, 0xCA, 
            0x51, 0x24, 0xD3, 0xC9, 0xEC, 0xFD, 0xCF, 0xCF, 
            0xDD, 0x0F, 0x0B, 0xA7, 0x3B, 0xB1, 0x9F, 0xE7
        };

 		const uint8_t SSL_Q[]__attribute__((aligned(2))) = {	
            0x9D, 0x2F, 0xAE, 0x81, 0xC3, 0xD2, 0xE6, 0x85, 
            0x53, 0xFE, 0xEE, 0x91, 0x23, 0x53, 0xCB, 0xF5, 
            0x90, 0x0C, 0x08, 0x75, 0xA9, 0xEE, 0x78, 0x5E, 
            0x23, 0x3C, 0xD8, 0x4C, 0xF0, 0x8A, 0x93, 0x9C, 
            0xE4, 0x95, 0x2E, 0x0A, 0xD7, 0xB4, 0xAB, 0xEB, 
            0xC3, 0x45, 0xD2, 0x32, 0x33, 0x7C, 0x9E, 0x7E, 
            0xC7, 0xB1, 0xDA, 0x61, 0x01, 0x7B, 0xE9, 0x54, 
            0xC8, 0x86, 0xDA, 0x27, 0x6D, 0xFB, 0x67, 0x30, 
            0xFA, 0x8D, 0x87, 0x49, 0x06, 0x81, 0xF8, 0x46, 
            0x3E, 0xE0, 0x50, 0xEE, 0xA6, 0x11, 0x7F, 0xAC, 
            0x7E, 0x96, 0x79, 0xAE, 0x00, 0xC3, 0x47, 0xF8, 
            0x8F, 0x98, 0x2F, 0xF9, 0x68, 0x80, 0x63, 0x3A, 
            0x18, 0xFC, 0x70, 0x6D, 0x8D, 0x94, 0xE8, 0xE9, 
            0x38, 0xDC, 0x53, 0xCA, 0xC9, 0xA6, 0xC5, 0x72, 
            0x1B, 0x31, 0x93, 0x78, 0x0C, 0x08, 0x15, 0xEA, 
            0x17, 0xEC, 0xC9, 0x47, 0x22, 0x5D, 0xC2, 0xDA
	    };

 		const uint8_t SSL_dP[]__attribute__((aligned(2))) = {	
            0x21, 0xA0, 0x30, 0x23, 0x26, 0xEA, 0xD0, 0xF8, 
            0xB8, 0x72, 0xCF, 0x77, 0x01, 0xA1, 0xF5, 0x5E, 
            0xB5, 0xBB, 0x9D, 0x18, 0x03, 0x8E, 0xD2, 0xBE, 
            0x44, 0xCE, 0xAC, 0xCF, 0x65, 0xA5, 0xAF, 0x17, 
            0xAD, 0x7E, 0xFC, 0x7A, 0x97, 0x96, 0xB3, 0x1B, 
            0xFF, 0x14, 0xA2, 0xAD, 0xDF, 0xA3, 0x47, 0x69, 
            0x8A, 0xFC, 0xF0, 0x44, 0xD2, 0xE9, 0x3E, 0x6F, 
            0xDF, 0xD3, 0x12, 0x7D, 0x69, 0x5D, 0x6D, 0x7D, 
            0x92, 0x75, 0x31, 0xA4, 0x1B, 0x8B, 0xFE, 0xD3, 
            0x44, 0xB5, 0x11, 0xB4, 0x89, 0x8A, 0xE3, 0x2A, 
            0x07, 0x6C, 0x76, 0xE9, 0x08, 0x0A, 0xDC, 0x76, 
            0x1D, 0x28, 0x2B, 0xD6, 0xBC, 0x00, 0x1D, 0xD8, 
            0x2E, 0x38, 0xB4, 0x21, 0x5E, 0xE5, 0x20, 0x15, 
            0xC4, 0x43, 0xBB, 0x2D, 0x10, 0x88, 0xEC, 0xE3, 
            0x72, 0x1B, 0x19, 0x2B, 0xB1, 0xDA, 0x7C, 0x08, 
            0x1E, 0xFA, 0xFC, 0xA9, 0xBA, 0x39, 0x2D, 0xCB
	    };

		const uint8_t SSL_dQ[]__attribute__((aligned(2))) = {	
            0xE1, 0xEB, 0x9D, 0x9F, 0xE1, 0x38, 0x41, 0xC4, 
            0x08, 0x36, 0xAC, 0xA6, 0xCB, 0x91, 0xB8, 0x82, 
            0xF0, 0x30, 0x27, 0x2D, 0x2A, 0x94, 0x90, 0xD6, 
            0x2A, 0xDA, 0xF8, 0xA4, 0x06, 0xA6, 0xCD, 0x57, 
            0x33, 0x78, 0x92, 0x96, 0x02, 0xCB, 0x61, 0xCE, 
            0x86, 0x82, 0xDE, 0xD9, 0x03, 0xAE, 0x66, 0x38, 
            0x49, 0x90, 0x63, 0x97, 0xD0, 0x6C, 0x54, 0x98, 
            0xE2, 0x59, 0xA4, 0x70, 0x33, 0x88, 0xA6, 0xC3, 
            0x76, 0x65, 0xEB, 0x95, 0x40, 0x9E, 0xF3, 0x0E, 
            0x30, 0xFC, 0xE1, 0xAE, 0xAD, 0x24, 0x70, 0x16, 
            0xBF, 0xD5, 0x4D, 0x48, 0x0C, 0xC5, 0x8C, 0xEC, 
            0x96, 0xD9, 0x47, 0xBC, 0x2A, 0x5D, 0xF1, 0x5F, 
            0xA9, 0xE8, 0xEC, 0x4B, 0x32, 0x93, 0x7A, 0x13, 
            0xCC, 0x33, 0xE3, 0x40, 0x83, 0x23, 0xE5, 0x5C, 
            0xCB, 0xCF, 0x90, 0xF2, 0xAD, 0x1D, 0xB0, 0x20, 
            0x5C, 0x8F, 0x5D, 0x27, 0x26, 0x7C, 0xE4, 0x42
    	};

 		const uint8_t SSL_qInv[]__attribute__((aligned(2))) = {	
            0x9C, 0x98, 0xDF, 0x31, 0x54, 0x12, 0x06, 0xD7, 
            0x5E, 0xF9, 0x93, 0x83, 0x2F, 0xF5, 0xA3, 0x7F, 
            0xEB, 0x03, 0x16, 0x63, 0xFC, 0x7A, 0x6F, 0x2D, 
            0xFE, 0x77, 0x46, 0xE7, 0x31, 0xF5, 0x61, 0xF0, 
            0x90, 0x02, 0xEA, 0xF3, 0x4D, 0xF1, 0x27, 0x9E, 
            0x28, 0x9D, 0x0A, 0xE9, 0x55, 0xCF, 0x0D, 0x44, 
            0x4B, 0x18, 0x30, 0x5A, 0x45, 0xE3, 0xEB, 0x26, 
            0x9A, 0x57, 0xEE, 0x14, 0x8D, 0xB6, 0x5E, 0x95, 
            0x9D, 0x3A, 0x67, 0xAB, 0x75, 0xEA, 0x17, 0xC7, 
            0x24, 0x2B, 0x82, 0xE3, 0xE6, 0xB5, 0x05, 0x94, 
            0xA5, 0x9A, 0xA6, 0x77, 0xC7, 0xBA, 0x37, 0x18, 
            0x0C, 0x18, 0x43, 0xE3, 0xFE, 0xF9, 0x17, 0xF9, 
            0x9D, 0xDB, 0xC0, 0x24, 0x03, 0x9C, 0x16, 0x52, 
            0xBA, 0x2B, 0xA3, 0xB8, 0x64, 0x91, 0x28, 0xF3, 
            0xFA, 0xD9, 0xE4, 0x1E, 0xE5, 0x69, 0x98, 0x01, 
            0xB8, 0xFF, 0x15, 0xDD, 0x26, 0x85, 0xD2, 0x1B
    	};
	
	#endif
#endif



#if SSL_RSA_KEY_SIZE == 512u
		const uint8_t SSL_CERT[]__attribute__((aligned(2))) = {	
		0x30, 0x82, 0x02, 0x08, 0x30, 0x82, 0x01, 0xB2, 0x02, 0x09, 0x00, 0xA5, 0x6A, 0xEA, 0x1A, 0xA9,
		0x52, 0x9D, 0x1E, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05,
		0x05, 0x00, 0x30, 0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
		0x55, 0x53, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69,
		0x7A, 0x6F, 0x6E, 0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43,
		0x68, 0x61, 0x6E, 0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A,
		0x13, 0x1A, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68,
		0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B,
		0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20,
		0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06,
		0x03, 0x55, 0x04, 0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30,
		0x1E, 0x17, 0x0D, 0x30, 0x37, 0x31, 0x30, 0x30, 0x39, 0x31, 0x38, 0x33, 0x37, 0x32, 0x37, 0x5A,
		0x17, 0x0D, 0x31, 0x37, 0x31, 0x30, 0x30, 0x36, 0x31, 0x38, 0x33, 0x37, 0x32, 0x37, 0x5A, 0x30,
		0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
		0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69, 0x7A, 0x6F, 0x6E,
		0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43, 0x68, 0x61, 0x6E,
		0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x1A, 0x4D,
		0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68, 0x6E, 0x6F, 0x6C,
		0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B, 0x06, 0x03, 0x55,
		0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20, 0x43, 0x65, 0x72,
		0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04,
		0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30, 0x5C, 0x30, 0x0D,
		0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x4B, 0x00,
		0x30, 0x48, 0x02, 0x41, 0x00, 0xAA, 0x96, 0xCA, 0x97, 0xEA, 0x27, 0xB0, 0xD7, 0xE9, 0x21, 0xD0,
		0x40, 0xD4, 0x2C, 0x09, 0x5A, 0x2E, 0x3A, 0xE4, 0x12, 0x64, 0x2D, 0x4B, 0x1B, 0x92, 0xDF, 0x79,
		0x68, 0x4E, 0x3C, 0x51, 0xF4, 0x43, 0x48, 0x0D, 0xF2, 0xC8, 0x50, 0x9B, 0x6E, 0xE5, 0xEA, 0xFE,
		0xEF, 0xD9, 0x10, 0x41, 0x08, 0x14, 0xF9, 0x85, 0x49, 0xFC, 0x50, 0xD3, 0x57, 0x34, 0xDC, 0x3A,
		0x0D, 0x79, 0xF8, 0xD3, 0x99, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86,
		0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x41, 0x00, 0x18, 0x18, 0xFE, 0x8B,
		0x2D, 0x0D, 0xF7, 0x0D, 0x65, 0x9D, 0x29, 0xEC, 0xB3, 0x51, 0x6E, 0x3B, 0x93, 0xBB, 0x40, 0x1A,
		0x0B, 0x34, 0x07, 0x63, 0x5E, 0x6A, 0x1C, 0x74, 0x59, 0xD4, 0x54, 0xD2, 0x1B, 0xF3, 0x31, 0xB7,
		0x57, 0x4B, 0xA5, 0xE6, 0xE2, 0x35, 0xF7, 0xB3, 0x6A, 0x15, 0x6E, 0x3C, 0x93, 0x85, 0xB2, 0xCA,
		0xF5, 0x35, 0x00, 0xF4, 0x49, 0xE7, 0x00, 0x8A, 0x00, 0xD8, 0xE8, 0xCF
	};
	
#elif SSL_RSA_KEY_SIZE == 768u
		const uint8_t SSL_CERT[]__attribute__((aligned(2))) = {	
		0x30, 0x82, 0x02, 0x48, 0x30, 0x82, 0x01, 0xD2, 0x02, 0x09, 0x00, 0xB3, 0xDA, 0x4B, 0x55, 0xEE,
		0x4C, 0x8C, 0x27, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05,
		0x05, 0x00, 0x30, 0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
		0x55, 0x53, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69,
		0x7A, 0x6F, 0x6E, 0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43,
		0x68, 0x61, 0x6E, 0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A,
		0x13, 0x1A, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68,
		0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B,
		0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20,
		0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06,
		0x03, 0x55, 0x04, 0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30,
		0x1E, 0x17, 0x0D, 0x30, 0x38, 0x30, 0x33, 0x32, 0x37, 0x31, 0x36, 0x35, 0x36, 0x35, 0x31, 0x5A,
		0x17, 0x0D, 0x31, 0x38, 0x30, 0x33, 0x32, 0x35, 0x31, 0x36, 0x35, 0x36, 0x35, 0x31, 0x5A, 0x30,
		0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
		0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69, 0x7A, 0x6F, 0x6E,
		0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43, 0x68, 0x61, 0x6E,
		0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x1A, 0x4D,
		0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68, 0x6E, 0x6F, 0x6C,
		0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B, 0x06, 0x03, 0x55,
		0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20, 0x43, 0x65, 0x72,
		0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04,
		0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30, 0x7C, 0x30, 0x0D,
		0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x6B, 0x00,
		0x30, 0x68, 0x02, 0x61, 0x00, 0xE7, 0x9B, 0x59, 0xE0, 0xE3, 0xA9, 0xBC, 0xBD, 0xE4, 0x66, 0xF0,
		0x3B, 0x47, 0x8A, 0x28, 0x88, 0xA3, 0xE6, 0x10, 0x1E, 0xBD, 0x21, 0x8E, 0x4F, 0xFA, 0xA1, 0xA8,
		0x9F, 0x27, 0x19, 0xE9, 0x3D, 0x0F, 0x0C, 0x9C, 0xC6, 0x4E, 0xEE, 0x3B, 0x2A, 0xDF, 0x5A, 0x5D,
		0x96, 0xAE, 0x38, 0x92, 0x6D, 0xAF, 0xFE, 0x9F, 0xB6, 0x9F, 0x95, 0xB6, 0xFF, 0xEF, 0xB5, 0xAB,
		0x1A, 0x8D, 0xAD, 0xE1, 0x14, 0xF3, 0xC5, 0xF4, 0x35, 0xAC, 0x6F, 0x46, 0x9A, 0xE5, 0xE0, 0x26,
		0xC9, 0xF8, 0x04, 0xF8, 0x8F, 0xD5, 0x58, 0x8D, 0x25, 0x4A, 0x6B, 0x55, 0x78, 0x92, 0x0A, 0x6A,
		0xA4, 0x87, 0xA4, 0x63, 0x29, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86,
		0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x61, 0x00, 0x69, 0xC0, 0x64, 0xB3,
		0x44, 0xC1, 0xAE, 0xA2, 0xE4, 0x5B, 0xC3, 0x01, 0xC6, 0x1F, 0x05, 0xD2, 0x97, 0x07, 0x0E, 0x43,
		0xF3, 0x22, 0x07, 0x00, 0xE6, 0x58, 0x0B, 0xA0, 0x46, 0x57, 0x17, 0x85, 0xD8, 0x8B, 0x55, 0x86,
		0x2B, 0xA8, 0xBA, 0xC5, 0x0E, 0xA0, 0x05, 0xC6, 0xBE, 0xDA, 0x66, 0xD5, 0x77, 0x22, 0x75, 0xDE,
		0xFD, 0x1B, 0x0F, 0xD2, 0x47, 0x63, 0x90, 0xE9, 0x3C, 0xAD, 0xA3, 0x85, 0x30, 0xF9, 0x8B, 0xE4,
		0x9D, 0x34, 0x33, 0xBC, 0xD6, 0xC6, 0x26, 0xD1, 0x2D, 0xCE, 0x8F, 0x35, 0xBD, 0xB8, 0xD6, 0x4F,
		0x73, 0xF6, 0x18, 0x02, 0x20, 0x77, 0x52, 0xBE, 0x22, 0x9B, 0x2F, 0x6B
	};
	
#elif SSL_RSA_KEY_SIZE == 1024u
		const uint8_t SSL_CERT[]__attribute__((aligned(2))) = {	
		0x30, 0x82, 0x02, 0x8D, 0x30, 0x82, 0x01, 0xF6, 0x02, 0x09, 0x00, 0xFB, 0x11, 0x3A, 0x83, 0xD7,
		0x60, 0xE3, 0x6D, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05,
		0x05, 0x00, 0x30, 0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
		0x55, 0x53, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69,
		0x7A, 0x6F, 0x6E, 0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43,
		0x68, 0x61, 0x6E, 0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A,
		0x13, 0x1A, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68,
		0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B,
		0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20,
		0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06,
		0x03, 0x55, 0x04, 0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30,
		0x1E, 0x17, 0x0D, 0x30, 0x38, 0x30, 0x33, 0x32, 0x37, 0x31, 0x36, 0x35, 0x36, 0x33, 0x36, 0x5A,
		0x17, 0x0D, 0x31, 0x38, 0x30, 0x33, 0x32, 0x35, 0x31, 0x36, 0x35, 0x36, 0x33, 0x36, 0x5A, 0x30,
		0x81, 0x8A, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31,
		0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69, 0x7A, 0x6F, 0x6E,
		0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43, 0x68, 0x61, 0x6E,
		0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x1A, 0x4D,
		0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68, 0x6E, 0x6F, 0x6C,
		0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1D, 0x30, 0x1B, 0x06, 0x03, 0x55,
		0x04, 0x0B, 0x13, 0x14, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20, 0x43, 0x65, 0x72,
		0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04,
		0x03, 0x13, 0x09, 0x6D, 0x63, 0x68, 0x70, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x30, 0x81, 0x9F, 0x30,
		0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81,
		0x8D, 0x00, 0x30, 0x81, 0x89, 0x02, 0x81, 0x81, 0x00, 0xBF, 0x75, 0xE7, 0xC7, 0x6F, 0xCA, 0xCA,
		0x64, 0x2F, 0x04, 0x7C, 0x2D, 0x78, 0x41, 0xF6, 0xB5, 0x8D, 0xA4, 0xA9, 0x24, 0x51, 0x08, 0x80,
		0xF1, 0x6C, 0xAE, 0xBD, 0xCA, 0x81, 0xE3, 0x00, 0x82, 0x7B, 0xB1, 0x90, 0x61, 0x74, 0xE2, 0x0E,
		0x86, 0xFE, 0x45, 0xAE, 0xCA, 0x9D, 0xAE, 0x71, 0x2D, 0x72, 0x65, 0x52, 0xBA, 0x0C, 0x51, 0x2F,
		0xE6, 0xFD, 0x95, 0x59, 0xC1, 0x60, 0x10, 0x2F, 0x93, 0x4E, 0x99, 0xDD, 0x8A, 0xAD, 0xC1, 0xCE,
		0x1C, 0xD1, 0x1D, 0xD4, 0xBF, 0x33, 0x25, 0x8A, 0x6A, 0xCA, 0xC4, 0xD2, 0xC0, 0x68, 0x10, 0x77,
		0xC4, 0xD0, 0x25, 0x42, 0x13, 0xCE, 0x17, 0xFD, 0x59, 0xDB, 0xE0, 0x4C, 0x70, 0x39, 0x2C, 0xBD,
		0x9A, 0xD6, 0x83, 0x4B, 0x56, 0x11, 0xED, 0x6A, 0xE8, 0x60, 0xA3, 0x3D, 0x9E, 0xEB, 0xC6, 0xE9,
		0x18, 0xB9, 0x9D, 0xE3, 0x94, 0xBB, 0x85, 0x7D, 0x0F, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x0D,
		0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x81, 0x81,
		0x00, 0x5C, 0x82, 0xB0, 0xFA, 0xC7, 0xBC, 0x25, 0xAE, 0x8C, 0x81, 0x9C, 0x65, 0x71, 0x67, 0x55,
		0x1E, 0x05, 0x5F, 0x3F, 0xEA, 0x96, 0x4E, 0xA8, 0xF0, 0xCE, 0x42, 0xAD, 0xB7, 0xD5, 0xC3, 0x07,
		0x93, 0x54, 0x5B, 0x4E, 0x65, 0xAD, 0x8E, 0xCD, 0x4D, 0x78, 0x15, 0x54, 0x18, 0x8D, 0x52, 0x6E,
		0x2C, 0xF0, 0x84, 0x64, 0x1D, 0x70, 0x5D, 0x93, 0x06, 0x08, 0xBC, 0xBE, 0xB6, 0xCF, 0x42, 0x9A,
		0xD2, 0x9B, 0x04, 0xE2, 0xD7, 0xD5, 0x69, 0x25, 0x0F, 0xED, 0xA0, 0xE4, 0x14, 0xBA, 0xBC, 0xEE,
		0xE9, 0x42, 0xCD, 0xCB, 0xD0, 0xCD, 0x85, 0xAE, 0x59, 0x9A, 0xD9, 0x8C, 0xAE, 0x8C, 0xE7, 0x61,
		0xA8, 0xB1, 0xD3, 0xFC, 0xE1, 0x5E, 0xD6, 0x0E, 0x2A, 0x73, 0x26, 0x08, 0x02, 0xC2, 0x18, 0xF7,
		0x74, 0x76, 0x5B, 0x24, 0x3C, 0x54, 0xC0, 0x64, 0x11, 0x87, 0x5B, 0x05, 0xE7, 0xD0, 0x03, 0x87,
		0x3D
	};

#elif SSL_RSA_KEY_SIZE == 2048u
		const uint8_t SSL_CERT[]__attribute__((aligned(4))) = {	
        0x30, 0x82, 0x03, 0xD6, 0x30, 0x82, 0x02, 0xBE, 0x02, 0x09, 0x00, 0xCF, 0x70, 0x0E, 0xAF, 0xAC, 
        0xDF, 0x27, 0x09, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 
        0x05, 0x00, 0x30, 0x81, 0xAC, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 
        0x55, 0x53, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69, 
        0x7A, 0x6F, 0x6E, 0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43, 
        0x68, 0x61, 0x6E, 0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A, 
        0x13, 0x1A, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68, 
        0x6E, 0x6F, 0x6C, 0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x0C, 0x30, 0x0A, 
        0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x03, 0x57, 0x50, 0x44, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 
        0x55, 0x04, 0x03, 0x13, 0x19, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20, 0x43, 0x65, 
        0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x20, 0x32, 0x30, 0x34, 0x38, 0x31, 0x21, 
        0x30, 0x1F, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x01, 0x16, 0x12, 0x69, 
        0x6E, 0x66, 0x6F, 0x40, 0x6D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x2E, 0x63, 0x6F, 
        0x6D, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x31, 0x31, 0x30, 0x30, 0x32, 0x31, 0x30, 0x35, 0x36, 0x32, 
        0x39, 0x5A, 0x17, 0x0D, 0x31, 0x32, 0x31, 0x30, 0x30, 0x31, 0x31, 0x30, 0x35, 0x36, 0x32, 0x39, 
        0x5A, 0x30, 0x81, 0xAC, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 
        0x53, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x13, 0x07, 0x41, 0x72, 0x69, 0x7A, 
        0x6F, 0x6E, 0x61, 0x31, 0x11, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x04, 0x07, 0x13, 0x08, 0x43, 0x68, 
        0x61, 0x6E, 0x64, 0x6C, 0x65, 0x72, 0x31, 0x23, 0x30, 0x21, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 
        0x1A, 0x4D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x20, 0x54, 0x65, 0x63, 0x68, 0x6E, 
        0x6F, 0x6C, 0x6F, 0x67, 0x79, 0x2C, 0x20, 0x49, 0x6E, 0x63, 0x2E, 0x31, 0x0C, 0x30, 0x0A, 0x06, 
        0x03, 0x55, 0x04, 0x0B, 0x13, 0x03, 0x57, 0x50, 0x44, 0x31, 0x22, 0x30, 0x20, 0x06, 0x03, 0x55, 
        0x04, 0x03, 0x13, 0x19, 0x53, 0x53, 0x4C, 0x20, 0x44, 0x65, 0x6D, 0x6F, 0x20, 0x43, 0x65, 0x72, 
        0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x20, 0x32, 0x30, 0x34, 0x38, 0x31, 0x21, 0x30, 
        0x1F, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x01, 0x16, 0x12, 0x69, 0x6E, 
        0x66, 0x6F, 0x40, 0x6D, 0x69, 0x63, 0x72, 0x6F, 0x63, 0x68, 0x69, 0x70, 0x2E, 0x63, 0x6F, 0x6D, 
        0x30, 0x82, 0x01, 0x22, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 
        0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0F, 0x00, 0x30, 0x82, 0x01, 0x0A, 0x02, 0x82, 0x01, 0x01, 
        0x00, 0xC5, 0xED, 0xD8, 0x35, 0x23, 0x00, 0x33, 0xA6, 0xAA, 0xFB, 0x6C, 0xA0, 0xBF, 0x4A, 0x44, 
        0x92, 0x7F, 0xD3, 0x75, 0x4F, 0x8A, 0x6B, 0x33, 0x4D, 0xEF, 0x66, 0x51, 0x2D, 0xF2, 0xD0, 0xB2, 
        0x85, 0xF0, 0x24, 0xB7, 0x86, 0x96, 0x66, 0xE6, 0x9A, 0x91, 0x61, 0x97, 0x11, 0x3A, 0x4A, 0x78, 
        0x3A, 0x71, 0xB8, 0x5F, 0x69, 0x47, 0xA6, 0x1B, 0x17, 0x4F, 0xDE, 0x37, 0x9C, 0x12, 0xB7, 0xD6, 
        0x72, 0x11, 0xCD, 0x94, 0x2B, 0x39, 0xC5, 0x92, 0x9D, 0x4B, 0x6B, 0x6C, 0x69, 0x30, 0x99, 0x9E, 
        0xCC, 0x85, 0x80, 0x5F, 0x68, 0x83, 0x41, 0x86, 0xA4, 0x2B, 0x9A, 0xEB, 0x95, 0xE0, 0x25, 0xAE, 
        0x3D, 0x9F, 0x76, 0x9B, 0x98, 0x47, 0x82, 0x85, 0x84, 0x78, 0x79, 0x0B, 0x5F, 0x7B, 0x0C, 0x31, 
        0x6D, 0x65, 0x8B, 0xFA, 0x65, 0x65, 0x62, 0x79, 0x22, 0x01, 0xAD, 0x96, 0x01, 0x84, 0x0C, 0x8B, 
        0x2D, 0xF2, 0x7C, 0x92, 0xB0, 0x08, 0xE6, 0x48, 0xD6, 0xA7, 0x57, 0xD8, 0x2D, 0x89, 0x20, 0xF6, 
        0x49, 0x3F, 0xEA, 0xEF, 0xB7, 0x88, 0x31, 0x26, 0x4F, 0x1F, 0x96, 0xF0, 0xA1, 0x8B, 0x56, 0xD1, 
        0x2A, 0x11, 0x32, 0x7C, 0xC0, 0xBA, 0xC5, 0x73, 0xFC, 0x94, 0x6B, 0xB9, 0x05, 0x6C, 0xFA, 0x6D, 
        0xF1, 0x93, 0x34, 0x41, 0xE1, 0x7A, 0x13, 0xB3, 0xC9, 0x40, 0xD1, 0x2D, 0xE2, 0x85, 0xFD, 0x64, 
        0x6D, 0x97, 0xEC, 0xFB, 0xB8, 0x08, 0x53, 0x09, 0x11, 0xC3, 0x44, 0x29, 0x5A, 0x2E, 0x96, 0xC4, 
        0xA6, 0x24, 0xB5, 0x00, 0x99, 0xD1, 0x3F, 0x70, 0x2C, 0xAA, 0x2A, 0xEC, 0xE7, 0x2A, 0xC9, 0x5C, 
        0xA6, 0x72, 0x33, 0x35, 0x02, 0xB7, 0xC7, 0x4C, 0x33, 0x03, 0x3D, 0x2B, 0xD6, 0x66, 0xB7, 0xE2, 
        0x84, 0x45, 0x76, 0x2E, 0xC3, 0x8A, 0x0B, 0x56, 0x8B, 0xD9, 0xC9, 0x89, 0xBE, 0x20, 0x20, 0x05, 
        0x87, 0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 
        0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x13, 0xAF, 0xCD, 0x5A, 0xF8, 0xAE, 
        0xA1, 0x32, 0x1E, 0x38, 0xF1, 0xB6, 0xAC, 0x1B, 0x77, 0x9B, 0x46, 0x74, 0x3F, 0xBF, 0x71, 0x16, 
        0x9B, 0x87, 0x16, 0x10, 0x1D, 0xF1, 0xC5, 0xFC, 0xA5, 0x53, 0x0C, 0x9C, 0x5F, 0x58, 0x03, 0x30, 
        0x68, 0xAD, 0x7F, 0x7C, 0xC0, 0x68, 0x44, 0xDB, 0x9B, 0xF7, 0xC8, 0xFE, 0x20, 0x0F, 0xF9, 0x42, 
        0xF1, 0xC8, 0xB1, 0x8E, 0xAA, 0xE4, 0xE6, 0xD6, 0x16, 0x2C, 0x66, 0x9D, 0x97, 0xDE, 0x34, 0x4C, 
        0xBA, 0xA7, 0x61, 0x11, 0x5F, 0xB3, 0x8F, 0x48, 0x92, 0x74, 0xD5, 0x52, 0x2B, 0xDF, 0x13, 0xE2, 
        0xFA, 0x7D, 0xAE, 0x60, 0xA3, 0x56, 0x27, 0x2B, 0xF2, 0x54, 0x79, 0x0C, 0x75, 0x3C, 0x40, 0xFE, 
        0xF3, 0x45, 0xD0, 0x23, 0x92, 0xA3, 0x7C, 0x64, 0x37, 0xD9, 0x17, 0xD9, 0x77, 0x11, 0x60, 0xDD, 
        0x18, 0xBA, 0xE4, 0xD6, 0x63, 0x77, 0xD5, 0x1B, 0x3B, 0x1A, 0x07, 0x29, 0xEB, 0x77, 0x45, 0xCB, 
        0x08, 0x7E, 0xF6, 0x67, 0xA1, 0xB7, 0x0C, 0x03, 0xEE, 0x07, 0xB6, 0x8E, 0x18, 0xD4, 0xC1, 0x36, 
        0xF5, 0xA7, 0xFE, 0x99, 0x48, 0xC4, 0x90, 0x7F, 0x73, 0x7D, 0x85, 0x31, 0x4E, 0xB1, 0x27, 0x1C, 
        0x5A, 0xB9, 0x22, 0x94, 0xF4, 0xEE, 0x79, 0x78, 0x72, 0xCA, 0x40, 0x65, 0x04, 0xD7, 0x27, 0x72, 
        0xEE, 0xF6, 0xDD, 0x94, 0x0D, 0x41, 0x3C, 0x61, 0x8C, 0xF1, 0x29, 0xB5, 0xDF, 0xE8, 0xC9, 0x01, 
        0x17, 0x2C, 0xD6, 0x25, 0xB9, 0xE9, 0x10, 0x30, 0x8A, 0xE0, 0x72, 0x32, 0xFC, 0x17, 0x12, 0x89, 
        0xFA, 0xB7, 0x70, 0x05, 0xF4, 0x48, 0x89, 0x21, 0xD1, 0x8A, 0x58, 0x64, 0x7F, 0x3E, 0x57, 0xBA, 
        0xB2, 0x48, 0x41, 0x25, 0xE9, 0x2C, 0x47, 0xB5, 0xF3, 0xBA, 0x27, 0x3A, 0x97, 0x06, 0x9B, 0x55, 
        0xB8, 0x29, 0x68, 0x20, 0x30, 0x1D, 0x87, 0x7C, 0x8A, 0x19
	};


#endif


// Number of bytes in the SSL_CERT[] array.  This length is used in other 
// .c files, which is why it has to be stored as a const constant instead of 
// a compiler constant.
const uint16_t SSL_CERT_LEN = sizeof(SSL_CERT);



#endif  // defined(TCPIP_STACK_USE_SSL_SERVER)

