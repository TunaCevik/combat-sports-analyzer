// 1. Standard C Libraries
#include <stdio.h>
#include "hardware.h"   // clock config symbols
#include "timer.h"      // your timer API
#include "gpio_init.h"
#include "spi_2_init.h"
#include "display_driver_asm.h"

extern void initialise_monitor_handles(void);

void SystemClock_Config(void);

int main(void) {

    initialise_monitor_handles();
    SystemClock_Config();
    timer_init();

    // Initialize your hardware peripherals
    MX_GPIO_Init_For_SPI2();
    MX_SPI2_Init();

    printf("System Booted @ 180 MHz\n");
    printf("Semihosting active.\n");
  
    while(1) {
	update_display_fsm();
	timer_delay_ms(1000);
    }
}

void SystemClock_Config(void) {
    // 1. Enable Power Control Clock
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    // 2. Set Voltage Scale 1 and Enable Over-Drive (Required for 180 MHz)
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_PWR_EnableOverDriveMode();
    while(LL_PWR_IsActiveFlag_OD() != 1); // Wait for Over-Drive to be ready
    LL_PWR_EnableOverDriveSwitching();
    while(LL_PWR_IsActiveFlag_ODSW() != 1); // Wait for switch to complete

    // 3. Configure Flash Latency (5 Wait States needed for 180 MHz at 3.3V)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

    // 4. Configure the Main PLL using the HSI (16 MHz)
    // M = 16, N = 360, P = 2
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 360, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();
    while(LL_RCC_PLL_IsReady() != 1); // Wait for PLL to lock

    // 5. Configure Bus Prescalers
    // The STM32F446 cannot handle 180 MHz on its peripheral buses!
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1); // AHB = 180 MHz
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);  // APB1 = 45 MHz (Max allowed is 45 MHz)
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);  // APB2 = 90 MHz (Max allowed is 90 MHz)

    // 6. Switch System Clock Source to the PLL
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL); // Wait for switch

    // 7. Update internal LL variables with the new speed
    LL_SetSystemCoreClock(SYSTEM_CORE_CLOCK);
}
