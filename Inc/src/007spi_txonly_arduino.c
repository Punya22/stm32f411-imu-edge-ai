/*
 * 007spi_txonly_arduino.c
 *
 * STM32F411 (Black Pill) - SPI2 Master Transmit Only
 * Protocol: Sends Length Byte first, then Data Bytes
 * * Hardware Connections (to Arduino via Level Shifter):
 * PB12 --> NSS / CS  (Arduino Pin 10) - Configured as General Purpose Output
 * PB13 --> SCLK      (Arduino Pin 13) - Alternate Function 5
 * PB15 --> MOSI      (Arduino Pin 11) - Alternate Function 5
 * PB14 --> MISO      (Arduino Pin 12) - Unused (Simplex transmission)
 */

#include "stm32f411xx.h"
#include <string.h>
#include <stdint.h>

int main(void) {
    // 1. Enable GPIOB Clock (Bit 1 in AHB1ENR)
    RCC->AHB1ENR |= (1 << 1);

    // 2. Enable SPI2 Clock (Bit 14 in APB1ENR)
    RCC->APB1ENR |= (1 << 14);

    // ==========================================
    // GPIO CONFIGURATION
    // ==========================================

    // 3. Configure PB13 (SCLK) and PB15 (MOSI) for Alternate Function 5
    // Clear MODER bits for PB13 and PB15
    GPIOB->MODER &= ~((3 << 26) | (3 << 30));
    // Set MODER to Alternate Function (10 in binary is 2)
    GPIOB->MODER |= ((2 << 26) | (2 << 30));

    // Set Alternate Function to AF5 for PB13 and PB15 in AFRH (AFR[1])
    // PB13 is bits 23:20, PB15 is bits 31:28
    GPIOB->AFR[1] &= ~((0xF << 20) | (0xF << 28));
    GPIOB->AFR[1] |= ((5 << 20) | (5 << 28));

    // Set pins to High Speed
    GPIOB->OSPEEDR |= ((3 << 26) | (3 << 30));

    // 4. Configure PB12 (NSS/CS) as General Purpose Output
    // The Arduino requires this pin to go LOW to receive data
    GPIOB->MODER &= ~(3 << 24); // Clear PB12 mode
    GPIOB->MODER |= (1 << 24);  // Set PB12 to Output mode (01)
    GPIOB->ODR |= (1 << 12);    // Pull PB12 HIGH initially (Idle state)

    // ==========================================
    // SPI2 CONFIGURATION
    // ==========================================

    // 5. Configure SPI2 CR1 Register
    SPI2->CR1 = 0; // Reset everything first to guarantee reset values

    // Explicitly clear CPOL, CPHA, and DFF (8-bit mode) for good practice
    SPI2->CR1 &= ~(1 << 1);  // CPOL = 0 (Low when idle)
    SPI2->CR1 &= ~(1 << 0);  // CPHA = 0 (Data captured on first edge)
    SPI2->CR1 &= ~(1 << 11); // DFF = 0  (8-bit data frame format)

    // Set Master Mode (Bit 2), Baud Rate to DIV64 (Bits 5:3 = 101)
    // Set Software Slave Management (SSM - Bit 9) and Internal Slave Select (SSI - Bit 8)
    SPI2->CR1 |= (1 << 2) | (5 << 3) | (1 << 9) | (1 << 8);

    // 6. Enable SPI2 (SPE - Bit 6)
    SPI2->CR1 |= (1 << 6);

    // ==========================================
    // DATA TRANSMISSION LOOP
    // ==========================================

    char data[] = "Hello world";
    uint8_t dataLen = strlen(data); // Calculate length once

    while(1) {
        // Pull PB12 (CS) LOW to wake up Arduino slave
        GPIOB->ODR &= ~(1 << 12);

        // --- STEP 1: SEND THE LENGTH BYTE ---
        // Wait until TXE flag is 1 (Buffer Empty)
        while(!(SPI2->SR & (1 << 1)));
        // Send the length byte explicitly as 8 bits
        *((volatile uint8_t *)&SPI2->DR) = dataLen;

        // --- STEP 2: SEND THE DATA PAYLOAD ---
        for(int i = 0; i < dataLen; i++) {
            // Wait until TXE flag is 1 (Buffer Empty)
            while(!(SPI2->SR & (1 << 1)));
            // Send 1 byte of the string explicitly as 8 bits
            *((volatile uint8_t *)&SPI2->DR) = data[i];
        }

        // --- STEP 3: WAIT FOR TRANSMISSION TO FINISH ---
        // Wait until TXE is 1 (Buffer Empty) AND BSY is 0 (Not Busy)
        // This guarantees the final bit has physically left the MOSI pin
        while(!(SPI2->SR & (1 << 1)));
        while(SPI2->SR & (1 << 7));

        // Pull PB12 (CS) HIGH to put Arduino slave back to sleep
        GPIOB->ODR |= (1 << 12);

        // Delay for a bit before sending the next burst
        for(volatile int i = 0; i < 500000; i++);
    }
}
