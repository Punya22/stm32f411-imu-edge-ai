/*
 * stm32f411xx.h
 *
 *  Created on: 12-Jun-2026
 *      Author: Punya
 */
#include <stdint.h>
#include <stddef.h>
#ifndef INC_STM32F411XX_H_
#define INC_STM32F411XX_H_

#define __vo volatile
#define SPI4_BASEADDR    (APB2PERIPH_BASEADDR + 0x3400)
#define NULL ((void *)0)
/************************************START:PROCESSOR SPECIFIC DETAILS******************************
 *
 * ARM CORTEX Mx Processor NVIC ISERx register Addresses
 *  */

#define NVIC_ISER0			((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1			((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2			((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3			((__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0   ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1   ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2   ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3   ((__vo uint32_t*)0xE000E18C)


#define FLASH_BASEADDR		0x08000000U
#define SRAM_BASEADDR		0X20000000U
#define SRAM 				SRAM_BASEADDR

#define PERIPH_BASEADDR			0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U

#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR    		(AHB1PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR    		(AHB1PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR    		(AHB1PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR    		(AHB1PERIPH_BASEADDR + 0x1C00U)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800U)

#define I2C1_BASEADDR 			(APB1PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00U)

#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000U)
#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00U)
#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400U)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800U)
#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00U)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000U)

/* APB2 peripherals */

#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400U)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00U)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800U)

typedef struct
{
    volatile uint32_t MODER;     /*!< GPIO port mode register,                Address offset: 0x00 */
    volatile uint32_t OTYPER;    /*!< GPIO port output type register,         Address offset: 0x04 */
    volatile uint32_t OSPEEDR;   /*!< GPIO port output speed register,        Address offset: 0x08 */
    volatile uint32_t PUPDR;     /*!< GPIO port pull-up/pull-down register,   Address offset: 0x0C */
    volatile uint32_t IDR;       /*!< GPIO port input data register,          Address offset: 0x10 */
    volatile uint32_t ODR;       /*!< GPIO port output data register,         Address offset: 0x14 */
    volatile uint32_t BSRR;     /*!< GPIO port bit set/reset low register,   Address offset: 0x18 */
    //volatile uint32_t BSRRH;     /*!< GPIO port bit set/reset high register,  Address offset: 0x1A */
    volatile uint32_t LCKR;      /*!< GPIO port configuration lock register,  Address offset: 0x1C */
    volatile uint32_t AFR[2];    /*!< AFR[0]: alt func low (0x20), AFR[1]: alt func high (0x24) */
} GPIO_RegDef_t;

#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)


typedef struct
{
    volatile uint32_t CR;          /* Address offset: 0x00 */
    volatile uint32_t PLLCFGR;     /* Address offset: 0x04 */
    volatile uint32_t CFGR;        /* Address offset: 0x08 */
    volatile uint32_t CIR;         /* Address offset: 0x0C */
    volatile uint32_t AHB1RSTR;    /* Address offset: 0x10 */
    volatile uint32_t AHB2RSTR;    /* Address offset: 0x14 */
    uint32_t      RESERVED0[2];    /* Reserved (AHB3RSTR slot),  0x18-0x1C */
    volatile uint32_t APB1RSTR;    /* Address offset: 0x20 */
    volatile uint32_t APB2RSTR;    /* Address offset: 0x24 */
    uint32_t      RESERVED1[2];    /* Reserved,                  0x28-0x2C */
    volatile uint32_t AHB1ENR;     /* Address offset: 0x30 */
    volatile uint32_t AHB2ENR;     /* Address offset: 0x34 */
    uint32_t      RESERVED2[2];    /* Reserved (AHB3ENR slot),   0x38-0x3C */
    volatile uint32_t APB1ENR;     /* Address offset: 0x40 */
    volatile uint32_t APB2ENR;     /* Address offset: 0x44 */
    uint32_t      RESERVED3[2];    /* Reserved,                  0x48-0x4C */
    volatile uint32_t AHB1LPENR;   /* Address offset: 0x50 */
    volatile uint32_t AHB2LPENR;   /* Address offset: 0x54 */
    uint32_t      RESERVED4[2];    /* Reserved (AHB3LPENR slot), 0x58-0x5C */
    volatile uint32_t APB1LPENR;   /* Address offset: 0x60 */
    volatile uint32_t APB2LPENR;   /* Address offset: 0x64 */
    uint32_t      RESERVED5[2];    /* Reserved,                  0x68-0x6C */
    volatile uint32_t BDCR;        /* Address offset: 0x70 */
    volatile uint32_t CSR;         /* Address offset: 0x74 */
    uint32_t      RESERVED6[2];    /* Reserved,                  0x78-0x7C */
    volatile uint32_t SSCGR;       /* Address offset: 0x80 */
    volatile uint32_t PLLI2SCFGR;  /* Address offset: 0x84 */
    uint32_t      RESERVED7;       /* Reserved,                  0x88 */
    volatile uint32_t DCKCFGR;     /* Address offset: 0x8C */
} RCC_RegDef_t;

typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    uint32_t RESERVED[2];
    volatile uint32_t CMPCR;
}SYSCFG_RegDef_t;

typedef struct
{
	__vo uint32_t CR1;        /*!< I2C control register 1,              Address offset: 0x00 */
	__vo uint32_t CR2;        /*!< I2C control register 2,              Address offset: 0x04 */
	__vo uint32_t OAR1;       /*!< I2C own address register 1,          Address offset: 0x08 */
	__vo uint32_t OAR2;       /*!< I2C own address register 2,          Address offset: 0x0C */
	__vo uint32_t DR;         /*!< I2C data register,                   Address offset: 0x10 */
	__vo uint32_t SR1;        /*!< I2C status register 1,               Address offset: 0x14 */
	__vo uint32_t SR2;        /*!< I2C status register 2,               Address offset: 0x18 */
	__vo uint32_t CCR;        /*!< I2C clock control register,          Address offset: 0x1C */
	__vo uint32_t TRISE;      /*!< I2C TRISE register,                  Address offset: 0x20 */
	__vo uint32_t FLTR;       /*!< I2C FLTR register,                   Address offset: 0x24 */
} I2C_RegDef_t;

typedef struct
{
	volatile uint32_t SR; /*Address Offset at 0x00*/
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef_t;

#define I2C1 ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2 ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3 ((I2C_RegDef_t*)I2C3_BASEADDR)


#define RCC							((RCC_RegDef_t*)RCC_BASEADDR)

/*Peripheral Clock Enable */
#define GPIOA_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLOCK_EN()			(RCC->AHB1ENR |= (1<<7))

/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()    ( RCC->APB1ENR |= (1 << 21) )
#define I2C2_PCLK_EN()    ( RCC->APB1ENR |= (1 << 22) )
#define I2C3_PCLK_EN()    ( RCC->APB1ENR |= (1 << 23) )

/*
 * Clock Enable Macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()    ( RCC->APB2ENR |= (1 << 12) )
#define SPI2_PCLK_EN()    ( RCC->APB1ENR |= (1 << 14) )
#define SPI3_PCLK_EN()    ( RCC->APB1ENR |= (1 << 15) )
#define SPI4_PCLK_EN()    ( RCC->APB2ENR |= (1 << 13) )

/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCLK_EN()  ( RCC->APB2ENR |= (1 << 4) )
#define USART2_PCLK_EN()  ( RCC->APB1ENR |= (1 << 17) )
#define USART6_PCLK_EN()  ( RCC->APB2ENR |= (1 << 5) )

/*
 * Clock Enable Macro for SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN()  ( RCC->APB2ENR |= (1 << 14) )

/*
 * Clock Enable Macros for GPIOx peripherals (AHB1ENR)
 */
#define GPIOA_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 0) )
#define GPIOB_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 1) )
#define GPIOC_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 4) )
#define GPIOH_PCLK_EN()   ( RCC->AHB1ENR |= (1 << 7) )

/*
 * Peripheral Clock Disable Macros for GPIOx
 */
#define GPIOA_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 0) )
#define GPIOB_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 4) )
#define GPIOH_PCLK_DI()   ( RCC->AHB1ENR &= ~(1 << 7) )

/*
 * Peripheral Clock Disable Macros for I2Cx
 */
#define I2C1_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 21) )
#define I2C2_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 22) )
#define I2C3_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 23) )

/*
 * Peripheral Clock Disable Macros for SPIx
 */
#define SPI1_PCLK_DI()    ( RCC->APB2ENR &= ~(1 << 12) )
#define SPI2_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 14) )
#define SPI3_PCLK_DI()    ( RCC->APB1ENR &= ~(1 << 15) )
#define SPI4_PCLK_DI()    ( RCC->APB2ENR &= ~(1 << 13) )

/*
Bit position definitions I2C_CR1
*/
#define I2C_CR1_PE				0
#define I2C_CR1_NOSTRETCH 		7
#define I2C_CR1_START			8
#define I2C_CR1_STOP			9
#define I2C_CR1_ACK				10
#define I2C_CR1_SWRST			15

/*
Bit position definitions for I2C_CR2
*/
#define I2C_CR2_FREQ			0
#define I2C_CR2_ITERREN			8
#define I2C_CR2_ITEVTEN			9
#define I2C_CR2_ITBUFEN			10

/*
Bit position definitions for I2C_OAR1
 */
#define I2C_OAR1_ADDMODE		15
#define I2C_OAR1_ADD98			8
#define I2C_OAR1_ADD71			1
#define I2C_OAR1_ADD0			0
/*
Bit position definitions for I2C_SR1
*/
#define I2C_SR1_SB         0
#define I2C_SR1_ADDR       1
#define I2C_SR1_BTF        2
#define I2C_SR1_ADD10      3
#define I2C_SR1_STOPF      4
#define I2C_SR1_RXNE       6
#define I2C_SR1_TXE        7
#define I2C_SR1_BERR       8
#define I2C_SR1_ARLO       9
#define I2C_SR1_AF         10
#define I2C_SR1_OVR        11
#define I2C_SR1_TIMEOUT    14
/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL        0
#define I2C_SR2_BUSY       1
#define I2C_SR2_TRA        2
#define I2C_SR2_GENCALL    4
#define I2C_SR2_DUALF      7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR        0
#define I2C_CCR_DUTY       14
#define I2C_CCR_FS         15

/*
Peripheral Clock Disable Macros for USARTx
*/
#define USART1_PCLK_DI()  ( RCC->APB2ENR &= ~(1 << 4) )
#define USART2_PCLK_DI()  ( RCC->APB1ENR &= ~(1 << 17) )
#define USART6_PCLK_DI()  ( RCC->APB2ENR &= ~(1 << 5) )

/*
 * Peripheral Clock Disable Macro for SYSCFG
 */
#define SYSCFG_PCLK_DI()  ( RCC->APB2ENR &= ~(1 << 14) )

/*
 * Macros to reset GPIOx Peripherals
 */
#define GPIOA_REG_RESET() \
do{ \
    RCC->AHB1RSTR |= (1 << 0); \
    RCC->AHB1RSTR &= ~(1 << 0); \
}while(0)

#define GPIOB_REG_RESET() \
do{ \
    RCC->AHB1RSTR |= (1 << 1); \
    RCC->AHB1RSTR &= ~(1 << 1); \
}while(0)

#define GPIOC_REG_RESET() \
do{ \
    RCC->AHB1RSTR |= (1 << 2); \
    RCC->AHB1RSTR &= ~(1 << 2); \
}while(0)
#define GPIOD_REG_RESET() \
do{ \
RCC->AHB1RSTR |= (1<<3); \
RCC->AHB1RSTR &= ~(1<<3); \
}while(0)

#define GPIOE_REG_RESET() \
do{ \
RCC->AHB1RSTR |= (1<<4); \
RCC->AHB1RSTR &= ~(1<<4); \
}while(0)

#define GPIOH_REG_RESET() \
do{ \
RCC->AHB1RSTR |= (1<<7); \
RCC->AHB1RSTR &= ~(1<<7); \
}while(0)

#define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA)?0:\
                                   (x == GPIOB)?1:\
                                   (x == GPIOC)?2:\
                                   (x == GPIOD)?3:\
                                   (x == GPIOE)?4:\
                                   (x == GPIOH)?7:0)

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40
#define IRQ_NO_SPI1         35
#define IRQ_NO_SPI2         36
#define IRQ_NO_SPI3         51
#define IRQ_NO_SPI4			84
#define IRQ_NO_I2C1_EV      31
#define IRQ_NO_I2C1_ER      32

