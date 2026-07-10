/*
 * stm32f411xx_gpio.h
 *
 *  Created on: 14-Jun-2026
 *      Author: Punya
 */

#ifndef INC_STM32F411XX_GPIO_H_
#define INC_STM32F411XX_GPIO_H_

#include "stm32f411xx.h"

/*
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN         0
#define GPIO_MODE_OUT        1
#define GPIO_MODE_ALTFN      2
#define GPIO_MODE_ANALOG     3

/*********************************************************************
 * GPIO PIN CONFIGURATION STRUCTURE
 *********************************************************************/
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;

/*********************************************************************
 * GPIO HANDLE STRUCTURE
 *********************************************************************/
typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/*********************************************************************
 * GPIO PIN NUMBERS
 *********************************************************************/
#define GPIO_PIN_NO_0				0
#define GPIO_PIN_NO_1				1
#define GPIO_PIN_NO_2				2
#define GPIO_PIN_NO_3				3
#define GPIO_PIN_NO_4				4
#define GPIO_PIN_NO_5				5
#define GPIO_PIN_NO_6				6
#define GPIO_PIN_NO_7				7
#define GPIO_PIN_NO_8				8
#define GPIO_PIN_NO_9				9
#define GPIO_PIN_NO_10				10
#define GPIO_PIN_NO_11				11
#define GPIO_PIN_NO_12				12
#define GPIO_PIN_NO_13				13
#define GPIO_PIN_NO_14				14
#define GPIO_PIN_NO_15				15

/*********************************************************************
 * GPIO POSSIBLE MODES
 *********************************************************************/
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_ALTFN				2
#define GPIO_MODE_ANALOG			3

#define GPIO_MODE_IT_FT				4
#define GPIO_MODE_IT_RT				5
#define GPIO_MODE_IT_RFT			6

/*********************************************************************
 * GPIO OUTPUT TYPES
 *********************************************************************/
#define GPIO_OP_TYPE_PP			0
#define GPIO_OP_TYPE_OD			1

/*********************************************************************
 * GPIO OUTPUT SPEEDS
 *********************************************************************/
#define GPIO_SPEED_LOW				0
#define GPIO_SPEED_MEDIUM			1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3

/*********************************************************************
 * GPIO PULL UP AND PULL DOWN CONFIGURATION MACROS
 *********************************************************************/
#define GPIO_NO_PUPD				0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2

/*********************************************************************
 * API SUPPORTED BY THIS DRIVER
 *********************************************************************/

/*
 * Peripheral Clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi);


/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value);

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);

/*
 * IRQ Configuration and ISR Handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi);

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

void GPIO_IRQHandling(uint8_t PinNumber);

/*********************************************************************
 * IRQ NUMBERS OF STM32F411xx MCU
 *********************************************************************/
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

#endif /* INC_STM32F411XX_GPIO_H_ */
