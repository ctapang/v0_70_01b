#ifndef _PLIB_SB_PROCESSOR_H
#define _PLIB_SB_PROCESSOR_H

#if defined(__PIC32MX__)
    #include "sb_p32xxxx.h"
	
#elif defined(__PIC32MZ__)
    #include "sb_p32xxxx.h"


#else
    #error "Can't find header"

#endif

#endif//_PLIB_SB_PROCESSOR_H