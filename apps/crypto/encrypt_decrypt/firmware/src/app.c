/*******************************************************************************
  MPLAB Harmony Application 
  
  File Name:
    app.c

  Summary:
    Application Template

  Description:
        Author: C15009
    
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#include <sys/endian.h>
#include <sys/kmem.h>
#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

const unsigned char vector[] = {/* "Now is the time for all " w/o trailing 0 */
    0x4e, 0x6f, 0x77, 0x20, 0x69, 0x73, 0x20, 0x74,
    0x68, 0x65, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x20,
    0x66, 0x6f, 0x72, 0x20, 0x61, 0x6c, 0x6c, 0x20
};

const unsigned char key3[] ={
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xde, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67
};
const unsigned char iv3[] ={
    0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef
};

const unsigned char verify3[] ={
    0x43, 0xa0, 0x29, 0x7e, 0xd1, 0x84, 0xf8, 0x0e,
    0x89, 0x64, 0x84, 0x32, 0x12, 0xd5, 0x08, 0x98,
    0x18, 0x94, 0x15, 0x74, 0x87, 0x12, 0x7d, 0xb0
};

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */
APP_DATA appData ={
    /* app state */
    .state = APP_STATE_INIT,

    /* test matches */
    .encryption_matched = false,
    .decryption_matched = false
};

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
 */

APP_DRV_OBJECTS appDrvObject;



// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************