/*
 * macros for all the possible priority levels
 */
#define NVIC_IRQ_PRI0       0
#define NVIC_IRQ_PRI15      15

/*Some generic Macros*/
#define ENABLE 				1
#define DISABLE 			0
#define SET					ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET
typedef enum
{
    FLAG_RESET = 0,
    FLAG_SET   = 1
} FlagStatus;

#define NO_PR_BITS_IMPLEMENTED		4

/************************************************************
 * Bit position of definitions of SPI Peripherals
 * *********************************************************/
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RxONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15

/*
 * Bit Position definitions SPI_CR2
*/
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7

/*
 * Bit Position definitions SPI_SR
*/
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8


typedef struct
{
    volatile uint32_t IMR;      // Interrupt Mask Register
    volatile uint32_t EMR;      // Event Mask Register
    volatile uint32_t RTSR;     // Rising Trigger Selection Register
    volatile uint32_t FTSR;     // Falling Trigger Selection Register
    volatile uint32_t SWIER;    // Software Interrupt Event Register
    volatile uint32_t PR;       // Pending Register

} EXTI_RegDef_t;

#define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)
#define NVIC_PR_BASEADDR	((__vo uint32_t*)0xE000E400)


#define SPI4_I2S4_BASEADDR      (APB2PERIPH_BASEADDR + 0x3400)


/****************************************************
 * General Purpose Timers
 ****************************************************/
#define TIM2_BASEADDR           (APB1PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR           (APB1PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR           (APB1PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR           (APB1PERIPH_BASEADDR + 0x0C00)


/****************************************************
 * Watchdog Timers
 ****************************************************/
