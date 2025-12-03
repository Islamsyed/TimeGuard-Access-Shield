#include "lcd.h"
#include "lcd_defines.h"
#include "type.h"
#include "rtc.h"

void display_RTC(void)
{
        s32 hour,min,sec;
        s32 date,month,year;
        s32 dow;

        GetRTCTimeInfo(&hour,&min,&sec);
        GetRTCDateInfo(&date,&month,&year);
        GetRTCDay(&dow);

        DisplayRTCTime((u32)hour, (u32)min, (u32)sec);
        DisplayRTCDate((u32) date, (u32) month, (u32)year);
        DisplayRTCDay((u32) dow);
}
