#include<lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "type.h"

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

// RTC Macros
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)

//CCR register bits
#define RTC_ENABLE  (1<<0)
#define RTC_RESET   (1<<1)
#define RTC_CLKSRC  (1<<4)

s8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

extern u32 hour,min,sec,date,month,year,dow;

void Init_RTC(void)
{
        PREINT=PREINT_VAL;
        PREFRAC=PREFRAC_VAL;
        CCR=RTC_RESET;
        CCR=RTC_ENABLE | RTC_CLKSRC;
}

void SetRTCTimeInfo(u32 hour, u32 min, u32 sec)
{
        HOUR = hour;
        MIN = min;
        SEC = sec;
}

void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
        DOM = date;
        MONTH = month;
        YEAR = year;
}

void SetRTCDay(u32 day)
{
        DOW = day;
}

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
        *hour = HOUR;
        *minute = MIN;
        *second = SEC;
}

void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
                cmdLCD(GOTO_LINE1_POS0);
                charLCD((hour/10)+48);
                charLCD((hour%10)+48);
                charLCD(':');
                charLCD((minute/10)+48);
                charLCD((minute%10)+48);
                charLCD(':');
                charLCD((second/10)+48);
                charLCD((second%10)+48);

}

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
        *date = DOM;
        *month = MONTH;
        *year = YEAR;
}

void DisplayRTCDate(u32 date, u32 month, u32 year)
{
                cmdLCD(GOTO_LINE2_POS0);
                charLCD((date/10)+48);
                charLCD((date%10)+48);
                charLCD('/');
                charLCD((month/10)+48);
                charLCD((month%10)+48);
                charLCD('/');
                u32LCD(year);
}

void GetRTCDay(s32 *day)
{
        *day = DOW;
}

void DisplayRTCDay(u32 dow)
{
        cmdLCD(GOTO_LINE1_POS0+10);
        strLCD(week[dow]);
}
