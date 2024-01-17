#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

void MPU6050_init();
int16_t read_MPU6050_accel_x();
int16_t read_MPU6050_accel_y();
int16_t read_MPU6050_accel_z();
int16_t read_MPU6050_gyro_x();
int16_t read_MPU6050_gyro_y();
int16_t read_MPU6050_gyro_z();

#endif // MPU6050_H gyroscope and accelerometer