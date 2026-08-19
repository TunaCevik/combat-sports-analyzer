#include "gpio_init.h"

#define LATCH_PORT       GPIOB
#define LATCH_PIN        LL_GPIO_PIN_12

void MX_GPIO_Init_For_SPI2(void) {
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 1. Enable GPIOB Clock */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    /* 2. Configure SPI SCK Pin (PB13) as Alternate Function AF5 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* 3. Configure SPI MOSI Pin (PB15) as Alternate Function AF5 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* 4. Configure Latch Pin (PB12) as standard Push-Pull Output */
    GPIO_InitStruct.Pin = LATCH_PIN;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    LL_GPIO_Init(LATCH_PORT, &GPIO_InitStruct);
    
    /* Ensure Latch starts LOW */
    LL_GPIO_ResetOutputPin(LATCH_PORT, LATCH_PIN);
}
