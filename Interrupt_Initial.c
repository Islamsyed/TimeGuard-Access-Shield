#include "inital.h"
#include "delay.h"
#include "kpm.h"
#include<lpc21xx.h>
#include "pin_connect_block.h"

#define EINT0_VIC_CHNO 14
#define EINT0_PIN_0_1 3
extern u32 irq_flag;
void interrupt_Inital(void)
{
        cfgportpinFunc(0,1,EINT0_PIN_0_1);
        VICIntEnable =1<<EINT0_VIC_CHNO;
        VICVectCntl0 =(1<<5)|EINT0_VIC_CHNO;
        VICVectAddr0=(u32)eint0_isr;
        EXTMODE =1<<0;
}

void eint0_isr(void)__irq
{
        irq_flag=1;

         EXTINT =1<<0;
         VICVectAddr=0;
}
