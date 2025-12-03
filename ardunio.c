 #include "lpc21xx.h"
 #include "type.h"
 #include "ardunio_defines.h"

void pinMode(u32 pinNo,u32 pinDir)
{
        if(pinNo<32)
        {
                if(pinDir == OUTPUT)
                {
                        IODIR0 |= 1<<pinNo;
                }
                else
                {
                        IODIR0&=~(1<<pinNo);
                }

        }
        else if((pinNo>=32) && (pinNo<=47))
        {
                if(pinDir == OUTPUT)
                {
                        IODIR1 |= 1<<(pinNo-16);
                }
                else
                {
                        IODIR1 &= ~(1<<(pinNo-16));
                }

        }
}

void digitalWrite(u32 pinNo,u32 bit)
{
        if(pinNo<32)
        {
                bit ? (IOSET0 = 1<<pinNo) : (IOCLR0 = 1<<pinNo);
        }
        else if((pinNo >= 32) && (pinNo<=47))
        {
                 bit ? (IOSET1 = 1<<(pinNo-16)) : (IOCLR1 = 1<<(pinNo-16));

        }
}

u32 digitalRead(u32 pinNo)
{
        u32 bit;
        if(pinNo < 32)
        {
                bit = ((IOPIN0>>pinNo)&1);
        }
        else if((pinNo >=32 ) &&  (pinNo<=47))
        {
                bit = ((IOPIN1 >> (pinNo-16))&1);
        }

        return bit;
}
void portMode(u32 pinstartNo,u32 npins,u32 pinsDir)
{
        if(pinstartNo < 32)
        {
                if(pinsDir == OUTPUT)
                        IODIR0 |=((1<<npins)-1)<<pinstartNo;
                else
                        IODIR0 &=~((1<<npins)-1)<<pinstartNo;
        }
        else if((pinstartNo >= 32) && (pinstartNo <= 47))
        {
                if(pinsDir == OUTPUT)
                        IODIR1 |=((1<<npins)-1)<<(pinstartNo-16);
                else
                        IODIR1 &=~((1<<npins)-1)<<(pinstartNo-16);
        }
}
void write2pins(u32 pinstartNo,u32 npins,u32 data)
{
        if(pinstartNo < 32)
        {
                IOCLR0 = ((1 << npins)-1) << pinstartNo;
                IOSET0 = data<<pinstartNo;
        }
        else if((pinstartNo >= 32) &&   (pinstartNo >= 47))
        {
                IOCLR1 = ((1 << npins)-1)<<(pinstartNo-16);
                IOSET1 = data<<(pinstartNo-16);
        }
}

u32 readpins(u32 pinstartNo,u32 npins)
{
        u32 data;
        if(pinstartNo < 32)
                data = ((IOPIN0 >> pinstartNo)& ((1 << npins)-1));
        else if(pinstartNo >= 32 && pinstartNo <= 47)
                data = ((IOPIN1 >> (pinstartNo-16))& ((1 << npins)-1));

        return data;
}
