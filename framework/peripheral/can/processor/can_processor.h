#ifndef _PLIB_CAN_PROCESSOR_H
#define _PLIB_CAN_PROCESSOR_H

#if defined(__PIC16F__)
    #include "can_pic_other.h"

#elif defined(__18CXX)
    #include "can_pic18.h"

#elif defined(_PIC18)
    #include "can_pic18.h"

#elif defined(__PIC24F__)
    #include "can_p24Fxxxx.h"

#elif defined(__PIC24H__)
    #include "can_p24Hxxxx.h"

#elif defined(__dsPIC30F__)
    #include "can_p30Fxxxx.h"

#elif defined(__dsPIC33E__)
    #include "can_p33Exxxx.h"

#elif defined(__dsPIC33F__)
    #include "can_p33Fxxxx.h"

#elif defined(__PIC32MX__)
    #include "can_p32xxxx.h"

#elif defined(__PIC32MZ__)
    #include "can_p32xxxx.h"


#else
    #error "Can't find header"

#endif

#endif//_PLIB_CAN_PROCESSOR_H