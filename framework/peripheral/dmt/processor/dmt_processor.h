#ifndef _DMT_PROCESSOR_H
#define _DMT_PROCESSOR_H

#if defined(__PIC16F__)
    #include "dmt_pic_other.h"

#elif defined(__18CXX)
    #include "dmt_pic18.h"

#elif defined(_PIC18)
    #include "dmt_pic18.h"

#elif defined(__PIC24F__)
    #include "dmt_p24fxxxx.h"

#elif defined(__PIC24H__)
    #include "dmt_p24hxxxx.h"

#elif defined(__dsPIC30F__)
    #include "dmt_p30fxxxx.h"

#elif defined(__dsPIC33E__)
    #include "dmt_p33exxxx.h"

#elif defined(__dsPIC33F__)
    #include "dmt_p33fxxxx.h"

#elif defined(__PIC32MX__)
    #include "dmt_p32mxxxxx.h"

#elif defined(__PIC32MZ__)
    #include "dmt_p32mzxxxx.h"

#else
    #error "Can't find header"

#endif

#endif//_DMT_PROCESSOR_H
