#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#include <string.h>
#include "Inital.h"

#define PASSWORD_LENGTH 4
extern s8 default_password[PASSWORD_LENGTH+1];

void update_password(s8 *saved_pass)
{
    s8 old_entered[5];
    s8 new_password[5];
    s8 confirm_password[5];

    //ASK OLD PASSWORD
    cmdLCD(CLEAR_LCD);
    delay_ms(2);
    strLCD("OLD PASSWORD");
                delay_ms(200);
    cmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(old_entered);

    if(strcmp(old_entered, saved_pass) != 0)
    {
        cmdLCD(CLEAR_LCD);
        delay_ms(2);
        strLCD("WRONG PASSWORD");
        delay_ms(800);
        return;     // exit without update
    }

    //ENTER NEW PASSWORD
    cmdLCD(CLEAR_LCD);
    delay_ms(2);
    strLCD("NEW PASSWORD");
    cmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(new_password);

    //CONFIRM PASSWORD
    cmdLCD(CLEAR_LCD);
    delay_ms(2);
    strLCD("CONFIRM PASSWORD");
    cmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(confirm_password);

    if(strcmp(new_password, confirm_password) == 0)
    {
        strcpy(default_password, new_password);   // update global password

        cmdLCD(CLEAR_LCD);
        strLCD("PASSWORD UPDATED");
        delay_ms(800);
                cmdLCD(0x01);
    }
    else
    {
        cmdLCD(CLEAR_LCD);
        strLCD("MISMATCH");
        delay_ms(800);
    }
}

void get_password_from_user(s8 *buffer)
{
    s8 key;
    u32 i = 0;

    while(i < PASSWORD_LENGTH)
    {
        key = Keyscan();

            if(key == 'B')    // BACKSPACE
            {
                if(i > 0)
                {
                    i--;
                    buffer[i] = '\0';

                    cmdLCD(GOTO_LINE2_POS0 + i);
                    charLCD(' ');
                    cmdLCD(GOTO_LINE2_POS0 + i);
                }
            }
            else
            {
                buffer[i] = key;

                charLCD(buffer[i]);  //show password when press key
                delay_ms(100);
                i++;
            }
            delay_ms(200);
    }

    buffer[i] = '\0';
}
