#ifndef INITAL_H
#define INITAL_H

#include "type.h"

void Init_system(void);
u32 password(void);
u32 open_edit_menu(void);
void update_password(s8 *);
void get_password_from_user(s8 *);
void eint0_isr(void)__irq;
void interrupt_Inital(void);
void display_RTC(void);
u32 time_limit(u32 sh, u32 sm, u32 eh, u32 em);
void device_time_setting(void);
u32 allowed_time_menu(void);
void set_start_time(void);
void set_end_time(void);
u32 get_hour_from_user(void);
u32 get_min_from_user(void);
u32 get_number_from_keypad(void);
u32 select_time_edit_option(void);
u32 rtc_edit_menu(void);
void set_rtc_hour(u32 *h);
void set_rtc_minute(u32 *mi);
void set_rtc_second(u32 *s);
void set_rtc_day(u32 *d);
void set_rtc_year(u32 *y);
void set_rtc_month(u32 * mo);
u32 days_in_month(u32 month, u32 year);
void set_rtc_date(u32 *da);
void edit_rtc_settings(void);
void time_limit_display(void);
void process_edit_menu(void);
#endif
