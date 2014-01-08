#ifndef _OC_PROCESSOR_H
#define _OC_PROCESSOR_H

#if defined(__PIC16F__)
    #include "oc_pic_other.h"

#elif defined(__18CXX)
    #include "oc_pic18.h"

#elif defined(_PIC18)
    #include "oc_pic18.h"

#elif defined(__PIC24F__)
    #include "oc_p24fxxxx.h"

#elif defined(__PIC24H__)
    #include "oc_p24hxxxx.h"

#elif defined(__dsPIC30F__)
    #include "oc_p30fxxxx.h"

#elif defined(__dsPIC33E__)
    #include "oc_p33exxxx.h"

#elif defined(__dsPIC33F__)
    #include "oc_p33fxxxx.h"

#elif defined(__PIC32MX__)
    #include "oc_p32mxxxxx.h"

#elif defined(__PIC32MZ__)
    #include "oc_p32mzxxxx.h"

#else
    #error "Can't find header"

#endif

#endif//_OC_PROCESSOR_H
