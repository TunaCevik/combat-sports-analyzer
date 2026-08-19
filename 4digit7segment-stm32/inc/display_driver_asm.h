#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Updates the 4-digit 7-segment display FSM, manages the latch pin via BSRR,
 *         and streams data to SPI2_DR.
 */
void update_display_fsm(void);

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_DRIVER_H */
