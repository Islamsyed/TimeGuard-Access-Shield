#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#include<string.h>

#define PASSWORD_LENGTH 4
s8 default_password[PASSWORD_LENGTH+1]="1234";

u32 password(void)
{
        s8 entered[PASSWORD_LENGTH+1],key;
        u32 i=0;

        cmdLCD(CLEAR_LCD);
        delay_ms(2);
        cmdLCD(GOTO_LINE1_POS0);
        strLCD("Enter Password:");
        delay_ms(100);
        clear_line2();
        cmdLCD(GOTO_LINE2_POS0);
        while(i < PASSWORD_LENGTH)
        {
                key = Keyscan();
                if(key == 'B')
                {
                    if(i>0)
                     {
                        i--; // reduce count
                        entered[i]='\0'; // remove last char
                        cmdLCD(GOTO_LINE2_POS0+i); // move cursor back 1 position
                        charLCD(' '); // overwrite previous * with space
                        cmdLCD(GOTO_LINE2_POS0+i);
                     }
                }
                else
                {
                        entered[i] = key;
                        charLCD(entered[i]);
                        delay_ms(150);
                        cmdLCD(GOTO_LINE2_POS0+i);
                        charLCD('*');
                        i++;
                }
                delay_ms(300);
        }
        entered[i]='\0';


        if(strcmp(entered,default_password)==0)
        {
                cmdLCD(CLEAR_LCD);
                delay_ms(2);
                strLCD("Acess Granted");
                delay_ms(1000);
                cmdLCD(CLEAR_LCD);
                delay_ms(2);
                return 1;
        }
        else
        {
                cmdLCD(CLEAR_LCD);
                delay_ms(2);
                strLCD("Invalid password");
                delay_ms(1000);
                cmdLCD(CLEAR_LCD);
                delay_ms(2);
                return 0;
        }

}