#define WWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x2C00)  // Window Watchdog
#define IWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x3000)  // Independent Watchdog


/****************************************************
 * Real Time Clock (RTC)
 ****************************************************/
#define RTC_BASEADDR            (APB1PERIPH_BASEADDR + 0x2800)


/****************************************************
 * SPI / I2S Communication Peripherals
 ****************************************************/
#define I2S2EXT_BASEADDR        (APB1PERIPH_BASEADDR + 0x3400)  // Extended I2S2
#define SPI2_I2S2_BASEADDR      (APB1PERIPH_BASEADDR + 0x3800)  // SPI2 / I2S2
#define SPI3_I2S3_BASEADDR      (APB1PERIPH_BASEADDR + 0x3C00)  // SPI3 / I2S3
#define I2S3EXT_BASEADDR        (APB1PERIPH_BASEADDR + 0x4000)  // Extended I2S3


/****************************************************
 * Power Control Peripheral
 ****************************************************/
#define PWR_BASEADDR            (APB1PERIPH_BASEADDR + 0x7000)

typedef struct
{
	__vo uint32_t CR1;        /*!< SPI control register 1,             Address offset: 0x00 */
	__vo uint32_t CR2;        /*!< SPI control register 2,             Address offset: 0x04 */
	__vo uint32_t SR;         /*!< SPI status register,                Address offset: 0x08 */
	__vo uint32_t DR;         /*!< SPI data register,                  Address offset: 0x0C */
	__vo uint32_t CRCPR;      /*!< SPI CRC polynomial register,        Address offset: 0x10 */
	__vo uint32_t RXCRCR;     /*!< SPI Rx CRC register,                Address offset: 0x14 */
	__vo uint32_t TXCRCR;     /*!< SPI Tx CRC register,                Address offset: 0x18 */
	__vo uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,     Address offset: 0x1C */
	__vo uint32_t I2SPR;      /*!< SPI_I2S prescaler register,         Address offset: 0x20 */
} SPI_RegDef_t;

#define SPI1 ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4 ((SPI_RegDef_t*)SPI4_BASEADDR)

/*Peripheral Clock Enable for SPIx*/


#define SPI5_PCLK_EN()  (RCC->APB2ENR |= (1 << 20))
#define USART1 ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2 ((USART_RegDef_t*)USART2_BASEADDR)
#define USART6 ((USART_RegDef_t*)USART6_BASEADDR)
/*USARTx Clock Enable*/
#define USART1_REG_RESET() \
do{ \
    RCC->APB2RSTR |= (1 << 4); \
    RCC->APB2RSTR &= ~(1 << 4); \
}while(0)

#define USART2_REG_RESET() \
do{ \
    RCC->APB1RSTR |= (1 << 17); \
    RCC->APB1RSTR &= ~(1 << 17); \
}while(0)

#define USART6_REG_RESET() \
do{ \
    RCC->APB2RSTR |= (1 << 5); \
    RCC->APB2RSTR &= ~(1 << 5); \
}while(0)
/****************************************************
 * TIM2 register definition (general purpose timer)
 ****************************************************/
typedef struct
{
	__vo uint32_t CR1;       /* 0x00 */
	__vo uint32_t CR2;       /* 0x04 */
	__vo uint32_t SMCR;      /* 0x08 */
	__vo uint32_t DIER;      /* 0x0C */
	__vo uint32_t SR;        /* 0x10 */
	__vo uint32_t EGR;       /* 0x14 */
	__vo uint32_t CCMR1;     /* 0x18 */
	__vo uint32_t CCMR2;     /* 0x1C */
	__vo uint32_t CCER;      /* 0x20 */
	__vo uint32_t CNT;       /* 0x24 */
	__vo uint32_t PSC;       /* 0x28 */
	__vo uint32_t ARR;       /* 0x2C */
	uint32_t      RESERVED0; /* 0x30 */
	__vo uint32_t CCR1;      /* 0x34 */
	__vo uint32_t CCR2;      /* 0x38 */
	__vo uint32_t CCR3;      /* 0x3C */
	__vo uint32_t CCR4;      /* 0x40 */
	uint32_t      RESERVED1; /* 0x44 */
	__vo uint32_t DCR;       /* 0x48 */
	__vo uint32_t DMAR;      /* 0x4C */
	__vo uint32_t OR;        /* 0x50 */
} TIM_RegDef_t;

#define TIM2            ((TIM_RegDef_t*)TIM2_BASEADDR)
#define TIM2_PCLK_EN()  ( RCC->APB1ENR |= (1 << 0) )
#define TIM2_PCLK_DI()  ( RCC->APB1ENR &= ~(1 << 0) )
#define IRQ_NO_TIM2     28
#endif /* INC_STM32F411XX_H_ */
