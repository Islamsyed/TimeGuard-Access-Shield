#ifndef _LCD_H_
#define _LCD_H_

#include "type.h"
void writeLCD(u8 byte);
void cmdLCD(u8 cmdbyte);
void Init_LCD(void);
void charLCD(u8 asciival);
void strLCD(s8 * p);
void u32LCD(u32 n);
void s32LCD(s32 n);
void f32LCD(f32 fn,u32 ndp);
void CGRAM(u8 * p,u8 nbytes);
void clear_line2(void);
#endif
