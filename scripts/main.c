#include "mpu6050.h"
#include "bmp280.h"
#include "hmc5883l.h"
#include "sensor_fusion.h"
#include <util/delay.h>
#include <math.h>

#define DT 0.01 // 10 ms loop time

void init_sensors() { // init all sensors
    MPU6050_init();
    BMP280_init();
    HMC5883L_init();
}

float calculate_accel_angle(int16_t accel_x, int16_t accel_y, int16_t accel_z) {
    float ax = accel_x / 16384.0; // Assuming +/- 2g range for accelerometer
    float ay = accel_y / 16384.0;
    float az = accel_z / 16384.0;

    // Calculate pitch (tilt along X-axis)
    float pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;

    return pitch; // Return pitch angle
}

float complementary_filter(float accel_angle, float gyro_rate) {
    static float fused_angle = 0;
    float alpha = 0.98;

    // Integrate the gyro rate to get an angle and apply the filter
    fused_angle = alpha * (fused_angle + gyro_rate) + (1 - alpha) * accel_angle;

    return fused_angle;
}

int main() {
    init_sensors();

    float gyro_angle, accel_angle, fused_angle;
    int16_t gyro_x, accel_x, accel_y, accel_z;

    while (1) {
        // Read sensor data
        gyro_x = read_MPU6050_gyro_x();
        accel_x = read_MPU6050_accel_x();
        accel_y = read_MPU6050_accel_y();
        accel_z = read_MPU6050_accel_z();

        // convert gyroscope data to angle (degrees)
        gyro_angle = gyro_x / 131.0 * DT; // Assuming +/- 250 degrees/second range

        // calc accelerometer angle by convert raw readings to pitch angle
        accel_angle = calculate_accel_angle(accel_x, accel_y, accel_z);

        // apply complementary filter to fuse accelerometer and gyroscope data
        fused_angle = complementary_filter(accel_angle, gyro_angle);

        // You can now use fused_angle for further processing

        _delay_ms(10); // sampling rate using delay of 10ms (DT)
    }

    return 0;
}
