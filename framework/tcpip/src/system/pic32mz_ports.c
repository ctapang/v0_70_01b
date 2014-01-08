

#if defined (HARMONY_FS)
#include "system_config.h"
#else
#include "system_services.h"
#endif
#include "pic32mz_ports.h"

#if defined(__PIC32MZ__)


// limited PIC32MZ implementation for ETH RMII support
//




void PORTSetPinsDigitalIn(IoPortId portId, unsigned int inputs)
{
    if(portId == IOPORT_D)
    {
        ANSELDCLR = inputs;
        TRISDSET = inputs;
    }
    else if(portId == IOPORT_H)
    {
        ANSELHCLR = inputs;
        TRISHSET = inputs;
    }
    else if(portId == IOPORT_J)
    {
        ANSELJCLR = inputs;
        TRISJSET = inputs;
    }
    else
    {   // not implemented
        SYS_ASSERT(0, "");
    }

}

void PORTSetPinsDigitalOut(IoPortId portId, unsigned int outputs)
{
    if(portId == IOPORT_D)
    {
        ANSELDCLR = outputs;
        TRISDCLR = outputs;
    }
    else if(portId == IOPORT_H)
    {
        ANSELHCLR = outputs;
        TRISHCLR = outputs;
    }
    else if(portId == IOPORT_J)
    {
        ANSELJCLR = outputs;
        TRISJCLR = outputs;
    }
    else
    {   // not implemented
        SYS_ASSERT(0, "");
    }

}

#endif // defined(__PIC32MZ__)


