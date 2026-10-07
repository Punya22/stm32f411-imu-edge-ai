/*
 * main.c
 *
 *  Created on: 29-Sept-2026
 *      Author: Punya
 */

// Make sure to include your actual device header and driver headers here
#include "stm32f411xx.h"
#include "stm32f411xx_i2c_driver.h"
#include "stm32f411xx_gpio.h" // Assuming you have a GPIO driver
#include "mpu6050.h"

I2C_Handle_t I2C1Handle;


// Configures PB6 (SCL) and PB7 (SDA) for I2C1
void I2C1_GPIOInits(void)
{
    GPIO_Handle_t I2CPins;

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4; // AF4 for I2C1, 2, 3 on STM32F411
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD; // Open Drain is required for I2C
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; // Enable internal pull-ups
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    // SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIO_Init(&I2CPins);

    // SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&I2CPins);
}

// Configures the I2C1 peripheral parameters
void I2C1_Inits(void)
{
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0x61; // Own address (doesn't matter for master)
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM; // 100 kHz standard mode

    I2C_Init(&I2C1Handle);
}
// returns 0 if write succeeded and read-back matches, 1 otherwise
static uint8_t MPU_WriteVerify(uint8_t reg, uint8_t val)
{
    MPU6050_WriteRegister(&I2C1Handle, reg, val);
    return (MPU6050_ReadRegister(&I2C1Handle, reg) == val) ? 0 : 1;
}
// Add this helper function to main.c to write data to the sensor
volatile uint8_t tick = 0;

// ISR: sirf flag aur debug pin toggle. I2C yahan nahi.
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & (1 << 0))          // UIF
    {
        TIM2->SR &= ~(1 << 0);        // flag clear
        GPIOA->ODR ^= (1 << 1);       // PA1 toggle (debug pin)
        tick = 1;
    }
}

void TIM2_Init_100Hz(void)
{
    // PA1 as output
    GPIOA_PCLK_EN();
    GPIOA->MODER &= ~(3U << 2);
    GPIOA->MODER |=  (1U << 2);

    // TIM2: 16 MHz / (1600 * 100) = 100 Hz
    TIM2_PCLK_EN();
    TIM2->PSC = 1599;
    TIM2->ARR = 99;
    TIM2->EGR = 1;                    // UG: PSC/ARR load karo
    TIM2->SR &= ~(1 << 0);            // UG se bana UIF clear karo
    TIM2->DIER |= (1 << 0);           // update interrupt enable
    *NVIC_ISER0 |= (1U << IRQ_NO_TIM2);
    TIM2->CR1 |= (1 << 0);            // counter start
}
int main(void)
{
    uint8_t who_am_i;
    uint8_t sensor_data[14];
    int16_t az_raw;
    int32_t gx_sum = 0, gy_sum = 0, gz_sum = 0;
    int16_t gx_bias, gy_bias, gz_bias;
    int16_t gx, gy, gz;
    uint8_t data_start_reg = 0x3B; // ACCEL_XOUT_H
    volatile uint8_t init_err = 0;

    I2C1_GPIOInits();
    I2C1_Inits();
    I2C_PeripheralControl(I2C1, ENABLE);

    who_am_i = MPU6050_ReadRegister(&I2C1Handle, MPU6050_WHO_AM_I);

    if(who_am_i == 0x70)
    {
        // ---- sensor init ----
        MPU6050_WriteRegister(&I2C1Handle, 0x6B, 0x80);   // device reset
        for(volatile uint32_t d = 0; d < 500000; d++);

        init_err |= MPU_WriteVerify(0x6B, 0x01) << 0;     // sleep band, PLL clock
        for(volatile uint32_t d = 0; d < 500000; d++);

        init_err |= MPU_WriteVerify(0x19, 0x00) << 1;     // SMPLRT_DIV = 0 -> 1 kHz
        init_err |= MPU_WriteVerify(0x1A, 0x03) << 2;     // gyro DLPF ~41 Hz
        init_err |= MPU_WriteVerify(0x1B, 0x00) << 3;     // gyro +-250 dps
        init_err |= MPU_WriteVerify(0x1C, 0x00) << 4;     // accel +-2 g
        init_err |= MPU_WriteVerify(0x1D, 0x03) << 5;     // accel DLPF ~44.8 Hz

        for(volatile uint32_t d = 0; d < 2000000; d++);   // gyro settle

        // ---- gyro bias ----
        for(int i = 0; i < 100; i++)
        {
            I2C_MasterSendData(&I2C1Handle, &data_start_reg, 1, MPU6050_ADDR, I2C_ENABLE_SR);
            I2C_MasterReceiveData(&I2C1Handle, sensor_data, 14, MPU6050_ADDR, I2C_DISABLE_SR);

            gx_sum += (int16_t)((sensor_data[8]  << 8) | sensor_data[9]);
            gy_sum += (int16_t)((sensor_data[10] << 8) | sensor_data[11]);
            gz_sum += (int16_t)((sensor_data[12] << 8) | sensor_data[13]);
        }
        gx_bias = gx_sum / 100;
        gy_bias = gy_sum / 100;
        gz_bias = gz_sum / 100;

        // ---- timer start, ab 100 Hz tick chalu ----
        TIM2_Init_100Hz();

        while(1)
        {
            if(tick)
            {
                tick = 0;

                I2C_MasterSendData(&I2C1Handle, &data_start_reg, 1, MPU6050_ADDR, I2C_ENABLE_SR);
                I2C_MasterReceiveData(&I2C1Handle, sensor_data, 14, MPU6050_ADDR, I2C_DISABLE_SR);

                az_raw = (int16_t)((sensor_data[4] << 8) | sensor_data[5]);
                az_raw += 1554;   // temporary, Step 4 mein hatega
                gx = (int16_t)((sensor_data[8]  << 8) | sensor_data[9])  - gx_bias;
                gy = (int16_t)((sensor_data[10] << 8) | sensor_data[11]) - gy_bias;
                gz = (int16_t)((sensor_data[12] << 8) | sensor_data[13]) - gz_bias;
            }
        }
    }
    else
    {
        while(1); // Error state
    }

    return 0;
}
