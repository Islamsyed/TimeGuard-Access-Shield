#ifndef  _ARDUNIO_H_
#define  _ARDUNIO_H_

#include "type.h"

void pinMode(u32 pinNo,u32 pinDir);
void digitalWrite(u32 pinNo,u32 bit);
u32  digitalRead(u32 pinNo);

void portMode(u32 pinstartNo,u32 npins,u32 pinsDir);
void write2pins(u32 pinstartNo,u32 npins,u32 data);
void readpins(u32 pinstartNo,u32 npins);


#endif