void reverse_words(unsigned int *p, unsigned int num_words) {
    for (; num_words; num_words--, p++)
        *p = ntohl(*p);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(APP_DATA * appData) {
    // TODO initialize your application state machine and other parameters

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(APP_DATA * appData) {
    /* create an uncached pointer to make sure the crypto structures are stored */
#if defined(USE_CRYPTO_HW)
    APP_DATA * uappData = KVA0_TO_KVA1(appData);
#endif
    
    /* check the application state*/
    switch (appData->state) {
        case APP_STATE_INIT:
#if defined(USE_CRYPTO_HW)
            memset((void *) &uappData->sa, sizeof (securityAssociation), 0);
            memset((void *) &uappData->bd, sizeof (bufferDescriptor), 0);
#endif
            appData->state = APP_STATE_SETUP_ENCRYPTION;
            break;

        case APP_STATE_SETUP_ENCRYPTION:
#if defined(USE_CRYPTO_HW)
            /* Reset the Crypto engine */
            CECON = 1 << 6;

            /* Initialize the security association */
            uappData->sa.SA_CTRL.ALGO = 0b0000010; /* TDES */
            uappData->sa.SA_CTRL.LNC = 1;
            uappData->sa.SA_CTRL.LOADIV = 1;
            uappData->sa.SA_CTRL.FB = 1;
            uappData->sa.SA_CTRL.ENCTYPE = 1; /* Encryption */
            uappData->sa.SA_CTRL.CRYPTOALGO = 0b0101; /* TCBC */

            memcpy(&uappData->sa.SA_ENCKEY[2], key3, 24);
            memcpy(&uappData->sa.SA_ENCIV[2], iv3, 8);
            reverse_words(&uappData->sa.SA_ENCKEY[2], 24 / 4);
            reverse_words(&uappData->sa.SA_ENCIV[2], 2);

            /* Initialize the buffer descriptor */
            uappData->bd.BD_CTRL.BUFLEN = sizeof (vector);
            uappData->bd.BD_CTRL.LIFM = 1;
            uappData->bd.BD_CTRL.SA_FETCH_EN = 1;
            uappData->bd.BD_CTRL.LAST_BD = 1;
            uappData->bd.BD_CTRL.DESC_EN = 1;

            uappData->bd.SA_ADDR = KVA_TO_PA(&uappData->sa);
            uappData->bd.SRCADDR = KVA_TO_PA(vector);
            uappData->bd.DSTADDR = KVA_TO_PA(&uappData->cipher);
            uappData->bd.MSGLEN = sizeof (vector);
#else
            CRYPT_TDES_KeySet(&appData->tdes, key3, iv3, CRYPT_TDES_ENCRYPTION);
#endif

            appData->state = APP_STATE_START_ENCRYPTION;
            break;

#if defined(USE_CRYPTO_HW)
        case APP_STATE_START_ENCRYPTION:
        case APP_STATE_START_DECRYPTION:
            CEBDPADDR = KVA_TO_PA(&uappData->bd);
            CEINTEN = 0x07;
            CECON = 0x27;

            appData->state = appData->state == APP_STATE_START_ENCRYPTION ? APP_STATE_WAIT_FOR_ENCRYPTION : APP_STATE_WAIT_FOR_DECRYPTION;
            break;
#else
        case APP_STATE_START_ENCRYPTION:
            CRYPT_TDES_CBC_Encrypt(&appData->tdes, appData->cipher, vector, TDES_SIZE);
            appData->state = APP_STATE_SETUP_DECRYPTION;
            break;

        case APP_STATE_START_DECRYPTION:
            CRYPT_TDES_CBC_Decrypt(&appData->tdes, appData->plain, appData->cipher, TDES_SIZE);
            appData->state = APP_STATE_COMPARE_RESULTS;
            break;
#endif

        case APP_STATE_WAIT_FOR_DECRYPTION:
        case APP_STATE_WAIT_FOR_ENCRYPTION:
#if defined(USE_CRYPTO_HW)
            if (!CESTATbits.ACTIVE)
                appData->state = appData->state == APP_STATE_WAIT_FOR_ENCRYPTION ? APP_STATE_BYTE_REVERSE_ENCRYPTION : APP_STATE_BYTE_REVERSE_DECRYPTION;
#else
            appData->state = appData->state == APP_STATE_WAIT_FOR_ENCRYPTION ? APP_STATE_SETUP_DECRYPTION : APP_STATE_COMPARE_RESULTS;
#endif
            break;

        case APP_STATE_BYTE_REVERSE_ENCRYPTION:
#if defined(USE_CRYPTO_HW)
            reverse_words((unsigned int *)&uappData->cipher, 24 / 4);
#endif
            appData->state = APP_STATE_SETUP_DECRYPTION;
            break;

        case APP_STATE_SETUP_DECRYPTION:
#if defined(USE_CRYPTO_HW)
            /* Reset the Crypto Hardware */
            CECON = 1 << 6;

            /* Initialize the security association */
            uappData->sa.SA_CTRL.ALGO = 0b0000010; /* TDES */
            uappData->sa.SA_CTRL.LNC = 1;
            uappData->sa.SA_CTRL.LOADIV = 1;
            uappData->sa.SA_CTRL.FB = 1;
            uappData->sa.SA_CTRL.ENCTYPE = 0; /* Decryption */
            uappData->sa.SA_CTRL.CRYPTOALGO = 0b0101; /* TCBC */

            memcpy(&uappData->sa.SA_ENCKEY[2], key3, 24);
            memcpy(&uappData->sa.SA_ENCIV[2], iv3, 8);
            reverse_words(&uappData->sa.SA_ENCKEY[2], 24 / 4);
            reverse_words(&uappData->sa.SA_ENCIV[2], 2);

            /* Initialize the buffer descriptor */
            uappData->bd.BD_CTRL.BUFLEN = sizeof (vector);
            uappData->bd.BD_CTRL.LIFM = 1;
            uappData->bd.BD_CTRL.SA_FETCH_EN = 1;
            uappData->bd.BD_CTRL.LAST_BD = 1;
            uappData->bd.BD_CTRL.DESC_EN = 1;

            uappData->bd.SA_ADDR = KVA_TO_PA(&uappData->sa);
            uappData->bd.SRCADDR = KVA_TO_PA(&uappData->cipher);
            uappData->bd.DSTADDR = KVA_TO_PA(&uappData->plain) & 0x1FFFFFFF;
            uappData->bd.MSGLEN = sizeof (vector);
#else
            CRYPT_TDES_KeySet(&appData->tdes, key3, iv3, CRYPT_TDES_DECRYPTION);
#endif
            appData->state = APP_STATE_START_DECRYPTION;
            break;

        case APP_STATE_BYTE_REVERSE_DECRYPTION:
#if defined(USE_CRYPTO_HW)
            reverse_words((unsigned int *)&uappData->plain, 24 / 4);
#endif
            appData->state = APP_STATE_COMPARE_RESULTS;
            break;

        case APP_STATE_COMPARE_RESULTS:
#if defined(USE_CRYPTO_HW)
            appData->decryption_matched = memcmp(&uappData->plain, vector, sizeof(vector)) == 0;
            appData->encryption_matched = memcmp(&uappData->cipher, verify3, sizeof(verify3)) == 0;
#else
            appData->decryption_matched = memcmp(&appData->plain, vector, sizeof(vector)) == 0;
            appData->encryption_matched = memcmp(&appData->cipher, verify3, sizeof(verify3)) == 0;
#endif

            if (appData->decryption_matched && appData->encryption_matched)
            {
                BSP_SwitchONLED(LED_GRN);
            }
            else
            {
                BSP_SwitchONLED(LED_RED);
            }

            appData->state = APP_STATE_SPIN;
            break;

        case APP_STATE_SPIN:
        default:
            break;

    }

}


/*******************************************************************************
 End of File
 */

