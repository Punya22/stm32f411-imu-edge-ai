/*
 * mpu6050.h
 *
 *  Created on: 29-Sept-2026
 *      Author: Punya
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_


#include "stm32f411xx_i2c_driver.h"


// ---------- DEVICE INFORMATION ----------

#define MPU6050_ADDR 0x68


// ---------- REGISTERS----------

#define MPU6050_WHO_AM_I       0x75
#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_SMPLRT_DIV     0x19
#define MPU6050_CONFIG         0x1A
#define MPU6050_GYRO_CONFIG    0x1B
#define MPU6050_ACCEL_CONFIG   0x1C
#define MPU6050_INT_PIN_CFG    0x37
#define MPU6050_INT_ENABLE     0x38
#define MPU6050_INT_STATUS     0x3A

#define MPU6050_ACCEL_XOUT_H   0x3B
#define MPU6050_ACCEL_XOUT_L   0x3C
#define MPU6050_ACCEL_YOUT_H   0x3D
#define MPU6050_ACCEL_YOUT_L   0x3E
#define MPU6050_ACCEL_ZOUT_H   0x3F
#define MPU6050_ACCEL_ZOUT_L   0x40

#define MPU6050_GYRO_XOUT_H    0x43
#define MPU6050_GYRO_XOUT_L    0x44
#define MPU6050_GYRO_YOUT_H    0x45
#define MPU6050_GYRO_YOUT_L    0x46
#define MPU6050_GYRO_ZOUT_H    0x47
#define MPU6050_GYRO_ZOUT_L    0x48


// ---------- EXPECTED DEVICE ID ----------

#define MPU6050_WHO_AM_I_VALUE 0x70


// ---------- DRIVER FUNCTIONS ----------

void MPU6050_Init(I2C_Handle_t *pI2CHandle);

uint8_t MPU6050_ReadRegister(
    I2C_Handle_t *pI2CHandle,
    uint8_t RegAddr
);

void MPU6050_WriteRegister(
    I2C_Handle_t *pI2CHandle,
    uint8_t RegAddr,
    uint8_t Data
);

#endif
