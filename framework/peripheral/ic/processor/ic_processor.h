#ifndef _IC_PROCESSOR_H
#define _IC_PROCESSOR_H

#if defined(__PIC16F__)
    #include "ic_pic_other.h"

#elif defined(__18CXX)
    #include "ic_pic18.h"

#elif defined(_PIC18)
    #include "ic_pic18.h"

#elif defined(__PIC24F__)
    #include "ic_p24fxxxx.h"

#elif defined(__PIC24H__)
    #include "ic_p24hxxxx.h"

#elif defined(__dsPIC30F__)
    #include "ic_p30fxxxx.h"

#elif defined(__dsPIC33E__)
    #include "ic_p33exxxx.h"

#elif defined(__dsPIC33F__)
    #include "ic_p33fxxxx.h"

#elif defined(__PIC32MX__)
    #include "ic_p32mxxxxx.h"

#elif defined(__PIC32MZ__)
    #include "ic_p32mzxxxx.h"

#else
    #error "Can't find header"

#endif

#endif//_IC_PROCESSOR_H
