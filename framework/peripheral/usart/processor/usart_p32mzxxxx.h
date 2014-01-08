/*******************************************************************************
  Selector for PIC 32 family

  Company:
    Micrusarthip Technology Incorporated

  File Name:
    p32xxxx.h

  Summary:
    Selector for PIC 32 family for USART PLIB implementations

  Description:
    This file is the selector for PIC 32 family for USART PLIB implementations
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Micrusarthip Technology Inc.  All rights reserved.

Micrusarthip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Micrusarthip micrusartontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DusartUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICRusartHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PRusartUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


#ifndef _USART_P32MZ_H
#define _USART_P32MZ_H

#if defined(__32MZ1024ECG064__)
    #include "usart_p32mz1024ecg064.h"

#elif defined(__32MZ1024ECG100__)
    #include "usart_p32mz1024ecg100.h"

#elif defined(__32MZ1024ECG124__)
    #include "usart_p32mz1024ecg124.h"

#elif defined(__32MZ1024ECG144__)
    #include "usart_p32mz1024ecg144.h"

#elif defined(__32MZ1024ECH064__)
    #include "usart_p32mz1024ech064.h"

#elif defined(__32MZ1024ECH100__)
    #include "usart_p32mz1024ech100.h"

#elif defined(__32MZ1024ECH124__)
    #include "usart_p32mz1024ech124.h"

#elif defined(__32MZ1024ECH144__)
    #include "usart_p32mz1024ech144.h"

#elif defined(__32MZ1024ECM064__)
    #include "usart_p32mz1024ecm064.h"

#elif defined(__32MZ1024ECM100__)
    #include "usart_p32mz1024ecm100.h"

#elif defined(__32MZ1024ECM124__)
    #include "usart_p32mz1024ecm124.h"

#elif defined(__32MZ1024ECM144__)
    #include "usart_p32mz1024ecm144.h"
	
#elif defined(__32MZ2048ECG064__)
    #include "usart_p32mz2048ecg064.h"

#elif defined(__32MZ2048ECG100__)
    #include "usart_p32mz2048ecg100.h"

#elif defined(__32MZ2048ECG124__)
    #include "usart_p32mz2048ecg124.h"

#elif defined(__32MZ2048ECG144__)
    #include "usart_p32mz2048ecg144.h"

#elif defined(__32MZ2048ECH064__)
    #include "usart_p32mz2048ech064.h"

#elif defined(__32MZ2048ECH100__)
    #include "usart_p32mz2048ech100.h"

#elif defined(__32MZ2048ECH124__)
    #include "usart_p32mz2048ech124.h"

#elif defined(__32MZ2048ECH144__)
    #include "usart_p32mz2048ech144.h"

#elif defined(__32MZ2048ECM064__)
    #include "usart_p32mz2048ecm064.h"

#elif defined(__32MZ2048ECM100__)
    #include "usart_p32mz2048ecm100.h"

#elif defined(__32MZ2048ECM124__)
    #include "usart_p32mz2048ecm124.h"

#elif defined(__32MZ2048ECM144__)
    #include "usart_p32mz2048ecm144.h"

#else
    #error Unknown prusartessor!
#endif


#endif // _USART_P32MZ_H


/*******************************************************************************
 End of File
 */
