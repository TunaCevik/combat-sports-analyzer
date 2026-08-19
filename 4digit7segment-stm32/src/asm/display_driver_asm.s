.syntax unified
.cpu cortex-m4
.thumb

.section .text

@ --- Peripheral Base Addresses ---
.equ GPIOB_BASE,      0x40020400
.equ SPI2_BASE,       0x40003800

@ Register Offsets & Bitmasks
.equ GPIO_BSRR_OFFSET, 0x18
.equ SPI_SR_OFFSET,    0x08
.equ SPI_DR_OFFSET,    0x0C
.equ SPI_SR_TXE_BIT,   1
.equ LATCH_PIN_RESET,  (1 << (12 + 16))
.equ LATCH_PIN_SET,    (1 << 12)

.global update_display_fsm
.thumb_func
.type update_display_fsm, %function
update_display_fsm:
    @ 1. Save callee-saved registers and link register
    push {r4, r5, lr}

    @ Load base addresses
    ldr r4, =GPIOB_BASE
    ldr r5, =SPI2_BASE

    @ 2. FSM payload generation: 
    @ Upper byte (0xFC) = Segments A-G ON (Digit '8')
    @ Lower byte (0x80) = Selects Digit 4 (QD pin)
    movw r0, #0xFCF0

    @ 3. Assert Latch Low (Reset PB12 via BSRR upper half)
    ldr.w r1, =LATCH_PIN_RESET
    str r1, [r4, #GPIO_BSRR_OFFSET]

    @ 4. Wait for SPI Transmit Buffer Empty (TXE)
.wait_txe:
    ldr.w r2, [r5, #SPI_SR_OFFSET]
    tst r2, #(1 << SPI_SR_TXE_BIT)
    beq .wait_txe

    @ Write 16-bit word to SPI Data Register
    strh r0, [r5, #SPI_DR_OFFSET]

    @ 5. Optional: Wait for BSY flag to clear
.wait_bsy:
    ldr.w r2, [r5, #SPI_SR_OFFSET]
    tst r2, #(1 << 7)
    bne .wait_bsy

    @ 6. Assert Latch High (Set PB12 via BSRR lower half)
    ldr.w r1, =LATCH_PIN_SET
    str r1, [r4, #GPIO_BSRR_OFFSET]

    @ 7. Restore registers and return safely
    pop {r4, r5, pc}
