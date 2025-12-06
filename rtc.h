#include "type.h"
#ifndef RTC_H
#define RTC_H

void Init_RTC(void);

void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);
void GetRTCDay(s32 *);
void DisplayRTCDay(u32);

void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);
void SetRTCDay(u32);

#endif
