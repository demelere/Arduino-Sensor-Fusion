#include "bmp280.h"
#include "i2c.h"

#define BMP280_ADDR 0x76
#define BMP280_REG_CTRL_MEAS 0xF4
#define BMP280_REG_CONFIG 0xF5
#define BMP280_REG_PRESSURE_DATA 0xF7

void BMP280_init() { // initialize the bmp280 sensor
    TWI_start();
    TWI_write(BMP280_ADDR << 1);
    TWI_write(BMP280_REG_CTRL_MEAS);
    TWI_write(0x27); // to do: configure normal mode, temperature and pressure oversampling x1
    TWI_stop();

    TWI_start();
    TWI_write(BMP280_ADDR << 1);
    TWI_write(BMP280_REG_CONFIG);
    TWI_write(0xA0); // standby time 1000 ms, filter off
    TWI_stop();
}

int32_t read_BMP280_pressure() { // read raw pressure data from the bmp280 sensor
    uint8_t data_msb, data_lsb, data_xlsb; // to do: need to compensate raw readings, implement addl fn and formulas
    int32_t pressure;

    TWI_start();
    TWI_write(BMP280_ADDR << 1);
    TWI_write(BMP280_REG_PRESSURE_DATA);
    TWI_stop();

    TWI_start();
    TWI_write((BMP280_ADDR << 1) | 1); // read operation
    data_msb = TWI_read_ack();
    data_lsb = TWI_read_ack();
    data_xlsb = TWI_read_nack();
    TWI_stop();

    pressure = ((int32_t)data_msb << 12) | ((int32_t)data_lsb << 4) | ((int32_t)data_xlsb >> 4);

    return pressure;
}
