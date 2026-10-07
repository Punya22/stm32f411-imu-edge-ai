/*
 * mpu6050.c
 *
 *  Created on: 29-Sept-2026
 *      Author: Punya
 */
#include "mpu6050.h"


void MPU6050_WriteRegister(
        I2C_Handle_t *pI2CHandle,
        uint8_t RegAddr,
        uint8_t Data)
{
    uint8_t buffer[2];

    buffer[0] = RegAddr;
    buffer[1] = Data;

    I2C_MasterSendData(
        pI2CHandle,
        buffer,
        2,
        MPU6050_ADDR,
        I2C_DISABLE_SR
    );
}


uint8_t MPU6050_ReadRegister(
        I2C_Handle_t *pI2CHandle,
        uint8_t RegAddr)
{
    uint8_t value = 0;

   I2C_MasterSendData(pI2CHandle,&RegAddr,1,MPU6050_ADDR,I2C_ENABLE_SR);
   I2C_MasterReceiveData(
          pI2CHandle,
          &value,
          1,
          MPU6050_ADDR,
          I2C_DISABLE_SR
      );

    return value;
}


void MPU6050_Init(I2C_Handle_t *pI2CHandle)
{
    /* Will implement after WHO_AM_I read works. */
}

