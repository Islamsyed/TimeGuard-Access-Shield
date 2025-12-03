TimeGuard Access Shield ---Password-Controlled, Time-Restricted Machine Operation System

Overview
TimeGuard Access Shield is a secure, password-based machine control system that restricts device operation to predefined working hours. 
It ensures that only authorized users can operate equipment and strictly within the allowed time window. 
This enhances safety, reduces unauthorized usage, and enables reliable automation in industrial or controlled environments.

AIM

To design a password-controlled automation system that permits device operation only when:

1. The user enters a valid password.
2. The current real-time clock (RTC) is within the permitted working hours.

Objectives

1. Display real-time date and time on a 16x2 LCD.
2. Authenticate users using a keypad-based password entry system.
3. Store and modify allowed operational working hours.
4. Provide an interrupt-driven configuration menu for updating:
   * RTC Information
   * Allowed device operation times
   * System password
5. Control the device ON/OFF state based on authentication and allowed time.

Hardware Requirements
1.LPC2148 ARM7 Microcontroller
2.16×2 LCD Display
3.4×4 Matrix Keypad
4.Device (LED/Relay Load)
5.External Switch for Interrupt
6.USB–UART Converter / DB-9 Cable

Software Requirements

Embedded C Programming
Flash Magic / Keil µVision

Project Workflow

1. On startup, LCD, RTC, keypad, and control logic are initialized.
2. Default LCD screen displays the current time from RTC.
3. User enters a password via keypad:
   Correct password + valid time window → Device ON
   Invalid password or time mismatch → Access denied
5. Pressing the interrupt switch pauses the main program and opens a configuration menu.

Configuration Menu

When the switch is pressed, display:

1. EDIT RTCINFO     3. PASSWORD CHANGE
2. EDIR DEVICE A TIME  4. EXIT

RTC Editing Process:

Menu structure:
1. Hour   2. Minute 3. Second 4. Day
5. Date   6. Month  7. Year   8. Exit

* User edits selected field via keypad.
* Input validation required:

  * Hours: 0–23
  * Minutes/Seconds: 0–59
  * Date must match month rules (including leap year)
* Invalid input → Error message + Retry
* Selecting **Exit** returns to main logic.

Allowed Time Editing:

Menu:
1. Set Start Time
2. Set End Time
3. Exit

* User enters new Start/End times.
* Values must be validated.
* Updated times are stored after confirmation.

Password Editing:

1. User enters current password.
2. If correct, user enters new password.
3. New password must be re-entered for confirmation.
4. If mismatch → Error + Retry.
5. On success, new password is saved.

Exit Menu:
Selecting **EXIT** returns to the main program and resumes machine control logic.

Conclusion

TimeGuard Access Shield is a robust solution for controlled machine access.
It integrates real-time scheduling, password authentication, and interrupt-driven configuration, making it ideal for:

* Training laboratories
* Industrial workshops
* Hazardous machinery operation zones
* Any environment requiring controlled and time-restricted equipment usage

The system enhances safety, prevents misuse, and supports disciplined automation.
