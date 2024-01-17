#include "hmc5883l.h"
#include "i2c.h"

#define HMC5883L_ADDR 0x1E
#define CONFIG_REG_A  0x00
#define CONFIG_REG_B  0x01
#define MODE_REG      0x02
#define DATA_OUTPUT_X_MSB 0x03
#define DATA_OUTPUT_Z_MSB 0x05
#define DATA_OUTPUT_Y_MSB 0x07

void HMC5883L_init() { // init the magnetometer sensor
    TWI_start();
    TWI_write(HMC5883L_ADDR << 1);
    TWI_write(CONFIG_REG_A);
    TWI_write(0x70); // config for output of 8-average, 15 Hz default, normal measurement
    TWI_stop();

    TWI_start();
    TWI_write(HMC5883L_ADDR << 1);
    TWI_write(CONFIG_REG_B);
    TWI_write(0xA0); // config for gain setting of = 5
    TWI_stop();

    TWI_start();
    TWI_write(HMC5883L_ADDR << 1);
    TWI_write(MODE_REG);
    TWI_write(0x00); // config for continuous measurement mode
    TWI_stop();
}

int16_t read_HMC5883L_data(uint8_t reg) { // to do: calibrate and convert raw readings to gauss, microtesla, etc.
    uint8_t data_high, data_low;

    TWI_start();
    TWI_write(HMC5883L_ADDR << 1);
    TWI_write(reg);
    TWI_stop();

    TWI_start();
    TWI_write((HMC5883L_ADDR << 1) | 1); // read operation
    data_high = TWI_read_ack();
    data_low = TWI_read_nack();
    TWI_stop();

    return ((int16_t)data_high << 8) | data_low;
}

int16_t read_HMC5883L_magnetometer_x() {
    return read_HMC5883L_data(DATA_OUTPUT_X_MSB);
}

int16_t read_HMC5883L_magnetometer_y() {
    return read_HMC5883L_data(DATA_OUTPUT_Y_MSB);
}

int16_t read_HMC5883L_magnetometer_z() {
    return read_HMC5883L_data(DATA_OUTPUT_Z_MSB);
}
