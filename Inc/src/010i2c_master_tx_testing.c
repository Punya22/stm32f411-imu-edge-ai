/*
 * 010i2c_master_tx_testing.c
 *
 *  Created on: 07-Jul-2026
 *      Author: Punya
 */
#include<stdio.h>
#include<string.h>
#include"stm32f411xx.h"
#include"stm32f411xx_i2c_driver.h"
#include "stm32f411xx_gpio.h"
I2C_Handle_t I2C1Handle;
void delay(void)
{
	for(uint32_t i = 0;i<500000/2;i++);
}

uint8_t some_data [] = "We are testing I2C master Tx\n";
void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;
	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure SCL pin
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);

	// Configure SDA pin
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2CPins);
}
void I2C_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
	I2C_Init(&I2C1Handle);
}
int main (void)
{
	// 1. I2C pin inits
	I2C1_GPIOInits();

	// 2. I2C peripheral configuration
	I2C_Inits();

	// 3. Enable the I2C peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// 4. Continuous Transmission Loop
	while(1)
	{
		// Send data to the slave
		I2C_MasterSendData(&I2C1Handle, some_data, strlen((char*)some_data), SLAVE_ADDR);

		// Pause before the next transmission so the bus isn't flooded
		delay();
	}

	return 0;
}
