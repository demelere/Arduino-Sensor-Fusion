#ifndef HMC5883L_H
#define HMC5883L_H

#include <stdint.h>

void HMC5883L_init();
int16_t read_HMC5883L_magnetometer_x();
int16_t read_HMC5883L_magnetometer_y();
int16_t read_HMC5883L_magnetometer_z();

#endif // HMC5883L_H magnetometer
