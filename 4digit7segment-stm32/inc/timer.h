// inc/timer.h
#ifndef TIMER_H
#define TIMER_H

#include "hardware.h"   // gives it stdint, LL clock/cortex stuff

void timer_init(void);
void timer_delay_ms(uint32_t ms);

#endif // TIMER_H
