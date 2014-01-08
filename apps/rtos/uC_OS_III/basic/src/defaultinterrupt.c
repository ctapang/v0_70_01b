#include <xc.h>
// PIC32 devices have a software breakpoint instruction.
// Create a macro to use it easily with inline assembly.
#define PIC32_SOFTWARE_BREAK()  __asm__ volatile ("sdbbp 0")

void __attribute__((weak, naked, nomips16, noreturn, section(".vector_default"))) _DefaultInterrupt (void)
{
 volatile int* p = &RSWRST;
 PIC32_SOFTWARE_BREAK();

 do {
   __builtin_disable_interrupts();
   SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;
 } while(0);
 //RSWRSTSET=0x00000001;
 *p |= 1;
 *p;
 while(1);
}

