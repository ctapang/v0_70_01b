/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    md2.c
  
  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic 
	Framework Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
File Name:  md2.c
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

#ifdef CYASSL_MD2

#include <md2.h>
#ifdef NO_INLINE
    #include <misc.h>
#else
    #include <src/misc.c>
#endif


void InitMd2(Md2* md2)
{
    XMEMSET(md2->X, 0, MD2_X_SIZE);
    XMEMSET(md2->C, 0, MD2_BLOCK_SIZE);
    XMEMSET(md2->buffer, 0, MD2_BLOCK_SIZE);
    md2->count = 0;
}


void Md2Update(Md2* md2, const byte* data, word32 len)
{
    static const byte S[256] = 
    {
        41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
        19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
        76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
        138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
        245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
        148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
        39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
        181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
        150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
        112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
        96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
        85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
        234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
        129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
        8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
        203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
        166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
        31, 26, 219, 153, 141, 51, 159, 17, 131, 20
    };

    while (len) {
        word32 L = (MD2_PAD_SIZE - md2->count) < len ?
                   (MD2_PAD_SIZE - md2->count) : len;
        XMEMCPY(md2->buffer + md2->count, data, L);
        md2->count += L;
        data += L;
        len  -= L;

        if (md2->count == MD2_PAD_SIZE) {
            int  i;
            byte t;

            md2->count = 0;
            XMEMCPY(md2->X + MD2_PAD_SIZE, md2->buffer, MD2_PAD_SIZE);
            t = md2->C[15];

            for(i = 0; i < MD2_PAD_SIZE; i++) {
                md2->X[32 + i] = md2->X[MD2_PAD_SIZE + i] ^ md2->X[i];
                t = md2->C[i] ^= S[md2->buffer[i] ^ t];
            }

            t=0;
            for(i = 0; i < 18; i++) {
                int j;
                for(j = 0; j < MD2_X_SIZE; j += 8) {
                    t = md2->X[j+0] ^= S[t];
                    t = md2->X[j+1] ^= S[t];
                    t = md2->X[j+2] ^= S[t];
                    t = md2->X[j+3] ^= S[t];
                    t = md2->X[j+4] ^= S[t];
                    t = md2->X[j+5] ^= S[t];
                    t = md2->X[j+6] ^= S[t];
                    t = md2->X[j+7] ^= S[t];
                }
                t = (t + i) & 0xFF;
            }
        }
    }
}


void Md2Final(Md2* md2, byte* hash)
{
    byte   padding[MD2_BLOCK_SIZE];
    word32 padLen = MD2_PAD_SIZE - md2->count;
    word32 i;

    for (i = 0; i < padLen; i++)
        padding[i] = (byte)padLen;

    Md2Update(md2, padding, padLen);
    Md2Update(md2, md2->C, MD2_BLOCK_SIZE);

    XMEMCPY(hash, md2->X, MD2_DIGEST_SIZE);

    InitMd2(md2);
}


#endif /* CYASSL_MD2 */
