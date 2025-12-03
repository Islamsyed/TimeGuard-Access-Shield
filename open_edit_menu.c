//open_edit_menu.c
#include<string.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "kpm.h"

char menu[4][16]={"1.EDIT RTC","2.DEVICE TIME","3.UPDATE PIN","4.EXIT"};
u32 open_edit_menu(void)
{
        u32 index=0;
        char key;

        cmdLCD(CLEAR_LCD);
        delay_ms(2);

        while(1)
        {
                clear_line2(); // clear line
                cmdLCD(CLEAR_LCD);
                delay_ms(2);
                strLCD(menu[index]); // show menu item

                //read keypad
                key = Keyscan();

                        if(key == 'U') // scroll up
                        {
                                if(index == 0)
                                         index =3;
                                else
                                        index--;
                        }
                        else if(key == 'D') // scroll down
                        {
                                if(index == 3)
                                        index=0;
                                else
                                        index++;
                        }
                        else if(key == 'S') // select
                        {

                                return index;
                        }
                delay_ms(300);
        }

}
