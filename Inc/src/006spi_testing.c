/*
 * 006spi_testing.c
 *
 * STM32F411 - SPI1 Testing (Alternate Pins Workaround)
 * * PB4  --> SPI1_MISO
 * PB5  --> SPI1_MOSI
 * PB3  --> SPI1_SCLK
 * PA15 --> SPI1_NSS
 * ALT FUNCTION MODE: 5
*/

#include "stm32f411xx.h"
#include "stm32f411xx_spi_driver.h"
#include <string.h>

void SPI1_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

    // SCLK, MISO, MOSI ke liye GPIOB
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCLK (PB3)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPIPins);

	// MOSI (PB5)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIPins);

	// MISO (PB4)
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIPins);

	// NSS ke liye GPIOA (PA15)
	SPIPins.pGPIOx = GPIOA;
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);
}

void SPI1_Inits(void)
{
	SPI_Handle_t SPI1handle;
	SPI1handle.pSPIx = SPI1;
	SPI1handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;


	SPI1handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV64;
	SPI1handle.SPIConfig.SPI_DFF = SPI_DFF__8BITS;
	SPI1handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1handle.SPIConfig.SPI_SSM = SPI_SSM_SW;

	SPI_Init(&SPI1handle);
}

int main(void) {
    // 1. Enable GPIOA Clock (Bit 0 in AHB1ENR)
    RCC->AHB1ENR |= (1 << 0);

    // 2. Enable SPI1 Clock (Bit 12 in APB2ENR)
    RCC->APB2ENR |= (1 << 12);

    // 3. Configure PA5 (SCLK) and PA7 (MOSI) for Alternate Function 5
    // Clear MODER bits for PA5 and PA7
    GPIOA->MODER &= ~((3 << 10) | (3 << 14));
    // Set MODER to Alternate Function (10 in binary is 2) for PA5 and PA7
    GPIOA->MODER |= ((2 << 10) | (2 << 14));

    // Set Alternate Function to AF5 for PA5 and PA7 in AFRL (AFR[0])
    GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 28)); // Clear
    GPIOA->AFR[0] |= ((5 << 20) | (5 << 28));      // Set AF5

    // Set pins to High Speed
    GPIOA->OSPEEDR |= ((3 << 10) | (3 << 14));

    // 4. Configure SPI1 CR1 Register
    SPI1->CR1 = 0; // Reset everything first

    // Set MSTR (Bit 2), BR to DIV64 (Bits 5:3 = 101), SSM (Bit 9), SSI (Bit 8)
    SPI1->CR1 |= (1 << 2) | (5 << 3) | (1 << 9) | (1 << 8);

    // 5. Enable SPI1 (SPE - Bit 6)
    SPI1->CR1 |= (1 << 6);

    char data[] = "Hello world";

    // 6. Infinite Loop sending data
    while(1) {
        for(int i = 0; i < strlen(data); i++) {
            // Wait until TXE flag (Bit 1 in SR) is 1 (Buffer Empty)
            while(!(SPI1->SR & (1 << 1)));
            // Send 1 byte
            SPI1->DR = data[i];
        }

        // Wait for a bit before sending the next burst
        for(volatile int i = 0; i < 500000; i++);
    }
}
