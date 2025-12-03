#include "type.h"
#include <Lpc21xx.h>

void cfgportpinFunc(u32 portNO,u32 pinNO,u32 pinFunc)
{
        if(portNO==0)
        {
                if(pinNO<16)
                {
                        PINSEL0=((PINSEL0&~(3<<(pinNO*2)))|(pinFunc<<(pinNO*2)));
                }
                else if(pinNO>=16 && pinNO<=31)
                {
                        PINSEL1=((PINSEL1&~(3<<((pinNO-16)*2)))|(pinFunc<<((pinNO-16)*2)));
                }
        }
        else if(portNO==1)
        {
        //not require for Lpc2129

        }
}
