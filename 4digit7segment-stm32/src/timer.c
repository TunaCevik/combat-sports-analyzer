#include "timer.h"
#include "stm32f4xx_ll_cortex.h"
volatile uint32_t sys_tick_count = 0;

void timer_init(void) {
    LL_Init1msTick(180000000);
    
    LL_SYSTICK_EnableIT();
}

void SysTick_Handler(void) {
    sys_tick_count++;
}

void timer_delay_ms(uint32_t ms) {
    uint32_t start_time = sys_tick_count;
    while ((sys_tick_count - start_time) < ms);
}
