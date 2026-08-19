#include "spi_2_init.h"

void MX_SPI2_Init(void) {
    LL_SPI_InitTypeDef SPI_InitStruct = {0};

    /* Enable SPI2 Peripheral Clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

    /* Configure SPI_CR1 parameters via LL Driver struct */
    SPI_InitStruct.TransferDirection = LL_SPI_HALF_DUPLEX_TX;
    SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
    SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_16BIT;
    SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
    SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV32;
    SPI_InitStruct.BitOrder = LL_SPI_LSB_FIRST;
    
    LL_SPI_Init(SPI2, &SPI_InitStruct);

    /* Set Motorola protocol */
    LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);

    /* Enable SPI2 */
    LL_SPI_Enable(SPI2);
}
