#ifndef    LPC2148_GPIO_REGS_H
#define   LPC2148_GPIO_REGS_H
#include <LPC214x.h>

volatile unsigned long* const GPIO_DIR_REG[] =  {  &IODIR0,  &IODIR1 };
volatile unsigned long* const GPIO_PIN_REG[] =  {  &IOPIN0,  &IOPIN1 };
volatile unsigned long* const GPIO_SET_REG[] = {  &IOSET0, &IOSET1 };
volatile unsigned long* const GPIO_CLR_REG[] = {  &IOCLR0, &IOCLR1 };
#endif


