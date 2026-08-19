// inc/hardware.h
#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include "stm32f446xx.h"

// Common LL modules nearly every file will need
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_cortex.h"

#define SYSTEM_CORE_CLOCK 180000000U // 180 MHz

#endif // HARDWARE_H
