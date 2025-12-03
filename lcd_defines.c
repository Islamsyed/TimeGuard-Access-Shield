#include "delay.h"
#include "type.h"
#include "ardunio.h"
#include "ardunio_defines.h"
#include "lcd_defines.h"
#include "lcd.h"

//Init_LCD
void Init_LCD(void)
{
	//cfg 8 data pins and 3 control pins as output pins
	portMode(LCD_DATA,11,OUTPUT);
	delay_ms(15);//power on disp
	cmdLCD(MODE_8BIT_1LINE);//init seq start
	delay_us(4100);	
	
	cmdLCD(MODE_8BIT_1LINE);//init seq start
	delay_us(100);
	cmdLCD(MODE_8BIT_1LINE);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DSP_ON_CUR_OFF);
	cmdLCD(CLEAR_LCD);
	cmdLCD(SHIFT_CUR_RIGHT);
}

void cmdLCD(u8 cmdbyte)
{
	//select cmd reg
	digitalWrite(LCD_RS,0);
	//WRITE TO CMD reg via data pins
	writeLCD(cmdbyte);
}

//to write to lcd
void writeLCD(u8 byte)
{
	//select write operation
	digitalWrite(LCD_RW,0);
	//write any byte onto to the data pins d0-d7
	write2pins(LCD_DATA,8,byte);
	//give high to low pulse for latching
	digitalWrite(LCD_EN,1);
	delay_us(2);
	digitalWrite(LCD_EN,0);
	delay_ms(2);//byte b/w byte delay
}

void charLCD(u8 asciival)
{
	// select data reg
	digitalWrite(LCD_RS,1);
	// write via data pins
	writeLCD(asciival);
}

void strLCD(s8 * p)
{
	while(*p)
		charLCD(*p++);
}

void u32LCD(u32 n)
{
		u8 digit[15];
		s32 i=0;
		if(n==0)
		{
			charLCD('0');
		}
		else
		{
			while(n>0)
			{
				digit[i++]=(n%10)+48;
				n/=10;
			}
			for(--i;i>=0;i--)
			{
				charLCD(digit[i]);
			}
		}
}

void s32LCD(s32 n)
{
	if(n<0)
	{
		charLCD('-');
		n=-n;
	}
	u32LCD(n);
}
	
void f32LCD(f32 fn,u32 ndp)
{
	u32 n,i;
	if(fn<0.0)
	{
		charLCD('-');
		fn=-fn;
	}
	n=fn;
	u32LCD(n);
	charLCD('.');
	for(i=0;i<ndp;i++)
	{
		fn=(fn-n)*10;
		n=fn;
		charLCD(n+'0');
	}
}

void CGRAM(u8 * p,u8 nbytes)
{
	u32 i;
	// points to cgram start 0x40
	cmdLCD(GOTO_CGRAM_START);
	// select data register
	digitalWrite(LCD_RS,1);
	// write to cgram reg bytes for custom character
	for(i=0;i<nbytes;i++)
	{
		writeLCD(p[i]);
	}
	// return back to data ram
	cmdLCD(GOTO_LINE1_POS0);
}

void clear_line2()
{
    cmdLCD(GOTO_LINE2_POS0);
    strLCD("                ");   // 16 spaces for 16x2 LCD
    cmdLCD(GOTO_LINE2_POS0);    // return cursor to start
}

