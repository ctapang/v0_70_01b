#include "app.h"

#include <sys/attribs.h>
#include <sys/kmem.h>

extern volatile GFX_COLOR GraphicsFrame[1][(DISP_VER_RESOLUTION)][(DISP_HOR_RESOLUTION)];

void APP_Initialize(void) {

    /* Switch SYSCLK */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB15Rbits.RPB15R = 0x0b; //OC5
    INT2Rbits.INT2R = 4;
    SYSKEY = 0x33333333;

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;
    ANSELG = 0;
    ANSELH = 0;
    ANSELJ = 0;
    ANSELK = 0;

    //Turn on Camera Clock source
    OC5CON = 0;
    OC5R = 0x0004;
    OC5RS = 0x0004;
    OC5CON = 0x0006;
    PR2 = 0x0008;
    T2CONSET = 0x8000;
    OC5CONSET = 0x8000;

    I2C_Init();
   
}

void APP_Tasks(void)
{
      return;
}
