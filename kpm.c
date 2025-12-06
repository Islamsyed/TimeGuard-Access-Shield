//kpm.c

#include<lpc21xx.h>
#include "type.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"

u32 kpmLUT[4][4]={{'1','2','3','4'},
                  {'5','6','7','8'},
                  {'9','0','R','U'},
                  {'B','N','S','D'}
                };

void Init_kpm(void)
{
        IODIR1|=15<<ROW0;
}

u32 Colscan(void)
{
           u32 status;
           status = (((IOPIN1>>COL0)&15)<15) ? 0 : 1;
           return status;
}

u32 Rowcheck(void)
{
        u32 r;
        for(r=0;r<=3;r++)
        {
                // starting with row 0 upto row 3
                IOPIN1 = ((IOPIN1&~(15<<ROW0))|(~(1<<r)<<ROW0));
                // check which key was pressed in that row
                if(Colscan()==0)
                {
                        break;
                }
        }
        //re-initalise rows to null or to their state
        IOCLR1 = 15<<ROW0;
        return r;
}

u32 Colcheck(void)
{
        u32 c;
        for(c=0;c<=3;c++)
        {
                //starting with  col 0 upto col 3
                if(((IOPIN1>>(COL0+c))&1)==0)
                {
                        break;
                }
        }
        return c;
}

u32 Keyscan(void)
{
        u32 r,c,keyV;
        //intialise kpm
        Init_kpm();
        //wait for any key press
        while(Colscan());

        r=Rowcheck();

        c=Colcheck();

        keyV=kpmLUT[r][c];
        return keyV;
}

void Readnum(u32 * num,u32 * lastkey)
{
        u32 key;
        *num=0;
        while(1)
        {
                key=Keyscan();
                if(key>='0' && key<='9')
                {
                        *num=(*num*10)+(key-'0');
                        cmdLCD(GOTO_LINE2_POS0);
                        charLCD('*');
                        while(Colscan()==0);
                }
                else
                {
                        *lastkey=key;
                        cmdLCD(GOTO_LINE2_POS0);
                        charLCD(*lastkey);
                        while(Colscan()==0);
                        break;
                }
        }
}
