#ifndef _PLIB_ADCP_PROCESSOR_H
#define _PLIB_ADCP_PROCESSOR_H

#if defined(__PIC32MX__)
	#include "adcp_p32xxxx.h"
	
#elif defined(__PIC32MZ__)
	#include "adcp_p32xxxx.h"

#else
    #error Cant find header

#endif

#endif//_PLIB_ADCP_PROCESSOR_H