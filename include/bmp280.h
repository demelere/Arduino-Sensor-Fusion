#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>

void BMP280_init();
int32_t read_BMP280_pressure();

#endif // BMP280_H barometer