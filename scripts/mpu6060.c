#include "mpu6050.h"
#include "i2c.h"

#define MPU6050_ADDR 0x68
#define PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

void MPU6050_init() {
    TWI_start();
    TWI_write(MPU6050_ADDR << 1);
    TWI_write(PWR_MGMT_1); // Power management register
    TWI_write(0x00); // Wake up MPU6050
    TWI_stop();
}

int16_t read_MPU6050_data(uint8_t reg) { // read data from specified register
    uint8_t data_high, data_low;

    TWI_start();
    TWI_write(MPU6050_ADDR << 1);
    TWI_write(reg);
    TWI_stop();

    TWI_start();
    TWI_write((MPU6050_ADDR << 1) | 1);
    data_high = TWI_read_ack();
    data_low = TWI_read_nack();
    TWI_stop();

    return ((int16_t)data_high << 8) | data_low;
}

int16_t read_MPU6050_accel_x() {
    return read_MPU6050_data(ACCEL_XOUT_H);
}

int16_t read_MPU6050_accel_y() {
    return read_MPU6050_data(ACCEL_XOUT_H + 2);
}

int16_t read_MPU6050_accel_z() {
    return read_MPU6050_data(ACCEL_XOUT_H + 4);
}

int16_t read_MPU6050_gyro_x() {
    return read_MPU6050_data(GYRO_XOUT_H);
}

int16_t read_MPU6050_gyro_y() {
    return read_MPU6050_data(GYRO_XOUT_H + 2);
}

int16_t read_MPU6050_gyro_z() {
    return read_MPU6050_data(GYRO_XOUT_H + 4);
}
