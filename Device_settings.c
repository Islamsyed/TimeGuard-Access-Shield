#include "kpm.h"
#include "lcd.h"
#include "delay.h"
#include "type.h"
#include "Inital.h"
#include "lcd_defines.h"
#include<stdlib.h>

extern u32 start_hour,start_min,end_hour,end_min;

void device_time_setting(void)
{
    u32 choice;

    while(1)
    {
        choice = allowed_time_menu();
                if(choice==2)
                {
                        delay_ms(100);
                        break;
                }
        switch(choice)
        {
            case 0: set_start_time();
                    break;
            case 1: set_end_time();
                    break;
        }
    }
}

u32 allowed_time_menu(void)
{
    char menu[][16] = {"1.SET START TIME", "2.SET END TIME", "3.EXIT"};
    u32 selected = 0,key;

    while(1)
    {
        cmdLCD(CLEAR_LCD);
        delay_ms(2);
        strLCD(menu[selected]);
        delay_ms(200);

        key=Keyscan();

        if(key=='U')
        {
            if(selected==0)
                selected=2;
            else
                selected--;
        }
        else if(key=='D')
        {
            if(selected==2)
                selected=0;
           else
                selected++;
        }
        else if(key=='S')
        {
            return selected;

        }
    }
}

void set_start_time(void)
{
    u32 option;

    cmdLCD(CLEAR_LCD);
    delay_ms(200);

    option = select_time_edit_option();

    switch(option)
    {
        case 0  :start_hour = get_hour_from_user();
                break;

        case 1 :start_min = get_min_from_user();
                break;

        case 2  :start_hour = get_hour_from_user();
                 start_min  = get_min_from_user();
                break;

        case 3 :return; // EXIT
    }

    cmdLCD(CLEAR_LCD);
    delay_ms(2);
    strLCD("START TIME SAVED");
    delay_ms(1000);
}

void set_end_time(void)
{
    u32 op;

    cmdLCD(CLEAR_LCD);
    delay_ms(200);

    op = select_time_edit_option();

    switch(op)
    {
        case 0 : end_hour = get_hour_from_user();
                 break;

        case 1 :end_min = get_min_from_user();
                break;

        case 2 :end_hour = get_hour_from_user();
                end_min  = get_min_from_user();
                break;

        case 3 :return;
    }

    cmdLCD(CLEAR_LCD);
    delay_ms(2);
    strLCD("END TIME SAVED");
    delay_ms(1000);
}

u32 get_hour_from_user(void)
{
    u32 h;

    while(1)
    {
        cmdLCD(0x01);
        delay_ms(300);
        strLCD("Enter Hour 0-23");

        h = get_number_from_keypad();

        if(h <= 23)
        {
            cmdLCD(0x01);
            delay_ms(2);
            return h;
        }

        cmdLCD(0x01);
        delay_ms(2);
        strLCD("Invalid Hour!");
        delay_ms(1000);
    }
}

u32 get_min_from_user(void)
{
    u32 m;

    while(1)
    {
        cmdLCD(0x01);
        delay_ms(300);
        strLCD("Enter Min (0-59)");

        m = get_number_from_keypad();

        if(m <= 59)
            return m;

        cmdLCD(0x01);
        delay_ms(2);
        strLCD("Invalid Minute!");
        delay_ms(800);
    }
}

u32 select_time_edit_option(void)
{
    char opt[][16] = {"1.HOUR", "2.MINUTE", "3.HOUR+MIN", "4.EXIT"};
    u32 s = 0;
    char key;

    while(1)
    {
        cmdLCD(CLEAR_LCD);
                delay_ms(2);
        strLCD(opt[s]);
        delay_ms(200);

        key = Keyscan();

        if(key=='U')  // up
        {
            if(s==0)
               s=3;
            else
              s--;
        }
        else if(key=='D') // down
        {
            if(s==3)
                s=0;
            else
               s++;
        }
        else if(key=='S') // select
        {
            return s;
        }
    }
}
u32 get_number_from_keypad(void)
{
    char buf[3] = {0,0,0};
    char key;
    u32 value = 0;
    int pos = 0;

    cmdLCD(GOTO_LINE2_POS0);

    while (1)
    {
        key = Keyscan();
        delay_ms(120);
        if(key==0)
        {
                continue;
        }

        if (key >= '0' && key <= '9')
        {
            if (pos < 2)
            {
                buf[pos] = key;
                cmdLCD(GOTO_LINE2_POS0 + pos);
                charLCD(buf[pos]);
                                delay_ms(200);
                pos++;
            }

        }
        else if (key == 'B')
        {
            if (pos > 0)
            {
                pos--;
                buf[pos] = '\0';
                cmdLCD(GOTO_LINE2_POS0 + pos);
                charLCD(' ');
                cmdLCD(GOTO_LINE2_POS0 + pos);
            }
        }
        else if (key == 'S')
        {
            if (pos == 0)
            {
                continue;
            }
            else if (pos == 1)
            {
                value = (u32)(buf[0] - '0');
                return value;
            }
            else
            {
                value = (u32)((buf[0] - '0') * 10 + (buf[1] - '0'));
                return value;
            }
        }
