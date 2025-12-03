#include "ardunio.h"
#include "ardunio_defines.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "Inital.h"
#include "delay.h"
#include <lpc21xx.h>

#define PIN 4

u32 irq_flag=0;
extern s8 default_password[5];
u32 h=12, mi=30, s=0, d=30, mo=11, y=2025,da=4;
u32 start_hour=11,start_min=0,end_hour=17, end_min=0;
int main()
{
    IODIR0 |= 1 << PIN;

    Init_system();

    while(1)
    {
        do
        {
            display_RTC();
        }
        while(Colscan()&& irq_flag==0);

        if(Colscan()==0)
        {
            if(password())
            {
                if(time_limit(start_hour, start_min, end_hour, end_min))
                {
                        IOSET0 = 1 << PIN;
                        delay_ms(1000);
                        IOCLR0 = 1 << PIN;
                }
               else
               {
                    cmdLCD(CLEAR_LCD);
                    strLCD("ALLOWED TIME");
                    time_limit_display();
                    delay_ms(1200);
                    cmdLCD(CLEAR_LCD);
                }
           }
        }
        if(irq_flag == 1)
        {
                irq_flag = 0;
                process_edit_menu();
        }
    }
}

void Init_system(void)
{
        Init_LCD();
        Init_RTC();
        Init_kpm();
        interrupt_Inital();

        SetRTCTimeInfo(h, mi, s);
        SetRTCDateInfo(d, mo, y);
        SetRTCDay(da);
}

void process_edit_menu(void)
{
        u32 select;

        while(1)
        {
                select = open_edit_menu();

                if(select == 3)
                {
                        while(Colscan()==0);
                        delay_ms(150);

                        cmdLCD(CLEAR_LCD);
                        strLCD("EXITING...");
                        delay_ms(500);
                        break;
                }

                switch(select)
                {
                        case 0: edit_rtc_settings(); break;
                        case 1: device_time_setting(); break;
                        case 2: update_password(default_password); break;
                }
        }

        cmdLCD(CLEAR_LCD);
        delay_ms(10);
}

void time_limit_display(void)
{
        cmdLCD(GOTO_LINE2_POS0);

        charLCD((start_hour/10)+'0');
        charLCD((start_hour%10)+'0');
        charLCD(':');
        charLCD((start_min/10)+'0');
        charLCD((start_min%10)+'0');

        strLCD(" TO ");

        charLCD((end_hour/10)+'0');
        charLCD((end_hour%10)+'0');
        charLCD(':');
        charLCD((end_min/10)+'0');
        charLCD((end_min%10)+'0');
}
